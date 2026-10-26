/**
 * @file    mc_api.c
 * @brief   电机控制对外 API 接口实现
 * @author  CJYS
 * @date    2024/1/1
 *
 * 依据 HW_FUN_MC_MOTOR_CONTROL_MODE 选择 FOC_F / FOC_T / SQ 对应的
 * 任务结构体指针数组，统一操作底层 Motor_Flag / Motor_API。
 */

/* ======================== 1. Header ======================= */
#include "mc_api.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */
#if (HW_FUN_MC_MOTOR_CONTROL_MODE == HW_FUN_MC_MOTOR_CONTROL_FOC_F)
#include "mcfoc_para_f.h"

static ST_MCFOC_TASK_F* pMC_API[3] =
{
    &MCFOC_Task_F,
    &MCFOC_Task_F,
    &MCFOC_Task_F
};

#elif (HW_FUN_MC_MOTOR_CONTROL_MODE == HW_FUN_MC_MOTOR_CONTROL_FOC_T)
#include "mcfoc_para_t.h"

static ST_MCFOC_TASK_T* pMC_API[3] =
{
    &MCFOC_Task_T,
    &MCFOC_Task_T,
    &MCFOC_Task_T
};

#elif (HW_FUN_MC_MOTOR_CONTROL_MODE == HW_FUN_MC_MOTOR_CONTROL_SQ)
#include "mcsq_para.h"

static ST_MCSQ_TASK* pMC_API[3] =
{
    &MCSQ_Task,
    &MCSQ_Task,
    &MCSQ_Task
};

#endif

/* ======================== 5. Function Prototypes ========== */

/* ======================== 6. Functions ==================== */

/**
 * @brief  电机启停控制
 * @param  motor_num  电机编号
 * @param  Enable     1 = 使能，0 = 停止
 */
void MC_API_Motor_StartStop(Q32U_ motor_num, Q32U_ Enable)
{
    if (Enable == 1U)
    {
        pMC_API[motor_num]->Motor_Flag.bit.motor_enable_flag = 1U;
    }
    else
    {
        pMC_API[motor_num]->Motor_Flag.bit.motor_enable_flag = 0U;
    }
}

/**
 * @brief  读取电机运行状态
 * @param  motor_num  电机编号
 * @return 1 = 运行中，0 = 停止
 */
Q32U_ MC_API_Motor_Read_State(Q32U_ motor_num)
{
    if (pMC_API[motor_num]->Motor_Flag.bit.motor_running_flag == 1U)
    {
        return 1U;
    }
    else
    {
        return 0U;
    }
}

/**
 * @brief  设置目标方向
 * @param  motor_num  电机编号
 * @param  Dir        1 = 正转，0 = 反转
 */
void MC_API_Motor_Set_Dir(Q32U_ motor_num, Q32U_ Dir)
{
    if (Dir == 1U)
    {
        pMC_API[motor_num]->Motor_Flag.bit.motor_target_dir = 1U;
    }
    else
    {
        pMC_API[motor_num]->Motor_Flag.bit.motor_target_dir = 0U;
    }
}

/**
 * @brief  读取实际方向
 * @param  motor_num  电机编号
 * @return 1 = 正转，0 = 反转
 */
Q32I_ MC_API_Motor_Read_Dir(Q32U_ motor_num)
{
    if (pMC_API[motor_num]->Motor_Flag.bit.motor_real_dir == 1U)
    {
        return 1U;
    }
    else
    {
        return 0U;
    }
}

/**
 * @brief  设置目标转速（额定范围内的百分比指令）
 * @param  motor_num  电机编号
 * @param  Speed      目标转速指令
 */
void MC_API_Motor_Set_Speed(Q32U_ motor_num, Q32U_ Speed)
{
    Q32U_ Speed_tmp = MATH_SAT_T(MATH_ABS_T((Q32I_)Speed), pMC_API[motor_num]->Motor_API.Max_Speed_rpm, pMC_API[motor_num]->Motor_API.Min_Speed_rpm);

    pMC_API[motor_num]->Motor_API.Target_Speed_pu = Q16I_LFT_14(Speed_tmp) / pMC_API[motor_num]->Motor_API.Max_Speed_rpm;
}

/**
 * @brief  读取实际转速
 * @param  motor_num  电机编号
 * @return 实际转速（rpm）
 */
Q32U_ MC_API_Motor_Read_Speed(Q32U_ motor_num)
{
    return Q32I_RHT_14(pMC_API[motor_num]->Motor_API.Real_Speed_pu * pMC_API[motor_num]->Motor_API.Max_Speed_rpm);
}

/**
 * @brief  读取相电流有效值
 * @param  motor_num  电机编号
 * @return 相电流（0.01A）
 */
Q32U_ MC_API_Motor_Read_Iphase(Q32U_ motor_num)
{
    return Q32I_RHT_14(pMC_API[motor_num]->Motor_API.Real_Iphase_pu * pMC_API[motor_num]->Motor_API.Max_Iphase_0p01A);
}

/**
 * @brief  读取母线电流
 * @param  motor_num  电机编号
 * @return 母线电流（0.01A）
 */
Q32U_ MC_API_Motor_Read_Ibus(Q32U_ motor_num)
{
    return Q32I_RHT_14(pMC_API[motor_num]->Motor_API.Real_Ibus_pu * pMC_API[motor_num]->Motor_API.Max_IBus_0p01A);
}

/**
 * @brief  读取故障标志整体
 * @param  motor_num  电机编号
 * @return 故障位图
 */
Q32U_ MC_API_Motor_Read_Err(Q32U_ motor_num)
{
    return pMC_API[motor_num]->Motor_Error.Motor_Error_Flag.all;
}

/**
 * @brief  清除可复位故障
 * @param  motor_num  电机编号
 */
void MC_API_Motor_Clear_Err(Q32U_ motor_num)
{
    MC_Error_Clear(&pMC_API[motor_num]->Motor_Error);
}

