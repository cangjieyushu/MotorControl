/**************************************************************************************************/
/**
* @copyright : 
**************************************************************************************************/
#include "MotorHal.h"

ST_MH_ADC_DATA  Adc_Data;

Q32U_ Q32U_ADC_Data_Lsb[20] = {0};

Ram_Func void MH_Read_ADC_Data(ST_MH_ADC_DATA *pADC_DATA)
{
    adc_reg_t * ADCx = (adc_reg_t *)(ADC0_BASE_ADDR);
    while(0U != ADCx->ADC_FCTRL.FCOUNT)
    {
        (void)ADCx->ADC_DATA_RD.ADC_DATA_RD;
    }
    
#if(HAL_CURRENT_SAMPLE_MODE == HAL_THREE_SHUNT)
    
    Q32U_ADC_Data_Lsb[0] = Hal_AdcLoopData[0] & 0x00000FFF;
    Q32U_ADC_Data_Lsb[1] = Hal_AdcLoopData[1] & 0x00000FFF;
    Q32U_ADC_Data_Lsb[2] = Hal_AdcLoopData[2] & 0x00000FFF;
    
    pADC_DATA->Ia = (float)Q32U_ADC_Data_Lsb[0];
    pADC_DATA->Ib = (float)Q32U_ADC_Data_Lsb[1];
    pADC_DATA->Ic = (float)Q32U_ADC_Data_Lsb[2];
    
#else
    
    Q32U_ADC_Data_Lsb[0] = Hal_AdcMapData[0] & 0x00000FFFU;
    Q32U_ADC_Data_Lsb[1] = Hal_AdcMapData[1] & 0x00000FFFU;
    
    pADC_DATA->Ishunt_1 = (float)Q32U_ADC_Data_Lsb[1];
    pADC_DATA->Ishunt_2 = (float)Q32U_ADC_Data_Lsb[0];
#endif
}


static bool Hal_IsPwmEnabled = true;
Ram_Func void MH_PWM_Channel_Output_Enable(MCPWM_ChannelId_t channelId)
{
    mcpwm_reg_w_t * MCPWMwx = (mcpwm_reg_w_t *)(MCPWM1_BASE_ADDR);
    Q32U_ regVal = MCPWMwx->MCPWM_GLBCR;
    
    MCPWMwx->MCPWM_GLBCR = regVal | (0x1UL << ((Q32U_)channelId));
}
Ram_Func void MH_PWM_Output_Enable(void) 
{
    MH_PWM_Channel_Output_Enable(HAL_PWM_UH_CHN);
    MH_PWM_Channel_Output_Enable(HAL_PWM_UL_CHN);
    MH_PWM_Channel_Output_Enable(HAL_PWM_VH_CHN);
    MH_PWM_Channel_Output_Enable(HAL_PWM_VL_CHN);
    MH_PWM_Channel_Output_Enable(HAL_PWM_WH_CHN);
    MH_PWM_Channel_Output_Enable(HAL_PWM_WL_CHN);
}

Ram_Func void MH_PWM_Channel_Output_Disable(MCPWM_ChannelId_t channelId)
{
    mcpwm_reg_w_t * MCPWMwx = (mcpwm_reg_w_t *)(MCPWM1_BASE_ADDR);
    Q32U_ regVal = MCPWMwx->MCPWM_GLBCR;
    
    MCPWMwx->MCPWM_GLBCR = regVal & (~(0x1UL << ((Q32U_)channelId)));
}
Ram_Func void MH_PWM_Output_Disable(void)
{
    MH_PWM_Channel_Output_Disable(HAL_PWM_UH_CHN);
    MH_PWM_Channel_Output_Disable(HAL_PWM_VH_CHN);
    MH_PWM_Channel_Output_Disable(HAL_PWM_WH_CHN);
    MH_PWM_Channel_Output_Disable(HAL_PWM_UL_CHN);
    MH_PWM_Channel_Output_Disable(HAL_PWM_VL_CHN);
    MH_PWM_Channel_Output_Disable(HAL_PWM_WL_CHN);
}

Ram_Func void MH_PWM_Output_En(bool IsEnabled)
{
    if(IsEnabled && (!Hal_IsPwmEnabled)) 
    {
        MH_PWM_Output_Enable();    
        Hal_IsPwmEnabled = true;
    }
    else if((!IsEnabled) && Hal_IsPwmEnabled)
    {
        MH_PWM_Output_Disable();
        Hal_IsPwmEnabled = false;
    }
    else{}
}

Ram_Func void MH_PWM_Duty_Set_Three(float Ta, float Tb, float Tc)
{
    mcpwm_reg_t * MCPWMx = (mcpwm_reg_t *)(MCPWM1_BASE_ADDR);  
    mcpwm_reg_w_t *MCPWMwx = (mcpwm_reg_w_t *)(MCPWM1_BASE_ADDR);
    
    MCPWMx->MCPWM_CV[HAL_PWM_UH_CHN].CV = (Q32U_)(Ta*HAL_PWM_ALL_COUNT_F);
    MCPWMx->MCPWM_CV[HAL_PWM_VH_CHN].CV = (Q32U_)(Tb*HAL_PWM_ALL_COUNT_F);
    MCPWMx->MCPWM_CV[HAL_PWM_WH_CHN].CV = (Q32U_)(Tc*HAL_PWM_ALL_COUNT_F);
    MCPWMwx->MCPWM_RELOAD |= 0x0700U;
}

Ram_Func void MH_PWM_Duty_Set_One(float Ta1, float Ta2, float Tb1, float Tb2, float Tc1, float Tc2)
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

Ram_Func void MH_ADC_TrigTime_Set(float Ch1, float Ch2)
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
    
    while(1U == (Q08U_)TDGx->TDG_CTRL1.CFGUP)
    {
        
    }
}

Ram_Func void MH_DMA0_ClearChannel0Int(void)
{
    dma_reg_w_t* dmaRegWPtr = (dma_reg_w_t *) DMA_BASE_ADDR;
    dmaRegWPtr->DMA_GCC = 0x00808080U | 
                    ((((Q32U_)DMA_CHANNEL0 << 16U) | 
                       ((Q32U_)DMA_CHANNEL0 << 24U)) & 
                      0x0F000000U);
}

Q32U_ MH_Read_Hall_Count(void)
{
    stim_reg_w_t* stimRegWPtr = (stim_reg_w_t*)STIM_BASE_ADDR;
    return ((Q32U_)stimRegWPtr->STIM_CNTn[HAL_STIM_HALL]);
}
