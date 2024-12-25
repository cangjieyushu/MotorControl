/**************************************************************************************************/
/**
 * @file      : Linphy_Drv.c
 * @brief     : LINPHY module driver file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 * 
 * @copyright : (C) 2023 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#include "Linphy_Drv.h"

/** @defgroup Private_MacroDefinition
 *  @{
 */
#define LINPHY_SREW_FAST_SHIFT                         ((uint32)1U)
#define LINPHY_SREW_RATE_SHIFT                         ((uint32)2U)
#define LINPHY_ACTION_TO_OVER_TEMP_SHIFT               ((uint32)3U)
#define LINPHY_ACTION_TO_OVER_VOLTAGE_SHIFT            ((uint32)5U)
#define LINPHY_ACTION_TO_UNDER_VOLTAGE_SHIFT           ((uint32)7U)
#define LINPHY_PWRON_SHIFT                             ((uint32)13U)
#define LINPHY_TX_CHANNEL_CTRL_SHIFT                   ((uint32)14U)
#define LINPHY_RX_CHANNEL_CTRL_SHIFT                   ((uint32)16U)
#define LINPHY_PHYMODE_SHIFT                           ((uint32)20U)
   
#define LINPHY_CONTROL_REG_MASK                        ((uint32)0x1800U)
#define LINPHY_CONTROL_REG_DISABLE                     ((uint32)0x102001U)

#define LINPHY_WAKEUP_DET_EN_SHIFT                     ((uint32)31U)
#define LINPHY_WAKEUP_DET_HIGH_THRE_SHIFT              ((uint32)16U)
#define LINPHY_WAKEUP_TO_ACT_SHIFT                     ((uint32)14U)
#define LINPHY_WAKEUP_TO_INT_SHIFT                     ((uint32)13U)
#define LINPHY_WAKEUP_DET_INT_SHIFT                    ((uint32)12U)


#define LINPHY_FILTER_COUNTER_SHIFT                    ((uint32)8U)

#define LINPHY_DOMINAT_DET_INT_SHIFT                   ((uint32)1U)
#define LINPHY_DOMINAT_TO_THRE_SHIFT                   ((uint32)8U)

#define LINPHY_INT_MASK_WKUP                 ((uint32)1U << 12U)
#define LINPHY_INT_MASK_WKUPTO               ((uint32)1U << 13U)
#define LINPHY_INT_MASK_DOMDET               ((uint32)1U << 1U)
   
#define LINPHY_INT_STATUS_WKUP               ((uint32)1U )
#define LINPHY_INT_STATUS_WKUPTO             ((uint32)1U << 1U)
#define LINPHY_INT_STATUS_DOMDET             ((uint32)1U << 2U)

#define LINPHY_INT_STATUS                    (LINPHY_INT_STATUS_WKUP|LINPHY_INT_STATUS_WKUPTO|  \
                                             LINPHY_INT_STATUS_DOMDET)
/** @} end of Private_MacroDefinition */

/** @defgroup Private_TypeDefinition
 *  @{
 */

/** @} end of group Private_TypeDefinition */

/** @defgroup Global_VariableDefinition
 *  @{
 */

/** @} end of group Global_VariableDefinition */

/** @defgroup Private_VariableDefinition
 *  @{
 */
/**
 *  @brief LINPHY ISR callback function pointer array
 */
static Isr_CbFuncType *Linphy_IsrCb[LINPHY_INT_ALL] = {NULL_PTR, NULL_PTR, NULL_PTR};

/**
 *  @brief LINPHY register address
 */
/*PRQA S 0303 ++*/
static Reg_Linphy_BfType *const Linphy_RegBfPtr = (Reg_Linphy_BfType *)LINPHY_BASE_ADDR;
static Reg_Linphy_WType *const Linphy_RegWPtr = (Reg_Linphy_WType *)LINPHY_BASE_ADDR;
/*PRQA S 0303 --*/

static const uint32 Linphy_StatusTable[]=
{
    0x00000001U,       /*!< LINPHY_STATUS_WKUP */
    0x00000002U,       /*!< LINPHY_STATUS_WKUPTO */
    0x00000004U,       /*!< LINPHY_STATUS_DOMDET */
    0x00000008U,       /*!< LINPHY_STATUS_OT */
    0x00000020U,       /*!< LINPHY_STATUS_OV20 */
    0x00000040U,       /*!< LINPHY_STATUS_UN */
    0x0000006FU        /*!< LINPHY_STATUS_ALL */
};

static const uint32 Linphy_InterruptStatusTable[]=
{
    0x00000001U,       /*!< LINPHY_STATUS_WKUP */
    0x00000002U,       /*!< LINPHY_STATUS_WKUPTO */
    0x00000004U,       /*!< LINPHY_STATUS_DOMDET */
    0x00000007U        /*!< LINPHY_STATUS_ALL */
};

/** @} end of group Private_VariableDefinition */

/** @defgroup Private_FunctionDeclaration
 *  @{
 */
static void Linphy_IntHandler(void);
void Linphy_DriverIrqHandler(void);

/** @} end of group Private_FunctionDeclaration */

/** @defgroup Private_FunctionDefinition
 *  @{
 */
/**
 * @brief      LINPHY interrupt handler.
 * @return None.
 */
static void Linphy_IntHandler(void)
{
    uint32 IntStatus;

    /* Read the interrupt status */
    IntStatus = Linphy_RegWPtr->LINPHY_SR;
    
    Linphy_RegWPtr->LINPHY_SR = IntStatus & LINPHY_INT_STATUS;
      
    if(0U != Linphy_RegBfPtr->LINPHY_CFGR0.WKUPIE)
    {
        if((IntStatus & Linphy_StatusTable[LINPHY_STATUS_WKUP]) != 0U)
        {
            if (NULL_PTR != Linphy_IsrCb[LINPHY_INT_WKUP])
            {
                /* call the callback function */
                Linphy_IsrCb[LINPHY_INT_WKUP]();
            }
            /* Disable the interrupt if callback function is not setup */
            else
            {
                Linphy_RegWPtr->LINPHY_CFGR0 &= ~LINPHY_INT_MASK_WKUP;
            }
        }
    }
    
    if(0U != Linphy_RegBfPtr->LINPHY_CFGR0.WKUPTOIE)
    {
        if((IntStatus & Linphy_StatusTable[LINPHY_STATUS_WKUPTO]) != 0U)
        {
            if (NULL_PTR != Linphy_IsrCb[LINPHY_INT_WKUPTO])
            {
                /* call the callback function */
                Linphy_IsrCb[LINPHY_INT_WKUPTO]();
            }
            /* Disable the interrupt if callback function is not setup */
            else
            {
                Linphy_RegWPtr->LINPHY_CFGR0 &= ~LINPHY_INT_MASK_WKUPTO;
            }
        }
    }
    
    if(0U != Linphy_RegBfPtr->LINPHY_CFGR2.DOMDETIE)
    {
        if((IntStatus & Linphy_StatusTable[LINPHY_STATUS_DOMDET]) != 0U)
        {
            if (NULL_PTR != Linphy_IsrCb[LINPHY_INT_DOMDET])
            {
                /* call the callback function */
                Linphy_IsrCb[LINPHY_INT_DOMDET]();
            }
            /* Disable the interrupt if callback function is not setup */
            else
            {
                Linphy_RegWPtr->LINPHY_CFGR2 &= ~LINPHY_INT_MASK_DOMDET;
            }
        }
    }

}

/**
 * @brief  Lin phy interrupt function.
 * @param  None.
 * @return None.
 */
void Linphy_DriverIrqHandler(void)
{
    Linphy_IntHandler();
}

/** @} end of group Private_FunctionDefinition */

/** @defgroup Public_FunctionDefinition
 *  @{
 */
/**
 * @brief      Disable linphy module
 * @param[in]  none
 *
 * @return     none
 */
void Linphy_Disable(void)
{

    Linphy_RegWPtr->LINPHY_CR &= ~LINPHY_CONTROL_REG_DISABLE;

}

/**
 * @brief      LINPHY initialize configuration. The api should be called after other configuration is ok.
 * @param[in]  CfgPtr: pointer to initialize configuration
 *
 * @return     none
 */
void Linphy_InitConfig(Linphy_ConfigType *CfgPtr)
{
    uint32 RegVal;
    
    RegVal = (((uint32)(CfgPtr->ModuleCmd) & 1U)|
              (((uint32)(CfgPtr->SrewMode) & 1U) << LINPHY_SREW_FAST_SHIFT)|
              (((uint32)(CfgPtr->SrewRate) & 1U) << LINPHY_SREW_RATE_SHIFT)|
              (((uint32)(CfgPtr->ActionToOverTemp) & 3U) << LINPHY_ACTION_TO_OVER_TEMP_SHIFT)|
              (((uint32)(CfgPtr->ActionToOverVoltage) & 3U) << LINPHY_ACTION_TO_OVER_VOLTAGE_SHIFT)|
              (((uint32)(CfgPtr->ActionToUnderVoltage) & 3U) << LINPHY_ACTION_TO_UNDER_VOLTAGE_SHIFT)|
              (((uint32)(CfgPtr->PowerOnCmd) & 1U) << LINPHY_PWRON_SHIFT) |
              (((uint32)(CfgPtr->RxChannel) & 3U) << LINPHY_RX_CHANNEL_CTRL_SHIFT) |
              (((uint32)(CfgPtr->TxChannel) & 3U) << LINPHY_TX_CHANNEL_CTRL_SHIFT) |
              (((uint32)(CfgPtr->LinphyMode) & 1U) << LINPHY_PHYMODE_SHIFT));

    Linphy_RegWPtr->LINPHY_CR &= LINPHY_CONTROL_REG_MASK;  
    Linphy_RegWPtr->LINPHY_CR |= RegVal;

}

/**
 * @brief      Get LINPHY status
 * @param[in]  StaType: type of status
 *                    -LINPHY_STATUS_WKUP
 *                    -LINPHY_STATUS_WKUPTO
 *                    -LINPHY_STATUS_DOMDET
 *                    -LINPHY_STATUS_OT
 *                    -LINPHY_STATUS_OV20
 *                    -LINPHY_STATUS_UN
 *                    -LINPHY_STATUS_ALL
 *
 * @return     Common_FlagStatusType:The state value of LINPHY Status register
 * @retval     COMMON_SET: The status bit is set
 * @retval     COMMON_RESET:The status bit is reset
 */
Common_FlagStatusType Linphy_GetStatus(Linphy_StatusType StaType)
{
    Common_FlagStatusType Ret = COMMON_RESET;
    
    Ret = ((Linphy_RegWPtr->LINPHY_SR & Linphy_StatusTable[StaType]) != 0U ) 
           ? COMMON_SET : COMMON_RESET;
      
    return Ret;
    
}

/**
 * @brief      Clear LINPHY interrupt status
 * @param[in]  IntType: type of interrupt. Only the interrupt status can be cleared.
 *                    -LINPHY_INT_WKUP
 *                    -LINPHY_INT_WKUPTO
 *                    -LINPHY_INT_DOMDET
 *                    -LINPHY_INT_ALL
 *
 * @return     none
 */
void Linphy_ClearIntStatus(Linphy_IntType IntType)
{
    Linphy_RegWPtr->LINPHY_SR = Linphy_InterruptStatusTable[IntType];

}

/**
 * @brief      Configure wakeup detection function. The function should be called before module enable.
 * @param[in]  WakeupPtr: configuration pointer of wakeup
 *
 * @return     none
 */
void Linphy_ConfigWakeupDetection(Linphy_WakeupConfigType *WakeupPtr)
{
    uint32 RegValue;
    
    RegValue = ((((uint32)(WakeupPtr->WakeupCmd) & 0x1U) << LINPHY_WAKEUP_DET_EN_SHIFT) |
               (((uint32)(WakeupPtr->HighWakeupDetThre) & 0xFFFU) << LINPHY_WAKEUP_DET_HIGH_THRE_SHIFT) |
               (((uint32)(WakeupPtr->ActionCmd) & 0x3U) << LINPHY_WAKEUP_TO_ACT_SHIFT) |
               (((uint32)(WakeupPtr->WakeupToInterruptCmd) & 0x1U) << LINPHY_WAKEUP_TO_INT_SHIFT) |
               (((uint32)(WakeupPtr->WakeupDetInterruptCmd) & 0x1U) << LINPHY_WAKEUP_DET_INT_SHIFT) |
               ((uint32)(WakeupPtr->LowWakeupDetThre) & 0xFFFU));
    
    Linphy_RegWPtr->LINPHY_CFGR0 = RegValue;
}

/**
 * @brief      Configure filter function. The filter function effects after configuration.
 * @param[in]  FilterPtr: configuration pointer of filter
 *
 * @return     none
 */
void Linphy_ConfigFilter(Linphy_FilterConfigType *FilterPtr)
{
    uint32 RegValue;
    
    RegValue = ((((uint32)(FilterPtr->FilterCounter) & 0x7U) << LINPHY_FILTER_COUNTER_SHIFT) |
               (uint32)(FilterPtr->FilterPeriod));
      
    Linphy_RegWPtr->LINPHY_CFGR1 = RegValue;
}

/**
 * @brief      Configure dominant timeout detection function.
 * @param[in]  ConfigPtr: pointer to dominant timeout detection configuration
 *
 * @return     none
 */
void Linphy_ConfigDominalToDetection(Linphy_DominalConfigType *ConfigPtr)
{
    uint32 RegValue;
    
    RegValue = ((((uint32)(ConfigPtr->DominalToDetInt) & 0x1U) << LINPHY_DOMINAT_DET_INT_SHIFT) |
                ((uint32)(ConfigPtr->DominalToDetCmd) & 0x1U ) |
                (((uint32)(ConfigPtr->DominalToThreshold) & 0xFFFFFFU) << LINPHY_DOMINAT_TO_THRE_SHIFT));
      
    Linphy_RegWPtr->LINPHY_CFGR2 = RegValue;

}

/**
 * @brief      Install call back function.
 * @param[in]  IntId:  Select the interrupt. It is not recommended to select LINPHY_INT_ALL,
 *                     as this parameter has no effect.
 * @param[in]  CbFun:  Pointer to callback function.
 * @return None.
 */
void Linphy_InstallCallbackFunc(Linphy_IntType IntId, Isr_CbFuncType * CbFun)
{
    if(IntId < LINPHY_INT_ALL)
    {
        Linphy_IsrCb[IntId] = CbFun;
    }
    else
    {
        /* Nothing to do */
    }
    
}

/** @} end of group Public_FunctionDefinition */
