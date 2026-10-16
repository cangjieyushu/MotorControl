/*
*     File Name :                        bsp_mc_dma
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制 DMA 初始化（ADC1 规则组搬运）
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_mc_dma.h"
#include "bsp_mc_adc.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 公有接口实现 -----------------------------*/
/*
Function: BSP_MC_DMA_Init
Description: ADC1 规则组 DMA 初始化
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_MC_DMA_Init(void)
{
    DMA_InitTypeDef DMA_InitStructure;
    Q32U_ timeout = 0xFFFFU;

    /* F3 无 DMA_GetCmdStatus()，直接读 CCR 的 EN 位判断 DMA 是否使能 */
    while ((HW_MC_ADC_DMA_CHANNEL->CCR & DMA_CCR_EN) && timeout--)
    {
        DMA_Cmd(HW_MC_ADC_DMA_CHANNEL, DISABLE);
    }

    /* 复位通道 */
    DMA_DeInit(HW_MC_ADC_DMA_CHANNEL);

    /* DMA1_Channel1 关联 ADC1 规则组 */
    DMA_InitStructure.DMA_PeripheralBaseAddr = (Q32U_)&HW_MC_ADC1->DR;
    DMA_InitStructure.DMA_MemoryBaseAddr     = (Q32U_)BSP_ADC_SYSTEM_BUFFER;
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize         = 2;                                /* 温度 + 母线电压 */
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;      /* 32 位 */
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Word;          /* 32 位 */
    DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;
    DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
    DMA_Init(HW_MC_ADC_DMA_CHANNEL, &DMA_InitStructure);
    DMA_Cmd(HW_MC_ADC_DMA_CHANNEL, ENABLE);

    /* ADC1 关联 DMA */
    ADC_DMACmd(HW_MC_ADC1, ENABLE);

    /* DMA 就绪后，启动 ADC1 规则组首次转换 */
    ADC_StartConversion(HW_MC_ADC1);
}
