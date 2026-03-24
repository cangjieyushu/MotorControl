/**************************************************************************************************
*     File Name :                        MATH_LPF_F.c
*     Library/Module Name :              MATH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             低通滤波器
**************************************************************************************************/

#include "MATH_LPF_F.h"


/**********************************************************************************************
Function: LPF_Init_F
Description: 浮点低通滤波初始化
Input: 浮点低通滤波初始值
Output: 无
Input_Output: 浮点低通滤波指针
Return: 无
Author: CJYS
***********************************************************************************************/
void LPF_Init_F(ST_LPF_F* pLPF, float init)
{
    pLPF->F_LPF_Out = init;
}

/**********************************************************************************************
Function: LPF_Cal_F
Description: 浮点低通滤波计算
Input: 无
Output: 无
Input_Output: 浮点低通滤波指针
Return: 无
Author: CJYS
***********************************************************************************************/
void LPF_Cal_F(ST_LPF_F* pLPF)
{
    pLPF->F_LPF_Out += pLPF->F_LPF_Coeff*(pLPF->F_LPF_In  - pLPF->F_LPF_Out);
}

/**********************************************************************************************
Function: MEAN_Init_F
Description: 浮点平均值滤波初始化
Input: 无
Output: 无
Input_Output: 浮点平均值滤波指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MEAN_Init_F(ST_MEAN_F* pMEAN)
{
    pMEAN->Q32U_MEAN_Cnt = 0U;
    
    pMEAN->F_MEAN_Tmp = 0.0f;
    pMEAN->F_MEAN_Out = 0.0f;
}

/**********************************************************************************************
Function: MEAN_Cal_F
Description: 浮点平均值滤波计算
Input: 无
Output: 无
Input_Output: 浮点平均值滤波指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MEAN_Cal_F(ST_MEAN_F* pMEAN)
{
    pMEAN->Q32U_MEAN_Cnt++;
    pMEAN->F_MEAN_Tmp += pMEAN->F_MEAN_In;
    
    if(pMEAN->Q32U_MEAN_Cnt >= pMEAN->Q32U_MEAN_Num)
    {
        pMEAN->F_MEAN_Out = pMEAN->F_MEAN_Tmp/((float)pMEAN->Q32U_MEAN_Num);
        
        pMEAN->Q32U_MEAN_Cnt = 0U;
        pMEAN->F_MEAN_Tmp = 0.0f;
    }
    else
    {
        
    }
}

/**********************************************************************************************
Function: MAX_Init_F
Description: 浮点最大值滤波初始化
Input: 无
Output: 无
Input_Output: 浮点最大值滤波指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MAX_Init_F(ST_MAX_F* pMAX)
{
    pMAX->Q32U_MAX_Cnt = 0U;
    
    pMAX->F_MAX_Tmp = 0.0f;
    pMAX->F_MAX_Out = 0.0f;
}

/**********************************************************************************************
Function: MAX_Cal_F
Description: 浮点最大值滤波计算
Input: 输入需大于0
Output: 无
Input_Output: 浮点最大值滤波指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MAX_Cal_F(ST_MAX_F* pMAX)
{
    pMAX->Q32U_MAX_Cnt++;
    if(pMAX->F_MAX_In >= pMAX->F_MAX_Tmp)
    {
        pMAX->F_MAX_Tmp = pMAX->F_MAX_In;
    }
    
    if(pMAX->Q32U_MAX_Cnt >= pMAX->Q32U_MAX_Num)
    {
        pMAX->F_MAX_Out = pMAX->F_MAX_Tmp;
        
        pMAX->Q32U_MAX_Cnt = 0U;
        pMAX->F_MAX_Tmp = 0.0f;
    }
    else
    {
        
    }
}
