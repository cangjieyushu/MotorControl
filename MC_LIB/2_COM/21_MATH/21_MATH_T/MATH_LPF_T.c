/**************************************************************************************************
*     File Name :                        MATH_LPF_T.c
*     Library/Module Name :              MATH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             低通滤波器
**************************************************************************************************/

#include "MATH_LPF_T.h"


/**********************************************************************************************
Function: LPF_Init_T
Description: 定点低通滤波初始化
Input: 定点低通滤波初始值
Output: 无
Input_Output: 定点低通滤波指针
Return: 无
Author: CJYS
***********************************************************************************************/
void LPF_Init_T(ST_LPF_T* pLPF, Q32I_ init)
{
    pLPF->Q28I_LPF_Tmp = Q16I_LFT_14(init);
    pLPF->Q14I_LPF_Out = init;
}

/**********************************************************************************************
Function: LPF_Cal_T
Description: 定点低通滤波计算
Input: 无
Output: 无
Input_Output: 定点低通滤波指针
Return: 无
Author: CJYS
***********************************************************************************************/
void LPF_Cal_T(ST_LPF_T* pLPF)
{
    pLPF->Q28I_LPF_Tmp += pLPF->Q14I_LPF_Coeff*(pLPF->Q14I_LPF_In - Q32I_RHT_14(pLPF->Q28I_LPF_Tmp));
    pLPF->Q14I_LPF_Out = Q32I_RHT_14(pLPF->Q28I_LPF_Tmp);
}

/**********************************************************************************************
Function: MEAN_Init_T
Description: 定点平均值滤波初始化
Input: 无
Output: 无
Input_Output: 定点平均值滤波指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MEAN_Init_T(ST_MEAN_T* pMEAN)
{
    pMEAN->Q32U_MEAN_Cnt = 0U;
    
    pMEAN->Q14I_MEAN_Tmp = 0;
    pMEAN->Q14I_MEAN_Out = 0;
}

/**********************************************************************************************
Function: MEAN_Cal_T
Description: 定点平均值滤波计算
Input: 无
Output: 无
Input_Output: 定点平均值滤波指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MEAN_Cal_T(ST_MEAN_T* pMEAN)
{
    pMEAN->Q32U_MEAN_Cnt++;
    pMEAN->Q14I_MEAN_Tmp += pMEAN->Q14I_MEAN_In;
    
    if(pMEAN->Q32U_MEAN_Cnt >= pMEAN->Q32U_MEAN_Num)
    {
        pMEAN->Q14I_MEAN_Out = pMEAN->Q14I_MEAN_Tmp>>pMEAN->Q32U_MEAN_Bit;
        
        pMEAN->Q32U_MEAN_Cnt = 0U;
        pMEAN->Q14I_MEAN_Tmp = 0;
    }
    else
    {
        
    }
}

/**********************************************************************************************
Function: MAX_Init_T
Description: 定点最大值滤波初始化
Input: 无
Output: 无
Input_Output: 定点最大值滤波指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MAX_Init_T(ST_MAX_T* pMAX)
{
    pMAX->Q32U_MAX_Cnt = 0U;
    
    pMAX->Q14I_MAX_Tmp = 0;
    pMAX->Q14I_MAX_Out = 0;
}

/**********************************************************************************************
Function: MAX_Cal_T
Description: 定点最大值滤波计算
Input: 输入需大于0
Output: 无
Input_Output: 定点最大值滤波指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MAX_Cal_T(ST_MAX_T* pMAX)
{
    pMAX->Q32U_MAX_Cnt++;
    if(pMAX->Q14I_MAX_In >= pMAX->Q14I_MAX_Tmp)
    {
        pMAX->Q14I_MAX_Tmp = pMAX->Q14I_MAX_In;
    }
    
    if(pMAX->Q32U_MAX_Cnt >= pMAX->Q32U_MAX_Num)
    {
        pMAX->Q14I_MAX_Out = pMAX->Q14I_MAX_Tmp;
        
        pMAX->Q32U_MAX_Cnt = 0U;
        pMAX->Q14I_MAX_Tmp = 0;
    }
    else
    {
        
    }
}
