/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef Current_H
#define Current_H

#include "BSP.h"
#include "SysTask.h"
#include "User_Pmsm.h"
#include "MotorTask.h"

//电流保护
//保护时间除号后面的时间是任务周期，只需要填除号之前的时间即可
//除32说明该任务32ms执行一次，最小分辨率就是32ms，然后系统会取整
//比如填96，就是96ms触发，填120也是96ms触发，只有填128，才是128ms触发
#define CURRENT_PROTECT_LEVEL           3                                   //过流保护档位

#define CURRENT_PROTECT_LEVEL_1_TL      (Q14I_CURRENT_MOTOR_TO_PU(30.0f))   //A，过流保护阈值
#define CURRENT_PROTECT_LEVEL_1_TIME    ( 100.0f /32.0f)                    //ms，过流保护时间

#define CURRENT_PROTECT_LEVEL_2_TL      (Q14I_CURRENT_MOTOR_TO_PU(35.0f))   //A，过流保护阈值
#define CURRENT_PROTECT_LEVEL_2_TIME    ( 1000.0f /32.0f)                   //ms，过流保护时间

#define CURRENT_PROTECT_LEVEL_3_TL      (Q14I_CURRENT_MOTOR_TO_PU(40.0f))   //A，过流保护阈值
#define CURRENT_PROTECT_LEVEL_3_TIME    ( 10000.0f /32.0f)                   //ms，过流保护时间

typedef struct{
    Q32U_ Q16U_current_protect_tl;
    Q32U_ Q16U_current_protect_time;
    
    Q32U_ Q16U_current_protect_cnt;
}ST_CURRENT_PROTECT;

void Current_Protect_Flow(ST_SYSTEM_TASK*  pST);
    
#endif /* Current_H */
