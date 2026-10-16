/*
*     File Name :                        sys_task
*     Library/Module Name :              sys
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             系统状态与任务调度
*/


#ifndef SYSTASK_H
#define SYSTASK_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "math_filter_t.h"
#include "hw_fun.h"

#if (SYS_CFG_UART_ENABLE != 0U)
#include "hal_uart.h"
#endif

#if (SYS_CFG_LCD_ENABLE != 0U)
#include "hal_lcd.h"
#endif

#if (SYS_CFG_MC_ENABLE != 0U)
#if(HW_MC_MOTOR_CONTROL_MODE == HW_MC_MOTOR_CONTROL_FOC_F)
#include "mcfoc_task_f.h"
#define MCFOC_Current_Flow      MCFOC_Current_Flow_F
#define MCFOC_Speed_Flow        MCFOC_Speed_Flow_F

#elif(HW_MC_MOTOR_CONTROL_MODE == HW_MC_MOTOR_CONTROL_FOC_T)
#include "mcfoc_task_t.h"
#define MCFOC_Current_Flow      MCFOC_Current_Flow_T
#define MCFOC_Speed_Flow        MCFOC_Speed_Flow_T

#elif(HW_MC_MOTOR_CONTROL_MODE == HW_MC_MOTOR_CONTROL_SQ)
#include "mcsq_task.h"

#endif
#endif


/*-------------------------- 2. 宏定义 -----------------------------------*/
#define SYSTEM_POWERUP_TIME               (1000U)           //ms，上电时间


/*-------------------------- 3. 枚举/结构体 ------------------------------*/
typedef enum{
    SYSTEM_STATE_POWERUP,
    SYSTEM_STATE_IDLE,
    SYSTEM_STATE_RUN,
    SYSTEM_STATE_ERROR,
}EM_SYSTEM_STATE_FLOW;

typedef union{
    SC_ALL all;
    struct{
        SC_BIT        systick_intflow           :1;
        SC_BIT        system_runflag            :1;
        SC_BIT        motor_enable              :1;
        SC_BIT        value_enable              :1;
    }bit;
}UN_SYSTEM_STATE_FLAG;

typedef union{
    SC_ALL all;
    struct{
        SC_BIT motor_error                     :1;
        SC_BIT systick_overflow                :1;
        SC_BIT USART_1_error                   :1;
        SC_BIT USART_2_error                   :1;
    }bit;
}UN_SYSTEM_ERROR_FLAG;

typedef struct{
    Q08U_                       systick_10ms_count;

    EM_SYSTEM_STATE_FLOW        System_Flow;
    UN_SYSTEM_STATE_FLAG        System_State_Flag;
    UN_SYSTEM_ERROR_FLAG        System_Error_Flag;

    ST_LPF_T                    FL_VR;
    ST_LPF_T                    FL_VBG;

    Q32U_                       Q16U_Duty_Target;
    Q32I_                       Speed_rpm;
    Q32I_                       Iphase_0p01A;
    Q32I_                       IBus_0p01A;

    Q32U_                       V_Q32U_Error_Code;

    Q32U_                       P_Q32U_System_PowerUp_Time;
    Q32U_                       V_flow_cnt;
}ST_SYSTEM_TASK;


/*-------------------------- 4. 外部全局变量声明 --------------------------*/
extern ST_SYSTEM_TASK  Systask;


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: Systask_Init_Flow
Description: 系统初始化（上电时调用一次）
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void Systask_Init_Flow(void);

/*
Function: Systask_Init_Flow_Finish
Description: 系统初始化（上电时调用一次）
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void Systask_Init_Flow_Finish(void);

/*
Function: Systask_1ms_Flow
Description: 1ms 时间片任务调度（SysTick 中断中调用）
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void Systask_1ms_Flow(void);

/*
Function: Systask_10ms_Flow
Description: 10ms 时间片任务调度（主循环中轮询）
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void Systask_10ms_Flow(void);


#endif /* SYSTASK_H */
