/**************************************************************************************************
*     File Name :                        SYSTASK.h
*     Library/Module Name :              SYSTASK
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             系统状态头文件
**************************************************************************************************/

#ifndef SYSTASK_H
#define SYSTASK_H


#include "MATH_LPF_T.h"
#include "BSP.h"

#ifdef MCSQ_CJYS
    #include "MCSQ_TASK.h"
    #include "MCSQ_API.h"
    #elif MCFOC_CJYS
        #ifdef MCFOC_CJYS_F
            #include "MCFOC_TASK_F.h"
            #include "MCFOC_API_F.h"
            #define Motor                       Motor_F
            #define MotorTask_Speed_Flow        MotorTask_Speed_Flow_F
            #define MotorTask_Current_Flow      MotorTask_Current_Flow_F
            #define MotorTask_Shut_Flow         MotorTask_Shut_Flow_F
            #define Motor_Start                 Motor_Start_F
            #define Motor_Stop                  Motor_Stop_F
            #define Motor_Set_Dir               Motor_Set_Dir_F
            #define Motor_Read_Dir              Motor_Read_Dir_F
            #define Motor_Read_Run_State        Motor_Read_Run_State_F
            #define Motor_Set_Target_Speed      Motor_Set_Target_Speed_F
            #define Motor_Read_Speed            Motor_Read_Speed_F
            #define Motor_Read_Error            Motor_Read_Error_F
            #define Motor_Clear_Error           Motor_Clear_Error_F
        #elif MCFOC_CJYS_T
            #include "MCFOC_TASK_T.h"
            #include "MCFOC_API_T.h"
            #define Motor                       Motor_T
            #define MotorTask_Speed_Flow        MotorTask_Speed_Flow_T
            #define MotorTask_Current_Flow      MotorTask_Current_Flow_T
            #define MotorTask_Shut_Flow         MotorTask_Shut_Flow_T
            #define Motor_Start                 Motor_Start_T
            #define Motor_Stop                  Motor_Stop_T
            #define Motor_Set_Dir               Motor_Set_Dir_T
            #define Motor_Read_Dir              Motor_Read_Dir_T
            #define Motor_Read_Run_State        Motor_Read_Run_State_T
            #define Motor_Set_Target_Speed      Motor_Set_Target_Speed_T
            #define Motor_Read_Speed            Motor_Read_Speed_T
            #define Motor_Read_Error            Motor_Read_Error_T
            #define Motor_Clear_Error           Motor_Clear_Error_T
    #endif
#endif

#define SYSTEM_POWERUP_TIME               (1000U)           //ms，上电时间


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
        BIT USART_1_error 			        :1;
        BIT USART_2_error 			        :1;
    }BIT;
}UN_SYSTEM_ERROR_FLAG;

typedef struct{
    Q08U_                       systick_10ms_count;
    
    EM_SYSTEM_STATE_FLOW        System_Flow;
    UN_SYSTEM_STATE_FLAG        System_State_Flag;
    UN_SYSTEM_ERROR_FLAG        System_Error_Flag;
    
    ST_LPF_T                    FL_VR;
    ST_LPF_T                    FL_VBG;
    
    Q32I_                       Q16U_Duty_Target;
    Q32I_                       Q16U_Motor_Speed_Target;
    Q32I_                       Q16U_Motor_Speed;
    
    Q32U_                       _P_Q32U_System_PowerUp_Time;
    
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


#endif /* SYSTASK_H */
