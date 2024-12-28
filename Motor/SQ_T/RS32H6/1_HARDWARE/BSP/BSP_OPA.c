/**************************************************************************************************
*     File Name :                        BSP_OPA.c
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             OPA初始化及应用层接口源文件
**************************************************************************************************/
#include "BSP_OPA.h"

/**********************************************************************************************
Function: BSP_OPA_Init
Description: 电机控制用OPA初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_OPA_Init(void)
{
    /*  Suggest used in FOC control,and BIOS voltage connects to Vref(the value equals to 1/2 Vref). */
    /*  Suggest used in square wave control,and BIOS voltage connects to VBG(the value equals to 0.5V). */
	OPAMP_InitTypeDef  OPAMP_InitStruct             = {0};		 						//PGA MODE3
	OPAMP_InitStruct.PGAGain						= OPAMP_GAIN_8;
	OPAMP_InitStruct.FunctionalMode					= OPAMP_MODE_PGA;
	OPAMP_InitStruct.OPAMP_OUTCONNECT				= OPAMP_VM_TO_VIN1;
	OPAMP_InitStruct.VPSEL							= OPAMP_CSR_VPSEL_P1;
	OPAMP_InitStruct.TOEXT							= OPAMP_CSR_TOEXT_DISABLE;
	OPAMP_InitStruct.TOINT							= OPAMP_CSR_TOINT_ENABLE;
	OPAMP_InitStruct.BIASMode						= OPAMP_BIAS_VBG;//OPAMP_BIAS_VBG//OPAMP_BIAS_VREF
	OPAMP_Init(HAL_MOTOR_OPA, &OPAMP_InitStruct);
	
	OPAMP_Enable(HAL_MOTOR_OPA);
}
