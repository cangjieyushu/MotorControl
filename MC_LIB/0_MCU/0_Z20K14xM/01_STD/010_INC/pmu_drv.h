/**************************************************************************************************/
/**
 * @file     pmu_drv.h
 * @brief    PMU driver module header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#ifndef PMU_DRV_H
#define PMU_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  PMU
 *  @{
 */

/** @defgroup PMU_Public_Types 
 *  @{
 */

/**
 *  @brief PMU voltage of LVD and LVW type definition
 */
typedef enum
{
    PMU_VDD_LVW     = 4U,          /*!< PMU VDD 5V LVW(warning) detect control*/
    PMU_REF_BUF_1V  = 8U,          /*!< PMU Reference 1V output enable with buf control */
} PMU_Ctrl_t;

/**
 *  @brief PMU LDO type definition
 */
typedef enum
{
    PMU_LDO_CORE  = 0U,            /*!< PMU LDO-core  type*/
    PMU_LDO_CLOCK = 1U,            /*!< PMU LDO-clock type*/
    PMU_LDO_FLASH = 2U,            /*!< PMU LDO-flash type*/
    PMU_LDO_AOA   = 4U             /*!< PMU LDO-AOA type*/
} PMU_Ldo_t;

/**
 *  @brief PMU int type definition
 */
typedef enum
{
    PMU_VDD_LVW_INT = 0U,          /*!< PMU VDD 5V LVW INT*/
    PMU_VDD_LVD_INT,               /*!< PMU VDD 5V LVD INT*/
    PMU_INT_ALL
} PMU_Int_t;

/** @} end of group PMU_Public_Types */

/** @defgroup PMU_Public_FunctionDeclaration
 *  @brief PMU functions declaration
 *  @{
 */
/**
 * @brief	   Clear Isolation status
 *
 * @param[in]  none
 *
 * @return	   none
 *
 */
void PMU_IsoClr(void);

/**
 * @brief	   Enable/Disable PMU Relevant Voltage's Function
 *
 * @param[in]  ctrlType: Select the PMU Control type defined in PMU_Ctrl_t
 * @param[in]  cmd: 	 Enable or Disable
 *
 * @return	   none
 *
 */
void PMU_Ctrl(PMU_Ctrl_t ctrlType, ControlState_t cmd);

/**
 * @brief      Enable/Disable PMU LDO LVD under active mode
 *             It is recommended to keep the LVD detect feature enabled.
 *
 * @param[in]  ldoType: Select the LDO type
 * @param[in]  cmd:     Enable or Disable
 *
 * @return     none
 *
 */
void PMU_LdoLvdEnCtrlInActive(PMU_Ldo_t ldoType, ControlState_t cmd);

/**
 * @brief      Enable/Disable PMU LDO LVD under Low Power Function
 *             It is recommended to keep the LVD detect feature enabled in stop mode.
 *
 * @param[in]  ldoType: Select the LDO type
 * @param[in]  cmd:     Enable or Disable
 *
 * @return     none
 *
 */
void PMU_LdoLvdEnCtrlInLowPower(PMU_Ldo_t ldoType, ControlState_t cmd);

/**
 * @brief      Enable/Disable PMU Reset when LDO LVD detected Function
 *             It is recommended to keep the reset feature enabled.
 *
 * @param[in]  ldoType: Select the LDO type
 * @param[in]  cmd:     Enable or Disable
 *
 * @return     none
 *
 */
void PMU_LdoLvdResetEnCtrl(PMU_Ldo_t ldoType, ControlState_t cmd);

/**
 * @brief	   Pmu Get LVD Status for LDO
 *
 * @param[in]  ldoType: Select the LDO type
 *
 * @return	   FlagStatus_t
 *
 */
FlagStatus_t PMU_GetLdoLvdStatus(PMU_Ldo_t ldoType);

/**
 * @brief	   Clear Pmu LVD Status for LDO
 *
 * @param[in]  ldoType: Select the LDO type
 *
 * @return	   none
 *
 */
void PMU_ClearLdoLvdStatus(PMU_Ldo_t ldoType);

/**
 * @brief	   Pmu Get LVD Flag Function
 *
 * @param[in]  intType: Select the low voltage behavior type
 *
 * @return	   FlagStatus_t
 *
 */
FlagStatus_t PMU_GetIntStatus(PMU_Int_t intType);

/**
 * @brief	   Mask/Unmask the Relevant Interrupt Function
 *
 * @param[in]  intType: Select the interrupt type
 * @param[in]  intMask: UNMASK or MASK
 *
 * @return	   none
 *
 */
void PMU_IntMask(PMU_Int_t intType, IntMask_t intMask);

/**
 * @brief	   Clear the Relevant Interrupt Status
 *
 * @param[in]  intType: Select the interrupt type
 *
 * @return	   none
 *
 */
void PMU_IntClr(PMU_Int_t intType);

/**
 * @brief	   Install call back function
 *
 * @param[in]  intType: select the interrupt type
 * @param[in]  cbFun:	pointer to callback function
 *
 * @return	   none
 *
 */
void PMU_InstallCallBackFunc(PMU_Int_t intType,isr_cb_t * cbFun);

/**
 * @brief	   Get LPO Clock Ready Status
 *
 * @param[in]  none
 *
 * @return	   FlagStatus_t
 *
 */
FlagStatus_t PMU_IsLpoClkReady(void);

/** @} end of group PMU_Public_FunctionDeclaration*/

/** @} end of group PMU */

/** @} end of group Z20K14XM_Peripheral_Driver*/
#endif /* PMU_DRV_H */
