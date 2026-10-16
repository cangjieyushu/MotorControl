/*
*     File Name :                        bsp_mc_dma
*     Library/Module Name :              bsp
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制 DMA 初始化（ADC1 规则组搬运）
*/


#ifndef BSP_MC_DMA_H
#define BSP_MC_DMA_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "hw_map.h"
#include "hw_para.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: BSP_MC_DMA_Init
Description: ADC1 规则组 DMA 初始化
             - DMA1_Channel1：ADC1_DR → BSP_ADC_SYSTEM_BUFFER[0..1]
             - 循环模式，32 位搬运
             - 初始化完成后启动 ADC1 规则组首次转换
Input: 无
Output: 无
Return: 无
Author: CJYS
*/
void BSP_MC_DMA_Init(void);


#endif /* BSP_MC_DMA_H */
