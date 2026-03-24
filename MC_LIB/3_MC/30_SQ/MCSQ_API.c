/**************************************************************************************************
*     File Name :                        MCSQ_API_H.c
*     Library/Module Name :              MCSQ
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制接口源文件
**************************************************************************************************/

#include "MCSQ_API.h"


/************************************电机控制接口函数*****************************************/

/**********************************************************************************************
Function: Motor_Start
Description: 电机启动
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Motor_Start(ST_MOTOR_TASK* pMotor)
{
    pMotor->Motor_State_Flag.bit.motor_run_flag = 1U;
}

/**********************************************************************************************
Function: Motor_Stop
Description: 电机停机
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Motor_Stop(ST_MOTOR_TASK* pMotor)
{
    pMotor->Motor_State_Flag.bit.motor_run_flag = 0U;
}


/**********************************************************************************************
Function: Motor_Set_Dir
Description: 设置电机运行方向
Input:  1（正转），-1（反转）
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Motor_Set_Dir(ST_MOTOR_TASK* pMotor, Q32I_ Dir)
{
    EM_DIRECTION Dir_tmp = CW;
    if(Dir == -1)
    {
        Dir_tmp = CCW;
    }
    pMotor->MCSQ_CTRL.MCSQ_BLDC.DIR_Target = Dir_tmp;
}

/**********************************************************************************************
Function: Motor_Read_Dir
Description: 获取电机运行方向
Input: 无
Output: 1（正转），-1（反转）
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Q32I_ Motor_Read_Dir(ST_MOTOR_TASK* pMotor)
{
    if(pMotor->MCSQ_CTRL.MCSQ_BLDC.DIR_Set == CW)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

/**********************************************************************************************
Function: Motor_Get_Run_State
Description: 获取电机是否为运行状态
Input: 无
Output: 1,0
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ Motor_Read_Run_State(ST_MOTOR_TASK* pMotor)
{
    if(pMotor->Motor_Flow == MOTOR_STATE_RUN)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**********************************************************************************************
Function: Motor_Set_Target_Speed
Description: 设置电机转速
Input: 电机转速（rpm）
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Motor_Set_Target_Speed(ST_MOTOR_TASK* pMotor, Q32I_ Speed)
{
    if(Speed < ((Q32I_)MOTOR_MIN_SPEED))
    {
        Speed = (Q32I_)MOTOR_MIN_SPEED;
    }
    pMotor->MCSQ_CTRL.PWM_CTRL._I_Q14U_Duty_VR = Q16I_LFT_14(Speed)/((Q32I_)MOTOR_MAX_SPEED);
}

/**********************************************************************************************
Function: Motor_Read_Speed
Description: 读取电机转速
Input: 无
Output: 电机转速（rpm）
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ Motor_Read_Speed(ST_MOTOR_TASK* pMotor)
{
    return Q32I_RHT_14(pMotor->MCSQ_CTRL.MCSQ_BLDC.FL_Freq.Q14I_LPF_Out*((Q32I_)MOTOR_MAX_SPEED));
}

/**********************************************************************************************
Function: Motor_Read_Error
Description: 读取电机故障码
Input: 无
Output: 电机故障码
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ Motor_Read_Error(ST_MOTOR_TASK* pMotor)
{
    return pMotor->MC_ERR.Motor_Error_Flag.all;
}

/**********************************************************************************************
Function: Motor_Clear_Error
Description: 清除电机故障
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Motor_Clear_Error(ST_MOTOR_TASK* pMotor)
{
    MC_Error_Clear(&pMotor->MC_ERR);
}
