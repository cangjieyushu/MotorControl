/**************************************************************************************************/
/**
 * @file      : Z20K11xM_tmu.h
 * @brief     : TMU driver module header file.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (C) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#ifndef Z20K11XM_TMU_H
#define Z20K11XM_TMU_H

#include "Z20K11xM_drv.h"

/** @addtogroup  Z20K11X_Peripheral_Driver
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
    TMU_MODULE_CMP_SAPMLE      = 20U,       /*!< CMP Sample  */
    TMU_MODULE_CMP_EXT_EN      = 21U,       /*!< CMP external enable */
    TMU_MODULE_TIMER0_FAULT0   = 24U,       /*!< Timer0 fault 0  */
    TMU_MODULE_TIMER0_FAULT1   = 25U,       /*!< Timer0 fault 1  */
    TMU_MODULE_TIMER1_FAULT0   = 26U,       /*!< Timer1 fault 0  */
    TMU_MODULE_TIMER1_FAULT1   = 27U,       /*!< Timer1 fault 1  */
    TMU_MODULE_TIMER2_FAULT0   = 28U,       /*!< Timer2 fault 0  */
    TMU_MODULE_TIMER2_FAULT1   = 29U,       /*!< Timer2 fault 1  */
    TMU_MODULE_TDG0_TRIG_IN    = 32U,       /*!< TDG0 trig in    */
    TMU_MODULE_STIM_TRIG_IN0   =36U,        /*!< stim_trig_in[0] */
    TMU_MODULE_STIM_TRIG_IN1   =37U,        /*!< stim_trig_in[1] */
    TMU_MODULE_STIM_TRIG_IN2   =38U,        /*!< stim_trig_in[2] */
    TMU_MODULE_STIM_TRIG_IN3   =39U         /*!< stim_trig_in[3] */
}TMU_Module_t;
/**
 *  @brief TMU Input Select type definition
 */
typedef enum
{
    TMU_SOURCE_DISABLED        = 0U,     /*!< VSS  */
    TMU_SOURCE_VDD             = 1U,     /*!< VDD  */
    TMU_SOURCE_IN0             = 2U,     /*!< TMU  IN0  */
    TMU_SOURCE_IN1             = 3U,     /*!< TMU  IN1  */
    TMU_SOURCE_IN2             = 4U,     /*!< TMU  IN2  */
    TMU_SOURCE_IN3             = 5U,     /*!< TMU  IN3  */
    TMU_SOURCE_IN4             = 6U,     /*!< TMU  IN4  */
    TMU_SOURCE_IN5             = 7U,     /*!< TMU  IN5  */
    TMU_SOURCE_IN6             = 8U,     /*!< TMU  IN6  */
    TMU_SOURCE_IN7             = 9U,     /*!< TMU  IN7  */
    TMU_SOURCE_IN8             = 10U,    /*!< TMU  IN8  */
    TMU_SOURCE_IN9             = 11U,    /*!< TMU  IN9 */
    TMU_SOURCE_RTC_1Hz         = 12U,    /*!< RTC_1HZ_MUX_OUT */
    TMU_SOURCE_RTC_ALARM       = 13U,    /*!< RTC  Alarm  interrupt */
    TMU_SOURCE_STIM_OUT0       = 14U,    /*!< stim_trig_out[0] */
    TMU_SOURCE_STIM_OUT1       = 15U,    /*!< stim_trig_out[1] */
    TMU_SOURCE_STIM_OUT2       = 16U,    /*!< stim_trig_out[2] */
    TMU_SOURCE_STIM_OUT3       = 17U,    /*!< stim_trig_out[3] */    
    TMU_SOURCE_TIMER0_MATCH    = 18U,    /*!< Timer0 Match Trigger  */
    TMU_SOURCE_TIMER0_INITIAL  = 19U,    /*!< Timer0 Initialization Trigger  */
    TMU_SOURCE_TIMER1_MATCH    = 20U,    /*!< Timer1 Match Trigger  */
    TMU_SOURCE_TIMER1_INITIAL  = 21U,    /*!< Timer1 Initialization Trigger  */
    TMU_SOURCE_TIMER2_MATCH    = 22U,    /*!< Timer2 Match Trigger  */
    TMU_SOURCE_TIMER2_INITIAL  = 23U,    /*!< Timer2 Initialization Trigger  */
    TMU_SOURCE_ADC0            = 26U,    /*!< ADC0 COCO  */
    TMU_SOURCE_CMP             = 28U,    /*!< CMP Cout  */
    TMU_SOURCE_TDG0_CH0        = 30U,    /*!< TDG0 channel 0 trigger out */
    TMU_SOURCE_TDG0_CH1        = 31U,    /*!< TDG0 channel 1 trigger out */
    TMU_SOURCE_TDG0_CH2        = 32U,    /*!< TDG0 channel 2 trigger out */
    TMU_SOURCE_TDG0_CH3        = 33U,    /*!< TDG0 channel 3 trigger out */
    TMU_SOURCE_TDG0_CH4        = 34U,    /*!< TDG0 channel 4 trigger out */
    TMU_SOURCE_TDG0_CH5        = 35U,    /*!< TDG0 channel 5 trigger out */
    TMU_SOURCE_I2C0_RX         = 38U,    /*!< I2C0 Rx Data  */
    TMU_SOURCE_I2C0_TX         = 39U,    /*!< I2C0 Tx Data  */
#if (2U == I2C_INSTANCE_NUM)
    TMU_SOURCE_I2C1_RX         = 40U,    /*!< I2C1 Rx Data  */
    TMU_SOURCE_I2C1_TX         = 41U,    /*!< I2C1 Tx Data  */
#endif
    TMU_SOURCE_SPI0_RX         = 44U,    /*!< SPI0 Rx Data  */
    TMU_SOURCE_SPI0_TX         = 45U,    /*!< SPI0 Tx Data  */
    TMU_SOURCE_SPI1_RX         = 46U,    /*!< SPI1 Rx Data  */
    TMU_SOURCE_SPI1_TX         = 47U,    /*!< SPI1 Tx Data  */
#if (3U == SPI_INSTANCE_NUM)
    TMU_SOURCE_SPI2_RX         = 48U,    /*!< SPI2 Rx Data  */
    TMU_SOURCE_SPI2_TX         = 49U,    /*!< SPI2 Tx Data  */
#endif
    TMU_SOURCE_SCM_0           = 52U,    /*!< SCM Trigger  */
    TMU_SOURCE_SCM_1           = 53U,    /*!< SCM Trigger  */
    TMU_SOURCE_SCM_2           = 54U,    /*!< SCM Trigger  */
    TMU_SOURCE_SCM_3           = 55U,    /*!< SCM Trigger  */       
    TMU_SOURCE_TIM0_CH0        = 56U,    /*!< Timer0 Ch0  */
    TMU_SOURCE_TIM0_CH1        = 57U,    /*!< Timer0 Ch1  */
    TMU_SOURCE_TIM1_CH0        = 58U,    /*!< Timer1 Ch0  */
    TMU_SOURCE_TIM1_CH1        = 59U,    /*!< Timer1 Ch1  */
    TMU_SOURCE_TIM2_CH0        = 60U,    /*!< Timer2 Ch0  */
    TMU_SOURCE_TIM2_CH1        = 61U     /*!< Timer2 Ch1  */
}TMU_Source_t;

/** @} end of group TMU_Public_Types*/

/** @defgroup TMU_Public_FunctionDeclaration
 *  @brief TMU functions statement
 *  @{
 */

/**
 * @brief       set source for TMU target module.
 *
 * @param[in]  source:           selects one of the TMU sources
 * @param[in]  module:           selects target module of the TMU modules
 *
 * @return none
 *
 */
void TMU_SetSourceForModule(TMU_Source_t source, TMU_Module_t module);

/**
 * @brief       get source for TMU target module.
 *
 * @param[in]  module:           selects target module of the TMU modules
 *
 * @return the selected source for target module.
 *
 */
TMU_Source_t TMU_GetSourceForModule(TMU_Module_t module);

/**
 * @brief       Enable/Disable target module in TMU modules.
 *
 * @param[in]  module:           selects target module of the TMU modules
 * @param[in]  cmd:              TMU Module Control: 
 *                                               - ENABLE; 
 *                                               - DISABLE;
 *
 * @return none
 *
 */
void TMU_ModuleCmd(TMU_Module_t module, ControlState_t cmd);

/**
 * @brief Lock Relevant Register for TMU target module, then register is read only.
 *
 * @param[in]  module:           selects target module of the TMU modules
 *
 * @return none.
 *
 */
void TMU_SetLockForModule(TMU_Module_t module);

/**
 * @brief Unlock Relevant Register for TMU target module, then register is writable.
 *
 * @param[in]  module:           selects target module of the TMU modules
 *
 * @return none.
 *
 */
void TMU_SetUnlockForModule(TMU_Module_t module);

/**
 * @brief Get Lock status for TMU target module.
 *
 * @param[in]  module:           selects target module of the TMU modules
 *
 * @return Lock status: 
 *                     - SET----Locked; 
 *                     - RESET----Unlocked;
 *
 */
FlagStatus_t TMU_GetLockStatusForModule(TMU_Module_t module);

/** @} end of group TMU_Public_FunctionDeclaration */

/** @} end of group TMU */

/** @} end of group Z20K11X_Peripheral_Driver */
#endif /* Z20K11XM_TMU_H */
