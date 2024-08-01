/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef Math_H
#define Math_H

#include <stdint.h>

#define MATH_PI                         (3.14159265358979323846264338328f)
#define MATH_2PI                        (2.0f*MATH_PI)
#define MATH_ONE_OVER_2PI               (1.0f/MATH_2PI)
#define MATH_PI_OVER_SIX                (MATH_PI/6.0f)
#define MATH_PI_OVER_TWO                (MATH_PI/2.0f)
    
#define MATH_ONE_OVER_THREE             (1.0f/3.0f)
#define MATH_SQRT_THREE                 (1.73205080756887729352744634151f)
#define MATH_ONE_OVER_SQRT_THREE        (1.0f/MATH_SQRT_THREE)
#define MATH_SQRT_THREE_OVER_TWO        (MATH_SQRT_THREE/2.0f)

#define MATH_ABS(A)                     (((A)<0.0f) ? (0.0f-(A)) : (A))
#define MATH_MAX(A, B)                  (((A)>(B)) ? (A) : (B))
#define MATH_MIN(A, B)                  (((A)<(B)) ? (A) : (B))
#define MATH_SAT(A, Pos, Neg)           (MATH_MAX(((MATH_MIN((A), (Pos)))), (Neg)))

#define MATH_ANGLE_MOD(A)               (((A)>(MATH_2PI)) ? (A-MATH_2PI) : (((A)<(0.0f)) ? (A+MATH_2PI) : (A)))
#define SINE_TABLE_SIZE (512U)

extern float Math_Sin(float A);
extern float Math_Cos(float A);
extern float Math_Sqrt(float x);

#endif /* Math_H */
