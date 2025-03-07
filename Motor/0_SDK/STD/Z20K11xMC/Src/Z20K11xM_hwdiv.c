/**************************************************************************************************/
/**
 * @file      : Z20K11xM_hwdiv.c
 * @brief     : HWDIV module driver file.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (c) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#include "Z20K11xM_hwdiv.h"

/** @addtogroup  Z20K11X_Peripheral_Driver
 *  @{
 */

/** @defgroup HWDIV HWDIV
 *  @brief HWDIV driver modules
 *  @{
 */

/** @defgroup HWDIV_Private_Type
 *  @{
 */

/** @}end of group HWDIV_Private_Type*/

/** @defgroup HWDIV_Private_Defines
 *  @{
 */

/** @}end of group HWDIV_Private_Defines */

/** @defgroup HWDIV_Private_Variables
 *  @{
 */

/** @}end of group HWDIV_Private_Variables */

/** @defgroup HWDIV_Global_Variables
 *  @{
 */

/** @}end of group HWDIV_Global_Variables */

/** @defgroup HWDIV_Private_FunctionDeclaration
 *  @{
 */

/** @}end of group HWDIV_Private_FunctionDeclaration */

/** @defgroup HWDIV_Private_Functions
 *  @{
 */

/** @} end of group HWDIV_Private_Functions */

/** @defgroup HWDIV_Public_Functions
 *  @{
 */
/**
 * @brief      Initializes the HWDIV
 * @param[in]  none
 *
 *
 * @return
 *         - SUCC: Operation is successful
 *         - BUSY: Operation fails, the module is busy calculating
 */
ResultStatus_t HWDIV_Init(void)
{
    ResultStatus_t ret;

    ret = (hwdivRegPtr->HWDIV_CSR.BUSY != 0U) ? BUSY : SUCC;

    return ret;
}

/**
 * @brief      Enable/disable divided by zero
 * @param[in]  newState: divided by zero enable/disable
 *               -DISABLE: If divisor is 0,the quotient result and remainder are
 *                        forced to 0x0000_0000,else reads of the RES register
 *                        return the register contents.
 *               -ENABLE: If divisor is 0,an attempted read of RES register will
 *                       generate hardfault interrupt,else the register contents
 *                       are returned
 *
 */
void HWDIV_DivZeroCmd(ControlState_t newState)
{
    hwdivRegPtr->HWDIV_CSR.DZE = (uint32_t)newState;
}

/**
 * @brief      Perform the unsigned division with non-blocking call
 * @param[in]  dividend: dividend operand
 * @param[in]  divisor: divisor operand
 *
 * @return
 *         - SUCC: Operation is successful
 *         - BUSY: Operation fails, the module is busy calculating
 */
ResultStatus_t HWDIV_UnsignedDiv(uint32_t dividend, uint32_t divisor)
{
    ResultStatus_t ret;

    if (hwdivRegPtr->HWDIV_CSR.BUSY != 0U)
    {
        ret = BUSY;
    }
    else
    {
        hwdivRegPtr->HWDIV_CSR.USGN = 1U;
        hwdivRegWPtr->HWDIV_DEND = dividend;
        hwdivRegWPtr->HWDIV_DSOR = divisor;

        if (hwdivRegPtr->HWDIV_CSR.DFS == 1U)
        {
            hwdivRegPtr->HWDIV_STRT.STRT = 1U;
        }
        ret = SUCC;
    }

    return ret;
}

/**
 * @brief      Get the result of unsigned division
 * @param[out]  result:  the result of division
 * @param[out]  rem: the remainder of the division
 *
 * @return
 *         - SUCC: Operation is successful
 *         - BUSY: Operation fails, the module is busy calculating
 *         - ERR: Operation fails, the last operation is not a division or
 *                divided by 0
 */
ResultStatus_t HWDIV_GetResultUnsignedDiv(uint32_t *result, uint32_t *rem)
{
    ResultStatus_t ret = SUCC;

    if (hwdivRegPtr->HWDIV_CSR.BUSY != 0U)
    {
        ret = BUSY;
    }
    else
    {
        if (hwdivRegPtr->HWDIV_CSR.DIV != 1U)
        {
            ret = ERR;
        }
        if ((ret == SUCC)&&(hwdivRegPtr->HWDIV_CSR.DZE == 0U))
        {
            if (hwdivRegPtr->HWDIV_CSR.DZ == 1U)
            {
                ret = ERR;
            }
        }
    }

    if (ret == SUCC)
    {
        *result = hwdivRegWPtr->HWDIV_RES;
        *rem = hwdivRegWPtr->HWDIV_REM;
    }

    return ret;
}

/**
 * @brief      Perform the unsigned division with blocking call
 * @param[in]  dividend:  dividend operand
 * @param[in]  divisor: divisor operand
 * @param[out]  result:  the result of division
 * @param[out]  rem: the remainder of the division
 *
 * @return
 *         - SUCC: Operation is successful
 *         - BUSY: Operation fails, the module is busy calculating
 *         - ERR: Operation fails, the operation is not a division or
 *                divided by 0
 */
ResultStatus_t HWDIV_UnsignedDivBlocking(uint32_t dividend, uint32_t divisor,
                                         uint32_t *result, uint32_t *rem)
{
    volatile uint32_t i = 0U;
    ResultStatus_t    ret;

    ret = HWDIV_UnsignedDiv(dividend, divisor);
    if (ret == SUCC)
    {
        while (i < HWDIV_TIMEOUT_WAIT_CNT)
        {
            if (hwdivRegPtr->HWDIV_CSR.BUSY != 1U)
            {
                break;
            }
            i++;
        }
        ret = HWDIV_GetResultUnsignedDiv(result, rem);
    }

    return ret;
}

/**
 * @brief      Perform the signed division with non-blocking call
 * @param[in]  dividend:  dividend operand
 * @param[in]  divisor: divisor operand
 *
 * @return
 *         - SUCC: Operation is successful
 *         - BUSY: Operation fails, the module is busy calculating
 */
ResultStatus_t HWDIV_SignedDiv(int32_t dividend, int32_t divisor)
{
    ResultStatus_t ret;

    if (hwdivRegPtr->HWDIV_CSR.BUSY != 0U)
    {
        ret = BUSY;
    }
    else
    {
        hwdivRegPtr->HWDIV_CSR.USGN = 0U;
        hwdivRegWPtr->HWDIV_DEND = (uint32_t)dividend;
        hwdivRegWPtr->HWDIV_DSOR = (uint32_t)divisor;

        if (hwdivRegPtr->HWDIV_CSR.DFS == 1U)
        {
            hwdivRegPtr->HWDIV_STRT.STRT = 1U;
        }
        ret = SUCC;
    }

    return ret;
}

/**
 * @brief      Get the result of signed division
 * @param[out]  result:  the result of division
 * @param[out]  rem: the remainder of the division
 *
 * @return
 *         - SUCC: Operation is successful
 *         - BUSY: Operation fails, the module is busy calculating
 *         - ERR: Operation fails, the last operation is not a division or
 *                divided by 0
 */
ResultStatus_t HWDIV_GetResultSignedDiv(int32_t *result, int32_t *rem)
{
    ResultStatus_t ret = SUCC;

    if (hwdivRegPtr->HWDIV_CSR.BUSY != 0U)
    {
        ret = BUSY;
    }
    else
    {
        if (hwdivRegPtr->HWDIV_CSR.DIV != 1U)
        {
            ret = ERR;
        }
        if ((ret==SUCC)&&(hwdivRegPtr->HWDIV_CSR.DZE == 0U))
        {
            if (hwdivRegPtr->HWDIV_CSR.DZ == 1U)
            {
                ret = ERR;
            }
        }
    }

    if (ret == SUCC)
    {
        *result = (int32_t)hwdivRegWPtr->HWDIV_RES;
        *rem = (int32_t)hwdivRegWPtr->HWDIV_REM;
    }

    return ret;
}

/**
 * @brief      Perform the signed division with blocking call
 * @param[in]  dividend:  dividend operand
 * @param[in]  divisor: divisor operand
 * @param[out]  result:  the result of division
 * @param[out]  rem: the remainder of the division
 *
 * @return
 *         - SUCC: Operation is successful
 *         - BUSY: Operation fails, the module is busy calculating
 *         - ERR: Operation fails, the operation is not a division or
 *                divided by 0
 */
ResultStatus_t HWDIV_SignedDivBlocking(int32_t dividend, int32_t divisor,
                                       int32_t *result, int32_t *rem)
{
    volatile uint32_t i = 0U;
    ResultStatus_t    ret;

    ret = HWDIV_SignedDiv(dividend, divisor);
    if (ret == SUCC)
    {
        while (i < HWDIV_TIMEOUT_WAIT_CNT)
        {
            if (hwdivRegPtr->HWDIV_CSR.BUSY != 1U)
            {
                break;
            }
            i++;
        }
        ret = HWDIV_GetResultSignedDiv(result, rem);
    }

    return ret;
}

/**
 * @brief      Perform the square root calculation with non-blocking call
 * @param[in]  radicand: the radicand
 *
 * @return
 *         - SUCC: Operation is successful
 *         - BUSY: Operation fails, the module is busy calculating
 */
ResultStatus_t HWDIV_SquareRoot(uint32_t radicand)
{
    ResultStatus_t ret;

    if (hwdivRegPtr->HWDIV_CSR.BUSY != 0U)
    {
        ret = BUSY;
    }
    else
    {
        hwdivRegWPtr->HWDIV_RCND = radicand;
        ret = SUCC;
    }

    return ret;
}

/**
 * @brief      Get the result of the square root calculation
 * @param[out]  result:  the result of square root calculation
 * @param[out]  rem: the remainder of the square root calculation
 *
 * @return
 *         - SUCC: Operation is successful
 *         - BUSY: Operation fails, the module is busy calculating
 *         - ERR: Operation fails, the last operation is not a square root
 *                calculation
 */
ResultStatus_t HWDIV_GetResultSquareRoot(uint32_t *result, uint32_t *rem)
{
    ResultStatus_t ret = SUCC;

    if ((hwdivRegPtr->HWDIV_CSR.BUSY != 0U))
    {
        ret = BUSY;
    }
    else if (hwdivRegPtr->HWDIV_CSR.SQRT != 1U)
    {
        ret = ERR;
    }
    else
    {
        *result = hwdivRegWPtr->HWDIV_RES;
        *rem = hwdivRegWPtr->HWDIV_REM;
    }

    return ret;
}

/**
 * @brief      Perform the square root calculation with blocking call
 * @param[in]   radicand:  the radicand
 * @param[out]  result:  the result of square root calculation
 * @param[out]  rem: the remainder of the square root calculation
 *
 * @return
 *         - SUCC: Operation is successful
 *         - BUSY: Operation fails, the module is busy calculating
 *         - ERR: Operation fails, the operation is not a square root
 *                calculation
 */
ResultStatus_t HWDIV_SquareRootBlocking(uint32_t radicand, uint32_t *result,
                                        uint32_t *rem)
{
    volatile uint32_t i = 0U;
    ResultStatus_t    ret;

    ret = HWDIV_SquareRoot(radicand);
    if (ret == SUCC)
    {
        while (i < HWDIV_TIMEOUT_WAIT_CNT)
        {
            if (hwdivRegPtr->HWDIV_CSR.BUSY != 1U)
            {
                break;
            }
            i++;
        }
        ret = HWDIV_GetResultSquareRoot(result, rem);
    }

    return ret;
}

/**
 * @brief      Disable/Enable the Divider Fast Start Mode
 * @param[in]  disableDivFastStart:
 *                                  - ture: Disable the Fast Start Mode
 *                                  - false: Enable the Fast Start Mode
 * @return
 *         - SUCC: Operation is successful
 *         - BUSY: Operation fails, the module is busy calculating
 */
ResultStatus_t HWDIV_DisableDivFastStart(ControlState_t disableDivFastStart)
{
    ResultStatus_t ret;

    if (hwdivRegPtr->HWDIV_CSR.BUSY != 0U)
    {
        ret = BUSY;
    }
    else
    {
        hwdivRegPtr->HWDIV_CSR.DFS = disableDivFastStart == ENABLE ? 1U : 0U;
        ret = SUCC;
    }

    return ret;
}

/**
 * @brief      Get the HWDIV IP Version
 * @param[out]  version: the version of the IP
 *
 *
 * @return
 *         - SUCC: Operation is successful
 *
 */
ResultStatus_t HWDIV_GetIPVersion(uint32_t *version)
{
    *version = hwdivRegWPtr->HWDIV_VERSION;

    return SUCC;
}

/**
 * @brief      Get the HWDIV IP Params
 * @param[out] param: the Params of the IP
 *
 *
 * @return
 *         - SUCC: Operation is successful
 *
 */
ResultStatus_t HWDIV_GetIPParam(uint32_t *param)
{
    *param = hwdivRegWPtr->HWDIV_PARAM;

    return SUCC;
}

/** @}end of group HWDIV_Public_Functions */

/** @}end of group HWDIV_definitions */

/** @}end of group Z20K11X_Peripheral_Driver */
