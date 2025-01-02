/**************************************************************************************************
*     File Name :                        BSP_PWM.c
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             PWM初始化及应用层接口源文件
**************************************************************************************************/
#include "BSP_PWM.h"

/**********************************************************************************************
Function: BSP_PWM_Init
Description: 电机控制用PWM初始化
Input: 故障中断函数
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
 void BSP_PWM_Init(isr_cb_t *M1FaultIntCbf)
{
    /*PRQA S 0303 ++*/
    mcpwm_reg_t * MCPWMx = (mcpwm_reg_t*) MCPWM1_BASE_ADDR;
    
    /*PRQA S 0303 --*/
    MCPWM_CompPwmChannelConfig_t CPwmChConfig1;
    MCPWM_CompPwmConfig_t Config1;
    MCPWM_CompPwmChannelConfig_t CPwmChConfig2;
    MCPWM_CompPwmConfig_t Config2;
    MCPWM_CompPwmChannelConfig_t CPwmChConfig3;
    MCPWM_CompPwmConfig_t Config3;
    MCPWM_FaultChannelConfig_t FaultChannelConfig[4];
    MCPWM_PwmFaultCtrlConfig_t  Configfault;
    /* reload config */    
    MCPWM_ReloadConfig_t ReloadConfig = 
    {
        DISABLE,
        ENABLE,
        0
    };
    
    /* Config pinmux */
    /* Need to pinmux first for FLTinput */    
    PORT_PinmuxConfig(HAL_FAULTIN_PORT, HAL_FAULTIN_PIN,HAL_FAULTIN_PINMUX);
    /* U_H OUTPUT */
    PORT_PinmuxConfig(HAL_PWM_UH_PORT, HAL_PWM_UH_PIN,HAL_PWM_UH_PINMUX);   
    /* U_L OUTPUT */    
    PORT_PinmuxConfig(HAL_PWM_UL_PORT, HAL_PWM_UL_PIN,HAL_PWM_UL_PINMUX); 
    /* V_H OUTPUT */      
    PORT_PinmuxConfig(HAL_PWM_VH_PORT, HAL_PWM_VH_PIN,HAL_PWM_VH_PINMUX);   
    /* V_L OUTPUT */    
    PORT_PinmuxConfig(HAL_PWM_VL_PORT, HAL_PWM_VL_PIN,HAL_PWM_VL_PINMUX);   
    /* W_H OUTPUT */    
    PORT_PinmuxConfig(HAL_PWM_WH_PORT, HAL_PWM_WH_PIN,HAL_PWM_WH_PINMUX);    
    /* W_L OUTPUT */   
    PORT_PinmuxConfig(HAL_PWM_WL_PORT, HAL_PWM_WL_PIN,HAL_PWM_WL_PINMUX);       
    
    /* MCPWM complementary PWM output channel config */
    CPwmChConfig1.pairId = HAL_PWM_U_PAIR_ID;
    CPwmChConfig1.pec = MCPWM_MAIN_CV;
    
#if (HAL_CURRENT_SAMPLE_MODE == HAL_THREE_SHUNT)
    /* symmetric PWM output */
    CPwmChConfig1.asym = MCPWM_SYMMETRIC;	
    CPwmChConfig1.pulsePol = MCPWM_HIGH_PULSE_POL;
#elif (HAL_CURRENT_SAMPLE_MODE == HAL_ONE_SHUNT)
    /* Asymmetric PWM output */
    CPwmChConfig1.asym = MCPWM_ASYMMETRIC; 
    CPwmChConfig1.pulsePol = MCPWM_LOW_PULSE_POL;       
#endif
    
    CPwmChConfig1.mainChannelOutputEnable = ENABLE;
    CPwmChConfig1.secondChannelOutputEnable = ENABLE;
    CPwmChConfig1.polarity = MCPWM_POL_LOW;
    CPwmChConfig1.mainCompareValue = HAL_PWM_SET_COUNT_U;
    CPwmChConfig1.secondCompareValue = 0U;
    CPwmChConfig1.mainChannelOffVal = LEVEL_LOW;
    CPwmChConfig1.secondChannelOffVal = LEVEL_LOW;
    CPwmChConfig1.mainChannelMatchTrigEnable = DISABLE;
    CPwmChConfig1.secondChannelMatchTrigEnable = DISABLE;
    CPwmChConfig1.deadTimeEnable =DISABLE;
    CPwmChConfig1.faultCtrlEnable =ENABLE;
    CPwmChConfig1.CVUpdateEnable=ENABLE;
    CPwmChConfig1.mainSafeStatusForFaultA=LEVEL_LOW;
    CPwmChConfig1.secondSafeStatusForFaultA =LEVEL_LOW;
    CPwmChConfig1.mainSafeStatusForFaultB=LEVEL_LOW;
    CPwmChConfig1.secondSafeStatusForFaultB =LEVEL_LOW;
    /* deattime is set in predrive */ 
    CPwmChConfig1.deadTimeVal = 160;                                                     
    /* MCPWM complementary PWM output global config */
    Config1.countMode = MCPWM_COUNTING_UP_DOWN;
    /* 10kpwm    fsoc/(2*fpwm) */
    Config1.countModVal = HAL_PWM_SET_COUNT_U;                 
    Config1.cPwmChConfig = &CPwmChConfig1;
    /* output complementary pwm config */
    MCPWM_OutputComplementaryPwmConfig(HAL_MCPWM_ID, HAL_PWM_COUNTER_ID, &Config1);
    MCPWM_PairCombineCmd(HAL_MCPWM_ID, HAL_PWM_U_PAIR_ID, ENABLE);
    
    CPwmChConfig2.pairId = HAL_PWM_V_PAIR_ID;
    CPwmChConfig2.pec = MCPWM_MAIN_CV;

#if (HAL_CURRENT_SAMPLE_MODE == HAL_THREE_SHUNT)
    /* symmetric PWM output */
    CPwmChConfig2.asym = MCPWM_SYMMETRIC;	
    CPwmChConfig2.pulsePol = MCPWM_HIGH_PULSE_POL;
#elif (HAL_CURRENT_SAMPLE_MODE == HAL_ONE_SHUNT)
    /* Asymmetric PWM output */
    CPwmChConfig2.asym = MCPWM_ASYMMETRIC; 
    CPwmChConfig2.pulsePol = MCPWM_LOW_PULSE_POL;       
#endif
    
    CPwmChConfig2.mainChannelOutputEnable = ENABLE;
    CPwmChConfig2.secondChannelOutputEnable = ENABLE;
    CPwmChConfig2.polarity = MCPWM_POL_LOW;
    CPwmChConfig2.mainCompareValue = HAL_PWM_SET_COUNT_U;
    CPwmChConfig2.secondCompareValue = 0U;
    CPwmChConfig2.mainChannelOffVal = LEVEL_LOW;
    CPwmChConfig2.secondChannelOffVal = LEVEL_LOW;
    CPwmChConfig2.mainChannelMatchTrigEnable = DISABLE;
    CPwmChConfig2.secondChannelMatchTrigEnable = DISABLE;
    CPwmChConfig2.deadTimeEnable =DISABLE;
    CPwmChConfig2.faultCtrlEnable =ENABLE;
    CPwmChConfig2.CVUpdateEnable=ENABLE;
    CPwmChConfig2.mainSafeStatusForFaultA=LEVEL_LOW;
    CPwmChConfig2.secondSafeStatusForFaultA =LEVEL_LOW;
    CPwmChConfig2.mainSafeStatusForFaultB=LEVEL_LOW;
    CPwmChConfig2.secondSafeStatusForFaultB =LEVEL_LOW;
    CPwmChConfig2.deadTimeVal = 160;  
    /* MCPWM complementary PWM output global config */
    Config2.countMode = MCPWM_COUNTING_UP_DOWN;
    /* 10kpwm fsoc/(2*fpwm) */
    Config2.countModVal = HAL_PWM_SET_COUNT_U;               
    Config2.cPwmChConfig = &CPwmChConfig2;
    /* output complementary pwm config  */
    MCPWM_OutputComplementaryPwmConfig(HAL_MCPWM_ID, HAL_PWM_COUNTER_ID, &Config2);
    MCPWM_PairCombineCmd(HAL_MCPWM_ID, HAL_PWM_V_PAIR_ID, ENABLE);
     
    CPwmChConfig3.pairId = HAL_PWM_W_PAIR_ID;
    CPwmChConfig3.pec = MCPWM_MAIN_CV;

#if (HAL_CURRENT_SAMPLE_MODE == HAL_THREE_SHUNT)
    /* symmetric PWM output */
    CPwmChConfig3.asym = MCPWM_SYMMETRIC;	
    CPwmChConfig3.pulsePol = MCPWM_HIGH_PULSE_POL;
#elif (HAL_CURRENT_SAMPLE_MODE == HAL_ONE_SHUNT)
    /* Asymmetric PWM output */
    CPwmChConfig3.asym = MCPWM_ASYMMETRIC; 
    CPwmChConfig3.pulsePol = MCPWM_LOW_PULSE_POL;       
#endif
    
    CPwmChConfig3.mainChannelOutputEnable = ENABLE;
    CPwmChConfig3.secondChannelOutputEnable = ENABLE;
    CPwmChConfig3.polarity = MCPWM_POL_LOW;
    CPwmChConfig3.mainCompareValue = HAL_PWM_SET_COUNT_U;
    CPwmChConfig3.secondCompareValue = 0U;    
    CPwmChConfig3.mainChannelOffVal = LEVEL_LOW;
    CPwmChConfig3.secondChannelOffVal = LEVEL_LOW;
    CPwmChConfig3.mainChannelMatchTrigEnable = DISABLE;
    CPwmChConfig3.secondChannelMatchTrigEnable = DISABLE;
    CPwmChConfig3.deadTimeEnable =DISABLE;
    CPwmChConfig3.faultCtrlEnable =ENABLE;
    CPwmChConfig3.CVUpdateEnable=ENABLE;
    CPwmChConfig3.mainSafeStatusForFaultA=LEVEL_LOW;
    CPwmChConfig3.secondSafeStatusForFaultA =LEVEL_LOW;
    CPwmChConfig3.mainSafeStatusForFaultB=LEVEL_LOW;
    CPwmChConfig3.secondSafeStatusForFaultB =LEVEL_LOW;
    CPwmChConfig3.deadTimeVal = 160;     
    /* MCPWM complementary PWM output global config */
    Config3.countMode = MCPWM_COUNTING_UP_DOWN;
    /* 10kpwm  0x1f40  fsoc/(2*fpwm) */
    Config3.countModVal = HAL_PWM_SET_COUNT_U;               
    Config3.cPwmChConfig = &CPwmChConfig3;
    /* output complementary pwm config  */
    MCPWM_OutputComplementaryPwmConfig(HAL_MCPWM_ID, HAL_PWM_COUNTER_ID, &Config3);
    MCPWM_PairCombineCmd(HAL_MCPWM_ID, HAL_PWM_W_PAIR_ID, ENABLE);   

    /* fault channel config */
    FaultChannelConfig[0].faultInputChannelEnable = DISABLE;
    FaultChannelConfig[0].faultInputFilterEnable = DISABLE;
    FaultChannelConfig[0].faultInputPolarity = MCPWM_POL_HIGH; 
    FaultChannelConfig[0].inputChannel =  MCPWM_FAULT_CHANNEL_0;
    FaultChannelConfig[1].faultInputChannelEnable = DISABLE;
    FaultChannelConfig[1].faultInputFilterEnable = DISABLE;
    FaultChannelConfig[1].faultInputPolarity = MCPWM_POL_HIGH; 
    FaultChannelConfig[1].inputChannel =  MCPWM_FAULT_CHANNEL_1;
    FaultChannelConfig[2].faultInputChannelEnable = DISABLE;
    FaultChannelConfig[2].faultInputFilterEnable = DISABLE;
    FaultChannelConfig[2].faultInputPolarity = MCPWM_POL_HIGH; 
    FaultChannelConfig[2].inputChannel =  MCPWM_FAULT_CHANNEL_2;
    FaultChannelConfig[3].faultInputChannelEnable = ENABLE;
    FaultChannelConfig[3].faultInputFilterEnable = ENABLE;
    FaultChannelConfig[3].faultInputPolarity = MCPWM_POL_HIGH;
    FaultChannelConfig[3].inputChannel =  MCPWM_FAULT_CHANNEL_3; 
     /* fault config */   
    Configfault.numFaultInputChannels = 4;
    Configfault.faultClearMode = MCPWM_Fault_MANUAL_CLEAR;
    Configfault.faultFilterValue = 0xf;
    Configfault.status =  MCPWM_INACTIVE_STATE;   
    Configfault.faultChannelConfig = FaultChannelConfig;
    MCPWM_FaultControlConfig(HAL_MCPWM_ID, &Configfault);
    
    /* clock config */
    MCPWM_ClockSourceConfig(HAL_MCPWM_ID, MCPWM_CLK_SOURCE_SYSTEM,MCPWM_CLK_DIVIDE_2); 
    
    /* cnt0 config */
    MCPWM_ReloadParamConfig(HAL_MCPWM_ID, HAL_PWM_COUNTER_ID, &ReloadConfig);      

    MCPWMx->MCPWM_RELOAD.LOADEN0 = ENABLE;
    MCPWMx->MCPWM_RELOAD.LOADEN1 = ENABLE;   
    MCPWMx->MCPWM_RELOAD.LOADEN2 = ENABLE;    

#if(HAL_CURRENT_SAMPLE_MODE == HAL_THREE_SHUNT)
    
    MCPWMx->MCPWM_CV[MCPWM_CHANNEL_0].CV = HAL_PWM_SET_COUNT_U;        
    MCPWMx->MCPWM_CV[MCPWM_CHANNEL_2].CV = HAL_PWM_SET_COUNT_U;  
    MCPWMx->MCPWM_CV[MCPWM_CHANNEL_4].CV = HAL_PWM_SET_COUNT_U;   
    
#elif(HAL_CURRENT_SAMPLE_MODE == HAL_ONE_SHUNT)
    
    MCPWMx->MCPWM_CV[MCPWM_CHANNEL_0].CV = HAL_PWM_SET_COUNT_U/2U;      
    MCPWMx->MCPWM_CV[MCPWM_CHANNEL_1].CV = HAL_PWM_SET_COUNT_U/2U; 
    
    MCPWMx->MCPWM_CV[MCPWM_CHANNEL_2].CV = HAL_PWM_SET_COUNT_U/2U;  
    MCPWMx->MCPWM_CV[MCPWM_CHANNEL_3].CV = HAL_PWM_SET_COUNT_U/2U;      
    
    MCPWMx->MCPWM_CV[MCPWM_CHANNEL_4].CV = HAL_PWM_SET_COUNT_U/2U;  
    MCPWMx->MCPWM_CV[MCPWM_CHANNEL_5].CV = HAL_PWM_SET_COUNT_U/2U; 
    
#endif
    
    MCPWM_InitTriggerCmd(HAL_MCPWM_ID, ENABLE);     
    
    MCPWM_InstallCallBackFunc(HAL_MCPWM_ID, HAL_FAULTIN, M1FaultIntCbf);
    MCPWM_IntClear(HAL_MCPWM_ID, HAL_FAULTIN);
    
    /* unmask/mask interrupt */
    MCPWM_IntMask(HAL_MCPWM_ID, HAL_FAULTIN, UNMASK);
    MCPWM_IntMask(HAL_MCPWM_ID, MCPWM_INT_CH0, MASK);
    MCPWM_IntMask(HAL_MCPWM_ID, MCPWM_INT_CH1, MASK);
    MCPWM_IntMask(HAL_MCPWM_ID, MCPWM_INT_CH2, MASK);
    MCPWM_IntMask(HAL_MCPWM_ID, MCPWM_INT_CH3, MASK);
    MCPWM_IntMask(HAL_MCPWM_ID, MCPWM_INT_CH4, MASK);
    MCPWM_IntMask(HAL_MCPWM_ID, MCPWM_INT_CH5, MASK);
    MCPWM_IntMask(HAL_MCPWM_ID, MCPWM_INT_CH7, MASK);
    MCPWM_IntMask(HAL_MCPWM_ID, MCPWM_INT_CH7, MASK);
    /* disable DMA */
    MCPWM_DMACmd(HAL_MCPWM_ID, MCPWM_CHANNEL_0, DISABLE);
    MCPWM_DMACmd(HAL_MCPWM_ID, MCPWM_CHANNEL_1, DISABLE);
    MCPWM_DMACmd(HAL_MCPWM_ID, MCPWM_CHANNEL_2, DISABLE);
    MCPWM_DMACmd(HAL_MCPWM_ID, MCPWM_CHANNEL_3, DISABLE);
    MCPWM_DMACmd(HAL_MCPWM_ID, MCPWM_CHANNEL_4, DISABLE);
    MCPWM_DMACmd(HAL_MCPWM_ID, MCPWM_CHANNEL_5, DISABLE);
    MCPWM_DMACmd(HAL_MCPWM_ID, MCPWM_CHANNEL_6, DISABLE);
    MCPWM_DMACmd(HAL_MCPWM_ID, MCPWM_CHANNEL_7, DISABLE);
    
    /* start counter */
    MCPWM_StartGlobalCounter(HAL_MCPWM_ID);
    MCPWM_StartCounter(HAL_MCPWM_ID,HAL_PWM_COUNTER_ID);
}

