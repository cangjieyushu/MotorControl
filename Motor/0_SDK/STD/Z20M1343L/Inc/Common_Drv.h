/**************************************************************************************************/
/**
 * @file      : Common_Drv.h
 * @brief     : Common module driver header file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
#ifndef COMMON_DRV_H
#define COMMON_DRV_H

#include "Device_Regs.h"
#include "Platform_Cfg.h"

/** @addtogroup Public_MacroDefinition
 *  @{
 */

/** 
 * @brief Compiler specific basic keyword and ramsection configuration
 */
/**************************************** IAR *************************************************/
#if defined ( __ICCARM__ )
    /**
     * @brief Compiler abstraction for "Put in Quotes".
     */
    #define SDK_PUT_IN_QUOTES(x) (#x)

    /**
     * @brief Compiler abstraction for the asm keyword.
     */
    #define ASM_KEYWORD  __asm

    /**
     * @brief Compiler abstraction for the asm volatile keyword.
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
    #define VAR_ALIGN(v, size)  _Pragma(SDK_PUT_IN_QUOTES(data_alignment=(size))) (v);
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
    #define SDK_PUT_IN_QUOTES(x) (#x)
     
    /**
     * @brief Compiler abstraction for the asm keyword.
     */    
    #define ASM_KEYWORD  __asm

    /**
     * @brief Compiler abstraction for the asm volatile keyword.
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
    #define VAR_ALIGN(v, size) __attribute__(( aligned(size) )) (v);
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
    #define SDK_PUT_IN_QUOTES(x) (#x)
     
    /**
     * @brief Compiler abstraction for the asm keyword.
     */    
    #define ASM_KEYWORD  __asm

    /**
     * @brief Compiler abstraction for the asm volatile keyword.
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
    #define VAR_ALIGN(v, size) __attribute__(( aligned(size) )) (v);
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
    #define SDK_PUT_IN_QUOTES(x) (#x)

    /**
     * @brief Compiler abstraction for the asm keyword.
     */    
    #define ASM_KEYWORD  __asm

    /**
     * @brief Compiler abstraction for the asm volatile keyword.
     */
    #define ASMV_KEYWORD  __asm volatile

    /**
     * @brief Compiler abstraction for the data alignment
     */
    #define ALIGNED_VARS_START(sec_name, align) 
    #define VAR_ALIGN(v, size) __attribute__(( aligned(size) )) (v);
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
#define SCB_SCR_SLEEPDEEP_POS     (2U)                           /*!< SCB SCR: SLEEPDEEP Position */
#define SCB_SCR_SLEEPDEEP_MASK    (1UL << SCB_SCR_SLEEPDEEP_POS) /*!< SCB SCR: SLEEPDEEP Mask */

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
#define COMMON_IS_INTMASK(INTMASK)     (((INTMASK) == MASK) || ((INTMASK) == UNMASK))
/** @} end of Public_MacroDefinition */

/** @defgroup Public_TypeDefinition
 *  @{
 */

/**
 * @brief Control state type definition
 */
typedef enum
{
    COMMON_DISABLE  = 0U,   /*!< Disable state */
    COMMON_ENABLE   = 1U    /*!< Enable state */
} Common_ControlStateType;

/**
 * @brief Result state type definition
 */
typedef enum
{
    COMMON_SUCC = 0U,       /*!< Success state */
    COMMON_ERR = 1U,        /*!< Error state */
    COMMON_BUSY = 2U        /*!< Busy state */
} Common_ResultStatusType;

/**
 * @brief Flag/Int status type definition
 */
typedef enum
{
    COMMON_RESET = 0U,      /*!< Reset state */
    COMMON_SET = 1U         /*!< Set state */
} Common_FlagStatusType, Common_IntStatusType;

/**
 * @brief Interrupt mask type definition
 */
typedef enum
{
    COMMON_UNMASK = 0U,     /*!< Interrupt unmask */
    COMMON_MASK = 1U        /*!< Interrupt mask */
} Common_IntMaskType;

/**
 * @brief Level type definition
 */
typedef enum
{
    COMMON_LEVEL_LOW = 0U,  /*!< Pad level low */
    COMMON_LEVEL_HIGH = 1U  /*!< Pad level high */
} Common_LevelType;

/** @} end of group Public_TypeDefinition */

/** @defgroup Global_VariableDeclaration
 *  @{
 */

/** @} end of group Global_VariableDeclaration */

/** @defgroup Public_FunctionDeclaration
 *  @{
 */

/**
 * @brief      Delay for some cycles
 *
 * @param[in]  DelayCount: the cycles to delay
 *
 * @return     None
 */
#if( 1U == COMMON_DELAY_FUNC_IN_RAM )
START_FUNCTION_DECLARATION_RAMSECTION
void Common_Delay(uint32 DelayCount)
END_FUNCTION_DECLARATION_RAMSECTION        /*PRQA S 0605*/
#else
void Common_Delay(uint32 DelayCount);
#endif

/**
 * @brief      Convert 4 byte into a word. The first byte is the lowest byte in 
 *             the word(little end).
 *
 * @param[in]  Bytes: It points to an array with 4 bytes.
 *
 * @return     Result: Word value
 */
uint32 Common_ConvertBytesToWord(uint8 Bytes[4]);

/**
 * @brief      Software system reset.
 * @param[in]  None.
 * @return     None.
 */
void Common_SwResetSystem(void);

/**
 * @brief      Config privileged mode in CONTROL register.
 * @param[in]  Mode: Select privileged or unprivileged mode.
 *             0:   privileged
 *             1:   unprivileged
 * @return     None.
 */
void Common_SetPrivilegeMode(const uint8 Mode);

/**
 * @brief      Get CONTROL register value
 * @param[in]  None
 * @return     Result: CONTROL register value
 */
LOCAL_INLINE uint32 Common_GetControl(void)
{
    volatile uint32 Result = 0U;

    ASMV_KEYWORD("MRS %0, CONTROL" : "=r" (Result));

    return (Result);
}

/**
 * @brief      Get IPSR register value
 * @param[in]  None
 * @return     Result: IPSR register value
 */
LOCAL_INLINE uint32 Common_GetIpsr(void)
{
    volatile uint32 Result = 0U;

    ASMV_KEYWORD("MRS %0, IPSR" : "=r" (Result));

    return (Result);
}

/**
 * @brief     Get APSR register value
 * @param[in] None
 * @return    Result: APSR register value
 */
LOCAL_INLINE uint32 Common_GetApsr(void)
{
    volatile uint32 Result = 0U;

    ASMV_KEYWORD("MRS %0, APSR" : "=r" (Result));

    return (Result);
}

/**
 * @brief     Get xPSR register value
 * @param[in] None
 * @return    Result: xPSR register value
 */
LOCAL_INLINE uint32 Common_GetXpsr(void)
{
    volatile uint32 Result = 0U;

    ASMV_KEYWORD("MRS %0, XPSR" : "=r" (Result));

    return (Result);
}

/**
 * @brief     Get PSP register value
 * @param[in] None
 * @return    Result: PSP register value
 */
LOCAL_INLINE uint32 Common_GetPsp(void)
{
    volatile uint32 Result = 0U;

    ASMV_KEYWORD("MRS %0, PSP"  : "=r" (Result));

    return (Result);
}

/**
 * @brief     Set PSP register value
 * @param[in] Value:  Process stack pointer value to set
 * @return    None
 */
LOCAL_INLINE void Common_SetPsp(uint32 Value)
{
    ASMV_KEYWORD("MSR PSP, %0" : : "r" (Value) : );
}

/**
 * @brief     Get MSP register value
 * @param[in] None
 * @return    Result: MSP register value
 */
LOCAL_INLINE uint32 Common_GetMsp(void)
{
    volatile uint32 Result = 0U;

    ASMV_KEYWORD("MRS %0, MSP" : "=r" (Result));

    return (Result);
}

/**
 * @brief     Set MSP register
 * @param[in] Value:  Main stack pointer value to set
 * @return    None
 */
LOCAL_INLINE void Common_SetMsp(uint32 Value)
{
    ASMV_KEYWORD("MSR MSP, %0" : : "r" (Value) : );
}

/**
 * @brief      Get the PRIMASK register value.
 * @param[in]  None
 * @return     result: PRIMASK value.
 */
LOCAL_INLINE uint32 Common_GetPrimask(void)
{
    volatile uint32 Result = 0U;

    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Result));

    return (Result);
}

/**
 * @brief      Set PRIMASK register
 * @param[in]  Value:  Priority mask value to set
 * @return     None
 */
LOCAL_INLINE void Common_SetPrimask(uint32 Value)
{
    ASMV_KEYWORD("MSR PRIMASK, %0" : : "r" (Value) : "memory");
}

/**
 * @brief     Get BASEPRI register value
 * @param[in] None
 * @return    Result: BASEPRI register value.
 */
LOCAL_INLINE uint32 Common_GetBasepri(void)
{
    volatile uint32 Result = 0U;

    ASMV_KEYWORD("MRS %0, BASEPRI" : "=r" (Result));

    return (Result);
}

/**
 * @brief     Set BASEPRI register
 * @param[in] value: BASEPRI value to set.
 * @return    None
 */
LOCAL_INLINE void Common_SetBasepri(uint32 Value)
{
    ASMV_KEYWORD("MSR BASEPRI, %0" : : "r" (Value) : "memory");
}

/**
 * @brief     Set BASEPRI_MAX register
 * @param[in] Value: BASEPRI_MAX value to set.
 * @return    None
 */
LOCAL_INLINE void Common_SetBasepriMax(uint32 Value)
{
    ASMV_KEYWORD("MSR BASEPRI_MAX, %0" : : "r" (Value) : "memory");
}

/**
 * @brief     Get FAULTMASK register value
 * @param[in] None
 * @return    result: FAULTMASK register value
 */
LOCAL_INLINE uint32 Common_GetFaultmask(void)
{
    volatile uint32 Result = 0U;

    ASMV_KEYWORD("MRS %0, FAULTMASK" : "=r" (Result));

    return (Result);
}

/**
 * @brief     Set FAULTMASK register
 * @param[in] Value: FAULTMASK value to set.
 * @return    None
 */
LOCAL_INLINE void Common_SetFaultmask(uint32 Value)
{
    ASMV_KEYWORD("MSR FAULTMASK, %0" : : "r" (Value) : "memory");
}
/** @} end of group Public_FunctionDeclaration */

#endif /* COMMON_DRV_H */
