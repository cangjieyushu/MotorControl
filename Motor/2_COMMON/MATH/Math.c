/**************************************************************************************************
*     File Name :                        Math.c
*     Library/Module Name :              MATH
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             数学运算库源文件
**************************************************************************************************/
#include "Math.h"

/************************************定点数学库**************************************/

/**********************************************************************************************
Function: Ramp_Init
Description: 定点斜坡初始化
Input: 定点斜坡输出初始值
Output: 无
Input_Output: 定点斜坡指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Ramp_Init(ST_RAMP* pRamp, Q16I_ init)
{
    pRamp->Q32I_Output = init;
}

/**********************************************************************************************
Function: Ramp_Cal
Description: 定点斜坡计算
Input: 无
Output: 无
Input_Output: 定点斜坡指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Ramp_Cal(ST_RAMP* pRamp)
{    
    if(pRamp->Q32I_Target > pRamp->Q32I_Output) 
    { 
        if(pRamp->Q32I_Target > pRamp->Q32I_Output + pRamp->Q32I_ADDStep) 
        {
            pRamp->Q32I_Output += pRamp->Q32I_ADDStep;
        }
        else 
        {
            pRamp->Q32I_Output = pRamp->Q32I_Target;
        }
    }
    else if(pRamp->Q32I_Target < pRamp->Q32I_Output) 
    { 
        if(pRamp->Q32I_Target < pRamp->Q32I_Output + pRamp->Q32I_SUBStep) 
        {
            pRamp->Q32I_Output -= pRamp->Q32I_ADDStep;
        }
        else 
        {
            pRamp->Q32I_Output = pRamp->Q32I_Target;
        }
    }
    else 
    {
        pRamp->Q32I_Output = pRamp->Q32I_Target;
    }
}

/**********************************************************************************************
Function: Filter_Init
Description: 定点低通滤波初始化
Input: 定点低通滤波初始值
Output: 无
Input_Output: 定点低通滤波指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Filter_Init(ST_FILTER* pFltr, Q16I_ init)
{
    pFltr->Q32I_Filter_tmp = Q16I_LFT_08(init);
    pFltr->Q16I_Filter_out = init;
}

/**********************************************************************************************
Function: Filter_Cal
Description: 定点低通滤波计算
Input: 无
Output: 无
Input_Output: 定点低通滤波指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Filter_Cal(ST_FILTER* pFltr)
{
    pFltr->Q32I_Filter_tmp = Q32I_RHT_08(Q16I_LFT_08(pFltr->Q08I_Filter_Coeff*pFltr->Q16I_Filter_in)
    + (MATH_FILTER_MAX - pFltr->Q08I_Filter_Coeff)*pFltr->Q32I_Filter_tmp);
    pFltr->Q16I_Filter_out = Q32I_RHT_08(pFltr->Q32I_Filter_tmp);
}

/**********************************************************************************************
Function: PID_Inc_Init
Description: 定点增量式PID初始化
Input: 定点积分器初始值
Output: 无
Input_Output: 定点增量式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Inc_Init(ST_PID_INC* pPID, Q16I_ init)
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
Function: PID_Inc_Cal
Description: 定点增量式PID计算
Input: 无
Output: 无
Input_Output: 定点增量式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Inc_Cal(ST_PID_INC* pPID)
{
    Q32I_ Q14I_Error = pPID->Q14I_Rf - pPID->Q14I_Fb;
    
    pPID->Q28I_Step = pPID->Q14I_Kp*(Q14I_Error - pPID->Q14I_LastError) + pPID->Q14I_Ki*Q14I_Error
    + pPID->Q14I_Kd*(Q14I_Error + pPID->Q14I_PrevError - 2*pPID->Q14I_LastError);
    pPID->Q28I_Step = MATH_SAT_U(pPID->Q28I_Step, Q16I_LFT_14(pPID->Q14I_StepMax), Q16I_LFT_14(pPID->Q14I_StepMin));
    
    pPID->Q28I_Output_tmp += pPID->Q28I_Step;
    pPID->Q28I_Output_tmp = MATH_SAT_U(pPID->Q28I_Output_tmp, Q16I_LFT_14(pPID->Q14I_OutMax), Q16I_LFT_14(pPID->Q14I_OutMin));
    
    pPID->Q14I_Output = Q32I_RHT_14(pPID->Q28I_Output_tmp);
    pPID->Q14I_PrevError = pPID->Q14I_LastError;
    pPID->Q14I_LastError = Q14I_Error;
}

/**********************************************************************************************
Function: PID_Pos_Init
Description: 定点位置式PID初始化
Input: 定点积分器初始值
Output: 无
Input_Output: 定点位置式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Pos_Init(ST_PID_POS* pPID, Q16I_ init)
{
    pPID->Q14I_Rf = 0;
    pPID->Q14I_Fb = 0;
    pPID->Q14I_Ui = init;
    pPID->Q28I_Ui_tmp = Q16I_LFT_14(init);
    pPID->Q14I_Output = init;
}

/**********************************************************************************************
Function: PID_Pos_Cal
Description: 定点位置式PID计算
Input: 无
Output: 无
Input_Output: 定点位置式PID指针
Return: 无
Author: CJYS
***********************************************************************************************/
void PID_Pos_Cal(ST_PID_POS* pPID)
{
    Q32I_ Q14I_Error = pPID->Q14I_Rf - pPID->Q14I_Fb;
    
    pPID->Q28I_Ui_tmp += pPID->Q14I_Ki*Q14I_Error;
    pPID->Q28I_Ui_tmp = MATH_SAT_U(pPID->Q28I_Ui_tmp, Q16I_LFT_14(pPID->Q14I_OutMax), Q16I_LFT_14(pPID->Q14I_OutMin));
    pPID->Q14I_Ui = Q32I_RHT_14(pPID->Q28I_Ui_tmp);
    
    pPID->Q14I_Output = Q32I_RHT_14(pPID->Q14I_Kp*Q14I_Error) + pPID->Q14I_Ui;
    pPID->Q14I_Output = MATH_SAT_U(pPID->Q14I_Output, pPID->Q14I_OutMax, pPID->Q14I_OutMin);
}

static const Q16I_ Math_Sin_Table_I16[1024] = {
0x0000U,0x0019U,0x0032U,0x004BU,0x0064U,0x007DU,0x0096U,0x00AFU,0x00C9U,0x00E2,
0x00FBU,0x0114U,0x012DU,0x0146U,0x015FU,0x0178U,0x0192U,0x01ABU,0x01C4U,0x01DD,
0x01F6U,0x020FU,0x0228U,0x0241U,0x025BU,0x0274U,0x028DU,0x02A6U,0x02BFU,0x02D8,
0x02F1U,0x030AU,0x0323U,0x033DU,0x0356U,0x036FU,0x0388U,0x03A1U,0x03BAU,0x03D3,
0x03ECU,0x0405U,0x041EU,0x0437U,0x0451U,0x046AU,0x0483U,0x049CU,0x04B5U,0x04CE,
0x04E7U,0x0500U,0x0519U,0x0532U,0x054BU,0x0564U,0x057DU,0x0596U,0x05AFU,0x05C8,
0x05E1U,0x05FAU,0x0613U,0x062CU,0x0645U,0x065EU,0x0677U,0x0690U,0x06A9U,0x06C2,
0x06DBU,0x06F4U,0x070DU,0x0726U,0x073FU,0x0758U,0x0771U,0x078AU,0x07A3U,0x07BC,
0x07D5U,0x07EEU,0x0807U,0x0820U,0x0839U,0x0852U,0x086BU,0x0884U,0x089CU,0x08B5,
0x08CEU,0x08E7U,0x0900U,0x0919U,0x0932U,0x094BU,0x0964U,0x097CU,0x0995U,0x09AE,
0x09C7U,0x09E0U,0x09F9U,0x0A11U,0x0A2AU,0x0A43U,0x0A5CU,0x0A75U,0x0A8DU,0x0AA6,
0x0ABFU,0x0AD8U,0x0AF1U,0x0B09U,0x0B22U,0x0B3BU,0x0B54U,0x0B6CU,0x0B85U,0x0B9E,
0x0BB6U,0x0BCFU,0x0BE8U,0x0C01U,0x0C19U,0x0C32U,0x0C4BU,0x0C63U,0x0C7CU,0x0C95,
0x0CADU,0x0CC6U,0x0CDEU,0x0CF7U,0x0D10U,0x0D28U,0x0D41U,0x0D59U,0x0D72U,0x0D8B,
0x0DA3U,0x0DBCU,0x0DD4U,0x0DEDU,0x0E05U,0x0E1EU,0x0E36U,0x0E4FU,0x0E67U,0x0E80,
0x0E98U,0x0EB1U,0x0EC9U,0x0EE2U,0x0EFAU,0x0F12U,0x0F2BU,0x0F43U,0x0F5CU,0x0F74,
0x0F8CU,0x0FA5U,0x0FBDU,0x0FD6U,0x0FEEU,0x1006U,0x101FU,0x1037U,0x104FU,0x1068,	
0x1080U,0x1098U,0x10B0U,0x10C9U,0x10E1U,0x10F9U,0x1111U,0x112AU,0x1142U,0x115A,
0x1172U,0x118AU,0x11A2U,0x11BBU,0x11D3U,0x11EBU,0x1203U,0x121BU,0x1233U,0x124B,
0x1263U,0x127BU,0x1294U,0x12ACU,0x12C4U,0x12DCU,0x12F4U,0x130CU,0x1324U,0x133C,
0x1354U,0x136CU,0x1383U,0x139BU,0x13B3U,0x13CBU,0x13E3U,0x13FBU,0x1413U,0x142B,
0x1443U,0x145AU,0x1472U,0x148AU,0x14A2U,0x14BAU,0x14D1U,0x14E9U,0x1501U,0x1519,
0x1530U,0x1548U,0x1560U,0x1577U,0x158FU,0x15A7U,0x15BEU,0x15D6U,0x15EEU,0x1605,
0x161DU,0x1634U,0x164CU,0x1664U,0x167BU,0x1693U,0x16AAU,0x16C2U,0x16D9U,0x16F1,
0x1708U,0x171FU,0x1737U,0x174EU,0x1766U,0x177DU,0x1794U,0x17ACU,0x17C3U,0x17DA,
0x17F2U,0x1809U,0x1820U,0x1838U,0x184FU,0x1866U,0x187DU,0x1895U,0x18ACU,0x18C3,
0x18DAU,0x18F1U,0x1908U,0x1920U,0x1937U,0x194EU,0x1965U,0x197CU,0x1993U,0x19AA,
0x19C1U,0x19D8U,0x19EFU,0x1A06U,0x1A1DU,0x1A34U,0x1A4BU,0x1A62U,0x1A79U,0x1A8F,
0x1AA6U,0x1ABDU,0x1AD4U,0x1AEBU,0x1B02U,0x1B18U,0x1B2FU,0x1B46U,0x1B5DU,0x1B73,
0x1B8AU,0x1BA1U,0x1BB7U,0x1BCEU,0x1BE5U,0x1BFBU,0x1C12U,0x1C28U,0x1C3FU,0x1C55,
0x1C6CU,0x1C83U,0x1C99U,0x1CAFU,0x1CC6U,0x1CDCU,0x1CF3U,0x1D09U,0x1D20U,0x1D36,
0x1D4CU,0x1D63U,0x1D79U,0x1D8FU,0x1DA6U,0x1DBCU,0x1DD2U,0x1DE8U,0x1DFEU,0x1E15,
0x1E2BU,0x1E41U,0x1E57U,0x1E6DU,0x1E83U,0x1E99U,0x1EB0U,0x1EC6U,0x1EDCU,0x1EF2,
0x1F08U,0x1F1EU,0x1F34U,0x1F49U,0x1F5FU,0x1F75U,0x1F8BU,0x1FA1U,0x1FB7U,0x1FCD,
0x1FE2U,0x1FF8U,0x200EU,0x2024U,0x2039U,0x204FU,0x2065U,0x207BU,0x2090U,0x20A6,
0x20BBU,0x20D1U,0x20E7U,0x20FCU,0x2112U,0x2127U,0x213DU,0x2152U,0x2168U,0x217D,
0x2192U,0x21A8U,0x21BDU,0x21D2U,0x21E8U,0x21FDU,0x2212U,0x2228U,0x223DU,0x2252,
0x2267U,0x227DU,0x2292U,0x22A7U,0x22BCU,0x22D1U,0x22E6U,0x22FBU,0x2310U,0x2325,
0x233AU,0x234FU,0x2364U,0x2379U,0x238EU,0x23A3U,0x23B8U,0x23CDU,0x23E1U,0x23F6,
0x240BU,0x2420U,0x2434U,0x2449U,0x245EU,0x2473U,0x2487U,0x249CU,0x24B0U,0x24C5,
0x24DAU,0x24EEU,0x2503U,0x2517U,0x252CU,0x2540U,0x2554U,0x2569U,0x257DU,0x2592,
0x25A6U,0x25BAU,0x25CFU,0x25E3U,0x25F7U,0x260BU,0x261FU,0x2634U,0x2648U,0x265C,
0x2670U,0x2684U,0x2698U,0x26ACU,0x26C0U,0x26D4U,0x26E8U,0x26FCU,0x2710U,0x2724,
0x2738U,0x274CU,0x275FU,0x2773U,0x2787U,0x279BU,0x27AFU,0x27C2U,0x27D6U,0x27EA,
0x27FDU,0x2811U,0x2824U,0x2838U,0x284BU,0x285FU,0x2872U,0x2886U,0x2899U,0x28AD,
0x28C0U,0x28D4U,0x28E7U,0x28FAU,0x290EU,0x2921U,0x2934U,0x2947U,0x295AU,0x296E,
0x2981U,0x2994U,0x29A7U,0x29BAU,0x29CDU,0x29E0U,0x29F3U,0x2A06U,0x2A19U,0x2A2C,
0x2A3FU,0x2A52U,0x2A65U,0x2A77U,0x2A8AU,0x2A9DU,0x2AB0U,0x2AC2U,0x2AD5U,0x2AE8,
0x2AFAU,0x2B0DU,0x2B20U,0x2B32U,0x2B45U,0x2B57U,0x2B6AU,0x2B7CU,0x2B8EU,0x2BA1,
0x2BB3U,0x2BC6U,0x2BD8U,0x2BEAU,0x2BFCU,0x2C0FU,0x2C21U,0x2C33U,0x2C45U,0x2C57,
0x2C6AU,0x2C7CU,0x2C8EU,0x2CA0U,0x2CB2U,0x2CC4U,0x2CD6U,0x2CE8U,0x2CF9U,0x2D0B,
0x2D1DU,0x2D2FU,0x2D41U,0x2D52U,0x2D64U,0x2D76U,0x2D88U,0x2D99U,0x2DABU,0x2DBC,
0x2DCEU,0x2DE0U,0x2DF1U,0x2E03U,0x2E14U,0x2E25U,0x2E37U,0x2E48U,0x2E5AU,0x2E6B,
0x2E7CU,0x2E8DU,0x2E9FU,0x2EB0U,0x2EC1U,0x2ED2U,0x2EE3U,0x2EF4U,0x2F05U,0x2F16,
0x2F28U,0x2F38U,0x2F49U,0x2F5AU,0x2F6BU,0x2F7CU,0x2F8DU,0x2F9EU,0x2FAFU,0x2FBF,
0x2FD0U,0x2FE1U,0x2FF1U,0x3002U,0x3013U,0x3023U,0x3034U,0x3044U,0x3055U,0x3065,
0x3076U,0x3086U,0x3096U,0x30A7U,0x30B7U,0x30C7U,0x30D8U,0x30E8U,0x30F8U,0x3108,
0x3118U,0x3128U,0x3138U,0x3149U,0x3159U,0x3169U,0x3179U,0x3188U,0x3198U,0x31A8,
0x31B8U,0x31C8U,0x31D8U,0x31E7U,0x31F7U,0x3207U,0x3216U,0x3226U,0x3236U,0x3245,
0x3255U,0x3264U,0x3274U,0x3283U,0x3293U,0x32A2U,0x32B1U,0x32C1U,0x32D0U,0x32DF,
0x32EEU,0x32FEU,0x330DU,0x331CU,0x332BU,0x333AU,0x3349U,0x3358U,0x3367U,0x3376,
0x3385U,0x3394U,0x33A3U,0x33B2U,0x33C1U,0x33CFU,0x33DEU,0x33EDU,0x33FBU,0x340A,
0x3419U,0x3427U,0x3436U,0x3444U,0x3453U,0x3461U,0x3470U,0x347EU,0x348CU,0x349B,
0x34A9U,0x34B7U,0x34C6U,0x34D4U,0x34E2U,0x34F0U,0x34FEU,0x350CU,0x351AU,0x3528,
0x3536U,0x3544U,0x3552U,0x3560U,0x356EU,0x357CU,0x3589U,0x3597U,0x35A5U,0x35B3,
0x35C0U,0x35CEU,0x35DCU,0x35E9U,0x35F7U,0x3604U,0x3612U,0x361FU,0x362CU,0x363A,
0x3647U,0x3654U,0x3662U,0x366FU,0x367CU,0x3689U,0x3696U,0x36A4U,0x36B1U,0x36BE,
0x36CBU,0x36D8U,0x36E5U,0x36F1U,0x36FEU,0x370BU,0x3718U,0x3725U,0x3731U,0x373E,
0x374BU,0x3757U,0x3764U,0x3771U,0x377DU,0x378AU,0x3796U,0x37A3U,0x37AFU,0x37BB,
0x37C8U,0x37D4U,0x37E0U,0x37EDU,0x37F9U,0x3805U,0x3811U,0x381DU,0x3829U,0x3835,
0x3841U,0x384DU,0x3859U,0x3865U,0x3871U,0x387DU,0x3889U,0x3894U,0x38A0U,0x38AC,
0x38B7U,0x38C3U,0x38CFU,0x38DAU,0x38E6U,0x38F1U,0x38FDU,0x3908U,0x3913U,0x391F,
0x392AU,0x3935U,0x3941U,0x394CU,0x3957U,0x3962U,0x396DU,0x3978U,0x3983U,0x398E,
0x3999U,0x39A4U,0x39AFU,0x39BAU,0x39C5U,0x39D0U,0x39DAU,0x39E5U,0x39F0U,0x39FB,
0x3A05U,0x3A10U,0x3A1AU,0x3A25U,0x3A2FU,0x3A3AU,0x3A44U,0x3A4FU,0x3A59U,0x3A63,
0x3A6DU,0x3A78U,0x3A82U,0x3A8CU,0x3A96U,0x3AA0U,0x3AAAU,0x3AB4U,0x3ABEU,0x3AC8,
0x3AD2U,0x3ADCU,0x3AE6U,0x3AF0U,0x3AFAU,0x3B03U,0x3B0DU,0x3B17U,0x3B20U,0x3B2A,
0x3B34U,0x3B3DU,0x3B47U,0x3B50U,0x3B59U,0x3B63U,0x3B6CU,0x3B75U,0x3B7FU,0x3B88,
0x3B91U,0x3B9AU,0x3BA3U,0x3BADU,0x3BB6U,0x3BBFU,0x3BC8U,0x3BD1U,0x3BDAU,0x3BE2,
0x3BEBU,0x3BF4U,0x3BFDU,0x3C06U,0x3C0EU,0x3C17U,0x3C20U,0x3C28U,0x3C31U,0x3C39,
0x3C42U,0x3C4AU,0x3C53U,0x3C5BU,0x3C63U,0x3C6CU,0x3C74U,0x3C7CU,0x3C84U,0x3C8C,
0x3C95U,0x3C9DU,0x3CA5U,0x3CADU,0x3CB5U,0x3CBDU,0x3CC5U,0x3CCCU,0x3CD4U,0x3CDC,
0x3CE4U,0x3CECU,0x3CF3U,0x3CFBU,0x3D02U,0x3D0AU,0x3D12U,0x3D19U,0x3D21U,0x3D28,
0x3D2FU,0x3D37U,0x3D3EU,0x3D45U,0x3D4DU,0x3D54U,0x3D5BU,0x3D62U,0x3D69U,0x3D70,
0x3D77U,0x3D7EU,0x3D85U,0x3D8CU,0x3D93U,0x3D9AU,0x3DA1U,0x3DA7U,0x3DAEU,0x3DB5,
0x3DBBU,0x3DC2U,0x3DC9U,0x3DCFU,0x3DD6U,0x3DDCU,0x3DE2U,0x3DE9U,0x3DEFU,0x3DF5,
0x3DFCU,0x3E02U,0x3E08U,0x3E0EU,0x3E14U,0x3E1BU,0x3E21U,0x3E27U,0x3E2DU,0x3E33,
0x3E38U,0x3E3EU,0x3E44U,0x3E4AU,0x3E50U,0x3E55U,0x3E5BU,0x3E61U,0x3E66U,0x3E6C,
0x3E71U,0x3E77U,0x3E7CU,0x3E82U,0x3E87U,0x3E8CU,0x3E92U,0x3E97U,0x3E9CU,0x3EA1,
0x3EA7U,0x3EACU,0x3EB1U,0x3EB6U,0x3EBBU,0x3EC0U,0x3EC5U,0x3ECAU,0x3ECEU,0x3ED3,
0x3ED8U,0x3EDDU,0x3EE1U,0x3EE6U,0x3EEBU,0x3EEFU,0x3EF4U,0x3EF8U,0x3EFDU,0x3F01,
0x3F06U,0x3F0AU,0x3F0EU,0x3F13U,0x3F17U,0x3F1BU,0x3F1FU,0x3F23U,0x3F27U,0x3F2B,
0x3F2FU,0x3F33U,0x3F37U,0x3F3BU,0x3F3FU,0x3F43U,0x3F47U,0x3F4AU,0x3F4EU,0x3F52,
0x3F55U,0x3F59U,0x3F5DU,0x3F60U,0x3F64U,0x3F67U,0x3F6AU,0x3F6EU,0x3F71U,0x3F74,
0x3F78U,0x3F7BU,0x3F7EU,0x3F81U,0x3F84U,0x3F87U,0x3F8AU,0x3F8DU,0x3F90U,0x3F93,
0x3F96U,0x3F99U,0x3F9CU,0x3F9EU,0x3FA1U,0x3FA4U,0x3FA6U,0x3FA9U,0x3FACU,0x3FAE,
0x3FB1U,0x3FB3U,0x3FB5U,0x3FB8U,0x3FBAU,0x3FBCU,0x3FBFU,0x3FC1U,0x3FC3U,0x3FC5,
0x3FC7U,0x3FC9U,0x3FCBU,0x3FCDU,0x3FCFU,0x3FD1U,0x3FD3U,0x3FD5U,0x3FD7U,0x3FD8,
0x3FDAU,0x3FDCU,0x3FDEU,0x3FDFU,0x3FE1U,0x3FE2U,0x3FE4U,0x3FE5U,0x3FE7U,0x3FE8,
0x3FE9U,0x3FEBU,0x3FECU,0x3FEDU,0x3FEEU,0x3FEFU,0x3FF0U,0x3FF1U,0x3FF2U,0x3FF3,
0x3FF4U,0x3FF5U,0x3FF6U,0x3FF7U,0x3FF8U,0x3FF9U,0x3FF9U,0x3FFAU,0x3FFBU,0x3FFB,
0x3FFCU,0x3FFCU,0x3FFDU,0x3FFDU,0x3FFEU,0x3FFEU,0x3FFEU,0x3FFFU,0x3FFFU,0x3FFF,
0x3FFFU,0x3FFFU,0x3FFFU,0x3FFFU,};
 
#define SIN_MASK        0x0C00U
#define U0_90           0x0000U
#define U90_180         0x0400U
#define U180_270        0x0800U
#define U270_360        0x0C00U
 
/**********************************************************************************************
Function: Math_SinCos
Description: 定点正余弦计算
Input: 角度，0到4096
Output: 正弦，余弦
Input_Output: 定点角度指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Math_SinCos(ST_TRIG* pTIG)
{
    Q16U_ Q16U_index_tmp;
    Q16U_index_tmp = 0x3FFU & pTIG->Q12U_Angle;
 
    switch(pTIG->Q12U_Angle & SIN_MASK)
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
Function: Math_Atan
Description: 定点反正切计算
Input: 正弦，余弦
Output: 角度，0到4096
Input_Output: 定点角度指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Math_Atan(ST_TRIG* pTIG)
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
		pTIG->Q16U_ReAngle = 0;
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

        Tan_tmp = ((Sin_tmp<<14)/Cos_tmp);
	
        temp1 = ((Tan_tmp*2789)>>14) + 10195; 
        temp2 = ((16384 - Tan_tmp)*temp1)>>14; 
        deg_temp = (Tan_tmp*(32768 + temp2))>>20;
	
        switch (Sector_N)
        {
            case 0U:
                pTIG->Q16U_ReAngle = deg_temp;
			break;
            case 1U:
                pTIG->Q16U_ReAngle = 1023 - (deg_temp);		
			break;
            case 2U:
                pTIG->Q16U_ReAngle = 2047 - (deg_temp);		
			break;
            case 3U:
                pTIG->Q16U_ReAngle = 1024 + (deg_temp);		
            break;
            case 4U:
                pTIG->Q16U_ReAngle = 4095 - (deg_temp);		
            break;
            case 5U:
                pTIG->Q16U_ReAngle = 3072 + (deg_temp);		
            break;
            case 6U:
                pTIG->Q16U_ReAngle = 2048 + (deg_temp);		
            break;
            case 7U:
                pTIG->Q16U_ReAngle = 3071 - (deg_temp);	
            break;
            default:
                pTIG->Q16U_ReAngle = 0;
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
Ram_Func void Ramp_Init_F(ST_RAMP_F* pRamp, float init)
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
Ram_Func void Ramp_Cal_F(ST_RAMP_F* pRamp)
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
            pRamp->F_Output -= pRamp->F_ADDStep;
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
Ram_Func void Filter_Init_F(ST_FILTER_F* pFltr, float init)
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
Ram_Func void Filter_Cal_F(ST_FILTER_F* pFltr)
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
Ram_Func void PID_Pos_Init_F(ST_PID_POS_F* pPID, float init)
{
    pPID->F_Rf = 0;
    pPID->F_Fb = 0;
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
Ram_Func void PID_Pos_Cal_F(ST_PID_POS_F* pPID)
{
    float F_Error = pPID->F_Rf - pPID->F_Fb;
    
    pPID->F_Ui += pPID->F_Ki*F_Error;
    pPID->F_Ui = MATH_SAT_U(pPID->F_Ui, pPID->F_OutMax, pPID->F_OutMin);
    
    pPID->F_Output = pPID->F_Kp*F_Error + pPID->F_Ui;
    pPID->F_Output = MATH_SAT_U(pPID->F_Output, pPID->F_OutMax, pPID->F_OutMin);
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
Function: Math_Sin_F
Description: 浮点正余弦计算
Input: 角度，0到2PI
Output: 正弦值
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func float Math_Sin_F(float A)
{
    float Input, OutVal;
    float Findex;
    Q32I_ Index;
	float a;
	float b;
	float Fract;

	/* Angle period converted to 1 */
    Input = A * MATH_ONE_OVER_2PI_F;
    Findex = Input * (float)SINE_TABLE_SIZE;
    Index = (Q32I_)Findex;
    a = Math_Sin_Table_Float[Index];
    b = Math_Sin_Table_Float[Index + 1];
    Fract = Findex - (float)Index;
    OutVal = a + Fract * (b - a);
    return OutVal;
}

/**********************************************************************************************
Function: Math_Cos_F
Description: 浮点正余弦计算
Input: 角度，0到2PI
Output: 余弦值
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
Ram_Func float Math_Cos_F(float A)
{
    float Input, OutVal;
    float Findex;
    Q32I_ Index;   
    float M;
    float N;
    float Fract;
    Input = A * MATH_ONE_OVER_2PI_F + 0.25f;
    while(Input > 1.0f)
    {
        Input -= 1.0f;        
    }
    Findex = Input * (float)SINE_TABLE_SIZE;
    Index = (Q32I_)Findex;
    M = Math_Sin_Table_Float[Index];
    N = Math_Sin_Table_Float[Index + 1];
    Fract = Findex - (float)Index;
    OutVal = M + Fract * (N - M);
    return OutVal;
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
Ram_Func float Math_Atan_F(float Sin, float Cos)
{
    Q08U_ Sector_N;
	Q08U_ Sector_a = 0U;
	Q08U_ Sector_b = 0U;
	Q08U_ Sector_c = 0U;
    
	float Cos_tmp,Sin_tmp,Tan_tmp,Atan_tmp;
    
	float temp;
	float deg_temp = 0.0f;

	Cos_tmp = Cos;
	Sin_tmp = Sin;

    if(Cos_tmp == 0.0f && Sin_tmp == 0.0f)
    {
		Atan_tmp = 0.0f;
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
                Atan_tmp = deg_temp;
			break;
            case 1U:
                Atan_tmp = 1.0f*MATH_PI_OVER_TWO_F - (deg_temp);		
			break;
            case 2U:
                Atan_tmp = 2.0f*MATH_PI_OVER_TWO_F - (deg_temp);		
			break;
            case 3U:
                Atan_tmp = 1.0f*MATH_PI_OVER_TWO_F + (deg_temp);		
            break;
            case 4U:
                Atan_tmp = 4.0f*MATH_PI_OVER_TWO_F - (deg_temp);		
            break;
            case 5U:
                Atan_tmp = 3.0f*MATH_PI_OVER_TWO_F + (deg_temp);		
            break;
            case 6U:
                Atan_tmp = 2.0f*MATH_PI_OVER_TWO_F + (deg_temp);		
            break;
            case 7U:
                Atan_tmp = 3.0f*MATH_PI_OVER_TWO_F - (deg_temp);	
            break;
            default:
                Atan_tmp = 0.0f;
            break;
        }
    }
    
    return Atan_tmp;
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
Ram_Func float Math_Sqrt_F(float A)
{
    if(A > 0.0f)
    {
        float xhalf = 0.5f * A;
        Q32I_ i = *(Q32I_*)&A;
        i = 0x1FBD1DF5 + (i >> 1);
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
