/**************************************************************************************************
*     File Name :                        Math.h
*     Library/Module Name :              MATH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             数学运算库头文件
**************************************************************************************************/
#ifndef Math_H
#define Math_H

/**********************************定点数学库**********************************/

typedef unsigned    char            Q08U_;

typedef unsigned    short int       Q16U_;
typedef unsigned    int             Q32U_;

typedef signed      short int       Q16I_;
typedef signed      int             Q32I_;
                 
typedef unsigned    int             ALL;
typedef unsigned    int             BIT;

#define Q02U_MAX                    (4.0f)
#define Q04U_MAX                    (16.0f)
#define Q08U_MAX                    (256.0f)
#define Q10U_MAX                    (1024.0f)
#define Q12U_MAX                    (4096.0f)
#define Q14U_MAX                    (16384.0f)
#define Q16U_MAX                    (65536.0f)
#define Q20U_MAX                    (1048576.0f)
#define Q22U_MAX                    (4194304.0f)
#define Q24U_MAX                    (16777216.0f)
#define Q28U_MAX                    (268435456.0f)
#define Q30U_MAX                    (1073741824.0f)
#define Q32U_MAX                    (4294967295.0f)

#define Q16I_LFT_01(A)              ((A)<<1U)
#define Q16I_LFT_02(A)              ((A)<<2U)
#define Q16I_LFT_03(A)              ((A)<<3U)
#define Q16I_LFT_04(A)              ((A)<<4U)
#define Q16I_LFT_05(A)              ((A)<<5U)
#define Q16I_LFT_06(A)              ((A)<<6U)
#define Q16I_LFT_07(A)              ((A)<<7U)
#define Q16I_LFT_08(A)              ((A)<<8U)

#define Q16I_LFT_09(A)              ((A)<<9U)
#define Q16I_LFT_10(A)              ((A)<<10U)
#define Q16I_LFT_11(A)              ((A)<<11U)
#define Q16I_LFT_12(A)              ((A)<<12U)
#define Q16I_LFT_13(A)              ((A)<<13U)
#define Q16I_LFT_14(A)              ((A)<<14U)
#define Q16I_LFT_15(A)              ((A)<<15U)
#define Q16I_LFT_16(A)              ((A)<<16U)

#define Q16I_LFT_17(A)              ((A)<<17U)
#define Q16I_LFT_18(A)              ((A)<<18U)
#define Q16I_LFT_19(A)              ((A)<<19U)
#define Q16I_LFT_20(A)              ((A)<<20U)
#define Q16I_LFT_21(A)              ((A)<<21U)
#define Q16I_LFT_22(A)              ((A)<<22U)
#define Q16I_LFT_23(A)              ((A)<<23U)
#define Q16I_LFT_24(A)              ((A)<<24U)

#define Q16I_LFT_25(A)              ((A)<<25U)
#define Q16I_LFT_26(A)              ((A)<<26U)
#define Q16I_LFT_27(A)              ((A)<<27U)
#define Q16I_LFT_28(A)              ((A)<<28U)
#define Q16I_LFT_29(A)              ((A)<<29U)
#define Q16I_LFT_30(A)              ((A)<<30U)
#define Q16I_LFT_31(A)              ((A)<<31U)
#define Q16I_LFT_32(A)              ((A)<<32U)

#define Q32I_RHT_01(A)              ((A)>>1U)
#define Q32I_RHT_02(A)              ((A)>>2U)
#define Q32I_RHT_03(A)              ((A)>>3U)
#define Q32I_RHT_04(A)              ((A)>>4U)
#define Q32I_RHT_05(A)              ((A)>>5U)
#define Q32I_RHT_06(A)              ((A)>>6U)
#define Q32I_RHT_07(A)              ((A)>>7U)
#define Q32I_RHT_08(A)              ((A)>>8U)

#define Q32I_RHT_09(A)              ((A)>>9U)
#define Q32I_RHT_10(A)              ((A)>>10U)
#define Q32I_RHT_11(A)              ((A)>>11U)
#define Q32I_RHT_12(A)              ((A)>>12U)
#define Q32I_RHT_13(A)              ((A)>>13U)
#define Q32I_RHT_14(A)              ((A)>>14U)
#define Q32I_RHT_15(A)              ((A)>>15U)
#define Q32I_RHT_16(A)              ((A)>>16U)
                                  
#define Q32I_RHT_17(A)              ((A)>>17U)
#define Q32I_RHT_18(A)              ((A)>>18U)
#define Q32I_RHT_19(A)              ((A)>>19U)
#define Q32I_RHT_20(A)              ((A)>>20U)
#define Q32I_RHT_21(A)              ((A)>>21U)
#define Q32I_RHT_22(A)              ((A)>>22U)
#define Q32I_RHT_23(A)              ((A)>>23U)
#define Q32I_RHT_24(A)              ((A)>>24U)

#define Q32I_RHT_25(A)              ((A)>>25U)
#define Q32I_RHT_26(A)              ((A)>>26U)
#define Q32I_RHT_27(A)              ((A)>>27U)
#define Q32I_RHT_28(A)              ((A)>>28U)
#define Q32I_RHT_29(A)              ((A)>>29U)
#define Q32I_RHT_30(A)              ((A)>>30U)
#define Q32I_RHT_31(A)              ((A)>>31U)
#define Q32I_RHT_32(A)              ((A)>>32U)

/********************************************************************/

typedef struct
{
    Q32I_ Q12U_Angle;
    Q32I_ Q14I_Cos;
    Q32I_ Q14I_Sin;
    Q32I_ Q12U_ReAngle;
}ST_TRIG_T;

#define MATH_FILTER_MAX_T                   ((Q16I_)(Q08U_MAX))

#define MATH_PI_T                           (2048)
#define MATH_2PI_T                          (MATH_PI_T*2)
#define MATH_PI_OVER_TWO_T                  (MATH_PI_T/2)
#define MATH_PI_OVER_FOUR_T                 (MATH_PI_T/4)
#define MATH_PI_OVER_SIX_T                  (MATH_PI_T/6)
#define MATH_2PI_TMP_T                      ((Q32I_)(Q28U_MAX))

#define MATH_ANGLE_MOD_T(A)                 while(A>=MATH_2PI_T){A-=MATH_2PI_T;}while(A<0){A+=MATH_2PI_T;}
#define MATH_ANGLE_TMP_T(A)                 while(A>=MATH_2PI_TMP_T){A-=MATH_2PI_TMP_T;}while(A<0){A+=MATH_2PI_TMP_T;}
    
#define MATH_SQRT_THREE_T(A)                (Q32I_RHT_12(7095*(A)))
#define MATH_SQRT_THREE_OVER_TWO_T(A)       (Q32I_RHT_12(3547*(A)))
#define MATH_ONE_OVER_SQRT_THREE_T(A)       (Q32I_RHT_12(2365*(A)))
#define MATH_ONE_OVER_THREE_T(A)            (Q32I_RHT_12(1365*(A)))

#define MATH_SQUARE_T(A)                    ((A)*(A))
#define MATH_SIGN_T(A)                      (((A)<(0)) ? (-1) : (1))
#define MATH_ABS_T(A)                       (((A)<(0)) ? (-(A)) : (A))
#define MATH_MAX_T(A, B)                    (((A)>(B)) ?   (A)  : (B))
#define MATH_MIN_T(A, B)                    (((A)<(B)) ?   (A)  : (B))
#define MATH_SAT_T(A, MAX, MIN)             (MATH_MAX_T(MATH_MIN_T((A), (MAX)), (MIN)))

/**********************************浮点数学库***********************************/

typedef struct
{
    float F_Angle;
    float F_Cos;
    float F_Sin;
    float F_ReAngle;
}ST_TRIG_F;

#define MATH_PI_F                           (3.1415926535897932384626433832795f)
#define MATH_2PI_F                          (2.0f*MATH_PI_F)
#define MATH_PI_OVER_TWO_F                  (MATH_PI_F/2.0f)
#define MATH_PI_OVER_FOUR_F                 (MATH_PI_F/4.0f)
#define MATH_PI_OVER_SIX_F                  (MATH_PI_F/6.0f)

#define MATH_ANGLE_MOD_F(A)                 while(A>1.0f){A-=1.0f;}while(A<0.0f){A+=1.0f;}

#define MATH_ONE_OVER_THREE_F               (1.0f/3.0f)
#define MATH_SQRT_THREE_F                   (1.7320508075688772935274463415059f)
#define MATH_ONE_OVER_SQRT_THREE_F          (1.0f/MATH_SQRT_THREE_F)
#define MATH_SQRT_THREE_OVER_TWO_F          (MATH_SQRT_THREE_F/2.0f)

#define MATH_SQUARE_F(A)                    ((A)*(A))
#define MATH_SIGN_F(A)                      (((A)<(0.0f)) ? (-1.0f) : (1.0f))
#define MATH_ABS_F(A)                       (((A)<(0.0f)) ? (-(A)) : (A))
#define MATH_MAX_F(A, B)                    (((A)>(B)   ) ?   (A)  : (B))
#define MATH_MIN_F(A, B)                    (((A)<(B)   ) ?   (A)  : (B))
#define MATH_SAT_F(A, MAX, MIN)             (MATH_MAX_F(MATH_MIN_F((A), (MAX)), (MIN)))

/**********************************************************************/

#define MATH_DELAY_NS_COUNT                 (1U)
#define MATH_DELAY_US_COUNT                 (21U)
#define MATH_DELAY_MS_COUNT                 (21850U)

typedef struct
{
    Q32I_ Q14I_Init;
    Q32I_ Q14I_Target;
    Q32I_ Q24I_ADDStep;
    Q32I_ Q24I_SUBStep;
    Q32I_ Q24I_Output_tmp;
    Q32I_ Q14I_Output;
}ST_RAMP_T;

typedef struct
{
    Q32I_ Q16I_Filter_in;
    Q32I_ Q16I_Filter_out;
    Q32I_ Q24I_Filter_tmp;
    Q32I_ Q08I_Filter_Coeff;
}ST_FILTER_T;

typedef struct
{
    Q32I_ Q14I_Rf;
    Q32I_ Q14I_Fb;
    
    Q32I_ Q14I_Kp;
    Q32I_ Q14I_Ki;
    Q32I_ Q14I_Kd;
    
    Q32I_ Q28I_Step;
    Q32I_ Q28I_StepMax;
    Q32I_ Q28I_StepMin;
    
    Q32I_ Q14I_Output;
    Q32I_ Q28I_Output_tmp;
    Q32I_ Q14I_OutMax;
    Q32I_ Q14I_OutMin;
    
    Q32I_ Q14I_LastError;   
    Q32I_ Q14I_PrevError;
}ST_PID_INC_T;

typedef struct
{
    Q32I_ Q14I_Rf;
    Q32I_ Q14I_Fb;
    
    Q32I_ Q14I_Kp;
    Q32I_ Q14I_Ki;
    Q32I_ Q14I_Kd;
    
    Q32I_ Q14I_Ui;
    Q32I_ Q28I_Ui_tmp;
    Q32I_ Q14I_Output;
    Q32I_ Q14I_OutMax;
    Q32I_ Q14I_OutMin;
}ST_PID_POS_T;

typedef struct
{
    Q32I_ Q28I_Rf;
    Q32I_ Q28I_Fb;
    
    Q32I_ Q00I_Kp;
    Q32I_ Q00I_Ki;
    Q32I_ Q00I_Kd;
    
    Q32I_ Q14I_Ui;
    Q32I_ Q18I_Ui_tmp;
    Q32I_ Q14I_Output;
    Q32I_ Q14I_OutMax;
    Q32I_ Q14I_OutMin;
}ST_PID_POS_P;

/**********************************************************************************************
Function: Ramp_Init_T
Description: 定点斜坡初始化
Input: 定点斜坡输出初始值
Output: 无
Input_Output: 定点斜坡指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Ramp_Init_T(ST_RAMP_T* pRamp, Q32I_ init);

/**********************************************************************************************
Function: Ramp_Cal_T
Description: 定点斜坡计算
Input: 无
Output: 无
Input_Output: 定点斜坡指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Ramp_Cal_T(ST_RAMP_T* pRamp);

/**********************************************************************************************
Function: Filter_Init_T
Description: 定点低通滤波初始化
Input: 定点低通滤波初始值
Output: 无
Input_Output: 定点低通滤波指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Filter_Init_T(ST_FILTER_T* pFltr, Q32I_ init);

/**********************************************************************************************
Function: Filter_Cal_T
Description: 定点低通滤波计算
Input: 无
Output: 无
Input_Output: 定点低通滤波指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Filter_Cal_T(ST_FILTER_T* pFltr);
    
/**********************************************************************************************
Function: PID_Inc_Init_T
Description: 定点增量式PID初始化
Input: 定点积分器初始值
Output: 无
Input_Output: 定点增量式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Inc_Init_T(ST_PID_INC_T* pPID, Q32I_ init);

/**********************************************************************************************
Function: PID_Inc_Cal_T
Description: 定点增量式PID计算
Input: 无
Output: 无
Input_Output: 定点增量式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Inc_Cal_T(ST_PID_INC_T* pPID);

/**********************************************************************************************
Function: PID_Pos_Init_T
Description: 定点位置式PID初始化
Input: 定点积分器初始值
Output: 无
Input_Output: 定点位置式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Pos_Init_T(ST_PID_POS_T* pPID, Q32I_ init);

/**********************************************************************************************
Function: PID_Pos_Cal_T
Description: 定点位置式PID计算
Input: 无
Output: 无
Input_Output: 定点位置式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Pos_Cal_T(ST_PID_POS_T* pPID);

/**********************************************************************************************
Function: Math_SinCos_T
Description: 定点正余弦计算
Input: 角度，0到4096
Output: 正弦，余弦
Input_Output: 定点角度指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Math_SinCos_T(ST_TRIG_T* TIG);

/**********************************************************************************************
Function: Math_Atan_T
Description: 定点反正切计算
Input: 正弦，余弦
Output: 角度，0到4096
Input_Output: 定点角度指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Math_Atan_T(ST_TRIG_T* pTIG);

/********************************************************************/

typedef struct
{
    float F_Init;
    float F_Target;
    float F_ADDStep;
    float F_SUBStep;
    float F_Output;
}ST_RAMP_F;

typedef struct
{
    float F_Filter_in;
    float F_Filter_out;
    float F_Filter_Coeff;
}ST_FILTER_F;

typedef struct
{
    float F_Rf;
    float F_Fb;
    
    float F_Kp;
    float F_Ki;
    float F_Kd;
    
    float F_Ui;
    float F_Output;
    float F_OutMax;
    float F_OutMin;
}ST_PID_POS_F;

typedef struct
{
    float F_Rf;
    float F_Fb;
    
    float F_Kp;
    float F_Ki;
    float F_Kd;
    float F_Kc;
    
    float F_Ui;
    float F_USat;
    float F_Output;
    float F_OutMax;
    float F_OutMin;
}ST_PID_SAT_F;

/**********************************************************************************************
Function: Ramp_Init_F
Description: 浮点斜坡初始化
Input: 浮点斜坡输出初始值
Output: 无
Input_Output: 浮点斜坡指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Ramp_Init_F(ST_RAMP_F* pRamp, float init);

/**********************************************************************************************
Function: Ramp_Cal_F
Description: 浮点斜坡计算
Input: 无
Output: 无
Input_Output: 浮点斜坡指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Ramp_Cal_F(ST_RAMP_F* pRamp);

/**********************************************************************************************
Function: Filter_Init_F
Description: 浮点低通滤波初始化
Input: 浮点低通滤波初始值
Output: 无
Input_Output: 浮点低通滤波指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Filter_Init_F(ST_FILTER_F* pFltr, float init);

/**********************************************************************************************
Function: Filter_Cal_F
Description: 浮点低通滤波计算
Input: 无
Output: 无
Input_Output: 浮点低通滤波指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Filter_Cal_F(ST_FILTER_F* pFltr);

/**********************************************************************************************
Function: PID_Pos_Init_F
Description: 浮点位置式PID初始化
Input: 浮点积分器初始值
Output: 无
Input_Output: 浮点位置式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Pos_Init_F(ST_PID_POS_F* pPID, float init);

/**********************************************************************************************
Function: PID_Pos_Cal_F
Description: 浮点位置式PID计算
Input: 无
Output: 无
Input_Output: 浮点位置式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Pos_Cal_F(ST_PID_POS_F* pPID);

/**********************************************************************************************
Function: PID_Sat_Init_F
Description: 抗饱和位置式PID初始化
Input: 抗饱和积分器初始值
Output: 无
Input_Output: 抗饱和位置式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Sat_Init_F(ST_PID_SAT_F* pPID, float init);

/**********************************************************************************************
Function: PID_Sat_Cal_F
Description: 抗饱和位置式PID计算
Input: 无
Output: 无
Input_Output: 抗饱和位置式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Sat_Cal_F(ST_PID_SAT_F* pPID);

/**********************************************************************************************
Function: Math_SinCos_F
Description: 浮点正余弦计算
Input: 角度，0到2PI
Output: 正弦，余弦
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Math_SinCos_F(ST_TRIG_F* pTIG);

/**********************************************************************************************
Function: Math_Atan_F
Description: 浮点反正切计算
Input: 正弦，余弦
Output: 角度，0到2PI
Input_Output: 浮点角度指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Math_Atan_F(ST_TRIG_F* pTIG);

/**********************************************************************************************
Function: Math_Sqrt_F
Description: 浮点平方根计算
Input: 正浮点数
Output: 平方根
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
float Math_Sqrt_F(float A);

/********************************延迟函数**********************************/

/**********************************************************************************************
Function: Delay_ns
Description: ns延迟
Input: 时间值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Delay_ns(Q32U_ time);

/**********************************************************************************************
Function: Delay_us
Description: us延迟
Input: 时间值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Delay_us(Q32U_ time);

/**********************************************************************************************
Function: Delay_ms
Description: ms延迟
Input: 时间值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Delay_ms(Q32U_ time);

#endif /* Math_H */
