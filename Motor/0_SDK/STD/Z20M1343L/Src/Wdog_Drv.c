/**************************************************************************************************/
/**
 * @file      : Wdog_Drv.c
 * @brief     : WDOG module driver file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#include "Wdog_Drv.h"

/** @defgroup Private_MacroDefinition
 *  @{
 */

#define WDOG_CS_INTF_MASK              (0x04000000U)
#define WDOG_CS_CFGUF_MASK             (0x01000000U)

#define WDOG_CS_TSTM_MASK              (0x00070000U)
#define WDOG_CS_CFGUA_MASK             (0x00000040U)
#define WDOG_CS_WINE_MASK              (0x00000020U)
#define WDOG_CS_INTE_MASK              (0x00000010U)
#define WDOG_CS_STOPE_MASK             (0x00000008U)
#define WDOG_CS_DEBUGE_MASK            (0x00000002U)
#define WDOG_CS_WDOGE_MASK             (0x00000001U)

#define WDOG_CS_INTF_SHIFT             (26U)
#define WDOG_CS_TSTM_SHIFT             (16U)
#define WDOG_CS_CFGUA_SHIFT            (6U)
#define WDOG_CS_WINE_SHIFT             (5U)
#define WDOG_CS_INTE_SHIFT             (4U)
#define WDOG_CS_STOPE_SHIFT            (3U)
#define WDOG_CS_DEBUGE_SHIFT           (1U)

#define WDOG_CS_TSTM_SET(X) \
        (((uint32)(((uint32)(X)) << WDOG_CS_TSTM_SHIFT))&WDOG_CS_TSTM_MASK)
        
#define WDOG_CS_CFGUA_SET(X) \
        (((uint32)(((uint32)(X)) << WDOG_CS_CFGUA_SHIFT))&WDOG_CS_CFGUA_MASK)
        
#define WDOG_CS_WINE_SET(X) \
        (((uint32)(((uint32)(X)) << WDOG_CS_WINE_SHIFT))&WDOG_CS_WINE_MASK)
        
#define WDOG_CS_STOPE_SET(X) \
        (((uint32)(((uint32)(X)) << WDOG_CS_STOPE_SHIFT))&WDOG_CS_STOPE_MASK)
        
#define WDOG_CS_DEBUGE_SET(X) \
        (((uint32)(((uint32)(X)) << WDOG_CS_DEBUGE_SHIFT))&WDOG_CS_DEBUGE_MASK)
        
#define WDOG_CS_INTE_SET(X) \
        (((uint32)(((uint32)(X)) << WDOG_CS_INTE_SHIFT))&WDOG_CS_INTE_MASK)
        
#define WDOG_UNLOCK_CONFIG_VALUE1     (0xB0D9A1C4UL)
#define WDOG_UNLOCK_CONFIG_VALUE2     (0x1A1E3B0FUL)
#define WDOG_REFRESH_VALUE1           (0xA0C4B1D6UL)
#define WDOG_REFRESH_VALUE2           (0x1E0D0C7BUL)

#define WDOG_MASK_CONVERT_ENABLE(X) \
        ((uint32)((((uint32)(X) + 1U) & 0x1U) << WDOG_CS_INTE_SHIFT))

START_FUNCTION_DECLARATION_RAMSECTION
static void Wdog_RefreshCount(void)
END_FUNCTION_DECLARATION_RAMSECTION    /* PRQA S 0605*/

/** @} end of group Private_MacroDefinition */


/** @defgroup Private_TypeDefinition
 *  @{
 */

/** @} end of group Private_TypeDefinition*/



/** @defgroup Private_VariableDefinition
 *  @{
 */

/**
 *  @brief Wdog Register address array
 */
/*PRQA S 0303 ++*/
static Reg_Wdg_BfType * const Wdog_RegBfPtr = (Reg_Wdg_BfType *)WDOG_BASE_ADDR;
static Reg_Wdg_WType * const Wdog_RegWPtr = (Reg_Wdg_WType *)WDOG_BASE_ADDR;
/*PRQA S 0303 --*/

/**
 *  @brief Wdog int status mask array 
 */
static const uint32 Wdog_IntMaskTable[] = 
{
    WDOG_CS_INTE_MASK,
    WDOG_CS_INTE_MASK
};

static const uint32 Wdog_IntFlagMaskTable[] = 
{
    WDOG_CS_INTF_MASK,
    WDOG_CS_INTF_MASK
};

/** @} end of group Private_VariableDefinition */

/** @defgroup Global_VariableDefinition
 *  @{
 */

/** @} end of group Global_VariableDefinition */

/** @defgroup Private_FunctionDeclaration
 *  @{
 */

/** @} end of group Private_FunctionDeclaration */

/** @defgroup Private_FunctionDefinition
 *  @{
 */
 
/**
 * @brief      Wait until configuration is completed function
 *
 * @param[in]  None
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed.
 * @retval     COMMON_ERR: Command execution timeout 
 *
 */
static inline Common_ResultStatusType Wdog_WaitConfigCompleted(void)
{    
    volatile uint32 ULoop = 0U;
    Common_ResultStatusType RetVal = COMMON_SUCC;
    
    while ((uint32)COMMON_SET != Wdog_RegBfPtr->WDOG_CS.CFGUF)
    {
        if (ULoop > WDOG_WAITCONFIG_GOING_CNT)
        {
            RetVal = COMMON_ERR;
            break;
        }

        ULoop++;
    }
    
    return RetVal;
}

/**
 * @brief      Refresh wdog count function
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
static void Wdog_RefreshCount(void)
{
    uint32 Primask;
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

/**
 * @brief      Unlock wdog config update function
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
static inline void Wdog_UnlockConfig(void)
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

/** @} end of group Private_FunctionDefinition */

/** @defgroup Public_FunctionDefinition
 *  @{
 */

/**
 * @brief      Wdog initializes function
 *
 * @param[in]  InitConfigPtr: Pointer to a WDOG configuration structure.
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed.
 * @retval     COMMON_ERR: Command execution timeout 
 *
 */
Common_ResultStatusType Wdog_Init(const Wdog_ConfigType * InitConfigPtr)
{
    Common_ResultStatusType RetVal = COMMON_SUCC;
    uint32 CsValue = Wdog_RegWPtr->WDOG_CS;
    uint32 Primask;

    if (0U == Wdog_RegBfPtr->WDOG_CS.CFGUA)
    {
        RetVal = COMMON_ERR;
    }

    if (COMMON_SUCC == RetVal)
    {
        /* Clear the bits used for configuration */
        CsValue &= ~(WDOG_CS_TSTM_MASK | WDOG_CS_WINE_MASK | WDOG_CS_STOPE_MASK
                    | WDOG_CS_DEBUGE_MASK);
        
        /* Construct CS register new value */
        CsValue |= WDOG_CS_TSTM_SET(InitConfigPtr->TestMode);
        CsValue |= WDOG_CS_WINE_SET(InitConfigPtr->WinEnable);
        CsValue |= WDOG_CS_STOPE_SET(InitConfigPtr->Stop);
        CsValue |= WDOG_CS_DEBUGE_SET(InitConfigPtr->Debug);

        ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
        if (0U == Primask)
        {
            COMMON_DISABLE_INTERRUPTS();
        }
        /* unlock config update */
        Wdog_UnlockConfig();
        Wdog_RegWPtr->WDOG_CS = CsValue;
        RetVal = Wdog_WaitConfigCompleted();
        if (COMMON_SUCC == RetVal)
        {
            Wdog_UnlockConfig();
            Wdog_RegBfPtr->WDOG_TMO.TMO = InitConfigPtr->TimeoutValue;
            RetVal = Wdog_WaitConfigCompleted();
            if (COMMON_SUCC == RetVal)
            {              
                if (COMMON_ENABLE == InitConfigPtr->WinEnable)
                {
                    Wdog_UnlockConfig();
                    Wdog_RegBfPtr->WDOG_WIN.WIN = InitConfigPtr->WindowValue;
                    RetVal = Wdog_WaitConfigCompleted();
		        }
	        }
        }
        if (0U == Primask)
        {
            COMMON_ENABLE_INTERRUPTS();
        }
    }

    return RetVal;
}

/**
 * @brief      Enable wdog count function
 *
 * @param[in]  None
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed.
 * @retval     COMMON_ERR: Command execution timeout 
 *
 */
Common_ResultStatusType Wdog_Enable(void)
{
    uint32 Primask;

    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
    if (0U == Primask)
    {
        COMMON_DISABLE_INTERRUPTS();
    }
    /* unlock config update */
    Wdog_UnlockConfig();
    Wdog_RegBfPtr->WDOG_CS.WDOGE = 1U;
    if (0U == Primask)
    {
        COMMON_ENABLE_INTERRUPTS();
    }

    return (Wdog_WaitConfigCompleted());
}

/**
 * @brief      Disable wdog count function
 *
 * @param[in]  None
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed.
 * @retval     COMMON_ERR: Command execution timeout 
 *
 */
Common_ResultStatusType Wdog_Disable(void)
{
    uint32 Primask;

    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
    if (0U == Primask)
    {
        COMMON_DISABLE_INTERRUPTS();
    }
    /* unlock config update */
    Wdog_UnlockConfig();
    Wdog_RegBfPtr->WDOG_CS.WDOGE = 0U;
    if (0U == Primask)
    {
        COMMON_ENABLE_INTERRUPTS();
    }

    return (Wdog_WaitConfigCompleted());
}

/**
 * @brief      Refresh wdog count function
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void Wdog_Refresh(void)
{
    Wdog_RefreshCount();
}

/**
 * @brief      Enable wdog time interval check function
 *
 * @param[in]  None
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Operation successfully executed.
 * @retval     COMMON_ERR: Operation execution timeout 
 *
 */
Common_ResultStatusType Wdog_EnableTimeIntervalCheck(void)
{
    uint32 Primask;

    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
    if (0U == Primask)
    {
        COMMON_DISABLE_INTERRUPTS();
    }
    /* unlock config update */
    Wdog_UnlockConfig();
    Wdog_RegBfPtr->WDOG_CS.TICEN = 1U;
    if (0U == Primask)
    {
        COMMON_ENABLE_INTERRUPTS();
    }

    return (Wdog_WaitConfigCompleted());
}

/**
 * @brief      Get wdog config allow flag status function
 *
 * @param[in]  None
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_SET: Status set.
 * @retval     COMMON_RESET: Status not set 
 *
 */
Common_FlagStatusType Wdog_GetConfigAllowStatus(void)
{
    return ((Common_FlagStatusType)Wdog_RegBfPtr->WDOG_CS.CFGUA);
}

/**
 * @brief      Set wdog config allow flag function
 *
 * @param[in]  Allow: config update control
 *                    - COMMON_ENABLE: enable config update
 *                    - COMMON_DISABLE: disable config update
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed.
 * @retval     COMMON_ERR: Command execution timeout 
 *
 */
Common_ResultStatusType Wdog_ControlConfigAllow(Common_ControlStateType Allow)
{
    uint32 Primask;

    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
    if (0U == Primask)
    {
        COMMON_DISABLE_INTERRUPTS();
    }
    /* unlock config update */
    Wdog_UnlockConfig();
    Wdog_RegBfPtr->WDOG_CS.CFGUA = (uint32)Allow;
    if (0U == Primask)
    {
        COMMON_ENABLE_INTERRUPTS();
    }

    return (Wdog_WaitConfigCompleted());
}

/**
 * @brief      Enable/disable wdog window mode function
 *
 * @param[in]  WinEnable: window mode control
 *                        - COMMON_ENABLE: enable window mode
 *                        - COMMON_DISABLE: disable window mode
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed.
 * @retval     COMMON_ERR: Command execution timeout 
 *
 */
Common_ResultStatusType Wdog_ControlWindowMode(Common_ControlStateType WinEnable)
{
    uint32 Primask;

    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
    if (0U == Primask)
    {
        COMMON_DISABLE_INTERRUPTS();
    }
    /* unlock config update */
    Wdog_UnlockConfig();
    Wdog_RegBfPtr->WDOG_CS.WINE = (uint32)WinEnable;
    if (0U == Primask)
    {
        COMMON_ENABLE_INTERRUPTS();
    }

    return (Wdog_WaitConfigCompleted());
}

/**
 * @brief      Set wdog window value function
 *
 * @param[in]  WindowValue: window value, 16 bits
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed.
 * @retval     COMMON_ERR: Command execution timeout 
 *
 */
Common_ResultStatusType Wdog_SetWindowValue(uint16 WindowValue)
{
    uint32 Primask;

    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
    if (0U == Primask)
    {
        COMMON_DISABLE_INTERRUPTS();
    }
    /* unlock config update */
    Wdog_UnlockConfig();
    Wdog_RegBfPtr->WDOG_WIN.WIN = WindowValue;
    if (0U == Primask)
    {
        COMMON_ENABLE_INTERRUPTS();
    }

    return (Wdog_WaitConfigCompleted());
}

/**
 * @brief      Get wdog window register value function
 *
 * @param[in]  None
 *
 * @return     window register value
 *
 */
uint16 Wdog_GetWindowValue(void)
{
    return ((uint16)Wdog_RegBfPtr->WDOG_WIN.WIN);
}

/**
 * @brief      Set wdog timeout value function
 *
 * @param[in]  TimeoutValue: timeout value, 16 bits
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed.
 * @retval     COMMON_ERR: Command execution timeout 
 *
 */
Common_ResultStatusType Wdog_SetTimeoutValue(uint16 TimeoutValue)
{
    uint32 Primask;
    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
    if (0U == Primask)
    {
        COMMON_DISABLE_INTERRUPTS();
    }
    /* unlock config update */
    Wdog_RegWPtr->WDOG_CNT = 0xB0D9A1C4U;
    Wdog_RegWPtr->WDOG_CNT = 0x1A1E3B0FU;
    Wdog_RegBfPtr->WDOG_TMO.TMO = TimeoutValue;
    if (0U == Primask)
    {
        COMMON_ENABLE_INTERRUPTS();
    }
    return (Wdog_WaitConfigCompleted());
}

/**
 * @brief      Get wdog timeout register value function
 *
 * @param[in]  None
 *
 * @return     timeout register value.
 *
 */
uint16 Wdog_GetTimeoutValue(void)
{
    return ((uint16)Wdog_RegBfPtr->WDOG_TMO.TMO);
}

/**
 * @brief      Configure wdog behavior in stop mode function
 *
 * @param[in]  Cmd: stop mode control
 *                  - COMMON_ENABLE: counter continue in stop mode
 *                  - COMMON_DISABLE: counter halt in stop mode
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed.
 * @retval     COMMON_ERR: Command execution timeout 
 *
 */
Common_ResultStatusType Wdog_ControlStopMode(Common_ControlStateType Cmd)
{
    uint32 Primask;

    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
    if (0U == Primask)
    {
        COMMON_DISABLE_INTERRUPTS();
    }
    /* unlock config update */
    Wdog_UnlockConfig();
    Wdog_RegBfPtr->WDOG_CS.STOPE = (uint32)Cmd;
    if (0U == Primask)
    {
        COMMON_ENABLE_INTERRUPTS();
    }

    return (Wdog_WaitConfigCompleted());
}

/**
 * @brief      Configure wdog behavior in debug mode function
 *
 * @param[in]  Cmd: debug mode control
 *                  - COMMON_ENABLE: counter continue in debug mode
 *                  - COMMON_DISABLE: counter halt in debug mode
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed.
 * @retval     COMMON_ERR: Command execution timeout 
 *
 */
Common_ResultStatusType Wdog_ControlDebugMode(Common_ControlStateType Cmd)
{
    uint32 Primask;

    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
    if (0U == Primask)
    {
        COMMON_DISABLE_INTERRUPTS();
    }
    /* unlock config update */
    Wdog_UnlockConfig();
    Wdog_RegBfPtr->WDOG_CS.DEBUGE = (uint32)Cmd;
    if (0U == Primask)
    {
        COMMON_ENABLE_INTERRUPTS();
    }

    return (Wdog_WaitConfigCompleted());
}

/**
 * @brief      Set wdog test mode function
 *
 * @param[in]  TestMode: test mode select
 *                       - WDOG_TST_MODE0: test mode 0, only byte0 is used
 *                       - WDOG_TST_MODE1: test mode 1, only byte1 is used
 *                       - WDOG_TST_NORMAL: normal mode
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed.
 * @retval     COMMON_ERR: Command execution timeout 
 *
 * @note       When in WDOG_TST_MODE0, CNT[7:0] is compared with TMO[7:0],
 *             the CNT[15:0] initial value is 0xFF00.
 *             When in WDOG_TST_MODE1, CNT[15:8] is compared with TMO[15:8],
 *             the CNT[15:0] initial value is 0x00FF.
 *             More info refers to RM document.
 * 
 */
Common_ResultStatusType Wdog_SetTestMode(Wdog_TestModeType TestMode)
{
    uint32 Primask;

    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
    if (0U == Primask)
    {
        COMMON_DISABLE_INTERRUPTS();
    }
    /* unlock config update */
    Wdog_UnlockConfig();
    Wdog_RegBfPtr->WDOG_CS.TSTM = (uint32)TestMode;
    if (0U == Primask)
    {
        COMMON_ENABLE_INTERRUPTS();
    }

    return (Wdog_WaitConfigCompleted());
}

/**
 * @brief      Get wdog test/normal mode function
 *
 * @param[in]  None
 *
 * @return     Wdog_TestModeType
 * @retval     WDOG_TST_MODE0: test mode 0
 * @retval     WDOG_TST_MODE1: test mode 1
 * @retval     WDOG_TST_NORMAL: normal mode
 *
 */
Wdog_TestModeType Wdog_GetTestMode(void)
{
    return ((Wdog_TestModeType)Wdog_RegBfPtr->WDOG_CS.TSTM);
}

/**
 * @brief      Get wdog free-running counter function
 *
 * @param[in]  None
 *
 * @return     free-running counter value.
 *
 */
uint16 Wdog_GetCounter(void)
{
    return ((uint16)Wdog_RegBfPtr->WDOG_CNT.CNT);
}

/**
 * @brief      Get flag indicates configuration update is completed function
 *
 * @param[in]  None
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_SET: status set
 * @retval     COMMON_RESET: status not set
 *
 */
Common_FlagStatusType Wdog_GetConfigCompletedStatus(void)
{
    return ((Common_FlagStatusType)Wdog_RegBfPtr->WDOG_CS.CFGUF);
}

/**
 * @brief      Get flag indicates all registers are locked or unlocked function
 *
 * @param[in]  None
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_SET: status set
 * @retval     COMMON_RESET: status not set
 *
 */
Common_FlagStatusType Wdog_GetLockStatus(void)
{
    return ((1U == Wdog_RegBfPtr->WDOG_CS.UNLKF) ? COMMON_RESET : COMMON_SET);
}

/**
 * @brief      Get WDOG int flag function
 *
 * @param[in]  IntType: int type
 *                      - WDOG_INT_BEFORERESET: int before reset
 *                      - WDOG_INT_ALL: all int type  
 *
 * @return     Common_IntStatusType
 * @retval     COMMON_SET: interrupt assert
 * @retval     COMMON_RESET: interrupt de-assert
 *
 */
Common_IntStatusType Wdog_GetIntStatus(Wdog_IntType IntType)
{
    return ((Common_IntStatusType)((uint32)((Wdog_RegWPtr->WDOG_CS & 
             Wdog_IntFlagMaskTable[IntType]) >> WDOG_CS_INTF_SHIFT)));
}

/**
 * @brief      Clear wdog int flag function
 *
 * @param[in]  IntType: int type
 *                      - WDOG_INT_BEFORERESET: int before reset
 *                      - WDOG_INT_ALL: all int type  
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed.
 * @retval     COMMON_ERR: Command execution timeout 
 *
 */
Common_ResultStatusType Wdog_ClearIntStatus(Wdog_IntType IntType)
{
    uint32 IntStatus = Wdog_RegWPtr->WDOG_CS;
    uint32 Primask;

    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
    if (0U == Primask)
    {
        COMMON_DISABLE_INTERRUPTS();
    }
    /* unlock config update */
    Wdog_UnlockConfig();
    IntStatus |= WDOG_CS_INTF_MASK;
    Wdog_RegWPtr->WDOG_CS = IntStatus;
    if (0U == Primask)
    {
        COMMON_ENABLE_INTERRUPTS();
    }

    return (Wdog_WaitConfigCompleted());
}

/**
 * @brief      Set wdog int mask function
 *
 * @param[in]  IntType: int type
 *                      - WDOG_INT_BEFORERESET: int before reset
 *                      - WDOG_INT_ALL: all int type  
 * @param[in]  IntMask: int mask
 *                      - COMMON_UNMASK: int unmask
 *                      - COMMON_MASK: int mask
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed.
 * @retval     COMMON_ERR: Command execution timeout 
 *
 */
Common_ResultStatusType Wdog_SetIntMask(Wdog_IntType IntType, Common_IntMaskType IntMask)
{
    uint32 Temp;
    uint32 Primask;

    Temp = Wdog_RegWPtr->WDOG_CS;

    if(COMMON_UNMASK == IntMask)
    {
        Temp |= Wdog_IntMaskTable[IntType];
    }
    else
    {
        Temp &= ~Wdog_IntMaskTable[IntType];
    }
    
    ASMV_KEYWORD( "MRS %0, PRIMASK " : "=r"(Primask));
    if (0U == Primask)
    {
        COMMON_DISABLE_INTERRUPTS();
    }
    /* unlock config update */
    Wdog_UnlockConfig();
    Wdog_RegWPtr->WDOG_CS = Temp;
    if (0U == Primask)
    {
        COMMON_ENABLE_INTERRUPTS();
    }

    return (Wdog_WaitConfigCompleted());
}

/** @} end of group Public_FunctionDefinition */
