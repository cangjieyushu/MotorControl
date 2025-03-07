/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/

#include "BSP_PWM.h"

void BSP_PWM_Init(isr_cb_t *PwmFaultIntCbf, isr_cb_t *PwmCPIntCbf)
{
    tim_reg_w_t * TIMx_w = (tim_reg_w_t *)(HAL_MOTOR_PWM_ADDRESS);
    
    /*TIM module enable*/
    SYSCTRL_ResetModule(SYSCTRL_TIM0);
    SYSCTRL_EnableModule(SYSCTRL_TIM0);
    
    /* TIM complementary PWM output channel 4 and channel 5 config struct :disable fault ctrl and disable ccv sync function */
    TIM_CompPwmChannelConfig_t  cPwmChConfig0 =
    {
        HAL_PWM_U_PAIR,
        TIM_PWM_HIGH_TRUE_PULSE,
        TIM_POL_HIGH,
        // 0.5*(1-a)*PWM_MAX a is the ratio of caculated ccv
        (0),
        // 0.5*(1+a)*PWM_MAX a is the ratio of caculated ccv
        (0),
        ENABLE,
        ENABLE,
        ENABLE
    };
    /* TIM complementary PWM output channel 6 and channel 7 config struct*/
    TIM_CompPwmChannelConfig_t  cPwmChConfig1 =
    {
        HAL_PWM_V_PAIR,
        TIM_PWM_HIGH_TRUE_PULSE,
        TIM_POL_HIGH,
        (0),
        (0),
        ENABLE,
        ENABLE,
        ENABLE
    };
    /* TIM complementary PWM output channel 0 and channel 1 config struct*/
    TIM_CompPwmChannelConfig_t  cPwmChConfig2 =
    {
        HAL_PWM_W_PAIR,
        TIM_PWM_HIGH_TRUE_PULSE,
        TIM_POL_HIGH,
        (0),
        (0),
        ENABLE,
        ENABLE,
        ENABLE
    };
    
    /* TIM complementary PWM output channel 2 and channel 3 config struct*/
    TIM_CompPwmChannelConfig_t  cPwmChConfig3 =
    {
        HAL_PWM_ADC_PAIR,
        TIM_PWM_HIGH_TRUE_PULSE,
        TIM_POL_HIGH,
        (0),
        (HAL_ADC_DELAY_VALUE),
        ENABLE,
        ENABLE,
        ENABLE
    };
    
    /* TIM complementary PWM output config array*/
    TIM_CompPwmChannelConfig_t cPwmChConfig[4] = {cPwmChConfig0, cPwmChConfig1, cPwmChConfig2, cPwmChConfig3};
    
    
    /* TIM complementary PWM output Config*/
    TIM_CompPwmConfig_t  cPwmConfig =
    {
        4,                  /*pair number*/
        0,                  /*counter init value*/
        HAL_PWM_INIT_SET - 1,  /*counter max value*/
        TIM_PRESCALER_4,    /*dead PRESCALER*/
        0,                  /*dead clock, dead time = TIM_PRESCALER_1 * 128 set 2us was 32 for 4910 has this funciton*/
        cPwmChConfig        /*channel config pointer*/
    };
    
    /*match relaod*/
    TIM_ChannelMatchConfig_t channelMatchConfig[6] =
    {
        {TIM_CHANNEL_4, DISABLE},
        {TIM_CHANNEL_5, DISABLE},
        {TIM_CHANNEL_6, DISABLE},
        {TIM_CHANNEL_7, DISABLE},
        {TIM_CHANNEL_0, DISABLE},
        {TIM_CHANNEL_1, DISABLE}
    };
    
    
    /*TIM reload config*/
    TIM_ReloadConfig_t   reloadConfig =
    {
        TIM_RELOAD_FULL_CYCLE,
        1,
        6,
        channelMatchConfig
    };
    
    /*TIM sync config for update ccv*/
    TIM_PwmSyncConfig_t  syncConfig =
    {
        TIM_UPDATE_PWM_SYN,
        TIM_UPDATE_PWM_SYN,
        DISABLE,
        ENABLE,
        &reloadConfig
    };
    
    /* GPIO config */
    PORT_PinmuxConfig(HAL_PWM_UH_PORT, HAL_PWM_UH_PIN, HAL_PWM_UH_PINMUX);
    PORT_PinmuxConfig(HAL_PWM_UL_PORT, HAL_PWM_UL_PIN, HAL_PWM_UL_PINMUX);
    
    PORT_PinmuxConfig(HAL_PWM_VH_PORT, HAL_PWM_VH_PIN, HAL_PWM_VH_PINMUX);
    PORT_PinmuxConfig(HAL_PWM_VL_PORT, HAL_PWM_VL_PIN, HAL_PWM_VL_PINMUX);
    
    PORT_PinmuxConfig(HAL_PWM_WH_PORT, HAL_PWM_WH_PIN, HAL_PWM_WH_PINMUX);
    PORT_PinmuxConfig(HAL_PWM_WL_PORT, HAL_PWM_WL_PIN, HAL_PWM_WL_PINMUX);
    
    
    /* set up-counting mode */
    TIM_CountingModeConfig(HAL_MOTOR_PWM, TIM_COUNTING_UP);
    
    /* output complementary init*/
    TIM_OutputComplementaryPwmConfig(HAL_MOTOR_PWM, &cPwmConfig);
    
    /* reload config*/
    TIM_SyncConfig(HAL_MOTOR_PWM, &syncConfig);
    
    // Disable the pwm output
    TIMx_w->TIM_GLBCR &= 0xffffff00U;
    TIM_StopCounter(HAL_MOTOR_PWM);
    
    /* TIM fault control config struct definition */
    const TIM_PwmFaultCtrlConfig_t  config =
    {
        DISABLE, TIM_INPUT_FILTER_15, TIM_LOW_STATE,
        TIM_Fault_MANUAL_CLEAR,{
            {DISABLE, DISABLE, TIM_POL_LOW},             /* TIM_POL_LOW: 0 is active fault0 input*/
            {ENABLE, ENABLE, TIM_POL_LOW},               /* TIM_FAULT_CHANNEL_1 */
        }
    };
    /* TIM initialise fault control config */
    TIM_FaultControlConfig(HAL_MOTOR_PWM, &config);
    //PORT_PinmuxConfig(PORT_E, GPIO_9, PTE9_TIM2_FLT0); 
    PORT_PinmuxConfig(HAL_PWM_FAULT_PORT, HAL_PWM_FAULT_PIN, HAL_PWM_FAULT_PINMUX);
    
    /* enable function */
    TIM_IntClear(HAL_MOTOR_PWM, TIM_INT_FAULT);
    TIM_IntClear(HAL_MOTOR_PWM, TIM_INT_CH3);
    TIM_InitTriggerCmd(HAL_MOTOR_PWM, DISABLE);
    
    /* Install interrupt callback function */
    TIM_InstallCallBackFunc(HAL_MOTOR_PWM, TIM_INT_FAULT, PwmFaultIntCbf);
    TIM_InstallCallBackFunc(HAL_MOTOR_PWM, TIM_INT_CH3, PwmCPIntCbf);
    
    // Enalbe Fault-in int  fault1 input
    TIM_IntMask(HAL_MOTOR_PWM, TIM_INT_FAULT, UNMASK);
    TIM_IntMask(HAL_MOTOR_PWM, TIM_INT_CH3, UNMASK);
    // Enable the TIM0 int
    TIM_DMACtrl(TIM0_ID, TIM_CHANNEL_0, DISABLE);
    TIM_DMACtrl(TIM0_ID, TIM_CHANNEL_1, DISABLE);    
    TIM_DMACtrl(TIM0_ID, TIM_CHANNEL_2, DISABLE);   
    TIM_DMACtrl(TIM0_ID, TIM_CHANNEL_3, DISABLE);
    TIM_DMACtrl(TIM0_ID, TIM_CHANNEL_4, DISABLE);
    TIM_DMACtrl(TIM0_ID, TIM_CHANNEL_5, DISABLE);
    TIM_DMACtrl(TIM0_ID, TIM_CHANNEL_6, DISABLE);
    TIM_DMACtrl(TIM0_ID, TIM_CHANNEL_7, DISABLE);
    
    /*start TIM PWM*/
    TIM_StartCounter(HAL_MOTOR_PWM, TIM_CLK_SOURCE_SYSTEM, TIM_CLK_DIVIDE_2);   // was TIM_CLK_SOURCE_SYSTEM
}
