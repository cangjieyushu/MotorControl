/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef BSP_GPIO_H
#define BSP_GPIO_H

#include "MotorHal_cfg.h"

#define HAL_SW2_PORT                        PORT_E
#define HAL_SW2_PIN                         GPIO_11
#define HAL_SW2_PINMUX                      PTE11_GPIO

#define HAL_SW3_PORT                        PORT_E
#define HAL_SW3_PIN                         GPIO_3
#define HAL_SW3_PINMUX                      PTE3_GPIO

typedef union
{
    Q32U_ Word;
    struct
    {
        Q32U_ B0 : 1;
        Q32U_ B1 : 1;
        Q32U_ B2 : 1;
        Q32U_ B3 : 1;
        Q32U_ B4 : 1;
        Q32U_ B5 : 1;
        Q32U_ B6 : 1;
        Q32U_ B7 : 1;
        Q32U_ B8 : 1;
        Q32U_ B9 : 1;
        Q32U_ B10 : 1;
        Q32U_ B11 : 1;
        Q32U_ B12 : 1;
        Q32U_ B13 : 1;
        Q32U_ B14 : 1;
        Q32U_ B15 : 1;
        Q32U_ B16 : 1;
        Q32U_ B17 : 1;
        Q32U_ B18 : 1;
        Q32U_ B19 : 1;
        Q32U_ B20 : 1;
        Q32U_ B21 : 1;
        Q32U_ B22 : 1;
        Q32U_ B23 : 1;
        Q32U_ B24 : 1;
        Q32U_ B25 : 1;
        Q32U_ B26 : 1;
        Q32U_ B27 : 1;
        Q32U_ B28 : 1;
        Q32U_ B29 : 1;
        Q32U_ B30 : 1;
        Q32U_ B31 : 1;
    }Bits;
}PortStatusType;

void BSP_GPIO_Init(void);

Q32U_ BSP_GPIO_Read_SW0_State(void);
Q32U_ BSP_GPIO_Read_SW1_State(void);
void HGPIO_TogglePinOutput(PORT_Id_t port, PORT_GpioNum_t gpioNum);

#endif /* BSP_GPIO_H */
