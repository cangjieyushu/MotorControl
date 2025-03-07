/**************************************************************************************************/
/**
 * @file      : Z20K11xM_srmc.c
 * @brief     : SRMC module driver file.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (C) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#include "Z20K11xM_srmc.h"

/** @addtogroup  Z20K11X_Peripheral_Driver
 *  @{
 */

/** @defgroup SRMC SRMC
 *  @brief SRMC driver modules
 *  @{
 */

/** @defgroup SRMC_Private_Type
 *  @{
 */

/*@} end of group SRMC_Private_Type*/

/** @defgroup SRMC_Private_Defines
 *  @{
 */
#define SRMC_GIE_BIT_POSITION               (7U)    /*Global Interrupt Enable Bit Position in SRIE*/
/*PRQA S 0303,0306 ++*/
static srmc_reg_t *const srmcRegPtr = (srmc_reg_t *) SRMC_BASE_ADDR;        /* SRMC Register */
static srmc_reg_w_t *const srmcRegWPtr = (srmc_reg_w_t *) SRMC_BASE_ADDR;   /* SRMC Word Register */
static SCB_Type *const coreSCB = (SCB_Type *)SCB_BASE;                      /* Core SCB Register*/
/*PRQA S 0303,0306 --*/

static const uint32_t SRMC_IntStatusTable[] = 
{
    0x00000004U,     /*SRMC_INT_TYPE_LOC status mask*/
    0x00000020U,     /*SRMC_INT_TYPE_WDOG status mask*/
    0x00000040U,     /*SRMC_INT_TYPE_PIN status mask*/
    0x00000200U,     /*SRMC_INT_TYPE_LOCKUP status mask*/
    0x00000400U,     /*SRMC_INT_TYPE_SW status mask*/
    0x00008000U,     /*SRMC_INT_TYPE_SACKERR status mask*/
    0x00008664U,     /*SRMC_INT_TYPE_ALL*/
};

/*PRQA S 3218 ++*/
static const uint32_t SRMC_IntMaskTable[] =
{
    0x00000004U,     /*SRMC_INT_TYPE_LOC enable mask*/
    0x00000020U,     /*SRMC_INT_TYPE_WDOG enable mask*/
    0x00000040U,     /*SRMC_INT_TYPE_PIN enable mask*/
    0x00000200U,     /*SRMC_INT_TYPE_LOCKUP enable mask*/
    0x00000400U,     /*SRMC_INT_TYPE_SW enable mask*/
    0x00008000U,     /*SRMC_INT_TYPE_SACKERR enable mask*/
    0x000086E4U,     /*SRMC_INT_TYPE_ALL*/
};
/*PRQA S 3218 --*/

static uint32_t srmcIntMaskStatus = 0;

/*@} end of group SRMC_Private_Defines */

/** @defgroup SRMC_Private_Variables
 *  @{
 */
static isr_cb_t * srmcIsrCbFunc[SRMC_INT_TYPE_ALL]= 
{
    NULL,NULL,NULL,NULL,NULL,NULL
};
/*@} end of group SRMC_Private_Variables */

/** @defgroup SRMC_Global_Variables
 *  @{
 */

/*@} end of group SRMC_Global_Variables */

/** @defgroup SRMC_Private_FunctionDeclaration
 *  @{
 */
void SRMC_DriverIRQHandler(void);

/*@} end of group SRMC_Private_FunctionDeclaration */

/** @defgroup SRMC_Private_Functions
 *  @{
 */

/**
 * @brief     SRMC Interrupt Handler
 *
 * @param[in] none
 *
 * @return    none
 *
 */
void SRMC_DriverIRQHandler(void)
{
    uint32_t intStatus;

    /* get interrupt status */
    intStatus = srmcRegWPtr->SRMC_SRS;
    /* only check enabled interrupts */
    intStatus = intStatus & srmcIntMaskStatus;
    /* clear interrupt status */
    srmcRegWPtr->SRMC_SRS = intStatus;

    /* loc cause reset Interrupt */
    if((intStatus & SRMC_IntStatusTable[SRMC_INT_TYPE_LOC]) != 0U)
    {
        if(srmcIsrCbFunc[SRMC_INT_TYPE_LOC] != NULL)
        {
             /* call the callback function */
             srmcIsrCbFunc[SRMC_INT_TYPE_LOC]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            srmcRegPtr->SRMC_SRIE.LOC = 0U;
        }
    }

    /* wdog cause reset Interrupt */
    if((intStatus & SRMC_IntStatusTable[SRMC_INT_TYPE_WDOG]) != 0U)
    {
        if(srmcIsrCbFunc[SRMC_INT_TYPE_WDOG] != NULL)
        {
            /* call the callback function */
            srmcIsrCbFunc[SRMC_INT_TYPE_WDOG]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            srmcRegPtr->SRMC_SRIE.WDOG = 0U;
        }
    }

    /* pin cause reset Interrupt */
    if((intStatus & SRMC_IntStatusTable[SRMC_INT_TYPE_PIN]) != 0U)
    {
        if(srmcIsrCbFunc[SRMC_INT_TYPE_PIN] != NULL)
        {
            /* call the callback function */
            srmcIsrCbFunc[SRMC_INT_TYPE_PIN]();  
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            srmcRegPtr->SRMC_SRIE.PIN = 0U;
        }
    }
    
    /* lock up cause reset Interrupt */
    if((intStatus & SRMC_IntStatusTable[SRMC_INT_TYPE_LOCKUP]) != 0U)
    {
        if(srmcIsrCbFunc[SRMC_INT_TYPE_LOCKUP] != NULL)
        {
            /* call the callback function */
            srmcIsrCbFunc[SRMC_INT_TYPE_LOCKUP]();  
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            srmcRegPtr->SRMC_SRIE.LOCKUP = 0U;
        }
    }

    /* software reset Interrupt */
    if((intStatus & SRMC_IntStatusTable[SRMC_INT_TYPE_SW]) != 0U)
    {
        if(srmcIsrCbFunc[SRMC_INT_TYPE_SW] != NULL)
        {
            /* call the callback function */
            srmcIsrCbFunc[SRMC_INT_TYPE_SW](); 
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            srmcRegPtr->SRMC_SRIE.SW = 0U;
        }
    }

    /* sack error cause reset Interrupt */
    if((intStatus & SRMC_IntStatusTable[SRMC_INT_TYPE_SACKERR]) != 0U)
    {
        if(srmcIsrCbFunc[SRMC_INT_TYPE_SACKERR] != NULL)
        {
            /* call the callback function */
            srmcIsrCbFunc[SRMC_INT_TYPE_SACKERR]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
             srmcRegPtr->SRMC_SRIE.SACKERR = 0U;
        }
    }
}
/*@} end of group SRMC_Private_Functions */

/** @defgroup SRMC_Public_Functions
 *  @{
 */

/**
 * @brief       configure core lockup reset enable/disable
 *
 * @param[in]  cmd:          control cmd:   DISABLE; ENABLE.
 *
 * @return none
 *
 */
void SRMC_CoreLockupResetCtrl(ControlState_t cmd)
{
    srmcRegPtr->SRMC_CTRL.LOCKUP_RST_EN = (uint32_t)cmd;
}

/**
 * @brief       SRMC wakeup source polarity config
 *
 * @param[in]  source:          wakeup source select.
 * @param[in]  polarity:        active polarity.
 *                              - SRMC_WUPPL_LOW
 *                              - SRMC_WUPPL_HIGH
 *
 * @return none
 *
 */
void SRMC_WakeupSourceConfig(SRMC_WakeupSource_t source, SRMC_WakePolarity_t polarity)
{
    uint8_t leftshift = (uint8_t) source;
    
    if(SRMC_WUPPL_LOW == polarity)
    {
        srmcRegWPtr->SRMC_DSMWUPC = srmcRegWPtr->SRMC_DSMWUPC & (~(0x10000UL << leftshift));
    }
    else
    {
        srmcRegWPtr->SRMC_DSMWUPC = srmcRegWPtr->SRMC_DSMWUPC | (0x10000UL << leftshift);
    }
}

/**
 * @brief       SRMC wakeup source function enable/disable
 *
 * @param[in]  source:          wakeup source select.
 * @param[in]  cmd:             enable/disable.
 *
 * @return none
 *
 */
void SRMC_WakeupSourceCtrl(SRMC_WakeupSource_t source, ControlState_t cmd)
{
    uint8_t leftshift = (uint8_t) source;
    
    if(DISABLE == cmd)
    {
        srmcRegWPtr->SRMC_DSMWUPC = srmcRegWPtr->SRMC_DSMWUPC & (~(0x1UL << leftshift));
    }
    else
    {
        srmcRegWPtr->SRMC_DSMWUPC = srmcRegWPtr->SRMC_DSMWUPC | (0x1UL << leftshift);
    }
}

/**
 * @brief       SRMC get wakeup source status, indicating corresponding wakeup 
 *              source waked up system
 *
 * @param[in]  source:          wakeup source select.
 *
 * @return status
 *
 */
FlagStatus_t SRMC_GetWakeupSourceStatus(SRMC_WakeupSource_t source)
{
    uint8_t leftshift = (uint8_t) source;
    FlagStatus_t retStatus;
    
    if((srmcRegWPtr->SRMC_DSMWUPS & (0x1UL << leftshift)) == 0UL)
    {
        retStatus = RESET;
    }
    else
    {
        retStatus = SET;
    }
    
    return retStatus;
}

/**
 * @brief       configure reset pin filter bus clock width,
 *              actural reset pin bus clock filter width cycle = clkCycles + 1
 *
 * @param[in]  clkCycles:          cycle number.
 *
 * @return none
 *
 */
void SRMC_ResetPinFilterBusClockConfig(uint8_t clkCycles)
{
    srmcRegPtr->SRMC_CTRL.RSTFLTSEL = (uint32_t)clkCycles & 0x1FUL;
}

/**
 * @brief       configure how reset pin filter is enabled in stop mode
 *
 * @param[in]  filterType:    only two type used in stop mode, as below
 *                                  SRMC_RESET_PIN_DISABLE_FILTER
 *                                  SRMC_RESET_PIN_LPO_CLOCK_FILTER
 *
 * @return none
 *
 */
void SRMC_ResetPinFilterInStopMode(SRMC_ResetPinFilter_t filterType)
{
    srmcRegPtr->SRMC_CTRL.RSTFLTSS = ((uint32_t)filterType >> 1U) & 0x1U;
}

/**
 * @brief       configure how reset pin filter is enabled in run and wait mode
 *
 * @param[in]  filterType:    three type used in run and wait mode, as below
 *                                  SRMC_RESET_PIN_DISABLE_FILTER
 *                                  SRMC_RESET_PIN_BUS_CLOCK_FILTER
 *                                  SRMC_RESET_PIN_LPO_CLOCK_FILTER
 *
 * @return none
 *
 */
void SRMC_ResetPinFilterInRunAndWaitMode(SRMC_ResetPinFilter_t filterType)
{
    srmcRegPtr->SRMC_CTRL.RSTFLTSRW = (uint32_t)filterType;
}

/**
 * @brief       Get the status that if the pointed reset type is the system
 *              reset cause.
 *
 * @param[in]  resetCauseType:          reset cause type.
 *
 * @return     status
 *
 */
FlagStatus_t SRMC_GetSystemResetStatus(SRMC_ResetCause_t resetCauseType)
{
    FlagStatus_t status;
    
    status = ((srmcRegWPtr->SRMC_SRS & (uint32_t)resetCauseType) != 0UL)? SET : RESET;
    
    return status;
}

/**
 * @brief       Clear the status that if the pointed reset type.
 *
 * @param[in]  resetCauseType:          reset cause type.
 *
 * @return     status
 *
 */
void SRMC_ClearSystemRestStatus(SRMC_ResetCause_t resetCauseType)
{
    srmcRegWPtr->SRMC_SSRS = (uint32_t )resetCauseType;
}

/**
 * @brief       Get system reset all causes
 *
 * @param[in]  none
 *
 * @return     reset cause type(uint32 value): one bit, one cause;
 *             seeing SRMC_ResetCause_t type; 
 *
 */
uint32_t SRMC_GetSystemResetCause(void)
{   
    uint32_t resetCause;
    
    resetCause = srmcRegWPtr->SRMC_SRS & (uint32_t)SRMC_RESET_TYPE_ALL;

    return resetCause;
}

/**
 * @brief       Unmask/Mask pointed interrupt
 *
 * @param[in]  intType:          srmc interrupt source.
 * @param[in]  intMask:          UNMASK or MASK.
 *
 * @return     none
 *
 */
void SRMC_IntMask(SRMC_Int_t intType, IntMask_t intMask)
{
    
    if(UNMASK == intMask)
    {
        srmcRegWPtr->SRMC_SRIE = srmcRegWPtr->SRMC_SRIE | SRMC_IntMaskTable[intType] \
                                 | (1UL << SRMC_GIE_BIT_POSITION);
        srmcIntMaskStatus = srmcIntMaskStatus | SRMC_IntStatusTable[intType];
    }
    else
    {
        srmcRegWPtr->SRMC_SRIE = srmcRegWPtr->SRMC_SRIE & (~SRMC_IntMaskTable[intType]);
        srmcIntMaskStatus = srmcIntMaskStatus & (~SRMC_IntStatusTable[intType]);
    }
}


/**
 * @brief       configure max reset delay time
 *
 * @param[in]  delayType:          delay cycle type.
 *
 * @return     none
 *
 */
void SRMC_MaxResetDelayTimeConfig(SRMC_Delay_t delayType)
{
    srmcRegPtr->SRMC_SRIE.DELAY = (uint32_t)delayType;
}

/**
 * @brief       configure standby mode entry allowed or not
 *
 * @param[in]  cmd:          DISABLE or ENABLE.
 *
 * @return     none
 *
 */
void SRMC_AllowStandbyMode(ControlState_t cmd)
{
    srmcRegPtr->SRMC_PMPORT.APD = (uint32_t)cmd;
}

/**
 * @brief       Set system enter wait mode
 *
 * @return     none
 *
 */
void SRMC_EnterWaitMode(void)
{
    coreSCB->SCR &= (~SCB_SCR_SLEEPDEEP_Msk);
    
    __WFI();
}

/**
 * @brief      Set system enter stop mode(deep sleep mode)
 *
 * @param[in]  ackTimeout: stop mode acknowledge timeout value in clock cycles
 *
 * @return     none
 *
 */
void SRMC_EnterStopMode(uint8_t ackTimeout)
{
    srmcRegPtr->SRMC_PMCTRL.DSMACKTMO = ackTimeout;
    
    /*10'b : STOP mode*/
    srmcRegPtr->SRMC_PMCTRL.DSMC = 2U;
    
    coreSCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    
    __WFI();
}

/**
 * @brief       Set system enter standby mode
 *
 * @return     none
 *
 */
void SRMC_EnterStandbyMode(void)
{
    /*11'b : Standby mode*/
    srmcRegPtr->SRMC_PMCTRL.DSMC = 3U;
    
    coreSCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    
    __WFI();
}

/**
 * @brief       Get current power mode
 *
 * @param[in]  none
 *
 * @return     power mode type
 *
 */
SRMC_PowerMode_t SRMC_GetCurrentPowerMode(void)
{
    SRMC_PowerMode_t retPowerMode;
    uint8_t pm = (uint8_t)srmcRegPtr->SRMC_PMSTAT.PMSTAT;
    
    switch(pm)
    {
        case 1U:
            retPowerMode = SRMC_POWERMODE_RUN;
            break;
     
        case 2U:
            retPowerMode = SRMC_POWERMODE_WAIT;
            break;
        
        case 4U:
            retPowerMode = SRMC_POWERMODE_STOP;
            break;

        case 8U:
            retPowerMode = SRMC_POWERMODE_STANDBY;
            break;
            
        default:
            retPowerMode = SRMC_POWERMODE_RUN;
            break;
    }
    
    return retPowerMode;
}

/**
 * @brief       Get previous stop mode(deep sleep mode) entry status
 *
 * @param[in]  none
 *
 * @return     stop entry status: 
 *                               - SRMC_STOP_SUCCESS; 
 *                               - SRMC_STOP_ABORT.
 *
 */
SRMC_StopModeStatus_t SRMC_GetStopAbortedStatus(void)
{
    SRMC_StopModeStatus_t stopAborted = 
                     (SRMC_StopModeStatus_t)srmcRegPtr->SRMC_PMSTAT.DSMABORT;     /*PRQA S 4342*/
    
    return stopAborted;
}

/**
 * @brief       install callback func
 *
 * @param[in]  intType: interrupt type id
 * @param[in]  cbFun  : callback function pointer
 *
 * @return     stop entry status: SRMC_STOP_SUCCESS; SRMC_STOP_ABORT.
 *
 */
void SRMC_InstallCallBackFunc(SRMC_Int_t intType,isr_cb_t * cbFun)
{
    srmcIsrCbFunc[intType] = cbFun;
}

/*@} end of group SRMC_Public_Functions */

/*@} end of group SRMC_definitions */

/*@} end of group Z20K11X_Peripheral_Driver */
