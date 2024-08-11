/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/

#include "BSP_DMA.h"

uint16_t ADC_INT_RAW_DATA[4] = {0,0,0,0};

void BSP_DMA_Init(void)
{
	DMA_InitTypeDef DMA_InitStructure;

	while(DMA_GetCmdStatus(DMA2_Stream0) != DISABLE);                               /*等待DMA可以配置*/
	 
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;                                  /*DMA通道0*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_Address;           /*外设地址*/
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)ADC_INT_RAW_DATA;             /*存取器地址*/
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;                         /*方向从外设到内存*/
	DMA_InitStructure.DMA_BufferSize = 1;                                           /*数据传输的数量为1*/
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;                /*地址不增加*/
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                         /*地址不增加*/
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;     /*数据长度半字*/
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;             /*数据长度半字*/
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;                             /*高优先级*/
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                                 /*循环模式*/
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;                          /*禁止FIFO*/
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;               /*FIFO的值*/
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;                     /*单次传输*/
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;             /*单次传输*/
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);/**/
    
    DMA_Cmd(DMA2_Stream0, ENABLE);
}
