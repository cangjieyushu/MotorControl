/**************************************************************************************************/
/** 
 * @file      : Z20A8300A_Hal.h
 * @brief     : Z20A8300A Hardware Abstract Layer Header File.
 *              - Platform : Z20K11xM
 * @version   : V0.1
 * @date      : 2022-08-15
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @Copyright : Copyright (C) 2022 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
#ifndef Z20A8300A_HAL_H
#define Z20A8300A_HAL_H

/** @addtogroup Z20A8300A_Driver
 *  @{
 */

/** @addtogroup Z20A8300A_Hal
 *  @brief Z20A8300A Hardware Abstraction Layer API.
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/** @defgroup Hal_Public_MacroDefinition
 *  @{
 */

#define Z20A8300A_SPI_ID             SPI1_ID
#define Z20A8300A_SPI_CLOCK_MODULE   CLK_SPI1
#define Z20A8300A_SPI_CLOCK_GATE     SYSCTRL_SPI1

#define Z20A8300A_SPI_PCS            SPI_SS_PCS0
#define Z20A8300A_SPI_PCS_PORT       PORT_D
#define Z20A8300A_SPI_PCS_PIN        GPIO_3
#define Z20A8300A_SPI_PCS_PINMUX     PTD3_SPI1_PCS0

#define Z20A8300A_SPI_SCK_PORT       PORT_A
#define Z20A8300A_SPI_SCK_PIN        GPIO_10
#define Z20A8300A_SPI_SCK_PINMUX     PTA10_SPI1_SCK

#define Z20A8300A_SPI_MOSI_PORT      PORT_D
#define Z20A8300A_SPI_MOSI_PIN       GPIO_2
#define Z20A8300A_SPI_MOSI_PINMUX    PTD2_SPI1_SOUT

#define Z20A8300A_SPI_MISO_PORT      PORT_A
#define Z20A8300A_SPI_MISO_PIN       GPIO_3
#define Z20A8300A_SPI_MISO_PINMUX    PTA3_SPI1_SIN

#define Z20A8300A_RST_PORT           PORT_D
#define Z20A8300A_RST_PIN            GPIO_6
#define Z20A8300A_RST_PINMUX         PTD6_GPIO

#define Z20A8300A_ENABLE_PORT        PORT_D
#define Z20A8300A_ENABLE_PIN         GPIO_7
#define Z20A8300A_ENABLE_PINMUX      PTD7_GPIO

#define Z20A8300A_DIAG_PORT          PORT_A
#define Z20A8300A_DIAG_PIN           GPIO_6
//#define Z20A8300A_DIAG_PINMUX      PTA6_GPIO
#define Z20A8300A_DIAG_PINMUX        PTA6_TIM0_FLT1

/** @} end of Hal_Public_MacroDefinition */

/** @defgroup Hal_Public_TypeDefinition
 *  @{
 */

/** @} end of group Hal_Public_TypeDefinition */

/** @defgroup Hal_Global_VariableDeclaration
 *  @{
 */

/** @} end of group Hal_Global_VariableDeclaration */

/** @defgroup Hal_Public_FunctionDeclaration
 *  @{
 */

/**
 * @brief       MCU Z20A8300A SPI Interface Init
 *
 * @param[in]   none
 *
 * @return      none
 *
 */
void MCU_Z20A8300A_SpiInit(void);

/**
 * @brief       MCU Z20A8300A GPIO Init
 *
 * @param[in]   none
 *
 * @return      none
 *
 */
void MCU_Z20A8300A_GpioInit(void);

/**
 * @brief       MCU SPI Send To Z20A8300A
 *
 * @param[in]   Data: send data(u16)
 *
 * @return      status
 * @retval      0: tx buff full,send failure
 * @retval      1: send succsess
 *
 */
uint16_t MCU_SPI_SendToZ20A8300A(uint16_t Data);

/**
 * @brief       get the data received from Z20A8300A
 *
 * @param[in]   none
 *
 * @return      uint16_t
 * @retval      receive data
 */
uint16_t MCU_SPI_ReceiveFromZ20A8300A(void);

/**
 * @brief      MCU SPI Waiting For Reception From Z20A8300A
 *
 * @param[in]  none
 *
 * @return     status
 * @retval     0: timeout
 * @retval     1: data received
 *
 */
uint16_t MCU_SPI_WaitingForReceptionFromZ20A8300A(void);

/**
 * @brief      Z20A8300A Set PWM Enable Pin
 *
 * @param[in]  States: Pwm Enable Pin States:
 *                     - 0,low level
 *                     - 1,high level
 *
 * @return     none
 *
 */
void Z20A8300A_SetPWMEnablePin(uint16_t States);

/**
 * @brief      Z20A8300A Set Reset Pin
 *
 * @param[in]  States: Reset Pin States:
 *                     - 0,low level
 *                     - 1,high level
 *
 * @return     none
 *
 */
void Z20A8300A_SetResetPin(uint16_t States);

/**
 * @brief      Z20A8300A Get Diag Pin States
 *
 * @param[in]  none
 *
 * @return     status
 * @retval     0: fault
 * @retval     1: normal
 *
 */
uint16_t Z20A8300A_GetDiagPinStates(void);

/** @} end of group Hal_Public_FunctionDeclaration */

#ifdef __cplusplus
}
#endif

/** @} end of group Z20A8300A_Hal */

/** @} end of group Z20A8300A_Driver */

#endif /* Z20A8300A_HAL_H */
