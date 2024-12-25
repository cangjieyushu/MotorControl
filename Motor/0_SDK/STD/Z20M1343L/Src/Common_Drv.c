/**************************************************************************************************/
/**
 * @file      : Common_Drv.c
 * @brief     : Common module driver file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#include "Common_Drv.h"

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
 *  @brief COMMON Register address array
 */
/*PRQA S 0306 ++*/
static Z20_SCBType * const Common_Z20ScbRegPtr = (Z20_SCBType *)Z20_SCB_BASE;
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
 * @brief      Delay for cycles
 *
 * @param[in]  DelayCount: the cycles to delay
 *
 * @return     None
 */
void Common_Delay(uint32 DelayCount)      /*PRQA S 3408*/
{
    volatile uint32 Count = 0U;

    while(Count++ < DelayCount)
    {
    }
}

/**
 * @brief      Convert 4 byte into a word. The first byte is the lowest byte in 
 *             the word(little end).
 *
 * @param[in]  Bytes: It points to an array with 4 bytes.
 *
 * @return     Result: Word value
 */
uint32 Common_ConvertBytesToWord(uint8 Bytes[4])
{
    volatile uint32 Result;

    Result = Bytes[0] | ((uint32)Bytes[1] << 8U) | ((uint32)Bytes[2] << 16U)
             | ((uint32)Bytes[3] << 24U);

    return (Result);
}

/**
 * @brief      Software system reset.
 * @param[in]  None.
 * @return     None.
 */
void Common_SwResetSystem(void)
{
    volatile uint8 WaitReset = 1U;

    /* Ensure completion of memory access before reset config*/
    COMMON_DSB(); 

    Common_Z20ScbRegPtr->AIRCR  = (uint32)((0x5FAUL << 16U) | \
        (Common_Z20ScbRegPtr->AIRCR & (7UL << 8U)) |(1UL << 2U));

    /* Ensure completion of memory access */
    COMMON_DSB();

    /* wait for reset */
    while(WaitReset != 0U)
    {
        COMMON_NOP();
    }
}

/**
 * @brief      Config privileged mode in CONTROL register.
 * @param[in]  Mode: Select privileged or unprivileged mode.
 *             0: privileged
 *             1: unprivileged
 * @return     None.
 */
void Common_SetPrivilegeMode(const uint8 Mode)
{
    __asm volatile("PUSH {R0,R1,R2}");
    __asm volatile("MOV R0, %0" : :"r"( Mode & 0x1));
    __asm volatile(
        "MRS R1, CONTROL\n"
        "MOVS R2, #0x1\n"

#if defined ( __ICCARM__ )
        "BICS R1,R1,R2\n"
        "ORRS R1,R1,R0\n"
#elif defined ( __ARMCC_VERSION )
        "BICS R1,R1,R2\n"
        "ORRS R1,R1,R0\n"
#elif defined ( __GNUC__ )
        "BIC R1,R1,R2\n"
        "ORR R1,R1,R0\n"
#elif defined ( __ghs__ )
        "BIC R1,R1,R2\n"
        "ORR R1,R1,R0\n"
#else
    #error "Unsupported compiler."
#endif /* __ICCARM__ */

        "MSR CONTROL, R1\n"
      );
    __asm volatile("POP {R0,R1,R2}");
}

/** @} end of group Public_FunctionDefinition */
