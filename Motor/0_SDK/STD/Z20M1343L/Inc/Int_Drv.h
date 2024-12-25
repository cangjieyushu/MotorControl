/**************************************************************************************************/
/**
 * @file      : Int_Drv.h
 * @brief     : Interrupt module driver header file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
#ifndef INT_DRV_H
#define INT_DRV_H

#include "Common_Drv.h"

/** @addtogroup Public_MacroDefinition
 *  @{
 */

#define INT_NVIC_IRQ_OFFSET             (16U)       /*!< Number of system exceptions */
#define INT_PRIO_BITS                   (2U)        /*!< Number of Bits used for Priority Levels */

/* Macros for offset and byte mask */
#define INT_BIT_SHIFT(IRQn)         (((((uint32)(sint32)(IRQn))) &  0x03UL) * 8UL)
#define INT_SHP_IDX(IRQn)           ((((((uint32)(sint32)(IRQn)) & 0x0FUL)-8UL) >> 2UL))
#define INT_IP_IDX(IRQn)            ((((uint32)(sint32)(IRQn)) >> 2UL))

/** @} end of Public_MacroDefinition */

/** @defgroup Public_TypeDefinition
 *  @{
 */

/** @} end of group Public_TypeDefinition */

/** @defgroup Global_VariableDeclaration
 *  @{
 */

/** @} end of group Global_VariableDeclaration */

/** @defgroup Public_FunctionDeclaration
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
Common_ResultStatusType Int_EnableIrq(Z20_IrqNumType IrqNum);

/**
 * @brief     Get interrupt enable status.
 * @param[in] IrqNum: Interrupt number, the valid value is defined in enum Z20_IrqNumType.
 *                    This function can only enable the interrupt whose IrqNum >= 0;
 *                    Otherwise, this function takes no effect.
 * @return    IntEnStatus: Interrupt enable status
 * @retval    0: Interrupt is not enabled.
 * @retval    1: Interrupt is enabled.
 */
uint32 Int_GetEnableIrq(Z20_IrqNumType IrqNum);

/**
 * @brief     Disable interrupt.
 * @param[in] IrqNum: Interrupt number, the valid value is defined in enum Z20_IrqNumType.
 *                    This function can only enable the interrupt whose IrqNum >= 0;
 *                    Otherwise, this function takes no effect.
 * @return    Ret:
 * @retval    COMMON_ERR  : Interrupt disable failed.
 * @retval    COMMON_SUCC : Interrupt disable successful.
 */
Common_ResultStatusType Int_DisableIrq(Z20_IrqNumType IrqNum);

/**
 * @brief     Get interrupt pending status.
 * @param[in] IrqNum: Interrupt number, the valid value is defined in enum Z20_IrqNumType.
 *                    This function can only enable the interrupt whose IrqNum >= 0;
 *                    Otherwise, this function takes no effect.
 * @return    IntPendingStatus: Interrupt pending status
 * @retval    0: Interrupt status is not pending.
 * @retval    1: Interrupt status is pending.
 */
uint32 Int_GetPendingIrq(Z20_IrqNumType IrqNum);

/**
 * @brief     Set interrupt to pending. 
 * @param[in] IrqNum: Interrupt number, the valid value is defined in enum Z20_IrqNumType.
 *                    This function can only enable the interrupt whose IrqNum >= 0;
 *                    Otherwise, this function takes no effect.
 * @return    Ret:
 * @retval    COMMON_ERR  : Interrupt pending setting failed.
 * @retval    COMMON_SUCC : Interrupt pending setting successful.
 */
Common_ResultStatusType Int_SetPendingIrq(Z20_IrqNumType IrqNum);

/**
 * @brief     Clear interrupt pending status
 * @param[in] IrqNum: Interrupt number, the valid value is defined in enum Z20_IrqNumType.
 *                    This function can only enable the interrupt whose IrqNum >= 0;
 *                    Otherwise, this function takes no effect.
 * @return    Ret:
 * @retval    COMMON_ERR  : Interrupt pending clear failed.
 * @retval    COMMON_SUCC : Interrupt pending clear successful.
 */
Common_ResultStatusType Int_ClearPendingIrq(Z20_IrqNumType IrqNum);

/**
 * @brief     Set interrupt priority
 * @param[in] IrqNum: Interrupt number, the valid value is defined in enum Z20_IrqNumType.
 * @param[in] Priority: Priority value, for IrqNum>=0 the priority value range should be within 0-3.
 *                      For IrqNum<0, only system handler SVCall_IRQn/PendSV_IRQn/SysTick_IRQn
 *                      can be set and all other bits in SHPR2/SHPR3 are reserved.
 * @return    None
 */
void Int_SetPriority(Z20_IrqNumType IrqNum, uint32 Priority);

/**
 * @brief     Get interrupt priority
 * @param[in] IrqNum: Interrupt number, the valid value is defined in enum Z20_IrqNumType.
 * @return    IntPriority: Interrupt priority value, the value is valid only for IrqNum>=0 and 
 *                         the system handler SVCall_IRQn/PendSV_IRQn/SysTick_IRQn.
 *                         For IrqNum<0, all other bits in SHPR2/SHPR3 are reserved.
 */
uint32 Int_GetPriority(Z20_IrqNumType IrqNum);

/**
 * @brief     Set interrupt vector address
 * @param[in] IrqNum: Interrupt number, the valid value is defined in enum Z20_IrqNumType.
 * @param[in] Vector: Interrupt handler address
 * @Return    None
 */
void Int_SetVector(Z20_IrqNumType IrqNum, uint32 Vector);

/**
 * @brief     Get interrupt vector address
 * @param[in] IrqNum: Interrupt number, the valid value is defined in enum Z20_IrqNumType.
 * @Return    Result: Interrupt handler address.
 */
uint32 Int_GetVector(Z20_IrqNumType IrqNum);

/**
 * @brief     SYSTICK config and enable
 * @param[in] Ticks: Tick value that to be set.
 * @return    Ret:
 * @retval    COMMON_ERR  : SysTick configure failed.
 * @retval    COMMON_SUCC : SysTick configure successful.
 */
Common_ResultStatusType Int_ConfigSysTick(uint32 Ticks);

/** @} end of group Public_FunctionDeclaration */

#endif /* INT_DRV_H */
