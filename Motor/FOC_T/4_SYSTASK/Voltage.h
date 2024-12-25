/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef Voltage_H
#define Voltage_H

#include "BSP.h"
#include "SysTask.h"
#include "User_Pmsm.h"

//电压保护
//保护时间除号后面的时间是任务周期，只需要填除号之前的时间即可
//除32说明该任务32ms执行一次，最小分辨率就是32ms，然后系统会取整
//比如填96，就是96ms触发，填120也是96ms触发，只有填128，才是128ms触发
#define LOW_VOLTAGE_PROTECT_LEVEL_TL        (Q14I_VOLTAGE_MOTOR_TO_PU(10.0f))    //V，过压保护阈值
#define LOW_VOLTAGE_PROTECT_LEVEL_TIME      (1000.0f/16.0f)                      //ms，过压保护时间

#define OVER_VOLTAGE_PROTECT_LEVEL_TL       (Q14I_VOLTAGE_MOTOR_TO_PU(28.0f))    //V，低压保护阈值
#define OVER_VOLTAGE_PROTECT_LEVEL_TIME     (100.0f/16.0f)                       //ms，低压保护时间

typedef struct{
    Q32I_ Q16I_voltage_protect_tl;
    Q32U_ Q16U_voltage_protect_time;
    
    Q32U_ Q16U_voltage_protect_cnt;
}ST_VOLTAGE_PROTECT;

void Voltage_Protect_Flow(ST_SYSTEM_TASK*  pST);
    
#endif /* Voltage_H */
