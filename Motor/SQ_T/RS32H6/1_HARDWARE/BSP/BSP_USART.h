/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef BSP_USART_H
#define BSP_USART_H

#include "MotorHal_cfg.h"

#define USART1_RESCEIVE_DATA         UART1->DR
#define USART1_TRANSMISSION_DATA     UART1->DR

#define USART2_RESCEIVE_DATA         UART2->DR
#define USART2_TRANSMISSION_DATA     UART2->DR

void BSP_USART_Init(void);

#endif /* BSP_USART_H */
