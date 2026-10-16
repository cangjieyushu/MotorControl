/* ==== SOURCE: 4_SYS\sys_uart.c ==== */
/*
*     File Name :                        sys_uart
*     Library/Module Name :              sys
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             上位机通讯协议（自有协议）
*                                        ┌────┬─────┬─────┬─────┬──────┬───────┬────┐
*                                        │0xAA│ ADDR│ CMD │ LEN │ DATA │ CRC16 │0x55│
*                                        └────┴─────┴─────┴─────┴──────┴───────┴────┘
*                                         0     1     2     3    4..n   n+1,n+2  n+3
*                                        CRC16 覆盖 ADDR~DATA，多项式 0xA001（小端先发低字节）
*
*     主从说明：
*       主机：周期点名各从机(PROTO_CMD_GET_STATE)，收到应答后刷新从机表，
*             同时按 PROTO_REPORT_PERIOD_MS 把自己的汇总状态上报上位机
*       从机：只处理"ADDR == 本机 或 ADDR == 0x00(广播)"的帧，收到后立即应答
*
*     条件编译：
*       主机专属代码 → SYS_PROTO_MASTER_MODE
*       从机主动上报 → SYS_PROTO_SLAVE_REPORT_MODE
*       保证任一角色编译都无 unused 警告，且不占用 Flash。
*/

/*-------------------------- 1. 对应头文件--------------------------------*/
#include "sys_uart.h"
#include "hal_uart.h"       /* 提供 ring_buffer_* / uart_send_data / UART_DMA_Tx_Poll */
#include "sys_task.h"

#if (SYS_CFG_MC_ENABLE != 0U)
#include "mc_api.h"
#endif


/*-------------------------- 2. 变量 ---------------------------------*/
/* ---- 本机状态量（主从共用）---- */
static Q32U_ s_ack_cnt      = 0U;
static Q32U_ s_err_cnt      = 0U;
static Q32U_ s_target_rpm   = 0U;
static Q32U_ s_current_ma   = 0U;       /* 0.01A */
static Q32U_ s_vbus_0p1v    = 0U;
static Q32U_ s_error_code   = 0U;

/* ---- 接收状态机（主从共用）---- */
static Q08U_ s_rxbuf[PROTO_FRAME_LEN_MAX];
static Q32U_ s_rxlen = 0U;

/* ---- 本机地址（从机可被 PROTO_CMD_SET_ADDR 改）---- */
static Q08U_ s_local_addr = PROTO_DEV_ADDR;

#if (SYS_PROTO_MASTER_MODE != 0U) || (SYS_PROTO_SLAVE_REPORT_MODE != 0U)
/* ---- 上报节拍（主机上报 / 从机主动上报时才需要）---- */
static Q32U_ s_report_tick  = 0U;
#endif

#if (SYS_PROTO_MASTER_MODE != 0U)
/* ---- 主机侧轮询状态 ---- */
static Q32U_ s_poll_tick  = 0U;
static Q32U_ s_poll_index = 0U;
static Q32U_ s_reply_wait = 0U;         /* >0 = 正在等应答，单位 10ms 拍 */
static ST_PROTO_SLAVE_INFO s_slave[SYS_PROTO_SLAVE_NUM];
#endif


/*-------------------------- 3. 内部函数 --------------------------------*/
/* CRC16/MODBUS：初值 0xFFFF，多项式 0xA001（反射） */
static Q16U_ Sys_Proto_CRC16(const Q08U_* pData, Q32U_ len)
{
    Q16U_ crc = 0xFFFFU;
    Q32U_ i;
    Q08U_ j;

    for (i = 0U; i < len; i++)
    {
        crc ^= (Q16U_)pData[i];
        for (j = 0U; j < 8U; j++)
        {
            if ((crc & 0x0001U) != 0U)
            {
                crc = (Q16U_)((crc >> 1U) ^ 0xA001U);
            }
            else
            {
                crc >>= 1U;
            }
        }
    }
    return crc;
}

/* 打包一帧并交给发送缓冲：返回帧长，0 = 失败。addr 为帧内地址域 */
static Q32U_ Sys_Proto_Build(Q08U_ cmd, const Q08U_* pData, Q32U_ len, Q08U_ addr)
{
    static Q08U_ frame[PROTO_FRAME_LEN_MAX];
    Q16U_ crc;
    Q32U_ i;

    if (len > PROTO_DATA_MAX)
    {
        return 0U;
    }

    frame[0] = PROTO_HEAD;
    frame[1] = addr;
    frame[2] = cmd;
    frame[3] = (Q08U_)len;
    for (i = 0U; i < len; i++)
    {
        frame[4U + i] = pData[i];
    }

    crc = Sys_Proto_CRC16(&frame[1], 3U + len);         /* CRC 覆盖 ADDR~DATA */
    frame[4U + len] = (Q08U_)(crc & 0x00FFU);           /* 低字节先发 */
    frame[5U + len] = (Q08U_)((crc >> 8U) & 0x00FFU);
    frame[6U + len] = PROTO_TAIL;

    uart_send_data(frame, (Q16U_)(7U + len));
    return (7U + len);
}

#if (SYS_PROTO_MASTER_MODE != 0U)
/* 应答：CMD = 0x81，DATA[0] = 应答码，DATA[1..] = 数据（仅主机需要回 ACK）*/
static void Sys_Proto_SendAck(Q08U_ ack, const Q08U_* pData, Q32U_ len, Q08U_ dst_addr)
{
    Q08U_ buf[PROTO_DATA_MAX];

    if ((len + 1U) > PROTO_DATA_MAX)
    {
        return;
    }
    buf[0] = ack;
    if ((pData != NULL) && (len != 0U))
    {
        Q32U_ i;
        for (i = 0U; i < len; i++)
        {
            buf[1U + i] = pData[i];
        }
    }
    (void)Sys_Proto_Build((Q08U_)PROTO_RPT_ACK, buf, len + 1U, dst_addr);
}
#endif

/* 组状态数据域：状态(1) + 目标转速(2) + 相电流(2) + 母线(2) + 故障(4) = 11 字节
 * ★ 主机（上报上位机）与从机（应答点名）都要用，因此任何角色都编译；
 *   不设条件，避免"定义被裁掉、调用还在"导致的 L6218E。*/
static void Sys_Proto_MakeStateData(Q08U_* buf)
{
    buf[0]  = (Q08U_)((Systask.System_Flow == SYSTEM_STATE_RUN) ? 0x02U :
                      ((Systask.System_Flow == SYSTEM_STATE_ERROR) ? 0x03U : 0x01U));
    buf[1]  = (Q08U_)(s_target_rpm & 0xFFU);
    buf[2]  = (Q08U_)((s_target_rpm >> 8U) & 0xFFU);
    buf[3]  = (Q08U_)(s_current_ma & 0xFFU);
    buf[4]  = (Q08U_)((s_current_ma >> 8U) & 0xFFU);
    buf[5]  = (Q08U_)(s_vbus_0p1v & 0xFFU);
    buf[6]  = (Q08U_)((s_vbus_0p1v >> 8U) & 0xFFU);
    buf[7]  = (Q08U_)(s_error_code & 0xFFU);
    buf[8]  = (Q08U_)((s_error_code >> 8U) & 0xFFU);
    buf[9]  = (Q08U_)((s_error_code >> 16U) & 0xFFU);
    buf[10] = (Q08U_)((s_error_code >> 24U) & 0xFFU);
}

/* 状态上报：CMD = 0x80（只有主机上报 / 从机主动上报时才需要）*/
#if (SYS_PROTO_MASTER_MODE != 0U) || (SYS_PROTO_SLAVE_REPORT_MODE != 0U)
static void Sys_Proto_SendReport(Q08U_ addr)
{
    Q08U_ buf[PROTO_STATE_DATA_LEN];

    Sys_Proto_MakeStateData(buf);
    (void)Sys_Proto_Build((Q08U_)PROTO_RPT_STATE, buf, PROTO_STATE_DATA_LEN, addr);
}
#endif

#if (SYS_PROTO_MASTER_MODE != 0U)
/* 主机：点名并查询某台从机的状态 */
static void Sys_Proto_SendGetStateToSlave(Q08U_ slave_addr)
{
    (void)Sys_Proto_Build((Q08U_)PROTO_CMD_GET_STATE, NULL, 0U, slave_addr);
}

/* 主机：收到从机的上报/点名应答，记录到从机表并结束等待 */
static void Sys_Proto_OnSlaveReply(const Q08U_* pFrame, Q32U_ len)
{
    Q08U_ cmd  = pFrame[2];
    Q08U_ dlen = pFrame[3];
    Q08U_ src  = pFrame[1];
    Q32U_ k;
    Q32U_ idx = SYS_PROTO_SLAVE_NUM;        /* 先按地址找 */

    (void)len;

    if ((cmd != PROTO_RPT_STATE) && (cmd != PROTO_RPT_SLAVE))
    {
        return;
    }

    for (k = 0U; k < SYS_PROTO_SLAVE_NUM; k++)
    {
        if (s_slave[k].addr == src)
        {
            idx = k;
            break;
        }
    }
    if (idx >= SYS_PROTO_SLAVE_NUM)
    {
        idx = s_poll_index;                 /* 地址对不上时归到当前点名的那台 */
        if (idx >= SYS_PROTO_SLAVE_NUM)
        {
            return;
        }
    }

    for (k = 0U; (k < dlen) && (k < PROTO_STATE_DATA_LEN); k++)
    {
        s_slave[idx].last_rpt[k] = pFrame[4U + k];
    }
    s_slave[idx].state       = PROTO_SLAVE_ONLINE;
    s_slave[idx].timeout_cnt = 0U;
    s_reply_wait             = 0U;          /* 结束等待 */
    s_ack_cnt++;
}
#endif

/* 处理一帧完整数据 */
static void Sys_Proto_HandleFrame(const Q08U_* pFrame, Q32U_ len)
{
    Q08U_  cmd;
    Q08U_  data_len;
    Q16U_  crc_calc;
    Q16U_  crc_recv;
    Q08U_  ack = PROTO_ACK_OK;

    if (len < PROTO_FRAME_LEN_MIN)
    {
        s_err_cnt++;
        return;
    }
    if ((pFrame[0] != PROTO_HEAD) || (pFrame[len - 1U] != PROTO_TAIL))
    {
        s_err_cnt++;
        return;
    }

    data_len = pFrame[3];
    if ((Q32U_)(7U + data_len) != len)
    {
        s_err_cnt++;
        return;                             /* 长度不符：静默丢弃（不回，避免总线争用）*/
    }

#if (SYS_PROTO_MASTER_MODE != 0U)
    /* ---- 主机：只收"发给主机"或"广播"的帧；否则当作从机应答处理 ---- */
    if ((pFrame[1] != SYS_PROTO_MASTER_ADDR) && (pFrame[1] != 0x00U))
    {
        if (s_reply_wait == 0U)
        {
            return;                         /* 不是给我的，且我没在等应答 */
        }
        /* 从机应答也要校验 CRC 后才采信 */
        crc_calc = Sys_Proto_CRC16(&pFrame[1], 3U + data_len);
        crc_recv = (Q16U_)((Q16U_)pFrame[4U + data_len]
                           | ((Q16U_)pFrame[5U + data_len] << 8U));
        if (crc_calc != crc_recv)
        {
            s_err_cnt++;
            return;
        }
        Sys_Proto_OnSlaveReply(pFrame, len);
        return;
    }
    Q08U_  reply_addr;
    reply_addr = SYS_PROTO_MASTER_ADDR;
#else
    /* ---- 从机：只收"点名自己"或"广播"的帧，其余静默丢弃 ---- */
    if ((pFrame[1] != s_local_addr) && (pFrame[1] != 0x00U))
    {
        return;
    }
#if (SYS_PROTO_SLAVE_REPORT_MODE != 0U)
    /* 应答的目的地址：谁问我我就回给谁；广播则回给主机 */
    Q08U_  reply_addr;
    reply_addr = (Q08U_)((pFrame[1] == 0x00U) ? SYS_PROTO_MASTER_ADDR : pFrame[1]);
#endif
#endif
    
    crc_calc = Sys_Proto_CRC16(&pFrame[1], 3U + data_len);
    crc_recv = (Q16U_)((Q16U_)pFrame[4U + data_len]
                       | ((Q16U_)pFrame[5U + data_len] << 8U));
    if (crc_calc != crc_recv)
    {
        s_err_cnt++;
        return;
    }

    cmd = pFrame[2];

    switch (cmd)
    {
        case PROTO_CMD_STOP:
        {
            Systask.System_State_Flag.bit.system_runflag = 0U;
#if (SYS_PROTO_MASTER_MODE != 0U)
            Sys_Proto_SendAck(ack, NULL, 0U, reply_addr);
#endif
            break;
        }
        case PROTO_CMD_RUN:
        {
            Systask.System_State_Flag.bit.system_runflag = 1U;
#if (SYS_PROTO_MASTER_MODE != 0U)
            Sys_Proto_SendAck(ack, NULL, 0U, reply_addr);
#endif
            break;
        }
        case PROTO_CMD_SET_SPEED:
        {
            if (data_len < 2U)
            {
                ack = PROTO_ACK_LEN;
            }
            else
            {
                s_target_rpm = (Q32U_)((Q16U_)pFrame[4] | ((Q16U_)pFrame[5] << 8U));
#if (SYS_CFG_MC_ENABLE != 0U)
                MC_API_Motor_Set_Speed(HW_MC_MOTOR_NUMBER_N0, s_target_rpm);
#endif
            }
#if (SYS_PROTO_MASTER_MODE != 0U)
            Sys_Proto_SendAck(ack, NULL, 0U, reply_addr);
#endif
            break;
        }
        case PROTO_CMD_GET_STATE:
        {
#if (SYS_PROTO_MASTER_MODE != 0U)
            /* 主机被上位机查状态：回自己的状态 */
            Sys_Proto_SendReport(reply_addr);
#else
            /* 从机被点名：回点名应答（含自身状态数据）*/
            Q08U_ buf[PROTO_STATE_DATA_LEN];
            Sys_Proto_MakeStateData(buf);
            (void)Sys_Proto_Build((Q08U_)PROTO_RPT_SLAVE, buf, PROTO_STATE_DATA_LEN, s_local_addr);
#endif
            break;
        }
        case PROTO_CMD_GET_PARA:
        {
#if (SYS_PROTO_MASTER_MODE != 0U)
            Q08U_ buf[4];
#endif
            if (data_len < 1U)
            {
#if (SYS_PROTO_MASTER_MODE != 0U)
                Sys_Proto_SendAck(PROTO_ACK_LEN, NULL, 0U, reply_addr);
#endif
                break;
            }
#if (SYS_PROTO_MASTER_MODE != 0U)
            switch (pFrame[4])
            {
                case PROTO_PARA_SPEED:
                    buf[0] = (Q08U_)(s_target_rpm & 0xFFU);
                    buf[1] = (Q08U_)((s_target_rpm >> 8U) & 0xFFU);
                    Sys_Proto_SendAck(ack, buf, 2U, reply_addr);
                    break;
                case PROTO_PARA_CURRENT:
                    buf[0] = (Q08U_)(s_current_ma & 0xFFU);
                    buf[1] = (Q08U_)((s_current_ma >> 8U) & 0xFFU);
                    Sys_Proto_SendAck(ack, buf, 2U, reply_addr);
                    break;
                case PROTO_PARA_VBUS:
                    buf[0] = (Q08U_)(s_vbus_0p1v & 0xFFU);
                    buf[1] = (Q08U_)((s_vbus_0p1v >> 8U) & 0xFFU);
                    Sys_Proto_SendAck(ack, buf, 2U, reply_addr);
                    break;
                case PROTO_PARA_ERROR:
                    buf[0] = (Q08U_)(s_error_code & 0xFFU);
                    buf[1] = (Q08U_)((s_error_code >> 8U) & 0xFFU);
                    buf[2] = (Q08U_)((s_error_code >> 16U) & 0xFFU);
                    buf[3] = (Q08U_)((s_error_code >> 24U) & 0xFFU);
                    Sys_Proto_SendAck(ack, buf, 4U, reply_addr);
                    break;
                default:
                    Sys_Proto_SendAck(PROTO_ACK_RANGE, NULL, 0U, reply_addr);
                    break;
            }
#endif
            break;
        }
        case PROTO_CMD_SET_PARA:
        {
            if (data_len < 3U)
            {
                ack = PROTO_ACK_LEN;
            }
            else
            {
                Q16U_ val = (Q16U_)((Q16U_)pFrame[5] | ((Q16U_)pFrame[6] << 8U));
                if (pFrame[4] == PROTO_PARA_SPEED)
                {
                    s_target_rpm = val;
#if (SYS_CFG_MC_ENABLE != 0U)
                    MC_API_Motor_Set_Speed(HW_MC_MOTOR_NUMBER_N0, s_target_rpm);
#endif
                }
                else
                {
                    ack = PROTO_ACK_RANGE;
                }
            }
#if (SYS_PROTO_MASTER_MODE != 0U)
            Sys_Proto_SendAck(ack, NULL, 0U, reply_addr);
#else
            (void)ack;
#endif
            break;
        }
        case PROTO_CMD_HEARTBEAT:
        {
#if (SYS_PROTO_MASTER_MODE != 0U)
            Sys_Proto_SendAck(ack, NULL, 0U, reply_addr);
#else
            (void)ack;
#endif
            break;
        }

        /* ★ 从机专有：改本机地址（掉电丢失）*/
        case PROTO_CMD_SET_ADDR:
        {
#if (SYS_PROTO_SLAVE_MODE != 0U)
            if (data_len < 1U)
            {
                ack = PROTO_ACK_LEN;
            }
            else if ((pFrame[4] == 0x00U) || (pFrame[4] >= 0xF0U))
            {
                ack = PROTO_ACK_RANGE;              /* 0x00 广播、0xF0~0xFF 主机段保留 */
            }
            else
            {
                s_local_addr = pFrame[4];           /* 运行期生效，掉电丢失 */
                ack = PROTO_ACK_OK;
            }
#endif
            (void)ack;
            break;
        }

        /* ★ 主机专有：点名从机 */
        case PROTO_CMD_POLL:
        {
#if (SYS_PROTO_MASTER_MODE != 0U)
            Q08U_ target = (data_len >= 1U) ? pFrame[4] : 0xFFU;
            Q32U_ k;
            for (k = 0U; k < SYS_PROTO_SLAVE_NUM; k++)
            {
                if (s_slave[k].addr == target)
                {
                    s_poll_index = k;
                    s_reply_wait = SYS_PROTO_REPLY_TIMEOUT_MS / 10U;
                    s_slave[k].timeout_cnt++;
                    Sys_Proto_SendGetStateToSlave(target);
                    break;
                }
            }
            Sys_Proto_SendAck(PROTO_ACK_OK, NULL, 0U, reply_addr);
#endif
            break;
        }

        /* ★ 运行期改主从：当前版本统一拒绝（改 hw_fun.h 重新编译）*/
        case PROTO_CMD_SET_MODE:
        {
#if (SYS_PROTO_MASTER_MODE != 0U)
            Sys_Proto_SendAck(PROTO_ACK_RANGE, NULL, 0U, reply_addr);
#else
            (void)ack;
#endif
            break;
        }

        default:
        {
            s_err_cnt++;
#if (SYS_PROTO_MASTER_MODE != 0U)
            Sys_Proto_SendAck(PROTO_ACK_CMD, NULL, 0U, reply_addr);
#endif
            break;
        }
    }

    if (ack == PROTO_ACK_OK)
    {
        s_ack_cnt++;
    }
}


/*-------------------------- 4. 公有接口实现 -----------------------------*/
void Sys_Proto_Init(void)
{
    s_ack_cnt     = 0U;
    s_err_cnt     = 0U;
    s_target_rpm  = 0U;
    s_current_ma  = 0U;
    s_vbus_0p1v   = 0U;
    s_error_code  = 0U;

    s_rxlen       = 0U;
    s_local_addr  = PROTO_DEV_ADDR;

#if (SYS_PROTO_MASTER_MODE != 0U) || (SYS_PROTO_SLAVE_REPORT_MODE != 0U)
    s_report_tick = 0U;
#endif

#if (SYS_PROTO_MASTER_MODE != 0U)
    {
        Q32U_ k;
        Q32U_ j;

        s_poll_tick   = 0U;
        s_poll_index  = 0U;
        s_reply_wait  = 0U;

        for (k = 0U; k < SYS_PROTO_SLAVE_NUM; k++)
        {
            s_slave[k].addr        = (Q08U_)(k + 1U);   /* 默认从机地址 1,2,3... */
            s_slave[k].state       = PROTO_SLAVE_OFFLINE;
            s_slave[k].timeout_cnt = 3U;                /* 上电即视为离线，等首次应答 */
            for (j = 0U; j < PROTO_STATE_DATA_LEN; j++)
            {
                s_slave[k].last_rpt[j] = 0U;
            }
        }
    }
#endif
}

void Sys_Proto_Loop_10ms(void)
{
    int   byte;
    Q32U_ avail;
    Q32U_ i;

    /* ---- 1. 把环形缓冲区里的字节逐个喂进状态机 ---- */
    avail = (Q32U_)ring_buffer_available();
    for (i = 0U; i < avail; i++)
    {
        byte = ring_buffer_get();
        if (byte < 0)
        {
            break;
        }

        if (s_rxlen == 0U)
        {
            if ((Q08U_)byte == PROTO_HEAD)
            {
                s_rxbuf[s_rxlen++] = (Q08U_)byte;
            }
            continue;                       /* 未同步到帧头前全部丢弃 */
        }

        s_rxbuf[s_rxlen++] = (Q08U_)byte;

        if (s_rxlen >= PROTO_FRAME_LEN_MAX)
        {
            s_rxlen = 0U;                   /* 超长保护，重新找帧头 */
            continue;
        }
        if (s_rxlen >= PROTO_FRAME_LEN_MIN)
        {
            if ((s_rxbuf[s_rxlen - 1U] == PROTO_TAIL)
             && ((Q32U_)(7U + s_rxbuf[3]) == s_rxlen))
            {
                Sys_Proto_HandleFrame(s_rxbuf, s_rxlen);
                s_rxlen = 0U;
            }
        }
    }

    /* ---- 2. 采集本机状态量 ---- */
#if (SYS_CFG_MC_ENABLE != 0U)
    s_current_ma = MC_API_Motor_Read_Iphase(HW_MC_MOTOR_NUMBER_N0);
    s_error_code = MC_API_Motor_Read_Err(HW_MC_MOTOR_NUMBER_N0);
    s_target_rpm = MC_API_Motor_Read_Speed(HW_MC_MOTOR_NUMBER_N0);
#endif
    s_vbus_0p1v  = 0U;      /* 需要母线电压时改接 BSP 采样或 MC_API_Motor_Read_Ibus */

#if (SYS_PROTO_MASTER_MODE != 0U)
    /* ---- 3M. 主机：应答超时处理 ---- */
    if (s_reply_wait > 0U)
    {
        s_reply_wait--;
        if ((s_reply_wait == 0U) && (s_poll_index < SYS_PROTO_SLAVE_NUM))
        {
            if (s_slave[s_poll_index].timeout_cnt >= 3U)
            {
                s_slave[s_poll_index].state = PROTO_SLAVE_OFFLINE;
            }
        }
    }

    /* ---- 4M. 主机：周期轮询从机 ---- */
    s_poll_tick += 10U;
    if ((s_poll_tick >= SYS_PROTO_POLL_PERIOD_MS) && (s_reply_wait == 0U)
        && (g_uart_tx_busy == 0U))
    {
        s_poll_tick = 0U;
        if (SYS_PROTO_SLAVE_NUM > 1U)
        {
            s_poll_index = (s_poll_index + 1U) % SYS_PROTO_SLAVE_NUM;   /* 多机轮流 */
        }
        else
        {
            s_poll_index = 0U;
        }
        s_reply_wait = SYS_PROTO_REPLY_TIMEOUT_MS / 10U;
        s_slave[s_poll_index].timeout_cnt++;
        Sys_Proto_SendGetStateToSlave(s_slave[s_poll_index].addr);
    }

    /* ---- 5M. 主机：把自己的汇总状态上报上位机 ---- */
    s_report_tick += 10U;
    if (s_report_tick >= PROTO_REPORT_PERIOD_MS)
    {
        s_report_tick = 0U;
        Sys_Proto_SendReport(SYS_PROTO_MASTER_ADDR);
    }
#endif

#if (SYS_PROTO_SLAVE_REPORT_MODE != 0U)
    /* ---- 3S. 从机：允许主动上报时按周期发 ---- */
    s_report_tick += 10U;
    if (s_report_tick >= PROTO_REPORT_PERIOD_MS)
    {
        s_report_tick = 0U;
        Sys_Proto_SendReport(SYS_PROTO_MASTER_ADDR);
    }
#endif

    /* ---- 6. 启动发送（从机收到就立即回，抢主机应答窗口）---- */
    UART_DMA_Tx_Poll();
}

void Sys_Proto_SetLocalAddr(Q08U_ addr)
{
    if ((addr != 0x00U) && (addr < 0xF0U))
    {
        s_local_addr = addr;
    }
}

Q08U_ Sys_Proto_GetLocalAddr(void)
{
    return s_local_addr;
}

#if (SYS_PROTO_MASTER_MODE != 0U)
Q32U_ Sys_Proto_GetSlaveNum(void)
{
    return (Q32U_)SYS_PROTO_SLAVE_NUM;
}

const ST_PROTO_SLAVE_INFO* Sys_Proto_GetSlaveInfo(Q32U_ index)
{
    if (index >= SYS_PROTO_SLAVE_NUM)
    {
        return NULL;
    }
    return &s_slave[index];
}

void Sys_Proto_SendToSlave(Q08U_ slave_addr, Q08U_ cmd, const Q08U_* pData, Q32U_ len)
{
    (void)Sys_Proto_Build(cmd, pData, len, slave_addr);
}
#endif

Q32U_ Sys_Proto_GetAckCnt(void) { return s_ack_cnt; }
Q32U_ Sys_Proto_GetErrCnt(void) { return s_err_cnt; }
