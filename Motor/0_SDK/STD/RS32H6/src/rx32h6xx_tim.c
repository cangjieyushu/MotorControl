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
* File         : rx32h6xx_tim.c
* By           : RX_SD_Team
* Version      : V1.0.0
* Description  : Only rx32h6xx
*********************************************************************************************************
*/

#include "rx32h6xx_tim.h"
#include "rx32h6xx_rcc.h"
#include "rx32h6xx.h"

/** @addtogroup TIM_Exported_Functions
  * @{
  */

/** @addtogroup TIM_EF_Init
  * @{
  */

/**
  * @brief  Set TIMx registers to their reset values.
  * @param  TIMx Timer instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx registers are de-initialized
  *          - ERROR: invalid TIMx instance
  */
void TIM_DeInit(TIM_TypeDef *TIMx)
{
  if (TIMx == TIM8)
  {
    RCC_Enable_APB2RST(RCC_APB2RSTR_TIM8RST);
    RCC_Disable_APB2RST(RCC_APB2RSTR_TIM8RST);
  }
  else if (TIMx == TIM2)
  {
    RCC_Enable_APB1RST(RCC_APB1RSTR_TIM2RST);
    RCC_Disable_APB1RST(RCC_APB1RSTR_TIM2RST);
  }
  else if (TIMx == TIM3)
  {
    RCC_Enable_APB1RST(RCC_APB1RSTR_TIM3RST);
    RCC_Disable_APB1RST(RCC_APB1RSTR_TIM3RST);
  }
  else if (TIMx == TIM6)
  {
    RCC_Enable_APB1RST(RCC_APB1RSTR_TIM6RST);
    RCC_Disable_APB1RST(RCC_APB1RSTR_TIM6RST);
  }
  else if (TIMx == TIM7)
  {
    RCC_Enable_APB1RST(RCC_APB1RSTR_TIM7RST);
    RCC_Disable_APB1RST(RCC_APB1RSTR_TIM7RST);
  }
  else if (TIMx == TIM15)
  {
    RCC_Enable_APB2RST(RCC_APB2RSTR_TIM15RST);
    RCC_Disable_APB2RST(RCC_APB2RSTR_TIM15RST);
  }
}

/**
  * @brief  Set the fields of the time base unit configuration data structure
  *         to their default values.
  * @param  TIM_InitStruct pointer to a @ref TIM_InitTypeDef structure (time base unit configuration data structure)
  * @retval None
  */
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef *TIM_InitStruct)
{
  /* Set the default configuration */
  TIM_InitStruct->Prescaler         = (uint16_t)0x0000;
  TIM_InitStruct->CounterMode       = TIM_COUNTERMODE_UP;
  TIM_InitStruct->Period            = 0xFFFFFFFFU;
  TIM_InitStruct->ClockDivision     = TIM_CLOCKDIVISION_DIV1;
  TIM_InitStruct->RepetitionCounter = 0x00000000U;
}

/**
  * @brief  Configure the TIMx time base unit.
  * @param  TIMx Timer Instance
  * @param  TIM_InitStruct pointer to a @ref TIM_InitTypeDef structure
  *         (TIMx time base unit configuration data structure)
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx registers are de-initialized
  *          - ERROR: not applicable
  */
void TIM_TimeBaseInit(TIM_TypeDef *TIMx, TIM_TimeBaseInitTypeDef *TIM_InitStruct)
{
  uint32_t tmpcr1 = 0;

  tmpcr1 = TIMx->CR1;

	/* Select the Counter Mode */
	tmpcr1 &= (uint32_t)(~((uint32_t)(TIM_CR1_DIR | TIM_CR1_CMS)));
	tmpcr1 |= (uint32_t)TIM_InitStruct->CounterMode;

	/* Set the clock division */
	tmpcr1 &= (uint32_t)(~((uint32_t)TIM_CR1_CKD));
	tmpcr1 |= (uint32_t)TIM_InitStruct->ClockDivision;

  TIMx->CR1 = tmpcr1;

  /* Set the Autoreload value */
  TIMx->ARR = TIM_InitStruct->Period ;
 
  /* Set the Prescaler value */
  TIMx->PSC = TIM_InitStruct->Prescaler;

  /* Set the Repetition Counter value */
  TIMx->RCR = TIM_InitStruct->RepetitionCounter;

  /* Generate an update event to reload the Prescaler and the Repetition counter
     values immediately */
  TIMx->EGR = 0x0001;           
}

/**
  * @brief  Set the fields of the TIMx output channel configuration data
  *         structure to their default values.
  * @param  TIM_OC_InitStruct pointer to a @ref TIM_OC_InitTypeDef structure
  *         (the output channel configuration data structure)
  * @retval None
  */
void TIM_OCStructInit(TIM_OCInitTypeDef *TIM_OC_InitStruct)
{
  /* Set the default configuration */
  TIM_OC_InitStruct->OCMode       = TIM_OCMODE_FROZEN;
  TIM_OC_InitStruct->OutputState  = TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct->OutputNState = TIM_OCSTATE_DISABLE;
  TIM_OC_InitStruct->Pulse        = 0x00000000U;
  TIM_OC_InitStruct->OCPolarity   = TIM_OCPOLARITY_HIGH;
  TIM_OC_InitStruct->OCNPolarity  = TIM_OCNPOLARITY_HIGH;
  TIM_OC_InitStruct->OCIdleState  = TIM_OCIDLESTATE_RESET;
  TIM_OC_InitStruct->OCNIdleState = TIM_OCNIDLESTATE_RESET;
}

/**
  * @brief  Configure the TIMx output channel.
  * @param  TIMx Timer Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH4
  *         @arg @ref TIM_CHANNEL_CH5
  *         @arg @ref TIM_CHANNEL_CH6
  * @param  TIM_OC_InitStruct pointer to a @ref TIM_OC_InitTypeDef structure (TIMx output channel configuration
  *         data structure)
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx output channel is initialized
  *          - ERROR: TIMx output channel is not initialized
  */
void TIM_OC_Init(TIM_TypeDef *TIMx, uint32_t Channel, TIM_OCInitTypeDef *TIM_OC_InitStruct)
{
  switch (Channel)
  {
    case TIM_CHANNEL_CH1:
      TIM_OC1Init(TIMx, TIM_OC_InitStruct);
      break;
    case TIM_CHANNEL_CH2:
      TIM_OC2Init(TIMx, TIM_OC_InitStruct);
      break;
    case TIM_CHANNEL_CH3:
      TIM_OC3Init(TIMx, TIM_OC_InitStruct);
      break;
    case TIM_CHANNEL_CH4:
      TIM_OC4Init(TIMx, TIM_OC_InitStruct);
      break;
    case TIM_CHANNEL_CH5:
      TIM_OC5Init(TIMx, TIM_OC_InitStruct);
      break;
    case TIM_CHANNEL_CH6:
      TIM_OC6Init(TIMx, TIM_OC_InitStruct);
      break;
    default:
      break;
  }
}

/**
  * @brief  Set the fields of the TIMx input channel configuration data
  *         structure to their default values.
  * @param  TIM_ICInitStruct pointer to a @ref TIM_IC_InitTypeDef structure (the input channel configuration
  *         data structure)
  * @retval None
  */
void TIM_ICStructInit(TIM_ICInitTypeDef *TIM_ICInitStruct)
{
  /* Set the default configuration */
  TIM_ICInitStruct->ICPolarity    = TIM_IC_POLARITY_RISING;
  TIM_ICInitStruct->ICSelection = TIM_ACTIVEINPUT_DIRECTTI;
  TIM_ICInitStruct->ICPrescaler   = TIM_ICPSC_DIV1;
  TIM_ICInitStruct->ICFilter      = TIM_IC_FILTER_FDIV1;
}

/**
  * @brief  Configure the TIMx input channel.
  * @param  TIMx Timer Instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH4
  * @param  TIM_IC_InitStruct pointer to a @ref TIM_IC_InitTypeDef structure (TIMx input channel configuration data
  *         structure)
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx output channel is initialized
  *          - ERROR: TIMx output channel is not initialized
  */
void TIM_ICInit(TIM_TypeDef *TIMx, TIM_ICInitTypeDef *TIM_IC_InitStruct)
{
  switch (TIM_IC_InitStruct->Channel)
  {
    case TIM_CHANNEL_CH1:
      TIM_Set_TI1(TIMx, TIM_IC_InitStruct);
      break;
    case TIM_CHANNEL_CH2:
      TIM_Set_TI2(TIMx, TIM_IC_InitStruct);
      break;
    case TIM_CHANNEL_CH3:
      TIM_Set_TI3(TIMx, TIM_IC_InitStruct);
      break;
    case TIM_CHANNEL_CH4:
      TIM_Set_TI4(TIMx, TIM_IC_InitStruct);
      break;
    default:
      break;
  }
}

/**
  * @brief  Fills each TIM_EncoderInitStruct field with its default value
  * @param  TIM_EncoderInitStruct pointer to a @ref TIM_ENCODER_InitTypeDef structure (encoder interface
  *         configuration data structure)
  * @retval None
  */
void TIM_ENCODER_StructInit(TIM_ENCODER_InitTypeDef *TIM_EncoderInitStruct)
{
  /* Set the default configuration */
  TIM_EncoderInitStruct->EncoderMode    = TIM_ENCODERMODE_X2_TI1;
  TIM_EncoderInitStruct->IC1Polarity    = TIM_IC_POLARITY_RISING;
  TIM_EncoderInitStruct->IC1ActiveInput = TIM_ACTIVEINPUT_DIRECTTI;
  TIM_EncoderInitStruct->IC1Prescaler   = TIM_ICPSC_DIV1;
  TIM_EncoderInitStruct->IC1Filter      = TIM_IC_FILTER_FDIV1;
  TIM_EncoderInitStruct->IC2Polarity    = TIM_IC_POLARITY_RISING;
  TIM_EncoderInitStruct->IC2ActiveInput = TIM_ACTIVEINPUT_DIRECTTI;
  TIM_EncoderInitStruct->IC2Prescaler   = TIM_ICPSC_DIV1;
  TIM_EncoderInitStruct->IC2Filter      = TIM_IC_FILTER_FDIV1;
}

/**
  * @brief  Configure the encoder interface of the timer instance.
  * @param  TIMx Timer Instance
  * @param  TIM_EncoderInitStruct pointer to a @ref TIM_ENCODER_InitTypeDef structure (TIMx encoder interface
  *         configuration data structure)
  * @param  TIMx:
  *         @arg TIM Instance
  * @param  EncoderMode£º 
  *         @arg @ref TIM_ENCODERMODE_X2_TI1                  
  *         @arg @ref TIM_ENCODERMODE_X2_TI2                  
  *         @arg @ref TIM_ENCODERMODE_X4_TI12                 
  *         @arg @ref TIM_ENCODERMODE_CLOCKPLUSDIRECTION_X2   
  *         @arg @ref TIM_ENCODERMODE_CLOCKPLUSDIRECTION_X1   
  *         @arg @ref TIM_ENCODERMODE_DIRECTIONALCLOCK_X2     
  *         @arg @ref TIM_ENCODERMODE_DIRECTIONALCLOCK_X1_TI12
  *         @arg @ref TIM_ENCODERMODE_X1_TI1                  
  *         @arg @ref TIM_ENCODERMODE_X1_TI2 
  * @param  IC1Polarity£º
  *         @arg @ref TIM_IC_POLARITY_RISING
  *         @arg @ref TIM_IC_POLARITY_FALLING
  *         @arg @ref TIM_IC_POLARITY_BOTHEDGE
  * @param  IC1ActiveInput£º
  *         @arg @ref TIM_ACTIVEINPUT_DIRECTTI
  *         @arg @ref TIM_ACTIVEINPUT_INDIRECTTI
  *         @arg @ref TIM_ACTIVEINPUT_TRC
  * @param  IC1Prescaler£º
  *         @arg @ref TIM_ICPSC_DIV1
  *         @arg @ref TIM_ICPSC_DIV2
  *         @arg @ref TIM_ICPSC_DIV4
  *         @arg @ref TIM_ICPSC_DIV8
  * @param  IC1Filter£º
  *         @arg @ref TIM_IC_FILTER_FDIV1
  *         @arg @ref TIM_IC_FILTER_FDIV1_N2	
  *         @arg @ref TIM_IC_FILTER_FDIV1_N4
  *         @arg @ref TIM_IC_FILTER_FDIV1_N8
  *         @arg @ref TIM_IC_FILTER_FDIV2_N6
  *         @arg @ref TIM_IC_FILTER_FDIV2_N8
  *         @arg @ref TIM_IC_FILTER_FDIV4_N6
  *         @arg @ref TIM_IC_FILTER_FDIV4_N8
  *         @arg @ref TIM_IC_FILTER_FDIV8_N6
  *         @arg @ref TIM_IC_FILTER_FDIV8_N8
  *         @arg @ref TIM_IC_FILTER_FDIV16_N5
  *         @arg @ref TIM_IC_FILTER_FDIV16_N6
  *         @arg @ref TIM_IC_FILTER_FDIV16_N8
  *         @arg @ref TIM_IC_FILTER_FDIV32_N5
  *         @arg @ref TIM_IC_FILTER_FDIV32_N6	
  *         @arg @ref TIM_IC_FILTER_FDIV32_N8	
  * @param  IC2Polarity£º
  *         @arg @ref TIM_IC_POLARITY_RISING
  *         @arg @ref TIM_IC_POLARITY_FALLING
  *         @arg @ref TIM_IC_POLARITY_BOTHEDGE  
  * @param  IC2ActiveInput£º
  *         @arg @ref TIM_ACTIVEINPUT_DIRECTTI
  *         @arg @ref TIM_ACTIVEINPUT_INDIRECTTI
  *         @arg @ref TIM_ACTIVEINPUT_TRC
  * @param  IC2Prescaler£º
  *         @arg @ref TIM_ICPSC_DIV1
  *         @arg @ref TIM_ICPSC_DIV2
  *         @arg @ref TIM_ICPSC_DIV4
  *         @arg @ref TIM_ICPSC_DIV8
  * @param  IC2Filter£º
  *         @arg @ref TIM_IC_FILTER_FDIV1
  *         @arg @ref TIM_IC_FILTER_FDIV1_N2	
  *         @arg @ref TIM_IC_FILTER_FDIV1_N4
  *         @arg @ref TIM_IC_FILTER_FDIV1_N8
  *         @arg @ref TIM_IC_FILTER_FDIV2_N6
  *         @arg @ref TIM_IC_FILTER_FDIV2_N8
  *         @arg @ref TIM_IC_FILTER_FDIV4_N6
  *         @arg @ref TIM_IC_FILTER_FDIV4_N8
  *         @arg @ref TIM_IC_FILTER_FDIV8_N6
  *         @arg @ref TIM_IC_FILTER_FDIV8_N8
  *         @arg @ref TIM_IC_FILTER_FDIV16_N5
  *         @arg @ref TIM_IC_FILTER_FDIV16_N6
  *         @arg @ref TIM_IC_FILTER_FDIV16_N8
  *         @arg @ref TIM_IC_FILTER_FDIV32_N5
  *         @arg @ref TIM_IC_FILTER_FDIV32_N6	
  *         @arg @ref TIM_IC_FILTER_FDIV32_N8		
  * @retval None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx registers are de-initialized
  *          - ERROR: not applicable
  */
void TIM_ENCODERInit(TIM_TypeDef *TIMx, TIM_ENCODER_InitTypeDef *TIM_EncoderInitStruct)
{
  uint32_t tmpccmr1;
  uint32_t tmpccer;

  /* Disable the CC1 and CC2: Reset the CC1E and CC2E Bits */
  TIMx->CCER &= (uint32_t)~(TIM_CCER_CC1E | TIM_CCER_CC2E);

  /* Get the TIMx CCMR1 register value */
  tmpccmr1 = TIM_ReadReg(TIMx, CCMR1);

  /* Get the TIMx CCER register value */
  tmpccer = TIM_ReadReg(TIMx, CCER);

  /* Configure TI1 */
  tmpccmr1 &= (uint32_t)~(TIM_CCMR1_CC1S | TIM_CCMR1_IC1F  | TIM_CCMR1_IC1PSC);
  tmpccmr1 |= (uint32_t)(TIM_EncoderInitStruct->IC1ActiveInput >> 16U);
  tmpccmr1 |= (uint32_t)(TIM_EncoderInitStruct->IC1Filter >> 16U);
  tmpccmr1 |= (uint32_t)(TIM_EncoderInitStruct->IC1Prescaler >> 16U);

  /* Configure TI2 */
  tmpccmr1 &= (uint32_t)~(TIM_CCMR1_CC2S | TIM_CCMR1_IC2F  | TIM_CCMR1_IC2PSC);
  tmpccmr1 |= (uint32_t)(TIM_EncoderInitStruct->IC2ActiveInput >> 8U);
  tmpccmr1 |= (uint32_t)(TIM_EncoderInitStruct->IC2Filter >> 8U);
  tmpccmr1 |= (uint32_t)(TIM_EncoderInitStruct->IC2Prescaler >> 8U);

  /* Set TI1 and TI2 polarity and enable TI1 and TI2 */
  tmpccer &= (uint32_t)~(TIM_CCER_CC1P | TIM_CCER_CC1NP | TIM_CCER_CC2P | TIM_CCER_CC2NP);
  tmpccer |= (uint32_t)(TIM_EncoderInitStruct->IC1Polarity);
  tmpccer |= (uint32_t)(TIM_EncoderInitStruct->IC2Polarity << 4U);
  tmpccer |= (uint32_t)(TIM_CCER_CC1E | TIM_CCER_CC2E);

  /* Set encoder mode */
  TIM_Set_EncoderMode(TIMx, TIM_EncoderInitStruct->EncoderMode);

  /* Write to TIMx CCMR1 */
  TIM_WriteReg(TIMx, CCMR1, tmpccmr1);

  /* Write to TIMx CCER */
  TIM_WriteReg(TIMx, CCER, tmpccer);
}

/**
  * @brief  Set the fields of the TIMx Hall sensor interface configuration data
  *         structure to their default values.
  * @param  TIM_HallSensorInitStruct pointer to a @ref TIM_HALLSENSOR_InitTypeDef structure (HALL sensor interface
  *         configuration data structure)
  * @retval None
  */
void TIM_HALLSENSOR_StructInit(TIM_HALLSENSOR_InitTypeDef *TIM_HallSensorInitStruct)
{
  /* Set the default configuration */
  TIM_HallSensorInitStruct->IC1Polarity       = TIM_IC_POLARITY_RISING;
  TIM_HallSensorInitStruct->IC1Prescaler      = TIM_ICPSC_DIV1;
  TIM_HallSensorInitStruct->IC1Filter         = TIM_IC_FILTER_FDIV1;
  TIM_HallSensorInitStruct->CommutationDelay  = 0U;
}

/**
  * @brief  Configure the Hall sensor interface of the timer instance.
  * @note TIMx CH1, CH2 and CH3 inputs connected through a XOR
  *       to the TI1 input channel
  * @note TIMx slave mode controller is configured in reset mode.
          Selected internal trigger is TI1F_ED.
  * @note Channel 1 is configured as input, IC1 is mapped on TRC.
  * @note Captured value stored in TIMx_CCR1 correspond to the time elapsed
  *       between 2 changes on the inputs. It gives information about motor speed.
  * @note Channel 2 is configured in output PWM 2 mode.
  * @note Compare value stored in TIMx_CCR2 corresponds to the commutation delay.
  * @note OC2REF is selected as trigger output on TRGO.
  * @note TIM_IC_POLARITY_BOTHEDGE must not be used for TI1 when it is used
  *       when TIMx operates in Hall sensor interface mode.
  * @param  TIMx Timer Instance
  * @param  TIM_HallSensorInitStruct pointer to a @ref TIM_HALLSENSOR_InitTypeDef structure (TIMx HALL sensor
  *         interface configuration data structure)
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx registers are de-initialized
  *          - ERROR: not applicable
  */
void TIM_HALLSENSOR_Init(TIM_TypeDef *TIMx, TIM_HALLSENSOR_InitTypeDef *TIM_HallSensorInitStruct)
{
  uint32_t tmpcr2;
  uint32_t tmpccmr1;
  uint32_t tmpccer;
  uint32_t tmpsmcr;

  /* Disable the CC1 and CC2: Reset the CC1E and CC2E Bits */
  TIMx->CCER &= (uint32_t)~(TIM_CCER_CC1E | TIM_CCER_CC2E);

  /* Get the TIMx CR2 register value */
  tmpcr2 = TIM_ReadReg(TIMx, CR2);

  /* Get the TIMx CCMR1 register value */
  tmpccmr1 = TIM_ReadReg(TIMx, CCMR1);

  /* Get the TIMx CCER register value */
  tmpccer = TIM_ReadReg(TIMx, CCER);

  /* Get the TIMx SMCR register value */
  tmpsmcr = TIM_ReadReg(TIMx, SMCR);

  /* Connect TIMx_CH1, CH2 and CH3 pins to the TI1 input */
  tmpcr2 |= TIM_CR2_TI1S;

  /* OC2REF signal is used as trigger output (TRGO) */
  tmpcr2 |= TIM_TRGO_OC2REF;

  /* Configure the slave mode controller */
  tmpsmcr &= (uint32_t)~(TIM_SMCR_TS | TIM_SMCR_SMS);
  tmpsmcr |= TIM_TS_TI1F_ED;
  tmpsmcr |= TIM_SLAVEMODE_RESET;

  /* Configure input channel 1 */
  tmpccmr1 &= (uint32_t)~(TIM_CCMR1_CC1S | TIM_CCMR1_IC1F  | TIM_CCMR1_IC1PSC);
  tmpccmr1 |= (uint32_t)(TIM_ACTIVEINPUT_TRC >> 16U);
  tmpccmr1 |= (uint32_t)(TIM_HallSensorInitStruct->IC1Filter >> 16U);
  tmpccmr1 |= (uint32_t)(TIM_HallSensorInitStruct->IC1Prescaler >> 16U);

  /* Configure input channel 2 */
  tmpccmr1 &= (uint32_t)~(TIM_CCMR1_OC2M | TIM_CCMR1_OC2FE  | TIM_CCMR1_OC2PE  | TIM_CCMR1_OC2CE);
  tmpccmr1 |= (uint32_t)(TIM_OCMODE_PWM2 << 8U);

  /* Set Channel 1 polarity and enable Channel 1 and Channel2 */
  tmpccer &= (uint32_t)~(TIM_CCER_CC1P | TIM_CCER_CC1NP | TIM_CCER_CC2P | TIM_CCER_CC2NP);
  tmpccer |= (uint32_t)(TIM_HallSensorInitStruct->IC1Polarity);
  tmpccer |= (uint32_t)(TIM_CCER_CC1E | TIM_CCER_CC2E);

  /* Write to TIMx CR2 */
  TIM_WriteReg(TIMx, CR2, tmpcr2);

  /* Write to TIMx SMCR */
  TIM_WriteReg(TIMx, SMCR, tmpsmcr);

  /* Write to TIMx CCMR1 */
  TIM_WriteReg(TIMx, CCMR1, tmpccmr1);

  /* Write to TIMx CCER */
  TIM_WriteReg(TIMx, CCER, tmpccer);

  /* Write to TIMx CCR2 */
  TIM_Set_OC_CompareCH2(TIMx, TIM_HallSensorInitStruct->CommutationDelay);
}

/**
  * @brief  Set the fields of the Break and Dead Time configuration data structure
  *         to their default values.
  * @param  TIM_BDTRInitStruct pointer to a @ref TIM_BDTRInitTypeDef structure (Break and Dead Time configuration
  *         data structure)
  * @retval None
  */
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef *TIM_BDTRInitStruct)
{
  /* Set the default configuration */
  TIM_BDTRInitStruct->OSSRState       = TIM_OSSR_DISABLE;
  TIM_BDTRInitStruct->OSSIState       = TIM_OSSI_DISABLE;
  TIM_BDTRInitStruct->LOCKLevel       = TIM_LOCKLEVEL_OFF;
  TIM_BDTRInitStruct->DeadTime        = (uint8_t)0x00;
  TIM_BDTRInitStruct->BreakState      = TIM_BREAK_DISABLE;
  TIM_BDTRInitStruct->BreakPolarity   = TIM_BREAK_POLARITY_LOW;
  TIM_BDTRInitStruct->BreakFilter     = TIM_BREAK_FILTER_FDIV1;
  TIM_BDTRInitStruct->BreakAFMode     = TIM_BREAK_AFMODE_INPUT;
  TIM_BDTRInitStruct->Break2State     = TIM_BREAK2_DISABLE;
  TIM_BDTRInitStruct->Break2Polarity  = TIM_BREAK2_POLARITY_LOW;
  TIM_BDTRInitStruct->Break2Filter    = TIM_BREAK2_FILTER_FDIV1;
  TIM_BDTRInitStruct->Break2AFMode    = TIM_BREAK2_AFMODE_INPUT;
  TIM_BDTRInitStruct->AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
}

/**
  * @brief  Configure the Break and Dead Time feature of the timer instance.
  * @note As the bits BK2P, BK2E, BK2F[3:0], BKF[3:0], AOE, BKP, BKE, OSSI, OSSR
  *  and DTG[7:0] can be write-locked depending on the LOCK configuration, it
  *  can be necessary to configure all of them during the first write access to
  *  the TIMx_BDTR register.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @note Macro IS_TIM_BKIN2_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a second break input.
  * @param  TIMx Timer Instance
  * @param  TIM_BDTRInitStruct pointer to a @ref TIM_BDTRInitTypeDef structure (Break and Dead Time configuration
  *         data structure)
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: Break and Dead Time is initialized
  *          - ERROR: not applicable
  */
void TIM_BDTRInit(TIM_TypeDef *TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct)
{
  uint32_t tmpbdtr = 0;

  /* Set the BDTR bits */
  MODIFY_REG(tmpbdtr, TIM_BDTR_DTG, TIM_BDTRInitStruct->DeadTime);
  MODIFY_REG(tmpbdtr, TIM_BDTR_LOCK, TIM_BDTRInitStruct->LOCKLevel);
  MODIFY_REG(tmpbdtr, TIM_BDTR_OSSI, TIM_BDTRInitStruct->OSSIState);
  MODIFY_REG(tmpbdtr, TIM_BDTR_OSSR, TIM_BDTRInitStruct->OSSRState);
  MODIFY_REG(tmpbdtr, TIM_BDTR_BKE, TIM_BDTRInitStruct->BreakState);
  MODIFY_REG(tmpbdtr, TIM_BDTR_BKP, TIM_BDTRInitStruct->BreakPolarity);
  MODIFY_REG(tmpbdtr, TIM_BDTR_AOE, TIM_BDTRInitStruct->AutomaticOutput);
  MODIFY_REG(tmpbdtr, TIM_BDTR_MOE, TIM_BDTRInitStruct->AutomaticOutput);
  if (IS_TIM_ADVANCED_INSTANCE(TIMx))
  {
    MODIFY_REG(tmpbdtr, TIM_BDTR_BKF, TIM_BDTRInitStruct->BreakFilter);
    MODIFY_REG(tmpbdtr, TIM_BDTR_BKBID, TIM_BDTRInitStruct->BreakAFMode);
  }

  if (IS_TIM_BKIN2_INSTANCE(TIMx))
  {
    MODIFY_REG(tmpbdtr, TIM_BDTR_BK2F, (TIM_BDTRInitStruct->Break2Filter));
    MODIFY_REG(tmpbdtr, TIM_BDTR_BK2E, TIM_BDTRInitStruct->Break2State);
    MODIFY_REG(tmpbdtr, TIM_BDTR_BK2P, TIM_BDTRInitStruct->Break2Polarity);
    MODIFY_REG(tmpbdtr, TIM_BDTR_BK2BID, TIM_BDTRInitStruct->Break2AFMode);
  }

  /* Set TIMx_BDTR */
  TIM_WriteReg(TIMx, BDTR, tmpbdtr);
}

/**
  * @brief  Configure the TIMx output channel 1.
  * @param  TIMx Timer Instance
  * @param  TIM_OCInitStruct pointer to the the TIMx output channel 1 configuration data structure
  * @param  TIMx:
          @arg TIM Instance
  * @param  OCMode: 
  *         @arg @ref TIM_OCMODE_FROZEN          
  *         @arg @ref TIM_OCMODE_ACTIVE          
  *         @arg @ref TIM_OCMODE_INACTIVE        
  *         @arg @ref TIM_OCMODE_TOGGLE          
  *         @arg @ref TIM_OCMODE_FORCED_INACTIVE 
  *         @arg @ref TIM_OCMODE_FORCED_ACTIVE   
  *         @arg @ref TIM_OCMODE_PWM1            
  *         @arg @ref TIM_OCMODE_PWM2            
  *         @arg @ref TIM_OCMODE_RETRIG_OPM1     
  *         @arg @ref TIM_OCMODE_RETRIG_OPM2     
  *         @arg @ref TIM_OCMODE_COMBINED_PWM1   
  *         @arg @ref TIM_OCMODE_COMBINED_PWM2   
  *         @arg @ref TIM_OCMODE_ASSYMETRIC_PWM1 
  *         @arg @ref TIM_OCMODE_ASSYMETRIC_PWM2 
  *         @arg @ref TIM_OCMODE_PULSE_ON_COMPARE
  *         @arg @ref TIM_OCMODE_DIRECTION_OUTPUT
  * @param  OutputState:
  *         @arg @ref TIM_OUTPUTSTATE_DISABLE
  *         @arg @ref TIM_OUTPUTSTATE_ENABLE 
  * @param  OutputNState:  
  *         @arg @ref TIM_OUTPUTNSTATE_DISABLE
  *         @arg @ref TIM_OUTPUTNSTATE_ENABLE 
  * @param  Pulse between Min_Data=0 and Max_Data=65535
  * @param  OCPolarity:
  *         @arg @ref TIM_OCPOLARITY_HIGH
  *         @arg @ref TIM_OCPOLARITY_LOW
  * @param  OCNPolarity:  
  *         @arg @ref TIM_OCNPOLARITY_HIGH
  *         @arg @ref TIM_OCNPOLARITY_LOW 
  * @param  OCIdleState:
  *         @arg @ref TIM_OCIDLESTATE_RESET
  *         @arg @ref TIM_OCIDLESTATE_SET  
  * @param  OCNIdleState:  
  *         @arg @ref TIM_OCNIDLESTATE_RESET
  *         @arg @ref TIM_OCNIDLESTATE_SET  
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx registers are de-initialized
  *          - ERROR: not applicable
  */
void TIM_OC1Init(TIM_TypeDef *TIMx, TIM_OCInitTypeDef *TIM_OCInitStruct)
{
  uint32_t tmpccmr1;
  uint32_t tmpccer;
  uint32_t tmpcr2;

  /* Disable the Channel 1: Reset the CC1E Bit */
  CLEAR_BIT(TIMx->CCER, TIM_CCER_CC1E);

  /* Get the TIMx CCER register value */
  tmpccer = TIM_ReadReg(TIMx, CCER);

  /* Get the TIMx CR2 register value */
  tmpcr2 = TIM_ReadReg(TIMx, CR2);

  /* Get the TIMx CCMR1 register value */
  tmpccmr1 = TIM_ReadReg(TIMx, CCMR1);

  /* Reset Capture/Compare selection Bits */
  CLEAR_BIT(tmpccmr1, TIM_CCMR1_CC1S);

  /* Set the Output Compare Mode */
  MODIFY_REG(tmpccmr1, TIM_CCMR1_OC1M, TIM_OCInitStruct->OCMode);

  /* Set the Output Compare Polarity */
  MODIFY_REG(tmpccer, TIM_CCER_CC1P, TIM_OCInitStruct->OCPolarity);

  /* Set the Output State */
  MODIFY_REG(tmpccer, TIM_CCER_CC1E, TIM_OCInitStruct->OutputState);

  if (IS_TIM_BREAK_INSTANCE(TIMx))
  {
    /* Set the complementary output Polarity */
    MODIFY_REG(tmpccer, TIM_CCER_CC1NP, TIM_OCInitStruct->OCNPolarity);

    /* Set the complementary output State */
    MODIFY_REG(tmpccer, TIM_CCER_CC1NE, TIM_OCInitStruct->OutputNState);

    /* Set the Output Idle state */
    MODIFY_REG(tmpcr2, TIM_CR2_OIS1, TIM_OCInitStruct->OCIdleState);

    /* Set the complementary output Idle state */
    MODIFY_REG(tmpcr2, TIM_CR2_OIS1N, TIM_OCInitStruct->OCNIdleState);
  }

  /* Write to TIMx CR2 */
  TIM_WriteReg(TIMx, CR2, tmpcr2);

  /* Write to TIMx CCMR1 */
  TIM_WriteReg(TIMx, CCMR1, tmpccmr1);

  /* Set the Capture Compare Register value */
  TIM_Set_OC_CompareCH1(TIMx, TIM_OCInitStruct->Pulse);

  /* Write to TIMx CCER */
  TIM_WriteReg(TIMx, CCER, tmpccer);
}

/**
  * @brief  Configure the TIMx output channel 2.
  * @param  TIMx Timer Instance
  * @param  TIM_OCInitStruct pointer to the the TIMx output channel 2 configuration data structure
  * @param  TIMx:
          @arg TIM Instance
  * @param  OCMode: 
  *         @arg @ref TIM_OCMODE_FROZEN          
  *         @arg @ref TIM_OCMODE_ACTIVE          
  *         @arg @ref TIM_OCMODE_INACTIVE        
  *         @arg @ref TIM_OCMODE_TOGGLE          
  *         @arg @ref TIM_OCMODE_FORCED_INACTIVE 
  *         @arg @ref TIM_OCMODE_FORCED_ACTIVE   
  *         @arg @ref TIM_OCMODE_PWM1            
  *         @arg @ref TIM_OCMODE_PWM2            
  *         @arg @ref TIM_OCMODE_RETRIG_OPM1     
  *         @arg @ref TIM_OCMODE_RETRIG_OPM2     
  *         @arg @ref TIM_OCMODE_COMBINED_PWM1   
  *         @arg @ref TIM_OCMODE_COMBINED_PWM2   
  *         @arg @ref TIM_OCMODE_ASSYMETRIC_PWM1 
  *         @arg @ref TIM_OCMODE_ASSYMETRIC_PWM2 
  *         @arg @ref TIM_OCMODE_PULSE_ON_COMPARE
  *         @arg @ref TIM_OCMODE_DIRECTION_OUTPUT
  * @param  OutputState:
  *         @arg @ref TIM_OUTPUTSTATE_DISABLE
  *         @arg @ref TIM_OUTPUTSTATE_ENABLE 
  * @param  OutputNState:  
  *         @arg @ref TIM_OUTPUTNSTATE_DISABLE
  *         @arg @ref TIM_OUTPUTNSTATE_ENABLE 
  * @param  Pulse between Min_Data=0 and Max_Data=65535
  * @param  OCPolarity:
  *         @arg @ref TIM_OCPOLARITY_HIGH
  *         @arg @ref TIM_OCPOLARITY_LOW
  * @param  OCNPolarity:  
  *         @arg @ref TIM_OCNPOLARITY_HIGH
  *         @arg @ref TIM_OCNPOLARITY_LOW 
  * @param  OCIdleState:
  *         @arg @ref TIM_OCIDLESTATE_RESET
  *         @arg @ref TIM_OCIDLESTATE_SET  
  * @param  OCNIdleState:  
  *         @arg @ref TIM_OCNIDLESTATE_RESET
  *         @arg @ref TIM_OCNIDLESTATE_SET  
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx registers are de-initialized
  *          - ERROR: not applicable
  */
void TIM_OC2Init(TIM_TypeDef *TIMx, TIM_OCInitTypeDef *TIM_OCInitStruct)
{
  uint32_t tmpccmr1;
  uint32_t tmpccer;
  uint32_t tmpcr2;

  /* Disable the Channel 2: Reset the CC2E Bit */
  CLEAR_BIT(TIMx->CCER, TIM_CCER_CC2E);

  /* Get the TIMx CCER register value */
  tmpccer =  TIM_ReadReg(TIMx, CCER);

  /* Get the TIMx CR2 register value */
  tmpcr2 = TIM_ReadReg(TIMx, CR2);

  /* Get the TIMx CCMR1 register value */
  tmpccmr1 = TIM_ReadReg(TIMx, CCMR1);

  /* Reset Capture/Compare selection Bits */
  CLEAR_BIT(tmpccmr1, TIM_CCMR1_CC2S);

  /* Select the Output Compare Mode */
  MODIFY_REG(tmpccmr1, TIM_CCMR1_OC2M, TIM_OCInitStruct->OCMode << 8U);

  /* Set the Output Compare Polarity */
  MODIFY_REG(tmpccer, TIM_CCER_CC2P, TIM_OCInitStruct->OCPolarity << 4U);

  /* Set the Output State */
  MODIFY_REG(tmpccer, TIM_CCER_CC2E, TIM_OCInitStruct->OutputState << 4U);

  if (IS_TIM_BREAK_INSTANCE(TIMx))
  {
    /* Set the complementary output Polarity */
    MODIFY_REG(tmpccer, TIM_CCER_CC2NP, TIM_OCInitStruct->OCNPolarity << 4U);

    /* Set the complementary output State */
    MODIFY_REG(tmpccer, TIM_CCER_CC2NE, TIM_OCInitStruct->OutputNState << 4U);

    /* Set the Output Idle state */
    MODIFY_REG(tmpcr2, TIM_CR2_OIS2, TIM_OCInitStruct->OCIdleState << 2U);

    /* Set the complementary output Idle state */
    MODIFY_REG(tmpcr2, TIM_CR2_OIS2N, TIM_OCInitStruct->OCNIdleState << 2U);
  }

  /* Write to TIMx CR2 */
  TIM_WriteReg(TIMx, CR2, tmpcr2);

  /* Write to TIMx CCMR1 */
  TIM_WriteReg(TIMx, CCMR1, tmpccmr1);

  /* Set the Capture Compare Register value */
  TIM_Set_OC_CompareCH2(TIMx, TIM_OCInitStruct->Pulse);

  /* Write to TIMx CCER */
  TIM_WriteReg(TIMx, CCER, tmpccer);
}

/**
  * @brief  Configure the TIMx output channel 3.
  * @param  TIMx Timer Instance
  * @param  TIM_OCInitStruct pointer to the the TIMx output channel 3 configuration data structure
  * @param  TIMx:
  *         @arg TIM Instance
  * @param  OCMode: 
  *         @arg @ref TIM_OCMODE_FROZEN          
  *         @arg @ref TIM_OCMODE_ACTIVE          
  *         @arg @ref TIM_OCMODE_INACTIVE        
  *         @arg @ref TIM_OCMODE_TOGGLE          
  *         @arg @ref TIM_OCMODE_FORCED_INACTIVE 
  *         @arg @ref TIM_OCMODE_FORCED_ACTIVE   
  *         @arg @ref TIM_OCMODE_PWM1            
  *         @arg @ref TIM_OCMODE_PWM2            
  *         @arg @ref TIM_OCMODE_RETRIG_OPM1     
  *         @arg @ref TIM_OCMODE_RETRIG_OPM2     
  *         @arg @ref TIM_OCMODE_COMBINED_PWM1   
  *         @arg @ref TIM_OCMODE_COMBINED_PWM2   
  *         @arg @ref TIM_OCMODE_ASSYMETRIC_PWM1 
  *         @arg @ref TIM_OCMODE_ASSYMETRIC_PWM2 
  *         @arg @ref TIM_OCMODE_PULSE_ON_COMPARE
  *         @arg @ref TIM_OCMODE_DIRECTION_OUTPUT
  * @param  OutputState:
  *         @arg @ref TIM_OUTPUTSTATE_DISABLE
  *         @arg @ref TIM_OUTPUTSTATE_ENABLE 
  * @param  OutputNState:  
  *         @arg @ref TIM_OUTPUTNSTATE_DISABLE
  *         @arg @ref TIM_OUTPUTNSTATE_ENABLE 
  * @param  Pulse between Min_Data=0 and Max_Data=65535
  * @param  OCPolarity:
  *         @arg @ref TIM_OCPOLARITY_HIGH
  *         @arg @ref TIM_OCPOLARITY_LOW
  * @param  OCNPolarity:  
  *         @arg @ref TIM_OCNPOLARITY_HIGH
  *         @arg @ref TIM_OCNPOLARITY_LOW 
  * @param  OCIdleState:
  *         @arg @ref TIM_OCIDLESTATE_RESET
  *         @arg @ref TIM_OCIDLESTATE_SET  
  * @param  OCNIdleState:  
  *         @arg @ref TIM_OCNIDLESTATE_RESET
  *         @arg @ref TIM_OCNIDLESTATE_SET  
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx registers are de-initialized
  *          - ERROR: not applicable
  */
void TIM_OC3Init(TIM_TypeDef *TIMx, TIM_OCInitTypeDef *TIM_OCInitStruct)
{
  uint32_t tmpccmr2;
  uint32_t tmpccer;
  uint32_t tmpcr2;

  /* Disable the Channel 3: Reset the CC3E Bit */
  CLEAR_BIT(TIMx->CCER, TIM_CCER_CC3E);

  /* Get the TIMx CCER register value */
  tmpccer =  TIM_ReadReg(TIMx, CCER);

  /* Get the TIMx CR2 register value */
  tmpcr2 = TIM_ReadReg(TIMx, CR2);

  /* Get the TIMx CCMR2 register value */
  tmpccmr2 = TIM_ReadReg(TIMx, CCMR2);

  /* Reset Capture/Compare selection Bits */
  CLEAR_BIT(tmpccmr2, TIM_CCMR2_CC3S);

  /* Select the Output Compare Mode */
  MODIFY_REG(tmpccmr2, TIM_CCMR2_OC3M, TIM_OCInitStruct->OCMode);

  /* Set the Output Compare Polarity */
  MODIFY_REG(tmpccer, TIM_CCER_CC3P, TIM_OCInitStruct->OCPolarity << 8U);

  /* Set the Output State */
  MODIFY_REG(tmpccer, TIM_CCER_CC3E, TIM_OCInitStruct->OutputState << 8U);

  if (IS_TIM_BREAK_INSTANCE(TIMx))
  {
    /* Set the complementary output Polarity */
    MODIFY_REG(tmpccer, TIM_CCER_CC3NP, TIM_OCInitStruct->OCNPolarity << 8U);

    /* Set the complementary output State */
    MODIFY_REG(tmpccer, TIM_CCER_CC3NE, TIM_OCInitStruct->OutputNState << 8U);

    /* Set the Output Idle state */
    MODIFY_REG(tmpcr2, TIM_CR2_OIS3, TIM_OCInitStruct->OCIdleState << 4U);

    /* Set the complementary output Idle state */
    MODIFY_REG(tmpcr2, TIM_CR2_OIS3N, TIM_OCInitStruct->OCNIdleState << 4U);
  }

  /* Write to TIMx CR2 */
  TIM_WriteReg(TIMx, CR2, tmpcr2);

  /* Write to TIMx CCMR2 */
  TIM_WriteReg(TIMx, CCMR2, tmpccmr2);

  /* Set the Capture Compare Register value */
  TIM_Set_OC_CompareCH3(TIMx, TIM_OCInitStruct->Pulse);

  /* Write to TIMx CCER */
  TIM_WriteReg(TIMx, CCER, tmpccer);
}

/**
  * @brief  Configure the TIMx output channel 4.
  * @param  TIMx Timer Instance
  * @param  TIM_OCInitStruct pointer to the the TIMx output channel 4 configuration data structure
  * @param  TIMx:
  *         @arg TIM Instance
  * @param  OCMode: 
  *         @arg @ref TIM_OCMODE_FROZEN          
  *         @arg @ref TIM_OCMODE_ACTIVE          
  *         @arg @ref TIM_OCMODE_INACTIVE        
  *         @arg @ref TIM_OCMODE_TOGGLE          
  *         @arg @ref TIM_OCMODE_FORCED_INACTIVE 
  *         @arg @ref TIM_OCMODE_FORCED_ACTIVE   
  *         @arg @ref TIM_OCMODE_PWM1            
  *         @arg @ref TIM_OCMODE_PWM2            
  *         @arg @ref TIM_OCMODE_RETRIG_OPM1     
  *         @arg @ref TIM_OCMODE_RETRIG_OPM2     
  *         @arg @ref TIM_OCMODE_COMBINED_PWM1   
  *         @arg @ref TIM_OCMODE_COMBINED_PWM2   
  *         @arg @ref TIM_OCMODE_ASSYMETRIC_PWM1 
  *         @arg @ref TIM_OCMODE_ASSYMETRIC_PWM2 
  *         @arg @ref TIM_OCMODE_PULSE_ON_COMPARE
  *         @arg @ref TIM_OCMODE_DIRECTION_OUTPUT
  * @param  OutputState:
  *         @arg @ref TIM_OUTPUTSTATE_DISABLE
  *         @arg @ref TIM_OUTPUTSTATE_ENABLE 
  * @param  Pulse between Min_Data=0 and Max_Data=65535
  * @param  OCPolarity:
  *         @arg @ref TIM_OCPOLARITY_HIGH
  *         @arg @ref TIM_OCPOLARITY_LOW
  * @param  OCIdleState:
  *         @arg @ref TIM_OCIDLESTATE_RESET
  *         @arg @ref TIM_OCIDLESTATE_SET  
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx registers are de-initialized
  *          - ERROR: not applicable
  */
void TIM_OC4Init(TIM_TypeDef *TIMx, TIM_OCInitTypeDef *TIM_OCInitStruct)
{
  uint32_t tmpccmr2;
  uint32_t tmpccer;
  uint32_t tmpcr2;

  /* Disable the Channel 4: Reset the CC4E Bit */
  CLEAR_BIT(TIMx->CCER, TIM_CCER_CC4E);

  /* Get the TIMx CCER register value */
  tmpccer = TIM_ReadReg(TIMx, CCER);

  /* Get the TIMx CR2 register value */
  tmpcr2 =  TIM_ReadReg(TIMx, CR2);

  /* Get the TIMx CCMR2 register value */
  tmpccmr2 = TIM_ReadReg(TIMx, CCMR2);

  /* Reset Capture/Compare selection Bits */
  CLEAR_BIT(tmpccmr2, TIM_CCMR2_CC4S);

  /* Select the Output Compare Mode */
  MODIFY_REG(tmpccmr2, TIM_CCMR2_OC4M, TIM_OCInitStruct->OCMode << 8U);

  /* Set the Output Compare Polarity */
  MODIFY_REG(tmpccer, TIM_CCER_CC4P, TIM_OCInitStruct->OCPolarity << 12U);

  /* Set the Output State */
  MODIFY_REG(tmpccer, TIM_CCER_CC4E, TIM_OCInitStruct->OutputState << 12U);

  if (IS_TIM_BREAK_INSTANCE(TIMx))
  {
    /* Set the Output Idle state */
    MODIFY_REG(tmpcr2, TIM_CR2_OIS4, TIM_OCInitStruct->OCIdleState << 6U);
  }

  /* Write to TIMx CR2 */
  TIM_WriteReg(TIMx, CR2, tmpcr2);

  /* Write to TIMx CCMR2 */
  TIM_WriteReg(TIMx, CCMR2, tmpccmr2);

  /* Set the Capture Compare Register value */
  TIM_Set_OC_CompareCH4(TIMx, TIM_OCInitStruct->Pulse);

  /* Write to TIMx CCER */
  TIM_WriteReg(TIMx, CCER, tmpccer);
}

/**
  * @brief  Configure the TIMx output channel 5.
  * @param  TIMx Timer Instance
  * @param  TIM_OCInitStruct pointer to the the TIMx output channel 5 configuration data structure
  * @param  TIMx:
  *         @arg TIM Instance
  * @param  OCMode: 
  *         @arg @ref TIM_OCMODE_FROZEN          
  *         @arg @ref TIM_OCMODE_ACTIVE          
  *         @arg @ref TIM_OCMODE_INACTIVE        
  *         @arg @ref TIM_OCMODE_TOGGLE          
  *         @arg @ref TIM_OCMODE_FORCED_INACTIVE 
  *         @arg @ref TIM_OCMODE_FORCED_ACTIVE   
  *         @arg @ref TIM_OCMODE_PWM1            
  *         @arg @ref TIM_OCMODE_PWM2            
  *         @arg @ref TIM_OCMODE_RETRIG_OPM1     
  *         @arg @ref TIM_OCMODE_RETRIG_OPM2     
  *         @arg @ref TIM_OCMODE_COMBINED_PWM1   
  *         @arg @ref TIM_OCMODE_COMBINED_PWM2   
  *         @arg @ref TIM_OCMODE_ASSYMETRIC_PWM1 
  *         @arg @ref TIM_OCMODE_ASSYMETRIC_PWM2 
  *         @arg @ref TIM_OCMODE_PULSE_ON_COMPARE
  *         @arg @ref TIM_OCMODE_DIRECTION_OUTPUT
  * @param  OutputState:
  *         @arg @ref TIM_OUTPUTSTATE_DISABLE
  *         @arg @ref TIM_OUTPUTSTATE_ENABLE 
  * @param  Pulse between Min_Data=0 and Max_Data=65535
  * @param  OCPolarity:
  *         @arg @ref TIM_OCPOLARITY_HIGH
  *         @arg @ref TIM_OCPOLARITY_LOW
  * @param  OCIdleState:
  *         @arg @ref TIM_OCIDLESTATE_RESET
  *         @arg @ref TIM_OCIDLESTATE_SET  
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx registers are de-initialized
  *          - ERROR: not applicable
  */
void TIM_OC5Init(TIM_TypeDef *TIMx, TIM_OCInitTypeDef *TIM_OCInitStruct)
{
  uint32_t tmpccmr3;
  uint32_t tmpccer;
  
  /* Disable the Channel 5: Reset the CC5E Bit */
  CLEAR_BIT(TIMx->CCER, TIM_CCER_CC5E);

  /* Get the TIMx CCER register value */
  tmpccer = TIM_ReadReg(TIMx, CCER);

  /* Get the TIMx CCMR3 register value */
  tmpccmr3 = TIM_ReadReg(TIMx, CCMR3);

  /* Select the Output Compare Mode */
  MODIFY_REG(tmpccmr3, TIM_CCMR3_OC5M, TIM_OCInitStruct->OCMode);

  /* Set the Output Compare Polarity */
  MODIFY_REG(tmpccer, TIM_CCER_CC5P, TIM_OCInitStruct->OCPolarity << 16U);

  /* Set the Output State */
  MODIFY_REG(tmpccer, TIM_CCER_CC5E, TIM_OCInitStruct->OutputState << 16U);

  if (IS_TIM_BREAK_INSTANCE(TIMx))
  {
    /* Set the Output Idle state */
    MODIFY_REG(TIMx->CR2, TIM_CR2_OIS5, TIM_OCInitStruct->OCIdleState << 8U);

  }

  /* Write to TIMx CCMR3 */
  TIM_WriteReg(TIMx, CCMR3, tmpccmr3);

  /* Set the Capture Compare Register value */
  TIM_Set_OC_CompareCH5(TIMx, TIM_OCInitStruct->Pulse);

  /* Write to TIMx CCER */
  TIM_WriteReg(TIMx, CCER, tmpccer);
}

/**
  * @brief  Configure the TIMx output channel 6.
  * @param  TIMx Timer Instance
  * @param  TIM_OCInitStruct pointer to the the TIMx output channel 6 configuration data structure
  * @param  TIMx:
  *         @arg TIM Instance
  * @param  OCMode: 
  *         @arg @ref TIM_OCMODE_FROZEN          
  *         @arg @ref TIM_OCMODE_ACTIVE          
  *         @arg @ref TIM_OCMODE_INACTIVE        
  *         @arg @ref TIM_OCMODE_TOGGLE          
  *         @arg @ref TIM_OCMODE_FORCED_INACTIVE 
  *         @arg @ref TIM_OCMODE_FORCED_ACTIVE   
  *         @arg @ref TIM_OCMODE_PWM1            
  *         @arg @ref TIM_OCMODE_PWM2            
  *         @arg @ref TIM_OCMODE_RETRIG_OPM1     
  *         @arg @ref TIM_OCMODE_RETRIG_OPM2     
  *         @arg @ref TIM_OCMODE_COMBINED_PWM1   
  *         @arg @ref TIM_OCMODE_COMBINED_PWM2   
  *         @arg @ref TIM_OCMODE_ASSYMETRIC_PWM1 
  *         @arg @ref TIM_OCMODE_ASSYMETRIC_PWM2 
  *         @arg @ref TIM_OCMODE_PULSE_ON_COMPARE
  *         @arg @ref TIM_OCMODE_DIRECTION_OUTPUT
  * @param  OutputState:
  *         @arg @ref TIM_OUTPUTSTATE_DISABLE
  *         @arg @ref TIM_OUTPUTSTATE_ENABLE 
  * @param  Pulse between Min_Data=0 and Max_Data=65535
  * @param  OCPolarity:
  *         @arg @ref TIM_OCPOLARITY_HIGH
  *         @arg @ref TIM_OCPOLARITY_LOW
  * @param  OCIdleState:
  *         @arg @ref TIM_OCIDLESTATE_RESET
  *         @arg @ref TIM_OCIDLESTATE_SET  
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx registers are de-initialized
  *          - ERROR: not applicable
  */
void TIM_OC6Init(TIM_TypeDef *TIMx, TIM_OCInitTypeDef *TIM_OCInitStruct)
{
  uint32_t tmpccmr3;
  uint32_t tmpccer;

  /* Disable the Channel 5: Reset the CC6E Bit */
  CLEAR_BIT(TIMx->CCER, TIM_CCER_CC6E);

  /* Get the TIMx CCER register value */
  tmpccer = TIM_ReadReg(TIMx, CCER);

  /* Get the TIMx CCMR3 register value */
  tmpccmr3 = TIM_ReadReg(TIMx, CCMR3);

  /* Select the Output Compare Mode */
  MODIFY_REG(tmpccmr3, TIM_CCMR3_OC6M, TIM_OCInitStruct->OCMode << 8U);

  /* Set the Output Compare Polarity */
  MODIFY_REG(tmpccer, TIM_CCER_CC6P, TIM_OCInitStruct->OCPolarity << 20U);

  /* Set the Output State */
  MODIFY_REG(tmpccer, TIM_CCER_CC6E, TIM_OCInitStruct->OutputState << 20U);

  if (IS_TIM_BREAK_INSTANCE(TIMx))
  {
    /* Set the Output Idle state */
    MODIFY_REG(TIMx->CR2, TIM_CR2_OIS6, TIM_OCInitStruct->OCIdleState << 10U);
  }

  /* Write to TIMx CCMR3 */
  TIM_WriteReg(TIMx, CCMR3, tmpccmr3);

  /* Set the Capture Compare Register value */
  TIM_Set_OC_CompareCH6(TIMx, TIM_OCInitStruct->Pulse);

  /* Write to TIMx CCER */
  TIM_WriteReg(TIMx, CCER, tmpccer);
}

/**
  * @brief  Configure the TIMx input channel 1.
  * @param  TIMx Timer Instance
  * @param  TIM_ICInitStruct pointer to the the TIMx input channel 1 configuration data structure
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx registers are de-initialized
  *          - ERROR: not applicable
  */
void TIM_Set_TI1(TIM_TypeDef *TIMx, TIM_ICInitTypeDef *TIM_ICInitStruct)
{
  /* Disable the Channel 1: Reset the CC1E Bit */
  TIMx->CCER &= (uint32_t)~TIM_CCER_CC1E;

  /* Select the Input and set the filter and the prescaler value */
  MODIFY_REG(TIMx->CCMR1,
             (TIM_CCMR1_CC1S | TIM_CCMR1_IC1F | TIM_CCMR1_IC1PSC),
             (TIM_ICInitStruct->ICSelection | TIM_ICInitStruct->ICFilter | TIM_ICInitStruct->ICPrescaler) >> 16U);

  /* Select the Polarity and set the CC1E Bit */
  MODIFY_REG(TIMx->CCER,
             (TIM_CCER_CC1P | TIM_CCER_CC1NP),
             (TIM_ICInitStruct->ICPolarity | TIM_CCER_CC1E));

}

/**
  * @brief  Configure the TIMx input channel 2.
  * @param  TIMx Timer Instance
  * @param  TIM_ICInitStruct pointer to the the TIMx input channel 2 configuration data structure
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx registers are de-initialized
  *          - ERROR: not applicable
  */
void TIM_Set_TI2(TIM_TypeDef *TIMx, TIM_ICInitTypeDef *TIM_ICInitStruct)
{
  /* Disable the Channel 2: Reset the CC2E Bit */
  TIMx->CCER &= (uint32_t)~TIM_CCER_CC2E;

  /* Select the Input and set the filter and the prescaler value */
  MODIFY_REG(TIMx->CCMR1,
             (TIM_CCMR1_CC2S | TIM_CCMR1_IC2F | TIM_CCMR1_IC2PSC),
             (TIM_ICInitStruct->ICSelection | TIM_ICInitStruct->ICFilter | TIM_ICInitStruct->ICPrescaler) >> 8U);

  /* Select the Polarity and set the CC2E Bit */
  MODIFY_REG(TIMx->CCER,
             (TIM_CCER_CC2P | TIM_CCER_CC2NP),
             ((TIM_ICInitStruct->ICPolarity << 4U) | TIM_CCER_CC2E));
}

/**
  * @brief  Configure the TIMx input channel 3.
  * @param  TIMx Timer Instance
  * @param  TIM_ICInitStruct pointer to the the TIMx input channel 3 configuration data structure
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx registers are de-initialized
  *          - ERROR: not applicable
  */
void TIM_Set_TI3(TIM_TypeDef *TIMx, TIM_ICInitTypeDef *TIM_ICInitStruct)
{
  /* Disable the Channel 3: Reset the CC3E Bit */
  TIMx->CCER &= (uint32_t)~TIM_CCER_CC3E;

  /* Select the Input and set the filter and the prescaler value */
  MODIFY_REG(TIMx->CCMR2,
             (TIM_CCMR2_CC3S | TIM_CCMR2_IC3F | TIM_CCMR2_IC3PSC),
             (TIM_ICInitStruct->ICSelection | TIM_ICInitStruct->ICFilter | TIM_ICInitStruct->ICPrescaler) >> 16U);

  /* Select the Polarity and set the CC3E Bit */
  MODIFY_REG(TIMx->CCER,
             (TIM_CCER_CC3P | TIM_CCER_CC3NP),
             ((TIM_ICInitStruct->ICPolarity << 8U) | TIM_CCER_CC3E));

}

/**
  * @brief  Configure the TIMx input channel 4.
  * @param  TIMx Timer Instance
  * @param  TIM_ICInitStruct pointer to the the TIMx input channel 4 configuration data structure
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: TIMx registers are de-initialized
  *          - ERROR: not applicable
  */
void TIM_Set_TI4(TIM_TypeDef *TIMx, TIM_ICInitTypeDef *TIM_ICInitStruct)
{
  /* Disable the Channel 4: Reset the CC4E Bit */
  TIMx->CCER &= (uint32_t)~TIM_CCER_CC4E;

  /* Select the Input and set the filter and the prescaler value */
  MODIFY_REG(TIMx->CCMR2,
             (TIM_CCMR2_CC4S | TIM_CCMR2_IC4F | TIM_CCMR2_IC4PSC),
             (TIM_ICInitStruct->ICSelection | TIM_ICInitStruct->ICFilter | TIM_ICInitStruct->ICPrescaler) >> 8U);

  /* Select the Polarity and set the CC2E Bit */
  MODIFY_REG(TIMx->CCER,
             (TIM_CCER_CC4P),
             ((TIM_ICInitStruct->ICPolarity << 12U) | TIM_CCER_CC4E));

}

/**
  * @brief  Configure an output channel.
  * @rmtoll CCMR1        CC1S          TIM_OC_ConfigOutput\n
  *         CCMR1        CC2S          TIM_OC_ConfigOutput\n
  *         CCMR2        CC3S          TIM_OC_ConfigOutput\n
  *         CCMR2        CC4S          TIM_OC_ConfigOutput\n
  *         CCMR3        CC5S          TIM_OC_ConfigOutput\n
  *         CCMR3        CC6S          TIM_OC_ConfigOutput\n
  *         CCER         CC1P          TIM_OC_ConfigOutput\n
  *         CCER         CC2P          TIM_OC_ConfigOutput\n
  *         CCER         CC3P          TIM_OC_ConfigOutput\n
  *         CCER         CC4P          TIM_OC_ConfigOutput\n
  *         CCER         CC5P          TIM_OC_ConfigOutput\n
  *         CCER         CC6P          TIM_OC_ConfigOutput\n
  *         CR2          OIS1          TIM_OC_ConfigOutput\n
  *         CR2          OIS2          TIM_OC_ConfigOutput\n
  *         CR2          OIS3          TIM_OC_ConfigOutput\n
  *         CR2          OIS4          TIM_OC_ConfigOutput\n
  *         CR2          OIS5          TIM_OC_ConfigOutput\n
  *         CR2          OIS6          TIM_OC_ConfigOutput
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH4
  *         @arg @ref TIM_CHANNEL_CH5
  *         @arg @ref TIM_CHANNEL_CH6
  * @param  Configuration This parameter must be a combination of all the following values:
  *         @arg @ref TIM_OCPOLARITY_HIGH or @ref TIM_OCPOLARITY_LOW
  *         @arg @ref TIM_OCIDLESTATE_SET or @ref TIM_OCIDLESTATE_RESET
  * @retval None
  */
void TIM_Set_OC_Output(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t Configuration)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  CLEAR_BIT(*pReg, (TIM_CCMR1_CC1S << SHIFT_TAB_OCxx[iChannel]));
  MODIFY_REG(TIMx->CCER, (TIM_CCER_CC1P << SHIFT_TAB_CCxP[iChannel]),
             (Configuration & TIM_CCER_CC1P) << SHIFT_TAB_CCxP[iChannel]);
  MODIFY_REG(TIMx->CR2, (TIM_CR2_OIS1 << SHIFT_TAB_OISx[iChannel]),
             (Configuration & TIM_CR2_OIS1) << SHIFT_TAB_OISx[iChannel]);
}

/**
  * @brief  Configure input channel.
  * @rmtoll CCMR1        CC1S          TIM_IC_Config\n
  *         CCMR1        IC1PSC        TIM_IC_Config\n
  *         CCMR1        IC1F          TIM_IC_Config\n
  *         CCMR1        CC2S          TIM_IC_Config\n
  *         CCMR1        IC2PSC        TIM_IC_Config\n
  *         CCMR1        IC2F          TIM_IC_Config\n
  *         CCMR2        CC3S          TIM_IC_Config\n
  *         CCMR2        IC3PSC        TIM_IC_Config\n
  *         CCMR2        IC3F          TIM_IC_Config\n
  *         CCMR2        CC4S          TIM_IC_Config\n
  *         CCMR2        IC4PSC        TIM_IC_Config\n
  *         CCMR2        IC4F          TIM_IC_Config\n
  *         CCER         CC1P          TIM_IC_Config\n
  *         CCER         CC1NP         TIM_IC_Config\n
  *         CCER         CC2P          TIM_IC_Config\n
  *         CCER         CC2NP         TIM_IC_Config\n
  *         CCER         CC3P          TIM_IC_Config\n
  *         CCER         CC3NP         TIM_IC_Config\n
  *         CCER         CC4P          TIM_IC_Config
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH4
  * @param  Configuration This parameter must be a combination of all the following values:
  *         @arg @ref TIM_ACTIVEINPUT_DIRECTTI or @ref TIM_ACTIVEINPUT_INDIRECTTI or @ref TIM_ACTIVEINPUT_TRC
  *         @arg @ref TIM_ICPSC_DIV1 or ... or @ref TIM_ICPSC_DIV8
  *         @arg @ref TIM_IC_FILTER_FDIV1 or ... or @ref TIM_IC_FILTER_FDIV32_N8
  *         @arg @ref TIM_IC_POLARITY_RISING or @ref TIM_IC_POLARITY_FALLING or @ref TIM_IC_POLARITY_BOTHEDGE
  * @retval None
  */
void TIM_IC_Config(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t Configuration)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  MODIFY_REG(*pReg, ((TIM_CCMR1_IC1F | TIM_CCMR1_IC1PSC | TIM_CCMR1_CC1S) << SHIFT_TAB_ICxx[iChannel]),
             ((Configuration >> 16U) & (TIM_CCMR1_IC1F | TIM_CCMR1_IC1PSC | TIM_CCMR1_CC1S))                \
             << SHIFT_TAB_ICxx[iChannel]);
  MODIFY_REG(TIMx->CCER, ((TIM_CCER_CC1NP | TIM_CCER_CC1P) << SHIFT_TAB_CCxP[iChannel]),
             (Configuration & (TIM_CCER_CC1NP | TIM_CCER_CC1P)) << SHIFT_TAB_CCxP[iChannel]);
}


