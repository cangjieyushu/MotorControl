/*
*     File Name :                        mc_api
*     Library/Module Name :              mc
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机控制接口
*/


/*-------------------------- 1. 对应头文件--------------------------------*/
#include "mc_api.h"


/*-------------------------- 2. 变量 ---------------------------------*/
#if(MOTOR_CONTROL_MODE == MOTOR_CONTROL_FOC_F)
#include "mcfoc_para_f.h"
static ST_MCFOC_TASK_F* pMC_API[3] = 
{
    &MCFOC_Task_F,
    &MCFOC_Task_F,
    &MCFOC_Task_F
};

#elif(MOTOR_CONTROL_MODE == MOTOR_CONTROL_FOC_T)
#include "mcfoc_para_t.h"
static ST_MCFOC_TASK_T* pMC_API[3] = 
{
    &MCFOC_Task_T,
    &MCFOC_Task_T,
    &MCFOC_Task_T
};

#elif(MOTOR_CONTROL_MODE == MOTOR_CONTROL_SQ)
#include "mcsq_para.h"
static ST_MCSQ_TASK* pMC_API[3] = 
{
    &MCSQ_Task,
    &MCSQ_Task,
    &MCSQ_Task
};

#endif


/*-------------------------- 3. 公有接口实现 -----------------------------*/
void MC_API_Motor_StartStop(Q32U_ motor_num, Q32U_ Enable)
{
    if(Enable == 1U)
    {
        pMC_API[motor_num]->Motor_Flag.bit.motor_enable_flag = 1U;
    }
    else
    {
        pMC_API[motor_num]->Motor_Flag.bit.motor_enable_flag = 0U;
    }
}

Q32U_ MC_API_Motor_Read_State(Q32U_ motor_num)
{
    if(pMC_API[motor_num]->Motor_Flag.bit.motor_running_flag == 1U)
    {
        return 1U;
    }
    else
    {
        return 0U;
    }
}

void MC_API_Motor_Set_Dir(Q32U_ motor_num, Q32U_ Dir)
{
    if(Dir == 1U)
    {
        pMC_API[motor_num]->Motor_Flag.bit.motor_target_dir = 1U;
    }
    else
    {
        pMC_API[motor_num]->Motor_Flag.bit.motor_target_dir = 0U;
    }
}

Q32I_ MC_API_Motor_Read_Dir(Q32U_ motor_num)
{
    if(pMC_API[motor_num]->Motor_Flag.bit.motor_real_dir == 1U)
    {
        return 1U;
    }
    else
    {
        return 0U;
    }
}

void MC_API_Motor_Set_Speed(Q32U_ motor_num, Q32U_ Speed)
{
    Q32U_ Speed_tmp = MATH_SAT_T(MATH_ABS_T((Q32I_)Speed), pMC_API[motor_num]->Motor_API.Max_Speed_rpm, pMC_API[motor_num]->Motor_API.Min_Speed_rpm);
    pMC_API[motor_num]->Motor_API.Target_Speed_pu = Q16I_LFT_14(Speed_tmp)/pMC_API[motor_num]->Motor_API.Max_Speed_rpm;
}

Q32U_ MC_API_Motor_Read_Speed(Q32U_ motor_num)
{
    return Q32I_RHT_14(pMC_API[motor_num]->Motor_API.Real_Speed_pu*pMC_API[motor_num]->Motor_API.Max_Speed_rpm);
}

Q32U_ MC_API_Motor_Read_Iphase(Q32U_ motor_num)
{
    return Q32I_RHT_14(pMC_API[motor_num]->Motor_API.Real_Iphase_pu*pMC_API[motor_num]->Motor_API.Max_Iphase_0p01A);
}

Q32U_ MC_API_Motor_Read_Ibus(Q32U_ motor_num)
{
    return Q32I_RHT_14(pMC_API[motor_num]->Motor_API.Real_Ibus_pu*pMC_API[motor_num]->Motor_API.Max_IBus_0p01A);
}

Q32U_ MC_API_Motor_Read_Err(Q32U_ motor_num)
{
    return pMC_API[motor_num]->Motor_Error.Motor_Error_Flag.all;
}

void MC_API_Motor_Clear_Err(Q32U_ motor_num)
{
    MC_Error_Clear(&pMC_API[motor_num]->Motor_Error);
}
