/**************************************************************************************************/
/**
 * @file      : Z20K11xM_pmu.h
 * @brief     : PMU module driver header file.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (c) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#ifndef Z20K11XM_PMU_H
#define Z20K11XM_PMU_H

#include "Z20K11xM_drv.h"

/** @addtogroup  Z20K11X_Peripheral_Driver
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
    PMU_VDD_LVD_LP  = 0U,          /*!< PMU VDD 5V LVD(detecting) detect enable/disable under low power mode  */
    PMU_VDD_LVD_ACT = 1U,          /*!< PMU VDD 5V LVD(detecting) detect enable/disable under active mode*/
    PMU_VDD_LVD_RE  = 3U,          /*!< PMU VDD 5V LVD(detecting) reset enable/disable */
    PMU_VDD_LVW     = 4U,          /*!< PMU VDD 5V LVW(warning) detect control  */
    PMU_REF_BUF_1V  = 8U,          /*!< PMU Reference 1V output enable with buf control  */
    PMU_LDO_LVD_ACT = 9U,          /*!< PMU LDO LVD detect enable/disable for active mode  */
    PMU_LDO_LVD_LP  = 10U,         /*!< PMU LDO LVD detect enable/disable for low power mode  */
    PMU_LDO_CLAMP   = 11U          /*!< PMU LDO clamp enable/disable  */
} PMU_Ctrl_t;


/**
 *  @brief PMU int type definition
 */
typedef enum
{
    PMU_VDD_LVW_INT = 0U,           /*!< PMU VDD 5V LVW INT     */
    PMU_VDD_LVD_INT,                /*!< PMU VDD 5V LVD INT     */
    PMU_INT_ALL
} PMU_Int_t;

/** @} end of group PMU_Public_Types */

/** @defgroup PMU_Public_FunctionDeclaration
 *  @brief PMU functions declaration
 *  @{
 */

/**
 * @brief       Clear Isolation status
 *
 * @return none
 *
 */
void PMU_IsoClr(void);

/**
 * @brief       Enable/Disable PMU Relevant Voltage's Function
 *
 * @param[in]  ctrlType:     Select the PMU Control type defined in PMU_Ctrl_t.
 * @param[in]  cmd:          Enable or Disable.
 *
 * @return none
 *
 */
void PMU_Ctrl(PMU_Ctrl_t ctrlType, ControlState_t cmd);

/**
 * @brief       Pmu Get Status Function
 *
 * @param[in]  intType:    Int Type.
 *
 * @return     status.
 *
 */
FlagStatus_t PMU_GetIntStatus(PMU_Int_t intType);

/**
 * @brief       Mask/Unmask the Relevant Interrupt Function
 *
 * @param[in]  intType:      Select the interrupt type.
 * @param[in]  intMask:          UNMASK or MASK.
 *
 * @return none
 *
 */
void PMU_IntMask(PMU_Int_t intType, IntMask_t intMask);

/**
 * @brief       Clear the Relevant Interrupt Status
 *
 * @param[in]  intType:      Select the interrupt type.
 *
 * @return none
 *
 */
void PMU_IntClr(PMU_Int_t intType);

/**
 * @brief      install call back function
 *
 * @param[in]  intId: select the interrupt type
 * @param[in]  cbFun: pointer to callback function
 *
 * @return none
 *
 */
void PMU_InstallCallBackFunc(PMU_Int_t intType,isr_cb_t * cbFun);


/** @} end of group PMU_Public_FunctionDeclaration */

/** @} end of group PMU */

/** @} end of group Z20K11X_Peripheral_Driver */
#endif /* Z20K11XM_PMU_H */
