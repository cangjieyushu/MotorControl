/**************************************************************************************************/
/**
 * @file     trng_drv.c
 * @brief    TRNG module driver file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#include "trng_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @defgroup TRNG
 *  @brief TRNG driver modules
 *  @{
 */

/** @defgroup TRNG_Private_Defines
 *  @{
 */

#define TRNG_CONFIG_EN_MASK           (0x00000001U)
#define TRNG_CONFIG_SM_MASK           (0x00000002U)
#define TRNG_CONFIG_DEC_MASK          (0x00003FF0U)
#define TRNG_CONFIG_LP_MASK           (0x0007C000U)

#define TRNG_CONFIG_EN_SHIFT          (0U)
#define TRNG_CONFIG_SM_SHIFT          (1U)
#define TRNG_CONFIG_DEC_SHIFT         (4U)
#define TRNG_CONFIG_LP_SHIFT          (14U)

#define TRNG_ADDCONFIG_I0_MASK        (0x00000001U)
#define TRNG_ADDCONFIG_I1_MASK        (0x00000002U)
#define TRNG_ADDCONFIG_I2_MASK        (0x00000004U)
#define TRNG_ADDCONFIG_I3_MASK        (0x00000008U)
#define TRNG_ADDCONFIG_MC_MASK        (0x00000010U)
#define TRNG_ADDCONFIG_RE_MASK        (0x00000020U)
#define TRNG_ADDCONFIG_E0_MASK        (0x00000040U)
#define TRNG_ADDCONFIG_E1_MASK        (0x00000080U)
#define TRNG_ADDCONFIG_E2_MASK        (0x00000100U)
#define TRNG_ADDCONFIG_E3_MASK        (0x00000200U)
#define TRNG_ADDCONFIG_SE_MASK        (0x00000400U)

#define TRNG_ADDCONFIG_I0_SHIFT       (0U)
#define TRNG_ADDCONFIG_I1_SHIFT       (1U)
#define TRNG_ADDCONFIG_I2_SHIFT       (2U)
#define TRNG_ADDCONFIG_I3_SHIFT       (3U)
#define TRNG_ADDCONFIG_MC_SHIFT       (4U)
#define TRNG_ADDCONFIG_RE_SHIFT       (5U)
#define TRNG_ADDCONFIG_E0_SHIFT       (6U)
#define TRNG_ADDCONFIG_E1_SHIFT       (7U)
#define TRNG_ADDCONFIG_E2_SHIFT       (8U)
#define TRNG_ADDCONFIG_E3_SHIFT       (9U)
#define TRNG_ADDCONFIG_SE_SHIFT       (10U)

#define TRNG_RAWRND_VA_MASK           (0x00010000U)
#define TRNG_RAWRND_DATA_MASK         (0x0000FFFFU)

#define TRNG_RAWRND_VA_SHIFT          (16U)
#define TRNG_RAWRND_DATA_SHIFT        (0U)

#define TRNG_RAWCTRDRBGRND_VA_MASK    (0x00010000U)
#define TRNG_RAWCTRDRBGRND_DATA_MASK  (0x0000FFFFU)

#define TRNG_RAWCTRDRBGRND_VA_SHIFT   (16U)
#define TRNG_RAWCTRDRBGRND_DATA_SHIFT (0U)

#define TRNG_STATSDATA_EV_MASK        (0x0000FFFFU)
#define TRNG_STATSDATA_PA_MASK        (0xFFFF0000U)
        
#define TRNG_STATSDATA_EV_SHIFT       (0U)
#define TRNG_STATSDATA_PA_SHIFT       (16U)



#define TRNG_CONFIG_EN_SET(x) \
        ((uint32_t)(x) & TRNG_CONFIG_EN_MASK)
        
#define TRNG_CONFIG_SM_SET(x) \
        (((uint32_t)(((uint32_t)(x)) << TRNG_CONFIG_SM_SHIFT)) & TRNG_CONFIG_SM_MASK)
        
#define TRNG_CONFIG_DEC_SET(x) \
        (((uint32_t)(((uint32_t)(x)) << TRNG_CONFIG_DEC_SHIFT)) & TRNG_CONFIG_DEC_MASK)
        
#define TRNG_CONFIG_LP_SET(x) \
        (((uint32_t)(((uint32_t)(x)) << TRNG_CONFIG_LP_SHIFT)) & TRNG_CONFIG_LP_MASK)


#define TRNG_ADDCONFIG_I0_SET(x) \
        ((uint32_t)(x) & TRNG_ADDCONFIG_I0_MASK)
        
#define TRNG_ADDCONFIG_I1_SET(x) \
        (((uint32_t)(((uint32_t)(x)) << TRNG_ADDCONFIG_I1_SHIFT)) & TRNG_ADDCONFIG_I1_MASK)
        
#define TRNG_ADDCONFIG_I2_SET(x) \
        (((uint32_t)(((uint32_t)(x)) << TRNG_ADDCONFIG_I2_SHIFT)) & TRNG_ADDCONFIG_I2_MASK)
                
#define TRNG_ADDCONFIG_I3_SET(x) \
        (((uint32_t)(((uint32_t)(x)) << TRNG_ADDCONFIG_I3_SHIFT)) & TRNG_ADDCONFIG_I3_MASK)

#define TRNG_ADDCONFIG_MC_SET(x) \
        (((uint32_t)(((uint32_t)(x)) << TRNG_ADDCONFIG_MC_SHIFT)) & TRNG_ADDCONFIG_MC_MASK)
        
#define TRNG_ADDCONFIG_RE_SET(x) \
        (((uint32_t)(((uint32_t)(x)) << TRNG_ADDCONFIG_RE_SHIFT)) & TRNG_ADDCONFIG_RE_MASK)
        
#define TRNG_ADDCONFIG_E0_SET(x) \
        (((uint32_t)(((uint32_t)(x)) << TRNG_ADDCONFIG_E0_SHIFT)) & TRNG_ADDCONFIG_E0_MASK)
                
#define TRNG_ADDCONFIG_E1_SET(x) \
        (((uint32_t)(((uint32_t)(x)) << TRNG_ADDCONFIG_E1_SHIFT)) & TRNG_ADDCONFIG_E1_MASK)

#define TRNG_ADDCONFIG_E2_SET(x) \
        (((uint32_t)(((uint32_t)(x)) << TRNG_ADDCONFIG_E2_SHIFT)) & TRNG_ADDCONFIG_E2_MASK)
        
#define TRNG_ADDCONFIG_E3_SET(x) \
        (((uint32_t)(((uint32_t)(x)) << TRNG_ADDCONFIG_E3_SHIFT)) & TRNG_ADDCONFIG_E3_MASK)
                
#define TRNG_ADDCONFIG_SE_SET(x) \
        (((uint32_t)(((uint32_t)(x)) << TRNG_ADDCONFIG_SE_SHIFT)) & TRNG_ADDCONFIG_SE_MASK)


/** @} end of group TRNG_Private_Defines */


/** @defgroup TRNG_Private_Type
 *  @{
 */

/** @} end of group TRNG_Private_Type*/



/** @defgroup TRNG_Private_Variables
 *  @{
 */

/*PRQA S 0303 ++*/
static trng_reg_t *const trngRegPtr = (trng_reg_t *) TRNG_BASE_ADDR;
static trng_reg_w_t *const trngRegWPtr = (trng_reg_w_t *) TRNG_BASE_ADDR;
/*PRQA S 0303 --*/ 

/*! @brief TRNG ISR CallBack VECTOR structure */
static isr_cb_t * trngIsrCb[TRNG_INT_ALL] = 
{
    NULL, NULL, NULL, NULL
};

/*! @brief TRNG int mask array */
static const uint32_t trngIntMask[] = 
{
    0x00000001U,
    0x00000002U,
    0x00000004U,
    0x00000008U,
    0x0000000FU
};


/** @} end of group TRNG_Private_Variables */

/** @defgroup TRNG_Global_Variables
 *  @{
 */

/** @} end of group TRNG_Global_Variables */

/** @defgroup TRNG_Private_FunctionDeclaration
 *  @{
 */
void TRNG_DriverIRQHandler(void);

/** @} end of group TRNG_Private_FunctionDeclaration */

/** @defgroup TRNG_Private_Functions
 *  @{
 */

/** @} end of group TRNG_Private_Functions */


/** @defgroup TRNG_Public_Functions
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
ResultStatus_t TRNG_Config(const TRNG_Config_t * config)
{
    ResultStatus_t ret = ERR;
    if(NULL != config)
    {
        trngRegWPtr->TRNG_CONFIG = TRNG_CONFIG_EN_SET(config->ctrDrbgEnable) |
                         TRNG_CONFIG_SM_SET(config->streamModeEnable) |
                         TRNG_CONFIG_DEC_SET(config->decimationParam) |
                         TRNG_CONFIG_LP_SET(config->latencyParam);
        ret = SUCC;
    }
    else 
    {
        /* Do nothing. */
    }
    return ret;
}

/**
 * @brief      get trng status Function
 *
 * @param[in]  status:     trng status type.
 *
 * @return whether trng status is asserted or not.
 *
 */
FlagStatus_t TRNG_GetStatus(TRNG_Status_t status)
{
    FlagStatus_t stat = RESET;
    uint32_t trngStatus = trngRegWPtr->TRNG_STATUS;

    if (((trngStatus >> (uint32_t)status) & 0x1U) == 0x1U)
    {
        stat = SET;
    }

    return stat;
}

/**
 * @brief      trng ctr-drbg operate Function
 *
 * @param[in]  operation:   ctr-drbg operation type.
 *
 * @return none
 *
 */
void TRNG_CtrDrbgOpt(TRNG_CtrDrbgOpt_t operation)
{
    trngRegWPtr->TRNG_CTR_DRBG_CONTROL = 0x1UL << (uint32_t)operation;
}

/**
 * @brief      set aes operation input data Function
 *
 * @param[in]  size:  means the number of requested 128-bit words is size + 1.
 *
 * @return none
 *
 */
void TRNG_SetCtrDrbgRequestSize(uint16_t size)
{
    trngRegWPtr->TRNG_CTR_DRBG_REQUEST_SIZE = size;
}

/**
 * @brief      set number of generate requests between two reseeds Function
 *
 * @param[in]  num:  means the number of generate requests is num + 1.
 *
 * @return none
 *
 */
void TRNG_SetGenReqNumBetweenReseed(uint32_t num)
{
    trngRegWPtr->TRNG_CTR_DRBG_CONFIG_1 = num;
}

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
void TRNG_SetGenRandNumBetweenHealthTest(uint32_t num)
{
    trngRegWPtr->TRNG_CTR_DRBG_CONFIG_2 = num;
}

/**
 * @brief      get trng alarm status Function
 *
 * @param[in]  status:     trng alarm status type.
 *
 * @return whether trng alarm status is asserted or not.
 *
 */
FlagStatus_t TRNG_GetAlarmStatus(TRNG_Alarm_t status)
{
    FlagStatus_t stat = RESET;
    uint32_t alarmStatus = trngRegWPtr->TRNG_ALARM;

    if (((alarmStatus >> (uint32_t)status) & 0x1U) == 0x1U)
    {
        stat = SET;
    }

    return stat;
}

/**
 * @brief      get trng alarm status Function
 *
 * @param[in]  status:     trng alarm status type.
 *
 * @return whether trng alarm status is asserted or not.
 *
 */
FlagStatus_t TRNG_GetCtrDrbgAlarmStatus(TRNG_CtrDrbgAlarm_t status)
{
    FlagStatus_t stat = RESET;
    uint32_t drbgAlarm = trngRegWPtr->TRNG_CTR_DRBG_ALARM;

    if (0x1U == ((drbgAlarm >> (uint32_t)status) & 0x1U))
    {
        stat = SET;
    }

    return stat;
}

/**
 * @brief      Flush the raw data fifo Function
 *
 * @param[in]  none.
 *
 * @return none
 *
 */
void TRNG_FlushRawDataFifo(void)
{
    trngRegWPtr->TRNG_RAW_RANDOM_CONTROL = 0x1U;
}

/**
 * @brief      get trng raw random data Function
 *
 * @param[out] rawData:  Point to the trng raw random data.
 *
 * @return     stat: -SUCC: Get raw random data successfully.
 *                   -ERR: Failed to get raw random data.
 *
 */
ResultStatus_t TRNG_GetRawRandData(uint16_t *rawData)
{
    uint32_t regValue;
    ResultStatus_t stat = ERR;
    volatile uint32_t count = 0U;
    regValue = trngRegWPtr->TRNG_RAW_RANDOM_DATA;
    if(NULL != rawData)
    {
        while ((count < TRNG_TIMEOUT_WAIT_CNT) && (0U == (regValue & TRNG_RAWRND_VA_MASK)))
        {           
            regValue = trngRegWPtr->TRNG_RAW_RANDOM_DATA;
            count++;
        }
        if(0U != (regValue & TRNG_RAWCTRDRBGRND_VA_MASK))
        {
            *rawData = (uint16_t)(regValue & TRNG_RAWRND_DATA_MASK);
            stat = SUCC;
        }
    }    
    return stat;
}

/**
 * @brief      get ctr-drbg random data Function
 *
 * @param[out] drbgData:  Point to the ctr-drbg random data.
 *
 * @return     stat: -SUCC: Get ctr-drbg random data successfully.
 *                   -ERR: Failed to get ctr-drbg random data.
 *
 */
ResultStatus_t TRNG_GetCtrDrbgRandData(uint16_t *drbgData)
{
    uint32_t regValue;
    ResultStatus_t stat = ERR;
    regValue = trngRegWPtr->TRNG_CTR_DRBG_RANDOM_DATA;
    volatile uint32_t count = 0U;
    if(NULL != drbgData)
    {
        while ((count < TRNG_TIMEOUT_WAIT_CNT) && (0U == (regValue & TRNG_RAWCTRDRBGRND_VA_MASK)))
        {           
            regValue = trngRegWPtr->TRNG_CTR_DRBG_RANDOM_DATA;
            count++;
        }
        if(0U != (regValue & TRNG_RAWCTRDRBGRND_VA_MASK))
        {
            *drbgData = (uint16_t)(regValue & TRNG_RAWCTRDRBGRND_DATA_MASK);
            stat = SUCC;
        }
    } 
    return stat;
}

/**
 * @brief      trng additional config Function
 *
 * @param[in]  config:   Pointer to trng additional configuration structure.
 *
 * @return     ret: -SUCC: Additional config success.
 *                   -ERR: Config pointer is NULL.
 *
 */
ResultStatus_t TRNG_AdditionalConfig(const TRNG_AdditionalConfig_t * config)
{
    ResultStatus_t ret = ERR;
    if(NULL != config)
    {
        trngRegWPtr->TRNG_ADDITIONAL_CONFIG_0 = TRNG_ADDCONFIG_I0_SET(config->monobitTestIgnore) |
                                                TRNG_ADDCONFIG_I1_SET(config->pokerTestIgnore) |
                                                TRNG_ADDCONFIG_I2_SET(config->runTestIgnore) |
                                                TRNG_ADDCONFIG_I3_SET(config->longRunTestIgnore) |
                                                TRNG_ADDCONFIG_MC_SET(config->manualCtrlEnable) |
                                                TRNG_ADDCONFIG_RE_SET(config->rawDataRecordEnable) |
                                                TRNG_ADDCONFIG_E0_SET(config->monobitTestEnable) |
                                                TRNG_ADDCONFIG_E1_SET(config->pokerTestEnable) |
                                                TRNG_ADDCONFIG_E2_SET(config->runTestEnable) |
                                                TRNG_ADDCONFIG_E3_SET(config->longRunTestEnable) |
                                                TRNG_ADDCONFIG_SE_SET(config->noiseModEnable);
        trngRegWPtr->TRNG_ADDITIONAL_CONFIG_1 = 0x400U;
        trngRegWPtr->TRNG_ADDITIONAL_CONFIG_2 = 0xFFFFFFFFU;
        ret = SUCC;
    }
    return ret;
}

/**
 * @brief      start noise measurement  Function
 *
 * @param[in]  none.
 *
 * @return none
 *
 */
void TRNG_StartNoiseMeas(void)
{
    trngRegWPtr->TRNG_ADDITIONAL_MEAS_CONTROL = 0x1U;
}

/**
 * @brief      noise measurement config Function
 *
 * @param[in]  config:   Pointer to noise measurement configuration structure.
 *
 * @return     ret: -SUCC: Noise measurement config success.
 *                  -ERR: Config pointer is NULL.
 *
 */
ResultStatus_t TRNG_NoiseMeasConfig(const TRNG_NoiseMeasConfig_t * config)
{
    ResultStatus_t ret = ERR;
    if(NULL != config)
    {
        trngRegPtr->TRNG_ADDITIONAL_MEAS_CONFIG.SEL = (uint32_t)config->noiseSrc;
        trngRegPtr->TRNG_ADDITIONAL_MEAS_CONFIG.TIME = config->measCycle;
        ret = SUCC;
    } 
    return ret;
}

/**
 * @brief      get noise measurement status Function
 *
 * @param[in]  status:    noise measurement status type.
 *
 * @return whether status is asserted or not.
 *
 */
FlagStatus_t TRNG_GetNoiseMeasStatus(TRNG_NoiseMeasStatus_t status)
{
    FlagStatus_t stat = RESET;
    uint32_t meaStatus = trngRegWPtr->TRNG_ADDITIONAL_MEAS_STATUS;

    if (0x1U == ((meaStatus >> (uint32_t)status) & 0x1U))
    {
        stat = SET;
    }

    return stat;
}

/**
 * @brief      get noise measurement data 0 Function
 *
 * @param[in]  none.
 *
 * @return noise measurement data 0
 *
 */
uint32_t TRNG_GetNoiseMeasData0(void)
{
    return trngRegWPtr->TRNG_ADDITIONAL_MEAS_DATA_0;
}

/**
 * @brief      get noise measurement data 1 Function
 *
 * @param[in]  none.
 *
 * @return noise measurement data 1
 *
 */
uint32_t TRNG_GetNoiseMeasData1(void)
{
    return trngRegWPtr->TRNG_ADDITIONAL_MEAS_DATA_1;
}

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
void TRNG_IntMask(TRNG_INT_t intType, IntMask_t intMask)
{
    if (UNMASK == intMask)
    {
        trngRegWPtr->TRNG_IRQ_CONFIG |= trngIntMask[intType];
    }
    else
    {
        trngRegWPtr->TRNG_IRQ_CONFIG &= ~trngIntMask[intType];
    }
}

/**
 * @brief      get trng alarm int flag Function
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
FlagStatus_t TRNG_GetIntStatus(TRNG_INT_t intType)
{
    FlagStatus_t stat = RESET;
    uint32_t irqStatus;
    
    if (intType < TRNG_INT_ALL)
    {
        irqStatus = trngRegWPtr->TRNG_IRQ_STATUS;
        if (0x1U == ((irqStatus >> (uint32_t)intType) & 0x1U))
        {
            stat = SET;
        }
    }

    return stat;
}

/**
 * @brief      clear trng alarm int flag Function
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
void TRNG_ClearIntStatus(TRNG_INT_t intType)
{
    trngRegWPtr->TRNG_IRQ_CLEAR = trngIntMask[intType];
}

/**
 * @brief      start timeout counting Function
 *
 * @param[in]  none.
 *
 * @return none.
 *
 */
void TRNG_StartTmoCount(void)
{
    trngRegWPtr->TRNG_ERROR_CONTROL = 0x1U;
}

/**
 * @brief      configure the timeout value Function
 *
 * @param[in]  tmo:  timeout value.
 *
 * @return none
 *
 */
void TRNG_SetTmoValue(uint32_t tmo)
{
    trngRegWPtr->TRNG_ERROR_CONFIG = tmo;
}

/**
 * @brief      get timeout status Function
 *
 * @param[in]  status:     timeout status type.
 *
 * @return whether timeout status is asserted or not.
 *
 */
FlagStatus_t TRNG_GetTmoStatus(TRNG_TmoStatus_t status)
{
    FlagStatus_t stat = RESET;
    
    if (0x1U == ((trngRegWPtr->TRNG_ERROR_STATUS >> (uint32_t)status) & 0x1U))
    {
        stat = SET;
    }
    
    return stat;
}

/**
 * @brief      reset the monitoring feature counters Function
 *
 * @param[in]  none.
 *
 * @return none
 *
 */
void TRNG_ResetMonitorCount(void)
{
    trngRegWPtr->TRNG_STATS_CONTROL = 0x1U;
}

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
void TRNG_MonitorControl(ControlState_t cmd)
{
    trngRegPtr->TRNG_STATS_CONFIG.MO = (uint32_t)cmd;
}

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
ResultStatus_t TRNG_GetMonitorCount(uint16_t * ev, uint16_t * pa)
{
    ResultStatus_t ret = ERR;
    if((NULL != ev) && (NULL != pa))
    {
        uint32_t regValue;
        regValue = trngRegWPtr->TRNG_STATS_DATA;
        *ev = (uint16_t)(regValue & TRNG_STATSDATA_EV_MASK);
        *pa = (uint16_t)((regValue & TRNG_STATSDATA_PA_MASK) >> TRNG_STATSDATA_PA_SHIFT);
        ret = SUCC;
    }
    return ret;
}

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
ResultStatus_t TRNG_InstallCallBackFunc(TRNG_INT_t intType, isr_cb_t * const cbFun)
{    
    ResultStatus_t ret = ERR;
    if(NULL != cbFun)
    {
        if (intType < TRNG_INT_ALL)
        {
            trngIsrCb[intType] = cbFun;
            ret = SUCC;
        } 
    }
    return ret;
}

/**
 * @brief      trng interrupt handle
 *
 * @param[in]  none
 *
 * @return     none
 *
 */
void TRNG_DriverIRQHandler(void)
{
    uint32_t status;

    status = trngRegWPtr->TRNG_IRQ_STATUS & trngIntMask[TRNG_INT_ALL];
    status &= trngRegWPtr->TRNG_IRQ_CONFIG;

    /* clear irq flag */
    trngRegWPtr->TRNG_IRQ_CLEAR = status;
    
    if (0U != (status & 0x1U))
    {
        if (NULL != trngIsrCb[TRNG_INT_TMO])
        {
            trngIsrCb[TRNG_INT_TMO]();
        }
        else
        {
            trngRegWPtr->TRNG_IRQ_CONFIG &= ~trngIntMask[TRNG_INT_TMO];
        }
    }

    if (0U != ((status  >> (uint32_t)TRNG_INT_RD) & 0x1U))
    {
        if (NULL != trngIsrCb[TRNG_INT_RD])
        {
            trngIsrCb[TRNG_INT_RD]();
        }
        else
        {
            trngRegWPtr->TRNG_IRQ_CONFIG &= ~trngIntMask[TRNG_INT_RD];
        }
    }

    if (0U != ((status  >> (uint32_t)TRNG_INT_TA & 0x1U)))
    {
        if (NULL != trngIsrCb[TRNG_INT_TA])
        {
            trngIsrCb[TRNG_INT_TA]();
        }
        else
        {
            trngRegWPtr->TRNG_IRQ_CONFIG &= ~trngIntMask[TRNG_INT_TA];
        }
    }

    if (0U != ((status  >> (uint32_t)TRNG_INT_DA) & 0x1U))
    {
        if (NULL != trngIsrCb[TRNG_INT_DA])
        {
            trngIsrCb[TRNG_INT_DA]();
        }
        else
        {
            trngRegWPtr->TRNG_IRQ_CONFIG &= ~trngIntMask[TRNG_INT_DA];
        }
    }

    COMMON_DSB();
}

/** @} end of group TRNG_Public_Functions */

/** @} end of group TRNG driver modules */

/** @} end of group Z20K14XM_Peripheral_Driver */
