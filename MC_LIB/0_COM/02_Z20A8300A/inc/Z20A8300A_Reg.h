/**************************************************************************************************/
/** 
 * @file      : Z20A8300A_Reg.h
 * @brief     : Z20A8300A Register Define Header File.
 *                 - Platform: Z20A8300A
 * @version   : V0.7.0
 * @date      : September-2022
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @Copyright : Copyright (c) 2022-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
#ifndef Z20A8300A_REG_H
#define Z20A8300A_REG_H

/** @addtogroup Z20A8300A_Driver
 *  @{
 */

/** @addtogroup Z20A8300A_Reg
 *  @brief Z20A8300A Register define.
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/** @defgroup Reg_Public_MacroDefinition
 *  @{
 */

/*!< @name Config0 - Z20A8300A Config Register 0 */
/*!< @{ */

#define Z20A8300A_CONFIG0_DT_MASK                0x3fU
#define Z20A8300A_CONFIG0_DT_SHIFT               0U
#define Z20A8300A_CONFIG0_DT_WIDTH               6U
#define Z20A8300A_CONFIG0_DT_SET(x)             (((uint32_t)((uint32_t)(x)))&Z20A8300A_CONFIG0_DT_MASK)
#define Z20A8300A_CONFIG0_DT_GET(x)             ((uint32_t)(((uint32_t)(x))&Z20A8300A_CONFIG0_DT_MASK))
#define Z20A8300A_CONFIG0_OTS_MASK                0xc0U
#define Z20A8300A_CONFIG0_OTS_SHIFT               6U
#define Z20A8300A_CONFIG0_OTS_WIDTH               2U
#define Z20A8300A_CONFIG0_OTS_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_CONFIG0_OTS_SHIFT))&Z20A8300A_CONFIG0_OTS_MASK)
#define Z20A8300A_CONFIG0_OTS_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_CONFIG0_OTS_MASK))>>Z20A8300A_CONFIG0_OTS_SHIFT)
#define Z20A8300A_CONFIG0_VBOV_MASK                0x100U
#define Z20A8300A_CONFIG0_VBOV_SHIFT               8U
#define Z20A8300A_CONFIG0_VBOV_WIDTH               1U
#define Z20A8300A_CONFIG0_VBOV_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_CONFIG0_VBOV_SHIFT))&Z20A8300A_CONFIG0_VBOV_MASK)
#define Z20A8300A_CONFIG0_VBOV_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_CONFIG0_VBOV_MASK))>>Z20A8300A_CONFIG0_VBOV_SHIFT)
/*!< @} */

/*!< @name Config1 - Z20A8300A Config Register 1 */
/*!< @{ */

#define Z20A8300A_CONFIG1_TCB_MASK                0x1fU
#define Z20A8300A_CONFIG1_TCB_SHIFT               0U
#define Z20A8300A_CONFIG1_TCB_WIDTH               5U
#define Z20A8300A_CONFIG1_TCB_SET(x)             (((uint32_t)((uint32_t)(x)))&Z20A8300A_CONFIG1_TCB_MASK)
#define Z20A8300A_CONFIG1_TCB_GET(x)             ((uint32_t)(((uint32_t)(x))&Z20A8300A_CONFIG1_TCB_MASK))
#define Z20A8300A_CONFIG1_OCT_MASK                0x1e0U
#define Z20A8300A_CONFIG1_OCT_SHIFT               5U
#define Z20A8300A_CONFIG1_OCT_WIDTH               4U
#define Z20A8300A_CONFIG1_OCT_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_CONFIG1_OCT_SHIFT))&Z20A8300A_CONFIG1_OCT_MASK)
#define Z20A8300A_CONFIG1_OCT_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_CONFIG1_OCT_MASK))>>Z20A8300A_CONFIG1_OCT_SHIFT)
/*!< @} */

/*!< @name Config2 - Z20A8300A Config Register 2 */
/*!< @{ */

#define Z20A8300A_CONFIG2_TVB_MASK                0x3fU
#define Z20A8300A_CONFIG2_TVB_SHIFT               0U
#define Z20A8300A_CONFIG2_TVB_WIDTH               6U
#define Z20A8300A_CONFIG2_TVB_SET(x)             (((uint32_t)((uint32_t)(x)))&Z20A8300A_CONFIG2_TVB_MASK)
#define Z20A8300A_CONFIG2_TVB_GET(x)             ((uint32_t)(((uint32_t)(x))&Z20A8300A_CONFIG2_TVB_MASK))
#define Z20A8300A_CONFIG2_FCP_MASK                0xc0U
#define Z20A8300A_CONFIG2_FCP_SHIFT               6U
#define Z20A8300A_CONFIG2_FCP_WIDTH               2U
#define Z20A8300A_CONFIG2_FCP_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_CONFIG2_FCP_SHIFT))&Z20A8300A_CONFIG2_FCP_MASK)
#define Z20A8300A_CONFIG2_FCP_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_CONFIG2_FCP_MASK))>>Z20A8300A_CONFIG2_FCP_SHIFT)
#define Z20A8300A_CONFIG2_CPM_MASK                0x100U
#define Z20A8300A_CONFIG2_CPM_SHIFT               8U
#define Z20A8300A_CONFIG2_CPM_WIDTH               1U
#define Z20A8300A_CONFIG2_CPM_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_CONFIG2_CPM_SHIFT))&Z20A8300A_CONFIG2_CPM_MASK)
#define Z20A8300A_CONFIG2_CPM_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_CONFIG2_CPM_MASK))>>Z20A8300A_CONFIG2_CPM_SHIFT)
/*!< @} */

/*!< @name Config3 - Z20A8300A Config Register 3 */
/*!< @{ */

#define Z20A8300A_CONFIG3_VDS_LS_MASK                0x1fU
#define Z20A8300A_CONFIG3_VDS_LS_SHIFT               0U
#define Z20A8300A_CONFIG3_VDS_LS_WIDTH               5U
#define Z20A8300A_CONFIG3_VDS_LS_SET(x)             (((uint32_t)((uint32_t)(x)))&Z20A8300A_CONFIG3_VDS_LS_MASK)
#define Z20A8300A_CONFIG3_VDS_LS_GET(x)             ((uint32_t)(((uint32_t)(x))&Z20A8300A_CONFIG3_VDS_LS_MASK))
#define Z20A8300A_CONFIG3_EBM_MASK                0x20U
#define Z20A8300A_CONFIG3_EBM_SHIFT               5U
#define Z20A8300A_CONFIG3_EBM_WIDTH               1U
#define Z20A8300A_CONFIG3_EBM_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_CONFIG3_EBM_SHIFT))&Z20A8300A_CONFIG3_EBM_MASK)
#define Z20A8300A_CONFIG3_EBM_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_CONFIG3_EBM_MASK))>>Z20A8300A_CONFIG3_EBM_SHIFT)
#define Z20A8300A_CONFIG3_SR_MASK                0x1c0U
#define Z20A8300A_CONFIG3_SR_SHIFT               6U
#define Z20A8300A_CONFIG3_SR_WIDTH               3U
#define Z20A8300A_CONFIG3_SR_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_CONFIG3_SR_SHIFT))&Z20A8300A_CONFIG3_SR_MASK)
#define Z20A8300A_CONFIG3_SR_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_CONFIG3_SR_MASK))>>Z20A8300A_CONFIG3_SR_SHIFT)
/*!< @} */

/*!< @name Config4 - Z20A8300A Config Register 4 */
/*!< @{ */

#define Z20A8300A_CONFIG4_VDS_HS_MASK                0x1fU
#define Z20A8300A_CONFIG4_VDS_HS_SHIFT               0U
#define Z20A8300A_CONFIG4_VDS_HS_WIDTH               5U
#define Z20A8300A_CONFIG4_VDS_HS_SET(x)             (((uint32_t)((uint32_t)(x)))&Z20A8300A_CONFIG4_VDS_HS_MASK)
#define Z20A8300A_CONFIG4_VDS_HS_GET(x)             ((uint32_t)(((uint32_t)(x))&Z20A8300A_CONFIG4_VDS_HS_MASK))
#define Z20A8300A_CONFIG4_SAO_MASK                0x1e0U
#define Z20A8300A_CONFIG4_SAO_SHIFT               5U
#define Z20A8300A_CONFIG4_SAO_WIDTH               4U
#define Z20A8300A_CONFIG4_SAO_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_CONFIG4_SAO_SHIFT))&Z20A8300A_CONFIG4_SAO_MASK)
#define Z20A8300A_CONFIG4_SAO_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_CONFIG4_SAO_MASK))>>Z20A8300A_CONFIG4_SAO_SHIFT)
/*!< @} */

/*!< @name Config5 - Z20A8300A Config Register 5 */
/*!< @{ */

#define Z20A8300A_CONFIG5_SAG_MASK                0x7U
#define Z20A8300A_CONFIG5_SAG_SHIFT               0U
#define Z20A8300A_CONFIG5_SAG_WIDTH               3U
#define Z20A8300A_CONFIG5_SAG_SET(x)             (((uint32_t)((uint32_t)(x)))&Z20A8300A_CONFIG5_SAG_MASK)
#define Z20A8300A_CONFIG5_SAG_GET(x)             ((uint32_t)(((uint32_t)(x))&Z20A8300A_CONFIG5_SAG_MASK))
#define Z20A8300A_CONFIG5_SBG_MASK                0x38U
#define Z20A8300A_CONFIG5_SBG_SHIFT               3U
#define Z20A8300A_CONFIG5_SBG_WIDTH               3U
#define Z20A8300A_CONFIG5_SBG_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_CONFIG5_SBG_SHIFT))&Z20A8300A_CONFIG5_SBG_MASK)
#define Z20A8300A_CONFIG5_SBG_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_CONFIG5_SBG_MASK))>>Z20A8300A_CONFIG5_SBG_SHIFT)
#define Z20A8300A_CONFIG5_SCG_MASK                0x1c0U
#define Z20A8300A_CONFIG5_SCG_SHIFT               6U
#define Z20A8300A_CONFIG5_SCG_WIDTH               3U
#define Z20A8300A_CONFIG5_SCG_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_CONFIG5_SCG_SHIFT))&Z20A8300A_CONFIG5_SCG_MASK)
#define Z20A8300A_CONFIG5_SCG_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_CONFIG5_SCG_MASK))>>Z20A8300A_CONFIG5_SCG_SHIFT)
/*!< @} */

/*!< @name DPS0 - Z20A8300A DPS Register 0 */
/*!< @{ */

#define Z20A8300A_DPS0_FCPU_MASK                0x1U
#define Z20A8300A_DPS0_FCPU_SHIFT               0U
#define Z20A8300A_DPS0_FCPU_WIDTH               1U
#define Z20A8300A_DPS0_FCPU_SET(x)             (((uint32_t)((uint32_t)(x)))&Z20A8300A_DPS0_FCPU_MASK)
#define Z20A8300A_DPS0_FCPU_GET(x)             ((uint32_t)(((uint32_t)(x))&Z20A8300A_DPS0_FCPU_MASK))
#define Z20A8300A_DPS0_FVDO_MASK                0x2U
#define Z20A8300A_DPS0_FVDO_SHIFT               1U
#define Z20A8300A_DPS0_FVDO_WIDTH               1U
#define Z20A8300A_DPS0_FVDO_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DPS0_FVDO_SHIFT))&Z20A8300A_DPS0_FVDO_MASK)
#define Z20A8300A_DPS0_FVDO_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DPS0_FVDO_MASK))>>Z20A8300A_DPS0_FVDO_SHIFT)
#define Z20A8300A_DPS0_FSE_MASK                0x8U
#define Z20A8300A_DPS0_FSE_SHIFT               3U
#define Z20A8300A_DPS0_FSE_WIDTH               1U
#define Z20A8300A_DPS0_FSE_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DPS0_FSE_SHIFT))&Z20A8300A_DPS0_FSE_MASK)
#define Z20A8300A_DPS0_FSE_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DPS0_FSE_MASK))>>Z20A8300A_DPS0_FSE_SHIFT)
#define Z20A8300A_DPS0_FOT_MASK                0x100U
#define Z20A8300A_DPS0_FOT_SHIFT               8U
#define Z20A8300A_DPS0_FOT_WIDTH               1U
#define Z20A8300A_DPS0_FOT_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DPS0_FOT_SHIFT))&Z20A8300A_DPS0_FOT_MASK)
#define Z20A8300A_DPS0_FOT_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DPS0_FOT_MASK))>>Z20A8300A_DPS0_FOT_SHIFT)
/*!< @} */

/*!< @name DPS1 - Z20A8300A DPS Register 1 */
/*!< @{ */

#define Z20A8300A_DPS1_FVSU_MASK                0x1U
#define Z20A8300A_DPS1_FVSU_SHIFT               0U
#define Z20A8300A_DPS1_FVSU_WIDTH               1U
#define Z20A8300A_DPS1_FVSU_SET(x)             (((uint32_t)((uint32_t)(x)))&Z20A8300A_DPS1_FVSU_MASK)
#define Z20A8300A_DPS1_FVSU_GET(x)             ((uint32_t)(((uint32_t)(x))&Z20A8300A_DPS1_FVSU_MASK))
#define Z20A8300A_DPS1_FVSO_MASK                0x2U
#define Z20A8300A_DPS1_FVSO_SHIFT               1U
#define Z20A8300A_DPS1_FVSO_WIDTH               1U
#define Z20A8300A_DPS1_FVSO_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DPS1_FVSO_SHIFT))&Z20A8300A_DPS1_FVSO_MASK)
#define Z20A8300A_DPS1_FVSO_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DPS1_FVSO_MASK))>>Z20A8300A_DPS1_FVSO_SHIFT)
#define Z20A8300A_DPS1_FVRU_MASK                0x4U
#define Z20A8300A_DPS1_FVRU_SHIFT               2U
#define Z20A8300A_DPS1_FVRU_WIDTH               1U
#define Z20A8300A_DPS1_FVRU_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DPS1_FVRU_SHIFT))&Z20A8300A_DPS1_FVRU_MASK)
#define Z20A8300A_DPS1_FVRU_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DPS1_FVRU_MASK))>>Z20A8300A_DPS1_FVRU_SHIFT)
#define Z20A8300A_DPS1_FVRO_MASK                0x8U
#define Z20A8300A_DPS1_FVRO_SHIFT               3U
#define Z20A8300A_DPS1_FVRO_WIDTH               1U
#define Z20A8300A_DPS1_FVRO_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DPS1_FVRO_SHIFT))&Z20A8300A_DPS1_FVRO_MASK)
#define Z20A8300A_DPS1_FVRO_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DPS1_FVRO_MASK))>>Z20A8300A_DPS1_FVRO_SHIFT)
#define Z20A8300A_DPS1_FVBU_MASK                0x10U
#define Z20A8300A_DPS1_FVBU_SHIFT               4U
#define Z20A8300A_DPS1_FVBU_WIDTH               1U
#define Z20A8300A_DPS1_FVBU_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DPS1_FVBU_SHIFT))&Z20A8300A_DPS1_FVBU_MASK)
#define Z20A8300A_DPS1_FVBU_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DPS1_FVBU_MASK))>>Z20A8300A_DPS1_FVBU_SHIFT)
#define Z20A8300A_DPS1_FGSU_MASK                0x20U
#define Z20A8300A_DPS1_FGSU_SHIFT               5U
#define Z20A8300A_DPS1_FGSU_WIDTH               1U
#define Z20A8300A_DPS1_FGSU_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DPS1_FGSU_SHIFT))&Z20A8300A_DPS1_FGSU_MASK)
#define Z20A8300A_DPS1_FGSU_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DPS1_FGSU_MASK))>>Z20A8300A_DPS1_FGSU_SHIFT)
#define Z20A8300A_DPS1_FDSO_MASK                0x40U
#define Z20A8300A_DPS1_FDSO_SHIFT               6U
#define Z20A8300A_DPS1_FDSO_WIDTH               1U
#define Z20A8300A_DPS1_FDSO_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DPS1_FDSO_SHIFT))&Z20A8300A_DPS1_FDSO_MASK)
#define Z20A8300A_DPS1_FDSO_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DPS1_FDSO_MASK))>>Z20A8300A_DPS1_FDSO_SHIFT)
#define Z20A8300A_DPS1_FOC_MASK                0x100U
#define Z20A8300A_DPS1_FOC_SHIFT               8U
#define Z20A8300A_DPS1_FOC_WIDTH               1U
#define Z20A8300A_DPS1_FOC_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DPS1_FOC_SHIFT))&Z20A8300A_DPS1_FOC_MASK)
#define Z20A8300A_DPS1_FOC_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DPS1_FOC_MASK))>>Z20A8300A_DPS1_FOC_SHIFT)
/*!< @} */

/*!< @name Mask0 - Z20A8300A Mask Register 0 */
/*!< @{ */

#define Z20A8300A_MASK0_ALU_MASK                0x1U
#define Z20A8300A_MASK0_ALU_SHIFT               0U
#define Z20A8300A_MASK0_ALU_WIDTH               1U
#define Z20A8300A_MASK0_ALU_SET(x)             (((uint32_t)((uint32_t)(x)))&Z20A8300A_MASK0_ALU_MASK)
#define Z20A8300A_MASK0_ALU_GET(x)             ((uint32_t)(((uint32_t)(x))&Z20A8300A_MASK0_ALU_MASK))
#define Z20A8300A_MASK0_AHU_MASK                0x2U
#define Z20A8300A_MASK0_AHU_SHIFT               1U
#define Z20A8300A_MASK0_AHU_WIDTH               1U
#define Z20A8300A_MASK0_AHU_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_MASK0_AHU_SHIFT))&Z20A8300A_MASK0_AHU_MASK)
#define Z20A8300A_MASK0_AHU_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_MASK0_AHU_MASK))>>Z20A8300A_MASK0_AHU_SHIFT)
#define Z20A8300A_MASK0_BLU_MASK                0x4U
#define Z20A8300A_MASK0_BLU_SHIFT               2U
#define Z20A8300A_MASK0_BLU_WIDTH               1U
#define Z20A8300A_MASK0_BLU_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_MASK0_BLU_SHIFT))&Z20A8300A_MASK0_BLU_MASK)
#define Z20A8300A_MASK0_BLU_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_MASK0_BLU_MASK))>>Z20A8300A_MASK0_BLU_SHIFT)
#define Z20A8300A_MASK0_BHU_MASK                0x8U
#define Z20A8300A_MASK0_BHU_SHIFT               3U
#define Z20A8300A_MASK0_BHU_WIDTH               1U
#define Z20A8300A_MASK0_BHU_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_MASK0_BHU_SHIFT))&Z20A8300A_MASK0_BHU_MASK)
#define Z20A8300A_MASK0_BHU_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_MASK0_BHU_MASK))>>Z20A8300A_MASK0_BHU_SHIFT)
#define Z20A8300A_MASK0_CLU_MASK                0x10U
#define Z20A8300A_MASK0_CLU_SHIFT               4U
#define Z20A8300A_MASK0_CLU_WIDTH               1U
#define Z20A8300A_MASK0_CLU_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_MASK0_CLU_SHIFT))&Z20A8300A_MASK0_CLU_MASK)
#define Z20A8300A_MASK0_CLU_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_MASK0_CLU_MASK))>>Z20A8300A_MASK0_CLU_SHIFT)
#define Z20A8300A_MASK0_CHU_MASK                0x20U
#define Z20A8300A_MASK0_CHU_SHIFT               5U
#define Z20A8300A_MASK0_CHU_WIDTH               1U
#define Z20A8300A_MASK0_CHU_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_MASK0_CHU_SHIFT))&Z20A8300A_MASK0_CHU_MASK)
#define Z20A8300A_MASK0_CHU_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_MASK0_CHU_MASK))>>Z20A8300A_MASK0_CHU_SHIFT)
#define Z20A8300A_MASK0_BSUA_MASK                0x40U
#define Z20A8300A_MASK0_BSUA_SHIFT               6U
#define Z20A8300A_MASK0_BSUA_WIDTH               1U
#define Z20A8300A_MASK0_BSUA_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_MASK0_BSUA_SHIFT))&Z20A8300A_MASK0_BSUA_MASK)
#define Z20A8300A_MASK0_BSUA_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_MASK0_BSUA_MASK))>>Z20A8300A_MASK0_BSUA_SHIFT)
#define Z20A8300A_MASK0_BSUB_MASK                0x80U
#define Z20A8300A_MASK0_BSUB_SHIFT               7U
#define Z20A8300A_MASK0_BSUB_WIDTH               1U
#define Z20A8300A_MASK0_BSUB_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_MASK0_BSUB_SHIFT))&Z20A8300A_MASK0_BSUB_MASK)
#define Z20A8300A_MASK0_BSUB_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_MASK0_BSUB_MASK))>>Z20A8300A_MASK0_BSUB_SHIFT)
#define Z20A8300A_MASK0_BSUC_MASK                0x100U
#define Z20A8300A_MASK0_BSUC_SHIFT               8U
#define Z20A8300A_MASK0_BSUC_WIDTH               1U
#define Z20A8300A_MASK0_BSUC_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_MASK0_BSUC_SHIFT))&Z20A8300A_MASK0_BSUC_MASK)
#define Z20A8300A_MASK0_BSUC_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_MASK0_BSUC_MASK))>>Z20A8300A_MASK0_BSUC_SHIFT)
/*!< @} */

/*!< @name Mask1 - Z20A8300A Mask Register 1 */
/*!< @{ */

#define Z20A8300A_MASK1_ALO_MASK                0x1U
#define Z20A8300A_MASK1_ALO_SHIFT               0U
#define Z20A8300A_MASK1_ALO_WIDTH               1U
#define Z20A8300A_MASK1_ALO_SET(x)             (((uint32_t)((uint32_t)(x)))&Z20A8300A_MASK1_ALO_MASK)
#define Z20A8300A_MASK1_ALO_GET(x)             ((uint32_t)(((uint32_t)(x))&Z20A8300A_MASK1_ALO_MASK))
#define Z20A8300A_MASK1_AHO_MASK                0x2U
#define Z20A8300A_MASK1_AHO_SHIFT               1U
#define Z20A8300A_MASK1_AHO_WIDTH               1U
#define Z20A8300A_MASK1_AHO_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_MASK1_AHO_SHIFT))&Z20A8300A_MASK1_AHO_MASK)
#define Z20A8300A_MASK1_AHO_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_MASK1_AHO_MASK))>>Z20A8300A_MASK1_AHO_SHIFT)
#define Z20A8300A_MASK1_BLO_MASK                0x4U
#define Z20A8300A_MASK1_BLO_SHIFT               2U
#define Z20A8300A_MASK1_BLO_WIDTH               1U
#define Z20A8300A_MASK1_BLO_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_MASK1_BLO_SHIFT))&Z20A8300A_MASK1_BLO_MASK)
#define Z20A8300A_MASK1_BLO_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_MASK1_BLO_MASK))>>Z20A8300A_MASK1_BLO_SHIFT)
#define Z20A8300A_MASK1_BHO_MASK                0x8U
#define Z20A8300A_MASK1_BHO_SHIFT               3U
#define Z20A8300A_MASK1_BHO_WIDTH               1U
#define Z20A8300A_MASK1_BHO_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_MASK1_BHO_SHIFT))&Z20A8300A_MASK1_BHO_MASK)
#define Z20A8300A_MASK1_BHO_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_MASK1_BHO_MASK))>>Z20A8300A_MASK1_BHO_SHIFT)
#define Z20A8300A_MASK1_CLO_MASK                0x10U
#define Z20A8300A_MASK1_CLO_SHIFT               4U
#define Z20A8300A_MASK1_CLO_WIDTH               1U
#define Z20A8300A_MASK1_CLO_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_MASK1_CLO_SHIFT))&Z20A8300A_MASK1_CLO_MASK)
#define Z20A8300A_MASK1_CLO_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_MASK1_CLO_MASK))>>Z20A8300A_MASK1_CLO_SHIFT)
#define Z20A8300A_MASK1_CHO_MASK                0x20U
#define Z20A8300A_MASK1_CHO_SHIFT               5U
#define Z20A8300A_MASK1_CHO_WIDTH               1U
#define Z20A8300A_MASK1_CHO_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_MASK1_CHO_SHIFT))&Z20A8300A_MASK1_CHO_MASK)
#define Z20A8300A_MASK1_CHO_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_MASK1_CHO_MASK))>>Z20A8300A_MASK1_CHO_SHIFT)
#define Z20A8300A_MASK1_AOC_MASK                0x40U
#define Z20A8300A_MASK1_AOC_SHIFT               6U
#define Z20A8300A_MASK1_AOC_WIDTH               1U
#define Z20A8300A_MASK1_AOC_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_MASK1_AOC_SHIFT))&Z20A8300A_MASK1_AOC_MASK)
#define Z20A8300A_MASK1_AOC_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_MASK1_AOC_MASK))>>Z20A8300A_MASK1_AOC_SHIFT)
#define Z20A8300A_MASK1_BOC_MASK                0x80U
#define Z20A8300A_MASK1_BOC_SHIFT               7U
#define Z20A8300A_MASK1_BOC_WIDTH               1U
#define Z20A8300A_MASK1_BOC_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_MASK1_BOC_SHIFT))&Z20A8300A_MASK1_BOC_MASK)
#define Z20A8300A_MASK1_BOC_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_MASK1_BOC_MASK))>>Z20A8300A_MASK1_BOC_SHIFT)
#define Z20A8300A_MASK1_COC_MASK                0x100U
#define Z20A8300A_MASK1_COC_SHIFT               8U
#define Z20A8300A_MASK1_COC_WIDTH               1U
#define Z20A8300A_MASK1_COC_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_MASK1_COC_SHIFT))&Z20A8300A_MASK1_COC_MASK)
#define Z20A8300A_MASK1_COC_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_MASK1_COC_MASK))>>Z20A8300A_MASK1_COC_SHIFT)
/*!< @} */

/*!< @name Mask2 - Z20A8300A Mask Register 2 */
/*!< @{ */

#define Z20A8300A_MASK2_OT_MASK                0x2U
#define Z20A8300A_MASK2_OT_SHIFT               1U
#define Z20A8300A_MASK2_OT_WIDTH               1U
#define Z20A8300A_MASK2_OT_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_MASK2_OT_SHIFT))&Z20A8300A_MASK2_OT_MASK)
#define Z20A8300A_MASK2_OT_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_MASK2_OT_MASK))>>Z20A8300A_MASK2_OT_SHIFT)
#define Z20A8300A_MASK2_VDO_MASK                0x8U
#define Z20A8300A_MASK2_VDO_SHIFT               3U
#define Z20A8300A_MASK2_VDO_WIDTH               1U
#define Z20A8300A_MASK2_VDO_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_MASK2_VDO_SHIFT))&Z20A8300A_MASK2_VDO_MASK)
#define Z20A8300A_MASK2_VDO_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_MASK2_VDO_MASK))>>Z20A8300A_MASK2_VDO_SHIFT)
#define Z20A8300A_MASK2_VRU_MASK                0x10U
#define Z20A8300A_MASK2_VRU_SHIFT               4U
#define Z20A8300A_MASK2_VRU_WIDTH               1U
#define Z20A8300A_MASK2_VRU_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_MASK2_VRU_SHIFT))&Z20A8300A_MASK2_VRU_MASK)
#define Z20A8300A_MASK2_VRU_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_MASK2_VRU_MASK))>>Z20A8300A_MASK2_VRU_SHIFT)
#define Z20A8300A_MASK2_VRO_MASK                0x20U
#define Z20A8300A_MASK2_VRO_SHIFT               5U
#define Z20A8300A_MASK2_VRO_WIDTH               1U
#define Z20A8300A_MASK2_VRO_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_MASK2_VRO_SHIFT))&Z20A8300A_MASK2_VRO_MASK)
#define Z20A8300A_MASK2_VRO_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_MASK2_VRO_MASK))>>Z20A8300A_MASK2_VRO_SHIFT)
#define Z20A8300A_MASK2_VCPU_MASK                0x40U
#define Z20A8300A_MASK2_VCPU_SHIFT               6U
#define Z20A8300A_MASK2_VCPU_WIDTH               1U
#define Z20A8300A_MASK2_VCPU_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_MASK2_VCPU_SHIFT))&Z20A8300A_MASK2_VCPU_MASK)
#define Z20A8300A_MASK2_VCPU_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_MASK2_VCPU_MASK))>>Z20A8300A_MASK2_VCPU_SHIFT)
#define Z20A8300A_MASK2_VSU_MASK                0x80U
#define Z20A8300A_MASK2_VSU_SHIFT               7U
#define Z20A8300A_MASK2_VSU_WIDTH               1U
#define Z20A8300A_MASK2_VSU_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_MASK2_VSU_SHIFT))&Z20A8300A_MASK2_VSU_MASK)
#define Z20A8300A_MASK2_VSU_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_MASK2_VSU_MASK))>>Z20A8300A_MASK2_VSU_SHIFT)
#define Z20A8300A_MASK2_VSO_MASK                0x100U
#define Z20A8300A_MASK2_VSO_SHIFT               8U
#define Z20A8300A_MASK2_VSO_WIDTH               1U
#define Z20A8300A_MASK2_VSO_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_MASK2_VSO_SHIFT))&Z20A8300A_MASK2_VSO_MASK)
#define Z20A8300A_MASK2_VSO_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_MASK2_VSO_MASK))>>Z20A8300A_MASK2_VSO_SHIFT)
/*!< @} */

/*!< @name Daig0 - Z20A8300A Diag Register 0 */
/*!< @{ */

#define Z20A8300A_DIAG0_ALU_MASK                0x1U
#define Z20A8300A_DIAG0_ALU_SHIFT               0U
#define Z20A8300A_DIAG0_ALU_WIDTH               1U
#define Z20A8300A_DIAG0_ALU_SET(x)             (((uint32_t)((uint32_t)(x)))&Z20A8300A_DIAG0_ALU_MASK)
#define Z20A8300A_DIAG0_ALU_GET(x)             ((uint32_t)(((uint32_t)(x))&Z20A8300A_DIAG0_ALU_MASK))
#define Z20A8300A_DIAG0_AHU_MASK                0x2U
#define Z20A8300A_DIAG0_AHU_SHIFT               1U
#define Z20A8300A_DIAG0_AHU_WIDTH               1U
#define Z20A8300A_DIAG0_AHU_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DIAG0_AHU_SHIFT))&Z20A8300A_DIAG0_AHU_MASK)
#define Z20A8300A_DIAG0_AHU_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DIAG0_AHU_MASK))>>Z20A8300A_DIAG0_AHU_SHIFT)
#define Z20A8300A_DIAG0_BLU_MASK                0x4U
#define Z20A8300A_DIAG0_BLU_SHIFT               2U
#define Z20A8300A_DIAG0_BLU_WIDTH               1U
#define Z20A8300A_DIAG0_BLU_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DIAG0_BLU_SHIFT))&Z20A8300A_DIAG0_BLU_MASK)
#define Z20A8300A_DIAG0_BLU_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DIAG0_BLU_MASK))>>Z20A8300A_DIAG0_BLU_SHIFT)
#define Z20A8300A_DIAG0_BHU_MASK                0x8U
#define Z20A8300A_DIAG0_BHU_SHIFT               3U
#define Z20A8300A_DIAG0_BHU_WIDTH               1U
#define Z20A8300A_DIAG0_BHU_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DIAG0_BHU_SHIFT))&Z20A8300A_DIAG0_BHU_MASK)
#define Z20A8300A_DIAG0_BHU_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DIAG0_BHU_MASK))>>Z20A8300A_DIAG0_BHU_SHIFT)
#define Z20A8300A_DIAG0_CLU_MASK                0x10U
#define Z20A8300A_DIAG0_CLU_SHIFT               4U
#define Z20A8300A_DIAG0_CLU_WIDTH               1U
#define Z20A8300A_DIAG0_CLU_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DIAG0_CLU_SHIFT))&Z20A8300A_DIAG0_CLU_MASK)
#define Z20A8300A_DIAG0_CLU_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DIAG0_CLU_MASK))>>Z20A8300A_DIAG0_CLU_SHIFT)
#define Z20A8300A_DIAG0_CHU_MASK                0x20U
#define Z20A8300A_DIAG0_CHU_SHIFT               5U
#define Z20A8300A_DIAG0_CHU_WIDTH               1U
#define Z20A8300A_DIAG0_CHU_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DIAG0_CHU_SHIFT))&Z20A8300A_DIAG0_CHU_MASK)
#define Z20A8300A_DIAG0_CHU_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DIAG0_CHU_MASK))>>Z20A8300A_DIAG0_CHU_SHIFT)
#define Z20A8300A_DIAG0_BSUA_MASK                0x40U
#define Z20A8300A_DIAG0_BSUA_SHIFT               6U
#define Z20A8300A_DIAG0_BSUA_WIDTH               1U
#define Z20A8300A_DIAG0_BSUA_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DIAG0_BSUA_SHIFT))&Z20A8300A_DIAG0_BSUA_MASK)
#define Z20A8300A_DIAG0_BSUA_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DIAG0_BSUA_MASK))>>Z20A8300A_DIAG0_BSUA_SHIFT)
#define Z20A8300A_DIAG0_BSUB_MASK                0x80U
#define Z20A8300A_DIAG0_BSUB_SHIFT               7U
#define Z20A8300A_DIAG0_BSUB_WIDTH               1U
#define Z20A8300A_DIAG0_BSUB_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DIAG0_BSUB_SHIFT))&Z20A8300A_DIAG0_BSUB_MASK)
#define Z20A8300A_DIAG0_BSUB_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DIAG0_BSUB_MASK))>>Z20A8300A_DIAG0_BSUB_SHIFT)
#define Z20A8300A_DIAG0_BSUC_MASK                0x100U
#define Z20A8300A_DIAG0_BSUC_SHIFT               8U
#define Z20A8300A_DIAG0_BSUC_WIDTH               1U
#define Z20A8300A_DIAG0_BSUC_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DIAG0_BSUC_SHIFT))&Z20A8300A_DIAG0_BSUC_MASK)
#define Z20A8300A_DIAG0_BSUC_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DIAG0_BSUC_MASK))>>Z20A8300A_DIAG0_BSUC_SHIFT)
/*!< @} */

/*!< @name Daig1 - Z20A8300A Diag Register 1 */
/*!< @{ */

#define Z20A8300A_DIAG1_ALO_MASK                0x1U
#define Z20A8300A_DIAG1_ALO_SHIFT               0U
#define Z20A8300A_DIAG1_ALO_WIDTH               1U
#define Z20A8300A_DIAG1_ALO_SET(x)             (((uint32_t)((uint32_t)(x)))&Z20A8300A_DIAG1_ALO_MASK)
#define Z20A8300A_DIAG1_ALO_GET(x)             ((uint32_t)(((uint32_t)(x))&Z20A8300A_DIAG1_ALO_MASK))
#define Z20A8300A_DIAG1_AHO_MASK                0x2U
#define Z20A8300A_DIAG1_AHO_SHIFT               1U
#define Z20A8300A_DIAG1_AHO_WIDTH               1U
#define Z20A8300A_DIAG1_AHO_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DIAG1_AHO_SHIFT))&Z20A8300A_DIAG1_AHO_MASK)
#define Z20A8300A_DIAG1_AHO_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DIAG1_AHO_MASK))>>Z20A8300A_DIAG1_AHO_SHIFT)
#define Z20A8300A_DIAG1_BLO_MASK                0x4U
#define Z20A8300A_DIAG1_BLO_SHIFT               2U
#define Z20A8300A_DIAG1_BLO_WIDTH               1U
#define Z20A8300A_DIAG1_BLO_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DIAG1_BLO_SHIFT))&Z20A8300A_DIAG1_BLO_MASK)
#define Z20A8300A_DIAG1_BLO_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DIAG1_BLO_MASK))>>Z20A8300A_DIAG1_BLO_SHIFT)
#define Z20A8300A_DIAG1_BHO_MASK                0x8U
#define Z20A8300A_DIAG1_BHO_SHIFT               3U
#define Z20A8300A_DIAG1_BHO_WIDTH               1U
#define Z20A8300A_DIAG1_BHO_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DIAG1_BHO_SHIFT))&Z20A8300A_DIAG1_BHO_MASK)
#define Z20A8300A_DIAG1_BHO_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DIAG1_BHO_MASK))>>Z20A8300A_DIAG1_BHO_SHIFT)
#define Z20A8300A_DIAG1_CLO_MASK                0x10U
#define Z20A8300A_DIAG1_CLO_SHIFT               4U
#define Z20A8300A_DIAG1_CLO_WIDTH               1U
#define Z20A8300A_DIAG1_CLO_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DIAG1_CLO_SHIFT))&Z20A8300A_DIAG1_CLO_MASK)
#define Z20A8300A_DIAG1_CLO_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DIAG1_CLO_MASK))>>Z20A8300A_DIAG1_CLO_SHIFT)
#define Z20A8300A_DIAG1_CHO_MASK                0x20U
#define Z20A8300A_DIAG1_CHO_SHIFT               5U
#define Z20A8300A_DIAG1_CHO_WIDTH               1U
#define Z20A8300A_DIAG1_CHO_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DIAG1_CHO_SHIFT))&Z20A8300A_DIAG1_CHO_MASK)
#define Z20A8300A_DIAG1_CHO_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DIAG1_CHO_MASK))>>Z20A8300A_DIAG1_CHO_SHIFT)
#define Z20A8300A_DIAG1_AOC_MASK                0x40U
#define Z20A8300A_DIAG1_AOC_SHIFT               6U
#define Z20A8300A_DIAG1_AOC_WIDTH               1U
#define Z20A8300A_DIAG1_AOC_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DIAG1_AOC_SHIFT))&Z20A8300A_DIAG1_AOC_MASK)
#define Z20A8300A_DIAG1_AOC_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DIAG1_AOC_MASK))>>Z20A8300A_DIAG1_AOC_SHIFT)
#define Z20A8300A_DIAG1_BOC_MASK                0x80U
#define Z20A8300A_DIAG1_BOC_SHIFT               7U
#define Z20A8300A_DIAG1_BOC_WIDTH               1U
#define Z20A8300A_DIAG1_BOC_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DIAG1_BOC_SHIFT))&Z20A8300A_DIAG1_BOC_MASK)
#define Z20A8300A_DIAG1_BOC_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DIAG1_BOC_MASK))>>Z20A8300A_DIAG1_BOC_SHIFT)
#define Z20A8300A_DIAG1_COC_MASK                0x100U
#define Z20A8300A_DIAG1_COC_SHIFT               8U
#define Z20A8300A_DIAG1_COC_WIDTH               1U
#define Z20A8300A_DIAG1_COC_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DIAG1_COC_SHIFT))&Z20A8300A_DIAG1_COC_MASK)
#define Z20A8300A_DIAG1_COC_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DIAG1_COC_MASK))>>Z20A8300A_DIAG1_COC_SHIFT)
/*!< @} */

/*!< @name Daig2 - Z20A8300A Diag Register 2 */
/*!< @{ */

#define Z20A8300A_DIAG2_VDU_MASK                0x4U
#define Z20A8300A_DIAG2_VDU_SHIFT               2U
#define Z20A8300A_DIAG2_VDU_WIDTH               1U
#define Z20A8300A_DIAG2_VDU_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DIAG2_VDU_SHIFT))&Z20A8300A_DIAG2_VDU_MASK)
#define Z20A8300A_DIAG2_VDU_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DIAG2_VDU_MASK))>>Z20A8300A_DIAG2_VDU_SHIFT)
#define Z20A8300A_DIAG2_VDO_MASK                0x8U
#define Z20A8300A_DIAG2_VDO_SHIFT               3U
#define Z20A8300A_DIAG2_VDO_WIDTH               1U
#define Z20A8300A_DIAG2_VDO_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DIAG2_VDO_SHIFT))&Z20A8300A_DIAG2_VDO_MASK)
#define Z20A8300A_DIAG2_VDO_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DIAG2_VDO_MASK))>>Z20A8300A_DIAG2_VDO_SHIFT)
#define Z20A8300A_DIAG2_VRU_MASK                0x10U
#define Z20A8300A_DIAG2_VRU_SHIFT               4U
#define Z20A8300A_DIAG2_VRU_WIDTH               1U
#define Z20A8300A_DIAG2_VRU_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DIAG2_VRU_SHIFT))&Z20A8300A_DIAG2_VRU_MASK)
#define Z20A8300A_DIAG2_VRU_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DIAG2_VRU_MASK))>>Z20A8300A_DIAG2_VRU_SHIFT)
#define Z20A8300A_DIAG2_VRO_MASK                0x20U
#define Z20A8300A_DIAG2_VRO_SHIFT               5U
#define Z20A8300A_DIAG2_VRO_WIDTH               1U
#define Z20A8300A_DIAG2_VRO_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DIAG2_VRO_SHIFT))&Z20A8300A_DIAG2_VRO_MASK)
#define Z20A8300A_DIAG2_VRO_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DIAG2_VRO_MASK))>>Z20A8300A_DIAG2_VRO_SHIFT)
#define Z20A8300A_DIAG2_VCPU_MASK                0x40U
#define Z20A8300A_DIAG2_VCPU_SHIFT               6U
#define Z20A8300A_DIAG2_VCPU_WIDTH               1U
#define Z20A8300A_DIAG2_VCPU_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DIAG2_VCPU_SHIFT))&Z20A8300A_DIAG2_VCPU_MASK)
#define Z20A8300A_DIAG2_VCPU_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DIAG2_VCPU_MASK))>>Z20A8300A_DIAG2_VCPU_SHIFT)
#define Z20A8300A_DIAG2_VSU_MASK                0x80U
#define Z20A8300A_DIAG2_VSU_SHIFT               7U
#define Z20A8300A_DIAG2_VSU_WIDTH               1U
#define Z20A8300A_DIAG2_VSU_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DIAG2_VSU_SHIFT))&Z20A8300A_DIAG2_VSU_MASK)
#define Z20A8300A_DIAG2_VSU_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DIAG2_VSU_MASK))>>Z20A8300A_DIAG2_VSU_SHIFT)
#define Z20A8300A_DIAG2_VSO_MASK                0x100U
#define Z20A8300A_DIAG2_VSO_SHIFT               8U
#define Z20A8300A_DIAG2_VSO_WIDTH               1U
#define Z20A8300A_DIAG2_VSO_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_DIAG2_VSO_SHIFT))&Z20A8300A_DIAG2_VSO_MASK)
#define Z20A8300A_DIAG2_VSO_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_DIAG2_VSO_MASK))>>Z20A8300A_DIAG2_VSO_SHIFT)
/*!< @} */

/*!< @name Control - Z20A8300A Control Register */
/*!< @{ */

#define Z20A8300A_CONTROL_AL_MASK                0x1U
#define Z20A8300A_CONTROL_AL_SHIFT               0U
#define Z20A8300A_CONTROL_AL_WIDTH               1U
#define Z20A8300A_CONTROL_AL_SET(x)             (((uint32_t)((uint32_t)(x)))&Z20A8300A_CONTROL_AL_MASK)
#define Z20A8300A_CONTROL_AL_GET(x)             ((uint32_t)(((uint32_t)(x))&Z20A8300A_CONTROL_AL_MASK))
#define Z20A8300A_CONTROL_AH_MASK                0x2U
#define Z20A8300A_CONTROL_AH_SHIFT               1U
#define Z20A8300A_CONTROL_AH_WIDTH               1U
#define Z20A8300A_CONTROL_AH_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_CONTROL_AH_SHIFT))&Z20A8300A_CONTROL_AH_MASK)
#define Z20A8300A_CONTROL_AH_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_CONTROL_AH_MASK))>>Z20A8300A_CONTROL_AH_SHIFT)
#define Z20A8300A_CONTROL_BL_MASK                0x4U
#define Z20A8300A_CONTROL_BL_SHIFT               2U
#define Z20A8300A_CONTROL_BL_WIDTH               1U
#define Z20A8300A_CONTROL_BL_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_CONTROL_BL_SHIFT))&Z20A8300A_CONTROL_BL_MASK)
#define Z20A8300A_CONTROL_BL_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_CONTROL_BL_MASK))>>Z20A8300A_CONTROL_BL_SHIFT)
#define Z20A8300A_CONTROL_BH_MASK                0x8U
#define Z20A8300A_CONTROL_BH_SHIFT               3U
#define Z20A8300A_CONTROL_BH_WIDTH               1U
#define Z20A8300A_CONTROL_BH_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_CONTROL_BH_SHIFT))&Z20A8300A_CONTROL_BH_MASK)
#define Z20A8300A_CONTROL_BH_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_CONTROL_BH_MASK))>>Z20A8300A_CONTROL_BH_SHIFT)
#define Z20A8300A_CONTROL_CL_MASK                0x10U
#define Z20A8300A_CONTROL_CL_SHIFT               4U
#define Z20A8300A_CONTROL_CL_WIDTH               1U
#define Z20A8300A_CONTROL_CL_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_CONTROL_CL_SHIFT))&Z20A8300A_CONTROL_CL_MASK)
#define Z20A8300A_CONTROL_CL_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_CONTROL_CL_MASK))>>Z20A8300A_CONTROL_CL_SHIFT)
#define Z20A8300A_CONTROL_CH_MASK                0x20U
#define Z20A8300A_CONTROL_CH_SHIFT               5U
#define Z20A8300A_CONTROL_CH_WIDTH               1U
#define Z20A8300A_CONTROL_CH_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_CONTROL_CH_SHIFT))&Z20A8300A_CONTROL_CH_MASK)
#define Z20A8300A_CONTROL_CH_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_CONTROL_CH_MASK))>>Z20A8300A_CONTROL_CH_SHIFT)
#define Z20A8300A_CONTROL_DG_MASK                0x180U
#define Z20A8300A_CONTROL_DG_SHIFT               7U
#define Z20A8300A_CONTROL_DG_WIDTH               2U
#define Z20A8300A_CONTROL_DG_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_CONTROL_DG_SHIFT))&Z20A8300A_CONTROL_DG_MASK)
#define Z20A8300A_CONTROL_DG_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_CONTROL_DG_MASK))>>Z20A8300A_CONTROL_DG_SHIFT)
/*!< @} */

/*!< @name Status - Z20A8300A Status Register */
/*!< @{ */

#define Z20A8300A_STATUS_DSO_MASK                0x2U
#define Z20A8300A_STATUS_DSO_SHIFT               1U
#define Z20A8300A_STATUS_DSO_WIDTH               1U
#define Z20A8300A_STATUS_DSO_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_STATUS_DSO_SHIFT))&Z20A8300A_STATUS_DSO_MASK)
#define Z20A8300A_STATUS_DSO_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_STATUS_DSO_MASK))>>Z20A8300A_STATUS_DSO_SHIFT)
#define Z20A8300A_STATUS_GSU_MASK                0x4U
#define Z20A8300A_STATUS_GSU_SHIFT               2U
#define Z20A8300A_STATUS_GSU_WIDTH               1U
#define Z20A8300A_STATUS_GSU_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_STATUS_GSU_SHIFT))&Z20A8300A_STATUS_GSU_MASK)
#define Z20A8300A_STATUS_GSU_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_STATUS_GSU_MASK))>>Z20A8300A_STATUS_GSU_SHIFT)
#define Z20A8300A_STATUS_BSU_MASK                0x8U
#define Z20A8300A_STATUS_BSU_SHIFT               3U
#define Z20A8300A_STATUS_BSU_WIDTH               1U
#define Z20A8300A_STATUS_BSU_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_STATUS_BSU_SHIFT))&Z20A8300A_STATUS_BSU_MASK)
#define Z20A8300A_STATUS_BSU_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_STATUS_BSU_MASK))>>Z20A8300A_STATUS_BSU_SHIFT)
#define Z20A8300A_STATUS_OC_MASK                0x10U
#define Z20A8300A_STATUS_OC_SHIFT               4U
#define Z20A8300A_STATUS_OC_WIDTH               1U
#define Z20A8300A_STATUS_OC_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_STATUS_OC_SHIFT))&Z20A8300A_STATUS_OC_MASK)
#define Z20A8300A_STATUS_OC_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_STATUS_OC_MASK))>>Z20A8300A_STATUS_OC_SHIFT)
#define Z20A8300A_STATUS_VD_MASK                0x20U
#define Z20A8300A_STATUS_VD_SHIFT               5U
#define Z20A8300A_STATUS_VD_WIDTH               1U
#define Z20A8300A_STATUS_VD_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_STATUS_VD_SHIFT))&Z20A8300A_STATUS_VD_MASK)
#define Z20A8300A_STATUS_VD_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_STATUS_VD_MASK))>>Z20A8300A_STATUS_VD_SHIFT)
#define Z20A8300A_STATUS_VR_MASK                0x40U
#define Z20A8300A_STATUS_VR_SHIFT               6U
#define Z20A8300A_STATUS_VR_WIDTH               1U
#define Z20A8300A_STATUS_VR_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_STATUS_VR_SHIFT))&Z20A8300A_STATUS_VR_MASK)
#define Z20A8300A_STATUS_VR_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_STATUS_VR_MASK))>>Z20A8300A_STATUS_VR_SHIFT)
#define Z20A8300A_STATUS_VS_MASK                0x200U
#define Z20A8300A_STATUS_VS_SHIFT               9U
#define Z20A8300A_STATUS_VS_WIDTH               1U
#define Z20A8300A_STATUS_VS_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_STATUS_VS_SHIFT))&Z20A8300A_STATUS_VS_MASK)
#define Z20A8300A_STATUS_VS_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_STATUS_VS_MASK))>>Z20A8300A_STATUS_VS_SHIFT)
#define Z20A8300A_STATUS_OT_MASK                0x800U
#define Z20A8300A_STATUS_OT_SHIFT               11U
#define Z20A8300A_STATUS_OT_WIDTH               1U
#define Z20A8300A_STATUS_OT_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_STATUS_OT_SHIFT))&Z20A8300A_STATUS_OT_MASK)
#define Z20A8300A_STATUS_OT_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_STATUS_OT_MASK))>>Z20A8300A_STATUS_OT_SHIFT)
#define Z20A8300A_STATUS_NVM_MASK                0x1000U
#define Z20A8300A_STATUS_NVM_SHIFT               12U
#define Z20A8300A_STATUS_NVM_WIDTH               1U
#define Z20A8300A_STATUS_NVM_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_STATUS_NVM_SHIFT))&Z20A8300A_STATUS_NVM_MASK)
#define Z20A8300A_STATUS_NVM_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_STATUS_NVM_MASK))>>Z20A8300A_STATUS_NVM_SHIFT)
#define Z20A8300A_STATUS_SE_MASK                0x2000U
#define Z20A8300A_STATUS_SE_SHIFT               13U
#define Z20A8300A_STATUS_SE_WIDTH               1U
#define Z20A8300A_STATUS_SE_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_STATUS_SE_SHIFT))&Z20A8300A_STATUS_SE_MASK)
#define Z20A8300A_STATUS_SE_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_STATUS_SE_MASK))>>Z20A8300A_STATUS_SE_SHIFT)
#define Z20A8300A_STATUS_POR_MASK                0x4000U
#define Z20A8300A_STATUS_POR_SHIFT               14U
#define Z20A8300A_STATUS_POR_WIDTH               1U
#define Z20A8300A_STATUS_POR_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_STATUS_POR_SHIFT))&Z20A8300A_STATUS_POR_MASK)
#define Z20A8300A_STATUS_POR_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_STATUS_POR_MASK))>>Z20A8300A_STATUS_POR_SHIFT)
#define Z20A8300A_STATUS_FF_MASK                0x8000U
#define Z20A8300A_STATUS_FF_SHIFT               15U
#define Z20A8300A_STATUS_FF_WIDTH               1U
#define Z20A8300A_STATUS_FF_SET(x)             (((uint32_t)(((uint32_t)(x))<<Z20A8300A_STATUS_FF_SHIFT))&Z20A8300A_STATUS_FF_MASK)
#define Z20A8300A_STATUS_FF_GET(x)             (((uint32_t)(((uint32_t)(x))&Z20A8300A_STATUS_FF_MASK))>>Z20A8300A_STATUS_FF_SHIFT)
/*!< @} */

/** @} end of Reg_Public_MacroDefinition */

/** @defgroup Reg_Public_TypeDefinition
 *  @{
 */

/**  
 *  @brief Z20A8300A Config0 register type definition
 */
typedef union
{
    uint32_t DB;
    struct {
           uint32_t DT                      : 6;  /* [5:0]          r/w        */
           uint32_t OTS                     : 2;  /* [7:6]          r/w        */
           uint32_t VBOV                    : 1;  /* [8]            r/w        */
           uint32_t RSVD_31_9               :23;  /* [31:9]         ro         */
    } BITS;
} Z20A8300A_Config0RegType;

/**
 *  @brief Z20A8300A Config1 register type definition
 */
typedef union
{
    uint32_t DB;
    struct {
           uint32_t TCB                     : 5;  /* [4:0]          r/w        */
           uint32_t OCT                     : 4;  /* [8:5]          r/w        */
           uint32_t RSVD_31_9               :23;  /* [31:9]         ro         */
    } BITS;
} Z20A8300A_Config1RegType;

/**
 *  @brief Z20A8300A Config2 register type definition
 */
typedef union
{
    uint32_t DB;
    struct {
           uint32_t TVB                     : 6;  /* [5:0]          r/w        */
           uint32_t FCP                     : 2;  /* [7:6]          r/w        */
           uint32_t CPM                     : 1;  /* [8]            r/w        */
           uint32_t RSVD_31_9               :23;  /* [31:9]         ro         */
    } BITS;
} Z20A8300A_Config2RegType;

/**
 *  @brief Z20A8300A Config3 register type definition
 */
typedef union
{
    uint32_t DB;
    struct {
           uint32_t VDS_LS                  : 5;  /* [4:0]          r/w        */
           uint32_t EBM                     : 1;  /* [5]            r/w        */
           uint32_t SR                      : 3;  /* [8:6]          r/w        */
           uint32_t RSVD_31_9               :23;  /* [31:9]         ro         */
    } BITS;
} Z20A8300A_Config3RegType;

/**
 *  @brief Z20A8300A Config4 register type definition
 */
typedef union
{
    uint32_t DB;
    struct {
           uint32_t VDS_HS                  : 5;  /* [4:0]          r/w        */
           uint32_t SAO                     : 4;  /* [8:5]          r/w        */
           uint32_t RSVD_31_9               :23;  /* [31:9]         ro         */
    } BITS;
} Z20A8300A_Config4RegType;

/**
 *  @brief Z20A8300A Config5 register type definition
 */
typedef union
{
    uint32_t DB;
    struct {
           uint32_t SAG                     : 3;  /* [2:0]          r/w        */
           uint32_t SBG                     : 3;  /* [5:3]          r/w        */
           uint32_t SCG                     : 3;  /* [8:6]          r/w        */
           uint32_t RSVD_31_9               :23;  /* [31:9]         ro         */
    } BITS;
} Z20A8300A_Config5RegType;

/**
 *  @brief Z20A8300A DPS0 register type definition
 */
typedef union
{
    uint32_t DB;
    struct {
           uint32_t FCPU                    : 1;  /* [0]            r/w        */
           uint32_t FVDO                    : 1;  /* [1]            r/w        */
           uint32_t RSVD_2                  : 1;  /* [2]            ro         */
           uint32_t FSE                     : 1;  /* [3]            r/w        */
           uint32_t RSVD_7_4                : 4;  /* [7:4]          ro         */
           uint32_t FOT                     : 1;  /* [8]            r/w        */
           uint32_t RSVD_31_9               :23;  /* [31:9]         ro         */
    } BITS;
} Z20A8300A_Dps0RegType;

/**
 *  @brief Z20A8300A DPS1 register type definition
 */
typedef union
{
    uint32_t DB;
    struct {
           uint32_t FVSU                    : 1;  /* [0]            r/w        */
           uint32_t FVSO                    : 1;  /* [1]            r/w        */
           uint32_t FVRU                    : 1;  /* [2]            r/w        */
           uint32_t FVRO                    : 1;  /* [3]            r/w        */
           uint32_t FVBU                    : 1;  /* [4]            r/w        */
           uint32_t FGSU                    : 1;  /* [5]            r/w        */
           uint32_t FDSO                    : 1;  /* [6]            r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t FOC                     : 1;  /* [8]            r/w        */
           uint32_t RSVD_31_9               :23;  /* [31:9]         ro         */
    } BITS;
} Z20A8300A_Dps1RegType;

/**
 *  @brief Z20A8300A Mask0 register type definition
 */
typedef union
{
    uint32_t DB;
    struct {
           uint32_t ALU                     : 1;  /* [0]            r/w        */
           uint32_t AHU                     : 1;  /* [1]            r/w        */
           uint32_t BLU                     : 1;  /* [2]            r/w        */
           uint32_t BHU                     : 1;  /* [3]            r/w        */
           uint32_t CLU                     : 1;  /* [4]            r/w        */
           uint32_t CHU                     : 1;  /* [5]            r/w        */
           uint32_t BSUA                    : 1;  /* [6]            r/w        */
           uint32_t BSUB                    : 1;  /* [7]            r/w        */
           uint32_t BSUC                    : 1;  /* [8]            r/w        */
           uint32_t RSVD_31_9               :23;  /* [31:9]         ro         */
    } BITS;
} Z20A8300A_Mask0RegType;

/**
 *  @brief Z20A8300A Mask1 register type definition
 */
typedef union
{
    uint32_t DB;
    struct {
           uint32_t ALO                     : 1;  /* [0]            r/w        */
           uint32_t AHO                     : 1;  /* [1]            r/w        */
           uint32_t BLO                     : 1;  /* [2]            r/w        */
           uint32_t BHO                     : 1;  /* [3]            r/w        */
           uint32_t CLO                     : 1;  /* [4]            r/w        */
           uint32_t CHO                     : 1;  /* [5]            r/w        */
           uint32_t AOC                     : 1;  /* [6]            r/w        */
           uint32_t BOC                     : 1;  /* [7]            r/w        */
           uint32_t COC                     : 1;  /* [8]            r/w        */
           uint32_t RSVD_31_9               :23;  /* [31:9]         ro         */
    } BITS;
} Z20A8300A_Mask1RegType;

/**
 *  @brief Z20A8300A Mask2 register type definition
 */
typedef union
{
    uint32_t DB;
    struct {
           uint32_t RSVD_0                  : 1;  /* [0]            r/w        */
           uint32_t OT                      : 1;  /* [1]            r/w        */
           uint32_t RSVD_2                  : 1;  /* [2]            r/w        */
           uint32_t VDO                     : 1;  /* [3]            r/w        */
           uint32_t VRU                     : 1;  /* [4]            r/w        */
           uint32_t VRO                     : 1;  /* [5]            r/w        */
           uint32_t VCPU                    : 1;  /* [6]            r/w        */
           uint32_t VSU                     : 1;  /* [7]            r/w        */
           uint32_t VSO                     : 1;  /* [8]            r/w        */
           uint32_t RSVD_31_9               :23;  /* [31:9]         ro         */
    } BITS;
} Z20A8300A_Mask2RegType;

/**
 *  @brief Z20A8300A Diag0 register type definition
 */
typedef union
{
    uint32_t DB;
    struct {
           uint32_t ALU                     : 1;  /* [0]            ro         */
           uint32_t AHU                     : 1;  /* [1]            ro         */
           uint32_t BLU                     : 1;  /* [2]            ro         */
           uint32_t BHU                     : 1;  /* [3]            ro         */
           uint32_t CLU                     : 1;  /* [4]            ro         */
           uint32_t CHU                     : 1;  /* [5]            ro         */
           uint32_t BSUA                    : 1;  /* [6]            ro         */
           uint32_t BSUB                    : 1;  /* [7]            ro         */
           uint32_t BSUC                    : 1;  /* [8]            ro         */
           uint32_t RSVD_31_9               :23;  /* [31:9]         ro         */
    } BITS;
} Z20A8300A_Diag0RegType;

/**
 *  @brief Z20A8300A Diag1 register type definition
 */
typedef union
{
    uint32_t DB;
    struct {
           uint32_t ALO                     : 1;  /* [0]            ro         */
           uint32_t AHO                     : 1;  /* [1]            ro         */
           uint32_t BLO                     : 1;  /* [2]            ro         */
           uint32_t BHO                     : 1;  /* [3]            ro         */
           uint32_t CLO                     : 1;  /* [4]            ro         */
           uint32_t CHO                     : 1;  /* [5]            ro         */
           uint32_t AOC                     : 1;  /* [6]            ro         */
           uint32_t BOC                     : 1;  /* [7]            ro         */
           uint32_t COC                     : 1;  /* [8]            ro         */
           uint32_t RSVD_31_9               :23;  /* [31:9]         ro         */
    } BITS;
} Z20A8300A_Diag1RegType;

/**
 *  @brief Z20A8300A Diag2 register type definition
 */
typedef union
{
    uint32_t DB;
    struct {
           uint32_t RSVD_0                  : 1;  /* [0]            ro         */
           uint32_t RSVD_1                  : 1;  /* [1]            ro         */
           uint32_t VDU                     : 1;  /* [2]            ro         */
           uint32_t VDO                     : 1;  /* [3]            ro         */
           uint32_t VRU                     : 1;  /* [4]            ro         */
           uint32_t VRO                     : 1;  /* [5]            ro         */
           uint32_t VCPU                    : 1;  /* [6]            ro         */
           uint32_t VSU                     : 1;  /* [7]            ro         */
           uint32_t VSO                     : 1;  /* [8]            ro         */
           uint32_t RSVD_31_9               :23;  /* [31:9]         ro         */
    } BITS;
} Z20A8300A_Diag2RegType;

/**
 *  @brief Z20A8300A Control register type definition
 */
typedef union
{
    uint32_t DB;
    struct {
           uint32_t AL                      : 1;  /* [0]            r/w        */
           uint32_t AH                      : 1;  /* [1]            r/w        */
           uint32_t BL                      : 1;  /* [2]            r/w        */
           uint32_t BH                      : 1;  /* [3]            r/w        */
           uint32_t CL                      : 1;  /* [4]            r/w        */
           uint32_t CH                      : 1;  /* [5]            r/w        */
           uint32_t RSVD_6                  : 1;  /* [6]            ro         */
           uint32_t DG                      : 2;  /* [8:7]          r/w        */
           uint32_t RSVD_31_9               :23;  /* [31:9]         ro         */
    } BITS;
} Z20A8300A_ControlRegType;

/**
 *  @brief Z20A8300A Status register type definition
 */
typedef union
{
    uint32_t DB;
    struct {
           uint32_t PARITY                  : 1;  /* [0]            ro         */
           uint32_t DSO                     : 1;  /* [1]            ro         */
           uint32_t GSU                     : 1;  /* [2]            ro         */
           uint32_t BSU                     : 1;  /* [3]            ro         */
           uint32_t OC                      : 1;  /* [4]            ro         */
           uint32_t VD                      : 1;  /* [5]            ro         */
           uint32_t VR                      : 1;  /* [6]            ro         */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t RSVD_8                  : 1;  /* [8]            ro         */
           uint32_t VS                      : 1;  /* [9]            ro         */
           uint32_t RSVD_10                 : 1;  /* [10]           ro         */
           uint32_t OT                      : 1;  /* [11]           ro         */
           uint32_t NVM                     : 1;  /* [12]           ro         */
           uint32_t SE                      : 1;  /* [13]           ro         */
           uint32_t POR                     : 1;  /* [14]           ro         */
           uint32_t FF                      : 1;  /* [15]           ro         */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } BITS;
} Z20A8300A_StatusRegType;


/** @} end of group Reg_Public_TypeDefinition */

/** @defgroup Reg_Global_VariableDeclaration
 *  @{
 */

/** @} end of group Reg_Global_VariableDeclaration */

/** @defgroup Reg_Public_FunctionDeclaration
 *  @{
 */

/** @} end of group Reg_Public_FunctionDeclaration */

#ifdef __cplusplus
}
#endif

/** @} end of group Z20A8300A_Reg */

/** @} end of group Z20A8300A_Driver */

#endif /* Z20A8300A_REG_H */
