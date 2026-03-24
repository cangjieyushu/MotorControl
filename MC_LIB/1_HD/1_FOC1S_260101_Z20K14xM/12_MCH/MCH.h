/**************************************************************************************************
*     File Name :                        MCH.h
*     Library/Module Name :              HD
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制HAL层头文件
**************************************************************************************************/

#ifndef MCH_H
#define MCH_H


#include "BSP.h"
#include "HAL_CFG.h"


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
    adc_reg_t * ADCx = (adc_reg_t *)(HAL_MOTOR_ADC_ADDRESS);
    Q32U_ adc_tmp = 0U;
    
    while(0U != ADCx->ADC_FCTRL.FCOUNT)
    {
        (void)ADCx->ADC_DATA_RD.ADC_DATA_RD;
    }
    
    adc_tmp = Hal_AdcMapData[0] & 0x00000FFFU;
    (*pADC_I1) = (Q32U_)adc_tmp;
    adc_tmp = Hal_AdcMapData[1] & 0x00000FFFU;
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
    mcpwm_reg_w_t * MCPWMwx = (mcpwm_reg_w_t *)(HAL_MOTOR_PWM_ADDRESS);
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
    mcpwm_reg_w_t * MCPWMwx = (mcpwm_reg_w_t *)(HAL_MOTOR_PWM_ADDRESS);
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
    mcpwm_reg_t * MCPWMx = (mcpwm_reg_t *)(HAL_MOTOR_PWM_ADDRESS);  
    mcpwm_reg_w_t *MCPWMwx = (mcpwm_reg_w_t *)(HAL_MOTOR_PWM_ADDRESS);
    MCPWMx->MCPWM_CV[HAL_PWM_UH_CHN].CV = Ta1;
    MCPWMx->MCPWM_CV[HAL_PWM_UL_CHN].CV = Ta2;
    MCPWMx->MCPWM_CV[HAL_PWM_VH_CHN].CV = Tb1;
    MCPWMx->MCPWM_CV[HAL_PWM_VL_CHN].CV = Tb2;
    MCPWMx->MCPWM_CV[HAL_PWM_WH_CHN].CV = Tc1;
    MCPWMx->MCPWM_CV[HAL_PWM_WL_CHN].CV = Tc2;
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
    tdg_reg_t * TDGx = (tdg_reg_t *)(HAL_MOTOR_TDG_ADDRESS);
    tdg_reg_w_t * TDGw = (tdg_reg_w_t *)(HAL_MOTOR_TDG_ADDRESS);
    
    TDGx->TDG_CHCFG[TDG_CHANNEL_0].TDG_CHCDOINTDLY.CDOINTDLY = 0;
    TDGx->TDG_CHCFG[TDG_CHANNEL_1].TDG_CHCDOINTDLY.CDOINTDLY = 0;
    
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
    dma_reg_w_t* dmaRegWPtr = (dma_reg_w_t *) DMA_BASE_ADDR;
    dmaRegWPtr->DMA_GCC = 0x00808080U | ((((Q32U_)0U << 16U) | ((Q32U_)0U << 24U)) & 0x0F000000U);
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
    mcpwm_reg_t * MCPWMx = (mcpwm_reg_t *)(HAL_MOTOR_PWM_ADDRESS);  
    MCPWMx->MCPWM_FLTSR.FAULTFA = 0U;
    MCPWMx->MCPWM_FLTSR.FAULTFB = 0U;
}

/**********************************************************************************************
Function: MH_TDG_Soft_Trig
Description: 软件触发TDG0
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_TDG_Soft_Trig(void)
{
    tdg_reg_t * TDGx = (tdg_reg_t *)(HAL_SYSTEM_TDG_ADDRESS);
    TDGx->TDG_CTRL1.SWTRG = 1U;
}


#endif /* MCH_H */
