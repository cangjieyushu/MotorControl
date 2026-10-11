/*
*     File Name :                        main
*     Library/Module Name :              main
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             任务管理
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "main.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 公有接口实现 -----------------------------*/
int main(void)
{
    __disable_irq();
    
    BSP_CLK_Init();
    BSP_GPIO_Init();
    BSP_ISR_Init();

    BSP_DAC_Init();      /* ★ 1. 先建立阈值电压 */
    BSP_OPAMP_Init();    /* ★ 2. 再使能 OPA 输出到 P 端 */
    BSP_CMP_Init();      /* ★ 3. 最后配置比较器，此时输入输出都已就绪 */
    BSP_PWM_Init();      /* TIM8 互补 PWM，BKIN 由 CMP 触发 */
    BSP_ADC_Init();
    BSP_DMA_Init();
    BSP_UART_DMA_Init();
    BSP_UART_Init();
    
    __enable_irq();
    
    for(;;)
    {
        System_10msTask_Flow();
    }
}

void ADC1_2_IRQHandler(void)
{
    if(ADC_GetFlagStatus(ADC1, ADC_FLAG_JEOC))
    {
        ADC_ClearFlag(ADC1, ADC_FLAG_JEOC);
        MCFOC_Current_Flow(MOTOR_NUMBER_N0);     //168M,18us,72M,42us
    }
}

void SysTick_Handler(void)
{
    System_1msTask_Flow();
    MCFOC_Speed_Flow(MOTOR_NUMBER_N0);
}

void USART1_IRQHandler(void)
{
    /* ---- IDLE 中断：一帧接收完成 ---- */
    if (USART_GetITStatus(HAL_HMI_UART, USART_IT_IDLE) != RESET)
    {
        USART_ClearITPendingBit(HAL_HMI_UART, USART_IT_IDLE);
        
        UART_DMA_Rx_Int();
    }
}

void DMA1_Channel5_IRQHandler(void)
{
    /* 传输完成中断（实际上 DMA 循环模式下会持续触发，每圈一次）*/
    if (DMA_GetITStatus(DMA1_IT_TC5) != RESET)
    {
        /* 缓冲区写满一圈，如果协议层还没处理完，说明数据过载 */
        DMA_ClearITPendingBit(DMA1_IT_TC5);
    }

    /* 半完成中断 */
    if (DMA_GetITStatus(DMA1_IT_HT5) != RESET)
    {
        /* 可用于双缓冲切换 */
        DMA_ClearITPendingBit(DMA1_IT_HT5);
    }
}

void DMA1_Channel4_IRQHandler(void)
{
    if (DMA_GetITStatus(DMA1_IT_TC4) != RESET)
    {
        DMA_ClearITPendingBit(DMA1_IT_TC4);

        /* 关闭 DMA 通道 */
        DMA_Cmd(DMA1_Channel4, DISABLE);

        /* 等待 USART1 的最后一个字节移位完成 */
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) { }

        /* 切回 RS485 接收方向 */
        GPIO_ResetBits(UART_EN_PORT, UART_EN_Pin);

        /* 通知上层发送完成 */
//        g_uart_tx_busy = 0;
    }
}
