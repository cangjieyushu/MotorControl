/**************************************************************************************************/
/**
 * @file      : Z20K11xM_tmu.c
 * @brief     : TMU module driver file.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (C) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#include "Z20K11xM_tmu.h"

/** @addtogroup  Z20K11X_Peripheral_Driver
 *  @{
 */

/** @defgroup TMU
 *  @brief TMU driver modules
 *  @{
 */

/** @defgroup TMU_Private_Type
 *  @{
 */

/** @} end of group TMU_Private_Type*/

/** @defgroup TMU_Private_Defines
 *  @{
 */
 
/*PRQA S 0303,0306 ++*/
static tmu_reg_t *const tmuRegPtr = (tmu_reg_t *) TMU_BASE_ADDR;/*!< TMU Register */
static tmu_reg_w_t *const tmuRegWPtr = (tmu_reg_w_t *) TMU_BASE_ADDR;/*!< TMU word Register */
/*PRQA S 0303,0306 ++*/


/*@} end of group TMU_Private_Defines */

/** @defgroup TMU_Private_Variables
 *  @{
 */

/*@} end of group TMU_Private_Variables */

/** @defgroup TMU_Global_Variables
 *  @{
 */

/** @} end of group TMU_Global_Variables */

/** @defgroup TMU_Public_Functions
 *  @{
 */

/**
 * @brief       set source for TMU target module.
 *
 * @param[in]  source:           selects one of the TMU sources
 * @param[in]  module:           selects target module of the TMU modules
 *
 * @return none
 *
 */
void TMU_SetSourceForModule(TMU_Source_t source, TMU_Module_t module)
{
    tmuRegPtr->TMU_CFGn[module].SEL = (uint32_t)source;
}

/**
 * @brief       get source for TMU target module.
 *
 * @param[in]  module:           selects target module of the TMU modules
 *
 * @return the selected source for target module.
 *
 */
TMU_Source_t TMU_GetSourceForModule(TMU_Module_t module)
{
    uint32_t tmuSource;
    
    tmuSource = tmuRegPtr->TMU_CFGn[module].SEL;
    
    return (TMU_Source_t)tmuSource;
}

/**
 * @brief       Enable/Disable target module in TMU modules.
 *
 * @param[in]  module:           selects target module of the TMU modules
 * @param[in]  cmd:              TMU Module Control: ENABLE; DISABLE.
 *
 * @return none
 *
 */
void TMU_ModuleCmd(TMU_Module_t module, ControlState_t cmd)
{
    tmuRegPtr->TMU_CFGn[module].EN = (uint32_t)cmd;
}

/**
 * @brief Lock Relevant Register for TMU target module, then register is read only.
 *
 * @param[in]  module:           selects target module of the TMU modules
 *
 * @return none.
 *
 */
void TMU_SetLockForModule(TMU_Module_t module)
{
    tmuRegPtr->TMU_CFGn[module].LOCK = 1U;
}

/**
 * @brief Unlock Relevant Register for TMU target module, then register is writable.
 *
 * @param[in]  module:           selects target module of the TMU modules
 *
 * @return none.
 *
 */
void TMU_SetUnlockForModule(TMU_Module_t module)
{
    uint32_t wordVal = tmuRegWPtr->TMU_CFGn[module] & 0x00FFFFFFUL;
    
    tmuRegWPtr->TMU_CFGn[module] = wordVal | 0x5B000000UL;
}

/**
 * @brief Get Lock status for TMU target module.
 *
 * @param[in]  module:           selects target module of the TMU modules
 *
 * @return Lock status: SET----Locked; RESET----Unlocked.
 *
 */
FlagStatus_t TMU_GetLockStatusForModule(TMU_Module_t module)
{    
    return (FlagStatus_t)tmuRegPtr->TMU_CFGn[module].LOCK;
}

/** @} end of group TMU_Public_Functions */

/** @} end of group TMU_definitions */

/** @} end of group Z20K11X_Peripheral_Driver */
