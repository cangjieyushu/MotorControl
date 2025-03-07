/**************************************************************************************************/
/** 
 * @file      : Z20A8300A_Init.h
 * @brief     : Z20A8300A Init Header File.
 *              - Platform : Z20K11xM
 * @version   : V0.1
 * @date      : 2022-08-15
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @Copyright : Copyright (C) 2022 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
#ifndef Z20A8300A_INIT_H
#define Z20A8300A_INIT_H

/** @addtogroup Z20A8300A_Driver
 *  @{
 */

/** @addtogroup Z20A8300A_Init
 *  @brief Z20A8300A Initialization API.
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "Z20A8300A_Spi.h"
#include "Z20A8300A_Hal.h"

/** @defgroup Init_Public_MacroDefinition
 *  @{
 */

/** @} end of Init_Public_MacroDefinition */

/** @defgroup Init_Public_TypeDefinition
 *  @{
 */

/** @} end of group Init_Public_TypeDefinition */

/** @defgroup Init_Global_VariableDeclaration
 *  @{
 */

extern Z20A8300A_IfType Z20A8300AIf1;

/** @} end of group Global_VariableDeclaration */

/** @defgroup Public_FunctionDeclaration
 *  @{
 */

/**
 * @brief       Z20A8300A Init
 *
 * @param[in]   none
 *
 * @return      uint32_t
 * @retval      1: success
 * @retval      0: failture
 *
 */
uint32_t Z20A8300A_Init(void);

/** @} end of group Init_Public_FunctionDefinition */

#ifdef __cplusplus
}
#endif

/** @} end of group Z20A8300A_Init */

/** @} end of group Z20A8300A_Driver */

#endif /* Z20A8300A_INIT_H */
