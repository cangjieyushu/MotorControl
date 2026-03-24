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
* File         : rx32h6xx_rcc.h
* By           : RX_SD_Team
* Version      : V1.0.0
* Description  : Only rx32h6xx
*********************************************************************************************************
*/
#ifndef _rx32h6xx_RCC_H
#define _rx32h6xx_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rx32h6xx.h"

/* constant -------------------------------------------------------------*/

/*******************  Bit definition for RCC_CR register  *******************/
#define RCC_CR_HSION                  BIT0
#define RCC_CR_HSIRDY                 BIT1
#define RCC_CR_HSICAL                 (0xFF<<8)
#define RCC_CR_PLLON                  BIT24
#define RCC_CR_PLLRDY                 BIT25

/*******************  Bit definition for RCC_CFGR register  *******************/
#define RCC_CFGR_SW                    0x03
#define RCC_CFGR_SW_HSI                0x00
#define RCC_CFGR_SW_PLL                0x02
#define RCC_CFGR_SW_LSI                0x03

#define RCC_CFGR_SWS                   BIT2|BIT3
#define RCC_CFGR_SWS_HSI               (0x00<<2)
#define RCC_CFGR_SWS_PLL               (0x02<<2)
#define RCC_CFGR_SWS_LSI               (0x03<<2)

#define RCC_CFGR_HPRE                  (0x0F<<4)
#define RCC_CFGR_HPRE_DIV1             (0x00<<4)
#define RCC_CFGR_HPRE_DIV2             (0x08<<4)
#define RCC_CFGR_HPRE_DIV4             (0x09<<4)
#define RCC_CFGR_HPRE_DIV8             (0x0A<<4)
#define RCC_CFGR_HPRE_DIV16            (0x0B<<4)
#define RCC_CFGR_HPRE_DIV64            (0x0C<<4)
#define RCC_CFGR_HPRE_DIV128           (0x0D<<4)
#define RCC_CFGR_HPRE_DIV256           (0x0E<<4)
#define RCC_CFGR_HPRE_DIV512           (0x0F<<4)

#define RCC_CFGR_PPRE1                 (0x07<<8)
#define RCC_CFGR_PPRE1_DIV1            (0x00<<8)
#define RCC_CFGR_PPRE1_DIV2            (0x04<<8)
#define RCC_CFGR_PPRE1_DIV4            (0x05<<8)
#define RCC_CFGR_PPRE1_DIV8            (0x06<<8)
#define RCC_CFGR_PPRE1_DIV16           (0x07<<8)

#define RCC_CFGR_PPRE2                 (0x07<<11)
#define RCC_CFGR_PPRE2_DIV1            (0x00<<11)
#define RCC_CFGR_PPRE2_DIV2            (0x04<<11)
#define RCC_CFGR_PPRE2_DIV4            (0x05<<11)
#define RCC_CFGR_PPRE2_DIV8            (0x06<<11)
#define RCC_CFGR_PPRE2_DIV16           (0x07<<11)

#define RCC_CFGR_ADCPRE                BIT14|BIT15|BIT31
#define RCC_CFGR_ADCPRE_DIV2           (0x01<<14)
#define RCC_CFGR_ADCPRE_DIV3           (0x02<<14)
#define RCC_CFGR_ADCPRE_DIV4           (0x03<<14)
#define RCC_CFGR_ADCPRE_DIV5           ((uint32_t)0x20000<<14)
#define RCC_CFGR_ADCPRE_DIV6           ((uint32_t)0x20001<<14)
#define RCC_CFGR_ADCPRE_DIV7           ((uint32_t)0x20002<<14)
#define RCC_CFGR_ADCPRE_DIV8           ((uint32_t)0x20003<<14)

#define RCC_CFGR_PLLMULL          (0x07<<18)
#define RCC_CFGR_PLLMUL_10x             (0x00<<18)
#define RCC_CFGR_PLLMUL_12x             (0x01<<18)
#define RCC_CFGR_PLLMUL_14x             (0x02<<18)
#define RCC_CFGR_PLLMUL_15x             (0x03<<18)
#define RCC_CFGR_PLLMUL_16x             (0x04<<18)
#define RCC_CFGR_PLLMUL_17x             (0x05<<18)
#define RCC_CFGR_PLLMUL_18x             (0x06<<18)
#define RCC_CFGR_PLLMUL_19x             (0x07<<18)

#define RCC_CFGR_MCO_SEL              (0x07<<24)
#define RCC_CFGR_MCO_LSI               (0x06<<24)
#define RCC_CFGR_MCO_FSYS              (0x01<<24)
#define RCC_CFGR_MCO_HSI               (0x03<<24)
#define RCC_CFGR_MCO_PLL               (0x05<<24)

#define RCC_CFGR_MCO_PRE              (0x03<<27)
#define RCC_CFGR_MCO_DIV1             (0x00<<27)
#define RCC_CFGR_MCO_DIV2             (0x01<<27)
#define RCC_CFGR_MCO_DIV4             (0x02<<27)
#define RCC_CFGR_MCO_DIV8             (0x03<<27)

#define RCC_CFGR_ADCCLK_SEL            BIT29
#define RCC_CFGR_ADCCLK_SEL_SYSCLK     0x00
#define RCC_CFGR_ADCCLK_SEL_PLL2       BIT29

/*******************  Bit definition for RCC_CIR register  *******************/
#define RCC_CIR_LSIRDYF                BIT0
#define RCC_CIR_HSIRDYF                BIT2
#define RCC_CIR_PLLRDYF                BIT4
#define RCC_CIR_LSIRDYIE               BIT8
#define RCC_CIR_HSIRDYIE               BIT10
#define RCC_CIR_PLLRDYIE               BIT12
#define RCC_CIR_LSIRDYC                BIT16
#define RCC_CIR_HSIRDYC                BIT18
#define RCC_CIR_PLLRDYC                BIT20

/*******************  Bit definition for RCC_APB2RSTR register  *******************/
#define RCC_APB2RSTR_SYSCFGRST         BIT0
#define RCC_APB2RSTR_SPI1RST           BIT12
#define RCC_APB2RSTR_TIM8RST           BIT13
#define RCC_APB2RSTR_UART1RST         BIT14
#define RCC_APB2RSTR_TIM15RST          BIT16

/*******************  Bit definition for RCC_APB1RSTR register  *******************/
#define RCC_APB1RSTR_TIM2RST           BIT0
#define RCC_APB1RSTR_TIM3RST           BIT1
#define RCC_APB1RSTR_TIM6RST           BIT4
#define RCC_APB1RSTR_TIM7RST           BIT5
#define RCC_APB1RSTR_UART2RST         BIT17
#define RCC_APB1RSTR_I2C1RST           BIT21
#define RCC_APB1RSTR_PWRRST            BIT28

/*******************  Bit definition for RCC_AHBENR register  *******************/
#define RCC_AHBENR_SRAMEN              BIT2
#define RCC_AHBENR_FLITEN              BIT4
#define RCC_AHBENR_CRCEN               BIT6
#define RCC_AHBENR_MEEN                BIT11
#define RCC_AHBENR_IOPAEN            	 BIT16
#define RCC_AHBENR_IOPBEN            	 BIT17
#define RCC_AHBENR_IOPCEN            	 BIT18
#define RCC_AHBENR_IOPDEN              BIT19
#define RCC_AHBENR_ADC1EN              BIT24

/*******************  Bit definition for RCC_APB2ENR register  *******************/
#define RCC_APB2ENR_SYSCFGEN           BIT0
#define RCC_APB2ENR_SPI1EN             BIT12
#define RCC_APB2ENR_TIM8EN             BIT13
#define RCC_APB2ENR_UART1EN           BIT14
#define RCC_APB2ENR_TIM15EN            BIT15

/*******************  Bit definition for RCC_APB1ENR register  *******************/
#define RCC_APB1ENR_TIM2EN             BIT0
#define RCC_APB1ENR_TIM3EN             BIT1
#define RCC_APB1ENR_TIM6EN             BIT4
#define RCC_APB1ENR_TIM7EN             BIT5
#define RCC_APB1ENR_UART2EN           BIT17
#define RCC_APB1ENR_I2C1EN             BIT21
#define RCC_APB1ENR_PWREN              BIT28

/*******************  Bit definition for RCC_BDCR register  *******************/
#define RCC_BDCR_RTCEN                 BIT15
#define RCC_BDCR_BDRST                 BIT16

/*******************  Bit definition for RCC_CSR register  *******************/
#define RCC_CSR_LSION                  BIT0
#define RCC_CSR_LSIRDY                 BIT1
#define RCC_CSR_RMVF                   BIT24
#define RCC_CSR_OBLRSTF                BIT25
#define RCC_CSR_PINRSTF                BIT26
#define RCC_CSR_PORRSTF                BIT27
#define RCC_CSR_SFTRSTF                BIT28
#define RCC_CSR_IWDGRSTF               BIT29
#define RCC_CSR_LPWRRSTF               BIT31

/*******************  Bit definition for RCC_AHBRSTR register  *******************/
#define RCC_AHBRSTR_CRCRST             BIT6
#define RCC_AHBRSTR_MERST              BIT11
#define RCC_AHBRSTR_IOPARST            BIT16
#define RCC_AHBRSTR_IOPBRST            BIT17
#define RCC_AHBRSTR_IOPCRST            BIT18
#define RCC_AHBRSTR_IOPDRST            BIT19
#define RCC_AHBRSTR_ADC1RST            BIT24

/*******************  Bit definition for RCC_PLLDET register  *******************/
#define RCC_PLLDET_DELTA               0x1F
#define RCC_PLLDET_FAIL_M0             BIT5
#define RCC_PLLDET_FAIL_M1             BIT6
#define RCC_PLLDET_TCNT_UPEN           BIT7
#define RCC_PLLDET_FCNT_WIDTH          0x7<<8
#define RCC_PLLDET_TOUT                0XFF<<16
#define RCC_PLLDET_FAIL_M2             BIT31

#define RCC_PLLDET_FCNT_WIDTH_5bit     0x000
#define RCC_PLLDET_FCNT_WIDTH_6bit     0x100
#define RCC_PLLDET_FCNT_WIDTH_7bit     0x200
#define RCC_PLLDET_FCNT_WIDTH_8bit     0x300
#define RCC_PLLDET_FCNT_WIDTH_9bit     0x400
#define RCC_PLLDET_FCNT_WIDTH_10bit    0x500
#define RCC_PLLDET_FCNT_WIDTH_11bit    0x600

/* constant -------------------------------------------------------------*/
typedef struct
{
  uint32_t SYSCLKSource;          /*!< The clock source (SYSCLKS) used as system clock.*/
  
  uint32_t PLLSource;             /*!< PLLSource: PLL entry clock source.*/
	
	uint32_t PLLMUL;                /*!< PLLMUL: PLL frequency multiplication.*/
  
  uint32_t LATENCY;

  uint32_t AHBCLKDivider;         /*!< The AHB clock (HCLK) divider. This clock is derived from the system clock (SYSCLK).*/

  uint32_t APB1CLKDivider;        /*!< The APB1 clock (PCLK1) divider. This clock is derived from the AHB clock (HCLK).*/

  uint32_t APB2CLKDivider;        /*!< The APB2 clock (PCLK2) divider. This clock is derived from the AHB clock (HCLK).*/
	
	uint32_t ADCSource;
   
  uint32_t ADCCLKDivider;         /*!< The ADC clock (ADCCLK) divider. This clock is derived from the APB2 clock (PCLK).*/
} RCC_ClkInitTypeDef;
  
typedef struct
{
  uint32_t SYSCLK_Frequency;        /*!< SYSCLK clock frequency */
  uint32_t HCLK_Frequency;          /*!< HCLK clock frequency */
  uint32_t PCLK1_Frequency;         /*!< PCLK1 clock frequency */
  uint32_t PCLK2_Frequency;         /*!< PCLK2 clock frequency */
} RCC_ClocksTypeDef;  

/* types -------------------------------------------------------------*/
/* functions -------------------------------------------------------------*/

/**
  * @function  RCC_Enable_HSI
  * @brief  Enable HSI
  * @retval None
*/
__STATIC_INLINE void RCC_Enable_HSI(void)
{
   SET_BIT(RCC->CR, RCC_CR_HSION);
}

/**
  * @function  RCC_Disable_HSI
  * @brief  Disable HSI
  * @retval None
*/
__STATIC_INLINE void RCC_Disable_HSI(void)
{
   CLEAR_BIT(RCC->CR, RCC_CR_HSION);
}

/**
  * @function  uint32_t RCC_Get_HSIRDY(void)
  * @brief  check if HSI ready
  * @param  None
  * @retval 1:HSI is ready, 0: HSI not ready
*/
__STATIC_INLINE uint32_t RCC_Get_HSIRDY(void)
{
  return (READ_BIT(RCC->CR, RCC_CR_HSIRDY) == (RCC_CR_HSIRDY));
}

/**
  * @function  RCC_Enable_LSI
  * @brief  Enable LSI
  * @retval None
*/
__STATIC_INLINE void RCC_Enable_LSI(void)
{
   SET_BIT(RCC->CSR, RCC_CSR_LSION);
}

/**
  * @function  RCC_Disable_LSI
  * @brief  Disable LSI
  * @retval None
*/
__STATIC_INLINE void RCC_Disable_LSI(void)
{
   CLEAR_BIT(RCC->CSR, RCC_CSR_LSION);
}

/**
  * @function  RCC_Get_LSIRDY
  * @brief  check if LSI ready
  * @param  None
  * @retval 1:LSI is ready, 0: LSI not ready
*/
__STATIC_INLINE uint32_t RCC_Get_LSIRDY(void)
{
  return (READ_BIT(RCC->CSR, RCC_CSR_LSIRDY) == (RCC_CSR_LSIRDY));
}

/**
  * @function  RCC_Enable_PLL
  * @brief  Enable PLL
  * @retval None
*/
__STATIC_INLINE void RCC_Enable_PLL(void)
{
   SET_BIT(RCC->CR, RCC_CR_PLLON);
}

/**
  * @function  RCC_Disable_PLL
  * @brief  Disable PLL
  * @retval None
*/
__STATIC_INLINE void RCC_Disable_PLL(void)
{
   CLEAR_BIT(RCC->CR, RCC_CR_PLLON);
}

/**
  * @function  RCC_Get_PLLRDY
  * @brief  check if PLL ready
  * @param  None
  * @retval 1:PLL is ready, 0: PLL not ready
*/
__STATIC_INLINE uint32_t RCC_Get_PLLRDY(void)
{
  return (READ_BIT(RCC->CR, RCC_CR_PLLRDY) == (RCC_CR_PLLRDY));
}
/**
  * @function  RCC_Set_PLLMUL
  * @brief  config PLL mul for system clock
  * @param  PLLMUL:
            @arg RCC_CFGR_PLLMUL_10x
            @arg RCC_CFGR_PLLMUL_12x
            @arg RCC_CFGR_PLLMUL_14x
            @arg RCC_CFGR_PLLMUL_15x
            @arg RCC_CFGR_PLLMUL_16x
            @arg RCC_CFGR_PLLMUL_17x
            @arg RCC_CFGR_PLLMUL_18x
            @arg RCC_CFGR_PLLMUL_19x
  * @retval None
*/
__STATIC_INLINE void RCC_Set_PLLMUL(uint32_t PLLMUL)
{
   MODIFY_REG(RCC->CFGR,RCC_CFGR_PLLMULL,PLLMUL);	
}
/**
  * @function  RCC_Set_SysClkSource
  * @brief  Set the system clock source
  * @param  Source:
            @arg RCC_CFGR_SW_HSI
            @arg RCC_CFGR_SW_PLL
            @arg RCC_CFGR_SW_LSI
  * @retval None
*/
__STATIC_INLINE void RCC_Set_SysClkSource(uint32_t Source)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, Source);
}

/**
  * @function  RCC_Get_SysClkSource
  * @brief  Get the system clock source
  * @param  None
  * @retval 
            @arg RCC_CFGR_SWS_HSI
            @arg RCC_CFGR_SWS_PLL
            @arg RCC_CFGR_SWS_LSI
*/
__STATIC_INLINE uint32_t RCC_Get_SysClkSource(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_SWS));
}

/**
  * @function  RCC_Set_ADCClkSource
  * @brief  Set the ADC clock source
  * @param  Source:
            @arg RCC_CFGR_ADCCLK_SEL_SYSCLK
            @arg RCC_CFGR_ADCCLK_SEL_PLL2
  * @retval None
*/
__STATIC_INLINE void RCC_Set_ADCClkSource(uint32_t Source)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_ADCCLK_SEL, Source);
}

/**
  * @function  RCC_Get_ADCClkSource
  * @brief  Get the ADC clock source
  * @param  None
  * @retval 
            @arg RCC_CFGR_ADCCLK_SEL_SYSCLK
            @arg RCC_CFGR_ADCCLK_SEL_PLL2
*/
__STATIC_INLINE uint32_t RCC_Get_ADCClkSource(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_ADCCLK_SEL));
}

/**
  * @function  RCC_Set_AHBPrescaler
  * @brief  Set AHB prescaler
  * @param  Prescaler:
            @arg RCC_CFGR_HPRE_DIV1
            @arg RCC_CFGR_HPRE_DIV2
            @arg RCC_CFGR_HPRE_DIV4
            @arg RCC_CFGR_HPRE_DIV8
            @arg RCC_CFGR_HPRE_DIV16
            @arg RCC_CFGR_HPRE_DIV64
            @arg RCC_CFGR_HPRE_DIV128
            @arg RCC_CFGR_HPRE_DIV256
            @arg RCC_CFGR_HPRE_DIV512
  * @retval None
*/
__STATIC_INLINE void RCC_Set_AHBPrescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, Prescaler);
}

/**
  * @function  RCC_Set_APB1Prescaler
  * @brief  Set APB1 prescaler
  * @param  Prescaler:
            @arg RCC_CFGR_PPRE1_DIV1
            @arg RCC_CFGR_PPRE1_DIV2
            @arg RCC_CFGR_PPRE1_DIV4
            @arg RCC_CFGR_PPRE1_DIV8
            @arg RCC_CFGR_PPRE1_DIV16
  * @retval None
*/
__STATIC_INLINE void RCC_Set_APB1Prescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, Prescaler);
}

/**
  * @function  RCC_Set_APB2Prescaler
  * @brief  Set APB2 prescaler
  * @param  Prescaler:
            @arg RCC_CFGR_PPRE2_DIV1
            @arg RCC_CFGR_PPRE2_DIV2
            @arg RCC_CFGR_PPRE2_DIV4
            @arg RCC_CFGR_PPRE2_DIV8
            @arg RCC_CFGR_PPRE2_DIV16
  * @retval None
*/
__STATIC_INLINE void RCC_Set_APB2Prescaler(uint32_t Prescaler)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, Prescaler);
}

/**
  * @function  RCC_Set_ADCPrescaler
  * @brief  Set ADC prescaler
  * @param  Source:
            @arg RCC_CFGR_ADCPRE_DIV2
            @arg RCC_CFGR_ADCPRE_DIV3
            @arg RCC_CFGR_ADCPRE_DIV4
            @arg RCC_CFGR_ADCPRE_DIV5
						@arg RCC_CFGR_ADCPRE_DIV6
            @arg RCC_CFGR_ADCPRE_DIV7
            @arg RCC_CFGR_ADCPRE_DIV8
  * @retval None
*/
__STATIC_INLINE void RCC_Set_ADCPrescaler(uint32_t ADCxPrescaler)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_ADCPRE, ADCxPrescaler);
}

/**
  * @function  RCC_Get_AHBPrescaler
  * @brief  Get AHB Prescaler
  * @param  None
  * @retval 
            @arg RCC_CFGR_HPRE_DIV1
            @arg RCC_CFGR_HPRE_DIV2
            @arg RCC_CFGR_HPRE_DIV4
            @arg RCC_CFGR_HPRE_DIV8
            @arg RCC_CFGR_HPRE_DIV16
            @arg RCC_CFGR_HPRE_DIV32
            @arg RCC_CFGR_HPRE_DIV64
            @arg RCC_CFGR_HPRE_DIV128
            @arg RCC_CFGR_HPRE_DIV256
            @arg RCC_CFGR_HPRE_DIV512
*/
__STATIC_INLINE uint32_t RCC_Get_AHBPrescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_HPRE));
}

/**
  * @function  RCC_Get_APB1Prescaler
  * @brief  Get APB1 Prescaler
  * @param  None
  * @retval 
            @arg RCC_CFGR_PPRE1_DIV1
            @arg RCC_CFGR_PPRE1_DIV2
            @arg RCC_CFGR_PPRE1_DIV4
            @arg RCC_CFGR_PPRE1_DIV8
            @arg RCC_CFGR_PPRE1_DIV16
*/
__STATIC_INLINE uint32_t RCC_Get_APB1Prescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_PPRE1));
}

/**
  * @function  RCC_Get_APB2Prescaler
  * @brief  Get APB2 Prescaler
  * @param  None
  * @retval 
            @arg RCC_CFGR_PPRE2_DIV1
            @arg RCC_CFGR_PPRE2_DIV2
            @arg RCC_CFGR_PPRE2_DIV4
            @arg RCC_CFGR_PPRE2_DIV8
            @arg RCC_CFGR_PPRE2_DIV16
*/
__STATIC_INLINE uint32_t RCC_Get_APB2Prescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_PPRE2));
}

/**
  * @function  RCC_Get_ADCPrescaler
  * @brief  Get APB2 Prescaler
  * @param  None
  * @retval 
            @arg RCC_CFGR_ADCPRE_DIV2
            @arg RCC_CFGR_ADCPRE_DIV3
            @arg RCC_CFGR_ADCPRE_DIV4
            @arg RCC_CFGR_ADCPRE_DIV5
						@arg RCC_CFGR_ADCPRE_DIV6
            @arg RCC_CFGR_ADCPRE_DIV7
            @arg RCC_CFGR_ADCPRE_DIV8
*/
__STATIC_INLINE uint32_t RCC_Get_ADCPrescaler(void)
{
  return (uint32_t)(READ_BIT(RCC->CFGR, RCC_CFGR_ADCPRE));
}

/**
  * @function  RCC_Config_MCO
  * @brief  MCO clock out select
  * @param  MCOxSource:
            @arg RCC_CFGR_MCO_NOCLK
            @arg RCC_CFGR_MCO_LSI
            @arg RCC_CFGR_MCO_FSYS
            @arg RCC_CFGR_MCO_HSI
            @arg RCC_CFGR_MCO_PLL
  * @param  MCOxPrescaler:
            @arg RCC_CFGR_MCO_DIV1
            @arg RCC_CFGR_MCO_DIV2
            @arg RCC_CFGR_MCO_DIV4
            @arg RCC_CFGR_MCO_DIV8
*/
__STATIC_INLINE void RCC_Config_MCO(uint32_t MCOxSource, uint32_t MCOxPrescaler)
{
  MODIFY_REG(RCC->CFGR, RCC_CFGR_MCO_SEL | RCC_CFGR_MCO_PRE, MCOxSource | MCOxPrescaler);
}

/**
  * @function  RCC_Enable_APB1Clock
  * @brief  Enable APB1 periphal clock
  * @param  Periphal:
            @arg RCC_APB1ENR_TIM2EN  
            @arg RCC_APB1ENR_TIM3EN  
            @arg RCC_APB1ENR_TIM6EN  
            @arg RCC_APB1ENR_TIM7EN  
            @arg RCC_APB1ENR_UART2EN
            @arg RCC_APB1ENR_I2C1EN  
            @arg RCC_APB1ENR_PWREN   
  * @retval None
*/
__STATIC_INLINE void RCC_Enable_APB1Clock(uint32_t Periphal)
{
    SET_BIT(RCC->APB1ENR, Periphal);
}

/**
  * @function  RCC_Disable_APB1Clock
  * @brief  Disable APB1 periphal clock
  * @param  Periphal:
            @arg RCC_APB1ENR_TIM2EN  
            @arg RCC_APB1ENR_TIM3EN  
            @arg RCC_APB1ENR_TIM6EN  
            @arg RCC_APB1ENR_TIM7EN  
            @arg RCC_APB1ENR_UART2EN
            @arg RCC_APB1ENR_I2C1EN  
            @arg RCC_APB1ENR_PWREN   
  * @retval None
*/
__STATIC_INLINE void RCC_Disable_APB1Clock(uint32_t Periphal)
{
    CLEAR_BIT(RCC->APB1ENR, Periphal);
}

/**
  * @function  RCC_Enable_APB2Clock
  * @brief  Enable APB2 periphal clock
  * @param  Periphal:
            @arg RCC_APB2ENR_SYSCFGEN 
            @arg RCC_APB2ENR_SPI1EN   
            @arg RCC_APB2ENR_TIM8EN   
            @arg RCC_APB2ENR_UART1EN 
            @arg RCC_APB2ENR_TIM15EN  
  * @retval None
*/
__STATIC_INLINE void RCC_Enable_APB2Clock(uint32_t Periphal)
{
    SET_BIT(RCC->APB2ENR, Periphal);
}

/**
  * @function  RCC_Disable_APB2Clock
  * @brief  Disable APB2 periphal clock
  * @param  Periphal:
            @arg RCC_APB2ENR_SYSCFGEN 
            @arg RCC_APB2ENR_SPI1EN   
            @arg RCC_APB2ENR_TIM8EN   
            @arg RCC_APB2ENR_UART1EN 
            @arg RCC_APB2ENR_TIM15EN  
  * @retval None
*/
__STATIC_INLINE void RCC_Disable_APB2Clock(uint32_t Periphal)
{
  CLEAR_BIT(RCC->APB2ENR, Periphal);
}

/**
  * @function  RCC_Enable_AHBClock
  * @brief  Enable AHB periphal clock
  * @param  Periphal:
            @arg RCC_AHBENR_SRAMEN
            @arg RCC_AHBENR_FLITEN
            @arg RCC_AHBENR_CRCEN 
            @arg RCC_AHBENR_MEEN  
            @arg RCC_AHBENR_IOPAEN
            @arg RCC_AHBENR_IOPBEN
            @arg RCC_AHBENR_IOPCEN
            @arg RCC_AHBENR_IOPDEN
            @arg RCC_AHBENR_ADC1EN
  * @retval None
*/
__STATIC_INLINE void RCC_Enable_AHBClock(uint32_t Periphal)
{
    SET_BIT(RCC->AHBENR, Periphal);
}

/**
  * @function  RCC_Disable_AHBClock
  * @brief  Disable AHB periphal clock
  * @param  Periphal:
            @arg RCC_AHBENR_SRAMEN
            @arg RCC_AHBENR_FLITEN
            @arg RCC_AHBENR_CRCEN 
            @arg RCC_AHBENR_MEEN  
            @arg RCC_AHBENR_IOPAEN
            @arg RCC_AHBENR_IOPBEN
            @arg RCC_AHBENR_IOPCEN
            @arg RCC_AHBENR_IOPDEN
            @arg RCC_AHBENR_ADC1EN
  * @retval None
*/
__STATIC_INLINE void RCC_Disable_AHBClock(uint32_t Periphal)
{
    CLEAR_BIT(RCC->AHBENR, Periphal);
}

/**
  * @function  RCC_Enable_RTC
  * @brief  Enable_RTCEN
  * @retval None
*/
__STATIC_INLINE void RCC_Enable_RTC(void)
{
    SET_BIT(RCC->BDCR, RCC_BDCR_RTCEN);
}

/**
  * @function  RCC_Disable_RTC
  * @brief  Disable RTCEN
  * @retval None
*/
__STATIC_INLINE void RCC_Disable_RTC(void)
{
  CLEAR_BIT(RCC->BDCR, RCC_BDCR_RTCEN);
}

/**
  * @brief  Check if RTC has been enabled or not
  * @rmtoll BDCR         RTCEN         RCC_Get_RTC
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t RCC_Get_RTC(void)
{
  return (READ_BIT(RCC->BDCR, RCC_BDCR_RTCEN) == (RCC_BDCR_RTCEN));
}

/**
  * @function  RCC_Enable_BDRST
  * @brief  Enable BDRST
  * @retval None
  */
__STATIC_INLINE void RCC_Enable_BDRST(void)
{
    SET_BIT(RCC->BDCR, RCC_BDCR_BDRST);
}

/**
  * @function  RCC_Disable_BDRST
  * @brief  Disable BDRST
  * @retval None
  */
__STATIC_INLINE void RCC_Disable_BDRST(void)
{
    CLEAR_BIT(RCC->BDCR, RCC_BDCR_BDRST);
}

/**
  * @function  RCC_Enable_AHBRST
  * @brief  Enable AHB periphal RESET
  * @param  Periphal This parameter can be one of the following values:
            @arg RCC_AHBRSTR_CRCRST 
            @arg RCC_AHBRSTR_MERST  
            @arg RCC_AHBRSTR_IOPARST
            @arg RCC_AHBRSTR_IOPBRST
            @arg RCC_AHBRSTR_IOPCRST
            @arg RCC_AHBRSTR_IOPDRST
            @arg RCC_AHBRSTR_ADC1RST
  * @retval None
  */
__STATIC_INLINE void RCC_Enable_AHBRST(uint32_t Periphal)
{
    SET_BIT(RCC->AHBRSTR, Periphal);
}

/**
  * @function  RCC_Disable_AHBRST
  * @brief  Disable AHB periphal RESET
  * @param  Periphal This parameter can be one of the following values:
            @arg RCC_AHBRSTR_CRCRST 
            @arg RCC_AHBRSTR_MERST  
            @arg RCC_AHBRSTR_IOPARST
            @arg RCC_AHBRSTR_IOPBRST
            @arg RCC_AHBRSTR_IOPCRST
            @arg RCC_AHBRSTR_IOPDRST
            @arg RCC_AHBRSTR_ADC1RST
  * @retval None
  */
__STATIC_INLINE void RCC_Disable_AHBRST(uint32_t Periphal)
{
    CLEAR_BIT(RCC->AHBRSTR, Periphal);
}
/**
  * @function  RCC_Enable_APB1RST
  * @brief  Enable APB1 periphal RESET
  * @param  Periphal This parameter can be one of the following values:
            @arg RCC_APB1RSTR_TIM2RST   
            @arg RCC_APB1RSTR_TIM3RST   
            @arg RCC_APB1RSTR_TIM6RST   
            @arg RCC_APB1RSTR_TIM7RST   
            @arg RCC_APB1RSTR_UART2RST 
            @arg RCC_APB1RSTR_I2C1RST   
            @arg RCC_APB1RSTR_PWRRST    
  * @retval None
  */
__STATIC_INLINE void RCC_Enable_APB1RST(uint32_t Periphal)
{
    SET_BIT(RCC->APB1RSTR, Periphal);
}

/**
  * @function  RCC_Disable_APB1RST
  * @brief  Disable APB1 periphal RESET
  * @param  Periphal This parameter can be one of the following values:
            @arg RCC_APB1RSTR_TIM2RST   
            @arg RCC_APB1RSTR_TIM3RST   
            @arg RCC_APB1RSTR_TIM6RST   
            @arg RCC_APB1RSTR_TIM7RST   
            @arg RCC_APB1RSTR_UART2RST 
            @arg RCC_APB1RSTR_I2C1RST   
            @arg RCC_APB1RSTR_PWRRST    
  * @retval None
  */
__STATIC_INLINE void RCC_Disable_APB1RST(uint32_t Periphal)
{
    CLEAR_BIT(RCC->APB1RSTR, Periphal);
}

/**
  * @function  RCC_Enable_APB2RST
  * @brief  Enable APB2 periphal RESET
  * @param  Periphal This parameter can be one of the following values:
  *         @arg RCC_APB2RSTR_SYSCFGRST
            @arg RCC_APB2RSTR_SPI1RST  
            @arg RCC_APB2RSTR_TIM8RST  
            @arg RCC_APB2RSTR_UART1RST
            @arg RCC_APB2RSTR_TIM15RST 
  * @retval None
  */
__STATIC_INLINE void RCC_Enable_APB2RST(uint32_t Periphal)
{
    SET_BIT(RCC->APB2RSTR, Periphal);
}

/**
  * @function  RCC_Disable_APB2RST
  * @brief  Disable APB2 periphal RESET
  * @param  Periphal This parameter can be one of the following values:
  *         @arg RCC_APB2RSTR_SYSCFGRST
            @arg RCC_APB2RSTR_SPI1RST  
            @arg RCC_APB2RSTR_TIM8RST  
            @arg RCC_APB2RSTR_UART1RST
            @arg RCC_APB2RSTR_TIM15RST 
  * @retval None
  */
__STATIC_INLINE void RCC_Disable_APB2RST(uint32_t Periphal)
{
    CLEAR_BIT(RCC->APB2RSTR, Periphal);
}

/**
  * @function  RCC_Get_RSTFlag
  * @brief  check if Reset flag
  * @param  FLAG This parameter can be one of the following values:
  *         @arg RCC_CSR_OBLRSTF  
  *         @arg RCC_CSR_PINRSTF  
  *         @arg RCC_CSR_PORRSTF  
  *         @arg RCC_CSR_SFTRSTF  
  *         @arg RCC_CSR_IWDGRSTF 
  *         @arg RCC_CSR_LPWRRSTF 
  * @retval 1:reset, 0: no reset
*/
__STATIC_INLINE uint32_t RCC_Get_RSTFlag(uint32_t FLAG)
{
  return (READ_BIT(RCC->CSR, FLAG) == (FLAG));
}

/**
  * @function RCC_Clear_RSTFlags
  * @brief  Set RMVF bit to clear the reset flags.
  * @param  None
  * @retval None
  */
__STATIC_INLINE void RCC_Clear_RSTFlags(void)
{
  SET_BIT(RCC->CSR, RCC_CSR_RMVF);
}

/**
  * @function  RCC_Get_ITFlag
  * @brief  Get if Interrupt flag
  * @param  InterruptFLAG This parameter can be one of the following values:
  *         @arg RCC_CIR_LSIRDYF
  *         @arg RCC_CIR_HSIRDYF
  *         @arg RCC_CIR_PLLRDYF 
  * @retval 1:ready, 0: no ready
*/
__STATIC_INLINE uint32_t RCC_Get_ITFlag(uint32_t InterruptFLAG)
{
  return (READ_BIT(RCC->CIR, InterruptFLAG) == (InterruptFLAG));
}

/**
  * @function  RCC_Clear_ITFlags
  * @brief  Clear Interrupt flag
  * @param  InterruptFLAG This parameter can be one of the following values:
  *         @arg RCC_CIR_LSIRDYC
  *         @arg RCC_CIR_HSIRDYC
  *         @arg RCC_CIR_PLLRDYC 
  * @retval None
*/
__STATIC_INLINE void RCC_Clear_ITFlags(uint32_t InterruptFLAG)
{
  SET_BIT(RCC->CIR, InterruptFLAG);
}

/**
  * @function  RCC_Enable_IT
  * @brief  Enable Periphal Interrupt
  * @param  Periphal This parameter can be one of the following values:
  *         @arg RCC_CIR_LSIRDYIE
  *         @arg RCC_CIR_HSIRDYIE
  *         @arg RCC_CIR_PLLRDYIE 
  * @retval None
  */
__STATIC_INLINE void RCC_Enable_IT(uint32_t Periphal)
{
    SET_BIT(RCC->CIR, Periphal);
}

/**
  * @function  RCC_Disable_IT
  * @brief  Disable Periphal Interrupt
  * @param  Periphal This parameter can be one of the following values:
  *         @arg RCC_CIR_LSIRDYIE
  *         @arg RCC_CIR_HSIRDYIE
  *         @arg RCC_CIR_PLLRDYIE 
  * @retval None
  */
__STATIC_INLINE void RCC_Disable_IT(uint32_t Periphal)
{
    CLEAR_BIT(RCC->CIR, Periphal);
}

/**
  * @function  RCC_Set_PLLDET_DELTA
  * @brief  Set the PLLDET DELTA
  * @param  Periphal£º0x00000000~0x0000001f
  * @retval DELTA of PLLDET
*/
__STATIC_INLINE void RCC_Set_PLLDET_DELTA(uint32_t Periphal)
{
	MODIFY_REG(RCC->PLLDET, RCC_PLLDET_DELTA, Periphal);
}

/**
  * @function  RCC_Get_PLLDET_DELTA
  * @brief  Get the PLLDET DELTA
  * @param  None
  * @retval DELTA of PLLDET
*/
__STATIC_INLINE uint32_t RCC_Get_PLLDET_DELTA(void)
{
	return (uint32_t)(READ_BIT(RCC->PLLDET, RCC_PLLDET_DELTA));
}

/**
  * @function  RCC_Enable_PLLDET_FAIL
  * @brief  Enable PLLDET FAIL
	* @param  Periphal:
  *         @arg RCC_PLLDET_FAIL_M0
  *         @arg RCC_PLLDET_FAIL_M1
  *         @arg RCC_PLLDET_FAIL_M2
  * @retval None
  */
__STATIC_INLINE void RCC_Enable_PLLDET_FAIL(uint32_t Periphal)
{
   SET_BIT(RCC->PLLDET, Periphal);
}

/**
  * @function  RCC_Disable_PLLDET_FAIL
  * @brief  Disable PLLDET FAIL
	* @param  Periphal:
  *         @arg RCC_PLLDET_FAIL_M0
  *         @arg RCC_PLLDET_FAIL_M1
  *         @arg RCC_PLLDET_FAIL_M2
  * @retval None
  */
__STATIC_INLINE void RCC_Disable_PLLDET_FAIL(uint32_t Periphal)
{
   CLEAR_BIT(RCC->PLLDET, Periphal);
}

/**
  * @function  RCC_Get_PLLDET_TCNT_UPEN
  * @brief  Get the status that whether the tracking count is update
  * @param  None
  * @retval 1:update, 0: no update
*/
__STATIC_INLINE uint32_t RCC_Get_PLLDET_TCNT_UPEN(void)
{
	return (uint32_t)(READ_BIT(RCC->PLLDET, RCC_PLLDET_TCNT_UPEN)==(RCC_PLLDET_TCNT_UPEN));
}

/**
  * @function  RCC_Set_PLLDET_FCNT_WIDTH
  * @brief  Set the PLLDET FCNT WIDTH
  * @param  Periphal:
            @arg RCC_PLLDET_FCNT_WIDTH_5bit 
            @arg RCC_PLLDET_FCNT_WIDTH_6bit 
            @arg RCC_PLLDET_FCNT_WIDTH_7bit 
            @arg RCC_PLLDET_FCNT_WIDTH_8bit 
            @arg RCC_PLLDET_FCNT_WIDTH_9bit 
            @arg RCC_PLLDET_FCNT_WIDTH_10bit
            @arg RCC_PLLDET_FCNT_WIDTH_11bit
  * @retval None
*/
__STATIC_INLINE void RCC_Set_PLLDET_FCNT_WIDTH(uint32_t Periphal)
{
  MODIFY_REG(RCC->PLLDET, RCC_PLLDET_FCNT_WIDTH, Periphal);
}

/**
  * @function  RCC_Get_PLLDET_TOUT
  * @brief  Get the PLLDET TOUT
  * @param  None
  * @retval TOUT of PLLDET
*/
__STATIC_INLINE uint32_t RCC_Get_PLLDET_TOUT(void)
{
	return (uint32_t)(READ_BIT(RCC->PLLDET, RCC_PLLDET_TOUT)>>16);
}

void RCC_ClockConfig(RCC_ClkInitTypeDef  *RCC_ClkInitStruct);
uint32_t RCC_Get_PLLClock(void);
uint32_t RCC_Get_SystemClock(void);
uint32_t RCC_Get_AHBClock(void);
uint32_t RCC_Get_APB1Clock(void);
uint32_t RCC_Get_APB2Clock(void);

#ifdef __cplusplus
}
#endif

#endif /* __rx32h6xx_RCC_H__ */

