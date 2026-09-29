/*
*     File Name :                        mcfoc_pmsm_f
*     Library/Module Name :              mcfoc_f
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             FOC电机参数
*/


#ifndef MCFOC_PMSM_F_H
#define MCFOC_PMSM_F_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "math_angle_f.h"
#include "math_filter_f.h"
#include "math_ramp_f.h"
#include "math_table_f.h"
#include "math_check.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/
typedef struct
{
    ST_MEAN_F   Mean_Freq;
    ST_MEAN_F   Mean_Vbus;
    ST_MEAN_F   Mean_Ibus;
    ST_MEAN_F   Mean_Id;
    ST_MEAN_F   Mean_Iq;
    ST_MEAN_F   Mean_Ud;
    ST_MEAN_F   Mean_Uq;
    ST_MEAN_F   Mean_Es;
    
    ST_MAX_F    Max_Ia;
    ST_MAX_F    Max_Ib;
    ST_MAX_F    Max_Ic;
    
    ST_MEAN_F   Mean_Ibus_10ms;
    ST_MEAN_F   Mean_Is_1000ms;
}ST_PMSM_FILTER_F;

typedef struct
{
    float       I_F_DIR_Target;
    float       I_F_Ibus;
    
    Q32I_       I_Q12I_Ia_Data;
    Q32I_       I_Q12I_Ib_Data;
    Q32I_       I_Q12I_Ic_Data;
    Q32I_       I_Q12I_Ia_Offset;
    Q32I_       I_Q12I_Ib_Offset;
    Q32I_       I_Q12I_Ic_Offset;
    
    Q32I_       I_Q12I_Ishunt_1_Data;
    Q32I_       I_Q12I_Ishunt_2_Data;
    Q32I_       I_Q12I_Ishunt_Offset;
    
    float       I_F_Ishunt[3];
    float       V_F_Ia;
    float       V_F_Ib;
    float       V_F_Ic;
    float       V_F_Ialfa;
    float       V_F_Ibeta;
    float       V_F_Ualfa;
    float       V_F_Ubeta;
    
    ST_TRIG_F   TG_Triangle_Est;
    ST_TRIG_F   TG_Triangle_Comp;
    ST_TRIG_F   TG_Triangle_Pre;
    
    float       V_F_Sin_Real;
    float       V_F_Cos_Real;
    float       V_F_Id_Real;
    float       V_F_Iq_Real;
    float       V_F_Ud_Real;
    float       V_F_Uq_Real;
    
    float       V_F_Sin_Pre;
    float       V_F_Cos_Pre;
    float       V_F_Ia_Pre;
    float       V_F_Ib_Pre;
    float       V_F_Ic_Pre;
    float       V_F_Ualfa_Pre;
    float       V_F_Ubeta_Pre;
    
    float       O_F_Active_Power;
    float       O_F_Reactive_Power;
    
    float       O_F_Freq;
    float       O_F_Vbus;
    float       O_F_Is;
    float       O_F_Us;
    float       O_F_Es;
    float       O_F_One_Over_Vbus;
    float       O_F_Modulation_Rate;
    float       O_F_UsRef;
    float       O_F_Ibus_10ms;
    float       O_F_Is_1000ms;
    
    float       P_F_Modulation_Mode;
    float       P_F_UsRef_Scale;
    float       P_F_Pre_Period;
}ST_PMSM_ELEC_F;

typedef struct
{
    ST_RAMP_F   Ramp_PWM_FREQ;
    ST_CHECK    PWM_FREQ_CHECK;
    Q32U_       O_Q32U_Low_PWM_Flag;

    float       O_F_Rs;
    float       O_F_Ld;
    float       O_F_Lq;
    float       O_F_Ls;
    float       O_F_Flux;
    float       O_F_Ts;
    
    float       O_F_PWM_Freq_Coeff;
    float       O_F_PWM_Period_Coeff;
    
    float       P_F_Rs;
    float       P_F_Ld;
    float       P_F_Lq;
    float       P_F_Ls;
    float       P_F_Flux;
    float       P_F_Ts;
    
    TABLE_1D_F  TAB_Lq_Coeff;
    float       P_F_PWM_FREQ_MAX;
    float       P_F_PWM_FREQ_MIN;
}ST_PMSM_PARA_F;


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: MCFOC_PMSM_Para_Init_F
Description: 电机参数初始化
Input: 无
Output: 无
Input_Output: SVPWM控制指针
Return: 无
Author: CJYS
*/
void MCFOC_PMSM_Para_Init_F(ST_PMSM_ELEC_F* pPMSMe);

/*
Function: MCFOC_PMSM_Para_Adapt_F
Description: 电机参数自适应
Input: 无
Output: 无
Input_Output: PMSM信号滤波指针，PMSM电信号指针，PMSM参数指针
Return: 无
Author: CJYS
*/
void MCFOC_PMSM_Para_Adapt_F(ST_PMSM_FILTER_F* pPMSMf, ST_PMSM_ELEC_F* pPMSMe, ST_PMSM_PARA_F* pPMSMa);

/*
Function: MCFOC_PMSM_Clark_F
Description: Clark坐标变换函数a
Input: 无
Output: 无
Input_Output: PMSM电信号指针
Return: 无
Author: CJYS
*/
void MCFOC_PMSM_Clark_F(ST_PMSM_ELEC_F* pPMSMe);

/*
Function: MCFOC_PMSM_Park_F
Description: Park坐标变换函数
Input: 无
Output: 无
Input_Output: PMSM电信号指针
Return: 无
Author: CJYS
*/
void MCFOC_PMSM_Park_F(ST_PMSM_ELEC_F* pPMSMe);

/*
Function: MCFOC_PMSM_Ipark_F
Description: Ipark坐标变换函数
Input: 无
Output: 无
Input_Output: PMSM电信号指针
Return: 无
Author: CJYS
*/
void MCFOC_PMSM_Ipark_F(ST_PMSM_ELEC_F* pPMSMe);

/*
Function: MCFOC_PMSM_Iclark_F
Description: IClark坐标变换函数
Input: 无
Output: 无
Input_Output: PMSM电信号指针
Return: 无
Author: CJYS
*/
void MCFOC_PMSM_Iclark_F(ST_PMSM_ELEC_F* pPMSMe);

/*
Function: MCFOC_PMSM_PQ_F
Description: 功率计算函数
Input: 无
Output: 无
Input_Output: PMSM电信号指针
Return: 无
Author: CJYS
*/
void MCFOC_PMSM_PQ_F(ST_PMSM_ELEC_F* pPMSMe);

#endif /* MCFOC_PMSM_F_H */
