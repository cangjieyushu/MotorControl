/**************************************************************************************************
*     File Name :                        Main.h
*     Library/Module Name :              Main
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             任务管理
**************************************************************************************************/

#ifndef Main_H
#define Main_H


#include "Z20A8300A_Init.h"
#include "SYS.h"


//JSCOPE_RTT模式使能标志位
#define JSCOPE_RTT_EN                   (0U)
#define JSCOPE_RTT_Sytle                "JScope_I4I4I4"
#if(JSCOPE_RTT_EN == 1U)
#include "SEGGER_RTT.h"
#endif


void IRQHandleDMAIsr(void);
void IRQHandleMCBKIsr(void);
void IRQHandleSTIMIsr(void);


#endif /* Main_H */
