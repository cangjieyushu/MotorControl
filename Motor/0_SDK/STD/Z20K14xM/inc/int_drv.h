/**************************************************************************************************/
/**
 * @file     int_drv.h
 * @brief    interrupt driver header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/
#ifndef INT_DRV_H
#define INT_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  INT
 *  @{
 */

/** @defgroup INT_Public_Types 
 *  @{
 */

#define NVIC_DEVICE_IRQ_OFFSET          16

/** @} end of group INT_Public_Types */

/** @defgroup SYSCTRL_Public_Constants
 *  @{
 */

/** @} end of group SYSCTRL_Public_Constants */

/** @defgroup SYSCTRL_Public_Macro
 *  @{
 */

/** @} end of group SYSCTRL_Public_Macro */

/** @defgroup INT_Public_FunctionDeclaration
 *  @brief INT functions declaration
 *  @{
 */

/**
 * @brief     Enable Interrupt.
 * @param[in] IRQn: Interrupt number.
 * @return    None.
 */
void INT_EnableIRQ(IRQn_Type IRQn);

/**
 * @brief     Get Interrupt Enable Status.
 * @param[in] IRQn: Interrupt number.
 * @return    intEnStatus: Interrupt enable status
             - 0:Interrupt is not enabled.
             - 1:Interrupt is enabled.
 */
uint32_t INT_GetEnableIRQ(IRQn_Type IRQn);

/**
 * @brief     Disable Interrupt.
 * @param[in] IRQn: Interrupt number.
 * @return    None.
 */
void INT_DisableIRQ(IRQn_Type IRQn);

/**
 * @brief      Get Interrupt Pending Status.
 * @param[in]  IRQn: Interrupt number.
 * @return     intPendingStatus: Interrupt pending status
              - 0  Interrupt status is not pending.
              - 1  Interrupt status is pending.
 */
uint32_t INT_GetPendingIRQ(IRQn_Type IRQn);

/**
 * @brief     Set Interrupt To Pending. 
 * @param[in] IRQn: Interrupt number.
 * @return    None.
 */
void INT_SetPendingIRQ(IRQn_Type IRQn);


/**
 * @brief     Clear Interrupt Pending Status
 * @param[in] IRQn: Interrupt number.
 * @note      None
 */
void INT_ClearPendingIRQ(IRQn_Type IRQn);

/**
 * @brief     Get Interrupt Active Status
 * @param[in] IRQn: Interrupt number.
 * @retunr    Interrupt active status
             - 0  Interrupt status is not active.
             - 1  Interrupt status is active.
 */
uint32_t INT_GetActive(IRQn_Type IRQn);

/**
 * @brief       Set Interrupt Priority
 * @param[in]  IRQn: Interrupt number.
 * @param[in]  priority:  Priority level.
 * @return      None
 */
void INT_SetPriority(IRQn_Type IRQn, uint32_t priority);

/**
 * @brief      Get Interrupt Priority
 * @param[in] IRQn: Interrupt number.
 * @return     intNumber: None
 */
uint32_t INT_GetPriority(IRQn_Type IRQn);

/**
 * @brief        Set Interrupt Vector
 * @param[in]    IRQn: Interrupt number
 * @param[in]    vector: Interrupt handler address
 * @return       None
 */
void INT_SetVector(IRQn_Type IRQn, uint32_t vector);

/**
 * @brief        Get Interrupt Vector
 * @param[in]    IRQn: Interrupt number.
 * @return       Interrupt handler address.
 */
uint32_t INT_GetVector(IRQn_Type IRQn);

/**
 * @brief SYSTICK config and enable 
 * @return Function status.
 *          0: Success
 *          1: Fail
 */
uint32_t SysTick_Config(uint32_t ticks);

/** @} end of group INT_Public_FunctionDeclaration */

/** @} end of group INT  */

/** @} end of group Z20K14XM_Peripheral_Driver */

#endif /* INT_DRV_H */
