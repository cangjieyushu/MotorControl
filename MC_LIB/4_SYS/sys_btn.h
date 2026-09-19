/*
*     File Name :                        sys_btn
*     Library/Module Name :              sys
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             按键控制
*/


#ifndef SYS_BTN_H
#define SYS_BTN_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "math_type.h"
#include "sys_task.h"


/*-------------------------- 2. 宏定义 -----------------------------------*/
//按键模式
#define BUTTON_MODE                     BUTTON_MODE_VR 
#define BUTTON_MODE_BUTTON              0                   //按键启动、停止
#define BUTTON_MODE_VR                  1                   //VR启动、停止、调速
#define BUTTON_MODE_BUTTON_VR           2                   //按键启动、停止，VR调速


//BUTTON_MODE_BUTTON


//BUTTON_MODE_VR
#define VR_START_TL                     ((Q32U_)(100.0f))               //VR启动阈值
#define VR_STOP_TL                      ((Q32U_)(50.0f))                //VR停止阈值

#define VR_MAX_LIMIT                    ((Q32U_)(3800.0f))              //VR最大阈值
#define VR_MIN_LIMIT                    ((Q32U_)(200.0f))               //VR最小阈值

#define VR_MAX_DUTY                     (Q14U_MAX_T)                    //VR最大占空比


//BUTTON_MODE_BUTTON_VR


/*-------------------------- 3. 枚举/结构体 ------------------------------*/
typedef struct{
    Q32U_       Q16U_vr_start_tl;
    Q32U_       Q16U_vr_stop_tl;
    
    Q32U_       Q16U_vr_max_limit;
    Q32U_       Q16U_vr_min_limit;
    
    Q32U_       Q16U_vr_duty_max;
    
    Q32U_       Button0_State;
    Q32U_       Button0_State_Last;
    Q32U_       Button1_State;
    Q32U_       Button1_State_Last;
    Q32U_       Button2_State;
    Q32U_       Button2_State_Last;
}ST_BUTTON_CONTROL;


/*-------------------------- 4. 外部全局变量声明 --------------------------*/
extern ST_BUTTON_CONTROL Button_Ctrl;


/*-------------------------- 5. 接口函数声明 ------------------------------*/
/*
Function: Button_Control
Description: 按键逻辑控制
Input: 无
Output: 无
Input_Output: 按键控制指针，系统状态指针
Return: 无
Author: CJYS
*/
void Button_Control(ST_BUTTON_CONTROL* pButton, ST_SYSTEM_TASK*  pST);


#endif /* SYS_BTN_H */
