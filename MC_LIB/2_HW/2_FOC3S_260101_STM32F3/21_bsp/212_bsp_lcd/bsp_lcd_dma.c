/*
*     File Name :                        bsp_lcd_dma
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             LCD SPI DMA 初始化
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_lcd_dma.h"


/*-------------------------- 2. 变量 ---------------------------------*/
/* LCD DMA 完成标志：初始化时置 1（空闲）*/
volatile uint8_t lcd_dma_done = 1U;


/*-------------------------- 3. 公有接口实现 -----------------------------*/
/*
Function: BSP_LCD_DMA_Init
Description: LCD SPI3 的 DMA 收发通道配置
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_LCD_DMA_Init(void)
{
    DMA_InitTypeDef DMA_InitStructure;
    
    /* SPI3_RX 重映射到 DMA2_Channel1（避免与 ADC1 的 DMA1_Ch1 冲突） */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    SYSCFG_DMAChannelRemapConfig(SYSCFG_DMARemapCh2_SPI1_RX, DISABLE);  /* 确保 SPI3_RX 走 DMA2_Ch1 */
    
    /* ============================================================
     * DMA1_Channel2：SPI3_TX（单次模式）
     * ============================================================ */
    DMA_DeInit(HW_LCD_SPI_TX_DMA_CH);

    DMA_InitStructure.DMA_PeripheralBaseAddr = (Q32U_)&HW_LCD_SPI->DR;
    DMA_InitStructure.DMA_MemoryBaseAddr     = 0;                    /* 每次启动时重配 */
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize         = 0;
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Priority           = DMA_Priority_Medium;
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;
    DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
    DMA_Init(HW_LCD_SPI_TX_DMA_CH, &DMA_InitStructure);

    /* 使能 DMA 传输完成中断 */
    DMA_ITConfig(HW_LCD_SPI_TX_DMA_CH, DMA_IT_TC, ENABLE);

    /* 通道默认关闭，等发送时由上层启动 */
    DMA_Cmd(HW_LCD_SPI_TX_DMA_CH, DISABLE);

    /* ============================================================
     * DMA2_Channel1：SPI3_RX（循环模式，需 SYSCFG 重映射）
     * ============================================================ */
    DMA_DeInit(HW_LCD_SPI_RX_DMA_CH);

    DMA_InitStructure.DMA_PeripheralBaseAddr = (Q32U_)&HW_LCD_SPI->DR;
    DMA_InitStructure.DMA_MemoryBaseAddr     = 0;
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize         = 0;
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Priority           = DMA_Priority_Medium;
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;
    DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
    DMA_Init(HW_LCD_SPI_RX_DMA_CH, &DMA_InitStructure);

    /* 通道默认关闭 */
    DMA_Cmd(HW_LCD_SPI_RX_DMA_CH, DISABLE);

    /* SPI3 使能 DMA 收发请求 */
    SPI_I2S_DMACmd(HW_LCD_SPI, SPI_I2S_DMAReq_Tx, ENABLE);
}
