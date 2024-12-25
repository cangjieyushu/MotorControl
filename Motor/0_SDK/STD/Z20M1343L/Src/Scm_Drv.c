/**************************************************************************************************/
/**
 * @file      : Scm_Drv.c
 * @brief     : SCM module driver file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#include "Scm_Drv.h"

/** @defgroup Private_MacroDefinition
 *  @{
 */
#define SCM_REGISTER_WRITE_UNLOCK_VALUE      (0x5A5A5A5AU)
#define SCM_REGISTER_WRITE_LOCK_VALUE        (0xA5A5A5A5U)
/** @} end of group Private_MacroDefinition */

/** @defgroup Private_TypeDefinition
 *  @{
 */

/** @} end of group Private_TypeDefinition */

/** @defgroup Global_VariableDefinition
 *  @{
 */

/** @} end of group Global_VariableDefinition */

/** @defgroup Private_VariableDefinition
 *  @{
 */

/*PRQA S 0303 ++*/
static Reg_Scm_BfType *const Scm_RegBfPtr  = (Reg_Scm_BfType *) SCM_BASE_ADDR;     /*!< SCM Register */
static Reg_Scm_WType  *const Scm_RegWPtr = (Reg_Scm_WType *) SCM_BASE_ADDR;   /*!< SCM Word Register */
/*PRQA S 0303 --*/

static const uint32 Scm_EccErrorTable[] = 
{
    0x20000000U,    /* ECC single bit error status */
    0x40000000U,    /* ECC multi bit error status */
    0x80000000U,    /* ECC overrun error status */
    0xE0000000U     /* All ECC error status */
};

static Isr_CbFuncType * Scm_NmiCbFuncPtr[SCM_LEVEL2_NMI_ALL] = 
{
    NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, 
    NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR
};

/** @} end of group Private_VariableDefinition */

/** @defgroup Private_FunctionDeclaration
 *  @{
 */
LOCAL_INLINE void Scm_UnlockWritableRegister(void);
LOCAL_INLINE void Scm_LockWritableRegister(void);

void NMI_Handler(void);
 /** @} end of group Private_FunctionDeclaration */

 /** @defgroup Private_FunctionDefinition
 *  @{
 */

/**
 * @brief      Unlock writing registers.
 * @param[in]  none
 *
 * @return     none
 *
 */
LOCAL_INLINE void Scm_UnlockWritableRegister(void)
{
    if (Scm_RegWPtr->SCM_WRITE_LOCK != SCM_REGISTER_WRITE_UNLOCK_VALUE)
    {
        Scm_RegWPtr->SCM_WRITE_LOCK = SCM_REGISTER_WRITE_UNLOCK_VALUE;
    }
}

/**
 * @brief      Lock writing registers.
 * @param[in]  none
 *
 * @return     none
 *
 */
LOCAL_INLINE void Scm_LockWritableRegister(void)
{
    Scm_RegWPtr->SCM_WRITE_LOCK = SCM_REGISTER_WRITE_LOCK_VALUE;
}

/**
 * @brief      NMI Handler
 *
 * @param[in]  none
 *
 * @return    none
 * 
 * @note      All the interrupt in this API are level2 interrupt, the SCM_LEVEL2_NMI_MCPWM_FAULT and 
 *            SCM_LEVEL2_NMI_HARD_FAILURE includes level1 interrupts. In this case, user should
 *            check which type level1 interrupt in user callback function.
 *
 */ 
void NMI_Handler(void)
{
    uint8 IntType;

    if ((Scm_RegBfPtr->SCM_NMI_LVL2_INT_FLAG.SCM_NMI_LVL2_INT_FLAG & \
        ((uint16)1U << (uint16)SCM_LEVEL2_NMI_WDOG_PRE_WARNING)) != 0U)
    {
        if (Scm_NmiCbFuncPtr[SCM_LEVEL2_NMI_WDOG_PRE_WARNING] != NULL_PTR)
        {
            Scm_NmiCbFuncPtr[SCM_LEVEL2_NMI_WDOG_PRE_WARNING]();
        }
        else
        {
            Scm_RegBfPtr->SCM_NMI_LVL2_INT_EN.SCM_NMI_LVL2_INT_EN &= 
                        (~((uint16)1U << (uint16)SCM_LEVEL2_NMI_WDOG_PRE_WARNING));
        }
    }
    else
    {
        for (IntType = (uint8)SCM_LEVEL2_NMI_GDU_WARNING; IntType < (uint8)SCM_LEVEL2_NMI_ALL; IntType++)
        {
            if ((uint8)SCM_LEVEL2_NMI_WDOG_PRE_WARNING != IntType)
            {
                if ((Scm_RegBfPtr->SCM_NMI_LVL2_INT_FLAG.SCM_NMI_LVL2_INT_FLAG & \
                    ((uint16)1U << (uint16)IntType)) != 0U)
                {
                    if (Scm_NmiCbFuncPtr[IntType] != NULL_PTR)
                    {
                        Scm_NmiCbFuncPtr[IntType]();
                    }
                    else
                    {
                        Scm_RegBfPtr->SCM_NMI_LVL2_INT_EN.SCM_NMI_LVL2_INT_EN &= 
                          (~((uint16)1U << (uint16)IntType));
                    }
                }
            }
        }
    }
}

/** @} end of group Private_FunctionDefinition */

/** @defgroup Public_FunctionDefinition
 *  @{
 */

/**
 * @brief      Enable peripheral register write lock. This API will lock all the peripheral
 *                writable registers, which are static configuration for the peripheral. When the 
 *                PERI_WLK bit is locked, all peripheral writable registers can not be written.
 *
 * @param[in]  none. 
 *
 * @return     none
 *
 */
void Scm_LockPeripheralWritableRegister(void)
{
    /* unlock SCM write lock */
    Scm_UnlockWritableRegister();

    /* unlock write register lock */
    if (1U == Scm_RegBfPtr->SCM_PERI_CTRL.LOCK)
    {
        Scm_RegWPtr->SCM_PERI_CTRL = 0x5B000000U;
    }
    
    Scm_RegBfPtr->SCM_PERI_CTRL.PERI_WLK = 1U; 

    /* lock write register */
    Scm_RegBfPtr->SCM_PERI_CTRL.LOCK = 1U;
    /* lock SCM write lock */
    Scm_LockWritableRegister();
}

/**
 * @brief      Disable peripheral register write lock. This API will unlock all the peripheral
 *                writable registers, which are static configuration for the peripheral. When the 
 *                PERI_WLK bit is unlocked, all peripheral writable registers can be written.
 *
 * @param[in]  none. 
 *
 * @return     none
 *
 */
void Scm_UnlockPeripheralWritableRegister(void)
{
    /* unlock SCM write lock */
    Scm_UnlockWritableRegister();

    /* unlock write register lock */
    if (Scm_RegBfPtr->SCM_PERI_CTRL.LOCK == 1U)
    {
        Scm_RegWPtr->SCM_PERI_CTRL = 0x5B000000U;
    }
    
    Scm_RegBfPtr->SCM_PERI_CTRL.PERI_WLK = 0U; 

    /* lock write register */
    Scm_RegBfPtr->SCM_PERI_CTRL.LOCK = 1U;
    /* lock SCM write lock */
    Scm_LockWritableRegister();
}

/**
 * @brief      Select UART LIN or PWM module config.
 * @param[in]  Type: SCM LIN UART PWM module select type :
 *               - SCM_UART: select UART function
 *               - SCM_LIN: select LIN function
 *               - SCM_MCPWM_CTIMER_COM: PWM CHO[7] output to channel PORT TX or to LIN/PWM-COM 
 *                                       CTIMER CHI[4] input from LIN/PWM-COM
 *               - SCM_MCPWM_CTIMER_PORTRX: PWM CHO[7] output to channel PORT TX or to LIN/PWM-COM 
 *                                          CTIMER CHI[4] input from PORT RX
 *
 * @return     none
 *
 */
void Scm_SelectLinPwmModule(Scm_LinPwmSelectionType Type)
{
    Scm_UnlockWritableRegister();
    switch (Type)
    {
        case SCM_UART:
            Scm_RegBfPtr->SCM_MISCCTL1.SCM_LINPWM_SEL = 0U;
            Scm_RegBfPtr->SCM_MISCCTL1.SCM_LIN_SEL = 1U;
            break;
        case SCM_LIN:
            Scm_RegBfPtr->SCM_MISCCTL1.SCM_LINPWM_SEL = 0U;
            Scm_RegBfPtr->SCM_MISCCTL1.SCM_LIN_SEL = 0U;
            break;
        case SCM_MCPWM_CTIMER_COM:
            Scm_RegBfPtr->SCM_MISCCTL1.SCM_LINPWM_SEL = 1U;
            Scm_RegBfPtr->SCM_MISCCTL1.SCM_LIN_SEL = 0U;
            break;
        case SCM_MCPWM_CTIMER_PORTRX:
            Scm_RegBfPtr->SCM_MISCCTL1.SCM_LINPWM_SEL = 1U;
            Scm_RegBfPtr->SCM_MISCCTL1.SCM_LIN_SEL = 1U;
            break;
        default:
            /* Do nothing */
            break;
    }
    Scm_LockWritableRegister();
}

/**
 * @brief      Select PWM module channel output type for PWM signal monitor
 * @param[in]  Type: PWM channel output type:
 *                   - SCM_PWM_CHANNEL_OUTPUT: select pwm chout[7:0]
 *                   - SCM_TDG_TRIGGER: select {trigger_out[2:0],trigger_in[2:0],chout[1:0]}
 *
 * @return     none
 *
 */
void Scm_SelectPwmChannelOutput(Scm_PwmChannelOutputType Type)
{
    Scm_UnlockWritableRegister();
    Scm_RegBfPtr->SCM_MISCCTL1.SCM_PWM_CHOUT_SEL = (uint32)Type;
    Scm_LockWritableRegister();
}

/**
 * @brief      Set SRAM ECC read control status.
 * @param[in]  Status: SRAM ECC read status :
 *                   - COMMON_ENABLE: SRAM ECC read enable
 *                   - COMMON_DISABLE: SRAM ECC read disable
 *
 * @return     none
 *
 */
void Scm_SetSramEccRead(Common_ControlStateType Status)
{
    Scm_UnlockWritableRegister();
    Scm_RegBfPtr->SCM_ECC_CTRL.SRAM_ECCR_DIS = (Status == COMMON_ENABLE) ? 0u: 1u;
    Scm_LockWritableRegister();
}

/**
 * @brief      Set SRAM ECC write control status.
 *
 * @param[in]  Status: SRAM ECC write status:
 *                 - COMMON_ENABLE: SRAM ECC write enable
 *                 - COMMON_DISABLE: SRAM ECC write disable
 *
 * @return     none
 *
 */
void Scm_SetSramEccWrite(Common_ControlStateType Status)
{
    Scm_UnlockWritableRegister();
    Scm_RegBfPtr->SCM_ECC_CTRL.SRAM_ECCW_DIS = (Status == COMMON_ENABLE) ? 0u: 1u;
    Scm_LockWritableRegister();
}

/**
 * @brief      Set SRAM ECC single bit control status.
 * 
 * @param[in]  Status: SRAM ECC single bit status :
 *                 - COMMON_ENABLE: SRAM ECC single bit enable
 *                 - COMMON_DISABLE: SRAM ECC single bit disable
 *
 * @return     none
 *
 */
void Scm_SetSramEccSingleBit(Common_ControlStateType Status)
{
    Scm_UnlockWritableRegister();
    Scm_RegBfPtr->SCM_ECC_CTRL.SRAM_ECCSB_DIS = (Status == COMMON_ENABLE) ? 0u: 1u;
    Scm_LockWritableRegister();
}

/**
 * @brief      Set SRAM ECC multi bit control status.
 * @param[in]  Status: SRAM ECC multi bit status :
 *                 - COMMON_ENABLE: SRAM ECC multi bit enable
 *                 - COMMON_DISABLE: SRAM ECC multi bit disable
 *
 * @return     none
 *
 */
void Scm_SetSramEccMultiBit(Common_ControlStateType Status)
{
    Scm_UnlockWritableRegister();
    Scm_RegBfPtr->SCM_ECC_CTRL.SRAM_ECCMB_DIS = (Status == COMMON_ENABLE) ? 0u: 1u;
    Scm_LockWritableRegister();
}

/**
 * @brief      Get SRAM ECC error cause
 *
 * @param[in]  CausePtr: the cause of SRAM ECC error will be stored in the struct 
 *                    that is pointed by this parameter. 
 *
 * @return none
 *
 */
void Scm_GetSramEccErrCause(Scm_SramEccErrCauseType *CausePtr)
{
    if (NULL_PTR != CausePtr)
    {
        CausePtr->ErrFaultAddr = Scm_RegWPtr->SCM_SRAM_ECC_FADDR;
        CausePtr->ErrFaultData = Scm_RegWPtr->SCM_SRAM_ECC_FDATA;
        CausePtr->IsWriting        = (Common_FlagStatusType)Scm_RegBfPtr->SCM_SRAM_ECC_ST.SRAM_EFW;
        CausePtr->ErrFaultMaster = (Scm_MasterType)(Scm_RegBfPtr->SCM_SRAM_ECC_ST.SRAM_EFMST);
        CausePtr->ErrFaultSize = (Scm_AccessSizeType)(Scm_RegBfPtr->SCM_SRAM_ECC_ST.SRAM_EFSIZE);
        CausePtr->AccessType = (((Scm_RegBfPtr->SCM_SRAM_ECC_ST.SRAM_EFPROT)&
                0x00000001UL) == 0U)? SCM_ACC_TYPE_OPCODE : SCM_ACC_TYPE_DATA;
        CausePtr->AccessMode = (((Scm_RegBfPtr->SCM_SRAM_ECC_ST.SRAM_EFPROT)&
                0x00000002UL) == 0U)? SCM_ACC_MODE_USER : SCM_ACC_MODE_PRIVIL;
        CausePtr->BufferableType = (((Scm_RegBfPtr->SCM_SRAM_ECC_ST.SRAM_EFPROT)&
                0x00000004UL) == 0U)? SCM_ACC_NON_BUFFERABLE : SCM_ACC_BUFFERABLE;
        CausePtr->CacheType = (((Scm_RegBfPtr->SCM_SRAM_ECC_ST.SRAM_EFPROT)&
                0x00000008UL) == 0U)? SCM_ACC_NON_CACHEABLE : SCM_ACC_CACHEABLE;
    }
    else
    {
        /*Do nothing*/
    }
}

/**
 * @brief      Get SRAM ECC error status
 *
 * @param[in]  EccErrorType: select the error status type to get :
 *               - SCM_ECC_ERR_SINGLEBIT: signal bit ECC error
 *               - SCM_ECC_ERR_MULTIBIT: multi bit ECC error
 *               - SCM_ECC_ERR_OVERRUN: ECC overrun error
 *               - SCM_ECC_ERR_ALL: All ECC error
 *
 * @return    Error status
 * @retval    COMMON_RESET: the error status is not set
 * @retval    COMMON_SET: the error status is set
 *
 */
Common_FlagStatusType Scm_GetSramEccErrStatus(Scm_EccErrorType EccErrorType)
{
    Common_FlagStatusType ErrorStatus = COMMON_RESET;

    ErrorStatus = ((Scm_RegWPtr->SCM_SRAM_ECC_ST & Scm_EccErrorTable[EccErrorType]) != 0U) ? 
                                       COMMON_SET : COMMON_RESET;

    return ErrorStatus;
}

/**
 * @brief      Clear SRAM ECC error status
 * @param[in]  EccErrorType: select the error status type to clear :
 *               - SCM_ECC_ERR_SINGLEBIT: signal bit ECC error
 *               - SCM_ECC_ERR_MULTIBIT: multi bit ECC error
 *               - SCM_ECC_ERR_OVERRUN: ECC overrun error
 *               - SCM_ECC_ERR_ALL: All ECC error
 *
 * @return    None
 *
 */
void Scm_ClearSramEccErrStatus(Scm_EccErrorType EccErrorType)
{
    Scm_UnlockWritableRegister();
    Scm_RegWPtr->SCM_SRAM_ECC_ST = Scm_RegWPtr->SCM_SRAM_ECC_ST | Scm_EccErrorTable[EccErrorType];
    Scm_LockWritableRegister();
}

/**
 * @brief      SRAM Init Trig Function
 *
 * @param[in]  None
 *
 * @return     Common_ResultStatusType:
 *              - COMMON_SUCC: SRAM init successfully
 *              - COMMON_ERR: SRAM init failed
 *
 */
Common_ResultStatusType Scm_SetSramInitTrig(void)
{
    volatile uint32 localCnt = 0;
    Common_ResultStatusType retVal = COMMON_SUCC;

    Scm_UnlockWritableRegister();

    Scm_RegBfPtr->SCM_MISCCTL1.SRAM_INIT_TRIG = (uint32)1U;
    while(1U != Scm_RegBfPtr->SCM_MISCSTAT1.SRAM_INIT_DONE)
    {
        if(localCnt > SCM_SRAM_INIT_TIMEOUT_WAIT_CNT)
        {
            retVal = COMMON_ERR;
            break;
        }
        else
        {
            localCnt++;
        } 
    }
    Scm_RegBfPtr->SCM_MISCCTL1.SRAM_INIT_TRIG = (uint32)0U;

    Scm_LockWritableRegister();
    
    return retVal;
}

/**
 * @brief      set CSA logic enable.
 * @param[in]  Status: CSA logic status :
 *                 - ENABLE: CSA logic enable
 *                 - DISABLE: CSA logic disable
 *
 * @return     none
 *
 */
void Scm_SetCsaLogicEnable(Common_ControlStateType Status)
{
    Scm_UnlockWritableRegister();
    Scm_RegBfPtr->SCM_CSA_CTRL.SCM_CSA_EN = (uint32)Status;
    Scm_LockWritableRegister();
}

/**
 * @brief      get CSA logic status.
 * @param[in]  none
 *
 * @return     CSA logic status
 * @return 
 */
Common_ControlStateType Scm_GetCsaLogicStatus(void)
{
    return (Common_ControlStateType)Scm_RegBfPtr->SCM_CSA_CTRL.SCM_CSA_EN;
}

/**
 * @brief      set CSA vzero control signal.
 * @param[in]  ControlCmd: CSA vzero control command
 *                 - SCM_CSA_OUTPUT_AMPLIFIER_SIGNAL: CSA output amplifier signal
 *                 - SCM_CSA_OUTPUT_VZERO_VOLTAGE: CSA output vzero voltage
 *
 * @return     none
 *
 */
void Scm_SetCsaVzeroControlSignal(Scm_CsaVzeroControlType ControlCmd)
{
    Scm_UnlockWritableRegister();
    Scm_RegBfPtr->SCM_CSA_CTRL.SCM_CSA_VZERO_CTRL = (uint32)ControlCmd;
    Scm_LockWritableRegister();
}

/**
 * @brief      get CSA vzero control signal.
 * @param[in]  none
 *
 * @return     CSA vzero control signal
 *
 */
Scm_CsaVzeroControlType Scm_GetCsaVzeroControlSignal(void)
{
    return (Scm_CsaVzeroControlType)Scm_RegBfPtr->SCM_CSA_CTRL.SCM_CSA_VZERO_CTRL;
}

/**
 * @brief      set CSA gain.
 * @param[in]  Gain: CSA gain
 *                 - SCM_CSA_OUTPUT_AMPLIFIER_SIGNAL: CSA output amplifier signal
 *                 - SCM_CSA_OUTPUT_VZERO_VOLTAGE: CSA output vzero voltage
 *
 * @return     none
 *
 */
void Scm_SetCsaGain(Scm_CsaGainType Gain)
{
    Scm_UnlockWritableRegister();
    Scm_RegBfPtr->SCM_CSA_CTRL.SCM_CSA_GAIN = (uint32)Gain;
    Scm_LockWritableRegister();
}

/**
 * @brief      get CSA gain.
 * @param[in]  none
 *
 * @return     CSA gain
 *
 */
Scm_CsaGainType Scm_GetCsaGain(void)
{
    return (Scm_CsaGainType)Scm_RegBfPtr->SCM_CSA_CTRL.SCM_CSA_GAIN;
}

/**
 * @brief      Config PAD fault polarity.
 * @param[in]  PolarityType: polarity type
 *                 - SCM_PAD_FAULT_POLARITY_0: normal status is 0, fault valid polarity is 1
 *                 - SCM_PAD_FAULT_POLARITY_1: normal status is 1, fault valid polarity is 0
 *
 * @return     none
 *
 */
void Scm_ConfigPadFaultPolarity(Scm_PadFaultPolarityType PolarityType)
{
    Scm_UnlockWritableRegister();
    Scm_RegBfPtr->SCM_NMI_LVL1_INT_EN.SCM_PAD_FLT_POLARITY = (uint8)PolarityType;
    Scm_LockWritableRegister();
}

/**
 * @brief      Get PAD fault polarity config type.
 *
 * @return     PAD fault polarity config type 
 * @retval     SCM_PAD_FAULT_POLARITY_0: normal status is 0, fault valid polarity is 1
 * @retval     SCM_PAD_FAULT_POLARITY_1: normal status is 1, fault valid polarity is 0
 *
 */
Scm_PadFaultPolarityType Scm_GetPadFaultPolarity(void)
{
    return (Scm_PadFaultPolarityType)Scm_RegBfPtr->SCM_NMI_LVL1_INT_EN.SCM_PAD_FLT_POLARITY;
}

/**
 * @brief      Config MCPWM PAD fault interrupt enable.
 * @param[in]  Status: MCPWM PAD fault interrupt enable/disable
 *                 - COMMON_DISABLE: disable PWM PAD fault interrupt
 *                 - COMMON_ENABLE: enable PWM PAD fault interrupt
 *
 * @return     none
 *
 */
void Scm_EnablePadFaultInt(Common_ControlStateType Status)
{
    Scm_UnlockWritableRegister();
    Scm_RegBfPtr->SCM_NMI_LVL1_INT_EN.SCM_PAD_FAULT_INT_EN = (uint8)Status;
    Scm_LockWritableRegister();
}

/**
 * @brief      Get MCPWM PAD fault interrupt enable status.
 *
 * @return     MCPWM PAD fault interrupt enable status 
 * @retval     COMMON_DISABLE: PWM PAD fault interrupt is disable
 * @retval     COMMON_ENABLE: PWM PAD fault interrupt is enable
 *
 */
Common_ControlStateType Scm_GetPadFaultIntConfig(void)
{
    return (Common_ControlStateType)Scm_RegBfPtr->SCM_NMI_LVL1_INT_EN.SCM_PAD_FAULT_INT_EN;
}

/**
 * @brief      enable level2 NMI interrupt.
 * @param[in]  IntType: control type
 *                 - SCM_LEVEL2_NMI_GDU_WARNING:  GDU warning interrupt
 *                   ...
 *                 - SCM_LEVEL2_NMI_ADC_DISABLE: ADC disable due to VAREF > VDDP interrupt enable
 *
 * @return     none
 *
 */
void Scm_EnableLevel2NMI(Scm_Level2NmiType IntType)
{
    Scm_UnlockWritableRegister();
    Scm_RegBfPtr->SCM_NMI_LVL2_INT_EN.SCM_NMI_LVL2_INT_EN |= ((uint16)1U << (uint16)IntType);
    Scm_LockWritableRegister();
}

/**
 * @brief      disable level2 NMI interrupt.
 * @param[in]  IntType: control type
 *                 - SCM_LEVEL2_NMI_GDU_WARNING:  GDU warning interrupt
 *                   ...
 *                 - SCM_LEVEL2_NMI_ADC_DISABLE: ADC disable due to VAREF > VDDP interrupt enable
 *
 * @return     none
 *
 */
void Scm_DisableLevel2NMI(Scm_Level2NmiType IntType)
{
    Scm_UnlockWritableRegister();
    Scm_RegBfPtr->SCM_NMI_LVL2_INT_EN.SCM_NMI_LVL2_INT_EN &= (~((uint16)1U << (uint16)IntType));
    Scm_LockWritableRegister();
}

/**
 * @brief      get level2 NMI interrupt control status.
 * @param[in]  IntType: control type
 *                 - SCM_LEVEL2_NMI_GDU_WARNING:  GDU warning interrupt
 *                   ...
 *                 - SCM_LEVEL2_NMI_ADC_DISABLE: ADC disable due to VAREF > VDDP interrupt enable
 *
 * @return     level2 NMI interrupt control status
 * @retval     COMMON_SET: interrupt control status set
 * @retval     COMMON_RESET: interrupt control status not set
 *
 */
Common_IntStatusType Scm_GetLevel2NMIControlStatus(Scm_Level2NmiType IntType)
{
    Common_IntStatusType ret = COMMON_RESET;
    if ((Scm_RegBfPtr->SCM_NMI_LVL2_INT_EN.SCM_NMI_LVL2_INT_EN & \
            ((uint16)1U << (uint16)IntType)) != 0U)
    {
        ret = COMMON_SET;
    }
    else
    {
        ret = COMMON_RESET;
    }

    return ret;
}

/**
 * @brief      get level1 NMI interrupt flag.
 * @param[in]  IntType: control type
 *                 - SCM_LEVEL1_CMU_FREQUENCY_ALARM_INT_FLAG:  CMU frequency alarm interrupt flag
 *                 - SCM_LEVEL1_FLASH_ECC_ERROR_INT_FLAG: flash ECC error interrupt flag
 *                 - SCM_LEVEL1_MEMORY_ECC_ERROR_INT_FLAG: memory ECC error interrupt flag
 *                 - SCM_LEVEL1_MCPWM_PAD_FAULT_INT_FLAG:  MCPWM pad fault interrupt flag
 *                 - SCM_LEVEL1_CMP_WARNING_INT_FLAG: CMP warning interrupt flag
 *
 * @return     level1 NMI interrupt flag
 * @retval     COMMON_SET: interrupt flag set
 * @retval     COMMON_RESET: interrupt flag not set
 *
 */
Common_IntStatusType Scm_GetLevel1NMIIntFlag(Scm_Level1NmiIntFlagType IntType)
{
    Common_IntStatusType ret = COMMON_RESET;
    if ((Scm_RegBfPtr->SCM_NMI_LVL1_INT_FLAG.SCM_NMI_LVL1_INT_FLAG & \
            ((uint32)1U << (uint32)IntType)) != 0U)
    {
        ret = COMMON_SET;
    }
    else
    {
        ret = COMMON_RESET;
    }

    return ret;
}

/**
 * @brief      get level2 NMI interrupt flag.
 * @param[in]  IntType: NMI interrupt flag type
 *                 - SCM_LEVEL2_GDU_WARNING_INT_FLAG:  GDU warning interrupt flag
 *                   ...
 *                 - SCM_LEVEL2_ADC_DISABLE_INT_FLAG: ADC disable due to VAREF>VDDP interrupt flag
 *
 * @return     level2 NMI interrupt status
 * @retval     COMMON_SET: interrupt flag set
 * @retval     COMMON_RESET: interrupt flag not set
 *
 */
Common_IntStatusType Scm_GetLevel2NMIIntFlag(Scm_Level2NmiIntFlagType IntType)
{
    Common_IntStatusType ret = COMMON_RESET;
    if ((Scm_RegBfPtr->SCM_NMI_LVL2_INT_FLAG.SCM_NMI_LVL2_INT_FLAG & \
            ((uint16)1U << (uint16)IntType)) != 0U)
    {
        ret = COMMON_SET;
    }
    else
    {
        ret = COMMON_RESET;
    }

    return ret;
}

/**
 * @brief      clear level2 NMI external pin interrupt flag.
 * @param[in]  none
 *
 * @return     none
 *
 */
void Scm_ClearExternalPinIntFlag(void)
{
    if ((Scm_RegBfPtr->SCM_NMI_LVL2_INT_FLAG.SCM_NMI_LVL2_INT_FLAG & \
            ((uint16)1U << (uint16)SCM_LEVEL2_EXTERNAL_NMI_PIN_INT_FLAG)) != 0U)
    {
        Scm_UnlockWritableRegister();
        Scm_RegBfPtr->SCM_NMI_LVL2_INT_FLAG.SCM_NMI_LVL2_INT_FLAG |= 
            ((uint16)1U << (uint16)SCM_LEVEL2_EXTERNAL_NMI_PIN_INT_FLAG);
        Scm_LockWritableRegister();
    }
    else
    {
        /* Do nothing */
    }
}

/**
 * @brief      Get Device ID
 *
 * @param[in]  none
 *
 * @return     Device ID
 *
 */   
uint32 Scm_GetDeviceId(void)
{
    return Scm_RegBfPtr->SCM_DEVID.CHIP_ID;
}

/**
 * @brief      Get Unique Identification 0
 *
 * @param[in]  IdType : Unique ID type
 *                   - SCM_UNIQUE0_TYPE
 *                   - SCM_UNIQUE1_TYPE
 *
 * @return     Unique IDx
 *
 */
uint32 Scm_GetUniqueId(Scm_UniqueIdType IdType)
{
    uint32 UniqueID = 0;

    switch(IdType)
    {
        case SCM_UNIQUE0_TYPE:
            UniqueID = Scm_RegWPtr->SCM_UNIQUE0;
            break;
        case SCM_UNIQUE1_TYPE:
            UniqueID = Scm_RegWPtr->SCM_UNIQUE1;
            break;
        default:
        /* Do nothing */
            break;
    }

    return UniqueID;
}

/**
 * @brief      Scm install NMI interrupt callback function
 *
 * @param[in]  IntType: Select Int type.
 *              - SCM_LEVEL2_NMI_GDU_WARNING,
 *              - SCM_LEVEL2_NMI_VAREF_FAILURE
 *                ...
 *              - SCM_LEVEL2_NMI_ADC_OVER_TEMP_SHUTDOWN
 *              - SCM_LEVEL2_NMI_ADC_DISABLE
 * @param[in]  CbFun: Callback function .
 *
 * @return     None
 *
 */
void Scm_InstallNmiLevel2CallBackFunc(Scm_Level2NmiType IntType, Isr_CbFuncType * CbFun)
{
    if(IntType < (Scm_Level2NmiType)SCM_LEVEL2_NMI_ALL)
    {
        Scm_NmiCbFuncPtr[IntType] = CbFun;
    }
}

/** @} end of group Public_FunctionDefinition */
