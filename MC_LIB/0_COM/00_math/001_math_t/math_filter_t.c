/**
 * @file    math_filter_t.c
 * @brief   定点滤波器与统计函数实现（Q14）
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "math_filter_t.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  初始化 Q14 低通滤波器
 * @param  pLPF  滤波器结构体指针
 * @param  init  初始输出
 */
void LPF_Init_T(ST_LPF_T* pLPF, Q32I_ init)
{
    pLPF->O_Q14I_LPF_Out = init;
    pLPF->V_Q28I_LPF_Tmp = Q16I_LFT_14(init);
}

/**
 * @brief  执行一帧 Q14 低通滤波
 * @param  pLPF  滤波器结构体指针
 */
void LPF_Cal_T(ST_LPF_T* pLPF)
{
    pLPF->V_Q28I_LPF_Tmp += pLPF->P_Q14I_LPF_Coeff * (pLPF->I_Q14I_LPF_In - Q32I_RHT_14(pLPF->V_Q28I_LPF_Tmp));
    pLPF->O_Q14I_LPF_Out = Q32I_RHT_14(pLPF->V_Q28I_LPF_Tmp);
}

/**
 * @brief  初始化 Q14 滑动平均
 * @param  pMEAN  滑动平均结构体指针
 */
void MEAN_Init_T(ST_MEAN_T* pMEAN)
{
    pMEAN->O_Q14I_MEAN_Out = 0;
    pMEAN->V_Q14I_MEAN_Tmp = 0;
    pMEAN->V_Q32U_MEAN_Cnt = 0U;
}

/**
 * @brief  执行一帧 Q14 滑动平均
 * @param  pMEAN  滑动平均结构体指针
 */
void MEAN_Cal_T(ST_MEAN_T* pMEAN)
{
    pMEAN->V_Q32U_MEAN_Cnt++;
    pMEAN->V_Q14I_MEAN_Tmp += pMEAN->I_Q14I_MEAN_In;

    if (pMEAN->V_Q32U_MEAN_Cnt >= pMEAN->P_Q32U_MEAN_Num)
    {
        pMEAN->O_Q14I_MEAN_Out = pMEAN->V_Q14I_MEAN_Tmp >> pMEAN->P_Q32U_MEAN_Bit;

        pMEAN->V_Q14I_MEAN_Tmp = 0;
        pMEAN->V_Q32U_MEAN_Cnt = 0U;
    }
}

/**
 * @brief  初始化 Q14 滑动最大值
 * @param  pMAX  滑动最大值结构体指针
 */
void MAX_Init_T(ST_MAX_T* pMAX)
{
    pMAX->O_Q14I_MAX_Out = 0;
    pMAX->V_Q14I_MAX_Tmp = 0;
    pMAX->V_Q32U_MAX_Cnt = 0U;
}

/**
 * @brief  执行一帧 Q14 滑动最大值
 * @param  pMAX  滑动最大值结构体指针
 */
void MAX_Cal_T(ST_MAX_T* pMAX)
{
    pMAX->V_Q32U_MAX_Cnt++;
    if (pMAX->I_Q14I_MAX_In >= pMAX->V_Q14I_MAX_Tmp)
    {
        pMAX->V_Q14I_MAX_Tmp = pMAX->I_Q14I_MAX_In;
    }

    if (pMAX->V_Q32U_MAX_Cnt >= pMAX->P_Q32U_MAX_Num)
    {
        pMAX->O_Q14I_MAX_Out = pMAX->V_Q14I_MAX_Tmp;

        pMAX->V_Q14I_MAX_Tmp = 0;
        pMAX->V_Q32U_MAX_Cnt = 0U;
    }
}
