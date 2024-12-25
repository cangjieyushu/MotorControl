/**************************************************************************************************/
/**
 * @file     tmu_drv.h
 * @brief    TMU driver module header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#ifndef TMU_DRV_H
#define TMU_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  TMU
 *  @{
 */

/** @defgroup TMU_Public_Types 
 *  @{
 */

/**
 *  @brief TMU ID type definition
 */
typedef enum
{
    TMU_MODULE_OUT0            = 0U,        /*!< IO OUTPUT0  */
    TMU_MODULE_OUT1            = 1U,        /*!< IO OUTPUT1  */
    TMU_MODULE_OUT2            = 2U,        /*!< IO OUTPUT2  */
    TMU_MODULE_OUT3            = 3U,        /*!< IO OUTPUT3  */
    TMU_MODULE_OUT4            = 4U,        /*!< IO OUTPUT4  */
    TMU_MODULE_OUT5            = 5U,        /*!< IO OUTPUT5  */
    TMU_MODULE_OUT6            = 6U,        /*!< IO OUTPUT6  */
    TMU_MODULE_OUT7            = 7U,        /*!< IO OUTPUT7  */	
    TMU_MODULE_ADC0_OPT0       = 8U,        /*!< ADC0 hw trigger OPT0  */
    TMU_MODULE_ADC0_OPT1       = 9U,        /*!< ADC0 hw trigger OPT1  */
    TMU_MODULE_ADC0_OPT2       = 10U,       /*!< ADC0 hw trigger OPT2  */
    TMU_MODULE_ADC0_OPT3       = 11U,       /*!< ADC0 hw trigger OPT3  */
    TMU_MODULE_ADC1_OPT0       = 12U,       /*!< ADC1 hw trigger OPT0  */
    TMU_MODULE_ADC1_OPT1       = 13U,       /*!< ADC1 hw trigger OPT1  */
    TMU_MODULE_ADC1_OPT2       = 14U,       /*!< ADC1 hw trigger OPT2  */
    TMU_MODULE_ADC1_OPT3       = 15U,       /*!< ADC1 hw trigger OPT3  */
    TMU_MODULE_CMP_SAMPLE      = 16U,       /*!< CMP Sample  */
    TMU_MODULE_CMP_EXT_EN      = 17U,       /*!< CMP external enable  */
    TMU_MODULE_TDG0_TRIG_IN    = 18U,       /*!< TDG0 trig in */
    TMU_MODULE_TDG1_TRIG_IN    = 19U,       /*!< TDG1 trig in */
    TMU_MODULE_TIM0_FAULT0     = 20U,       /*!< Timer0 fault 0  */
    TMU_MODULE_TIM0_FAULT1     = 21U,       /*!< Timer0 fault 1  */
    TMU_MODULE_TIM1_FAULT0     = 22U,       /*!< Timer1 fault 0  */
    TMU_MODULE_TIM1_FAULT1     = 23U,       /*!< Timer1 fault 1  */
    TMU_MODULE_TIM2_FAULT0     = 24U,       /*!< Timer2 fault 0  */
    TMU_MODULE_TIM2_FAULT1     = 25U,       /*!< Timer2 fault 1  */
    TMU_MODULE_TIM3_FAULT0     = 26U,       /*!< Timer3 fault 0  */
    TMU_MODULE_TIM3_FAULT1     = 27U,       /*!< Timer3 fault 1  */
    TMU_MODULE_MCPWM0_FAULT0   = 28U,       /*!< MCPWM0 fault0 */
    TMU_MODULE_MCPWM0_FAULT1   = 29U,       /*!< MCPWM0 fault1 */
    TMU_MODULE_MCPWM0_FAULT2   = 30U,       /*!< MCPWM0 fault2 */
    TMU_MODULE_MCPWM0_FAULT3   = 31U,       /*!< MCPWM0 fault3 */
    TMU_MODULE_MCPWM1_FAULT0   = 32U,       /*!< MCPWM1 fault0 */
    TMU_MODULE_MCPWM1_FAULT1   = 33U,       /*!< MCPWM1 fault1 */
    TMU_MODULE_MCPWM1_FAULT2   = 34U,       /*!< MCPWM1 fault2 */
    TMU_MODULE_MCPWM1_FAULT3   = 35U,       /*!< MCPWM1 fault3 */
    TMU_MODULE_STIM_TRIG_IN0   = 36U,       /*!< STIM trigger input 0 */
    TMU_MODULE_STIM_TRIG_IN1   = 37U,       /*!< STIM trigger input 1  */
    TMU_MODULE_STIM_TRIG_IN2   = 38U,       /*!< STIM trigger input 2  */
    TMU_MODULE_STIM_TRIG_IN3   = 39U,       /*!< STIM trigger input 3  */
}TMU_Module_t;

/**
 *  @brief TMU Input Select type definition
 */
typedef enum
{
    TMU_SOURCE_DISABLED          = 0U,     /*!< VSS  */
    TMU_SOURCE_VDD               = 1U,     /*!< VDD  */
    TMU_SOURCE_IN0               = 2U,     /*!< TMU  IN0  */
    TMU_SOURCE_IN1               = 3U,     /*!< TMU  IN1  */
    TMU_SOURCE_IN2               = 4U,     /*!< TMU  IN2  */
    TMU_SOURCE_IN3               = 5U,     /*!< TMU  IN3  */
    TMU_SOURCE_IN4               = 6U,     /*!< TMU  IN4  */
    TMU_SOURCE_IN5               = 7U,     /*!< TMU  IN5  */
    TMU_SOURCE_IN6               = 8U,     /*!< TMU  IN6  */
    TMU_SOURCE_IN7               = 9U,     /*!< TMU  IN7  */
    TMU_SOURCE_IN8               = 10U,    /*!< TMU  IN8  */
    TMU_SOURCE_IN9               = 11U,    /*!< TMU  IN9 */
    TMU_SOURCE_IN10              = 12U,    /*!< TMU  IN10 */
    TMU_SOURCE_IN11              = 13U,    /*!< TMU  IN1 */
    TMU_SOURCE_RTC_1Hz           = 14U,    /*!< RTC_1HZ_MUX_OUT */
    TMU_SOURCE_RTC_ALARM         = 15U,    /*!< RTC  Alarm  */
    TMU_SOURCE_STIM_OUT0         = 16U,    /*!< stim_trig_out[0] */
    TMU_SOURCE_STIM_OUT1         = 17U,    /*!< stim_trig_out[1] */
    TMU_SOURCE_STIM_OUT2         = 18U,    /*!< stim_trig_out[2] */
    TMU_SOURCE_STIM_OUT3         = 19U,    /*!< stim_trig_out[3] */    
    TMU_SOURCE_TIM0_MATCH        = 20U,    /*!< Timer0 Match Trigger  */
    TMU_SOURCE_TIM0_INITIAL      = 21U,    /*!< Timer0 Initialization Trigger */
    TMU_SOURCE_TIM1_MATCH        = 22U,    /*!< Timer1 Match Trigger  */
    TMU_SOURCE_TIM1_INITIAL      = 23U,    /*!< Timer1 Initialization Trigger */
    TMU_SOURCE_TIM2_MATCH        = 24U,    /*!< Timer2 Match Trigger  */
    TMU_SOURCE_TIM2_INITIAL      = 25U,    /*!< Timer2 Initialization Trigger */
    TMU_SOURCE_TIM3_MATCH        = 26U,    /*!< Timer3 Match Trigger  */
    TMU_SOURCE_TIM3_INITIAL      = 27U,    /*!< Timer3 Initialization Trigger */
    TMU_SOURCE_ADC0              = 28U,    /*!< ADC0 COCO  */
    TMU_SOURCE_ADC1              = 29U,    /*!< ADC1 COCO  */
    TMU_SOURCE_CMP               = 30U,    /*!< CMP Cout  */
    TMU_SOURCE_TDG0_CH0          = 31U,    /*!< TDG0 channel 0 trigger out */
    TMU_SOURCE_TDG0_CH1          = 32U,    /*!< TDG0 channel 1 trigger out */
    TMU_SOURCE_TDG0_CH2          = 33U,    /*!< TDG0 channel 2 trigger out */
    TMU_SOURCE_TDG0_CH3          = 34U,    /*!< TDG0 channel 3 trigger out */
    TMU_SOURCE_TDG0_CH4          = 35U,    /*!< TDG0 channel 4 trigger out */
    TMU_SOURCE_TDG0_CH5          = 36U,    /*!< TDG0 channel 5 trigger out */
    TMU_SOURCE_TDG1_CH0          = 37U,    /*!< TDG1 channel 0 trigger out */
    TMU_SOURCE_TDG1_CH1          = 38U,    /*!< TDG1 channel 1 trigger out */
    TMU_SOURCE_TDG1_CH2          = 39U,    /*!< TDG1 channel 2 trigger out */
    TMU_SOURCE_TDG1_CH3          = 40U,    /*!< TDG1 channel 3 trigger out */
    TMU_SOURCE_TDG1_CH4          = 41U,    /*!< TDG1 channel 4 trigger out */
    TMU_SOURCE_TDG1_CH5          = 42U,    /*!< TDG1 channel 5 trigger out */
    TMU_SOURCE_SPI0_RX           = 43U,    /*!< SPI0 Rx Data  */
    TMU_SOURCE_SPI0_TX           = 44U,    /*!< SPI0 Tx Data  */
    TMU_SOURCE_SPI1_RX           = 45U,    /*!< SPI1 Rx Data  */
    TMU_SOURCE_SPI1_TX           = 46U,    /*!< SPI1 Tx Data  */
    TMU_SOURCE_SPI2_RX           = 47U,    /*!< SPI2 Rx Data  */
    TMU_SOURCE_SPI2_TX           = 48U,    /*!< SPI2 Tx Data  */
    TMU_SOURCE_SPI3_RX           = 49U,    /*!< SPI3 Rx Data  */
    TMU_SOURCE_SPI3_TX           = 50U,    /*!< SPI3 Tx Data  */
    TMU_SOURCE_I2C0_RX           = 51U,    /*!< I2C0 Rx Data  */
    TMU_SOURCE_I2C0_TX           = 52U,    /*!< I2C0 Tx Data  */
#if (2U == I2C_INSTANCE_NUM)
    TMU_SOURCE_I2C1_RX           = 53U,    /*!< I2C1 Rx Data  */
    TMU_SOURCE_I2C1_TX           = 54U,    /*!< I2C1 Tx Data  */      
#endif
    TMU_SOURCE_SCM_0             = 55U,    /*!< SCM Trigger  */
    TMU_SOURCE_SCM_1             = 56U,    /*!< SCM Trigger  */
    TMU_SOURCE_SCM_2             = 57U,    /*!< SCM Trigger  */
    TMU_SOURCE_SCM_3             = 58U,    /*!< SCM Trigger  */       
    TMU_SOURCE_MCPWM0_EXT_TRIG0  = 59U,    /*!< MCPWM0 EXT_TRIG[0]  */
    TMU_SOURCE_MCPWM0_EXT_TRIG1  = 60U,    /*!< MCPWM0 EXT_TRIG[1]  */
    TMU_SOURCE_MCPWM0_EXT_TRIG2  = 61U,    /*!< MCPWM0 EXT_TRIG[2]  */
    TMU_SOURCE_MCPWM0_EXT_TRIG3  = 62U,    /*!< MCPWM0 EXT_TRIG[3]  */
    TMU_SOURCE_MCPWM0_EXT_TRIG4  = 63U,    /*!< MCPWM0 EXT_TRIG[4]  */
    TMU_SOURCE_MCPWM0_EXT_TRIG5  = 64U,    /*!< MCPWM0 EXT_TRIG[5]  */
    TMU_SOURCE_MCPWM0_EXT_TRIG6  = 65U,    /*!< MCPWM0 EXT_TRIG[6]  */
    TMU_SOURCE_MCPWM0_EXT_TRIG7  = 66U,    /*!< MCPWM0 EXT_TRIG[7]  */
    TMU_SOURCE_MCPWM0_INIT_TRIG0 = 67U,    /*!< MCPWM0 INIT_TRIG[0]  */
    TMU_SOURCE_MCPWM0_INIT_TRIG1 = 68U,    /*!< MCPWM0 INIT_TRIG[1]  */
    TMU_SOURCE_MCPWM0_INIT_TRIG2 = 69U,    /*!< MCPWM0 INIT_TRIG[2]  */
    TMU_SOURCE_MCPWM0_INIT_TRIG3 = 70U,    /*!< MCPWM0 INIT_TRIG[3]  */
    TMU_SOURCE_MCPWM1_EXT_TRIG0  = 71U,    /*!< MCPWM1 EXT_TRIG[0]  */
    TMU_SOURCE_MCPWM1_EXT_TRIG1  = 72U,    /*!< MCPWM1 EXT_TRIG[1]  */
    TMU_SOURCE_MCPWM1_EXT_TRIG2  = 73U,    /*!< MCPWM1 EXT_TRIG[2]  */
    TMU_SOURCE_MCPWM1_EXT_TRIG3  = 74U,    /*!< MCPWM1 EXT_TRIG[3]  */
    TMU_SOURCE_MCPWM1_EXT_TRIG4  = 75U,    /*!< MCPWM1 EXT_TRIG[4]  */
    TMU_SOURCE_MCPWM1_EXT_TRIG5  = 76U,    /*!< MCPWM1 EXT_TRIG[5]  */
    TMU_SOURCE_MCPWM1_EXT_TRIG6  = 77U,    /*!< MCPWM1 EXT_TRIG[6]  */
    TMU_SOURCE_MCPWM1_EXT_TRIG7  = 78U,    /*!< MCPWM1 EXT_TRIG[7]  */
    TMU_SOURCE_MCPWM1_INIT_TRIG0 = 79U,    /*!< MCPWM1 INIT_TRIG[0]  */
    TMU_SOURCE_MCPWM1_INIT_TRIG1 = 80U,    /*!< MCPWM1 INIT_TRIG[1]  */
    TMU_SOURCE_MCPWM1_INIT_TRIG2 = 81U,    /*!< MCPWM1 INIT_TRIG[2]  */
    TMU_SOURCE_MCPWM1_INIT_TRIG3 = 82U,    /*!< MCPWM1 INIT_TRIG[3]  */
}TMU_Source_t;

/** @} end of group TMU_Public_Types*/

/** @defgroup TMU_Public_FunctionDeclaration
 *  @brief TMU functions statement
 *  @{
 */

/**
 * @brief       set source for TMU target module.
 *
 * @param[in]  source: Selects one of the TMU sources
 * @param[in]  module: Selects target module of the TMU modules
 *
 * @return none
 *
 */
void TMU_SetSourceForModule(TMU_Source_t source, TMU_Module_t module);

/**
 * @brief       get source for TMU target module.
 *
 * @param[in]  module: Selects target module of the TMU modules
 *
 * @return TMU_Source_t: The selected source for target module.
 *
 */
TMU_Source_t TMU_GetSourceForModule(TMU_Module_t module);

/**
 * @brief       Enable/Disable target module in TMU modules.
 *
 * @param[in]  module: Selects target module of the TMU modules
 * @param[in]  cmd:  TMU Module Control: 
 *                   - ENABLE; 
 *                   - DISABLE.
 *
 * @return none
 *
 */
void TMU_ModuleCmd(TMU_Module_t module, ControlState_t cmd);

/**
 * @brief      Lock Relevant Register for TMU target module, then register is 
 *             read only.
 *
 * @param[in]  module: Selects target module of the TMU modules
 *
 * @return none.
 *
 */
void TMU_SetLockForModule(TMU_Module_t module);

/**
 * @brief Unlock Relevant Register for TMU target module, then register is writable.
 *
 * @param[in]  module:  Selects target module of the TMU modules
 *
 * @return none.
 *
 */
void TMU_SetUnlockForModule(TMU_Module_t module);

/**
 * @brief Get Lock status for TMU target module.
 *
 * @param[in]  module: Selects target module of the TMU modules
 *
 * @return Lock status: 
 *                     - SET----Locked; 
 *                     - RESET----Unlocked.
 *
 */
FlagStatus_t TMU_GetLockStatusForModule(TMU_Module_t module);

/** @} end of group TMU_Public_FunctionDeclaration */

/** @} end of group TMU */

/** @} end of group Z20K14XM_Peripheral_Driver */
#endif /* TMU_DRV_H */
