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
 * @brief  输出引脚初始化（LED / 测试点 / RS485 EN）
 */
static void BSP_SYS_GPIO_InitOutput(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /* 默认输出低电平 */
    GPIO_ResetBits(HW_SYS_RED_GPIO_Port,   HW_SYS_RED_Pin);
    GPIO_ResetBits(HW_SYS_YEW_GPIO_Port,   HW_SYS_YEW_Pin);
    GPIO_ResetBits(HW_SYS_GRE_GPIO_Port,   HW_SYS_GRE_Pin);
    GPIO_ResetBits(HW_SYS_TEST1_GPIO_Port, HW_SYS_TEST1_Pin);
    GPIO_ResetBits(HW_SYS_TEST2_GPIO_Port, HW_SYS_TEST2_Pin);

    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_1;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_DOWN;

    GPIO_InitStruct.GPIO_Pin = HW_SYS_RED_Pin;   GPIO_Init(HW_SYS_RED_GPIO_Port,   &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = HW_SYS_YEW_Pin;   GPIO_Init(HW_SYS_YEW_GPIO_Port,   &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = HW_SYS_GRE_Pin;   GPIO_Init(HW_SYS_GRE_GPIO_Port,   &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = HW_SYS_TEST1_Pin; GPIO_Init(HW_SYS_TEST1_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = HW_SYS_TEST2_Pin; GPIO_Init(HW_SYS_TEST2_GPIO_Port, &GPIO_InitStruct);

    /* RS485 方向控制（PA11，GPIO 输出） */
    GPIO_InitStruct.GPIO_Pin   = HW_SYS_UART_EN_Pin;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_DOWN;
    GPIO_Init(HW_SYS_UART_EN_Port, &GPIO_InitStruct);
    GPIO_ResetBits(HW_SYS_UART_EN_Port, HW_SYS_UART_EN_Pin);   /* 默认接收方向 */
}

/**
 * @brief  输入引脚初始化（按键）
 */
static void BSP_SYS_GPIO_InitInput(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_1;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;

    GPIO_InitStruct.GPIO_Pin = HW_SYS_START_Pin; GPIO_Init(HW_SYS_START_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = HW_SYS_STOP_Pin;  GPIO_Init(HW_SYS_STOP_GPIO_Port,  &GPIO_InitStruct);
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
 * @brief  读取启动键状态
 * @return 1 = 松开，0 = 按下
 */
Q08U_ BSP_SYS_GPIO_Read_START_State(void)
{
    return (Q08U_)GPIO_ReadInputDataBit(HW_SYS_START_GPIO_Port, HW_SYS_START_Pin);
}

/**
 * @brief  读取停止键状态
 * @return 1 = 松开，0 = 按下
 */
Q08U_ BSP_SYS_GPIO_Read_STOP_State(void)
{
    return (Q08U_)GPIO_ReadInputDataBit(HW_SYS_STOP_GPIO_Port, HW_SYS_STOP_Pin);
}

/**
 * @brief  读取按键 UP（预留，恒返回 1）
 * @return 1
 */
Q08U_ BSP_SYS_GPIO_Read_Key_UP(void)
{
    return 1U;
}

/**
 * @brief  读取按键 DOWN（预留，恒返回 1）
 * @return 1
 */
Q08U_ BSP_SYS_GPIO_Read_Key_DOWN(void)
{
    return 1U;
}

/**
 * @brief  读取按键 MENU（预留，恒返回 1）
 * @return 1
 */
Q08U_ BSP_SYS_GPIO_Read_Key_MENU(void)
{
    return 1U;
}

/**
 * @brief  读取按键 OK（预留，恒返回 1）
 * @return 1
 */
Q08U_ BSP_SYS_GPIO_Read_Key_OK(void)
{
    return 1U;
}

/* ======================== LED 控制接口 ==================== */

/**
 * @brief  LED1 亮（预留）
 */
void BSP_SYS_GPIO_LED1_Set(void)
{
    
}

/**
 * @brief  LED1 灭（预留）
 */
void BSP_SYS_GPIO_LED1_Clr(void)
{
    
}

/**
 * @brief  LED2 亮（预留）
 */
void BSP_SYS_GPIO_LED2_Set(void)
{
    
}

/**
 * @brief  LED2 灭（预留）
 */
void BSP_SYS_GPIO_LED2_Clr(void)
{
    
}

/**
 * @brief  红色 LED 亮
 */
void BSP_SYS_GPIO_RED_Set(void)
{
    GPIO_SetBits(HW_SYS_RED_GPIO_Port, HW_SYS_RED_Pin);
}

/**
 * @brief  红色 LED 灭
 */
void BSP_SYS_GPIO_RED_Clr(void)
{
    GPIO_ResetBits(HW_SYS_RED_GPIO_Port, HW_SYS_RED_Pin);
}

/**
 * @brief  黄色 LED 亮
 */
void BSP_SYS_GPIO_YEW_Set(void)
{
    GPIO_SetBits(HW_SYS_YEW_GPIO_Port, HW_SYS_YEW_Pin);
}

/**
 * @brief  黄色 LED 灭
 */
void BSP_SYS_GPIO_YEW_Clr(void)
{
    GPIO_ResetBits(HW_SYS_YEW_GPIO_Port, HW_SYS_YEW_Pin);
}

/**
 * @brief  绿色 LED 亮
 */
void BSP_SYS_GPIO_GRE_Set(void)
{
    GPIO_SetBits(HW_SYS_GRE_GPIO_Port, HW_SYS_GRE_Pin);
}

/**
 * @brief  绿色 LED 灭
 */
void BSP_SYS_GPIO_GRE_Clr(void)
{
    GPIO_ResetBits(HW_SYS_GRE_GPIO_Port, HW_SYS_GRE_Pin);
}

/* ======================== 测试点接口 ====================== */

/**
 * @brief  测试点 1 置高
 */
void BSP_SYS_GPIO_TEST1_Set(void)
{
    GPIO_SetBits(HW_SYS_TEST1_GPIO_Port, HW_SYS_TEST1_Pin);
}

/**
 * @brief  测试点 1 置低
 */
void BSP_SYS_GPIO_TEST1_Clr(void)
{
    GPIO_ResetBits(HW_SYS_TEST1_GPIO_Port, HW_SYS_TEST1_Pin);
}

/**
 * @brief  测试点 2 置高
 */
void BSP_SYS_GPIO_TEST2_Set(void)
{
    GPIO_SetBits(HW_SYS_TEST2_GPIO_Port, HW_SYS_TEST2_Pin);
}

/**
 * @brief  测试点 2 置低
 */
void BSP_SYS_GPIO_TEST2_Clr(void)
{
    GPIO_ResetBits(HW_SYS_TEST2_GPIO_Port, HW_SYS_TEST2_Pin);
}

/* ======================== RS485 方向控制 ================== */

/**
 * @brief  RS485 方向控制
 * @param  state  1 = 发送方向，0 = 接收方向
 */
void BSP_SYS_GPIO_TXEN(Q32U_ state)
{
    if (state)
    {
        GPIO_SetBits(HW_SYS_UART_EN_Port, HW_SYS_UART_EN_Pin);      /* 发送方向 */
    }
    else
    {
        GPIO_ResetBits(HW_SYS_UART_EN_Port, HW_SYS_UART_EN_Pin);    /* 接收方向 */
    }
}
