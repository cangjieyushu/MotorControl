/**************************************************************************************************/
/**
 * @file      : Z20K11xM_rtc.c
 * @brief     : RTC module driver file.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (c) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#include "Z20K11xM_rtc.h"
#include "Z20K11xM_clock.h"

/** @addtogroup  Z20K11X_Peripheral_Driver
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
 *  @brief RTC ISR callback function pointer array
 */
static isr_cb_t * rtcIsrCb[RTC_INT_ALL]= {NULL, NULL, NULL};

/*PRQA S 0303 ++*/
static rtc_reg_w_t  *const rtcRegWPtr   = (rtc_reg_w_t *) RTC_BASE_ADDR; 
static rtc_reg_t    *const rtcRegPtr    = (rtc_reg_t *) RTC_BASE_ADDR;
/*PRQA S 0303 --*/

static const uint32_t rtcInterruptMaskTable[] =
{
    0x00000008U,    /*!< RTC overflow interrupt */
    0x00000010U,    /*!< RTC alarm interrupt  */
    0x00000020U,    /*!< RTC second interrupt */
    0x00000038U     /*!< RTC_INT_ALL */
};

static const uint32_t rtcIntStatusTable[] =
{
    0x00000080U,    /*!< RTC overflow interrupt flag */
    0x00000100U,    /*!< RTC alarm interrupt  flag */
    0x00000800U,    /*!< RTC second interrupt flag */
    0x00000980U     /*!< RTC_INT_ALL */
};

static uint32_t rtcIntMaskStatus = 0;  /*PRQA S 3218*/

/** @} end of group RTC_Private_Variables */

/** @defgroup RTC_Global_Variables
 *  @{
 */

/** @} end of group RTC_Global_Variables */


/** @defgroup RTC_Private_FunctionDeclaration
 *  @{
 */
static void RTC_IntHandler(void);
void RTC_DriverIRQHandler(void);

/** @} end of group RTC_Private_FunctionDeclaration */

/** @defgroup RTC_Private_Functions
 *  @{
 */

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
        /* clear interrupt status */
        rtcRegPtr->RTC_CSR.SECONDS_INT_FLAG = 1U;
        if(rtcIsrCb[RTC_INT_SECOND] != NULL)
        {
            rtcIsrCb[RTC_INT_SECOND]();
        }
        else
        {
            rtcRegPtr->RTC_IER.SECONDS_IE = 0U;
        }
    }
    
    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;

}

/** @} end of group RTC_Private_Functions */

/** @defgroup RTC_Public_Functions
 *  @{
 */

 /**
 * @brief      RTC enable functioin
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
void RTC_Enable(void)
{
    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    rtcRegPtr->RTC_CSR.COUNT_EN = 1U;

    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

 /**
 * @brief      RTC disable functioin
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
void RTC_Disable(void)
{
    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    rtcRegPtr->RTC_CSR.COUNT_EN = 0U;

    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

 /**
 * @brief      RTC internal analog OSC clock disable functioin
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
void RTC_OSCDisable(void)
{
    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }
    
    rtcRegPtr->RTC_CSR.CRYSTAL_EN = 0U;

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
    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    rtcRegPtr->RTC_CSR.SW_RST = 1U;
    rtcRegPtr->RTC_CSR.SW_RST = 0U;
    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

/**
 * @brief      config whether write access to RTC in non-supervisor
 *
 * @param[in]  cmd: ENABLE/DISABLE
 *
 * @return none
 *
 */
void RTC_SupModeConfig(ControlState_t cmd)
{
    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    rtcRegPtr->RTC_CSR.SUP_EN = (uint32_t)cmd;
    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

/**
 * @brief      config second interrupt mux function
 *
 * @param[in]  muxSel: select frequency to generate second frequency
 *
 * @return none
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
 * @brief     Config RTC clcok source
 *
 * @param[in]   config:config clock output
 *
 * @return none
 *
 */
void RTC_OutputConfig(RTC_OutputConfig_t const * config)
{
    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    rtcRegPtr->RTC_CSR.CLKOUT_SEL = (uint32_t)config->clkOutput;
    rtcRegPtr->RTC_IER.SECOND_INT_MUX_SEL = (uint32_t)config -> freqSel;
    
    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

/**
 * @brief      Enable  RTC output clock function after configure output
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void RTC_OutputEnable(void)
{
    if(rtcRegPtr->RTC_LOCKR.LOCK !=  0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    rtcRegPtr->RTC_CSR.CLKOUT_PIN_EN = 0x1U;

    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

/**
 * @brief      Disable  RTC output clock function
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void RTC_OutputDisable(void)
{
    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    rtcRegPtr->RTC_CSR.CLKOUT_PIN_EN = 0U;

    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

/**
 * @brief        Select clock source function, suggest select clock source before 
 *               enable RTC clock
 *
 * @param[in]   clockSource:RTC clock source
 *
 * @return       
 *           -SUCC:clock config is success
 *           -ERR:clock config is fail
 *
 */
ResultStatus_t RTC_ClkConfig(RTC_Clk_t clockSource)
{
    ResultStatus_t ret = ERR;
    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    switch(clockSource)
    {
        case RTC_CLK_OSC32K_INT:            
            rtcRegPtr->RTC_CSR.CNT_CLK_SEL = 0U;
            CLK_OSC32KEnable(CLK_OSC_XTAL);             
            if(SUCC == CLK_WaitClkReady(CLK_SRC_OSC32K))
            {
                ret = SUCC;
            }
            else
            {
                ret = ERR;
            }
            break;

        case RTC_CLK_OSC32K_EXT:
            rtcRegPtr->RTC_CSR.CNT_CLK_SEL = 0U;
            CLK_OSC32KEnable(CLK_OSC_EXT_SRC);            
            if(SUCC == CLK_WaitClkReady(CLK_SRC_OSC32K))
            {               
                ret = SUCC;
            }
            else
            {
                ret = ERR;
            }
            break;

        case RTC_CLK_LPO32K:  
            CLK_LPO32KEnable();
            rtcRegPtr->RTC_CSR.CNT_CLK_SEL = 1U;            
            if(SUCC == CLK_WaitClkReady(CLK_SRC_LPO32K))
            {                 
                ret = SUCC;
            }
            else
            {
                ret = ERR;
            }
            break;
            
        case RTC_CLK_DISABLE:
            CLK_LPO32KDisable();
            CLK_OSC32KDisable();
            break;

        default:/*PRQA S 2016*/
            break;
    }
  
    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
    return ret;
}

/**
 * @brief       Set match counter register  to clear alarm interrupt
 *
 * @param[in]   counterValue:set the counter value
 *
 * @return      none
 *
 *****************************************************************************/
void RTC_SetMatchCounter(uint32_t counterValue)
{
    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    rtcRegPtr->RTC_MATCH_CNTR.MATCH_CNT = counterValue;

    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

/**
 * @brief        get match counter register
 *
 * @param[in]   none
 *
 * @return      match counter
 *
 *****************************************************************************/
uint32_t RTC_GetMatchCounter(void)
{
    return (rtcRegPtr->RTC_MATCH_CNTR.MATCH_CNT);
}

/**
 * @brief        Mask/Unmask the RTC interrupt funtion
 *
 * @param[in]     intType: select interrupt
 * @param[in]    intMask:Enable/Disable  interrupt
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
 * @brief       RTC Get alarm match status Function
 *
 * @param[in]    none
 *
 * @return       intstatus
 *
 */
IntStatus_t RTC_GetAlarmMatchStatus(void)
{
    return ((IntStatus_t)rtcRegPtr->RTC_CSR.ALARM_MATCHF); /*PRQA S 4342*/
}

/**
 * @brief       Get  second interrupt status Function
 *
 * @param[in]    none
 *
 * @return       intstatus
 *
 */
IntStatus_t RTC_GetSecondStatus(void)
{
    return ((IntStatus_t)rtcRegPtr->RTC_CSR.SECONDS_INT_FLAG); /*PRQA S 4342*/
}

/**
 * @brief       RTC Get alarm overflow status Function
 *
 * @param[in]    none
 *
 * @return       intstatus
 *
 */
IntStatus_t RTC_GetAlarmOVFStatus(void)
{
    return ((IntStatus_t)rtcRegPtr->RTC_CSR.OVF); /*PRQA S 4342*/
}

/**
 * @brief        Clear RTC overflow flag after disable RTC 
 *
 * @param[in]    countVal: set alarm counter value
 *
 * @return       none
 *
 *****************************************************************************/
void RTC_ClearOVF(uint32_t countVal)
{
    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }
    
    rtcRegPtr->RTC_ALARM_CNTR.ALARM_CNT = countVal;
    
    rtcRegPtr->RTC_LOCKR.LOCK = 0x1U;
}

/**
 * @brief        Clear RTC seconds interrupt flag function
 *
 * @param[in]    none
 *
 * @return       none
 *
 *****************************************************************************/
void RTC_ClearSecondsFlag(void)
{
    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }

    rtcRegPtr->RTC_CSR.SECONDS_INT_FLAG = 1;
    
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
 * @param[in]   delayVal: compensation delay value
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
 * @param[in]   Val: compensation counter value
 *
 * @return      none
 *
 *****************************************************************************/
void RTC_SetCompVal(uint8_t Val)
{
    if(rtcRegPtr->RTC_LOCKR.LOCK !=  0U)
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
 * @brief       Config the compensation  function
 *
 * @param[in]   config: compensation config
 *
 * @return      none
 *
 *****************************************************************************/
void RTC_CompConfig(RTC_CompConfig_t const *config)
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

/**
 * @brief  RTC ISR function
 *
 * @param  none
 *
 * @return none
 *
 */
void RTC_DriverIRQHandler(void)
{
   RTC_IntHandler();
}

/** @} end of group RTC_Public_Functions */

/** @} end of group RTC_definitions */

/** @} end of group Z20K11X_Peripheral_Driver */
