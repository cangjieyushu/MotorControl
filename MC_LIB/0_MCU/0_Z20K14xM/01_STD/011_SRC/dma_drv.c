/**************************************************************************************************/
/**
 * @file     dma_drv.c
 * @brief    DMA module driver file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#include "dma_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
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

#define DMAMUX_SOURCE_MASK          (0x0000007FU)                                            /*!< dma mux input source mask */
#define DMAMUX_SWSOURCE_SHIFT       (7U)                                                     /*!< dma mux software trigger shift */

#define DMA_CHANNEL0_MASK           (0x00000001U)                                            /*!< dma channel 0 mask */
#define DMA_CHANNEL1_MASK           (0x00000002U)                                            /*!< dma channel 1 mask */
#define DMA_CHANNEL2_MASK           (0x00000004U)                                            /*!< dma channel 2 mask */
#define DMA_CHANNEL3_MASK           (0x00000008U)                                            /*!< dma channel 3 mask */
#define DMA_CHANNEL4_MASK           (0x00000010U)                                            /*!< dma channel 4 mask */
#define DMA_CHANNEL5_MASK           (0x00000020U)                                            /*!< dma channel 5 mask */
#define DMA_CHANNEL6_MASK           (0x00000040U)                                            /*!< dma channel 6 mask */
#define DMA_CHANNEL7_MASK           (0x00000080U)                                            /*!< dma channel 7 mask */
#define DMA_CHANNEL8_MASK           (0x00000100U)                                            /*!< dma channel 8 mask */
#define DMA_CHANNEL9_MASK           (0x00000200U)                                            /*!< dma channel 9 mask */
#define DMA_CHANNEL10_MASK          (0x00000400U)                                            /*!< dma channel 10 mask */
#define DMA_CHANNEL11_MASK          (0x00000800U)                                            /*!< dma channel 11 mask */
#define DMA_CHANNEL12_MASK          (0x00001000U)                                            /*!< dma channel 12 mask */
#define DMA_CHANNEL13_MASK          (0x00002000U)                                            /*!< dma channel 13 mask */
#define DMA_CHANNEL14_MASK          (0x00004000U)                                            /*!< dma channel 14 mask */
#define DMA_CHANNEL15_MASK          (0x00008000U)                                            /*!< dma channel 15 mask */
#define DMA_CHANNELALL_MASK         (0x0000FFFFU)                                            /*!< dma all channels mask */

#define DMA_CHANNEL_PRI_MASK        ((uint32_t)0x0000000FU)                                /*!< dma channel priority mask */

/**  
 *  @brief Calculate priority shift of reg via channel
 */
#define DMA_CHANNEL_PRI_SHIFT(x)    ((uint32_t)(24U - (((uint32_t)(x) & 0x03U) << 3U)))

#define DMA_CHANNEL_PREEMPT_MASK    ((uint32_t)0x00000003U)                                /*!< dma channel preempt set mask */

/**  
 *  @brief Calculate preempt shift of reg via channel
 */
#define DMA_CHANNEL_PREEMPT_SHIFT(x) ((uint32_t)(30U - (((uint32_t)(x) & 0x03U) << 3U)))

/**  
 *  @brief Get base address of priority reg
 */
#define DMA_PRIORITY_REG_BASEADDR   ((uint32_t)(&(dmaRegWPtr->DMA_CPRI0)))

#define DMA_ERROR_ALL_MASK           (0x00008000U)                            /*!< dma all error mask */
#define DMA_ERROR_PRIORITY_MASK     (0x00002000U)                            /*!< dma priority error mask */
#define DMA_ERROR_SRCADDR_MASK      (0x00000080U)                            /*!< dma src addr unalign error mask */
#define DMA_ERROR_SRCOFFSET_MASK    (0x00000040U)                            /*!< dma src offset unalign error mask */  
#define DMA_ERROR_DESTADDR_MASK     (0x00000020U)                            /*!< dma dest addr unalign error mask */
#define DMA_ERROR_DESTOFFSET_MASK   (0x00000010U)                            /*!< dma dest offset unalign error mask */
#define DMA_ERROR_TRANSFERNUM_MASK  (0x00000008U)                            /*!< dma number of transfer unalign error mask */
#define DMA_ERROR_SRCBUS_MASK       (0x00000002U)                            /*!< dma src access error mask */
#define DMA_ERROR_DESTBUS_MASK      (0x00000001U)                            /*!< dma dest access error mask */

#define DMA_ERROR_ALL_SHIFT          (15U)                                    /*!< dma all error shift */
#define DMA_ERROR_PRIORITY_SHIFT    (13U)                                    /*!< dma priority error shift */
#define DMA_ERROR_SRCADDR_SHIFT     (7U)                                     /*!< dma src addr unalign error shift */
#define DMA_ERROR_SRCOFFSET_SHIFT   (6U)                                     /*!< dma src offset unalign error shift */
#define DMA_ERROR_DESTADDR_SHIFT    (5U)                                     /*!< dma dest addr unalign error shift */
#define DMA_ERROR_DESTOFFSET_SHIFT  (4U)                                     /*!< dma dest offset unalign error shift */
#define DMA_ERROR_TRANSFERNUM_SHIFT (3U)                                     /*!< dma number of transfer unalign error shift */
#define DMA_ERROR_SRCBUS_SHIFT       (1U)                                     /*!< dma src access error shift */
#define DMA_ERROR_DESTBUS_SHIFT      (0U)                                     /*!< dma dest access error shift */

/**  
 *  @brief Calculate set value of mask control
 */
#define DMA_MASK_CONVERT_ENABLE(x)  (((uint32_t)(x) + 1U) & 0x1U)

#define DMA_GCC_WPEN0_MASK          (0x80808000U)                           /*!< WPEN0 of global channel control reg mask */
#define DMA_GCC_WPEN1_MASK          (0x80800080U)                           /*!< WPEN1 of global channel control reg mask */
#define DMA_GCC_WPEN2_MASK          (0x80008080U)                           /*!< WPEN2 of global channel control reg mask */
#define DMA_GCC_WPEN3_MASK          (0x00808080U)                           /*!< WPEN3 of global channel control reg mask */
#define DMA_GCC_WPEN03_MASK         (0x00808000U)                           /*!< WPEN0&3 of global channel control reg mask */
#define DMA_GCC_WPEN23_MASK         (0x00008080U)                           /*!< WPEN2&3 of global channel control reg mask */
#define DMA_GCC_CACIS_MASK          (0x40000000U)                           /*!< CACIS of global channel control reg mask */
#define DMA_GCC_CACES_MASK          (0x00400000U)                           /*!< CACES of global channel control reg mask */
#define DMA_GCC_SACSTART_MASK       (0x00004000U)                           /*!< SACSTART of global channel control reg mask */
#define DMA_GCC_CACDONE_MASK        (0x00000040U)                           /*!< CACDONE of global channel control reg mask */
#define DMA_GCC_CACIES_MASK         (0x40400000U)                           /*!< CACIS&CACES of global channel control reg mask */
#define DMA_GCC_CCIS_MASK           (0x0F000000U)                           /*!< CCIS of global channel control reg mask */
#define DMA_GCC_CCES_MASK           (0x000F0000U)                           /*!< CCES of global channel control reg mask */
#define DMA_GCC_SCSTART_MASK        (0x00000F00U)                           /*!< SCSTART of global channel control reg mask */
#define DMA_GCC_CCDONE_MASK         (0x0000000FU)                           /*!< CCDONE of global channel control reg mask */
#define DMA_GCC_CCIES_MASK          (0x0F0F0000U)                           /*!< CCIS&CCES of global channel control reg mask */
#define DMA_GCC_CCDONE_SHIFT        (0U)                                    /*!< CCDONE of global channel control reg shift */
#define DMA_GCC_CCES_SHIFT          (16U)                                   /*!< CCES of global channel control reg shift */
#define DMA_GCC_CCIS_SHIFT          (24U)                                   /*!< CCIS of global channel control reg shift */

#define DMA_CHANNEL_NUM             (16U)                                   /*!< max number of dma channels */

#define DMA_WRITE_TIMEOUT           (100U)

#define DMA_SADDR_OFFSET            (0U)
#define DMA_SADDR_WIDTH             (32U)
#define DMA_DADDR_OFFSET            (0U)
#define DMA_DADDR_WIDTH             (32U)
#define DMA_SAOFF_OFFSET            (0U)
#define DMA_SAOFF_WIDTH             (16U)
#define DMA_DAOFF_OFFSET            (16U)
#define DMA_DAOFF_WIDTH             (16U)
#define DMA_MLSAOFF_OFFSET          (0U)
#define DMA_MLSAOFF_WIDTH           (16U)
#define DMA_MLDAOFF_OFFSET          (16U)
#define DMA_MLDAOFF_WIDTH           (16U)
#define DMA_NUM_OFFSET              (0U)
#define DMA_NUM_WIDTH               (32U)
#define DMA_MLITER_OFFSET           (0U)
#define DMA_MLITER_WIDTH            (16U)
#define DMA_INTE_OFFSET             (1U)
#define DMA_INTE_WIDTH              (1U)
#define DMA_REQDIS_OFFSET           (3U)
#define DMA_REQDIS_WIDTH            (1U)
#define DMA_DSIZE_OFFSET            (16U)
#define DMA_DSIZE_WIDTH             (2U)
#define DMA_SSIZE_OFFSET            (24U)
#define DMA_SSIZE_WIDTH             (2U)
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

void DMA_Ch0_DriverIRQHandler(void);
void DMA_Ch1_DriverIRQHandler(void);
void DMA_Ch2_DriverIRQHandler(void);
void DMA_Ch3_DriverIRQHandler(void);
void DMA_Ch4_DriverIRQHandler(void);
void DMA_Ch5_DriverIRQHandler(void);
void DMA_Ch6_DriverIRQHandler(void);
void DMA_Ch7_DriverIRQHandler(void);
void DMA_Ch8_DriverIRQHandler(void);
void DMA_Ch9_DriverIRQHandler(void);
void DMA_Ch10_DriverIRQHandler(void);
void DMA_Ch11_DriverIRQHandler(void);
void DMA_Ch12_DriverIRQHandler(void);
void DMA_Ch13_DriverIRQHandler(void);
void DMA_Ch14_DriverIRQHandler(void);
void DMA_Ch15_DriverIRQHandler(void);

void DMA_Err_DriverIRQHandler(void);
LOCAL_INLINE ResultStatus_t DMA_WriteRegister(volatile uint32_t * regAddr, uint32_t bitOffset,
                                               uint32_t bitWidth, uint32_t Value);
/** @} end of group DMA_Private_FunctionDeclaration */

/** @defgroup DMA_Private_Functions
 *  @{
 */
/**
 * @brief      Dma error interrupt handle
 *
 * @param[in]  none
 *
 * @return none
 *
 */ 
static void DMA_ErrorIntHandler(void)
{
    uint32_t status;
    uint32_t loop;
    
    status = dmaRegWPtr->DMA_CES;
    status &= dmaRegWPtr->DMA_EIE;
    
    for (loop = (uint32_t)DMA_CHANNEL0; loop < DMA_CHANNEL_NUM; loop++)
    {
        if ((status & dmaChannelMask[loop]) != 0U)
        {
            dmaRegWPtr->DMA_GCC = DMA_GCC_WPEN2_MASK | 
                                  (loop << DMA_GCC_CCES_SHIFT);
            
            if(dmaIsrCb[loop][DMA_INT_ERROR] != NULL)
            {
                dmaIsrCb[loop][DMA_INT_ERROR]();
            }
            else
            {
                dmaRegWPtr->DMA_EIE &= ~dmaChannelMask[loop];
            }
        }
    }
}

/**
 * @brief      Dma done interrupt handle
 *
 * @param[in]  channel: dma channel id
 *
 * @return none
 *
 */
static void DMA_DoneIntHandler(DMA_Channel_t channel)
{
    uint32_t status;
    
    status = dmaRegWPtr->DMA_CIS;

    if ((status & dmaChannelMask[channel]) != 0U) 
    {
        dmaRegWPtr->DMA_GCC = DMA_GCC_WPEN03_MASK | 
                              ((uint32_t)channel << DMA_GCC_CCIS_SHIFT) | (uint32_t)channel;
        
        if(dmaIsrCb[channel][DMA_INT_DONE] != NULL)
        {
            dmaIsrCb[channel][DMA_INT_DONE]();
        }
        else
        {
            (void)DMA_WriteRegister(&dmaRegWPtr->DMA_CH_CONFIG[channel].DMA_CS,
                DMA_INTE_OFFSET, DMA_INTE_WIDTH, 0U);
        }
    }
}

/**
 * @brief Loop write register until written successfully. DMA channel related registers cannot be
 *  written while any DMA channel is transferring data, which is designed in Z20K14xMC DMA hardware.
 *  This function is a workaround to avoid unexpected register write failures. 
 * @param[in] regAddr: Register address to write.
 * @param[in] bitOffset: Register bit offset to write based on register address. range [0,31].
 * @param[in] bitWidth: Bit width to write based on register offset. bitWidth + bitOffset <= 32.
 * @param[in] Value: Target value to be written, should be within "bitWidth" bit width.
 * 
 * @return    ResultStatus_t: the write operation result
 */
LOCAL_INLINE ResultStatus_t DMA_WriteRegister(volatile uint32_t * regAddr, uint32_t bitOffset,
                                               uint32_t bitWidth, uint32_t Value)
{
    uint32_t regValue = 0U;
    uint32_t regMask = 0U;
    uint32_t regValueMasked = 0U;
    uint32_t Counter = 0U;
    ResultStatus_t retVal = SUCC;

    regValue = *regAddr;
    regMask = ((1UL << bitWidth) - 1UL) << bitOffset;
    regValue &= (~regMask);
    regValue |= ((Value & ((1UL << bitWidth) - 1UL)) << bitOffset);   
    *regAddr = regValue;
    regValueMasked = regValue & regMask;
    /* Loop write until success */
    while (((*regAddr) & regMask) != regValueMasked)
    {
        *regAddr = regValue;
        if (Counter > DMA_WRITE_TIMEOUT)
        {
            retVal = ERR;
            break;
        }
        Counter++;
    }
    return retVal;
}


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
    dmaMuxRegPtr->DMA_MUX_CH_CFG[outChannel].SRC_MUX = (uint32_t)questSource & 
                                                       DMAMUX_SOURCE_MASK;
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
 * @param[in]  configPtr:     Pointer to a DMA configuration structure.
 *
 * @return none
 *
 */
void DMA_Init(const DMA_Config_t * configPtr)
{
    dmaRegPtr->DMA_CONF.HOEE = (uint32_t)configPtr->dmaErrorBehavior;
    dmaRegPtr->DMA_CONF.DBGE = (uint32_t)configPtr->dmaDebugBehavior;
    dmaRegPtr->DMA_CONF.RRCAE = (uint32_t)configPtr->dmaPriorityArbitration;
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
 * @param[in]  address: dma transfer source address
 *
 * @return none.
 *
 */
void DMA_SetSrcAddr(DMA_Channel_t channel, uint32_t address)
{
    (void)DMA_WriteRegister(&dmaRegWPtr->DMA_CH_CONFIG[channel].DMA_SADDR,
        DMA_SADDR_OFFSET, DMA_SADDR_WIDTH, address);    
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
    (void)DMA_WriteRegister(&dmaRegWPtr->DMA_CH_CONFIG[channel].DMA_DADDR,
        DMA_DADDR_OFFSET, DMA_DADDR_WIDTH, address);
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
 * @param[in]  offset: dma source address offset in minor loop
 *
 * @return none.
 *
 */
void DMA_SetMinorLoopSrcOffset(DMA_Channel_t channel, int16_t offset)
{
    (void)DMA_WriteRegister(&dmaRegWPtr->DMA_CH_CONFIG[channel].DMA_AOFF,
        DMA_SAOFF_OFFSET, DMA_SAOFF_WIDTH, (uint32_t)offset);    
}

/**
 * @brief      Set dma destination address offset in minor loop Function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  offset: dma destination address offset in minor loop
 *
 * @return none.
 *
 */
void DMA_SetMinorLoopDestOffset(DMA_Channel_t channel, int16_t offset)
{
    (void)DMA_WriteRegister(&dmaRegWPtr->DMA_CH_CONFIG[channel].DMA_AOFF,
        DMA_DAOFF_OFFSET, DMA_DAOFF_WIDTH, (uint32_t)offset);
}

/**
 * @brief      Set dma source address offset after a major loop done Function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  offset: dma source address offset after a major loop done
 *
 * @return none.
 *
 */
void DMA_SetMajorLoopSrcOffset(DMA_Channel_t channel, int16_t offset)
{
    (void)DMA_WriteRegister(&dmaRegWPtr->DMA_CH_CONFIG[channel].DMA_MLAOFF,
        DMA_MLSAOFF_OFFSET, DMA_MLSAOFF_WIDTH, (uint32_t)offset);
}

/**
 * @brief      Set dma destination address offset after a major loop done Function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  offset: dma destination address offset after a major loop done
 *
 * @return none.
 *
 */
void DMA_SetMajorLoopDestOffset(DMA_Channel_t channel, int16_t offset)
{
    (void)DMA_WriteRegister(&dmaRegWPtr->DMA_CH_CONFIG[channel].DMA_MLAOFF,
        DMA_MLDAOFF_OFFSET, DMA_MLDAOFF_WIDTH, (uint32_t)offset);
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
    (void)DMA_WriteRegister(&dmaRegWPtr->DMA_CH_CONFIG[channel].DMA_ITER,
        DMA_MLITER_OFFSET, DMA_MLITER_WIDTH, (uint32_t)num);
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
void DMA_SetSrcTransferSize(DMA_Channel_t channel, 
                                     DMA_TransferSize_t size)
{
    (void)DMA_WriteRegister(&dmaRegWPtr->DMA_CH_CONFIG[channel].DMA_CS,
        DMA_SSIZE_OFFSET, DMA_SSIZE_WIDTH, (uint32_t)size);
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
void DMA_SetDestTransferSize(DMA_Channel_t channel, 
                                      DMA_TransferSize_t size)
{
    (void)DMA_WriteRegister(&dmaRegWPtr->DMA_CH_CONFIG[channel].DMA_CS,
        DMA_DSIZE_OFFSET, DMA_DSIZE_WIDTH, (uint32_t)size);
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
    (void)DMA_WriteRegister(&dmaRegWPtr->DMA_CH_CONFIG[channel].DMA_NUM,
        DMA_NUM_OFFSET, DMA_NUM_WIDTH, num);
}

/**
 * @brief      Disables/Enables the DMA request after the transfer complete Function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  cmd: disable request after done
 *                  - ENABLE: disables the DMA request after the transfer complete
 *                  - DISABLE: enables the DMA request after the transfer complete
 *
 * @return none.
 *
 */
void DMA_SetDisableRequestAfterDone(DMA_Channel_t channel, 
                                                ControlState_t cmd)
{
    (void)DMA_WriteRegister(&dmaRegWPtr->DMA_CH_CONFIG[channel].DMA_CS,
        DMA_REQDIS_OFFSET, DMA_REQDIS_WIDTH, (uint32_t)cmd);
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
FlagStatus_t DMA_GetLastErrorStatus(DMA_Error_t error)
{
    return ((FlagStatus_t)((uint32_t)(dmaRegWPtr->DMA_ES >> 
                                       dmaErrorShift[error] & 0x01U)));
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
IntStatus_t DMA_GetIntStatus(DMA_Channel_t channel, DMA_Int_t intType)
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
void DMA_ClearIntStatus(DMA_Channel_t channel, DMA_Int_t intType)
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
void DMA_ClearAllChannelsIntStatus(DMA_Int_t intType)
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
void DMA_IntMask(DMA_Channel_t channel, DMA_Int_t intType, IntMask_t intMask)
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
            (void)DMA_WriteRegister(&dmaRegWPtr->DMA_CH_CONFIG[channel].DMA_CS,
                DMA_INTE_OFFSET, DMA_INTE_WIDTH, DMA_MASK_CONVERT_ENABLE(intMask));
            break;

        case DMA_INT_ALL:
            regValue = dmaRegWPtr->DMA_EIE;
            regValue &= ~dmaChannelMask[channel];
            regValue |= DMA_MASK_CONVERT_ENABLE(intMask) << (uint32_t)channel;
            dmaRegWPtr->DMA_EIE = regValue;
            (void)DMA_WriteRegister(&dmaRegWPtr->DMA_CH_CONFIG[channel].DMA_CS,
                DMA_INTE_OFFSET, DMA_INTE_WIDTH, DMA_MASK_CONVERT_ENABLE(intMask));
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
void DMA_InstallCallBackFunc(DMA_Channel_t channel, DMA_Int_t intType, 
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
 * When peripheral use DMA to transfer data, unexpected data transfer may be 
 * triggered due to defect in the handshake mechanism between DMA and the 
 * peripheral, resulting in invalid data obtained from Rx channel or overflow of
 *  sending data in Tx channel. In order to avoid unexpected dma request, some 
 * configurations are suggested: for peripheral Tx channel using DMA, the 
 * transfer byte number is suggested to be set as the same with the destination
 * data transfer size; for peripheral Rx channel using DMA, the transfer byte
 * number is suggested to be set as double of the source data transfer size. 
 * For more details can be seen in chapter 3.2 of Z20K14xM_ES_V1.2. 
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
    /*PRQA S 2896 --*/

    /*PRQA S 2896 ++*/
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
        dmaMuxRegPtr->DMA_MUX_CH_CFG[channel].SRC_MUX = (uint32_t)config->source & 
                                                         DMAMUX_SOURCE_MASK;
        if (DMA_REQ_SOFTWARE != config->source)
        {
            dmaMuxRegPtr->DMA_MUX_CH_CFG[channel].ENABLE = 1U;
        }
        else
        {
            dmaMuxRegPtr->DMA_MUX_CH_CFG[channel].ENABLE = 0U;
        }

        regValue = *priRegPtr;
        
        regValue &= ~(DMA_CHANNEL_PRI_MASK << DMA_CHANNEL_PRI_SHIFT(channel));
        regValue |= (uint32_t)config->channelPriority << DMA_CHANNEL_PRI_SHIFT(channel);
            
        regValue &= ~(DMA_CHANNEL_PREEMPT_MASK << DMA_CHANNEL_PREEMPT_SHIFT(channel));
        regValue |= (uint32_t)config->channelPreempt << DMA_CHANNEL_PREEMPT_SHIFT(channel);
        
        *priRegPtr = regValue;

        /* transfer config */
        (void)DMA_WriteRegister(&dmaRegWPtr->DMA_CH_CONFIG[channel].DMA_SADDR,
            DMA_SADDR_OFFSET, DMA_SADDR_WIDTH, config->srcAddr);

        (void)DMA_WriteRegister(&dmaRegWPtr->DMA_CH_CONFIG[channel].DMA_DADDR,
            DMA_DADDR_OFFSET, DMA_DADDR_WIDTH, config->destAddr);
        /*PRQA S 2897 ++*/
        (void)DMA_WriteRegister(&dmaRegWPtr->DMA_CH_CONFIG[channel].DMA_AOFF,
            DMA_SAOFF_OFFSET, DMA_SAOFF_WIDTH, (uint32_t)config->minorLoopSrcOffset);           

        (void)DMA_WriteRegister(&dmaRegWPtr->DMA_CH_CONFIG[channel].DMA_AOFF,
            DMA_DAOFF_OFFSET, DMA_DAOFF_WIDTH, (uint32_t)config->minorLoopDestOffset);
        /*PRQA S 2897 --*/
        (void)DMA_WriteRegister(&dmaRegWPtr->DMA_CH_CONFIG[channel].DMA_CS,
            DMA_SSIZE_OFFSET, DMA_SSIZE_WIDTH, (uint32_t)config->srcTransferSize);

        (void)DMA_WriteRegister(&dmaRegWPtr->DMA_CH_CONFIG[channel].DMA_CS,
            DMA_DSIZE_OFFSET, DMA_DSIZE_WIDTH, (uint32_t)config->destTransferSize);

        (void)DMA_WriteRegister(&dmaRegWPtr->DMA_CH_CONFIG[channel].DMA_NUM,
            DMA_NUM_OFFSET, DMA_NUM_WIDTH, config->transferByteNum);
        /*PRQA S 2897 ++*/
        (void)DMA_WriteRegister(&dmaRegWPtr->DMA_CH_CONFIG[channel].DMA_MLAOFF,
            DMA_MLSAOFF_OFFSET, DMA_MLSAOFF_WIDTH, (uint32_t)config->majorLoopSrcOffset);

        (void)DMA_WriteRegister(&dmaRegWPtr->DMA_CH_CONFIG[channel].DMA_MLAOFF,
            DMA_MLDAOFF_OFFSET, DMA_MLDAOFF_WIDTH, (uint32_t)config->majorLoopDestOffset);
        /*PRQA S 2897 --*/
        (void)DMA_WriteRegister(&dmaRegWPtr->DMA_CH_CONFIG[channel].DMA_ITER,
            DMA_MLITER_OFFSET, DMA_MLITER_WIDTH, (uint32_t)config->minorLoopNum);
        
        (void)DMA_WriteRegister(&dmaRegWPtr->DMA_CH_CONFIG[channel].DMA_CS,
            DMA_REQDIS_OFFSET, DMA_REQDIS_WIDTH, (uint32_t)config->disableRequestAfterDoneCmd);
    }

    return retFlag;
}

/**
 * @brief      Dma channel 0 interrupt function
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void DMA_Ch0_DriverIRQHandler(void)
{
    DMA_DoneIntHandler(DMA_CHANNEL0);
    COMMON_DSB();
}

/**
 * @brief      Dma channel 1 interrupt function
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void DMA_Ch1_DriverIRQHandler(void)
{
    DMA_DoneIntHandler(DMA_CHANNEL1);
    COMMON_DSB();
}

/**
 * @brief      Dma channel 2 interrupt function
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void DMA_Ch2_DriverIRQHandler(void)
{
    DMA_DoneIntHandler(DMA_CHANNEL2);
    COMMON_DSB();
}

/**
 * @brief      Dma channel 3 interrupt function
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void DMA_Ch3_DriverIRQHandler(void)
{
    DMA_DoneIntHandler(DMA_CHANNEL3);
    COMMON_DSB();
}

/**
 * @brief      Dma channel 4 interrupt function
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void DMA_Ch4_DriverIRQHandler(void)
{
    DMA_DoneIntHandler(DMA_CHANNEL4);
    COMMON_DSB();
}

/**
 * @brief      Dma channel 5 interrupt function
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void DMA_Ch5_DriverIRQHandler(void)
{
    DMA_DoneIntHandler(DMA_CHANNEL5);
    COMMON_DSB();
}

/**
 * @brief      Dma channel 6 interrupt function
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void DMA_Ch6_DriverIRQHandler(void)
{
    DMA_DoneIntHandler(DMA_CHANNEL6);
    COMMON_DSB();
}

/**
 * @brief      Dma channel 7 interrupt function
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void DMA_Ch7_DriverIRQHandler(void)
{
    DMA_DoneIntHandler(DMA_CHANNEL7);
    COMMON_DSB();
}

/**
 * @brief      Dma channel 8 interrupt function
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void DMA_Ch8_DriverIRQHandler(void)
{
    DMA_DoneIntHandler(DMA_CHANNEL8);
    COMMON_DSB();
}

/**
 * @brief      Dma channel 9 interrupt function
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void DMA_Ch9_DriverIRQHandler(void)
{
    DMA_DoneIntHandler(DMA_CHANNEL9);
    COMMON_DSB();
}

/**
 * @brief      Dma channel 10 interrupt function
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void DMA_Ch10_DriverIRQHandler(void)
{
    DMA_DoneIntHandler(DMA_CHANNEL10);
    COMMON_DSB();
}

/**
 * @brief      Dma channel 11 interrupt function
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void DMA_Ch11_DriverIRQHandler(void)
{
    DMA_DoneIntHandler(DMA_CHANNEL11);
    COMMON_DSB();
}

/**
 * @brief      Dma channel 12 interrupt function
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void DMA_Ch12_DriverIRQHandler(void)
{
    DMA_DoneIntHandler(DMA_CHANNEL12);
    COMMON_DSB();
}

/**
 * @brief      Dma channel 13 interrupt function
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void DMA_Ch13_DriverIRQHandler(void)
{
    DMA_DoneIntHandler(DMA_CHANNEL13);
    COMMON_DSB();
}

/**
 * @brief      Dma channel 14 interrupt function
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void DMA_Ch14_DriverIRQHandler(void)
{
    DMA_DoneIntHandler(DMA_CHANNEL14);
    COMMON_DSB();
}

/**
 * @brief      Dma channel 15 interrupt function
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void DMA_Ch15_DriverIRQHandler(void)
{
    DMA_DoneIntHandler(DMA_CHANNEL15);
    COMMON_DSB();
}

/**
 * @brief      Dma error interrupt function
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void DMA_Err_DriverIRQHandler(void)
{
    DMA_ErrorIntHandler();
    COMMON_DSB();
}

/** @} end of group DMA_Public_Functions */

/** @} end of group DMA driver modules */

/** @} end of group Z20K14XM_Peripheral_Driver */


