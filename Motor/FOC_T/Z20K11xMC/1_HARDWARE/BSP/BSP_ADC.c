/**************************************************************************************************
*     File Name :                        BSP_ADC.c
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             ADC初始化及应用层接口源文件
**************************************************************************************************/
#include "BSP_ADC.h"

/**********************************************************************************************
Function: BSP_ADC_Init_Three_Shunt
Description: 电机控制用ADC初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_ADC_Init_Three_Shunt(isr_cb_t *ADCDoneCbf)
{
    ADC_Config_t SubcaseAdcCfg =
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
        45,
    };
    
    ADC_ChannelConfig_t AdcChannelCfg1 =
    {
        ADC_SINGLE_MODE, /* Single-Ended Mode Selected */
        HAL_ADC_IU_CHN,  /* Single mode, channel[12] and vssa */
        ADC_N_NONE,      /* Single mode, N-channel donn't need to configure */
    };
    
    ADC_ChannelConfig_t AdcChannelCfg2 =
    {
        ADC_SINGLE_MODE, /* Single-Ended Mode Selected */
        HAL_ADC_IV_CHN,  /* Single mode, channel[12] and vssa */
        ADC_N_NONE,      /* Single mode, N-channel donn't need to configure */
    };
    
	ADC_ChannelConfig_t AdcChannelCfg3 =
    {
        ADC_SINGLE_MODE, /* Single-Ended Mode Selected */
        HAL_ADC_IW_CHN,  /* Single mode, channel[12] and vssa */
        ADC_N_NONE,      /* Single mode, N-channel donn't need to configure */
    };
    
    ADC_ChannelConfig_t AdcChannelCfg4 =
    {
        ADC_SINGLE_MODE,  /* Single-Ended Mode Selected */
        HAL_ADC_VBUS_CHN, /* Single mode, channel[12] and vssa */
        ADC_N_NONE,       /* Single mode, N-channel donn't need to configure */
    };
    
    ADC_ChannelConfig_t AdcChannelCfg5 = 
    {
        ADC_SINGLE_MODE,  /* Single-Ended Mode Selected */
        HAL_ADC_VR_CHN,       /* Single mode, channel[12] and vssa */
        ADC_N_NONE,       /* Single mode, N-channel donn't need to configure */ 
    };
    
    ADC_TDGTriggerConfig_t AdcTriggerConfig =
    {
        /* Loop mode Selected */
        ADC_LOOP_MODE,
        /* CMD1: channel 14; */
        HAL_ADC_IU_CHN,
        /* CMD2: channel 13; */
        HAL_ADC_IV_CHN,
        /* CMD3: channel 12; */
        HAL_ADC_IW_CHN,
        /* CMD4: channel 7; */
        HAL_ADC_VBUS_CHN,
        /* CMD5: channel 7; all CMDs can be Configured as different channels */
        HAL_ADC_VR_CHN,
        /* CMD5: channel 7; all CMDs can be Configured as different channels */
        HAL_ADC_VR_CHN,
    };
    
    /* mod value, single, divide4, SW trig, clear to mod */
    TDG_InitConfig_t Config =
    {
        HAL_PWM_SET_COUNT_T - 1U, TDG_COUNT_SINGLE, TDG_CLK_DIVIDE_1, TDG_TRIG_EXTERNAL, TDG_UPDATE_IMMEDIATELY, TDG_CLEAR_MODULATOR};
    
    /* 001*1/64Tclock */
    TDG_DelayOutputConfig_t Doconfig =
    {
        TDG_DO_0, (HAL_PWM_SET_COUNT_T - (HAL_ADC_SAMPLE_VALUE - HAL_ADC_DELAY_VALUE)/2U), ENABLE
    };
    
    TDG_ChannelConfig_t Chconfig =
    {
        TDG_CHANNEL_0, 0U, 1U, &Doconfig
    };
    
    /* Reset ADC */
    SYSCTRL_ResetModule(SYSCTRL_ADC0);
    /* Enable ADC clock */
    SYSCTRL_EnableModule(SYSCTRL_ADC0);
    /* adc pinmux */
    PORT_PinmuxConfig(HAL_ADC_IU_PORT, HAL_ADC_IU_PIN, HAL_ADC_IU_PINMUX);
	PORT_PinmuxConfig(HAL_ADC_IV_PORT, HAL_ADC_IV_PIN, HAL_ADC_IV_PINMUX);
	PORT_PinmuxConfig(HAL_ADC_IW_PORT, HAL_ADC_IW_PIN, HAL_ADC_IW_PINMUX);
    PORT_PinmuxConfig(HAL_ADC_VBUS_PORT, HAL_ADC_VBUS_PIN, HAL_ADC_VBUS_PINMUX);
    PORT_PinmuxConfig(HAL_ADC_VR_PORT, HAL_ADC_VR_PIN, HAL_ADC_VR_PINMUX); 
    /* Reset software */
    ADC_SoftwareReset(HAL_MOTOR_ADC);
    /* Self calibration */
    // ADC_SelfCalibration(HAL_MOTOR_ADC);
    /* Initialize ADC */
    ADC_Init(HAL_MOTOR_ADC, &SubcaseAdcCfg);
    /* Redefine the depth the function */
    ADC_FifoDepthRedefine(HAL_MOTOR_ADC, (2U*HAL_MOTOR_ADC_NUM));
    /* Set ADC watermark */
    /* fifo WM > 3, that is when WM=4,flag will be set */
    ADC_FifoWatermarkConfig(HAL_MOTOR_ADC, (2U*HAL_MOTOR_ADC_NUM-1U));
    /* Configure input channel */
    ADC_ChannelConfig(HAL_MOTOR_ADC, &AdcChannelCfg1);
    ADC_ChannelConfig(HAL_MOTOR_ADC, &AdcChannelCfg2);
    ADC_ChannelConfig(HAL_MOTOR_ADC, &AdcChannelCfg3);
	ADC_ChannelConfig(HAL_MOTOR_ADC, &AdcChannelCfg4);
	ADC_ChannelConfig(HAL_MOTOR_ADC, &AdcChannelCfg5);
    
    /* Mask FIFO watermark interrupt */
    ADC_IntMask(HAL_MOTOR_ADC, ADC_FWM_INT, UNMASK);
    
    /* Set trigger mode */
    ADC_TDGTriggerConfig(HAL_MOTOR_ADC, &AdcTriggerConfig);
    /* Clear TCOMP interrupt */
    ADC_IntClear(HAL_MOTOR_ADC, ADC_TCOMP_INT);
    ADC_IntClear(HAL_MOTOR_ADC, ADC_FWM_INT);
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

/**********************************************************************************************
Function: BSP_ADC_Init_One_Shunt
Description: 电机控制用ADC初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_ADC_Init_One_Shunt(isr_cb_t *ADCDoneCbf)
{
    ADC_Config_t SubcaseAdcCfg =
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
        45,
    };
    
    ADC_ChannelConfig_t AdcChannelCfg1 =
    {
        ADC_SINGLE_MODE,  /* Single-Ended Mode Selected */
        HAL_ADC_VBUS_CHN, /* Single mode, channel[12] and vssa */
        ADC_N_NONE,       /* Single mode, N-channel donn't need to configure */
    };
    
    ADC_ChannelConfig_t AdcChannelCfg2 =
    {
        ADC_SINGLE_MODE, /* Single-Ended Mode Selected */
        HAL_ADC_IV_CHN,  /* Single mode, channel[12] and vssa */
        ADC_N_NONE,      /* Single mode, N-channel donn't need to configure */
    };
    
    ADC_TDGTriggerConfig_t AdcTriggerConfig =
    {
        /* Loop mode Selected */
        ADC_MAPPING_MODE,
        /* CMD0: channel 15; */
        HAL_ADC_IV_CHN,
        /* CMD1: channel 14; */
        HAL_ADC_IV_CHN,
        /* CMD2: channel 13; */
        HAL_ADC_VBUS_CHN,
        /* CMD3: channel 12; */
        HAL_ADC_IV_CHN,
        /* CMD4: channel 7; */
        HAL_ADC_IV_CHN,
        /* CMD5: channel 7; all CMDs can be Configured as different channels */
        HAL_ADC_VBUS_CHN,
    };
    
    /* mod value, single, divide4, SW trig, clear to mod */
    TDG_InitConfig_t Config =
    {
        HAL_PWM_SET_COUNT_T - 1U, TDG_COUNT_SINGLE, TDG_CLK_DIVIDE_1, TDG_TRIG_EXTERNAL, TDG_UPDATE_IMMEDIATELY, TDG_CLEAR_MODULATOR};
    
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
    PORT_PinmuxConfig(HAL_ADC_IU_PORT, HAL_ADC_IU_PIN, HAL_ADC_IU_PINMUX);
	PORT_PinmuxConfig(HAL_ADC_IV_PORT, HAL_ADC_IV_PIN, HAL_ADC_IV_PINMUX);
	PORT_PinmuxConfig(HAL_ADC_IW_PORT, HAL_ADC_IW_PIN, HAL_ADC_IW_PINMUX);
    PORT_PinmuxConfig(HAL_ADC_VBUS_PORT, HAL_ADC_VBUS_PIN, HAL_ADC_VBUS_PINMUX);
    PORT_PinmuxConfig(HAL_ADC_VR_PORT, HAL_ADC_VR_PIN, HAL_ADC_VR_PINMUX); 
    /* Reset software */
    ADC_SoftwareReset(HAL_MOTOR_ADC);
    /* Self calibration */
    // ADC_SelfCalibration(HAL_MOTOR_ADC);
    /* Initialize ADC */
    ADC_Init(HAL_MOTOR_ADC, &SubcaseAdcCfg);
    /* Redefine the depth the function */
    ADC_FifoDepthRedefine(HAL_MOTOR_ADC, (HAL_MOTOR_ADC_NUM));
    /* Set ADC watermark */
    /* fifo WM > 3, that is when WM=4,flag will be set */
    ADC_FifoWatermarkConfig(HAL_MOTOR_ADC, (HAL_MOTOR_ADC_NUM-1U));
    /* Configure input channel */
    ADC_ChannelConfig(HAL_MOTOR_ADC, &AdcChannelCfg1);
    ADC_ChannelConfig(HAL_MOTOR_ADC, &AdcChannelCfg2);
    
    /* Mask FIFO watermark interrupt */
    ADC_IntMask(HAL_MOTOR_ADC, ADC_FWM_INT, UNMASK);
    
    /* Set trigger mode */
    ADC_TDGTriggerConfig(HAL_MOTOR_ADC, &AdcTriggerConfig);
    /* Clear TCOMP interrupt */
    ADC_IntClear(HAL_MOTOR_ADC, ADC_TCOMP_INT);
    ADC_IntClear(HAL_MOTOR_ADC, ADC_FWM_INT);
    
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
    
    Chconfig.channelId = TDG_CHANNEL_0;
    Doconfig.offset = (Q16U_)(HAL_ADC_TRIGGER_TIME1*HAL_PWM_ALL_COUNT_F);
    TDG_ChannelDelayOutputConfig(HAL_MOTOR_TDG, &Chconfig, ENABLE);

    Chconfig.channelId = TDG_CHANNEL_1;
    Doconfig.offset = (Q16U_)(HAL_ADC_TRIGGER_TIME2*HAL_PWM_ALL_COUNT_F);
    TDG_ChannelDelayOutputConfig(HAL_MOTOR_TDG, &Chconfig, ENABLE);
    
    /* enable TDG */
    TDG_Enable(HAL_MOTOR_TDG, ENABLE);
    /* Load channel Configuration */
    TDG_LoadCmd(HAL_MOTOR_TDG);
    
    ADC_InstallCallBackFunc(HAL_MOTOR_ADC, ADC_FWM_INT, ADCDoneCbf);
}
