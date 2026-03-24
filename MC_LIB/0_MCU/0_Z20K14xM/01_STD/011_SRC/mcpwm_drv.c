/**************************************************************************************************/
/**
 * @file     mcpwm_drv.c
 * @brief    MCPWM module driver file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#include "mcpwm_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @defgroup MCPWM MCPWM
 *  @brief MCPWM driver modules
 *  @{
 */

/** @defgroup MCPWM_Private_Type
 *  @{
 */

/*@} end of group MCPWM_Private_Type*/

/** @defgroup MCPWM_Private_Defines
 *  @{
 */
#define    MCPWM_NUM_ALL     0x2U
/*@} end of group MCPWM_Private_Defines */

/** @defgroup MCPWM_Interrupt_Mask_Defines
 *  @{
 */
#define MCPWM_CH_INT_MASK         (0x00000020U)
#define MCPWM_RLDF0_INT_MASK      (0x00000100U)
#define MCPWM_RLDF1_INT_MASK      (0x00000200U)
#define MCPWM_RLDF2_INT_MASK      (0x00000400U)
#define MCPWM_RLDF3_INT_MASK      (0x00000800U)
#define MCPWM_TOF0_INT_MASK       (0x00001000U)
#define MCPWM_TOF1_INT_MASK       (0x00002000U)
#define MCPWM_TOF2_INT_MASK       (0x00004000U)
#define MCPWM_TOF3_INT_MASK       (0x00008000U)
#define MCPWM_FAULT_INT_MASK      (0x00000030U)
/*@} end of group MCPWM_Interrupt_Mask_Defines */

/** @defgroup MCPWM_Private_Variables
 *  @{
 */
/**
 *  @brief MCPWM0, MCPWM1 address array
 */
/*PRQA S 0303 ++*/
static mcpwm_reg_t *const mcpwmRegPtr[MCPWM_NUM_ALL] = 
{
    (mcpwm_reg_t *)MCPWM0_BASE_ADDR, 
    (mcpwm_reg_t *)MCPWM1_BASE_ADDR
};
/*PRQA S 0303 --*/

/**
 *  @brief MCPWM0, MCPWM1 address array
 */
/*PRQA S 0303 ++*/
static mcpwm_reg_w_t *const mcpwmRegWPtr[MCPWM_NUM_ALL] = 
{
    (mcpwm_reg_w_t *)MCPWM0_BASE_ADDR, 
    (mcpwm_reg_w_t *)MCPWM1_BASE_ADDR
};
/*PRQA S 0303 --*/

static isr_cb_t * mcpwmIsrCbFunc[MCPWM_NUM_ALL][MCPWM_INT_ALL] = 
{
    {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
};

static const uint32_t MCPWM_IntMaskTable[] = 
{
    0x00000001U,               /*!< MCPWM_INT_CH0 */
    0x00000002U,               /*!< MCPWM_INT_CH1 */
    0x00000004U,               /*!< MCPWM_INT_CH2 */
    0x00000008U,               /*!< MCPWM_INT_CH3 */
    0x00000010U,               /*!< MCPWM_INT_CH4 */
    0x00000020U,               /*!< MCPWM_INT_CH5 */
    0x00000040U,               /*!< MCPWM_INT_CH6 */
    0x00000080U,               /*!< MCPWM_INT_CH7 */
    0x00000100U,               /*!< MCPWM_INT_RLD0 */
    0x00000200U,               /*!< MCPWM_INT_RLD1 */
    0x00000400U,               /*!< MCPWM_INT_RLD2 */
    0x00000800U,               /*!< MCPWM_INT_RLD3 */
    0x00001000U,               /*!< MCPWM_INT_TO0 */
    0x00002000U,               /*!< MCPWM_INT_TO1 */
    0x00004000U,               /*!< MCPWM_INT_TO2 */
    0x00008000U,               /*!< MCPWM_INT_TO3 */
    0x00000030U,               /*!< MCPWM_INT_FAULT */
    0x0000FFFFU                /*!< MCPWM_INT_ALL except MCPWM_INT_FAULT*/
};

/*@} end of group MCPWM_Private_Variables */

/** @defgroup MCPWM_Global_Variables
 *  @{
 */

/*@} end of group MCPWM_Global_Variables */

/** @defgroup MCPWM_Private_FunctionDeclaration
 *  @{
 */
static void MCPWM_ChIntHandler(MCPWM_ID_t mcpwmId);
static void MCPWM_FaultIntHandler(MCPWM_ID_t mcpwmId);
static void MCPWM_OverflowIntHandler(MCPWM_ID_t mcpwmId);
static void MCPWM_RlflIntHandler(MCPWM_ID_t mcpwmId);

void MCPWM0_Ch_DriverIRQHandler(void);
void MCPWM0_Fault_DriverIRQHandler(void);
void MCPWM0_Overflow_DriverIRQHandler(void);
void MCPWM0_Rlfl_DriverIRQHandler(void);
void MCPWM1_Ch_DriverIRQHandler(void);
void MCPWM1_Fault_DriverIRQHandler(void);
void MCPWM1_Overflow_DriverIRQHandler(void);
void MCPWM1_Rlfl_DriverIRQHandler(void);

/*@} end of group MCPWM_Private_FunctionDeclaration */

/** @defgroup MCPWM_Private_Functions
 *  @{
 */
/**
 * @brief      MCPWM channel interrupt handle
 *
 * @param[in]  mcpwmId:  Select the MCPWM ID
 *
 * @return none
 *
 */
static void MCPWM_ChIntHandler(MCPWM_ID_t mcpwmId)
{
    uint32_t mcpwmChannel = 0U;
    uint32_t MCPWMIntStatus = 0U;
    uint32_t intStatus;
    mcpwm_reg_w_t * MCPWMwx = mcpwmRegWPtr[mcpwmId];
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];

    /* Check the parameters */
    intStatus = MCPWMwx->MCPWM_GLBSR  & MCPWM_IntMaskTable[MCPWM_INT_ALL];
    
    for(mcpwmChannel = (uint32_t)MCPWM_INT_CH0; mcpwmChannel <= (uint32_t)MCPWM_INT_CH7; mcpwmChannel++)
    {
        if ((0U != (intStatus & ((uint32_t)1U << mcpwmChannel))) && (1U == MCPWMx->MCPWM_CFG[mcpwmChannel].CHIE))
        {
            /* get interrupt status */
            MCPWMIntStatus = MCPWMwx->MCPWM_CFG[mcpwmChannel];
            /* only set interrupt flag bit */
            MCPWMIntStatus = MCPWMIntStatus & (~(MCPWM_CH_INT_MASK));
            /* clear interrupt status */
            MCPWMwx->MCPWM_CFG[mcpwmChannel] = MCPWMIntStatus;
            if(mcpwmIsrCbFunc[mcpwmId][mcpwmChannel] != NULL)
            {
                /* call the callback function */
                mcpwmIsrCbFunc[mcpwmId][mcpwmChannel]();
            }
            /* Disable the interrupt if callback function is not setup */
            else
            {
                MCPWM_IntMask(mcpwmId, (MCPWM_INT_t)mcpwmChannel, MASK);
            }
        }
    }
   
    COMMON_DSB();
}

/**
 * @brief      MCPWM fault interrupt handle
 *
 * @param[in]  mcpwmId:  Select the MCPWM ID
 *
 * @return none
 *
 */
static void MCPWM_FaultIntHandler(MCPWM_ID_t mcpwmId)
{
    uint32_t MCPWMIntStatus = 0U;
    uint32_t intFaultStatus;
    mcpwm_reg_w_t * MCPWMwx = mcpwmRegWPtr[mcpwmId];
    /* Check the parameters */
    intFaultStatus = MCPWMwx->MCPWM_FLTSR  & MCPWM_IntMaskTable[MCPWM_INT_FAULT];
    
        /* Fault Control Interrupt */
    if((intFaultStatus & MCPWM_IntMaskTable[MCPWM_INT_FAULT]) != 0UL)
    {
        /* get interrupt status */
        MCPWMIntStatus = MCPWMwx->MCPWM_FLTSR;
        /* only check enabled interrupts */
        MCPWMIntStatus = MCPWMIntStatus & (~(MCPWM_FAULT_INT_MASK));
        /* clear interrupt status */
        MCPWMwx->MCPWM_FLTSR = MCPWMIntStatus;
        if(mcpwmIsrCbFunc[mcpwmId][MCPWM_INT_FAULT] != NULL)
        {
            /* call the callback function */
            mcpwmIsrCbFunc[mcpwmId][MCPWM_INT_FAULT]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            MCPWM_IntMask(mcpwmId, MCPWM_INT_FAULT, MASK);
        }
    }

    COMMON_DSB();
}

/**
 * @brief      MCPWM overflow interrupt handle
 *
 * @param[in]  mcpwmId:  Select the MCPWM ID
 *
 * @return none
 *
 */
static void MCPWM_OverflowIntHandler(MCPWM_ID_t mcpwmId)
{
    uint32_t MCPWMIntStatus = 0U;
    uint32_t intStatus;
    mcpwm_reg_w_t * MCPWMwx = mcpwmRegWPtr[mcpwmId];
    
    /* Check the parameters */
    intStatus = MCPWMwx->MCPWM_GLBSR  & MCPWM_IntMaskTable[MCPWM_INT_ALL];
    
        /* Timer overflow 0 Interrupt */
    if((intStatus & MCPWM_IntMaskTable[MCPWM_INT_TO0]) != 0UL)
    {
        /* get interrupt status */
        MCPWMIntStatus = MCPWMwx->MCPWM_GLBSR;
        /* only check enabled interrupts */
        MCPWMIntStatus = MCPWMIntStatus & (~(MCPWM_TOF0_INT_MASK));
        /* clear interrupt status */
        MCPWMwx->MCPWM_GLBSR = MCPWMIntStatus;
        if(mcpwmIsrCbFunc[mcpwmId][MCPWM_INT_TO0] != NULL)
        {
            /* call the callback function */
            mcpwmIsrCbFunc[mcpwmId][MCPWM_INT_TO0]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            MCPWM_IntMask(mcpwmId, MCPWM_INT_TO0, MASK);
        }
    }
    
    /* Timer overflow 1 Interrupt */
    if((intStatus & MCPWM_IntMaskTable[MCPWM_INT_TO1]) != 0UL)
    {
        /* get interrupt status */
        MCPWMIntStatus = MCPWMwx->MCPWM_GLBSR;
        /* only check enabled interrupts */
        MCPWMIntStatus = MCPWMIntStatus & (~(MCPWM_TOF1_INT_MASK));
        /* clear interrupt status */
        MCPWMwx->MCPWM_GLBSR = MCPWMIntStatus;
        if(mcpwmIsrCbFunc[mcpwmId][MCPWM_INT_TO1] != NULL)
        {
            /* call the callback function */
            mcpwmIsrCbFunc[mcpwmId][MCPWM_INT_TO1]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            MCPWM_IntMask(mcpwmId, MCPWM_INT_TO1, MASK);
        }
    }
    
    /* Timer overflow 2 Interrupt */
    if((intStatus & MCPWM_IntMaskTable[MCPWM_INT_TO2]) != 0UL)
    {
        /* get interrupt status */
        MCPWMIntStatus = MCPWMwx->MCPWM_GLBSR;
        /* only check enabled interrupts */
        MCPWMIntStatus = MCPWMIntStatus & (~(MCPWM_TOF2_INT_MASK));
        /* clear interrupt status */
        MCPWMwx->MCPWM_GLBSR = MCPWMIntStatus;
        if(mcpwmIsrCbFunc[mcpwmId][MCPWM_INT_TO2] != NULL)
        {
            /* call the callback function */
            mcpwmIsrCbFunc[mcpwmId][MCPWM_INT_TO2]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            MCPWM_IntMask(mcpwmId, MCPWM_INT_TO2, MASK);
        }
    }
    
    /* Timer overflow 3 Interrupt */
    if((intStatus & MCPWM_IntMaskTable[MCPWM_INT_TO3]) != 0UL)
    {
        /* get interrupt status */
        MCPWMIntStatus = MCPWMwx->MCPWM_GLBSR;
        /* only check enabled interrupts */
        MCPWMIntStatus = MCPWMIntStatus & (~(MCPWM_TOF3_INT_MASK));
        /* clear interrupt status */
        MCPWMwx->MCPWM_GLBSR = MCPWMIntStatus;
        if(mcpwmIsrCbFunc[mcpwmId][MCPWM_INT_TO3] != NULL)
        {
            /* call the callback function */
            mcpwmIsrCbFunc[mcpwmId][MCPWM_INT_TO3]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            MCPWM_IntMask(mcpwmId, MCPWM_INT_TO3, MASK);
        }
    }
    
    COMMON_DSB();

}

/**
 * @brief      MCPWM reload interrupt handle
 *
 * @param[in]  mcpwmId:  Select the MCPWM ID
 *
 * @return none
 *
 */
static void MCPWM_RlflIntHandler(MCPWM_ID_t mcpwmId)
{
    uint32_t MCPWMIntStatus = 0U;
    uint32_t intStatus;
    mcpwm_reg_w_t * MCPWMwx = mcpwmRegWPtr[mcpwmId];
    
    /* Check the parameters */
    intStatus = MCPWMwx->MCPWM_GLBSR  & MCPWM_IntMaskTable[MCPWM_INT_ALL];
    
    /* Reload0 Interrupt */
    if((intStatus & MCPWM_IntMaskTable[MCPWM_INT_RLD0]) != 0UL)
    {
        /* get interrupt status */
        MCPWMIntStatus = MCPWMwx->MCPWM_GLBSR;
        /* only check enabled interrupts */
        MCPWMIntStatus = MCPWMIntStatus & (~(MCPWM_RLDF0_INT_MASK));
        /* clear interrupt status */
        MCPWMwx->MCPWM_GLBSR = MCPWMIntStatus;
        if(mcpwmIsrCbFunc[mcpwmId][MCPWM_INT_RLD0] != NULL)
        {
            /* call the callback function */
            mcpwmIsrCbFunc[mcpwmId][MCPWM_INT_RLD0]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            MCPWM_IntMask(mcpwmId, MCPWM_INT_RLD0, MASK);
        }
    }
    
    /* Reload1 Interrupt */
    if((intStatus & MCPWM_IntMaskTable[MCPWM_INT_RLD1]) != 0UL)
    {
         /* get interrupt status */
        MCPWMIntStatus = MCPWMwx->MCPWM_GLBSR;
        /* only check enabled interrupts */
        MCPWMIntStatus = MCPWMIntStatus & (~(MCPWM_RLDF1_INT_MASK));
        /* clear interrupt status */
        MCPWMwx->MCPWM_GLBSR = MCPWMIntStatus;
        if(mcpwmIsrCbFunc[mcpwmId][MCPWM_INT_RLD1] != NULL)
        {
            /* call the callback function */
            mcpwmIsrCbFunc[mcpwmId][MCPWM_INT_RLD1]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            MCPWM_IntMask(mcpwmId, MCPWM_INT_RLD1, MASK);
        }
    }
    
    /* Reload2 Interrupt */
    if((intStatus & MCPWM_IntMaskTable[MCPWM_INT_RLD2]) != 0UL)
    {
         /* get interrupt status */
        MCPWMIntStatus = MCPWMwx->MCPWM_GLBSR;
        /* only check enabled interrupts */
        MCPWMIntStatus = MCPWMIntStatus & (~(MCPWM_RLDF2_INT_MASK));
        /* clear interrupt status */
        MCPWMwx->MCPWM_GLBSR = MCPWMIntStatus;
        if(mcpwmIsrCbFunc[mcpwmId][MCPWM_INT_RLD2] != NULL)
        {
            /* call the callback function */
            mcpwmIsrCbFunc[mcpwmId][MCPWM_INT_RLD2]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            MCPWM_IntMask(mcpwmId, MCPWM_INT_RLD2, MASK);
        }
    }
    
    /* Reload3 Interrupt */
    if((intStatus & MCPWM_IntMaskTable[MCPWM_INT_RLD3]) != 0UL)
    {
         /* get interrupt status */
        MCPWMIntStatus = MCPWMwx->MCPWM_GLBSR;
        /* only check enabled interrupts */
        MCPWMIntStatus = MCPWMIntStatus & (~(MCPWM_RLDF3_INT_MASK));
        /* clear interrupt status */
        MCPWMwx->MCPWM_GLBSR = MCPWMIntStatus;
        if(mcpwmIsrCbFunc[mcpwmId][MCPWM_INT_RLD3] != NULL)
        {
            /* call the callback function */
            mcpwmIsrCbFunc[mcpwmId][MCPWM_INT_RLD3]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            MCPWM_IntMask(mcpwmId, MCPWM_INT_RLD3, MASK);
        }
    }

    COMMON_DSB();
}

/**
 * @brief      MCPWM0 Channel IRQHandler
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void MCPWM0_Ch_DriverIRQHandler(void)
{
    MCPWM_ChIntHandler(MCPWM0_ID);
}

/**
 * @brief      MCPWM0 Fault IRQHandler
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void MCPWM0_Fault_DriverIRQHandler(void)
{
    MCPWM_FaultIntHandler(MCPWM0_ID);
}

/**
 * @brief      MCPWM0 Overflow IRQHandler
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void MCPWM0_Overflow_DriverIRQHandler(void)
{
    MCPWM_OverflowIntHandler(MCPWM0_ID);
}

/**
 * @brief      MCPWM0 Rlfl IRQHandler
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void MCPWM0_Rlfl_DriverIRQHandler(void)
{
    MCPWM_RlflIntHandler(MCPWM0_ID);
}

/**
 * @brief      MCPWM1 Channel IRQHandler
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void MCPWM1_Ch_DriverIRQHandler(void)
{
    MCPWM_ChIntHandler(MCPWM1_ID);
}

/**
 * @brief      MCPWM1 Fault IRQHandler
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void MCPWM1_Fault_DriverIRQHandler(void)
{
    MCPWM_FaultIntHandler(MCPWM1_ID);
}

/**
 * @brief      MCPWM1 Overflow IRQHandler
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void MCPWM1_Overflow_DriverIRQHandler(void)
{
    MCPWM_OverflowIntHandler(MCPWM1_ID);
}

/**
 * @brief      MCPWM1 Rlfl IRQHandler
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void MCPWM1_Rlfl_DriverIRQHandler(void)
{
    MCPWM_RlflIntHandler(MCPWM1_ID);
}

/**
 * @brief       MCPWM WriteProtection Enable Function
 *
 * @param[in]  mcpwmId:  Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID, ... .
 *
 * @return none
 *
 */
void MCPWM_WriteProtectionEnable(MCPWM_ID_t mcpwmId)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    MCPWMx->MCPWM_GLBCR.WPEN = (uint32_t)1UL;
}

/**
 * @brief       MCPWM WriteProtection Disable Function
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID, ... .
 *
 * @return none
 *
 */
void MCPWM_WriteProtectionDisable(MCPWM_ID_t mcpwmId)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    volatile FlagStatus_t flag = (FlagStatus_t)MCPWMx->MCPWM_GLBCR.WPEN;
    if(flag == SET)
    {
        MCPWMx->MCPWM_GLBSR.WPDIS = (uint32_t)1UL;
    }
    
}

/**
 * @brief       MCPWM Start counter with clock configuration
 *
 * @param[in]  mcpwmId:     Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID, ... .
 * @param[in]  clkSource:   Select MCPWM clock source:
 *                                  - MCPWM_CLK_SOURCE_SYSTEM
                                    - MCPWM_CLK_SOURCE_FUNCTION
 *                                  - MCPWM_CLK_SOURCE_EXTERNAL
 * @param[in]  divider:     Select MCPWM clock divider.
 *
 * @return none
 *
 */
void MCPWM_ClockSourceConfig(MCPWM_ID_t mcpwmId, MCPWM_ClkSource_t clkSource, 
                     MCPWM_ClkDivide_t divider)
{
    MCPWM_WriteProtectionDisable(mcpwmId);
    
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    MCPWMx->MCPWM_TIMEBASE.CKSRC = (uint32_t)clkSource;
    MCPWMx->MCPWM_TIMEBASE.PSDIV = (uint32_t)divider;
    
    MCPWM_WriteProtectionEnable(mcpwmId);
}

/**
 * @brief       MCPWM Start counter
 *
 * @param[in]  mcpwmId:       Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID, ... .
 * @param[in]  counterId:     Selected Counter ID.
 *
 * @return none
 *
 */
void MCPWM_StartCounter(MCPWM_ID_t mcpwmId, MCPWM_CounterId_t counterId)
{
    MCPWM_WriteProtectionDisable(mcpwmId);
    
    mcpwm_reg_w_t * MCPWMwx = mcpwmRegWPtr[mcpwmId];
    
    uint32_t regVal = MCPWMwx->MCPWM_GLBCR;
    
    MCPWMwx->MCPWM_GLBCR = regVal | ((uint32_t)0x1000UL << ((uint32_t)(counterId)));
    
    MCPWM_WriteProtectionEnable(mcpwmId);
}

/**
 * @brief       MCPWM Stop counter
 *
 * @param[in]  mcpwmId:       Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID, ... .
 * @param[in]  counterId:     Selected Counter ID.
 *
 * @return none
 *
 */
void MCPWM_StopCounter(MCPWM_ID_t mcpwmId, MCPWM_CounterId_t counterId)
{
    MCPWM_WriteProtectionDisable(mcpwmId);
    
    mcpwm_reg_w_t * MCPWMwx = mcpwmRegWPtr[mcpwmId];
    
    uint32_t regVal = MCPWMwx->MCPWM_GLBCR;
    
    MCPWMwx->MCPWM_GLBCR = regVal & (~(0x1000UL << (uint32_t)(counterId))); 
    
    MCPWM_WriteProtectionEnable(mcpwmId);
}

/**
 * @brief       MCPWM Start Global counter
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID, ... .
 *
 * @return none
 *
 */
void MCPWM_StartGlobalCounter(MCPWM_ID_t mcpwmId)
{
    MCPWM_WriteProtectionDisable(mcpwmId);
    
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    MCPWMx->MCPWM_GLBCR.GLBCNTEN = (uint32_t)1UL;
    MCPWMx->MCPWM_GLBCR.CNTEN0 = (uint32_t)0UL;
    MCPWMx->MCPWM_GLBCR.CNTEN1 = (uint32_t)0UL;
    MCPWMx->MCPWM_GLBCR.CNTEN2 = (uint32_t)0UL;
    MCPWMx->MCPWM_GLBCR.CNTEN3 = (uint32_t)0UL;
    
    MCPWM_WriteProtectionEnable(mcpwmId);
}

/**
 * @brief       MCPWM Stop Global counter
 *
 * @param[in]  mcpwmId:  Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID, ... .
 *
 * @return none
 *
 */
void MCPWM_StopGlobalCounter(MCPWM_ID_t mcpwmId)
{
    MCPWM_WriteProtectionDisable(mcpwmId);
    
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    MCPWMx->MCPWM_GLBCR.GLBCNTEN = (uint32_t)0UL;
    
    MCPWM_WriteProtectionEnable(mcpwmId);
}

/**
 * @brief       MCPWM Set Counter Counting Mode Function
 *
 * @param[in]  mcpwmId:        Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID, ... .
 * @param[in]  counterId:      Selected Counter ID.
 * @param[in]  countingMode:   Counter Counting Mode.
 *
 * @return none
 *
 */
void MCPWM_SetCountingMode(MCPWM_ID_t mcpwmId, MCPWM_CounterId_t counterId,
                                MCPWM_CountingMode_t countingMode)
{
    MCPWM_WriteProtectionDisable(mcpwmId);
    
    mcpwm_reg_w_t * MCPWMwx = mcpwmRegWPtr[mcpwmId];
    
    uint32_t regVal = MCPWMwx->MCPWM_GLBCR;
    
    if(MCPWM_COUNTING_UP == countingMode)
    {
        MCPWMwx->MCPWM_GLBCR = regVal & (~(0x100UL << (uint32_t)(counterId)));  
    }
    else
    {
        MCPWMwx->MCPWM_GLBCR = regVal | (0x100UL << (uint32_t)(counterId));  
    }
    
     MCPWM_WriteProtectionEnable(mcpwmId);
}

/**
 * @brief       MCPWM Get Counter Value Function
 *
 * @param[in]  mcpwmId:     Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID, ... .
 * @param[in]  counterId:   Selected Counter ID.
 *
 * @return Counter Init Value
 *
 */
uint16_t MCPWM_GetCounterVal(MCPWM_ID_t mcpwmId, MCPWM_CounterId_t counterId)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    return (uint16_t)(MCPWMx->MCPWM_CNT[counterId].CNT);
}

/**
 * @brief       MCPWM Set Counter Mod(Max) Value Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID, ... .
 * @param[in]  counterId:  Selected Counter ID.
 * @param[in]  modVal:     Counter MOD value.
 *
 * @return none
 *
 */
void MCPWM_SetCounterModVal(MCPWM_ID_t mcpwmId, MCPWM_CounterId_t counterId, uint16_t modVal)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    MCPWMx->MCPWM_MOD[counterId].MOD = (uint32_t)modVal;
}

/**
 * @brief       MCPWM Get Counter MOD Value Function
 *
 * @param[in]  mcpwmId:     Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID, ... .
 * @param[in]  counterId:   Selected Counter ID.
 *
 * @return Counter MOD Value
 *
 */
uint16_t MCPWM_GetCounterModVal(MCPWM_ID_t mcpwmId, MCPWM_CounterId_t counterId)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    return (uint16_t)(MCPWMx->MCPWM_MOD[counterId].MOD);
}

/**
 * @brief       MCPWM Load Counter Init Value Function
 *
 * @param[in]  mcpwmId:     Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID, ... .
 * @param[in]  counterId:   Selected Counter ID.
 *
 * @return none
 *
 */
void MCPWM_ResetCounter(MCPWM_ID_t mcpwmId, MCPWM_CounterId_t counterId)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];

    MCPWMx->MCPWM_CNT[counterId].CNT = (uint16_t)0x0U;
}

/**
 * @brief       MCPWM Set deadtime Value Function
 *
 * @param[in]  mcpwmId:     Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID, ... .
 * @param[in]  pairId:      Select the MCPWM pair ID.
 * @param[in]  deadtimeVal: Deadtime value, max value is 0xFFF.
 *
 * @return none
 *
 */
void MCPWM_SetDeadtimeVal(MCPWM_ID_t mcpwmId, MCPWM_PairId_t pairId, uint16_t deadtimeVal)
{
    MCPWM_WriteProtectionDisable(mcpwmId);
    
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    MCPWMx->MCPWM_DTVAL[pairId].DTVAL = (uint32_t)deadtimeVal;
    
    MCPWM_WriteProtectionEnable(mcpwmId);
}

/**
 * @brief       MCPWM Get deadtime Value Function
 *
 * @param[in]  mcpwmId:     Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID, ... .
 * @param[in]  pairId:      Select the MCPWM pair ID.
 *
 * @return Deadtime Value
 *
 */
uint16_t MCPWM_GetDeadtimeVal(MCPWM_ID_t mcpwmId, MCPWM_PairId_t pairId)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    return (uint16_t)(MCPWMx->MCPWM_DTVAL[pairId].DTVAL);
}

/**
 * @brief       MCPWM Set MOD Dither  Function
 *
 * @param[in]  mcpwmId:      Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  counterId:    Selected Counter ID.
 * @param[in]  modDitherVal: Mod dither value, max value is 0x1F.
 *
 * @return none
 *
 */
void MCPWM_SetModDither(MCPWM_ID_t mcpwmId, MCPWM_CounterId_t counterId, uint8_t modDither)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    MCPWMx->MCPWM_MOD_DITHER[counterId].MOD_DITHER = (uint32_t)modDither;        
}

/**
 * @brief       MCPWM enable channel output Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  channelId:  Select Channel Id.
 *
 * @return none
 *
 */
void MCPWM_ChannelOutputEnable(MCPWM_ID_t mcpwmId, MCPWM_ChannelId_t channelId)
{
    mcpwm_reg_w_t * MCPWMwx = mcpwmRegWPtr[mcpwmId];
    
    uint32_t regVal = MCPWMwx->MCPWM_GLBCR;
    
    MCPWMwx->MCPWM_GLBCR = regVal | (0x1UL << (uint32_t)(channelId));    
}

/**
 * @brief       MCPWM disable channel output Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  channelId:  Select Channel Id.
 *
 * @return none
 *
 */
void MCPWM_ChannelOutputDisable(MCPWM_ID_t mcpwmId, MCPWM_ChannelId_t channelId)
{
    mcpwm_reg_w_t * MCPWMwx = mcpwmRegWPtr[mcpwmId];
    
    uint32_t regVal = MCPWMwx->MCPWM_GLBCR;
    
    MCPWMwx->MCPWM_GLBCR = regVal & (~(0x1UL << (uint32_t)(channelId))); 
}

/**
 * @brief       MCPWM DMA function enable/disable for selected channel
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  channelId:  Select Channel Id.
 * @param[in]  cmd:        enable/disable.
 *
 * @return none
 *
 */
void MCPWM_DMACmd(MCPWM_ID_t mcpwmId, MCPWM_ChannelId_t channelId,
                                ControlState_t cmd)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];

    MCPWMx->MCPWM_CFG[channelId].DMA = (uint32_t)cmd;
}

/**
 * @brief       MCPWM set channel pulse polarity for selected channel
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  channelId:  Select Channel Id.
 * @param[in]  cpp:        Select pulse polarity.
 *
 * @return none
 *
 */
void MCPWM_SetChannelPulsePol(MCPWM_ID_t mcpwmId, MCPWM_ChannelId_t channelId,
                                MCPWM_PulsePolarity_t cpp)
{
    MCPWM_WriteProtectionDisable(mcpwmId);
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];

    MCPWMx->MCPWM_CFG[channelId].CPP = (uint32_t)cpp;
    MCPWM_WriteProtectionEnable(mcpwmId);    
}

/**
 * @brief       MCPWM Set  Compare Value Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  channelId:  Select channel ID.
 * @param[in]  cVal:       Compare Value.
 *
 * @return none
 *
 */
void MCPWM_SetChannelCVal(MCPWM_ID_t mcpwmId, MCPWM_ChannelId_t channelId, uint16_t cVal)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];

    MCPWMx->MCPWM_CV[channelId].CV = (uint32_t)cVal;     
}

/**
 * @brief       MCPWM Get Compare Value Function
 *
 * @param[in]   mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]   channelId:  Select channel ID.
 *
 * @return Compare Value
 *
 */
uint16_t MCPWM_GetChannelCVal(MCPWM_ID_t mcpwmId, MCPWM_ChannelId_t channelId)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    return ((uint16_t)(MCPWMx->MCPWM_CV[channelId].CV));
}

/**
 * @brief       MCPWM Set  CVal Dither Value Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  channelId:  Select channel ID.
 * @param[in]  cvDither:   Compare Value Dither, max value is 0x1F.
 *
 * @return none
 *
 */
void MCPWM_SetChannelCVDither(MCPWM_ID_t mcpwmId, MCPWM_ChannelId_t channelId, uint8_t cvDither)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    MCPWMx->MCPWM_CV_DITHER[channelId].CV_DITHER = (uint32_t)cvDither;
}

/**
 * @brief       MCPWM Set  channel output value when counter is off
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  channelId:  Select channel ID.
 * @param[in]  level:      Low_level/high_level for channel output.
 *
 * @return none
 *
 */
void MCPWM_SetChannelOffValue(MCPWM_ID_t mcpwmId, MCPWM_ChannelId_t channelId,
                              Level_t level)
{
    MCPWM_WriteProtectionDisable(mcpwmId);
    
    mcpwm_reg_w_t * MCPWMwx = mcpwmRegWPtr[mcpwmId];
    
    uint32_t regVal = MCPWMwx->MCPWM_OUTCR;
    
    if(LEVEL_LOW == level)
    {
        MCPWMwx->MCPWM_OUTCR = regVal & (~(0x100UL << (uint32_t)(channelId)));  
    }
    else
    {
        MCPWMwx->MCPWM_OUTCR = regVal | (0x100UL << (uint32_t)(channelId));  
    }    
    
    MCPWM_WriteProtectionEnable(mcpwmId);
}

/**
 * @brief       MCPWM set channel output polarity for selected channel
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  channelId: Select Channel Id.
 * @param[in]  pol:       Output polarity.
 *
 * @return none
 *
 */
void MCPWM_SetChannelPolarity(MCPWM_ID_t mcpwmId, MCPWM_ChannelId_t channelId,
                                MCPWM_Polarity_t pol)
{
    MCPWM_WriteProtectionDisable(mcpwmId);
    
    mcpwm_reg_w_t * MCPWMwx = mcpwmRegWPtr[mcpwmId];
    
    uint32_t regVal = MCPWMwx->MCPWM_OUTCR;
    
    if(MCPWM_POL_LOW == pol)
    {
        /*output polarity: high level is active*/
        MCPWMwx->MCPWM_OUTCR = regVal & (~(0x1UL << (uint32_t)(channelId)));  
    }
    else
    {
        /*output polarity: low level is active*/
        MCPWMwx->MCPWM_OUTCR = regVal | (0x1UL << (uint32_t)(channelId));  
    }   
    
    MCPWM_WriteProtectionEnable(mcpwmId);
}

/**
 * @brief       MCPWM Set channel match trigger cmd enable/disable Function
 *
 * @param[in]  mcpwmId:      Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  channelId:    Select channel id .
 * @param[in]  cmd:          Enable/disable.
 *
 * @return none
 *
 */
void MCPWM_ChannelMatchTriggerCmd(MCPWM_ID_t mcpwmId, MCPWM_ChannelId_t channelId, 
                                ControlState_t cmd)
{
    mcpwm_reg_w_t * MCPWMwx = mcpwmRegWPtr[mcpwmId];
    
    uint32_t regVal = MCPWMwx->MCPWM_OUTTRIG;
    
    if(DISABLE == cmd)
    {
        MCPWMwx->MCPWM_OUTTRIG = regVal & (~(0x1UL << (uint32_t)(channelId)));  
    }
    else
    {
        MCPWMwx->MCPWM_OUTTRIG = regVal | (0x1UL << (uint32_t)(channelId));  
    } 
}

/**
 * @brief       MCPWM Set init trigger cmd enable/disable Function
 *
 * @param[in]  mcpwmId: Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  cmd:     Enable/disable.
 *
 * @return none
 *
 */
void MCPWM_InitTriggerCmd(MCPWM_ID_t mcpwmId, ControlState_t cmd)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    MCPWMx->MCPWM_OUTTRIG.INITRIGE = (uint32_t)cmd;
}

/**
 * @brief       MCPWM Set  channel output software control value
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  channelId:  Select channel ID.
 * @param[in]  level:      Low_level/high_level for channel output.
 * 
 * @Note: Donot Call this function more than one time before PWM synchronization
 * event occur When SYNCOSWC = MCPWM_UPDATE_PWM_SYN.
 * 
 * @return none
 *
 */
void MCPWM_SetChannelOCV(MCPWM_ID_t mcpwmId, MCPWM_ChannelId_t channelId,
                              Level_t level)
{
    mcpwm_reg_w_t * MCPWMwx = mcpwmRegWPtr[mcpwmId];
    
    uint32_t regVal = MCPWMwx->MCPWM_OUTSWCR;
    
    if(LEVEL_LOW == level)
    {
        MCPWMwx->MCPWM_OUTSWCR = regVal & (~(0x100UL << (uint32_t)(channelId)));  
    }
    else
    {
        MCPWMwx->MCPWM_OUTSWCR = regVal | (0x100UL << (uint32_t)(channelId));  
    }     
}

/**
 * @brief       MCPWM Set channel output software control enable/disable Function
 *
 * @param[in]  mcpwmId:      Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  channelId:    Select channel id .
 * @param[in]  cmd:          Enable/disable.
 *
 * @Note: Donot Call this function more than one time before PWM synchronization
 * event occur When SYNCOSWC = MCPWM_UPDATE_PWM_SYN.
 * 
 * @return none
 *
 */
void MCPWM_ChannelOCCmd(MCPWM_ID_t mcpwmId, MCPWM_ChannelId_t channelId, 
                                ControlState_t cmd)
{
    mcpwm_reg_w_t * MCPWMwx = mcpwmRegWPtr[mcpwmId];
    
    uint32_t regVal = MCPWMwx->MCPWM_OUTSWCR;
    
    if(DISABLE == cmd)
    {
        MCPWMwx->MCPWM_OUTSWCR = regVal & (~(0x1UL << (uint32_t)(channelId)));  
    }
    else
    {
        MCPWMwx->MCPWM_OUTSWCR = regVal | (0x1UL << (uint32_t)(channelId));  
    } 
}

/**
 * @brief       MCPWM Config  output software control for All channels 
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  Config:     Config values.
 *
 * @return none
 *
 */
void MCPWM_ConfigAllOutputSoftwareControl(MCPWM_ID_t mcpwmId, uint16_t Config)
{
    mcpwm_reg_w_t * MCPWMwx = mcpwmRegWPtr[mcpwmId];
    
    uint32_t regVal = MCPWMwx->MCPWM_OUTSWCR & 0xFFFF0000UL;

    MCPWMwx->MCPWM_OUTSWCR = regVal | (uint32_t)Config;  
 
}

/**
 * @brief       MCPWM Set combine enable/disable for pairs of channel
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  pairId:    Select pair id .
 * @param[in]  cmd:       Enable/disable.
 *
 * @return none
 *
 */
void MCPWM_PairCombineCmd(MCPWM_ID_t mcpwmId, MCPWM_PairId_t pairId, 
                                ControlState_t cmd)
{
    MCPWM_WriteProtectionDisable(mcpwmId);
    
    mcpwm_reg_w_t * MCPWMwx = mcpwmRegWPtr[mcpwmId];
    
    uint32_t regVal = MCPWMwx->MCPWM_PCR;
    
    if(DISABLE == cmd)
    {
        MCPWMwx->MCPWM_PCR = regVal & (~(0x40UL << ((uint32_t)pairId*8UL)));  
    }
    else
    {
        MCPWMwx->MCPWM_PCR = regVal | (0x40UL << ((uint32_t)pairId*8UL));  
    } 
    
    MCPWM_WriteProtectionEnable(mcpwmId);
}

/**
 * @brief       MCPWM Set pulse edge control for pairs of channel
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  pairId:    Select pair id .
 * @param[in]  pec:       Pulse Edge Ctrl.
 *
 * @return none
 *
 */
void MCPWM_SetPairPulseEdgeCtrl(MCPWM_ID_t mcpwmId, MCPWM_PairId_t pairId, 
                                MCPWM_PulseEdgeCtrl_t pec)
{
    MCPWM_WriteProtectionDisable(mcpwmId);
    
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    switch (pairId)
    {
        case MCPWM_PAIR_CHANNEL_0:
            MCPWMx->MCPWM_PCR.CVSEL0 = (uint32_t)pec & 1UL;
            MCPWMx->MCPWM_PCR.PEC0 = ((uint32_t)pec>>1UL) & 1UL;
            break;
            
        case MCPWM_PAIR_CHANNEL_1:
            MCPWMx->MCPWM_PCR.CVSEL1 = (uint32_t)pec & 1UL;
            MCPWMx->MCPWM_PCR.PEC1 = ((uint32_t)pec>>1UL) & 1UL;
            break;

        case MCPWM_PAIR_CHANNEL_2:
            MCPWMx->MCPWM_PCR.CVSEL2 = (uint32_t)pec & 1UL;
            MCPWMx->MCPWM_PCR.PEC2 = ((uint32_t)pec>>1UL) & 1UL;
            break;

        case MCPWM_PAIR_CHANNEL_3:
            MCPWMx->MCPWM_PCR.CVSEL3 = (uint32_t)pec & 1UL;
            MCPWMx->MCPWM_PCR.PEC3 = ((uint32_t)pec>>1UL) & 1UL;
            break;

        default:
            /* do nothing */
            break;            
    }
    
    MCPWM_WriteProtectionEnable(mcpwmId);
}

/**
 * @brief       MCPWM Set asymmetric PWM output enable for pairs of channel
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  pairId:    Select pair id .
 * @param[in]  asym:      Symmetric/asymmetric.
 *
 * @return none
 *
 */
void MCPWM_PairAsymmetricCmd(MCPWM_ID_t mcpwmId, MCPWM_PairId_t pairId, 
                                MCPWM_Asym_t asym)
{
    MCPWM_WriteProtectionDisable(mcpwmId);
    
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    switch (pairId)
    {
        case MCPWM_PAIR_CHANNEL_0:
            MCPWMx->MCPWM_PCR.ASYMEN0 = (uint32_t)asym;
            break;
            
        case MCPWM_PAIR_CHANNEL_1:
            MCPWMx->MCPWM_PCR.ASYMEN1 = (uint32_t)asym;
            break;

        case MCPWM_PAIR_CHANNEL_2:
            MCPWMx->MCPWM_PCR.ASYMEN2 = (uint32_t)asym;
            break;

        case MCPWM_PAIR_CHANNEL_3:
            MCPWMx->MCPWM_PCR.ASYMEN3 = (uint32_t)asym;
            break;

        default:
            /* do nothing */
            break;            
    } 
    
    MCPWM_WriteProtectionEnable(mcpwmId);
}

/**
 * @brief       MCPWM Set enable/disable Synchronization of CV(n) and CV(n+1) for pairs of channel
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  pairId:    Select pair id .
 * @param[in]  cmd:       Enable/disable.
 *
 * @return none
 *
 */
void MCPWM_PairSynchronizationCmd(MCPWM_ID_t mcpwmId, MCPWM_PairId_t pairId, 
                                ControlState_t cmd)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    switch (pairId)
    {
        case MCPWM_PAIR_CHANNEL_0:
            MCPWMx->MCPWM_PCR.SYNCEN0 = (uint32_t)cmd;
            break;
            
        case MCPWM_PAIR_CHANNEL_1:
            MCPWMx->MCPWM_PCR.SYNCEN1 = (uint32_t)cmd;
            break;

        case MCPWM_PAIR_CHANNEL_2:
            MCPWMx->MCPWM_PCR.SYNCEN2 = (uint32_t)cmd;
            break;

        case MCPWM_PAIR_CHANNEL_3:
            MCPWMx->MCPWM_PCR.SYNCEN3 = (uint32_t)cmd;
            break;

        default:
            /* do nothing */
            break;            
    }      
}

/**
 * @brief       MCPWM Set deadtime insertion enable/disable for pairs of channel
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  pairId:    Select pair id .
 * @param[in]  cmd:       Enable/disable.
 *
 * @return none
 *
 */
void MCPWM_PairDeadtimeCmd(MCPWM_ID_t mcpwmId, MCPWM_PairId_t pairId, 
                                ControlState_t cmd)
{
    MCPWM_WriteProtectionDisable(mcpwmId);
    
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    switch (pairId)
    {
        case MCPWM_PAIR_CHANNEL_0:
            MCPWMx->MCPWM_PCR.DTEN0 = (uint32_t)cmd;
            break;
            
        case MCPWM_PAIR_CHANNEL_1:
            MCPWMx->MCPWM_PCR.DTEN1 = (uint32_t)cmd;
            break;

        case MCPWM_PAIR_CHANNEL_2:
            MCPWMx->MCPWM_PCR.DTEN2 = (uint32_t)cmd;
            break;

        case MCPWM_PAIR_CHANNEL_3:
            MCPWMx->MCPWM_PCR.DTEN3 = (uint32_t)cmd;
            break;

        default:
            /* do nothing */
            break;            
    } 
    
    MCPWM_WriteProtectionEnable(mcpwmId);
}

/**
 * @brief       MCPWM Set fault control enable/disable for pairs of channel
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  pairId:    Select pair id .
 * @param[in]  cmd:       Enable/disable.
 *
 * @return none
 *
 */
void MCPWM_PairFaultCtrlCmd(MCPWM_ID_t mcpwmId, MCPWM_PairId_t pairId, 
                                ControlState_t cmd)
{
    MCPWM_WriteProtectionDisable(mcpwmId);
    
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    switch (pairId)
    {
        case MCPWM_PAIR_CHANNEL_0:
            MCPWMx->MCPWM_PCR.FCTLEN0 = (uint32_t)cmd;
            break;
            
        case MCPWM_PAIR_CHANNEL_1:
            MCPWMx->MCPWM_PCR.FCTLEN1 = (uint32_t)cmd;
            break;

        case MCPWM_PAIR_CHANNEL_2:
            MCPWMx->MCPWM_PCR.FCTLEN2 = (uint32_t)cmd;
            break;

        case MCPWM_PAIR_CHANNEL_3:
            MCPWMx->MCPWM_PCR.FCTLEN3 = (uint32_t)cmd;
            break;

        default:
            /* do nothing */
            break;            
    } 
    
    MCPWM_WriteProtectionEnable(mcpwmId);
}


/**
 * @brief       MCPWM Set fault input filter value
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  filterVal: Fault input filter value(max value is 0xF, 0 is disabled).
 *
 * @return none
 *
 */
void MCPWM_SetFaultFilterVal(MCPWM_ID_t mcpwmId, uint8_t filterVal)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    MCPWMx->MCPWM_FLTCR.FIFVAL = (uint32_t)filterVal;
}

/**
 * @brief       MCPWM set fault input filter enable/disable for selected input channel
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  inputId:   Select fault input channel Id.
 * @param[in]  cmd:       Fault input enable/disable.
 *
 * @return none
 *
 */
void MCPWM_FaultFilterCmd(MCPWM_ID_t mcpwmId, MCPWM_FaultChannelId_t inputId,
                                ControlState_t cmd)
{
    MCPWM_WriteProtectionDisable(mcpwmId);
    
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    switch (inputId)
    {
        case MCPWM_FAULT_CHANNEL_0:
            MCPWMx->MCPWM_FLTCR.FIFEN0 = (uint32_t)cmd;
            break;
            
        case MCPWM_FAULT_CHANNEL_1:
            MCPWMx->MCPWM_FLTCR.FIFEN1 = (uint32_t)cmd;
            break;

        case MCPWM_FAULT_CHANNEL_2:
            MCPWMx->MCPWM_FLTCR.FIFEN2 = (uint32_t)cmd;
            break;

        case MCPWM_FAULT_CHANNEL_3:
            MCPWMx->MCPWM_FLTCR.FIFEN3 = (uint32_t)cmd;
            break;

        default:
            /* do nothing */
            break;            
    } 
    
    MCPWM_WriteProtectionEnable(mcpwmId);    
}

/**
 * @brief       MCPWM Set fault output state
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  state:     Inactive state / tri-state, if inactive state, 
 *                        the safe state is decided by FLTASS and FLTBSS.
 *
 * @return none
 *
 */
void MCPWM_SetFaultOutputState(MCPWM_ID_t mcpwmId, MCPWM_FaultSafeState_t state)
{
    MCPWM_WriteProtectionDisable(mcpwmId);
    
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    MCPWMx->MCPWM_FLTCR.FSTATE = (uint32_t)state;
    
    MCPWM_WriteProtectionEnable(mcpwmId); 
}

/**
 * @brief       MCPWM Set fault clear mode
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  mode:      Fault clear mode.
 *
 * @return none
 *
 */
void MCPWM_SetFaultClearMode(MCPWM_ID_t mcpwmId, MCPWM_FaultClearMode_t mode)
{
    MCPWM_WriteProtectionDisable(mcpwmId);
    
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    MCPWMx->MCPWM_FLTCR.FLTCM = (uint32_t)mode; 
    
    MCPWM_WriteProtectionEnable(mcpwmId); 
}

/**
 * @brief       MCPWM set fault input channel polarity for selected input channel
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  inputId:   Select fault input channel Id.
 * @param[in]  pol:       Fault input channel polarity.
 *
 * @return none
 *
 */
void MCPWM_SetFaultInputPolarity(MCPWM_ID_t mcpwmId, MCPWM_FaultChannelId_t inputId,
                                MCPWM_Polarity_t pol)
{
    MCPWM_WriteProtectionDisable(mcpwmId);
    
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    switch (inputId)
    {
        case MCPWM_FAULT_CHANNEL_0:
            MCPWMx->MCPWM_FLTCR.FLTPOL0 = (uint32_t)pol;
            break;
            
        case MCPWM_FAULT_CHANNEL_1:
            MCPWMx->MCPWM_FLTCR.FLTPOL1 = (uint32_t)pol;
            break;

        case MCPWM_FAULT_CHANNEL_2:
            MCPWMx->MCPWM_FLTCR.FLTPOL2 = (uint32_t)pol;
            break;

        case MCPWM_FAULT_CHANNEL_3:
            MCPWMx->MCPWM_FLTCR.FLTPOL3 = (uint32_t)pol;
            break;

        default:
            /* do nothing */
            break;            
    }       
    
    MCPWM_WriteProtectionEnable(mcpwmId); 
}

/**
 * @brief       MCPWM set fault input enable/disable for selected input channel
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  inputId:   Select fault input channel Id.
 * @param[in]  cmd:       Fault input enable/disable.
 *
 * @return none
 *
 */
void MCPWM_FaultInputCmd(MCPWM_ID_t mcpwmId, MCPWM_FaultChannelId_t inputId,
                                ControlState_t cmd)
{
    MCPWM_WriteProtectionDisable(mcpwmId);
    
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    switch (inputId)
    {
        case MCPWM_FAULT_CHANNEL_0:
            MCPWMx->MCPWM_FLTCR.FLTEN0 = (uint32_t)cmd;
            break;
            
        case MCPWM_FAULT_CHANNEL_1:
            MCPWMx->MCPWM_FLTCR.FLTEN1 = (uint32_t)cmd;
            break;

        case MCPWM_FAULT_CHANNEL_2:
            MCPWMx->MCPWM_FLTCR.FLTEN2 = (uint32_t)cmd;
            break;

        case MCPWM_FAULT_CHANNEL_3:
            MCPWMx->MCPWM_FLTCR.FLTEN3 = (uint32_t)cmd;
            break;

        default:
            /* do nothing */
            break;            
    }     
    
    MCPWM_WriteProtectionEnable(mcpwmId);
}

/**
 * @brief       MCPWM set selected channel safe status value for fault Group A(fault 
                input 0 and fault input 1).
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  channelId: Select channel Id.
 * @param[in]  level:     Safe status level: low level/high level.
 *
 * @return none
 *
 */
void MCPWM_SetChannelSafeStatusValForFaultA(MCPWM_ID_t mcpwmId, 
                                            MCPWM_ChannelId_t channelId,
                                            Level_t level)
{
    MCPWM_WriteProtectionDisable(mcpwmId);
    
    mcpwm_reg_w_t * MCPWMwx = mcpwmRegWPtr[mcpwmId];
    
    uint32_t regVal = MCPWMwx->MCPWM_FLTASS;
    
    if(LEVEL_LOW == level)
    {
        MCPWMwx->MCPWM_FLTASS = regVal & (~(0x1UL << (uint32_t)(channelId)));  
    }
    else
    {
        MCPWMwx->MCPWM_FLTASS = regVal | (0x1UL << (uint32_t)(channelId));  
    }  
    
    MCPWM_WriteProtectionEnable(mcpwmId);
}

/**
 * @brief       MCPWM set selected channel safe status value for fault Group B(fault 
                input 2 and fault input 3).
 *
 * @param[in]  mcpwmId:   Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  channelId: Select channel Id.
 * @param[in]  level:     Safe status level: low level/high level.
 *
 * @return none
 *
 */
void MCPWM_SetChannelSafeStatusValForFaultB(MCPWM_ID_t mcpwmId, 
                                            MCPWM_ChannelId_t channelId,
                                            Level_t level)
{
    MCPWM_WriteProtectionDisable(mcpwmId);
    
    mcpwm_reg_w_t * MCPWMwx = mcpwmRegWPtr[mcpwmId];
    
    uint32_t regVal = MCPWMwx->MCPWM_FLTBSS;
    
    if(LEVEL_LOW == level)
    {
        MCPWMwx->MCPWM_FLTBSS = regVal & (~(0x1UL << (uint32_t)(channelId)));  
    }
    else
    {
        MCPWMwx->MCPWM_FLTBSS = regVal | (0x1UL << (uint32_t)(channelId));  
    }  
    
    MCPWM_WriteProtectionEnable(mcpwmId);
}

/**
 * @brief       MCPWM output software control config Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  channelId:  Select Channel Id.
 * @param[in]  config:     Software Control Config.
 *
 * @Note: This  function cannot be used when SYNCOSWC = MCPWM_UPDATE_PWM_SYN:
 * OUTSWCR register is updated with its buffer value only by PWM synchronization
 * 
 * @return none
 *
 */
void MCPWM_OutputSWCtrlConfig(MCPWM_ID_t mcpwmId, MCPWM_ChannelId_t channelId, 
                            const MCPWM_OutputSWCtrlConfig_t* config)
{
    MCPWM_SetChannelOCV(mcpwmId, channelId, config->outputSWCtrlVal);
    MCPWM_ChannelOCCmd(mcpwmId, channelId, config->outputSWCtrlEnable);
}

/**
 * @brief       MCPWM get match trigger flag Function when any channel match trigger
 *              is generated, this flag is set by hardware.
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 *
 * @return     FlagStatus_t: 0: No channel match trigger is generated. 
 *                           1: At least one channel match trigger is generated.
 *
 */
FlagStatus_t MCPWM_GetMatchTriggerFlag(MCPWM_ID_t mcpwmId)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    return (FlagStatus_t)(MCPWMx->MCPWM_OUTTRIG.TRIGF);
}

/**
 * @brief       MCPWM independent PWM channel config Function
 *
 * @param[in]  mcpwmId:         Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  channelConfig:   Independent PWM Output Channel Config.
 *
 * @return none
 *
 */
void MCPWM_IndependentPwmChannelConfig(MCPWM_ID_t mcpwmId, const MCPWM_PwmChannelConfig_t * channelConfig)
{
    uint8_t pairId = (uint8_t)channelConfig->channelId >> 1U;
    
    if(ENABLE == channelConfig->channelOutputEnable)
    {
        MCPWM_ChannelOutputEnable(mcpwmId, channelConfig->channelId);
    }
    else
    {
        MCPWM_ChannelOutputDisable(mcpwmId, channelConfig->channelId);
    }
    MCPWM_SetChannelPulsePol(mcpwmId, channelConfig->channelId, channelConfig->pulsePol);
    MCPWM_SetChannelPolarity(mcpwmId, channelConfig->channelId, channelConfig->polarity);
    MCPWM_SetChannelCVal(mcpwmId, channelConfig->channelId, channelConfig->compareValue);
    MCPWM_SetChannelOffValue(mcpwmId, channelConfig->channelId, channelConfig->channelOffVal);
    MCPWM_ChannelMatchTriggerCmd(mcpwmId, channelConfig->channelId, channelConfig->channelMatchTrigEnable);
    
    if(ENABLE == channelConfig->faultCtrlEnable)
    {
        MCPWM_SetChannelSafeStatusValForFaultA(mcpwmId, channelConfig->channelId, channelConfig->safeStatusForFaultA);
        MCPWM_SetChannelSafeStatusValForFaultB(mcpwmId, channelConfig->channelId, channelConfig->safeStatusForFaultB);
    }
    MCPWM_PairCombineCmd(mcpwmId, (MCPWM_PairId_t)pairId, DISABLE);
    MCPWM_PairFaultCtrlCmd(mcpwmId, (MCPWM_PairId_t)pairId, channelConfig->faultCtrlEnable);
    MCPWM_PairSynchronizationCmd(mcpwmId, (MCPWM_PairId_t)pairId, channelConfig->CVUpdateEnable);
}

/**
 * @brief       MCPWM initialise independent PWM output config Function
 *
 * @param[in]  mcpwmId:    Selected the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  counterId:  Selected Counter ID.
 * @param[in]  config:     Independent PWM Output Config.
 *
 * @return none
 *
 */
void MCPWM_OutputIndependentPwmConfig(MCPWM_ID_t mcpwmId, MCPWM_CounterId_t counterId, const MCPWM_PwmConfig_t * config)
{   
    MCPWM_IndependentPwmChannelConfig(mcpwmId, config->MainPwmChConfig);
    MCPWM_IndependentPwmChannelConfig(mcpwmId, config->SecondPwmChConfig);
    
    MCPWM_SetCountingMode(mcpwmId, counterId, config->countMode);
    MCPWM_SetCounterModVal(mcpwmId, counterId, config->countModVal);
    
}

/**
 * @brief       MCPWM Complementary PWM channel config Function
 *
 * @param[in]  mcpwmId:         Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  channelConfig:   Complementary PWM Output Channel Config.
 *
 * @return none
 *
 */
void MCPWM_ComplementaryPwmChannelConfig(MCPWM_ID_t mcpwmId, const MCPWM_CompPwmChannelConfig_t * channelConfig)
{
    uint8_t mainChannel = ((uint8_t)channelConfig->pairId) << 1U;
    uint8_t secondChannel = mainChannel + 1U;

    MCPWM_SetPairPulseEdgeCtrl(mcpwmId, channelConfig->pairId, channelConfig->pec);
    MCPWM_PairAsymmetricCmd(mcpwmId, channelConfig->pairId, channelConfig->asym);
    if(ENABLE == channelConfig->mainChannelOutputEnable)
    {
        MCPWM_ChannelOutputEnable(mcpwmId, (MCPWM_ChannelId_t)mainChannel);
    }
    else
    {
        MCPWM_ChannelOutputDisable(mcpwmId, (MCPWM_ChannelId_t)mainChannel);
    }
    
    if(ENABLE == channelConfig->secondChannelOutputEnable)
    {
        MCPWM_ChannelOutputEnable(mcpwmId, (MCPWM_ChannelId_t)secondChannel);
    }
    else
    {
        MCPWM_ChannelOutputDisable(mcpwmId, (MCPWM_ChannelId_t)secondChannel);
    }    
    
    MCPWM_SetChannelPulsePol(mcpwmId, (MCPWM_ChannelId_t)mainChannel, channelConfig->pulsePol);
    MCPWM_SetChannelPolarity(mcpwmId, (MCPWM_ChannelId_t)mainChannel, channelConfig->polarity);
    MCPWM_SetChannelPolarity(mcpwmId, (MCPWM_ChannelId_t)secondChannel, channelConfig->polarity);
    MCPWM_SetChannelCVal(mcpwmId, (MCPWM_ChannelId_t)mainChannel, channelConfig->mainCompareValue);
    MCPWM_SetChannelCVal(mcpwmId, (MCPWM_ChannelId_t)secondChannel, channelConfig->secondCompareValue);
    MCPWM_SetChannelOffValue(mcpwmId, (MCPWM_ChannelId_t)mainChannel, channelConfig->mainChannelOffVal);
    MCPWM_SetChannelOffValue(mcpwmId, (MCPWM_ChannelId_t)secondChannel, channelConfig->secondChannelOffVal);
    MCPWM_ChannelMatchTriggerCmd(mcpwmId, (MCPWM_ChannelId_t)mainChannel, channelConfig->mainChannelMatchTrigEnable);
    MCPWM_ChannelMatchTriggerCmd(mcpwmId, (MCPWM_ChannelId_t)secondChannel, channelConfig->secondChannelMatchTrigEnable);
    
    if(ENABLE == channelConfig->faultCtrlEnable)
    {
        MCPWM_SetChannelSafeStatusValForFaultA(mcpwmId, (MCPWM_ChannelId_t)mainChannel, channelConfig->mainSafeStatusForFaultA);
        MCPWM_SetChannelSafeStatusValForFaultB(mcpwmId, (MCPWM_ChannelId_t)mainChannel, channelConfig->mainSafeStatusForFaultB);
        MCPWM_SetChannelSafeStatusValForFaultA(mcpwmId, (MCPWM_ChannelId_t)secondChannel, channelConfig->secondSafeStatusForFaultA);
        MCPWM_SetChannelSafeStatusValForFaultB(mcpwmId, (MCPWM_ChannelId_t)secondChannel, channelConfig->secondSafeStatusForFaultB);
    }

    MCPWM_PairCombineCmd(mcpwmId, channelConfig->pairId, ENABLE);
    MCPWM_SetDeadtimeVal(mcpwmId, channelConfig->pairId, channelConfig->deadTimeVal); 
    MCPWM_PairFaultCtrlCmd(mcpwmId, channelConfig->pairId, channelConfig->faultCtrlEnable);
    MCPWM_PairDeadtimeCmd(mcpwmId, channelConfig->pairId, channelConfig->deadTimeEnable);
    MCPWM_PairSynchronizationCmd(mcpwmId, channelConfig->pairId, channelConfig->CVUpdateEnable);
}
                                
/**
 * @brief       MCPWM initialise complementary PWM output config Function
 *
 * @param[in]  mcpwmId:    Selected the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  counterId:  Selected Counter ID.
 * @param[in]  config:     Complementary PWM Output Config.
 *
 * @return none
 *
 */
void MCPWM_OutputComplementaryPwmConfig(MCPWM_ID_t mcpwmId, MCPWM_CounterId_t counterId,
                                        const MCPWM_CompPwmConfig_t * config)
{   
    MCPWM_ComplementaryPwmChannelConfig(mcpwmId, config->cPwmChConfig);
    MCPWM_SetCountingMode(mcpwmId, counterId, config->countMode);
    MCPWM_SetCounterModVal(mcpwmId, counterId, config->countModVal);  
}

/**
 * @brief   MCPWM initialise fault control config Function, which used in pwm mode
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  config:     Fault Control Config.
 *
 * @return none
 *
 */
void MCPWM_FaultControlConfig(MCPWM_ID_t mcpwmId, const MCPWM_PwmFaultCtrlConfig_t * config)
{
    uint8_t i;
    
    MCPWM_SetFaultFilterVal(mcpwmId, config->faultFilterValue);
    MCPWM_SetFaultOutputState(mcpwmId, config->status);
    MCPWM_SetFaultClearMode(mcpwmId, config->faultClearMode);
    
    for(i = 0; i < config->numFaultInputChannels; i++)
    {
        MCPWM_FaultFilterCmd(mcpwmId, config->faultChannelConfig[i].inputChannel,
                             config->faultChannelConfig[i].faultInputFilterEnable);
        MCPWM_SetFaultInputPolarity(mcpwmId, config->faultChannelConfig[i].inputChannel,
                             config->faultChannelConfig[i].faultInputPolarity);
        MCPWM_FaultInputCmd(mcpwmId, config->faultChannelConfig[i].inputChannel,
                             config->faultChannelConfig[i].faultInputChannelEnable);
    }
}

/**
 * @brief       MCPWM enable/disable that Software Trigger activate CNT register sync
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  cmd:        Enable/Disable.
 *
 * @return none
 *
 */
void MCPWM_SWTrigCNTSyncCmd(MCPWM_ID_t mcpwmId, ControlState_t cmd)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    MCPWMx->MCPWM_SYNC.SWRSTCNT = (uint32_t)cmd;
}

/**
 * @brief       MCPWM enable/disable that Software Trigger activate write buffer register sync
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  cmd:        Enable/Disable.
 *
 * @return none
 *
 */
void MCPWM_SWTrigWRBUFSyncCmd(MCPWM_ID_t mcpwmId, ControlState_t cmd)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    MCPWMx->MCPWM_SYNC.SWWRBUF = (uint32_t)cmd;    
}

/**
 * @brief       MCPWM PWM synchronization software trigger Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 *
 * @return none
 *
 */
void MCPWM_SyncSoftwareTrigger(MCPWM_ID_t mcpwmId)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    MCPWMx->MCPWM_SYNC.SWTRIG = 1U;
}

/**
 * @brief       MCPWM Output Software Control Register update mode select Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  updateMode: Update mode. 0: update on all rising edge of the system clock
 *                                       1: update only by PWM synchronization
 *
 * @return none
 *
 */
void MCPWM_OSWCUpdateModeSelect(MCPWM_ID_t mcpwmId, MCPWM_RegUpdateMode_t updateMode)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    MCPWMx->MCPWM_SYNC.SYNCOSWC = (uint32_t)updateMode;
}

/**
 * @brief       MCPWM CPWM half cycle reload enable/disable Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  counterId:  Select counter id for CPWM.
 * @param[in]  cmd:        Enable/Disable.
 *
 * @return none
 *
 */
void MCPWM_CPWMHalfCycleReloadCmd(MCPWM_ID_t mcpwmId, MCPWM_CounterId_t counterId, ControlState_t cmd)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    switch (counterId)
    {
        case MCPWM_COUNTER_0:
            MCPWMx->MCPWM_RELOAD.CPWMHCR0 = (uint32_t)cmd;
            break;
            
        case MCPWM_COUNTER_1:
            MCPWMx->MCPWM_RELOAD.CPWMHCR1 = (uint32_t)cmd;
            break;

        case MCPWM_COUNTER_2:
            MCPWMx->MCPWM_RELOAD.CPWMHCR2 = (uint32_t)cmd;
            break;

        case MCPWM_COUNTER_3:
            MCPWMx->MCPWM_RELOAD.CPWMHCR3 = (uint32_t)cmd;
            break;

        default:
            /* do nothing */
            break;            
    } 
}

/**
 * @brief       MCPWM CPWM full cycle reload enable/disable Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  counterId:  Select counter id for CPWM.
 * @param[in]  cmd:        Enable/Disable.
 *
 * @return none
 *
 */
void MCPWM_CPWMFullCycleReloadCmd(MCPWM_ID_t mcpwmId, MCPWM_CounterId_t counterId, ControlState_t cmd)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    switch (counterId)
    {
        case MCPWM_COUNTER_0:
            MCPWMx->MCPWM_RELOAD.CPWMFCR0 = (uint32_t)cmd;
            break;
            
        case MCPWM_COUNTER_1:
            MCPWMx->MCPWM_RELOAD.CPWMFCR1 = (uint32_t)cmd;
            break;

        case MCPWM_COUNTER_2:
            MCPWMx->MCPWM_RELOAD.CPWMFCR2 = (uint32_t)cmd;
            break;

        case MCPWM_COUNTER_3:
            MCPWMx->MCPWM_RELOAD.CPWMFCR3 = (uint32_t)cmd;
            break;

        default:
            /* do nothing */
            break;            
    } 
}

/**
 * @brief       MCPWM Set reload frequency Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  counterId:  Select counter id for CPWM.
 * @param[in]  freq:       reload frequency, max is 0x1F.
 *
 * @return none
 *
 */
void MCPWM_SetReloadFreq(MCPWM_ID_t mcpwmId, MCPWM_CounterId_t counterId, uint8_t freq)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    switch (counterId)
    {
        case MCPWM_COUNTER_0:
            MCPWMx->MCPWM_LDFREQ.LDFREQ0 = (uint32_t)freq;
            break;
            
        case MCPWM_COUNTER_1:
            MCPWMx->MCPWM_LDFREQ.LDFREQ1 = (uint32_t)freq;
            break;

        case MCPWM_COUNTER_2:
            MCPWMx->MCPWM_LDFREQ.LDFREQ2 = (uint32_t)freq;
            break;

        case MCPWM_COUNTER_3:
            MCPWMx->MCPWM_LDFREQ.LDFREQ3 = (uint32_t)freq;
            break;

        default:
            /* do nothing */
            break;            
    } 
}

/**
 * @brief       MCPWM Config Reload Param for selected pair of channels Function
 *
 * @param[in]  mcpwmId:      Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  counterId:    Select counter id .
 * @param[in]  reloadConfig: Pointer to reload param config struct.
 *
 * @return none
 *
 */
void MCPWM_ReloadParamConfig(MCPWM_ID_t mcpwmId, MCPWM_CounterId_t counterId, 
                             const MCPWM_ReloadConfig_t* reloadConfig)
{
    MCPWM_CPWMHalfCycleReloadCmd(mcpwmId, counterId, reloadConfig->halfCycleEnable);
    MCPWM_CPWMFullCycleReloadCmd(mcpwmId, counterId, reloadConfig->fullCycleEnable);
    MCPWM_SetReloadFreq(mcpwmId, counterId, reloadConfig->loadFrequency);
}

/**
 * @brief       MCPWM Reload Sync Config Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  pairId:     Select pair id for CPWM.
 * @param[in]  cmd:        Enable/Disable.
 *
 * @return none
 *
 */
void MCPWM_ReloadEnable(MCPWM_ID_t mcpwmId, MCPWM_PairId_t pairId, ControlState_t cmd)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    switch (pairId)
    {
        case MCPWM_PAIR_CHANNEL_0:
            MCPWMx->MCPWM_RELOAD.LOADEN0 = (uint32_t)cmd;
            break;
            
        case MCPWM_PAIR_CHANNEL_1:
            MCPWMx->MCPWM_RELOAD.LOADEN1 = (uint32_t)cmd;
            break;

        case MCPWM_PAIR_CHANNEL_2:
            MCPWMx->MCPWM_RELOAD.LOADEN2 = (uint32_t)cmd;
            break;

        case MCPWM_PAIR_CHANNEL_3:
            MCPWMx->MCPWM_RELOAD.LOADEN3 = (uint32_t)cmd;
            break;

        default:
            /* do nothing */
            break;            
    }     
}

/**
 * @brief       MCPWM INT mask/unmask Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  intType:    Select interrupt type.
 * @param[in]  intMask:    Mask/unmask .
 *
 * @return none
 *
 */
void MCPWM_IntMask(MCPWM_ID_t mcpwmId, MCPWM_INT_t intType, IntMask_t intMask)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    ControlState_t cmd = (intMask == UNMASK) ? ENABLE : DISABLE;

    switch (intType)
    {
        case MCPWM_INT_CH0:
            MCPWMx->MCPWM_CFG[0].CHIE = (uint32_t)cmd;
            break;
            
        case MCPWM_INT_CH1:
            MCPWMx->MCPWM_CFG[1].CHIE = (uint32_t)cmd;
            break;
            
        case MCPWM_INT_CH2:
            MCPWMx->MCPWM_CFG[2].CHIE = (uint32_t)cmd;
            break;
            
        case MCPWM_INT_CH3:
            MCPWMx->MCPWM_CFG[3].CHIE = (uint32_t)cmd;
            break;
            
        case MCPWM_INT_CH4:
            MCPWMx->MCPWM_CFG[4].CHIE = (uint32_t)cmd;
            break;
            
        case MCPWM_INT_CH5:
            MCPWMx->MCPWM_CFG[5].CHIE = (uint32_t)cmd;
            break;
            
        case MCPWM_INT_CH6:
            MCPWMx->MCPWM_CFG[6].CHIE = (uint32_t)cmd;
            break;
            
        case MCPWM_INT_CH7:
            MCPWMx->MCPWM_CFG[7].CHIE = (uint32_t)cmd;
            break;
            
        case MCPWM_INT_RLD0:
            MCPWMx->MCPWM_GLBCR.RLDIE0 = (uint32_t)cmd;
            break;
            
        case MCPWM_INT_RLD1:
            MCPWMx->MCPWM_GLBCR.RLDIE1 = (uint32_t)cmd;
            break;
            
        case MCPWM_INT_RLD2:
            MCPWMx->MCPWM_GLBCR.RLDIE2 = (uint32_t)cmd;
            break;
            
        case MCPWM_INT_RLD3:
            MCPWMx->MCPWM_GLBCR.RLDIE3= (uint32_t)cmd;
            break;
            
        case MCPWM_INT_TO0:
            MCPWMx->MCPWM_GLBCR.TOIE0 = (uint32_t)cmd;
            break;
            
        case MCPWM_INT_TO1:
            MCPWMx->MCPWM_GLBCR.TOIE1 = (uint32_t)cmd;
            break;
            
        case MCPWM_INT_TO2:
            MCPWMx->MCPWM_GLBCR.TOIE2 = (uint32_t)cmd;
            break;
            
        case MCPWM_INT_TO3:
            MCPWMx->MCPWM_GLBCR.TOIE3 = (uint32_t)cmd;
            break;
            
        case MCPWM_INT_FAULT:
            MCPWMx->MCPWM_FLTCR.FLTIE = (uint32_t)cmd;
            break;
            
        case MCPWM_INT_ALL:
            MCPWMx->MCPWM_CFG[0].CHIE = (uint32_t)cmd;
            MCPWMx->MCPWM_CFG[1].CHIE = (uint32_t)cmd;
            MCPWMx->MCPWM_CFG[2].CHIE = (uint32_t)cmd;
            MCPWMx->MCPWM_CFG[3].CHIE = (uint32_t)cmd;
            MCPWMx->MCPWM_CFG[4].CHIE = (uint32_t)cmd;
            MCPWMx->MCPWM_CFG[5].CHIE = (uint32_t)cmd;
            MCPWMx->MCPWM_CFG[6].CHIE = (uint32_t)cmd;
            MCPWMx->MCPWM_CFG[7].CHIE = (uint32_t)cmd;
            MCPWMx->MCPWM_GLBCR.RLDIE0 = (uint32_t)cmd;
            MCPWMx->MCPWM_GLBCR.RLDIE1 = (uint32_t)cmd;
            MCPWMx->MCPWM_GLBCR.RLDIE2 = (uint32_t)cmd;
            MCPWMx->MCPWM_GLBCR.RLDIE3 = (uint32_t)cmd;
            MCPWMx->MCPWM_GLBCR.TOIE0 = (uint32_t)cmd;
            MCPWMx->MCPWM_GLBCR.TOIE1 = (uint32_t)cmd;
            MCPWMx->MCPWM_GLBCR.TOIE2 = (uint32_t)cmd;
            MCPWMx->MCPWM_GLBCR.TOIE3 = (uint32_t)cmd;
            MCPWMx->MCPWM_FLTCR.FLTIE = (uint32_t)cmd;
            break;
            
        default:
            /* do nothing */
            break;
    }        
}

/**
 * @brief       MCPWM INT status clear Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  intType:    Select interrupt type.
 *
 * @return none
 *
 */
void MCPWM_IntClear(MCPWM_ID_t mcpwmId, MCPWM_INT_t intType)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];

    switch (intType)
    {
        case MCPWM_INT_CH0:
            MCPWMx->MCPWM_CFG[0].CHF = 0U;
            break;
            
        case MCPWM_INT_CH1:
            MCPWMx->MCPWM_CFG[1].CHF = 0U;
            break;
            
        case MCPWM_INT_CH2:
            MCPWMx->MCPWM_CFG[2].CHF = 0U;
            break;
            
        case MCPWM_INT_CH3:
            MCPWMx->MCPWM_CFG[3].CHF = 0U;
            break;
            
        case MCPWM_INT_CH4:
            MCPWMx->MCPWM_CFG[4].CHF = 0U;
            break;
            
        case MCPWM_INT_CH5:
            MCPWMx->MCPWM_CFG[5].CHF = 0U;
            break;
            
        case MCPWM_INT_CH6:
            MCPWMx->MCPWM_CFG[6].CHF = 0U;
            break;
            
        case MCPWM_INT_CH7:
            MCPWMx->MCPWM_CFG[7].CHF = 0U;
            break;
            
        case MCPWM_INT_RLD0:
            MCPWMx->MCPWM_GLBSR.RLDF0 = 0U;
            break;
            
        case MCPWM_INT_RLD1:
            MCPWMx->MCPWM_GLBSR.RLDF1 = 0U;
            break;
            
        case MCPWM_INT_RLD2:
            MCPWMx->MCPWM_GLBSR.RLDF2 = 0U;
            break;
            
        case MCPWM_INT_RLD3:
            MCPWMx->MCPWM_GLBSR.RLDF3= 0U;
            break;
            
        case MCPWM_INT_TO0:
            MCPWMx->MCPWM_GLBSR.TOF0 = 0U;
            break;
            
        case MCPWM_INT_TO1:
            MCPWMx->MCPWM_GLBSR.TOF1 = 0U;
            break;
            
        case MCPWM_INT_TO2:
            MCPWMx->MCPWM_GLBSR.TOF2 = 0U;
            break;
            
        case MCPWM_INT_TO3:
            MCPWMx->MCPWM_GLBSR.TOF3 = 0U;
            break;
            
        case MCPWM_INT_FAULT:
            MCPWMx->MCPWM_FLTSR.FAULTFA = 0U;
            MCPWMx->MCPWM_FLTSR.FAULTFB = 0U;
            break;
            
        case MCPWM_INT_ALL:
            MCPWMx->MCPWM_CFG[0].CHF = 0U;
            MCPWMx->MCPWM_CFG[1].CHF = 0U;
            MCPWMx->MCPWM_CFG[2].CHF = 0U;
            MCPWMx->MCPWM_CFG[3].CHF = 0U;
            MCPWMx->MCPWM_CFG[4].CHF = 0U;
            MCPWMx->MCPWM_CFG[5].CHF = 0U;
            MCPWMx->MCPWM_CFG[6].CHF = 0U;
            MCPWMx->MCPWM_CFG[7].CHF = 0U;
            MCPWMx->MCPWM_GLBSR.RLDF0 = 0U;
            MCPWMx->MCPWM_GLBSR.RLDF1 = 0U;
            MCPWMx->MCPWM_GLBSR.RLDF2 = 0U;
            MCPWMx->MCPWM_GLBSR.RLDF3 = 0U;
            MCPWMx->MCPWM_GLBSR.TOF0 = 0U;
            MCPWMx->MCPWM_GLBSR.TOF1 = 0U;
            MCPWMx->MCPWM_GLBSR.TOF2 = 0U;
            MCPWMx->MCPWM_GLBSR.TOF3 = 0U;
            MCPWMx->MCPWM_FLTSR.FAULTFA = 0U;
            MCPWMx->MCPWM_FLTSR.FAULTFB = 0U;
            break;
            
        default:
            /* do nothing */
            break;
    }   
}

/**
 * @brief       MCPWM Get INT status Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID .
 * @param[in]  intType:    Select interrupt type.
 *
 * @return intstatus
 *
 */
IntStatus_t MCPWM_GetIntStatus(MCPWM_ID_t mcpwmId, MCPWM_INT_t intType)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    IntStatus_t intStatus = RESET;
    
    switch (intType)
    {
        case MCPWM_INT_CH0:
            intStatus = (IntStatus_t)MCPWMx->MCPWM_CFG[0].CHF;
            break;
            
        case MCPWM_INT_CH1:
            intStatus = (IntStatus_t)MCPWMx->MCPWM_CFG[1].CHF;
            break;
            
        case MCPWM_INT_CH2:
            intStatus = (IntStatus_t)MCPWMx->MCPWM_CFG[2].CHF;
            break;
            
        case MCPWM_INT_CH3:
            intStatus = (IntStatus_t)MCPWMx->MCPWM_CFG[3].CHF;
            break;
            
        case MCPWM_INT_CH4:
            intStatus = (IntStatus_t)MCPWMx->MCPWM_CFG[4].CHF;
            break;
            
        case MCPWM_INT_CH5:
            intStatus = (IntStatus_t)MCPWMx->MCPWM_CFG[5].CHF;
            break;
            
        case MCPWM_INT_CH6:
            intStatus = (IntStatus_t)MCPWMx->MCPWM_CFG[6].CHF;
            break;
            
        case MCPWM_INT_CH7:
            intStatus = (IntStatus_t)MCPWMx->MCPWM_CFG[7].CHF;
            break;
            
        case MCPWM_INT_RLD0:
            intStatus = (IntStatus_t)MCPWMx->MCPWM_GLBSR.RLDF0;
            break;
            
        case MCPWM_INT_RLD1:
            intStatus = (IntStatus_t)MCPWMx->MCPWM_GLBSR.RLDF1;
            break;
            
        case MCPWM_INT_RLD2:
            intStatus = (IntStatus_t)MCPWMx->MCPWM_GLBSR.RLDF2;
            break;
            
        case MCPWM_INT_RLD3:
            intStatus = (IntStatus_t)MCPWMx->MCPWM_GLBSR.RLDF3;
            break;
            
        case MCPWM_INT_TO0:
            intStatus = (IntStatus_t)MCPWMx->MCPWM_GLBSR.TOF0;
            break;
            
        case MCPWM_INT_TO1:
            intStatus = (IntStatus_t)MCPWMx->MCPWM_GLBSR.TOF1;
            break;
            
        case MCPWM_INT_TO2:
            intStatus = (IntStatus_t)MCPWMx->MCPWM_GLBSR.TOF2;
            break;
            
        case MCPWM_INT_TO3:
            intStatus = (IntStatus_t)MCPWMx->MCPWM_GLBSR.TOF3;
            break;
            
        case MCPWM_INT_FAULT:
            if(MCPWMx->MCPWM_FLTSR.FAULTFA != 0UL)
            {
                intStatus = SET;
            }
            
            if(MCPWMx->MCPWM_FLTSR.FAULTFB != 0UL)
            {
                intStatus = SET;
            }
            break;
            
        default:
            /* do nothing */
            break;
      
    }  
    
    return intStatus;
}

/**
 * @brief       MCPWM Get Fault detection flag status of fault channel  Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  channelId:  Select fault input channel:MCPWM_FAULT_CHANNEL_0,.. .
 *
 * @return intstatus
 *
 */
IntStatus_t MCPWM_GetFaultStatus(MCPWM_ID_t mcpwmId, MCPWM_FaultChannelId_t inputId)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    IntStatus_t intStatus = RESET;
    
    switch (inputId)
    {
        case MCPWM_FAULT_CHANNEL_0:
            intStatus = (IntStatus_t)MCPWMx->MCPWM_FLTSR.FAULTF0;
            break;
            
        case MCPWM_FAULT_CHANNEL_1:
            intStatus = (IntStatus_t)MCPWMx->MCPWM_FLTSR.FAULTF1;
            break;

        case MCPWM_FAULT_CHANNEL_2:
            intStatus = (IntStatus_t)MCPWMx->MCPWM_FLTSR.FAULTF2;
            break;

        case MCPWM_FAULT_CHANNEL_3:
            intStatus = (IntStatus_t)MCPWMx->MCPWM_FLTSR.FAULTF3;
            break;

        default:
            /* do nothing */
            break;            
    }  
    
    return intStatus;
}

/**
 * @brief       MCPWM fault status clear Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  intType:    Select interrupt type.
 *
 * @return none
 *
 */
void MCPWM_FaultStatusClear(MCPWM_ID_t mcpwmId, MCPWM_FaultChannelId_t inputId)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    switch (inputId)
    {
        case MCPWM_FAULT_CHANNEL_0:
            MCPWMx->MCPWM_FLTSR.FAULTF0 = 0U;
            break;
            
        case MCPWM_FAULT_CHANNEL_1:
            MCPWMx->MCPWM_FLTSR.FAULTF1 = 0U;
            break;

        case MCPWM_FAULT_CHANNEL_2:
            MCPWMx->MCPWM_FLTSR.FAULTF2 = 0U;
            break;

        case MCPWM_FAULT_CHANNEL_3:
            MCPWMx->MCPWM_FLTSR.FAULTF3 = 0U;
            break;

        default:
            /* do nothing */
            break;            
    }  
}

/**
 * @brief       MCPWM any channel match trigger flag clear Function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 *
 * @return none
 *
 */
void MCPWM_MatchTriggerFlagClear(MCPWM_ID_t mcpwmId)
{
    mcpwm_reg_t * MCPWMx = mcpwmRegPtr[mcpwmId];
    
    MCPWMx->MCPWM_OUTTRIG.TRIGF = 0U;
}

/**
 * @brief       MCPWM install interrupt callback function
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID, MCPWM1_ID.
 * @param[in]  intType:    Select interrupt type.
 * @param[in]  cbFun:      Callback function .
 *
 * @return none
 *
 */
void MCPWM_InstallCallBackFunc(MCPWM_ID_t mcpwmId, MCPWM_INT_t intType, isr_cb_t * cbFun)
{
    mcpwmIsrCbFunc[mcpwmId][intType] = cbFun;
}


/*@} end of group MCPWM_Public_Functions */

/*@} end of group MCPWM_definitions */

/*@} end of group Z20K14XM_Peripheral_Driver */
