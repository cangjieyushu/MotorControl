/*******************************************************************************/
/**
 * @file     regfile_drv.c
 * @brief    REGFILE module driver file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 *******************************************************************************/

#include "regfile_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @defgroup REGFILE REGFILE
 *  @brief REGFILE driver modules
 *  @{
 */

/** @defgroup REGFILE_Private_Type
 *  @{
 */

/** @}end of group REGFILE_Private_Type*/

/** @defgroup REGFILE_Private_Defines
 *  @{
 */
#define REGFILE_TOTAL_NUMBER        (32U)

/** @}end of group REGFILE_Private_Defines */

/** @defgroup REGFILE_Private_Variables
 *  @{
 */
static regfile_reg_w_t *const regfileRegWPtr = 
                                                (regfile_reg_w_t *)REGFILE_BASE_ADDR;/*PRQA S 0303*/

/** @}end of group REGFILE_Private_Variables */

/** @defgroup REGFILE_Global_Variables
 *  @{
 */

/** @}end of group REGFILE_Global_Variables */

/** @defgroup REGFILE_Private_FunctionDeclaration
 *  @{
 */


/** @}end of group REGFILE_Private_FunctionDeclaration */

/** @defgroup REGFILE_Private_Functions
 *  @{
 */

/** @} end of group REGFILE_Private_Functions */

/** @defgroup REGFILE_Public_Functions
 *  @{
 */

/**
 * @brief      Write into the REGFILE by regID
 * @param[in]  regID: the regID of the regfile, the scope is [0-31]
 * @param[in]  data: the data to be written
 *
 * @return     Write into the REGFILE Status:
 * @retval     SUCC: Operation is successful
 * @retval     ERR:  Operation fails, input param is invalid
 *
 */
ResultStatus_t REGFILE_WriteByRegId(uint8_t regID, uint32_t data)
{
    ResultStatus_t ret = ERR;

    if(regID < REGFILE_TOTAL_NUMBER)
    {
        regfileRegWPtr->REGFILE_REGn[regID] = data;
        ret = SUCC;
    }


    return ret;
}

/**
 * @brief        Read from the REGFILE by regID
 * @param[in]    regID: the regID of the regfile, the scope is [0-31]
 * @param[out]   dataPtr: the data pointer to be stored in
 *
 * @return       Read from the REGFILE Status:
 * @retval       SUCC: Operation is successful
 * @retval       ERR:  Operation fails, input param is invalid
 *
 */
ResultStatus_t REGFILE_ReadByRegId(uint8_t regID, uint32_t *dataPtr)
{
    ResultStatus_t ret = ERR;

    if((regID < REGFILE_TOTAL_NUMBER) && (dataPtr != NULL))
    {
        *dataPtr = regfileRegWPtr->REGFILE_REGn[regID];
        ret = SUCC;
    }

    return ret;
}

/** @}end of group REGFILE_Public_Functions */

/** @}end of group REGFILE_definitions */

/** @}end of group Z20K14XM_Peripheral_Driver */
