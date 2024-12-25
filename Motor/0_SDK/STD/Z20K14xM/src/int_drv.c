/**************************************************************************************************/
/**
 * @file     int_drv.c
 * @brief    interrupt driver source file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#include "int_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @defgroup INT
 *  @brief Interrupt driver modules
 *  @{
 */

/** @defgroup INT_Private_Type
 *  @{
 */

/** @} end of group INT_Private_Type*/

/** @defgroup INT_Private_Defines
 *  @{
 */

/** @} end of group INT_Private_Defines */

/** @defgroup INT_Private_Variables
 *  @{
 */

/** @} end of group INT_Private_Variables */

/** @defgroup INT_Global_Variables
 *  @{
 */

/**
 *  @brief INT Register address array
 */

/*PRQA S 0306 ++*/
static Z20_SCBType *const SCBRegPtr = (Z20_SCBType *) Z20_SCB_BASE;
static Z20_SysTickType *const SysTickPtr = (Z20_SysTickType *) Z20_SYSTICK_BASE;
static Z20_NVICType *const NVICRegPtr = (Z20_NVICType *) Z20_NVIC_BASE;
/*PRQA S 0306 --*/

/** @} end of group INT_Global_Variables */

/** @defgroup INT_Private_FunctionDeclaration
 *  @{
 */


/** @} end of group INT_Private_FunctionDeclaration */

/** @defgroup INT_Private_Functions
 *  @{
 */

/** @} end of group INT_Private_Functions */

/** @defgroup INT_Public_Functions
 *  @{
 */
/**
 * @brief     Enable Interrupt.
 * @param[in] IRQn: Interrupt number.
 * @return    None.
 */
void INT_EnableIRQ(IRQn_Type IRQn)
{
    if ((int32_t)(IRQn) >= 0)
    {
      NVICRegPtr->ISER[(((uint32_t)IRQn) >> 5U)] = \
        (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FU));
    }
}

/**
 * @brief     Get Interrupt Enable Status.
 * @param[in] IRQn: Interrupt number.
 * @return    intEnStatus: Interrupt enable status
             - 0:Interrupt is not enabled.
             - 1:Interrupt is enabled.
 */
uint32_t INT_GetEnableIRQ(IRQn_Type IRQn)
{
    uint32_t intEnStatus = 0U;

    if ((int32_t)(IRQn) >= 0)
    {
        intEnStatus = (uint32_t)(((NVICRegPtr->ISER[(((uint32_t)IRQn) \
            >> 5U)] & (1UL << (((uint32_t)IRQn) & 0x1FU))) != 0U) ? 1U : 0U);
    }

    return (intEnStatus);
}

/**
 * @brief     Disable Interrupt.
 * @param[in] IRQn: Interrupt number.
 * @return    None.
 */
void INT_DisableIRQ(IRQn_Type IRQn)
{
    if ((int32_t)(IRQn) >= 0)
    {
        NVICRegPtr->ICER[(((uint32_t)IRQn) >> 5U)] = \
            (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FU));
        COMMON_DSB();
        COMMON_ISB();
    }
}

/**
 * @brief      Get Interrupt Pending Status.
 * @param[in]  IRQn: Interrupt number.
 * @return     intPendingStatus: Interrupt pending status
              - 0  Interrupt status is not pending.
              - 1  Interrupt status is pending.
 */
uint32_t INT_GetPendingIRQ(IRQn_Type IRQn)
{
    uint32_t intPendingStatus = 0U;
    if ((int32_t)(IRQn) >= 0)
    {
        intPendingStatus = (uint32_t)(((NVICRegPtr->ISPR[(((uint32_t)IRQn) \
            >> 5U)] & (1UL << (((uint32_t)IRQn) & 0x1FU))) != 0UL) ? 1U : 0U);
    }
    return (intPendingStatus);
}

/**
 * @brief     Set Interrupt To Pending. 
 * @param[in] IRQn: Interrupt number.
 * @return    None.
 */
void INT_SetPendingIRQ(IRQn_Type IRQn)
{
    if ((int32_t)(IRQn) >= 0)
    {
        NVICRegPtr->ISPR[(((uint32_t)IRQn) >> 5U)] = \
            (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FU));
    }
}

/**
 * @brief     Clear Interrupt Pending Status
 * @param[in] IRQn: Interrupt number.
 * @note      None
 */
void INT_ClearPendingIRQ(IRQn_Type IRQn)
{
    if ((int32_t)(IRQn) >= 0)
    {
        NVICRegPtr->ICPR[(((uint32_t)IRQn) >> 5U)] = \
            (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FU));
    }
}

/**
 * @brief     Get Interrupt Active Status
 * @param[in] IRQn: Interrupt number.
 * @retunr    Interrupt active status
             - 0  Interrupt status is not active.
             - 1  Interrupt status is active.
 */
uint32_t INT_GetActive(IRQn_Type IRQn)
{
    uint32_t activeStatus = 0U;

    if ((int32_t)(IRQn) >= 0)
    {
        activeStatus = (uint32_t)(((NVICRegPtr->IABR[(((uint32_t)IRQn) \
            >> 5U)] & (1UL << (((uint32_t)IRQn) & 0x1FU))) != 0U) ? 1U : 0U);
    }

    return (activeStatus);
}

/**
 * @brief       Set Interrupt Priority
 * @param[in]  IRQn: Interrupt number.
 * @param[in]  priority:  Priority level.
 * @return      None
 */
void INT_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
    if ((int32_t)(IRQn) >= 0)
    {
        NVICRegPtr->IP[((uint32_t)IRQn)] = (uint8_t)((priority << \
        (8U - INT_PRIO_BITS)) & (uint32_t)0xFFU);
    }
    else
    {
        /*PRQA S 2896 ++*/
        SCBRegPtr->SHP[(((uint32_t)IRQn) & 0xFU)-4U] = (uint8_t)((priority << \
        (8U - INT_PRIO_BITS)) & (uint32_t)0xFFU);
        /*PRQA S 2896 --*/
    }
}

/**
 * @brief      Get Interrupt Priority
 * @param[in] IRQn: Interrupt number.
 * @return     intNumber: None
 */
uint32_t INT_GetPriority(IRQn_Type IRQn)
{
    uint32_t intNumber = 0U;

    if ((int32_t)(IRQn) >= 0)
    {
        intNumber = ((uint32_t)NVICRegPtr->IP[((uint32_t)IRQn)] \
             >> (8U - INT_PRIO_BITS));
    }
    else
    {
        /*PRQA S 2896 ++*/
        intNumber = ((uint32_t)SCBRegPtr->SHP[(((uint32_t)IRQn) \
            & 0xFU)-4U] >> (8U - INT_PRIO_BITS));
        /*PRQA S 2896 --*/
    }

    return (intNumber);
}

/**
 * @brief        Set Interrupt Vector
 * @param[in]    IRQn: Interrupt number
 * @param[in]    vector: Interrupt handler address
 * @return       None
 */
void INT_SetVector(IRQn_Type IRQn, uint32_t vector)
{  
    /*PRQA S 0306 ++*/
    uint32_t *vectors = (uint32_t *)SCBRegPtr->VTOR;
    /*PRQA S 0306 --*/

    vectors[(int32_t)IRQn + NVIC_DEVICE_IRQ_OFFSET] = vector;
}

/**
 * @brief        Get Interrupt Vector
 * @param[in]    IRQn: Interrupt number.
 * @return       Interrupt handler address.
 */
uint32_t INT_GetVector(IRQn_Type IRQn)
{
    /*PRQA S 0306 ++*/
    uint32_t *vectors = (uint32_t *)SCBRegPtr->VTOR;
    /*PRQA S 0306 --*/

    return vectors[(int32_t)IRQn + NVIC_DEVICE_IRQ_OFFSET];
}

/**
 * @brief       SYSTICK config and enable
 * @param[in]   None
 * @return      result: Function status.
 *              0U: Success
 *              1U: Fail
 */
uint32_t SysTick_Config(uint32_t ticks)
{
    uint32_t result = 0U;

    if ((ticks - 1U) > (0xFFFFFFU))
    {
        result = 1U;
    }
    else
    {
        /* Set reload register */
        SysTickPtr->LOAD  = (uint32_t)(ticks - 1U); 
        /* Set Priority */   
        INT_SetPriority(SysTick_IRQn, (1U << INT_PRIO_BITS) - 1U);
        /* Load Counter Value */
        SysTickPtr->VAL = 0U;  
        /* Enable SysTick IRQ and Start Timer */                                           
        SysTickPtr->CTRL = (1U << 2U) | (1U << 1U) | (1U);
    }

    return (result);
}

/** @} end of group INT_Public_Functions */

/** @} end of group INT */

/** @} end of group Z20K14XM_Peripheral_Driver */

