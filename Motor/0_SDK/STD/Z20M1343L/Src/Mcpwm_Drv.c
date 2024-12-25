/**************************************************************************************************/
/**
 * @file     : Mcpwm_Drv.c
 * @brief    : Mcpwm module driver  source file.
 *              - Platform: Z20M1343L
 * @version  : 0.1.0
 * @date     : May-2023
 * @author   : Zhixin Semiconductor
 * @note     : None   
 *   
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#include "Mcpwm_Drv.h"

/** @defgroup Mcpwm_Private_Type
 *  @{
 */

/*@} end of group Mcpwm_Private_Type*/

/** @defgroup Mcpwm_Private_Defines
 *  @{
 */
#define    MCPWM_NUM_ALL     0x1U
/*@} end of group Mcpwm_Private_Defines */
/** @defgroup MCPWM_Private_Defines
 *  @{
 */   
static uint32 Mcpwm_IntMaskStatus = 0x0U; 
/*@} end of group MCPWM_Private_Defines */

/** @defgroup Mcpwm_Interrupt_Mask_Defines
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
/*@} end of group Mcpwm_Interrupt_Mask_Defines */

/** @defgroup Mcpwm_Private_Variables
 *  @{
 */
/**
 *  @brief MCPWM address array
 */
/*PRQA S 0303,0306 ++*/
static Reg_Mcpwm_BfType *const Mcpwm_RegBfPtr[MCPWM_NUM_ALL] = 
{
    (Reg_Mcpwm_BfType *)MCPWM_BASE_ADDR 
};
/*PRQA S 0303,0306 --*/

/**
 *  @brief MCPWM address array
 */
/*PRQA S 0303,0306 ++*/
static Reg_Mcpwm_WType *const Mcpwm_RegWPtr[MCPWM_NUM_ALL] = 
{
    (Reg_Mcpwm_WType *)MCPWM_BASE_ADDR
};
/*PRQA S 0303,0306 --*/

static Isr_CbFuncType * McpwmIsrCbFunc[MCPWM_NUM_ALL][MCPWM_INT_ALL] = 
{
    {NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR}
};

static const uint32 Mcpwm_IntMaskTable[] = 
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

/*@} end of group Mcpwm_Private_Variables */

/** @defgroup Mcpwm_Global_Variables
 *  @{
 */

/*@} end of group Mcpwm_Global_Variables */

/** @defgroup Mcpwm_Private_FunctionDeclaration
 *  @{
 */
static void Mcpwm_ChIntHandler(Mcpwm_IdType McpwmId);
static void Mcpwm_OverflowIntHandler(Mcpwm_IdType McpwmId);
static void Mcpwm_RlflIntHandler(Mcpwm_IdType McpwmId);
void Mcpwm_DriverIrqHandler(void);
LOCAL_INLINE void Mcpwm_DisableWriteProtection(Mcpwm_IdType McpwmId);
LOCAL_INLINE void Mcpwm_EnableWriteProtection(Mcpwm_IdType McpwmId);

/*@} end of group Mcpwm_Private_FunctionDeclaration */

/** @defgroup Mcpwm_Private_FunctionDefinition
 *  @{
 */
/**
 * @brief      MCPWM channel interrupt handle  
 *
 * @param[in]  McpwmId:  Select the MCPWM ID
 *
 * @return none
 *
 */
static void Mcpwm_ChIntHandler(Mcpwm_IdType McpwmId)  
{
    uint32 McpwmChannel = 0U;
    uint32 McpwmIntStatus = 0U;
    uint32 IntStatus;

    /* Check the parameters */
    IntStatus = Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBSR  & Mcpwm_IntMaskTable[MCPWM_INT_ALL];
    
    for (McpwmChannel = (uint32)MCPWM_INT_CH0; McpwmChannel <= (uint32)MCPWM_INT_CH7; McpwmChannel++)
    {
        if ((0U != (IntStatus & ((uint32)1U << McpwmChannel))) && (1U == Mcpwm_RegBfPtr[McpwmId]->MCPWM_CFG[McpwmChannel].CHIE))
        {
            /* get interrupt Status */
            McpwmIntStatus = Mcpwm_RegWPtr[McpwmId]->MCPWM_CFG[McpwmChannel];
            /* only set interrupt flag bit */
            McpwmIntStatus = McpwmIntStatus & (~(MCPWM_CH_INT_MASK));
            /* clear interrupt Status */
            Mcpwm_RegWPtr[McpwmId]->MCPWM_CFG[McpwmChannel] = McpwmIntStatus;
            if(McpwmIsrCbFunc[McpwmId][McpwmChannel] != NULL_PTR)
            {
                /* call the callback function */
                McpwmIsrCbFunc[McpwmId][McpwmChannel]();
            }
            /* Disable the interrupt if callback function is not setup */
            else
            {
                Mcpwm_SetIntMask(McpwmId, (Mcpwm_IntType)McpwmChannel, COMMON_MASK);
            }
        }
    }
   
}

/**
 * @brief      MCPWM overflow interrupt handle
 *
 * @param[in]  McpwmId:  Select the MCPWM ID
 *
 * @return none
 *
 */
static void Mcpwm_OverflowIntHandler(Mcpwm_IdType McpwmId)
{
    uint32 McpwmIntStatus = 0U;
    uint32 IntStatus;

    /* Check the parameters */
    IntStatus = Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBSR  & Mcpwm_IntMaskTable[MCPWM_INT_ALL];
    
        /* Timer overflow 0 Interrupt */
    if(((IntStatus & Mcpwm_IntMaskTable[MCPWM_INT_TO0]) != 0UL)&&( 1U == Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBCR.TOIE0))

    {
        /* get interrupt Status */
        McpwmIntStatus = Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBSR;
        /* only check enabled interrupts */
        McpwmIntStatus = McpwmIntStatus & (~(MCPWM_TOF0_INT_MASK));
        /* clear interrupt Status */
        Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBSR = McpwmIntStatus;
        if(McpwmIsrCbFunc[McpwmId][MCPWM_INT_TO0] != NULL_PTR)
        {
            /* call the callback function */
            McpwmIsrCbFunc[McpwmId][MCPWM_INT_TO0]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            Mcpwm_SetIntMask(McpwmId, MCPWM_INT_TO0, COMMON_MASK);
        }
    }
    
    /* Timer overflow 1 Interrupt */
    if(((IntStatus & Mcpwm_IntMaskTable[MCPWM_INT_TO1]) != 0UL)&& (1U == Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBCR.TOIE1))
    {
        /* get interrupt Status */
        McpwmIntStatus = Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBSR;
        /* only check enabled interrupts */
        McpwmIntStatus = McpwmIntStatus & (~(MCPWM_TOF1_INT_MASK));
        /* clear interrupt Status */
        Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBSR = McpwmIntStatus;
        if(McpwmIsrCbFunc[McpwmId][MCPWM_INT_TO1] != NULL_PTR)
        {
            /* call the callback function */
            McpwmIsrCbFunc[McpwmId][MCPWM_INT_TO1]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            Mcpwm_SetIntMask(McpwmId, MCPWM_INT_TO1, COMMON_MASK);
        }
    }
    
    /* Timer overflow 2 Interrupt */
    if(((IntStatus & Mcpwm_IntMaskTable[MCPWM_INT_TO2]) != 0UL)&&(1U == Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBCR.TOIE2))
    {
        /* get interrupt Status */
        McpwmIntStatus = Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBSR;
        /* only check enabled interrupts */
        McpwmIntStatus = McpwmIntStatus & (~(MCPWM_TOF2_INT_MASK));
        /* clear interrupt Status */
        Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBSR = McpwmIntStatus;
        if(McpwmIsrCbFunc[McpwmId][MCPWM_INT_TO2] != NULL_PTR)
        {
            /* call the callback function */
            McpwmIsrCbFunc[McpwmId][MCPWM_INT_TO2]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            Mcpwm_SetIntMask(McpwmId, MCPWM_INT_TO2, COMMON_MASK);
        }
    }
    
    /* Timer overflow 3 Interrupt */
    if(((IntStatus & Mcpwm_IntMaskTable[MCPWM_INT_TO3]) != 0UL)&&(1U == Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBCR.TOIE3))
    {
        /* get interrupt Status */
        McpwmIntStatus = Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBSR;
        /* only check enabled interrupts */
        McpwmIntStatus = McpwmIntStatus & (~(MCPWM_TOF3_INT_MASK));
        /* clear interrupt Status */
        Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBSR = McpwmIntStatus;
        if(McpwmIsrCbFunc[McpwmId][MCPWM_INT_TO3] != NULL_PTR)
        {
            /* call the callback function */
            McpwmIsrCbFunc[McpwmId][MCPWM_INT_TO3]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            Mcpwm_SetIntMask(McpwmId, MCPWM_INT_TO3, COMMON_MASK);
        }
    }
    

}

/**
 * @brief      MCPWM reload interrupt handle
 *
 * @param[in]  McpwmId:  Select the MCPWM ID
 *
 * @return none
 *
 */
static void Mcpwm_RlflIntHandler(Mcpwm_IdType McpwmId)
{
    uint32 McpwmIntStatus = 0U;
    uint32 IntStatus;

    /* Check the parameters */
    IntStatus = Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBSR  & Mcpwm_IntMaskTable[MCPWM_INT_ALL];
    
    /* Reload0 Interrupt */
    if(((IntStatus & Mcpwm_IntMaskTable[MCPWM_INT_RLD0]) != 0UL)&&(1U == Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBCR.RLDIE0))
    {
        /* get interrupt Status */
        McpwmIntStatus = Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBSR;
        /* only check enabled interrupts */
        McpwmIntStatus = McpwmIntStatus & (~(MCPWM_RLDF0_INT_MASK));
        /* clear interrupt Status */
        Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBSR = McpwmIntStatus;
        if(McpwmIsrCbFunc[McpwmId][MCPWM_INT_RLD0] != NULL_PTR)
        {
            /* call the callback function */
            McpwmIsrCbFunc[McpwmId][MCPWM_INT_RLD0]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            Mcpwm_SetIntMask(McpwmId, MCPWM_INT_RLD0, COMMON_MASK);
        }
    }
    
    /* Reload1 Interrupt */
    if(((IntStatus & Mcpwm_IntMaskTable[MCPWM_INT_RLD1]) != 0UL)&&(1U == Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBCR.RLDIE1))
    {
         /* get interrupt Status */
        McpwmIntStatus = Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBSR;
        /* only check enabled interrupts */
        McpwmIntStatus = McpwmIntStatus & (~(MCPWM_RLDF1_INT_MASK));
        /* clear interrupt Status */
        Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBSR = McpwmIntStatus;
        if(McpwmIsrCbFunc[McpwmId][MCPWM_INT_RLD1] != NULL_PTR)
        {
            /* call the callback function */
            McpwmIsrCbFunc[McpwmId][MCPWM_INT_RLD1]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            Mcpwm_SetIntMask(McpwmId, MCPWM_INT_RLD1, COMMON_MASK);
        }
    }
    
    /* Reload2 Interrupt */
    if(((IntStatus & Mcpwm_IntMaskTable[MCPWM_INT_RLD2]) != 0UL)&&(1U == Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBCR.RLDIE2))
    {
         /* get interrupt Status */
        McpwmIntStatus = Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBSR;
        /* only check enabled interrupts */
        McpwmIntStatus = McpwmIntStatus & (~(MCPWM_RLDF2_INT_MASK));
        /* clear interrupt Status */
        Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBSR = McpwmIntStatus;
        if(McpwmIsrCbFunc[McpwmId][MCPWM_INT_RLD2] != NULL_PTR)
        {
            /* call the callback function */
            McpwmIsrCbFunc[McpwmId][MCPWM_INT_RLD2]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            Mcpwm_SetIntMask(McpwmId, MCPWM_INT_RLD2, COMMON_MASK);
        }
    }
    
    /* Reload3 Interrupt */
    if(((IntStatus & Mcpwm_IntMaskTable[MCPWM_INT_RLD3]) != 0UL)&&(1U == Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBCR.RLDIE3))
    {
         /* get interrupt Status */
        McpwmIntStatus = Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBSR;
        /* only check enabled interrupts */
        McpwmIntStatus = McpwmIntStatus & (~(MCPWM_RLDF3_INT_MASK));
        /* clear interrupt Status */
        Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBSR = McpwmIntStatus;
        if(McpwmIsrCbFunc[McpwmId][MCPWM_INT_RLD3] != NULL_PTR)
        {
            /* call the callback function */
            McpwmIsrCbFunc[McpwmId][MCPWM_INT_RLD3]();
        }
        /* Disable the interrupt if callback function is not setup */
        else
        {
            Mcpwm_SetIntMask(McpwmId, MCPWM_INT_RLD3, COMMON_MASK);
        }
    }

}

/**
 * @brief      MCPWM  IRQHandler
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void Mcpwm_DriverIrqHandler(void)
{
    Mcpwm_ChIntHandler(MCPWM0_ID);
    Mcpwm_OverflowIntHandler(MCPWM0_ID);
    Mcpwm_RlflIntHandler(MCPWM0_ID);
}

/**
 * @brief       MCPWM Disable Write protection Function
 *
 * @param[in]  McpwmId:  Select the MCPWM ID: MCPWM0_ID.
 *
 * @return none
 *
 */
LOCAL_INLINE void Mcpwm_DisableWriteProtection(Mcpwm_IdType McpwmId)
{
    

   
    if(Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBCR.WPEN == 1U)
    {
        Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBSR.WPDIS = (uint32)1UL;
    }
    
       
}

/**
 * @brief       MCPWM Enable Write Protection Function
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID.
 *
 * @return none
 *
 */
LOCAL_INLINE void Mcpwm_EnableWriteProtection(Mcpwm_IdType McpwmId)
{
    
    
    Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBCR.WPEN = (uint32)1UL;
    
}

/** @} end of group Private_FunctionDefinition */

/** @defgroup Public_FunctionDefinition
 *  @{
 */

/**
 * @brief       MCPWM Start counter with clock configuration
 *
 * @param[in]  McpwmId:     Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  ClkSource:   Select MCPWM clock source:
 *                                  - Mcpwm_CLK_SOURCE_CORE
 *                                  - Mcpwm_CLK_SOURCE_EXTERNAL
 * @param[in]  Divider:     Select MCPWM clock divider.
 *
 * @return none
 *
 */
void Mcpwm_ConfigClockSource(Mcpwm_IdType McpwmId, Mcpwm_ClkSourceType ClkSource, 
                     Mcpwm_ClkDivideType Divider)
{
    Mcpwm_DisableWriteProtection(McpwmId);
    
    
    Mcpwm_RegBfPtr[McpwmId]->MCPWM_TIMEBASE.CKSRC = (uint32)ClkSource;
    Mcpwm_RegBfPtr[McpwmId]->MCPWM_TIMEBASE.PSDIV = (uint32)Divider;
    
    Mcpwm_EnableWriteProtection(McpwmId);
}

/**
 * @brief       MCPWM Start counter
 *
 * @param[in]  McpwmId:       Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  CounterId:     Selected Counter ID.
 *
 * @return none
 *
 */
void Mcpwm_StartCounter(Mcpwm_IdType McpwmId, Mcpwm_CounterIdType CounterId)
{
    Mcpwm_DisableWriteProtection(McpwmId);
    
    
    uint32 RegVal = Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBCR;
    
    Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBCR = RegVal | ((uint32)0x1000UL << ((uint32)(CounterId)));
    
    Mcpwm_EnableWriteProtection(McpwmId);
}

/**
 * @brief       MCPWM Stop counter
 *
 * @param[in]  McpwmId:       Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  CounterId:     Selected Counter ID.
 *
 * @return none
 *
 */
void Mcpwm_StopCounter(Mcpwm_IdType McpwmId, Mcpwm_CounterIdType CounterId)
{
    Mcpwm_DisableWriteProtection(McpwmId);
    

    uint32 RegVal = Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBCR;

    Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBCR = RegVal & (~(0x1000UL << (uint32)(CounterId))); 
    
    Mcpwm_EnableWriteProtection(McpwmId);
}

/**
 * @brief       MCPWM Start Globale counter
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID.
 *
 * @return none
 *
 */
void Mcpwm_StartGlobalCounter(Mcpwm_IdType McpwmId)
{
    Mcpwm_DisableWriteProtection(McpwmId);
     

    
    Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBCR.GLBCNTEN = (uint32)1UL;
   
    Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBCR.CNTEN0 = (uint32)0UL;
    Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBCR.CNTEN1 = (uint32)0UL;
    Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBCR.CNTEN2 = (uint32)0UL;
    Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBCR.CNTEN3 = (uint32)0UL;
     
    Mcpwm_EnableWriteProtection(McpwmId);
}

/**
 * @brief       MCPWM Stop Global counter
 *
 * @param[in]  McpwmId:  Select the MCPWM ID: MCPWM0_ID.
 *
 * @return none
 *
 */
void Mcpwm_StopGlobalCounter(Mcpwm_IdType McpwmId)
{

    Mcpwm_DisableWriteProtection(McpwmId);
    

    Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBCR.GLBCNTEN = (uint32)0UL;
    
    Mcpwm_EnableWriteProtection(McpwmId);
}

/**
 * @brief       MCPWM Set Counter Counting Mode Function
 *
 * @param[in]  McpwmId:        Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  CounterId:      Selected Counter ID.
 * @param[in]  CountingMode:   Counter Counting Mode.
 *
 * @return none
 *
 */
void Mcpwm_SetCountingMode(Mcpwm_IdType McpwmId, Mcpwm_CounterIdType CounterId,
                                Mcpwm_CountingModeType CountingMode)
{
    Mcpwm_DisableWriteProtection(McpwmId);
    
    
    uint32 RegVal = Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBCR;
    
    if(MCPWM_COUNTING_UP == CountingMode)
    {
        Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBCR = RegVal & (~(0x100UL << (uint32)(CounterId)));  
    }
    else
    {
        Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBCR = RegVal | (0x100UL << (uint32)(CounterId));  
    }
    
    Mcpwm_EnableWriteProtection(McpwmId);   
}

/**
 * @brief       MCPWM Get Counter Value Function
 *
 * @param[in]  McpwmId:     Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  CounterId:   Selected Counter ID.
 *
 * @return Counter Init Value
 *
 */
uint16 Mcpwm_GetCounterVal(Mcpwm_IdType McpwmId, Mcpwm_CounterIdType CounterId)
{
    
    return (uint16)(Mcpwm_RegBfPtr[McpwmId]->MCPWM_CNT[CounterId].CNT);
}

/**
 * @brief       MCPWM Set Counter Mod(Max) Value Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  CounterId:  Selected Counter ID.
 * @param[in]  ModVal:     Counter MOD value.
 *
 * @return none
 *
 */
void Mcpwm_SetCounterModVal(Mcpwm_IdType McpwmId, Mcpwm_CounterIdType CounterId, uint16 ModVal)
{
    
    
    Mcpwm_RegBfPtr[McpwmId]->MCPWM_MOD[CounterId].MOD = (uint32)ModVal;
    
}

/**
 * @brief       MCPWM Get Counter MOD Value Function
 *
 * @param[in]  McpwmId:     Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  CounterId:   Selected Counter ID.
 *
 * @return Counter MOD Value
 *
 */
uint16 Mcpwm_GetCounterModVal(Mcpwm_IdType McpwmId, Mcpwm_CounterIdType CounterId)
{
    
    return (uint16)(Mcpwm_RegBfPtr[McpwmId]->MCPWM_MOD[CounterId].MOD);
}

/**
 * @brief       MCPWM Load Counter Init Value Function
 *
 * @param[in]  McpwmId:     Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  CounterId:   Selected Counter ID.
 *
 * @return none
 *
 */
void Mcpwm_ResetCounter(Mcpwm_IdType McpwmId, Mcpwm_CounterIdType CounterId)
{
    

    Mcpwm_RegBfPtr[McpwmId]->MCPWM_CNT[CounterId].CNT = (uint16)0x0U; 
    
}

/**
 * @brief       MCPWM Set deadtime Value Function
 *
 * @param[in]  McpwmId:     Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  PairId:      Select the MCPWM pair ID.
 * @param[in]  DeadTimeVal: Deadtime value, max value is 0xFFF.
 *
 * @return none
 *
 */
void Mcpwm_SetDeadTimeVal(Mcpwm_IdType McpwmId, Mcpwm_PairIdType PairId, uint16 DeadTimeVal)
{
    Mcpwm_DisableWriteProtection(McpwmId);

    
    Mcpwm_RegBfPtr[McpwmId]->MCPWM_DTVAL[PairId].DTVAL = (uint32)DeadTimeVal; 
    
    Mcpwm_EnableWriteProtection(McpwmId); 
}

/**
 * @brief       MCPWM Get deadtime Value Function
 *
 * @param[in]  McpwmId:     Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  PairId:      Select the MCPWM pair ID.
 *
 * @return Deadtime Value
 *
 */
uint16 Mcpwm_GetDeadTimeVal(Mcpwm_IdType McpwmId, Mcpwm_PairIdType PairId)
{
    
    return (uint16)(Mcpwm_RegBfPtr[McpwmId]->MCPWM_DTVAL[PairId].DTVAL);
}

/**
 * @brief       MCPWM Set MOD Dither  Function
 *
 * @param[in]  McpwmId:      Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  CounterId:    Selected Counter ID.
 * @param[in]  modDitherVal: Mod dither value, max value is 0x1F.
 *
 * @return none
 *
 */
void Mcpwm_SetModDither(Mcpwm_IdType McpwmId, Mcpwm_CounterIdType CounterId, uint8 ModDither)
{
    
    Mcpwm_RegBfPtr[McpwmId]->MCPWM_MOD_DITHER[CounterId].MOD_DITHER = (uint32)ModDither;
        
}

/**
 * @brief       MCPWM enable channel output Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  ChannelId:  Select Channel Id.
 *
 * @return none
 *
 */
void Mcpwm_EnableChannelOutput(Mcpwm_IdType McpwmId, Mcpwm_ChannelIdType ChannelId)
{
    
    
    uint32 RegVal = Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBCR;
    
    Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBCR = RegVal | (0x1UL << (uint32)(ChannelId)); 
    
}

/**
 * @brief       MCPWM disable channel output Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  ChannelId:  Select Channel Id.
 *
 * @return none
 *
 */
void Mcpwm_DisableChannelOutput(Mcpwm_IdType McpwmId, Mcpwm_ChannelIdType ChannelId)
{
    
    uint32 RegVal = Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBCR;
    
    Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBCR = RegVal & (~(0x1UL << (uint32)(ChannelId)));
    
}


/**
 * @brief       MCPWM  Get Output Status of selected channel
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  ChannelId:  Select Channel Id.
 *
 * @return    Mcpwm_OutputStatusType: Channel Output Status.  
 * @retval    MCPWM_OUT_LOW         : MCPWM channel output is low .
 * @retval    MCPWM_OUT_HIGH        : MCPWM channel output is high.                        
 *
 */
Mcpwm_OutputStatusType Mcpwm_GetChannelOutputStatus(Mcpwm_IdType McpwmId, Mcpwm_ChannelIdType ChannelId)
{

    return (Mcpwm_OutputStatusType)Mcpwm_RegBfPtr[McpwmId]->MCPWM_CFG[ChannelId].CHOS;
}

/**
 * @brief       MCPWM set channel pulse Polarity for selected channel
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  ChannelId:  Select Channel Id.
 * @param[in]  Cpp:        Select pulse Polarity.
 *
 * @return none
 *
 */
void Mcpwm_SetChannelPulsePol(Mcpwm_IdType McpwmId, Mcpwm_ChannelIdType ChannelId,
                                Mcpwm_Pulse_PolarityType Cpp)
{
    Mcpwm_DisableWriteProtection(McpwmId);

    Mcpwm_RegBfPtr[McpwmId]->MCPWM_CFG[ChannelId].CPP = (uint32)Cpp;
    Mcpwm_EnableWriteProtection(McpwmId);
    
}

/**
 * @brief       MCPWM Set  Compare Value Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  ChannelId:  Select channel ID
 * @param[in]  CVal:       Compare Value.
 *
 * @return none
 *
 */
void Mcpwm_SetChannelCVal(Mcpwm_IdType McpwmId, Mcpwm_ChannelIdType ChannelId, uint16 CVal)
{
    

    Mcpwm_RegBfPtr[McpwmId]->MCPWM_CV[ChannelId].CV = (uint32)CVal;
    
}

/**
 * @brief       MCPWM Get Compare Value Function
 *
 * @param[in]   McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]   ChannelId:  Select channel ID.
 *
 * @return Compare Value
 *
 */
uint16 Mcpwm_GetChannelCVal(Mcpwm_IdType McpwmId, Mcpwm_ChannelIdType ChannelId)
{
    
    return ((uint16)(Mcpwm_RegBfPtr[McpwmId]->MCPWM_CV[ChannelId].CV));
}

/**
 * @brief       MCPWM Set  CVal Dither Value Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  ChannelId:  Select channel ID.
 * @param[in]  CvDither:   Compare Value Dither, max value is 0x1F.
 *
 * @return none
 *
 */
void Mcpwm_SetChannelCVDither(Mcpwm_IdType McpwmId, Mcpwm_ChannelIdType ChannelId, uint8 CvDither)
{
    
    
    Mcpwm_RegBfPtr[McpwmId]->MCPWM_CV_DITHER[ChannelId].CV_DITHER = (uint32)CvDither;
    
}

/**
 * @brief       MCPWM Set  channel output value when counter is off
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  ChannelId:  Select channel ID.
 * @param[in]  Level:      Low_level/high_level for channel output.
 *
 * @return none
 *
 */
void Mcpwm_SetChannelOffValue(Mcpwm_IdType McpwmId, Mcpwm_ChannelIdType ChannelId,
                              Common_LevelType Level)
{
    Mcpwm_DisableWriteProtection(McpwmId);
    
    
    uint32 RegVal = Mcpwm_RegWPtr[McpwmId]->MCPWM_OUTCR;
    
    if(COMMON_LEVEL_LOW == Level)
    {
        Mcpwm_RegWPtr[McpwmId]->MCPWM_OUTCR = RegVal & (~(0x100UL << (uint32)(ChannelId)));  
    }
    else
    {
        Mcpwm_RegWPtr[McpwmId]->MCPWM_OUTCR = RegVal | (0x100UL << (uint32)(ChannelId));  
    } 
    
    Mcpwm_EnableWriteProtection(McpwmId);     
}

/**
 * @brief       MCPWM set channel output Polarity for selected channel
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  ChannelId: Select Channel Id.
 * @param[in]  Pol:       Output Polarity.
 *
 * @return none
 *
 */
void Mcpwm_SetChannelPolarity(Mcpwm_IdType McpwmId, Mcpwm_ChannelIdType ChannelId,
                                Mcpwm_PolarityType Pol)
{
    Mcpwm_DisableWriteProtection(McpwmId);
    
    
    uint32 RegVal = Mcpwm_RegWPtr[McpwmId]->MCPWM_OUTCR;
    
    if(MCPWM_POL_ACTIVE_HIGH == Pol)
    {
        /*output Polarity: high Level is active*/
        Mcpwm_RegWPtr[McpwmId]->MCPWM_OUTCR = RegVal & (~(0x1UL << (uint32)(ChannelId)));  
    }
    else
    {
        /*output Polarity: low Level is active*/
        Mcpwm_RegWPtr[McpwmId]->MCPWM_OUTCR = RegVal | (0x1UL << (uint32)(ChannelId));  
    } 
    
    Mcpwm_EnableWriteProtection(McpwmId);
}

/**
 * @brief       MCPWM Set channel match trigger Mode Function
 *
 * @param[in]  McpwmId:      Select the MCPWM ID: MCPWM0_ID .
 * @param[in]  ChannelId:    Select channel id .
 * @param[in]  Mode:          Mcpwm_MatchTriggerModeType: DISABLE_MODE,ENABLE_UP_GENERATE_MODE,ENABLE_DOWN_GENERATE_MODE,ENABLE_UP_DOWN_GENERATE_MODE
 *
 * @return none
 *
 */
void Mcpwm_SetChannelMatchTriggerMode(Mcpwm_IdType McpwmId, Mcpwm_ChannelIdType ChannelId, 
                                Mcpwm_MatchTriggerModeType Mode)
{
    
     
    switch (ChannelId)
    {
        case MCPWM_CHANNEL_0:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_OUTTRIG.TRIGE0 = (uint32)Mode;
            break;
            
        case MCPWM_CHANNEL_1:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_OUTTRIG.TRIGE1 = (uint32)Mode;
            break;

        case MCPWM_CHANNEL_2:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_OUTTRIG.TRIGE2 = (uint32)Mode;
            break;

        case MCPWM_CHANNEL_3:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_OUTTRIG.TRIGE3 = (uint32)Mode;
            break;
            
        case MCPWM_CHANNEL_4:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_OUTTRIG.TRIGE4 = (uint32)Mode;
            break;

        case MCPWM_CHANNEL_5:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_OUTTRIG.TRIGE5 = (uint32)Mode;
            break;

        case MCPWM_CHANNEL_6:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_OUTTRIG.TRIGE6 = (uint32)Mode;
            break;
            
        case MCPWM_CHANNEL_7:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_OUTTRIG.TRIGE7 = (uint32)Mode;
            break;

        default:
            /* do nothing */
            break;            
    }
    
}

/**
 * @brief       MCPWM Set init trigger Cmd enable/disable Function
 *
 * @param[in]  McpwmId: Select the MCPWM ID: MCPWM0_ID .
 * @param[in]  Cmd:     Enable/disable.
 *
 * @return none
 *
 */
void Mcpwm_EnableInitTrigger(Mcpwm_IdType McpwmId, Common_ControlStateType Cmd)
{
    
    
    Mcpwm_RegBfPtr[McpwmId]->MCPWM_OUTTRIG.INITRIGE = (uint32)Cmd;
    
}

/**
 * @brief       MCPWM Set End trigger Cmd enable/disable Function
 *
 * @param[in]  McpwmId: Select the MCPWM ID: MCPWM0_ID .
 * @param[in]  Cmd:     Enable/disable.
 *
 * @return none
 *
 */
void Mcpwm_EnableEndTrigger(Mcpwm_IdType McpwmId, Common_ControlStateType Cmd)
{

    
    Mcpwm_RegBfPtr[McpwmId]->MCPWM_OUTTRIG.ENDTRIGE = (uint32)Cmd;
    
}

/**
 * @brief       MCPWM Set  channel output software control value
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID .
 * @param[in]  ChannelId:  Select channel ID.
 * @param[in]  LogicStatus:    Logic Status for channel output.
 *
 * Note: Donot Call this function more than one time before PWM synchronization
 * event occur When SYNCOSWC = MCPWM_UPDATE_PWM_SYN.
 * Config with POL decide the Output
 *
 * @return none
 *
 */
void Mcpwm_SetChannelOCV(Mcpwm_IdType McpwmId, Mcpwm_ChannelIdType ChannelId,
                            Mcpwm_LogicStatusType  LogicStatus)
{
    

    
    uint32 RegVal = Mcpwm_RegWPtr[McpwmId]->MCPWM_OUTSWCR;
    
    if(MCPWM_LOGIC_LOW == LogicStatus)
    {
        Mcpwm_RegWPtr[McpwmId]->MCPWM_OUTSWCR = RegVal & (~(0x100UL << (uint32)(ChannelId)));  
    }
    else
    {
        Mcpwm_RegWPtr[McpwmId]->MCPWM_OUTSWCR = RegVal | (0x100UL << (uint32)(ChannelId));  
    }  
    
}

/**
 * @brief       MCPWM Set channel output software control enable/disable Function
 *
 * @param[in]  McpwmId:      Select the MCPWM ID: MCPWM0_ID .
 * @param[in]  ChannelId:    Select channel id .
 * @param[in]  Cmd:          Enable/disable.
 *
 * Note: Donot Call this function more than one time before PWM synchronization
 * event occur When SYNCOSWC = MCPWM_UPDATE_PWM_SYN.
 *
 * @return none
 *
 */
void Mcpwm_EnableChannelOC(Mcpwm_IdType McpwmId, Mcpwm_ChannelIdType ChannelId, 
                                Common_ControlStateType Cmd)
{
    

    
    uint32 RegVal = Mcpwm_RegWPtr[McpwmId]->MCPWM_OUTSWCR;
    
    if(COMMON_DISABLE == Cmd)
    {
        Mcpwm_RegWPtr[McpwmId]->MCPWM_OUTSWCR = RegVal & (~(0x1UL << (uint32)(ChannelId)));  
    }
    else
    {
        Mcpwm_RegWPtr[McpwmId]->MCPWM_OUTSWCR = RegVal | (0x1UL << (uint32)(ChannelId));  
    } 
    
}

/****************************************************************************//**
 * @brief       MCPWM Config  output software control for All channels 
 *
 * @param[in]  mcpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  Config:     Config values.
 *
 * @return none
 *
 *******************************************************************************/
void Mcpwm_ConfigAllOutputSoftwareControl(Mcpwm_IdType McpwmId, uint16 Config)
{
    
    uint32 RegVal = Mcpwm_RegWPtr[McpwmId]->MCPWM_OUTSWCR & 0xFFFF0000UL;

    Mcpwm_RegWPtr[McpwmId]->MCPWM_OUTSWCR = RegVal | (uint32)Config;  
 
}

/**
 * @brief       MCPWM Set combine enable/disable for pairs of channel
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID .
 * @param[in]  PairId:    Select pair id .
 * @param[in]  Cmd:       Enable/disable.
 *
 * @return none
 *
 */
void Mcpwm_EnablePairCombine(Mcpwm_IdType McpwmId, Mcpwm_PairIdType PairId, 
                                Common_ControlStateType Cmd)
{
    Mcpwm_DisableWriteProtection(McpwmId);
    

    
    uint32 RegVal = Mcpwm_RegWPtr[McpwmId]->MCPWM_PCR;
    
    if(COMMON_DISABLE == Cmd)
    {
        Mcpwm_RegWPtr[McpwmId]->MCPWM_PCR = RegVal & (~(0x40UL << ((uint32)PairId*8UL)));  
    }
    else
    {
        Mcpwm_RegWPtr[McpwmId]->MCPWM_PCR = RegVal | (0x40UL << ((uint32)PairId*8UL));  
    } 
    
    Mcpwm_EnableWriteProtection(McpwmId);    
}

/**
 * @brief       MCPWM Select channel value  for pairs of channel
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  PairId:    Select pair id .
 * @param[in]  CvSel:     Select channel value .
 *
 * @return none
 *
 */
void Mcpwm_SelPairChannelValue(Mcpwm_IdType McpwmId, Mcpwm_PairIdType PairId, 
                                Mcpwm_ChannelValueSelType CvSel)
{
    Mcpwm_DisableWriteProtection(McpwmId);
    
    switch (PairId)
    {
        case MCPWM_PAIR_CHANNEL_0:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_PCR.CVSEL0 = (uint32)CvSel;
            break;
            
        case MCPWM_PAIR_CHANNEL_1:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_PCR.CVSEL1 = (uint32)CvSel;
            break;

        case MCPWM_PAIR_CHANNEL_2:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_PCR.CVSEL2 = (uint32)CvSel;
            break;

        case MCPWM_PAIR_CHANNEL_3:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_PCR.CVSEL3 = (uint32)CvSel;
            break;

        default:
            /* do nothing */
            break;            
    }
    
    Mcpwm_EnableWriteProtection(McpwmId); 
}

/**
 * @brief       MCPWM Set pulse edge control mode for pairs of channel
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  PairId:    Select pair id .
 * @param[in]  Pec:       Pulse Edge Ctrl.
 *
 * @return none
 *
 */
void Mcpwm_SetPairPulseEdgeCtrlMode(Mcpwm_IdType McpwmId, Mcpwm_PairIdType PairId, 
                                Mcpwm_PulseEdgeCtrlType Pec)
{
    Mcpwm_DisableWriteProtection(McpwmId);
    
 
    
    switch (PairId)
    {
        case MCPWM_PAIR_CHANNEL_0:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_PCR.PEC0 = (uint32)Pec;
            break;
            
        case MCPWM_PAIR_CHANNEL_1:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_PCR.PEC1 = (uint32)Pec;
            break;

        case MCPWM_PAIR_CHANNEL_2:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_PCR.PEC2 = (uint32)Pec;
            break;

        case MCPWM_PAIR_CHANNEL_3:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_PCR.PEC3 = (uint32)Pec;
            break;

        default:
            /* do nothing */
            break;            
    }
    
    Mcpwm_EnableWriteProtection(McpwmId);
}

/**
 * @brief       MCPWM enable asymmetric PWM output  for pairs of channel
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  PairId:    Select pair id .
 * @param[in]  Asym:      Symmetric/asymmetric.
 *
 * @return none
 *
 */
void Mcpwm_EnablePairAsymmetric(Mcpwm_IdType McpwmId, Mcpwm_PairIdType PairId, 
                                Mcpwm_AsymType Asym)
{
    Mcpwm_DisableWriteProtection(McpwmId);
 
    
    switch (PairId)
    {
        case MCPWM_PAIR_CHANNEL_0:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_PCR.ASYMEN0 = (uint32)Asym;
            break;
            
        case MCPWM_PAIR_CHANNEL_1:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_PCR.ASYMEN1 = (uint32)Asym;
            break;

        case MCPWM_PAIR_CHANNEL_2:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_PCR.ASYMEN2 = (uint32)Asym;
            break;

        case MCPWM_PAIR_CHANNEL_3:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_PCR.ASYMEN3 = (uint32)Asym;
            break;

        default:
            /* do nothing */
            break;            
    }  
     Mcpwm_EnableWriteProtection(McpwmId);
    
}

/**
 * @brief       MCPWM Set enable/disable Synchronization of CV(n) and CV(n+1) for pairs of channel
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID .
 * @param[in]  PairId:    Select pair id .
 * @param[in]  Cmd:       Enable/disable.
 *
 * @return none
 *
 */
void Mcpwm_EnablePairSynchronization(Mcpwm_IdType McpwmId, Mcpwm_PairIdType PairId, 
                                Common_ControlStateType Cmd)
{
    
    
    switch (PairId)
    {
        case MCPWM_PAIR_CHANNEL_0:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_PCR.SYNCEN0 = (uint32)Cmd;
            break;
            
        case MCPWM_PAIR_CHANNEL_1:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_PCR.SYNCEN1 = (uint32)Cmd;
            break;

        case MCPWM_PAIR_CHANNEL_2:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_PCR.SYNCEN2 = (uint32)Cmd;
            break;

        case MCPWM_PAIR_CHANNEL_3:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_PCR.SYNCEN3 = (uint32)Cmd;
            break;

        default:
            /* do nothing */
            break;            
    } 
       
}

/**
 * @brief       MCPWM Set deadtime insertion enable/disable for pairs of channel
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  PairId:    Select pair id .
 * @param[in]  Cmd:       Enable/disable.
 *
 * @return none
 *
 */
void Mcpwm_EnablePairDeadtime(Mcpwm_IdType McpwmId, Mcpwm_PairIdType PairId, 
                                Common_ControlStateType Cmd)
{
    Mcpwm_DisableWriteProtection(McpwmId);
    
 
    
    switch (PairId)
    {
        case MCPWM_PAIR_CHANNEL_0:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_PCR.DTEN0 = (uint32)Cmd;
            break;
            
        case MCPWM_PAIR_CHANNEL_1:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_PCR.DTEN1 = (uint32)Cmd;
            break;

        case MCPWM_PAIR_CHANNEL_2:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_PCR.DTEN2 = (uint32)Cmd;
            break;

        case MCPWM_PAIR_CHANNEL_3:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_PCR.DTEN3 = (uint32)Cmd;
            break;

        default:
            /* do nothing */
            break;            
    } 
    
    Mcpwm_EnableWriteProtection(McpwmId);
}

/**
 * @brief       MCPWM Set fault control enable/disable for pairs of channel
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID .
 * @param[in]  PairId:    Select pair id .
 * @param[in]  Cmd:       Enable/disable.
 *
 * @return none
 *
 */
void Mcpwm_EnablePairFaultCtrl(Mcpwm_IdType McpwmId, Mcpwm_PairIdType PairId, 
                                Common_ControlStateType Cmd)
{
    Mcpwm_DisableWriteProtection(McpwmId);
    
 
    
    switch (PairId)
    {
        case MCPWM_PAIR_CHANNEL_0:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_PCR.FCTLEN0 = (uint32)Cmd;
            break;
            
        case MCPWM_PAIR_CHANNEL_1:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_PCR.FCTLEN1 = (uint32)Cmd;
            break;

        case MCPWM_PAIR_CHANNEL_2:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_PCR.FCTLEN2 = (uint32)Cmd;
            break;

        case MCPWM_PAIR_CHANNEL_3:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_PCR.FCTLEN3 = (uint32)Cmd;
            break;

        default:
            /* do nothing */
            break;            
    }
    
    Mcpwm_EnableWriteProtection(McpwmId);
}


/**
 * @brief       MCPWM Set fault input filter value
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  FilterVal: Fault input filter value(max value is 0xF, 0 is disabled).
 *
 * @return none
 *
 */
void Mcpwm_SetFaultFilterVal(Mcpwm_IdType McpwmId, uint8 FilterVal)
{    
    Mcpwm_RegBfPtr[McpwmId]->MCPWM_FLTCR.FIFVAL = (uint32)FilterVal; 
}

/**
 * @brief       MCPWM set fault input filter enable/disable for selected input channel
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  InputId:   Select fault input channel Id.
 * @param[in]  Cmd:       Fault input enable/disable.
 *
 * @return none
 *
 */
void Mcpwm_EnableFaultFilter(Mcpwm_IdType McpwmId, Common_ControlStateType Cmd)
{
    Mcpwm_DisableWriteProtection(McpwmId);
    Mcpwm_RegBfPtr[McpwmId]->MCPWM_FLTCR.FIFEN0 = (uint32)Cmd;
    Mcpwm_EnableWriteProtection(McpwmId);
}

/**
 * @brief       MCPWM Set fault output State
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  State:     Safe State / tri-State, if Safe State, 
 *                        the safe State is decided by FLTASS.
 *
 * @return none
 *
 */
void Mcpwm_SetFaultOutputState(Mcpwm_IdType McpwmId, Mcpwm_FaultSafeStateType State)
{
    Mcpwm_DisableWriteProtection(McpwmId);
    Mcpwm_RegBfPtr[McpwmId]->MCPWM_FLTCR.FSTATE = (uint32)State;
    Mcpwm_EnableWriteProtection(McpwmId);
}

/**
 * @brief       MCPWM Set fault clear Mode
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  Mode:      Fault clear Mode.
 *
 * @return none
 *
 */
void Mcpwm_SetFaultClearMode(Mcpwm_IdType McpwmId, Mcpwm_FaultClearModeType Mode)
{
    Mcpwm_DisableWriteProtection(McpwmId);
    Mcpwm_RegBfPtr[McpwmId]->MCPWM_FLTCR.FLTCM = (uint32)Mode;  
    Mcpwm_EnableWriteProtection(McpwmId);
}

/**
 * @brief       MCPWM set fault input channel Polarity for selected input channel
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  InputId:   Select fault input channel Id.
 * @param[in]  Pol:       Fault input channel Polarity.
 *
 * @return none
 *
 */
void Mcpwm_SetFaultInputPolarity(Mcpwm_IdType McpwmId, Mcpwm_PolarityType Pol)
{
    Mcpwm_DisableWriteProtection(McpwmId);
    Mcpwm_RegBfPtr[McpwmId]->MCPWM_FLTCR.FLTPOL0 = (uint32)Pol;
    Mcpwm_EnableWriteProtection(McpwmId);   
}

/**
 * @brief       MCPWM set fault input enable/disable for selected input channel
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  InputId:   Select fault input channel Id.
 * @param[in]  Cmd:       Fault input enable/disable.
 *
 * @return none
 *
 */
void Mcpwm_EnableFaultInput(Mcpwm_IdType McpwmId,  Common_ControlStateType Cmd)
{
    Mcpwm_DisableWriteProtection(McpwmId);
    Mcpwm_RegBfPtr[McpwmId]->MCPWM_FLTCR.FLTEN0 = (uint32)Cmd;
    Mcpwm_EnableWriteProtection(McpwmId); 
}

/**
 * @brief       MCPWM set selected channel safe Status value for fault Group A(fault 
                input 0 ).
 *
 * @param[in]  McpwmId:   Select the MCPWM ID: MCPWM0_ID .
 * @param[in]  ChannelId: Select channel Id.
 * @param[in]  Level:     Safe Status Level: low Level/high Level.
 *
 * @return none
 *
 */
void Mcpwm_SetChannelSafeStatusValForFaultA(Mcpwm_IdType McpwmId, 
                                            Mcpwm_ChannelIdType ChannelId,
                                            Common_LevelType Level)
{
    Mcpwm_DisableWriteProtection(McpwmId);
    uint32 RegVal = Mcpwm_RegWPtr[McpwmId]->MCPWM_FLTASS;
    if(COMMON_LEVEL_LOW == Level)
    {
        Mcpwm_RegWPtr[McpwmId]->MCPWM_FLTASS = RegVal & (~(0x1UL << (uint32)(ChannelId)));  
    }
    else
    {
        Mcpwm_RegWPtr[McpwmId]->MCPWM_FLTASS = RegVal | (0x1UL << (uint32)(ChannelId));  
    }
    
    Mcpwm_EnableWriteProtection(McpwmId);
}



/**
 * @brief       MCPWM output software control Config Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  ChannelId:  Select Channel Id.
 * @param[in]  Config:     Software Control Config.
 *
 * @Note: This  function cannot be used when SYNCOSWC = MCPWM_UPDATE_PWM_SYN:
 * OUTSWCR register is updated with its buffer value only by PWM synchronization
 * Config with POL decide the Output
 *
 * @return none
 *
 */
void Mcpwm_OutputSWCtrlConfig(Mcpwm_IdType McpwmId, Mcpwm_ChannelIdType ChannelId, 
                            const Mcpwm_OutputSWCtrlConfigType* Config)
{
    Mcpwm_SetChannelOCV(McpwmId, ChannelId, Config->OutputLogicStatus);
    Mcpwm_EnableChannelOC(McpwmId, ChannelId, Config->OutputSWCtrlEnable);
}

/**
 * @brief       MCPWM get match trigger flag Function when any channel match trigger
 *              is generated, this flag is set by hardware.
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 *
 * @return     Common_FlagStatusType.
 * @retval     COMMON_RESET : Reset state, No channel match trigger is generated. 
 * @retval     COMMON_SET   : Set state, At least one channel match trigger is generated.
 *
 */
Common_FlagStatusType Mcpwm_GetMatchTriggerFlag(Mcpwm_IdType McpwmId)
{
 
    
    return (Common_FlagStatusType)(Mcpwm_RegBfPtr[McpwmId]->MCPWM_OUTTRIG.TRIGF);
}

/**
 * @brief       MCPWM independent PWM channel Config Function
 *
 * @param[in]  McpwmId:         Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  ChannelConfig:   Independent PWM Output Channel Config.
 *
 * @return none
 *
 */
void Mcpwm_ConfigIndependentPwmChannel(Mcpwm_IdType McpwmId, const Mcpwm_PwmChannelConfigType * ChannelConfig)
{
    uint8 PairId = (uint8)ChannelConfig->ChannelId >> 1U;
    
    if(COMMON_ENABLE == ChannelConfig->ChannelOutputEnable)
    {
       Mcpwm_EnableChannelOutput(McpwmId, ChannelConfig->ChannelId);
    }
    else
    {
       Mcpwm_DisableChannelOutput(McpwmId, ChannelConfig->ChannelId);
    }
    Mcpwm_SetChannelPulsePol(McpwmId, ChannelConfig->ChannelId, ChannelConfig->PulsePol);
    Mcpwm_SetChannelPolarity(McpwmId, ChannelConfig->ChannelId, ChannelConfig->Polarity);
    Mcpwm_SetChannelCVal(McpwmId, ChannelConfig->ChannelId, ChannelConfig->CompareValue);
    Mcpwm_SetChannelOffValue(McpwmId, ChannelConfig->ChannelId, ChannelConfig->ChannelOffVal);
    Mcpwm_SetChannelMatchTriggerMode(McpwmId, ChannelConfig->ChannelId, ChannelConfig->ChannelMatchTrigMode);
    
    if(COMMON_ENABLE == ChannelConfig->FaultCtrlEnable)
    {
        Mcpwm_SetChannelSafeStatusValForFaultA(McpwmId, ChannelConfig->ChannelId, ChannelConfig->SafeStatusForFaultA);
    }
    Mcpwm_EnablePairCombine(McpwmId, (Mcpwm_PairIdType)PairId, COMMON_DISABLE);
    Mcpwm_EnablePairFaultCtrl(McpwmId, (Mcpwm_PairIdType)PairId, ChannelConfig->FaultCtrlEnable);
    Mcpwm_EnablePairSynchronization(McpwmId, (Mcpwm_PairIdType)PairId, ChannelConfig->CvUpdateEnable);
}

/**
 * @brief       MCPWM initialise independent PWM output Config Function
 *
 * @param[in]  McpwmId:    Selected the MCPWM ID: MCPWM0_ID.
 * @param[in]  CounterId:  Selected Counter ID.
 * @param[in]  Config:     Independent PWM Output Config.
 *
 * @return none
 *
 */
void Mcpwm_ConfigOutputIndependentPwm(Mcpwm_IdType McpwmId, Mcpwm_CounterIdType CounterId,  const Mcpwm_IndependentPwmConfigType * Config)
{   
    
    Mcpwm_ConfigIndependentPwmChannel(McpwmId, Config->MainPwmChConfig);
    Mcpwm_ConfigIndependentPwmChannel(McpwmId, Config->SecondPwmChConfig);
 
    Mcpwm_SetCountingMode(McpwmId, CounterId, Config->CountMode);
    Mcpwm_SetCounterModVal(McpwmId, CounterId, Config->CountModVal);
    
}

/**
 * @brief       MCPWM Complementary PWM channel Config Function
 *
 * @param[in]  McpwmId:         Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  ChannelConfig:   Complementary PWM Output Channel Config.
 *
 * @return none
 *
 */
void Mcpwm_ConfigComplementaryPwmChannel(Mcpwm_IdType McpwmId, const Mcpwm_CompPwmChannelConfigType * ChannelConfig)
{
    uint8 MainChannel = (uint8)ChannelConfig->PairId << 1U;
    uint8 SecondChannel = MainChannel + 1U;

    Mcpwm_SetPairPulseEdgeCtrlMode(McpwmId, ChannelConfig->PairId, ChannelConfig->Pec);
    Mcpwm_SelPairChannelValue(McpwmId,ChannelConfig->PairId,ChannelConfig->CvSel);
    Mcpwm_EnablePairAsymmetric(McpwmId, ChannelConfig->PairId, ChannelConfig->Asym);
    if(COMMON_ENABLE == ChannelConfig->MainChannelOutputEnable)
    {
        Mcpwm_EnableChannelOutput(McpwmId, (Mcpwm_ChannelIdType)MainChannel);
    }
    else
    {
        Mcpwm_DisableChannelOutput(McpwmId, (Mcpwm_ChannelIdType)MainChannel);
    }
    
    if(COMMON_ENABLE == ChannelConfig->SecondChannelOutputEnable)
    {
        Mcpwm_EnableChannelOutput(McpwmId, (Mcpwm_ChannelIdType)SecondChannel);
    }
    else
    {
        Mcpwm_DisableChannelOutput(McpwmId, (Mcpwm_ChannelIdType)SecondChannel);
    }    
    
    Mcpwm_SetChannelPulsePol(McpwmId, (Mcpwm_ChannelIdType)MainChannel, ChannelConfig->PulsePol);
    Mcpwm_SetChannelPolarity(McpwmId, (Mcpwm_ChannelIdType)MainChannel, ChannelConfig->Polarity);
    Mcpwm_SetChannelPolarity(McpwmId, (Mcpwm_ChannelIdType)SecondChannel, ChannelConfig->Polarity);
    Mcpwm_SetChannelCVal(McpwmId, (Mcpwm_ChannelIdType)MainChannel, ChannelConfig->MainCompareValue);
    Mcpwm_SetChannelCVal(McpwmId, (Mcpwm_ChannelIdType)SecondChannel, ChannelConfig->SecondCompareValue);
    Mcpwm_SetChannelOffValue(McpwmId, (Mcpwm_ChannelIdType)MainChannel, ChannelConfig->MainChannelOffVal);
    Mcpwm_SetChannelOffValue(McpwmId, (Mcpwm_ChannelIdType)SecondChannel, ChannelConfig->SecondChannelOffVal);
    Mcpwm_SetChannelMatchTriggerMode(McpwmId, (Mcpwm_ChannelIdType)MainChannel, ChannelConfig->MainChannelMatchTrigMode);
    Mcpwm_SetChannelMatchTriggerMode(McpwmId, (Mcpwm_ChannelIdType)SecondChannel, ChannelConfig->SecondChannelMatchTrigMode);
    
    if(COMMON_ENABLE == ChannelConfig->FaultCtrlEnable)
    {
        Mcpwm_SetChannelSafeStatusValForFaultA(McpwmId, (Mcpwm_ChannelIdType)MainChannel, ChannelConfig->MainSafeStatusForFaultA);
        Mcpwm_SetChannelSafeStatusValForFaultA(McpwmId, (Mcpwm_ChannelIdType)SecondChannel, ChannelConfig->SecondSafeStatusForFaultA);
    }

    Mcpwm_EnablePairCombine(McpwmId, ChannelConfig->PairId, COMMON_ENABLE);
    Mcpwm_SetDeadTimeVal(McpwmId, ChannelConfig->PairId, ChannelConfig->DeadTimeVal); 
    Mcpwm_EnablePairFaultCtrl(McpwmId, ChannelConfig->PairId, ChannelConfig->FaultCtrlEnable);
    Mcpwm_EnablePairDeadtime(McpwmId, ChannelConfig->PairId, ChannelConfig->DeadTimeEnable);
    Mcpwm_EnablePairSynchronization(McpwmId, ChannelConfig->PairId, ChannelConfig->CvUpdateEnable);
}
                                
/**
 * @brief       MCPWM initialise complementary PWM output Config Function
 *
 * @param[in]  McpwmId:    Selected the MCPWM ID: MCPWM0_ID .
 * @param[in]  CounterId:  Selected Counter ID.
 * @param[in]  Config:     Complementary PWM Output Config.
 *
 * @return none
 *
 */
void Mcpwm_ConfigOutputComplementaryPwm(Mcpwm_IdType McpwmId, Mcpwm_CounterIdType CounterId,
                                        const Mcpwm_CompPwmConfigType * Config)
{   
    Mcpwm_ConfigComplementaryPwmChannel(McpwmId, Config->CPwmChConfig);
    Mcpwm_SetCountingMode(McpwmId, CounterId, Config->CountMode);
    Mcpwm_SetCounterModVal(McpwmId, CounterId, Config->CountModVal);  
}

/**
 * @brief   MCPWM initialise fault control Config Function, which used in pwm Mode
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  Config:     Fault Control Config.
 *
 * @return none
 *
 */
void Mcpwm_ConfigFaultControl(Mcpwm_IdType McpwmId, const Mcpwm_PwmFaultCtrlConfigType * Config)
{
    
    Mcpwm_SetFaultFilterVal(McpwmId, Config->FaultFilterValue);
    Mcpwm_SetFaultOutputState(McpwmId, Config->Status);
    Mcpwm_SetFaultClearMode(McpwmId, Config->FaultClearMode);
    Mcpwm_EnableFaultFilter(McpwmId,  Config->FaultChannelConfig[0].FaultInputFilterEnable);
    Mcpwm_SetFaultInputPolarity(McpwmId, Config->FaultChannelConfig[0].FaultInputPolarity);
    Mcpwm_EnableFaultInput(McpwmId, Config->FaultChannelConfig[0].FaultInputChannelEnable);

}

/**
 * @brief       MCPWM enable/disable that Software Trigger activate CNT register sync
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  Cmd:        Enable/Disable.
 *
 * @return none
 *
 */
void Mcpwm_EnableSwTrigCntSync(Mcpwm_IdType McpwmId, Common_ControlStateType Cmd)
{
    Mcpwm_RegBfPtr[McpwmId]->MCPWM_SYNC.SWRSTCNT = (uint32)Cmd;   
}

/**
 * @brief       MCPWM enable/disable that Software Trigger activate write buffer register sync
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  Cmd:        Enable/Disable.
 *
 * @return none
 *
 */
void Mcpwm_EnableSwTrigWrBufSync(Mcpwm_IdType McpwmId, Common_ControlStateType Cmd)
{
    
 
    
    Mcpwm_RegBfPtr[McpwmId]->MCPWM_SYNC.SWWRBUF = (uint32)Cmd;  
}

/**
 * @brief       MCPWM generate  PWM synchronization software trigger Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 *
 * @return none
 *
 */
void Mcpwm_EnableSyncSoftwareTrigger(Mcpwm_IdType McpwmId)
{
    
 
    
    Mcpwm_RegBfPtr[McpwmId]->MCPWM_SYNC.SWTRIG = 1U;
    
}

/**
 * @brief       MCPWM Output Software Control Register update Mode select Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  UpdateMode: Update Mode. 0: update on all rising edge of the system clock
 *                                       1: update only by PWM synchronization
 *
 * @return none
 *
 */
void Mcpwm_SetOswcUpdateMode(Mcpwm_IdType McpwmId, Mcpwm_RegUpdateModeType UpdateMode)
{
    
 
    
    Mcpwm_RegBfPtr[McpwmId]->MCPWM_SYNC.SYNCOSWC = (uint32)UpdateMode;

}

/**
 * @brief       MCPWM CPWM half cycle reload enable/disable Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  CounterId:  Select counter id for CPWM.
 * @param[in]  Cmd:        Enable/Disable.
 *
 * @return none
 *
 */
void Mcpwm_EnableCpwmHalfCycleReload(Mcpwm_IdType McpwmId, Mcpwm_CounterIdType CounterId, Common_ControlStateType Cmd)
{
    
 
    
    switch (CounterId)
    {
        case MCPWM_COUNTER_0:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_RELOAD.CPWMHCR0 = (uint32)Cmd;
            break;
            
        case MCPWM_COUNTER_1:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_RELOAD.CPWMHCR1 = (uint32)Cmd;
            break;

        case MCPWM_COUNTER_2:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_RELOAD.CPWMHCR2 = (uint32)Cmd;
            break;

        case MCPWM_COUNTER_3:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_RELOAD.CPWMHCR3 = (uint32)Cmd;
            break;

        default:
            /* do nothing */
            break;            
    } 
    
}

/**
 * @brief       MCPWM CPWM full cycle reload enable/disable Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  CounterId:  Select counter id for CPWM.
 * @param[in]  Cmd:        Enable/Disable.
 *
 * @return none
 *
 */
void Mcpwm_EnableCpwmFullCycleReload(Mcpwm_IdType McpwmId, Mcpwm_CounterIdType CounterId, Common_ControlStateType Cmd)
{
    
 
    
    switch (CounterId)
    {
        case MCPWM_COUNTER_0:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_RELOAD.CPWMFCR0 = (uint32)Cmd;
            break;
            
        case MCPWM_COUNTER_1:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_RELOAD.CPWMFCR1 = (uint32)Cmd;
            break;

        case MCPWM_COUNTER_2:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_RELOAD.CPWMFCR2 = (uint32)Cmd;
            break;

        case MCPWM_COUNTER_3:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_RELOAD.CPWMFCR3 = (uint32)Cmd;
            break;

        default:
            /* do nothing */
            break;            
    } 
    
}

/**
 * @brief       MCPWM Set reload frequency Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  CounterId:  Select counter id for CPWM.
 * @param[in]  Freq:       reload frequency, max is 0x1F.
 *
 * @return none
 *
 */
void Mcpwm_SetReloadFreq(Mcpwm_IdType McpwmId, Mcpwm_CounterIdType CounterId, uint8 Freq)
{
    
 
    
    switch (CounterId)
    {
        case MCPWM_COUNTER_0:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_LDFREQ.LDFREQ0 = (uint32)Freq;
            break;
            
        case MCPWM_COUNTER_1:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_LDFREQ.LDFREQ1 = (uint32)Freq;
            break;

        case MCPWM_COUNTER_2:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_LDFREQ.LDFREQ2 = (uint32)Freq;
            break;

        case MCPWM_COUNTER_3:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_LDFREQ.LDFREQ3 = (uint32)Freq;
            break;

        default:
            /* do nothing */
            break;            
    } 
    
}

/**
 * @brief       MCPWM Config Reload Param for selected pair of channels Function
 *
 * @param[in]  McpwmId:      Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  CounterId:    Select counter id .
 * @param[in]  ReloadConfig: Pointer to reload param Config struct.
 *
 * @return none
 *
 */
void Mcpwm_ConfigReloadParam(Mcpwm_IdType McpwmId, Mcpwm_CounterIdType CounterId, 
                             const Mcpwm_ReloadConfigType* ReloadConfig)
{
    Mcpwm_EnableCpwmHalfCycleReload(McpwmId, CounterId, ReloadConfig->HalfCycleEnable);
    Mcpwm_EnableCpwmFullCycleReload(McpwmId, CounterId, ReloadConfig->FullCycleEnable);
    Mcpwm_SetReloadFreq(McpwmId, CounterId, ReloadConfig->LoadFrequency);
}

/**
 * @brief       MCPWM Reload enable Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  PairId:     Select pair id for CPWM.
 * @param[in]  Cmd:        Enable/Disable.
 *
 * @return none
 *
 */
void Mcpwm_EnableReload(Mcpwm_IdType McpwmId, Mcpwm_PairIdType PairId, Common_ControlStateType Cmd)
{
    
 
    
    switch (PairId)
    {
        case MCPWM_PAIR_CHANNEL_0:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_RELOAD.LOADEN0 = (uint32)Cmd;
            break;
            
        case MCPWM_PAIR_CHANNEL_1:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_RELOAD.LOADEN1 = (uint32)Cmd;
            break;

        case MCPWM_PAIR_CHANNEL_2:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_RELOAD.LOADEN2 = (uint32)Cmd;
            break;

        case MCPWM_PAIR_CHANNEL_3:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_RELOAD.LOADEN3 = (uint32)Cmd;
            break;

        default:
            /* do nothing */
            break;            
    }
    
}

/**
 * @brief       MCPWM Load Mode Select Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  Mode:       Select Load Mode:Mcpwm_LOAD_MANUAL,Mcpwm_LOAD_AUTO
 *
 * @return none
 *
 */
void Mcpwm_SetLoadMode(Mcpwm_IdType McpwmId, Mcpwm_LoadModeType Mode)
{
    
 
    Mcpwm_RegBfPtr[McpwmId]->MCPWM_RELOAD.LOADMODE = (uint32)Mode;
    
   
}

/**
 * @brief       MCPWM INT mask/unmask Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  IntType:    Select interrupt type.
 * @param[in]  IntMask:    Mask/unmask .
 *
 * @return none
 *
 */
void Mcpwm_SetIntMask(Mcpwm_IdType McpwmId, Mcpwm_IntType IntType, Common_IntMaskType IntMask)
{
 

    uint32 IntStatus;
    IntStatus =Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBCR;
    Common_ControlStateType Cmd = COMMON_DISABLE;
    if (IntMask == COMMON_UNMASK)
    {
        Cmd = COMMON_ENABLE;
         switch (IntType)
        {
            case MCPWM_INT_CH0:
            case MCPWM_INT_CH1:
            case MCPWM_INT_CH2:
            case MCPWM_INT_CH3:
            case MCPWM_INT_CH4:
            case MCPWM_INT_CH5: 
            case MCPWM_INT_CH6:
            case MCPWM_INT_CH7: 
            case MCPWM_INT_RLD0:
            case MCPWM_INT_RLD1:
            case MCPWM_INT_RLD2:
            case MCPWM_INT_RLD3:
            case MCPWM_INT_TO0:
            case MCPWM_INT_TO1: 
            case MCPWM_INT_TO2: 
            case MCPWM_INT_TO3:
            case MCPWM_INT_ALL:
                Mcpwm_IntMaskStatus = Mcpwm_IntMaskStatus | Mcpwm_IntMaskTable[IntType];
                break;

            default:
                /* do nothing */
                break;
        }
    }
    switch (IntType)
    {
        case MCPWM_INT_CH0:
        case MCPWM_INT_CH1: 
        case MCPWM_INT_CH2: 
        case MCPWM_INT_CH3:
        case MCPWM_INT_CH4: 
        case MCPWM_INT_CH5: 
        case MCPWM_INT_CH6:
        case MCPWM_INT_CH7: 
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_CFG[IntType].CHIE = (uint32)Cmd;
            break;
            
        case MCPWM_INT_RLD0:
        case MCPWM_INT_RLD1:
        case MCPWM_INT_RLD2:
        case MCPWM_INT_RLD3:
        case MCPWM_INT_TO0:
        case MCPWM_INT_TO1:
        case MCPWM_INT_TO2:
        case MCPWM_INT_TO3:
        if(Cmd==COMMON_DISABLE)
        {
            Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBCR &= ~(Mcpwm_IntMaskTable[IntType]<<8);  
        }
        else {
            Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBCR = IntStatus|(Mcpwm_IntMaskTable[IntType]<<8);             
        }
            break;            
        case MCPWM_INT_FAULT:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_FLTCR.FLTIE = (uint32)Cmd;
            break;
            
        case MCPWM_INT_ALL:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_CFG[0].CHIE = (uint32)Cmd;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_CFG[1].CHIE = (uint32)Cmd; 
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_CFG[2].CHIE = (uint32)Cmd;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_CFG[3].CHIE = (uint32)Cmd;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_CFG[4].CHIE = (uint32)Cmd;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_CFG[5].CHIE = (uint32)Cmd; 
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_CFG[6].CHIE = (uint32)Cmd;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_CFG[7].CHIE = (uint32)Cmd;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBCR.RLDIE0= (uint32)Cmd;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBCR.RLDIE1= (uint32)Cmd;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBCR.RLDIE2= (uint32)Cmd;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBCR.RLDIE3= (uint32)Cmd;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBCR.TOIE0 = (uint32)Cmd;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBCR.TOIE1 = (uint32)Cmd;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBCR.TOIE2 = (uint32)Cmd;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBCR.TOIE3 = (uint32)Cmd;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_FLTCR.FLTIE = (uint32)Cmd;
            break;

        default:
            /* do nothing */
            break;
    }

   if (IntMask == COMMON_MASK)
    {
        switch (IntType)
        {
            case MCPWM_INT_CH0:
            case MCPWM_INT_CH1: 
            case MCPWM_INT_CH2: 
            case MCPWM_INT_CH3:
            case MCPWM_INT_CH4: 
            case MCPWM_INT_CH5: 
            case MCPWM_INT_CH6:
            case MCPWM_INT_CH7: 
            case MCPWM_INT_RLD0:
            case MCPWM_INT_RLD1:
            case MCPWM_INT_RLD2:
            case MCPWM_INT_RLD3:
            case MCPWM_INT_TO0:
            case MCPWM_INT_TO1: 
            case MCPWM_INT_TO2: 
            case MCPWM_INT_TO3:
            case MCPWM_INT_ALL:
                Mcpwm_IntMaskStatus= Mcpwm_IntMaskStatus& (~Mcpwm_IntMaskTable[IntType]);
                break;

            default:
                /* do nothing */
                break;
        }
    }
}    


/**
 * @brief       MCPWM INT Status clear Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  IntType:    Select interrupt type.
 *
 * @return none
 *
 */
void Mcpwm_ClearInt(Mcpwm_IdType McpwmId, Mcpwm_IntType IntType)
{
    
 

    uint32 McpwmIntStatus = 0U;
   switch (IntType)
    {
        case MCPWM_INT_CH0:
        case MCPWM_INT_CH1:
        case MCPWM_INT_CH2:
        case MCPWM_INT_CH3:
        case MCPWM_INT_CH4:
        case MCPWM_INT_CH5:
        case MCPWM_INT_CH6:
        case MCPWM_INT_CH7:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_CFG[IntType].CHF = 0U;
            break;
        case MCPWM_INT_RLD0:
        case MCPWM_INT_RLD1:
        case MCPWM_INT_RLD2:
        case MCPWM_INT_RLD3:
        case MCPWM_INT_TO0:
        case MCPWM_INT_TO1:
        case MCPWM_INT_TO2:
        case MCPWM_INT_TO3:
	    McpwmIntStatus=Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBSR;
            McpwmIntStatus=McpwmIntStatus&(~(Mcpwm_IntMaskTable[IntType]));
	    Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBSR=McpwmIntStatus;
            break;
        case MCPWM_INT_FAULT:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_FLTSR.FAULTFA = 0U;
            break;
       case MCPWM_INT_ALL:
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_CFG[0].CHF = 0U;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_CFG[1].CHF = 0U;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_CFG[2].CHF = 0U;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_CFG[3].CHF = 0U;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_CFG[4].CHF = 0U;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_CFG[5].CHF = 0U;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_CFG[6].CHF = 0U;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_CFG[7].CHF = 0U;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBSR.RLDF0 = 0U;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBSR.RLDF1 = 0U;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBSR.RLDF2 = 0U;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBSR.RLDF3 = 0U;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBSR.TOF0 = 0U;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBSR.TOF1 = 0U;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBSR.TOF2 = 0U;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_GLBSR.TOF3 = 0U;
            Mcpwm_RegBfPtr[McpwmId]->MCPWM_FLTSR.FAULTFA = 0U;
            break;
            
        default:
            /* do nothing */
            break;
    }
  
}

/**
 * @brief       MCPWM Get INT Status Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID .
 * @param[in]  IntType:    Select interrupt type.
 *
 * @return    IntStatus: interrupt status.
 * @retval    COMMON_RESET : Reset state.
 * @retval    COMMON_SET   : Set state.
 * @note     :MCPWM_INT_ALL is invalid as input
 */
Common_IntStatusType Mcpwm_GetIntStatus(Mcpwm_IdType McpwmId, Mcpwm_IntType IntType)
{

 

    Common_IntStatusType IntStatus = COMMON_RESET;
    
    switch (IntType)
    {
        case MCPWM_INT_CH0:
        case MCPWM_INT_CH1:
        case MCPWM_INT_CH2:
        case MCPWM_INT_CH3:
        case MCPWM_INT_CH4:
        case MCPWM_INT_CH5:
        case MCPWM_INT_CH6:
        case MCPWM_INT_CH7:
            IntStatus = (Common_IntStatusType)Mcpwm_RegBfPtr[McpwmId]->MCPWM_CFG[IntType].CHF;
            break;
        case MCPWM_INT_RLD0:
        case MCPWM_INT_RLD1:
        case MCPWM_INT_RLD2:
        case MCPWM_INT_RLD3:
        case MCPWM_INT_TO0:
        case MCPWM_INT_TO1:
        case MCPWM_INT_TO2:
        case MCPWM_INT_TO3:
            IntStatus = (((Mcpwm_RegWPtr[McpwmId]->MCPWM_GLBSR&(Mcpwm_IntMaskTable[IntType]))!=0U) ? COMMON_SET : COMMON_RESET);
            break;
            
        case MCPWM_INT_FAULT:
            if(Mcpwm_RegBfPtr[McpwmId]->MCPWM_FLTSR.FAULTFA != 0UL)
            {
                IntStatus = COMMON_SET;
            }   
            break;         
            
        default:
            /* do nothing */
            break;
      
    }  
    
    return IntStatus;
}
       


/**
 * @brief       MCPWM Get Fault detection flag Status of fault channel  Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  ChannelId:  Select fault input channel:MCPWM_FAULT_CHANNEL_0,.. .
 *
 * @return    IntStatus: interrupt status.
 * @retval    COMMON_RESET : Reset state.
 * @retval    COMMON_SET   : Set state.
 *
 */
Common_IntStatusType Mcpwm_GetFaultStatus(Mcpwm_IdType McpwmId)
{
 
    Common_IntStatusType IntStatus = COMMON_RESET;
    IntStatus = (Common_IntStatusType)Mcpwm_RegBfPtr[McpwmId]->MCPWM_FLTSR.FAULTF0; 
    return IntStatus;
}

/**
 * @brief       MCPWM fault Status clear Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  InputId:    Select the Fault input ID.
 *
 * @return none
 *
 */
void Mcpwm_ClearFaultStatus(Mcpwm_IdType McpwmId)
{    
    Mcpwm_RegBfPtr[McpwmId]->MCPWM_FLTSR.FAULTF0 = 0U;
}

/**
 * @brief       MCPWM any channel match trigger flag clear Function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 *
 * @return none
 *
 */
void Mcpwm_ClearMatchTriggerFlag(Mcpwm_IdType McpwmId)
{ 
    Mcpwm_RegBfPtr[McpwmId]->MCPWM_OUTTRIG.TRIGF = 0U;
}

/**
 * @brief       MCPWM install interrupt callback function
 *
 * @param[in]  McpwmId:    Select the MCPWM ID: MCPWM0_ID.
 * @param[in]  IntType:    Select interrupt type.
 * @param[in]  CbFun:      Callback function .
 *
 * @return none
 * @note     :MCPWM_INT_ALL is invalid as input
 */
void Mcpwm_InstallCallBackFunc(Mcpwm_IdType McpwmId, Mcpwm_IntType IntType, Isr_CbFuncType * CbFun)
{
    if (IntType <MCPWM_INT_ALL)
    {
        McpwmIsrCbFunc[McpwmId][IntType] = CbFun;  
    }
    else 
    {
        /* do nothing */
    }

}

/*@} end of group Mcpwm_Public_Functions */
