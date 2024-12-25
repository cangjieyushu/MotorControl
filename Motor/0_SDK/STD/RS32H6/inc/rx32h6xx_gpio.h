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
* File         : rx32h6xx_gpio.h
* By           : RX_SD_Team
* Version      : V1.0.0
* Description  : Only rx32h6xx
*********************************************************************************************************
*/
#ifndef _rx32h6xx_GPIO_H
#define _rx32h6xx_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rx32h6xx.h"
#include "rx32h6xx_rcc.h"

typedef struct
{
  uint32_t Pin;        /*!< Specifies the GPIO pins to be configured.
                           This parameter can be any value of @ref GPIO_pins */

  uint32_t Mode;       /*!< Specifies the operating mode for the selected pins.
                           This parameter can be a value of @ref GPIO_mode */

  uint32_t Pull;       /*!< Specifies the Pull-up or Pull-Down activation for the selected pins.
                           This parameter can be a value of @ref GPIO_pull */

  uint32_t Speed;      /*!< Specifies the speed for the selected pins.
                           This parameter can be a value of @ref GPIO_speed */

  uint32_t Alternate;  /*!< Peripheral to be connected to the selected pins 
                            This parameter can be a value of @ref GPIOx_Alternate_function_selection */
}GPIO_InitTypeDef;


/* Exported constants --------------------------------------------------------*/


/*
* @brief  GPIO_PIN
*/
#define GPIO_PIN_0                 (BIT0)     /*!< Pin 0 selected    */
#define GPIO_PIN_1                 (BIT1)     /*!< Pin 1 selected    */
#define GPIO_PIN_2                 (BIT2)     /*!< Pin 2 selected    */
#define GPIO_PIN_3                 (BIT3)     /*!< Pin 3 selected    */
#define GPIO_PIN_4                 (BIT4)     /*!< Pin 4 selected    */
#define GPIO_PIN_5                 (BIT5)     /*!< Pin 5 selected    */
#define GPIO_PIN_6                 (BIT6)     /*!< Pin 6 selected    */
#define GPIO_PIN_7                 (BIT7)     /*!< Pin 7 selected    */                                   /*!< Select all pins */
#define GPIO_PIN_ALL               (0xFF) 		/*!< Pin ALL selected   */                                      /*!< Select all pins */

/******************************************************************************/
/*                                                                            */
/*                General Purpose and Alternate Function I/O                  */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for GPIO_MODER register  *******************/
#define GPIO_MODER                             0x00000003
#define GPIO_MODER_MODER_Input                 0x00000000
#define GPIO_MODER_MODER_Output                0x00000001
#define GPIO_MODER_MODER_AF                    0x00000002
#define GPIO_MODER_MODER_Analog                0x00000003

#define  GPIO_MODE_INPUT                       (0x00000000U)   /*!< Input Floating Mode                   */
#define  GPIO_MODE_OUTPUT_PP                   (0x00000001U)   /*!< Output Push Pull Mode                 */
#define  GPIO_MODE_OUTPUT_OD                   (0x00000011U)   /*!< Output Open Drain Mode                */
#define  GPIO_MODE_AF_PP                       (0x00000002U)   /*!< Alternate Function Push Pull Mode     */
#define  GPIO_MODE_AF_OD                       (0x00000012U)   /*!< Alternate Function Open Drain Mode    */
#define  GPIO_MODE_ANALOG                      (0x00000003U)   /*!< Analog Mode  */

/*******************  Bit definition for GPIO_OTYPER register  *******************/
#define GPIO_OTYPER                            0x00000001
#define GPIO_OTYPER_OUT_Pushpull               0x00000000
#define GPIO_OTYPER_OUT_Opendrain              0x00000001

/*!<******************  Bit definition for GPIO_OSPEEDR register  *******************/
#define GPIO_OSPEEDR                           0x00000003
#define GPIO_OSPEEDR_Low                       0x00000000
#define GPIO_OSPEEDR_Medium                    0x00000001
#define GPIO_OSPEEDR_High                   	 0x00000002
#define GPIO_OSPEEDR_VeryHigh                  0x00000003

/*!<******************  Bit definition for GPIO_PUPDR register  *******************/
#define GPIO_PUPDR                             0x00000003
#define GPIO_PUPDR_Floating 			             0x00000000
#define GPIO_PUPDR_Pullup             			   0x00000001
#define GPIO_PUPDR_Pulldown          			     0x00000002
#define GPIO_PUPDR_reserved           			   0x00000003

/*!<******************  Bit definition for GPIO_IDR register  *******************/
#define GPIO_IDR                               0x000000FF
#define GPIO_IDR_IDR0                          0x00000001
#define GPIO_IDR_IDR1                          0x00000002
#define GPIO_IDR_IDR2                          0x00000004
#define GPIO_IDR_IDR3                          0x00000008
#define GPIO_IDR_IDR4                          0x00000010
#define GPIO_IDR_IDR5                          0x00000020
#define GPIO_IDR_IDR6                          0x00000040
#define GPIO_IDR_IDR7                          0x00000080

/*!<******************  Bit definition for GPIO_ODR register  *******************/
#define GPIO_ODR                               0x000000FF
#define GPIO_ODR_ODR0                          0x00000001
#define GPIO_ODR_ODR1                          0x00000002
#define GPIO_ODR_ODR2                          0x00000004
#define GPIO_ODR_ODR3                          0x00000008
#define GPIO_ODR_ODR4                          0x00000010
#define GPIO_ODR_ODR5                          0x00000020
#define GPIO_ODR_ODR6                          0x00000040
#define GPIO_ODR_ODR7                          0x00000080

/*!<******************  Bit definition for GPIO_BSRR register  *******************/
#define GPIO_BSRR                              0x00FF00FF

#define GPIO_BSRR_BR0                          0x00010000
#define GPIO_BSRR_BR1                          0x00020000
#define GPIO_BSRR_BR2                          0x00040000
#define GPIO_BSRR_BR3                          0x00080000
#define GPIO_BSRR_BR4                          0x00100000
#define GPIO_BSRR_BR5                          0x00200000
#define GPIO_BSRR_BR6                          0x00400000
#define GPIO_BSRR_BR7                          0x00800000

#define GPIO_BSRR_BS0                          0x00000001
#define GPIO_BSRR_BS1                          0x00000002
#define GPIO_BSRR_BS2                          0x00000004
#define GPIO_BSRR_BS3                          0x00000008
#define GPIO_BSRR_BS4                          0x00000010
#define GPIO_BSRR_BS5                          0x00000020
#define GPIO_BSRR_BS6                          0x00000040
#define GPIO_BSRR_BS7                          0x00000080

/*!<******************  Bit definition for GPIO_LCKR register  *******************/
#define GPIO_LCKR                              0x000100FF
#define GPIO_LCKR_LCKK                         0x00010000
#define GPIO_LCKR_LCK0                         0x00000001
#define GPIO_LCKR_LCK1                         0x00000002
#define GPIO_LCKR_LCK2                         0x00000004
#define GPIO_LCKR_LCK3                         0x00000008
#define GPIO_LCKR_LCK4                         0x00000010
#define GPIO_LCKR_LCK5                         0x00000020
#define GPIO_LCKR_LCK6                         0x00000040
#define GPIO_LCKR_LCK7                         0x00000080

/*!<******************  Bit definition for GPIO_AFRL register  *******************/
#define GPIO_AFRL                              0x0000000F
#define GPIO_AF0                        			 0x00000000
#define GPIO_AF1                       				 0x00000001
#define GPIO_AF2                        			 0x00000002
#define GPIO_AF3                          		 0x00000003
#define GPIO_AF4                        			 0x00000004
#define GPIO_AF5                         			 0x00000005
#define GPIO_AF6                      				 0x00000006
#define GPIO_AF7                       				 0x00000007

/*!<******************  Bit definition for AFIO register  *******************/
/** @defgroup GPIO_EC_EXTI_PORT GPIO EXTI PORT
  * @{
  */
#define GPIO_AF_EXTI_PORTA          					 0U   /*!< EXTI PORT A */
#define GPIO_AF_EXTI_PORTB           					 1U   /*!< EXTI PORT B */
#define GPIO_AF_EXTI_PORTC          				   2U   /*!< EXTI PORT C */
#define GPIO_AF_EXTI_PORTD           				   3U   /*!< EXTI PORT D */

/** @defgroup GPIO_EC_EXTI_LINE GPIO EXTI LINE
  * @{
  */
#define GPIO_AF_EXTI_LINE0        				    (0x000FU << 16U | 0U)  /*!< EXTI_POSITION_0  | EXTICR[0] */
#define GPIO_AF_EXTI_LINE1         				    (0x00F0U << 16U | 0U)  /*!< EXTI_POSITION_4  | EXTICR[0] */
#define GPIO_AF_EXTI_LINE2          				  (0x0F00U << 16U | 0U)  /*!< EXTI_POSITION_8  | EXTICR[0] */
#define GPIO_AF_EXTI_LINE3          				  (0xF000U << 16U | 0U)  /*!< EXTI_POSITION_12 | EXTICR[0] */
#define GPIO_AF_EXTI_LINE4          				  (0x000FU << 16U | 1U)  /*!< EXTI_POSITION_0  | EXTICR[1] */
#define GPIO_AF_EXTI_LINE5           				  (0x00F0U << 16U | 1U)  /*!< EXTI_POSITION_4  | EXTICR[1] */
#define GPIO_AF_EXTI_LINE6           				  (0x0F00U << 16U | 1U)  /*!< EXTI_POSITION_8  | EXTICR[1] */
#define GPIO_AF_EXTI_LINE7          				  (0xF000U << 16U | 1U)  /*!< EXTI_POSITION_12 | EXTICR[1] */

/**
  * @brief  Configure gpio mode for a dedicated pin on dedicated port.
  * @note   I/O mode can be Input,Output,AF,Analog mode
  * @note   Warning: only one pin can be passed as parameter.
  * @rmtoll MODER        MODEy         GPIO_Set_PinMode
  * @param  GPIOx GPIO Port
	*         @arg @ref  GPIOA
	*         @arg @ref  GPIOB
	*         @arg @ref  GPIOC
	*         @arg @ref  GPIOD
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref  GPIO_PIN_0
  *         @arg @ref  GPIO_PIN_1
  *         @arg @ref  GPIO_PIN_2
  *         @arg @ref  GPIO_PIN_3
  *         @arg @ref  GPIO_PIN_4
  *         @arg @ref  GPIO_PIN_5
  *         @arg @ref  GPIO_PIN_6
  *         @arg @ref  GPIO_PIN_7
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref GPIO_MODER_MODER_Input
  *         @arg @ref GPIO_MODER_MODER_Output
  *         @arg @ref GPIO_MODER_MODER_AF
  *         @arg @ref GPIO_MODER_MODER_Analog

  * @retval None
  */
__STATIC_INLINE void GPIO_Set_PinMode(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Mode)
{
   MODIFY_REG(GPIOx->MODER,GPIO_MODER<<(POSITION_VAL(Pin)* 2U),Mode<<(POSITION_VAL(Pin)* 2U));
}

/**
  * @brief  Return gpio mode for a dedicated pin on dedicated port.
  * @note   I/O mode can be Input mode, General purpose output, Alternate function mode or Analog.
  * @note   Warning: only one pin can be passed as parameter.
  * @rmtoll MODER        MODEy         GPIO_Get_PinMode
  * @param  GPIOx GPIO Port
  *         @arg @ref  GPIOA
	*         @arg @ref  GPIOB
	*         @arg @ref  GPIOC
	*         @arg @ref  GPIOD
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref  GPIO_PIN_0
  *         @arg @ref  GPIO_PIN_1
  *         @arg @ref  GPIO_PIN_2
  *         @arg @ref  GPIO_PIN_3
  *         @arg @ref  GPIO_PIN_4
  *         @arg @ref  GPIO_PIN_5
  *         @arg @ref  GPIO_PIN_6
  *         @arg @ref  GPIO_PIN_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref GPIO_MODER_MODER_Input
  *         @arg @ref GPIO_MODER_MODER_Output
  *         @arg @ref GPIO_MODER_MODER_AF
  *         @arg @ref GPIO_MODER_MODER_Analog
  */
__STATIC_INLINE uint32_t GPIO_Get_PinMode(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(GPIOx->MODER,(GPIO_MODER<<(POSITION_VAL(Pin)*2U)))>>(POSITION_VAL(Pin)*2U));
}

/**
  * @brief  Configure gpio output type for several pins on dedicated port.
  * @note   Output type as to be set when gpio pin is in output or
  *         alternate modes. Possible type are Push-pull or Open-drain.
  * @rmtoll OTYPER       OTy           GPIO_Set_PinOutputType
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref  GPIO_PIN_0
  *         @arg @ref  GPIO_PIN_1
  *         @arg @ref  GPIO_PIN_2
  *         @arg @ref  GPIO_PIN_3
  *         @arg @ref  GPIO_PIN_4
  *         @arg @ref  GPIO_PIN_5
  *         @arg @ref  GPIO_PIN_6
  *         @arg @ref  GPIO_PIN_7
	*         @arg @ref  GPIO_PIN_ALL
  * @param  OutputType This parameter can be one of the following values:
  *         @arg @ref GPIO_OTYPER_OUT_Pushpull
  *         @arg @ref GPIO_OTYPER_OUT_Opendrain
  * @retval None
  */
__STATIC_INLINE void GPIO_Set_PinOutputType(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t OutputType)
{
  MODIFY_REG(GPIOx->OTYPER, Pin, (Pin * OutputType));
}

/**
  * @brief  Return gpio output type for several pins on dedicated port.
  * @note   Output type as to be set when gpio pin is in output or
  *         alternate modes. Possible type are Push-pull or Open-drain.
  * @note   Warning: only one pin can be passed as parameter.
  * @rmtoll OTYPER       OTy           GPIO_Get_PinOutputType
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref  GPIO_PIN_0
  *         @arg @ref  GPIO_PIN_1
  *         @arg @ref  GPIO_PIN_2
  *         @arg @ref  GPIO_PIN_3
  *         @arg @ref  GPIO_PIN_4
  *         @arg @ref  GPIO_PIN_5
  *         @arg @ref  GPIO_PIN_6
  *         @arg @ref  GPIO_PIN_7
	*         @arg @ref  GPIO_PIN_ALL
  * @retval Returned value can be one of the following values:
  *         @arg @ref GPIO_OTYPER_OUT_Pushpull
  *         @arg @ref GPIO_OTYPER_OUT_Opendrain
  */
__STATIC_INLINE uint32_t GPIO_Get_PinOutputType(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(GPIOx->OTYPER, Pin) >> POSITION_VAL(Pin));
}
/**
  * @brief  Configure gpio speed for a dedicated pin on dedicated port.
  * @note   I/O speed can be Low, Medium,High speed.
  * @note   Warning: only one pin can be passed as parameter.
  * @note   Refer to datasheet for frequency specifications and the power
  *         supply and load conditions for each speed.
  * @rmtoll OSPEEDR      OSPEEDy       GPIO_Set_PinOutSpeed
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref  GPIO_PIN_0
  *         @arg @ref  GPIO_PIN_1
  *         @arg @ref  GPIO_PIN_2
  *         @arg @ref  GPIO_PIN_3
  *         @arg @ref  GPIO_PIN_4
  *         @arg @ref  GPIO_PIN_5
  *         @arg @ref  GPIO_PIN_6
  *         @arg @ref  GPIO_PIN_7
  * @param  Speed This parameter can be one of the following values:
  *         @arg @ref GPIO_OSPEEDR_Low
  *         @arg @ref GPIO_OSPEEDR_Medium
  *         @arg @ref GPIO_OSPEEDR_High  
  *         @arg @ref GPIO_OSPEEDR_VeryHigh	
  * @retval None
  */
__STATIC_INLINE void GPIO_Set_PinOutSpeed(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t  Speed)
{
  MODIFY_REG(GPIOx->OSPEEDR, (GPIO_OSPEEDR << (POSITION_VAL(Pin) * 2U)),(Speed << (POSITION_VAL(Pin) * 2U)));
}

/**
  * @brief  Return gpio speed for a dedicated pin on dedicated port.
  * @note   I/O speed can be Low, Medium, Fast or High speed.
  * @note   Warning: only one pin can be passed as parameter.
  * @note   Refer to datasheet for frequency specifications and the power
  *         supply and load conditions for each speed.
  * @rmtoll OSPEEDR      OSPEEDy       GPIO_Get_PinOutSpeed
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref  GPIO_PIN_0
  *         @arg @ref  GPIO_PIN_1
  *         @arg @ref  GPIO_PIN_2
  *         @arg @ref  GPIO_PIN_3
  *         @arg @ref  GPIO_PIN_4
  *         @arg @ref  GPIO_PIN_5
  *         @arg @ref  GPIO_PIN_6
  *         @arg @ref  GPIO_PIN_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref GPIO_OSPEEDR_Low
  *         @arg @ref GPIO_OSPEEDR_Medium
  *         @arg @ref GPIO_OSPEEDR_High
  *         @arg @ref GPIO_OSPEEDR_VeryHigh		
  */
__STATIC_INLINE uint32_t GPIO_Get_PinOutSpeed(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(GPIOx->OSPEEDR,(GPIO_OSPEEDR<<(POSITION_VAL(Pin)*2U)))>>(POSITION_VAL(Pin)*2U));
}

/**
  * @brief  Configure gpio pull-up or pull-down for a dedicated pin on a dedicated port.
  * @note   Warning: only one pin can be passed as parameter.
  * @rmtoll PUPDR        PUPDy         GPIO_Set_PinPull
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref  GPIO_PIN_0
  *         @arg @ref  GPIO_PIN_1
  *         @arg @ref  GPIO_PIN_2
  *         @arg @ref  GPIO_PIN_3
  *         @arg @ref  GPIO_PIN_4
  *         @arg @ref  GPIO_PIN_5
  *         @arg @ref  GPIO_PIN_6
  *         @arg @ref  GPIO_PIN_7
  * @param  Pull This parameter can be one of the following values:
  *         @arg @ref GPIO_PUPDR_Floating
  *         @arg @ref GPIO_PUPDR_Pullup
  *         @arg @ref GPIO_PUPDR_Pulldown	
  * @retval None
  */
__STATIC_INLINE void GPIO_Set_PinPull(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Pull)
{
  MODIFY_REG(GPIOx->PUPDR, (GPIO_PUPDR << (POSITION_VAL(Pin) * 2U)), (Pull << (POSITION_VAL(Pin) * 2U)));
}

/**
  * @brief  Return gpio pull-up or pull-down for a dedicated pin on a dedicated port
  * @note   Warning: only one pin can be passed as parameter.
  * @rmtoll PUPDR        PUPDy         GPIO_Get_PinPull
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref  GPIO_PIN_0
  *         @arg @ref  GPIO_PIN_1
  *         @arg @ref  GPIO_PIN_2
  *         @arg @ref  GPIO_PIN_3
  *         @arg @ref  GPIO_PIN_4
  *         @arg @ref  GPIO_PIN_5
  *         @arg @ref  GPIO_PIN_6
  *         @arg @ref  GPIO_PIN_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref GPIO_PUPDR_Floating
  *         @arg @ref GPIO_PUPDR_Pullup
  *         @arg @ref GPIO_PUPDR_Pulldown
  */
__STATIC_INLINE uint32_t GPIO_Get_PinPull(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return (uint32_t)(READ_BIT(GPIOx->PUPDR,(GPIO_PUPDR<<(POSITION_VAL(Pin)*2U)))>>(POSITION_VAL(Pin)*2U));
}

/**
  * @brief  Return full input data register value for a dedicated port.
  * @rmtoll IDR          IDy           GPIO_Read_InputPort
  * @param  GPIOx GPIO Port
  * @retval Input data register value of port
  */
__STATIC_INLINE uint32_t GPIO_Read_InputPort(GPIO_TypeDef *GPIOx)
{
  return (uint32_t)(READ_REG(GPIOx->IDR));
}

/**
  * @brief  Return if input data level for several pins of dedicated port is high or low.
  * @rmtoll IDR          IDy           GPIO_Read_PINIDR
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref  GPIO_PIN_0
  *         @arg @ref  GPIO_PIN_1
  *         @arg @ref  GPIO_PIN_2
  *         @arg @ref  GPIO_PIN_3
  *         @arg @ref  GPIO_PIN_4
  *         @arg @ref  GPIO_PIN_5
  *         @arg @ref  GPIO_PIN_6
  *         @arg @ref  GPIO_PIN_7
	*         @arg @ref  GPIO_PIN_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t GPIO_Read_PinIDR(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return ((READ_BIT(GPIOx->IDR, Pin) == (Pin)) ? 1UL : 0UL);
}

/**
  * @brief  Write output data register for the port.
  * @rmtoll ODR          ODy           GPIO_Write_ODR
  * @param  GPIOx GPIO Port
  * @param  PortValue Level value for each pin of the port
  *         @arg @ref  GPIO_PIN_0
  *         @arg @ref  GPIO_PIN_1
  *         @arg @ref  GPIO_PIN_2
  *         @arg @ref  GPIO_PIN_3
  *         @arg @ref  GPIO_PIN_4
  *         @arg @ref  GPIO_PIN_5
  *         @arg @ref  GPIO_PIN_6
  *         @arg @ref  GPIO_PIN_7
	*         @arg @ref  GPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void GPIO_Write_ODR(GPIO_TypeDef *GPIOx, uint32_t Port)
{
  WRITE_REG(GPIOx->ODR, Port);
}

/**
  * @brief  Return full output data register value for a dedicated port.
  * @rmtoll ODR          ODy           GPIO_Read_ODR
  * @param  GPIOx GPIO Port
  * @retval Output data register value of port
  */
__STATIC_INLINE uint32_t GPIO_Read_ODR(GPIO_TypeDef *GPIOx)
{
  return (uint32_t)(READ_REG(GPIOx->ODR));
}

/**
  * @brief  Return if input data level for several pins of dedicated port is high or low.
  * @rmtoll ODR          ODy           GPIO_Read_PinODR
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref  GPIO_PIN_0
  *         @arg @ref  GPIO_PIN_1
  *         @arg @ref  GPIO_PIN_2
  *         @arg @ref  GPIO_PIN_3
  *         @arg @ref  GPIO_PIN_4
  *         @arg @ref  GPIO_PIN_5
  *         @arg @ref  GPIO_PIN_6
  *         @arg @ref  GPIO_PIN_7
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t GPIO_Read_PinODR(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return ((READ_BIT(GPIOx->ODR, Pin) == (Pin)) ? 1UL : 0UL);
}

/**
  * @brief  Set several pins to high level on dedicated gpio port.
  * @rmtoll BSRR         BSy           GPIO_Set_OutputPin
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref  GPIO_PIN_0
  *         @arg @ref  GPIO_PIN_1
  *         @arg @ref  GPIO_PIN_2
  *         @arg @ref  GPIO_PIN_3
  *         @arg @ref  GPIO_PIN_4
  *         @arg @ref  GPIO_PIN_5
  *         @arg @ref  GPIO_PIN_6
  *         @arg @ref  GPIO_PIN_7
	*         @arg @ref  GPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void GPIO_Set_OutputPin(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
#if !defined( BSRR_u8 ) && !defined( BSRR_u16 ) && !defined( BSRR_u32 )	
  WRITE_REG(GPIOx->BSRR, Pin);
#endif
}
/**
  * @brief  Set several pins to low level on dedicated gpio port.
  * @rmtoll BRR          BRy           GPIO_Reset_OutputPin
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref  GPIO_PIN_0
  *         @arg @ref  GPIO_PIN_1
  *         @arg @ref  GPIO_PIN_2
  *         @arg @ref  GPIO_PIN_3
  *         @arg @ref  GPIO_PIN_4
  *         @arg @ref  GPIO_PIN_5
  *         @arg @ref  GPIO_PIN_6
  *         @arg @ref  GPIO_PIN_7
	*         @arg @ref  GPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void GPIO_Reset_OutputPin(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
#if !defined( BSRR_u8 ) && !defined( BSRR_u16 ) && !defined( BSRR_u32 )		
  WRITE_REG(GPIOx->BSRR, Pin<<16U);
#endif
}

/**
  * @brief  Toggle data value for several pin of dedicated port.
  * @rmtoll ODR          ODy           GPIO_Toggle_Pin
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref  GPIO_PIN_0
  *         @arg @ref  GPIO_PIN_1
  *         @arg @ref  GPIO_PIN_2
  *         @arg @ref  GPIO_PIN_3
  *         @arg @ref  GPIO_PIN_4
  *         @arg @ref  GPIO_PIN_5
  *         @arg @ref  GPIO_PIN_6
  *         @arg @ref  GPIO_PIN_7
	*         @arg @ref  GPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void GPIO_Toggle_Pin(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  WRITE_REG(GPIOx->ODR, READ_REG(GPIOx->ODR) ^ Pin);
}

/**
  * @brief  Lock configuration of several pins for a dedicated port.
  * @note   When the lock sequence has been applied on a port bit, the
  *         value of this port bit can no longer be modified until the
  *         next reset.
  * @note   Each lock bit freezes a specific configuration register
  *         (control and alternate function registers).
  * @rmtoll LCKR         LCKK          GPIO_Lock_Pin
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref  GPIO_PIN_0
  *         @arg @ref  GPIO_PIN_1
  *         @arg @ref  GPIO_PIN_2
  *         @arg @ref  GPIO_PIN_3
  *         @arg @ref  GPIO_PIN_4
  *         @arg @ref  GPIO_PIN_5
  *         @arg @ref  GPIO_PIN_6
  *         @arg @ref  GPIO_PIN_7
	*         @arg @ref  GPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void GPIO_Lock_Pin(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  __IO uint32_t temp;
  WRITE_REG(GPIOx->LCKR, GPIO_LCKR_LCKK | Pin);
  WRITE_REG(GPIOx->LCKR, Pin);
  WRITE_REG(GPIOx->LCKR, GPIO_LCKR_LCKK | Pin);
  /* Read LCKR register. This read is mandatory to complete key lock sequence */
  temp = READ_REG(GPIOx->LCKR);
  (void) temp;
}

/**
  * @brief  Lock configuration of several pins for a dedicated port.
  * @note   When the lock sequence has been applied on a port bit, the
  *         value of this port bit can no longer be modified until the
  *         next reset.
  * @note   Each lock bit freezes a specific configuration register
  *         (control and alternate function registers).
  * @rmtoll LCKR         LCKK          GPIO_Lock_Pin
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref  GPIO_PIN_0
  *         @arg @ref  GPIO_PIN_1
  *         @arg @ref  GPIO_PIN_2
  *         @arg @ref  GPIO_PIN_3
  *         @arg @ref  GPIO_PIN_4
  *         @arg @ref  GPIO_PIN_5
  *         @arg @ref  GPIO_PIN_6
  *         @arg @ref  GPIO_PIN_7
	*         @arg @ref  GPIO_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void GPIO_ErrorLock_Pin(GPIO_TypeDef *GPIOx, uint32_t Pin,char error_rankx)
{
  __IO uint32_t temp;
	if(error_rankx==1) //ERR 1
	{
		WRITE_REG(GPIOx->LCKR, GPIO_LCKR_LCKK | Pin);//write LCKK=1,LCKy=1
		WRITE_REG(GPIOx->LCKR, (uint32_t)0x00000000);//write LCKK=0,LCKy=0
		WRITE_REG(GPIOx->LCKR, GPIO_LCKR_LCKK | Pin);//write LCKK=1,LCKy=1
		temp = READ_REG(GPIOx->LCKR);                //read
		(void) temp;
	}
	else if(error_rankx==2) //ERR 2
	{
		WRITE_REG(GPIOx->LCKR, GPIO_LCKR_LCKK | Pin);//write LCKK=1,LCKy=1
		temp = READ_REG(GPIOx->LCKR);                //read
		WRITE_REG(GPIOx->LCKR, Pin);                 //write LCKK=0,LCKy=1
		temp = READ_REG(GPIOx->LCKR);                //read
		WRITE_REG(GPIOx->LCKR, GPIO_LCKR_LCKK | Pin);//write LCKK=1,LCKy=1
		temp = READ_REG(GPIOx->LCKR);                //read
		(void) temp;
	}
}

/**
  * @brief  Return 1 if all pins passed as parameter, of a dedicated port, are locked. else Return 0.
  * @rmtoll LCKR         LCKy          GPIO_Get_PinLocked
  * @param  GPIOx GPIO Port
  * @param  PinMask This parameter can be a combination of the following values:
  *         @arg @ref  GPIO_PIN_0
  *         @arg @ref  GPIO_PIN_1
  *         @arg @ref  GPIO_PIN_2
  *         @arg @ref  GPIO_PIN_3
  *         @arg @ref  GPIO_PIN_4
  *         @arg @ref  GPIO_PIN_5
  *         @arg @ref  GPIO_PIN_6
  *         @arg @ref  GPIO_PIN_7
	*         @arg @ref  GPIO_PIN_ALL
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t GPIO_Get_PinLocked(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
  return ((READ_BIT(GPIOx->LCKR, Pin) == (Pin)) ? 1UL : 0UL);
}

/**
  * @brief  Return 1 if one of the pin of a dedicated port is locked. else return 0.
  * @rmtoll LCKR         LCKK          GPIO_Get_AnyPinLocked
  * @param  GPIOx GPIO Port
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t GPIO_Get_AnyPinLocked(GPIO_TypeDef *GPIOx)
{
  return ((READ_BIT(GPIOx->LCKR, GPIO_LCKR_LCKK) == (GPIO_LCKR_LCKK)) ? 1UL : 0UL);
}

/**
  * @brief  Configure gpio alternate function of a dedicated pin from 0 to 15 for a dedicated port.
  * @note   Possible values are from GPIO_AF0 to GPIO_AF7 depending on target.
  * @note   Warning: only one pin can be passed as parameter.
  * @rmtoll AFRL     AFRH             GPIO_Set_AF
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref  GPIO_PIN_0
  *         @arg @ref  GPIO_PIN_1
  *         @arg @ref  GPIO_PIN_2
  *         @arg @ref  GPIO_PIN_3
  *         @arg @ref  GPIO_PIN_4
  *         @arg @ref  GPIO_PIN_5
  *         @arg @ref  GPIO_PIN_6
  *         @arg @ref  GPIO_PIN_7
  * @param  Alternate This parameter can be one of the following values:
  *         @arg @ref GPIO_AF0
  *         @arg @ref GPIO_AF1
  *         @arg @ref GPIO_AF2
  *         @arg @ref GPIO_AF3
  *         @arg @ref GPIO_AF4
  *         @arg @ref GPIO_AF5
  *         @arg @ref GPIO_AF6
  *         @arg @ref GPIO_AF7
  * @retval None
  */
__STATIC_INLINE void GPIO_Set_AF(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Alternate)
{
		MODIFY_REG(GPIOx->AFRL, (GPIO_AFRL << (POSITION_VAL(Pin) * 4U)),(Alternate << (POSITION_VAL(Pin) * 4U)));
}
/**
  * @brief  Return gpio alternate function of a dedicated pin from 0 to 15 for a dedicated port.
  * @rmtoll AFRL  AFRH                 GPIO_Get_AF
  * @param  GPIOx GPIO Port
  * @param  Pin This parameter can be one of the following values:
  *         @arg @ref  GPIO_PIN_0
  *         @arg @ref  GPIO_PIN_1
  *         @arg @ref  GPIO_PIN_2
  *         @arg @ref  GPIO_PIN_3
  *         @arg @ref  GPIO_PIN_4
  *         @arg @ref  GPIO_PIN_5
  *         @arg @ref  GPIO_PIN_6
  *         @arg @ref  GPIO_PIN_7
  * @retval Returned value can be one of the following values:
  *         @arg @ref GPIO_AF0
  *         @arg @ref GPIO_AF1
  *         @arg @ref GPIO_AF2
  *         @arg @ref GPIO_AF3
  *         @arg @ref GPIO_AF4
  *         @arg @ref GPIO_AF5
  *         @arg @ref GPIO_AF6
  *         @arg @ref GPIO_AF7
  */
__STATIC_INLINE uint32_t GPIO_Get_AF(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
	uint32_t temp = 0;
	temp = (uint32_t)(READ_BIT(GPIOx->AFRL,(GPIO_AFRL << (POSITION_VAL(Pin) * 4U))) >> (POSITION_VAL(Pin) * 4U));
  return temp;
}


/**
  * @brief  Configure source input for the EXTI external interrupt.
  * @rmtoll AFIO_EXTICR1      EXTIx         GPIO_Set_EXTISource\n
  *         AFIO_EXTICR2      EXTIx         GPIO_Set_EXTISource\n
  * @param  Port This parameter can be one of the following values:
  *         @arg @ref GPIO_AF_EXTI_PORTA
  *         @arg @ref GPIO_AF_EXTI_PORTB
  *         @arg @ref GPIO_AF_EXTI_PORTC
  *         @arg @ref GPIO_AF_EXTI_PORTD
  * @param  Line This parameter can be one of the following values:
  *         @arg @ref GPIO_AF_EXTI_LINE0
  *         @arg @ref GPIO_AF_EXTI_LINE1
  *         @arg @ref GPIO_AF_EXTI_LINE2
  *         @arg @ref GPIO_AF_EXTI_LINE3
  *         @arg @ref GPIO_AF_EXTI_LINE4
  *         @arg @ref GPIO_AF_EXTI_LINE5
  *         @arg @ref GPIO_AF_EXTI_LINE6
  *         @arg @ref GPIO_AF_EXTI_LINE7
  * @retval None
  */
__STATIC_INLINE void GPIO_Set_EXTISource(uint32_t Port, uint32_t Line)
{
  MODIFY_REG(SYSCFG->EXTICR[Line & 0xFF], (Line >> 16), Port << POSITION_VAL((Line >> 16)));
}

/**
  * @brief  Get the configured defined for specific EXTI Line
  * @rmtoll AFIO_EXTICR1      EXTIx         GPIO_Get_EXTISource\n
  *         AFIO_EXTICR2      EXTIx         GPIO_Get_EXTISource\n
  * @param  Line This parameter can be one of the following values:
  *         @arg @ref GPIO_AF_EXTI_LINE0
  *         @arg @ref GPIO_AF_EXTI_LINE1
  *         @arg @ref GPIO_AF_EXTI_LINE2
  *         @arg @ref GPIO_AF_EXTI_LINE3
  *         @arg @ref GPIO_AF_EXTI_LINE4
  *         @arg @ref GPIO_AF_EXTI_LINE5
  *         @arg @ref GPIO_AF_EXTI_LINE6
  *         @arg @ref GPIO_AF_EXTI_LINE7
  * @retval Returned value can be one of the following values:
  *         @arg @ref GPIO_AF_EXTI_PORTA
  *         @arg @ref GPIO_AF_EXTI_PORTB
  *         @arg @ref GPIO_AF_EXTI_PORTC
  *         @arg @ref GPIO_AF_EXTI_PORTD
  */
__STATIC_INLINE uint32_t GPIO_Get_EXTISource(uint32_t Line)
{
  return (uint32_t)(READ_BIT(SYSCFG->EXTICR[Line & 0xFF], (Line >> 16)) >> POSITION_VAL(Line >> 16));
}

void GPIO_DeInit(GPIO_TypeDef *GPIOx);
void GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);

#ifdef __cplusplus
}
#endif

#endif /* __rx32h6xx_GPIO_H__ */

