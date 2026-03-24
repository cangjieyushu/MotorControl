/**************************************************************************************************
*     File Name :                        MCFOC_API_T.c
*     Library/Module Name :              MCFOC_T
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制接口源文件
**************************************************************************************************/

#include "MCFOC_API_T.h"


/************************************电机控制接口函数*****************************************/

/**********************************************************************************************
Function: Motor_Start_T
Description: 电机启动
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Motor_Start_T(ST_MOTOR_TASK* pMotor)
{
    pMotor->Motor_State_Flag.bit.motor_run_flag = 1U;
}

/**********************************************************************************************
Function: Motor_Stop_T
Description: 电机停机
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Motor_Stop_T(ST_MOTOR_TASK* pMotor)
{
    pMotor->Motor_State_Flag.bit.motor_run_flag = 0U;
}


/**********************************************************************************************
Function: Motor_Set_Dir_T
Description: 设置电机运行方向
Input:  1（正转），-1（反转）
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Motor_Set_Dir_T(ST_MOTOR_TASK* pMotor, Q32I_ Dir)
{
    Q32I_ Dir_tmp = 1;
    if(Dir == -1)
    {
        Dir_tmp = -1;
    }
    pMotor->PMSM_ELEC_CTRL._I_Q00I_DIR_Target = Dir_tmp;
}

/**********************************************************************************************
Function: Motor_Read_Dir_T
Description: 获取电机运行方向
Input: 无
Output: 1（正转），-1（反转）
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Q32I_ Motor_Read_Dir_T(ST_MOTOR_TASK* pMotor)
{
    Q32I_ Dir_tmp = 1;
    if(pMotor->PMSM_ELEC_CTRL._I_Q00I_DIR_Target == -1)
    {
        Dir_tmp = -1;
    }
    return Dir_tmp;
}

/**********************************************************************************************
Function: Motor_Get_Run_State_T
Description: 获取电机是否为运行状态
Input: 无
Output: 1, 0
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ Motor_Read_Run_State_T(ST_MOTOR_TASK* pMotor)
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
Function: Motor_Set_Target_Speed_T
Description: 设置电机转速
Input: 电机转速（rpm）
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Motor_Set_Target_Speed_T(ST_MOTOR_TASK* pMotor, Q32I_ Speed)
{
    pMotor->FREQ_CTRL._I_Q14I_FREQ_Target = Q14I_FREQ_TO_PU(MOTOR_SPEED_TO_FREQ((float)Speed));
}

/**********************************************************************************************
Function: Motor_Read_Speed_T
Description: 读取电机转速
Input: 无
Output: 电机转速（rpm）
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Q32I_ Motor_Read_Speed_T(ST_MOTOR_TASK* pMotor)
{
    return Q32I_RHT_14(pMotor->PMSM_ELEC_CTRL._O_Q14I_Freq*((Q32I_)MOTOR_MAX_SPEED));
}

/**********************************************************************************************
Function: Motor_Read_Error_T
Description: 读取电机故障码
Input: 无
Output: 电机故障码
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Q32U_ Motor_Read_Error_T(ST_MOTOR_TASK* pMotor)
{
    return pMotor->MC_ERR.Motor_Error_Flag.all;
}

/**********************************************************************************************
Function: Motor_Clear_Error_T
Description: 清除电机故障
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Motor_Clear_Error_T(ST_MOTOR_TASK* pMotor)
{
    MC_Error_Clear(&pMotor->MC_ERR);
}
