/**************************************************************************************************/
/**
 * @file      : Z20K11xM_uart.c
 * @brief     : UART module driver file.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (c) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#include "Z20K11xM_uart.h"
#include "Z20K11xM_clock.h"

/** @addtogroup  Z20K11X_Peripheral_Driver
 *  @{
 */

/** @defgroup UART UART
 *  @brief UART driver modules
 *  @{
 */

/** @defgroup UART_Private_Type
 *  @{
 */

/** @}end of group UART_Private_Type*/

/** @defgroup UART_Private_Defines
 *  @{
 */

/**
 *  @brief UART interrupt IID definition
 */
#define UART_INTSTA_IID_TBEI          0x02U
#define UART_INTSTA_IID_RBFI          0x04U
#define UART_INTSTA_IID_LSI           0x06U
#define UART_INTSTA_IID_BYDET         0x07U
#define UART_INTSTA_IID_RCVRTO        0x0CU
#define UART_INTSTA_IID_HEADER_DONE   0x0DU
#define UART_INTSTA_IID_RSP_DONE      0x0EU

#define UART_LIN_SEND_BREAK_MIN      13U
#define UART_LIN_SEND_BREAK_THR      11U


#define UART_LIN_HEADER_DONE_FLG      ((uint32_t)1U << 14U)
#define UART_LIN_RSP_DONE_FLAG        ((uint32_t)1U << 15U)
#define UART_LIN_TO_ERR                ((uint32_t)1U << 13U)
#define UART_LIN_CHECKSUM_ERR         ((uint32_t)1U << 12U)
#define UART_LIN_PID_ERR               ((uint32_t)1U << 11U)
#define UART_LIN_SYNC_FIELD_ERR       ((uint32_t)1U << 10U)
#define UART_LIN_ASYNC_INT_FLAG       ((uint32_t)1U << 9U)
     
#define UART_LSI_OE       (1U << 1U)
#define UART_LSI_PE       (1U << 2U)
#define UART_LSI_FE       (1U << 3U)
#define UART_LSI_BI       (1U << 4U)
#define UART_LSI_RFE      (1U << 7U)

#define UART_LIN_HEADER_DONE_INT_FLAG     (UART_LIN_HEADER_DONE_FLG | \
                                           UART_LIN_SYNC_FIELD_ERR | \
                                           UART_LIN_PID_ERR| \
                                           UART_LIN_TO_ERR)
  
#define UART_LIN_RSP_DONE_INT_FLAG       (UART_LIN_RSP_DONE_FLAG | \
                                          UART_LIN_CHECKSUM_ERR | \
                                          UART_LIN_TO_ERR)
#define UART_LSI_INT_FLAG                (UART_LSI_OE | \
                                          UART_LSI_PE | \
                                          UART_LSI_FE | \
                                          UART_LSI_BI | \
                                          UART_LSI_RFE)


#define UART_ENABLE_FIFO         1U
#define UART_RESET_RX_FIFO      (1U << 1U)
#define UART_RESET_TX_FIFO      (1U << 2U)

static const uint32_t uartInterruptMaskTable[]=
{
    0x00000001U,       /*!< UART_INT_RBFI */    
    0x00000082U,       /*!< UART_INT_TBEI */    
    0x00000004U,       /*!< UART_INT_LSI */
    0x00000000U,       /*!< UART_INT_BYDET */
    0x00000001U,       /*!< UART_INT_RCVRTO */
    0x00000100U,       /*!< UART_INT_HEADER_DONE */
    0x00000200U,       /*!< UART_INT_RSP_DONE */
    0x00000400U,       /*!< UART_INT_ASYNC */
    0x0000078FU,       /*!< UART_INT_ALL */
};

static const uint32_t uartInterruptStatusTable[]=
{
    UART_INTSTA_IID_RBFI,           /*!< UART_INTSTA_RBFI */
    UART_INTSTA_IID_TBEI,           /*!< UART_INTSTA_TBEI */    
    UART_INTSTA_IID_LSI,            /*!< UART_INTSTA_LSI */
    UART_INTSTA_IID_BYDET,          /*!< UART_INTSTA_BYDET */
    UART_INTSTA_IID_RCVRTO,         /*!< UART_INTSTA_RCVRTO */
    UART_INTSTA_IID_HEADER_DONE,    /*!< UART_INTSTA_HEADER_DONE */
    UART_INTSTA_IID_RSP_DONE        /*!< UART_INTSTA_RSP_DONE */
};

static const uint32_t uartLineStatusTable[]=
{
    0x00000001U,           /*!< UART_LINESTA_DR */
    0x00000002U,           /*!< UART_LINESTA_OE */
    0x00000004U,           /*!< UART_LINESTA_PE */
    0x00000008U,           /*!< UART_LINESTA_FE */
    0x00000010U,           /*!< UART_LINESTA_BI */
    0x00000020U,           /*!< UART_LINESTA_THRE */
    0x00000040U,           /*!< UART_LINESTA_TEMT */
    0x00000080U,           /*!< UART_LINESTA_RFE */
    0x0000009eU,           /*!< UART_LINESTA_TRANS_ERR */
    0x00000100U,           /*!< UART_LINESTA_ADDR_RCVD */
    0x00000200U,           /*!< UART_LINESTA_ASYNC */
    0x00000400U,           /*!< UART_LINESTA_PID_ERR */
    0x00000800U,           /*!< UART_LINESTA_FIELD_ERR */
    0x00001000U,           /*!< UART_LINESTA_CHECKSUM_ERR */
    0x00002000U,           /*!< UART_LINESTA_TO_ERR */
    0x00004000U,           /*!< UART_LINESTA_HEADER_DONE */
    0x00008000U,           /*!< UART_LINESTA_RSP_DONE */
};


/** @}end of group UART_Private_Defines */

/** @defgroup UART_Private_Variables
 *  @{
 */

/**
 *  @brief UART ISR callback function pointer array
 */
static isr_cb_t * uartIsrCb[UART_INSTANCE_NUM][UART_INT_ALL]=
{
    {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
#if (4U == UART_INSTANCE_NUM) 
    {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
#endif
};

/**
 *  @brief UART address array
 */
/*PRQA S 0303,0306 ++*/
static uart_reg_t * const uartRegPtr[UART_INSTANCE_NUM] = 
{
    (uart_reg_t *)UART0_BASE_ADDR,
    (uart_reg_t *)UART1_BASE_ADDR,
    (uart_reg_t *)UART2_BASE_ADDR,
#if (4U == UART_INSTANCE_NUM ) 
    (uart_reg_t *)UART3_BASE_ADDR,
#endif
};

static uart_reg_w_t * const uartRegWPtr[UART_INSTANCE_NUM] = 
{
    (uart_reg_w_t *)UART0_BASE_ADDR,
    (uart_reg_w_t *)UART1_BASE_ADDR,
    (uart_reg_w_t *)UART2_BASE_ADDR,
#if (4U == UART_INSTANCE_NUM ) 
    (uart_reg_w_t *)UART3_BASE_ADDR,
#endif
};
/*PRQA S 0303,0306 --*/

/** @}end of group UART_Private_Variables */

/** @defgroup UART_Global_Variables
 *  @{
 */
/* line status buff */
static uint32_t uartLineStatusBuf[UART_INSTANCE_NUM] = {0U};
/* FIFO Control register buff */
static uint32_t uartFifoControlBuf[UART_INSTANCE_NUM] = {0U};


/** @}end of group UART_Global_Variables */

/** @defgroup UART_Private_FunctionDeclaration
 *  @{
 */
static void UART_IntHandler(UART_ID_t uartId);
void UART0_DriverIRQHandler(void);
void UART1_DriverIRQHandler(void);
void UART2_DriverIRQHandler(void);
#if (4U == UART_INSTANCE_NUM) 
void UART3_DriverIRQHandler(void);
#endif

/** @}end of group UART_Private_FunctionDeclaration */

/** @defgroup UART_Private_Functions
 *  @{
 */

/**
 * @brief      Handle UART interrupt.
 *
 * @param[in]  uartId:  Select the UART port.
 *
 * @return     none
 *
 */
static void UART_IntHandler(UART_ID_t uartId)
{
    uint32_t intId;
    volatile uint32_t dummyData;
    
    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);
    uart_reg_w_t * UARTxw = (uart_reg_w_t *)(uartRegWPtr[uartId]);
        
    uartLineStatusBuf[uartId] = UARTxw->UART_LSR;
     
    if(1U == UARTx->UART_DLH_IER.UART_IER.HEADER_DONE_INT_EN)
    {
        /* LIN header done interrupt */
        if( (UART_LIN_HEADER_DONE_FLG & uartLineStatusBuf[uartId] ) != 0U )
        {
            if(uartIsrCb[uartId][UART_INT_HEADER_DONE] != NULL)
            {
                /* call the callback function */
                uartIsrCb[uartId][UART_INT_HEADER_DONE]();
            }
            /* Disable the interrupt if callback function is not setup */
            else
            {
                UARTx->UART_DLH_IER.UART_IER.HEADER_DONE_INT_EN = 0U;
            }   
        }
    }
    
    if(1U == UARTx->UART_DLH_IER.UART_IER.RSP_DONE_INT_EN)
    {
        /* LIN respnse done interrupt*/
        if(0U != (UART_LIN_RSP_DONE_FLAG  & uartLineStatusBuf[uartId]))
        {
            if(uartIsrCb[uartId][UART_INT_RSP_DONE] != NULL)
            {
                /* call the callback function */
                uartIsrCb[uartId][UART_INT_RSP_DONE]();
            }
            /* Disable the interrupt if callback function is not setup */
            else
            {
                UARTx->UART_DLH_IER.UART_IER.RSP_DONE_INT_EN = 0U;
            }  
        }
    }
    
    if(1U == UARTx->UART_DLH_IER.UART_IER.ELSI)
    {
        /* UART line status interrupt */
        if((UART_LSI_INT_FLAG & uartLineStatusBuf[uartId]) != 0U)
        {
            if(uartIsrCb[uartId][UART_INT_LSI] != NULL)
            {
                /* call the callback function */
                uartIsrCb[uartId][UART_INT_LSI]();
            }
            /* Disable the interrupt if callback function is not setup */
            else
            {
                UARTx->UART_DLH_IER.UART_IER.ELSI = 0U;
            } 
        }
    }
    
    if(1U == UARTx->UART_DLH_IER.UART_IER.ASYNC_INT_EN)
    {
        /* UART_LIN async interrupt */
        if((UART_LIN_ASYNC_INT_FLAG & uartLineStatusBuf[uartId]) != 0x0U )
        {
            if(uartIsrCb[uartId][UART_INT_ASYNC] != NULL)
            {
                /* call the callback function */
                uartIsrCb[uartId][UART_INT_ASYNC]();
            }
            /* Disable the interrupt if callback function is not setup */
            else
            {
                UARTx->UART_DLH_IER.UART_IER.ASYNC_INT_EN = 0U;
            }
        }    
    }
    
    /* Get the BF related pointer */
    intId = UARTx->UART_IIR_FCR.UART_IIR.IID;  
    
    switch(intId)
    {
         /* Transmit holding register empty inerrupt */
        case UART_INTSTA_IID_TBEI:
            if(uartIsrCb[uartId][UART_INT_TBEI] != NULL)
            {
                /* call the callback function */
                uartIsrCb[uartId][UART_INT_TBEI]();
            }
            /* Disable the interrupt if callback function is not setup */
            else
            {
                UARTx->UART_DLH_IER.UART_IER.ETBEI = 0U;
            }
            break;
       
        case UART_INTSTA_IID_RBFI:
            if(uartIsrCb[uartId][UART_INT_RBFI] != NULL)
            {
                /* call the callback function */
                uartIsrCb[uartId][UART_INT_RBFI]();
            }
            /* Disable the interrupt if callback function is not setup */
            else
            {
                UARTx->UART_DLH_IER.UART_IER.ERBFI = 0U;
            }
            break;

        /* Busy detect indication */
        case UART_INTSTA_IID_BYDET:
            /* Clear it by reading the UART status register */
            dummyData = UARTxw->UART_USR;
            if(uartIsrCb[uartId][UART_INT_BYDET] != NULL)
            {
                /* call the callback function */
                uartIsrCb[uartId][UART_INT_BYDET]();
            }
            /* Disable the interrupt if callback function is not setup */
            else
            {
                UARTx->UART_DLH_IER.UART_IER.ERBFI = 0U;
            }            
            break;
       
        /* Character timeout indication */
        case UART_INTSTA_IID_RCVRTO:
            if(uartIsrCb[uartId][UART_INT_RCVRTO] != NULL)
            {
                /* call the callback function */
                uartIsrCb[uartId][UART_INT_RCVRTO]();
            }
            /* Disable the interrupt if callback function is not setup */
            else
            {
                UARTx->UART_DLH_IER.UART_IER.ERBFI = 0U;
            }
            /* Clear it by reading the UART receive register */
            dummyData = UARTxw ->UART_RBR_THR_DLL.UART_RBR;
            break;

        default:
            /* do nothing  */
            break;
    }              
    
    uartLineStatusBuf[uartId] = 0U;
}
/** @} end of group UART_Private_Functions */

/** @defgroup UART_Public_Functions
 *  @{
 */

/**
 * @brief      install call back function for interrupts 
 *
 * @param[in]  uartId: Select the UART port.
 * @param[in]  intType: select the interrupt
 * @param[in]  cbFun: pointer to callback function
 *
 * @return     none
 */
void UART_InstallCallBackFunc(UART_ID_t uartId, UART_Int_t intType,
                              isr_cb_t * cbFun)
{
    uartIsrCb[uartId][intType] = cbFun;
}

/**
 * @brief      Get line status buffer in interrupt call back functions. The line 
 *              status will be stored into line status buffer in UART_IRQHandler.
 *            If the call back functions which are installed through () 
 *            UART_InstallCallBackFunc() needs to get the line status, please 
 *            use this function instead of UART_GetAllLineStatus or 
 *            UART_GetLineStatus.
 *
 * @param[in]  uartId: Select the UART port.
 *
 * @return     linestatus
 *
 */
uint32_t UART_GetLineStatusBufForCbf(UART_ID_t uartId)
{        
    return uartLineStatusBuf[uartId];
}

/**
 * @brief      Default initializes the UART. The OSC40M clock frequency is 40MHz.
 *             baudrate:115200, no parity, 8 date bits, 1 stop bit,
 *             disable autoflow.
 *
 * @param[in]  uartId:  Select the UART port.
 *
 * @return     none
 *
 */
void UART_DefaultInit(UART_ID_t uartId)
{
    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);
    uint32_t integerDiv, fractionalDiv;
#if (4U == UART_INSTANCE_NUM)
    CLK_Module_t const clk[] = {CLK_UART0,CLK_UART1,CLK_UART2,CLK_UART3};
#else
    CLK_Module_t const clk[] = {CLK_UART0,CLK_UART1,CLK_UART2};
#endif
    CLK_Module_t uartClkId = clk[uartId];
    uint32_t clkFreq = CLK_GetModuleClkFreq(uartClkId, 40000000U);

    /* Enable DLAB to set baud rate */
    UARTx->UART_LCR.DLAB = 0x01U;
    /* get integer baudrate divisor*/
    integerDiv = clkFreq/(16U * 115200U);

    /* Config the DLL and DLH registers */
    UARTx->UART_RBR_THR_DLL.UART_DLL.DL_L = integerDiv & 0xFFU;
    UARTx->UART_DLH_IER.UART_DLH.DL_H = (integerDiv >> 0x08U) ;

    /* config fractional divisor */
    fractionalDiv = clkFreq%(16U * 115200U);
    fractionalDiv /= 115200U;
    UARTx->UART_FD.FD = fractionalDiv;

    /* Disable DLAB */
    UARTx->UART_LCR.DLAB = 0x0U;
    /* NO PARITY */
    UARTx->UART_LCR.PEN = 0x0U;
    /*set 8 bits data */
    UARTx->UART_LCR.DLS = (uint32_t)UART_DATABITS_8;
    /* Set UART  stop bit */
    UARTx->UART_LCR.STOP = (uint32_t)UART_STOPBITS_1;
    /* disable autoflow */
    UARTx->UART_AFCR.AFCE = (uint32_t)DISABLE;
    UARTx->UART_AFCR.RTS = 0U;
}

/**
 * @brief      Initializes the UART
 *
 * @param[in]  uartId:  Select the UART port.
 * @param[in]  uartCfg:  Pointer to a UART configuration structure
 *
 * @return     none
 *
 */
void UART_Init(UART_ID_t uartId, const UART_Config_t* uartCfg)
{
    uint32_t integerDiv, fractionalDiv;
#if (4U == UART_INSTANCE_NUM)
    CLK_Module_t clk[] = {CLK_UART0,CLK_UART1,CLK_UART2,CLK_UART3};
#else
    CLK_Module_t clk[] = {CLK_UART0,CLK_UART1,CLK_UART2};
#endif
    CLK_Module_t uartClkId = clk[uartId];
    uint32_t clkFreq = CLK_GetModuleClkFreq(uartClkId, uartCfg->oscFreq);
    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);

  /************Configure the Baud Rate*********************************/

    /* Enable DLAB to set baud rate */
    UARTx->UART_LCR.DLAB = 0x01U;

    /* get integer baudrate divisor*/
    integerDiv = clkFreq/(16U * uartCfg->baudRate);

    /* Config the DLL and DLH registers */
    UARTx->UART_RBR_THR_DLL.UART_DLL.DL_L = integerDiv & 0xFFU;
    UARTx->UART_DLH_IER.UART_DLH.DL_H = (integerDiv >> 0x08U)& 0xFFU;

    /* calculate fractional divisor
       divisor = clkFreq/(16*baudrate) = BRDI +BRDF
       FD = BRDF*2^4 = 16* BRDF
       BRDF = clkFreq%(16*baudrate)/(16*baudrate)
       FD = clkFreq%(16*baudrate)*16/(16*baudrate)
          = clkFreq%(16*baudrate)/baudrate  */
    fractionalDiv = clkFreq%(16U * uartCfg->baudRate);
    fractionalDiv /= uartCfg->baudRate;
    UARTx->UART_FD.FD = fractionalDiv;

    /* Disable DLAB */
    UARTx->UART_LCR.DLAB = 0x0U;

    if(uartCfg->parity == UART_PARITY_NONE)
    {
        UARTx->UART_LCR.PEN = 0x0U;
    }
    else if(uartCfg->parity == UART_PARITY_ODD)
    {
        UARTx->UART_LCR.PEN = 0x1U;
        UARTx->UART_LCR.EPS = 0U;
    }
    else
    {
        UARTx->UART_LCR.PEN = 0x1U;
        UARTx->UART_LCR.EPS = 1U;
    }

    /* Set UART Data Length and stop bit */
    if(uartCfg->dataBits == UART_DATABITS_9)
    {
       UARTx->UART_LCR_EXT.DLS_E = 0x1U;
    }
    else
    {
        UARTx->UART_LCR.DLS = (uint32_t)uartCfg->dataBits ;
    }
    /* Set UART  stop bit */
    UARTx->UART_LCR.STOP = (uint32_t)uartCfg->stopBits;

    /***********Configure auto flow  *******************/
    UARTx->UART_AFCR.AFCE = (uint32_t)uartCfg->autoFlowControl;

    if(uartCfg->autoFlowControl == ENABLE)
    {
        UARTx->UART_AFCR.RTS = 1U;
    }
    else
    {
        UARTx->UART_AFCR.RTS = 0U;
    }

}

/**
 * @brief      Wait for UART busy bit clear.
 *
 * @param[in]  uartId:  UART peripheral selected.
 * @param[in]  cycle: The software cycles to be waited. User decides how many 
 *             cycles need to be waited.
 *
 * @return ResultStatus_t 
 *                       - SUCC: busy bit is cleared
 *                       - ERR: UART is still busy
 *
 */
ResultStatus_t UART_WaitBusyClear(UART_ID_t uartId, uint32_t cycle)
{
    ResultStatus_t ret = ERR;
    volatile uint32_t localcnt = 0;
    
    while(localcnt < cycle)
    {
        if(RESET == UART_GetBusyStatus(uartId))
        {
            ret = SUCC;
            break;
        }
        
        localcnt = localcnt + 1U;
    }   
    
    return ret;
}

/**
 * @brief      Set UART rts enable 
 *
 * @param[in]  uartId:  UART peripheral selected.
 * @param[in]  newState: Enable/Disable function state
 *
 * @return     none
 *
 */
void UART_RtsEnable(UART_ID_t uartId, ControlState_t newState)
{
    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);

    UARTx->UART_AFCR.RTS = (uint32_t)newState;

}

/**
 * @brief      Set UART loopback mode
 *
 * @param[in]  uartId:  UART peripheral selected.
 * @param[in]  newState: Enable/Disable function state
 *
 * @return     none
 *
 */
void UART_SetLoopBackMode(UART_ID_t uartId, ControlState_t newState)
{
    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);

    UARTx->UART_AFCR.LB = (uint32_t)newState;

}

/**
 * @brief      Send break function, user can choose the length of break,
 *             the length should not be less than eleven
 *
 * @param[in]  uartId:  UART peripheral selected.
 * @param[in]  len:     the length of break
 *
 * @return     
 *             - SUCC : break is sent
 *             - ERR : break length is invalid
 *
 */
ResultStatus_t UART_SendBreak(UART_ID_t uartId, uint8_t len)
{
    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);
    ResultStatus_t ret = SUCC;
    if(len < 0x0BU)
    {
        ret =  ERR;
    }
    else
    {
        UARTx->UART_LCR.LBKM = (uint32_t)len - 0xBU;
        UARTx->UART_LCR.LBKEN = 1U;
        /* send break characters */
        UARTx->UART_LCR.BC = 1;
    }

    return ret;    
}

/**
 * @brief      Receive one byte data from the UART peripheral
 *
 * @param[in]  uartId:  Select the UART port.
 *
 * @return     The received data
 *
 */
uint8_t UART_ReceiveByte(UART_ID_t uartId)
{
    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);

    /* Receive data */
    return (uint8_t)(UARTx->UART_RBR_THR_DLL.UART_RBR.RBR_LSB);
}

/**
 * @brief      Read received bytes from the RX FIFO
 * @param[in]  uartId:  Select the UART port, should be UART0_ID, UART1_ID,
 *                      UART2_ID, UART3_ID.
 * @param[in]  length:  the number of bytes to be read. When call this function,
 *                      the user needs to make sure that the "length" is not
 *                      greater than the number of bytes that is available in
 *                      RX FIFO
 * @param[out]  data:  points to the memory where the data to be stored
 *.
 * @return     The received data
 */
void UART_ReceiveBytes(UART_ID_t uartId,uint32_t length, uint8_t data[])
{
    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);

    for(uint32_t cnt = 0U; cnt <length; cnt++)
    {
        data[cnt] = (uint8_t)UARTx->UART_RBR_THR_DLL.UART_RBR.RBR_LSB;
    }
}

/**
 * @brief      Empty the RX FIFO. This function reads received data until RX
 *             FIFO is empty
 * @param[in]  uartId:  Select the UART port.
 *
 * @return     None
 */
void UART_EmptyRxFifo(UART_ID_t uartId)
{
    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);

    volatile uint8_t dummyData;

    while(SET == UART_GetLineStatus(uartId, UART_LINESTA_DR))
    {
        dummyData = (uint8_t)UARTx->UART_RBR_THR_DLL.UART_RBR.RBR_LSB;
    }
}

/**
 * @brief      Set receive 9 bits data mode 0
 *
 * @param[in]  uartId: Select the UART port.
 *
 * @return     none
 *
 */
void UART_9BitsM0Rx(UART_ID_t uartId)
{    
    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);
    
    if((uint32_t)SET == UARTx->UART_LCR_EXT.DLS_E)
    {   /* Receive mode 0 */
        UARTx->UART_LCR_EXT.ADDR_MATCH = 0x0U;        
    }
    else
    {
        /* none */
    }

}

/**
 * @brief      Program the address of  receive 9 bits data, mode 1
 *
 * @param[in]  uartId: Select the UART port.
 *
 * @return     none
 *
 */
void UART_9BitsM1SetAddr(UART_ID_t uartId, uint8_t addr)
{
    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);
   
    /* set address in rar */
    UARTx->UART_RAR.RAR = addr;
}

/**
 * @brief      Select 9 bits hardware receive mode 1
 *
 * @param[in]  uartId: Select the UART port.
 *
 * @return     none
 *
 */
void UART_9BitsHWRecvEnable(UART_ID_t uartId)
{
    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);

    UARTx->UART_LCR_EXT.ADDR_MATCH = 0x1U;
}

/**
 * @brief      Receive address from the UART peripheral, mode 1
 *
 * @param[in]  uartId: Select the UART port.
 *
 * @return     the received address
 *
 */
/* receive address */
uint16_t UART_9BitsM1RxAddr(UART_ID_t uartId)
{
    uint16_t ret;

    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);
    uart_reg_w_t * UARTxw = (uart_reg_w_t *)(uartRegWPtr[uartId]);

    uint8_t rxAddr;
    uint32_t regData;
    
    regData = (uint32_t)UARTxw->UART_RBR_THR_DLL.UART_RBR;
    rxAddr = (uint8_t)UARTx->UART_RAR.RAR;
    
    if(0x100U == (regData & 0x100U))
    {
        if(rxAddr == (regData & 0xFFU))
        {
            ret = (uint16_t)(regData & 0x1FFU);
        }
        else
        {
            ret = (uint16_t)ERR;
        }
    }
    else
    {
        ret = (uint16_t)ERR;
    }

    return ret;
}

/**
 * @brief      Receive one byte data from the UART peripheral, mode 1
 *
 * @param[in]  uartId:  Select the UART port.
 *
 * @return     The received data
 *
 */
uint16_t UART_9BitsM1RxData(UART_ID_t uartId)
{
    uint16_t ret;
    uint32_t regData;
    
    uart_reg_w_t * UARTxw = (uart_reg_w_t *)(uartRegWPtr[uartId]);
    regData = (uint32_t)UARTxw->UART_RBR_THR_DLL.UART_RBR;
    
    if(0U == (regData & 0x100U))
    {
        ret = (uint16_t)(regData & 0xFFU);
    }
    else
    {
        ret = 0x1FF;
    }

    return ret;
}

/**
 * @brief      Send one byte data to the UART peripheral,5/6/7/8 bits
 *
 * @param[in]  uartId:  Select the UART port.
 * @param[in]  data:  The data to be sent
 *
 * @return     none
 *
 */
void UART_SendByte(UART_ID_t uartId, uint8_t data)
{
    uart_reg_w_t * UARTxw = (uart_reg_w_t *)(uartRegWPtr[uartId]);
    /* Send data */
    UARTxw->UART_RBR_THR_DLL.UART_THR = (uint32_t)data;
}

/**
 * @brief      Program the transmit target address, 9bits, mode 0
 *
 * @param[in]  uartId:  Select the UART port.
 * @param[in]  addr:  program the address
 *
 * @return     none
 *
 */
void UART_9BitsM0SetAddr(UART_ID_t uartId, uint8_t addr)
{
    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);
    /* transmit mode 0 */
    if(0x1U == UARTx->UART_LCR_EXT.DLS_E)
    {
        UARTx->UART_LCR_EXT.TRANSMIST_MODE = 0x0U;
        UARTx->UART_TAR.TAR = (uint32_t)addr;
    }
}

/**
 * @brief      Set send address bit, mode 0
 *
 * @param[in]  uartId:  Select the UART port.
 *
 * @return     none
 *
 */
void UART_9BitsM0SendAddr(UART_ID_t uartId)
{
    /* transmit mode 0 */
    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);
                
    UARTx->UART_LCR_EXT.SEND_ADDR = 0x1U;    
}

/**
 * @brief      Send 9 bits data to the UART peripheral, mode 1
 *
 * @param[in]  uartId:  Select the UART port.
 * @param[in]  data:  The data to be send
 *
 * @return     none
 *
 */
void UART_9BitsM1TxData(UART_ID_t uartId, uint16_t data)
{
    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);
    uart_reg_w_t * UARTxw = (uart_reg_w_t *)(uartRegWPtr[uartId]);
    /* transmit mode 1 */
    if((uint32_t)SET == UARTx->UART_LCR_EXT.DLS_E)
    {
        UARTx->UART_LCR_EXT.TRANSMIST_MODE = 0x1U;
        /* Send data */
        UARTxw->UART_RBR_THR_DLL.UART_THR = ((uint32_t)data) & 0x1FFU;
    }
}

/**
 * @brief      Config UART FIFO function
 *
 * @param[in]  uartId:  Select the UART port.
 * @param[in]  fifoCfg:  Pointer to a UART_FIFO_CFG_t Structure
 *
 * @return     none
 *
 */
void UART_FIFOConfig(UART_ID_t uartId, const UART_FIFOConfig_t * fifoCfg)
{
    uint32_t regValue;
    uart_reg_w_t * UARTxw = (uart_reg_w_t *)(uartRegWPtr[uartId]);

    regValue =((((uint32_t)(fifoCfg->fifoRt) & 0x03U) << 6U)
                    | (((uint32_t)(fifoCfg->fifoTet) & 0x03U) << 4U)
                    | (((uint32_t)(fifoCfg->txFifoReset) & 0x01U) << 2U)
                    | (((uint32_t)(fifoCfg->rxFifoReset) & 0x01U) << 1U)
                    | ((uint32_t)(fifoCfg->fifoEnable) & 0x01U));
    
    UARTxw->UART_IIR_FCR.UART_FCR = regValue;
    
    uartFifoControlBuf[uartId] = regValue; 
    uartFifoControlBuf[uartId] &= (~(UART_RESET_RX_FIFO | UART_RESET_TX_FIFO));

}

/**
 * @brief      get UART FIFO status
 *
 * @param[in]  uartId:  Select the UART port.
 *
 * @return     status
 *
 */
ControlState_t UART_GetfifoStatus(UART_ID_t uartId)
{
    ControlState_t ret;

    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);

    if(3U == UARTx->UART_IIR_FCR.UART_IIR.FIFOSE)
    {
        ret = ENABLE;
    }
    else
    {
        ret = DISABLE;
    }

    return ret;
}

/**
 * @brief      Reset uart receive fifo
 *
 * @param[in]  uartId:  Select the UART port.
 *
 * @return     none
 *
 */
void UART_ResetRxFifo(UART_ID_t uartId)
{
    uart_reg_w_t * UARTxw = (uart_reg_w_t *)(uartRegWPtr[uartId]);
    
    uartFifoControlBuf[uartId] |= UART_RESET_RX_FIFO;

    UARTxw->UART_IIR_FCR.UART_FCR = uartFifoControlBuf[uartId];
    
    uartFifoControlBuf[uartId] &= (~UART_RESET_RX_FIFO);
}

/**
 * @brief      Reset uart transmit fifo
 *
 * @param[in]  uartId:  Select the UART port.
 *
 * @return     none
 *
 */
void UART_ResetTxFifo(UART_ID_t uartId)
{
    uart_reg_w_t * UARTxw = (uart_reg_w_t *)(uartRegWPtr[uartId]);
    
    uartFifoControlBuf[uartId] |= UART_RESET_TX_FIFO;    
    UARTxw->UART_IIR_FCR.UART_FCR = uartFifoControlBuf[uartId];
    
    uartFifoControlBuf[uartId] &= (~UART_RESET_TX_FIFO);
}

/**
 * @brief      Enable/Disable debug mode. If enabled, hardware will not clean 
 *             the recevier fifo automaticlly
 *
 * @param[in]  uartId:  Select the UART port.
 *
 * @param[in]  Cmd: ENABLE/DISABLE
 *
 * @return     none
 *
 */
void UART_DebugCmd(UART_ID_t uartId, ControlState_t Cmd)
{
    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);
    
    UARTx->UART_LCR.DEBUG_EN = (uint32_t)Cmd;
}

/**
 * @brief      Idle detect config
 *
 * @param[in]  uartId:  Select the UART port.
 *
 * @param[in]  config: config idle detect 
 *
 * @return     none
 *
 */
void UART_IdleDetectConfig(UART_ID_t uartId,UART_IdleDetectConfig_t *config)
{
    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);
        
    UARTx->UART_LCR.IDLE_DET_LENGTH = (uint32_t)config->len;
    UARTx->UART_LCR.IDLE_DET_EN = (uint32_t)config->Cmd;
}

/**
 * @brief      Config UART in LIN mode
 * @param[in]  uartId:  Select the UART port.
 *                      
 * @param[in]  config:  points to the configuration of LIN mode
 * @return     none
 */
void UART_LinConfig(UART_ID_t uartId, const UART_LinConfig_t *config)
{
    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);
    uart_reg_w_t * UARTxw = (uart_reg_w_t *)(uartRegWPtr[uartId]);
    
    uint32_t integerDiv, fractionalDiv;
#if (4U == UART_INSTANCE_NUM)
    CLK_Module_t clk[] = {CLK_UART0,CLK_UART1,CLK_UART2,CLK_UART3};
#else
    CLK_Module_t clk[] = {CLK_UART0,CLK_UART1,CLK_UART2};
#endif
    CLK_Module_t uartClkId = clk[uartId];
    uint32_t tmp;

    /* Enable DLAB to set baud rate */
    UARTx->UART_LCR.DLAB = 0x01U;
    tmp = CLK_GetModuleClkFreq(uartClkId, config->oscFreq);
    
    if(1U == (uint32_t)config->autoSyncEn)
    {
        /* get baudrate divisor*/        
        integerDiv = (10U * tmp/(16U * config->baudRate) )+ 5U;
        integerDiv = integerDiv / 10U;

        /* Config the DLL and DLH registers */
        UARTx->UART_RBR_THR_DLL.UART_DLL.DL_L = integerDiv & 0xFFU;
        UARTx->UART_DLH_IER.UART_DLH.DL_H = (integerDiv >> 0x08U)& 0xFFU;

        UARTx->UART_FD.FD = 0U;
    }
    else
    {
        /* get baudrate divisor*/
        integerDiv = tmp/(16U * config->baudRate);

        /* Config the DLL and DLH registers */
        UARTx->UART_RBR_THR_DLL.UART_DLL.DL_L = integerDiv & 0xFFU;
        UARTx->UART_DLH_IER.UART_DLH.DL_H = (integerDiv >> 0x08U)& 0xFFU;

     /* calculate fractional divisor 
      *  divisor = clkFreq/(16*baudrate) = BRDI +BRDF 
      *  FD = BRDF*2^4 = 16* BRDF 
      *  BRDF = clkFreq%(16*baudrate)/(16*baudrate) 
      *  FD = clkFreq%(16*baudrate)*16/(16*baudrate) 
      *     = clkFreq%(16*baudrate)/baudrate  
      */
        fractionalDiv = tmp%(16U * config->baudRate);
        fractionalDiv /= config->baudRate;
        UARTx->UART_FD.FD = fractionalDiv;
    }
    /* Disable DLAB */
    UARTx->UART_LCR.DLAB = 0x0U;
    /* no parity */
    UARTx->UART_LCR.PEN = 0x0U;

    /* 8 bits */
    UARTx->UART_LCR.DLS = 3U ;

    /* 1 stop bit */
    UARTx->UART_LCR.STOP = 0U;

    UARTx->UART_AFCR.RTS = 0U;

    /* LIN mode */
    UARTx->UART_LIN_CTL.LIN_MODE = 1U;
    UARTx->UART_LIN_CTL.MASTER_MODE = (uint32_t)config->mode;

    /* auto sync */
    UARTx->UART_LCR.AUTO_SYNC_EN = (uint32_t)config->autoSyncEn;

    /* enable and clear FIFO in LIN mode */
    uartFifoControlBuf[uartId] |= UART_ENABLE_FIFO;
    
    UARTxw->UART_IIR_FCR.UART_FCR = uartFifoControlBuf[uartId];
    
    uartFifoControlBuf[uartId] |= ( UART_RESET_TX_FIFO | UART_RESET_RX_FIFO);
    
    UARTxw->UART_IIR_FCR.UART_FCR = uartFifoControlBuf[uartId];
    
    uartFifoControlBuf[uartId] &= ( ~ (UART_RESET_TX_FIFO | UART_RESET_RX_FIFO));

}

/**
 * @brief      Set UART in LIN mode as a LIN master and start to send the header
 * @param[in]  uartId:  Select the UART port.
 *                     
 * @param[in]  header:  points to the header to be sent
 * @return     status
 *             - SUCC : header is sent
 *             - ERR : header is not sent due to UART is busy
 */
ResultStatus_t UART_LinSendHeader(UART_ID_t uartId, 
                                  const UART_LinHeader_t *header)
{
    ResultStatus_t ret;
    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);
    
    uint32_t breakLen;
    uint32_t rsp_op_start = UARTx->UART_LIN_CTL.RSP_OP_START;
    uint32_t header_op_start = UARTx->UART_LIN_CTL.HEADER_OP_START;
    /* check if UART is busy */
    if( (rsp_op_start != 0U) || (header_op_start != 0U) )
    {
        ret = ERR;
    }
    else
    {
        UARTx->UART_LIN_DEL_LENGTH.LIN_DEL_LENGTH = header->deleLen - 1U;
        UARTx->UART_LIN_PID_VALUE.PID = header->id;
        breakLen = ((header->breakLen) >= UART_LIN_SEND_BREAK_MIN)?(
                           (header->breakLen) - UART_LIN_SEND_BREAK_THR):
                           (UART_LIN_SEND_BREAK_MIN - UART_LIN_SEND_BREAK_THR);
                           
        if(breakLen != UARTx->UART_LCR.LBKM )
        {
            UARTx->UART_LCR.LBKM = breakLen;
        }
        else
        {
            /* Nothing to do */
        }
        UARTx->UART_LIN_CTL.MASTER_MODE = 1U;
        /* start to send */
        UARTx->UART_LIN_CTL.HEADER_OP_START = 1U;

        ret = SUCC;
    }

    return ret;
}

/**
 * @brief       This function stops receiving/sending header/response of LIN. 
 *
 * @param[in]   uartId:  Select the UART port.
 *                     
 * @return     none
 */
void UART_LinStopTransmission(UART_ID_t uartId)
{
    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);
    
    UARTx->UART_LIN_CTL.RSP_OP_START = 0U;
    
    UARTx->UART_LIN_CTL.HEADER_OP_START = 0U;
    
}

/**
 * @brief       If LIN is sending/receiving header/response
 *                this function returns SET, otherwise, return RESET.
 *
 * @param[in]   uartId:  Select the UART port.
 *                     
 * @return     SET/RESET
 */
FlagStatus_t UART_LinGetTransmissionStatus(UART_ID_t uartId)
{
    FlagStatus_t ret = RESET;
    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);
    
    uint32_t rsp_op_start = UARTx->UART_LIN_CTL.RSP_OP_START;
    uint32_t header_op_start = UARTx->UART_LIN_CTL.HEADER_OP_START;
    /* check if UART is busy */
    if( (rsp_op_start != 0U) || (header_op_start != 0U) )
    {
        ret = SET;
    }
    else
    {
        /* nothing */
    }
    
    return ret;
}

/**
 * @brief      Set UART in LIN mode as a LIN slave and start to receive a header.
 *             FIFO is disabled before it starts to receive a header
 *
 * @param[in]  uartId:  Select the UART port.
 * @return     
 *            - SUCC : it starts to receive header
 *            - ERR : it dose not start to receive header due to UART is busy
 */
ResultStatus_t UART_LinStartReceiveHeader(UART_ID_t uartId)
{
    ResultStatus_t ret;
    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);
    uart_reg_w_t * UARTxw = (uart_reg_w_t *)(uartRegWPtr[uartId]);
    
    uint32_t rsp_op_start = UARTx->UART_LIN_CTL.RSP_OP_START;
    uint32_t header_op_start = UARTx->UART_LIN_CTL.HEADER_OP_START;
    /* check if UART is busy */
    if( (rsp_op_start != 0U) || (header_op_start != 0U) )
    {
        ret = ERR;
    }
    else
    {
        /* reset rx fifo then disable fifo */
        uartFifoControlBuf[uartId] |= UART_RESET_RX_FIFO;
        UARTxw->UART_IIR_FCR.UART_FCR = uartFifoControlBuf[uartId];        
        uartFifoControlBuf[uartId] &= (~UART_RESET_RX_FIFO);
        
        uartFifoControlBuf[uartId] &= ~UART_ENABLE_FIFO;            
        UARTxw->UART_IIR_FCR.UART_FCR = uartFifoControlBuf[uartId];

        UARTx->UART_LIN_CTL.MASTER_MODE = 0U;
        /* start to receive */
        UARTx->UART_LIN_CTL.HEADER_OP_START = 1U;

        ret = SUCC;
    }

    return ret;
}

/**
 * @brief      Read the 6-bit ID(exclude parity bits) of header
 * @param[in]  uartId:  Select the UART port.
 *                     
 * @return     ID
 */
uint32_t UART_LinGetId(UART_ID_t uartId)
{
    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);

    return UARTx->UART_LIN_PID_VALUE.PID;
}

/**
 * @brief      start to send a response
 * @param[in]  uartId:  Select the UART port.
 *                    
 * @param[in]  rsp:  Points to reponse structure to be sent.
 * @return
 *             - SUCC : response is sent
 *             - ERR : resoponse is not sent due to UART is busy
 */
ResultStatus_t UART_LinSendResponse(UART_ID_t uartId,
                                    const UART_LinResponse_t *rsp)
{
    ResultStatus_t ret;
    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);
    uart_reg_w_t * UARTxw = (uart_reg_w_t *)(uartRegWPtr[uartId]);

    uint32_t rsp_op_start = UARTx->UART_LIN_CTL.RSP_OP_START;
    uint32_t header_op_start = UARTx->UART_LIN_CTL.HEADER_OP_START;
    if((rsp->len > 8U) || ( (rsp_op_start != 0U)|| (header_op_start != 0U)))
    {
        ret = ERR;
    }
    else
    {
        /* enable fifo  */
        uartFifoControlBuf[uartId] |= UART_ENABLE_FIFO;
        UARTxw->UART_IIR_FCR.UART_FCR = uartFifoControlBuf[uartId];
        
        UARTx->UART_LIN_RSP_LENGTH.RSP_LENGTH = (uint32_t)rsp->len;
        UARTx->UART_LIN_CHECKSUM.CHECKSUM_TYPE = (uint32_t)rsp->checkType;

        for(uint32_t cnt = 0U; cnt < rsp->len; cnt++)
        {
            UARTxw->UART_RBR_THR_DLL.UART_THR = (uint32_t)rsp->data[cnt];
        }

        UARTx->UART_LIN_CTL.RSP_DIR = 1U;

        UARTx->UART_LIN_CTL.RSP_OP_START = 1U;

        ret = SUCC;
    }

    return ret;
}

/**
 * @brief      Start to receive a response
 * @param[in]  uartId:  Select the UART port.
 *                    
 * @param[in]  check:  Checksum type.
 * @param[in]  len:  Response length, the maximun value is 8 bytes in a frame.
 * @return
 *            - SUCC : it starts to receive response
 *            - ERR : it dose not start to receive response due to UART is busy
 */
ResultStatus_t UART_LinStartReceiveResponse(UART_ID_t uartId,
                                            UART_LinCheckSum_t check,
                                            uint32_t len)
{
    ResultStatus_t ret;
    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);
    uart_reg_w_t * UARTxw = (uart_reg_w_t *)(uartRegWPtr[uartId]);
    
    uint32_t rsp_op_start = UARTx->UART_LIN_CTL.RSP_OP_START;
    uint32_t header_op_start = UARTx->UART_LIN_CTL.HEADER_OP_START;

    /* check if UART is busy */
    if((rsp_op_start != 0U) || (header_op_start !=0U))
    {
        ret = ERR;
    }
    else
    {
        /* enable fifo and reset rx fifo */
        uartFifoControlBuf[uartId] |= UART_ENABLE_FIFO;
        UARTxw->UART_IIR_FCR.UART_FCR = uartFifoControlBuf[uartId];
        
        uartFifoControlBuf[uartId] |= UART_RESET_RX_FIFO;
        UARTxw->UART_IIR_FCR.UART_FCR = uartFifoControlBuf[uartId];
        uartFifoControlBuf[uartId] &= (~UART_RESET_RX_FIFO);
        
        UARTx->UART_LIN_RSP_LENGTH.RSP_LENGTH = len;
        UARTx->UART_LIN_CHECKSUM.CHECKSUM_TYPE = (uint32_t)check;

        UARTx->UART_LIN_CTL.RSP_DIR = 0U;

        UARTx->UART_LIN_CTL.RSP_OP_START = 1U;

        ret = SUCC;
    }
    return ret;
}

/**
 * @brief      read a response. if a reponse is received, this function can be
 *             called to get the data of response. This function is called
 *             after UART_LinStartReceiveResponse() and UART_INTSTA_RSP_DONE
 *             status is set.
 * @param[in]  uartId:  Select the UART port.
 * @param[in]  len:  response length to be read.
 * @param[out]  data:  points to the memory where the response data to be stored.
 *                    the memory size must not be smaller than len
 * @return     none
 */
void UART_LinReadResponse(UART_ID_t uartId, uint32_t len, uint8_t data[])
{
    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);

    for(uint32_t cnt = 0U; cnt < len; cnt++)
    {
        data[cnt] = (uint8_t)UARTx->UART_RBR_THR_DLL.UART_RBR.RBR_LSB;
    }
}

/**
 * @brief      Get current value of Line Status register
 *
 * @param[in]  uartId:  Select the UART port.
 * @param[in]  lineStatus:
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
 *                       - UART_LINESTA_ASYNC
 *                       - UART_LINESTA_FIELD_ERR
 *                       - UART_LINESTA_PID_ERR
 *                       - UART_LINESTA_CHECKSUM_ERR
 *                       - UART_LINESTA_TO_ERR
 *                       - UART_LINESTA_HEADER_DONE
 *                       - UART_LINESTA_RSP_DONE
 * 
 * @note       This function returns only one line status. However,  once call 
 *             this function, all line status will be cleared. If user
 *             needs to read more than one line status, it is suggested to use 
 *             UART_GetAllLineStatus() to get all line status and handle them 
 *             one by one.
 * @return     The state value of UART Line Status register
 *
 */
FlagStatus_t UART_GetLineStatus(UART_ID_t uartId, UART_LineStatus_t lineStatus)
{
    FlagStatus_t bitStatus;
    uart_reg_w_t * UARTxw = (uart_reg_w_t *)(uartRegWPtr[uartId]);
    
    bitStatus = (((UARTxw->UART_LSR & uartLineStatusTable[lineStatus]) != 0U)
                  ? SET : RESET);

    return bitStatus;
}

/**
 * @brief      Get all Line Status 
 *
 * @param[in]  uartId:  Select the UART port.
 * 
 * @note       Once call the function, line status will be cleared
 *
 * @return     The state value of UART Line Status register
 *
 */
uint32_t UART_GetAllLineStatus(UART_ID_t uartId)
{
    uart_reg_w_t * UARTxw = (uart_reg_w_t *)(uartRegWPtr[uartId]);
    
    return ((uint32_t)UARTxw->UART_LSR & 0xFFFFU);
}

/**
 * @brief      Get busy status
 *
 * @param[in]  uartId:  Select the UART port.
 *
 * @return     The state value of busy Status
 *
 */
FlagStatus_t UART_GetBusyStatus(UART_ID_t uartId)
{
    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);

    return (UARTx->UART_USR.BUSY != 0U) ? SET : RESET;
}

/**
 * @brief      Get current UART interrupt status except async status
 *
 * @param[in]  uartId:  Select the UART port.
 * @param[in]  intType: select interrupt
 *
 * @note       If user needs to get async status, user can use UART_GetLineStatus 
 *              function.
 *
 * @return     The state value of UART Status register
 */
IntStatus_t UART_GetIntStatus(UART_ID_t uartId, UART_Int_t intType)
{
    IntStatus_t bitStatus ;
    uart_reg_t * UARTx = (uart_reg_t *)(uartRegPtr[uartId]);
    
     bitStatus = ((UARTx->UART_IIR_FCR.UART_IIR.IID ==
                      uartInterruptStatusTable[intType] ) ? SET : RESET);      

    return bitStatus;
}

/**
 * @brief      Mask/Unmask the UART interrupt, UART_INT_BYDET cannot be masked,
 *             UART_INT_RCVRTO is only effective when fifo enable.
 *
 * @param[in]  uartId:  Select the UART port.
 * @param[in]  intType:  Specifies the interrupt type
 * @param[in]  intMask:  Enable/Disable Specified interrupt type
 *
 * @return     none
 *
 */
void UART_IntMask(UART_ID_t uartId, UART_Int_t intType, IntMask_t intMask)
{
    uart_reg_w_t * UARTxw = (uart_reg_w_t *)(uartRegWPtr[uartId]);

    if(intMask == UNMASK)
    {
        UARTxw->UART_DLH_IER.UART_IER  |= (uartInterruptMaskTable[intType]);
    }
    else
    {
        UARTxw->UART_DLH_IER.UART_IER &= (~(uartInterruptMaskTable[intType]));
    }
}

/**
 * @brief  UART0 interrupt function
 *
 * @param  none
 *
 * @return none
 *
 */
void UART0_DriverIRQHandler(void)
{
    UART_IntHandler(UART0_ID);
}
/**
 * @brief  UART1 interrupt function
 *
 * @param  none
 *
 * @return none
 *
 */
void UART1_DriverIRQHandler(void)
{
    UART_IntHandler(UART1_ID);
}

/**
 * @brief  UART2 interrupt function
 *
 * @param  none
 *
 * @return none
 *
 */
void UART2_DriverIRQHandler(void)
{
    UART_IntHandler(UART2_ID);
}

#if (4U == UART_INSTANCE_NUM)
/**
 * @brief  UART3 interrupt function
 *
 * @param  none
 *
 * @return none
 *
 */
void UART3_DriverIRQHandler(void)
{
    UART_IntHandler(UART3_ID);
}
#endif 

/** @}end of group UART_Public_Functions */

/** @}end of group UART_definitions */

/** @}end of group Z20K11X_Peripheral_Driver */
