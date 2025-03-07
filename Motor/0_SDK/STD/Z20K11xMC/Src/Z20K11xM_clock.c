/**************************************************************************************************/
/**
 * @file      : Z20K11xM_clock.c
 * @brief     : CLOCK module driver file.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (C) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#include "Z20K11xM_clock.h"

/** @addtogroup  Z20K11X_Peripheral_Driver
 *  @{
 */

/** @defgroup Clock
 *  @brief Clock driver modules
 *  @{
 */

/** @defgroup Clock_Private_Type
 *  @{
 */
typedef volatile union
{
    struct {
        uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
        uint32_t RSVD_3_2                : 2;  /* [3:2]          r          */
        uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
        uint32_t RSVD_7                  : 1;  /* [7]            r          */
        uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
        uint32_t RSVD_15_12              : 4;  /* [15:12]        r          */
        uint32_t PWLK                    : 1;  /* [16]           r/w        */
        uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
        uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
        uint32_t PRSTB                   : 1;  /* [21]           r/w        */
        uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
        uint32_t PPR                     : 1;  /* [24]           r/w        */
        uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
        uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
        uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
        uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
        uint32_t LOCK                    : 1;  /* [31]           r/w        */
     } BF;
    uint32_t WORDVAL;
} ModuleClk_t;
/** @} end of group Clock_Private_Type*/

/** @defgroup Clock_Private_Defines
 *  @{
 */

/**
 *  @brief RTC Register address array
 */
/*PRQA S 0303,0306 ++*/
static rtc_reg_t * const rtcRegPtr = (rtc_reg_t *)RTC_BASE_ADDR;
static rtc_reg_w_t * const rtcRegWPtr = (rtc_reg_w_t *)RTC_BASE_ADDR;
/*PRQA S 0303,0306 --*/

/**
 *  @brief SCM Register address array
 */
/*PRQA S 0303,0306 ++*/
static scm_reg_t * const scmRegPtr = (scm_reg_t *)SCM_BASE_ADDR;
/*PRQA S 0303,0306 --*/

/**
 *  @brief SCC Register address array
 */
/*PRQA S 0303,0306 ++*/
static scc_reg_t * const sccRegPtr = (scc_reg_t *)SCC_BASE_ADDR;
static scc_reg_w_t * const sccRegWPtr = (scc_reg_w_t *)SCC_BASE_ADDR;
/*PRQA S 0303,0306 --*/

/**
 *  @brief PMU Register address array
 */
/*PRQA S 0303,0306 ++*/
static pmu_reg_t * const pmuRegPtr = (pmu_reg_t *)PMU_BASE_ADDR;
static pmu_reg_w_t * const pmuRegWPtr = (pmu_reg_w_t *)PMU_BASE_ADDR;
/*PRQA S 0303,0306 --*/

/**
 *  @brief PARCC Register address array
 */
/*PRQA S 0303,0306 ++*/
static ModuleClk_t * const parccRegPtr[]=
{   
    (ModuleClk_t *)(PARCC_BASE_ADDR+0u),
    (ModuleClk_t *)(PARCC_BASE_ADDR + (uint32_t)CLK_EWDT),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_STIM),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_TIM0),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_TIM1),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_TIM2),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_TDG0),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_CAN0),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_CAN1),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_UART0),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_UART1),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_UART2),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_UART3),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_SPI0),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_SPI1),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_SPI2),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_I2C0),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_I2C1),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_ADC0),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_CMP),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_CRC),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_FLASH),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_DMA),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_DMAMUX),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_PORTA),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_PORTB),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_PORTC),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_PORTD),
    (ModuleClk_t *)(PARCC_BASE_ADDR+(uint32_t)CLK_PORTE),
};
/*PRQA S 0303,0306 --*/

#define PMU_UNLOCK_SEQUENCE   (0x94730000UL)

/** @} end of group Clock_Private_Defines */

/** @defgroup Clock_Private_Variables
 *  @{
 */

/**
 *  @brief SCC ISR callback function pointer array
 */
static isr_cb_t * sccIsrCbFunc[CLK_INT_ALL]= {NULL, NULL};

/** @} end of group Clock_Private_Variables */

/** @defgroup Clock_Global_Variables
 *  @{
 */

/** @} end of group Clock_Global_Variables */

/** @defgroup Clock_Private_FunctionDeclaration
 *  @{
 */
void SCC_DriverIRQHandler(void);

static uint32_t CLK_GetSysClkFreq(uint32_t oscFreq);
static void CLK_WaitOSC40MSwitchReady(void);

/** @} end of group Clock_Private_FunctionDeclaration */

/** @defgroup Clock_Private_Functions
 *  @{
 */

/**
 * @brief      get system clock frequency before divider
 *
 * @param[in]  oscFreq: frequency of the OSC clock
 *
 * @return     The clock frequency. If return 0, there is some error.
 *
 */
static uint32_t CLK_GetSysClkFreq(uint32_t oscFreq)
{
    uint32_t ret = 0U;
    
    if(2U == sccRegPtr->SCC_CST.SCS)
    {
        ret = oscFreq;
    }
    else if(1U == sccRegPtr->SCC_CST.SCS)
    {
        ret = 64000000U;
    }
    else
    {
        /*nothing to do*/
    }

    return ret;
}

/**
 * @brief      Wait 500us for the Crystal oscillator ready when switching mode
 *
 * @param[in]  None
 *
 * @return     None
 *
 */
static void CLK_WaitOSC40MSwitchReady(void)
{
    uint32_t cldDiv, waitCount = CLK_WAITCONFIG_CNT;
    volatile uint32_t cnt = 0U;
    cldDiv = sccRegPtr->SCC_CST.DIVCORE + (uint32_t)1U;
    
    waitCount = (CLK_WAITCONFIG_CNT / cldDiv) + (uint32_t)1U;
    
    while(cnt++ < waitCount)
    {
    }
}

/** @} end of group Clock_Private_Functions */

/** @defgroup Clock_Public_Functions
 *  @{
 */

/**
 * @brief      Enable FIRC64M clock and set enablement in stop mode
 *
 * @param[in]  stopModeEn:  Enable/Disable FIRC64M in stop mode.
 *
 * @return none
 *
 */
void CLK_FIRC64MEnable(ControlState_t stopModeEn)
{
    if(sccRegPtr->SCC_FIRCCS.LOCK != 0U)
    {
        /* unlock this register */
        sccRegWPtr->SCC_FIRCCS = 0x5B000000U;
    }

    sccRegPtr->SCC_FIRCCS.FIRCSTOPEN = (uint32_t)stopModeEn;
    sccRegPtr->SCC_FIRCCS.FIRCEN = 1U;

    /* lock this register */
    sccRegPtr->SCC_FIRCCS.LOCK = 1U;
}

/**
 * @brief      It is suggested to use CLK_OSC40MEnable2() instead of this 
 *             function. It Configures and enables OSC40M clock. The frequency 
 *             mode is selected according to the 'freq' parameter. However, the 
 *             selection may be not accurate.
 *
 * @param[in]  freq:  the frequency of OSC40M, unit/MHz. The value should be
 *                    between 4 and 40. If 4<= freq <= 24, CLK_OSC_FREQ_MODE_LOW
 *                    is selected for the frequency mode; if 24< freq <= 40, 
 *                    CLK_OSC_FREQ_MODE_HIGH is selected for the frequency mode.
 * @param[in]  stopModeEn:  Enable/Disable OSC40M in stop mode.
 * @param[in]  mode: select OSC mode. It selects from crystal oscillator or 
 *                   external square wave clock source.
 *
 * @note   It is suggested to use CLK_OSC40MEnable2() instead of this function.
 *             
 *
 * @return status
 *         - ERR - some error.
 *         - SUCC - successful
 *
 */
ResultStatus_t CLK_OSC40MEnable(uint32_t freq, ControlState_t stopModeEn,
                                CLK_OscMode_t mode)
{
    ResultStatus_t retVal = SUCC;
    if(sccRegPtr->SCC_OSCCS.LOCK != 0U)
    {
        /* unlock this register */
        sccRegWPtr->SCC_OSCCS = 0x5B000000U;
    }
    sccRegPtr->SCC_OSCCS.OSCSTOPEN = (uint32_t)stopModeEn;
    if(CLK_GetSysClkSrc() == CLK_SYS_OSC40M)
    {
        /* lock */
        sccRegPtr->SCC_OSCCS.LOCK = 1U;
    }
    else
    {
        if((freq <= 24U) && (freq >= 4U))
        {
            sccRegPtr->SCC_OSCCFG.HFREQ = 0U;
        }
        else if((freq <= 40U) &&(freq > 24U))
        {
            sccRegPtr->SCC_OSCCFG.HFREQ = 1U;
        }
        else
        {
            retVal = ERR;
        }
    
        if(SUCC == retVal)
        {
            sccRegPtr->SCC_OSCCFG.EXCLKS = (uint32_t)mode;
            sccRegPtr->SCC_OSCCFG.OLMEN = 1U;

            sccRegPtr->SCC_OSCCS.OSCEN = 0U;
    
            if(CLK_OSC_XTAL == mode)
            {        
                CLK_WaitOSC40MSwitchReady();

                sccRegPtr->SCC_OSCCS.OSCEN = 1U;

                /* lock */
                sccRegPtr->SCC_OSCCS.LOCK = 1U;

                if(sccRegPtr->SCC_OSCCS.OSCRDY == 1U)
                {
            /* for XTAL mode, it needs some time to be ready. If the OSCRDY is
               set immediately, there is some error */
                    retVal = ERR;
                }
            }
            else
            {
                sccRegPtr->SCC_OSCCS.OSCEN = 1U;

                /* lock */
                sccRegPtr->SCC_OSCCS.LOCK = 1U;
            }
        }
    
        if(SUCC == retVal)
        {
            retVal = CLK_WaitClkReady(CLK_SRC_OSC40M);
        }
    }

    /* wait for clock ready */
    return retVal;
}

/**
 * @brief      Config and enable OSC40M clock
 *
 * @param[in]  freqMode:  It selects the frequency mode of OSC40M
 * @param[in]  stopModeEn:  Enable/Disable OSC40M in stop mode.
 * @param[in]  mode: select OSC mode. It selects from crystal oscillator or 
 *                   external square wave clock source.
 *
 * @return status
 *         ERR - some error.
 *         SUCC - successful
 *
 */
ResultStatus_t CLK_OSC40MEnable2(CLK_OscFreqMode_t freqMode, 
                                 ControlState_t stopModeEn, 
                                 CLK_OscMode_t mode)
{
    ResultStatus_t retVal = SUCC;
    if(sccRegPtr->SCC_OSCCS.LOCK != 0U)
    {
        /* unlock this register */
        sccRegWPtr->SCC_OSCCS = 0x5B000000U;
    }
    sccRegPtr->SCC_OSCCS.OSCSTOPEN = (uint32_t)stopModeEn;
    if(CLK_GetSysClkSrc() == CLK_SYS_OSC40M)
    {
        /* lock */
        sccRegPtr->SCC_OSCCS.LOCK = 1U;
    }
    else
    {
        sccRegPtr->SCC_OSCCFG.HFREQ = (uint32_t)freqMode;
        sccRegPtr->SCC_OSCCFG.EXCLKS = (uint32_t)mode;
        sccRegPtr->SCC_OSCCFG.OLMEN = 1U;
    
        sccRegPtr->SCC_OSCCS.OSCEN = 0U;
    
        if(CLK_OSC_XTAL == mode)
        {        
            CLK_WaitOSC40MSwitchReady();

            sccRegPtr->SCC_OSCCS.OSCEN = 1U;

            /* lock */
            sccRegPtr->SCC_OSCCS.LOCK = 1U;

            if(sccRegPtr->SCC_OSCCS.OSCRDY == 1U)
            {
            /* for XTAL mode, it needs some time to be ready. If the OSCRDY is
               set immediately, there is some error */
                retVal = ERR;
            }
        }
        else
        {
            sccRegPtr->SCC_OSCCS.OSCEN = 1U;

            /* lock */
            sccRegPtr->SCC_OSCCS.LOCK = 1U;
        }
        
        if(SUCC == retVal)
        {
            retVal = CLK_WaitClkReady(CLK_SRC_OSC40M);
        }
    }


    return retVal;
}

/**
 * @brief      Select system clock.
 *
 * @param[in]  clk: select the clock source
 *
 * @return 
 *         SUCC: the system clock is selected successfully
 *         ERR: fail
 * @note The selected clock source has to be ready
 *       before call this function.
 *
 */
ResultStatus_t CLK_SysClkSrc(CLK_System_t clk)
{
    ResultStatus_t retVal = SUCC;
    if(CLK_SYS_FIRC64M == clk)
    {
        if(CLK_WaitClkReady(CLK_SRC_FIRC64M) != SUCC)
        {
            retVal = ERR;
        }
        else
        {
            if(sccRegPtr->SCC_CFG.LOCK != 0U)
            {
                /* unlock this register */
                sccRegWPtr->SCC_CFG = 0x5B000000U;
            }
            /* select sys clock source */
            sccRegWPtr->SCC_CFG = 
              (sccRegWPtr->SCC_CFG & 0xFFF8FFFFU) | (1UL << 16U);

            sccRegPtr->SCC_CFG.LOCK = 1U;
        }

    }
    else if(CLK_SYS_OSC40M == clk)
    {
        if(CLK_WaitClkReady(CLK_SRC_OSC40M) != SUCC)
        {
            retVal = ERR;
        }
        else
        {
            if(sccRegPtr->SCC_CFG.LOCK != 0U)
            {
                /* unlock this register */
                sccRegWPtr->SCC_CFG = 0x5B000000U;
            }
            /* select sys clock source */
            sccRegWPtr->SCC_CFG = 
              (sccRegWPtr->SCC_CFG & 0xFFF8FFFFU) | (1UL << 17U);

            sccRegPtr->SCC_CFG.LOCK = 1;

        }
        
    }
    else
    {
        retVal = ERR;
    }
    return retVal;
}

/**
 * @brief      Get system clock source.
 *
 * @param[in]  none.
 *
 * @return 
 *          -CLK_SYS_FIRC64M
 *          -CLK_SYS_OSC40M
 *
 */
CLK_System_t CLK_GetSysClkSrc(void)
{
    CLK_System_t retVal;
    if((uint32_t)CLK_SYS_FIRC64M == sccRegPtr->SCC_CST.SCS)
    {
        retVal = CLK_SYS_FIRC64M;
    }
    else /*CLK_SYS_OSC40M*/
    {
        retVal = CLK_SYS_OSC40M;
    }
    return retVal;
}

/**
 * @brief      Disable FIRC64M clock
 *
 * @param[in]  none.
 *
 * @return none
 *
 */
void CLK_FIRC64MDisable(void)
{
    if(sccRegPtr->SCC_FIRCCS.LOCK != 0U)
    {
        /* unlock this register */
        sccRegWPtr->SCC_FIRCCS = 0x5B000000;
    }

    sccRegPtr->SCC_FIRCCS.FIRCEN = 0;

    /* lock this register */
    sccRegPtr->SCC_FIRCCS.LOCK = 1;
}

/**
 * @brief      Disable OSC40M clock
 *
 * @param[in]  none.
 *
 * @return none
 *
 */
void CLK_OSC40MDisable(void)
{
    if(sccRegPtr->SCC_OSCCS.LOCK != 0U)
    {
        /* unlock this register */
        sccRegWPtr->SCC_OSCCS = 0x5B000000;
    }

    sccRegPtr->SCC_OSCCS.OSCEN = 0U;
    sccRegPtr->SCC_OSCCFG.OLMEN = 0U;
    /* lock */
    sccRegPtr->SCC_OSCCS.LOCK = 1U;
}

/**
 * @brief      Config and Enable OSC40M loss of clock monitor
 *
 * @param[in]  act: select the action when loss of clock is detected.
 *
 * @return none
 *
 */
void CLK_OSC40MMonitorEnable(CLK_MonitorAct_t act)
{
    if(sccRegPtr->SCC_OSCCS.LOCK != 0U)
    {
        /* unlock this register */
        sccRegWPtr->SCC_OSCCS = 0x5B000000;
    }

    sccRegPtr->SCC_OSCCS.OSCCMRE = (uint32_t)act;

    sccRegPtr->SCC_OSCCS.OSCCME = 1;
    sccRegPtr->SCC_OSCCS.OSCCMIE = 1;
    /* lock */
    sccRegPtr->SCC_OSCCS.LOCK = 1;
}

/**
 * @brief      Disable OSC40M loss of clock monitor
 *
 * @param[in]  none.
 *
 * @return none
 *
 */
void CLK_OSC40MMonitorDisable(void)
{
    if(sccRegPtr->SCC_OSCCS.LOCK != 0U)
    {
        /* unlock this register */
        sccRegWPtr->SCC_OSCCS = 0x5B000000;
    }

    sccRegPtr->SCC_OSCCS.OSCCME = 0;
    /* lock */
    sccRegPtr->SCC_OSCCS.LOCK = 1;
}

/**
 * @brief      Config and Enable FIRC64M loss of clock monitor
 *
 * @param[in]  act: select the action when loss of clock is detected.
 *
 * @return none
 *
 */
void CLK_FIRC64MMonitorEnable(CLK_MonitorAct_t act)
{
    if(sccRegPtr->SCC_FIRCCS.LOCK != 0U)
    {
        /* unlock this register */
        sccRegWPtr->SCC_FIRCCS = 0x5B000000;
    }

    sccRegPtr->SCC_FIRCCS.FIRCCMRE = (uint32_t)act;

    sccRegPtr->SCC_FIRCCS.FIRCCME = 1;
    sccRegPtr->SCC_FIRCCS.FIRCCMIE =1;
    /* lock */
    sccRegPtr->SCC_FIRCCS.LOCK = 1;
}

/**
 * @brief      Config and Enable FIRC64M loss of clock monitor
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void CLK_FIRC64MMonitorDisable(void)
{
    if(sccRegPtr->SCC_FIRCCS.LOCK != 0U)
    {
        /* unlock this register */
        sccRegWPtr->SCC_FIRCCS = 0x5B000000;
    }

    sccRegPtr->SCC_FIRCCS.FIRCCME = 0;
    /* lock */
    sccRegPtr->SCC_FIRCCS.LOCK = 1;
}

/**
 * @brief      Config and Enable LPO32K clock
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void CLK_LPO32KEnable(void)
{
    pmuRegWPtr->PMU_LOCK = (uint32_t)PMU_UNLOCK_SEQUENCE;
    pmuRegPtr->PMU_LPO_32K_CFG.LPO_CLK_DIS = 0U;
    pmuRegPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Disable LPO32K clock
 *
 * @param[in]  none.
 *
 * @return none
 *
 */
void CLK_LPO32KDisable(void)
{
    pmuRegWPtr->PMU_LOCK = (uint32_t)PMU_UNLOCK_SEQUENCE;
    pmuRegPtr->PMU_LPO_32K_CFG.LPO_CLK_DIS = 1U;
    pmuRegPtr->PMU_LOCK.LOCK = 1U;
}

/**
 * @brief      Config and Enable OSC32K clock
 *
 * @param[in]  mode: select OSC mode. It selects from crystal oscillator or 
 *                   external square wave clock source.
 *
 * @return none
 *
 */
void CLK_OSC32KEnable(CLK_OscMode_t mode)
{
    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }
    
    if( CLK_OSC_XTAL == mode)
    {
        rtcRegPtr->RTC_CSR.EXTAL_32K_EN = 0U;
        rtcRegPtr->RTC_CSR.CRYSTAL_EN = 1U;
    }
    else
    {
        rtcRegPtr->RTC_CSR.EXTAL_32K_EN = 1U;
        rtcRegPtr->RTC_CSR.CRYSTAL_EN = 0U;
    }    

    rtcRegPtr->RTC_LOCKR.LOCK = 1U;
}

/**
 * @brief      Disable OSC32K clock
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void CLK_OSC32KDisable(void)
{
    if(rtcRegPtr->RTC_LOCKR.LOCK != 0U)
    {
        rtcRegWPtr->RTC_LOCKR = 0x98670000U;
    }
    
    rtcRegPtr->RTC_CSR.EXTAL_32K_EN = 0U;
    rtcRegPtr->RTC_CSR.CRYSTAL_EN = 0U;
    
    rtcRegPtr->RTC_LOCKR.LOCK = 1U;
}

/**
 * @brief      Set clock divider
 *
 * @param[in]  module: select which module clock to set divider. 
 *                     It selects from CLK_EWDT, CLK_STIM, CLK_TIM0, 
 *                     CLK_TIM1, CLK_TIM2, CLK_TDG0, CLK_CAN0, CLK_CAN1, 
 *                     CLK_UART0, CLK_UART1, CLK_UART2, CLK_UART3, 
 *                     CLK_SPI0, CLK_SPI1, CLK_SPI2, CLK_I2C0, CLK_I2C1, 
 *                     CLK_ADC0, CLK_PORTA,CLK_PORTB, CLK_PORTC, CLK_PORTD, 
 *                     CLK_PORTE CLK_CORE, CLK_BUS, CLK_SLOW
 *                     
 * @param[in] divider: clock divider
 * @return     none
 *
 */
void CLK_SetClkDivider(CLK_Module_t module, CLK_Divider_t divider)
{    
    uint32_t index = (uint32_t)module >> 2U;
    /*PRQA S 0303,0306 ++*/
    ModuleClk_t *PARCCx = (ModuleClk_t *)(parccRegPtr[index]);
    /*PRQA S 0303,0306 ++*/
    switch(module)
    {
        case CLK_EWDT:
        case CLK_STIM:
        case CLK_TIM0:
        case CLK_TIM1:
        case CLK_TIM2:
        case CLK_TDG0:
        case CLK_CAN0:
#if (2U == CAN_INSTANCE_NUM)
        case CLK_CAN1:
#endif
        case CLK_UART0:
        case CLK_UART1:
        case CLK_UART2:
#if (4U == UART_INSTANCE_NUM) 
        case CLK_UART3:
#endif
        case CLK_SPI0:
        case CLK_SPI1:
#if (3U == SPI_INSTANCE_NUM) 
        case CLK_SPI2:
#endif
        case CLK_I2C0:
#if (2U == I2C_INSTANCE_NUM)
        case CLK_I2C1:
#endif
        case CLK_ADC0:
        case CLK_PORTA:
        case CLK_PORTB:
        case CLK_PORTC:
        case CLK_PORTD:
        case CLK_PORTE:
            if(PARCCx->BF.LOCK != 0U)
            {
                /* unlock this register */
                PARCCx->WORDVAL = 0x5B000000U;
            }

            PARCCx->BF.CLKDIV = (uint32_t)divider;
            PARCCx->BF.LOCK = 1;
            break;

        case CLK_CORE:
            if(sccRegPtr->SCC_CFG.LOCK != 0U)
            {
                /* unlock this register */
                sccRegWPtr->SCC_CFG = 0x5B000000U;
            }

            sccRegWPtr->SCC_CFG = 
              (sccRegWPtr->SCC_CFG & 0xFFFFF0FFU) | ((uint32_t)divider << 8U);
            sccRegPtr->SCC_CFG.LOCK = 1;
            break;

        case CLK_BUS:
            if(sccRegPtr->SCC_CFG.LOCK != 0U)
            {
                /* unlock this register */
                sccRegWPtr->SCC_CFG = 0x5B000000U;
            }

            sccRegWPtr->SCC_CFG = (sccRegWPtr->SCC_CFG & 0xFFFFFF0FU) | 
                                       ((uint32_t)divider << 4U);
            sccRegPtr->SCC_CFG.LOCK = 1U;
            break;

        case CLK_SLOW:
            if(sccRegPtr->SCC_CFG.LOCK != 0U)
            {
                /* unlock this register */
                sccRegWPtr->SCC_CFG = 0x5B000000U;
            }

            sccRegWPtr->SCC_CFG = (sccRegWPtr->SCC_CFG & 0xFFFFFFF0U) | 
                                    (uint32_t)divider;
            sccRegPtr->SCC_CFG.LOCK = 1U;
            break;

        default:
            /* nothing to do */
            break;
    }

}

/**
 * @brief      Select clock source for module
 *
 * @param[in]  module: select which module to set clock source.
 *                     It selects from CLK_EWDT, CLK_STIM, CLK_TIM0, CLK_TIM1,
 *                     CLK_TIM2, CLK_TDG0, CLK_CAN0, CLK_CAN1, CLK_UART0, 
 *                     CLK_UART1, CLK_UART2, CLK_UART3, CLK_SPI0, CLK_SPI1, 
 *                     CLK_SPI2, CLK_I2C0, CLK_I2C1, CLK_ADC0, CLK_PORTA,
 *                     CLK_PORTB, CLK_PORTC, CLK_PORTD, CLK_PORTE
 *                     
 * @param[in]  clockSource: select clock source
 * @note  For CAN0 CAN1, the clock source can only select from CLK_SRC_FIRC64M
 *        CLK_SRC_OSC40M,CLK_SRC_NO. 
 *        For ADC0, the clock source can only select from CLK_SRC_FIRC64M, 
 *        CLK_SRC_NO. 
 *        This function should only be called when the module is not working,
 *        otherwise, the clock source will not change.
 * @return     
 *         - SUCC
 *         - ERR: the input parameter is unreasonable.
 *
 */
ResultStatus_t CLK_ModuleSrc(CLK_Module_t module, CLK_Src_t clockSource)
{
    uint32_t index = (uint32_t)module >> 2;
    /*PRQA S 0303,0306 ++*/
    ModuleClk_t *PARCCx = (ModuleClk_t *)(parccRegPtr[index]);
    /*PRQA S 0303,0306 ++*/
    
    ResultStatus_t res = SUCC;

    switch(module)
    {
        case CLK_EWDT:
        case CLK_STIM:
        case CLK_TIM0:
        case CLK_TIM1:
        case CLK_TIM2:
        case CLK_TDG0:
        case CLK_UART0:
        case CLK_UART1:
        case CLK_UART2:
#if (4U == UART_INSTANCE_NUM) 
        case CLK_UART3:
#endif
        case CLK_SPI0:
        case CLK_SPI1:
#if (3U == SPI_INSTANCE_NUM) 
        case CLK_SPI2:
#endif
        case CLK_I2C0:
#if (2U == I2C_INSTANCE_NUM)
        case CLK_I2C1:
#endif
        case CLK_PORTA:
        case CLK_PORTB:
        case CLK_PORTC:
        case CLK_PORTD:
        case CLK_PORTE:
            if(PARCCx->BF.LOCK != 0U)
            {
                /* unlock this register */
                PARCCx->WORDVAL = 0x5B000000U;
            }

            PARCCx->BF.CLKMUX = (uint32_t)clockSource;
            PARCCx->BF.LOCK = 1U;
            break;
            
        case CLK_CAN0:
#if (2U == CAN_INSTANCE_NUM)
        case CLK_CAN1:
#endif
            if(PARCCx->BF.LOCK != 0U)
            {
                /* unlock this register */
                PARCCx->WORDVAL = 0x5B000000U;
            }
    
            if(CLK_SRC_FIRC64M == clockSource)
            {
                PARCCx->BF.CLKMUX = 1U;
            }
            else if(CLK_SRC_OSC40M == clockSource)
            {
                PARCCx->BF.CLKMUX = 2U;
            }
            else if(CLK_SRC_NO == clockSource)
            {
                PARCCx->BF.CLKMUX = 0;
            }
            else
            {
                res = ERR;
            }
            
            PARCCx->BF.LOCK = 1U;
            break;
            
        case CLK_ADC0:
            if(PARCCx->BF.LOCK != 0U)
            {
                /* unlock this register */
                PARCCx->WORDVAL = 0x5B000000U;
            }
            
            if(CLK_SRC_FIRC64M == clockSource)
            {
                PARCCx->BF.CLKMUX = (uint32_t)clockSource;
            }
            else if(CLK_SRC_NO == clockSource)
            {
                PARCCx->BF.CLKMUX = (uint32_t)CLK_SRC_NO;
            }
            else
            {
                res = ERR;
            }
            PARCCx->BF.LOCK = 1U;
            break;
            
        default:
            res = ERR;
            break;
    }
    
    return res;
}


/**
 * @brief      get module clock frequency before divider
 *
 * @param[in]  module: select the module
 * @param[in]  oscFreq: frequency of the OSC clock
 *
 * @return     The clock frequency. If return 0, there is some error.
 *
 */
uint32_t CLK_GetModuleClkFreq(CLK_Module_t module,uint32_t oscFreq)
{
    uint32_t index = (uint32_t)module >> 2;
    /*PRQA S 0303,0306 ++*/
    ModuleClk_t *PARCCx = (ModuleClk_t *)(parccRegPtr[index]);
    /*PRQA S 0303,0306 ++*/
        
    uint32_t freq = 0,clkDiv = 1;

    switch(module)
    {        
        case CLK_EWDT:
        case CLK_STIM:
        case CLK_TIM0:
        case CLK_TIM1:
        case CLK_TIM2:
        case CLK_TDG0:
        case CLK_UART0:
        case CLK_UART1:
        case CLK_UART2:
#if (4U == UART_INSTANCE_NUM) 
        case CLK_UART3:
#endif
        case CLK_SPI0:
        case CLK_SPI1:
#if (3U == SPI_INSTANCE_NUM) 
        case CLK_SPI2:
#endif
        case CLK_I2C0:
#if (2U == I2C_INSTANCE_NUM)
        case CLK_I2C1:
#endif
        case CLK_ADC0:
        case CLK_PORTA:
        case CLK_PORTB:
        case CLK_PORTC:
        case CLK_PORTD:
        case CLK_PORTE:
            clkDiv = (PARCCx->BF.CLKDIV + (uint32_t)1U);
            switch((uint32_t)PARCCx->BF.CLKMUX)
            {
                case (uint32_t)CLK_SRC_LPO32K:
                    freq = 32000U;
                    break;
            
                case (uint32_t)CLK_SRC_OSC32K:
                    freq = 32768U;
                    break;
            
                case (uint32_t)CLK_SRC_FIRC64M:
                    freq = 64000000U;
                    break;
            
                case (uint32_t)CLK_SRC_OSC40M:
                    freq = oscFreq;
                    break;
            
                default:
                    /* nothing to do */
                    break;
            }
            break;
    
        case CLK_CAN0:
#if (2U == CAN_INSTANCE_NUM)
        case CLK_CAN1:
#endif
            clkDiv = (PARCCx->BF.CLKDIV + (uint32_t)1U);
            switch(PARCCx->BF.CLKMUX)
            {   
                case 1U:
                    freq = 64000000U;
                    break;
            
                case 2U:
                    freq = oscFreq;
                    break;
            
                default:
                    /* nothing to do */
                    break;
            }
            break;
        
        case CLK_CORE:
            clkDiv = (sccRegPtr->SCC_CST.DIVCORE + (uint32_t)1U);
            freq = CLK_GetSysClkFreq(oscFreq);
            break;
        
        case CLK_BUS:
            clkDiv = (sccRegPtr->SCC_CST.DIVCORE + (uint32_t)1U);
            clkDiv *=  (sccRegPtr->SCC_CST.DIVBUS + (uint32_t)1U);
            freq = CLK_GetSysClkFreq(oscFreq);
            break;
        
        case CLK_SLOW:
            clkDiv = (sccRegPtr->SCC_CST.DIVCORE + (uint32_t)1U);
            clkDiv *= (sccRegPtr->SCC_CST.DIVSLOW +(uint32_t) 1U);
            freq = CLK_GetSysClkFreq(oscFreq);
            break;

        default:
            /* nothing to do */
            break;
    }
    
    return freq/clkDiv;
    
}

/**
 * @brief      Select TIM external clock source. If TIM is configured to use
 *             external clock source, this function can select a external clock
 *             source from a pin.
 *
 * @param[in]  timId: it indicates which TIM to config
 * @param[in]  clockSrc: select the external TIM clock source
 *
 * @return     None
 *
 */
void CLK_TimExternalClkSrc(CLK_TIM_t timId, CLK_TIMExtClk_t clockSrc)
{
    if(CLK_TIM0_ID == timId)
    {
        scmRegPtr->SCM_TIMOPT.TIM0_CLK_SEL = (uint32_t)clockSrc;
    }
    else if(CLK_TIM1_ID == timId)
    {
        scmRegPtr->SCM_TIMOPT.TIM1_CLK_SEL = (uint32_t)clockSrc;
    }
    else
    {
        scmRegPtr->SCM_TIMOPT.TIM2_CLK_SEL = (uint32_t)clockSrc;
    }
}

/**
 * @brief      Get the clock source status
 *
 * @param[in]  clockSource: it can get status of CLK_OUT_LPO32K,CLK_OUT_FIRC64M,
 *                          CLK_OUT_OSC32K,CLK_OUT_OSC40M
 *
 * @return     The clock source status
 *
 */
FlagStatus_t CLK_GetClkStatus(CLK_Src_t clockSource)
{
    FlagStatus_t bitStatus = RESET;

    switch(clockSource)
    {
        case CLK_SRC_LPO32K:
            bitStatus = ((pmuRegPtr->PMU_LPO_32K_CFG.LPO_CLK_READY != 0U) ? SET 
                            : RESET);
            break;

        case CLK_SRC_FIRC64M:
            bitStatus = ((sccRegPtr->SCC_FIRCCS.FIRCRDY != 0U) ? SET : RESET);
            break;

        case CLK_SRC_OSC32K:
            bitStatus = ((rtcRegPtr->RTC_CSR.OSC_RDY != 0U) ? SET : RESET);
            break;

        case CLK_SRC_OSC40M:
            bitStatus = ((sccRegPtr->SCC_OSCCS.OSCRDY != 0U) ? SET : RESET);
            break;

        default:
            /* nothing to do */
            break;
    }

    return bitStatus;
}

/**
 * @brief      Wait the clock source status until it is ready
 *
 * @param[in]  clockSource: the clock source to be waited
 *
 * @return     SUCC -- the clock is ready
 *             ERR -- time out
 *
 */
ResultStatus_t CLK_WaitClkReady(CLK_Src_t clockSource)
{
    volatile uint32_t localCnt = 0;
    ResultStatus_t retVal = ERR;
    switch(clockSource)
    {
        case CLK_SRC_LPO32K:
            while(localCnt < CLK_TIMEOUT_WAIT_CNT )
            {                
                localCnt++;
                if (1U == pmuRegPtr->PMU_LPO_32K_CFG.LPO_CLK_READY)
                {
                    retVal = SUCC;
                    break;
                }            
            }
            break;

        case CLK_SRC_FIRC64M:
            while(localCnt < CLK_TIMEOUT_WAIT_CNT )
            {                
                localCnt++;
                if (1U == sccRegPtr->SCC_FIRCCS.FIRCRDY)
                {
                    retVal = SUCC;
                    break;
                }            
            }
            break;

        case CLK_SRC_OSC32K:
            while(localCnt < CLK_TIMEOUT_WAIT_CNT )
            {                
                localCnt++;
                if (1U == rtcRegPtr->RTC_CSR.OSC_RDY)
                {
                    retVal = SUCC;
                    break;
                }            
            }
            break;

        case CLK_SRC_OSC40M:
            while(localCnt < CLK_TIMEOUT_WAIT_CNT )
            {                
                localCnt++;
                if (1U == sccRegPtr->SCC_OSCCS.OSCRDY )
                {
                    retVal = SUCC;
                    break;
                }            
            }
            break;

        default:
            retVal = SUCC;
            break;
    }

    return retVal;
}

/**
 * @brief      Config and Enable clock output
 *
 * @param[in]  outSrc:  Select the clock source to be output.
 * @param[in]  divider: output clock divider
 *
 * @return none
 *
 */
void CLK_ClkOutEnable(CLK_OutSrc_t outSrc, CLK_OutDiv_t divider)
{
    /*Disable clock out first before switching*/
    scmRegPtr->SCM_CHIPCTL.CLKOUTEN = 0;

    switch(outSrc)
    {
        case CLK_OUT_OSC40M:
        case CLK_OUT_FIRC64M:
        case CLK_OUT_SLOW:
        case CLK_OUT_BUS:
        case CLK_OUT_CORE:
            scmRegPtr->SCM_CHIPCTL.CLKOUTSEL = 0;
            sccRegPtr->SCC_CLKOUTCFG.CLKOUTSEL = (uint32_t)outSrc;
            break;

        case CLK_OUT_OSC32K:
            scmRegPtr->SCM_CHIPCTL.CLKOUTSEL = 1;
            break;
    
        case CLK_OUT_LPO32K:
            scmRegPtr->SCM_CHIPCTL.CLKOUTSEL = 2;
            break;

        default:
            /* nothing to do */
            break;
    }

    scmRegPtr->SCM_CHIPCTL.CLKOUTDIV = (uint32_t)divider;

    /* Enable clock out */
    scmRegPtr->SCM_CHIPCTL.CLKOUTEN = 1;
}

/**
 * @brief      Disable clock output
 *
 * @param[in]  none
 *
 * @return none
 *
 */
void CLK_ClkOutDisable(void)
{
    scmRegPtr->SCM_CHIPCTL.CLKOUTEN = 0U;
}

/**
 * @brief      install call back function
 *
 * @param[in]  intId: select the interrupt
 * @param[in]  cbFun: pointer to callback function
 *
 * @return none
 *
 */
void SCC_InstallCallBackFunc(CLK_Int_t intId,isr_cb_t * cbFun)
{
    sccIsrCbFunc[intId] = cbFun;
}

/**
 * @brief      Clear Interrupt status
 *
 * @param[in]  intId: select the interrupt
 *
 * @return none
 *
 */
void SCC_IntClear(CLK_Int_t intId)
{
    if(CLK_INT_OSCLOC == intId)
    {
        if(sccRegPtr->SCC_OSCCS.LOCK != 0U)
        {
            /* unlock this register */
            sccRegWPtr->SCC_OSCCS = 0x5B000000U;
        }

        /* clear int status */
        sccRegPtr->SCC_OSCCS.OSCLOC = 1U;
        /* lock */
        sccRegPtr->SCC_OSCCS.LOCK = 1U;
    }
    
    if(CLK_INT_FIRCLOC == intId)
    {
        if(sccRegPtr->SCC_FIRCCS.LOCK != 0U)
        {
            /* unlock this register */
            sccRegWPtr->SCC_FIRCCS = 0x5B000000U;
        }

        /* clear int status */
        sccRegPtr->SCC_FIRCCS.FIRCLOC = 1U;
        /* lock */
        sccRegPtr->SCC_FIRCCS.LOCK = 1U;
    }
}

/**
 * @brief  SCC IRQHandler function
 *
 * @param  none
 *
 * @return none
 *
 */
void SCC_DriverIRQHandler(void)
{
    if(sccRegPtr->SCC_OSCCS.OSCLOC != 0U)
    {
        if(sccRegPtr->SCC_OSCCS.LOCK != 0U)
        {
            /* unlock this register */
            sccRegWPtr->SCC_OSCCS = 0x5B000000U;
        }

        /* clear int status */
        sccRegPtr->SCC_OSCCS.OSCLOC = 1U;
        /* lock */
        sccRegPtr->SCC_OSCCS.LOCK = 1U;
        
        if(sccIsrCbFunc[CLK_INT_OSCLOC] != NULL)
        {
            sccIsrCbFunc[CLK_INT_OSCLOC]();
        }
        else
        {
            CLK_OSC40MMonitorDisable();
        }
        
    }
    
    if(sccRegPtr->SCC_FIRCCS.FIRCLOC != 0U)
    {
        if(sccRegPtr->SCC_FIRCCS.LOCK != 0U)
        {
            /* unlock this register */
            sccRegWPtr->SCC_FIRCCS = 0x5B000000U;
        }

        /* clear int status */
        sccRegPtr->SCC_FIRCCS.FIRCLOC = 1U;
        /* lock */
        sccRegPtr->SCC_FIRCCS.LOCK = 1U;
        
        if(sccIsrCbFunc[CLK_INT_FIRCLOC] != NULL)
        {
            sccIsrCbFunc[CLK_INT_FIRCLOC]();
        }
        else
        {
            CLK_FIRC64MMonitorDisable();
        }
        
    }
}

/** @} end of group Clock_Public_Functions */

/** @} end of group Clock_definitions */

/** @} end of group Z20K11X_Peripheral_Driver */
