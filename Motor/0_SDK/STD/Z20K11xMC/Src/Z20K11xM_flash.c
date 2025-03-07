/**************************************************************************************************/
/**
 * @file      : Z20K11xM_flash.c
 * @brief     : FLASH module driver file.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (c) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#include "Z20K11xM_flash.h"

/** @addtogroup  Z20K11X_Peripheral_Driver
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
     
#define FLASH_CMD_ERR_MASK     (FLASH_STATUS_CMDABT_MASK \
                               | FLASH_STATUS_ACCERR_MASK \
                               | FLASH_STATUS_FAIL_MASK)

#define FLASH_INT_CCIF_MASK         0x00000080U
#define FLASH_INT_DFDIF_MASK        0x00010000U
#define FLASH_INT_SFDIF_MASK        0x00020000U
#define FLASH_INT_ALL_MASK       (FLASH_INT_CCIF_MASK | FLASH_INT_DFDIF_MASK\
                                  | FLASH_INT_SFDIF_MASK)
#define FLASH_ECC_MASK           (FLASH_INT_DFDIF_MASK | FLASH_INT_SFDIF_MASK)

/** @} end of group FLASH_Private_Defines */

/** @defgroup FLASH_Private_Variables
 *  @{
 */
/*PRQA S 0303 ++*/
static flash_reg_t *const flsRegPtr = (flash_reg_t *) FLASHC_BASE_ADDR;
static flash_reg_w_t *const flsRegWPtr = (flash_reg_w_t *) FLASHC_BASE_ADDR;
/*PRQA S 0303 --*/

static isr_cb_t * flashIsrCbFunc[FLASH_INT_ALL] = {NULL, NULL};

static const uint32_t flashInterruptMaskTable[] =
{
    FLASH_INT_CCIF_MASK,      /* FLASH_INT_CCIF */
    FLASH_INT_DFDIF_MASK,      /* FLASH_INT_DFDIF */
    FLASH_INT_ALL_MASK       /* FLASH_INT_ALL */
};

/** @} end of group FLASH_Private_Variables */

/** @defgroup FLASH_Global_Variables
 *  @{
 */

/** @} end of group FLASH_Global_Variables */

/** @defgroup FLASH_Private_FunctionDeclaration
 *  @{
 */

void FLASH_DriverIRQHandler(void);

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
    volatile uint32_t localCnt = 0U;
    /*PRQA S 0303 ++*/
    flash_reg_t *pFlashReg = (flash_reg_t *) FLASHC_BASE_ADDR;
    /*PRQA S 0303 --*/
    
    while(localCnt < FLASH_TIMEOUT_WAIT_CNT)
    {
        if(pFlashReg->FLASH_FSTAT.CCIF != 0U)
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
    volatile uint32_t localCnt = 0U;
    /*PRQA S 0303 ++*/
    flash_reg_t *pFlashReg = (flash_reg_t *) FLASHC_BASE_ADDR;
    /*PRQA S 0303 --*/
    
    while(localCnt < FLASH_TIMEOUT_WAIT_CNT_ERASE_ALL)
    {
        if(pFlashReg->FLASH_FSTAT.CCIF != 0U)
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
    /*PRQA S 0303 ++*/
    flash_reg_t *pFlashReg = (flash_reg_t *) FLASHC_BASE_ADDR;
    flash_reg_w_t *pFlashRegW = (flash_reg_w_t *) FLASHC_BASE_ADDR;
    /*PRQA S 0303 --*/
    
    if(0U == pFlashReg->FLASH_FSTAT.CCIF)
    {
        stat = BUSY;
    }
    else
    {
        pFlashReg->FLASH_FCMD.CMDCODE = (uint32_t)cmd;
        
        pFlashReg->FLASH_FCTRL.ABTREQ = 0U;

        /* clear ACCERR, PVIOL, CMDABT, CWSABT if any is set */
        pFlashRegW->FLASH_FSTAT = 0x00000074U;

        /* clear CCIF to start cmd */
        pFlashRegW->FLASH_FSTAT = 0x00000080U;

        if(FLASH_CMD_ERSALL == cmd)
        {
            stat = FLASH_WaitEraseAllComplete(callBack);
        }
        else
        {
            stat = FLASH_WaitCmdComplete(callBack);
        }

        if((pFlashRegW->FLASH_FSTAT & FLASH_CMD_ERR_MASK) != 0U)
        {
            stat = ERR;
        }
    }

    return stat;
}

static ResultStatus_t FLASH_ExecuteCommandInt(FLASH_Cmd_t cmd)
{
    ResultStatus_t stat;
    /*PRQA S 0303 ++*/
    flash_reg_t *pFlashReg = (flash_reg_t *) FLASHC_BASE_ADDR;
    flash_reg_w_t *pFlashRegW = (flash_reg_w_t *) FLASHC_BASE_ADDR;
    /*PRQA S 0303 --*/
 
    if(0U == pFlashReg->FLASH_FSTAT.CCIF)
    {
        stat = BUSY;
    }
    else
    {
        pFlashReg->FLASH_FCMD.CMDCODE = (uint32_t)cmd;
        
        pFlashReg->FLASH_FCTRL.ABTREQ = 0;

        /* clear ACCERR, PVIOL, CMDABT, CWSABT if any is set */
        pFlashRegW->FLASH_FSTAT = 0x00000074;

        /* clear CCIF to start cmd */
        pFlashRegW->FLASH_FSTAT = 0x00000080;

        pFlashReg->FLASH_FCNFG.CCIE = 1;    
        stat = SUCC;
    }
    
    return stat;
}

/** @} end of group FLASH_Private_Functions */

/** @defgroup FLASH_Public_Functions
 *  @{
 */

   
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

    if(0U == flsRegPtr->FLASH_FSTAT.CCIF)
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
                                 const FLASH_CmdConfig_t *config)
{
    ResultStatus_t stat;

    if(0U == flsRegPtr->FLASH_FSTAT.CCIF)
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
                                  const FLASH_CmdConfig_t *config)
{
    ResultStatus_t stat;
    
    if(0U == flsRegPtr->FLASH_FSTAT.CCIF)
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
                                const FLASH_CmdConfig_t *config)
{
    ResultStatus_t stat;

    if(0U == flsRegPtr->FLASH_FSTAT.CCIF)
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
ResultStatus_t FLASH_VerifyPhrase(uint32_t addr,
                                  const FLASH_CmdConfig_t *config)
{
    ResultStatus_t stat;

    if(0U == flsRegPtr->FLASH_FSTAT.CCIF)
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
 *                        singnature result that will be stored through this function.
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
ResultStatus_t FLASH_PagesMircSignature(uint32_t startAddr, uint32_t endAddr,
                                        uint32_t seed[4], uint32_t signature[4],
                                        const FLASH_CmdConfig_t *config)
{
    ResultStatus_t stat;
    
    if(0U == flsRegPtr->FLASH_FSTAT.CCIF)
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
                                     const FLASH_CmdConfig_t *config)   
{
    ResultStatus_t stat;
    
    if(0U == flsRegPtr->FLASH_FSTAT.CCIF)
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
                                   const FLASH_CmdConfig_t *config)
{
    ResultStatus_t stat;

    if(0U == flsRegPtr->FLASH_FSTAT.CCIF)
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
                                     const FLASH_CmdConfig_t *config)
{
    ResultStatus_t stat;
    
    if(0U == flsRegPtr->FLASH_FSTAT.CCIF)
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
 *                        singnature result that will be stored through this function.
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
                                        const FLASH_CmdConfig_t *config)
{
    ResultStatus_t stat;
    
    if(0U == flsRegPtr->FLASH_FSTAT.CCIF)
    {
        stat = BUSY;
    }
    else {
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
                                   const FLASH_CmdConfig_t *config)
{
    ResultStatus_t stat;
    volatile uint8_t *fData = (volatile uint8_t *)&(flsRegWPtr->FLASH_FDATA0);
    
    if(0U == flsRegPtr->FLASH_FSTAT.CCIF)
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
            stat = FLASH_ProgramPhrase((flashAddr + count),
                                       (uint8_t *)(bufAddr + count), &config);
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
 * @note       if config->callBack is not NULL, it has to point to a funtion 
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
    
    if(0U == flsRegPtr->FLASH_FSTAT.CCIF)
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
    if(0U == flsRegPtr->FLASH_FSTAT.CCIF)
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
 *                             - DIABLE: debug erase all request cannot erase flash
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
    ResultStatus_t stat = ERR;

    if(0U == flsRegPtr->FLASH_FSTAT.CCIF)
    {
        stat = BUSY;
    }
    else
    {
        if(DISABLE == debugEraseAllEn)
        {
            data[2] = 0xE2U;
            data[3] = 0x3EU;
        }
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
 * @brief      This function will wait until command is completed
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void FLASH_WaitUntilCmdComplete(void)
{
    while(flsRegPtr->FLASH_FSTAT.CCIF == 0U)
    {
    }
}

/**
 * @brief      Get FLASHC status
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
    if (1U == flsRegPtr->FLASH_FSTAT.CCIF)
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
            else if (1U == ccifFlag) {
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
 * @brief      Install callback function
 *
 * @param[in]  intType: select interrrupt type
 * @param[in]  cbFun: indicate callback function
 *
 *
 * @return    none
 *
 */ 
void FLASH_InstallCallBackFunc(FLASH_Int_t intType, isr_cb_t * cbFun)
{
    if(intType < FLASH_INT_ALL)
    {
         flashIsrCbFunc[intType] = cbFun;
    }
}

/**
 * @brief      Mask/Unmask interrupt
 *
 * @param[in]  intType: select interrrupt type
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
 * @param[in]  intType: select interrrupt type
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
         flsRegWPtr->FLASH_FSTAT = flashInterruptMaskTable[intType];
         break;

    case FLASH_INT_ALL:
         flsRegWPtr->FLASH_FSTAT = FLASH_ECC_MASK;
         flsRegPtr->FLASH_FCNFG.CCIE = 0;
         break;
    /*PRQA S 2016 ++*/
    default:
    /*PRQA S 2016 --*/
      break;
    }
}

/**
 * @brief      FLASH IRQHandler
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void FLASH_DriverIRQHandler(void)
{
    uint32_t status, id;    
    
    status = flsRegWPtr->FLASH_FSTAT & flashInterruptMaskTable[FLASH_INT_ALL];
    
    /* get status */
    status &= flsRegWPtr->FLASH_FCNFG;

    if((status & FLASH_INT_CCIF_MASK) != 0U)
    {
        /* this flag can only be cleared by execute a new command,so disable this
           interrupt here */
        flsRegPtr->FLASH_FCNFG.CCIE = 0;
    }
    /* clear int status */
    if((status & FLASH_INT_DFDIF_MASK) != 0U)
    {
        flsRegWPtr->FLASH_FSTAT = FLASH_INT_DFDIF_MASK;
    }    
    
    for(id = 0U; id < (uint32_t)FLASH_INT_ALL; id++)
    {
        if((status & flashInterruptMaskTable[id]) != 0U)
        {
            if(flashIsrCbFunc[id] != NULL)
            {
                flashIsrCbFunc[id]();
            }
            else
            {
                flsRegWPtr->FLASH_FCNFG &= ~flashInterruptMaskTable[id]; 
            }            
        }
    }  
}


/**
 * @brief      flash module init
 *
 * @param[in]  none
 *
 * @return     - SUCC -- Initialization succeeded.
 *             - ERR  -- Initialization failed.
 *
 */ 
ResultStatus_t Flash_Init(void)
{
    ResultStatus_t stat = SUCC;

    if(1U == flsRegPtr->FLASH_FSTAT.FAIL)
    {
        stat = ERR;
    }

    return stat;
}

/** @} end of group FLASH_Public_Functions */

/** @} end of group FLASH_definitions */

/** @} end of group Z20K11X_Peripheral_Driver */
