/*
*     File Name :                        bsp_gpio
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             GPIO初始化
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_gpio.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 内部辅助函数 ----------------------------*/
static void BSP_GPIO_InitOutput(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /* 默认输出低电平 */
    GPIO_ResetBits(RED_GPIO_PORT, RED_Pin);
    GPIO_ResetBits(YEW_GPIO_PORT, YEW_Pin);
    GPIO_ResetBits(GRE_GPIO_PORT, GRE_Pin);
    GPIO_ResetBits(TEST1_GPIO_PORT, TEST1_Pin);
    GPIO_ResetBits(TEST2_GPIO_PORT, TEST2_Pin);

    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_1;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_DOWN;

    GPIO_InitStruct.GPIO_Pin = RED_Pin;
    GPIO_Init(RED_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = YEW_Pin;
    GPIO_Init(YEW_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GRE_Pin;
    GPIO_Init(GRE_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = TEST1_Pin;
    GPIO_Init(TEST1_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = TEST2_Pin;
    GPIO_Init(TEST2_GPIO_PORT, &GPIO_InitStruct);
}

static void BSP_GPIO_InitInput(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_1;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;

    GPIO_InitStruct.GPIO_Pin = START_Pin;
    GPIO_Init(START_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = STOP_Pin;
    GPIO_Init(STOP_GPIO_PORT, &GPIO_InitStruct);
}

static void BSP_GPIO_InitAnalogInput(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AN;      /* ★ F3 用 AN，不是 AIN */
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;

    /* ---- 三相电流 ADC 输入 ---- */
    GPIO_InitStruct.GPIO_Pin = ADC_U_CURRENT_Pin;   /* PA2 */
    GPIO_Init(ADC_U_CURRENT_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = ADC_V_CURRENT_Pin;   /* PA6 */
    GPIO_Init(ADC_V_CURRENT_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = ADC_W_CURRENT_Pin;   /* PB13 */
    GPIO_Init(ADC_W_CURRENT_GPIO_Port, &GPIO_InitStruct);

    /* ---- 母线电压 / 温度 ADC 输入 ---- */
    GPIO_InitStruct.GPIO_Pin = ADC_VBUS_Pin;        /* PC3 */
    GPIO_Init(ADC_VBUS_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = ADC_TEMP_Pin;        /* PC2 */
    GPIO_Init(ADC_TEMP_GPIO_Port, &GPIO_InitStruct);

    /* ---- OPA 输出引脚（模拟输出）---- */
    GPIO_InitStruct.GPIO_Pin = HAL_OPA1_Pin;        /* PA2  OPA1_VOUT */
    GPIO_Init(HAL_OPA1_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = HAL_OPA2_Pin;        /* PC5  OPA2_VOUT */
    GPIO_Init(HAL_OPA2_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = HAL_OPA3_Pin;        /* PB1  OPA3_VOUT */
    GPIO_Init(HAL_OPA3_GPIO_Port, &GPIO_InitStruct);

    /* ---- DAC 输出引脚（模拟输出）---- */
    GPIO_InitStruct.GPIO_Pin = HAL_DAC_VH_Pin;      /* PA4  DAC1_OUT1 */
    GPIO_Init(HAL_DAC_VH_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = HAL_DAC_VL_Pin;      /* PA5  DAC1_OUT2 */
    GPIO_Init(HAL_DAC_VL_GPIO_Port, &GPIO_InitStruct);

    /* ---- CMP 主比较器 P 端（外部走线接 OPA 输出）---- */
    GPIO_InitStruct.GPIO_Pin = HAL_OCP_COMP1_Pin;   /* PA1  COMP1_INP */
    GPIO_Init(HAL_OCP_COMP1_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = HAL_OCP_COMP3_Pin;   /* PB14 COMP3_INP */
    GPIO_Init(HAL_OCP_COMP3_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = HAL_OCP_COMP5_Pin;   /* PB13 COMP5_INP */
    GPIO_Init(HAL_OCP_COMP5_GPIO_Port, &GPIO_InitStruct);
}

static void BSP_GPIO_InitPwm(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_3;   /* ★ 用 Level_3，50MHz */

    /* ---- TIM8 高侧 CH1/2/3（PC6/PC7/PC8）---- */
    GPIO_InitStruct.GPIO_Pin = UH_PWM_Pin;
    GPIO_Init(UH_PWM_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = VH_PWM_Pin;
    GPIO_Init(VH_PWM_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = WH_PWM_Pin;
    GPIO_Init(WH_PWM_GPIO_Port, &GPIO_InitStruct);

    /* ---- TIM8 低侧 CH1N/2N/3N（PB3/PB4/PB5）---- */
    GPIO_InitStruct.GPIO_Pin = UL_PWM_Pin;
    GPIO_Init(UL_PWM_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = VL_PWM_Pin;
    GPIO_Init(VL_PWM_GPIO_Port, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = WL_PWM_Pin;
    GPIO_Init(WL_PWM_GPIO_Port, &GPIO_InitStruct);

    /* ---- AF4（TIM8 的 AF 编号）---- */
    GPIO_PinAFConfig(UH_PWM_GPIO_Port, UH_PWM_Pin_Source, GPIO_AF_4);
    GPIO_PinAFConfig(VH_PWM_GPIO_Port, VH_PWM_Pin_Source, GPIO_AF_4);
    GPIO_PinAFConfig(WH_PWM_GPIO_Port, WH_PWM_Pin_Source, GPIO_AF_4);
    GPIO_PinAFConfig(UL_PWM_GPIO_Port, UL_PWM_Pin_Source, GPIO_AF_4);
    GPIO_PinAFConfig(VL_PWM_GPIO_Port, VL_PWM_Pin_Source, GPIO_AF_4);
    GPIO_PinAFConfig(WL_PWM_GPIO_Port, WL_PWM_Pin_Source, GPIO_AF_4);

    /* 注：CMP→TIM8_BKIN 是芯片内部硬件连接，不需要外部引脚 */
}

static void BSP_GPIO_InitUart(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /* ---- USART1 TX/RX（PA9/PA10，AF7）---- */
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_3;

    GPIO_InitStruct.GPIO_Pin = UART_TX_Pin;
    GPIO_Init(UART_TX_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = UART_RX_Pin;
    GPIO_Init(UART_RX_PORT, &GPIO_InitStruct);

    GPIO_PinAFConfig(UART_TX_PORT, UART_TX_Pin_Source, GPIO_AF_7);
    GPIO_PinAFConfig(UART_RX_PORT, UART_RX_Pin_Source, GPIO_AF_7);

    /* ---- RS485 方向控制（PA11，GPIO 输出）---- */
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_DOWN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_1;
    GPIO_InitStruct.GPIO_Pin   = UART_EN_Pin;
    GPIO_Init(UART_EN_PORT, &GPIO_InitStruct);
    GPIO_ResetBits(UART_EN_PORT, UART_EN_Pin);
}

static void BSP_GPIO_InitSpi(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /* ---- SPI3：PA15(NSS) / PC10(SCK) / PC11(MISO) / PC12(MOSI)，AF6 ---- */
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_3;

    GPIO_InitStruct.GPIO_Pin = SPI_NSS_Pin;
    GPIO_Init(SPI_NSS_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = SPI_SCK_Pin;
    GPIO_Init(SPI_SCK_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = SPI_MISO_Pin;
    GPIO_Init(SPI_MISO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = SPI_MOSI_Pin;
    GPIO_Init(SPI_MOSI_PORT, &GPIO_InitStruct);

    /* SPI3 的 AF 编号是 6 */
    GPIO_PinAFConfig(SPI_NSS_PORT,  SPI_NSS_Pin_Source,  GPIO_AF_6);
    GPIO_PinAFConfig(SPI_SCK_PORT,  SPI_SCK_Pin_Source,  GPIO_AF_6);
    GPIO_PinAFConfig(SPI_MISO_PORT, SPI_MISO_Pin_Source, GPIO_AF_6);
    GPIO_PinAFConfig(SPI_MOSI_PORT, SPI_MOSI_Pin_Source, GPIO_AF_6);

    /* ---- SPI 方向的 GPIO（若使用软件片选/中断）---- */
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_1;

    GPIO_InitStruct.GPIO_Pin = SPI_OUT_Pin;
    GPIO_Init(SPI_OUT_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin  = SPI_IN_Pin;
    GPIO_Init(SPI_IN_PORT, &GPIO_InitStruct);
}


/*-------------------------- 4. 公有接口实现 -----------------------------*/
void BSP_GPIO_Init(void)
{
    BSP_GPIO_InitOutput();         /* 输出：LED / 测试点 */
    BSP_GPIO_InitInput();          /* 输入：按键 */
    BSP_GPIO_InitAnalogInput();    /* 模拟：ADC/OPA/DAC/CMP */
    BSP_GPIO_InitPwm();            /* 复用：TIM8 六路 PWM */
    BSP_GPIO_InitUart();           /* 复用 + 输出：USART1 + RS485 EN */
    BSP_GPIO_InitSpi();            /* 复用 + 输出 + 输入：SPI3 */
}


/*-------------------------- 5. 按键读取接口 -----------------------------*/
/*
Function: BSP_GPIO_Read_START_State
Description: 读取 START 按键状态（PC9）
Return: 0 - 按下；1 - 松开（上拉输入）
*/
Q32U_ BSP_GPIO_Read_START_State(void)
{
    return (Q32U_)GPIO_ReadInputDataBit(START_GPIO_PORT, START_Pin);
}

/*
Function: BSP_GPIO_Read_STOP_State
Description: 读取 STOP 按键状态（PA8）
Return: 0 - 按下；1 - 松开（上拉输入）
*/
Q32U_ BSP_GPIO_Read_STOP_State(void)
{
    return (Q32U_)GPIO_ReadInputDataBit(STOP_GPIO_PORT, STOP_Pin);
}


/*-------------------------- 6. LED 控制接口 ----------------------------*/
/* 三色指示灯 */
void BSP_GPIO_RED_Set(void)    { GPIO_SetBits(RED_GPIO_PORT, RED_Pin); }
void BSP_GPIO_RED_Clr(void)    { GPIO_ResetBits(RED_GPIO_PORT, RED_Pin); }
void BSP_GPIO_RED_Toggle(void) { GPIO_WriteBit(RED_GPIO_PORT, RED_Pin,
                                               (BitAction)(1 - GPIO_ReadOutputDataBit(RED_GPIO_PORT, RED_Pin))); }

void BSP_GPIO_YEW_Set(void)    { GPIO_SetBits(YEW_GPIO_PORT, YEW_Pin); }
void BSP_GPIO_YEW_Clr(void)    { GPIO_ResetBits(YEW_GPIO_PORT, YEW_Pin); }
void BSP_GPIO_YEW_Toggle(void) { GPIO_WriteBit(YEW_GPIO_PORT, YEW_Pin,
                                               (BitAction)(1 - GPIO_ReadOutputDataBit(YEW_GPIO_PORT, YEW_Pin))); }

void BSP_GPIO_GRE_Set(void)    { GPIO_SetBits(GRE_GPIO_PORT, GRE_Pin); }
void BSP_GPIO_GRE_Clr(void)    { GPIO_ResetBits(GRE_GPIO_PORT, GRE_Pin); }
void BSP_GPIO_GRE_Toggle(void) { GPIO_WriteBit(GRE_GPIO_PORT, GRE_Pin,
                                               (BitAction)(1 - GPIO_ReadOutputDataBit(GRE_GPIO_PORT, GRE_Pin))); }

/* 测试点 */
void BSP_GPIO_TEST1_Set(void)    { GPIO_SetBits(TEST1_GPIO_PORT, TEST1_Pin); }
void BSP_GPIO_TEST1_Clr(void)    { GPIO_ResetBits(TEST1_GPIO_PORT, TEST1_Pin); }
void BSP_GPIO_TEST1_Toggle(void) { GPIO_WriteBit(TEST1_GPIO_PORT, TEST1_Pin,
                                                 (BitAction)(1 - GPIO_ReadOutputDataBit(TEST1_GPIO_PORT, TEST1_Pin))); }

void BSP_GPIO_TEST2_Set(void)    { GPIO_SetBits(TEST2_GPIO_PORT, TEST2_Pin); }
void BSP_GPIO_TEST2_Clr(void)    { GPIO_ResetBits(TEST2_GPIO_PORT, TEST2_Pin); }
void BSP_GPIO_TEST2_Toggle(void) { GPIO_WriteBit(TEST2_GPIO_PORT, TEST2_Pin,
                                                 (BitAction)(1 - GPIO_ReadOutputDataBit(TEST2_GPIO_PORT, TEST2_Pin))); }
/*
Function: BSP_GPIO_TXEN
Description: RS485 方向控制（1 = 发送；0 = 接收）
Input: state - 1 发送 / 0 接收
Output: 无
Return: 无
Author: CJYS
*/
void BSP_GPIO_TXEN(Q32U_ state)
{
    if (state)
    {
        GPIO_SetBits(UART_EN_PORT, UART_EN_Pin);      /* 发送方向 */
    }
    else
    {
        GPIO_ResetBits(UART_EN_PORT, UART_EN_Pin);    /* 接收方向 */
    }
}
