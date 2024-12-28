/**************************************************************************************************
*     File Name :                        BSP_GPIO.c
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             GPIO初始化及应用层接口源文件
**************************************************************************************************/
#include "BSP_GPIO.h"

#define GPIO_TOTAL_NUM                (5U)
#define GPIOA_BASE_ADDR               (GPIO_BASE_ADDR + 0x00UL)       
#define GPIOB_BASE_ADDR               (GPIO_BASE_ADDR + 0x40UL)      
#define GPIOC_BASE_ADDR               (GPIO_BASE_ADDR + 0x80UL)     
#define GPIOD_BASE_ADDR               (GPIO_BASE_ADDR + 0xC0UL)     
#define GPIOE_BASE_ADDR               (GPIO_BASE_ADDR + 0x100UL) 

static gpio_reg_t * gpioRegPtr[GPIO_TOTAL_NUM] =
{
    (gpio_reg_t *)GPIOA_BASE_ADDR,     /*!< GPIO A base address */
    (gpio_reg_t *)GPIOB_BASE_ADDR,     /*!< GPIO B base address */
    (gpio_reg_t *)GPIOC_BASE_ADDR,     /*!< GPIO C base address */
    (gpio_reg_t *)GPIOD_BASE_ADDR,     /*!< GPIO D base address */
    (gpio_reg_t *)GPIOE_BASE_ADDR      /*!< GPIO E base address */
};

/**********************************************************************************************
Function: BSP_GPIO_Init
Description: GPIO初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_GPIO_Init(void)
{
    PORT_PinmuxConfig(HAL_HALLA_PORT, HAL_HALLA_PIN, HAL_HALLA_PINMUX);
    PORT_PullConfig(HAL_HALLA_PORT, HAL_HALLA_PIN, PORT_PULL_DISABLED);
    GPIO_SetPinDir(HAL_HALLA_PORT, HAL_HALLA_PIN, GPIO_OUTPUT);
    
    /* SW2 */
    PORT_PinmuxConfig(HAL_SW2_PORT, HAL_SW2_PIN, HAL_SW2_PINMUX);
    PORT_PullConfig(HAL_SW2_PORT, HAL_SW2_PIN, PORT_PULL_DISABLED);
    GPIO_SetPinDir(HAL_SW2_PORT, HAL_SW2_PIN, GPIO_INPUT);
    
    /* SW3 */
    PORT_PinmuxConfig(HAL_SW3_PORT, HAL_SW3_PIN, HAL_SW3_PINMUX);
    PORT_PullConfig(HAL_SW3_PORT, HAL_SW3_PIN, PORT_PULL_DISABLED);
    GPIO_SetPinDir(HAL_SW3_PORT, HAL_SW3_PIN, GPIO_INPUT);
}

/**********************************************************************************************
Function: BSP_GPIO_Read_SW0_State
Description: 按键0状态读取
Input: 无
Output: 无
Input_Output: 无
Return: 按键0状态
Author: CJYS
***********************************************************************************************/
Q32U_ BSP_GPIO_Read_SW0_State(void)
{
    PortStatusType SW2PortStatus;
    gpio_reg_t * GPIOx = (gpio_reg_t *)(gpioRegPtr[4]);      
    SW2PortStatus.Word = GPIOx->GPIOx_PDIR.PDI;
    return (Q32U_)(SW2PortStatus.Bits.B11); 
}

/**********************************************************************************************
Function: BSP_GPIO_Read_SW1_State
Description: 按键1状态读取
Input: 无
Output: 无
Input_Output: 无
Return: 按键1状态
Author: CJYS
***********************************************************************************************/
Q32U_ BSP_GPIO_Read_SW1_State(void)
{
    PortStatusType SW3PortStatus;
    gpio_reg_t * GPIOx = (gpio_reg_t *)(gpioRegPtr[4]);      
    SW3PortStatus.Word = GPIOx->GPIOx_PDIR.PDI;
    return (Q32U_)(SW3PortStatus.Bits.B3); 
}

/**********************************************************************************************
Function: HGPIO_TogglePinOutput
Description: GPIO翻转
Input: 引脚编号，引脚位号
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void HGPIO_TogglePinOutput(PORT_Id_t port, PORT_GpioNum_t gpioNum)
{
    gpio_reg_w_t * GPIOx = (gpio_reg_w_t *)(gpioRegPtr[port]);

    GPIOx->GPIOx_PTOR = (0x01UL << (Q32U_)gpioNum);
}
