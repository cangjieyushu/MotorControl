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
 * @brief  模拟通道引脚初始化（ADC / OPA / CMP）
 */
static void BSP_MC_GPIO_InitAnalog(void)
{

}

/**
 * @brief  TIM8 互补 PWM 引脚初始化
 */
static void BSP_MC_GPIO_InitPwm(void)
{

}

/**
 * @brief  电机控制 GPIO 初始化入口
 */
void BSP_MC_GPIO_Init(void)
{
    BSP_MC_GPIO_InitAnalog();
    BSP_MC_GPIO_InitPwm();
}
