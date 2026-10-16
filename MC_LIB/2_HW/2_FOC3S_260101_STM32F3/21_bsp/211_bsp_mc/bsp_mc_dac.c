/*
*     File Name :                        bsp_mc_dac
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             DAC 阈值输出初始化
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "bsp_mc_dac.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 公有接口实现 -----------------------------*/
/*
Function: BSP_MC_DAC_Init
Description: DAC 初始化（窗口比较器阈值输出）
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_MC_DAC_Init(void)
{
    DAC_InitTypeDef DAC_InitStructure;

    /* DAC 挂 APB1，使能时钟 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC1, ENABLE);

    /* ---------------- 通道 1（PA4）：窗口上限 VH ---------------- */
    DAC_InitStructure.DAC_Trigger             = DAC_Trigger_None;
    DAC_InitStructure.DAC_WaveGeneration      = DAC_WaveGeneration_None;
    DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
    DAC_InitStructure.DAC_Buffer_Switch       = DAC_BufferSwitch_Enable;
    DAC_Init(DAC1, DAC_Channel_1, &DAC_InitStructure);

    /* ---------------- 通道 2（PA5）：窗口下限 VL ---------------- */
    DAC_Init(DAC1, DAC_Channel_2, &DAC_InitStructure);

    /* 上电默认阈值 */
    DAC_SetChannel1Data(DAC1, DAC_Align_12b_R, 3000);
    DAC_SetChannel2Data(DAC1, DAC_Align_12b_R, 1000);

    DAC_Cmd(DAC1, DAC_Channel_1, ENABLE);
    DAC_Cmd(DAC1, DAC_Channel_2, ENABLE);
}
