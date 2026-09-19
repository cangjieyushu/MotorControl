/*
*     File Name :                        main
*     Library/Module Name :              main
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             任务管理
*/


#ifndef MAIN_H
#define MAIN_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "sys_task.h"

#if(MOTOR_CONTROL_MODE == MOTOR_CONTROL_FOC_F)
#include "mcfoc_task_f.h"

#elif(MOTOR_CONTROL_MODE == MOTOR_CONTROL_FOC_T)
#include "mcfoc_task_t.h"

#elif(MOTOR_CONTROL_MODE == MOTOR_CONTROL_SQ)
#include "mcsq_task.h"

#endif


/*-------------------------- 2. 宏定义 -----------------------------------*/


/*-------------------------- 3. 枚举/结构体 ------------------------------*/


/*-------------------------- 4. 外部全局变量声明 --------------------------*/


/*-------------------------- 5. 接口函数声明 ------------------------------*/


#endif /* MAIN_H */
