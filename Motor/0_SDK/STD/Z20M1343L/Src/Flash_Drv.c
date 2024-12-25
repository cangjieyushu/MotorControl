/**************************************************************************************************/
/**
 * @file      : Flash_Drv.c
 * @brief     : Flash module driver file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#include "Flash_Drv.h"

/** @defgroup Private_MacroDefinition
 *  @{
 */
/**
 *  @brief security debug control start address 
 */
#if (defined(FLASH_PFLASH))
    #define FLASH_SECDEBUG_CTRL_ADDR     ((uint32)FLASH_CODE_BASE_ADDR + 3U * FLASH_PAGE_SIZE)
#endif

#define FLASH_RECOVERY_TIME_VAL (0x64U)

#define FLASH_CMD_ERR_STATUS   ((uint32)FLASH_STATUS_CMDABT | (uint32)FLASH_STATUS_ACCERR)

#define FLASH_CMDABT_MASK      (uint32)FLASH_STATUS_CMDABT
#define FLASH_ACCERR_MASK      (uint32)FLASH_STATUS_ACCERR
#define FLASH_PREABT_MASK      (uint32)FLASH_STATUS_PREABT
#define FLASH_CCIE_MASK        (0x00000100U)
#define FLASH_DFDIE_MASK       (0x00000200U)
#define FLASH_ALL_MASK          (FLASH_CCIE_MASK | FLASH_DFDIE_MASK)
#define FLASH_CMD_ERR_MASK     ((uint32)FLASH_CMDABT_MASK   \
                                | (uint32)FLASH_ACCERR_MASK | (uint32)FLASH_PREABT_MASK)     

#define FLASH_EEPROM_END_ADDR  (EEPROM_BASE_ADDR + EEPROM_SIZE -1U)
#define FLASH_VALID_EEPROM_ADDR(addr)   (((addr) >= EEPROM_BASE_ADDR) \
                                            && ((addr) <= FLASH_EEPROM_END_ADDR))
#define FLASH_SFDIF_FLAG       (uint32)FLASH_STATUS_SFDIF
#define FLASH_DFDIF_FLAG       (uint32)FLASH_STATUS_DFDIF
#define FLASH_CCIF_FLAG        (uint32)FLASH_STATUS_CCIF
#define FLASH_ECC_FLAG         (FLASH_DFDIF_FLAG | FLASH_SFDIF_FLAG)
/** @} end of Private_MacroDefinition */

/** @defgroup Private_TypeDefinition
 *  @{
 */
 
/**
 *  @brief Flash command type definition
 */
typedef enum
{
    FLASH_CMD_EE_PROG      = 1U,   /*!< Program EEPROM array by phrase(8 Bytes) */
    FLASH_CMD_FL_SEC_ERASE = 2U,   /*!< Erase flash array by sector(2 KBytes) */
    FLASH_CMD_FL_PROG      = 3U,   /*!< Program flash array by page(128 Bytes) */
    FLASH_CMD_ERASE_ALL    = 4U,   /*!< Erase all flash and EEPROM main array */
    FLASH_CMD_BLL_WRITE    = 5U    /*!< Write data to BLLA/BLLR, used for flash pre-write */
}Flash_CmdType;

/** @} end of group Private_TypeDefinition */

/** @defgroup Global_VariableDefinition
 *  @{
 */

/** @} end of group Global_VariableDefinition */

/** @defgroup Private_VariableDefinition
 *  @{
 */
 
/*PRQA S 0303 ++*/
static Reg_Flash_BfType *const Flash_RegBfPtr = (Reg_Flash_BfType *) FLASHC_BASE_ADDR;
static Reg_Flash_WType *const Flash_RegWPtr = (Reg_Flash_WType *) FLASHC_BASE_ADDR;
/*PRQA S 0303 --*/

static Isr_CbFuncType * Flash_IsrCbFun = NULL_PTR;

static const uint32 Flash_InterruptFlagTable[] =
{
    FLASH_CCIF_FLAG,      /* FLASH_INT_CCIF */
    FLASH_DFDIF_FLAG,     /* FLASH_INT_DFDIF */
    FLASH_SFDIF_FLAG,     /* FLASH_INT_SFDIF */
    FLASH_ECC_FLAG        /* FLASH_INT_ALL */
};

static const uint32 Flash_InterruptMaskTable[] =
{
    FLASH_CCIE_MASK,      /* FLASH_INT_CCIE */
    FLASH_DFDIE_MASK,     /* FLASH_INT_DFDIE */
    FLASH_ALL_MASK        /* FLASH_INT_ALL */
};

static const uint32 Flash_IntStatus = 0x00000080U;

static uint32 Flash_IntMaskStatus = 0xFFFFFF7FU;

/** @} end of group Private_VariableDefinition */

/** @defgroup Private_FunctionDeclaration
 *  @{
 */
void Flash_EraseProgram_DriverIrqHandler(void);

#if (1 == FLASH_CMD_FUNC_IN_RAM)
/*PRQA S 0605 ++*/
START_FUNCTION_DECLARATION_RAMSECTION
static Common_ResultStatusType Flash_WaitCmdComplete(Flash_CallbackType CallBack, uint32 TimeoutVal)
END_FUNCTION_DECLARATION_RAMSECTION

START_FUNCTION_DECLARATION_RAMSECTION
static Common_ResultStatusType Flash_ExecuteCommand(Flash_CmdType Cmd, Flash_CallbackType CallBack)
END_FUNCTION_DECLARATION_RAMSECTION

START_FUNCTION_DECLARATION_RAMSECTION
static Common_ResultStatusType Flash_ExecuteCommandInt(Flash_CmdType Cmd)
END_FUNCTION_DECLARATION_RAMSECTION

START_FUNCTION_DECLARATION_RAMSECTION
static Common_ResultStatusType Flash_Drv_Compare(uint32 SrcAddr, const uint8 *CompareBuff,
                                                                                    uint32 Length)
END_FUNCTION_DECLARATION_RAMSECTION
/*PRQA S 0605 --*/
#else
static Common_ResultStatusType Flash_WaitCmdComplete(Flash_CallbackType CallBack,uint32 TimeoutVal);
static Common_ResultStatusType Flash_ExecuteCommand(Flash_CmdType Cmd, Flash_CallbackType CallBack);
static Common_ResultStatusType Flash_ExecuteCommandInt(Flash_CmdType Cmd);
static Common_ResultStatusType Flash_Drv_Compare(uint32 SrcAddr, const uint8 *CompareBuff,
                                                                                    uint32 Length);
#endif

/** @} end of group Private_FunctionDeclaration */

/** @defgroup Private_FunctionDefinition
 *  @{
 */

/**
 * @brief      Waiting for completion of flash command.
 *
 * @param[in]  CallBack: It points to the callback function that will be called while waiting for
 *                       completing the command. If no callback function is needed, please set
 *                       this parameter to NULL_PTR.
 * @param[in]  TimeoutVal: Timeout value for command execution.
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed. 
 * @retval     COMMON_ERR: Command execution timeout.
 *
 */
static Common_ResultStatusType Flash_WaitCmdComplete(Flash_CallbackType CallBack, uint32 TimeoutVal)
{
    Common_ResultStatusType Stat = COMMON_ERR;
    uint32 CmdCompIntFlag = 0U;
    volatile uint32 LocalCnt = 0U;
    /*PRQA S 0303 ++*/
    Reg_Flash_BfType *FlashRegPtr = (Reg_Flash_BfType *) FLASHC_BASE_ADDR;
    /*PRQA S 0303 --*/
    
    while(LocalCnt < TimeoutVal)
    {
        CmdCompIntFlag = FlashRegPtr->FLASH_FSTAT.CCIF;
        if(0U != CmdCompIntFlag)
        {
            Stat = COMMON_SUCC;
            break;
        }
        else
        {
            LocalCnt++;
        
            if(CallBack != NULL_PTR)
            {
                DISABLE_CHECK_RAMSECTION_FUNCTION_CALL
                CallBack();
                ENABLE_CHECK_RAMSECTION_FUNCTION_CALL
            } 
        }         
    }

    return Stat;
}

/**
 * @brief      Execute command and wait for the completion.
 *
 * @param[in]  Cmd: The command to be executed.
 * @param[in]  CallBack: It points to the callback function that will be called while waiting for
                         completing the command.
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully executed. 
 * @retval     COMMON_ERR: Command execution error or timeout.
 * @retval     COMMON_BUSY: Flash command execution is ongoing.
 *
 */ 
static Common_ResultStatusType Flash_ExecuteCommand(Flash_CmdType Cmd, Flash_CallbackType CallBack)
{
    Common_ResultStatusType Stat = COMMON_SUCC;
    uint32 CmdCompIntFlag;
    uint32 TimeoutVal;
    uint32 RecoveryTime;
    /*PRQA S 0303 ++*/
    Reg_Flash_BfType *FlashRegPtr = (Reg_Flash_BfType *) FLASHC_BASE_ADDR;
    Reg_Flash_WType *FlashRegWPtr = (Reg_Flash_WType *) FLASHC_BASE_ADDR;
    /*PRQA S 0303 --*/
    
    RecoveryTime = FlashRegPtr->FLASH_TIMING_R1.NS10_OF_TRCP;
    if(RecoveryTime != FLASH_RECOVERY_TIME_VAL)
    {
        /* set charge pump recovery time to 0x64 */
        FlashRegPtr->FLASH_TIMING_R1.NS10_OF_TRCP = FLASH_RECOVERY_TIME_VAL;
    }

    CmdCompIntFlag = FlashRegPtr->FLASH_FSTAT.CCIF;
    if(0U == CmdCompIntFlag)
    {
        Stat = COMMON_BUSY;
    }
    else
    {
        /* disable command complete interrupt */
        FlashRegPtr->FLASH_FCNFG.CCIE = 0U;
        Flash_IntMaskStatus = Flash_IntMaskStatus & 0xFFFFFF7FU;
        
        FlashRegPtr->FLASH_FCMD.CMDCODE = (uint32)Cmd;
        
        FlashRegPtr->FLASH_FCTRL.ABTREQ = 0U;

        /* clear CMDABT, ACCERR, PREABT if any is set */
        FlashRegWPtr->FLASH_FSTAT = FLASH_CMD_ERR_MASK;

        /* clear CCIF to start cmd */
        FlashRegWPtr->FLASH_FSTAT = 0x00000080U;

        if(FLASH_CMD_ERASE_ALL == Cmd)
        {
            TimeoutVal = FLASH_TIMEOUT_WAIT_CNT_ERASE_ALL;
        }
        else
        {
            TimeoutVal = FLASH_TIMEOUT_WAIT_CNT;
        }

        Stat = Flash_WaitCmdComplete(CallBack, TimeoutVal);

        if((FlashRegWPtr->FLASH_FSTAT & FLASH_CMD_ERR_STATUS) != 0U)
        {
            Stat = COMMON_ERR;
        }
    }

    return Stat;
}

/**
 * @brief      Execute command and use interrupt to inform when the command is completed.
 *
 * @param[in]  Cmd: The command to be executed.
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: Command successfully started.
 * @retval     COMMON_BUSY: Flash command execution is ongoing.
 *
 */ 
static Common_ResultStatusType Flash_ExecuteCommandInt(Flash_CmdType Cmd)
{
    Common_ResultStatusType Stat = COMMON_SUCC;
    uint32 CmdCompIntFlag;
    uint32 RecoveryTime;
    /*PRQA S 0303 ++*/
    Reg_Flash_BfType *FlashRegPtr = (Reg_Flash_BfType *) FLASHC_BASE_ADDR;
    Reg_Flash_WType *FlashRegWPtr = (Reg_Flash_WType *) FLASHC_BASE_ADDR;
    /*PRQA S 0303 --*/
 
    RecoveryTime = FlashRegPtr->FLASH_TIMING_R1.NS10_OF_TRCP;
    if(RecoveryTime != FLASH_RECOVERY_TIME_VAL)
    {
        /* set charge pump recovery time to 0x64 */
        FlashRegPtr->FLASH_TIMING_R1.NS10_OF_TRCP = FLASH_RECOVERY_TIME_VAL;
    }

    CmdCompIntFlag = FlashRegPtr->FLASH_FSTAT.CCIF;
    if(0U == CmdCompIntFlag)
    {
        Stat = COMMON_BUSY;
    }
    else
    {
        FlashRegPtr->FLASH_FCMD.CMDCODE = (uint32)Cmd;
        
        FlashRegPtr->FLASH_FCTRL.ABTREQ = 0U;

        /* clear CMDABT, ACCERR, PREABT if any is set */
        FlashRegWPtr->FLASH_FSTAT = FLASH_CMD_ERR_MASK;        

        /* clear CCIF to start cmd */
        FlashRegWPtr->FLASH_FSTAT = 0x00000080U;

        Flash_IntMaskStatus = Flash_IntMaskStatus | 0x00000080U;
        
        /* enable command complete interrupt */
        FlashRegPtr->FLASH_FCNFG.CCIE = 1U;
    }    
    
    return Stat;
}

/**
 * @brief      Compare data in Flash or EEPROM main array with the expected value. 
 *
 * @param[in]  SrcAddr: Start address where to read in the Flash or EEPROM memory.
 * @param[in]  CompareBuff: Points to the start address where the expected values are stored.
 * @param[in]  Length: The length of data in byte.
 *
 * @return     Common_ResultStatusType
 * @retval     COMMON_SUCC: All the values are the same.
 * @retval     COMMON_ERR: Parameters invalid, or values are different.
 *
 */
static Common_ResultStatusType Flash_Drv_Compare(uint32 SrcAddr, const uint8 *CompareBuff,
                                                                                    uint32 Length)
{
    Common_ResultStatusType Stat = COMMON_SUCC;
    uint32 LenCount;

    if((NULL_PTR == CompareBuff) || (0U == Length))
    {
        Stat = COMMON_ERR;
    }
    else
    {
        for (LenCount = 0U; LenCount < Length; LenCount++)   
        { 
            /*PRQA S 0303 ++*/
            if (*(volatile uint8 *)(SrcAddr + LenCount) != CompareBuff[LenCount])
            /*PRQA S 0303 --*/
            {
                Stat = COMMON_ERR;
                break;
            }
        }
    }

    return Stat;
}

/** @} end of group Private_FunctionDefinition */

/** @defgroup Public_FunctionDefinition
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
void Flash_SetClockDivision(uint8 SetValue)
{
    Flash_RegBfPtr->FLASH_FCNFG.CLK_DIV = SetValue;
}

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
void Flash_IgnoreBusErrorConfig(uint32 StartAddr[2U], uint32 EndAddr[2U])
{
    Flash_RegBfPtr->FLASH_BED_ADDR_STRT_RG0.BED_ADDR_STRT = StartAddr[0U] >> 3U;
    Flash_RegBfPtr->FLASH_BED_ADDR_END_RG0.BED_ADDR_END = EndAddr[0U] >> 3U;
    Flash_RegBfPtr->FLASH_BED_ADDR_STRT_RG1.BED_ADDR_STRT = StartAddr[1U] >> 3U;
    Flash_RegBfPtr->FLASH_BED_ADDR_END_RG1.BED_ADDR_END = EndAddr[1U] >> 3U;
}

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
                                   const Flash_CmdConfigType *ConfigType)
{
    volatile uint8 *RegData = (volatile uint8 *)&(Flash_RegWPtr->FLASH_FDATA0);
    Common_ResultStatusType Stat;
    uint8 i;
    
    if(((EepromAddr % FLASH_EEPROM_PHRASE_SIZE) != 0U) || 
        (!FLASH_VALID_EEPROM_ADDR(EepromAddr)))
    {
        Stat = COMMON_ERR;
    }
    else if(0U == Flash_RegBfPtr->FLASH_FSTAT.CCIF)
    {
        Stat = COMMON_BUSY;
    }
    else
    {
        Flash_RegWPtr->FLASH_FADDR = EepromAddr;

        for(i = 0U; i < FLASH_EEPROM_PHRASE_SIZE; i++)
        {
            RegData[i] = DataPtr[i];
        }

        if(FLASH_CMD_ACT_WAIT == ConfigType->Act)
        {
            Stat = Flash_ExecuteCommand(FLASH_CMD_EE_PROG, ConfigType->CallBack);
        }
        else
        {
            Stat = Flash_ExecuteCommandInt(FLASH_CMD_EE_PROG);
        }
    }

    return Stat;
}

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
                                           Flash_CallbackType CallBack)
{
    Common_ResultStatusType Stat = COMMON_ERR;
    uint32 Count;
    uint32 BufAddr;
    Flash_CmdConfigType ConfigType;

    ConfigType.Act = FLASH_CMD_ACT_WAIT;
    ConfigType.CallBack = CallBack;

    if(((EepromAddr % FLASH_EEPROM_PHRASE_SIZE) != 0U)  || (DataPtr == NULL_PTR) 
      || (Len == 0U) || ((Len % FLASH_EEPROM_PHRASE_SIZE) != 0U))
    {
       Stat = COMMON_ERR;
    }
    else
    {
        /*PRQA S 0306 ++*/
        BufAddr = (uint32)DataPtr;
        /*PRQA S 0306 --*/

        for(Count = 0U; Count < Len; Count += FLASH_EEPROM_PHRASE_SIZE)
        {
            /*PRQA S 0306 ++*/
            Stat = Eeprom_ProgramEepromPhrase((EepromAddr + Count), (uint8 *)(BufAddr + Count),
                                            &ConfigType);
            /*PRQA S 0306 --*/
            if(COMMON_SUCC != Stat)
            {
                break;
            }
        }

        if (COMMON_SUCC == Stat)
        {
            Stat = Flash_Drv_Compare(EepromAddr, DataPtr, Len);
        }
    }
   
    return Stat;    
}

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
                                   const Flash_CmdConfigType *ConfigType)
{
    volatile uint8 *RegData = (volatile uint8 *)&(Flash_RegWPtr->FLASH_FDATA0);
    uint8 i;
    Common_ResultStatusType Stat;

    if(0U == Flash_RegBfPtr->FLASH_FSTAT.CCIF)
    {
        Stat = COMMON_BUSY;
    }
    else
    {
        Flash_RegWPtr->FLASH_FADDR = BllaNum;

        for(i = 0U; i < FLASH_BLLA_SIZE; i++)
        {
            RegData[i] = DataPtr[i];
        }

        if(FLASH_CMD_ACT_WAIT == ConfigType->Act)
        {
            Stat = Flash_ExecuteCommand(FLASH_CMD_BLL_WRITE, ConfigType->CallBack);
        }
        else
        {
            Stat = Flash_ExecuteCommandInt(FLASH_CMD_BLL_WRITE);
        }
    }

    return Stat;
}

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
Common_ResultStatusType Flash_PreWriteBllr(const Flash_CmdConfigType *ConfigType)
{
   volatile uint8 *RegData = (volatile uint8 *)&(Flash_RegWPtr->FLASH_FDATA0);
   uint8 BllrValue[FLASH_BLLR_DATA_LEN] = {0x4aU, 0xaaU, 0x4aU, 0xaaU,
                                           0x4aU, 0xaaU, 0x4aU, 0x00U, 0x00U};
   Common_ResultStatusType Stat;
   uint8 i;

   if(0U == Flash_RegBfPtr->FLASH_FSTAT.CCIF)
   {
       Stat = COMMON_BUSY;
   }
   else
   {
       Flash_RegWPtr->FLASH_FADDR = FLASH_BLLR_ADDR;

       for(i = 0U; i < FLASH_BLLR_DATA_LEN; i++)
       {
           RegData[i] = BllrValue[i];
       }

       if(FLASH_CMD_ACT_WAIT == ConfigType->Act)
       {
           Stat = Flash_ExecuteCommand(FLASH_CMD_BLL_WRITE, ConfigType->CallBack);
       }
       else
       {
           Stat = Flash_ExecuteCommandInt(FLASH_CMD_BLL_WRITE);
       }
   }

   return Stat;
}

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
Common_ResultStatusType Flash_ProgramPage(uint32 FlashAddr, const Flash_CmdConfigType *ConfigType)
{
    Common_ResultStatusType Stat;

    if((FlashAddr % FLASH_PAGE_SIZE) != 0U)
    {
        Stat = COMMON_ERR;
    }
    else
    {
        if(0U == Flash_RegBfPtr->FLASH_FSTAT.CCIF)
        {
            Stat = COMMON_BUSY;
        }
        else
        {
            Flash_RegWPtr->FLASH_FADDR = FlashAddr;

            if(FLASH_CMD_ACT_WAIT == ConfigType->Act)
            {
                Stat = Flash_ExecuteCommand(FLASH_CMD_FL_PROG, ConfigType->CallBack);
            }
            else
            {
                Stat = Flash_ExecuteCommandInt(FLASH_CMD_FL_PROG);
            }
        }
    }

    return Stat;
}

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
                                        Flash_CallbackType CallBack)
{
    Common_ResultStatusType Stat = COMMON_SUCC;
    uint32 LenCount;
    uint8 BllaCount;
    Flash_CmdConfigType ConfigType;

    ConfigType.Act = FLASH_CMD_ACT_WAIT;
    ConfigType.CallBack = CallBack;

    if(((FlashAddr % FLASH_PAGE_SIZE) != 0U) || (NULL_PTR == DataPtr) 
         || (0U == Len) || ((Len % FLASH_PAGE_SIZE) != 0U))
    {
        Stat = COMMON_ERR;
    }
    else
    {
        for (LenCount = 0U; LenCount < Len; LenCount += FLASH_PAGE_SIZE)   
        { 
            for (BllaCount = 0U; BllaCount < FLASH_BLLA_COUNT; BllaCount++)
            {
                if (COMMON_SUCC != Stat)
                {
                    break;
                }
                
                Stat = Flash_PreWriteBlla(BllaCount, &DataPtr[LenCount + (uint32)BllaCount * 8U], 
                                                                                    &ConfigType);
            }

            if (COMMON_SUCC == Stat)
            {
                Stat = Flash_PreWriteBllr(&ConfigType);
                if (COMMON_SUCC == Stat)
                {
                    Stat = Flash_ProgramPage((FlashAddr + LenCount), &ConfigType);
                }
            }
        }
        
        if (COMMON_SUCC == Stat)
        {
            Stat = Flash_Drv_Compare(FlashAddr, DataPtr, Len);
        }
    }

    return Stat;
}

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
Common_ResultStatusType Flash_EraseAll(const Flash_CmdConfigType *ConfigType)
{
    Common_ResultStatusType Stat;

    if(0U == Flash_RegBfPtr->FLASH_FSTAT.CCIF)
    {
        Stat = COMMON_BUSY;
    }
    else
    {
        Flash_RegWPtr->FLASH_FADDR = 0U;
        
        if(FLASH_CMD_ACT_WAIT == ConfigType->Act)
        {
            Stat = Flash_ExecuteCommand(FLASH_CMD_ERASE_ALL, ConfigType->CallBack);
        }
        else
        {
            Stat = Flash_ExecuteCommandInt(FLASH_CMD_ERASE_ALL);
        }
    }
    
    return Stat;
}

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
Common_ResultStatusType Flash_EraseSector(uint32 Addr, const Flash_CmdConfigType *ConfigType)
{
    Common_ResultStatusType Stat;

    if((Addr % FLASH_SECTOR_SIZE) != 0U)
    {
        Stat = COMMON_ERR;
    }
    else if(0U == Flash_RegBfPtr->FLASH_FSTAT.CCIF)
    {
        Stat = COMMON_BUSY;
    }
    else
    {
        Flash_RegWPtr->FLASH_FADDR = Addr;

        if(FLASH_CMD_ACT_WAIT == ConfigType->Act)
        {
            Stat = Flash_ExecuteCommand(FLASH_CMD_FL_SEC_ERASE, ConfigType->CallBack);
        }
        else
        {
            Stat = Flash_ExecuteCommandInt(FLASH_CMD_FL_SEC_ERASE);
        }
    }
    
    return Stat;
}

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
                                                    const Flash_CmdConfigType *ConfigType)
{
    Common_ResultStatusType Stat = COMMON_SUCC;
    uint8 i;
    uint8 SecDbgCtrl[FLASH_PHRASE_SIZE] = {0xECU, 0xF5U, 0x00U, 0x00U, 
                                           0x00U, 0x00U, 0x00U, 0x00U};
    uint8 BlankData[FLASH_PHRASE_SIZE] = {0U};
    
    if(COMMON_DISABLE == EraseAll)
    {
        SecDbgCtrl[2] = 0xE2U;
        SecDbgCtrl[3] = 0x3EU;
    }
    
    for (i = 0U; i < FLASH_BLLA_COUNT; i++)
    {
        if (COMMON_SUCC != Stat)
        {
            break;
        }

        /* debug mode */
        if (0U == i)
        {
            Stat = Flash_PreWriteBlla(i, SecDbgCtrl, ConfigType);
        }

        /* first 64bit key */
        if (1U == i)
        {
            Stat = Flash_PreWriteBlla(i, Key, ConfigType);
        }

        /* second 64bit key */
        if (2U == i)
        {
            Stat = Flash_PreWriteBlla(i, &Key[FLASH_BLLA_SIZE], ConfigType);
        }
        
        if (i > 2U)
        {
            Stat = Flash_PreWriteBlla(i, BlankData, ConfigType);
        }
    }
        
    if (COMMON_SUCC == Stat)
    {
        Stat = Flash_PreWriteBllr(ConfigType);
        if (COMMON_SUCC == Stat)
        {
            Stat = Flash_ProgramPage(FLASH_SECDEBUG_CTRL_ADDR, ConfigType);
        }
    }
    
    return Stat;
}
#endif

/**
 * @brief      Get secure debug mode status.
 *
 * @param[in]  None
 *
 * @return     Flash_SecureDebugModeType
 * @retval     SECURE_DEBUG_OFF: Secure debug mode off.
 * @retval     SECURE_DEBUG_ON: Secure debug mode on.
 * @retval     SECURE_DEBUG_ON_ERASE_OFF: Secure debug mode on and erase 
 *                                        all request cannot erase flash.
 *
 */
Flash_SecureDebugModeType Flash_GetSecureDebugMode(void)
{
    Flash_SecureDebugModeType Ret = SECURE_DEBUG_OFF;

    if (1U == Flash_RegBfPtr->FLASH_FSTAT.DBG_ERSALL_DIS)
    {
        Ret = SECURE_DEBUG_ON_ERASE_OFF;
    }
    else if (1U == Flash_RegBfPtr->FLASH_FSTAT.FSEC)
    {
        Ret = SECURE_DEBUG_ON;
    }
    else
    {
        /* do nothing */
    }
    return Ret;
}

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
Common_ResultStatusType Flash_OpenSecureDebugPort(uint8 Key[])
{
    Common_ResultStatusType Ret = COMMON_SUCC;
    uint8 i;
    /* import auth session key */
    volatile uint8 *KeyPtr = (volatile uint8 *)&(Flash_RegWPtr->FLASH_DECRY_KEY_R0);   
    for(i = 0U; i < 16U; i++)
    {
        KeyPtr[i] = Key[i];
    }

    if(0U == Flash_RegBfPtr->FLASH_FSTAT.CCIF)
    {
        Ret = COMMON_BUSY;
    }
    else
    {
        /* generate a query after writing auth session keys */
        Flash_RegBfPtr->FLASH_FCTRL.BK_QUERY = 1U;
        
        /* Check auth result */
        if (Flash_RegBfPtr->FLASH_FSTAT.FSEC != 0U) 
        {
            Ret = COMMON_ERR;
        }
    }

    return Ret;
}

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
Common_FlagStatusType Flash_GetStatus(Flash_StatusType Stat)
{
    Common_FlagStatusType Status;
    
    Status = (0U == ((Flash_RegWPtr->FLASH_FSTAT) & (uint32)Stat)) ? COMMON_RESET : COMMON_SET;
    
    return Status;
}

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
Flash_AbortResultType Flash_AbortCommand(void)
{
    volatile uint32 LocalCnt = 0U;
    Flash_AbortResultType Stat;

    /* No flash command is being executed */
    if(1U == Flash_RegBfPtr->FLASH_FSTAT.CCIF)
    {
        Stat = FLASH_ABORT_FINISHED;
    }
    else
    {
        /* Abort executing flash comand */
        Flash_RegBfPtr->FLASH_FCTRL.ABTREQ = 1U;
        Stat = FLASH_ABORT_TIMEOUT;
        while(LocalCnt < FLASH_TIMEOUT_ABORT_WAIT_CNT)
        {
            if ((1U == Flash_RegBfPtr->FLASH_FSTAT.CCIF ) && (1U == Flash_RegBfPtr->FLASH_FSTAT.CMDABT))
            {
                /* clear CMDABT flag */
                Flash_RegWPtr->FLASH_FSTAT = (uint32)FLASH_STATUS_CMDABT;
                Stat = FLASH_ABORT_OK;
                break;
            }
            else if (1U == Flash_RegBfPtr->FLASH_FSTAT.CCIF)
            {
                /* abort failed, but flash command has been finished */
                Stat = FLASH_ABORT_FINISHED;
                break;
            }
            else
            {
                LocalCnt++;
            }
        }
    }

    return Stat;
}

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
 *              Refer to System Control Module in RM for more infomation.
 * 
 */
void Flash_SetEepromReadEccEnable(Common_ControlStateType NewStatus)
{
    Flash_RegBfPtr->FLASH_FCNFG.EE_READ_ECC_EN = (uint32)NewStatus;
}

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
 *              Refer to System Control Module in RM for more infomation.
 * 
 */
void Flash_SetFlashReadEccEnable(Common_ControlStateType NewStatus)
{
    Flash_RegBfPtr->FLASH_FCNFG.FL_READ_ECC_EN = (uint32)NewStatus;
}

/**
 * @brief       Get Flash single-bit ECC error state.
 *
 * @param[out]  State: It points to a struct where the Ecc state will be stored.
 *
 * @return      None
 *
 */
void Flash_GetSingleBitEccState(Flash_EccStateType *State)
{
    State->EccFlag = (0U == Flash_RegBfPtr->FLASH_FSTAT.SFDIF) ? COMMON_RESET : COMMON_SET;
    State->Overrun = (0U == Flash_RegBfPtr->FLASH_SBE_STATE.SBE_OVERRUN) ? COMMON_RESET : COMMON_SET;
    if(COMMON_SET == State->EccFlag)
    {
        State->Addr = (Flash_RegWPtr->FLASH_SBE_STATE) & 0xFFFFFFF8U;
    }
}

/**
 * @brief       Get Flash multi-bit ECC error state.
 *
 * @param[out]  State: It points to a struct where the Ecc state will be stored.
 *
 * @return      None
 *
 */
void Flash_GetMultiBitEccState(Flash_EccStateType *State)
{
    State->EccFlag = (0U == Flash_RegBfPtr->FLASH_FSTAT.DFDIF) ? COMMON_RESET : COMMON_SET;
    State->Overrun = (0U == Flash_RegBfPtr->FLASH_MBE_STATE.MBE_OVERRUN) ? COMMON_RESET : COMMON_SET;
    if(COMMON_SET == State->EccFlag)
    {
        State->Addr = (Flash_RegWPtr->FLASH_MBE_STATE) & 0xFFFFFFF8U;
    }
}

/**
 * @brief      Clear Flash single-bit ECC error state.
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void Flash_ClearSingleBitEccState(void)
{
    Flash_RegWPtr->FLASH_FSTAT = (uint32)FLASH_SFDIF_FLAG;
}

/**
 * @brief      Clear Flash multi-bit ECC error state.
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void Flash_ClearMultiBitEccState(void)
{
    Flash_RegWPtr->FLASH_FSTAT = (uint32)FLASH_DFDIF_FLAG;
}

/**
 * @brief      Install callback function.
 *
 * @param[in]  CallbackFun: Indicate callback function.
 *
 * @return     None
 *
 */
void Flash_InstallCallBackFunc(Isr_CbFuncType * CallbackFun)
{
    Flash_IsrCbFun = CallbackFun;
}

/**
 * @brief      Mask/Unmask command complete interrupt.
 *
 * @param[in]  IntType: select interrupt type
 * @param[in]  IntMask: Interrupt MASK or UNMASK.
 *               - COMMON_UNMASK: Interrupt unmask.
 *               - COMMON_MASK: Interrupt mask.
 * 
 * @return     None
 * 
 * @note       If user wants to set mask double-bit interrupt, 
 *             correct configuration of SCM module is needed.
 *             Refer to System Control Module in RM for more infomation.
 *
 */
void Flash_SetIntMask(Flash_IntMaskType IntType, Common_IntMaskType IntMask)
{
    if(COMMON_UNMASK == IntMask)
    {
        if(IntType != FLASH_INT_DFDIE_MASK)
        {
            Flash_IntMaskStatus = Flash_IntMaskStatus | Flash_IntStatus;
        }
        Flash_RegWPtr->FLASH_FCNFG |= Flash_InterruptMaskTable[IntType];
    }
    else
    {
        Flash_RegWPtr->FLASH_FCNFG &= ~Flash_InterruptMaskTable[IntType];
        if(IntType != FLASH_INT_DFDIE_MASK)
        {
            Flash_IntMaskStatus = Flash_IntMaskStatus & (~Flash_IntStatus);
        }
    }
}

/**
 * @brief      Clear command complete interrupt flag.
 *
 * @param[in]  IntType: select interrupt type
 *
 * @return     None
 *
 */
void Flash_ClearIntFlag(Flash_IntFlagType IntType)
{
    switch (IntType) {
    case FLASH_INT_CCIF_FLAG:
        /* ccif can only be cleared by execute a new command,
            so disable this interrupt here */
        Flash_SetIntMask(FLASH_INT_CCIE_MASK, COMMON_MASK);
        break;

    case FLASH_INT_DFDIF_FLAG:
    case FLASH_INT_SFDIF_FLAG:
        Flash_RegWPtr->FLASH_FSTAT = Flash_InterruptFlagTable[IntType];
        break;
    
    case FLASH_INT_ALL_FLAG:
        Flash_SetIntMask(FLASH_INT_CCIE_MASK, COMMON_MASK);
        Flash_RegWPtr->FLASH_FSTAT = (uint32)FLASH_ECC_FLAG;
        break;
    
    default:
        /* do noting */
        break;
    }
}

/**
 * @brief      Flash erase or program operation done IrqHandler.
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void Flash_EraseProgram_DriverIrqHandler(void)
{
    uint32 IntStatus; 

    /* get interrupt status */
    IntStatus = Flash_RegWPtr->FLASH_FSTAT;
    /* only check enabled interrupts */
    IntStatus = IntStatus & Flash_IntMaskStatus;

    if((IntStatus & Flash_IntStatus) != 0U)
    {
        /* this flag can only be cleared by execute a new command,so disable this
           interrupt here */
        Flash_SetIntMask(FLASH_INT_CCIE_MASK, COMMON_MASK);
        
        if (Flash_IsrCbFun != NULL_PTR)
        {
            Flash_IsrCbFun();
        }
    }
}

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
Common_ResultStatusType Flash_Init(void)
{
    Common_ResultStatusType Stat = COMMON_SUCC;

    if(1U == Flash_RegBfPtr->FLASH_FSTAT.INIT_FAIL)
    {
        Stat = COMMON_ERR;
    }

    return Stat;
}

/** @} end of group Public_FunctionDefinition */
