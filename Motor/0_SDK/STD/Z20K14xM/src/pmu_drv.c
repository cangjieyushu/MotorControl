/**************************************************************************************************/
/**
 * @file     pmu_drv.c
 * @brief    PMU module driver file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#include "pmu_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
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

#define PMU_UNLOCK   (0x94730000U)                                     /*!< PMU Unlock Key */
/*@} end of group PMU_Private_Defines */

/** @defgroup PMU_Private_Variables
 *  @{
 */
static isr_cb_t * pmuIsrCallback[PMU_INT_ALL]= {NULL,NULL};

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
 * @return     none
 *
 */
void PMU_DriverIRQHandler(void)
{   
    uint32_t intStatus;

    /* get interrupt status */
    intStatus = pmuRegWPtr->PMU_CSR;
    /* only check enabled interrupts */
    intStatus = intStatus & pmuIntMaskStatus;
    /* clear interrupt status */
    if(1U == pmuRegPtr->PMU_LOCK.LOCK)
    {
        pmuRegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    pmuRegWPtr->PMU_CSR = intStatus;
    pmuRegPtr->PMU_LOCK.LOCK = 1U;
    
    /* VDD 5V low voltage warning detect Interrupt */
    if((intStatus & PMU_IntStatusTable[PMU_VDD_LVW_INT]) != 0U)
    {
        if(pmuIsrCallback[PMU_VDD_LVW_INT] != NULL)
        {
             /* call the callback function */
             pmuIsrCallback[PMU_VDD_LVW_INT]();
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
        if(pmuIsrCallback[PMU_VDD_LVD_INT] != NULL)
        {
            /* call the callback function */
            pmuIsrCallback[PMU_VDD_LVD_INT]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
             PMU_IntMask(PMU_VDD_LVD_INT, MASK);
        }
    }
    
    COMMON_DSB();
}
/*@} end of group PMU_Private_Functions */

/** @defgroup PMU_Public_Functions
 *  @{
 */

/**
 * @brief      Clear Isolation status
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
void PMU_IsoClr(void)
{
    if(1U == pmuRegPtr->PMU_LOCK.LOCK)
    {
        pmuRegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    pmuRegPtr->PMU_ISO_CLR.ISO_CLR = 1U;
    pmuRegPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Enable/Disable PMU Relevant Voltage's Function
 *
 * @param[in]  ctrlType: Select the PMU Control type defined in PMU_Ctrl_t
 * @param[in]  cmd:      Enable or Disable
 *
 * @return     none
 *
 */
void PMU_Ctrl(PMU_Ctrl_t ctrlType, ControlState_t cmd)
{
    uint32_t pmuStatusTmp = pmuRegWPtr->PMU_CSR & 0xffffff3fU;
    if(1U == pmuRegPtr->PMU_LOCK.LOCK)
    {
        pmuRegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    if(ENABLE == cmd)
    {
        pmuStatusTmp |= (1UL << (uint32_t)ctrlType);
    }
    else 
    {
        pmuStatusTmp &= (~(1UL << (uint32_t)ctrlType));
    }

    /* Enable LVD under low power mode and active mode, LVD reset function */
    pmuStatusTmp |= 0x0000000BU;
    pmuRegWPtr->PMU_CSR = pmuStatusTmp;
    pmuRegPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Enable/Disable PMU LDO LVD under active mode
 *             It is recommended to keep the LVD detect feature enabled.
 *
 * @param[in]  ldoType: Select the LDO type
 * @param[in]  cmd:     Enable or Disable
 *
 * @return     none
 *
 */
void PMU_LdoLvdEnCtrlInActive(PMU_Ldo_t ldoType, ControlState_t cmd)
{
    if(1U == pmuRegPtr->PMU_LOCK.LOCK)
    {
        pmuRegWPtr->PMU_LOCK = PMU_UNLOCK;
    }

    switch(ldoType)
    {
        case PMU_LDO_CORE:
            pmuRegPtr->PMU_LDO_LVD_CFG.ACT_CORE_LVDE = (uint32_t)cmd;
            break;
        case PMU_LDO_CLOCK:
            pmuRegPtr->PMU_LDO_LVD_CFG.ACT_CLOCK_LVDE = (uint32_t)cmd;
            break;
        case PMU_LDO_AOA:
            pmuRegPtr->PMU_LDO_LVD_CFG.ACT_AOA_LVDE = (uint32_t)cmd;
            break;
        default:
			/*do nothing*/
            break;
    }

    pmuRegPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Enable/Disable PMU LDO LVD under Low Power Function
 *             It is recommended to keep the LVD detect feature enabled in stop mode.
 *
 * @param[in]  ldoType: Select the LDO type
 * @param[in]  cmd:     Enable or Disable
 *
 * @return     none
 *
 */
void PMU_LdoLvdEnCtrlInLowPower(PMU_Ldo_t ldoType, ControlState_t cmd)
{
    if(1U == pmuRegPtr->PMU_LOCK.LOCK)
    {
        pmuRegWPtr->PMU_LOCK = PMU_UNLOCK;
    }

    switch(ldoType)
    {
        case PMU_LDO_CORE:
            pmuRegPtr->PMU_LDO_LVD_CFG.LP_CORE_LVDE = (uint32_t)cmd;
            break;
        case PMU_LDO_CLOCK:
            pmuRegPtr->PMU_LDO_LVD_CFG.LP_CLOCK_LVDE = (uint32_t)cmd;
            break;
        case PMU_LDO_AOA:
            pmuRegPtr->PMU_LDO_LVD_CFG.LP_AOA_LVDE = (uint32_t)cmd;
            break;
        default:
			/*do nothing*/
            break;
    }

    pmuRegPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Enable/Disable PMU Reset when LDO LVD detected Function
 *             It is recommended to keep the reset feature enabled.
 *
 * @param[in]  ldoType: Select the LDO type
 * @param[in]  cmd:     Enable or Disable
 *
 * @return     none
 *
 */
void PMU_LdoLvdResetEnCtrl(PMU_Ldo_t ldoType, ControlState_t cmd)
{
    if(1U == pmuRegPtr->PMU_LOCK.LOCK)
    {
        pmuRegWPtr->PMU_LOCK = PMU_UNLOCK;
    }

    switch(ldoType)
    {
        case PMU_LDO_CORE:
            pmuRegPtr->PMU_LDO_LVD_CFG.LVD_CORE_RE = (uint32_t)cmd;
            break;
        case PMU_LDO_CLOCK:
            pmuRegPtr->PMU_LDO_LVD_CFG.LVD_CLOCK_RE = (uint32_t)cmd;
            break;
        case PMU_LDO_FLASH:
            pmuRegPtr->PMU_LDO_LVD_CFG.LVD_FLASH_RE = (uint32_t)cmd;
            break;
        case PMU_LDO_AOA:
            pmuRegPtr->PMU_LDO_LVD_CFG.LVD_AOA_RE = (uint32_t)cmd;
            break;
        default:
			/*do nothing*/
            break;
    }

    pmuRegPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Pmu Get LVD Status for LDO
 *
 * @param[in]  ldoType: Select the LDO type
 *
 * @return     FlagStatus_t
 *
 */
FlagStatus_t PMU_GetLdoLvdStatus(PMU_Ldo_t ldoType)
{
    FlagStatus_t bitStatus = RESET;
    
    switch(ldoType)
    {
        case PMU_LDO_CORE:
            bitStatus = (bool)pmuRegPtr->PMU_LDO_LVD_STATUS.LVD_CORE_FLAG ? SET : RESET;
            break;
        case PMU_LDO_CLOCK:
            bitStatus = (bool)pmuRegPtr->PMU_LDO_LVD_STATUS.LVD_CLOCK_FLAG ? SET : RESET;
            break;
        case PMU_LDO_FLASH:
            bitStatus = (bool)pmuRegPtr->PMU_LDO_LVD_STATUS.LVD_FLASH_FLAG ? SET : RESET;
            break;
        case PMU_LDO_AOA:
            bitStatus = (bool)pmuRegPtr->PMU_LDO_LVD_STATUS.LVD_AOA_FLAG ? SET : RESET;
            break;
        default:
			/*do nothing*/
            break;
    }

    return bitStatus;
}

/**
 * @brief      Clear Pmu LVD Status for LDO
 *
 * @param[in]  ldoType: Select the LDO type
 *
 * @return     none
 *
 */
void PMU_ClearLdoLvdStatus(PMU_Ldo_t ldoType)
{
    volatile uint32_t status = 0U;

    if(1U == pmuRegPtr->PMU_LOCK.LOCK)
    {
        pmuRegWPtr->PMU_LOCK = PMU_UNLOCK;
    }

    status = pmuRegWPtr->PMU_LDO_LVD_STATUS;
    
    status &= (1UL << (uint32_t)ldoType);

    pmuRegWPtr->PMU_LDO_LVD_STATUS = status;

    pmuRegPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Pmu Get LVD Flag Function
 *
 * @param[in]  intType: Select the low voltage behavior type
 *
 * @return     FlagStatus_t
 *
 */
FlagStatus_t PMU_GetIntStatus(PMU_Int_t intType)
{
    FlagStatus_t bitStatus;
    
    if((pmuRegWPtr->PMU_CSR & PMU_IntStatusTable[intType]) != 0U)
    {
        bitStatus = SET;
    }
    else
    {
        bitStatus = RESET;
    }
    
    return bitStatus;
}

/**
 * @brief      Mask/Unmask the Relevant Interrupt Function
 *
 * @param[in]  intType: Select the interrupt type
 * @param[in]  intMask: UNMASK or MASK
 *
 * @return     none
 *
 */
void PMU_IntMask(PMU_Int_t intType, IntMask_t intMask)
{
    if(1U == pmuRegPtr->PMU_LOCK.LOCK)
    {
        pmuRegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    
    if(UNMASK == intMask)
    {
        pmuRegWPtr->PMU_CSR = pmuRegWPtr->PMU_CSR | PMU_IntMaskTable[intType];
        pmuIntMaskStatus = pmuIntMaskStatus | PMU_IntStatusTable[intType];
    }
    else
    {
        pmuIntMaskStatus = pmuIntMaskStatus & (~PMU_IntStatusTable[intType]);
        pmuRegWPtr->PMU_CSR = pmuRegWPtr->PMU_CSR & (~PMU_IntMaskTable[intType]);
    }
    
    pmuRegPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Clear the Relevant Interrupt Status
 *
 * @param[in]  intType: Select the interrupt type
 *
 * @return     none
 *
 */
void PMU_IntClr(PMU_Int_t intType)
{
    uint32_t IntStatus = PMU_IntStatusTable[intType] | 0xffffff3fU; 
    if(1U == pmuRegPtr->PMU_LOCK.LOCK)
    {
        pmuRegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    pmuRegWPtr->PMU_CSR = pmuRegWPtr->PMU_CSR & IntStatus;
    pmuRegPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Install call back function
 *
 * @param[in]  intType: select the interrupt type
 * @param[in]  cbFun:   pointer to callback function
 *
 * @return     none
 *
 */
void PMU_InstallCallBackFunc(PMU_Int_t intType,isr_cb_t * cbFun)
{
    pmuIsrCallback[intType] = cbFun;
}

/**
 * @brief      Get LPO Clock Ready Status
 *
 * @param[in]  none
 *
 * @return     FlagStatus_t
 *
 */
FlagStatus_t PMU_IsLpoClkReady(void)
{
    FlagStatus_t result;

    result = (FlagStatus_t) pmuRegPtr->PMU_LPO_32K_CFG.LPO_CLK_READY;

    return result;
}

/*@} end of group PMU_Public_Functions */

/*@} end of group PMU_definitions */

/*@} end of group Z20K14XM_Peripheral_Driver */
