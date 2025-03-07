/**************************************************************************************************/
/**
 * @file      : Z20K11xM_pmu.c
 * @brief     : PMU module driver file.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (c) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#include "Z20K11xM_pmu.h"

/** @addtogroup  Z20K11X_Peripheral_Driver
 *  @{
 */

/** @defgroup PMU
 *  @brief PMU driver modules
 *  @{
 */

/** @defgroup PMU_Private_Type
 *  @{
 */

/*@} end of group PMU_Private_Type*/

/** @defgroup PMU_Private_Defines
 *  @{
 */
/*PRQA S 0303 ++ */
static pmu_reg_t *const pmuRegPtr = (pmu_reg_t *) PMU_BASE_ADDR;       /*!< PMU Register */
static pmu_reg_w_t *const pmuRegWPtr = (pmu_reg_w_t *) PMU_BASE_ADDR;  /*!< PMU word Register */
/*PRQA S 0303 -- */

#define PMU_UNLOCK   (0x94730000U)
/*@} end of group PMU_Private_Defines */

/** @defgroup PMU_Private_Variables
 *  @{
 */
static isr_cb_t * pmuIsrCb[PMU_INT_ALL]= {NULL,NULL};

static const uint32_t PMU_IntStatusTable[] = 
{
    0x00000040U,        /*PMU_VDD_LVW_INT status mask*/
    0x00000080U,        /*PMU_VDD_LVD_INT status mask*/
    0x000000C0U         /*PMU_INT_ALL status mask*/
};

static const uint32_t PMU_IntMaskTable[] = 
{
    0x00000020U,        /*PMU_VDD_LVW_INT enable mask*/
    0x00000004U,        /*PMU_VDD_LVD_INT enable mask*/
    0x00000024U         /*PMU_INT_ALL enable mask*/
};

/* The bit6/bit7 are for LVW/LVD int status with w1c attributes*/
static uint32_t pmuIntMaskStatus = 0xffffff3fU;

/*@} end of group PMU_Private_Variables */

/** @defgroup PMU_Global_Variables
 *  @{
 */

/*@} end of group PMU_Global_Variables */

/** @defgroup PMU_Private_FunctionDeclaration
 *  @{
 */
 
void PMU_DriverIRQHandler(void);

/*@} end of group PMU_Private_FunctionDeclaration */

/** @defgroup PMU_Private_Functions
 *  @{
 */

/**
 * @brief      PMU IRQHandler
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void PMU_DriverIRQHandler(void)
{   
    uint32_t intStatus;

    /* get interrupt status */
    intStatus = pmuRegWPtr->PMU_VDD5V_CSR;
    /* only check enabled interrupts */
    intStatus = intStatus & pmuIntMaskStatus;
    /* clear interrupt status */
    pmuRegWPtr->PMU_VDD5V_CSR = intStatus;

    /* VDD 5V low voltage warning detect Interrupt */
    if((intStatus & PMU_IntStatusTable[PMU_VDD_LVW_INT]) != 0U)
    {
        if(pmuIsrCb[PMU_VDD_LVW_INT] != NULL)
        {
         /* call the callback function */
             pmuIsrCb[PMU_VDD_LVW_INT]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            PMU_IntMask(PMU_VDD_LVW_INT, MASK);
        }
    }

    /* VDDA low voltage detect Interrupt */
    if((intStatus & PMU_IntStatusTable[PMU_VDD_LVD_INT]) != 0U)
    {
        if(pmuIsrCb[PMU_VDD_LVD_INT] != NULL)
        {
            /* call the callback function */
            pmuIsrCb[PMU_VDD_LVD_INT]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
             PMU_IntMask(PMU_VDD_LVD_INT, MASK);
        }
    }
}
/*@} end of group PMU_Private_Functions */

/** @defgroup PMU_Public_Functions
 *  @{
 */
 
/**
 * @brief       Clear Isolation status
 *
 * @return none
 *
 */
void PMU_IsoClr(void)
{
    pmuRegWPtr->PMU_LOCK = PMU_UNLOCK;
    pmuRegPtr->PMU_ISO_CLR.ISO_CLR = 1;
    pmuRegPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief       Enable/Disable PMU Relevant Voltage's Function
 *
 * @param[in]  ctrlType:     Select the PMU Control type defined in PMU_Ctrl_t.
 * @param[in]  cmd:          Enable or Disable.
 *
 * @return none
 *
 */
void PMU_Ctrl(PMU_Ctrl_t ctrlType, ControlState_t cmd)
{
    pmuRegWPtr->PMU_LOCK = PMU_UNLOCK;
    switch(ctrlType)
    {
        case PMU_VDD_LVD_LP:
            pmuRegPtr->PMU_VDD5V_CSR.VDD_LVD_LP_EN = (uint32_t)cmd;
            break;
        case PMU_VDD_LVD_ACT:
            pmuRegPtr->PMU_VDD5V_CSR.VDD_LVD_ACT_EN = (uint32_t)cmd;
            break;
        case PMU_VDD_LVD_RE:
            pmuRegPtr->PMU_VDD5V_CSR.VDD_LVD_RE = (uint32_t)cmd;
            break;
        case PMU_VDD_LVW:
            pmuRegPtr->PMU_VDD5V_CSR.VDD_LVW_EN = (uint32_t)cmd;
            break;
        case PMU_REF_BUF_1V:
            pmuRegPtr->PMU_VDD5V_CSR.REF_BUF_1V_EN = (uint32_t)cmd;
            break;
        default:
            /*Do nothing*/
            break;
    }
    pmuRegPtr->PMU_LOCK.LOCK = 1U;

    return;
}

/**
 * @brief       Pmu Get Status Function
 *
 * @param[in]  intType:    Int Type.
 *
 * @return     status.
 *
 */
FlagStatus_t PMU_GetIntStatus(PMU_Int_t intType)
{
    FlagStatus_t bitStatus;
    
    pmuRegWPtr->PMU_LOCK = PMU_UNLOCK;
    
    if((pmuRegWPtr->PMU_VDD5V_CSR & PMU_IntStatusTable[intType]) != 0U)
    {
        bitStatus = SET;
    }
    else
    {
        bitStatus = RESET;
    }
    
    pmuRegPtr->PMU_LOCK.LOCK = 1U;
    return bitStatus;
}

/**
 * @brief       Mask/Unmask the Relevant Interrupt Function
 *
 * @param[in]  intType:      Select the interrupt type.
 * @param[in]  intMask:          UNMASK or MASK.
 *
 * @return none
 *
 */
void PMU_IntMask(PMU_Int_t intType, IntMask_t intMask)
{
    pmuRegWPtr->PMU_LOCK = PMU_UNLOCK;
    
    if(UNMASK == intMask)
    {
        pmuRegWPtr->PMU_VDD5V_CSR = pmuRegWPtr->PMU_VDD5V_CSR | PMU_IntMaskTable[intType];
        pmuIntMaskStatus = pmuIntMaskStatus | PMU_IntStatusTable[intType];
    }
    else
    {
        pmuRegWPtr->PMU_VDD5V_CSR = pmuRegWPtr->PMU_VDD5V_CSR & (~PMU_IntMaskTable[intType]);
        pmuIntMaskStatus = pmuIntMaskStatus & (~PMU_IntStatusTable[intType]);
    }
    
    pmuRegPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief       Clear the Relevant Interrupt Status
 *
 * @param[in]  intType:      Select the interrupt type.
 *
 * @return none
 *
 */
void PMU_IntClr(PMU_Int_t intType)
{
    pmuRegWPtr->PMU_LOCK = PMU_UNLOCK;
    pmuRegWPtr->PMU_VDD5V_CSR = pmuRegWPtr->PMU_VDD5V_CSR | PMU_IntStatusTable[intType];
    pmuRegPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      install call back function
 *
 * @param[in]  intId: select the interrupt type
 * @param[in]  cbFun: pointer to callback function
 *
 * @return none
 *
 */
void PMU_InstallCallBackFunc(PMU_Int_t intType,isr_cb_t * cbFun)
{
    pmuIsrCb[intType] = cbFun;
}


/*@} end of group PMU_Public_Functions */

/*@} end of group PMU_definitions */

/*@} end of group Z20K11X_Peripheral_Driver */
