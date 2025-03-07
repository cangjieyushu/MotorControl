/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/

#include "BSP_ADC.h"
#include "BSP_CLK.h"
#include "BSP_DMA.h"
#include "BSP_GPIO.h"
#include "BSP_ISR.h"
#include "BSP_PWM.h"
#include "BSP_TIM.h"
#include "BSP_TMU.h"
#include "BSP_USART.h"
#include "BSP_WDG.h"

#if(HAL_CURRENT_SAMPLE_MODE == HAL_THREE_SHUNT)
#define BSP_ADC_Init                    BSP_ADC_Init_Three_Shunt
#define BSP_PWM_Init                    BSP_PWM_Init_Three_Shunt
#define MH_ADC_FIFO_Read                MH_ADC_FIFO_Read_Three
#elif(HAL_CURRENT_SAMPLE_MODE == HAL_ONE_SHUNT)
#define BSP_ADC_Init                    BSP_ADC_Init_One_Shunt
#define BSP_PWM_Init                    BSP_PWM_Init_One_Shunt
#define MH_ADC_FIFO_Read                MH_ADC_FIFO_Read_One
#endif
