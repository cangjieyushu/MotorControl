/**************************************************************************************************/
/** 
 * @file      : Z20A8300A_Hal.c
 * @brief     : Z20A8300A Hardware Abstract Layer Source File.
 *              - Platform : Z20K14xM
 * @version   : V0.2.0
 * @date      : 23-Oct-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @Copyright : Copyright (C) 2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
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

#include "Z20A8300A_Hal.h"

/** @defgroup Hal_Private_MacroDefinition
 *  @{
 */

/** @} end of Hal_Private_MacroDefinition */

/** @defgroup Hal_Private_TypeDefinition
 *  @{
 */

/** @} end of group Hal_Private_TypeDefinition */

/** @defgroup Hal_Global_VariableDefinition
 *  @{
 */

/** @} end of group Hal_Global_VariableDefinition */

/** @defgroup Hal_Private_VariableDefinition
 *  @{
 */

/** @} end of group Hal_Private_VariableDefinition */

/** @defgroup Hal_Private_FunctionDeclaration
 *  @{
 */

/** @} end of group Hal_Private_FunctionDeclaration */

/** @defgroup Hal_Private_FunctionDefinition
 *  @{
 */

/** @} end of group Hal_Private_FunctionDefinition */

/** @defgroup Hal_Public_FunctionDefinition
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
void MCU_Z20A8300A_SpiInit1(void)
{
    /* spi master initial configuration */
    SPI_Config_t SpiMasterCfgStruct =
    {
        SPI_MODE_MASTER,                      /* spi mode */
        16U,                                  /* data frame size */
        SPI_CLK_PHASE_SECOND,                 /* clock phase */
        SPI_CLK_INACTIVE_HIGH,                /* clock polarity */
        SPI_TMOD_TR,                          /* transfer mode */
        40U,                                  /* clock Divider */
        2U,                                   /* transmit FIFO threshold level */
        2U                                    /* receive FIFO threshold level */
    };
    /* spi clock */
    PORT_PinmuxConfig(Z20A8300A_M1SPI_SCK_PORT, Z20A8300A_M1SPI_SCK_PIN, Z20A8300A_M1SPI_SCK_PINMUX);
    /* spi master rx */
    PORT_PinmuxConfig(Z20A8300A_M1SPI_MISO_PORT, Z20A8300A_M1SPI_MISO_PIN, Z20A8300A_M1SPI_MISO_PINMUX);
    /* spi master tx */
    PORT_PinmuxConfig(Z20A8300A_M1SPI_MOSI_PORT, Z20A8300A_M1SPI_MOSI_PIN, Z20A8300A_M1SPI_MOSI_PINMUX);
    /* spi pcs0 */
    PORT_PinmuxConfig(Z20A8300A_M1SPI_PCS_PORT, Z20A8300A_M1SPI_PCS_PIN, Z20A8300A_M1SPI_PCS_PINMUX);
    /* choose osc clock as function clock of spi */
    while(ERR == CLK_ModuleSrc(Z20A8300A_M1SPI_CLOCK_MODULE, CLK_SRC_OSC40M))
    {}
    /* set divide ratio of spi's function clock*/
    CLK_SetClkDivider(Z20A8300A_M1SPI_CLOCK_MODULE, CLK_DIV_1);
    /* enable clock for spi */
    SYSCTRL_EnableModule(Z20A8300A_M1SPI_CLOCK_GATE);
    
    /* initiate spi */
    SPI_Init(Z20A8300A_M1SPI_ID, &SpiMasterCfgStruct);
    /* Pull down the CS signal to select slave */
    SPI_SelectSlave(Z20A8300A_M1SPI_ID, Z20A8300A_M1SPI_PCS);
    /* enable spi */
    SPI_Enable(Z20A8300A_M1SPI_ID);
}
    
/**
 * @brief       MCU Z20A8300A GPIO Init
 *
 * @param[in]   none
 *
 * @return      none
 *
 */
void MCU_Z20A8300A_GpioInit1(void)
{
    PORT_PinmuxConfig(Z20A8300A_M1ENABLE_PORT, Z20A8300A_M1ENABLE_PIN, Z20A8300A_M1ENABLE_PINMUX);
    GPIO_SetPinDir(Z20A8300A_M1ENABLE_PORT, Z20A8300A_M1ENABLE_PIN, GPIO_OUTPUT);
    GPIO_WritePinOutput(Z20A8300A_M1ENABLE_PORT, Z20A8300A_M1ENABLE_PIN, GPIO_HIGH);

    PORT_PinmuxConfig(Z20A8300A_M1RST_PORT, Z20A8300A_M1RST_PIN, Z20A8300A_M1RST_PINMUX);
    GPIO_SetPinDir(Z20A8300A_M1RST_PORT, Z20A8300A_M1RST_PIN, GPIO_OUTPUT);
    GPIO_WritePinOutput(Z20A8300A_M1RST_PORT, Z20A8300A_M1RST_PIN, GPIO_HIGH);
}

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
uint16_t MCU_SPI_SendToZ20A8300A1(uint16_t Data)
{
    uint16_t Status = 1U;
    if(RESET == SPI_GetStatus(Z20A8300A_M1SPI_ID, SPI_STATUS_TFNF))
    {
        Status = 0U;
    }
    SPI_SendData(Z20A8300A_M1SPI_ID, Data);

    return Status;
}

/**
 * @brief       get the data received from Z20A8300A
 *
 * @param[in]   none
 *
 * @return      uint16_t
 * @retval      receive data
 */
uint16_t MCU_SPI_ReceiveFromZ20A8300A1(void)
{
    return (uint16_t)(SPI_ReceiveData(Z20A8300A_M1SPI_ID));
}

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
uint16_t MCU_SPI_WaitingForReceptionFromZ20A8300A1(void)
{
    uint32_t LocalCnt = 0U;
    uint16_t Status = 1U;

    while(RESET == SPI_GetStatus(Z20A8300A_M1SPI_ID, SPI_STATUS_RFNE))
    { 
        if(LocalCnt > 0xFFU)
        {
           Status = 0U;
           break;
        }
        LocalCnt++;
    }

    return Status;

}

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
void Z20A8300A_SetPWMEnablePin1(uint16_t States)
{
    if(1U == States)
    {
        GPIO_WritePinOutput(Z20A8300A_M1ENABLE_PORT, Z20A8300A_M1ENABLE_PIN, GPIO_HIGH);
    }
    else
    {
        GPIO_WritePinOutput(Z20A8300A_M1ENABLE_PORT, Z20A8300A_M1ENABLE_PIN, GPIO_LOW);
    }
}

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
void Z20A8300A_SetResetPin1(uint16_t States)
{
    if(1U == States)
    {
        GPIO_WritePinOutput(Z20A8300A_M1RST_PORT, Z20A8300A_M1RST_PIN, GPIO_HIGH);
    }
    else
    {
        GPIO_WritePinOutput(Z20A8300A_M1RST_PORT, Z20A8300A_M1RST_PIN, GPIO_LOW);
    }
}

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
uint16_t Z20A8300A_GetDiagPinStates1(void)
{
    return (uint16_t)(GPIO_ReadPinLevel(HAL_FAULTIN_PORT, HAL_FAULTIN_PIN));
}


/** @} end of group Hal_Public_FunctionDefinition */

#ifdef __cplusplus
}
#endif

/** @} end of group Z20A8300A_Hal */

/** @} end of group Z20A8300A_Driver */
