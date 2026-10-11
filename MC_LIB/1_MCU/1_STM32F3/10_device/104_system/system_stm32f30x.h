/**
  ******************************************************************************
  * @file    system_stm32f30x.h
  * @author  MCD Application Team
  * @version V1.2.4
  * @date    15-December-2021
  * @brief   CMSIS Cortex-M4 Device System Source File for STM32F30x devices.  
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32f30x_system
  * @{
  */  
  
/**
  * @brief Define to prevent recursive inclusion
  */
#ifndef __SYSTEM_STM32F30X_H
#define __SYSTEM_STM32F30X_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Exported types ------------------------------------------------------------*/
extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/** @addtogroup STM32F30x_System_Exported_Functions
  * @{
  */
  
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_STM32F30X_H */

/**
  * @}
  */
  
/**
  * @}
  */  
