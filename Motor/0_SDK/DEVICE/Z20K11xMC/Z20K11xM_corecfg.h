/**************************************************************************************************/
/**
 * @file      : Z20K11xM_corecfg.h
 * @brief     : Z20K11xM Device core config Header File.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (c) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved. 
 **************************************************************************************************/

#ifndef Z20K11XM_CORECFG_H
#define Z20K11XM_CORECFG_H

/** \mainpage Z20K11X Core configuration

*/

/** \defgroup Core_configuration Configuration of the Cortex-M0+ Processor and Core Peripherals

   @{
 */

/*PRQA S 0603,0602 ++*/
#define __CHECK_DEVICE_DEFINES         /*!< check device definition */
#define __CM0PLUS_REV     0x0000U      /*!< core version */
#define __VTOR_PRESENT    1U           /*!< VTOR present or not*/
#define __MPU_PRESENT     1U           /*!< MPU present or not*/
#define __NVIC_PRIO_BITS          2U   /*!< Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0U   /*!< Set to 1 if different SysTick Config is used*/
/*PRQA S 0603,0602 --*/

/** @} end of group Core_configuration Configuration of the Cortex-M0+ Processor and Core Peripherals */

#endif /* __Z20K11XM_CORECFG_H */

/******************* (C) COPYRIGHT 2020 Zhixin Semiconductor *****END OF FILE****/


