/*
*     File Name :                        math_filter_f
*     Library/Module Name :              math
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             低通滤波器
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "math_filter_f.h"


/*-------------------------- 2. 变量 ---------------------------------*/


/*-------------------------- 3. 公有接口实现 -----------------------------*/
void LPF_Init_F(ST_LPF_F* pLPF, float init)
{
    pLPF->O_F_LPF_Out = init;
}

void LPF_Cal_F(ST_LPF_F* pLPF)
{
    pLPF->O_F_LPF_Out += pLPF->P_F_LPF_Coeff*(pLPF->I_F_LPF_In - pLPF->O_F_LPF_Out);
}

void MEAN_Init_F(ST_MEAN_F* pMEAN)
{
    pMEAN->O_F_MEAN_Out = 0.0f;

    pMEAN->V_F_MEAN_Tmp = 0.0f;
    pMEAN->V_Q32U_MEAN_Cnt = 0U;
}

void MEAN_Cal_F(ST_MEAN_F* pMEAN)
{
    pMEAN->V_Q32U_MEAN_Cnt++;
    pMEAN->V_F_MEAN_Tmp += pMEAN->I_F_MEAN_In;
    
    if(pMEAN->V_Q32U_MEAN_Cnt >= pMEAN->P_Q32U_MEAN_Num)
    {
        pMEAN->O_F_MEAN_Out = pMEAN->V_F_MEAN_Tmp/((float)pMEAN->P_Q32U_MEAN_Num);
        
        pMEAN->V_F_MEAN_Tmp = 0.0f;
        pMEAN->V_Q32U_MEAN_Cnt = 0U;
    }
}

void MAX_Init_F(ST_MAX_F* pMAX)
{
    pMAX->O_F_MAX_Out = 0.0f;

    pMAX->V_F_MAX_Tmp = 0.0f;
    pMAX->V_Q32U_MAX_Cnt = 0U;
}

void MAX_Cal_F(ST_MAX_F* pMAX)
{
    pMAX->V_Q32U_MAX_Cnt++;
    if(pMAX->I_F_MAX_In >= pMAX->V_F_MAX_Tmp)
    {
        pMAX->V_F_MAX_Tmp = pMAX->I_F_MAX_In;
    }
    
    if(pMAX->V_Q32U_MAX_Cnt >= pMAX->P_Q32U_MAX_Num)
    {
        pMAX->O_F_MAX_Out = pMAX->V_F_MAX_Tmp;
        
        pMAX->V_F_MAX_Tmp = 0.0f;
        pMAX->V_Q32U_MAX_Cnt = 0U;
    }
}
