/**************************************************************************************************/
/**
 * @file     flash_drv.c
 * @brief    FLASH module driver file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 *
 **************************************************************************************************/

#include "flash_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @defgroup FLASH
 *  @brief FLASH driver modules
 *  @{
 */

/** @defgroup FLASH_Private_Type
 *  @{
 */
/**
 *  @brief FLASH command type definition
 */
typedef enum
{
    FLASH_CMD_RD1ALL = 0U,      /*!< Verify that all flash and IFR space is
                                    erased*/
    FLASH_CMD_RD1BLK = 1U,      /*!< Verify that a flash block is erased */
    FLASH_CMD_RD1SCR = 2U,      /*!< Verify that a flash sector is erased */
    FLASH_CMD_RD1PG = 3U,       /*!< Verify that a flash page is erased */
    FLASH_CMD_RD1PHR = 4U,      /*!< Verify that a flash phrase is erased */
    FLASH_CMD_RDMISR = 5U,      /*!< Generate MISR signature for range of flash
                                     pages */
    FLASH_CMD_RD1ISCR = 0x12U,  /*!< Verify that an IFR sector is erased */
    FLASH_CMD_RD1IPG = 0x13U,   /*!< Verify that an IFR page is erased */
    FLASH_CMD_RD1IPHR = 0x14U,  /*!< Verify that an IFR phrase is erased */
    FLASH_CMD_RDIMISR = 0x15U,  /*!< Generate MISR signature for range of IFR
                                     pages */
    FLASH_CMD_PGMPHR = 0x24U,   /*!< Program data to a flash or IFR phrase */
    FLASH_CMD_ERSALL = 0x40U,   /*!< Erase all flash and IFR space */
    FLASH_CMD_ERSSCR = 0x42U    /*!< Erase a flash sector */
}FLASH_Cmd_t;
/** @} end of group FLASH_Private_Type*/

/** @defgroup FLASH_Private_Defines
 *  @{
 */

#define FLASH_SECURE_ADDR      0x02000000U
#define FLASH_PHRASE_SIZE      16U
#define FLASH_SECTOR_SIZE      0x2000U

/* Dflash */
#define FLASH_DFLASH_END_ADDR         (FLASH_DATA_BASE_ADDR + FLASH_DFLASH_SIZE - 1U)
#define FLASH_VALID_DFLASH_ADDR(addr) (((addr) >= FLASH_DATA_BASE_ADDR) && ((addr) <= FLASH_DFLASH_END_ADDR))
     
#define FLASH_CMD_ERR_MASK     (FLASH_STATUS_CMDABT_MASK \
                               | FLASH_STATUS_ACCERR_MASK \
                               | FLASH_STATUS_FAIL_MASK)

#define FLASH_INT_CCIF_MASK         0x00000080U
#define FLASH_INT_DFDIF_MASK        0x00010000U
#define FLASH_INT_SFDIF_MASK        0x00020000U
#define FLASH_INT_ALL_MASK       (FLASH_INT_CCIF_MASK | FLASH_INT_DFDIF_MASK\
                                  | FLASH_INT_SFDIF_MASK)
#define FLASH_ECC_MASK           (FLASH_INT_DFDIF_MASK | FLASH_INT_SFDIF_MASK)

#define FLASH_BUGFIX_CCIF_ENABLE

/** @} end of group FLASH_Private_Defines */

/** @defgroup FLASH_Private_Variables
 *  @{
 */
/*PRQA S 0303 ++*/
static flash_reg_t *const flsRegPtr = (flash_reg_t *) FLASHC_BASE_ADDR;
static flash_reg_w_t *const flsRegWPtr = (flash_reg_w_t *) FLASHC_BASE_ADDR;
/*PRQA S 0303 --*/

static isr_cb_t * flashIsrCbFunc[FLASH_INT_ALL] = {NULL, NULL, NULL};

static const uint32_t flashInterruptMaskTable[] =
{
    FLASH_INT_CCIF_MASK,      /* FLASH_INT_CCIF */
    FLASH_INT_DFDIF_MASK,     /* FLASH_INT_DFDIF */
    FLASH_INT_SFDIF_MASK,     /* FLASH_INT_SFDIF */
    FLASH_INT_ALL_MASK        /* FLASH_INT_ALL */
};

/** @} end of group FLASH_Private_Variables */

/** @defgroup FLASH_Global_Variables
 *  @{
 */

/** @} end of group FLASH_Global_Variables */

/** @defgroup FLASH_Private_FunctionDeclaration
 *  @{
 */
void FLASH_CmdComplete_DriverIRQHandler(void);
void FLASH_Ecc_DriverIRQHandler(void);

#if (FLASH_CMD_FUNC_IN_RAM == 1)
/*PRQA S 0605 ++*/
START_FUNCTION_DECLARATION_RAMSECTION
static ResultStatus_t FLASH_WaitCmdComplete(flash_cb_t callBack)
END_FUNCTION_DECLARATION_RAMSECTION

START_FUNCTION_DECLARATION_RAMSECTION
static ResultStatus_t FLASH_WaitEraseAllComplete(flash_cb_t callBack)
END_FUNCTION_DECLARATION_RAMSECTION

START_FUNCTION_DECLARATION_RAMSECTION
static ResultStatus_t FLASH_ExecuteCommand(FLASH_Cmd_t cmd, flash_cb_t callBack)
END_FUNCTION_DECLARATION_RAMSECTION

START_FUNCTION_DECLARATION_RAMSECTION
static ResultStatus_t FLASH_ExecuteCommandInt(FLASH_Cmd_t cmd)
END_FUNCTION_DECLARATION_RAMSECTION
/*PRQA S 0605 --*/
#else
static ResultStatus_t FLASH_WaitCmdComplete(flash_cb_t callBack);
static ResultStatus_t FLASH_WaitEraseAllComplete(flash_cb_t callBack);
static ResultStatus_t FLASH_ExecuteCommand(FLASH_Cmd_t cmd, flash_cb_t callBack);
static ResultStatus_t FLASH_ExecuteCommandInt(FLASH_Cmd_t cmd);
#endif

/** @} end of group FLASH_Private_FunctionDeclaration */

/** @defgroup FLASH_Private_Functions
 *  @{
 */
static ResultStatus_t FLASH_WaitCmdComplete(flash_cb_t callBack)
{
    ResultStatus_t ret = ERR;
    uint32_t ccifFlag = 0U;
    volatile uint32_t localCnt = 0U;
    /*PRQA S 0303 ++*/
    flash_reg_t *pFlashReg = (flash_reg_t *) FLASHC_BASE_ADDR;
    /*PRQA S 0303 --*/
    
    while(localCnt < FLASH_TIMEOUT_WAIT_CNT)
    {
        ccifFlag = pFlashReg->FLASH_FSTAT.CCIF;
        if(0U != ccifFlag)
        {
            ret = SUCC;
            break;
        }
        else
        {
            localCnt++;
        
            if(callBack != NULL)
            {
                DISABLE_CHECK_RAMSECTION_FUNCTION_CALL
                callBack();
                ENABLE_CHECK_RAMSECTION_FUNCTION_CALL
            } 
        }         
    }

    return ret;
}

static ResultStatus_t FLASH_WaitEraseAllComplete(flash_cb_t callBack)
{
    ResultStatus_t ret = ERR;
    uint32_t ccifFlag = 0U;
    volatile uint32_t localCnt = 0U;
    /*PRQA S 0303 ++*/
    flash_reg_t *pFlashReg = (flash_reg_t *) FLASHC_BASE_ADDR;
    /*PRQA S 0303 --*/
    
    while(localCnt < FLASH_TIMEOUT_WAIT_CNT_ERASE_ALL)
    {
        ccifFlag = pFlashReg->FLASH_FSTAT.CCIF;
        if(0U != ccifFlag)
        {
            ret = SUCC;
            break;
        }
        else
        {
            localCnt++;
        
            if(callBack != NULL)
            {
                DISABLE_CHECK_RAMSECTION_FUNCTION_CALL
                callBack();
                ENABLE_CHECK_RAMSECTION_FUNCTION_CALL
            } 
        }               
    }

    return ret;
}

static ResultStatus_t FLASH_ExecuteCommand(FLASH_Cmd_t cmd, flash_cb_t callBack)
{
    ResultStatus_t stat = SUCC;
    uint32_t regOldPriMask;
    uint32_t fstatVal;
    /*PRQA S 0303 ++*/
    flash_reg_t *pFlashReg = (flash_reg_t *) FLASHC_BASE_ADDR;
    flash_reg_w_t *pFlashRegW = (flash_reg_w_t *) FLASHC_BASE_ADDR;
    /*PRQA S 0303 --*/
    
    fstatVal = pFlashReg->FLASH_FSTAT.CCIF;
    if(0U == fstatVal)
    {
        stat = BUSY;
    }
    else
    {

        pFlashReg->FLASH_FCMD.CMDCODE = (uint32_t)cmd;
        
        pFlashReg->FLASH_FCTRL.ABTREQ = 0U;

        /* clear ACCERR, CMDABT, PREABT if any is set */
        pFlashRegW->FLASH_FSTAT = 0x00000074U;

    #ifndef FLASH_BUGFIX_CCIF_ENABLE
        /* clear CCIF to start cmd */
        pFlashRegW->FLASH_FSTAT = 0x00000080U;
    #else

    #if (FLASH_CMD_FUNC_IN_RAM == 0)
        scm_reg_t *scmRegPtr = (scm_reg_t *) SCM_BASE_ADDR;
        ControlState_t oldCacheStat;

        /* disable cache */
        oldCacheStat = (ControlState_t )scmRegPtr->SCM_MISCCTL1.CACHE_DIS;
        scmRegPtr->SCM_MISCCTL1.CACHE_DIS = 1U;

        /* Perform Cache clean */
        scmRegPtr->SCM_MISCCTL1.CCACHE_CLR = 1U;
        /* Perform Cache clean disable*/
        scmRegPtr->SCM_MISCCTL1.CCACHE_CLR = 0U;
    #endif

        __asm volatile("MRS %0, PRIMASK" :"=r" (regOldPriMask));
        if (0U == regOldPriMask) {
            COMMON_DISABLE_INTERRUPTS();
        }

        {
          __asm volatile(
            "PUSH  {R0, R1, R2}\n"
            "LDR   R0, =0x40020000\n"
            "LDR   R1, =0x80\n"

            "NOP\n"
            "NOP\n"
            "NOP\n"
            "NOP\n"
            "NOP\n"
            "NOP\n"
            "NOP\n"
            "NOP\n"

            "STR   R1, [R0]\n"
            "LDR   R2, [R0]\n"

            "NOP\n"
            "NOP\n"
            "NOP\n"
            "NOP\n"
            "NOP\n"
            "NOP\n"
            "NOP\n"
            "NOP\n"
            "POP  {R0, R1, R2}\n"
             );
        }

        if (0U == regOldPriMask) {
            COMMON_ENABLE_INTERRUPTS();
        }
    #if (FLASH_CMD_FUNC_IN_RAM == 0)
        /* enable  cache,if need */
        scmRegPtr->SCM_MISCCTL1.CACHE_DIS = oldCacheStat;
    #endif
    #endif

        if(FLASH_CMD_ERSALL == cmd)
        {
            stat = FLASH_WaitEraseAllComplete(callBack);
        }
        else
        {
            stat = FLASH_WaitCmdComplete(callBack);
        }

        fstatVal = pFlashRegW->FLASH_FSTAT;
        if((fstatVal & FLASH_CMD_ERR_MASK) != 0U)
        {
            stat = ERR;
        }
    }

    return stat;
}

static ResultStatus_t FLASH_ExecuteCommandInt(FLASH_Cmd_t cmd)
{
    ResultStatus_t stat = SUCC;
    uint32_t regOldPriMask;
    uint32_t ccifFlag;
    /*PRQA S 0303 ++*/
    flash_reg_t *pFlashReg = (flash_reg_t *) FLASHC_BASE_ADDR;
    flash_reg_w_t *pFlashRegW = (flash_reg_w_t *) FLASHC_BASE_ADDR;
    /*PRQA S 0303 --*/
 
    ccifFlag = pFlashReg->FLASH_FSTAT.CCIF;
    if(0U == ccifFlag)
    {
        stat = BUSY;
    }
    else
    {
        pFlashReg->FLASH_FCMD.CMDCODE = (uint32_t)cmd;
        
        pFlashReg->FLASH_FCTRL.ABTREQ = 0;

        /* clear ACCERR, CMDABT, PREABT if any is set */
        pFlashRegW->FLASH_FSTAT = 0x00000074;


    #ifndef FLASH_BUGFIX_CCIF_ENABLE
        /* clear CCIF to start cmd */
        pFlashRegW->FLASH_FSTAT = 0x00000080U;
    #else

    #if (FLASH_CMD_FUNC_IN_RAM == 0)
        scm_reg_t *scmRegPtr = (scm_reg_t *) SCM_BASE_ADDR;
        ControlState_t oldCacheStat;

        /* disable cache */
        oldCacheStat = (ControlState_t )scmRegPtr->SCM_MISCCTL1.CACHE_DIS;
        scmRegPtr->SCM_MISCCTL1.CACHE_DIS = 1U;

        /* Perform Cache clean */
        scmRegPtr->SCM_MISCCTL1.CCACHE_CLR = 1U;
        /* Perform Cache clean disable*/
        scmRegPtr->SCM_MISCCTL1.CCACHE_CLR = 0U;
    #endif

        __asm volatile("MRS %0, PRIMASK" :"=r" (regOldPriMask));
        if (0U == regOldPriMask) {
            COMMON_DISABLE_INTERRUPTS();
        }

        {
          __asm volatile(
            "PUSH  {R0, R1, R2}\n"
            "LDR   R0, =0x40020000\n"
            "LDR   R1, =0x80\n"

            "NOP\n"
            "NOP\n"
            "NOP\n"
            "NOP\n"
            "NOP\n"
            "NOP\n"
            "NOP\n"
            "NOP\n"

            "STR   R1, [R0]\n"
            "LDR   R2, [R0]\n"

            "NOP\n"
            "NOP\n"
            "NOP\n"
            "NOP\n"
            "NOP\n"
            "NOP\n"
            "NOP\n"
            "NOP\n"
            "POP  {R0, R1, R2}\n"
             );
        }

        if (0U == regOldPriMask) {
            COMMON_ENABLE_INTERRUPTS();
        }
    #if (FLASH_CMD_FUNC_IN_RAM == 0)
        /* enable cache,if need */
        scmRegPtr->SCM_MISCCTL1.CACHE_DIS = oldCacheStat;
    #endif
    #endif
        pFlashReg->FLASH_FCNFG.CCIE = 1;
    }    
    
    return stat;
}

/** @} end of group FLASH_Private_Functions */

/** @defgroup FLASH_Public_Functions
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
 *                        endAddr shall always be 0.
 *
 * @return     none
 *
 */
void FLASH_IgnoreBusErrorConfig(uint32_t startAddr, uint32_t endAddr)
{
    flsRegPtr->FLASH_BED_ADDR_STRT.BED_ADDR_STRT = startAddr >> 4U;
    flsRegPtr->FLASH_BED_ADDR_END.BED_ADDR_END = endAddr >> 4U;
}
   
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
ResultStatus_t FLASH_VerifyAll(const FLASH_CmdConfig_t *config)
{
    ResultStatus_t stat;
    uint32_t ccifFlag;

    ccifFlag = flsRegPtr->FLASH_FSTAT.CCIF;
    if(0U == ccifFlag)
    {
        stat = BUSY;
    }
    else
    {
        if(FLASH_CMD_ACT_WAIT == config->act)
        {
            stat = FLASH_ExecuteCommand(FLASH_CMD_RD1ALL, config->callBack);
        }
        else
        {
            stat = FLASH_ExecuteCommandInt(FLASH_CMD_RD1ALL);
        }
    }

    return stat;
}

/**
 * @brief      Verify that a flash block is erased
 *
 * @param[in]  addr: block start address
 * @param[in]  config: config the action when the command is executing
 *
 * @note       if config->callBack is not NULL, it has to point to a function 
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
                                 const FLASH_CmdConfig_t *config)
{
    ResultStatus_t stat;
    uint32_t ccifFlag;

    ccifFlag = flsRegPtr->FLASH_FSTAT.CCIF;
    if(0U == ccifFlag)
    {
        stat = BUSY;
    }
    else
    {
        flsRegWPtr->FLASH_FADDR = addr;

        if(FLASH_CMD_ACT_WAIT == config->act)
        {
            stat = FLASH_ExecuteCommand(FLASH_CMD_RD1BLK, config->callBack);
        }
        else
        {
            stat = FLASH_ExecuteCommandInt(FLASH_CMD_RD1BLK);
        }
    }

    return stat;
}

/**
 * @brief      Verify that a flash sector is erased
 *
 * @param[in]  addr: sector start address
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
ResultStatus_t FLASH_VerifySector(uint32_t addr,
                                  const FLASH_CmdConfig_t *config)
{
    ResultStatus_t stat;
    uint32_t ccifFlag;

    ccifFlag = flsRegPtr->FLASH_FSTAT.CCIF;
    if(0U == ccifFlag)
    {
        stat = BUSY;
    }
    else
    {
        flsRegWPtr->FLASH_FADDR = addr;
        
        if(FLASH_CMD_ACT_WAIT == config->act)
        {
            stat = FLASH_ExecuteCommand(FLASH_CMD_RD1SCR, config->callBack);
        }
        else
        {
            stat = FLASH_ExecuteCommandInt(FLASH_CMD_RD1SCR);
        }
    }

    return stat;
}

/**
 * @brief      Verify that a flash page is erased
 *
 * @param[in]  addr: page start address
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
ResultStatus_t FLASH_VerifyPage(uint32_t addr,
                                const FLASH_CmdConfig_t *config)
{
    ResultStatus_t stat;
    uint32_t ccifFlag;

    ccifFlag = flsRegPtr->FLASH_FSTAT.CCIF;
    if(0U == ccifFlag)
    {
        stat = BUSY;
    }
    else
    {
        flsRegWPtr->FLASH_FADDR = addr;

        if(FLASH_CMD_ACT_WAIT == config->act)
        {
            stat = FLASH_ExecuteCommand(FLASH_CMD_RD1PG, config->callBack);
        }
        else
        {
            stat = FLASH_ExecuteCommandInt(FLASH_CMD_RD1PG);
        }
    }
    
    return stat;
}

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
                                  const FLASH_CmdConfig_t *config)
{
    ResultStatus_t stat;
    uint32_t ccifFlag;

    ccifFlag = flsRegPtr->FLASH_FSTAT.CCIF;
    if(0U == ccifFlag)
    {
        stat = BUSY;
    }
    else
    {
        flsRegWPtr->FLASH_FADDR = addr;

        if(FLASH_CMD_ACT_WAIT == config->act)
        {
            stat = FLASH_ExecuteCommand(FLASH_CMD_RD1PHR, config->callBack);
        }
        else
        {
            stat = FLASH_ExecuteCommandInt(FLASH_CMD_RD1PHR);
        }
    }

    return stat;
}

/**
 * @brief      Generate MISR signature for flash pages
 *
 * @param[in]  startAddr: page start address
 * @param[in]  endAddr: Ending phrase address. It must be the last phrase in a page.
 * @param[in]  seed: the pointer that points to the 4-word seed
 * @param[in]  signature: the pointer that points the memory that the 128-bit 
 *                        signature result that will be stored through this function.
 *                        it is only valid when config->act == FLASH_CMD_ACT_WAIT.
 *                       If config->act == FLASH_CMD_ACT_INT, the result is not stored
 * @param[in]  config: config the action when the command is executing. If
 *                     FLASH_CMD_ACT_WAIT is selected, the result is stored in
 *                     signature[4]. If FLASH_CMD_ACT_INT is selected, the result
 *                     is not stored. user can get the result in the interrupt
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
                                        const FLASH_CmdConfig_t *config)
{
    ResultStatus_t stat;
    uint32_t ccifFlag;

    ccifFlag = flsRegPtr->FLASH_FSTAT.CCIF;
    if(0U == ccifFlag)
    {
        stat = BUSY;
    }
    else
    {
        flsRegWPtr->FLASH_FADDR = startAddr;
        flsRegWPtr->FLASH_FADDR_END = endAddr;

        flsRegWPtr->FLASH_FDATA0 = seed[0];
        flsRegWPtr->FLASH_FDATA1 = seed[1];
        flsRegWPtr->FLASH_FDATA2 = seed[2];
        flsRegWPtr->FLASH_FDATA3 = seed[3];

        if(FLASH_CMD_ACT_WAIT == config->act)
        {
            stat = FLASH_ExecuteCommand(FLASH_CMD_RDMISR, config->callBack);
            if( SUCC == stat)
            {
                signature[0] = flsRegWPtr->FLASH_FDATA0;
                signature[1] = flsRegWPtr->FLASH_FDATA1;
                signature[2] = flsRegWPtr->FLASH_FDATA2;
                signature[3] = flsRegWPtr->FLASH_FDATA3;
            }
        }
        else
        {
            stat = FLASH_ExecuteCommandInt(FLASH_CMD_RDMISR);
        }
    }

    return stat;
}

/**
 * @brief      Verify that a flash IFR sector is erased
 *
 * @param[in]  addr: sector start address. 
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
ResultStatus_t FLASH_VerifyIfrSector(uint32_t addr,
                                     const FLASH_CmdConfig_t *config)   
{
    ResultStatus_t stat;
    uint32_t ccifFlag;

    ccifFlag = flsRegPtr->FLASH_FSTAT.CCIF;
    if(0U == ccifFlag)
    {
        stat = BUSY;
    }
    else
    {
        flsRegWPtr->FLASH_FADDR = addr;

        if(FLASH_CMD_ACT_WAIT == config->act)
        {
            stat = FLASH_ExecuteCommand(FLASH_CMD_RD1ISCR, config->callBack);
        }
        else
        {
            stat = FLASH_ExecuteCommandInt(FLASH_CMD_RD1ISCR);
        }
    }
    
    return stat;
}

/**
 * @brief      Verify that a flash IFR page is erased
 *
 * @param[in]  addr: IFR page start address
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
ResultStatus_t FLASH_VerifyIfrPage(uint32_t addr,
                                   const FLASH_CmdConfig_t *config)
{
    ResultStatus_t stat;
    uint32_t ccifFlag;

    ccifFlag = flsRegPtr->FLASH_FSTAT.CCIF;
    if(0U == ccifFlag)
    {
        stat = BUSY;
    }
    else
    {
        flsRegWPtr->FLASH_FADDR = addr;
        
        if(FLASH_CMD_ACT_WAIT == config->act)
        {
            stat = FLASH_ExecuteCommand(FLASH_CMD_RD1IPG, config->callBack);
        }
        else
        {
            stat = FLASH_ExecuteCommandInt(FLASH_CMD_RD1IPG);
        }
    }

    return stat;
}

/**
 * @brief      Verify that a flash IFR phrase is erased
 *
 * @param[in]  addr: IFR phrase start address
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
ResultStatus_t FLASH_VerifyIfrPhrase(uint32_t addr,
                                     const FLASH_CmdConfig_t *config)
{
    ResultStatus_t stat;
    uint32_t ccifFlag;

    ccifFlag = flsRegPtr->FLASH_FSTAT.CCIF;
    if(0U == ccifFlag)
    {
        stat = BUSY;
    }
    else
    {
        flsRegWPtr->FLASH_FADDR = addr;

        if(FLASH_CMD_ACT_WAIT == config->act)
        {
            stat = FLASH_ExecuteCommand(FLASH_CMD_RD1IPHR, config->callBack);
        }
        else
        {
            stat = FLASH_ExecuteCommandInt(FLASH_CMD_RD1IPHR);
        }
    }

    return stat;
}


/**
 * @brief      Generate MISR signature for flash IFR pages
 *
 * @param[in]  startAddr: page start address
 * @param[in]  endAddr: Ending phrase address. It must be the last phrase in a page.
 * @param[in]  seed: the pointer that points to the 4-word seed
 * @param[in]  signature: the pointer that points the memory that the 128-bit 
 *                        signature result that will be stored through this function.
 *                        it is only valid when config->act == FLASH_CMD_ACT_WAIT.
 *                       If config->act == FLASH_CMD_ACT_INT, the result is not stored
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
ResultStatus_t FLASH_IfrPagesMircSignature(uint32_t startAddr, uint32_t endAddr,
                                        uint32_t seed[4], uint32_t signature[4],
                                        const FLASH_CmdConfig_t *config)
{
    ResultStatus_t stat;
    uint32_t ccifFlag;

    ccifFlag = flsRegPtr->FLASH_FSTAT.CCIF;
    if(0U == ccifFlag)
    {
        stat = BUSY;
    }
    else
    {
        flsRegWPtr->FLASH_FADDR = startAddr;
        flsRegWPtr->FLASH_FADDR_END = endAddr;
        
        flsRegWPtr->FLASH_FDATA0 = seed[0];
        flsRegWPtr->FLASH_FDATA1 = seed[1];
        flsRegWPtr->FLASH_FDATA2 = seed[2];
        flsRegWPtr->FLASH_FDATA3 = seed[3];
        
        if(FLASH_CMD_ACT_WAIT == config->act)
        {
            stat = FLASH_ExecuteCommand(FLASH_CMD_RDIMISR, config->callBack);
            if( SUCC == stat)
            {
                signature[0] = flsRegWPtr->FLASH_FDATA0;
                signature[1] = flsRegWPtr->FLASH_FDATA1;
                signature[2] = flsRegWPtr->FLASH_FDATA2;
                signature[3] = flsRegWPtr->FLASH_FDATA3;
            }
        }
        else
        {
            stat = FLASH_ExecuteCommandInt(FLASH_CMD_RDIMISR);
        }
    }

    return stat;
}

/**
 * @brief      program a Dflash phrase
 *
 * @param[in]  flashAddr: phrase start address to be programmed
 * @param[in]  dataP: points to data to be programmed into flash
 * @param[in]  config: config the action when the command is executing
 *
 * @note       if config->callBack is not NULL, it has to point to a function 
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
                                                   const FLASH_CmdConfig_t *config)
{
    volatile uint8_t *fData = (volatile uint8_t *)&(flsRegWPtr->FLASH_FDATA0);
    ResultStatus_t stat;
    uint32_t ccifFlag;

    ccifFlag = flsRegPtr->FLASH_FSTAT.CCIF;

    if (!FLASH_VALID_DFLASH_ADDR(flashAddr))
    {
        stat = ERR;
    }
    else if(0U == ccifFlag)
    {
        stat = BUSY;
    }
    else
    {
        flsRegWPtr->FLASH_FADDR = flashAddr;

        for(uint8_t i = 0U; i < FLASH_PHRASE_SIZE; i++)
        {
            fData[i] = dataP[i];
        }

        if(FLASH_CMD_ACT_WAIT == config->act)
        {
            stat = FLASH_ExecuteCommand(FLASH_CMD_PGMPHR, config->callBack);
        }
        else
        {
            stat = FLASH_ExecuteCommandInt(FLASH_CMD_PGMPHR);
        }
    }

    return stat;
}

/**
 * @brief      program a flash phrase
 *
 * @param[in]  flashAddr: phrase start address to be programmed
 * @param[in]  dataP: points to data to be programmed into flash
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
ResultStatus_t FLASH_ProgramPhrase(uint32_t flashAddr, const uint8_t *dataP, 
                                   const FLASH_CmdConfig_t *config)
{
    volatile uint8_t *fData = (volatile uint8_t *)&(flsRegWPtr->FLASH_FDATA0);
    ResultStatus_t stat;
    uint32_t ccifFlag;

    ccifFlag = flsRegPtr->FLASH_FSTAT.CCIF;
    if(0U == ccifFlag)
    {
        stat = BUSY;
    }
    else
    {
        flsRegWPtr->FLASH_FADDR = flashAddr;

        for(uint8_t i = 0U; i < FLASH_PHRASE_SIZE; i++)
        {
            fData[i] = dataP[i];
        }

        if(FLASH_CMD_ACT_WAIT == config->act)
        {
            stat = FLASH_ExecuteCommand(FLASH_CMD_PGMPHR, config->callBack);
        }
        else
        {
            stat = FLASH_ExecuteCommandInt(FLASH_CMD_PGMPHR);
        }
    }

    return stat;
}

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
 * @note       if callBack is not NULL, it has to point to a function 
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
                             flash_cb_t callBack)
{
    uint32_t count;
    uint32_t bufAddr;
    FLASH_CmdConfig_t config;
    ResultStatus_t stat = ERR;

    config.act = FLASH_CMD_ACT_WAIT;
    config.callBack = callBack;
    
    if(((flashAddr % 16U) != 0U)  || (dataP == NULL) 
       || (len == 0U) || ((len % 16U) != 0U))
    {
        stat = ERR;
    }
    else
    {
        /*PRQA S 0306 ++*/
        bufAddr = (uint32_t)dataP;
        /*PRQA S 0306 --*/

        for(count = 0U; count < len; count += 16U)
        {
            /*PRQA S 0306 ++*/
            stat = FLASH_ProgramPhrase((flashAddr + count), (uint8_t *)(bufAddr + count),
                                       &config);
            /*PRQA S 0306 --*/
            if(SUCC != stat)
            {
                break;
            }
        }
    }
    
    return stat;    
}

/**
 * @brief      Erase all flash and IFR space
 *
 * @param[in]  config: config the action when the command is executing
 *
 * @note       if config->callBack is not NULL, it has to point to a function 
 *             that is not in the flash memory 
 *
 * @return     - SUCC -- successful
 *             - ERR -- some error
 *             - BUSY -- flash is executing last command. It can not execute this  
 *                       new command now. 
 *
 */
ResultStatus_t FLASH_EraseAll(const FLASH_CmdConfig_t *config)
{
    ResultStatus_t stat;

    uint32_t ccifFlag;

    ccifFlag = flsRegPtr->FLASH_FSTAT.CCIF;
    if(0U == ccifFlag)
    {
        stat = BUSY;
    }
    else
    {
        if(FLASH_CMD_ACT_WAIT == config->act)
        {
            stat = FLASH_ExecuteCommand(FLASH_CMD_ERSALL, config->callBack);
        }
        else
        {
            stat = FLASH_ExecuteCommandInt(FLASH_CMD_ERSALL);
        }
    }
    
    return stat;
}

/**
 * @brief      Erase a Dflash sector
 *
 * @param[in]  addr: DFlash sector start address. It shall be aligned to 8K bytes.
 * @param[in]  config: config the action when the command is executing
 *
 * @note       if config->callBack is not NULL, it has to point to a function 
 *             that is not in the flash memory that flash commands is executing
 *             in.
 *
 * @return     - SUCC -- successful.
 *             - ERR -- invalid input address, or command execution error or timeout.
 *             - BUSY -- flash is executing last command. It can not execute this  
 *                       new command now.  
 *
 */
ResultStatus_t FLASH_EraseDflashSector(uint32_t addr, const FLASH_CmdConfig_t *config)
{
    ResultStatus_t stat;
    uint32_t ccifFlag;

    ccifFlag = flsRegPtr->FLASH_FSTAT.CCIF;

    if((!FLASH_VALID_DFLASH_ADDR(addr)) || ((addr % FLASH_SECTOR_SIZE) != 0U))
    {
        stat = ERR;
    }
    else if(0U == ccifFlag)
    {
        stat = BUSY;
    }
    else
    {
        flsRegWPtr->FLASH_FADDR = addr;

        if(FLASH_CMD_ACT_WAIT == config->act)
        {
            stat = FLASH_ExecuteCommand(FLASH_CMD_ERSSCR, config->callBack);
        }
        else
        {
            stat = FLASH_ExecuteCommandInt(FLASH_CMD_ERSSCR);
        }
    }
    
    return stat;
}

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
ResultStatus_t FLASH_EraseSector(uint32_t addr, const FLASH_CmdConfig_t *config)
{
    ResultStatus_t stat;
    uint32_t ccifFlag;

    ccifFlag = flsRegPtr->FLASH_FSTAT.CCIF;
    if(0U == ccifFlag)
    {
        stat = BUSY;
    }
    else
    {
        flsRegWPtr->FLASH_FADDR = addr;

        if(FLASH_CMD_ACT_WAIT == config->act)
        {
            stat = FLASH_ExecuteCommand(FLASH_CMD_ERSSCR, config->callBack);
        }
        else
        {
            stat = FLASH_ExecuteCommandInt(FLASH_CMD_ERSSCR);
        }
    }
    
    return stat;
}

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
                                       const FLASH_CmdConfig_t *config)
{
    uint8_t data[16] = {0xECU, 0xF5U, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
                        0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU};
    ResultStatus_t stat;
    uint32_t ccifFlag;
    
    if(DISABLE == debugEraseAllEn)
    {
        data[2] = 0xE2U;
        data[3] = 0x3EU;
    }

    ccifFlag = flsRegPtr->FLASH_FSTAT.CCIF;
    if(0U == ccifFlag)
    {
        stat = BUSY;
    }
    else
    {
        stat = FLASH_ProgramPhrase(FLASH_SECURE_ADDR, data, config);
    }
    
    return stat;
}

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
void FLASH_SetWaitState(uint8_t cycle)
{
    flsRegPtr->FLASH_FCTRL.RWSC = cycle;
}

/**
 * @brief      Get FLASH single-bit ECC error state
 *
 * @param[out]  stat: it points to a struct where the Ecc state will be stored
 *
 * @return    none
 *
 */ 
void FLASH_GetSingleBitEccState(FLASH_EccState_t *state)
{
    uint32_t sbeFlag = 0U;
    uint32_t sbeOverrun = 0U;

    sbeFlag = flsRegPtr->FLASH_SBE_STATE.SBE_FLAG;
    sbeOverrun = flsRegPtr->FLASH_SBE_STATE.SBE_OVERRUN;

    if (0U == sbeFlag)
    {
        state->eccFlag = RESET;
    }
    else 
    {
        state->eccFlag = SET;
        state->addr = (flsRegWPtr->FLASH_SBE_STATE) & 0xFFFFFFF0U;
    }

    if (0U == sbeOverrun)
    {
        state->overrun = RESET;
    }
    else 
    {
        state->overrun = SET;
    }
}

/**
 * @brief      Get FLASH multi-bit ECC error state
 *
 * @param[out]  stat: it points to a struct where the Ecc state will be stored
 *
 * @return    none
 *
 */ 
void FLASH_GetMultiBitEccState(FLASH_EccState_t *state)
{
    uint32_t mbeFlag, mbeOverrun;

    mbeFlag = flsRegPtr->FLASH_MBE_STATE.MBE_FLAG;
    mbeOverrun = flsRegPtr->FLASH_MBE_STATE.MBE_OVERRUN;

    if (0U == mbeFlag)
    {
        state->eccFlag = RESET;
    }
    else 
    {
        state->eccFlag = SET;
        state->addr = (flsRegWPtr->FLASH_MBE_STATE) & 0xFFFFFFF0U;
    }

    if (0U == mbeOverrun)
    {
        state->overrun = RESET;
    }
    else 
    {
        state->overrun = SET;
    }
}

/**
 * @brief      Clear FLASH single-bit ECC error state
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void FLASH_ClearSingleBitEccState(void)
{
    flsRegPtr->FLASH_SBE_STATE.SBE_FLAG = 1U;
}

/**
 * @brief      Clear FLASH multi-bit ECC error state
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void FLASH_ClearMultiBitEccState(void)
{
    flsRegPtr->FLASH_MBE_STATE.MBE_FLAG = 1U;
}

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
void FLASH_InjectEcc(uint32_t addr, uint32_t eccBits, uint32_t dataBits[4])
{
    uint32_t lockFlag;

    lockFlag = flsRegPtr->FLASH_ECC_IN_CTRL.LOCK;
    if(1U == lockFlag)
    {
        /* unlock */
        flsRegWPtr->FLASH_ECC_IN_CTRL = 0x5C000000U;
    }

    flsRegWPtr->FLASH_FDATA0 = dataBits[0];
    flsRegWPtr->FLASH_FDATA1 = dataBits[1];
    flsRegWPtr->FLASH_FDATA2 = dataBits[2];
    flsRegWPtr->FLASH_FDATA3 = dataBits[3];
    flsRegPtr->FLASH_ECC_IN_CTRL.ECC_9BIT = eccBits;
    flsRegPtr->FLASH_ECC_IN_ADDR.ECC_IN_ADDR = addr >> 4U;
    flsRegPtr->FLASH_ECC_IN_CTRL.ECC_IN_EN = 1U;

    flsRegPtr->FLASH_ECC_IN_CTRL.LOCK = 1U;
}

/**
 * @brief      Disable ECC error injection into FLASH 
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void FLASH_DisableEccInjection(void)
{
    uint32_t lockFlag;

    lockFlag = flsRegPtr->FLASH_ECC_IN_CTRL.LOCK;
    if(1U == lockFlag)
    {
        /* unlock */
        flsRegWPtr->FLASH_ECC_IN_CTRL = 0x5C000000U;
    }

    flsRegPtr->FLASH_ECC_IN_CTRL.ECC_IN_EN = 0U;
    flsRegPtr->FLASH_ECC_IN_CTRL.LOCK = 1U;
}

/**
 * @brief      Query if the key entered is correct. If it is correct, exit 
 *             secure mode
 *
 * @param[in]  key: it points to the 96-bit key to be entered.
 *
 * @return     none
 *
 */
void FLASH_QueryKey(uint8_t key[12])
{
    flsRegWPtr->FLASH_FDATA0 = COMMON_BytesToWord(key);
    flsRegWPtr->FLASH_FDATA1 = COMMON_BytesToWord(&key[4]);
    flsRegWPtr->FLASH_FDATA2 = COMMON_BytesToWord(&key[8]);
    
    flsRegPtr->FLASH_FCNFG.BK_QUERY = 1U;    
}

/**
 * @brief      Get flsRegPtr status
 *
 * @param[in]  statMask: the status to be get
 *
 * @return    the status
 *
 */ 
FlagStatus_t FLASH_GetStatus(uint32_t statMask)
{
    FlagStatus_t status;
    
    status = (((flsRegWPtr->FLASH_FSTAT) & (uint32_t)statMask) == 0U)? RESET: SET;
    
    return status;
}


/**
 * @brief      Request to abort a command write sequence
 *
 * @param[in]  none
 *
 * @return - FLASH_ABORT_OK        -- abort flash command succeeded
 *         - FLASH_ABORT_FINISHED  -- abort failed, but flash command has been finished
 *         - FLASH_ABORT_TIMEOUT   -- abort flash command timeout
 *
 */
FLASH_AbortResult_t FLASH_AbortCommand(void)
{
    volatile uint32_t localCnt = 0U;
    uint32_t ccifFlag, cmdabtFlag;
    FLASH_AbortResult_t stat;

    /* No flash command is being executed */
    ccifFlag = flsRegPtr->FLASH_FSTAT.CCIF;
    if(1U == ccifFlag)
    {
        stat = FLASH_ABORT_FINISHED;
    }
    else
    {
        /* Abort executing flash comand */
        flsRegPtr->FLASH_FCTRL.ABTREQ = 1U;
        stat = FLASH_ABORT_TIMEOUT;
        while(localCnt < FLASH_TIMEOUT_ABORT_WAIT_CNT)
        {
            ccifFlag = flsRegPtr->FLASH_FSTAT.CCIF;
            cmdabtFlag = flsRegPtr->FLASH_FSTAT.CMDABT;

            if ((1U == ccifFlag ) && (1U == cmdabtFlag))
            {
                /* clear  CMDABT flag */
                flsRegWPtr->FLASH_FSTAT = FLASH_STATUS_CMDABT_MASK;
                stat = FLASH_ABORT_OK;
                break;
            }
            else if (1U == ccifFlag)
            {
                /* abort failed, but flash command has been finished */
                stat = FLASH_ABORT_FINISHED;
                break;
            }
            else
            {
                localCnt++;
            }
        }
    }

    return stat;
}


/**
 * @brief      Mask/Unmask interrupt
 *
 * @param[in]  intType: select interrupt type
 * @param[in]  intMask: MASK/UNMASK
 *
 * @return    none
 *
 */
void FLASH_IntMask(FLASH_Int_t intType, IntMask_t intMask)
{
    if(UNMASK == intMask)
    {
        flsRegWPtr->FLASH_FCNFG |= flashInterruptMaskTable[intType];
    }
    else
    {
        flsRegWPtr->FLASH_FCNFG &= ~flashInterruptMaskTable[intType];
    }
}

/**
 * @brief      Clear interrupt
 *
 * @param[in]  intType: select interrupt type
 *
 * @return    none
 *
 */ 
void FLASH_IntClear(FLASH_Int_t intType)
{
    switch (intType) {
    case FLASH_INT_CCIF:
         /* this flag can only be cleared by execute a new command,so disable this
           interrupt here */
         flsRegPtr->FLASH_FCNFG.CCIE = 0;
         break;

    case FLASH_INT_DFDIF:
    case FLASH_INT_SFDIF:
         flsRegWPtr->FLASH_FSTAT = flashInterruptMaskTable[intType];
         break;

    case FLASH_INT_ALL:
         flsRegWPtr->FLASH_FSTAT = FLASH_ECC_MASK;
         flsRegPtr->FLASH_FCNFG.CCIE = 0;
         break;

    default:
      /* do nothing */
      break;
    }
}

/**
 * @brief      FLASH command complete IRQHandler
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void FLASH_CmdComplete_DriverIRQHandler(void)
{
    /* command complete flag can only be cleared by execute a new command,
       so disable this interrupt here */
    flsRegPtr->FLASH_FCNFG.CCIE = 0;
    
    if(flashIsrCbFunc[FLASH_INT_CCIF] != NULL)
    {
        flashIsrCbFunc[FLASH_INT_CCIF]();
    }
    COMMON_DSB();
}

/**
 * @brief      FLASH ECC IRQHandler
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void FLASH_Ecc_DriverIRQHandler(void)
{
    uint32_t status =0;
    status = flsRegWPtr->FLASH_FSTAT & FLASH_ECC_MASK;
    
    status &= flsRegWPtr->FLASH_FCNFG;
    
    /* clear int status */
    flsRegWPtr->FLASH_FSTAT = status;
    
    /* multi-bit ECC interrupt */
    if((status & FLASH_INT_DFDIF_MASK) != 0U)
    {
        if(flashIsrCbFunc[FLASH_INT_DFDIF] != NULL)
        {
            flashIsrCbFunc[FLASH_INT_DFDIF]();
        }
        else
        {
            flsRegWPtr->FLASH_FCNFG &= ~flashInterruptMaskTable[FLASH_INT_DFDIF];
        }
    }
    /* single-bit ECC interrupt */
    if((status & FLASH_INT_SFDIF_MASK) != 0U)
    {
        if(flashIsrCbFunc[FLASH_INT_SFDIF] != NULL)
        {
            flashIsrCbFunc[FLASH_INT_SFDIF]();
        }
        else
        {
            flsRegWPtr->FLASH_FCNFG &= ~flashInterruptMaskTable[FLASH_INT_SFDIF];
        }
    }
    COMMON_DSB();
}

/**
 * @brief      Install FLASH callback function
 *
 * @param[in]  intType: select interrupt type
 * @param[in]  cbFun: indicate callback function
 *
 * @return    none
 *
 */ 
void FLASH_InstallCallBackFunc(FLASH_Int_t intType, isr_cb_t * const cbFun)
{
    if (intType < FLASH_INT_ALL)
    {
        flashIsrCbFunc[intType] = cbFun;
    }
}

/**
 * @brief      flash init
 *
 * @param[in]  none
 *
 * @return     - SUCC -- Initialization succeeded.
 *             - ERR  -- Initialization failed.
 *
 */ 
ResultStatus_t FLASH_Init(void)
{
    ResultStatus_t stat = SUCC;
    uint32_t failFlag = flsRegPtr->FLASH_FSTAT.FAIL;

    if(1U == failFlag)
    {
        stat = ERR;
    }

    return stat;
}

/** @} end of group FLASH_Public_Functions */

/** @} end of group FLASH_definitions */

/** @} end of group Z20K14XM_Peripheral_Driver */
