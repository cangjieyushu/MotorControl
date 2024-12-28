/**************************************************************************************************
*     File Name :                        SysTask.h
*     Library/Module Name :              SysTask
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             系统状态头文件
**************************************************************************************************/
#ifndef SysTask_H
#define SysTask_H

#include "BSP.h"
#include "MotorTask.h"

#define SYSTEM_POWERUP_TIME               (1000U)           //上电时间

typedef enum{
    SYSTEM_STATE_POWERUP,
    SYSTEM_STATE_IDLE,
    SYSTEM_STATE_RUN,
    SYSTEM_STATE_ERROR,
}EM_SYSTEM_STATE_FLOW;

typedef union{
    ALL ALL;
    struct{
        BIT        systick_intflow         :1;
        BIT        system_runflag          :1;
    }BIT;
}UN_SYSTEM_STATE_FLAG;

typedef union{
    ALL ALL;
    struct{
        BIT motor_error 					:1;
        BIT systick_overflow				:1;
        BIT over_current_error 			:1;
        BIT over_speed_error 		        :1;
        BIT low_speed_error 			    :1;
        BIT over_voltage_error 			:1;
        BIT low_voltage_error 			    :1;
        BIT over_temperature_error 		:1;
        BIT low_temperature_error 			:1;
        BIT USART_1_error 			        :1;
        BIT USART_2_error 			        :1;
    }BIT;
}UN_SYSTEM_ERROR_FLAG;

typedef struct{
    Q08U_                       systick_count;
    EM_SYSTEM_STATE_FLOW        System_Flow;
    UN_SYSTEM_STATE_FLAG        System_State_Flag;
    UN_SYSTEM_ERROR_FLAG        System_Error_Flag;
    
    ST_FILTER_F                 F_FL_VBUS;
    ST_FILTER_F                 F_FL_TEMP;
    ST_FILTER_F                 F_FL_VR;
    ST_FILTER_F                 F_FL_VBG;
    
    float                       F_Duty_Target;
    float                       F_Current_Max;
    float                       F_Voltage_Bus;
    float                       F_Motor_Speed;
    float                       F_Temp_0p01_C;
    
    Q32U_                       Q32U_System_PowerUp_Time;
    Q32U_                       flow_cnt;
}ST_SYSTEM_TASK;

/**********************************************************************************************
Function: System_Task_Flow
Description: 系统状态控制
Input: 无
Output: 无
Input_Output: 系统状态指针
Return: 无
Author: CJYS
***********************************************************************************************/
void System_Task_Flow(ST_SYSTEM_TASK*  pST);

/**********************************************************************************************
Function: System_Tick_Isr
Description: 系统负载率防溢出
Input: 无
Output: 无
Input_Output: 系统状态指针
Return: 无
Author: CJYS
***********************************************************************************************/
void System_Tick_Isr(ST_SYSTEM_TASK*  pST);

extern ST_SYSTEM_TASK  Systask;

#endif /* SysTask_H */
