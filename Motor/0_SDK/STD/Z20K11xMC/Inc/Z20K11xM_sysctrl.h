/**************************************************************************************************/
/**
 * @file      : Z20K11xM_sysctrl.h
 * @brief     : SYSCTRL driver module header file.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (C) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#ifndef Z20K11XM_SYSCTRL_H
#define Z20K11XM_SYSCTRL_H

#include "Z20K11xM_drv.h"

/** @addtogroup  Z20K11X_Peripheral_Driver
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
    SYSCTRL_TDG0 = 0x18U,              /*!< TDG0 */
    SYSCTRL_CAN0 = 0x1CU,              /*!< CAN0 */
    SYSCTRL_CAN1 = 0x20U,              /*!< CAN1 */
    SYSCTRL_UART0 = 0x24U,             /*!< UART0 */
    SYSCTRL_UART1 = 0x28U,             /*!< UART1 */
    SYSCTRL_UART2 = 0x2CU,             /*!< UART2 */
    SYSCTRL_UART3 = 0x30U,             /*!< UART3 */
    SYSCTRL_SPI0 = 0x34U,              /*!< SPI0 */
    SYSCTRL_SPI1 = 0x38U,              /*!< SPI1 */
    SYSCTRL_SPI2 = 0x3CU,              /*!< SPI2 */
    SYSCTRL_I2C0 = 0x40U,              /*!< I2C0 */
    SYSCTRL_I2C1 = 0x44U,              /*!< I2C1 */
    SYSCTRL_ADC0 = 0x48U,              /*!< ADC0 */
    SYSCTRL_CMP = 0x4CU,               /*!< CMP */
    SYSCTRL_CRC = 0x50U,               /*!< CRC */
    SYSCTRL_FLASH = 0x54U,             /*!< FLASH */
    SYSCTRL_DMA = 0x58U,               /*!< DMA */
    SYSCTRL_DMAMUX = 0x5CU,            /*!< DMAMUX */
    SYSCTRL_PORTA = 0x60U,             /*!< PORTA */
    SYSCTRL_PORTB = 0x64U,             /*!< PORTB */
    SYSCTRL_PORTC = 0x68U,             /*!< PORTC */
    SYSCTRL_PORTD = 0x6cU,             /*!< PORTD */
    SYSCTRL_PORTE = 0x70U,              /*!< PORTE */
    SYSCTRL_TMU = 0x74U,                /*!< TMU */    
    SYSCTRL_REGFILE = 0x78U,           /*!< REGFILE */ 
    SYSCTRL_GPIO = 0x7CU,              /*!< GPIO */
    SYSCTRL_HWDIV = 0x80U             /*!< HWDIV */
}SYSCTRL_Module_t;

typedef enum
{
    SYSCTRL_TRIG_LEVEL_LOW = 0U,     /*!< software trigger level: low */
    SYSCTRL_TRIG_LEVEL_HIGH = 1U     /*!< software trigger level: high */
}SYSCTRL_TriggerLevel_t;

typedef enum
{
    SYSCTRL_TRIG_SRC_0 = 0U,     /*!< software trigger source 0 */
    SYSCTRL_TRIG_SRC_1 = 1U,     /*!< software trigger source 1 */
    SYSCTRL_TRIG_SRC_2 = 2U,     /*!< software trigger source 2 */
    SYSCTRL_TRIG_SRC_3 = 3U      /*!< software trigger source 3 */
}SYSCTRL_TriggerSrc_t;

/**
 *  @brief SYSCTRL SRAM ID definition
 */
typedef enum
{
    SYSCTRL_SRAM_L = 0U,            /*!< SRAM_L */
    SYSCTRL_SRAM_U                  /*!< SRAM_U */
}SYSCTRL_Sram_t;

/**
 *  @brief SYSCTRL master definition
 */
typedef enum
{
    SYSCTRL_MASTER_CPU = 1U,   /*!< Master: CPU */
    SYSCTRL_MASTER_DMA = 2U,   /*!< Master: DMA */
}SYSCTRL_Master_t;

/**
 *  @brief SYSCTRL access size definition
 */
typedef enum
{
    SYSCTRL_ACC_SIZE_8BIT = 0U,   /*!< access size: 8 bits */
    SYSCTRL_ACC_SIZE_16BIT = 1U,  /*!< access size: 16 bits */
    SYSCTRL_ACC_SIZE_32BIT = 2U,  /*!< access size: 32 bits */
}SYSCTRL_AccessSize_t;

/**
 *  @brief SYSCTRL access type definition
 */
typedef enum
{
    SYSCTRL_ACC_TYPE_OPCODE = 0U,   /*!< access type: opcode fetch */
    SYSCTRL_ACC_TYPE_DATA = 1U,     /*!< access type: data access */
}SYSCTRL_AccessType_t;

/**
 *  @brief SYSCTRL access mode definition
 */
typedef enum
{
    SYSCTRL_ACC_MODE_USER = 0U,   /*!< access mode: user */
    SYSCTRL_ACC_MODE_PRIVIL = 1U, /*!< access mode: privileged */
}SYSCTRL_AccessMode_t;

/**
 *  @brief SYSCTRL SRAM config struct definition
 */
typedef struct
{
    ControlState_t readEccEn;      /*!< Enable/disable ECC when it reads SRAM */
    ControlState_t writeEccEn;     /*!< Enable/disable ECC when it writes SRAM */
    ControlState_t singleBitEccEn; /*!< Enable/disable single bit ECC when 
                                        accesses SRAM */
    ControlState_t multiBitEccEn;  /*!< Enable/disable multi bit ECC when 
                                        accesses SRAM */
}SYSCTRL_SramEcc_t;
    
/**
 *  @brief SYSCTRL SRAM ECC error cause struct definition
 */
typedef struct
{
    FlagStatus_t write;    /*!< whether ECC error is caused by writing operation 
                                - RESET: it is caused by reading
                                - SET: it is caused by writing */
    uint32_t errAddr;      /*!< The access address that caused ECC error */
    uint32_t faultData;    /*!< The fault data  */
    SYSCTRL_Master_t faultMaster; /*!< Indicates error caused by which master.*/
    SYSCTRL_AccessSize_t faultSize; /*!< Indicates error caused by  what size of
                                         access.*/
    SYSCTRL_AccessType_t accessType;/*!< Indicates error caused by which type of
                                         access. */
    SYSCTRL_AccessMode_t accessMode;/*!< Indicates error caused in which mode */
    FlagStatus_t bufferable;      /*!< Indicates it is bufferable or not
                                       - RESET: Non-bufferable
                                       - SET: Bufferable */
    FlagStatus_t cacheable;       /*!< Indicates it is bufferable or not
                                       - RESET: Non-cacheable
                                       - SET: Cacheable */
}SYSCTRL_SramEccErrCause_t;

/**
 *  @brief SYSCTRL device ID struct definition
 */
typedef struct
{   
    uint8_t packageId;     /*!< Package ID*/
    uint8_t featureId;     /*!< Feature ID*/
    uint8_t RevisionId;    /*!< Revision ID*/
    uint8_t familyId;      /*!< Family ID*/
    uint8_t subFamilyId;   /*!< Sub Family ID*/
    uint8_t seriesId;      /*!< Series ID*/
    uint8_t memSizeId;     /*!< Memory size ID*/
}SYSCTRL_DeviceId_t;



/** @} end of group SYSCTRL_Public_Types */

/** @defgroup SYSCTRL_Public_Constants
 *  @{
 */

/** @} end of group SYSCTRL_Public_Constants */

/** @defgroup SYSCTRL_Public_Macro
 *  @{
 */
#define  SYSCTRL_SRAM_ECC_ERR_SINGLEBIT_MASK     0x20000000U,   /*!< SRAM ECC single bit error */
#define  SYSCTRL_SRAM_ECC_ERR_MULTIBIT_MASK      0x40000000U,   /*!< SRAM ECC multi bit error */
#define  SYSCTRL_SRAM_ECC_ERR_OVERRUN_MASK       0x80000000U,   /*!< SRAM ECC error overrun */
#define  SYSCTRL_SRAM_ECC_ERR_ALL_MASK           0xE0000000U    /*!< all SRAM ECC error status */
/** @} end of group SYSCTRL_Public_Macro */

/** @defgroup SYSCTRL_Public_FunctionDeclaration
 *  @brief SYSCTRL functions declaration
 *  @{
 */

/**
 * @brief      Get Device ID
 *
 * @param[in]  none
 *
 * @return     Device ID
 *
 */   
SYSCTRL_DeviceId_t SYSCTRL_GetDeviceId(void);

/**
 * @brief      Get 128-bit unique ID
 *
 * @param[in]  uniqueId: the start address of a array with 4 32-bit elements.
 *                       the 128-bit unique ID will be written to this array.
 *                       UniqueId[0]: bit 0-31
 *                       UniqueId[1]: bit 63-32
 *                       UniqueId[2]: bit 95-64
 *                       UniqueId[3]: bit 127-96
 *
 * @return     none
 *
 */ 
void SYSCTRL_Get128BitUniqueId(uint32_t uniqueId[]);

/**
 * @brief      reset module
 *
 * @param[in]  mod: select which module to reset. It can select from modules
 *                     defined in type SYSCTRL_Module_t except SYSCTRL_FLASH.
 *
 * @return     none
 *
 */
void SYSCTRL_ResetModule(SYSCTRL_Module_t mod);

/**
 * @brief      Enable module. The module is enabled in normal/wait/stop modes.
 *
 * @param[in]  mod: select which module to enable. 
 *
 * @return     none
 *
 */
void SYSCTRL_EnableModule(SYSCTRL_Module_t mod);

/**
 * @brief      Enable module but the module is off in stop mode.
 *
 * @param[in]  mod: select which module to enable. 
 *
 * @return     none
 * @note       ADC does not support clock off in stop mode, no action is
 *             performed when mod = SYSCTRL_ADC0.
 *
 */
void SYSCTRL_EnableModuleWithOffInStopMode(SYSCTRL_Module_t mod);

/**
 * @brief      Disable module
 *
 * @param[in]  mod: select which module to disable. 
 *
 * @return     none
 * @note        The module clock is switched off after calling this API. 
 *              The register value of the selected module will be reset by 
 *              this API except PORTx and flash modules.
 *              -- The PORTx is more likely to be shared among many modules, 
 *                 so the register values of PORTx are not reset by this API 
 *                 and only the function clock is diabled.
 *                 The pinmux function retains when re-enable PORTx.
 *                 User should use SYSCTRL_ResetModule() to reset PORTx regiters
 *                 if desired.
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

/**
 * @brief      Set Software trigger to TMU
 *
 * @param[in]  source: select software trigger source to TMU
 * @param[in]  level: trigger level to TMU. 
 *
 * @return     none
 *
 */
void SYSCTRL_SoftTriggerToTmu(SYSCTRL_TriggerSrc_t source, SYSCTRL_TriggerLevel_t level);

/**
 * @brief      config SRAM ECC. SRAM ECC is enabled by default. ECC config can be 
 *             changed through this function.
 *
 * @param[in]  sram: select which SRAM to config.
 * @param[in]  eccConfig: points to the struct that stores the parameters. 
 *
 * @return     none
 *
 */
void SYSCTRL_SramEccConfig(SYSCTRL_Sram_t sram, 
                           const SYSCTRL_SramEcc_t *eccConfig);

/**
 * @brief      Get SRAM ECC error status
 *
 * @param[in]  sram: select which SRAM to config.
 * @param[in]  errMask: select the error mask. 
 *
 * @return     
 *        - RESET: the error status is not set
 *        - SET: the error status is set
 *
 */
FlagStatus_t SYSCTRL_GetSramEccErrStatus(SYSCTRL_Sram_t sram, uint32_t errMask);

/**
 * @brief      Clear SRAM ECC error status
 *
 * @param[in]  sram: select which SRAM to config.
 * @param[in]  errMask: select the error mask. 
 *
 * @return none
 *
 */
void SYSCTRL_ClearSramEccErrStatus(SYSCTRL_Sram_t sram, uint32_t errMask);

/**
 * @brief      Get SRAM ECC error cause
 *
 * @param[in]  sram: select which SRAM to config.
 * @param[in]  cause: the cause of SRAM ERR error will be stored in the struct 
 *                    that is pointed by this parameter. 
 *
 * @return none
 *
 */
void SYSCTRL_GetSramEccErrCause(SYSCTRL_Sram_t sram, 
                                         SYSCTRL_SramEccErrCause_t *cause);


/** @} end of group SYSCTRL_Public_FunctionDeclaration */

/** @} end of group SYSCTRL  */

/** @} end of group Z20K11X_Peripheral_Driver */
#endif /* Z20K11XM_SYSCTRL_H */
