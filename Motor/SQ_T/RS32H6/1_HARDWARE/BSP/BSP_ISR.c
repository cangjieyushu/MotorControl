/**************************************************************************************************
*     File Name :                        BSP_ISR.c
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             中断优先级初始化
**************************************************************************************************/
#include "BSP_ISR.h"

/**********************************************************************************************
Function: BSP_ISR_Init
Description: 中断优先级初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_ISR_Init(void)
{
	NVIC_SetPriority(TIM8_BRK_UP_TRG_COM_IRQn, 0);	//设置中断优先级
	NVIC_EnableIRQ(TIM8_BRK_UP_TRG_COM_IRQn);		//使能 刹车 中断
	
	NVIC_SetPriority(TIM3_IRQn, 1);			        //设置中断优先级
	NVIC_EnableIRQ(TIM3_IRQn);				        //使能 比较 中断
    
	NVIC_SetPriority(ADC_IRQn, 1);			        //设置中断优先级
	NVIC_EnableIRQ(ADC_IRQn);				        //使能 ADC 中断
    
	NVIC_SetPriority(TIM8_CC_IRQn, 2);	            //设置中断优先级
	NVIC_EnableIRQ(TIM8_CC_IRQn);		            //使能 触发 中断

	NVIC_SetPriority(UART1_IRQn, 4);			    //设置中断优先级
	NVIC_EnableIRQ(UART1_IRQn);				        //使能 串口 中断
	NVIC_SetPriority(UART2_IRQn, 4);			    //设置中断优先级
	NVIC_EnableIRQ(UART2_IRQn);				        //使能 串口 中断
    
	NVIC_SetPriority(SysTick_IRQn, 5);			    //设置中断优先级
	NVIC_EnableIRQ(SysTick_IRQn);				    //使能 SYS 中断
}
