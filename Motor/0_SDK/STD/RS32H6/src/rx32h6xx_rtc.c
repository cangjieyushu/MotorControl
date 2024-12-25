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
* File         : rx32h6xx_rtc.c
* By           : RX_SD_Team
* Version      : V1.0.0
* Description  : Only rx32h6xx
*********************************************************************************************************
*/

#include "rx32h6xx_rtc.h"


/**
  * @brief  De-Initializes the RTC registers to their default reset values.
  * @note   This function doesn't reset the RTC Clock source and RTC Backup Data
  *         registers.
  * @param  RTCx RTC Instance
  * @retval None.
  */
void RTC_DeInit(RTC_TypeDef *RTCx)
{
  /* Disable the write protection for RTC registers */
  RTC_Disable_WriteProtection(RTCx);

  /* Set Initialization mode */
  if (RTC_Enter_InitMode(RTCx) != 1)
  {
    RTCx->CNTL = 0x0000;
    RTCx->CNTH = 0x0000;
    RTCx->PRLH = 0x0000;
    RTCx->PRLL = 0x8000;
    RTCx->CRH = 0x0000;
    RTCx->CRL = 0x0020;

    /* Exit Initialization Mode */
    if (RTC_Exit_InitMode(RTCx) != 1)
    {
      /* Wait till the RTC RSF flag is set */
      RTC_Wait_Synchro();
  
      /* Clear RSF Flag */
      RTC_Clear_Flag(RTC_FLAG_RSF);
      
      /* Enable the write protection for RTC registers */
      RTC_Enable_WriteProtection(RTCx);
    }
  }
  else
  {
    /* Enable the write protection for RTC registers */
    RTC_Enable_WriteProtection(RTCx);
  }
}

/**
  * @brief  Set each @ref RTC_InitTypeDef field to default value.
  * @param  RTC_InitStruct pointer to a @ref RTC_InitTypeDef structure which will be initialized.
  * @retval None
  */
void RTC_StructInit(RTC_InitTypeDef *RTC_InitStruct)
{
  /* Set RTC_InitStruct fields to default values */
  RTC_InitStruct->AsynchPrescaler = RTC_ASYNCH_PRESC_DEFAULT;
}

/**
  * @brief  Set each @ref RTC_TimeTypeDef field to default value (Time = 00h:00min:00sec).
  * @param  RTC_TimeStruct pointer to a @ref RTC_TimeTypeDef structure which will be initialized.
  * @retval None
  */
void RTC_TIME_StructInit(RTC_TimeTypeDef *RTC_TimeStruct)
{
  /* Time = 00h:00min:00sec */
  RTC_TimeStruct->Hours      = 0U;
  RTC_TimeStruct->Minutes    = 0U;
  RTC_TimeStruct->Seconds    = 0U;
}

/**
  * @brief  Set each @ref RTC_AlarmTypeDef of ALARM field to default value (Time = 00h:00mn:00sec /
  *         Day = 1st day of the month/Mask = all fields are masked).
  * @param  RTC_AlarmStruct pointer to a @ref RTC_AlarmTypeDef structure which will be initialized.
  * @retval None
  */
void RTC_ALARM_StructInit(RTC_AlarmTypeDef *RTC_AlarmStruct)
{
  /* Alarm Time Settings : Time = 00h:00mn:00sec */
  RTC_AlarmStruct->AlarmTime.Hours      = 0U;
  RTC_AlarmStruct->AlarmTime.Minutes    = 0U;
  RTC_AlarmStruct->AlarmTime.Seconds    = 0U;
}

/**
  * @brief  Initializes the RTC registers according to the specified parameters
  *         in RTC_InitStruct.
  * @param  RTCx RTC Instance
  * @param  AsynchPrescaler Value between Min_Data = 0 and Max_Data = 0xFFFFF
  * @param  OutputSource This parameter can be one of the following values:
  *         @arg @ref BKP_RTCOutputSource_None      
  *         @arg @ref BKP_RTCOutputSource_CalibClock
  *         @arg @ref BKP_RTCOutputSource_Alarm     
  *         @arg @ref BKP_RTCOutputSource_Second  
  * @note   The RTC Prescaler register is write protected and can be written in
  *         initialization mode only.
  * @note   the user should call RTC_StructInit()  or the structure of Prescaler
  *         need to be initialized  before RTC init()
  * @retval None.
  */
void RTC_Initial(RTC_TypeDef *RTCx, RTC_InitTypeDef *RTC_InitStruct)
{
  /* Waiting for synchro */
  RTC_Wait_Synchro();
  
  /* Set Initialization mode */
  if (RTC_Enter_InitMode(RTCx) != 1)
  {
    /* Clear Flag Bits */
    RTC_Clear_Flag(RTC_FLAG_ALR);
    RTC_Clear_Flag(RTC_FLAG_OW);
    RTC_Clear_Flag(RTC_FLAG_SEC);

    /* Configure Synchronous and Asynchronous prescaler factor */
    RTC_Set_AsynchPrescaler(RTCx, RTC_InitStruct->AsynchPrescaler);

    /* Exit Initialization Mode */
    RTC_Exit_InitMode(RTCx);
  }
}

/**
  * @brief  Set the RTC current time.
  * @param  RTCx RTC Instance
  * @param  RTC_Format This parameter can be one of the following values:
  *         @arg @ref RTC_FORMAT_BIN
  *         @arg @ref RTC_FORMAT_BCD
  * @param  Hours This parameter must be a number between Min_Data = 0 and Max_Data = 23 
  * @param  Minutes This parameter must be a number between Min_Data = 0 and Max_Data = 59
  * @param  Seconds This parameter must be a number between Min_Data = 0 and Max_Data = 59 
  * @param  RTC_TimeStruct pointer to a RTC_TimeTypeDef structure that contains
  *                        the time configuration information for the RTC.
  * @note  The user should call RTC_TIME_StructInit() or the structure
  *        of time need to be initialized  before time init()
  * @retval None.
  */
void RTC_TIME_Init(RTC_TypeDef *RTCx, RTC_TimeTypeDef *RTC_TimeStruct)
{
  uint32_t counter_time = 0U;

  /* Enter Initialization mode */
  if (RTC_Enter_InitMode(RTCx) != 1)
  {
    /* Check the input parameters format */
    if (RTC_TimeStruct->Format != RTC_FORMAT_BIN)
    {
      counter_time = (uint32_t)(((uint32_t)RTC_TimeStruct->Hours * 3600U) + \
                                ((uint32_t)RTC_TimeStruct->Minutes * 60U) + \
                                ((uint32_t)RTC_TimeStruct->Seconds));
      RTC_Set_TIME(RTCx, counter_time);
    }
    else
    {
      counter_time = (((uint32_t)(__RTC_CONVERT_BCD2BIN(RTC_TimeStruct->Hours)) * 3600U) + \
                      ((uint32_t)(__RTC_CONVERT_BCD2BIN(RTC_TimeStruct->Minutes)) * 60U) + \
                      ((uint32_t)(__RTC_CONVERT_BCD2BIN(RTC_TimeStruct->Seconds))));
      RTC_Set_TIME(RTCx, counter_time);
    }
  }
  /* Exit Initialization mode */
  RTC_Exit_InitMode(RTCx);
}

/**
  * @brief  Set the RTC Alarm.
  * @param  RTCx RTC Instance
  * @param  RTC_Format This parameter can be one of the following values:
  *         @arg @ref RTC_FORMAT_BIN
  *         @arg @ref RTC_FORMAT_BCD
  * @param  Hours This parameter must be a number between Min_Data = 0 and Max_Data = 23 
  * @param  Minutes This parameter must be a number between Min_Data = 0 and Max_Data = 59
  * @param  Seconds This parameter must be a number between Min_Data = 0 and Max_Data = 59 
  * @param  RTC_AlarmStruct pointer to a @ref RTC_AlarmTypeDef structure that
  *                         contains the alarm configuration parameters.
  * @note   the user should call RTC_ALARM_StructInit()  or the structure
  *         of Alarm need to be initialized  before Alarm init()
  * @retval None.
  */
void RTC_ALARM_Init(RTC_TypeDef *RTCx, RTC_AlarmTypeDef *RTC_AlarmStruct)
{
  uint32_t counter_alarm = 0U;

  /* Enter Initialization mode */
  if (RTC_Enter_InitMode(RTCx) != 1)
  {
    /* Check the input parameters format */
    if (RTC_AlarmStruct->AlarmTime.Format != RTC_FORMAT_BIN)
    {
      counter_alarm = (uint32_t)(((uint32_t)RTC_AlarmStruct->AlarmTime.Hours * 3600U) + \
                                 ((uint32_t)RTC_AlarmStruct->AlarmTime.Minutes * 60U) + \
                                 ((uint32_t)RTC_AlarmStruct->AlarmTime.Seconds));
      RTC_Set_ALARM(RTCx, counter_alarm);
    }
    else
    {
      counter_alarm = (((uint32_t)(__RTC_CONVERT_BCD2BIN(RTC_AlarmStruct->AlarmTime.Hours)) * 3600U) + \
                       ((uint32_t)(__RTC_CONVERT_BCD2BIN(RTC_AlarmStruct->AlarmTime.Minutes)) * 60U) + \
                       ((uint32_t)(__RTC_CONVERT_BCD2BIN(RTC_AlarmStruct->AlarmTime.Seconds))));
      RTC_Set_ALARM(RTCx, counter_alarm);
    }
  }
  /* Exit Initialization mode */
  RTC_Exit_InitMode(RTCx);
}

/**
  * @brief  Enters the RTC Initialization mode.
  * @param  RTCx RTC Instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: 0
  *          - ERROR: 1
  */
uint32_t RTC_Enter_InitMode(RTC_TypeDef *RTCx)
{
  __IO uint32_t timeout = RTC_INITMODE_TIMEOUT;
  uint32_t status = 0;
  uint32_t tmp = 0U;

  /* Wait till RTC is in INIT state and if Time out is reached exit */
  tmp = RTC_Get_Flag(RTC_FLAG_RTOFF);
  while ((timeout != 0U) && (tmp != 1U))
  {
    if ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == (SysTick_CTRL_COUNTFLAG_Msk))
    {
      timeout --;
    }
    tmp = RTC_Get_Flag(RTC_FLAG_RTOFF);
    if (timeout == 0U)
    {
      status = 1;
    }
  }

  /* Disable the write protection for RTC registers */
  RTC_Disable_WriteProtection(RTCx);

  return status;
}

/**
  * @brief  Exit the RTC Initialization mode.
  * @note   When the initialization sequence is complete, the calendar restarts
  *         counting after 4 RTCCLK cycles.
  * @param  RTCx RTC Instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: 0
  *          - ERROR: 1
  */
uint32_t RTC_Exit_InitMode(RTC_TypeDef *RTCx)
{
  __IO uint32_t timeout = RTC_INITMODE_TIMEOUT;
  uint32_t status = 0;
  uint32_t tmp = 0U;

  /* Disable initialization mode */
  RTC_Enable_WriteProtection(RTCx);

  /* Wait till RTC is in INIT state and if Time out is reached exit */
  tmp = RTC_Get_Flag(RTC_FLAG_RTOFF);
  while ((timeout != 0U) && (tmp != 1U))
  {
    if ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == (SysTick_CTRL_COUNTFLAG_Msk))
    {
      timeout --;
    }
    tmp = RTC_Get_Flag(RTC_FLAG_RTOFF);
    if (timeout == 0U)
    {
      status = 1;
    }
  }
  return status;
}

/**
  * @brief  Set the Time Counter
  * @param  RTCx RTC Instance
  * @param  TimeCounter this value can be from 0 to 0xFFFFFFFF
  * @retval None.
  */
void RTC_Set_TIMECounter(RTC_TypeDef *RTCx, uint32_t TimeCounter)
{
  /* Enter Initialization mode */
  if (RTC_Enter_InitMode(RTCx) != 1)
  {
    RTC_Set_TIME(RTCx, TimeCounter);
  }
  /* Exit Initialization mode */
  RTC_Exit_InitMode(RTCx);
}

/**
  * @brief  Set Alarm Counter.
  * @param  RTCx RTC Instance
  * @param  AlarmCounter this value can be from 0 to 0xFFFFFFFF
  * @retval None.
  */
void RTC_Set_ALARMCounter(RTC_TypeDef *RTCx, uint32_t AlarmCounter)
{
  /* Enter Initialization mode */
  if (RTC_Enter_InitMode(RTCx) != 1)
  {
    RTC_Set_ALARM(RTCx, AlarmCounter);
  }
  /* Exit Initialization mode */
  RTC_Exit_InitMode(RTCx);
}



