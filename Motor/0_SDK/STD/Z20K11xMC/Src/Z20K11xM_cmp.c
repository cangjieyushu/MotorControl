/**************************************************************************************************/
/**
 * @file      : Z20K11xM_cmp.c
 * @brief     : CMP module driver file.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (c) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#include "Z20K11xM_cmp.h"


/** @addtogroup  Z20K11X_Peripheral_Driver
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
/** @} end of group CMP_Private_Defines */

/** @defgroup CMP_Private_Variables
 *  @{
 */
static isr_cb_t * cmpIsrCbFunc[CMP_INT_ALL] = {NULL, NULL};

/*PRQA S 0303 ++*/
static cmp_reg_t   *const cmpRegPtr    = (cmp_reg_t *) CMP_BASE_ADDR;        /*!< Analog comparator Register */
static cmp_reg_w_t *const cmpRegWPtr   = (cmp_reg_w_t *) CMP_BASE_ADDR;      /*!< Analog comparator Register */
/*PRQA S 0303 --*/

static const uint32_t CMP_InterruptMaskTable[] =
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

/** @} end of group CMP_Private_FunctionDeclaration */

/** @defgroup CMP_Private_Functions
 *  @{
 */

void CMP_DriverIRQHandler(void);
/** @} end of group CMP_Private_Functions */

/** @defgroup CMP_Public_Functions
 *  @{
 */
/**
 * @brief      Initialize CMP
 *
 * @param[in]  cfg: the configuration parameters.
 *                  if cfg->mode == CMP_MODE_WINDOW or CMP_MODE_WINDOW_FILTER,
 *                  CMP_WindowConfig() need to be called to config window para.
 *                  if cfg->mode == CMP_MODE_FILTER or CMP_MODE_WINDOW_FILTER,
 *                  CMP_FilterConfig() need to be called to config filter para.
 *
 * @return     none
 *
 */
void CMP_Init(const CMP_Config_t * cfg)
{
    cmpRegPtr->CMP_CCR0.CMP_SEL = (uint32_t)(cfg->speed);
    if(CMP_SPEED_LOW == cfg->speed)
    {
        cmpRegPtr->CMP_CCR2.LS_HSTCTR = (uint32_t)(cfg->hyst.ls);
        cmpRegPtr->CMP_CCR2.LS_PSEL = (uint32_t)(cfg->pIn);
        cmpRegPtr->CMP_CCR2.LS_MSEL = (uint32_t)(cfg->nIn);
    }
    else
    {
        cmpRegPtr->CMP_CCR2.HS_HSTCTR = (uint32_t)(cfg->hyst.hs);
        cmpRegPtr->CMP_CCR2.HS_PSEL = (uint32_t)(cfg->pIn);
        cmpRegPtr->CMP_CCR2.HS_MSEL = (uint32_t)(cfg->nIn);
    }
    
    /* config working mode */
    switch(cfg->mode)
    {
        case CMP_MODE_BASIC:
            cmpRegPtr->CMP_CCR1.WINDOW_EN = 0;
            cmpRegPtr->CMP_CCR1.SAMPLE_EN = 0;
            break;
        
        case CMP_MODE_WINDOW:
            cmpRegPtr->CMP_CCR1.WINDOW_EN = 1;
            cmpRegPtr->CMP_CCR1.SAMPLE_EN = 0;
            cmpRegPtr->CMP_CCR1.FILT_CNT = 0;
            cmpRegPtr->CMP_CCR1.FILT_PER = 0;
            break;
        
        case CMP_MODE_FILTER:
            cmpRegPtr->CMP_CCR1.WINDOW_EN = 0;
            cmpRegPtr->CMP_CCR1.SAMPLE_EN = 0;
            break;
        
        case CMP_MODE_SAMPLE:
            cmpRegPtr->CMP_CCR1.WINDOW_EN = 0;
            cmpRegPtr->CMP_CCR1.SAMPLE_EN = 1;
            cmpRegPtr->CMP_CCR1.FILT_CNT = 1;
            cmpRegPtr->CMP_CCR1.FILT_PER = 0;
            break;
        
        case CMP_MODE_WINDOW_FILTER:
            cmpRegPtr->CMP_CCR1.WINDOW_EN = 1;
            cmpRegPtr->CMP_CCR1.SAMPLE_EN = 0;
            break;
            
        default:/*PRQA S 2016*/
            break;
    }
    
    /* default cout after filter */
    cmpRegPtr->CMP_CCR1.COUT_SEL = 0;
    
    cmpRegPtr->CMP_CCR0.STOP_EN = (uint32_t)(cfg->stopReqEn);
    /* select DMA / interrupt request */
    cmpRegPtr->CMP_CCR1.DMA_EN = (uint32_t)(cfg->req);
    /* invert output or not */
    cmpRegPtr->CMP_CCR1.COUT_INV = (uint32_t)(cfg->invertEn);
    /* output to pad or not */
    cmpRegPtr->CMP_CCR1.COUT_PEN = (uint32_t)(cfg->outToPad);  
    
}

/**
 * @brief      select the output 
 *
 * @param[in]  out: select the output
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
 * @param[in]  cnt: the consecutive sample count number that agree the output 
 *                  value to be changed. The range is 1 - 7. If it is 0, the 
 *                  filter is bypassed.
 * @param[in]  period: the sampling period in bus clock of the output filter.
 *                     The range is 1-0xff. If it is 0, filter is bypassed
 *
 * @return     None
 *
 */
void CMP_FilterConfig(uint32_t cnt, uint32_t period)
{
    cmpRegPtr->CMP_CCR1.FILT_PER = period;
    cmpRegPtr->CMP_CCR1.FILT_CNT = cnt;    
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
        cmpRegPtr->CMP_CCR1.COUT_OWE = 0;
    }
    else
    {
        cmpRegPtr->CMP_CCR1.COUT_OWE = 1;
        cmpRegPtr->CMP_CCR1.COUT_OW = ((uint32_t)closedLvl) >> 1;
    }
}

/**
 * @brief      Initialize DAC
 *
 * @param[in]  vref: Select the reference voltage
 *
 * @return     None
 *
 */   
void CMP_DacInit(CMP_DACVref_t vref)
{
    cmpRegPtr->CMP_DCR.VREF_SEL = (uint32_t)vref;
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
    cmpRegPtr->CMP_DCR.DAC_EN = 1;
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
    cmpRegPtr->CMP_DCR.DAC_EN = 0;
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
 * @param[in]  type: select how to trigger the CMP
 *
 * @return     none
 *
 */ 
void CMP_Trigger(CMP_Trigger_t type)
{
    if(CMP_SW_TRIGGER == type)
    {
        cmpRegPtr->CMP_CCR0.CMP_EN = 1;
        cmpRegPtr->CMP_CCR0.SOC_TRG_EN = 0;
    }
    else
    {
        cmpRegPtr->CMP_CCR0.CMP_EN = 0;
        cmpRegPtr->CMP_CCR0.SOC_TRG_EN = 1;
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
    cmpRegPtr->CMP_CCR0.CMP_EN = 0;
    cmpRegPtr->CMP_CCR0.SOC_TRG_EN = 0;
}

/**
 * @brief      Get CMP output value
 *
 * @param[in]  none
 *
 * @return     0  -- low level
 *             1  -- high level
 *
 */   
uint32_t CMP_GetOutput(void)
{
    return cmpRegPtr->CMP_CSR.COUT;
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
    if(intType >= CMP_INT_ALL)
    {
        
    }
    else
    {
        cmpIsrCbFunc[intType] = cbFun;
    }
}

/**
 * @brief      Mask/Unmask interrupt
 *
 * @param[in]  intType: select interrrupt type
 * @param[in]  intMask: MASK/UNMASK
 *
 * @return    none
 *
 */
void CMP_IntMask(CMP_Int_t intType, IntMask_t intMask)
{
    if(UNMASK == intMask)
    {
        cmpRegWPtr->CMP_IER |= CMP_InterruptMaskTable[intType];
    }
    else
    {
        cmpRegWPtr->CMP_IER &= ~CMP_InterruptMaskTable[intType];
    }
}

/**
 * @brief      Clear interrupt
 *
 * @param[in]  intType: select interrrupt type
 *
 * @return    none
 *
 */ 
void CMP_IntClear(CMP_Int_t intType)
{
    uint32_t intstatus = cmpRegWPtr->CMP_CSR;
    intstatus |= CMP_InterruptMaskTable[intType];
    cmpRegWPtr->CMP_CSR = intstatus;
}

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
                cmpRegWPtr->CMP_IER &= ~((uint32_t)0x00000001U << intType); 
            }
        }
    }  
}

/** @} end of group CMP_Public_Functions */

/** @} end of group CMP_definitions */

/** @} end of group Z20K11X_Peripheral_Driver */
