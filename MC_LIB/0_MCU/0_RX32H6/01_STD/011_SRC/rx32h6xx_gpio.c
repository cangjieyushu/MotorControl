/*********************************************************************************************
Copyright <2024> <Icore Technology (Nanjing)  Co.,Ltd>
All Rights Reserved,
Redistribution and use in source and binary forms, with or without modification, are permitted
provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice, this list of
conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list of
conditions and the following disclaimer in the documentation and/or other materials provided 
with the distribution.
3. Neither the name of the copyright holder nor the names of its contributors may be used to 
endorse or promote products derived from this software without specific prior written
permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS 
OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
OF THE POSSIBILITY OF SUCH DAMAGE.
**********************************************************************************************/

/*
*********************************************************************************************************
*                                              rx32h6xx
*                                           Library Function
*
*                                   Copyright 2024, RX Tech, Corp.
*                                        All Rights Reserved
*
*
* Project      : rx32h6xx
* File         : rx32h6xx_gpio.c
* By           : RX_SD_Team
* Version      : V1.0.0
* Description  : Only rx32h6xx
*********************************************************************************************************
*/

#include "rx32h6xx.h"
#include "rx32h6xx_gpio.h"

/**
  * @brief  Initializes the GPIOx peripheral in the GPIO_InitStruct.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that
  *         contains the configuration information for the specified GPIO peripheral.
  * @retval None
  */
void GPIO_DeInit(GPIO_TypeDef *GPIOx)
{
	if(GPIOx==GPIOA)
	{
		RCC_Enable_AHBRST(RCC_AHBRSTR_IOPARST); 
		RCC_Disable_AHBRST(RCC_AHBRSTR_IOPARST);
	}
	else if(GPIOx==GPIOB)
	{
		RCC_Enable_AHBRST(RCC_AHBRSTR_IOPBRST); 
		RCC_Disable_AHBRST(RCC_AHBRSTR_IOPBRST);
	}
	else if(GPIOx==GPIOC)
	{
		RCC_Enable_AHBRST(RCC_AHBRSTR_IOPCRST); 
		RCC_Disable_AHBRST(RCC_AHBRSTR_IOPCRST);
	}
	else
	{
		RCC_Enable_AHBRST(RCC_AHBRSTR_IOPDRST); 
		RCC_Disable_AHBRST(RCC_AHBRSTR_IOPDRST);
  }
}
/**
  * @brief  Initialize the GPIOx peripheral according to the specified parameters in the GPIO_Init.
  * @param  GPIOx:
	*         @arg @ref  GPIOA
	*         @arg @ref  GPIOB
	*         @arg @ref  GPIOC
	*         @arg @ref  GPIOD	
  * @param  GPIO_Init->Pin:
  *         @arg @ref  GPIO_PIN_0
  *         @arg @ref  GPIO_PIN_1
  *         @arg @ref  GPIO_PIN_2
  *         @arg @ref  GPIO_PIN_3
  *         @arg @ref  GPIO_PIN_4
  *         @arg @ref  GPIO_PIN_5
  *         @arg @ref  GPIO_PIN_6
  *         @arg @ref  GPIO_PIN_7
  * @param  GPIO_Init->Mode:
  *         @arg @ref  GPIO_MODE_INPUT
  *         @arg @ref  GPIO_MODE_OUTPUT_PP
  *         @arg @ref  GPIO_MODE_OUTPUT_OD
  *         @arg @ref  GPIO_MODE_AF_PP
  *         @arg @ref  GPIO_MODE_AF_OD
  *         @arg @ref  GPIO_MODE_ANALOG
  * @param  GPIO_Init->Alternate:
  *         @arg @ref GPIO_AF0
  *         @arg @ref GPIO_AF1
  *         @arg @ref GPIO_AF2
  *         @arg @ref GPIO_AF3
  *         @arg @ref GPIO_AF4
  *         @arg @ref GPIO_AF5
  *         @arg @ref GPIO_AF6
  *         @arg @ref GPIO_AF7
  * @param  GPIO_Init->Pull:
  *         @arg @ref GPIO_PUPDR_Floating
  *         @arg @ref GPIO_PUPDR_Pullup
  *         @arg @ref GPIO_PUPDR_Pulldown   
  * @param  GPIO_Init->Speed:
  *         @arg @ref GPIO_OSPEEDR_Low
  *         @arg @ref GPIO_OSPEEDR_Medium
  *         @arg @ref GPIO_OSPEEDR_High
  *         @arg @ref GPIO_OSPEEDR_VeryHigh	
  * @retval None
  */
void GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
	GPIO_Set_PinMode(GPIOx,GPIO_Init->Pin,(GPIO_Init->Mode)&(~(1<<4)));
  GPIO_Set_PinOutputType(GPIOx,GPIO_Init->Pin,(GPIO_Init->Mode)>>4);
	GPIO_Set_AF(GPIOx,GPIO_Init->Pin,GPIO_Init->Alternate);
	GPIO_Set_PinOutSpeed(GPIOx,GPIO_Init->Pin,GPIO_Init->Speed);
	GPIO_Set_PinPull(GPIOx,GPIO_Init->Pin,GPIO_Init->Pull);
}
