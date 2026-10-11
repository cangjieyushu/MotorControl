/**************************************************************************************************
*     File Name :                        UARTS.h
*     Library/Module Name :              UARTS
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             串口通讯头文件
**************************************************************************************************/
#ifndef UARTS_H
#define UARTS_H


#include "bsp.h"
#include "hal_uart.h"


#define RESCEIVE_DATA_LENGTH        (20U)
#define TRANSMISSION_DATA_LENGTH    (20U)


typedef enum{
    UART_STATE_IDLE,
    UART_STATE_RUN,
    UART_STATE_END,
    UART_STATE_ERROR,
}EM_UART_STATE_FLOW;

typedef union{
    SC_ALL ALL;
    struct{
        SC_BIT        resceive_enable         :1;
        SC_BIT        transmission_enable     :1;
    }BIT;
}UN_UART_STATE_FLAG;

typedef struct{
    EM_UART_STATE_FLOW UART_Resceive_Flow;
    EM_UART_STATE_FLOW UART_Transmission_Flow;
    UN_UART_STATE_FLAG UART_State;
    
    Q08U_ rxdata[RESCEIVE_DATA_LENGTH];
    Q08U_ txdata[TRANSMISSION_DATA_LENGTH];

    Q32U_ rxdata_length_tmp;
    Q32U_ txdata_length_tmp;
    
    Q32U_ rxdata_length_last;
    Q32U_ txdata_length_last;

    Q32U_ rxdata_maxlength;
    Q32U_ txdata_maxlength;
    
    Q32U_ rxdata_cnt;
    Q32U_ txdata_cnt;
    
    Q32U_ rx_num;
    Q32U_ error_cnt;
}ST_UART_CONTROL;

typedef union{
    float f32p;
    Q08U_ u08p[4];
}UN_Q32U_to_F;

extern ST_UART_CONTROL UART_Ctrl;

/**********************************************************************************************
Function: UART_Get_Resceive_Data
Description: 串口1接收数据
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void UART_Get_Resceive_Data(void);

/**********************************************************************************************
Function: UART_Send_Transmission_Data
Description: 串口1发送数据
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void UART_Send_Transmission_Data(void);
/**********************************************************************************************
Function: UART_Resceive_Int_1
Description: 串口1接收数据中断
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void UART_Resceive_Int(void);

/**********************************************************************************************
Function: UART_Transmission_Int_1
Description: 串口1发送数据中断
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void UART_Transmission_Int(void);

void uart_send_data(uint8_t *data, uint16_t len);
void uart_send_string(const char *str);

void     ring_buffer_init(void);
uint16_t ring_buffer_available(void);
int      ring_buffer_get(void);
Q08U_    ring_buffer_put(uint8_t data);
void     ring_buffer_clear(void);

/**********************************************************************************************
Function: UART_DMA_Rx_Int
Description: UART的DMA接收
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void UART_DMA_Rx_Int(void);


#endif /* UARTS_H */
