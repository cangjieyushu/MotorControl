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
* File         : rx32h6xx_usart.c
* By           : RX_SD_Team
* Version      : V1.0.0
* Description  : Only rx32h6xx
*********************************************************************************************************
*/

#include "rx32h6xx_usart.h"
#include "rx32h6xx_rcc.h"

#define UART1_PUT 0
#define UART2_PUT 1

int fputc(int ch, FILE *f)
{
#if defined(UART1_PUT)
	UART1->DR = ch & 0x1FFU;
  while((UART1->SR & UART_SR_TXE) == 0);
#endif
  
#if defined(UART2_PUT)
	UART2->DR = ch & 0x1FFU;
  while((UART2->SR & UART_SR_TXE) == 0);
#endif
  return ch;
}

/**
  * @brief  De-initialize UART registers (Registers restored to their default values).
  * @param  UARTx UART Instance

  */
void UART_DeInit(UART_TypeDef *UARTx)
{
  if (UARTx == UART1)
  {
		SET_BIT(RCC->APB2RSTR,RCC_APB2RSTR_UART1RST);
		CLEAR_BIT(RCC->APB2RSTR,RCC_APB2RSTR_UART1RST);
  }
  else if (UARTx == UART2)
  {
		SET_BIT(RCC->APB1RSTR,RCC_APB1RSTR_UART2RST);
		CLEAR_BIT(RCC->APB1RSTR,RCC_APB1RSTR_UART2RST);
  }
}

/**
  * @brief Set each @ref UART_InitTypeDef field to default value.
  * @param UART_InitStruct Pointer to a @ref UART_InitTypeDef structure
  *                         whose fields will be set to default values.
  * @retval None
  */
void UART_StructInit(UART_InitTypeDef *UART_InitStruct)
{
  /* Set UART_InitStruct fields to default values */
  UART_InitStruct->BaudRate            = 9600U;
  UART_InitStruct->DataWidth           = UART_DATAWIDTH_8B;
  UART_InitStruct->StopBits            = UART_STOPBITS_1;
  UART_InitStruct->Parity              = UART_PARITY_NONE ;
  UART_InitStruct->TransferDirection   = UART_DIRECTION_TX_RX;
}

/**
  * @brief  Initialize UART registers according to the specified
  *         parameters in UART_InitStruct.
  * @note   As some bits in UART configuration registers can only be written when the UART is disabled (UART_CR1_UE bit =0),
  *         UART IP should be in disabled state prior calling this function. Otherwise, ERROR result will be returned.
  * @note   Baud rate value stored in UART_InitStruct BaudRate field, should be valid (different from 0).
  * @param  UARTx UART Instance
  * @param  UART_InitStruct pointer to a UART_InitTypeDef structure
  *         that contains the configuration information for the specified UART peripheral.
  */
void UART_Init(UART_TypeDef *UARTx, UART_InitTypeDef *UART_InitStruct)
{
  uint32_t periphclk = 0U;
	
  RCC_ClocksTypeDef rcc_clocks = {0};
	
	/* Get SYSCLK frequency */
	rcc_clocks.SYSCLK_Frequency = RCC_Get_SystemClock();  
	/* HCLK clock frequency */
	rcc_clocks.HCLK_Frequency   = RCC_Get_AHBClock(); 
	/* PCLK1 clock frequency */
	rcc_clocks.PCLK1_Frequency  = RCC_Get_APB1Clock();  
	/* PCLK2 clock frequency */
	rcc_clocks.PCLK2_Frequency  = RCC_Get_APB2Clock();  
	
  if (UART_Is_Enable(UARTx) == 0U)
  {
    MODIFY_REG(UARTx->CR1,
               (UART_CR1_M | UART_CR1_PCE | UART_CR1_PS |
                UART_CR1_TE | UART_CR1_RE),
               (UART_InitStruct->DataWidth | UART_InitStruct->Parity |
                UART_InitStruct->TransferDirection));

    UART_Set_StopBitsLength(UARTx, UART_InitStruct->StopBits);

    //RCC_GetSystemClocksFreq(&rcc_clocks);		
    if (UARTx == UART1)
    {
      periphclk = rcc_clocks.PCLK2_Frequency;
    }
    else if (UARTx == UART2)
    {
      periphclk = rcc_clocks.PCLK1_Frequency;
    }
    else {;}

    if ((periphclk != 0U) && (UART_InitStruct->BaudRate != 0U))
    {
      UART_Set_BaudRate(UARTx,periphclk,UART_InitStruct->BaudRate);
    }
  }
 
}


