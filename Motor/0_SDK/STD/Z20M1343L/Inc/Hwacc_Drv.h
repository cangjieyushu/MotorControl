/**************************************************************************************************/
/**
 * @file     : Hwacc_Drv.h
 * @brief    : Hwacc module driver header file.
 *              - Platform: Z20M1343L
 * @version  : 0.1.0
 * @date     : May-2023
 * @author   : Zhixin Semiconductor
 * @note     : None   
 *   
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#ifndef Hwacc_DRV_H
#define Hwacc_DRV_H

#include "Common_Drv.h"

/** @addtogroup Public_MacroDefinition
 *  @{
 */

/** @} end of Public_MacroDefinition */

/** @defgroup Public_TypeDefinition
 *  @{
 */

/**
 *  @brief Hwacc Interrupt type definition
 */
typedef enum
{
    HWACC_INT_CLARK_TRANS = 0U,        /*!<  clarke transform ends INT*/
    HWACC_INT_PARK_TRANS,              /*!<  park transform ends INT*/
    HWACC_INT_PI_CURRENTD,             /*!< pi_id currents end INT*/
    HWACC_INT_PI_CURRENTQ,             /*!< pi_iq currents end INT*/
    HWACC_INT_INV_PARK,                /*!< inverse park transform ends INT*/
    HWACC_INT_INV_CLARK,               /*!< inverse clarke transform ends INT*/
    HWACC_INT_MATHCMD,                 /*!< user Math commands execute done INT*/
    HWACC_INT_DIV_NAN,                 /*!< the division calculation result is in infinity INT*/
    HWACC_INT_OVERFLOW,                /*!< the calculation result is more than or equal to 1 INT*/                                                 
    HWACC_INT_SQR_ERR,                 /*!< the rad is negative number INT*/
    HWACC_INT_UNDERFLOW,               /*!< the calculation result is less than -1 INT*/
    HWACC_INT_ALL                      
} Hwacc_IntType;

/**
 *  @brief Hwacc operation mode  type definition
 */
typedef enum
{
    HWACC_MATH_MODE = 0U,              /*!<  Math mode */
    HWACC_FOC_MODE                     /*!< FOC motor controller mode */  
} Hwacc_OperationModeType;


/**
 *  @brief Hwacc Math operation  type definition
 */
typedef enum
{
    HWACC_NO_OPERATION = 0U,                       /*!< No operation*/
    HWACC_CORDIC_SINCOS_OPERATION = 4U,            /*!< CORDIC Sincos: x0 = 1/F , y0= 0 , 
                                                        z0=A ; xn = cos (A) , yn = sin (A) , zn = 0;
                                                        F ~ 1.64 result store 
                                                        HWACC_MATH_OUT_REG_L_0 = xn , 
                                                        HWACC_MATH_OUT_REG_H_0 = yn , 
                                                        HWACC_MATH_OUT_REG_L_1= zn */
    HWACC_SIGNED_DIVISION_OPERATION = 5U,          /*!< Signed division: A / B = res result store 
                                                        HWACC_MATH_OUT_REG_L_0 =high 16bits , 
                                                        HWACC_MATH_OUT_REG_H_0 = low 16 bits */
    HWACC_SQAURE_ROOT_OPERATION = 6U,              /*!< square root: sqrt(A) = res , result store 
                                                        HWACC_MATH_OUT_REG_L_0 = res*/
    HWACC_CORDIC_ARCTAN_OPERATION = 7U            /*!< CORDIC Arctan: x0 = 1, y0 = A, z0 = 0; 
                                                        xn =Fsqrt(1+A^2),yn = 0,  zn = atan(A); 
                                                        F ~ 1.64 result store 
                                                        HWACC_MATH_OUT_REG_L_0 = xn, 
                                                        HWACC_MATH_OUT_REG_H_0 = yn, 
                                                        HWACC_MATH_OUT_REG_L_1 = zn */
} Hwacc_MathOperationType;

/**
 *  @brief Hwacc Foc operation  type definition
 */
typedef enum
{
    HWACC_FOC_NO_OPERATION = 0U,                                       /*!< No operation */
    HWACC_FOC_CLARKE_OPERATION = 1U,                                   /*!< Clarke operation, 
                                                                            in Clark transform, */
    HWACC_FOC_PARK_PIVD_PIVQ_INVPARK_INVCLARKE_OPERATION = 62U,        /*!< park &  pivd & pivq & 
                                                                    invpark & invclarke operation */
    HWACC_FOC_CLARKE_PARK_PIVD_PIVQ_INVPARK_INVCLARKE_OPERATION = 63U  /*!< clarke & park &  pivd & 
                                                            pivq & invpark & invclarke operation */ 
} Hwacc_FocOperationType;

/**
 *  @brief Hwacc  foc  status  type definition
 */
typedef enum
{
    HWACC_FOC_STATE_IDLE = 0U,         /*!<  foc motor controller is on Idle state. 
                                            After foc reset, also on idle state. */
    HWACC_FOC_STATE_CLARKE,            /*!<  foc motor controller is on clarke transform state*/
    HWACC_FOC_STATE_WAIT_ID_RESULT,    /*!<  foc motor controller is on waiting id result state */
    HWACC_FOC_STATE_PARK,              /*!<  foc motor controller is on park transform state*/
    HWACC_FOC_STATE_PI_IQ,             /*!<  foc motor controller is on pi_iq state*/
    HWACC_FOC_STATE_PI_ID,             /*!<  foc motor controller is on pi_id state*/
    HWACC_FOC_STATE_WAIT_IQ_RESULT,    /*!<  foc motor controller is on waiting iq result state*/
    HWACC_FOC_STATE_INV_PARK,          /*!<  foc motor controller is on inv park transform state*/
    HWACC_FOC_STATE_INV_CLARKE,        /*!<  foc motor controller is on inv clarke transform state*/
    HWACC_FOC_STATE_WAIT_PARK_RESULT   /*!<  foc motor controller is on waiting park result state*/
} Hwacc_FocStatusType;

/**
 *  @brief Hwacc  math  status  type definition
 */
typedef enum
{
    HWACC_MATH_STATE_IDLE = 0U,                /*!< math  is idle */
    HWACC_MATH_STATE_BUSY,                     /*!< math is busy*/
} Hwacc_MathStatusType;

/**
 *  @brief Hwacc  inverse clarke transform mode  type definition;
 */
typedef enum
{
    HWACC_VR0_EQUAL_VBETA = 0U,                 /*!<  vr0 = vbeta,vr1=(-vbeta+1.732*valpha)/2,
                                                vr2=(-vbeta-1.732*valpha)/2 */
    HWACC_VR0_EQUAL_VALPHA                      /*!<   vr0 = valpha,vr1=(-valpha+1.732*vbeta)/2,
                                                vr2= (-valpha-1.732*vbeta)/2 */
} Hwacc_InverseClarkeModeType;

/**
 *  @brief Hwacc   Current controller type definition;
 */
typedef enum
{
    HWACC_IQ_CURRENT_CONTROLLER = 0U,                   /*!<   iq current controller */
    HWACC_ID_CURRENT_CONTROLLER                         /*!<   id current controller*/
} Hwacc_CurrentControllerType;

/**
 *  @brief Hwacc  Foc Output type definition;
 */
typedef enum
{
    HWACC_FOC_CLARK_IALPHA_RESULT = 0U,    /*!< FOC motor clark transform results i_alpha.   */
    HWACC_FOC_CLARK_IBETA_RESULT,          /*!< FOC motor clark transform results i_beta.   */
    HWACC_FOC_PARK_IQ_RESULT,              /*!< FOC motor park transform results iq.  */
    HWACC_FOC_PARK_ID_RESULT,              /*!< FOC motor park transform results id.  */
    HWACC_FOC_PARK_COSTHETA_RESULT,        /*!< FOC motor park transform results cos(theta).   */
    HWACC_FOC_PARK_SINTHETA_RESULT,        /*!< FOC motor park transform results sin(theta).   */
    HWACC_FOC_PI_VQ_RESULT,                /*!< FOC motor pi transform results vq.  */
    HWACC_FOC_PI_VD_RESULT,                /*!< FOC motor pi transform results vd.  */
    HWACC_FOC_INVERSE_CLARKE_VR1_RESULT,   /*!< FOC motor inverse clarke transform results vr1.  */  
    HWACC_FOC_INVERSE_CLARKE_VR2_RESULT,   /*!< FOC motor inverse clarke transform results vr2.  */
    HWACC_FOC_INVERSE_PARK_VA_RESULT,      /*!< FOC motor inverse park transform results va.   */
    HWACC_FOC_INVERSE_PARK_VB_RESULT,      /*!< FOC motor inverse park transform results vb.   */
    HWACC_FOC_NORMALIZE_VAPU_RESULT,       /*!<FOC motor normalize results va_pu.   */
    HWACC_FOC_NORMALIZE_VBPU_RESULT        /*!< FOC motor normalize results vb_pu.   */
} Hwacc_FocOutputType;

/**
 *  @brief Hwacc  Foc PI Intergration Output type definition;
 */
typedef enum
{
    HWACC_FOC_PI_INTERGRATION_VQ_RESULT = 0U,           /*!< FOC  pi Integration Output vq.  */
    HWACC_FOC_PI_INTERGRATION_VD_RESULT                 /*!< FOC  pi Integration Output vd.   */
} Hwacc_FocPiIntergrationOutputType;

/**
 *  @brief Hwacc   Math  Output Register Type definition;
 */
typedef enum
{
    HWACC_MATH_OUT_REG_L_0 = 0U,                           /*!< Math Out Register0 Low 16 bit.  */
    HWACC_MATH_OUT_REG_H_0,                                /*!< Math Out Register0 High 16 bit.  */
    HWACC_MATH_OUT_REG_L_1,                                /*!< Math Out Register1 Low 16 bit.  */
    HWACC_MATH_OUT_REG_H_1                                 /*!< Math Out Register1 High 16 bit.*/    
} Hwacc_MathOutputRegisterType;

/**
 *  @brief Hwacc  Math Input Register Type definition;
 */
typedef enum
{
    HWACC_MATH_IN_REG0_L = 0U,                       /*!< Math In Register0 Low 16 bit.
                                                       If it runs in Clark transform, 
                                                       ia = HWACC_MATH_IN_REG0_L. */
    HWACC_MATH_IN_REG0_H,                            /*!< Math In Register0 High 16 bit.
                                                       If it runs in Clark transform, 
                                                       ib =HWACC_MATH_IN_REG0_H.  */
    HWACC_MATH_IN_REG1_L,                            /*!< Math In Register1 Low 16 bit. */
    HWACC_MATH_IN_REG1_H                             /*!<Math In Register1 High 16 bit. */    
} Hwacc_MathInputRegisterType;

/**
 *  @brief Hwacc Math Input Data number type definition
 */
typedef enum
{
    HWACC_MATH_INPUT_DATA_A = 0U,                /*!< Math input A data  */
    HWACC_MATH_INPUT_DATA_B,                     /*!< Math input B data*/
    HWACC_MATH_INPUT_DATA_C,                     /*!< Math input C data */
    HWACC_MATH_INPUT_DATA_D                      /*!< Math input D data*/
} Hwacc_MathInputDataNumType;

/**
 *  @brief Hwacc  Foc Clarke Input Parameter  struct definition;
 */
typedef struct
{
    sint16 ClarkeInputIa;                     /*!< FOC clarke Input ia .*/
    sint16 ClarkeInputIb;                      /*!< FOC clarke Input ib.*/
    sint16 ClarkeInputIc;                      /*!< FOC clarke Input ic .*/   
} Hwacc_FocClarkeInputType;

/**
 *  @brief Hwacc  Foc Clarke Transform result  struct definition;
 */
typedef struct
{
    sint16 ClarkeResultIalpha;                     /*!< FOC clarke transform result Ialpha.*/
    sint16 ClarkeResultIbeta;                      /*!< FOC clarke transform result Ibeta.*/
} Hwacc_FocClarkeResultType;

/**
 *  @brief Hwacc  Foc Park Transform current result  struct definition;
 */
typedef struct
{
    sint16 ParkResultId;                     /*!< FOC park transform result id.*/
    sint16 ParkResultIq;                      /*!< FOC park transform result iq.*/
} Hwacc_FocParkCurrentResultType;

/**
 *  @brief Hwacc  Foc park Transform sincos result  struct definition;
 */
typedef struct
{
    sint16 ParkResultSinTheta;                     /*!< FOC park transform result SinTheta.*/
    sint16 ParkResultCosTheta;                      /*!< FOC park transform result CosTheta.*/
} Hwacc_FocParkSinCosResultType;

/**
 *  @brief Hwacc  Foc PI controller Output result  struct definition;
 */
typedef struct
{
    sint16 PiResultVd;                     /*!< FOC Pi output result Vd.*/
    sint16 PiResultVq;                      /*!< FOC Pi output result Vq.*/
} Hwacc_FocPiOutputResultType;

/**
 *  @brief Hwacc  Foc Pi Integration Input  struct definition;
 */
typedef struct
{
    sint32 PiIntergrationVd;                     /*!< FOC Pi Integration Input Vd.*/
    sint32 PiIntergrationVq;                      /*!< FOC Pi Integration Input Vq.*/
} Hwacc_FocPiIntergrationInputType;

/**
 *  @brief Hwacc  Inverse CLarke result  struct definition;
 */
typedef struct
{
    sint16 InverseClarkeResultVR0;                    /*!< FOC InverseClarke result VR0.*/
    sint16 InverseClarkeResultVR1;                    /*!< FOC InverseClarke result VR1.*/
    sint16 InverseClarkeResultVR2;                    /*!< FOC InverseClarke result VR2.*/
} Hwacc_FocInvClarkeResultType;

/**
 *  @brief Hwacc  Inverse Park Transform result  struct definition;
 */
typedef struct
{
    sint16 InverseParkValpha;                    /*!< FOC Inverse Park result Valpha.*/
    sint16 InverseParkVbeta;                     /*!< FOC Inverse Park result Vbeta.*/
} Hwacc_FocInvParkResultType;

/**
 *  @brief Hwacc  Inverse Park  transform normalization result  struct definition;
 */
typedef struct
{
    sint16 InverseParkValphaPu;                    /*!< FOC Inverse Park normalization 
                                                        result ValphaPu.*/
    sint16 InverseParkVbetaPu;                    /*!< FOC Inverse Park normalization 
                                                        result VbetaPu.*/
} Hwacc_FocInvParkNormalizationResultType;

/**
 *  @brief Hwacc  Current Reference  struct definition;
 */
typedef struct
{
    sint16 IdRef;                    /*!< FOC id reference .*/
    sint16 IqRef;                    /*!< FOC iq reference .*/
} Hwacc_FocCurrentReferenceType;

/**
 *  @brief Hwacc  Foc  Parameter Configure struct definition;
 */
typedef struct
{
    Common_ControlStateType EnableVoltageNormalizationBypass;    /*!< FOC Voltage Normalization  
                                                                    bypass cmd: 
                                                                    - COMMON_DISABLE, 
                                                                    - COMMON_ENABLE.
                                                                    */
    sint16 VoltageNormalizeBaseValue;                   /*!< FOC Voltage Normalize BaseValue.*/
    Hwacc_InverseClarkeModeType InverseClarkeMode;      /*!< FOC InverseClarke Mode: 
                                                            HWACC_VR1_EQUAL_VBETA, 
                                                            HWACC_VR1_EQUAL_VALPHA.
                                                        */
    sint16 IqKp;                                    /*!< Iq PI controller Kp parameter.*/
    sint16 IqKi;                                    /*!< Iq PI controller Ki parameter.*/
    sint16 IdKp;                                    /*!< Id PI controller Kp parameter.*/
    sint16 IdKi;                                    /*!< Id PI controller Ki parameter.*/
    sint16 VoltageMaxLimit;                         /*!< Foc voltage  max limit.*/
    sint32 IdPiControllerIntergrationMaxLimit;      /*!< FOC Id PI controller Intergration 
                                                        output max limit. */
    sint32 IdPiControllerIntergrationMinLimit;      /*!< FOC Id PI controller Intergration 
                                                        output min limit. */
    sint16 IdPiControllerOutMaxLimit;               /*!< FOC Id PI controller output max limit. */
    sint16 IdPiControllerOutMinLimit;               /*!< FOC Id PI controller output min limit. */
} Hwacc_FocParameterConfigType;

/**
 *  @brief Hwacc Math SinCos Result struct definition;
 */
typedef struct
{
    sint16 SinResult;                    /*!< Math SinTheta Result .*/
    sint16 CosResult;                    /*!< Math CosTheta Result .*/
} Hwacc_MathSinCosResultType;

/** @} end of group Public_TypeDefinition */

/** @defgroup Public_FunctionDeclaration
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
Common_IntStatusType Hwacc_GetIntStatus(Hwacc_IntType IntType);

/**
 * @brief     HWACC interrupt mask or unmask function
 *
 * @param[in] IntType: Interrupt type.
 * @param[in] Cmd: COMMON_MASK, COMMON_UNMASK.
 *
 * @return    none.
 * 
 */
void Hwacc_IntMask(Hwacc_IntType IntType, Common_IntMaskType Cmd);

/**
 * @brief     Clear interrupt state
 *
 * @param[in] IntType: Interrupt type.
 *
 * @return    none.
 * 
 */
void Hwacc_ClearIntStatus(Hwacc_IntType IntType);

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
                        Hwacc_OperationModeType OpModeType);

/**
 * @brief     Machine Run enable/disable Cmd for FOC and Math mode
 *
 * @param[in] Common_ControlStateType : COMMON_DISABLE,COMMON_ENABLE.
 *
 * @return    none.
 * 
 */
void Hwacc_EnableMachineRun(Common_ControlStateType Cmd);

/**
 * @brief     Hwacc Reset Foc.
 *
 * @param[in] none.
 *
 * @return    none.
 * 
 */
void Hwacc_ResetFoc(void);

/**
 * @brief    Get Foc  Status 
 *
 * @param[in]  none.
 *
 * @return     Hwacc_FocStatusType .
 * @retval     Refer to Hwacc_FocStatusType definition.    
 * 
 */
Hwacc_FocStatusType Hwacc_GetFocStatus(void);

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
Hwacc_MathStatusType Hwacc_GetMathStatus(void);

/**
 * @brief    Set Inverse Clarke Mode
 *
 * @param[in] ModeSel: Hwacc  inverse clarke transform mode: 
 *                          - HWACC_VR0_EQUAL_VBETA  
 *                          - HWACC_VR0_EQUAL_VALPHA 
 * @return    none. 
 * 
 */
void Hwacc_SetInverseClarkeMode(Hwacc_InverseClarkeModeType ModeSel);

/**
 * @brief     Voltage Normalization  bypass cmd
 *
 * @param[in]  Cmd:Common_ControlStateType,COMMON_DISABLE,COMMON_ENABLE.
 *
 * @return    none. 
 * 
 */
void Hwacc_EnableVoltageNormalizationBypass(Common_ControlStateType Cmd);

/**
 * @brief      Set Clarke transform Result.
 *
 * @param[in]  ClarkeResultVal :   Clarke transform Result, ClarkeResultIalpha, ClarkeResultIbeta.
 *
 * @return    none. 
 * 
 */
void Hwacc_SetClarkeTransformResult(Hwacc_FocClarkeResultType ClarkeResultVal);

/**
 * @brief      Set Park  transform Current Result.
 *
 * @param[in]  ParkCurrentResultVal :   ParkResultId, ParkResultIq.
 *
 * @return    none. 
 * 
 */
void Hwacc_SetParkTransformCurrentResult(Hwacc_FocParkCurrentResultType ParkCurrentResultVal);

/**
 * @brief      Set Park  transform sincos Result.
 *
 * @param[in]  ParkSinCosResultVal : ParkResultSinTheta, ParkResultCosTheta.
 *
 * @return    none. 
 * 
 */
void Hwacc_SetParkTransformSinCosResult(Hwacc_FocParkSinCosResultType ParkSinCosResultVal);

/**
 * @brief      Set  PI controller Output result.
 *
 * @param[in]  PiOutputVal :  PiResultVd, PiResultVq.
 *
 * @return    none. 
 * 
 */
void Hwacc_SetPiOutputResult(Hwacc_FocPiOutputResultType PiOutputVal);

/**
 * @brief      Set  PI Intergration Input 
 *
 * @param[in]  PiIntergrationVal :  PiIntergrationVd, PiIntergrationVq.
 *
 * @return    none. 
 * 
 */
void Hwacc_SetPiIntergrationInput(Hwacc_FocPiIntergrationInputType PiIntergrationVal);

/**
 * @brief      Set Inverse Clarke transform Result.
 *
 * @param[in]  InvClarkeVal :  InverseClarkeResultVR1, InverseClarkeResultVR2
 *
 * @return    none. 
 * 
 */
void Hwacc_SetInverseClarkeTransformResult(Hwacc_FocInvClarkeResultType InvClarkeVal);

/**
 * @brief      Set Inverse Park transform Result.
 *
 * @param[in]  InvParkVal :  InverseParkValpha, InverseParkVbeta.
 *
 * @return    none. 
 * 
 */
void Hwacc_SetInverseParkTransformResult(Hwacc_FocInvParkResultType InvParkVal);

/**
 * @brief      Set Inverse Park Normalization transform Result.
 *
 * @param[in]  InvParkNormalVal :  InverseParkValphaPu, InverseParkVbetaPu.
 *
 * @return    none. 
 * 
 */
void Hwacc_SetInverseParkNormalizationkTransformResult(
                        Hwacc_FocInvParkNormalizationResultType InvParkNormalVal);

/**
 * @brief      Set park transform input  parameter.theta
 *
 * @param[in]   Theta: sint16,  -32768:-pi,   32767:pi.
 *
 * @return    none. 
 * 
 */
void Hwacc_SetParkTransformInputTheta(sint16 Theta);

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
void Hwacc_SetPiControllerCurrentReference(Hwacc_CurrentControllerType CurrentType, sint16 Val);

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
void Hwacc_SetPiControllerKp(Hwacc_CurrentControllerType CurrentType, sint16 Val);

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
void Hwacc_SetPiControllerKi(Hwacc_CurrentControllerType CurrentType, sint16 Val);

/**
 * @brief      Set Id PI controller Intergration output max limit 
 *
 * @param[in]  Val:   Intergration max limit
 *
 * @return    none. 
 * 
 */
void Hwacc_SetIdPiControllerIntergrationMaxLimit(sint32 Val);

/**
 * @brief      Get Iq PI controller Intergration output max limit 
 *
 * @param[in]  none. 
 *
 * @return    Intergration max limit. 
 * 
 */
sint32  Hwacc_GetIqPiControllerIntergrationMaxLimit(void);

/**
 * @brief      Set Id PI controller Intergration output min limit 
 *
 * @param[in]  Val:   Intergration min limit 
 *
 * @return    none. 
 * 
 */
void Hwacc_SetIdPiControllerIntergrationMinLimit(sint32 Val);

/**
 * @brief      Get Iq PI controller Intergration output min limit 
 *
 * @param[in]  none.   
 *
 * @return    Intergration min limit . 
 * 
 */
sint32  Hwacc_GetIqPiControllerIntergrationMinLimit(void);

/**
 * @brief      Set Voltage normalize BaseValue.
 *
 * @param[in]  Val:    Voltage normalize BaseValue. 
 *
 * @return    none. 
 * 
 */
void Hwacc_SetVoltageNormalizeBaseValue(sint16 Val);

/**
 * @brief      Set  Id PI controller out max limit  
 *
 * @param[in]  Val:   out max limit. 
 *
 * @return    none. 
 * 
 */
void Hwacc_SetIdPiControllerOutMaxLimit(sint16 Val);

/**
 * @brief      Get  Iq PI controller out max limit  
 *
 * @param[in]  none.
 *
 * @return    out max limit. 
 * 
 */
sint16  Hwacc_GetIqPiControllerOutMaxLimit(void);

/**
 * @brief      Set Id PI controller out min limit  
 *
 * @param[in]  Val:   out min limit. 
 *
 * @return    none. 
 * 
 */
void Hwacc_SetIdPiControllerOutMinLimit(sint16 Val);

/**
 * @brief      Get Iq PI controller out min limit  
 *
 * @param[in]  none.    
 *
 * @return    out min limit. 
 * 
 */
sint16  Hwacc_GetIqPiControllerOutMinLimit(void);

/**
 * @brief      Set Foc voltage  max limit 
 *
 * @param[in]  Val:   Voltage max value. 
 *
 * @return    none. 
 * 
 */
void Hwacc_SetFocVoltageMaxLimit(sint16 Val);

/**
 * @brief      Get  Foc Output Value.   
 *
 * @param[in]   OutputType :Foc Output Type, refer to Hwacc_FocOutputType definition.
 *
 * @return     Foc Output Value, sint16. 
 * 
 */
sint16 Hwacc_GetFocOutput(Hwacc_FocOutputType OutputType);

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
sint32 Hwacc_GetFocPIIntergrationOutput(Hwacc_FocPiIntergrationOutputType IntergrationOutputType);

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
sint16 Hwacc_GetMathOutputRegisterValue(Hwacc_MathOutputRegisterType RegType);

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
void Hwacc_SetMathInputRegisterValue(Hwacc_MathInputRegisterType RegType, sint16 Val);

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
                                            uint8 AdrrOffSet);

/**
 * @brief       Hwacc install interrupt callback function
 *
 * @param[in]  IntType:    Select interrupt type.
 * @param[in]  CbFun:      Callback function .
 *
 * @return none
 *
 */
void Hwacc_InstallCallBackFunc(Hwacc_IntType IntType, Isr_CbFuncType * CbFun);

/**
 * @brief       Hwacc Foc Init Function .
 *
 * @param[in]   Config: Foc Config Parameters.
 *
 * @return none
 *
 */
void Hwacc_InitFoc(Hwacc_FocParameterConfigType *Config);

/**
 * @brief       Hwacc Start Foc Clarke Transform From Ia/Ib/Ic To Ialpha/Ibeta  
 *
 * @param[in]  ClarkeInput: ClarkeInputIa, ClarkeInputIb, 
 *                          ClarkeInputIa + ClarkeInputIb + ClarkeInputIc = 0.
 *
 * @return none.
 *
 */
void Hwacc_StartFocClarkeTransform(Hwacc_FocClarkeInputType ClarkeInput);

/**
 * @brief       Hwacc   Get Foc Clarke Transform  Result .
 *
 * @param[in]  TimeOutVal:  ClarkeTransform TimeOutValue
 *
 * @return ClarkeResult :ClarkeResultIalpha, ClarkeResultIbeta.
 *
 */
Hwacc_FocClarkeResultType Hwacc_GetFocClarkeTransformResult(uint32 TimeOutVal);

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
                    sint16 Theta, Hwacc_FocCurrentReferenceType CurrentRef);

/**
 * @brief       Hwacc   Get Foc Inverse Clarke Transform  Result .
 *
 * @param[in]  TimeOutVal: Inverse Clarke Transform TimeOutValue
 *
 * @return InvClarkeResult : InverseClarkeResultVR1, InverseClarkeResultVR2, InverseClarkeResultVR3.
 */
Hwacc_FocInvClarkeResultType Hwacc_GetFocInverseClarkeTransformResult(uint32 TimeOutVal);

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
                        sint16 Theta, Hwacc_FocCurrentReferenceType CurrentRef);

/**
 * @brief       Hwacc Math Init Function .
 *
 * @param[in]   none.
 *
 * @return none
 *
 */
void Hwacc_InitMath(void);

/**
 * @brief       Hwacc Math Start SinCos Transform .
 *
 * @param[in]   Theta: sint16,  -32768:-pi,   32767:pi.
 * @param[in]   TimeOutVal: Wait Math To Idle TimeOutValue.
 *
 * @return none
 *
 */
void Hwacc_StartMathSinCosTransform(sint16 Theta, uint32 TimeOutVal);

/**
 * @brief       Hwacc Get Math SinCos Transform Result.
 *
 * @param[in]   TimeOutVal: SinCos Transform TimeOutValue.
 *
 * @return      SinCosResult:CosResult,SinResult,sint16.
 *
 */
Hwacc_MathSinCosResultType Hwacc_GetMathSinCosTransformResult(uint32 TimeOutVal);

/**
 * @brief       Hwacc Math Start Arctan Transform .
 *
 * @param[in]   A:  tan(theta), -32768:tan(-pi), 32767:tan(pi).
 * @param[in]   TimeOutVal: Wait Math To Idle TimeOutValue.
 *
 * @return none
 *
 */
void Hwacc_StartMathArctanTransform(sint16 A, uint32 TimeOutVal);

/**
 * @brief       Hwacc Get Math Arctan Transform Result.
 *
 * @param[in]   TimeOutVal: Arctan Transform TimeOutValue.
 *
 * @return      Theta:  sint16 , -32768:-pi, 32767:pi.
 *
 */
sint16 Hwacc_GetMathArctanTransformResult(uint32 TimeOutVal);

/**
 * @brief       Hwacc Math Start Sqrt Transform .
 *
 * @param[in]   A:Input Data.
 * @param[in]   TimeOutVal: Wait Math To Idle TimeOutValue.
 *
 * @return none
 *
 */
void Hwacc_StartMathSqrtTransform(uint16 A, uint32 TimeOutVal);

/**
 * @brief       Hwacc Get Math Sqrt Transform Result.
 *
 * @param[in]   TimeOutVal: Sqrt Transform TimeOutValue.
 *
 * @return      SqrtResult.
 *
 */
uint16 Hwacc_GetMathSqrtTransformResult(uint32 TimeOutVal);

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
void Hwacc_StartMathDivisionTransform(sint32 A, sint32 B, uint32 TimeOutVal);

/**
 * @brief       Hwacc Get Math Division Transform Result.
 *
 * @param[in]   TimeOutVal: Division Transform TimeOutValue.
 *
 * @return      A/B Result.
 *
 */
sint32 Hwacc_GetMathDivisionTransformResult(uint32 TimeOutVal);

/** @} end of group Public_FunctionDeclaration */

#endif /* HWACC_DRV_H */
