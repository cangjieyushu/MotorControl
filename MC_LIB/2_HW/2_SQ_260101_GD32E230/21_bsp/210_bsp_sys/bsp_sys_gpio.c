/*
*     File Name :                        bsp_sys_gpio
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             系统 GPIO 初始化
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_sys_gpio.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 内部辅助函数 ----------------------------*/
static void BSP_SYS_GPIO_InitOutput(void)
{
    /* 在此添加 LED、测试点、RS485_EN 的 GPIO 初始化 */
    /* config port to USARTx_Tx */
    /* config port to USARTx_Rx */
    gpio_af_set(HW_SYS_UART_TX_GPIO_Port, GPIO_AF_0, HW_SYS_UART_TX_Pin);
    gpio_af_set(HW_SYS_UART_RX_GPIO_Port, GPIO_AF_0, HW_SYS_UART_RX_Pin);

    /* config USART Tx as alternate function push-pull */
    gpio_mode_set(HW_SYS_UART_TX_GPIO_Port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, HW_SYS_UART_TX_Pin);
    gpio_output_options_set(HW_SYS_UART_TX_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, HW_SYS_UART_TX_Pin);

    /* config USART Rx as alternate function push-pull */
    gpio_mode_set(HW_SYS_UART_RX_GPIO_Port, GPIO_MODE_AF, GPIO_PUPD_PULLUP, HW_SYS_UART_RX_Pin);
    gpio_output_options_set(HW_SYS_UART_RX_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, HW_SYS_UART_RX_Pin);
    
    /* configure UART_TXEN GPIO port */ 
    gpio_mode_set(HW_SYS_UART_TXEN_GPIO_Port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, HW_SYS_UART_TXEN_Pin);
    gpio_output_options_set(HW_SYS_UART_TXEN_GPIO_Port, GPIO_OTYPE_PP, GPIO_OSPEED_2MHZ, HW_SYS_UART_TXEN_Pin);
    /* reset UART_TXEN GPIO pin */
    gpio_bit_reset(HW_SYS_UART_TXEN_GPIO_Port, HW_SYS_UART_TXEN_Pin);
}

static void BSP_SYS_GPIO_InitInput(void)
{
    
}


/*-------------------------- 4. 公有接口实现 -----------------------------*/
/*
Function: BSP_SYS_GPIO_Init
Description: 系统 GPIO 初始化
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_SYS_GPIO_Init(void)
{
    BSP_SYS_GPIO_InitOutput();
    BSP_SYS_GPIO_InitInput();
}

/*
Function: BSP_SYS_GPIO_Read_START_State
Description: START 按键状态读取
Return: 0 - 按下；1 - 松开
*/
Q08U_ BSP_SYS_GPIO_Read_START_State(void)
{
    return 1U;   /* 默认松开 */
}

/*
Function: BSP_SYS_GPIO_Read_STOP_State
Description: STOP 按键状态读取
Return: 0 - 按下；1 - 松开
*/
Q08U_ BSP_SYS_GPIO_Read_STOP_State(void)
{
    return 1U;   /* 默认松开 */
}

/*===========================================================================
 *  语义按键读取（引脚 → 功能的映射层）
 *===========================================================================*/

Q08U_ BSP_SYS_GPIO_Read_Key_UP(void)   { return 1U; }
Q08U_ BSP_SYS_GPIO_Read_Key_DOWN(void) { return 1U; }
Q08U_ BSP_SYS_GPIO_Read_Key_MENU(void) { return 1U; }
Q08U_ BSP_SYS_GPIO_Read_Key_OK(void)   { return 1U; }

/*-------------------------- 5. LED 控制接口 ----------------------------*/
void BSP_SYS_GPIO_RED_Set(void){ }
void BSP_SYS_GPIO_RED_Clr(void){ }
void BSP_SYS_GPIO_RED_Toggle(void){ }

void BSP_SYS_GPIO_YEW_Set(void){ }
void BSP_SYS_GPIO_YEW_Clr(void){ }
void BSP_SYS_GPIO_YEW_Toggle(void){ }

void BSP_SYS_GPIO_GRE_Set(void){ }
void BSP_SYS_GPIO_GRE_Clr(void){ }
void BSP_SYS_GPIO_GRE_Toggle(void){ }

void BSP_SYS_GPIO_TEST1_Set(void){ }
void BSP_SYS_GPIO_TEST1_Clr(void){ }
void BSP_SYS_GPIO_TEST1_Toggle(void){ }

void BSP_SYS_GPIO_TEST2_Set(void){ }
void BSP_SYS_GPIO_TEST2_Clr(void){ }
void BSP_SYS_GPIO_TEST2_Toggle(void){ }

/*
Function: BSP_SYS_GPIO_TXEN
Description: RS485 方向控制（1 = 发送；0 = 接收）
Input: state - 1 发送 / 0 接收
Return: 无
Author: CJYS
*/
void BSP_SYS_GPIO_TXEN(Q32U_ state)
{
    if (state != 0U)
    {
        gpio_bit_set(HW_SYS_UART_TXEN_GPIO_Port, HW_SYS_UART_TXEN_Pin);      /* 发送 */
    }
    else
    {
        gpio_bit_reset(HW_SYS_UART_TXEN_GPIO_Port, HW_SYS_UART_TXEN_Pin);    /* 接收 */
    }
}
