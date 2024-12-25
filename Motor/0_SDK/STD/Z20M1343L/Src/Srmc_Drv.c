/**************************************************************************************************/
/**
 * @file      : Srmc_Drv.c
 * @brief     : SRMC module driver file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#include "Srmc_Drv.h"

/** @defgroup Private_MacroDefinition
 *  @{
 */

#define SRMC_GIE_BIT_MASK           (0x10000UL)  /* Global Interrupt Enable Bit Position in SRIE*/

/** @} end of Private_MacroDefinition */

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
 /*PRQA S 0303,0306 ++*/
static Reg_Srmc_BfType* const Srmc_RegBfPtr = (Reg_Srmc_BfType*)SRMC_BASE_ADDR;  /* SRMC Register */
static Reg_Srmc_WType* const Srmc_RegWPtr = (Reg_Srmc_WType*)SRMC_BASE_ADDR;/* SRMC Word Register */
static Z20_SCBType* const Core_ScbRegWPtr = (Z20_SCBType*)Z20_SCB_BASE;      /* Core SCB Register */
/*PRQA S 0303,0306 --*/

static const uint32 Srmc_IntMaskTable[] =
{
    0x00000010U,     /*SRMC_INT_TYPE_STOP_WKUP_RST enable mask*/
    0x00000020U,     /*SRMC_INT_TYPE_WDOG enable mask*/
    0x00000040U,     /*SRMC_INT_TYPE_LOCKUP enable mask*/
    0x00000080U,     /*SRMC_INT_TYPE_SW enable mask*/
    0x00000100U,     /*SRMC_INT_TYPE_ADM_AP enable mask*/
    0x00004000U,     /*SRMC_INT_TYPE_SACKERR enable mask*/
    0x00008000U,     /*SRMC_INT_TYPE_PIN enable mask*/
    0x0000C1F0U      /*SRMC_INT_TYPE_ALL*/
};

static Isr_CbFuncType * Srmc_IsrCbFuncPtr = NULL_PTR;

/** @} end of group Private_VariableDefinition */

/** @defgroup Private_FunctionDeclaration
 *  @{
 */

void Srmc_DriverIrqHandler(void);

/** @} end of group Private_FunctionDeclaration */

/** @defgroup Private_FunctionDefinition
 *  @{
 */

/**
 * @brief       SRMC interrupt handler.
 *
 * @param       None.
 *
 * @return      None.
 * 
 */
void Srmc_DriverIrqHandler(void)
{
    if (Srmc_IsrCbFuncPtr != NULL_PTR)
    {
        Srmc_IsrCbFuncPtr();
    }
}

/** @} end of group Private_FunctionDefinition */

/** @defgroup Public_FunctionDefinition
 *  @{
 */

/**
 * @brief       SRMC trigger software reset to corresponding peripheral.
 *
 * @param[in]   ResetModule:          SRMC software reset type.
 *
 * @return      Software reset status: COMMON_SUCC or COMMON_ERR.
 * 
 * @note        SCM peripheral write lock must be unlock before calling this function.
 *              Mostly:
 *              - Calling function Scm_UnlockPeripheralWritableRegister() to unlock.
 *              - Calling function Scm_LockPeripheralWritableRegister() to lock.
 *
 */
Common_ResultStatusType Srmc_TriggerSwReset(Srmc_SoftwareResetType ResetModule)
{
    volatile uint32 LocalCount;
    uint8 LeftShift;
    Common_ResultStatusType ResetResult;

    LeftShift = (uint8) ResetModule;
    Srmc_RegWPtr->SRMC_SW_RST = (1UL << LeftShift);

    LocalCount = 0;
    ResetResult = COMMON_ERR;
    while (LocalCount < SRMC_SW_RESET_WAIT_CNT)
    {
        if (COMMON_SET == Srmc_GetSwResetStatus(ResetModule))
        {
            ResetResult = COMMON_SUCC;
            break;
        }
        else
        {
            LocalCount++;
        }
    }
    return ResetResult;
}

/**
 * @brief       SRMC get software reset flag status, indicating corresponding  
 *              peripheral reset by software.
 *
 * @param[in]   ResetModule:          SRMC software reset type.
 *
 * @return      status.
 *
 */
Common_FlagStatusType Srmc_GetSwResetStatus(Srmc_SoftwareResetType ResetModule)
{
    uint8 LeftShift = (uint8) ResetModule;
    Common_FlagStatusType Status;

    if (0U == (Srmc_RegWPtr->SRMC_SW_RST_FLAG & (1UL << LeftShift)))
    {
        Status = COMMON_RESET;
    }
    else
    {
        Status = COMMON_SET;
    }
    
    return Status;
}

/**
 * @brief       SRMC clear software reset flag status.
 *
 * @param[in]   ResetModule:          SRMC software reset type.
 *
 * @return      none.
 *
 */
void Srmc_ClearSwResetStatus(Srmc_SoftwareResetType ResetModule)
{
    uint8 LeftShift = (uint8) ResetModule;
    Srmc_RegWPtr->SRMC_SW_RST_FLAG = (1UL << LeftShift);
}

/**
 * @brief       configure core lockup reset enable/disable.
 *
 * @param[in]   Cmd:          control cmd:   DISABLE; ENABLE.
 *
 * @return      none.
 * 
 * @note        SCM peripheral write lock must be unlock before calling this function.
 *              Mostly:
 *              - Calling function Scm_UnlockPeripheralWritableRegister() to unlock.
 *              - Calling function Scm_LockPeripheralWritableRegister() to lock.
 *
 */
void Srmc_CtrlCoreLockupReset(Common_ControlStateType Cmd)
{
    Srmc_RegBfPtr->SRMC_RST_CTRL.LOCKUP_RST_EN = (uint32)Cmd;
}

/**
 * @brief       SRMC wakeup source function enable/disable
 *
 * @param[in]   Source:          wakeup source select.
 * @param[in]   Cmd:             enable/disable.
 *
 * @return      none.
 * 
 * @note        SCM peripheral write lock must be unlock before calling this function.
 *              Mostly:
 *              - Calling function Scm_UnlockPeripheralWritableRegister() to unlock.
 *              - Calling function Scm_LockPeripheralWritableRegister() to lock.
 *
*/
void Srmc_CtrlWakeupSource(Srmc_WakeupSourceType Source, Common_ControlStateType Cmd)
{
    uint8 LeftShift = (uint8) Source;

    if (COMMON_DISABLE == Cmd)
    {
        Srmc_RegWPtr->SRMC_PM_WKUP_CTRL1 &= (~(0x1UL << LeftShift));
    }
    else
    {
        Srmc_RegWPtr->SRMC_PM_WKUP_CTRL1 |= (0x1UL << LeftShift);
    }
}

/**
 * @brief       SRMC get wakeup source status, indicating corresponding wakeup 
 *              source waked up system.
 *
 * @param[in]   Source:          wakeup source select.
 *
 * @return      status.
 *
 */
Common_FlagStatusType Srmc_GetWakeupSourceStatus(Srmc_WakeupSourceType Source)
{
    uint8 LeftShift = (uint8) Source;
    Common_FlagStatusType Status;
    
    if (0UL == (Srmc_RegWPtr->SRMC_PM_WKUP_STAT & (0x1UL << LeftShift)))
    {
        Status = COMMON_RESET;
    }
    else
    {
        Status = COMMON_SET;
    }
    
    return Status;
}

/**
 * @brief       SRMC clear wakeup source status, indicating corresponding wakeup
 *              source waked up system.
 *
 * @param[in]   Source:          wakeup source select.
 *
 * @return      none.
 *
 */
void Srmc_ClearWakeupSourceStatus(Srmc_WakeupSourceType Source)
{
    uint8 LeftShift = (uint8) Source;

    Srmc_RegWPtr->SRMC_PM_WKUP_STAT |= ((0x1UL) << LeftShift);
}

/**
 * @brief       configure reset pin filter bus clock width,
 *              actual reset pin bus clock filter width cycle = ClkCycles + 1.
 *
 * @param[in]   ClkCycles:          cycle number.
 *
 * @return      none.
 * 
 * @note        SCM peripheral write lock must be unlock before calling this function.
 *              Mostly:
 *              - Calling function Scm_UnlockPeripheralWritableRegister() to unlock.
 *              - Calling function Scm_LockPeripheralWritableRegister() to lock.
 *
 */
void Srmc_ConfigBusClockResetPinFilter(uint8 ClkCycles)
{
    Srmc_RegBfPtr->SRMC_RST_CTRL.RSTFLTSEL = (uint32)ClkCycles & 0x1FUL;
}

/**
 * @brief       configure how reset pin filter is enabled in stop mode.
 *
 * @param[in]   PinFilter:    only two type used in stop mode, as below:
 *                             - SRMC_RESET_PIN_DISABLE_FILTER;
 *                             - SRMC_RESET_PIN_LPO_CLOCK_FILTER.
 *
 * @return      none.
 * 
 * @note        SCM peripheral write lock must be unlock before calling this function.
 *              Mostly:
 *              - Calling function Scm_UnlockPeripheralWritableRegister() to unlock.
 *              - Calling function Scm_LockPeripheralWritableRegister() to lock.
 *
 */
void Srmc_ConfigStopModeResetPinFilter(Srmc_ResetPinFilterType PinFilter)
{
    Srmc_RegBfPtr->SRMC_RST_CTRL.RSTFLTSS = ((uint32)PinFilter >> 1U) & 0x01U;
}

/**
 * @brief       configure how reset pin filter is enabled in run mode
 *
 * @param[in]   PinFilter:    three type used in run mode, as below:
 *                             - SRMC_RESET_PIN_DISABLE_FILTER
 *                             - SRMC_RESET_PIN_BUS_CLOCK_FILTER
 *                             - SRMC_RESET_PIN_LPO_CLOCK_FILTER
 *
 * @return      none.
 *
 * @note        SCM peripheral write lock must be unlock before calling this function.
 *              Mostly:
 *              - Calling function Scm_UnlockPeripheralWritableRegister() to unlock.
 *              - Calling function Scm_LockPeripheralWritableRegister() to lock.
 * 
 */
void Srmc_ConfigRunModeResetPinFilter(Srmc_ResetPinFilterType PinFilter)
{
    Srmc_RegBfPtr->SRMC_RST_CTRL.RSTFLTSRW = (uint32)PinFilter;
}

/**
 * @brief       Get the status that if the pointed reset type is the system
 *              reset cause.
 *
 * @param[in]   ResetCause:          reset cause type.
 *
 * @return      status.
 *
 */
Common_FlagStatusType Srmc_GetSystemResetStatus(Srmc_ResetCauseType ResetCause)
{
    Common_FlagStatusType Status;
    
    if (0UL == (Srmc_RegWPtr->SRMC_RST_SSRS & (uint32)ResetCause))
    {
        Status = COMMON_RESET;
    }
    else
    {
        Status = COMMON_SET;
    }

    return Status;
}

/**
 * @brief       Clear the status that if the pointed reset type.
 *
 * @param[in]   ResetCause:          reset cause type.
 *
 * @return      status.
 *
 */
void Srmc_ClearSystemResetStatus(Srmc_ResetCauseType ResetCause)
{
    Srmc_RegWPtr->SRMC_RST_SSRS = (uint32 )ResetCause;
}

/**
 * @brief       Get system reset all causes.
 *
 * @param[in]   none.
 *
 * @return      reset cause type(uint32 value): one bit, one cause;
 *              seeing SRMC_ResetCause_t type.
 *
 */
uint32 Srmc_GetSystemResetCause(void)
{   
    uint32 ResetCause;
    
    ResetCause = Srmc_RegWPtr->SRMC_RST_SRS & (uint32)SRMC_RESET_TYPE_ALL;

    return ResetCause;
}

/**
 * @brief       Unmask/Mask pointed interrupt.
 *
 * @param[in]   IntType:          srmc interrupt source.
 * @param[in]   IntMask:          UNMASK or MASK.
 *
 * @return      none.
 * 
 * @note        SCM peripheral write lock must be unlock before calling this function.
 *              Mostly:
 *              - Calling function Scm_UnlockPeripheralWritableRegister() to unlock.
 *              - Calling function Scm_LockPeripheralWritableRegister() to lock.
 *
 */
void Srmc_SetIntMask(Srmc_IntType IntType, Common_IntMaskType IntMask)
{
    if (COMMON_UNMASK == IntMask)
    {
        Srmc_RegWPtr->SRMC_RST_SRIE |= (Srmc_IntMaskTable[IntType] | SRMC_GIE_BIT_MASK);
    }
    else
    {
        Srmc_RegWPtr->SRMC_RST_SRIE &= ~Srmc_IntMaskTable[IntType];
        if (0U == (Srmc_RegWPtr->SRMC_RST_SRIE & Srmc_IntMaskTable[SRMC_INT_TYPE_ALL]))
        {
            Srmc_RegWPtr->SRMC_RST_SRIE &= ~SRMC_GIE_BIT_MASK;
        }
    }
}


/**
 * @brief       Configure max reset delay time from when the interrupt is 
 *              asserted and the system reset occurs.
 *
 * @param[in]   Delay:          delay cycle type.
 *
 * @return      none.
 * 
 * @note        SCM peripheral write lock must be unlock before calling this function.
 *              Mostly:
 *              - Calling function Scm_UnlockPeripheralWritableRegister() to unlock.
 *              - Calling function Scm_LockPeripheralWritableRegister() to lock.
 *
 */
void Srmc_ConfigMaxResetDelayTime(Srmc_DelayType Delay)
{
    Srmc_RegBfPtr->SRMC_RST_SRIE.DELAY = (uint32)Delay;
}

/**
 * @brief       Configure standby mode entry allowed or not.
 *
 * @param[in]   Cmd:          DISABLE or ENABLE.
 *
 * @return      none.
 * 
 * @note        SCM peripheral write lock must be unlock before calling this function.
 *              Mostly:
 *              - Calling function Scm_UnlockPeripheralWritableRegister() to unlock.
 *              - Calling function Scm_LockPeripheralWritableRegister() to lock.
 *
 */
void Srmc_CtrlStandbyMode(Common_ControlStateType Cmd)
{
    Srmc_RegBfPtr->SRMC_PM_PROT.APD = (uint32)Cmd;
}

/**
 * @brief       Set system enter stop mode(deep sleep mode).
 *
 * @param[in]   AckTimeout: low power mode acknowledge time out.
 * @note        setting ackTimeout to 0 means the stop sequence will wait forever.
 *
 * @return      none.
 * 
 * @note        SCM peripheral write lock must be unlock before calling this function.
 *              Mostly:
 *              - Calling function Scm_UnlockPeripheralWritableRegister() to unlock.
 *              - Calling function Scm_LockPeripheralWritableRegister() to lock.
 *
 */
void Srmc_EnterStopMode(uint8 AckTimeout)
{
    Srmc_RegBfPtr->SRMC_PM_CTRL.DSMACKTMO = AckTimeout;
    
    /*10'b : STOP mode*/
    Srmc_RegBfPtr->SRMC_PM_CTRL.DSMC = 2U;
    
    Core_ScbRegWPtr->SCR |= SCB_SCR_SLEEPDEEP_MASK;
    
    COMMON_WFI();
}

/**
 * @brief       Set system enter standby mode.
 *
 * @param[in]   AckTimeout: low power mode acknowledge time out.
 * @note        setting ackTimeout to 0 means the stop sequence will wait forever.
 * 
 * @return      none.
 * 
 * @note        SCM peripheral write lock must be unlock before calling this function.
 *              Mostly:
 *              - Calling function Scm_UnlockPeripheralWritableRegister() to unlock.
 *              - Calling function Scm_LockPeripheralWritableRegister() to lock.
 *
 */
void Srmc_EnterStandbyMode(uint8 AckTimeout)
{
    Srmc_RegBfPtr->SRMC_PM_CTRL.DSMACKTMO = AckTimeout;
    
    /*11'b : Standby mode*/
    Srmc_RegBfPtr->SRMC_PM_CTRL.DSMC = 3U;

    Core_ScbRegWPtr->SCR |= SCB_SCR_SLEEPDEEP_MASK;
    
    COMMON_WFI();
}

/**
 * @brief       Get current power mode.
 *
 * @param[in]   none.
 *
 * @return      power mode type.
 *
 */
Srmc_PowerModeType Srmc_GetCurrentPowerMode(void)
{
    Srmc_PowerModeType PowerMode;
    uint8 PowerModeInReg = (uint8)Srmc_RegBfPtr->SRMC_PM_STAT.PMSTAT;
    
    switch(PowerModeInReg)
    {
        case 1U:
            PowerMode = SRMC_POWERMODE_RUN;
            break;
     
        case 2U:
            PowerMode = SRMC_POWERMODE_STOP;
            break;
        
        case 4U:
            PowerMode = SRMC_POWERMODE_STANDBY;
            break;
            
        default:
            PowerMode = SRMC_POWERMODE_RUN;
            break;
    }
    
    return PowerMode;
}

/**
 * @brief       Get previous stop mode(deep sleep mode) entry status.
 *
 * @param[in]   none.
 *
 * @return      stop entry status: 
 *              - SRMC_STOP_SUCCESS; 
 *              - SRMC_STOP_ABORT.
 *
 */
Srmc_StopModeStatusType Srmc_GetStopAbortedStatus(void)
{
    return (Srmc_StopModeStatusType)Srmc_RegBfPtr->SRMC_PM_STAT.DSMABORT;
}

/**
 * @brief       Install callback func.
 *
 * @param[in]   CbFunc  : callback function pointer.
 *
 * @return      none
 *
 */
void Srmc_InstallCallBackFunc(Isr_CbFuncType * CbFunc)
{
    Srmc_IsrCbFuncPtr = CbFunc;
}

/** @} end of group Public_FunctionDefinition */
