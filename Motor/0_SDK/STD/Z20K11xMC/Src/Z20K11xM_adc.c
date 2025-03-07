/**************************************************************************************************/
/**
 * @file      : Z20K11xM_adc.c
 * @brief     : ADC module driver file.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (c) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#include "Z20K11xM_adc.h"

/** @addtogroup  Z20K11X_Peripheral_Driver
 *  @{
 */

/** @defgroup ADC ADC
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

#define ADC_NUM                   0x1U

/** @} end of group ADC_Private_Defines */

/** @defgroup ADC_Private_Variables
 *  @{
 */

 /**
  *  @brief ADC interrupt ID definition
  */
static const uint32_t ADC_IntStatusTable[] =
{
	0x00000001U,               /*!< ADC_FWM_INT */
	0x00000002U,               /*!< ADC_FOF_INT */
	0x00000004U,               /*!< ADC_TCOMP_INT */
	0x00000008U,               /*!< ADC_CMP_INT */
	0x00000200U,               /*!< ADC_ERR_INT */
	0x0000020FU                /*!< ADC_INT_ALL */
};

static uint32_t adcIntMaskStatus = 0U;

/**
 *  @brief ADC0 address array
 */
 /*PRQA S 0303,0306 ++*/
static adc_reg_t * const adcRegPtr[ADC_NUM] = 
{
    (adc_reg_t *)ADC0_BASE_ADDR
};

static adc_reg_w_t * const adcRegWPtr[ADC_NUM] =
{
	(adc_reg_w_t *)ADC0_BASE_ADDR
};
/*PRQA S 0303,0306 --*/

/**
 *  @brief ADC ISR callback function pointer array
 */
static isr_cb_t * adcIsrCbFunc[ADC_NUM][ADC_INT_ALL] = 
{
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
static void ADC_IntHandler(ADC_ID_t adcId);
/** @} end of group ADC_Private_FunctionDeclaration */

/** @defgroup ADC_Private_Functions
 *  @{
 */
/**
 * @brief      ADC interrupt handle
 * @param[in]  adcId: Select the ADC ID: ADC0_ID,....
 *
 * @return     none
 *
 */
static void ADC_IntHandler(ADC_ID_t adcId)
{
    uint32_t intStatus;

    adc_reg_t * ADCx = (adc_reg_t *)(adcRegPtr[adcId]);
    adc_reg_w_t * ADCWx = (adc_reg_w_t *) (adcRegWPtr[adcId]);

    /* get interrupt status */
    intStatus = ADCWx->ADC_STAT; 
    /* only check enabled interrupts */
    intStatus = intStatus & adcIntMaskStatus;
    /* clear interrupt status */
    ADCWx->ADC_STAT = intStatus;

    /* FIFO Watermark Interrupt */
    if((intStatus & ADC_IntStatusTable[ADC_FWM_INT]) != 0U)
    {
        if(adcIsrCbFunc[adcId][ADC_FWM_INT] != NULL)
        {
            /* Check fifo ready flag, it represents the FIFO holding data above 
             * watermark level. This is a workaround for Errata ADC.1, please  
             * refer to Errata doc for more information.
             */
            if(ADCx->ADC_STAT.RDY == 1U)
            {
                /* call the callback function */
                adcIsrCbFunc[adcId][ADC_FWM_INT]();
            }
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            ADCx->ADC_IE.FWM_IE = 0U;
        }
    }

    /* FIFO Overflow Interrupt */
    if((intStatus & ADC_IntStatusTable[ADC_FOF_INT]) != 0U)
    {
        if(adcIsrCbFunc[adcId][ADC_FOF_INT] != NULL)
        {
            /* call the callback function */
            adcIsrCbFunc[adcId][ADC_FOF_INT]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            ADCx->ADC_IE.FOF_IE = 0U;
        }
    }

    /* Adc Complete Interrupt */
    if((intStatus & ADC_IntStatusTable[ADC_TCOMP_INT]) != 0U)
    {
        if(adcIsrCbFunc[adcId][ADC_TCOMP_INT] != NULL)
        {
            /* call the callback function */
            adcIsrCbFunc[adcId][ADC_TCOMP_INT]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            ADCx->ADC_IE.TCOM_IE = 0U;
        }
    }

    /* Adc Compare Interrupt */
    if((intStatus & ADC_IntStatusTable[ADC_CMP_INT]) != 0U)
    {
        if(adcIsrCbFunc[adcId][ADC_CMP_INT] != NULL)
        {
            /* call the callback function */
            adcIsrCbFunc[adcId][ADC_CMP_INT]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            ADCx->ADC_IE.CMP_IE = 0U;
        }
    }
    
        /* Adc trigger confict error Interrupt */
    if((intStatus & ADC_IntStatusTable[ADC_TC_ERR_INT]) != 0U)
    {
        if(adcIsrCbFunc[adcId][ADC_TC_ERR_INT] != NULL)
        {
            /* call the callback function */
            adcIsrCbFunc[adcId][ADC_TC_ERR_INT]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            ADCx->ADC_IE.ERR_INT_IE = 0U;
        }
    }
}

/**
 * @brief      ADC IRQHandler
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

/** @} end of group ADC_Private_Functions */

/** @defgroup ADC_Public_Functions
 *  @{
 */

/**
 * @brief      Adc Software Reset Function
 *
 * @param[in]  adcId: Select the ADC ID
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
        i = i + 1U;
    }
}


/**
 * @brief      Adc Initializes Function
 *
 * @param[in]  adcId: Select the ADC ID: ADC0_ID,....
 * @param[in]  adcConfigSet: Pointer to a ADC configuration structure.
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
    }
    
    ADCx->ADC_CFG.REF_SEL = (uint32_t)adcConfigSet->adcVrefSource;
    ADCx->ADC_CFG.RES = (uint32_t)adcConfigSet->adcResolution;
    ADCx->ADC_CFG.CTYPE = (uint32_t)adcConfigSet->adcConversionMode;
    ADCx->ADC_CFG.AVGS = (uint32_t)adcConfigSet->adcAvgsSelect;
    ADCx->ADC_CFG.STS = (uint32_t)adcConfigSet->adcSampleTime;
}

/**
 * @brief      Adc Reset(Terminate) Loop Mode for TDG Trigger Function
 *
 * @param[in]  adcId: Select the ADC ID: ADC0_ID,....
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
 * @brief      Adc Channel Configurate Function
 *
 * @param[in]  adcId: Select the ADC ID: ADC0_ID,....
 * @param[in]  channelConfig: Pointer to a ADC channel configuration structure.
 *
 * @return     none
 *
 */
void ADC_ChannelConfig(ADC_ID_t adcId, 
    const ADC_ChannelConfig_t* channelConfig)
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
 * @brief      Adc TDG Trigger Configurate Function
 *
 * @param[in]  adcId: Select the ADC ID: ADC0_ID,....
 * @param[in]  triggerConfig: Pointer to a ADC TDG trigger configuration 
                              structure.
 *
 * @return     none
 *
 */
void ADC_TDGTriggerConfig(ADC_ID_t adcId, 
    const ADC_TDGTriggerConfig_t* triggerConfig)
{
    adc_reg_t * ADCx = (adc_reg_t *)(adcRegPtr[adcId]);
    ADCx->ADC_CTRL.TRIG_MODE = (uint32_t)triggerConfig->adcTDGTrigMode;
    ADCx->ADC_CMD_BUFF0.CMD0 = (uint32_t)triggerConfig->adcCmd0;
    ADCx->ADC_CMD_BUFF0.CMD1 = (uint32_t)triggerConfig->adcCmd1;
    ADCx->ADC_CMD_BUFF0.CMD2 = (uint32_t)triggerConfig->adcCmd2;
    ADCx->ADC_CMD_BUFF0.CMD3 = (uint32_t)triggerConfig->adcCmd3;
    ADCx->ADC_CMD_BUFF1.CMD4 = (uint32_t)triggerConfig->adcCmd4;
    ADCx->ADC_CMD_BUFF1.CMD5 = (uint32_t)triggerConfig->adcCmd5;
}

/**
 * @brief      Adc Enable Function
 *
 * @param[in]  adcId: Select the ADC ID: ADC0_ID,....
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
 * @param[in]  adcId: Select the ADC ID: ADC0_ID,....
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
 * @brief      Adc Compare Configurate Function
 *
 * @param[in]  adcId: Select the ADC ID: ADC0_ID,....
 * @param[in]  compareConfig: Pointer to a ADC compare configuration structure.
 *                    adcCompareMode: Compare Mode
 *                                     - ADC_COMPARE_MODE_DISABLED
 *                                     - ADC_COMPARE_MODE_LESS_CVL
 *                                     - ADC_COMPARE_MODE_GREATER_CVL
 *                                     - ADC_COMPARE_MODE_EQUAL_CVL
 *                                     - ADC_COMPARE_MODE_WITHIN_CVL_CVH
 *                                     - ADC_COMPARE_MODE_OUT_OF_RANGE_CVL_CVH.
 *                    cvl: Compare Value Low, which is used in below modes:
 *                                     - ADC_COMPARE_MODE_LESS_CVL
 *                                     - ADC_COMPARE_MODE_GREATER_CVL
 *                                     - ADC_COMPARE_MODE_EQUAL_CVL
 *                                     - ADC_COMPARE_MODE_WITHIN_CVL_CVH
 *                                     - ADC_COMPARE_MODE_OUT_OF_RANGE_CVL_CVH
 *                    cvh: Compare Value High, which is used in below modes:
 *                                     - ADC_COMPARE_MODE_WITHIN_CVL_CVH
 *                                     - ADC_COMPARE_MODE_OUT_OF_RANGE_CVL_CVH
 *
 * @return     none
 *
 */
void ADC_CompareConfig(ADC_ID_t adcId, 
    const ADC_CompareConfig_t* compareConfig)
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
 * @param[in]  adcId: Select the ADC ID: ADC0_ID,....
 *
 * @param[in]  cmd: Enable/Disable.
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
 * @param[in]  adcId: Select the ADC ID: ADC0_ID,....
 *
 * @return     FIFO size.
 *
 */
uint32_t ADC_GetFifoSize(ADC_ID_t adcId)
{
    adc_reg_t const volatile * ADCx = (adc_reg_t *)(adcRegPtr[adcId]);
    
    return (uint32_t) ADCx->ADC_PARAM.FIFO_SIZE;
}

/**
 * @brief      Adc FIFO Depth Redefine Function
 *
 * @param[in]  adcId: Select the ADC ID
 * @param[in]  fifoDepth: FIFO depth Configuration.
 *
 * @return     none
 *
 */
void ADC_FifoDepthRedefine(ADC_ID_t adcId, uint8_t fifoDepth)
{
    adc_reg_t * ADCx = (adc_reg_t *)(adcRegPtr[adcId]);
    
    ADCx->ADC_FCTRL.FDRD = fifoDepth;
}

/**
 * @brief      Adc FIFO Watermark Configurate Function
 *
 * @param[in]  adcId: Select the ADC ID
 * @param[in]  fwmark: FIFO watermark configration.
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
 * @brief      Adc Get data size in FIFO Function  
 *
 * @param[in]  adcId: Select the ADC ID
 *
 * @return     Data size in FIFO.
 *
 */
uint32_t ADC_GetNumOfFifoData(ADC_ID_t adcId)
{
    adc_reg_t const volatile * ADCx = (adc_reg_t *)(adcRegPtr[adcId]);
    
    return (uint32_t) ADCx->ADC_FCTRL.FCOUNT;
}

/**
 * @brief      Adc Dma Request Command Function
 *
 * @param[in]  adcId: Select the ADC ID
 * @param[in]  cmd: Enable/Disable.
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
 * @param[in]  adcId: Select the ADC ID
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
 * @param[in]  adcId: Select the ADC ID
 *
 * @return     Conversion Result: bit[11:0] is conversion data; bit[16:12] is 
                                  conversion channel.
 *
 */
uint32_t ADC_GetConversionResult(ADC_ID_t adcId)
{
    adc_reg_t const volatile * ADCx = (adc_reg_t *)(adcRegPtr[adcId]);
    
    return (uint32_t) ADCx->ADC_DATA_RD.ADC_DATA_RD;
}

/**
 * @brief      Adc Get Status Function
 *
 * @param[in]  adcId: Select the ADC ID
 * @param[in]  statusType: Status Type
 *                                     - ADC_STATUS_FWM_INT
 *                                     - ADC_STATUS_FOF_INT
 *                                     - ADC_STATUS_TCOMP_INT
 *                                     - ADC_STATUS_CMP_INT
 *                                     - ADC_STATUS_DMA_REQ
 *                                     - ADC_STATUS_FIFO_RDY
 *                                     - ADC_STATUS_CAL_RDY
 *                                     - ADC_STATUS_ACTIVE 
 *                                     - ADC_STATUS_LOOP_IDLE
 *                                     - ADC_STATUS_TC_ERR_INT
 *
 * @return     status: RESET, SET
 *
 */
FlagStatus_t ADC_GetStatus(ADC_ID_t adcId, ADC_Status_t statusType)
{   
    adc_reg_w_t const volatile * ADCWx = (adc_reg_w_t *) adcRegWPtr[adcId];
  
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
 * @param[in]  adcId: Select the ADC ID: ADC0_ID,....
 * @param[in]  intType: Interrupt Type
 *                                     - ADC_FWM_INT.
 *                                     - ADC_FOF_INT
 *                                     - ADC_TCOMP_INT
 *                                     - ADC_CMP_INT
 *                                     - ADC_TC_ERR_INT
 * @param[in]  intMask: Mask Type
 *                                     - UNMASK
 *                                     - MASK
 *
 * @return     none.
 *
 */
void ADC_IntMask(ADC_ID_t adcId, ADC_INT_t intType, IntMask_t intMask)
{   
    adc_reg_w_t * ADCWx = (adc_reg_w_t *) (adcRegWPtr[adcId]);

    /**
     *  @brief ADC interrupt ID definition
     */
    static const uint32_t ADC_IntMaskTable[] =
    {
        0x00000001U,               /*!< ADC_FWM_INT */
        0x00000002U,               /*!< ADC_FOF_INT */
        0x00000004U,               /*!< ADC_TCOMP_INT */
        0x00000008U,               /*!< ADC_CMP_INT */
        0x00000020U,               /*!< ADC_ERR_INT */
        0x0000002FU                /*!< ADC_INT_ALL */
    };
    
    if(UNMASK == intMask)
    {
        ADCWx->ADC_IE = ADCWx->ADC_IE | ADC_IntMaskTable[intType];
        adcIntMaskStatus = adcIntMaskStatus | ADC_IntStatusTable[intType];
    }
    else
    {
        ADCWx->ADC_IE = ADCWx->ADC_IE & (~ADC_IntMaskTable[intType]);
        adcIntMaskStatus = adcIntMaskStatus &(~ADC_IntStatusTable[intType]);
    }
}

/**
 * @brief      Adc Interrupt Clear Status Function
 *
 * @param[in]  adcId: Select the ADC ID
 * @param[in]  intType: Interrupt Type  
 *                                     - ADC_FWM_INT.
 *                                     - ADC_FOF_INT
 *                                     - ADC_TCOMP_INT
 *                                     - ADC_CMP_INT
 *                                     - ADC_TC_ERR_INT
 *                                     - ADC_INT_ALL
 *
 * @return     none.
 *
 */
void ADC_IntClear(ADC_ID_t adcId, ADC_INT_t intType)
{
    adc_reg_w_t * ADCWx = (adc_reg_w_t *) (adcRegWPtr[adcId]);
    
    ADCWx->ADC_STAT = ADCWx->ADC_STAT | ADC_IntStatusTable[intType];
}

/**
 * @brief      Adc Get Interrupt Status Function
 *
 * @param[in]  adcId: Select the ADC ID
 * @param[in]  intType: Interrupt Type   
 *                                     - ADC_FWM_INT.
 *                                     - ADC_FOF_INT
 *                                     - ADC_TCOMP_INT
 *                                     - ADC_CMP_INT
 *                                     - ADC_TC_ERR_INT
 *
 * @return     status: RESET, SET
 *
 */
FlagStatus_t ADC_GetIntStatus(ADC_ID_t adcId, ADC_INT_t intType)
{
    adc_reg_w_t const volatile * ADCWx = (adc_reg_w_t *) (adcRegWPtr[adcId]);
    FlagStatus_t bitStatus = RESET;
   
    if((ADCWx->ADC_STAT & ADC_IntStatusTable[intType]) != 0UL)
    {
        bitStatus = SET;
    }

    return bitStatus;
}

/**
 * @brief      install call back function
 *
 * @param[in]  adcId: Select the ADC ID
 * @param[in]  intType: select the interrupt type
 *                                     - ADC_FWM_INT.
 *                                     - ADC_FOF_INT
 *                                     - ADC_TCOMP_INT
 *                                     - ADC_CMP_INT
 *                                     - ADC_TC_ERR_INT
 * @param[in]  cbFun: pointer to callback function
 *
 * @return     none
 *
 */
void ADC_InstallCallBackFunc(ADC_ID_t adcId, ADC_INT_t intType, 
    isr_cb_t * cbFun)
{
    adcIsrCbFunc[adcId][intType] = cbFun;
}

/** @} end of group ADC_Public_Functions */

/** @} end of group ADC_definitions */

/** @} end of group Z20K11X_Peripheral_Driver */
