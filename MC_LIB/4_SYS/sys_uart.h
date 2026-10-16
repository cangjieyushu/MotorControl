/* ==== SOURCE: 4_SYS\sys_uart.h ==== */
/*
*     File Name :                        sys_uart
*     Library/Module Name :              sys
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             上位机通讯协议（自有协议）
*
*     角色说明：
*       主机(MASTER)：主动轮询从机，并把汇总结果上报上位机
*       从机(SLAVE) ：只应答被点名的帧，默认不主动占用总线
*     角色与地址在 2_HW\..\20_hw\hw_fun.h 中配置（SYS_PROTO_ROLE / SYS_PROTO_SLAVE_ADDR）
*
*     条件编译约定：
*       本模块按角色裁剪代码，主机专属 / 从机专属的变量、函数、结构体全部用
*       SYS_PROTO_MASTER_MODE / SYS_PROTO_SLAVE_MODE 包起来，保证任一种角色编译都
*       不产生 "declared but never referenced" / "set but never used" 警告。
*/

#ifndef SYS_UART_H
#define SYS_UART_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "hw_map.h"
#include "hw_fun.h"         /* 主从机配置 SYS_PROTO_ROLE / SYS_PROTO_*_ADDR 在这里 */


/*-------------------------- 2. 宏定义 -----------------------------------*/
/* ---- 角色派生宏（全模块统一用它做条件编译）---- */
#if (SYS_PROTO_ROLE == SYS_PROTO_ROLE_MASTER)
    #define SYS_PROTO_MASTER_MODE       (1U)
    #define SYS_PROTO_SLAVE_MODE        (0U)
#else
    #define SYS_PROTO_MASTER_MODE       (0U)
    #define SYS_PROTO_SLAVE_MODE        (1U)
#endif

/* 从机是否允许主动上报（多机共总线建议 0）*/
#if (SYS_PROTO_SLAVE_MODE != 0U) && (SYS_PROTO_SLAVE_AUTO_REPORT != 0U)
    #define SYS_PROTO_SLAVE_REPORT_MODE (1U)
#else
    #define SYS_PROTO_SLAVE_REPORT_MODE (0U)
#endif

/* 参数合法性检查：从机数量为 0 会产生零长数组 */
#if (SYS_PROTO_SLAVE_NUM < 1U)
    #error "SYS_PROTO_SLAVE_NUM 必须 >= 1"
#endif

/* ---- 帧格式 ---- */
#define PROTO_HEAD                  (0xAAU)     /* 帧头 */
#define PROTO_TAIL                  (0x55U)     /* 帧尾 */
#define PROTO_DATA_MAX              (32U)       /* 数据域最大字节数 */
#define PROTO_FRAME_LEN_MIN         (8U)        /* 最小帧长 = 头+地址+命令+长度+CRC16+尾 */
#define PROTO_FRAME_LEN_MAX         (PROTO_FRAME_LEN_MIN + PROTO_DATA_MAX)

/* ---- 状态上报数据域长度 ---- */
#define PROTO_STATE_DATA_LEN        (11U)       /* 状态1 + 转速2 + 相电流2 + 母线2 + 故障4 */

/* ---- 从机主动上报间隔（仅 SYS_PROTO_SLAVE_REPORT_MODE != 0 时生效）---- */
#define PROTO_REPORT_PERIOD_MS      (100U)

/* ---- 本机设备地址（由 hw_fun.h 的角色决定）---- */
#define PROTO_DEV_ADDR              ((SYS_PROTO_ROLE == SYS_PROTO_ROLE_MASTER) \
                                     ? (SYS_PROTO_MASTER_ADDR) : (SYS_PROTO_SLAVE_ADDR))


/*-------------------------- 3. 枚举/结构体 ------------------------------*/
/* ---- 应答码 ---- */
typedef enum{
    PROTO_ACK_OK        = 0x00U,    /* 成功 */
    PROTO_ACK_CRC       = 0x01U,    /* CRC 校验错 */
    PROTO_ACK_LEN       = 0x02U,    /* 长度错 */
    PROTO_ACK_CMD       = 0x03U,    /* 未知命令 */
    PROTO_ACK_RANGE     = 0x04U,    /* 参数越界 */
    PROTO_ACK_BUSY      = 0x05U,    /* 忙 */
}EM_PROTO_ACK;

/* ---- 命令码 ---- */
typedef enum{
    PROTO_CMD_STOP      = 0x01U,    /* 停机（无数据） */
    PROTO_CMD_RUN       = 0x02U,    /* 启动（无数据） */
    PROTO_CMD_SET_SPEED = 0x03U,    /* 设定转速：DATA[0..1] = rpm，小端 */
    PROTO_CMD_GET_STATE = 0x04U,    /* 查询状态（无数据） */
    PROTO_CMD_GET_PARA  = 0x05U,    /* 读参数：DATA[0] = 参数编号 */
    PROTO_CMD_SET_PARA  = 0x06U,    /* 写参数：DATA[0] = 参数编号，DATA[1..2] = 值，小端 */
    PROTO_CMD_HEARTBEAT = 0x07U,    /* 心跳（无数据） */
    PROTO_CMD_SET_ADDR  = 0x08U,    /* 改本机地址：DATA[0] = 新地址（仅从机）*/
    PROTO_CMD_POLL      = 0x09U,    /* 主机点名从机：DATA[0] = 目标从机地址 */
    PROTO_CMD_SET_MODE  = 0x0AU,    /* 运行期改主从：当前版本拒绝（改 hw_fun.h 重新编译）*/
}EM_PROTO_CMD;

/* ---- 上报/应答码 ---- */
typedef enum{
    PROTO_RPT_STATE     = 0x80U,    /* 状态上报（从机→主机，或主机→上位机）*/
    PROTO_RPT_ACK       = 0x81U,    /* 命令应答 */
    PROTO_RPT_SLAVE     = 0x82U,    /* 从机应答点名 */
}EM_PROTO_RPT;

/* ---- 参数编号 ---- */
typedef enum{
    PROTO_PARA_SPEED    = 0x01U,    /* 目标转速 rpm */
    PROTO_PARA_CURRENT  = 0x02U,    /* 相电流 0.01A */
    PROTO_PARA_VBUS     = 0x03U,    /* 母线电压 0.1V */
    PROTO_PARA_ERROR    = 0x04U,    /* 故障码 */
}EM_PROTO_PARA;

/* ---- 从机在线状态 ---- */
typedef enum{
    PROTO_SLAVE_OFFLINE = 0x00U,    /* 未应答 / 超时 */
    PROTO_SLAVE_ONLINE  = 0x01U,    /* 通讯正常 */
}EM_PROTO_SLAVE_STATE;

#if (SYS_PROTO_MASTER_MODE != 0U)
/* ---- 主机侧：一台从机的信息（仅主机编译）---- */
typedef struct{
    Q08U_  addr;                        /* 从机地址 */
    Q08U_  state;                       /* EM_PROTO_SLAVE_STATE */
    Q32U_  timeout_cnt;                 /* 连续超时次数，>=3 判离线 */
    Q08U_  last_rpt[PROTO_STATE_DATA_LEN];  /* 最近一次上报的 DATA 域 */
}ST_PROTO_SLAVE_INFO;
#endif


/*-------------------------- 4. 内联接口（编译期常量，放头文件避免未使用告警）----*/
/*
Function: Sys_Proto_IsMaster
Description: 查询本机角色（编译期常量，会被优化成立即数）
Return: 1 = 主机，0 = 从机
*/
static inline Q08U_ Sys_Proto_IsMaster(void)
{
    return (Q08U_)SYS_PROTO_MASTER_MODE;
}


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/* ---- 通用：主从机都要用 ---- */
void  Sys_Proto_Init(void);
void  Sys_Proto_Loop_10ms(void);                    /* 10ms 任务中调用 */
void  Sys_Proto_SetLocalAddr(Q08U_ addr);           /* 改本机地址（运行期生效）*/
Q08U_ Sys_Proto_GetLocalAddr(void);

/* ---- 调试统计 ---- */
Q32U_ Sys_Proto_GetAckCnt(void);                    /* 已完成的有效交互数 */
Q32U_ Sys_Proto_GetErrCnt(void);                    /* 校验/长度错误数 */

#if (SYS_PROTO_MASTER_MODE != 0U)
/* ---- 主机专属：从机表访问 + 主动下发 ---- */
Q32U_                      Sys_Proto_GetSlaveNum(void);
const ST_PROTO_SLAVE_INFO* Sys_Proto_GetSlaveInfo(Q32U_ index);
void  Sys_Proto_SendToSlave(Q08U_ slave_addr, Q08U_ cmd, const Q08U_* pData, Q32U_ len);
#endif


#endif /* SYS_UART_H */
