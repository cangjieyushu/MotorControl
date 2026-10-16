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

    /* RS485 方向控制（PA11，GPIO 输出）*/
    GPIO_InitStruct.GPIO_Pin   = HW_SYS_UART_EN_Pin;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_DOWN;
    GPIO_Init(HW_SYS_UART_EN_Port, &GPIO_InitStruct);
    GPIO_ResetBits(HW_SYS_UART_EN_Port, HW_SYS_UART_EN_Pin);   /* 默认接收方向 */
}

static void BSP_SYS_GPIO_InitInput(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_1;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;

    GPIO_InitStruct.GPIO_Pin = HW_SYS_START_Pin; GPIO_Init(HW_SYS_START_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = HW_SYS_STOP_Pin;  GPIO_Init(HW_SYS_STOP_GPIO_Port,  &GPIO_InitStruct);
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
    return (Q08U_)GPIO_ReadInputDataBit(HW_SYS_START_GPIO_Port, HW_SYS_START_Pin);
}

/*
Function: BSP_SYS_GPIO_Read_STOP_State
Description: STOP 按键状态读取
Return: 0 - 按下；1 - 松开
*/
Q08U_ BSP_SYS_GPIO_Read_STOP_State(void)
{
    return (Q08U_)GPIO_ReadInputDataBit(HW_SYS_STOP_GPIO_Port, HW_SYS_STOP_Pin);
}

Q08U_ BSP_SYS_GPIO_Read_Key_UP(void){return 1U;}
Q08U_ BSP_SYS_GPIO_Read_Key_DOWN(void){return 1U;}
Q08U_ BSP_SYS_GPIO_Read_Key_MENU(void){return 1U;}
Q08U_ BSP_SYS_GPIO_Read_Key_OK(void){return 1U;}

/*-------------------------- 5. LED 控制接口 ----------------------------*/
void BSP_SYS_GPIO_RED_Set(void)    { GPIO_SetBits(HW_SYS_RED_GPIO_Port, HW_SYS_RED_Pin); }
void BSP_SYS_GPIO_RED_Clr(void)    { GPIO_ResetBits(HW_SYS_RED_GPIO_Port, HW_SYS_RED_Pin); }
void BSP_SYS_GPIO_RED_Toggle(void) { GPIO_WriteBit(HW_SYS_RED_GPIO_Port, HW_SYS_RED_Pin,
                                    (BitAction)(1 - GPIO_ReadOutputDataBit(HW_SYS_RED_GPIO_Port, HW_SYS_RED_Pin))); }

void BSP_SYS_GPIO_YEW_Set(void)    { GPIO_SetBits(HW_SYS_YEW_GPIO_Port, HW_SYS_YEW_Pin); }
void BSP_SYS_GPIO_YEW_Clr(void)    { GPIO_ResetBits(HW_SYS_YEW_GPIO_Port, HW_SYS_YEW_Pin); }
void BSP_SYS_GPIO_YEW_Toggle(void) { GPIO_WriteBit(HW_SYS_YEW_GPIO_Port, HW_SYS_YEW_Pin,
                                    (BitAction)(1 - GPIO_ReadOutputDataBit(HW_SYS_YEW_GPIO_Port, HW_SYS_YEW_Pin))); }

void BSP_SYS_GPIO_GRE_Set(void)    { GPIO_SetBits(HW_SYS_GRE_GPIO_Port, HW_SYS_GRE_Pin); }
void BSP_SYS_GPIO_GRE_Clr(void)    { GPIO_ResetBits(HW_SYS_GRE_GPIO_Port, HW_SYS_GRE_Pin); }
void BSP_SYS_GPIO_GRE_Toggle(void) { GPIO_WriteBit(HW_SYS_GRE_GPIO_Port, HW_SYS_GRE_Pin,
                                    (BitAction)(1 - GPIO_ReadOutputDataBit(HW_SYS_GRE_GPIO_Port, HW_SYS_GRE_Pin))); }

/*-------------------------- 6. 测试点接口 ------------------------------*/
void BSP_SYS_GPIO_TEST1_Set(void)    { GPIO_SetBits(HW_SYS_TEST1_GPIO_Port, HW_SYS_TEST1_Pin); }
void BSP_SYS_GPIO_TEST1_Clr(void)    { GPIO_ResetBits(HW_SYS_TEST1_GPIO_Port, HW_SYS_TEST1_Pin); }
void BSP_SYS_GPIO_TEST1_Toggle(void) { GPIO_WriteBit(HW_SYS_TEST1_GPIO_Port, HW_SYS_TEST1_Pin,
                                       (BitAction)(1 - GPIO_ReadOutputDataBit(HW_SYS_TEST1_GPIO_Port, HW_SYS_TEST1_Pin))); }

void BSP_SYS_GPIO_TEST2_Set(void)    { GPIO_SetBits(HW_SYS_TEST2_GPIO_Port, HW_SYS_TEST2_Pin); }
void BSP_SYS_GPIO_TEST2_Clr(void)    { GPIO_ResetBits(HW_SYS_TEST2_GPIO_Port, HW_SYS_TEST2_Pin); }
void BSP_SYS_GPIO_TEST2_Toggle(void) { GPIO_WriteBit(HW_SYS_TEST2_GPIO_Port, HW_SYS_TEST2_Pin,
                                       (BitAction)(1 - GPIO_ReadOutputDataBit(HW_SYS_TEST2_GPIO_Port, HW_SYS_TEST2_Pin))); }

/*
Function: BSP_SYS_GPIO_TXEN
Description: RS485 方向控制（1 = 发送；0 = 接收）
Input: state - 1 发送 / 0 接收
Return: 无
Author: CJYS
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
