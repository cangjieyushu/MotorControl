/**************************************************************************************************/
/**
 * @file      : Z20K11xM_tim.c
 * @brief     : TIM module driver file.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (c) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#include "Z20K11xM_tim.h"

/** @addtogroup  Z20K11X_Peripheral_Driver
 *  @{
 */

/** @defgroup TIM TIM
 *  @brief TIM driver modules
 *  @{
 */

/** @defgroup TIM_Private_Type
 *  @{
 */

/*@} end of group TIM_Private_Type*/

/** @defgroup TIM_Private_Defines
 *  @{
 */
#define TIM_NUM_ALL             0x3U
#define TIM_CH_INT_MASK         (0x00000020U)
#define TIM_RLDF_INT_MASK       (0x00000100U)
#define TIM_TOF_INT_MASK        (0x00000200U)
#define TIM_FAULT_INT_MASK      (0x00000010U)


/*@} end of group TIM_Private_Defines */

/** @defgroup TIM_Private_Variables
 *  @{
 */
/**
 *  @brief TIM0, TIM1, TIM2, TIM3 address array
 */
/*PRQA S 0303,0306 ++*/
static tim_reg_t *const timRegPtr[TIM_NUM_ALL] = 
{
    (tim_reg_t *)TIM0_BASE_ADDR, 
    (tim_reg_t *)TIM1_BASE_ADDR,
    (tim_reg_t *)TIM2_BASE_ADDR
};
/*PRQA S 0303,0306 --*/

/**
 *  @brief TIM0, TIM1, TIM2, TIM3 address array
 */
/*PRQA S 0303,0306 ++*/
static tim_reg_w_t *const timRegWPtr[TIM_NUM_ALL] = 
{
    (tim_reg_w_t *)TIM0_BASE_ADDR, 
    (tim_reg_w_t *)TIM1_BASE_ADDR,
    (tim_reg_w_t *)TIM2_BASE_ADDR
};
/*PRQA S 0303,0306 --*/

static isr_cb_t * timIsrCbFunc[TIM_NUM_ALL][TIM_INT_ALL] = 
{
    {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
};

/*@} end of group TIM_Private_Variables */

/** @defgroup TIM_Global_Variables
 *  @{
 */

/*@} end of group TIM_Global_Variables */

/** @defgroup TIM_Private_FunctionDeclaration
 *  @{
 */
void TIM0_DriverIRQHandler(void);
void TIM1_DriverIRQHandler(void);
void TIM2_DriverIRQHandler(void);
static void TIM_IntHandler(TIM_ID_t timId);
/*@} end of group TIM_Private_FunctionDeclaration */

/** @defgroup TIM_Private_Functions
 *  @{
 */
/**
 * @brief      TIM interrupt handle
 *
 * @param[in]  timId:  Select the TIM ID
 *
 * @return none
 *
 */
static void TIM_IntHandler(TIM_ID_t timId)
{
    uint32_t timChannel = 0U;
    uint32_t intStatus = 0U;
    uint32_t intFaultStatus = 0U;
    uint32_t timIntStatus = 0U;
    tim_reg_t * TIMx = timRegPtr[timId];
    tim_reg_w_t * TIMw = timRegWPtr[timId];
    /* Check the parameters */

    const uint32_t timIntMaskTable[] = 
    {
        0x00000001U,               /*!< TIM_INT_CH0 */
        0x00000002U,               /*!< TIM_INT_CH1 */
        0x00000004U,               /*!< TIM_INT_CH2 */
        0x00000008U,               /*!< TIM_INT_CH3 */
        0x00000010U,               /*!< TIM_INT_CH4 */
        0x00000020U,               /*!< TIM_INT_CH5 */
        0x00000040U,               /*!< TIM_INT_CH6 */
        0x00000080U,               /*!< TIM_INT_CH7 */
        0x00000100U,               /*!< TIM_INT_RLD */
        0x00000200U,               /*!< TIM_INT_TO */
        0x00000010U,               /*!< TIM_INT_FAULT */
        0x000003FFU                /*!< TIM_INT_ALL except TIM_INT_FAULT*/
    };

    intStatus = TIMw->TIM_GLBSR  & timIntMaskTable[TIM_INT_ALL];
    intFaultStatus = TIMw->TIM_FLTSR  & timIntMaskTable[TIM_INT_FAULT];
    
    for (timChannel = 0U; timChannel <= 7U; timChannel++)
    {
        if ((0U != (intStatus & ((uint32_t)1U << timChannel))) && (1U == TIMx->TIM_CMCn[timChannel].CHIE))
        {
            /* get interrupt status */
            timIntStatus = TIMw->TIM_CMCn[timChannel];
            /* only check enabled interrupts */
            timIntStatus = timIntStatus & (~(TIM_CH_INT_MASK));
            /* clear interrupt status */
            TIMw->TIM_CMCn[timChannel] = timIntStatus;
            if(timIsrCbFunc[timId][timChannel] != NULL)
            {
                /* call the callback function */
                timIsrCbFunc[timId][timChannel]();
            }
            /* Disable the interrupt if callback function is not setup */
            else
            {
                TIMx->TIM_CMCn[timChannel].CHIE = 0U;
            }
        }
    }

    /* Reload Interrupt */
    if(((intStatus & timIntMaskTable[TIM_INT_RLD]) != 0U) && (1U == TIMx->TIM_GLBCR.RLDIE))
    {
        /* get interrupt status */
        timIntStatus = TIMw->TIM_GLBSR;
        /* only check enabled interrupts */
        timIntStatus = timIntStatus & (~(TIM_RLDF_INT_MASK));
        /* clear interrupt status */
        TIMw->TIM_GLBSR = timIntStatus;
        if(timIsrCbFunc[timId][TIM_INT_RLD] != NULL)
        {
            /* call the callback function */
            timIsrCbFunc[timId][TIM_INT_RLD]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            TIMx->TIM_GLBCR.RLDIE = 0U;
        }
    }
    
    /* Timer overlop Interrupt */
    if(((intStatus & timIntMaskTable[TIM_INT_TO]) != 0U) && (1U == TIMx->TIM_GLBCR.TOIE))
    {
        /* get interrupt status */
        timIntStatus = TIMw->TIM_GLBSR;
        /* only check enabled interrupts */
        timIntStatus = timIntStatus & (~(TIM_TOF_INT_MASK));
        /* clear interrupt status */
        TIMw->TIM_GLBSR = timIntStatus;
        if(timIsrCbFunc[timId][TIM_INT_TO] != NULL)
        {
            /* call the callback function */
            timIsrCbFunc[timId][TIM_INT_TO]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            TIMx->TIM_GLBCR.TOIE = 0U;
        }
    }
    
    /* Fault Control Interrupt */
    if(((intFaultStatus & timIntMaskTable[TIM_INT_FAULT]) != 0U) && (1U == TIMx->TIM_FLTCR.FLTIE))
    {
        /* get interrupt status */
        timIntStatus = TIMw->TIM_FLTSR;
        /* only check enabled interrupts */
        timIntStatus = timIntStatus & (~(TIM_FAULT_INT_MASK));
        /* clear interrupt status */
        TIMw->TIM_FLTSR = timIntStatus;
        if(timIsrCbFunc[timId][TIM_INT_FAULT] != NULL)
        {
            /* call the callback function */
            timIsrCbFunc[timId][TIM_INT_FAULT]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            TIMx->TIM_FLTCR.FLTIE = 0U;
        }
    }

}

/**
 * @brief      TIM0 IRQHandler
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void TIM0_DriverIRQHandler(void)
{
    TIM_IntHandler(TIM0_ID);
}

/**
 * @brief      TIM1 IRQHandler
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void TIM1_DriverIRQHandler(void)
{
    TIM_IntHandler(TIM1_ID);
}

/**
 * @brief      TIM2 IRQHandler
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void TIM2_DriverIRQHandler(void)
{
    TIM_IntHandler(TIM2_ID);
}


/**
 * @brief       TIM Set Combine enable/disable Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  pairId:       Select paired id .
 * @param[in]  cmd:          enable/disable.
 *
 * @return none
 *
 */
static inline void TIM_SetCombineCmd(TIM_ID_t timId, TIM_PairId_t pairId, ControlState_t cmd)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    switch (pairId)
    {
        case TIM_PAIR_CHANNEL_0:
            TIMx->TIM_PCR.COMB0 = (uint32_t)cmd;
            break;
            
        case TIM_PAIR_CHANNEL_1:
            TIMx->TIM_PCR.COMB1 = (uint32_t)cmd;
            break;
            
        case TIM_PAIR_CHANNEL_2:
            TIMx->TIM_PCR.COMB2 = (uint32_t)cmd;
            break;
            
        case TIM_PAIR_CHANNEL_3:
            TIMx->TIM_PCR.COMB3 = (uint32_t)cmd;
            break;
            
        default:
            /* do nothing */
            break;
      
    }
}

/**
 * @brief       TIM Set deadtime function enable/disable Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  pairId:       Select paired id .
 * @param[in]  cmd:          enable/disable.
 *
 * @return none
 *
 */
static inline void TIM_SetDeadTimeCmd(TIM_ID_t timId, TIM_PairId_t pairId, ControlState_t cmd)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    switch (pairId)
    {
        case TIM_PAIR_CHANNEL_0:
            TIMx->TIM_PCR.DTEN0 = (uint32_t)cmd;
            break;
            
        case TIM_PAIR_CHANNEL_1:
            TIMx->TIM_PCR.DTEN1 = (uint32_t)cmd;
            break;
            
        case TIM_PAIR_CHANNEL_2:
            TIMx->TIM_PCR.DTEN2 = (uint32_t)cmd;
            break;
            
        case TIM_PAIR_CHANNEL_3:
            TIMx->TIM_PCR.DTEN3 = (uint32_t)cmd;
            break;
            
        default:
            /* do nothing */
            break;
      
    }
}

/**
 * @brief       TIM Set fault control enable/disable Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  pairId:       Select paired id .
 * @param[in]  cmd:          enable/disable.
 *
 * @return none
 *
 */
static inline void TIM_SetFaultCtrlCmd(TIM_ID_t timId, TIM_PairId_t pairId, ControlState_t cmd)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    switch (pairId)
    {
        case TIM_PAIR_CHANNEL_0:
            TIMx->TIM_PCR.FCTLEN0 = (uint32_t)cmd;
            break;
            
        case TIM_PAIR_CHANNEL_1:
            TIMx->TIM_PCR.FCTLEN1 = (uint32_t)cmd;
            break;
            
        case TIM_PAIR_CHANNEL_2:
            TIMx->TIM_PCR.FCTLEN2 = (uint32_t)cmd;
            break;
            
        case TIM_PAIR_CHANNEL_3:
            TIMx->TIM_PCR.FCTLEN3 = (uint32_t)cmd;
            break;
            
        default:
            /* do nothing */
            break;
      
    }
}

/**
 * @brief       TIM Set Sync CCV register enable/disable Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  pairId:       Select paired id .
 * @param[in]  cmd:          enable/disable.
 *
 * @return none
 *
 */
static inline void TIM_SetSyncPairCCVCmd(TIM_ID_t timId, TIM_PairId_t pairId, ControlState_t cmd)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    switch (pairId)
    {
        case TIM_PAIR_CHANNEL_0:
            TIMx->TIM_PCR.SYNCEN0 = (uint32_t)cmd;
            break;
            
        case TIM_PAIR_CHANNEL_1:
            TIMx->TIM_PCR.SYNCEN1 = (uint32_t)cmd;
            break;
            
        case TIM_PAIR_CHANNEL_2:
            TIMx->TIM_PCR.SYNCEN2 = (uint32_t)cmd;
            break;
            
        case TIM_PAIR_CHANNEL_3:
            TIMx->TIM_PCR.SYNCEN3 = (uint32_t)cmd;
            break;
            
        default:
            /* do nothing */
            break;
      
    }
}

/**
 * @brief       TIM Set dual edge capture function enable/disable Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  pairId:       Select paired id .
 * @param[in]  cmd:          enable/disable.
 *
 * @return none
 *
 */
static inline void TIM_SetDualEdgeCaptureCmd(TIM_ID_t timId, TIM_PairId_t pairId,
                                             ControlState_t cmd)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    switch (pairId)
    {
        case TIM_PAIR_CHANNEL_0:
            TIMx->TIM_PCR.DECAPEN0 = (uint32_t)cmd;
            break;
            
        case TIM_PAIR_CHANNEL_1:
            TIMx->TIM_PCR.DECAPEN1 = (uint32_t)cmd;
            break;
            
        case TIM_PAIR_CHANNEL_2:
            TIMx->TIM_PCR.DECAPEN2 = (uint32_t)cmd;
            break;
            
        case TIM_PAIR_CHANNEL_3:
            TIMx->TIM_PCR.DECAPEN3 = (uint32_t)cmd;
            break;
            
        default:
            /* do nothing */
            break;
      
    }
}

/**
 * @brief       TIM Set dual edge decap enable/disable Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  pairId:       Select paired id .
 * @param[in]  cmd:          enable/disable.
 *
 * @return none
 *
 */
static inline void TIM_SetDualEdgeDecapCmd(TIM_ID_t timId, TIM_PairId_t pairId,
                                           ControlState_t cmd)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    switch (pairId)
    {
        case TIM_PAIR_CHANNEL_0:
            TIMx->TIM_PCR.DECAP0 = (uint32_t)cmd;
            break;
            
        case TIM_PAIR_CHANNEL_1:
            TIMx->TIM_PCR.DECAP1 = (uint32_t)cmd;
            break;
            
        case TIM_PAIR_CHANNEL_2:
            TIMx->TIM_PCR.DECAP2 = (uint32_t)cmd;
            break;
            
        case TIM_PAIR_CHANNEL_3:
            TIMx->TIM_PCR.DECAP3 = (uint32_t)cmd;
            break;
            
        default:
            /* do nothing */
            break;
      
    }
}

/**
 * @brief       TIM Set input filter Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  channelId:    Select channel id .
 * @param[in]  filter:       filter value.
 *
 * @return none
 *
 */
static inline void TIM_SetInputFilter(TIM_ID_t timId, TIM_ChannelId_t channelId,
                                      TIM_Filter_t filter)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    switch (channelId)
    {
        case TIM_CHANNEL_0:
            TIMx->TIM_FILTER.FILVAL0 = (uint32_t)filter;
            break;
            
        case TIM_CHANNEL_1:
            TIMx->TIM_FILTER.FILVAL1 = (uint32_t)filter;
            break;
            
        case TIM_CHANNEL_2:
            TIMx->TIM_FILTER.FILVAL2 = (uint32_t)filter;
            break;
            
        case TIM_CHANNEL_3:
            TIMx->TIM_FILTER.FILVAL3 = (uint32_t)filter;
            break;
            
        default:
            /* do nothing */
            break;
      
    }
}

/**
 * @brief       TIM Set output polarity Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  channelId:    Select channel id .
 * @param[in]  polarity:     polarity value.
 *
 * @return none
 *
 */
static inline void TIM_SetOutputPolarity(TIM_ID_t timId, TIM_ChannelId_t channelId,
                                      TIM_Polarity_t polarity)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    switch (channelId)
    {
        case TIM_CHANNEL_0:
            TIMx->TIM_OUTCR.POL0 = (uint32_t)polarity;
            break;
            
        case TIM_CHANNEL_1:
            TIMx->TIM_OUTCR.POL1 = (uint32_t)polarity;
            break;
            
        case TIM_CHANNEL_2:
            TIMx->TIM_OUTCR.POL2 = (uint32_t)polarity;
            break;
            
        case TIM_CHANNEL_3:
            TIMx->TIM_OUTCR.POL3 = (uint32_t)polarity;
            break;
        case TIM_CHANNEL_4:
            TIMx->TIM_OUTCR.POL4 = (uint32_t)polarity;
            break;
            
        case TIM_CHANNEL_5:
            TIMx->TIM_OUTCR.POL5 = (uint32_t)polarity;
            break;
            
        case TIM_CHANNEL_6:
            TIMx->TIM_OUTCR.POL6 = (uint32_t)polarity;
            break;
            
        case TIM_CHANNEL_7:
            TIMx->TIM_OUTCR.POL7 = (uint32_t)polarity;
            break;
            
        default:
            /* do nothing */
            break;
      
    }
}

/**
 * @brief       TIM Set output init value Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  channelId:    Select channel id .
 * @param[in]  val:     level value.
 *
 * @return none
 *
 */
static inline void TIM_SetOutputInitValue(TIM_ID_t timId, TIM_ChannelId_t channelId,
                                          Level_t val)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    switch (channelId)
    {
        case TIM_CHANNEL_0:
            TIMx->TIM_OUTCR.INIT0 = (uint32_t)val;
            break;
            
        case TIM_CHANNEL_1:
            TIMx->TIM_OUTCR.INIT1 = (uint32_t)val;
            break;
            
        case TIM_CHANNEL_2:
            TIMx->TIM_OUTCR.INIT2 = (uint32_t)val;
            break;
            
        case TIM_CHANNEL_3:
            TIMx->TIM_OUTCR.INIT3 = (uint32_t)val;
            break;
        case TIM_CHANNEL_4:
            TIMx->TIM_OUTCR.INIT4 = (uint32_t)val;
            break;
            
        case TIM_CHANNEL_5:
            TIMx->TIM_OUTCR.INIT5 = (uint32_t)val;
            break;
            
        case TIM_CHANNEL_6:
            TIMx->TIM_OUTCR.INIT6 = (uint32_t)val;
            break;
            
        case TIM_CHANNEL_7:
            TIMx->TIM_OUTCR.INIT7 = (uint32_t)val;
            break;
            
        default:
            /* do nothing */
            break;
      
    }
}

/*@} end of group TIM_Private_Functions */


/** @defgroup TIM_Public_Functions
 *  @{
 */

/**
 * @brief       TIM WriteProtection Enable Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 *
 * @return none
 *
 */
void TIM_WriteProtectionEnable(TIM_ID_t timId)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    TIMx->TIM_FLTSR.WPEN = (uint32_t)1UL;
}

/**
 * @brief       TIM WriteProtection Disable Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 *
 * @return none
 *
 */
void TIM_WriteProtectionDisable(TIM_ID_t timId)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    TIMx->TIM_GLBSR.WPDIS = (uint32_t)1UL;
}

/**
 * @brief       Init TIMER Counter with initial value and max value
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  initialVal:   Counter init value.
 * @param[in]  maxVal:       Counter max value, also named mod value.
 *
 * @return none
 *
 */
void TIM_InitCounter(TIM_ID_t timId, uint16_t initialVal, uint16_t maxVal)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    TIMx->TIM_CNTINIT.CNTINIT = initialVal;
    
    TIMx->TIM_MOD.MOD = maxVal;
}

/**
 * @brief       TIM Start counter with clock configuration
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  clkSource:    Select TIM clock source:
 *                                  - TIM_CLK_SOURCE_SYSTEM
 *                                  - TIM_CLK_SOURCE_FUNCTION               
 *                                  - TIM_CLK_SOURCE_EXTERNAL
 * @param[in]  divider:      Select TIM clock divider.
 *                                  - 000b: Divide by 1
 *                                  - 001b: Divide by 2
 *                                  - 010b: Divide by 4
 *                                  - 011b: Divide by 8
 *                                  - 100b: Divide by 16
 *                                  - 101b: Divide by 32
 *                                  - 110b: Divide by 64
 *                                  - 111b: Divide by 128
 *
 * @return none
 *
 */
void TIM_StartCounter(TIM_ID_t timId, TIM_ClkSource_t clkSource, 
                     TIM_ClkDivide_t divider)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    TIMx->TIM_TIMEBASE.CKSRC = (uint32_t)clkSource;
    TIMx->TIM_TIMEBASE.PSDIV = (uint32_t)divider;
}

/**
 * @brief       TIM exernal clock source configuration
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  clkSource:    Select TIM external clock source
 *
 * @return none
 *
 */
void TIM_ExternalCounterSelect(TIM_ID_t timId, TIM_ExternalSource_t clkSource)
{
    /*PRQA S 0303,0306 ++*/
    scm_reg_t *const SCMx = (scm_reg_t *)SCM_BASE_ADDR;
    /*PRQA S 0303,0306 --*/

    if(TIM0_ID == timId )
    {
        SCMx->SCM_TIMOPT.TIM0_CLK_SEL = (uint32_t)clkSource;
    }
    else if(TIM1_ID == timId )
    {
        SCMx->SCM_TIMOPT.TIM1_CLK_SEL = (uint32_t)clkSource;
    }
    else
    {
        SCMx->SCM_TIMOPT.TIM2_CLK_SEL = (uint32_t)clkSource;
    }
    
}

/**
 * @brief       TIM Stop counter
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 *
 * @return none
 *
 */
void TIM_StopCounter(TIM_ID_t timId)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    TIMx->TIM_TIMEBASE.CKSRC = (uint32_t)0UL;
}

/**
 * @brief       TIM Set Counter Init Value Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  initialVal:   Counter init value.
 *
 * @return none
 *
 */

void TIM_SetCounterInitialVal(TIM_ID_t timId, uint16_t initialVal)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    TIMx->TIM_CNTINIT.CNTINIT = initialVal;
}

/**
 * @brief       TIM Load Counter Init Value Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 *
 * @return none
 *
 */
void TIM_LoadCounterInitialVal(TIM_ID_t timId)
{
    tim_reg_t * TIMx = timRegPtr[timId];

    TIMx->TIM_CNT.CNT = (uint16_t)0x0U;
}

/**
 * @brief       TIM Get Counter Init Value Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 *
 * @return Counter Init Value
 *
 */
uint16_t TIM_GetCounterInitialVal(TIM_ID_t timId)
{
    tim_reg_t const volatile* TIMx = timRegPtr[timId];
    
    return (uint16_t)TIMx->TIM_CNTINIT.CNTINIT;
}

/**
 * @brief       TIM Set Counter Mod Value Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  modVal:   Counter MOD value.
 *
 * @return none
 *
 */
void TIM_SetCounterModVal(TIM_ID_t timId, uint16_t modVal)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    TIMx->TIM_MOD.MOD = modVal;
}

/**
 * @brief       TIM Get Counter MOD Value Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 *
 * @return Counter MOD Value
 *
 */
uint16_t TIM_GetCounterModVal(TIM_ID_t timId)
{
    tim_reg_t const volatile* TIMx = timRegPtr[timId];
    
    return (uint16_t)TIMx->TIM_MOD.MOD;
}

/**
 * @brief       TIM Set  Capture and Compare Value Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  channelId:Selcct channel ID.
 * @param[in]  ccVal:    Capture and Compare Value.
 *
 * @return none
 *
 */
void TIM_SetCCVal(TIM_ID_t timId, TIM_ChannelId_t channelId, uint16_t ccVal)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    TIMx->TIM_CCVn[channelId].CCV = ccVal;
}

/**
 * @brief       TIM Get Capture and Compare Value Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  channelId:    Selcct channel ID.
 *
 * @return Capture and Compare Value
 *
 */
uint16_t TIM_GetCCVal(TIM_ID_t timId, TIM_ChannelId_t channelId)
{
    tim_reg_t const volatile* TIMx = timRegPtr[timId];
    
    return (uint16_t)TIMx->TIM_CCVn[channelId].CCV;
}

/**
 * @brief       TIM Set  Half Cycle Value Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  hcVal:   Half Cycle value.
 *
 * @return none
 *
 */
void TIM_SetHCVal(TIM_ID_t timId, uint16_t hcVal)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    TIMx->TIM_HCV.HCV = hcVal;
}

/**
 * @brief       TIM Get Half Cycle Value Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 *
 * @return Half Cycle Value
 *
 */
uint16_t TIM_GetHCVal(TIM_ID_t timId)
{
    tim_reg_t const volatile* TIMx = timRegPtr[timId];
    
    return (uint16_t)TIMx->TIM_HCV.HCV;
}

/**
 * @brief       TIM Set  Output Software Control Register Function
 *
 * @param[in]  timId:     Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  swCtrlCmd: Output Software Control Cmd.
 *
 * @return none
 *
 */
void TIM_SetOutputSwControl(TIM_ID_t timId, uint8_t swCtrlCmd)
{
    tim_reg_w_t * TIMw = timRegWPtr[timId];
    uint32_t regVal = TIMw->TIM_OUTSWCR ;
    
    regVal |= (uint32_t)swCtrlCmd;
    TIMw->TIM_OUTSWCR = regVal;
}

/**
 * @brief       TIM Set  Output Software Control Value Register Function
 *
 * @param[in]  timId:     Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  swCtrlVal: Output Software Control value.
 *
 * @return none
 *
 */
void TIM_SetOutputSwCtrlVal(TIM_ID_t timId, uint8_t swCtrlVal)
{
    tim_reg_w_t * TIMw = timRegWPtr[timId];
    uint32_t regVal = TIMw->TIM_OUTSWCR;
    
    regVal |= ((uint32_t)swCtrlVal << 8);
    TIMw->TIM_OUTSWCR = regVal;
}

/**
 * @brief       TIM Get Output Software Control Register Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 *
 * @return     Output Software Control Cmd.
 *
 */
uint8_t TIM_GetOutputSwControl(TIM_ID_t timId)
{
    tim_reg_w_t const volatile* TIMw = timRegWPtr[timId];
    
    return (uint8_t) (TIMw->TIM_OUTSWCR & 0x000000FFUL);
}

/**
 * @brief       TIM Get Output Software Control Register Value Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 *
 * @return     Output Software Control Cmd.
 *
 */
uint8_t TIM_GetOutputSwCtrlVal(TIM_ID_t timId)
{
    tim_reg_w_t const volatile* TIMw = timRegWPtr[timId];
    
    return (uint8_t) ((TIMw->TIM_OUTSWCR & 0x0000FF00UL) >> 8);
}

/**
 * @brief       TIM output software control config Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  channelId:Select Channel Id.
 * @param[in]  config:   Pointer to software control config.
 *
 * @return none
 *
 */
void TIM_OutputSWCtrlConfig(TIM_ID_t timId, TIM_ChannelId_t channelId, 
                            const TIM_OutputSWCtrlConfig_t* config)
{
    tim_reg_w_t * TIMw = timRegWPtr[timId];
    
    volatile uint16_t regValue = 0U;
    uint16_t regLow = ((uint16_t)0x1U) << (uint16_t)channelId ;
    uint16_t regHigh= ((uint16_t)0x1U) << ((uint16_t)channelId + (uint16_t)8U);
    uint8_t pairId = (uint8_t)channelId >> 1U;
    
    TIM_SetDualEdgeCaptureCmd(timId, (TIM_PairId_t)pairId, DISABLE);
    
    regValue = (uint16_t)TIMw->TIM_OUTSWCR;
    
    if((ENABLE == config->outputSWCtrlEnable) && (HIGH_LEVEL == config ->outputSWCtrlVal))
    {
        regValue = regLow | regHigh | regValue;
    }
    else if((DISABLE == config->outputSWCtrlEnable) && (HIGH_LEVEL == config ->outputSWCtrlVal))
    {        
        regValue =  regHigh | regValue;
        regValue &= ~regLow;
    }
    
    else if((ENABLE == config->outputSWCtrlEnable) && (LOW_LEVEL == config ->outputSWCtrlVal))
    {
        regValue = regLow  | regValue;
        regValue &= ~regHigh;
    }
    else
    {       
        regValue &= ~(regLow | regHigh) ;
    }
    
    TIMw->TIM_OUTSWCR = regValue;
}

/**
 * @brief       TIM 16-bit Counter Counting Mode Config Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  cntMode: Counting Mode Param.
 *                      - TIM_COUNTING_UP
 *                      - TIM_COUNTING_UP_DOWN
 *
 * @return none
 *
 */
void TIM_CountingModeConfig(TIM_ID_t timId, TIM_CountingMode_t cntMode)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    TIMx->TIM_GLBCR.CNTMODE = (uint32_t)cntMode;
}

/**
 * @brief       TIM Initialize the channels output Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 *
 * @return none
 *
 */
void TIM_InitChannelsOutput(TIM_ID_t timId)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    TIMx->TIM_GLBCR.INIT = 1;
}

/**
 * @brief       TIM initialise input capture mode config Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  config:   Pointer to input capture config.
 *
 * @return none
 *
 */
void TIM_InputCaptureInit(TIM_ID_t timId, const TIM_InputCaptureConfig_t * config)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    uint8_t i;
    TIM_ChannelId_t channelId;
    uint8_t pairId;
    
    TIMx->TIM_GLBCR.CNTMODE = 0;
    
    TIMx->TIM_MOD.MOD = config->maxCounterVal;
    
    for(i = 0; i < config->numChannels; i++)
    {
        channelId = config->inputChConfig[i].channelId;
        pairId = (uint8_t)channelId >> 1U;
        
        TIM_SetCombineCmd(timId, (TIM_PairId_t)pairId, DISABLE);
        TIM_SetDualEdgeCaptureCmd(timId, (TIM_PairId_t)pairId, DISABLE);
        TIMx->TIM_CMCn[channelId].CMS = 0U;
        TIMx->TIM_CMCn[channelId].ELS = (uint32_t)config->inputChConfig[i].edgeConfig;
        TIMx->TIM_CMCn[channelId].ICRST = (uint32_t)config->inputChConfig[i].resetEnable;
        if(channelId < TIM_CHANNEL_4)
        {
            TIM_SetInputFilter(timId, channelId, config->inputChConfig[i].filter);
        }
    }
}

/**
 * @brief       TIM initialise dual edge capture mode config Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  config:   Pointer to dual edge capture config.
 *
 * @return none
 *
 */
void TIM_DualEdgeCaptureInit(TIM_ID_t timId, const TIM_DualEdgeCaptureConfig_t * config)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    uint32_t i;
    uint8_t mainChannelId;
    uint8_t secondChannelId;
    TIM_PairId_t pairId;
    
    TIMx->TIM_GLBCR.CNTMODE = 0;
    TIMx->TIM_MOD.MOD = config->maxCounterVal;
    
    for(i = 0; i < config->numPairs; i++)
    {
        pairId = config->config[i].pairId;
        mainChannelId = (uint8_t)pairId << 1U;
        secondChannelId = mainChannelId + 1U;
        
        TIM_SetCombineCmd(timId, pairId, DISABLE);
        TIM_SetDualEdgeCaptureCmd(timId, pairId, ENABLE);
        TIM_SetDualEdgeDecapCmd(timId, pairId, ENABLE);
        TIM_SetCombineCmd(timId, pairId, DISABLE);
        TIMx->TIM_CMCn[mainChannelId].CMS = (uint32_t)config->config[i].captureMode;

        TIMx->TIM_CMCn[mainChannelId].ELS = (uint32_t)config->config[i].mainEdgeConfig;
        TIMx->TIM_CMCn[secondChannelId].ELS = (uint32_t)config->config[i].secondEdgeConfig;
        
        if(mainChannelId < (uint8_t)TIM_CHANNEL_4)
        {
            TIM_SetInputFilter(timId, (TIM_ChannelId_t)mainChannelId, config->config[i].filter);
        }  
    }
}

/**
 * @brief       TIM initialise output compare mode config Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  config:   Pointer to output compare config.
 *
 * @return none
 *
 */
void TIM_OutputCompareInit(TIM_ID_t timId, const TIM_OutputCompareConfig_t * config)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    uint8_t i;
    TIM_ChannelId_t channelId;
    uint8_t pairId;
    
    
    TIMx->TIM_GLBCR.CNTMODE = (uint32_t)0UL;
    TIMx->TIM_MOD.MOD = config->maxCounterVal;
    TIMx->TIM_OUTCR.INITRIGE = (uint32_t)config->initTriggerEnable;
    
    for(i = 0; i < config->numChannels; i++)
    {
        channelId = config->outputConfig[i].channelId;
        pairId = (uint8_t)channelId >> 1;
        
        TIM_SetCombineCmd(timId, (TIM_PairId_t)pairId, DISABLE);
        TIM_SetDualEdgeCaptureCmd(timId, (TIM_PairId_t)pairId, DISABLE);
        TIMx->TIM_CMCn[channelId].CMS = 1;
        TIMx->TIM_CMCn[channelId].ELS = (uint32_t)config->outputConfig[i].outputMode;
        TIM_SetOutputPolarity(timId, channelId, config->outputConfig[i].polarity);
        TIM_SetOutputInitValue(timId, channelId, config->outputConfig[i].initValue);
        TIMx->TIM_CCVn[channelId].CCV = config->outputConfig[i].compareValue;
        TIM_SetFaultCtrlCmd(timId, (TIM_PairId_t)pairId, config->faultCtrlChannelEnable);
    }    
}

/**
 * @brief       TIM enable channel output Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  channelId:Select Channel Id.
 *
 * @return none
 *
 */
void TIM_ChannelOutputEnable(TIM_ID_t timId, TIM_ChannelId_t channelId)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    switch (channelId)
    {
        case TIM_CHANNEL_0:
            TIMx->TIM_GLBCR.CHOE0 = (uint32_t)ENABLE;
            break;
            
        case TIM_CHANNEL_1:
            TIMx->TIM_GLBCR.CHOE1 = (uint32_t)ENABLE;
            break;
            
        case TIM_CHANNEL_2:
            TIMx->TIM_GLBCR.CHOE2 = (uint32_t)ENABLE;
            break;
            
        case TIM_CHANNEL_3:
            TIMx->TIM_GLBCR.CHOE3 = (uint32_t)ENABLE;
            break;
        case TIM_CHANNEL_4:
            TIMx->TIM_GLBCR.CHOE4 = (uint32_t)ENABLE;
            break;
            
        case TIM_CHANNEL_5:
            TIMx->TIM_GLBCR.CHOE5 = (uint32_t)ENABLE;
            break;
            
        case TIM_CHANNEL_6:
            TIMx->TIM_GLBCR.CHOE6 = (uint32_t)ENABLE;
            break;
            
        case TIM_CHANNEL_7:
            TIMx->TIM_GLBCR.CHOE7 = (uint32_t)ENABLE;
            break;
            
        default:
            /* do nothing */
            break;
      
    }
}

/**
 * @brief       TIM disable channel output Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  channelId:Select Channel Id.
 *
 * @return none
 *
 */
void TIM_ChannelOutputDisable(TIM_ID_t timId, TIM_ChannelId_t channelId)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    switch (channelId)
    {
        case TIM_CHANNEL_0:
            TIMx->TIM_GLBCR.CHOE0 = (uint32_t)DISABLE;
            break;
            
        case TIM_CHANNEL_1:
            TIMx->TIM_GLBCR.CHOE1 = (uint32_t)DISABLE;
            break;
            
        case TIM_CHANNEL_2:
            TIMx->TIM_GLBCR.CHOE2 = (uint32_t)DISABLE;
            break;
            
        case TIM_CHANNEL_3:
            TIMx->TIM_GLBCR.CHOE3 = (uint32_t)DISABLE;
            break;
        case TIM_CHANNEL_4:
            TIMx->TIM_GLBCR.CHOE4 = (uint32_t)DISABLE;
            break;
            
        case TIM_CHANNEL_5:
            TIMx->TIM_GLBCR.CHOE5 = (uint32_t)DISABLE;
            break;
            
        case TIM_CHANNEL_6:
            TIMx->TIM_GLBCR.CHOE6 = (uint32_t)DISABLE;
            break;
            
        case TIM_CHANNEL_7:
            TIMx->TIM_GLBCR.CHOE7 = (uint32_t)DISABLE;
            break;
            
        default:
            /* do nothing */
            break;
      
    }
}

/**
 * @brief       TIM Set match trigger cmd enable/disable Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  channelId:    Select channel id .
 * @param[in]  cmd:     enable/disable.
 *
 * @return none
 *
 */
void TIM_ChannelMatchTriggerCmd(TIM_ID_t timId, TIM_ChannelId_t channelId, 
                                ControlState_t cmd)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    switch (channelId)
    {
        case TIM_CHANNEL_0:
            TIMx->TIM_OUTCR.TRIGE0 = (uint32_t)cmd;
            break;
            
        case TIM_CHANNEL_1:
            TIMx->TIM_OUTCR.TRIGE1 = (uint32_t)cmd;
            break;
            
        case TIM_CHANNEL_2:
            TIMx->TIM_OUTCR.TRIGE2 = (uint32_t)cmd;
            break;
            
        case TIM_CHANNEL_3:
            TIMx->TIM_OUTCR.TRIGE3 = (uint32_t)cmd;
            break;
        case TIM_CHANNEL_4:
            TIMx->TIM_OUTCR.TRIGE4 = (uint32_t)cmd;
            break;
            
        case TIM_CHANNEL_5:
            TIMx->TIM_OUTCR.TRIGE5 = (uint32_t)cmd;
            break;
            
        case TIM_CHANNEL_6:
            TIMx->TIM_OUTCR.TRIGE6 = (uint32_t)cmd;
            break;
            
        case TIM_CHANNEL_7:
            TIMx->TIM_OUTCR.TRIGE7 = (uint32_t)cmd;
            break;
            
        default:
            /* do nothing */
            break;
      
    }
}

/**
 * @brief       TIM Set init trigger cmd enable/disable Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  cmd:     enable/disable.
 *
 * @return none
 *
 */
void TIM_InitTriggerCmd(TIM_ID_t timId, ControlState_t cmd)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    TIMx->TIM_OUTCR.INITRIGE = (uint32_t)cmd;
}

/**
 * @brief       TIM get match trigger flag Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 *
 * @return flag status
 *
 */
FlagStatus_t TIM_GetMatchTriggerFlag(TIM_ID_t timId)
{
    tim_reg_t const volatile* TIMx = timRegPtr[timId];
    
    return (FlagStatus_t) TIMx->TIM_OUTCR.TRIGF;
}

/**
 * @brief       TIM initialise center-aligned PWM output config Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  config:   Pointer to center-aligned PWM output config.
 *
 * @return none
 *
 */
void TIM_OutputCenterAlignedPwmConfig(TIM_ID_t timId, const TIM_PwmConfig_t * config)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    uint8_t i;
    TIM_ChannelId_t channelId;
    uint8_t pairId;
    
    TIMx->TIM_GLBCR.CNTMODE = (uint32_t)1UL;
    TIMx->TIM_MOD.MOD = config->maxCounterVal;
    TIMx->TIM_CNTINIT.CNTINIT = config->minCounterVal;
    
    for(i = 0; i < config->numChannels; i++)
    {
        channelId = config->pwmChConfig[i].channelId;
        pairId = (uint8_t)channelId >> 1U;
        
        TIM_SetCombineCmd(timId, (TIM_PairId_t)pairId, DISABLE);
        TIM_SetDualEdgeCaptureCmd(timId, (TIM_PairId_t)pairId, DISABLE);
        TIMx->TIM_CMCn[channelId].ELS = (uint32_t)config->pwmChConfig[i].pwmModeConfig;
        TIM_SetOutputPolarity(timId, channelId, config->pwmChConfig[i].polarity);
        TIMx->TIM_CCVn[channelId].CCV = config->pwmChConfig[i].compareValue;
        TIM_SetFaultCtrlCmd(timId, (TIM_PairId_t)pairId, config->pwmChConfig[i].faultCtrlChannelEnable);
        TIM_SetSyncPairCCVCmd(timId, (TIM_PairId_t)pairId, config->pwmChConfig[i].ccvUpdateEnable);
    }      
}

/**
 * @brief       TIM initialise edge-aligned PWM output config Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  config:   Pointer to edge-aligned PWM output config.
 *
 * @return none
 *
 */
void TIM_OutputEdgeAlignedPwmConfig(TIM_ID_t timId, const TIM_PwmConfig_t * config)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    uint8_t i;
    TIM_ChannelId_t channelId;
    uint8_t pairId;
    
    TIMx->TIM_GLBCR.CNTMODE = 0;
    TIMx->TIM_MOD.MOD = config->maxCounterVal;
    TIMx->TIM_CNTINIT.CNTINIT = config->minCounterVal;
    
    for(i = 0; i < config->numChannels; i++)
    {
        channelId = config->pwmChConfig[i].channelId;
        pairId = (uint8_t)channelId >> 1;
        
        TIM_SetCombineCmd(timId, (TIM_PairId_t)pairId, DISABLE);
        TIM_SetDualEdgeCaptureCmd(timId, (TIM_PairId_t)pairId, DISABLE);
        TIMx->TIM_CMCn[channelId].CMS = 2;
        TIMx->TIM_CMCn[channelId].ELS = (uint32_t)config->pwmChConfig[i].pwmModeConfig;
        TIM_SetOutputPolarity(timId, channelId, config->pwmChConfig[i].polarity);
        TIMx->TIM_CCVn[channelId].CCV = config->pwmChConfig[i].compareValue;
        TIM_SetFaultCtrlCmd(timId, (TIM_PairId_t)pairId, config->pwmChConfig[i].faultCtrlChannelEnable);
        TIM_SetSyncPairCCVCmd(timId, (TIM_PairId_t)pairId, config->pwmChConfig[i].ccvUpdateEnable);
    }
}

/**
 * @brief       TIM initialise complementary PWM output config Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  config:   Pointer to complementary PWM output config.
 *
 * @return none
 *
 */
void TIM_OutputComplementaryPwmConfig(TIM_ID_t timId, const TIM_CompPwmConfig_t * config)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    uint8_t i;
    uint8_t mainChannelId;
    uint8_t secondChannelId;
    TIM_PairId_t pairId;
    
    TIMx->TIM_GLBCR.CNTMODE = 0;
    TIMx->TIM_MOD.MOD = config->maxCounterVal;
    TIMx->TIM_CNTINIT.CNTINIT = config->minCounterVal;
    /*dead time config*/
    TIMx->TIM_FILTER.DTPS = (uint32_t)config->deadTimePrescaler;
    TIMx->TIM_FILTER.DTVAL = config->deadTimeVal;
    
    for(i = 0; i < config->numPairs; i++)
    {
        pairId = config->cPwmChConfig[i].pairId;
        mainChannelId = (uint8_t)pairId << 1U;
        secondChannelId = mainChannelId + 1U;
        
        TIM_SetCombineCmd(timId, pairId, ENABLE);
        TIM_SetDualEdgeCaptureCmd(timId, pairId, DISABLE);

        TIMx->TIM_CMCn[mainChannelId].ELS = (uint32_t)config->cPwmChConfig[i].pwmModeConfig;
        TIM_SetOutputPolarity(timId, (TIM_ChannelId_t)mainChannelId, config->cPwmChConfig[i].polarity);
        TIM_SetOutputPolarity(timId, (TIM_ChannelId_t)secondChannelId, config->cPwmChConfig[i].polarity);
        TIMx->TIM_CCVn[mainChannelId].CCV = config->cPwmChConfig[i].mainCompareValue;
        TIMx->TIM_CCVn[secondChannelId].CCV = config->cPwmChConfig[i].secondCompareValue;
        
        TIM_SetDeadTimeCmd(timId, pairId, config->cPwmChConfig[i].deadtimeEnable);
        TIM_SetFaultCtrlCmd(timId, pairId, config->cPwmChConfig[i].faultCtrlChannelEnable);
        TIM_SetSyncPairCCVCmd(timId, pairId, config->cPwmChConfig[i].ccvUpdateEnable);
    }
}

/**
 * @brief       TIM initialise fault control config Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  config:   Pointer to fault control config.
 *
 * @return none
 *
 */
void TIM_FaultControlConfig(TIM_ID_t timId, const TIM_PwmFaultCtrlConfig_t * config)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    /*fault control config*/
    TIMx->TIM_FLTCR.FAULTEN0 = (uint32_t)config->faultChannelConfig[0].faultInputChannelEnable;
    TIMx->TIM_FLTCR.FIFEN0 = (uint32_t)config->faultChannelConfig[0].faultInputFilterEnable;
    TIMx->TIM_FLTCR.FLTPOL0 = (uint32_t)config->faultChannelConfig[0].faultInputPolarity;
    TIMx->TIM_FLTCR.FAULTEN1 = (uint32_t)config->faultChannelConfig[1].faultInputChannelEnable;
    TIMx->TIM_FLTCR.FIFEN1 = (uint32_t)config->faultChannelConfig[1].faultInputFilterEnable;
    TIMx->TIM_FLTCR.FLTPOL1 = (uint32_t)config->faultChannelConfig[1].faultInputPolarity;
    TIMx->TIM_FLTCR.FIFVAL = (uint32_t)config->faultFilterValue;
    TIMx->TIM_FLTCR.FSTATE = (uint32_t)config->status;
    TIMx->TIM_FLTCR.FLTCM = (uint32_t)config->faultClearMode;
    TIMx->TIM_FLTCR.FLTCEN = (uint32_t)config->faultCtrlEnable;
}
                                          
/**
 * @brief       TIM initialise fault control config Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  cmd:      - ENABLE - DISABLE.
 *
 * @return none
 *
 */
void TIM_FaultControlCmd(TIM_ID_t timId, ControlState_t cmd)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    TIMx->TIM_FLTCR.FLTCEN = (uint32_t)cmd;
}

/**
 * @brief       TIM Software Trigger Sync Config Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  cmd:      Enable/Disable.
 *
 * @return none
 *
 */
void TIM_SWTriggerSyncCmd(TIM_ID_t timId, ControlState_t cmd)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    if(cmd == ENABLE)
    {
        TIMx->TIM_SYNC.SWWRBUF = 1U;
        TIMx->TIM_SYNC.SWRSTCNT = 1U;
    }
    else
    {
        TIMx->TIM_SYNC.SWWRBUF = 0U;
        TIMx->TIM_SYNC.SWRSTCNT = 0U;
    }
}

/**
 * @brief       TIM Reload Sync Config Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  cmd:      Enable/Disable.
 *
 * @return none
 *
 */
void TIM_ReloadSyncCmd(TIM_ID_t timId, ControlState_t cmd)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    if(cmd == ENABLE)
    {
        TIMx->TIM_RELOAD.LOADEN = 1U;
    }
    else
    {
        TIMx->TIM_RELOAD.LOADEN = 0U;
    }
}

/**
 * @brief       TIM PWM synchronization software trigger Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 *
 * @return none
 *
 */
void TIM_SyncSoftwareTrigger(TIM_ID_t timId)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    TIMx->TIM_SYNC.SWTRIG = 1U;
}

/**
 * @brief       TIM CNTINT update mode select Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  updateMode:  update mode.
 *
 * @return none
 *
 */
void TIM_CNTINTUpdateModeSelect(TIM_ID_t timId, TIM_RegUpdateMode_t updateMode)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    TIMx->TIM_SYNC.SYNCINIT = (uint32_t)updateMode;
}

/**
 * @brief       TIM Output Software Control Register update mode select Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  updateMode:  update mode.
 *
 * @return none
 *
 */
void TIM_OSWCUpdateModeSelect(TIM_ID_t timId, TIM_RegUpdateMode_t updateMode)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    TIMx->TIM_SYNC.SYNCOSWC = (uint32_t)updateMode;
}

/**
 * @brief       Enable/Disable TIM CCV register update function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  channelId:    Select channel id .
 * @param[in]  cmd:          enable/disable.
 *
 * @return none
 *
 */
void TIM_CCVUpdateCmd(TIM_ID_t timId, TIM_ChannelId_t channelId, ControlState_t cmd)
{
    uint8_t pairId;
    pairId = (uint8_t)channelId >> 1U;
    TIM_SetSyncPairCCVCmd(timId, (TIM_PairId_t)pairId, cmd);
}

/**
 * @brief       TIM Reload Param Config Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  reloadConfig:  reload param.
 *
 * @return none
 *
 */
void TIM_ReloadParamConfig(TIM_ID_t timId, const TIM_ReloadConfig_t* reloadConfig)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    uint8_t i;
    
    switch (reloadConfig->reloadMode)
    {
        case TIM_RELOAD_FULL_CYCLE:
            TIMx->TIM_RELOAD.HCSEL = 0U;
            TIMx->TIM_RELOAD.CH0SEL = 0U;
            TIMx->TIM_RELOAD.CH1SEL = 0U;
            TIMx->TIM_RELOAD.CH2SEL = 0U;
            TIMx->TIM_RELOAD.CH3SEL = 0U;
            TIMx->TIM_RELOAD.CH4SEL = 0U;
            TIMx->TIM_RELOAD.CH5SEL = 0U;
            TIMx->TIM_RELOAD.CH6SEL = 0U;
            TIMx->TIM_RELOAD.CH7SEL = 0U;
            break;
            
        case TIM_RELOAD_HALF_CYCLE:
            TIMx->TIM_RELOAD.HCSEL = 1U;
            TIMx->TIM_RELOAD.CH0SEL = 0U;
            TIMx->TIM_RELOAD.CH1SEL = 0U;
            TIMx->TIM_RELOAD.CH2SEL = 0U;
            TIMx->TIM_RELOAD.CH3SEL = 0U;
            TIMx->TIM_RELOAD.CH4SEL = 0U;
            TIMx->TIM_RELOAD.CH5SEL = 0U;
            TIMx->TIM_RELOAD.CH6SEL = 0U;
            TIMx->TIM_RELOAD.CH7SEL = 0U;
            break;
            
        case TIM_RELOAD_CHANNEL_MATCH:
            TIMx->TIM_RELOAD.HCSEL = 0U;
            break;
            
        default:
            /* do nothing */
            break;
    }
    
    TIMx->TIM_RELOAD.LDFREQ = reloadConfig->loadFrequency;
    
    for(i=0; i<reloadConfig->numChannels; i++)
    {
        TIM_ChannleMatchReloadCmd(timId, 
                                  reloadConfig->channelMatchConfig[i].channelId,
                                  reloadConfig->channelMatchConfig[i].channelMatchEnable);
    }
    
}

/**
 * @brief       TIM Set channel match reload cmd enable/disable Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  channelId:    Select channel id .
 * @param[in]  cmd:     enable/disable.
 *
 * @return none
 *
 */
void TIM_ChannleMatchReloadCmd(TIM_ID_t timId, TIM_ChannelId_t channelId, 
                                ControlState_t cmd)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    switch (channelId)
    {
        case TIM_CHANNEL_0:
            TIMx->TIM_RELOAD.CH0SEL = (uint32_t)cmd;
            break;
            
        case TIM_CHANNEL_1:
            TIMx->TIM_RELOAD.CH1SEL = (uint32_t)cmd;
            break;
            
        case TIM_CHANNEL_2:
            TIMx->TIM_RELOAD.CH2SEL = (uint32_t)cmd;
            break;
            
        case TIM_CHANNEL_3:
            TIMx->TIM_RELOAD.CH3SEL = (uint32_t)cmd;
            break;
            
        case TIM_CHANNEL_4:
            TIMx->TIM_RELOAD.CH4SEL = (uint32_t)cmd;
            break;
            
        case TIM_CHANNEL_5:
            TIMx->TIM_RELOAD.CH5SEL = (uint32_t)cmd;
            break;
            
        case TIM_CHANNEL_6:
            TIMx->TIM_RELOAD.CH6SEL = (uint32_t)cmd;
            break;
            
        case TIM_CHANNEL_7:
            TIMx->TIM_RELOAD.CH7SEL = (uint32_t)cmd;
            break;
            
        default:
            /* do nothing */
            break;
      
    }
}

/**
 * @brief       TIM PWM Sync Configure Function
 *
 * @param[in]  timId:        Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  syncConfig:   Pointer to sync configure struct.
 *
 * @return none
 *
 */
void TIM_SyncConfig(TIM_ID_t timId, const TIM_PwmSyncConfig_t* syncConfig)
{
    TIM_CNTINTUpdateModeSelect(timId, syncConfig->cntinitSync);
    
    TIM_OSWCUpdateModeSelect(timId, syncConfig->outswcSync);
    
    TIM_SWTriggerSyncCmd(timId, syncConfig->syncSWTriggerEnable);
    
    if(ENABLE == syncConfig->syncReloadEnable)
    {
        TIM_ReloadParamConfig(timId, syncConfig->reloadConfig);
    }
   
}

/**
 * @brief       TIM INT DMA enable/disable Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  channelId:    Selcct channel ID.
 * @param[in]  cmd:  enable/disable.
 *
 * @return none
 *
 */
void TIM_DMACtrl(TIM_ID_t timId, TIM_ChannelId_t channelId, ControlState_t cmd)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    TIMx->TIM_CMCn[channelId].DMAEN = (uint32_t)cmd;
}

/**
 * @brief       TIM INT mask/unmask Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  intType:    Selcct interrupt type.
 * @param[in]  intMask:  mask/unmask .
 *
 * @return none
 *
 */
void TIM_IntMask(TIM_ID_t timId, TIM_INT_t intType, IntMask_t intMask)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    ControlState_t cmd = (intMask == UNMASK) ? ENABLE : DISABLE;

    switch (intType)
    {
        case TIM_INT_CH0:
            TIMx->TIM_CMCn[0].CHIE = (uint32_t)cmd;
            break;
            
        case TIM_INT_CH1:
            TIMx->TIM_CMCn[1].CHIE = (uint32_t)cmd;
            break;
            
        case TIM_INT_CH2:
            TIMx->TIM_CMCn[2].CHIE = (uint32_t)cmd;
            break;
            
        case TIM_INT_CH3:
            TIMx->TIM_CMCn[3].CHIE = (uint32_t)cmd;
            break;
        case TIM_INT_CH4:
            TIMx->TIM_CMCn[4].CHIE = (uint32_t)cmd;
            break;
            
        case TIM_INT_CH5:
            TIMx->TIM_CMCn[5].CHIE = (uint32_t)cmd;
            break;
            
        case TIM_INT_CH6:
            TIMx->TIM_CMCn[6].CHIE = (uint32_t)cmd;
            break;
            
        case TIM_INT_CH7:
            TIMx->TIM_CMCn[7].CHIE = (uint32_t)cmd;
            break;
            
        case TIM_INT_RLD:
            TIMx->TIM_GLBCR.RLDIE = (uint32_t)cmd;
            break;
            
        case TIM_INT_TO:
            TIMx->TIM_GLBCR.TOIE = (uint32_t)cmd;
            break;
            
        case TIM_INT_FAULT:
            TIMx->TIM_FLTCR.FLTIE = (uint32_t)cmd;
            break;
            
        case TIM_INT_ALL:
            TIMx->TIM_CMCn[0].CHIE = (uint32_t)cmd;
            TIMx->TIM_CMCn[1].CHIE = (uint32_t)cmd;
            TIMx->TIM_CMCn[2].CHIE = (uint32_t)cmd;
            TIMx->TIM_CMCn[3].CHIE = (uint32_t)cmd;
            TIMx->TIM_CMCn[4].CHIE = (uint32_t)cmd;
            TIMx->TIM_CMCn[5].CHIE = (uint32_t)cmd;
            TIMx->TIM_CMCn[6].CHIE = (uint32_t)cmd;
            TIMx->TIM_CMCn[7].CHIE = (uint32_t)cmd;
            TIMx->TIM_GLBCR.RLDIE = (uint32_t)cmd;
            TIMx->TIM_GLBCR.TOIE = (uint32_t)cmd;
            TIMx->TIM_FLTCR.FLTIE = (uint32_t)cmd;
            break;
            
        default:
            /* do nothing */
            break;
      
    }    
}

/**
 * @brief       TIM INT status clear Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  intType:    Selcct interrupt type.
 *
 * @return none
 *
 */
void TIM_IntClear(TIM_ID_t timId, TIM_INT_t intType)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    switch (intType)
    {
        case TIM_INT_CH0:
            TIMx->TIM_CMCn[0].CHF = 0;
            break;
            
        case TIM_INT_CH1:
            TIMx->TIM_CMCn[1].CHF = 0;
            break;
            
        case TIM_INT_CH2:
            TIMx->TIM_CMCn[2].CHF = 0;
            break;
            
        case TIM_INT_CH3:
            TIMx->TIM_CMCn[3].CHF = 0;
            break;
        case TIM_INT_CH4:
            TIMx->TIM_CMCn[4].CHF = 0;
            break;
            
        case TIM_INT_CH5:
            TIMx->TIM_CMCn[5].CHF = 0;
            break;
            
        case TIM_INT_CH6:
            TIMx->TIM_CMCn[6].CHF = 0;
            break;
            
        case TIM_INT_CH7:
            TIMx->TIM_CMCn[7].CHF = 0;
            break;
            
        case TIM_INT_RLD:
            TIMx->TIM_GLBSR.RLDF = 0;
            break;
            
        case TIM_INT_TO:
            TIMx->TIM_GLBSR.TOF = 0;
            break;
            
        case TIM_INT_FAULT:
            TIMx->TIM_FLTSR.FAULTF = 0;
            break;
            
        case TIM_INT_ALL:
            TIMx->TIM_CMCn[0].CHF = 0;
            TIMx->TIM_CMCn[1].CHF = 0;
            TIMx->TIM_CMCn[2].CHF = 0;
            TIMx->TIM_CMCn[3].CHF = 0;
            TIMx->TIM_CMCn[4].CHF = 0;
            TIMx->TIM_CMCn[5].CHF = 0;
            TIMx->TIM_CMCn[6].CHF = 0;
            TIMx->TIM_CMCn[7].CHF = 0;
            TIMx->TIM_GLBSR.RLDF = 0;
            TIMx->TIM_GLBSR.TOF = 0;
            TIMx->TIM_FLTSR.FAULTF = 0;
            break;
            
        default:
            /* do nothing */
            break;
      
    }    
}

/**
 * @brief       TIM Get INT status Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  intType:    Selcct interrupt type.
 *
 * @return intstatus
 *
 */
IntStatus_t TIM_GetIntStatus(TIM_ID_t timId, TIM_INT_t intType)
{
    tim_reg_t const volatile* TIMx = timRegPtr[timId];
    IntStatus_t intStatus = RESET;
    
    switch (intType)
    {
        case TIM_INT_CH0:
            intStatus = (IntStatus_t)TIMx->TIM_CMCn[0].CHF;
            break;
            
        case TIM_INT_CH1:
            intStatus = (IntStatus_t)TIMx->TIM_CMCn[1].CHF;
            break;
            
        case TIM_INT_CH2:
            intStatus = (IntStatus_t)TIMx->TIM_CMCn[2].CHF;
            break;
            
        case TIM_INT_CH3:
            intStatus = (IntStatus_t)TIMx->TIM_CMCn[3].CHF;
            break;
            
        case TIM_INT_CH4:
            intStatus = (IntStatus_t)TIMx->TIM_CMCn[4].CHF;
            break;
            
        case TIM_INT_CH5:
            intStatus = (IntStatus_t)TIMx->TIM_CMCn[5].CHF;
            break;
            
        case TIM_INT_CH6:
            intStatus = (IntStatus_t)TIMx->TIM_CMCn[6].CHF;
            break;
            
        case TIM_INT_CH7:
            intStatus = (IntStatus_t)TIMx->TIM_CMCn[7].CHF;
            break;
            
        case TIM_INT_RLD:
            intStatus = (IntStatus_t)TIMx->TIM_GLBSR.RLDF;
            break;
            
        case TIM_INT_TO:
            intStatus = (IntStatus_t)TIMx->TIM_GLBSR.TOF;
            break;
            
        case TIM_INT_FAULT:
            intStatus = (IntStatus_t)TIMx->TIM_FLTSR.FAULTF;
            break;
            
        default:
            /* do nothing */
            break;
      
    }  
    
    return intStatus;
}

/**
 * @brief       TIM Get Fault detection flag status of fault channel  Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  channelId: Selcct fault channel:TIM_FAULT_CHANNEL_0,.. .
 *
 * @return intstatus
 *
 */
IntStatus_t TIM_GetFaultStatus(TIM_ID_t timId, TIM_FaultChannelId_t channelId)
{
    tim_reg_t const volatile* TIMx = timRegPtr[timId];
    IntStatus_t intStatus = RESET;
    
    switch (channelId)
    {
        case TIM_FAULT_CHANNEL_0:
            intStatus = (IntStatus_t)TIMx->TIM_FLTSR.FAULTF0;
            break;
            
        case TIM_FAULT_CHANNEL_1:
            intStatus = (IntStatus_t)TIMx->TIM_FLTSR.FAULTF1;
            break;
            
        case TIM_FAULT_CHANNEL_ALL:
            intStatus = (IntStatus_t)TIMx->TIM_FLTSR.FAULTF;
            break;
            
        default:
            /* do nothing */
            break;
        
    }    
    
    return intStatus;
}

/**
 * @brief       TIM fault status clear Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  intType:    Selcct interrupt type.
 *
 * @return none
 *
 */
void TIM_FaultStatusClear(TIM_ID_t timId, TIM_FaultChannelId_t channelId)
{
    tim_reg_t * TIMx = timRegPtr[timId];
    
    switch (channelId)
    {
        case TIM_FAULT_CHANNEL_0:
            TIMx->TIM_FLTSR.FAULTF0 = 0;
        break;
        
        case TIM_FAULT_CHANNEL_1:
            TIMx->TIM_FLTSR.FAULTF1 = 0;
            break;
           
        case TIM_FAULT_CHANNEL_ALL:
            TIMx->TIM_FLTSR.FAULTF0 = 0;
            TIMx->TIM_FLTSR.FAULTF1 = 0;
            TIMx->TIM_FLTSR.FAULTF = 0;
            break;
            
        default:
            /* do nothing */
            break;
    }
            
}

/**
 * @brief       TIM match trigger clear Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 *
 * @return none
 *
 */
void TIM_MatchTriggerClear(TIM_ID_t timId)
{
     tim_reg_t * TIMx = timRegPtr[timId];
     
     TIMx->TIM_OUTCR.TRIGF = 0;
}

/**
 * @brief       TIM INT mask/unmask Function
 *
 * @param[in]  timId:    Select the TIM ID: TIM0_ID, TIM1_ID, ... .
 * @param[in]  intType:    Selcct interrupt type.
 * @param[in]  cbFun:  callback function .
 *
 * @return none
 *
 */
void TIM_InstallCallBackFunc(TIM_ID_t timId, TIM_INT_t intType, isr_cb_t * cbFun)
{
    timIsrCbFunc[timId][intType] = cbFun;
}

/*@} end of group TIM_Public_Functions */

/*@} end of group TIM_definitions */

/*@} end of group Z20K11X_Peripheral_Driver */
