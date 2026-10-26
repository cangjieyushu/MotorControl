/**
 * @file    bsp_mc_adc.h
 * @brief   ADC 初始化
 *          - 三 ADC 同步采样三相电流
 *          - ADC1 规则组 DMA 搬运电压/温度
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef BSP_MC_ADC_H
#define BSP_MC_ADC_H

/* ======================== 1. Includes ===================== */
#include "hw_map.h"
#include "hw_para.h"

/* ======================== 2. Defines ====================== */
#define BSP_MC_ADC_DATA_READ_VR     (4095U)
#define BSP_MC_ADC_DATA_READ_VBG    (0U)

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */
/* 规则组 DMA 缓冲区：[0] = 外部温度   [1] = 母线电压 */
extern Q32U_ BSP_ADC_SYSTEM_BUFFER[10];

/* ======================== 5. Function Prototypes ========== */
void BSP_MC_ADC_Init(void);

#endif /* BSP_MC_ADC_H */
