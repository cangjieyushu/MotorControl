/**************************************************************************************************/
/**
 * @file      : Z20K11xM_sysctrl.c
 * @brief     : SYSCTRL module driver file.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (C) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#include "Z20K11xM_sysctrl.h"

/** @addtogroup  Z20K11X_Peripheral_Driver
 *  @{
 */

/** @defgroup SYSCTRL
 *  @brief SYSCTRL driver modules
 *  @{
 */

/** @defgroup SYSCTRL_Private_Type
 *  @{
 */

typedef volatile union
{
    struct
    {
        uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
        uint32_t RSVD_3_2                : 2;  /* [3:2]          r          */
        uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
        uint32_t RSVD_7                  : 1;  /* [7]            r          */
        uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
        uint32_t RSVD_15_12              : 4;  /* [15:12]        r          */
        uint32_t PWLK                    : 1;  /* [16]           r/w        */
        uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
        uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
        uint32_t PRSTB                   : 1;  /* [21]           r/w        */
        uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
        uint32_t PPR                     : 1;  /* [24]           r/w        */
        uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
        uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
        uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
        uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
        uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } BF;
    uint32_t WORDVAL;
} ModuleRst_t;


/** @} end of group SYSCTRL_Private_Type*/

/** @defgroup SYSCTRL_Private_Defines
 *  @{
 */
/*PRQA S 0303 ++*/
static scm_reg_t *const scmRegPtr = (scm_reg_t *) SCM_BASE_ADDR;        /* SCM Register */
static scm_reg_w_t *const scmRegWPtr = (scm_reg_w_t *) SCM_BASE_ADDR;   /* SCM Word Register */
static parcc_reg_t *const parccRegPtr = (parcc_reg_t *) PARCC_BASE_ADDR;        /* PARCC Register */
static parcc_reg_w_t *const parccRegWPtr = (parcc_reg_w_t *) PARCC_BASE_ADDR;   /* PARCC Word Register */
/*PRQA S 0303 --*/
/** @} end of group SYSCTRL_Private_Defines */

/** @defgroup SYSCTRL_Private_Variables
 *  @{
 */


/** @} end of group SYSCTRL_Private_Variables */

/** @defgroup SYSCTRL_Global_Variables
 *  @{
 */

/** @} end of group SYSCTRL_Global_Variables */

/** @defgroup SYSCTRL_Private_FunctionDeclaration
 *  @{
 */

/** @} end of group SYSCTRL_Private_FunctionDeclaration */

/** @defgroup SYSCTRL_Private_Functions
 *  @{
 */


/** @} end of group SYSCTRL_Private_Functions */

/** @defgroup SYSCTRL_Public_Functions
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
SYSCTRL_DeviceId_t SYSCTRL_GetDeviceId(void)
{
    SYSCTRL_DeviceId_t devId;
    
    devId.packageId = (uint8_t)(scmRegPtr->SCM_DEVID.PACKAGE_ID);
    devId.featureId = (uint8_t)(scmRegPtr->SCM_DEVID.FEATURE_ID);
    devId.RevisionId = (uint8_t)(scmRegPtr->SCM_DEVID.REV_ID);
    devId.familyId = (uint8_t)(scmRegPtr->SCM_DEVID.FAMILY_ID);
    devId.subFamilyId = (uint8_t)(scmRegPtr->SCM_DEVID.SUBFAMILY_ID);
    devId.seriesId = (uint8_t)(scmRegPtr->SCM_DEVID.SERIES_ID);
    devId.memSizeId = (uint8_t)(scmRegPtr->SCM_DEVID.MEMSIZE_ID);
    
    return devId;
}

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
void SYSCTRL_Get128BitUniqueId(uint32_t uniqueId[])
{
    uniqueId[3] = scmRegPtr->SCM_UNIQUE3.UID_127_96;
    uniqueId[2] = scmRegPtr->SCM_UNIQUE2.UID_95_64;
    uniqueId[1] = scmRegPtr->SCM_UNIQUE1.UID_63_32;
    uniqueId[0] = scmRegPtr->SCM_UNIQUE0.UID_31_0;
}


/**
 * @brief      reset module
 *
 * @param[in]  module: select which module to reset. It can select from modules
 *                     defined in type SYSCTRL_Module_t except SYSCTRL_FLASH.
 *
 * @return     none
 *
 */
void SYSCTRL_ResetModule(SYSCTRL_Module_t mod)
{
    ModuleRst_t *mod_p = (ModuleRst_t *)(PARCC_BASE_ADDR + (uint32_t)mod);    /*PRQA S 0303*/
  
    switch(mod)
    {
        case SYSCTRL_WDOG:
        case SYSCTRL_EWDT:
        case SYSCTRL_STIM:
        case SYSCTRL_TIM0:
        case SYSCTRL_TIM1:
        case SYSCTRL_TIM2: 
        case SYSCTRL_TDG0:
        case SYSCTRL_CAN0:
        case SYSCTRL_CAN1:
        case SYSCTRL_UART0:
        case SYSCTRL_UART1:
        case SYSCTRL_UART2:
        case SYSCTRL_UART3:
        case SYSCTRL_SPI0:
        case SYSCTRL_SPI1:
        case SYSCTRL_SPI2:
        case SYSCTRL_I2C0:
        case SYSCTRL_I2C1:
        case SYSCTRL_ADC0:
        case SYSCTRL_CMP:
        case SYSCTRL_CRC:
        case SYSCTRL_DMA:
        case SYSCTRL_DMAMUX:
        case SYSCTRL_PORTA:
        case SYSCTRL_PORTB:
        case SYSCTRL_PORTC:
        case SYSCTRL_PORTD:
        case SYSCTRL_PORTE:
        case SYSCTRL_TMU:
        case SYSCTRL_REGFILE:
        case SYSCTRL_GPIO:
        case SYSCTRL_HWDIV:
            if(mod_p->BF.LOCK != 0U)
            {
                /* unlock this register */
                mod_p->WORDVAL = 0x5B000000U; 
            }

            mod_p->BF.PRSTB = 0U;
            mod_p->BF.PRSTB = 1U;
            mod_p->BF.LOCK = 1U;
            break;
        default:
            /*Do Nothing*/
            break;
    }
}

/**
 * @brief      Enable module. The module is enabled in normal/wait/stop modes.
 *
 * @param[in]  module: select which module to enable. 
 *
 * @return     none
 *
 */
void SYSCTRL_EnableModule(SYSCTRL_Module_t mod)
{
    ModuleRst_t *mod_p = (ModuleRst_t *)(PARCC_BASE_ADDR + (uint32_t)mod);	/*PRQA S 0303*/

    switch(mod)
    {
        case SYSCTRL_WDOG:
        case SYSCTRL_EWDT:
        case SYSCTRL_STIM:
        case SYSCTRL_TIM0:
        case SYSCTRL_TIM1:
        case SYSCTRL_TIM2: 
        case SYSCTRL_TDG0:
        case SYSCTRL_CAN0:
        case SYSCTRL_CAN1:
        case SYSCTRL_UART0:
        case SYSCTRL_UART1:
        case SYSCTRL_UART2:
        case SYSCTRL_UART3:
        case SYSCTRL_SPI0:
        case SYSCTRL_SPI1:
        case SYSCTRL_SPI2:
        case SYSCTRL_I2C0:
        case SYSCTRL_I2C1:
        case SYSCTRL_ADC0:
        case SYSCTRL_CMP:
        case SYSCTRL_CRC:
        case SYSCTRL_DMA:
        case SYSCTRL_DMAMUX:
        case SYSCTRL_PORTA:
        case SYSCTRL_PORTB:
        case SYSCTRL_PORTC:
        case SYSCTRL_PORTD:
        case SYSCTRL_PORTE:
        case SYSCTRL_TMU:
        case SYSCTRL_REGFILE:
        case SYSCTRL_GPIO:
        case SYSCTRL_HWDIV:
            if(mod_p->BF.LOCK != 0U)
            {
                /* unlock this register */
                mod_p->WORDVAL = 0x5B000000; 
            }

            mod_p->BF.PCKMD = 1;

            mod_p->BF.PRSTB = 1;
            mod_p->BF.LOCK = 1;
            break;
            
        case SYSCTRL_FLASH: 
            if(parccRegPtr->PARCC_FLASH.LOCK != 0U)
            {
                parccRegWPtr->PARCC_FLASH = 0x5B000000;
            }
            parccRegPtr->PARCC_FLASH.PCKMD = 1;            
            parccRegPtr->PARCC_FLASH.LOCK = 1;
            break;
        default:
            /*Do Nothing*/
            break;
    }
}

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
void SYSCTRL_EnableModuleWithOffInStopMode(SYSCTRL_Module_t mod)
{
     ModuleRst_t *mod_p = (ModuleRst_t *)(PARCC_BASE_ADDR + (uint32_t)mod);	/*PRQA S 0303*/

    switch(mod)
    {
        case SYSCTRL_WDOG:
        case SYSCTRL_EWDT:
        case SYSCTRL_STIM:
        case SYSCTRL_TIM0:
        case SYSCTRL_TIM1:
        case SYSCTRL_TIM2: 
        case SYSCTRL_TDG0:
        case SYSCTRL_CAN0:
        case SYSCTRL_CAN1:
        case SYSCTRL_UART0:
        case SYSCTRL_UART1:
        case SYSCTRL_UART2:
        case SYSCTRL_UART3:
        case SYSCTRL_SPI0:
        case SYSCTRL_SPI1:
        case SYSCTRL_SPI2:
        case SYSCTRL_I2C0:
        case SYSCTRL_I2C1:
        case SYSCTRL_CMP:
        case SYSCTRL_CRC:
        case SYSCTRL_DMA:
        case SYSCTRL_DMAMUX:
        case SYSCTRL_PORTA:
        case SYSCTRL_PORTB:
        case SYSCTRL_PORTC:
        case SYSCTRL_PORTD:
        case SYSCTRL_PORTE:
        case SYSCTRL_TMU:
        case SYSCTRL_REGFILE:
        case SYSCTRL_GPIO:
        case SYSCTRL_HWDIV:
            if(mod_p->BF.LOCK != 0U)
            {
                /* unlock this register */
                mod_p->WORDVAL = 0x5B000000U; 
            }

            mod_p->BF.PCKMD = 2;
            
            mod_p->BF.PRSTB = 1;
            mod_p->BF.LOCK = 1;
            break;
        case SYSCTRL_FLASH:
            if(parccRegPtr->PARCC_FLASH.LOCK != 0U)
            {
                parccRegWPtr->PARCC_FLASH = 0x5B000000U;
            }
            parccRegPtr->PARCC_FLASH.PCKMD = 2;
            parccRegPtr->PARCC_FLASH.LOCK = 1;
            break;
            
        default:
            /*Do Nothing*/
            break;
    }
}

/**
 * @brief      Disable module
 *
 * @param[in]  module: select which module to disable. 
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
void SYSCTRL_DisableModule(SYSCTRL_Module_t mod)
{
    ModuleRst_t *mod_p = (ModuleRst_t *)(PARCC_BASE_ADDR + (uint32_t)mod);	/*PRQA S 0303*/
  
    switch(mod)
    {
        case SYSCTRL_WDOG:
        case SYSCTRL_EWDT:
        case SYSCTRL_STIM:
        case SYSCTRL_TIM0:
        case SYSCTRL_TIM1:
        case SYSCTRL_TIM2: 
        case SYSCTRL_TDG0:
        case SYSCTRL_CAN0:
        case SYSCTRL_CAN1:
        case SYSCTRL_UART0:
        case SYSCTRL_UART1:
        case SYSCTRL_UART2:
        case SYSCTRL_UART3:
        case SYSCTRL_SPI0:
        case SYSCTRL_SPI1:
        case SYSCTRL_SPI2:
        case SYSCTRL_I2C0:
        case SYSCTRL_I2C1:
        case SYSCTRL_ADC0:
        case SYSCTRL_CMP:
        case SYSCTRL_CRC:
        case SYSCTRL_DMA:
        case SYSCTRL_DMAMUX:
        case SYSCTRL_TMU:
        case SYSCTRL_REGFILE:
        case SYSCTRL_GPIO:
        case SYSCTRL_HWDIV:
            if(mod_p->BF.LOCK != 0U)
            {
                /* unlock this register */
                mod_p->WORDVAL = 0x5B000000; 
            }

            mod_p->BF.PCKMD = 0;
            mod_p->BF.PRSTB = 0;
            mod_p->BF.LOCK = 1;
            break;

        case SYSCTRL_PORTA:
        case SYSCTRL_PORTB:
        case SYSCTRL_PORTC:
        case SYSCTRL_PORTD:
        case SYSCTRL_PORTE:
            if(mod_p->BF.LOCK != 0U)
            {
                /* unlock this register */
                mod_p->WORDVAL = 0x5B000000; 
            }

            mod_p->BF.PCKMD = 0;
            mod_p->BF.LOCK = 1;
            break;

        case SYSCTRL_FLASH:
            if(parccRegPtr->PARCC_FLASH.LOCK != 0U)
            {
                parccRegWPtr->PARCC_FLASH = 0x5B000000U;
            }
            parccRegPtr->PARCC_FLASH.PCKMD = 0;            
            parccRegPtr->PARCC_FLASH.LOCK = 1;
            break;
            
        default:
            /*Do Nothing*/
            break;
    }
}

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
                                ControlState_t supervisorEn)
{
    ModuleRst_t *mod_p = (ModuleRst_t *)(PARCC_BASE_ADDR + (uint32_t)mod);	/*PRQA S 0303*/
  
    switch(mod)
    {
        case SYSCTRL_WDOG:
        case SYSCTRL_EWDT:
        case SYSCTRL_STIM:
        case SYSCTRL_TIM0:
        case SYSCTRL_TIM1:
        case SYSCTRL_TIM2: 
        case SYSCTRL_TDG0:
        case SYSCTRL_CAN0:
        case SYSCTRL_CAN1:
        case SYSCTRL_UART0:
        case SYSCTRL_UART1:
        case SYSCTRL_UART2:
        case SYSCTRL_UART3:
        case SYSCTRL_SPI0:
        case SYSCTRL_SPI1:
        case SYSCTRL_SPI2:
        case SYSCTRL_I2C0:
        case SYSCTRL_I2C1:
        case SYSCTRL_ADC0:
        case SYSCTRL_CMP:
        case SYSCTRL_CRC:
        case SYSCTRL_FLASH: 
        case SYSCTRL_DMA:
        case SYSCTRL_DMAMUX:
        case SYSCTRL_PORTA:
        case SYSCTRL_PORTB:
        case SYSCTRL_PORTC:
        case SYSCTRL_PORTD:
        case SYSCTRL_PORTE:
        case SYSCTRL_TMU:
        case SYSCTRL_REGFILE:
        case SYSCTRL_GPIO:
        case SYSCTRL_HWDIV:
            if(mod_p->BF.LOCK != 0U)
            {
                /* unlock this register */
                mod_p->WORDVAL = 0x5B000000; 
            }

            mod_p->BF.PWLK = (uint32_t)writeLock;
            mod_p->BF.PSUPVACEN = (uint32_t)supervisorEn;
            mod_p->BF.LOCK = 1;
            break;
        default:
            /*Do Nothing*/
            break;
    }
}

/**
 * @brief      config SRAM ECC. SRAM ECC is enabled by default. ECC config can  
 *             be changed through this function.
 *
 * @param[in]  sram: select which SRAM to config.
 * @param[in]  eccConfig: points to the struct that stores the parameters. 
 *
 * @return     none
 *
 */
void SYSCTRL_SramEccConfig(SYSCTRL_Sram_t sram, 
                           const SYSCTRL_SramEcc_t *eccConfig)
{
    if(SYSCTRL_SRAM_L == sram)
    {
        scmRegPtr->SCM_ECCOPT.SRAM0_ECCMB_DIS = (eccConfig->multiBitEccEn == ENABLE) ? 0U : 1U;
        scmRegPtr->SCM_ECCOPT.SRAM0_ECCSB_DIS = (eccConfig->singleBitEccEn == ENABLE) ? 0U : 1U;
        scmRegPtr->SCM_ECCOPT.SRAM0_ECCR_DIS = (eccConfig->readEccEn == ENABLE) ? 0U : 1U;
        scmRegPtr->SCM_ECCOPT.SRAM0_ECCW_DIS = (eccConfig->writeEccEn == ENABLE) ? 0U : 1U;
    }
    
    if(SYSCTRL_SRAM_U == sram)
    {
        scmRegPtr->SCM_ECCOPT.SRAM1_ECCMB_DIS = (eccConfig->multiBitEccEn == ENABLE) ? 0U : 1U;
        scmRegPtr->SCM_ECCOPT.SRAM1_ECCSB_DIS = (eccConfig->singleBitEccEn == ENABLE) ? 0U : 1U;
        scmRegPtr->SCM_ECCOPT.SRAM1_ECCR_DIS = (eccConfig->readEccEn == ENABLE) ? 0U : 1U;
        scmRegPtr->SCM_ECCOPT.SRAM1_ECCW_DIS = (eccConfig->writeEccEn == ENABLE) ? 0U : 1U;
    }
}

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
FlagStatus_t SYSCTRL_GetSramEccErrStatus(SYSCTRL_Sram_t sram, uint32_t errMask)
{
    FlagStatus_t res = RESET;

    if(SYSCTRL_SRAM_L == sram)
    {
        res = ((scmRegWPtr->SCM_ECC0ST & (uint32_t)errMask) != 0U)? SET : RESET;
    }
    
    if(SYSCTRL_SRAM_U == sram)
    {
        res = ((scmRegWPtr->SCM_ECC1ST & (uint32_t)errMask) != 0U)? SET : RESET;
    }
    
    return res;
}

/**
 * @brief      Clear SRAM ECC error status
 *
 * @param[in]  sram: select which SRAM to config.
 * @param[in]  errMask: select the error mask. 
 *
 * @return none
 *
 */
void SYSCTRL_ClearSramEccErrStatus(SYSCTRL_Sram_t sram, uint32_t errMask)
{
    if(SYSCTRL_SRAM_L == sram)
    {
       scmRegWPtr->SCM_ECC0ST = (uint32_t)errMask;
    }
    
    if(SYSCTRL_SRAM_U == sram)
    {
       scmRegWPtr->SCM_ECC1ST = (uint32_t)errMask;
    }
}
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
                                         SYSCTRL_SramEccErrCause_t *cause)
{
    if(SYSCTRL_SRAM_L == sram)
    {
        cause->errAddr = scmRegWPtr->SCM_ECC0FADDR;
        cause->faultData = scmRegWPtr->SCM_ECC0FDATA;
        cause->write = (scmRegPtr->SCM_ECC0ST.EFW != 0U) ? SET : RESET;
        cause->faultMaster = (SYSCTRL_Master_t)(scmRegPtr->SCM_ECC0ST.EFMST);
        cause->faultSize = (SYSCTRL_AccessSize_t)(scmRegPtr->SCM_ECC0ST.EFSIZE);
        cause->accessType = (((scmRegWPtr->SCM_ECC0ST)& 0x000000001UL) == 0U)?
                               SYSCTRL_ACC_TYPE_OPCODE : SYSCTRL_ACC_TYPE_DATA;
        cause->accessMode = (((scmRegWPtr->SCM_ECC0ST)&0x000000002UL) == 0U)?
                               SYSCTRL_ACC_MODE_USER : SYSCTRL_ACC_MODE_PRIVIL;
        cause->bufferable = (((scmRegWPtr->SCM_ECC0ST)&0x000000004UL) == 0U) ?
                               RESET : SET;
        cause->cacheable = (((scmRegWPtr->SCM_ECC0ST)&0x000000008UL) == 0U) ?
                               RESET : SET;
    }
    
    if(SYSCTRL_SRAM_U == sram)
    {
        cause->errAddr = scmRegWPtr->SCM_ECC1FADDR;
        cause->faultData = scmRegWPtr->SCM_ECC1FDATA;
        cause->write = (scmRegPtr->SCM_ECC1ST.EFW != 0U) ? SET : RESET;
        cause->faultMaster = (SYSCTRL_Master_t)(scmRegPtr->SCM_ECC1ST.EFMST);
        cause->faultSize = (SYSCTRL_AccessSize_t)(scmRegPtr->SCM_ECC1ST.EFSIZE);
        cause->accessType = (((scmRegWPtr->SCM_ECC1ST)& 0x000000001UL) == 0U)?
                               SYSCTRL_ACC_TYPE_OPCODE : SYSCTRL_ACC_TYPE_DATA;
        cause->accessMode = (((scmRegWPtr->SCM_ECC1ST)&0x000000002UL) == 0U)?
                               SYSCTRL_ACC_MODE_USER : SYSCTRL_ACC_MODE_PRIVIL;
        cause->bufferable = (((scmRegWPtr->SCM_ECC1ST)&0x000000004UL) == 0U) ?
                               RESET : SET;
        cause->cacheable = (((scmRegWPtr->SCM_ECC1ST)&0x000000008UL) == 0U) ?
                               RESET : SET;
    }
}
/**
 * @brief      Set Software trigger to TMU
 *
 * @param[in]  source: select software trigger source to TMU
 * @param[in]  level: trigger level to TMU. 
 *
 * @return     none
 *
 */
void SYSCTRL_SoftTriggerToTmu(SYSCTRL_TriggerSrc_t source, SYSCTRL_TriggerLevel_t level)
{
    volatile uint32_t tmp;
    
    if(SYSCTRL_TRIG_LEVEL_LOW == level)
    {
        tmp = scmRegWPtr->SCM_MISCCTL & (~(1UL << (uint32_t)source));
        scmRegWPtr->SCM_MISCCTL = tmp;
    }
    else
    {
        tmp = scmRegWPtr->SCM_MISCCTL | (1UL << (uint32_t)source);
        scmRegWPtr->SCM_MISCCTL = tmp;
    }    
}
/** @} end of group SYSCTRL_Public_Functions */

/** @} end of group SYSCTRL_definitions */

/** @} end of group Z20K11X_Peripheral_Driver */
