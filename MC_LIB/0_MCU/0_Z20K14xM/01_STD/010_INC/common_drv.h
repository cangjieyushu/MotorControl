/**************************************************************************************************/
/**
 * @file     common_drv.h
 * @brief    Drv common module header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#ifndef COMMON_DRV_H
#define COMMON_DRV_H

#include "device_regs.h"
#include "platform_cfg.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  COMMON_DRV
 *  @{
 */

/** @addtogroup  COMMON_Public_Macro
 *  @{
 */

/** 
 * @brief Core Configuration
 */
#define CM4_REV                 (0x0001U) /*!< core version */
#define FPU_PRESENT             (1U)      /*!< FPU present or not*/
#define INT_PRIO_BITS           (4U)      /*!< Number of Bits used for Priority Levels */

/** 
 * @brief PMU register unlock sequence
 */
#define PMU_UNLOCK_SEQUENCE   (0x94730000UL)

/** 
 * @brief Compiler specific basic keyword and ramsection configuration
 */
/**************************************** IAR *************************************************/
#if defined ( __ICCARM__ )
    /**
     * @brief Compiler abstraction for "Put in Quotes".
     */
    #define SDK_PUT_IN_QUOTES(x) #x

    /**
     * @brief Compiler abstraction for the asm keyword.
     */
    #define ASM_KEYWORD  __asm

    /**
     * @brief Compiler abstraction for the asm keyword.
     */
    #define ASMV_KEYWORD  __asm volatile

    /**
     * @brief Compiler abstraction for packed
     */
    #define PACKED __packed

    /**
     * @brief Compiler abstraction for the data alignment
     */
    #define ALIGNED_VARS_START(sec_name, align) 
    #define VAR_ALIGN(v, size)  _Pragma(SDK_PUT_IN_QUOTES(data_alignment=size)) v;
    #define ALIGNED_VARS_STOP()

    /**
     * @brief the INLINE define for abstraction of the keyword inline.
     */
    #define INLINE inline

    /**
     * @brief the LOCAL_INLINE define for abstraction of the keyword inline in functions with
     *        "static" scope
     */
    #define LOCAL_INLINE static inline

    /**
     * @brief Compiler abstraction for specifying an interrupt handler.
     */
    #define INTERRUPT_FUNC

    /*
     * @brief Compiler ramsection configuration.
     */
    #define START_FUNCTION_DECLARATION_RAMSECTION      __ramfunc
    #define END_FUNCTION_DECLARATION_RAMSECTION     ;

    #define DISABLE_CHECK_RAMSECTION_FUNCTION_CALL     _Pragma("diag_suppress=Ta022")
    #define ENABLE_CHECK_RAMSECTION_FUNCTION_CALL      _Pragma("diag_default=Ta022")

/**************************************** ARMCC *************************************************/
#elif defined ( __ARMCC_VERSION )
    /**
     * @brief Compiler abstraction for "Put in Quotes".
     */
    #define SDK_PUT_IN_QUOTES(x) #x
     
    /**
     * @brief Compiler abstraction for the asm keyword.
     */    
    #define ASM_KEYWORD  __asm

    /**
     * @brief Compiler abstraction for the asm keyword.
     */
    #define ASMV_KEYWORD  __asm volatile

    /**
     * @brief Compiler abstraction for packed
     */
    #define PACKED __attribute__((__packed__))

    /**
     * @brief Compiler abstraction for the data alignment
     */
    #define ALIGNED_VARS_START(sec_name, align) 
    #define VAR_ALIGN(v, size) __attribute__(( aligned(size) )) v;
    #define ALIGNED_VARS_STOP() 

    /**
     * @brief the INLINE define for abstraction of the keyword inline.
     */
    #define INLINE inline

    /**
     * @brief the LOCAL_INLINE define for abstraction of the keyword inline in functions with
     *        "static" scope
     */
    #define LOCAL_INLINE static inline

    /**
     * @brief Compiler abstraction for specifying an interrupt handler.
     */
    #define INTERRUPT_FUNC

    /*
     * @brief Compiler ramsection configuration.
     */
    #define START_FUNCTION_DECLARATION_RAMSECTION
    #define END_FUNCTION_DECLARATION_RAMSECTION        __attribute__((section (".code_ram")));

    #define DISABLE_CHECK_RAMSECTION_FUNCTION_CALL
    #define ENABLE_CHECK_RAMSECTION_FUNCTION_CALL

/**************************************** GCC *************************************************/
#elif defined ( __GNUC__ )
    /**
     * @brief Compiler abstraction for "Put in Quotes".
     */
    #define SDK_PUT_IN_QUOTES(x) #x
     
    /**
     * @brief Compiler abstraction for the asm keyword.
     */    
    #define ASM_KEYWORD  __asm

    /**
     * @brief Compiler abstraction for the asm keyword.
     */
    #define ASMV_KEYWORD  __asm volatile

    /**
     * @brief Compiler abstraction for packed
     */
    #define PACKED __attribute__((__packed__))

    /**
     * @brief Compiler abstraction for the data alignment
     */
    #define ALIGNED_VARS_START(sec_name, align) 
    #define VAR_ALIGN(v, size) __attribute__(( aligned(size) )) v;
    #define ALIGNED_VARS_STOP() 

    /**
     * @brief the INLINE define for abstraction of the keyword inline.
     */
    #define INLINE inline

    /**
     * @brief the LOCAL_INLINE define for abstraction of the keyword inline in functions with
     *        "static" scope
     */
    #define LOCAL_INLINE static inline

    /**
     * @brief Compiler abstraction for specifying an interrupt handler.
     */
    #define INTERRUPT_FUNC

    /*
     * @brief Compiler ramsection configuration.
     */
    #define START_FUNCTION_DECLARATION_RAMSECTION
    #define END_FUNCTION_DECLARATION_RAMSECTION        __attribute__((section (".code_ram")));

    #define DISABLE_CHECK_RAMSECTION_FUNCTION_CALL
    #define ENABLE_CHECK_RAMSECTION_FUNCTION_CALL

/************************************* Green Hills ******************************************/
#elif defined ( __ghs__ )
    /**
     * @brief Compiler abstraction for "Put in Quotes".
     */
    #define SDK_PUT_IN_QUOTES(x) #x

    /**
     * @brief Compiler abstraction for the asm keyword.
     */    
    #define ASM_KEYWORD  __asm

    /**
     * @brief Compiler abstraction for the asm keyword.
     */
    #define ASMV_KEYWORD  __asm volatile

    /**
     * @brief Compiler abstraction for the data alignment
     */
    #define ALIGNED_VARS_START(sec_name, align) 
    #define VAR_ALIGN(v, size) __attribute__(( aligned(size) )) v;
    #define ALIGNED_VARS_STOP() 

    /**
     * @brief Compiler abstraction for packed
     */
    #define PACKED __packed

    /**
     * @brief the INLINE define for abstraction of the keyword inline.
     */
    #define INLINE __inline

    /**
     * @brief the LOCAL_INLINE define for abstraction of the keyword inline in functions with
     *        "static" scope
     */
    #define LOCAL_INLINE static __inline

    /**
     * @brief Compiler abstraction for specifying an interrupt handler.
     */
    #define INTERRUPT_FUNC __interrupt

    /*
     * @brief Compiler ramsection configuration.
     */
    #define START_FUNCTION_DECLARATION_RAMSECTION      _Pragma("ghs callmode=far")
    #define END_FUNCTION_DECLARATION_RAMSECTION        __attribute__((section (".code_ram")));\
                                                       _Pragma("ghs callmode=default")

    #define DISABLE_CHECK_RAMSECTION_FUNCTION_CALL
    #define ENABLE_CHECK_RAMSECTION_FUNCTION_CALL
#else
    #error "Unsupported compiler."
#endif /* __ICCARM__ */

/**
 * @brief Core register mask
 */
#define SCB_SCR_SLEEPDEEP_POS               (2U)                                           /*!< SCB SCR: SLEEPDEEP Position */
#define SCB_SCR_SLEEPDEEP_MASK              (1UL << SCB_SCR_SLEEPDEEP_POS)                 /*!< SCB SCR: SLEEPDEEP Mask */

/**
 * @brief DSB instruction
 */
#define COMMON_DSB()    ASMV_KEYWORD("DSB")

/**
 * @brief ISB instruction
 */
#define COMMON_ISB()    ASMV_KEYWORD("ISB")

/**
 * @brief DMB instruction
 */
#define COMMON_DMB()    ASMV_KEYWORD("DMB")

/**
 * @brief NOP instruction
 */
#define COMMON_NOP()    ASMV_KEYWORD("NOP")

/**
 * @brief Wait for interrupt
 */
#define COMMON_WFI()    ASMV_KEYWORD("WFI")

/**
 * @brief Wait for event
 */
#define COMMON_WFE()    ASMV_KEYWORD("WFE")

/**
 * @brief Enable interrupt
 */
#define COMMON_ENABLE_INTERRUPTS() ASMV_KEYWORD("CPSIE I" : : : "memory")

/**
 * @brief Disable interrupt
 */
#define COMMON_DISABLE_INTERRUPTS() ASMV_KEYWORD("CPSID I" : : : "memory")

/**
 * @brief Enable fault interrupt
 */
#define COMMON_ENABLE_FAULT_INTERRUPR() ASMV_KEYWORD("CPSIE F" : : : "memory")

/**
 * @brief Disable fault interrupt
 */
#define COMMON_DISABLE_FAULT_INTERRUPR() ASMV_KEYWORD("CPSID F" : : : "memory")

/**
 * @brief If it is interrupt mask macro
 */
#define IS_INTMASK(INTMASK)     (((INTMASK) == MASK) || ((INTMASK) == UNMASK))

/** @} end of group COMMON_Public_Macro */

/** @defgroup COMMON_Public_Types
 *  @brief DRV type definition
 *  @{
 */

/**
 * @brief Control State Type Definition
 */
typedef enum
{
    DISABLE  = 0U,
    ENABLE   = 1U
}ControlState_t;

/**
 * @brief Result status Type definition
 */
typedef enum
{
    SUCC = 0U,
    ERR = 1U,
    BUSY = 2U
}ResultStatus_t;

/**
 * @brief Flag/Int status Type definition
 */
typedef enum
{
    RESET = 0U,
    SET = 1U
}FlagStatus_t, IntStatus_t;

/**
 * @brief interrupt mask Type definition
 */
typedef enum
{
    UNMASK = 0U,
    MASK = 1U
}IntMask_t;

/**
 * @brief level Type definition
 */
typedef enum
{
    LEVEL_LOW = 0U,
    LEVEL_HIGH = 1U
}Level_t;

/**
 *  @brief ISR callback function type
 */
typedef void (isr_cb_t)(void);

/** @} end of group COMMON_Public_Types */

/** @defgroup COMMON_Public_Constants
 *  @{
 */

/** @} end of group COMMON_Public_Constants */

/** @defgroup COMMON_Public_Macro
 *  @{
 */

/** @} end of group COMMON_Public_Macro */

/** @defgroup COMMON_Public_FunctionDeclaration
 *  @brief DRV functions declaration
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
#if( COMMON_DELAY_FUNC_IN_RAM == 1)
START_FUNCTION_DECLARATION_RAMSECTION
void COMMON_Delay(uint32_t delayCount)
END_FUNCTION_DECLARATION_RAMSECTION        /*PRQA S 0605*/
#else
void COMMON_Delay(uint32_t delayCount);
#endif

/**
 * @brief      Convert 4 byte into a word. The first byte is the lowest byte in 
 *             the word(little end).
 *
 * @param[in]  bytes: it points to an array with 4 bytes.
 *
 * @return     None
 *
 */
uint32_t COMMON_BytesToWord(uint8_t bytes[4]);

/**
 * @brief      System reset.
 * @param[in]  None.
 * @return     None.
 */
void COMMON_SystemReset(void);

/**
 * @brief      Config privileged mode in CONTROL register.
 * @param[in]  mode: 
 *             0:   privileged
 *             1:   unprivileged
 * @return     None.
 */
void COMMON_SetCONTROL(const uint8_t mode);

/**
 * @brief     Get FPU type
 * @param[in] None
 * @return    result: FPU type id
                0: No FPU
                1: Single precision FPU
 */
uint32_t COMMON_GetFPUType(void);

/**
 * @brief      Get CONTROL register value
 * @param[in]  None
 * @return     result: CONTROL register value
 */
LOCAL_INLINE uint32_t COMMON_GetCONTROL(void)
{
    volatile uint32_t result;

    ASMV_KEYWORD("MRS %0, CONTROL" : "=r" (result) );

    return (result);
}

/**
 * @brief      Get IPSR register value
 * @param[in]  None
 * @return     result: IPSR register value
 */
LOCAL_INLINE uint32_t COMMON_GetIPSR(void)
{
    volatile uint32_t result;

    ASMV_KEYWORD("MRS %0, IPSR" : "=r" (result) );

    return (result);
}

/**
 * @brief     Get APSR register value
 * @param[in] None
 * @return    result: APSR register value
 */
LOCAL_INLINE uint32_t COMMON_GetAPSR(void)
{
    volatile uint32_t result;

    ASMV_KEYWORD("MRS %0, APSR" : "=r" (result) );

    return (result);
}

/**
 * @brief     Get xPSR register value
 * @param[in] None
 * @return    result: xPSR register value
 */
LOCAL_INLINE uint32_t COMMON_GetxPSR(void)
{
    volatile uint32_t result;

    ASMV_KEYWORD("MRS %0, XPSR" : "=r" (result) );

    return (result);
}

/**
 * @brief     Get PSP register value
 * @param[in] None
 * @return    result: PSP register value
 */
LOCAL_INLINE uint32_t COMMON_GetPSP(void)
{
    volatile uint32_t result;

    ASMV_KEYWORD("MRS %0, PSP"  : "=r" (result) );

    return (result);
}

/**
 * @brief     Set PSP register value
 * @param[in] value:  Process stack pointer value to set
 * @return    None
 */
LOCAL_INLINE void COMMON_SetPSP(uint32_t value)
{
    ASMV_KEYWORD("MSR PSP, %0" : : "r" (value) : );
}

/**
 * @brief     Get MSP register value
 * @param[in] None
 * @return    result: MSP register value
 */
LOCAL_INLINE uint32_t COMMON_GetMSP(void)
{
    volatile uint32_t result;

    ASMV_KEYWORD("MRS %0, MSP" : "=r" (result) );

    return (result);
}

/**
 * @brief     Set MSP register
 * @param[in] value:  Main stack pointer value to set
 * @return    None
 */
LOCAL_INLINE void COMMON_SetMSP(uint32_t value)
{
    ASMV_KEYWORD("MSR MSP, %0" : : "r" (value) : );
}

/**
 * @brief      Get the PRIMASK register value.
 * @param[in]  None
 * @return     result: PRIMASK value.
 */
LOCAL_INLINE uint32_t COMMON_GetPRIMASK(void)
{
    volatile uint32_t result;

    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(result));

    return (result);
}

/**
 * @brief      Set PRIMASK register
 * @param[in]  value:  Priority mask value to set
 * @return     None
 */
LOCAL_INLINE void COMMON_SetPRIMASK(uint32_t value)
{
    ASMV_KEYWORD("MSR PRIMASK, %0" : : "r" (value) : "memory");
}

/**
 * @brief     Get BASEPRI register value
 * @param[in] None
 * @return    result: BASEPRI register value.
 */
LOCAL_INLINE uint32_t COMMON_GetBASEPRI(void)
{
    volatile uint32_t result;

    ASMV_KEYWORD("MRS %0, BASEPRI" : "=r" (result) );

    return (result);
}

/**
 * @brief     Set BASEPRI register
 * @param[in] value: BASEPRI value to set.
 * @return    None
 */
LOCAL_INLINE void COMMON_SetBASEPRI(uint32_t value)
{
    ASMV_KEYWORD("MSR BASEPRI, %0" : : "r" (value) : "memory");
}

/**
 * @brief     Set BASEPRI_MAX register
 * @param[in] value: BASEPRI_MAX value to set.
 * @return    None
 */
LOCAL_INLINE void COMMON_SetBASEPRIMAX(uint32_t value)
{
    ASMV_KEYWORD("MSR BASEPRI_MAX, %0" : : "r" (value) : "memory");
}

/**
 * @brief     Get FAULTMASK register value
 * @param[in] None
 * @return    result: FAULTMASK register value
 */
LOCAL_INLINE uint32_t COMMON_GetFAULTMASK(void)
{
    volatile uint32_t result;

    ASMV_KEYWORD("MRS %0, FAULTMASK" : "=r" (result) );

    return (result);
}

/**
 * @brief     Set FAULTMASK register
 * @param[in] value: FAULTMASK value to set.
 * @return    None
 */
LOCAL_INLINE void COMMON_SetFAULTMASK(uint32_t value)
{
    ASMV_KEYWORD("MSR FAULTMASK, %0" : : "r" (value) : "memory");
}

/**
 * @brief     Get FPSCR register value
 * @param[in] None
 * @return    result: Floating point status/control register value
 */
LOCAL_INLINE uint32_t COMMON_GetFPSCR(void)
{
#if ((FPU_PRESENT == 1U) && (FPU_USED == 1U))

    volatile uint32_t result;

    ASMV_KEYWORD("VMRS %0, FPSCR" : "=r" (result) );

    return (result);
#else
    return (0U);
#endif
}

/** @} end of group COMMON_Public_FunctionDeclaration */

/** @} end of group COMMON_DRV  */

/** @} end of group Z20K14XM_Peripheral_Driver */

#endif /* COMMON_DRV_H */
