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
Function: MH_ADC_Data_Read_Three
Description: 三电阻读取ADC采样数据
Input: 无
Output: 无
Input_Output: ADC数据指针
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_ADC_Data_Read_Three(Q32I_* pADC_Ia, Q32I_* pADC_Ib, Q32I_* pADC_Ic)
{
    adc_reg_t * ADCx = (adc_reg_t *)(ADC0_BASE_ADDR);
    while(0U != ADCx->ADC_FCTRL.FCOUNT)
    {
        (void)ADCx->ADC_DATA_RD.ADC_DATA_RD;
    }
    
    (*pADC_Ia) = (Q32I_)(Hal_AdcLoopData[0] & 0x00000FFF);
    (*pADC_Ib) = (Q32I_)(Hal_AdcLoopData[1] & 0x00000FFF);
    (*pADC_Ic) = (Q32I_)(Hal_AdcLoopData[2] & 0x00000FFF);
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
static inline void MH_ADC_Data_Read_One(Q32I_* pADC_I1, Q32I_* pADC_I2)
{
    adc_reg_t * ADCx = (adc_reg_t *)(ADC0_BASE_ADDR);
    while(0U != ADCx->ADC_FCTRL.FCOUNT)
    {
        (void)ADCx->ADC_DATA_RD.ADC_DATA_RD;
    }
    
    (*pADC_I1) = (Q32I_)(Hal_AdcMapData[0] & 0x00000FFFU);
    (*pADC_I2) = (Q32I_)(Hal_AdcMapData[1] & 0x00000FFFU);
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
    mcpwm_reg_w_t * MCPWMwx = (mcpwm_reg_w_t *)(MCPWM1_BASE_ADDR);
    Q32U_ regVal = MCPWMwx->MCPWM_GLBCR;
    
    MCPWMwx->MCPWM_GLBCR = regVal | HAL_PWM_ALL_CHN;
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
    mcpwm_reg_w_t * MCPWMwx = (mcpwm_reg_w_t *)(MCPWM1_BASE_ADDR);
    Q32U_ regVal = MCPWMwx->MCPWM_GLBCR;
    
    MCPWMwx->MCPWM_GLBCR = regVal & (~(HAL_PWM_ALL_CHN));
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
    mcpwm_reg_t * MCPWMx = (mcpwm_reg_t *)(MCPWM1_BASE_ADDR);  
    mcpwm_reg_w_t *MCPWMwx = (mcpwm_reg_w_t *)(MCPWM1_BASE_ADDR);
    
    MCPWMx->MCPWM_CV[HAL_PWM_UH_CHN].CV = (Q32U_)(Ta*HAL_PWM_ALL_COUNT_F);
    MCPWMx->MCPWM_CV[HAL_PWM_VH_CHN].CV = (Q32U_)(Tb*HAL_PWM_ALL_COUNT_F);
    MCPWMx->MCPWM_CV[HAL_PWM_WH_CHN].CV = (Q32U_)(Tc*HAL_PWM_ALL_COUNT_F);
    MCPWMwx->MCPWM_RELOAD |= 0x0700U;
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
    mcpwm_reg_t * MCPWMx = (mcpwm_reg_t *)(MCPWM1_BASE_ADDR);  
    mcpwm_reg_w_t *MCPWMwx = (mcpwm_reg_w_t *)(MCPWM1_BASE_ADDR);
    
    MCPWMx->MCPWM_CV[HAL_PWM_UH_CHN].CV = (Q32U_)(Ta1*HAL_PWM_ALL_COUNT_F);
    MCPWMx->MCPWM_CV[HAL_PWM_UL_CHN].CV = (Q32U_)(Ta2*HAL_PWM_ALL_COUNT_F);
    MCPWMx->MCPWM_CV[HAL_PWM_VH_CHN].CV = (Q32U_)(Tb1*HAL_PWM_ALL_COUNT_F);
    MCPWMx->MCPWM_CV[HAL_PWM_VL_CHN].CV = (Q32U_)(Tb2*HAL_PWM_ALL_COUNT_F);
    MCPWMx->MCPWM_CV[HAL_PWM_WH_CHN].CV = (Q32U_)(Tc1*HAL_PWM_ALL_COUNT_F);
    MCPWMx->MCPWM_CV[HAL_PWM_WL_CHN].CV = (Q32U_)(Tc2*HAL_PWM_ALL_COUNT_F);
    MCPWMwx->MCPWM_RELOAD |= 0x0700U;
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
    Q32U_ Ch1Delay = (Q32U_)(Ch1*HAL_PWM_ALL_COUNT_F);
    Q32U_ Ch2Delay = (Q32U_)(Ch2*HAL_PWM_ALL_COUNT_F);
    
    tdg_reg_t * TDGx = (tdg_reg_t *)(TDG0_BASE_ADDR);
    tdg_reg_w_t * TDGw = (tdg_reg_w_t *)(TDG0_BASE_ADDR);
    
    TDGx->TDG_CHCFG[TDG_CHANNEL_0].TDG_CHCDOINTDLY.CDOINTDLY = 0;
    TDGx->TDG_CHCFG[TDG_CHANNEL_1].TDG_CHCDOINTDLY.CDOINTDLY = 0;
    
    Q32U_ doId = (Q32U_)TDG_DO_0;
    Q32U_ doEnable;
    doEnable = TDGw->TDG_CHCFG[TDG_CHANNEL_0].TDG_CHCTRL;
    TDGw->TDG_CHCFG[TDG_CHANNEL_0].TDG_CHCTRL = doEnable | (((Q32U_)ENABLE) << (8U+doId));
    TDGw->TDG_CHCFG[TDG_CHANNEL_0].TDG_CHDOOFS[doId] = (Q32U_)Ch1Delay;  
    doEnable = TDGw->TDG_CHCFG[TDG_CHANNEL_1].TDG_CHCTRL;
    TDGw->TDG_CHCFG[TDG_CHANNEL_1].TDG_CHCTRL = doEnable | (((Q32U_)ENABLE) << (8U+doId));
    TDGw->TDG_CHCFG[TDG_CHANNEL_1].TDG_CHDOOFS[doId] = (Q32U_)Ch2Delay;
    
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
    dma_reg_w_t* dmaRegWPtr = (dma_reg_w_t *) DMA_BASE_ADDR;
    dmaRegWPtr->DMA_GCC = 0x00808080U | ((((Q32U_)DMA_CHANNEL0 << 16U) | ((Q32U_)DMA_CHANNEL0 << 24U)) & 0x0F000000U);
}

/**********************************************************************************************
Function: MH_Hall_State_Read
Description: 读取用于HALL电平
Input: 无
Output: 无
Input_Output: 无
Return: HALL电平
Author: CJYS
***********************************************************************************************/
static inline Q32U_ MH_Hall_State_Read(void)
{
	return 0;
}

/**********************************************************************************************
Function: MH_Hall_TIM_Count_Read
Description: 读取用于HALL换向计数器的当前值
Input: 无
Output: 无
Input_Output: 无
Return: 计数器值
Author: CJYS
***********************************************************************************************/
static inline Q32U_ MH_Hall_TIM_Count_Read(void)
{
    stim_reg_w_t* stimRegWPtr = (stim_reg_w_t*)STIM_BASE_ADDR;
    return ((Q32U_)stimRegWPtr->STIM_CNTn[HAL_STIM_HALL]);
}

#endif /* MotorHal_H */
