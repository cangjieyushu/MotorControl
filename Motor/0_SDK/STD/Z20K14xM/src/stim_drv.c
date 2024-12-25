/**************************************************************************************************/
/**
 * @file     stim_drv.c
 * @brief    STIM module driver file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 *
 **************************************************************************************************/

#include "stim_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @defgroup STIM
 *  @brief STIM driver modules
 *  @{
 */

/** @defgroup STIM_Private_Defines
 *  @{
 */

/** @} end of group STIM_Private_Defines */

/** @defgroup STIM_Private_Variables
 *  @{
 */
/*PRQA S 0303 ++*/
static stim_reg_t *const stimRegPtr = (stim_reg_t *) STIM_BASE_ADDR;
static stim_reg_w_t *const stimRegWPtr = (stim_reg_w_t *) STIM_BASE_ADDR;
/*PRQA S 0303 --*/

/**
 *  @brief STIM ISR callback function pointer array
 */
static isr_cb_t * stimIsrCb[STIM_NUM_ALL][STIM_INT_ALL]= 
{
    {NULL},
    {NULL},
    {NULL},
    {NULL}
};
/** @} end of group STIM_Private_Variables */

/** @defgroup STIM_Global_Variables
 *  @{
 */

/** @} end of group STIM_Global_Variables */

/** @defgroup STIM_Private_FunctionDeclaration
 *  @{
 */
/* local functions */
static void STIM_IntHandler(void);
void STIM_DriverIRQHandler(void);

/** @} end of group STIM_Private_FunctionDeclaration */

/** @defgroup STIM_Private_Function
 *  @{
 */
/**
 * @brief  STIM interrupt handle
 *
 * @return none
 *
 */
static void STIM_IntHandler(void)
{
    uint32_t i;
    uint32_t intStatus;

    for(i = 0U; i < (uint32_t)STIM_NUM_ALL; i++)
    {
        /* Read the interrupt status */
        intStatus = stimRegPtr->STIM_SCn[i].FLAG;
        /* only check enabled interrupt */
        intStatus = intStatus & stimRegPtr->STIM_SCn[i].IE;
        /* clear the interrupt */
        stimRegPtr->STIM_SCn[i].FLAG = intStatus;
        
        if(intStatus != 0U)
        {
            if(stimIsrCb[i][STIM_INT]!= NULL)
            {
                stimIsrCb[i][STIM_INT]();
            }
            /* Disable the interrupt */
            else
            {
                stimRegPtr->STIM_SCn[i].IE = 0U;
            }
        }
    }

    COMMON_DSB();
}

/**
 * @brief  STIM interrupt function
 *
 * @param  none
 *
 * @return none
 *
 */
void STIM_DriverIRQHandler(void)
{
    STIM_IntHandler();
}
/** @} end of group STIM_Private_Function */

/** @defgroup STIM_Public_Functions
 *  @{
 */
/**
 * @brief      Install call back function
 *
 * @param[in]  stimNo: Select the stim number,should be STIM_0,STIM_1,STIM_2,
 *                     STIM_3.
 * @param[in]  intType: Select the interrupt.
 *                     - STIM_INT
 * @param[in]  cbFun: pointer to callback function.
 *
 * @return     none
 *
 */
void STIM_InstallCallBackFunc(STIM_No_t stimNo, STIM_Int_t intType,
                               isr_cb_t * cbFun)
{
    stimIsrCb[stimNo][intType] = cbFun;
}

/**
 * @brief      Initialize STIM configuration
 *
 * @param[in]  stimNo: Select the stim number,should be STIM_0,STIM_1,STIM_2,
 *                     STIM_3.
 * @param[in]  stimConfigStruct: Stim configuration struct.
 *
 * @return     none
 *
 */
void STIM_Init(STIM_No_t stimNo, const STIM_Config_t* stimConfigStruct)
{
    stimRegPtr->STIM_SCn[stimNo].MODE = (uint32_t)stimConfigStruct->workMode;

    /* Enable prescaler */
    if(STIM_FREE_COUNT == stimConfigStruct->workMode)
    {
        stimRegPtr->STIM_CVn[stimNo].CV = 
                                    (uint32_t)stimConfigStruct->compareValue;
        stimRegPtr->STIM_SCn[stimNo].RSTDIS = 
                                    (uint32_t)stimConfigStruct->countResetMode;
        stimRegPtr->STIM_SCn[stimNo].CLKS = 
                                    (uint32_t)stimConfigStruct->clockSource;
        stimRegPtr->STIM_SCn[stimNo].PSEN = 
                                    (uint32_t)stimConfigStruct->prescalerMode;
        stimRegPtr->STIM_SCn[stimNo].PSDIV = 
                             (uint32_t)stimConfigStruct->prescalerOrFilterValue;
    }
    else
    {
        stimRegPtr->STIM_CVn[stimNo].CV = stimConfigStruct->compareValue;
        stimRegPtr->STIM_SCn[stimNo].RSTDIS = 
                                     (uint32_t)stimConfigStruct->countResetMode;
        stimRegPtr->STIM_SCn[stimNo].CLKS = 
                                     (uint32_t)stimConfigStruct->clockSource;
        stimRegPtr->STIM_SCn[stimNo].PSRC = 
                                     (uint32_t)stimConfigStruct->pinSource;
        stimRegPtr->STIM_SCn[stimNo].POL = 
                                     (uint32_t)stimConfigStruct->pinPolarity;
        stimRegPtr->STIM_SCn[stimNo].PSEN = 
                                     (uint32_t)stimConfigStruct->prescalerMode;
        stimRegPtr->STIM_SCn[stimNo].PSDIV = 
                             (uint32_t)stimConfigStruct->prescalerOrFilterValue;
    }
}

/**
 * @brief      Set compare value 
 *
 * @param[in]  stimNo: Select the stim number,should be STIM_0,STIM_1,STIM_2,
 *                     STIM_3.
 * @param[in]  compareValue: Stim compare value.
 *
 * @return     none
 *
 */
void STIM_SetCompareValue(STIM_No_t stimNo, uint32_t compareValue)
{

    /* Set compare value */
    stimRegWPtr->STIM_CVn[stimNo] = (uint32_t)compareValue;
}

/**
 * @brief      Current Value of stim
 *
 * @param[in]  stimNo: Select the stim number,should be STIM_0,STIM_1,STIM_2,
 *                     STIM_3.
 *
 * @return      value of stim
 *
 */
uint32_t STIM_GetCurrentCounterValue(STIM_No_t stimNo)
{
    /* Current Value of STIM */
    return ((uint32_t)stimRegWPtr->STIM_CNTn[stimNo]);
}

/**
 * @brief      Enable stim
 *
 * @param[in]  stimNo: Select the stim number,should be STIM_0,STIM_1,STIM_2,
 *                     STIM_3.
 *
 * @return     none
 *
 */
void STIM_Enable(STIM_No_t stimNo)
{
    stimRegPtr->STIM_SCn[stimNo].EN = 1U;
}

/**
 * @brief      Disable stim
 *
 * @param[in]  stimNo: Select the stim number,should be STIM_0,STIM_1,STIM_2,
 *                     STIM_3.
 *
 * @return     none
 *
 */
void STIM_Disable(STIM_No_t stimNo)
{
    stimRegPtr->STIM_SCn[stimNo].EN = 0U;
}

/**
 * @brief       Enable/Disable the stim interrupt
 *
 * @param[in]   stimNo: Select the stim number,should be STIM_0,STIM_1,STIM_2,
 *                      STIM_3.
 * @param[in]   newState: Enable/Disable function state.
 *             - ENABLE: enable interrupt
 *             - DISABLE: disable interrupt
 *
 * @return     none
 *
 */
void STIM_IntCmd(STIM_No_t stimNo, ControlState_t newState)
{
    /* Mask/Unmask the timer interrupt */
    stimRegPtr->STIM_SCn[stimNo].IE = (uint32_t)newState;
}

/**
 * @brief      Enable or disable the STIM DMA function.
 *
 * @param[in]  stimNo: Select the stim number,should be STIM_0,STIM_1,STIM_2,
 *                     STIM_3.
 * @param[in]  newState: Enable/Disable function state.
 *             - ENABLE: enable DMA request
 *             - DISABLE: disable DMA request
 *
 * @return     none
 *
 */
void STIM_DmaCmd(STIM_No_t stimNo, ControlState_t newState)
{
    stimRegPtr->STIM_SCn[stimNo].DMAE = (uint32_t)newState;
}

/**
 * @brief      Checks if the status flag is set when the counter matches the
 *             compare value
 *
 * @param[in]  stimNo: Select the stim number,should be STIM_0,STIM_1,STIM_2,
 *                     STIM_3.
 *
 * @return     The status flag.
 *             - SET
 *             - RESET
 *
 */
FlagStatus_t STIM_GetStatus(STIM_No_t stimNo)
{
    FlagStatus_t intBitStatus;

    intBitStatus = (stimRegPtr->STIM_SCn[stimNo].FLAG != 0U ? SET : RESET);
    return intBitStatus;
}

/**
 * @brief      Clear the interrupt of stim
 *
 * @param[in]  stimNo: Select the stim number,should be STIM_0,STIM_1,STIM_2,
 *                     STIM_3.
 *
 * @return     none
 *
 */
void STIM_ClearInt(STIM_No_t stimNo)
{
    /* Write 1 to clear interrupt */
    stimRegPtr->STIM_SCn[stimNo].FLAG = 1U;
}

/** @} end of group STIM_Public_Functions */

/** @} end of group STIM */

/** @} end of group Z20K14XM_Peripheral_Driver */
