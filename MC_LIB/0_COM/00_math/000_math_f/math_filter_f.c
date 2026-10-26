/**
 * @file    math_filter_f.c
 * @brief   浮点滤波器与统计函数实现
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "math_filter_f.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  初始化低通滤波器
 * @param  pLPF  滤波器结构体指针
 * @param  init  初始输出
 */
void LPF_Init_F(ST_LPF_F* pLPF, float init)
{
    pLPF->O_F_LPF_Out = init;
}

/**
 * @brief  执行一帧低通滤波
 * @param  pLPF  滤波器结构体指针
 */
void LPF_Cal_F(ST_LPF_F* pLPF)
{
    pLPF->O_F_LPF_Out += pLPF->P_F_LPF_Coeff * (pLPF->I_F_LPF_In - pLPF->O_F_LPF_Out);
}

/**
 * @brief  初始化高通滤波器
 * @param  pHPF  滤波器结构体指针
 * @param  init  初始输出
 */
void HPF_Init_F(ST_HPF_F* pHPF, float init)
{
    pHPF->O_F_HPF_Out     = init;
    pHPF->V_F_HPF_In_Last = init;
}

/**
 * @brief  执行一帧高通滤波
 * @param  pHPF  滤波器结构体指针
 */
void HPF_Cal_F(ST_HPF_F* pHPF)
{
    pHPF->O_F_HPF_Out = pHPF->P_F_HPF_Coeff * (pHPF->I_F_HPF_In + pHPF->O_F_HPF_Out - pHPF->V_F_HPF_In_Last);
    pHPF->V_F_HPF_In_Last = pHPF->I_F_HPF_In;
}

/**
 * @brief  初始化滑动平均
 * @param  pMEAN  滑动平均结构体指针
 */
void MEAN_Init_F(ST_MEAN_F* pMEAN)
{
    pMEAN->O_F_MEAN_Out    = 0.0f;
    pMEAN->V_F_MEAN_Tmp    = 0.0f;
    pMEAN->V_Q32U_MEAN_Cnt = 0U;
}

/**
 * @brief  执行一帧滑动平均
 * @param  pMEAN  滑动平均结构体指针
 */
void MEAN_Cal_F(ST_MEAN_F* pMEAN)
{
    pMEAN->V_Q32U_MEAN_Cnt++;
    pMEAN->V_F_MEAN_Tmp += pMEAN->I_F_MEAN_In;

    if (pMEAN->V_Q32U_MEAN_Cnt >= pMEAN->P_Q32U_MEAN_Num)
    {
        pMEAN->O_F_MEAN_Out = pMEAN->V_F_MEAN_Tmp / ((float)pMEAN->P_Q32U_MEAN_Num);

        pMEAN->V_F_MEAN_Tmp    = 0.0f;
        pMEAN->V_Q32U_MEAN_Cnt = 0U;
    }
}

/**
 * @brief  初始化滑动最大值
 * @param  pMAX  滑动最大值结构体指针
 */
void MAX_Init_F(ST_MAX_F* pMAX)
{
    pMAX->O_F_MAX_Out    = 0.0f;
    pMAX->V_F_MAX_Tmp    = 0.0f;
    pMAX->V_Q32U_MAX_Cnt = 0U;
}

/**
 * @brief  执行一帧滑动最大值
 * @param  pMAX  滑动最大值结构体指针
 */
void MAX_Cal_F(ST_MAX_F* pMAX)
{
    pMAX->V_Q32U_MAX_Cnt++;
    if (pMAX->I_F_MAX_In >= pMAX->V_F_MAX_Tmp)
    {
        pMAX->V_F_MAX_Tmp = pMAX->I_F_MAX_In;
    }

    if (pMAX->V_Q32U_MAX_Cnt >= pMAX->P_Q32U_MAX_Num)
    {
        pMAX->O_F_MAX_Out = pMAX->V_F_MAX_Tmp;

        pMAX->V_F_MAX_Tmp    = 0.0f;
        pMAX->V_Q32U_MAX_Cnt = 0U;
    }
}
