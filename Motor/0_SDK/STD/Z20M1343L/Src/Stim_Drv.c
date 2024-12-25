/**************************************************************************************************/
/**
 * @file      : Stim_Drv.c
 * @brief     : Stim module driver file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#include "Stim_Drv.h"

/** @defgroup Private_MacroDefinition
 *  @{
 */

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

/**
 * @brief     Stim register address.
 */
/*PRQA S 0303 ++*/
static Reg_Stim_BfType *const Stim_RegBfPtr = (Reg_Stim_BfType *) STIM_BASE_ADDR;
/*PRQA S 0303 --*/

/**
 * @brief     Stim ISR callback function pointer array.
 */
static Isr_CbFuncType * Stim_IsrCbFuncPtr = NULL_PTR;

/** @} end of group Private_VariableDefinition */

/** @defgroup Private_FunctionDeclaration
 *  @{
 */

void Stim_DriverIrqHandler(void);

 /** @} end of group Private_FunctionDeclaration */

/** @defgroup Private_FunctionDefinition
 *  @{
 */

/**
 * @brief     Stim interrupt handler.
 * 
 * @param     None
 * 
 * @return    None
 */
void Stim_DriverIrqHandler(void)
{
    uint32 IntStatus;

    /* Read the interrupt status */
    IntStatus = Stim_RegBfPtr->STIM_INT_STS.INT;
    /* only check enabled interrupt */
    IntStatus = IntStatus & Stim_RegBfPtr->STIM_INT_CTRL.INT_EN;
    /* clear the interrupt */
    Stim_RegBfPtr->STIM_INT_CTRL.INT_CLR = IntStatus;
        
    if(0U != IntStatus)
    {
        if(Stim_IsrCbFuncPtr != NULL_PTR)
        {
            Stim_IsrCbFuncPtr();
        }
        /* Disable the interrupt */
        else
        {
            Stim_RegBfPtr->STIM_INT_CTRL.INT_EN = 0U;
        }
    }
    
}

/** @} end of group Private_FunctionDefinition */

/** @defgroup Public_FunctionDefinition
 *  @{
 */

/**
 * @brief     Install call back function.
 * 
 * @param[in] CbFun: pointer to callback function.
 * 
 * @return    None
 */
void Stim_InstallCallBackFunc(Isr_CbFuncType * CbFun)
{
    Stim_IsrCbFuncPtr = CbFun;
}

/**
 * @brief     Initialize stim configuration.
 * 
 * @param[in] StimConfigStruct: Stim configuration struct.
 * 
 * @return    None
 */
void Stim_Init(const Stim_ConfigType* StimConfigStruct)
{
    Stim_RegBfPtr->STIM_CONF0.FREERUN = (uint32)StimConfigStruct->FreerunMode;

    if(STIM_MATCH == StimConfigStruct->FreerunMode)
    {
        Stim_RegBfPtr->STIM_MATCH_VAL.MATCH_VAL = StimConfigStruct->MatchValue;
    }
}

/**
 * @brief     Set match value.
 * 
 * @param[in] MatValue: Stim match value.
 * 
 * @return    None
 */
void Stim_SetMatchValue(uint32 MatValue)
{
    /* Set match value */
    Stim_RegBfPtr->STIM_MATCH_VAL.MATCH_VAL = (uint32)MatValue;
}

/**
 * @brief     Current value of stim.
 * 
 * @param     None
 * 
 * @return    Value of stim.
 */
uint32 Stim_GetCurrentTimerValue(void)
{
    /* Current Value of STIM */
    return ((uint32)Stim_RegBfPtr->STIM_TIM_VAL.TIM_VAL);
}

/**
 * @brief     Enable stim.
 * 
 * @param     None
 * 
 * @return    None

 */
void Stim_Enable(void)
{
    Stim_RegBfPtr->STIM_CONF0.EN = 1U;
}

/**
 * @brief     Disable stim.
 * 
 * @param     None
 * 
 * @return    None
 *
 */
void Stim_Disable(void)
{
    Stim_RegBfPtr->STIM_CONF0.EN = 0U;
}

/**
 * @brief     Enable/Disable the stim interrupt.
 * 
 * @param[in] IntEnStatus: Enable/Disable function state.
 *            - COMMON_ENABLE:  enable interrupt
 *            - COMMON_DISABLE: disable interrupt
 * 
 * @return    None
 *
 */
void Stim_EnableInt(Common_ControlStateType IntEnStatus)
{
    /* Mask/Unmask the timer interrupt */
    Stim_RegBfPtr->STIM_INT_CTRL.INT_EN = (uint32)IntEnStatus;
}


/**
 * @brief     Checks if the interrupt status flag is set when the timer gets full or matches the
 *            match value.
 * 
 * @param     None
 * 
 * @return    IntStatusFlag: The interrupt status flag.
 * @retval    COMMON_SET.
 * @retval    COMMON_RESET.
 *
 */
Common_IntStatusType Stim_GetIntStatus(void)
{
    Common_IntStatusType IntStatusFlag;

    IntStatusFlag = ((Stim_RegBfPtr->STIM_INT_STS.INT != 0U) ? COMMON_SET : COMMON_RESET);
    return IntStatusFlag;
}

/**
 * @brief     Clear the interrupt flag of stim.
 * 
 * @param     None
 * 
 * @return    None
 *
 */
void Stim_ClearInt(void)
{
    /* Write 1 to clear interrupt flag */
    Stim_RegBfPtr->STIM_INT_CTRL.INT_CLR = 1U;
}

/** @} end of group Public_FunctionDefinition */
