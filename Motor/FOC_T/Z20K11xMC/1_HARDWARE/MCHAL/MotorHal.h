/**************************************************************************************************
*     File Name :                        MotorHal.h
*     Library/Module Name :              MotorHal
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制HAL层头文件
**************************************************************************************************/
#ifndef MotorHal_H
#define MotorHal_H

#include "BSP.h"
#include "MotorHal_cfg.h"

/**********************************************************************************************
Function: MH_ADC_FIFO_Read_Three
Description: ADCFIFO
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_ADC_FIFO_Read_Three(void)
{
    adc_reg_t * ADCx = (adc_reg_t *)(HAL_MOTOR_ADC_ADDRESS);
    for(Q32U_ i=0U;i<2U*HAL_MOTOR_ADC_NUM;i++){Hal_AdcLoopData[i] = ADCx->ADC_DATA_RD.ADC_DATA_RD;}
    while(0U != ADCx->ADC_FCTRL.FCOUNT){(void)ADCx->ADC_DATA_RD.ADC_DATA_RD;}
}

/**********************************************************************************************
Function: MH_ADC_FIFO_Read_One
Description: ADCFIFO
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_ADC_FIFO_Read_One(void)
{
    adc_reg_t * ADCx = (adc_reg_t *)(HAL_MOTOR_ADC_ADDRESS);
    for(Q32U_ i=0U;i<HAL_MOTOR_ADC_NUM;i++){Hal_AdcLoopData[i] = ADCx->ADC_DATA_RD.ADC_DATA_RD;}
    while(0U != ADCx->ADC_FCTRL.FCOUNT){(void)ADCx->ADC_DATA_RD.ADC_DATA_RD;}
}

/**********************************************************************************************
Function: MH_ADC_Data_Read_Three
Description: 三电阻读取ADC采样数据
Input: 无
Output: 无
Input_Output: ADC数据指针
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_ADC_Data_Read_Three(Q32U_* pADC_Ia, Q32U_* pADC_Ib, Q32U_* pADC_Ic)
{
    Q32U_ adc_tmp = 0U;
    
    adc_tmp = Hal_AdcLoopData[0] & 0x00000FFFU;
    (*pADC_Ia) = (Q32U_)adc_tmp;
    adc_tmp = Hal_AdcLoopData[1] & 0x00000FFFU;
    (*pADC_Ib) = (Q32U_)adc_tmp;
    adc_tmp = Hal_AdcLoopData[2] & 0x00000FFFU;
    (*pADC_Ic) = (Q32U_)adc_tmp;
}

/**********************************************************************************************
Function: MH_ADC_Data_Read_One
Description: 单电阻读取ADC采样数据
Input: 无
Output: 无
Input_Output: ADC数据指针
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_ADC_Data_Read_One(Q32U_* pADC_I1, Q32U_* pADC_I2)
{
    Q32U_ adc_tmp = 0U;
    
    adc_tmp = Hal_AdcLoopData[0] & 0x00000FFFU;
    (*pADC_I1) = (Q32U_)adc_tmp;
    adc_tmp = Hal_AdcLoopData[1] & 0x00000FFFU;
    (*pADC_I2) = (Q32U_)adc_tmp;
}

/**********************************************************************************************
Function: MH_PWM_Output_Enable
Description: PWM输出通道开通
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_PWM_Output_Enable(void) 
{
    tim_reg_w_t * TIMx_w = (tim_reg_w_t *)(HAL_MOTOR_PWM_ADDRESS);
    TIMx_w->TIM_GLBCR |= (HAL_PWM_ALL_CHN);
}

/**********************************************************************************************
Function: MH_PWM_Output_Disable
Description: PWM输出通道关闭
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_PWM_Output_Disable(void)
{
    tim_reg_w_t * TIMx_w = (tim_reg_w_t *)(HAL_MOTOR_PWM_ADDRESS);
    TIMx_w->TIM_GLBCR &= (~(HAL_PWM_ALL_CHN));
}

/**********************************************************************************************
Function: MH_PWM_Duty_Set_Three
Description: PWM输出三相占空比输出
Input: ABC三相切换时间点，0~0.5对应开始到对称中心
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_PWM_Duty_Set_Three(Q32U_ Ta, Q32U_ Tb, Q32U_ Tc)
{
    tim_reg_w_t * TIMx_w = (tim_reg_w_t *)(HAL_MOTOR_PWM_ADDRESS);
	TIMx_w->TIM_CCVn[HAL_PWM_UH_CHN] = Ta;
	TIMx_w->TIM_CCVn[HAL_PWM_UL_CHN] = HAL_PWM_SET_COUNT_T-Ta;
	TIMx_w->TIM_CCVn[HAL_PWM_VH_CHN] = Tb;
	TIMx_w->TIM_CCVn[HAL_PWM_VL_CHN] = HAL_PWM_SET_COUNT_T-Tb;
	TIMx_w->TIM_CCVn[HAL_PWM_WH_CHN] = Tc;
	TIMx_w->TIM_CCVn[HAL_PWM_WL_CHN] = HAL_PWM_SET_COUNT_T-Tc;
	TIMx_w->TIM_RELOAD |= 0x0100U;
}

/**********************************************************************************************
Function: MH_PWM_Duty_Set_One
Description: PWM输出三相占空比输出，带移相
Input: ABC三相占空比，0~0.5对应开始到对称中心，Ta1是上升计数过程中的切换时间点，Ta2是下降计数过程中的切换时间点，
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_PWM_Duty_Set_One(Q32U_ Ta1, Q32U_ Ta2, Q32U_ Tb1, Q32U_ Tb2, Q32U_ Tc1, Q32U_ Tc2)
{
    tim_reg_w_t * TIMx_w = (tim_reg_w_t *)(HAL_MOTOR_PWM_ADDRESS);
	TIMx_w->TIM_CCVn[HAL_PWM_UH_CHN] = Ta1;
	TIMx_w->TIM_CCVn[HAL_PWM_UL_CHN] = HAL_PWM_SET_COUNT_T-Ta2;
	TIMx_w->TIM_CCVn[HAL_PWM_VH_CHN] = Tb1;
	TIMx_w->TIM_CCVn[HAL_PWM_VL_CHN] = HAL_PWM_SET_COUNT_T-Tb2;
	TIMx_w->TIM_CCVn[HAL_PWM_WH_CHN] = Tc1;
	TIMx_w->TIM_CCVn[HAL_PWM_WL_CHN] = HAL_PWM_SET_COUNT_T-Tc2;
	TIMx_w->TIM_RELOAD |= 0x0100U;
}

/**********************************************************************************************
Function: MH_ADC_TrigTime_Set
Description: 移相情况下，ADC的采样时刻设置
Input: 0~0.5对应开始到对称中心，ch1是第一次采样时刻，Ta2是第二次采样时刻，
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_ADC_TrigTime_Set(Q32U_ Ch1, Q32U_ Ch2)
{
    tdg_reg_t * TDGx = (tdg_reg_t *)(HAL_MOTOR_TDG_ADDRESS);
    tdg_reg_w_t * TDGw = (tdg_reg_w_t *)(HAL_MOTOR_TDG_ADDRESS);
    
    TDGx->TDG_CHCFG[TDG_CHANNEL_0].TDG_CHDOCINTDLY.CDOINTDLY = 0;
    TDGx->TDG_CHCFG[TDG_CHANNEL_1].TDG_CHDOCINTDLY.CDOINTDLY = 0;
    
    Q32U_ doId = (Q32U_)TDG_DO_0;
    Q32U_ doEnable;
    doEnable = TDGw->TDG_CHCFG[TDG_CHANNEL_0].TDG_CHCTRL;
    TDGw->TDG_CHCFG[TDG_CHANNEL_0].TDG_CHCTRL = doEnable | (((Q32U_)ENABLE) << (8U+doId));
    TDGw->TDG_CHCFG[TDG_CHANNEL_0].TDG_CHDOOFS[doId] = Ch1;  
    doEnable = TDGw->TDG_CHCFG[TDG_CHANNEL_1].TDG_CHCTRL;
    TDGw->TDG_CHCFG[TDG_CHANNEL_1].TDG_CHCTRL = doEnable | (((Q32U_)ENABLE) << (8U+doId));
    TDGw->TDG_CHCFG[TDG_CHANNEL_1].TDG_CHDOOFS[doId] = Ch2;
    
    TDGx->TDG_CTRL2.CH0E = (Q32U_)ENABLE;
    TDGx->TDG_CTRL2.CH1E = (Q32U_)ENABLE;
    
    TDGx->TDG_CTRL1.CFGUP = 1U;
    
    while(1U == (Q08U_)TDGx->TDG_CTRL1.CFGUP){}
}

/**********************************************************************************************
Function: MH_Current_IntFlag_Clear
Description: DMA的0号通道中断标志位清除
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_Current_IntFlag_Clear(void)
{
    ADC_IntClear(HAL_MOTOR_ADC, ADC_FWM_INT);
}

/**********************************************************************************************
Function: MH_PWMFault_IntFlag_Clear
Description: MCPWM故障中断标志位清除
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_PWMFault_IntFlag_Clear(void)
{
    TIM_IntClear(HAL_MOTOR_PWM, TIM_INT_FAULT);
}

#endif /* MotorHal_H */
