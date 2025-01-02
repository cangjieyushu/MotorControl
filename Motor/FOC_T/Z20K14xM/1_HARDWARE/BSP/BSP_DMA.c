/**************************************************************************************************
*     File Name :                        BSP_DMA.c
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             DMA初始化及应用层接口源文件
**************************************************************************************************/
#include "BSP_DMA.h"
#include "BSP_ADC.h"

uint32_t Hal_AdcLoopData[8] = {0,0,0,0,0,0,0,0};
uint32_t Hal_AdcMapData[8] = {0,0,0,0,0,0,0,0};

/**********************************************************************************************
Function: DMA_ADC_Init
Description: 电机控制用DMA初始化
Input: 电流环中断函数
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_DMA_Init(isr_cb_t *DMADoneCbf)
{
#if (HAL_CURRENT_SAMPLE_MODE == HAL_THREE_SHUNT)

    DMA_TransferConfig_t GtDMATransferConfig;

    /* Select DMA channel 0 transfer */
    GtDMATransferConfig.channel = DMA_CHANNEL0;
    /* Select ADC as the DMA request for channel 0 */
    GtDMATransferConfig.source = DMA_REQ_ADC0;
    /* DMA channel priority */
    GtDMATransferConfig.channelPriority = DMA_CHN_PRIORITY0;
    /* Unmask done interrupt */
    DMA_IntMask(DMA_CHANNEL0,DMA_INT_DONE,UNMASK);
    /* Mask error interrupt */
    DMA_IntMask(DMA_CHANNEL0,DMA_INT_ERROR,MASK);
    /* Done int Callback that will be registered for channel 0 */
    DMA_InstallCallBackFunc(DMA_CHANNEL0,DMA_INT_DONE,DMADoneCbf);
    
    /* Address pointing to the source data */
    GtDMATransferConfig.srcAddr = (uint32_t)HAL_ADC_DATA_ADDRESS;
    /* Address pointing to the destination data */
    /*PRQA S 0306 ++*/
    GtDMATransferConfig.destAddr = (uint32_t)Hal_AdcLoopData;
    /*PRQA S 0306 --*/
    /* Number of minor loop in a major loop: 1 */
    GtDMATransferConfig.minorLoopNum = 1U;
    /* Source address offset in minor loop */
    GtDMATransferConfig.minorLoopSrcOffset = 0;
    /* Destination address offset in minor loop */
    GtDMATransferConfig.minorLoopDestOffset = 4;
    /* Source address offset after a major loop done */
    GtDMATransferConfig.majorLoopSrcOffset = 0;
    /* Destination address offset after a major loop done */
    GtDMATransferConfig.majorLoopDestOffset = -16;
    
    /* Source data transfer size */
    GtDMATransferConfig.srcTransferSize = DMA_TRANSFER_SIZE_4B;
    /* Destination data transfer size */
    GtDMATransferConfig.destTransferSize = DMA_TRANSFER_SIZE_4B;
    /* Transfer bytes number */
    GtDMATransferConfig.transferByteNum = 16U;
    /* Disable request after done control */
    GtDMATransferConfig.disableRequestAfterDoneCmd = DISABLE;
    /* DMA transfer Configure */
    DMA_ConfigTransfer(&GtDMATransferConfig);
    /* Enable dma channel request */
    DMA_ChannelRequestEnable(DMA_CHANNEL0);
    
#else
    
    DMA_TransferConfig_t GtDMATransferConfig;
    
    /* Select DMA channel 0 transfer */
    GtDMATransferConfig.channel = DMA_CHANNEL0;
    /* Select ADC as the DMA request for channel 0 */
    GtDMATransferConfig.source = DMA_REQ_ADC0;
    /* DMA channel priority */
    GtDMATransferConfig.channelPriority = DMA_CHN_PRIORITY0;
     /* Unmask done interrupt */
    DMA_IntMask(DMA_CHANNEL0,DMA_INT_DONE,UNMASK);
    /* Mask error interrupt */
    DMA_IntMask(DMA_CHANNEL0,DMA_INT_ERROR,MASK);
     /* Done int Callback that will be registered for channel 0 */
    DMA_InstallCallBackFunc(DMA_CHANNEL0,DMA_INT_DONE,DMADoneCbf);
  
    
    /* Address pointing to the source data */
    GtDMATransferConfig.srcAddr = (uint32_t)HAL_ADC_DATA_ADDRESS;
    /* Address pointing to the destination data */
    GtDMATransferConfig.destAddr  = (uint32_t)Hal_AdcMapData;
    /* Number of minor loop in a major loop: 1 */
    GtDMATransferConfig.minorLoopNum = 1U;
    /* Source address offset in minor loop */
    GtDMATransferConfig.minorLoopSrcOffset = 0;
    /* Destination address offset in minor loop */
    GtDMATransferConfig.minorLoopDestOffset = 4;
    /* Source address offset after a major loop done */
    GtDMATransferConfig.majorLoopSrcOffset = 0;
    /* Destination address offset after a major loop done */
    GtDMATransferConfig.majorLoopDestOffset = -12;
    
    /* Source data transfer size */
    GtDMATransferConfig.srcTransferSize = DMA_TRANSFER_SIZE_4B;
    /* Destination data transfer size */
    GtDMATransferConfig.destTransferSize = DMA_TRANSFER_SIZE_4B;
    /* Transfer bytes number */
    GtDMATransferConfig.transferByteNum = 12U;
    /* Disable request after done control */
    GtDMATransferConfig.disableRequestAfterDoneCmd = DISABLE;
    /* DMA transfer Configure */
    DMA_ConfigTransfer(&GtDMATransferConfig);
    /* Enable dma channel request */
    DMA_ChannelRequestEnable(DMA_CHANNEL0);
    
#endif
}

uint32_t Hal_AdcLoopData_S[8] = {0};

/**********************************************************************************************
Function: BSP_DMA_Init_S
Description: 应用层DMA初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_DMA_Init_S(void)
{
    DMA_TransferConfig_t GtDMATransferConfig;
    DMA_Config_t DMAInitConfig =
    {
        .dmaDebugBehavior = DMA_DEBUG_CONTINUE,
        .dmaPriorityArbitration = DMA_FIXED_PRIORITY_ARBITRATION,
        .dmaErrorBehavior = DMA_ERROR_HALT
    };    
    DMA_Init(&DMAInitConfig);   
    
    /* Select DMA channel 1 transfer M1 &Bus*/
    GtDMATransferConfig.channel = DMA_CHANNEL1;
    /* Select ADC as the DMA request for channel 1 */
    GtDMATransferConfig.source = DMA_REQ_ADC1;
    /* DMA channel priority */
    GtDMATransferConfig.channelPriority = DMA_CHN_PRIORITY1;
        /* mask done interrupt */
    DMA_IntMask(DMA_CHANNEL1,DMA_INT_DONE,MASK);
    /* Mask error interrupt */
    DMA_IntMask(DMA_CHANNEL1,DMA_INT_ERROR,MASK);
    /* Done int Callback that will be registered for channel 1 */
//    DMA_InstallCallBackFunc(DMA_CHANNEL1,DMA_INT_DONE,DMADoneCbf);
    /* Address pointing to the source data */
    GtDMATransferConfig.srcAddr = (uint32_t)HAL_ADC_DATA_ADDRESS_S;
    /* Address pointing to the destination data */
    /*PRQA S 0306 ++*/
    GtDMATransferConfig.destAddr = (uint32_t)Hal_AdcLoopData_S;
    /*PRQA S 0306 --*/
    /* Number of minor loop in a major loop: 1 */
    GtDMATransferConfig.minorLoopNum = 1U;
    /* Source address offset in minor loop */
    GtDMATransferConfig.minorLoopSrcOffset = 0;
    /* Destination address offset in minor loop */
    GtDMATransferConfig.minorLoopDestOffset = 4;
    /* Source address offset after a major loop done */
    GtDMATransferConfig.majorLoopSrcOffset = 0;
    /* Destination address offset after a major loop done */
    GtDMATransferConfig.majorLoopDestOffset = - 4*ADC_DATA_NUM_S;
    /* Source data transfer size */
    GtDMATransferConfig.srcTransferSize = DMA_TRANSFER_SIZE_4B;
    /* Destination data transfer size */
    GtDMATransferConfig.destTransferSize = DMA_TRANSFER_SIZE_4B;
    /* Transfer bytes number */
    GtDMATransferConfig.transferByteNum = 4*ADC_DATA_NUM_S;
    /* Disable request after done control */
    GtDMATransferConfig.disableRequestAfterDoneCmd = DISABLE;
    GtDMATransferConfig.channelPreempt =  DMA_SUSPEND_NOPREEMPT;

    /* DMA transfer Configure */
    DMA_ConfigTransfer(&GtDMATransferConfig);

    /* Enable dma channel request */
    DMA_ChannelRequestEnable(DMA_CHANNEL1);
}