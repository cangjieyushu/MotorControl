/*
*     File Name :                        mcfoc_task_t
*     Library/Module Name :              mcfoc_t
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机子任务
*/

#ifndef MCFOC_TASK_T_H
#define MCFOC_TASK_T_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "pmsm_para.h"
#include "hal_mc.h"
#include "mcfoc_para_t.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/
#if (MOTOR_SHUNT_MODE == MOTOR_SHUNT_THREE)
#define MCFOC_Offset_Check              MCFOC_Offset_Check_Three_T
#define MCFOC_Init_Flow_ADC_Read        MCFOC_Init_Flow_ADC_Read_Three_T
#define MCFOC_Run_Flow_ADC_Read         MCFOC_Run_Flow_ADC_Read_Three_T
#define MCFOC_Run_Flow_PWM_Set          MCFOC_Run_Flow_PWM_Set_Three_T
#elif  (MOTOR_SHUNT_MODE == MOTOR_SHUNT_ONE)
#define MCFOC_Offset_Check              MCFOC_Offset_Check_One_T
#define MCFOC_Init_Flow_ADC_Read        MCFOC_Init_Flow_ADC_Read_One_T
#define MCFOC_Run_Flow_ADC_Read         MCFOC_Run_Flow_ADC_Read_One_T
#define MCFOC_Run_Flow_PWM_Set          MCFOC_Run_Flow_PWM_Set_One_T
#endif

#if (MOTOR_EST_MODE == MOTOR_EST_SMO)
#define MCFOC_EST_FUNCTION              MCFOC_EST_SMO_Cal_T(&pMotor->SMO_Ctrl, &pMotor->PMSM_Elec);
#define MCFOC_EST_Freq                  SMO_Ctrl.FL_SMO_FREQ.O_Q14I_LPF_Out
#define MCFOC_EST_TG_Triangle           SMO_Ctrl.TG_SMO_Triangle
#define MCFOC_EST_TG_Triangle_Comp      SMO_Ctrl.TG_SMO_Triangle_Comp
#elif (MOTOR_EST_MODE == MOTOR_EST_FLUX)
#define MCFOC_EST_FUNCTION              MCFOC_EST_FLUX_Cal_T(&pMotor->FLUX_Ctrl, &pMotor->PMSM_Elec);
#define MCFOC_EST_Freq                  FLUX_Ctrl.FL_FLUX_FREQ.O_Q14I_LPF_Out
#define MCFOC_EST_TG_Triangle           FLUX_Ctrl.TG_FLUX_Triangle
#define MCFOC_EST_TG_Triangle_Comp      FLUX_Ctrl.TG_FLUX_Triangle_Comp
#endif


/*-------------------------- 3. 枚举/结构体 ------------------------------*/


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: MCFOC_Speed_Flow_T
Description: 电机控制速度环
Input: 无
Output: 无
Input_Output: 电机编号0，1，2，3；
Return: 无
Author: CJYS
*/
void MCFOC_Speed_Flow_T(Q32U_ motor_num);

/*
Function: MCFOC_Current_Flow_T
Description: 电机控制电流环
Input: 无
Output: 无
Input_Output: 电机编号0，1，2，3；
Return: 无
Author: CJYS
*/
void MCFOC_Current_Flow_T(Q32U_ motor_num);


#endif /* MCFOC_TASK_T_H */
