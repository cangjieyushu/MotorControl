/**************************************************************************************************/
/**
 * @file      : Tdg_Drv.c
 * @brief     : TDG module driver file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#include "Tdg_Drv.h"
#include "Scm_Drv.h"

/** @defgroup Private_TypeDefinition
 *  @{
 */

/** @} end of group Private_TypeDefinition */

/** @defgroup Private_MacroDefinition
 *  @{
 */

/** @} end of group Private_MacroDefinition */

/** @defgroup Private_VariableDefinition
 *  @{
 */

/*PRQA S 0303 ++*/
static Reg_Tdg_BfType * const Tdg_RegBfPtr =  (Reg_Tdg_BfType *)TDG_BASE_ADDR;
static Reg_Tdg_WType * const Tdg_RegWPtr =  (Reg_Tdg_WType *)TDG_BASE_ADDR;
/*PRQA S 0303 --*/

/** @} end of group Private_VariableDefinition */

/** @defgroup Private_FunctionDeclaration
 *  @{
 */

/** @} end of group Private_FunctionDeclaration */

/** @defgroup Global_VariableDefinition
 *  @{
 */

/** @} end of group Global_VariableDefinition */

/** @defgroup Private_FunctionDeclaration
 *  @{
 */

/** @} end of group Private_FunctionDeclaration */

/** @defgroup Public_FunctionDefinition
 *  @{
 */

/**
 * @brief      TDG enable/disable function
 *
 * @param[in]  Cmd: Common_ControlStateType
 *                     - COMMON_ENABLE: tdg enable
 *                     - COMMON_DISABLE: tdg disable
 *
 * @return     None
 */
void Tdg_Enable(Common_ControlStateType Cmd)
{    
    Tdg_RegBfPtr->TDG_ABS_CONF0.EN = (uint32)Cmd;  
}

/**
 * @brief      TDG select trigger source 
 *
 * @param[in]  ChannelId: Tdg_ChannelIdType
 *                        - TDG_CHANNEL_0
 *                        - TDG_CHANNEL_1
 *                        - TDG_CHANNEL_2
 * @param[in]  Trig: Tdg_TriggerSourceType
 *                       -TDG_TRIG_PWM_INIT0
 *                       -TDG_TRIG_PWM_INIT1
 *                       -TDG_TRIG_PWM_INIT2
 *                       -TDG_TRIG_PWM_CV0
 *                       -TDG_TRIG_PWM_CV1
 *                       -TDG_TRIG_PWM_CV2
 *                       -TDG_TRIG_PWM_CV3
 *                       -TDG_TRIG_PWM_CV4
 *                       -TDG_TRIG_PWM_CV5
 *                       -TDG_TRIG_SW0
 *                       -TDG_TRIG_SW1
 *                       -TDG_TRIG_SW2
 *
 * @return     None
 *
 */
void Tdg_SelectTriggerSource(Tdg_ChannelIdType ChannelId, Tdg_TriggerSourceType Trig)
{
    switch (ChannelId)
    {
        case TDG_CHANNEL_0:
            Tdg_RegBfPtr->TDG_ABS_CH_TRIG_SEL.CH0_TRIG_SEL = (uint32)Trig;
            break;

        case TDG_CHANNEL_1:
            Tdg_RegBfPtr->TDG_ABS_CH_TRIG_SEL.CH1_TRIG_SEL = (uint32)Trig;
            break;

        case TDG_CHANNEL_2:
            Tdg_RegBfPtr->TDG_ABS_CH_TRIG_SEL.CH2_TRIG_SEL = (uint32)Trig;
            break;

        default:
            /*Do nothing*/
            break;
    }
}

/**
 * @brief      TDG software trigger 
 *
 * @param[in]  SwTrigId: Tdg_SoftwareTriggerIdType
 *                        - TDG_SOFTWARE_TRIGGER_0
 *                        - TDG_SOFTWARE_TRIGGER_1
 *                        - TDG_SOFTWARE_TRIGGER_2
 *
 * @return     None
 *
 */
void Tdg_SoftwareTrigger(Tdg_SoftwareTriggerIdType SwTrigId)
{   
    Tdg_RegBfPtr->TDG_ABS_SW_TRIG.SW_TRIG = (1U << (uint32)SwTrigId);
}

/**
 * @brief      TDG absolute delay time value config
 *
 * @param[in]  ChannelId: Tdg_ChannelIdType
 *                        - TDG_CHANNEL_0
 *                        - TDG_CHANNEL_1
 *                        - TDG_CHANNEL_2
 * @param[in]  TimeValue: uint16
 *
 * @return none
 *
 */
void Tdg_SetTimeValue(Tdg_ChannelIdType ChannelId, uint16 TimeValue)
{   
    volatile uint32 *ValRegTable[3] = {
        &Tdg_RegWPtr->TDG_ABS_T0,
        &Tdg_RegWPtr->TDG_ABS_T1,
        &Tdg_RegWPtr->TDG_ABS_T2
    };
    *ValRegTable[ChannelId] = (uint32)TimeValue;
}

/**
 * @brief      Get TDG absolute delay time value
 *
 * @param[in]  ChannelId: Tdg_ChannelIdType
 *                        - TDG_CHANNEL_0
 *                        - TDG_CHANNEL_1
 *                        - TDG_CHANNEL_2
 *
 * @return time value
 *
 */
uint16 Tdg_GetTimeValue(Tdg_ChannelIdType ChannelId)
{
    uint32 RegValue;
    volatile uint32 *ValRegTable[3] = {
        &Tdg_RegWPtr->TDG_ABS_T0,
        &Tdg_RegWPtr->TDG_ABS_T1,
        &Tdg_RegWPtr->TDG_ABS_T2
    };
    RegValue = *ValRegTable[ChannelId];
    return (uint16)RegValue;
}

/**
 * @brief      TDG channel enable/disable
 *
 * @param[in]  ChannelId: Tdg_ChannelIdType
 *                        - TDG_CHANNEL_0
 *                        - TDG_CHANNEL_1
 *                        - TDG_CHANNEL_2
 * @param[in]  Cmd: Common_ControlStateType
 *                        - COMMON_ENABLE: tdg channel enable
 *                        - COMMON_DISABLE: tdg channel disable
 *
 * @return none
 *
 */
void Tdg_EnableChannel(Tdg_ChannelIdType ChannelId, Common_ControlStateType Cmd)
{
    uint32 TempVal = (uint32)Tdg_RegBfPtr->TDG_ABS_CONF0.CH_EN;
    
    switch (ChannelId)
    {
        case TDG_CHANNEL_0:
        case TDG_CHANNEL_1:
        case TDG_CHANNEL_2:
            /* Clear setting */
            TempVal &= (~(0x1UL << (uint32)ChannelId));
            /* Set channel */
            TempVal |= (((uint32)Cmd << (uint32)ChannelId) & 0x7U);
            /* Deploy setting */
            Tdg_RegBfPtr->TDG_ABS_CONF0.CH_EN = TempVal;
            break;

        default:
            /*Do nothing*/
            break;
    }
}

/**
 * @brief       TDG skip cycle config
 *
 * @param[in]  SkipCycle: Tdg_SkipCycleType
 *                              - TDG_SC_0
 *                              - TDG_SC_1
 *                              - TDG_SC_2
 *                              - TDG_SC_3
 *
 * @return none
 *
 */
void Tdg_SetSkipCycleValue(Tdg_SkipCycleType SkipCycle)
{
    Tdg_RegBfPtr->TDG_ABS_SKIP_CYC.SKIP_CYC = (uint32)SkipCycle;
}

/**
 * @brief      Get TDG skip cycle number
 *
 * @param[in]  none
 *
 * @return    Tdg_SkipCycleType
 *                           - TDG_SC_0
 *                           - TDG_SC_1
 *                           - TDG_SC_2
 *                           - TDG_SC_3                       
 *
 */
Tdg_SkipCycleType Tdg_GetSkipCycleValue(void)
{
    return (Tdg_SkipCycleType)(Tdg_RegBfPtr->TDG_ABS_SKIP_CYC.SKIP_CYC);
}

/**
 * @brief      Get TDG channel counter value
 *
 * @param[in]  ChannelId: Tdg_ChannelIdType
 *                        - TDG_CHANNEL_0
 *                        - TDG_CHANNEL_1
 *                        - TDG_CHANNEL_2
 *
 * @return counter value
 *
 */
uint16 Tdg_GetCounterValue(Tdg_ChannelIdType ChannelId)
{
    uint32 RegValue;
    volatile uint32 *CntRegTable[3] = {
        &Tdg_RegWPtr->TDG_ABS_CNT0,
        &Tdg_RegWPtr->TDG_ABS_CNT1,
        &Tdg_RegWPtr->TDG_ABS_CNT2
    };
    RegValue = *CntRegTable[ChannelId];
    return (uint16)RegValue;
}

/**
 * @brief      Get TDG channel counter status
 *
 * @param[in]  ChannelId: Tdg_ChannelIdType
 *                        - TDG_CHANNEL_0
 *                        - TDG_CHANNEL_1
 *                        - TDG_CHANNEL_2
 *
 * @return     Tdg_CounterStatusType
 *                        - TDG_COUNTER_STOPPED
 *                        - TDG_COUNTER_RUNNING
 *
 */
Tdg_CounterStatusType Tdg_GetCounterStatus(Tdg_ChannelIdType ChannelId)
{
    uint32 CounterStatus = 0;
    switch (ChannelId)
    {
        case TDG_CHANNEL_0:
            CounterStatus = Tdg_RegBfPtr->TDG_ABS_CHX_STS.CNT0_RUN;
            break;

        case TDG_CHANNEL_1:
            CounterStatus = Tdg_RegBfPtr->TDG_ABS_CHX_STS.CNT1_RUN;
            break;

        case TDG_CHANNEL_2:
            CounterStatus = Tdg_RegBfPtr->TDG_ABS_CHX_STS.CNT2_RUN;
            break;

        default:
            /*Do nothing*/
            break;
    }
    return (Tdg_CounterStatusType)CounterStatus;
}

/**
 * @brief      Clear TDG channel counter overflow flag
 *
 * @param[in]  ChannelId: Tdg_ChannelIdType
 *                        - TDG_CHANNEL_0
 *                        - TDG_CHANNEL_1
 *                        - TDG_CHANNEL_2
 *
 * @return none
 *
 */
void Tdg_ClearOverflowFlag(Tdg_ChannelIdType ChannelId)
{
    switch (ChannelId)
    {
        case TDG_CHANNEL_0:
        case TDG_CHANNEL_1:
        case TDG_CHANNEL_2:
            Tdg_RegWPtr->TDG_ABS_CHX_STS = (0x1UL << (uint32)ChannelId);
            break;

        default:
            /*Do nothing*/
            break;
    }
}

/** @} end of group Public_FunctionDefinition */
