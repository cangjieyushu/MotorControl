/**
 * @file    bsp_sys_gpio.c
 * @brief   系统 GPIO 初始化
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "bsp_sys_gpio.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  输出引脚初始化（UART 复用 / RS485 TXEN）
 */
static void BSP_SYS_GPIO_InitOutput(void)
{
    /* 串口 TX / RX 复用配置 */
    gpio_af_set(HW_SYS_UART_TX_GPIO_Port, GPIO_AF_0, HW_SYS_UART_TX_Pin);
    gpio_af_set(HW_SYS_UART_RX_GPIO_Port, GPIO_AF_0, HW_SYS_UART_RX_Pin);

    /* UART TX：复用推挽 */
    gpio_mode_set(HW_SYS_UART_TX_GPIO_Port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, HW_SYS_UART_TX_Pin);
    gpio_output_options_set(HW_SYS_UART_TX_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, HW_SYS_UART_TX_Pin);

    /* UART RX：复用推挽 */
    gpio_mode_set(HW_SYS_UART_RX_GPIO_Port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, HW_SYS_UART_RX_Pin);
    gpio_output_options_set(HW_SYS_UART_RX_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, HW_SYS_UART_RX_Pin);

    /* RS485 方向控制 TXEN */
    gpio_mode_set(HW_SYS_UART_TXEN_GPIO_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, HW_SYS_UART_TXEN_Pin);
    gpio_output_options_set(HW_SYS_UART_TXEN_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, HW_SYS_UART_TXEN_Pin);
    gpio_bit_reset(HW_SYS_UART_TXEN_GPIO_Port, HW_SYS_UART_TXEN_Pin);   /* 默认接收方向 */
}

/**
 * @brief  输入引脚初始化（按键 BTN1~BTN4）
 */
static void BSP_SYS_GPIO_InitInput(void)
{
    /* BTN1 */
    gpio_mode_set(HW_SYS_BTN1_GPIO_Port, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, HW_SYS_BTN1_Pin);
    gpio_bit_reset(HW_SYS_BTN1_GPIO_Port, HW_SYS_BTN1_Pin);
    /* BTN2 */
    gpio_mode_set(HW_SYS_BTN2_GPIO_Port, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, HW_SYS_BTN2_Pin);
    gpio_bit_reset(HW_SYS_BTN2_GPIO_Port, HW_SYS_BTN2_Pin);
    /* BTN3 */
    gpio_mode_set(HW_SYS_BTN3_GPIO_Port, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, HW_SYS_BTN3_Pin);
    gpio_bit_reset(HW_SYS_BTN3_GPIO_Port, HW_SYS_BTN3_Pin);
    /* BTN4 */
    gpio_mode_set(HW_SYS_BTN4_GPIO_Port, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, HW_SYS_BTN4_Pin);
    gpio_bit_reset(HW_SYS_BTN4_GPIO_Port, HW_SYS_BTN4_Pin);
}

/**
 * @brief  系统 GPIO 初始化入口
 */
void BSP_SYS_GPIO_Init(void)
{
    BSP_SYS_GPIO_InitOutput();
    BSP_SYS_GPIO_InitInput();
}

/**
 * @brief  读取启动键状态（GD32 无独立 START，恒返回 1）
 * @return 1 = 松开
 */
Q08U_ BSP_SYS_GPIO_Read_START_State(void)
{
    return 1U;
}

/**
 * @brief  读取停止键状态（GD32 无独立 STOP，恒返回 1）
 * @return 1 = 松开
 */
Q08U_ BSP_SYS_GPIO_Read_STOP_State(void)
{
    return 1U;
}

/**
 * @brief  读取按键 UP（BTN1）
 * @return 0 = 按下，1 = 松开
 */
Q08U_ BSP_SYS_GPIO_Read_Key_UP(void)
{
    return (Q08U_)gpio_input_bit_get(HW_SYS_BTN1_GPIO_Port, HW_SYS_BTN1_Pin);
}

/**
 * @brief  读取按键 DOWN（BTN2）
 * @return 0 = 按下，1 = 松开
 */
Q08U_ BSP_SYS_GPIO_Read_Key_DOWN(void)
{
    return (Q08U_)gpio_input_bit_get(HW_SYS_BTN2_GPIO_Port, HW_SYS_BTN2_Pin);
}

/**
 * @brief  读取按键 MENU（BTN3）
 * @return 0 = 按下，1 = 松开
 */
Q08U_ BSP_SYS_GPIO_Read_Key_MENU(void)
{
    return (Q08U_)gpio_input_bit_get(HW_SYS_BTN3_GPIO_Port, HW_SYS_BTN3_Pin);
}

/**
 * @brief  读取按键 OK（BTN4）
 * @return 0 = 按下，1 = 松开
 */
Q08U_ BSP_SYS_GPIO_Read_Key_OK(void)
{
    return (Q08U_)gpio_input_bit_get(HW_SYS_BTN4_GPIO_Port, HW_SYS_BTN4_Pin);
}

/* ======================== LED 控制接口 ==================== */

/**
 * @brief  LED1 亮（预留，GD32 无对应引脚）
 */
void BSP_SYS_GPIO_LED1_Set(void)
{

}

/**
 * @brief  LED1 灭（预留，GD32 无对应引脚）
 */
void BSP_SYS_GPIO_LED1_Clr(void)
{

}

/**
 * @brief  LED2 亮（预留，GD32 无对应引脚）
 */
void BSP_SYS_GPIO_LED2_Set(void)
{

}

/**
 * @brief  LED2 灭（预留，GD32 无对应引脚）
 */
void BSP_SYS_GPIO_LED2_Clr(void)
{

}

/**
 * @brief  红色 LED 亮（预留，GD32 无对应引脚）
 */
void BSP_SYS_GPIO_RED_Set(void)
{

}

/**
 * @brief  红色 LED 灭（预留，GD32 无对应引脚）
 */
void BSP_SYS_GPIO_RED_Clr(void)
{

}

/**
 * @brief  黄色 LED 亮（预留，GD32 无对应引脚）
 */
void BSP_SYS_GPIO_YEW_Set(void)
{

}

/**
 * @brief  黄色 LED 灭（预留，GD32 无对应引脚）
 */
void BSP_SYS_GPIO_YEW_Clr(void)
{

}

/**
 * @brief  绿色 LED 亮（预留，GD32 无对应引脚）
 */
void BSP_SYS_GPIO_GRE_Set(void)
{

}

/**
 * @brief  绿色 LED 灭（预留，GD32 无对应引脚）
 */
void BSP_SYS_GPIO_GRE_Clr(void)
{

}

/* ======================== 测试点接口 ====================== */

/**
 * @brief  测试点 1 置高（预留，GD32 无对应引脚）
 */
void BSP_SYS_GPIO_TEST1_Set(void)
{

}

/**
 * @brief  测试点 1 置低（预留，GD32 无对应引脚）
 */
void BSP_SYS_GPIO_TEST1_Clr(void)
{

}

/**
 * @brief  测试点 2 置高（预留，GD32 无对应引脚）
 */
void BSP_SYS_GPIO_TEST2_Set(void)
{

}

/**
 * @brief  测试点 2 置低（预留，GD32 无对应引脚）
 */
void BSP_SYS_GPIO_TEST2_Clr(void)
{

}

/* ======================== RS485 方向控制 ================== */

/**
 * @brief  RS485 方向控制
 * @param  state  1 = 发送方向，0 = 接收方向
 */
void BSP_SYS_GPIO_TXEN(Q32U_ state)
{
    if (state != 0U)
    {
        gpio_bit_set(HW_SYS_UART_TXEN_GPIO_Port, HW_SYS_UART_TXEN_Pin);      /* 发送方向 */
    }
    else
    {
        gpio_bit_reset(HW_SYS_UART_TXEN_GPIO_Port, HW_SYS_UART_TXEN_Pin);    /* 接收方向 */
    }
}
