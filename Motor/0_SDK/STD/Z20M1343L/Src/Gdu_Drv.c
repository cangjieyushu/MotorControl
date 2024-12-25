/**************************************************************************************************/
/**
 * @file      : Gdu_Drv.c
 * @brief     : Gdu module driver file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
#include "Gdu_Drv.h"

/** @defgroup Private_MacroDefinition
 *  @{
 */

/** @} end of group Private_MacroDefinition */

/** @defgroup Private_TypeDefinition
 *  @{
 */

/** @} end of group Private_TypeDefinition */

/** @defgroup Global_VariableDefinition
 *  @{
 */

/** @} end of group Global_VariableDefinition */

/** @defgroup Private_VariableDefinition
 *  @{
 */

/*PRQA S 0303 ++*/
static Reg_Gdu_BfType * const Gdu_RegBfPtr = (Reg_Gdu_BfType *)GDU_BASE_ADDR;
static Reg_Gdu_WType * const Gdu_RegWPtr = (Reg_Gdu_WType *)GDU_BASE_ADDR;
/*PRQA S 0303 --*/

static const uint32 Gdu_IntMaskTable[] =
{
    0x00000002U,      /* FAULT_VCP_UV_INT */
    0x00000020U,      /* FAULT_VSD_OV_INT */
    0x00000200U,      /* FAULT_VDS_LS1_INT */
    0x00002000U,      /* FAULT_VDS_LS2_INT */
    0x00020000U,      /* FAULT_VDS_LS3_INT */
    0x00200000U,      /* FAULT_VDS_HS1_INT */
    0x02000000U,      /* FAULT_VDS_HS2_INT */
    0x20000000U,      /* FAULT_VDS_HS3_INT */
    0x22222222U       /* FAULT_ALL_INT */
};

static const uint32 Gdu_IntStatusTable[] =
{
    0x00000001U,      /* FAULT_VCP_UV_INT */
    0x00000010U,      /* FAULT_VSD_OV_INT */
    0x00000100U,      /* FAULT_VDS_LS1_INT */
    0x00001000U,      /* FAULT_VDS_LS2_INT */
    0x00010000U,      /* FAULT_VDS_LS3_INT */
    0x00100000U,      /* FAULT_VDS_HS1_INT */
    0x01000000U,      /* FAULT_VDS_HS2_INT */
    0x10000000U,      /* FAULT_VDS_HS3_INT */
    0x11111111U       /* FAULT_ALL_INT */
};

static uint32 Gdu_IntMaskStatus = 0U;
/** @} end of group Private_VariableDefinition */


/**
 * @brief      Configurate Charge Pump Function
 *
 * @param[in]  ChargePumpConfig: Pointer to a charge pump configuration structure.
 *
 * @return     None
 *
 */
void Gdu_ConfigChargePump(const Gdu_ChargePumpConfigType * ChargePumpConfig)
{
    Gdu_RegBfPtr->GDU_CP_CTRL.DITH_LO = (uint32)ChargePumpConfig->ClockDitherTHL;
    Gdu_RegBfPtr->GDU_CP_CTRL.DITH_UP = (uint32)ChargePumpConfig->ClockDitherTHH;
    Gdu_RegBfPtr->GDU_CP_CTRL.CP_EN = (uint32)ChargePumpConfig->ChargePumpEn;
}

/**
 * @brief      Configurate Filter/Blank Time Function
 *
 * @param[in]  FilterBlankConfig: Pointer to a filter/blank time configuration structure.
 *
 * @return     None
 *
 */
void Gdu_ConfigFilterBlank(const Gdu_FilterBlankConfigType * FilterBlankConfig)
{
    Gdu_RegBfPtr->GDU_FILT.VDS_BLK = (uint32)FilterBlankConfig->VdsBlankTime;
    Gdu_RegBfPtr->GDU_FILT.LS_VDS_FILT = (uint32)FilterBlankConfig->VdsFilterTimeLow;
    Gdu_RegBfPtr->GDU_FILT.HS_VDS_FILT = (uint32)FilterBlankConfig->VdsFilterTimeHigh;
    Gdu_RegBfPtr->GDU_FILT.VCP_UV_FILT = (uint32)FilterBlankConfig->VcpUvFilterTime;
    Gdu_RegBfPtr->GDU_FILT.VSD_OV_FILT = (uint32)FilterBlankConfig->VsdOvFilterTime;
}

/**
 * @brief      Configurate Delay Measure Function
 *
 * @param[in]  DelayMeasureConfig: Pointer to a delay measure configuration structure.
 *
 * @return     None
 *
 */
void Gdu_ConfigDelayMeasure(const Gdu_DelayMeasureConfigType * DelayMeasureConfig)
{
    Gdu_RegBfPtr->GDU_DLY.DLY_MEA_CH = (uint32)DelayMeasureConfig->MeasureChannel;
    Gdu_RegBfPtr->GDU_DLY.DLY_MEA_DIR = (uint32)DelayMeasureConfig->MeasureDirection;
}

/**
 * @brief      Restart Delay Measure Function
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void Gdu_RestartDelayMeasure(void)
{
    Gdu_RegBfPtr->GDU_DLY.DLY_MEA_CLR = 1U;
}

/**
 * @brief      Get Delay Measure Result Function
 *
 * @param[out] Result: 12-bit delay measure timer result.
 *
 * @return     Result Status:
 *              - COMMON_SUCC: measurement is complete
 *              - COMMON_ERR: measurement is not complete
 */
Common_ResultStatusType Gdu_GetDelayMeasureResult(uint16 * Result)
{
    Common_ResultStatusType ReturnValue = COMMON_ERR;
    if(Gdu_RegBfPtr->GDU_DLY.DLY_MEA_RDY != 0U)
    {
        *Result = (uint16)Gdu_RegBfPtr->GDU_DLY.DLY_MEA_TIM;
        ReturnValue = COMMON_SUCC;
    }

    return ReturnValue;
}

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
void Gdu_SetVdsThreshold(Gdu_VDSThresholdType Threshold)
{
    Gdu_RegBfPtr->GDU_CTRL3.VDS_TH = (uint32)Threshold;
}

/**
 * @brief      Configurate Cross Conduction Protection Function
 *
 * @param[in]  CcpConfig: Pointer to a cross conduction protection configuration structure.
 *
 * @return     None
 *
 */
void Gdu_ConfigCcp(const Gdu_CcpConfigType * CcpConfig)
{
    Gdu_RegBfPtr->GDU_CTRL3.CCP_TIM = (uint32)CcpConfig->CcpTime;
    Gdu_RegBfPtr->GDU_CTRL3.CCP_MUL = (uint32)CcpConfig->CcpMultiplier;
    Gdu_RegBfPtr->GDU_CTRL3.CCP1_DIS = (uint32)CcpConfig->CcpBridge1Disable;
    Gdu_RegBfPtr->GDU_CTRL3.CCP2_DIS = (uint32)CcpConfig->CcpBridge2Disable;
    Gdu_RegBfPtr->GDU_CTRL3.CCP3_DIS = (uint32)CcpConfig->CcpBridge3Disable;
}

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
                                      const Gdu_BridgeDriverConfigType * DriverConfig)
{
    switch (BridgeType)
    {
    case GDU_BRIDGE_DRIVER_LS1:
        Gdu_RegBfPtr->GDU_CTRL1.LS1_EN = (uint32)DriverConfig->DriverEnable;
        Gdu_RegBfPtr->GDU_CTRL1.LS1_CMS = (uint32)DriverConfig->DriverMode;
        Gdu_RegBfPtr->GDU_CTRL1.LS1_ON = (uint32)DriverConfig->DriverControlOn;
        Gdu_RegBfPtr->GDU_CTRL1.LS1_DCS_EN = (uint32)DriverConfig->DiagnosisCurrentEn;
        Gdu_RegBfPtr->GDU_CTRL1.LS1_VDS_EN = (uint32)DriverConfig->VdsEnable;
        Gdu_RegBfPtr->GDU_CTRL1.LS1_DRV_VDS_DIS = (uint32)DriverConfig->DriverShutdown;
        break;
    
    case GDU_BRIDGE_DRIVER_LS2:
        Gdu_RegBfPtr->GDU_CTRL1.LS2_EN = (uint32)DriverConfig->DriverEnable;
        Gdu_RegBfPtr->GDU_CTRL1.LS2_CMS = (uint32)DriverConfig->DriverMode;
        Gdu_RegBfPtr->GDU_CTRL1.LS2_ON = (uint32)DriverConfig->DriverControlOn;
        Gdu_RegBfPtr->GDU_CTRL1.LS2_DCS_EN = (uint32)DriverConfig->DiagnosisCurrentEn;
        Gdu_RegBfPtr->GDU_CTRL1.LS2_VDS_EN = (uint32)DriverConfig->VdsEnable;
        Gdu_RegBfPtr->GDU_CTRL1.LS2_DRV_VDS_DIS = (uint32)DriverConfig->DriverShutdown;
        break;
    
    case GDU_BRIDGE_DRIVER_LS3:
        Gdu_RegBfPtr->GDU_CTRL2.LS3_EN = (uint32)DriverConfig->DriverEnable;
        Gdu_RegBfPtr->GDU_CTRL2.LS3_CMS = (uint32)DriverConfig->DriverMode;
        Gdu_RegBfPtr->GDU_CTRL2.LS3_ON = (uint32)DriverConfig->DriverControlOn;
        Gdu_RegBfPtr->GDU_CTRL2.LS3_DCS_EN = (uint32)DriverConfig->DiagnosisCurrentEn;
        Gdu_RegBfPtr->GDU_CTRL2.LS3_VDS_EN = (uint32)DriverConfig->VdsEnable;
        Gdu_RegBfPtr->GDU_CTRL2.LS3_DRV_VDS_DIS = (uint32)DriverConfig->DriverShutdown;
        break;
    
    case GDU_BRIDGE_DRIVER_HS1:
        Gdu_RegBfPtr->GDU_CTRL1.HS1_EN = (uint32)DriverConfig->DriverEnable;
        Gdu_RegBfPtr->GDU_CTRL1.HS1_CMS = (uint32)DriverConfig->DriverMode;
        Gdu_RegBfPtr->GDU_CTRL1.HS1_ON = (uint32)DriverConfig->DriverControlOn;
        Gdu_RegBfPtr->GDU_CTRL1.HS1_DCS_EN = (uint32)DriverConfig->DiagnosisCurrentEn;
        Gdu_RegBfPtr->GDU_CTRL1.HS1_VDS_EN = (uint32)DriverConfig->VdsEnable;
        Gdu_RegBfPtr->GDU_CTRL1.HS1_DRV_VDS_DIS = (uint32)DriverConfig->DriverShutdown;
        break;
    
    case GDU_BRIDGE_DRIVER_HS2:
        Gdu_RegBfPtr->GDU_CTRL1.HS2_EN = (uint32)DriverConfig->DriverEnable;
        Gdu_RegBfPtr->GDU_CTRL1.HS2_CMS = (uint32)DriverConfig->DriverMode;
        Gdu_RegBfPtr->GDU_CTRL1.HS2_ON = (uint32)DriverConfig->DriverControlOn;
        Gdu_RegBfPtr->GDU_CTRL1.HS2_DCS_EN = (uint32)DriverConfig->DiagnosisCurrentEn;
        Gdu_RegBfPtr->GDU_CTRL1.HS2_VDS_EN = (uint32)DriverConfig->VdsEnable;
        Gdu_RegBfPtr->GDU_CTRL1.HS2_DRV_VDS_DIS = (uint32)DriverConfig->DriverShutdown;
        break;
    
    case GDU_BRIDGE_DRIVER_HS3:
        Gdu_RegBfPtr->GDU_CTRL2.HS3_EN = (uint32)DriverConfig->DriverEnable;
        Gdu_RegBfPtr->GDU_CTRL2.HS3_CMS = (uint32)DriverConfig->DriverMode;
        Gdu_RegBfPtr->GDU_CTRL2.HS3_ON = (uint32)DriverConfig->DriverControlOn;
        Gdu_RegBfPtr->GDU_CTRL2.HS3_DCS_EN = (uint32)DriverConfig->DiagnosisCurrentEn;
        Gdu_RegBfPtr->GDU_CTRL2.HS3_VDS_EN = (uint32)DriverConfig->VdsEnable;
        Gdu_RegBfPtr->GDU_CTRL2.HS3_DRV_VDS_DIS = (uint32)DriverConfig->DriverShutdown;
        break;
    
    default:
        /* do nothing */
        break;
    }
}

/**
 * @brief      Get Monitor Fault Status Function
 *
 * @param[out] FaultType: Select Fault type.
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
Common_FlagStatusType Gdu_GetMonitorFaultStatus(Gdu_FaultType FaultType)
{
    Common_FlagStatusType ReturnValue = COMMON_RESET;
    uint8 Mask;

    if(FaultType < GDU_FAULT_ALL)
    {
        Mask = (1U << (uint8)FaultType);
    }
    else
    {
        Mask = 0xFFU;
    }

    if((Gdu_RegWPtr->GDU_STAT & Mask) != 0U)
    {
        ReturnValue = COMMON_SET;
    }

    return ReturnValue;
}

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
void Gdu_SetFaultRecover(Gdu_FaultType FaultType, Gdu_FaultRecoverType RecoverType)
{
    switch (FaultType)
    {
    case GDU_FAULT_VCP_UV:
        Gdu_RegBfPtr->GDU_INT.DRV_VCPUV_RCV = (uint32)RecoverType;
        break;
    
    case GDU_FAULT_VSD_OV:
        Gdu_RegBfPtr->GDU_INT.DRV_VSDOV_RCV = (uint32)RecoverType;
        break;
       
    case GDU_FAULT_VDS_LS1:
        Gdu_RegBfPtr->GDU_INT.LS1_VDS_RCV = (uint32)RecoverType;
        break;
      
    case GDU_FAULT_VDS_LS2:
        Gdu_RegBfPtr->GDU_INT.LS2_VDS_RCV = (uint32)RecoverType;
        break;
      
    case GDU_FAULT_VDS_LS3:
        Gdu_RegBfPtr->GDU_INT.LS3_VDS_RCV = (uint32)RecoverType;
        break;
      
    case GDU_FAULT_VDS_HS1:
        Gdu_RegBfPtr->GDU_INT.HS1_VDS_RCV = (uint32)RecoverType;
        break;
      
    case GDU_FAULT_VDS_HS2:
        Gdu_RegBfPtr->GDU_INT.HS2_VDS_RCV = (uint32)RecoverType;
        break;
       
    case GDU_FAULT_VDS_HS3:
        Gdu_RegBfPtr->GDU_INT.HS3_VDS_RCV = (uint32)RecoverType;
        break;
        
    case GDU_FAULT_ALL:
        Gdu_RegBfPtr->GDU_INT.DRV_VCPUV_RCV = (uint32)RecoverType;
        Gdu_RegBfPtr->GDU_INT.DRV_VSDOV_RCV = (uint32)RecoverType;
        Gdu_RegBfPtr->GDU_INT.LS1_VDS_RCV = (uint32)RecoverType;
        Gdu_RegBfPtr->GDU_INT.LS2_VDS_RCV = (uint32)RecoverType;
        Gdu_RegBfPtr->GDU_INT.LS3_VDS_RCV = (uint32)RecoverType;
        Gdu_RegBfPtr->GDU_INT.HS1_VDS_RCV = (uint32)RecoverType;
        Gdu_RegBfPtr->GDU_INT.HS2_VDS_RCV = (uint32)RecoverType;
        Gdu_RegBfPtr->GDU_INT.HS3_VDS_RCV = (uint32)RecoverType;
        break;
        
    default:
        /* do nothing */
        break;
    }
}

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
void Gdu_SetFaultDriver(Gdu_FaultType FaultType, Common_ControlStateType Shutdown)
{
    switch (FaultType)
    {
    case GDU_FAULT_VCP_UV:
        Gdu_RegBfPtr->GDU_INT.DRV_VCPUV_DIS = (uint32)Shutdown;
        break;
    
    case GDU_FAULT_VSD_OV:
        Gdu_RegBfPtr->GDU_INT.DRV_VSDOV_DIS = (uint32)Shutdown;
        break;
      
    case GDU_FAULT_ALL:
        Gdu_RegBfPtr->GDU_INT.DRV_VCPUV_DIS = (uint32)Shutdown;
        Gdu_RegBfPtr->GDU_INT.DRV_VSDOV_DIS = (uint32)Shutdown;
        break;
      
    default:
        /* do nothing */
        break;
    } 
}

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
void Gdu_SetFaultIntMask(Gdu_FaultType FaultType, Common_IntMaskType IntMask)
{
    uint32 Mask = Gdu_RegWPtr->GDU_INT & (~Gdu_IntStatusTable[GDU_FAULT_ALL]);
    if(COMMON_UNMASK == IntMask)
    {
        Gdu_IntMaskStatus = Gdu_IntMaskStatus | Gdu_IntStatusTable[FaultType];
        Gdu_RegWPtr->GDU_INT = Mask | Gdu_IntMaskTable[FaultType];
    }
    else
    {
        Gdu_RegWPtr->GDU_INT = Mask & (~Gdu_IntMaskTable[FaultType]);
        Gdu_IntMaskStatus = Gdu_IntMaskStatus & (~Gdu_IntStatusTable[FaultType]);
    }
}

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
void Gdu_ClearFaultInt(Gdu_FaultType FaultType)
{
    uint32 Mask = Gdu_RegWPtr->GDU_INT & (~Gdu_IntStatusTable[GDU_FAULT_ALL]);
    Gdu_RegWPtr->GDU_INT = Mask | Gdu_IntStatusTable[FaultType];
}

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
Common_IntStatusType Gdu_GetFaultIntStatus(Gdu_FaultType FaultType)
{
    Common_IntStatusType ReturnValue = COMMON_RESET;
   
    if((Gdu_RegWPtr->GDU_INT & Gdu_IntStatusTable[FaultType]) != 0UL)
    {
        ReturnValue = COMMON_SET;
    }

    return ReturnValue;
}

/**
 * @brief      Gdu Init function
 *.
 * @param[in]  : Callback function.
 * @return     None
 *
 */
void Gdu_Init( const Gdu_InitConfigType * InitConfig)
{
    
    Gdu_ConfigChargePump( InitConfig->ChargePumpConfig);
    Gdu_SetFaultRecover(GDU_FAULT_VCP_UV,InitConfig->VCPRecover);
    Gdu_SetFaultRecover(GDU_FAULT_VSD_OV,InitConfig->VSDRecover);
    Gdu_SetFaultRecover(GDU_FAULT_VDS_LS1,InitConfig->HLRecover);
    Gdu_SetFaultRecover(GDU_FAULT_VDS_LS2,InitConfig->HLRecover);
    Gdu_SetFaultRecover(GDU_FAULT_VDS_LS3,InitConfig->HLRecover);
    Gdu_SetFaultRecover(GDU_FAULT_VDS_HS1,InitConfig->HLRecover);
    Gdu_SetFaultRecover(GDU_FAULT_VDS_HS2,InitConfig->HLRecover);
    Gdu_SetFaultRecover(GDU_FAULT_VDS_HS3,InitConfig->HLRecover);
    Gdu_SetVdsThreshold(InitConfig->Threshold);
    Gdu_SetFaultDriver(GDU_FAULT_ALL,InitConfig->Shutdown);
    Gdu_ConfigDelayMeasure( InitConfig->DelayMeasureConfig);
    Gdu_ConfigFilterBlank( InitConfig->FilterBlankConfig);
    Gdu_ConfigCcp( InitConfig->CcpConfig);
    Gdu_ConfigBridgeDriver(GDU_BRIDGE_DRIVER_LS1,InitConfig->DriverConfig);
    Gdu_ConfigBridgeDriver(GDU_BRIDGE_DRIVER_LS2,InitConfig->DriverConfig);
    Gdu_ConfigBridgeDriver(GDU_BRIDGE_DRIVER_LS3,InitConfig->DriverConfig);
    Gdu_ConfigBridgeDriver(GDU_BRIDGE_DRIVER_HS1,InitConfig->DriverConfig);
    Gdu_ConfigBridgeDriver(GDU_BRIDGE_DRIVER_HS2,InitConfig->DriverConfig);
    Gdu_ConfigBridgeDriver(GDU_BRIDGE_DRIVER_HS3,InitConfig->DriverConfig);
}

/** @} end of group Public_FunctionDefinition */
