/**************************************************************************************************
*     File Name :                        MCFOC_EST_F.h
*     Library/Module Name :              MCFOC_F
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             速度角度观测器头文件
**************************************************************************************************/

#ifndef MCFOC_EST_F_H
#define MCFOC_EST_F_H


#include "MATH_ANGLE_F.h"
#include "MATH_LPF_F.h"
#include "MATH_PID_F.h"
#include "MATH_TABLE_F.h"
#include "MCFOC_PMSM_F.h"


typedef struct
{
    ST_LPF_F        FL_EMF_Ialfa_err;
    ST_LPF_F        FL_EMF_Ibeta_err;

    float       _V_F_EMF_Ialfa_Last;
    float       _V_F_EMF_Ibeta_Last;

    float       _O_F_EMF_Ealfa;
    float       _O_F_EMF_Ebeta;

    float       _D_F_EMF_Rs;
    float       _D_F_EMF_Ls_Over_Ts;
}ST_EMF_CONTROL_F;

typedef struct
{
    ST_PID_POS_F    PID_SMO_PLL;
    ST_LPF_F        FL_SMO_FREQ;
    ST_TRIG_F       TG_SMO_Triangle;
    ST_TRIG_F       TG_SMO_Triangle_Comp;
    
    float       _V_F_SMO_Aalfa;
    float       _V_F_SMO_Abeta;
    float       _V_F_SMO_Ealfa;
    float       _V_F_SMO_Ebeta;
    
    float       _D_F_SMO_H1_Set;
    float       _D_F_SMO_Ts;
    float       _D_F_SMO_One_Over_Ld;
    float       _D_F_SMO_Rs_Over_Ld;
    float       _D_F_SMO_Ld_Lq_Over_Ld;
    
    float       _P_F_SMO_H1;
    float       _P_F_SMO_PLL_Kp;
    float       _P_F_SMO_PLL_Ki;
    TABLE_1D_F  TAB_SMO_H1_Coeff;
    TABLE_1D_F  TAB_SMO_Kp_Coeff;
    TABLE_1D_F  TAB_SMO_Ki_Coeff;
    TABLE_2D_F  TAB_SMO_Angle_Comp;
}ST_SMO_CONTROL_F;

typedef struct
{
    ST_PID_POS_F    PID_FLUX_PLL;
    ST_LPF_F        FL_FLUX_FREQ;
    ST_TRIG_F       TG_FLUX_Triangle;
    ST_TRIG_F       TG_FLUX_Triangle_Comp;
    
    float       _V_F_FLUX_Xalfa;
    float       _V_F_FLUX_Xbeta;

    float       _D_F_FLUX_Gamma_Set;
    float       _D_F_FLUX_Ts;
    float       _D_F_FLUX_Ld;
    float       _D_F_FLUX_Lq;
    float       _D_F_FLUX_Flux;
    
    float       _P_F_FLUX_Gamma;
    float       _P_F_FLUX_PLL_Kp;
    float       _P_F_FLUX_PLL_Ki;
    TABLE_1D_F  TAB_FLUX_Gamma_Coeff;
    TABLE_1D_F  TAB_FLUX_Kp_Coeff;
    TABLE_1D_F  TAB_FLUX_Ki_Coeff;
    TABLE_2D_F  TAB_FLUX_Angle_Comp;
}ST_FLUX_CONTROL_F;


/**********************************************************************************************
Function: MCFOC_EST_EMF_Init_F
Description: 反电动势观测器初始化
Input: 无
Output: 无
Input_Output: 反电动势观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_EST_EMF_Init_F(ST_EMF_CONTROL_F* pEMF);

/**********************************************************************************************
Function: MCFOC_EST_EMF_Adapt_F
Description: 反电动势观测器参数自适应
Input: 无
Output: 无
Input_Output: 反电动势观测器指针，PMSM参数指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_EST_EMF_Adapt_F(ST_EMF_CONTROL_F* pEMF, ST_PMSM_PARA_F* pPMSMa);

/**********************************************************************************************
Function: MCFOC_EST_EMF_F
Description: 反电动势观测器计算
Input: 无
Output: 无
Input_Output: 反电动势观测器指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_EST_EMF_F(ST_EMF_CONTROL_F* pEMF, ST_PMSM_ELEC_F* pPMSMe);

/**********************************************************************************************
Function: MCFOC_EST_SMO_Init_F
Description: 滑模观测器初始化
Input: 无
Output: 无
Input_Output: 滑模观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_EST_SMO_Init_F(ST_SMO_CONTROL_F* pSMO);

/**********************************************************************************************
Function: MCFOC_EST_SMO_Adapt_F
Description: SMO观测器参数自适应
Input: 无
Output: 无
Input_Output: SMO观测器指针，PMSM电信号指针，PMSM参数指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_EST_SMO_Adapt_F(ST_SMO_CONTROL_F* pSMO, ST_PMSM_ELEC_F* pPMSMe, ST_PMSM_PARA_F* pPMSMa);

/**********************************************************************************************
Function: MCFOC_EST_SMO_F
Description: 滑模观测器计算
Input: 无
Output: 无
Input_Output: 滑模观测器指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_EST_SMO_F(ST_SMO_CONTROL_F* pSMO, ST_PMSM_ELEC_F* pPMSMe);

/**********************************************************************************************
Function: MCFOC_EST_FLUX_Init_F
Description: 磁链观测器初始化
Input: 无
Output: 无
Input_Output: 磁链观测器指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_EST_FLUX_Init_F(ST_FLUX_CONTROL_F* pFLUX);

/**********************************************************************************************
Function: MCFOC_EST_FLUX_Adapt_F
Description: FLUX观测器参数自适应
Input: 无
Output: 无
Input_Output: FLUX观测器指针，PMSM电信号指针，PMSM参数指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_EST_FLUX_Adapt_F(ST_FLUX_CONTROL_F* pFLUX, ST_PMSM_ELEC_F* pPMSMe, ST_PMSM_PARA_F* pPMSMa);

/**********************************************************************************************
Function: MCFOC_EST_FLUX_F
Description: 磁链观测器计算
Input: 无
Output: 无
Input_Output: 磁链观测器指针，PMSM电信号指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MCFOC_EST_FLUX_F(ST_FLUX_CONTROL_F* pFLUX, ST_PMSM_ELEC_F* pPMSMe);


#endif /* MCFOC_EST_F_H */
