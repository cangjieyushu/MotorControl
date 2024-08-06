/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef BSP_GPIO_H
#define BSP_GPIO_H

#include <stdint.h>
#include "stm32f4xx.h"

#define SHUTDOWN1_GPIO_Port         GPIOF
#define SHUTDOWN1_Pin               GPIO_Pin_10

#define Start_Stop_GPIO_Port        GPIOE
#define Start_Stop_Pin              GPIO_Pin_4

#define LED0_GPIO_PORT              GPIOE
#define LED0_Pin                    GPIO_Pin_0

#define LED1_GPIO_PORT              GPIOE
#define LED1_Pin                    GPIO_Pin_1

void BSP_GPIO_Init(void);

#endif /* BSP_GPIO_H */
