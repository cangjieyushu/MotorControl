/**
 * @file    bsp_mc_dac.c
 * @brief   DAC 阈值输出初始化
 *          - DAC1 通道 1（PA4）：窗口上限 VH，默认 3500
 *          - DAC1 通道 2（PA5）：窗口下限 VL，当前未启用
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "bsp_mc_dac.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  DAC 阈值输出初始化
 */
void BSP_MC_DAC_Init(void)
{
    DAC_InitTypeDef DAC_InitStructure;

    /* DAC 挂 APB1，使能时钟 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC1, ENABLE);

    /* ---------------- 通道 1（PA4）：窗口上限 VH ---------------- */
    DAC_InitStructure.DAC_Trigger                      = DAC_Trigger_None;
    DAC_InitStructure.DAC_WaveGeneration               = DAC_WaveGeneration_None;
    DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
    DAC_InitStructure.DAC_Buffer_Switch                = DAC_BufferSwitch_Enable;
    DAC_Init(DAC1, DAC_Channel_1, &DAC_InitStructure);

    /* ---------------- 通道 2（PA5）：窗口下限 VL ---------------- */
//    DAC_Init(DAC1, DAC_Channel_2, &DAC_InitStructure);

    /* 上电默认阈值 */
    DAC_SetChannel1Data(DAC1, DAC_Align_12b_R, 3500);
//    DAC_SetChannel2Data(DAC1, DAC_Align_12b_R, 500);

    DAC_Cmd(DAC1, DAC_Channel_1, ENABLE);
//    DAC_Cmd(DAC1, DAC_Channel_2, ENABLE);
}
