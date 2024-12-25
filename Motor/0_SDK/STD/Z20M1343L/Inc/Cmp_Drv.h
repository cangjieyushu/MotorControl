/**************************************************************************************************/
/**
 * @file      : Cmp_Drv.h
 * @brief     : CMP driver module header file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#ifndef CMP_DRV_H
#define CMP_DRV_H

#include "Common_Drv.h"

/** @defgroup Public_MacroDefinition
 *  @{
 */

/** @} end of group Public_MacroDefinition */

/** @defgroup Public_TypeDefinition
 *  @{
 */

/**
 *  @brief CMP hysteresis in high-speed mode type definition
 */
typedef enum
{
    CMP_HYST_H_NO = 0U,    /*!< hysteresis in high-speed mode: no hysteresis */
    CMP_HYST_H_21MV,       /*!< hysteresis in high-speed mode: 21mv */
    CMP_HYST_H_34MV,       /*!< hysteresis in high-speed mode: 34mv */
    CMP_HYST_H_45MV        /*!< hysteresis in high-speed mode: 45mv */
} Cmp_HystHighSpeedType;

/**
 *  @brief CMP High speed CMP PMUX select type definition
 */
typedef enum
{
    CMP_P_IN_0 = 0U           /*!< CMP_P_IN0 pin*/                               
} Cmp_InputPmuxSelectionType;
/**
 *  @brief CMP High speed CMP NMUX select type definition
 */
typedef enum
{
    CMP_N_DACOUT = 3U          /*!< CMP_N_DACOUT pin*/                            
} Cmp_InputNmuxSelectionType;
/**
 *  @brief CMP interrupt type definition
 */
typedef enum
{
    CMP_INT_RAISE = 0U,          /*!< output raising edge interrupt */   
    CMP_INT_FALL,                /*!< output falling edge interrupt */
    CMP_INT_ALL                  /*!< all interrupt */ 
} Cmp_InterruptType;

/**
 *  @brief  DAC reference voltage type definition
 */
typedef enum
{
    CMP_DAC_VREF_VDDA = 0U,      /*!< VDDA */
    CMP_DAC_VREF_VREFH           /*!< VREFH */
} Cmp_DacVrefVoltageType;

/**
 *  @brief  DAC output type definition
 */
typedef enum
{
    CMP_DAC_NOT_OUTPUT = 0U,      /*!< DAC not output */
    CMP_DAC_UNBUFFERED_OUTPUT,    /*!< DAC unbuffered output */
    CMP_DAC_BUFFERED_OUTPUT       /*!< DAC buffered output */
} Cmp_DacOutputType;

/**
 *  @brief CMP configuration structure type definition
 */
typedef struct
{

    Cmp_HystHighSpeedType Hysteresis;              /*!< hysteresis */  
    Cmp_InputPmuxSelectionType PositiveInput;          /*!< positive input selection */    
    Cmp_InputNmuxSelectionType NegativeInput;          /*!< Negative input selection */
    Common_ControlStateType InvertEnable;          /*!< whether invert cout
                                                    - ENABLE: invert
                                                    - DISABLE: not invert  */
    Common_LevelType SpeedMode;           /*! High-speed cmp speed mode
                                        - LEVEL_LOW low bias current, comparator speed is low 
                                        - LEVEL_HIGH low bias current, comparator speed is high*/
} Cmp_ConfigType;

/** @} end of group Public_TypeDefinition */

/** @defgroup Global_VariableDeclaration
 *  @{
 */

/** @} end of group Global_VariableDeclaration */

/** @defgroup Public_FunctionDeclaration
 *  @{
 */

/**
 * @brief      Initialize CMP
 *
 * @param[in]  ConfigPtr: the configuration parameters.
 *
 * @return     none
 *
 */
void Cmp_Init(const Cmp_ConfigType *ConfigPtr);

/**
 * @brief      Config filter parameters
 *
 * @param[in]  Count: the consecutive sample count number that agree the output 
 *                  value to be changed. The range is 1 - 255. If it is 0, the 
 *                  filter is bypassed.
 *
 * @return     None
 *
 */
void Cmp_ConfigFilterCount(uint32 Count);

/**
 * @brief      Set DAC reference voltage
 *
 * @param[in]  Vref: Select the reference voltage
 *                     - CMP_DAC_VREF_VDDA
 *                     - CMP_DAC_VREF_VREFH
 *
 * @return     None
 *
 */
void Cmp_SetDacRefVoltage(Cmp_DacVrefVoltageType Vref);

/**
 * @brief      Set DAC output type
 *
 * @param[in]  OutputType: DAC output type
 *                          - CMP_DAC_NOT_OUTPUT
 *                          - CMP_DAC_UNBUFFERED_OUTPUT
 *                          - CMP_DAC_BUFFERED_OUTPUT
 *
 * @return     None
 *
 */   
void Cmp_SetDacOutputType(Cmp_DacOutputType OutputType);

/**
 * @brief      Enable DAC 
 *
 * @param[in]  None
 *
 * @return     None
 *
 */

void Cmp_EnableDac(void);

/**
 * @brief      Disable DAC
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void Cmp_DisableDac(void);

/**
 * @brief      set DAC output value
 *
 * @param[in]  Data: the data to be converted. The range is 0 - 0xFF.
 *
 * @return     None
 *
 */
void Cmp_SetDacValue(uint8 Data);

/**
 * @brief      Enable CMP
 *
 * @param[in]  none
 *
 * @return     none
 *
 */ 
void Cmp_EnableCmp(void);

/**
 * @brief      Disable CMP
 *
 * @param[in]  none
 *
 * @return     none
 *
 */ 
void Cmp_DisableCmp(void);

/**
 * @brief      Get CMP output value
 *
 * @param[in]  none
 *
 * @return     CMP Out Voltage Level
 * @retval     COMMON_LEVEL_LOW: - low level
 * @retval     COMMON_LEVEL_HIGH: - high level
 *
 */
Common_LevelType Cmp_GetOutput(void);

/**
 * @brief      Install callback function
 *
 * @param[in]  IntType: select interrupt type
 * @param[in]  CallbackFun: indicate callback function
 *
 * @return    none
 * @note      CMP_INT_ALL is invalid as input
 */ 
void Cmp_InstallCallBackFunc(Cmp_InterruptType IntType, Isr_CbFuncType * CallbackFun);

/**
 * @brief      Mask/Unmask interrupt
 *
 * @param[in]  IntType: select interrupt type
 *                        - CMP_INT_RAISE
 *                        - CMP_INT_FALL
 *                        - CMP_INT_ALL
 * @param[in]  IntMask: 
 *                        - MASK
 *                        - UNMASK
 *
 * @return    none
 *
 */
void Cmp_SetIntMask(Cmp_InterruptType IntType, Common_IntMaskType IntMask);

/**
 * @brief      Clear interrupt
 *
 * @param[in]  IntType: select interrupt type
 *                        - CMP_INT_RAISE
 *                        - CMP_INT_FALL
 *                        - CMP_INT_ALL
 *
 * @return    none
 *
 */ 
void Cmp_ClearInt(Cmp_InterruptType IntType);

/** @} end of group Public_FunctionDeclaration */

#endif /* CMP_DRV_H */
