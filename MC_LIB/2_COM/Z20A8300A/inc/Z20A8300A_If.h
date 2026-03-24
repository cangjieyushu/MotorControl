/**************************************************************************************************/
/** 
 * @file      : Z20A8300A_If.h
 * @brief     : Z20A8300A Spi Interface Header File.
 *                 - Platform: Z20A8300A
 * @version   : V0.7.0
 * @date      : September-2022
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @Copyright : Copyright (c) 2022-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
#ifndef Z20A8300A_IF_H
#define Z20A8300A_IF_H

/** @addtogroup Z20A8300A_Driver
 *  @{
 */

/** @addtogroup Z20A8300A_If
 *  @brief Z20A8300A Spi Interface define.
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "Z20A8300A_Reg.h"
#include "Z20A8300A_Type.h"

/** @defgroup If_Public_MacroDefinition
 *  @{
 */

/*!< @name Frame - Z20A8300A Spi frame field */
/*!< @{ */
#define Z20A8300A_FRAME_PARITY_MASK               0x0001u
#define Z20A8300A_FRAME_PARITY_WIDTH              1u
#define Z20A8300A_FRAME_PARITY_SET(x)             (((uint32_t)((uint32_t)(x)))&Z20A8300A_FRAME_PARITY_MASK)
#define Z20A8300A_FRAME_PARITY_GET(x)             ((uint32_t)(((uint32_t)(x))&Z20A8300A_FRAME_PARITY_MASK))
#define Z20A8300A_FRAME_DATA_MASK                 0x03FEu
#define Z20A8300A_FRAME_DATA_SHIFT                1u
#define Z20A8300A_FRAME_DATA_WIDTH                9u
#define Z20A8300A_FRAME_DATA_SET(x)               (((uint32_t)(((uint32_t)(x))<<Z20A8300A_FRAME_DATA_SHIFT))&Z20A8300A_FRAME_DATA_MASK)
#define Z20A8300A_FRAME_DATA_GET(x)               (((uint32_t)(((uint32_t)(x))&Z20A8300A_FRAME_DATA_MASK))>>Z20A8300A_FRAME_DATA_SHIFT)
#define Z20A8300A_FRAME_WR_MASK                   0x0400u
#define Z20A8300A_FRAME_WR_SHIFT                  10u
#define Z20A8300A_FRAME_WR_WIDTH                  1u
#define Z20A8300A_FRAME_WR_SET(x)                 (((uint32_t)(((uint32_t)(x))<<Z20A8300A_FRAME_WR_SHIFT))&Z20A8300A_FRAME_WR_MASK)
#define Z20A8300A_FRAME_WR_GET(x)                 (((uint32_t)(((uint32_t)(x))&Z20A8300A_FRAME_WR_MASK))>>Z20A8300A_FRAME_WR_SHIFT)
#define Z20A8300A_FRAME_ADDRESS_MASK              0xF800u
#define Z20A8300A_FRAME_ADDRESS_SHIFT             11u
#define Z20A8300A_FRAME_ADDRESS_WIDTH             5u
#define Z20A8300A_FRAME_ADDRESS_SET(x)            (((uint32_t)(((uint32_t)(x))<<Z20A8300A_FRAME_ADDRESS_SHIFT))&Z20A8300A_FRAME_ADDRESS_MASK)
#define Z20A8300A_FRAME_ADDRESS_GET(x)            (((uint32_t)(((uint32_t)(x))&Z20A8300A_FRAME_ADDRESS_MASK))>>Z20A8300A_FRAME_ADDRESS_SHIFT)
/*!< @} */

/** @} end of If_Public_MacroDefinition */

/** @defgroup If_Public_TypeDefinition
 *  @{
 */

/**
 *  @brief Spi send callback function pointer definition
 */
typedef uint16_t (*SendCallBackPtr)(uint16_t Data);

/**
 *  @brief Spi receive callback function pointer definition
 */
typedef uint16_t (*ReceiveCallBackPtr)(void);

/**
 *  @brief Spi waiting for reception callback function pointer definition
 */
typedef uint16_t (*WaitingForReceptionCallBackPtr)(void);

/**  
 *  @brief Z20A8300A Spi frame type definition
 */
typedef union
{
    uint32_t DB;
    struct
    {
        uint32_t PARITY                :1;  /* [0]          r/w        */
        uint32_t DATA                  :9;  /* [9:1]        r/w        */
        uint32_t WR                    :1;  /* [10]         r/w        */
        uint32_t ADDRESS               :5;  /* [15:11]      r/w        */
        uint32_t RSVD                  :16; /* [31:16]      r        */
    } BITS;
} Z20A8300A_SpiFrameType;

/**  
 *  @brief Z20A8300A spi frame read/write bit type definition
 */
typedef enum
{
    Z20A8300A_WR_READ = 0U,
    Z20A8300A_WR_WRITE
} Z20A8300A_ReadWriteBitType;

/**  
 *  @brief Z20A8300A spi frame address field type definition
 */
typedef enum
{
    Z20A8300A_CONFIG0_ADDRESS = 0x0000U,
    Z20A8300A_CONFIG1_ADDRESS = 0x0001U,
    Z20A8300A_CONFIG2_ADDRESS = 0x0002U,
    Z20A8300A_CONFIG3_ADDRESS = 0x0003U,
    Z20A8300A_CONFIG4_ADDRESS = 0x0004U,
    Z20A8300A_CONFIG5_ADDRESS = 0x0005U,
    Z20A8300A_DPS0_ADDRESS    = 0x0006U,
    Z20A8300A_DPS1_ADDRESS    = 0x0007U,
    Z20A8300A_MASK0_ADDRESS   = 0x0008U,
    Z20A8300A_MASK1_ADDRESS   = 0x0009U,
    Z20A8300A_MASK2_ADDRESS   = 0x000AU,
    Z20A8300A_DIAG0_ADDRESS   = 0x000BU,
    Z20A8300A_DIAG1_ADDRESS   = 0x000CU,
    Z20A8300A_DIAG2_ADDRESS   = 0x000DU,
    Z20A8300A_CONTROL_ADDRESS = 0x000EU,
    Z20A8300A_RESERVED_ADDRESS = 0x000FU
} Z20A8300A_RegisterAddressType;

/**  
 *  @brief Z20A8300A spi status type definition
 */
typedef enum
{
    Z20A8300A_ERR_OK = 0U,
    Z20A8300A_ERR_SEND,
    Z20A8300A_ERR_OVER_TIME,
    Z20A8300A_ERR_PARITY,
    Z20A8300A_ERR_WRITE
} Z20A8300A_SpiStatusType;

/**  
 *  @brief Z20A8300A control config type definition
 */
typedef struct
{
    Z20A8300A_Ctrl_DiagModeType DiagMode;
    Z20A8300A_Ctrl_PhaseStatesType PhaseAInitVal;
    Z20A8300A_Ctrl_PhaseStatesType PhaseBInitVal;
    Z20A8300A_Ctrl_PhaseStatesType PhaseCInitVal;
} Z20A8300A_ControlConfigType;

/**  
 *  @brief Z20A8300A parameters config type definition
 */
typedef struct
{
    Z20A8300A_Config0_DeadTimeType DeadTime;
    Z20A8300A_Config0_OverTempeThresholdType OverTempeThreshold;
    Z20A8300A_Config0_VbbOverVoltageThresholdType VbbOverVoltageThreshold;
    Z20A8300A_Config1_OverCurrentBlankingTimeType OverCurrentBlankingTime;
    Z20A8300A_Config1_OverCurrentThresholdType OverCurrentThreshold;
    Z20A8300A_Config2_VgsVdsBlankingTimeType VgsVdsBlankingTime;
    Z20A8300A_Config2_ChargePumpFrequencyType ChargePumpFrequency;
    Z20A8300A_Config2_ChargePumpModeType ChargePumpMode;
    Z20A8300A_Config_VdsThresholdType VdsLowSideThreshold;
    Z20A8300A_ContorlStateType BootstrapManagementEnable;
    Z20A8300A_Config3_SourcePeakCurrentType SourcePeakCurrent;
    Z20A8300A_Config_VdsThresholdType VdsHighSideThreshold;
    Z20A8300A_Config4_SensorAmplifierOffsetType SensorAmplifierOffset;
    Z20A8300A_Config5_SensorGainType SensorAGain;
    Z20A8300A_Config5_SensorGainType SensorBGain;
    Z20A8300A_Config5_SensorGainType SensorCGain;
} Z20A8300A_ParamsConfigType;

/**  
 *  @brief Z20A8300A Dps config type definition
 */
typedef struct
{
    Z20A8300A_ContorlStateType EnableFCPU;
    Z20A8300A_ContorlStateType EnableFVDO;
    Z20A8300A_ContorlStateType EnableFSE;
    Z20A8300A_ContorlStateType EnableFOT;
    Z20A8300A_ContorlStateType EnableFVSU;
    Z20A8300A_ContorlStateType EnableFVSO;
    Z20A8300A_ContorlStateType EnableFVRU;
    Z20A8300A_ContorlStateType EnableFVRO;
    Z20A8300A_ContorlStateType EnableFVBU;
    Z20A8300A_ContorlStateType EnableFGSU;
    Z20A8300A_ContorlStateType EnableFDSO;
    Z20A8300A_ContorlStateType EnableFOC;
} Z20A8300A_DpsConfigType;

/**  
 *  @brief Z20A8300A diag mask config type definition
 */
typedef struct
{
    Z20A8300A_MaskType MaskEnableALU;
    Z20A8300A_MaskType MaskEnableAHU;
    Z20A8300A_MaskType MaskEnableBLU;
    Z20A8300A_MaskType MaskEnableBHU;
    Z20A8300A_MaskType MaskEnableCLU;
    Z20A8300A_MaskType MaskEnableCHU;
    Z20A8300A_MaskType MaskEnableBSUA;
    Z20A8300A_MaskType MaskEnableBSUB;
    Z20A8300A_MaskType MaskEnableBSUC;
    Z20A8300A_MaskType MaskEnableALO;
    Z20A8300A_MaskType MaskEnableAHO;
    Z20A8300A_MaskType MaskEnableBLO;
    Z20A8300A_MaskType MaskEnableBHO;
    Z20A8300A_MaskType MaskEnableCLO;
    Z20A8300A_MaskType MaskEnableCHO;
    Z20A8300A_MaskType MaskEnableAOC;
    Z20A8300A_MaskType MaskEnableBOC;
    Z20A8300A_MaskType MaskEnableCOC;
    Z20A8300A_MaskType MaskEnableOT;
    Z20A8300A_MaskType MaskEnableVDO;
    Z20A8300A_MaskType MaskEnableVRU;
    Z20A8300A_MaskType MaskEnableVRO;
    Z20A8300A_MaskType MaskEnableVCPU;
    Z20A8300A_MaskType MaskEnableVSU;
    Z20A8300A_MaskType MaskEnableVSO;
} Z20A8300A_MaskConfigType;

/**  
 *  @brief Z20A8300A Interface type definition
 */
typedef struct 
{
    Z20A8300A_SpiFrameType TxFrame;
    Z20A8300A_SpiFrameType RxFrame;

    SendCallBackPtr SpiSendCallBack;
    ReceiveCallBackPtr SpiReceiveCallBack;
    WaitingForReceptionCallBackPtr SpiWaitingForReceptionCallBack;

} Z20A8300A_IfType;

/**
 *  @brief Z20A8300A Diag Fault Flag type definition
 */
typedef enum
{
    Z20A8300A_DIAG_FAULT = 0U,
    Z20A8300A_DIAG_NORMAL
} Z20A8300A_FaultFlagType;

/** @} end of group If_Public_TypeDefinition */

/** @defgroup If_Global_VariableDeclaration
 *  @{
 */

/** @} end of group If_Global_VariableDeclaration */

/** @defgroup If_Public_FunctionDeclaration
 *  @{
 */

/**
 * @brief      uint16 Parity Check
 *
 * @param[in]  Data
 *
 * @return     uint16_t
 * @retval     0:even
 * @retval     1:odd
 *
 */
static inline uint16_t Z20A8300A_ParityCheck16(uint16_t Data)
{
    Data ^= (Data >> 8U);
    Data ^= (Data >> 4U);
    Data ^= (Data >> 2U);
    Data ^= (Data >> 1U);

    return Data & 0x0001U;
}

/**
 * @brief      Implement default assert macro
 *
 * @param[in]  x:condition
 *
 * @return     none
 *
 */

static inline void Z20A8300A_Assert(volatile bool x)
{
    if(x)
    {
        for(;;) {}
    }
    else
    {
    }
}

/** @} end of group If_Public_FunctionDeclaration */

#ifdef __cplusplus
}
#endif

/** @} end of group Z20A8300A_If */

/** @} end of group Z20A8300A_Driver */

#endif /* Z20A8300A_IF_H */
