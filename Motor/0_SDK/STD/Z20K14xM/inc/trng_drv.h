/**************************************************************************************************/
/**
 * @file     trng_drv.h
 * @brief    TRNG driver module header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#ifndef TRNG_DRV_H
#define TRNG_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  TRNG
 *  @{
 */

/** @defgroup TRNG_Public_Types 
 *  @{
 */

/*! @brief trng status type definition
 * Implements : TRNG_Status_t_Class
 */
typedef enum 
{
    TRNG_CTRDRBG_READY = 0U,                /*!< TRNG IP is ready to accept a new operation */
    TRNG_CTRDRBG_INSTANTIATED,              /*!< CTR-DRBG is instantiated */
    TRNG_ALARM_VALID,                       /*!< Alarms are available on register TRNG_ALARM */
    TRNG_CTRDRBGALARM_VALID                 /*!< Alarms are available on register CTR_DRBG_ALARM */
} TRNG_Status_t;

/*! @brief ctr-drbg operation type definition 
 * Implements : TRNG_CtrDrbgOpt_t_Class
 */
typedef enum 
{
    TRNG_CTRDRBGOPT_GENERATE      = 0x0U,   /*!< generate operation */
    TRNG_CTRDRBGOPT_INSTANTIATE,            /*!< instantiate operation */
    TRNG_CTRDRBGOPT_HEALTHTEST,             /*!< health test */
    TRNG_CTRDRBGOPT_UNINSTANTIATE,          /*!< uninstantiate operation */
    TRNG_CTRDRBGOPT_RESEED,                 /*!< reseed operation */
    TRNG_CTRDRBGOPT_ALARMACK                /*!< acknowledge ctr-drbg alarm */
} TRNG_CtrDrbgOpt_t;

/*! @brief trng alarm type definition
 * Implements : TRNG_Alarm_t_Class
 */
typedef enum 
{
    TRNG_ALARM_MONOBITTEST        = 0U,     /*!< Monobit test alarm result */
    TRNG_ALARM_POKERTEST,                   /*!< poker test alarm result */
    TRNG_ALARM_RUNTEST,                     /*!< run test alarm result */
    TRNG_ALARM_LONGRUNTEST,                 /*!< Long run test alarm result */
    TRNG_ALARM_ALL                          /*!< all alarm test result */
} TRNG_Alarm_t;

/*! @brief ctr-drbg alarm type definition
 * Implements : TRNG_CtrDrbgAlarm_t_Class
 */
typedef enum 
{
    TRNG_CTRDRBGALARM_INSTANTIATE = 0U,     /*!< instantiate function alarm result */
    TRNG_CTRDRBGALARM_RESEED,               /*!< reseed function alarm result */
    TRNG_CTRDRBGALARM_GENERATE,             /*!< generate function alarm result */
    TRNG_CTRDRBGALARM_ALL                   /*!< all ctr-drbg alarm result */
} TRNG_CtrDrbgAlarm_t;

/**  
 *  @brief trng interrupt type definition
 */
typedef enum
{
    TRNG_INT_TMO                 = 0U,     /*!< timeout interrupt */
    TRNG_INT_RD,                           /*!< random data ready interrupt */
    TRNG_INT_TA,                           /*!< TRNG alarm interrupt */
    TRNG_INT_DA,                           /*!< DRBG alarm interrupt */
    TRNG_INT_ALL                           /*!< all alarm interrupt */
} TRNG_INT_t;

/*! @brief trng timeout status type definition
 * Implements : TRNG_TmoStatus_Class
 */
typedef enum 
{
    TRNG_TMOMOD_READY            = 0U,     /*!< Timeout module is not operating and is ready */
    TRNG_TMOMOD_OVER,                      /*!< Timeout module has finished its last operation */
    TRNG_TMOMOD_ERR                        /*!< Timeout is reached, and no random data has been delivered */
} TRNG_TmoStatus_t;

/*! @brief trng noise source type definition
 * Implements : TRNG_NoiseSrc_t_Class
 */
typedef enum 
{
    TRNG_NOISESRC_DISABLE       = 0U,     /*!< no source is enabled */
    TRNG_NOISESRC1_ENABLE,                /*!< noise source 1 is enabled */
    TRNG_NOISESRC2_ENABLE,                /*!< noise source 2 is enabled */
    TRNG_NOISESRCALL_ENABLE               /*!< both noise sources are enabled */
} TRNG_NoiseSrc_t;

/*! @brief noise measurement status type definition
 * Implements : TRNG_NoiseMeasStatus_t_Class
 */
typedef enum 
{
    TRNG_NOISEMEAS_READY       = 0U,     /*!< noise measurement operation is ready to start */
    TRNG_NOISEMEAS_OVER                  /*!< noise measurement operation is over */
} TRNG_NoiseMeasStatus_t;

/*!
 * @brief trng configuration.
 * Implements : TRNG_Config_t_Class
 */
typedef struct 
{
    ControlState_t ctrDrbgEnable;          /*!< CTR-DRBG enable */
    ControlState_t streamModeEnable;       /*!< Stream mode enable */
    uint16_t decimationParam;              /*!< Decimation parameter */
    uint8_t latencyParam;                  /*!< Latency parameter */
} TRNG_Config_t;

/*!
 * @brief trng additional configuration.
 * Implements : TRNG_AdditionalConfig_t_Class
 */
typedef struct 
{
    ControlState_t monobitTestIgnore;     /*!< cryptographic algorithm type */
    ControlState_t pokerTestIgnore;       /*!< cryptographic algorithm type */
    ControlState_t runTestIgnore;         /*!< cryptographic algorithm type */
    ControlState_t longRunTestIgnore;     /*!< cryptographic algorithm type */
    ControlState_t manualCtrlEnable;      /*!< cryptographic algorithm type */
    ControlState_t rawDataRecordEnable;   /*!< cryptographic algorithm type */
    ControlState_t monobitTestEnable;     /*!< cryptographic algorithm type */
    ControlState_t pokerTestEnable;       /*!< cryptographic algorithm type */
    ControlState_t runTestEnable;         /*!< cryptographic algorithm type */
    ControlState_t longRunTestEnable;     /*!< cryptographic algorithm type */
    ControlState_t noiseModEnable;        /*!< cryptographic algorithm type */
} TRNG_AdditionalConfig_t;

/*!
 * @brief noise measurement configuration.
 * Implements : TRNG_NoiseMeasConfig_t_Class
 */
typedef struct 
{
    TRNG_NoiseSrc_t noiseSrc;             /*!< noise measurement selection */
    uint32_t measCycle;                   /*!< noise measurement time */
} TRNG_NoiseMeasConfig_t;

/** @} end of group TRNG_Public_Types */

/** @defgroup TRNG_Public_Constants
 *  @{
 */

/** @} end of group TRNG_Public_Constants */

/** @defgroup TRNG_Public_Macro
 *  @{
 */

/** @} end of group TRNG_Public_Macro */


/** @defgroup TRNG_Public_FunctionDeclaration
 *  @brief TRNG functions declaration
 *  @{
 */

/**
 * @brief      trng config Function
 *
 * @param[in]  config:   Pointer to trng configuration structure.
 *
 * @return     ret: -SUCC: trng config success.
 *                  -ERR: Config pointer is NULL.
 *
 */
ResultStatus_t TRNG_Config(const TRNG_Config_t * config);

/**
 * @brief      get trng status Function
 *
 * @param[in]  status:     trng status type.
 *
 * @return whether trng status is asserted or not.
 *
 */
FlagStatus_t TRNG_GetStatus(TRNG_Status_t status);

/**
 * @brief      trng ctr-drbg operate Function
 *
 * @param[in]  operation:   ctr-drbg operation type.
 *
 * @return none
 *
 */
void TRNG_CtrDrbgOpt(TRNG_CtrDrbgOpt_t operation);

/**
 * @brief      set requeset number size of ctr-drbg Function
 *
 * @param[in]  size:  means the number of requested 128-bit words is size + 1.
 *
 * @return none
 *
 */
void TRNG_SetCtrDrbgRequestSize(uint16_t size);

/**
 * @brief      set number of generate requests between two reseeds Function
 *
 * @param[in]  num:  means the number of generate requests is num + 1.
 *
 * @return none
 *
 */
void TRNG_SetGenReqNumBetweenReseed(uint32_t num);

/**
 * @brief      set number of random generations between two periodic
 *             health tests Function
 *
 * @param[in]  num:  means the number of random generations between two periodic
 *                   health tests is num + 1.
 *
 * @return none
 *
 */
void TRNG_SetGenRandNumBetweenHealthTest(uint32_t num);

/**
 * @brief      get trng alarm status Function
 *
 * @param[in]  status:     trng alarm status type.
 *
 * @return whether trng alarm status is asserted or not.
 *
 */
FlagStatus_t TRNG_GetAlarmStatus(TRNG_Alarm_t status);

/**
 * @brief      get ctr-drbg alarm status Function
 *
 * @param[in]  status:     trng alarm status type.
 *
 * @return whether trng alarm status is asserted or not.
 *
 */
FlagStatus_t TRNG_GetCtrDrbgAlarmStatus(TRNG_CtrDrbgAlarm_t status);

/**
 * @brief      Flush the raw data fifo Function
 *
 * @param[in]  none.
 *
 * @return none
 *
 */
void TRNG_FlushRawDataFifo(void);

/**
 * @brief      get trng raw random data Function
 *
 * @param[out] rawData:  Point to the trng raw random data.
 *
 * @return     stat: -SUCC: Get raw random data successfully.
 *                   -ERR: Failed to get raw random data.
 *
 */
ResultStatus_t TRNG_GetRawRandData(uint16_t *rawData);

/**
 * @brief      get ctr-drbg random data Function
 *
 * @param[out] drbgData:  Point to the ctr-drbg random data.
 *
 * @return     stat: -SUCC: Get ctr-drbg random data successfully.
 *                   -ERR: Failed to get ctr-drbg random data.
 *
 */
ResultStatus_t TRNG_GetCtrDrbgRandData(uint16_t *drbgData);

/**
 * @brief      trng additional config Function
 *
 * @param[in]  config:   Pointer to trng additional configuration structure.
 *
 * @return     ret: -SUCC: Additional config success.
 *                  -ERR: Config pointer is NULL.
 *
 */
ResultStatus_t TRNG_AdditionalConfig(const TRNG_AdditionalConfig_t * config);

/**
 * @brief      start noise measurement  Function
 *
 * @param[in]  none.
 *
 * @return none
 *
 */
void TRNG_StartNoiseMeas(void);

/**
 * @brief      noise measurement config Function
 *
 * @param[in]  config:   Pointer to noise measurement configuration structure.
 *
 * @return     ret: -SUCC: Noise measurement config success.
 *                  -ERR: Config pointer is NULL.
 *
 */
ResultStatus_t TRNG_NoiseMeasConfig(const TRNG_NoiseMeasConfig_t * config);

/**
 * @brief      get noise measurement status Function
 *
 * @param[in]  status:    noise measurement status type.
 *
 * @return whether status is asserted or not.
 *
 */
FlagStatus_t TRNG_GetNoiseMeasStatus(TRNG_NoiseMeasStatus_t status);

/**
 * @brief      get noise measurement data 0 Function
 *
 * @param[in]  none.
 *
 * @return noise measurement data 0
 *
 */
uint32_t TRNG_GetNoiseMeasData0(void);

/**
 * @brief      get noise measurement data 1 Function
 *
 * @param[in]  none.
 *
 * @return noise measurement data 1
 *
 */
uint32_t TRNG_GetNoiseMeasData1(void);

/**
 * @brief      set int mask Function
 *
 * @param[in]  intType: int type
 *                      - TRNG_INT_TMO: timeout interrupt
 *                      - TRNG_INT_RD: random data ready interrupt
 *                      - TRNG_INT_TA: TRNG alarm interrupt
 *                      - TRNG_INT_DA: DRBG alarm interrupt 
 *                      - TRNG_INT_ALL: all interrupt
 * @param[in]  intMask: int mask
 *
 * @return none.
 *
 */
void TRNG_IntMask(TRNG_INT_t intType, IntMask_t intMask);

/**
 * @brief      get trng int flag Function
 *
 * @param[in]  intType: int type
 *                      - TRNG_INT_TMO: timeout interrupt
 *                      - TRNG_INT_RD: random data ready interrupt
 *                      - TRNG_INT_TA: TRNG alarm interrupt
 *                      - TRNG_INT_DA: DRBG alarm interrupt 
 *
 * @return whether a int is asserted or not.
 *
 */
FlagStatus_t TRNG_GetIntStatus(TRNG_INT_t intType);

/**
 * @brief      clear trng int flag Function
 *
 * @param[in]  intType: int type
 *                      - TRNG_INT_TMO: timeout interrupt
 *                      - TRNG_INT_RD: random data ready interrupt
 *                      - TRNG_INT_TA: TRNG alarm interrupt
 *                      - TRNG_INT_DA: DRBG alarm interrupt 
 *                      - TRNG_INT_ALL: all interrupt
 *
 * @return none.
 *
 */
void TRNG_ClearIntStatus(TRNG_INT_t intType);

/**
 * @brief      start timeout counting Function
 *
 * @param[in]  none.
 *
 * @return none.
 *
 */
void TRNG_StartTmoCount(void);

/**
 * @brief      configure the timeout value Function
 *
 * @param[in]  tmo:  timeout value.
 *
 * @return none
 *
 */
void TRNG_SetTmoValue(uint32_t tmo);

/**
 * @brief      get timeout status Function
 *
 * @param[in]  status:     timeout status type.
 *
 * @return whether timeout status is asserted or not.
 *
 */
FlagStatus_t TRNG_GetTmoStatus(TRNG_TmoStatus_t status);

/**
 * @brief      reset the monitoring feature counters Function
 *
 * @param[in]  none.
 *
 * @return none
 *
 */
void TRNG_ResetMonitorCount(void);

/**
 * @brief      enable the monitoring feature Function
 *
 * @param[in]  cmd: monitoring feature control
 *                  - ENABLE: Enable the monitoring feature
 *                  - DISABLE: disable the monitoring feature
 *
 * @return none
 *
 */
void TRNG_MonitorControl(ControlState_t cmd);

/**
 * @brief      get monitor count data Function
 *
 * @param[out]  ev: Point to the number of sequences that
 *                  have been evaluated by the embedded test
 * @param[out]  pa: Point to the number of sequences that
 *                  have passed the embedded test
 *
 * @return      ret: -SUCC: Successfully get monitor count data.
 *                   -ERR: Pointer is NULL.
 *
 */
ResultStatus_t TRNG_GetMonitorCount(uint16_t * ev, uint16_t * pa);

/**
 * @brief      Install callback function
 *
 * @param[in]  intType: int type
 *                      - TRNG_INT_TMO: timeout interrupt
 *                      - TRNG_INT_RD: random data ready interrupt
 *                      - TRNG_INT_TA: TRNG alarm interrupt
 *                      - TRNG_INT_DA: DRBG alarm interrupt 
 * @param[in]  cbFun: indicate callback function
 *
 * @return    ret: -ERR: 1.Callback function pointer is NULL.
 *                       2.Callbcak function is out of type.
 *                 -SUCC: Successfully install the callback function.
 *
 */ 
ResultStatus_t TRNG_InstallCallBackFunc(TRNG_INT_t intType, isr_cb_t * const cbFun);

/** @} end of group TRNG_Public_FunctionDeclaration */

/** @} end of group TRNG  */

/** @} end of group Z20K14XM_Peripheral_Driver */

#endif  /* TRNG_DRV_H */
