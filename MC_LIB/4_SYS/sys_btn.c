/**
 * @file    sys_btn.c
 * @brief   按键 / VR 控制
 * @author  CJYS
 * @date    2024/1/1
 */

/* ======================== 1. Header ======================= */
#include "sys_btn.h"
#include "sys_task.h"

/* ======================== 2. Defines ====================== */

/* ======================== 3. Typedefs ===================== */

/* ======================== 4. Globals ====================== */
ST_BUTTON_CONTROL Button_Ctrl = {
    .vr_start_tl   = VR_START_TL,
    .vr_stop_tl    = VR_STOP_TL,

    .vr_max_limit  = VR_MAX_LIMIT,
    .vr_min_limit  = VR_MIN_LIMIT,

    .vr_duty_max   = VR_MAX_DUTY,
};

/* ======================== 5. Function Prototypes ========== */

#if ((HW_FUN_BTN_MODE == HW_FUN_BTN_MODE_DB) || (HW_FUN_BTN_MODE == BUTTON_MODE_BUTTON_VR))
/**
 * @brief  按键启停状态更新
 * @param  pButton  按键控制结构体指针
 */
static void Button_UpdateState(ST_BUTTON_CONTROL* pButton)
{
    /* ---- 读取按键电平 ---- */
    pButton->button0_state = BSP_SYS_GPIO_Read_START_State();   /* 启动键 */
    pButton->button1_state = BSP_SYS_GPIO_Read_STOP_State();    /* 停止键 */

    /* ---- 停止状态：检测"启动"按下（下降沿）---- */
    if (Systask.System_State_Flag.bit.system_runflag == 0U)
    {
        if (pButton->button0_state == 0U && pButton->button0_state_last == 1U)
        {
            Systask.System_State_Flag.bit.system_runflag = 1U;
        }
    }
    /* ---- 运行状态：检测"停止"按下（下降沿）---- */
    else
    {
        if (pButton->button1_state == 0U && pButton->button1_state_last == 1U)
        {
            Systask.System_State_Flag.bit.system_runflag = 0U;
        }
    }

    /* ---- 保存本次电平，供下次比较 ---- */
    pButton->button0_state_last = pButton->button0_state;
    pButton->button1_state_last = pButton->button1_state;
}
#endif

#if ((HW_FUN_BTN_MODE == HW_FUN_BTN_MODE_VR) || (HW_FUN_BTN_MODE == HW_FUN_BTN_MODE_DB_VR))
/**
 * @brief  VR 值映射为占空比
 * @param  pButton  按键控制结构体指针
 * @param  vr_val   VR 采样值
 * @return 映射后的占空比
 */
static Q32U_ Button_VrToDuty(const ST_BUTTON_CONTROL* pButton, Q32U_ vr_val)
{
    Q32U_ range;

    /* ---- 1. 上下限钳位 ---- */
    if (vr_val > pButton->vr_max_limit)
    {
        vr_val = pButton->vr_max_limit;
    }
    else if (vr_val < pButton->vr_min_limit)
    {
        vr_val = pButton->vr_min_limit;
    }

    /* ---- 2. 线性映射，保护除零 ---- */
    range = pButton->vr_max_limit - pButton->vr_min_limit;
    if (range == 0U)
    {
        return 0U;      /* 阈值范围非法，返回 0 */
    }

    return (Q32U_)((pButton->vr_duty_max * (vr_val - pButton->vr_min_limit)) / range);
}
#endif

/* ======================== 6. Functions ==================== */

/**
 * @brief  按键 / VR 控制入口
 * @param  pButton  按键控制结构体指针
 */
void Button_Control(ST_BUTTON_CONTROL* pButton)
{
#if (HW_FUN_BTN_MODE == HW_FUN_BTN_MODE_DB)

    /* ========== 纯按键模式：启停 + 占空比固定为最大值 ========== */
    Button_UpdateState(pButton);
    Systask.Q16U_Duty_Target = pButton->vr_duty_max;

#elif (HW_FUN_BTN_MODE == HW_FUN_BTN_MODE_VR)

    /* ========== 纯 VR 模式：VR 控制启停 + 调速 ========== */
    {
        Q32U_ vr_val = (Q32U_)Systask.FL_VR.O_Q14I_LPF_Out;

        /* ---- 启停判断（VR 阈值）---- */
        if (vr_val > pButton->vr_start_tl)
        {
            Systask.System_State_Flag.bit.system_runflag = 1U;
        }
        else if (vr_val < pButton->vr_stop_tl)
        {
            Systask.System_State_Flag.bit.system_runflag = 0U;
        }

        /* ---- 占空比映射 ---- */
        Systask.Q16U_Duty_Target = Button_VrToDuty(pButton, vr_val);
    }

#elif (HW_FUN_BTN_MODE == HW_FUN_BTN_MODE_DB_VR)

    /* ========== 组合模式：按键启停 + VR 调速 ========== */
    {
        Q32U_ vr_val;

        Button_UpdateState(pButton);

        vr_val = (Q32U_)Systask.FL_VR.Q14I_LPF_Out;
        Systask.Q16U_Duty_Target = Button_VrToDuty(pButton, vr_val);
    }

#else
    /* 无有效模式：不做任何处理 */
    (void)pButton;

#endif
}
