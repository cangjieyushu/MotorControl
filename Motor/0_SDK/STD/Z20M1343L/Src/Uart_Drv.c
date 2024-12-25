/**************************************************************************************************/
/**
 * @file      : Uart_drv.c
 * @brief     : Uart module driver file.
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#include "Uart_Drv.h"
#include "Clk_Drv.h"
 
/** @defgroup Private_MacroDefinition
 *  @{
 */

/** @} end of Private_MacroDefinition */

/** @defgroup Private_TypeDefinition
 *  @{
 */

/** @} end of group Private_TypeDefinition */


/** @defgroup Private_TypeDefinition
 *  @{
 */

/**
 *  @brief UART interrupt IID definition
 */
#define UART_INTSTA_IID_MODEM                     (0x00U)
#define UART_INTSTA_IID_TBEI                      (0x02U)
#define UART_INTSTA_IID_RBFI                      (0x04U)
#define UART_INTSTA_IID_LSI                       (0x06U)
#define UART_INTSTA_IID_BYDET                     (0x07U)
#define UART_INTSTA_IID_LIN_HEADER_OP_SUCC        (0x08U)
#define UART_INTSTA_IID_LIN_WUP_OP_SUCC           (0x09U)
#define UART_INTSTA_IID_LIN_RSP_OP_SUCC           (0x0AU)
#define UART_INTSTA_IID_LIN_ERR                   (0x0BU)
#define UART_INTSTA_IID_RCVRTO                    (0x0CU)
#define UART_INTSTA_IID_ASYNC                     (0x0DU)

#define UART_LIN_SEND_BREAK_MIN                   (13U)
#define UART_LIN_SEND_BREAK_THR                   (11U)


#define UART_LIN_ERR_SYNC_FIELD                   (1U)
#define UART_LIN_ERR_PID                          (1U << 1U)
#define UART_LIN_ERR_CHECKSUM                     (1U << 2U)
#define UART_LIN_ERR_TO                           (1U << 3U)
#define UART_LIN_ERR_BIT                          (1U << 4U)
#define UART_LIN_ERR_WUP_TO                       (1U << 5U)

     
#define UART_LSI_OE                               (1U << 1U)
#define UART_LSI_PE                               (1U << 2U)
#define UART_LSI_FE                               (1U << 3U)
#define UART_LSI_BI                               (1U << 4U)
#define UART_LSI_RFE                              (1U << 7U)

#define UART_LIN_ERR_FLAG                         (UART_LIN_ERR_SYNC_FIELD | \
                                                   UART_LIN_ERR_PID | \
                                                   UART_LIN_ERR_CHECKSUM | \
                                                   UART_LIN_ERR_TO | \
                                                   UART_LIN_ERR_BIT | \
                                                   UART_LIN_ERR_WUP_TO)

#define UART_LSI_INT_FLAG                         (UART_LSI_OE | \
                                                   UART_LSI_PE | \
                                                   UART_LSI_FE | \
                                                   UART_LSI_BI | \
                                                   UART_LSI_RFE)
#define UART_INT_ASYNC_CLEAR                      ((uint32)1U << 9U)

#define UART_ENABLE_FIFO                          (1U)
#define UART_RESET_RX_FIFO                        (1U << 1U)
#define UART_RESET_TX_FIFO                        (1U << 2U)


/* six bits id for frame header */
#define UART_LIN_ID_MASK                           (0x3F)

/* LIN operation mode */
#define UART_LIN_OPERATION_HEADER                  (0U)
#define UART_LIN_OPERATION_RESPONSE                (1U)
#define UART_LIN_OPERATION_WAKEUP                  (2U)

/* the direction of wakeup signal */
#define UART_LIN_DETECT_WAKEUP_SIGNAL              (0U)
#define UART_LIN_TRANSMITTING_WAKEUP_SIGNAL        (1U)

#define UART_LIN_ERROR_ALL_MASK                    (0x3FU)

#define UART_CHECK_PTIME                           (0x82U)

static const uint32 Uart_InterruptMaskTable[]=
{
    0x00000001U,       /*!< UART_INT_RBFI */
    0x00000002U,       /*!< UART_INT_TBEI */
    0x00000004U,       /*!< UART_INT_LSI */
    0x00000008U,       /*!< UART_INT_MODEM */
    0x00000082U,       /*!< UART_INT_PTIME*/
    0x00001000U,       /*!< UART_INT_ASYNC */
    0x00002000U,       /*!< UART_INT_BYDET */
    0x00000010U,       /*!< UART_INT_RCVRTO */    
    0x00000001U,       /*!< UART_INT_LIN_ERR */
    0x00000002U,       /*!< UART_INT_LIN_WUP_OP_SUCC */
    0x00000004U,       /*!< UART_INT_LIN_HEADER_OP_SUCC */
    0x00000008U,       /*!< UART_INT_LIN_RSP_OP_SUCC */
    0x0000000FU,       /*!< UART_INT_LIN_ALL */
    0x0000309FU,       /*!< UART_INT_ALL: include UART and LIN */
};

static const uint32 Uart_LinInterruptStatusTable[]=
{
    0x00000001U,       /*!< UART_INT_LIN_ERR */
    0x00000002U,       /*!< UART_INT_LIN_WUP_OP_SUCC */
    0x00000004U,       /*!< UART_INT_LIN_HEADER_OP_SUCC */
    0x00000008U,       /*!< UART_INT_LIN_RSP_OP_SUCC */
};

static const uint32 Uart_LineStatusTable[]=
{
    0x00000001U,           /*!< UART_LINESTA_DR */
    0x00000002U,           /*!< UART_LINESTA_OE */
    0x00000004U,           /*!< UART_LINESTA_PE */
    0x00000008U,           /*!< UART_LINESTA_FE */
    0x00000010U,           /*!< UART_LINESTA_BI */
    0x00000020U,           /*!< UART_LINESTA_THRE */
    0x00000040U,           /*!< UART_LINESTA_TEMT */
    0x00000080U,           /*!< UART_LINESTA_RFE */
    0x0000009EU,           /*!< UART_LINESTA_TRANS_ERR */
    0x00000100U,           /*!< UART_LINESTA_ADDR_RCVD */
    0x00000200U,           /*!< UART_LINESTA_ASYNC */
    0x0000039FU,           /*!< ALL LINE STATUS */
};

/** @}end of group Private_TypeDefinition */

/** @defgroup Global_VariableDefinition
 *  @{
 */
 
 /* UART serial frequency */
 static uint32 Uart_SerialFreq = 0U;

 /** @} end of group Global_VariableDefinition */

/** @defgroup Private_VariableDefinition
 *  @{
 */

/**
 *  @brief UART ISR callback function pointer array
 */
static Isr_CbFuncType * Uart_IsrCbPtr[UART_INT_NUM]=
{
    NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,
    NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR,NULL_PTR
};

/**
 *  @brief UART base address array
 */
/*PRQA S 0303 ++*/
static Reg_Uart_BfType * const Uart_RegBfPtr = (Reg_Uart_BfType *)UART_BASE_ADDR;

static Reg_Uart_WType * const Uart_RegWPtr = (Reg_Uart_WType *)UART_BASE_ADDR;
/*PRQA S 0303 --*/

/** @}end of group Private_VariableDefinition */


/** @defgroup Private_FunctionDeclaration
 *  @{
 */
static void Uart_IntHandler(void);
void Uart_DriverIrqHandler(void);


/** @}end of group Private_FunctionDeclaration */

/** @defgroup Private_FunctionDefinition
 *  @{
 */

/** @} end of group Private_FunctionDefinition */

/** @defgroup Private_FunctionDefinition
 *  @{
 */

static void Uart_ModemHandle(void)
{
    volatile uint32 DummyData;

    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)Uart_RegBfPtr;
    Reg_Uart_WType * UartRegWPtr = (Reg_Uart_WType *)Uart_RegWPtr;

    DummyData = UartRegWPtr->UART_MSR;
    if (NULL_PTR != Uart_IsrCbPtr[UART_INT_MODEM])
    {
        /* call the callback function */
        Uart_IsrCbPtr[UART_INT_MODEM]();
    }
    /* Disable the interrupt if callback function is not setup */
    else
    {
        UartRegBfPtr->UART_IER.EDSSI = 0U;
    }
}

static void Uart_ThrEmptyHandle(void)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)Uart_RegBfPtr;
    Reg_Uart_WType * UartRegWPtr = (Reg_Uart_WType *)Uart_RegWPtr;

    if(0x82U == (UartRegWPtr->UART_IER & (uint32)UART_CHECK_PTIME))
        {
            if(Uart_IsrCbPtr[UART_INT_PTIME] != NULL_PTR)
            {
                    /* call the callback function */
                Uart_IsrCbPtr[UART_INT_PTIME]();
            }
            /* Disable the interrupt if callback function is not setup */
            else
            {
                    UartRegWPtr->UART_IER &= ~((uint32)UART_CHECK_PTIME);
            }              
        }
        /* TEBI interrupt is enable */
        else
        {
            if(Uart_IsrCbPtr[UART_INT_TBEI] != NULL_PTR)
            {
                /* call the callback function */
                Uart_IsrCbPtr[UART_INT_TBEI]();
            }
            /* Disable the interrupt if callback function is not setup */
            else
            {
                UartRegBfPtr->UART_IER.ETBEI = 0U;
            }              
        }
}

static void Uart_RbfiHandle(void)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)Uart_RegBfPtr;

    if (NULL_PTR != Uart_IsrCbPtr[UART_INT_RBFI])
    {
        /* call the callback function */
        Uart_IsrCbPtr[UART_INT_RBFI]();
    }
    /* Disable the interrupt if callback function is not setup */
    else
    {
        UartRegBfPtr->UART_IER.ERBFI = 0U;
    } 
}

static void Uart_LsiHandle(void)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)Uart_RegBfPtr;
    Reg_Uart_WType * UartRegWPtr = (Reg_Uart_WType *)Uart_RegWPtr;

    if (NULL_PTR != Uart_IsrCbPtr[UART_INT_LSI])
    {
        /* call the callback function */
        Uart_IsrCbPtr[UART_INT_LSI]();
    }
    /* Disable the interrupt if callback function is not setup */
    else
    {
        UartRegBfPtr->UART_IER.ELSI = 0U;
    }
    UartRegWPtr->UART_LSR = UART_LSI_INT_FLAG;
}

static void Uart_BydetHandle(void)
{
    volatile uint32 DummyData;

    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)Uart_RegBfPtr;
    Reg_Uart_WType * UartRegWPtr = (Reg_Uart_WType *)Uart_RegWPtr;

    /* Clear it by reading the UART status register */
    DummyData = UartRegWPtr->UART_USR;
    if (NULL_PTR != Uart_IsrCbPtr[UART_INT_BYDET])
    {
        /* call the callback function */
        Uart_IsrCbPtr[UART_INT_BYDET]();
    }
    /* Disable the interrupt if callback function is not setup */
    else
    {
        UartRegBfPtr->UART_IER.BYDET_INT_EN = 0U;
    }
    /* Clear it by reading the UART receive register */
    DummyData = UartRegWPtr->UART_RBR;
}

static void Uart_LinHeaderDoneHandle(void)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)Uart_RegBfPtr;
    Reg_Uart_WType * UartRegWPtr = (Reg_Uart_WType *)Uart_RegWPtr;

    UartRegWPtr->UART_LIN_LISR = Uart_LinInterruptStatusTable[UART_LIN_INTSTA_HEADER_OP_SUCC];
    if (NULL_PTR != Uart_IsrCbPtr[UART_INT_LIN_HEADER_OP_SUCC])
    {
        /* call the callback function */
        Uart_IsrCbPtr[UART_INT_LIN_HEADER_OP_SUCC]();
    }
    /* Disable the interrupt if callback function is not setup */
    else
    {
        UartRegBfPtr->UART_LIN_INT_EN.HEADER_OP_SUCC_EN = 0U;
    }     
}

static void Uart_LinWakeUpDoneHandle(void)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)Uart_RegBfPtr;
    Reg_Uart_WType * UartRegWPtr = (Reg_Uart_WType *)Uart_RegWPtr;

    UartRegWPtr->UART_LIN_LISR = Uart_LinInterruptStatusTable[UART_LIN_INTSTA_WUP_OP_SUCC];
    if (NULL_PTR != Uart_IsrCbPtr[UART_INT_LIN_WUP_OP_SUCC])
    {
        /* call the callback function */
        Uart_IsrCbPtr[UART_INT_LIN_WUP_OP_SUCC]();
    }
    /* Disable the interrupt if callback function is not setup */
    else
    {
        UartRegBfPtr->UART_LIN_INT_EN.WAKEUP_OP_SUCC_EN = 0U;
    } 
}

static void Uart_LinResponseDoneHandle(void)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)Uart_RegBfPtr;
    Reg_Uart_WType * UartRegWPtr = (Reg_Uart_WType *)Uart_RegWPtr;

    UartRegWPtr->UART_LIN_LISR = Uart_LinInterruptStatusTable[UART_LIN_INTSTA_RSP_OP_SUCC];
    if (NULL_PTR != Uart_IsrCbPtr[UART_INT_LIN_RSP_OP_SUCC])
    {
        /* call the callback function */
        Uart_IsrCbPtr[UART_INT_LIN_RSP_OP_SUCC]();
    }
    /* Disable the interrupt if callback function is not setup */
    else
    {
        UartRegBfPtr->UART_LIN_INT_EN.RSP_OP_SUCC_EN = 0U;
    }
}

static void Uart_LinErrorHandle(void)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)Uart_RegBfPtr;

    /* User need to clear error flag in callback function, otherwise, operation start will not trigger*/        
    if (NULL_PTR != Uart_IsrCbPtr[UART_INT_LIN_ERR])
    {
        /* call the callback function */
        Uart_IsrCbPtr[UART_INT_LIN_ERR]();
    }
    /* Disable the interrupt if callback function is not setup */
    else
    {
        UartRegBfPtr->UART_LIN_INT_EN.LIN_ERR_EN = 0U;
    }
}

static void Uart_RcvrtoHandle(void)
{
    volatile uint32 DummyData; 
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)Uart_RegBfPtr;
    Reg_Uart_WType * UartRegWPtr = (Reg_Uart_WType *)Uart_RegWPtr;

    if (NULL_PTR != Uart_IsrCbPtr[UART_INT_RCVRTO])
    {
        /* call the callback function */
        Uart_IsrCbPtr[UART_INT_RCVRTO]();
    }
    /* Disable the interrupt if callback function is not setup */
    else
    {
        UartRegBfPtr->UART_IER.TOI = 0U;
    } 
    /* Clear it by reading the UART receive register */
    DummyData = UartRegWPtr->UART_RBR; 
}

static void Uart_AsyncHandle(void)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)Uart_RegBfPtr;
    Reg_Uart_WType * UartRegWPtr = (Reg_Uart_WType *)Uart_RegWPtr;

    UartRegWPtr->UART_LSR = (uint32)UART_INT_ASYNC_CLEAR;
    if (NULL_PTR != Uart_IsrCbPtr[UART_INT_ASYNC])
    {
        /* call the callback function */
        Uart_IsrCbPtr[UART_INT_ASYNC]();
    }
    /* Disable the interrupt if callback function is not setup */
    else
    {
        UartRegBfPtr->UART_IER.ASYNC_INT_EN = 0U;
    } 
}


static void Uart_DefaultHandle(void)
{

}


/**
 * @brief      Handle UART interrupt.
 * @param[in]  none
 * @return     none
 */
static void Uart_IntHandler(void)
{
    uint32 IntId;

    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);

    HandlerFuncPtr* Uart_HandlerFuncPtr[] = 
    {
        Uart_ModemHandle,                     /*!< Modem status */    
        Uart_DefaultHandle,                   /*!< Default */
        Uart_ThrEmptyHandle,                  /*!< THR empty */
        Uart_DefaultHandle,                   /*!< Default */
        Uart_RbfiHandle,                      /*!< Received data available */
        Uart_DefaultHandle,                   /*!< Default */
        Uart_LsiHandle,                       /*!< Receiver line status */
        Uart_BydetHandle,                     /*!< Busy detect */
        Uart_LinHeaderDoneHandle,             /*!< LIN:header operation success */
        Uart_LinWakeUpDoneHandle,             /*!< LIN:wakeup operation success */
        Uart_LinResponseDoneHandle,           /*!< LIN:response operation success */
        Uart_LinErrorHandle,                  /*!< LIN:error */
        Uart_RcvrtoHandle,                    /*!< Charactor time out */
        Uart_AsyncHandle,                     /*!< Async interrupt */
        Uart_DefaultHandle,                   /*!< Default */
        Uart_DefaultHandle,                   /*!< Default */
    };
    /* Get the IID */
    IntId = UartRegBfPtr->UART_IIR.IID;     
    
    Uart_HandlerFuncPtr[IntId]();
}

/** @} end of group Private_FunctionDefinition */

/** @defgroup Public_FunctionDefinition
 *  @{
 */
/**
 * @brief      install call back function for interrupts 
 * @param[in]  IntType: select the interrupt
 *                      - UART_INT_RBFI
 *                      - UART_INT_TBEI
 *                      - ......
 *                      - UART_INT_LIN_RSP_OP_SUCC
 *                      - UART_INT_LIN_ALL
 *                      - UART_INT_ALL
 * @param[in]  CbFunPtr: pointer to callback function
 * @return     none
 */
void Uart_InstallCallBackFunc(Uart_IntType IntType,Isr_CbFuncType * CbFunPtr)

{
    Uart_IsrCbPtr[IntType] = CbFunPtr;
}


/**
 * @brief      Initializes the UART
 * @param[in]  UartConfigPtr:Pointer to a UART configuration structure
 * @return     none
 */
void Uart_Init(const Uart_ConfigType* UartConfigPtr)
{

    uint32 IntegerDiv, FractionalDiv;
    Clk_ClockNodeType UartClkId = CLK_NODE_UART;
    uint32 ClkFreq = Clk_GetClkFreq(UartClkId, UartConfigPtr->OscFreq);
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);

  /************Configure the Baud Rate*********************************/

    /* Enable DLAB to set baud rate */
    UartRegBfPtr->UART_LCR.DLAB = 0x01U;

    /* get integer baudrate divisor*/
    IntegerDiv = ClkFreq/(16U * UartConfigPtr->BaudRate);

    /* Config the DLL and DLH registers */
    UartRegBfPtr->UART_DLR.DLR = IntegerDiv & 0xFFFFU;

    /* calculate fractional divisor
       divisor = clkFreq/(16*baudrate) = BRDI +BRDF
       FD = BRDF*2^4 = 16* BRDF
       BRDF = clkFreq%(16*baudrate)/(16*baudrate)
       FD = clkFreq%(16*baudrate)*16/(16*baudrate)
          = clkFreq%(16*baudrate)/baudrate  */
    FractionalDiv = ClkFreq%(16U * UartConfigPtr->BaudRate);
    FractionalDiv /= UartConfigPtr->BaudRate;
    UartRegBfPtr->UART_FD.FD = FractionalDiv;

    /* Disable DLAB */
    UartRegBfPtr->UART_LCR.DLAB = 0x0U;

    if (UART_PARITY_NONE == UartConfigPtr->Parity)
    {
        UartRegBfPtr->UART_LCR.PEN = 0x0U;
    }
    else if (UART_PARITY_ODD == UartConfigPtr->Parity)
    {
        UartRegBfPtr->UART_LCR.PEN = 0x1U;
        UartRegBfPtr->UART_LCR.EPS = 0U;
    }
    else
    {
        UartRegBfPtr->UART_LCR.PEN = 0x1U;
        UartRegBfPtr->UART_LCR.EPS = 1U;
    }

    /* Set UART Data Length and stop bit */
    if (UART_DATABITS_9 == UartConfigPtr->DataBits)
    {
       UartRegBfPtr->UART_LCR_EXT.DLS_E = 0x1U;
    }
    else
    {
        UartRegBfPtr->UART_LCR.DLS = (uint32)UartConfigPtr->DataBits;
    }
    /* Set UART stop bit */
    UartRegBfPtr->UART_LCR.STOP = (uint32)UartConfigPtr->StopBits;
    /***********Configure auto flow  *******************/
    UartRegBfPtr->UART_AFCR.AFCE = (uint32)UartConfigPtr->AutoFlowControl;

    if (COMMON_ENABLE == UartConfigPtr->AutoFlowControl)
    {
        UartRegBfPtr->UART_AFCR.RTS = 1U;
    }
    else
    {
        UartRegBfPtr->UART_AFCR.RTS = 0U;
    }
}

/**
 * @brief      UART/LIN enable/disable function
 * @param[in]  Cmd: Enable/Disable function state
                    - COMMON_DISABLE
                    - COMMON_ENABLE
 * @return none
 */
void Uart_Enable( Common_ControlStateType Cmd)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)Uart_RegBfPtr;

    UartRegBfPtr->UART_LCR.UART_LIN_EN = (uint32)Cmd;
}

/**
 * @brief      Wait for UART busy bit clear
 * @param[in]  Cycle: wait time need user calculation
 * @return     Ret: 
 * @retval     COMMON_SUCC:busy bit is cleared
 * @retval     COMMON_ERR: UART is still busy
 */
Common_ResultStatusType Uart_WaitBusyClear(uint32 Cycle)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    Common_ResultStatusType Ret = COMMON_ERR;
    volatile uint32 Localcnt = 0U;
    while (Localcnt < Cycle)
    {
        if ((uint32)COMMON_RESET == UartRegBfPtr->UART_USR.BUSY)
        {
            Ret = COMMON_SUCC;
            break;
        }
        Localcnt++;
    }
    return Ret;
}

/**
 * @brief      Set UART rts enable 
 * @param[in]  NewState: Enable/Disable function state
 * @return     none
 */
void Uart_EnableRts(Common_ControlStateType NewState)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    UartRegBfPtr->UART_AFCR.RTS = (uint32)NewState;
}

/**
 * @brief      Set UART loopback mode
 * @param[in]  NewState: Enable/disable function state
 * @return     none
 */
void Uart_SetLoopBackMode(Common_ControlStateType NewState)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);

    UartRegBfPtr->UART_AFCR.LB = (uint32)NewState;

}

/**
 * @brief      Send break function, user can choose the length of break
 * @param[in]  Len:     the length of break
 * @return     Ret:
 * @retval     COMMON_SUCC: break is sent
 * @retval     COMMON_ERR : break length is invalid
 */
Common_ResultStatusType Uart_SendBreak(uint8 Len)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    Common_ResultStatusType Ret = COMMON_ERR;
    if (Len < 0x0BU)
    {
        /*NOTHING*/
    }
    else
    {
        UartRegBfPtr->UART_LIN_HEADER_CFG.LBKM = (uint32)Len;
        UartRegBfPtr->UART_LCR.LBKEN = 0x1U;
        /* send break characters */
        UartRegBfPtr->UART_LCR.BC = 0x1U;
        Ret = COMMON_SUCC;
    }
    return Ret;
}

/**
 * @brief      Receive one byte data from the UART peripheral
 * @param[in]  none
 * @return     uint8:the received data
 */
uint8 Uart_ReceiveByte(void)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    /* Receive data */
    return (uint8)(UartRegBfPtr ->UART_RBR.RBR_LSB);
}

/**
 * @brief      Read received bytes from the RX FIFO
 * @param[in]  Length:  the number of bytes to be read. When call this function,
 *                      the user needs to make sure that the "length" is not
 *                      greater than the number of bytes that is available in
 *                      RX FIFO
 * @param[out] Data:  points to the memory where the data to be stored
 * @return     none
 */
void Uart_ReceiveBytes(uint32 Length, uint8 Data[])
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    uint32 cnt = 0U;
    for (cnt = 0U; cnt <Length; cnt++)
    {
        Data[cnt] = (uint8)UartRegBfPtr->UART_RBR.RBR_LSB;
    }
}

/**
 * @brief      Empty the RX FIFO. This function reads received data until RX
 *             FIFO is empty
 * @param[in]  none
 * @return     None
 */
void Uart_EmptyRxFifo(void)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);

    volatile uint8 DummyData;

    while (0U != UartRegBfPtr->UART_LSR.DR)
    {
        DummyData = (uint8)UartRegBfPtr->UART_RBR.RBR_LSB;
    }
}

/**
 * @brief      Set DMA transfer enable/disable when character timeout in fifo
 * @param[in]  Cmd: ENABLE/DISABLE
 * @return     none
 */
void Uart_EnableDmaTrigger(Common_ControlStateType Cmd)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    if(COMMON_ENABLE == Cmd  )
    {
        UartRegBfPtr->UART_LCR.IDLE_DMA_EN = (uint32)Cmd;
        UartRegBfPtr->UART_IER.TOI = (uint32)COMMON_DISABLE;
    }
    else
    {
        UartRegBfPtr->UART_LCR.IDLE_DMA_EN = (uint32)Cmd;
        UartRegBfPtr->UART_IER.TOI = (uint32)COMMON_ENABLE;
    }
    
}



/**
 * @brief      Set receive 9 bits data mode 0
 * @param[in]  none
 * @return     none
 */
void Uart_SetRx9BitsMode0Normal(void)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    if ((uint32)COMMON_SET == UartRegBfPtr->UART_LCR_EXT.DLS_E)
    {   /* Receive mode 0 */
        UartRegBfPtr->UART_LCR_EXT.ADDR_MATCH = 0x0U;
    }
}

/**
 * @brief      Program the address of  receive 9 bits data, mode 1
 * @param[in]  Addr: Set address
 * @return     none
 */
void Uart_SetRx9BitsMode1Addr(uint8 Addr)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
   
    /* set address in rar */
    UartRegBfPtr->UART_RAR.RAR = Addr;
}

/**
 * @brief      Select 9 bits hardware receive mode 1
 * @param[in]  none
 * @return     none
 */
void Uart_SetRx9BitsMode1Enable(void)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);

    UartRegBfPtr->UART_LCR_EXT.ADDR_MATCH = 0x1U;
}

/**
 * @brief      Receive address from the UART peripheral, mode 1
 * @param[in]  none
 * @return     uint16:the received address
 */
uint16 Uart_GetRx9BitsMode1Addr(void)
{
    uint16 Ret;
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    Reg_Uart_WType * UAartxw = (Reg_Uart_WType *)(Uart_RegWPtr);
    uint8 RxAddr;
    uint32 RegData;
    RegData = (uint32)UAartxw->UART_RBR;
    RxAddr = (uint8)UartRegBfPtr->UART_RAR.RAR;
    
    if (0x100U == (RegData & 0x100U))
    {
        if (RxAddr == (RegData & 0xFFU))
        {
            Ret = (uint16)RegData;
        }
        else
        {
            Ret = (uint16)COMMON_ERR;
        }
    }
    else
    {
        Ret = (uint16)COMMON_ERR;
    }

    return Ret;
}

/**
 * @brief      Receive one byte data from the UART peripheral, mode 1
 * @param[in]  none
 * @return     uint16:The received data
 */
uint16 Uart_GetRx9BitsMode1Data(void)
{
    uint16 Ret;
    uint32 RegData;
    Reg_Uart_WType * UartRegWPtr = (Reg_Uart_WType *)(Uart_RegWPtr);
    RegData = (uint32)UartRegWPtr->UART_RBR;
    if (0U == (RegData & 0x100U))
    {
        Ret = (uint16)(RegData & 0xFFU);
    }
    else
    {
        Ret = 0x1FF;
    }
    return Ret;
}

/**
 * @brief      Send one byte data to the UART peripheral
 * @param[in]  Data:The data to be sent
 * @return     none
 */
void Uart_SendByte(uint8 Data)
{
    Reg_Uart_WType * UartRegWPtr = (Reg_Uart_WType *)(Uart_RegWPtr);
    /* Send data */
    UartRegWPtr->UART_THR = (uint32)Data;
}

/**
 * @brief      Program the transmit target address, 9bits, mode 0
 * @param[in]  Addr:  program the address
 * @return     none
 */
void Uart_SetTx9BitsMode0Addr(uint8 Addr)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    /* transmit mode 0 */
    if (0x1U == UartRegBfPtr->UART_LCR_EXT.DLS_E)
    {
        UartRegBfPtr->UART_LCR_EXT.TRANSMIST_MODE = 0x0U;
        UartRegBfPtr->UART_TAR.TAR = (uint32)Addr;
    }
}

/**
 * @brief      Set send address bit, mode 0
 * @param[in]  none
 * @return     none
 */
void Uart_Set9BitsMode0SendAddr(void)
{
    /* transmit mode 0 */
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    UartRegBfPtr->UART_LCR_EXT.SEND_ADDR = 0x1U;
}

/**
 * @brief      Send 9 bits data to the UART peripheral, mode 1
 * @param[in]  Data:  The data to be send
 * @return     none
 */
void Uart_SetTx9BitsMode1Data(uint16 Data)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    Reg_Uart_WType * UartRegWPtr = (Reg_Uart_WType *)(Uart_RegWPtr);
    /* transmit mode 1 */
    if((uint32)COMMON_SET == UartRegBfPtr ->UART_LCR_EXT.DLS_E)
    {
        UartRegBfPtr ->UART_LCR_EXT.TRANSMIST_MODE = 0x1U;
        /* Send data */
        UartRegWPtr->UART_THR = ((uint32)Data) & 0x1FFU;
    }
}

/**
 * @brief      Config UART FIFO function
 * @param[in]  FiFoConfigPtr:Pointer to a FIFO configuration
 * @return     none
 */
void Uart_ConfigFIFO(const Uart_FIFOConfigType * FiFoConfigPtr)
{
    uint32 RegValue;
    Reg_Uart_WType * UartRegWPtr = (Reg_Uart_WType *)(Uart_RegWPtr);

    RegValue =((((uint32)(FiFoConfigPtr->RxFiFoTrigger) & 0xFU) << 8U)
                    | (((uint32)(FiFoConfigPtr->TxFiFoTrigger) & 0xFU) << 4U)
                    | (((uint32)(FiFoConfigPtr->TxFiFoReset) & 0x01U) << 2U)
                    | (((uint32)(FiFoConfigPtr->RxFiFoReset) & 0x01U) << 1U)
                    | ((uint32)(FiFoConfigPtr->FiFoEnable) & 0x01U));

    UartRegWPtr->UART_FCR = RegValue;
}

/**
 * @brief      Get UART FIFO status
 * @param[in]  none.
 * @return     Ret:
 * @retval     COMMON_SUCC:fifo is enable
 * @retval     COMMON_ERR :fifo is disable
 */
Common_ControlStateType Uart_GetFifoStatus(void)
{
    Common_ControlStateType Ret;
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    if(3U == UartRegBfPtr->UART_IIR.FIFOSE)
    {
        Ret = COMMON_ENABLE;
    }
    else
    {
        Ret = COMMON_DISABLE;
    }
    return Ret;
}

/**
 * @brief      Reset uart receive fifo
 * @param[in]  none
 * @return     none
 */
void Uart_ResetRxFiFo(void)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);

    UartRegBfPtr->UART_FCR.RFIFOR = 1U;
}

/**
 * @brief      Reset uart transmit fifo
 * @param[in]  none
 * @return     none
 */
void Uart_ResetTxFiFo(void)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    UartRegBfPtr->UART_FCR.XFIFOR = 1U;
}

/**
 * @brief       Get transmit FIFO level
  * @param[in]  none.
 * @return      uint32:The number of valid data entries in the transmit FIFO memory.
 */
uint32 Uart_GetTxFiFoLevel(void)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);

    return (UartRegBfPtr->UART_TFL.TFL);
}

/**
 * @brief      Get receive FIFO level
 * @param[in]  none.
 * @return     uint32:The number of valid data entries in the receive FIFO memory.
 */
uint32 Uart_GetRxFiFoLevel(void)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);

    return (UartRegBfPtr->UART_RFL.RFL);
}

/**
 * @brief      Enable/Disable debug enable. If enabled, hardware will not clean 
 *             the receiver fifo automatically
 * @param[in]  Cmd: ENABLE/DISABLE
 * @return     none
 */
void Uart_ControlDebugCmd(Common_ControlStateType Cmd)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    UartRegBfPtr->UART_LCR.DEBUG_EN = (uint32)Cmd;
}

/**
 * @brief      Enable/Disable UART programmable THRE interrupt mode.
 * @param[in]  cmd:  ENABLE/DISABLE
 *                
 * @return     none
 *
 */
void Uart_EnableProgramTHRE(Common_ControlStateType Cmd)
{
    Reg_Uart_WType * UartRegWPtr = (Reg_Uart_WType *)(Uart_RegWPtr);
    if((uint32)COMMON_ENABLE == (uint32)Cmd)
    {
        UartRegWPtr->UART_IER |= (uint32)UART_CHECK_PTIME;
    }
    else
    {
        UartRegWPtr->UART_IER &= ~((uint32)UART_CHECK_PTIME);
    }
}

/**
 * @brief      Config idle detect 
 * @param[in]  ConfigPtr: config idle detect 
 * @return     none
 */
void Uart_ConfigIdleDetect(Uart_IdleDetectConfigType *ConfigPtr)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    UartRegBfPtr->UART_LCR.IDLE_DET_LENGTH = (uint32)ConfigPtr->Len;
    UartRegBfPtr->UART_LCR.IDLE_DET_EN = (uint32)ConfigPtr->Cmd;
}

/**
 * @brief      Config UART sample point, default is 8
 * @param[in]  DelVal: config UART sample point
 * @note       Default sample ratio is 16, sample delay set to 8 means sample 
 *             at the center of data. No special requirements. You are advised to 
 *             retain the default value
 * @return     none
 */
void Uart_SetSampleDelay(uint8 DelVal)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    
    UartRegBfPtr->UART_LCR.RX_SMP_DLY = DelVal;
}

/**
 * @brief      Set uart break detect len
 * @param[in]  BreakDetLen: break detect len
 *                      - UART_BREAKDETECTLEN_95
 *                      - UART_BREAKDETECTLEN_105
 * @return     None
 */
void Uart_SetBreakDetectLen(Uart_BreakDetectLen BreakDetLen)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    UartRegBfPtr->UART_LCR.LBK_SW = (uint32)BreakDetLen;
}

/**
 * @brief      Config Lin readback sample point, default is 8
 * @param[in]  DelVal: config Lin sample point
 * @note       Default sample ratio is 16, sample delay set to 8 means sample 
 *             at the center of data. No special requirements. You are advised to 
 *             retain the default value
 * @return     none
 */
void Uart_LinSetSampleDelay(uint8 DelVal)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    
    UartRegBfPtr->UART_LIN_CTL.COLLISION_SAMPLE_DELAY = DelVal;
}

/**
 * @brief      Config UART in LIN mode
 * @param[in]  ConfigPtr:  points to the configuration of LIN mode
 * @return     none
 */
void Uart_LinConfig(const Uart_LinConfigType *ConfigPtr)
{

    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    Reg_Uart_WType * UartRegWPtr = (Reg_Uart_WType *)(Uart_RegWPtr);
    
    uint32 IntegerDiv, FractionalDiv;
    Clk_ClockNodeType UartClkId = CLK_NODE_UART;
    uint32 Tmp;
    
    /* Enable DLAB to set baud rate */
    UartRegBfPtr->UART_LCR.DLAB = 0x01U;
    Tmp = Clk_GetClkFreq(UartClkId, ConfigPtr->OscFreq);
    /* serial frequency */
    Uart_SerialFreq = Tmp;
     /* get baudrate divisor*/
    IntegerDiv = Tmp/(16U * ConfigPtr->BaudRate);

    /* Config the DLL and DLH registers */
    UartRegBfPtr->UART_DLR.DLR = IntegerDiv & 0xFFFFU;
    
    /* calculate fractional divisor
       divisor = clkFreq/(16*baudrate) = BRDI +BRDF
       FD = BRDF*2^4 = 16* BRDF
       BRDF = clkFreq%(16*baudrate)/(16*baudrate)
       FD = clkFreq%(16*baudrate)*16/(16*baudrate)
          = clkFreq%(16*baudrate)/baudrate  */
    FractionalDiv = Tmp%(16U * ConfigPtr->BaudRate);
    FractionalDiv /= ConfigPtr->BaudRate;
    UartRegBfPtr->UART_FD.FD = FractionalDiv;
    
    /* Disable DLAB */
    UartRegBfPtr->UART_LCR.DLAB = 0x0U;
    /* no parity */
    UartRegBfPtr->UART_LCR.PEN = 0x0U;

    /* 8 bits */
    UartRegBfPtr->UART_LCR.DLS = 3U;

    /* 1 stop bit */
    UartRegBfPtr->UART_LCR.STOP = 0U;

    UartRegBfPtr->UART_AFCR.RTS = 0U;

    /* LIN mode */
    UartRegBfPtr->UART_LIN_CTL.LIN_MODE = 1U;
    UartRegBfPtr->UART_LIN_CTL.MASTER_MODE = (uint32)ConfigPtr->Mode;

    /* auto sync */
    UartRegBfPtr->UART_LIN_CTL.AUTO_SYNC_EN = (uint32)ConfigPtr->AutoSyncEn;
    /* collision sample delay */
    UartRegBfPtr->UART_LIN_CTL.COLLISION_SAMPLE_DELAY = (uint32)ConfigPtr->SampleDelay;
    /* bit error */
    UartRegBfPtr->UART_LIN_CTL.BIT_ERR_DET_EN = (uint32)ConfigPtr->BitErrorEn;
     
    /* ID filter enable */
    UartRegBfPtr->UART_LIN_PID_FILTER_CTRL.LIN_FILTER_EN = (uint32)ConfigPtr->IdFilterEn;
    
    /* enable and clear FIFO in LIN mode */
    UartRegWPtr->UART_FCR |= 7U;
}

/**
 * @brief      Enable/Disable LIN software calculate PID parity.
 * @param[in]  Cmd:  
 *                -COMMON_ENABLE:software calculate pid
 *                -COMMON_DISABLE:hardware calculate pid,default is hardware calculate.
 * @return     none
 */
void Uart_LinEnableSwCalcPid(Common_ControlStateType Cmd)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    /*PID calculation method*/
    UartRegBfPtr->UART_LIN_CTL.PID_OVRD_EN = (uint32)Cmd;
}

/**
 * @brief      Enable/Disable LIN readback detect bit error function.
 * @param[in]  Cmd:  COMMON_ENABLE/COMMON_DISABLE
 * @return     none
 */
void Uart_LinEnableBitErrorDetect(Common_ControlStateType Cmd)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    /*PID calculation method*/
    UartRegBfPtr->UART_LIN_CTL.BIT_ERR_DET_EN = (uint32)Cmd;
}

/**
 * @brief      Set UART in LIN mode as a LIN master and start to send the header
 * @param[in]  HeaderPtr:  points to the header to be send
 * @return     Ret:
 * @retval     COMMON_SUCC:start send header
 * @retval     COMMON_ERR :UART status is busy
 */
Common_ResultStatusType Uart_LinSendHeader(const Uart_LinHeaderType *HeaderPtr)
{
    Common_ResultStatusType Ret;
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);

    uint32 BreakLen;
    uint32 OpStart = UartRegBfPtr->UART_LIN_CTL.OP_START;

    /* check if UART is busy */
    if ( 0U != OpStart )
    {
        Ret = COMMON_ERR;
    }
    else
    {
        UartRegBfPtr->UART_LIN_HEADER_CFG.LIN_DEL_LENGTH = HeaderPtr->DeleLen - 1U;
        UartRegBfPtr->UART_LIN_HEADER_CFG.PID = HeaderPtr->Pid;
        
        BreakLen = HeaderPtr->BreakLen;
        UartRegBfPtr->UART_LIN_HEADER_CFG.LBKM = (BreakLen >= UART_LIN_SEND_BREAK_MIN)?
                           BreakLen :UART_LIN_SEND_BREAK_MIN ;
        UartRegBfPtr->UART_LIN_CTL.MASTER_MODE = 1U;
        /* start to send */
        UartRegBfPtr->UART_LIN_CTL.OP_MODE = UART_LIN_OPERATION_HEADER;
        UartRegBfPtr->UART_LIN_CTL.OP_START = 1U;
        Ret = COMMON_SUCC;
    }
    return Ret;
}

/**
 * @brief       This function stops receiving/sending header/response of LIN. 
 * @param[in]   none
 * @return      none
 */
void Uart_LinStopTransmission(void)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    UartRegBfPtr->UART_LIN_CTL.OP_START = 0U;
}

/**
 * @brief       If LIN is sending/receiving header/response
 *              this function returns COMMON_SET, otherwise, return COMMON_RESET.
 * @param[in]   none
 * @return      Ret:
 * @retval      COMMON_SET   :UART status is busy
 * @retval      COMMON_RESET :UART transmission is done
 */

Common_FlagStatusType Uart_LinGetTransmissionStatus(void)
{
    Common_FlagStatusType Ret = COMMON_RESET;
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    
    uint32 OpStart = UartRegBfPtr->UART_LIN_CTL.OP_START;

    /* check if UART is busy */
    if( 0U != OpStart )
    {
        Ret = COMMON_SET;
    }
    return Ret;
}

/**
 * @brief      Set LIN as a slave and start to receive a header.
 *             FIFO is disabled before it starts to receive a header
 * @param[in]  none
 * @return     Ret:
 * @retval     COMMON_SUCC : it starts to receive header
 * @retval     COMMON_ERR  :  it dose not start to receive header due to UART is busy
 */
Common_ResultStatusType Uart_LinStartReceiveHeader(void)
{
    Common_ResultStatusType Ret;
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    Reg_Uart_WType * UartRegWPtr = (Reg_Uart_WType *)(Uart_RegWPtr);
         
    uint32 OpStart = UartRegBfPtr->UART_LIN_CTL.OP_START;
    
    /* check if UART is busy */
    if( 0U != OpStart)
    {
        Ret = COMMON_ERR;
    }
    else
    {       
        /* reset rx fifo then disable fifo */        
        UartRegBfPtr->UART_FCR.RFIFOR = 1U; 
        UartRegBfPtr->UART_FCR.FIFOE = 0U;                  

        UartRegBfPtr->UART_LIN_CTL.MASTER_MODE = 0U;
        /* clear  BI and FE*/
        UartRegWPtr->UART_LSR = (UART_LSI_FE|UART_LSI_BI);
        /* start to receive */
        UartRegBfPtr->UART_LIN_CTL.OP_MODE = UART_LIN_OPERATION_HEADER;
        UartRegBfPtr->UART_LIN_CTL.OP_START = 1U;

        Ret = COMMON_SUCC;
    }
    return Ret;
}

/**
 * @brief      Read the 6-bit ID(exclude parity bits) of header 
 * @param[in]  none
 * @return     uint8: ID
 */
uint8 Uart_LinGetId(void)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);

    return (uint8)((uint8)(UartRegBfPtr->UART_LIN_HEADER_CFG.PID) & (uint8)UART_LIN_ID_MASK);
}

/**
 * @brief      Read the 8-bit PID of header
 * @param[in]  none
 * @return     uint32:ID
 */
uint32 Uart_LinGetPid(void)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);

    return UartRegBfPtr->UART_LIN_HEADER_CFG.PID;
}

/**
 * @brief      start to send a response
 * @param[in]  RspPtr:  Points to response structure to be sent.
 * @return     Ret:
 * @retval     COMMON_SUCC : response starts to send
 * @retval     COMMON_ERR  : response is not sent due to UART is busy
 */
Common_ResultStatusType Uart_LinSendResponse(const Uart_LinResponseType *RspPtr)
{
    Common_ResultStatusType Ret;
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    Reg_Uart_WType * UartRegWPtr = (Reg_Uart_WType *)(Uart_RegWPtr);
    uint32 Cnt = 0U;
    uint32 OpStart = UartRegBfPtr->UART_LIN_CTL.OP_START;
    
    /* check if UART is busy */
    if ((RspPtr->Len > 8U) || ( 0U !=OpStart ))
    {
        Ret = COMMON_ERR;
    }
    else
    {
        /* enable fifo  */
        UartRegWPtr->UART_FCR |= UART_ENABLE_FIFO;
        
        UartRegBfPtr->UART_LIN_RSP_CFG.RSP_LENGTH = RspPtr->Len;
        UartRegBfPtr->UART_LIN_RSP_CFG.CHECKSUM_TYPE = (uint32)RspPtr->CheckType;

        for (Cnt = 0U; Cnt < RspPtr->Len; Cnt++)
        {
            UartRegWPtr->UART_THR = RspPtr->Data[Cnt];
        }

        UartRegBfPtr->UART_LIN_RSP_CFG.RSP_DIR = 1U;

        UartRegBfPtr->UART_LIN_CTL.OP_MODE = UART_LIN_OPERATION_RESPONSE;

        UartRegBfPtr->UART_LIN_CTL.OP_START = 1U;
        Ret = COMMON_SUCC;
    }
    return Ret;
}

/**
 * @brief      start to receive a response
 * @param[in]  Check:  checksum type.
                       - UART_LIN_CHECKSUM_CLASSIC
                       - UART_LIN_CHECKSUM_ENHANCED
 * @param[in]  Len:  response length.
 * @return     Ret:
 * @retval     COMMON_SUCC : it starts to receive response
 * @retval     COMMON_ERR  : it dose not start to receive response due to UART is busy
 */
Common_ResultStatusType Uart_LinStartReceiveResponse(Uart_LinCheckSumType Check,
                                                          uint32 Len)
{
    Common_ResultStatusType Ret;
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    Reg_Uart_WType * UartRegWPtr = (Reg_Uart_WType *)(Uart_RegWPtr);
    
    uint32 OpStart = UartRegBfPtr->UART_LIN_CTL.OP_START;

    /* check if UART is busy */
    if( 0U != OpStart )
    {
        Ret = COMMON_ERR;
    }
    else
    {
        /* enable fifo and reset rx fifo */
        UartRegWPtr->UART_FCR |= (UART_ENABLE_FIFO|UART_RESET_RX_FIFO);

        UartRegBfPtr->UART_LIN_RSP_CFG.RSP_LENGTH = Len;
        UartRegBfPtr->UART_LIN_RSP_CFG.CHECKSUM_TYPE = (uint32)Check;

        UartRegBfPtr->UART_LIN_RSP_CFG.RSP_DIR = 0U;
        UartRegBfPtr->UART_LIN_CTL.OP_MODE = UART_LIN_OPERATION_RESPONSE;
        UartRegBfPtr->UART_LIN_CTL.OP_START = 1U;
        Ret = COMMON_SUCC;
    }
    return Ret;
}

/**
 * @brief      read a response. if a response is received, this function can be
 *             called to get the data of response. This function is called
 *             after UART_LinStartReceiveResponse() and UART_INTSTA_RSP_DONE
 *             status is set.
 * @param[in]  Len:  response length to be read.
 * @param[in]  Data:  points to the memory where the response data to be stored.
 *                    the memory size must not be smaller than len
 * @return     none
 */
void Uart_LinReadResponse(uint32 Len, uint8 Data[])
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    uint32 Cnt;

    for ( Cnt = 0U; Cnt < Len; Cnt++)
    {
        Data[Cnt] = (uint8)UartRegBfPtr->UART_RBR.RBR_LSB;
    }
}

/**
 * @brief       Add LIN response timeout function
 *              The normal response timeout= (response length(byte) + checksum(1 byte)) * 1.4
 *              If the api is called, 
                timeout = (response length(byte) + checksum(1 byte)) * 1.4 + len(bits)
 * @param[in]   Len: several bits time added to delay LIN response timeout
 * @return      none
 */
void Uart_LinAddResponseTimeout(uint32 Len)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);

    UartRegBfPtr->UART_LIN_RSP_CFG.ADD_TO_CNT = Len;
}

/**
 * @brief      Get current value of Line Status register
* @param[in]   LineStatus:
 *                       - UART_LINESTA_DR
 *                       - UART_LINESTA_OE
 *                       - UART_LINESTA_PE
 *                       - UART_LINESTA_FE
 *                       - UART_LINESTA_BI
 *                       - UART_LINESTA_THRE
 *                       - UART_LINESTA_TEMT
 *                       - UART_LINESTA_RFE
 *                       - UART_LINESTA_TRANS_ERR
 *                       - UART_LINESTA_ADDR_RCVD
 *                       - UART_LINESTA_ALL
 * @return     Common_FlagStatusType:The state value of UART Line Status register
 * @retval     COMMON_SET: The Line status bit is set
 * @retval     COMMON_RESET:The Line status bit is reset
 */
Common_FlagStatusType Uart_GetLineStatus(Uart_LineStatusType LineStatus)
{
    Common_FlagStatusType BitStatus;
    Reg_Uart_WType * UartRegWPtr = (Reg_Uart_WType *)(Uart_RegWPtr);

    BitStatus = ((( 0U != (UartRegWPtr->UART_LSR & Uart_LineStatusTable[LineStatus]))) 
                 ? COMMON_SET : COMMON_RESET);

    return BitStatus;
}

/**
 * @brief      Clear line status
 * @param[in]  LineStatus:
 *                       - UART_LINESTA_OE
 *                       - UART_LINESTA_PE
 *                       - UART_LINESTA_FE
 *                       - UART_LINESTA_BI
 *                       - UART_LINESTA_RFE
 *                       - UART_LINESTA_TRANS_ERR
 *                       - UART_LINESTA_ADDR_RCVD
 *                       - UART_LINESTA_ASYNC
 *                       - UART_LINESTA_ALL
 * @return     none
 */
void Uart_ClearLineStatusFlag(Uart_LineStatusType LineStatus)
{
    Reg_Uart_WType * UartRegWPtr = (Reg_Uart_WType *)(Uart_RegWPtr);

    UartRegWPtr->UART_LSR = Uart_LineStatusTable[LineStatus]; 
}

/**
 * @brief      Get UART (UART_USR) status
 * @param[in]  Type: select one status type
                     - UART_STA_BUSY
 *                   - UART_STA_TFNF
 *                   - UART_STA_TFE
 *                   - UART_STA_RFNE
 *                   - UART_STA_RFF
 * @return     UART status:
 * @retval     COMMON_SET: The Type status bit is set
 * @retval     COMMON_RESET:The Type status bit is reset
 */
Common_FlagStatusType Uart_GetStatus(Uart_StatusType Type)
{
    Common_IntStatusType BitStatus;
    Reg_Uart_WType * UartRegWPtr = (Reg_Uart_WType *)(Uart_RegWPtr);

    BitStatus = ( 0U != (UartRegWPtr->UART_USR & 
                  ((uint32)1U << (uint32)Type))) ? COMMON_SET : COMMON_RESET;

    return BitStatus;
}

/**
 * @brief      Get current LIN interrupt Status
 * @param[in]  StaType: select one interrupt status
 *                     - UART_LIN_INTSTA_ERR
 *                     - UART_LIN_INTSTA_WUP_OP_SUCC
 *                     - UART_LIN_INTSTA_HEADER_OP_SUCC
 *                     - UART_LIN_INTSTA_RSP_OP_SUCC
 * @note       This api is used to get lin interrupt status when the interrupt is masked
 * @return     Common_IntStatusType:The state value of LIN interrupt status register
 * @retval     COMMON_SET: The Line int status bit is set
 * @retval     COMMON_RESET:The Line int status bit is reset
 */
Common_IntStatusType Uart_LinGetIntStatus(Uart_LinIntStatusType StaType)
{
    Common_IntStatusType BitStatus;
    Reg_Uart_WType * UartRegWPtr = (Reg_Uart_WType *)(Uart_RegWPtr);
   
    BitStatus = (( 0U != (UartRegWPtr->UART_LIN_LISR  &  
                   ((uint32)1U << (uint32)StaType ))) ? COMMON_SET: COMMON_RESET);

    return BitStatus;
}

/**
 * @brief      Clear LIN interrupt Status
 * @param[in]  StaType: select one interrupt status
 *                     - UART_LIN_INTSTA_ERR
 *                     - UART_LIN_INTSTA_WUP_OP_SUCC
 *                     - UART_LIN_INTSTA_HEADER_OP_SUCC
 *                     - UART_LIN_INTSTA_RSP_OP_SUCC
 * @note       UART_LIN_INTSTA_ERR need call UART_LinClearErrorStatus() to clear
 * @return     none.
 */
void Uart_LinClearIntStatus(Uart_LinIntStatusType StaType)
{
    Reg_Uart_WType * UartRegWPtr = (Reg_Uart_WType *)(Uart_RegWPtr);
    UartRegWPtr->UART_LIN_LISR =  Uart_LinInterruptStatusTable[StaType];
}

/**
* @brief       Mask/Unmask the UART interrupt
 *             UART_INT_RCVRTO and UART_INT_RBFI are controlled by the same bit,
 *             so they are masked/unmasked at the same time. But UART_INT_RCVRTO
 *             is only generated when it is in fifo mode and fifo is enabled
 * @param[in]  IntType: select the interrupt
 *                      - UART_INT_RBFI
 *                      - UART_INT_TBEI
 *                      - ......
 *                      - UART_INT_LIN_RSP_OP_SUCC
 *                      - UART_INT_LIN_ALL
 *                      - UART_INT_ALL
 * @param[in]  IntMask:  Enable/Disable Specified interrupt type
                        - COMMON_UNMASK
 *                      - COMMON_MASK
 * @return     none
 */

void Uart_SetIntMask(Uart_IntType IntType, Common_IntMaskType IntMask)
{
    Reg_Uart_WType * UartRegWPtr = (Reg_Uart_WType *)(Uart_RegWPtr);

    if(COMMON_UNMASK == IntMask )
    {
        if(IntType < UART_INT_LIN_ERR )
        {
            UartRegWPtr->UART_IER  |= (Uart_InterruptMaskTable[IntType]);
        }
        else if(UART_INT_ALL == IntType)
        {
            UartRegWPtr->UART_IER  |= (Uart_InterruptMaskTable[IntType]);
            UartRegWPtr->UART_LIN_INT_EN  |= (Uart_InterruptMaskTable[UART_INT_LIN_ALL]);
        }
        else
        {
            UartRegWPtr->UART_LIN_INT_EN  |= (Uart_InterruptMaskTable[IntType]);
        }
    }
    else
    {
        if(IntType < UART_INT_LIN_ERR)
        {
            UartRegWPtr->UART_IER &= (~(Uart_InterruptMaskTable[IntType]));
        }
        else if(UART_INT_ALL == IntType )
        {
            UartRegWPtr->UART_IER &= (~(Uart_InterruptMaskTable[IntType]));
            UartRegWPtr->UART_LIN_INT_EN &= (~(Uart_InterruptMaskTable[UART_INT_LIN_ALL]));
        }
        else
        {
            UartRegWPtr->UART_LIN_INT_EN &= (~(Uart_InterruptMaskTable[IntType]));
        }
    }
}


/**
 * @brief      Get Lin error status
 * @param[in]  ErrType: Specifies the error status type
 *                      - UART_LIN_ERROR_SYNC
 *                      - UART_LIN_ERROR_PID
 *                      - UART_LIN_ERROR_CHECKSUM
 *                      - UART_LIN_ERROR_TO
 *                      - UART_LIN_ERROR_BIT
 *                      - UART_LIN_ERROR_WUP
 *                      - UART_LIN_ERROR_ALL
 * @return     The state value of LIN error Status register
 * @retval     COMMON_SET: The Lin error status bit is set
 * @retval     COMMON_RESET:The Lin error status bit is reset
 */
Common_IntStatusType Uart_LinGetErrorStatus(Uart_LinErrorType ErrType)
{
    Common_IntStatusType BitStatus;
    Reg_Uart_WType * UartRegWPtr = (Reg_Uart_WType *)(Uart_RegWPtr);
    if(UART_LIN_ERROR_ALL == ErrType)
    {
        BitStatus = (((UartRegWPtr->UART_LIN_ERR & 
                    (uint32)UART_LIN_ERROR_ALL_MASK) != 0U ) ? COMMON_SET: COMMON_RESET);
    }
    else
    {
        BitStatus = (( 0U != (UartRegWPtr->UART_LIN_ERR  &  
                   ((uint32)1U << (uint32)ErrType ))) ? COMMON_SET: COMMON_RESET);
    }
    
    return BitStatus;
}

/**
 * @brief      Clear Lin error status
 * @param[in]  ErrType: Specifies the error status type
 *                      - UART_LIN_ERROR_SYNC
 *                      - UART_LIN_ERROR_PID
 *                      - UART_LIN_ERROR_CHECKSUM
 *                      - UART_LIN_ERROR_TO
 *                      - UART_LIN_ERROR_BIT
 *                      - UART_LIN_ERROR_WUP
 *                      - UART_LIN_ERROR_ALL
 * @return     none
 */
void Uart_LinClearErrorStatus(Uart_LinErrorType ErrType)
{
    Reg_Uart_WType * UartRegWPtr = (Reg_Uart_WType *)(Uart_RegWPtr);

    if(ErrType < UART_LIN_ERROR_ALL)
    {
        UartRegWPtr->UART_LIN_ERR = (uint32)1U << (uint32)ErrType;
    }
    else
    {
        UartRegWPtr->UART_LIN_ERR = UART_LIN_ERR_FLAG;
    }
}



/**
 * @brief      LIN detect wakeup signal config
 * @param[in]  WupCfgPtr: Pointer to  Wakeup configuration
 * @return     Ret:
 * @retval     COMMON_SUCC: start delect  wakeup signal
 * @retval     COMMON_ERR:UART status is busy
 */
Common_ResultStatusType Uart_LinDetectWakeupSignal(Uart_LinDetWakeupCfgType *WupCfgPtr)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
   
    Common_ResultStatusType Ret = COMMON_SUCC;
    uint32 OpStart = UartRegBfPtr->UART_LIN_CTL.OP_START;
    /* check if UART is busy */
    if (0U != OpStart)
    {
        Ret = COMMON_ERR;
    }
    else
    { 
        /*config wakeup counter clock divisor*/
        uint32 WupDiv;
        WupDiv = Uart_SerialFreq/(16U * (uint32)WupCfgPtr->WakeupFreq);
        UartRegBfPtr->UART_LIN_WUP_CFG1.WDR = WupDiv;
        /* config timeout action */
        UartRegBfPtr->UART_LIN_WUP_CFG2.WUP_TO_ACT = (uint32) WupCfgPtr->ActCmd;
        /* wakeup detection high threhold */
        UartRegBfPtr->UART_LIN_WUP_CFG2.WUP_DET_THE_HIGH = (uint32)WupCfgPtr->WakeupDetThrHigh;
        /* wakeup detection low threhold */
        UartRegBfPtr->UART_LIN_WUP_CFG2.WUP_DET_THE_LOW = (uint32)WupCfgPtr->WakeupDetThrLow;
        /* wakeup detection */
        UartRegBfPtr->UART_LIN_WUP_CFG1.WUP_OP_SEL = UART_LIN_DETECT_WAKEUP_SIGNAL;

        UartRegBfPtr->UART_LIN_CTL.OP_MODE = UART_LIN_OPERATION_WAKEUP;
        UartRegBfPtr->UART_LIN_CTL.OP_START = 1U;
    }
    return Ret;
}

/**
 * @brief      LIN send wakeup signal function
 * @param[in]  WuFreq:the frequency of wakeup counter. 
 *                    Wakeup counter clock frequency = (serial clock freq)/(16 * WDR)
 * @param[in]  Num   :the length of wakeup signal will be calculated as follows
 *                    length = num / wuFreq
 * @return     Ret   :
 * @retval     COMMON_SUCC:start send  wakeup signal
 * @retval     COMMON_ERR :UART status is busy
 */
Common_ResultStatusType Uart_LinSendWakeupSignal(uint16 WuFreq,uint8 Num)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
   
    Common_ResultStatusType Ret = COMMON_SUCC;
    uint32 OpStart = UartRegBfPtr->UART_LIN_CTL.OP_START;

    /* check if UART is busy */
    if( 0U != OpStart )
    {
        Ret = COMMON_ERR;
    }
    else
    {
       /*config wakeup counter clock divisor*/
        uint32 WupDiv;
        WupDiv = Uart_SerialFreq/(16U * (uint32)WuFreq);
        UartRegBfPtr->UART_LIN_WUP_CFG1.WDR = WupDiv;
        /*config len of wakeup signal*/
        UartRegBfPtr->UART_LIN_WUP_CFG1.WUP_SEND_LEN = (uint32)Num;
        /* transmit wakeup */
        UartRegBfPtr->UART_LIN_WUP_CFG1.WUP_OP_SEL = UART_LIN_TRANSMITTING_WAKEUP_SIGNAL;

        UartRegBfPtr->UART_LIN_CTL.OP_MODE = UART_LIN_OPERATION_WAKEUP;
        UartRegBfPtr->UART_LIN_CTL.OP_START = 1U;
    }
    
    return Ret;
}

/**
 * @brief      Enable a ID filter and config the ID filter value
 * @param[in]  IdIndex:  the index of ID filter. It indicates which ID filter
 *                       will be enabled. Its range is 0-15
 * @param[in]  IdFilterValue:  the value of ID filter.
 * @return     Ret:
 * @retval     COMMON_SUCC:enable filter success
 * @retval     COMMON_ERR :parameter error
 */
Common_ResultStatusType Uart_LinEnableIdFilter(uint8 IdIndex,uint8 IdFilterValue)
{
    Common_ResultStatusType Ret;
    volatile uint32* IdFilterPtr[4];
    volatile uint32 RegTmp;
    uint32 Tmp;
    uint32 IdInd = (uint32)IdIndex;
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    Reg_Uart_WType * UartRegWPtr = (Reg_Uart_WType *)(Uart_RegWPtr);

    IdFilterPtr[0] = &(UartRegWPtr->UART_LIN_PID_FILTER_0);
    IdFilterPtr[1] = &(UartRegWPtr->UART_LIN_PID_FILTER_1);
    IdFilterPtr[2] = &(UartRegWPtr->UART_LIN_PID_FILTER_2);
    IdFilterPtr[3] = &(UartRegWPtr->UART_LIN_PID_FILTER_3);
    
    if(IdInd >= 16U)
    {
        Ret = COMMON_ERR;
    }
    else
    {
        Tmp = (IdInd%4U)*8U;
        RegTmp = *IdFilterPtr[IdInd/4UL] & ~(0x3FUL << Tmp);
        *IdFilterPtr[IdInd/4U] = RegTmp | ((uint32)IdFilterValue << Tmp);
        UartRegBfPtr->UART_LIN_PID_FILTER_CTRL.FID_MASK |= (1UL << IdInd);

        Ret = COMMON_SUCC;
    }
    return Ret;
}

/**
 * @brief      Disable a ID filter
 * @param[in]  IdIndex:  the index of ID filter. It indicates which ID filter
 *                       will be disabled. Its range is 0-15
 * @return     Ret:
 * @retval     COMMON_SUCC:disable filter success
 * @retval     COMMON_ERR :parameter error
 */
Common_ResultStatusType Uart_LinDisableIdFilter(uint32 IdIndex)
{
    Common_ResultStatusType Ret;
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);

    if(IdIndex >= 16U)
    {
        Ret = COMMON_ERR;
    }
    else
    {
        UartRegBfPtr->UART_LIN_PID_FILTER_CTRL.FID_MASK &= ~(1UL << IdIndex);
        Ret = COMMON_SUCC;
    }
    return Ret;
}

/**
 * @brief      Enable and config the ID vague filter
 * @param[in]  IdFilterValue: the value of ID filter. Its range is 0 - 0x3F.
 * @param[in]  IdFilterMask : the mask of the vague ID filter. If a bit of
 *                            idFilterMask is 0, this bit in the vague ID filter
 *                            is ignored. Only bit0-5 is valid.
 * @return     none
 */
void Uart_LinEnableVagueIdFilter(uint8 IdFilterValue,uint8 IdFilterMask)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);
    UartRegBfPtr->UART_LIN_PID_FILTER_VAGUE.FID_VAGUE = IdFilterValue;
    UartRegBfPtr->UART_LIN_PID_FILTER_CTRL.FID_VAGUE_MASK = IdFilterMask;
    UartRegBfPtr->UART_LIN_PID_FILTER_CTRL.FID_MASK |= ((uint32)1U << 16U);
}

/**
 * @brief      Disable the vague ID filter
 * @param[in]  none
 * @return     none
 */
void Uart_LinDisableVagueIdFilter(void)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);

    UartRegBfPtr->UART_LIN_PID_FILTER_CTRL.FID_MASK &= ~((uint32)1U << 16U);
}

/**
 * @brief      Enable/Disable ID filters
 * @param[in]  IdIndex:the IDs to be enabled/disabled. The bit0-15 correspond to
 *                     ID filter 0-15. Bit 16 corresponds to the vague ID filter.
 *                     If a bit is 1,the corresponding ID filter is enabled;
 *                     otherwise it is disabled.
 * @return    none
 */
void Uart_LinControlIdFilters(uint32 IdIndex)
{
    Reg_Uart_BfType * UartRegBfPtr = (Reg_Uart_BfType *)(Uart_RegBfPtr);

    UartRegBfPtr->UART_LIN_PID_FILTER_CTRL.FID_MASK = IdIndex;
}

/**
 * @brief      Config the ID filter values for ID filter 0-15. It will config
 *             the ID filter values for ID filter 0 - (idNum-1) in order. The
 *             value to be configured is stored in the memory that idValues points
 *             to.
 * @param[in]  IdNum   :  the number of IDs to be configured. The range is 1-16.
 * @param[in]  IdValues:  a pointer to the ID filter value that will be used to
 *                        config the ID filters. The size of the memory must
 *                        not be smaller than idNum
 * @return     Ret:
 * @retval     COMMON_SUCC:config success
 * @retval     COMMON_ERR :parameter error
 */
Common_ResultStatusType Uart_LinConfigIdFilters(uint8 IdNum,const uint8 IdValues[])
{
    Common_ResultStatusType Ret;

    volatile uint32 RegTmp;
    uint32 Tmp;
    uint8 Index;
    volatile uint32* IdFilterPtr[4];
    Reg_Uart_WType * UartRegWPtr = (Reg_Uart_WType *)(Uart_RegWPtr);
    
    IdFilterPtr[0] = &(UartRegWPtr->UART_LIN_PID_FILTER_0);
    IdFilterPtr[1] = &(UartRegWPtr->UART_LIN_PID_FILTER_1);
    IdFilterPtr[2] = &(UartRegWPtr->UART_LIN_PID_FILTER_2);
    IdFilterPtr[3] = &(UartRegWPtr->UART_LIN_PID_FILTER_3);

    if(IdNum > 16U)
    {
        Ret = COMMON_ERR;
     }
    else
    {
        for(Index = 0U; Index < IdNum; Index++)
        {
            Tmp = (Index % 4UL) * 8UL;
            RegTmp = *IdFilterPtr[Index/4UL] & ~(0x3FUL << Tmp);
            *IdFilterPtr[Index/4UL] = RegTmp | (uint8)(IdValues[Index] << Tmp);
            RegTmp = RegTmp | ((uint32)(IdValues[Index]) << Tmp);
            *IdFilterPtr[Index/4UL] = RegTmp;
        }
        Ret = COMMON_SUCC;
    }
    return Ret;
}

/**
 * @brief  UART interrupt function
 *
 * @param  none
 *
 * @return none
 *
 */
void Uart_DriverIrqHandler(void)
{
    Uart_IntHandler();
}

/** @}end of group Public_FunctionDefinition */
