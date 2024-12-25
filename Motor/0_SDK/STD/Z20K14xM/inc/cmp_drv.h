/**************************************************************************************************/
/**
 * @file     cmp_drv.h
 * @brief    CMP driver module header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#ifndef CMP_DRV_H
#define CMP_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  CMP
 *  @{
 */

/** @defgroup CMP_Public_Types 
 *  @{
 */

/**
 *  @brief CMP trigger type definition
 */
typedef enum
{
    CMP_SW_TRIGGER = 0U,      /*!< software trigger */
    CMP_HW_TRIGGER            /*!< hardware trigger by trigger signal from TMU*/
} CMP_Trigger_t;

/**
 *  @brief CMP speed type definition
 */
typedef enum
{
    CMP_SPEED_LOW = 0U,        /*!< speed: low */
    CMP_SPEED_HIGH             /*!< speed: high */
} CMP_Speed_t;

/**
 *  @brief CMP hysteresis in low-speed mode type definition
 */
typedef enum
{
    CMP_HYST_L_NO = 0U,    /*!< hysteresis in low-speed mode: no hysteresis */
    CMP_HYST_L_16MV,       /*!< hysteresis in low-speed mode: 16mv */
    CMP_HYST_L_25MV,       /*!< hysteresis in low-speed mode: 25mv */
    CMP_HYST_L_32MV        /*!< hysteresis in low-speed mode: 32mv */
} CMP_HystLowSpeed_t;

/**
 *  @brief CMP hysteresis in high-speed mode type definition
 */
typedef enum
{
    CMP_HYST_H_NO = 0U,    /*!< hysteresis in high-speed mode: no hysteresis */
    CMP_HYST_H_21MV,       /*!< hysteresis in high-speed mode: 21mv */
    CMP_HYST_H_34MV,       /*!< hysteresis in high-speed mode: 34mv */
    CMP_HYST_H_45MV        /*!< hysteresis in high-speed mode: 45mv */
} CMP_HystHighSpeed_t;
   
/**
 *  @brief CMP output selection type definition
 */
typedef enum
{ 
    CMP_OUT_FILTER_SAMPLE = 0U,  /*!< output after filter/sample */
    CMP_OUT_WINDOW               /*!< output after window */
} CMP_Output_t;

/**
 *  @brief CMP input selection type definition
 */
typedef enum
{
    CMP_IN_0 = 0U,           /*!< CMP0_IN0 pin*/
    CMP_IN_1,                /*!< CMP0_IN1 pin*/
    CMP_IN_2,                /*!< CMP0_IN2 pin */
    CMP_IN_3,                /*!< CMP0_IN3 pin */
    CMP_IN_4,                /*!< CMP0_IN4 pin*/ 
    CMP_IN_5,                /*!< CMP0_IN5 pin*/
    CMP_IN_6,                /*!< CMP0_IN6 pin*/  
    CMP_IN_7,                /*!< CMP0_IN7 pin*/
    CMP_IN_8,                /*!< CMP0_IN8 pin*/   
    CMP_IN_9,                /*!< CMP0_IN9 pin*/
    CMP_IN_10,               /*!< CMP0_IN10 pin*/    
    CMP_IN_11,               /*!< CMP0_IN11 pin*/
    CMP_IN_12,               /*!< CMP0_IN12 pin*/    
    CMP_IN_DACOUT = 15U      /*!< DAC Output */
} CMP_In_t;

/**
 *  @brief CMP output level when window is closed type definition
 */
typedef enum
{
    CMP_WIN_OUT_LVL_LAST = 0U,    /*!< COUTA hold the value of the last sample */
    CMP_WIN_OUT_LVL_0,           /*!< COUTA is 0 when window is closed */
    CMP_WIN_OUT_LVL_1            /*!< COUTA is 1 when window is closed */
} CMP_WinOutLvl_t;

/**
 *  @brief CMP working mode type definition
 */
typedef enum
{
    CMP_MODE_BASIC = 0U,     /*!< basic mode: the analog output is not handled by 
                                  window/filter/sample */
    CMP_MODE_WINDOW,         /*!< window mode: the analog output is processed 
                                  by window signal from TMU */
    CMP_MODE_FILTER,         /*!< filter mode: the analog output is processed 
                                  by filter*/
    CMP_MODE_SAMPLE,         /*!< sample mode: the analog output is sampled by 
                                  signal from TMU */
    CMP_MODE_WINDOW_FILTER   /*!< window + filter mode: the analog output is 
                                  first processed by window signal from TMU,
                                  then it is processed by filter */
} CMP_Mode_t;

/**
 *  @brief CMP interrupt/DMA request option type definition
 */
typedef enum
{
    CMP_REQ_INT = 0U,   /*!< generate interrupt request on rising/falling edge
                             of output */
    CMP_REQ_DMA         /*!< generate DMA request on rising/falling edge of output*/
} CMP_Request_t;

/**
 *  @brief CMP interrupt type definition
 */
typedef enum
{
    CMP_INT_RAISE = 0U,          /*!< output raising edge interrupt */   
    CMP_INT_FALL,                /*!< output falling edge interrupt */
    CMP_INT_ALL                  /*!< all interrupt */ 
} CMP_Int_t;

/**
 *  @brief  DAC reference voltage type definition
 */
typedef enum
{
    CMP_DAC_VREF_VDDA = 0U,      /*!< VDDA */
    CMP_DAC_VREF_VREFH           /*!< VREFH */
} CMP_DACVref_t;

/**
 *  @brief  Filter sample count type definition
 */
typedef enum
{
    CMP_FILTER_BYPASSED = 0U,                   /*!< Filter is bypassed */
    CMP_FILTER_1_CONSECUTIVE_SAMPLE,            /*!< 1 consecutive sample must agree */
    CMP_FILTER_3_CONSECUTIVE_SAMPLE,            /*!< 3 consecutive sample must agree */
    CMP_FILTER_4_CONSECUTIVE_SAMPLE,            /*!< 4 consecutive sample must agree */
    CMP_FILTER_5_CONSECUTIVE_SAMPLE,            /*!< 5 consecutive sample must agree */
    CMP_FILTER_6_CONSECUTIVE_SAMPLE,            /*!< 6 consecutive sample must agree */
    CMP_FILTER_7_CONSECUTIVE_SAMPLE,            /*!< 7 consecutive sample must agree */
    CMP_FILTER_8_CONSECUTIVE_SAMPLE             /*!< 8 consecutive sample must agree */
} CMP_FilterSampleCount_t;


/**
 *  @brief CMP configuration structure type definition
 */
typedef struct
{
    CMP_Speed_t speed;            /*!< speed */
    union
    {
        CMP_HystLowSpeed_t ls;
        CMP_HystHighSpeed_t hs;      
    } hyst;                        /*!< hysteresis */  
    CMP_In_t pIn;                 /*!< positive input selection */    
    CMP_In_t nIn;                 /*!< Negative input selection */
    CMP_Mode_t mode;              /*!< select working mode */
    CMP_Request_t req;            /*!< generate Interrupt or DMA request on 
                                       rising/falling edge of output */
    ControlState_t invertEn;      /*!< whether invert cout
                                       - ENABLE: invert
                                       - DISABLE: not invert  */
    ControlState_t outToPad;      /*!< whether output to pad
                                       - ENABLE: output to pad
                                       - DISABLE: do not output to pad  */
    ControlState_t stopReqEn;     /*!< whether generate interrupt/DMA in stop
                                       mode */
} CMP_Config_t;



/** @} end of group CMP_Public_Types */

/** @defgroup CMP_Public_Constants
 *  @{
 */

/** @} end of group CMP_Public_Constants */

/** @defgroup CMP_Public_Macro
 *  @{
 */

/** @} end of group CMP_Public_Macro */

/** @defgroup CMP_Public_FunctionDeclaration
 *  @brief CMP functions declaration
 *  @{
 */

/**
 * @brief      Initialize CMP
 *
 * @param[in]  config: the configuration parameters.
 *                  if config->mode == CMP_MODE_WINDOW or CMP_MODE_WINDOW_FILTER,
 *                  CMP_WindowConfig() need to be called to config window para.
 *                  if config->mode == CMP_MODE_FILTER or CMP_MODE_WINDOW_FILTER,
 *                  CMP_FilterConfig() need to be called to config filter para.
 *
 * @return     none
 *
 */
void CMP_Init(const CMP_Config_t *config);

/**
 * @brief      Config filter parameters
 *
 * @param[in]  count: the consecutive sample count number that agree the output 
 *                  value to be changed. The range is 1 - 7. If it is 0, the 
 *                  filter is bypassed.
 * @param[in]  period: the sampling period in bus clock of the output filter.
 *                     The range is 1-0xff. If it is 0, filter is bypassed
 *
 * @return     None
 *
 */
void CMP_FilterConfig(CMP_FilterSampleCount_t count, uint8_t period);

/**
 * @brief      Config window mode parameter
 *
 * @param[in]  closedLvl: Select the output level when window is closed
 *
 * @return     None
 *
 */ 
void CMP_WindowConfig(CMP_WinOutLvl_t closedLvl);

/**
 * @brief      select the output 
 *
 * @param[in]  out: select the output position
 *                    - CMP_OUT_FILTER_SAMPLE
 *                    - CMP_OUT_WINDOW
 *
 * @return     None
 *
 */
void CMP_SelectOutput(CMP_Output_t out);

/**
 * @brief      Set DAC reference voltage
 *
 * @param[in]  vref: Select the reference voltage
 *                     - CMP_DAC_VREF_VDDA
 *                     - CMP_DAC_VREF_VREFH
 *
 * @return     None
 *
 */
void CMP_DacSetRefVoltage(CMP_DACVref_t vref);
/**
 * @brief      DAC buffer control
 *
 * @param[in]  cmd: ENABLE or DISABLE
 *
 * @return     None
 *
 */   
void CMP_DacBufferControl(ControlState_t cmd);

/**
 * @brief      Enable DAC 
 *
 * @param[in]  None
 *
 * @return     None
 *
 */

void CMP_DacEnable(void);

/**
 * @brief      Disable DAC
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void CMP_DacDisable(void);

/**
 * @brief      set DAC output value
 *
 * @param[in]  data: the data to be converted. The range is 0 - 0xFF.
 *
 * @return     None
 *
 */
void CMP_DacSetValue(uint8_t data);

/**
 * @brief      Trigger CMP
 *
 * @param[in]  type: Select CMP Trigger Type 
 *                     - CMP_SW_TRIGGER
 *                     - CMP_HW_TRIGGER
 *
 * @return     none
 *
 */ 
void CMP_Trigger(CMP_Trigger_t type);

/**
 * @brief      Clear CMP trigger
 *
 * @param[in]  none
 *
 * @return     none
 *
 */ 
void CMP_TriggerClear(void);

/**
 * @brief      Get CMP output value
 *
 * @param[in]  none
 *
 * @return     CMP Out Voltage Level
 *             0: - low level
 *             1: - high level
 *
 */
Level_t CMP_GetOutput(void);

/**
 * @brief      Install callback function
 *
 * @param[in]  intType: select interrrupt type
 * @param[in]  cbFun: indicate callback function
 *
 * @return    none
 *
 */ 
void CMP_InstallCallBackFunc(CMP_Int_t intType, isr_cb_t * cbFun);

/**
 * @brief      Mask/Unmask interrupt
 *
 * @param[in]  intType: select interrrupt type
 *                        - CMP_INT_RAISE
 *                        - CMP_INT_FALL
 *                        - CMP_INT_ALL
 * @param[in]  intMask: 
 *                        - MASK
 *                        - UNMASK
 *
 * @return    none
 *
 */
void CMP_IntMask(CMP_Int_t intType, IntMask_t intMask);

/**
 * @brief      Clear interrupt
 *
 * @param[in]  intType: select interrrupt type
 *                        - CMP_INT_RAISE
 *                        - CMP_INT_FALL
 *                        - CMP_INT_ALL
 *
 * @return    none
 *
 */
void CMP_IntClear(CMP_Int_t intType);

/** @} end of group CMP_Public_FunctionDeclaration */

/** @} end of group CMP  */

/** @} end of group Z20K14XM_Peripheral_Driver */
#endif /* CMP_DRV_H */
