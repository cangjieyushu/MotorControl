/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/

#include "BSP_ADC.h"

void BSP_ADC_Init(isr_cb_t *ADCDoneCbf)
{
    ADC_Config_t SubcaseAdcCfg=
    {
        /* resolution */
        ADC_RESOLUTION_12BIT, 
        /* vref */    
        ADC_VREF_INTERNAL,  
        /* trigger mode */      
        ADC_TDG_TRIGGER,        
        /* conversion mode */  
        ADC_CONVERSION_SINGLE, 
        /* average disabled */   
        ADC_AVGS_DISABLED,     
        /* Set sample interval > 700ns */   
        45,
    };
    
    ADC_ChannelConfig_t AdcChannelCfg1 = 
    {
        ADC_SINGLE_MODE,  /* Single-Ended Mode Selected */
        HAL_ADC_UBEMF_CHN,     /* Single mode, channel[12] and vssa */
        ADC_N_NONE,       /* Single mode, N-channel donn't need to configure */                  
    };
    
    ADC_ChannelConfig_t AdcChannelCfg2 = 
    {
        ADC_SINGLE_MODE,  /* Single-Ended Mode Selected */
        HAL_ADC_VBEMF_CHN,       /* Single mode, channel[12] and vssa */
        ADC_N_NONE,       /* Single mode, N-channel donn't need to configure */ 
    };
    
    ADC_ChannelConfig_t AdcChannelCfg3 = 
    {
        ADC_SINGLE_MODE,  /* Single-Ended Mode Selected */
        HAL_ADC_WBEMF_CHN,       /* Single mode, channel[12] and vssa */
        ADC_N_NONE,       /* Single mode, N-channel donn't need to configure */ 
    };
    
    ADC_ChannelConfig_t AdcChannelCfg4 = 
    {
        ADC_SINGLE_MODE,  /* Single-Ended Mode Selected */
        HAL_ADC_IPHASE_CHN,       /* Single mode, channel[12] and vssa */
        ADC_N_NONE,       /* Single mode, N-channel donn't need to configure */ 
    };
    
    ADC_ChannelConfig_t AdcChannelCfg5 = 
    {
        ADC_SINGLE_MODE,  /* Single-Ended Mode Selected */
        HAL_ADC_VBUS_CHN,       /* Single mode, channel[12] and vssa */
        ADC_N_NONE,       /* Single mode, N-channel donn't need to configure */ 
    };
    
    ADC_ChannelConfig_t AdcChannelCfg6 = 
    {
        ADC_SINGLE_MODE,  /* Single-Ended Mode Selected */
        HAL_ADC_VR_CHN,       /* Single mode, channel[12] and vssa */
        ADC_N_NONE,       /* Single mode, N-channel donn't need to configure */ 
    };
    
    ADC_TDGTriggerConfig_t  AdcTriggerConfig = 
    {
        /* Loop mode Selected */  
        ADC_LOOP_MODE, 
        /* CMD0: channel 15; */          
        HAL_ADC_UBEMF_CHN,       
        /* CMD1: channel 14; */      
        HAL_ADC_VBEMF_CHN,        
        /* CMD2: channel 13; */       
        HAL_ADC_WBEMF_CHN,     
        /* CMD3: channel 12; */           
        HAL_ADC_IPHASE_CHN,         
        /* CMD4: channel 7; */          
        HAL_ADC_VBUS_CHN,   
        /* CMD5: channel 7; all CMDs can be Configured as different channels */            
        HAL_ADC_VR_CHN,                              
    };
    
    /* mod value, single, divide4, SW trig, clear to mod */
    TDG_InitConfig_t Config=
    {
        100U, TDG_COUNT_SINGLE, TDG_CLK_DIVIDE_2, TDG_TRIG_SW, TDG_UPDATE_IMMEDIATELY, TDG_CLEAR_MODULATOR
    };
    
    /* 001*1/64Tclock */
    TDG_DelayOutputConfig_t Doconfig =         
    {
        TDG_DO_0, 
        10U, 
        ENABLE,
    };
    
    TDG_ChannelConfig_t Chconfig =
    {
        TDG_CHANNEL_0, 
        0U, 
        1U, 
        &Doconfig,
    };
    
    /* Reset ADC */
    SYSCTRL_ResetModule(SYSCTRL_ADC0);
    /* Enable ADC clock */
    SYSCTRL_EnableModule(SYSCTRL_ADC0);
    /* adc pinmux */ 
    /* PTB22/ADC0_CH19 for motor V_current */      
    PORT_PinmuxConfig(HAL_ADC_UBEMF_PORT, HAL_ADC_UBEMF_PIN, HAL_ADC_UBEMF_PINMUX);
    /* PTC17/ADC0_CH15 for motor bus volatage */   
    PORT_PinmuxConfig(HAL_ADC_VBEMF_PORT, HAL_ADC_VBEMF_PIN, HAL_ADC_VBEMF_PINMUX); 
    /* PTB22/ADC0_CH19 for motor V_current */      
    PORT_PinmuxConfig(HAL_ADC_WBEMF_PORT, HAL_ADC_WBEMF_PIN, HAL_ADC_WBEMF_PINMUX);
    /* PTC17/ADC0_CH15 for motor bus volatage */   
    PORT_PinmuxConfig(HAL_ADC_IPHASE_PORT, HAL_ADC_IPHASE_PIN, HAL_ADC_IPHASE_PINMUX); 
    /* PTB22/ADC0_CH19 for motor V_current */      
    PORT_PinmuxConfig(HAL_ADC_VBUS_PORT, HAL_ADC_VBUS_PIN, HAL_ADC_VBUS_PINMUX);
    /* PTC17/ADC0_CH15 for motor bus volatage */   
    PORT_PinmuxConfig(HAL_ADC_VR_PORT, HAL_ADC_VR_PIN, HAL_ADC_VR_PINMUX); 
    /* Reset software */
    ADC_SoftwareReset(HAL_MOTOR_ADC);
    
    /* Initialize ADC */
    ADC_Init(HAL_MOTOR_ADC, &SubcaseAdcCfg);
    /* Redefine the depth the function */
    ADC_FifoDepthRedefine(HAL_MOTOR_ADC, HAL_MOTOR_ADC_NUM); 
    /* Set ADC watermark */
    /* fifo WM > 3, that is when WM=4,flag will be set */
    ADC_FifoWatermarkConfig(HAL_MOTOR_ADC, (HAL_MOTOR_ADC_NUM-1U));
    /* Configure input channel */
    ADC_ChannelConfig(HAL_MOTOR_ADC, &AdcChannelCfg1);
    ADC_ChannelConfig(HAL_MOTOR_ADC, &AdcChannelCfg2);
    ADC_ChannelConfig(HAL_MOTOR_ADC, &AdcChannelCfg3);
    ADC_ChannelConfig(HAL_MOTOR_ADC, &AdcChannelCfg4);
    ADC_ChannelConfig(HAL_MOTOR_ADC, &AdcChannelCfg5);
    ADC_ChannelConfig(HAL_MOTOR_ADC, &AdcChannelCfg6);
    /* Mask FIFO watermark interrupt */
    ADC_IntMask(HAL_MOTOR_ADC, ADC_FWM_INT, UNMASK);   
    
    /* Set trigger mode */
    ADC_TDGTriggerConfig(HAL_MOTOR_ADC, &AdcTriggerConfig);
    /* Clear TCOMP interrupt */
    ADC_IntClear(HAL_MOTOR_ADC, ADC_FWM_INT);
    ADC_IntClear(HAL_MOTOR_ADC, ADC_TCOMP_INT);
    /* Enable ADC module */
    ADC_Enable(HAL_MOTOR_ADC);
    /* Enable ADC dma request */
    ADC_DmaRequestCmd(HAL_MOTOR_ADC, DISABLE);
    
    /*Enable TDG module */
    SYSCTRL_EnableModule(SYSCTRL_TDG0);
    /* Initialize TDG */
    TDG_InitConfig(HAL_MOTOR_TDG, &Config);
    /* Set TDG delay output */
    TDG_ChannelDelayOutputConfig(HAL_MOTOR_TDG, &Chconfig, ENABLE);
    
    /* enable TDG */
    TDG_Enable(HAL_MOTOR_TDG, ENABLE);
    /* Load channel Configuration */
    TDG_LoadCmd(HAL_MOTOR_TDG);
    
    ADC_InstallCallBackFunc(HAL_MOTOR_ADC, ADC_FWM_INT, ADCDoneCbf);
    
}
