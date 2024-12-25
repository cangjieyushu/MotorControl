/**************************************************************************************************/
/**
 * @file      : Pmu_Drv.h
 * @brief     : Pmu module driver header file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#ifndef PMU_DRV_H
#define PMU_DRV_H

#include "Common_Drv.h"

/** @addtogroup Public_MacroDefinition
 *  @{
 */

/** @} end of Public_MacroDefinition */

/** @defgroup Public_TypeDefinition
 *  @{
 */

/**
 *  @brief PMU interrupt type definition
 */
typedef enum
{
    PMU_WAKEUP_TIMER_INT = 0U,   /*!< PMU wakeup timer interrupt */  
    PMU_HVMON_INT,               /*!< PMU high voltage monitor interrupt */
    PMU_VDDEXT_UV_INT,           /*!< PMU VDDEXT_FAIL: vdd exit under voltage interrupt */
    PMU_VDDEXT_OV_INT,           /*!< PMU VDDEXT_FAIL: vdd exit over voltage interrupt */
    PMU_VDDEXT_OL_INT,           /*!< PMU VDDEXT_FAIL: vdd exit over loading interrupt */
    PMU_VDDEXT_SHORT_INT         /*!< PMU VDDEXT_FAIL: vdd exit short event interrupt */
} Pmu_IntType;
    
/**
 *  @brief PMU control type definition
 */
typedef enum
{
    PMU_REF1V_BUF_EN       = 1U,      /*!< PMU reference 1V output enable/disable with buf control for ADC channel */
    PMU_CYCLIC_CNT_EN      = 2U,      /*!< PMU cyclic wakeup timer counter enable/disable */
    PMU_WKUP_CNT_EN        = 3U,      /*!< PMU wakeup timer counter enable/disable */
    PMU_CYCLIC_SENSE_SEL   = 4U,      /*!< PMU select cyclic sense feature for stop mode or disable it */
    PMU_TS_EN              = 6U,      /*!< PMU thermal sensor enable/disable */
    PMU_OL_ST_FLT_EN       = 7U,      /*!< PMU over loading and short filter enable/disable */
    PMU_OV_FLT_EN          = 8U,      /*!< PMU over voltage filter enable/disable */
    PMU_VAREF_CMP_EN       = 10U,     /*!< PMU VAREF comparator enable/disable */
    PMU_VDDP_OK_DET_EN     = 13U,     /*!< PMU VDDP ok detect circuit enable/disable under active mode */
    PMU_VDDP_OK_DET_LPEN   = 14U,     /*!< PMU VDDP ok detect circuit enable/disable under stop mode */
    PMU_VDDEXT_OK_DET_EN   = 15U,     /*!< PMU VDDEXT ok detect circuit enable/disable under active mode */
    PMU_VDDEXT_OK_DET_LPEN = 16U      /*!< PMU VDDEXT ok detect circuit enable/disable under stop mode */
} Pmu_CtrlType;

/**
 *  @brief PMU HVMON configuration type definition
 */
typedef enum
{
    PMU_HVMON_FLT_EN  = 0U,      /*!< PMU HVMON filter enable/disable */
    PMU_HVMON_EN      = 1U,      /*!< PMU HVMON enable/disable under normal mode */
    PMU_HVMON_PU_EN   = 3U,      /*!< PMU HVMON pull up enable/disable */
    PMU_HVMON_PD_EN   = 4U,      /*!< PMU HVMON pull down enable/disable */
} Pmu_HvMonCfgType;

/**
 *  @brief PMU cyclic counter type definition
 */
typedef enum
{
    PMU_CYCLIC_DEAD_CNT = 0U,  /*!< used for stop dead mode and only increase when CYCLIC_CNT_EN = 1 */
    PMU_CYCLIC_SENSE_CNT       /*!< used for stop sense mode and only increase when CYCLIC_CNT_EN = 1 */
} Pmu_CycCntType;

/**
 *  @brief PMU wakeup counter type definition
 */
typedef enum
{
    PMU_AUTO_WKUP_CNT = 0U,   /*!< auto wakeup match counter for standby mode and only valid when WKUP_CNT_EN = 1 */
    PMU_NORMAL_WKUP_CNT       /*!< normal wakeup match counter for stop and standby mode and only valid when WKUP_CNT_EN = 1 */
} Pmu_WkupCntType;

/**
 *  @brief PMU LDO type definition
 */
typedef enum
{
    PMU_LDO_VDDC     = 0U,      /*!< PMU LDO_VDDC */
    PMU_LDO_VDDP     = 1U,      /*!< PMU LDO_VDDP */
    PMU_LDO_VDDEXT   = 2U,      /*!< PMU LDO_VDDEXT */
    PMU_LDO_VDDVAREF = 3U,      /*!< PMU LDO_VAREF */
    PMU_LDO_VDDC_AON = 4U       /*!< PMU LDO_VDDC_AON */
} Pmu_LdoType;

/**
 *  @brief PMU under voltage type definition
 */
typedef enum
{
    PMU_VDDC_UV     = 0U,      /*!< PMU LDO_VDDC UV */
    PMU_VDDP_UV     = 1U,      /*!< PMU LDO_VDDP UV */
    PMU_VDDEXT_UV   = 2U,      /*!< PMU LDO_VDDEXT UV */
    PMU_VDDVAREF_UV = 3U       /*!< PMU LDO_VAREF UV */
} Pmu_VddUvType;

/**
 *  @brief PMU over voltage type definition
 */
typedef enum
{
    PMU_VDDC_OV     = 0U,      /*!< PMU LDO_VDDC OV */
    PMU_VDDP_OV     = 1U,      /*!< PMU LDO_VDDP OV */
    PMU_VDDEXT_OV   = 2U,      /*!< PMU LDO_VDDEXT OV */
    PMU_VDDVAREF_OV = 3U,      /*!< PMU LDO_VAREF OV */
    PMU_VDDC_AON_OV = 4U       /*!< PMU LDO_VDDC_AON OV */
} Pmu_VddOvType;

/**
 *  @brief PMU over loading type definition
 */
typedef enum
{
    PMU_VDDC_OL     = 0U,      /*!< PMU LDO_VDDC OL */
    PMU_VDDP_OL     = 1U,      /*!< PMU LDO_VDDP OL */
    PMU_VDDEXT_OL   = 2U,      /*!< PMU LDO_VDDEXT OL */
    PMU_VDDVAREF_OL = 3U       /*!< PMU LDO_VAREF OL */
} Pmu_VddOlType;

/**
 *  @brief PMU LDO configuration type definition
 */
typedef enum
{
    PMU_LDO_VDDC_EN         = 0U,     /*!< PMU LDO VDDC enable/disable */
    PMU_LDO_VDDP_EN         = 1U,     /*!< PMU LDO VDDP enable/disable */
    PMU_LDO_VDDEXT_EN       = 2U,     /*!< PMU LDO VDDEXT enable/disable */
    PMU_LDO_VDDVAREF_EN     = 3U,     /*!< PMU LDO VDD analog vref enable/disable */
    PMU_VDDP_STABLE_EN      = 5U,     /*!< PMU LDO VDDP stable detect circuit enable/disable */
    PMU_VDDEXT_STABLE_EN    = 6U,     /*!< PMU LDO VDDEXT stable detect circuit enable/disable */
    PMU_VDDEXT_LPEN         = 7U,     /*!< PMU LDO VDDEXT enable/disable for stop mode */
    PMU_VDDP_STABLE_LPEN    = 18U,    /*!< PMU LDO VDDP stable detect circuit enable/disable */
    PMU_VDDEXT_STABLE_LPEN  = 19U     /*!< PMU LDO VDDEXT stable detect circuit enable/disable */
} Pmu_LdoCfgType;

/**
 *  @brief PMU monitor filter type definition
 */
typedef enum
{
    PMU_OV_FLT_SEL    = 0U,      /*!< PMU over voltage filter 
                                          - 00:  600us
                                          - 01:  700us
                                          - 02:  800us
                                          - 03: 1000us */
    PMU_OL_ST_FLT_SEL = 1U,      /*!< PMU over loading and short filter
                                          - 00:  20us
                                          - 01:  30us
                                          - 02:  40us
                                          - 03:  60us */
    PMU_OL_TM_SEL     = 2U,      /*!< PMU over loading timeout for vddc/vddp/vddaref
                                          - 00:  200us
                                          - 01:  300us
                                          - 02:  400us
                                          - 03:  600us */
    PMU_OL_TM_EXT_SEL = 3U       /*!< PMU over loading timeout for vddext
                                          - 00:  70us
                                          - 01:  100us
                                          - 02:  150us
                                          - 03:  200us */
} Pmu_MonFilterType;

/**
 *  @brief PMU stop and standby request type definition
 */
typedef enum
{
    PMU_VDDC_SDBREQ_EN0         = 0U,     /*!< PMU enable/disable VDDC over loading event to turn off VDDC */
    PMU_VDDC_SDBREQ_EN1         = 1U,     /*!< PMU enable/disable VDDC short event to turn off VDDC */
    PMU_VDDP_SDBREQ_EN0         = 2U,     /*!< PMU enable/disable VDDP over loading event to turn off VDDP */
    PMU_VDDP_SDBREQ_EN1         = 3U,     /*!< PMU enable/disable VDDP short event to turn off VDDP */
    PMU_VDDEXT_SDBREQ_EN0       = 4U,     /*!< PMU enable/disable VDDEXT over loading event to turn off VDDEXT */
    PMU_VDDEXT_SDBREQ_EN1       = 5U,     /*!< PMU enable/disable VDDEXT short event to turn off VDDEXT */
    PMU_VDDEXT_FAIL_STOP_RST_EN = 6U,     /*!< PMU enable/disable VDDEXT failure to generate reset as stop wakeup source */
    PMU_CYCLIC_SENSE_RST_EN     = 7U,     /*!< PMU enable/disable cyclic sense trigger to generate reset as stop wakeup source */
    PMU_WKUP_TIMER_TRIG_RST_EN  = 8U,     /*!< PMU enable/disable wakeup sense trigger to generate reset as stop wakeup source */
    PMU_CMP_SDBREQ_EN           = 9U,     /*!< PMU enable/disable CMP fault entering standby mode */
    PMU_GDU_FAIL_SDBREQ_EN      = 10U,    /*!< PMU enable/disable GDU fault entering standby mode */
    PMU_WDG_SDBREQ_EN           = 11U,    /*!< PMU enable/disable Watch Dog fault entering standby mode */
    PMU_LOC_SDBREQ_EN           = 12U,    /*!< PMU enable/disable loss of clock fault entering standby mode */
    PMU_OT_SDBREQ_EN            = 13U,    /*!< PMU enable/disable over temperature fault entering standby mode */
    PMU_UV_VDDC_SDBREQ_EN       = 14U,    /*!< PMU enable/disable allow vddc uv reset to generate standby request */
    PMU_UV_VDDP_SDBREQ_EN       = 15U,    /*!< PMU enable/disable allow vddp uv reset to generate standby request */
    PMU_LIN_TRIG_RST_EN         = 16U,    /*!< PMU enable/disable lin trigger generate reset as stop wakeup source */
    PMU_PORTA_RST_EN            = 17U,    /*!< PMU enable/disable port A generate reset as stop wakeup source */
    PMU_HVMON_RST_EN            = 18U     /*!< PMU enable/disable HVMON trigger generate reset as stop wakeup source */
} Pmu_StopStandbyReqType;

/**
 *  @brief PMU temperature sensor type definition
 */
typedef enum
{
    PMU_GDU_TS = 0U,         /*!< GDU temperature sensor */   
    PMU_LIN_TS               /*!< Lin temperature sensor */ 
} Pmu_TsType;

/**
 *  @brief PMU attenuator type definition
 */
typedef enum
{
    PMU_ATT_VDH_EN = 0U,         /*!< PMU attenuator VDH channel */   
    PMU_ATT_VMON_EN,             /*!< PMU attenuator VMON channel */ 
    PMU_ATT_VCP_EN,              /*!< PMU attenuator VCP channel */ 
    PMU_ATT_VSD_EN,              /*!< PMU attenuator VSD channel */ 
    PMU_ATT_VS_EN,               /*!< PMU attenuator VS channel */ 
    PMU_ATT_VDDP_EN,             /*!< PMU attenuator VDDP channel */ 
    PMU_ATT_EN                   /*!< PMU attenuator module */ 
} Pmu_AttenType;

/**
 *  @brief PMU system failure type definition
 */
typedef enum
{
    PMU_SYS_FAIL_VDDP_OL = 0U,   /*!< PMU VDDP over-loading timeout failure */   
    PMU_SYS_FAIL_VDDC_OL,        /*!< PMU VDDC over-loading timeout failure */ 
    PMU_SYS_FAIL_VDDP_ST,        /*!< PMU VDDP short failure */ 
    PMU_SYS_FAIL_VDDC_ST,        /*!< PMU VDDC short failure */ 
    PMU_SYS_FAIL_VDDP_UV,        /*!< PMU VDDP under-voltage failure */ 
    PMU_SYS_FAIL_VDDC_UV,        /*!< PMU VDDC under-voltage failure */ 
    PMU_SYS_FAIL_WDG_5,          /*!< Watchdog consecutive 5 or more failures */ 
    PMU_SYS_FAIL_ADC_OT,         /*!< ADC over-temperature failure */ 
    PMU_SYS_FAIL_GDU,            /*!< GDU failure */ 
    PMU_SYS_FAIL_SCC_LOC,        /*!< SCC loss of clock failure */ 
    PMU_SYS_FAIL_CMP_FAULT,      /*!< CMP failure */
    PMU_SYS_FAIL_SUPPLY_5,       /*!< System supply failure times over 5 */
    PMU_SYS_WAKEUP_TIMER = 29U,  /*!< System has been awakened from system failure standby mode by Timer */ 
    PMU_SYS_WAKEUP_HVMON,        /*!< System has been awakened from system failure standby mode by HVMON */  
    PMU_SYS_WAKEUP_LIN           /*!< System has been awakened from system failure standby mode by Lin */ 
} Pmu_SysFailType;

/**
 *  @brief PMU retention bytes type definition
 */
typedef enum
{
    PMU_RETENTION_BYTE0 = 0U,   /*!< PMU retention byte 0 */   
    PMU_RETENTION_BYTE1 = 1U,   /*!< PMU retention byte 1 */
    PMU_RETENTION_BYTE2 = 2U,   /*!< PMU retention byte 2 */
    PMU_RETENTION_BYTE3 = 3U    /*!< PMU retention byte 3 */
} Pmu_RetentionByteType;

/**
 *  @brief PMU HVMON filter window type definition
 */
typedef enum
{
    PMU_HVMON_FILTER_WINDOW_20US = 0U,   /*!< PMU HVMON filter window 20us */   
    PMU_HVMON_FILTER_WINDOW_40US = 1U,   /*!< PMU HVMON filter window 40us */
} Pmu_HvmonFilterWindowType;

/** @} end of group Public_TypeDefinition */

/** @defgroup Global_VariableDeclaration
 *  @{
 */

/** @} end of group Global_VariableDeclaration */

/** @defgroup Public_FunctionDeclaration
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
Common_FlagStatusType Pmu_GetLpoClockReadyStatus(void);

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
void Pmu_DisableLpoClock(Common_ControlStateType Cmd);

/**
 * @brief      Clear Isolation status.
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void Pmu_ClearIsoStatus(void);

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
void Pmu_Ctrl(Pmu_CtrlType CtrlType, Common_ControlStateType Cmd);

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
Common_FlagStatusType Pmu_GetVarefCmpStatus(void);

/**
 * @brief      Pmu clear varef comparator output status.
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void Pmu_ClearVarefCmpStatus(void);

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
Common_FlagStatusType Pmu_GetLdoReadyStatus(Pmu_LdoType LdoType);

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
void Pmu_ConfigHvMon(Pmu_HvMonCfgType HvMonCfgType, Common_ControlStateType Cmd);

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
void Pmu_SelectHvMonFilterWindow(Pmu_HvmonFilterWindowType FilterWindowValue);

/**
 * @brief      PMU cyclic counter configuration function
 *
 * @param[in]  CycCntType: Cyclic counter type defined in Pmu_CycCntType.
 * @param[in]  CntValue: Cyclic counter value.
 *
 * @return     None
 *
 */
void Pmu_ConfigCycCnt(Pmu_CycCntType CycCntType, uint8 CntValue);

/**
 * @brief      PMU wakeup counter configuration function
 *
 * @param[in]  WkupCntType: Wakeup counter type defined in Pmu_WkupCntType.
 * @param[in]  CntValue: Wakeup counter value.
 *
 * @return     None
 *
 */
void Pmu_ConfigWkupCnt(Pmu_WkupCntType WkupCntType, uint8 CntValue);

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
void Pmu_ConfigLdo(Pmu_LdoCfgType CfgType, Common_ControlStateType Cmd);

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
Common_FlagStatusType Pmu_GetLdoStableStatus(Pmu_LdoType LdoType);

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
Common_FlagStatusType Pmu_GetLdoVoltageStatus(Pmu_LdoType LdoType);

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
void Pmu_EnableUvUnderActive(Pmu_VddUvType UvType, Common_ControlStateType Cmd);

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
void Pmu_EnableUvUnderStop(Pmu_VddUvType UvType, Common_ControlStateType Cmd);

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
void Pmu_ResetUv(Pmu_VddUvType UvType, Common_ControlStateType Cmd);

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
Common_FlagStatusType Pmu_GetUvStatus(Pmu_VddUvType UvType);

/**
 * @brief      Pmu clear LDO under voltage status.
 *
 * @param[in]  UvType: Select VDD under voltage type defined in Pmu_VddUvType.
 *
 * @return     None
 *
 */
void Pmu_ClearUvStatus(Pmu_VddUvType UvType);

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
void Pmu_EnableOvUnderActive(Pmu_VddOvType OvType, Common_ControlStateType Cmd);

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
void Pmu_EnableOvUnderStop(Pmu_VddOvType OvType, Common_ControlStateType Cmd);

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
Common_FlagStatusType Pmu_GetOvStatus(Pmu_VddOvType OvType);

/**
 * @brief      Pmu clear LDO over voltage status.
 *
 * @param[in]  OvType: Select VDD over voltage type defined in Pmu_VddOvType.
 *
 * @return     None
 *
 */
void Pmu_ClearOvStatus(Pmu_VddOvType OvType);

/**
 * @brief      Enable/Disable LDO over loading detect under active mode.
 *
 * @param[in]  OlType: Select VDD over loading type defined in Pmu_VddOlType.
 * @param[in]  Cmd: Enable or Disable.
 *               - COMMON_DISABLE: Disable.
 *               - COMMON_ENABLE: Enable.
 *
 * @return     None
 *
 */
void Pmu_EnableOlUnderActive(Pmu_VddOlType OlType, Common_ControlStateType Cmd);


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
void Pmu_EnableOlUnderStop(Pmu_VddOlType OlType, Common_ControlStateType Cmd);

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
Common_FlagStatusType Pmu_GetOlStatus(Pmu_VddOlType OlType);

/**
 * @brief      Pmu clear LDO over loading status.
 *
 * @param[in]  OlType: Select VDD over loading type defined in Pmu_VddOlType.
 *
 * @return     None
 *
 */
void Pmu_ClearOlStatus(Pmu_VddOlType OlType);
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
Common_FlagStatusType Pmu_GetShortStatus(Pmu_LdoType LdoType);

/**
 * @brief      Pmu clear LDO short status.
 *
 * @param[in]  LdoType: Select the PMU LDO type defined in Pmu_LdoType.
 *
 * @return     None
 *
 */
void Pmu_ClearShortStatus(Pmu_LdoType LdoType);

/**
 * @brief      PMU monitor filter select function.
 *
 * @param[in]  FilterType: Select monitor filtler type defined in Pmu_MonFilterType.
 * @param[in]  SelValue: Value to be selected.
 *
 * @return     None
 *
 */
void Pmu_SelectMonFilterWindow(Pmu_MonFilterType FilterType, uint32 SelValue);

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
void Pmu_ConfigStopStandbyReq(Pmu_StopStandbyReqType ReqType, Common_ControlStateType Cmd);

/**
 * @brief      Set PMU regfile0 retention bytes.
 *
 * @param[in]  RetType  : PMU retention bytes type.
 * @param[in]  RetValue : Retention value.
 *
 * @return     None
 *
 */
void Pmu_SetRegfile0RetentionBytes(Pmu_RetentionByteType RetType, uint8 RetValue);

/**
 * @brief      Read PMU regfile0 retention bytes.
 *
 * @param[in]  RetType  : PMU retention bytes type.
 *
 * @return     None
 *
 */
uint8 Pmu_ReadRegfile0RetentionBytes(Pmu_RetentionByteType RetType);

/**
 * @brief      Set PMU regfile1 retention bytes.
 *
 * @param[in]  RetType  : PMU retention bytes type.
 * @param[in]  RetValue : Retention value.
 *
 * @return     None
 *
 */
void Pmu_SetRegfile1RetentionBytes(Pmu_RetentionByteType RetType, uint8 RetValue);

/**
 * @brief      Read PMU regfile1 retention bytes.
 *
 * @param[in]  RetType  : PMU retention bytes type.
 *
 * @return     None
 *
 */
uint8 Pmu_ReadRegfile1RetentionBytes(Pmu_RetentionByteType RetType);

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
void Pmu_EnableCPRef1VBuffer(Common_ControlStateType Cmd);

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
void Pmu_EnableTemperatureSensor(Pmu_TsType TsType, Common_ControlStateType Cmd);

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
void Pmu_ConfigAtten(Pmu_AttenType AttenType, Common_ControlStateType Cmd);

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
Common_FlagStatusType Pmu_GetSysFailStatus(Pmu_SysFailType SysFailType);

/**
 * @brief      Pmu clear system failure status.
 *
 * @param[in]  SysFailType: Select system failure type defined in Pmu_SysFailType.
 *
 * @return     None
 *
 */
void Pmu_ClearSysFailStatus(Pmu_SysFailType SysFailType);

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
Common_FlagStatusType Pmu_GetWkTimIntStatus(void);

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
Common_FlagStatusType Pmu_GetHvMonIntStatus(void);

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
Common_FlagStatusType Pmu_GetVddExtFailIntStatus(Pmu_IntType IntType);

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
Common_FlagStatusType Pmu_GetIntStatus(Pmu_IntType IntType);

/**
 * @brief      MASK/UNMASK wakeup timer Interrupt Function.
 *
 * @param[in]  IntMask: UNMASK or MASK.
 *
 * @return     None
 *
 */
void Pmu_SetWkTimIntMask(Common_IntMaskType IntMask);

/**
 * @brief      MASK/UNMASK VDD exit fail Interrupt Function.
 *
 * @param[in]  IntType: Select the interrupt type.
 * @param[in]  IntMask: UNMASK or MASK.
 *
 * @return     None
 *
 */
void Pmu_SetVddExtFailIntMask(Pmu_IntType IntType, Common_IntMaskType IntMask);

/**
 * @brief      MASK/UNMASK high voltage monitor Interrupt Function.
 *
 * @param[in]  IntMask: UNMASK or MASK.
 *
 * @return     None
 *
 */
void Pmu_SetHvMonIntMask(Common_IntMaskType IntMask);

/**
 * @brief      MASK/UNMASK the Relevant Interrupt Function.
 *
 * @param[in]  IntType: Select the interrupt type.
 * @param[in]  IntMask: UNMASK or MASK.
 *
 * @return     None
 *
 */
void Pmu_SetIntMask(Pmu_IntType IntType, Common_IntMaskType IntMask);

/**
 * @brief      Clear the wakeup timer Interrupt Status.
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void Pmu_ClearWkTimInt(void);

/**
 * @brief      Clear the high voltage monitor Interrupt Status
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void Pmu_ClearHvMonInt(void);

/**
 * @brief      Clear the Relevant Interrupt Status.
 *
 * @param[in]  IntType: Select the interrupt type.
 *
 * @return     None
 *
 */
void Pmu_ClearInt(Pmu_IntType IntType);

/**
 * @brief      Install call back function.
 *
 * @param[in]  IntType: Select the interrupt type.
 * @param[in]  CallbackFun: Pointer to callback function.
 *
 * @return     None
 *
 */
void Pmu_InstallCallBackFunc(Pmu_IntType IntType, Isr_CbFuncType * CallbackFun);

/**
 * @brief      Pmu VDDEXT IRQ Handler.
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void Pmu_VddExtFailIrqHandler(void);

/**
 * @brief      Pmu IRQ Handler.
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void Pmu_DriverIrqHandler(void);

/**
 * @brief      Mon IRQ Handler.
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
void Pmu_Mon_DriverIrqHandler(void);

/** @} end of group Public_FunctionDeclaration */

#endif /* PMU_DRV_H */

