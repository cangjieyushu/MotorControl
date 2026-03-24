/**************************************************************************************************/
/**
 * @file     flash_drv.h
 * @brief    FLASH driver module header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#ifndef FLASH_DRV_H
#define FLASH_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  FLASH
 *  @{
 */

/** @defgroup FLASH_Public_Types 
 *  @{
 */

/**
 *  @brief FLASH status mask definition
 */

#define FLASH_STATUS_FAIL_MASK           0x00000001U /*!< command fail */
#define FLASH_STATUS_CMDABT_MASK         0x00000004U /*!< Command Abort */
#define FLASH_STATUS_ACCERR_MASK         0x00000020U /*!< Access Error */
#define FLASH_STATUS_PREABT_MASK         0x00000040U /*!< Write Sequence Abort */
#define FLASH_STATUS_CCIF_MASK           0x00000080U /*!< Command Complete */
#define FLASH_STATUS_CMDWRF_MASK         0x00000800U /*!< Flash command registers written */
#define FLASH_STATUS_DFDIF_MASK          0x00010000U /*!< Multi-bit ECC fault */
#define FLASH_STATUS_SFDIF_MASK          0x00020000U /*!< Single-bit ECC fault */
#define FLASH_STATUS_DBG_ERSALL_DIS_MASK 0x40000000U /*!< debug erase all request disable */
#define FLASH_STATUS_FSEC_MASK           0x80000000U /*!< Flash secure state */

/**
 *  @brief FLASH interrupt type definition
 */
typedef enum
{
    FLASH_INT_CCIF = 0U,    /*!< command complete */
    FLASH_INT_DFDIF,        /*!< Multi-bit ECC fault */
    FLASH_INT_SFDIF,        /*!< single-bit ECC fault */
    FLASH_INT_ALL           /*!< all interrupt */
}FLASH_Int_t;

/**
 *  @brief FLASH user actions when execute a command type definition
 */
typedef enum
{
    FLASH_CMD_ACT_WAIT = 0U,    /*!< wait until a command is completed */
    FLASH_CMD_ACT_INT           /*!< enable interrupt and use interrupt to inform
                                     when the command is completed */ 
}FLASH_CmdAct_t;


/**
 *  @brief FLASH abort command result type definition
 */
typedef enum
{
    FLASH_ABORT_OK = 0U,      /*!< abort flash command succeeded */
    FLASH_ABORT_FINISHED,     /*!< abort failed, but flash command has been finished  */
    FLASH_ABORT_TIMEOUT,      /*!< abort flash command timeout */ 
}FLASH_AbortResult_t;

/** 
 *   @brief Call back function pointer data type
 *   If using callback in the application, any code reachable from this function
 *   must not be placed in a Flash block targeted for a program/erase operation.
 *   Functions can be placed in RAM section.
 */
typedef void (* flash_cb_t)(void);

/**
 * @brief Flash command Configuration Structure
 */
typedef struct
{
    FLASH_CmdAct_t act;   /*!< define the actions when the command is executing
                               - FLASH_CMD_ACT_WAIT: wait until a command is completed
                               - FLASH_CMD_ACT_INT: enable interrupt and use interrupt to inform
                                     when the command is completed */   
    flash_cb_t callBack;   /*!< Call back function to service the time critical 
                                events. Any code reachable from this function
                                must not be placed in a Flash block targeted for
                                a program/erase operation. if "act" parameter is 
                                set to FLASH_CMD_ACT_WAIT, this callBack is called
                                when waiting for the completion of command. If
                                FLASH_CMD_ACT_INT is selected, this parameter can
                                be ignored a interrupt call back function can be
                                installed through FLASH_InstallCallBackFunc() */
} FLASH_CmdConfig_t;

/**
 * @brief Flash ECC state Structure
 */
typedef struct
{
    FlagStatus_t eccFlag;   /*!< It reflects if an single/multi bit ECC error is
                                 detected
                               - RESET: no ECC error
                               - SET: ECC error is detected */
    FlagStatus_t overrun;   /*!< It reflects if single/multi bit ECC error is 
                                 overrun
                               - RESET: no overrun
                               - SET: ECC error is overrun */
    uint32_t addr;          /*!< If an ECC error is detected, it indicates the
                                 address where ECC error happens */

} FLASH_EccState_t;

/** @} end of group FLASH_Public_Types */

/** @defgroup FLASH_Public_Constants
 *  @{
 */

/** @} end of group FLASH_Public_Constants */

/** @defgroup FLASH_Public_Macro
 *  @{
 */

/** @} end of group FLASH_Public_Macro */

/** @defgroup FLASH_Public_FunctionDeclaration
 *  @brief FLASH functions declaration
 *  @{
 */

/**
 * @brief      configure a range of Flash to not generate bus error when 
 *             multi-bit ECC error happens.
 *
 * @param[in]  startAddr: The start address of flash to ignore bus error. It 
 *                        should be 16-byte aligned, the lowest 4 bits of 
 *                        starAddr shall always be 0.
 * @param[in]  endAddr: The end address of flash to ignore bus error. It 
 *                        should be 16-byte aligned, the lowest 4 bits of 
 *                        starAddr shall always be 0.
 *
 * @return     none
 *
 */
void FLASH_IgnoreBusErrorConfig(uint32_t startAddr, uint32_t endAddr);

/**
 * @brief      Verify all flash and IFR space are in the erased state
 *
 * @param[in]  config: config the action when the command is executing
 *
 * @note       if config->callBack is not NULL, it has to point to a funtion 
 *             that is not in flash memory
 *
 * @return     
 *             - SUCC -- successful
 *             - ERR --  some error
 *             - BUSY -- flash is executing last command. It can not execute this  
 *                       new command now.  
 *
 */
ResultStatus_t FLASH_VerifyAll(const FLASH_CmdConfig_t *config);


/**
 * @brief      Verify that a flash block is erased
 *
 * @param[in]  addr: block start address
 * @param[in]  config: config the action when the command is executing
 *
 * @note       if config->callBack is not NULL, it has to point to a funtion 
 *             that is not in the flash memory that flash commands is executing
 *             in.
 *
 * @return     - SUCC -- successful
 *             - ERR --  some error
 *             - BUSY -- flash is executing last command. It can not execute this  
 *                       new command now.  
 *
 */   
ResultStatus_t FLASH_VerifyBlock(uint32_t addr,
                                 const FLASH_CmdConfig_t *config);

/**
 * @brief      Verify that a flash sector is erased
 *
 * @param[in]  addr: sector start address
 * @param[in]  config: config the action when the command is executing
 *
 * @note       if config->callBack is not NULL, it has to point to a funtion 
 *             that is not in the flash memory that flash commands is executing
 *             in.
 *
 * @return     - SUCC -- successful
 *             - ERR -- some error
 *             - BUSY -- flash is executing last command. It can not execute this  
 *                       new command now. 
 *
 */   
ResultStatus_t FLASH_VerifySector(uint32_t addr,
                                  const FLASH_CmdConfig_t *config);
     
/**
 * @brief      Verify that a flash page is erased
 *
 * @param[in]  addr: page start address
 * @param[in]  config: config the action when the command is executing
 *
 * @note       if config->callBack is not NULL, it has to point to a funtion 
 *             that is not in the flash memory that flash commands is executing
 *             in.
 *
 * @return     - SUCC -- successful
 *             - ERR -- some error
 *             - BUSY -- flash is executing last command. It can not execute this  
 *                       new command now.  
 *
 */   
ResultStatus_t FLASH_VerifyPage(uint32_t addr,
                                const FLASH_CmdConfig_t *config);
     
/**
 * @brief      Verify that a flash phrase is erased
 *
 * @param[in]  addr: phrase start address
 * @param[in]  config: config the action when the command is executing
 *
 * @note       if config->callBack is not NULL, it has to point to a function 
 *             that is not in the flash memory that flash commands is executing
 *             in.
 *
 * @return     - SUCC -- successful
 *             - ERR -- some error
 *             - BUSY -- flash is executing last command. It can not execute this  
 *                       new command now.  
 *
 */   
ResultStatus_t FLASH_VerifyPhrase(uint32_t addr,
                                  const FLASH_CmdConfig_t *config);

/**
 * @brief      Generate MISR signature for flash pages
 *
 * @param[in]  startAddr: page start address
 * @param[in]  endAddr: Ending phrase address. It must be the last phrase in a page.
 * @param[in]  seed: the pointer that points to the 4-word seed
 * @param[in]  signature: the pointer that points the memory that the 128-bit 
 *                        signature result that will be stored through this function.
 *                        it is only valid when config->act == FLASH_CMD_ACT_WAIT.
 *                       If config->act == FLASH_CMD_ACT_WAIT, the result is not stored
 * @param[in]  config: config the action when the command is executing. If
 *                     FLASH_CMD_ACT_WAIT is selected, the result is stored in
 *                     signature[4]. If FLASH_CMD_ACT_INT is selected, the result
 *                     is not selected. user can get the result in the interrupt
 *                     call back function
 *
 * @note       if config->callBack is not NULL, it has to point to a function 
 *             that is not in the flash memory that flash commands is executing
 *             in.
 *
 * @return     - SUCC -- successful
 *             - ERR -- some error
 *             - BUSY -- flash is executing last command. It can not execute this  
 *                       new command now. 
 *
 */   
ResultStatus_t FLASH_PagesMircSignature(uint32_t startAddr, uint32_t endAddr,
                                        uint32_t seed[4], uint32_t signature[4],
                                        const FLASH_CmdConfig_t *config);
 
/**
 * @brief      Verify that a flash IFR sector is erased
 *
 * @param[in]  addr: sector start address. 
 * @param[in]  config: config the action when the command is executing
 *
 * @note       if config->callBack is not NULL, it has to point to a funtion 
 *             that is not in the flash memory that flash commands is executing
 *             in.
 *
 * @return     - SUCC -- successful
 *             - ERR -- some error
 *             - BUSY -- flash is executing last command. It can not execute this  
 *                       new command now. 
 *
 */   
ResultStatus_t FLASH_VerifyIfrSector(uint32_t addr,
                                     const FLASH_CmdConfig_t *config);
     
/**
 * @brief      Verify that a flash IFR page is erased
 *
 * @param[in]  addr: IFR page start address
 * @param[in]  config: config the action when the command is executing
 *
 * @note       if config->callBack is not NULL, it has to point to a funtion 
 *             that is not in the flash memory that flash commands is executing
 *             in.
 *
 * @return     - SUCC -- successful
 *             - ERR -- some error 
 *             - BUSY -- flash is executing last command. It can not execute this  
 *                       new command now. 
 *
 */   
ResultStatus_t FLASH_VerifyIfrPage(uint32_t addr,
                                   const FLASH_CmdConfig_t *config);
     
/**
 * @brief      Verify that a flash IFR phrase is erased
 *
 * @param[in]  addr: IFR phrase start address
 * @param[in]  config: config the action when the command is executing
 *
 * @note       if config->callBack is not NULL, it has to point to a funtion 
 *             that is not in the flash memory that flash commands is executing
 *             in.
 *
 * @return     - SUCC -- successful
 *             - ERR -- some error 
 *             - BUSY -- flash is executing last command. It can not execute this  
 *                       new command now. 
 *
 */   
ResultStatus_t FLASH_VerifyIfrPhrase(uint32_t addr,
                                     const FLASH_CmdConfig_t *config);

/**
 * @brief      Generate MISR signature for flash IFR pages
 *
 * @param[in]  startAddr: page start address
 * @param[in]  endAddr: Ending phrase address. It must be the last phrase in a page.
 * @param[in]  seed: the pointer that points to the 4-word seed
 * @param[in]  signature: the pointer that points the memory that the 128-bit 
 *                        signature result that will be stored through this function.
 *                        it is only valid when config->act == FLASH_CMD_ACT_WAIT.
 *                       If config->act == FLASH_CMD_ACT_WAIT, the result is not stored
 * @param[in]  config: config the action when the command is executing. If
 *                     FLASH_CMD_ACT_WAIT is selected, the result is stored in
 *                     signature[4]. If FLASH_CMD_ACT_INT is selected, the result
 *                     is not selected. user can get the result in the interrupt
 *                     call back function
 *
 * @note       if config->callBack is not NULL, it has to point to a funtion 
 *             that is not in the flash memory that flash commands is executing
 *             in.
 *
 * @return     - SUCC -- successful
 *             - ERR -- some error
 *             - BUSY -- flash is executing last command. It can not execute this  
 *                       new command now.  
 *
 */   
ResultStatus_t FLASH_IfrPagesMircSignature(uint32_t startAddr, uint32_t endAddr,
                                        uint32_t seed[4], uint32_t signature[4],
                                        const FLASH_CmdConfig_t *config);

/**
 * @brief      program a Dflash phrase
 *
 * @param[in]  flashAddr: phrase start address to be programmed
 * @param[in]  dataP: points to data to be programmed into flash
 * @param[in]  config: config the action when the command is executing
 *
 * @note       if config->callBack is not NULL, it has to point to a funtion 
 *             that is not in the flash memory that flash commands is executing
 *             in.
 *
 * @return     - SUCC -- successful.
 *             - ERR -- invalid input address, or command execution error or timeout.
 *             - BUSY -- flash is executing last command. It can not execute this  
 *                       new command now. 
 *
 */
ResultStatus_t FLASH_ProgramDflashPhrase(uint32_t flashAddr, const uint8_t *dataP, 
                                         const FLASH_CmdConfig_t *config);
/**
 * @brief      program a flash phrase
 *
 * @param[in]  flashAddr: phrase start address to be programmed
 * @param[in]  dataP: points to data to be programmed into flash
 * @param[in]  config: config the action when the command is executing
 *
 * @note       if config->callBack is not NULL, it has to point to a funtion 
 *             that is not in the flash memory that flash commands is executing
 *             in.
 *
 * @return     - SUCC -- successful
 *             - ERR -- some error 
 *             - BUSY -- flash is executing last command. It can not execute this  
 *                       new command now. 
 *
 */
ResultStatus_t FLASH_ProgramPhrase(uint32_t flashAddr, const uint8_t *dataP, 
                                   const FLASH_CmdConfig_t *config);
     
/**
 * @brief      program flash memory
 *
 * @param[in] flashAddr: start address of flash memory. It is the start address of 
 *                   a phrase. This address should be aligned to 4 words(16 bytes)
 * @param[in] len: length in byte to be programmed.
 *                 This length should be aligned to 4 words(16 bytes).
 * @param[in] dataP: points to the source buffer from which data is taken 
 *                     for program operation.
 * @param[in]  callBack: the callBack function when waiting for command executing
 *
 * @note       if callBack is not NULL, it has to point to a funtion 
 *             that is not in the flash memory that flash commands is executing
 *             in.
 *
 * @return     - SUCC -- successful
 *             - ERR -- some error
 *             - BUSY -- flash is executing last command. It can not execute this  
 *                       new command now.  
 *
 */   
ResultStatus_t FLASH_Program(uint32_t flashAddr, uint32_t len, const uint8_t *dataP,
                             flash_cb_t callBack);


/**
 * @brief      Erase all flash and IFR space
 *
 * @param[in]  config: config the action when the command is executing
 *
 * @note       if config->callBack is not NULL, it has to point to a funtion 
 *             that is not in the flash memory 
 *
 * @return     - SUCC -- successful
 *             - ERR -- some error
 *             - BUSY -- flash is executing last command. It can not execute this  
 *                       new command now. 
 *
 */
ResultStatus_t FLASH_EraseAll(const FLASH_CmdConfig_t *config);

/**
 * @brief      Erase a Dflash sector
 *
 * @param[in]  addr: DFlash sector start address. It shall be aligned to 8K bytes.
 * @param[in]  config: config the action when the command is executing
 *
 * @note       if config->callBack is not NULL, it has to point to a funtion 
 *             that is not in the flash memory that flash commands is executing
 *             in.
 *
 * @return     - SUCC -- successful.
 *             - ERR -- invalid input address, or command execution error or timeout.
 *             - BUSY -- flash is executing last command. It can not execute this  
 *                       new command now.  
 *
 */
ResultStatus_t FLASH_EraseDflashSector(uint32_t addr, const FLASH_CmdConfig_t *config);

/**
 * @brief      Erase a flash sector
 *
 * @param[in]  addr: sector start address
 * @param[in]  config: config the action when the command is executing
 *
 * @note       if config->callBack is not NULL, it has to point to a funtion 
 *             that is not in the flash memory that flash commands is executing
 *             in.
 *
 * @return     - SUCC -- successful
 *             - ERR -- some error
 *             - BUSY -- flash is executing last command. It can not execute this  
 *                       new command now.  
 *
 */
ResultStatus_t FLASH_EraseSector(uint32_t addr, const FLASH_CmdConfig_t *config);

/**
 * @brief      Flash enters security mode. In this mdoe, debug Port is prevented
 *             to read any AHB-AP memory-map addresses
 *
 * @param[in]  debugEraseAllEn: Enable/Disable debug erase-all.
 *                             - ENABLE: debug erase all request is allowed to 
 *                                       erase flash
 *                             - DISABLE: debug erase all request cannot erase flash
 * @param[in]  config: config the action when the command is executing
 *
 * @note       if config->callBack is not NULL, it has to point to a funtion 
 *             that is not in the flash memory that flash commands is executing
 *             in.
 *
 * @return     - SUCC -- successful
 *             - ERR -- some error
 *             - BUSY -- flash is executing last command. It can not execute this  
 *                       new command now.  
 *
 */
ResultStatus_t FLASH_EnterSecurityMode(ControlState_t debugEraseAllEn,
                                       const FLASH_CmdConfig_t *config);

/**
 * @brief      Set wait state. If the system clock frequency is higher than
 *             flash clock, some wait-states are required to be added to wait
 *             for flash data ready.
 *
 * @param[in]  cycle: number of additional wait-state is added. 
 *                    Its range is 0-15.
 *
 * @return    none
 *
 */ 
void FLASH_SetWaitState(uint8_t cycle);

/**
 * @brief      Get FLASHC status
 *
 * @param[in]  statMask: the status to be get
 *
 * @return    the status
 *
 */ 
FlagStatus_t FLASH_GetStatus(uint32_t statMask);

/**
 * @brief      Inject ECC error into FLASH 
 *
 * @param[in]  addr: the address at which Ecc will be injected. It should be 
 *                   16-byte aligned.
 * @param[in]  eccBits: It indicates which bits in 9-bit Ecc part will be 
 *                      injected error. Only bit 0-9 in eccBits is
 *                      valid. If one bit is 0, no error is injected into this
 *                      bit; if one bit is 1, this bit will be inverted on 
 *                      reading.
 * @param[in]  dataBits: It indicates which bits in 128-bit data part will be
 *                       injected error. If one bit is 0, no error is injected 
 *                       into this bit; if one bit is 1, this bit will be 
 *                       inverted on reading. It points to an array with 
 *                       4 elements, each element is 32-bit.
 *                       dataBits[0] : data bit 0 - data bit31
 *                       dataBits[1] : data bit 32 - data bit63
 *                       dataBits[2] : data bit 64 - data bit95
 *                       dataBits[3] : data bit 96 - data bit127 
 *
 * @return    none
 *
 */ 
void FLASH_InjectEcc(uint32_t addr, uint32_t eccBits, uint32_t dataBits[4]);
     
/**
 * @brief      Disable ECC error injection into FLASH 
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void FLASH_DisableEccInjection(void);

/**
 * @brief      Get FLASH single-bit ECC error state
 *
 * @param[out]  stat: it points to a struct where the Ecc state will be stored
 *
 * @return    none
 *
 */ 
void FLASH_GetSingleBitEccState(FLASH_EccState_t *state);
     
/**
 * @brief      Get FLASH multi-bit ECC error state
 *
 * @param[out]  stat: it points to a struct where the Ecc state will be stored
 *
 * @return    none
 *
 */ 
void FLASH_GetMultiBitEccState(FLASH_EccState_t *state);

/**
 * @brief      Clear FLASH single-bit ECC error state
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void FLASH_ClearSingleBitEccState(void);

/**
 * @brief      Clear FLASH multi-bit ECC error state
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void FLASH_ClearMultiBitEccState(void);

/**
 * @brief      Query if the key entered is correct. If it is correct, exit 
 *             secure mode
 *
 * @param[in]  key: it points to the 96-bit key to be entered.
 *
 * @return     none
 *
 */
void FLASH_QueryKey(uint8_t key[12]);

/**
 * @brief      Request to abort a command write sequence
 *
 * @param[in]  none
 *
 * @note       none
 *
 * @return - FLASH_ABORT_OK        -- abort flash command succeeded
 *         - FLASH_ABORT_FINISHED  -- abort failed, but flash command has been finished
 *         - FLASH_ABORT_TIMEOUT   -- abort flash command timeout
 *
 */
FLASH_AbortResult_t FLASH_AbortCommand(void);

/**
 * @brief      Mask/Unmask interrupt
 *
 * @param[in]  intType: select interrupt type
 * @param[in]  intMask: MASK/UNMASK
 *
 * @return    none
 *
 */
void FLASH_IntMask(FLASH_Int_t intType, IntMask_t intMask);

/**
 * @brief      Clear interrupt
 *
 * @param[in]  intType: select interrupt type
 *
 * @return    none
 *
 */ 
void FLASH_IntClear(FLASH_Int_t intType);

/**
 * @brief      Install FLASH callback function
 *
 * @param[in]  intType: select interrupt type
 * @param[in]  cbFun: indicate callback function
 *
 * @return    none
 *
 */ 
void FLASH_InstallCallBackFunc(FLASH_Int_t intType, isr_cb_t * const cbFun);

/**
 * @brief      flash init
 *
 * @param[in]  none
 *
 * @return     - SUCC -- Initialization succeeded.
 *             - ERR  -- Initialization failed.
 *
 */ 
ResultStatus_t FLASH_Init(void);

/** @} end of group FLASH_Public_FunctionDeclaration */

/** @} end of group FLASH  */

/** @} end of group Z20K14XM_Peripheral_Driver */
#endif /* FLASH_DRV_H */
