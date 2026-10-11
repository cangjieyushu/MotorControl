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

/* 状态机接口 */
void UART_NUM_Init(void);
void UART_Get_Resceive_Data(void);
void UART_Send_Transmission_Data(void);
void UART_Resceive_Int(void);
void UART_Transmission_Int(void);

/* DMA 发送 / 环形缓冲区 */
void     uart_send_data(uint8_t *data, uint16_t len);
void     uart_send_string(const char *str);

void     ring_buffer_init(void);
uint16_t ring_buffer_available(void);
int      ring_buffer_get(void);
Q08U_    ring_buffer_put(uint8_t data);
void     ring_buffer_clear(void);

/* DMA 接收中断回调 */
void UART_DMA_Rx_Int(void);


#endif /* UARTS_H */
