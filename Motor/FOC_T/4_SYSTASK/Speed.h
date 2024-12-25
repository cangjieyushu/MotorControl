/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef Speed_H
#define Speed_H

#include "BSP.h"
#include "SysTask.h"
#include "User_Pmsm.h"
#include "MotorTask.h"

//速度保护
//保护时间除号后面的时间是任务周期，只需要填除号之前的时间即可
//除32说明该任务32ms执行一次，最小分辨率就是32ms，然后系统会取整
//比如填96，就是96ms触发，填120也是96ms触发，只有填128，才是128ms触发
#define OVER_SPEED_PROTECT_LEVEL_TL         (Q14I_SRAD_MOTOR_TO_PU(60000.0f))
#define OVER_SPEED_PROTECT_LEVEL_TIME       (1000.0f/64.0f)

#define LOW_SPEED_PROTECT_LEVEL_TL          (Q14I_SRAD_MOTOR_TO_PU(10.0f))
#define LOW_SPEED_PROTECT_LEVEL_TIME        (1000.0f/64.0f)

typedef struct{
    Q32I_ Q16I_speed_protect_tl;
    Q32U_ Q16U_speed_protect_time;
    
    Q32U_ Q16U_speed_protect_cnt;
}ST_SPEED_PROTECT;

void Speed_Protect_Flow(ST_SYSTEM_TASK*  pST);
    
#endif /* Speed_H */
