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
* File         : rx32h6xx_exti.h
* By           : RX_SD_Team
* Description  : Only rx32h6xx
*********************************************************************************************************
*/
#ifndef __rx32h6xx_EXTI_H__
#define __rx32h6xx_EXTI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "rx32h6xx.h"

/******************************************************************************/
/*                                                                            */
/*                    External Interrupt/Event Controller                     */
/*                                                                            */
/******************************************************************************/

#if defined (EXTI)

/** @defgroup EXTI  */
  
typedef struct
{

  uint32_t Line;          		  /*!< Specifies the EXTI lines to be enabled or disabled for Lines in range 0 to 31
                                     This parameter can be any combination of @ref EXTI_EC_LINE */

  FunctionalState LineCommand;  /*!< Specifies the new state of the selected EXTI lines.
                                     This parameter can be set either to ENABLE or DISABLE */

  uint8_t Mode;                 /*!< Specifies the mode for the EXTI lines.
                                     This parameter can be a value of @ref EXTI_EC_MODE. */

  uint8_t Trigger;              /*!< Specifies the trigger signal active edge for the EXTI lines.
                                     This parameter can be a value of @ref EXTI_EC_TRIGGER. */
} EXTI_InitTypeDef;
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private Macros ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/** @defgroup EXTI_Exported_Constants EXTI Exported Constants  */

/*******************  Bit definition for EXTI_IMR register  *******************/

#define EXTI_IMR_MR0                        BIT0                   /*!< Interrupt Mask on line 0 0x00000001*/
#define EXTI_IMR_MR1                        BIT1                   /*!< Interrupt Mask on line 1 0x00000002*/
#define EXTI_IMR_MR2                        BIT2                   /*!< Interrupt Mask on line 2 0x00000004*/
#define EXTI_IMR_MR3                        BIT3                   /*!< Interrupt Mask on line 3 0x00000008*/
#define EXTI_IMR_MR4                        BIT4                   /*!< Interrupt Mask on line 4 0x00000010*/
#define EXTI_IMR_MR5                        BIT5                   /*!< Interrupt Mask on line 5 0x00000020*/
#define EXTI_IMR_MR6                        BIT6                   /*!< Interrupt Mask on line 6 0x00000040*/
#define EXTI_IMR_MR7                        BIT7                   /*!< Interrupt Mask on line 7 0x00000080*/
#define EXTI_IMR_MR16                       BIT16                  /*!< Interrupt Mask on line 16 0x00010000*/
#define EXTI_IMR_MR17                       BIT17                  /*!< Interrupt Mask on line 17 0x00020000*/
#define EXTI_IMR_MR21                       BIT21                  /*!< Interrupt Mask on line 21 0x00200000*/
#define EXTI_IMR_MR22                       BIT22                  /*!< Interrupt Mask on line 22 0x00400000*/

/*******************  Bit definition for EXTI_EMR register  *******************/
#define EXTI_EMR_MR0                        BIT0                   /*!< Event Mask on line 0 0x00000001*/
#define EXTI_EMR_MR1                        BIT1                   /*!< Event Mask on line 1 0x00000002*/
#define EXTI_EMR_MR2                        BIT2                   /*!< Event Mask on line 2 0x00000004*/
#define EXTI_EMR_MR3                        BIT3                   /*!< Event Mask on line 3 0x00000008*/
#define EXTI_EMR_MR4                        BIT4                   /*!< Event Mask on line 4 0x00000010*/
#define EXTI_EMR_MR5                        BIT5                   /*!< Event Mask on line 5 0x00000020*/
#define EXTI_EMR_MR6                        BIT6                   /*!< Event Mask on line 6 0x00000040*/
#define EXTI_EMR_MR7                        BIT7                   /*!< Event Mask on line 7 0x00000080*/
#define EXTI_EMR_MR16                       BIT16                  /*!< Event Mask on line 16 0x00010000*/
#define EXTI_EMR_MR17                       BIT17                  /*!< Event Mask on line 17 0x00020000*/
#define EXTI_EMR_MR21                       BIT21                  /*!< Event Mask on line 21 0x00200000*/
#define EXTI_EMR_MR22                       BIT22                  /*!< Event Mask on line 22 0x00400000*/

/******************  Bit definition for EXTI_RTSR register  *******************/
#define EXTI_RTSR_TR0                       BIT0                   /*!< Rising trigger event configuration bit of line 0 0x00000001*/
#define EXTI_RTSR_TR1                       BIT1                   /*!< Rising trigger event configuration bit of line 1 0x00000002*/
#define EXTI_RTSR_TR2                       BIT2                   /*!< Rising trigger event configuration bit of line 2 0x00000004*/
#define EXTI_RTSR_TR3                       BIT3                   /*!< Rising trigger event configuration bit of line 3 0x00000008*/
#define EXTI_RTSR_TR4                       BIT4                   /*!< Rising trigger event configuration bit of line 4 0x00000010*/
#define EXTI_RTSR_TR5                       BIT5                   /*!< Rising trigger event configuration bit of line 5 0x00000020*/
#define EXTI_RTSR_TR6                       BIT6                   /*!< Rising trigger event configuration bit of line 6 0x00000040*/
#define EXTI_RTSR_TR7                       BIT7                   /*!< Rising trigger event configuration bit of line 7 0x00000080*/
#define EXTI_RTSR_TR16                      BIT16                  /*!< Rising trigger event configuration bit of line 16 0x00010000*/
#define EXTI_RTSR_TR17                      BIT17                  /*!< Rising trigger event configuration bit of line 17 0x00020000*/
#define EXTI_RTSR_TR21                      BIT21                  /*!< Rising trigger event configuration bit of line 21 0x00200000*/
#define EXTI_RTSR_TR22                      BIT22                  /*!< Rising trigger event configuration bit of line 22 0x00400000*/

/******************  Bit definition for EXTI_FTSR register  *******************/
#define EXTI_FTSR_TR0                       BIT0                   /*!< Falling trigger event configuration bit of line 0 0x00000001*/
#define EXTI_FTSR_TR1                       BIT1                   /*!< Falling trigger event configuration bit of line 1 0x00000002*/
#define EXTI_FTSR_TR2                       BIT2                   /*!< Falling trigger event configuration bit of line 2 0x00000004*/
#define EXTI_FTSR_TR3                       BIT3                   /*!< Falling trigger event configuration bit of line 3 0x00000008*/
#define EXTI_FTSR_TR4                       BIT4                   /*!< Falling trigger event configuration bit of line 4 0x00000010*/
#define EXTI_FTSR_TR5                       BIT5                   /*!< Falling trigger event configuration bit of line 5 0x00000020*/
#define EXTI_FTSR_TR6                       BIT6                   /*!< Falling trigger event configuration bit of line 6 0x00000040*/
#define EXTI_FTSR_TR7                       BIT7                   /*!< Falling trigger event configuration bit of line 7 0x00000080*/
#define EXTI_FTSR_TR16                      BIT16                  /*!< Falling trigger event configuration bit of line 16 0x00010000*/
#define EXTI_FTSR_TR17                      BIT17                  /*!< Falling trigger event configuration bit of line 17 0x00020000*/
#define EXTI_FTSR_TR21                      BIT21                  /*!< Falling trigger event configuration bit of line 21 0x00200000*/
#define EXTI_FTSR_TR22                      BIT22                  /*!< Falling trigger event configuration bit of line 22 0x00400000*/

/******************  Bit definition for EXTI_SWIER register  ******************/
#define EXTI_SWIER_SWIER0                   BIT0                   /*!< Software Interrupt on line 0 0x00000001*/
#define EXTI_SWIER_SWIER1                   BIT1                   /*!< Software Interrupt on line 1 0x00000002*/
#define EXTI_SWIER_SWIER2                   BIT2                   /*!< Software Interrupt on line 2 0x00000004*/
#define EXTI_SWIER_SWIER3                   BIT3                   /*!< Software Interrupt on line 3 0x00000008*/
#define EXTI_SWIER_SWIER4                   BIT4                   /*!< Software Interrupt on line 4 0x00000010*/
#define EXTI_SWIER_SWIER5                   BIT5                   /*!< Software Interrupt on line 5 0x00000020*/
#define EXTI_SWIER_SWIER6                   BIT6                   /*!< Software Interrupt on line 6 0x00000040*/
#define EXTI_SWIER_SWIER7                   BIT7                   /*!< Software Interrupt on line 7 0x00000080*/
#define EXTI_SWIER_SWIER16                  BIT16                  /*!< Software Interrupt on line 16 0x00010000*/
#define EXTI_SWIER_SWIER17                  BIT17                  /*!< Software Interrupt on line 17 0x00020000*/
#define EXTI_SWIER_SWIER21                  BIT21                  /*!< Software Interrupt on line 21 0x00200000*/
#define EXTI_SWIER_SWIER22                  BIT22                  /*!< Software Interrupt on line 22 0x00400000*/

/*******************  Bit definition for EXTI_PR register  ********************/
#define EXTI_PR_PR0                         BIT0                   /*!< Pending bit on line 0 0x00000001*/
#define EXTI_PR_PR1                         BIT1                   /*!< Pending bit on line 1 0x00000002*/
#define EXTI_PR_PR2                         BIT2                   /*!< Pending bit on line 2 0x00000004*/
#define EXTI_PR_PR3                         BIT3                   /*!< Pending bit on line 3 0x00000008*/
#define EXTI_PR_PR4                         BIT4                   /*!< Pending bit on line 4 0x00000010*/
#define EXTI_PR_PR5                         BIT5                   /*!< Pending bit on line 5 0x00000020*/
#define EXTI_PR_PR6                         BIT6                   /*!< Pending bit on line 6 0x00000040*/
#define EXTI_PR_PR7                         BIT7                   /*!< Pending bit on line 7 0x00000080*/
#define EXTI_PR_PR16                        BIT16                  /*!< Pending bit on line 16 0x00010000*/
#define EXTI_PR_PR17                        BIT17                  /*!< Pending bit on line 17 0x00020000*/
#define EXTI_PR_PR21                        BIT21                  /*!< Pending bit on line 21 0x00200000*/
#define EXTI_PR_PR22                        BIT22                  /*!< Pending bit on line 22 0x00400000*/

#define EXTI_LINE_NONE     				         (0x00000000U)  /*!< None Extended line */
#define EXTI_LINE_0             				    BIT0           /*!< Extended line 0 */
#define EXTI_LINE_1              				    BIT1           /*!< Extended line 1 */
#define EXTI_LINE_2              				    BIT2           /*!< Extended line 2 */
#define EXTI_LINE_3                         BIT3           /*!< Extended line 3 */
#define EXTI_LINE_4                         BIT4           /*!< Extended line 4 */
#define EXTI_LINE_5               				  BIT5           /*!< Extended line 5 */
#define EXTI_LINE_6                				  BIT6           /*!< Extended line 6 */
#define EXTI_LINE_7                 				BIT7           /*!< Extended line 7 */
#define EXTI_LINE_16                				BIT16          /*!< Extended line 16 */
#define EXTI_LINE_17                				BIT17          /*!< Extended line 17 */
#define EXTI_LINE_21                				BIT21          /*!< Extended line 21 */
#define EXTI_LINE_22                				BIT22          /*!< Extended line 22 */
#define EXTI_LINE_A0_31             			  0x6300FFU    /*!< All Extended line not reserved*/
#define EXTI_LINE_ALL               			 (0xFFFFFFFFU)  /*!< All Extended line */

#if defined(USE_FUDRIVER)
#define EXTI_LINE_NONE              (0x00000000U)  /*!< None Extended line */
#endif /*USE_FUDRIVER*/


/* Exported macro ------------------------------------------------------------*/
/** @defgroup EXTI_Exported_Macros EXTI Exported Macros  */

/** @defgroup EXTI_EM_WRITE_READ Common Write and read registers Macros  */

/**
  * @brief  Write a value in EXTI register
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define EXTI_WriteReg(__REG__, __VALUE__) WRITE_REG(EXTI->__REG__, (__VALUE__))

/**
  * @brief  Read a value in EXTI register
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define EXTI_ReadReg(__REG__) READ_REG(EXTI->__REG__)

#define EXTI_MODE_IT                 ((uint8_t)0x00) /*!< Interrupt Mode */
#define EXTI_MODE_EVENT              ((uint8_t)0x01) /*!< Event Mode */
#define EXTI_MODE_IT_EVENT           ((uint8_t)0x02) /*!< Interrupt & Event Mode */

/** @defgroup EXTI_EC_TRIGGER Edge Trigger  */
#define EXTI_TRIGGER_NONE            ((uint8_t)0x00) /*!< No Trigger Mode */
#define EXTI_TRIGGER_RISING          ((uint8_t)0x01) /*!< Trigger Rising Mode */
#define EXTI_TRIGGER_FALLING         ((uint8_t)0x02) /*!< Trigger Falling Mode */
#define EXTI_TRIGGER_RISING_FALLING  ((uint8_t)0x03) /*!< Trigger Rising & Falling Mode */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @addtogroup EXTI_Private_Macros
  * @{
  */

#define IS_EXTI_LINE(__VALUE__)                   (((__VALUE__) & ~EXTI_LINE_A0_31) == 0x00000000U)

#define IS_EXTI_MODE(__VALUE__)                   (((__VALUE__) == EXTI_MODE_IT)            \
                                                   || ((__VALUE__) == EXTI_MODE_EVENT)         \
                                                   || ((__VALUE__) == EXTI_MODE_IT_EVENT))


#define IS_EXTI_TRIGGER(__VALUE__)                (((__VALUE__) == EXTI_TRIGGER_NONE)       \
                                                   || ((__VALUE__) == EXTI_TRIGGER_RISING)     \
                                                   || ((__VALUE__) == EXTI_TRIGGER_FALLING)    \
                                                   || ((__VALUE__) == EXTI_TRIGGER_RISING_FALLING))

/**
  * @brief  Enable ExtiLine Interrupt request for Lines in range 0 to 31
  * @note The reset value for the direct or internal lines (see RM)
  *       is set to 1 in order to enable the interrupt by default.
  *       Bits are set automatically at Power on.
  * @rmtoll EXTI_Enable_IT
  * @param  ExtiLine This parameter can be one of the following values:
  *         @arg @ref EXTI_LINE_0    
  *         @arg @ref EXTI_LINE_1    
  *         @arg @ref EXTI_LINE_2    
  *         @arg @ref EXTI_LINE_3    
  *         @arg @ref EXTI_LINE_4    
  *         @arg @ref EXTI_LINE_5    
  *         @arg @ref EXTI_LINE_6    
  *         @arg @ref EXTI_LINE_7    
  *         @arg @ref EXTI_LINE_16   
  *         @arg @ref EXTI_LINE_17   
  *         @arg @ref EXTI_LINE_21   
  *         @arg @ref EXTI_LINE_22   
  *         @arg @ref EXTI_LINE_A0_31
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval None
  */
__STATIC_INLINE void EXTI_Enable_IT(uint32_t ExtiLine)
{
  SET_BIT(EXTI->IMR, ExtiLine);
}

/**
  * @brief  Disable ExtiLine Interrupt request for Lines in range 0 to 31
  * @note The reset value for the direct or internal lines (see RM)
  *       is set to 1 in order to enable the interrupt by default.
  *       Bits are set automatically at Power on.
  * @rmtoll EXTI_Disable_IT
  * @param  ExtiLine This parameter can be one of the following values:
  *         @arg @ref EXTI_LINE_0    
  *         @arg @ref EXTI_LINE_1    
  *         @arg @ref EXTI_LINE_2    
  *         @arg @ref EXTI_LINE_3    
  *         @arg @ref EXTI_LINE_4    
  *         @arg @ref EXTI_LINE_5    
  *         @arg @ref EXTI_LINE_6    
  *         @arg @ref EXTI_LINE_7    
  *         @arg @ref EXTI_LINE_16   
  *         @arg @ref EXTI_LINE_17   
  *         @arg @ref EXTI_LINE_21   
  *         @arg @ref EXTI_LINE_22   
  *         @arg @ref EXTI_LINE_A0_31
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval None
  */
__STATIC_INLINE void EXTI_Disable_IT(uint32_t ExtiLine)
{
  CLEAR_BIT(EXTI->IMR, ExtiLine);
}

/**
  * @brief  Indicate if ExtiLine Interrupt request is enabled for Lines in range 0 to 31
  * @note The reset value for the direct or internal lines (see RM)
  *       is set to 1 in order to enable the interrupt by default.
  *       Bits are set automatically at Power on.
  * @rmtoll EXTI_Get_IT
  * @param  ExtiLine This parameter can be one of the following values:
  *         @arg @ref EXTI_LINE_0    
  *         @arg @ref EXTI_LINE_1    
  *         @arg @ref EXTI_LINE_2    
  *         @arg @ref EXTI_LINE_3    
  *         @arg @ref EXTI_LINE_4    
  *         @arg @ref EXTI_LINE_5    
  *         @arg @ref EXTI_LINE_6    
  *         @arg @ref EXTI_LINE_7    
  *         @arg @ref EXTI_LINE_16   
  *         @arg @ref EXTI_LINE_17   
  *         @arg @ref EXTI_LINE_21   
  *         @arg @ref EXTI_LINE_22   
  *         @arg @ref EXTI_LINE_A0_31
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t EXTI_Get_IT(uint32_t ExtiLine)
{
  return (READ_BIT(EXTI->IMR, ExtiLine) == (ExtiLine));
}

/**
  * @brief  Enable ExtiLine Event request for Lines in range 0 to 31
  * @rmtoll EXTI_Enable_Event
  * @param  ExtiLine This parameter can be one of the following values:
  *         @arg @ref EXTI_LINE_0    
  *         @arg @ref EXTI_LINE_1    
  *         @arg @ref EXTI_LINE_2    
  *         @arg @ref EXTI_LINE_3    
  *         @arg @ref EXTI_LINE_4    
  *         @arg @ref EXTI_LINE_5    
  *         @arg @ref EXTI_LINE_6    
  *         @arg @ref EXTI_LINE_7    
  *         @arg @ref EXTI_LINE_16   
  *         @arg @ref EXTI_LINE_17   
  *         @arg @ref EXTI_LINE_21   
  *         @arg @ref EXTI_LINE_22   
  *         @arg @ref EXTI_LINE_A0_31
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval None
  */
__STATIC_INLINE void EXTI_Enable_Event(uint32_t ExtiLine)
{
  SET_BIT(EXTI->EMR, ExtiLine);
}

/**
  * @brief  Disable ExtiLine Event request for Lines in range 0 to 31
  * @rmtoll EXTI_Disable_Event
  * @param  ExtiLine This parameter can be one of the following values:
  *         @arg @ref EXTI_LINE_0    
  *         @arg @ref EXTI_LINE_1    
  *         @arg @ref EXTI_LINE_2    
  *         @arg @ref EXTI_LINE_3    
  *         @arg @ref EXTI_LINE_4    
  *         @arg @ref EXTI_LINE_5    
  *         @arg @ref EXTI_LINE_6    
  *         @arg @ref EXTI_LINE_7    
  *         @arg @ref EXTI_LINE_16   
  *         @arg @ref EXTI_LINE_17   
  *         @arg @ref EXTI_LINE_21   
  *         @arg @ref EXTI_LINE_22   
  *         @arg @ref EXTI_LINE_A0_31
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval None
  */
__STATIC_INLINE void EXTI_Disable_Event(uint32_t ExtiLine)
{
  CLEAR_BIT(EXTI->EMR, ExtiLine);
}

/**
  * @brief  Indicate if ExtiLine Event request is enabled for Lines in range 0 to 31
  * @rmtoll EXTI_Get_Event
  * @param  ExtiLine This parameter can be one of the following values:
  *         @arg @ref EXTI_LINE_0    
  *         @arg @ref EXTI_LINE_1    
  *         @arg @ref EXTI_LINE_2    
  *         @arg @ref EXTI_LINE_3    
  *         @arg @ref EXTI_LINE_4    
  *         @arg @ref EXTI_LINE_5    
  *         @arg @ref EXTI_LINE_6    
  *         @arg @ref EXTI_LINE_7    
  *         @arg @ref EXTI_LINE_16   
  *         @arg @ref EXTI_LINE_17   
  *         @arg @ref EXTI_LINE_21   
  *         @arg @ref EXTI_LINE_22   
  *         @arg @ref EXTI_LINE_A0_31
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t EXTI_Get_Event(uint32_t ExtiLine)
{
  return (READ_BIT(EXTI->EMR, ExtiLine) == (ExtiLine));
}

/**
  * @brief  Enable ExtiLine Rising Edge Trigger for Lines in range 0 to 31
  * @note The configurable wakeup lines are edge-triggered. No glitch must be
  *       generated on these lines. If a rising edge on a configurable interrupt
  *       line occurs during a write operation in the EXTI_RTSR register, the
  *       pending bit is not set.
  *       Rising and falling edge triggers can be set for
  *       the same interrupt line. In this case, both generate a trigger
  *       condition.
  * @rmtoll EXTI_Enable_RisingTrig
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref EXTI_LINE_0    
  *         @arg @ref EXTI_LINE_1    
  *         @arg @ref EXTI_LINE_2    
  *         @arg @ref EXTI_LINE_3    
  *         @arg @ref EXTI_LINE_4    
  *         @arg @ref EXTI_LINE_5    
  *         @arg @ref EXTI_LINE_6    
  *         @arg @ref EXTI_LINE_7    
  *         @arg @ref EXTI_LINE_16   
  *         @arg @ref EXTI_LINE_17   
  *         @arg @ref EXTI_LINE_21   
  *         @arg @ref EXTI_LINE_22   
  *         @arg @ref EXTI_LINE_A0_31
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval None
  */
__STATIC_INLINE void EXTI_Enable_RisingTrig(uint32_t ExtiLine)
{
  SET_BIT(EXTI->RTSR, ExtiLine);
}

/**
  * @brief  Disable ExtiLine Rising Edge Trigger for Lines in range 0 to 31
  * @note The configurable wakeup lines are edge-triggered. No glitch must be
  *       generated on these lines. If a rising edge on a configurable interrupt
  *       line occurs during a write operation in the EXTI_RTSR register, the
  *       pending bit is not set.
  *       Rising and falling edge triggers can be set for
  *       the same interrupt line. In this case, both generate a trigger
  *       condition.
  * @rmtoll EXTI_Disable_RisingTrig
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref EXTI_LINE_0    
  *         @arg @ref EXTI_LINE_1    
  *         @arg @ref EXTI_LINE_2    
  *         @arg @ref EXTI_LINE_3    
  *         @arg @ref EXTI_LINE_4    
  *         @arg @ref EXTI_LINE_5    
  *         @arg @ref EXTI_LINE_6    
  *         @arg @ref EXTI_LINE_7    
  *         @arg @ref EXTI_LINE_16   
  *         @arg @ref EXTI_LINE_17   
  *         @arg @ref EXTI_LINE_21   
  *         @arg @ref EXTI_LINE_22   
  *         @arg @ref EXTI_LINE_A0_31
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval None
  */
__STATIC_INLINE void EXTI_Disable_RisingTrig(uint32_t ExtiLine)
{
  CLEAR_BIT(EXTI->RTSR, ExtiLine);
}

/**
  * @brief  Check if rising edge trigger is enabled for Lines in range 0 to 31
  * @rmtoll EXTI_Get_RisingTrig
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref EXTI_LINE_0    
  *         @arg @ref EXTI_LINE_1    
  *         @arg @ref EXTI_LINE_2    
  *         @arg @ref EXTI_LINE_3    
  *         @arg @ref EXTI_LINE_4    
  *         @arg @ref EXTI_LINE_5    
  *         @arg @ref EXTI_LINE_6    
  *         @arg @ref EXTI_LINE_7    
  *         @arg @ref EXTI_LINE_16   
  *         @arg @ref EXTI_LINE_17   
  *         @arg @ref EXTI_LINE_21   
  *         @arg @ref EXTI_LINE_22   
  *         @arg @ref EXTI_LINE_A0_31
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t EXTI_Get_RisingTrig(uint32_t ExtiLine)
{
  return (READ_BIT(EXTI->RTSR, ExtiLine) == (ExtiLine));
}

/**
  * @brief  Enable ExtiLine Falling Edge Trigger for Lines in range 0 to 31
  * @note The configurable wakeup lines are edge-triggered. No glitch must be
  *       generated on these lines. If a falling edge on a configurable interrupt
  *       line occurs during a write operation in the EXTI_FTSR register, the
  *       pending bit is not set.
  *       Rising and falling edge triggers can be set for
  *       the same interrupt line. In this case, both generate a trigger
  *       condition.
  * @rmtoll EXTI_Enable_FallingTrig
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref EXTI_LINE_0    
  *         @arg @ref EXTI_LINE_1    
  *         @arg @ref EXTI_LINE_2    
  *         @arg @ref EXTI_LINE_3    
  *         @arg @ref EXTI_LINE_4    
  *         @arg @ref EXTI_LINE_5    
  *         @arg @ref EXTI_LINE_6    
  *         @arg @ref EXTI_LINE_7    
  *         @arg @ref EXTI_LINE_16   
  *         @arg @ref EXTI_LINE_17   
  *         @arg @ref EXTI_LINE_21   
  *         @arg @ref EXTI_LINE_22   
  *         @arg @ref EXTI_LINE_A0_31
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval None
  */
__STATIC_INLINE void EXTI_Enable_FallingTrig(uint32_t ExtiLine)
{
  SET_BIT(EXTI->FTSR, ExtiLine);
}

/**
  * @brief  Disable ExtiLine Falling Edge Trigger for Lines in range 0 to 31
  * @note The configurable wakeup lines are edge-triggered. No glitch must be
  *       generated on these lines. If a Falling edge on a configurable interrupt
  *       line occurs during a write operation in the EXTI_FTSR register, the
  *       pending bit is not set.
  *       Rising and falling edge triggers can be set for the same interrupt line.
  *       In this case, both generate a trigger condition.
  * @rmtoll EXTI_Disable_FallingTrig
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref EXTI_LINE_0    
  *         @arg @ref EXTI_LINE_1    
  *         @arg @ref EXTI_LINE_2    
  *         @arg @ref EXTI_LINE_3    
  *         @arg @ref EXTI_LINE_4    
  *         @arg @ref EXTI_LINE_5    
  *         @arg @ref EXTI_LINE_6    
  *         @arg @ref EXTI_LINE_7    
  *         @arg @ref EXTI_LINE_16   
  *         @arg @ref EXTI_LINE_17   
  *         @arg @ref EXTI_LINE_21   
  *         @arg @ref EXTI_LINE_22   
  *         @arg @ref EXTI_LINE_A0_31
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval None
  */
__STATIC_INLINE void EXTI_Disable_FallingTrig(uint32_t ExtiLine)
{
  CLEAR_BIT(EXTI->FTSR, ExtiLine);
}

/**
  * @brief  Check if falling edge trigger is enabled for Lines in range 0 to 31
  * @rmtoll EXTI_Get_FallingTrig
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref EXTI_LINE_0    
  *         @arg @ref EXTI_LINE_1    
  *         @arg @ref EXTI_LINE_2    
  *         @arg @ref EXTI_LINE_3    
  *         @arg @ref EXTI_LINE_4    
  *         @arg @ref EXTI_LINE_5    
  *         @arg @ref EXTI_LINE_6    
  *         @arg @ref EXTI_LINE_7    
  *         @arg @ref EXTI_LINE_16   
  *         @arg @ref EXTI_LINE_17   
  *         @arg @ref EXTI_LINE_21   
  *         @arg @ref EXTI_LINE_22   
  *         @arg @ref EXTI_LINE_A0_31
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t EXTI_Get_FallingTrig(uint32_t ExtiLine)
{
  return (READ_BIT(EXTI->FTSR, ExtiLine) == (ExtiLine));
}

/**
  * @brief  Generate a software Interrupt Event for Lines in range 0 to 31
  * @note If the interrupt is enabled on this line in the EXTI_IMR, writing a 1 to
  *       this bit when it is at '0' sets the corresponding pending bit in EXTI_PR
  *       resulting in an interrupt request generation.
  *       This bit is cleared by clearing the corresponding bit in the EXTI_PR
  *       register (by writing a 1 into the bit)
  * @rmtoll EXTI_Generate_SWI
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref EXTI_LINE_0    
  *         @arg @ref EXTI_LINE_1    
  *         @arg @ref EXTI_LINE_2    
  *         @arg @ref EXTI_LINE_3    
  *         @arg @ref EXTI_LINE_4    
  *         @arg @ref EXTI_LINE_5    
  *         @arg @ref EXTI_LINE_6    
  *         @arg @ref EXTI_LINE_7    
  *         @arg @ref EXTI_LINE_16   
  *         @arg @ref EXTI_LINE_17   
  *         @arg @ref EXTI_LINE_21   
  *         @arg @ref EXTI_LINE_22   
  *         @arg @ref EXTI_LINE_A0_31
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval None
  */
__STATIC_INLINE void EXTI_Generate_SWI(uint32_t ExtiLine)
{
  SET_BIT(EXTI->SWIER, ExtiLine);
}

/**
  * @brief  Check if the ExtLine Flag is set or not for Lines in range 0 to 31
  * @note This bit is set when the selected edge event arrives on the interrupt
  *       line. This bit is cleared by writing a 1 to the bit.
  * @rmtoll EXTI_Get_Flag
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref EXTI_LINE_0    
  *         @arg @ref EXTI_LINE_1    
  *         @arg @ref EXTI_LINE_2    
  *         @arg @ref EXTI_LINE_3    
  *         @arg @ref EXTI_LINE_4    
  *         @arg @ref EXTI_LINE_5    
  *         @arg @ref EXTI_LINE_6    
  *         @arg @ref EXTI_LINE_7    
  *         @arg @ref EXTI_LINE_16   
  *         @arg @ref EXTI_LINE_17   
  *         @arg @ref EXTI_LINE_21   
  *         @arg @ref EXTI_LINE_22   
  *         @arg @ref EXTI_LINE_A0_31
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t EXTI_Get_Flag(uint32_t ExtiLine)
{
  return (READ_BIT(EXTI->PR, ExtiLine) == (ExtiLine));
}

/**
  * @brief  Read ExtLine Combination Flag for Lines in range 0 to 31
  * @note This bit is set when the selected edge event arrives on the interrupt
  *       line. This bit is cleared by writing a 1 to the bit.
  * @rmtoll EXTI_Read_Flag
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref EXTI_LINE_0    
  *         @arg @ref EXTI_LINE_1    
  *         @arg @ref EXTI_LINE_2    
  *         @arg @ref EXTI_LINE_3    
  *         @arg @ref EXTI_LINE_4    
  *         @arg @ref EXTI_LINE_5    
  *         @arg @ref EXTI_LINE_6    
  *         @arg @ref EXTI_LINE_7    
  *         @arg @ref EXTI_LINE_16   
  *         @arg @ref EXTI_LINE_17   
  *         @arg @ref EXTI_LINE_21   
  *         @arg @ref EXTI_LINE_22   
  *         @arg @ref EXTI_LINE_A0_31
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval @note This bit is set when the selected edge event arrives on the interrupt
  */
__STATIC_INLINE uint32_t EXTI_Read_Flag(uint32_t ExtiLine)
{
  return (uint32_t)(READ_BIT(EXTI->PR, ExtiLine));
}

/**
  * @brief  Clear ExtLine Flags  for Lines in range 0 to 31
  * @note This bit is set when the selected edge event arrives on the interrupt
  *       line. This bit is cleared by writing a 1 to the bit.
  * @rmtoll EXTI_Clear_Flag
  * @param  ExtiLine This parameter can be a combination of the following values:
  *         @arg @ref EXTI_LINE_0    
  *         @arg @ref EXTI_LINE_1    
  *         @arg @ref EXTI_LINE_2    
  *         @arg @ref EXTI_LINE_3    
  *         @arg @ref EXTI_LINE_4    
  *         @arg @ref EXTI_LINE_5    
  *         @arg @ref EXTI_LINE_6    
  *         @arg @ref EXTI_LINE_7    
  *         @arg @ref EXTI_LINE_16   
  *         @arg @ref EXTI_LINE_17   
  *         @arg @ref EXTI_LINE_21   
  *         @arg @ref EXTI_LINE_22   
  *         @arg @ref EXTI_LINE_A0_31
  * @note   Please check each device line mapping for EXTI Line availability
  * @retval None
  */
__STATIC_INLINE void EXTI_Clear_Flag(uint32_t ExtiLine)
{
  WRITE_REG(EXTI->PR, ExtiLine);
}

void EXTI_DeInit(void);
void EXTI_StructInit(EXTI_InitTypeDef *EXTI_InitStruct);
void EXTI_Init(EXTI_InitTypeDef *EXTI_InitStruct);

#endif /* EXTI */

#ifdef __cplusplus
}
#endif

#endif /* __rx32h6xx_EXTI_H__ */

