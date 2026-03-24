/**************************************************************************************************
*     File Name :                        MATH.h
*     Library/Module Name :              MATH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             数学运算库头文件
**************************************************************************************************/

#ifndef MATH_H
#define MATH_H


/**********************************变量类型定义**********************************/

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


/**********************************定点数学库**********************************/

#define MATH_2PI_T                          (Q14U_MAX)
#define MATH_PI_T                           (MATH_2PI_T/2)
#define MATH_PI_OVER_TWO_T                  (MATH_2PI_T/4)
#define MATH_PI_OVER_FOUR_T                 (MATH_2PI_T/8)
#define MATH_PI_OVER_SIX_T                  (MATH_2PI_T/12)
#define MATH_2PI_TMP_T                      ((Q32I_)(Q28U_MAX))

#define MATH_ANGLE_MOD_T(A)                 if(A>=MATH_2PI_T){A-=MATH_2PI_T;}if(A<0){A+=MATH_2PI_T;}
#define MATH_ANGLE_TMP_T(A)                 if(A>=MATH_2PI_TMP_T){A-=MATH_2PI_TMP_T;}if(A<0){A+=MATH_2PI_TMP_T;}

#define MATH_SQRT_THREE_T(A)                (Q32I_RHT_14(28378*(A)))
#define MATH_SQRT_THREE_OVER_TWO_T(A)       (Q32I_RHT_14(14189*(A)))
#define MATH_ONE_OVER_SQRT_THREE_T(A)       (Q32I_RHT_14(9460*(A)))
#define MATH_ONE_OVER_THREE_T(A)            (Q32I_RHT_14(5461*(A)))

#define MATH_SQUARE_T(A)                    ((A)*(A))
#define MATH_SIGN_T(A)                      (((A)<(0)) ? (-1) : (1))
#define MATH_ABS_T(A)                       (((A)<(0)) ? (-(A)) : (A))
#define MATH_MAX_T(A, B)                    (((A)>(B)) ?   (A)  : (B))
#define MATH_MIN_T(A, B)                    (((A)<(B)) ?   (A)  : (B))
#define MATH_SAT_T(A, MAX, MIN)             (MATH_MAX_T(MATH_MIN_T((A), (MAX)), (MIN)))
#define MATH_SQADD_T(A, B)                  (Math_Sqrt_T((A)*(A) + (B)*(B)))
#define MATH_SQSUB_T(A, B)                  (Math_Sqrt_T((A)*(A) - (B)*(B)))


/**********************************浮点数学库***********************************/

#define MATH_2PI_F                          (6.2831853f)
#define MATH_PI_F                           (MATH_2PI_F/2.0f)
#define MATH_PI_OVER_TWO_F                  (MATH_2PI_F/4.0f)
#define MATH_PI_OVER_FOUR_F                 (MATH_2PI_F/8.0f)
#define MATH_PI_OVER_SIX_F                  (MATH_2PI_F/12.0f)

#define MATH_ANGLE_MOD_F(A)                 if(A>1.0f){A-=1.0f;}if(A<0.0f){A+=1.0f;}

#define MATH_SQRT_THREE_F                   (1.7320508f)
#define MATH_ONE_OVER_SQRT_THREE_F          (0.5773503f)
#define MATH_SQRT_THREE_OVER_TWO_F          (0.8660254f)
#define MATH_ONE_OVER_THREE_F               (0.3333333f)

#define MATH_SQUARE_F(A)                    ((A)*(A))
#define MATH_SIGN_F(A)                      (((A)<(0.0f)) ? (-1.0f) : (1.0f))
#define MATH_ABS_F(A)                       (((A)<(0.0f)) ? (-(A)) : (A))
#define MATH_MAX_F(A, B)                    (((A)>(B)   ) ?   (A)  : (B))
#define MATH_MIN_F(A, B)                    (((A)<(B)   ) ?   (A)  : (B))
#define MATH_SAT_F(A, MAX, MIN)             (MATH_MAX_F(MATH_MIN_F((A), (MAX)), (MIN)))
#define MATH_SQADD_F(A, B)                  (Math_Sqrt_F((A)*(A) + (B)*(B)))
#define MATH_SQSUB_F(A, B)                  (Math_Sqrt_F((A)*(A) - (B)*(B)))


/**********************************************************************************************
Function: Math_Sqrt_T
Description: 定点平方根计算
Input: 正浮点数
Output: 平方根
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Q32I_ Math_Sqrt_T(Q32I_ A);

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


#endif /* MATH_H */
