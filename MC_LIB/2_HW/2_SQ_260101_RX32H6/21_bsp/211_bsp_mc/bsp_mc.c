/**
 * @file    bsp_mc.c
 * @brief   电机控制外设汇总初始化
 *          - 依赖顺序：GPIO → DAC → OPA → CMP → PWM → TIM → DMA → ADC
 *          - DAC 建立窗口阈值电压，OPA 输出到 CMP P 端，CMP 输出到 TIM8_BKIN
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "bsp_mc.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */
#if (HW_FUN_MC_RTT_ENABLE == 1U)
char JS_RTT_UpBuffer[256];      // J-Scope RTT Buffer
int  JS_RTT_Channel = 1;        // J-Scope RTT Channel
Q16I_ JS_RTT_Data[4];           // J-Scope RTT Buffer
#endif

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  电机控制外设汇总初始化
 */
void BSP_MC_Init(void)
{
    /* GPIO 引脚复用先配置（ADC/OPA/DAC/CMP/PWM） */
    BSP_MC_GPIO_Init();

    /* 有依赖关系的按序初始化：DAC → OPA → CMP */
    BSP_MC_DAC_Init();         /* 建立窗口阈值电压 */
    BSP_MC_OPAMP_Init();       /* OPA 输出到 CMP 的 P 端 */
    BSP_MC_CMP_Init();         /* 窗口比较器输出到 TIM8_BKIN */

    /* 电机控制主外设 */
    BSP_MC_PWM_Init();         /* TIM8 三相互补 PWM */
    BSP_MC_TIM_Init();         /* TIM2 HALL 计时 */

    /* ADC 最后：注入组配置 + 规则组 DMA */
    BSP_MC_DMA_Init();         /* DMA 配置 + 启动 ADC1 规则组 */
    BSP_MC_ADC_Init();         /* 三 ADC 配置，未启动转换 */
    
#if (HW_FUN_MC_RTT_ENABLE == 1U)
    SEGGER_RTT_ConfigUpBuffer(JS_RTT_Channel, "JScope_i2i2i2i2", &JS_RTT_UpBuffer[0], sizeof(JS_RTT_UpBuffer), SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);
#endif
}
