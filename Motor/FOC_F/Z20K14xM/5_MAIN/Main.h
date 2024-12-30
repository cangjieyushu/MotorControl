/**************************************************************************************************
*     File Name :                        Main.h
*     Library/Module Name :              Main
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             任务管理
**************************************************************************************************/
#ifndef Main_H
#define Main_H

#include "Math.h"
#include "BSP.h"
#include "SYS.h"

#include "MotorTask.h"
#include "SysTask.h"
#include "Z20A8300A_Init.h"

#include "USART.h"

#define BIT0    0x0001U
#define BIT1    0x0002U
#define BIT2    0x0004U
#define BIT3    0x0008U
#define BIT4    0x0010U
#define BIT5    0x0020U
#define BIT6    0x0040U
#define BIT7    0x0080U

//JSCOPE_RTT模式使能标志位
#define JSCOPE_RTT_EN                   (0U)
#define JSCOPE_RTT_Sytle                "JScope_f4f4f4"
#if(JSCOPE_RTT_EN == 1U)
#include "SEGGER_RTT.h"
#endif

void IRQHandleDMAIsr(void);
void IRQHandleMCBKIsr(void);
void IRQHandleSTIMIsr(void);

#endif /* Main_H */
