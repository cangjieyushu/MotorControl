/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/

#include "BSP_WDG.h"

void BSP_WDG_Init(void)
{
    RCC_Enable_LSI();//Enable LSI
    while (RCC_Get_LSIRDY() != 1){;}
                          
    IWDG_Enable_WriteAccess(IWDG);
    IWDG_Set_Prescaler(IWDG,IWDGPrescaler);
    IWDG_Set_ReloadCounter(IWDG,ReloadCounter);
    while (IWDG_Is_Ready(IWDG) != 1){;}
    IWDG_Reload_Counter(IWDG);
    IWDG_Enable(IWDG); 
}
