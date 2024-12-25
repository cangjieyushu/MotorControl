/**************************************************************************************************/
/**
 * @file      : Clk_Drv.h
 * @brief     : Clk driver module header file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
#ifndef CLOCK_DRV_H
#define CLOCK_DRV_H

#include "Common_Drv.h"

/** @defgroup Public_MacroDefinition
 *  @{
 */

/** @} end of Public_MacroDefinition */

/** @defgroup Public_TypeDefinition
 *  @{
 */

/** 
 *  @brief clock source option 
 */
typedef enum
{
    CLK_NO = 0U,                            /*!< none is selected  */
    CLK_LPO96K = 1U,                        /*!< LPO96K  */
    CLK_FRO48M = 2U,                        /*!< FRO48M  */
    CLK_OSC24M = 3U,                        /*!< OSC24M  */ 
}Clk_ClockType;

/** 
 *  @brief system clock source option 
 */
typedef enum
{
    CLK_SYS_FRO48M = 1U,                /*!< FRO48M System Clock */
    CLK_SYS_OSC24M = 2U                 /*!< OSC24M System Clock */
}Clk_SystemSrcType;

/** 
 *  @brief peripheral clock source option 
 */
typedef enum
{
    CLK_PERI_CORE = 0U,        /*!< Core Clock */  
    CLK_PERI_OSC24M = 1U       /*!< OSC24M  */                     
}Clk_PeripheralSrcType;

/** 
 *  @brief OSC24M mode option 
 *  @note CLK_OSC_[SOURCE]_[FREQUENCY] = Source[3] + FreqMode[2] + Itrim[1:0]
 *        Source: The 4th bit represent the clock source property. 
 *                Internal = 0,           External = 1.
 *        FreqMode: The 3rd bit represent the clock frequency mode.
 *                Low Frequency Mode = 0, High Frequency Mode = 1.
 *        Itrim: The lower 2 bits represent the I-trim configuration. 
 *                I-trim for (Frequency = 4M)         = b00, 
 *                I-trim for (4M  < Frequency <= 12M) = b10, 
 *                I-trim for (12M < Frequency <= 16M) = b00, 
 *                I-trim for (16M < Frequency <= 24M) = b01, 
 */
typedef enum
{
    CLK_OSC_INT_24M = 0x5U,   /*!< OSC clock comes from internal crystal oscillator. 
                                   (Frequency = 24M) */
    CLK_OSC_EXT_4M  = 0x8U,   /*!< OSC clock comes from a external square wave clock source. 
                                   (Frequency = 4M) */
    CLK_OSC_EXT_4_TO_12M = 0xAU,  /*!< OSC clock comes from a external square wave clock source.
                                      (4M  < Frequency <= 12M) */
    CLK_OSC_EXT_12_TO_16M = 0xCU, /*!< OSC clock comes from a external square wave clock source.
                                      (12M < Frequency <= 16M) */
    CLK_OSC_EXT_16_TO_24M = 0xDU, /*!< OSC clock comes from a external square wave clock source.
                                      (16M < Frequency <= 24M) */
}Clk_OscModeType;

/** 
 *  @brief clock divider type 
 */
typedef enum
{
    CLK_DIV_1 = 0U,                    /*!< clock divided by 1 */
    CLK_DIV_2,                         /*!< clock divided by 2 */
    CLK_DIV_3,                         /*!< clock divided by 3 */
    CLK_DIV_4,                         /*!< clock divided by 4 */
    CLK_DIV_5,                         /*!< clock divided by 5 */
    CLK_DIV_6,                         /*!< clock divided by 6 */
    CLK_DIV_7,                         /*!< clock divided by 7 */
    CLK_DIV_8,                         /*!< clock divided by 8 */
    CLK_DIV_9,                         /*!< clock divided by 9 */
    CLK_DIV_10,                        /*!< clock divided by 10 */
    CLK_DIV_11,                        /*!< clock divided by 11 */
    CLK_DIV_12,                        /*!< clock divided by 12 */
    CLK_DIV_13,                        /*!< clock divided by 13 */
    CLK_DIV_14,                        /*!< clock divided by 14 */
    CLK_DIV_15,                        /*!< clock divided by 15 */
    CLK_DIV_16                         /*!< clock divided by 16 */
}Clk_DividerType;

typedef enum
{
    CLK_OUT_DIV_1 = 0U,                    /*!< clock divided by 1 */
    CLK_OUT_DIV_2 = 1U,                    /*!< clock divided by 2 */
    CLK_OUT_DIV_4 = 2U,                    /*!< clock divided by 4 */
    CLK_OUT_DIV_8 = 3U                     /*!< clock divided by 8 */
}Clk_OutDivType;

/** 
 *  @brief output clock source option 
 */
typedef enum
{
    CLK_OUT_DISABLE = 0U,                /*!< Disable */
    CLK_OUT_FRO48M = 1U,                 /*!< FRO48M Clock */
    CLK_OUT_OSC24M = 2U,                 /*!< OSC24M Clock  */   
    CLK_OUT_BUS = 9U,                    /*!< BUS Clock */
    CLK_OUT_CORE = 10U,                  /*!< CORE Clock */
    CLK_OUT_LPO96K = 11U,                /*!< LPO96K Clock */
    CLK_OUT_GDU_CP = 12U,                /*!< GDU CP dither Clock */
    CLK_OUT_FRO48M_ANALOG = 13U,         /*!< FRO48M Clock from analog hard */
    CLK_OUT_OSC24M_ANALOG = 14U          /*!< OSC24M Clock from analog hard */
}Clk_OutSrcType;

/**
 *  @brief clock error flag type definition
 */
typedef enum
{
    CLK_ERR_OSCLOC = 0U,             /*!< OSC24M loss of clock flag */
    CLK_ERR_FRO48MLOC = 1U           /*!< FRO48M loss of clock flag */
}Clk_ErrorType;

/**
 *  @brief clock node type definition
 */
typedef enum
{
    CLK_NODE_CORE = 0U,               /*!< Core */
    CLK_NODE_BUS = 1U,                /*!< Bus */
    CLK_NODE_UART = 2U,               /*!< UART */
    CLK_NODE_SPI = 3U                 /*!< SPI */
}Clk_ClockNodeType;

/**
 *  @brief module clock type definition
 */
typedef enum
{
    CLK_UART_CLK = 0U,         /*!< UART */
    CLK_SPI_CLK,               /*!< SPI */
    CLK_ADC_CLK,               /*!< ADC */
    CLK_WDOG_CLK,              /*!< WDOG */
    CLK_MCPWM_CLK,             /*!< MCPWM */
    CLK_CTIMER_CLK,            /*!< CTIMER */
    CLK_TDG_CLK,               /*!< TDG */
    CLK_CRC_CLK,               /*!< CRC */
    CLK_PORT_CLK,              /*!< PORT */
    CLK_CMP_CLK,               /*!< CMP */
    CLK_GDU_CLK,               /*!< GDU */
    CLK_SSTIM_CLK,             /*!< SSTIM */
    CLK_ACCEL_CLK,             /*!< ACCEL */
    CLK_FLASH_CLK,             /*!< FLASH */
    CLK_SRAM_CLK,              /*!< SRAM */
    CLK_ROM_CLK                /*!< ROM */
} Clk_ModuleType;

/** @} end of group Public_TypeDefinition */

/** @defgroup Global_VariableDeclaration
 *  @{
 */

/** @} end of group Global_VariableDeclaration */

/** @defgroup Public_FunctionDeclaration
 *  @{
 */

/**
 * @brief       Config and enable FRO48M clock.
 *
 * @param[in]   StopModeEn:  Enable/Disable FIRC48M in stop mode.
 *
 * @return      clock enable status:
 *              - COMMON_ERR  - error;
 *              - COMMON_SUCC - success.
 */
Common_ResultStatusType Clk_EnableFro48m(Common_ControlStateType StopModeEn);

/**
 * @brief       Config and enable OSC24M clock.
 *
 * @param[in]  Mode: select OSC24M work and frequency mode.
 * @param[in]  StopModeEn:  Enable/Disable OSC24M in stop mode.
 *
 * @return      clock enable status:
 *              - COMMON_ERR  - error;
 *              - COMMON_SUCC - success.
 */
Common_ResultStatusType Clk_EnableOsc24m(Clk_OscModeType Mode, 
                                         Common_ControlStateType StopModeEn);

/**
 * @brief       Select system clock.
 *
 * @param[in]   ClkSrc: select the clock source.
 *
 * @return      Select result:
 *              - COMMON_SUCC: the system clock is selected successfully;
 *              - COMMON_ERR: fail.
 * @note        The selected clock source has to be ready
 *              before call this function.
 *
 */
Common_ResultStatusType Clk_SetSysClk(Clk_SystemSrcType ClkSrc);

/**
 * @brief       Get system clock source.
 *
 * @param[in]   none.
 *
 * @return      clock source:
 *              - CLK_SYS_FIRC48M
 *              - CLK_SYS_OSC24M
 *
 */
Clk_SystemSrcType Clk_GetSysClk(void);

/**
 * @brief       Disable FIRC48M clock.
 *
 * @param[in]   none.
 *
 * @return      Result status:
 *              COMMON_SUCC - disable success.
 *              COMMON_ERR  - trying to disable current system clock.
 */
Common_ResultStatusType Clk_DisableFro48m(void);

/**
 * @brief       Disable OSC24M clock.
 *
 * @param[in]   none.
 *
 * @return      Result status:
 *              COMMON_SUCC - disable success.
 *              COMMON_ERR  - trying to disable current system clock.
 */
Common_ResultStatusType Clk_DisableOsc24m(void);

/**
 * @brief       Enable OSC24M loss of clock monitor.
 *
 * @param[in]   none.
 *
 * @return      none.
 *
 */
void Clk_EnableOsc24mMonitor(void);

/**
 * @brief       Disable OSC24M loss of clock monitor.
 *
 * @param[in]   none.
 *
 * @return      none.
 *
 */
void Clk_DisableOsc24mMonitor(void);

/**
 * @brief       Enable FRO48M loss of clock monitor.
 *
 * @param[in]   none.
 *
 * @return      none.
 *
 */
void Clk_EnableFro48mMonitor(void);

/**
 * @brief       Disable FIRC48M loss of clock monitor.
 *
 * @param[in]   none.
 *
 * @return      none.
 *
 */
void Clk_DisableFro48mMonitor(void);

/**
 * @brief       Config and Enable LPO96K clock.
 *
 * @param[in]   none.
 *
 * @return      none.
 *
 */
void Clk_EnableLpo96k(void);

/**
 * @brief       Disable LPO96K clock.
 *
 * @param[in]   none.
 *
 * @return      none.
 *
 */
void Clk_DisableLpo96k(void);

/**
 * @brief       Set clock divider of the selected node.
 *
 * @param[in]   ClockNode: select clock divider to set. It selects from
 *                      CLK_NODE_CORE, CLK_NODE_BUS, CLK_NODE_UART, CLK_NODE_SPI.
 *                     
 * @param[in]   Divider: clock divider.
 * 
 * @return      none.
 *
 */
void Clk_SetClkDivider(Clk_ClockNodeType ClockNode, Clk_DividerType Divider);

/**
 * @brief       Get clock frequency of the selected node.
 *
 * @param[in]   ClockNode: select the module. It selects from 
 *                         CLK_NODE_CORE, CLK_NODE_BUS, CLK_NODE_UART, CLK_NODE_SPI.
 * @param[in]   OscFreq: frequency of the OSC clock.
 *
 * @return      The clock frequency. If return 0, there is some error.
 *
 */
uint32 Clk_GetClkFreq(Clk_ClockNodeType ClockNode, uint32 OscFreq);

/**
 * @brief       Get the clock source status.
 *
 * @param[in]   ClkSrc: it can get status of CLK_LPO96K,CLK_FRO48M,
 *                           CLK_OSC24M.
 *
 * @return      The clock source status.
 *
 */
Common_FlagStatusType Clk_GetClkStatus(Clk_ClockType ClkSrc);

/**
 * @brief       Wait the clock source status until it is ready.
 *
 * @param[in]   ClkSrc: the clock source to be waited.
 *
 * @return      COMMON_SUCC -- the clock is ready;
 *              COMMON_ERR -- time out.
 *
 */
Common_ResultStatusType Clk_WaitClkReady(Clk_ClockType ClkSrc);

/**
 * @brief       Config and Enable clock output.
 *
 * @param[in]   OutSrc:  Select the clock source to be output.
 * @param[in]   Divider: output clock divider.
 *
 * @return      none.
 *
 */
void Clk_EnableClkOut(Clk_OutSrcType OutSrc, Clk_OutDivType Divider);

/**
 * @brief       Disable clock output.
 *
 * @param[in]   none.
 *
 * @return      none.
 *
 */
void Clk_DisableClkOut(void);

/**
 * @brief       Get clock error status.
 *
 * @param[in]   Error: select the error type.
 *
 * @return      none.
 *
 */
Common_FlagStatusType Clk_GetErrorStatus(Clk_ErrorType Error);

/**
 * @brief       Clear clock error flag.
 *
 * @param[in]   Error: select the error type.
 *
 * @return      none.
 *
 */
void Clk_ClearErrorStatus(Clk_ErrorType Error);

/**
 * @brief       Select UART clock source.
 *
 * @param[in]   PeriClk: select the clock of UART.
 *
 * @return      none.
 *
 */
void Clk_SetUartClkSrc(Clk_PeripheralSrcType PeriClk);

/**
 * @brief       Get UART clock source.
 *
 * @param[in]   none.
 *
 * @return      clock source:
 *              - CLK_PERI_CORE
 *              - CLK_PERI_OSC24M
 */
Clk_PeripheralSrcType Clk_GetUartClkSrc(void);

/**
 * @brief      Enable module clock.
 *
 * @param[in]  ModuleType: select which module to enable. 
 *                         - CLK_UART_CLK : UART module
 *                         ...
 *                         - CLK_ROM_CLK : ROM module
 *
 * @return     none
 *
 */
void Clk_EnableModule(Clk_ModuleType ModuleType);

/**
 * @brief      Disable module clock.
 *
 * @param[in]  ModuleType: select which module to disable. 
 *                         - CLK_UART_CLK : UART module
 *                         ...
 *                         - CLK_ROM_CLK : ROM module
 *
 * @return     none
 *
 */
void Clk_DisableModule(Clk_ModuleType ModuleType);

/** @} end of group Public_FunctionDeclaration */

#endif /* CLOCK_DRV_H */
