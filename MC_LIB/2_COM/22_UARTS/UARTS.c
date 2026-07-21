/**************************************************************************************************
*     File Name :                        UARTS.c
*     Library/Module Name :              UARTS
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             串口通讯源文件
**************************************************************************************************/

#include "UARTS.h"
#include "SYSTASK.h"


ST_UART_CONTROL UART_Ctrl = {
    .UART_State.BIT.resceive_enable = 1U,
    .rxdata_maxlength = RESCEIVE_DATA_LENGTH,
    .txdata_maxlength = TRANSMISSION_DATA_LENGTH,
};


/**********************************************************************************************
Function: Cal_CRC8
Description: CRC8校验
Input: 数据
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
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

/**********************************************************************************************
Function: UART_Get_Resceive_Data
Description: 串口1接收数据
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void UART_Get_Resceive_Data(void)
{
    ST_UART_CONTROL* pUC = &UART_Ctrl;
    
    switch(pUC->UART_Resceive_Flow)
    {
        case UART_STATE_IDLE:
        {
            if(pUC->UART_State.BIT.resceive_enable == 1U)
            {
                if(++pUC->rxdata_cnt > 5U)
                {
                    pUC->rxdata_cnt = 0U;
                    UARTH_Enable_Rx();
                    pUC->UART_Resceive_Flow = UART_STATE_RUN;
                }
            }
        }break;
        case UART_STATE_RUN:
        {
            if(pUC->rxdata_length_tmp >= pUC->rxdata_maxlength)
            {
                UARTH_Disable_Rx();
                pUC->UART_Resceive_Flow = UART_STATE_ERROR;
            }
            if((pUC->rxdata_length_tmp == pUC->rxdata_length_last)
            && (pUC->rxdata_length_tmp != 0U))
            {
                if(++pUC->rxdata_cnt > 5U)
                {
                    pUC->rxdata_cnt = 0U;
                    UARTH_Disable_Rx();
                    pUC->UART_Resceive_Flow = UART_STATE_END;
                }
            }
            pUC->rxdata_length_last = pUC->rxdata_length_tmp;
        }break;
        case UART_STATE_END:
        {
            Q08U_ txdata_tmp = Cal_CRC8(pUC->rxdata[0]+pUC->rxdata[1]+pUC->rxdata[2]+pUC->rxdata[3]+pUC->rxdata[4]+pUC->rxdata[5]+pUC->rxdata[6]);
//            if((pUC->rxdata[0] == HAL_UART_RX_HEAD) && (txdata_tmp == pUC->rxdata[7]))
//            {
//                Systask.System_State_Flag.BIT.system_runflag = pUC->rxdata[1];
//                Systask.Q16U_Speed_Target = (pUC->rxdata[2]<<8U) + pUC->rxdata[3];
//                Systask.System_State_Flag.BIT.system_clearflag = pUC->rxdata[4];
//                Systask.Q16U_YaSuo_Mode = pUC->rxdata[5];
//                
//                pUC->UART_State.BIT.transmission_enable = 1U;
//            }
//            else
//            {
//                pUC->UART_State.BIT.resceive_enable = 1U;
//            }
            
            pUC->rxdata_length_last = 0U;
            pUC->rxdata_length_tmp = 0U;
            pUC->rxdata_cnt = 0U;
            
            pUC->txdata_cnt = 0U;
            pUC->txdata_length_tmp = 0U;
            pUC->txdata_length_last = 0U;
            
            pUC->UART_Resceive_Flow = UART_STATE_IDLE;
        }break;
        case UART_STATE_ERROR:
        {
            pUC->rxdata_length_tmp = 0U;
            pUC->rxdata_length_last = 0U;
            pUC->rxdata_cnt = 0U;
            
            pUC->txdata_cnt = 0U;
            pUC->txdata_length_tmp = 0U;
            pUC->txdata_length_last = 0U;
            
            pUC->UART_State.BIT.transmission_enable = 0U;
            pUC->UART_State.BIT.resceive_enable = 1U;
            pUC->UART_Resceive_Flow = UART_STATE_IDLE;
        }break;
        default:
            break;
    }
}

/**********************************************************************************************
Function: UART_Send_Transmission_Data
Description: 串口1发送数据
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void UART_Send_Transmission_Data(void)
{
    ST_UART_CONTROL* pUC = &UART_Ctrl;
    
    switch(pUC->UART_Transmission_Flow)
    {
        case UART_STATE_IDLE:
        {
            if(pUC->UART_State.BIT.transmission_enable == 1U)
            {
                if(++pUC->txdata_cnt > 5U)
                {
                    pUC->txdata_cnt = 0U;
                    pUC->txdata_length_tmp = 0U;
                    pUC->txdata_length_last = 0U;
                    
//                    pUC->txdata[pUC->txdata_length_tmp++] = HAL_UART_TX_HEAD;
//                    pUC->txdata[pUC->txdata_length_tmp++] = (Q08U_)((Systask.Q16U_Speed&0xFF00U)>>8U);
//                    pUC->txdata[pUC->txdata_length_tmp++] = (Q08U_)(Systask.Q16U_Speed&0x00FFU);
//                    pUC->txdata[pUC->txdata_length_tmp++] = (Q08U_)Systask.Q16U_Error_Code;
//                    pUC->txdata[pUC->txdata_length_tmp++] = 0U;
//                    pUC->txdata[pUC->txdata_length_tmp++] = 0U;
//                    pUC->txdata[pUC->txdata_length_tmp++] = 0U;
//                    pUC->txdata[pUC->txdata_length_tmp++] = Cal_CRC8(pUC->txdata[0]+pUC->txdata[1]+pUC->txdata[2]+pUC->txdata[3]+pUC->txdata[4]+pUC->txdata[5]+pUC->txdata[6]);
                    
                    UART_TRANSMISSION_DATA = pUC->txdata[0];
                    UARTH_Enable_Tx();
                    
                    pUC->UART_Transmission_Flow = UART_STATE_RUN;
                }
            }
            if(++pUC->error_cnt > 1000U)
            {
                pUC->error_cnt = 0U;
                pUC->UART_Transmission_Flow = UART_STATE_ERROR;
            }
        }break;
        case UART_STATE_RUN:
        {
            if(pUC->txdata_length_last >= pUC->txdata_length_tmp)
            {
                pUC->UART_Transmission_Flow = UART_STATE_END;
            }
        }break;
        case UART_STATE_END:
        {
            pUC->rxdata_length_tmp = 0U;
            pUC->rxdata_length_last = 0U;
            pUC->rxdata_cnt = 0U;
            
            pUC->txdata_cnt = 0U;
            pUC->txdata_length_tmp = 0U;
            pUC->txdata_length_last = 0U;
            
            pUC->UART_State.BIT.transmission_enable = 0U;
            pUC->UART_State.BIT.resceive_enable = 1U;
            pUC->UART_Transmission_Flow = UART_STATE_IDLE;
        }break;
        case UART_STATE_ERROR:
        {
            pUC->rxdata_length_tmp = 0U;
            pUC->rxdata_length_last = 0U;
            pUC->rxdata_cnt = 0U;
            
            pUC->txdata_cnt = 0U;
            pUC->txdata_length_tmp = 0U;
            pUC->txdata_length_last = 0U;
            
            pUC->UART_State.BIT.transmission_enable = 0U;
            pUC->UART_State.BIT.resceive_enable = 1U;
            pUC->UART_Transmission_Flow = UART_STATE_IDLE;
        }break;
        default:
            break;
    }
}

/**********************************************************************************************
Function: UART_Resceive_Int
Description: 串口1接收数据中断
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void UART_Resceive_Int(void)
{
    ST_UART_CONTROL* pUC = &UART_Ctrl;
    if(pUC->rxdata_length_tmp < pUC->rxdata_maxlength)
    {
        pUC->rxdata[pUC->rxdata_length_tmp++] = UART_RESCEIVE_DATA;
    }
    else
    {
        UARTH_Disable_Rx();
    }
}

/**********************************************************************************************
Function: UART_Transmission_Int
Description: 串口1发送数据中断
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void UART_Transmission_Int(void)
{
    ST_UART_CONTROL* pUC = &UART_Ctrl;
    UART_TRANSMISSION_DATA = pUC->txdata[pUC->txdata_length_last++];
    if(pUC->txdata_length_last == pUC->txdata_length_tmp)
    {
        UARTH_Disable_Tx();
    }
}
