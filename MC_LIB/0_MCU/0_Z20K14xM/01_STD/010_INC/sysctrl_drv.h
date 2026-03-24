/**************************************************************************************************/
/**
 * @file     sysctrl_drv.h
 * @brief    SYSCTRL driver module header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#ifndef SYSCTRL_DRV_H
#define SYSCTRL_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SYSCTRL
 *  @{
 */

/** @defgroup SYSCTRL_Public_Types 
 *  @{
 */



/**
 *  @brief SYSCTRL module type definition
 */
typedef enum
{
    SYSCTRL_WDOG = 0U,                 /*!< WDOG */
    SYSCTRL_EWDT = 0x04U,              /*!< EWDT */
    SYSCTRL_STIM = 0x08U,              /*!< STIM */
    SYSCTRL_TIM0 = 0x0CU,              /*!< TIM0 */
    SYSCTRL_TIM1 = 0x10U,              /*!< TIM1 */
    SYSCTRL_TIM2 = 0x14U,              /*!< TIM2 */
    SYSCTRL_TIM3 = 0x18U,              /*!< TIM3 */
    SYSCTRL_MCPWM0 = 0x1CU,            /*!< MCPWM0 */
    SYSCTRL_MCPWM1 = 0x20U,            /*!< MCPWM1 */
    SYSCTRL_TDG0 = 0x24U,              /*!< TDG0 */
    SYSCTRL_TDG1 = 0x28U,              /*!< TDG1 */
    SYSCTRL_CAN0 = 0x2CU,              /*!< CAN0 */
    SYSCTRL_CAN1 = 0x30U,              /*!< CAN1 */
    SYSCTRL_CAN2 = 0x34U,              /*!< CAN2 */
    SYSCTRL_CAN3 = 0x38U,              /*!< CAN3 */
    SYSCTRL_CAN4 = 0x3CU,              /*!< CAN4 */
    SYSCTRL_CAN5 = 0x40U,              /*!< CAN5 */
    SYSCTRL_CAN6 = 0x44U,              /*!< CAN6 */
    SYSCTRL_CAN7 = 0x48U,              /*!< CAN7 */
    SYSCTRL_UART0 = 0x4CU,             /*!< UART0 */
    SYSCTRL_UART1 = 0x50U,             /*!< UART1 */
    SYSCTRL_UART2 = 0x54U,             /*!< UART2 */
    SYSCTRL_UART3 = 0x58U,             /*!< UART3 */
    SYSCTRL_UART4 = 0x5CU,             /*!< UART4 */
    SYSCTRL_UART5 = 0x60U,             /*!< UART5 */
    SYSCTRL_SPI0 = 0x64U,              /*!< SPI0 */
    SYSCTRL_SPI1 = 0x68U,              /*!< SPI1 */
    SYSCTRL_SPI2 = 0x6cU,              /*!< SPI2 */
    SYSCTRL_SPI3 = 0x70U,              /*!< SPI3 */
    SYSCTRL_I2C0 = 0x74U,              /*!< I2C0 */    
    SYSCTRL_I2C1 = 0x78U,              /*!< I2C1 */ 
    SYSCTRL_I2S0 = 0x7CU,              /*!< I2S0 */
    SYSCTRL_I2S1 = 0x80U,              /*!< I2S1 */
    SYSCTRL_RSVDOx84 = 0x84U,          /*!< RESERVED */
    SYSCTRL_ADC0 = 0x88U,              /*!< ADC0 */
    SYSCTRL_ADC1 = 0x8CU,              /*!< ADC1 */
    SYSCTRL_CMP = 0x90U,               /*!< CMP */
    SYSCTRL_CRC = 0x94U,               /*!< CRC */
    SYSCTRL_AES = 0x98U,               /*!< AES */
    SYSCTRL_TRNG = 0x9CU,              /*!< TRNG */
    SYSCTRL_FLASH = 0xA0U,             /*!< FLASH */
    SYSCTRL_RSVDOxA4 = 0xA4U,          /*!< RESERVED */
    SYSCTRL_DMA = 0xA8U,               /*!< DMA */
    SYSCTRL_DMAMUX = 0xACU,            /*!< DMAMUX */
    SYSCTRL_PORTA = 0xB0U,             /*!< PORTA */
    SYSCTRL_PORTB = 0xB4U,             /*!< PORTB */
    SYSCTRL_PORTC = 0xB8U,             /*!< PORTC */
    SYSCTRL_PORTD = 0xBCU,             /*!< PORTD */
    SYSCTRL_PORTE = 0xC0U,             /*!< PORTE */
    SYSCTRL_TMU = 0xC4U,               /*!< TMU */
    SYSCTRL_REGFILE = 0xC8U,           /*!< REGFILE */
    SYSCTRL_SMPU = 0xCCU,              /*!< SMPU */
    SYSCTRL_GPIO = 0xD0U,              /*!< GPIO */
}SYSCTRL_Module_t; 

/** @} end of group SYSCTRL_Public_Types */

/** @defgroup SYSCTRL_Public_Constants
 *  @{
 */

/** @} end of group SYSCTRL_Public_Constants */

/** @defgroup SYSCTRL_Public_Macro
 *  @{
 */

/** @} end of group SYSCTRL_Public_Macro */

/** @defgroup SYSCTRL_Public_FunctionDeclaration
 *  @brief SYSCTRL functions declaration
 *  @{
 */

/**
 * @brief      reset module
 *
 * @param[in]  module: select which module to reset. 
 *
 * @return     none
 *
 */
void SYSCTRL_ResetModule(SYSCTRL_Module_t mod);

/**
 * @brief      Enable module. The module is enabled in normal/wait/stop modes.
 *
 * @param[in]  module: select which module to enable. 
 *
 * @return     none
 *
 */
void SYSCTRL_EnableModule(SYSCTRL_Module_t mod);

/**
 * @brief      Enable module but the module is off in stop mode.
 *
 * @param[in]  module: select which module to enable. 
 *
 * @return     none
 *
 */
void SYSCTRL_EnableModuleWithOffInStopMode(SYSCTRL_Module_t mod);

/**
 * @brief      Disable module
 *
 * @param[in]  module: select which module to disable. 
 *
 * @return     none
 *
 */
void SYSCTRL_DisableModule(SYSCTRL_Module_t mod);

/**
 * @brief      Config the module write access limits
 *
 * @param[in]  module: select which module to config 
 * @param[in]  writeLock: write lock
 *                        - ENABLE: Peripheral register write is denied 
 *                        - DISABLE:  Peripheral register write is allowed
 * @param[in]  supervisorEn: supervisor enable
 *                        - ENABLE: Peripheral register write is allowed in 
 *                                  supervisor mode,but denied in user mode 
 *                        - DISABLE:  Peripheral register write is allowed in 
 *                                   both supervisor and user mode
 *
 * @return     none
 *
 */
void SYSCTRL_ModuleWriteControl(SYSCTRL_Module_t mod, ControlState_t writeLock,
                                ControlState_t supervisorEn);

/** @} end of group SYSCTRL_Public_FunctionDeclaration */

/** @} end of group SYSCTRL  */

/** @} end of group Z20K14XM_Peripheral_Driver */
#endif /* SYSCTRL_DRV_H */
