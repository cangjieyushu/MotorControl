/**************************************************************************************************/
/**
 * @file      : Z20K11xM_hwdiv.h
 * @brief     : HWDIV driver module header file.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (c) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#ifndef Z20K11XM_HWDIV_H
#define Z20K11XM_HWDIV_H

#include <stdbool.h>
#include "Z20K11xM_drv.h"

/** @addtogroup  Z20K11X_Peripheral_Driver
 *  @{
 */

/** @addtogroup  HWDIV
 *  @{
 */

/** @defgroup HWDIV_Private_Defines
 *  @{
 */
#define HWDIV_TIMEOUT_CNT (100U)
/** @}end of group HWDIV_Private_Defines */
/** @defgroup HWDIV_Private_Variables
 *  @{
 */
/**
 *  @brief HWDIV address array
 */
/*PRQA S 0303 ++*/
static hwdiv_reg_w_t *const hwdivRegWPtr = (hwdiv_reg_w_t *)HWDIV_BASE_ADDR;
static hwdiv_reg_t *const   hwdivRegPtr = (hwdiv_reg_t *)HWDIV_BASE_ADDR;
/*PRQA S 0303 --*/
/** @}end of group HWDIV_Private_Variables */
/** @defgroup HWDIV_Public_Types
 *  @{
 */

/** @}end of group HWDIV_Public_Types */

/** @defgroup HWDIV_Public_Constants
 *  @{
 */

/** @}end of group HWDIV_Public_Constants */

/** @defgroup HWDIV_Private_Func
 *  @{
 */
/**
 * @brief      Perform the square root calculation
 *             Note: Ensure input is valid
 * @param[in]  radicand: the radicand
 * @param[out]  result_addr:  the result of square root calculation
 * @param[out]  remainder_addr: the remainder of the square root calculation
 *
 * @return
 *         - SUCC: Operation is successful
 *         - ERR: Operation fails
 */

static inline ResultStatus_t HWDIV_SqrtFast(uint32_t radicand,
              uint32_t *result_addr,uint32_t *remainder_addr)            
{
   volatile uint32_t i = 0U;                                            
    ResultStatus_t    ret = ERR;                                         
    hwdivRegWPtr->HWDIV_RCND = (uint32_t)(radicand);                     
    while (i < HWDIV_TIMEOUT_CNT)                                        
    {                                                                    
        if (hwdivRegPtr->HWDIV_CSR.BUSY != 1U)                           
        {                                                                
            ret = SUCC;                                                  
            break;                                                       
        }                                                                
        i++;                                                             
    }                                                                    
    *(result_addr) = (uint32_t)hwdivRegWPtr->HWDIV_RES;                  
    *(remainder_addr) = (uint32_t)hwdivRegWPtr->HWDIV_REM;    
    return ret;
}
/**
 * @brief      Perform the fast unsigned division
 *             Note: Ensure input is valid
 * @param[in]  dividend:  dividend operand
 * @param[in]  divisor: divisor operand
 * @param[out]  result_addr:  the result of division
 * @param[out]  remainder_addr: the remainder of the division
 *
 * @return
 *         - SUCC: Operation is successful
 *         - ERR: Operation fails
 */
static inline ResultStatus_t HWDIV_UnsignedDivFast(uint32_t dividend,
              uint32_t divisor,uint32_t *result_addr,uint32_t *remainder_addr)  
{  
    volatile uint32_t i = 0U;                                            
    ResultStatus_t    ret = ERR;                                         
    hwdivRegPtr->HWDIV_CSR.USGN = 1U;                                    
    hwdivRegWPtr->HWDIV_DEND = (uint32_t)(dividend);                     
    hwdivRegWPtr->HWDIV_DSOR = (uint32_t)(divisor);                      
    hwdivRegPtr->HWDIV_STRT.STRT =                                       
        (hwdivRegPtr->HWDIV_CSR.DFS == 1U) ? 1U : 0U;                    
    while (i < HWDIV_TIMEOUT_CNT)                                        
    {                                                                    
        if (hwdivRegPtr->HWDIV_CSR.BUSY != 1U)                           
        {                                                                
            ret = SUCC;                                                  
            break;                                                       
        }                                                                
        i++;                                                             
    }                                                                    
    *(result_addr) = (uint32_t)hwdivRegWPtr->HWDIV_RES;                  
    *(remainder_addr) = (uint32_t)hwdivRegWPtr->HWDIV_REM;   
    return ret;
}
/**
 * @brief      Perform the fast signed division
 *             Note: Ensure input is valid
 * @param[in]  dividend:  dividend operand
 * @param[in]  divisor: divisor operand
 * @param[out]  result_addr:  the result of division
 * @param[out]  remainder_addr: the remainder of the division
 *
 * @return
 *         - SUCC: Operation is successful
 *         - ERR: Operation fails
 */
static inline ResultStatus_t HWDIV_SignedDivFast(int32_t dividend,
              int32_t divisor, int32_t *result_addr,int32_t *remainder_addr)   
{   
    volatile uint32_t i = 0U;                                            
    ResultStatus_t    ret = ERR;                                         
    while (i < HWDIV_TIMEOUT_CNT)                                        
    {                                                                    
        if (hwdivRegPtr->HWDIV_CSR.BUSY != 1U)                           
        {                                                                
            ret = SUCC;                                                  
            break;                                                       
        }                                                                
        i++;                                                             
    }                                                                    
    i = 0U;                                                              
    ret = ERR;                                                          
    hwdivRegPtr->HWDIV_CSR.USGN = 0U;                                    
    hwdivRegWPtr->HWDIV_DEND = (uint32_t)(dividend);                     
    hwdivRegWPtr->HWDIV_DSOR = (uint32_t)(divisor);                      
    hwdivRegPtr->HWDIV_STRT.STRT =                                       
        (hwdivRegPtr->HWDIV_CSR.DFS == 1U) ? 1U : 0U;                    
    while (i < HWDIV_TIMEOUT_CNT)                                        
    {                                                                    
        if (hwdivRegPtr->HWDIV_CSR.BUSY != 1U)                           
        {                                                                
            ret = SUCC;                                                  
            break;                                                       
        }                                                                
        i++;                                                             
    }                                                                    
    *(result_addr) = (int32_t)hwdivRegWPtr->HWDIV_RES;                   
    *(remainder_addr) = (int32_t)hwdivRegWPtr->HWDIV_REM;  
    return ret;
}

/** @}end of group HWDIV_Private_Func */

/** @defgroup HWDIV_Public_FunctionDeclaration
 *  @brief HWDIV functions declaration
 *  @{
 */

/**
 * @brief      Initializes the HWDIV
 * @param[in]  none
 *
 * @return
 *         - SUCC: Operation is successful
 *         - BUSY: Operation fails, the module is busy calculating
 */
ResultStatus_t HWDIV_Init(void);

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
void HWDIV_DivZeroCmd(ControlState_t newState);

/**
 * @brief      Perform the unsigned division with non-blocking call
 * @param[in]  dividend: dividend operand
 * @param[in]  divisor: divisor operand
 *
 * @return
 *         - SUCC: Operation is successful
 *         - BUSY: Operation fails, the module is busy calculating
 */
ResultStatus_t HWDIV_UnsignedDiv(uint32_t dividend, uint32_t divisor);

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
ResultStatus_t HWDIV_GetResultUnsignedDiv(uint32_t *result,
                                          uint32_t *rem);

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
                                         uint32_t *result, uint32_t *rem);

/**
 * @brief      Perform the signed division with non-blocking call
 * @param[in]  dividend:  dividend operand
 * @param[in]  divisor: divisor operand
 *
 * @return
 *         - SUCC: Operation is successful
 *         - BUSY: Operation fails, the module is busy calculating
 */
ResultStatus_t HWDIV_SignedDiv(int32_t dividend, int32_t divisor);

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
ResultStatus_t HWDIV_GetResultSignedDiv(int32_t *result, int32_t *rem);

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
                                       int32_t *result, int32_t *rem);

/**
 * @brief      Perform the square root calculation with non-blocking call
 * @param[in]  radicand: the radicand
 *
 * @return
 *         - SUCC: Operation is successful
 *         - BUSY: Operation fails, the module is busy calculating
 */
ResultStatus_t HWDIV_SquareRoot(uint32_t radicand);

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
ResultStatus_t HWDIV_GetResultSquareRoot(uint32_t *result, uint32_t *rem);

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
                                        uint32_t *rem);
/**
 * @brief      Disable/Enable the Divider Fast Start Mode
 * @param[in]  disableDivFastStart:
 *                                  - ture: Disable the Fast Start Mode
 *                                  - false: Enable the Fast Start Mode
 * @return
 *         - SUCC: Operation is successful
 *         - BUSY: Operation fails, the module is busy calculating
 */
ResultStatus_t HWDIV_DisableDivFastStart(ControlState_t disableDivFastStart);

/**
 * @brief      Get the HWDIV IP Version
 * @param[out]  version: the version of the IP
 *
 *
 * @return
 *         - SUCC: Operation is successful
 *
 */
ResultStatus_t HWDIV_GetIPVersion(uint32_t *version);
/**
 * @brief      Get the HWDIV IP Params
 * @param[out] param: the Params of the IP
 *
 *
 * @return
 *         - SUCC: Operation is successful
 *
 */
ResultStatus_t HWDIV_GetIPParam(uint32_t *param);

/** @}end of group HWDIV_Public_FunctionDeclaration */

/** @}end of group HWDIV  */

/** @}end of group Z20K11X_Peripheral_Driver */

#endif /* Z20K11XM_HWDIV_H */
