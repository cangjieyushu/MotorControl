/**************************************************************************************************/
/**
 * @file      : Scm_Drv.h
 * @brief     : SCM driver module header file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#ifndef SCM_DRV_H
#define SCM_DRV_H

#include "Common_Drv.h"

/** @defgroup Public_MacroDefinition
 *  @{
 */
#define SCM_LEVEL2_NMI_ALL (10U)
/** @} end of group Public_MacroDefinition */

/** @defgroup Public_TypeDefinition 
 *  @{
 */

/**  
 *  @brief SCM LIN UART PWM module selection type
 */
typedef enum
{
    SCM_UART    = 0U,                   /*!< UART */
    SCM_LIN,                            /*!< LIN */
    SCM_MCPWM_CTIMER_COM,               /*!< PWM CHO[7] output to channel PORT TX or to LIN/PWM-COM 
                                             CTIMER CHI[4] input from LIN/PWM-COM*/
    SCM_MCPWM_CTIMER_PORTRX             /*!< PWM CHO[7] output to channel PORT TX or to LIN/PWM-COM 
                                             CTIMER CHI[4] input from PORT RX*/
} Scm_LinPwmSelectionType;

/**  
 *  @brief SCM LIN UART PWM data path select type
 */
typedef enum
{
    SCM_UART_LIN_DATA_PATH0 = 0U,  /*!< UART connect to LIN(optional to PORT Tx/Rx ouput 
                                                for monitor,config through IOMIX); */
    SCM_UART_LIN_DATA_PATH1,       /*!< UART connect to PORT tx/rx(PORT.Tx (output) connected to UART.Tx ,          
                                        PORT.Rx (input) connected to UART.Rx); */
    SCM_UART_LIN_DATA_PATH2,       /*!< LIN connect to PORT tx/rx (PORT.Tx(input) connected to LIN.Tx ,
                                                          PORT.Rx (output) connected to LIN.Rx (UART.Rx)); */
    SCM_UART_LIN_DATA_PATH3       /*!< LIN connect to PORT tx/rx(PORT.Tx (input) connected to LIN.Tx,
                                                         PORT.Rx (output) connected to LIN.Rx (UART.Rx)) */
} Scm_LinPwmDataPathType;

/**  
 *  @brief PWM channel output type definition
 */
typedef enum
{
    SCM_PWM_CHANNEL_OUTPUT       = 0U,              /*!< select pwm chout[7:0] */
    SCM_TDG_TRIGGER                                 /*!< select {trigger_out[2:0],
                                                         trigger_in[2:0],chout[1:0]} */
} Scm_PwmChannelOutputType;

/**  
 *  @brief Unique Identification definition
 */
typedef enum
{
    SCM_UNIQUE0_TYPE       = 0U,               /*!< UID_31_0 */
    SCM_UNIQUE1_TYPE                           /*!< UID_63_32 */
} Scm_UniqueIdType;


/**
 *  @brief SCM master definition
 */
typedef enum
{
    SCM_MASTER_CPU          = 0U,        /*!< Master: CPU */
    SCM_MASTER_DEBUGGER,                 /*!< Master: DEBUGGER */
    SCM_MASTER_DMA,                      /*!< Master: DMA */
    SCM_MASTER_JTAG2AHB                  /*!< Master: JTAG2AHB */
} Scm_MasterType;

/**
 *  @brief SCM access size definition
 */
typedef enum
{
    SCM_ACC_SIZE_8BIT = 0U,   /*!< access size: 8 bits */
    SCM_ACC_SIZE_16BIT,       /*!< access size: 16 bits */
    SCM_ACC_SIZE_32BIT        /*!< access size: 32 bits */
} Scm_AccessSizeType;

/**
 *  @brief SCM access type definition
 */
typedef enum
{
    SCM_ACC_TYPE_OPCODE = 0U,   /*!< access type: opcode fetch */
    SCM_ACC_TYPE_DATA           /*!< access type: data access */
} Scm_AccessTypeType;

/**
 *  @brief SCM access bufferable type when ECC error detected
 */
typedef enum
{
    SCM_ACC_NON_BUFFERABLE = 0U,   /*!< access type: non bufferable */
    SCM_ACC_BUFFERABLE     /*!< access type: bufferable */
} Scm_AccessBuffableType;

/**
 *  @brief SCM access cache type when ECC error detected
 */
typedef enum
{
    SCM_ACC_NON_CACHEABLE = 0U,   /*!< access type: non-cacheable */
    SCM_ACC_CACHEABLE             /*!< access type: cacheable */
} Scm_AccessCacheType;

/**
 *  @brief SCM access mode definition
 */
typedef enum
{
    SCM_ACC_MODE_USER   = 0U,   /*!< access mode: user */
    SCM_ACC_MODE_PRIVIL         /*!< access mode: privileged */
} Scm_AccessModeType;

/**
 *  @brief CSA vzero control type definition
 */
typedef enum
{
    SCM_CSA_OUTPUT_AMPLIFIER_SIGNAL   = 0U,   /*!< CSA output amplifier signal */
    SCM_CSA_OUTPUT_VZERO_VOLTAGE      = 1U    /*!< CSA output vzero voltage */
} Scm_CsaVzeroControlType;

/**
 *  @brief CSA gain type definition
 */
typedef enum
{
    SCM_CSA_GAIN_10x   = 0U,   /*!< 10x */
    SCM_CSA_GAIN_20x,          /*!< 20x */
    SCM_CSA_GAIN_40x,          /*!< 40x */
    SCM_CSA_GAIN_60x           /*!< 60x */
} Scm_CsaGainType;

/**
 *  @brief SCM PAD fault polarity config type
 */
typedef enum
{
    SCM_PAD_FAULT_POLARITY_0  = 0U,      /*!< normal status is 0, fault valid polarity is 1 */
    SCM_PAD_FAULT_POLARITY_1,            /*!< normal status is 1, fault valid polarity is 0 */
} Scm_PadFaultPolarityType;

/**
 *  @brief SCM level2 NMI enable control type definition
 */
typedef enum
{
    SCM_LEVEL2_NMI_GDU_WARNING            = 0U,     /*!< GDU warning interrupt */
    SCM_LEVEL2_NMI_VAREF_FAILURE,                   /*!< VAREF failure interrupt */
    SCM_LEVEL2_NMI_VDDEXT_FAILURE,                  /*!< VDDEXT failure interrupt */
    SCM_LEVEL2_NMI_SUPPLY_PRE_WARNING,              /*!< Supply pre-warning interrupt */
    SCM_LEVEL2_NMI_HARD_FAILURE,                    /*!< hard failure interrupt */
    SCM_LEVEL2_NMI_MCPWM_FAULT,                     /*!< mcpwm fault interrupt */
    SCM_LEVEL2_NMI_EXTERNAL_PIN,                    /*!< external nmi pin interrupt */
    SCM_LEVEL2_NMI_WDOG_PRE_WARNING,                /*!< WDOG pre-warning interrupt */
    SCM_LEVEL2_NMI_ADC_OVER_TEMP_SHUTDOWN,          /*!< ADC over-temperature shutdown 
                                                        interrupt */
    SCM_LEVEL2_NMI_ADC_DISABLE                      /*!< ADC disable due to VAREF > VDDP 
                                                         interrupt*/
} Scm_Level2NmiType;

/**
 *  @brief SCM level1 NMI interrupt flag type definition
 */
typedef enum
{
    SCM_LEVEL1_CMU_FREQUENCY_ALARM_INT_FLAG    = 11U,   /*!< CMU frequency alarm interrupt flag */
    SCM_LEVEL1_FLASH_ECC_ERROR_INT_FLAG,                /*!< flash ECC error interrupt flag */
    SCM_LEVEL1_MEMORY_ECC_ERROR_INT_FLAG,               /*!< memory ECC error interrupt flag */
    SCM_LEVEL1_MCPWM_PAD_FAULT_INT_FLAG,                /*!< mcpwm pad fault interrupt flag */
    SCM_LEVEL1_CMP_WARNING_INT_FLAG,                    /*!< CMP warning interrupt flag */
} Scm_Level1NmiIntFlagType;

/**
 *  @brief SCM level2 NMI interrupt flag type definition
 */
typedef enum
{
    SCM_LEVEL2_GDU_WARNING_INT_FLAG            = 0U,   /*!< GDU warning interrupt flag */
    SCM_LEVEL2_VAREF_FAILURE_INT_FLAG,                 /*!< VAREF failure interrupt flag */
    SCM_LEVEL2_VDDEXT_FAILURE_INT_FLAG,                /*!< VDDEXT failure interrupt flag */
    SCM_LEVEL2_SUPPLY_PRE_WARNING_INT_FLAG,            /*!< supply pre-warning interrupt flag */
    SCM_LEVEL2_HARD_FAILURE_INT_FLAG,                  /*!< hard failure warning interrupt flag */
    SCM_LEVEL2_MCPWM_FAULT_INT_FLAG,                   /*!< mcpwm fault interrupt flag */
    SCM_LEVEL2_EXTERNAL_NMI_PIN_INT_FLAG,              /*!< external NMI pin interrupt flag */
    SCM_LEVEL2_WDOG_PRE_WARNING_INT_FLAG,              /*!< WDOG pre-warning interrupt flag */
    SCM_LEVEL2_ADC_OVER_TEMP_SHUTDOWN_INT_FLAG,        /*!< ADC over-temperature shutdown interrupt flag */
    SCM_LEVEL2_ADC_DISABLE_INT_FLAG,                   /*!< ADC disable due to VAREF>VDDP interrupt flag */
} Scm_Level2NmiIntFlagType;

/**
 *  @brief SCM ECC error type definition
 */
typedef enum
{
    SCM_ECC_ERR_SINGLEBIT = 0u,
    SCM_ECC_ERR_MULTIBIT,
    SCM_ECC_ERR_OVERRUN,
    SCM_ECC_ERR_ALL
} Scm_EccErrorType;

/**
 *  @brief SCM SRAM ECC error cause struct definition
 */
typedef struct
{
    Common_FlagStatusType IsWriting;        /*!< whether ECC error is caused by writing operation 
                                        - RESET: it is caused by reading
                                        - SET: it is caused by writing */
    uint32 ErrFaultAddr;               /*!< The access address that caused ECC error */
    uint32 ErrFaultData;               /*!< The fault data  */
    Scm_MasterType ErrFaultMaster;     /*!< Indicates error caused by which master.*/
    Scm_AccessSizeType ErrFaultSize;   /*!< Indicates error caused by  what size of access.*/
    Scm_AccessTypeType AccessType;     /*!< Indicates error caused by which type of access. */
    Scm_AccessModeType AccessMode;     /*!< Indicates error caused in which mode */
    Scm_AccessBuffableType BufferableType;   /*!< Indicates error caused in which bufferable type */
    Scm_AccessCacheType CacheType;     /*!< Indicates error caused in which cache type */
} Scm_SramEccErrCauseType;

/** @} end of group Public_TypeDefinition */

/** @defgroup Global_VariableDeclaration
 *  @{
 */

/** @} end of group Global_VariableDeclaration */

/** @defgroup Public_FunctionDeclaration
 *  @{
 */
/**
 * @brief      Enable peripheral register write lock. This API will lock all the peripheral
 *                writable registers, which are static configuration for the peripheral. When the 
 *                PERI_WLK bit is locked, all peripheral writable registers can not be written.
 *
 * @param[in]  none. 
 *
 * @return     none
 *
 */
void Scm_LockPeripheralWritableRegister(void);

/**
 * @brief      Disable peripheral register write lock. This API will unlock all the peripheral
 *                writable registers, which are static configuration for the peripheral. When the 
 *                PERI_WLK bit is unlocked, all peripheral writable registers can be written.
 *
 * @param[in]  none. 
 *
 * @return     none
 *
 */
void Scm_UnlockPeripheralWritableRegister(void);

/**
 * @brief      Select UART LIN or PWM module config.
 * @param[in]  Type: SCM LIN UART PWM module select type :
 *               - SCM_UART: select UART function
 *               - SCM_LIN: select LIN function
 *               - SCM_MCPWM_CTIMER_COM: PWM CHO[7] output to channel PORT TX or to LIN/PWM-COM 
 *                                       CTIMER CHI[4] input from LIN/PWM-COM
 *               - SCM_MCPWM_CTIMER_PORTRX: PWM CHO[7] output to channel PORT TX or to LIN/PWM-COM 
 *                                          CTIMER CHI[4] input from PORT RX
 *
 * @return     none
 *
 */
void Scm_SelectLinPwmModule(Scm_LinPwmSelectionType Type);

/**
 * @brief      Select PWM module channel output type for PWM signal monitor
 * @param[in]  Type: PWM channel output type:
 *                   - SCM_PWM_CHANNEL_OUTPUT: select pwm chout[7:0]
 *                   - SCM_TDG_TRIGGER: select {trigger[5:0],chout[1:0]}
 *
 * @return     none
 *
 */
void Scm_SelectPwmChannelOutput(Scm_PwmChannelOutputType Type);

/**
 * @brief      Set SRAM ECC read control status.
 * @param[in]  Status: SRAM ECC read status :
 *                   - COMMON_ENABLE: SRAM ECC read enable
 *                   - COMMON_DISABLE: SRAM ECC read disable
 *
 * @return     none
 *
 */
void Scm_SetSramEccRead(Common_ControlStateType Status);

/**
 * @brief      Set SRAM ECC write control status.
 *
 * @param[in]  Status: SRAM ECC write status:
 *                 - COMMON_ENABLE: SRAM ECC write enable
 *                 - COMMON_DISABLE: SRAM ECC write disable
 *
 * @return     none
 *
 */
void Scm_SetSramEccWrite(Common_ControlStateType Status);

/**
 * @brief      Set SRAM ECC single bit control status.
 * 
 * @param[in]  Status: SRAM ECC single bit status :
 *                 - COMMON_ENABLE: SRAM ECC single bit enable
 *                 - COMMON_DISABLE: SRAM ECC single bit disable
 *
 * @return     none
 *
 */
void Scm_SetSramEccSingleBit(Common_ControlStateType Status);

/**
 * @brief      Set SRAM ECC multi bit control status.
 * @param[in]  Status: SRAM ECC multi bit status :
 *                 - COMMON_ENABLE: SRAM ECC multi bit enable
 *                 - COMMON_DISABLE: SRAM ECC multi bit disable
 *
 * @return     none
 *
 */
void Scm_SetSramEccMultiBit(Common_ControlStateType Status);

/**
 * @brief      Get SRAM ECC error cause
 *
 * @param[in]  CausePtr: the cause of SRAM ECC error will be stored in the struct 
 *                    that is pointed by this parameter. 
 *
 * @return none
 *
 */
void Scm_GetSramEccErrCause(Scm_SramEccErrCauseType *CausePtr);

/**
 * @brief      Get SRAM ECC error status
 *
 * @param[in]  EccErrorType: select the error status type to get :
 *               - SCM_ECC_ERR_SINGLEBIT: signal bit ECC error
 *               - SCM_ECC_ERR_MULTIBIT: multi bit ECC error
 *               - SCM_ECC_ERR_OVERRUN: ECC overrun error
 *               - SCM_ECC_ERR_ALL: All ECC error
 *
 * @return    Error status
 * @retval    COMMON_RESET: the error status is not set
 * @retval    COMMON_SET: the error status is set
 *
 */
Common_FlagStatusType Scm_GetSramEccErrStatus(Scm_EccErrorType EccErrorType);

/**
 * @brief      Clear SRAM ECC error status
 * @param[in]  EccErrorType: select the error status type to clear :
 *               - SCM_ECC_ERR_SINGLEBIT: signal bit ECC error
 *               - SCM_ECC_ERR_MULTIBIT: multi bit ECC error
 *               - SCM_ECC_ERR_OVERRUN: ECC overrun error
 *               - SCM_ECC_ERR_ALL: All ECC error
 *
 * @return    None
 *
 */
void Scm_ClearSramEccErrStatus(Scm_EccErrorType EccErrorType);

/**
 * @brief      SRAM Init Trig Function
 *
 * @param[in]  None
 *
 * @return     Common_ResultStatusType:
 *              - COMMON_SUCC: SRAM init successfully
 *              - COMMON_ERR: SRAM init failed
 *
 */
Common_ResultStatusType Scm_SetSramInitTrig(void);

/**
 * @brief      set CSA logic enable.
 * @param[in]  Status: CSA logic status :
 *                 - COMMON_ENABLE: CSA logic enable
 *                 - COMMON_DISABLE: CSA logic disable
 *
 * @return     none
 *
 */
void Scm_SetCsaLogicEnable(Common_ControlStateType Status);

/**
 * @brief      get CSA logic status.
 * @param[in]  none
 *
 * @return     CSA logic status
 *
 */
Common_ControlStateType Scm_GetCsaLogicStatus(void);

/**
 * @brief      set CSA vzero control signal.
 * @param[in]  ControlCmd: CSA Vzero control signal
 *                 - SCM_CSA_OUTPUT_AMPLIFIER_SIGNAL: CSA output amplifier signal
 *                 - SCM_CSA_OUTPUT_VZERO_VOLTAGE: CSA output vzero voltage
 *
 * @return     none
 *
 */
void Scm_SetCsaVzeroControlSignal(Scm_CsaVzeroControlType ControlCmd);

/**
 * @brief      get CSA vzero control signal.
 * @param[in]  none
 *
 * @return     CSA vzero control signal
 *
 */
Scm_CsaVzeroControlType Scm_GetCsaVzeroControlSignal(void);

/**
 * @brief      set CSA gain.
 * @param[in]  Gain: CSA gain
 *                 - SCM_CSA_OUTPUT_AMPLIFIER_SIGNAL: CSA output amplifier signal
 *                 - SCM_CSA_OUTPUT_VZERO_VOLTAGE: CSA output vzero voltage
 *
 * @return     none
 *
 */
void Scm_SetCsaGain(Scm_CsaGainType Gain);

/**
 * @brief      get CSA gain.
 * @param[in]  none
 *
 * @return     CSA gain
 *
 */
Scm_CsaGainType Scm_GetCsaGain(void);

/**
 * @brief      Config PAD fault polarity.
 * @param[in]  PolarityType: polarity type
 *                 - SCM_PAD_FAULT_POLARITY_0: normal status is 0, fault valid polarity is 1
 *                 - SCM_PAD_FAULT_POLARITY_1: normal status is 1, fault valid polarity is 0
 *
 * @return     none
 *
 */
void Scm_ConfigPadFaultPolarity(Scm_PadFaultPolarityType PolarityType);

/**
 * @brief      Get PAD fault polarity config type.
 *
 * @return     PAD fault polarity config type 
 * @retval     SCM_PAD_FAULT_POLARITY_0: normal status is 0, fault valid polarity is 1
 * @retval     SCM_PAD_FAULT_POLARITY_1: normal status is 1, fault valid polarity is 0
 *
 */
Scm_PadFaultPolarityType Scm_GetPadFaultPolarity(void);

/**
 * @brief      Config MCPWM PAD fault interrupt enable.
 * @param[in]  Status: MCPWM PAD fault interrupt enable/disable
 *                 - COMMON_DISABLE: disable PWM PAD fault interrupt
 *                 - COMMON_ENABLE: enable PWM PAD fault interrupt
 *
 * @return     none
 *
 */
void Scm_EnablePadFaultInt(Common_ControlStateType Status);

/**
 * @brief      Get MCPWM PAD fault interrupt enable status.
 *
 * @return     MCPWM PAD fault interrupt enable status 
 * @retval     COMMON_DISABLE: PWM PAD fault interrupt is disable
 * @retval     COMMON_ENABLE: PWM PAD fault interrupt is enable
 *
 */
Common_ControlStateType Scm_GetPadFaultIntConfig(void);

/**
 * @brief      enable level2 NMI interrupt.
 * @param[in]  IntType: control type
 *                 - SCM_LEVEL2_NMI_GDU_WARNING:  GDU warning interrupt
 *                   ...
 *                 - SCM_LEVEL2_NMI_ADC_DISABLE: ADC disable due to VAREF > VDDP interrupt enable
 *
 * @return     none
 *
 */
void Scm_EnableLevel2NMI(Scm_Level2NmiType IntType);

/**
 * @brief      disable level2 NMI interrupt.
 * @param[in]  IntType: control type
 *                 - SCM_LEVEL2_NMI_GDU_WARNING:  GDU warning interrupt
 *                   ...
 *                 - SCM_LEVEL2_NMI_ADC_DISABLE: ADC disable due to VAREF > VDDP interrupt enable
 *
 * @return     none
 *
 */
void Scm_DisableLevel2NMI(Scm_Level2NmiType IntType);

/**
 * @brief      get level2 NMI interrupt control status.
 * @param[in]  IntType: control type
 *                 - SCM_LEVEL2_NMI_GDU_WARNING:  GDU warning interrupt
 *                   ...
 *                 - SCM_LEVEL2_NMI_ADC_DISABLE: ADC disable due to VAREF > VDDP interrupt enable
 *
 * @return     level2 NMI interrupt control status
 * @retval     COMMON_SET: interrupt control status set
 * @retval     COMMON_RESET: interrupt control status not set
 *
 */
Common_IntStatusType Scm_GetLevel2NMIControlStatus(Scm_Level2NmiType IntType);

/**
 * @brief      get level1 NMI interrupt flag.
 * @param[in]  IntType: control type
 *                 - SCM_LEVEL1_CMU_FREQUENCY_ALARM_INT_FLAG:  CMU frequency alarm interrupt flag
 *                   ...
 *                 - SCM_LEVEL1_CMP_WARNING_INT_FLAG: CMP warning interrupt flag
 *
 * @return     level1 NMI interrupt flag
 * @retval     COMMON_SET: interrupt flag set
 * @retval     COMMON_RESET: interrupt flag not set
 *
 */
Common_IntStatusType Scm_GetLevel1NMIIntFlag(Scm_Level1NmiIntFlagType IntType);

/**
 * @brief      get level2 NMI interrupt flag.
 * @param[in]  IntType: NMI interrupt flag type
 *                 - SCM_LEVEL2_GDU_WARNING_INT_FLAG:  GDU warning interrupt flag
 *                   ...
 *                 - SCM_LEVEL2_ADC_DISABLE_INT_FLAG: ADC disable due to VAREF>VDDP interrupt flag
 *
 * @return     level2 NMI interrupt status
 * @retval     COMMON_SET: interrupt flag set
 * @retval     COMMON_RESET: interrupt flag not set
 *
 */
Common_IntStatusType Scm_GetLevel2NMIIntFlag(Scm_Level2NmiIntFlagType IntType);

/**
 * @brief      clear level2 NMI external pin interrupt flag.
 * @param[in]  none
 *
 * @return     none
 *
 */
void Scm_ClearExternalPinIntFlag(void);

/**
 * @brief      Get Device ID
 *
 * @param[in]  none
 *
 * @return     Device ID
 *
 */   
uint32 Scm_GetDeviceId(void);

/**
 * @brief      Get Unique Identification 0
 *
 * @param[in]  IdType : Unique ID type
 *                   - SCM_UNIQUE0_TYPE
 *                   - SCM_UNIQUE1_TYPE
 *                   - SCM_UNIQUE2_TYPE
 *                   - SCM_UNIQUE3_TYPE
 *
 * @return     Unique IDx
 *
 */
uint32 Scm_GetUniqueId(Scm_UniqueIdType IdType);

/**
 * @brief      Scm install NMI interrupt callback function
 *
 * @param[in]  IntType: Select Int type.
 *              - SCM_LEVEL2_NMI_GDU_WARNING,
 *              - SCM_LEVEL2_NMI_VAREF_FAILURE
 *                ...
 *              - SCM_LEVEL2_NMI_ADC_OVER_TEMP_SHUTDOWN
 *              - SCM_LEVEL2_NMI_ADC_DISABLE
 * @param[in]  CbFun: Callback function .
 *
 * @return     None
 *
 */
void Scm_InstallNmiLevel2CallBackFunc(Scm_Level2NmiType IntType, Isr_CbFuncType * CbFun);

/** @} end of group Public_FunctionDeclaration */

#endif  /* SCM_DRV_H */
