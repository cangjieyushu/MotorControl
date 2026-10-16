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


/*-------------------------- 3. 内部辅助函数 ----------------------------*/
static void BSP_MC_CMP_ConfigMaster(uint32_t compSel,
                                    uint32_t invert,
                                    uint32_t nonInvert,
                                    uint32_t output,
                                    uint32_t outputPol)
{
    COMP_InitTypeDef COMP_InitStructure;

    COMP_InitStructure.COMP_InvertingInput    = invert;
    COMP_InitStructure.COMP_NonInvertingInput = nonInvert;
    COMP_InitStructure.COMP_Output            = output;
    COMP_InitStructure.COMP_BlankingSrce      = COMP_BlankingSrce_None;
    COMP_InitStructure.COMP_OutputPol         = outputPol;
    COMP_InitStructure.COMP_Hysteresis        = COMP_Hysteresis_Low;
    COMP_InitStructure.COMP_Mode              = COMP_Mode_HighSpeed;

    COMP_Init(compSel, &COMP_InitStructure);
    COMP_Cmd(compSel, ENABLE);
}

static void BSP_MC_CMP_ConfigSlave(uint32_t compSel,
                                   uint32_t invert,
                                   uint32_t output,
                                   uint32_t outputPol)
{
    COMP_InitTypeDef COMP_InitStructure;

    COMP_InitStructure.COMP_InvertingInput    = invert;
    COMP_InitStructure.COMP_NonInvertingInput = COMP_NonInvertingInput_IO1;   /* 窗口模式下此字段被忽略 */
    COMP_InitStructure.COMP_Output            = output;
    COMP_InitStructure.COMP_BlankingSrce      = COMP_BlankingSrce_None;
    COMP_InitStructure.COMP_OutputPol         = outputPol;
    COMP_InitStructure.COMP_Hysteresis        = COMP_Hysteresis_Low;
    COMP_InitStructure.COMP_Mode              = COMP_Mode_HighSpeed;

    COMP_Init(compSel, &COMP_InitStructure);

    /* 使能窗口模式 */
    COMP_WindowCmd(compSel, ENABLE);

    COMP_Cmd(compSel, ENABLE);
}


/*-------------------------- 4. 公有接口实现 -----------------------------*/
/*
Function: BSP_MC_CMP_Init
Description: 三组窗口比较器初始化
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_MC_CMP_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    /* 组 1：COMP1(主) + COMP2(从) */
    BSP_MC_CMP_ConfigMaster(HW_MC_OCP_COMP1, HW_MC_OCP_COMP1_INVERT,
                            HW_MC_OCP_COMP1_NONINVERT, HW_MC_OCP_COMP1_OUTPUT,
                            HW_MC_OCP_COMP1_OUTPUTPOL);
    BSP_MC_CMP_ConfigSlave(HW_MC_OCP_COMP2, HW_MC_OCP_COMP2_INVERT,
                           HW_MC_OCP_COMP2_OUTPUT, HW_MC_OCP_COMP2_OUTPUTPOL);

    /* 组 2：COMP3(主) + COMP4(从) */
    BSP_MC_CMP_ConfigMaster(HW_MC_OCP_COMP3, HW_MC_OCP_COMP3_INVERT,
                            HW_MC_OCP_COMP3_NONINVERT, HW_MC_OCP_COMP3_OUTPUT,
                            HW_MC_OCP_COMP3_OUTPUTPOL);
    BSP_MC_CMP_ConfigSlave(HW_MC_OCP_COMP4, HW_MC_OCP_COMP4_INVERT,
                           HW_MC_OCP_COMP4_OUTPUT, HW_MC_OCP_COMP4_OUTPUTPOL);

    /* 组 3：COMP5(主) + COMP6(从) */
    BSP_MC_CMP_ConfigMaster(HW_MC_OCP_COMP5, HW_MC_OCP_COMP5_INVERT,
                            HW_MC_OCP_COMP5_NONINVERT, HW_MC_OCP_COMP5_OUTPUT,
                            HW_MC_OCP_COMP5_OUTPUTPOL);
    BSP_MC_CMP_ConfigSlave(HW_MC_OCP_COMP6, HW_MC_OCP_COMP6_INVERT,
                           HW_MC_OCP_COMP6_OUTPUT, HW_MC_OCP_COMP6_OUTPUTPOL);
}
