/**
 * @file    bsp_mc_gpio.c
 * @brief   电机控制 GPIO 初始化
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "bsp_mc_gpio.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */
static void BSP_MC_GPIO_InitAnalog(void);
static void BSP_MC_GPIO_InitPwm(void);

/* ======================== 6. Functions ==================== */

/**
 * @brief  模拟引脚初始化（三相电流 / 母线电压 / 温度 ADC 输入）
 */
static void BSP_MC_GPIO_InitAnalog(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;

    /* ---- 三相电流 ADC 输入 ---- */
    GPIO_InitStruct.GPIO_Pin = HW_MC_ADC_U_CURRENT_Pin; GPIO_Init(HW_MC_ADC_U_CURRENT_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = HW_MC_ADC_V_CURRENT_Pin; GPIO_Init(HW_MC_ADC_V_CURRENT_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = HW_MC_ADC_W_CURRENT_Pin; GPIO_Init(HW_MC_ADC_W_CURRENT_GPIO_Port, &GPIO_InitStruct);

    /* ---- 母线电压 / 温度 ADC 输入 ---- */
    GPIO_InitStruct.GPIO_Pin = HW_MC_ADC_VBUS_Pin;      GPIO_Init(HW_MC_ADC_VBUS_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = HW_MC_ADC_TEMP_Pin;      GPIO_Init(HW_MC_ADC_TEMP_GPIO_Port, &GPIO_InitStruct);
}

/**
 * @brief  PWM 引脚初始化（TIM8 高侧 CH1/2/3 + 低侧 CH1N/2N/3N）
 */
static void BSP_MC_GPIO_InitPwm(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;

    /* ---- TIM8 高侧 CH1/2/3（PC6/PC7/PC8）---- */
    GPIO_InitStruct.GPIO_Pin = HW_MC_PWM_UH_Pin; GPIO_Init(HW_MC_PWM_UH_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = HW_MC_PWM_VH_Pin; GPIO_Init(HW_MC_PWM_VH_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = HW_MC_PWM_WH_Pin; GPIO_Init(HW_MC_PWM_WH_GPIO_Port, &GPIO_InitStruct);

    /* ---- TIM8 低侧 CH1N/2N/3N（PB3/PB4/PB5）---- */
    GPIO_InitStruct.GPIO_Pin = HW_MC_PWM_UL_Pin; GPIO_Init(HW_MC_PWM_UL_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = HW_MC_PWM_VL_Pin; GPIO_Init(HW_MC_PWM_VL_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = HW_MC_PWM_WL_Pin; GPIO_Init(HW_MC_PWM_WL_GPIO_Port, &GPIO_InitStruct);

    /* ---- AF4（TIM8 的 AF 编号）---- */
    GPIO_PinAFConfig(HW_MC_PWM_UH_GPIO_Port, HW_MC_PWM_UH_Pin_Source, GPIO_AF_TIM1);
    GPIO_PinAFConfig(HW_MC_PWM_VH_GPIO_Port, HW_MC_PWM_VH_Pin_Source, GPIO_AF_TIM1);
    GPIO_PinAFConfig(HW_MC_PWM_WH_GPIO_Port, HW_MC_PWM_WH_Pin_Source, GPIO_AF_TIM1);
    GPIO_PinAFConfig(HW_MC_PWM_UL_GPIO_Port, HW_MC_PWM_UL_Pin_Source, GPIO_AF_TIM1);
    GPIO_PinAFConfig(HW_MC_PWM_VL_GPIO_Port, HW_MC_PWM_VL_Pin_Source, GPIO_AF_TIM1);
    GPIO_PinAFConfig(HW_MC_PWM_WL_GPIO_Port, HW_MC_PWM_WL_Pin_Source, GPIO_AF_TIM1);
}

/**
 * @brief  电机控制 GPIO 初始化入口
 */
void BSP_MC_GPIO_Init(void)
{
    BSP_MC_GPIO_InitAnalog();
    BSP_MC_GPIO_InitPwm();
}
