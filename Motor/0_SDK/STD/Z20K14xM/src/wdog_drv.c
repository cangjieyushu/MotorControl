/*******************************************************************************/
/**
 * @file     wdog_drv.c
 * @brief    WDOG module driver file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 *******************************************************************************/

#include "wdog_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @defgroup WDOG
 *  @brief WDOG driver modules
 *  @{
 */

/** @defgroup WDOG_Private_Defines
 *  @{
 */

#define WDOG_CS_INTF_MASK              (0x04000000U)
#define WDOG_CS_CFGUF_MASK             (0x01000000U)

#define WDOG_CS_TSTM_MASK              (0x00070000U)
#define WDOG_CS_CLKS_MASK              (0x00000300U)
#define WDOG_CS_CFGUA_MASK             (0x00000040U)
#define WDOG_CS_WINE_MASK              (0x00000020U)
#define WDOG_CS_INTE_MASK              (0x00000010U)
#define WDOG_CS_STOPE_MASK             (0x00000008U)
#define WDOG_CS_WAITE_MASK             (0x00000004U)
#define WDOG_CS_DEBUGE_MASK            (0x00000002U)
#define WDOG_CS_WDOGE_MASK             (0x00000001U)

#define WDOG_CS_INTF_SHIFT             (26U)
#define WDOG_CS_TSTM_SHIFT             (16U)
#define WDOG_CS_CLKS_SHIFT             (8U)
#define WDOG_CS_CFGUA_SHIFT            (6U)
#define WDOG_CS_WINE_SHIFT             (5U)
#define WDOG_CS_INTE_SHIFT             (4U)
#define WDOG_CS_STOPE_SHIFT            (3U)
#define WDOG_CS_WAITE_SHIFT            (2U)
#define WDOG_CS_DEBUGE_SHIFT           (1U)

#define WDOG_CS_TSTM_SET(x) \
        (((uint32_t)(((uint32_t)(x)) << WDOG_CS_TSTM_SHIFT))&WDOG_CS_TSTM_MASK)

#define WDOG_CS_CLKS_SET(x) \
        (((uint32_t)(((uint32_t)(x)) << WDOG_CS_CLKS_SHIFT))&WDOG_CS_CLKS_MASK)
        
#define WDOG_CS_CFGUA_SET(x) \
        (((uint32_t)(((uint32_t)(x)) << WDOG_CS_CFGUA_SHIFT))&WDOG_CS_CFGUA_MASK)
        
#define WDOG_CS_WINE_SET(x) \
        (((uint32_t)(((uint32_t)(x)) << WDOG_CS_WINE_SHIFT))&WDOG_CS_WINE_MASK)
        
#define WDOG_CS_STOPE_SET(x) \
        (((uint32_t)(((uint32_t)(x)) << WDOG_CS_STOPE_SHIFT))&WDOG_CS_STOPE_MASK)
        
#define WDOG_CS_WAITE_SET(x) \
        (((uint32_t)(((uint32_t)(x)) << WDOG_CS_WAITE_SHIFT))&WDOG_CS_WAITE_MASK)
        
#define WDOG_CS_DEBUGE_SET(x) \
        (((uint32_t)(((uint32_t)(x)) << WDOG_CS_DEBUGE_SHIFT))&WDOG_CS_DEBUGE_MASK)
        
#define WDOG_CS_INTE_SET(x) \
        (((uint32_t)(((uint32_t)(x)) << WDOG_CS_INTE_SHIFT))&WDOG_CS_INTE_MASK)
        
#define WDOG_UNLOCK_CONFIG_VALUE1     (0xB0D9A1C4UL)
#define WDOG_UNLOCK_CONFIG_VALUE2     (0x1A1E3B0FUL)
#define WDOG_REFRESH_VALUE1           (0xA0C4B1D6UL)
#define WDOG_REFRESH_VALUE2           (0x1E0D0C7BUL)

#define WDOG_MASK_CONVERT_ENABLE(x) \
        ((uint32_t)((((uint32_t)(x) + 1U) & 0x1U) << WDOG_CS_INTE_SHIFT))

START_FUNCTION_DECLARATION_RAMSECTION
static void WDOG_REFRESH_COUNT(void)
END_FUNCTION_DECLARATION_RAMSECTION    /* PRQA S 0605*/

/** @} end of group WDOG_Private_Defines */


/** @defgroup WDOG_Private_Type
 *  @{
 */

/** @} end of group WDOG_Private_Type*/



/** @defgroup WDOG_Private_Variables
 *  @{
 */

/**
 *  @brief WDOG Register address array
 */
/*PRQA S 0303 ++*/
static wdog_reg_t * const wdogRegPtr = (wdog_reg_t *)WDOG_BASE_ADDR;
static wdog_reg_w_t * const wdogRegWPtr = (wdog_reg_w_t *)WDOG_BASE_ADDR;
/*PRQA S 0303 --*/

/*! @brief wdog int status mask array */
static const uint32_t wdogIntMask[] = 
{
    WDOG_CS_INTE_MASK,
    WDOG_CS_INTE_MASK
};

static const uint32_t wdogIntFlagMask[] = 
{
    WDOG_CS_INTF_MASK,
    WDOG_CS_INTF_MASK
};

/*! @brief WDOG ISR CallBack VECTOR structure */
static isr_cb_t * wdogIsrCb[WDOG_INT_ALL] = {NULL};

/** @} end of group WDOG_Private_Variables */

/** @defgroup WDOG_Global_Variables
 *  @{
 */

/** @} end of group WDOG_Global_Variables */

/** @defgroup WDOG_Private_FunctionDeclaration
 *  @{
 */
void WDOG_DriverIRQHandler(void);
/** @} end of group WDOG_Private_FunctionDeclaration */

/** @defgroup WDOG_Private_Functions
 *  @{
 */
 
/**
 * @brief      wait until configuration update is completed Function
 *
 * @param[in]  none
 *
 * @return     wait operation status.
 *
 */
static inline ResultStatus_t WDOG_WaitConfigCompleted(void)
{
    wdog_reg_t * wDOGx = (wdog_reg_t *)(wdogRegPtr);
    
    volatile uint32_t uLoop = 0U;
    ResultStatus_t retVal = SUCC;
    
    while ((uint32_t)SET != wDOGx->WDOG_CS.CFGUF)
    {
        if (uLoop > WDOG_WAITCONFIG_GOING_CNT)
        {
            retVal = ERR;
            break;
        }

        uLoop++;
    }
    
    return retVal;
}

static void WDOG_REFRESH_COUNT(void)
{
    uint32_t Primask;
    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
    if (0U == Primask)
    {
        COMMON_DISABLE_INTERRUPTS();
    }
    __asm (
        "PUSH  {R0, R1, R2}\n"
        "LDR   R0, =0x40052014\n"
        "LDR   R1, =0xA0C4B1D6\n"
        "LDR   R2, =0x1E0D0C7B\n"

        "STR   R1, [R0]\n"
        "STR   R2, [R0]\n"
        "POP  {R0, R1, R2}\n"
            );
    if (0U == Primask)
    {
        COMMON_ENABLE_INTERRUPTS();
    }
}

static inline void WDOG_UNLOCK_CONFIG(void)
{
    __asm (
        "PUSH  {R0, R1, R2}\n"
        "LDR   R0, =0x40052014\n"
        "LDR   R1, =0xB0D9A1C4\n"
        "LDR   R2, =0x1A1E3B0F\n"

        "STR   R1, [R0]\n"
        "STR   R2, [R0]\n"
        "POP  {R0, R1, R2}\n"
            );
}

/** @} end of group WDOG_Private_Functions */

/** @defgroup WDOG_Public_Functions
 *  @{
 */

/**
 * @brief      wdog Initializes Function
 *
 * @param[in]  ptWDOGInitConfig:     Pointer to a WDOG configuration structure.
 *
 * @return     Initializes operate flag
 *
 */
ResultStatus_t WDOG_Init(const WDOG_Config_t * ptWDOGInitConfig)
{
    wdog_reg_t * wDOGx = (wdog_reg_t *)(wdogRegPtr);
    wdog_reg_w_t * wDOGxw = (wdog_reg_w_t *)(wdogRegWPtr);
    ResultStatus_t retVal = SUCC;
    uint32_t wdog_cs = wDOGxw->WDOG_CS;
    uint32_t Primask;

    if (0U == wDOGx->WDOG_CS.CFGUA)
    {
        retVal = ERR;
    }

    if (SUCC == retVal)
    {
        /* Clear the bits used for configuration */
        wdog_cs &= ~(WDOG_CS_TSTM_MASK | WDOG_CS_CLKS_MASK | WDOG_CS_WINE_MASK | 
                     WDOG_CS_STOPE_MASK | WDOG_CS_WAITE_MASK | WDOG_CS_DEBUGE_MASK);
        
        /* Construct CS register new value */
        wdog_cs |= WDOG_CS_TSTM_SET(ptWDOGInitConfig->testMode);
        wdog_cs |= WDOG_CS_CLKS_SET(ptWDOGInitConfig->clkSource);
        wdog_cs |= WDOG_CS_WINE_SET(ptWDOGInitConfig->winEnable);
        wdog_cs |= WDOG_CS_STOPE_SET(ptWDOGInitConfig->stop);
        wdog_cs |= WDOG_CS_WAITE_SET(ptWDOGInitConfig->wait);
        wdog_cs |= WDOG_CS_DEBUGE_SET(ptWDOGInitConfig->debug);
        ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
        if (0U == Primask)
        {
            COMMON_DISABLE_INTERRUPTS();
        }
        /* unlock config update */
        WDOG_UNLOCK_CONFIG();
        wDOGxw->WDOG_CS = wdog_cs;
        retVal = WDOG_WaitConfigCompleted();
        if (SUCC == retVal)
        {
            WDOG_UNLOCK_CONFIG();
            wDOGxw->WDOG_TMO = ptWDOGInitConfig->timeoutValue;
            retVal = WDOG_WaitConfigCompleted();
            if (SUCC == retVal)
            {
                if (ENABLE == ptWDOGInitConfig->winEnable)
                {
                    WDOG_UNLOCK_CONFIG();
                    wDOGxw->WDOG_WIN = ptWDOGInitConfig->windowValue;
                    retVal = WDOG_WaitConfigCompleted();
                }
            }
        }
        if (0U == Primask)
        {
            COMMON_ENABLE_INTERRUPTS();
        }
    }

    return retVal;
}

/**
 * @brief      enable wdog count Function
 *
 * @param[in]  none
 *
 * @return     operation status.
 *
 */
ResultStatus_t WDOG_Enable(void)
{
    wdog_reg_t * wDOGx = (wdog_reg_t *)(wdogRegPtr);
    uint32_t Primask;
    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
    if (0U == Primask)
    {
        COMMON_DISABLE_INTERRUPTS();
    }
    /* unlock config update */
    WDOG_UNLOCK_CONFIG();

    wDOGx->WDOG_CS.WDOGE = 1U;
    if (0U == Primask)
    {
        COMMON_ENABLE_INTERRUPTS();
    }
    return (WDOG_WaitConfigCompleted());
}

/**
 * @brief      disable wdog count Function
 *
 * @param[in]  none
 *
 * @return     operation status.
 *
 */
ResultStatus_t WDOG_Disable(void)
{
    wdog_reg_t * wDOGx = (wdog_reg_t *)(wdogRegPtr);
    uint32_t Primask;
    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
    if (0U == Primask)
    {
        COMMON_DISABLE_INTERRUPTS();
    }
    /* unlock config update */
    WDOG_UNLOCK_CONFIG();
    wDOGx->WDOG_CS.WDOGE = 0U;
    if (0U == Primask)
    {
        COMMON_ENABLE_INTERRUPTS();
    }
    return (WDOG_WaitConfigCompleted());
}

/**
 * @brief      refresh wdog count Function
 *
 * @param[in]  none
 *
 * @return none.
 *
 */
void WDOG_Refresh(void)
{
    WDOG_REFRESH_COUNT();
}

/**
 * @brief      get wdog config allow flag status Function
 *
 * @param[in]  none
 *
 * @return     busy status.
 *
 */
FlagStatus_t WDOG_GetConfigAllowStatus(void)
{
    wdog_reg_t * wDOGx = (wdog_reg_t *)(wdogRegPtr);
    return ((FlagStatus_t)wDOGx->WDOG_CS.CFGUA);
}

/**
 * @brief      set wdog config allow flag Function
 *
 * @param[in]  allow: config update control
 *                    - ENABLE: enable config update
 *                    - DISABLE: disbale config update
 *
 * @return     operation status.
 *
 */
ResultStatus_t WDOG_ConfigAllowControl(ControlState_t allow)
{
    wdog_reg_t * wDOGx = (wdog_reg_t *)(wdogRegPtr);
    uint32_t Primask;
    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
    if (0U == Primask)
    {
        COMMON_DISABLE_INTERRUPTS();
    }
    /* unlock config update */
    WDOG_UNLOCK_CONFIG();
    wDOGx->WDOG_CS.CFGUA = (uint32_t)allow;
    if (0U == Primask)
    {
        COMMON_ENABLE_INTERRUPTS();
    }
    return (WDOG_WaitConfigCompleted());
}

/**
 * @brief      enable/disable wdog window mode Function
 *
 * @param[in]  winEnable: window mode control
 *                        - ENABLE: enable window mode
 *                        - DISABLE: disbale window mode
 *
 * @return     operation status.
 *
 */
ResultStatus_t WDOG_WindowModeControl(ControlState_t winEnable)
{
    wdog_reg_t * wDOGx = (wdog_reg_t *)(wdogRegPtr);
    uint32_t Primask;
    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
    if (0U == Primask)
    {
        COMMON_DISABLE_INTERRUPTS();
    }
    /* unlock config update */
    WDOG_UNLOCK_CONFIG();
    wDOGx->WDOG_CS.WINE = (uint32_t)winEnable;
    if (0U == Primask)
    {
        COMMON_ENABLE_INTERRUPTS();
    }
    return (WDOG_WaitConfigCompleted());
}

/**
 * @brief      set wdog window value Function
 *
 * @param[in]  windowValue: window value, 32 bits
 *
 * @return     operation status.
 *
 */
ResultStatus_t WDOG_SetWindowValue(uint32_t windowValue)
{
    wdog_reg_w_t * wDOGxw = (wdog_reg_w_t *)(wdogRegWPtr);
    uint32_t Primask;
    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
    if (0U == Primask)
    {
        COMMON_DISABLE_INTERRUPTS();
    }
    /* unlock config update */
    WDOG_UNLOCK_CONFIG();
    wDOGxw->WDOG_WIN = windowValue;
    if (0U == Primask)
    {
        COMMON_ENABLE_INTERRUPTS();
    }
    return (WDOG_WaitConfigCompleted());
}

/**
 * @brief      get wdog window register value Function
 *
 * @param[in]  none
 *
 * @return window register value.
 *
 */
uint32_t WDOG_GetWindowValue(void)
{
    wdog_reg_t * wDOGx = (wdog_reg_t *)(wdogRegPtr);
    return ((uint32_t)wDOGx->WDOG_WIN.WIN);
}

/**
 * @brief      set wdog clock source Function
 *
 * @param[in]  clkSource: clock source
 *
 * @return     operation status.
 *
 */
ResultStatus_t WDOG_SetClockSource(WDOG_ClkSource_t clkSource)
{
    wdog_reg_t * wDOGx = (wdog_reg_t *)(wdogRegPtr);
    uint32_t Primask;
    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
    if (0U == Primask)
    {
        COMMON_DISABLE_INTERRUPTS();
    }
    /* unlock config update */
    WDOG_UNLOCK_CONFIG();
    wDOGx->WDOG_CS.CLKS = (uint32_t)clkSource;
    if (0U == Primask)
    {
        COMMON_ENABLE_INTERRUPTS();
    }
    return (WDOG_WaitConfigCompleted());
}

/**
 * @brief      set wdog timeout value Function
 *
 * @param[in]  timeoutValue: timeout value, 32 bits
 *
 * @return     operation status.
 *
 */
ResultStatus_t WDOG_SetTimeoutValue(uint32_t timeoutValue)
{
    wdog_reg_w_t * wDOGxw = (wdog_reg_w_t *)(wdogRegWPtr);
    uint32_t Primask;
    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
    if (0U == Primask)
    {
        COMMON_DISABLE_INTERRUPTS();
    }
    /* unlock config update */
    wDOGxw->WDOG_CNT = 0xB0D9A1C4U;
    wDOGxw->WDOG_CNT = 0x1A1E3B0FU;
    wDOGxw->WDOG_TMO = timeoutValue;
    if (0U == Primask)
    {
        COMMON_ENABLE_INTERRUPTS();
    }
    return (WDOG_WaitConfigCompleted());
}

/**
 * @brief      get wdog timeout register value Function
 *
 * @param[in]  none
 *
 * @return timeout register value.
 *
 */
uint32_t WDOG_GetTimeoutValue(void)
{
    wdog_reg_t * wDOGx = (wdog_reg_t *)(wdogRegPtr);

    return ((uint32_t)wDOGx->WDOG_TMO.TMO);
}

/**
 * @brief      configure wdog behavior in stop mode Function
 *
 * @param[in]  cmd: stop mode control
 *                  - ENABLE: counter continue in stop mode
 *                  - DISABLE: counter halt in stop mode
 *
 * @return     operation status.
 *
 */
ResultStatus_t WDOG_StopModeControl(ControlState_t cmd)
{
    wdog_reg_t * wDOGx = (wdog_reg_t *)(wdogRegPtr);
    uint32_t Primask;
    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
    if (0U == Primask)
    {
        COMMON_DISABLE_INTERRUPTS();
    }
    /* unlock config update */
    WDOG_UNLOCK_CONFIG();
    wDOGx->WDOG_CS.STOPE = (uint32_t)cmd;
    if (0U == Primask)
    {
        COMMON_ENABLE_INTERRUPTS();
    }
    return (WDOG_WaitConfigCompleted());
}

/**
 * @brief      configure wdog behavior in wait mode Function
 *
 * @param[in]  cmd: wait mode control
 *                  - ENABLE: counter continue in wait mode
 *                  - DISABLE: counter halt in wait mode
 *
 * @return     operation status.
 *
 */
ResultStatus_t WDOG_WaitModeControl(ControlState_t cmd)
{
    wdog_reg_t * wDOGx = (wdog_reg_t *)(wdogRegPtr);
    uint32_t Primask;
    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
    if (0U == Primask)
    {
        COMMON_DISABLE_INTERRUPTS();
    }
    /* unlock config update */
    WDOG_UNLOCK_CONFIG();
    wDOGx->WDOG_CS.WAITE = (uint32_t)cmd;
    if (0U == Primask)
    {
        COMMON_ENABLE_INTERRUPTS();
    }
    return (WDOG_WaitConfigCompleted());
}

/**
 * @brief      configure wdog behavior in debug mode Function
 *
 * @param[in]  cmd: debug mode control
 *                  - ENABLE: counter continue in debug mode
 *                  - DISABLE: counter halt in debug mode
 *
 * @return     operation status.
 *
 */
ResultStatus_t WDOG_DebugModeControl(ControlState_t cmd)
{
    wdog_reg_t * wDOGx = (wdog_reg_t *)(wdogRegPtr);
    uint32_t Primask;
    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
    if (0U == Primask)
    {
        COMMON_DISABLE_INTERRUPTS();
    }
    /* unlock config update */
    WDOG_UNLOCK_CONFIG();
    wDOGx->WDOG_CS.DEBUGE = (uint32_t)cmd;
    if (0U == Primask)
    {
        COMMON_ENABLE_INTERRUPTS();
    }
    return (WDOG_WaitConfigCompleted());
}

/**
 * @brief      set wdog test mode Function
 *
 * @param[in]  testMode: test/normal mode
 *
 * @return     operation status.
 *
 */
ResultStatus_t WDOG_SetTestMode(WDOG_TestMode_t testMode)
{
    wdog_reg_t * wDOGx = (wdog_reg_t *)(wdogRegPtr);
    uint32_t Primask;
    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
    if (0U == Primask)
    {
        COMMON_DISABLE_INTERRUPTS();
    }
    /* unlock config update */
    WDOG_UNLOCK_CONFIG();
    wDOGx->WDOG_CS.TSTM = (uint32_t)testMode;
    if (0U == Primask)
    {
        COMMON_ENABLE_INTERRUPTS();
    }
    return (WDOG_WaitConfigCompleted());
}

/**
 * @brief      get wdog test/normal mode Function
 *
 * @param[in]  none
 *
 * @return test/normal mode.
 *
 */
WDOG_TestMode_t WDOG_GetTestMode(void)
{
    wdog_reg_t * wDOGx = (wdog_reg_t *)(wdogRegPtr);
    return ((WDOG_TestMode_t)wDOGx->WDOG_CS.TSTM);
}

/**
 * @brief      get wdog free-running counter Function
 *
 * @param[in]  none
 *
 * @return free-running counter value.
 *
 */
uint32_t WDOG_GetCounter(void)
{
    wdog_reg_t * wDOGx = (wdog_reg_t *)(wdogRegPtr);
    return ((uint32_t)wDOGx->WDOG_CNT.CNT);
}

/**
 * @brief      get flag indcates configuration update is completed Function
 *
 * @param[in]  none
 *
 * @return     configuration update completed status.
 *
 */
FlagStatus_t WDOG_GetConfigCompletedStatus(void)
{
    wdog_reg_t * wDOGx = (wdog_reg_t *)(wdogRegPtr);
    return ((FlagStatus_t)wDOGx->WDOG_CS.CFGUF);
}

/**
 * @brief      get Flag indcates all registers are locked or unlocked Function
 *
 * @param[in]  none
 *
 * @return     lock Flag.
 *
 */
FlagStatus_t WDOG_GetLockStatus(void)
{
    wdog_reg_t * wDOGx = (wdog_reg_t *)(wdogRegPtr);
    return ((1U == wDOGx->WDOG_CS.UNLKF) ? RESET : SET);
}

/**
 * @brief      get WDOG int flag Function
 *
 * @param[in]  intType: int type
 *                      - WDOG_INT_BEFORERESET: int befor reset
 *                      - WDOG_INT_ALL: all int type  
 *
 * @return whether a int is asserted or not.
 *
 */
IntStatus_t WDOG_GetIntStatus(WDOG_INT_t intType)
{
    wdog_reg_w_t * wDOGxw = (wdog_reg_w_t *)(wdogRegWPtr);
    return ((IntStatus_t)((uint32_t)((wDOGxw->WDOG_CS & wdogIntFlagMask[intType]) 
                                       >> WDOG_CS_INTF_SHIFT)));
}

/**
 * @brief      clear wdog int flag Function
 *
 * @param[in]  none
 *
 * @return     operation status.
 *
 */
ResultStatus_t WDOG_ClearIntStatus(void)
{
    wdog_reg_w_t * wDOGxw = (wdog_reg_w_t *)(wdogRegWPtr);
    uint32_t Primask;
    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
    if (0U == Primask)
    {
        COMMON_DISABLE_INTERRUPTS();
    }
    /* unlock config update */
    WDOG_UNLOCK_CONFIG();
    uint32_t intStatus = wDOGxw->WDOG_CS;
    intStatus = intStatus | WDOG_CS_INTF_MASK;
    wDOGxw->WDOG_CS = intStatus;
    if (0U == Primask)
    {
        COMMON_ENABLE_INTERRUPTS();
    }
    return (WDOG_WaitConfigCompleted());
}

/**
 * @brief      set wdog int mask Function
 *
 * @param[in]  intType: int type
 *                      - WDOG_INT_BEFORERESET: int befor reset
 *                      - WDOG_INT_ALL: all int type  
 * @param[in]  intMask: int mask
 *
 * @return     operation status.
 *
 */
ResultStatus_t WDOG_IntMask(WDOG_INT_t intType, IntMask_t intMask)
{
    wdog_reg_w_t * wDOGxw = (wdog_reg_w_t *)(wdogRegWPtr);
    uint32_t uTmp;
    uint32_t Primask;
    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
    if (0U == Primask)
    {
        COMMON_DISABLE_INTERRUPTS();
    }
    uTmp = wDOGxw->WDOG_CS;

    uTmp &= ~wdogIntMask[intType];
    uTmp |= WDOG_MASK_CONVERT_ENABLE(intMask);
    
    /* unlock config update */
    WDOG_UNLOCK_CONFIG();
    wDOGxw->WDOG_CS = uTmp;
    if (0U == Primask)
    {
        COMMON_ENABLE_INTERRUPTS();
    }
    return (WDOG_WaitConfigCompleted());
}

/**
 * @brief      Install callback function
 *
 * @param[in]  intType: select interrupt type
 *                      - WDOG_INT_BEFORERESET: int befor reset
 * @param[in]  cbFun: indicate callback function
 *
 * @return    none
 *
 */
void WDOG_InstallCallBackFunc(WDOG_INT_t intType, isr_cb_t *cbFun)
{
    if(intType < WDOG_INT_ALL)
    {
        wdogIsrCb[intType] = cbFun;
    }
}

/**
 * @brief      WDOG interrupt function in vector
 *
 * @param  none
 *
 * @return none
 *
 */
void WDOG_DriverIRQHandler(void)
{
    uint32_t Primask;
    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
    if (0U == Primask)
    {
        COMMON_DISABLE_INTERRUPTS();
    }
    if(wdogIsrCb[WDOG_INT_BEFORERESET] != NULL)
    {
        wdogIsrCb[WDOG_INT_BEFORERESET]();
    }
    COMMON_DSB();
    
    WDOG_UNLOCK_CONFIG();
    wdogRegWPtr->WDOG_CS |= wdogIntFlagMask[WDOG_INT_BEFORERESET];
    if (0U == Primask)
    {
        COMMON_ENABLE_INTERRUPTS();
    }
}

/** @} end of group WDOG_Public_Functions */

/** @} end of group WDOG driver modules */

/** @} end of group Z20K14XM_Peripheral_Driver */
