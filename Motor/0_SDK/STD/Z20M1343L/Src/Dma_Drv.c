/**************************************************************************************************/
/**
 * @file      : Dma_Drv.c
 * @brief     : DMA module driver file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 * 
 * @copyright : Copyright (C) 2021-2023 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#include "Dma_Drv.h"
#include "Scm_Drv.h"

/** @defgroup PrivateDefinition
 *  @{
 */
/*PRQA S 0303 ++*/
static Reg_Dma_BfType * const Dma_RegBfPtr = (Reg_Dma_BfType *) DMA_BASE_ADDR;                    /*!< DMA Register */
static Reg_Dma_WType * const Dma_RegWPtr = (Reg_Dma_WType *) DMA_BASE_ADDR;                     /*!< DMA Word Register */
/*PRQA S 0303 --*/

#define DMA_CHANNEL0_MASK           (0x00000001U)                                            /*!< dma channel 0 mask */
#define DMA_CHANNEL1_MASK           (0x00000002U)                                            /*!< dma channel 1 mask */
#define DMA_CHANNEL2_MASK           (0x00000004U)                                            /*!< dma channel 2 mask */
#define DMA_CHANNEL3_MASK           (0x00000008U)                                            /*!< dma channel 3 mask */
#define DMA_CHANNELALL_MASK         (0x0000000FU)                                            /*!< dma all channels mask */

#define DMA_CHANNEL_PRI_MASK        ((uint32)0x00000003U)                                /*!< dma channel priority mask */

/**  
 *  @brief Calculate priority shift of reg via channel
 */
#define DMA_CHANNEL_PRI_SHIFT(X)    ((uint32)((uint32)(X) << 3U))

/**  
 *  @brief Get base address of priority reg
 */
#define DMA_PRIORITY_REG_BASEADDR   ((uint32)(&(Dma_RegWPtr->DMA_CPRI0)))

#define DMA_ERROR_ALL_MASK          (0x00008000U)                            /*!< dma all error mask */
#define DMA_ERROR_PRIORITY_MASK     (0x00002000U)                            /*!< dma priority error mask */
#define DMA_ERROR_SRCADDR_MASK      (0x00000080U)                            /*!< dma src addr unalign error mask */
#define DMA_ERROR_SRCOFFSET_MASK    (0x00000040U)                            /*!< dma src offset unalign error mask */  
#define DMA_ERROR_DESTADDR_MASK     (0x00000020U)                            /*!< dma dest addr unalign error mask */
#define DMA_ERROR_DESTOFFSET_MASK   (0x00000010U)                            /*!< dma dest offset unalign error mask */
#define DMA_ERROR_TRANSFERNUM_MASK  (0x00000008U)                            /*!< dma number of transfer unalign error mask */
#define DMA_ERROR_SRCBUS_MASK       (0x00000002U)                            /*!< dma src access error mask */
#define DMA_ERROR_DESTBUS_MASK      (0x00000001U)                            /*!< dma dest access error mask */

#define DMA_ERROR_ALL_SHIFT         (15U)                                    /*!< dma all error shift */
#define DMA_ERROR_PRIORITY_SHIFT    (13U)                                    /*!< dma priority error shift */
#define DMA_ERROR_SRCADDR_SHIFT     (7U)                                     /*!< dma src addr unalign error shift */
#define DMA_ERROR_SRCOFFSET_SHIFT   (6U)                                     /*!< dma src offset unalign error shift */
#define DMA_ERROR_DESTADDR_SHIFT    (5U)                                     /*!< dma dest addr unalign error shift */
#define DMA_ERROR_DESTOFFSET_SHIFT  (4U)                                     /*!< dma dest offset unalign error shift */
#define DMA_ERROR_TRANSFERNUM_SHIFT (3U)                                     /*!< dma number of transfer unalign error shift */
#define DMA_ERROR_SRCBUS_SHIFT      (1U)                                     /*!< dma src access error shift */
#define DMA_ERROR_DESTBUS_SHIFT     (0U)                                     /*!< dma dest access error shift */

/**  
 *  @brief Calculate set value of mask control
 */
#define DMA_MASK_CONVERT_ENABLE(X)  (((uint32)(X) + 1U) & 0x1U)

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
#define DMA_GCC_CCIS_MASK           (0x03000000U)                           /*!< CCIS of global channel control reg mask */
#define DMA_GCC_CCES_MASK           (0x00030000U)                           /*!< CCES of global channel control reg mask */
#define DMA_GCC_SCSTART_MASK        (0x00000F00U)                           /*!< SCSTART of global channel control reg mask */
#define DMA_GCC_CCDONE_MASK         (0x0000000FU)                           /*!< CCDONE of global channel control reg mask */
#define DMA_GCC_CCIES_MASK          (0x03030000U)                           /*!< CCIS&CCES of global channel control reg mask */
#define DMA_GCC_CCDONE_SHIFT        (0U)                                    /*!< CCDONE of global channel control reg shift */
#define DMA_GCC_CCES_SHIFT          (16U)                                   /*!< CCES of global channel control reg shift */
#define DMA_GCC_CCIS_SHIFT          (24U)                                   /*!< CCIS of global channel control reg shift */

#define DMA_CHANNEL_NUM             (4U)                                   /*!< max number of dma channels */
#define DMA_WRITE_TIMEOUT           (100U)

#define DMA_SADDR_OFFSET            (0U)
#define DMA_SADDR_WIDTH             (32U)
#define DMA_DADDR_OFFSET            (0U)
#define DMA_DADDR_WIDTH             (32U)
#define DMA_SAOFF_OFFSET            (0U)
#define DMA_SAOFF_WIDTH             (16U)
#define DMA_DAOFF_OFFSET            (16U)
#define DMA_DAOFF_WIDTH             (16U)
#define DMA_NUM_OFFSET              (0U)
#define DMA_NUM_WIDTH               (32U)
#define DMA_INTE_OFFSET             (1U)
#define DMA_INTE_WIDTH              (1U)
#define DMA_REQDIS_OFFSET           (3U)
#define DMA_REQDIS_WIDTH            (1U)
#define DMA_DSIZE_OFFSET            (24U)
#define DMA_DSIZE_WIDTH             (2U)
#define DMA_SSIZE_OFFSET            (27U)
#define DMA_SSIZE_WIDTH             (2U)
/**  
 *  @brief Calculate whether unsigned number is divided with no remainder
 */
#define DMA_GET_UNSIGNED_REMAINDER(X, Y) ((uint32)(X) & (((uint32)1U << (uint32)(Y)) - 1U))

/**  
 *  @brief Calculate whether signed number is divided with no remainder
 */
#define DMA_GET_SIGNED_REMAINDER(X, Y) ((sint32)(X) >= 0 ? \
                                       ((uint32)(X) & (((uint32)1U << (uint32)(Y)) - 1U)) : \
                                       ((((uint32)(X) - 1U) ^ 0xFFFFFFFFU) & \
                                       (((uint32)1U << (uint32)(Y)) - 1U)))

/** @} end of group PrivateDefinition */


/** @defgroup Private_TypeDefinition
 *  @{
 */

/** @} end of group Private_TypeDefinition*/



/** @defgroup Private_VariableDefinition
 *  @{
 */

/*! @brief dma channel mask array */
static const uint32 DmaChannelMaskTable[] = 
{
    DMA_CHANNEL0_MASK,                       /*!< dma channel 0 mask */
    DMA_CHANNEL1_MASK,                       /*!< dma channel 1 mask */
    DMA_CHANNEL2_MASK,                       /*!< dma channel 2 mask */
    DMA_CHANNEL3_MASK,                       /*!< dma channel 3 mask */
};

/*! @brief dma error shift array */
static const uint32 DmaErrorShiftTable[] = 
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

static const uint32 DmaGccWpenMaskTable[] = 
{
    DMA_GCC_WPEN2_MASK,                      /*!< WPEN2 of global channel control reg mask */
    DMA_GCC_WPEN3_MASK,                      /*!< WPEN3 of global channel control reg mask */
    DMA_GCC_WPEN23_MASK                      /*!< WPEN2&3 of global channel control reg mask */
};
                            
static const uint32 DmaGccClearAllChannelsMaskTable[] = 
{
    DMA_GCC_CACES_MASK,                      /*!< CACES of global channel control reg mask */
    DMA_GCC_CACIS_MASK,                      /*!< CACIS of global channel control reg mask */
    DMA_GCC_CACIES_MASK                      /*!< CACIS&CACES of global channel control reg mask */
};

static const uint32 DmaGccClearChannelsMaskTable[] = 
{
    DMA_GCC_CCES_MASK,                      /*!< CCES of global channel control reg mask */
    DMA_GCC_CCIS_MASK,                      /*!< CCIS of global channel control reg mask */
    DMA_GCC_CCIES_MASK                      /*!< CCIS&CCES of global channel control reg mask */
};

/*! @brief DMA ISR CallBack VECTOR structure */
static Isr_CbFuncType * DmaIsrCallback[DMA_CHANNEL_NUM][DMA_INT_ALL]= 
{
    {NULL_PTR, NULL_PTR},
    {NULL_PTR, NULL_PTR},
    {NULL_PTR, NULL_PTR},
    {NULL_PTR, NULL_PTR}
};

/** @} end of group Private_VariableDefinition */

/** @defgroup Global_VariableDefinition
 *  @{
 */

/** @} end of group Global_VariableDefinition */

/** @defgroup Private_FunctionDeclaration
 *  @{
 */

void Dma_Ch0_DriverIrqHandler(void);
void Dma_Ch1_DriverIrqHandler(void);
void Dma_Ch2_DriverIrqHandler(void);
void Dma_Ch3_DriverIrqHandler(void);
void Dma_Err_DriverIrqHandler(void);

LOCAL_INLINE Common_ResultStatusType Dma_WriteRegister(volatile uint32 * RegAddr, uint32 BitOffset,
                                               uint32 BitWidth, uint32 Value);
/** @} end of group Private_FunctionDeclaration */

/** @defgroup Private_FunctionDefinition
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
static void Dma_ErrorIntHandler(void)
{
    uint32 Status;
    uint32 Loop;
    
    Status = Dma_RegWPtr->DMA_CES;
    Status &= Dma_RegWPtr->DMA_EIE;
    for (Loop = (uint32)DMA_CHANNEL0; Loop < DMA_CHANNEL_NUM; Loop++)
    {
        if ((Status & DmaChannelMaskTable[Loop]) != 0U)
        {
            Dma_RegWPtr->DMA_GCC = DMA_GCC_WPEN2_MASK | 
                                  (Loop << DMA_GCC_CCES_SHIFT);
            
            if(DmaIsrCallback[Loop][DMA_INT_ERROR] != NULL_PTR)
            {
                DmaIsrCallback[Loop][DMA_INT_ERROR]();
            }
            else
            {
                Dma_RegWPtr->DMA_EIE &= ~DmaChannelMaskTable[Loop];
            }
        }
    }
}

/**
 * @brief      Dma done interrupt handle
 *
 * @param[in]  Channel: dma channel id
 *                         - DMA_CHANNEL0
 *                         - DMA_CHANNEL1
 *                         - DMA_CHANNEL2
 *                         - DMA_CHANNEL3
 *
 * @return none
 *
 */
static void Dma_DoneIntHandler(Dma_ChannelType Channel)
{
    uint32 Status;
    
    Status = Dma_RegWPtr->DMA_CIS;
    if ((Status & DmaChannelMaskTable[Channel]) != 0U) 
    {
        Dma_RegWPtr->DMA_GCC = DMA_GCC_WPEN03_MASK | 
                              ((uint32)Channel << DMA_GCC_CCIS_SHIFT) | (uint32)Channel;
        
        if(DmaIsrCallback[Channel][DMA_INT_DONE] != NULL_PTR)
        {
            DmaIsrCallback[Channel][DMA_INT_DONE]();
        }
        else
        {
            (void)Dma_WriteRegister(&Dma_RegWPtr->DMA_CH_CONFIG[Channel].DMA_CS,
                DMA_INTE_OFFSET, DMA_INTE_WIDTH, 0U);
        }
    }
}

/**
 * @brief Loop write register until written successfully. DMA channel related registers cannot be
 *  written while any DMA channel is transferring data, which is designed in Z20M1343L DMA hardware.
 *  This function is a workaround to avoid unexpected register write failures. 
 * @param[in] RegAddr: Register address to write.
 * @param[in] BitOffset: Register bit offset to write based on register address. range [0,31].
 * @param[in] BitWidth: Bit width to write based on register offset. BitWidth + BitOffset <= 32.
 * @param[in] Value: Target value to be written, should be within "BitWidth" bit width.
 * 
 * @return    Common_ResultStatusType: the write operation result
 */
LOCAL_INLINE Common_ResultStatusType Dma_WriteRegister(volatile uint32 * RegAddr, uint32 BitOffset,
                                               uint32 BitWidth, uint32 Value)
{
    uint32 RegValue = 0U;
    uint32 RegMask = 0U;
    uint32 RegValueMasked = 0U;
    uint32 Counter = 0U;
    Common_ResultStatusType RetVal = COMMON_SUCC;

    RegValue = *RegAddr;
    RegMask = ((1UL << BitWidth) - 1UL) << BitOffset;
    RegValue &= (~RegMask);
    RegValue |= ((Value & ((1UL << BitWidth) - 1UL)) << BitOffset);   
    *RegAddr = RegValue;
    RegValueMasked = RegValue & RegMask;
    /* Loop write until success */
    while (((*RegAddr) & RegMask) != RegValueMasked)
    {
        *RegAddr = RegValue;
        if (Counter > DMA_WRITE_TIMEOUT)
        {
            RetVal = COMMON_ERR;
            break;
        }
        Counter++;
    }
    return RetVal;
}
/** @} end of group Private_FunctionDefinition */


/** @defgroup Public_FunctionDefinition
 *  @{
 */

/**
 * @brief      Dma initializes function
 *
 * @param[in]  ConfigPtr:     Pointer to a DMA configuration structure.
 *
 * @return none
 *
 */
void Dma_Init(const Dma_ConfigType * ConfigPtr)
{
    Dma_RegBfPtr->DMA_CONF.HOEE = (uint32)ConfigPtr->DmaErrorBehavior;
    Dma_RegBfPtr->DMA_CONF.DBGE = (uint32)ConfigPtr->DmaDebugBehavior;
}

/**
 * @brief      Get dma busy status function
 *
 * @param[in]  none
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_SET: status set
 * @retval     COMMON_RESET: status not set
 *
 */
Common_FlagStatusType Dma_GetDmaBusyStatus(void)
{
    return ((Common_FlagStatusType)Dma_RegBfPtr->DMA_CONF.BUSY);
}

/**
 * @brief      Halt dma function
 *
 * @param[in]  Cmd: halt control
 *                  - COMMON_ENABLE: stall the dma start a new channels for transfer
 *                  - COMMON_DISABLE: dma is not stall
 *
 * @return none.
 *
 */
void Dma_EnableHalt(Common_ControlStateType Cmd)
{
    Dma_RegBfPtr->DMA_CONF.HALT = (uint32)Cmd;
}

/**
 * @brief      Get dma halt status function
 *
 * @param[in]  none
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_SET: status set
 * @retval     COMMON_RESET: status not set
 *
 */
Common_FlagStatusType Dma_GetHaltStatus(void)
{
    return ((Common_FlagStatusType)Dma_RegBfPtr->DMA_CONF.HALT);
}

/**
 * @brief      Enable dma channel request function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 *
 * @return none.
 *
 */
void Dma_EnableChannelRequest(Dma_ChannelType Channel)
{
    Dma_RegWPtr->DMA_DMAE |= DmaChannelMaskTable[Channel];
}

/**
 * @brief      Disable dma channel request function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 *
 * @return none.
 *
 */
void Dma_DisableChannelRequest(Dma_ChannelType Channel)
{
    Dma_RegWPtr->DMA_DMAE &= ~DmaChannelMaskTable[Channel];
}

/**
 * @brief      Get dma channel request status function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_SET: status set
 * @retval     COMMON_RESET: status not set
 *
 */
Common_FlagStatusType Dma_GetChannelRequestStatus(Dma_ChannelType Channel)
{
    return ((Common_FlagStatusType)((uint32)(Dma_RegWPtr->DMA_DMAE >> (uint32)Channel & 0x01U)));
}

/**
 * @brief      Set dma channel priority function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 * 
 * @param[in]  Priority: dma priority level
 *                              - DMA_CHN_PRIORITY0
 *                              - DMA_CHN_PRIORITY1
 *                              - DMA_CHN_PRIORITY2
 *                              - DMA_CHN_PRIORITY3
 *
 * @return none.
 *
 */
void Dma_SetChannelPriority(Dma_ChannelType Channel, 
                                     Dma_ChannelPriorityType Priority)
{
    uint32 RegValue;
    /*PRQA S 0303 ++*/
    volatile uint32 * PriRegPtr = (volatile uint32 *)(DMA_PRIORITY_REG_BASEADDR); 
    /*PRQA S 0303 --*/ 
    RegValue = *PriRegPtr;
    RegValue &= ~(DMA_CHANNEL_PRI_MASK << DMA_CHANNEL_PRI_SHIFT(Channel));
    RegValue |= (uint32)Priority << DMA_CHANNEL_PRI_SHIFT(Channel);
    *PriRegPtr = RegValue;
}

/**
 * @brief      Get dma channel priority function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 *
 * @return     Dma_ChannelPriorityType
 * @retval     DMA_CHN_PRIORITY0
 * @retval     DMA_CHN_PRIORITY1
 * @retval     DMA_CHN_PRIORITY2
 * @retval     DMA_CHN_PRIORITY3
 *
 */
Dma_ChannelPriorityType Dma_GetChannelPriority(Dma_ChannelType Channel)
{
    /*PRQA S 0303 ++*/
    volatile uint32 * PriRegPtr = (volatile uint32 *)(DMA_PRIORITY_REG_BASEADDR);
    /*PRQA S 0303 --*/
    
    return ((Dma_ChannelPriorityType)((uint32)(*PriRegPtr >> 
            DMA_CHANNEL_PRI_SHIFT(Channel) & DMA_CHANNEL_PRI_MASK)));
}

/**
 * @brief      Set dma source address function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 * @param[in]  Address: dma transfer source address
 *
 * @return none.
 *
 */
void Dma_SetSrcAddr(Dma_ChannelType Channel, uint32 Address)
{
    (void)Dma_WriteRegister(&Dma_RegWPtr->DMA_CH_CONFIG[Channel].DMA_SADDR,
    DMA_SADDR_OFFSET, DMA_SADDR_WIDTH, Address);
}

/**
 * @brief      Get dma source address function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 *
 * @return dma source address.
 *
 */
uint32 Dma_GetSrcAddr(Dma_ChannelType Channel)
{
    return ((uint32)Dma_RegBfPtr->DMA_CH_CONFIG[Channel].DMA_SADDR.SADDR);
}

/**
 * @brief      Set dma destination address function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 * @param[in]  Address: dma transfer destination address
 *
 * @return none.
 *
 */
void Dma_SetDestAddr(Dma_ChannelType Channel, uint32 Address)
{
    (void)Dma_WriteRegister(&Dma_RegWPtr->DMA_CH_CONFIG[Channel].DMA_DADDR,
        DMA_DADDR_OFFSET, DMA_DADDR_WIDTH, Address);
}

/**
 * @brief      Get dma destination address function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 *
 * @return dma destination address.
 *
 */
uint32 Dma_GetDestAddr(Dma_ChannelType Channel)
{
    return ((uint32)Dma_RegBfPtr->DMA_CH_CONFIG[Channel].DMA_DADDR.DADDR);
}

/**
 * @brief      Set dma source address offset in minor loop function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 * @param[in]  Offset: dma source address offset in minor loop
 *
 * @return none.
 *
 */
void Dma_SetMinorLoopSrcOffset(Dma_ChannelType Channel, sint16 Offset)
{
    (void)Dma_WriteRegister(&Dma_RegWPtr->DMA_CH_CONFIG[Channel].DMA_AOFF,
        DMA_SAOFF_OFFSET, DMA_SAOFF_WIDTH, (uint32)Offset);
}

/**
 * @brief      Set dma destination address offset in minor loop function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 * @param[in]  Offset: dma destination address offset in minor loop
 *
 * @return none.
 *
 */
void Dma_SetMinorLoopDestOffset(Dma_ChannelType Channel, sint16 Offset)
{
    (void)Dma_WriteRegister(&Dma_RegWPtr->DMA_CH_CONFIG[Channel].DMA_AOFF,
        DMA_DAOFF_OFFSET, DMA_DAOFF_WIDTH, (uint32)Offset);
}

/**
 * @brief      Set dma source transfer size function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 * @param[in]  Size: dma transfer size
 *                              - DMA_TRANSFER_SIZE_1B
 *                              - DMA_TRANSFER_SIZE_2B
 *                              - DMA_TRANSFER_SIZE_4B
 *
 * @return none.
 *
 */
void Dma_SetSrcTransferSize(Dma_ChannelType Channel, 
                                     Dma_TransferSizeType Size)
{
    (void)Dma_WriteRegister(&Dma_RegWPtr->DMA_CH_CONFIG[Channel].DMA_CS,
        DMA_SSIZE_OFFSET, DMA_SSIZE_WIDTH, (uint32)Size);
}

/**
 * @brief      Set dma destination transfer size function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 * @param[in]  Size: dma transfer size
 *                              - DMA_TRANSFER_SIZE_1B
 *                              - DMA_TRANSFER_SIZE_2B
 *                              - DMA_TRANSFER_SIZE_4B
 *
 * @return none.
 *
 */
void Dma_SetDestTransferSize(Dma_ChannelType Channel, 
                                      Dma_TransferSizeType Size)
{
    (void)Dma_WriteRegister(&Dma_RegWPtr->DMA_CH_CONFIG[Channel].DMA_CS,
        DMA_DSIZE_OFFSET, DMA_DSIZE_WIDTH, (uint32)Size);
}

/**
 * @brief      Set dma transfer num of bytes in a minor loop function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 * @param[in]  Num: dma transfer num of bytes in a minor loop
 *
 * @return none.
 *
 */
void Dma_SetTransferByteNum(Dma_ChannelType Channel, uint32 Num)
{
    (void)Dma_WriteRegister(&Dma_RegWPtr->DMA_CH_CONFIG[Channel].DMA_NUM,
        DMA_NUM_OFFSET, DMA_NUM_WIDTH, Num);
}

/**
 * @brief      Disables/Enables the DMA request after the transfer complete function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 * @param[in]  Cmd: disable request after done
 *                  - COMMON_ENABLE: disables the DMA request after the transfer complete
 *                  - COMMON_DISABLE: enables the DMA request after the transfer complete
 *
 * @return none.
 *
 */
void Dma_SetDisableRequestAfterDone(Dma_ChannelType Channel, 
                                                Common_ControlStateType Cmd)
{
    (void)Dma_WriteRegister(&Dma_RegWPtr->DMA_CH_CONFIG[Channel].DMA_CS,
        DMA_REQDIS_OFFSET, DMA_REQDIS_WIDTH, (uint32)Cmd);
}

/**
 * @brief      Software trigger one channel dma transfer function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 *
 * @return none.
 *
 */
void Dma_TriggerChannelStart(Dma_ChannelType Channel)
{
    Dma_RegBfPtr->DMA_CH_CONFIG[Channel].DMA_CS.START = 1U;
}

/**
 * @brief      Software trigger all channel dma transfer function
 *
 * @param[in]  none
 *
 * @return none.
 *
 */
void Dma_TriggerAllChannelStart(void)
{
    Dma_RegWPtr->DMA_GCC = DMA_GCC_WPEN1_MASK | DMA_GCC_SACSTART_MASK;
}

/**
 * @brief      Get one channel hardware DMA request status function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_SET: status set
 * @retval     COMMON_RESET: status not set
 *
 */
Common_FlagStatusType Dma_GetHwRequestStatus(Dma_ChannelType Channel)
{
    return ((Common_FlagStatusType)((uint32)(Dma_RegWPtr->DMA_CHRS >> (uint32)Channel & 0x01U)));
}

/**
 * @brief      Get dma last error status function
 *
 * @param[in]  Error: error type
 *                              - DMA_ERROR_PRIORITY
 *                              - DMA_ERROR_SRCADDR
 *                              - DMA_ERROR_SRCOFFSET
 *                              - DMA_ERROR_DESTADDR
 *                              - DMA_ERROR_DESTOFFSET
 *                              - DMA_ERROR_TRANSFERNUM
 *                              - DMA_ERROR_SRCBUS
 *                              - DMA_ERROR_DESTBUS
 *                              - DMA_ERROR_ALL
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_SET: status set
 * @retval     COMMON_RESET: status not set
 *
 */
Common_FlagStatusType Dma_GetLastErrorStatus(Dma_ErrorType Error)
{
    return ((Common_FlagStatusType)((uint32)(Dma_RegWPtr->DMA_ES >> 
                                       DmaErrorShiftTable[Error] & 0x01U)));
}

/**
 * @brief      Get last error channel id function
 *
 * @param[in]  none
 *
 * @return     Dma_ChannelType
 * @retval     DMA_CHANNEL0: dma channel 0 error
 * @retval     DMA_CHANNEL1: dma channel 1 error
 * @retval     DMA_CHANNEL2: dma channel 2 error
 * @retval     DMA_CHANNEL3: dma channel 3 error
 *
 */
Dma_ChannelType Dma_GetLastErrorChannel(void)
{
    return ((Dma_ChannelType)Dma_RegBfPtr->DMA_ES.CHEF);
}

/**
 * @brief      Get channel int flag function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 * @param[in]  IntType: int type
 *                      - DMA_INT_ERROR: error interrupt
 *                      - DMA_INT_DONE: done interrupt
 *                      - DMA_INT_ALL: all interrupt
 *
 * @return     Common_IntStatusType
 *                      - COMMON_SET: status set
 *                      - COMMON_RESET: status not set
 *
 */
Common_IntStatusType Dma_GetIntStatus(Dma_ChannelType Channel, Dma_IntType IntType)
{
    uint32 RetVal;
    
    switch (IntType)
    {
        case DMA_INT_ERROR:
            RetVal = Dma_RegWPtr->DMA_CES >> (uint32)Channel & 0x01U;
            break;

        case DMA_INT_DONE:
            RetVal = Dma_RegWPtr->DMA_CIS >> (uint32)Channel & 0x01U;
            break;

        case DMA_INT_ALL:
            RetVal = Dma_RegWPtr->DMA_CIS;
            RetVal |= Dma_RegWPtr->DMA_CES;
            RetVal = RetVal >> (uint32)Channel & 0x01U;
            break;
            
        default:
            RetVal = 0U;
            break;
    }
    
    return ((Common_IntStatusType)RetVal);
}

/**
 * @brief      Clear channel int flag function
 *
 * @param[in]  Channel: dma channel id
 * @param[in]  IntType: int type
 *                      - DMA_INT_ERROR: error interrupt
 *                      - DMA_INT_DONE: done interrupt
 *                      - DMA_INT_ALL: all interrupt
 *
 * @return none.
 *
 */
void Dma_ClearIntStatus(Dma_ChannelType Channel, Dma_IntType IntType)
{
    Dma_RegWPtr->DMA_GCC = DmaGccWpenMaskTable[IntType] | 
                    ((((uint32)Channel << DMA_GCC_CCES_SHIFT) | 
                       ((uint32)Channel << DMA_GCC_CCIS_SHIFT)) & 
                      DmaGccClearChannelsMaskTable[IntType]);
}

/**
 * @brief      Clear all channels int flag function
 *
 * @param[in]  IntType: int type
 *                      - DMA_INT_ERROR: error interrupt
 *                      - DMA_INT_DONE: done interrupt
 *                      - DMA_INT_ALL: all interrupt
 *
 * @return none.
 *
 */
void Dma_ClearAllChannelsIntStatus(Dma_IntType IntType)
{
    Dma_RegWPtr->DMA_GCC = DmaGccWpenMaskTable[IntType] | 
                          DmaGccClearAllChannelsMaskTable[IntType];
}

/**
 * @brief      Get channel done flag function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 *
 * @return     Common_FlagStatusType
 *                              - COMMON_SET: status set
 *                              - COMMON_RESET: status not set
 *
 */
Common_FlagStatusType Dma_GetDoneStatus(Dma_ChannelType Channel)
{
    return ((Common_FlagStatusType)Dma_RegBfPtr->DMA_CH_CONFIG[Channel].DMA_CS.DONE);
}

/**
 * @brief      Clear channel done flag function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 *
 * @return none.
 *
 */
void Dma_ClearDoneStatus(Dma_ChannelType Channel)
{
    Dma_RegWPtr->DMA_GCC = DMA_GCC_WPEN0_MASK | (uint32)Channel;
}

/**
 * @brief      Clear all channels done flag function
 *
 * @param[in]  none
 *
 * @return none.
 *
 */
void Dma_ClearAllChannelsDoneStatus(void)
{
    Dma_RegWPtr->DMA_GCC = DMA_GCC_WPEN0_MASK | DMA_GCC_CACDONE_MASK;
}

/**
 * @brief      Get channel busy status function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 *
 * @return     Common_FlagStatusType
 *                              - COMMON_SET: status set
 *                              - COMMON_RESET: status not set
 *
 */
Common_FlagStatusType Dma_GetChannelBusyStatus(Dma_ChannelType Channel)
{
    return ((Common_FlagStatusType)Dma_RegBfPtr->DMA_CH_CONFIG[Channel].DMA_CS.BUSY);
}

/**
 * @brief      Set channel int mask function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 * @param[in]  IntType: int type
 *                      - DMA_INT_ERROR: error interrupt
 *                      - DMA_INT_DONE: done interrupt
 *                      - DMA_INT_ALL: all interrupt
 * @param[in]  IntMask: int mask
 *                      - COMMON_UNMASK: int unmask
 *                      - COMMON_MASK: int mask
 *
 * @return none.
 *
 */
void Dma_SetIntMask(Dma_ChannelType Channel, Dma_IntType IntType, Common_IntMaskType IntMask)
{
    uint32 RegValue;
    switch (IntType)
    {
        case DMA_INT_ERROR:
            RegValue = Dma_RegWPtr->DMA_EIE;
            RegValue &= ~DmaChannelMaskTable[Channel];
            RegValue |= DMA_MASK_CONVERT_ENABLE(IntMask) << (uint32)Channel;
            Dma_RegWPtr->DMA_EIE = RegValue;
            break;

        case DMA_INT_DONE:
            (void)Dma_WriteRegister(&Dma_RegWPtr->DMA_CH_CONFIG[Channel].DMA_CS,
                DMA_INTE_OFFSET, DMA_INTE_WIDTH, DMA_MASK_CONVERT_ENABLE(IntMask));
            break;

        case DMA_INT_ALL:
            RegValue = Dma_RegWPtr->DMA_EIE;
            RegValue &= ~DmaChannelMaskTable[Channel];
            RegValue |= DMA_MASK_CONVERT_ENABLE(IntMask) << (uint32)Channel;
            Dma_RegWPtr->DMA_EIE = RegValue;
            (void)Dma_WriteRegister(&Dma_RegWPtr->DMA_CH_CONFIG[Channel].DMA_CS,
                DMA_INTE_OFFSET, DMA_INTE_WIDTH, DMA_MASK_CONVERT_ENABLE(IntMask));
            break;
            
        default:
            /*Do nothing*/
            break;
    }
}

/**
 * @brief      Install callback function
 *
 * @param[in]  Channel: dma channel id
 *                              - DMA_CHANNEL0
 *                              - DMA_CHANNEL1
 *                              - DMA_CHANNEL2
 *                              - DMA_CHANNEL3
 * @param[in]  IntType: select interrupt type
 *                      - DMA_INT_ERROR: error interrupt
 *                      - DMA_INT_DONE: done interrupt
 * @param[in]  CbFun: indicate callback function
 *
 * @return    none
 *
 */ 
void Dma_InstallCallBackFunc(Dma_ChannelType Channel, Dma_IntType IntType, 
                                      Isr_CbFuncType * CbFun)
{
    if(IntType < DMA_INT_ALL)
    {
        DmaIsrCallback[Channel][IntType] = CbFun;
    }
}

/**
 * @brief      Dma transfer config function
 *
 * @param[in]  Config:   Pointer to dma transfer configuration structure.
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: command successful excuted
 * @retval     COMMON_ERR: command excution timeout
 *
 */
Common_ResultStatusType Dma_ConfigTransfer(const Dma_TransferConfigType * Config)
{
    Common_ResultStatusType RetFlag = COMMON_SUCC;
    uint32 RegValue;
    Dma_ChannelType Channel = Config->Channel;
    /*PRQA S 0303 ++*/
    volatile uint32 * PriRegPtr = (volatile uint32 *)(DMA_PRIORITY_REG_BASEADDR);
    /*PRQA S 0303 --*/

    if ((DMA_GET_UNSIGNED_REMAINDER(Config->SrcAddr, Config->SrcTransferSize) 
        != 0U) || 
        (DMA_GET_UNSIGNED_REMAINDER(Config->DestAddr, Config->DestTransferSize)
        != 0U))
    {
        RetFlag = COMMON_ERR;
    }

    /*PRQA S 2896 ++*/
    if ((DMA_GET_SIGNED_REMAINDER(Config->MinorLoopSrcOffset, Config->SrcTransferSize) 
        != 0U) || 
        (DMA_GET_SIGNED_REMAINDER(Config->MinorLoopDestOffset, Config->DestTransferSize)
        != 0U))
    {
        RetFlag = COMMON_ERR;
    }
    /*PRQA S 2896 --*/

    if ((DMA_GET_UNSIGNED_REMAINDER(Config->TransferByteNum, Config->SrcTransferSize) 
        != 0U) || 
        (DMA_GET_UNSIGNED_REMAINDER(Config->TransferByteNum, Config->DestTransferSize)
        != 0U))
    {
        RetFlag = COMMON_ERR;
    }

    if (0U == Config->TransferByteNum)
    {
        RetFlag = COMMON_ERR;
    }

    if (COMMON_SUCC == RetFlag)
    {
        /* dma channel config */
        RegValue = *PriRegPtr;
        
        RegValue &= ~(DMA_CHANNEL_PRI_MASK << DMA_CHANNEL_PRI_SHIFT(Channel));
        RegValue |= (uint32)Config->ChannelPriority << DMA_CHANNEL_PRI_SHIFT(Channel);
        
        *PriRegPtr = RegValue;

        /* transfer config */
        (void)Dma_WriteRegister(&Dma_RegWPtr->DMA_CH_CONFIG[Channel].DMA_SADDR,
            DMA_SADDR_OFFSET, DMA_SADDR_WIDTH, Config->SrcAddr);

        (void)Dma_WriteRegister(&Dma_RegWPtr->DMA_CH_CONFIG[Channel].DMA_DADDR,
            DMA_DADDR_OFFSET, DMA_DADDR_WIDTH, Config->DestAddr);
        /*PRQA S 2897 ++*/
        (void)Dma_WriteRegister(&Dma_RegWPtr->DMA_CH_CONFIG[Channel].DMA_AOFF,
            DMA_SAOFF_OFFSET, DMA_SAOFF_WIDTH, (uint32)Config->MinorLoopSrcOffset);        

        (void)Dma_WriteRegister(&Dma_RegWPtr->DMA_CH_CONFIG[Channel].DMA_AOFF,
            DMA_DAOFF_OFFSET, DMA_DAOFF_WIDTH, (uint32)Config->MinorLoopDestOffset); 
        /*PRQA S 2897 --*/
        (void)Dma_WriteRegister(&Dma_RegWPtr->DMA_CH_CONFIG[Channel].DMA_CS,
            DMA_SSIZE_OFFSET, DMA_SSIZE_WIDTH, (uint32)Config->SrcTransferSize);

        (void)Dma_WriteRegister(&Dma_RegWPtr->DMA_CH_CONFIG[Channel].DMA_CS,
            DMA_DSIZE_OFFSET, DMA_DSIZE_WIDTH, (uint32)Config->DestTransferSize);

        (void)Dma_WriteRegister(&Dma_RegWPtr->DMA_CH_CONFIG[Channel].DMA_NUM,
            DMA_NUM_OFFSET, DMA_NUM_WIDTH, Config->TransferByteNum);        

        (void)Dma_WriteRegister(&Dma_RegWPtr->DMA_CH_CONFIG[Channel].DMA_CS,
            DMA_REQDIS_OFFSET, DMA_REQDIS_WIDTH, (uint32)Config->DisableRequestAfterDoneCmd);        
    }
    return RetFlag;
}

/**
 * @brief      Dma channel 0 interrupt function
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void Dma_Ch0_DriverIrqHandler(void)
{
    Dma_DoneIntHandler(DMA_CHANNEL0);
}

/**
 * @brief      Dma channel 1 interrupt function
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void Dma_Ch1_DriverIrqHandler(void)
{
    Dma_DoneIntHandler(DMA_CHANNEL1);
}

/**
 * @brief      Dma channel 2 interrupt function
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void Dma_Ch2_DriverIrqHandler(void)
{
    Dma_DoneIntHandler(DMA_CHANNEL2);
}

/**
 * @brief      Dma channel 3 interrupt function
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void Dma_Ch3_DriverIrqHandler(void)
{
    Dma_DoneIntHandler(DMA_CHANNEL3);
}

/**
 * @brief      Dma error interrupt function
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void Dma_Err_DriverIrqHandler(void)
{
    Dma_ErrorIntHandler();
}

/** @} end of group Public_FunctionDefinition */
