/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
#include "USART.h"

ST_USART_CONTROL USART_Ctrl_1 = {
    .rxdata_maxlength = RESCEIVE_DATA_LENGTH,
    .txdata_maxlength = TRANSMISSION_DATA_LENGTH,
};

ST_USART_CONTROL USART_Ctrl_2 = {
    .rxdata_maxlength = RESCEIVE_DATA_LENGTH,
    .txdata_maxlength = TRANSMISSION_DATA_LENGTH,
};

Q08U_ Cal_CRC8(const Q08U_ data)
{
    Q08U_ i, crc;
    crc = data;
    /* 数据往左移了8位，需要计算8次 */
    for (i = 8; i > 0; i--) {
        /* 判断最高位是否为1 */
        if(crc & 0x80)
        {
        /* 最高位为1，不需要异或，往左移一位，然后与0x2f异或 */
        /* 0x12f(多项式：x8 + x5 + x3 + x2 + x + 1,  100101111)，最高位不需要异或，直接去掉 */
            crc = (crc << 1) ^ 0x2f;
        } 
        else
        {
            /* 最高位为0时，不需要异或，整体数据往左移一位 */
            crc = (crc << 1);
        }
    }
    return crc;
}

void USART_Get_Resceive_Data_1(void)
{
    ST_USART_CONTROL* pUC = &USART_Ctrl_1;
    
    switch(pUC->USART_Resceive_Flow)
    {
        case USART_STATE_IDLE:
        {
            if(pUC->USART_State.BIT.resceive_enable == 1U)
            {
                if(++pUC->rxdata_cnt > 3U)
                {
                    pUC->rxdata_cnt = 0U;
                    UART_Enable_Rx(UART1);
                    pUC->USART_Resceive_Flow = USART_STATE_RUN;
                }
            }
        }break;
        case USART_STATE_RUN:
        {
            if(pUC->rxdata_length_tmp >= pUC->rxdata_maxlength)
            {
                UART_Disable_Rx(UART1);
                pUC->USART_Resceive_Flow = USART_STATE_ERROR;
            }
            if((pUC->rxdata_length_tmp == pUC->rxdata_length_last)
            && (pUC->rxdata_length_tmp != 0U))
            {
                if(++pUC->rxdata_cnt > 3)
                {
                    pUC->rxdata_cnt = 0;
                    UART_Disable_Rx(UART1);
                    pUC->USART_Resceive_Flow = USART_STATE_END;
                }
            }
            pUC->rxdata_length_last = pUC->rxdata_length_tmp;
        }break;
        case USART_STATE_END:
        {
//            pUC->txdata[0] = pUC->rxdata[0];
//            pUC->txdata[1] = pUC->rxdata[1];
//            pUC->txdata[2] = pUC->rxdata[2];
//            pUC->txdata[3] = pUC->rxdata[3];
//            pUC->txdata[4] = pUC->rxdata[4];
            
            pUC->rxdata_length_last = 0U;
            pUC->rxdata_length_tmp = 0U;
            
            pUC->USART_State.BIT.resceive_enable = 0U;
            pUC->USART_State.BIT.transmission_enable = 1U;
            pUC->USART_Resceive_Flow = USART_STATE_IDLE;
        }break;
        case USART_STATE_ERROR:
        {
            pUC->rxdata_length_tmp = 0U;
            pUC->rxdata_length_last = 0U;
            pUC->rxdata_cnt = 0U;
            pUC->USART_Resceive_Flow = USART_STATE_IDLE;
        }break;
        default:
            break;
    }
}

void USART_Send_Transmission_Data_1(void)
{
    ST_USART_CONTROL* pUC = &USART_Ctrl_1;
    
    switch(pUC->USART_Transmission_Flow)
    {
        case USART_STATE_IDLE:
        {
            if(pUC->USART_State.BIT.transmission_enable == 1U)
            {
                if(++pUC->txdata_cnt > 500U)
                {
                    pUC->txdata_cnt = 0U;
                    pUC->txdata_length_tmp = 0U;
                    pUC->txdata_length_last = 0U;
                    
//                    pUC->txdata[pUC->txdata_length_tmp++] = pUC->rxdata[0];
//                    pUC->txdata[pUC->txdata_length_tmp++] = pUC->rxdata[1];
//                    pUC->txdata[pUC->txdata_length_tmp++] = pUC->rxdata[2];
//                    pUC->txdata[pUC->txdata_length_tmp++] = pUC->rxdata[3];
//                    pUC->txdata[pUC->txdata_length_tmp++] = pUC->rxdata[4];
                    
                    pUC->txdata[pUC->txdata_length_tmp++] = 1;
                    pUC->txdata[pUC->txdata_length_tmp++] = 3;
                    pUC->txdata[pUC->txdata_length_tmp++] = 5;
                    pUC->txdata[pUC->txdata_length_tmp++] = 7;
                    pUC->txdata[pUC->txdata_length_tmp++] = 9;
                    
                    USART1_TRANSMISSION_DATA = pUC->txdata[0];
                    UART_Enable_Tx(UART1); 
                    
                    pUC->USART_Transmission_Flow = USART_STATE_RUN;
                }
            }
            if(++pUC->error_cnt > 1000U)
            {
                pUC->error_cnt = 0U;
                pUC->USART_Transmission_Flow = USART_STATE_ERROR;
            }
        }break;
        case USART_STATE_RUN:
        {
            if(pUC->rxdata_length_last == pUC->rxdata_length_tmp)
            {
                pUC->USART_Transmission_Flow = USART_STATE_END;
            }
        }break;
        case USART_STATE_END:
        {
            pUC->USART_State.BIT.resceive_enable = 1U;
            pUC->USART_Transmission_Flow = USART_STATE_IDLE;
        }break;
        case USART_STATE_ERROR:
        {
            pUC->USART_State.BIT.resceive_enable = 1U;
            pUC->USART_Transmission_Flow = USART_STATE_IDLE;
        }break;
        default:
            break;
    }
}

void USART_Get_Resceive_Data_2(void)
{
    ST_USART_CONTROL* pUC = &USART_Ctrl_2;
    
    switch(pUC->USART_Resceive_Flow)
    {
        case USART_STATE_IDLE:
        {
            if(pUC->USART_State.BIT.resceive_enable == 1U)
            {
                if(++pUC->rxdata_cnt > 3U)
                {
                    pUC->rxdata_cnt = 0U;
                    UART_Enable_Rx(UART1);
                    pUC->USART_Resceive_Flow = USART_STATE_RUN;
                }
            }
        }break;
        case USART_STATE_RUN:
        {
            if(pUC->rxdata_length_tmp >= pUC->rxdata_maxlength)
            {
                UART_Disable_Rx(UART1);
                pUC->USART_Resceive_Flow = USART_STATE_ERROR;
            }
            if((pUC->rxdata_length_tmp == pUC->rxdata_length_last)
            && (pUC->rxdata_length_tmp != 0U))
            {
                if(++pUC->rxdata_cnt > 3)
                {
                    pUC->rxdata_cnt = 0;
                    UART_Disable_Rx(UART1);
                    pUC->USART_Resceive_Flow = USART_STATE_END;
                }
            }
            pUC->rxdata_length_last = pUC->rxdata_length_tmp;
        }break;
        case USART_STATE_END:
        {
//            pUC->txdata[0] = pUC->rxdata[0];
//            pUC->txdata[1] = pUC->rxdata[1];
//            pUC->txdata[2] = pUC->rxdata[2];
//            pUC->txdata[3] = pUC->rxdata[3];
//            pUC->txdata[4] = pUC->rxdata[4];
            
            pUC->rxdata_length_last = 0U;
            pUC->rxdata_length_tmp = 0U;
            
            pUC->USART_State.BIT.resceive_enable = 0U;
            pUC->USART_State.BIT.transmission_enable = 1U;
            pUC->USART_Resceive_Flow = USART_STATE_IDLE;
        }break;
        case USART_STATE_ERROR:
        {
            pUC->rxdata_length_tmp = 0U;
            pUC->rxdata_length_last = 0U;
            pUC->rxdata_cnt = 0U;
            pUC->USART_Resceive_Flow = USART_STATE_IDLE;
        }break;
        default:
            break;
    }
}

void USART_Send_Transmission_Data_2(void)
{
    ST_USART_CONTROL* pUC = &USART_Ctrl_2;
    
    switch(pUC->USART_Transmission_Flow)
    {
        case USART_STATE_IDLE:
        {
            if(pUC->USART_State.BIT.transmission_enable == 1U)
            {
                if(++pUC->txdata_cnt > 500U)
                {
                    pUC->txdata_cnt = 0U;
                    pUC->txdata_length_tmp = 0U;
                    pUC->txdata_length_last = 0U;
                    
//                    pUC->txdata[pUC->txdata_length_tmp++] = pUC->rxdata[0];
//                    pUC->txdata[pUC->txdata_length_tmp++] = pUC->rxdata[1];
//                    pUC->txdata[pUC->txdata_length_tmp++] = pUC->rxdata[2];
//                    pUC->txdata[pUC->txdata_length_tmp++] = pUC->rxdata[3];
//                    pUC->txdata[pUC->txdata_length_tmp++] = pUC->rxdata[4];
                    
                    pUC->txdata[pUC->txdata_length_tmp++] = 1;
                    pUC->txdata[pUC->txdata_length_tmp++] = 3;
                    pUC->txdata[pUC->txdata_length_tmp++] = 5;
                    pUC->txdata[pUC->txdata_length_tmp++] = 7;
                    pUC->txdata[pUC->txdata_length_tmp++] = 9;
                    
                    USART1_TRANSMISSION_DATA = pUC->txdata[0];
                    UART_Enable_Tx(UART1); 
                    
                    pUC->USART_Transmission_Flow = USART_STATE_RUN;
                }
            }
            if(++pUC->error_cnt > 1000U)
            {
                pUC->error_cnt = 0U;
                pUC->USART_Transmission_Flow = USART_STATE_ERROR;
            }
        }break;
        case USART_STATE_RUN:
        {
            if(pUC->rxdata_length_last == pUC->rxdata_length_tmp)
            {
                pUC->USART_Transmission_Flow = USART_STATE_END;
            }
        }break;
        case USART_STATE_END:
        {
            pUC->USART_State.BIT.resceive_enable = 1U;
            pUC->USART_Transmission_Flow = USART_STATE_IDLE;
        }break;
        case USART_STATE_ERROR:
        {
            pUC->USART_State.BIT.resceive_enable = 1U;
            pUC->USART_Transmission_Flow = USART_STATE_IDLE;
        }break;
        default:
            break;
    }
}

void USART_Resceive_Int_1(void)
{
    ST_USART_CONTROL* pUC = &USART_Ctrl_1;
    pUC->rxdata[pUC->rxdata_length_tmp++] = USART1_RESCEIVE_DATA; 
}

void USART_Transmission_Int_1(void)
{
    ST_USART_CONTROL* pUC = &USART_Ctrl_1;
    USART1_TRANSMISSION_DATA = pUC->txdata[++pUC->txdata_length_last];
    if(pUC->txdata_length_last == pUC->txdata_length_tmp)
    {
        UART_Disable_Tx(UART1);
    }
}

void USART_Resceive_Int_2(void)
{
    ST_USART_CONTROL* pUC = &USART_Ctrl_2;
    pUC->rxdata[pUC->rxdata_length_tmp++] = USART2_RESCEIVE_DATA; 
}

void USART_Transmission_Int_2(void)
{
    ST_USART_CONTROL* pUC = &USART_Ctrl_2;
    USART1_TRANSMISSION_DATA = pUC->txdata[++pUC->txdata_length_last];
    if(pUC->txdata_length_last == pUC->txdata_length_tmp)
    {
        UART_Disable_Tx(UART1);
    }
}
