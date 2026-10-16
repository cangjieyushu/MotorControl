/*
*     File Name :                        bsp_mc_cmp
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             CMP 窗口比较器初始化
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_mc_cmp.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 公有接口实现 -----------------------------*/
/*
Function: BSP_MC_CMP_Init
Description: 比较器初始化
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_MC_CMP_Init(void)
{
    CMP_InitTypeDef CMP_InitStruct = {0};

    CMP_InitStruct.Pol     = CMP_CxCR_POL_Positive;
    CMP_InitStruct.Rhyst   = CMP_CxCR_RHYST_0mV;
    CMP_InitStruct.Fhyst   = CMP_CxCR_FHYST_0mV;
    CMP_InitStruct.INP_Sel = CMP_INP_SEL_OPA2_out_CMP2;
    CMP_InitStruct.INM_Sel = CMP_INM_SEL_CRV;
    CMP_InitStruct.OFLT    = CMP_CxCR_OFLT_DIV32;
    CMP_InitStruct.CRV_SEL = CMP_CRV_SEL_32_32;
    CMP_InitStruct.CRV_En  = ENABLE;
    CMP_InitStruct.CRV_Src = CMP_CR2_CRV_SRC_1;
    CMP_InitStruct.CR1_SRN = DISABLE;

    CMP_Init(HW_MC_CMP, &CMP_InitStruct);
    CMP_Enable(HW_MC_CMP);
}
