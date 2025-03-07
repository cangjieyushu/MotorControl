/**************************************************************************************************/
/**
 * @file      : Z20K11xM_regfile.h
 * @brief     : REGFILE module header file.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (c) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#ifndef Z20K11XM_REGFILE_H
#define Z20K11XM_REGFILE_H

#include "Z20K11xM_drv.h"

/** @addtogroup  Z20K11X_Peripheral_Driver
 *  @{
 */

/** @addtogroup  REGFILE
 *  @{
 */

/** @defgroup REGFILE_Public_Types
 *  @{
 */

/** @}end of group REGFILE_Public_Types */

/** @defgroup REGFILE_Public_Constants
 *  @{
 */

/** @}end of group REGFILE_Public_Constants */

/** @defgroup REGFILE_Public_Macro
 *  @{
 */

/** @}end of group REGFILE_Public_Macro */

/** @defgroup REGFILE_Public_FunctionDeclaration
 *  @brief REGFILE functions declaration
 *  @{
 */

/**
 * @brief      Write into the REGFILE by regID
 * @param[in]  regID: the regID of the regfile, the scope is [0-31]
 * @param[in]  data: the data to be written
 *
 * @return Write into the REGFILE Status:
 *         - SUCC: Operation is successful
 *         - ERR:  Operation fails, input param is invalid
 *
 */
ResultStatus_t REGFILE_WriteByRegID(uint8_t regID, uint32_t const * data);

/**
 * @brief        Read from the REGFILE by regID
 * @param[in]    regID: the regID of the regfile, the scope is [0-31]
 * @param[inout] data: the data to be read
 *
 *
 * @return Read from the REGFILE Status:
 *         - SUCC: Operation is successful
 *         - ERR:  Operation fails, input param is invalid
 *
 */
ResultStatus_t REGFILE_ReadByRegID(uint8_t regID, uint32_t *data);

/** @}end of group REGFILE_Public_FunctionDeclaration */

/** @}end of group REGFILE  */

/** @}end of group Z20K11X_Peripheral_Driver */

#endif /* Z20K11XM_REGFILE_H */
