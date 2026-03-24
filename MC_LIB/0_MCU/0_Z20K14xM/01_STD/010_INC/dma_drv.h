/**************************************************************************************************/
/**
 * @file     dma_drv.h
 * @brief    DMA driver module header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#ifndef DMA_DRV_H
#define DMA_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  DMA
 *  @{
 */

/** @defgroup DMA_Public_Types 
 *  @{
 */

/**
 *  @brief DMA channel priority type definition
 */
typedef enum 
{
    DMA_CHN_PRIORITY0 = 0U,          /*!< dma channel priority 0, the lowest */
    DMA_CHN_PRIORITY1,               /*!< dma channel priority 1 */
    DMA_CHN_PRIORITY2,               /*!< dma channel priority 2 */
    DMA_CHN_PRIORITY3,               /*!< dma channel priority 3 */
    DMA_CHN_PRIORITY4,               /*!< dma channel priority 4 */
    DMA_CHN_PRIORITY5,               /*!< dma channel priority 5 */
    DMA_CHN_PRIORITY6,               /*!< dma channel priority 6 */
    DMA_CHN_PRIORITY7,               /*!< dma channel priority 7 */
    DMA_CHN_PRIORITY8,               /*!< dma channel priority 8 */
    DMA_CHN_PRIORITY9,               /*!< dma channel priority 9 */
    DMA_CHN_PRIORITY10,              /*!< dma channel priority 10 */
    DMA_CHN_PRIORITY11,              /*!< dma channel priority 11 */
    DMA_CHN_PRIORITY12,              /*!< dma channel priority 12 */
    DMA_CHN_PRIORITY13,              /*!< dma channel priority 13 */
    DMA_CHN_PRIORITY14,              /*!< dma channel priority 14 */
    DMA_CHN_PRIORITY15               /*!< dma channel priority 15, the highest*/
} DMA_ChannelPriority_t;

/**
 *  @brief DMA channel id type definition
 */ 
typedef enum 
{
    DMA_CHANNEL0      = 0U,          /*!< dma channel 0 */
    DMA_CHANNEL1,                    /*!< dma channel 1 */
    DMA_CHANNEL2,                    /*!< dma channel 2 */
    DMA_CHANNEL3,                    /*!< dma channel 3 */
    DMA_CHANNEL4,                    /*!< dma channel 4 */
    DMA_CHANNEL5,                    /*!< dma channel 5 */
    DMA_CHANNEL6,                    /*!< dma channel 6 */
    DMA_CHANNEL7,                    /*!< dma channel 7 */
    DMA_CHANNEL8,                    /*!< dma channel 8 */
    DMA_CHANNEL9,                    /*!< dma channel 9 */
    DMA_CHANNEL10,                   /*!< dma channel 10 */
    DMA_CHANNEL11,                   /*!< dma channel 11 */
    DMA_CHANNEL12,                   /*!< dma channel 12 */
    DMA_CHANNEL13,                   /*!< dma channel 13 */
    DMA_CHANNEL14,                   /*!< dma channel 14 */
    DMA_CHANNEL15                    /*!< dma channel 15 */
} DMA_Channel_t;

/**
 *  @brief DMA transfer size type definition
 */ 
typedef enum 
{
    DMA_TRANSFER_SIZE_1B  = 0U,      /*!< dma once transfer size: 1 byte */
    DMA_TRANSFER_SIZE_2B,            /*!< dma once transfer size: 2 bytes */
    DMA_TRANSFER_SIZE_4B             /*!< dma once transfer size: 4 bytes */
} DMA_TransferSize_t;

/**
 *  @brief Structure for the DMA hardware request source
 */ 
typedef enum 
{  
    DMA_REQ_UART0_TX                = 2U,    /*!< dma input source: uart0 tx */
    DMA_REQ_UART0_RX                = 3U,    /*!< dma input source: uart0 rx */
    DMA_REQ_UART1_TX                = 4U,    /*!< dma input source: uart1 tx */
    DMA_REQ_UART1_RX                = 5U,    /*!< dma input source: uart1 rx */
    DMA_REQ_UART2_TX                = 6U,    /*!< dma input source: uart2 tx */
    DMA_REQ_UART2_RX                = 7U,    /*!< dma input source: uart2 rx */
    DMA_REQ_UART3_TX                = 8U,    /*!< dma input source: uart3 tx */
    DMA_REQ_UART3_RX                = 9U,    /*!< dma input source: uart3 rx */
    DMA_REQ_UART4_TX                = 10U,   /*!< dma input source: uart4 tx */
    DMA_REQ_UART4_RX                = 11U,   /*!< dma input source: uart4 rx */
    DMA_REQ_UART5_TX                = 12U,   /*!< dma input source: uart5 tx */
    DMA_REQ_UART5_RX                = 13U,   /*!< dma input source: uart5 rx */
    
    DMA_REQ_SPI0_TX                 = 14U,   /*!< dma input source: spi0 tx */
    DMA_REQ_SPI0_RX                 = 15U,   /*!< dma input source: spi0 rx */
    DMA_REQ_SPI1_TX                 = 16U,   /*!< dma input source: spi1 tx */
    DMA_REQ_SPI1_RX                 = 17U,   /*!< dma input source: spi1 rx */
    DMA_REQ_SPI2_TX                 = 18U,   /*!< dma input source: spi2 tx */
    DMA_REQ_SPI2_RX                 = 19U,   /*!< dma input source: spi2 rx */
    DMA_REQ_SPI3_TX                 = 20U,   /*!< dma input source: spi3 tx */
    DMA_REQ_SPI3_RX                 = 21U,   /*!< dma input source: spi3 rx */

    DMA_REQ_STIM0                   = 22U,   /*!< dma input source: STIM0 */
    DMA_REQ_STIM1                   = 23U,   /*!< dma input source: STIM1 */
    DMA_REQ_STIM2                   = 24U,   /*!< dma input source: STIM2 */
    DMA_REQ_STIM3                   = 25U,   /*!< dma input source: STIM3 */
    
    DMA_REQ_I2C0_TX                 = 26U,   /*!< dma input source: i2c0 tx */
    DMA_REQ_I2C0_RX                 = 27U,   /*!< dma input source: i2c0 rx */
#if (2U == I2C_INSTANCE_NUM)	
    DMA_REQ_I2C1_TX                 = 28U,   /*!< dma input source: i2c1 tx */
    DMA_REQ_I2C1_RX                 = 29U,   /*!< dma input source: i2c1 rx */
#endif    
    DMA_REQ_CAN0                    = 30U,   /*!< dma input source: can0 */
    DMA_REQ_CAN1                    = 31U,   /*!< dma input source: can1 */
#if (2U < CAN_INSTANCE_NUM)	
    DMA_REQ_CAN2                    = 32U,   /*!< dma input source: can2 */
    DMA_REQ_CAN3                    = 33U,   /*!< dma input source: can3 */
#endif	
#if (4U < CAN_INSTANCE_NUM)	
    DMA_REQ_CAN4                    = 34U,   /*!< dma input source: can4 */
    DMA_REQ_CAN5                    = 35U,   /*!< dma input source: can5 */
#endif	
#if (8U == CAN_INSTANCE_NUM)	
    DMA_REQ_CAN6                    = 36U,   /*!< dma input source: can6 */
    DMA_REQ_CAN7                    = 37U,   /*!< dma input source: can7 */
#endif    
    DMA_REQ_TIM0_CHANNEL0           = 38U,   /*!< dma input source: tim0-channel0 */
    DMA_REQ_TIM0_CHANNEL1           = 39U,   /*!< dma input source: tim0-channel1 */
    DMA_REQ_TIM0_CHANNEL2           = 40U,   /*!< dma input source: tim0-channel2 */
    DMA_REQ_TIM0_CHANNEL3           = 41U,   /*!< dma input source: tim0-channel3 */
    DMA_REQ_TIM0_CHANNEL4           = 42U,   /*!< dma input source: tim0-channel4 */
    DMA_REQ_TIM0_CHANNEL5           = 43U,   /*!< dma input source: tim0-channel5 */
    DMA_REQ_TIM0_CHANNEL6           = 44U,   /*!< dma input source: tim0-channel6 */
    DMA_REQ_TIM0_CHANNEL7           = 45U,   /*!< dma input source: tim0-channel7 */
    DMA_REQ_TIM1_CHANNEL0           = 46U,   /*!< dma input source: tim1-channel0 */
    DMA_REQ_TIM1_CHANNEL1           = 47U,   /*!< dma input source: tim1-channel1 */
    DMA_REQ_TIM1_CHANNEL2           = 48U,   /*!< dma input source: tim1-channel2 */
    DMA_REQ_TIM1_CHANNEL3           = 49U,   /*!< dma input source: tim1-channel3 */
    DMA_REQ_TIM1_CHANNEL4           = 50U,   /*!< dma input source: tim1-channel4 */
    DMA_REQ_TIM1_CHANNEL5           = 51U,   /*!< dma input source: tim1-channel5 */
    DMA_REQ_TIM1_CHANNEL6           = 52U,   /*!< dma input source: tim1-channel6 */
    DMA_REQ_TIM1_CHANNEL7           = 53U,   /*!< dma input source: tim1-channel7 */
    DMA_REQ_TIM2_CHANNEL0           = 54U,   /*!< dma input source: tim2-channel0 */
    DMA_REQ_TIM2_CHANNEL1           = 55U,   /*!< dma input source: tim2-channel1 */
    DMA_REQ_TIM2_CHANNEL2           = 56U,   /*!< dma input source: tim2-channel2 */
    DMA_REQ_TIM2_CHANNEL3           = 57U,   /*!< dma input source: tim2-channel3 */
    DMA_REQ_TIM2_CHANNEL4           = 58U,   /*!< dma input source: tim2-channel4 */
    DMA_REQ_TIM2_CHANNEL5           = 59U,   /*!< dma input source: tim2-channel5 */
    DMA_REQ_TIM2_CHANNEL6           = 60U,   /*!< dma input source: tim2-channel6 */
    DMA_REQ_TIM2_CHANNEL7           = 61U,   /*!< dma input source: tim2-channel7 */
    DMA_REQ_TIM3_CHANNEL0           = 62U,   /*!< dma input source: tim3-channel0 */
    DMA_REQ_TIM3_CHANNEL1           = 63U,   /*!< dma input source: tim3-channel1 */
    DMA_REQ_TIM3_CHANNEL2           = 64U,   /*!< dma input source: tim3-channel2 */
    DMA_REQ_TIM3_CHANNEL3           = 65U,   /*!< dma input source: tim3-channel3 */
    DMA_REQ_TIM3_CHANNEL4           = 66U,   /*!< dma input source: tim3-channel4 */
    DMA_REQ_TIM3_CHANNEL5           = 67U,   /*!< dma input source: tim3-channel5 */
    DMA_REQ_TIM3_CHANNEL6           = 68U,   /*!< dma input source: tim3-channel6 */
    DMA_REQ_TIM3_CHANNEL7           = 69U,   /*!< dma input source: tim3-channel7 */

    DMA_REQ_MPWM0_CHANNEL0          = 70U,   /*!< dma input source: mpwm0-channel0 */
    DMA_REQ_MPWM0_CHANNEL1          = 71U,   /*!< dma input source: mpwm0-channel1 */
    DMA_REQ_MPWM0_CHANNEL2          = 72U,   /*!< dma input source: mpwm0-channel2 */
    DMA_REQ_MPWM0_CHANNEL3          = 73U,   /*!< dma input source: mpwm0-channel3 */
    DMA_REQ_MPWM0_CHANNEL4          = 74U,   /*!< dma input source: mpwm0-channel4 */
    DMA_REQ_MPWM0_CHANNEL5          = 75U,   /*!< dma input source: mpwm0-channel5 */
    DMA_REQ_MPWM0_CHANNEL6          = 76U,   /*!< dma input source: mpwm0-channel6 */
    DMA_REQ_MPWM0_CHANNEL7          = 77U,   /*!< dma input source: mpwm0-channel7 */
    DMA_REQ_MPWM1_CHANNEL0          = 78U,   /*!< dma input source: mpwm1-channel0 */
    DMA_REQ_MPWM1_CHANNEL1          = 79U,   /*!< dma input source: mpwm1-channel1 */
    DMA_REQ_MPWM1_CHANNEL2          = 80U,   /*!< dma input source: mpwm1-channel2 */
    DMA_REQ_MPWM1_CHANNEL3          = 81U,   /*!< dma input source: mpwm1-channel3 */
    DMA_REQ_MPWM1_CHANNEL4          = 82U,   /*!< dma input source: mpwm1-channel4 */
    DMA_REQ_MPWM1_CHANNEL5          = 83U,   /*!< dma input source: mpwm1-channel5 */
    DMA_REQ_MPWM1_CHANNEL6          = 84U,   /*!< dma input source: mpwm1-channel6 */
    DMA_REQ_MPWM1_CHANNEL7          = 85U,   /*!< dma input source: mpwm1-channel7 */

    DMA_REQ_ADC0                    = 88U,   /*!< dma input source: adc0 */
    DMA_REQ_ADC1                    = 89U,   /*!< dma input source: adc1 */
    
    DMA_REQ_CMP                     = 90U,   /*!< dma input source: cmp */
    
    DMA_REQ_PORTA                   = 91U,   /*!< dma input source: PORTA */
    DMA_REQ_PORTB                   = 92U,   /*!< dma input source: PORTB */
    DMA_REQ_PORTC                   = 93U,   /*!< dma input source: PORTC */
    DMA_REQ_PORTD                   = 94U,   /*!< dma input source: PORTD */
    DMA_REQ_PORTE                   = 95U,   /*!< dma input source: PORTE */
    
    DMA_REQ_DMAMUX_ALWAYS_ENABLED0  = 96U,   /*!< dma input source: always on channel 0 */
    DMA_REQ_DMAMUX_ALWAYS_ENABLED1  = 97U,   /*!< dma input source: always on channel 1 */

    DMA_REQ_SOFTWARE                = 128U   /*!< software trigger to DMA channel */
} DMA_RequestSource_t;

/**
 *  @brief DMA behavior in debug mode type definition
 */ 
typedef enum 
{
    DMA_DEBUG_CONTINUE              = 0U,   /*!< continue transfer in debug mode */
    DMA_DEBUG_HALT                          /*!< halt next transfer in debug mode */
} DMA_DebugBehavior_t;

/**
 *  @brief DMA priority arbitration type definition
 */ 
typedef enum 
{
    DMA_FIXED_PRIORITY_ARBITRATION  = 0U,   /*!< fixed priority */
    DMA_ROUND_ROBIN_ARBITRATION             /*!< round-robin priority */
} DMA_PriorityArbitration_t;

/**
 *  @brief DMA channel preempt type definition, Defines the behavior of this channel and other channels in concurrency:
 *         When channel DMA request is servicing and a higher priority channel's DMA request assert:
 *         - NO SUSPEND: channel DMA service can not be suspended by other channel
 *         - SUSPEND: channel DMA service can be suspended by other channel
 *         When channel DMA request assert but a lower priority channel's DMA is servicing:
 *         - NO PREEMPT: channel DMA request can not preempt a lower priority channel's service
 *         - PREEMPT: channel DMA request can preempt a lower priority channel's service
 */ 
typedef enum 
{
    DMA_NOSUSPEND_PREEMPT           = 0U,    /*!< NO SUSPEND and PREEMPT */
    DMA_NOSUSPEND_NOPREEMPT         = 1U,    /*!< NO SUSPEND and NO PREEMPT */
    DMA_SUSPEND_PREEMPT             = 2U,    /*!< SUSPEND and PREEMPT */
    DMA_SUSPEND_NOPREEMPT           = 3U     /*!< SUSPEND and NO PREEMPT */ 
} DMA_ChannelPreempt_t;

/**
 *  @brief DMA behavior type definition when error occur
 */ 
typedef enum 
{
    DMA_ERROR_CONTINUE              = 0U,   /*!< continue transfer when error occur */
    DMA_ERROR_HALT                          /*!< halt next transfer when error occur */
} DMA_ErrorBehavior_t;

/**
 *  @brief DMA init config type definition
 */ 
typedef struct 
{
    DMA_DebugBehavior_t dmaDebugBehavior;                /*!< dma behavior in debiug mode */
    DMA_PriorityArbitration_t dmaPriorityArbitration;    /*!< dma priority arbitration */
    DMA_ErrorBehavior_t dmaErrorBehavior;                /*!< dma behavior in error mode */
} DMA_Config_t;

/**
 *  @brief DMA interrupt type definition
 */ 
typedef enum
{
    DMA_INT_ERROR           = 0U,                /*!< dma error interrupt */
    DMA_INT_DONE,                                /*!< dma done interrupt */
    DMA_INT_ALL                                  /*!< dma all interrupt */
} DMA_Int_t;

/**  
 *  @brief DMA error type definition
 */
typedef enum
{
    DMA_ERROR_PRIORITY      = 0U,               /*!< dma priority error */
    DMA_ERROR_SRCADDR,                          /*!< dma src addr unalign error */
    DMA_ERROR_SRCOFFSET,                        /*!< dma src offset unalign error */
    DMA_ERROR_DESTADDR,                         /*!< dma dest addr unalign error */
    DMA_ERROR_DESTOFFSET,                       /*!< dma dest addr unalign error */
    DMA_ERROR_TRANSFERNUM,                      /*!< dma transfer size unalign error */
    DMA_ERROR_SRCBUS,                           /*!< dma src bus error */
    DMA_ERROR_DESTBUS,                          /*!< dma dest bus error */
    DMA_ERROR_ALL                               /*!< dma all error type */
} DMA_Error_t;

/**
 *  @brief DMA transfer configuration
 */
typedef struct 
{
    DMA_Channel_t channel;                      /*!< specifies the channel used for dma transfer */
    DMA_ChannelPriority_t channelPriority;      /*!< dma channel priority - only used Fixed priority mode */
    DMA_ChannelPreempt_t channelPreempt;        /*!< the behavior of this channel and other channels in concurrency */
    DMA_RequestSource_t source;                 /*!< selects the source of the DMA request for this channel */
    uint32_t srcAddr;                           /*!< address pointing to the source data */
    uint32_t destAddr;                          /*!< address pointing to the destination data */
    int16_t minorLoopSrcOffset;                 /*!< source address offset in minor loop */ 
    int16_t minorLoopDestOffset;                /*!< destination address offset in minor loop */
    int16_t majorLoopSrcOffset;                 /*!< source address offset after a major loop done */ 
    int16_t majorLoopDestOffset;                /*!< destination address offset after a major loop done */
    uint32_t transferByteNum;                   /*!< transfer bytes number in a minor loop */
    uint16_t minorLoopNum;                      /*!< number of minor loop in a major loop */
    DMA_TransferSize_t srcTransferSize;         /*!< source data transfer size */
    DMA_TransferSize_t destTransferSize;        /*!< destination data transfer size */
    ControlState_t disableRequestAfterDoneCmd;  /*!< disable request after done control
                                                     - ENABLE: disable channel request after done 
                                                     - DISABLE: enable channel request after done */
} DMA_TransferConfig_t;

/** @} end of group DMA_Public_Types */

/** @defgroup DMA_Public_Constants
 *  @{
 */

/** @} end of group DMA_Public_Constants */

/** @defgroup DMA_Public_Macro
 *  @{
 */

/** @} end of group DMA_Public_Macro */


/** @defgroup DMA_Public_FunctionDeclaration
 *  @brief DMA functions declaration
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
                                      DMA_RequestSource_t questSource);

/**
 * @brief      Enable dmamux output channel Function
 *
 * @param[in]  outChannel:     output channel id.
 *
 * @return none
 *
 */
void DMAMUX_OutputChannelEnable(DMA_Channel_t outChannel);

/**
 * @brief      Disable dmamux output channel Function
 *
 * @param[in]  outChannel:     output channel id.
 *
 * @return none
 *
 */
void DMAMUX_OutputChannelDisable(DMA_Channel_t outChannel);

/**
 * @brief      Dma Initializes Function
 *
 * @param[in]  configPtr:     Pointer to a DMA configuration structure.
 *
 * @return none
 *
 */
void DMA_Init(const DMA_Config_t * configPtr);

/**
 * @brief      Get dma busy status Function
 *
 * @param[in]  none
 *
 * @return     busy status.
 *
 */
FlagStatus_t DMA_GetDmaBusyStatus(void);

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
void DMA_HaltControl(ControlState_t cmd);

/**
 * @brief      Get dma halt status Function
 *
 * @param[in]  none
 *
 * @return whether dma halt is asserted or not.
 *
 */
FlagStatus_t DMA_GetHaltStatus(void);

/**
 * @brief      Set dma priority arbitration mode Function
 *
 * @param[in]  channelArbitration: arbitration mode
 *
 * @return none.
 *
 */
void DMA_SetPriorityArbitrationMode(DMA_PriorityArbitration_t arbitration);

/**
 * @brief       Get dma current priority arbitration mode Function
 *
 * @param[in]  none
 *
 * @return     current priority arbitration mode.
 *
 */
DMA_PriorityArbitration_t DMA_GetPriorityArbitrationMode(void);

/**
 * @brief      Enable dma channel request Function
 *
 * @param[in]  channel: dma channel id
 *
 * @return none.
 *
 */
void DMA_ChannelRequestEnable(DMA_Channel_t channel);

/**
 * @brief      Disable dma channel request Function
 *
 * @param[in]  channel: dma channel id
 *
 * @return none.
 *
 */
void DMA_ChannelRequestDisable(DMA_Channel_t channel);

/**
 * @brief      Get dma channel request status Function
 *
 * @param[in]  channel: dma channel id
 *
 * @return whether dma channel request enable bit is asserted or not.
 *
 */
FlagStatus_t DMA_GetChannelRequestStatus(DMA_Channel_t channel);

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
                                     DMA_ChannelPriority_t priority);

/**
 * @brief      Get dma channel priority Function
 *
 * @param[in]  channel: dma channel id
 *
 * @return channel priority.
 *
 */
DMA_ChannelPriority_t DMA_GetChannelPriority(DMA_Channel_t channel);

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
                                    DMA_ChannelPreempt_t preempt);

/**
 * @brief      Get dma channel preempt type Function
 *
 * @param[in]  channel: dma channel id
 *
 * @return channel preempt type.
 *
 */
DMA_ChannelPreempt_t DMA_GetChannelPreempt(DMA_Channel_t channel);

/**
 * @brief      Set dma source address Function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  address: dma transfer source address
 *
 * @return none.
 *
 */
void DMA_SetSrcAddr(DMA_Channel_t channel, uint32_t address);

/**
 * @brief      Get dma source address Function
 *
 * @param[in]  channel: dma channel id
 *
 * @return dma source address.
 *
 */
uint32_t DMA_GetSrcAddr(DMA_Channel_t channel);

/**
 * @brief      Set dma destination address Function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  address: dma transfer destination address
 *
 * @return none.
 *
 */
void DMA_SetDestAddr(DMA_Channel_t channel, uint32_t address);

/**
 * @brief      Get dma destination address Function
 *
 * @param[in]  channel: dma channel id
 *
 * @return dma destination address.
 *
 */
uint32_t DMA_GetDestAddr(DMA_Channel_t channel);

/**
 * @brief      Set dma source address offset in minor loop Function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  offset: dma source address offset in minor loop
 *
 * @return none.
 *
 */
void DMA_SetMinorLoopSrcOffset(DMA_Channel_t channel, int16_t offset);

/**
 * @brief      Set dma destination address offset in minor loop Function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  offset: dma destination address offset in minor loop
 *
 * @return none.
 *
 */
void DMA_SetMinorLoopDestOffset(DMA_Channel_t channel, int16_t offset);

/**
 * @brief      Set dma source address offset after a major loop done Function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  offset: dma source address offset after a major loop done
 *
 * @return none.
 *
 */
void DMA_SetMajorLoopSrcOffset(DMA_Channel_t channel, int16_t offset);

/**
 * @brief      Set dma destination address offset after a major loop done Function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  offset: dma destination address offset after a major loop done
 *
 * @return none.
 *
 */
void DMA_SetMajorLoopDestOffset(DMA_Channel_t channel, int16_t offset);

/**
 * @brief      Set total number of minor loop in a major loop Function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  num: number of minor loop in a major loop
 *
 * @return none.
 *
 */
void DMA_SetMinorLoopNum(DMA_Channel_t channel, uint16_t num);

/**
 * @brief      Get total number of minor loop in one major loop Function
 *
 * @param[in]  channel: dma channel id
 *
 * @return number of minor loop in a major loop.
 *
 */
uint16_t DMA_GetMinorLoopNum(DMA_Channel_t channel);

/**
 * @brief      Get number of minor loop that not finished in one major loop Function
 *
 * @param[in]  channel: dma channel id
 *
 * @return number of rest minor loop in a major loop.
 *
 */
uint16_t DMA_GetRestMinorLoopNum(DMA_Channel_t channel);

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
                                     DMA_TransferSize_t size);

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
                                      DMA_TransferSize_t size);

/**
 * @brief      Set dma transfer num of bytes in a minor loop Function
 *
 * @param[in]  channel: dma channel id
 * @param[in]  num: dma transfer num of bytes in a minor loop
 *
 * @return none.
 *
 */
void DMA_SetTransferByteNum(DMA_Channel_t channel, uint32_t num);

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
                                                ControlState_t cmd);

/**
 * @brief      Software trigger one channel dma transfer Function
 *
 * @param[in]  channel: dma channel id
 *
 * @return none.
 *
 */
void DMA_TriggerChannelStart(DMA_Channel_t channel);

/**
 * @brief      Software trigger all channel dma transfer Function
 *
 * @param[in]  none
 *
 * @return none.
 *
 */
void DMA_TriggerAllChannelStart(void);

/**
 * @brief      Get one channel hardware DMA request status Function
 *
 * @param[in]  channel: dma channel id
 *
 * @return whether a channel hardware DMA request is asserted or not.
 *
 */
FlagStatus_t DMA_GetHwRequestStatus(DMA_Channel_t channel);

/**
 * @brief      Get dma last error status Function
 *
 * @param[in]  error: error type
 *
 * @return whether a dma error is asserted or not.
 *
 */
FlagStatus_t DMA_GetLastErrorStatus(DMA_Error_t error);

/**
 * @brief      Get last error channel id Function
 *
 * @param[in]  none
 *
 * @return channel which occur the last error
 *
 */
DMA_Channel_t DMA_GetLastErrorChannel(void);

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
IntStatus_t DMA_GetIntStatus(DMA_Channel_t channel, DMA_Int_t intType);

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
void DMA_ClearIntStatus(DMA_Channel_t channel, DMA_Int_t intType);

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
void DMA_ClearAllChannelsIntStatus(DMA_Int_t intType);

/**
 * @brief      Get channel done flag Function
 *
 * @param[in]  channel: dma channel id
 *
 * @return whether a channel done flag is asserted or not.
 *
 */
FlagStatus_t DMA_GetDoneStatus(DMA_Channel_t channel);

/**
 * @brief      Clear channel done flag Function
 *
 * @param[in]  channel: dma channel id
 *
 * @return none.
 *
 */
void DMA_ClearDoneStatus(DMA_Channel_t channel);

/**
 * @brief      Clear all channels done flag Function
 *
 * @param[in]  none
 *
 * @return none.
 *
 */
void DMA_ClearAllChannelsDoneStatus(void);

/**
 * @brief      Get channel busy status Function
 *
 * @param[in]  channel: dma channel id
 *
 * @return whether a channel is busy or not.
 *
 */
FlagStatus_t DMA_GetChannelBusyStatus(DMA_Channel_t channel);

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
void DMA_IntMask(DMA_Channel_t channel, DMA_Int_t intType, IntMask_t intMask);

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
                                      isr_cb_t * cbFun);

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
ResultStatus_t DMA_ConfigTransfer(const DMA_TransferConfig_t * config);

/** @} end of group DMA_Public_FunctionDeclaration */

/** @} end of group DMA  */

/** @} end of group Z20K14XM_Peripheral_Driver */

#endif  /* DMA_DRV_H */

