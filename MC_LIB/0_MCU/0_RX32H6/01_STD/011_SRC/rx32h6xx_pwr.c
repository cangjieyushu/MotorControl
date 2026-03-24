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
* File         : rx32h6xx_pwr.c
* By           : RX_SD_Team
* Version      : V1.0.0
* Description  : Only rx32h6xx
*********************************************************************************************************
*/

#include "rx32h6xx_pwr.h"
#include "rx32h6xx_gpio.h"
#include "rx32h6xx_rcc.h"
#include "rx32h6xx_cortex.h"

/**
  * @brief  Enter SLEEP_NOW Mode
  * @rmtoll PWR_Enter_SLEEP_NOW Mode
  * @retval None.
  */
void PWR_Enter_SLEEP_NOW_Mode(void)
{  
	LPM_DisableSleepOnExit();
  LPM_EnableSleep();
  __WFI();
}

/**
  * @brief  Enter SLEEP_ON_EXIT Mode
  * @rmtoll PWR_Enter_SLEEP_ON_EXIT Mode
  * @retval None.
  */
void PWR_Enter_SLEEP_ON_EXIT_Mode(void)
{  
	LPM_EnableSleepOnExit();
  LPM_EnableSleep();
  __WFI();
}

/**
  * @brief  Enter STOP Mode
  * @rmtoll PWR_Enter_STOP Mode
  * @retval None.
  */
void PWR_Enter_STOP_Mode(void)
{
  LPM_EnableDeepSleep();
  __WFI( );
}

/**
  * @brief  Enter STOP_LPR Mode
  * @rmtoll PWR_Enter_STOP_LPR Mode
  * @retval None.
  */
void PWR_Enter_STOP_LPREGUMode(void)
{
	PWR_Set_PowerMode(PWR_MODE_STOP_LPREGU);
  LPM_EnableDeepSleep();
  __WFI( );
}

/**
  * @brief  Enter STANDBY Mode
  * @rmtoll PWR_Enter_STANDBYMode
  * @retval None.
  */
void PWR_Enter_STANDBYMode(void)
{
  /* Request Wait For Interrupt */
	PWR_Disable_WakeUpPin(PWR_WAKEUP_PIN1);
  
  /* Clear all wake up Flag */
  PWR_Clear_Flag(PWR_SCR_CWUF1);
  
	
  /* Enable wakeup pin */
  PWR_Enable_WakeUpPin(PWR_WAKEUP_PIN1);
   
  /* As default User push-button state is high level, need to clear all wake up Flag again */  
  PWR_Clear_Flag(PWR_SCR_CWUF1);

  /* Set STANDBY mode when CPU enters deepsleep */
  PWR_Set_PowerMode(PWR_MODE_STANDBY);
   
  /* Set SLEEPDEEP bit of Cortex System Control Register */
  LPM_EnableDeepSleep();
  
  /* Request Wait For Interrupt */
  __WFI();
}







