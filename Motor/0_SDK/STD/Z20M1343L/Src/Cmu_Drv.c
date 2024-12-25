/**************************************************************************************************/
/**
 * @file      : Cmu_Drv.c
 * @brief     : CMU module driver file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#include "Cmu_Drv.h"

/** @defgroup Private_MacroDefinition
 *  @{
 */

#define CMU_INT_BELOW_LOW_THRE_MASK    (1UL << 17U)
#define CMU_INT_ABOVE_HIGH_THRE_MASK   (1UL << 16U)
#define CMU_INT_ALL_MASK    (CMU_INT_BELOW_LOW_THRE_MASK | CMU_INT_ABOVE_HIGH_THRE_MASK)
#define CMU_CTRL_MASK       (0x00FFFFFFU)
#define CMU_UNLOCK_SEQUENCE (0x5B000000U)
#define SCM_WRITE_UNLOCK_SEQUENCE   (0x5A5A5A5AU)
#define SCM_WRITE_LOCK_SEQUENCE     (0xA5A5A5A5U)

/** @} end of Private_MacroDefinition */

/** @defgroup Private_TypeDefinition
 *  @{
 */

/** @} end of group Private_TypeDefinition */

/** @defgroup Global_VariableDefinition
 *  @{
 */
/*PRQA S 0303,0306 ++*/
static Reg_Cmu_BfType* const Cmu_RegBfPtr = (Reg_Cmu_BfType*)CMU_BASE_ADDR;/* CMU Register */
static Reg_Cmu_WType* const Cmu_RegWPtr = (Reg_Cmu_WType*)CMU_BASE_ADDR;   /* CMU Word Register */
static Reg_Scm_BfType *const Scm_RegBfPtr  = (Reg_Scm_BfType *) SCM_BASE_ADDR;  /*!< SCM Register */
static Reg_Scm_WType  *const Scm_RegWPtr = (Reg_Scm_WType *) SCM_BASE_ADDR;/*!< SCM Word Register */
/*PRQA S 0303,0306 --*/

static const uint32 Cmu_IntMaskTable[] =
{
    CMU_INT_BELOW_LOW_THRE_MASK,
    CMU_INT_ABOVE_HIGH_THRE_MASK, 
    CMU_INT_ALL_MASK                
};

/** @} end of group Global_VariableDefinition */

/** @defgroup Private_VariableDefinition
 *  @{
 */

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
 * @brief       Initializes the monitor mode of CMU peripheral. 
 *
 * @param[in]   MonitorConfig: points to the monitorMode configuration struct
 *
 * @return      none
 *
 */
void Cmu_InitMonitorMode(const Cmu_MonitorModeConfigType *MonitorConfig)
{
    /* make sure monitor is disabled before configuration */
    Cmu_Disable();
    
    Cmu_RegBfPtr->CMU_CTRL.FBLTIE = (uint32)MonitorConfig->BelowLowIntEn;
    Cmu_RegBfPtr->CMU_CTRL.FAHTIE = (uint32)MonitorConfig->AboveHighIntEn;
    
    Cmu_RegWPtr->CMU_CUMHCT4INT = MonitorConfig->IntHighThreshold;
    Cmu_RegWPtr->CMU_CUMLCT4INT = MonitorConfig->IntLowThreshold;
    Cmu_RegWPtr->CMU_MONWIN = MonitorConfig->MonitorWindow;
    
    /* set to monitor mode */
    Cmu_RegBfPtr->CMU_CTRL.CMMD = 0U;
}

/**
 * @brief       Initializes the measure mode of CMU peripheral. 
 *
 * @param[in]   MonitorWin: the monitor window value
 *
 * @return      none
 *
 */
void Cmu_InitMeasureMode(uint32 MonitorWin)
{   
    /* make sure monitor is disabled before configuration */
    Cmu_Disable();
    
    Cmu_RegWPtr->CMU_MONWIN = MonitorWin;
    
    /* set to measure mode */
    Cmu_RegBfPtr->CMU_CTRL.CMMD = 1U;
}

/**
 * @brief       Enable the CMU.
 *
 * @param[in]   Monitor: Select monitor to be enabled
 *
 * @return      none
 *
 */
void Cmu_Enable(Cmu_MonitorType Monitor)
{   
    if (Scm_RegWPtr->SCM_WRITE_LOCK != SCM_WRITE_UNLOCK_SEQUENCE)
    {
        /* unlock */
        Scm_RegWPtr->SCM_WRITE_LOCK = SCM_WRITE_UNLOCK_SEQUENCE;
    }
    /* Select pointed Monitor */
    Scm_RegBfPtr->SCM_MISCCTL1.SCM_CMU_CFG = (uint32)Monitor;
    /* lock */
    Scm_RegWPtr->SCM_WRITE_LOCK = SCM_WRITE_LOCK_SEQUENCE;

    if (Cmu_RegBfPtr->CMU_CTRL.LOCK != 0U)
    {
        /* unlock */
        Cmu_RegWPtr->CMU_CTRL = (CMU_UNLOCK_SEQUENCE | (Cmu_RegWPtr->CMU_CTRL & CMU_CTRL_MASK));
    }
    
    Cmu_RegBfPtr->CMU_CTRL.CME = 1U;
    
    /* lock CMU_CTRL register */
    Cmu_RegBfPtr->CMU_CTRL.LOCK = 1U;
}

/**
 * @brief       Disable the CMU. 
 *
 * @param[in]   none
 *
 * @return      none
 *
 */
void Cmu_Disable(void)
{   
    if (Cmu_RegBfPtr->CMU_CTRL.LOCK != 0U)
    {
        /* unlock */
        Cmu_RegWPtr->CMU_CTRL = (CMU_UNLOCK_SEQUENCE | (Cmu_RegWPtr->CMU_CTRL & CMU_CTRL_MASK));
    }
    
    Cmu_RegBfPtr->CMU_CTRL.CME = 0U;
    
    /* lock CMU_CTRL register */
    Cmu_RegBfPtr->CMU_CTRL.LOCK = 1U;
}

/**
 * @brief       Start the measure mode. 
 *
 * @param[in]   none
 *
 * @return      none
 *
 */
void Cmu_StartMeasure(void)
{
    Cmu_RegBfPtr->CMU_STAT.STARTMEA = 1U;
}

/**
 * @brief       Get the measure complete status. 
 *
 * @param[in]   none
 *
 * @return      measure status
 * @retval      CMU_MEASURE_COMPLETED: measure completed
 * @retval      CMU_MEASURE_UNCOMPLETED: measure uncompleted
 * 
 */
Cmu_MeasureCompleteType Cmu_GetMeasureCompleteStatus(void)
{
    return ((Cmu_MeasureCompleteType)Cmu_RegBfPtr->CMU_STAT.STARTMEA);
}

/**
 * @brief       Read measure result when CMU is working in measure mode. User 
 *              needs to make sure the measure is completed before calling this 
 *              function, otherwise, the return value is incorrect.
 *
 * @param[in]   none
 *
 * @return      measure result
 *
 */
uint32 Cmu_ReadMeasureResult(void)
{
    return (Cmu_RegWPtr->CMU_CUMMEARSLT);
}

/**
 * @brief       Get the CMU state. 
 *
 * @param[in]   none
 *
 * @return      the CMU state
 * @retval      CMU_STATE_UPDATABLE: CMU configuration can be updated
 * @retval      CMU_STATE_LOCKED:    CMU configuration is locked
 * @retval      CMU_STATE_RUNNING:   CMU is running 
 *
 */
Cmu_StateType Cmu_GetState(void)
{
    return ((Cmu_StateType)(Cmu_RegBfPtr->CMU_STAT.MONST));
}

/**
 * @brief       Mask/Unmask interrupt.
 *
 * @param[in]   IntType: select interrupt type
 * @param[in]   IntMask: MASK/UNMASK
 *
 * @return      none
 *
 */
void Cmu_SetIntMask(Cmu_IntType IntType, Common_IntMaskType IntMask)
{   
    if (COMMON_UNMASK == IntMask)
    {
        Cmu_RegWPtr->CMU_CTRL |= Cmu_IntMaskTable[IntType];
    }
    else
    {
        Cmu_RegWPtr->CMU_CTRL &= ~Cmu_IntMaskTable[IntType];
    }
}

/**
 * @brief       Clear interrupt.
 *
 * @param[in]   IntType: select interrupt type
 *
 * @return      none
 *
 */
void Cmu_ClearIntFlag(Cmu_IntType IntType)
{
    Cmu_RegWPtr->CMU_STAT = Cmu_IntMaskTable[IntType];
}

/**
 * @brief       Get interrupt status.
 *
 * @param[in]   IntType: select interrupt type
 *
 * @return      interrupt status
 * @retval      SET: The interrupt flag is set
 * @retval      RESET: The interrupt flag is clear
 *
 */
Common_IntStatusType Cmu_GetIntStatus(Cmu_IntType IntType)
{
    Common_IntStatusType Status;

    Status = COMMON_RESET;
    if ( (Cmu_RegWPtr->CMU_STAT & Cmu_IntMaskTable[IntType]) != 0U)
    {
        Status = COMMON_SET;
    }

    return Status;
}

/** @} end of group Public_FunctionDefinition */
