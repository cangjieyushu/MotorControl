/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef Main_H
#define Main_H

#include <stdint.h>
#include "BSP_ADC.h"
#include "BSP_CLK.h"
#include "BSP_CMP.h"
#include "BSP_GPIO.h"
#include "BSP_ISR.h"
#include "BSP_OPA.h"
#include "BSP_PWM.h"
#include "BSP_TIM.h"
#include "BSP_USART.h"
#include "BSP_WDG.h"

#include "MotorTask.h"
#include "SysTask.h"

#include "Button.h"
#include "Current.h"
#include "Voltage.h"
#include "Error.h"
#include "USART.h"
#include "Speed.h"
#include "Temperature.h"

//JSCOPE_RTT
#define JSCOPE_RTT_EN                   (0U)
#define JSCOPE_RTT_Sytle                "JScope_I4I4I4"
#if(JSCOPE_RTT_EN == 1U)
#include "SEGGER_RTT.h"
#endif

#endif /* Main_H */
