/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/

#include "BSP_CMP.h"

void BSP_CMP_Init(void)
{
    CMP_InitTypeDef CMP_InitStruct = {0};
    
    CMP_InitStruct.Pol = CMP_CxCR_POL_Positive;
    CMP_InitStruct.Rhyst = CMP_CxCR_RHYST_0mV;
    CMP_InitStruct.Fhyst = CMP_CxCR_FHYST_0mV;
    CMP_InitStruct.INP_Sel = CMP_INP_SEL_OPA2_out_CMP2;
    CMP_InitStruct.INM_Sel = CMP_INM_SEL_CRV;
    CMP_InitStruct.OFLT = CMP_CxCR_OFLT_DIV32;
    CMP_InitStruct.CRV_SEL = CMP_CRV_SEL_32_32;
    CMP_InitStruct.CRV_En = ENABLE;
    CMP_InitStruct.CRV_Src = 0;
    CMP_InitStruct.CR1_SRN = DISABLE;
    
    CMP_Init(HAL_MOTOR_CMP, &CMP_InitStruct);
    
    CMP_Enable(HAL_MOTOR_CMP);
}
