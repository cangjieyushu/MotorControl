/**************************************************************************************************/
/**
 * @file     srmc_drv.c
 * @brief    SRMC module driver file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#include "srmc_drv.h"

/** @addtogroup  Z20K14X_Peripheral_Driver
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

#define SRMC_GIE_BIT_MASK           (0x80UL)  /* Global Interrupt Enable Bit Position in SRIE*/
#define SRMC_ALL_INT_MASK           (0x0000B664UL) /* All Interrupt Mask for SRIE*/

/*@} end of group SRMC_Private_Defines */

/** @defgroup SRMC_Private_Variables
 *  @{
 */
/*PRQA S 0303,0306 ++*/
static srmc_reg_t* const srmcRegPtr = (srmc_reg_t*)SRMC_BASE_ADDR;         /* SRMC Register */
static srmc_reg_w_t* const srmcRegWPtr = (srmc_reg_w_t*)SRMC_BASE_ADDR;    /* SRMC Word Register */
static Z20_SCBType* const coreSCB = (Z20_SCBType*)Z20_SCB_BASE;             /* Core SCB Register*/
/*PRQA S 0303,0306 --*/

static const uint32_t SRMC_IntMaskTable[] = 
{
    0x00000004U,     /*SRMC_INT_TYPE_LOC enable mask*/  
    0x00000020U,     /*SRMC_INT_TYPE_WDOG enable mask*/
    0x00000040U,     /*SRMC_INT_TYPE_PIN enable mask*/
    0x00000200U,     /*SRMC_INT_TYPE_LOCKUP enable mask*/
    0x00000400U,     /*SRMC_INT_TYPE_SW enable mask*/
    0x00001000U,     /*SRMC_INT_TYPE_SERU_COLD enable mask*/
    0x00002000U,     /*SRMC_INT_TYPE_SERU_SYS enable mask*/
    0x00008000U,     /*SRMC_INT_TYPE_SACKERR enable mask*/
    0x0000B664U,     /*SRMC_INT_TYPE_ALL*/
};

static isr_cb_t * srmcIsrCbFunc = NULL;

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
 * @brief  SRMC interrupt handler.
 *
 * @param  None.
 *
 * @return None.
 *
 */
void SRMC_DriverIRQHandler(void)
{
    if (srmcIsrCbFunc != NULL)
    {
        srmcIsrCbFunc();
    }
    COMMON_DSB();
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
    
    if(source <= SRMC_WUPSRC_PTA25)
    {
        if(SRMC_WUPPL_LOW == polarity)
        {
            srmcRegWPtr->SRMC_DSMWUPC1 = srmcRegWPtr->SRMC_DSMWUPC1 & (~(0x10000UL << leftshift));
        }
        else
        {
            srmcRegWPtr->SRMC_DSMWUPC1 = srmcRegWPtr->SRMC_DSMWUPC1 | (0x10000UL << leftshift);
        }
    }
    else
    {
        /*Do nothing*/
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
        if( SRMC_WUPSRC_RTC == source)
        {
            srmcRegWPtr->SRMC_DSMWUPC2 = srmcRegWPtr->SRMC_DSMWUPC2 & (~(0x1UL));
        }
        else
        {
            srmcRegWPtr->SRMC_DSMWUPC1 = srmcRegWPtr->SRMC_DSMWUPC1 & (~(0x1UL << leftshift));
        }
    }
    else
    {
        if(SRMC_WUPSRC_RTC == source)
        {
            srmcRegWPtr->SRMC_DSMWUPC2 = srmcRegWPtr->SRMC_DSMWUPC2 | (0x1UL);
        }
        else
        {
            srmcRegWPtr->SRMC_DSMWUPC1 = srmcRegWPtr->SRMC_DSMWUPC1 | (0x1UL << leftshift);
        }
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
    
    if(0UL == (srmcRegWPtr->SRMC_DSMWUPS & (0x1UL << leftshift)))
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
 * @brief       SRMC clear wakeup source status, indicating corresponding wakeup 
 *              source waked up system
 *
 * @param[in]  source:          wakeup source select.
 *
 * @return none
 *
 */
void SRMC_ClearWakeupSourceStatus(SRMC_WakeupSource_t source)
{
    uint8_t leftshift = (uint8_t) source;

    srmcRegWPtr->SRMC_DSMWUPS = ((0x1UL) << leftshift);
}

/**
 * @brief       configure reset pin filter bus clock width,
 *              actual reset pin bus clock filter width cycle = clkCycles + 1
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
    srmcRegPtr->SRMC_CTRL.RSTFLTSS = ((uint32_t)filterType >> 1U) & 0x01U;
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
    
    status = ((srmcRegWPtr->SRMC_SSRS & (uint32_t)resetCauseType) != 0UL)? SET : RESET;
    
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
void SRMC_ClearSystemResetStatus(SRMC_ResetCause_t resetCauseType)
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
        srmcRegWPtr->SRMC_SRIE |= SRMC_IntMaskTable[intType] | SRMC_GIE_BIT_MASK;
    }
    else
    {
        srmcRegWPtr->SRMC_SRIE &= ~SRMC_IntMaskTable[intType];

        if (0U == (srmcRegWPtr->SRMC_SRIE & SRMC_ALL_INT_MASK))
        {
            /* If all interrupts are disabled, clear global enable bit. */
            srmcRegWPtr->SRMC_SRIE &= ~SRMC_GIE_BIT_MASK;
        }

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
 * @param[in]  none
 * 
 * @return     none
 *
 */
void SRMC_EnterWaitMode(void)
{
    coreSCB->SCR &= (~SCB_SCR_SLEEPDEEP_MASK);
    
    COMMON_WFI();
}

/**
 * @brief       Set system enter stop mode(deep sleep mode)
 *
 * @param[in]  ackTimeout: low power mode acknowledge time out. 
 * @note       setting ackTimeout to 0 means the stop sequence will wait forever
 *
 * @return     none
 *
 */
void SRMC_EnterStopMode(uint8_t ackTimeout)
{
    srmcRegPtr->SRMC_PMCTRL.DSMACKTMO = ackTimeout;
    
    /*10'b : STOP mode*/
    srmcRegPtr->SRMC_PMCTRL.DSMC = 2U;
    
    coreSCB->SCR |= SCB_SCR_SLEEPDEEP_MASK;
    
    COMMON_WFI();
}

/**
 * @brief       Set system enter standby mode
 *
 * @param[in]  ackTimeout: low power mode acknowledge time out. 
 * @note       setting ackTimeout to 0 means the stop sequence will wait forever
 * 
 * @return     none
 *
 */
void SRMC_EnterStandbyMode(uint8_t ackTimeout)
{
    srmcRegPtr->SRMC_PMCTRL.DSMACKTMO = ackTimeout;

    /*11'b : standby mode*/
    srmcRegPtr->SRMC_PMCTRL.DSMC = 3U;
    
    coreSCB->SCR |= SCB_SCR_SLEEPDEEP_MASK;
    
    COMMON_WFI();
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
                     (SRMC_StopModeStatus_t)srmcRegPtr->SRMC_PMSTAT.DSMABORT;
    
    return stopAborted;
}

/**
 * @brief       install callback function
 *
 * @param[in]  cbFun  : callback function pointer
 *
 * @return     stop entry status: SRMC_STOP_SUCCESS; SRMC_STOP_ABORT.
 *
 */
void SRMC_InstallCallBackFunc(isr_cb_t * cbFun)
{
    srmcIsrCbFunc = cbFun;
}

/*@} end of group SRMC_Public_Functions */

/*@} end of group SRMC_definitions */

/*@} end of group Z20K14X_Peripheral_Driver */
