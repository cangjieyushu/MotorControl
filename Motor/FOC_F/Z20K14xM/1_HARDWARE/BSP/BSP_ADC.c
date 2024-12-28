/**************************************************************************************************
*     File Name :                        BSP_ADC.c
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             ADC初始化及应用层接口源文件
**************************************************************************************************/
#include "BSP_ADC.h"

/**********************************************************************************************
Function: BSP_ADC_Init
Description: 电机控制用ADC初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_ADC_Init(void)
{
    static adc_reg_t * ADC0 = (adc_reg_t *)(ADC0_BASE_ADDR);       /*PRQA S 0303*/  
    
#if (HAL_CURRENT_SAMPLE_MODE == HAL_THREE_SHUNT)
    
    ADC_Config_t SubcaseAdcCfg=
    {
        /* resolution  */
        ADC_RESOLUTION_12BIT,
        /* vref */     
        ADC_VREF_INTERNAL,
        /* trigger mode */        
        ADC_TDG_TRIGGER,
        /* conversion mode */          
        ADC_CONVERSION_SINGLE,
        /* average disabled */    
        ADC_AVGS_DISABLED,
        /* Set sample interval > 500ns */        
        28,
        /* Set ADC Stable time interval */                       
        28,                       
    }; 
   
    ADC_ChannelConfig_t AdcChannelCfg1 = 
    {
        /* Single-Ended Mode Selected */
        ADC_SINGLE_MODE,
        /* Single mode, channel[13] and vssa */          
        HAL_ADC_IU_CHN,
        /* Single mode, N-channel donn't need to configure */               
        ADC_N_NONE,               
    };
 
    ADC_ChannelConfig_t AdcChannelCfg2 = 
    {
        /* Single-Ended Mode Selected */
        ADC_SINGLE_MODE,
        /* Single mode, channel[19] and vssa */          
        HAL_ADC_IV_CHN,
        /* Single mode, N-channel donn't need to configure */               
        ADC_N_NONE,               
    };
  
    ADC_ChannelConfig_t AdcChannelCfg3 = 
    {
        /* Single-Ended Mode Selected */
        ADC_SINGLE_MODE,
        /* Single mode, channel[14] and vssa */          
        HAL_ADC_IW_CHN,
        /* Single mode, N-channel donn't need to configure */               
        ADC_N_NONE,               
    };
  
    ADC_ChannelConfig_t AdcChannelCfg4 = 
    {
        /* Single-Ended Mode Selected */
        ADC_SINGLE_MODE,
        /* Single mode, channel[15] and vssa */          
        HAL_ADC_VBUS_CHN,
        /* Single mode, N-channel donn't need to configure */             
        ADC_N_NONE,               
    };  
  
    ADC_TDGTriggerConfig_t  AdcTriggerConfig = 
    {
        /* Loop mode Selected */
        ADC_LOOP_MODE,
        /* CMD0: channel 15; */                
        HAL_ADC_IU_CHN,
        /* CMD1: channel 14; */               
        HAL_ADC_IV_CHN,
        /* CMD2: channel 13; */               
        HAL_ADC_IW_CHN,
        /* CMD3: channel 12; */               
        HAL_ADC_VBUS_CHN,
        /* CMD4: channel 7; */                  
        ADC_P_CH7,
        /* CMD5: channel 7; all CMDs can be configured as different channels */                
        ADC_P_CH7,
        /* Loop depth */                
        4,                   
    };
    
    /* mod value, single, divide4, SW trig, clear to mod */
    TDG_InitConfig_t Config=
    {
        HAL_PWM_SET_COUNT_U*2U, TDG_COUNT_SINGLE, TDG_CLK_DIVIDE_1, TDG_TRIG_EXTERNAL, TDG_UPDATE_IMMEDIATELY, TDG_CLEAR_DELAY
    };
  
    /* 001*1/64Tclock */
    TDG_DelayOutputConfig_t Doconfig =         
    {
        TDG_DO_0, (HAL_PWM_SET_COUNT_U*2U - (HAL_ADC_SAMPLE_VALUE-HAL_ADC_DELAY_VALUE)/2U), ENABLE
    };
  
    const TDG_ChannelConfig_t Chconfig =
    {
        TDG_CHANNEL_0, 0U, 1U, &Doconfig
    };
  

    /* Reset ADC */
    SYSCTRL_ResetModule(SYSCTRL_ADC0);
    /* Enable ADC clock */
    SYSCTRL_EnableModule(SYSCTRL_ADC0);
    /* adc pinmux */
    /* PTC15/ADC0_CH13 for motor U_current */
    PORT_PinmuxConfig(HAL_ADC_IU_PORT, HAL_ADC_IU_PIN, HAL_ADC_IU_PINMUX);
    /* PTB22/ADC0_CH19 for motor V_current */         
    PORT_PinmuxConfig(HAL_ADC_IV_PORT, HAL_ADC_IV_PIN, HAL_ADC_IV_PINMUX);
    /* PTC16/ADC0_CH16 for motor W_current */       
    PORT_PinmuxConfig(HAL_ADC_IW_PORT, HAL_ADC_IW_PIN, HAL_ADC_IW_PINMUX);
    /* PTC17/ADC0_CH15 for motor bus volatage */       
    PORT_PinmuxConfig(HAL_ADC_VBUS_PORT, HAL_ADC_VBUS_PIN, HAL_ADC_VBUS_PINMUX); 
    
    /* Reset software */
    ADC_SoftwareReset(HAL_ADC_ID);
    /* Initialize ADC */
    ADC_Init(HAL_ADC_ID,&SubcaseAdcCfg);
    /* Redefine the depth the function */    
    ADC_FifoDepthRedefine(HAL_ADC_ID,4); 
    /* Set ADC watermark */
    /* fifo WM > 3, that is when WM=4,flag will be set */
    ADC_FifoWatermarkConfig(HAL_ADC_ID,3);                               
    /* Configure input channel */
    ADC_ChannelConfig(HAL_ADC_ID, &AdcChannelCfg1);
    ADC_ChannelConfig(HAL_ADC_ID, &AdcChannelCfg2);
    ADC_ChannelConfig(HAL_ADC_ID, &AdcChannelCfg3);
    ADC_ChannelConfig(HAL_ADC_ID, &AdcChannelCfg4);     
    /* Mask FIFO watermark interrupt */
    ADC_IntMask(HAL_ADC_ID,ADC_FWM_INT, MASK);   
    
    /* Set trigger mode */
    ADC_TDGTriggerConfig(HAL_ADC_ID,&AdcTriggerConfig);
    /* Clear TCOMP interrupt */
    ADC_IntClear(HAL_ADC_ID,ADC_TCOMP_INT);
    /* Enable ADC module */
    ADC_Enable(HAL_ADC_ID);
    /* Enable ADC dma request */
    ADC_DmaRequestCmd(HAL_ADC_ID, ENABLE);
    
    
    /* Initialize TDG */
    TDG_InitConfig(HAL_TGD_ID, &Config);
    /* Set TDG delay output */
    TDG_ChannelDelayOutputConfig(HAL_TGD_ID, &Chconfig, ENABLE);
    /* enable TDG */
    TDG_Enable(HAL_TGD_ID, ENABLE);    
    /* Load channel Configuration */
    TDG_LoadCmd(HAL_TGD_ID); 

    ADC0->ADC_CTRL.TRIG_MODE_ENABLE = 0;
    ADC0->ADC_CFG.CHSELP = (uint32_t)HAL_ADC_VBUS_CHN;             /* config channel */
    ADC0->ADC_IE.TCOM_IE = 1U;                                         /* enable complete Int */
    ADC0->ADC_SWTRIG.ADC_SWTRIG = 1U;                                  /* start conversion */
    while (0U == ADC0->ADC_STAT.TCOMP_INT)
    {
    }

    ADC0->ADC_IE.TCOM_IE = 0U;                                         /* disable complete Int */
    ADC0->ADC_STAT.TCOMP_INT = 1U;                                     /* clear flag */
    ADC0->ADC_CTRL.TRIG_MODE_ENABLE = 1;                              /* change to tdg trigger */
    
    /* Clear FIFO */
    while (0U != ADC0->ADC_FCTRL.FCOUNT)
    {
        (void)ADC0->ADC_DATA_RD.ADC_DATA_RD;
    }    
    
#else

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
        /* Set sample interval > 500ns */   
        28,                 
        /* Set ADC Stable time interval */      
        28,                       
    }; 
   
    ADC_ChannelConfig_t AdcChannelCfg1 = 
    {
        /* Single-Ended Mode Selected */
        ADC_SINGLE_MODE,  
        /* Single mode, channel[13] and vssa */        
        HAL_ADC_IU_CHN,  
        /* Single mode, N-channel donn't need to Configure */             
        ADC_N_NONE,               
    };
 
    ADC_ChannelConfig_t AdcChannelCfg2 = 
    {
        /* Single-Ended Mode Selected */
        ADC_SINGLE_MODE,
        /* Single mode, channel[19] and vssa */          
        HAL_ADC_IV_CHN,     
        /* Single mode, N-channel donn't need to Configure */          
        ADC_N_NONE,               
    };
  
    ADC_ChannelConfig_t AdcChannelCfg3 = 
    {
        /* Single-Ended Mode Selected */
        ADC_SINGLE_MODE,         
        /* Single mode, channel[14] and vssa */ 
        HAL_ADC_IW_CHN,    
        /* Single mode, N-channel donn't need to Configure */           
        ADC_N_NONE,               
    };
  
    ADC_ChannelConfig_t AdcChannelCfg4 = 
    {
        /* Single-Ended Mode Selected */
        ADC_SINGLE_MODE,  
        /* Single mode, channel[15] and vssa */        
        HAL_ADC_VBUS_CHN,   
        /* Single mode, N-channel donn't need to Configure */          
        ADC_N_NONE,               
    };  
  
    ADC_TDGTriggerConfig_t  AdcTriggerConfig = 
    {
        /* Loop mode Selected */  
        ADC_MAPPING_MODE,  
        /* CMD1: channel 14; */      
        HAL_ADC_IV_CHN,        
        /* CMD2: channel 13; */       
        HAL_ADC_IV_CHN,    
        /* CMD0: channel 15; */          
        HAL_ADC_VBUS_CHN,       
        /* CMD3: channel 12; */           
        HAL_ADC_IV_CHN,         
        /* CMD4: channel 7; */          
        HAL_ADC_IV_CHN,   
        /* CMD5: channel 7; all CMDs can be Configured as different channels */            
        HAL_ADC_IV_CHN,      
        /* Loop depth */          
        3,                           
    };
    
    /* mod value, single, divide4, SW trig, clear to mod */
    TDG_InitConfig_t Config=
    {
        HAL_PWM_SET_COUNT_U*2U - 1U, TDG_COUNT_SINGLE, TDG_CLK_DIVIDE_1, TDG_TRIG_EXTERNAL, TDG_UPDATE_IMMEDIATELY, TDG_CLEAR_DELAY
    };
  
    /* 001*1/64Tclock */
    TDG_DelayOutputConfig_t Doconfig =         
    {
        TDG_DO_0, 
        (Q16U_)(HAL_ADC_TRIGGER_TIME3*HAL_PWM_ALL_COUNT_F), 
        ENABLE,
    };
  
    TDG_ChannelConfig_t Chconfig =
    {
        TDG_CHANNEL_2, 
        0U, 
        1U, 
        &Doconfig,
    };
  

    /* Reset ADC */
    SYSCTRL_ResetModule(SYSCTRL_ADC0);
    /* Enable ADC clock */
    SYSCTRL_EnableModule(SYSCTRL_ADC0);
    /* adc pinmux */
    /* PTC15/ADC0_CH13 for motor U_current */ 
    PORT_PinmuxConfig(HAL_ADC_IU_PORT, HAL_ADC_IU_PIN, HAL_ADC_IU_PINMUX);  
    /* PTB22/ADC0_CH19 for motor V_current */      
    PORT_PinmuxConfig(HAL_ADC_IV_PORT, HAL_ADC_IV_PIN, HAL_ADC_IV_PINMUX);       
    /* PTC16/ADC0_CH16 for motor W_current */
    PORT_PinmuxConfig(HAL_ADC_IW_PORT, HAL_ADC_IW_PIN, HAL_ADC_IW_PINMUX);    
    /* PTC17/ADC0_CH15 for motor bus volatage */   
    PORT_PinmuxConfig(HAL_ADC_VBUS_PORT, HAL_ADC_VBUS_PIN, HAL_ADC_VBUS_PINMUX); 
    
    /* Reset software */
    ADC_SoftwareReset(HAL_ADC_ID);
    
    /* Initialize ADC */
    ADC_Init(HAL_ADC_ID,&SubcaseAdcCfg);
    /* Redefine the depth the function */    
    ADC_FifoDepthRedefine(HAL_ADC_ID,3); 
    /* Set ADC watermark */
    /* fifo WM > 2, that is when WM=3,flag will be set */
    ADC_FifoWatermarkConfig(HAL_ADC_ID,2);                               
    /* Configure input channel */
    ADC_ChannelConfig(HAL_ADC_ID, &AdcChannelCfg1);
    ADC_ChannelConfig(HAL_ADC_ID, &AdcChannelCfg2);
    ADC_ChannelConfig(HAL_ADC_ID, &AdcChannelCfg3);
    ADC_ChannelConfig(HAL_ADC_ID, &AdcChannelCfg4);     
    /* Mask FIFO watermark interrupt */
    ADC_IntMask(HAL_ADC_ID,ADC_FWM_INT, MASK);   
    
    /* Set trigger mode */
    ADC_TDGTriggerConfig(HAL_ADC_ID,&AdcTriggerConfig);
    /* Clear TCOMP interrupt */
    ADC_IntClear(HAL_ADC_ID,ADC_TCOMP_INT);
    /* Enable ADC module */
    ADC_Enable(HAL_ADC_ID);
    /* Enable ADC dma request */
    ADC_DmaRequestCmd(HAL_ADC_ID, ENABLE);
    
    
    /* Initialize TDG */
    TDG_InitConfig(HAL_TGD_ID, &Config);
    /* Set TDG delay output */
    TDG_ChannelDelayOutputConfig(HAL_TGD_ID, &Chconfig, ENABLE);
    
    Chconfig.channelId = TDG_CHANNEL_0;
    Doconfig.offset = (Q16U_)(HAL_ADC_TRIGGER_TIME1*HAL_PWM_ALL_COUNT_F);
    TDG_ChannelDelayOutputConfig(HAL_TGD_ID, &Chconfig, ENABLE);

    Chconfig.channelId = TDG_CHANNEL_1;
    Doconfig.offset = (Q16U_)(HAL_ADC_TRIGGER_TIME2*HAL_PWM_ALL_COUNT_F);
    TDG_ChannelDelayOutputConfig(HAL_TGD_ID, &Chconfig, ENABLE);
    /* enable TDG */
    TDG_Enable(HAL_TGD_ID, ENABLE);    
    /* Load channel Configuration */
    TDG_LoadCmd(HAL_TGD_ID);


    ADC0->ADC_CTRL.TRIG_MODE_ENABLE = 0;
    ADC0->ADC_CFG.CHSELP = HAL_ADC_VBUS_CHN;             /* config channel */
    ADC0->ADC_IE.TCOM_IE = 1U;                                         /* enable complete Int */
    ADC0->ADC_SWTRIG.ADC_SWTRIG = 1U;                                  /* start conversion */
    while (0U == ADC0->ADC_STAT.TCOMP_INT)
    {
    }

    ADC0->ADC_IE.TCOM_IE = 0U;                                         /* disable complete Int */
    ADC0->ADC_STAT.TCOMP_INT = 1U;                                     /* clear flag */
    ADC0->ADC_CTRL.TRIG_MODE_ENABLE = 1;                              /* change to tdg trigger */
    
    /* Clear FIFO */
    while (0U != ADC0->ADC_FCTRL.FCOUNT)
    {
        (void)ADC0->ADC_DATA_RD.ADC_DATA_RD;
    }      

#endif
}

/**********************************************************************************************
Function: BSP_ADC_Init_S
Description: 应用层ADC初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_ADC_Init_S(void)
{
    static adc_reg_t * ADC1 = (adc_reg_t *)(ADC1_BASE_ADDR);       /*PRQA S 0303*/  
    
    ADC_Config_t SubcaseAdcCfg =
    {
        /* resolution  */
        ADC_RESOLUTION_12BIT,
        /* vref */
        ADC_VREF_INTERNAL,
        /* trigger mode */
        ADC_TDG_TRIGGER,
        /* conversion mode */
        ADC_CONVERSION_SINGLE,
        /* average disabled */
        ADC_AVGS_DISABLED,
        /* Set sample interval > 500ns */
        50,
        /* Set ADC Stable time interval */
        50,
    };
    
    ADC_ChannelConfig_t Adc1ChannelCfg1 =
    {
        /* Single-Ended Mode Selected */
        ADC_SINGLE_MODE,
        /* Single mode vssa */
        HAL_ADC1_VR_CHN,
        /* Single mode, N-channel donn't need to configure */
        ADC_N_NONE,
    };
    ADC_ChannelConfig_t Adc1ChannelCfg2 =
    {
        /* Single-Ended Mode Selected */
        ADC_SINGLE_MODE,
        /* Single mode vssa */
        HAL_ADC1_TEMP_CHN,
        /* Single mode, N-channel donn't need to configure */
        ADC_N_NONE,
    };
    ADC_ChannelConfig_t Adc1ChannelCfg3 =
    {
        /* Single-Ended Mode Selected */
        ADC_SINGLE_MODE,
        /* Single mode, channel vssa */
        HAL_ADC1_BAT_CHN,
        /* Single mode, N-channel donn't need to configure */
        ADC_N_NONE,
    };
    
    
    /* Reset ADC1 */
    SYSCTRL_ResetModule(SYSCTRL_ADC1);
    /* Enable ADC1 clock */
    SYSCTRL_EnableModule(SYSCTRL_ADC1);
    /* adc pinmux */
    PORT_PinmuxConfig(HAL_ADC1_VR_PORT, HAL_ADC1_VR_PIN, HAL_ADC1_VR_PINMUX);
    PORT_PinmuxConfig(HAL_ADC1_TEMP_PORT, HAL_ADC1_TEMP_PIN, HAL_ADC1_TEMP_PINMUX);
    PORT_PinmuxConfig(HAL_ADC1_BAT_PORT, HAL_ADC1_BAT_PIN, HAL_ADC1_BAT_PINMUX);

    /* Reset software */
    ADC_SoftwareReset(HAL_ADC1_ID);
    /* Initialize ADC */
    ADC_Init(HAL_ADC1_ID, &SubcaseAdcCfg);
    /* Redefine the depth the function */
    ADC_FifoDepthRedefine(HAL_ADC1_ID, ADC_DATA_NUM_S);
    /* Set ADC watermark */
    /* fifo WM > 2, that is when WM=3,flag will be set */
    ADC_FifoWatermarkConfig(HAL_ADC1_ID, (ADC_DATA_NUM_S-1));
    /* Configure input channel */
    ADC_ChannelConfig(HAL_ADC1_ID, &Adc1ChannelCfg1);
    ADC_ChannelConfig(HAL_ADC1_ID, &Adc1ChannelCfg2);
    ADC_ChannelConfig(HAL_ADC1_ID, &Adc1ChannelCfg3);
    /* Mask FIFO watermark interrupt */
    ADC_IntMask(HAL_ADC1_ID, ADC_FWM_INT, MASK);
    
    /* M1&Bus */
    ADC_TDGTriggerConfig_t  Adc1TriggerConfig =
    {
        /* Loop mode Selected */
        ADC_LOOP_MODE,
        HAL_ADC1_VR_CHN,
        HAL_ADC1_TEMP_CHN,
        HAL_ADC1_BAT_CHN,
        ADC_P_CH7,
        ADC_P_CH7,
        ADC_P_CH7,
        /* Loop depth */
        ADC_DATA_NUM_S,
    };
    
    /* Set trigger mode */
    ADC_TDGTriggerConfig(HAL_ADC1_ID, &Adc1TriggerConfig);
    
    /* Clear TCOMP interrupt */
    ADC_IntClear(HAL_ADC1_ID, ADC_TCOMP_INT);
    /* Enable ADC1 module */
    ADC_Enable(HAL_ADC1_ID);
    /* Enable ADC1 dma request */
    ADC_DmaRequestCmd(HAL_ADC1_ID, ENABLE);
    /* mod value, single, divide4, SW trig, clear to mod */
    TDG_InitConfig_t Config =
    {
        1000U, TDG_COUNT_SINGLE, TDG_CLK_DIVIDE_1, TDG_TRIG_SW, TDG_UPDATE_IMMEDIATELY, TDG_CLEAR_DELAY
    };
    TDG_DelayOutputConfig_t Doconfig =
    {
        TDG_DO_0, 100U, ENABLE
    };
    const TDG_ChannelConfig_t Chconfig =
    {
        TDG_CHANNEL_0, 0U, 1U, &Doconfig
    };
    
    TDG_InitConfig(TDG1_ID, &Config);
    /* Set TDG delay output */
    TDG_ChannelDelayOutputConfig(TDG1_ID, &Chconfig, ENABLE);
    /* enable TDG */
    TDG_Enable(TDG1_ID, ENABLE);
    /* Load channel Configuration */
    TDG_LoadCmd(TDG1_ID);

    ADC1->ADC_CTRL.TRIG_MODE_ENABLE = 0;
    ADC1->ADC_CFG.CHSELP = HAL_ADC_VBUS_CHN;             /* config channel */
    ADC1->ADC_IE.TCOM_IE = 1U;                                         /* enable complete Int */
    ADC1->ADC_SWTRIG.ADC_SWTRIG = 1U;                                  /* start conversion */
    while (0U == ADC1->ADC_STAT.TCOMP_INT)
    {
    }

    ADC1->ADC_IE.TCOM_IE = 0U;                                         /* disable complete Int */
    ADC1->ADC_STAT.TCOMP_INT = 1U;                                     /* clear flag */
    ADC1->ADC_CTRL.TRIG_MODE_ENABLE = 1;                              /* change to tdg trigger */

    /* Clear FIFO */
    while (0U != ADC1->ADC_FCTRL.FCOUNT)
    {
        (void)ADC1->ADC_DATA_RD.ADC_DATA_RD;
    }
}
