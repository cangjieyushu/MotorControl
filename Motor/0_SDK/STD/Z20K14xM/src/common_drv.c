/**************************************************************************************************/
/**
 * @file     common_drv.c
 * @brief    Common driver file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @defgroup COMMON_DRV
 *  @brief Z20K14X driver common functions
 *  @{
 */

/** @defgroup COMMON_Private_Type
 *  @{
 */

/** @} end of group COMMON_Private_Type*/

/** @defgroup COMMON_Private_Defines
 *  @{
 */

/** @} end of group COMMON_Private_Defines */


/** @defgroup COMMON_Private_Variables
 *  @{
 */

/** @} end of group COMMON_Private_Variables */

/** @defgroup COMMON_Global_Variables
 *  @{
 */

/**
 *  @brief COMMON Register address array
 */
/*PRQA S 0306 ++*/
static Z20_SCBType * const z20ScbRegPtr = (Z20_SCBType *)Z20_SCB_BASE;
static Z20_FPUType * const z20FpuRegPtr = (Z20_FPUType *)Z20_FPU_BASE;
/*PRQA S 0306 --*/

/** @} end of group COMMON_Global_Variables */


/** @defgroup COMMON_Private_FunctionDeclaration
 *  @{
 */


/** @} end of group COMMON_Private_FunctionDeclaration */

/** @defgroup COMMON_Private_Functions
 *  @{
 */

/** @} end of group COMMON_Private_Functions */

/** @defgroup COMMON_Public_Functions
 *  @{
 */
/**
 * @brief      Delay for some cycles
 *
 * @param[in]  delayCount: the cycles to delay
 *
 * @return     None
 *
 */
void COMMON_Delay(uint32_t delayCount)      /*PRQA S 3408*/
{
    volatile uint32_t count = 0U;

    while(count++ < delayCount)
    {
    }
}

/**
 * @brief      Convert 4 byte into a word. The first byte is the lowest byte in 
 *             the word(little end).
 *
 * @param[in]  bytes: it points to an array with 4 bytes.
 *
 * @return     None
 *
 */
uint32_t COMMON_BytesToWord(uint8_t bytes[4])
{
    volatile uint32_t result;

    result = bytes[0] | ((uint32_t)bytes[1] << 8U) | ((uint32_t)bytes[2] << 16U)
             | ((uint32_t)bytes[3] << 24U);

    return (result);
}

/**
 * @brief      System reset.
 * @param[in]  None.
 * @return     None.
 */
void COMMON_SystemReset(void)
{
    volatile uint8_t waitReset = 1U;
    
    /* Ensure completion of memory access before reset config*/   
    COMMON_DSB(); 

    z20ScbRegPtr->AIRCR  = (uint32_t)((0x5FAUL << 16U) | (z20ScbRegPtr->AIRCR & (7UL << 8U)) |(1UL << 2U));
    /* Ensure completion of memory access */
    COMMON_DSB();

    /* wait for reset */
    while((bool)waitReset)
    {
        COMMON_NOP();
    }
}

/**
 * @brief      Config privileged mode in CONTROL register.
 * @param[in]  mode: 
 *             0:   privileged
 *             1:   unprivileged
 * @return     None.
 */
void COMMON_SetCONTROL(const uint8_t mode)
{
    uint32_t tmp0 = 0U;
    uint32_t tmp1 = 0U;
    tmp0 = (mode & (uint32_t)0x1);
    __asm volatile("MRS %0, CONTROL": "=r"(tmp1));
    tmp1 &= (~((uint32_t)0x1));
    tmp1 |= tmp0;
    __asm volatile("MSR CONTROL, %0" : :"r"(tmp1));
    (void)tmp1;
}

/**
 * @brief     Get FPU type
 * @param[in] None
 * @return    result: FPU type id
                0: No FPU
                1: Single precision FPU
 */
uint32_t COMMON_GetFPUType(void)
{
    volatile uint32_t mvfr0Reg = 0U;
    volatile uint32_t result = 0U;

    mvfr0Reg = z20FpuRegPtr->MVFR0;
    if (0x020U == (mvfr0Reg & ((0xFUL << 4U) | (0xFUL << 8U))))
    {
        result =  1U;
    }
    else
    {
        result =  0U;
    }

    return (result);
}

/** @} end of group COMMON_Public_Functions */

/** @} end of group COMMON_DRV */

/** @} end of group Z20K14XM_Peripheral_Driver */
