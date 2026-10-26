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
 * @brief  模拟通道引脚初始化（BEMF / 电流 / 母线 / 温度 ADC 输入）
 */
static void BSP_MC_GPIO_InitAnalog(void)
{
    /* ---- ADC 模拟输入 ---- */
    gpio_mode_set(HW_MC_ADC_U_BEMF_GPIO_Port,  GPIO_MODE_ANALOG, GPIO_PUPD_NONE, HW_MC_ADC_U_BEMF_Pin);
    gpio_mode_set(HW_MC_ADC_V_BEMF_GPIO_Port,  GPIO_MODE_ANALOG, GPIO_PUPD_NONE, HW_MC_ADC_V_BEMF_Pin);
    gpio_mode_set(HW_MC_ADC_W_BEMF_GPIO_Port,  GPIO_MODE_ANALOG, GPIO_PUPD_NONE, HW_MC_ADC_W_BEMF_Pin);
    gpio_mode_set(HW_MC_ADC_CURRENT_GPIO_Port, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, HW_MC_ADC_CURRENT_Pin);
    gpio_mode_set(HW_MC_ADC_VBUS_GPIO_Port,    GPIO_MODE_ANALOG, GPIO_PUPD_NONE, HW_MC_ADC_VBUS_Pin);
    gpio_mode_set(HW_MC_ADC_TEMP_GPIO_Port,    GPIO_MODE_ANALOG, GPIO_PUPD_NONE, HW_MC_ADC_TEMP_Pin);
}

/**
 * @brief  TIMER0 互补 PWM 引脚初始化（上桥 CH0/1/2 + 下桥 CH0N/1N/2N + 刹车 BRK）
 */
static void BSP_MC_GPIO_InitPwm(void)
{
    /* ---- TIMER0 上桥 PA8/PA9/PA10（CH0/CH1/CH2）---- */
    gpio_mode_set(HW_MC_PWM_UH_GPIO_Port, GPIO_MODE_AF, GPIO_PUPD_NONE, HW_MC_PWM_UH_Pin);
    gpio_output_options_set(HW_MC_PWM_UH_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, HW_MC_PWM_UH_Pin);

    gpio_mode_set(HW_MC_PWM_VH_GPIO_Port, GPIO_MODE_AF, GPIO_PUPD_NONE, HW_MC_PWM_VH_Pin);
    gpio_output_options_set(HW_MC_PWM_VH_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, HW_MC_PWM_VH_Pin);

    gpio_mode_set(HW_MC_PWM_WH_GPIO_Port, GPIO_MODE_AF, GPIO_PUPD_NONE, HW_MC_PWM_WH_Pin);
    gpio_output_options_set(HW_MC_PWM_WH_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, HW_MC_PWM_WH_Pin);

    gpio_af_set(HW_MC_PWM_UH_GPIO_Port, GPIO_AF_2, HW_MC_PWM_UH_Pin);
    gpio_af_set(HW_MC_PWM_VH_GPIO_Port, GPIO_AF_2, HW_MC_PWM_VH_Pin);
    gpio_af_set(HW_MC_PWM_WH_GPIO_Port, GPIO_AF_2, HW_MC_PWM_WH_Pin);

    /* ---- TIMER0 下桥 PB13/PB14/PB15（CH0N/CH1N/CH2N）---- */
    gpio_mode_set(HW_MC_PWM_UL_GPIO_Port, GPIO_MODE_AF, GPIO_PUPD_NONE, HW_MC_PWM_UL_Pin);
    gpio_output_options_set(HW_MC_PWM_UL_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, HW_MC_PWM_UL_Pin);

    gpio_mode_set(HW_MC_PWM_VL_GPIO_Port, GPIO_MODE_AF, GPIO_PUPD_NONE, HW_MC_PWM_VL_Pin);
    gpio_output_options_set(HW_MC_PWM_VL_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, HW_MC_PWM_VL_Pin);

    gpio_mode_set(HW_MC_PWM_WL_GPIO_Port, GPIO_MODE_AF, GPIO_PUPD_NONE, HW_MC_PWM_WL_Pin);
    gpio_output_options_set(HW_MC_PWM_WL_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, HW_MC_PWM_WL_Pin);

    gpio_af_set(HW_MC_PWM_UL_GPIO_Port, GPIO_AF_2, HW_MC_PWM_UL_Pin);
    gpio_af_set(HW_MC_PWM_VL_GPIO_Port, GPIO_AF_2, HW_MC_PWM_VL_Pin);
    gpio_af_set(HW_MC_PWM_WL_GPIO_Port, GPIO_AF_2, HW_MC_PWM_WL_Pin);

    /* ---- 刹车输入 PB12（BRK）---- */
    gpio_mode_set(HW_MC_PWM_BRK_GPIO_Port, GPIO_MODE_AF, GPIO_PUPD_NONE, HW_MC_PWM_BRK_Pin);
    gpio_af_set(HW_MC_PWM_BRK_GPIO_Port, GPIO_AF_2, HW_MC_PWM_BRK_Pin);
}

/**
 * @brief  电机控制 GPIO 初始化入口
 */
void BSP_MC_GPIO_Init(void)
{
    BSP_MC_GPIO_InitAnalog();
    BSP_MC_GPIO_InitPwm();
}
