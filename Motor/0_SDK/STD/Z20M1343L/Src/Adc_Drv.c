/**************************************************************************************************/
/**
 * @file      : Adc_Drv.c
 * @brief     : Adc module driver file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
#include "Adc_Drv.h"

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
static Reg_Adc_BfType * const Adc_RegBfPtr = (Reg_Adc_BfType *)ADC_BASE_ADDR;
static Reg_Adc_WType * const Adc_RegWPtr = (Reg_Adc_WType *)ADC_BASE_ADDR;
/*PRQA S 0303 --*/

static Isr_CbFuncType * Adc_IsrCbFuncPtr[ADC_INT_ALL] = 
{
    NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR,
    NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR,
    NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR
};


static const uint32 Adc_IntMaskTable[] = 
{
    0x00000004U,                            /*!< ADC_INT_AWDG_UNDER */
    0x00000008U,                            /*!< ADC_INT_AWDG_OVER */
    0x00000010U,                            /*!< ADC_INT_GRP0_LOOP_SCOM */
    0x00000020U,                            /*!< ADC_INT_GRP0_MAP_SCOM */
    0x00000040U,                            /*!< ADC_INT_GRP0_CCOM0 */
    0x00000080U,                            /*!< ADC_INT_GRP0_CCOM1 */
    0x00000100U,                            /*!< ADC_INT_GRP0_CCOM2 */
    0x00000200U,                            /*!< ADC_INT_GRP0_CCOM3 */
    0x00000400U,                            /*!< ADC_INT_GRP0_CCOM4 */
    0x00000800U,                            /*!< ADC_INT_GRP0_CCOM5 */
    0x00001000U,                            /*!< ADC_INT_GRP0_CCOM6 */
    0x00002000U,                            /*!< ADC_INT_GRP0_CCOM7 */
    0x00004000U,                            /*!< ADC_INT_GRP1_SCOM0 */
    0x00008000U,                            /*!< ADC_INT_GRP1_SCOM1 */
    0x00010000U,                            /*!< ADC_INT_GRP1_SCOM2 */
    0x00020000U,                            /*!< ADC_INT_GRP1_ALL_COM */
    0x00040000U,                            /*!< ADC_INT_GRP0_LOOP_ABORT */
    0x00080000U,                            /*!< ADC_INT_GRP1_LOOP_ABORT */
    0x00100000U,                            /*!< ADC_INT_TRIG_CERR */
    0x00200000U,                            /*!< ADC_INT_GDU_OT */
    0x00400000U,                            /*!< ADC_INT_PMU_OT */
    0x00800000U,                            /*!< ADC_INT_MEAS_TRIG */
    0x00FFFFFCU                             /*!< ADC_INT_ALL */
};

static const uint32 Adc_IntStatusTable[] = 
{
    0x00000004U,                            /*!< ADC_INT_AWDG_UNDER */
    0x00000008U,                            /*!< ADC_INT_AWDG_OVER */
    0x00000010U,                            /*!< ADC_INT_GRP0_LOOP_SCOM */
    0x00000020U,                            /*!< ADC_INT_GRP0_MAP_SCOM */
    0x00000040U,                            /*!< ADC_INT_GRP0_CCOM0 */
    0x00000080U,                            /*!< ADC_INT_GRP0_CCOM1 */
    0x00000100U,                            /*!< ADC_INT_GRP0_CCOM2 */
    0x00000200U,                            /*!< ADC_INT_GRP0_CCOM3 */
    0x00000400U,                            /*!< ADC_INT_GRP0_CCOM4 */
    0x00000800U,                            /*!< ADC_INT_GRP0_CCOM5 */
    0x00001000U,                            /*!< ADC_INT_GRP0_CCOM6 */
    0x00002000U,                            /*!< ADC_INT_GRP0_CCOM7 */
    0x00004000U,                            /*!< ADC_INT_GRP1_SCOM0 */
    0x00008000U,                            /*!< ADC_INT_GRP1_SCOM1 */
    0x00010000U,                            /*!< ADC_INT_GRP1_SCOM2 */
    0x00020000U,                            /*!< ADC_INT_GRP1_ALL_COM */
    0x00040000U,                            /*!< ADC_INT_GRP0_LOOP_ABORT */
    0x00080000U,                            /*!< ADC_INT_GRP1_LOOP_ABORT */
    0x00100000U,                            /*!< ADC_INT_TRIG_CERR */
    0x00200000U,                            /*!< ADC_INT_GDU_OT */
    0x00400000U,                            /*!< ADC_INT_PMU_OT */
    0x00800000U,                            /*!< ADC_INT_MEAS_TRIG */
    0x00FFFFFCU                             /*!< ADC_INT_ALL */
};

static const uint32 Adc_StatusTable[] =
{
    0x00000001U,                            /*!< ADC_STATUS_DMA_REQ */
    0x00000002U,                            /*!< ADC_STATUS_AWDG_FAIL */
    0x00000004U,                            /*!< ADC_STATUS_AWDG_UNDER */
    0x00000008U,                            /*!< ADC_STATUS_AWDG_OVER */
    0x00000010U,                            /*!< ADC_STATUS_GRP0_LOOP_SCOM */
    0x00000020U,                            /*!< ADC_STATUS_GRP0_MAP_SCOM */
    0x00000040U,                            /*!< ADC_STATUS_GRP0_CCOM0 */
    0x00000080U,                            /*!< ADC_STATUS_GRP0_CCOM1 */
    0x00000100U,                            /*!< ADC_STATUS_GRP0_CCOM2 */
    0x00000200U,                            /*!< ADC_STATUS_GRP0_CCOM3 */
    0x00000400U,                            /*!< ADC_STATUS_GRP0_CCOM4 */
    0x00000800U,                            /*!< ADC_STATUS_GRP0_CCOM5 */
    0x00001000U,                            /*!< ADC_STATUS_GRP0_CCOM6 */
    0x00002000U,                            /*!< ADC_STATUS_GRP0_CCOM7 */
    0x00004000U,                            /*!< ADC_STATUS_GRP1_SCOM0 */
    0x00008000U,                            /*!< ADC_STATUS_GRP1_SCOM1 */
    0x00010000U,                            /*!< ADC_STATUS_GRP1_SCOM2 */
    0x00020000U,                            /*!< ADC_STATUS_GRP1_ALL_COM */
    0x00040000U,                            /*!< ADC_STATUS_GRP0_LOOP_ABORT */
    0x00080000U,                            /*!< ADC_STATUS_GRP1_LOOP_ABORT */
    0x00100000U,                            /*!< ADC_STATUS_TRIG_CERR */
    0x00200000U,                            /*!< ADC_STATUS_GDU_OT */
    0x00400000U,                            /*!< ADC_STATUS_PMU_OT */
    0x00800000U,                            /*!< ADC_STATUS_MEAS_TRIG */
    0x08000000U,                            /*!< ADC_STATUS_PMU_DIS */
    0x10000000U,                            /*!< ADC_STATUS_GRP0_BUSY */
    0x20000000U,                            /*!< ADC_STATUS_GRP1_BUSY */
    0x40000000U,                            /*!< ADC_STATUS_SAR_BUSY */
    0x80000000U,                            /*!< ADC_STATUS_PWON */
    0xF8FFFFFFU                             /*!< ADC_STATUS_ALL */
};

static const uint32 Adc_IntStatusClearTable[] = 
{
    0x000000C0U,                            /*!< ADC_INT_GRP0_CCOM0 and ADC_INT_GRP0_CCOM1 */    
    0x00000300U,                            /*!< ADC_INT_GRP0_CCOM2 and ADC_INT_GRP0_CCOM3 */
    0x00000C00U,                            /*!< ADC_INT_GRP0_CCOM4 and ADC_INT_GRP0_CCOM5 */
    0x00003000U,                            /*!< ADC_INT_GRP0_CCOM6 and ADC_INT_GRP0_CCOM7 */
    0x00000020U,                            /*!< ADC_INT_GRP0_MAP_SCOM */
    0x00000010U,                            /*!< ADC_INT_GRP0_LOOP_SCOM */
    0x00000008U,                            /*!< ADC_INT_AWDG_OVER */
    0x00000004U,                            /*!< ADC_INT_AWDG_UNDER */
    0x00800000U,                            /*!< ADC_INT_MEAS_TRIG */
    0x001FC000U                             /*!< ADC_STATUS_GRP1_SCOM0/1/2, ADC_STATUS_GRP1_ALL_COM,
                     ADC_STATUS_GRP0_LOOP_ABORT, ADC_STATUS_GRP1_LOOP_ABORT, ADC_STATUS_TRIG_CERR */
};

static uint32 Adc_IntMaskStatus = 0U;
/** @} end of group Private_VariableDefinition */

/** @defgroup Private_FunctionDeclaration
 *  @{
 */
void Adc_Ccomp01_DriverIrqHandler(void);
void Adc_Ccomp23_DriverIrqHandler(void);
void Adc_Ccomp45_DriverIrqHandler(void);
void Adc_Ccomp67_DriverIrqHandler(void);
void Adc_MapScomp_DriverIrqHandler(void);
void Adc_LoopScomp_DriverIrqHandler(void);
void Adc_AwdgOver_DriverIrqHandler(void);
void Adc_AwdgUnder_DriverIrqHandler(void);
void Adc_MeasureTimer_DriverIrqHandler(void);
void Adc_Error_DriverIrqHandler(void);
/** @} end of group Private_FunctionDeclaration */

/** @defgroup Private_FunctionDefinition
 *  @{
 */
/**
 * @brief      ADC convert complete 0-1 IrqHandler
 *
 * @param[in]  none
 *
 * @return     none
 *
 */ 
void Adc_Ccomp01_DriverIrqHandler(void)
{
    uint32 IntStatus;

    /* get interrupt status */
    IntStatus = Adc_RegWPtr->ADC_STAT; 
    /* only check enabled interrupts */
    IntStatus = IntStatus & Adc_IntMaskStatus;
    /* clear Command0 and Command1 interrupt status */
    Adc_RegWPtr->ADC_STAT = IntStatus & Adc_IntStatusClearTable[0];

    /* Group0 Command0 Complete Interrupt */
    if((IntStatus & Adc_IntStatusTable[ADC_INT_GRP0_CCOM0]) != 0U)
    {
        if(Adc_IsrCbFuncPtr[ADC_INT_GRP0_CCOM0] != NULL_PTR)
        {
            /* call the callback function */
            Adc_IsrCbFuncPtr[ADC_INT_GRP0_CCOM0]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            Adc_RegBfPtr->ADC_IE.CCOM0_INT_EN = 0U;
        }
    }
    
    /* Group0 Command1 Complete Interrupt */
    if((IntStatus & Adc_IntStatusTable[ADC_INT_GRP0_CCOM1]) != 0U)
    {
        if(Adc_IsrCbFuncPtr[ADC_INT_GRP0_CCOM1] != NULL_PTR)
        {
            /* call the callback function */
            Adc_IsrCbFuncPtr[ADC_INT_GRP0_CCOM1]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            Adc_RegBfPtr->ADC_IE.CCOM1_INT_EN = 0U;
        }
    }
}

/**
 * @brief      ADC convert complete 2-3 IrqHandler
 *
 * @param[in]  none
 *
 * @return     none
 *
 */ 
void Adc_Ccomp23_DriverIrqHandler(void)
{
    uint32 IntStatus;

    /* get interrupt status */
    IntStatus = Adc_RegWPtr->ADC_STAT; 
    /* only check enabled interrupts */
    IntStatus = IntStatus & Adc_IntMaskStatus;
    /* clear Command2 and Command3 interrupt status */
    Adc_RegWPtr->ADC_STAT = IntStatus & Adc_IntStatusClearTable[1];

    /* Group0 Command2 Complete Interrupt */
    if((IntStatus & Adc_IntStatusTable[ADC_INT_GRP0_CCOM2]) != 0U)
    {
        if(Adc_IsrCbFuncPtr[ADC_INT_GRP0_CCOM2] != NULL_PTR)
        {
            /* call the callback function */
            Adc_IsrCbFuncPtr[ADC_INT_GRP0_CCOM2]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            Adc_RegBfPtr->ADC_IE.CCOM2_INT_EN = 0U;
        }
    }
    
    /* Group0 Command3 Complete Interrupt */
    if((IntStatus & Adc_IntStatusTable[ADC_INT_GRP0_CCOM3]) != 0U)
    {
        if(Adc_IsrCbFuncPtr[ADC_INT_GRP0_CCOM3] != NULL_PTR)
        {
            /* call the callback function */
            Adc_IsrCbFuncPtr[ADC_INT_GRP0_CCOM3]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            Adc_RegBfPtr->ADC_IE.CCOM3_INT_EN = 0U;
        }
    }
}

/**
 * @brief      ADC convert complete 4-5 IrqHandler
 *
 * @param[in]  none
 *
 * @return     none
 *
 */ 
void Adc_Ccomp45_DriverIrqHandler(void)
{
    uint32 IntStatus;

    /* get interrupt status */
    IntStatus = Adc_RegWPtr->ADC_STAT; 
    /* only check enabled interrupts */
    IntStatus = IntStatus & Adc_IntMaskStatus;
    /* clear Command4 and Command5 interrupt status */
    Adc_RegWPtr->ADC_STAT = IntStatus & Adc_IntStatusClearTable[2];

    /* Group0 Command4 Complete Interrupt */
    if((IntStatus & Adc_IntStatusTable[ADC_INT_GRP0_CCOM4]) != 0U)
    {
        if(Adc_IsrCbFuncPtr[ADC_INT_GRP0_CCOM4] != NULL_PTR)
        {
            /* call the callback function */
            Adc_IsrCbFuncPtr[ADC_INT_GRP0_CCOM4]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            Adc_RegBfPtr->ADC_IE.CCOM4_INT_EN = 0U;
        }
    }
    
    /* Group0 Command5 Complete Interrupt */
    if((IntStatus & Adc_IntStatusTable[ADC_INT_GRP0_CCOM5]) != 0U)
    {
        if(Adc_IsrCbFuncPtr[ADC_INT_GRP0_CCOM5] != NULL_PTR)
        {
            /* call the callback function */
            Adc_IsrCbFuncPtr[ADC_INT_GRP0_CCOM5]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            Adc_RegBfPtr->ADC_IE.CCOM5_INT_EN = 0U;
        }
    }
}

/**
 * @brief      ADC convert complete 6-7 IrqHandler
 *
 * @param[in]  none
 *
 * @return     none
 *
 */ 
void Adc_Ccomp67_DriverIrqHandler(void)
{
    uint32 IntStatus;

    /* get interrupt status */
    IntStatus = Adc_RegWPtr->ADC_STAT; 
    /* only check enabled interrupts */
    IntStatus = IntStatus & Adc_IntMaskStatus;
    /* clear Command6 and Command7 interrupt status */
    Adc_RegWPtr->ADC_STAT = IntStatus & Adc_IntStatusClearTable[3];

    /* Group0 Command6 Complete Interrupt */
    if((IntStatus & Adc_IntStatusTable[ADC_INT_GRP0_CCOM6]) != 0U)
    {
        if(Adc_IsrCbFuncPtr[ADC_INT_GRP0_CCOM6] != NULL_PTR)
        {
            /* call the callback function */
            Adc_IsrCbFuncPtr[ADC_INT_GRP0_CCOM6]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            Adc_RegBfPtr->ADC_IE.CCOM6_INT_EN = 0U;
        }
    }
    
    /* Group0 Command7 Complete Interrupt */
    if((IntStatus & Adc_IntStatusTable[ADC_INT_GRP0_CCOM7]) != 0U)
    {
        if(Adc_IsrCbFuncPtr[ADC_INT_GRP0_CCOM7] != NULL_PTR)
        {
            /* call the callback function */
            Adc_IsrCbFuncPtr[ADC_INT_GRP0_CCOM7]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            Adc_RegBfPtr->ADC_IE.CCOM7_INT_EN = 0U;
        }
    }
}

/**
 * @brief      ADC mapping complete IrqHandler
 *
 * @param[in]  none
 *
 * @return     none
 *
 */ 
void Adc_MapScomp_DriverIrqHandler(void)
{
    uint32 IntStatus;

    /* get interrupt status */
    IntStatus = Adc_RegWPtr->ADC_STAT; 
    /* only check enabled interrupts */
    IntStatus = IntStatus & Adc_IntMaskStatus;
    /* clear Group0 Map Sequence Complete interrupt status */
    Adc_RegWPtr->ADC_STAT = IntStatus & Adc_IntStatusClearTable[4];

    /* Group0 Map Sequence Complete Interrupt */
    if((IntStatus & Adc_IntStatusTable[ADC_INT_GRP0_MAP_SCOM]) != 0U)
    {
        if(Adc_IsrCbFuncPtr[ADC_INT_GRP0_MAP_SCOM] != NULL_PTR)
        {
            /* call the callback function */
            Adc_IsrCbFuncPtr[ADC_INT_GRP0_MAP_SCOM]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            Adc_RegBfPtr->ADC_IE.GRP0_MAP_SCOM_EN = 0U;
        }
    }
}

/**
 * @brief      ADC loop complete IrqHandler
 *
 * @param[in]  none
 *
 * @return     none
 *
 */ 
void Adc_LoopScomp_DriverIrqHandler(void)
{
    uint32 IntStatus;

    /* get interrupt status */
    IntStatus = Adc_RegWPtr->ADC_STAT; 
    /* only check enabled interrupts */
    IntStatus = IntStatus & Adc_IntMaskStatus;
    /* clear Group0 LOOP Complete interrupt status */
    Adc_RegWPtr->ADC_STAT = IntStatus & Adc_IntStatusClearTable[5];

    /* Group0 LOOP Complete Interrupt */
    if((IntStatus & Adc_IntStatusTable[ADC_INT_GRP0_LOOP_SCOM]) != 0U)
    {
        if(Adc_IsrCbFuncPtr[ADC_INT_GRP0_LOOP_SCOM] != NULL_PTR)
        {
            /* call the callback function */
            Adc_IsrCbFuncPtr[ADC_INT_GRP0_LOOP_SCOM]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            Adc_RegBfPtr->ADC_IE.GRP0_LOOP_SCOM_EN = 0U;
        }
    }
}

/**
 * @brief      ADC awdg over IrqHandler
 *
 * @param[in]  none
 *
 * @return     none
 *
 */ 
void Adc_AwdgOver_DriverIrqHandler(void)
{
    uint32 IntStatus;

    /* get interrupt status */
    IntStatus = Adc_RegWPtr->ADC_STAT; 
    /* only check enabled interrupts */
    IntStatus = IntStatus & Adc_IntMaskStatus;

    /* Analog Watchdog over interrupt */
    if((IntStatus & Adc_IntStatusTable[ADC_INT_AWDG_OVER]) != 0U)
    {
        if(Adc_IsrCbFuncPtr[ADC_INT_AWDG_OVER] != NULL_PTR)
        {
            /* call the callback function */
            Adc_IsrCbFuncPtr[ADC_INT_AWDG_OVER]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            Adc_RegBfPtr->ADC_IE.AWDG_OVER_INT_EN = 0U;
        }

        /* clear Analog Watchdog over interrupt status */
        Adc_RegWPtr->ADC_STAT = IntStatus & Adc_IntStatusClearTable[6];
    }
}

/**
 * @brief      ADC awdg under IrqHandler
 *
 * @param[in]  none
 *
 * @return     none
 *
 */ 
void Adc_AwdgUnder_DriverIrqHandler(void)
{
    uint32 IntStatus;

    /* get interrupt status */
    IntStatus = Adc_RegWPtr->ADC_STAT; 
    /* only check enabled interrupts */
    IntStatus = IntStatus & Adc_IntMaskStatus;

    /* Analog Watchdog under interrupt */
    if((IntStatus & Adc_IntStatusTable[ADC_INT_AWDG_UNDER]) != 0U)
    {
        if(Adc_IsrCbFuncPtr[ADC_INT_AWDG_UNDER] != NULL_PTR)
        {
            /* call the callback function */
            Adc_IsrCbFuncPtr[ADC_INT_AWDG_UNDER]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            Adc_RegBfPtr->ADC_IE.AWDG_UNDER_INT_EN = 0U;
        }

        /* clear Analog Watchdog under interrupt status */
        Adc_RegWPtr->ADC_STAT = IntStatus & Adc_IntStatusClearTable[7];
    }
}

/**
 * @brief      ADC measure timer IrqHandler
 *
 * @param[in]  none
 *
 * @return     none
 *
 */ 
void Adc_MeasureTimer_DriverIrqHandler(void)
{
    uint32 IntStatus;

    /* get interrupt status */
    IntStatus = Adc_RegWPtr->ADC_STAT; 
    /* only check enabled interrupts */
    IntStatus = IntStatus & Adc_IntMaskStatus;
    /* clear Measure Counter Trig Interrupt status */
    Adc_RegWPtr->ADC_STAT = IntStatus & Adc_IntStatusClearTable[8];

    /* Measure Counter Trig Interrupt */
    if((IntStatus & Adc_IntStatusTable[ADC_INT_MEAS_TRIG]) != 0U)
    {
        if(Adc_IsrCbFuncPtr[ADC_INT_MEAS_TRIG] != NULL_PTR)
        {
            /* call the callback function */
            Adc_IsrCbFuncPtr[ADC_INT_MEAS_TRIG]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            Adc_RegBfPtr->ADC_IE.MEAS_TRIG_INT_EN = 0U;
        }
    }
}

/**
 * @brief      ADC error IrqHandler
 *
 * @param[in]  none
 *
 * @return     none
 *
 */ 
void Adc_Error_DriverIrqHandler(void)
{
    uint32 IntStatus;
    uint32 LocalIter = 0U;

    /* get interrupt status */
    IntStatus = Adc_RegWPtr->ADC_STAT; 
    /* only check enabled interrupts */
    IntStatus = IntStatus & Adc_IntMaskStatus;
    /* clear ADC_STATUS_GRP1_SCOM0/1/2, ADC_STATUS_GRP1_ALL_COM,
       ADC_STATUS_GRP0_LOOP_ABORT, ADC_STATUS_GRP1_LOOP_ABORT, ADC_STATUS_TRIG_CERR status */
    Adc_RegWPtr->ADC_STAT = IntStatus & Adc_IntStatusClearTable[9];

    /* Handle Sequence 0 - 2, and All Group, and ADC_INT_GRP0_LOOP_ABORT, and
      ADC_INT_GRP1_LOOP_ABORT, and ADC_INT_TRIG_CERR */
    for( LocalIter = (uint32)ADC_INT_GRP1_SCOM0; 
        LocalIter <= (uint32)ADC_INT_TRIG_CERR; LocalIter++ )
    {
        if((IntStatus & Adc_IntStatusTable[LocalIter]) != 0U)
        {
            if(Adc_IsrCbFuncPtr[LocalIter] != NULL_PTR)
            {
                /* call the callback function */
                Adc_IsrCbFuncPtr[LocalIter]();
            }
            /* Disable the interrupt if callback function is not setup */
            else
            {
                Adc_RegWPtr->ADC_IE &= (~Adc_IntMaskTable[LocalIter]);
            }
        }
    }
}

/** @} end of group Private_FunctionDefinition */

/** @defgroup Public_FunctionDefinition
 *  @{
 */
/**
 * @brief      Adc Config Self Test Function
 *
 * @param[in]  Config: Pointer to a Self Test configuration structure.
 *
 * @return     None
 *
 */
void Adc_ConfigSelfTest(const Adc_SelfTestConfigType * Config)
{
    Adc_RegBfPtr->ADC_SELF_TEST_CFG.CUT = (uint32)Config->CapSelect;
    Adc_RegBfPtr->ADC_SELF_TEST_CFG.TESTPOL = (uint32)Config->VoltageSelect;
    Adc_RegBfPtr->ADC_SELF_TEST_CFG.TEST = (uint32)Config->TestEnable;
}

/**
 * @brief      Adc Config Measure Timer Function
 *
 * @param[in]  Config: Pointer to a Measure Module configuration structure.
 *
 * @return     None
 *
 */
void Adc_ConfigMeasureTimer(const Adc_MeasureConfigType * Config)
{
    if(0U == Config->ReloadValue)
    {
        /* It is at least 1 */
        Adc_RegBfPtr->ADC_MEAS_TRIG.RELOAD_VAL = 1U;
    }
    else
    {
        Adc_RegBfPtr->ADC_MEAS_TRIG.RELOAD_VAL = (uint32)Config->ReloadValue;
    }  
    Adc_RegBfPtr->ADC_MEAS_TRIG.TRIG_EN = (uint32)Config->TriggerEnable;
}

/**
 * @brief      Adc Start Or Stop Measure Timer Function
 *
 * @param[in]  Cmd: Select Disable Or Enable.
 *              - COMMON_DISABLE: Stop measuring timer.
 *              - COMMON_ENABLE: Start measuring timer.
 *
 * @return     None
 *
 */
void Adc_EnableMeasureTimer(Common_ControlStateType Cmd)
{
    Adc_RegBfPtr->ADC_MEAS_TRIG.MOD_EN = (uint32)Cmd;
}

/**
 * @brief      Adc Generate Measure Interrupt Or Flag Function
 *
 * @param[in]  None.
 *
 * @return     None
 *
 */
void Adc_GenerateMeasureFlag(void)
{
    Adc_RegBfPtr->ADC_MEAS_TRIG.SW_TRIG_INT = 1U;
}

/**
 * @brief      Adc Enable Function
 *
 * @param[in]  None.
 *
 * @return     Result Status:
 *              - COMMON_SUCC: Adc Enable Success
 *              - COMMON_ERR: ADC Enable Failed
 */
Common_ResultStatusType Adc_Enable(void)
{
    Common_ResultStatusType ReturnValue = COMMON_SUCC;

    Adc_RegBfPtr->ADC_CTRL.ADC_EN = 1U;

    if(Adc_RegBfPtr->ADC_CTRL.ADC_EN != 1U)
    { 
        ReturnValue = COMMON_ERR;
    }

    return ReturnValue;
}

/**
 * @brief      Adc Disable Function
 *
 * @param[in]  None.
 *
 * @return     None
 *
 */
void Adc_Disable(void)
{
    Adc_RegBfPtr->ADC_CTRL.ADC_EN = 0U;
}

/**
 * @brief      Adc Software Reset Function
 *
 * @param[in]  None.
 *
 * @return     None
 *
 */
void Adc_ResetSw(void)
{
    volatile uint32 Index = 0U;
    
    Adc_RegBfPtr->ADC_CTRL.RST = 1U;
    
    while(Index < ADC_TIMEOUT_WAIT_CNT_SWRST)
    {
        Index++;
    }
}

/**
 * @brief      Adc Reset(Terminate) Loop For Group Sequence Conversion Function
 *
 * @param[in]  GroupType: Select the Group Type.
 *              - ADC0_GROUP_0
 *              - ADC0_GROUP_1
 *
 * @return     None
 *
 */
void Adc_ResetGroupLoop(Adc_GroupType GroupType)
{
    switch (GroupType)
    {
    case ADC0_GROUP_0:
        Adc_RegBfPtr->ADC_CTRL.GRP0_ABORT = 1U;
        break;
    
    case ADC0_GROUP_1:
        Adc_RegBfPtr->ADC_CTRL.GRP1_ABORT = 1U;
        break;

    default:
        /* do nothing */
        break;
    }
}

/**
 * @brief      Adc Software Trigger Loop For Group Sequence Conversion Function
 *
 * @param[in]  GroupType: Select the Group Type.
 *              - ADC0_GROUP_0
 *              - ADC0_GROUP_1
 *
 * @return     None
 *
 */
void Adc_TriggerSwLoop(Adc_GroupType GroupType)
{
    switch (GroupType)
    {
    case ADC0_GROUP_0:
        Adc_RegBfPtr->ADC_SWTRIG.ADC_SWTRIG0 = 1U;
        break;
    
    case ADC0_GROUP_1:
        Adc_RegBfPtr->ADC_SWTRIG.ADC_SWTRIG_MEAS = 1U;
        break;

    default:
        /* do nothing */
        break;
    }
}

/**
 * @brief      Adc Software Trigger Map For Group0 Conversion Function
 *
 * @param[in]  MapTriggerType: Select the Map Trigger Type.
 *              - ADC_MAP_TRIGGER_CMD0
 *              - ADC_MAP_TRIGGER_CMD1
 *              - ADC_MAP_TRIGGER_CMD2
 *
 * @return     None
 *
 */
void Adc_TriggerSwMap(Adc_MapTriggerType MapTriggerType)
{
    switch (MapTriggerType)
    {
    case ADC_MAP_TRIGGER_CMD0:
        Adc_RegBfPtr->ADC_SWTRIG.ADC_SWTRIG0 = 1U;
        break;
    
    case ADC_MAP_TRIGGER_CMD1:
        Adc_RegBfPtr->ADC_SWTRIG.ADC_SWTRIG1 = 1U;
        break;

    case ADC_MAP_TRIGGER_CMD2:
        Adc_RegBfPtr->ADC_SWTRIG.ADC_SWTRIG2 = 1U;
        break;

    default:
        /* do nothing */
        break;
    }
}

/**
 * @brief      Adc Config Function
 *
 * @param[in]  Config: Pointer to a configuration structure.
 *
 * @return     None
 *
 */
void Adc_Config(const Adc_ConfigType * Config)
{
    Adc_RegBfPtr->ADC_CFG.BUFFCAL_EN = (uint32)Config->BufferOffsetEn;
    Adc_RegBfPtr->ADC_CFG.CLK_DIV = (uint32)Config->ClockDividerEn;
    Adc_RegBfPtr->ADC_CFG.HWT_EN = (uint32)Config->HardWareTriggerEn;
    Adc_RegBfPtr->ADC_CFG.FAST_MODE = (uint32)Config->DigitalFastModeEn;
    Adc_RegBfPtr->ADC_CFG.ANA_FAST_EN = (uint32)Config->AnalogFastModeEn;
    Adc_RegBfPtr->ADC_CFG.STABLE_T = (uint32)Config->StableTime;
}

/**
 * @brief      Adc Config Sample Input Time Function
 *
 * @param[in]  TimeConfig: Pointer to a Sample Input Time configuration structure.
 *
 * @return     None
 *
 */
void Adc_ConfigSampleTime(const Adc_TimeConfigType * TimeConfig)
{
    Adc_RegBfPtr->ADC_TCFG0.SMP_EXT0 = (uint32)TimeConfig->ExternalTime0;
    Adc_RegBfPtr->ADC_TCFG0.SMP_EXT1 = (uint32)TimeConfig->ExternalTime1;
    Adc_RegBfPtr->ADC_TCFG0.SMP_EXT2 = (uint32)TimeConfig->ExternalTime2;
    Adc_RegBfPtr->ADC_TCFG1.SMP_EXT3 = (uint32)TimeConfig->ExternalTime3;
    Adc_RegBfPtr->ADC_TCFG1.SMP_EXT4 = (uint32)TimeConfig->ExternalTime4;
    Adc_RegBfPtr->ADC_TCFG1.SMP_EXT5 = (uint32)TimeConfig->ExternalTime5;
    Adc_RegBfPtr->ADC_TCFG2.SMP_EXT6 = (uint32)TimeConfig->ExternalTime6;
    Adc_RegBfPtr->ADC_TCFG2.SMP_EXT7 = (uint32)TimeConfig->ExternalTime7;
    Adc_RegBfPtr->ADC_TCFG2.SMP_EXT8 = (uint32)TimeConfig->ExternalTime8;
    Adc_RegBfPtr->ADC_TCFG3.SMP_IN0 = (uint32)TimeConfig->InternalTime0;
    Adc_RegBfPtr->ADC_TCFG3.SMP_IN1 = (uint32)TimeConfig->InternalTime1;
    Adc_RegBfPtr->ADC_TCFG3.SMP_IN2 = (uint32)TimeConfig->InternalTime2;
    Adc_RegBfPtr->ADC_TCFG4.SMP_IN3 = (uint32)TimeConfig->InternalTime3;
    Adc_RegBfPtr->ADC_TCFG4.SMP_IN4 = (uint32)TimeConfig->InternalTime4;
}

/**
 * @brief      Adc Set Channel Buffer Disable Or Enable Function
 *
 * @param[in]  ChannelType: Select the Buffer Channel Type.
 *              - ADC_BUFFER_VS
 *              - ADC_BUFFER_VDDP
 *              - ADC_BUFFER_MON
 *              - ADC_BUFFER_VSD
 *                ...
 *              - ADC_BUFFER_PMU_TEMPER_GROUND
 *              - ADC_BUFFER_GDU_TEMPER_GROUND
 *              - ADC_BUFFER_LIN_TEMPER_GROUND
 * @param[in]  Cmd: Select Disable Or Enable.
 *              - COMMON_DISABLE
 *              - COMMON_ENABLE
 *
 * @return     None
 *
 */
void Adc_EnableChannelBuffer(Adc_BufferChannelType ChannelType, Common_ControlStateType Cmd)
{
    if(COMMON_ENABLE == Cmd)
    {
        Adc_RegWPtr->ADC_BUFF_EN = Adc_RegWPtr->ADC_BUFF_EN | (1UL << (uint8)ChannelType);
    }
    else
    {
        Adc_RegWPtr->ADC_BUFF_EN = Adc_RegWPtr->ADC_BUFF_EN & (~(1UL << (uint8)ChannelType));
    } 
}

/**
 * @brief      Adc Get Channel Buffer Status Function
 *
 * @param[in]  ChannelType: Select the Buffer Channel Type.
 *              - ADC_BUFFER_VS
 *              - ADC_BUFFER_VDDP
 *              - ADC_BUFFER_MON
 *              - ADC_BUFFER_VSD
 *                ...
 *              - ADC_BUFFER_PMU_TEMPER_GROUND
 *              - ADC_BUFFER_GDU_TEMPER_GROUND
 *              - ADC_BUFFER_LIN_TEMPER_GROUND
 *
 * @return     Common_ControlStateType: Channel Buffer Disable Or Enable.
 *              - COMMON_DISABLE
 *              - COMMON_ENABLE
 */
Common_ControlStateType Adc_GetChannelBufferStatus(Adc_BufferChannelType ChannelType)
{
    Common_ControlStateType Cmd = COMMON_DISABLE;

    if((Adc_RegWPtr->ADC_BUFF_EN & (1UL << (uint8)ChannelType)) != 0U)
    {
        Cmd = COMMON_ENABLE;
    }

    return Cmd;
}

/*PRQA S 2897 ++*/
/**
 * @brief      Adc Set Buffer Calibration Offset Value Function
 *
 * @param[in]  OffsetValue: Adc buffer calibration offset Value.
 *
 * @return     None
 *
 */
void Adc_SetBufferOffsetValue(sint16 OffsetValue)
{
    if(OffsetValue > 0xFFF)
    {
        OffsetValue = 0xFFF;
    }
    else if(OffsetValue < -0xFFF)
    {
        OffsetValue = -0xFFF;
    }
    else
    {
        /* do nothing */
    }

    Adc_RegBfPtr->ADC_BUFF_OFFSET_VAL.BUFF_OFFSET = ((uint32)OffsetValue & 0x1FFFU);
}
/*PRQA S 2897 --*/

/**
 * @brief      Adc Get Buffer Calibration Offset Value Function
 *
 * @param[in]  None.
 *
 * @return     int16: Adc buffer calibration offset Value.
 *
 */
sint16 Adc_GetBufferOffsetValue(void)
{
    sint16 OffsetValue = (sint16)Adc_RegBfPtr->ADC_BUFF_OFFSET_VAL.BUFF_OFFSET;

    if((Adc_RegBfPtr->ADC_BUFF_OFFSET_VAL.BUFF_OFFSET & 0x1000U) != 0U)
    {
        OffsetValue = OffsetValue - 0x2000;
    }

    return OffsetValue;
}

/**
 * @brief      Adc Config Group0 Function
 *
 * @param[in]  Group0Config: Pointer to a group0 configuration structure.
 *
* @return     Result Status:
 *              - COMMON_SUCC: Loop Depth Correct
 *              - COMMON_ERR: Loop Depth Error
 */
Common_ResultStatusType Adc_ConfigGroup0(const Adc_Group0ConfigType * Group0Config)
{
    Common_ResultStatusType ReturnValue = COMMON_SUCC;

    if(Group0Config->LoopDepth < 1U || Group0Config->LoopDepth > 8U)
    {
        ReturnValue = COMMON_ERR;
    }

    if(COMMON_SUCC == ReturnValue)
    {
        if(ADC_TRIGGER_MAP_MODE == Group0Config->TriggerMode)
        {
            Adc_RegBfPtr->ADC_GRP0_CFG.TRIG_MODE = 1U;
        }
        else
        {
            Adc_RegBfPtr->ADC_GRP0_CFG.TRIG_MODE = 0U;
        }

        if (ADC_TRIGGER_MIX_MODE == Group0Config->TriggerMode)
        {
            Adc_RegBfPtr->ADC_GRP0_CFG.MIX_MODE = 1U;
        }
        else
        {
            Adc_RegBfPtr->ADC_GRP0_CFG.MIX_MODE = 0U;
        }

        Adc_RegBfPtr->ADC_GRP0_CFG.DATA_MASK = (uint32)Group0Config->DataMask;
        Adc_RegBfPtr->ADC_GRP0_CFG.AVGS = (uint32)Group0Config->AverageSelect;
        Adc_RegBfPtr->ADC_GRP0_CFG.LMD = (uint32)Group0Config->LoopDepth - 1U;
        
        Adc_RegBfPtr->ADC_CMD_BUFF0.CMD0 = (uint32)Group0Config->Group0Cmd0;
        Adc_RegBfPtr->ADC_CMD_BUFF0.CMD1 = (uint32)Group0Config->Group0Cmd1;
        Adc_RegBfPtr->ADC_CMD_BUFF0.CMD2 = (uint32)Group0Config->Group0Cmd2;
        Adc_RegBfPtr->ADC_CMD_BUFF0.CMD3 = (uint32)Group0Config->Group0Cmd3;
        Adc_RegBfPtr->ADC_CMD_BUFF1.CMD4 = (uint32)Group0Config->Group0Cmd4;
        Adc_RegBfPtr->ADC_CMD_BUFF1.CMD5 = (uint32)Group0Config->Group0Cmd5;
        Adc_RegBfPtr->ADC_CMD_BUFF1.CMD6 = (uint32)Group0Config->Group0Cmd6;
        Adc_RegBfPtr->ADC_CMD_BUFF1.CMD7 = (uint32)Group0Config->Group0Cmd7;

        Adc_RegBfPtr->ADC_CMD_BUFF0.MAP0_SEQ_AND_EN = (uint32)Group0Config->MapSelect0;
        Adc_RegBfPtr->ADC_CMD_BUFF0.MAP1_SEQ_AND_EN = (uint32)Group0Config->MapSelect1;
        Adc_RegBfPtr->ADC_CMD_BUFF0.MAP2_SEQ_AND_EN = (uint32)Group0Config->MapSelect2;
    }
    
    return ReturnValue;
}

/**
 * @brief      Adc Get Group0 One Cmd Result Function
 *
 * @param[in]  CmdType: Select Read Group0 Cmd Type.
 *              - ADC_GROUP0_CMD0
 *              - ADC_GROUP0_CMD1
 *              - ADC_GROUP0_CMD2
 *              - ADC_GROUP0_CMD3
 *              - ADC_GROUP0_CMD4
 *              - ADC_GROUP0_CMD5
 *              - ADC_GROUP0_CMD6
 *              - ADC_GROUP0_CMD7
 * @param[out] Result: Pointer to where to store the Result.
 *
 * @return     Result Status:
 *              - COMMON_SUCC: Result Valid
 *              - COMMON_ERR: Result Overrun Or No New Valid Data Available
 */
Common_ResultStatusType Adc_GetGroup0CmdResult(Adc_Group0CmdType CmdType, uint32 * Result)
{
    Common_ResultStatusType ReturnValue = COMMON_SUCC;
    uint32 Data;

    Data = Adc_RegWPtr->ADC_GRP0_DATA_RD[CmdType];

    if(1U != Adc_RegBfPtr->ADC_GRP0_CFG.DATA_MASK)
    {
        if(((Data & 0x1000000U) != 0x1000000U) || ((Data & 0x2000000U) != 0U))
        {
            ReturnValue = COMMON_ERR;
        }
    }
    *Result = Data;

    return ReturnValue;
}

/**
 * @brief      Adc Get Group0 Cmds Result
 *
 * @param[in]  CmdNumber: Select Read CMD Type.
 * @param[out] Result: Pointer to where to store the Result.
 *
 * @return     Result Status:
 *              - COMMON_SUCC: Result Valid
 *              - COMMON_ERR: Result Overrun Or No New Valid Data Available Or CmdNumber Error
 */
Common_ResultStatusType Adc_GetGroup0CmdsResult(uint8 CmdNumber, uint32 * Result)
{
    Common_ResultStatusType ReturnValue = COMMON_SUCC;
    uint32 Data;
    uint8 Index;

    if(CmdNumber < 9U)
    {
        for(Index = 0U; Index < CmdNumber; Index++)
        {
            Data = Adc_RegWPtr->ADC_GRP0_DATA_RD[Index];

            if(1U != Adc_RegBfPtr->ADC_GRP0_CFG.DATA_MASK)
            {
                if(((Data & 0x1000000U) != 0x1000000U) || ((Data & 0x2000000U) != 0U))
                {     
                    ReturnValue = COMMON_ERR;
                }
            }
            Result[Index] = Data;
        }
    }

    return ReturnValue;
}

/**
 * @brief      Adc Enable Group1 Sequence Channels Function
 *
 * @param[in]  SequenceType: Select the Group1 Sequence Type.
 *              - ADC_GROUP1_SEQUENCE0
 *              - ADC_GROUP1_SEQUENCE1
 *              - ADC_GROUP1_SEQUENCE2
 * @param[in]  ChannelNumber: Number of enabled channels.
 * @param[in]  ChannelType: Pointing to the set channels type.
 *
 * @return     None
 *
 */
void Adc_EnableGroup1Sequence(Adc_Group1SequenceType SequenceType, uint8 ChannelNumber,
                               const Adc_Group1ChannelType * ChannelType)
{
    uint8 Index = 0U;
    uint32 TempValue = 0U;

    ChannelNumber = ChannelNumber <= 16U ? ChannelNumber : 16U;

    for(Index = 0U; Index < ChannelNumber; Index++)
    {
        TempValue |= (1UL << (uint8)ChannelType[Index]);
    }
    
    switch (SequenceType)
    {
    case ADC_GROUP1_SEQUENCE0:
        Adc_RegWPtr->ADC_GRP1_SQ0 |= TempValue;
        break;
    
    case ADC_GROUP1_SEQUENCE1:
        Adc_RegWPtr->ADC_GRP1_SQ1 |= TempValue;
        break;
    
    case ADC_GROUP1_SEQUENCE2:
        Adc_RegWPtr->ADC_GRP1_SQ2 |= TempValue;
        break;
    
    default:
        /* do nothing */
        break;
    }
}

/**
 * @brief      Adc Disable Group1 Sequence Channels Function
 *
 * @param[in]  SequenceType: Select the Group1 Sequence Type.
 *              - ADC_GROUP1_SEQUENCE0
 *              - ADC_GROUP1_SEQUENCE1
 *              - ADC_GROUP1_SEQUENCE2
 * @param[in]  ChannelNumber: Number of enabled channels.
 * @param[in]  ChannelType: Pointing to the set channels type.
 *
 * @return     None
 *
 */
void Adc_DisableGroup1Sequence(Adc_Group1SequenceType SequenceType, uint8 ChannelNumber,
                               const Adc_Group1ChannelType * ChannelType)
{
    uint8 Index = 0U;
    uint32 TempValue = 0U;

    ChannelNumber = ChannelNumber <= 16U ? ChannelNumber : 16U;

    for(Index = 0U; Index < ChannelNumber; Index++)
    {
        TempValue |= (1UL << (uint8)ChannelType[Index]);
    }
    
    switch (SequenceType)
    {
    case ADC_GROUP1_SEQUENCE0:
        Adc_RegWPtr->ADC_GRP1_SQ0 &= (~(TempValue));
        break;
    
    case ADC_GROUP1_SEQUENCE1:
        Adc_RegWPtr->ADC_GRP1_SQ1 &= (~(TempValue));
        break;
    
    case ADC_GROUP1_SEQUENCE2:
        Adc_RegWPtr->ADC_GRP1_SQ2 &= (~(TempValue));
        break;
    
    default:
        /* do nothing */
        break;
    }
}

/**
 * @brief      Adc Get Group1 Sequence Channel Status Function
 *
 * @param[in]  SequenceType: Select the Group1 Sequence Type.
 *              - ADC_GROUP1_SEQUENCE0
 *              - ADC_GROUP1_SEQUENCE1
 *              - ADC_GROUP1_SEQUENCE2
 * @param[in]  ChannelType: Select the Group1 Channel Type.
 *              - ADC_GROUP1_VS
 *              - ADC_GROUP1_VDDP
 *              - ADC_GROUP1_MON
 *                ...
 *              - ADC_GROUP1_DAC
 *              - ADC_GROUP1_VDDC_AON
 *              - ADC_GROUP1_VAREF
 *
 * @return     Common_ControlStateType: Group1 Channel Disable Or Enable.
 *              - COMMON_DISABLE
 *              - COMMON_ENABLE
 */
Common_ControlStateType Adc_GetGroup1SequenceStatus(Adc_Group1SequenceType SequenceType, 
                                                       Adc_Group1ChannelType ChannelType)
{
    Common_ControlStateType ReturnValue = COMMON_DISABLE;
    uint32 MaskValue = 0U;

    switch (SequenceType)
    {
    case ADC_GROUP1_SEQUENCE0:
        MaskValue = Adc_RegWPtr->ADC_GRP1_SQ0 & (1UL << (uint8)ChannelType);
        break;
    
    case ADC_GROUP1_SEQUENCE1:
        MaskValue = Adc_RegWPtr->ADC_GRP1_SQ1 & (1UL << (uint8)ChannelType);
        break;
    
    case ADC_GROUP1_SEQUENCE2:
        MaskValue = Adc_RegWPtr->ADC_GRP1_SQ2 & (1UL << (uint8)ChannelType);
        break;
    
    default:
        /* do nothing */
        break;
    }

    if(MaskValue != 0U)
    {
        ReturnValue = COMMON_ENABLE;
    }

    return ReturnValue;
}

/**
 * @brief      Adc Get Group1 One Channel Raw Result Function
 *
 * @param[in]  ChannelType: Select Read Group1 Channel Type.
 *              - ADC_GROUP1_VS
 *              - ADC_GROUP1_VDDP
 *              - ADC_GROUP1_MON
 *                ...
 *              - ADC_GROUP1_DAC
 *              - ADC_GROUP1_VDDC_AON
 *              - ADC_GROUP1_VAREF
 * @param[out] Result: Pointer to where to store the Result.
 *
 * @return     None
 *
 */
void Adc_GetGroup1ChannelRawResult(Adc_Group1ChannelType ChannelType, uint32 * Result)
{
    *Result = Adc_RegWPtr->ADC_GRP1_DATA_RD[ChannelType];
}

/**
 * @brief      Adc Get Group1 Channels Raw Result Function
 *
 * @param[in]  CmdNumber: Select Read Group1 Channels Number.
 * @param[out] Result: Pointer to where to store the Result.
 *
 * @return     Result Status:
 *              - COMMON_SUCC: Result Valid
 *              - COMMON_ERR: CmdNumber Error
 */
Common_ResultStatusType Adc_GetGroup1ChannelsRawResult(uint8 CmdNumber, uint32 * Result)
{
    Common_ResultStatusType ReturnValue = COMMON_ERR;
    uint8 Index;

    if(CmdNumber < 17U)
    {
        for(Index = 0U; Index < CmdNumber; Index++)
        {
            Result[Index] = Adc_RegWPtr->ADC_GRP1_DATA_RD[Index];
        }

        ReturnValue = COMMON_SUCC;
    }

    return ReturnValue;
}

/**
 * @brief      Adc Get Analog Watchdog One Channel Iir Result Function
 *
 * @param[in]  ChannelType: Select Read Analog Watchdog Channel Type.
 *              - ADC_AWDG_VS
 *              - ADC_AWDG_VDDP
 *              - ADC_AWDG_MON
 *                ...
 *              - ADC_AWDG_USER2
 *              - ADC_AWDG_USER3
 *              - ADC_AWDG_USER4
 * @param[out] Result: Pointer to where to store the Result.
 *
 * @return     None
 *
 */
void Adc_GetAwdgChannelIirResult(Adc_AwdgChannelType ChannelType, uint32 * Result)
{
    *Result = Adc_RegWPtr->ADC_IIR_DATA_RD[ChannelType];
}

/**
 * @brief      Adc Get Analog Watchdog Channels Iir Result Function
 *
 * @param[in]  CmdNumber: Select Read Analog Watchdog Channels Number.
 * @param[out] Result: Pointer to where to store the Result.
 *
 * @return     Result Status:
 *              - COMMON_SUCC: Result Valid
 *              - COMMON_ERR: CmdNumber Error
 */
Common_ResultStatusType Adc_GetAwdgChannelsIirResult(uint8 CmdNumber, uint32 * Result)
{
    Common_ResultStatusType ReturnValue = COMMON_ERR;
    uint8 Index;

    if(CmdNumber < 16U)
    {
        for(Index = 0U; Index < CmdNumber; Index++)
        {
            Result[Index] = Adc_RegWPtr->ADC_IIR_DATA_RD[Index];
        }

        ReturnValue = COMMON_SUCC;
    }

    return ReturnValue;
}

/**
 * @brief      Adc Set Analog Watchdog One Channel Iir Result Function
 *
 * @param[in]  ChannelType: Select Analog Watchdog Channel Type.
 *              - ADC_AWDG_VS
 *              - ADC_AWDG_VDDP
 *              - ADC_AWDG_MON
 *                ...
 *              - ADC_AWDG_USER2
 *              - ADC_AWDG_USER3
 *              - ADC_AWDG_USER4
 * @param[in]  Result: Result To Set.
 *
 * @return     None
 *
 */
void Adc_SetAwdgChannelIirResult(Adc_AwdgChannelType ChannelType, uint32 Result)
{
    Adc_RegWPtr->ADC_IIR_DATA_RD[ChannelType] = Result;
}

/**
 * @brief      Adc Set Analog Watchdog Channels Iir Result Function
 *
 * @param[in]  CmdNumber: Select Read Analog Watchdog Channels Number.
 * @param[in]  Result: Pointer to where to store the Result.
 *
 * @return     Result Status:
 *              - COMMON_SUCC: Result Valid
 *              - COMMON_ERR: CmdNumber Error
 */
Common_ResultStatusType Adc_SetAwdgChannelsIirResult(uint8 CmdNumber, uint32 * Result)
{
    Common_ResultStatusType ReturnValue = COMMON_ERR;
    uint8 Index;

    if(CmdNumber < 16U)
    {
        for(Index = 0U; Index < CmdNumber; Index++)
        {
            Adc_RegWPtr->ADC_IIR_DATA_RD[Index] = Result[Index];
        }

        ReturnValue = COMMON_SUCC;
    }

    return ReturnValue;
}

/**
 * @brief      Adc Set Analog Watchdog Channel Filter Coefficient B0 Function
 *
 * @param[in]  ChannelType: Select Analog Watchdog Channel Type.
 *              - ADC_AWDG_VS
 *              - ADC_AWDG_VDDP
 *              - ADC_AWDG_MON
 *                ...
 *              - ADC_AWDG_USER2
 *              - ADC_AWDG_USER3
 *              - ADC_AWDG_USER4
 * @param[in]  CoeffType: Select Filter Coefficient Type.
 *              - ADC_FILTER_1V2
 *              - ADC_FILTER_1V4
 *              - ADC_FILTER_1V8
 *              - ADC_FILTER_1V16
 *
 * @return     None
 *
 */
void Adc_SetAwdgChannelFilterCoeff(Adc_AwdgChannelType ChannelType,
                                                        Adc_FilterCoefficientType CoeffType)
{
    uint8 Shift = (uint8)ChannelType << 1U;

    if(ChannelType <= ADC_AWDG_USER4)
    {
        Adc_RegWPtr->ADC_IIR_COE = (Adc_RegWPtr->ADC_IIR_COE & (~(3UL << Shift))) |
                                                    ((uint32)CoeffType << Shift);
    }
}

/**
 * @brief      Adc Get Analog Watchdog Channel Filter Coefficient B0 Function
 *
 * @param[in]  ChannelType: Select Analog Watchdog Channel Type.
 *              - ADC_AWDG_VS
 *              - ADC_AWDG_VDDP
 *              - ADC_AWDG_MON
 *                ...
 *              - ADC_AWDG_USER2
 *              - ADC_AWDG_USER3
 *              - ADC_AWDG_USER4
 *
 * @return     Adc_FilterCoefficientType: Filter Coefficient Type.
 *              - ADC_FILTER_1V2
 *              - ADC_FILTER_1V4
 *              - ADC_FILTER_1V8
 *              - ADC_FILTER_1V16
 */
Adc_FilterCoefficientType Adc_GetAwdgChannelFilterCoeff(Adc_AwdgChannelType ChannelType)
{
    Adc_FilterCoefficientType ReturnValue = ADC_FILTER_1V2;
    uint32 Coefficient;
    uint8 Shift = (uint8)ChannelType << 1U;

    if(ChannelType <= ADC_AWDG_USER4)
    {
        Coefficient = (Adc_RegWPtr->ADC_IIR_COE >> Shift) & 3U;
        ReturnValue = (Adc_FilterCoefficientType)Coefficient;
    }

    return ReturnValue;
}

/**
 * @brief      Adc Config Analog Watchdog Internal Channel Threshold Function
 *
 * @param[in]  InternalType: Select Analog Watchdog Internal Channel Threshold Type.
 *              - ADC_AWDG_VS_OV_L2
 *              - ADC_AWDG_VS_OV_L1
 *              - ADC_AWDG_VS_UV
 *                ...
 *              - ADC_AWDG_GDU_OT_SHUTDOWN
 *              - ADC_AWDG_LIN_OT_WARNING
 *              - ADC_AWDG_VDDC_AON_OV
 * @param[in]  Config: Pointer to a Analog Watchdog Internal Channel Threshold config structure.
 *
 * @return     None
 *
 */
void Adc_ConfigAwdgInternal(Adc_AwdgInternalThType InternalType,
                                              const Adc_AwdgInternalConfigType * Config)
{
    uint32 TempVal = ((uint32)Config->CompareValue & 0x3FFU) |  
                (((uint32)Config->TimeThreshold & 0x7U) << 10U) | 
                (((uint32)Config->ValueSelect & 0x1U) << 14U);
    uint32 MaskVal = (0x3FFUL) | (0x7UL << 10U) | (0x1UL << 14U);
    uint32 ShiftVal = 0U;

    volatile uint32 * const ValAddrTable[(uint32)ADC_AWDG_VDDC_AON_OV + 1U] = {
        &Adc_RegWPtr->ADC_AWDG_TH10_0,
        &Adc_RegWPtr->ADC_AWDG_TH10_1,
        &Adc_RegWPtr->ADC_AWDG_TH10_1,
        &Adc_RegWPtr->ADC_AWDG_TH11,
        &Adc_RegWPtr->ADC_AWDG_TH11,
        &Adc_RegWPtr->ADC_AWDG_TH12,
        &Adc_RegWPtr->ADC_AWDG_TH12,
        &Adc_RegWPtr->ADC_AWDG_TH13,
        &Adc_RegWPtr->ADC_AWDG_TH13,
        &Adc_RegWPtr->ADC_AWDG_TH14,
        &Adc_RegWPtr->ADC_AWDG_TH14,
        &Adc_RegWPtr->ADC_AWDG_TH15,
        &Adc_RegWPtr->ADC_AWDG_TH15,
        &Adc_RegWPtr->ADC_AWDG_TH16,
        &Adc_RegWPtr->ADC_AWDG_TH16,
        &Adc_RegWPtr->ADC_AWDG_TH17,
        &Adc_RegWPtr->ADC_AWDG_TH17,
        &Adc_RegWPtr->ADC_AWDG_TH18,
        &Adc_RegWPtr->ADC_AWDG_TH18,
        &Adc_RegWPtr->ADC_AWDG_TH19E,
        &Adc_RegWPtr->ADC_AWDG_TH19E
    };

    switch (InternalType)
    {
        case ADC_AWDG_VS_OV_L2:
        case ADC_AWDG_LIN_OT_WARNING:
        case ADC_AWDG_VDDC_AON_OV:
            ShiftVal = (1U == ((uint32)InternalType & 1U)) ? 0U : 16U;
            /* Clear register */
            *ValAddrTable[InternalType] &= (~(MaskVal << ShiftVal));
            /* Set register */
            *ValAddrTable[InternalType] |= (TempVal << ShiftVal);
            break;

        case ADC_AWDG_VS_OV_L1:
        case ADC_AWDG_VS_UV:
        case ADC_AWDG_VDDP_OV:
        case ADC_AWDG_VDDP_UV:
        case ADC_AWDG_MON_OV:
        case ADC_AWDG_MON_UV:
        case ADC_AWDG_VSD_OV:
        case ADC_AWDG_VSD_UV:
        case ADC_AWDG_VCP_OV:
        case ADC_AWDG_VCP_UV:
        case ADC_AWDG_VDH_OV:
        case ADC_AWDG_VDH_UV:
        case ADC_AWDG_VDDC_SW_OV:
        case ADC_AWDG_VDDC_SW_UV:
        case ADC_AWDG_PMU_OT_WARNING:
        case ADC_AWDG_PMU_OT_SHUTDOWN:
        case ADC_AWDG_GDU_OT_WARNING:
        case ADC_AWDG_GDU_OT_SHUTDOWN:
            ShiftVal = (1U == ((uint32)InternalType & 1U)) ? 16U : 0U;
            /* Clear register */
            *ValAddrTable[InternalType] &= (~(MaskVal << ShiftVal));
            /* Set register */
            *ValAddrTable[InternalType] |= (TempVal << ShiftVal);
            break;

        
        default:
            /* do nothing */
            break;
    }
}

/**
 * @brief      Adc Get Analog Watchdog Internal Compare Select Type Function
 *
 * @param[in]  InternalType: Select Analog Watchdog Internal Channel Threshold Type.
 *              - ADC_AWDG_VS_OV_L2
 *              - ADC_AWDG_VS_OV_L1
 *              - ADC_AWDG_VS_UV
 *                ...
 *              - ADC_AWDG_GDU_OT_SHUTDOWN
 *              - ADC_AWDG_LIN_OT_WARNING
 *              - ADC_AWDG_VDDC_AON_OV
 *
 * @return     Adc_AwdgCompareSelectType: Compare Select Type
 *              - ADC_AWDG_COMPARE_UNDER
 *              - ADC_AWDG_COMPARE_OVER
 */
Adc_AwdgCompareSelectType Adc_GetAwdgInternalCompareType(Adc_AwdgInternalThType InternalType)
{
    Adc_AwdgCompareSelectType CompareType = ADC_AWDG_COMPARE_UNDER;
    uint32 TempVal = 0U;

    volatile uint32 * const ValAddrTable[(uint32)ADC_AWDG_VDDC_AON_OV + 1U] = {
        &Adc_RegWPtr->ADC_AWDG_TH10_0,
        &Adc_RegWPtr->ADC_AWDG_TH10_1,
        &Adc_RegWPtr->ADC_AWDG_TH10_1,
        &Adc_RegWPtr->ADC_AWDG_TH11,
        &Adc_RegWPtr->ADC_AWDG_TH11,
        &Adc_RegWPtr->ADC_AWDG_TH12,
        &Adc_RegWPtr->ADC_AWDG_TH12,
        &Adc_RegWPtr->ADC_AWDG_TH13,
        &Adc_RegWPtr->ADC_AWDG_TH13,
        &Adc_RegWPtr->ADC_AWDG_TH14,
        &Adc_RegWPtr->ADC_AWDG_TH14,
        &Adc_RegWPtr->ADC_AWDG_TH15,
        &Adc_RegWPtr->ADC_AWDG_TH15,
        &Adc_RegWPtr->ADC_AWDG_TH16,
        &Adc_RegWPtr->ADC_AWDG_TH16,
        &Adc_RegWPtr->ADC_AWDG_TH17,
        &Adc_RegWPtr->ADC_AWDG_TH17,
        &Adc_RegWPtr->ADC_AWDG_TH18,
        &Adc_RegWPtr->ADC_AWDG_TH18,
        &Adc_RegWPtr->ADC_AWDG_TH19E,
        &Adc_RegWPtr->ADC_AWDG_TH19E
    };

    uint32 CommonShift = 13U;

    switch (InternalType)
    {
        case ADC_AWDG_VS_OV_L2:
        case ADC_AWDG_LIN_OT_WARNING:
        case ADC_AWDG_VDDC_AON_OV:
            CommonShift = (1U == ((uint32)InternalType & 1U)) ? 13U : 29U;
            TempVal = (*ValAddrTable[InternalType] >> CommonShift);
            break;

        case ADC_AWDG_VS_OV_L1:
        case ADC_AWDG_VS_UV:
        case ADC_AWDG_VDDP_OV:
        case ADC_AWDG_VDDP_UV:
        case ADC_AWDG_MON_OV:
        case ADC_AWDG_MON_UV:
        case ADC_AWDG_VSD_OV:
        case ADC_AWDG_VSD_UV:
        case ADC_AWDG_VCP_OV:
        case ADC_AWDG_VCP_UV:
        case ADC_AWDG_VDH_OV:
        case ADC_AWDG_VDH_UV:
        case ADC_AWDG_VDDC_SW_OV:
        case ADC_AWDG_VDDC_SW_UV:
        case ADC_AWDG_PMU_OT_WARNING:
        case ADC_AWDG_PMU_OT_SHUTDOWN:
        case ADC_AWDG_GDU_OT_WARNING:
        case ADC_AWDG_GDU_OT_SHUTDOWN:
            CommonShift = (1U == ((uint32)InternalType & 1U)) ? 29U : 13U;
            TempVal = (*ValAddrTable[InternalType] >> CommonShift);
            break;
        
        default:
            /* do nothing */
            break;
    }
    if(1U == (TempVal & 0x1UL))
    {
        CompareType = ADC_AWDG_COMPARE_OVER;
    }

    return CompareType;
}

/**
 * @brief      Adc Config Analog Watchdog User Channel Threshold Function
 *
 * @param[in]  UserType: Select Analog Watchdog User Channel Threshold Type.
 *              - ADC_AWDG_USER1_TH
 *              - ADC_AWDG_USER2_TH
 *              - ADC_AWDG_USER3_TH
 *              - ADC_AWDG_USER4_TH
 * @param[in]  Config: Pointer to a Analog Watchdog User Channel Threshold config structure.
 *
 * @return     None
 *
 */
void Adc_ConfigAwdgUser(Adc_AwdgUserThType UserType,
                                              const Adc_AwdgUserConfigType * Config)
{
    switch (UserType)
    {
    case ADC_AWDG_USER1_TH:
        Adc_RegBfPtr->ADC_AWDG_THU1.TH_U1 =(uint32)Config->CompareValue;
        Adc_RegBfPtr->ADC_AWDG_THU1.TIME_TH_U1 =(uint32)Config->TimeThreshold;
        Adc_RegBfPtr->ADC_AWDG_THU1.MODE_U1 =(uint32)Config->CompareSelect;
        Adc_RegBfPtr->ADC_AWDG_THU1.IIR_EN_U1 =(uint32)Config->ValueSelect;
        Adc_RegBfPtr->ADC_AWDG_THU1.CH_ID_U1 =(uint32)Config->ChannelSelect;
        Adc_RegBfPtr->ADC_AWDG_THU1.U1_EN =(uint32)Config->AwdgEnable;
        break;
    
    case ADC_AWDG_USER2_TH:
        Adc_RegBfPtr->ADC_AWDG_THU2.TH_U2 =(uint32)Config->CompareValue;
        Adc_RegBfPtr->ADC_AWDG_THU2.TIME_TH_U2 =(uint32)Config->TimeThreshold;
        Adc_RegBfPtr->ADC_AWDG_THU2.MODE_U2 =(uint32)Config->CompareSelect;
        Adc_RegBfPtr->ADC_AWDG_THU2.IIR_EN_U2 =(uint32)Config->ValueSelect;
        Adc_RegBfPtr->ADC_AWDG_THU2.CH_ID_U2 =(uint32)Config->ChannelSelect;
        Adc_RegBfPtr->ADC_AWDG_THU2.U2_EN =(uint32)Config->AwdgEnable;
        break;
    
    case ADC_AWDG_USER3_TH:
        Adc_RegBfPtr->ADC_AWDG_THU3.TH_U3 =(uint32)Config->CompareValue;
        Adc_RegBfPtr->ADC_AWDG_THU3.TIME_TH_U3 =(uint32)Config->TimeThreshold;
        Adc_RegBfPtr->ADC_AWDG_THU3.MODE_U3 =(uint32)Config->CompareSelect;
        Adc_RegBfPtr->ADC_AWDG_THU3.IIR_EN_U3 =(uint32)Config->ValueSelect;
        Adc_RegBfPtr->ADC_AWDG_THU3.CH_ID_U3 =(uint32)Config->ChannelSelect;
        Adc_RegBfPtr->ADC_AWDG_THU3.U3_EN =(uint32)Config->AwdgEnable;
        break;
    
    case ADC_AWDG_USER4_TH:
        Adc_RegBfPtr->ADC_AWDG_THU4.TH_U4 =(uint32)Config->CompareValue;
        Adc_RegBfPtr->ADC_AWDG_THU4.TIME_TH_U4 =(uint32)Config->TimeThreshold;
        Adc_RegBfPtr->ADC_AWDG_THU4.MODE_U4 =(uint32)Config->CompareSelect;
        Adc_RegBfPtr->ADC_AWDG_THU4.IIR_EN_U4 =(uint32)Config->ValueSelect;
        Adc_RegBfPtr->ADC_AWDG_THU4.CH_ID_U4 =(uint32)Config->ChannelSelect;
        Adc_RegBfPtr->ADC_AWDG_THU4.U4_EN =(uint32)Config->AwdgEnable;
        break;
    
    default:
        /* do nothing */
        break;
    }
}

/**
 * @brief      Adc Get Analog Watchdog Internal Channel Threshold Status Function
 *
 * @param[in]  InternalType: Select Analog Watchdog Internal Channel Threshold Type.
 *              - ADC_AWDG_VS_OV_L2
 *              - ADC_AWDG_VS_OV_L1
 *              - ADC_AWDG_VS_UV
 *                ...
 *              - ADC_AWDG_GDU_OT_SHUTDOWN
 *              - ADC_AWDG_LIN_OT_WARNING
 *              - ADC_AWDG_VDDC_AON_OV
 *
 * @return     Common_FlagStatusType: Status
 *              - COMMON_RESET
 *              - COMMON_SET
 */
Common_FlagStatusType Adc_GetAwdgInternalStatus(Adc_AwdgInternalThType InternalType)
{
    Common_FlagStatusType ReturnValue = COMMON_RESET;

    if((Adc_RegWPtr->ADC_AWDOG_STAT & (1UL << (uint8)InternalType)) != 0U)
    {
        ReturnValue = COMMON_SET;
    }

    return ReturnValue;
}

/**
 * @brief      Adc Get Analog Watchdog User Channel Threshold Status Function
 *
 * @param[in]  UserType: Select Analog Watchdog User Channel Threshold Type.
 *              - ADC_AWDG_USER1_TH
 *              - ADC_AWDG_USER2_TH
 *              - ADC_AWDG_USER3_TH
 *              - ADC_AWDG_USER4_TH
 *
 * @return     Common_FlagStatusType: Status
 *              - COMMON_RESET
 *              - COMMON_SET
 */
Common_FlagStatusType Adc_GetAwdgUserStatus(Adc_AwdgUserThType UserType)
{
    Common_FlagStatusType ReturnValue = COMMON_RESET;
    
    if((Adc_RegWPtr->ADC_AWDOG_STAT & (1UL << ((uint8)UserType + 21U))) != 0U)
    {
        ReturnValue = COMMON_SET;
    }

    return ReturnValue;
}

/**
 * @brief      Adc Dma Request Command Function
 *
 * @param[in]  Cmd: Select Disable Or Enable.
 *              - COMMON_DISABLE
 *              - COMMON_ENABLE
 *
 * @return     None
 *
 */
void Adc_EnableDmaRequest(Common_ControlStateType Cmd)
{
    Adc_RegBfPtr->ADC_IE.DMA_EN = (uint32)Cmd;
}

/**
 * @brief      Adc Temperature Calibration Command Function
 *
 * @param[in]  Type: Select Temperature Calibration Type.
 *              - ADC_TS_CAL_LIN
 *              - ADC_TS_CAL_GDU
 *              - ADC_TS_CAL_PMU
 * @param[in]  Cmd: Select Disable Or Enable.
 *              - COMMON_DISABLE
 *              - COMMON_ENABLE
 *
 * @return     None
 *
 */
void Adc_EnableTemperatureCalibration(Adc_TsCalibrationType Type, Common_ControlStateType Cmd)
{
    switch (Type)
    {
    case ADC_TS_CAL_LIN:
        Adc_RegBfPtr->ADC_TS_CFG.LIN_TS_CAL_EN = (uint32)Cmd;
        break;

    case ADC_TS_CAL_GDU:
        Adc_RegBfPtr->ADC_TS_CFG.GDU_TS_CAL_EN = (uint32)Cmd;
        break;

    case ADC_TS_CAL_PMU:
        Adc_RegBfPtr->ADC_TS_CFG.PMU_TS_CAL_EN = (uint32)Cmd;
        break;

    default:
        /* do nothing */
        break;
    }
}

/*PRQA S 2897 ++*/
/**
 * @brief      Adc Set Temperature Calibration Offset Value Function
 *
 * @param[in]  Type: Select Temperature Calibration Type.
 *              - ADC_TS_CAL_LIN
 *              - ADC_TS_CAL_GDU
 *              - ADC_TS_CAL_PMU
 * @param[in]  OffsetValue: Adc Temperature calibration offset Value.
 *
 * @return     None
 *
 */
void Adc_SetTemperatureOffsetValue(Adc_TsCalibrationType Type, sint16 OffsetValue)
{
    if(OffsetValue > 0xFFF)
    {
        OffsetValue = 0xFFF;
    }
    else if(OffsetValue < -0xFFF)
    {
        OffsetValue = -0xFFF;
    }
    else
    {
        /* do nothing */
    }

    switch (Type)
    {
    case ADC_TS_CAL_LIN:
        Adc_RegBfPtr->ADC_TS_CAL1.LIN_TS_OFFSET = ((uint32)OffsetValue & 0x1FFFU);
        break;

    case ADC_TS_CAL_GDU:
        Adc_RegBfPtr->ADC_TS_CAL0.GDU_TS_OFFSET = ((uint32)OffsetValue & 0x1FFFU);
        break;

    case ADC_TS_CAL_PMU:
        Adc_RegBfPtr->ADC_TS_CAL0.PMU_TS_OFFSET = ((uint32)OffsetValue & 0x1FFFU);
        break;

    default:
        /* do nothing */
        break;
    }
}
/*PRQA S 2897 --*/

/**
 * @brief      Adc Get Temperature Calibration Offset Value Function
 *
 * @param[in]  Type: Select Temperature Calibration Type.
 *              - ADC_TS_CAL_LIN
 *              - ADC_TS_CAL_GDU
 *              - ADC_TS_CAL_PMU
 *
 * @return     int16: Adc Temperature calibration offset Value.
 *
 */
sint16 Adc_GetTemperatureOffsetValue(Adc_TsCalibrationType Type)
{
    sint16 OffsetValue = 0;
    uint32 Value = 0U;

    switch (Type)
    {
    case ADC_TS_CAL_LIN:
        OffsetValue = (sint16)Adc_RegBfPtr->ADC_TS_CAL1.LIN_TS_OFFSET;
        Value = Adc_RegBfPtr->ADC_TS_CAL1.LIN_TS_OFFSET;
        break;

    case ADC_TS_CAL_GDU:
        OffsetValue = (sint16)Adc_RegBfPtr->ADC_TS_CAL0.GDU_TS_OFFSET;
        Value = Adc_RegBfPtr->ADC_TS_CAL0.GDU_TS_OFFSET;
        break;

    case ADC_TS_CAL_PMU:
        OffsetValue = (sint16)Adc_RegBfPtr->ADC_TS_CAL0.PMU_TS_OFFSET;
        Value = Adc_RegBfPtr->ADC_TS_CAL0.PMU_TS_OFFSET;
        break;

    default:
        /* do nothing */
        break;
    }

    if((Value & 0x1000U) != 0U)
    {
        OffsetValue = OffsetValue - 0x2000;
    }

    return OffsetValue;
}

/**
 * @brief      Adc Get Status Function
 *
 * @param[in]  StatusType: Select Status Type.
 *              - ADC_STATUS_DMA_REQ
 *              - ADC_STATUS_AWDG_NMI
 *              - ADC_STATUS_AWDG_UNDER
 *                ...
 *              - ADC_STATUS_SAR_BUSY
 *              - ADC_STATUS_PWON
 *              - ADC_STATUS_ALL
 *
 * @return     Common_FlagStatusType: Status
 *              - COMMON_RESET
 *              - COMMON_SET
 */
Common_FlagStatusType Adc_GetStatus(Adc_StatusType StatusType)
{
    Common_FlagStatusType ReturnValue = COMMON_RESET;

    if ((Adc_RegWPtr->ADC_STAT & Adc_StatusTable[StatusType]) != 0UL)
    {
        ReturnValue = COMMON_SET;
    }

    return ReturnValue;
}

/**
 * @brief      Adc Set Status Flag Disable Or Enable Function
 *
 * @param[in]  IntType: Select Int type.
 *              - ADC_INT_GRP0_LOOP_SCOM
 *              - ADC_INT_GRP0_MAP_SCOM
 *              - ADC_INT_GRP0_CCOM0
 *                ...
 *              - ADC_INT_GRP1_SCOM2
 *              - ADC_INT_GRP1_ALL_COM,
 *              - ADC_INT_ALL
 * @param[in]  Cmd: Select Disable Or Enable.
 *              - COMMON_DISABLE
 *              - COMMON_ENABLE
 *
 * @return     Result Status:
 *              - COMMON_SUCC: Flag set successfully
 *              - COMMON_ERR: The flag does not need to be set
 */
Common_ResultStatusType Adc_EnableStatusFlag(Adc_IntType IntType, Common_ControlStateType Cmd)
{
    Common_ResultStatusType ReturnValue = COMMON_SUCC;
    uint8 Shift = 0U;

    if(IntType < ADC_INT_GRP0_LOOP_SCOM)
    {
        ReturnValue = COMMON_ERR;
    }
    else if(IntType < ADC_INT_GRP0_CCOM0)
    {
        Shift = (uint8)IntType + 2U;
        Adc_RegWPtr->ADC_GRP0_CFG = (Adc_RegWPtr->ADC_GRP0_CFG & (~(1UL << Shift))) |
                                                            ((uint32)Cmd << Shift);
    }
    else if(IntType < ADC_INT_GRP0_CCOM4)
    {
        Shift = ((uint8)IntType << 3U) - 26U;
        Adc_RegWPtr->ADC_CMD_BUFF0 = (Adc_RegWPtr->ADC_CMD_BUFF0 & (~(1UL << Shift))) |
                                                            ((uint32)Cmd << Shift);
    }
    else if(IntType < ADC_INT_GRP1_SCOM0)
    {
        Shift = ((uint8)IntType << 3U) - 58U;
        Adc_RegWPtr->ADC_CMD_BUFF1 = (Adc_RegWPtr->ADC_CMD_BUFF1 & (~(1UL << Shift))) |
                                                            ((uint32)Cmd << Shift);
    }
    else if(IntType < ADC_INT_GRP0_LOOP_ABORT)
    {
        Shift = (uint8)IntType - 8U;
        Adc_RegWPtr->ADC_GRP1_CFG = (Adc_RegWPtr->ADC_GRP1_CFG & (~(1UL << Shift))) |
                                                            ((uint32)Cmd << Shift);
    }
    else if(IntType < ADC_INT_ALL)
    {
        ReturnValue = COMMON_ERR;
    }
    else if(ADC_INT_ALL == IntType)
    {
        Adc_RegBfPtr->ADC_GRP0_CFG.LOOP_SCOM_FLAG_EN = (uint32)Cmd;
        Adc_RegBfPtr->ADC_GRP0_CFG.MAP_SCOM_FLAG_EN = (uint32)Cmd;
        Adc_RegBfPtr->ADC_CMD_BUFF0.CMD0_FLAG_EN = (uint32)Cmd;
        Adc_RegBfPtr->ADC_CMD_BUFF0.CMD1_FLAG_EN = (uint32)Cmd;
        Adc_RegBfPtr->ADC_CMD_BUFF0.CMD2_FLAG_EN = (uint32)Cmd;
        Adc_RegBfPtr->ADC_CMD_BUFF0.CMD3_FLAG_EN = (uint32)Cmd;
        Adc_RegBfPtr->ADC_CMD_BUFF1.CMD4_FLAG_EN = (uint32)Cmd;
        Adc_RegBfPtr->ADC_CMD_BUFF1.CMD5_FLAG_EN = (uint32)Cmd;
        Adc_RegBfPtr->ADC_CMD_BUFF1.CMD6_FLAG_EN = (uint32)Cmd;
        Adc_RegBfPtr->ADC_CMD_BUFF1.CMD7_FLAG_EN = (uint32)Cmd;
        Adc_RegBfPtr->ADC_GRP1_CFG.LOOP0_SCOM_FLAG_EN = (uint32)Cmd;
        Adc_RegBfPtr->ADC_GRP1_CFG.LOOP1_SCOM_FLAG_EN = (uint32)Cmd;
        Adc_RegBfPtr->ADC_GRP1_CFG.LOOP2_SCOM_FLAG_EN = (uint32)Cmd;
        Adc_RegBfPtr->ADC_GRP1_CFG.LOOP_SCOM_FLAG_EN = (uint32)Cmd;
    }
    else
    {
        ReturnValue = COMMON_ERR;
    }

    return ReturnValue;
}

/**
 * @brief      Adc Set INT Mask/Unmask Function
 *
 * @param[in]  IntType: Select Int type.
 *              - ADC_INT_AWDG_UNDER,
 *              - ADC_INT_AWDG_OVER
 *                ...
 *              - ADC_INT_TRIG_CERR
 *              - ADC_INT_MEAS_TRIG
 *              - ADC_INT_ALL
 * @param[in]  IntMask: Mask/Unmask.
 *              - COMMON_UNMASK
 *              - COMMON_MASK
 *
 * @return     None
 *
 */
void Adc_SetIntMask(Adc_IntType IntType, Common_IntMaskType IntMask)
{
    if(COMMON_UNMASK == IntMask)
    {
        Adc_IntMaskStatus = Adc_IntMaskStatus | Adc_IntStatusTable[IntType];
        (void)Adc_EnableStatusFlag(IntType, COMMON_ENABLE);
        Adc_RegWPtr->ADC_IE = Adc_RegWPtr->ADC_IE | Adc_IntMaskTable[IntType];
    }
    else
    {
        Adc_RegWPtr->ADC_IE = Adc_RegWPtr->ADC_IE & (~Adc_IntMaskTable[IntType]);
        Adc_IntMaskStatus = Adc_IntMaskStatus &(~Adc_IntStatusTable[IntType]);
    }
}

/**
 * @brief      Adc Clear INT Status Function
 *
 * @param[in]  IntType: Select Int type.
 *              - ADC_INT_AWDG_UNDER,
 *              - ADC_INT_AWDG_OVER
 *                ...
 *              - ADC_INT_PMU_OT
 *              - ADC_INT_MEAS_TRIG
 *              - ADC_INT_ALL 
 *
 * @return     None
 *
 */
void Adc_ClearIntStatus(Adc_IntType IntType)
{
    Adc_RegWPtr->ADC_STAT = Adc_IntStatusTable[IntType];
}

/**
 * @brief      Adc Get INT status Function
 *
 * @param[in]  IntType: Select Int type.
 *              - ADC_INT_AWDG_UNDER,
 *              - ADC_INT_AWDG_OVER
 *                ...
 *              - ADC_INT_TRIG_CERR
 *              - ADC_INT_MEAS_TRIG
 *              - ADC_INT_ALL
 *
 * @return     IntStatus
 *
 */
Common_IntStatusType Adc_GetIntStatus(Adc_IntType IntType)
{
    Common_IntStatusType ReturnValue = COMMON_RESET;
       
    if((Adc_RegWPtr->ADC_STAT & Adc_IntStatusTable[IntType]) != 0UL)
    {
        ReturnValue = COMMON_SET;
    }

    return ReturnValue;
}

/**
 * @brief      Adc install interrupt callback function
 *
 * @param[in]  IntType: Select Int type.
 *              - ADC_INT_AWDG_UNDER,
 *              - ADC_INT_AWDG_OVER
 *                ...
 *              - ADC_INT_TRIG_CERR
 *              - ADC_INT_MEAS_TRIG
 * @param[in]  CbFun: Callback function .
 *
 * @return     None
 *
 */
void Adc_InstallCallBackFunc(Adc_IntType IntType, Isr_CbFuncType * CbFun)
{
    if(IntType < ADC_INT_ALL)
    {
        if((IntType != ADC_INT_GDU_OT) && (IntType != ADC_INT_PMU_OT))
        {
            Adc_IsrCbFuncPtr[IntType] = CbFun;
        }  
    }
}

/** @} end of group Public_FunctionDefinition */
