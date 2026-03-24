/**************************************************************************************************/
/**
 * @file     cmu_drv.c
 * @brief    CMU module driver file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 *
 **************************************************************************************************/

#include "cmu_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @defgroup CMU
 *  @brief CMU driver modules
 *  @{
 */

/** @defgroup CMU_Private_Type
 *  @{
 */


/** @} end of group CMU_Private_Type*/

/** @defgroup CMU_Private_Defines
 *  @{
 */
#define CMU_NUM  (3U)

#define CMU_INT_BELOW_LOW_THRE_MASK    (1UL << 17U)
#define CMU_INT_ABOVE_HIGH_THRE_MASK   (1UL << 16U)
#define CMU_INT_ALL_MASK    (CMU_INT_BELOW_LOW_THRE_MASK | CMU_INT_ABOVE_HIGH_THRE_MASK)
#define CMU_CTRL_MASK       (0x00FFFFFFU)
#define CMU_UNLOCK_SEQUENCE (0x5B000000U)

/** @} end of group CMU_Private_Defines */

/** @defgroup CMU_Private_Variables
 *  @{
 */
/*PRQA S 0303 ++*/
static cmu_reg_t * const cmuRegPtr[CMU_NUM] = 
{
    (cmu_reg_t *)CMU0_BASE_ADDR,
    (cmu_reg_t *)CMU1_BASE_ADDR,
    (cmu_reg_t *)CMU2_BASE_ADDR
};

static cmu_reg_w_t * const cmuRegWPtr[CMU_NUM] = 
{
    (cmu_reg_w_t *)CMU0_BASE_ADDR,
    (cmu_reg_w_t *)CMU1_BASE_ADDR,
    (cmu_reg_w_t *)CMU2_BASE_ADDR
};
/*PRQA S 0303 --*/

static isr_cb_t * cmuIsrCbFunc[CMU_NUM][CMU_INT_ALL] =
{
    {NULL, NULL},
    {NULL, NULL},
    {NULL, NULL}
}; 

static const uint32_t CMU_InterruptMaskTable[] =
{
    CMU_INT_BELOW_LOW_THRE_MASK,
    CMU_INT_ABOVE_HIGH_THRE_MASK, 
    CMU_INT_ALL_MASK                
};
/** @} end of group CMU_Private_Variables */

/** @defgroup CMU_Global_Variables
 *  @{
 */

/** @} end of group CMU_Global_Variables */

/** @defgroup CMU_Private_FunctionDeclaration
 *  @{
 */


/** @} end of group CMU_Private_FunctionDeclaration */

/** @defgroup CMU_Private_Functions
 *  @{
 */
/**
 * @brief      CMU interrupt Handler
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
static void CMU_IntHandler(CMU_Id_t id)
{
    cmu_reg_w_t * CMUxw = cmuRegWPtr[id];
    uint32_t status;
    
    status = (CMU_InterruptMaskTable[CMU_INT_ALL]) & (CMUxw->CMU_CTRL);
    status &= (CMUxw->CMU_STAT);
    /* clear interrupt status */
    CMUxw->CMU_STAT = status;    
    
    /* handle CMU_INT_BELOW_LOW_THRE */
    if((status & CMU_InterruptMaskTable[CMU_INT_BELOW_LOW_THRE]) != 0U)
    {
        if(cmuIsrCbFunc[id][CMU_INT_BELOW_LOW_THRE] != NULL)
        {
            cmuIsrCbFunc[id][CMU_INT_BELOW_LOW_THRE]();
        }
        else
        {
            CMU_IntMask(id, CMU_INT_BELOW_LOW_THRE, MASK);
        }
    }
    
    /* handle CMU_INT_ABOVE_HIGH_THRE */
    if((status & CMU_InterruptMaskTable[CMU_INT_ABOVE_HIGH_THRE]) != 0U)
    {
        if(cmuIsrCbFunc[id][CMU_INT_ABOVE_HIGH_THRE] != NULL)
        {
            cmuIsrCbFunc[id][CMU_INT_ABOVE_HIGH_THRE]();
        }
        else
        {
            CMU_IntMask(id, CMU_INT_ABOVE_HIGH_THRE, MASK);
        }
    }    
}
/** @} end of group CMU_Private_Functions */

/** @defgroup CMU_Public_Functions
 *  @{
 */

void CMU0_DriverIRQHandler(void);
void CMU1_DriverIRQHandler(void);
void CMU2_DriverIRQHandler(void);

/**
 * @brief      Initializes the monitor mode of CMU peripheral. 
 *
 * @param[in]  id: select the CMU ID
 * @param[in]  config: points to the monitorMode configuration struct
 *
 * @return     none
 *
 */
void CMU_MonitorModeInit(CMU_Id_t id, const CMU_MonitorModeConfig_t *config)
{
    cmu_reg_t * CMUx = (cmu_reg_t *)(cmuRegPtr[id]);
    cmu_reg_w_t * CMUxw = cmuRegWPtr[id];
    
    /* make sure monitor is disabled before configuration */
    CMU_Disable(id);
    
    CMUx->CMU_CTRL.FBLTIE = (uint32_t)config->belowLowThresholdIntEn;
    CMUx->CMU_CTRL.FAHTIE = (uint32_t)config->aboveHighThresholdIntEn;
    CMUx->CMU_CTRL.FBLTRSTE = (uint32_t)config->belowLowThresholdResetEn;
    CMUx->CMU_CTRL.FAHTRSTE = (uint32_t)config->aboveHighThresholdResetEn;
    
    CMUxw->CMU_CUMHCT4INT = config->intHighThreshold;
    CMUxw->CMU_CUMLCT4INT = config->intLowThreshold;
    CMUxw->CMU_CUMHCT4RST = config->resetHighThreshold;
    CMUxw->CMU_CUMLCT4RST = config->resetLowThreshold;
    CMUxw->CMU_MONWIN = config->monitorWindow;
    
    /* set to monitor mode */
    CMUx->CMU_CTRL.CMMD = 0U;
}

/**
 * @brief      Initializes the measure mode of CMU peripheral. 
 *
 * @param[in]  id: select the CMU ID
 * @param[in]  monitorWin: the monitor window value
 *
 * @return     none
 *
 */
void CMU_MeasureModeInit(CMU_Id_t id, uint32_t monitorWin)
{
    cmu_reg_t * CMUx = (cmu_reg_t *)(cmuRegPtr[id]);
    cmu_reg_w_t * CMUxw = cmuRegWPtr[id];
    
    /* make sure monitor is disabled before configuration */
    CMU_Disable(id);
    
    CMUxw->CMU_MONWIN = monitorWin;
    
    /* set to measure mode */
    CMUx->CMU_CTRL.CMMD = 1U;
}

/**
 * @brief      Enable the CMU. 
 *
 * @param[in]  id: select the CMU ID
 *
 * @return     none
 *
 */
void CMU_Enable(CMU_Id_t id)
{
    cmu_reg_t * CMUx = (cmu_reg_t *)(cmuRegPtr[id]);
    cmu_reg_w_t * CMUxw = cmuRegWPtr[id];
    
    if(CMUx->CMU_CTRL.LOCK != 0U)
    {
        /* unlock */
        CMUxw->CMU_CTRL = (CMU_UNLOCK_SEQUENCE | (CMUxw->CMU_CTRL & CMU_CTRL_MASK));
    }
    
    CMUx->CMU_CTRL.CME = 1U;
    
    /* lock CMU_CTRL register */
    CMUx->CMU_CTRL.LOCK = 1U;
}

/**
 * @brief      Disable the CMU. 
 *
 * @param[in]  id: select the CMU ID
 *
 * @return     none
 *
 */
void CMU_Disable(CMU_Id_t id)
{
    cmu_reg_t * CMUx = (cmu_reg_t *)(cmuRegPtr[id]);
    cmu_reg_w_t * CMUxw = cmuRegWPtr[id];
    
    if(CMUx->CMU_CTRL.LOCK != 0U)
    {
        /* unlock */
        CMUxw->CMU_CTRL = (CMU_UNLOCK_SEQUENCE | (CMUxw->CMU_CTRL & CMU_CTRL_MASK));
    }
    
    CMUx->CMU_CTRL.CME = 0U;
    
    /* lock CMU_CTRL register */
    CMUx->CMU_CTRL.LOCK = 1U;
}

/**
 * @brief      Start the measure mode. 
 *
 * @param[in]  id: select the CMU ID
 *
 * @return     none
 *
 */
void CMU_StartMeasure(CMU_Id_t id)
{
    cmu_reg_w_t * CMUxw = cmuRegWPtr[id];

    CMUxw->CMU_STAT |= 0x10U;
}

/**
 * @brief      Get the measure complete status. 
 *
 * @param[in]  id: select the CMU ID
 *
 * @return     - SET: measure is completed
 *             - RESET: measure is not completed
 *
 */
FlagStatus_t CMU_GetMeasureCompleteStatus(CMU_Id_t id)
{
    cmu_reg_t * CMUx = (cmu_reg_t *)(cmuRegPtr[id]);

    return (FlagStatus_t)(0U == CMUx->CMU_STAT.STARTMEA);
}

/**
 * @brief      Read measure result when CMU is working in measure mode. User 
 *             needs to make sure the measure is completed before calling this 
 *             function, otherwise, the return value is incorrect.
 *
 * @param[in]  id: select the CMU ID
 *
 * @return     measure result
 *
 */
uint32_t CMU_ReadMeasureResult(CMU_Id_t id)
{
    cmu_reg_w_t * CMUxw = cmuRegWPtr[id];
    
    return (CMUxw->CMU_CUMMEARSLT);
}

/**
 * @brief      Get the CMU state. 
 *
 * @param[in]  id: select the CMU ID
 *
 * @return     the CMU state
 *
 */
CMU_State_t CMU_GetState(CMU_Id_t id)
{
    cmu_reg_t * CMUx = (cmu_reg_t *)(cmuRegPtr[id]);
    
    return (CMU_State_t)(CMUx->CMU_STAT.MONST);
}

/**
 * @brief      Mask/Unmask interrupt
 *
 * @param[in]  id: select the CMU ID
 * @param[in]  intType: select interrupt type
 * @param[in]  intMask: MASK/UNMASK
 *
 * @return    none
 *
 */
void CMU_IntMask(CMU_Id_t id, CMU_Int_t intType, IntMask_t intMask)
{
    cmu_reg_w_t * CMUxw = cmuRegWPtr[id];
    
    if(UNMASK == intMask)
    {
        CMUxw->CMU_CTRL |= CMU_InterruptMaskTable[intType];
    }
    else
    {
        CMUxw->CMU_CTRL &= ~CMU_InterruptMaskTable[intType];
    }
}

/**
 * @brief      Clear interrupt
 *
 * @param[in]  id: select the CMU ID
 * @param[in]  intType: select interrupt type
 *
 * @return    none
 *
 */
void CMU_IntClear(CMU_Id_t id, CMU_Int_t intType)
{
    cmu_reg_w_t * CMUxw = cmuRegWPtr[id];
    
    CMUxw->CMU_STAT = CMU_InterruptMaskTable[intType];
}

/**
 * @brief      Get interrupt status
 *
 * @param[in]  id: select the CMU ID
 * @param[in]  intType: select interrupt type
 *
 * @return    
 *          - SET
 *          - RESET
 *
 */
IntStatus_t CMU_GetIntStatus(CMU_Id_t id, CMU_Int_t intType)
{
    cmu_reg_w_t * CMUxw = cmuRegWPtr[id];
    uint32_t cmuStatus = CMUxw->CMU_STAT;
    IntStatus_t ret = RESET;

    if ((cmuStatus & CMU_InterruptMaskTable[intType]) != 0U)
    {
        ret = SET;
    }

    return ret;
}

/**
 * @brief      CMU0 IRQHandler
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CMU0_DriverIRQHandler(void)
{
    CMU_IntHandler(CMU_ID_0);
    COMMON_DSB();
}

/**
 * @brief      CMU1 IRQHandler
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CMU1_DriverIRQHandler(void)
{
    CMU_IntHandler(CMU_ID_1);
    COMMON_DSB();
}

/**
 * @brief      CMU2 IRQHandler
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CMU2_DriverIRQHandler(void)
{
    CMU_IntHandler(CMU_ID_2);
    COMMON_DSB();
}

/**
 * @brief      Install cmu interrupt callback function
 *
 * @param[in]  id: select the CMU ID
 * @param[in]  intType: select interrupt type 
 * @param[in]  cbFun: indicate callback function
 *
 * @return    none
 *
 */ 
void CMU_InstallCallBackFunc(CMU_Id_t id, CMU_Int_t intType, 
                             isr_cb_t * const cbFun)
{
    if (intType < CMU_INT_ALL)
    {
        cmuIsrCbFunc[id][intType] = cbFun;
    }
}

/** @} end of group CMU_Public_Functions */

/** @} end of group CMU */

/** @} end of group Z20K14XM_Peripheral_Driver */
