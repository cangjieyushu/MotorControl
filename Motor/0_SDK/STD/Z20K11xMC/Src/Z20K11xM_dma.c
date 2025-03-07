/**************************************************************************************************/
/**
 * @file      : Z20K11xM_dma.c
 * @brief     : DMA module driver file.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (c) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#include "Z20K11xM_dma.h"

/** @addtogroup  Z20K11XM_Peripheral_Driver
 *  @{
 */

/** @defgroup DMA
 *  @brief DMA driver modules
 *  @{
 */

/** @defgroup DMA_Private_Defines
 *  @{
 */
/*PRQA S 0303 ++*/
static dma_chmux_reg_t * const dmaMuxRegPtr = (dma_chmux_reg_t *) DMAMUX_BASE_ADDR;        /*!< DMAMUX Register */
static dma_reg_t * const dmaRegPtr = (dma_reg_t *) DMA_BASE_ADDR;                          /*!< DMA Register */
static dma_reg_w_t * const dmaRegWPtr = (dma_reg_w_t *) DMA_BASE_ADDR;                     /*!< DMA Word Register */
/*PRQA S 0303 --*/

#define DMA0TO3_NUM                 0x00000004U              /*!< dma 0 to 3 int entry idx */               
#define DMA4TO7_NUM                 0x00000008U              /*!< dma 4 to 7 int entry idx */
#define DMA8TO11_NUM                0x0000000CU              /*!< dma 8 to 11 int entry idx */
#define DMA12TO15_NUM               0x00000010U              /*!< dma 12 to 15 int entry idx */

#define DMA_CHANNEL0_MASK           0x00000001U              /*!< dma channel 0 mask */
#define DMA_CHANNEL1_MASK           0x00000002U              /*!< dma channel 1 mask */
#define DMA_CHANNEL2_MASK           0x00000004U              /*!< dma channel 2 mask */
#define DMA_CHANNEL3_MASK           0x00000008U              /*!< dma channel 3 mask */
#define DMA_CHANNEL4_MASK           0x00000010U              /*!< dma channel 4 mask */
#define DMA_CHANNEL5_MASK           0x00000020U              /*!< dma channel 5 mask */
#define DMA_CHANNEL6_MASK           0x00000040U              /*!< dma channel 6 mask */
#define DMA_CHANNEL7_MASK           0x00000080U              /*!< dma channel 7 mask */
#define DMA_CHANNEL8_MASK           0x00000100U              /*!< dma channel 8 mask */
#define DMA_CHANNEL9_MASK           0x00000200U              /*!< dma channel 9 mask */
#define DMA_CHANNEL10_MASK          0x00000400U              /*!< dma channel 10 mask */
#define DMA_CHANNEL11_MASK          0x00000800U              /*!< dma channel 11 mask */
#define DMA_CHANNEL12_MASK          0x00001000U              /*!< dma channel 12 mask */
#define DMA_CHANNEL13_MASK          0x00002000U              /*!< dma channel 13 mask */
#define DMA_CHANNEL14_MASK          0x00004000U              /*!< dma channel 14 mask */
#define DMA_CHANNEL15_MASK          0x00008000U              /*!< dma channel 15 mask */
#define DMA_CHANNELALL_MASK         0x0000FFFFU              /*!< dma all channels mask */

#define DMA_CHANNEL_PRI_MASK        ((uint32_t)0x0000000FU)  /*!< dma channel priority mask */

/**  
 *  @brief Calculate priority shift of reg via channel
 */
#define DMA_CHANNEL_PRI_SHIFT(x)    ((uint32_t)(24U - (((uint32_t)(x) & 0x03U) << 3U)))
#define DMA_CHANNEL_PREEMPT_MASK    ((uint32_t)0x00000003U)  /*!< dma channel preempt set mask */

/**  
 *  @brief Calculate preempt shift of reg via channel
 */
#define DMA_CHANNEL_PREEMPT_SHIFT(x) ((uint32_t)(30U - (((uint32_t)(x) & 0x03U) << 3U)))

/**  
 *  @brief Get base address of priority reg
 */
#define DMA_PRIORITY_REG_BASEADDR   ((uint32_t)(&(dmaRegWPtr->DMA_CPRI0)))

#define DMA_ERROR_ALL_MASK          0x00008000U                            /*!< dma all error mask */
#define DMA_ERROR_PRIORITY_MASK     0x00002000U                            /*!< dma priority error mask */
#define DMA_ERROR_SRCADDR_MASK      0x00000080U                            /*!< dma src addr unalign error mask */
#define DMA_ERROR_SRCOFFSET_MASK    0x00000040U                            /*!< dma src offset unalign error mask */  
#define DMA_ERROR_DESTADDR_MASK     0x00000020U                            /*!< dma dest addr unalign error mask */
#define DMA_ERROR_DESTOFFSET_MASK   0x00000010U                            /*!< dma dest offset unalign error mask */
#define DMA_ERROR_TRANSFERNUM_MASK  0x00000008U                            /*!< dma number of transfer unalign error mask */
#define DMA_ERROR_SRCBUS_MASK       0x00000002U                            /*!< dma src access error mask */
#define DMA_ERROR_DESTBUS_MASK      0x00000001U                            /*!< dma dest access error mask */

#define DMA_ERROR_ALL_SHIFT         15U                                    /*!< dma all error shift */
#define DMA_ERROR_PRIORITY_SHIFT    13U                                    /*!< dma priority error shift */
#define DMA_ERROR_SRCADDR_SHIFT     7U                                     /*!< dma src addr unalign error shift */
#define DMA_ERROR_SRCOFFSET_SHIFT   6U                                     /*!< dma src offset unalign error shift */
#define DMA_ERROR_DESTADDR_SHIFT    5U                                     /*!< dma dest addr unalign error shift */
#define DMA_ERROR_DESTOFFSET_SHIFT  4U                                     /*!< dma dest offset unalign error shift */
#define DMA_ERROR_TRANSFERNUM_SHIFT 3U                                     /*!< dma number of transfer unalign error shift */
#define DMA_ERROR_SRCBUS_SHIFT      1U                                     /*!< dma src access error shift */
#define DMA_ERROR_DESTBUS_SHIFT     0U                                     /*!< dma dest access error shift */

/**  
 *  @brief Calculate set value of mask control
 */
#define DMA_MASK_CONVERT_ENABLE(x)  (((uint32_t)(x) + 1U) & 0x1U)

#define DMA_GCC_WPEN0_MASK          0x80808000U                           /*!< WPEN0 of global channel control reg mask */
#define DMA_GCC_WPEN1_MASK          0x80800080U                           /*!< WPEN1 of global channel control reg mask */
#define DMA_GCC_WPEN2_MASK          0x80008080U                           /*!< WPEN2 of global channel control reg mask */
#define DMA_GCC_WPEN3_MASK          0x00808080U                           /*!< WPEN3 of global channel control reg mask */
#define DMA_GCC_WPEN03_MASK         0x00808000U                           /*!< WPEN0&3 of global channel control reg mask */
#define DMA_GCC_WPEN23_MASK         0x00008080U                           /*!< WPEN2&3 of global channel control reg mask */
#define DMA_GCC_CACIS_MASK          0x40000000U                           /*!< CACIS of global channel control reg mask */
#define DMA_GCC_CACES_MASK          0x00400000U                           /*!< CACES of global channel control reg mask */
#define DMA_GCC_SACSTART_MASK       0x00004000U                           /*!< SACSTART of global channel control reg mask */
#define DMA_GCC_CACDONE_MASK        0x00000040U                           /*!< CACDONE of global channel control reg mask */
#define DMA_GCC_CACIES_MASK         0x40400000U                           /*!< CACIS&CACES of global channel control reg mask */
#define DMA_GCC_CCIS_MASK           0x0F000000U                           /*!< CCIS of global channel control reg mask */
#define DMA_GCC_CCES_MASK           0x000F0000U                           /*!< CCES of global channel control reg mask */
#define DMA_GCC_SCSTART_MASK        0x00000F00U                           /*!< SCSTART of global channel control reg mask */
#define DMA_GCC_CCDONE_MASK         0x0000000FU                           /*!< CCDONE of global channel control reg mask */
#define DMA_GCC_CCIES_MASK          0x0F0F0000U                           /*!< CCIS&CCES of global channel control reg mask */
#define DMA_GCC_CCDONE_SHIFT        0U                                    /*!< CCDONE of global channel control reg shift */
#define DMA_GCC_CCES_SHIFT          16U                                   /*!< CCES of global channel control reg shift */
#define DMA_GCC_CCIS_SHIFT          24U                                   /*!< CCIS of global channel control reg shift */
                                       
#define DMA_CHANNEL_NUM             16U                                   /*!< max number of dma channels */

/**  
 *  @brief Calculate whether unsigned number is divided with no remainder
 */
#define DMA_GET_UNSIGNED_REMAINDER(x, y) ((uint32_t)(x) & (((uint32_t)1U << (uint32_t)(y)) - 1U))

/**  
 *  @brief Calculate whether signed number is divided with no remainder
 */
#define DMA_GET_SIGNED_REMAINDER(x, y) ((int32_t)(x) >= 0 ? \
                                       ((uint32_t)(x) & (((uint32_t)1U << (uint32_t)(y)) - 1U)) : \
                                       ((((uint32_t)(x) - 1U) ^ 0xFFFFFFFFU) & \
                                       (((uint32_t)1U << (uint32_t)(y)) - 1U)))

/** @} end of group DMA_Private_Defines */


/** @defgroup DMA_Private_Type
 *  @{
 */

/** @} end of group DMA_Private_Type*/



/** @defgroup DMA_Private_Variables
 *  @{
 */

/*! @brief dma channel mask array */
static const uint32_t dmaChannelMask[] = 
{
    DMA_CHANNEL0_MASK,                       /*!< dma channel 0 mask */
    DMA_CHANNEL1_MASK,                       /*!< dma channel 1 mask */
    DMA_CHANNEL2_MASK,                       /*!< dma channel 2 mask */
    DMA_CHANNEL3_MASK,                       /*!< dma channel 3 mask */
    DMA_CHANNEL4_MASK,                       /*!< dma channel 4 mask */
    DMA_CHANNEL5_MASK,                       /*!< dma channel 5 mask */
    DMA_CHANNEL6_MASK,                       /*!< dma channel 6 mask */
    DMA_CHANNEL7_MASK,                       /*!< dma channel 7 mask */
    DMA_CHANNEL8_MASK,                       /*!< dma channel 8 mask */
    DMA_CHANNEL9_MASK,                       /*!< dma channel 9 mask */
    DMA_CHANNEL10_MASK,                      /*!< dma channel 10 mask */
    DMA_CHANNEL11_MASK,                      /*!< dma channel 11 mask */
    DMA_CHANNEL12_MASK,                      /*!< dma channel 12 mask */
    DMA_CHANNEL13_MASK,                      /*!< dma channel 13 mask */
    DMA_CHANNEL14_MASK,                      /*!< dma channel 14 mask */
    DMA_CHANNEL15_MASK                       /*!< dma channel 15 mask */
};

/*! @brief dma error shift array */
static const uint32_t dmaErrorShift[] = 
{
    DMA_ERROR_PRIORITY_SHIFT,                /*!< dma priority error shift */
    DMA_ERROR_SRCADDR_SHIFT,                 /*!< dma src addr unalign error shift */
    DMA_ERROR_SRCOFFSET_SHIFT,               /*!< dma src offset unalign error shift */
    DMA_ERROR_DESTADDR_SHIFT,                /*!< dma dest addr unalign error shift */
    DMA_ERROR_DESTOFFSET_SHIFT,              /*!< dma dest offset unalign error shift */
    DMA_ERROR_TRANSFERNUM_SHIFT,             /*!< dma number of transfer unalign error shift */
    DMA_ERROR_SRCBUS_SHIFT,                  /*!< dma src access error shift */
    DMA_ERROR_DESTBUS_SHIFT,                 /*!< dma dest access error shift */
    DMA_ERROR_ALL_SHIFT                      /*!< dma all error shift */
};

static const uint32_t dmaGccWpenMask[] = 
{
    DMA_GCC_WPEN2_MASK,                      /*!< WPEN2 of global channel control reg mask */
    DMA_GCC_WPEN3_MASK,                      /*!< WPEN3 of global channel control reg mask */
    DMA_GCC_WPEN23_MASK                      /*!< WPEN2&3 of global channel control reg mask */
};
                            
static const uint32_t dmaGccClearAllChannelsMask[] = 
{
    DMA_GCC_CACES_MASK,                      /*!< CACES of global channel control reg mask */
    DMA_GCC_CACIS_MASK,                      /*!< CACIS of global channel control reg mask */
    DMA_GCC_CACIES_MASK                      /*!< CACIS&CACES of global channel control reg mask */
};

static const uint32_t dmaGccClearChannelsMask[] = 
{
    DMA_GCC_CCES_MASK,                      /*!< CCES of global channel control reg mask */
    DMA_GCC_CCIS_MASK,                      /*!< CCIS of global channel control reg mask */
    DMA_GCC_CCIES_MASK                      /*!< CCIS&CCES of global channel control reg mask */
};

/*! @brief DMA ISR CallBack VECTOR structure */
static isr_cb_t * dmaIsrCb[DMA_CHANNEL_NUM][DMA_INT_ALL]= 
{
    {NULL, NULL},
    {NULL, NULL},
    {NULL, NULL},
    {NULL, NULL},
    {NULL, NULL},
    {NULL, NULL},
    {NULL, NULL},
    {NULL, NULL},
    {NULL, NULL},
    {NULL, NULL},
    {NULL, NULL},
    {NULL, NULL},
    {NULL, NULL},
    {NULL, NULL},
    {NULL, NULL},
    {NULL, NULL}
};

/** @} end of group DMA_Private_Variables */

/** @defgroup DMA_Global_Variables
 *  @{
 */

/** @} end of group DMA_Global_Variables */

/** @defgroup DMA_Private_FunctionDeclaration
 *  @{
 */

void DMA0TO3_DriverIRQHandler(void);
void DMA4TO7_DriverIRQHandler(void);
void DMA8TO11_DriverIRQHandler(void);
void DMA12TO15_DriverIRQHandler(void);
void DMAERR_DriverIRQHandler(void);
/** @} end of group DMA_Private_FunctionDeclaration */

/** @defgroup DMA_Private_Functions
 *  @{
 */

/** @} end of group DMA_Private_Functions */


/** @defgroup DMA_Public_Functions
 *  @{
 */

/**
 * @brief      Select dmamux input source Function
 *
 * @param[in]  outChannel:     output channel id.
 * @param[in]  questSource:    inpout source.
 *
 * @return none
 *
 */
void DMAMUX_SelChannelSource(DMA_Channel_t outChannel, 
                                      DMA_RequestSource_t questSource)
{
    dmaMuxRegPtr->DMA_MUX_CH_CFG[outChannel].SRC_MUX = (uint32_t)questSource;
}

/**
 * @brief      Enable dmamux output channel Function
 *
 * @param[in]  outChannel:     output channel id.
 *
 * @return none
 *
 */
void DMAMUX_OutputChannelEnable(DMA_Channel_t outChannel)
{
    dmaMuxRegPtr->DMA_MUX_CH_CFG[outChannel].ENABLE = 1U;
}

/**
 * @brief      Disable dmamux output channel Function
 *
 * @param[in]  outChannel:     output channel id.
 *
 * @return none
 *
 */
void DMAMUX_OutputChannelDisable(DMA_Channel_t outChannel)
{
    dmaMuxRegPtr->DMA_MUX_CH_CFG[outChannel].ENABLE = 0U;
}


/**
 * @brief      Dma Initializes Function
 *
 * @param[in]  ptDMAInitConfig:     Pointer to a DMA configuration structure.
 *
 * @return none
 *
 */
void DMA_Init(const DMA_Config_t * ptDMAInitConfig)
{
    dmaRegPtr->DMA_CONF.HOEE = (uint32_t)ptDMAInitConfig->dmaErrorBehavior;
    dmaRegPtr->DMA_CONF.DBGE = (uint32_t)ptDMAInitConfig->dmaDebugBehavior;
    dmaRegPtr->DMA_CONF.RRCAE = (uint32_t)ptDMAInitConfig->dmaPriorityArbitration;
}

/**
 * @brief      Get dma busy status Function
 *
 * @param[in]  none
 *
 * @return     busy status.
 *
 */
FlagStatus_t DMA_GetDmaBusyStatus(void)
{
    return ((FlagStatus_t)dmaRegPtr->DMA_CONF.BUSY);
}

/**
 * @brief      Halt dma Function
 *
 * @param[in]  cmd: halt control
 *                  - ENABLE: stall the dma start a new channels for transfer
 *                  - DISABLE: dma is not stall
 *
 * @return none.
 *
 */
void DMA_HaltControl(ControlState_t cmd)
{
    dmaRegPtr->DMA_CONF.HALT = (uint32_t)cmd;
}

/**
 * @brief      Get dma halt status Function
 *
 * @param[in]  none
 *
 * @return whether dma halt is asserted or not.
 *
 */
FlagStatus_t DMA_GetHaltStatus(void)
{
    return ((FlagStatus_t)dmaRegPtr->DMA_CONF.HALT);
}

/**
 * @brief      Set dma priority arbitration mode Function
 *
 * @param[in]  channelArbitration: arbitration mode
 *
 * @return none.
 *
 */
void DMA_SetPriorityArbitrationMode(DMA_PriorityArbitration_t arbitration)
{
    dmaRegPtr->DMA_CONF.RRCAE = (uint32_t)arbitration;
}

/**
 * @brief       Get dma current priority arbitration mode Function
 *
 * @param[in]  none
 *
 * @return     current priority arbitration mode.
 *
 */
DMA_PriorityArbitration_t DMA_GetPriorityArbitrationMode(void)
{
    return ((DMA_PriorityArbitration_t)dmaRegPtr->DMA_CONF.RRCAE);
}

/**
 * @brief      Enable dma channel request Function
 *
 * @param[in]  channel: dma channel id
 *
 * @return none.
 *
 */
void DMA_ChannelRequestEnable(DMA_Channel_t channel)
{
    dmaRegWPtr->DMA_DMAE |= dmaChannelMask[channel];
}

/**
 * @brief      Disable dma channel request Function
 *
 * @param[in]  channel: dma channel id
 *
 * @return none.
 *
 */
void DMA_ChannelRequestDisable(DMA_Channel_t channel)
{
    dmaRegWPtr->DMA_DMAE &= ~dmaChannelMask[channel];
}

/**
 * @brief      Get dma channel request status Function
 *
 * @param[in]  channel: dma channel id
 *
 * @return whether dma channel request enable bit is asserted or not.
 *
 */
FlagStatus_t DMA_GetChannelRequestStatus(DMA_Channel_t channel)
{
    return ((FlagStatus_t)((uint32_t)(dmaRegWPtr->DMA_DMAE >> (uint32_t)channel & 0x01U)));
}

/**
 * @brief      Set dma channel priority Function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  priority: channel priority
 *
 * @return none.
 *
 */
void DMA_SetChannelPriority(DMA_Channel_t channel, 
                                     DMA_ChannelPriority_t priority)
{
    uint32_t regValue;
    /*PRQA S 0303 ++*/
    volatile uint32_t * priRegPtr = (volatile uint32_t *)(DMA_PRIORITY_REG_BASEADDR 
                                      + ((uint32_t)channel >> 0x2U) * 4U);
    /*PRQA S 0303 --*/
    
    regValue = *priRegPtr;
    regValue &= ~(DMA_CHANNEL_PRI_MASK << DMA_CHANNEL_PRI_SHIFT(channel));
    regValue |= (uint32_t)priority << DMA_CHANNEL_PRI_SHIFT(channel);
    *priRegPtr = regValue;
}

/**
 * @brief      Get dma channel priority Function
 *
 * @param[in]  channel: dma channel id
 *
 * @return channel priority.
 *
 */
DMA_ChannelPriority_t DMA_GetChannelPriority(DMA_Channel_t channel)
{
    /*PRQA S 0303 ++*/
    volatile uint32_t * priRegPtr = (volatile uint32_t *)(DMA_PRIORITY_REG_BASEADDR 
                                      + ((uint32_t)channel >> 0x2U) * 4U);
    /*PRQA S 0303 --*/
    
    return ((DMA_ChannelPriority_t)((uint32_t)(*priRegPtr >> 
            DMA_CHANNEL_PRI_SHIFT(channel) & DMA_CHANNEL_PRI_MASK)));
}

/**
 * @brief      Set dma channel preempt type Function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  preempt: channel preempt type
 *
 * @return none.
 *
 */
void DMA_SetChannelPreempt(DMA_Channel_t channel, 
                                    DMA_ChannelPreempt_t preempt)
{
    uint32_t regValue;
    /*PRQA S 0303 ++*/
    volatile uint32_t * priRegPtr = (volatile uint32_t *)(DMA_PRIORITY_REG_BASEADDR 
                                      + ((uint32_t)channel >> 0x2U) * 4U);
    /*PRQA S 0303 --*/
    
    regValue = *priRegPtr;
    regValue &= ~(DMA_CHANNEL_PREEMPT_MASK << 
                   DMA_CHANNEL_PREEMPT_SHIFT(channel));
    regValue |= (uint32_t)preempt << DMA_CHANNEL_PREEMPT_SHIFT(channel);
    *priRegPtr = regValue;
}

/**
 * @brief      Get dma channel preempt type Function
 *
 * @param[in]  channel: dma channel id
 *
 * @return channel preempt type.
 *
 */
DMA_ChannelPreempt_t DMA_GetChannelPreempt(DMA_Channel_t channel)
{
    /*PRQA S 0303 ++*/
    volatile uint32_t * priRegPtr = (volatile uint32_t *)(DMA_PRIORITY_REG_BASEADDR 
                                      + ((uint32_t)channel >> 0x2U) * 4U);
    /*PRQA S 0303 --*/
    
    return ((DMA_ChannelPreempt_t)((uint32_t)(*priRegPtr >> 
            DMA_CHANNEL_PREEMPT_SHIFT(channel) & DMA_CHANNEL_PREEMPT_MASK)));
}

/**
 * @brief      Set dma source address Function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  address: dma transfer source address.
 *
 * @return none.
 *
 */
void DMA_SetSrcAddr(DMA_Channel_t channel, uint32_t address)
{
    dmaRegPtr->DMA_CH_CONFIG[channel].DMA_SADDR.SADDR = address;
}

/**
 * @brief      Get dma source address Function
 *
 * @param[in]  channel: dma channel id
 *
 * @return dma source address.
 *
 */
uint32_t DMA_GetSrcAddr(DMA_Channel_t channel)
{
    return ((uint32_t)dmaRegPtr->DMA_CH_CONFIG[channel].DMA_SADDR.SADDR);
}

/**
 * @brief      Set dma destination address Function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  address: dma transfer destination address
 *
 * @return none.
 *
 */
void DMA_SetDestAddr(DMA_Channel_t channel, uint32_t address)
{
    dmaRegPtr->DMA_CH_CONFIG[channel].DMA_DADDR.DADDR = address;
}

/**
 * @brief      Get dma destination address Function
 *
 * @param[in]  channel: dma channel id
 *
 * @return dma destination address.
 *
 */
uint32_t DMA_GetDestAddr(DMA_Channel_t channel)
{
    return ((uint32_t)dmaRegPtr->DMA_CH_CONFIG[channel].DMA_DADDR.DADDR);
}

/**
 * @brief      Set dma source address offset in minor loop Function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  offest: dma source address offset in minor loop
 *
 * @return none.
 *
 */
void DMA_SetMinorLoopSrcOffest(DMA_Channel_t channel, int16_t offest)
{
    dmaRegPtr->DMA_CH_CONFIG[channel].DMA_AOFF.SAOFF = offest;
}

/**
 * @brief      Set dma destination address offset in minor loop Function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  offest: dma destination address offset in minor loop
 *
 * @return none.
 *
 */
void DMA_SetMinorLoopDestOffest(DMA_Channel_t channel, int16_t offest)
{
    dmaRegPtr->DMA_CH_CONFIG[channel].DMA_AOFF.DAOFF = offest;
}

/**
 * @brief      Set dma source address offset after a major loop done Function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  offest: dma source address offset after a major loop done
 *
 * @return none.
 *
 */
void DMA_SetMajorLoopSrcOffest(DMA_Channel_t channel, int16_t offest)
{
    dmaRegPtr->DMA_CH_CONFIG[channel].DMA_MLAOFF.MLSAOFF = offest;
}

/**
 * @brief      Set dma destination address offset after a major loop done Function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  offest: dma destination address offset after a major loop done
 *
 * @return none.
 *
 */
void DMA_SetMajorLoopDestOffest(DMA_Channel_t channel, int16_t offest)
{
    dmaRegPtr->DMA_CH_CONFIG[channel].DMA_MLAOFF.MLDAOFF = offest;
}

/**
 * @brief      Set total number of minor loop in a major loop Function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  num: number of minor loop in a major loop
 *
 * @return none.
 *
 */
void DMA_SetMinorLoopNum(DMA_Channel_t channel, uint16_t num)
{
    dmaRegPtr->DMA_CH_CONFIG[channel].DMA_ITER.MLITER = (uint16_t)(num & 0x7FFFU);
}

/**
 * @brief      Get total number of minor loop in one major loop Function
 *
 * @param[in]  channel: dma channel id
 *
 * @return number of minor loop in a major loop.
 *
 */
uint16_t DMA_GetMinorLoopNum(DMA_Channel_t channel)
{
    return ((uint16_t)dmaRegPtr->DMA_CH_CONFIG[channel].DMA_ITER.MLITER);
}

/**
 * @brief      Get number of minor loop that not finished in one major loop Function
 *
 * @param[in]  channel: dma channel id
 *
 * @return number of rest minor loop in a major loop.
 *
 */
uint16_t DMA_GetRestMinorLoopNum(DMA_Channel_t channel)
{
    return ((uint16_t)dmaRegPtr->DMA_CH_CONFIG[channel].DMA_ITER.MLSTA);
}

/**
 * @brief      Set dma source transfer size Function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  size: dma source transfer size
 *
 * @return none.
 *
 */
void DMA_SetSrcTransferSize(DMA_Channel_t channel, DMA_TransferSize_t size)
{
    dmaRegPtr->DMA_CH_CONFIG[channel].DMA_CS.SSIZE = (uint32_t)size;
}

/**
 * @brief      Set dma destination transfer size Function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  size: dma destination transfer size
 *
 * @return none.
 *
 */
void DMA_SetDestTransferSize(DMA_Channel_t channel, DMA_TransferSize_t size)
{
    dmaRegPtr->DMA_CH_CONFIG[channel].DMA_CS.DSIZE = (uint32_t)size;
}

/**
 * @brief      Set dma transfer num of bytes in a minor loop Function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  num: dma transfer num of bytes in a minor loop
 *
 * @return none.
 *
 */
void DMA_SetTransferByteNum(DMA_Channel_t channel, uint32_t num)
{
    dmaRegPtr->DMA_CH_CONFIG[channel].DMA_NUM.NUM = num;
}

/**
 * @brief      Disables/enables the DMA request after the transfer complete Function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  cmd: disable request after done
 *                  - ENABLE: disables the DMA request after the transfer complete
 *                  - DISABLE: enables the DMA request after the transfer complete
 *
 * @return none.
 *
 */
void DMA_SetDisableRequestAfterDone(DMA_Channel_t channel, ControlState_t cmd)
{
    dmaRegPtr->DMA_CH_CONFIG[channel].DMA_CS.REQDIS = (uint32_t)cmd;
}

/**
 * @brief      Software trigger one channel dma transfer Function
 *
 * @param[in]  channel: dma channel id
 *
 * @return none.
 *
 */
void DMA_TriggerChannelStart(DMA_Channel_t channel)
{
    dmaRegPtr->DMA_CH_CONFIG[channel].DMA_CS.START = 1U;
}

/**
 * @brief      Software trigger all channel dma transfer Function
 *
 * @param[in]  none
 *
 * @return none.
 *
 */
void DMA_TriggerAllChannelStart(void)
{
    dmaRegWPtr->DMA_GCC = DMA_GCC_WPEN1_MASK | DMA_GCC_SACSTART_MASK; 
}

/**
 * @brief      Get one channel hardware DMA request status Function
 *
 * @param[in]  channel: dma channel id
 *
 * @return whether a channel hardware DMA request is asserted or not.
 *
 */
FlagStatus_t DMA_GetHwRequestStatus(DMA_Channel_t channel)
{
    return ((FlagStatus_t)((uint32_t)(dmaRegWPtr->DMA_CHRS >> (uint32_t)channel & 0x01U)));
}

/**
 * @brief      Get dma last error status Function
 *
 * @param[in]  error: error type
 *
 * @return whether a dma error is asserted or not.
 *
 */
FlagStatus_t DMA_GetLastErrorStatus(DMA_ERROR_t error)
{
    return ((FlagStatus_t)((uint32_t)(dmaRegWPtr->DMA_ES >> dmaErrorShift[error] & 0x01U)));
}

/**
 * @brief      Get last error channel id Function
 *
 * @param[in]  none
 *
 * @return channel which occur the last error
 *
 */
DMA_Channel_t DMA_GetLastErrorChannel(void)
{
    return ((DMA_Channel_t)dmaRegPtr->DMA_ES.CHEF);
}

/**
 * @brief      Get channel int flag Function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  intType: int type
 *                      - DMA_INT_ERROR: error interrupt
 *                      - DMA_INT_DONE: done interrupt
 *                      - DMA_INT_ALL: all interrupt
 *
 * @return whether a channel int is asserted or not.
 *
 */
IntStatus_t DMA_GetIntStatus(DMA_Channel_t channel, DMA_INT_t intType)
{
    uint32_t retVal;
    
    switch (intType)
    {
        case DMA_INT_ERROR:
            retVal = dmaRegWPtr->DMA_CES >> (uint32_t)channel & 0x01U;
            break;

        case DMA_INT_DONE:
            retVal = dmaRegWPtr->DMA_CIS >> (uint32_t)channel & 0x01U;
            break;

        case DMA_INT_ALL:
            retVal = dmaRegWPtr->DMA_CIS;
            retVal |= dmaRegWPtr->DMA_CES;
            retVal = retVal >> (uint32_t)channel & 0x01U;
            break;
            
        default:
            retVal = 0U;
            break;
    }
    
    return ((IntStatus_t)retVal);
}

/**
 * @brief      Clear channel int flag Function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  intType: int type
 *                      - DMA_INT_ERROR: error interrupt
 *                      - DMA_INT_DONE: done interrupt
 *                      - DMA_INT_ALL: all interrupt
 *
 * @return none.
 *
 */
void DMA_ClearIntStatus(DMA_Channel_t channel, DMA_INT_t intType)
{
    dmaRegWPtr->DMA_GCC = dmaGccWpenMask[intType] | 
                    ((((uint32_t)channel << DMA_GCC_CCES_SHIFT) | 
                       ((uint32_t)channel << DMA_GCC_CCIS_SHIFT)) & 
                      dmaGccClearChannelsMask[intType]);
}

/**
 * @brief      Clear all channels int flag Function
 *
 * @param[in]  intType: int type
 *                      - DMA_INT_ERROR: error interrupt
 *                      - DMA_INT_DONE: done interrupt
 *                      - DMA_INT_ALL: all interrupt
 *
 * @return none.
 *
 */
void DMA_ClearAllChannelsIntStatus(DMA_INT_t intType)
{
    dmaRegWPtr->DMA_GCC = dmaGccWpenMask[intType] | 
                    dmaGccClearAllChannelsMask[intType];
}

/**
 * @brief      Get channel done flag Function
 *
 * @param[in]  channel: dma channel id
 *
 * @return whether a channel done flag is asserted or not.
 *
 */
FlagStatus_t DMA_GetDoneStatus(DMA_Channel_t channel)
{
    return ((FlagStatus_t)dmaRegPtr->DMA_CH_CONFIG[channel].DMA_CS.DONE);
}

/**
 * @brief      Clear channel done flag Function
 *
 * @param[in]  channel: dma channel id
 *
 * @return none.
 *
 */
void DMA_ClearDoneStatus(DMA_Channel_t channel)
{
    dmaRegWPtr->DMA_GCC = DMA_GCC_WPEN0_MASK | (uint32_t)channel;
}

/**
 * @brief      Clear all channels done flag Function
 *
 * @param[in]  none
 *
 * @return none.
 *
 */
void DMA_ClearAllChannelsDoneStatus(void)
{
    dmaRegWPtr->DMA_GCC = DMA_GCC_WPEN0_MASK | DMA_GCC_CACDONE_MASK;
}

/**
 * @brief      Get channel busy status Function
 *
 * @param[in]  channel: dma channel id
 *
 * @return whether a channel is busy or not.
 *
 */
FlagStatus_t DMA_GetChannelBusyStatus(DMA_Channel_t channel)
{
    return ((FlagStatus_t)dmaRegPtr->DMA_CH_CONFIG[channel].DMA_CS.BUSY);
}

/**
 * @brief      Set channel int mask Function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  intType: int type
 *                      - DMA_INT_ERROR: error interrupt
 *                      - DMA_INT_DONE: done interrupt
 *                      - DMA_INT_ALL: all interrupt
 * @param[in]  intMask: int mask
 *
 * @return none.
 *
 */
void DMA_IntMask(DMA_Channel_t channel, DMA_INT_t intType, IntMask_t intMask)
{
    uint32_t regValue;
    
    switch (intType)
    {
        case DMA_INT_ERROR:
            regValue = dmaRegWPtr->DMA_EIE;
            regValue &= ~dmaChannelMask[channel];
            regValue |= DMA_MASK_CONVERT_ENABLE(intMask) << (uint32_t)channel;
            dmaRegWPtr->DMA_EIE = regValue;
            break;

        case DMA_INT_DONE:
            dmaRegPtr->DMA_CH_CONFIG[channel].DMA_CS.INTE = DMA_MASK_CONVERT_ENABLE(intMask);
            break;

        case DMA_INT_ALL:
            regValue = dmaRegWPtr->DMA_EIE;
            regValue &= ~dmaChannelMask[channel];
            regValue |= DMA_MASK_CONVERT_ENABLE(intMask) << (uint32_t)channel;
            dmaRegWPtr->DMA_EIE = regValue;
            dmaRegPtr->DMA_CH_CONFIG[channel].DMA_CS.INTE = DMA_MASK_CONVERT_ENABLE(intMask);
            break;
            
        default:
            /*Do nothing*/
            break;
    }
}

/**
 * @brief      Install callback function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  intType: select interrrupt type
 *                      - DMA_INT_ERROR: error interrupt
 *                      - DMA_INT_DONE: done interrupt
 * @param[in]  cbFun: indicate callback function
 *
 * @return    none
 *
 */ 
void DMA_InstallCallBackFunc(DMA_Channel_t channel, DMA_INT_t intType, 
                                      isr_cb_t * cbFun)
{
    if(intType < DMA_INT_ALL)
    {
        dmaIsrCb[channel][intType] = cbFun;
    }
}

/**
 * @brief      Dma transfer config Function
 *
 * @param[in]  config:   Pointer to dma transfer configuration structure.
 *
 * @return function execution result
 *
 */
ResultStatus_t DMA_ConfigTransfer(const DMA_TransferConfig_t * config)
{
    ResultStatus_t retFlag = SUCC;
    uint32_t regValue;
    DMA_Channel_t channel = config->channel;
    /*PRQA S 0303 ++*/
    volatile uint32_t * priRegPtr = (volatile uint32_t *)(DMA_PRIORITY_REG_BASEADDR 
                                      + ((uint32_t)channel >> 0x2U) * 4U);
    /*PRQA S 0303 --*/
    
    if ((DMA_GET_UNSIGNED_REMAINDER(config->srcAddr, config->srcTransferSize) 
        != 0U) || 
        (DMA_GET_UNSIGNED_REMAINDER(config->destAddr, config->destTransferSize)
        != 0U))
    {
        retFlag = ERR;
    }

    /*PRQA S 2896 ++*/
    if ((DMA_GET_SIGNED_REMAINDER(config->minorLoopSrcOffset, config->srcTransferSize) 
        != 0U) || 
        (DMA_GET_SIGNED_REMAINDER(config->minorLoopDestOffset, config->destTransferSize)
        != 0U))
    {
        retFlag = ERR;
    }

    if ((DMA_GET_SIGNED_REMAINDER(config->majorLoopSrcOffset, config->srcTransferSize) 
        != 0U) || 
        (DMA_GET_SIGNED_REMAINDER(config->majorLoopDestOffset, config->destTransferSize)
        != 0U))
    {
        retFlag = ERR;
    }
    /*PRQA S 2896 --*/

    if ((DMA_GET_UNSIGNED_REMAINDER(config->transferByteNum, config->srcTransferSize) 
        != 0U) || 
        (DMA_GET_UNSIGNED_REMAINDER(config->transferByteNum, config->destTransferSize)
        != 0U))
    {
        retFlag = ERR;
    }

    if (0U == config->transferByteNum)
    {
        retFlag = ERR;
    }

    if (SUCC == retFlag)
    {
        /* dma channel config */
        dmaMuxRegPtr->DMA_MUX_CH_CFG[channel].SRC_MUX = (uint32_t)config->source;
        dmaMuxRegPtr->DMA_MUX_CH_CFG[channel].ENABLE = 1U;

        regValue = *priRegPtr;
        
        regValue &= ~(DMA_CHANNEL_PRI_MASK << DMA_CHANNEL_PRI_SHIFT(channel));
        regValue |= (uint32_t)config->channelPriority << DMA_CHANNEL_PRI_SHIFT(channel);
            
        regValue &= ~(DMA_CHANNEL_PREEMPT_MASK << DMA_CHANNEL_PREEMPT_SHIFT(channel));
        regValue |= (uint32_t)config->channelPreempt << DMA_CHANNEL_PREEMPT_SHIFT(channel);
        
        *priRegPtr = regValue;

        dmaRegPtr->DMA_CH_CONFIG[channel].DMA_CS.INTE = DMA_MASK_CONVERT_ENABLE(config->doneIntMask);
        dmaRegWPtr->DMA_EIE &= ~dmaChannelMask[channel];
        dmaRegWPtr->DMA_EIE |= DMA_MASK_CONVERT_ENABLE(config->errorIntMask) << (uint32_t)channel;

        /* transfer config */
        dmaRegPtr->DMA_CH_CONFIG[channel].DMA_SADDR.SADDR = config->srcAddr;
        dmaRegPtr->DMA_CH_CONFIG[channel].DMA_DADDR.DADDR = config->destAddr;

        dmaRegPtr->DMA_CH_CONFIG[channel].DMA_AOFF.SAOFF = config->minorLoopSrcOffset;
        dmaRegPtr->DMA_CH_CONFIG[channel].DMA_AOFF.DAOFF = config->minorLoopDestOffset;

        dmaRegPtr->DMA_CH_CONFIG[channel].DMA_CS.SSIZE = (uint32_t)config->srcTransferSize;
        dmaRegPtr->DMA_CH_CONFIG[channel].DMA_CS.DSIZE = (uint32_t)config->destTransferSize;

        dmaRegPtr->DMA_CH_CONFIG[channel].DMA_NUM.NUM = config->transferByteNum;

        dmaRegPtr->DMA_CH_CONFIG[channel].DMA_MLAOFF.MLSAOFF = config->majorLoopSrcOffset;
        dmaRegPtr->DMA_CH_CONFIG[channel].DMA_MLAOFF.MLDAOFF = config->majorLoopDestOffset;

        dmaRegPtr->DMA_CH_CONFIG[channel].DMA_ITER.MLITER = (uint16_t)(config->minorLoopNum & 0x7FFFU);
        
        dmaRegPtr->DMA_CH_CONFIG[channel].DMA_CS.REQDIS = (uint32_t)config->disableRequestAfterDoneCmd;
    }

    return retFlag;
}

/**
 * @brief      DMA error interrupt handle
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
static void DMA_ErrorIntHandler(void)
{
    uint32_t status;
    uint32_t loop;
    
    status = dmaRegWPtr->DMA_CES;
    status &= dmaRegWPtr->DMA_EIE;

    /* clear all channel error status*/
    /* DMA->DMA_GCC.WORDVAL = DMA_GCC_WPEN2_MASK | DMA_GCC_CACES_MASK; */
    
    for (loop = (uint32_t)DMA_CHANNEL0; loop < DMA_CHANNEL_NUM; loop++)
    {
        if ((status & dmaChannelMask[loop]) != 0U)
        {
            if(dmaIsrCb[loop][DMA_INT_ERROR] != NULL)
            {
                dmaIsrCb[loop][DMA_INT_ERROR]();
            }
            else
            {
                dmaRegWPtr->DMA_EIE &= ~dmaChannelMask[loop];
            }
                
            dmaRegWPtr->DMA_GCC = DMA_GCC_WPEN2_MASK | 
                                      (loop << DMA_GCC_CCES_SHIFT);
        }
    }
}

/**
 * @brief      DMA done interrupt handle
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
static void DMA_DoneIntHandler(uint32_t channelNum)
{
    uint32_t status;
    uint32_t loop;
    
    status = dmaRegWPtr->DMA_CIS;

    /* clear all channel done flag and done interrupt flag*/
    /*
    DMA->DMA_GCC.WORDVAL = DMA_GCC_WPEN03_MASK | DMA_GCC_CACIS_MASK | 
                           DMA_GCC_CACDONE_MASK;
    */

    for (loop = (uint32_t)(channelNum - 4U); loop < channelNum; loop++)
    {
        if ((status & dmaChannelMask[loop]) != 0U) 
        {
            if(dmaIsrCb[loop][DMA_INT_DONE] != NULL)
            {
                dmaIsrCb[loop][DMA_INT_DONE]();
            }
            else
            {
                dmaRegPtr->DMA_CH_CONFIG[loop].DMA_CS.INTE = 0U;
            }

            dmaRegWPtr->DMA_GCC = DMA_GCC_WPEN03_MASK | 
                                      (loop << DMA_GCC_CCIS_SHIFT) | loop ;
        }
    }
}

/**
 * @brief  DMA channel 0-3 interrupt function
 *
 * @param  none
 *
 * @return none
 *
 */
void DMA0TO3_DriverIRQHandler(void)
{
    DMA_DoneIntHandler(DMA0TO3_NUM);
}

/**
 * @brief  DMA channel 4-7 interrupt function
 *
 * @param  none
 *
 * @return none
 *
 */
void DMA4TO7_DriverIRQHandler(void)
{
    DMA_DoneIntHandler(DMA4TO7_NUM);
}

/**
 * @brief  DMA channel 8-11 interrupt function
 *
 * @param  none
 *
 * @return none
 *
 */
void DMA8TO11_DriverIRQHandler(void)
{
    DMA_DoneIntHandler(DMA8TO11_NUM);
}

/**
 * @brief  DMA channel 12-15 interrupt function
 *
 * @param  none
 *
 * @return none
 *
 */
void DMA12TO15_DriverIRQHandler(void)
{
    DMA_DoneIntHandler(DMA12TO15_NUM);
}

/**
 * @brief  DMA error interrupt function
 *
 * @param  none
 *
 * @return none
 *
 */
void DMAERR_DriverIRQHandler(void)
{
    DMA_ErrorIntHandler();
}

/** @} end of group DMA_Public_Functions */

/** @} end of group DMA driver modules */

/** @} end of group Z20K11XM_Peripheral_Driver */

