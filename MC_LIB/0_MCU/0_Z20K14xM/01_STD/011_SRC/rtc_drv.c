/**************************************************************************************************/
/**
 * @file     rtc_drv.c
 * @brief    RTC module driver file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#include "rtc_drv.h"
#include "clock_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @defgroup RTC RTC
 *  @brief RTC driver modules
 *  @{
 */

/** @defgroup RTC_Private_Type
 *  @{
 */

/** @} end of group RTC_Private_Type*/

/** @defgroup RTC_Private_Defines
 *  @{
 */

/** @} end of group RTC_Private_Defines */

/** @defgroup RTC_Private_Variables
 *  @{
 */

/**
 *  @brief RTC IRQHandler callback function pointer array
 */
static isr_cb_t * rtcIsrCb[RTC_INT_ALL]= 
{
    NULL, NULL, NULL,NULL
};
/*PRQA S 0303 ++*/
static rtc_reg_w_t  *const rtcRegWPtr   = (rtc_reg_w_t *) RTC_BASE_ADDR;
static rtc_reg_t    *const rtcRegPtr    = (rtc_reg_t *) RTC_BASE_ADDR;
/*PRQA S 0303 --*/

static const uint32_t rtcInterruptMaskTable[] =
{
    0x00000008U,    /*!< RTC overflow interrupt */
    0x00000010U,    /*!< RTC alarm interrupt  */
    0x00000020U,    /*!< RTC second interrupt */
    0x00000040U,    /*!< RTC period interrupt */
    0x00000038U     /*!< RTC_INT_ALL */
};

static const uint32_t rtcIntStatusTable[] =
{
    0x00000080U,    /*!< RTC overflow interrupt */
    0x00000100U,    /*!< RTC alarm interrupt  */
    0x00000800U,    /*!< RTC second interrupt */
    0x00002000U,    /*!< RTC period interrupt */
    0x00002980U     /*!< RTC_INT_ALL */
};

static uint32_t rtcIntMaskStatus = 0U;

static const uint32_t rtcCsrRegMask = 0x0000147FU;

/** @} end of group RTC_Private_Variables */

/** @defgroup RTC_Global_Variables
 *  @{
 */

/** @} end of group RTC_Global_Variables */


/** @defgroup RTC_Private_FunctionDeclaration
 *  @{
 */
static void RTC_IntHandler(void);

/**
 * @brief      RTC alarm match interrupt IRQ handler function
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
void RTC_Alarm_DriverIRQHandler(void);

/**
 * @brief      RTC second interrupt IRQ handler  function
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
void RTC_Second_DriverIRQHandler(void);

/** @} end of group RTC_Private_FunctionDeclaration */

/** @defgroup RTC_Private_Functions
 *  @{
 */

/**
 * @brief  RTC Alarm_IRQHandler function
 *
 * @param  none
 *
 * @return none
 *
 */
void RTC_Alarm_DriverIRQHandler(void)
{
   RTC_IntHandler();
}

/**
 * @brief  RTC Second_IRQHandler function
 *
 * @param  none
 *
 * @return none
 *
 */
void RTC_Second_DriverIRQHandler(void)
{
   RTC_IntHandler();
}

/**
 * @brief      RTC interrupt handle
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
static void RTC_IntHandler(void)
{
    uint32_t intStatus;
    uint32_t tempVal = 0U;
    
    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    /* get interrupt status */
    intStatus = rtcRegWPtr->RTC_CSR; 

    /* make sure interrupt is enable */
    intStatus = intStatus & rtcIntMaskStatus;
    
    if((intStatus & rtcIntStatusTable[RTC_INT_ALARM]) != 0U)
    {
        /* clear interrupt status */
        rtcRegWPtr->RTC_MATCH_CNTR = 0xFFFFFFFFU;
        
        if(rtcIsrCb[RTC_INT_ALARM] != NULL)
        {
            rtcIsrCb[RTC_INT_ALARM]();
        }
        else
        {
            rtcRegPtr->RTC_IER.ALARM_IE = 0U;
        }
    }

    if((intStatus & rtcIntStatusTable[RTC_INT_OVERFLOW]) != 0U)
    {
        if(rtcIsrCb[RTC_INT_OVERFLOW] != NULL)
        {
            rtcIsrCb[RTC_INT_OVERFLOW]();
        }
        else
        {
            rtcRegPtr->RTC_IER.OVFLOW_IE = 0U;
        }
    }

    if((intStatus & rtcIntStatusTable[RTC_INT_SECOND]) != 0U)
    {
        tempVal = (rtcRegWPtr->RTC_CSR & rtcCsrRegMask) | (0x1UL << 11U);
        rtcRegWPtr->RTC_CSR = tempVal;
        if(rtcIsrCb[RTC_INT_SECOND] != NULL)
        {
            rtcIsrCb[RTC_INT_SECOND]();
        }
        else
        {
            rtcRegPtr->RTC_IER.SECONDS_IE = 0U;
        }
        
    }
    
    if((intStatus & rtcIntStatusTable[RTC_INT_PERIODIC]) != 0U)
    {
        tempVal = (rtcRegWPtr->RTC_CSR & rtcCsrRegMask) | (0x1UL << 13U);
        rtcRegWPtr->RTC_CSR = tempVal;
        if(rtcIsrCb[RTC_INT_PERIODIC] != NULL)
        {
            rtcIsrCb[RTC_INT_PERIODIC]();
        }
        else
        {
            rtcRegPtr->RTC_IER.PERIODIC_IE = 0U;
        }
        
    }

    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
    COMMON_DSB();
}

/** @} end of group RTC_Private_Functions */

/** @defgroup RTC_Public_Functions
 *  @{
 */

 /**
 * @brief      RTC enable function
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
void RTC_Enable(void)
{
    uint32_t tempVal = 0U;

    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    tempVal = (rtcRegWPtr->RTC_CSR & rtcCsrRegMask) | (0x1U << 6U);
    rtcRegWPtr->RTC_CSR = tempVal;

    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

 /**
 * @brief      RTC disable function
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
void RTC_Disable(void)
{
    uint32_t tempVal = 0U;

    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    tempVal = (rtcRegWPtr->RTC_CSR & rtcCsrRegMask) & (~(0x1U << 6U));
    rtcRegWPtr->RTC_CSR = tempVal;

    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

/**
 * @brief      Software reset all rtc registers except sw_rst bit
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
void RTC_SWRest(void)
{
    volatile uint32_t localCount = 0U;
    uint32_t tempVal = 0U;

    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    tempVal = (rtcRegWPtr->RTC_CSR & rtcCsrRegMask) | (0x1U << 5U);
    rtcRegWPtr->RTC_CSR = tempVal;
    while(localCount < RTC_WAIT_CNT_SWRST)
    {
        localCount ++;
    }
    tempVal = (rtcRegWPtr->RTC_CSR & rtcCsrRegMask) & (~(0x1U << 5U));
    rtcRegWPtr->RTC_CSR = tempVal;
    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

/**
 * @brief      config whether write access to RTC in non-supervisor
 *
 * @param[in]  cmd: ENABLE/DISABLE
 *
 * @return     none
 *
 */
void RTC_SupModeConfig(ControlState_t cmd)
{
    uint32_t tempVal = 0U;

    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    tempVal = (rtcRegWPtr->RTC_CSR & rtcCsrRegMask) & (~(0x1U << 4U)) | ((uint32_t)cmd << 4U);
    rtcRegWPtr->RTC_CSR = tempVal;
    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

/**
 * @brief       config second interrupt mux function
 *              need to configure this before enable second interrupt
 *
 * @param[in]   muxSel: select frequency to generate second frequency
 *
 * @return      none
 *
 */
void RTC_FreqMuxConfig(RTC_SecondIntMuxSel_t muxSel)
{
    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    rtcRegPtr->RTC_IER.SECONDS_IE = 0U;
    rtcRegPtr->RTC_IER.SECOND_INT_MUX_SEL = (uint32_t)muxSel;

    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

/**
 * @brief       Enable  RTC output clock function, then need to config clock source
 *
 * @param[in]   config:config clock output
 *
 * @return      none
 *
 */
void RTC_OutputConfig(RTC_OutputConfig_t * config)
{
    uint32_t tempVal = 0U;

    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    tempVal = (rtcRegWPtr->RTC_CSR & rtcCsrRegMask) & (~(0x1U << 2U)) | 
                ((uint32_t)config->clkOutput << 2U);
    rtcRegWPtr->RTC_CSR = tempVal;
    rtcRegPtr->RTC_IER.SECOND_INT_MUX_SEL = (uint32_t)config -> freqSel;
    
    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

/**
 * @brief       Enable RTC output clock function
 *
 * @param[in]   none
 *
 * @return      none
 *
 */
void RTC_OutputEnable(void)
{
    uint32_t tempVal = 0U;

    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    tempVal = (rtcRegWPtr->RTC_CSR & rtcCsrRegMask) | (0x1U << 3U);
    rtcRegWPtr->RTC_CSR = tempVal;

    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

/**
 * @brief       Disable RTC output clock function
 *
 * @param[in]   none
 *
 * @return      none
 *
 */
void RTC_OutputDisable(void)
{
    uint32_t tempVal = 0U;

    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    tempVal = (rtcRegWPtr->RTC_CSR & rtcCsrRegMask) & (~(0x1U << 3U));
    rtcRegWPtr->RTC_CSR = tempVal;

    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

/**
 * @brief       Enable RTC periodic counter function, which is count with 32kHz 
 *
 * @param[in]   none
 *
 * @return      none
 *
 */
void RTC_PeriodicCounterEnable(void)
{
    uint32_t tempVal = 0U;

    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    tempVal = (rtcRegWPtr->RTC_CSR & rtcCsrRegMask) | (0x1UL << 12U);
    rtcRegWPtr->RTC_CSR = tempVal;

    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

/**
 * @brief       Disable RTC periodic counter function
 *
 * @param[in]   none
 *
 * @return      none
 *
 */
void RTC_PeriodicCounterDisable(void)
{
    uint32_t tempVal = 0U;

    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    tempVal = (rtcRegWPtr->RTC_CSR & rtcCsrRegMask) & (~(0x1UL << 12U));
    rtcRegWPtr->RTC_CSR = tempVal;

    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

/**
 * @brief       Select clock source function. When clock source selected is from crystal, this API
 *              return SUCC means that the CRYSTAL_EN bit is set, but not means that OSC_RDY status
 *              asserts. User should call RTC_GetOSC32KReady API to check if OSC_RDY status asserts.
 *
 * @param[in]   clockSource:RTC clock source
 *
 * @return       
 *              -SUCC:clock config is success
 *              -ERR:clock config is fail
 *
 */
ResultStatus_t RTC_ClkConfig(RTC_Clk_t clockSource)
{
    ResultStatus_t ret = ERR;
    uint32_t tempVal = 0U;

    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    switch(clockSource)
    {
        case RTC_CLK_OSC32K_INT:
            /* CNT_CLK_SEL = 0, CRYSTAL_EN = 1 */
            tempVal = (rtcRegWPtr->RTC_CSR & rtcCsrRegMask) & (~0x2U) | (0x1U);
            rtcRegWPtr->RTC_CSR = tempVal;
            if(1U == rtcRegPtr->RTC_CSR.CRYSTAL_EN)
            {                
                ret = SUCC;
            }
            else
            {
                ret = ERR;
            }
            break;

        case RTC_CLK_OSC32K_EXT:
            /* CNT_CLK_SEL = 0, EXTAL_32K_EN = 1 */
            tempVal = (rtcRegWPtr->RTC_CSR & rtcCsrRegMask) & (~0x2UL) | (0x1UL << 10U);
            rtcRegWPtr->RTC_CSR = tempVal;
            if(SUCC == RTC_WaitOSC32KReady())
            {                
                ret = SUCC;
            }
            else
            {
                ret = ERR;
            }
            break;

        case RTC_CLK_LPO32K:
            /* CNT_CLK_SEL = 1 */
            tempVal = (rtcRegWPtr->RTC_CSR & rtcCsrRegMask) | (0x2U);
            rtcRegWPtr->RTC_CSR = tempVal;
            if(SET == CLK_GetClkStatus(CLK_SRC_LPO32K))
            {                 
                ret = SUCC;
            }
            else
            {
                ret = ERR;
            }

            break;

        default:
        /* Intentionally Empty */
            break;
    }
  
    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
    return ret;
}

/**
 * @brief        Set alarm match counter, which also can clear alarm interrupt
 *               it can be written when rtc is enable
 *
 * @param[in]    matchValue:set the match value
 *
 * @return       none
 *
 *****************************************************************************/
void RTC_SetAlarmMatchCounter(uint32_t matchValue)
{
    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    rtcRegPtr->RTC_MATCH_CNTR.MATCH_CNT = matchValue;

    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

/**
 * @brief       Get alarm match counter register
 *
 * @param[in]   none
 *
 * @return      alarm match counter value
 *
 *****************************************************************************/
uint32_t RTC_GetAlarmMatchCounter(void)
{
    return (rtcRegPtr->RTC_MATCH_CNTR.MATCH_CNT);
}

/**
 * @brief       Set periodic counter start value when rtc is disable
 *
 * @param[in]   counterValue:set the counter start  value
 *
 * @return      none
 *
 *****************************************************************************/
void RTC_SetPeriodicCounterValue(uint32_t counterValue)
{
    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    rtcRegPtr->RTC_PERIODIC_TMR_CNT.PERIODIC_TMR_CNT = counterValue;

    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

/**
 * @brief       Get periodic counter register
 *
 * @param[in]   none
 *
 * @return      periodic counter value
 *
 *****************************************************************************/
uint32_t RTC_GetPeriodicCounter(void)
{
    return (rtcRegWPtr->RTC_PERIODIC_TMR_CNT);
}

/**
 * @brief       Set periodic timer match value
 *
 * @param[in]   matchValue:set the counter match value
 *
 * @return      none
 *
 *****************************************************************************/
void RTC_SetPeriodicMatchValue(uint32_t matchValue)
{
    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    rtcRegWPtr->RTC_PERIODIC_TMR_MATCH_CNT = matchValue;

    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

/**
 * @brief       Get alarm match counter register
 *
 * @param[in]   none
 *
 * @return      periodic match counter value
 *
 *****************************************************************************/
uint32_t RTC_GetPeriodicMatchCounter(void)
{
    return (rtcRegWPtr->RTC_PERIODIC_TMR_MATCH_CNT);
}

/**
 * @brief        Mask/Unmask the RTC interrupt function
 *
 * @param[in]    intType: select interrupt
 * @param[in]    intMask: Enable/Disable  interrupt
 *
 * @return       none
 *
 *****************************************************************************/
void RTC_IntMask(RTC_Int_t intType, IntMask_t intMask)
{
    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    if(intMask == UNMASK)
    {
        rtcRegWPtr->RTC_IER |= rtcInterruptMaskTable[intType];
        rtcIntMaskStatus |=  rtcIntStatusTable[intType];
    }
    else
    {
        rtcRegWPtr->RTC_IER &= (~(rtcInterruptMaskTable[intType]));
        rtcIntMaskStatus &=  (~rtcIntStatusTable[intType]);
    }

    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

/**
 * @brief        Clear RTC interrupt status
 *               Note:Clear RTC overflow flag via writing 0 to one second counter, it 
 *               can be written only when rtc counter is disable
 *               reset match counter to clear alarm int status 
 *
 * @param[in]    intType: interrupt type
 *
 * @return       none
 *
 *****************************************************************************/
void RTC_ClearIntStatus(RTC_Int_t intType)
{
    uint32_t tempVal = 0U;

    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }
    
    switch (intType)
    {
        case RTC_INT_OVERFLOW:
            rtcRegPtr->RTC_ONE_SECOND_CNTR.ONE_SECOND_CNT = 0U;
            break;
        
        case RTC_INT_ALARM:
            rtcRegPtr->RTC_MATCH_CNTR.MATCH_CNT = 0xFFFFFFFFU;
            break;
        
        case RTC_INT_SECOND:
            /* SECONDS_INT_FLAG = 1 */
            tempVal = (rtcRegWPtr->RTC_CSR & rtcCsrRegMask) | (0x1UL << 11U);
            rtcRegWPtr->RTC_CSR = tempVal;
            break;
            
        case RTC_INT_PERIODIC:
            /* PERIODIC_MATCH_FLG = 1 */
            tempVal = (rtcRegWPtr->RTC_CSR & rtcCsrRegMask) | (0x1UL << 13U);
            rtcRegWPtr->RTC_CSR = tempVal;
            break;
            
        case RTC_INT_ALL:
            rtcRegPtr->RTC_ONE_SECOND_CNTR.ONE_SECOND_CNT = 0U;
            rtcRegPtr->RTC_MATCH_CNTR.MATCH_CNT = 0xFFFFFFFFU;
            /* SECONDS_INT_FLAG = 1, PERIODIC_MATCH_FLG = 1 */
            tempVal = (rtcRegWPtr->RTC_CSR & rtcCsrRegMask) | (0x1UL << 11U) | (0x1UL << 13U);
            rtcRegWPtr->RTC_CSR = tempVal;
            break;
            
        default:
        /* Intentionally Empty */
            break;
    }

    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

/**
 * @brief        Get RTC interrupt status
 *
 * @param[in]    intType: 
 *                      - RTC_INT_OVERFLOW
 *                      - RTC_INT_ALARM
 *                      - RTC_INT_SECOND
 *                      - RTC_INT_PERIODIC
 *
 * @return       none
 *
 *****************************************************************************/
IntStatus_t RTC_GetIntStatus(RTC_Int_t intType)
{
     IntStatus_t bitStatus = RESET;
         
    if (intType < RTC_INT_ALL)
    {
        bitStatus = (((rtcRegWPtr->RTC_CSR & rtcIntStatusTable[intType]) !=0U )? SET: RESET);
    }
    else
    {
        /* nothing */
    }
    return bitStatus;

}

/**
 * @brief       Set alarm counter then alarm counter will count from this value
 *              Note: this value can be written when rtc is disable only and
 *              at the same time, written this register can clear overflow flag
 * 
 * @param[in]   countVal: set start value
 *
 * @return      none
 *
 *****************************************************************************/
void RTC_SetAlarmCounter(uint32_t countVal)
{
    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }
    
    rtcRegPtr->RTC_ALARM_CNTR.ALARM_CNT = countVal;
    
    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

/**
 * @brief       Read the current alarm counter function
 *
 * @param[in]   none
 *
 * @return      current alarm counter
 *
 *****************************************************************************/
uint32_t RTC_GetAlarmCounter(void)
{
    return (rtcRegPtr->RTC_ALARM_CNTR.ALARM_CNT);
}

/**
 * @brief       Get the current compensation delay value  function
 *
 * @param[in]   none
 *
 * @return      current compensation delay value
 *
 *****************************************************************************/
uint8_t RTC_GetCurrentCompDelayCVal(void)
{
    return (uint8_t)(rtcRegPtr->RTC_COMPENSATIONR.CDLY);
}

/**
 * @brief       Get current compensation counter value  function
 *
 * @param[in]   none
 *
 * @return      current compensation value
 *
 *****************************************************************************/
uint8_t RTC_GetCurrentCompVal(void)
{
    return (uint8_t)(rtcRegPtr->RTC_COMPENSATIONR.CCOMP_CNT);
}

/**
 * @brief       Set compensation delay value function
 *
 * @param[in]   delayVal: delay value
 *
 * @return      none
 *
 *****************************************************************************/
void RTC_SetCompDelayVal(uint8_t delayVal)
{
    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    rtcRegPtr->RTC_COMPENSATIONR.DLY = delayVal;

    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

/**
 * @brief       Set frequency compensation direction function
 *
 * @param[in]   freqComp : select frequency compensation direction
 *
 * @return      none
 *
 *****************************************************************************/
void RTC_SetCompDirection(RTC_CompDirection_t freqComp)
{
    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    rtcRegPtr->RTC_COMPENSATIONR.COMP_DIRECTION = (uint32_t)freqComp;

    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

/**
 * @brief       Set compensation counter value function
 *
 * @param[in]   Val: counter value
 *
 * @return      none
 *
 *****************************************************************************/
void RTC_SetCompVal(uint8_t Val)
{
    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    rtcRegPtr->RTC_COMPENSATIONR.COMP_CNT = Val;

    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

/**
 * @brief       Get the current one second counter function
 *
 * @param[in]   none
 *
 * @return      current one second counter
 *
 *****************************************************************************/
uint16_t RTC_GetSecondCounter(void)
{
    return (uint16_t)(rtcRegPtr->RTC_ONE_SECOND_CNTR.ONE_SECOND_CNT);
}

/**
 * @brief       Set the one second counter value effective when RTC is disable, write
 *               to one second counter also can clear OVF flag
 *
 * @param[in]   val: counter start from this value
 *
 * @return      none
 *
 *****************************************************************************/
void RTC_SetSecondCounter(uint16_t val)
{
    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    rtcRegPtr->RTC_ONE_SECOND_CNTR.ONE_SECOND_CNT = val;

    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

/**
 * @brief       Config the compensation  function
 *
 * @param[in]   config: compensation config
 *
 * @return      none
 *
 *****************************************************************************/
void RTC_CompConfig(RTC_CompConfig_t * config)
{
    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    rtcRegPtr->RTC_COMPENSATIONR.DLY = config->delayVal;
    rtcRegPtr->RTC_COMPENSATIONR.COMP_DIRECTION = (uint32_t)(config->dir);
    rtcRegPtr->RTC_COMPENSATIONR.COMP_CNT = config->compVal;

    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

/**
 * @brief       Disable the compensation  function
 *
 * @param[in]   none
 *
 * @return      none
 *
 *****************************************************************************/
void RTC_CompDisable(void)
{
    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    rtcRegWPtr->RTC_COMPENSATIONR = 0x00000000U;

    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

/**
 * @brief      Wait the clock source status until it is ready
 *
 * @param[in]  none
 *
 * @return     SUCC -- the clock is ready
 *             ERR -- time out
 *
 */
ResultStatus_t RTC_WaitOSC32KReady(void)
{
    ResultStatus_t ret = ERR;
    volatile uint32_t localCnt = 0U;

    while(localCnt < RTC_WAIT_CNT)
    {
        if(rtcRegPtr->RTC_CSR.OSC_RDY != 0U)
        {
            ret = SUCC;
            break;
        }
        localCnt++;
    }
    return ret;
}

/**
 * @brief      Get the clock source status ready
 *             Please note that the OSC_RDY flag assert will take about 1.4s when select 
 *             RTC_CLK_OSC32K_INT source.
 *
 * @param[in]  none
 *
 * @return     SUCC -- the clock is ready
 *             ERR -- time out
 *
 */
ResultStatus_t RTC_GetOSC32KReady(void)
{
    ResultStatus_t ret = ERR;

    if(1U == rtcRegPtr->RTC_CSR.OSC_RDY)
    {
        ret = SUCC;
    }
    else
    {
        ret = ERR;
    }

    return ret;
}

/**
 * @brief      install call back function
 *
 * @param[in]  intId: select the interrupt
 * @param[in]  cbFun: pointer to callback function
 *
 * @return none
 *
 */
void RTC_InstallCallBackFunc(RTC_Int_t intId,isr_cb_t * cbFun)
{
    if(RTC_INT_ALL <= intId)
    {
        /* Do nothing */
    }
    else
    {
        rtcIsrCb[intId] = cbFun;
    }
}

/** @} end of group RTC_Public_Functions */

/** @} end of group RTC_definitions */

/** @} end of group Z20K14XM_Peripheral_Driver */
