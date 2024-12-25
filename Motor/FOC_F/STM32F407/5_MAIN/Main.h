/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef Main_H
#define Main_H

#include "BSP.h"

#include "MotorPara.h"
#include "MotorTask.h"
#include "SysTask.h"

//#include "Button.h"
//#include "Current.h"
//#include "Voltage.h"
//#include "Error.h"
//#include "USART.h"
//#include "Speed.h"
//#include "Temperature.h"


#define BIT0    0x0001U
#define BIT1    0x0002U
#define BIT2    0x0004U
#define BIT3    0x0008U
#define BIT4    0x0010U
#define BIT5    0x0020U
#define BIT6    0x0040U
#define BIT7    0x0080U

//JSCOPE_RTT模式使能标志位
#define JSCOPE_RTT_EN                   (1U)
#define JSCOPE_RTT_Sytle                "JScope_f4f4f4"
#if(JSCOPE_RTT_EN == 1U)
#include "SEGGER_RTT.h"
#endif

#endif /* Main_H */
