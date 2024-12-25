/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef Button_H
#define Button_H

#include "BSP.h"
#include "SysTask.h"

//按键模式
#define BUTTON_MODE                     BUTTON_MODE_VR
#define BUTTON_MODE_BUTTON              0                   //按键启动、停止
#define BUTTON_MODE_VR                  1                   //VR启动、停止、调速
#define BUTTON_MODE_BUTTON_VR           2                   //按键启动、停止，VR调速


//BUTTON_MODE_BUTTON

//BUTTON_MODE_VR
#define VR_START_TL                     (Q16I_)(100.0f)             //VR启动阈值
#define VR_STOP_TL                      (Q16I_)(50.0f)              //VR停止阈值

#define VR_MAX_LIMIT                    (Q16I_)(3800.0f)            //VR最大阈值
#define VR_MIN_LIMIT                    (Q16I_)(200.0f)             //VR最小阈值

#define VR_MAX_DUTY                     (Q32I_)(MOTOR_Q14_PU)           //VR最大占空比

//BUTTON_MODE_BUTTON_VR

typedef struct{
    Q32U_ Q16U_vr_start_tl;
    Q32U_ Q16U_vr_stop_tl;
    
    Q32U_ Q16U_vr_max_limit;
    Q32U_ Q16U_vr_min_limit;
    
    Q32U_ Q16U_vr_duty_max;
}ST_BUTTON_CONTROL;

extern ST_BUTTON_CONTROL Button_Ctrl;

void Button_Control(ST_BUTTON_CONTROL* pButton, ST_SYSTEM_TASK*  pST);

#endif /* Button_H */
