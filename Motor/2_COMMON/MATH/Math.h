/**************************************************************************************************
*     File Name :                        Math.h
*     Library/Module Name :              MATH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             数学运算库头文件
**************************************************************************************************/
#ifndef Math_H
#define Math_H

#ifdef __ramfunc
#define Ram_Func                    __ramfunc
#else
#define Ram_Func                     __attribute__ ((section (".ramfunc")))
#endif

/********************************************************************/

typedef unsigned char Q08U_;

typedef unsigned int Q16U_;
typedef unsigned int Q32U_;
typedef signed   int Q16I_;
typedef signed   int Q32I_;
                 
typedef unsigned int ALL;
typedef unsigned int BIT;

#define Q02U_MAX                    (4.0f)
#define Q04U_MAX                    (16.0f)
#define Q08U_MAX                    (256.0f)
#define Q10U_MAX                    (1024.0f)
#define Q12U_MAX                    (4096.0f)
#define Q14U_MAX                    (16384.0f)
#define Q16U_MAX                    (65536.0f)
#define Q20U_MAX                    (1048576.0f)
#define Q24U_MAX                    (16777216.0f)
#define Q28U_MAX                    (268435456.0f)
#define Q30U_MAX                    (1073741824.0f)
#define Q32U_MAX                    (4294967295.0f)

#define Q16I_LFT_01(A)              ((A)<<1)
#define Q16I_LFT_02(A)              ((A)<<2)
#define Q16I_LFT_03(A)              ((A)<<3)
#define Q16I_LFT_04(A)              ((A)<<4)
#define Q16I_LFT_05(A)              ((A)<<5)
#define Q16I_LFT_06(A)              ((A)<<6)
#define Q16I_LFT_07(A)              ((A)<<7)
#define Q16I_LFT_08(A)              ((A)<<8)

#define Q16I_LFT_09(A)              ((A)<<9)
#define Q16I_LFT_10(A)              ((A)<<10)
#define Q16I_LFT_11(A)              ((A)<<11)
#define Q16I_LFT_12(A)              ((A)<<12)
#define Q16I_LFT_13(A)              ((A)<<13)
#define Q16I_LFT_14(A)              ((A)<<14)
#define Q16I_LFT_15(A)              ((A)<<15)
#define Q16I_LFT_16(A)              ((A)<<16)

#define Q16I_LFT_17(A)              ((A)<<17)
#define Q16I_LFT_18(A)              ((A)<<18)
#define Q16I_LFT_19(A)              ((A)<<19)
#define Q16I_LFT_20(A)              ((A)<<20)
#define Q16I_LFT_21(A)              ((A)<<21)
#define Q16I_LFT_22(A)              ((A)<<22)
#define Q16I_LFT_23(A)              ((A)<<23)
#define Q16I_LFT_24(A)              ((A)<<24)

#define Q32I_RHT_01(A)              ((A)>>1)
#define Q32I_RHT_02(A)              ((A)>>2)
#define Q32I_RHT_03(A)              ((A)>>3)
#define Q32I_RHT_04(A)              ((A)>>4)
#define Q32I_RHT_05(A)              ((A)>>5)
#define Q32I_RHT_06(A)              ((A)>>6)
#define Q32I_RHT_07(A)              ((A)>>7)
#define Q32I_RHT_08(A)              ((A)>>8)

#define Q32I_RHT_09(A)              ((A)>>9)
#define Q32I_RHT_10(A)              ((A)>>10)
#define Q32I_RHT_11(A)              ((A)>>11)
#define Q32I_RHT_12(A)              ((A)>>12)
#define Q32I_RHT_13(A)              ((A)>>13)
#define Q32I_RHT_14(A)              ((A)>>14)
#define Q32I_RHT_15(A)              ((A)>>15)
#define Q32I_RHT_16(A)              ((A)>>16)
                                  
#define Q32I_RHT_17(A)              ((A)>>17)
#define Q32I_RHT_18(A)              ((A)>>18)
#define Q32I_RHT_19(A)              ((A)>>19)
#define Q32I_RHT_20(A)              ((A)>>20)
#define Q32I_RHT_21(A)              ((A)>>21)
#define Q32I_RHT_22(A)              ((A)>>22)
#define Q32I_RHT_23(A)              ((A)>>23)
#define Q32I_RHT_24(A)              ((A)>>24)

/********************************************************************/

typedef struct
{
    Q32I_ Q12U_Angle;
    Q32I_ Q14I_Cos;
    Q32I_ Q14I_Sin;
    Q32I_ Q16U_ReAngle;
}ST_TRIG;

#define MATH_FILTER_MAX                     ((Q16U_)(Q08U_MAX))
#define MATH_PID_MAX                        (Q14U_MAX)

#define MATH_PI_U                           (2048)
#define MATH_2PI_U                          (MATH_PI_U*2)
#define MATH_PI_OVER_SIX_U                  (MATH_PI_U/6)
#define MATH_PI_OVER_TWO_U                  (MATH_PI_U/2)
#define MATH_2PI_TMP_U                      ((Q32U_)(Q28U_MAX))

#define MATH_ANGLE_MOD_U(A)                 while(A>=MATH_2PI_U){A-=MATH_2PI_U;}while(A<0){A+=MATH_2PI_U;}
#define MATH_ANGLE_TMP_U(A)                 while(A>=MATH_2PI_TMP_U){A-=MATH_2PI_TMP_U;}while(A<0){A+=MATH_2PI_TMP_U;}
    
#define MATH_SQRT_THREE_U(A)                (Q32I_RHT_12(7095*(A)))
#define MATH_SQRT_THREE_OVER_TWO_U(A)       (Q32I_RHT_12(3547*(A)))
#define MATH_ONE_OVER_SQRT_THREE_U(A)       (Q32I_RHT_12(2365*(A)))
#define MATH_ONE_OVER_THREE_U(A)            (Q32I_RHT_12(1365*(A)))

#define MATH_ABS_U(A)                       (((A)<(0)) ? (-(A)) : (A))
#define MATH_MAX_U(A, B)                    (((A)>(B)) ?   (A)  : (B))
#define MATH_MIN_U(A, B)                    (((A)<(B)) ?   (A)  : (B))
#define MATH_SAT_U(A, MAX, MIN)             (MATH_MAX_U(MATH_MIN_U((A), (MAX)), (MIN)))

/*********************************************************************/

typedef struct
{
    float F_Angle;
    float F_Cos;
    float F_Sin;
    float F_ReAngle;
}ST_TRIG_F;

#define MATH_PI_F                           (3.1415926535897932384626433832795f)
#define MATH_2PI_F                          (2.0f*MATH_PI_F)
#define MATH_ONE_OVER_2PI_F                 (1.0f/MATH_2PI_F)
#define MATH_PI_OVER_SIX_F                  (MATH_PI_F/6.0f)
#define MATH_PI_OVER_TWO_F                  (MATH_PI_F/2.0f)
#define MATH_PI_OVER_FOUR_F                 (MATH_PI_F/4.0f)
    
#define MATH_ANGLE_MOD_F(A)                 while(A>MATH_2PI_F){A-=MATH_2PI_F;}while(A<0.0f){A+=MATH_2PI_F;}

#define MATH_ONE_OVER_THREE_F               (1.0f/3.0f)
#define MATH_SQRT_THREE_F                   (1.7320508075688772935274463415059f)
#define MATH_ONE_OVER_SQRT_THREE_F          (1.0f/MATH_SQRT_THREE_F)
#define MATH_SQRT_THREE_OVER_TWO_F          (MATH_SQRT_THREE_F/2.0f)

#define MATH_SQUARE_F(A)                    ((A)*(A))
#define MATH_ABS_F(A)                       (((A)<(0.0f)) ? (-(A)) : (A))
#define MATH_MAX_F(A, B)                    (((A)>(B)) ?   (A)  : (B))
#define MATH_MIN_F(A, B)                    (((A)<(B)) ?   (A)  : (B))
#define MATH_SAT_F(A, MAX, MIN)             (MATH_MAX_F(MATH_MIN_F((A), (MAX)), (MIN)))

/**********************************************************************/

#define MATH_DELAY_NS_COUNT                 (1U)
#define MATH_DELAY_US_COUNT                 (21U)
#define MATH_DELAY_MS_COUNT                 (21850U)

typedef struct
{
    Q32I_ Q32I_Init;
    Q32I_ Q32I_Target;
    Q32I_ Q32I_ADDStep;
    Q32I_ Q32I_SUBStep;
    Q32I_ Q32I_Output;
}ST_RAMP;

typedef struct
{
    Q32I_ Q16I_Filter_in;
    Q32I_ Q16I_Filter_out;
    Q32I_ Q32I_Filter_tmp;
    Q32I_ Q08I_Filter_Coeff;
}ST_FILTER;

typedef struct
{
    Q32I_ Q14I_Rf;
    Q32I_ Q14I_Fb;
    
    Q32I_ Q14I_Kp;
    Q32I_ Q14I_Ki;
    Q32I_ Q14I_Kd;
    
    Q32I_ Q28I_Step;
    Q32I_ Q14I_StepMax;
    Q32I_ Q14I_StepMin;
    
    Q32I_ Q14I_Output;
    Q32I_ Q28I_Output_tmp;
    Q32I_ Q14I_OutMax;
    Q32I_ Q14I_OutMin;
    
    Q32I_ Q14I_LastError;   
    Q32I_ Q14I_PrevError;
}ST_PID_INC;

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
}ST_PID_POS;

void Ramp_Init(ST_RAMP* pRamp, Q16I_ init);
void Ramp_Cal(ST_RAMP* pRamp);

void Filter_Init(ST_FILTER* pFltr, Q16I_ init);
void Filter_Cal(ST_FILTER* pFltr);
    
void PID_Inc_Init(ST_PID_INC* pPID, Q16I_ init);
void PID_Inc_Cal(ST_PID_INC* pPID);

void PID_Pos_Init(ST_PID_POS* pPID, Q16I_ init);
void PID_Pos_Cal(ST_PID_POS* pPID);

void Math_SinCos(ST_TRIG* TIG);
void Math_Atan(ST_TRIG* pTIG);

/**********************************/

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

Ram_Func void Ramp_Init_F(ST_RAMP_F* pRamp, float init);
Ram_Func void Ramp_Cal_F(ST_RAMP_F* pRamp);

Ram_Func void Filter_Init_F(ST_FILTER_F* pFltr, float init);
Ram_Func void Filter_Cal_F(ST_FILTER_F* pFltr);

Ram_Func void PID_Pos_Init_F(ST_PID_POS_F* pPID, float init);
Ram_Func void PID_Pos_Cal_F(ST_PID_POS_F* pPID);

Ram_Func float Math_Sin_F(float A);
Ram_Func float Math_Cos_F(float A);
Ram_Func float Math_Atan_F(float Sin, float Cos);
Ram_Func float Math_Sqrt_F(float A);

/**********************************/

void Delay_ns(Q32U_ time);
void Delay_us(Q32U_ time);
void Delay_ms(Q32U_ time);

#endif /* Math_H */
