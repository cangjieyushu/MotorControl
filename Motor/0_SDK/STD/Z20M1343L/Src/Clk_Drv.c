/**************************************************************************************************/
/**
 * @file      : Clk_Drv.c
 * @brief     : Clk module driver file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
#include "Clk_Drv.h"

/** @defgroup Private_MacroDefinition
 *  @{
 */

#define PMU_UNLOCK_SEQUENCE          (0x94730000U)
#define SCC_INTFLAG_MASK             (0x00040000U)
#define SCC_LOCK_SEQUENCE            (0x80000000U)
#define SCC_UNLOCK_SEQUENCE          (0x5B000000U)
#define SCM_REGISTER_UNLOCK_SEQUENCE (0x5A5A5A5AU)
#define SCM_REGISTER_LOCK_SEQUENCE   (0xA5A5A5A5U)
#define SCM_PERICTRL_UNLOCK_SEQUENCE (0x5B000000U)

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
 *  @brief SCM Register address array
 */
/*PRQA S 0303 ++*/
static Reg_Scm_BfType * const Scm_RegBfPtr = (Reg_Scm_BfType *)SCM_BASE_ADDR;
static Reg_Scm_WType * const Scm_RegWPtr = (Reg_Scm_WType *)SCM_BASE_ADDR;
/*PRQA S 0303 --*/

/**
 *  @brief SCC Register address array
 */
/*PRQA S 0303 ++*/
static Reg_Scc_BfType * const Scc_RegBfPtr = (Reg_Scc_BfType *)SCC_BASE_ADDR;
static Reg_Scc_WType * const Scc_RegWPtr = (Reg_Scc_WType *)SCC_BASE_ADDR;
/*PRQA S 0303 --*/

/**
 *  @brief PMU Register address array
 */
/*PRQA S 0303 ++*/
static Reg_Pmu_BfType * const Pmu_RegBfPtr = (Reg_Pmu_BfType *)PMU_BASE_ADDR;
static Reg_Pmu_WType * const Pmu_RegWPtr = (Reg_Pmu_WType *)PMU_BASE_ADDR;
/*PRQA S 0303 --*/

/** @} end of group Private_VariableDefinition */

/** @defgroup Private_FunctionDeclaration
 *  @{
 */

LOCAL_INLINE void Clk_UnlockScmRegister(void);
LOCAL_INLINE void Clk_LockScmRegister(void);

static uint32 Clk_GetSysClkFreq(uint32 OscFreq);

/** @} end of group Private_FunctionDeclaration */

/** @defgroup Private_FunctionDefinition
 *  @{
 */

/**
 * @brief      Unlock SCM writing registers.
 * 
 * @param[in]  none
 *
 * @return     none
 *
 */
LOCAL_INLINE void Clk_UnlockScmRegister(void)
{
    if (Scm_RegWPtr->SCM_WRITE_LOCK != SCM_REGISTER_UNLOCK_SEQUENCE)
    {
        Scm_RegWPtr->SCM_WRITE_LOCK = SCM_REGISTER_UNLOCK_SEQUENCE;
    }
}

/**
 * @brief      Lock SCM writing registers.
 * 
 * @param[in]  none
 *
 * @return     none
 *
 */
LOCAL_INLINE void Clk_LockScmRegister(void)
{
    Scm_RegWPtr->SCM_WRITE_LOCK = SCM_REGISTER_LOCK_SEQUENCE;
}

/**
 * @brief       get system clock frequency before divider.
 *
 * @param[in]   OscFreq: frequency of the OSC clock.
 *
 * @return      The clock frequency. If return 0, there is some error.
 *
 */
static uint32 Clk_GetSysClkFreq(uint32 OscFreq)
{
    uint32 Freq;
    
    Freq = 0U;
    if (2U == Scc_RegBfPtr->SCC_CST.SCS)
    {
        Freq = OscFreq;
    }
    else if (1U == Scc_RegBfPtr->SCC_CST.SCS)
    {
        Freq = 48000000U;
    }
    else
    {
        /* nothing to do */
    }

    return Freq;
}

/** @} end of group Private_FunctionDefinition */

/** @defgroup Public_FunctionDefinition
 *  @{
 */

/**
 * @brief       Config and enable FRO48M clock.
 *
 * @param[in]   StopModeEn:  Enable/Disable FIRC48M in stop mode.
 *
 * @return      clock enable status:
 *              - COMMON_ERR  - error;
 *              - COMMON_SUCC - success.
 */
Common_ResultStatusType Clk_EnableFro48m(Common_ControlStateType StopModeEn)
{
    uint32 RegVal;

    if (Scc_RegBfPtr->SCC_FRO48MCS.LOCK != 0U)
    {
        /* unlock this register */
        Scc_RegWPtr->SCC_FRO48MCS = SCC_UNLOCK_SEQUENCE;
    }
    /* Mask flag bit */
    RegVal = (Scc_RegWPtr->SCC_FRO48MCS & ~SCC_INTFLAG_MASK);
    /* Set the stop mode enable status and Enable FRO48M clock */
    RegVal &= (~0x2UL);
    RegVal |= (((uint32)StopModeEn<<1U) | 0x1U) ;
    /* lock this register */
    Scc_RegWPtr->SCC_FRO48MCS = (RegVal | SCC_LOCK_SEQUENCE);

    return Clk_WaitClkReady(CLK_FRO48M);
}

/**
 * @brief       Config and enable OSC24M clock.
 *
 * @param[in]  Mode: select OSC24M work and frequency mode.
 * @param[in]  StopModeEn:  Enable/Disable OSC24M in stop mode.
 *
 * @return      clock enable status:
 *              - COMMON_ERR  - error;
 *              - COMMON_SUCC - success.
 */
Common_ResultStatusType Clk_EnableOsc24m(Clk_OscModeType Mode, 
                                         Common_ControlStateType StopModeEn)
{
    uint32 RegVal;
    
    if (Scc_RegBfPtr->SCC_OSCCFG.LOCK != 0U)
    {
        /* unlock this register */
        Scc_RegWPtr->SCC_OSCCFG = SCC_UNLOCK_SEQUENCE;
    }
    Scc_RegBfPtr->SCC_OSCCFG.EXCLKS = (((uint32)Mode >> 3U) & 0x1U);
    Scc_RegBfPtr->SCC_OSCCFG.HF_MODE = (((uint32)Mode >> 2U) & 0x1U);
    Scc_RegBfPtr->SCC_OSCCFG.ITRIM = ((uint32)Mode & 0x3U);
    Scc_RegBfPtr->SCC_OSCCFG.OLMEN = 1U;
    /* lock registers */
    Scc_RegBfPtr->SCC_OSCCFG.LOCK = 1U;

    if (Scc_RegBfPtr->SCC_OSCCS.LOCK != 0U)
    {
        /* unlock this register */
        Scc_RegWPtr->SCC_OSCCS = SCC_UNLOCK_SEQUENCE;
    }
    /* Mask flag bit */
    RegVal = (Scc_RegWPtr->SCC_OSCCS & ~SCC_INTFLAG_MASK);
    /* Set stop mode enable status and Enable OSC clock */
    RegVal &= (~0x2UL);
    RegVal |= (((uint32)StopModeEn<<1U)| 1U);
    /* lock registers */
    Scc_RegWPtr->SCC_OSCCS = (RegVal | SCC_LOCK_SEQUENCE);

    return Clk_WaitClkReady(CLK_OSC24M);
}

/**
 * @brief       Select system clock.
 *
 * @param[in]   ClkSrc: select the clock source.
 *
 * @return      Select result:
 *              - COMMON_SUCC: the system clock is selected successfully;
 *              - COMMON_ERR: fail.
 * @note        The selected clock source has to be ready
 *              before call this function.
 *
 */
Common_ResultStatusType Clk_SetSysClk(Clk_SystemSrcType ClkSrc)
{
    Common_ResultStatusType Status;

    Status = COMMON_SUCC;
    if (CLK_SYS_FRO48M == ClkSrc)
    {
        if (Clk_WaitClkReady(CLK_FRO48M) != COMMON_SUCC)
        {
            Status = COMMON_ERR;
        }
        else
        {
            if (Scc_RegBfPtr->SCC_CFG.LOCK != 0U)
            {
                /* unlock this register */
                Scc_RegWPtr->SCC_CFG = SCC_UNLOCK_SEQUENCE;
            }
            /* select sys clock source */
            Scc_RegWPtr->SCC_CFG = (Scc_RegWPtr->SCC_CFG & 0xFFF8FFFFU) | (1UL << 16U);

            Scc_RegBfPtr->SCC_CFG.LOCK = 1U;
        }

    }
    else if (CLK_SYS_OSC24M == ClkSrc)
    {
        if (Clk_WaitClkReady(CLK_OSC24M) != COMMON_SUCC)
        {
            Status = COMMON_ERR;
        }
        else
        {
            if (Scc_RegBfPtr->SCC_CFG.LOCK != 0U)
            {
                /* unlock this register */
                Scc_RegWPtr->SCC_CFG = SCC_UNLOCK_SEQUENCE;
            }
            /* select sys clock source */
            Scc_RegWPtr->SCC_CFG = (Scc_RegWPtr->SCC_CFG & 0xFFF8FFFFU) | (1UL << 17U);

            Scc_RegBfPtr->SCC_CFG.LOCK = 1;
        }
    }
    else
    {
        Status = COMMON_ERR;
    }

    return Status;
}

/**
 * @brief       Get system clock source.
 *
 * @param[in]   none.
 *
 * @return      clock source:
 *              - CLK_SYS_FIRC48M
 *              - CLK_SYS_OSC24M
 *
 */
Clk_SystemSrcType Clk_GetSysClk(void)
{
    Clk_SystemSrcType ClkSrc;

    if ((uint32)CLK_SYS_OSC24M == Scc_RegBfPtr->SCC_CST.SCS)
    {
        ClkSrc = CLK_SYS_OSC24M;
    }
    else
    {
        ClkSrc = CLK_SYS_FRO48M;
    }

    return ClkSrc;
}

/**
 * @brief       Disable FIRC48M clock.
 *
 * @param[in]   none.
 *
 * @return      Result status:
 *              COMMON_SUCC - disable success.
 *              COMMON_ERR  - trying to disable current system clock.
 */
Common_ResultStatusType Clk_DisableFro48m(void)
{
    uint32 RegVal;
    Common_ResultStatusType Status;

    Status = COMMON_SUCC;
    if (CLK_SYS_FRO48M == Clk_GetSysClk())
    {
        Status = COMMON_ERR;
    }
    else
    {
        if (Scc_RegBfPtr->SCC_FRO48MCS.LOCK != 0U)
        {
            /* unlock this register */
            Scc_RegWPtr->SCC_FRO48MCS = SCC_UNLOCK_SEQUENCE;
        }
        /* Mask flag bit */
        RegVal = (Scc_RegWPtr->SCC_FRO48MCS & ~SCC_INTFLAG_MASK);
        /* Disable FRO48M clock */
        RegVal &= (~0x1UL);
        /* lock this register */
        Scc_RegWPtr->SCC_FRO48MCS = (RegVal | SCC_LOCK_SEQUENCE);
    }

    return Status;
}

/**
 * @brief       Disable OSC24M clock.
 *
 * @param[in]   none.
 *
 * @return      Result status:
 *              COMMON_SUCC - disable success.
 *              COMMON_ERR  - trying to disable current system clock.
 */
Common_ResultStatusType Clk_DisableOsc24m(void)
{
    uint32 RegVal;
    Common_ResultStatusType Status;

    Status = COMMON_SUCC;
    if (CLK_SYS_OSC24M == Clk_GetSysClk())
    {
        Status = COMMON_ERR;
    }
    else
    {
        if (Scc_RegBfPtr->SCC_OSCCS.LOCK != 0U)
        {
            /* unlock this register */
            Scc_RegWPtr->SCC_OSCCS = SCC_UNLOCK_SEQUENCE;
        }
        /* Mask flag bit */
        RegVal = (Scc_RegWPtr->SCC_OSCCS & ~SCC_INTFLAG_MASK);
        /* Disable OSC clock */
        RegVal &= (~1UL);
        /* Lock */
        Scc_RegWPtr->SCC_OSCCS = (RegVal | SCC_LOCK_SEQUENCE);

        if (Scc_RegBfPtr->SCC_OSCCFG.LOCK != 0U)
        {
            /* unlock this register */
            Scc_RegWPtr->SCC_OSCCFG = SCC_UNLOCK_SEQUENCE;
        }
        Scc_RegBfPtr->SCC_OSCCFG.OLMEN = 0U;
        /* lock */
        Scc_RegBfPtr->SCC_OSCCFG.LOCK = 1U;
    }

    return Status;
}

/**
 * @brief       Enable OSC24M loss of clock monitor.
 *
 * @param[in]   none.
 *
 * @return      none.
 *
 */
void Clk_EnableOsc24mMonitor(void)
{
    uint32 RegVal;

    if (Scc_RegBfPtr->SCC_OSCCS.LOCK != 0U)
    {
        /* unlock this register */
        Scc_RegWPtr->SCC_OSCCS = SCC_UNLOCK_SEQUENCE;
    }
    /* Mask flag bit */
    RegVal = (Scc_RegWPtr->SCC_OSCCS & ~SCC_INTFLAG_MASK);
    /* Enable OSC24M Monitor */
    RegVal |= (0x200U);
    /* Lock */
    Scc_RegWPtr->SCC_OSCCS = (RegVal | SCC_LOCK_SEQUENCE);
}

/**
 * @brief       Disable OSC24M loss of clock monitor.
 *
 * @param[in]   none.
 *
 * @return      none.
 *
 */
void Clk_DisableOsc24mMonitor(void)
{
    uint32 RegVal;

    if (Scc_RegBfPtr->SCC_OSCCS.LOCK != 0U)
    {
        /* unlock this register */
        Scc_RegWPtr->SCC_OSCCS = SCC_UNLOCK_SEQUENCE;
    }
    /* Mask flag bit */
    RegVal = (Scc_RegWPtr->SCC_OSCCS & ~SCC_INTFLAG_MASK);
    /* Disable OSC24M Monitor */
    RegVal &= (~0x200U);
    /* Lock */
    Scc_RegWPtr->SCC_OSCCS = (RegVal | SCC_LOCK_SEQUENCE);
}

/**
 * @brief       Enable FRO48M loss of clock monitor.
 *
 * @param[in]   none.
 *
 * @return      none.
 *
 */
void Clk_EnableFro48mMonitor(void)
{
    uint32 RegVal;

    if (Scc_RegBfPtr->SCC_FRO48MCS.LOCK != 0U)
    {
        /* unlock this register */
        Scc_RegWPtr->SCC_FRO48MCS = SCC_UNLOCK_SEQUENCE;
    }
    /* Mask flag bit */
    RegVal = (Scc_RegWPtr->SCC_FRO48MCS & ~SCC_INTFLAG_MASK);
    /* Enable FRO48M Monitor */
    RegVal |= (0x200U);
    /* lock this register */
    Scc_RegWPtr->SCC_FRO48MCS = (RegVal | SCC_LOCK_SEQUENCE);
}

/**
 * @brief       Disable FIRC48M loss of clock monitor.
 *
 * @param[in]   none.
 *
 * @return      none.
 *
 */
void Clk_DisableFro48mMonitor(void)
{
    uint32 RegVal;

    if (Scc_RegBfPtr->SCC_FRO48MCS.LOCK != 0U)
    {
        /* unlock this register */
        Scc_RegWPtr->SCC_FRO48MCS = SCC_UNLOCK_SEQUENCE;
    }
    /* Mask flag bit */
    RegVal = (Scc_RegWPtr->SCC_FRO48MCS & ~SCC_INTFLAG_MASK);
    /* Disable FRO48M Monitor */
    RegVal &= (~0x200U);
    /* Lock */
    Scc_RegWPtr->SCC_FRO48MCS = (RegVal | SCC_LOCK_SEQUENCE);
}

/**
 * @brief       Config and Enable LPO96K clock.
 *
 * @param[in]   none.
 *
 * @return      none.
 *
 */
void Clk_EnableLpo96k(void)
{   
    if (0U != Pmu_RegBfPtr->PMU_LOCK.LOCK)
    {
        /* Unlock the PWM register*/
        Pmu_RegWPtr->PMU_LOCK = (uint32)PMU_UNLOCK_SEQUENCE;
    }
    
    Pmu_RegBfPtr->PMU_LPO_96K_CFG.LPO_CLK_DIS = 0U;
    /* Lock the register*/
    Pmu_RegBfPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief       Disable LPO96K clock.
 *
 * @param[in]   none.
 *
 * @return      none.
 *
 */
void Clk_DisableLpo96k(void)
{
    if (0U != Pmu_RegBfPtr->PMU_LOCK.LOCK)
    {
        /* Unlock the PWM register*/
        Pmu_RegWPtr->PMU_LOCK = (uint32)PMU_UNLOCK_SEQUENCE;
    }

    Pmu_RegBfPtr->PMU_LPO_96K_CFG.LPO_CLK_DIS = 1U;
    /* Lock the register*/
    Pmu_RegBfPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief       Set clock divider of the selected node.
 *
 * @param[in]   ClockNode: select clock divider to set. It selects from
 *                      CLK_NODE_CORE, CLK_NODE_BUS, CLK_NODE_UART, CLK_NODE_SPI.
 *                     
 * @param[in]   Divider: clock divider.
 * 
 * @return      none.
 *
 */
void Clk_SetClkDivider(Clk_ClockNodeType ClockNode, Clk_DividerType Divider)
{
    switch (ClockNode)
    {
        case CLK_NODE_CORE:
            if (Scc_RegBfPtr->SCC_CFG.LOCK != 0U)
            {
                /* unlock this register */
                Scc_RegWPtr->SCC_CFG = SCC_UNLOCK_SEQUENCE;
            }

            Scc_RegWPtr->SCC_CFG = (Scc_RegWPtr->SCC_CFG & 0xFFFFF0FFU) \
                                   | ((uint32)Divider << 8U);
            Scc_RegBfPtr->SCC_CFG.LOCK = 1;
            break;

        case CLK_NODE_BUS:
            if (Scc_RegBfPtr->SCC_CFG.LOCK != 0U)
            {
                /* unlock this register */
                Scc_RegWPtr->SCC_CFG = SCC_UNLOCK_SEQUENCE;
            }

            Scc_RegWPtr->SCC_CFG = (Scc_RegWPtr->SCC_CFG & 0xFFFFFF0FU) \
                                   | ((uint32)Divider << 4U);
            Scc_RegBfPtr->SCC_CFG.LOCK = 1U;
            break;

        case CLK_NODE_UART:
            {
                /* unlock SCM register write lock*/
                Clk_UnlockScmRegister();
                /* unlock write register lock*/
                if (1U == Scm_RegBfPtr->SCM_PERI_CTRL.LOCK)
                {
                    Scm_RegWPtr->SCM_PERI_CTRL = SCM_PERICTRL_UNLOCK_SEQUENCE;
                }
                /* SCM_PERI_CLK is protected by SCM_PERI_CTRL.LOCK */
                Scm_RegBfPtr->SCM_PERI_CLK.UART_CLK_DIV = (uint32)Divider;
                /* lock write register */
                Scm_RegBfPtr->SCM_PERI_CTRL.LOCK = 1U;
                /* lock SCM register write lock */
                Clk_LockScmRegister();
                break;
            }
            
        case CLK_NODE_SPI:
            {
                /* unlock SCM register write lock*/
                Clk_UnlockScmRegister();
                /* unlock write register lock*/
                if (1U == Scm_RegBfPtr->SCM_PERI_CTRL.LOCK)
                {
                    Scm_RegWPtr->SCM_PERI_CTRL = SCM_PERICTRL_UNLOCK_SEQUENCE;
                }
                /* SCM_PERI_CLK is protected by SCM_PERI_CTRL.LOCK */
                Scm_RegBfPtr->SCM_PERI_CLK.SPI_CLK_DIV = (uint32)Divider;
                /* lock write register */
                Scm_RegBfPtr->SCM_PERI_CTRL.LOCK = 1U;
                /* lock SCM register write lock */
                Clk_LockScmRegister();
                break;
            }
            
        default:
            /* nothing to do */
            break;
    }
}

/**
 * @brief       Get clock frequency of the selected node.
 *
 * @param[in]   ClockNode: select the module. It selects from 
 *                         CLK_NODE_CORE, CLK_NODE_BUS, CLK_NODE_UART, CLK_NODE_SPI.
 * @param[in]   OscFreq: frequency of the OSC clock.
 *
 * @return      The clock frequency. If return 0, there is some error.
 *
 */
uint32 Clk_GetClkFreq(Clk_ClockNodeType ClockNode, uint32 OscFreq)
{
    uint32 Freq;
    uint32 Divider;

    Freq = 0;
    Divider = 1;
    switch (ClockNode)
    {        
        case CLK_NODE_CORE:
            Divider = (Scc_RegBfPtr->SCC_CST.DIVCORE +  (uint32)1U);
            Freq = Clk_GetSysClkFreq(OscFreq);
            break;
        
        case CLK_NODE_BUS:
            Divider = (Scc_RegBfPtr->SCC_CST.DIVCORE +  (uint32)1U);
            Divider *= (Scc_RegBfPtr->SCC_CST.DIVBUS +  (uint32)1U);
            Freq = Clk_GetSysClkFreq(OscFreq);
            break;

        case CLK_NODE_UART:
            if (CLK_PERI_CORE == Clk_GetUartClkSrc())
            {
                Divider = (Scc_RegBfPtr->SCC_CST.DIVCORE +  (uint32)1U);
                Divider *= (Scm_RegBfPtr->SCM_PERI_CLK.UART_CLK_DIV + (uint32)1U);
                Freq = Clk_GetSysClkFreq(OscFreq);
            }
            else
            {
                Divider = (Scm_RegBfPtr->SCM_PERI_CLK.UART_CLK_DIV + (uint32)1U);
                Freq = OscFreq;
            }
            break;

        case CLK_NODE_SPI:
            Divider = (Scc_RegBfPtr->SCC_CST.DIVCORE +  (uint32)1U);
            Divider *= (Scc_RegBfPtr->SCC_CST.DIVBUS +  (uint32)1U);
            Divider *= (Scm_RegBfPtr->SCM_PERI_CLK.SPI_CLK_DIV + (uint32)1U);
            Freq = Clk_GetSysClkFreq(OscFreq);
            break;

        default:
            /* nothing to do */
            break;
    }
    
    return (Freq/Divider);
}

/**
 * @brief       Get the clock source status.
 *
 * @param[in]   ClkSrc: it can get status of CLK_LPO96K,CLK_FRO48M,
 *                           CLK_OSC24M.
 *
 * @return      The clock source status.
 *
 */
Common_FlagStatusType Clk_GetClkStatus(Clk_ClockType ClkSrc)
{
    Common_FlagStatusType BitStatus;

    BitStatus = COMMON_RESET;
    switch (ClkSrc)
    {
        case CLK_LPO96K:
            BitStatus = (Common_FlagStatusType)Pmu_RegBfPtr->PMU_LPO_96K_CFG.LPO_CLK_READY;
            break;

        case CLK_FRO48M:
            BitStatus = (Common_FlagStatusType)Scc_RegBfPtr->SCC_FRO48MCS.RDY;
            break;

        case CLK_OSC24M:
            BitStatus = (Common_FlagStatusType)Scc_RegBfPtr->SCC_OSCCS.RDY;
            break;        

        default:
            /* nothing to do */
            break;
    }

    return BitStatus;
}

/**
 * @brief       Wait the clock source status until it is ready.
 *
 * @param[in]   ClkSrc: the clock source to be waited.
 *
 * @return      COMMON_SUCC -- the clock is ready;
 *              COMMON_ERR -- time out.
 *
 */
Common_ResultStatusType Clk_WaitClkReady(Clk_ClockType ClkSrc)
{
    volatile uint32 LocalCount;
    Common_ResultStatusType Status;
    
    LocalCount = 0;
    Status = COMMON_SUCC;
    switch (ClkSrc)
    {
        case CLK_LPO96K:
            while(Pmu_RegBfPtr->PMU_LPO_96K_CFG.LPO_CLK_READY != 1U)
            {
                if (LocalCount > CLK_TIMEOUT_WAIT_CNT)
                {
                    Status = COMMON_ERR;
                    break;
                }
                else
                {
                    LocalCount++;
                } 
            }
            break;

        case CLK_FRO48M:
            while(Scc_RegBfPtr->SCC_FRO48MCS.RDY != 1U)
            {                
                if (LocalCount > CLK_TIMEOUT_WAIT_CNT)
                {
                    Status = COMMON_ERR;
                    break;
                }
                else
                {
                    LocalCount++;
                }                
            }
            break;

        case CLK_OSC24M:
            while(Scc_RegBfPtr->SCC_OSCCS.RDY != 1U)
            {
                if (LocalCount > CLK_TIMEOUT_WAIT_CNT)
                {
                    Status = COMMON_ERR;
                    break;
                }
                else
                {
                    LocalCount++;
                }
            }
            break;

        default:
            /* nothing to do */
            break;
    }

    return Status;
}

/**
 * @brief       Config and Enable clock output.
 *
 * @param[in]   OutSrc:  Select the clock source to be output.
 * @param[in]   Divider: output clock divider.
 *
 * @return      none.
 *
 */
void Clk_EnableClkOut(Clk_OutSrcType OutSrc, Clk_OutDivType Divider)
{
    /* unlock SCM register write lock*/
    Clk_UnlockScmRegister();

    /*Disable clock out first before switching*/
    Scm_RegBfPtr->SCM_CHIPCTL.CLKOUTEN = 0U;

    if (CLK_OUT_LPO96K == OutSrc)
    {
        Scm_RegBfPtr->SCM_CHIPCTL.CLKOUTSEL = 1U;
    }
    else if (CLK_OUT_GDU_CP == OutSrc)
    {
        Scm_RegBfPtr->SCM_CHIPCTL.CLKOUTSEL = 2U;
    }
    else if (CLK_OUT_DISABLE != OutSrc)
    {
        Scm_RegBfPtr->SCM_CHIPCTL.CLKOUTSEL = 0U;
        Scc_RegBfPtr->SCC_CLKOUTCFG.CLKOUTSEL = (uint32)OutSrc;
    }
    else
    {
        /* nothing to do */
    }

    Scm_RegBfPtr->SCM_CHIPCTL.CLKOUTDIV = (uint32)Divider;
    /* Enable clock out */
    Scm_RegBfPtr->SCM_CHIPCTL.CLKOUTEN = 1U;
    /* lock SCM register write lock */
    Clk_LockScmRegister();
}

/**
 * @brief       Disable clock output.
 *
 * @param[in]   none.
 *
 * @return      none.
 *
 */
void Clk_DisableClkOut(void)
{
    /* unlock SCM register write lock*/
    Clk_UnlockScmRegister();
    Scm_RegBfPtr->SCM_CHIPCTL.CLKOUTEN = 0U;
    /* lock SCM register write lock */
    Clk_LockScmRegister();
}

/**
 * @brief       Get clock error status.
 *
 * @param[in]   Error: select the error type.
 *
 * @return      none.
 *
 */
Common_FlagStatusType Clk_GetErrorStatus(Clk_ErrorType Error)
{
    uint32 RetVal = 0U;
    if (CLK_ERR_OSCLOC == Error)
    {
        /* Get OSC24M clock loss of clock flag */
        RetVal = Scc_RegBfPtr->SCC_OSCCS.LOC;
    }
    else
    {
        /* Get FRO48M clock loss of clock flag */
        RetVal = Scc_RegBfPtr->SCC_FRO48MCS.LOC;
    }
    return (Common_FlagStatusType)RetVal;
}

/**
 * @brief       Clear clock error flag.
 *
 * @param[in]   Error: select the error type.
 *
 * @return      none.
 *
 */
void Clk_ClearErrorStatus(Clk_ErrorType Error)
{
    if (CLK_ERR_OSCLOC == Error)
    {
        if (Scc_RegBfPtr->SCC_OSCCS.LOCK != 0U)
        {
            /* unlock this register */
            Scc_RegWPtr->SCC_OSCCS = SCC_UNLOCK_SEQUENCE;
        }
        /* clear error flag and lock */
        Scc_RegBfPtr->SCC_OSCCS.LOCK = 1U;
    }
    else
    {
        if (Scc_RegBfPtr->SCC_FRO48MCS.LOCK != 0U)
        {
            /* unlock this register */
            Scc_RegWPtr->SCC_FRO48MCS = SCC_UNLOCK_SEQUENCE;
        }
        /* clear error flag and lock */
        Scc_RegBfPtr->SCC_FRO48MCS.LOCK = 1U;
    }
}

/**
 * @brief       Select UART clock source.
 *
 * @param[in]   PeriClk: select the clock of UART.
 *
 * @return      none.
 *
 */
void Clk_SetUartClkSrc(Clk_PeripheralSrcType PeriClk)
{
    /* unlock SCM register write lock*/
    Clk_UnlockScmRegister();
    /* unlock write register lock*/
    if (1U == Scm_RegBfPtr->SCM_PERI_CTRL.LOCK)
    {
        Scm_RegWPtr->SCM_PERI_CTRL = SCM_PERICTRL_UNLOCK_SEQUENCE;
    }
    /* SCM_PERI_CLK is protected by SCM_PERI_CTRL.LOCK */
    Scm_RegBfPtr->SCM_PERI_CLK.UART_CLK_SEL = (uint32) PeriClk;
    /* lock write register */
    Scm_RegBfPtr->SCM_PERI_CTRL.LOCK = 1U;
    /* lock SCM register write lock */
    Clk_LockScmRegister();
}

/**
 * @brief       Get UART clock source.
 *
 * @param[in]   none.
 *
 * @return      clock source:
 *              - CLK_PERI_CORE
 *              - CLK_PERI_OSC24M
 */
Clk_PeripheralSrcType Clk_GetUartClkSrc(void)
{
    return (Clk_PeripheralSrcType) Scm_RegBfPtr->SCM_PERI_CLK.UART_CLK_SEL;
}

/**
 * @brief      Enable module clock.
 *
 * @param[in]  ModuleType: select which module to enable. 
 *                         - CLK_UART_CLK : UART module
 *                         ...
 *                         - CLK_ROM_CLK : ROM module
 *
 * @return     none
 *
 */
void Clk_EnableModule(Clk_ModuleType ModuleType)
{
    /* unlock SCM register write lock*/
    Clk_UnlockScmRegister();
    /* unlock write register lock*/
    if (1U == Scm_RegBfPtr->SCM_PERI_CTRL.LOCK)
    {
        Scm_RegWPtr->SCM_PERI_CTRL = SCM_PERICTRL_UNLOCK_SEQUENCE;
    }

    Scm_RegBfPtr->SCM_PERI_CTRL.PERI_CLK_EN |= ((uint16)1U<< (uint8)ModuleType); 

    /* lock write register */
    Scm_RegBfPtr->SCM_PERI_CTRL.LOCK = 1U;
    /* lock SCM register write lock */
    Clk_LockScmRegister();
}

/**
 * @brief      Disable module clock.
 *
 * @param[in]  ModuleType: select which module to disable. 
 *                         - CLK_UART_CLK : UART module
 *                         ...
 *                         - CLK_ROM_CLK : ROM module
 *
 * @return     none
 *
 */
void Clk_DisableModule(Clk_ModuleType ModuleType)
{
    /* unlock SCM register write lock*/
    Clk_UnlockScmRegister();
    /* unlock write register lock*/
    if (1U == Scm_RegBfPtr->SCM_PERI_CTRL.LOCK)
    {
        Scm_RegWPtr->SCM_PERI_CTRL = SCM_PERICTRL_UNLOCK_SEQUENCE;
    }
    
    Scm_RegBfPtr->SCM_PERI_CTRL.PERI_CLK_EN &= (~((uint16)1U<< (uint8)ModuleType)); 

    /* lock write register */
    Scm_RegBfPtr->SCM_PERI_CTRL.LOCK = 1U;
    /* lock SCM register write lock */
    Clk_LockScmRegister();
}

/** @} end of group Public_FunctionDefinition */
