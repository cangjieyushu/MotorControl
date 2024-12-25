/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#ifndef BSP_WDG_H
#define BSP_WDG_H

#include "MotorHal_cfg.h"

#define HAL_WDOG_WIN_WINDOWVALUE (36000U)
#define HAL_WDOG_WIN_TIMEOUTVALUE (400000U)

static inline void Hal_FeedWatchDog(void)
{
    if(WDOG_GetCounter() > HAL_WDOG_WIN_WINDOWVALUE)
    {
        WDOG_Refresh();
    }
}

void BSP_WDG_Init(void);

#endif /* BSP_WDG_H */
