/**
 * @file    bsp_mc_opamp.c
 * @brief   OPA 跟随器 / PGA 初始化
 *          - OPA1：输出到 PA2
 *          - OPA2：输出到 PC5
 *          - OPA4：输出到 PB1
 *          - 模式与增益取自 hw_map 中的 HW_MC_OPAMPx_* 宏
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
 * @brief  配置单个 OPA（跟随器 / PGA）
 * @param  opampSel  OPA 实例
 * @param  vinpIo    同相输入 IO
 * @param  mode      工作模式（HW_MC_OPAMP_MODE_FOLLOWER / HW_MC_OPAMP_MODE_PGA）
 * @param  gain      PGA 增益
 * @param  pgaConn   PGA 内部电阻连接
 */
static void BSP_MC_OPAMP_ConfigOne(uint32_t opampSel,
                                   uint32_t vinpIo,
                                   uint32_t mode,
                                   uint32_t gain,
                                   uint32_t pgaConn)
{
    OPAMP_InitTypeDef OPAMP_InitStructure;

    OPAMP_InitStructure.OPAMP_NonInvertingInput = vinpIo;
    OPAMP_InitStructure.OPAMP_InvertingInput    = OPAMP_InvertingInput_PGA;    /* 先默认 PGA */

    /* 1. 基础初始化（先不使能） */
    OPAMP_Init(opampSel, &OPAMP_InitStructure);

//    /* 2. 将内部参考电压（50% VDDA）连接到非反相输入端作为偏置 */
//    OPAMP_VrefConnectNonInvertingInput(opampSel, ENABLE);
//    OPAMP_VrefConfig(opampSel, OPAMP_Vref_50VDDA);   /* 关键：选择 50% VDDA */

    /* 3. 根据模式配置 */
    if (mode == HW_MC_OPAMP_MODE_PGA)
    {
        OPAMP_PGAConfig(opampSel, gain, pgaConn);
    }
    else    /* 跟随器模式 */
    {
        /* 跟随器模式下，反相输入接输出 */
        OPAMP_InitStructure.OPAMP_InvertingInput = OPAMP_InvertingInput_Vout;
        OPAMP_Init(opampSel, &OPAMP_InitStructure);
    }

    /* 4. 使能 OPAMP */
    OPAMP_Cmd(opampSel, ENABLE);
}

/**
 * @brief  OPA 跟随器 / PGA 初始化（OPA1/2/4）
 */
void BSP_MC_OPAMP_Init(void)
{
    /* ---- OPA1：输出到 PA2 ---- */
    BSP_MC_OPAMP_ConfigOne(HW_MC_OPAMP1, HW_MC_OPAMP1_VINP_IO, HW_MC_OPAMP1_MODE, HW_MC_OPAMP1_GAIN, HW_MC_OPAMP1_PGA_CONNECT);

    /* ---- OPA2：输出到 PC5 ---- */
    BSP_MC_OPAMP_ConfigOne(HW_MC_OPAMP2, HW_MC_OPAMP2_VINP_IO, HW_MC_OPAMP2_MODE, HW_MC_OPAMP2_GAIN, HW_MC_OPAMP2_PGA_CONNECT);

    /* ---- OPA4：输出到 PB1 ---- */
    BSP_MC_OPAMP_ConfigOne(HW_MC_OPAMP4, HW_MC_OPAMP4_VINP_IO, HW_MC_OPAMP4_MODE, HW_MC_OPAMP4_GAIN, HW_MC_OPAMP4_PGA_CONNECT);
}
