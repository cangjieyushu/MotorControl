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
* File         : rx32h6xx_i2c.c
* By           : RX_SD_Team
* Version      : V1.0.0
* Description  : Only rx32h6xx
*********************************************************************************************************
*/

#include "rx32h6xx.h"
#include "rx32h6xx_i2c.h"

/**
  * @brief  De-initialize the I2C registers to their default reset values.
  * @param  I2Cx I2C Instance.
  * @retval none.
  */
void I2C_DeInit(I2C_TypeDef *I2Cx)
{
    /* Force reset of I2C clock */
    RCC_Enable_APB1RST(RCC_APB1RSTR_I2C1RST);

    /* Release reset of I2C clock */
    RCC_Disable_APB1RST(RCC_APB1RSTR_I2C1RST);
}

/**
  * @brief  Initialize the I2C registers according to the specified parameters in I2C_InitStruct.
  * @param  I2Cx I2C Instance.
  * @param  ClockSpeed This parameter must be a value lower than 400kHz (in Hz).
  * @param  DutyCycle This parameter can be one of the following values:
  *         @arg @ref I2C_DUTYCYCLE_2
  *         @arg @ref I2C_DUTYCYCLE_16_9
  * @param  OwnAddress1 This parameter must be a value between Min_Data=0 and Max_Data=0x3FF.
  * @param  OwnAddrSize This parameter can be one of the following values:
  *         @arg @ref I2C_OWNADDRESS1_7BIT
  *         @arg @ref I2C_OWNADDRESS1_10BIT
  * @param  TypeAcknowledge This parameter can be one of the following values:
  *         @arg @ref I2C_CR1_ACK
  *         @arg @ref I2C_CR1_NACK
  * @retval None.
  */
void I2C_Init(I2C_TypeDef *I2Cx, I2C_InitTypeDef *I2C_InitStruct)
{
  RCC_ClocksTypeDef rcc_clocks;

  /* Disable the selected I2Cx Peripheral */
  I2C_Disable(I2Cx);

  /* Get SYSCLK frequency */
  rcc_clocks.SYSCLK_Frequency = RCC_Get_SystemClock();

  /* HCLK clock frequency */
  rcc_clocks.HCLK_Frequency   = RCC_Get_AHBClock();

  /* PCLK1 clock frequency */
  rcc_clocks.PCLK1_Frequency  = RCC_Get_APB1Clock();

  /* PCLK2 clock frequency */
  rcc_clocks.PCLK2_Frequency  = RCC_Get_APB2Clock();

  /*---------------------------- I2Cx SCL Clock Speed Configuration ------------*/
  I2C_Set_Speed(I2Cx, rcc_clocks.PCLK1_Frequency, I2C_InitStruct->ClockSpeed, I2C_InitStruct->DutyCycle);

  /*---------------------------- I2Cx OAR1 Configuration -----------------------*/
  I2C_Set_OwnAddress1(I2Cx, I2C_InitStruct->OwnAddress1, I2C_InitStruct->OwnAddrSize);

  /* Enable the selected I2Cx Peripheral */
  I2C_Enable(I2Cx);

  /*---------------------------- I2Cx CR2 Configuration ------------------------*/
  I2C_Set_AcknowledgeNextData(I2Cx, I2C_InitStruct->TypeAcknowledge);
}


/**
  * @brief  Configure the SCL speed.
  * @note   This bit can only be programmed when the I2C is disabled (PE = 0).
  * @rmtoll CR2          FREQ          I2C_Set_Speed\n
  *         TRISE        TRISE         I2C_Set_Speed\n
  *         CCR          FS            I2C_Set_Speed\n
  *         CCR          DUTY          I2C_Set_Speed\n
  *         CCR          CCR           I2C_Set_Speed
  * @param  I2Cx I2C Instance.
  * @param  PeriphClock Peripheral Clock (in Hz)
  * @param  ClockSpeed This parameter must be a value lower than 400kHz (in Hz).
  * @param  DutyCycle This parameter can be one of the following values:
  *         @arg @ref I2C_DUTYCYCLE_2
  *         @arg @ref I2C_DUTYCYCLE_16_9
  * @retval None
  */
void I2C_Set_Speed(I2C_TypeDef *I2Cx, uint32_t PeriphClock, uint32_t ClockSpeed,
                                        uint32_t DutyCycle)
{
  register uint32_t freqrange = 0x0U;
  register uint32_t clockconfig = 0x0U;

  /* Compute frequency range */
  freqrange = (uint32_t)((PeriphClock)/1000000U);

  /* Configure I2Cx: Frequency range register */
  MODIFY_REG(I2Cx->CR2, I2C_CR2_FREQ, freqrange);

  /* Configure I2Cx: Rise Time register */
  MODIFY_REG(I2Cx->TRISE, I2C_TRISE_TRISE, __I2C_RISE_TIME(freqrange, ClockSpeed));

  /* Configure Speed mode, Duty Cycle and Clock control register value */
  if (ClockSpeed > I2C_MAX_SPEED_STANDARD)
  {
    /* Set Speed mode at fast and duty cycle for Clock Speed request in fast clock range */
    clockconfig = I2C_FAST_MODE                                          | \
                  __I2C_SPEED_FAST_TO_CCR(PeriphClock, ClockSpeed, DutyCycle)        | \
                  DutyCycle;
  }
  else
  {
    /* Set Speed mode at standard for Clock Speed request in standard clock range */
    clockconfig = I2C_STANDARD_MODE                                      | \
                  __I2C_SPEED_STANDARD_TO_CCR(PeriphClock, ClockSpeed);
  }

  /* Configure I2Cx: Clock control register */
  MODIFY_REG(I2Cx->CCR, (I2C_CCR_FS | I2C_CCR_DUTY | I2C_CCR_CCR), clockconfig);
}



