/**************************************************************************************************/
/**
 * @file     sysctrl_drv.c
 * @brief    SYSCTRL module driver file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 *
 **************************************************************************************************/

#include "sysctrl_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
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
#define SCM         ((scm_reg_t *) SCM_BASE_ADDR)          /*!< System Control Register */
#define SCM_W       ((scm_reg_w_t *) SCM_BASE_ADDR)        /*!< System Control Register */

static ModuleRst_t * const parccRegPtrArray[] =
{
    /*PRQA S 0303 ++*/
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_WDOG),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_EWDT),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_STIM),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_TIM0),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_TIM1),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_TIM2),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_TIM3),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_MCPWM0),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_MCPWM1),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_TDG0),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_TDG1),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_CAN0),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_CAN1),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_CAN2),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_CAN3),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_CAN4),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_CAN5),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_CAN6),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_CAN7),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_UART0),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_UART1),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_UART2),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_UART3),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_UART4),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_UART5),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_SPI0),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_SPI1),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_SPI2),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_SPI3),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_I2C0),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_I2C1),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_I2S0),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_I2S1),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_RSVDOx84),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_ADC0),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_ADC1),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_CMP),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_CRC),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_AES),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_TRNG),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_FLASH),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_RSVDOxA4),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_DMA),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_DMAMUX),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_PORTA),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_PORTB),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_PORTC),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_PORTD),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_PORTE),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_TMU),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_REGFILE),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_SMPU),
    (ModuleRst_t *)(PARCC_BASE_ADDR+(uint32_t)SYSCTRL_GPIO)
    /*PRQA S 0303 --*/
};
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
 * @brief      reset module
 *
 * @param[in]  module: select which module to reset. 
 *
 * @return     none
 *
 */
void SYSCTRL_ResetModule(SYSCTRL_Module_t mod)
{
    uint32_t module;

    module = (uint32_t)mod;
    ModuleRst_t *mod_p = (ModuleRst_t *)(parccRegPtrArray[module>>2U]);

    if(mod_p->BF.LOCK != 0U)
    {
        /* unlock this register */
        mod_p->WORDVAL = 0x5B000000U; 
    }

    mod_p->BF.PRSTB = 0U;
    mod_p->BF.PRSTB = 1U;
    mod_p->BF.LOCK = 1U;
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
    uint32_t module;

    module = (uint32_t)mod;
    ModuleRst_t *mod_p = (ModuleRst_t *)(parccRegPtrArray[module>>2U]);
    
    if(mod_p->BF.LOCK != 0U)
    {
        /* unlock this register */
        mod_p->WORDVAL = 0x5B000000U; 
    }

    mod_p->BF.PCKMD = 1U;
    mod_p->BF.PRSTB = 1U;
    mod_p->BF.LOCK = 1U;
}

/**
 * @brief      Enable module but the module is off in stop mode.
 *
 * @param[in]  module: select which module to enable. 
 *
 * @return     none
 *
 */
void SYSCTRL_EnableModuleWithOffInStopMode(SYSCTRL_Module_t mod)
{
    uint32_t module;

    module = (uint32_t)mod;
    ModuleRst_t *mod_p = (ModuleRst_t *)(parccRegPtrArray[module>>2U]);
    
    if(mod_p->BF.LOCK != 0U)
    {
        /* unlock this register */
        mod_p->WORDVAL = 0x5B000000U; 
    }

    mod_p->BF.PCKMD = 2U;
    mod_p->BF.PRSTB = 1U;
    mod_p->BF.LOCK = 1U;
}

/**
 * @brief      Disable module
 *
 * @param[in]  module: select which module to disable. 
 *
 * @return     none
 *
 */
void SYSCTRL_DisableModule(SYSCTRL_Module_t mod)
{
    uint32_t module;

    module = (uint32_t)mod;
    ModuleRst_t *mod_p = (ModuleRst_t *)(parccRegPtrArray[module>>2U]);
    
    if(mod_p->BF.LOCK != 0U)
    {
        /* unlock this register */
        mod_p->WORDVAL = 0x5B000000U; 
    }

    mod_p->BF.PCKMD = 0U;
    mod_p->BF.PRSTB = 0U;
    mod_p->BF.LOCK = 1U;
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
    uint32_t module;

    module = (uint32_t)mod;
    ModuleRst_t *mod_p = (ModuleRst_t *)(parccRegPtrArray[module>>2U]);

    if(mod_p->BF.LOCK != 0U)
    {
        /* unlock this register */
        mod_p->WORDVAL = 0x5B000000U; 
    }

    if (SYSCTRL_FLASH != mod)
    {
        mod_p->BF.PWLK = (uint32_t)writeLock;
    }

    mod_p->BF.PSUPVACEN = (uint32_t)supervisorEn;
    mod_p->BF.LOCK = 1U;
}

/** @} end of group SYSCTRL_Public_Functions */

/** @} end of group SYSCTRL */

/** @} end of group Z20K14XM_Peripheral_Driver */
