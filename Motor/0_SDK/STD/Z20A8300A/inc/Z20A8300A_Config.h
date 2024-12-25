/**************************************************************************************************/
/** 
 * @file      : Z20A8300A_Config.h
 * @brief     : Z20A8300A Config Register API Header File.
 *                 - Platform: Z20A8300A
 * @version   : V0.7.0
 * @date      : September-2022
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @Copyright : Copyright (c) 2022-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
#ifndef Z20A8300A_CONFIG_H
#define Z20A8300A_CONFIG_H

/** @addtogroup Z20A8300A_Driver
 *  @{
 */

/** @addtogroup Z20A8300A_Config
 *  @brief Z20A8300A Configuration Register API.
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "Z20A8300A_If.h"

/** @defgroup Config_Public_MacroDefinition
 *  @{
 */

/** @} end of Config_Public_MacroDefinition */

/** @defgroup Config_Public_TypeDefinition
 *  @{
 */

/** @} end of group Config_Public_TypeDefinition */

/** @defgroup Config_Global_VariableDeclaration
 *  @{
 */

/** @} end of group Config_Global_VariableDeclaration */

/** @defgroup Config_Public_FunctionDeclaration
 *  @{
 */

/**
 * @brief      Get dead time
 *             Before using this function,Z20A8300A_ReadDataRegister
 *             should be called to get the latest data.
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 *
 * @return     DeadTime
 * @retval     DT_0nS~DT_3150nS,interval 50ns
 *
 */
Z20A8300A_Config0_DeadTimeType Z20A8300A_Config_GetDeadTime(Z20A8300A_IfType *IfPtr);

/**
 * @brief      Get Over Temperature Threshold
 *             Before using this function,Z20A8300A_ReadDataRegister
 *             should be called to get the latest data.
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 *
 * @return     OverTempeThreshold
 * @retval     OTS_165_DEG
 * @retval     OTS_155_DEG
 * @retval     OTS_145_DEG
 * @retval     OTS_135_DEG
 *
 */
Z20A8300A_Config0_OverTempeThresholdType Z20A8300A_Config_GetOverTempeThreshold(
                                         Z20A8300A_IfType *IfPtr);

/**
 * @brief      Get Vbb Over Voltage Threshold
 *             Before using this function,Z20A8300A_ReadDataRegister
 *             should be called to get the latest data.
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 *
 * @return     VbbOverVoltageThreshold
 * @retval     VBOV_35V
 * @retval     VBOV_18V
 *
 */
Z20A8300A_Config0_VbbOverVoltageThresholdType Z20A8300A_Config_GetVbbOverVoltageThreshold(
                                              Z20A8300A_IfType *IfPtr);

/** 
 * @brief      Set dead time
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  DeadTime: DT_0nS ~ DT_3150nS,interval 50ns
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Config_SetDeadTime(Z20A8300A_IfType *IfPtr,
                                                     Z20A8300A_Config0_DeadTimeType DeadTime);

/**
 * @brief      Set Over Tempe Threshold
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  Ots: Over Temperature Threshold Type:
 *                  - OTS_165_DEG
 *                  - OTS_155_DEG
 *                  - OTS_145_DEG
 *                  - OTS_135_DEG
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Config_SetOverTempeThreshold(Z20A8300A_IfType *IfPtr,
                        Z20A8300A_Config0_OverTempeThresholdType Ots);

/**
 * @brief      Set Vbb Over Voltage Threshold
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  Vbov: Vbb Over Voltage Threshold Type:
 *                   - VBOV_35V
 *                   - VBOV_18V
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Config_SetVbbOverVoltageThreshold(Z20A8300A_IfType *IfPtr,
                        Z20A8300A_Config0_VbbOverVoltageThresholdType Vbov);

/**
 * @brief      Get Over Current Blanking Time
 *             Before using this function,Z20A8300A_ReadDataRegister
 *             should be called to get the latest data.
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 *
 * @return     OverCurrentBlankingTime
 * @retval     TCB_0ns~TCB_1550nS,interval 50ns
 *
 */
Z20A8300A_Config1_OverCurrentBlankingTimeType Z20A8300A_Config_GetOverCurrentBlankingTime(
                                              Z20A8300A_IfType *IfPtr);

/**
 * @brief      Get Over Current Threshold
 *             Before using this function,Z20A8300A_ReadDataRegister
 *             should be called to get the latest data.
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 *
 * @return     OverCurrentThreshold
 * @retval     OCT_300mV~OCT_4800mV,interval 300mV
 *
 */
Z20A8300A_Config1_OverCurrentThresholdType Z20A8300A_Config_GetOverCurrentThreshold(
                                           Z20A8300A_IfType *IfPtr);

/**
 * @brief      Set Over Current Blanking Time
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  Tcb: TCB_0ns ~ TCB_1550nS,interval 50ns
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Config_SetOverCurrentBlankingTime(Z20A8300A_IfType *IfPtr,
                        Z20A8300A_Config1_OverCurrentBlankingTimeType Tcb);

/**
 * @brief      Set Over Current Threshold
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  Oct: OCT_300mV ~ OCT_4800mV,interval 300mV
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Config_SetOverCurrentThreshold(Z20A8300A_IfType *IfPtr,
                        Z20A8300A_Config1_OverCurrentThresholdType Oct);

/**
 * @brief      Get Vgs Vds Blanking Time
 *             Before using this function,Z20A8300A_ReadDataRegister
 *             should be called to get the latest data.
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 *
 * @return     VgsVdsBlankingTime
 * @retval     TVB_0nS~TVB_3150nS,interval 50nS
 *
 */
Z20A8300A_Config2_VgsVdsBlankingTimeType Z20A8300A_Config_GetVgsVdsBlankingTime(
                                         Z20A8300A_IfType *IfPtr);

/**
 * @brief      Get Charge Pump Frequency
 *             Before using this function,Z20A8300A_ReadDataRegister
 *             should be called to get the latest data.
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 *
 * @return     ChargePumpFrequency
 * @retval     FCP_100KHz~FCP_400KHz,interval 100KHz
 *
 */
Z20A8300A_Config2_ChargePumpFrequencyType Z20A8300A_Config_GetChargePumpFrequency(
                                          Z20A8300A_IfType *IfPtr);

/**
 * @brief      Get Charge Pump Mode
 *             Before using this function,Z20A8300A_ReadDataRegister
 *             should be called to get the latest data.
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 *
 * @return     ChargePumpMode
 * @retval     CPM_REGULATE_TO_GROUND
 * @retval     CPM_REGULATE_TO_BATTERY
 *
 */
Z20A8300A_Config2_ChargePumpModeType Z20A8300A_Config_GetChargePumpMode(
                                     Z20A8300A_IfType *IfPtr);

/**
 * @brief      Set Vgs Vds Blanking Time
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  Tvb: TVB_0nS ~ TVB_3150nS,interval 50nS
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Config_SetVgsVdsBlankingTime(Z20A8300A_IfType *IfPtr,
                        Z20A8300A_Config2_VgsVdsBlankingTimeType Tvb);

/**
 * @brief      Set Charge Pump Frequency
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  Fcp: FCP_100KHz ~ FCP_400KHz,interval 100KHz
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Config_SetChargePumpFrequency(Z20A8300A_IfType *IfPtr,
                        Z20A8300A_Config2_ChargePumpFrequencyType Fcp);

/**
 * @brief      Set Charge Pump Mode
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  Cpm: Charge Pump Mode Type:
 *                  - CPM_REGULATE_TO_GROUND
 *                  - CPM_REGULATE_TO_BATTERY
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Config_SetChargePumpMode(Z20A8300A_IfType *IfPtr,
                        Z20A8300A_Config2_ChargePumpModeType Cpm);

/**
 * @brief      Get Vds Low Side Threshold
 *             Before using this function,Z20A8300A_ReadDataRegister
 *             should be called to get the latest data.
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 *
 * @return     VdsLowSideThreshold
 * @retval     VDS_THRESHOLD_60mV~VDS_THRESHOLD_1920mV,interval 60mV
 *
 */
Z20A8300A_Config_VdsThresholdType Z20A8300A_Config_GetVdsLowSideThreshold(Z20A8300A_IfType *IfPtr);

/**
 * @brief      Get Bootstrap Management Enable states
 *             Before using this function,Z20A8300A_ReadDataRegister
 *             should be called to get the latest data.
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 *
 * @return     BootstrapManagementEnable
 * @retval     DISABLE
 * @retval     ENABLE
 *
 */
Z20A8300A_ContorlStateType Z20A8300A_Config_GetBootstrapManagementEnable(
                           Z20A8300A_IfType *IfPtr);

/**
 * @brief      Get Source Peak Current
 *             Before using this function,Z20A8300A_ReadDataRegister
 *             should be called to get the latest data.
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 *
 * @return     SourcePeakCurrent
 * @retval     SR_30mA~SR_210mA or SR_DISABLE,interval 30mA
 *
 */
Z20A8300A_Config3_SourcePeakCurrentType Z20A8300A_Config_GetSourcePeakCurrent(
                                        Z20A8300A_IfType *IfPtr);

/**
 * @brief      Set Vds Low Side Threshold
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  VdsLs: VDS_THRESHOLD_60mV ~ VDS_THRESHOLD_1920mV,interval 60mV
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Config_SetVdsLowSideThreshold(Z20A8300A_IfType *IfPtr,
                        Z20A8300A_Config_VdsThresholdType VdsLs);

/**
 * @brief      Set Bootstrap Management Enable
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  Ebm: Bootstrap Management Enable Type:
 *                  - DISABLE
 *                  - ENABLE
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Config_SetBootstrapManagementEnable(Z20A8300A_IfType *IfPtr,
                        Z20A8300A_ContorlStateType Ebm);

/**
 * @brief      Set Source Peak Current
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  SR: SR_30mA ~ SR_210mA or SR_DISABLE,interval 30mA
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Config_SetSourcePeakCurrent(Z20A8300A_IfType *IfPtr,
                        Z20A8300A_Config3_SourcePeakCurrentType SR);

/**
 * @brief      Get Vds High Side Threshold
 *             Before using this function,Z20A8300A_ReadDataRegister
 *             should be called to get the latest data.
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 *
 * @return     VdsHighSideThreshold
 * @retval     VDS_THRESHOLD_60mV~VDS_THRESHOLD_1920mV,interval 60mV
 *
 */
Z20A8300A_Config_VdsThresholdType Z20A8300A_Config_GetVdsHighSideThreshold(Z20A8300A_IfType *IfPtr);

/**
 * @brief      Get Sensor Amplifier Offset
 *             Before using this function,Z20A8300A_ReadDataRegister
 *             should be called to get the latest data.
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 *
 * @return     SensorAmplifierOffset
 * @retval     SAO_0mV~SAO_2500mV,See the definition of Z20A8300A_Config4_SensorAmplifierOffsetType
 *
 */
Z20A8300A_Config4_SensorAmplifierOffsetType Z20A8300A_Config_GetSensorAmplifierOffset(
                                            Z20A8300A_IfType *IfPtr);

/**
 * @brief      Set Vds High Side Threshold
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  VdsHs: VDS_THRESHOLD_60mV ~ VDS_THRESHOLD_1920mV,interval 60mV
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Config_SetVdsHighSideThreshold(Z20A8300A_IfType *IfPtr,
                        Z20A8300A_Config_VdsThresholdType VdsHs);

/**
 * @brief      Set Sensor Amplifier Offset
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  Sao: SAO_0mV ~ SAO_2500mV,
 *                  See the definition of Z20A8300A_Config4_SensorAmplifierOffsetType
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Config_SetSensorAmplifierOffset(Z20A8300A_IfType *IfPtr,
                        Z20A8300A_Config4_SensorAmplifierOffsetType Sao);

/**
 * @brief      Get SensorA Gain
 *             Before using this function,Z20A8300A_ReadDataRegister
 *             should be called to get the latest data.
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 *
 * @return     SensorAGain
 * @retval     SENSOR_GAIN_10~SENSOR_GAIN_40,interval 5;or SENSOR_GAIN_50
 *
 */
Z20A8300A_Config5_SensorGainType Z20A8300A_Config_GetSensorAGain(Z20A8300A_IfType *IfPtr);

/**
 * @brief      Get SensorB Gain
 *             Before using this function,Z20A8300A_ReadDataRegister
 *             should be called to get the latest data.
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 *
 * @return     SensorBGain
 * @retval     SENSOR_GAIN_10~SENSOR_GAIN_40,interval 5;or SENSOR_GAIN_50
 *
 */
Z20A8300A_Config5_SensorGainType Z20A8300A_Config_GetSensorBGain(Z20A8300A_IfType *IfPtr);

/**
 * @brief      Get SensorC Gain
 *             Before using this function,Z20A8300A_ReadDataRegister
 *             should be called to get the latest data.
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 *
 * @return     SensorCGain
 * @retval     SENSOR_GAIN_10~SENSOR_GAIN_40,interval 5;or SENSOR_GAIN_50
 *
 */
Z20A8300A_Config5_SensorGainType Z20A8300A_Config_GetSensorCGain(Z20A8300A_IfType *IfPtr);

/**
 * @brief      Set SensorA Gain
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  Sag: SENSOR_GAIN_10 ~ SENSOR_GAIN_40,interval 5;or SENSOR_GAIN_50
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Config_SetSensorAGain(Z20A8300A_IfType *IfPtr,
                                                        Z20A8300A_Config5_SensorGainType Sag);

/**
 * @brief      Set SensorB Gain
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  Sbg: SENSOR_GAIN_10 ~ SENSOR_GAIN_40,interval 5;or SENSOR_GAIN_50
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Config_SetSensorBGain(Z20A8300A_IfType *IfPtr,
                                                        Z20A8300A_Config5_SensorGainType Sbg);

/**
 * @brief      Set SensorC Gain
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  Scg: SENSOR_GAIN_10 ~ SENSOR_GAIN_40,interval 5;or SENSOR_GAIN_50
 * 
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Config_SetSensorCGain(Z20A8300A_IfType *IfPtr,
                                                        Z20A8300A_Config5_SensorGainType Scg);

/**
 * @brief      Disable Trickle Charge Pump
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Config_DisableTrickleChargePump(Z20A8300A_IfType *IfPtr);

/** @} end of group Config_Public_FunctionDeclaration */

#ifdef __cplusplus
}
#endif

/** @} end of group Z20A8300A_Config */

/** @} end of group Z20A8300A_Driver */

#endif /* Z20A8300A_CFG_H */
