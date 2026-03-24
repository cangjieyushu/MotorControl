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
* File         : rx32h6xx_i2c.h
* By           : RX_SD_Team
* Version      : V1.0.0
* Description  : Only rx32h6xx
*********************************************************************************************************
*/
#ifndef _rx32h6xx_I2C_H
#define _rx32h6xx_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rx32h6xx.h"
#include "rx32h6xx_rcc.h"

typedef struct
{
 uint32_t ClockSpeed;          /*!< Specifies the clock frequency.
                                     This parameter must be set to a value lower than 400kHz (in Hz)

                                     This feature can be modified afterwards using unitary function @ref I2C_SetClockPeriod()
                                     or @ref LL_I2C_SetDutyCycle() or @ref I2C_SetClockSpeedMode() or @ref I2C_ConfigSpeed(). */

  uint32_t DutyCycle;           /*!< Specifies the I2C fast mode duty cycle.
                                     This parameter can be a value of @ref I2C_EC_DUTYCYCLE

                                     This feature can be modified afterwards using unitary function @ref I2C_SetDutyCycle(). */

  uint32_t OwnAddress1;         /*!< Specifies the device own address 1.
                                     This parameter must be a value between Min_Data = 0x00 and Max_Data = 0x3FF

                                     This feature can be modified afterwards using unitary function @ref I2C_Set_OwnAddress1(). */

  uint32_t TypeAcknowledge;     /*!< Specifies the ACKnowledge or Non ACKnowledge condition after the address receive match code or next received byte.
                                     This parameter can be a value of @ref I2C_EC_I2C_ACKNOWLEDGE

                                     This feature can be modified afterwards using unitary function @ref I2C_Set_AcknowledgeNextData(). */

  uint32_t OwnAddrSize;         /*!< Specifies the device own address 1 size (7-bit or 10-bit).
                                     This parameter can be a value of @ref I2C_EC_OWNADDRESS1

                                     This feature can be modified afterwards using unitary function @ref I2C_Set_OwnAddress1(). */
} I2C_InitTypeDef;

/******************************************************************************/
/*                                                                            */
/*                      Inter-integrated Circuit Interface                    */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for I2C_CR1 register  ********************/
#define I2C_CR1_PE                          0x00000001                  /*!< Peripheral Enable */
#define I2C_CR1_ENGC                        0x00000040                  /*!< General Call Enable */
#define I2C_CR1_NOSTRETCH                   0x00000080                  /*!< Clock Stretching Disable (Slave mode) */
#define I2C_CR1_START                       0x00000100                  /*!< Start Generation */
#define I2C_CR1_STOP                        0x00000200                  /*!< Stop Generation */
#define I2C_CR1_ACK                         0x00000400                  /*!< Acknowledge Enable */
#define I2C_CR1_NACK                        0x00000000                  /*!< Acknowledge Disable */
#define I2C_CR1_POS                         0x00000800                  /*!< Acknowledge/PEC Position (for data reception) */
#define I2C_CR1_SWRST                       0x00008000                  /*!< Software Reset */

/*******************  Bit definition for I2C_CR2 register  ********************/
#define I2C_CR2_FREQ                        0x0000003F                   /*!< FREQ[5:0] bits (Peripheral Clock Frequency) */
#define I2C_CR2_FREQ_0                      0x00000001                   /*!< 0x00000001 */
#define I2C_CR2_FREQ_1                      0x00000002                   /*!< 0x00000002 */
#define I2C_CR2_FREQ_2                      0x00000004                   /*!< 0x00000004 */
#define I2C_CR2_FREQ_3                      0x00000008                   /*!< 0x00000008 */
#define I2C_CR2_FREQ_4                      0x00000010                   /*!< 0x00000010 */
#define I2C_CR2_FREQ_5                      0x00000020                   /*!< 0x00000020 */

#define I2C_CR2_ITERREN                     0x00000100                   /*!< Error Interrupt Enable */
#define I2C_CR2_ITEVTEN                     0x00000200                   /*!< Event Interrupt Enable */
#define I2C_CR2_ITBUFEN                     0x00000400                   /*!< Buffer Interrupt Enable */

/*******************  Bit definition for I2C_OAR1 register  *******************/
#define I2C_OAR1_ADD1_7                     0x000040FEU                  /*!< Interface Address */
#define I2C_OAR1_ADD8_9                     0x00004300U                  /*!< Interface Address */

#define I2C_OAR1_ADD0                       0x00004001                   /*!< Bit 0 */

#define I2C_OAR1_ADDMODE                    0x0000C000                   /*!< Addressing Mode (Slave mode) */
  
#define I2C_OWNADDRESS1_7BIT                0x00004000U                  /*!< Own address 1 is a 7-bit address.   */
#define I2C_OWNADDRESS1_10BIT            (uint32_t)(I2C_OAR1_ADDMODE | 0x00004000U) /*!< Own address 1 is a 10-bit address.  */
	
/*******************  Bit definition for I2C_OAR2 register  *******************/
#define I2C_OAR2_ENDUAL                     0x00000001                   /*!< Dual addressing mode enable */
#define I2C_OAR2_ADD2                       0x000000FEU                  /*!< Interface address */

/********************  Bit definition for I2C_DR register  ********************/
#define I2C_DR_DR                           0x000000FFU                  /*!< 8-bit Data Register         */

/*******************  Bit definition for I2C_SR1 register  ********************/
#define I2C_SR1_SB                       0x00000001              /*!< Start Bit (master mode)                   */
#define I2C_SR1_ADDR                     0x00000002              /*!< Address sent (master mode) or                                                                         Address matched flag (slave mode)         */
#define I2C_SR1_BTF                      0x00000004              /*!< Byte Transfer Finished flag               */
#define I2C_SR1_ADD10                    0x00000008              /*!< 10-bit header sent (master mode)          */
#define I2C_SR1_STOPF                    0x00000010              /*!< Stop detection flag (slave mode)          */
#define I2C_SR1_RXNE                     0x00000040              /*!< Data register not empty (receivers)       */
#define I2C_SR1_TXE                      0x00000080              /*!< Data register empty (transmitters)        */
#define I2C_SR1_BERR                     0x00000100              /*!< Bus error                                 */
#define I2C_SR1_ARLO                     0x00000200              /*!< Arbitration lost                          */
#define I2C_SR1_AF                       0x00000400              /*!< Acknowledge failure flag                  */
#define I2C_SR1_OVR                      0x00000800              /*!< Overrun/Underrun                          */
#define I2C_SR1_TIMEOUT                  0x00004000              /*!< Timeout detection flag (SMBus mode)       */

/*******************  Bit definition for I2C_SR2 register  ********************/
#define I2C_SR2_MSL                      0x00000001              /*!< Master/Slave flag                         */
#define I2C_SR2_BUSY                     0x00000002              /*!< Bus busy flag                             */
#define I2C_SR2_TRA                      0x00000004              /*!< Transmitter/receiver direction            */
#define I2C_SR2_GENCALL                  0x00000010              /*!< General call address (Slave mode)         */
#define I2C_SR2_DUALF                    0x00000080              /*!< Dual flag  (Slave mode)                   */


#define I2C_DIRECTION_WRITE              I2C_SR2_TRA             /*!< Bus is in write transfer */
#define I2C_DIRECTION_READ               0x00000000U             /*!< Bus is in read transfer  */

/*******************  Bit definition for I2C_CCR register  ********************/
#define I2C_CCR_CCR                      0x00000FFFU             /*!< Clock Control Register in Fast/Standard mode (Master mode) */

#define I2C_CCR_DUTY                     0x00004000              /*!< Fast Mode Duty Cycle */
#define I2C_DUTYCYCLE_2                  0x00000000U             /*!< I2C fast mode Tlow/Thigh = 2        */
#define I2C_DUTYCYCLE_16_9               I2C_CCR_DUTY            /*!< I2C fast mode Tlow/Thigh = 16/9     */


#define I2C_CCR_FS                       0x00008000              /*!< I2C Master Mode Selection */
#define I2C_STANDARD_MODE                0x00000000U             /*!< Master clock speed range is standard mode */
#define I2C_FAST_MODE                    I2C_CCR_FS              /*!< Master clock speed range is fast mode     */

/******************  Bit definition for I2C_TRISE register  *******************/
#define I2C_TRISE_TRISE                  0x0000003FU             /*!< Maximum Rise Time in Fast/Standard mode (Master mode) */


/*******************  Bit definition for I2C_FLAG register  ********************/
#define I2C_FLAG_SB                       0x10000001              /*!< Start Bit (master mode)                   */
#define I2C_FLAG_ADDR                     0x10000002              /*!< Address sent (master mode) or                                                                         Address matched flag (slave mode)         */
#define I2C_FLAG_BTF                      0x10000004              /*!< Byte Transfer Finished flag               */
#define I2C_FLAG_ADD10                    0x10000008              /*!< 10-bit header sent (master mode)          */
#define I2C_FLAG_STOPF                    0x10000010              /*!< Stop detection flag (slave mode)          */
#define I2C_FLAG_RXNE                     0x10000040              /*!< Data register not empty (receivers)       */
#define I2C_FLAG_TXE                      0x10000080              /*!< Data register empty (transmitters)        */
#define I2C_FLAG_BERR                     0x10000100              /*!< Bus error                                 */
#define I2C_FLAG_ARLO                     0x10000200              /*!< Arbitration lost                          */
#define I2C_FLAG_AF                       0x10000400              /*!< Acknowledge failure flag                  */
#define I2C_FLAG_OVR                      0x10000800              /*!< Overrun/Underrun                          */
#define I2C_FLAG_TIMEOUT                  0x10004000              /*!< Timeout detection flag (SMBus mode)       */
#define I2C_FLAG_MSL                      0x20000001              /*!< Master/Slave flag                          */
#define I2C_FLAG_BUSY                     0x20000002              /*!< Bus busy flag                              */
#define I2C_FLAG_GENCALL                  0x20000010              /*!< General call address (Slave mode)         */
#define I2C_FLAG_DUALF                    0x20000080              /*!< Dual flag  (Slave mode)                   */

/* Defines used to perform compute and check in the macros */
#define I2C_MAX_SPEED_STANDARD           100000U
#define I2C_MAX_SPEED_FAST               400000U
/**
  * @brief  Compute I2C Clock rising time.
  * @param  __FREQRANGE__ This parameter must be a value of peripheral clock (in Mhz).
  * @param  __SPEED__ This parameter must be a value lower than 400kHz (in Hz).
  * @retval Value between Min_Data=0x02 and Max_Data=0x3F
  */
#define __I2C_RISE_TIME(__FREQRANGE__, __SPEED__)                    (uint32_t)(((__SPEED__) <= I2C_MAX_SPEED_STANDARD) ? ((__FREQRANGE__) + 1U) : ((((__FREQRANGE__) * 300U) / 1000U) + 1U))

/**
  * @brief  Compute Speed Fast clock range to a Clock Control Register (I2C_CCR_CCR) value.
  * @param  __PCLK__ This parameter must be a value of peripheral clock (in Hz).
  * @param  __SPEED__ This parameter must be a value between Min_Data=100Khz and Max_Data=400Khz (in Hz).
  * @param  __DUTYCYCLE__ This parameter can be one of the following values:
  *         @arg @ref I2C_DUTYCYCLE_2
  *         @arg @ref I2C_DUTYCYCLE_16_9
  * @retval Value between Min_Data=0x001 and Max_Data=0xFFF
  */
#define __I2C_SPEED_FAST_TO_CCR(__PCLK__, __SPEED__, __DUTYCYCLE__)  (uint32_t)(((__DUTYCYCLE__) == I2C_DUTYCYCLE_2)? \
                                                                            (((((__PCLK__) / ((__SPEED__) * 3U)) & I2C_CCR_CCR) == 0U)? 1U:((__PCLK__) / ((__SPEED__) * 3U))) : \
                                                                            (((((__PCLK__) / ((__SPEED__) * 25U)) & I2C_CCR_CCR) == 0U)? 1U:((__PCLK__) / ((__SPEED__) * 25U))))
/**
  * @brief  Compute Speed Standard clock range to a Clock Control Register (I2C_CCR_CCR) value.
  * @param  __PCLK__ This parameter must be a value of peripheral clock (in Hz).
  * @param  __SPEED__ This parameter must be a value lower than 100kHz (in Hz).
  * @retval Value between Min_Data=0x004 and Max_Data=0xFFF.
  */
#define __I2C_SPEED_STANDARD_TO_CCR(__PCLK__, __SPEED__)             (uint32_t)(((((__PCLK__)/((__SPEED__) << 1U)) & I2C_CCR_CCR) < 4U)? 4U:((__PCLK__) / ((__SPEED__) << 1U)))


/**
  * @brief  Enable I2C peripheral (PE = 1).
  * @rmtoll CR1          PE            I2C_Enable
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void I2C_Enable(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CR1, I2C_CR1_PE);
}

/**
  * @brief  Disable I2C peripheral (PE = 0).
  * @rmtoll CR1          PE            I2C_Disable
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void I2C_Disable(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CR1, I2C_CR1_PE);
}
/**
  * @brief  Check if the I2C peripheral is enabled or disabled.
  * @rmtoll CR1          PE            I2C_Is_Enabled
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t I2C_Is_Enabled(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CR1, I2C_CR1_PE) == (I2C_CR1_PE));
}

/**
  * @brief  Enable General Call.
  * @note   When enabled the Address 0x00 is ACKed.
  * @rmtoll CR1          ENGC          I2C_Enable_GeneralCall
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void I2C_Enable_GeneralCall(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CR1, I2C_CR1_ENGC);
}

/**
  * @brief  Disable General Call.
  * @note   When disabled the Address 0x00 is NACKed.
  * @rmtoll CR1          ENGC          I2C_Disable_GeneralCall
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void I2C_Disable_GeneralCall(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CR1, I2C_CR1_ENGC);
}

/**
  * @brief  Check if General Call is enabled or disabled.
  * @rmtoll CR1          ENGC          I2C_Get_GeneralCall
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t I2C_Get_GeneralCall(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CR1, I2C_CR1_ENGC) == (I2C_CR1_ENGC));
}

/**
  * @brief  Enable Clock stretching.
  * @note   This bit can only be programmed when the I2C is disabled (PE = 0).
  * @rmtoll CR1          NOSTRETCH     I2C_Enable_ClockStretching
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void I2C_Enable_ClockStretching(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CR1, I2C_CR1_NOSTRETCH);
}

/**
  * @brief  Disable Clock stretching.
  * @note   This bit can only be programmed when the I2C is disabled (PE = 0).
  * @rmtoll CR1          NOSTRETCH     I2C_Disable_ClockStretching
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void I2C_Disable_ClockStretching(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CR1, I2C_CR1_NOSTRETCH);
}

/**
  * @brief  Check if Clock stretching is enabled or disabled.
  * @rmtoll CR1          NOSTRETCH     I2C_Get_ClockStretching
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t I2C_Get_ClockStretching(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CR1, I2C_CR1_NOSTRETCH) != (I2C_CR1_NOSTRETCH));
}

/**
  * @brief  Generate a START or RESTART condition
  * @note   The START bit can be set even if bus is BUSY or I2C is in slave mode.
  *         This action has no effect when RELOAD is set.
  * @rmtoll CR1          START         I2C_Generate_StartCondition
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void I2C_Generate_StartCondition(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CR1, I2C_CR1_START);
}
/**
  * @brief  Generate a STOP condition after the current byte transfer (master mode).
  * @rmtoll CR1          STOP          I2C_Generate_StopCondition
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void I2C_Generate_StopCondition(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CR1, I2C_CR1_STOP);
}

/**
  * @brief  Prepare the generation of a ACKnowledge or Non ACKnowledge condition after the address receive match code or next received byte.
  * @note   Usage in Slave or Master mode.
  * @rmtoll CR1          ACK           I2C_Set_AcknowledgeNextData
  * @param  I2Cx I2C Instance.
  * @param  TypeAcknowledge This parameter can be one of the following values:
  *         @arg @ref I2C_CR1_ACK
  *         @arg @ref I2C_CR1_NACK
  * @retval None
  */
__STATIC_INLINE void I2C_Set_AcknowledgeNextData(I2C_TypeDef *I2Cx, uint32_t TypeAcknowledge)
{
  MODIFY_REG(I2Cx->CR1, I2C_CR1_ACK, TypeAcknowledge);
}

/**
  * @brief  Enable bit POS (master/host mode).
  * @note   In that case, the ACK bit controls the (N)ACK of the next byte received or the PEC bit indicates that the next byte in shift register is a PEC.
  * @rmtoll CR1          POS           I2C_Enable_POSBit
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void I2C_Enable_POSBit(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CR1, I2C_CR1_POS);
}

/**
  * @brief  Disable bit POS (master/host mode).
  * @note   In that case, the ACK bit controls the (N)ACK of the current byte received or the PEC bit indicates that the current byte in shift register is a PEC.
  * @rmtoll CR1          POS           I2C_Disable_POSBit
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void I2C_Disable_POSBit(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CR1, I2C_CR1_POS);
}

/**
  * @brief  Check if bit POS  is enabled or disabled.
  * @rmtoll CR1          POS           I2C_Get_POSBit
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t I2C_Get_POSBit(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CR1, I2C_CR1_POS) == (I2C_CR1_POS));
}

/**
  * @brief  Enable Reset of I2C peripheral.
  * @rmtoll CR1          SWRST         I2C_Enable_Reset
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void I2C_Enable_Reset(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->CR1, I2C_CR1_SWRST);
}

/**
  * @brief  Disable Reset of I2C peripheral.
  * @rmtoll CR1          SWRST         I2C_Disable_Reset
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void I2C_Disable_Reset(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->CR1, I2C_CR1_SWRST);
}

/**
  * @brief  Check if the I2C peripheral is under reset state or not.
  * @rmtoll CR1          SWRST         I2C_Get_Reset
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t I2C_Get_Reset(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->CR1, I2C_CR1_SWRST) == (I2C_CR1_SWRST));
}


/**
  * @brief  Configure the Peripheral clock frequency.
  * @rmtoll CR2          FREQ          I2C_Set_PeriphClockFREQ
  * @param  I2Cx I2C Instance.
  * @param  PeriphClock Peripheral Clock (in Hz)
  * @retval None
  */
__STATIC_INLINE void I2C_Set_PeriphClockFREQ(I2C_TypeDef *I2Cx, uint32_t PeriphClock)
{
  MODIFY_REG(I2Cx->CR2, I2C_CR2_FREQ, (uint32_t)(PeriphClock/1000000U));
}

/**
  * @brief  Get the Peripheral clock frequency.
  * @rmtoll CR2          FREQ          I2C_Get_PeriphClockFREQ
  * @param  I2Cx I2C Instance.
  * @retval Value of Peripheral Clock (in Hz)
  */
__STATIC_INLINE uint32_t I2C_Get_PeriphClockFREQ(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(1000000U*(READ_BIT(I2Cx->CR2, I2C_CR2_FREQ)));
}


/**
***********************************************************************************
*@Function I2C_Enable_IT
*@brief    Enable I2C Iterrupt.
*@param  I2Cx I2C Instance
*@param1   IT:
*          @arg  I2C_CR2_ITERREN
*          @arg  I2C_CR2_ITEVTEN
*          @arg  I2C_CR2_ITBUFEN
*          @arg  I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN    (TXE interrupt)
*@retval None.
***********************************************************************************
  */
__STATIC_INLINE void I2C_Enable_IT(I2C_TypeDef *I2Cx, uint32_t IT)
{
	SET_BIT( I2Cx->CR2, IT );
}

/**
***********************************************************************************
*@Function I2C_Disable_IT
*@brief    Disable I2C Iterrupt.
*@param  I2Cx I2C Instance
*@param1   IT:
*          @arg  I2C_CR2_ITERREN
*          @arg  I2C_CR2_ITEVTEN
*          @arg  I2C_CR2_ITBUFEN
*          @arg  I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN    (TXE interrupt)
*@retval None.
***********************************************************************************
  */
__STATIC_INLINE void I2C_Disable_IT(I2C_TypeDef *I2Cx, uint32_t IT)
{
	CLEAR_BIT( I2Cx->CR2, IT );
}


/**
***********************************************************************************
*@Function I2C_Get_IT
*@brief    Get I2C Iterrupt.
*@param  I2Cx I2C Instance
*@param1   IT:
*          @arg  I2C_CR2_ITERREN
*          @arg  I2C_CR2_ITEVTEN
*          @arg  I2C_CR2_ITBUFEN
*          @arg  I2C_CR2_ITEVTEN | I2C_CR2_ITBUFEN    (TXE interrupt)
*@retval State of bit (1 or 0).
***********************************************************************************
  */
__STATIC_INLINE uint32_t I2C_Get_IT(I2C_TypeDef *I2Cx, uint32_t IT)
{
	return (READ_BIT(I2Cx->CR2, IT) == (IT));
}

/**
  * @brief  Set the Own Address1.
  * @rmtoll OAR1         ADD0          I2C_Set_OwnAddress1\n
  *         OAR1         ADD1_7        I2C_Set_OwnAddress1\n
  *         OAR1         ADD8_9        I2C_Set_OwnAddress1\n
  *         OAR1         ADDMODE       I2C_Set_OwnAddress1
  * @param  I2Cx I2C Instance.
  * @param  OwnAddress1 This parameter must be a value between Min_Data=0 and Max_Data=0x3FF.
  * @param  OwnAddrSize This parameter can be one of the following values:
  *         @arg @ref I2C_OWNADDRESS1_7BIT
  *         @arg @ref I2C_OWNADDRESS1_10BIT
  * @retval None
  */
__STATIC_INLINE void I2C_Set_OwnAddress1(I2C_TypeDef *I2Cx, uint32_t OwnAddress1, uint32_t OwnAddrSize)
{
  MODIFY_REG(I2Cx->OAR1, I2C_OAR1_ADD0 | I2C_OAR1_ADD1_7 | I2C_OAR1_ADD8_9 | I2C_OAR1_ADDMODE, OwnAddress1 | OwnAddrSize);
}

/**
  * @brief  Enable acknowledge on Own Address2 match address.
  * @rmtoll OAR2         ENDUAL        I2C_Enable_OwnAddress2
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void I2C_Enable_OwnAddress2(I2C_TypeDef *I2Cx)
{
  SET_BIT(I2Cx->OAR2, I2C_OAR2_ENDUAL);
}

/**
  * @brief  Disable  acknowledge on Own Address2 match address.
  * @rmtoll OAR2         ENDUAL        I2C_Disable_OwnAddress2
  * @param  I2Cx I2C Instance.
  * @retval None
  */
__STATIC_INLINE void I2C_Disable_OwnAddress2(I2C_TypeDef *I2Cx)
{
  CLEAR_BIT(I2Cx->OAR2, I2C_OAR2_ENDUAL);
}

/**
  * @brief  Check if Own Address1 acknowledge is enabled or disabled.
  * @rmtoll OAR2         ENDUAL        I2C_Get_OwnAddress2
  * @param  I2Cx I2C Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t I2C_Get_OwnAddress2(I2C_TypeDef *I2Cx)
{
  return (READ_BIT(I2Cx->OAR2, I2C_OAR2_ENDUAL) == (I2C_OAR2_ENDUAL));
}

/**
  * @brief  Set the 7bits Own Address2.
  * @note   This action has no effect if own address2 is enabled.
  * @rmtoll OAR2         ADD2          I2C_Set_OwnAddress2
  * @param  I2Cx I2C Instance.
  * @param  OwnAddress2 This parameter must be a value between Min_Data=0 and Max_Data=0x7F.
  * @retval None
  */
__STATIC_INLINE void I2C_Set_OwnAddress2(I2C_TypeDef *I2Cx, uint32_t OwnAddress2)
{
  MODIFY_REG(I2Cx->OAR2, I2C_OAR2_ADD2, OwnAddress2);
}

/**
  * @brief  Get the data register address used for DMA transfer.
  * @rmtoll DR           DR            I2C_Get_DMARegAddr
  * @param  I2Cx I2C Instance.
  * @retval Address of data register
  */
__STATIC_INLINE uint32_t I2C_Get_DMARegAddr(I2C_TypeDef *I2Cx)
{
  return (uint32_t) & (I2Cx->DR);
}

/**
  * @brief  Read Receive Data register.
  * @rmtoll DR           DR            I2C_Receive_Data8
  * @param  I2Cx I2C Instance.
  * @retval Value between Min_Data=0x0 and Max_Data=0xFF
  */
__STATIC_INLINE uint8_t I2C_Receive_Data8(I2C_TypeDef *I2Cx)
{
  return (uint8_t)(READ_BIT(I2Cx->DR, I2C_DR_DR));
}

/**
  * @brief  Write in Transmit Data Register .
  * @rmtoll DR           DR            I2C_Transmit_Data8
  * @param  I2Cx I2C Instance.
  * @param  Data Value between Min_Data=0x0 and Max_Data=0xFF
  * @retval None
  */
__STATIC_INLINE void I2C_Transmit_Data8(I2C_TypeDef *I2Cx, uint8_t Data)
{
  MODIFY_REG(I2Cx->DR, I2C_DR_DR, Data);
}

/**
  * @brief  Indicate the status of SR1.
  * @rmtoll SR1                     I2C_Get_Flag
  * @param  I2Cx I2C Instance.
  *         @arg @ref  I2C_FLAG_SB     
  *         @arg @ref  I2C_FLAG_ADDR   
  *         @arg @ref  I2C_FLAG_BTF    
  *         @arg @ref  I2C_FLAG_ADD10  
  *         @arg @ref  I2C_FLAG_STOPF  
  *         @arg @ref  I2C_FLAG_RXNE   
  *         @arg @ref  I2C_FLAG_TXE     
  *         @arg @ref  I2C_FLAG_BERR   
  *         @arg @ref  I2C_FLAG_ARLO    
  *         @arg @ref  I2C_FLAG_AF     
  *         @arg @ref  I2C_FLAG_OVR     
  *         @arg @ref  I2C_FLAG_TIMEOUT
  *         @arg @ref  I2C_FLAG_MSL     
  *         @arg @ref  I2C_FLAG_BUSY    
  *         @arg @ref  I2C_FLAG_GENCALL
  *         @arg @ref  I2C_FLAG_DUALF  
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t I2C_Get_Flag(I2C_TypeDef *I2Cx,uint32_t FLAG)
{
	if((FLAG&0x10000000)==0x10000000)
	{
		return (READ_BIT(I2Cx->SR1, (FLAG&0xFFFFFFF)) == (FLAG&0xFFFFFFF));
	}
	else if((FLAG&0x20000000)==0x20000000)
	{
		return (READ_BIT(I2Cx->SR2, (FLAG&0x1FFFFFFF)) == (FLAG&0x1FFFFFFF));
	}
	return 0;
}

/**
  * @brief  Clear the status of SR1.
  * @rmtoll SR1             I2C_Clear_Flag
  * @param  I2Cx I2C Instance.  
  *         @arg @ref  I2C_FLAG_ADDR
  *         @arg @ref  I2C_FLAG_STOPF
  *         @arg @ref  I2C_FLAG_BERR
  *         @arg @ref  I2C_FLAG_ARLO 
  *         @arg @ref  I2C_FLAG_AF
  *         @arg @ref  I2C_FLAG_OVR 
  *         @arg @ref  I2C_FLAG_TIMEOUT 
  * @retval None.
  */
__STATIC_INLINE void I2C_Clear_Flag(I2C_TypeDef *I2Cx,uint32_t FLAG)
{
	__IO uint32_t tmpreg;
	if( (FLAG&I2C_FLAG_ADDR) == I2C_FLAG_ADDR )
	{
		tmpreg = I2Cx->SR1;
	    (void) tmpreg;
	    tmpreg = I2Cx->SR2;
	    (void) tmpreg;
	}
	else if( (FLAG&I2C_FLAG_STOPF) == I2C_FLAG_STOPF)
	{
		tmpreg = I2Cx->SR1;
		(void) tmpreg;
		SET_BIT(I2Cx->CR1, I2C_CR1_PE);
	}
	else if((FLAG&0x10000000)==0x10000000)
	{
		CLEAR_BIT(I2Cx->SR1, (FLAG&0xFFFFFFF));
	}
}


/**
  * @brief  Indicate the value of transfer direction.
  * @note   RESET: Bus is in read transfer (peripheral point of view).
  *         SET: Bus is in write transfer (peripheral point of view).
  * @rmtoll SR2          TRA           I2C_Get_TransferDirection
  * @param  I2Cx I2C Instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref I2C_DIRECTION_WRITE
  *         @arg @ref I2C_DIRECTION_READ
  */
__STATIC_INLINE uint32_t I2C_Get_TransferDirection(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->SR2, I2C_SR2_TRA));
}

/**
  * @brief  Configure the SCL high and low period.
  * @note   This bit can only be programmed when the I2C is disabled (PE = 0).
  * @rmtoll CCR          CCR           I2C_Set_ClockPeriod
  * @param  I2Cx I2C Instance.
  * @param  ClockPeriod This parameter must be a value between Min_Data=0x004 and Max_Data=0xFFF, except in FAST DUTY mode where Min_Data=0x001.
  * @retval None
  */
__STATIC_INLINE void I2C_Set_ClockPeriod(I2C_TypeDef *I2Cx, uint32_t ClockPeriod)
{
  MODIFY_REG(I2Cx->CCR, I2C_CCR_CCR, ClockPeriod);
}

/**
  * @brief  Get the SCL high and low period.
  * @rmtoll CCR          CCR           I2C_Get_ClockPeriod
  * @param  I2Cx I2C Instance.
  * @retval Value between Min_Data=0x004 and Max_Data=0xFFF, except in FAST DUTY mode where Min_Data=0x001.
  */
__STATIC_INLINE uint32_t I2C_Get_ClockPeriod(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->CCR, I2C_CCR_CCR));
}


/**
  * @brief  Configure the Duty cycle (Fast mode only).
  * @rmtoll CCR          DUTY          I2C_Set_DutyCycle
  * @param  I2Cx I2C Instance.
  * @param  DutyCycle This parameter can be one of the following values:
  *         @arg @ref I2C_DUTYCYCLE_2
  *         @arg @ref I2C_DUTYCYCLE_16_9
  * @retval None
  */
__STATIC_INLINE void I2C_Set_DutyCycle(I2C_TypeDef *I2Cx, uint32_t DutyCycle)
{
  MODIFY_REG(I2Cx->CCR, I2C_CCR_DUTY, DutyCycle);
}

/**
  * @brief  Get the Duty cycle (Fast mode only).
  * @rmtoll CCR          DUTY          I2C_Get_DutyCycle
  * @param  I2Cx I2C Instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref I2C_DUTYCYCLE_2
  *         @arg @ref I2C_DUTYCYCLE_16_9
  */
__STATIC_INLINE uint32_t I2C_Get_DutyCycle(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->CCR, I2C_CCR_DUTY));
}

/**
  * @brief  Configure the I2C master clock speed mode.
  * @rmtoll CCR          FS            I2C_Set_ClockSpeedMode
  * @param  I2Cx I2C Instance.
  * @param  ClockSpeedMode This parameter can be one of the following values:
  *         @arg @ref I2C_STANDARD_MODE
  *         @arg @ref I2C_FAST_MODE
  * @retval None
  */
__STATIC_INLINE void I2C_Set_ClockSpeedMode(I2C_TypeDef *I2Cx, uint32_t ClockSpeedMode)
{
  MODIFY_REG(I2Cx->CCR, I2C_CCR_FS, ClockSpeedMode);
}

/**
  * @brief  Get the the I2C master speed mode.
  * @rmtoll CCR          FS            I2C_Get_ClockSpeedMode
  * @param  I2Cx I2C Instance.
  * @retval Returned value can be one of the following values:
  *         @arg @ref I2C_STANDARD_MODE
  *         @arg @ref I2C_FAST_MODE
  */
__STATIC_INLINE uint32_t I2C_Get_ClockSpeedMode(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->CCR, I2C_CCR_FS));
}

/**
  * @brief  Configure the SCL, SDA rising time.
  * @note   This bit can only be programmed when the I2C is disabled (PE = 0).
  * @rmtoll TRISE        TRISE         I2C_Set_RiseTime
  * @param  I2Cx I2C Instance.
  * @param  RiseTime This parameter must be a value between Min_Data=0x02 and Max_Data=0x3F.
  * @retval None
  */
__STATIC_INLINE void I2C_Set_RiseTime(I2C_TypeDef *I2Cx, uint32_t RiseTime)
{
  MODIFY_REG(I2Cx->TRISE, I2C_TRISE_TRISE, RiseTime);
}

/**
  * @brief  Get the SCL, SDA rising time.
  * @rmtoll TRISE        TRISE         I2C_Get_RiseTime
  * @param  I2Cx I2C Instance.
  * @retval Value between Min_Data=0x02 and Max_Data=0x3F
  */
__STATIC_INLINE uint32_t I2C_Get_RiseTime(I2C_TypeDef *I2Cx)
{
  return (uint32_t)(READ_BIT(I2Cx->TRISE, I2C_TRISE_TRISE));
}

void I2C_DeInit(I2C_TypeDef *I2Cx);
void I2C_Init(I2C_TypeDef *I2Cx, I2C_InitTypeDef *I2C_InitStruct);
void I2C_Set_Speed(I2C_TypeDef *I2Cx, uint32_t PeriphClock, uint32_t ClockSpeed,uint32_t DutyCycle);

#ifdef __cplusplus
}
#endif

#endif /* __rx32h6xx_GPIO_H__ */

