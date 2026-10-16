/*
*     File Name :                        sys_task
*     Library/Module Name :              sys
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             系统状态与任务调度
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp.h"
#include "sys_task.h"

#if (SYS_CFG_MC_ENABLE != 0U)
#include "mc_api.h"
#endif

#if (SYS_CFG_BTN_ENABLE != 0U)
#include "sys_btn.h"
#endif

#if (SYS_CFG_ERR_ENABLE != 0U)
#include "sys_err.h"
#endif

#if (SYS_CFG_UART_ENABLE != 0U)
#include "sys_uart.h"
#endif

#if (SYS_CFG_LCD_ENABLE != 0U)
#include "sys_lcd.h"
#include "sys_font.h"
#include "sys_menu.h"
#endif


/*-------------------------- 2. 变量 ---------------------------------*/
ST_SYSTEM_TASK Systask = {
    .P_Q32U_System_PowerUp_Time = SYSTEM_POWERUP_TIME,

    .FL_VR.P_Q14I_LPF_Coeff = 2000,
    .FL_VBG.P_Q14I_LPF_Coeff = 2000,
};


/*-------------------------- 3. 内部辅助函数 ----------------------------*/
/*
Function: Systask_AdcRead
Description: 读取 VR 采样值，送入滤波器
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
static void Systask_AdcRead(void)
{
    Q32U_ adc_tmp = 0U;

    adc_tmp = BSP_MC_ADC_DATA_READ_VR;              /* VR 采样值（ADC）*/
    Systask.FL_VR.I_Q14I_LPF_In = (Q32I_)adc_tmp;

    LPF_Cal_T(&Systask.FL_VR);
}

/*
Function: Systask_TickIsr
Description: 1ms 计数器：每 10ms 置 systick_intflow 标志
             若上次标志未被清除，则置 systick_overflow 错误
Input: 无
Output: 无
Return: 无
Author: CJYS
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

/*
Function: Systask_StateMachine
Description: 系统状态机：POWERUP → IDLE ? RUN ? ERROR
Input: 无
Output: 无
Return: 无
Author: CJYS
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
#if (SYS_CFG_MC_ENABLE != 0U)
                MC_API_Motor_Clear_Err(HW_MC_MOTOR_NUMBER_N0);
#endif
                Systask.System_Flow = SYSTEM_STATE_IDLE;
            }
            break;
        }
        default: break;
    }
}


/*-------------------------- 4. 公有接口实现 -----------------------------*/
/*
Function: Systask_Init_Flow
Description: 系统初始化（上电时调用一次）
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void Systask_Init_Flow(void)
{
    /* ---- 1. 系统级（永远初始化） ---- */
    BSP_SYS_Init();

    /* ---- 2. 电机控制 ---- */
#if (SYS_CFG_MC_ENABLE != 0U)
    BSP_MC_Init();
#endif

    /* ---- 3. UI 分区：LCD + 字模 + 菜单 ---- */
#if (SYS_CFG_LCD_ENABLE != 0U)
    BSP_LCD_Init();     /* GPIO / SPI / DMA */
#endif
    
}

/*
Function: Systask_Init_Flow_Finish
Description: 系统初始化（上电时调用一次）
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void Systask_Init_Flow_Finish(void)
{
    /* ---- 3. UI 分区：LCD + 字模 + 菜单 ---- */
#if (SYS_CFG_LCD_ENABLE != 0U)
    lcd_init();         /* ST7796 寄存器 + 清屏 */
    Menu_Init();        /* 菜单状态初始化 */
#endif

    /* ---- 4. 上位机串口 ---- */
#if (SYS_CFG_UART_ENABLE != 0U)
    Sys_Proto_Init();               /* ★ 新增 */
#endif
}

/*
Function: Systask_1ms_Flow
Description: 1ms 时间片任务调度（SysTick 中断中调用）
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void Systask_1ms_Flow(void)
{
    Systask_AdcRead();

#if (SYS_CFG_MC_ENABLE != 0U)
    /* ---- 检测电机错误 ---- */
    if (MC_API_Motor_Read_Err(HW_MC_MOTOR_NUMBER_N0) != 0U)
    {
        Systask.System_Error_Flag.bit.motor_error = 1U;
    }
#endif

    /* ---- 系统状态机 ---- */
    Systask_StateMachine();

#if (SYS_CFG_MC_ENABLE != 0U)
    /* ---- 根据状态控制电机启停 ---- */
    if (Systask.System_Flow == SYSTEM_STATE_RUN)
    {
        MC_API_Motor_StartStop(HW_MC_MOTOR_NUMBER_N0, 1U);
    }
    else
    {
        MC_API_Motor_StartStop(HW_MC_MOTOR_NUMBER_N0, 0U);
    }
#endif

    Systask_TickIsr();
}

/*
Function: Systask_10ms_Flow
Description: 10ms 时间片任务调度（主循环中轮询）
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void Systask_10ms_Flow(void)
{
    if (Systask.System_State_Flag.bit.systick_intflow == 1U)
    {
        /* ---- 1. 按键 / VR 控制 ---- */
#if (SYS_CFG_BTN_ENABLE != 0U)
        Button_Control(&Button_Ctrl);
#endif

        /* ---- 2. UI 分区：菜单 10ms 周期任务 ---- */
#if (SYS_CFG_LCD_ENABLE != 0U)
        Menu_Loop_10ms();
#endif

        /* ---- 3. 上位机串口收发 ---- */
#if (SYS_CFG_UART_ENABLE != 0U)
        Sys_Proto_Loop_10ms();          /* ★ 取代 UART_Get_Resceive_Data / UART_Send_Transmission_Data */
#endif

        /* ---- 4. 电机控制 + 状态回读 ---- */
#if (SYS_CFG_MC_ENABLE != 0U)
        MC_API_Motor_Set_Dir(HW_MC_MOTOR_NUMBER_N0, 1U);
        MC_API_Motor_Set_Speed(HW_MC_MOTOR_NUMBER_N0, Systask.Q16U_Duty_Target * 3000 / 16384);

        Systask.Speed_rpm    = MC_API_Motor_Read_Speed (HW_MC_MOTOR_NUMBER_N0);
        Systask.Iphase_0p01A = MC_API_Motor_Read_Iphase(HW_MC_MOTOR_NUMBER_N0);
        Systask.IBus_0p01A   = MC_API_Motor_Read_Ibus  (HW_MC_MOTOR_NUMBER_N0);

#if (SYS_CFG_ERR_ENABLE != 0U)
        Systask.V_Q32U_Error_Code = Error_Priority_Check(MC_API_Motor_Read_Err(HW_MC_MOTOR_NUMBER_N0));
#endif
#endif

        Systask.System_State_Flag.bit.systick_intflow = 0U;
    }
}
