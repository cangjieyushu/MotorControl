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
* File         : rx32h6xx_rtc.h
* By           : RX_SD_Team
* Version      : V1.0.0
* Description  : Only rx32h6xx
*********************************************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __rx32h6xx_RTC_H
#define __rx32h6xx_RTC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "rx32h6xx.h"

/** @defgroup RTC_interrupts_define 
  * @{
  */

#define RTC_IT_OW            ((uint16_t)0x0004)  /*!< Overflow interrupt */
#define RTC_IT_ALR           ((uint16_t)0x0002)  /*!< Alarm interrupt */
#define RTC_IT_SEC           ((uint16_t)0x0001)  /*!< Second interrupt */
#define IS_RTC_IT(IT) ((((IT) & (uint16_t)0xFFF8) == 0x00) && ((IT) != 0x00))
#define IS_RTC_GET_IT(IT) (((IT) == RTC_IT_OW) || ((IT) == RTC_IT_ALR) || \
                           ((IT) == RTC_IT_SEC))
/**
  * @}
  */ 

/** @defgroup RTC_interrupts_flags 
  * @{
  */

#define RTC_FLAG_RTOFF       ((uint16_t)0x0020)  /*!< RTC Operation OFF flag */
#define RTC_FLAG_RSF         ((uint16_t)0x0008)  /*!< Registers Synchronized flag */
#define RTC_FLAG_OW          ((uint16_t)0x0004)  /*!< Overflow flag */
#define RTC_FLAG_ALR         ((uint16_t)0x0002)  /*!< Alarm flag */
#define RTC_FLAG_SEC         ((uint16_t)0x0001)  /*!< Second flag */
#define IS_RTC_CLEAR_FLAG(FLAG) ((((FLAG) & (uint16_t)0xFFF0) == 0x00) && ((FLAG) != 0x00))
#define IS_RTC_GET_FLAG(FLAG) (((FLAG) == RTC_FLAG_RTOFF) || ((FLAG) == RTC_FLAG_RSF) || \
                               ((FLAG) == RTC_FLAG_OW) || ((FLAG) == RTC_FLAG_ALR) || \
                               ((FLAG) == RTC_FLAG_SEC))
#define IS_RTC_PRESCALER(PRESCALER) ((PRESCALER) <= 0xFFFFF)


/******************************************************************************/
/*                                                                            */
/*                             Real-Time Clock                                */
/*                                                                            */
/******************************************************************************/

/*******************  Bit definition for RTC_CRH register  ********************/
#define  RTC_CRH_SECIE                       ((uint8_t)0x01)               /*!< Second Interrupt Enable */
#define  RTC_CRH_ALRIE                       ((uint8_t)0x02)               /*!< Alarm Interrupt Enable */
#define  RTC_CRH_OWIE                        ((uint8_t)0x04)               /*!< OverfloW Interrupt Enable */

/*******************  Bit definition for RTC_CRL register  ********************/
#define  RTC_CRL_SECF                        ((uint8_t)0x01)               /*!< Second Flag */
#define  RTC_CRL_ALRF                        ((uint8_t)0x02)               /*!< Alarm Flag */
#define  RTC_CRL_OWF                         ((uint8_t)0x04)               /*!< OverfloW Flag */
#define  RTC_CRL_RSF                         ((uint8_t)0x08)               /*!< Registers Synchronized Flag */
#define  RTC_CRL_CNF                         ((uint8_t)0x10)               /*!< Configuration Flag */
#define  RTC_CRL_RTOFF                       ((uint8_t)0x20)               /*!< RTC operation OFF */

/*******************  Bit definition for RTC_PRLH register  *******************/
#define  RTC_PRLH_PRL                        ((uint16_t)0x000F)            /*!< RTC Prescaler Reload Value High */

/*******************  Bit definition for RTC_PRLL register  *******************/
#define  RTC_PRLL_PRL                        ((uint16_t)0xFFFF)            /*!< RTC Prescaler Reload Value Low */

/*******************  Bit definition for RTC_DIVH register  *******************/
#define  RTC_DIVH_RTC_DIV                    ((uint16_t)0x000F)            /*!< RTC Clock Divider High */

/*******************  Bit definition for RTC_DIVL register  *******************/
#define  RTC_DIVL_RTC_DIV                    ((uint16_t)0xFFFF)            /*!< RTC Clock Divider Low */

/*******************  Bit definition for RTC_CNTH register  *******************/
#define  RTC_CNTH_RTC_CNT                    ((uint16_t)0xFFFF)            /*!< RTC Counter High */

/*******************  Bit definition for RTC_CNTL register  *******************/
#define  RTC_CNTL_RTC_CNT                    ((uint16_t)0xFFFF)            /*!< RTC Counter Low */

/*******************  Bit definition for RTC_ALRH register  *******************/
#define  RTC_ALRH_RTC_ALR                    ((uint16_t)0xFFFF)            /*!< RTC Alarm High */

/*******************  Bit definition for RTC_ALRL register  *******************/
#define  RTC_ALRL_RTC_ALR                    ((uint16_t)0xFFFF) 

#define RTC_LSB_MASK     ((uint32_t)0x0000FFFF)  /*!< RTC LSB Mask */
#define PRLH_MSB_MASK    ((uint32_t)0x000F0000)  /*!< RTC Prescaler MSB Mask */

/* Default values used for prescaler */
#define RTC_ASYNCH_PRESC_DEFAULT     0x00007FFFU

/** @defgroup RTC_EC_FORMAT FORMAT
  * @{
  */
#define RTC_FORMAT_BIN                  (0x000000000U) /*!< Binary data format */
#define RTC_FORMAT_BCD                  (0x000000001U) /*!< BCD data format */

/* Values used for timeout */
#define RTC_INITMODE_TIMEOUT         1000U /* 1s when tick set to 1ms */
#define RTC_SYNCHRO_TIMEOUT          1000U /* 1s when tick set to 1ms */


/**
  * @brief  Helper macro to convert a value from BCD format to 2 digit decimal format
  * @param  __VALUE__ BCD value to be converted
  * @retval Converted byte
  */
#define __RTC_CONVERT_BCD2BIN(__VALUE__) (uint8_t)(((uint8_t)((__VALUE__) & (uint8_t)0xF0U) >> (uint8_t)0x4U) * 10U + ((__VALUE__) & (uint8_t)0x0FU))



/**
  * @brief  RTC Init structures definition
  */
typedef struct
{
  uint32_t AsynchPrescaler; /*!< Specifies the RTC Asynchronous Predivider value.
                              This parameter must be a number between Min_Data = 0x00 and Max_Data = 0xFFFFF

                              This feature can be modified afterwards using unitary function
                              @ref RTC_Set_AsynchPrescaler(). */

  uint32_t OutPutSource;    /*!< Specifies which signal will be routed to the RTC Tamper pin.
                                 This parameter can be a value of @ref RTC_Output_Source

                              This feature can be modified afterwards using unitary function
                              @ref RTC_Set_OutputSource(). */

} RTC_InitTypeDef;

/**
  * @brief  RTC Time structure definition
  */
typedef struct
{
  uint32_t Format;
  uint8_t Hours;       /*!< Specifies the RTC Time Hours.
                            This parameter must be a number between Min_Data = 0 and Max_Data = 23 */

  uint8_t Minutes;     /*!< Specifies the RTC Time Minutes.
                            This parameter must be a number between Min_Data = 0 and Max_Data = 59 */

  uint8_t Seconds;     /*!< Specifies the RTC Time Seconds.
                            This parameter must be a number between Min_Data = 0 and Max_Data = 59 */
} RTC_TimeTypeDef;


/**
  * @brief  RTC Alarm structure definition
  */
typedef struct
{
  RTC_TimeTypeDef AlarmTime;  /*!< Specifies the RTC Alarm Time members. */

} RTC_AlarmTypeDef;


typedef struct 
{
	uint8_t hour;
	uint8_t min;
	uint8_t sec;			
	uint16_t w_year;
	uint8_t  w_month;
	uint8_t  w_date;
	uint8_t  week;		 
}_calendar_obj;		
extern _calendar_obj calendar;

/**
  * @brief  Set Asynchronous prescaler factor
  * @param  RTCx RTC Instance
  * @param  AsynchPrescaler Value between Min_Data = 0 and Max_Data = 0xFFFFF
  * @retval None
  */
__STATIC_INLINE void RTC_Set_AsynchPrescaler(RTC_TypeDef *RTCx, uint32_t AsynchPrescaler)
{
  MODIFY_REG(RTCx->PRLH, RTC_PRLH_PRL, (AsynchPrescaler >> 16));
  MODIFY_REG(RTCx->PRLL, RTC_PRLL_PRL, (AsynchPrescaler & RTC_PRLL_PRL));
}

/**
  * @brief  Get Asynchronous prescaler factor
  * @param  RTCx RTC Instance
  * @retval Value between Min_Data = 0 and Max_Data = 0xFFFFF
  */
__STATIC_INLINE uint32_t RTC_Get_Divider(RTC_TypeDef *RTCx)
{
  register uint16_t Highprescaler = 0, Lowprescaler = 0;
  Highprescaler = READ_REG(RTCx->DIVH & RTC_DIVH_RTC_DIV);
  Lowprescaler  = READ_REG(RTCx->DIVL & RTC_DIVL_RTC_DIV);

  return (((uint32_t) Highprescaler << 16U) | Lowprescaler);
}

/**
  * @brief  Enable the write protection for RTC registers.
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void RTC_Enable_WriteProtection(RTC_TypeDef *RTCx)
{
  CLEAR_BIT(RTCx->CRL, RTC_CRL_CNF);
}

/**
  * @brief  Disable the write protection for RTC registers.
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE void RTC_Disable_WriteProtection(RTC_TypeDef *RTCx)
{
  SET_BIT(RTCx->CRL, RTC_CRL_CNF);
}

/**
  * @brief  Set time counter in BCD format
  * @note   Bit is write-protected. @ref LL_RTC_DisableWriteProtection function should be called before.
  * @note   It can be written in initialization mode only (@ref RTC_EnterInitMode function)
  * @param  RTCx RTC Instance
  * @param  TimeCounter Value between Min_Data=0x00 and Max_Data=0xFFFFF
  * @retval None
  */
__STATIC_INLINE void RTC_Set_TIME(RTC_TypeDef *RTCx, uint32_t TimeCounter)
{
  /* Set RTC COUNTER MSB word */
  WRITE_REG(RTCx->CNTH, (TimeCounter >> 16U));
  /* Set RTC COUNTER LSB word */
  WRITE_REG(RTCx->CNTL, (TimeCounter & RTC_CNTL_RTC_CNT));
}

/**
  * @brief  Get time counter in BCD format
  * @param  RTCx RTC Instance
  * @retval Value between Min_Data = 0 and Max_Data = 0xFFFFF
  */
__STATIC_INLINE uint32_t RTC_Get_TIME(RTC_TypeDef *RTCx)
{
  register uint16_t high = 0, low = 0;

  high = READ_REG(RTCx->CNTH & RTC_CNTH_RTC_CNT);
  low  = READ_REG(RTCx->CNTL & RTC_CNTL_RTC_CNT);
  return ((uint32_t)(((uint32_t) high << 16U) | low));
}

/**
  * @brief  Set Alarm Counter
  * @note   Bit is write-protected. @ref RTC_DisableWriteProtection function should be called before.
  * @param  RTCx RTC Instance
  * @param  AlarmCounter Value between Min_Data=0x00 and Max_Data=0xFFFFF
  * @retval None
  */
__STATIC_INLINE void RTC_Set_ALARM(RTC_TypeDef *RTCx, uint32_t AlarmCounter)
{
  /* Set RTC COUNTER MSB word */
  WRITE_REG(RTCx->ALRH, (AlarmCounter >> 16));
  /* Set RTC COUNTER LSB word */
  WRITE_REG(RTCx->ALRL, (AlarmCounter & RTC_ALRL_RTC_ALR));
}

/**
  * @brief  Get Alarm Counter
  * @note   Bit is write-protected. @ref RTC_DisableWriteProtection function should be called before.
  * @param  RTCx RTC Instance
  * @retval None
  */
__STATIC_INLINE uint32_t RTC_Get_ALARM(RTC_TypeDef *RTCx)
{
  register uint16_t high = 0, low = 0;

  high  = READ_REG(RTCx->ALRH & RTC_ALRH_RTC_ALR);
  low   = READ_REG(RTCx->ALRL & RTC_ALRL_RTC_ALR);

  return (((uint32_t) high << 16U) | low);
}

/**
  * @brief  Enables the specified RTC interrupts.
  * @param  RTC_IT: specifies the RTC interrupts sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg RTC_IT_OW: Overflow interrupt
  *     @arg RTC_IT_ALR: Alarm interrupt
  *     @arg RTC_IT_SEC: Second interrupt
  * @retval None
  */
__STATIC_INLINE void RTC_Enable_IT(uint16_t RTC_IT)
{
  SET_BIT(RTC->CRH, RTC_IT);
}

/**
  * @brief  Disables the specified RTC interrupts.
  * @param  RTC_IT: specifies the RTC interrupts sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg RTC_IT_OW: Overflow interrupt
  *     @arg RTC_IT_ALR: Alarm interrupt
  *     @arg RTC_IT_SEC: Second interrupt
  * @retval None
  */
__STATIC_INLINE void RTC_Disable_IT(uint16_t RTC_IT)
{
  CLEAR_BIT(RTC->CRH, RTC_IT);
}


/**
  * @brief  Checks whether the specified RTC interrupt has occurred or not.
  * @param  RTC_IT: specifies the RTC interrupts sources to check.
  *   This parameter can be one of the following values:
  *     @arg RTC_IT_OW: Overflow interrupt
  *     @arg RTC_IT_ALR: Alarm interrupt
  *     @arg RTC_IT_SEC: Second interrupt
  * @retval The new state of the RTC_IT (SET or RESET).
  */
__STATIC_INLINE uint32_t RTC_Get_IT(uint16_t RTC_IT)
{
  return ((READ_BIT(RTC->CRH, RTC_IT) != 0) && (READ_BIT(RTC->CRL, RTC_IT) != 0));
}


/**
  * @brief  Gets the RTC counter value.
  * @param  None
  * @retval RTC counter value.
  */
__STATIC_INLINE uint32_t RTC_Get_Counter(void)
{
  return (((uint32_t)RTC->CNTH << 16 ) | RTC->CNTL) ;
}

/**
  * @brief  Sets the RTC counter value.
  * @param  CounterValue: RTC counter new value.
  * @retval None
  */
__STATIC_INLINE void RTC_Set_Counter(uint32_t CounterValue)
{ 
  RTC_Disable_WriteProtection(RTC);
  /* Set RTC COUNTER MSB word */
  RTC->CNTH = CounterValue >> 16;
  /* Set RTC COUNTER LSB word */
  RTC->CNTL = (CounterValue & RTC_LSB_MASK);
  RTC_Enable_WriteProtection(RTC);
}

/**
  * @brief  Sets the RTC prescaler value.
  * @param  PrescalerValue: RTC prescaler new value.
  * @retval None
  */
__STATIC_INLINE void RTC_Set_Prescaler(uint32_t PrescalerValue)
{ 
  RTC_Disable_WriteProtection(RTC);
  /* Set RTC PRESCALER MSB word */
  RTC->PRLH = (PrescalerValue & PRLH_MSB_MASK) >> 16;
  /* Set RTC PRESCALER LSB word */
  RTC->PRLL = (PrescalerValue & RTC_LSB_MASK);
  RTC_Enable_WriteProtection(RTC);
}

/**
  * @brief  Sets the RTC alarm value.
  * @param  AlarmValue: RTC alarm new value.
  * @retval None
  */
__STATIC_INLINE void RTC_Set_Alarm(uint32_t AlarmValue)
{  
  RTC_Disable_WriteProtection(RTC);
  /* Set the ALARM MSB word */
  RTC->ALRH = AlarmValue >> 16;
  /* Set the ALARM LSB word */
  RTC->ALRL = (AlarmValue & RTC_LSB_MASK);
  RTC_Enable_WriteProtection(RTC);
}

/**
  * @brief  Checks whether the specified RTC flag is set or not.
  * @param  RTC_FLAG: specifies the flag to check.
  *   This parameter can be one the following values:
  *     @arg RTC_FLAG_RTOFF: RTC Operation OFF flag
  *     @arg RTC_FLAG_RSF: Registers Synchronized flag
  *     @arg RTC_FLAG_OW: Overflow flag
  *     @arg RTC_FLAG_ALR: Alarm flag
  *     @arg RTC_FLAG_SEC: Second flag
  * @retval The new state of RTC_FLAG (SET or RESET).
  */
__STATIC_INLINE uint32_t RTC_Get_Flag(uint16_t RTC_FLAG)
{
  return (READ_BIT(RTC->CRL, RTC_FLAG) == RTC_FLAG);
}

/**
  * @brief  Clears the RTC's pending flags.
  * @param  RTC_FLAG: specifies the flag to clear.
  *   This parameter can be any combination of the following values:
  *     @arg RTC_FLAG_RSF: Registers Synchronized flag. This flag is cleared only after
  *                        an APB reset or an APB Clock stop.
  *     @arg RTC_FLAG_OW: Overflow flag
  *     @arg RTC_FLAG_ALR: Alarm flag
  *     @arg RTC_FLAG_SEC: Second flag
  * @retval None
  */
__STATIC_INLINE void RTC_Clear_Flag(uint16_t RTC_FLAG)
{
  /* Clear the corresponding RTC flag */
  CLEAR_BIT(RTC->CRL, RTC_FLAG);
}

/**
  * @brief  Clears the RTC's interrupt pending bits.
  * @param  RTC_IT: specifies the interrupt pending bit to clear.
  *   This parameter can be any combination of the following values:
  *     @arg RTC_IT_OW: Overflow interrupt
  *     @arg RTC_IT_ALR: Alarm interrupt
  *     @arg RTC_IT_SEC: Second interrupt
  * @retval None
  */
__STATIC_INLINE void RTC_Clear_ITPendingBit(uint16_t RTC_IT)
{
  /* Clear the corresponding RTC pending bit */
  CLEAR_BIT(RTC->CRL, RTC_IT);
}


/**
  * @brief  Waits until last write operation on RTC registers has finished.
  * @note   This function must be called before any write to RTC registers.
  * @param  None
  * @retval None
  */
__STATIC_INLINE void RTC_Wait_LastTask(void)
{
  /* Loop until RTOFF flag is set */
  while ((RTC->CRL & RTC_FLAG_RTOFF) == (uint16_t)RESET)
  {
  }
}

/**
  * @brief  Waits until the RTC registers (RTC_CNT, RTC_ALR and RTC_PRL)
  *   are synchronized with RTC APB clock.
  * @note   This function must be called before any read operation after an APB reset
  *   or an APB clock stop.
  * @param  None
  * @retval None
  */
__STATIC_INLINE void RTC_Wait_Synchro(void)
{
  /* Clear RSF flag */
  CLEAR_BIT(RTC->CRL, RTC_FLAG_RSF);
  /* Loop until RSF flag is set */
  while ((RTC->CRL & RTC_FLAG_RSF) == (uint16_t)RESET)
  {
  }
}

void RTC_DeInit(RTC_TypeDef *RTCx);
void RTC_Initial(RTC_TypeDef *RTCx, RTC_InitTypeDef *RTC_InitStruct);
void RTC_StructInit(RTC_InitTypeDef *RTC_InitStruct);
void RTC_TIME_Init(RTC_TypeDef *RTCx, RTC_TimeTypeDef *RTC_TimeStruct);
void RTC_TIME_StructInit(RTC_TimeTypeDef *RTC_TimeStruct);
void RTC_ALARM_Init(RTC_TypeDef *RTCx, RTC_AlarmTypeDef *RTC_AlarmStruct);
void RTC_ALARM_StructInit(RTC_AlarmTypeDef *RTC_AlarmStruct);
uint32_t RTC_Enter_InitMode(RTC_TypeDef *RTCx);
uint32_t RTC_Exit_InitMode(RTC_TypeDef *RTCx);
void RTC_Set_TIMECounter(RTC_TypeDef *RTCx, uint32_t TimeCounter);
void RTC_Set_ALARMCounter(RTC_TypeDef *RTCx, uint32_t AlarmCounter);

#ifdef __cplusplus
}
#endif

#endif 
