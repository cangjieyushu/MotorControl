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

#define ADC_DATA_READ_U_BEMF        (Hal_AdcLoopData[0] & 0x00000FFFU)
#define ADC_DATA_READ_V_BEMF        (Hal_AdcLoopData[1] & 0x00000FFFU)
#define ADC_DATA_READ_W_BEMF        (Hal_AdcLoopData[2] & 0x00000FFFU)
#define ADC_DATA_READ_CURRENT       (Hal_AdcLoopData[3] & 0x00000FFFU)

/**********************************************************************************************
Function: MH_ADC_FIFO_Read
Description: ADCFIFO
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_ADC_FIFO_Read(void)
{
    adc_reg_t * ADCx = (adc_reg_t *)(HAL_MOTOR_ADC_ADDRESS);
    while(0U != ADCx->ADC_FCTRL.FCOUNT){(void)ADCx->ADC_DATA_RD.ADC_DATA_RD;}
} 

/**********************************************************************************************
Function: MH_ADC_Soft_Trigger
Description: 软件触发ADC
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_ADC_Soft_Trigger(void)
{
    tdg_reg_t * TDGx = (tdg_reg_t *)(HAL_MOTOR_TDG_ADDRESS);
    TDGx->TDG_CTRL1.SWTRG = 1U;
}

/**********************************************************************************************
Function: MH_ADC_TrigTime_Set
Description: 延迟触发ADC,避开米勒平台
Input: 延迟触发采样计数器值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_ADC_TrigTime_Set(Q32U_ count)
{
    mcpwm_reg_t * MCPWMx = (mcpwm_reg_t *)(HAL_MOTOR_PWM_ADDRESS);
    mcpwm_reg_w_t *MCPWMwx = (mcpwm_reg_w_t *)(HAL_MOTOR_PWM_ADDRESS); 
    MCPWMx->MCPWM_CV[HAL_PWM_ADC_CHN].CV = count;
    MCPWMwx->MCPWM_RELOAD |= 0x0800U;
}

/**********************************************************************************************
Function: MH_PWM_Freq_Set
Description: 设置载频
Input: PWM载频控制计数器值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_PWM_Freq_Set(Q32U_ count)
{
    mcpwm_reg_t * MCPWMx = (mcpwm_reg_t *)(HAL_MOTOR_PWM_ADDRESS); 
    MCPWMx->MCPWM_MOD[HAL_PWM_COUNT].MOD = count;
}

/**********************************************************************************************
Function: MH_PWM_Preload_Enable
Description: 预装载使能
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_PWM_Preload_Enable(void)
{
    mcpwm_reg_t * MCPWMx = (mcpwm_reg_t *)(HAL_MOTOR_PWM_ADDRESS);
    MCPWMx->MCPWM_SYNC.SYNCOSWC = 1U;
    MCPWMx->MCPWM_SYNC.SWWRBUF = 0U;
    MCPWMx->MCPWM_SYNC.SWRSTCNT = 0U;
}

/**********************************************************************************************
Function: MH_PWM_Preload_Disable
Description: 预装载关闭
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_PWM_Preload_Disable(void)
{
    mcpwm_reg_t * MCPWMx = (mcpwm_reg_t *)(HAL_MOTOR_PWM_ADDRESS);
    MCPWMx->MCPWM_SYNC.SYNCOSWC = 1U;
    MCPWMx->MCPWM_SYNC.SWWRBUF = 1U;
    MCPWMx->MCPWM_SYNC.SWRSTCNT = 0U;
}

/**********************************************************************************************
Function: MH_POSITION_XX
Description: 定位脉冲，开三管
Input: PWM占空比控制计数器值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_POSITION_Up(Q32U_ duty)
{
    mcpwm_reg_t * MCPWMx = (mcpwm_reg_t *)(HAL_MOTOR_PWM_ADDRESS);  
    mcpwm_reg_w_t *MCPWMwx = (mcpwm_reg_w_t *)(HAL_MOTOR_PWM_ADDRESS); 
    MCPWMx->MCPWM_CV[HAL_PWM_UH_CHN].CV = duty;
    MCPWMx->MCPWM_CV[HAL_PWM_VH_CHN].CV = 0U;
    MCPWMx->MCPWM_CV[HAL_PWM_WH_CHN].CV = 0U;
    MCPWMwx->MCPWM_GLBCR &= (~(HAL_PWM_UL_CHN_EN|HAL_PWM_VH_CHN_EN|HAL_PWM_WH_CHN_EN));
    MCPWMwx->MCPWM_GLBCR |= (HAL_PWM_UH_CHN_EN|HAL_PWM_VL_CHN_EN|HAL_PWM_WL_CHN_EN);
    MCPWMwx->MCPWM_RELOAD |= 0x0700U;
}
static inline void MH_POSITION_Wn(Q32U_ duty)
{
    mcpwm_reg_t * MCPWMx = (mcpwm_reg_t *)(HAL_MOTOR_PWM_ADDRESS);  
    mcpwm_reg_w_t *MCPWMwx = (mcpwm_reg_w_t *)(HAL_MOTOR_PWM_ADDRESS);
	MCPWMx->MCPWM_CV[HAL_PWM_UH_CHN].CV = duty;
	MCPWMx->MCPWM_CV[HAL_PWM_VH_CHN].CV = duty;
	MCPWMx->MCPWM_CV[HAL_PWM_WH_CHN].CV = 0U;
    MCPWMwx->MCPWM_GLBCR &= (~(HAL_PWM_UL_CHN_EN|HAL_PWM_VL_CHN_EN|HAL_PWM_WH_CHN_EN));
    MCPWMwx->MCPWM_GLBCR |= (HAL_PWM_UH_CHN_EN|HAL_PWM_VH_CHN_EN|HAL_PWM_WL_CHN_EN);
    MCPWMwx->MCPWM_RELOAD |= 0x0700U;
}
static inline void MH_POSITION_Vp(Q32U_ duty)
{
    mcpwm_reg_t * MCPWMx = (mcpwm_reg_t *)(HAL_MOTOR_PWM_ADDRESS);  
    mcpwm_reg_w_t *MCPWMwx = (mcpwm_reg_w_t *)(HAL_MOTOR_PWM_ADDRESS);
	MCPWMx->MCPWM_CV[HAL_PWM_UH_CHN].CV = 0U;
	MCPWMx->MCPWM_CV[HAL_PWM_VH_CHN].CV = duty;
	MCPWMx->MCPWM_CV[HAL_PWM_WH_CHN].CV = 0U;
    MCPWMwx->MCPWM_GLBCR &= (~(HAL_PWM_UH_CHN_EN|HAL_PWM_VL_CHN_EN|HAL_PWM_WH_CHN_EN));
    MCPWMwx->MCPWM_GLBCR |= (HAL_PWM_UL_CHN_EN|HAL_PWM_VH_CHN_EN|HAL_PWM_WL_CHN_EN);
    MCPWMwx->MCPWM_RELOAD |= 0x0700U;
}
static inline void MH_POSITION_Un(Q32U_ duty)
{
    mcpwm_reg_t * MCPWMx = (mcpwm_reg_t *)(HAL_MOTOR_PWM_ADDRESS);  
    mcpwm_reg_w_t *MCPWMwx = (mcpwm_reg_w_t *)(HAL_MOTOR_PWM_ADDRESS);
	MCPWMx->MCPWM_CV[HAL_PWM_UH_CHN].CV = 0U;
	MCPWMx->MCPWM_CV[HAL_PWM_VH_CHN].CV = duty;
	MCPWMx->MCPWM_CV[HAL_PWM_WH_CHN].CV = duty;
    MCPWMwx->MCPWM_GLBCR &= (~(HAL_PWM_UH_CHN_EN|HAL_PWM_VL_CHN_EN|HAL_PWM_WL_CHN_EN));
    MCPWMwx->MCPWM_GLBCR |= (HAL_PWM_UL_CHN_EN|HAL_PWM_VH_CHN_EN|HAL_PWM_WH_CHN_EN);
    MCPWMwx->MCPWM_RELOAD |= 0x0700U;
}
static inline void MH_POSITION_Wp(Q32U_ duty)
{
    mcpwm_reg_t * MCPWMx = (mcpwm_reg_t *)(HAL_MOTOR_PWM_ADDRESS);  
    mcpwm_reg_w_t *MCPWMwx = (mcpwm_reg_w_t *)(HAL_MOTOR_PWM_ADDRESS);
	MCPWMx->MCPWM_CV[HAL_PWM_UH_CHN].CV = 0U;
	MCPWMx->MCPWM_CV[HAL_PWM_VH_CHN].CV = 0U;
	MCPWMx->MCPWM_CV[HAL_PWM_WH_CHN].CV = duty;
    MCPWMwx->MCPWM_GLBCR &= (~(HAL_PWM_UH_CHN_EN|HAL_PWM_VH_CHN_EN|HAL_PWM_WL_CHN_EN));
    MCPWMwx->MCPWM_GLBCR |= (HAL_PWM_UL_CHN_EN|HAL_PWM_VL_CHN_EN|HAL_PWM_WH_CHN_EN);
    MCPWMwx->MCPWM_RELOAD |= 0x0700U;
}
static inline void MH_POSITION_Vn(Q32U_ duty)
{
    mcpwm_reg_t * MCPWMx = (mcpwm_reg_t *)(HAL_MOTOR_PWM_ADDRESS);  
    mcpwm_reg_w_t *MCPWMwx = (mcpwm_reg_w_t *)(HAL_MOTOR_PWM_ADDRESS);
	MCPWMx->MCPWM_CV[HAL_PWM_UH_CHN].CV = duty;
	MCPWMx->MCPWM_CV[HAL_PWM_VH_CHN].CV = 0U;
	MCPWMx->MCPWM_CV[HAL_PWM_WH_CHN].CV = duty;
    MCPWMwx->MCPWM_GLBCR &= (~(HAL_PWM_UL_CHN_EN|HAL_PWM_VH_CHN_EN|HAL_PWM_WL_CHN_EN));
    MCPWMwx->MCPWM_GLBCR |= (HAL_PWM_UH_CHN_EN|HAL_PWM_VL_CHN_EN|HAL_PWM_WH_CHN_EN);
    MCPWMwx->MCPWM_RELOAD |= 0x0700U;
}

/**********************************************************************************************
Function: MH_HPWM_LPWM_XXXX
Description: 同步整流控制，UpVn为导通U上和V下，其他以此类推，HOpen为开三相上关三相下，LOpen为关三相上开三相下,CLOSE为六管全关
Input: PWM占空比控制计数器值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_HPWM_LPWM_UpVn(Q32U_ duty)
{
    mcpwm_reg_t * MCPWMx = (mcpwm_reg_t *)(HAL_MOTOR_PWM_ADDRESS);  
    mcpwm_reg_w_t *MCPWMwx = (mcpwm_reg_w_t *)(HAL_MOTOR_PWM_ADDRESS); 
	MCPWMx->MCPWM_CV[HAL_PWM_UH_CHN].CV = duty;
	MCPWMx->MCPWM_CV[HAL_PWM_VH_CHN].CV = 0U;
	MCPWMx->MCPWM_CV[HAL_PWM_WH_CHN].CV = 0U;
    MCPWMwx->MCPWM_GLBCR &= (~(HAL_PWM_WH_CHN_EN|HAL_PWM_WL_CHN_EN));
    MCPWMwx->MCPWM_GLBCR |= (HAL_PWM_UH_CHN_EN|HAL_PWM_UL_CHN_EN|HAL_PWM_VH_CHN_EN|HAL_PWM_VL_CHN_EN);
    MCPWMwx->MCPWM_RELOAD |= 0x0700U;
    MCPWMx->MCPWM_SYNC.SWTRIG = 1U;
}
static inline void MH_HPWM_LPWM_UpWn(Q32U_ duty)
{
    mcpwm_reg_t * MCPWMx = (mcpwm_reg_t *)(HAL_MOTOR_PWM_ADDRESS);  
    mcpwm_reg_w_t *MCPWMwx = (mcpwm_reg_w_t *)(HAL_MOTOR_PWM_ADDRESS);
	MCPWMx->MCPWM_CV[HAL_PWM_UH_CHN].CV = duty;
	MCPWMx->MCPWM_CV[HAL_PWM_VH_CHN].CV = 0U;
	MCPWMx->MCPWM_CV[HAL_PWM_WH_CHN].CV = 0U;
    MCPWMwx->MCPWM_GLBCR &= (~(HAL_PWM_VH_CHN_EN|HAL_PWM_VL_CHN_EN));
    MCPWMwx->MCPWM_GLBCR |= (HAL_PWM_UH_CHN_EN|HAL_PWM_UL_CHN_EN|HAL_PWM_WH_CHN_EN|HAL_PWM_WL_CHN_EN);
    MCPWMwx->MCPWM_RELOAD |= 0x0700U;
    MCPWMx->MCPWM_SYNC.SWTRIG = 1U;
}
static inline void MH_HPWM_LPWM_VpWn(Q32U_ duty)
{
    mcpwm_reg_t * MCPWMx = (mcpwm_reg_t *)(HAL_MOTOR_PWM_ADDRESS);  
    mcpwm_reg_w_t *MCPWMwx = (mcpwm_reg_w_t *)(HAL_MOTOR_PWM_ADDRESS); 
	MCPWMx->MCPWM_CV[HAL_PWM_UH_CHN].CV = 0U;
	MCPWMx->MCPWM_CV[HAL_PWM_VH_CHN].CV = duty;
	MCPWMx->MCPWM_CV[HAL_PWM_WH_CHN].CV = 0U;
    MCPWMwx->MCPWM_GLBCR &= (~(HAL_PWM_UH_CHN_EN|HAL_PWM_UL_CHN_EN));
    MCPWMwx->MCPWM_GLBCR |= (HAL_PWM_VH_CHN_EN|HAL_PWM_VL_CHN_EN|HAL_PWM_WH_CHN_EN|HAL_PWM_WL_CHN_EN);
    MCPWMwx->MCPWM_RELOAD |= 0x0700U;
    MCPWMx->MCPWM_SYNC.SWTRIG = 1U;
}
static inline void MH_HPWM_LPWM_VpUn(Q32U_ duty)
{
    mcpwm_reg_t * MCPWMx = (mcpwm_reg_t *)(HAL_MOTOR_PWM_ADDRESS);  
    mcpwm_reg_w_t *MCPWMwx = (mcpwm_reg_w_t *)(HAL_MOTOR_PWM_ADDRESS);
	MCPWMx->MCPWM_CV[HAL_PWM_UH_CHN].CV = 0U;
	MCPWMx->MCPWM_CV[HAL_PWM_VH_CHN].CV = duty;
	MCPWMx->MCPWM_CV[HAL_PWM_WH_CHN].CV = 0U;
    MCPWMwx->MCPWM_GLBCR &= (~(HAL_PWM_WH_CHN_EN|HAL_PWM_WL_CHN_EN));
    MCPWMwx->MCPWM_GLBCR |= (HAL_PWM_UH_CHN_EN|HAL_PWM_UL_CHN_EN|HAL_PWM_VH_CHN_EN|HAL_PWM_VL_CHN_EN);
    MCPWMwx->MCPWM_RELOAD |= 0x0700U;
    MCPWMx->MCPWM_SYNC.SWTRIG = 1U;
}
static inline void MH_HPWM_LPWM_WpUn(Q32U_ duty)
{
    mcpwm_reg_t * MCPWMx = (mcpwm_reg_t *)(HAL_MOTOR_PWM_ADDRESS);  
    mcpwm_reg_w_t *MCPWMwx = (mcpwm_reg_w_t *)(HAL_MOTOR_PWM_ADDRESS);
	MCPWMx->MCPWM_CV[HAL_PWM_UH_CHN].CV = 0U;
	MCPWMx->MCPWM_CV[HAL_PWM_VH_CHN].CV = 0U;
	MCPWMx->MCPWM_CV[HAL_PWM_WH_CHN].CV = duty;
    MCPWMwx->MCPWM_GLBCR &= (~(HAL_PWM_VH_CHN_EN|HAL_PWM_VL_CHN_EN));
    MCPWMwx->MCPWM_GLBCR |= (HAL_PWM_UH_CHN_EN|HAL_PWM_UL_CHN_EN|HAL_PWM_WH_CHN_EN|HAL_PWM_WL_CHN_EN);
    MCPWMwx->MCPWM_RELOAD |= 0x0700U;
    MCPWMx->MCPWM_SYNC.SWTRIG = 1U;
}
static inline void MH_HPWM_LPWM_WpVn(Q32U_ duty)
{
    mcpwm_reg_t * MCPWMx = (mcpwm_reg_t *)(HAL_MOTOR_PWM_ADDRESS);  
    mcpwm_reg_w_t *MCPWMwx = (mcpwm_reg_w_t *)(HAL_MOTOR_PWM_ADDRESS);
	MCPWMx->MCPWM_CV[HAL_PWM_UH_CHN].CV = 0U;
	MCPWMx->MCPWM_CV[HAL_PWM_VH_CHN].CV = 0U;
	MCPWMx->MCPWM_CV[HAL_PWM_WH_CHN].CV = duty;
    MCPWMwx->MCPWM_GLBCR &= (~(HAL_PWM_UH_CHN_EN|HAL_PWM_UL_CHN_EN));
    MCPWMwx->MCPWM_GLBCR |= (HAL_PWM_VH_CHN_EN|HAL_PWM_VL_CHN_EN|HAL_PWM_WH_CHN_EN|HAL_PWM_WL_CHN_EN);
    MCPWMwx->MCPWM_RELOAD |= 0x0700U;
    MCPWMx->MCPWM_SYNC.SWTRIG = 1U;
}
static inline void MH_HPWM_LPWM_HOpen(Q32U_ duty)
{
    mcpwm_reg_t * MCPWMx = (mcpwm_reg_t *)(HAL_MOTOR_PWM_ADDRESS);  
    mcpwm_reg_w_t *MCPWMwx = (mcpwm_reg_w_t *)(HAL_MOTOR_PWM_ADDRESS);
	MCPWMx->MCPWM_CV[HAL_PWM_UH_CHN].CV = duty;
	MCPWMx->MCPWM_CV[HAL_PWM_VH_CHN].CV = duty;
	MCPWMx->MCPWM_CV[HAL_PWM_WH_CHN].CV = duty;
    MCPWMwx->MCPWM_GLBCR &= (~(HAL_PWM_DN_CHN));
    MCPWMwx->MCPWM_GLBCR |= HAL_PWM_UP_CHN;
    MCPWMwx->MCPWM_RELOAD |= 0x0700U;
}
static inline void MH_HPWM_LPWM_LOpen(Q32U_ duty)
{
    mcpwm_reg_t * MCPWMx = (mcpwm_reg_t *)(HAL_MOTOR_PWM_ADDRESS);  
    mcpwm_reg_w_t *MCPWMwx = (mcpwm_reg_w_t *)(HAL_MOTOR_PWM_ADDRESS);
	MCPWMx->MCPWM_CV[HAL_PWM_UH_CHN].CV = duty;
	MCPWMx->MCPWM_CV[HAL_PWM_VH_CHN].CV = duty;
	MCPWMx->MCPWM_CV[HAL_PWM_WH_CHN].CV = duty;
    MCPWMwx->MCPWM_GLBCR &= (~(HAL_PWM_UP_CHN));
    MCPWMwx->MCPWM_GLBCR |= HAL_PWM_DN_CHN;
    MCPWMwx->MCPWM_RELOAD |= 0x0700U;
}
static inline void MH_HPWM_LPWM_Close(void)
{
    mcpwm_reg_t * MCPWMx = (mcpwm_reg_t *)(HAL_MOTOR_PWM_ADDRESS);  
    mcpwm_reg_w_t *MCPWMwx = (mcpwm_reg_w_t *)(HAL_MOTOR_PWM_ADDRESS);
	MCPWMx->MCPWM_CV[HAL_PWM_UH_CHN].CV = 0U;
	MCPWMx->MCPWM_CV[HAL_PWM_VH_CHN].CV = 0U;
	MCPWMx->MCPWM_CV[HAL_PWM_WH_CHN].CV = 0U;
    MCPWMwx->MCPWM_GLBCR &= (~(HAL_PWM_ALL_CHN));
    MCPWMwx->MCPWM_RELOAD |= 0x0700U;
}

/**********************************************************************************************
Function: MH_PWM_Count_Read
Description: 读取当前PWM计数器值
Input: 无
Output: 无
Input_Output: 无
Return: PWM计数器值
Author: CJYS
***********************************************************************************************/
static inline Q32U_ MH_PWM_Count_Read(void)
{
    mcpwm_reg_t * MCPWMx = (mcpwm_reg_t *)(HAL_MOTOR_PWM_ADDRESS);  
    return MCPWMx->MCPWM_CNT[0].CNT;
}

/**********************************************************************************************
Function: MH_HALL_TIM_Count_Read
Description: 读取当前HALL换向计数器值
Input: 无
Output: 无
Input_Output: 无
Return: ALL换向计数器值
Author: CJYS
***********************************************************************************************/
static inline Q32U_ MH_HALL_TIM_Count_Read(void)
{
    stim_reg_w_t * STIMx_w = (stim_reg_w_t *)(HAL_MOTOR_STIM_ADDRESS);
    return STIMx_w->STIM_CNTn[1];
}

/**********************************************************************************************
Function: MH_Switch_TIM_Delay
Description: 设置延迟换向计数器值，进入中断
Input: 换向计数器值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_Switch_TIM_Delay(Q32U_ count)
{
    stim_reg_w_t * STIMx_w = (stim_reg_w_t *)(HAL_MOTOR_STIM_ADDRESS);
    stim_reg_t * STIMx = (stim_reg_t *)(HAL_MOTOR_STIM_ADDRESS);
    STIMx_w->STIM_CNTn[0] = 0U;
    STIMx_w->STIM_CVn[0] = count;
    STIMx->STIM_SCn[0].EN = 1U;
}

/**********************************************************************************************
Function: MH_Switch_TIM_Stop
Description: 停止延迟换向计数器值，屏蔽中断
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_Switch_TIM_Stop(void)
{
    stim_reg_w_t * STIMx_w = (stim_reg_w_t *)(HAL_MOTOR_STIM_ADDRESS);
    stim_reg_t * STIMx = (stim_reg_t *)(HAL_MOTOR_STIM_ADDRESS);
    STIMx->STIM_SCn[0].EN = 0U;
    STIMx_w->STIM_CNTn[0] = 0U;
}

/**********************************************************************************************
Function: MH_ADC_IntFlag_Clear
Description: DMA的0号通道中断标志位清除
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_ADC_IntFlag_Clear(void)
{
    dma_reg_w_t* dmaRegWPtr = (dma_reg_w_t *) DMA_BASE_ADDR;
    dmaRegWPtr->DMA_GCC = 0x00808080U | ((((Q32U_)0U << 16U) | ((Q32U_)0U << 24U)) & 0x0F000000U);
}

/**********************************************************************************************
Function: MH_PWMCP_IntFlag_Clear
Description: MCPWM比较中断标志位清除
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
static inline void MH_PWMCP_IntFlag_Clear(void)
{
    mcpwm_reg_t * MCPWMx = (mcpwm_reg_t *)(HAL_MOTOR_PWM_ADDRESS);  
    MCPWMx->MCPWM_CFG[6].CHF = 0U;
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

#endif /* MotorHal_H */
