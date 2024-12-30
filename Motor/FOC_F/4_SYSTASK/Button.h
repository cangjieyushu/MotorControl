/**************************************************************************************************
*     File Name :                        Button.h
*     Library/Module Name :              SysTask
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             按键控制头文件
**************************************************************************************************/
#ifndef Button_H
#define Button_H

#include "SysTask.h"


//按键模式
#define BUTTON_MODE                     BUTTON_MODE_VR
#define BUTTON_MODE_BUTTON              0                   //按键启动、停止
#define BUTTON_MODE_VR                  1                   //VR启动、停止、调速
#define BUTTON_MODE_BUTTON_VR           2                   //按键启动、停止，VR调速


//BUTTON_MODE_BUTTON

//BUTTON_MODE_VR
#define VR_START_TL                     (100.0f)                    //VR启动阈值
#define VR_STOP_TL                      (50.0f)                     //VR停止阈值

#define VR_MAX_LIMIT                    (3800.0f)                   //VR最大阈值
#define VR_MIN_LIMIT                    (200.0f)                    //VR最小阈值

//BUTTON_MODE_BUTTON_VR

typedef struct{
    float F_vr_start_tl;
    float F_vr_stop_tl;
    
    float F_vr_max_limit;
    float F_vr_min_limit;
}ST_BUTTON_CONTROL;

extern ST_BUTTON_CONTROL Button_Ctrl;

/**********************************************************************************************
Function: Button_Control
Description: 按键逻辑控制
Input: 无
Output: 无
Input_Output: 按键控制指针，系统状态指针
Return: 无
Author: CJYS
***********************************************************************************************/
void Button_Control(ST_BUTTON_CONTROL* pButton, ST_SYSTEM_TASK*  pST);

#endif /* Button_H */
