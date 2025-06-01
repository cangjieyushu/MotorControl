/**************************************************************************************************
*     File Name :                        Math.c
*     Library/Module Name :              MATH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             数学运算库源文件
                                         注意：定点数学库中应用到了有符号数移位，暂不做处理。
**************************************************************************************************/
#include "Math.h"

/************************************定点数学库**************************************/

/**********************************************************************************************
Function: Ramp_Init_T
Description: 定点斜坡初始化
Input: 定点斜坡输出初始值
Output: 无
Input_Output: 定点斜坡指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Ramp_Init_T(ST_RAMP_T* pRamp, Q32I_ init)
{
    pRamp->Q24I_Output_tmp = Q16I_LFT_10(init);
    pRamp->Q14I_Output = init;
}

/**********************************************************************************************
Function: Ramp_Cal_T
Description: 定点斜坡计算
Input: 无
Output: 无
Input_Output: 定点斜坡指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Ramp_Cal_T(ST_RAMP_T* pRamp)
{
    Q32I_ Q24I_Target_tmp = Q16I_LFT_10(pRamp->Q14I_Target);
    if(Q24I_Target_tmp > pRamp->Q24I_Output_tmp) 
    {
        if(Q24I_Target_tmp > pRamp->Q24I_Output_tmp + pRamp->Q24I_ADDStep) 
        {
            pRamp->Q24I_Output_tmp += pRamp->Q24I_ADDStep;
        }
        else 
        {
            pRamp->Q24I_Output_tmp = Q24I_Target_tmp;
        }
    }
    else if(Q24I_Target_tmp < pRamp->Q24I_Output_tmp) 
    { 
        if(Q24I_Target_tmp < pRamp->Q24I_Output_tmp + pRamp->Q24I_SUBStep) 
        {
            pRamp->Q24I_Output_tmp += pRamp->Q24I_SUBStep;
        }
        else 
        {
            pRamp->Q24I_Output_tmp = Q24I_Target_tmp;
        }
    }
    else 
    {
        pRamp->Q24I_Output_tmp = Q24I_Target_tmp;
    }
    
    pRamp->Q14I_Output = Q32I_RHT_10(pRamp->Q24I_Output_tmp);
}

/**********************************************************************************************
Function: Filter_Init_T
Description: 定点低通滤波初始化
Input: 定点低通滤波初始值
Output: 无
Input_Output: 定点低通滤波指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Filter_Init_T(ST_FILTER_T* pFltr, Q32I_ init)
{
    pFltr->Q24I_Filter_tmp = Q16I_LFT_08(init);
    pFltr->Q16I_Filter_out = init;
}

/**********************************************************************************************
Function: Filter_Cal_T
Description: 定点低通滤波计算
Input: 无
Output: 无
Input_Output: 定点低通滤波指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Filter_Cal_T(ST_FILTER_T* pFltr)
{
    pFltr->Q24I_Filter_tmp = Q32I_RHT_08(Q16I_LFT_08(pFltr->Q08I_Filter_Coeff*pFltr->Q16I_Filter_in)
    + (MATH_FILTER_MAX_T - pFltr->Q08I_Filter_Coeff)*pFltr->Q24I_Filter_tmp);
    pFltr->Q16I_Filter_out = Q32I_RHT_08(pFltr->Q24I_Filter_tmp);
}

/**********************************************************************************************
Function: PID_Inc_Init_T
Description: 定点增量式PID初始化
Input: 定点积分器初始值
Output: 无
Input_Output: 定点增量式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Inc_Init_T(ST_PID_INC_T* pPID, Q32I_ init)
{
    pPID->Q14I_Rf = 0;
    pPID->Q14I_Fb = 0;
    pPID->Q28I_Step = 0;
    pPID->Q14I_LastError = 0;   
    pPID->Q14I_PrevError = 0;
    pPID->Q14I_Output = init;
    pPID->Q28I_Output_tmp = Q16I_LFT_14(init);
}

/**********************************************************************************************
Function: PID_Inc_Cal_T
Description: 定点增量式PID计算
Input: 无
Output: 无
Input_Output: 定点增量式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Inc_Cal_T(ST_PID_INC_T* pPID)
{
    Q32I_ Q14I_Error = pPID->Q14I_Rf - pPID->Q14I_Fb;
    
    pPID->Q28I_Step = pPID->Q14I_Kp*(Q14I_Error - pPID->Q14I_LastError) + pPID->Q14I_Ki*Q14I_Error
    + pPID->Q14I_Kd*(Q14I_Error + pPID->Q14I_PrevError - 2*pPID->Q14I_LastError);
    pPID->Q28I_Step = MATH_SAT_T(pPID->Q28I_Step, pPID->Q28I_StepMax, pPID->Q28I_StepMin);
    
    pPID->Q28I_Output_tmp += pPID->Q28I_Step;
    pPID->Q28I_Output_tmp = MATH_SAT_T(pPID->Q28I_Output_tmp, Q16I_LFT_14(pPID->Q14I_OutMax), Q16I_LFT_14(pPID->Q14I_OutMin));
    
    pPID->Q14I_Output = Q32I_RHT_14(pPID->Q28I_Output_tmp);
    pPID->Q14I_PrevError = pPID->Q14I_LastError;
    pPID->Q14I_LastError = Q14I_Error;
}

/**********************************************************************************************
Function: PID_Pos_Init_T
Description: 定点位置式PID初始化
Input: 定点积分器初始值
Output: 无
Input_Output: 定点位置式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Pos_Init_T(ST_PID_POS_T* pPID, Q32I_ init)
{
    pPID->Q14I_Rf = 0;
    pPID->Q14I_Fb = 0;
    pPID->Q14I_Ui = init;
    pPID->Q28I_Ui_tmp = Q16I_LFT_14(init);
    pPID->Q14I_Output = init;
}

/**********************************************************************************************
Function: PID_Pos_Cal_T
Description: 定点位置式PID计算
Input: 无
Output: 无
Input_Output: 定点位置式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Pos_Cal_T(ST_PID_POS_T* pPID)
{
    Q32I_ Q14I_Error = pPID->Q14I_Rf - pPID->Q14I_Fb;
    
    pPID->Q28I_Ui_tmp += pPID->Q14I_Ki*Q14I_Error;
    pPID->Q28I_Ui_tmp = MATH_SAT_T(pPID->Q28I_Ui_tmp, Q16I_LFT_14(pPID->Q14I_OutMax), Q16I_LFT_14(pPID->Q14I_OutMin));
    pPID->Q14I_Ui = Q32I_RHT_14(pPID->Q28I_Ui_tmp);
    
    pPID->Q14I_Output = Q32I_RHT_14(pPID->Q14I_Kp*Q14I_Error) + pPID->Q14I_Ui;
    pPID->Q14I_Output = MATH_SAT_T(pPID->Q14I_Output, pPID->Q14I_OutMax, pPID->Q14I_OutMin);
}

static const Q16I_ Math_Sin_Table_I16[1024] = {
0x0000,0x0019,0x0032,0x004B,0x0064,0x007D,0x0096,0x00AF,0x00C9,0x00E2,
0x00FB,0x0114,0x012D,0x0146,0x015F,0x0178,0x0192,0x01AB,0x01C4,0x01DD,
0x01F6,0x020F,0x0228,0x0241,0x025B,0x0274,0x028D,0x02A6,0x02BF,0x02D8,
0x02F1,0x030A,0x0323,0x033D,0x0356,0x036F,0x0388,0x03A1,0x03BA,0x03D3,
0x03EC,0x0405,0x041E,0x0437,0x0451,0x046A,0x0483,0x049C,0x04B5,0x04CE,
0x04E7,0x0500,0x0519,0x0532,0x054B,0x0564,0x057D,0x0596,0x05AF,0x05C8,
0x05E1,0x05FA,0x0613,0x062C,0x0645,0x065E,0x0677,0x0690,0x06A9,0x06C2,
0x06DB,0x06F4,0x070D,0x0726,0x073F,0x0758,0x0771,0x078A,0x07A3,0x07BC,
0x07D5,0x07EE,0x0807,0x0820,0x0839,0x0852,0x086B,0x0884,0x089C,0x08B5,
0x08CE,0x08E7,0x0900,0x0919,0x0932,0x094B,0x0964,0x097C,0x0995,0x09AE,
0x09C7,0x09E0,0x09F9,0x0A11,0x0A2A,0x0A43,0x0A5C,0x0A75,0x0A8D,0x0AA6,
0x0ABF,0x0AD8,0x0AF1,0x0B09,0x0B22,0x0B3B,0x0B54,0x0B6C,0x0B85,0x0B9E,
0x0BB6,0x0BCF,0x0BE8,0x0C01,0x0C19,0x0C32,0x0C4B,0x0C63,0x0C7C,0x0C95,
0x0CAD,0x0CC6,0x0CDE,0x0CF7,0x0D10,0x0D28,0x0D41,0x0D59,0x0D72,0x0D8B,
0x0DA3,0x0DBC,0x0DD4,0x0DED,0x0E05,0x0E1E,0x0E36,0x0E4F,0x0E67,0x0E80,
0x0E98,0x0EB1,0x0EC9,0x0EE2,0x0EFA,0x0F12,0x0F2B,0x0F43,0x0F5C,0x0F74,
0x0F8C,0x0FA5,0x0FBD,0x0FD6,0x0FEE,0x1006,0x101F,0x1037,0x104F,0x1068,	
0x1080,0x1098,0x10B0,0x10C9,0x10E1,0x10F9,0x1111,0x112A,0x1142,0x115A,
0x1172,0x118A,0x11A2,0x11BB,0x11D3,0x11EB,0x1203,0x121B,0x1233,0x124B,
0x1263,0x127B,0x1294,0x12AC,0x12C4,0x12DC,0x12F4,0x130C,0x1324,0x133C,
0x1354,0x136C,0x1383,0x139B,0x13B3,0x13CB,0x13E3,0x13FB,0x1413,0x142B,
0x1443,0x145A,0x1472,0x148A,0x14A2,0x14BA,0x14D1,0x14E9,0x1501,0x1519,
0x1530,0x1548,0x1560,0x1577,0x158F,0x15A7,0x15BE,0x15D6,0x15EE,0x1605,
0x161D,0x1634,0x164C,0x1664,0x167B,0x1693,0x16AA,0x16C2,0x16D9,0x16F1,
0x1708,0x171F,0x1737,0x174E,0x1766,0x177D,0x1794,0x17AC,0x17C3,0x17DA,
0x17F2,0x1809,0x1820,0x1838,0x184F,0x1866,0x187D,0x1895,0x18AC,0x18C3,
0x18DA,0x18F1,0x1908,0x1920,0x1937,0x194E,0x1965,0x197C,0x1993,0x19AA,
0x19C1,0x19D8,0x19EF,0x1A06,0x1A1D,0x1A34,0x1A4B,0x1A62,0x1A79,0x1A8F,
0x1AA6,0x1ABD,0x1AD4,0x1AEB,0x1B02,0x1B18,0x1B2F,0x1B46,0x1B5D,0x1B73,
0x1B8A,0x1BA1,0x1BB7,0x1BCE,0x1BE5,0x1BFB,0x1C12,0x1C28,0x1C3F,0x1C55,
0x1C6C,0x1C83,0x1C99,0x1CAF,0x1CC6,0x1CDC,0x1CF3,0x1D09,0x1D20,0x1D36,
0x1D4C,0x1D63,0x1D79,0x1D8F,0x1DA6,0x1DBC,0x1DD2,0x1DE8,0x1DFE,0x1E15,
0x1E2B,0x1E41,0x1E57,0x1E6D,0x1E83,0x1E99,0x1EB0,0x1EC6,0x1EDC,0x1EF2,
0x1F08,0x1F1E,0x1F34,0x1F49,0x1F5F,0x1F75,0x1F8B,0x1FA1,0x1FB7,0x1FCD,
0x1FE2,0x1FF8,0x200E,0x2024,0x2039,0x204F,0x2065,0x207B,0x2090,0x20A6,
0x20BB,0x20D1,0x20E7,0x20FC,0x2112,0x2127,0x213D,0x2152,0x2168,0x217D,
0x2192,0x21A8,0x21BD,0x21D2,0x21E8,0x21FD,0x2212,0x2228,0x223D,0x2252,
0x2267,0x227D,0x2292,0x22A7,0x22BC,0x22D1,0x22E6,0x22FB,0x2310,0x2325,
0x233A,0x234F,0x2364,0x2379,0x238E,0x23A3,0x23B8,0x23CD,0x23E1,0x23F6,
0x240B,0x2420,0x2434,0x2449,0x245E,0x2473,0x2487,0x249C,0x24B0,0x24C5,
0x24DA,0x24EE,0x2503,0x2517,0x252C,0x2540,0x2554,0x2569,0x257D,0x2592,
0x25A6,0x25BA,0x25CF,0x25E3,0x25F7,0x260B,0x261F,0x2634,0x2648,0x265C,
0x2670,0x2684,0x2698,0x26AC,0x26C0,0x26D4,0x26E8,0x26FC,0x2710,0x2724,
0x2738,0x274C,0x275F,0x2773,0x2787,0x279B,0x27AF,0x27C2,0x27D6,0x27EA,
0x27FD,0x2811,0x2824,0x2838,0x284B,0x285F,0x2872,0x2886,0x2899,0x28AD,
0x28C0,0x28D4,0x28E7,0x28FA,0x290E,0x2921,0x2934,0x2947,0x295A,0x296E,
0x2981,0x2994,0x29A7,0x29BA,0x29CD,0x29E0,0x29F3,0x2A06,0x2A19,0x2A2C,
0x2A3F,0x2A52,0x2A65,0x2A77,0x2A8A,0x2A9D,0x2AB0,0x2AC2,0x2AD5,0x2AE8,
0x2AFA,0x2B0D,0x2B20,0x2B32,0x2B45,0x2B57,0x2B6A,0x2B7C,0x2B8E,0x2BA1,
0x2BB3,0x2BC6,0x2BD8,0x2BEA,0x2BFC,0x2C0F,0x2C21,0x2C33,0x2C45,0x2C57,
0x2C6A,0x2C7C,0x2C8E,0x2CA0,0x2CB2,0x2CC4,0x2CD6,0x2CE8,0x2CF9,0x2D0B,
0x2D1D,0x2D2F,0x2D41,0x2D52,0x2D64,0x2D76,0x2D88,0x2D99,0x2DAB,0x2DBC,
0x2DCE,0x2DE0,0x2DF1,0x2E03,0x2E14,0x2E25,0x2E37,0x2E48,0x2E5A,0x2E6B,
0x2E7C,0x2E8D,0x2E9F,0x2EB0,0x2EC1,0x2ED2,0x2EE3,0x2EF4,0x2F05,0x2F16,
0x2F28,0x2F38,0x2F49,0x2F5A,0x2F6B,0x2F7C,0x2F8D,0x2F9E,0x2FAF,0x2FBF,
0x2FD0,0x2FE1,0x2FF1,0x3002,0x3013,0x3023,0x3034,0x3044,0x3055,0x3065,
0x3076,0x3086,0x3096,0x30A7,0x30B7,0x30C7,0x30D8,0x30E8,0x30F8,0x3108,
0x3118,0x3128,0x3138,0x3149,0x3159,0x3169,0x3179,0x3188,0x3198,0x31A8,
0x31B8,0x31C8,0x31D8,0x31E7,0x31F7,0x3207,0x3216,0x3226,0x3236,0x3245,
0x3255,0x3264,0x3274,0x3283,0x3293,0x32A2,0x32B1,0x32C1,0x32D0,0x32DF,
0x32EE,0x32FE,0x330D,0x331C,0x332B,0x333A,0x3349,0x3358,0x3367,0x3376,
0x3385,0x3394,0x33A3,0x33B2,0x33C1,0x33CF,0x33DE,0x33ED,0x33FB,0x340A,
0x3419,0x3427,0x3436,0x3444,0x3453,0x3461,0x3470,0x347E,0x348C,0x349B,
0x34A9,0x34B7,0x34C6,0x34D4,0x34E2,0x34F0,0x34FE,0x350C,0x351A,0x3528,
0x3536,0x3544,0x3552,0x3560,0x356E,0x357C,0x3589,0x3597,0x35A5,0x35B3,
0x35C0,0x35CE,0x35DC,0x35E9,0x35F7,0x3604,0x3612,0x361F,0x362C,0x363A,
0x3647,0x3654,0x3662,0x366F,0x367C,0x3689,0x3696,0x36A4,0x36B1,0x36BE,
0x36CB,0x36D8,0x36E5,0x36F1,0x36FE,0x370B,0x3718,0x3725,0x3731,0x373E,
0x374B,0x3757,0x3764,0x3771,0x377D,0x378A,0x3796,0x37A3,0x37AF,0x37BB,
0x37C8,0x37D4,0x37E0,0x37ED,0x37F9,0x3805,0x3811,0x381D,0x3829,0x3835,
0x3841,0x384D,0x3859,0x3865,0x3871,0x387D,0x3889,0x3894,0x38A0,0x38AC,
0x38B7,0x38C3,0x38CF,0x38DA,0x38E6,0x38F1,0x38FD,0x3908,0x3913,0x391F,
0x392A,0x3935,0x3941,0x394C,0x3957,0x3962,0x396D,0x3978,0x3983,0x398E,
0x3999,0x39A4,0x39AF,0x39BA,0x39C5,0x39D0,0x39DA,0x39E5,0x39F0,0x39FB,
0x3A05,0x3A10,0x3A1A,0x3A25,0x3A2F,0x3A3A,0x3A44,0x3A4F,0x3A59,0x3A63,
0x3A6D,0x3A78,0x3A82,0x3A8C,0x3A96,0x3AA0,0x3AAA,0x3AB4,0x3ABE,0x3AC8,
0x3AD2,0x3ADC,0x3AE6,0x3AF0,0x3AFA,0x3B03,0x3B0D,0x3B17,0x3B20,0x3B2A,
0x3B34,0x3B3D,0x3B47,0x3B50,0x3B59,0x3B63,0x3B6C,0x3B75,0x3B7F,0x3B88,
0x3B91,0x3B9A,0x3BA3,0x3BAD,0x3BB6,0x3BBF,0x3BC8,0x3BD1,0x3BDA,0x3BE2,
0x3BEB,0x3BF4,0x3BFD,0x3C06,0x3C0E,0x3C17,0x3C20,0x3C28,0x3C31,0x3C39,
0x3C42,0x3C4A,0x3C53,0x3C5B,0x3C63,0x3C6C,0x3C74,0x3C7C,0x3C84,0x3C8C,
0x3C95,0x3C9D,0x3CA5,0x3CAD,0x3CB5,0x3CBD,0x3CC5,0x3CCC,0x3CD4,0x3CDC,
0x3CE4,0x3CEC,0x3CF3,0x3CFB,0x3D02,0x3D0A,0x3D12,0x3D19,0x3D21,0x3D28,
0x3D2F,0x3D37,0x3D3E,0x3D45,0x3D4D,0x3D54,0x3D5B,0x3D62,0x3D69,0x3D70,
0x3D77,0x3D7E,0x3D85,0x3D8C,0x3D93,0x3D9A,0x3DA1,0x3DA7,0x3DAE,0x3DB5,
0x3DBB,0x3DC2,0x3DC9,0x3DCF,0x3DD6,0x3DDC,0x3DE2,0x3DE9,0x3DEF,0x3DF5,
0x3DFC,0x3E02,0x3E08,0x3E0E,0x3E14,0x3E1B,0x3E21,0x3E27,0x3E2D,0x3E33,
0x3E38,0x3E3E,0x3E44,0x3E4A,0x3E50,0x3E55,0x3E5B,0x3E61,0x3E66,0x3E6C,
0x3E71,0x3E77,0x3E7C,0x3E82,0x3E87,0x3E8C,0x3E92,0x3E97,0x3E9C,0x3EA1,
0x3EA7,0x3EAC,0x3EB1,0x3EB6,0x3EBB,0x3EC0,0x3EC5,0x3ECA,0x3ECE,0x3ED3,
0x3ED8,0x3EDD,0x3EE1,0x3EE6,0x3EEB,0x3EEF,0x3EF4,0x3EF8,0x3EFD,0x3F01,
0x3F06,0x3F0A,0x3F0E,0x3F13,0x3F17,0x3F1B,0x3F1F,0x3F23,0x3F27,0x3F2B,
0x3F2F,0x3F33,0x3F37,0x3F3B,0x3F3F,0x3F43,0x3F47,0x3F4A,0x3F4E,0x3F52,
0x3F55,0x3F59,0x3F5D,0x3F60,0x3F64,0x3F67,0x3F6A,0x3F6E,0x3F71,0x3F74,
0x3F78,0x3F7B,0x3F7E,0x3F81,0x3F84,0x3F87,0x3F8A,0x3F8D,0x3F90,0x3F93,
0x3F96,0x3F99,0x3F9C,0x3F9E,0x3FA1,0x3FA4,0x3FA6,0x3FA9,0x3FAC,0x3FAE,
0x3FB1,0x3FB3,0x3FB5,0x3FB8,0x3FBA,0x3FBC,0x3FBF,0x3FC1,0x3FC3,0x3FC5,
0x3FC7,0x3FC9,0x3FCB,0x3FCD,0x3FCF,0x3FD1,0x3FD3,0x3FD5,0x3FD7,0x3FD8,
0x3FDA,0x3FDC,0x3FDE,0x3FDF,0x3FE1,0x3FE2,0x3FE4,0x3FE5,0x3FE7,0x3FE8,
0x3FE9,0x3FEB,0x3FEC,0x3FED,0x3FEE,0x3FEF,0x3FF0,0x3FF1,0x3FF2,0x3FF3,
0x3FF4,0x3FF5,0x3FF6,0x3FF7,0x3FF8,0x3FF9,0x3FF9,0x3FFA,0x3FFB,0x3FFB,
0x3FFC,0x3FFC,0x3FFD,0x3FFD,0x3FFE,0x3FFE,0x3FFE,0x3FFF,0x3FFF,0x3FFF,
0x3FFF,0x3FFF,0x3FFF,0x3FFF,};
 
#define SIN_MASK        0x0C00U
#define U0_90           0x0000U
#define U90_180         0x0400U
#define U180_270        0x0800U
#define U270_360        0x0C00U
 
/**********************************************************************************************
Function: Math_SinCos_T
Description: 定点正余弦计算
Input: 角度，0到4096
Output: 正弦，余弦
Input_Output: 定点角度指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Math_SinCos_T(ST_TRIG_T* pTIG)
{
    Q16U_ Q16U_index_tmp;
    Q16U_index_tmp = 0x3FFU & (Q16U_)pTIG->Q12U_Angle;
 
    switch((Q16U_)pTIG->Q12U_Angle & SIN_MASK)
    {
        case U0_90:
            pTIG->Q14I_Sin =  Math_Sin_Table_I16[Q16U_index_tmp];
            pTIG->Q14I_Cos =  Math_Sin_Table_I16[(0x3FFU - Q16U_index_tmp)];
            break;
        case U90_180:
            pTIG->Q14I_Sin =  Math_Sin_Table_I16[(0x3FFU - Q16U_index_tmp)];
            pTIG->Q14I_Cos = -Math_Sin_Table_I16[Q16U_index_tmp];
            break;
        case U180_270:
            pTIG->Q14I_Sin = -Math_Sin_Table_I16[Q16U_index_tmp];
            pTIG->Q14I_Cos = -Math_Sin_Table_I16[(0x3FFU - Q16U_index_tmp)];
            break;
        case U270_360:
            pTIG->Q14I_Sin = -Math_Sin_Table_I16[(0x3FFU - Q16U_index_tmp)];
            pTIG->Q14I_Cos =  Math_Sin_Table_I16[Q16U_index_tmp];
            break;
        default:
            break;
    }
}

/**********************************************************************************************
Function: Math_Atan_T
Description: 定点反正切计算
Input: 正弦，余弦
Output: 角度，0到4096
Input_Output: 定点角度指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Math_Atan_T(ST_TRIG_T* pTIG)
{
    Q08U_ Sector_N;
	Q08U_ Sector_a = 0U;
	Q08U_ Sector_b = 0U;
	Q08U_ Sector_c = 0U;
    
	Q32I_ Cos_tmp,Sin_tmp,Tan_tmp;
    
	Q32I_ temp;
	Q32I_ temp1,temp2;
	Q32I_ deg_temp = 0;

	Cos_tmp = pTIG->Q14I_Cos;
	Sin_tmp = pTIG->Q14I_Sin;

    if(Cos_tmp == 0 && Sin_tmp == 0)
    {
		pTIG->Q12U_ReAngle = 0;
    }
    else
    {
        if (Cos_tmp < 0)
        {
            Cos_tmp = -Cos_tmp;
            Sector_b = 2U;
        }
        if (Sin_tmp < 0)
        {
            Sin_tmp = -Sin_tmp;
            Sector_c = 4U;
        }
        if (Sin_tmp > Cos_tmp)
        {
            temp = Cos_tmp;
            Cos_tmp = Sin_tmp;
            Sin_tmp = temp;
            Sector_a = 1U;
        }
        Sector_N = Sector_a + Sector_b + Sector_c;

        Tan_tmp = ((Sin_tmp<<14U)/Cos_tmp);
	
        temp1 = ((Tan_tmp*2789)>>14U) + 10195; 
        temp2 = ((16384 - Tan_tmp)*temp1)>>14U; 
        deg_temp = (Tan_tmp*(32768 + temp2))>>20U;
	
        switch (Sector_N)
        {
            case 0U:
                pTIG->Q12U_ReAngle = deg_temp;
			break;
            case 1U:
                pTIG->Q12U_ReAngle = 1023 - (deg_temp);		
			break;
            case 2U:
                pTIG->Q12U_ReAngle = 2047 - (deg_temp);		
			break;
            case 3U:
                pTIG->Q12U_ReAngle = 1024 + (deg_temp);		
            break;
            case 4U:
                pTIG->Q12U_ReAngle = 4095 - (deg_temp);		
            break;
            case 5U:
                pTIG->Q12U_ReAngle = 3072 + (deg_temp);		
            break;
            case 6U:
                pTIG->Q12U_ReAngle = 2048 + (deg_temp);		
            break;
            case 7U:
                pTIG->Q12U_ReAngle = 3071 - (deg_temp);	
            break;
            default:
                pTIG->Q12U_ReAngle = 0;
            break;
        }
    }
}

/************************************浮点数学库**************************************/

/**********************************************************************************************
Function: Ramp_Init_F
Description: 浮点斜坡初始化
Input: 浮点斜坡输出初始值
Output: 无
Input_Output: 浮点斜坡指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Ramp_Init_F(ST_RAMP_F* pRamp, float init)
{
    pRamp->F_Output = init;
}

/**********************************************************************************************
Function: Ramp_Cal_F
Description: 浮点斜坡计算
Input: 无
Output: 无
Input_Output: 浮点斜坡指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Ramp_Cal_F(ST_RAMP_F* pRamp)
{    
    if(pRamp->F_Target > pRamp->F_Output) 
    { 
        if(pRamp->F_Target > pRamp->F_Output + pRamp->F_ADDStep) 
        {
            pRamp->F_Output += pRamp->F_ADDStep;
        }
        else 
        {
            pRamp->F_Output = pRamp->F_Target;
        }
    }
    else if(pRamp->F_Target < pRamp->F_Output) 
    { 
        if(pRamp->F_Target < pRamp->F_Output + pRamp->F_SUBStep) 
        {
            pRamp->F_Output += pRamp->F_SUBStep;
        }
        else 
        {
            pRamp->F_Output = pRamp->F_Target;
        }
    }
    else 
    {
        pRamp->F_Output = pRamp->F_Target;
    }
}

/**********************************************************************************************
Function: Filter_Init_F
Description: 浮点低通滤波初始化
Input: 浮点低通滤波初始值
Output: 无
Input_Output: 浮点低通滤波指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Filter_Init_F(ST_FILTER_F* pFltr, float init)
{
    pFltr->F_Filter_out = init;
}

/**********************************************************************************************
Function: Filter_Cal_F
Description: 浮点低通滤波计算
Input: 无
Output: 无
Input_Output: 浮点低通滤波指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Filter_Cal_F(ST_FILTER_F* pFltr)
{
    pFltr->F_Filter_out = pFltr->F_Filter_Coeff*pFltr->F_Filter_in + (1.0f - pFltr->F_Filter_Coeff)*pFltr->F_Filter_out;
}

/**********************************************************************************************
Function: PID_Pos_Init_F
Description: 浮点位置式PID初始化
Input: 浮点积分器初始值
Output: 无
Input_Output: 浮点位置式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Pos_Init_F(ST_PID_POS_F* pPID, float init)
{
    pPID->F_Rf = 0.0f;
    pPID->F_Fb = 0.0f;
    pPID->F_Ui = init;
    pPID->F_Output = init;
}

/**********************************************************************************************
Function: PID_Pos_Cal_F
Description: 浮点位置式PID计算
Input: 无
Output: 无
Input_Output: 浮点位置式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Pos_Cal_F(ST_PID_POS_F* pPID)
{
    float F_Error = pPID->F_Rf - pPID->F_Fb;
    
    pPID->F_Ui += pPID->F_Ki*F_Error;
    pPID->F_Ui = MATH_SAT_F(pPID->F_Ui, pPID->F_OutMax, pPID->F_OutMin);
    
    pPID->F_Output = pPID->F_Kp*F_Error + pPID->F_Ui;
    pPID->F_Output = MATH_SAT_F(pPID->F_Output, pPID->F_OutMax, pPID->F_OutMin);
}

/**********************************************************************************************
Function: PID_Sat_Init_F
Description: 抗饱和位置式PID初始化
Input: 抗饱和积分器初始值
Output: 无
Input_Output: 抗饱和位置式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Sat_Init_F(ST_PID_SAT_F* pPID, float init)
{
    pPID->F_Rf = 0.0f;
    pPID->F_Fb = 0.0f;
    pPID->F_Ui = init;
    pPID->F_Output = init;
}

/**********************************************************************************************
Function: PID_Sat_Cal_F
Description: 抗饱和位置式PID计算
Input: 无
Output: 无
Input_Output: 抗饱和位置式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Sat_Cal_F(ST_PID_SAT_F* pPID)
{
    float F_Error = pPID->F_Rf - pPID->F_Fb;
    
    pPID->F_Ui += pPID->F_Ki*F_Error - pPID->F_Kc*pPID->F_USat;
    
    pPID->F_Output = pPID->F_Kp*F_Error + pPID->F_Ui;
    pPID->F_Output = MATH_SAT_F(pPID->F_Output, pPID->F_OutMax, pPID->F_OutMin);
    pPID->F_USat = pPID->F_Ui - pPID->F_Output;
}

#define SINE_TABLE_SIZE                 (512U)
static float Math_Sin_Table_Float[SINE_TABLE_SIZE + 2U] =
{
	0.00000000f, 0.01227154f, 0.02454123f, 0.03680722f, 0.04906767f, 0.06132074f,
    0.07356456f, 0.08579731f, 0.09801714f, 0.11022221f, 0.12241068f, 0.13458071f,
	0.14673047f, 0.15885814f, 0.17096189f, 0.18303989f, 0.19509032f, 0.20711138f,
	0.21910124f, 0.23105811f, 0.24298018f, 0.25486566f, 0.26671276f, 0.27851969f,
	0.29028468f, 0.30200595f, 0.31368174f, 0.32531029f, 0.33688985f, 0.34841868f,
	0.35989504f, 0.37131719f, 0.38268343f, 0.39399204f, 0.40524131f, 0.41642956f,
	0.42755509f, 0.43861624f, 0.44961133f, 0.46053871f, 0.47139674f, 0.48218377f,
	0.49289819f, 0.50353838f, 0.51410274f, 0.52458968f, 0.53499762f, 0.54532499f,
	0.55557023f, 0.56573181f, 0.57580819f, 0.58579786f, 0.59569930f, 0.60551104f,
	0.61523159f, 0.62485949f, 0.63439328f, 0.64383154f, 0.65317284f, 0.66241578f,
	0.67155895f, 0.68060100f, 0.68954054f, 0.69837625f, 0.70710678f, 0.71573083f,
	0.72424708f, 0.73265427f, 0.74095113f, 0.74913639f, 0.75720885f, 0.76516727f,
	0.77301045f, 0.78073723f, 0.78834643f, 0.79583690f, 0.80320753f, 0.81045720f,
	0.81758481f, 0.82458930f, 0.83146961f, 0.83822471f, 0.84485357f, 0.85135519f,
	0.85772861f, 0.86397286f, 0.87008699f, 0.87607009f, 0.88192126f, 0.88763962f,
	0.89322430f, 0.89867447f, 0.90398929f, 0.90916798f, 0.91420976f, 0.91911385f,
	0.92387953f, 0.92850608f, 0.93299280f, 0.93733901f, 0.94154407f, 0.94560733f,
	0.94952818f, 0.95330604f, 0.95694034f, 0.96043052f, 0.96377607f, 0.96697647f,
	0.97003125f, 0.97293995f, 0.97570213f, 0.97831737f, 0.98078528f, 0.98310549f,
	0.98527764f, 0.98730142f, 0.98917651f, 0.99090264f, 0.99247953f, 0.99390697f,
	0.99518473f, 0.99631261f, 0.99729046f, 0.99811811f, 0.99879546f, 0.99932238f,
	0.99969882f, 0.99992470f, 1.00000000f, 0.99992470f, 0.99969882f, 0.99932238f,
	0.99879546f, 0.99811811f, 0.99729046f, 0.99631261f, 0.99518473f, 0.99390697f,
	0.99247953f, 0.99090264f, 0.98917651f, 0.98730142f, 0.98527764f, 0.98310549f,
	0.98078528f, 0.97831737f, 0.97570213f, 0.97293995f, 0.97003125f, 0.96697647f,
	0.96377607f, 0.96043052f, 0.95694034f, 0.95330604f, 0.94952818f, 0.94560733f,
	0.94154407f, 0.93733901f, 0.93299280f, 0.92850608f, 0.92387953f, 0.91911385f,
	0.91420976f, 0.90916798f, 0.90398929f, 0.89867447f, 0.89322430f, 0.88763962f,
	0.88192126f, 0.87607009f, 0.87008699f, 0.86397286f, 0.85772861f, 0.85135519f,
	0.84485357f, 0.83822471f, 0.83146961f, 0.82458930f, 0.81758481f, 0.81045720f,
	0.80320753f, 0.79583690f, 0.78834643f, 0.78073723f, 0.77301045f, 0.76516727f,
	0.75720885f, 0.74913639f, 0.74095113f, 0.73265427f, 0.72424708f, 0.71573083f,
	0.70710678f, 0.69837625f, 0.68954054f, 0.68060100f, 0.67155895f, 0.66241578f,
	0.65317284f, 0.64383154f, 0.63439328f, 0.62485949f, 0.61523159f, 0.60551104f,
	0.59569930f, 0.58579786f, 0.57580819f, 0.56573181f, 0.55557023f, 0.54532499f,
	0.53499762f, 0.52458968f, 0.51410274f, 0.50353838f, 0.49289819f, 0.48218377f,
	0.47139674f, 0.46053871f, 0.44961133f, 0.43861624f, 0.42755509f, 0.41642956f,
	0.40524131f, 0.39399204f, 0.38268343f, 0.37131719f, 0.35989504f, 0.34841868f,
	0.33688985f, 0.32531029f, 0.31368174f, 0.30200595f, 0.29028468f, 0.27851969f,
	0.26671276f, 0.25486566f, 0.24298018f, 0.23105811f, 0.21910124f, 0.20711138f,
	0.19509032f, 0.18303989f, 0.17096189f, 0.15885814f, 0.14673047f, 0.13458071f,
	0.12241068f, 0.11022221f, 0.09801714f, 0.08579731f, 0.07356456f, 0.06132074f,
	0.04906767f, 0.03680722f, 0.02454123f, 0.01227154f, 0.00000000f, -0.01227154f,
    -0.02454123f, -0.03680722f, -0.04906767f, -0.06132074f, -0.07356456f, -0.08579731f,
	-0.09801714f, -0.11022221f, -0.12241068f, -0.13458071f, -0.14673047f, -0.15885814f,
	-0.17096189f, -0.18303989f, -0.19509032f, -0.20711138f, -0.21910124f, -0.23105811f,
	-0.24298018f, -0.25486566f, -0.26671276f, -0.27851969f, -0.29028468f, -0.30200595f,
	-0.31368174f, -0.32531029f, -0.33688985f, -0.34841868f, -0.35989504f, -0.37131719f,
	-0.38268343f, -0.39399204f, -0.40524131f, -0.41642956f, -0.42755509f, -0.43861624f,
	-0.44961133f, -0.46053871f, -0.47139674f, -0.48218377f, -0.49289819f, -0.50353838f,
	-0.51410274f, -0.52458968f, -0.53499762f, -0.54532499f, -0.55557023f, -0.56573181f,
	-0.57580819f, -0.58579786f, -0.59569930f, -0.60551104f, -0.61523159f, -0.62485949f,
	-0.63439328f, -0.64383154f, -0.65317284f, -0.66241578f, -0.67155895f, -0.68060100f,
	-0.68954054f, -0.69837625f, -0.70710678f, -0.71573083f, -0.72424708f, -0.73265427f,
	-0.74095113f, -0.74913639f, -0.75720885f, -0.76516727f, -0.77301045f, -0.78073723f,
	-0.78834643f, -0.79583690f, -0.80320753f, -0.81045720f, -0.81758481f, -0.82458930f,
	-0.83146961f, -0.83822471f, -0.84485357f, -0.85135519f, -0.85772861f, -0.86397286f,
	-0.87008699f, -0.87607009f, -0.88192126f, -0.88763962f, -0.89322430f, -0.89867447f,
	-0.90398929f, -0.90916798f, -0.91420976f, -0.91911385f, -0.92387953f, -0.92850608f,
	-0.93299280f, -0.93733901f, -0.94154407f, -0.94560733f, -0.94952818f, -0.95330604f,
	-0.95694034f, -0.96043052f, -0.96377607f, -0.96697647f, -0.97003125f, -0.97293995f,
	-0.97570213f, -0.97831737f, -0.98078528f, -0.98310549f, -0.98527764f, -0.98730142f,
	-0.98917651f, -0.99090264f, -0.99247953f, -0.99390697f, -0.99518473f, -0.99631261f,
	-0.99729046f, -0.99811811f, -0.99879546f, -0.99932238f, -0.99969882f, -0.99992470f,
	-1.00000000f, -0.99992470f, -0.99969882f, -0.99932238f, -0.99879546f, -0.99811811f,
	-0.99729046f, -0.99631261f, -0.99518473f, -0.99390697f, -0.99247953f, -0.99090264f,
	-0.98917651f, -0.98730142f, -0.98527764f, -0.98310549f, -0.98078528f, -0.97831737f,
	-0.97570213f, -0.97293995f, -0.97003125f, -0.96697647f, -0.96377607f, -0.96043052f,
	-0.95694034f, -0.95330604f, -0.94952818f, -0.94560733f, -0.94154407f, -0.93733901f,
	-0.93299280f, -0.92850608f, -0.92387953f, -0.91911385f, -0.91420976f, -0.90916798f,
	-0.90398929f, -0.89867447f, -0.89322430f, -0.88763962f, -0.88192126f, -0.87607009f,
	-0.87008699f, -0.86397286f, -0.85772861f, -0.85135519f, -0.84485357f, -0.83822471f,
	-0.83146961f, -0.82458930f, -0.81758481f, -0.81045720f, -0.80320753f, -0.79583690f,
	-0.78834643f, -0.78073723f, -0.77301045f, -0.76516727f, -0.75720885f, -0.74913639f,
	-0.74095113f, -0.73265427f, -0.72424708f, -0.71573083f, -0.70710678f, -0.69837625f,
	-0.68954054f, -0.68060100f, -0.67155895f, -0.66241578f, -0.65317284f, -0.64383154f,
	-0.63439328f, -0.62485949f, -0.61523159f, -0.60551104f, -0.59569930f, -0.58579786f,
	-0.57580819f, -0.56573181f, -0.55557023f, -0.54532499f, -0.53499762f, -0.52458968f,
	-0.51410274f, -0.50353838f, -0.49289819f, -0.48218377f, -0.47139674f, -0.46053871f,
	-0.44961133f, -0.43861624f, -0.42755509f, -0.41642956f, -0.40524131f, -0.39399204f,
	-0.38268343f, -0.37131719f, -0.35989504f, -0.34841868f, -0.33688985f, -0.32531029f,
	-0.31368174f, -0.30200595f, -0.29028468f, -0.27851969f, -0.26671276f, -0.25486566f,
	-0.24298018f, -0.23105811f, -0.21910124f, -0.20711138f, -0.19509032f, -0.18303989f,
	-0.17096189f, -0.15885814f, -0.14673047f, -0.13458071f, -0.12241068f, -0.11022221f,
	-0.09801714f, -0.08579731f, -0.07356456f, -0.06132074f, -0.04906767f, -0.03680722f,
	-0.02454123f, -0.01227154f, -0.00000000f, 0.00000000f
};

/**********************************************************************************************
Function: Math_SinCos_F
Description: 浮点正余弦计算
Input: 角度，0到2PI
Output: 正弦，余弦
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Math_SinCos_F(ST_TRIG_F* pTIG)
{
    float Input;
    float Findex;
    Q32I_ Index;
	float M;
	float N;
	float Fract;
    Input = pTIG->F_Angle;
    Findex = Input * (float)SINE_TABLE_SIZE;
    Index = (Q32I_)Findex;
    M = Math_Sin_Table_Float[Index];
    N = Math_Sin_Table_Float[Index + 1];
    Fract = Findex - (float)Index;
    pTIG->F_Sin = M + Fract * (N - M);
    
    Input = Input + 0.25f;
    if(Input > 1.0f)
    {
        Input -= 1.0f;        
    }
    Findex = Input * (float)SINE_TABLE_SIZE;
    Index = (Q32I_)Findex;
    M = Math_Sin_Table_Float[Index];
    N = Math_Sin_Table_Float[Index + 1];
    Fract = Findex - (float)Index;
    pTIG->F_Cos = M + Fract * (N - M);
}

/**********************************************************************************************
Function: Math_Atan_F
Description: 浮点反正切计算
Input: 正弦，余弦
Output: 角度，0到2PI
Input_Output: 浮点角度指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Math_Atan_F(ST_TRIG_F* pTIG)
{
    Q08U_ Sector_N;
	Q08U_ Sector_a = 0U;
	Q08U_ Sector_b = 0U;
	Q08U_ Sector_c = 0U;
    
	float Cos_tmp,Sin_tmp,Tan_tmp;
    
	float temp;
	float deg_temp = 0.0f;

	Cos_tmp = pTIG->F_Cos;
	Sin_tmp = pTIG->F_Sin;

    if(Cos_tmp == 0.0f && Sin_tmp == 0.0f)
    {
		pTIG->F_ReAngle = 0.0f;
    }
    else
    {
        if (Cos_tmp < 0.0f)
        {
            Cos_tmp = -Cos_tmp;
            Sector_b = 2U;
        }
        if (Sin_tmp < 0.0f)
        {
            Sin_tmp = -Sin_tmp;
            Sector_c = 4U;
        }
        if (Sin_tmp > Cos_tmp)
        {
            temp = Cos_tmp;
            Cos_tmp = Sin_tmp;
            Sin_tmp = temp;
            Sector_a = 1U;
        }
        Sector_N = Sector_a + Sector_b + Sector_c;

        Tan_tmp = Sin_tmp/Cos_tmp;
	
        deg_temp = Tan_tmp*(MATH_PI_OVER_FOUR_F + (1.0f - Tan_tmp)*(0.2447f + 0.0663f*Tan_tmp));
        
        switch (Sector_N)
        {
            case 0U:
                pTIG->F_ReAngle = deg_temp;
			break;
            case 1U:
                pTIG->F_ReAngle = 1.0f*MATH_PI_OVER_TWO_F - (deg_temp);		
			break;
            case 2U:
                pTIG->F_ReAngle = 2.0f*MATH_PI_OVER_TWO_F - (deg_temp);		
			break;
            case 3U:
                pTIG->F_ReAngle = 1.0f*MATH_PI_OVER_TWO_F + (deg_temp);		
            break;
            case 4U:
                pTIG->F_ReAngle = 4.0f*MATH_PI_OVER_TWO_F - (deg_temp);		
            break;
            case 5U:
                pTIG->F_ReAngle = 3.0f*MATH_PI_OVER_TWO_F + (deg_temp);		
            break;
            case 6U:
                pTIG->F_ReAngle = 2.0f*MATH_PI_OVER_TWO_F + (deg_temp);		
            break;
            case 7U:
                pTIG->F_ReAngle = 3.0f*MATH_PI_OVER_TWO_F - (deg_temp);	
            break;
            default:
                pTIG->F_ReAngle = 0.0f;
            break;
        }
    }
}

/**********************************************************************************************
Function: Math_Sqrt_F
Description: 浮点平方根计算
Input: 正浮点数
Output: 平方根
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
float Math_Sqrt_F(float A)
{
    if(A > 0.0f)
    {
        float xhalf = 0.5f * A;
        Q32I_ i = *(Q32I_*)&A;
        i = 0x1FBD1DF5 + (i >> 1U);
        A = *(float*)&i;
        A = 0.5f * A + xhalf / A;
    }
    else
    {
        A = 0.0f;
    }
    return A;
}

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
void Delay_ns(Q32U_ time)
{
	Q32U_ delay_count1 = 0,delay_count2 = 0;
	for(delay_count2=0;delay_count2<time;delay_count2++){
        for(delay_count1=0;delay_count1<MATH_DELAY_NS_COUNT;delay_count1++);
    }
}

/**********************************************************************************************
Function: Delay_us
Description: us延迟
Input: 时间值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Delay_us(Q32U_ time)
{
	Q32U_ delay_count1 = 0,delay_count2 = 0;
	for(delay_count2=0;delay_count2<time;delay_count2++){
        for(delay_count1=0;delay_count1<MATH_DELAY_US_COUNT;delay_count1++);
    }
}

/**********************************************************************************************
Function: Delay_ms
Description: ms延迟
Input: 时间值
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void Delay_ms(Q32U_ time)
{
	Q32U_ delay_count1 = 0,delay_count2 = 0;
	for(delay_count2=0;delay_count2<time;delay_count2++){
        for(delay_count1=0;delay_count1<MATH_DELAY_MS_COUNT;delay_count1++);
    }
}
