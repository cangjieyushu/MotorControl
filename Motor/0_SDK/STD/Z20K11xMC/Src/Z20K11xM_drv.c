/**************************************************************************************************/
/**
 * @file      : Z20K11xM_drv.c
 * @brief     : Common driver file.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (c) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#include "Z20K11xM_drv.h"

/** @addtogroup  Z20K11X_Peripheral_Driver
 *  @{
 */

/** @defgroup DRV_COMMON
 *  @brief Z20K11X driver common functions
 *  @{
 */

/** @defgroup DRV_Private_Type
 *  @{
 */


/** @} end of group DRV_Private_Type*/

/** @defgroup DRV_Private_Defines
 *  @{
 */


/** @} end of group DRV_Private_Defines */


/** @defgroup DRV_Private_Variables
 *  @{
 */

                                  
  		      
/** @} end of group DRV_Private_Variables */

/** @defgroup DRV_Global_Variables
 *  @{
 */
  


/** @} end of group DRV_Global_Variables */


/** @defgroup DRV_Private_FunctionDeclaration
 *  @{
 */


/** @} end of group DRV_Private_FunctionDeclaration */

/** @defgroup DRV_Private_Functions
 *  @{
 */


/** @} end of group DRV_Private_Functions */

/** @defgroup DRV_Public_Functions
 *  @{
 */
 


#ifdef  DEBUG
/**
* @brief		Reports the name of the source file and the source line number
* 				where the CHECK_PARAM error has occurred.

* @param[in]	file: Pointer to the source file name
* @param[in]    line: assert_param error line source number

* @return	none
 */
void check_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */     /*PRQA S 2053*/

    /* Infinite loop */
    while(1);
}
#endif /* DEBUG */

/**
 * @brief      Delay for some cycles
 *
 * @param[in]  delayCount: the cycles to delay
 *
 * @return     None
 *
 */
void Drv_Delay(uint32_t delayCount)    /*PRQA S 3408*/
{
    volatile uint32_t cnt = 0U;

    while(cnt++ < delayCount)
    {
    }
}

/** @} end of group DRV_Public_Functions */

/** @} end of group DRV_COMMON */

/** @} end of group Z20K11X_Peripheral_Driver */
