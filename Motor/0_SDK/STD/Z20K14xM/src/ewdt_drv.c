/******************************************************************************/
/**
 * @file     ewdt_drv.c
 * @brief    EWDT module driver file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 ******************************************************************************/

#include "ewdt_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @defgroup EWDT
 *  @brief EWDT driver modules
 *  @{
 */

/** @defgroup EWDT_Private_Defines
 *  @{
 */

#define EWDT_CS_INTF_MASK              (0x01000000U)
#define EWDT_CS_INPP_MASK              (0x00000040U)
#define EWDT_CS_INPE_MASK              (0x00000020U)
#define EWDT_CS_INPUT_MASK             (0x00000060U)
#define EWDT_CS_INTE_MASK              (0x00000010U)
#define EWDT_CS_WAITE_MASK             (0x00000004U)
#define EWDT_CS_DEBUGE_MASK            (0x00000002U)
#define EWDT_CS_EWDTE_MASK             (0x00000001U)

#define EWDT_CS_INTF_SHIFT             (24U)
#define EWDT_CS_INPP_SHIFT             (6U)
#define EWDT_CS_INPE_SHIFT             (5U)
#define EWDT_CS_INTE_SHIFT             (4U)
#define EWDT_CS_WAITE_SHIFT            (2U)
#define EWDT_CS_DEBUGE_SHIFT           (1U)

#define EWDT_CS_INPUT_STATUS_SET(x) \
        (((uint32_t)(((uint32_t)(x)) \
          << EWDT_CS_INPE_SHIFT)) & EWDT_CS_INPUT_MASK)
        
#define EWDT_CS_INPP_SET(x) \
        (((uint32_t)(((uint32_t)(x)) \
          << EWDT_CS_INPP_SHIFT)) & EWDT_CS_INPP_MASK)
        
#define EWDT_CS_INPE_SET(x) \
        (((uint32_t)(((uint32_t)(x)) \
          << EWDT_CS_INPE_SHIFT)) & EWDT_CS_INPE_MASK)
        
#define EWDT_CS_INTE_SET(x) \
        (((uint32_t)(((uint32_t)(x)) \
          << EWDT_CS_INTE_SHIFT)) & EWDT_CS_INTE_MASK)
        
#define EWDT_CS_WAITE_SET(x) \
        (((uint32_t)(((uint32_t)(x)) \
          << EWDT_CS_WAITE_SHIFT)) & EWDT_CS_WAITE_MASK)
        
#define EWDT_CS_DEBUGE_SET(x) \
          (((uint32_t)(((uint32_t)(x)) \
            << EWDT_CS_DEBUGE_SHIFT)) & EWDT_CS_DEBUGE_MASK)
        
#define EWDT_CS_EWDTE_SET(x) (((uint32_t)((uint32_t)(x))) & EWDT_CS_EWDTE_MASK)

#define EWDT_REFRESH_VALUE1            (0xB2C5D3A8UL)
#define EWDT_REFRESH_VALUE2            (0x1D7E4C5FUL)

#define EWDT_MASK_CONVERT_ENABLE(x) \
         ((uint32_t)((((uint32_t)(x) + 1U) & 0x1U) << EWDT_CS_INTE_SHIFT))

START_FUNCTION_DECLARATION_RAMSECTION
static void EWDT_REFRESH_COUNT(void)
END_FUNCTION_DECLARATION_RAMSECTION    /* PRQA S 0605*/

/** @} end of group EWDT_Private_Defines */


/** @defgroup EWDT_Private_Type
 *  @{
 */

/** @} end of group EWDT_Private_Type*/



/** @defgroup EWDT_Private_Variables
 *  @{
 */

/**
 *  @brief EWDT Register address array
 */
/*PRQA S 0303 ++*/
static ewdt_reg_t * const ewdtRegPtr = (ewdt_reg_t *)EWDT_BASE_ADDR;
static ewdt_reg_w_t * const ewdtRegWPtr = (ewdt_reg_w_t *)EWDT_BASE_ADDR;
/*PRQA S 0303 --*/
/*! @brief ewdt int status mask array */
static const uint32_t ewdtIntMask[] = 
{
    EWDT_CS_INTE_MASK,
    EWDT_CS_INTE_MASK
};

static const uint32_t ewdtIntFlagMask[] = 
{
    EWDT_CS_INTF_MASK,
    EWDT_CS_INTF_MASK
};

/*! @brief EWDT ISR CallBack VECTOR structure */
static isr_cb_t * ewdtIsrCb[EWDT_INT_ALL] = {NULL};

/** @} end of group EWDT_Private_Variables */

/** @defgroup EWDT_Global_Variables
 *  @{
 */

/** @} end of group EWDT_Global_Variables */

/** @defgroup EWDT_Private_FunctionDeclaration
 *  @{
 */
void EWDT_DriverIRQHandler(void);
/** @} end of group EWDT_Private_FunctionDeclaration */

/** @defgroup EWDT_Private_Functions
 *  @{
 */
static void EWDT_REFRESH_COUNT(void)
{
    COMMON_DISABLE_INTERRUPTS();
    __asm (
        "PUSH  {R0, R1, R2}\n"
        "LDR   R0, =0x40061014\n"
        "LDR   R1, =0xB2C5D3A8\n"
        "LDR   R2, =0x1D7E4C5F\n"

        "STR   R1, [R0]\n"
        "STR   R2, [R0]\n"
        "POP  {R0, R1, R2}\n"
            );
    COMMON_ENABLE_INTERRUPTS();
}

/**
 * @brief      EWDT interrupt handle
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
static void EWDT_IntHandler(void)
{
    ewdt_reg_w_t * eWDTxw = (ewdt_reg_w_t *)(ewdtRegWPtr);
    EWDT_ClearIntStatus(EWDT_INT_OUTPUTASSERT);
    if ((eWDTxw->EWDT_CS & EWDT_CS_INTE_MASK) != 0U)
    {
        if(ewdtIsrCb[EWDT_INT_OUTPUTASSERT] != NULL)
        {
            ewdtIsrCb[EWDT_INT_OUTPUTASSERT]();
        }
    }
    COMMON_DSB();
}

/** @} end of group EWDT_Private_Functions */


/** @defgroup EWDT_Public_Functions
 *  @{
 */

/**
 * @brief      ewdt Initializes Function
 *
 * @param[in]  ptEWDTInitConfig:     Pointer to a EWDT configuration structure.
 *
 * @return Initializes operate flag
 *
 */
ResultStatus_t EWDT_Init(const EWDT_Config_t * ptEWDTInitConfig)
{
    ewdt_reg_w_t * eWDTxw = (ewdt_reg_w_t *)(ewdtRegWPtr);
    uint32_t ewdt_cs = 0U;


    /* Construct CS register new value */
    ewdt_cs = EWDT_CS_INPUT_STATUS_SET(ptEWDTInitConfig->input);
    ewdt_cs |= EWDT_MASK_CONVERT_ENABLE(ptEWDTInitConfig->intMask);
    ewdt_cs |= EWDT_CS_WAITE_SET(ptEWDTInitConfig->wait);
    ewdt_cs |= EWDT_CS_DEBUGE_SET(ptEWDTInitConfig->debug);
    ewdt_cs |= EWDT_CS_EWDTE_SET(ptEWDTInitConfig->enable);

    /* config timeout value and window value */
    eWDTxw->EWDT_COMPH = ptEWDTInitConfig->cmpHighValue;
    eWDTxw->EWDT_COMPL = ptEWDTInitConfig->cmpLowValue;
    
    eWDTxw->EWDT_CS = ewdt_cs;

    return SUCC;
}

/**
 * @brief      refresh ewdt count Function
 *
 * @param[in]  none
 *
 * @return none.
 *
 */
void EWDT_Refresh(void)
{
    EWDT_REFRESH_COUNT();
}

/**
 * @brief      get ewdt input pin assertion config Function
 *
 * @param[in]  none
 *
 * @return     input pin assertion config status.
 *
 */
EWDT_InputStatus_t EWDT_GetInputAssertConfig(void)
{
    ewdt_reg_w_t * eWDTxw = (ewdt_reg_w_t *)(ewdtRegWPtr);
    return ((EWDT_InputStatus_t)
            ((uint32_t)((eWDTxw->EWDT_CS & EWDT_CS_INPUT_MASK) >> 
                                  EWDT_CS_INPE_SHIFT)));
}

/**
 * @brief      get ewdt compare low reg value Function
 *
 * @param[in]  none
 *
 * @return compare low reg value.
 *
 */
uint32_t EWDT_GetCompareLowValue(void)
{
    ewdt_reg_t * eWDTx = (ewdt_reg_t *)(ewdtRegPtr);
    return ((uint32_t)eWDTx->EWDT_COMPL.COMPL);
}

/**
 * @brief      get ewdt compare high reg value Function
 *
 * @param[in]  none
 *
 * @return compare high reg value.
 *
 */
uint32_t EWDT_GetCompareHighValue(void)
{
    ewdt_reg_t * eWDTx = (ewdt_reg_t *)(ewdtRegPtr);
    return ((uint32_t)eWDTx->EWDT_COMPH.COMPH);
}

/**
 * @brief      get ewdt counter current value Function
 *
 * @param[in]  none
 *
 * @return current counter count value.
 *
 */
uint32_t EWDT_GetCounter(void)
{
    ewdt_reg_t * eWDTx = (ewdt_reg_t *)(ewdtRegPtr);
    return ((uint32_t)eWDTx->EWDT_CNT.CNT);
}

/**
 * @brief      get flag indcates ewdt is enable/disable Function
 *
 * @param[in]  none
 *
 * @return     ewdt enable status.
 *
 */
FlagStatus_t EWDT_GetEnableStatus(void)
{
    ewdt_reg_t * eWDTx = (ewdt_reg_t *)(ewdtRegPtr);
    return ((FlagStatus_t)eWDTx->EWDT_CS.EWDTE);
}

/**
 * @brief      get interrupt mask Function
 *
 * @param[in]  intType: int type
 *                      - EWDT_INT_OUTPUTASSERT: ewdt out assert int
 *                      - EWDT_INT_ALL: all int type  
 *
 * @return     interrupt mask.
 *
 */
IntMask_t EWDT_GetIntMaskStatus(EWDT_INT_t intType)
{
    ewdt_reg_w_t * eWDTxw = (ewdt_reg_w_t *)(ewdtRegWPtr);
    return (((eWDTxw->EWDT_CS & ewdtIntMask[intType]) != 0U) ? UNMASK : MASK);
}

/**
 * @brief      clear ewdt interrupt flag Function
 *
 * @param[in]  intType: int type
 *                      - EWDT_INT_OUTPUTASSERT: ewdt out assert int
 *                      - EWDT_INT_ALL: all int type
 *
 * @return none.
 *
 */
void EWDT_ClearIntStatus(EWDT_INT_t intType)
{
    ewdt_reg_w_t * eWDTxw = (ewdt_reg_w_t *)(ewdtRegWPtr);
    uint32_t intStatus = eWDTxw->EWDT_CS;
    intStatus = intStatus | EWDT_CS_INTF_MASK;
    eWDTxw->EWDT_CS = intStatus;
}

/**
 * @brief      get ewdt int flag Function
 *
 * @param[in]  intType: int type
 *                      - EWDT_INT_OUTPUTASSERT: ewdt out assert int
 *                      - EWDT_INT_ALL: all int type
 *
 * @return whether a int is asserted or not.
 *
 */
IntStatus_t EWDT_GetIntStatus(EWDT_INT_t intType)
{
    ewdt_reg_w_t * eWDTxw = (ewdt_reg_w_t *)(ewdtRegWPtr);
    return ((IntStatus_t)((uint32_t)((eWDTxw->EWDT_CS & ewdtIntFlagMask[intType]) 
                                        >> EWDT_CS_INTF_SHIFT)));
}

/**
 * @brief      Install callback function
 *
 * @param[in]  intType: select interrrupt type
 *                      - EWDT_INT_OUTPUTASSERT: ewdt out assert int
 *                      - EWDT_INT_ALL: all int type
 * @param[in]  cbFun: indicate callback function
 *
 * @return    none
 *
 */  
void EWDT_InstallCallBackFunc(EWDT_INT_t intType, isr_cb_t *cbFun)
{
    if(intType < EWDT_INT_ALL)
    {
        ewdtIsrCb[intType] = cbFun;
    }
}

/**
 * @brief  EWDT interrupt function in vector
 *
 * @param  none
 *
 * @return none
 *
 */
void EWDT_DriverIRQHandler(void)
{
    EWDT_IntHandler();
}

/** @} end of group EWDT_Public_Functions */

/** @} end of group EWDT driver modules */

/** @} end of group Z20K14XM_Peripheral_Driver */
