/*
*     File Name :                        math_filter_t
*     Library/Module Name :              MATH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             滤波器
*/

/*-------------------------- 1. 对应头文件--------------------------------*/
#include "math_filter_t.h"

/*-------------------------- 2. 变量 ---------------------------------*/

/*-------------------------- 3. 公有接口实现 -----------------------------*/
void LPF_Init_T(ST_LPF_T* pLPF, Q32I_ init)
{
    pLPF->O_Q14I_LPF_Out = init;
    pLPF->V_Q28I_LPF_Tmp = Q16I_LFT_14(init);
}

void LPF_Cal_T(ST_LPF_T* pLPF)
{
    pLPF->V_Q28I_LPF_Tmp += pLPF->P_Q14I_LPF_Coeff*(pLPF->I_Q14I_LPF_In - Q32I_RHT_14(pLPF->V_Q28I_LPF_Tmp));
    pLPF->O_Q14I_LPF_Out = Q32I_RHT_14(pLPF->V_Q28I_LPF_Tmp);
}

void MEAN_Init_T(ST_MEAN_T* pMEAN)
{
    pMEAN->O_Q14I_MEAN_Out = 0;
    
    pMEAN->V_Q14I_MEAN_Tmp = 0;
    pMEAN->V_Q32U_MEAN_Cnt = 0U;
}

void MEAN_Cal_T(ST_MEAN_T* pMEAN)
{
    pMEAN->V_Q32U_MEAN_Cnt++;
    pMEAN->V_Q14I_MEAN_Tmp += pMEAN->I_Q14I_MEAN_In;
    
    if(pMEAN->V_Q32U_MEAN_Cnt >= pMEAN->P_Q32U_MEAN_Num)
    {
        pMEAN->O_Q14I_MEAN_Out = pMEAN->V_Q14I_MEAN_Tmp>>pMEAN->P_Q32U_MEAN_Bit;
        
        pMEAN->V_Q14I_MEAN_Tmp = 0;
        pMEAN->V_Q32U_MEAN_Cnt = 0U;
    }
}

void MAX_Init_T(ST_MAX_T* pMAX)
{
    pMAX->O_Q14I_MAX_Out = 0;
    
    pMAX->V_Q14I_MAX_Tmp = 0;
    pMAX->V_Q32U_MAX_Cnt = 0U;
}

void MAX_Cal_T(ST_MAX_T* pMAX)
{
    pMAX->V_Q32U_MAX_Cnt++;
    if(pMAX->I_Q14I_MAX_In >= pMAX->V_Q14I_MAX_Tmp)
    {
        pMAX->V_Q14I_MAX_Tmp = pMAX->I_Q14I_MAX_In;
    }
    
    if(pMAX->V_Q32U_MAX_Cnt >= pMAX->P_Q32U_MAX_Num)
    {
        pMAX->O_Q14I_MAX_Out = pMAX->V_Q14I_MAX_Tmp;
        
        pMAX->V_Q14I_MAX_Tmp = 0;
        pMAX->V_Q32U_MAX_Cnt = 0U;
    }
}
