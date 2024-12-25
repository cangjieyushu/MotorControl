/**************************************************************************************************/
/**
 * @file     tdg_drv.c
 * @brief    TDG module driver file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 *
 **************************************************************************************************/

#include "tdg_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @defgroup TDG TDG
 *  @brief TDG driver modules
 *  @{
 */

/** @defgroup TDG_Private_Type
 *  @{
 */

/** @} end of group TDG_Private_Type*/

/** @defgroup TDG_Private_Defines
 *  @{
 */

#define    TDG_NUM_ALL     (0x2U)

/** @} end of group TDG_Private_Defines */

/** @defgroup TDG_Private_Variables
 *  @{
 */
/*PRQA S 0303 ++*/
static tdg_reg_t * const tdgRegPtr[TDG_NUM_ALL] = 
{
    (tdg_reg_t *)TDG0_BASE_ADDR, 
    (tdg_reg_t *)TDG1_BASE_ADDR, 
};

static tdg_reg_w_t * const tdgRegWPtr[TDG_NUM_ALL] = 
{
    (tdg_reg_w_t *)TDG0_BASE_ADDR, 
    (tdg_reg_w_t *)TDG1_BASE_ADDR, 
};
/*PRQA S 0303 --*/

static isr_cb_t * tdgIsrCbFunc[TDG_NUM_ALL][TDG_INT_ALL] =
{
    {NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {NULL,NULL,NULL,NULL,NULL,NULL,NULL}
};

static const uint32_t TDG_IntMaskTable[] =
{
   0x00000001U,              /*!< Channel 0 complete delay output interrupt */
   0x00000002U,              /*!< Channel 1 complete delay output interrupt*/
   0x00000004U,              /*!< Channel 2 complete delay output interrupt*/
   0x00000008U,              /*!< Channel 3 complete delay output interrupt*/
   0x00000010U,              /*!< Channel 4 complete delay output interrupt*/
   0x00000020U,              /*!< Channel 5 complete delay output interrupt*/
   0x00000100U,               /*!< Error interrupt */
   0x0000013FU                /*!< TDG_INT_ALL */
};

#define    TDG_DELAY_OUTPUT_INT_FLAG   (0x3FU)

/** @} end of group TDG_Private_Variables */

/** @defgroup TDG_Global_Variables
 *  @{
 */

/** @} end of group TDG_Global_Variables */

/** @defgroup TDG_Private_FunctionDeclaration
 *  @{
 */
static void TDG_TcoIntHandler(TDG_ID_t tdgId);
static void TDG_ErrIntHandler(TDG_ID_t tdgId);
void TDG0_Tco_DriverIRQHandler(void);
void TDG0_Err_DriverIRQHandler(void);
void TDG1_Tco_DriverIRQHandler(void);
void TDG1_Err_DriverIRQHandler(void);

/** @} end of group TDG_Private_FunctionDeclaration */

/** @defgroup TDG_Private_Functions
 *  @{
 */
/**
 * @brief      TDG interrupt handle
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 *
 * @return none
 *
 */
static void TDG_TcoIntHandler(TDG_ID_t tdgId)
{
    uint32_t intStatus;
    uint32_t localCount;

    tdg_reg_w_t * TDGxw = (tdg_reg_w_t *)(tdgRegWPtr[tdgId]);
    
    intStatus = TDGxw->TDG_STAT & TDG_DELAY_OUTPUT_INT_FLAG;
    /* only check enabled interrupts */
    intStatus &= TDGxw->TDG_CTRL2;
    /* clear interrupt status */
    TDGxw->TDG_STAT = intStatus;

    /* Handle Channel 0-5 Interrupt */
    for(localCount = (uint32_t)TDG_INT_CH0; localCount <= (uint32_t)TDG_INT_CH5; localCount++)
    {
        if(0U != (intStatus & TDG_IntMaskTable[localCount]))
        {
            if(tdgIsrCbFunc[tdgId][localCount] != NULL)
            {
                /* call the callback function */
                tdgIsrCbFunc[tdgId][localCount]();
            }
            /* Disable the interrupt if callback function is not setup */
            else
            {
                TDGxw->TDG_CTRL2 &= ~TDG_IntMaskTable[localCount];
            }
        }
    }

    COMMON_DSB();
    
}
/**
 * @brief      TDG error interrupt handle
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 *
 * @return none
 *
 */
static void TDG_ErrIntHandler(TDG_ID_t tdgId)
{
    uint32_t intStatus;
    
    tdg_reg_t * TDGx = (tdg_reg_t *)(tdgRegPtr[tdgId]);
    tdg_reg_w_t * TDGxw = (tdg_reg_w_t *)(tdgRegWPtr[tdgId]);
    
    intStatus = TDGxw->TDG_STAT & TDG_IntMaskTable[TDG_INT_ALL];
    
    /* ERR Interrupt */
    if((intStatus & TDG_IntMaskTable[TDG_INT_ERR]) != 0U)
    {
        TDGxw->TDG_STAT = TDG_IntMaskTable[TDG_INT_ERR];
        if(tdgIsrCbFunc[tdgId][TDG_INT_ERR] != NULL)
        {
            /* call the callback function */
            tdgIsrCbFunc[tdgId][TDG_INT_ERR]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            TDGx->TDG_CTRL2.ERRIE = 0U;
        }
    }
    COMMON_DSB();
}

/**
 * @brief      TDG0 IRQHandler
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void TDG0_Tco_DriverIRQHandler(void)
{
    TDG_TcoIntHandler(TDG0_ID);
}

/**
 * @brief      TDG0 IRQHandler
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void TDG0_Err_DriverIRQHandler(void)
{
    TDG_ErrIntHandler(TDG0_ID);
}
/**
 * @brief      TDG0 IRQHandler
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void TDG1_Tco_DriverIRQHandler(void)
{
    TDG_TcoIntHandler(TDG1_ID);
}

/**
 * @brief      TDG1 IRQHandler
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void TDG1_Err_DriverIRQHandler(void)
{
    TDG_ErrIntHandler(TDG1_ID);
}

/**
 * @brief       TDG ENABLE/DISABLE FUNCTION
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  cmd: ENABLE/DISABLE
 *
 * @return none
 *
 */
void TDG_Enable(TDG_ID_t tdgId, ControlState_t cmd)
{
    tdg_reg_t * TDGx = (tdg_reg_t *)(tdgRegPtr[tdgId]);
 
    TDGx->TDG_CTRL1.TDGEN = (uint32_t)cmd;
}

/**
 * @brief       TDG init config function
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]    config: Init config
 *
 * @return none
 *
 */
void TDG_InitConfig(TDG_ID_t tdgId, const TDG_InitConfig_t * config)
{
    tdg_reg_t * TDGx = (tdg_reg_t *)(tdgRegPtr[tdgId]);
   
    /* modulate value */
    TDGx->TDG_MOD.MOD = config->modVal;

    /* count mode */
    TDGx->TDG_CTRL1.CNTMD = (uint32_t)config->countMode;

    TDGx->TDG_CTRL1.PRES = (uint32_t)config->clkDivide;
    /* trig source */
    TDGx->TDG_CTRL1.TRIGS = (uint32_t)config->trigSource;
    /*  update mode select */
    TDGx->TDG_CTRL1.UPMD = (uint32_t)config->updateMode;
    /* clear counter mode */
    TDGx->TDG_CTRL1.CLRMD = (uint32_t)config->clearMode;
}

/**
 * @brief       TDG config update mode function
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  updateMode:
 *                       -TDG_UPDATE_IMMEDIATELY
 *                       -TDG_UPDATE_MODULATOR
 *                       -TDG_UPDATE_DELAY
 *
 * @return none
 *
 */
void TDG_UpdateModeConfig(TDG_ID_t tdgId, TDG_UpdateMode_t updateMode)
{
    tdg_reg_t * TDGx = (tdg_reg_t *)(tdgRegPtr[tdgId]);
   
    TDGx->TDG_CTRL1.UPMD = (uint32_t)updateMode;
}

/**
 * @brief       TDG select counter clear mode
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  clearMode:
 *                       -TDG_ClEAR_MODULATOR
 *                       -TDG_CLEAR_DELAY
 *
 * @return none
 *
 */
void TDG_ClearCounterMode(TDG_ID_t tdgId, TDG_CountClearMode_t clearMode)
{
    tdg_reg_t * TDGx = (tdg_reg_t *)(tdgRegPtr[tdgId]);
   
    TDGx->TDG_CTRL1.CLRMD = (uint32_t)clearMode;
}

/**
 * @brief       TDG select count mode
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  countMode:
 *                       -TDG_COUNT_SINGLE
 *                       -TDG_COUNT_INFINITY
 *
 * @return none
 *
 */
void TDG_SelectCountMode(TDG_ID_t tdgId, TDG_CountMode_t countMode)
{
    tdg_reg_t * TDGx = (tdg_reg_t *)(tdgRegPtr[tdgId]);
    
    TDGx->TDG_CTRL1.CNTMD = (uint32_t)countMode;
}

/**
 * @brief       TDG select trig source
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  trig:
 *                       -TDG_TRIG_EXTERNAL
 *                       -TDG_TRIG_INFINITY
 *
 * @return none
 *
 */
void TDG_SelectTrigMode(TDG_ID_t tdgId, TDG_TrigSource_t trig)
{
    tdg_reg_t * TDGx = (tdg_reg_t *)(tdgRegPtr[tdgId]);
   
    TDGx ->TDG_CTRL1.TRIGS = (uint32_t)trig;
}

/**
 * @brief      Set this bit to load channel configuration from shadow buffer to 
 *             register
 *
 * @param[in]  tdgId
 *
 * @return ResultStatus_t 
 *                       - SUCC: Load complete 
 *                       - ERR:load fail
 *
 *
 */
ResultStatus_t TDG_LoadCmd(TDG_ID_t tdgId)
{
    tdg_reg_t * TDGx = (tdg_reg_t *)(tdgRegPtr[tdgId]);
    
    ResultStatus_t ret = ERR;
    volatile uint32_t localCnt = 0;
     
    TDGx->TDG_CTRL1.CFGUP = 1U;
    
    while(localCnt < TDG_TIMEOUT_WAIT_CNT)
    {
        if((uint32_t)RESET == TDGx->TDG_CTRL1.CFGUP)
        {
            ret = SUCC;
            break;
        }
        
        localCnt++;
    }        
    
    return ret;
}

/**
 * @brief      TDG software trig
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 *
 * @return none
 *
 */
void TDG_SoftwareTrig(TDG_ID_t tdgId)
{
    tdg_reg_t * TDGx = (tdg_reg_t *)(tdgRegPtr[tdgId]);
  
    TDGx->TDG_CTRL1.SWTRG = 1U;
}

/**
 * @brief      TDG mod value config
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  modValue: Set mod value
 *
 * @return none
 *
 */
void TDG_SetModVal(TDG_ID_t tdgId, uint16_t modValue)
{
    tdg_reg_t * TDGx = (tdg_reg_t *)(tdgRegPtr[tdgId]);
    
    TDGx->TDG_MOD.MOD = modValue;
}

/**
 * @brief      GET TDG mod value
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 *
 * @return mod value
 *
 */
uint16_t TDG_GetModVal(TDG_ID_t tdgId)
{
    tdg_reg_t * TDGx = (tdg_reg_t *)(tdgRegPtr[tdgId]);
   
    return (uint16_t)(TDGx->TDG_MOD.MOD);
}

/**
 * @brief      GET TDG counter value
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 *
 * @return  uint16_t: The counter value
 *
 */
uint16_t TDG_GetCounterVal(TDG_ID_t tdgId)
{
    tdg_reg_t * TDGx = (tdg_reg_t *)(tdgRegPtr[tdgId]);
 
    return (uint16_t)(TDGx->TDG_CNT.CNT);
}

/**
 * @brief      TDG pre-scale the count clock source function
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  divide:
 *                            -TDG_CLK_DIVIDE_1
 *                            -TDG_CLK_DIVIDE_2
 *                            -TDG_CLK_DIVIDE_4
 *                            -TDG_CLK_DIVIDE_8
 *                            -TDG_CLK_DIVIDE_16
 *                            -TDG_CLK_DIVIDE_32
 *                            -TDG_CLK_DIVIDE_64
 *                            -TDG_CLK_DIVIDE_128
 *
 * @return none
 *
 */
void TDG_DivideClk(TDG_ID_t tdgId, TDG_ClkDivide_t divide)
{
    tdg_reg_t * TDGx = (tdg_reg_t *)(tdgRegPtr[tdgId]);
   
    TDGx->TDG_CTRL1.PRES = (uint32_t)divide;
}

/**
 * @brief      TDG channel enable/disable
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  channelId: Select channel
 * @param[in]  cmd:ENABLE/DISABLE
 *
 * @return none
 *
 */
void TDG_ChannelEnable(TDG_ID_t tdgId, TDG_ChannelId_t channelId, 
                                                    ControlState_t cmd)
{
    tdg_reg_t * TDGx = (tdg_reg_t *)(tdgRegPtr[tdgId]);
  
     switch (channelId)
    {
        case TDG_CHANNEL_0:
            TDGx->TDG_CTRL2.CH0E = (uint32_t)cmd;
            break;

        case TDG_CHANNEL_1:
            TDGx->TDG_CTRL2.CH1E = (uint32_t)cmd;
            break;

        case TDG_CHANNEL_2:
            TDGx->TDG_CTRL2.CH2E = (uint32_t)cmd;
            break;

        case TDG_CHANNEL_3:
            TDGx->TDG_CTRL2.CH3E = (uint32_t)cmd;
            break;
        case TDG_CHANNEL_4:
            TDGx->TDG_CTRL2.CH4E = (uint32_t)cmd;
            break;

        case TDG_CHANNEL_5:
            TDGx->TDG_CTRL2.CH5E = (uint32_t)cmd;
            break;

        default:
            /*Do nothing*/
            break;

    }
}

/**
 * @brief       TDG INT mask/unmask Function
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  intType:    Select interrupt type.
 * @param[in]  intMask:  MASK/UNMASK .
 *
 * @return none
 *
 */
void TDG_IntMask(TDG_ID_t tdgId, TDG_INT_t intType, IntMask_t intMask)
{
    tdg_reg_t * TDGx = (tdg_reg_t *)(tdgRegPtr[tdgId]);
   
    ControlState_t cmd = (intMask == UNMASK) ? ENABLE : DISABLE;

    switch (intType)
    {
        case TDG_INT_CH0:
            TDGx->TDG_CTRL2.CDO0IE = (uint32_t)cmd;
            break;

        case TDG_INT_CH1:
            TDGx->TDG_CTRL2.CDO1IE = (uint32_t)cmd;
            break;

        case TDG_INT_CH2:
            TDGx->TDG_CTRL2.CDO2IE = (uint32_t)cmd;
            break;

        case TDG_INT_CH3:
            TDGx->TDG_CTRL2.CDO3IE = (uint32_t)cmd;
            break;

        case TDG_INT_CH4:
            TDGx->TDG_CTRL2.CDO4IE = (uint32_t)cmd;
            break;

        case TDG_INT_CH5:
            TDGx->TDG_CTRL2.CDO5IE = (uint32_t)cmd;
            break;

        case TDG_INT_ERR:
            TDGx->TDG_CTRL2.ERRIE = (uint32_t)cmd;
            break;

        case TDG_INT_ALL:
            TDGx->TDG_CTRL2.CDO0IE = (uint32_t)cmd;
            TDGx->TDG_CTRL2.CDO1IE = (uint32_t)cmd;
            TDGx->TDG_CTRL2.CDO2IE = (uint32_t)cmd;
            TDGx->TDG_CTRL2.CDO3IE = (uint32_t)cmd;
            TDGx->TDG_CTRL2.CDO4IE = (uint32_t)cmd;
            TDGx->TDG_CTRL2.CDO5IE = (uint32_t)cmd;
            TDGx->TDG_CTRL2.ERRIE = (uint32_t)cmd;
            break;

        default:
            /*Do nothing*/
            break;

    }
}

/**
 * @brief       TDG INT status clear Function
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  intType:    Select interrupt type.
 *
 * @return none
 *
 */
void TDG_IntClear(TDG_ID_t tdgId, TDG_INT_t intType)
{
    tdg_reg_w_t * TDGxw = (tdg_reg_w_t *)(tdgRegWPtr[tdgId]);
  
    switch (intType)
    {
        case TDG_INT_CH0:
            TDGxw->TDG_STAT = TDG_IntMaskTable[0];
            break;

        case TDG_INT_CH1:
            TDGxw->TDG_STAT = TDG_IntMaskTable[1];
            break;

        case TDG_INT_CH2:
            TDGxw->TDG_STAT = TDG_IntMaskTable[2];
            break;

        case TDG_INT_CH3:
            TDGxw->TDG_STAT = TDG_IntMaskTable[3];
            break;

        case TDG_INT_CH4:
            TDGxw->TDG_STAT = TDG_IntMaskTable[4];
            break;

        case TDG_INT_CH5:
            TDGxw->TDG_STAT = TDG_IntMaskTable[5];
            break;

        case TDG_INT_ERR:
            TDGxw->TDG_STAT = TDG_IntMaskTable[6];
            break;

        case TDG_INT_ALL:
            TDGxw->TDG_STAT = TDG_IntMaskTable[7];
            break;

        default:
            /*Do nothing*/
            break;

    }
}

/**
 * @brief       TDG Get INT status Function
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  intType:    Select interrupt type.
 *
 * @return intStatus
 *
 */
IntStatus_t TDG_GetIntStatus(TDG_ID_t tdgId, TDG_INT_t intType)
{
    tdg_reg_t * TDGx = (tdg_reg_t *)(tdgRegPtr[tdgId]);
  
    IntStatus_t intStatus = RESET;

    switch (intType)
    {
        case TDG_INT_CH0:
            intStatus = (IntStatus_t)TDGx->TDG_STAT.CDO0IF;
            break;

        case TDG_INT_CH1:
            intStatus = (IntStatus_t)TDGx->TDG_STAT.CDO1IF;
            break;

        case TDG_INT_CH2:
            intStatus = (IntStatus_t)TDGx->TDG_STAT.CDO2IF;
            break;

        case TDG_INT_CH3:
            intStatus = (IntStatus_t)TDGx->TDG_STAT.CDO3IF;
            break;

        case TDG_INT_CH4:
            intStatus = (IntStatus_t)TDGx->TDG_STAT.CDO4IF;
            break;

        case TDG_INT_CH5:
            intStatus = (IntStatus_t)TDGx->TDG_STAT.CDO5IF;
            break;

        case TDG_INT_ERR:
            intStatus = (IntStatus_t)TDGx->TDG_STAT.ERRIF;
            break;

        default:
            /*Do nothing*/
            break;

    }

    return intStatus;
}

/**
 * @brief       TDG channel delay output complete interrupt delay
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  channelId: select channel
 * @param[in]  delayVal: delay output complete interrupt delay
 *
 * @return none
 *
 */
void TDG_SetIntDelayVal(TDG_ID_t tdgId, TDG_ChannelId_t channelId, 
                                                uint16_t delayVal)
{
    tdg_reg_t * TDGx = (tdg_reg_t *)(tdgRegPtr[tdgId]);
   
    TDGx->TDG_CHCFG[channelId].TDG_CHCDOINTDLY.CDOINTDLY = delayVal & 0x03FFUL;

}

/**
 * @brief      Get TDG delay output complete interrupt delay value
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  channelId: select channel 
 *
 * @return    uint16_t: The delay value
 *
 */
uint16_t TDG_GetChannelIntDelayVal(TDG_ID_t tdgId, TDG_ChannelId_t channelId)
{
    tdg_reg_t * TDGx = (tdg_reg_t *)(tdgRegPtr[tdgId]);
  
    return (uint16_t)(TDGx->TDG_CHCFG[channelId].TDG_CHCDOINTDLY.CDOINTDLY & 
                      0x3FFUL);
}

/**
 * @brief       TDG channel delay output enable function
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  channelId: Select channel
 * @param[in]  doConfig: Config delay output 
 *
 * @return none
 *
 */
void TDG_DelayOuputConfig(TDG_ID_t tdgId, TDG_ChannelId_t channelId,
                           const TDG_DelayOutputConfig_t* doConfig)
{
   
    tdg_reg_w_t * TDGxw = (tdg_reg_w_t *)(tdgRegWPtr[tdgId]);

    uint32_t doId = (uint32_t)doConfig->doId;
    
    uint32_t doEnable;
    doEnable = TDGxw->TDG_CHCFG[channelId].TDG_CHCTRL;
    if(ENABLE == doConfig->cmd)
    {
        TDGxw->TDG_CHCFG[channelId].TDG_CHCTRL = doEnable | 
                                (((uint32_t)doConfig->cmd) << (8U+doId));
    }
    else
    {
        TDGxw->TDG_CHCFG[channelId].TDG_CHCTRL  = doEnable & 
                                (~(((uint32_t)1U) << (8U+doId)));
    }
    
    TDGxw->TDG_CHCFG[channelId].TDG_CHDOOFS[doId] = (uint32_t)doConfig->offset;   
}

/**
 * @brief      Get TDG delay output offset value
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  channelId: Select channel id
 * @param[in]  doId: Select delay output id
 *
 * @return    uint16_t: The delay value
 *
 */
uint16_t TDG_GetChannelOffsetVal(TDG_ID_t tdgId, TDG_ChannelId_t channelId, 
                                                    TDG_DelayOutputId_t doId)
{
    uint32_t offsetVal;
    
    uint32_t delOutId = (uint32_t)doId;
    
    tdg_reg_w_t * TDGxw = (tdg_reg_w_t *)(tdgRegWPtr[tdgId]);
    
    offsetVal = (TDGxw->TDG_CHCFG[channelId].TDG_CHDOOFS[delOutId]) & 0xFFFFU;
    
   return (uint16_t)offsetVal;
}

/**
 * @brief       Clear TDG channel delay output function
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  channelId: Select channel
 *
 * @return none
 *
 */
void TDG_ClearChannelDelayOutput(TDG_ID_t tdgId, TDG_ChannelId_t channelId)
{
   
    tdg_reg_w_t * TDGxw = (tdg_reg_w_t *)(tdgRegWPtr[tdgId]);
    
    /* clear TDG Delay Output  Complete Interrupt Delay */
    TDG_SetIntDelayVal(tdgId, channelId, 0U);
    /*clear channel offset */
    for (volatile uint8_t i = 0U; i< 8U; i++)
    {
        TDGxw->TDG_CHCFG[channelId].TDG_CHDOOFS[i] = 0U;
    }
}

/**
 * @brief       TDG channel delay output config function
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  config: Configuration
 * @param[in]  cmd: 
 *                -ENABLE
 *                -DISABLE
 *
 * @return none
 *
 */
void TDG_ChannelDelayOutputConfig(TDG_ID_t tdgId, 
                                  const TDG_ChannelConfig_t* config, 
                                  ControlState_t cmd)
{
    volatile uint8_t i;
    uint16_t delayValue;

    delayValue = config -> intDelayVal;
    TDG_SetIntDelayVal(tdgId, config -> channelId, delayValue);

    for (i=0U; i < config->doNum; i++)
    {
       TDG_DelayOuputConfig(tdgId, config->channelId, &(config->doConfig[i]));
    }

    TDG_ChannelEnable(tdgId, config -> channelId, cmd);
}

/**
 * @brief       TDG get interrupt delay config load complete status Function
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  channelId:    Select channel type.
 *
 * @return IntStatus_t
 *
 */
IntStatus_t TDG_GetDelayStatus(TDG_ID_t tdgId, TDG_ChannelId_t channelId)
{
    tdg_reg_t * TDGx = (tdg_reg_t *)(tdgRegPtr[tdgId]);

    return ((IntStatus_t)TDGx->TDG_CHCFG[channelId].TDG_CHCDOINTDLY.LDCO);
}

/**
 * @brief       TDG get channel number Function
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 *
 * @return   uint8_t: The channel number
 *
 */
uint8_t TDG_GetCHNum(TDG_ID_t tdgId)
{
    tdg_reg_t * TDGx = (tdg_reg_t *)(tdgRegPtr[tdgId]);
 
    return ((uint8_t)TDGx->TDG_PARAM.CHNUM);
}

/**
 * @brief       TDG get delay output point Function
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 *
 * @return     uint8_t: The delay output point.
 *
 */
uint8_t TDG_GetDoNum(TDG_ID_t tdgId)
{
    tdg_reg_t * TDGx = (tdg_reg_t *)(tdgRegPtr[tdgId]);
        
    return ((uint8_t)TDGx->TDG_PARAM.DOPNUM);
}

/**
 * @brief      Install call back function
 *
 * @param[in]  tdgId:  Select the TDG ID: TDG0_ID, TDG1_ID.
 * @param[in]  intType: Select the interrupt
 * @param[in]  cbFun: Pointer to callback function
 *
 * @return     none
 */
void TDG_InstallCallBackFunc(TDG_ID_t tdgId, TDG_INT_t intType, isr_cb_t * cbFun)
{ 
    if(intType < TDG_INT_ALL) {
        tdgIsrCbFunc[tdgId][intType] = cbFun;
    }
    else
    {
        /* Do nothing */
    }
}


/** @} end of group TDG_Public_Functions */

/** @} end of group TDG_definitions */

/** @} end of group Z20K14XM_Peripheral_Driver */
