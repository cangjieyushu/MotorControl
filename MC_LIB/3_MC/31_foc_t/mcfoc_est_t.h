/*
*     File Name :                        mcfoc_est_t
*     Library/Module Name :              mcfoc_t
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             速度角度观测器
*/


#ifndef MCFOC_EST_T_H
#define MCFOC_EST_T_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "math_angle_t.h"
#include "math_filter_t.h"
#include "math_pid_t.h"
#include "math_table_t.h"
#include "mcfoc_pmsm_t.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/
typedef struct
{
    ST_LPF_T        FL_EMF_Ialfa_err;
    ST_LPF_T        FL_EMF_Ibeta_err;

    Q32I_       V_Q14I_EMF_Ialfa_Last;
    Q32I_       V_Q14I_EMF_Ibeta_Last;

    Q32I_       O_Q14I_EMF_Ealfa;
    Q32I_       O_Q14I_EMF_Ebeta;

    Q32I_       D_Q14I_EMF_Rs;
    Q32I_       D_Q10I_EMF_Ls_Over_Ts;
}ST_EMF_CONTROL_T;

typedef struct
{
    ST_PID_POS_T    PID_SMO_PLL;
    ST_LPF_T        FL_SMO_FREQ;
    ST_TRIG_T       TG_SMO_Triangle;
    ST_TRIG_T       TG_SMO_Triangle_Comp;
    
    Q32I_       V_Q28I_SMO_Angle_tmp;
    Q32I_       V_Q28I_SMO_Aalfa;
    Q32I_       V_Q28I_SMO_Abeta;
    Q32I_       V_Q14I_SMO_Aalfa;
    Q32I_       V_Q14I_SMO_Abeta;
    Q32I_       V_Q14I_SMO_Ealfa;
    Q32I_       V_Q14I_SMO_Ebeta;
    
    Q32I_       D_Q14I_SMO_H1_Set;
    Q32I_       D_Q14I_SMO_Ts;
    Q32I_       D_Q10I_SMO_One_Over_Ld;
    Q32I_       D_Q10I_SMO_Rs_Over_Ld;
    Q32I_       D_Q14I_SMO_Ld_Lq_Over_Ld;
    
    Q32I_       P_Q14I_SMO_H1;
    Q32I_       P_Q14I_SMO_PLL_Kp;
    Q32I_       P_Q14I_SMO_PLL_Ki;
    TABLE_1D_T  TAB_SMO_H1_Coeff;
    TABLE_1D_T  TAB_SMO_Kp_Coeff;
    TABLE_1D_T  TAB_SMO_Ki_Coeff;
    TABLE_2D_T  TAB_SMO_Angle_Comp;
}ST_SMO_CONTROL_T;

typedef struct
{
    ST_PID_POS_T    PID_FLUX_PLL;
    ST_LPF_T        FL_FLUX_FREQ;
    ST_TRIG_T       TG_FLUX_Triangle;
    ST_TRIG_T       TG_FLUX_Triangle_Comp;
    
    Q32I_       V_Q28I_FLUX_Angle_tmp;
    Q32I_       V_Q28I_FLUX_Xalfa;
    Q32I_       V_Q28I_FLUX_Xbeta;

    Q32I_       D_Q14I_FLUX_Gamma_Set;
    Q32I_       D_Q14I_FLUX_Ts;
    Q32I_       D_Q14I_FLUX_Ld;
    Q32I_       D_Q14I_FLUX_Lq;
    Q32I_       D_Q14I_FLUX_Flux;
    
    Q32I_       P_Q14I_FLUX_Gamma;
    Q32I_       P_Q14I_FLUX_PLL_Kp;
    Q32I_       P_Q14I_FLUX_PLL_Ki;
    TABLE_1D_T  TAB_FLUX_Gamma_Coeff;
    TABLE_1D_T  TAB_FLUX_Kp_Coeff;
    TABLE_1D_T  TAB_FLUX_Ki_Coeff;
    TABLE_2D_T  TAB_FLUX_Angle_Comp;
}ST_FLUX_CONTROL_T;


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: MCFOC_EST_EMF_Init_T
Description: 反电动势观测器初始化
Input: 无
Output: 无
Input_Output: 反电动势观测器指针
Return: 无
Author: CJYS
*/
void MCFOC_EST_EMF_Init_T(ST_EMF_CONTROL_T* pEMF);

/*
Function: MCFOC_EST_EMF_Adapt_T
Description: 反电动势观测器参数自适应
Input: 无
Output: 无
Input_Output: 反电动势观测器指针，PMSM参数指针
Return: 无
Author: CJYS
*/
void MCFOC_EST_EMF_Adapt_T(ST_EMF_CONTROL_T* pEMF, ST_PMSM_PARA_T* pPMSMa);

/*
Function: MCFOC_EST_EMF_Cal_T
Description: 反电动势观测器计算
Input: 无
Output: 无
Input_Output: 反电动势观测器指针，PMSM电信号指针
Return: 无
Author: CJYS
*/
void MCFOC_EST_EMF_Cal_T(ST_EMF_CONTROL_T* pEMF, ST_PMSM_ELEC_T* pPMSMe);

/*
Function: MCFOC_EST_SMO_Init_T
Description: 滑模观测器初始化
Input: 无
Output: 无
Input_Output: 滑模观测器指针
Return: 无
Author: CJYS
*/
void MCFOC_EST_SMO_Init_T(ST_SMO_CONTROL_T* pSMO);

/*
Function: MCFOC_EST_SMO_Adapt_T
Description: SMO观测器参数自适应
Input: 无
Output: 无
Input_Output: SMO观测器指针，PMSM电信号指针，PMSM参数指针
Return: 无
Author: CJYS
*/
void MCFOC_EST_SMO_Adapt_T(ST_SMO_CONTROL_T* pSMO, ST_PMSM_ELEC_T* pPMSMe, ST_PMSM_PARA_T* pPMSMa);

/*
Function: MCFOC_EST_SMO_Cal_T
Description: 滑模观测器计算
Input: 无
Output: 无
Input_Output: 滑模观测器指针，PMSM电信号指针
Return: 无
Author: CJYS
*/
void MCFOC_EST_SMO_Cal_T(ST_SMO_CONTROL_T* pSMO, ST_PMSM_ELEC_T* pPMSMe);

/*
Function: MCFOC_EST_FLUX_Init_T
Description: 磁链观测器初始化
Input: 无
Output: 无
Input_Output: 磁链观测器指针
Return: 无
Author: CJYS
*/
void MCFOC_EST_FLUX_Init_T(ST_FLUX_CONTROL_T* pFLUX);

/*
Function: MCFOC_EST_FLUX_Adapt_T
Description: FLUX观测器参数自适应
Input: 无
Output: 无
Input_Output: FLUX观测器指针，PMSM电信号指针，PMSM参数指针
Return: 无
Author: CJYS
*/
void MCFOC_EST_FLUX_Adapt_T(ST_FLUX_CONTROL_T* pFLUX, ST_PMSM_ELEC_T* pPMSMe, ST_PMSM_PARA_T* pPMSMa);

/*
Function: MCFOC_EST_FLUX_Cal_T
Description: 磁链观测器计算
Input: 无
Output: 无
Input_Output: 磁链观测器指针，PMSM电信号指针
Return: 无
Author: CJYS
*/
void MCFOC_EST_FLUX_Cal_T(ST_FLUX_CONTROL_T* pFLUX, ST_PMSM_ELEC_T* pPMSMe);


#endif /* MCFOC_EST_T_H */
