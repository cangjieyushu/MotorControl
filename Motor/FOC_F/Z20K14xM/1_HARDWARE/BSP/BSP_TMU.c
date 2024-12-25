/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#include "BSP_TMU.h"

void BSP_TMU_Init(void)
{
    TMU_SetUnlockForModule(TMU_MODULE_TDG0_TRIG_IN);
    TMU_SetSourceForModule(TMU_SOURCE_MCPWM1_INIT_TRIG0, TMU_MODULE_TDG0_TRIG_IN);
    TMU_ModuleCmd(TMU_MODULE_TDG0_TRIG_IN, ENABLE);
    TMU_SetLockForModule(TMU_MODULE_TDG0_TRIG_IN);
}
