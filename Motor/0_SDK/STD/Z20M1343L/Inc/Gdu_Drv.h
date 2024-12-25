/**************************************************************************************************/
/**
 * @file      : Gdu_Drv.h
 * @brief     : Gdu driver module header file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#ifndef GDU_DRV_H
#define GDU_DRV_H

#include "Common_Drv.h"

/** @defgroup Public_MacroDefinition
 *  @{
 */

/** @} end of group Public_MacroDefinition */

/** @defgroup Public_TypeDefinition 
 *  @{
 */
/**
 *  @brief Gdu fault type definition
 */
typedef enum
{
    GDU_RECOVER_AUTOMATICALLY = 0U,/*!< Driver&predriver automatically recovered when fault removed*/
    GDU_RECOVER_MANUAL             /*!< Driver&predriver recovered when fault IRQ is cleared. */
} Gdu_FaultRecoverType;

/**
 *  @brief Gdu fault type definition
 */
typedef enum
{
    GDU_FAULT_VCP_UV = 0U,     /*!< Charge pump output voltage undervoltage fault. */
    GDU_FAULT_VSD_OV,          /*!< driver supply voltage overvoltage fault. */
    GDU_FAULT_VDS_LS1,         /*!< low side driver 1 VDS diagnosis fault. */
    GDU_FAULT_VDS_LS2,         /*!< low side driver 2 VDS diagnosis fault. */
    GDU_FAULT_VDS_LS3,         /*!< low side driver 3 VDS diagnosis fault. */
    GDU_FAULT_VDS_HS1,         /*!< high side driver 1 VDS diagnosis fault. */
    GDU_FAULT_VDS_HS2,         /*!< high side driver 2 VDS diagnosis fault. */
    GDU_FAULT_VDS_HS3,         /*!< high side driver 3 VDS diagnosis fault. */
    GDU_FAULT_ALL              /*!< All fault. */
} Gdu_FaultType;

/**
 *  @brief Gdu bridge driver type definition
 */
typedef enum
{
    GDU_BRIDGE_DRIVER_LS1 = 0U,    /*!< low side driver 1 */
    GDU_BRIDGE_DRIVER_LS2,         /*!< low side driver 2 */
    GDU_BRIDGE_DRIVER_LS3,         /*!< low side driver 3 */
    GDU_BRIDGE_DRIVER_HS1,         /*!< high side driver 1 */
    GDU_BRIDGE_DRIVER_HS2,         /*!< high side driver 2 */
    GDU_BRIDGE_DRIVER_HS3          /*!< high side driver 3 */
} Gdu_BridgeDriverType;

/**
 *  @brief Gdu bridge control mode type definition
 */
typedef enum
{
    GDU_DRIVER_INTERNAL_REGISTER = 0U,    /*!< Driver controled by internal register */
    GDU_DRIVER_EXTERNAL_PWM               /*!< Driver controled by external PWM */
} Gdu_DriverModeType;

/**
 *  @brief Gdu driver shutdown definition
 */
typedef enum
{
    GDU_DRIVER_SHUTDOWN_ALL = 0U,    /*!< All shutdown, all bridges shutdown */
    GDU_DRIVER_SHUTDOWN_LOCAL        /*!< Local shutdown, only local bridge will be shut down */
} Gdu_DriverShutdownType;

/**
 *  @brief Gdu cross conduction protection time type definition
 */
typedef enum
{
    GDU_CCP_TIME_200ns = 0U,     /*!< 0.2us,calculate at 50MHz */
    GDU_CCP_TIME_400ns,          /*!< 0.4us,calculate at 50MHz */
    GDU_CCP_TIME_800ns,          /*!< 0.8us,calculate at 50MHz */
    GDU_CCP_TIME_1600ns          /*!< 1.6us,calculate at 50MHz */
} Gdu_CcpTimeType;

/**
 *  @brief Gdu cross conduction protection time multiplier type definition
 */
typedef enum
{
    GDU_CCP_MULTIPLIER_1 = 0U,     /*!< CCP time value is multiplied by 1 */
    GDU_CCP_MULTIPLIER_2,          /*!< CCP time value is multiplied by 2 */
    GDU_CCP_MULTIPLIER_4,          /*!< CCP time value is multiplied by 4 */
    GDU_CCP_MULTIPLIER_8           /*!< CCP time value is multiplied by 8 */
} Gdu_CcpMultiplierType;

/**
 *  @brief Gdu voltage threshold for VDS monitor type definition
 */
typedef enum
{
    GDU_VDS_THRESHOLD_250mv = 0U,    /*!< 0.25V */
    GDU_VDS_THRESHOLD_500mv,         /*!< 0.5V */
    GDU_VDS_THRESHOLD_750mv,         /*!< 0.75V */
    GDU_VDS_THRESHOLD_1000mv,        /*!< 1.0V */
    GDU_VDS_THRESHOLD_1250mv,        /*!< 1.25V */
    GDU_VDS_THRESHOLD_1500mv,        /*!< 1.5V */
    GDU_VDS_THRESHOLD_1750mv,        /*!< 1.75V */
    GDU_VDS_THRESHOLD_2000mv         /*!< 2.0V */
} Gdu_VDSThresholdType;

/**
 *  @brief Gdu delay measure timer channel select type definition
 */
typedef enum
{
    GDU_DLY_MEASURE_DISABLE = 0U,    /*!< Measure timer disabled */
    GDU_DLY_MEASURE_LS1,             /*!< HB1 LS select, measure LS1 on/off delay time */
    GDU_DLY_MEASURE_LS2,             /*!< HB2 LS select, measure LS2 on/off delay time */
    GDU_DLY_MEASURE_LS3,             /*!< HB3 LS select, measure LS3 on/off delay time */
    GDU_DLY_MEASURE_HS1 = 5U,        /*!< HB1 HS select, measure HS1 on/off delay time */
    GDU_DLY_MEASURE_HS2,             /*!< HB2 HS select, measure HS2 on/off delay time */
    GDU_DLY_MEASURE_HS3              /*!< HB3 HS select, measure HS3 on/off delay time */
} Gdu_MeasureChannelType;

/**
 *  @brief Gdu delay measure timer direction select type definition
 */
typedef enum
{
    GDU_DLY_MEASURE_TURN_OFF = 0U,   /*!< Turn off, measure turn off delay time */
    GDU_DLY_MEASURE_TURN_ON          /*!< Turn on, measure turn on delay time */
} Gdu_MeasureDirectionType;

/**
 *  @brief Gdu VSD over voltage filter time type definition
 */
typedef enum
{
    GDU_VSD_OV_FILTER_10 = 0U,    /*!< 10us,calculate at 50MHz */
    GDU_VSD_OV_FILTER_20,         /*!< 20us,calculate at 50MHz */
    GDU_VSD_OV_FILTER_40,         /*!< 40us,calculate at 50MHz */
    GDU_VSD_OV_FILTER_80          /*!< 70us,calculate at 50MHz */
} Gdu_VsdOvFilterTimeType;

/**
 *  @brief Gdu VCP under voltage filter time type definition
 */
typedef enum
{
    GDU_VCP_UV_FILTER_4 = 0U,     /*!< 4us,calculate at 50MHz */
    GDU_VCP_UV_FILTER_8,          /*!< 8us,calculate at 50MHz */
    GDU_VCP_UV_FILTER_16,         /*!< 16us,calculate at 50MHz */
    GDU_VCP_UV_FILTER_32          /*!< 32us,calculate at 50MHz */
} Gdu_VcpUvFilterTimeType;

/**
 *  @brief Gdu low/high side drivers VDS monitor filter/blanking time type definition
 */
typedef enum
{
    GDU_VDS_FILTER_BLANK_1 = 0U,  /*!< 1us,calculate at 50MHz */
    GDU_VDS_FILTER_BLANK_2,       /*!< 2us,calculate at 50MHz */
    GDU_VDS_FILTER_BLANK_4,       /*!< 4us,calculate at 50MHz */
    GDU_VDS_FILTER_BLANK_8        /*!< 8us,calculate at 50MHz */
} Gdu_VdsFilterBlankTimeType;


/**
 *  @brief Gdu bridge driver configuration structure type definition
 */
typedef struct
{
    Common_ControlStateType DriverEnable;        /*!< Driver enable */ 
    Gdu_DriverModeType DriverMode;        /*!< Driver control mode select */
    Common_ControlStateType DriverControlOn;     /*!< Driver controled by internal register on */
    Common_ControlStateType DiagnosisCurrentEn;  /*!< Diagnosis current source enable */
    Common_ControlStateType VdsEnable;           /*!< VDS enable */
    Gdu_DriverShutdownType DriverShutdown;/*!< Driver shutdown when VDS(overcurrent) fault */
} Gdu_BridgeDriverConfigType;

/**
 *  @brief Gdu cross conduction protection configuration structure type definition
 */
typedef struct
{
    Gdu_CcpTimeType CcpTime;  /*!< Min cross conduction protection time setting, calculate at 50MHz*/ 
    Gdu_CcpMultiplierType CcpMultiplier;/*!< Multiplier for cross conduction protection time setting*/
    Common_ControlStateType CcpBridge1Disable; /*!< Bridge1 cross conduction protection disable */
    Common_ControlStateType CcpBridge2Disable; /*!< Bridge2 cross conduction protection disable */
    Common_ControlStateType CcpBridge3Disable; /*!< Bridge3 cross conduction protection disable */
} Gdu_CcpConfigType;

/**
 *  @brief Gdu filter/blanking time configuration structure type definition
 */
typedef struct
{
    Gdu_MeasureChannelType MeasureChannel;       /*!< Delay measure timer channel select */ 
    Gdu_MeasureDirectionType MeasureDirection;   /*!< Delay measure timer turn on/ off select */
} Gdu_DelayMeasureConfigType;

/**
 *  @brief Gdu filter/blanking time configuration structure type definition
 */
typedef struct
{
    Gdu_VdsFilterBlankTimeType VdsBlankTime;       /*!< VDS blanking time */ 
    Gdu_VdsFilterBlankTimeType VdsFilterTimeLow;   /*!< Low side VDS filter time */
    Gdu_VdsFilterBlankTimeType VdsFilterTimeHigh;  /*!< High side VDS filter time */
    Gdu_VcpUvFilterTimeType VcpUvFilterTime;       /*!< VCP under voltage filter time */
    Gdu_VsdOvFilterTimeType VsdOvFilterTime;       /*!< VSD over voltage filter time */
} Gdu_FilterBlankConfigType;

/**
 *  @brief Gdu charge pump configuration structure type definition
 */
typedef struct
{
    uint8 ClockDitherTHL;       /*!< Charge pump clock dither lower boundary */ 
    uint8 ClockDitherTHH;       /*!< Charge pump clock dither upper boundary */
    Common_ControlStateType ChargePumpEn;  /*!< Charge pump enable */
} Gdu_ChargePumpConfigType;

/**
 *  @brief Gdu Init structure type definition
 */
typedef struct
{
    Gdu_FaultRecoverType VCPRecover;
    Gdu_FaultRecoverType VSDRecover;
    Gdu_FaultRecoverType HLRecover; 
    Gdu_VDSThresholdType Threshold;
    Common_ControlStateType Shutdown;
    Gdu_DelayMeasureConfigType * DelayMeasureConfig;
    Gdu_FilterBlankConfigType * FilterBlankConfig;
    Gdu_ChargePumpConfigType * ChargePumpConfig;     
    Gdu_CcpConfigType * CcpConfig;
    Gdu_BridgeDriverConfigType * DriverConfig;
} Gdu_InitConfigType;
/** @} end of group Public_TypeDefinition */

/** @defgroup Global_VariableDeclaration
 *  @{
 */

/** @} end of group Global_VariableDeclaration */

/** @defgroup Public_FunctionDeclaration
 *  @{
 */

/**
 * @brief      Configurate Charge Pump Function
 *
 * @param[in]  ChargePumpConfig: Pointer to a charge pump configuration structure.
 *
 * @return     None
 *
 */
void Gdu_ConfigChargePump(const Gdu_ChargePumpConfigType * ChargePumpConfig);

/**
 * @brief      Configurate Filter/Blank Time Function
 *
 * @param[in]  FilterBlankConfig: Pointer to a filter/blank time configuration structure.
 *
 * @return     None
 *
 */
void Gdu_ConfigFilterBlank(const Gdu_FilterBlankConfigType * FilterBlankConfig);

/**
 * @brief      Configurate Delay Measure Function
 *
 * @param[in]  DelayMeasureConfig: Pointer to a delay measure configuration structure.
 *
 * @return     None
 *
 */
void Gdu_ConfigDelayMeasure(const Gdu_DelayMeasureConfigType * DelayMeasureConfig);

/**
 * @brief      Delay Measure Restart Function
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void Gdu_RestartDelayMeasure(void);

/**
 * @brief      Get Delay Measure Result Function
 *
 * @param[out] Result: 12-bit delay measure timer result.
 *
 * @return     Result Status:
 *              - COMMON_SUCC: measurement is complete
 *              - COMMON_ERR: measurement is not complete
 */
Common_ResultStatusType Gdu_GetDelayMeasureResult(uint16 * Result);

/**
 * @brief      Set Voltage threshold for VDS monitor Function
 *
 * @param[in]  Threshold: Voltage threshold for VDS monitor.
 *              - GDU_VDS_THRESHOLD_250mv
 *              - GDU_VDS_THRESHOLD_500mv
 *              - GDU_VDS_THRESHOLD_750mv
 *              - GDU_VDS_THRESHOLD_1000mv
 *              - GDU_VDS_THRESHOLD_1250mv
 *              - GDU_VDS_THRESHOLD_1500mv
 *              - GDU_VDS_THRESHOLD_1750mv
 *              - GDU_VDS_THRESHOLD_2000mv
 *
 * @return     None
 *
 */
void Gdu_SetVdsThreshold(Gdu_VDSThresholdType Threshold);

/**
 * @brief      Configurate Cross Conduction Protection Function
 *
 * @param[in]  CcpConfig: Pointer to a cross conduction protection configuration structure.
 *
 * @return     None
 *
 */
void Gdu_ConfigCcp(const Gdu_CcpConfigType * CcpConfig);

/**
 * @brief      Configurate Bridge Driver Function
 *
 * @param[in]  BridgeType: bridge driver Type.
 *              - GDU_BRIDGE_DRIVER_LS1
 *              - GDU_BRIDGE_DRIVER_LS2
 *              - GDU_BRIDGE_DRIVER_LS3
 *              - GDU_BRIDGE_DRIVER_HS1
 *              - GDU_BRIDGE_DRIVER_HS2
 *              - GDU_BRIDGE_DRIVER_HS3
 * @param[in]  DriverConfig: Pointer to a bridge driver configuration structure.
 *
 * @return     None
 *
 */
void Gdu_ConfigBridgeDriver(Gdu_BridgeDriverType BridgeType,
                                      const Gdu_BridgeDriverConfigType * DriverConfig);

/**
 * @brief      Get Monitor Fault Status Function
 *
 * @param[in]  FaultType: Select Fault type.
 *              - GDU_FAULT_VCP_UV
 *              - GDU_FAULT_VSD_OV
 *              - GDU_FAULT_VDS_LS1
 *              - GDU_FAULT_VDS_LS2
 *              - GDU_FAULT_VDS_LS3
 *              - GDU_FAULT_VDS_HS1
 *              - GDU_FAULT_VDS_HS2
 *              - GDU_FAULT_VDS_HS3
 *              - GDU_FAULT_ALL
 *
 * @return     Result Status:
 *              - COMMON_RESET: no fault
 *              - COMMON_SET: Failure occurred
 */
Common_FlagStatusType Gdu_GetMonitorFaultStatus(Gdu_FaultType FaultType);

/**
 * @brief      Gdu Select Fault Driver & Predriver Recover Condition Function
 *
 * @param[in]  FaultType: Select Fault type.
 *              - GDU_FAULT_VCP_UV
 *              - GDU_FAULT_VSD_OV
 *              - GDU_FAULT_VDS_LS1
 *              - GDU_FAULT_VDS_LS2
 *              - GDU_FAULT_VDS_LS3
 *              - GDU_FAULT_VDS_HS1
 *              - GDU_FAULT_VDS_HS2
 *              - GDU_FAULT_VDS_HS3
 *              - GDU_FAULT_ALL
 * @param[in]  RecoverType: Select Recover Condition.
 *              - GDU_RECOVER_AUTOMATICALLY
 *              - GDU_RECOVER_MANUAL
 *
 * @return     None
 *
 */
void Gdu_SetFaultRecover(Gdu_FaultType FaultType, Gdu_FaultRecoverType RecoverType);

/**
 * @brief      Gdu Set Driver Shutdown In Case Of Fault Function
 *
 * @param[in]  FaultType: Select Fault type.
 *              - GDU_FAULT_VCP_UV
 *              - GDU_FAULT_VSD_OV
 *              - GDU_FAULT_VDS_LS1
 *              - GDU_FAULT_VDS_LS2
 *              - GDU_FAULT_VDS_LS3
 *              - GDU_FAULT_VDS_HS1
 *              - GDU_FAULT_VDS_HS2
 *              - GDU_FAULT_VDS_HS3
 *              - GDU_FAULT_ALL
 * @param[in]  Shutdown: Select Whether to Shutdown.
 *              - COMMON_DISABLE: driver not shutdown
 *              - COMMON_ENABLE: driver shutdown
 *
 * @return     None
 *
 */
void Gdu_SetFaultDriver(Gdu_FaultType FaultType, Common_ControlStateType Shutdown);

/**
 * @brief      Gdu Set Fault INT Mask/Unmask Function
 *
 * @param[in]  FaultType: Select Fault type.
 *              - GDU_FAULT_VCP_UV
 *              - GDU_FAULT_VSD_OV
 *              - GDU_FAULT_VDS_LS1
 *              - GDU_FAULT_VDS_LS2
 *              - GDU_FAULT_VDS_LS3
 *              - GDU_FAULT_VDS_HS1
 *              - GDU_FAULT_VDS_HS2
 *              - GDU_FAULT_VDS_HS3
 *              - GDU_FAULT_ALL
 * @param[in]  IntMask: Mask/Unmask.
 *              - COMMON_UNMASK
 *              - COMMON_MASK
 *
 * @return     None
 *
 */
void Gdu_SetFaultIntMask(Gdu_FaultType FaultType, Common_IntMaskType IntMask);

/**
 * @brief      Gdu Clear Fault INT Status Function
 *
 * @param[in]  FaultType: Select Fault type.
 *              - GDU_FAULT_VCP_UV
 *              - GDU_FAULT_VSD_OV
 *              - GDU_FAULT_VDS_LS1
 *              - GDU_FAULT_VDS_LS2
 *              - GDU_FAULT_VDS_LS3
 *              - GDU_FAULT_VDS_HS1
 *              - GDU_FAULT_VDS_HS2
 *              - GDU_FAULT_VDS_HS3
 *              - GDU_FAULT_ALL
 *
 * @return     None
 *
 */
void Gdu_ClearFaultInt(Gdu_FaultType FaultType);

/**
 * @brief      Gdu Get Fault INT status Function
 *
 * @param[in]  FaultType: Select Fault type.
 *              - GDU_FAULT_VCP_UV
 *              - GDU_FAULT_VSD_OV
 *              - GDU_FAULT_VDS_LS1
 *              - GDU_FAULT_VDS_LS2
 *              - GDU_FAULT_VDS_LS3
 *              - GDU_FAULT_VDS_HS1
 *              - GDU_FAULT_VDS_HS2
 *              - GDU_FAULT_VDS_HS3
 *              - GDU_FAULT_ALL
 *
 * @return     IntStatus
 *              - COMMON_RESET
 *              - COMMON_SET
 *
 */
Common_IntStatusType Gdu_GetFaultIntStatus(Gdu_FaultType FaultType);



/**
 * @brief      Gdu Init function
 *.
 *
 * @return     None
 *
 */
void Gdu_Init( const Gdu_InitConfigType * InitConfig);

/** @} end of group Public_FunctionDeclaration */

#endif /* GDU_DRV_H */
