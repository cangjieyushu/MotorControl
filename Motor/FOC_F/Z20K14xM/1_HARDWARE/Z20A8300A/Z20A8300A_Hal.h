/**************************************************************************************************/
/** 
 * @file      : Z20A8300A_Hal.h
 * @brief     : Z20A8300A Hardware Abstract Layer Header File.
 *              - Platform : Z20K14xM
 * @version   : V0.2.0
 * @date      : 23-Oct-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @Copyright : Copyright (C) 2023 Zhixin Semiconductor Ltd. All rights reserved.
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
extern "C"
{
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "spi_drv.h"
#include "BSP_PWM.h"

/** @defgroup Hal_Public_MacroDefinition
 *  @{
 */
        /* Motor1 A8300 confg*/
    
#define Z20A8300A_M1SPI_ID             SPI_ID_1
#define Z20A8300A_M1SPI_CLOCK_MODULE   CLK_SPI1
#define Z20A8300A_M1SPI_CLOCK_GATE     SYSCTRL_SPI1

#define Z20A8300A_M1SPI_PCS            SPI_SS_PCS0
#define Z20A8300A_M1SPI_PCS_PORT       PORT_D
#define Z20A8300A_M1SPI_PCS_PIN        GPIO_3
#define Z20A8300A_M1SPI_PCS_PINMUX     PTD3_SPI1_PCS0

#define Z20A8300A_M1SPI_SCK_PORT       PORT_A
#define Z20A8300A_M1SPI_SCK_PIN        GPIO_2
#define Z20A8300A_M1SPI_SCK_PINMUX     PTA2_SPI1_SCK

#define Z20A8300A_M1SPI_MOSI_PORT      PORT_D
#define Z20A8300A_M1SPI_MOSI_PIN       GPIO_2
#define Z20A8300A_M1SPI_MOSI_PINMUX    PTD2_SPI1_SOUT

#define Z20A8300A_M1SPI_MISO_PORT      PORT_A
#define Z20A8300A_M1SPI_MISO_PIN       GPIO_3
#define Z20A8300A_M1SPI_MISO_PINMUX    PTA3_SPI1_SIN

#define Z20A8300A_M1RST_PORT           PORT_D
#define Z20A8300A_M1RST_PIN            GPIO_9
#define Z20A8300A_M1RST_PINMUX         PTD9_GPIO

#define Z20A8300A_M1ENABLE_PORT        PORT_C
#define Z20A8300A_M1ENABLE_PIN         GPIO_0
#define Z20A8300A_M1ENABLE_PINMUX      PTC0_GPIO

#define Z20A8300A_M1DIAG_PORT          PORT_B
#define Z20A8300A_M1DIAG_PIN           GPIO_2
#define Z20A8300A_M1DIAG_PINMUX        PTB2_GPIO

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
void MCU_Z20A8300A_SpiInit1(void);
/**
 * @brief       MCU Z20A8300A GPIO Init
 *
 * @param[in]   none
 *
 * @return      none
 *
 */
void MCU_Z20A8300A_GpioInit1(void);
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
uint16_t MCU_SPI_SendToZ20A8300A1(uint16_t Data);
/**
 * @brief       get the data received from Z20A8300A
 *
 * @param[in]   none
 *
 * @return      uint16_t
 * @retval      receive data
 */
uint16_t MCU_SPI_ReceiveFromZ20A8300A1(void);
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
uint16_t MCU_SPI_WaitingForReceptionFromZ20A8300A1(void);
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
void Z20A8300A_SetPWMEnablePin1(uint16_t States);
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
void Z20A8300A_SetResetPin1(uint16_t States);
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
uint16_t Z20A8300A_GetDiagPinStates1(void);

/** @} end of group Hal_Public_FunctionDeclaration */

#ifdef __cplusplus
}
#endif

/** @} end of group Z20A8300A_Hal */

/** @} end of group Z20A8300A_Driver */

#endif /* Z20A8300A_HAL_H */
