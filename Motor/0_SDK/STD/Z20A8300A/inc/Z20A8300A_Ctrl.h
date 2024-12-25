/**************************************************************************************************/
/** 
 * @file      : Z20A8300A_Ctrl.h
 * @brief     : Z20A8300A Control Register API Header File.
 *                 - Platform: Z20A8300A
 * @version   : V0.7.0
 * @date      : September-2022
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @Copyright : Copyright (c) 2022-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
#ifndef Z20A8300A_CTRL_H
#define Z20A8300A_CTRL_H

/** @addtogroup Z20A8300A_Driver
 *  @{
 */

/** @addtogroup Z20A8300A_Ctrl
 *  @brief Z20A8300A Control Register API.
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "Z20A8300A_If.h"

/** @defgroup Ctrl_Public_MacroDefinition
 *  @{
 */

/** @} end of Ctrl_Public_MacroDefinition */

/** @defgroup Ctrl_Public_TypeDefinition
 *  @{
 */

/** @} end of group Ctrl_Public_TypeDefinition */

/** @defgroup Ctrl_Global_VariableDeclaration
 *  @{
 */

/** @} end of group Ctrl_Global_VariableDeclaration */

/** @defgroup Ctrl_Public_FunctionDeclaration
 *  @{
 */

/**
 * @brief      Get Gate States
 *             Before using this function,Z20A8300A_ReadDataRegister
 *             should be called to get the latest data.
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  Gate: Gate Type:
 *                   - GATE_AL
 *                   - GATE_AH
 *                   - GATE_BL
 *                   - GATE_BH
 *                   - GATE_CL
 *                   - GATE_CH
 *
 * @return     GateStates
 * @retval     GATE_LOW
 * @retval     GATE_HIGH
 *
 */
Z20A8300A_Ctrl_GateStatesType Z20A8300A_Ctrl_GetGateStates(Z20A8300A_IfType *IfPtr,
                                                           Z20A8300A_Ctrl_GateType Gate);

/**
 * @brief      Get PhaseA States
 *             Before using this function,Z20A8300A_ReadDataRegister
 *             should be called to get the latest data.
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 *
 * @return     PhaseStates
 * @retval     PHASE_DISABLE
 * @retval     PHASE_SINKING
 * @retval     PHASE_SOURCING
 *
 */
Z20A8300A_Ctrl_PhaseStatesType Z20A8300A_Ctrl_GetPhaseAStates(Z20A8300A_IfType *IfPtr);
    
/**
 * @brief      Get PhaseB States
 *             Before using this function,Z20A8300A_ReadDataRegister
 *             should be called to get the latest data.
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 *
 * @return     PhaseStates
 * @retval     PHASE_DISABLE
 * @retval     PHASE_SINKING
 * @retval     PHASE_SOURCING
 *
 */
Z20A8300A_Ctrl_PhaseStatesType Z20A8300A_Ctrl_GetPhaseBStates(Z20A8300A_IfType *IfPtr);
    
/**
 * @brief      Get PhaseC States
 *             Before using this function,Z20A8300A_ReadDataRegister
 *             should be called to get the latest data.
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 *
 * @return     PhaseStates
 * @retval     PHASE_DISABLE
 * @retval     PHASE_SINKING
 * @retval     PHASE_SOURCING
 *
 */
Z20A8300A_Ctrl_PhaseStatesType Z20A8300A_Ctrl_GetPhaseCStates(Z20A8300A_IfType *IfPtr);

/**
 * @brief      Get Diag Mode
 *             Before using this function,Z20A8300A_ReadDataRegister
 *             should be called to get the latest data.
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 *
 * @return     DiagMode
 * @retval     MODE_FAULT_FLAG
 * @retval     MODE_SYSTEM_OUT
 * @retval     MODE_TEMPERATURE
 *
 */
Z20A8300A_Ctrl_DiagModeType Z20A8300A_Ctrl_GetDiagMode(Z20A8300A_IfType *IfPtr);

/**
 * @brief      Set Gate States
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  Gate: Gate Type:
 *                   - GATE_AL
 *                   - GATE_AH
 *                   - GATE_BL
 *                   - GATE_BH
 *                   - GATE_CL
 *                   - GATE_CH
 * @param[in]  States: Gate States Type:
 *                     - GATE_LOW
 *                     - GATE_HIGH
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Ctrl_SetGateStates(Z20A8300A_IfType *IfPtr,
                                                     Z20A8300A_Ctrl_GateType Gate,
                                                     Z20A8300A_Ctrl_GateStatesType States);

/**
 * @brief      Set PhaseA States
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  Psa: Phase States Type:
 *                  - PHASE_DISABLE
 *                  - PHASE_SINKING
 *                  - PHASE_SOURCING
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Ctrl_SetPhaseAStates(Z20A8300A_IfType *IfPtr,
                                                       Z20A8300A_Ctrl_PhaseStatesType Psa);
        
/**
 * @brief      Set PhaseB States
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  Psb: Phase States Type:
 *                  - PHASE_DISABLE
 *                  - PHASE_SINKING
 *                  - PHASE_SOURCING
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Ctrl_SetPhaseBStates(Z20A8300A_IfType *IfPtr,
                                                       Z20A8300A_Ctrl_PhaseStatesType Psb);

/**
 * @brief      Set PhaseC States
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  Psc: Phase States Type:
 *                  - PHASE_DISABLE
 *                  - PHASE_SINKING
 *                  - PHASE_SOURCING
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Ctrl_SetPhaseCStates(Z20A8300A_IfType *IfPtr,
                                                       Z20A8300A_Ctrl_PhaseStatesType Psc);

/**
 * @brief      Set Diag Mode
 *
 * @param[in]  IfPtr: Z20A8300A Interface struct pointer
 * @param[in]  DiagMode: Diag Mode Type:
 *                       - MODE_FAULT_FLAG
 *                       - MODE_SYSTEM_OUT
 *                       - MODE_TEMPERATURE
 *
 * @return     SPI communication status
 * @retval     Z20A8300A_ERR_OK
 * @retval     Z20A8300A_ERR_SEND
 * @retval     Z20A8300A_ERR_OVER_TIME
 * @retval     Z20A8300A_ERR_PARITY
 * @retval     Z20A8300A_ERR_WRITE
 *
 */
Z20A8300A_SpiStatusType Z20A8300A_Ctrl_SetDiagMode(Z20A8300A_IfType *IfPtr,
                                                   Z20A8300A_Ctrl_DiagModeType DiagMode);

/** @} end of group Ctrl_Public_FunctionDeclaration */

#ifdef __cplusplus
}
#endif

/** @} end of group Z20A8300A_Ctrl */

/** @} end of group Z20A8300A_Driver */

#endif /* Z20A8300A_CTRL_H */
