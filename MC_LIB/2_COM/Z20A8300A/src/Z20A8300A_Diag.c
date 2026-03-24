/**************************************************************************************************/
/** 
 * @file      : Z20A8300A_Diag.c
 * @brief     : Z20A8300A DPS and DIAG Register API Source File.
 *                 - Platform: Z20A8300A
 * @version   : V0.7.0
 * @date      : September-2022
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @Copyright : Copyright (c) 2022-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
/** @addtogroup Z20A8300A_Driver
 *  @{
 */

/** @addtogroup Z20A8300A_Diag
 *  @brief Z20A8300A Fault States And Diagnostics Register API.
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "Z20A8300A_Diag.h"
#include "Z20A8300A_Spi.h"

/** @defgroup Diag_Private_MacroDefinition
 *  @{
 */

/** @} end of Diag_Private_MacroDefinition */

/** @defgroup Diag_Private_TypeDefinition
 *  @{
 */

/** @} end of group Diag_Private_TypeDefinition */

/** @defgroup Diag_Global_VariableDefinition
 *  @{
 */

/** @} end of group Diag_Global_VariableDefinition */

/** @defgroup Diag_Private_VariableDefinition
 *  @{
 */

/** @} end of group Diag_Private_VariableDefinition */

/** @defgroup Diag_Private_FunctionDeclaration
 *  @{
 */

/** @} end of group Diag_Private_FunctionDeclaration */

/** @defgroup Diag_Private_FunctionDefinition
 *  @{
 */

/** @} end of group Diag_Private_FunctionDefinition */

/** @defgroup Diag_Public_FunctionDefinition
 *  @{
 */

/**
 * @brief      Read DPS Data
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  AllDpsPtr: All DPS Register struct pointer
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Diag_ReadAllDPSData(Z20A8300A_IfType *IfPtr,
                                                      Z20A8300A_AllDpsType *AllDpsPtr)
{
    uint32_t Data;
    Z20A8300A_SpiStatusType Rst = Z20A8300A_ReadDataRegister(IfPtr,Z20A8300A_DPS0_ADDRESS);
    
    if(Z20A8300A_ERR_OK == Rst)
    {
        Data = Z20A8300A_FRAME_DATA_GET(IfPtr->RxFrame.DB);
        AllDpsPtr->WORD = Data;
        
        Rst = Z20A8300A_ReadDataRegister(IfPtr,Z20A8300A_DPS1_ADDRESS);
        if(Z20A8300A_ERR_OK == Rst)
        {
            Data = Z20A8300A_FRAME_DATA_GET(IfPtr->RxFrame.DB);
            AllDpsPtr->WORD |= (Data << 9U);
        }
    }
    else
    {
    }
    
    return Rst;
}

/**
 * @brief      Get Fault Enable Status
 *             Before using this function,Z20A8300A_Diag_ReadAllDPSData
 *             should be called to get the latest data.
 *
 * @param[in]  AllDpsPtr: All DPS Register struct pointer
 * @param[in]  FaultType: Fault Name Type:
 *                            - DPS0_FCPU
 *                            - DPS0_FVDO
 *                            - DPS0_FSE
 *                            - DPS0_FOT
 *                            - DPS1_FVSU
 *                            - DPS1_FVSO
 *                            - DPS1_FVRU
 *                            - DPS1_FVRO
 *                            - DPS1_FVBU
 *                            - DPS1_FGSU
 *                            - DPS1_FDSO
 *                            - DPS1_FOC
 *
 * @return     FaultEnable
 * @retval     DISABLE
 * @retval     ENABLE
 *
 */
Z20A8300A_ContorlStateType Z20A8300A_Diag_GetFaultEnableStatus(Z20A8300A_AllDpsType *AllDpsPtr,
                                                               Z20A8300A_FaultNameType FaultType)
{
    Z20A8300A_ContorlStateType Enable;

    if(1U == ((AllDpsPtr->WORD >> ((uint8_t)FaultType)) & 0x0001U))
    {
        Enable = Z20A8300A_ENABLE;
    }
    else
    {
        Enable = Z20A8300A_DISABLE;
    }

    return Enable;
}

/**
 * @brief      Set All Fault Enable Status
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  DpsConfigPtr: DPS config struct pointer
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Diag_SetAllFaultEnableStatus(Z20A8300A_IfType *IfPtr,
                        const Z20A8300A_DpsConfigType *DpsConfigPtr)
{
    Z20A8300A_SpiStatusType Rst;
    uint32_t Data;

    Data  = Z20A8300A_DPS0_FCPU_SET(DpsConfigPtr->EnableFCPU);
    Data |= Z20A8300A_DPS0_FVDO_SET(DpsConfigPtr->EnableFVDO);
    Data |= Z20A8300A_DPS0_FSE_SET(DpsConfigPtr->EnableFSE);
    Data |= Z20A8300A_DPS0_FOT_SET(DpsConfigPtr->EnableFOT);

    Rst = Z20A8300A_WriteDataRegister(IfPtr,Z20A8300A_DPS0_ADDRESS,Data);
    if(Z20A8300A_ERR_OK == Rst)
    {
        Data  = Z20A8300A_DPS1_FVSU_SET(DpsConfigPtr->EnableFVSU);
        Data |= Z20A8300A_DPS1_FVSO_SET(DpsConfigPtr->EnableFVSO);
        Data |= Z20A8300A_DPS1_FVRU_SET(DpsConfigPtr->EnableFVRU);
        Data |= Z20A8300A_DPS1_FVRO_SET(DpsConfigPtr->EnableFVRO);
        Data |= Z20A8300A_DPS1_FVBU_SET(DpsConfigPtr->EnableFVBU);
        Data |= Z20A8300A_DPS1_FGSU_SET(DpsConfigPtr->EnableFGSU);
        Data |= Z20A8300A_DPS1_FDSO_SET(DpsConfigPtr->EnableFDSO);
        Data |= Z20A8300A_DPS1_FOC_SET(DpsConfigPtr->EnableFOC);

        Rst = Z20A8300A_WriteDataRegister(IfPtr,Z20A8300A_DPS1_ADDRESS,Data);
    }
    
    return Rst;
}

/**
 * @brief      Set Fault Enable Status
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  FaultType: Fault Name Type:
 *                            - DPS0_FCPU
 *                            - DPS0_FVDO
 *                            - DPS0_FSE
 *                            - DPS0_FOT
 *                            - DPS1_FVSU
 *                            - DPS1_FVSO
 *                            - DPS1_FVRU
 *                            - DPS1_FVRO
 *                            - DPS1_FVBU
 *                            - DPS1_FGSU
 *                            - DPS1_FDSO
 *                            - DPS1_FOC
 * @param[in]  En: Fault Enable Type:
 *                    - DISABLE
 *                    - ENABLE
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Diag_SetFaultEnableStatus(Z20A8300A_IfType *IfPtr,
                                                            Z20A8300A_FaultNameType FaultType,
                                                            Z20A8300A_ContorlStateType En)
{
    Z20A8300A_SpiStatusType Rst;
    uint32_t Data,FaultBits;
    Z20A8300A_RegisterAddressType Address;

    if((uint32_t)FaultType < 9U)
    {
        Address = Z20A8300A_DPS0_ADDRESS;
        FaultBits = (uint32_t)FaultType;
    }
    else
    {
        Address = Z20A8300A_DPS1_ADDRESS;
        FaultBits = (uint32_t)FaultType - 9U;
    }

    Rst = Z20A8300A_ReadDataRegister(IfPtr,Address);
    if(Z20A8300A_ERR_OK == Rst)
    {
        if(En == Z20A8300A_DISABLE)
        {
            Data = (IfPtr->RxFrame.BITS.DATA & (~((uint32_t)0x0001U << FaultBits)));
        }
        else
        {
            Data = (IfPtr->RxFrame.BITS.DATA | (((uint32_t)0x0001U << FaultBits)));
        }

        Rst = Z20A8300A_WriteDataRegister(IfPtr,Address,Data);
    }
    else
    {
    }
    
    return Rst;
}

/**
 * @brief      Read All Mask Data
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  AllMaskPtr: All mask register struct pointer
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Diag_ReadAllMaskData(Z20A8300A_IfType *IfPtr,
                                                       Z20A8300A_AllMaskType *AllMaskPtr)
{
    uint32_t Data;
    Z20A8300A_SpiStatusType Rst = Z20A8300A_ReadDataRegister(IfPtr,Z20A8300A_MASK0_ADDRESS);
    
    if(Z20A8300A_ERR_OK == Rst)
    {
        Data = Z20A8300A_FRAME_DATA_GET(IfPtr->RxFrame.DB);
        AllMaskPtr->WORD = Data;
        
        Rst = Z20A8300A_ReadDataRegister(IfPtr,Z20A8300A_MASK1_ADDRESS);
        if(Z20A8300A_ERR_OK == Rst)
        {
            Data = Z20A8300A_FRAME_DATA_GET(IfPtr->RxFrame.DB);
            AllMaskPtr->WORD |= (Data << 9U);
            
            Rst = Z20A8300A_ReadDataRegister(IfPtr,Z20A8300A_MASK2_ADDRESS);
            if(Z20A8300A_ERR_OK == Rst)
            {
                Data = Z20A8300A_FRAME_DATA_GET(IfPtr->RxFrame.DB);
                AllMaskPtr->WORD |= (Data << 18U);
            }
        }
    }
    else
    {
    }
    
    return Rst;
}

/**
 * @brief      Get Diag Mask Status
 *             Before using this function,Z20A8300A_Diag_ReadAllMaskData
 *             should be called to get the latest data.
 *
 * @param[in]  AllMaskPtr: All mask register struct pointer
 * @param[in]  MaskType: Mask Name Type:
 *                            - DIAG0_ALU
 *                            - DIAG0_AHU
 *                            - DIAG0_BLU
 *                            - DIAG0_BHU
 *                            - DIAG0_CLU
 *                            - DIAG0_CHU                        
 *                            - DIAG0_BSUA
 *                            - DIAG0_BSUB
 *                            - DIAG0_BSUC
 *                            - DIAG1_ALO
 *                            - DIAG1_AHO
 *                            - DIAG1_BLO
 *                            - DIAG1_BHO
 *                            - DIAG1_CLO
 *                            - DIAG1_CHO                            
 *                            - DIAG1_AOC
 *                            - DIAG1_BOC
 *                            - DIAG1_COC                            
 *                            - DIAG2_OT
 *                            - DIAG2_VDO                        
 *                            - DIAG2_VRU
 *                            - DIAG2_VRO                        
 *                            - DIAG2_VCPU
 *                            - DIAG2_VSU
 *                            - DIAG2_VSO
 *
 * @return     DiagMask
 * @retval     UNMASK
 * @retval     MASK
 *
 */
Z20A8300A_MaskType Z20A8300A_Diag_GetDiagMaskStatus(Z20A8300A_AllMaskType *AllMaskPtr,
                                                    Z20A8300A_MaskNameType MaskType)
{
    Z20A8300A_MaskType Mask;

    if(1U == ((AllMaskPtr->WORD >> ((uint8_t)MaskType)) & 0x0001U))
    {
        Mask = Z20A8300A_MASK;
    }
    else
    {
        Mask = Z20A8300A_UNMASK;
    }
    
    return Mask;
}

/**
 * @brief      Set All Diag Mask Status
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  MaskCfgPtr: mask config struct pointer
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Diag_SetAllDiagMaskStatus(Z20A8300A_IfType *IfPtr,
                                                      const Z20A8300A_MaskConfigType *MaskCfgPtr)
{
    Z20A8300A_SpiStatusType Rst;
    uint32_t Data;

    Data  = Z20A8300A_MASK0_ALU_SET(MaskCfgPtr->MaskEnableALU);
    Data |= Z20A8300A_MASK0_AHU_SET(MaskCfgPtr->MaskEnableAHU);
    Data |= Z20A8300A_MASK0_BLU_SET(MaskCfgPtr->MaskEnableBLU);
    Data |= Z20A8300A_MASK0_BHU_SET(MaskCfgPtr->MaskEnableBHU);
    Data |= Z20A8300A_MASK0_CLU_SET(MaskCfgPtr->MaskEnableCLU);
    Data |= Z20A8300A_MASK0_CHU_SET(MaskCfgPtr->MaskEnableCHU);
    Data |= Z20A8300A_MASK0_BSUA_SET(MaskCfgPtr->MaskEnableBSUA);
    Data |= Z20A8300A_MASK0_BSUB_SET(MaskCfgPtr->MaskEnableBSUB);
    Data |= Z20A8300A_MASK0_BSUC_SET(MaskCfgPtr->MaskEnableBSUC);
    
    Rst = Z20A8300A_WriteDataRegister(IfPtr,Z20A8300A_MASK0_ADDRESS,Data);
    
    if(Z20A8300A_ERR_OK == Rst)
    {
        Data  = Z20A8300A_MASK1_ALO_SET(MaskCfgPtr->MaskEnableALO);
        Data |= Z20A8300A_MASK1_AHO_SET(MaskCfgPtr->MaskEnableAHO);
        Data |= Z20A8300A_MASK1_BLO_SET(MaskCfgPtr->MaskEnableBLO);
        Data |= Z20A8300A_MASK1_BHO_SET(MaskCfgPtr->MaskEnableBHO);
        Data |= Z20A8300A_MASK1_CLO_SET(MaskCfgPtr->MaskEnableCLO);
        Data |= Z20A8300A_MASK1_CHO_SET(MaskCfgPtr->MaskEnableCHO);
        Data |= Z20A8300A_MASK1_AOC_SET(MaskCfgPtr->MaskEnableAOC);
        Data |= Z20A8300A_MASK1_BOC_SET(MaskCfgPtr->MaskEnableBOC);
        Data |= Z20A8300A_MASK1_COC_SET(MaskCfgPtr->MaskEnableCOC);
        
        Rst = Z20A8300A_WriteDataRegister(IfPtr,Z20A8300A_MASK1_ADDRESS,Data);
        
        if(Z20A8300A_ERR_OK == Rst)
        {
            Data  = Z20A8300A_MASK2_OT_SET(MaskCfgPtr->MaskEnableOT);
            Data |= Z20A8300A_MASK2_VDO_SET(MaskCfgPtr->MaskEnableVDO);
            Data |= Z20A8300A_MASK2_VRU_SET(MaskCfgPtr->MaskEnableVRU);
            Data |= Z20A8300A_MASK2_VRO_SET(MaskCfgPtr->MaskEnableVRO);
            Data |= Z20A8300A_MASK2_VCPU_SET(MaskCfgPtr->MaskEnableVCPU);
            Data |= Z20A8300A_MASK2_VSU_SET(MaskCfgPtr->MaskEnableVSU);
            Data |= Z20A8300A_MASK2_VSO_SET(MaskCfgPtr->MaskEnableVSO);

            Rst = Z20A8300A_WriteDataRegister(IfPtr,Z20A8300A_MASK2_ADDRESS,Data);
        }
    }

    return Rst;
}

/**
 * @brief      Set Diag Mask Status
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  MaskType: Mask Name Type:
 *                            - DIAG0_ALU
 *                            - DIAG0_AHU
 *                            - DIAG0_BLU
 *                            - DIAG0_BHU
 *                            - DIAG0_CLU
 *                            - DIAG0_CHU                        
 *                            - DIAG0_BSUA
 *                            - DIAG0_BSUB
 *                            - DIAG0_BSUC
 *                            - DIAG1_ALO
 *                            - DIAG1_AHO
 *                            - DIAG1_BLO
 *                            - DIAG1_BHO
 *                            - DIAG1_CLO
 *                            - DIAG1_CHO                            
 *                            - DIAG1_AOC
 *                            - DIAG1_BOC
 *                            - DIAG1_COC                            
 *                            - DIAG2_OT
 *                            - DIAG2_VDO                        
 *                            - DIAG2_VRU
 *                            - DIAG2_VRO                        
 *                            - DIAG2_VCPU
 *                            - DIAG2_VSU
 *                            - DIAG2_VSO
 * @param[in]  Mask: Diag Mask Type:
 *                   - DIAG_UNMASK
 *                   - DIAG_MASK
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Diag_SetDiagMaskStatus(Z20A8300A_IfType *IfPtr,
                                                         Z20A8300A_MaskNameType MaskType,
                                                         Z20A8300A_MaskType Mask)
{
    Z20A8300A_SpiStatusType Rst;
    uint32_t Data,MaskBits;
    Z20A8300A_RegisterAddressType Address;

    if((uint32_t)MaskType >= 18U)
    {
        Address = Z20A8300A_MASK2_ADDRESS;
        MaskBits = (uint32_t)MaskType - 18U;
    }
    else if((uint32_t)MaskType >= 9U)
    {
        Address = Z20A8300A_MASK1_ADDRESS;
        MaskBits = (uint32_t)MaskType - 9U;
    }
    else
    {
        Address = Z20A8300A_MASK0_ADDRESS;
        MaskBits = (uint32_t)MaskType;
    }

    Rst = Z20A8300A_ReadDataRegister(IfPtr,Address);
    if(Z20A8300A_ERR_OK == Rst)
    {
        if(Mask == Z20A8300A_UNMASK)
        {
            Data = (IfPtr->RxFrame.BITS.DATA & (~((uint32_t)0x0001U << MaskBits)));
        }
        else
        {
            Data = (IfPtr->RxFrame.BITS.DATA | (((uint32_t)0x0001U << MaskBits)));
        }

        Rst = Z20A8300A_WriteDataRegister(IfPtr,Address,Data);
    }
    else
    {
    }
    
    return Rst;
}

/**
 * @brief      SPI Read Clear Diag
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  StatusRegPtr: status register struct pointer
 * @param[in]  AllDiagPtr: All diag register struct pointer
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Diag_ReadClearDiag(Z20A8300A_IfType *IfPtr,
                                                     Z20A8300A_StatusRegType *StatusRegPtr,
                                                     Z20A8300A_AllDiagType *AllDiagPtr)
{
    uint32_t Data;
    Z20A8300A_SpiStatusType Rst0;
    Z20A8300A_SpiStatusType Rst1 = Z20A8300A_ERR_OK;
    Z20A8300A_SpiStatusType Rst2 = Z20A8300A_ERR_OK;
    /* write RO reg get status */
    Rst0 = Z20A8300A_WriteDataRegister(IfPtr,Z20A8300A_DIAG0_ADDRESS,0U);        

    if(Z20A8300A_ERR_OK == Rst0)
    {
        StatusRegPtr->DB = IfPtr->RxFrame.DB;
        AllDiagPtr->WORD = 0U;

        if((1U == Z20A8300A_STATUS_BSU_GET(IfPtr->RxFrame.DB)) || 
           (1U == Z20A8300A_STATUS_GSU_GET(IfPtr->RxFrame.DB)))
        {
            Rst0 = Z20A8300A_ReadDataRegister(IfPtr,Z20A8300A_DIAG0_ADDRESS);
            if(Z20A8300A_ERR_OK == Rst0)
            {
                Data = Z20A8300A_FRAME_DATA_GET(IfPtr->RxFrame.DB);
                AllDiagPtr->WORD = Data;
            }
        }
        
        if((1U == Z20A8300A_STATUS_OC_GET(IfPtr->RxFrame.DB)) || 
           (1U == Z20A8300A_STATUS_DSO_GET(IfPtr->RxFrame.DB)))
        {
            Rst1 = Z20A8300A_ReadDataRegister(IfPtr,Z20A8300A_DIAG1_ADDRESS);
            if(Z20A8300A_ERR_OK == Rst1)
            {
                Data = Z20A8300A_FRAME_DATA_GET(IfPtr->RxFrame.DB);
                AllDiagPtr->WORD |= (Data << 9U);
            }
        }
        
        if( (1U == Z20A8300A_STATUS_VD_GET(IfPtr->RxFrame.DB)) ||
            (1U == Z20A8300A_STATUS_VR_GET(IfPtr->RxFrame.DB)) ||
            (1U == Z20A8300A_STATUS_VS_GET(IfPtr->RxFrame.DB)))
        {
            Rst2 = Z20A8300A_ReadDataRegister(IfPtr,Z20A8300A_DIAG2_ADDRESS);
            if(Z20A8300A_ERR_OK == Rst2)
            {
                Data = Z20A8300A_FRAME_DATA_GET(IfPtr->RxFrame.DB);
                AllDiagPtr->WORD |= (Data << 18U);
            }
        }

    }
    else
    {
    }
    
    if(Z20A8300A_ERR_OK != Rst0)
    {
    }
    else if(Z20A8300A_ERR_OK != Rst1)
    {
        Rst0 = Rst1;
    }
    else if(Z20A8300A_ERR_OK != Rst2)
    {
        Rst0 = Rst2;
    }
    else
    {
        Rst0 = Z20A8300A_ERR_OK;
    }
    
    return Rst0;
}

/**
 * @brief      Get status data
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  StatusRegPtr: status register struct pointer
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Diag_GetStatusData(Z20A8300A_IfType *IfPtr,
                                                     Z20A8300A_StatusRegType *StatusRegPtr)
{
    Z20A8300A_SpiStatusType Rst;
    /* write RO reg get status */
    Rst = Z20A8300A_WriteDataRegister(IfPtr,Z20A8300A_DIAG0_ADDRESS,0U);        

    if(Z20A8300A_ERR_OK == Rst)
    {
        StatusRegPtr->DB = IfPtr->RxFrame.DB;
    }
    else
    {
    }

    return Rst;
}

/** @} end of group Diag_Public_FunctionDefinition */

#ifdef __cplusplus
}
#endif

/** @} end of group Z20A8300A_Diag */

/** @} end of group Z20A8300A_Driver */
