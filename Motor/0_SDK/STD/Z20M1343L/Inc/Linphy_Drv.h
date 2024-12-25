/**************************************************************************************************/
/**
 * @file      : Linphy_Drv.h
 * @brief     : Linphy module driver header file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 * 
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
#ifndef LINPHY_DRV_H
#define LINPHY_DRV_H

#include "Common_Drv.h"

/** @addtogroup Public_MacroDefinition
 *  @{
 */
/** @} end of Public_MacroDefinition */

/** @defgroup Public_TypeDefinition
 *  @{
 */

/**
 *  @brief LINPHY interrupt type definition
 */
typedef enum
{
    LINPHY_INT_WKUP = 0U,     /*!< LINPHY wakeup request detection interrupt */
    LINPHY_INT_WKUPTO,        /*!< LINPHY wakeup request timeout interrupt */
    LINPHY_INT_DOMDET,        /*!< LINPHY dominant timeout detection interrupt */
    LINPHY_INT_ALL            /*!< All interrupt */
} Linphy_IntType;

/**
 *  @brief LINPHY status bit type definition
 */
typedef enum
{
    LINPHY_STATUS_WKUP = 0U,   /*!< LINPHY wakeup request flag */
    LINPHY_STATUS_WKUPTO,      /*!< LINPHY wakeup timeout error flag */
    LINPHY_STATUS_DOMDET,      /*!< LINPHY TXD dominant timeout flag */
    LINPHY_STATUS_OT,          /*!< LINPHY over temperature flag */
    LINPHY_STATUS_OV20,        /*!< LINPHY 20V over voltage */
    LINPHY_STATUS_UN,          /*!< LINPHY under voltage 6.5V */
    LINPHY_STATUS_ALL          /*!< All the Status */
} Linphy_StatusType;

/**
 *  @brief LINPHY action to wakeup timeout event bit type definition
 */
typedef enum
{
    
    LINPHY_WAKEUP_TIMEOUT_ACTION_INVALID = 0U,      /*!< The dominant pulse longer than the high 
                                              threshold is recognized as a invalid wakeup signal */
    LINPHY_WAKEUP_TIMEOUT_ACTION_VALID,   /*!< The dominant pulse longer than the high 
                                               threshold is recognized as a valid wakeup signal */
} Linphy_ActionToWakeupType;

/**
 *  @brief LINPHY action type to under voltage definition
 */
typedef enum
{
    LINPHY_ACT_TO_UV_SW = 0U,          /*!< Software handles the event */
    LINPHY_ACT_TO_UV_TX_OFF = 1U,      /*!< TX transfer to analog LINPHY is close with event */
} Linphy_ActToUnderVoltageType;

/**
 *  @brief LINPHY abnormal action type to over temperature and voltage definition
 */
typedef enum
{
    LINPHY_ACT_TO_ABNORMAL_SW = 0U,      /*!< Software handles the event */
    LINPHY_ACT_TO_ABNORMAL_ON = 1U,      /*!< TX/RX transfer is on with event */
    LINPHY_ACT_TO_ABNORMAL_OFF = 3U      /*!< TX/RX transfer are closed */
} Linphy_ActToAbnormalType;

/**
 *  @brief LINPHY transceiver srew fast mode type definition
 */
typedef enum
{
    LINPHY_SREW_NORMAL = 0U,    /*!< Srew rate in normal mode */
    LINPHY_SREW_FAST,           /*!< 115.2k fast srew mode */
} Linphy_SrewModeType;

/**
 *  @brief LINPHY transceiver srew rate selection type definition
 */
typedef enum
{
    LINPHY_SREW_RATE_10K = 0U,       /*!< Maximum srew rate is 10k */
    LINPHY_SREW_RATE_20K,           /*!< Maximum srew rate is 20k*/
} Linphy_SrewRateType;

/**
 *  @brief LINPHY power on control type definition
 */
typedef enum
{
    LINPHY_POWER_ON_DISABLE = 0U,    /*!< 10u bias current is closed and LINPHY in standby is enabled */
    LINPHY_POWER_ON_ENABLE,          /*!< Analog LINPHY works as normal */
} Linphy_PowerOnModeType;

/**
 *  @brief LINPHY Tx channel control type
 */
typedef enum
{
    LINPHY_TX_CH_CTRL_SW_ON = 0U,      /*!< Software control and channel is on */
    LINPHY_TX_CH_CTRL_SW_OFF,          /*!< Software control and channel is off */
    LINPHY_TX_CH_CTRL_HW_ON,           /*!< Hardware control channel is on with the hardware trigger */
    LINPHY_TX_CH_CTRL_HW_OFF           /*!< Hardware control channel is off with the hardware trigger */
} Linphy_TxChannelControlType;

/**
 *  @brief LINPHY channel control type
 */
typedef enum
{
    LINPHY_RX_CH_CTRL_SW_ON = 0U,      /*!< Software control and channel is on */
    LINPHY_RX_CH_CTRL_SW_OFF= 2U,          /*!< Software control and channel is off */
} Linphy_RxChannelControlType;

/**
 *  @brief LINPHY wakeup Configuration Structure type definition
 */
typedef struct
{
    Common_ControlStateType WakeupDetInterruptCmd; /*!<Wakeup request detection enable
                                     - COMMON_DISABLE: wakeup request detection is disabled 
                                     - COMMON_ENABLE: wakeup request detection is enabled */
    
    Common_ControlStateType WakeupToInterruptCmd; /*!<Wakeup request timeout interrupt enable
                                     - COMMON_DISABLE: wakeup request timeout interrupt is disabled 
                                     - COMMON_ENABLE: wakeup request timeout interrupt is enabled */
    
    Common_ControlStateType WakeupCmd;            /*!< LINPHY wakeup request detection command
                                             - COMMON_DISABLE: wakeup request detection is disabled 
                                             - COMMON_ENABLE: wakeup request detection is enabled */
    
    uint32 LowWakeupDetThre;        /*!< Low wakeup detection threshold
                                     The low threshold = Twakeup_clk * LowWakeupDetThre
                                      the frequency of Twakeup_clk is 96k*/
    
    uint32 HighWakeupDetThre;        /*!< High wakeup detection threshold
                                     The high threshold = Twakeup_clk * HighWakeupDetThre 
                                     the frequency of Twakeup_clk is 96k*/
    
    Linphy_ActionToWakeupType ActionCmd;    /*!< Defines the action when the length of detected 
                                                 dominant level is longer than the high threshold,
                                     - LINPHY_WAKEUP_TIMEOUT_ACTION_VALID
                                     - LINPHY_WAKEUP_TIMEOUT_ACTION_INVALID */

} Linphy_WakeupConfigType;

/**
 *  @brief LINPHY filter function for RX channel from analog LINPHY Configuration Structure type definition
 */
typedef struct
{
    uint8 FilterCounter; /*!< Filter counter. It determines filter number for filter period counter */
    
    uint8 FilterPeriod; /*!< Filter period. It determines filter period of every filter operation 
                        the frequency is filter is 96k*/
} Linphy_FilterConfigType;

/**
 *  @brief LINPHY dominal timeout detection Configuration Structure type definition
 */
typedef struct
{
    Common_ControlStateType DominalToDetInt; /*!< Dominal timeout detection interrupt enable*/
    
    Common_ControlStateType DominalToDetCmd; /*!< Dominal timeout detection enable*/
    
    uint32 DominalToThreshold; /*!< Dominal timeout threshold for txd from LIN controller.
                                    The threshold is calculated by Tpclk * DominalToThreshold .*/
} Linphy_DominalConfigType;

/**
 *  @brief LINPHY Configuration Structure type definition
 */
typedef struct
{
    Common_ControlStateType ModuleCmd; /*!< LINPHY module command
                                           - COMMON_DISABLE: LINPHY module is disabled 
                                           - COMMON_ENABLE: LINPHY module is enabled */
    
    Linphy_SrewModeType SrewMode; /*!< Srew rate mode: 
                                  -LINPHY_SREW_NORMAL
                                  -LINPHY_SREW_FAST */
    
    Linphy_SrewRateType SrewRate; /*!< Srew rate selection: 
                                  -LINPHY_SREW_RATE_10K
                                  -LINPHY_SREW_RATE_20K */
    
    Linphy_ActToAbnormalType ActionToOverTemp; /*!< action to over temperature event */
    
    Linphy_ActToAbnormalType ActionToOverVoltage; /*!< action to over voltage 20v event */
    
    Linphy_ActToUnderVoltageType ActionToUnderVoltage; /*!< action to under voltage 6v event */
    
    Linphy_PowerOnModeType PowerOnCmd;             /*!< LINPHY normal mode power on control */
    Linphy_RxChannelControlType RxChannel;           /*!< Configure rx channel control type */
    Linphy_TxChannelControlType TxChannel;           /*!< Configure tx channel control type */
    Common_ControlStateType LinphyMode;              /*!< Analog LINPHY working mode:
                                                      - COMMON_DISABLE:readonly mode 
                                                      - COMMON_ENABLE: normal mode */
} Linphy_ConfigType;

/** @} end of group Public_TypeDefinition */

/** @defgroup Global_VariableDeclaration
 *  @{
 */
/** @} end of group Global_VariableDeclaration */

/** @defgroup Public_FunctionDeclaration
 *  @{
 */
/**
 * @brief      Disable linphy module
 * @param[in]  none
 *
 * @return     none
 */
void Linphy_Disable(void);

/**
 * @brief      LINPHY initialize configuration. The api should be called after other configuration is ok.
 * @param[in]  CfgPtr: pointer to initialize configuration
 *
 * @return     none
 */
void Linphy_InitConfig(Linphy_ConfigType *CfgPtr);

/**
 * @brief      Get LINPHY status
 * @param[in]  StaType: type of status
 *                    -LINPHY_STATUS_WKUP
 *                    -LINPHY_STATUS_WKUPTO
 *                    -LINPHY_STATUS_DOMDET
 *                    -LINPHY_STATUS_OT
 *                    -LINPHY_STATUS_OV20
 *                    -LINPHY_STATUS_UN
 *                    -LINPHY_STATUS_ALL
 *
 * @return     Common_FlagStatusType:The state value of LINPHY Status register
 * @retval     COMMON_SET: The status bit is set
 * @retval     COMMON_RESET:The status bit is reset
 */
Common_FlagStatusType Linphy_GetStatus(Linphy_StatusType StaType);

/**
 * @brief      Clear LINPHY interrupt status
 * @param[in]  IntType: type of interrupt. Only the interrupt status can be cleared.
 *                    -LINPHY_INT_WKUP = 0U,
 *                    -LINPHY_INT_WKUPTO,
 *                    -LINPHY_INT_DOMDET,
 *                    -LINPHY_INT_ALL
 *
 * @return     none
 */
void Linphy_ClearIntStatus(Linphy_IntType IntType);

/**
 * @brief      Configure wakeup detection function. The function should be called before module enable.
 * @param[in]  WakeupPtr: configuration pointer of wakeup
 *
 * @return     none
 */
void Linphy_ConfigWakeupDetection(Linphy_WakeupConfigType *WakeupPtr);

/**
 * @brief      Configure filter function. The filter function effects after configuration.
 * @param[in]  FilterPtr: configuration pointer of filter
 *
 * @return     none
 */
void Linphy_ConfigFilter(Linphy_FilterConfigType *FilterPtr);

/**
 * @brief      Configure dominant timeout detection function.
 * @param[in]  ConfigPtr: pointer to dominant timeout detection configuration
 *
 * @return     none
 */
void Linphy_ConfigDominalToDetection(Linphy_DominalConfigType *ConfigPtr);

/**
 * @brief      Install call back function.
 * @param[in]  IntId:  Select the interrupt.
 * @param[in]  CbFun:  Pointer to callback function.
 * @return None.
 */
void Linphy_InstallCallbackFunc(Linphy_IntType IntId, Isr_CbFuncType * CbFun);

/** @} end of group Public_FunctionDeclaration */

#endif /* LINPHY_DRV_H */
