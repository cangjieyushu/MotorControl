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


/*-------------------------- 3. 内部辅助函数 ----------------------------*/
/*
Function: BSP_MC_OPAMP_ConfigOne
Description: 配置单个 OPA（跟随器或 PGA 模式）
Input: opampSel  - OPA 实例（HW_MC_OPAMP1/2/3）
       vinpIo    - 同相输入 IO 选择（OPAMP_NonInvertingInput_IOx）
       mode      - 工作模式（HW_MC_OPAMP_MODE_FOLLOWER / HW_MC_OPAMP_MODE_PGA）
       gain      - PGA 增益（仅 PGA 模式有效）
       pgaConn   - PGA 内部电阻连接（仅 PGA 模式有效）
Return: 无
Author: CJYS
*/
static void BSP_MC_OPAMP_ConfigOne(uint32_t opampSel,
                                   uint32_t vinpIo,
                                   uint32_t mode,
                                   uint32_t gain,
                                   uint32_t pgaConn)
{
    OPAMP_InitTypeDef OPAMP_InitStructure;

    OPAMP_InitStructure.OPAMP_NonInvertingInput = vinpIo;

    if (mode == HW_MC_OPAMP_MODE_PGA)
    {
        OPAMP_InitStructure.OPAMP_InvertingInput = OPAMP_InvertingInput_PGA;
        OPAMP_Init(opampSel, &OPAMP_InitStructure);
        OPAMP_PGAConfig(opampSel, gain, pgaConn);
    }
    else
    {
        OPAMP_InitStructure.OPAMP_InvertingInput = OPAMP_InvertingInput_Vout;
        OPAMP_Init(opampSel, &OPAMP_InitStructure);
    }

    OPAMP_Cmd(opampSel, ENABLE);
}


/*-------------------------- 4. 公有接口实现 -----------------------------*/
/*
Function: BSP_MC_OPAMP_Init
Description: OPA1/2/3 初始化
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_MC_OPAMP_Init(void)
{
    /* ---- OPA1：输出到 PA2 ---- */
    BSP_MC_OPAMP_ConfigOne(HW_MC_OPAMP1,
                           HW_MC_OPAMP1_VINP_IO,
                           HW_MC_OPAMP1_MODE,
                           HW_MC_OPAMP1_GAIN,
                           HW_MC_OPAMP1_PGA_CONNECT);

    /* ---- OPA2：输出到 PC5 ---- */
    BSP_MC_OPAMP_ConfigOne(HW_MC_OPAMP2,
                           HW_MC_OPAMP2_VINP_IO,
                           HW_MC_OPAMP2_MODE,
                           HW_MC_OPAMP2_GAIN,
                           HW_MC_OPAMP2_PGA_CONNECT);

    /* ---- OPA3：输出到 PB1 ---- */
    BSP_MC_OPAMP_ConfigOne(HW_MC_OPAMP3,
                           HW_MC_OPAMP3_VINP_IO,
                           HW_MC_OPAMP3_MODE,
                           HW_MC_OPAMP3_GAIN,
                           HW_MC_OPAMP3_PGA_CONNECT);
}
