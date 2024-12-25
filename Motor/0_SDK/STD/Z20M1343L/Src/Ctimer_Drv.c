/**************************************************************************************************/
/**
 * @file      : Ctimer_Drv.c
 * @brief     : Ctimer module driver file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
#include "Ctimer_Drv.h"

/** @defgroup Private_MacroDefinition
 *  @{
 */

/** @} end of group Private_MacroDefinition */

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
/*PRQA S 0303 ++*/
static Reg_Ctimer_BfType * const Ctimer_RegBfPtr = (Reg_Ctimer_BfType *)CTIMER_BASE_ADDR;
static Reg_Ctimer_WType * const Ctimer_RegWPtr = (Reg_Ctimer_WType *)CTIMER_BASE_ADDR;
/*PRQA S 0303 --*/

static Isr_CbFuncType * Ctimer_IsrCbFuncPtr[CTIMER_INT_ALL] = 
{
    NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR
};


static const uint32 Ctimer_IntMaskTable[] =
{
    0x00000001U,      /* INT_RISING_UNIT_0 */
    0x00000002U,      /* INT_RISING_UNIT_1 */
    0x00000004U,      /* INT_RISING_UNIT_2 */
    0x00000010U,      /* INT_FALLING_UNIT_0 */
    0x00000020U,      /* INT_FALLING_UNIT_1 */
    0x00000040U,      /* INT_FALLING_UNIT_2 */
    0x00000100U,      /* INT_OVERFLOW_UNIT_0 */
    0x00000200U,      /* INT_OVERFLOW_UNIT_1 */
    0x00000400U,      /* INT_OVERFLOW_UNIT_2 */
    0x00000777U       /* INT_ALL */
};

static const uint32 Ctimer_IntStatusTable[] =
{
    0x00000001U,      /* INT_RISING_UNIT_0 */
    0x00000002U,      /* INT_RISING_UNIT_1 */
    0x00000004U,      /* INT_RISING_UNIT_2 */
    0x00000010U,      /* INT_FALLING_UNIT_0 */
    0x00000020U,      /* INT_FALLING_UNIT_1 */
    0x00000040U,      /* INT_FALLING_UNIT_2 */
    0x00000100U,      /* INT_OVERFLOW_UNIT_0 */
    0x00000200U,      /* INT_OVERFLOW_UNIT_1 */
    0x00000400U,      /* INT_OVERFLOW_UNIT_2 */
    0x00000777U       /* INT_ALL */
};

static uint32 Ctimer_IntMaskStatus = 0U;
/** @} end of group Private_VariableDefinition */

/** @defgroup Private_FunctionDeclaration
 *  @{
 */
void Ctimer_DriverIrqHandler(void);
/** @} end of group Private_FunctionDeclaration */

/** @defgroup Private_FunctionDefinition
 *  @{
 */
/**
 * @brief      Ctimer IrqHandler
 *
 * @param[in]  none
 *
 * @return     none
 *
 */ 
void Ctimer_DriverIrqHandler(void)
{
    uint32 IntStatus;
    uint32 CtimerIntType=0U;
    /* get interrupt status */
    IntStatus = Ctimer_RegWPtr->CTIMER_INT_STS; 
    /* only check enabled interrupts */
    IntStatus = IntStatus & Ctimer_IntMaskStatus;
    /* clear interrupt status */
    Ctimer_RegWPtr->CTIMER_INT_CLR = IntStatus;

    for (CtimerIntType = (uint32)CTIMER_INT_RISING_UNIT_0; CtimerIntType < (uint32)CTIMER_INT_ALL; CtimerIntType++)
    {
        if (0U != (IntStatus & (Ctimer_IntMaskTable[CtimerIntType])))
        {
            if(Ctimer_IsrCbFuncPtr[CtimerIntType] != NULL_PTR)
        {
            /* call the callback function */
            Ctimer_IsrCbFuncPtr[CtimerIntType]();
        }
        else
        {
        Ctimer_SetIntMask((Ctimer_IntType)CtimerIntType,COMMON_MASK);  
        }

        }
    }
}
/** @} end of group Private_FunctionDefinition */

/** @defgroup Public_FunctionDefinition
 *  @{
 */

/**
 * @brief      Ctimer Config Function
 *
 * @param[in]  Config: Pointer to a configuration structure.
 *
 * @return     None
 *
 */
void Ctimer_Config(const Ctimer_ConfigType * Config)
{
    uint8 Index;

    Ctimer_SetChannelFilter(Config->FilterType);
    Ctimer_SelectUnit1Channel(Config->ChannelType);

    for(Index = 0U; Index < Config->UnitNumber; Index++)
    {
        Ctimer_DetectEdgeMode(Config->UnitConfig[Index].UnitType, 
                                                      Config->UnitConfig[Index].DetectMode);
        Ctimer_TimerClearMode(Config->UnitConfig[Index].UnitType, 
                                                       Config->UnitConfig[Index].ClearMode);
        Ctimer_SetOverflowValue(Config->UnitConfig[Index].UnitType, 
                                                   Config->UnitConfig[Index].OverflowValue);
    }
}

/**
 * @brief      Module Enable Function
 *
 * @param[in]  None.
 *
 * @return     None
 *
 */
void Ctimer_Enable(void)
{
    Ctimer_RegBfPtr->CTIMER_CONF0.EN = 1U;
}

/**
 * @brief      Module Disable Function
 *
 * @param[in]  None.
 *
 * @return     None
 *
 */
void Ctimer_Disable(void)
{
    Ctimer_RegBfPtr->CTIMER_CONF0.EN = 0U;
}

/**
 * @brief      Set Channel Filter Function
 *
 * @param[in]  FilterType: Select channel filter type.
 *              - CTIMER_FILTER_DISABLE
 *              - CTIMER_FILTER_1
 *              - CTIMER_FILTER_2
 *              - CTIMER_FILTER_3
 *              - CTIMER_FILTER_4
 *              - CTIMER_FILTER_5
 *              - CTIMER_FILTER_6
 *              - CTIMER_FILTER_7
 *              - CTIMER_FILTER_8
 *              - CTIMER_FILTER_9
 *              - CTIMER_FILTER_10
 *              - CTIMER_FILTER_11
 *              - CTIMER_FILTER_12
 *              - CTIMER_FILTER_13
 *              - CTIMER_FILTER_14
 *              - CTIMER_FILTER_15
 *
 * @return     None
 *
 */
void Ctimer_SetChannelFilter(Ctimer_ChannelFilterType FilterType)
{
    Ctimer_RegBfPtr->CTIMER_CONF0.FILTER = (uint32)FilterType;
}

/**
 * @brief      Select Channel For Unit1 Function
 *
 * @param[in]  ChannelType: Select channel type.
 *              - CTIMER_CHANNEL_1
 *              - CTIMER_CHANNEL_2
 *              - CTIMER_CHANNEL_3
 *
 * @return     None
 *
 */
void Ctimer_SelectUnit1Channel(Ctimer_ChannelSelectionType ChannelType)
{
    Ctimer_RegBfPtr->CTIMER_CONF0.CH_SEL_TIM1 = (uint32)ChannelType;
}

/**
 * @brief      Detect Input Edge Mode Function
 *
 * @param[in]  UnitType: Select Unit type.
 *              - CTIMER_UNIT_0
 *              - CTIMER_UNIT_1
 *              - CTIMER_UNIT_2
 * @param[in]  EdgeType: Select Edge type.
 *              - CTIMER_EDGE_DISABLE
 *              - CTIMER_EDGE_RISING
 *              - CTIMER_EDGE_FALLING
 *              - CTIMER_EDGE_DUAL
 *
 * @return     None
 *
 */
void Ctimer_DetectEdgeMode(Ctimer_CaptureUnitType UnitType, Ctimer_EdgeType EdgeType)
{
    switch (UnitType)
    {
    case CTIMER_UNIT_0:
        Ctimer_RegBfPtr->CTIMER_CONF1.EDGE_MOD_0 = (uint32)EdgeType;
        break;
    
    case CTIMER_UNIT_1:
        Ctimer_RegBfPtr->CTIMER_CONF1.EDGE_MOD_1 = (uint32)EdgeType;
        break;
    
    case CTIMER_UNIT_2:
        Ctimer_RegBfPtr->CTIMER_CONF1.EDGE_MOD_2 = (uint32)EdgeType;
        break;
    
    default:
        /* do nothing */
        break;
    }
}

/**
 * @brief      Clear Input Edge Mode Function
 *
 * @param[in]  UnitType: Select Unit type.
 *              - CTIMER_UNIT_0
 *              - CTIMER_UNIT_1
 *              - CTIMER_UNIT_2
 * @param[in]  EdgeType: Select Edge type.
 *              - CTIMER_EDGE_DISABLE
 *              - CTIMER_EDGE_RISING
 *              - CTIMER_EDGE_FALLING
 *              - CTIMER_EDGE_DUAL
 *
 * @return     None
 *
 */
void Ctimer_TimerClearMode(Ctimer_CaptureUnitType UnitType, Ctimer_EdgeType EdgeType)
{ 
    switch (UnitType)
    {
    case CTIMER_UNIT_0:
        Ctimer_RegBfPtr->CTIMER_CONF1.TIM_CLR_SEL_0 = (uint32)EdgeType;
        break;
    
    case CTIMER_UNIT_1:
        Ctimer_RegBfPtr->CTIMER_CONF1.TIM_CLR_SEL_1 = (uint32)EdgeType;
        break;
    
    case CTIMER_UNIT_2:
        Ctimer_RegBfPtr->CTIMER_CONF1.TIM_CLR_SEL_2 = (uint32)EdgeType;
        break;
    
    default:
        /* do nothing */
        break;
    }
}

/**
 * @brief      Set Overflow Value Function
 *
 * @param[in]  UnitType: Select Unit type.
 *              - CTIMER_UNIT_0
 *              - CTIMER_UNIT_1
 *              - CTIMER_UNIT_2
 * @param[in]  Value: Overflow Value.
 *
 * @return     None
 *
 */
void Ctimer_SetOverflowValue(Ctimer_CaptureUnitType UnitType, uint16 Value)
{
    switch (UnitType)
    {
    case CTIMER_UNIT_0:
        Ctimer_RegBfPtr->CTIMER_OVF_0.OVF_0 = (uint32)Value;
        break;
    
    case CTIMER_UNIT_1:
        Ctimer_RegBfPtr->CTIMER_OVF_1.OVF_1 = (uint32)Value;
        break;
    
    case CTIMER_UNIT_2:
        Ctimer_RegBfPtr->CTIMER_OVF_2.OVF_2 = (uint32)Value;
        break;
    
    default:
        /* do nothing */
        break;
    }
}

/**
 * @brief      Get Rising Edge Capture Value Function
 *
 * @param[in]  UnitType: Select Unit type.
 *              - CTIMER_UNIT_0
 *              - CTIMER_UNIT_1
 *              - CTIMER_UNIT_2
 *
 * @return     uint16: Capture Value.
 *
 */
uint16 Ctimer_GetRisingCaptureValue(Ctimer_CaptureUnitType UnitType)
{
    uint16 CaptureValue = 0U;

    switch (UnitType)
    {
    case CTIMER_UNIT_0:
        CaptureValue = (uint16)Ctimer_RegBfPtr->CTIMER_RCAP_0.RCAP_0;
        break;
    
    case CTIMER_UNIT_1:
        CaptureValue = (uint16)Ctimer_RegBfPtr->CTIMER_RCAP_1.RCAP_1;
        break;
    
    case CTIMER_UNIT_2:
        CaptureValue = (uint16)Ctimer_RegBfPtr->CTIMER_RCAP_2.RCAP_2;
        break;
    
    default:
        /* do nothing */
        break;
    }

    return CaptureValue;
}

/**
 * @brief      Get Falling Edge Capture Value Function
 *
 * @param[in]  UnitType: Select Unit type.
 *              - CTIMER_UNIT_0
 *              - CTIMER_UNIT_1
 *              - CTIMER_UNIT_2
 *
 * @return     uint16: Capture Value.
 *
 */
uint16 Ctimer_GetFallingCaptureValue(Ctimer_CaptureUnitType UnitType)
{
    uint16 CaptureValue = 0U;

    switch (UnitType)
    {
    case CTIMER_UNIT_0:
        CaptureValue = (uint16)Ctimer_RegBfPtr->CTIMER_FCAP_0.FCAP_0;
        break;
    
    case CTIMER_UNIT_1:
        CaptureValue = (uint16)Ctimer_RegBfPtr->CTIMER_FCAP_1.FCAP_1;
        break;
    
    case CTIMER_UNIT_2:
        CaptureValue = (uint16)Ctimer_RegBfPtr->CTIMER_FCAP_2.FCAP_2;
        break;
    
    default:
        /* do nothing */
        break;
    }

    return CaptureValue;
}

/**
 * @brief      Ctimer Set INT Mask/Unmask Function
 *
 * @param[in]  IntType: Select Int type.
 *              - CTIMER_INT_RISING_UNIT_0
 *              - CTIMER_INT_RISING_UNIT_1
 *              - CTIMER_INT_RISING_UNIT_2
 *              - CTIMER_INT_FALLING_UNIT_0
 *              - CTIMER_INT_FALLING_UNIT_1
 *              - CTIMER_INT_FALLING_UNIT_2
 *              - CTIMER_INT_OVERFLOW_UNIT_0
 *              - CTIMER_INT_OVERFLOW_UNIT_1
 *              - CTIMER_INT_OVERFLOW_UNIT_2
 *              - CTIMER_INT_ALL
 * @param[in]  IntMask: Mask/Unmask.
 *              - COMMON_UNMASK
 *              - COMMON_MASK
 *
 * @return     None
 *
 */
void Ctimer_SetIntMask(Ctimer_IntType IntType, Common_IntMaskType IntMask)
{
    if(COMMON_UNMASK == IntMask)
    {
        Ctimer_IntMaskStatus = Ctimer_IntMaskStatus | Ctimer_IntStatusTable[IntType];
        Ctimer_RegWPtr->CTIMER_INT_CTRL = Ctimer_RegWPtr->CTIMER_INT_CTRL | 
                                                            Ctimer_IntMaskTable[IntType];
    }
    else
    {
        Ctimer_RegWPtr->CTIMER_INT_CTRL = Ctimer_RegWPtr->CTIMER_INT_CTRL & 
                                                         (~Ctimer_IntMaskTable[IntType]);
        Ctimer_IntMaskStatus = Ctimer_IntMaskStatus & (~Ctimer_IntStatusTable[IntType]);
    }
}

/**
 * @brief      Ctimer Clear INT Status Function
 *
 * @param[in]  IntType: Select Int type.
 *              - CTIMER_INT_RISING_UNIT_0
 *              - CTIMER_INT_RISING_UNIT_1
 *              - CTIMER_INT_RISING_UNIT_2
 *              - CTIMER_INT_FALLING_UNIT_0
 *              - CTIMER_INT_FALLING_UNIT_1
 *              - CTIMER_INT_FALLING_UNIT_2
 *              - CTIMER_INT_OVERFLOW_UNIT_0
 *              - CTIMER_INT_OVERFLOW_UNIT_1
 *              - CTIMER_INT_OVERFLOW_UNIT_2
 *              - CTIMER_INT_ALL
 *
 * @return     None
 *
 */
void Ctimer_ClearIntStatus(Ctimer_IntType IntType)
{
    Ctimer_RegWPtr->CTIMER_INT_CLR = Ctimer_IntStatusTable[IntType];
}

/**
 * @brief      Ctimer Get INT status Function
 *
 * @param[in]  IntType: Select Int type.
 *              - CTIMER_INT_RISING_UNIT_0
 *              - CTIMER_INT_RISING_UNIT_1
 *              - CTIMER_INT_RISING_UNIT_2
 *              - CTIMER_INT_FALLING_UNIT_0
 *              - CTIMER_INT_FALLING_UNIT_1
 *              - CTIMER_INT_FALLING_UNIT_2
 *              - CTIMER_INT_OVERFLOW_UNIT_0
 *              - CTIMER_INT_OVERFLOW_UNIT_1
 *              - CTIMER_INT_OVERFLOW_UNIT_2
 *              - CTIMER_INT_ALL
 *
 * @return     IntStatus
 *              - COMMON_RESET
 *              - COMMON_SET
 *
 */
Common_IntStatusType Ctimer_GetIntStatus(Ctimer_IntType IntType)
{
    Common_IntStatusType ReturnValue = COMMON_RESET;
   
    if((Ctimer_RegWPtr->CTIMER_INT_STS & Ctimer_IntStatusTable[IntType]) != 0UL)
    {
        ReturnValue = COMMON_SET;
    }

    return ReturnValue;
}


/**
 * @brief      Ctimer install interrupt callback function
 *
 * @param[in]  IntType: Select Int type.
 *              - CTIMER_INT_RISING_UNIT_0
 *              - CTIMER_INT_RISING_UNIT_1
 *              - CTIMER_INT_RISING_UNIT_2
 *              - CTIMER_INT_FALLING_UNIT_0
 *              - CTIMER_INT_FALLING_UNIT_1
 *              - CTIMER_INT_FALLING_UNIT_2
 *              - CTIMER_INT_OVERFLOW_UNIT_0
 *              - CTIMER_INT_OVERFLOW_UNIT_1
 *              - CTIMER_INT_OVERFLOW_UNIT_2
 * @param[in]  CbFun: Callback function .
 *
 * @return     None
 * @note       CTIMER_INT_ALL is invalid as input 
 */
void Ctimer_InstallCallBackFunc(Ctimer_IntType IntType, Isr_CbFuncType * CbFun)
{
    if(IntType < CTIMER_INT_ALL)
    {
        Ctimer_IsrCbFuncPtr[IntType] = CbFun;
    }
}

/** @} end of group Public_FunctionDefinition */
