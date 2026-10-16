/*
*     File Name :                        bsp_mc_opamp
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             OPA 跟随器 / PGA 初始化
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_mc_opamp.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 公有接口实现 -----------------------------*/
/*
Function: BSP_MC_OPAMP_Init
Description: OPA 初始化（PGA 模式，输出送 CMP 的 P 端）
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_MC_OPAMP_Init(void)
{
    OPAMP_InitTypeDef OPAMP_InitStruct = {0};

    OPAMP_InitStruct.PGAGain          = OPAMP_GAIN_8;
    OPAMP_InitStruct.FunctionalMode   = OPAMP_MODE_PGA;
    OPAMP_InitStruct.OPAMP_OUTCONNECT = OPAMP_VM_TO_VIN1;
    OPAMP_InitStruct.VPSEL            = OPAMP_CSR_VPSEL_P1;
    OPAMP_InitStruct.TOEXT            = OPAMP_CSR_TOEXT_DISABLE;
    OPAMP_InitStruct.TOINT            = OPAMP_CSR_TOINT_ENABLE;
    OPAMP_InitStruct.BIASMode         = OPAMP_BIAS_VBG;

    OPAMP_Init(HW_MC_OPAMP, &OPAMP_InitStruct);
    OPAMP_Enable(HW_MC_OPAMP);
}
