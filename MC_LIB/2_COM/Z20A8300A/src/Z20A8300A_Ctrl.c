/**************************************************************************************************/
/** 
 * @file      : Z20A8300A_Ctrl.c
 * @brief     : Z20A8300A Control Register API Source File.
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

/** @addtogroup Z20A8300A_Ctrl
 *  @brief Z20A8300A Control Register API.
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "Z20A8300A_Ctrl.h"
#include "Z20A8300A_Spi.h"

/** @defgroup Ctrl_Private_MacroDefinition
 *  @{
 */

/** @} end of Ctrl_Private_MacroDefinition */

/** @defgroup Ctrl_Private_TypeDefinition
 *  @{
 */

/** @} end of group Ctrl_Private_TypeDefinition */

/** @defgroup Ctrl_Global_VariableDefinition
 *  @{
 */

/** @} end of group Ctrl_Global_VariableDefinition */

/** @defgroup Ctrl_Private_VariableDefinition
 *  @{
 */

/** @} end of group Ctrl_Private_VariableDefinition */

/** @defgroup Ctrl_Private_FunctionDeclaration
 *  @{
 */

/** @} end of group Ctrl_Private_FunctionDeclaration */

/** @defgroup Ctrl_Private_FunctionDefinition
 *  @{
 */

/** @} end of group Ctrl_Private_FunctionDefinition */

/** @defgroup Ctrl_Public_FunctionDefinition
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
                                                           Z20A8300A_Ctrl_GateType Gate)
{
    Z20A8300A_Ctrl_GateStatesType GateStates;

    if(1U == ((IfPtr->RxFrame.BITS.DATA >> (uint32_t)(Gate)) & 0x01U))
    {
        GateStates = Z20A8300A_GATE_HIGH;
    }
    else
    {
        GateStates = Z20A8300A_GATE_LOW;
    }
    
    return GateStates;
}

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
Z20A8300A_Ctrl_PhaseStatesType Z20A8300A_Ctrl_GetPhaseAStates(Z20A8300A_IfType *IfPtr)
{
    Z20A8300A_Ctrl_PhaseStatesType PhaseStates;
    
    if(Z20A8300A_CONTROL_AL_GET(IfPtr->RxFrame.BITS.DATA) == 
       Z20A8300A_CONTROL_AH_GET(IfPtr->RxFrame.BITS.DATA))
    {
        PhaseStates = Z20A8300A_PHASE_DISABLE;
    }
    else if((uint32_t)Z20A8300A_GATE_HIGH == Z20A8300A_CONTROL_AH_GET(IfPtr->RxFrame.BITS.DATA))
    {
        PhaseStates = Z20A8300A_PHASE_SOURCING;
    }
    else
    {
        PhaseStates = Z20A8300A_PHASE_SINKING;
    }
    
    return PhaseStates;
}
    
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
Z20A8300A_Ctrl_PhaseStatesType Z20A8300A_Ctrl_GetPhaseBStates(Z20A8300A_IfType *IfPtr)
{
    Z20A8300A_Ctrl_PhaseStatesType PhaseStates;
    
    if(Z20A8300A_CONTROL_BL_GET(IfPtr->RxFrame.BITS.DATA) == 
       Z20A8300A_CONTROL_BH_GET(IfPtr->RxFrame.BITS.DATA))
    {
        PhaseStates = Z20A8300A_PHASE_DISABLE;
    }
    else if((uint32_t)Z20A8300A_GATE_HIGH == Z20A8300A_CONTROL_BH_GET(IfPtr->RxFrame.BITS.DATA))
    {
        PhaseStates = Z20A8300A_PHASE_SOURCING;
    }
    else
    {
        PhaseStates = Z20A8300A_PHASE_SINKING;
    }
    
    return PhaseStates;
}
    
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
Z20A8300A_Ctrl_PhaseStatesType Z20A8300A_Ctrl_GetPhaseCStates(Z20A8300A_IfType *IfPtr)
{
    Z20A8300A_Ctrl_PhaseStatesType PhaseStates;
    
    if(Z20A8300A_CONTROL_CL_GET(IfPtr->RxFrame.BITS.DATA) == 
       Z20A8300A_CONTROL_CH_GET(IfPtr->RxFrame.BITS.DATA))
    {
        PhaseStates = Z20A8300A_PHASE_DISABLE;
    }
    else if((uint32_t)Z20A8300A_GATE_HIGH == Z20A8300A_CONTROL_CH_GET(IfPtr->RxFrame.BITS.DATA))
    {
        PhaseStates = Z20A8300A_PHASE_SOURCING;
    }
    else
    {
        PhaseStates = Z20A8300A_PHASE_SINKING;
    }
    
    return PhaseStates;
}

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
Z20A8300A_Ctrl_DiagModeType Z20A8300A_Ctrl_GetDiagMode(Z20A8300A_IfType *IfPtr)
{
    Z20A8300A_Ctrl_DiagModeType DiagMode;
    
    if(Z20A8300A_CONTROL_DG_GET(IfPtr->RxFrame.BITS.DATA) == (uint32_t)MODE_TEMPERATURE)
    {
        DiagMode = MODE_TEMPERATURE;
    }
    else if(Z20A8300A_CONTROL_DG_GET(IfPtr->RxFrame.BITS.DATA) == (uint32_t)MODE_SYSTEM_OUT)
    {
        DiagMode = MODE_SYSTEM_OUT;
    }
    else
    {
        DiagMode = MODE_FAULT_FLAG;
    }
    
    return DiagMode;
}

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
                                                     Z20A8300A_Ctrl_GateStatesType States)
{
    uint32_t Data;
    Z20A8300A_SpiStatusType Rst;
    Rst = Z20A8300A_ReadDataRegister(IfPtr,Z20A8300A_CONTROL_ADDRESS);
    if(Z20A8300A_ERR_OK == Rst)
    {
        if(States == Z20A8300A_GATE_LOW)
        {
            Data = (IfPtr->RxFrame.BITS.DATA & (~((uint32_t)0x0001U << (uint32_t)Gate)));
        }
        else
        {
            Data = (IfPtr->RxFrame.BITS.DATA | ((uint32_t)0x0001U << (uint32_t)Gate));
        }

        Rst = Z20A8300A_WriteDataRegister(IfPtr,Z20A8300A_CONTROL_ADDRESS,Data);
    }
    else
    {
    }
    
    return Rst;
}

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
                                                       Z20A8300A_Ctrl_PhaseStatesType Psa)
{
    uint32_t Data;
    Z20A8300A_SpiStatusType Rst;
    Rst = Z20A8300A_ReadDataRegister(IfPtr,Z20A8300A_CONTROL_ADDRESS);
    if(Z20A8300A_ERR_OK == Rst)
    {
        if(Psa == Z20A8300A_PHASE_SOURCING)
        {
            Data = (IfPtr->RxFrame.BITS.DATA &
                    (uint32_t)(~(Z20A8300A_CONTROL_AH_MASK | Z20A8300A_CONTROL_AL_MASK))) |
                   Z20A8300A_CONTROL_AH_SET(Z20A8300A_GATE_HIGH);
        }
        else if(Psa == Z20A8300A_PHASE_SINKING)
        {
            Data = (IfPtr->RxFrame.BITS.DATA &
                    (uint32_t)(~(Z20A8300A_CONTROL_AH_MASK | Z20A8300A_CONTROL_AL_MASK))) |
                   Z20A8300A_CONTROL_AL_SET(Z20A8300A_GATE_HIGH);
        }
        else
        {
            Data = (IfPtr->RxFrame.BITS.DATA &
                    (uint32_t)(~(Z20A8300A_CONTROL_AH_MASK | Z20A8300A_CONTROL_AL_MASK)));
        }

        Rst = Z20A8300A_WriteDataRegister(IfPtr,Z20A8300A_CONTROL_ADDRESS,Data);
    }
    else
    {
    }
    
    return Rst;
}
        
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
                                                       Z20A8300A_Ctrl_PhaseStatesType Psb)
{
    uint32_t Data;
    Z20A8300A_SpiStatusType Rst;
    Rst = Z20A8300A_ReadDataRegister(IfPtr,Z20A8300A_CONTROL_ADDRESS);
    if(Z20A8300A_ERR_OK == Rst)
    {
        if(Psb == Z20A8300A_PHASE_SOURCING)
        {
            Data = (IfPtr->RxFrame.BITS.DATA &
                    (uint32_t)(~(Z20A8300A_CONTROL_BH_MASK | Z20A8300A_CONTROL_BL_MASK))) |
                   (Z20A8300A_CONTROL_BH_SET(Z20A8300A_GATE_HIGH));
        }
        else if(Psb == Z20A8300A_PHASE_SINKING)
        {
            Data = (IfPtr->RxFrame.BITS.DATA &
                    (uint32_t)(~(Z20A8300A_CONTROL_BH_MASK | Z20A8300A_CONTROL_BL_MASK))) |
                   (Z20A8300A_CONTROL_BL_SET(Z20A8300A_GATE_HIGH));
        }
        else
        {
            Data = (IfPtr->RxFrame.BITS.DATA &
                    (uint32_t)(~(Z20A8300A_CONTROL_BH_MASK | Z20A8300A_CONTROL_BL_MASK)));
        }

        Rst = Z20A8300A_WriteDataRegister(IfPtr,Z20A8300A_CONTROL_ADDRESS,Data);
    }
    else
    {
    }
    
    return Rst;
}

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
                                                       Z20A8300A_Ctrl_PhaseStatesType Psc)
{
    uint32_t Data;
    Z20A8300A_SpiStatusType Rst;
    Rst = Z20A8300A_ReadDataRegister(IfPtr,Z20A8300A_CONTROL_ADDRESS);
    if(Z20A8300A_ERR_OK == Rst)
    {
        if(Psc == Z20A8300A_PHASE_SOURCING)
        {
            Data = (IfPtr->RxFrame.BITS.DATA &
                    (uint32_t)(~(Z20A8300A_CONTROL_CH_MASK | Z20A8300A_CONTROL_CL_MASK))) |
                   (Z20A8300A_CONTROL_CH_SET(Z20A8300A_GATE_HIGH));
        }
        else if(Psc == Z20A8300A_PHASE_SINKING)
        {
            Data = (IfPtr->RxFrame.BITS.DATA &
                    (uint32_t)(~(Z20A8300A_CONTROL_CH_MASK | Z20A8300A_CONTROL_CL_MASK))) |
                   (Z20A8300A_CONTROL_CL_SET(Z20A8300A_GATE_HIGH));
        }
        else
        {
            Data = (IfPtr->RxFrame.BITS.DATA &
                    (uint32_t)(~(Z20A8300A_CONTROL_CH_MASK | Z20A8300A_CONTROL_CL_MASK)));
        }

        Rst = Z20A8300A_WriteDataRegister(IfPtr,Z20A8300A_CONTROL_ADDRESS,Data);
    }
    else
    {
    }
    
    return Rst;
}

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
                                                   Z20A8300A_Ctrl_DiagModeType DiagMode)
{
    uint32_t Data;
    Z20A8300A_SpiStatusType Rst;
    Rst = Z20A8300A_ReadDataRegister(IfPtr,Z20A8300A_CONTROL_ADDRESS);
    if(Z20A8300A_ERR_OK == Rst)
    {
        Data = Z20A8300A_CONTROL_DG_SET(DiagMode);

        Rst = Z20A8300A_WriteDataRegister(IfPtr,Z20A8300A_CONTROL_ADDRESS,Data);
    }
    else
    {
    }

    return Rst;
}

/** @} end of group Ctrl_Public_FunctionDefinition */

#ifdef __cplusplus
}
#endif

/** @} end of group Z20A8300A_Ctrl */

/** @} end of group Z20A8300A_Driver */
