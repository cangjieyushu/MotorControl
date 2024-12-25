/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/

#include "BSP_USART.h"

void BSP_USART_Init(void)
{
	UART_InitTypeDef UART_InitStruct = {0};

	UART_InitStruct.BaudRate             = 9600U;
	UART_InitStruct.DataWidth            = UART_DATAWIDTH_8B;
	UART_InitStruct.Parity               = UART_PARITY_NONE;
	UART_InitStruct.StopBits             = UART_STOPBITS_1;
	UART_InitStruct.TransferDirection    = UART_DIRECTION_TX_RX;
    
	UART_Init(UART1,&UART_InitStruct);
	UART_Init(UART2,&UART_InitStruct);
      
	UART_Enable_IT(UART1, UART_IT_RXNEIE);
	UART_Enable_IT(UART1, UART_IT_TCIE);
    UART_Clear_Flag(UART1, UART_FLAG_RXNE);
    UART_Clear_Flag(UART1, UART_FLAG_TXE);
    UART_Disable_Tx(UART1);   
    UART_Disable_Rx(UART1);  
	UART_Enable(UART1);
     
	UART_Enable_IT(UART2, UART_IT_RXNEIE);
	UART_Enable_IT(UART2, UART_IT_TCIE);
    UART_Clear_Flag(UART2, UART_FLAG_RXNE);
    UART_Clear_Flag(UART2, UART_FLAG_TXE);
    UART_Disable_Tx(UART2);   
    UART_Disable_Rx(UART2); 
	UART_Enable(UART2);   
    
}
