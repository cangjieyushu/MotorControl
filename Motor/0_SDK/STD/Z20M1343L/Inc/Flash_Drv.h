/**************************************************************************************************/
/**
 * @file      : Flash_Drv.h
 * @brief     : Flash module driver header file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
#ifndef FLASH_DRV_H
#define FLASH_DRV_H

#include "Common_Drv.h"

/** @addtogroup Public_MacroDefinition
 *  @{
 */
 
/**
 *  @brief size definition for Flash and EEPROM
 */
#if (defined(FLASH_PFLASH))
#define FLASH_PFLASH_SIZE        0x10000U
#define FLASH_PHRASE_SIZE        0x08U
#define FLASH_PAGE_SIZE          0x80U
#define FLASH_SECTOR_SIZE        0x800U
#define FLASH_BLLA_SIZE          0x08U
#define FLASH_BLLA_COUNT         0x10U
#define FLASH_BLLR_ADDR          0x10U
#define FLASH_BLLR_DATA_LEN      0x09U
#endif
#define FLASH_EEPROM_PHRASE_SIZE 0x08U
/** @} end of Public_MacroDefinition */

/** @defgroup Public_TypeDefinition
 *  @{
 */

/**
 *  @brief Flash status type definition
 */
typedef enum
{
    FLASH_STATUS_INIT_FAIL = 0x00000002U,      /*!< Ecc error in initial process */
    FLASH_STATUS_CMDABT = 0x00000004U,         /*!< Command Abort: Command is aborted 
                                                    during execution */
    FLASH_STATUS_ACCERR = 0x00000020U,         /*!< Access Error */
    FLASH_STATUS_PREABT = 0x00000040U,         /*!< Write Sequence Abort: a request to 
                                                    abort a command write sequence prior 
                                                    to command launch has been granted */
    FLASH_STATUS_CCIF = 0x00000080U,           /*!< Command Complete: a flash command has 
                                                    completed */
    FLASH_STATUS_DFDIF = 0x00010000U,          /*!< double bit fault was detected during
                                                    a valid flash read */
    FLASH_STATUS_SFDIF = 0x00020000U,          /*!< single bit fault was detected during
                                                    a valid flash read */
    FLASH_STATUS_DBG_ERSALL_DIS = 0x40000000U, /*!< debug erase all request disable:
                                                    - 1: debug erase all request 
                                                         cannot erase flash
                                                    - 0: debug erase all request
                                                         is allowed to erase flash */
    /*PRQA S 0646 ++*/
    FLASH_STATUS_FSEC = 0x80000000U            /*!< Flash secure:
                                                    - 1: flash is secure
                                                    - 0: flash is not secure */
    /*PRQA S 0646 --*/
}Flash_StatusType;

/**
 *  @brief Flash user actions when execute a command type definition
 */
typedef enum
{
    FLASH_CMD_ACT_WAIT = 0U,    /*!< wait until a command is completed */
    FLASH_CMD_ACT_INT           /*!< enable interrupt and use interrupt to inform
                                     when the command is completed */ 
}Flash_CmdActType;

/**
 *  @brief Flash abort command result type definition
 */
typedef enum
{
    FLASH_ABORT_OK = 0U,      /*!< abort flash command succeeded */
    FLASH_ABORT_FINISHED,     /*!< abort failed, but flash command has been finished  */
    FLASH_ABORT_TIMEOUT       /*!< abort flash command timeout */ 
}Flash_AbortResultType;

/**
 *  @brief Flash secure debug mode type definition
 */
typedef enum
{
    SECURE_DEBUG_OFF = 0U,    /*!< secure debug mode off */
    SECURE_DEBUG_ON,          /*!< secure debug mode on */
    SECURE_DEBUG_ON_ERASE_OFF /*!< secure debug mode on and erase all request cannot erase flash */
} Flash_SecureDebugModeType;

/**
 *  @brief FLASH interrupt mask type definition
 */
typedef enum
{
    FLASH_INT_CCIE_MASK = 0U,    /*!< command complete */
    FLASH_INT_DFDIE_MASK,        /*!< Multi-bit ECC fault */
    FLASH_INT_ALL_MASK           /*!< all interrupt */
}Flash_IntMaskType;

/**
 *  @brief FLASH interrupt flag type definition
 */
typedef enum
{
    FLASH_INT_CCIF_FLAG = 0U,    /*!< command complete */
    FLASH_INT_DFDIF_FLAG,        /*!< Multi-bit ECC fault */
    FLASH_INT_SFDIF_FLAG,        /*!< single-bit ECC fault */
    FLASH_INT_ALL_FLAG           /*!< all interrupt */
}Flash_IntFlagType;

/** 
 *   @brief Call back function pointer data type
 *   If using callback in the application, any code reachable from this function
 *   must not be placed in a Flash block targeted for a program/erase operation.
 *   Functions can be placed in RAM section.
 */
typedef void (* Flash_CallbackType)(void);

/**
 * @brief Flash command Configuration Structure
 */
typedef struct
{
    Flash_CmdActType Act;  /*!< define the actions when the command is executing
                                - FLASH_CMD_ACT_WAIT: wait until a command is completed
                                - FLASH_CMD_ACT_INT: enable interrupt and use interrupt to inform
                                                     when the command is completed */   
    Flash_CallbackType CallBack;  /*!< Call back function to service the time critical 
                                       events. Any code reachable from this function
                                       must not be placed in a Flash block targeted for
                                       a program/erase operation. if "act" parameter is 
                                       set to FLASH_CMD_ACT_WAIT, this callBack is called
                                       when waiting for the completion of command. If
                                       FLASH_CMD_ACT_INT is selected, this parameter can
                                       be ignored a interrupt call back function can be
                                       installed through Flash_InstallCallBackFunc() */
} Flash_CmdConfigType;

/**
 * @brief Flash ECC state Structure
 */
typedef struct
{
    Common_FlagStatusType EccFlag;  /*!< It reflects if an single/multi bit ECC error is detected
                                         - 0: no ECC error
                                         - 1: ECC error is detected */
    Common_FlagStatusType Overrun;  /*!< It reflects if single/multi bit ECC error is overrun
                                         - 0: no overrun
                                         - 1: ECC error is overrun */
    uint32 Addr;                    /*!< If an ECC error is detected, it indicates the
                                         address where ECC error happens */

} Flash_EccStateType;

/** @} end of group Public_TypeDefinition */

/** @defgroup Global_VariableDeclaration
 *  @{
 */

/** @} end of group Global_VariableDeclaration */

/** @defgroup Public_FunctionDeclaration
 *  @{
 */
 
/**
 * @brief      Set flash clock frequency division. Flash program/erase clock must be 8M.
 *
 * @param[in]  SetValue: frequency division to be set.        
 *
 * @return     None
 *
 */
void Flash_SetClockDivision(uint8 SetValue);

/**
 * @brief      Configure a range of Flash area where bus error will not be generated when 
 *             multi-bit ECC error happens.
 *
 * @param[in]  StartAddr[2U]: The start address of flash to ignore bus error. It 
 *                            should be 8-byte aligned, the lowest 3 bits of 
 *                            starAddr shall always be 0.
 * @param[in]  EndAddr[2U]: The end address of flash to ignore bus error. It 
 *                          should be 8-byte aligned, the lowest 3 bits of 
 *                          starAddr shall always be 0.
 *
 * @return     None
 *
 */
void Flash_IgnoreBusErrorConfig(uint32 StartAddr[2U], uint32 EndAddr[2U]);

/**
 * @brief      Program EEPROM main array by phrase (8 bytes).
 *
 * @param[in]  EepromAddr: Start address of EEPROM main array. It is the start address of 
 *                         a phrase. This address should be aligned to 8 bytes.
 * @param[in]  DataPtr: Points to data to be programmed into EEPROM.
 * @param[in]  ConfigType: Config the action when the command is executing.
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed or started.
 * @retval     COMMON_ERR: Parameters invalid, command execution error or timeout.
 * @retval     COMMON_BUSY: Flash command execution is ongoing.
 *
 */
Common_ResultStatusType Eeprom_ProgramEepromPhrase(uint32 EepromAddr, const uint8 *DataPtr, 
                                   const Flash_CmdConfigType *ConfigType);

/**
 * @brief      Program EEPROM main array.
 *
 * @param[in]  EepromAddr: Start address of EEPROM memory. It is the start address of 
 *                         a phrase. This address should be aligned to 8 bytes.
 * @param[in]  Len: Length in byte to be programmed. it should be aligned to 8 bytes.
 * @param[in]  DataPtr: Points to data to be programmed into EEPROM.
 * @param[in]  CallBack: The callBack function when waiting for command executing.
 *
 * @note       If CallBack is not NULL, it has to point to a function 
 *             that is not in the flash memory where flash commands is executing.
 * 
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed or started.
 * @retval     COMMON_ERR: Parameters invalid, command execution error or timeout or compare failed.
 * @retval     COMMON_BUSY: Flash command execution is ongoing.
 *
 */   
Common_ResultStatusType Eeprom_ProgramEeprom(uint32 EepromAddr, uint32 Len, const uint8 *DataPtr, 
                                           Flash_CallbackType CallBack);

#if (defined(FLASH_PFLASH))
/**
 * @brief      Pre-write function to write data to flash bit line latches BLLA.
 *
 * @param[in]  BllaNum: Blla number ranges from 0 to 15.
 * @param[in]  DataPtr: Points to data to be written into BLLA specified by BllaNum.
 * @param[in]  ConfigType: Config the action when the command is executing.
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed or started.
 * @retval     COMMON_ERR: Command execution error or timeout.
 * @retval     COMMON_BUSY: Flash command execution is ongoing.
 *
 */
Common_ResultStatusType Flash_PreWriteBlla(uint32 BllaNum, const uint8 *DataPtr, 
                                   const Flash_CmdConfigType *ConfigType);

/**
 * @brief      Pre-write function to write data to bit line latches BLLR.
 *
 * @param[in]  ConfigType: Config the action when the command is executing.
 *
 * @return     Common_ResultStatusType.
 * @retval     COMMON_SUCC: Command successfully executed or started.
 * @retval     COMMON_ERR: Command execution error or timeout.
 * @retval     COMMON_BUSY: Flash command execution is ongoing.
 *
 */
Common_ResultStatusType Flash_PreWriteBllr(const Flash_CmdConfigType *ConfigType);

/**
 * @brief      Program Flash main array by page (128 bytes).
 *
 * @param[in]  FlashAddr: Start address of Flash main array. It is the start address of 
 *                        a page. This address should be aligned to 128 bytes.
 * @param[in]  ConfigType: Config the action when the command is executing.
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed or started.
 * @retval     COMMON_ERR: Parameters invalid, or command execution error or timeout.
 * @retval     COMMON_BUSY: Flash command execution is ongoing.
 *
 */
Common_ResultStatusType Flash_ProgramPage(uint32 FlashAddr, const Flash_CmdConfigType *ConfigType);

/**
 * @brief      Program Flash main array.
 *
 * @param[in]  FlashAddr: Start address of Flash main array. It is the start address of 
 *                        a page. This address should be aligned to 128 bytes.
 * @param[in]  Len: Length in byte to be programmed into Flash main array.
 *                  This length should be aligned to 128 bytes.
 * @param[in]  DataPtr: Points to data to be programmed into Flash main array.
 * @param[in]  CallBack: The callBack function when waiting for command executing.
 *
 * @note       If CallBack is not NULL, it has to point to a function 
 *             that is not in the flash memory where flash commands is executing.
 * 
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed or started.
 * @retval     COMMON_ERR: Parameters invalid, command execution error or timeout or compare failed.
 * @retval     COMMON_BUSY: Flash command execution is ongoing.
 *
 */
Common_ResultStatusType Flash_Program(uint32 FlashAddr, uint32 Len, const uint8 *DataPtr,
                                        Flash_CallbackType CallBack);

/**
 * @brief      Erase all flash and EEPROM main array.
 *
 * @param[in]  ConfigType: Config the action when the command is executing.
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed or started.
 * @retval     COMMON_ERR: Command execution error or timeout.
 * @retval     COMMON_BUSY: Flash command execution is ongoing.
 *
 */
Common_ResultStatusType Flash_EraseAll(const Flash_CmdConfigType *ConfigType);

/**
 * @brief      Erase flash main array by sector (2 KBytes).
 *
 * @param[in]  Addr: Start address of Flash main array. It is the start address of a sector. 
 *                   This address should be aligned to 2K bytes.
 * @param[in]  ConfigType: Config the action when the command is executing.
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed or started.
 * @retval     COMMON_ERR: Parameters invalid, or command execution error or timeout.
 * @retval     COMMON_BUSY: Flash command execution is ongoing.
 *
 */
Common_ResultStatusType Flash_EraseSector(uint32 Addr, const Flash_CmdConfigType *ConfigType);

/**
 * @brief      Set security debug mode. In this mode, debug Port is prevented
 *             to read any AHB-AP memory-map addresses.
 *
 * @param[in]  EraseAll: Enable/Disable erase-all debug.
 *                         - COMMON_ENABLE: Erase all request is allowed to erase flash.
 *                         - COMMON_DISABLE: Erase all request cannot erase flash.
 * @param[in]  Key[]: Decry key used to unlock the debug port and access the chip.
 * @param[in]  Config: Config the action when the command is executing.
 *
 * @return     Common_ResultStatusType  
 * @retval     COMMON_SUCC: Command successfully executed or started.
 * @retval     COMMON_ERR: Parameters invalid, or command execution error or timeout.
 * @retval     COMMON_BUSY: Flash command execution is ongoing.
 *
 */
Common_ResultStatusType Flash_ConfigSecureDebugMode(Common_ControlStateType EraseAll, 
                                                    uint8 Key[], 
                                                    const Flash_CmdConfigType *ConfigType);
#endif

/**
 * @brief      Get secure debug mode status.
 *
 * @param[in]  None
 *
 * @return     Flash_SecureDebugModeType
 * @retval     SECURE_DEBUG_OFF: Secure debug mode off.
 * @retval     SECURE_DEBUG_ON: Secure debug mode on.
 * @retval     SECURE_DEBUG_ON_ERASE_OFF: Secure debug mode on and 
 *                                        erase all request cannot erase flash.
 *
 */
Flash_SecureDebugModeType Flash_GetSecureDebugMode(void);

/**
 * @brief      Open secure debug port.
 *
 * @param[in]  Key[]: Authentication session key to be imported.
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Open secure debug port successfully.
 * @retval     COMMON_ERR: Open secure debug port failed.
 * @retval     COMMON_BUSY: Flash command execution is ongoing.
 *
 */
Common_ResultStatusType Flash_OpenSecureDebugPort(uint8 Key[]);

/**
 * @brief      Get FLASHC status.
 *
 * @param[in]  Stat: Status needs to be get.
 *               - FLASH_STATUS_INIT_FAIL: Ecc error in initial process.
 *               ......
 *               - FLASH_STATUS_FSEC: Flash secure status.
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_RESET: Reset state.
 * @retval     COMMON_SET: Set state.
 *
 */ 
Common_FlagStatusType Flash_GetStatus(Flash_StatusType Stat);

/**
 * @brief      Request to abort a command write sequence.
 *
 * @param[in]  None
 *
 * @return     Flash_AbortResultType
 * @retval     FLASH_ABORT_OK: Abort flash command succeeded.
 * @retval     FLASH_ABORT_FINISHED: Abort failed, but flash command has been finished.
 * @retval     FLASH_ABORT_TIMEOUT: Abort flash command timeout.
 *
 */
Flash_AbortResultType Flash_AbortCommand(void);

/**
 * @brief       EEPROM ECC read control.
 *
 * @param[in]   NewStatus: EEPROM ECC read status :
 *                   - COMMON_ENABLE: EEPROM ECC read enable
 *                   - COMMON_DISABLE: EEPROM ECC read disable
 *
 * @return      None
 *
 * @note        This field is protected by global write lock.
 *              Refer to RM System Control Module for more infomation.
 * 
 */
void Flash_SetEepromReadEccEnable(Common_ControlStateType NewStatus);

/**
 * @brief       Flash ECC read control.
 *
 * @param[in]   NewStatus: Flash ECC read status :
 *                   - COMMON_ENABLE: Flash ECC read enable
 *                   - COMMON_DISABLE: Flash ECC read disable
 *
 * @return      None
 *
 * @note        This field is protected by global write lock.
 *              Refer to RM System Control Module for more infomation.
 * 
 */
void Flash_SetFlashReadEccEnable(Common_ControlStateType NewStatus);

/**
 * @brief       Get Flash single-bit ECC error state.
 *
 * @param[out]  State: It points to a struct where the Ecc state will be stored.
 *
 * @return      None
 *
 */
void Flash_GetSingleBitEccState(Flash_EccStateType *State);

/**
 * @brief       Get Flash multi-bit ECC error state.
 *
 * @param[out]  State: It points to a struct where the Ecc state will be stored.
 *
 * @return      None
 *
 */
void Flash_GetMultiBitEccState(Flash_EccStateType *State);

/**
 * @brief      Clear Flash single-bit ECC error state.
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void Flash_ClearSingleBitEccState(void);

/**
 * @brief      Clear Flash multi-bit ECC error state.
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void Flash_ClearMultiBitEccState(void);

/**
 * @brief      Install callback function.
 *
 * @param[in]  CallbackFun: Indicate callback function.
 *
 * @return     None
 *
 */
void Flash_InstallCallBackFunc(Isr_CbFuncType * CallbackFun);

/**
 * @brief      Mask/Unmask command complete interrupt.
 *
 * @param[in]  IntType: select interrupt type
 * @param[in]  IntMask: Interrupt MASK or UNMASK.
 *               - COMMON_UNMASK: Interrupt unmask.
 *               - COMMON_MASK: Interrupt mask.
 *
 * 
 * @return     None
 *
 */
void Flash_SetIntMask(Flash_IntMaskType IntType, Common_IntMaskType IntMask);

/**
 * @brief      Clear command complete interrupt flag.
 *
 * @param[in]  IntType: select interrupt type
 *
 * @return     None
 *
 */
void Flash_ClearIntFlag(Flash_IntFlagType IntType);

/**
 * @brief      Flash initialization.
 *
 * @param[in]  None
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Flash initialization success.
 * @retval     COMMON_ERR: Flash initialization failed.
 *
 */
Common_ResultStatusType Flash_Init(void);

/** @} end of group Public_FunctionDeclaration */

#endif /* FLASH_DRV_H */

