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
* File         : rx32h6xx_spi.c
* By           : RX_SD_Team
* Version      : V1.0.0
* Description  : Only rx32h6xx
*********************************************************************************************************
*/

#include "rx32h6xx_spi.h"
#include "rx32h6xx_rcc.h"

/**
  * @brief  De-initialize the SPI registers to their default reset values.
  * @param  SPIx SPI Instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: SPI registers are de-initialized
  *          - ERROR: SPI registers are not de-initialized
  */
void SPI_DeInit(SPI_TypeDef *SPIx)
{
  if (SPIx == SPI1)
  {
		SET_BIT(RCC->APB2RSTR,RCC_APB2ENR_SPI1EN);
		CLEAR_BIT(RCC->APB2RSTR,RCC_APB2ENR_SPI1EN);
  }
}


/**
  * @brief  Set each @ref LL_SPI_InitTypeDef field to default value.
  * @param  SPI_InitStruct pointer to a @ref LL_SPI_InitTypeDef structure
  * whose fields will be set to default values.
  * @retval None
  */
void SPI_StructInit(SPI_InitTypeDef *SPI_InitStruct)
{
  /* Set SPI_InitStruct fields to default values */
  SPI_InitStruct->TransferDirection = SPI_FULL_DUPLEX;
  SPI_InitStruct->Mode              = SPI_MODE_SLAVE;
  SPI_InitStruct->DataWidth         = SPI_DATAWIDTH_8BIT;
  SPI_InitStruct->ClockPolarity     = SPI_POLARITY_LOW;
  SPI_InitStruct->ClockPhase        = SPI_PHASE_1EDGE;
  SPI_InitStruct->NSS               = SPI_NSS_HARD_INPUT;
  SPI_InitStruct->BaudRate          = SPI_BAUDRATEPRESCALER_DIV2;
  SPI_InitStruct->BitOrder          = SPI_MSB_FIRST;
}

/**
  * @brief  Initialize the SPI registers according to the specified parameters in SPI_InitStruct.
  * @note   As some bits in SPI configuration registers can only be written when the SPI is disabled (SPI_CR1_SPE bit =0),
  *         SPI peripheral should be in disabled state prior calling this function. Otherwise, ERROR result will be returned.
  * @param  SPIx SPI Instance
  * @param  TransferDirection:
  *         @arg @ref SPI_FULL_DUPLEX
  *         @arg @ref SPI_SIMPLEX_RX
  *         @arg @ref SPI_HALF_DUPLEX_RX
  *         @arg @ref SPI_HALF_DUPLEX_TX
  * @param  Mode:  
  *         @arg @ref SPI_MODE_MASTER
  *         @arg @ref SPI_MODE_SLAVE
  * @param  DataWidth:  
  *         @arg @ref SPI_DATAWIDTH_8BIT 
  *         @arg @ref SPI_DATAWIDTH_16BIT
  * @param  ClockPolarity:  
  *         @arg @ref SPI_POLARITY_LOW  
  *         @arg @ref SPI_POLARITY_HIGH
  * @param  ClockPhase:  
  *         @arg @ref SPI_PHASE_1EDGE  
  *         @arg @ref SPI_PHASE_2EDGE
  * @param  NSS:  
  *         @arg @ref SPI_NSS_SOFT  
  *         @arg @ref SPI_NSS_HARD_INPUT
  *         @arg @ref SPI_NSS_HARD_OUTPUT
  * @param  BaudRate:
  *         @arg @ref SPI_BAUDRATEPRESCALER_DIV2  
  *         @arg @ref SPI_BAUDRATEPRESCALER_DIV4  
  *         @arg @ref SPI_BAUDRATEPRESCALER_DIV8  
  *         @arg @ref SPI_BAUDRATEPRESCALER_DIV16 
  *         @arg @ref SPI_BAUDRATEPRESCALER_DIV32 
  *         @arg @ref SPI_BAUDRATEPRESCALER_DIV64 
  *         @arg @ref SPI_BAUDRATEPRESCALER_DIV128
  *         @arg @ref SPI_BAUDRATEPRESCALER_DIV256
  * @param  BitOrder:  
  *         @arg @ref SPI_LSB_FIRST  
  *         @arg @ref SPI_MSB_FIRST
  * @retval An ErrorStatus enumeration value. (Return always SUCCESS)
  */
void SPI_Init(SPI_TypeDef *SPIx, SPI_InitTypeDef *SPI_InitStruct)
{
  if (SPI_Is_Enabled(SPIx) == 0x00000000U)
  {
    MODIFY_REG(SPIx->CR1, 
               SPI_CR1_CLEAR_MASK,
               SPI_InitStruct->TransferDirection | SPI_InitStruct->Mode | SPI_InitStruct->DataWidth |
               SPI_InitStruct->ClockPolarity | SPI_InitStruct->ClockPhase |
               SPI_InitStruct->NSS | SPI_InitStruct->BaudRate |
               SPI_InitStruct->BitOrder );

    /*---------------------------- SPIx CR2 Configuration ------------------------
     * Configure SPIx CR2 with parameters:
     * - NSS management:     SSOE bit
     */
    MODIFY_REG(SPIx->CR2, SPI_CR2_SSOE, (SPI_InitStruct->NSS >> 16U));
  }
}




