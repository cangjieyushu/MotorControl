/**************************************************************************************************/
/** 
 * @file      : Z20A8300A_Diag.h
 * @brief     : Z20A8300A DPS and DIAG Register API Header File.
 *                 - Platform: Z20A8300A
 * @version   : V0.7.0
 * @date      : September-2022
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @Copyright : Copyright (c) 2022-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
#ifndef Z20A8300A_DIAG_H
#define Z20A8300A_DIAG_H

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

#include "Z20A8300A_If.h"

/** @defgroup Diag_Public_MacroDefinition
 *  @{
 */

/** @} end of Diag_Public_MacroDefinition */

/** @defgroup Diag_Public_TypeDefinition
 *  @{
 */
/**  
 *  @brief Z20A8300A All DPS type definition
 */

typedef union
{
    uint32_t WORD;
    struct
    {
        uint32_t FCPU                  :1;  /* [0]         r/w        */
        uint32_t FVDO                  :1;  /* [1]         r/w        */
        uint32_t RSVD_3                :1;  /* [2]         r/w        */
        uint32_t FSE                   :1;  /* [3]         r/w        */
        uint32_t RSVD_5_8              :4;  /* [7:4]       r/w        */
        uint32_t FOT                   :1;  /* [8]         r/w        */
        uint32_t FVSU                  :1;  /* [9]         r/w        */
        uint32_t FVSO                  :1;  /* [10]        r/w        */
        uint32_t FVRU                  :1;  /* [11]        r/w        */
        uint32_t FVRO                  :1;  /* [12]        r/w        */
        uint32_t FVBU                  :1;  /* [13]        r/w        */
        uint32_t FGSU                  :1;  /* [14]        r/w        */
        uint32_t FDSO                  :1;  /* [15]        r/w        */
        uint32_t RSVD_16               :1;  /* [16]        r/w        */
        uint32_t FOC                   :1;  /* [17]        r/w        */
        uint32_t RSVD                  :14; /* [31:18]     r/w        */
    } BITS;
} Z20A8300A_AllDpsType;

/**  
 *  @brief Z20A8300A All Mask type definition
 */
typedef union
{
    uint32_t WORD;
    struct
    {
        uint32_t ALU                   :1;  /* [0]         r/w        */
        uint32_t AHU                   :1;  /* [1]         r/w        */
        uint32_t BLU                   :1;  /* [2]         r/w        */
        uint32_t BHU                   :1;  /* [3]         r/w        */
        uint32_t CLU                   :1;  /* [4]         r/w        */
        uint32_t CHU                   :1;  /* [5]         r/w        */
        uint32_t BSUA                  :1;  /* [6]         r/w        */
        uint32_t BSUB                  :1;  /* [7]         r/w        */
        uint32_t BSUC                  :1;  /* [8]         r/w        */
        uint32_t ALO                   :1;  /* [9]         r/w        */
        uint32_t AHO                   :1;  /* [10]        r/w        */
        uint32_t BLO                   :1;  /* [11]        r/w        */
        uint32_t BHO                   :1;  /* [12]        r/w        */
        uint32_t CLO                   :1;  /* [13]        r/w        */
        uint32_t CHO                   :1;  /* [14]        r/w        */
        uint32_t AOC                   :1;  /* [15]        r/w        */
        uint32_t BOC                   :1;  /* [16]        r/w        */
        uint32_t COC                   :1;  /* [17]        r/w        */
        uint32_t RSVD_1                :1;  /* [18]        r/w        */
        uint32_t OT                    :1;  /* [19]        r/w        */
        uint32_t RSVD_3                :1;  /* [20]        r/w        */
        uint32_t VDO                   :1;  /* [21]        r/w        */
        uint32_t VRU                   :1;  /* [22]        r/w        */
        uint32_t VRO                   :1;  /* [23]        r/w        */
        uint32_t VCPU                  :1;  /* [24]        r/w        */
        uint32_t VSU                   :1;  /* [25]        r/w        */
        uint32_t VSO                   :1;  /* [26]        r/w        */
        uint32_t RSVD                  :5;  /* [31:27]     r/w        */
    } BITS;
} Z20A8300A_AllMaskType;

/**  
 *  @brief Z20A8300A All Diag type definition
 */
typedef union
{
    uint32_t WORD;
    struct
    {
        uint32_t ALU                  :1;  /* [0]        r        */
        uint32_t AHU                  :1;  /* [1]        r        */
        uint32_t BLU                  :1;  /* [2]        r        */
        uint32_t BHU                  :1;  /* [3]        r        */
        uint32_t CLU                  :1;  /* [4]        r        */
        uint32_t CHU                  :1;  /* [5]        r        */
        uint32_t BSUA                 :1;  /* [6]        r        */
        uint32_t BSUB                 :1;  /* [7]        r        */
        uint32_t BSUC                 :1;  /* [8]        r        */
        uint32_t ALO                  :1;  /* [9]        r        */
        uint32_t AHO                  :1;  /* [10]        r        */
        uint32_t BLO                  :1;  /* [11]        r        */
        uint32_t BHO                  :1;  /* [12]        r        */
        uint32_t CLO                  :1;  /* [13]        r        */
        uint32_t CHO                  :1;  /* [14]        r        */
        uint32_t AOC                  :1;  /* [15]        r        */
        uint32_t BOC                  :1;  /* [16]        r        */
        uint32_t COC                  :1;  /* [17]        r        */
        uint32_t RSVD_1               :1;  /* [18]        r        */
        uint32_t RSVD_2               :1;  /* [19]        r        */
        uint32_t VDU                  :1;  /* [20]        r        */
        uint32_t VDO                  :1;  /* [21]        r        */
        uint32_t VRU                  :1;  /* [22]        r        */
        uint32_t VRO                  :1;  /* [23]        r        */
        uint32_t VCPU                 :1;  /* [24]        r        */
        uint32_t VSU                  :1;  /* [25]        r        */
        uint32_t VSO                  :1;  /* [26]        r        */
        uint32_t RSVD                 :5;  /* [31:27]     r        */
    } BITS;
} Z20A8300A_AllDiagType;

/** @} end of group Diag_Public_TypeDefinition */

/** @defgroup Diag_Global_VariableDeclaration
 *  @{
 */

/** @} end of group Diag_Global_VariableDeclaration */

/** @defgroup Diag_Public_FunctionDeclaration
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
                                                      Z20A8300A_AllDpsType *AllDpsPtr);

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
                           Z20A8300A_FaultNameType FaultType);

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
                        const Z20A8300A_DpsConfigType *DpsConfigPtr);

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
                                                            Z20A8300A_ContorlStateType En);

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
                                                       Z20A8300A_AllMaskType *AllMaskPtr);

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
                                                    Z20A8300A_MaskNameType MaskType);

/**
 * @brief      Set All Diag Mask Status
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  MaskCfgPtr:     mask config struct pointer
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
                                                      const Z20A8300A_MaskConfigType *MaskCfgPtr);

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
                                                         Z20A8300A_MaskType Mask);

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
                                                     Z20A8300A_AllDiagType *AllDiagPtr);

/**
 * @brief      Get status data
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 *             StatusRegPtr: status register struct pointer
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
                                                     Z20A8300A_StatusRegType *StatusRegPtr);

/** @} end of group Diag_Public_FunctionDeclaration */

#ifdef __cplusplus
}
#endif

/** @} end of group Z20A8300A_Diag */

/** @} end of group Z20A8300A_Driver */

#endif /* Z20A8300A_DIAG_H */
