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
* File         : rx32h6xx_spi.h
* By           : RX_SD_Team
* Version      : V1.0.0
* Description  : Only rx32h6xx
*********************************************************************************************************
*/

#ifndef __rx32h6xx_SPI_H__
#define __rx32h6xx_SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "rx32h6xx.h"

/*********************************************************************************/
/*                                                                               */
/*                     Serial Peripheral Interface(SPI)                          */
/*                                                                               */
/*********************************************************************************/

/*******************  Bit definition for SPI_CR1 register  ********************/
#define SPI_CR1_CPHA                        (0x00000001)  /*!< Clock Phase */
#define SPI_CR1_CPOL                        (0x00000002)	/*!< Clock Polarity */
#define SPI_CR1_MSTR                        (0x00000004)	/*!< Master Selection */
#define SPI_CR1_BR                          (0x00000038)	/*!< BR[2:0] bits (Baud Rate Control) */
#define SPI_CR1_BR_0                        (0x00000008)
#define SPI_CR1_BR_1                        (0x00000010)
#define SPI_CR1_BR_2                        (0x00000020)
#define SPI_CR1_SPE                         (0x00000040)	/*!< SPI Enable */
#define SPI_CR1_LSBFIRST                    (0x00000080)	/*!< Frame Format */
#define SPI_CR1_SSI                         (0x00000100)	/*!< Internal slave select */
#define SPI_CR1_SSM                         (0x00000200)	/*!< Software slave management */
#define SPI_CR1_RXONLY                      (0x00000400)	/*!< Receive only */
#define SPI_CR1_DFF                         (0x00000800)	/*!< Data Frame Format */
#define SPI_CR1_BIDIOE                      (0x00004000)	/*!< Output enable in bidirectional mode */
#define SPI_CR1_BIDIMODE                    (0x00008000)	/*!< Bidirectional data mode enable */

/*******************  Bit definition for SPI_CR2 register  ********************/
#define SPI_CR2_SSOE                        (0x00000004)	/*!< SS Output Enable */
#define SPI_CR2_ERRIE                       (0x00000020)	/*!< Error Interrupt Enable */
#define SPI_CR2_RXNEIE                      (0x00000040)	/*!< RX buffer Not Empty Interrupt Enable */
#define SPI_CR2_TXEIE                       (0x00000080)	/*!< Tx buffer Empty Interrupt Enable */

/********************  Bit definition for SPI_SR register  ********************/
#define SPI_SR_RXNE                         (0x00000001)	/*!< Receive buffer Not Empty */
#define SPI_SR_TXE                          (0x00000002)	/*!< Transmit buffer Empty */
#define SPI_SR_CHSIDE                       (0x00000004)
#define SPI_SR_UDR                          (0x00000008)  /*!< CRC Error flag */
#define SPI_SR_MODF                         (0x00000020)	/*!< Mode fault */
#define SPI_SR_OVR                          (0x00000040)	/*!< Overrun flag */
#define SPI_SR_BSY                          (0x00000080)	/*!< Busy flag */

/********************  Bit definition for SPI_DR register  ********************/
#define SPI_DR_DR                           (0x0000FFFF)  /*!< Data Register */

/** @defgroup SPI_EC_MODE Operation Mode
  */
#define SPI_MODE_MASTER                     (SPI_CR1_MSTR | SPI_CR1_SSI)    /*!< Master configuration  */
#define SPI_MODE_SLAVE                      0x00000000U                     /*!< Slave configuration   */


/** @defgroup SPI_EC_PHASE Clock Phase
  */
#define SPI_PHASE_1EDGE                 		0x00000000U          /*!< First clock transition is the first data capture edge  */
#define SPI_PHASE_2EDGE                 		(SPI_CR1_CPHA)       /*!< Second clock transition is the first data capture edge */

/** @defgroup SPI_EC_POLARITY Clock Polarity
	*/
#define SPI_POLARITY_LOW               		  0x00000000U          /*!< Clock to 0 when idle */
#define SPI_POLARITY_HIGH               	 (SPI_CR1_CPOL)        /*!< Clock to 1 when idle */

/** @defgroup SPI_EC_BAUDRATEPRESCALER Baud Rate Prescaler
  */
#define SPI_BAUDRATEPRESCALER_DIV2          0x00000000U                                    /*!< BaudRate control equal to fPCLK/2   */
#define SPI_BAUDRATEPRESCALER_DIV4          (SPI_CR1_BR_0)                                 /*!< BaudRate control equal to fPCLK/4   */
#define SPI_BAUDRATEPRESCALER_DIV8          (SPI_CR1_BR_1)                                 /*!< BaudRate control equal to fPCLK/8   */
#define SPI_BAUDRATEPRESCALER_DIV16         (SPI_CR1_BR_1 | SPI_CR1_BR_0)                  /*!< BaudRate control equal to fPCLK/16  */
#define SPI_BAUDRATEPRESCALER_DIV32         (SPI_CR1_BR_2)                                 /*!< BaudRate control equal to fPCLK/32  */
#define SPI_BAUDRATEPRESCALER_DIV64         (SPI_CR1_BR_2 | SPI_CR1_BR_0)                  /*!< BaudRate control equal to fPCLK/64  */
#define SPI_BAUDRATEPRESCALER_DIV128        (SPI_CR1_BR_2 | SPI_CR1_BR_1)                  /*!< BaudRate control equal to fPCLK/128 */
#define SPI_BAUDRATEPRESCALER_DIV256        (SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0)   /*!< BaudRate control equal to fPCLK/256 */

/** @defgroup SPI_EC_BIT_ORDER Transmission Bit Order
  */
#define SPI_LSB_FIRST                       (SPI_CR1_LSBFIRST)        /*!< Data is transmitted/received with the LSB first */
#define SPI_MSB_FIRST                       0x00000000U               /*!< Data is transmitted/received with the MSB first */

/** @defgroup SPI_EC_TRANSFER_MODE Transfer Mode
  */
#define SPI_FULL_DUPLEX                      0x00000000U                         /*!< Full-Duplex mode. Rx and Tx transfer on 2 lines */
#define SPI_SIMPLEX_RX                      (SPI_CR1_RXONLY)                     /*!< Simplex Rx mode.  Rx transfer only on 1 line    */
#define SPI_HALF_DUPLEX_RX                  (SPI_CR1_BIDIMODE)                   /*!< Half-Duplex Rx mode. Rx transfer on 1 line      */
#define SPI_HALF_DUPLEX_TX                  (SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE)  /*!< Half-Duplex Tx mode. Tx transfer on 1 line      */


/** @defgroup SPI_EC_NSS_MODE Slave Select Pin Mode
  */
#define SPI_NSS_SOFT                        (SPI_CR1_SSM)                        /*!< NSS managed internally. NSS pin not used and free              */
#define SPI_NSS_HARD_INPUT                  0x00000000U                          /*!< NSS pin used in Input. Only used in Master mode                */
#define SPI_NSS_HARD_OUTPUT                 (((uint32_t)SPI_CR2_SSOE << 16U))    /*!< NSS pin used in Output. Only used in Slave mode as chip select */

/** @defgroup SPI_EC_DATAWIDTH Datawidth
  */
#define SPI_DATAWIDTH_8BIT                  0x00000000U         /*!< Data length for SPI transfer:  8 bits */
#define SPI_DATAWIDTH_16BIT                 (SPI_CR1_DFF)       /*!< Data length for SPI transfer:  16 bits */
																															  

/* SPI registers Masks */
#define SPI_CR1_CLEAR_MASK                 (SPI_CR1_CPHA    | SPI_CR1_CPOL     | SPI_CR1_MSTR   | \
                                            SPI_CR1_BR      | SPI_CR1_LSBFIRST | SPI_CR1_SSI    | \
                                            SPI_CR1_SSM     | SPI_CR1_RXONLY   | SPI_CR1_DFF    | \
                                            SPI_CR1_BIDIOE  | SPI_CR1_BIDIMODE)
                                            
/**
  * @brief  SPI Init structures definition
  */
typedef struct
{
  uint32_t TransferDirection;       /*!< Specifies the SPI unidirectional or bidirectional data mode.
                                         This parameter can be a value of @ref SPI_EC_TRANSFER_MODE.

                                         This feature can be modified afterwards using unitary function @ref SPI_SetTransferDirection().*/

  uint32_t Mode;                    /*!< Specifies the SPI mode (Master/Slave).
                                         This parameter can be a value of @ref SPI_EC_MODE.

                                         This feature can be modified afterwards using unitary function @ref SPI_SetMode().*/

  uint32_t DataWidth;               /*!< Specifies the SPI data width.
                                         This parameter can be a value of @ref SPI_EC_DATAWIDTH.

                                         This feature can be modified afterwards using unitary function @ref SPI_SetDataWidth().*/

  uint32_t ClockPolarity;           /*!< Specifies the serial clock steady state.
                                         This parameter can be a value of @ref SPI_EC_POLARITY.

                                         This feature can be modified afterwards using unitary function @ref SPI_SetClockPolarity().*/

  uint32_t ClockPhase;              /*!< Specifies the clock active edge for the bit capture.
                                         This parameter can be a value of @ref SPI_EC_PHASE.

                                         This feature can be modified afterwards using unitary function @ref SPI_SetClockPhase().*/

  uint32_t NSS;                     /*!< Specifies whether the NSS signal is managed by hardware (NSS pin) or by software using the SSI bit.
                                         This parameter can be a value of @ref SPI_EC_NSS_MODE.

                                         This feature can be modified afterwards using unitary function @ref SPI_SetNSSMode().*/

  uint32_t BaudRate;                /*!< Specifies the BaudRate prescaler value which will be used to configure the transmit and receive SCK clock.
                                         This parameter can be a value of @ref SPI_EC_BAUDRATEPRESCALER.
                                         @note The communication clock is derived from the master clock. The slave clock does not need to be set.

                                         This feature can be modified afterwards using unitary function @ref SPI_SetBaudRatePrescaler().*/

  uint32_t BitOrder;                /*!< Specifies whether data transfers start from MSB or LSB bit.
                                         This parameter can be a value of @ref SPI_EC_BIT_ORDER.

                                         This feature can be modified afterwards using unitary function @ref SPI_SetTransferBitOrder().*/


} SPI_InitTypeDef;

/**
  * @brief  Enable SPI peripheral
  * @rmtoll CR1          SPE           SPI_Enable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void SPI_Enable(SPI_TypeDef *SPIx)
{
  SET_BIT(SPIx->CR1, SPI_CR1_SPE);
}

/**
  * @brief  Disable SPI peripheral
  * @note   When disabling the SPI, follow the procedure described in the Reference Manual.
  * @rmtoll CR1          SPE           SPI_Disable
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void SPI_Disable(SPI_TypeDef *SPIx)
{
  CLEAR_BIT(SPIx->CR1, SPI_CR1_SPE);
}

/**
  * @brief  Check if SPI peripheral is enabled
  * @rmtoll CR1          SPE           SPI_Is_Enabled
  * @param  SPIx SPI Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t SPI_Is_Enabled(SPI_TypeDef *SPIx)
{
  return ((READ_BIT(SPIx->CR1, SPI_CR1_SPE) == (SPI_CR1_SPE)) ? 1UL : 0UL);
}

/**
  * @brief  Set SPI operation mode to Master or Slave
  * @note   This bit should not be changed when communication is ongoing.
  * @rmtoll CR1          MSTR          SPI_SetMode\n
  *         CR1          SSI           SPI_SetMode
  * @param  SPIx SPI Instance
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref SPI_MODE_MASTER
  *         @arg @ref SPI_MODE_SLAVE
  * @retval None
  */
__STATIC_INLINE void SPI_Set_Mode(SPI_TypeDef *SPIx, uint32_t Mode)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_MSTR | SPI_CR1_SSI, Mode);
}

/**
  * @brief  Get SPI operation mode (Master or Slave)
  * @rmtoll CR1          MSTR          SPI_GetMode\n
  *         CR1          SSI           SPI_GetMode
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref SPI_MODE_MASTER
  *         @arg @ref SPI_MODE_SLAVE
  */
__STATIC_INLINE uint32_t SPI_Get_Mode(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_MSTR | SPI_CR1_SSI));
}

/**
  * @brief  Set clock phase
  * @note   This bit should not be changed when communication is ongoing.
  *         This bit is not used in SPI TI mode.
  * @rmtoll CR1          CPHA          SPI_SetClockPhase
  * @param  SPIx SPI Instance
  * @param  ClockPhase This parameter can be one of the following values:
  *         @arg @ref SPI_PHASE_1EDGE
  *         @arg @ref SPI_PHASE_2EDGE
  * @retval None
  */
__STATIC_INLINE void SPI_Set_ClockPhase(SPI_TypeDef *SPIx, uint32_t ClockPhase)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_CPHA, ClockPhase);
}

/**
  * @brief  Get clock phase
  * @rmtoll CR1          CPHA          SPI_GetClockPhase
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref SPI_PHASE_1EDGE
  *         @arg @ref SPI_PHASE_2EDGE
  */
__STATIC_INLINE uint32_t SPI_Get_ClockPhase(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_CPHA));
}

/**
  * @brief  Set clock polarity
  * @note   This bit should not be changed when communication is ongoing.
  *         This bit is not used in SPI TI mode.
  * @rmtoll CR1          CPOL          SPI_SetClockPolarity
  * @param  SPIx SPI Instance
  * @param  ClockPolarity This parameter can be one of the following values:
  *         @arg @ref SPI_POLARITY_LOW
  *         @arg @ref SPI_POLARITY_HIGH
  * @retval None
  */
__STATIC_INLINE void SPI_Set_ClockPolarity(SPI_TypeDef *SPIx, uint32_t ClockPolarity)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_CPOL, ClockPolarity);
}

/**
  * @brief  Get clock polarity
  * @rmtoll CR1          CPOL          SPI_GetClockPolarity
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref SPI_POLARITY_LOW
  *         @arg @ref SPI_POLARITY_HIGH
  */
__STATIC_INLINE uint32_t SPI_Get_ClockPolarity(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_CPOL));
}

/**
  * @brief  Set baud rate prescaler
  * @note   These bits should not be changed when communication is ongoing. SPI BaudRate = fPCLK/Prescaler.
  * @rmtoll CR1          BR            SPI_SetBaudRatePrescaler
  * @param  SPIx SPI Instance
  * @param  BaudRate This parameter can be one of the following values:
  *         @arg @ref SPI_BAUDRATEPRESCALER_DIV2
  *         @arg @ref SPI_BAUDRATEPRESCALER_DIV4
  *         @arg @ref SPI_BAUDRATEPRESCALER_DIV8
  *         @arg @ref SPI_BAUDRATEPRESCALER_DIV16
  *         @arg @ref SPI_BAUDRATEPRESCALER_DIV32
  *         @arg @ref SPI_BAUDRATEPRESCALER_DIV64
  *         @arg @ref SPI_BAUDRATEPRESCALER_DIV128
  *         @arg @ref SPI_BAUDRATEPRESCALER_DIV256
  * @retval None
  */
__STATIC_INLINE void SPI_Set_BaudRatePrescaler(SPI_TypeDef *SPIx, uint32_t BaudRate)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_BR, BaudRate);
}

/**
  * @brief  Get baud rate prescaler
  * @rmtoll CR1          BR            SPI_GetBaudRatePrescaler
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref SPI_BAUDRATEPRESCALER_DIV2
  *         @arg @ref SPI_BAUDRATEPRESCALER_DIV4
  *         @arg @ref SPI_BAUDRATEPRESCALER_DIV8
  *         @arg @ref SPI_BAUDRATEPRESCALER_DIV16
  *         @arg @ref SPI_BAUDRATEPRESCALER_DIV32
  *         @arg @ref SPI_BAUDRATEPRESCALER_DIV64
  *         @arg @ref SPI_BAUDRATEPRESCALER_DIV128
  *         @arg @ref SPI_BAUDRATEPRESCALER_DIV256
  */
__STATIC_INLINE uint32_t SPI_Get_BaudRatePrescaler(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_BR));
}

/**
  * @brief  Set transfer bit order
  * @note   This bit should not be changed when communication is ongoing. This bit is not used in SPI TI mode.
  * @rmtoll CR1          LSBFIRST      SPI_SetTransferBitOrder
  * @param  SPIx SPI Instance
  * @param  BitOrder This parameter can be one of the following values:
  *         @arg @ref SPI_LSB_FIRST
  *         @arg @ref SPI_MSB_FIRST
  * @retval None
  */
__STATIC_INLINE void SPI_Set_TransferBitOrder(SPI_TypeDef *SPIx, uint32_t BitOrder)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_LSBFIRST, BitOrder);
}

/**
  * @brief  Get transfer bit order
  * @rmtoll CR1          LSBFIRST      SPI_GetTransferBitOrder
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref SPI_LSB_FIRST
  *         @arg @ref SPI_MSB_FIRST
  */
__STATIC_INLINE uint32_t SPI_Get_TransferBitOrder(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_LSBFIRST));
}

/**
  * @brief  Set transfer direction mode
  * @note   For Half-Duplex mode, Rx Direction is set by default.
  *         In master mode, the MOSI pin is used and in slave mode, the MISO pin is used for Half-Duplex.
  * @rmtoll CR1          RXONLY        SPI_SetTransferDirection\n
  *         CR1          BIDIMODE      SPI_SetTransferDirection\n
  *         CR1          BIDIOE        SPI_SetTransferDirection
  * @param  SPIx SPI Instance
  * @param  TransferDirection This parameter can be one of the following values:
  *         @arg @ref SPI_FULL_DUPLEX
  *         @arg @ref SPI_SIMPLEX_RX
  *         @arg @ref SPI_HALF_DUPLEX_RX
  *         @arg @ref SPI_HALF_DUPLEX_TX
  * @retval None
  */
__STATIC_INLINE void SPI_Set_TransferDirection(SPI_TypeDef *SPIx, uint32_t TransferDirection)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_RXONLY | SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE, TransferDirection);
}

/**
  * @brief  Get transfer direction mode
  * @rmtoll CR1          RXONLY        SPI_GetTransferDirection\n
  *         CR1          BIDIMODE      SPI_GetTransferDirection\n
  *         CR1          BIDIOE        SPI_GetTransferDirection
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref SPI_FULL_DUPLEX
  *         @arg @ref SPI_SIMPLEX_RX
  *         @arg @ref SPI_HALF_DUPLEX_RX
  *         @arg @ref SPI_HALF_DUPLEX_TX
  */
__STATIC_INLINE uint32_t SPI_Get_TransferDirection(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_RXONLY | SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE));
}

/**
  * @brief  Set frame data width
  * @rmtoll CR1          DFF           SPI_SetDataWidth
  * @param  SPIx SPI Instance
  * @param  DataWidth This parameter can be one of the following values:
  *         @arg @ref SPI_DATAWIDTH_8BIT
  *         @arg @ref SPI_DATAWIDTH_16BIT
  * @retval None
  */
__STATIC_INLINE void SPI_Set_DataWidth(SPI_TypeDef *SPIx, uint32_t DataWidth)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_DFF, DataWidth);
}

/**
  * @brief  Get frame data width
  * @rmtoll CR1          DFF           SPI_GetDataWidth
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref SPI_DATAWIDTH_8BIT
  *         @arg @ref SPI_DATAWIDTH_16BIT
  */
__STATIC_INLINE uint32_t SPI_Get_DataWidth(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_BIT(SPIx->CR1, SPI_CR1_DFF));
}

/**
  * @brief  Set polynomial for CRC calculation
  * @rmtoll CRCPR        CRCPOLY       SPI_SetCRCPolynomial
  * @param  SPIx SPI Instance
  * @param  CRCPoly This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFFFF
  * @retval None
  */
__STATIC_INLINE void SPI_Set_CRCPolynomial(SPI_TypeDef *SPIx, uint32_t CRCPoly)
{
  WRITE_REG(SPIx->CRCPR, (uint16_t)CRCPoly);
}

/**
  * @brief  Get polynomial for CRC calculation
  * @rmtoll CRCPR        CRCPOLY       SPI_GetCRCPolynomial
  * @param  SPIx SPI Instance
  * @retval Returned value is a number between Min_Data = 0x00 and Max_Data = 0xFFFF
  */
__STATIC_INLINE uint32_t SPI_Get_CRCPolynomial(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_REG(SPIx->CRCPR));
}

/**
  * @brief  Get Rx CRC
  * @rmtoll RXCRCR       RXCRC         SPI_GetRxCRC
  * @param  SPIx SPI Instance
  * @retval Returned value is a number between Min_Data = 0x00 and Max_Data = 0xFFFF
  */
__STATIC_INLINE uint32_t SPI_Get_RxCRC(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_REG(SPIx->RXCRCR));
}

/**
  * @brief  Get Tx CRC
  * @rmtoll TXCRCR       TXCRC         SPI_GetTxCRC
  * @param  SPIx SPI Instance
  * @retval Returned value is a number between Min_Data = 0x00 and Max_Data = 0xFFFF
  */
__STATIC_INLINE uint32_t SPI_Get_TxCRC(SPI_TypeDef *SPIx)
{
  return (uint32_t)(READ_REG(SPIx->TXCRCR));
}

/**
  * @brief  Set NSS mode
  * @note   SPI_NSS_SOFT Mode is not used in SPI TI mode.
  * @rmtoll CR1          SSM           SPI_SetNSSMode\n
  * @rmtoll CR2          SSOE          SPI_SetNSSMode
  * @param  SPIx SPI Instance
  * @param  NSS This parameter can be one of the following values:
  *         @arg @ref SPI_NSS_SOFT
  *         @arg @ref SPI_NSS_HARD_INPUT
  *         @arg @ref SPI_NSS_HARD_OUTPUT
  * @retval None
  */
__STATIC_INLINE void SPI_Set_NSSMode(SPI_TypeDef *SPIx, uint32_t NSS)
{
  MODIFY_REG(SPIx->CR1, SPI_CR1_SSM,  NSS);
  MODIFY_REG(SPIx->CR2, SPI_CR2_SSOE, ((uint32_t)(NSS >> 16U)));
}

/**
  * @brief  Get NSS mode
  * @rmtoll CR1          SSM           SPI_GetNSSMode\n
  * @rmtoll CR2          SSOE          SPI_GetNSSMode
  * @param  SPIx SPI Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref SPI_NSS_SOFT
  *         @arg @ref SPI_NSS_HARD_INPUT
  *         @arg @ref SPI_NSS_HARD_OUTPUT
  */
__STATIC_INLINE uint32_t SPI_Get_NSSMode(SPI_TypeDef *SPIx)
{
  register uint32_t Ssm  = (READ_BIT(SPIx->CR1, SPI_CR1_SSM));
  register uint32_t Ssoe = (READ_BIT(SPIx->CR2,  SPI_CR2_SSOE) << 16U);
  return (Ssm | Ssoe);
}


/**
***********************************************************************************
*@Function SPI_Get_Flag
*@brief    Get SPI Flag.
*@param  SPIx SPI Instance
*@param1   Flag:
*          @arg  SPI_SR_RXNE  
*          @arg  SPI_SR_TXE   
*          @arg  SPI_SR_CHSIDE
*          @arg  SPI_SR_UDR   
*          @arg  SPI_SR_MODF  
*          @arg  SPI_SR_OVR   
*          @arg  SPI_SR_BSY   
*@retval State of bit (1 or 0).
***********************************************************************************
  */
__STATIC_INLINE uint32_t SPI_Get_Flag(SPI_TypeDef *SPIx, uint32_t Flag)
{
	return (READ_BIT(SPIx->SR, Flag ) == Flag);
}

/**
***********************************************************************************
*@Function SPI_Clear_Flag
*@brief    Clear SPI Flag.
*@param  SPIx SPI Instance
*@param1   Flag:
*          @arg  SPI_SR_MODF
*          @arg  SPI_SR_OVR
*@retval None.
***********************************************************************************
  */
__STATIC_INLINE void SPI_Clear_Flag(SPI_TypeDef *SPIx, uint32_t Flag)
{
	__IO uint32_t tmpreg;
	switch(Flag)
	{
		case SPI_SR_MODF:
			tmpreg = SPIx->SR;
			(void) tmpreg;
			CLEAR_BIT(SPIx->CR1, SPI_CR1_SPE);
			break;
		case SPI_SR_OVR:
			tmpreg = SPIx->DR;
			(void) tmpreg;
			tmpreg = SPIx->SR;
			(void) tmpreg;
			break;
		default:;
	}
}

/**
  * @brief  Clear frame format error flag
  * @note   Clearing this flag is done by reading SPIx_SR register
  * @rmtoll SR           FRE           SPI_ClearFlag_FRE
  * @param  SPIx SPI Instance
  * @retval None
  */
__STATIC_INLINE void SPI_Clear_FlagFRE(SPI_TypeDef *SPIx)
{
  __IO uint32_t tmpreg;
  tmpreg = SPIx->SR;
  (void) tmpreg;
}

/**
***********************************************************************************
*@Function SPI_Enable_IT
*@brief    Enable SPI Iterrupt.
*@param  SPIx SPI Instance
*@param1   IT:
*          @arg  SPI_CR2_ERRIE
*          @arg  SPI_CR2_RXNEIE
*          @arg  SPI_CR2_TXEIE
*@retval None.
***********************************************************************************
  */
__STATIC_INLINE void SPI_Enable_IT(SPI_TypeDef *SPIx, uint32_t IT)
{
	SET_BIT(SPIx->CR2, IT );
}



/**
***********************************************************************************
*@Function SPI_Disable_IT
*@brief    Disable SPI Iterrupt.
*@param  SPIx SPI Instance
*@param1   IT:
*          @arg  SPI_CR2_ERRIE
*          @arg  SPI_CR2_RXNEIE
*          @arg  SPI_CR2_TXEIE
*@retval None.
***********************************************************************************
  */
__STATIC_INLINE void SPI_Disable_IT(SPI_TypeDef *SPIx, uint32_t IT)
{
	CLEAR_BIT(SPIx->CR2, IT);
}

/**
***********************************************************************************
*@Function SPI_Get_IT
*@brief    Get SPI Iterrupt.
*@param  SPIx SPI Instance
*@param1   IT:
*          @arg  SPI_CR2_ERRIE
*          @arg  SPI_CR2_RXNEIE
*          @arg  SPI_CR2_TXEIE
*@retval State of bit (1 or 0).
***********************************************************************************
  */
__STATIC_INLINE uint32_t SPI_Get_IT(SPI_TypeDef *SPIx, uint32_t IT)
{
	return ( READ_BIT(SPIx->CR2, IT) == (IT) );
}

/**
  * @brief  Get the data register address used for DMA transfer
  * @rmtoll DR           DR            SPI_Get_DMARegAddr
  * @param  SPIx SPI Instance
  * @retval Address of data register
  */
__STATIC_INLINE uint32_t SPI_Get_DMARegAddr(SPI_TypeDef *SPIx)
{
  return (uint32_t) &(SPIx->DR);
}

/**
  * @brief  Read 8-Bits in the data register
  * @rmtoll DR           DR            SPI_ReceiveData8
  * @param  SPIx SPI Instance
  * @retval RxData Value between Min_Data=0x00 and Max_Data=0xFF
  */
__STATIC_INLINE uint8_t SPI_Receive_Data8(SPI_TypeDef *SPIx)
{
  return (uint8_t)(READ_REG(SPIx->DR));
}

/**
  * @brief  Read 16-Bits in the data register
  * @rmtoll DR           DR            SPI_ReceiveData16
  * @param  SPIx SPI Instance
  * @retval RxData Value between Min_Data=0x00 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint16_t SPI_Receive_Data16(SPI_TypeDef *SPIx)
{
  return (uint16_t)(READ_REG(SPIx->DR));
}

/**
  * @brief  Write 8-Bits in the data register
  * @rmtoll DR           DR            SPI_TransmitData8
  * @param  SPIx SPI Instance
  * @param  TxData Value between Min_Data=0x00 and Max_Data=0xFF
  * @retval None
  */
__STATIC_INLINE void SPI_Transmit_Data8(SPI_TypeDef *SPIx, uint8_t TxData)
{
  *((__IO uint8_t *)&SPIx->DR) = TxData;
}

/**
  * @brief  Write 16-Bits in the data register
  * @rmtoll DR           DR            SPI_TransmitData16
  * @param  SPIx SPI Instance
  * @param  TxData Value between Min_Data=0x00 and Max_Data=0xFFFF
  * @retval None
  */
__STATIC_INLINE void SPI_Transmit_Data16(SPI_TypeDef *SPIx, uint16_t TxData)
{
  *((__IO uint16_t *)&SPIx->DR) = TxData;
}


void     SPI_StructInit(SPI_InitTypeDef *SPI_InitStruct);
void     SPI_Init(SPI_TypeDef *SPIx, SPI_InitTypeDef *SPI_InitStruct);
void     SPI_DeInit(SPI_TypeDef *SPIx);

#ifdef __cplusplus
}
#endif

#endif /* __rx32h6xx_SPI_H__ */

