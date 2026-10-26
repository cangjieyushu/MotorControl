/**
 * @file    math_type.h
 * @brief   数学运算库基础类型与宏定义
 * @author  CJYS
 * @date    2024/1/1
 *
 * 提供定宽整数类型、位域基础类型，以及浮点/定点数学常量、
 * 移位宏和编译器属性宏。
 */

#ifndef MATH_TYPE_H
#define MATH_TYPE_H

/* ======================== 1. Includes ===================== */

/* ======================== 2. Defines ====================== */

/** @brief 无符号定宽类型最大值（浮点表示） */
#define Q02U_MAX_F                  (4.0f)
#define Q04U_MAX_F                  (16.0f)
#define Q08U_MAX_F                  (256.0f)
#define Q10U_MAX_F                  (1024.0f)
#define Q12U_MAX_F                  (4096.0f)
#define Q14U_MAX_F                  (16384.0f)
#define Q16U_MAX_F                  (65536.0f)
#define Q20U_MAX_F                  (1048576.0f)
#define Q22U_MAX_F                  (4194304.0f)
#define Q24U_MAX_F                  (16777216.0f)
#define Q28U_MAX_F                  (268435456.0f)
#define Q30U_MAX_F                  (1073741824.0f)

/** @brief 无符号定宽类型最大值（整数表示） */
#define Q02U_MAX_T                  (4)
#define Q04U_MAX_T                  (16)
#define Q08U_MAX_T                  (256)
#define Q10U_MAX_T                  (1024)
#define Q12U_MAX_T                  (4096)
#define Q14U_MAX_T                  (16384)
#define Q16U_MAX_T                  (65536)
#define Q20U_MAX_T                  (1048576)
#define Q22U_MAX_T                  (4194304)
#define Q24U_MAX_T                  (16777216)
#define Q28U_MAX_T                  (268435456)
#define Q30U_MAX_T                  (1073741824)

/** @brief Q16I_ 左移 1~30 位 */
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

/** @brief Q32I_ 右移 1~30 位 */
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

/** @brief 浮点数学常量与运算宏 */
#define MATH_2PI_F                          (6.2831853f)
#define MATH_PI_F                           (3.1415926f)
#define MATH_PI_OVER_TWO_F                  (1.5707963f)
#define MATH_PI_OVER_FOUR_F                 (0.7853982f)
#define MATH_PI_OVER_SIX_F                  (0.2617993f)

#define MATH_SQRT_THREE_F                   (1.7320508f)
#define MATH_ONE_OVER_SQRT_THREE_F          (0.5773503f)
#define MATH_SQRT_THREE_OVER_TWO_F          (0.8660254f)
#define MATH_ONE_OVER_THREE_F               (0.3333333f)

#define MATH_SQUARE_F(A)                    ((A)*(A))
#define MATH_SIGN_F(A)                      (((A)<(0.0f)) ? (-1.0f) : (1.0f))
#define MATH_ABS_F(A)                       (((A)<(0.0f)) ? (-(A)) : (A))
#define MATH_MAX_F(A, B)                    (((A)>(B)) ? (A) : (B))
#define MATH_MIN_F(A, B)                    (((A)<(B)) ? (A) : (B))
#define MATH_SAT_F(A, MAX, MIN)             (MATH_MAX_F(MATH_MIN_F((A), (MAX)), (MIN)))
#define MATH_SQRTADD_F(A, B)                (Math_Sqrt_F((A)*(A) + (B)*(B)))
#define MATH_SQRTSUB_F(A, B)                (Math_Sqrt_F((A)*(A) - (B)*(B)))

#define MATH_ANGLE_MOD_F(A)                 if(A>1.0f){A-=1.0f;}if(A<0.0f){A+=1.0f;}

/** @brief 定点数学常量与运算宏 */
#define MATH_2PI_T                          (Q14U_MAX_T)
#define MATH_PI_T                           (8192)
#define MATH_PI_OVER_TWO_T                  (4092)
#define MATH_PI_OVER_FOUR_T                 (2048)
#define MATH_PI_OVER_SIX_T                  (1365)
#define MATH_2PI_TMP_T                      (Q28U_MAX_T)

#define MATH_SQRT_THREE_T(A)                (Q32I_RHT_14(28378*(A)))
#define MATH_SQRT_THREE_OVER_TWO_T(A)       (Q32I_RHT_14(14189*(A)))
#define MATH_ONE_OVER_SQRT_THREE_T(A)       (Q32I_RHT_14(9460*(A)))
#define MATH_ONE_OVER_THREE_T(A)            (Q32I_RHT_14(5461*(A)))

#define MATH_SQUARE_T(A)                    ((A)*(A))
#define MATH_SIGN_T(A)                      (((A)<(0)) ? (-1) : (1))
#define MATH_ABS_T(A)                       (((A)<(0)) ? (-(A)) : (A))
#define MATH_MAX_T(A, B)                    (((A)>(B)) ? (A) : (B))
#define MATH_MIN_T(A, B)                    (((A)<(B)) ? (A) : (B))
#define MATH_SAT_T(A, MAX, MIN)             (MATH_MAX_T(MATH_MIN_T((A), (MAX)), (MIN)))
#define MATH_SQRTADD_T(A, B)                (Math_Sqrt_T((A)*(A) + (B)*(B)))
#define MATH_SQRTSUB_T(A, B)                (Math_Sqrt_T((A)*(A) - (B)*(B)))

#define MATH_ANGLE_MOD_T(A)                 if(A>=MATH_2PI_T){A-=MATH_2PI_T;}if(A<0){A+=MATH_2PI_T;}
#define MATH_ANGLE_TMP_T(A)                 if(A>=MATH_2PI_TMP_T){A-=MATH_2PI_TMP_T;}if(A<0){A+=MATH_2PI_TMP_T;}

/** @brief 编译器属性宏：将函数放入 CCMRAM（若启用） */
#ifdef MC_FUNCTION_SET_RAM
#define __attribute__CCMRAM                 __attribute__((section("ccmram")))
#else
#define __attribute__CCMRAM
#endif

/* ======================== 3. Typedefs ===================== */

/** @brief 无符号 8 位整数 */
typedef unsigned char       Q08U_;

/** @brief 无符号 16 位整数 */
typedef unsigned short int  Q16U_;

/** @brief 无符号 32 位整数 */
typedef unsigned int        Q32U_;

/** @brief 有符号 16 位整数 */
typedef signed short int    Q16I_;

/** @brief 有符号 32 位整数 */
typedef signed int          Q32I_;

/** @brief 位域整体访问类型 */
typedef unsigned int        SC_ALL;

/** @brief 位域位宽类型 */
typedef unsigned int        SC_BIT;

/* ======================== 4. Globals ====================== */

/* ======================== 5. Function Prototypes ========== */

/**
 * @brief  浮点数平方根（快速倒数开方迭代）
 * @param  A  输入值，需 > 0
 * @return A 的平方根
 */
__attribute__CCMRAM
float Math_Sqrt_F(float A);

/**
 * @brief  定点整数平方根（牛顿迭代）
 * @param  A  输入值，需 > 0
 * @return A 的平方根（向下取整）
 */
__attribute__CCMRAM
Q32I_ Math_Sqrt_T(Q32I_ A);

/**
 * @brief  软件微秒级延时
 * @param  time  延时时间（微秒）
 */
__attribute__CCMRAM
void Math_Delay_us(Q32U_ time);

/**
 * @brief  软件毫秒级延时
 * @param  time  延时时间（毫秒）
 */
__attribute__CCMRAM
void Math_Delay_ms(Q32U_ time);

#endif /* MATH_TYPE_H */
