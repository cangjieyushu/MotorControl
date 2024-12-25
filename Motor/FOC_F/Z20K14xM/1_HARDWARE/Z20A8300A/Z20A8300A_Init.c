/**************************************************************************************************/
/** 
 * @file      : Z20A8300A_Init.c
 * @brief     : Z20A8300A Init Source File.
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

/** @addtogroup Z20A8300A_Init
 *  @brief Z20A8300A Initialization API.
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "Z20A8300A_Init.h"

/** @defgroup Init_Private_MacroDefinition
 *  @{
 */

/** @} end of Init_Private_MacroDefinition */

/** @defgroup Init_Private_TypeDefinition
 *  @{
 */

/** @} end of group Init_Private_TypeDefinition */

/** @defgroup Init_Global_VariableDefinition
 *  @{
 */

Z20A8300A_IfType Z20A8300AIf1;

Z20A8300A_StatusRegType         Z20A8300AStatus_1;
Z20A8300A_AllDiagType           Z20A8300ADiag_1;

/** @} end of group Init_Global_VariableDefinition */

/** @defgroup Init_Private_VariableDefinition
 *  @{
 */
static const Z20A8300A_ControlConfigType CtrlConfigStruct =
{
    MODE_FAULT_FLAG,                        /*!< DiagMode */
    Z20A8300A_PHASE_DISABLE,                /*!< PhaseA States */
    Z20A8300A_PHASE_DISABLE,                /*!< PhaseB States */
    Z20A8300A_PHASE_DISABLE                 /*!< PhaseC States */
};
static const Z20A8300A_ParamsConfigType ParamsConfigStruct =
{
    Z20A8300A_DT_600nS,                    /*!< Dead Time */
    Z20A8300A_OTS_165_DEG,                  /*!< Over Temperature Threshold */
    Z20A8300A_VBOV_35V,                     /*!< Vbb Over Voltage Threshold */
    Z20A8300A_TCB_6200nS,                   /*!< Over Current Blanking Time */
    Z20A8300A_OCT_4800mV,                   /*!< Over Current Threshold */
    Z20A8300A_TVB_3150nS,                   /*!< Vgs Vds Blanking Time */
    Z20A8300A_FCP_200KHz,                   /*!< Charge Pump Frequency */
    Z20A8300A_CPM_REGULATE_TO_BATTERY,      /*!< Charge Pump Mode */
    Z20A8300A_VDS_THRESHOLD_1920mV,         /*!< Vds Low Side Threshold */
    Z20A8300A_DISABLE,                       /*!< Bootstrap Management Disable */
    Z20A8300A_SR_DISABLE,                   /*!< Source Peak Current */
    Z20A8300A_VDS_THRESHOLD_1920mV,         /*!< Vds High Side Threshold */
    Z20A8300A_SAO_2500mV,                   /*!< Sensor Amplifier Offset */
    Z20A8300A_SENSOR_GAIN_10,               /*!< SensorA Gain */
    Z20A8300A_SENSOR_GAIN_10,               /*!< SensorB Gain */
    Z20A8300A_SENSOR_GAIN_10                /*!< SensorC Gain */
};

static const Z20A8300A_DpsConfigType DpsConfigStruct =
{
    Z20A8300A_DISABLE,               /*!< VCP Under Voltage */
    Z20A8300A_ENABLE,                /*!< VDD Over Voltage */
    Z20A8300A_DISABLE,               /*!< SPI Transmission Error */
    Z20A8300A_ENABLE,                /*!< Over Temperature */
    Z20A8300A_ENABLE,                /*!< VBB Under Voltage */
    Z20A8300A_ENABLE,                /*!< VBB Over Voltage */
    Z20A8300A_ENABLE,                /*!< VREG Under Voltage */
    Z20A8300A_ENABLE,                /*!< VREG Over Voltage */
    Z20A8300A_ENABLE,                /*!< Bootstrap Under Voltage */
    Z20A8300A_ENABLE,                /*!< VGS Under Voltage */
    Z20A8300A_ENABLE,                /*!< VDS Over Voltage */
    Z20A8300A_ENABLE                 /*!< Over Current */
};

static const Z20A8300A_MaskConfigType MaskConfigStruct =
{
    Z20A8300A_UNMASK,                /*!< AL VGS Under Voltage */
    Z20A8300A_UNMASK,                /*!< AH VGS Under Voltage */
    Z20A8300A_UNMASK,                /*!< BL VGS Under Voltage */
    Z20A8300A_UNMASK,                /*!< BH VGS Under Voltage */
    Z20A8300A_UNMASK,                /*!< CL VGS Under Voltage */
    Z20A8300A_UNMASK,                /*!< CH VGS Under Voltage */
    Z20A8300A_UNMASK,                /*!< Phase A Bootstrap Under Voltage */
    Z20A8300A_UNMASK,                /*!< Phase B Bootstrap Under Voltage */
    Z20A8300A_UNMASK,                /*!< Phase C Bootstrap Under Voltage */

    Z20A8300A_UNMASK,                /*!< AL VDS Over Voltage */
    Z20A8300A_UNMASK,                /*!< AH VDS Over Voltage */
    Z20A8300A_UNMASK,                /*!< BL VDS Over Voltage */
    Z20A8300A_UNMASK,                /*!< BH VDS Over Voltage */
    Z20A8300A_UNMASK,                /*!< CL VDS Over Voltage */
    Z20A8300A_UNMASK,                /*!< CH VDS Over Voltage */
    Z20A8300A_UNMASK,                /*!< Phase A Over Current */
    Z20A8300A_UNMASK,                /*!< Phase B Over Current */
    Z20A8300A_UNMASK,                /*!< Phase C Over Current */

    Z20A8300A_UNMASK,                /*!< Over Temperature */
    Z20A8300A_UNMASK,                /*!< VDD Over Voltage */
    Z20A8300A_UNMASK,                /*!< VREG Under Voltage */
    Z20A8300A_UNMASK,                /*!< VREG Over Voltage */
    Z20A8300A_UNMASK,                /*!< VCP Under Voltage */
    Z20A8300A_UNMASK,                /*!< VBB Under Voltage */
    Z20A8300A_UNMASK                 /*!< VBB Over Voltage */
};

/** @} end of group Init_Private_VariableDefinition */

/** @defgroup Init_Private_FunctionDeclaration
 *  @{
 */

/** @} end of group Init_Private_FunctionDeclaration */

/** @defgroup Init_Private_FunctionDefinition
 *  @{
 */

/** @} end of group Init_Private_FunctionDefinition */

/** @defgroup Init_Public_FunctionDefinition
 *  @{
 */

/**
 * @brief       Z20A8300A Init
 *
 * @param[in]   none
 *
 * @return      uint32_t
 * @retval      1: success
 * @retval      0: failture
 *
 */
uint32_t Z20A8300A_Init1(void)
{
    Z20A8300A_StatusRegType Status;
    Z20A8300A_AllDiagType   Diag;
    uint16_t SpiErrorCounter=0U;
    uint32_t ReturnValue = 1U;

    /*!< MCU SPI init */
    MCU_Z20A8300A_SpiInit1();
    /*!< MCU GPIO init */
    MCU_Z20A8300A_GpioInit1();

    Z20A8300AIf1.SpiSendCallBack = MCU_SPI_SendToZ20A8300A1;
    Z20A8300AIf1.SpiReceiveCallBack = MCU_SPI_ReceiveFromZ20A8300A1;
    Z20A8300AIf1.SpiWaitingForReceptionCallBack = MCU_SPI_WaitingForReceptionFromZ20A8300A1;

    while(Z20A8300A_ERR_OK != Z20A8300A_Diag_ReadClearDiag(&Z20A8300AIf1,&Status,&Diag))
    {
        if(SpiErrorCounter > 10U)
        {
           ReturnValue = 0U;
           break;
        }
        SpiErrorCounter++;
    }
    if(ReturnValue!=0U)
    {
        SpiErrorCounter = 0U;
        if(Z20A8300A_ERR_OK != Z20A8300A_Ctrl_SetDiagMode(&Z20A8300AIf1,CtrlConfigStruct.DiagMode))
        { 
            SpiErrorCounter++;
        }
        if(Z20A8300A_ERR_OK != Z20A8300A_Ctrl_SetPhaseAStates(&Z20A8300AIf1,
                               CtrlConfigStruct.PhaseAInitVal))
        { 
            SpiErrorCounter++;
        }
        if(Z20A8300A_ERR_OK != Z20A8300A_Ctrl_SetPhaseBStates(&Z20A8300AIf1,
                               CtrlConfigStruct.PhaseBInitVal))
        { 
            SpiErrorCounter++;
        }
        if(Z20A8300A_ERR_OK != Z20A8300A_Ctrl_SetPhaseCStates(&Z20A8300AIf1,
                               CtrlConfigStruct.PhaseCInitVal))
        { 
            SpiErrorCounter++;
        }

        if(Z20A8300A_ERR_OK != Z20A8300A_Config_SetDeadTime(&Z20A8300AIf1,
                               ParamsConfigStruct.DeadTime))
        { 
            SpiErrorCounter++;
        }
        if(Z20A8300A_ERR_OK != Z20A8300A_Config_SetOverTempeThreshold(&Z20A8300AIf1,
                               ParamsConfigStruct.OverTempeThreshold))
        { 
            SpiErrorCounter++;
        }
        if(Z20A8300A_ERR_OK != Z20A8300A_Config_SetVbbOverVoltageThreshold(&Z20A8300AIf1,
                               ParamsConfigStruct.VbbOverVoltageThreshold))
        { 
            SpiErrorCounter++;
        }
        if(Z20A8300A_ERR_OK != Z20A8300A_Config_SetOverCurrentBlankingTime(&Z20A8300AIf1,
                               ParamsConfigStruct.OverCurrentBlankingTime))
        { 
            SpiErrorCounter++;
        }
        if(Z20A8300A_ERR_OK != Z20A8300A_Config_SetOverCurrentThreshold(&Z20A8300AIf1,
                               ParamsConfigStruct.OverCurrentThreshold))
        { 
            SpiErrorCounter++;
        }
        if(Z20A8300A_ERR_OK != Z20A8300A_Config_SetVgsVdsBlankingTime(&Z20A8300AIf1,
                               ParamsConfigStruct.VgsVdsBlankingTime))
        { 
            SpiErrorCounter++;
        }
        if(Z20A8300A_ERR_OK != Z20A8300A_Config_SetChargePumpFrequency(&Z20A8300AIf1,
                               ParamsConfigStruct.ChargePumpFrequency))
        { 
            SpiErrorCounter++;
        }
        if(Z20A8300A_ERR_OK != Z20A8300A_Config_SetChargePumpMode(&Z20A8300AIf1,
                               ParamsConfigStruct.ChargePumpMode))
        { 
            SpiErrorCounter++;
        }
        if(Z20A8300A_ERR_OK != Z20A8300A_Config_SetVdsLowSideThreshold(&Z20A8300AIf1,
                               ParamsConfigStruct.VdsLowSideThreshold))
        { 
            SpiErrorCounter++;
        }
        if(Z20A8300A_ERR_OK != Z20A8300A_Config_SetBootstrapManagementEnable(&Z20A8300AIf1,
                               ParamsConfigStruct.BootstrapManagementEnable))
        { 
            SpiErrorCounter++;
        }
        if(Z20A8300A_ERR_OK != Z20A8300A_Config_SetSourcePeakCurrent(&Z20A8300AIf1,
                               ParamsConfigStruct.SourcePeakCurrent))
        { 
            SpiErrorCounter++;
        }
        if(Z20A8300A_ERR_OK != Z20A8300A_Config_SetVdsHighSideThreshold(&Z20A8300AIf1,
                               ParamsConfigStruct.VdsHighSideThreshold))
        { 
            SpiErrorCounter++;
        }
        if(Z20A8300A_ERR_OK != Z20A8300A_Config_SetSensorAmplifierOffset(&Z20A8300AIf1,
                               ParamsConfigStruct.SensorAmplifierOffset))
        { 
            SpiErrorCounter++;
        }
        if(Z20A8300A_ERR_OK != Z20A8300A_Config_SetSensorAGain(&Z20A8300AIf1,
                               ParamsConfigStruct.SensorAGain))
        { 
            SpiErrorCounter++;
        }
        if(Z20A8300A_ERR_OK != Z20A8300A_Config_SetSensorBGain(&Z20A8300AIf1,
                               ParamsConfigStruct.SensorBGain))
        { 
            SpiErrorCounter++;
        }
        if(Z20A8300A_ERR_OK != Z20A8300A_Config_SetSensorCGain(&Z20A8300AIf1,
                               ParamsConfigStruct.SensorCGain))
        { 
            SpiErrorCounter++;
        }

        if(Z20A8300A_ERR_OK != Z20A8300A_Diag_SetAllFaultEnableStatus(&Z20A8300AIf1,&DpsConfigStruct))
        { 
            SpiErrorCounter++;
        }
        if(Z20A8300A_ERR_OK != Z20A8300A_Diag_SetAllDiagMaskStatus(&Z20A8300AIf1,&MaskConfigStruct))
        { 
            SpiErrorCounter++;
        }
    }
    
    if(0U == SpiErrorCounter)
    {
        ReturnValue =  1U;
    }
    else
    {
        ReturnValue =  0U;
    }
    
    return ReturnValue;
}

/** @} end of group Init_Public_FunctionDefinition */

#ifdef __cplusplus
}
#endif

/** @} end of group Z20A8300A_Init */

/** @} end of group Z20A8300A_Driver */
