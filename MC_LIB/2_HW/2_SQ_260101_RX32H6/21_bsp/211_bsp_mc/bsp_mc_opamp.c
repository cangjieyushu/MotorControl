/**
 * @file    bsp_mc_opamp.c
 * @brief   OPA 跟随器 / PGA 初始化
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "bsp_mc_opamp.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  OPA 初始化（PGA 模式，输出送 CMP 的 P 端）
 */
void BSP_MC_OPAMP_Init(void)
{
    OPAMP_InitTypeDef OPAMP_InitStruct = {0};

    OPAMP_InitStruct.PGAGain          = OPAMP_GAIN_8;
    OPAMP_InitStruct.FunctionalMode   = OPAMP_MODE_PGA;
    OPAMP_InitStruct.OPAMP_OUTCONNECT = OPAMP_VM_TO_VIN1;
    OPAMP_InitStruct.VPSEL            = OPAMP_CSR_VPSEL_P1;
    OPAMP_InitStruct.TOEXT            = OPAMP_CSR_TOEXT_DISABLE;
    OPAMP_InitStruct.TOINT            = OPAMP_CSR_TOINT_ENABLE;
    OPAMP_InitStruct.BIASMode         = OPAMP_BIAS_VBG;

    OPAMP_Init(HW_MC_OPAMP, &OPAMP_InitStruct);
    OPAMP_Enable(HW_MC_OPAMP);
}
