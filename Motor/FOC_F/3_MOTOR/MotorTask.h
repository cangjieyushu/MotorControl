/**************************************************************************************************
*     File Name :                        MotorTask.h
*     Library/Module Name :              Motor
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机子任务头文件
**************************************************************************************************/
#ifndef MotorTask_H
#define MotorTask_H

#include "MotorPara.h"
#include "MotorHal.h"

typedef void(*pMOTOR_FUN)(ST_MOTOR_TASK*);


/**********************************************************************************************
Function: MotorTask_Init_Flow_ADC_Read_Three
Description: 电机控制初始状态ADC读取
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MotorTask_Init_Flow_ADC_Read_Three(ST_MS_OFFSET* pMS_OFFSET)
{
    Q32U_ adc_data1,adc_data2,adc_data3 = 0;
    
    MH_ADC_Data_Read_Three(&adc_data1, &adc_data2, &adc_data3);
    pMS_OFFSET->_I_Q12I_Ia_Data = (Q32I_)adc_data1;
    pMS_OFFSET->_I_Q12I_Ib_Data = (Q32I_)adc_data2;
    pMS_OFFSET->_I_Q12I_Ic_Data = (Q32I_)adc_data3;
}

/**********************************************************************************************
Function: MotorTask_Init_Flow_ADC_Read_One
Description: 电机控制初始状态ADC读取
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MotorTask_Init_Flow_ADC_Read_One(ST_MS_OFFSET* pMS_OFFSET)
{
    Q32U_ adc_data1,adc_data2 = 0;
    
    MH_ADC_Data_Read_One(&adc_data1, &adc_data2);
    pMS_OFFSET->_I_Q12I_Ishunt_2_Data = (Q32I_)adc_data1;
    pMS_OFFSET->_I_Q12I_Ishunt_1_Data = (Q32I_)adc_data2;
}

/**********************************************************************************************
Function: MotorTask_Run_Flow_ADC_Read_Three
Description: 电机控制运行状态ADC读取
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MotorTask_Run_Flow_ADC_Read_Three(ST_SVPWM_CONTROL_F* pCTRL)
{
    Q32U_ adc_data1,adc_data2,adc_data3 = 0;
    
    MH_ADC_Data_Read_Three(&adc_data1, &adc_data2, &adc_data3);
    pCTRL->_I_Q12I_Ia_Data = (Q32I_)adc_data1;
    pCTRL->_I_Q12I_Ib_Data = (Q32I_)adc_data2;
    pCTRL->_I_Q12I_Ic_Data = (Q32I_)adc_data3;
    
    pCTRL->_I_F_Ia = pCTRL->_P_F_Current_Scale*((float)(pCTRL->_I_Q12I_Ia_Offset - pCTRL->_I_Q12I_Ia_Data));
    pCTRL->_I_F_Ib = pCTRL->_P_F_Current_Scale*((float)(pCTRL->_I_Q12I_Ib_Offset - pCTRL->_I_Q12I_Ib_Data));
    pCTRL->_I_F_Ic = pCTRL->_P_F_Current_Scale*((float)(pCTRL->_I_Q12I_Ic_Offset - pCTRL->_I_Q12I_Ic_Data));
}

/**********************************************************************************************
Function: MotorTask_Run_Flow_ADC_Read_Three
Description: 电机控制运行状态ADC读取
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MotorTask_Run_Flow_ADC_Read_One(ST_SVPWM_CONTROL_F* pCTRL)
{
    Q32U_ adc_data1,adc_data2 = 0;
    
    MH_ADC_Data_Read_One(&adc_data1, &adc_data2);
    pCTRL->_I_Q12I_Ishunt_2_Data = (Q32I_)adc_data1;
    pCTRL->_I_Q12I_Ishunt_1_Data = (Q32I_)adc_data2;
    
    pCTRL->_I_F_Ishunt[0] =  pCTRL->_P_F_Current_Scale*(pCTRL->_I_Q12I_Ishunt_1_Data - pCTRL->_I_Q12I_Ishunt_1_Offset);
    pCTRL->_I_F_Ishunt[1] = -pCTRL->_P_F_Current_Scale*(pCTRL->_I_Q12I_Ishunt_2_Data - pCTRL->_I_Q12I_Ishunt_2_Offset);
    pCTRL->_I_F_Ishunt[2] = -pCTRL->_I_F_Ishunt[0] - pCTRL->_I_F_Ishunt[1];
    MotorFoc_OneShunt_Cal_F(pCTRL);
}

/**********************************************************************************************
Function: MotorTask_Run_Flow_PWM_Set_Three
Description: 电机控制运行状态PWM设置
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MotorTask_Run_Flow_PWM_Set_Three(ST_SVPWM_CONTROL_F* pCTRL)
{
    float pwm_tmp1,pwm_tmp2,pwm_tmp3 = 0;
    
    MotorFoc_SVPWM_ThreeShunt_F(&Motor.SVPWM_CTRL);
    
    pwm_tmp1 = Motor.SVPWM_CTRL._P_F_PWM_All_Count*Motor.SVPWM_CTRL._O_F_Ta;
    pwm_tmp2 = Motor.SVPWM_CTRL._P_F_PWM_All_Count*Motor.SVPWM_CTRL._O_F_Tb;
    pwm_tmp3 = Motor.SVPWM_CTRL._P_F_PWM_All_Count*Motor.SVPWM_CTRL._O_F_Tc;
    
    MH_PWM_Duty_Set_Three((Q32U_)pwm_tmp1,(Q32U_)pwm_tmp2,(Q32U_)pwm_tmp3);
}

/**********************************************************************************************
Function: MotorTask_Run_Flow_PWM_Set_One
Description: 电机控制运行状态PWM设置
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MotorTask_Run_Flow_PWM_Set_One(ST_SVPWM_CONTROL_F* pCTRL)
{
    float pwm_tmp1,pwm_tmp2,pwm_tmp3,pwm_tmp4,pwm_tmp5,pwm_tmp6,adc_tmp1,adc_tmp2 = 0;
    
    MotorFoc_SVPWM_OneShunt_F(&Motor.SVPWM_CTRL);
    
    pwm_tmp1 = Motor.SVPWM_CTRL._P_F_PWM_All_Count*Motor.SVPWM_CTRL._O_F_TaUp;
    pwm_tmp2 = Motor.SVPWM_CTRL._P_F_PWM_All_Count*Motor.SVPWM_CTRL._O_F_TaDn;
    pwm_tmp3 = Motor.SVPWM_CTRL._P_F_PWM_All_Count*Motor.SVPWM_CTRL._O_F_TbUp;
    pwm_tmp4 = Motor.SVPWM_CTRL._P_F_PWM_All_Count*Motor.SVPWM_CTRL._O_F_TbDn;
    pwm_tmp5 = Motor.SVPWM_CTRL._P_F_PWM_All_Count*Motor.SVPWM_CTRL._O_F_TcUp;
    pwm_tmp6 = Motor.SVPWM_CTRL._P_F_PWM_All_Count*Motor.SVPWM_CTRL._O_F_TcDn;
    adc_tmp1 = Motor.SVPWM_CTRL._P_F_PWM_All_Count*Motor.SVPWM_CTRL._O_F_ADCTrigTime1;
    adc_tmp2 = Motor.SVPWM_CTRL._P_F_PWM_All_Count*Motor.SVPWM_CTRL._O_F_ADCTrigTime2;
    
    MH_PWM_Duty_Set_One((Q32U_)pwm_tmp1,(Q32U_)pwm_tmp2,(Q32U_)pwm_tmp3,(Q32U_)pwm_tmp4,(Q32U_)pwm_tmp5,(Q32U_)pwm_tmp6);
    MH_ADC_TrigTime_Set((Q32U_)adc_tmp1,(Q32U_)adc_tmp2);
}


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
static inline void Motor_Start(void)
{
    Motor.Motor_State_Flag.bit.motor_run_flag = 1U;
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
static inline void Motor_Stop(void)
{
    Motor.Motor_State_Flag.bit.motor_run_flag = 0U;
}


/**********************************************************************************************
Function: Motor_Set_Dir
Description: 设置电机运行方向
Input: 1.0f（正转），-1.0f（反转）
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void Motor_Set_Dir(float Dir)
{
    Motor.SRAD_CTRL._I_F_DIR_Target = Dir;
    Motor.IF_CTRL._I_F_DIR_Target = Dir;
    Motor.VF_CTRL._I_F_DIR_Target = Dir;
}

/**********************************************************************************************
Function: Motor_Read_Dir
Description: 获取电机运行方向
Input: 无
Output: 1.0f（正转），-1.0f（反转）
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline float Motor_Read_Dir(void)
{
    return Motor.SRAD_CTRL._O_F_DIR_Set;
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
static inline Q32U_ Motor_Read_Run_State(void)
{
    if(Motor.Motor_Flow == MOTOR_STATE_RUN)
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
static inline void Motor_Set_Target_Speed(float Speed)
{
    Motor.SRAD_CTRL._I_F_SRAD_Target = MOTOR_SPEED_TO_SRAD(Speed);
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
static inline float Motor_Read_Speed(void)
{
    return Motor.SRAD_CTRL._I_F_SRAD;
}

/**********************************************************************************************
Function: Motor_Set_Vbus
Description: 设置FOC算法的母线电压值
Input: 母线电压（V）
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void Motor_Set_Vbus(float Vbus_Val)
{
    Motor.SVPWM_CTRL._I_F_Vbus = Vbus_Val;
    Motor.SVPWM_CTRL._I_F_One_Over_Vbus = 1.0f/Vbus_Val;
    Motor.SRAD_CTRL._I_F_Vbus = Vbus_Val;
    Motor.CURRENT_CTRL._I_F_Vbus = Vbus_Val;
}

/**********************************************************************************************
Function: Motor_Read_Current_Max
Description: 获取周期内相电流最大值，周期为该函数被调用的周期
Input: 无
Output: 相电流最大值（A）
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline float Motor_Read_Current_Max(void)
{
    float iphase_max_tmp = Motor.F_Iphase_Max;
    Motor.F_Iphase_Max = 0.0f;
    return iphase_max_tmp;
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
static inline Q32U_ Motor_Read_Error(void)
{
    return Motor.Motor_Error_Flag.all;
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
static inline void Motor_Clear_Error(void)
{
    Motor.Motor_Error_Flag.all = 0U;
}

/**********************************************************************************************
Function: MotorTask_Speed_Flow
Description: 电机控制速度环
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Speed_Flow(ST_MOTOR_TASK* pMotor);

/**********************************************************************************************
Function: MotorTask_Current_Flow
Description: 电机控制电流环
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Current_Flow(ST_MOTOR_TASK* pMotor);

/**********************************************************************************************
Function: MotorTask_Shut_Flow
Description: 电机控制故障关断
Input: 无
Output: 无
Input_Output: 电机控制指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MotorTask_Shut_Flow(ST_MOTOR_TASK* pMotor);

#endif /* MotorTask_H */
