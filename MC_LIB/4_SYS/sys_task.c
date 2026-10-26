/**
 * @file    sys_task.c
 * @brief   系统状态与任务调度
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "bsp.h"
#include "sys_task.h"

#if (HW_FUN_MC_ENABLE != 0U)
#include "mc_api.h"
#endif

#if (HW_FUN_BTN_ENABLE != 0U)
#include "sys_btn.h"
#endif

#if (HW_FUN_ERR_ENABLE != 0U)
#include "sys_err.h"
#endif

#if (HW_FUN_UART_ENABLE != 0U)
#include "sys_uart.h"
#endif

#if (HW_FUN_LCD_ENABLE != 0U)
#include "sys_lcd.h"
#include "sys_font.h"
#include "sys_menu.h"
#endif

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */
ST_SYSTEM_TASK Systask = {
    .P_Q32U_System_PowerUp_Time = SYSTEM_POWERUP_TIME,

    .FL_VR.P_Q14I_LPF_Coeff  = 2000,
    .FL_VBG.P_Q14I_LPF_Coeff = 2000,
};

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  ADC 采样 + VR 低通滤波
 */
static void Systask_AdcRead(void)
{
    Q32U_ adc_tmp = 0U;

    adc_tmp = BSP_MC_ADC_DATA_READ_VR;              /* VR 采样值（ADC）*/
    Systask.FL_VR.I_Q14I_LPF_In = (Q32I_)adc_tmp;

    LPF_Cal_T(&Systask.FL_VR);
}

/**
 * @brief  SysTick 节拍处理（1ms 调用）
 */
static void Systask_TickIsr(void)
{
    Systask.systick_10ms_count++;

    if (Systask.systick_10ms_count >= 10U)
    {
        Systask.systick_10ms_count = 0U;

        if (Systask.System_State_Flag.bit.systick_intflow == 0U)
        {
            Systask.System_State_Flag.bit.systick_intflow = 1U;
        }
        else
        {
            Systask.System_Error_Flag.bit.systick_overflow = 1U;
        }
    }
}

/**
 * @brief  系统状态机
 */
static void Systask_StateMachine(void)
{
    switch (Systask.System_Flow)
    {
        case SYSTEM_STATE_POWERUP:
        {
            Systask.V_flow_cnt++;
            if (Systask.V_flow_cnt >= Systask.P_Q32U_System_PowerUp_Time)
            {
                Systask.V_flow_cnt = 0U;

                /* 上电稳定完成：初始化滤波器 */
                {
                    Q32U_ adc_tmp = BSP_MC_ADC_DATA_READ_VR;
                    LPF_Init_T(&Systask.FL_VR, (Q32I_)adc_tmp);
                }

                Systask.System_Flow = SYSTEM_STATE_IDLE;
            }
            break;
        }
        case SYSTEM_STATE_IDLE:
        {
            if (Systask.System_Error_Flag.all != 0U)
            {
                Systask.System_Flow = SYSTEM_STATE_ERROR;
            }
            else
            {
                if (Systask.System_State_Flag.bit.system_runflag == 1U)
                {
                    Systask.System_Flow = SYSTEM_STATE_RUN;
                }
            }
            break;
        }
        case SYSTEM_STATE_RUN:
        {
            if (Systask.System_Error_Flag.all != 0U)
            {
                Systask.System_Flow = SYSTEM_STATE_ERROR;
            }
            else
            {
                if (Systask.System_State_Flag.bit.system_runflag == 0U)
                {
                    Systask.System_Flow = SYSTEM_STATE_IDLE;
                }
            }
            break;
        }
        case SYSTEM_STATE_ERROR:
        {
            if (Systask.System_State_Flag.bit.system_runflag == 0U)
            {
                Systask.System_Error_Flag.all = 0U;
#if (HW_FUN_MC_ENABLE != 0U)
                MC_API_Motor_Clear_Err(HW_FUN_MC_MOTOR_NUMBER_N0);
#endif
                Systask.System_Flow = SYSTEM_STATE_IDLE;
            }
            break;
        }
        default: break;
    }
}

/**
 * @brief  系统初始化（临界区内）
 */
void Systask_Init_Flow(void)
{
    /* ---- 1. 系统级（永远初始化） ---- */
    BSP_SYS_Init();

    /* ---- 2. 电机控制 ---- */
#if (HW_FUN_MC_ENABLE != 0U)
    BSP_MC_Init();
#endif

    /* ---- 3. UI 分区：LCD 底层 ---- */
#if (HW_FUN_LCD_ENABLE != 0U)
    BSP_LCD_Init();     /* GPIO / SPI / DMA */
#endif
}

/**
 * @brief  系统初始化完成（开中断后调用）
 */
void Systask_Init_Flow_Finish(void)
{
    /* ---- 3. UI 分区：LCD + 字模 + 菜单 ---- */
#if (HW_FUN_LCD_ENABLE != 0U)
    lcd_init();         /* ST7796 寄存器 + 清屏 */
    Menu_Init();        /* 菜单状态初始化 */
#endif
}

/**
 * @brief  1ms 任务
 */
void Systask_1ms_Flow(void)
{
    Systask_AdcRead();

#if (HW_FUN_MC_ENABLE != 0U)
    /* ---- 检测电机错误 ---- */
    if (MC_API_Motor_Read_Err(HW_FUN_MC_MOTOR_NUMBER_N0) != 0U)
    {
        Systask.System_Error_Flag.bit.motor_error = 1U;
    }
#endif

    /* ---- 系统状态机 ---- */
    Systask_StateMachine();

#if (HW_FUN_MC_ENABLE != 0U)
    /* ---- 根据状态控制电机启停 ---- */
    if (Systask.System_Flow == SYSTEM_STATE_RUN)
    {
        MC_API_Motor_StartStop(HW_FUN_MC_MOTOR_NUMBER_N0, 1U);
    }
    else
    {
        MC_API_Motor_StartStop(HW_FUN_MC_MOTOR_NUMBER_N0, 0U);
    }
#endif

    Systask_TickIsr();
}

/**
 * @brief  10ms 任务
 */
void Systask_10ms_Flow(void)
{
    if (Systask.System_State_Flag.bit.systick_intflow == 1U)
    {
        /* ---- 4. 电机控制 + 状态回读 ---- */
#if (HW_FUN_MC_ENABLE != 0U)
        MC_API_Motor_Set_Dir(HW_FUN_MC_MOTOR_NUMBER_N0, Systask.Dir_Target);
        MC_API_Motor_Set_Speed(HW_FUN_MC_MOTOR_NUMBER_N0, Systask.Speed_rpm_Target);

        Systask.Speed_rpm    = MC_API_Motor_Read_Speed (HW_FUN_MC_MOTOR_NUMBER_N0);
        Systask.Iphase_0p01A = MC_API_Motor_Read_Iphase(HW_FUN_MC_MOTOR_NUMBER_N0);
        Systask.IBus_0p01A   = MC_API_Motor_Read_Ibus  (HW_FUN_MC_MOTOR_NUMBER_N0);
#endif

        /* ---- 1. 按键 / VR 控制 ---- */
#if (HW_FUN_BTN_ENABLE != 0U)
        Button_Control(&Button_Ctrl);
#endif

#if (HW_FUN_ERR_ENABLE != 0U)
        Systask.V_Q32U_Error_Code = Error_Priority_Check(MC_API_Motor_Read_Err(HW_FUN_MC_MOTOR_NUMBER_N0));
#endif

        /* ---- 3. 上位机串口收发 ---- */
#if (HW_FUN_UART_ENABLE != 0U)
        Uart_Rx_Poll_10ms();        /* 轮询搬运 DMA → ring buf */
        Hmi_Uart_Read_Process();    /* 从 ring buf 取字节拼帧 */
        Hmi_Uart_Tx_Process();      /* TX 状态机 */
#endif

        /* ---- 2. UI 分区：菜单 10ms 周期任务 ---- */
#if (HW_FUN_LCD_ENABLE != 0U)
        Menu_Loop_10ms();
#endif

        Systask.System_State_Flag.bit.systick_intflow = 0U;
    }
}
