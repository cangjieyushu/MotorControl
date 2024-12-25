/**************************************************************************************************/
/**
 * @file     : Hwacc_Drv.c
 * @brief    : Hwacc module driver source file.
 *              - Platform: Z20M1343L
 * @version  : 0.1.0
 * @date     : May-2023
 * @author   : Zhixin Semiconductor
 * @note     : None
 *   
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#include "Hwacc_Drv.h"

/** @defgroup Private_MacroDefinition
 *  @{
 */
/*PRQA S 0303 ++*/
static Reg_Hwacc_BfType * const Hwacc_RegBfPtr  = (Reg_Hwacc_BfType *) MATHACCEL_BASE_ADDR; /*!< HWACC Register */
static Reg_Hwacc_WType * const Hwacc_RegWPtr = (Reg_Hwacc_WType *) MATHACCEL_BASE_ADDR; /*!< HWACC Register */
/*PRQA S 0303 --*/

/** @} end of Private_MacroDefinition */

/** @defgroup Private_TypeDefinition
 *  @{
 */

/** @} end of group Private_TypeDefinition */

/** @defgroup Global_VariableDefinition
 *  @{
 */ 
   
/**
 *  @brief HWACC  ISR callback function  pointer 
 */

static Isr_CbFuncType * Hwacc_IsrCbFunc[HWACC_INT_ALL] = 
{
    NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, 
    NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR
};

/** @} end of group Global_VariableDefinition */

/** @defgroup Private_VariableDefinition
 *  @{
 */


/**
 *  @brief HWACC interrupt mask array
 */
static const uint32 Hwacc_IntMaskTable[] =
{
        0x00000001U,                /*!< clarke transform ends INT*/
        0x00000002U,                /*!< park transform ends INT*/
        0x00000008U,                /*!< pi_id currents end INT */
        0x00000010U,                /*!< pi_iq currents end INT */
        0x00000020U,                /*!< inverse park transform ends INT */
        0x00000040U,                /*!< inverse clarke transform ends INT */
        0x00000100U,                /*!< user math math commands execute done INT*/
        0x00000200U,                /*!< the division calculation result is in infinity INT */
        0x00000400U,                /*!<the calculation result is more than or equal to 1 INT */
        0x00000800U,                /*!< the rad is negative number INT */
        0x00001000U,                /*!< the calculation result is less than -1 INT */
        0x00001F7BU                 /*!< All the interrupts */
};

/**
 *  @brief Hwacc interrupt clear array
 */
static const uint32 Hwacc_IntClearTable[] =
{
        0x00000001U,                /*!< clear clarke transform ends INT*/
        0x00000002U,                /*!< clear park transform ends INT*/
        0x00000008U,                /*!< clear pi_id currents end INT */
        0x00000010U,                /*!< clear pi_iq currents end INT */
        0x00000020U,                /*!< clear inverse park transform ends INT */
        0x00000040U,                /*!< clear inverse clarke transform ends INT */
        0x00000100U,                /*!< clear user math math commands execute done INT*/
        0x00000200U,                /*!< clear the division calculation result is in infinity INT */
        0x00000400U,                /*!< clear the calculation result is more than or equal to 1*/
        0x00000800U,                /*!< clear the rad is negative number INT */
        0x00001000U,                /*!< clear the calculation result is less than -1 INT */
        0x00001F7BU                 /*!< clear All the interrupts */
};

/**
 *  @brief Hwacc interrupt mask status
 */
static uint32 Hwacc_IntMaskStatus = 0U;

/** @} end of group Private_VariableDefinition */

/** @defgroup Private_FunctionDeclaration
 *  @{
 */

void Math_Accel_DriverIrqHandler(void);

 /** @} end of group Private_FunctionDeclaration */

/** @defgroup Private_FunctionDefinition
 *  @{
 */
/**
 * @brief  Hwacc interrupt handler.
 * @param  None.
 * @return None.
 */
void Math_Accel_DriverIrqHandler(void)
{
    uint32 IntStatus;
    uint32 IntType;
    
    /* Read the interrupt status */
    IntStatus = Hwacc_RegWPtr->HWACC_INTR_STATE;
    /* only check enabled interrupts */
    IntStatus = IntStatus & Hwacc_IntMaskStatus; 
    for(IntType = (uint32)HWACC_INT_CLARK_TRANS; IntType < (uint32)HWACC_INT_ALL; IntType++)
    {
        if ((IntStatus & Hwacc_IntMaskTable[IntType]) != 0U)
        {
            /* Clear the interrupt status */
            Hwacc_RegWPtr->HWACC_INTR_STATE = Hwacc_IntClearTable[IntType];
            if (NULL_PTR != Hwacc_IsrCbFunc[IntType])
            {
                Hwacc_IsrCbFunc[IntType]();
            }
            /* Mask this interrupt */
            else
            {
                Hwacc_RegWPtr->HWACC_INTR_ENABLE &= (~Hwacc_IntMaskTable[IntType]);
            }
        }
    }
}

/** @} end of group Private_FunctionDefinition */

/** @defgroup Public_FunctionDefinition
 *  @{
 */

/**
 * @brief     Get interrupt status  
 *
 * @param[in] IntType: Interrupt type.
 *
 * @return    IntStatus : Interrupt status.
 * @retval    COMMON_RESET : Reset state.
 * @retval    COMMON_SET   : Set state.
 * 
 */
Common_IntStatusType Hwacc_GetIntStatus(Hwacc_IntType IntType)
{
    Common_IntStatusType IntStatus = COMMON_RESET;
    uint32 TempStatus = 0;
    switch (IntType)
    {
        case HWACC_INT_CLARK_TRANS:
        case HWACC_INT_PARK_TRANS:
        case HWACC_INT_PI_CURRENTD:
        case HWACC_INT_PI_CURRENTQ:
        case HWACC_INT_INV_PARK:
        case HWACC_INT_INV_CLARK:
        case HWACC_INT_MATHCMD:
        case HWACC_INT_DIV_NAN:
        case HWACC_INT_OVERFLOW:
        case HWACC_INT_SQR_ERR:
        case HWACC_INT_UNDERFLOW:
            TempStatus = (Hwacc_RegWPtr->HWACC_INTR_STATE & Hwacc_IntMaskTable[IntType]);
            break;
            
        default:
            /* do nothing */
            break;
    }

    if(TempStatus != 0UL)
    {
        IntStatus = COMMON_SET;
    }

    return IntStatus;
}

/**
 * @brief     HWACC interrupt mask or unmask function
 *
 * @param[in] IntType: Interrupt type.
 * @param[in] Cmd: COMMON_MASK, COMMON_UNMASK.
 *
 * @return    none.
 * 
 */
void Hwacc_IntMask(Hwacc_IntType IntType, Common_IntMaskType Cmd)
{   
    if(COMMON_UNMASK == Cmd)
    {
        Hwacc_IntMaskStatus |= Hwacc_IntMaskTable[IntType];
        Hwacc_RegWPtr->HWACC_INTR_ENABLE |= Hwacc_IntMaskTable[IntType];
    }
    else
    {
        Hwacc_RegWPtr->HWACC_INTR_ENABLE &= (~Hwacc_IntMaskTable[IntType]);
        Hwacc_IntMaskStatus &= (~Hwacc_IntMaskTable[IntType]);
    }     
}

/**
 * @brief     Clear interrupt state
 *
 * @param[in] IntType: Interrupt type.
 *
 * @return    none.
 * 
 */
void Hwacc_ClearIntStatus(Hwacc_IntType IntType)
{
    switch (IntType)
    {
        case HWACC_INT_CLARK_TRANS: 
        case HWACC_INT_PARK_TRANS:
        case HWACC_INT_PI_CURRENTD:
        case HWACC_INT_PI_CURRENTQ:
        case HWACC_INT_INV_PARK:
        case HWACC_INT_INV_CLARK:
        case HWACC_INT_MATHCMD:
        case HWACC_INT_DIV_NAN:
        case HWACC_INT_OVERFLOW:
        case HWACC_INT_SQR_ERR:
        case HWACC_INT_UNDERFLOW:
        case HWACC_INT_ALL:
            Hwacc_RegWPtr->HWACC_INTR_STATE |= Hwacc_IntClearTable[IntType];
            break;
                    
        default:
            /* do nothing */
            break;
    }        
}

/**
 * @brief     Set  operation  type and  mode
 *
 * @param[in] MathOpType:  Hwacc math operation  type: refer to  Hwacc_MathOperationType.
 * @param[in] FocOpType :  Hwacc Foc controller operation  type: refer to Hwacc_FocOperationType
 * @param[in] OpModeType:  Hwacc operation mode  type: HWACC_MATH_MODE,HWACC_FOC_MODE.
 *
 * @return    none.
 * 
 */
void Hwacc_SetOperationCode(Hwacc_MathOperationType MathOpType, Hwacc_FocOperationType FocOpType, 
                        Hwacc_OperationModeType OpModeType)
{
    Hwacc_RegBfPtr->HWACC_CTRL_OP.DECODE_MACHINE = (uint32)OpModeType;
    
    if( OpModeType == HWACC_MATH_MODE)
    {
        Hwacc_RegBfPtr->HWACC_CTRL_OP.DECODE_OPCODE = (uint32) MathOpType;
    }
    else if( OpModeType == HWACC_FOC_MODE)
    {
        Hwacc_RegBfPtr->HWACC_CTRL_OP.DECODE_OPCODE = (uint32) FocOpType;
    }
    else
    {
        /* do nothing */
    }   
}

/**
 * @brief     Machine Run enable/disable Cmd for FOC and Math mode
 *
 * @param[in] Common_ControlStateType : COMMON_DISABLE,COMMON_ENABLE.
 *
 * @return    none.
 * 
 */
void Hwacc_EnableMachineRun(Common_ControlStateType Cmd)
{
    Hwacc_RegBfPtr->HWACC_CTRL_RUN.MACHINE_GO = (uint32)Cmd;
}

/**
 * @brief     Hwacc Reset Foc.
 *
 * @param[in] none.
 *
 * @return    none.
 * 
 */
void Hwacc_ResetFoc(void)
{
    Hwacc_RegBfPtr->HWACC_CTRL_RUN.FOC_STATE_RST = 1U;
}

/**
 * @brief    Get Foc  Status 
 *
 * @param[in]  none.
 *
 * @return     Hwacc_FocStatusType .
 * @retval     Refer to Hwacc_FocStatusType definition.    
 * 
 */
Hwacc_FocStatusType Hwacc_GetFocStatus(void)
{
   return (Hwacc_FocStatusType)Hwacc_RegBfPtr->HWACC_STATUS.FOC_FSM_STATE;  
}

/**
 * @brief    Get Math status 
 *
 * @param[in]  none.
 *
 * @return     Hwacc_MathStatusType.
 * @retval     MATH_BUSY : math is busy .
 * @retval     MATH_IDLE : math is idle . 
 * 
 */
Hwacc_MathStatusType Hwacc_GetMathStatus(void)
{
    return (Hwacc_MathStatusType)Hwacc_RegBfPtr->HWACC_STATUS.ALU_BUSY;  
}

/**
 * @brief    Set Inverse Clarke Mode
 *
 * @param[in] ModeSel: Hwacc  inverse clarke transform mode: 
 *                          - HWACC_VR0_EQUAL_VBETA  
 *                          - HWACC_VR0_EQUAL_VALPHA 
 * @return    none. 
 * 
 */
void Hwacc_SetInverseClarkeMode(Hwacc_InverseClarkeModeType ModeSel)
{
    Hwacc_RegBfPtr->HWACC_FOC_CFG.SET_VR0 = (uint32)ModeSel;
}

/**
 * @brief     Voltage Normalization  bypass cmd
 *
 * @param[in]  Cmd:Common_ControlStateType,COMMON_DISABLE,COMMON_ENABLE.
 *
 * @return    none. 
 * 
 */
void Hwacc_EnableVoltageNormalizationBypass(Common_ControlStateType Cmd)
{
    Hwacc_RegBfPtr->HWACC_FOC_CFG.BYPASS_PU = (uint32)Cmd;
}

/**
 * @brief      Set Clarke transform Result.
 *
 * @param[in]  ClarkeResultVal :   Clarke transform Result, ClarkeResultIalpha, ClarkeResultIbeta.
 *
 * @return    none. 
 * 
 */
void Hwacc_SetClarkeTransformResult(Hwacc_FocClarkeResultType ClarkeResultVal)
{
    Hwacc_RegBfPtr->HWACC_FOC_CLARKE_RES.IA= (uint32)ClarkeResultVal.ClarkeResultIalpha;
    Hwacc_RegBfPtr->HWACC_FOC_CLARKE_RES.IB= (uint32)ClarkeResultVal.ClarkeResultIbeta;
}

/**
 * @brief      Set Park  transform Current Result.
 *
 * @param[in]  ParkCurrentResultVal :   ParkResultId, ParkResultIq.
 *
 * @return    none. 
 * 
 */
void Hwacc_SetParkTransformCurrentResult(Hwacc_FocParkCurrentResultType ParkCurrentResultVal)
{
    Hwacc_RegBfPtr->HWACC_FOC_PARK_RES0.ID= (uint32)ParkCurrentResultVal.ParkResultId;
    Hwacc_RegBfPtr->HWACC_FOC_PARK_RES0.IQ= (uint32)ParkCurrentResultVal.ParkResultIq;
}

/**
 * @brief      Set Park  transform sincos Result.
 *
 * @param[in]  ParkSinCosResultVal : ParkResultSinTheta, ParkResultCosTheta.
 *
 * @return    none. 
 * 
 */
void Hwacc_SetParkTransformSinCosResult(Hwacc_FocParkSinCosResultType ParkSinCosResultVal)
{
    Hwacc_RegBfPtr->HWACC_FOC_PARK_RES1.COS = (uint32)ParkSinCosResultVal.ParkResultCosTheta;
    Hwacc_RegBfPtr->HWACC_FOC_PARK_RES1.SIN= (uint32)ParkSinCosResultVal.ParkResultSinTheta;
}

/**
 * @brief      Set  PI controller Output result.
 *
 * @param[in]  PiOutputVal :  PiResultVd, PiResultVq.
 *
 * @return    none. 
 * 
 */
void Hwacc_SetPiOutputResult(Hwacc_FocPiOutputResultType PiOutputVal)
{
    Hwacc_RegBfPtr->HWACC_FOC_PI_RES.VD  = (uint32)PiOutputVal.PiResultVd;
    Hwacc_RegBfPtr->HWACC_FOC_PI_RES.VQ  = (uint32)PiOutputVal.PiResultVq;
}

/**
 * @brief      Set  PI Intergration Input 
 *
 * @param[in]  PiIntergrationVal :  PiIntergrationVd, PiIntergrationVq.
 *
 * @return    none. 
 * 
 */
void Hwacc_SetPiIntergrationInput(Hwacc_FocPiIntergrationInputType PiIntergrationVal)
{
    Hwacc_RegBfPtr->HWACC_FOC_I_VQ.I_VQ  = (uint32)PiIntergrationVal.PiIntergrationVq;
    Hwacc_RegBfPtr->HWACC_FOC_I_VD.I_VD  = (uint32)PiIntergrationVal.PiIntergrationVd;
}

/**
 * @brief      Set Inverse Clarke transform Result.
 *
 * @param[in]  InvClarkeVal :  InverseClarkeResultVR1, InverseClarkeResultVR2
 *
 * @return    none. 
 * 
 */
void Hwacc_SetInverseClarkeTransformResult(Hwacc_FocInvClarkeResultType InvClarkeVal)
{
    Hwacc_RegBfPtr->HWACC_FOC_INV_CLARKE_RES.VR1  = (uint32)InvClarkeVal.InverseClarkeResultVR1;
    Hwacc_RegBfPtr->HWACC_FOC_INV_CLARKE_RES.VR2  = (uint32)InvClarkeVal.InverseClarkeResultVR2;
}

/**
 * @brief      Set Inverse Park transform Result.
 *
 * @param[in]  InvParkVal :  InverseParkValpha, InverseParkVbeta.
 *
 * @return    none. 
 * 
 */
void Hwacc_SetInverseParkTransformResult(Hwacc_FocInvParkResultType InvParkVal)
{
    Hwacc_RegBfPtr->HWACC_FOC_INV_PARK_RES.VA  = (uint32)InvParkVal.InverseParkValpha;
    Hwacc_RegBfPtr->HWACC_FOC_INV_PARK_RES.VB  = (uint32)InvParkVal.InverseParkVbeta;
}

/**
 * @brief      Set Inverse Park Normalization transform Result.
 *
 * @param[in]  InvParkNormalVal :  InverseParkValphaPu, InverseParkVbetaPu.
 *
 * @return    none. 
 * 
 */
void Hwacc_SetInverseParkNormalizationkTransformResult(
                        Hwacc_FocInvParkNormalizationResultType InvParkNormalVal)
{
    Hwacc_RegBfPtr->HWACC_FOC_PU_RES.VA_PU = (uint32)InvParkNormalVal.InverseParkValphaPu;
    Hwacc_RegBfPtr->HWACC_FOC_PU_RES.VB_PU  = (uint32)InvParkNormalVal.InverseParkVbetaPu;
}

/**
 * @brief      Set park transform input  parameter.theta
 *
 * @param[in]   Theta: sint16,  -32768:-pi,   32767:pi.
 *
 * @return    none. 
 * 
 */
void Hwacc_SetParkTransformInputTheta(sint16 Theta)
{
    Hwacc_RegBfPtr->HWACC_FOC_CFG.THETA = (uint32)Theta;
}

/**
 * @brief      Set PI controller current reference
 *
 * @param[in]  CurrentType: 
 *                      - Hwacc_CurrentControllerType 
 *                      - HWACC_IQ_CURRENT_CONTROLLER 
 *                      - HWACC_ID_CURRENT_CONTROLLER
 * @param[in]  Val:  current reference value.
 *
 * @return    none. 
 * 
 */
void Hwacc_SetPiControllerCurrentReference(Hwacc_CurrentControllerType CurrentType, sint16 Val)
{
    switch (CurrentType)
    {
        case HWACC_IQ_CURRENT_CONTROLLER:
            Hwacc_RegBfPtr->HWACC_FOC_IREF.IQ_REF = (uint32)Val;
            break;
          
        case HWACC_ID_CURRENT_CONTROLLER:
            Hwacc_RegBfPtr->HWACC_FOC_IREF.ID_REF = (uint32)Val;
            break;
        default:
            /* do nothing */
            break; 
    }
}

/**
 * @brief      Set PI controller Kp parameter
 *
 * @param[in]  CurrentType: 
 *                      - Hwacc_CurrentControllerType 
 *                      - HWACC_IQ_CURRENT_CONTROLLER 
 *                      - HWACC_ID_CURRENT_CONTROLLER
 * @param[in]  Val:  Kp value.
 *
 * @return    none. 
 * 
 */
void Hwacc_SetPiControllerKp(Hwacc_CurrentControllerType CurrentType, sint16 Val)
{
    switch (CurrentType)
    {
        case HWACC_IQ_CURRENT_CONTROLLER:
            Hwacc_RegBfPtr->HWACC_FOC_IKP.IQ_KP= (uint32)Val;
            break;
          
        case HWACC_ID_CURRENT_CONTROLLER:
            Hwacc_RegBfPtr->HWACC_FOC_IKP.ID_KP = (uint32)Val;
            break;
        default:
            /* do nothing */
            break; 
    }
}

/**
 * @brief      Set PI controller Ki parameter
 *
 * @param[in]  CurrentType: 
 *                      - Hwacc_CurrentControllerType 
 *                      - HWACC_IQ_CURRENT_CONTROLLER 
 *                      - HWACC_ID_CURRENT_CONTROLLER
 * @param[in]  Val:  Ki value.
 *
 * @return    none. 
 * 
 */
void Hwacc_SetPiControllerKi(Hwacc_CurrentControllerType CurrentType, sint16 Val)
{
    switch (CurrentType)
    {
        case HWACC_IQ_CURRENT_CONTROLLER:
            Hwacc_RegBfPtr->HWACC_FOC_IKI.IQ_KI= (uint32)Val;
            break;
          
        case HWACC_ID_CURRENT_CONTROLLER:
            Hwacc_RegBfPtr->HWACC_FOC_IKI.ID_KI = (uint32)Val;
            break;
        default:
            /* do nothing */
            break; 
    }
}

/**
 * @brief      Set Id PI controller Intergration output max limit 
 *
 * @param[in]  Val:   Intergration max limit
 *
 * @return    none. 
 * 
 */
void Hwacc_SetIdPiControllerIntergrationMaxLimit(sint32 Val)
{
    Hwacc_RegBfPtr->HWACC_FOC_I_ID_MAX.ID_I_MAX = (uint32)Val;
}

/**
 * @brief      Get Iq PI controller Intergration output max limit 
 *
 * @param[in]  none. 
 *
 * @return    Intergration max limit. 
 * 
 */
sint32  Hwacc_GetIqPiControllerIntergrationMaxLimit(void)
{
    return (sint32)Hwacc_RegBfPtr->HWACC_FOC_I_IQ_MAX.IQ_I_MAX;
}

/**
 * @brief      Set Id PI controller Intergration output min limit 
 *
 * @param[in]  Val:   Intergration min limit 
 *
 * @return    none. 
 * 
 */
void Hwacc_SetIdPiControllerIntergrationMinLimit(sint32 Val)
{
    Hwacc_RegBfPtr->HWACC_FOC_I_ID_MIN.ID_I_MIN  = (uint32)Val;
}

/**
 * @brief      Get Iq PI controller Intergration output min limit 
 *
 * @param[in]  none.   
 *
 * @return    Intergration min limit . 
 * 
 */
sint32  Hwacc_GetIqPiControllerIntergrationMinLimit(void)
{
    return (sint32)Hwacc_RegBfPtr->HWACC_FOC_I_IQ_MIN.IQ_I_MIN;
}

/**
 * @brief      Set Voltage normalize BaseValue.
 *
 * @param[in]  Val:    Voltage normalize BaseValue. 
 *
 * @return    none. 
 * 
 */
void Hwacc_SetVoltageNormalizeBaseValue(sint16 Val)
{
    Hwacc_RegBfPtr->HWACC_FOC_VS_BASE.VS_BASE = (uint32)Val;
}

/**
 * @brief      Set  Id PI controller out max limit  
 *
 * @param[in]  Val:   out max limit. 
 *
 * @return    none. 
 * 
 */
void Hwacc_SetIdPiControllerOutMaxLimit(sint16 Val)
{
    Hwacc_RegBfPtr->HWACC_FOC_ID_LIMIT.ID_PI_MAX = (uint32)Val;
}

/**
 * @brief      Get  Iq PI controller out max limit  
 *
 * @param[in]  none.
 *
 * @return    out max limit. 
 * 
 */
sint16  Hwacc_GetIqPiControllerOutMaxLimit(void)
{
    return (sint16)Hwacc_RegBfPtr->HWACC_FOC_IQ_LIMIT.IQ_PI_MAX;
}

/**
 * @brief      Set Id PI controller out min limit  
 *
 * @param[in]  Val:   out min limit. 
 *
 * @return    none. 
 * 
 */
void Hwacc_SetIdPiControllerOutMinLimit(sint16 Val)
{
    Hwacc_RegBfPtr->HWACC_FOC_ID_LIMIT.ID_PI_MIN = (uint32)Val;
}

/**
 * @brief      Get Iq PI controller out min limit  
 *
 * @param[in]  none.    
 *
 * @return    out min limit. 
 * 
 */
sint16  Hwacc_GetIqPiControllerOutMinLimit(void)
{
    return (sint16)Hwacc_RegBfPtr->HWACC_FOC_IQ_LIMIT.IQ_PI_MIN;
}

/**
 * @brief      Set Foc voltage  max limit 
 *
 * @param[in]  Val:   Voltage max value. 
 *
 * @return    none. 
 * 
 */
void Hwacc_SetFocVoltageMaxLimit(sint16 Val)
{
    Hwacc_RegBfPtr->HWACC_FOC_VS_MAX.VS_MAX = (uint32)Val;
}

/**
 * @brief      Get  Foc Output Value.   
 *
 * @param[in]   OutputType :Foc Output Type, refer to Hwacc_FocOutputType definition.
 *
 * @return     Foc Output Value, sint16. 
 * 
 */
sint16 Hwacc_GetFocOutput(Hwacc_FocOutputType OutputType)
{
    uint16 Val = 0U;
    uint32 TempVal = 0U;
    volatile uint32 * const ValAddrTable[(uint32)HWACC_FOC_NORMALIZE_VBPU_RESULT + 1U] = {
        &Hwacc_RegWPtr->HWACC_FOC_CLARKE_RES,
        &Hwacc_RegWPtr->HWACC_FOC_CLARKE_RES,
        &Hwacc_RegWPtr->HWACC_FOC_PARK_RES0,
        &Hwacc_RegWPtr->HWACC_FOC_PARK_RES0,
        &Hwacc_RegWPtr->HWACC_FOC_PARK_RES1,
        &Hwacc_RegWPtr->HWACC_FOC_PARK_RES1,
        &Hwacc_RegWPtr->HWACC_FOC_PI_RES,
        &Hwacc_RegWPtr->HWACC_FOC_PI_RES,
        &Hwacc_RegWPtr->HWACC_FOC_INV_CLARKE_RES,
        &Hwacc_RegWPtr->HWACC_FOC_INV_CLARKE_RES,
        &Hwacc_RegWPtr->HWACC_FOC_INV_PARK_RES,
        &Hwacc_RegWPtr->HWACC_FOC_INV_PARK_RES,
        &Hwacc_RegWPtr->HWACC_FOC_PU_RES,
        &Hwacc_RegWPtr->HWACC_FOC_PU_RES
    };
  
    switch (OutputType)
    {
        case HWACC_FOC_CLARK_IALPHA_RESULT:
        case HWACC_FOC_CLARK_IBETA_RESULT:
        case HWACC_FOC_PARK_IQ_RESULT:
        case HWACC_FOC_PARK_ID_RESULT:
        case HWACC_FOC_PARK_COSTHETA_RESULT:
        case HWACC_FOC_PARK_SINTHETA_RESULT:
        case HWACC_FOC_PI_VQ_RESULT:
        case HWACC_FOC_PI_VD_RESULT:
        case HWACC_FOC_INVERSE_CLARKE_VR1_RESULT:
        case HWACC_FOC_INVERSE_CLARKE_VR2_RESULT:
        case HWACC_FOC_INVERSE_PARK_VA_RESULT:
        case HWACC_FOC_INVERSE_PARK_VB_RESULT:
        case HWACC_FOC_NORMALIZE_VAPU_RESULT:
        case HWACC_FOC_NORMALIZE_VBPU_RESULT:
            /* If OutputType mod 2 equal 1, value right shift 16 bits */
            TempVal = ((*ValAddrTable[OutputType]) >> (((uint32)OutputType & 1U)<<4U));
            Val = (uint16)(TempVal & 0xFFFFU);
            break;            

        default:
            /* do nothing */
            break;            
    }    
    
    return (sint16)Val;
}

/**
 * @brief      Get  Foc PI Intergration Output.
 *
 * @param[in]   IntergrationOutputType: 
 *                                  - HWACC_FOC_PI_INTERGRATION_VQ_RESULT 
 *                                  - HWACC_FOC_PI_INTERGRATION_VD_RESULT
 *
 * @return    Foc Pi Intergration output,sint32.
 * 
 */
sint32 Hwacc_GetFocPIIntergrationOutput(Hwacc_FocPiIntergrationOutputType IntergrationOutputType)
{
    uint32 Val = 0U;
  
    switch (IntergrationOutputType)
    {       
        case HWACC_FOC_PI_INTERGRATION_VQ_RESULT:
            Val = Hwacc_RegBfPtr->HWACC_FOC_I_VQ.I_VQ;
            break;

        case HWACC_FOC_PI_INTERGRATION_VD_RESULT:
            Val = Hwacc_RegBfPtr->HWACC_FOC_I_VD.I_VD;
            break;                      

        default:
            /* do nothing */
            break;            
    }    
    
    return (sint32)Val;
}

/**
 * @brief      Get  Math  output Register Value
 *
 * @param[in]   RegType: 
 *                  - HWACC_MATH_OUT_REG_L_0 
 *                  - HWACC_MATH_OUT_REG_H_0 
 *                  - HWACC_MATH_OUT_REG_L_1 
 *                  - HWACC_MATH_OUT_REG_H_1
 *
 * @return    Output value.
 * 
 */
sint16 Hwacc_GetMathOutputRegisterValue(Hwacc_MathOutputRegisterType RegType)
{
    uint32 Val = 0U;
    switch (RegType)
    {       
        case HWACC_MATH_OUT_REG_L_0:
            Val = Hwacc_RegBfPtr->HWACC_COMPREGS_0.COMP_REG_L_0;
            break;

        case HWACC_MATH_OUT_REG_H_0:
            Val = Hwacc_RegBfPtr->HWACC_COMPREGS_0.COMP_REG_H_0;
            break;                      

        case HWACC_MATH_OUT_REG_L_1:
            Val = Hwacc_RegBfPtr->HWACC_COMPREGS_1.COMP_REG_L_1;
            break;

        case HWACC_MATH_OUT_REG_H_1:
            Val = Hwacc_RegBfPtr->HWACC_COMPREGS_1.COMP_REG_H_1;
            break;
            
        default:
            /* do nothing */
            break;            
    }    
    return (sint16)Val;
}

/**
 * @brief      Set Math Input Register value
 *
 * @param[in]   RegType: 
 *                  - HWACC_MATH_OUT_REG_L_0 
 *                  - HWACC_MATH_OUT_REG_H_0 
 *                  - HWACC_MATH_OUT_REG_L_1 
 *                  - HWACC_MATH_OUT_REG_H_1
 * @param[in]   Val :The Value to set.
 *
 * @return   none.
 * 
 */
void Hwacc_SetMathInputRegisterValue(Hwacc_MathInputRegisterType RegType, sint16 Val)
{
    switch (RegType)
    {       
        case HWACC_MATH_IN_REG0_L:
           Hwacc_RegBfPtr->HWACC_GPREGS_0.GENERAL_REG_L_0 = (uint32)Val;  
            break;

        case HWACC_MATH_IN_REG0_H:
            Hwacc_RegBfPtr->HWACC_GPREGS_0.GENERAL_REG_H_0 = (uint32)Val;  
            break;                      

        case HWACC_MATH_IN_REG1_L:
            Hwacc_RegBfPtr->HWACC_GPREGS_1.GENERAL_REG_L_1 = (uint32)Val;  
            break;

        case HWACC_MATH_IN_REG1_H:
            Hwacc_RegBfPtr->HWACC_GPREGS_1.GENERAL_REG_H_1 = (uint32)Val;  
            break;
            
        default:
            /* do nothing */
            break;            
    } 
}

/**
 * @brief    Set Math Input Data A B C D Address Offset .
 *
 * @param[in] InputDataNum : Hwacc Math Input Data Number:A,B,C,D.
 * @param[in] AdrrOffSet: Math Input Data Address Offset to HWACC_MATH_IN_REG0_L, max value is 0x3.
 *
 * @return    none.
 * 
 */
void Hwacc_SetMathInputDataABCDAddressOffset(Hwacc_MathInputDataNumType InputDataNum, 
                                            uint8 AdrrOffSet)
{
   uint32 regVal = Hwacc_RegWPtr->HWACC_INBASE;

   AdrrOffSet = AdrrOffSet > 0x3U ? 0x3U : AdrrOffSet;    
   
   Hwacc_RegWPtr->HWACC_INBASE = regVal | ((uint32)AdrrOffSet << ((uint32)InputDataNum*8UL));  
}

/**
 * @brief       Hwacc install interrupt callback function
 *
 * @param[in]  IntType:    Select interrupt type.
 * @param[in]  CbFun:      Callback function .
 *
 * @return none
 *
 */
void Hwacc_InstallCallBackFunc(Hwacc_IntType IntType, Isr_CbFuncType * CbFun)
{
    if(HWACC_INT_ALL > IntType) 
    {
        Hwacc_IsrCbFunc[IntType] = CbFun;
    }
}

/**
 * @brief       Hwacc Foc Init Function .
 *
 * @param[in]   Config: Foc Config Parameters.
 *
 * @return none
 *
 */
void Hwacc_InitFoc(Hwacc_FocParameterConfigType *Config)
{
    /*Foc Reset*/
    Hwacc_RegBfPtr->HWACC_CTRL_RUN.FOC_STATE_RST = 1U;
    /*Disable All Int*/
    Hwacc_RegWPtr->HWACC_INTR_ENABLE &= (~Hwacc_IntMaskTable[HWACC_INT_ALL]);
    /*Clear All  Status*/
    Hwacc_RegWPtr->HWACC_INTR_STATE = Hwacc_IntClearTable[HWACC_INT_ALL];
    /* Set Operation Mode to FOC */
    Hwacc_RegBfPtr->HWACC_CTRL_OP.DECODE_MACHINE = (uint32)HWACC_FOC_MODE;
    /* Wait,No operation to do*/
    Hwacc_RegBfPtr->HWACC_CTRL_OP.DECODE_OPCODE = (uint32)HWACC_NO_OPERATION;
 
    /*Set Foc Init  Parameters */
    Hwacc_RegBfPtr->HWACC_FOC_CFG.BYPASS_PU = (uint32)Config->EnableVoltageNormalizationBypass;
    Hwacc_RegBfPtr->HWACC_FOC_VS_BASE.VS_BASE = (uint32)Config->VoltageNormalizeBaseValue;
    Hwacc_RegBfPtr->HWACC_FOC_CFG.SET_VR0 = (uint32)Config->InverseClarkeMode;
    Hwacc_SetPiControllerKp(HWACC_IQ_CURRENT_CONTROLLER,Config->IqKp);
    Hwacc_SetPiControllerKi(HWACC_IQ_CURRENT_CONTROLLER,Config->IqKi);
    Hwacc_SetPiControllerKp(HWACC_ID_CURRENT_CONTROLLER,Config->IdKp);
    Hwacc_SetPiControllerKi(HWACC_ID_CURRENT_CONTROLLER,Config->IdKi);
    Hwacc_RegBfPtr->HWACC_FOC_VS_MAX.VS_MAX = (uint32)Config->VoltageMaxLimit;
    Hwacc_RegBfPtr->HWACC_FOC_I_ID_MAX.ID_I_MAX = (uint32)Config->IdPiControllerIntergrationMaxLimit;
    Hwacc_RegBfPtr->HWACC_FOC_I_ID_MIN.ID_I_MIN  = (uint32)Config->IdPiControllerIntergrationMinLimit;
    Hwacc_RegBfPtr->HWACC_FOC_ID_LIMIT.ID_PI_MAX = (uint32)Config->IdPiControllerOutMaxLimit;
    Hwacc_RegBfPtr->HWACC_FOC_ID_LIMIT.ID_PI_MIN = (uint32)Config->IdPiControllerOutMinLimit;
}

/**
 * @brief       Hwacc Start Foc Clarke Transform From Ia/Ib/Ic To Ialpha/Ibeta  
 *
 * @param[in]  ClarkeInput: ClarkeInputIa, ClarkeInputIb, 
 *                          ClarkeInputIa + ClarkeInputIb + ClarkeInputIc = 0.
 *
 * @return none.
 *
 */
void Hwacc_StartFocClarkeTransform(Hwacc_FocClarkeInputType ClarkeInput)
{
    /* Foc Reset*/
    Hwacc_RegBfPtr->HWACC_CTRL_RUN.FOC_STATE_RST = 1U;
    /* Clear Clarke transform ends  Status*/
    Hwacc_RegWPtr->HWACC_INTR_STATE = 0x01U;          
    /* Set Clarke Input  Parameter Ia,Ib*/
    Hwacc_RegBfPtr->HWACC_GPREGS_0.GENERAL_REG_L_0 = (uint32)ClarkeInput.ClarkeInputIa;  
    Hwacc_RegBfPtr->HWACC_GPREGS_0.GENERAL_REG_H_0 = (uint32)ClarkeInput.ClarkeInputIb; 
    /* Set Operation Mode to CLARKE */
    Hwacc_RegBfPtr->HWACC_CTRL_OP.DECODE_OPCODE = (uint32)HWACC_FOC_CLARKE_OPERATION;
    /* Start to  Run*/
    Hwacc_RegBfPtr->HWACC_CTRL_RUN.MACHINE_GO = (uint32)COMMON_ENABLE;
    
}

/**
 * @brief       Hwacc   Get Foc Clarke Transform  Result .
 *
 * @param[in]  TimeOutVal:  ClarkeTransform TimeOutValue
 *
 * @return ClarkeResult :ClarkeResultIalpha, ClarkeResultIbeta.
 *
 */
Hwacc_FocClarkeResultType Hwacc_GetFocClarkeTransformResult(uint32 TimeOutVal)
{
    static Hwacc_FocClarkeResultType ClarkeResult ={(sint16)0,(sint16)0};
    volatile uint32 ClarkeLocalCount = 0U;
    while((Common_IntStatusType)Hwacc_RegBfPtr->HWACC_INTR_STATE.CLARK_TRANS == COMMON_RESET)
    {
        ClarkeLocalCount++;
        if(ClarkeLocalCount >= TimeOutVal)
        {
            break;
        }
    }    
    if(ClarkeLocalCount < TimeOutVal)
    {
        ClarkeResult.ClarkeResultIalpha = (sint16)Hwacc_RegBfPtr->HWACC_FOC_CLARKE_RES.IA;
        ClarkeResult.ClarkeResultIbeta  = (sint16)Hwacc_RegBfPtr->HWACC_FOC_CLARKE_RES.IB;  
    }
    
    return ClarkeResult;   
}

/**
 * @brief       Hwacc   Start Foc Park to Inverse Clarke Transform. 
 *
 * @param[in]  ClarkeResult: ClarkeResultIalpha, ClarkeResultIbeta.
 * @param[in]   Theta:  sint16 , -32768:-pi, 32767:pi.
 * @param[in]  CurrentRef:   IdRef,IqRef.
 *
 * @return none.
 */
void Hwacc_StartFocParkToInverseClarkeTransform(
                    Hwacc_FocClarkeResultType ClarkeResult, 
                    sint16 Theta, Hwacc_FocCurrentReferenceType CurrentRef)
{
    /* Foc Reset*/
    Hwacc_RegBfPtr->HWACC_CTRL_RUN.FOC_STATE_RST = 1U;
    /* Clear  park &  pivd & pivq & invpark & invclarke ends Status*/
    Hwacc_RegWPtr->HWACC_INTR_STATE = 0x7EU;
    /* Set Operation Mode to park &  pivd & pivq & invpark & invclarke operation  */
    Hwacc_RegBfPtr->HWACC_CTRL_OP.DECODE_OPCODE = 
                            (uint32)HWACC_FOC_PARK_PIVD_PIVQ_INVPARK_INVCLARKE_OPERATION;
    /*Set Input Parameter */
    Hwacc_RegBfPtr->HWACC_FOC_CLARKE_RES.IA= (uint32)ClarkeResult.ClarkeResultIalpha;
    Hwacc_RegBfPtr->HWACC_FOC_CLARKE_RES.IB= (uint32)ClarkeResult.ClarkeResultIbeta;
    Hwacc_RegBfPtr->HWACC_FOC_CFG.THETA = (uint32)Theta;
    Hwacc_RegBfPtr->HWACC_FOC_IREF.IQ_REF = (uint32)CurrentRef.IqRef;
    Hwacc_RegBfPtr->HWACC_FOC_IREF.ID_REF = (uint32)CurrentRef.IdRef;
    /* Start to  Run*/
    Hwacc_RegBfPtr->HWACC_CTRL_RUN.MACHINE_GO = (uint32)COMMON_ENABLE;
    
}

/**
 * @brief       Hwacc   Get Foc Inverse Clarke Transform  Result .
 *
 * @param[in]  TimeOutVal: Inverse Clarke Transform TimeOutValue
 *
 * @return InvClarkeResult : InverseClarkeResultVR1, InverseClarkeResultVR2, InverseClarkeResultVR3.
 */
Hwacc_FocInvClarkeResultType Hwacc_GetFocInverseClarkeTransformResult(uint32 TimeOutVal)
{
    volatile  uint32 LocalCount = 0U;
    static Hwacc_FocInvClarkeResultType InvClarkeResult = {(sint16)0,(sint16)0,(sint16)0};
    /*Get InvClarke Result*/    
    while((Common_IntStatusType)Hwacc_RegBfPtr->HWACC_INTR_STATE.INV_CLARK == COMMON_RESET)
    {
        LocalCount++;
        if(LocalCount >= TimeOutVal)
        {
            break;
        }
    }    
   
    if(LocalCount < TimeOutVal)
    {
        InvClarkeResult.InverseClarkeResultVR1 = (sint16)Hwacc_RegBfPtr->HWACC_FOC_INV_CLARKE_RES.VR1;
        InvClarkeResult.InverseClarkeResultVR2 = (sint16)Hwacc_RegBfPtr->HWACC_FOC_INV_CLARKE_RES.VR2; 
        InvClarkeResult.InverseClarkeResultVR0 = 
                -(InvClarkeResult.InverseClarkeResultVR1+InvClarkeResult.InverseClarkeResultVR2);
    }
    
    return InvClarkeResult;
}

/**
 * @brief       Hwacc   Start Foc Clarke to Inverse Clarke Transform. 
 *
 * @param[in]  ClarkeInput:  ClarkeInputIa , ClarkeInputIb, 
 *                          ClarkeInputIa +ClarkeInputIb + ClarkeInputIc = 0.
 * @param[in]   Theta: sint16,  -32768:-pi,   32767:pi
 * @param[in]  CurrentRef:   IdRef,IqRef.
 *
 * @return none.
 */
void Hwacc_StartFocClarkeToInverseClarkeTransform(Hwacc_FocClarkeInputType ClarkeInput, 
                        sint16 Theta, Hwacc_FocCurrentReferenceType CurrentRef)
{

    /*Foc Reset*/
    Hwacc_RegBfPtr->HWACC_CTRL_RUN.FOC_STATE_RST = 1U;
    /*Clear clarke & park &  pivd & pivq & invpark & invclarke ends Status*/
    Hwacc_RegWPtr->HWACC_INTR_STATE = 0x7FU;
    /* Set Operation Mode to clarke & park &  pivd & pivq & invpark & invclarke opreation */
    Hwacc_RegBfPtr->HWACC_CTRL_OP.DECODE_OPCODE = 
                        (uint32)HWACC_FOC_CLARKE_PARK_PIVD_PIVQ_INVPARK_INVCLARKE_OPERATION;
    /*Set Input Parameter */
    Hwacc_RegBfPtr->HWACC_GPREGS_0.GENERAL_REG_L_0 = (uint32)ClarkeInput.ClarkeInputIa;  
    Hwacc_RegBfPtr->HWACC_GPREGS_0.GENERAL_REG_H_0 = (uint32)ClarkeInput.ClarkeInputIb; 
    Hwacc_RegBfPtr->HWACC_FOC_CFG.THETA = (uint32)Theta;
    Hwacc_RegBfPtr->HWACC_FOC_IREF.IQ_REF = (uint32)CurrentRef.IqRef;
    Hwacc_RegBfPtr->HWACC_FOC_IREF.ID_REF = (uint32)CurrentRef.IdRef;
    /* Start to  Run*/
    Hwacc_RegBfPtr->HWACC_CTRL_RUN.MACHINE_GO = (uint32)COMMON_ENABLE;
   
}

/**
 * @brief       Hwacc Math Init Function .
 *
 * @param[in]   none.
 *
 * @return none
 *
 */
void Hwacc_InitMath(void)
{
    /*Diable All Int*/
    Hwacc_RegWPtr->HWACC_INTR_ENABLE &= (~Hwacc_IntMaskTable[HWACC_INT_ALL]);
    /*Clear All  Status*/
    Hwacc_RegWPtr->HWACC_INTR_STATE = Hwacc_IntClearTable[HWACC_INT_ALL];
    /* Set Operation Mode to Math */
    Hwacc_RegBfPtr->HWACC_CTRL_OP.DECODE_MACHINE = (uint32)HWACC_MATH_MODE;
    /* Wait,No operation to do*/
    Hwacc_RegBfPtr->HWACC_CTRL_OP.DECODE_OPCODE = (uint32)HWACC_NO_OPERATION; 
    /*Set Math Input Data A/B/C/D Address Offset   */
    Hwacc_SetMathInputDataABCDAddressOffset(HWACC_MATH_INPUT_DATA_A,(uint8)0);
    Hwacc_SetMathInputDataABCDAddressOffset(HWACC_MATH_INPUT_DATA_B,(uint8)0);
    Hwacc_SetMathInputDataABCDAddressOffset(HWACC_MATH_INPUT_DATA_C,(uint8)0);
    Hwacc_SetMathInputDataABCDAddressOffset(HWACC_MATH_INPUT_DATA_D,(uint8)0);
}

/**
 * @brief       Hwacc Math Start SinCos Transform .
 *
 * @param[in]   Theta: sint16,  -32768:-pi,   32767:pi.
 * @param[in]   TimeOutVal: Wait Math To Idle TimeOutValue.
 *
 * @return none
 *
 */
void Hwacc_StartMathSinCosTransform(sint16 Theta, uint32 TimeOutVal)
{
    volatile  uint32 LocalCount = 0U;
    /*Wait Math to Idle*/
    while(Hwacc_RegBfPtr->HWACC_STATUS.ALU_BUSY == (uint32)HWACC_MATH_STATE_BUSY)
    {
        LocalCount++;
        if(LocalCount >= TimeOutVal)
        {
            break;
        }
        
    } 
    /*Clear Math Cmd  ends  Status*/
    Hwacc_RegWPtr->HWACC_INTR_STATE = Hwacc_IntClearTable[HWACC_INT_MATHCMD];
    /* Get Theta  */
    Hwacc_RegBfPtr->HWACC_GPREGS_0.GENERAL_REG_L_0 = (uint32)Theta;
    /* Set Operation Mode  to SinCos Mode */
    Hwacc_RegBfPtr->HWACC_CTRL_OP.DECODE_OPCODE =  (uint32)HWACC_CORDIC_SINCOS_OPERATION;
    /* Start to  Run*/
    Hwacc_RegBfPtr->HWACC_CTRL_RUN.MACHINE_GO = (uint32)COMMON_ENABLE;

}

/**
 * @brief       Hwacc Get Math SinCos Transform Result.
 *
 * @param[in]   TimeOutVal: SinCos Transform TimeOutValue.
 *
 * @return      SinCosResult:CosResult,SinResult,sint16.
 *
 */
Hwacc_MathSinCosResultType Hwacc_GetMathSinCosTransformResult(uint32 TimeOutVal)
{
    volatile  uint32 LocalCount = 0U;
    static Hwacc_MathSinCosResultType SinCosResult = {(sint16)0, (sint16)0};
    while(Hwacc_RegBfPtr->HWACC_STATUS.ALU_BUSY == (uint32)HWACC_MATH_STATE_BUSY)
    {
        LocalCount++;
        if(LocalCount >= TimeOutVal)
        {
            break;
        }
    } 
    if(LocalCount < TimeOutVal)
    {
        SinCosResult.CosResult = (sint16)Hwacc_RegBfPtr->HWACC_COMPREGS_0.COMP_REG_L_0;
        SinCosResult.SinResult = (sint16)Hwacc_RegBfPtr->HWACC_COMPREGS_0.COMP_REG_H_0; 
    }

    return SinCosResult;
}

/**
 * @brief       Hwacc Math Start Arctan Transform .
 *
 * @param[in]   A:  tan(theta), -32768:tan(-pi), 32767:tan(pi).
 * @param[in]   TimeOutVal: Wait Math To Idle TimeOutValue.
 *
 * @return none
 *
 */
void Hwacc_StartMathArctanTransform(sint16 A, uint32 TimeOutVal)
{
    volatile  uint32 LocalCount = 0U;
    /*Wait Math to Idle*/
    while(Hwacc_RegBfPtr->HWACC_STATUS.ALU_BUSY == (uint32)HWACC_MATH_STATE_BUSY)
    {
        LocalCount++;
        if(LocalCount >= TimeOutVal)
        {
            break;
        }    
    } 
    /*Clear Math Cmd  ends  Status*/
    Hwacc_RegWPtr->HWACC_INTR_STATE = Hwacc_IntClearTable[HWACC_INT_MATHCMD];
    /* Get A  */
    Hwacc_RegBfPtr->HWACC_GPREGS_0.GENERAL_REG_L_0 = 1U;
    Hwacc_RegBfPtr->HWACC_GPREGS_0.GENERAL_REG_H_0 = (uint32)A;
    /* Set Operation Mode  to Arctan Mode */
    Hwacc_RegBfPtr->HWACC_CTRL_OP.DECODE_OPCODE =  (uint32)HWACC_CORDIC_ARCTAN_OPERATION;
    /* Start to  Run*/
    Hwacc_RegBfPtr->HWACC_CTRL_RUN.MACHINE_GO = (uint32)COMMON_ENABLE;

}

/**
 * @brief       Hwacc Get Math Arctan Transform Result.
 *
 * @param[in]   TimeOutVal: Arctan Transform TimeOutValue.
 *
 * @return      Theta:  sint16 , -32768:-pi, 32767:pi.
 *
 */
sint16 Hwacc_GetMathArctanTransformResult(uint32 TimeOutVal)
{
    volatile  uint32 LocalCount = 0U;
    sint16 ArctanResult = (sint16)0;
    while(Hwacc_RegBfPtr->HWACC_STATUS.ALU_BUSY == (uint32)HWACC_MATH_STATE_BUSY)
    {
        LocalCount++;
        if(LocalCount >= TimeOutVal)
        {
            break;
        }
    } 
    if(LocalCount < TimeOutVal)
    {
        ArctanResult = (sint16)Hwacc_RegBfPtr->HWACC_COMPREGS_1.COMP_REG_L_1;
    }
  
    return ArctanResult;
}

/**
 * @brief       Hwacc Math Start Sqrt Transform .
 *
 * @param[in]   A:Input Data.
 * @param[in]   TimeOutVal: Wait Math To Idle TimeOutValue.
 *
 * @return none
 *
 */
void Hwacc_StartMathSqrtTransform(uint16 A, uint32 TimeOutVal)
{
    volatile  uint32 LocalCount = 0U;
    /*Wait Math to Idle*/
    while(Hwacc_RegBfPtr->HWACC_STATUS.ALU_BUSY == (uint32)HWACC_MATH_STATE_BUSY)
    {
        LocalCount++;
        if(LocalCount >= TimeOutVal)
        {
            break;
        }
        
    } 
    /*Clear Math Cmd  ends  Status*/
    Hwacc_RegWPtr->HWACC_INTR_STATE = Hwacc_IntClearTable[HWACC_INT_MATHCMD];
    /* Get Input Data  */
    Hwacc_RegBfPtr->HWACC_GPREGS_0.GENERAL_REG_L_0 = A;
    /* Set Operation Mode  to Sqrt Mode */
    Hwacc_RegBfPtr->HWACC_CTRL_OP.DECODE_OPCODE =  (uint32)HWACC_SQAURE_ROOT_OPERATION;
    /* Start to  Run*/
    Hwacc_RegBfPtr->HWACC_CTRL_RUN.MACHINE_GO = (uint32)COMMON_ENABLE;
}

/**
 * @brief       Hwacc Get Math Sqrt Transform Result.
 *
 * @param[in]   TimeOutVal: Sqrt Transform TimeOutValue.
 *
 * @return      SqrtResult.
 *
 */
uint16 Hwacc_GetMathSqrtTransformResult(uint32 TimeOutVal)
{
    volatile  uint32 LocalCount = 0U;
    uint16 SqrtResult = (uint16)0;
    while(Hwacc_RegBfPtr->HWACC_STATUS.ALU_BUSY == (uint32)HWACC_MATH_STATE_BUSY)
    {
        LocalCount++;
        if(LocalCount >= TimeOutVal)
        {
            break;
        }  
    } 
    if(LocalCount < TimeOutVal)
    {
        SqrtResult = (uint16)Hwacc_RegBfPtr->HWACC_COMPREGS_0.COMP_REG_L_0;
    }
  
    return SqrtResult;
}

/**
 * @brief       Hwacc Math Start Division Transform .
 *
 * @param[in]   A:Dividend.
 * @param[in]   B:Divisor.
 * @param[in]   TimeOutVal: Wait Math To Idle TimeOutValue.
 *
 * @return none
 *
 */
void Hwacc_StartMathDivisionTransform(sint32 A, sint32 B, uint32 TimeOutVal)
{
    volatile  uint32 LocalCount = 0U;
    /*Wait Math to Idle*/
    while(Hwacc_RegBfPtr->HWACC_STATUS.ALU_BUSY == (uint32)HWACC_MATH_STATE_BUSY)
    {
        LocalCount++;
        if(LocalCount >= TimeOutVal)
        {
            break;
        }
    } 
    /*Clear Math Cmd  ends  Status*/
    Hwacc_RegWPtr->HWACC_INTR_STATE = Hwacc_IntClearTable[HWACC_INT_MATHCMD];
    /* Get Input Data  */
    Hwacc_RegWPtr->HWACC_GPREGS_0 = (uint32)A;
    Hwacc_RegWPtr->HWACC_GPREGS_1 = (uint32)B;
    /* Set Operation Mode  to division Mode */
    Hwacc_RegBfPtr->HWACC_CTRL_OP.DECODE_OPCODE =  (uint32)HWACC_SIGNED_DIVISION_OPERATION;
    /* Start to  Run*/
    Hwacc_RegBfPtr->HWACC_CTRL_RUN.MACHINE_GO = (uint32)COMMON_ENABLE;
}

/**
 * @brief       Hwacc Get Math Division Transform Result.
 *
 * @param[in]   TimeOutVal: Division Transform TimeOutValue.
 *
 * @return      A/B Result.
 *
 */
sint32 Hwacc_GetMathDivisionTransformResult(uint32 TimeOutVal)
{
    uint32 Var;
    uint16 LowVal;
    sint32 DivisionResult = (sint32)0;
    volatile uint32 LocalCount = 0U;
    while(Hwacc_RegBfPtr->HWACC_STATUS.ALU_BUSY == (uint32)HWACC_MATH_STATE_BUSY)
    {
        LocalCount++;
        if(LocalCount >= TimeOutVal)
        {
            break;
        }
        
    } 
    if(LocalCount < TimeOutVal)
    {
        LowVal = (uint16)Hwacc_RegBfPtr->HWACC_COMPREGS_0.COMP_REG_L_0;
        Var = ((uint32)LowVal<<16); 
        Var = (Hwacc_RegBfPtr->HWACC_COMPREGS_0.COMP_REG_H_0 | Var);
        DivisionResult =(sint32)Var;
    }

    return DivisionResult;
   
}

/** @} end of group Public_FunctionDefinition */
