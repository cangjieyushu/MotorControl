/**************************************************************************************************/
/**
 * @file      : Cmp_Drv.c
 * @brief     : CMP module driver file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
#include "Cmp_Drv.h"

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
static Reg_Cmp_BfType   *const Cmp_RegBfPtr  = (Reg_Cmp_BfType *) CMP_BASE_ADDR;
static Reg_Cmp_WType    *const Cmp_RegWPtr   = (Reg_Cmp_WType *) CMP_BASE_ADDR;
/*PRQA S 0303 --*/

static Isr_CbFuncType * Cmp_IsrCbFunc[CMP_INT_ALL] = 
{
    NULL_PTR, NULL_PTR
};


static const uint32 Cmp_IntMaskTable[] =
{
    0x00000001U,      /* CMP_INT_RAISE */
    0x00000002U,      /* CMP_INT_FALL */
    0x00000003U       /* CMP_INT_ALL */
};

static const uint32 Cmp_IntStatusTable[] =
{
    0x00000001U,      /* CMP_INT_RAISE */
    0x00000002U,      /* CMP_INT_FALL */
    0x00000003U       /* CMP_INT_ALL */
};

static uint32 Cmp_IntMaskStatus = 0U;
/** @} end of group Private_VariableDefinition */

/** @defgroup Private_FunctionDeclaration
 *  @{
 */
void Cmp_DriverIRQHandler(void);
/** @} end of group Private_FunctionDeclaration */

/** @defgroup Private_FunctionDefinition
 *  @{
 */
/**
 * @brief      CMP IRQHandler
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void Cmp_DriverIRQHandler(void)
{
    uint32 IntStatus;
    uint32 IntType;
    
    IntStatus = Cmp_RegWPtr->CMP_CSR;
    /* get status */
    IntStatus = IntStatus & Cmp_IntMaskStatus;
    /* clear int status */
    Cmp_RegWPtr->CMP_CSR = IntStatus;
    
    for(IntType = (uint32)CMP_INT_RAISE; IntType < (uint32)CMP_INT_ALL; IntType++)
    {
        if((IntStatus & (0x00000001UL << IntType)) != 0U)
        {
            if(Cmp_IsrCbFunc[IntType] != NULL_PTR)
            {
                Cmp_IsrCbFunc[IntType]();
            }
            else
            {
                Cmp_RegWPtr->CMP_IER &= ~(0x00000001UL << IntType); 
            }
        }
    }
}
/** @} end of group Private_FunctionDefinition */

/** @defgroup Public_FunctionDefinition
 *  @{
 */
/**
 * @brief      Initialize CMP
 * @param[in]  ConfigPtr: the configuration parameters.
 * @return     none
 *
 */
void Cmp_Init(const Cmp_ConfigType *ConfigPtr)
{
    Cmp_RegBfPtr->CMP_CCR2.HS_PSEL = (uint32)(ConfigPtr->PositiveInput);
    Cmp_RegBfPtr->CMP_CCR2.HS_MSEL = (uint32)(ConfigPtr->NegativeInput);
    Cmp_RegBfPtr->CMP_CCR2.HS_HSTCTR = (uint32)(ConfigPtr->Hysteresis);
    Cmp_RegBfPtr->CMP_CCR2.HS_MODE   = (uint32)(ConfigPtr->SpeedMode);
    
    /* invert output or not */
    Cmp_RegBfPtr->CMP_CCR1.COUT_INV = (uint32)(ConfigPtr->InvertEnable);
}

/**
 * @brief      Config filter parameters
 *
 * @param[in]  Count: the consecutive sample count number that agree the output 
 *                  value to be changed. The range is 0 ~ 255. If it is 0, the 
 *                  filter is bypassed.
 *
 * @return     None
 *
 */
void Cmp_ConfigFilterCount(uint32 Count)
{
    Cmp_RegBfPtr->CMP_CCR1.FILT_CNT = (uint32)Count;    
}

/**
 * @brief      Initialize DAC
 *
 * @param[in]  Vref: Select the reference voltage
 *                     - CMP_DAC_VREF_VDDA
 *                     - CMP_DAC_VREF_VREFH
 *
 * @return     None
 *
 */   
void Cmp_SetDacRefVoltage(Cmp_DacVrefVoltageType Vref)
{
    Cmp_RegBfPtr->CMP_DCR.VREF_SEL = (uint32)Vref;
}

/**
 * @brief      Set DAC output type
 *
 * @param[in]  OutputType: DAC output type
 *                          - CMP_DAC_NOT_OUTPUT
 *                          - CMP_DAC_UNBUFFERED_OUTPUT
 *                          - CMP_DAC_BUFFERED_OUTPUT
 *
 * @return     None
 *
 */   
void Cmp_SetDacOutputType(Cmp_DacOutputType OutputType)
{
    Cmp_RegBfPtr->CMP_DCR.DAC_OUT_SEL = (uint32)OutputType;
}

/**
 * @brief      Enable DAC 
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void Cmp_EnableDac(void)
{
    Cmp_RegBfPtr->CMP_DCR.DAC_EN = 1U;
}

/**
 * @brief      Disable DAC
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void Cmp_DisableDac(void)
{
    Cmp_RegBfPtr->CMP_DCR.DAC_EN = 0U;
}

/**
 * @brief      set DAC output value
 *
 * @param[in]  Data: the data to be converted. The range is 0 - 0xFF.
 *
 * @return     None
 *
 */
void Cmp_SetDacValue(uint8 Data)
{
    Cmp_RegBfPtr->CMP_DCR.DAC_SEL = Data;
}

/**
 * @brief      Trigger CMP
 *
 * @param[in]  none
 *
 * @return     none
 *
 */ 
void Cmp_EnableCmp(void)
{
    Cmp_RegBfPtr->CMP_CCR0.CMP_EN = 1U;
}

/**
 * @brief      Disable CMP
 *
 * @param[in]  none
 *
 * @return     none
 *
 */ 
void Cmp_DisableCmp(void)
{
    Cmp_RegBfPtr->CMP_CCR0.CMP_EN = 0U;
}

/**
 * @brief      Get CMP output value
 *
 * @param[in]  none
 *
 * @return     CMP Out Voltage Level
 * @retval     COMMON_LEVEL_LOW: - low level
 * @retval     COMMON_LEVEL_HIGH: - high level
 *
 */
Common_LevelType Cmp_GetOutput(void)
{
    return (Common_LevelType)Cmp_RegBfPtr->CMP_CSR.COUT;
}

/**
 * @brief      Install callback function
 *
 * @param[in]  IntType: select interrupt type
 * @param[in]  CallbackFun: indicate callback function
 *
 * @return    none
 * @note      CMP_INT_ALL is invalid as input
 */ 
void Cmp_InstallCallBackFunc(Cmp_InterruptType IntType, Isr_CbFuncType * CallbackFun)
{
    if(IntType < CMP_INT_ALL)
    {
        Cmp_IsrCbFunc[IntType] = CallbackFun;
    }
    else
    {
        /* do nothing */
    }
}

/**
 * @brief      Mask/Unmask interrupt
 *
 * @param[in]  IntType: select interrupt type
 *                        - CMP_INT_RAISE
 *                        - CMP_INT_FALL
 *                        - CMP_INT_ALL
 * @param[in]  IntMask: 
 *                        - MASK
 *                        - UNMASK
 *
 * @return    none
 *
 */
void Cmp_SetIntMask(Cmp_InterruptType IntType, Common_IntMaskType IntMask)
{
    if(COMMON_UNMASK == IntMask)
    {
        Cmp_IntMaskStatus    |= Cmp_IntStatusTable[IntType];
        Cmp_RegWPtr->CMP_IER |= Cmp_IntMaskTable[IntType];
    }
    else
    {
        Cmp_RegWPtr->CMP_IER &= ~Cmp_IntMaskTable[IntType];
        Cmp_IntMaskStatus    &= ~Cmp_IntStatusTable[IntType];
    }
}

/**
 * @brief      Clear interrupt
 *
 * @param[in]  IntType: select interrupt type
 *                        - CMP_INT_RAISE
 *                        - CMP_INT_FALL
 *                        - CMP_INT_ALL
 *
 * @return    none
 *
 */ 
void Cmp_ClearInt(Cmp_InterruptType IntType)
{
    /* get interrupt status */
    uint32 Intstatus = Cmp_RegWPtr->CMP_CSR;
    /* make sure interrupt is enable */
    Intstatus = Intstatus & Cmp_IntStatusTable[IntType];

    Cmp_RegWPtr->CMP_CSR = Intstatus;
}

/** @} end of group Public_FunctionDefinition */
