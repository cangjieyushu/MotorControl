/**************************************************************************************************/
/**
 * @file      : Z20K11xM_clock.h
 * @brief     : Clock driver module header file.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (C) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#ifndef Z20K11XM_CLOCK_H
#define Z20K11XM_CLOCK_H

#include "Z20K11xM_drv.h"

/** @addtogroup  Z20K11X_Peripheral_Driver
 *  @{
 */

/** @addtogroup  Clock
 *  @{
 */

/** @defgroup Clock_Public_Types 
 *  @{
 */

/** 
 *  @brief clock source option 
 */
typedef enum
{
    CLK_SRC_NO = 0U,                     /*!< none is selected  */
    CLK_SRC_LPO32K,                      /*!< LPO32K  */
    CLK_SRC_OSC32K,                      /*!< OSC32K  */
    CLK_SRC_FIRC64M,                     /*!< FIRC64M  */
    CLK_SRC_OSC40M                       /*!< OSC40M  */ 
}CLK_Src_t;

/** 
 *  @brief system clock source option 
 */
typedef enum
{
    CLK_SYS_OSC40M = 0U,                /*!< OSC40M System Clock */
    CLK_SYS_FIRC64M                     /*!< FIRC64M System Clock */
}CLK_System_t;

/** 
 *  @brief OSC40M/OSC32K mode option 
 */
typedef enum
{
    CLK_OSC_XTAL = 0U,     /*!< crystal: OSC clock comes from crystal oscillator */
    CLK_OSC_EXT_SRC        /*!< external source: OSC clock comes from a external
                                square wave clock source */
}CLK_OscMode_t;

/** 
 *  @brief OSC40M frequency mode option 
 */
typedef enum
{
    CLK_OSC_FREQ_MODE_LOW = 0U,     /*!< OSC40M clock works in low frequency mode */
    CLK_OSC_FREQ_MODE_HIGH          /*!< OSC40M clock works in high frequency mode */
}CLK_OscFreqMode_t;

/** 
 *  @brief The action option if lock of clock is detected 
 */
typedef enum
{
    CLK_MON_INT = 0U,            /*!< Generat interrupt if loss of 
                                            clock is detected */
    CLK_MON_RST                  /*!< reset if loss of clock is detected */
}CLK_MonitorAct_t;

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
    CLK_DIV_16,                        /*!< clock divided by 16 */
}CLK_Divider_t;

typedef enum
{
    CLK_OUT_DIV_1 = 0U,                    /*!< clock divided by 1 */
    CLK_OUT_DIV_2 = 1U,                    /*!< clock divided by 2 */
    CLK_OUT_DIV_4 = 2U,                    /*!< clock divided by 4 */
    CLK_OUT_DIV_8 = 3U                     /*!< clock divided by 8 */
}CLK_OutDiv_t;

/** 
 *  @brief output clock source option 
 */
typedef enum
{
    CLK_OUT_FIRC64M = 1U,                  /*!< FIRC64M Clock */
    CLK_OUT_OSC40M = 2U,                   /*!< OSC40M Clock  */    
    CLK_OUT_SLOW = 8U,                     /*!< SLOW Clock */
    CLK_OUT_BUS = 9U,                      /*!< BUS Clock */
    CLK_OUT_CORE = 10U,                    /*!< CORE Clock */
    CLK_OUT_OSC32K = 11U,                  /*!< OSC32K Clock */
    CLK_OUT_LPO32K =12U                    /*!< LPO32K Clock */
}CLK_OutSrc_t;


/** 
 *  @brief TIM External clock source option 
 */
typedef enum
{
    CLK_TIM_PTB1 = 0U,               /*!< PTB1 pin */
    CLK_TIM_PTE1_PTA5,               /*!< PTE1/PTA5 pin */
    CLK_TIM_PTE8                     /*!< PTE8 pin*/
}CLK_TIMExtClk_t;

/** 
 *  @brief TIM ID for clock selction
 */
typedef enum
{
    CLK_TIM0_ID = 0U,               /*!< TIM0 pin */
    CLK_TIM1_ID,                    /*!< TIM1 pin */
    CLK_TIM2_ID                     /*!< TIM2 pin*/
}CLK_TIM_t;


/**
 *  @brief clock interrupt type definition
 */
typedef enum
{
    CLK_INT_OSCLOC = 0U,            /*!< OSC40M loss of clock interrupt */
    CLK_INT_FIRCLOC = 1U,           /*!< FIRC64M loss of clock interrupt */
    CLK_INT_ALL                     /*!< all interrupt */
}CLK_Int_t;

/**
 *  @brief clock module type definition
 */
typedef enum
{
    CLK_EWDT = 0x04U,               /*!< EWDT */
    CLK_STIM = 0x08U,               /*!< STIM */
    CLK_TIM0 = 0x0CU,               /*!< TIM0 */
    CLK_TIM1 = 0x10U,               /*!< TIM1 */
    CLK_TIM2 = 0x14U,               /*!< TIM2 */ 
    CLK_TDG0 = 0x18U,               /*!< TDG0 */
    CLK_CAN0 = 0x1CU,               /*!< CAN0 */
    CLK_CAN1 = 0x20U,               /*!< CAN1 */
    CLK_UART0 = 0x24U,              /*!< UART0 */
    CLK_UART1 = 0x28U,              /*!< UART1 */
    CLK_UART2 = 0x2CU,              /*!< UART2 */
    CLK_UART3 = 0x30U,              /*!< UART3 */
    CLK_SPI0 = 0x34U,               /*!< SPI0 */
    CLK_SPI1 = 0x38U,               /*!< SPI1 */
    CLK_SPI2 = 0x3CU,               /*!< SPI2 */
    CLK_I2C0 = 0x40U,               /*!< I2C0 */
    CLK_I2C1 = 0x44U,               /*!< I2C1 */
    CLK_ADC0 = 0x48U,               /*!< ADC0 */
    CLK_CMP = 0x4cU,                /*!< CMP */
    CLK_CRC = 0x50U,                /*!< CRC */
    CLK_FLASH = 0x54U,              /*!< FLASH */
    CLK_DMA = 0x58U,                /*!< DMA */
    CLK_DMAMUX = 0x5CU,             /*!< DMAMUX */
    CLK_PORTA = 0x60U,              /*!< PORTA */
    CLK_PORTB = 0x64U,              /*!< PORTB */
    CLK_PORTC = 0x68U,              /*!< PORTC */
    CLK_PORTD = 0x6cU,              /*!< PORTD */
    CLK_PORTE = 0x70U,              /*!< PORTE */

    /* below define are only used for CLK_SetClkDivider */
    CLK_CORE = 0x85U,               /*!< Core */
    CLK_BUS = 0x86U,                /*!< Bus */
    CLK_SLOW = 0x87U                /*!< Slow */       
    
}CLK_Module_t;


/** @} end of group Clock_Public_Types */

/** @defgroup Clock_Public_Constants
 *  @{
 */

/** @} end of group Clock_Public_Constants */

/** @defgroup Clock_Public_Macro
 *  @{
 */

/** @} end of group Clock_Public_Macro */

/** @defgroup Clock_Public_FunctionDeclaration
 *  @brief Clock functions declaration
 *  @{
 */

/**
 * @brief      Enable FIRC64M clock and set enablement in stop mode
 *
 * @param[in]  stopModeEn:  Enable/Disable FIRC64M in stop mode.
 *
 * @return none
 *
 */
void CLK_FIRC64MEnable(ControlState_t stopModeEn);

/**
 * @brief      Get system clock source.
 *
 * @param[in]  none.
 *
 * @return 
 *          -CLK_SYS_FIRC64M
 *          -CLK_SYS_OSC40M
 *
 */
CLK_System_t CLK_GetSysClkSrc(void);

/**
 * @brief      Disable FIRC64M clock
 *
 * @param[in]  none.
 *
 * @return none
 *
 */
void CLK_FIRC64MDisable(void);

/**
 * @brief      It is suggested to use CLK_OSC40MEnable2() instead of this 
 *             function. It Configures and enables OSC40M clock. The frequency 
 *             mode is selected according to the 'freq' parameter. However, the 
 *             selection may be not accurate.
 *
 * @param[in]  freq:  the frequency of OSC40M, unit/MHz. The value should be
 *                    between 4 and 40. If 4<= freq <= 24, CLK_OSC_FREQ_MODE_LOW
 *                    is selected for the frequency mode; if 24< freq <= 40, 
 *                    CLK_OSC_FREQ_MODE_HIGH is selected for the frequency mode.
 * @param[in]  stopModeEn:  Enable/Disable OSC40M in stop mode.
 * @param[in]  mode: select OSC mode. It selects from crystal oscillator or 
 *                   external square wave clock source.
 *
 * @note   It is suggested to use CLK_OSC40MEnable2() instead of this function.
 *             
 *
 * @return status
 *         - ERR - some error.
 *         - SUCC - successful
 *
 */
ResultStatus_t CLK_OSC40MEnable(uint32_t freq, ControlState_t stopModeEn, 
                                CLK_OscMode_t mode);

/**
 * @brief      Configure and enable OSC40M clock
 *
 * @param[in]  freqMode:  It selects the frequency mode of OSC40M
 * @param[in]  stopModeEn:  Enable/Disable OSC40M in stop mode.
 * @param[in]  mode: select OSC mode. It selects from crystal oscillator or 
 *                   external square wave clock source.

 *
 * @return status
 *         - ERR - some error.
 *         - SUCC - successful
 *
 */
ResultStatus_t CLK_OSC40MEnable2(CLK_OscFreqMode_t freqMode, 
                                 ControlState_t stopModeEn, 
                                 CLK_OscMode_t mode);

/**
 * @brief      Disable OSC40M clock
 *
 * @param[in]  none.
 *
 * @return none
 *
 */
void CLK_OSC40MDisable(void);

/**
 * @brief      Select system clock.
 *
 * @param[in]  clk: select the clock source
 *
 * @return 
 *         - SUCC: the system clock is selected successfully
 *         - ERR: fail
 * @note The selected clock source has to be ready
 *       before call this function.
 *
 */
ResultStatus_t CLK_SysClkSrc(CLK_System_t clk);

/**
 * @brief      Config and Enable OSC40M loss of clock monitor
 *
 * @param[in]  act: select the action when loss of clock is detected.
 *
 * @return none
 *
 */
void CLK_OSC40MMonitorEnable(CLK_MonitorAct_t act);

/**
 * @brief      Disable OSC40M loss of clock monitor
 *
 * @param[in]  none.
 *
 * @return none
 *
 */
void CLK_OSC40MMonitorDisable(void);

/**
 * @brief      Config and Enable FIRC64M loss of clock monitor
 *
 * @param[in]  act: select the action when loss of clock is detected.
 *
 * @return none
 *
 */
void CLK_FIRC64MMonitorEnable(CLK_MonitorAct_t act);

/**
 * @brief      Config and Enable FIRC64M loss of clock monitor
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void CLK_FIRC64MMonitorDisable(void);

/**
 * @brief      Config and Enable LPO32K clock
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void CLK_LPO32KEnable(void);

/**
 * @brief      Disable LPO32K clock
 *
 * @param[in]  none.
 *
 * @return none
 *
 */
void CLK_LPO32KDisable(void);

/**
 * @brief      Config and Enable OSC32K clock
 *
 * @param[in]  mode: select OSC mode. It selects from crystal oscillator or 
 *                   external square wave clock source.
 * @return none
 *
 */
void CLK_OSC32KEnable(CLK_OscMode_t mode);

/**
 * @brief      Disable OSC32K clock
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void CLK_OSC32KDisable(void);

/**
 * @brief      Set clock divider
 *
 * @param[in]  module: select which module clock to set divider. 
 *                     It selects from CLK_EWDT, CLK_STIM, CLK_TIM0, 
 *                     CLK_TIM1, CLK_TIM2, CLK_TDG0, CLK_CAN0, CLK_CAN1, 
 *                     CLK_UART0, CLK_UART1, CLK_UART2, CLK_UART3, 
 *                     CLK_SPI0, CLK_SPI1, CLK_SPI2, CLK_I2C0, CLK_I2C1, 
 *                     CLK_ADC0, CLK_PORTA,CLK_PORTB, CLK_PORTC, CLK_PORTD, 
 *                     CLK_PORTE CLK_CORE, CLK_BUS, CLK_SLOW
 *                     
 * @param[in] divider: clock divider
 * @return     none
 *
 */
void CLK_SetClkDivider(CLK_Module_t module, CLK_Divider_t divider);

/**
 * @brief      Select clock source for module
 *
 * @param[in]  module: select which module to set clock source.
 *                     It selects from CLK_EWDT, CLK_STIM, CLK_TIM0, CLK_TIM1,
 *                     CLK_TIM2, CLK_TDG0, CLK_CAN0, CLK_CAN1, CLK_UART0, 
 *                     CLK_UART1, CLK_UART2, CLK_UART3, CLK_SPI0, CLK_SPI1, 
 *                     CLK_SPI2, CLK_I2C0, CLK_I2C1, CLK_ADC0, CLK_PORTA,
 *                     CLK_PORTB, CLK_PORTC, CLK_PORTD, CLK_PORTE
 *                     
 * @param[in]  clockSource: select clock source
 * @note  For CAN0 CAN1, the clock source can only select from CLK_SRC_FIRC64M
 *        CLK_SRC_OSC40M,CLK_SRC_NO. 
 *        For ADC0, the clock source can only select from CLK_SRC_FIRC64M, 
 *        CLK_SRC_NO. 
 *        This function should only be called when the module is not working,
 *        otherwise, the clock source will not change.
 * @return     
 *         - SUCC
 *         - ERR: the input parameter is unreasonable.
 *
 */
ResultStatus_t CLK_ModuleSrc(CLK_Module_t module, CLK_Src_t clockSource);

/**
 * @brief      Select TIM external clock source. If TIM is configured to use
 *             external clock source, this function can select a external clock
 *             source from a pin.
 *
 * @param[in]  timId: it indicates which TIM to config
 * @param[in]  clockSrc: select the external TIM clock source
 *
 * @return     None
 *
 */
void CLK_TimExternalClkSrc(CLK_TIM_t timId, CLK_TIMExtClk_t clockSrc);

/**
 * @brief      Config and Enable clock output
 *
 * @param[in]  outSrc:  Select the clock source to be output.
 * @param[in]  divider: output clock divider
 *
 * @return none
 *
 */
void CLK_ClkOutEnable(CLK_OutSrc_t outSrc, CLK_OutDiv_t divider);

/**
 * @brief      Disable clock output
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void CLK_ClkOutDisable(void);

/**
 * @brief      get module clock frequency before divider
 *
 * @param[in]  module: select the module
 * @param[in]  oscFreq: frequency of the OSC clock
 *
 * @return     The clock frequency. If return 0, there is some error.
 *
 */
uint32_t CLK_GetModuleClkFreq(CLK_Module_t module,uint32_t oscFreq);

/**
 * @brief      Get the clock source status
 *
 * @param[in]  clockSource: it can get status of CLK_OUT_LPO32K,CLK_OUT_FIRC64M,
 *                          CLK_OUT_OSC32K,CLK_OUT_OSC40M
 *
 * @return     The clock source status
 *
 */
FlagStatus_t CLK_GetClkStatus(CLK_Src_t clockSource);

/**
 * @brief      Wait the clock source status until it is ready
 *
 * @param[in]  clockSource: the clock source to be waited
 *
 * @return     
 *             - SUCC -- the clock is ready
 *             - ERR -- time out
 *
 */
ResultStatus_t CLK_WaitClkReady(CLK_Src_t clockSource);

/**
 * @brief      install call back function
 *
 * @param[in]  intId: select the interrupt
 * @param[in]  cbFun: pointer to callback function
 *
 * @return none
 *
 */
void SCC_InstallCallBackFunc(CLK_Int_t intId,isr_cb_t * cbFun);

/**
 * @brief      Clear Interrupt status
 *
 * @param[in]  intId: select the interrupt
 *
 * @return none
 *
 */
void SCC_IntClear(CLK_Int_t intId);

/** @} end of group Clock_Public_FunctionDeclaration */

/** @} end of group Clock  */

/** @} end of group Z20K11X_Peripheral_Driver */
#endif /* Z20K11XM_CLOCK_H */
