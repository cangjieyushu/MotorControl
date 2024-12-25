/**************************************************************************************************/
/**
 * @file      : Pmu_Drv.c
 * @brief     : Pmu module driver file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#include "Pmu_Drv.h"

/** @defgroup Private_MacroDefinition
 *  @{
 */
 
#define PMU_UNLOCK      (0x94730000U)
#define PMU_INT_COUNT   (6U)
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
 
/*PRQA S 0303 ++ */
static Reg_Pmu_BfType *const Pmu_RegBPtr = (Reg_Pmu_BfType *) PMU_BASE_ADDR;  /*!< PMU Register */
static Reg_Pmu_WType *const Pmu_RegWPtr = (Reg_Pmu_WType *) PMU_BASE_ADDR;   /*!< PMU word Register */
/*PRQA S 0303 -- */

static Isr_CbFuncType * Pmu_IsrCallback[PMU_INT_COUNT] = \
{NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR, NULL_PTR};

static const uint32 Pmu_IntMaskTable[] = 
{
    0x00000020U,          /*!< PMU wakeup timer interrupt */
    0x00000100U,          /*!< PMU high voltage monitor interrupt */
    0x00000200U,          /*!< PMU VDDEXT_FAIL: PMU vdd exit under voltage */
    0x00000200U,          /*!< PMU VDDEXT_FAIL: PMU vdd exit over voltage */
    0x00000200U,          /*!< PMU VDDEXT_FAIL: PMU vdd exit over loading */
    0x00000200U,          /*!< PMU VDDEXT_FAIL: PMU vdd short exit */
};

static const uint32 Pmu_IntStatusTable[] = 
{
    0x00020000U,          /*!< PMU wakeup timer interrupt */
    0x00000200U,          /*!< PMU high voltage monitor interrupt */
    0x00000004U,          /*!< PMU VDDEXT_FAIL: PMU vdd exit under voltage */
    0x00000004U,          /*!< PMU VDDEXT_FAIL: PMU vdd exit over voltage */
    0x00000004U,          /*!< PMU VDDEXT_FAIL: PMU vdd exit over loading */
    0x00000004U,          /*!< PMU VDDEXT_FAIL: PMU vdd short exit */
};

static uint32 Pmu_IntMaskStatusTable[] =
{
    0xfffdf7ffU,          /*!< PMU wakeup timer interrupt */
    0xfffffdffU,          /*!< PMU high voltage monitor interrupt */
    0x00000000U,          /*!< PMU VDDEXT_FAIL: PMU vdd exit under voltage */
    0x00000000U,          /*!< PMU VDDEXT_FAIL: PMU vdd exit over voltage */
    0x00000000U,          /*!< PMU VDDEXT_FAIL: PMU vdd exit over loading */
    0x00000000U,          /*!< PMU VDDEXT_FAIL: PMU vdd short exit */
};
/** @} end of group Private_VariableDefinition */

/** @defgroup Private_FunctionDeclaration
 *  @{
 */
 
/** @} end of group Private_FunctionDeclaration */

/** @defgroup Private_FunctionDefinition
 *  @{
 */
 
/** @} end of group Private_FunctionDefinition */

/** @defgroup Public_FunctionDefinition
 *  @{
 */

/**
 * @brief      Get LPO Clock Ready Status.
 *
 * @param[in]  None
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_RESET: LPO clock is not ready.
 * @retval     COMMON_SET: LPO clock is ready.
 *
 */
Common_FlagStatusType Pmu_GetLpoClockReadyStatus(void)
{
    Common_FlagStatusType Status;

    Status = (Common_FlagStatusType)Pmu_RegBPtr->PMU_LPO_96K_CFG.LPO_CLK_READY;

    return Status;
}

/**
 * @brief      Enable/Disable LPO Clock.
 *
 * @param[in]  Cmd: Enable or Disable.
 *               - COMMON_DISABLE: enable LPO Clock.
 *               - COMMON_ENABLE: disable LPO Clock.
 *
 * @return     None
 *
 */
void Pmu_DisableLpoClock(Common_ControlStateType Cmd)
{
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    Pmu_RegBPtr->PMU_LPO_96K_CFG.LPO_CLK_DIS = (uint32)Cmd;
    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Clear Isolation status.
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void Pmu_ClearIsoStatus(void)
{
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    Pmu_RegBPtr->PMU_ISO_CLR.ISO_CLR = 1U;
    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      PMU control function.
 *
 * @param[in]  CtrlType: Select the PMU Control type defined in Pmu_CtrlType.
 * @param[in]  Cmd: Enable or Disable.
 *               - COMMON_DISABLE: Disable.
 *               - COMMON_ENABLE: Enable.
 *
 * @return     None
 *
 */
void Pmu_Ctrl(Pmu_CtrlType CtrlType, Common_ControlStateType Cmd)
{
    uint32 PmuStatusTmp = Pmu_RegWPtr->PMU_CSR & 0xfffdf7ffU;
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }

    if(COMMON_ENABLE == Cmd)
    {
        PmuStatusTmp |= (1UL << (uint32)CtrlType);
    }
    else
    {
        PmuStatusTmp &= (~(1UL << (uint32)CtrlType));
    }
    Pmu_RegWPtr->PMU_CSR = PmuStatusTmp;
    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Pmu get varef comparator output status.
 *
 * @param[in]  None
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_RESET: Vddp voltage is higher than vddvaref voltage.
 * @retval     COMMON_SET: Vddp voltage is lower than vddvaref voltage.
 *
 */
Common_FlagStatusType Pmu_GetVarefCmpStatus(void)
{
    Common_FlagStatusType Status = COMMON_RESET;
    Status = Pmu_RegBPtr->PMU_CSR.VAREF_COMP_FLG != 0U ? COMMON_SET : COMMON_RESET;
    return Status;
}

/**
 * @brief      Pmu clear varef comparator output status.
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void Pmu_ClearVarefCmpStatus(void)
{
    uint32 PmuStatusTmp = Pmu_RegWPtr->PMU_CSR & 0xfffdffffU;
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    Pmu_RegWPtr->PMU_CSR = PmuStatusTmp;
    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Pmu get LDO ready status.
 *
 * @param[in]  LdoType: Select the PMU LDO type defined in Pmu_LdoType.
 *             Note: Only PMU LDO_VDDEXT and LDO_VDDVAREF is supported.
 *               - PMU_LDO_VDDEXT: PMU LDO_VDDEXT
 *               - PMU_LDO_VDDVAREF: PMU LDO_VDDVAREF
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_RESET: LDO is not ready.
 * @retval     COMMON_SET: LDO is ready.
 *
 */
Common_FlagStatusType Pmu_GetLdoReadyStatus(Pmu_LdoType LdoType)
{
    Common_FlagStatusType Status = COMMON_RESET;
    
    switch(LdoType)
    {
        case PMU_LDO_VDDEXT:
            Status = Pmu_RegBPtr->PMU_CSR.VDDEXT_RDY_FLG != 0U ? COMMON_SET : COMMON_RESET;
            break;
        case PMU_LDO_VDDVAREF:
            Status = Pmu_RegBPtr->PMU_CSR.VAREF_RDY_FLG != 0U ? COMMON_SET : COMMON_RESET;
            break;
        default:
            /*do nothing*/
            break;  
    }

    return Status;
}

/**
 * @brief      PMU high voltage monitor configuration function.
 *
 * @param[in]  HvMonCfgType: HVMON configuration type defined in Pmu_HvMonCfgType.
 * @param[in]  Cmd: Enable or Disable.
 *               - COMMON_DISABLE: Disable.
 *               - COMMON_ENABLE: Enable.
 *
 * @return     None
 *
 */
void Pmu_ConfigHvMon(Pmu_HvMonCfgType HvMonCfgType, Common_ControlStateType Cmd)
{
    uint32 HvMonCfgTmp = Pmu_RegWPtr->PMU_HV_MON_CFG & 0xfffffdffU;
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    if(COMMON_ENABLE == Cmd)
    {
        HvMonCfgTmp |= (1UL << (uint32)HvMonCfgType);
    }
    else
    {
        HvMonCfgTmp &= (~(1UL << (uint32)HvMonCfgType));
    }
    Pmu_RegWPtr->PMU_HV_MON_CFG = HvMonCfgTmp;
    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      PMU high voltage monitor filter window select function.
 *
 * @param[in]  FilterWindowValue: Filter window value.
 *               - PMU_HVMON_FILTER_WINDOW_20US: HVMON filter window as 20us. 
 *               - PMU_HVMON_FILTER_WINDOW_40US: HVMON filter window as 40us.
 *
 * @return     None
 *
 */
void Pmu_SelectHvMonFilterWindow(Pmu_HvmonFilterWindowType FilterWindowValue)
{
    uint32 HvMonCfgTmp = Pmu_RegWPtr->PMU_HV_MON_CFG & 0xfffffdffU;
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    if(PMU_HVMON_FILTER_WINDOW_20US == FilterWindowValue)
    {
        HvMonCfgTmp &= (~(1U << 7U));
    }
    else
    {
        HvMonCfgTmp |= (1U << 7U);
    }
    Pmu_RegWPtr->PMU_HV_MON_CFG = HvMonCfgTmp;
    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      PMU cyclic counter configuration function
 *
 * @param[in]  CycCntType: Cyclic counter type defined in Pmu_CycCntType.
 * @param[in]  CntValue: Cyclic counter value.
 *
 * @return     None
 *
 */
void Pmu_ConfigCycCnt(Pmu_CycCntType CycCntType, uint8 CntValue)
{
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    switch(CycCntType)
    {
        case PMU_CYCLIC_DEAD_CNT:
            Pmu_RegBPtr->PMU_CYCLIC_CNT.CYCLIC_DEAD_CNT = (uint8)CntValue;
            break;
        case PMU_CYCLIC_SENSE_CNT:
            Pmu_RegBPtr->PMU_CYCLIC_CNT.CYCLIC_SENSE_CNT = (uint8)CntValue;
            break; 
        default:
            /*do nothing*/
            break;
    }
    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      PMU wakeup counter configuration function
 *
 * @param[in]  WkupCntType: Wakeup counter type defined in Pmu_WkupCntType.
 * @param[in]  CntValue: Wakeup counter value.
 *
 * @return     None
 *
 */
void Pmu_ConfigWkupCnt(Pmu_WkupCntType WkupCntType, uint8 CntValue)
{
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    switch(WkupCntType)
    {
        case PMU_AUTO_WKUP_CNT:
            Pmu_RegBPtr->PMU_WKUP_CNT.AUTO_WKUP_CNT = (uint8)CntValue;
            break;
        case PMU_NORMAL_WKUP_CNT:
            Pmu_RegBPtr->PMU_WKUP_CNT.NORMAL_WKUP_CNT = (uint8)CntValue;
            break; 
        default:
            /*do nothing*/
            break;
    }
    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      PMU LDO config function.
 *
 * @param[in]  CfgType: Select PMU configuration type defined in Pmu_LdoCfgType.
 * @param[in]  Cmd: Enable or Disable.
 *               - COMMON_DISABLE: Disable.
 *               - COMMON_ENABLE: Enable.
 *
 * @return     None
 *
 */
void Pmu_ConfigLdo(Pmu_LdoCfgType CfgType, Common_ControlStateType Cmd)
{
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    Pmu_RegBPtr->PMU_LDO_CFG.LOCK = 0U;
    switch(CfgType)
    {
        case PMU_LDO_VDDC_EN:
            Pmu_RegBPtr->PMU_LDO_CFG.LDO_VDDC_EN = (uint32)Cmd;
            break;
        case PMU_LDO_VDDP_EN:
            Pmu_RegBPtr->PMU_LDO_CFG.LDO_VDDP_EN = (uint32)Cmd;
            break;
        case PMU_LDO_VDDEXT_EN:
            Pmu_RegBPtr->PMU_LDO_CFG.LDO_VDDEXT_EN = (uint32)Cmd;
            break;
        case PMU_LDO_VDDVAREF_EN:
            Pmu_RegBPtr->PMU_LDO_CFG.LDO_VDDAVREF_EN = (uint32)Cmd;
            break;
        case PMU_VDDP_STABLE_EN:
            Pmu_RegBPtr->PMU_LDO_CFG.VDDP_STABLE_EN = (uint32)Cmd;
            break;
        case PMU_VDDEXT_STABLE_EN:
            Pmu_RegBPtr->PMU_LDO_CFG.VDDEXT_STABLE_EN = (uint32)Cmd;
            break;
        case PMU_VDDEXT_LPEN:
            Pmu_RegBPtr->PMU_LDO_CFG.VDDEXT_LPEN = (uint32)Cmd;
            break;
        case PMU_VDDP_STABLE_LPEN:
            Pmu_RegBPtr->PMU_LDO_CFG.VDDP_STABLE_LPEN = (uint32)Cmd;
            break;
        case PMU_VDDEXT_STABLE_LPEN:
            Pmu_RegBPtr->PMU_LDO_CFG.VDDEXT_STABLE_LPEN = (uint32)Cmd;
            break;
        default:
            /*do nothing*/
            break;
    }
    Pmu_RegBPtr->PMU_LDO_CFG.LOCK = 1U;
    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Pmu get LDO stable status.
 *
 * @param[in]  LdoType: Select the PMU LDO type defined in Pmu_LdoType.
 *             Note: Only PMU LDO_VDDP and LDO_VDDEXT is supported.
 *               - PMU_LDO_VDDP: PMU LDO_VDDP
 *               - PMU_LDO_VDDEXT: PMU LDO_VDDEXT
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_RESET: LDO is not stable.
 * @retval     COMMON_SET: LDO is stable.
 *
 */
Common_FlagStatusType Pmu_GetLdoStableStatus(Pmu_LdoType LdoType)
{
    Common_FlagStatusType Status = COMMON_RESET;
    
    switch(LdoType)
    {
        case PMU_LDO_VDDP:
            Status = Pmu_RegBPtr->PMU_LDO_CFG.VDDP_IS_STABLE != 0U ? COMMON_SET : COMMON_RESET;
            break;
        case PMU_LDO_VDDEXT:
            Status = Pmu_RegBPtr->PMU_LDO_CFG.VDDEXT_IS_STABLE != 0U ? COMMON_SET : COMMON_RESET;
            break;
        default:
            /*do nothing*/
            break;  
    }

    return Status;
}

/**
 * @brief      Pmu get LDO voltage status.
 *
 * @param[in]  LdoType: Select the PMU LDO type defined in Pmu_LdoType.
 *             Note: Only PMU LDO_VDDP and LDO_VDDEXT is supported.
 *               - PMU_LDO_VDDP: PMU LDO_VDDP
 *               - PMU_LDO_VDDEXT: PMU LDO_VDDEXT
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_RESET: LDO voltage is not ok.
 * @retval     COMMON_SET: LDO voltage is ok.
 *
 */
Common_FlagStatusType Pmu_GetLdoVoltageStatus(Pmu_LdoType LdoType)
{
    Common_FlagStatusType Status = COMMON_RESET;
    
    switch(LdoType)
    {
        case PMU_LDO_VDDP:
            Status = Pmu_RegBPtr->PMU_LDO_CFG.VDDP_IS_OK != 0U ? COMMON_SET : COMMON_RESET;
            break;
        case PMU_LDO_VDDEXT:
            Status = Pmu_RegBPtr->PMU_LDO_CFG.VDDEXT_IS_OK != 0U ? COMMON_SET : COMMON_RESET;
            break;
        default:
            /*do nothing*/
            break;  
    }

    return Status;
}

/**
 * @brief      Enable/Disable LDO under-voltage detect under active mode.
 *
 * @param[in]  UvType: Select VDD under voltage type defined in Pmu_VddUvType.
 * @param[in]  Cmd: Enable or Disable.
 *               - COMMON_DISABLE: Disable.
 *               - COMMON_ENABLE: Enable.
 *
 * @return     None
 *
 */
void Pmu_EnableUvUnderActive(Pmu_VddUvType UvType, Common_ControlStateType Cmd)
{
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    switch(UvType)
    {
        case PMU_VDDC_UV:
            Pmu_RegBPtr->PMU_UV_CFG.UV_VDDC_EN = (uint32)Cmd;
            break;
        case PMU_VDDP_UV:
            Pmu_RegBPtr->PMU_UV_CFG.UV_VDDP_EN = (uint32)Cmd;
            break;
        case PMU_VDDEXT_UV:
            Pmu_RegBPtr->PMU_UV_CFG.UV_VDDEXT_EN = (uint32)Cmd;
            break;
        case PMU_VDDVAREF_UV:
            Pmu_RegBPtr->PMU_UV_CFG.UV_VDDVAREF_EN = (uint32)Cmd;
            break;
        default:
            /*do nothing*/
            break;
    }
    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Enable/Disable LDO under-voltage detect under stop mode.
 *
 * @param[in]  UvType: Select VDD under voltage type defined in Pmu_VddUvType.
 * @param[in]  Cmd: Enable or Disable.
 *               - COMMON_DISABLE: Disable.
 *               - COMMON_ENABLE: Enable.
 *
 * @return     None
 *
 */
void Pmu_EnableUvUnderStop(Pmu_VddUvType UvType, Common_ControlStateType Cmd)
{
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    switch(UvType)
    {
        case PMU_VDDC_UV:
            Pmu_RegBPtr->PMU_UV_CFG.UV_VDDC_LPEN = (uint32)Cmd;
            break;
        case PMU_VDDP_UV:
            Pmu_RegBPtr->PMU_UV_CFG.UV_VDDP_LPEN = (uint32)Cmd;
            break;
        case PMU_VDDEXT_UV:
            Pmu_RegBPtr->PMU_UV_CFG.UV_VDDEXT_LPEN = (uint32)Cmd;
            break;
        case PMU_VDDVAREF_UV:
            Pmu_RegBPtr->PMU_UV_CFG.UV_VDDVREF_LPEN = (uint32)Cmd;
            break;
        default:
            /*do nothing*/
            break;
    }
    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Enable/Disable LDO under-voltage reset.
 *
 * @param[in]  UvType: Select VDD under voltage type defined in Pmu_VddUvType.
 * @param[in]  Cmd: Enable or Disable.
 *               - COMMON_DISABLE: Disable.
 *               - COMMON_ENABLE: Enable.
 *
 * @return     None
 *
 */
void Pmu_ResetUv(Pmu_VddUvType UvType, Common_ControlStateType Cmd)
{
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    switch(UvType)
    {
        case PMU_VDDC_UV:
            Pmu_RegBPtr->PMU_UV_CFG.UV_VDDC_RE = (uint32)Cmd;
            break;
        case PMU_VDDP_UV:
            Pmu_RegBPtr->PMU_UV_CFG.UV_VDDP_RE = (uint32)Cmd;
            break;
        default:
            /*do nothing*/
            break;
    }
    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Pmu get LDO under voltage status.
 *
 * @param[in]  UvType: Select VDD under voltage type defined in Pmu_VddUvType.
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_RESET: LDO under voltage event has not ever occured.
 * @retval     COMMON_SET: LDO under voltage event has occured.
 *
 */
Common_FlagStatusType Pmu_GetUvStatus(Pmu_VddUvType UvType)
{
    Common_FlagStatusType Status = COMMON_RESET;
    
    switch(UvType)
    {
        case PMU_VDDC_UV:
            Status = Pmu_RegBPtr->PMU_UV_STATUS.VDDC_UV != 0U ? COMMON_SET : COMMON_RESET;
            break;
        case PMU_VDDP_UV:
            Status = Pmu_RegBPtr->PMU_UV_STATUS.VDDP_UV != 0U ? COMMON_SET : COMMON_RESET;
            break;
        case PMU_VDDEXT_UV:
            Status = Pmu_RegBPtr->PMU_UV_STATUS.VDDEXT_UV != 0U ? COMMON_SET : COMMON_RESET;
            break;
        case PMU_VDDVAREF_UV:
            Status = Pmu_RegBPtr->PMU_UV_STATUS.VDDVREF_UV != 0U ? COMMON_SET : COMMON_RESET;
            break;
        default:
            /*do nothing*/
            break;  
    }

    return Status;
}

/**
 * @brief      Pmu clear LDO under voltage status.
 *
 * @param[in]  UvType: Select VDD under voltage type defined in Pmu_VddUvType.
 *
 * @return     None
 *
 */
void Pmu_ClearUvStatus(Pmu_VddUvType UvType)
{
    volatile uint32 Status = 0U;

    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }

    Status = Pmu_RegWPtr->PMU_UV_STATUS;
    Status &= (1UL << (uint32)UvType);
    Pmu_RegWPtr->PMU_UV_STATUS = Status;

    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Enable/Disable LDO over-voltage detect under active mode.
 *
 * @param[in]  OvType: Select VDD over voltage type defined in Pmu_VddOvType.
 * @param[in]  Cmd: Enable or Disable.
 *               - COMMON_DISABLE: Disable.
 *               - COMMON_ENABLE: Enable.
 *
 * @return     None
 *
 */
void Pmu_EnableOvUnderActive(Pmu_VddOvType OvType, Common_ControlStateType Cmd)
{
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    switch(OvType)
    {
        case PMU_VDDC_OV:
           Pmu_RegBPtr->PMU_OV_CFG.OV_VDDC_EN = (uint32)Cmd;
           break;
        case PMU_VDDP_OV:
           Pmu_RegBPtr->PMU_OV_CFG.OV_VDDP_EN = (uint32)Cmd;
           break;
        case PMU_VDDEXT_OV:
           Pmu_RegBPtr->PMU_OV_CFG.OV_VDDEXT_EN = (uint32)Cmd;
           break;
        case PMU_VDDVAREF_OV:
           Pmu_RegBPtr->PMU_OV_CFG.OV_VDDVAREF_EN = (uint32)Cmd;
           break;
        case PMU_VDDC_AON_OV:
           Pmu_RegBPtr->PMU_OV_CFG.OV_VDDC_AON_EN = (uint32)Cmd;
           break;
        default:
            /*do nothing*/
            break;
    }
    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Enable/Disable LDO over-voltage detect under stop mode.
 *
 * @param[in]  OvType: Select VDD over voltage type defined in Pmu_VddOvType.
 * @param[in]  Cmd: Enable or Disable.
 *               - COMMON_DISABLE: Disable.
 *               - COMMON_ENABLE: Enable.
 *
 * @return     None
 *
 */
void Pmu_EnableOvUnderStop(Pmu_VddOvType OvType, Common_ControlStateType Cmd)
{
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    switch(OvType)
    {
        case PMU_VDDC_OV:
           Pmu_RegBPtr->PMU_OV_CFG.OV_VDDC_LPEN = (uint32)Cmd;
           break;
        case PMU_VDDP_OV:
           Pmu_RegBPtr->PMU_OV_CFG.OV_VDDP_LPEN = (uint32)Cmd;
           break;
        case PMU_VDDEXT_OV:
           Pmu_RegBPtr->PMU_OV_CFG.OV_VDDEXT_LPEN = (uint32)Cmd;
           break;
        case PMU_VDDVAREF_OV:
           Pmu_RegBPtr->PMU_OV_CFG.OV_VDDVAREF_LPEN = (uint32)Cmd;
           break;
        case PMU_VDDC_AON_OV:
           Pmu_RegBPtr->PMU_OV_CFG.OV_VDDC_AON_LPEN = (uint32)Cmd;
           break;
        default:
            /*do nothing*/
            break;
    }
    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Pmu get LDO over voltage status.
 *
 * @param[in]  OvType: Select VDD over voltage type defined in Pmu_VddOvType.
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_RESET: LDO over voltage event has not ever occured.
 * @retval     COMMON_SET: LDO over voltage event has occured.
 *
 */
Common_FlagStatusType Pmu_GetOvStatus(Pmu_VddOvType OvType)
{
    Common_FlagStatusType Status = COMMON_RESET;
    
    switch(OvType)
    {
        case PMU_VDDC_OV:
            Status = Pmu_RegBPtr->PMU_OV_STATUS.VDDC_OV != 0U ? COMMON_SET : COMMON_RESET;
            break;
        case PMU_VDDP_OV:
            Status = Pmu_RegBPtr->PMU_OV_STATUS.VDDP_OV != 0U ? COMMON_SET : COMMON_RESET;
            break;
        case PMU_VDDEXT_OV:
            Status = Pmu_RegBPtr->PMU_OV_STATUS.VDDEXT_OV != 0U ? COMMON_SET : COMMON_RESET;
            break;
        case PMU_VDDVAREF_OV:
            Status = Pmu_RegBPtr->PMU_OV_STATUS.VDDVAREF_OV != 0U ? COMMON_SET : COMMON_RESET;
            break;
        case PMU_VDDC_AON_OV:
            Status = Pmu_RegBPtr->PMU_OV_STATUS.VDDCAON_OV != 0U ? COMMON_SET : COMMON_RESET;
            break;
        default:
            /*do nothing*/
            break;  
    }

    return Status;
}

/**
 * @brief      Pmu clear LDO over voltage status.
 *
 * @param[in]  OvType: Select VDD over voltage type defined in Pmu_VddOvType.
 *
 * @return     None
 *
 */
void Pmu_ClearOvStatus(Pmu_VddOvType OvType)
{
    volatile uint32 Status = 0U;

    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }

    Status = Pmu_RegWPtr->PMU_OV_STATUS;
    Status &= (1UL << (uint32)OvType);
    Pmu_RegWPtr->PMU_OV_STATUS = Status;

    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Enable/Disable LDO over loading detect under active mode.
 *
 * @param[in]  OlType: Select VDD over loading type defined in Pmu_VddOvType.
 * @param[in]  Cmd: Enable or Disable.
 *               - COMMON_DISABLE: Disable.
 *               - COMMON_ENABLE: Enable.
 *
 * @return     None
 *
 */
void Pmu_EnableOlUnderActive(Pmu_VddOlType OlType, Common_ControlStateType Cmd)
{
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    switch(OlType)
    {
        case PMU_VDDC_OL:
            Pmu_RegBPtr->PMU_OL_CFG.OL_VDDC_EN = (uint32)Cmd;
            break;
        case PMU_VDDP_OL:
            Pmu_RegBPtr->PMU_OL_CFG.OL_VDDP_EN = (uint32)Cmd;
            break;
        case PMU_VDDEXT_OL:
            Pmu_RegBPtr->PMU_OL_CFG.OL_VDDEXT_EN = (uint32)Cmd;
            break;
        case PMU_VDDVAREF_OL:
            Pmu_RegBPtr->PMU_OL_CFG.OL_VDDVAREF_EN = (uint32)Cmd;
            break;
        default:
            /*do nothing*/
            break;
    }
    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Enable/Disable LDO over loading detect under stop mode.
 *
 * @param[in]  OlType: Select VDD over loading type defined in Pmu_VddOlType.
 * @param[in]  Cmd: Enable or Disable.
 *               - COMMON_DISABLE: Disable.
 *               - COMMON_ENABLE: Enable.
 *
 * @return     None
 *
 */
void Pmu_EnableOlUnderStop(Pmu_VddOlType OlType, Common_ControlStateType Cmd)
{
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    switch(OlType)
    {
        case PMU_VDDC_OL:
            Pmu_RegBPtr->PMU_OL_CFG.OL_VDDC_LPEN = (uint32)Cmd;
            break;
        case PMU_VDDP_OL:
            Pmu_RegBPtr->PMU_OL_CFG.OL_VDDP_LPEN = (uint32)Cmd;
            break;
        case PMU_VDDEXT_OL:
            Pmu_RegBPtr->PMU_OL_CFG.OL_VDDEXT_LPEN = (uint32)Cmd;
            break;
        case PMU_VDDVAREF_OL:
            Pmu_RegBPtr->PMU_OL_CFG.OL_VDDVREF_LPEN = (uint32)Cmd;
            break;
        default:
            /*do nothing*/
            break;
    }
    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Pmu get LDO over loading status.
 *
 * @param[in]  OlType: Select VDD over loading type defined in Pmu_VddOlType.
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_RESET: LDO over loading event has not ever occured.
 * @retval     COMMON_SET: LDO over loading event has occured.
 *
 */
Common_FlagStatusType Pmu_GetOlStatus(Pmu_VddOlType OlType)
{
    Common_FlagStatusType Status = COMMON_RESET;
    
    switch(OlType)
    {
        case PMU_VDDC_OL:
            Status = Pmu_RegBPtr->PMU_OL_STATUS.OL_VDDC != 0U ? COMMON_SET : COMMON_RESET;
            break;
        case PMU_VDDP_OL:
            Status = Pmu_RegBPtr->PMU_OL_STATUS.OL_VDDP != 0U ? COMMON_SET : COMMON_RESET;
            break;
        case PMU_VDDEXT_OL:
            Status = Pmu_RegBPtr->PMU_OL_STATUS.OL_VDDEXT != 0U ? COMMON_SET : COMMON_RESET;
            break;
        case PMU_VDDVAREF_OL:
            Status = Pmu_RegBPtr->PMU_OL_STATUS.OL_VDDVREF != 0U ? COMMON_SET : COMMON_RESET;
            break;
        default:
            /*do nothing*/
            break;  
    }

    return Status;
}

/**
 * @brief      Pmu clear LDO over loading status.
 *
 * @param[in]  OlType: Select VDD over loading type defined in Pmu_VddOlType.
 *
 * @return     None
 *
 */
void Pmu_ClearOlStatus(Pmu_VddOlType OlType)
{
    volatile uint32 Status = 0U;

    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }

    Status = Pmu_RegWPtr->PMU_OL_STATUS;
    Status &= (1UL << (uint32)OlType);
    Pmu_RegWPtr->PMU_OL_STATUS = Status;

    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Pmu get LDO short status.
 *
 * @param[in]  LdoType: Select the PMU LDO type defined in Pmu_LdoType.
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_RESET: LDO short event has not ever occured.
 * @retval     COMMON_SET: LDO short event has occured.
 *
 */
Common_FlagStatusType Pmu_GetShortStatus(Pmu_LdoType LdoType)
{
    Common_FlagStatusType Status = COMMON_RESET;
    
    switch(LdoType)
    {
        case PMU_LDO_VDDC:
            Status = Pmu_RegBPtr->PMU_SHORT_STATUS.SHORT_VDDC != 0U ? COMMON_SET : COMMON_RESET;
            break;
        case PMU_LDO_VDDP:
            Status = Pmu_RegBPtr->PMU_SHORT_STATUS.SHORT_VDDP != 0U ? COMMON_SET : COMMON_RESET;
            break;
        case PMU_LDO_VDDEXT:
            Status = Pmu_RegBPtr->PMU_SHORT_STATUS.SHORT_VDDEXT != 0U ? COMMON_SET : COMMON_RESET;
            break;
        default:
            /*do nothing*/
            break;  
    }

    return Status;
}

/**
 * @brief      Pmu clear LDO short status.
 *
 * @param[in]  LdoType: Select the PMU LDO type defined in Pmu_LdoType.
 *
 * @return     None
 *
 */
void Pmu_ClearShortStatus(Pmu_LdoType LdoType)
{
    volatile uint32 Status = 0U;

    if((PMU_LDO_VDDC == LdoType) || (PMU_LDO_VDDP == LdoType) || (PMU_LDO_VDDEXT == LdoType))
    {
        if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
        {
            Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
        }

        Status = Pmu_RegWPtr->PMU_SHORT_STATUS;
        Status &= (1UL << (uint32)LdoType);
        Pmu_RegWPtr->PMU_SHORT_STATUS = Status;

        Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
    }
}

/**
 * @brief      PMU monitor filter select function.
 *
 * @param[in]  FilterType: Select monitor filtler type defined in Pmu_MonFilterType.
 * @param[in]  SelValue: Value to be selected.
 *
 * @return     None
 *
 */
void Pmu_SelectMonFilterWindow(Pmu_MonFilterType FilterType, uint32 SelValue)
{
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    switch(FilterType)
    {
        case PMU_OV_FLT_SEL:
            Pmu_RegBPtr->PMU_MON_FILT_SEL.OV_FLT_SEL = (uint32)SelValue;
            break;
        case PMU_OL_ST_FLT_SEL:
            Pmu_RegBPtr->PMU_MON_FILT_SEL.OL_ST_FLT_SEL = (uint32)SelValue;
            break;
        case PMU_OL_TM_SEL:
            Pmu_RegBPtr->PMU_MON_FILT_SEL.OL_TM_SEL = (uint32)SelValue;
            break;
        case PMU_OL_TM_EXT_SEL:
            Pmu_RegBPtr->PMU_MON_FILT_SEL.OL_TM_EXT_SEL = (uint32)SelValue;
            break;
        default:
            /*do nothing*/
            break;
    }
    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      PMU stop and standby request configuration function.
 *
 * @param[in]  ReqType: Select request type defined in Pmu_StopStandbyReqType.
 * @param[in]  Cmd: Enable or Disable.
 *               - COMMON_DISABLE: Disable.
 *               - COMMON_ENABLE: Enable.
 *
 * @return     None
 *
 */
void Pmu_ConfigStopStandbyReq(Pmu_StopStandbyReqType ReqType, Common_ControlStateType Cmd)
{
    uint32 Status = Pmu_RegWPtr->PMU_STOP_SDBREQ_EN;
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }

    if(COMMON_ENABLE == Cmd)
    {
        Status |= (1UL << (uint32)ReqType);
    }
    else
    {
        Status &= (~(1UL << (uint32)ReqType));
    }
    Pmu_RegWPtr->PMU_STOP_SDBREQ_EN = Status;

    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Set PMU regfile0 retention bytes.
 *
 * @param[in]  RetType  : PMU retention bytes type.
 * @param[in]  RetValue : Retention value.
 *
 * @return     None
 *
 */
void Pmu_SetRegfile0RetentionBytes(Pmu_RetentionByteType RetType, uint8 RetValue)
{
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    switch(RetType)
    {
        case PMU_RETENTION_BYTE0:
            Pmu_RegBPtr->PMU_REGFILE0.BYTE0 = (uint8)RetValue;
            break;
        case PMU_RETENTION_BYTE1:
            Pmu_RegBPtr->PMU_REGFILE0.BYTE1 = (uint8)RetValue;
            break;
        case PMU_RETENTION_BYTE2:
            Pmu_RegBPtr->PMU_REGFILE0.BYTE2 = (uint8)RetValue;
            break;
        case PMU_RETENTION_BYTE3:
            Pmu_RegBPtr->PMU_REGFILE0.BYTE3 = (uint8)RetValue;
            break;
        default:
            /*do nothing*/
            break;
    }
    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Read PMU regfile0 retention bytes.
 *
 * @param[in]  RetType  : PMU retention bytes type.
 *
 * @return     None
 *
 */
uint8 Pmu_ReadRegfile0RetentionBytes(Pmu_RetentionByteType RetType)
{
    uint8 Result = (uint8)0U;

    switch(RetType)
    {
        case PMU_RETENTION_BYTE0:
            Result = (uint8)Pmu_RegBPtr->PMU_REGFILE0.BYTE0;
            break;
        case PMU_RETENTION_BYTE1:
            Result = (uint8)Pmu_RegBPtr->PMU_REGFILE0.BYTE1;
            break;
        case PMU_RETENTION_BYTE2:
            Result = (uint8)Pmu_RegBPtr->PMU_REGFILE0.BYTE2;
            break;
        case PMU_RETENTION_BYTE3:
            Result = (uint8)Pmu_RegBPtr->PMU_REGFILE0.BYTE3;
            break;
        default:
            /*do nothing*/
            break;
    }

    return Result;
}

/**
 * @brief      Set PMU regfile1 retention bytes.
 *
 * @param[in]  RetType  : PMU retention bytes type.
 * @param[in]  RetValue : Retention value.
 *
 * @return     None
 *
 */
void Pmu_SetRegfile1RetentionBytes(Pmu_RetentionByteType RetType, uint8 RetValue)
{
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    switch(RetType)
    {
        case PMU_RETENTION_BYTE0:
            Pmu_RegBPtr->PMU_REGFILE1.BYTE0 = (uint8)RetValue;
            break;
        case PMU_RETENTION_BYTE1:
            Pmu_RegBPtr->PMU_REGFILE1.BYTE1 = (uint8)RetValue;
            break;
        case PMU_RETENTION_BYTE2:
            Pmu_RegBPtr->PMU_REGFILE1.BYTE2 = (uint8)RetValue;
            break;
        default:
            /*do nothing*/
            break;
    }
    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Read PMU regfile1 retention bytes.
 *
 * @param[in]  RetType  : PMU retention bytes type.
 *
 * @return     None
 *
 */
uint8 Pmu_ReadRegfile1RetentionBytes(Pmu_RetentionByteType RetType)
{
    uint8 Result = (uint8)0U;

    switch(RetType)
    {
        case PMU_RETENTION_BYTE0:
            Result = (uint8)Pmu_RegBPtr->PMU_REGFILE1.BYTE0;
            break;
        case PMU_RETENTION_BYTE1:
            Result = (uint8)Pmu_RegBPtr->PMU_REGFILE1.BYTE1;
            break;
        case PMU_RETENTION_BYTE2:
            Result = (uint8)Pmu_RegBPtr->PMU_REGFILE1.BYTE2;
            break;
        default:
            /*do nothing*/
            break;
    }

    return Result;
}

/**
 * @brief      Enable/Disable CP reference BG1 1v buffer.
 *
 * @param[in]  Cmd: Enable or Disable.
 *               - COMMON_DISABLE: Disable.
 *               - COMMON_ENABLE: Enable.
 *
 * @return     None
 *
 */
void Pmu_EnableCPRef1VBuffer(Common_ControlStateType Cmd)
{
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    Pmu_RegBPtr->PMU_MISC_CTRL1.CP_REF1V_BUF_EN = (uint32)Cmd;
    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Enable/Disable temperature sensor for GDU or Lin.
 *
 * @param[in]  TsType: Select temperature sensor type defined in Pmu_TsType.
 * @param[in]  Cmd: Enable or Disable.
 *               - COMMON_DISABLE: Disable.
 *               - COMMON_ENABLE: Enable.
 *
 * @return     None
 *
 */
void Pmu_EnableTemperatureSensor(Pmu_TsType TsType, Common_ControlStateType Cmd)
{
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    switch(TsType)
    {
        case PMU_GDU_TS:
            Pmu_RegBPtr->PMU_MISC_CTRL1.GDU_TS_EN = (uint32)Cmd;
            break;
        case PMU_LIN_TS:
            Pmu_RegBPtr->PMU_MISC_CTRL1.LIN_TS_EN = (uint32)Cmd;
            break;
        default:
            /*do nothing*/
            break;
    }
    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      PMU attenuator configuration function.
 *
 * @param[in]  AttenType: Attenuator type defined in Pmu_AttenType.
 * @param[in]  Cmd: Enable or Disable.
 *               - COMMON_DISABLE: Disable.
 *               - COMMON_ENABLE: Enable.
 *
 * @return     None
 *
 */
void Pmu_ConfigAtten(Pmu_AttenType AttenType, Common_ControlStateType Cmd)
{
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    switch(AttenType)
    {
        case PMU_ATT_VDH_EN:
            Pmu_RegBPtr->PMU_ATTEN_CFG.ATT_VDH_EN = (uint32)Cmd;
            break;
        case PMU_ATT_VMON_EN:
            Pmu_RegBPtr->PMU_ATTEN_CFG.ATT_VMON_EN = (uint32)Cmd;
            break;
        case PMU_ATT_VCP_EN:
            Pmu_RegBPtr->PMU_ATTEN_CFG.ATT_VCP_EN = (uint32)Cmd;
            break;
        case PMU_ATT_VSD_EN:
            Pmu_RegBPtr->PMU_ATTEN_CFG.ATT_VSD_EN = (uint32)Cmd;
            break;
        case PMU_ATT_VS_EN:
            Pmu_RegBPtr->PMU_ATTEN_CFG.ATT_VS_EN = (uint32)Cmd;
            break;
        case PMU_ATT_VDDP_EN:
            Pmu_RegBPtr->PMU_ATTEN_CFG.ATT_VDDP_EN = (uint32)Cmd;
            break;
        case PMU_ATT_EN:
            Pmu_RegBPtr->PMU_ATTEN_CFG.ATT_EN = (uint32)Cmd;
            break;
        default:
            /*do nothing*/
            break;
    }
    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Pmu get system failure status.
 *
 * @param[in]  SysFailType: Select system failure type defined in Pmu_SysFailType.
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_RESET: System failure event has not ever occured.
 * @retval     COMMON_SET: System failure event has occured.
 *
 */
Common_FlagStatusType Pmu_GetSysFailStatus(Pmu_SysFailType SysFailType)
{
    Common_FlagStatusType Status = COMMON_RESET;
    uint32 TempStatus = Pmu_RegWPtr->PMU_SYS_FAIL_STATUS & (1UL << (uint32)SysFailType);

    if(TempStatus != 0UL)
    {
        Status = COMMON_SET;
    }

    return Status;
}

/**
 * @brief      Pmu clear system failure status.
 *
 * @param[in]  SysFailType: Select system failure type defined in Pmu_SysFailType.
 *
 * @return     None
 *
 */
void Pmu_ClearSysFailStatus(Pmu_SysFailType SysFailType)
{
    volatile uint32 Status = 0U;

    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }

    Status = Pmu_RegWPtr->PMU_SYS_FAIL_STATUS;
    Status &= (1UL << (uint32)SysFailType);
    Pmu_RegWPtr->PMU_SYS_FAIL_STATUS = Status;

    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Pmu get wakeup timer interrupt status Function.
 *
 * @param[in]  None
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_RESET: Flag is cleared or no wakeup timer interrupt has ever occured.
 * @retval     COMMON_SET: Wakeup timer interrupt has occured.
 *
 */
Common_FlagStatusType Pmu_GetWkTimIntStatus(void)
{
    Common_FlagStatusType Status;
    
    if((Pmu_RegWPtr->PMU_CSR & Pmu_IntStatusTable[PMU_WAKEUP_TIMER_INT]) != 0U)
    {
        Status = COMMON_SET;
    }
    else
    {
        Status = COMMON_RESET;
    }

    return Status;
}

/**
 * @brief      Pmu get high voltage monitor interrupt status Function.
 *
 * @param[in]  None
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_RESET: Flag is cleared or no high voltage monitor interrupt has ever occured.
 * @retval     COMMON_SET: High voltage monitor interrupt has occured.
 *
 */
Common_FlagStatusType Pmu_GetHvMonIntStatus(void)
{
    Common_FlagStatusType Status;
    
    if((Pmu_RegWPtr->PMU_HV_MON_CFG & Pmu_IntStatusTable[PMU_HVMON_INT]) != 0U)
    {
        Status = COMMON_SET;
    }
    else
    {
        Status = COMMON_RESET;
    }

    return Status;
}

/**
 * @brief      Pmu get vdd exit fail relative event interrupt status Function.
 *
 * @param[in]  IntType: Select the interrupt type.
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_RESET: Flag is cleared or no high voltage monitor interrupt has ever occured.
 * @retval     COMMON_SET: High voltage monitor interrupt has occured.
 *
 */
Common_FlagStatusType Pmu_GetVddExtFailIntStatus(Pmu_IntType IntType)
{
    Common_FlagStatusType Status = COMMON_RESET;
    
    switch(IntType)
    {
        case PMU_VDDEXT_UV_INT:
            Status = Pmu_GetUvStatus(PMU_VDDEXT_UV);
            break;
        case PMU_VDDEXT_OV_INT:
            Status = Pmu_GetOvStatus(PMU_VDDEXT_OV);
            break;
        case PMU_VDDEXT_OL_INT:
            Status = Pmu_GetOlStatus(PMU_VDDEXT_OL);
            break;
        case PMU_VDDEXT_SHORT_INT:
            Status = Pmu_GetShortStatus(PMU_LDO_VDDEXT);
            break;
        default:
            /* do nothing */
            break;
    }

    return Status;
}

/**
 * @brief      Pmu get interrupt status Function.
 *
 * @param[in]  IntType: Select the interrupt type.
 *
 * @return     Common_FlagStatusType
 * @retval     COMMON_RESET: Flag is cleared or no interrupt has ever occured.
 * @retval     COMMON_SET: Interrupt has occured.
 *
 */
Common_FlagStatusType Pmu_GetIntStatus(Pmu_IntType IntType)
{
    Common_FlagStatusType Status = COMMON_RESET;

    switch(IntType)
    {
        case PMU_WAKEUP_TIMER_INT:
            Status = Pmu_GetWkTimIntStatus();
            break;
        case PMU_HVMON_INT:
            Status = Pmu_GetHvMonIntStatus();
            break;
        case PMU_VDDEXT_UV_INT:
            Status = Pmu_GetVddExtFailIntStatus(IntType);
            break;
        case PMU_VDDEXT_OV_INT:
            Status = Pmu_GetVddExtFailIntStatus(IntType);
            break;
        case PMU_VDDEXT_OL_INT:
            Status = Pmu_GetVddExtFailIntStatus(IntType);
            break;
        case PMU_VDDEXT_SHORT_INT:
            Status = Pmu_GetVddExtFailIntStatus(IntType);
            break;
        default:
            /*do nothing*/
            break;
    }
    
    return Status;
}

/**
 * @brief      MASK/UNMASK wakeup timer Interrupt Function.
 *
 * @param[in]  IntMask: UNMASK or MASK.
 *
 * @return     None
 *
 */
void Pmu_SetWkTimIntMask(Common_IntMaskType IntMask)
{
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    
    if(COMMON_UNMASK == IntMask)
    {
        Pmu_RegWPtr->PMU_CSR = Pmu_RegWPtr->PMU_CSR | Pmu_IntMaskTable[PMU_WAKEUP_TIMER_INT];
        Pmu_IntMaskStatusTable[PMU_WAKEUP_TIMER_INT] = Pmu_IntMaskStatusTable[PMU_WAKEUP_TIMER_INT] | Pmu_IntStatusTable[PMU_WAKEUP_TIMER_INT];
    }
    else
    {
        Pmu_IntMaskStatusTable[PMU_WAKEUP_TIMER_INT] = Pmu_IntMaskStatusTable[PMU_WAKEUP_TIMER_INT] & (~Pmu_IntStatusTable[PMU_WAKEUP_TIMER_INT]);
        Pmu_RegWPtr->PMU_CSR = Pmu_RegWPtr->PMU_CSR & (~Pmu_IntMaskTable[PMU_WAKEUP_TIMER_INT]);
    }

    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      MASK/UNMASK VDD exit fail Interrupt Function.
 *
 * @param[in]  IntType: Select the interrupt type of vdd exit fail interrupt.
 * @param[in]  IntMask: UNMASK or MASK.
 *
 * @return     None
 *
 */
void Pmu_SetVddExtFailIntMask(Pmu_IntType IntType, Common_IntMaskType IntMask)
{
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }

    /* exclude wakeup timer interrupt and high voltage monitor interrupt */
    if((PMU_WAKEUP_TIMER_INT != IntType) && (PMU_HVMON_INT != IntType))
    {
        if(COMMON_UNMASK == IntMask)
        {
            Pmu_RegWPtr->PMU_CSR = Pmu_RegWPtr->PMU_CSR | Pmu_IntMaskTable[IntType];
            Pmu_IntMaskStatusTable[IntType] = Pmu_IntMaskStatusTable[IntType] | Pmu_IntStatusTable[IntType];
        }
        else
        {
            Pmu_IntMaskStatusTable[IntType] = Pmu_IntMaskStatusTable[IntType] & (~Pmu_IntStatusTable[IntType]);

            /* If all four event flags are masked, the corresponding interrupt is disabled */
            if(0U == (Pmu_IntMaskStatusTable[PMU_VDDEXT_UV_INT] | Pmu_IntMaskStatusTable[PMU_VDDEXT_OV_INT] | \
            Pmu_IntMaskStatusTable[PMU_VDDEXT_OL_INT] | Pmu_IntMaskStatusTable[PMU_VDDEXT_SHORT_INT]))
            {
                Pmu_RegWPtr->PMU_CSR = Pmu_RegWPtr->PMU_CSR & (~Pmu_IntMaskTable[IntType]);
            }
        }
    }

    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      MASK/UNMASK high voltage monitor Interrupt Function.
 *
 * @param[in]  IntMask: UNMASK or MASK.
 *
 * @return     None
 *
 */
void Pmu_SetHvMonIntMask(Common_IntMaskType IntMask)
{
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    
    if(COMMON_UNMASK == IntMask)
    {
        Pmu_RegWPtr->PMU_HV_MON_CFG = Pmu_RegWPtr->PMU_HV_MON_CFG | Pmu_IntMaskTable[PMU_HVMON_INT];
        Pmu_IntMaskStatusTable[PMU_HVMON_INT] = Pmu_IntMaskStatusTable[PMU_HVMON_INT] | Pmu_IntStatusTable[PMU_HVMON_INT];
    }
    else
    {
        Pmu_IntMaskStatusTable[PMU_HVMON_INT] = Pmu_IntMaskStatusTable[PMU_HVMON_INT] & (~Pmu_IntStatusTable[PMU_HVMON_INT]);
        Pmu_RegWPtr->PMU_HV_MON_CFG = Pmu_RegWPtr->PMU_HV_MON_CFG & (~Pmu_IntMaskTable[PMU_HVMON_INT]);
    }

    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}


/**
 * @brief      MASK/UNMASK the Relevant Interrupt Function.
 *
 * @param[in]  IntType: Select the interrupt type.
 * @param[in]  IntMask: UNMASK or MASK.
 *
 * @return     None
 *
 */
void Pmu_SetIntMask(Pmu_IntType IntType, Common_IntMaskType IntMask)
{
    switch(IntType)
    {
        case PMU_WAKEUP_TIMER_INT:
            Pmu_SetWkTimIntMask(IntMask);
            break;
        case PMU_HVMON_INT:
            Pmu_SetHvMonIntMask(IntMask);
            break;
        case PMU_VDDEXT_UV_INT:
            Pmu_SetVddExtFailIntMask(IntType, IntMask);
            break;
        case PMU_VDDEXT_OV_INT:
            Pmu_SetVddExtFailIntMask(IntType, IntMask);
            break;
        case PMU_VDDEXT_OL_INT:
            Pmu_SetVddExtFailIntMask(IntType, IntMask);
            break;
        case PMU_VDDEXT_SHORT_INT:
            Pmu_SetVddExtFailIntMask(IntType, IntMask);
            break;
        default:
            /*do nothing*/
            break;
    }
}

/**
 * @brief      Clear the wakeup timer Interrupt Status.
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void Pmu_ClearWkTimInt(void)
{
    uint32 PmuCsrTemp = Pmu_RegWPtr->PMU_CSR;
    PmuCsrTemp &= 0xfffff7ffU;
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    Pmu_RegWPtr->PMU_CSR = PmuCsrTemp | Pmu_IntStatusTable[PMU_WAKEUP_TIMER_INT];
    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Clear the high voltage monitor Interrupt Status
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void Pmu_ClearHvMonInt(void)
{
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    Pmu_RegWPtr->PMU_HV_MON_CFG = Pmu_RegWPtr->PMU_HV_MON_CFG | Pmu_IntStatusTable[PMU_HVMON_INT];
    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Clear the Relevant Interrupt Status.
 *
 * @param[in]  IntType: Select the interrupt type.
 *
 * @return     None
 *
 */
void Pmu_ClearInt(Pmu_IntType IntType)
{
    switch(IntType)
    {
        case PMU_WAKEUP_TIMER_INT:
            Pmu_ClearWkTimInt();
            break;
        case PMU_HVMON_INT:
            Pmu_ClearHvMonInt();
            break;
        case PMU_VDDEXT_UV_INT:
            Pmu_ClearUvStatus(PMU_VDDEXT_UV);
            break;
        case PMU_VDDEXT_OV_INT:
            Pmu_ClearOvStatus(PMU_VDDEXT_OV);
            break;
        case PMU_VDDEXT_OL_INT:
            Pmu_ClearOlStatus(PMU_VDDEXT_OL);
            break;
        case PMU_VDDEXT_SHORT_INT:
            Pmu_ClearShortStatus(PMU_LDO_VDDEXT);
            break;
        default:
            /*do nothing*/
            break;
    }
}

/**
 * @brief      Install call back function.
 *
 * @param[in]  IntType: Select the interrupt type.
 * @param[in]  CallbackFun: Pointer to callback function.
 *
 * @return     None
 *
 */
void Pmu_InstallCallBackFunc(Pmu_IntType IntType, Isr_CbFuncType * CallbackFun)
{
    Pmu_IsrCallback[IntType] = CallbackFun;
}

/**
 * @brief      Pmu VDDEXT IRQ Handler.
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void Pmu_VddExtFailIrqHandler(void)
{
    /* Enable vdd exit fail interrupt */
    if(COMMON_SET == Pmu_GetUvStatus(PMU_VDDEXT_UV))
    {
        Pmu_ClearUvStatus(PMU_VDDEXT_UV);
        if(Pmu_IsrCallback[PMU_VDDEXT_UV_INT] != NULL_PTR)
        {
            /* call the callback function */
            Pmu_IsrCallback[PMU_VDDEXT_UV_INT]();
        }
        else
        {
            Pmu_SetVddExtFailIntMask(PMU_VDDEXT_UV_INT, COMMON_MASK);
        }
    }

    if(COMMON_SET == Pmu_GetOvStatus(PMU_VDDEXT_OV))
    {
        Pmu_ClearOvStatus(PMU_VDDEXT_OV);
        if(Pmu_IsrCallback[PMU_VDDEXT_OV_INT] != NULL_PTR)
        {
            /* call the callback function */
            Pmu_IsrCallback[PMU_VDDEXT_OV_INT]();
        }
        else
        {
            Pmu_SetVddExtFailIntMask(PMU_VDDEXT_OV_INT, COMMON_MASK);
        }
    }

    if(COMMON_SET == Pmu_GetOlStatus(PMU_VDDEXT_OL))
    {
        Pmu_ClearOlStatus(PMU_VDDEXT_OL);
        if(Pmu_IsrCallback[PMU_VDDEXT_OL_INT] != NULL_PTR)
        {
            /* call the callback function */
            Pmu_IsrCallback[PMU_VDDEXT_OL_INT]();
        }
        else
        {
            Pmu_SetVddExtFailIntMask(PMU_VDDEXT_OL_INT, COMMON_MASK);
        }
    }

    if(COMMON_SET == Pmu_GetShortStatus(PMU_LDO_VDDEXT))
    {
        Pmu_ClearShortStatus(PMU_LDO_VDDEXT);
        if(Pmu_IsrCallback[PMU_VDDEXT_SHORT_INT] != NULL_PTR)
        {
            /* call the callback function */
            Pmu_IsrCallback[PMU_VDDEXT_SHORT_INT]();
        }
        else
        {
            Pmu_SetVddExtFailIntMask(PMU_VDDEXT_SHORT_INT, COMMON_MASK);
        }
    }
}

/**
 * @brief      Pmu IRQ Handler.
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void Pmu_DriverIrqHandler(void)
{   
    uint32 WkTimIntStatus;

    /* get interrupt status */
    WkTimIntStatus = Pmu_RegWPtr->PMU_CSR;

    /* only check enabled interrupts */
    WkTimIntStatus = WkTimIntStatus & Pmu_IntMaskStatusTable[PMU_WAKEUP_TIMER_INT];
    
    /* clear interrupt status */
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    Pmu_RegWPtr->PMU_CSR = WkTimIntStatus;
    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;

    /* wakeup timer Interrupt */
    if((WkTimIntStatus & Pmu_IntStatusTable[PMU_WAKEUP_TIMER_INT]) != 0U)
    {
        /* Call the callback function if it has been setup */
        if(Pmu_IsrCallback[PMU_WAKEUP_TIMER_INT] != NULL_PTR)
        {
             Pmu_IsrCallback[PMU_WAKEUP_TIMER_INT]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            Pmu_SetIntMask(PMU_WAKEUP_TIMER_INT, COMMON_MASK);
        }
    }
    /*check whether VDD EXT FAIL interrupt enable*/
    if((Pmu_RegWPtr->PMU_CSR & 0x00000200U) != 0U)
    {
        Pmu_VddExtFailIrqHandler();
    }
}

/**
 * @brief      Mon IRQ Handler.
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void Pmu_Mon_DriverIrqHandler(void)
{   
    uint32 HvMonIntStatus;

    /* get interrupt status */
    HvMonIntStatus = Pmu_RegWPtr->PMU_HV_MON_CFG;
    
    /* only check enabled interrupts */
    HvMonIntStatus = HvMonIntStatus & Pmu_IntMaskStatusTable[PMU_HVMON_INT];
    
    /* clear interrupt status */
    if(1U == Pmu_RegBPtr->PMU_LOCK.LOCK)
    {
        Pmu_RegWPtr->PMU_LOCK = PMU_UNLOCK;
    }
    Pmu_RegWPtr->PMU_HV_MON_CFG = HvMonIntStatus;
    Pmu_RegBPtr->PMU_LOCK.LOCK = 1U;

    /* high voltage monitor Interrupt */
    if((HvMonIntStatus & Pmu_IntStatusTable[PMU_HVMON_INT]) != 0U)
    {
        /* Call the callback function if it has been setup */
        if(Pmu_IsrCallback[PMU_HVMON_INT] != NULL_PTR)
        {
            Pmu_IsrCallback[PMU_HVMON_INT]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
             Pmu_SetIntMask(PMU_HVMON_INT, COMMON_MASK);
        }
    }
}

/** @} end of group Public_FunctionDefinition */
