/**************************************************************************************************/
/**
 * @file     clock_drv.h
 * @brief    Clock driver module header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#ifndef CLOCK_DRV_H
#define CLOCK_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
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
    CLK_SRC_NO = 0U,                   /*!< none is selected  */
    CLK_SRC_LPO32K = 1U,               /*!< LPO32K  */
    CLK_SRC_OSC32K = 2U,               /*!< OSC32K  */
    CLK_SRC_FIRC64M = 3U,              /*!< FIRC64M  */
    CLK_SRC_OSC40M = 4U,               /*!< OSC40M  */ 
    CLK_SRC_PLL = 5U,                  /*!< PLL  */
    CLK_SRC_SLOW = 6U                  /*!< SLOW CLOCK */   
}CLK_Src_t;

/** 
 *  @brief system clock source option 
 */
typedef enum
{
    CLK_SYS_FIRC64M = 1U,              /*!< FIRC64M System Clock */
    CLK_SYS_OSC40M = 2U,               /*!< OSC40M System Clock */
    CLK_SYS_PLL = 3U,                  /*!< PLL System Clock */
}CLK_System_t;

/** 
 *  @brief OSC40M/OSC32K mode option 
 */
typedef enum
{
    CLK_OSC_XTAL = 0U,                 /*!< Crystal: OSC clock comes from crystal oscillator */
    CLK_OSC_EXT_SRC                    /*!< external source: OSC clock comes from a external 
                                            square wave clock source */
}CLK_OscMode_t;

/** 
 *  @brief OSC40M frequency mode option 
 */
typedef enum
{
    CLK_OSC_FREQ_MODE_LOW = 0U,        /*!< OSC40M clock works in low frequency mode */
    CLK_OSC_FREQ_MODE_HIGH             /*!< OSC40M clock works in high frequency mode */
}CLK_OscFreqMode_t;

/** 
 *  @brief The action option if lock of clock is detected 
 */
typedef enum
{
    CLK_MON_INT = 0U,                  /*!< Generate interrupt if loss of clock is detected */
    CLK_MON_RST                        /*!< reset if loss of clock is detected */
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
    CLK_DIV_16                         /*!< clock divided by 16 */
}CLK_Divider_t;

typedef enum
{
    CLK_OUT_DIV_1 = 0U,                /*!< clock divided by 1 */
    CLK_OUT_DIV_2 = 1U,                /*!< clock divided by 2 */
    CLK_OUT_DIV_4 = 2U,                /*!< clock divided by 4 */
    CLK_OUT_DIV_8 = 3U                 /*!< clock divided by 8 */
}CLK_OutDiv_t;

/** 
 *  @brief output clock source option 
 */
typedef enum
{
    CLK_OUT_FIRC64M = 1U,              /*!< FIRC64M Clock */
    CLK_OUT_OSC40M = 2U,               /*!< OSC40M Clock  */    
    CLK_OUT_PLL = 3U,                  /*!< PLL Clock  */    
    CLK_OUT_SLOW = 8U,                 /*!< SLOW Clock */
    CLK_OUT_BUS = 9U,                  /*!< BUS Clock */
    CLK_OUT_CORE = 10U,                /*!< CORE Clock */
    CLK_OUT_OSC32K = 11U,              /*!< OSC32K Clock */
    CLK_OUT_LPO32K = 12U               /*!< LPO32K Clock */
}CLK_OutSrc_t;

/** 
 *  @brief PLL reference clock selection
 */
typedef enum
{
    PLL_FIRC64M_CLK = 0U,              /*!< PLL select FIRC as reference clock */
    PLL_OSC_CLK = 1U                   /*!< PLL select OSC as reference clock */
}CLK_PLLRefClk_t;


/** 
 *  @brief PLL post-divider type definition.
 */
typedef enum
{
    PLL_PRE_DIV_VALUE_1    = 0U,       /*!< PLL pre divider value is 1 */
    PLL_PRE_DIV_VALUE_2    = 1U,       /*!< PLL pre divider value is 2 */
    PLL_PRE_DIV_VALUE_4    = 2U        /*!< PLL pre divider value is 4 */
}CLK_PLLPreDiv_t;

/** 
 *  @brief PLL post-divider type definition.
 */
typedef enum
{
    PLL_POST_DIV_VALUE_6    = 3U,      /*!< PLL post divider value is 6 */
    PLL_POST_DIV_VALUE_8    = 4U,      /*!< PLL post divider value is 8 */
    PLL_POST_DIV_VALUE_10   = 5U,      /*!< PLL post divider value is 10 */
    PLL_POST_DIV_VALUE_12   = 6U,      /*!< PLL post divider value is 12 */
    PLL_POST_DIV_VALUE_14   = 7U       /*!< PLL post divider value is 14 */
}CLK_PLLPostDiv_t;

/** 
 *  @brief PLL pre-scaler type definition
 */
typedef enum
{
    PLL_SCALER_VALUE_1 = 0U,            /*!< PLL pre-scaler value is 1 */
    PLL_SCALER_VALUE_2 = 1U             /*!< PLL pre-scaler value is 2 */
}CLK_PLLPreScaler_t;

/** 
 *  @brief PLL configuration parameters definition
 */
typedef struct
{
    CLK_PLLPreDiv_t pllPreDivider;      /*!< PLL pre-divider */
    CLK_PLLPostDiv_t pllPostDivider;    /*!< PLL post-divider */
    uint32_t pllMultiplier;             /*!< PLL multiplier, range from 8 to 255 */
    CLK_PLLRefClk_t pllRefClock;        /*!< PLL reference clock */
    CLK_PLLPreScaler_t pllPreScaler;    /*!< PLL pre-scaler */
}CLK_PLLConfig_t;

/**
 *  @brief clock interrupt type definition
 */
typedef enum
{
    CLK_INT_OSCLOC = 0U,                /*!< OSC40M loss of clock interrupt */
    CLK_INT_FIRCLOC = 1U,               /*!< FIRC64M loss of clock interrupt */
    CLK_INT_ALL                         /*!< all interrupt */
}CLK_Int_t;

/**
 *  @brief clock module type definition
 */
typedef enum
{   
    CLK_WDOG = 0x00U,                   /*!< WDOG */
    CLK_EWDT = 0x04U,                   /*!< EWDT */
    CLK_STIM = 0x08U,                   /*!< STIM */
    CLK_TIM0 = 0x0CU,                   /*!< TIM0 */
    CLK_TIM1 = 0x10U,                   /*!< TIM1 */
    CLK_TIM2 = 0x14U,                   /*!< TIM2 */
    CLK_TIM3 = 0x18U,                   /*!< TIM3 */
    CLK_MCPWM0 = 0x1CU,                 /*!< MCPWM0 */
    CLK_MCPWM1 = 0x20U,                 /*!< MCPWM1 */
    CLK_TDG0 = 0x24U,                   /*!< TDG0 */
    CLK_TDG1 = 0x28U,                   /*!< TDG1 */
    CLK_CAN0 = 0x2CU,                   /*!< CAN0 */
    CLK_CAN1 = 0x30U,                   /*!< CAN1 */
    CLK_CAN2 = 0x34U,                   /*!< CAN2 */
    CLK_CAN3 = 0x38U,                   /*!< CAN3 */
    CLK_CAN4 = 0x3CU,                   /*!< CAN4 */
    CLK_CAN5 = 0x40U,                   /*!< CAN5 */
    CLK_CAN6 = 0x44U,                   /*!< CAN6 */
    CLK_CAN7 = 0x48U,                   /*!< CAN7 */
    CLK_UART0 = 0x4CU,                  /*!< UART0 */
    CLK_UART1 = 0x50U,                  /*!< UART1 */
    CLK_UART2 = 0x54U,                  /*!< UART2 */
    CLK_UART3 = 0x58U,                  /*!< UART3 */
    CLK_UART4 = 0x5CU,                  /*!< UART4 */
    CLK_UART5 = 0x60U,                  /*!< UART5 */
    CLK_SPI0 = 0x64U,                   /*!< SPI0 */
    CLK_SPI1 = 0x68U,                   /*!< SPI1 */
    CLK_SPI2 = 0x6cU,                   /*!< SPI2 */
    CLK_SPI3 = 0x70U,                   /*!< SPI3 */
    CLK_I2C0 = 0x74U,                   /*!< I2C0 */    
    CLK_I2C1 = 0x78U,                   /*!< I2C1 */ 
    CLK_I2S0 = 0x7CU,                   /*!< I2S0 */
    CLK_I2S1 = 0x80U,                   /*!< I2S1 */
    CLK_ADC0 = 0x88U,                   /*!< ADC0 */
    CLK_ADC1 = 0x8CU,                   /*!< ADC1 */
    CLK_CMP = 0x90U,                    /*!< CMP0 */
    CLK_CRC = 0x94U,                    /*!< CRC */
    CLK_AES = 0x98U,                    /*!< AES */
    CLK_TRNG = 0x9CU,                   /*!< TRNG */
    CLK_FLASH = 0xA0U,                  /*!< FLASH */
    CLK_DMA = 0xA8U,                    /*!< DMA */
    CLK_DMAMUX = 0xACU,                 /*!< DMAMUX */
    CLK_PORTA = 0xB0U,                  /*!< PORTA */
    CLK_PORTB = 0xB4U,                  /*!< PORTB */
    CLK_PORTC = 0xB8U,                  /*!< PORTC */
    CLK_PORTD = 0xBCU,                  /*!< PORTD */
    CLK_PORTE = 0xC0U,                  /*!< PORTE */
    CLK_TMU = 0xC4U,                    /*!< TMU */
    CLK_REGFILE = 0xC8U,                /*!< REGFILE */
    CLK_SMPU = 0xCCU,                   /*!< SMPU */
    CLK_GPIO = 0xD0U,                   /*!< GPIO */
    /* below definations are only used for CLK_SetClkDivider */
    CLK_CORE = 0x85U,                   /*!< Core */
    CLK_BUS = 0x86U,                    /*!< Bus */
    CLK_SLOW = 0x87U                    /*!< Slow */
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

/** @} end of group Clock_Private_Functions */

/** @defgroup Clock_Public_FunctionDeclaration
 *  @{
 */

/**
 * @brief      Config and enable FIRC64M clock
 *
 * @param[in]  stopModeEn:  Enable/Disable FIRC64M in stop mode
 *                              -ENABLE
 *                              -DISABLE
 *
 * @return status
 *         - ERR - some error.
 *         - SUCC - successful
 *
 */
ResultStatus_t CLK_FIRC64MEnable(ControlState_t stopModeEn);

/**
 * @brief      Config and enable PLL clock
 *
 * @param[in]  stopModeEn:  Enable/Disable PLL in stop mode.
 *                              -ENABLE
 *                              -DISABLE
 *
 * @return status
 *         - ERR - some error.
 *         - SUCC - successful
 *
 */
ResultStatus_t CLK_PLLEnable(ControlState_t stopModeEn);

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
ResultStatus_t CLK_OSC40MEnable(CLK_OscFreqMode_t freqMode, 
                                 ControlState_t stopModeEn, 
                                 CLK_OscMode_t mode);

/**
 * @brief      Select system clock.
 *
 * @param[in]  clk: select the clock source
 *                  -CLK_SYS_OSC40M
 *                  -CLK_SYS_PLL
 *
 * @return  ret:
 *        -SUCC: the system clock is selected successfully
 *        -ERR: fail
 * @note The selected clock source has to be ready
 *       before call this function.
 *
 */
ResultStatus_t CLK_SysClkSrc(CLK_System_t clk);

/**
 * @brief      Get system clock source.
 *
 * @param[in]  none.
 *
 * @return  ret:
 *          -CLK_SYS_FIRC64M
 *          -CLK_SYS_OSC40M
 *          -CLK_SYS_PLL
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
 * @brief      Disable PLL clock
 *
 * @param[in]  none.
 *
 * @return none
 *
 */
void CLK_PLLDisable(void);

/**
 * @brief      Select PLL reference clock
 *
 * @param[in]  pllRefClk: PLL reference clock
 *                              -PLL_OSC_CLK
 *
 * @return none
 *
 */
void CLK_PLLRefClockSelect(CLK_PLLRefClk_t pllRefClk);

/**
 * @brief      Get PLL output frequency
 *
 * @param[in]  oscFreq: oscillator frequency when PLL uses OSC as reference clock
 *
 * @return     PLL output frequency.
 *
 */
uint32_t CLK_GetPLLFreq(uint32_t oscFreq);

/**
 * @brief      Set PLL output clock configuration
 *
 * @param[in]  pllConfig: pointer to the PLL configure struct
 *
 * @return  none
 *
 * @note    According to the following formula to configure the desired PLL out frequency:
 *
 *           pllOutFreq = refClock * mult * preScaler / (postDivEnum*preDivEnum)
 *
 *           1. 80M PLL output configuration(use OSC40M as clock reference)
 *              CLK_PLLConfig_t PLLOSC40MSet80M =
 *              {
 *                  .pllPreDivider = PLL_PRE_DIV_VALUE_4,         
 *                  .pllPostDivider = PLL_POST_DIV_VALUE_12,        
 *                  .pllMultiplier = 48,                           
 *                  .pllRefClock = PLL_OSC_CLK,                  
 *                  .pllPreScaler = PLL_SCALER_VALUE_2,       
 *              };
 *
 *           2. 120M PLL output configuration(use OSC40M as clock reference)
 *              CLK_PLLConfig_t PLLOSC40MSet120M =
 *              {
 *                  .pllPreDivider = PLL_PRE_DIV_VALUE_4,              
 *                  .pllPostDivider = PLL_POST_DIV_VALUE_8,            
 *                  .pllMultiplier = 48,                            
 *                  .pllRefClock = PLL_OSC_CLK,                  
 *                  .pllPreScaler = PLL_SCALER_VALUE_2,             
 *              };
 *
 */
void CLK_PLLConfig(CLK_PLLConfig_t *pllConfig);

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
 * @brief      Config and Enable OSC40M loss of clock monitor
 *
 * @param[in]  act: select the action when loss of clock is detected.
 *                  -CLK_MON_INT
 *                  -CLK_MON_RST
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
 *                  -CLK_MON_INT
 *                  -CLK_MON_RST
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
 * @brief      Config and Enable OSC32K clock
 *
 * @param[in]  mode:  Select internal/external mode.
 *                    -CLK_OSC_XTAL
 *                    -CLK_OSC_EXT_SRC
 *
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
 *                     
 * @param[in] divider: Select the clock divider: CLK_DIV_1...CLK_DIV_16.
 * @return     none
 *
 */
void CLK_SetClkDivider(CLK_Module_t module, CLK_Divider_t divider);

/**
 * @brief      Select clock source for module
 *
 * @param[in]  module: select which module to set clock source.
 *                     
 * @param[in]  clockSource: select clock source
 *                          -CLK_SRC_NO
 *                          -CLK_SRC_LPO32K
 *                          -CLK_SRC_OSC32K
 *                          -CLK_SRC_FIRC64M
 *                          -CLK_SRC_OSC40M
 *                          -CLK_SRC_PLL
 * @note  for CAN0 CAN1, the clock source can only select from CLK_SRC_OSC40M,
 *         CLK_SRC_NO. other values will be ignored.
 * @return  res:
 *         - SUCC
 *         - ERR: the input parameter is unreasonable
 *
 */
ResultStatus_t CLK_ModuleSrc(CLK_Module_t module, CLK_Src_t clockSource);

/**
 * @brief      get module clock frequency before divider
 *
 * @param[in]  module: select the module
 * @param[in]  oscFreq: frequency of the OSC clock
 *
 * @return     freq: The clock frequency. If return 0, there is some error.
 *
 */
uint32_t CLK_GetModuleClkFreq(CLK_Module_t module,uint32_t oscFreq);

/**
 * @brief      Get the clock source status
 *
 * @param[in]  clockSource: clock source
 *                              -CLK_SRC_NO
 *                              -CLK_SRC_LPO32K
 *                              -CLK_SRC_OSC32K
 *                              -CLK_SRC_OSC40M
 *                              -CLK_SRC_PLL
 *
 * @return     bitStatus: The clock source status
 *
 */
FlagStatus_t CLK_GetClkStatus(CLK_Src_t clockSource);

/**
 * @brief      Wait the clock source status until it is ready
 *
 * @param[in]  clockSource: the clock source to be waited
 *                              -CLK_SRC_NO
 *                              -CLK_SRC_LPO32K
 *                              -CLK_SRC_OSC32K
 *                              -CLK_SRC_FIRC64M
 *                              -CLK_SRC_OSC40M
 *                              -CLK_SRC_PLL
 *
 * @return   retVal:
              -SUCC -- the clock is ready
 *            -ERR -- time out
 *
 */
ResultStatus_t CLK_WaitClkReady(CLK_Src_t clockSource);

/**
 * @brief      Config and Enable clock output
 *
 * @param[in]  outSrc:  Select the clock source to be output.
 *                          -CLK_OUT_FIRC64M
 *                          -CLK_OUT_OSC40M
 *                          -CLK_OUT_PLL
 *                          -CLK_OUT_SLOW
 *                          -CLK_OUT_BUS
 *                          -CLK_OUT_CORE
 *                          -CLK_OUT_OSC32K
 *                          -CLK_OUT_LPO32K
 * @param[in]  divider: output clock divider
 *                          -CLK_OUT_DIV_1
 *                          -CLK_OUT_DIV_2
 *                          -CLK_OUT_DIV_4
 *                          -CLK_OUT_DIV_8
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
 * @brief      install call back function
 *
 * @param[in]  intId: select the interrupt
 *                      -CLK_INT_OSCLOC
 *                      -CLK_INT_FIRCLOC
 *                      -CLK_INT_ALL
 * @param[in]  cbFun: pointer to callback function
 *
 * @return none
 *
 */
void CLK_InstallCallBackFunc(CLK_Int_t intId,isr_cb_t * cbFun);

/**
 * @brief      Clear Interrupt status
 *
 * @param[in]  intId: select the interrupt
 *                      -CLK_INT_OSCLOC
 *                      -CLK_INT_FIRCLOC
 *                      -CLK_INT_ALL
 *
 * @return none
 *
 */
void CLK_IntClear(CLK_Int_t intId);

/** @} end of group Clock_Public_FunctionDeclaration */

/** @} end of group Clock  */

/** @} end of group Z20K14XM_Peripheral_Driver */
#endif /* CLOCK_DRV_H */
