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
* File         : rx32h6xx_usart.h
* By           : RX_SD_Team
* Version      : V1.0.0
* Description  : Only rx32h6xx
*********************************************************************************************************
*/

#ifndef __rx32h6xx_UART_H__
#define __rx32h6xx_UART_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "rx32h6xx.h"
#include "stdio.h"

/*********************************************************************************/
/*                                                                               */
/*       Universal synchronous asynchronous receiver transmitter (UART)         */
/*                                                                               */
/*********************************************************************************/

/*******************  Bit definition for UART_SR register  *******************/      
#define UART_SR_PE                         (0x00000001)  /*!< Parity Error */
#define UART_SR_FE                         (0x00000002)  /*!< Framing Error */
#define UART_SR_NE                         (0x00000004)  /*!< Noise Error Flag */
#define UART_SR_ORE                        (0x00000008)  /*!< OverRun Error */
#define UART_SR_IDLE                       (0x00000010)  /*!< IDLE line detected */
#define UART_SR_RXNE                       (0x00000020)  /*!< Read Data Register Not Empty */
#define UART_SR_TC                         (0x00000040)  /*!< Transmission Complete */
#define UART_SR_TXE                        (0x00000080)  /*!< Transmit Data Register Empty */
#define UART_SR_LBD                        (0x00000100)  /*!< LIN Break Detection Flag */

/*******************  Bit definition for UART_DR register  *******************/
#define UART_DR_DR                         (0x000001FF)  /*!< Data value */

/******************  Bit definition for UART_BRR register  *******************/
#define UART_BRR_DIV_Fraction              (0x0000000F)  /*!< Fraction of UARTDIV */
#define UART_BRR_DIV_Mantissa              (0x0000FFF0)  /*!< Mantissa of UARTDIV */

/******************  Bit definition for UART_CR1 register  *******************/
#define UART_CR1_SBK                       (0x00000001)  /*!< Send Break */
#define UART_CR1_RE                        (0x00000004)  /*!< Receiver Enable */
#define UART_CR1_TE                        (0x00000008)  /*!< Transmitter Enable */
#define UART_CR1_IDLEIE                    (0x00000010)  /*!< IDLE Interrupt Enable */
#define UART_CR1_RXNEIE                    (0x00000020)  /*!< RXNE Interrupt Enable */
#define UART_CR1_TCIE                      (0x00000040)  /*!< Transmission Complete Interrupt Enable */
#define UART_CR1_TXEIE                     (0x00000080)  /*!< TXE Interrupt Enable */
#define UART_CR1_PEIE                      (0x00000100)  /*!< PE Interrupt Enable */
#define UART_CR1_PS                        (0x00000200)  /*!< Parity Selection */
#define UART_CR1_PCE                       (0x00000400)  /*!< Parity Control Enable */
#define UART_CR1_M                         (0x00001000)  /*!< Word length */
#define UART_CR1_UE                        (0x00002000)  /*!< UART Enable */

/******************  Bit definition for UART_FLAG register  *******************/
#define UART_FLAG_PE                    (0x10000001)  /*!< Parity Error */
#define UART_FLAG_FE                    (0x10000002)  /*!< Framing Error */
#define UART_FLAG_NE                    (0x10000004)  /*!< Noise Error Flag */
#define UART_FLAG_ORE                   (0x10000008)  /*!< OverRun Error */
#define UART_FLAG_IDLE                  (0x10000010)  /*!< IDLE line detected */
#define UART_FLAG_RXNE                  (0x10000020)  /*!< Read Data Register Not Empty */
#define UART_FLAG_TC                    (0x10000040)  /*!< Transmission Complete */
#define UART_FLAG_TXE                   (0x10000080)  /*!< Transmit Data Register Empty */
#define UART_FLAG_LBD                   (0x10000100)  /*!< LIN Break Detection Flag */
#define UART_FLAG_SBK                   (0x20000001)  /*!< Send Break */

/******************  Bit definition for UART_CR2 register  *******************/
#define UART_CR2_ADD                       (0x0000000F)  /*!< Address of the UART node */
#define UART_CR2_LBDL                      (0x00000020)  /*!< LIN Break Detection Length */
#define UART_CR2_LBDIE                     (0x00000040)  /*!< LIN Break Detection Interrupt Enable */
#define UART_CR2_STOP                      (0x00003000)  /*!< STOP[1:0] bits (STOP bits) */
#define UART_CR2_STOP_0                    (0x00001000)  
#define UART_CR2_STOP_1                    (0x00002000)
#define UART_CR2_LINEN                     (0x00004000)  /*!< LIN mode enable */

/******************  Bit definition for UART_CR3 register  *******************/
#define UART_CR3_EIE                       (0x00000001)  /*!< Error Interrupt Enable */
#define UART_CR3_HDSEL                     (0x00000008)  /*!< Half-Duplex Selection */

/******************  Bit definition for UART_IT register  *******************/
#define UART_IT_IDLEIE                 (0x10000010)  /*!< IDLE Interrupt Enable */
#define UART_IT_RXNEIE                 (0x10000020)  /*!< RXNE Interrupt Enable */
#define UART_IT_TCIE                   (0x10000040)  /*!< Transmission Complete Interrupt Enable */
#define UART_IT_TXEIE                  (0x10000080)  /*!< TXE Interrupt Enable */
#define UART_IT_PEIE                   (0x10000100)  /*!< PE Interrupt Enable */
#define UART_IT_LBDIE                  (0x20000040)  /*!< LIN Break Detection Interrupt Enable */
#define UART_IT_EIE                    (0x40000001)  /*!< Error Interrupt Enable */


/** @defgroup UART_EC_DATAWIDTH Datawidth
  */
#define UART_DATAWIDTH_8B                   0x00000000U             /*!< 8 bits word length : Start bit, 8 data bits, n stop bits */
#define UART_DATAWIDTH_9B                   UART_CR1_M             /*!< 9 bits word length : Start bit, 9 data bits, n stop bits */

/** @defgroup UART_EC_STOPBITS Stop Bits
  */
#define UART_STOPBITS_0_5                   UART_CR2_STOP_0                           /*!< 0.5 stop bit */
#define UART_STOPBITS_1                     0x00000000U                                /*!< 1 stop bit */
#define UART_STOPBITS_1_5                   (UART_CR2_STOP_0 | UART_CR2_STOP_1)      /*!< 1.5 stop bits */
#define UART_STOPBITS_2                     UART_CR2_STOP_1                           /*!< 2 stop bits */

/** @defgroup UART_EC_PARITY Parity Control
  */
#define UART_PARITY_NONE                    0x00000000U                          /*!< Parity control disabled */
#define UART_PARITY_EVEN                    UART_CR1_PCE                        /*!< Parity control enabled and Even Parity is selected */
#define UART_PARITY_ODD                     (UART_CR1_PCE | UART_CR1_PS)       /*!< Parity control enabled and Odd Parity is selected */

/** @defgroup UART_EC_DIRECTION Communication Direction
  */
#define UART_DIRECTION_NONE                 0x00000000U                        /*!< Transmitter and Receiver are disabled */
#define UART_DIRECTION_RX                   UART_CR1_RE                       /*!< Transmitter is disabled and Receiver is enabled */
#define UART_DIRECTION_TX                   UART_CR1_TE                       /*!< Transmitter is enabled and Receiver is disabled */
#define UART_DIRECTION_TX_RX                (UART_CR1_TE |UART_CR1_RE)       /*!< Transmitter and Receiver are enabled */



/** @defgroup UART_EC_LINBREAK_DETECT LIN Break Detection Length
  */
#define UART_LINBREAK_DETECT_10B            0x00000000U           /*!< 10-bit break detection method selected */
#define UART_LINBREAK_DETECT_11B            UART_CR2_LBDL        /*!< 11-bit break detection method selected */

/**
  * @brief UART Init Structure definition
  */
typedef struct
{
  uint32_t BaudRate;                  /*!< This field defines expected Usart communication baud rate.

                                           This feature can be modified afterwards using unitary function @ref UART_Set_BaudRate().*/

  uint32_t DataWidth;                 /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref UART_EC_DATAWIDTH.

                                           This feature can be modified afterwards using unitary function @ref UART_Set_DataWidth().*/

  uint32_t StopBits;                  /*!< Specifies the number of stop bits transmitted.
                                           This parameter can be a value of @ref UART_EC_STOPBITS.

                                           This feature can be modified afterwards using unitary function @ref UART_Set_StopBitsLength().*/

  uint32_t Parity;                    /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref UART_EC_PARITY.

                                           This feature can be modified afterwards using unitary function @ref UART_Set_Parity().*/

  uint32_t TransferDirection;         /*!< Specifies whether the Receive and/or Transmit mode is enabled or disabled.
                                           This parameter can be a value of @ref UART_EC_DIRECTION.

                                           This feature can be modified afterwards using unitary function @ref UART_Set_TransferDirection().*/


} UART_InitTypeDef;

/**
  * @brief  Compute UARTDIV value according to Peripheral Clock and
  *         expected Baud Rate in 16 bits sampling mode (32 bits value of UARTDIV is returned)
  * @param  __PERIPHCLK__ Peripheral Clock frequency used for UART instance
  * @param  __BAUDRATE__ Baud rate value to achieve
  * @retval UARTDIV value to be used for BRR register filling in OverSampling_16 case
  */
#define __UART_DIV_SAMPLING16_100(__PERIPHCLK__, __BAUDRATE__)     (((__PERIPHCLK__)*25)/(4*(__BAUDRATE__)))
#define __UART_DIVMANT_SAMPLING16(__PERIPHCLK__, __BAUDRATE__)     (__UART_DIV_SAMPLING16_100((__PERIPHCLK__), (__BAUDRATE__))/100)
#define __UART_DIVFRAQ_SAMPLING16(__PERIPHCLK__, __BAUDRATE__)     (((__UART_DIV_SAMPLING16_100((__PERIPHCLK__), (__BAUDRATE__)) - (__UART_DIVMANT_SAMPLING16((__PERIPHCLK__), (__BAUDRATE__)) * 100)) * 16 + 50) / 100)
/* UART BRR = mantissa + overflow + fraction
            = (UART DIVMANT << 4) + (UART DIVFRAQ & 0xF0) + (UART DIVFRAQ & 0x0F) */
#define __UART_DIV_SAMPLING16(__PERIPHCLK__, __BAUDRATE__)            (((__UART_DIVMANT_SAMPLING16((__PERIPHCLK__), (__BAUDRATE__)) << 4) + \
                                                                           (__UART_DIVFRAQ_SAMPLING16((__PERIPHCLK__), (__BAUDRATE__)) & 0xF0)) + \
                                                                           (__UART_DIVFRAQ_SAMPLING16((__PERIPHCLK__), (__BAUDRATE__)) & 0x0F))

/**
  * @brief  UART Enable
  * @rmtoll CR1          UE            UART_Enable
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void UART_Enable(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->CR1, UART_CR1_UE);
}

/**
  * @brief  UART Disable (all UART prescalers and outputs are disabled)
  * @note   When UART is disabled, UART prescalers and outputs are stopped immediately,
  *         and current operations are discarded. The configuration of the UART is kept, but all the status
  *         flags, in the UARTx_SR are set to their default values.
  * @rmtoll CR1          UE            UART_Disable
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void UART_Disable(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->CR1, UART_CR1_UE);
}

/**
  * @brief  Indicate if UART is enabled
  * @rmtoll CR1          UE            UART_Is_Enable
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t UART_Is_Enable(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->CR1, UART_CR1_UE) == (UART_CR1_UE));
}

/**
  * @brief  Receiver Enable (Receiver is enabled and begins searching for a start bit)
  * @rmtoll CR1          RE            UART_Enable_Rx
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void UART_Enable_Rx(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->CR1, UART_CR1_RE);
}

/**
  * @brief  Receiver Disable
  * @rmtoll CR1          RE            UART_Disable_Rx
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void UART_Disable_Rx(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->CR1, UART_CR1_RE);
}

/**
  * @brief  Transmitter Enable
  * @rmtoll CR1          TE            UART_Enable_Tx
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void UART_Enable_Tx(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->CR1, UART_CR1_TE);
}

/**
  * @brief  Transmitter Disable
  * @rmtoll CR1          TE            UART_Disable_Tx
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void UART_Disable_Tx(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->CR1, UART_CR1_TE);
}

/**
  * @brief  Configure simultaneously enabled/disabled states
  *         of Transmitter and Receiver
  * @rmtoll CR1          RE            UART_Set_TransferDirection\n
  *         CR1          TE            UART_Set_TransferDirection
  * @param  UARTx UART Instance
  * @param  TransferDirection This parameter can be one of the following values:
  *         @arg @ref UART_DIRECTION_NONE
  *         @arg @ref UART_DIRECTION_RX
  *         @arg @ref UART_DIRECTION_TX
  *         @arg @ref UART_DIRECTION_TX_RX
  * @retval None
  */
__STATIC_INLINE void UART_Set_TransferDirection(UART_TypeDef *UARTx, uint32_t TransferDirection)
{
  MODIFY_REG(UARTx->CR1, UART_CR1_RE | UART_CR1_TE, TransferDirection);
}

/**
  * @brief  Return enabled/disabled states of Transmitter and Receiver
  * @rmtoll CR1          RE            UART_GetTransferDirection\n
  *         CR1          TE            UART_GetTransferDirection
  * @param  UARTx UART Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref UART_DIRECTION_NONE
  *         @arg @ref UART_DIRECTION_RX
  *         @arg @ref UART_DIRECTION_TX
  *         @arg @ref UART_DIRECTION_TX_RX
  */
__STATIC_INLINE uint32_t UART_Get_TransferDirection(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->CR1, UART_CR1_RE | UART_CR1_TE));
}

/**
  * @brief  Configure Parity (enabled/disabled and parity mode if enabled).
  * @note   This function selects if hardware parity control (generation and detection) is enabled or disabled.
  *         When the parity control is enabled (Odd or Even), computed parity bit is inserted at the MSB position
  *         (9th or 8th bit depending on data width) and parity is checked on the received data.
  * @rmtoll CR1          PS            UART_SetParity\n
  *         CR1          PCE           UART_SetParity
  * @param  UARTx UART Instance
  * @param  Parity This parameter can be one of the following values:
  *         @arg @ref UART_PARITY_NONE
  *         @arg @ref UART_PARITY_EVEN
  *         @arg @ref UART_PARITY_ODD
  * @retval None
  */
__STATIC_INLINE void UART_Set_Parity(UART_TypeDef *UARTx, uint32_t Parity)
{
  MODIFY_REG(UARTx->CR1, UART_CR1_PS | UART_CR1_PCE, Parity);
}

/**
  * @brief  Return Parity configuration (enabled/disabled and parity mode if enabled)
  * @rmtoll CR1          PS            UART_GetParity\n
  *         CR1          PCE           UART_GetParity
  * @param  UARTx UART Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref UART_PARITY_NONE
  *         @arg @ref UART_PARITY_EVEN
  *         @arg @ref UART_PARITY_ODD
  */
__STATIC_INLINE uint32_t UART_Get_Parity(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->CR1, UART_CR1_PS | UART_CR1_PCE));
}

/**
  * @brief  Set Word length (i.e. nb of data bits, excluding start and stop bits)
  * @rmtoll CR1          M             UART_SetDataWidth
  * @param  UARTx UART Instance
  * @param  DataWidth This parameter can be one of the following values:
  *         @arg @ref UART_DATAWIDTH_8B
  *         @arg @ref UART_DATAWIDTH_9B
  * @retval None
  */
__STATIC_INLINE void UART_Set_DataWidth(UART_TypeDef *UARTx, uint32_t DataWidth)
{
  MODIFY_REG(UARTx->CR1, UART_CR1_M, DataWidth);
}

/**
  * @brief  Return Word length (i.e. nb of data bits, excluding start and stop bits)
  * @rmtoll CR1          M             UART_GetDataWidth
  * @param  UARTx UART Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref UART_DATAWIDTH_8B
  *         @arg @ref UART_DATAWIDTH_9B
  */
__STATIC_INLINE uint32_t UART_Get_DataWidth(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->CR1, UART_CR1_M));
}

/**
  * @brief  Set the length of the stop bits
  * @rmtoll CR2          STOP          UART_SetStopBitsLength
  * @param  UARTx UART Instance
  * @param  StopBits This parameter can be one of the following values:
  *         @arg @ref UART_STOPBITS_0_5
  *         @arg @ref UART_STOPBITS_1
  *         @arg @ref UART_STOPBITS_1_5
  *         @arg @ref UART_STOPBITS_2
  * @retval None
  */
__STATIC_INLINE void UART_Set_StopBitsLength(UART_TypeDef *UARTx, uint32_t StopBits)
{
  MODIFY_REG(UARTx->CR2, UART_CR2_STOP, StopBits);
}

/**
  * @brief  Retrieve the length of the stop bits
  * @rmtoll CR2          STOP          UART_GetStopBitsLength
  * @param  UARTx UART Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref UART_STOPBITS_0_5
  *         @arg @ref UART_STOPBITS_1
  *         @arg @ref UART_STOPBITS_1_5
  *         @arg @ref UART_STOPBITS_2
  */
__STATIC_INLINE uint32_t UART_Get_StopBitsLength(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->CR2, UART_CR2_STOP));
}

/**
  * @brief  Configure Character frame format (Datawidth, Parity control, Stop Bits)
  * @note   Call of this function is equivalent to following function call sequence :
  *         - Data Width configuration using @ref UART_SetDataWidth() function
  *         - Parity Control and mode configuration using @ref UART_SetParity() function
  *         - Stop bits configuration using @ref UART_SetStopBitsLength() function
  * @rmtoll CR1          PS            UART_Set_Character\n
  *         CR1          PCE           UART_Set_Character\n
  *         CR1          M             UART_Set_Character\n
  *         CR2          STOP          UART_Set_Character
  * @param  UARTx UART Instance
  * @param  DataWidth This parameter can be one of the following values:
  *         @arg @ref UART_DATAWIDTH_8B
  *         @arg @ref UART_DATAWIDTH_9B
  * @param  Parity This parameter can be one of the following values:
  *         @arg @ref UART_PARITY_NONE
  *         @arg @ref UART_PARITY_EVEN
  *         @arg @ref UART_PARITY_ODD
  * @param  StopBits This parameter can be one of the following values:
  *         @arg @ref UART_STOPBITS_0_5
  *         @arg @ref UART_STOPBITS_1
  *         @arg @ref UART_STOPBITS_1_5
  *         @arg @ref UART_STOPBITS_2
  * @retval None
  */
__STATIC_INLINE void UART_Set_Character(UART_TypeDef *UARTx, uint32_t DataWidth, uint32_t Parity, uint32_t StopBits)
{
  MODIFY_REG(UARTx->CR1, UART_CR1_PS | UART_CR1_PCE | UART_CR1_M, Parity | DataWidth);
  MODIFY_REG(UARTx->CR2, UART_CR2_STOP, StopBits);
}

/**
  * @brief  Set Address of the UART node.
  * @note   This is used in multiprocessor communication during Mute mode or Stop mode,
  *         for wake up with address mark detection.
  * @rmtoll CR2          ADD           UART_SetNodeAddress
  * @param  UARTx UART Instance
  * @param  NodeAddress 4 bit Address of the UART node.
  * @retval None
  */
__STATIC_INLINE void UART_Set_NodeAddress(UART_TypeDef *UARTx, uint32_t NodeAddress)
{
  MODIFY_REG(UARTx->CR2, UART_CR2_ADD, (NodeAddress & UART_CR2_ADD));
}

/**
  * @brief  Return 4 bit Address of the UART node as set in ADD field of CR2.
  * @note   only 4bits (b3-b0) of returned value are relevant (b31-b4 are not relevant)
  * @rmtoll CR2          ADD           UART_Get_NodeAddress
  * @param  UARTx UART Instance
  * @retval Address of the UART node (Value between Min_Data=0 and Max_Data=255)
  */
__STATIC_INLINE uint32_t UART_Get_NodeAddress(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->CR2, UART_CR2_ADD));
}


/**
  * @brief  Configure UART BRR register for achieving expected Baud Rate value.
  * @note   Compute and set UARTDIV value in BRR Register (full BRR content)
  *         according to used Peripheral Clock, Oversampling mode, and expected Baud Rate values
  * @note   Peripheral clock and Baud rate values provided as function parameters should be valid
  *         (Baud rate value != 0)
  * @rmtoll BRR          BRR           UART_Set_BaudRate
  * @param  UARTx UART Instance
  * @param  PeriphClk Peripheral Clock
  * @param  BaudRate Baud Rate
  * @retval None
  */
__STATIC_INLINE void UART_Set_BaudRate(UART_TypeDef *UARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
  UARTx->BRR = (uint16_t)(__UART_DIV_SAMPLING16(PeriphClk, BaudRate));
}

/**
  * @brief  Return current Baud Rate value, according to UARTDIV present in BRR register
  *         (full BRR content), and to used Peripheral Clock and Oversampling mode values
  * @note   In case of non-initialized or invalid value stored in BRR register, value 0 will be returned.
  * @rmtoll BRR          BRR           UART_Get_BaudRate
  * @param  UARTx UART Instance
  * @param  PeriphClk Peripheral Clock
  * @retval Baud Rate
  */
__STATIC_INLINE uint32_t UART_Get_BaudRate(UART_TypeDef *UARTx, uint32_t PeriphClk)
{
  register uint32_t usartdiv = 0x0U;
  register uint32_t brrresult = 0x0U;

  usartdiv = UARTx->BRR;

  if ((usartdiv & 0xFFFFU) != 0U)
  {
    brrresult = PeriphClk / usartdiv;
  }
  return (brrresult);
}

/**
  * @brief  Enable Single Wire Half-Duplex mode
  * @note   Macro @ref IS_UART_HALFDUPLEX_INSTANCE(UARTx) can be used to check whether or not
  *         Half-Duplex mode is supported by the UARTx instance.
  * @rmtoll CR3          HDSEL         UART_EnableHalfDuplex
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void UART_Enable_HalfDuplex(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->CR3, UART_CR3_HDSEL);
}

/**
  * @brief  Disable Single Wire Half-Duplex mode
  * @note   Macro @ref IS_UART_HALFDUPLEX_INSTANCE(UARTx) can be used to check whether or not
  *         Half-Duplex mode is supported by the UARTx instance.
  * @rmtoll CR3          HDSEL         UART_DisableHalfDuplex
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void UART_Disable_HalfDuplex(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->CR3, UART_CR3_HDSEL);
}

/**
  * @brief  Indicate if Single Wire Half-Duplex mode is enabled
  * @note   Macro @ref IS_UART_HALFDUPLEX_INSTANCE(UARTx) can be used to check whether or not
  *         Half-Duplex mode is supported by the UARTx instance.
  * @rmtoll CR3          HDSEL         UART_Get_HalfDuplex
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t UART_Get_HalfDuplex(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->CR3, UART_CR3_HDSEL) == (UART_CR3_HDSEL));
}

/**
  * @brief  Set LIN Break Detection Length
  * @note   Macro @ref IS_UART_LIN_INSTANCE(UARTx) can be used to check whether or not
  *         LIN feature is supported by the UARTx instance.
  * @rmtoll CR2          LBDL          UART_SetLINBrkDetectionLen
  * @param  UARTx UART Instance
  * @param  LINBDLength This parameter can be one of the following values:
  *         @arg @ref UART_LINBREAK_DETECT_10B
  *         @arg @ref UART_LINBREAK_DETECT_11B
  * @retval None
  */
__STATIC_INLINE void UART_Set_LINBrkDetectionLen(UART_TypeDef *UARTx, uint32_t LINBDLength)
{
  MODIFY_REG(UARTx->CR2, UART_CR2_LBDL, LINBDLength);
}

/**
  * @brief  Return LIN Break Detection Length
  * @note   Macro @ref IS_UART_LIN_INSTANCE(UARTx) can be used to check whether or not
  *         LIN feature is supported by the UARTx instance.
  * @rmtoll CR2          LBDL          UART_GetLINBrkDetectionLen
  * @param  UARTx UART Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref UART_LINBREAK_DETECT_10B
  *         @arg @ref UART_LINBREAK_DETECT_11B
  */
__STATIC_INLINE uint32_t UART_Get_LINBrkDetectionLen(UART_TypeDef *UARTx)
{
  return (uint32_t)(READ_BIT(UARTx->CR2, UART_CR2_LBDL));
}

/**
  * @brief  Enable LIN mode
  * @note   Macro @ref IS_UART_LIN_INSTANCE(UARTx) can be used to check whether or not
  *         LIN feature is supported by the UARTx instance.
  * @rmtoll CR2          LINEN         UART_EnableLIN
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void UART_Enable_LIN(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->CR2, UART_CR2_LINEN);
}

/**
  * @brief  Disable LIN mode
  * @note   Macro @ref IS_UART_LIN_INSTANCE(UARTx) can be used to check whether or not
  *         LIN feature is supported by the UARTx instance.
  * @rmtoll CR2          LINEN         UART_DisableLIN
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void UART_Disable_LIN(UART_TypeDef *UARTx)
{
  CLEAR_BIT(UARTx->CR2, UART_CR2_LINEN);
}

/**
  * @brief  Indicate if LIN mode is enabled
  * @note   Macro @ref IS_UART_LIN_INSTANCE(UARTx) can be used to check whether or not
  *         LIN feature is supported by the UARTx instance.
  * @rmtoll CR2          LINEN         UART_Get_LIN
  * @param  UARTx UART Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t UART_Get_LIN(UART_TypeDef *UARTx)
{
  return (READ_BIT(UARTx->CR2, UART_CR2_LINEN) == (UART_CR2_LINEN));
}


/**
***********************************************************************************
*@Function UART_Get_Flag
*@brief    Get UART Flag.
*@param  UARTx UART Instance
*@param1   Flag:
*          @arg  UART_FLAG_PE  
*          @arg  UART_FLAG_FE  
*          @arg  UART_FLAG_NE  
*          @arg  UART_FLAG_ORE 
*          @arg  UART_FLAG_IDLE
*          @arg  UART_FLAG_RXNE
*          @arg  UART_FLAG_TC  
*          @arg  UART_FLAG_TXE  
*          @arg  UART_FLAG_LBD 
*          @arg  UART_FLAG_SBK 
*@retval State of bit (1 or 0).
***********************************************************************************
  */
__STATIC_INLINE uint32_t UART_Get_Flag(UART_TypeDef *UARTx, uint32_t Flag)
{	
	if((Flag&0x10000000)==0x10000000)
	{
		return (READ_BIT(UARTx->SR, (Flag&0xFFFFFFF) ) == (Flag&0xFFFFFFF));
	}
	else if((Flag&0x20000000)==0x20000000)
	{
		return (READ_BIT(UARTx->CR1, (Flag&0x1FFFFFFF) ) == (Flag&0x1FFFFFFF));
	}
	return 0;
}

/**
***********************************************************************************
*@Function UART_Clear_Flag
*@brief    Clear UART Flag.
*@param  UARTx UART Instance
*@param1   Flag:
*          @arg  UART_FLAG_PE  
*          @arg  UART_FLAG_FE  
*          @arg  UART_FLAG_NE  
*          @arg  UART_FLAG_ORE 
*          @arg  UART_FLAG_IDLE
*          @arg  UART_FLAG_RXNE
*          @arg  UART_FLAG_TC  
*          @arg  UART_FLAG_TXE  
*          @arg  UART_FLAG_LBD 
*          @arg  UART_FLAG_SBK  
*@retval None.
***********************************************************************************
  */
__STATIC_INLINE void UART_Clear_Flag(UART_TypeDef *UARTx, uint32_t Flag)
{	
	if((Flag==UART_FLAG_PE)|(Flag==UART_FLAG_FE)|(Flag==UART_FLAG_NE)|(Flag==UART_FLAG_ORE)|(Flag==UART_FLAG_IDLE))
	{
		__IO uint32_t tmpreg;
	  tmpreg = UARTx->SR;
	  (void) tmpreg;
	  tmpreg = UARTx->DR;
	  (void) tmpreg;
	}
	else if((Flag&0x10000000)==0x10000000)
	{
		WRITE_REG(UARTx->SR, ~(Flag&0xFFFFFFF) );
	}
	else if((Flag&0x20000000)==0x20000000)
	{
		CLEAR_BIT(UARTx->CR1, (Flag&0x1FFFFFFF) );
	}
}


/**
***********************************************************************************
*@Function UART_Enable_IT
*@brief    Enable UART Iterrupt.
*@param  UARTx UART Instance
*@param1   IT:
*          @arg  UART_IT_IDLEIE
*          @arg  UART_IT_RXNEIE
*          @arg  UART_IT_TCIE  
*          @arg  UART_IT_TXEIE 
*          @arg  UART_IT_PEIE  
*          @arg  UART_IT_LBDIE 
*          @arg  UART_IT_EIE   
*@retval None.
***********************************************************************************
  */
__STATIC_INLINE void UART_Enable_IT(UART_TypeDef *UARTx, uint32_t IT)
{
	if((IT&0x10000000)==0x10000000)
	{
		SET_BIT(UARTx->CR1, (IT&0xFFFFFFF) );
	}
	else if((IT&0x20000000)==0x20000000)
	{
		SET_BIT(UARTx->CR2, (IT&0x1FFFFFFF) );
	}
	else if((IT&0x40000000)==0x40000000)
	{
		SET_BIT(UARTx->CR3, (IT&0x3FFFFFFF) );
	}	
}

/**
***********************************************************************************
*@Function UART_Disable_IT
*@brief    Disable UART Iterrupt.
*@param  UARTx UART Instance
*@param1   IT:
*          @arg  UART_IT_IDLEIE
*          @arg  UART_IT_RXNEIE
*          @arg  UART_IT_TCIE  
*          @arg  UART_IT_TXEIE 
*          @arg  UART_IT_PEIE  
*          @arg  UART_IT_LBDIE 
*          @arg  UART_IT_EIE    
*@retval None.
***********************************************************************************
  */
__STATIC_INLINE void UART_Disable_IT(UART_TypeDef *UARTx, uint32_t IT)
{	
	if((IT&0x10000000)==0x10000000)
	{
		CLEAR_BIT(UARTx->CR1, (IT&0xFFFFFFF) );
	}
	else if((IT&0x20000000)==0x20000000)
	{
		CLEAR_BIT(UARTx->CR2, (IT&0x1FFFFFFF) );
	}
	else if((IT&0x40000000)==0x40000000)
	{
		CLEAR_BIT(UARTx->CR3, (IT&0x3FFFFFFF) );
	}	
}

/**
***********************************************************************************
*@Function UART_Get_IT
*@brief    Get UART Iterrupt.
*@param  UARTx UART Instance
*@param1   IT:
*          @arg  UART_IT_IDLEIE
*          @arg  UART_IT_RXNEIE
*          @arg  UART_IT_TCIE  
*          @arg  UART_IT_TXEIE 
*          @arg  UART_IT_PEIE  
*          @arg  UART_IT_LBDIE 
*          @arg  UART_IT_EIE   
*@retval State of bit (1 or 0).
***********************************************************************************
  */
__STATIC_INLINE uint32_t UART_Get_IT(UART_TypeDef *UARTx, uint32_t IT)
{	
	if((IT&0x10000000)==0x10000000)
	{
		return (READ_BIT(UARTx->CR1, (IT&0xFFFFFFF) ) == (IT&0xFFFFFFF));
	}
	else if((IT&0x20000000)==0x20000000)
	{
		return (READ_BIT(UARTx->CR2, (IT&0x1FFFFFFF) ) == (IT&0x1FFFFFFF));
	}
	else if((IT&0x40000000)==0x40000000)
	{
		return (READ_BIT(UARTx->CR3, (IT&0x3FFFFFFF) ) == (IT&0x3FFFFFFF));
	}
	return 0;
}

/**
  * @brief  Get the data register address used for DMA transfer
  * @rmtoll DR           DR            UART_Get_DMARegAddr
  * @note   Address of Data Register is valid for both Transmit and Receive transfers.
  * @param  UARTx UART Instance
  * @retval Address of data register
  */
__STATIC_INLINE uint32_t UART_Get_DMARegAddr(UART_TypeDef *UARTx)
{
  /* return address of DR register */
  return ((uint32_t) & (UARTx->DR));
}

/**
  * @brief  Read Receiver Data register (Receive Data value, 8 bits)
  * @rmtoll DR           DR            UART_ReceiveData8
  * @param  UARTx UART Instance
  * @retval Value between Min_Data=0x00 and Max_Data=0xFF
  */
__STATIC_INLINE uint8_t UART_Receive_Data8(UART_TypeDef *UARTx)
{
  return (uint8_t)(READ_BIT(UARTx->DR, UART_DR_DR));
}

/**
  * @brief  Read Receiver Data register (Receive Data value, 9 bits)
  * @rmtoll DR           DR            UART_ReceiveData9
  * @param  UARTx UART Instance
  * @retval Value between Min_Data=0x00 and Max_Data=0x1FF
  */
__STATIC_INLINE uint16_t UART_Receive_Data9(UART_TypeDef *UARTx)
{
  return (uint16_t)(READ_BIT(UARTx->DR, UART_DR_DR));
}

/**
  * @brief  Write in Transmitter Data Register (Transmit Data value, 8 bits)
  * @rmtoll DR           DR            UART_TransmitData8
  * @param  UARTx UART Instance
  * @param  Value between Min_Data=0x00 and Max_Data=0xFF
  * @retval None
  */
__STATIC_INLINE void UART_Transmit_Data8(UART_TypeDef *UARTx, uint8_t Value)
{
  UARTx->DR = Value;
}

/**
  * @brief  Write in Transmitter Data Register (Transmit Data value, 9 bits)
  * @rmtoll DR           DR            UART_TransmitData9
  * @param  UARTx UART Instance
  * @param  Value between Min_Data=0x00 and Max_Data=0x1FF
  * @retval None
  */
__STATIC_INLINE void UART_Transmit_Data9(UART_TypeDef *UARTx, uint16_t Value)
{
  UARTx->DR = Value & 0x1FFU;
}

/**
  * @brief  Request Break sending
  * @rmtoll CR1          SBK           UART_RequestBreakSending
  * @param  UARTx UART Instance
  * @retval None
  */
__STATIC_INLINE void UART_Request_BreakSending(UART_TypeDef *UARTx)
{
  SET_BIT(UARTx->CR1, UART_CR1_SBK);
}

void     UART_DeInit(UART_TypeDef *UARTx);
void	   UART_StructInit(UART_InitTypeDef *UART_InitStruct);
void     UART_Init(UART_TypeDef *UARTx, UART_InitTypeDef *UART_InitStruct);

#ifdef __cplusplus
}
#endif

#endif /* __rx32h6xx_UART_H__ */
