/**************************************************************************************************/
/**
 * @file      : Int_Drv.c
 * @brief     : Interrupt module driver file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#include "Int_Drv.h"

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

/*PRQA S 0306 ++*/
static Z20_SCBType *const Int_ScbRegPtr = (Z20_SCBType *) Z20_SCB_BASE;
static Z20_SysTickType *const Int_SysTickPtr = (Z20_SysTickType *) Z20_SYSTICK_BASE;
static Z20_NVICType *const Int_NvicRegPtr = (Z20_NVICType *) Z20_NVIC_BASE;
/*PRQA S 0306 --*/

/** @} end of group Private_VariableDefinition */

/** @defgroup Private_FunctionDeclaration
 *  @{
 */

 /** @} end of group Private_FunctionDeclaration */

/** @defgroup Private_FunctionDefinition
 *  @{
 */

/** @} end of group Private_FunctionDefinition */

/** @defgroup Public_FunctionDefinition
 *  @{
 */

/**
 * @brief     Enable interrupt.
 * @param[in] IrqNum: Interrupt number, the valid value is defined in enum Z20_IrqNumType.
 *                    This function can only enable the interrupt whose IrqNum >= 0;
 *                    Otherwise, this function takes no effect.
 * @return    Ret:
 * @retval    COMMON_ERR  : Interrupt enable failed.
 * @retval    COMMON_SUCC : Interrupt enable successful.
 */
Common_ResultStatusType Int_EnableIrq(Z20_IrqNumType IrqNum)
{
    Common_ResultStatusType Ret = COMMON_ERR;

    if ((sint32)(IrqNum) >= 0)
    {
        Int_NvicRegPtr->ISER[(((uint32)IrqNum) >> 5U)] = \
        (uint32)(1UL << (((uint32)IrqNum) & 0x1FU));

        Ret = COMMON_SUCC;
    }

    return Ret;
}

/**
 * @brief     Get interrupt enable status.
 * @param[in] IrqNum: Interrupt number, the valid value is defined in enum Z20_IrqNumType.
 *                    This function can only enable the interrupt whose IrqNum >= 0;
 *                    Otherwise, this function takes no effect.
 * @return    IntEnStatus: Interrupt enable status
 * @retval    0: Interrupt is not enabled.
 * @retval    1: Interrupt is enabled.
 */
uint32 Int_GetEnableIrq(Z20_IrqNumType IrqNum)
{
    uint32 IntEnStatus = 0U;

    if ((sint32)(IrqNum) >= 0)
    {
        IntEnStatus = (uint32)(((Int_NvicRegPtr->ISER[(((uint32)IrqNum) \
            >> 5U)] & (1UL << (((uint32)IrqNum) & 0x1FU))) != 0U) ? 1U : 0U);
    }

    return (IntEnStatus);
}

/**
 * @brief     Disable interrupt.
 * @param[in] IrqNum: Interrupt number, the valid value is defined in enum Z20_IrqNumType.
 *                    This function can only enable the interrupt whose IrqNum >= 0;
 *                    Otherwise, this function takes no effect.
 * @return    Ret:
 * @retval    COMMON_ERR  : Interrupt disable failed.
 * @retval    COMMON_SUCC : Interrupt disable successful.
 */
Common_ResultStatusType Int_DisableIrq(Z20_IrqNumType IrqNum)
{
    Common_ResultStatusType Ret = COMMON_ERR;

    if ((sint32)(IrqNum) >= 0)
    {
        Int_NvicRegPtr->ICER[(((uint32)IrqNum) >> 5U)] = \
            (uint32)(1UL << (((uint32)IrqNum) & 0x1FU));
        COMMON_DSB();
        COMMON_ISB();

        Ret = COMMON_SUCC;
    }

    return (Ret);
}

/**
 * @brief     Get interrupt pending status.
 * @param[in] IrqNum: Interrupt number, the valid value is defined in enum Z20_IrqNumType.
 *                    This function can only enable the interrupt whose IrqNum >= 0;
 *                    Otherwise, this function takes no effect.
 * @return    IntPendingStatus: Interrupt pending status
 * @retval    0: Interrupt status is not pending.
 * @retval    1: Interrupt status is pending.
 */
uint32 Int_GetPendingIrq(Z20_IrqNumType IrqNum)
{
    uint32 IntPendingStatus = 0U;

    if ((sint32)(IrqNum) >= 0)
    {
        IntPendingStatus = (uint32)(((Int_NvicRegPtr->ISPR[(((uint32)IrqNum) \
            >> 5U)] & (1UL << (((uint32)IrqNum) & 0x1FU))) != 0UL) ? 1U : 0U);
    }

    return (IntPendingStatus);
}

/**
 * @brief     Set interrupt to pending. 
 * @param[in] IrqNum: Interrupt number, the valid value is defined in enum Z20_IrqNumType.
 *                    This function can only enable the interrupt whose IrqNum >= 0;
 *                    Otherwise, this function takes no effect.
 * @return    Ret:
 * @retval    COMMON_ERR  : Interrupt pending setting failed.
 * @retval    COMMON_SUCC : Interrupt pending setting successful.
 */
Common_ResultStatusType Int_SetPendingIrq(Z20_IrqNumType IrqNum)
{
    Common_ResultStatusType Ret = COMMON_ERR;

    if ((sint32)(IrqNum) >= 0)
    {
        Int_NvicRegPtr->ISPR[(((uint32)IrqNum) >> 5U)] = \
            (uint32)(1UL << (((uint32)IrqNum) & 0x1FU));

        Ret = COMMON_SUCC;
    }

    return (Ret);
}

/**
 * @brief     Clear interrupt pending status
 * @param[in] IrqNum: Interrupt number, the valid value is defined in enum Z20_IrqNumType.
 *                    This function can only enable the interrupt whose IrqNum >= 0;
 *                    Otherwise, this function takes no effect.
 * @return    Ret:
 * @retval    COMMON_ERR  : Interrupt pending clear failed.
 * @retval    COMMON_SUCC : Interrupt pending clear successful.
 */
Common_ResultStatusType Int_ClearPendingIrq(Z20_IrqNumType IrqNum)
{
    Common_ResultStatusType Ret = COMMON_ERR;

    if ((sint32)(IrqNum) >= 0)
    {
        Int_NvicRegPtr->ICPR[(((uint32)IrqNum) >> 5U)] = \
            (uint32)(1UL << (((uint32)IrqNum) & 0x1FU));

        Ret = COMMON_SUCC;
    }

    return (Ret);
}

/**
 * @brief     Set interrupt priority
 * @param[in] IrqNum: Interrupt number, the valid value is defined in enum Z20_IrqNumType.
 * @param[in] Priority: Priority value, for IrqNum>=0 the priority value range should be within 0-3.
 *                      For IrqNum<0, only system handler SVCall_IRQn/PendSV_IRQn/SysTick_IRQn
 *                      can be set and all other bits in SHPR2/SHPR3 are reserved.
 * @return    None
 */
void Int_SetPriority(Z20_IrqNumType IrqNum, uint32 Priority)
{
    if ((sint32)(IrqNum) >= 0)
    {
        Int_NvicRegPtr->IPR[INT_IP_IDX(IrqNum)]  = ((uint32)(Int_NvicRegPtr->IPR[INT_IP_IDX(IrqNum)]  \
            & ~(0xFFUL << INT_BIT_SHIFT(IrqNum))) | (((Priority << (8U - INT_PRIO_BITS)) \
            & (uint32)0xFFUL) << INT_BIT_SHIFT(IrqNum)));
    }
    else
    {
        /*PRQA S 2896 ++*/
        Int_ScbRegPtr->SHPR[INT_SHP_IDX(IrqNum)] = ((uint32)(Int_ScbRegPtr->SHPR[INT_SHP_IDX(IrqNum)] \
            & ~(0xFFUL << INT_BIT_SHIFT(IrqNum))) | (((Priority << (8U - INT_PRIO_BITS)) \
            & (uint32)0xFFUL) << INT_BIT_SHIFT(IrqNum)));
        /*PRQA S 2896 --*/
    }
}

/**
 * @brief     Get interrupt priority
 * @param[in] IrqNum: Interrupt number, the valid value is defined in enum Z20_IrqNumType.
 * @return    IntPriority: Interrupt priority value, the value is valid only for IrqNum>=0 and 
 *                         the system handler SVCall_IRQn/PendSV_IRQn/SysTick_IRQn.
 *                         For IrqNum<0, all other bits in SHPR2/SHPR3 are reserved.
 */
uint32 Int_GetPriority(Z20_IrqNumType IrqNum)
{
    uint32 IntPriority = 0U;

    if ((sint32)(IrqNum) >= 0)
    {
        IntPriority = ((uint32)(((Int_NvicRegPtr->IPR[INT_IP_IDX(IrqNum)] >> \
            INT_BIT_SHIFT(IrqNum) ) & (uint32)0xFFUL) >> (8U - INT_PRIO_BITS)));
    }
    else
    {
        /*PRQA S 2896 ++*/
        IntPriority = ((uint32)(((Int_ScbRegPtr->SHPR[INT_SHP_IDX(IrqNum)] >> \
            INT_BIT_SHIFT(IrqNum) ) & (uint32)0xFFUL) >> (8U - INT_PRIO_BITS)));
        /*PRQA S 2896 --*/
    }

    return (IntPriority);
}

/**
 * @brief     Set interrupt vector address
 * @param[in] IrqNum: Interrupt number, the valid value is defined in enum Z20_IrqNumType.
 * @param[in] Vector: Interrupt handler address
 * @Return    None
 */
void Int_SetVector(Z20_IrqNumType IrqNum, uint32 Vector)
{  
    /*PRQA S 0306 ++*/
    uint32 *Vectors = (uint32 *)Int_ScbRegPtr->VTOR;
    /*PRQA S 0306 --*/

    /*PRQA S 1820 ++*/
    Vectors[(sint32)IrqNum + INT_NVIC_IRQ_OFFSET] = Vector;
    /*PRQA S 1820 --*/
}

/**
 * @brief     Get interrupt vector address
 * @param[in] IrqNum: Interrupt number, the valid value is defined in enum Z20_IrqNumType.
 * @Return    Result: Interrupt handler address.
 */
uint32 Int_GetVector(Z20_IrqNumType IrqNum)
{
    /*PRQA S 0306 ++*/
    uint32 *Vectors = (uint32 *)Int_ScbRegPtr->VTOR;
    /*PRQA S 0306 --*/
    uint32 Result = 0U;

    /*PRQA S 1820 ++*/
    Result = Vectors[(sint32)IrqNum + INT_NVIC_IRQ_OFFSET];
    /*PRQA S 1820 --*/

    return (Result);
}

/**
 * @brief     SYSTICK config and enable
 * @param[in] Ticks: Tick value that to be set.
 * @return    Ret:
 * @retval    COMMON_ERR  : SysTick configure failed.
 * @retval    COMMON_SUCC : SysTick configure successful.
 */
Common_ResultStatusType Int_ConfigSysTick(uint32 Ticks)
{
    Common_ResultStatusType Ret = COMMON_SUCC;

    if ((Ticks - 1U) > (0xFFFFFFU))
    {
        Ret = COMMON_ERR;
    }
    else
    {
        /* Set reload register */
        Int_SysTickPtr->LOAD  = (uint32)(Ticks - 1U); 
        /* Set Priority */   
        Int_SetPriority(SYSTICK_IRQn, (1U << INT_PRIO_BITS) - 1U);
        /* Load Counter Value */
        Int_SysTickPtr->VAL = 0U;  
        /* Enable SysTick IRQ and Start Timer */
        Int_SysTickPtr->CTRL = (1U << 2U) | (1U << 1U) | (1U);
    }

    return (Ret);
}

/** @} end of group Public_FunctionDefinition */
