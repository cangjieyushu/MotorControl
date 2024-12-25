/**************************************************************************************************/
/**
 * @file     adc_drv.c
 * @brief    ADC module driver file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#include "adc_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @defgroup ADC
 *  @brief ADC driver modules
 *  @{
 */

/** @defgroup ADC_Private_Type
 *  @{
 */

/*@} end of group ADC_Private_Type*/

/** @defgroup ADC_Private_Defines
 *  @{
 */

#define ADC_NUM                   (0x2U)    /*!< Total ADC instance number on chip */

/** @} end of group ADC_Private_Defines */

/** @defgroup ADC_Private_Variables
 *  @{
 */

/**
 *  @brief ADC interrupt ID definition
 */
static const uint32_t adcIntMaskTable[] =
{
	0x00000001U,               /*!< ADC_FWM_INT */
	0x00000002U,               /*!< ADC_FOF_INT */
	0x00000004U,               /*!< ADC_TCOMP_INT */
	0x00000008U,               /*!< ADC_CMP_INT */
	0x00000020U,               /*!< ADC_ERR_INT */
	0x0000002FU                /*!< ADC_INT_ALL */
};

static const uint32_t adcIntStatusTable[] =
{
	0x00000001U,               /*!< ADC_FWM_INT */
	0x00000002U,               /*!< ADC_FOF_INT */
	0x00000004U,               /*!< ADC_TCOMP_INT */
	0x00000008U,               /*!< ADC_CMP_INT */
	0x00000200U,               /*!< ADC_ERR_INT */
	0x0000020FU                /*!< ADC_INT_ALL */
};

static uint32_t adcIntMaskStatus[ADC_NUM] = 
{
    0U,
    0U
};

/**
 *  @brief ADC0 and ADC1 instance address array
 */
 /*PRQA S 0303 ++*/
static adc_reg_t * const adcRegPtr[ADC_NUM] = 
{
    (adc_reg_t *)ADC0_BASE_ADDR,
    (adc_reg_t *)ADC1_BASE_ADDR
};

static adc_reg_w_t * const adcRegWPtr[ADC_NUM] =
{
    (adc_reg_w_t *)ADC0_BASE_ADDR,
    (adc_reg_w_t *)ADC1_BASE_ADDR
};
/*PRQA S 0303 --*/

/**
 *  @brief ADC IRQHandler callback function pointer array
 */
static isr_cb_t * adcIsrCbFunc[ADC_NUM][ADC_INT_ALL] = 
{
    {NULL,NULL,NULL,NULL,NULL},
    {NULL,NULL,NULL,NULL,NULL}
};

/** @} end of group ADC_Private_Variables */

/** @defgroup ADC_Global_Variables
 *  @{
 */

/** @} end of group ADC_Global_Variables */

/** @defgroup ADC_Private_FunctionDeclaration
 *  @{
 */
void ADC0_DriverIRQHandler(void);
void ADC1_DriverIRQHandler(void);
static void ADC_IntHandler(ADC_ID_t adcId);
/** @} end of group ADC_Private_FunctionDeclaration */

/** @defgroup ADC_Private_Functions
 *  @{
 */
/**
 * @brief      ADC interrupt handler
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 *
 * @return none
 *
 */
static void ADC_IntHandler(ADC_ID_t adcId)
{
    uint32_t intStatus;
    uint32_t localCount;

    adc_reg_t * ADCx = (adc_reg_t *)(adcRegPtr[adcId]);
    adc_reg_w_t * ADCWx = (adc_reg_w_t *) (adcRegWPtr[adcId]);

    /* get interrupt status */
    intStatus = ADCWx->ADC_STAT; 
    /* only check enabled interrupts */
    intStatus = intStatus & adcIntMaskStatus[adcId];
    /* clear interrupt status, excluding FIFO Watermark Interrupt*/
    ADCWx->ADC_STAT = intStatus & (~adcIntStatusTable[ADC_FWM_INT]);

    /* FIFO Watermark Interrupt */
    if((intStatus & adcIntStatusTable[ADC_FWM_INT]) != 0U)
    {
        if(adcIsrCbFunc[adcId][ADC_FWM_INT] != NULL)
        {
            /* call the callback function */
            adcIsrCbFunc[adcId][ADC_FWM_INT]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            ADCx->ADC_IE.FWM_IE = 0U;
        }

        /* Clear FIFO Watermark Interrupt after callback. */
        ADCWx->ADC_STAT = adcIntStatusTable[ADC_FWM_INT];
    }

    /* Handle FIFO Overflow Interrupt, Complete Interrupt, Compare Interrupt, and Trigger Conflict 
        Error Interrupt*/
    for(localCount = (uint32_t)ADC_FOF_INT; localCount <= (uint32_t)ADC_TC_ERR_INT; localCount ++)
    {
        if((intStatus & adcIntStatusTable[localCount]) != 0U)
        {
            if(adcIsrCbFunc[adcId][localCount] != NULL)
            {
                /* call the callback function */
                adcIsrCbFunc[adcId][localCount]();
            }
            /* Disable the interrupt if callback function is not setup */
            else
            {
                ADCWx->ADC_IE &= ~(adcIntMaskTable[localCount]);
            }
        }
    }

    COMMON_DSB();

}

/**
 * @brief      ADC0 Interrupt Handler
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
void ADC0_DriverIRQHandler(void)
{
    ADC_IntHandler(ADC0_ID);
}

/**
 * @brief      ADC1 Interrupt Handler
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
void ADC1_DriverIRQHandler(void)
{
    ADC_IntHandler(ADC1_ID);
}

/** @} end of group ADC_Private_Functions */

/** @defgroup ADC_Public_Functions
 *  @{
 */

/**
 * @brief      Adc Software Reset Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 *
 * @return     none
 *
 */
void ADC_SoftwareReset(ADC_ID_t adcId)
{
    volatile uint32_t i = 0U;
    adc_reg_t * ADCx = (adc_reg_t *)(adcRegPtr[adcId]);
    
    ADCx->ADC_CTRL.RST = 1U;
    
    while(i < ADC_TIMEOUT_WAIT_CNT_SWRST)
    {
        i++;
    }
}

/**
 * @brief      Adc Initialize Function
 *
 * @param[in]  adcId:         Select the ADC ID:
 *                               - ADC0_ID
 *                               - ADC1_ID
 * @param[in]  adcConfigSet:  Pointer to a ADC configuration structure.
 *
 * @return     none
 *
 */
void ADC_Init(ADC_ID_t adcId, const ADC_Config_t* adcConfigSet)
{   
    adc_reg_t * ADCx = (adc_reg_t *)(adcRegPtr[adcId]);
    
    if(ADC_TDG_TRIGGER == adcConfigSet->adcTriggerMode)
    {
        ADCx->ADC_CTRL.TRIG_MODE_ENABLE = 1U;
    }
    else
    {
        ADCx->ADC_CTRL.TRIG_MODE_ENABLE = 0U;
        ADCx->ADC_CFG.HWT_EN = (uint32_t)adcConfigSet->adcTriggerMode;
    }
    
    ADCx->ADC_CFG.REF_SEL = (uint32_t)adcConfigSet->adcVrefSource;
    ADCx->ADC_CFG.RES = (uint32_t)adcConfigSet->adcResolution;
    ADCx->ADC_CFG.CTYPE = (uint32_t)adcConfigSet->adcConversionMode;
    ADCx->ADC_CFG.AVGS = (uint32_t)adcConfigSet->adcAvgsSelect;
    ADCx->ADC_CFG.STS = (uint32_t)adcConfigSet->adcSampleTime;
    ADCx->ADC_CTRL.STABLE_T = (uint32_t)adcConfigSet->adcStableTime;
    ADCx->ADC_CTRL.IREF_SEL = (uint32_t)ADC_IREF_SELECT_INTERNAL;
}

/**
 * @brief      Adc Reset(Terminate) Loop Mode for TDG Trigger Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 *
 * @return     none
 *
 */
void ADC_ResetLoopMode(ADC_ID_t adcId)
{
    adc_reg_t * ADCx = (adc_reg_t *)(adcRegPtr[adcId]);
    ADCx->ADC_CTRL.MODE1_RST = 1U;
}

/**
 * @brief      Adc Channel Configure Function
 *
 * @param[in]  adcId:           Select the ADC ID:
 *                                - ADC0_ID
 *                                - ADC1_ID
 * @param[in]  channelConfig:   Pointer to a ADC channel configuration structure.
 *
 * @return     none
 *
 */
void ADC_ChannelConfig(ADC_ID_t adcId, const ADC_ChannelConfig_t* channelConfig)
{   
    adc_reg_t * ADCx = (adc_reg_t *)(adcRegPtr[adcId]);
    
    ADCx->ADC_CFG.DIFF_MODE = (uint32_t)channelConfig->adcDifferentialMode;
    ADCx->ADC_CFG.CHSELP = (uint32_t)channelConfig->adcChannelP;
    
    if(ADC_DIFF_MODE == channelConfig->adcDifferentialMode)
    {
        ADCx->ADC_CFG.CHSELN = (uint32_t)channelConfig->adcChannelN;
    }
}

/**
 * @brief      Adc TDG Trigger Configure Function
 *
 * @param[in]  adcId:            Select the ADC ID:
 *                                 - ADC0_ID
 *                                 - ADC1_ID
 * @param[in]  triggerConfig:    Pointer to a ADC TDG trigger configuration structure.
 *
 * @return     none
 *
 */
void ADC_TDGTriggerConfig(ADC_ID_t adcId, const ADC_TDGTriggerConfig_t* triggerConfig)
{
    adc_reg_t * ADCx = (adc_reg_t *)(adcRegPtr[adcId]);

    ADCx->ADC_CTRL.TRIG_MODE = (uint32_t)triggerConfig->adcTDGTrigMode;

    if(ADC_LOOP_MODE == triggerConfig->adcTDGTrigMode)
    {
        ADCx->ADC_CTRL.LMD = (uint32_t)triggerConfig->loopModeDepth;
    }

    ADCx->ADC_CMD_BUFF0.CMD0 = (uint32_t)triggerConfig->adcCmd0;
    ADCx->ADC_CMD_BUFF0.CMD1 = (uint32_t)triggerConfig->adcCmd1;
    ADCx->ADC_CMD_BUFF0.CMD2 = (uint32_t)triggerConfig->adcCmd2;
    ADCx->ADC_CMD_BUFF0.CMD3 = (uint32_t)triggerConfig->adcCmd3;
    ADCx->ADC_CMD_BUFF1.CMD4 = (uint32_t)triggerConfig->adcCmd4;
    ADCx->ADC_CMD_BUFF1.CMD5 = (uint32_t)triggerConfig->adcCmd5;
}

/**
 * @brief      Adc TDG Trigger CMD Interrupt Enable Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 *
 * @param[in]  cmdId:      CMD identifier:
 *                           - ADC_CMD_BUFFER_CMD0
 *                           - ADC_CMD_BUFFER_CMD1
 *                           - ADC_CMD_BUFFER_CMD2
 *                           - ADC_CMD_BUFFER_CMD3
 *                           - ADC_CMD_BUFFER_CMD4
 *                           - ADC_CMD_BUFFER_CMD5
 *
 * @param[in]  status:     Interrupt Enablement:
 *                           - ENABLE
*                            - DISABLE
 * @return     none
 *
 */
void ADC_TDGTriggerCMDIntEnable(ADC_ID_t adcId, ADC_CmdBuffer_t cmdId, ControlState_t status)
{
    adc_reg_t * ADCx = (adc_reg_t *)(adcRegPtr[adcId]);

    switch(cmdId)
    {
        case ADC_CMD_BUFFER_CMD0:
            ADCx->ADC_CMD_BUFF0.CMD0_INT_EN = (uint32_t)status;
            break;
        case ADC_CMD_BUFFER_CMD1:
            ADCx->ADC_CMD_BUFF0.CMD1_INT_EN = (uint32_t)status;
            break;
        case ADC_CMD_BUFFER_CMD2:
            ADCx->ADC_CMD_BUFF0.CMD2_INT_EN = (uint32_t)status;
            break;
        case ADC_CMD_BUFFER_CMD3:
            ADCx->ADC_CMD_BUFF0.CMD3_INT_EN = (uint32_t)status;
            break;
        case ADC_CMD_BUFFER_CMD4:
            ADCx->ADC_CMD_BUFF1.CMD4_INT_EN = (uint32_t)status;
            break;
        case ADC_CMD_BUFFER_CMD5:
            ADCx->ADC_CMD_BUFF1.CMD5_INT_EN = (uint32_t)status;
            break;
        default:
            /* Nothing to do */
            break;
    }
}

/**
 * @brief      Adc Enable Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 *
 * @return     none
 *
 */
void ADC_Enable(ADC_ID_t adcId)
{
    adc_reg_t * ADCx = (adc_reg_t *)(adcRegPtr[adcId]);
    
    ADCx->ADC_CTRL.ADC_EN = 1U;
}

/**
 * @brief      Adc Disable Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 *
 * @return     none
 *
 */
void ADC_Disable(ADC_ID_t adcId)
{
    adc_reg_t * ADCx = (adc_reg_t *)(adcRegPtr[adcId]);
    
    ADCx->ADC_CTRL.ADC_EN = 0U;
}


/**
 * @brief      Adc Compare Configure Function
 *
 * @param[in]  adcId:    Select the ADC ID:
 *                         - ADC0_ID
 *                         - ADC1_ID
 * @param[in]  compareConfig: Pointer to a ADC compare configuration structure.
 *                       adcCompareMode:
 *                                        - ADC_COMPARE_MODE_DISABLED
 *                                        - ADC_COMPARE_MODE_LESS_CVL
 *                                        - ADC_COMPARE_MODE_GREATER_CVL
 *                                        - ADC_COMPARE_MODE_EQUAL_CVL
 *                                        - ADC_COMPARE_MODE_WITHIN_CVL_CVH
 *                                        - ADC_COMPARE_MODE_OUT_OF_RANGE_CVL_CVH.
 *                       adcCvl:         Compare Value Low, which is used in below modes:
 *                                        - ADC_COMPARE_MODE_LESS_CVL
 *                                        - ADC_COMPARE_MODE_GREATER_CVL
 *                                        - ADC_COMPARE_MODE_EQUAL_CVL
 *                                        - ADC_COMPARE_MODE_WITHIN_CVL_CVH
 *                                        - ADC_COMPARE_MODE_OUT_OF_RANGE_CVL_CVH
 *                       adcCvh:         Compare Value High, which is used in below modes:
 *                                        - ADC_COMPARE_MODE_WITHIN_CVL_CVH
 *                                        - ADC_COMPARE_MODE_OUT_OF_RANGE_CVL_CVH
 *
 * @return     none
 *
 */
void ADC_CompareConfig(ADC_ID_t adcId, const ADC_CompareConfig_t* compareConfig)
{   
    adc_reg_t * ADCx = (adc_reg_t *)(adcRegPtr[adcId]);
    
    ADCx->ADC_CFG.CMPS = (uint32_t)compareConfig->adcCompareMode;
    
    if(compareConfig->adcCompareMode > ADC_COMPARE_MODE_DISABLED) 
    {
        ADCx->ADC_CV.CVL = (uint32_t)compareConfig->adcCvl;
    }
    
    if(compareConfig->adcCompareMode > ADC_COMPARE_MODE_EQUAL_CVL)
    {
        ADCx->ADC_CV.CVH = (uint32_t)compareConfig->adcCvh;
    }
}

/**
 * @brief      Adc Dozen Control Function
 *
 * @param[in]  adcId:    Select the ADC ID:
 *                         - ADC0_ID
 *                         - ADC1_ID
 *
 * @param[in]  cmd:      Doze Enablement
 *                         - Enable
 *                         - Disable
 *
 * @return     none
 *
 */
void ADC_DozeControl(ADC_ID_t adcId, ControlState_t cmd)
{ 
    adc_reg_t * ADCx = (adc_reg_t *)(adcRegPtr[adcId]);
    
    ADCx->ADC_CTRL.DOZEN = (uint32_t)cmd;
}

/**
 * @brief      Adc Get FIFO size Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 *
 * @return     FIFO size.
 *
 */
uint32_t ADC_GetFifoSize(ADC_ID_t adcId)
{
    adc_reg_t * ADCx = (adc_reg_t *)(adcRegPtr[adcId]);
    
    return (uint32_t) ADCx->ADC_PARAM.FIFO_SIZE;
}

/**
 * @brief      Adc FIFO Depth Redefine Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 * @param[in]  fifoDepth:  New FIFO Depth Value.
 *
 * @return none
 *
 */
void ADC_FifoDepthRedefine(ADC_ID_t adcId, uint8_t fifoDepth)
{
    adc_reg_t * ADCx = (adc_reg_t *)(adcRegPtr[adcId]);
    
    ADCx->ADC_FCTRL.FDRD = fifoDepth;
}

/**
 * @brief      Adc FIFO Watermark Configure Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 * @param[in]  fwmark:     New FIFO Watermark Value.
 *
 * @return     none
 *
 */
void ADC_FifoWatermarkConfig(ADC_ID_t adcId, uint8_t fwmark)
{
    adc_reg_t * ADCx = (adc_reg_t *)(adcRegPtr[adcId]);
    
    ADCx->ADC_FCTRL.FWMARK = fwmark;
}

/**
 * @brief      Adc Get Data Size in FIFO Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 *
 * @return     Data size in FIFO.
 *
 */
uint32_t ADC_GetNumOfFifoData(ADC_ID_t adcId)
{
    adc_reg_t * ADCx = (adc_reg_t *)(adcRegPtr[adcId]);
    
    return (uint32_t) ADCx->ADC_FCTRL.FCOUNT;
}

/**
 * @brief      Adc Dma Request Command Function
 *
 * @param[in]  adcId:    Select the ADC ID:
 *                         - ADC0_ID
 *                         - ADC1_ID
 * @param[in]  cmd:      DMA Request Enablement
 *                         - Enable
 *                         - Disable.
 *
 * @return     none
 *
 */
void ADC_DmaRequestCmd(ADC_ID_t adcId, ControlState_t cmd)
{
    adc_reg_t * ADCx = (adc_reg_t *)(adcRegPtr[adcId]);
    
    ADCx->ADC_IE.FWMDE = (uint32_t)cmd;
}

/**
 * @brief      Adc Software Trigger Control Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 *
 * @return     none
 *
 */
void ADC_SoftwareTrigger(ADC_ID_t adcId)
{   
    adc_reg_t * ADCx = (adc_reg_t *)(adcRegPtr[adcId]);
    
    ADCx->ADC_SWTRIG.ADC_SWTRIG = 1U;
}

/**
 * @brief      Adc Get Conversion Result Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 *
 * @return     Conversion Result
 *
 */
uint32_t ADC_GetConversionResult(ADC_ID_t adcId)
{
    adc_reg_t * ADCx = (adc_reg_t *)(adcRegPtr[adcId]);
    
    return ADCx->ADC_DATA_RD.ADC_DATA_RD;
}

/**
 * @brief      Adc Get Status Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 * @param[in]  statusType: Status Type :
 *                           - ADC_STATUS_FWM_INT
 *                           - ADC_STATUS_FOF_INT
 *                           - ADC_STATUS_TCOMP_INT
 *                           - ADC_STATUS_CMP_INT
 *                           - ADC_STATUS_DMA_REQ
 *                           - ADC_STATUS_FIFO_RDY
 *                           - ADC_STATUS_ACTIVE 
 *                           - ADC_STATUS_LOOP_IDLE
 *                           - ADC_STATUS_TC_ERR_INT
 *
 * @return     status.
 *
 */
FlagStatus_t ADC_GetStatus(ADC_ID_t adcId, ADC_Status_t statusType)
{   
    adc_reg_w_t * ADCWx = (adc_reg_w_t *) (adcRegWPtr[adcId]);
  
    FlagStatus_t bitStatus = RESET;

    if((ADCWx->ADC_STAT & (0x00000001UL << (uint32_t)statusType)) != 0UL)
    {
        bitStatus = SET;
    }
    
    return bitStatus;
}

/**
 * @brief      Adc Interrupt Mask Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 * @param[in]  intType:    Interrupt Type :
 *                           - ADC_FWM_INT.
 *                           - ADC_FOF_INT
 *                           - ADC_TCOMP_INT
 *                           - ADC_CMP_INT
 *                           - ADC_TC_ERR_INT
 *                           - ADC_INT_ALL
 * @param[in]  intMask:    Mask Type :
 *                           - UNMASK
 *                           - MASK
 *
 * @return     none.
 *
 */
void ADC_IntMask(ADC_ID_t adcId, ADC_INT_t intType, IntMask_t intMask)
{   
    adc_reg_w_t * ADCWx = (adc_reg_w_t *) (adcRegWPtr[adcId]);
    
    if(UNMASK == intMask)
    {
        adcIntMaskStatus[adcId] = adcIntMaskStatus[adcId] | adcIntStatusTable[intType];
        ADCWx->ADC_IE = ADCWx->ADC_IE | adcIntMaskTable[intType];
    }
    else
    {
        ADCWx->ADC_IE = ADCWx->ADC_IE & (~adcIntMaskTable[intType]);
        adcIntMaskStatus[adcId] = adcIntMaskStatus[adcId] &(~adcIntStatusTable[intType]);
    }
}

/**
 * @brief      Adc Interrupt Clear Status Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 * @param[in]  intType:    Interrupt Type :
 *                           - ADC_FWM_INT.
 *                           - ADC_FOF_INT
 *                           - ADC_TCOMP_INT
 *                           - ADC_CMP_INT
 *                           - ADC_TC_ERR_INT
 *                           - ADC_INT_ALL
 *
 * @return     none.
 *
 */
void ADC_IntClear(ADC_ID_t adcId, ADC_INT_t intType)
{
    adc_reg_w_t * ADCWx = (adc_reg_w_t *) (adcRegWPtr[adcId]);
    
    ADCWx->ADC_STAT = adcIntStatusTable[intType];
}

/**
 * @brief      Adc Get Interrupt Status Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 * @param[in]  intType:    Interrupt Type :
 *                           - ADC_FWM_INT
 *                           - ADC_FOF_INT
 *                           - ADC_TCOMP_INT
 *                           - ADC_CMP_INT
 *                           - ADC_TC_ERR_INT
 *
 * @return     none.
 *
 */
FlagStatus_t ADC_GetIntStatus(ADC_ID_t adcId, ADC_INT_t intType)
{
    adc_reg_w_t * ADCWx = (adc_reg_w_t *) (adcRegWPtr[adcId]);
    FlagStatus_t bitStatus = RESET;
   
    if((ADCWx->ADC_STAT & adcIntStatusTable[intType]) != 0UL)
    {
        bitStatus = SET;
    }

    return bitStatus;
}

/**
 * @brief      ADC Set Stable time Function
 *
 * @param[in]  adcId:      Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 *
 * @param[in]  stableTime: 11bits region, make sure the stable time be over 500ns
 *
 * @return none
 *
 */
void ADC_SetStableTime(ADC_ID_t adcId, uint32_t stableTime)
{ 
    adc_reg_t * ADCx = (adc_reg_t *)(adcRegPtr[adcId]);

    ADCx->ADC_CTRL.STABLE_T = stableTime;
}

/**
 * @brief      Install call back function
 *
 * @param[in]  adcId:   Select the ADC ID:
 *                           - ADC0_ID
 *                           - ADC1_ID
 * @param[in]  intType: Select the interrupt
 *                           -  ADC_FWM_INT.
 *                           -  ADC_FOF_INT
 *                           -  ADC_TCOMP_INT
 *                           -  ADC_CMP_INT
 *                           -  ADC_TC_ERR_INT
 * @param[in]  cbFun:   Pointer to callback function
 *
 * @return     none
 *
 */
void ADC_InstallCallBackFunc(ADC_ID_t adcId, ADC_INT_t intType,isr_cb_t * cbFun)
{
    if(intType < ADC_INT_ALL) {
        adcIsrCbFunc[adcId][intType] = cbFun;
    }
    else
    {
        /* Do nothing */
    }
}

/** @} end of group ADC_Public_Functions */

/** @} end of group ADC_definitions */

/** @} end of group Z20K14XM_Peripheral_Driver */
