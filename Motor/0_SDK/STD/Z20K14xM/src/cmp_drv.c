/***************************************************************************//**
 * @file     cmp_drv.c
 * @brief    CMP module driver file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 *
 ******************************************************************************/

#include "cmp_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @defgroup CMP
 *  @brief CMP driver modules
 *  @{
 */

/** @defgroup CMP_Private_Type
 *  @{
 */

/** @} end of group CMP_Private_Type*/

/** @defgroup CMP_Private_Defines
 *  @{
 */

/*PRQA S 0303 ++*/
static cmp_reg_t   *const cmpRegPtr    = (cmp_reg_t *) CMP_BASE_ADDR;         /*!< Analog comparator Register */
static cmp_reg_w_t *const cmpRegWPtr   = (cmp_reg_w_t *) CMP_BASE_ADDR;       /*!< Analog comparator Register */
/*PRQA S 0303 --*/

/** @} end of group CMP_Private_Defines */

/** @defgroup CMP_Private_Variables
 *  @{
 */
static isr_cb_t * cmpIsrCbFunc[CMP_INT_ALL] = 
{
    NULL, NULL
};


static const uint32_t cmpInterruptMaskTable[] =
{
    0x00000001U,      /* CMP_INT_RAISE */
    0x00000002U,      /* CMP_INT_FALL */
    0x00000003U       /* CMP_INT_ALL */
};
/** @} end of group CMP_Private_Variables */

/** @defgroup CMP_Global_Variables
 *  @{
 */

/** @} end of group CMP_Global_Variables */

/** @defgroup CMP_Private_FunctionDeclaration
 *  @{
 */

void CMP_DriverIRQHandler(void);

/** @} end of group CMP_Private_FunctionDeclaration */

/** @defgroup CMP_Private_Functions
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
void CMP_DriverIRQHandler(void)
{
    uint32_t status;
    uint32_t intType;
    
    status = cmpRegWPtr->CMP_CSR;
    /* get status */
    status = status & 0x00000003U;
    status &= cmpRegWPtr->CMP_IER;
    /* clear int status */
    cmpRegWPtr->CMP_CSR = status;
    
    for(intType = (uint32_t)CMP_INT_RAISE; intType < (uint32_t)CMP_INT_ALL; intType++)
    {
        if((status & (0x00000001UL << intType)) != 0U)
        {
            if(cmpIsrCbFunc[intType] != NULL)
            {
                cmpIsrCbFunc[intType]();
            }
            else
            {
                cmpRegWPtr->CMP_IER &= ~(0x00000001UL << intType); 
            }
        }
    }

    COMMON_DSB();
}
/** @} end of group CMP_Private_Functions */

/** @defgroup CMP_Public_Functions
 *  @{
 */
/**
 * @brief      Initialize CMP
 *
 * @param[in]  config: the configuration parameters.
 *                  if config->mode == CMP_MODE_WINDOW or CMP_MODE_WINDOW_FILTER,
 *                  CMP_WindowConfig() need to be called to config window para.
 *                  if config->mode == CMP_MODE_FILTER or CMP_MODE_WINDOW_FILTER,
 *                  CMP_FilterConfig() need to be called to config filter para.
 *
 * @return     none
 *
 */
void CMP_Init(const CMP_Config_t *config)
{
    cmpRegPtr->CMP_CCR0.CMP_SEL = (uint32_t)(config->speed);
    if(CMP_SPEED_LOW == config->speed)
    {
        cmpRegPtr->CMP_CCR2.LS_HSTCTR = (uint32_t)(config->hyst.ls);
        cmpRegPtr->CMP_CCR2.LS_PSEL = (uint32_t)(config->pIn);
        cmpRegPtr->CMP_CCR2.LS_MSEL = (uint32_t)(config->nIn);
    }
    else
    {
        cmpRegPtr->CMP_CCR2.HS_HSTCTR = (uint32_t)(config->hyst.hs);
        cmpRegPtr->CMP_CCR2.HS_PSEL = (uint32_t)(config->pIn);
        cmpRegPtr->CMP_CCR2.HS_MSEL = (uint32_t)(config->nIn);
    }
    
    /* config working mode */
    switch(config->mode)
    {
        case CMP_MODE_BASIC:
            cmpRegPtr->CMP_CCR1.WINDOW_EN = (uint32_t)DISABLE;
            cmpRegPtr->CMP_CCR1.SAMPLE_EN = (uint32_t)DISABLE;
            break;
        
        case CMP_MODE_WINDOW:
            cmpRegPtr->CMP_CCR1.WINDOW_EN = (uint32_t)ENABLE;
            cmpRegPtr->CMP_CCR1.SAMPLE_EN = (uint32_t)DISABLE;
            cmpRegPtr->CMP_CCR1.FILT_CNT = (uint32_t)CMP_FILTER_BYPASSED;
            cmpRegPtr->CMP_CCR1.FILT_PER = 0U;
            break;
        
        case CMP_MODE_FILTER:
            cmpRegPtr->CMP_CCR1.WINDOW_EN = (uint32_t)DISABLE;
            cmpRegPtr->CMP_CCR1.SAMPLE_EN = (uint32_t)DISABLE;
            break;
        
        case CMP_MODE_SAMPLE:
            cmpRegPtr->CMP_CCR1.WINDOW_EN = (uint32_t)DISABLE;
            cmpRegPtr->CMP_CCR1.SAMPLE_EN = (uint32_t)ENABLE;
            cmpRegPtr->CMP_CCR1.FILT_CNT = (uint32_t)CMP_FILTER_1_CONSECUTIVE_SAMPLE;
            cmpRegPtr->CMP_CCR1.FILT_PER = 0U;
            break;
        
        case CMP_MODE_WINDOW_FILTER:
            cmpRegPtr->CMP_CCR1.WINDOW_EN = (uint32_t)ENABLE;
            cmpRegPtr->CMP_CCR1.SAMPLE_EN = (uint32_t)DISABLE;
            break;
            
        default:
        /* Intentionally Empty */
            break;
    }
    
    /* default cout after filter */
    cmpRegPtr->CMP_CCR1.COUT_SEL = 0U;
    
    cmpRegPtr->CMP_CCR0.STOP_EN = (uint32_t)(config->stopReqEn);
    /* select DMA / interrupt request */
    cmpRegPtr->CMP_CCR1.DMA_EN = (uint32_t)(config->req);
    /* invert output or not */
    cmpRegPtr->CMP_CCR1.COUT_INV = (uint32_t)(config->invertEn);
    /* output to pad or not */
    cmpRegPtr->CMP_CCR1.COUT_PEN = (uint32_t)(config->outToPad);  
    
}

/**
 * @brief      select the output 
 *
 * @param[in]  out: select the output position
 *                    - CMP_OUT_FILTER_SAMPLE
 *                    - CMP_OUT_WINDOW
 *
 * @return     None
 *
 */
void CMP_SelectOutput(CMP_Output_t out)
{
    cmpRegPtr->CMP_CCR1.COUT_SEL = (uint32_t)out;
}

/**
 * @brief      Config filter parameters
 *
 * @param[in]  count: the consecutive sample count number that agree the output 
 *                  value to be changed. The range is 1 - 7. If it is 0, the 
 *                  filter is bypassed.
 * @param[in]  period: the sampling period in bus clock of the output filter.
 *                     The range is 1-0xff. If it is 0, filter is bypassed
 *
 * @return     None
 *
 */
void CMP_FilterConfig(CMP_FilterSampleCount_t count, uint8_t period)
{
    cmpRegPtr->CMP_CCR1.FILT_PER = period;
    cmpRegPtr->CMP_CCR1.FILT_CNT = (uint32_t)count;    
}

/**
 * @brief      Config window mode parameter
 *
 * @param[in]  closedLvl: Select the output level when window is closed
 *
 * @return     None
 *
 */ 
void CMP_WindowConfig(CMP_WinOutLvl_t closedLvl)
{
    if(CMP_WIN_OUT_LVL_LAST == closedLvl)
    {
        cmpRegPtr->CMP_CCR1.COUT_OWE = 0U;
    }
    else
    {
        cmpRegPtr->CMP_CCR1.COUT_OWE = 1U;
        cmpRegPtr->CMP_CCR1.COUT_OW = ((uint32_t)closedLvl) >> 1U;
    }
}

/**
 * @brief      Initialize DAC
 *
 * @param[in]  vref: Select the reference voltage
 *                     - CMP_DAC_VREF_VDDA
 *                     - CMP_DAC_VREF_VREFH
 *
 * @return     None
 *
 */   
void CMP_DacSetRefVoltage(CMP_DACVref_t vref)
{
    cmpRegPtr->CMP_DCR.VREF_SEL = (uint32_t)vref;
}

/**
 * @brief      DAC buffer control
 *
 * @param[in]  cmd: ENABLE or DISABLE
 *
 * @return     None
 *
 */   
void CMP_DacBufferControl(ControlState_t cmd)
{
    cmpRegPtr->CMP_DCR.DAC_BUFF_EN = (uint32_t)cmd;
}

/**
 * @brief      Enable DAC 
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void CMP_DacEnable(void)
{
    cmpRegPtr->CMP_DCR.DAC_EN = 1U;
}

/**
 * @brief      Disable DAC
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void CMP_DacDisable(void)
{
    cmpRegPtr->CMP_DCR.DAC_EN = 0U;
}

/**
 * @brief      set DAC output value
 *
 * @param[in]  data: the data to be converted. The range is 0 - 0xFF.
 *
 * @return     None
 *
 */
void CMP_DacSetValue(uint8_t data)
{
    cmpRegPtr->CMP_DCR.DAC_SEL = data;
}

/**
 * @brief      Trigger CMP
 *
 * @param[in]  type: Select CMP Trigger Type 
 *                     - CMP_SW_TRIGGER
 *                     - CMP_HW_TRIGGER
 *
 * @return     none
 *
 */ 
void CMP_Trigger(CMP_Trigger_t type)
{
    if(CMP_SW_TRIGGER == type)
    {
        cmpRegPtr->CMP_CCR0.CMP_EN = 1U;
        cmpRegPtr->CMP_CCR0.SOC_TRG_EN = 0U;
    }
    else
    {
        cmpRegPtr->CMP_CCR0.CMP_EN = 0U;
        cmpRegPtr->CMP_CCR0.SOC_TRG_EN = 1U;
    }    
}

/**
 * @brief      Clear CMP trigger
 *
 * @param[in]  none
 *
 * @return     none
 *
 */ 
void CMP_TriggerClear(void)
{
    cmpRegPtr->CMP_CCR0.CMP_EN = 0U;
    cmpRegPtr->CMP_CCR0.SOC_TRG_EN = 0U;
}

/**
 * @brief      Get CMP output value
 *
 * @param[in]  none
 *
 * @return     CMP Out Voltage Level
 *             0: - low level
 *             1: - high level
 *
 */   
Level_t CMP_GetOutput(void)
{
    return (Level_t)cmpRegPtr->CMP_CSR.COUT;
}

/**
 * @brief      Install callback function
 *
 * @param[in]  intType: select interrrupt type
 * @param[in]  cbFun: indicate callback function
 *
 * @return    none
 *
 */ 
void CMP_InstallCallBackFunc(CMP_Int_t intType, isr_cb_t * cbFun)
{
    if(intType < CMP_INT_ALL)
    {
        cmpIsrCbFunc[intType] = cbFun;
    }
    else
    {
        /* do nothing */
    }
}

/**
 * @brief      Mask/Unmask interrupt
 *
 * @param[in]  intType: select interrrupt type
 *                        - CMP_INT_RAISE
 *                        - CMP_INT_FALL
 *                        - CMP_INT_ALL
 * @param[in]  intMask: 
 *                        - MASK
 *                        - UNMASK
 *
 * @return    none
 *
 */
void CMP_IntMask(CMP_Int_t intType, IntMask_t intMask)
{
    if(UNMASK == intMask)
    {
        cmpRegWPtr->CMP_IER |= cmpInterruptMaskTable[intType];
    }
    else
    {
        cmpRegWPtr->CMP_IER &= ~cmpInterruptMaskTable[intType];
    }
}

/**
 * @brief      Clear interrupt
 *
 * @param[in]  intType: select interrrupt type
 *                        - CMP_INT_RAISE
 *                        - CMP_INT_FALL
 *                        - CMP_INT_ALL
 *
 * @return    none
 *
 */ 
void CMP_IntClear(CMP_Int_t intType)
{
    uint32_t intstatus = cmpRegWPtr->CMP_CSR;
    intstatus |= cmpInterruptMaskTable[intType];
    cmpRegWPtr->CMP_CSR = intstatus;
}

/** @} end of group CMP_Public_Functions */

/** @} end of group CMP_definitions */

/** @} end of group Z20K14XM_Peripheral_Driver */

