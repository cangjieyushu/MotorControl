/**
 * @file    bsp_mc_cmp.c
 * @brief   CMP 窗口比较器初始化
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "bsp_mc_cmp.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  窗口比较器初始化（COMP2，输出送 TIM8_BKIN）
 */
void BSP_MC_CMP_Init(void)
{
    CMP_InitTypeDef CMP_InitStruct = {0};

    CMP_InitStruct.Pol     = CMP_CxCR_POL_Positive;
    CMP_InitStruct.Rhyst   = CMP_CxCR_RHYST_0mV;
    CMP_InitStruct.Fhyst   = CMP_CxCR_FHYST_0mV;
    CMP_InitStruct.INP_Sel = CMP_INP_SEL_OPA2_out_CMP2;      /* 同相：OPA2 输出 */
    CMP_InitStruct.INM_Sel = CMP_INM_SEL_CRV;                /* 反相：内部参考 */
    CMP_InitStruct.OFLT    = CMP_CxCR_OFLT_DIV32;
    CMP_InitStruct.CRV_SEL = CMP_CRV_SEL_32_32;
    CMP_InitStruct.CRV_En  = ENABLE;
    CMP_InitStruct.CRV_Src = CMP_CR2_CRV_SRC_1;
    CMP_InitStruct.CR1_SRN = DISABLE;

    CMP_Init(HW_MC_CMP, &CMP_InitStruct);
    CMP_Enable(HW_MC_CMP);
}
