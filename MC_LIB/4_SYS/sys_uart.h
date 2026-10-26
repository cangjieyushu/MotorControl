/**
 * @file    sys_uart.h
 * @brief   上位机通讯协议（自有协议）
 *
 *   帧格式（RX 固定 9 字节，TX 固定 10 字节）：
 *     接收：[0xAA][D1..D7][CRC8]        CRC8 = Crc8(D1+...+D7)，poly=0x2F
 *     发送：[0xFF][0xFF][HEAD][D1..D4][CRC8][0xFF][0xFF]
 *           HEAD 由设备编号决定（1~4 → 0xFA~0xFD）
 *
 *   收发方式：
 *     接收：DMA 循环 + 10ms 轮询（Uart_Rx_Poll_10ms）
 *     发送：协议层组包 + 10ms 状态机（Hmi_Uart_Tx_Process）
 * @author  CJYS
 * @date    2024/1/1
 */

#ifndef SYS_UART_H
#define SYS_UART_H

/* ======================== 1. Includes ===================== */
#include "hw_map.h"
#include "hw_fun.h"
#include "hw_para.h"

/* ======================== 2. Defines ====================== */
#define HMI_RX_FRAME_LEN            (4U)       /* 接收固定 10 字节帧 */
#define HMI_TX_FRAME_LEN            (10U)       /* 发送固定 10 字节帧 */
#define HMI_TX_TIMEOUT_CNT          (500U)      /* 500 × 10ms = 5000ms 超时 */

/* ======================== 3. Typedefs ===================== */
typedef enum {
    HMI_TX_IDLE  = 0,
    HMI_TX_RUN   = 1,
    HMI_TX_END   = 2,
} EM_HMI_TX_FLOW;

typedef union {
    uint32_t all;
    struct {
        uint32_t resceive_enable     : 1;
        uint32_t transmission_enable : 1;
    } BIT;
} UN_HMI_UART_STATE;

typedef struct {
    EM_HMI_TX_FLOW    tx_flow;
    UN_HMI_UART_STATE state;

    uint8_t  txdata[HMI_TX_FRAME_LEN];
    uint32_t txdata_len;
    uint32_t txdata_cnt;
    uint32_t error_cnt;
} ST_HMI_UART_CTRL;

/* ======================== 4. Globals ====================== */
extern ST_HMI_UART_CTRL Hmi_Uart_Ctrl;

/* ======================== 5. Function Prototypes ========== */
void Uart_Rx_Poll_10ms(void);

uint8_t Hmi_Crc8(uint8_t data);

void Hmi_Uart_Read_Process(void);

void Hmi_Uart_Tx_Process(void);

void Hmi_Uart_Send_Data(uint8_t *data, uint16_t len);

#endif /* SYS_UART_H */
