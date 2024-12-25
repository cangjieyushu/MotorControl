/**************************************************************************************************/
/**
 * @file     Z20K146M.h
 * @brief    Z20K146M device header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#ifndef  Z20K146M_H
#define Z20K146M_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifndef IO
#define   RO     volatile const       /*!< Read only permission */
#define   WO     volatile             /*!< Write only permission */
#define   RW     volatile             /*!< Read/Write permission */
#endif

/**
 * @brief Variant Peripheral Instance Information
 */
#define CAN_INSTANCE_NUM      (6U)
#define I2S_INSTANCE_NUM      (1U)
#define I2C_INSTANCE_NUM      (2U)  


/**
 * @brief Peripheral Base Address
 */
#define FLASH_CODE_BASE_ADDR           ((uint32_t)0x00000000)            /*!< program/Code flash base address */
#define FLASH_CODE_END_ADDR            ((uint32_t)0x000FFFFF)            /*!< program/Code flash end address */
#define FLASH_DATA_BASE_ADDR           ((uint32_t)0x01000000)            /*!< Data flash base address */
#define FLASH_DATA_END_ADDR            ((uint32_t)0x0101FFFF)            /*!< Data flash end address */
#define FLASH_IFR_BASE_ADDR            ((uint32_t)0x02000000)            /*!< flash IFR base address */
#define FLASH_IFR_END_ADDR             ((uint32_t)0x02007FFF)            /*!< flash IFR end address */
#define SRAMU_BASE_ADDR                ((uint32_t)0x20000000)            /*!< SRAMU base address */
#define SRAMU_END_ADDR                 ((uint32_t)0x2001FFFF)            /*!< SRAMU end address */ 
#define PERIPHERAL_BASE_ADDR           ((uint32_t)0x40000000)            /*!< Peripheral area base address */
#define AIPS0_BASE_ADDR                ((uint32_t)0x40000000)            /*!< AIPS0 base address */
#define FLASH_DFLASH_SIZE              ((uint32_t)0x00020000)            /*!< Data flash size */
#define PRI_PERI_BUS_BASE_ADDR         ((uint32_t)0xE0000000)            /*!< private Peripheral base address */

#define DMA_BASE_ADDR              (PERIPHERAL_BASE_ADDR + 0x8000UL)        /*!< DMA controller base address */
#define DMAMUX_BASE_ADDR           (PERIPHERAL_BASE_ADDR + 0x9000UL)        /*!< DMA channel Multiplexer base address */
#define SMPU_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0xA000UL)        /*!< SMPU base address */
#define EIRU_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0xB000UL)        /*!< EIRU base address */
#define TIM0_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0xC000UL)        /*!< TIM0 base address */
#define TIM1_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0xD000UL)        /*!< TIM1 base address */
#define MCPWM0_BASE_ADDR           (PERIPHERAL_BASE_ADDR + 0xE000UL)        /*!< MCPWM0 base address */
#define TDG0_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0xF000UL)        /*!< TDG0 base address */
#define TIM2_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x18000UL)       /*!< TIM2 base address */
#define TIM3_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x19000UL)       /*!< TIM3 base address */
#define MCPWM1_BASE_ADDR           (PERIPHERAL_BASE_ADDR + 0x1A000UL)       /*!< MCPWM1 base address */
#define TDG1_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x1B000UL)       /*!< TDG1 base address */     
#define FLASHC_BASE_ADDR           (PERIPHERAL_BASE_ADDR + 0x20000UL)       /*!< flash controller base address */
#define CAN0_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x24000UL)       /*!< CAN0 base address */
#define CAN1_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x25000UL)       /*!< CAN1 base address */ 
#define ADC1_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x27000UL)       /*!< ADC1 base address */
#define SPI0_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x2C000UL)       /*!< SPI0 base address */
#define SPI1_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x2D000UL)       /*!< SPI1 base address */
#define SPI2_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x30000UL)       /*!< SPI2 base address */
#define SPI3_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x31000UL)       /*!< SPI3 base address */
#define CRC_BASE_ADDR              (PERIPHERAL_BASE_ADDR + 0x32000UL)       /*!< CRC base address */
#define AES_BASE_ADDR              (PERIPHERAL_BASE_ADDR + 0x33000UL)       /*!< AES base address */
#define TRNG_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x34000UL)       /*!< TRNG base address */
#define CAN2_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x38000UL)       /*!< CAN2 base address */
#define CAN3_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x39000UL)       /*!< CAN3 base address */ 
#define ADC0_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x3B000UL)       /*!< ADC0 base address */
#define CMU0_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x3E000UL)       /*!< CMU0 base address */
#define STIM_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x40000UL)       /*!< STIM base address */
#define CMU1_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x42000UL)       /*!< CMU1 base address */
#define CMU2_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x43000UL)       /*!< CMU2 base address */     
#define CAN4_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x44000UL)       /*!< CAN4 base address */
#define CAN5_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x45000UL)       /*!< CAN5 base address */
#define SCM_BASE_ADDR              (PERIPHERAL_BASE_ADDR + 0x48000UL)       /*!< SCM base address */
#define PORTA_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0x49000UL)       /*!< PORTA multiplexing base address */
#define PORTB_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0x4A000UL)       /*!< PORTB multiplexing base address */
#define PORTC_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0x4B000UL)       /*!< PORTC multiplexing base address */
#define PORTD_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0x50000UL)       /*!< PORTD multiplexing base address */
#define PORTE_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0x51000UL)       /*!< PORTE multiplexing base address */
#define WDOG_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x52000UL)       /*!< WDOG base address */
#define I2S0_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x54000UL)       /*!< I2S0 base address */
#define I2C1_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x58000UL)       /*!< I2C1 base address */
#define EWDT_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x61000UL)       /*!< EWDT base address */
#define TMU_BASE_ADDR              (PERIPHERAL_BASE_ADDR + 0x63000UL)       /*!< TMU base address */
#define SCC_BASE_ADDR              (PERIPHERAL_BASE_ADDR + 0x64000UL)       /*!< SCC base address */
#define PARCC_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0x65000UL)       /*!< PARCC base address */
#define I2C0_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x66000UL)       /*!< I2C0 base address */     
#define UART0_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0x6A000UL)       /*!< UART0 base address */
#define UART1_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0x6B000UL)       /*!< UART1 base address */
#define UART2_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0x6C000UL)       /*!< UART2 base address */
#define UART3_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0x70000UL)       /*!< UART3 base address */
#define UART4_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0x71000UL)       /*!< UART4 base address */
#define UART5_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0x72000UL)       /*!< UART5 base address */
#define CMP_BASE_ADDR              (PERIPHERAL_BASE_ADDR + 0x73000UL)       /*!< CMP base address */
#define RTC_BASE_ADDR              (PERIPHERAL_BASE_ADDR + 0x79000UL)       /*!< RTC base address */ 
#define REGFILE_BASE_ADDR          (PERIPHERAL_BASE_ADDR + 0x7C000UL)       /*!< REGFILE base address */
#define PMU_BASE_ADDR              (PERIPHERAL_BASE_ADDR + 0x7D000UL)       /*!< PMU base address */
#define SRMC_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x7E000UL)       /*!< SRMC base address */
#define SERU_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x7F000UL)       /*!< SERU base address */
#define GPIO_BASE_ADDR             ((uint32_t)0x400FF000)                   /*!< GPIO base address */     

/**
 * @brief IRQ Number Definition
 */
typedef enum IRQn
{
    /******  Cortex-M4F Processor IRQ Numbers *******************************/
    NMI_IRQn             = -14,    /*!< 2 Non Maskable Interrupt */
    HardFalut_IRQn       = -13,    /*!< 3 Hardfault Interrupt */
    MemManageFault_IRQn  = -12,    /*!< 4 memory manage fault Interrupt */
    BusFault_IRQn        = -11,    /*!< 5 bus fault Interrupt */
    UsageFault_IRQn      = -10,    /*!< 6 usage fault Interrupt */
    SVCall_IRQn          = -5,     /*!< 11 SV Call Interrupt */
    DebugMonitor_IRQn    = -4,     /*!< 12 debug monitor Interrupt */
    PendSV_IRQn          = -2,     /*!< 14 Pend SV Interrupt  */
    SysTick_IRQn         = -1,     /*!< 15 System Tick Interrupt  */

    /******  specific IRQ Numbers *************************************/
    DMA_Ch0_IRQn = 0,             /*!< DMA channel 0 transfer complete Interrupt */
    DMA_Ch1_IRQn = 1,             /*!< DMA channel 1 transfer complete Interrupt */
    DMA_Ch2_IRQn = 2,             /*!< DMA channel 2 transfer complete Interrupt */
    DMA_Ch3_IRQn = 3,             /*!< DMA channel 3 transfer complete Interrupt */
    DMA_Ch4_IRQn = 4,             /*!< DMA channel 4 transfer complete Interrupt */
    DMA_Ch5_IRQn = 5,             /*!< DMA channel 5 transfer complete Interrupt */
    DMA_Ch6_IRQn = 6,             /*!< DMA channel 6 transfer complete Interrupt */
    DMA_Ch7_IRQn = 7,             /*!< DMA channel 7 transfer complete Interrupt */
    DMA_Ch8_IRQn = 8,             /*!< DMA channel 8 transfer complete Interrupt */
    DMA_Ch9_IRQn = 9,             /*!< DMA channel 9 transfer complete Interrupt */
    DMA_Ch10_IRQn = 10,            /*!< DMA channel 10 transfer complete Interrupt */
    DMA_Ch11_IRQn = 11,            /*!< DMA channel 11 transfer complete Interrupt */
    DMA_Ch12_IRQn = 12,            /*!< DMA channel 12 transfer complete Interrupt */
    DMA_Ch13_IRQn = 13,            /*!< DMA channel 13 transfer complete Interrupt */
    DMA_Ch14_IRQn = 14,            /*!< DMA channel 14 transfer complete Interrupt */
    DMA_Ch15_IRQn = 15,            /*!< DMA channel 15 transfer complete Interrupt */
    DMA_Err_IRQn = 16,             /*!< DMA channel 0-15 error Interrupt */
    FLASH_CmdComplete_IRQn = 17,   /*!< flash command complete Interrupt */
    FLASH_Ecc_IRQn = 18,           /*!< flash multi-bit or single-bit ECC Interrupt */
    PMU_IRQn = 19,                 /*!< PMU Interrupt */
    WDOG_IRQn = 20,                /*!< watchdog Interrupt */
    EWDT_IRQn = 21,                /*!< external watchdog monitor Interrupt */
    SRMC_IRQn = 22,                /*!< system reset and mode control Interrupt */
    I2C0_IRQn = 23,                /*!< I2C 0 Interrupt */
    I2C1_IRQn = 24,                /*!< I2C 1 Interrupt */    
    SPI0_Txe_IRQn = 25,            /*!< SPI 0 TXE Interrupt */
    SPI0_Txo_IRQn = 26,            /*!< SPI 0 TXO Interrupt */
    SPI0_Rxf_IRQn = 27,            /*!< SPI 0 RXF Interrupt */
    SPI0_Rxo_IRQn = 28,            /*!< SPI 0 RXO Interrupt */
    SPI0_Rxu_IRQn = 29,            /*!< SPI 0 RXU Interrupt */
    Reserved30_IRQn = 30,          /*!< Reserved interrupt */
    SPI1_Txe_IRQn = 31,            /*!< SPI 1 TXE Interrupt */
    SPI1_Txo_IRQn = 32,            /*!< SPI 1 TXO Interrupt */
    SPI1_Rxf_IRQn = 33,            /*!< SPI 1 RXF Interrupt */
    SPI1_Rxo_IRQn = 34,            /*!< SPI 1 RXO Interrupt */
    SPI1_Rxu_IRQn = 35,            /*!< SPI 1 RXU Interrupt */
    Reserved36_IRQn = 36,          /*!< Reserved interrupt */ 
    SPI2_Txe_IRQn = 37,            /*!< SPI 2 TXE Interrupt */
    SPI2_Txo_IRQn = 38,            /*!< SPI 2 TXO Interrupt */
    SPI2_Rxf_IRQn = 39,            /*!< SPI 2 RXF Interrupt */
    SPI2_Rxo_IRQn = 40,            /*!< SPI 2 RXO Interrupt */
    SPI2_Rxu_IRQn = 41,            /*!< SPI 2 RXU Interrupt */
    Reserved42_IRQn = 42,          /*!< Reserved interrupt */
    SPI3_Txe_IRQn = 43,            /*!< SPI 3 TXE Interrupt */
    SPI3_Txo_IRQn = 44,            /*!< SPI 3 TXO Interrupt */
    SPI3_Rxf_IRQn = 45,            /*!< SPI 3 RXF Interrupt */
    SPI3_Rxo_IRQn = 46,            /*!< SPI 3 RXO Interrupt */
    SPI3_Rxu_IRQn = 47,            /*!< SPI 3 RXU Interrupt */
    Reserved48_IRQn = 48,          /*!< Reserved interrupt */
    UART0_IRQn = 49,               /*!< UART 0 Interrupt */
    UART1_IRQn = 50,               /*!< UART 1 Interrupt */
    UART2_IRQn = 51,               /*!< UART 2 Interrupt */
    UART3_IRQn = 52,               /*!< UART 3 Interrupt */
    UART4_IRQn = 53,               /*!< UART 4 Interrupt */
    UART5_IRQn = 54,               /*!< UART 5 Interrupt */
    CAN0_BusOff_IRQn = 55,         /*!< CAN 0 bus off/ bus off done Interrupt */
    CAN0_TxWarn_IRQn = 56,         /*!< CAN 0 TX warning Interrupt */
    CAN0_RxWarn_IRQn = 57,         /*!< CAN 0 RX warning Interrupt */
    CAN0_Err_IRQn = 58,            /*!< CAN 0 error Interrupt */
    CAN0_ErrFd_IRQn = 59,          /*!< CAN 0 error FD Interrupt */
    CAN0_PnWake_IRQn = 60,         /*!< CAN 0 PN wakeup Interrupt */
    CAN0_SelfWakeup_IRQn = 61,     /*!< CAN 0 self wakeup Interrupt */
    CAN0_Ecc_IRQn = 62,            /*!< CAN 0 ECC Interrupt */
    CAN0_Mb0To15_IRQn = 63,        /*!< CAN 0 message buffer 0-15 Interrupt */
    CAN0_Mb16To31_IRQn = 64,       /*!< CAN 0 message buffer 16-31 Interrupt */
    CAN0_Mb32To47_IRQn = 65,       /*!< CAN 0 message buffer 32-47 Interrupt */
    CAN0_Mb48To63_IRQn = 66,       /*!< CAN 0 message buffer 48-63 Interrupt */
    CAN1_BusOff_IRQn = 67,         /*!< CAN 1 bus off/ bus off done Interrupt */
    CAN1_TxWarn_IRQn = 68,         /*!< CAN 1 TX warning Interrupt */
    CAN1_RxWarn_IRQn = 69,         /*!< CAN 1 RX warning Interrupt */
    CAN1_Err_IRQn = 70,            /*!< CAN 1 error Interrupt */
    CAN1_ErrFd_IRQn = 71,          /*!< CAN 1 error FD Interrupt */
    CAN1_PnWake_IRQn = 72,         /*!< CAN 1 PN wakeup Interrupt */
    CAN1_SelfWakeup_IRQn = 73,     /*!< CAN 1 self wakeup Interrupt */
    CAN1_Ecc_IRQn = 74,            /*!< CAN 1 ECC Interrupt */
    CAN1_Mb0To15_IRQn = 75,        /*!< CAN 1 message buffer 0-15 Interrupt */
    CAN1_Mb16To31_IRQn = 76,       /*!< CAN 1 message buffer 16-31 Interrupt */
    CAN1_Mb32To47_IRQn = 77,       /*!< CAN 1 message buffer 32-47 Interrupt */
    CAN1_Mb48To63_IRQn = 78,       /*!< CAN 1 message buffer 48-63 Interrupt */
    CAN2_BusOff_IRQn = 79,         /*!< CAN 2 bus off/ bus off done Interrupt */
    CAN2_TxWarn_IRQn = 80,         /*!< CAN 2 TX warning Interrupt */
    CAN2_RxWarn_IRQn = 81,         /*!< CAN 2 RX warning Interrupt */
    CAN2_Err_IRQn = 82,            /*!< CAN 2 error Interrupt */
    CAN2_ErrFd_IRQn = 83,          /*!< CAN 2 error FD Interrupt */
    CAN2_PnWake_IRQn = 84,         /*!< CAN 2 PN wakeup Interrupt */
    CAN2_SelfWakeup_IRQn = 85,     /*!< CAN 2 self wakeup Interrupt */
    CAN2_Ecc_IRQn = 86,            /*!< CAN 2 ECC Interrupt */
    CAN2_Mb0To15_IRQn = 87,        /*!< CAN 2 message buffer 0-15 Interrupt */
    CAN2_Mb16To31_IRQn = 88,       /*!< CAN 2 message buffer 16-31 Interrupt */
    CAN2_Mb32To47_IRQn = 89,       /*!< CAN 2 message buffer 32-47 Interrupt */
    CAN2_Mb48To63_IRQn = 90,       /*!< CAN 2 message buffer 48-63 Interrupt */
    CAN3_BusOff_IRQn = 91,         /*!< CAN 3 bus off/ bus off done Interrupt */
    CAN3_TxWarn_IRQn = 92,         /*!< CAN 3 TX warning Interrupt */
    CAN3_RxWarn_IRQn = 93,         /*!< CAN 3 RX warning Interrupt */
    CAN3_Err_IRQn = 94,            /*!< CAN 3 error Interrupt */
    CAN3_ErrFd_IRQn = 95,          /*!< CAN 3 error FD Interrupt */
    CAN3_PnWake_IRQn = 96,         /*!< CAN 3 PN wakeup Interrupt */
    CAN3_SelfWakeup_IRQn = 97,     /*!< CAN 3 self wakeup Interrupt */
    CAN3_Ecc_IRQn = 98,            /*!< CAN 3 ECC Interrupt */
    CAN3_Mb0To15_IRQn = 99,        /*!< CAN 3 message buffer 0-15 Interrupt */
    CAN3_Mb16To31_IRQn = 100,      /*!< CAN 3 message buffer 16-31 Interrupt */
    CAN3_Mb32To47_IRQn = 101,      /*!< CAN 3 message buffer 32-47 Interrupt */
    CAN3_Mb48To63_IRQn = 102,      /*!< CAN 3 message buffer 48-63 Interrupt */
    CAN4_BusOff_IRQn = 103,        /*!< CAN 4 bus off/ bus off done Interrupt */
    CAN4_TxWarn_IRQn = 104,        /*!< CAN 4 TX warning Interrupt */
    CAN4_RxWarn_IRQn = 105,        /*!< CAN 4 RX warning Interrupt */
    CAN4_Err_IRQn = 106,           /*!< CAN 4 error Interrupt */
    CAN4_ErrFd_IRQn = 107,         /*!< CAN 4 error FD Interrupt */
    CAN4_PnWake_IRQn = 108,        /*!< CAN 4 PN wakeup Interrupt */
    CAN4_SelfWakeup_IRQn = 109,    /*!< CAN 4 self wakeup Interrupt */
    CAN4_Ecc_IRQn = 110,           /*!< CAN 4 ECC Interrupt */
    CAN4_Mb0To15_IRQn = 111,       /*!< CAN 4 message buffer 0-15 Interrupt */
    CAN4_Mb16To31_IRQn = 112,      /*!< CAN 4 message buffer 16-31 Interrupt */
    CAN4_Mb32To47_IRQn = 113,      /*!< CAN 4 message buffer 32-47 Interrupt */
    CAN4_Mb48To63_IRQn = 114,      /*!< CAN 4 message buffer 48-63 Interrupt */
    CAN5_BusOff_IRQn = 115,        /*!< CAN 5 bus off/ bus off done Interrupt */
    CAN5_TxWarn_IRQn = 116,        /*!< CAN 5 TX warning Interrupt */
    CAN5_RxWarn_IRQn = 117,        /*!< CAN 5 RX warning Interrupt */
    CAN5_Err_IRQn = 118,           /*!< CAN 5 error Interrupt */
    CAN5_ErrFd_IRQn = 119,         /*!< CAN 5 error FD Interrupt */
    CAN5_PnWake_IRQn = 120,        /*!< CAN 5 PN wakeup Interrupt */
    CAN5_SelfWakeup_IRQn = 121,    /*!< CAN 5 self wakeup Interrupt */
    CAN5_Ecc_IRQn = 122,           /*!< CAN 5 ECC Interrupt */
    CAN5_Mb0To15_IRQn = 123,       /*!< CAN 5 message buffer 0-15 Interrupt */
    CAN5_Mb16To31_IRQn = 124,      /*!< CAN 5 message buffer 16-31 Interrupt */
    CAN5_Mb32To47_IRQn = 125,      /*!< CAN 5 message buffer 32-47 Interrupt */
    CAN5_Mb48To63_IRQn = 126,      /*!< CAN 5 message buffer 48-63 Interrupt */
    Reserved127_IRQn = 127,        /*!< Reserved127 */
    Reserved128_IRQn = 128,        /*!< Reserved128 */
    Reserved129_IRQn = 129,        /*!< Reserved129 */
    Reserved130_IRQn = 130,        /*!< Reserved130 */
    Reserved131_IRQn = 131,        /*!< Reserved131 */
    Reserved132_IRQn = 132,        /*!< Reserved132 */
    Reserved133_IRQn = 133,        /*!< Reserved133 */
    Reserved134_IRQn = 134,        /*!< Reserved134 */
    Reserved135_IRQn = 135,        /*!< Reserved135 */
    Reserved136_IRQn = 136,        /*!< Reserved136 */
    Reserved137_IRQn = 137,        /*!< Reserved137 */
    Reserved138_IRQn = 138,        /*!< Reserved138 */
    Reserved139_IRQn = 139,        /*!< Reserved139 */
    Reserved140_IRQn = 140,        /*!< Reserved140 */
    Reserved141_IRQn = 141,        /*!< Reserved141 */
    Reserved142_IRQn = 142,        /*!< Reserved142 */
    Reserved143_IRQn = 143,        /*!< Reserved143 */
    Reserved144_IRQn = 144,        /*!< Reserved144 */
    Reserved145_IRQn = 145,        /*!< Reserved145 */
    Reserved146_IRQn = 146,        /*!< Reserved146 */
    Reserved147_IRQn = 147,        /*!< Reserved147 */
    Reserved148_IRQn = 148,        /*!< Reserved148 */
    Reserved149_IRQn = 149,        /*!< Reserved149 */
    Reserved150_IRQn = 150,        /*!< Reserved150 */
    Reserved151_IRQn = 151,        /*!< Reserved151 Interrupt */
    Reserved152_IRQn = 152,        /*!< Reserved152 Interrupt */
    Reserved153_IRQn = 153,        /*!< Reserved153 Interrupt */
    TIM0_Ch_IRQn = 154,            /*!< TIM0 CH Interrupt */
    TIM0_Fault_IRQn = 155,         /*!< TIM0 Fault Interrupt */
    TIM0_Overflow_IRQn = 156,       /*!< TIM0 overflow Interrupt */
    TIM0_Rlfl_IRQn = 157,          /*!< TIM0 Rlfl Interrupt */
    TIM1_Ch_IRQn = 158,            /*!< TIM1 CH Interrupt */
    TIM1_Fault_IRQn = 159,         /*!< TIM1 Fault Interrupt */
    TIM1_Overflow_IRQn = 160,       /*!< TIM1 overflow Interrupt */
    TIM1_Rlfl_IRQn = 161,          /*!< TIM1 Rlfl Interrupt */
    TIM2_Ch_IRQn = 162,            /*!< TIM2 CH Interrupt */
    TIM2_Fault_IRQn = 163,         /*!< TIM2 Fault Interrupt */
    TIM2_Overflow_IRQn = 164,       /*!< TIM2 overflow Interrupt */
    TIM2_Rlfl_IRQn = 165,          /*!< TIM2 Rlfl Interrupt */
    TIM3_Ch_IRQn = 166,            /*!< TIM3 CH Interrupt */
    TIM3_Fault_IRQn = 167,         /*!< TIM3 Fault Interrupt */
    TIM3_Overflow_IRQn = 168,       /*!< TIM3 overflow Interrupt */
    TIM3_Rlfl_IRQn = 169,          /*!< TIM3 Rlfl Interrupt */
    TDG0_Tco_IRQn = 170,           /*!< TDG0 TCO Interrupt */
    TDG0_Err_IRQn = 171,           /*!< TDG0 ERR Interrupt */
    TDG1_Tco_IRQn = 172,           /*!< TDG1 TCO Interrupt */
    TDG1_Err_IRQn = 173,           /*!< TDG1 ERR Interrupt */
    I2S0_IRQn = 174,               /*!< I2S0 Interrupt */
    Reserved175_IRQn = 175,        /*!< Reserved175 */
    PORTA_IRQn = 176,              /*!< port A Interrupt */
    PORTB_IRQn = 177,              /*!< port B Interrupt */
    PORTC_IRQn = 178,              /*!< port C Interrupt */
    PORTD_IRQn = 179,              /*!< port D Interrupt */
    PORTE_IRQn = 180,              /*!< port E Interrupt */
    STIM_IRQn = 181,               /*!< STIM Interrupt */
    RTC_Alarm_IRQn = 182,          /*!< RTC alarm Interrupt */
    RTC_Second_IRQn = 183,         /*!< RTC second Interrupt */
    AES_IRQn = 184,                /*!< AES Interrupt */
    TRNG_IRQn = 185,               /*!< TRNG Interrupt */
    CMU0_IRQn = 186,               /*!< CMU0 Interrupt */
    CMU1_IRQn = 187,               /*!< CMU1 Interrupt */
    CMU2_IRQn = 188,               /*!< CMU2 Interrupt */
    SERU_ParityErr_IRQn = 189,     /*!< SERU parity error Interrupt */
    SERU_ChErr_IRQn = 190,         /*!< SERU channel error Interrupt */
    SCC_IRQn = 191,                /*!< SCC Interrupt */
    MCPWM0_Ch_IRQn = 192,          /*!< MCPWM0 CH Interrupt */
    MCPWM0_Fault_IRQn = 193,       /*!< MCPWM0 fault Interrupt */
    MCPWM0_Overflow_IRQn = 194,    /*!< MCPWM0 overflow Interrupt */
    MCPWM0_Rlfl_IRQn = 195,        /*!< MCPWM0 Rlfl Interrupt */
    MCPWM1_Ch_IRQn = 196,          /*!< MCPWM1 CH Interrupt */
    MCPWM1_Fault_IRQn = 197,       /*!< MCPWM1 fault Interrupt */
    MCPWM1_Overflow_IRQn = 198,    /*!< MCPWM1 overflow Interrupt */
    MCPWM1_Rlfl_IRQn = 199,        /*!< MCPWM1 Rlfl Interrupt */    
    ADC0_IRQn = 200,               /*!< ADC0 Interrupt */
    ADC1_IRQn = 201,               /*!< ADC1 Interrupt */    
    CMP_IRQn = 202,                /*!< CMP Interrupt */
    FPU_Err_IRQn = 203,            /*!< FPU error Interrupt */
    CACHE_Err_IRQn = 204,          /*!< CACHE error Interrupt */
} IRQn_Type;

/**
  @brief  Structure type to access the System Control and ID Register not in the SCB.
 */
typedef struct
{
      uint32_t RESERVED0[1U];
  RO  uint32_t ICTR;                   /*!< Offset: 0x004 (R/ )  Interrupt Controller Type Register */
  RW  uint32_t ACTLR;                  /*!< Offset: 0x008 (R/W)  Auxiliary Control Register */
} Z20_SCnSCBType;

/**
 * @brief  Structure type to access the System Control Block (SCB).
 */
typedef struct
{
  RO uint32_t CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  RW uint32_t ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  RW uint32_t VTOR;                   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  RW uint32_t AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  RW uint32_t SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
  RW uint32_t CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  RW uint8_t  SHP[12U];               /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  RW uint32_t SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
  RW uint32_t CFSR;                   /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
  RW uint32_t HFSR;                   /*!< Offset: 0x02C (R/W)  HardFault Status Register */
  RW uint32_t DFSR;                   /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
  RW uint32_t MMFAR;                  /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
  RW uint32_t BFAR;                   /*!< Offset: 0x038 (R/W)  BusFault Address Register */
  RW uint32_t AFSR;                   /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
  RO uint32_t PFR[2U];                /*!< Offset: 0x040 (R/ )  Processor Feature Register */
  RO uint32_t DFR;                    /*!< Offset: 0x048 (R/ )  Debug Feature Register */
  RO uint32_t ADR;                    /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
  RO uint32_t MMFR[4U];               /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
  RO uint32_t ISAR[5U];               /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
     uint32_t RESERVED0[5U];
  RW uint32_t CPACR;                  /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
} Z20_SCBType;

/**
  @brief  Structure type to access the System Timer (SysTick).
 */
typedef struct
{
  RW uint32_t CTRL;                   /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  RW uint32_t LOAD;                   /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
  RW uint32_t VAL;                    /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
  RO uint32_t CALIB;                  /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
} Z20_SysTickType;

/**
 * @brief  Structure type to access the Nested Vectored Interrupt Controller (NVIC).
 */
typedef struct
{
  RW uint32_t ISER[8U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
     uint32_t RESERVED0[24U];
  RW uint32_t ICER[8U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
     uint32_t RSERVED1[24U];
  RW uint32_t ISPR[8U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
     uint32_t RESERVED2[24U];
  RW uint32_t ICPR[8U];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
     uint32_t RESERVED3[24U];
  RW uint32_t IABR[8U];               /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
     uint32_t RESERVED4[56U];
  RW uint8_t  IP[240U];               /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
     uint32_t RESERVED5[644U];
  WO uint32_t STIR;                   /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
}Z20_NVICType;

/**
  @brief  Structure type to access the Data Watchpoint and Trace Register (DWT).
 */
typedef struct
{
  RW uint32_t CTRL;                   /*!< Offset: 0x000 (R/W)  Control Register */
  RW uint32_t CYCCNT;                 /*!< Offset: 0x004 (R/W)  Cycle Count Register */
  RW uint32_t CPICNT;                 /*!< Offset: 0x008 (R/W)  CPI Count Register */
  RW uint32_t EXCCNT;                 /*!< Offset: 0x00C (R/W)  Exception Overhead Count Register */
  RW uint32_t SLEEPCNT;               /*!< Offset: 0x010 (R/W)  Sleep Count Register */
  RW uint32_t LSUCNT;                 /*!< Offset: 0x014 (R/W)  LSU Count Register */
  RW uint32_t FOLDCNT;                /*!< Offset: 0x018 (R/W)  Folded-instruction Count Register */
  RO uint32_t PCSR;                   /*!< Offset: 0x01C (R/ )  Program Counter Sample Register */
  RW uint32_t COMP0;                  /*!< Offset: 0x020 (R/W)  Comparator Register 0 */
  RW uint32_t MASK0;                  /*!< Offset: 0x024 (R/W)  Mask Register 0 */
  RW uint32_t FUNCTION0;              /*!< Offset: 0x028 (R/W)  Function Register 0 */
     uint32_t RESERVED0[1U];
  RW uint32_t COMP1;                  /*!< Offset: 0x030 (R/W)  Comparator Register 1 */
  RW uint32_t MASK1;                  /*!< Offset: 0x034 (R/W)  Mask Register 1 */
  RW uint32_t FUNCTION1;              /*!< Offset: 0x038 (R/W)  Function Register 1 */
     uint32_t RESERVED1[1U];
  RW uint32_t COMP2;                  /*!< Offset: 0x040 (R/W)  Comparator Register 2 */
  RW uint32_t MASK2;                  /*!< Offset: 0x044 (R/W)  Mask Register 2 */
  RW uint32_t FUNCTION2;              /*!< Offset: 0x048 (R/W)  Function Register 2 */
     uint32_t RESERVED2[1U];
  RW uint32_t COMP3;                  /*!< Offset: 0x050 (R/W)  Comparator Register 3 */
  RW uint32_t MASK3;                  /*!< Offset: 0x054 (R/W)  Mask Register 3 */
  RW uint32_t FUNCTION3;              /*!< Offset: 0x058 (R/W)  Function Register 3 */
} Z20_DWTType;

/**
  @brief  Structure type to access the Core Debug Register (CoreDebug).
 */
typedef struct
{
  RW uint32_t DHCSR;                  /*!< Offset: 0x000 (R/W)  Debug Halting Control and Status Register */
  WO uint32_t DCRSR;                  /*!< Offset: 0x004 ( /W)  Debug Core Register Selector Register */
  RW uint32_t DCRDR;                  /*!< Offset: 0x008 (R/W)  Debug Core Register Data Register */
  RW uint32_t DEMCR;                  /*!< Offset: 0x00C (R/W)  Debug Exception and Monitor Control Register */
} Z20_CoreDebugType;

/**
  @brief  Structure type to access the Floating Point Unit (FPU).
 */
typedef struct
{
     uint32_t RESERVED0[1U];
  RW uint32_t FPCCR;                  /*!< Offset: 0x004 (R/W)  Floating-Point Context Control Register */
  RW uint32_t FPCAR;                  /*!< Offset: 0x008 (R/W)  Floating-Point Context Address Register */
  RW uint32_t FPDSCR;                 /*!< Offset: 0x00C (R/W)  Floating-Point Default Status Control Register */
  RO uint32_t MVFR0;                  /*!< Offset: 0x010 (R/ )  Media and FP Feature Register 0 */
  RO uint32_t MVFR1;                  /*!< Offset: 0x014 (R/ )  Media and FP Feature Register 1 */
} Z20_FPUType;

/* Memory mapping of Core Hardware */
#define Z20_SCS_BASE            (0xE000E000UL)                            /*!< System Control Space Base Address */
#define Z20_ITM_BASE            (0xE0000000UL)                            /*!< ITM Base Address */
#define Z20_DWT_BASE            (0xE0001000UL)                            /*!< DWT Base Address */
#define Z20_CORE_DEBUG_BASE     (0xE000EDF0UL)                            /*!< Core Debug Base Address */
#define Z20_SYSTICK_BASE        (Z20_SCS_BASE +  0x0010UL)                    /*!< SysTick Base Address */
#define Z20_NVIC_BASE           (Z20_SCS_BASE +  0x0100UL)                    /*!< NVIC Base Address */
#define Z20_SCB_BASE            (Z20_SCS_BASE +  0x0D00UL)                    /*!< System Control Block Base Address */

#define Z20_SCnSCB              ((Z20_SCnSCBType    *)     Z20_SCS_BASE      )   /*!< System control Register not in SCB */
#define Z20_SCB                 ((Z20_SCBType       *)     Z20_SCB_BASE      )   /*!< SCB configuration struct */
#define Z20_SYSTICK             ((Z20_SysTickType   *)     Z20_SYSTICK_BASE  )   /*!< SysTick configuration struct */
#define Z20_NVIC                ((Z20_NVICType      *)     Z20_NVIC_BASE     )   /*!< NVIC configuration struct */
#define Z20_DWT                 ((Z20_DWTType       *)     Z20_DWT_BASE      )   /*!< DWT configuration struct */
#define Z20_CORE_DEBUG          ((Z20_CoreDebugType *)     Z20_CORE_DEBUG_BASE)  /*!< Core Debug configuration struct */
#define Z20_FPU_BASE            (Z20_SCS_BASE +  0x0F30UL)                       /*!< Floating Point Unit */
#define Z20_FPU                 ((Z20_FPUType       *)     Z20_FPU_BASE     )    /*!< Floating Point Unit */

/**
 * Peripheral Register Defination
 */
struct adc_reg {
    /* 0x000*/
    uint32_t zResverd0x000;
    /* 0x004*/
    struct {
           uint32_t RSVD_7_0                : 8;  /* [7:0]          ro         */
           uint32_t FIFO_SIZE               : 8;  /* [15:8]         ro         */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } ADC_PARAM;

    /* 0x008*/
    struct {
           uint32_t ADC_EN                  : 1;  /* [0]            r/w        */
           uint32_t RSVD_1                  : 1;  /* [1]            ro         */
           uint32_t RST                     : 1;  /* [2]            r/w        */
           uint32_t DOZEN                   : 1;  /* [3]            r/w        */
           uint32_t TRIG_MODE_ENABLE        : 1;  /* [4]            r/w        */
           uint32_t TRIG_MODE               : 1;  /* [5]            r/w        */
           uint32_t MODE1_RST               : 1;  /* [6]            r/w        */
           uint32_t LMD                     : 3;  /* [9:7]          r/w        */
           uint32_t IREF_SEL                : 1;  /* [10]           r/w        */
           uint32_t STABLE_T                :11;  /* [21:11]        r/w        */
           uint32_t RSVD_31_22              :10;  /* [31:22]        ro         */
    } ADC_CTRL;

    /* 0x00C*/
    struct {
           uint32_t FWM_INT                 : 1;  /* [0]            w1c        */
           uint32_t FOF                     : 1;  /* [1]            w1c        */
           uint32_t TCOMP_INT               : 1;  /* [2]            w1c        */
           uint32_t CMP_INT                 : 1;  /* [3]            w1c        */
           uint32_t DMA_REQ                 : 1;  /* [4]            ro         */
           uint32_t RDY                     : 1;  /* [5]            ro         */
           uint32_t RSVD_6                  : 1;  /* [6]            ro         */
           uint32_t ADC_ACTIVE              : 1;  /* [7]            ro         */
           uint32_t LSI                     : 1;  /* [8]            ro         */
           uint32_t TC_ERR                  : 1;  /* [9]            ro         */
           uint32_t RSVD_31_10              :22;  /* [31:10]        ro         */
    } ADC_STAT;

    /* 0x010*/
    struct {
           uint32_t FWM_IE                  : 1;  /* [0]            r/w        */
           uint32_t FOF_IE                  : 1;  /* [1]            r/w        */
           uint32_t TCOM_IE                 : 1;  /* [2]            r/w        */
           uint32_t CMP_IE                  : 1;  /* [3]            r/w        */
           uint32_t FWMDE                   : 1;  /* [4]            r/w        */
           uint32_t ERR_INT_IE              : 1;  /* [5]            r/w        */
           uint32_t RSVD_31_6               :26;  /* [31:6]         ro         */
    } ADC_IE;

    /* 0x014*/
    struct {
           uint32_t DIFF_MODE               : 1;  /* [0]            r/w        */
           uint32_t CHSELP                  : 5;  /* [5:1]          r/w        */
           uint32_t CHSELN                  : 2;  /* [7:6]          r/w        */
           uint32_t RSVD_10_8               : 3;  /* [10:8]         ro         */
           uint32_t CTYPE                   : 1;  /* [11]           r/w        */
           uint32_t CMPS                    : 3;  /* [14:12]        r/w        */
           uint32_t HWT_EN                  : 1;  /* [15]           r/w        */
           uint32_t REF_SEL                 : 1;  /* [16]           r/w        */
           uint32_t RES                     : 2;  /* [18:17]        r/w        */
           uint32_t AVGS                    : 3;  /* [21:19]        r/w        */
           uint32_t STS                     :10;  /* [31:22]        r/w        */
    } ADC_CFG;

    /* 0x018*/
    struct {
           uint32_t CVL                     :12;  /* [11:0]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t CVH                     :12;  /* [27:16]        r/w        */
           uint32_t RSVD_31_28              : 4;  /* [31:28]        ro         */
    } ADC_CV;

    uint8_t zResverd0x01C[4];   /*pad 0x01C - 01F*/

    /* 0x020*/
    struct {
           uint32_t ADC_DATA_RD             :17;  /* [16:0]         ro         */
           uint32_t RSVD_31_17              :15;  /* [31:17]        ro         */
    } ADC_DATA_RD;

    /* 0x024*/
    struct {
           uint32_t FCOUNT                  : 5;  /* [4:0]          ro         */
           uint32_t RSVD_15_5               :11;  /* [15:5]         ro         */
           uint32_t FWMARK                  : 4;  /* [19:16]        r/w        */
           uint32_t FDRD                    : 5;  /* [24:20]        r/w        */
           uint32_t RSVD_31_25              : 7;  /* [31:25]        ro         */
    } ADC_FCTRL;

    /* 0x028*/
    struct {
           uint32_t ADC_SWTRIG              : 1;  /* [0]            wo         */
           uint32_t RSVD_31_1               :31;  /* [31:1]         ro         */
    } ADC_SWTRIG;

    uint8_t zResverd0x02C[4];   /*pad 0x02C - 02F*/

    /* 0x030*/
    struct {
           uint32_t CMD0                    : 5;  /* [4:0]          r/w        */
           uint32_t CMD0_INT_EN             : 1;  /* [5]            r/w        */
           uint32_t RSVD_7_6                : 2;  /* [7:6]          ro         */
           uint32_t CMD1                    : 5;  /* [12:8]         r/w        */
           uint32_t CMD1_INT_EN             : 1;  /* [13]           r/w        */
           uint32_t RSVD_15_14              : 2;  /* [15:14]        ro         */
           uint32_t CMD2                    : 5;  /* [20:16]        r/w        */
           uint32_t CMD2_INT_EN             : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t CMD3                    : 5;  /* [28:24]        r/w        */
           uint32_t CMD3_INT_EN             : 1;  /* [29]           r/w        */
           uint32_t RSVD_31_30              : 2;  /* [31:30]        ro         */
    } ADC_CMD_BUFF0;

    /* 0x034*/
    struct {
           uint32_t CMD4                    : 5;  /* [4:0]          r/w        */
           uint32_t CMD4_INT_EN             : 1;  /* [5]            r/w        */
           uint32_t RSVD_7_6                : 2;  /* [7:6]          ro         */
           uint32_t CMD5                    : 5;  /* [12:8]         r/w        */
           uint32_t CMD5_INT_EN             : 1;  /* [13]           r/w        */
           uint32_t RSVD_31_14              :18;  /* [31:14]        ro         */
    } ADC_CMD_BUFF1;

};    /*adc_reg*/

struct adc_reg_w {
    /* 0x000*/
    uint32_t zResverd0x000;
    /* 0x004*/
    uint32_t ADC_PARAM;
    /* 0x008*/
    uint32_t ADC_CTRL;
    /* 0x00C*/
    uint32_t ADC_STAT;
    /* 0x010*/
    uint32_t ADC_IE;
    /* 0x014*/
    uint32_t ADC_CFG;
    /* 0x018*/
    uint32_t ADC_CV;
    uint8_t zResverd0x01C[4];   /*pad 0x01C - 01F*/

    /* 0x020*/
    uint32_t ADC_DATA_RD;
    /* 0x024*/
    uint32_t ADC_FCTRL;
    /* 0x028*/
    uint32_t ADC_SWTRIG;
    uint8_t zResverd0x02C[4];   /*pad 0x02C - 02F*/

    /* 0x030*/
    uint32_t ADC_CMD_BUFF0;
    /* 0x034*/
    uint32_t ADC_CMD_BUFF1;
};    /*adc_reg*/

typedef volatile struct adc_reg adc_reg_t;
typedef volatile struct adc_reg_w adc_reg_w_t;

struct aes_reg {
    /* 0x0000*/
    uint32_t zResverd0x0000;
    /* 0x0004*/
    struct {
           uint32_t R                       : 1;  /* [0]            ro         */
           uint32_t ERR                     : 8;  /* [8:1]          ro         */
           uint32_t RSVD_31_9               :23;  /* [31:9]         ro         */
    } AES_STATUS;

    /* 0x0008*/
    struct {
           uint32_t S                       : 1;  /* [0]            wo         */
           uint32_t RND                     : 4;  /* [4:1]          wo         */
           uint32_t RSVD_31_5               :27;  /* [31:5]         ro         */
    } AES_CONTROL;

    /* 0x000c*/
    struct {
           uint32_t CD                      : 1;  /* [0]            wo         */
           uint32_t KSS                     : 2;  /* [2:1]          wo         */
           uint32_t RSVD_3                  : 1;  /* [3]            ro         */
           uint32_t RSVD_7_4                : 4;  /* [7:4]          ro         */
           uint32_t MODE                    : 8;  /* [15:8]         wo         */
           uint32_t BS                      : 8;  /* [23:16]        wo         */
           uint32_t ALGO                    : 8;  /* [31:24]        wo         */
    } AES_CONFIG;

    uint8_t zResverd0x010[12];   /*pad 0x010 - 01B*/

    /* 0x001c*/
    struct {
           uint32_t DATA_I                  :32;  /* [31:0]         wo         */
    } AES_DATA_I0;

    /* 0x0020*/
    struct {
           uint32_t DATA_I                  :32;  /* [31:0]         wo         */
    } AES_DATA_I1;

    /* 0x0024*/
    struct {
           uint32_t DATA_I                  :32;  /* [31:0]         wo         */
    } AES_DATA_I2;

    /* 0x0028*/
    struct {
           uint32_t DATA_I                  :32;  /* [31:0]         wo         */
    } AES_DATA_I3;

    /* 0x002c*/
    struct {
           uint32_t DATA_O                  :32;  /* [31:0]         ro         */
    } AES_DATA_O0;

    /* 0x0030*/
    struct {
           uint32_t DATA_O                  :32;  /* [31:0]         ro         */
    } AES_DATA_O1;

    /* 0x0034*/
    struct {
           uint32_t DATA_O                  :32;  /* [31:0]         ro         */
    } AES_DATA_O2;

    /* 0x0038*/
    struct {
           uint32_t DATA_O                  :32;  /* [31:0]         ro         */
    } AES_DATA_O3;

    /* 0x003c*/
    struct {
           uint32_t KEY0                    :32;  /* [31:0]         r/w        */
    } AES_KEY0;

    /* 0x0040*/
    struct {
           uint32_t KEY1                    :32;  /* [31:0]         r/w        */
    } AES_KEY1;

    /* 0x0044*/
    struct {
           uint32_t KEY2                    :32;  /* [31:0]         r/w        */
    } AES_KEY2;

    /* 0x0048*/
    struct {
           uint32_t KEY3                    :32;  /* [31:0]         r/w        */
    } AES_KEY3;

    uint8_t zResverd0x04C[16];   /*pad 0x04C - 05B*/

    /* 0x005c*/
    struct {
           uint32_t IV0                     :32;  /* [31:0]         wo         */
    } AES_IV0;

    /* 0x0060*/
    struct {
           uint32_t IV1                     :32;  /* [31:0]         wo         */
    } AES_IV1;

    /* 0x0064*/
    struct {
           uint32_t IV2                     :32;  /* [31:0]         wo         */
    } AES_IV2;

    /* 0x0068*/
    struct {
           uint32_t IV3                     :32;  /* [31:0]         wo         */
    } AES_IV3;

};    /*aes_reg*/

struct aes_reg_w {
    /* 0x0000*/
    uint32_t zResverd0x0000;
    /* 0x0004*/
    uint32_t AES_STATUS;
    /* 0x0008*/
    uint32_t AES_CONTROL;
    /* 0x000c*/
    uint32_t AES_CONFIG;
    uint8_t zResverd0x010[12];   /*pad 0x010 - 01B*/

    /* 0x001c*/
    uint32_t AES_DATA_I0;
    /* 0x0020*/
    uint32_t AES_DATA_I1;
    /* 0x0024*/
    uint32_t AES_DATA_I2;
    /* 0x0028*/
    uint32_t AES_DATA_I3;
    /* 0x002c*/
    uint32_t AES_DATA_O0;
    /* 0x0030*/
    uint32_t AES_DATA_O1;
    /* 0x0034*/
    uint32_t AES_DATA_O2;
    /* 0x0038*/
    uint32_t AES_DATA_O3;
    /* 0x003c*/
    uint32_t AES_KEY0;
    /* 0x0040*/
    uint32_t AES_KEY1;
    /* 0x0044*/
    uint32_t AES_KEY2;
    /* 0x0048*/
    uint32_t AES_KEY3;
    uint8_t zResverd0x04C[16];   /*pad 0x04C - 05B*/

    /* 0x005c*/
    uint32_t AES_IV0;
    /* 0x0060*/
    uint32_t AES_IV1;
    /* 0x0064*/
    uint32_t AES_IV2;
    /* 0x0068*/
    uint32_t AES_IV3;
};    /*aes_reg*/

typedef volatile struct aes_reg aes_reg_t;
typedef volatile struct aes_reg_w aes_reg_w_t;

struct can_reg {
    /* 0x00*/
    struct {
       uint32_t MAXMB                   : 7;  /* [6:0]          r/w        */
       uint32_t RSVD_7                  : 1;  /* [7]            ro         */
       uint32_t IDAM                    : 2;  /* [9:8]          r/w        */
       uint32_t RSVD_10                 : 1;  /* [10]           ro         */
       uint32_t FDEN                    : 1;  /* [11]           r/w        */
       uint32_t AEN                     : 1;  /* [12]           r/w        */
       uint32_t LPRIOEN                 : 1;  /* [13]           r/w        */
       uint32_t PNET_EN                 : 1;  /* [14]           r/w        */
       uint32_t DMAE                    : 1;  /* [15]           r/w        */
       uint32_t IRMQ                    : 1;  /* [16]           r/w        */
       uint32_t SRXDIS                  : 1;  /* [17]           r/w        */
       uint32_t DOZE                    : 1;  /* [18]           r/w        */
       uint32_t WAKSRC                  : 1;  /* [19]           r/w        */
       uint32_t LPMACK                  : 1;  /* [20]           ro         */
       uint32_t WRNEN                   : 1;  /* [21]           r/w        */
       uint32_t SLFWAK                  : 1;  /* [22]           r/w        */
       uint32_t SUPV                    : 1;  /* [23]           r/w        */
       uint32_t FRZACK                  : 1;  /* [24]           ro         */
       uint32_t SOFTRST                 : 1;  /* [25]           r/w        */
       uint32_t WAKMSK                  : 1;  /* [26]           r/w        */
       uint32_t NOTRDY                  : 1;  /* [27]           ro         */
       uint32_t HALT                    : 1;  /* [28]           r/w        */
       uint32_t RFEN                    : 1;  /* [29]           r/w        */
       uint32_t FRZ                     : 1;  /* [30]           r/w        */
       uint32_t MDIS                    : 1;  /* [31]           r/w        */
    } CAN_MCR;

    /* 0x04*/
    struct {
       uint32_t PROPSEG                 : 3;  /* [2:0]          r/w        */
       uint32_t LOM                     : 1;  /* [3]            r/w        */
       uint32_t LBUF                    : 1;  /* [4]            r/w        */
       uint32_t TSYC                    : 1;  /* [5]            r/w        */
       uint32_t BOFFREC                 : 1;  /* [6]            r/w        */
       uint32_t SMP                     : 1;  /* [7]            r/w        */
       uint32_t RSVD_9_8                : 2;  /* [9:8]          ro         */
       uint32_t RWRNMSK                 : 1;  /* [10]           r/w        */
       uint32_t TWRNMSK                 : 1;  /* [11]           r/w        */
       uint32_t LPB                     : 1;  /* [12]           r/w        */
       uint32_t RSVD_13                 : 1;  /* [13]           ro         */
       uint32_t ERRMSK                  : 1;  /* [14]           r/w        */
       uint32_t BOFFMSK                 : 1;  /* [15]           r/w        */
       uint32_t PSEG2                   : 3;  /* [18:16]        r/w        */
       uint32_t PSEG1                   : 3;  /* [21:19]        r/w        */
       uint32_t RJW                     : 2;  /* [23:22]        r/w        */
       uint32_t PRESDIV                 : 8;  /* [31:24]        r/w        */
    } CAN_CTRL1;

    /* 0x08*/
    struct {
       uint32_t TIMER                   :16;  /* [15:0]         r/w        */
       uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } CAN_TIMER;

    uint8_t zResverd0x0C[4];   /*pad 0x0C - 0F*/

    /* 0x10*/
    struct {
       uint32_t MG                      :32;  /* [31:0]         r/w        */
    } CAN_RXMGMSK;

    /* 0x14*/
    struct {
       uint32_t RX14M                   :32;  /* [31:0]         r/w        */
    } CAN_RX14MASK;

    /* 0x18*/
    struct {
       uint32_t RX15M                   :32;  /* [31:0]         r/w        */
    } CAN_RX15MASK;

    /* 0x1c*/
    struct {
       uint32_t TXERRCNT                : 8;  /* [7:0]          r/w        */
       uint32_t RXERRCNT                : 8;  /* [15:8]         r/w        */
       uint32_t TX_ERRCNT_FAST          : 8;  /* [23:16]        r/w        */
       uint32_t RX_ERRCNT_FAST          : 8;  /* [31:24]        r/w        */
    } CAN_ECR;

    /* 0x20*/
    struct {
       uint32_t WAKINT                  : 1;  /* [0]            w1c        */
       uint32_t ERRINT                  : 1;  /* [1]            w1c        */
       uint32_t BOFFINT                 : 1;  /* [2]            w1c        */
       uint32_t RX                      : 1;  /* [3]            ro         */
       uint32_t FLTCONF                 : 2;  /* [5:4]          ro         */
       uint32_t TX                      : 1;  /* [6]            ro         */
       uint32_t IDLE                    : 1;  /* [7]            ro         */
       uint32_t RXWRN                   : 1;  /* [8]            ro         */
       uint32_t TXWRN                   : 1;  /* [9]            ro         */
       uint32_t STFERR                  : 1;  /* [10]           ro         */
       uint32_t FRAMERR                 : 1;  /* [11]           ro         */
       uint32_t CRCERR                  : 1;  /* [12]           ro         */
       uint32_t ACKERR                  : 1;  /* [13]           ro         */
       uint32_t BIT0ERR                 : 1;  /* [14]           ro         */
       uint32_t BIT1ERR                 : 1;  /* [15]           ro         */
       uint32_t RWRNINT                 : 1;  /* [16]           ro         */
       uint32_t TWRNINT                 : 1;  /* [17]           ro         */
       uint32_t SYNCH                   : 1;  /* [18]           ro         */
       uint32_t BUSOFFDONEINT           : 1;  /* [19]           w1c        */
       uint32_t ERRINT_FAST             : 1;  /* [20]           w1c        */
       uint32_t ERROVR                  : 1;  /* [21]           w1c        */
       uint32_t RSVD_25_22              : 4;  /* [25:22]        ro         */
       uint32_t STFERR_FAST             : 1;  /* [26]           ro         */
       uint32_t FRAMERR_FAST            : 1;  /* [27]           ro         */
       uint32_t CRCERR_FAST             : 1;  /* [28]           ro         */
       uint32_t RSVD_29                 : 1;  /* [29]           ro         */
       uint32_t BIT0ERR_FAST            : 1;  /* [30]           ro         */
       uint32_t BIT1ERR_FAST            : 1;  /* [31]           ro         */
    } CAN_ESR1;

    /* 0x24*/
    struct {
       uint32_t BUF63TO32M              :32;  /* [31:0]         r/w        */
    } CAN_IMASK2;

    /* 0x28*/
    struct {
       uint32_t BUF31TO0M               :32;  /* [31:0]         r/w        */
    } CAN_IMASK1;

    /* 0x2c*/
    struct {
       uint32_t BUF63TO32I              :32;  /* [31:0]         r/w        */
    } CAN_IFLAG2;

    /* 0x30*/
    struct {
       uint32_t BUF0I                   : 1;  /* [0]            w1c        */
       uint32_t BUF4TO1I                : 4;  /* [4:1]          w1c        */
       uint32_t BUF5I                   : 1;  /* [5]            w1c        */
       uint32_t BUF6I                   : 1;  /* [6]            w1c        */
       uint32_t BUF7I                   : 1;  /* [7]            w1c        */
       uint32_t BUF31TO8I               :24;  /* [31:8]         w1c        */
    } CAN_IFLAG1;

    /* 0x34*/
    struct {
       uint32_t RSVD_10_0               :11;  /* [10:0]         ro         */
       uint32_t EDFLTDIS                : 1;  /* [11]           r/w        */
       uint32_t ISOCANFDEN              : 1;  /* [12]           r/w        */
       uint32_t RSVD_13                 : 1;  /* [13]           ro         */
       uint32_t PREXCEN                 : 1;  /* [14]           r/w        */
       uint32_t TIMER_SRC               : 1;  /* [15]           r/w        */
       uint32_t EACEN                   : 1;  /* [16]           r/w        */
       uint32_t RRS                     : 1;  /* [17]           r/w        */
       uint32_t MRP                     : 1;  /* [18]           r/w        */
       uint32_t TASD                    : 5;  /* [23:19]        r/w        */
       uint32_t RFFN                    : 4;  /* [27:24]        r/w        */
       uint32_t WRMFRZ                  : 1;  /* [28]           r/w        */
       uint32_t ECRWRE                  : 1;  /* [29]           r/w        */
       uint32_t BOFFDONEMSK             : 1;  /* [30]           r/w        */
       uint32_t ERRMASK_FAST            : 1;  /* [31]           r/w        */
    } CAN_CTRL2;

    /* 0x38*/
    struct {
       uint32_t RSVD_12_0               :13;  /* [12:0]         ro         */
       uint32_t IMB                     : 1;  /* [13]           ro         */
       uint32_t VPS                     : 1;  /* [14]           ro         */
       uint32_t RSVD_15                 : 1;  /* [15]           ro         */
       uint32_t LPTM                    : 7;  /* [22:16]        ro         */
       uint32_t RSVD_31_23              : 9;  /* [31:23]        ro         */
    } CAN_ESR2;

    uint8_t zResverd0x03C[8];   /*pad 0x03C - 043*/

    /* 0x44*/
    struct {
       uint32_t TXCRC                   :15;  /* [14:0]         ro         */
       uint32_t RSVD_15                 : 1;  /* [15]           ro         */
       uint32_t MBCRC                   : 7;  /* [22:16]        ro         */
       uint32_t RSVD_31_23              : 9;  /* [31:23]        ro         */
    } CAN_CRCR;

    /* 0x48*/
    struct {
       uint32_t FGM                     :32;  /* [31:0]         r/w        */
    } CAN_RXFGMASK;

    /* 0x4c*/
    struct {
       uint32_t IDHIT                   : 9;  /* [8:0]          ro         */
       uint32_t RSVD_31_9               :23;  /* [31:9]         ro         */
    } CAN_RXFIR;

    /* 0x50*/
    struct {
       uint32_t EPSEG2                  : 5;  /* [4:0]          r/w        */
       uint32_t EPSEG1                  : 5;  /* [9:5]          r/w        */
       uint32_t EPROPSEG                : 6;  /* [15:10]        r/w        */
       uint32_t ERJW                    : 5;  /* [20:16]        r/w        */
       uint32_t EPRESDIV                :10;  /* [30:21]        r/w        */
       uint32_t BTF                     : 1;  /* [31]           r/w        */
    } CAN_CBT;

    uint8_t zResverd0x054[20];   /*pad 0x054 - 067*/

    /* 0x68*/
    struct {
       uint32_t BUF127TO96M             :32;  /* [31:0]         r/w        */
    } CAN_IMASK4;

    /* 0x6c*/
    struct {
       uint32_t BUF95TO64M              :32;  /* [31:0]         r/w        */
    } CAN_IMASK3;

    /* 0x70*/
    struct {
       uint32_t BUF127TO96I             :32;  /* [31:0]         w1c        */
    } CAN_IFLAG4;

    /* 0x74*/
    struct {
       uint32_t BUF95TO64I              :32;  /* [31:0]         w1c        */
    } CAN_IFLAG3;

    uint8_t zResverd0x078[8];   /*pad 0x078 - 07F*/

    /* 0x80 */
    struct {
    struct {
           uint32_t TIME_STAMP              :16;  /* [15:0]         r/w        */
           uint32_t DLC                     : 4;  /* [19:16]        r/w        */
           uint32_t RTR                     : 1;  /* [20]           r/w        */
           uint32_t IDE                     : 1;  /* [21]           r/w        */
           uint32_t SRR                     : 1;  /* [22]           r/w        */
           uint32_t RSVD_23                 : 1;  /* [23]           ro         */
           uint32_t CODE                    : 4;  /* [27:24]        r/w        */
           uint32_t RSVD_28                 : 1;  /* [28]           ro         */
           uint32_t ESI                     : 1;  /* [29]           r/w        */
           uint32_t BRS                     : 1;  /* [30]           r/w        */
           uint32_t EDL                     : 1;  /* [31]           r/w        */
    } CS;

    /* 0x84*/
    struct {
           uint32_t ID_EXT                  :18;  /* [17:0]         r/w        */
           uint32_t ID_STD_EXT              :11;  /* [28:18]        r/w        */
           uint32_t PRIO                    : 3;  /* [31:29]        ro         */
    } ID;

    /* 0x88*/
    struct {
           uint32_t DATA_BYTE03             :32;  /* [31:0]         r/w        */
    } DATA03;

    /* 0x8c*/
    struct {
           uint32_t DATA_BYTE47             :32;  /* [31:0]         r/w        */
    } DATA47;
    } CAN_MB[128];

    /* 0x880*/
    struct {
           uint32_t MI                      :32;  /* [31:0]         r/w        */
    } CAN_RXIMR[128];

    uint8_t zResverd0x0A80[96];   /*pad 0x0A80 - 0ADF*/

    /* 0xAE0*/
    struct {
       uint32_t RSVD_6_0                : 7;  /* [6:0]          ro         */
       uint32_t NCEFAFRZ                : 1;  /* [7]            r/w        */
       uint32_t ECCDIS                  : 1;  /* [8]            r/w        */
       uint32_t RERRDIS                 : 1;  /* [9]            r/w        */
       uint32_t RSVD_12_10              : 3;  /* [12:10]        ro         */
       uint32_t EXTERRIE                : 1;  /* [13]           r/w        */
       uint32_t FAERRIE                 : 1;  /* [14]           r/w        */
       uint32_t HAERRI                  : 1;  /* [15]           r/w        */
       uint32_t CEI_MSK                 : 1;  /* [16]           r/w        */
       uint32_t RSVD_17                 : 1;  /* [17]           ro         */
       uint32_t FANCEI_MSK              : 1;  /* [18]           r/w        */
       uint32_t HANCEI_MSK              : 1;  /* [19]           r/w        */
       uint32_t RSVD_30_20              :11;  /* [30:20]        ro         */
       uint32_t ECRWRDIS                : 1;  /* [31]           r/w        */
    } CAN_MECR;

    /* 0xAE4*/
    struct {
       uint32_t INJADDR_L               : 2;  /* [1:0]          ro         */
       uint32_t INJADDR_H               :12;  /* [13:2]         r/w        */
       uint32_t RSVD_31_14              :18;  /* [31:14]        ro         */
    } CAN_ERRIAR;

    /* 0xAE8*/
    struct {
       uint32_t DFLIP                   :32;  /* [31:0]         r/w        */
    } CAN_ERRIDPR;

    /* 0xAEC*/
    struct {
       uint32_t PFLIP0                  : 5;  /* [4:0]          r/w        */
       uint32_t RSVD_7_5                : 3;  /* [7:5]          ro         */
       uint32_t PFLIP1                  : 5;  /* [12:8]         r/w        */
       uint32_t RSVD_15_13              : 3;  /* [15:13]        ro         */
       uint32_t PFLIP2                  : 5;  /* [20:16]        r/w        */
       uint32_t RSVD_23_21              : 3;  /* [23:21]        ro         */
       uint32_t PFLIP3                  : 5;  /* [28:24]        r/w        */
       uint32_t RSVD_31_29              : 3;  /* [31:29]        ro         */
    } CAN_ERRIPPR;

    /* 0xAF0*/
    struct {
       uint32_t ERRADDR                 :14;  /* [13:0]         ro         */
       uint32_t RSVD_15_14              : 2;  /* [15:14]        ro         */
       uint32_t SAID                    : 3;  /* [18:16]        ro         */
       uint32_t RSVD_23_19              : 5;  /* [23:19]        ro         */
       uint32_t NCE                     : 1;  /* [24]           ro         */
       uint32_t RSVD_31_25              : 7;  /* [31:25]        ro         */
    } CAN_RERRAR;

    /* 0xAF4*/
    struct {
       uint32_t RDATA                   :32;  /* [31:0]         ro         */
    } CAN_RERRDR;

    /* 0xAF8*/
    struct {
       uint32_t SYND0                   : 5;  /* [4:0]          ro         */
       uint32_t RSVD_6_5                : 2;  /* [6:5]          ro         */
       uint32_t BE0                     : 1;  /* [7]            ro         */
       uint32_t SYND1                   : 5;  /* [12:8]         ro         */
       uint32_t RSVD_14_13              : 2;  /* [14:13]        ro         */
       uint32_t BE1                     : 1;  /* [15]           ro         */
       uint32_t SYND2                   : 5;  /* [20:16]        ro         */
       uint32_t RSVD_22_21              : 2;  /* [22:21]        ro         */
       uint32_t BE2                     : 1;  /* [23]           ro         */
       uint32_t SYND3                   : 5;  /* [28:24]        ro         */
       uint32_t RSVD_30_29              : 2;  /* [30:29]        ro         */
       uint32_t BE3                     : 1;  /* [31]           ro         */
    } CAN_RERRSYNR;

    /* 0xAFC*/
    struct {
       uint32_t CEIOF                   : 1;  /* [0]            w1c        */
       uint32_t RSVD_1                  : 1;  /* [1]            ro         */
       uint32_t FANCEIOF                : 1;  /* [2]            w1c        */
       uint32_t HANCEIOF                : 1;  /* [3]            w1c        */
       uint32_t RSVD_15_4               :12;  /* [15:4]         ro         */
       uint32_t CEIF                    : 1;  /* [16]           w1c        */
       uint32_t RSVD_17                 : 1;  /* [17]           ro         */
       uint32_t FANCEIF                 : 1;  /* [18]           w1c        */
       uint32_t HANCEIF                 : 1;  /* [19]           w1c        */
       uint32_t RSVD_31_20              :12;  /* [31:20]        ro         */
    } CAN_ERRSR;

    /* 0xB00*/
    struct {
       uint32_t FCS                     : 2;  /* [1:0]          r/w        */
       uint32_t IDFS                    : 2;  /* [3:2]          r/w        */
       uint32_t PLFS                    : 2;  /* [5:4]          r/w        */
       uint32_t RSVD_7_6                : 2;  /* [7:6]          ro         */
       uint32_t NMATCH                  : 8;  /* [15:8 ]        r/w        */
       uint32_t WUMF_MSK                : 1;  /* [16]           r/w        */
       uint32_t WTOF_MSK                : 1;  /* [17]           r/w        */
       uint32_t RSVD_31_18              :14;  /* [31:18]        ro         */
    } CAN_CTRL1_PN;

    /* 0xB04*/
    struct {
       uint32_t MATCHTO                 :16;  /* [15:0]         r/w        */
       uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } CAN_CTRL2_PN;

    /* 0xB08*/
    struct {
       uint32_t RSVD_7_0                : 8;  /* [7:0]          ro         */
       uint32_t MCOUNTER                : 8;  /* [15:8]         ro         */
       uint32_t WUMF                    : 1;  /* [16]           w1c        */
       uint32_t WTOF                    : 1;  /* [17]           w1c        */
       uint32_t RSVD_31_18              :14;  /* [31:18]        ro         */
    } CAN_WU_MTC;

    /* 0xB0C*/
    struct {
       uint32_t FLT_ID1                 :29;  /* [28:0]         r/w        */
       uint32_t FLT_RTR                 : 1;  /* [29]           r/w        */
       uint32_t FLT_IDE                 : 1;  /* [30]           r/w        */
       uint32_t RSVD_31                 : 1;  /* [31]           ro         */
    } CAN_FLT_ID1;

    /* 0xB10*/
    struct {
       uint32_t FLT_DLC_HI              : 4;  /* [3:0]          r/w        */
       uint32_t RSVD_15_4               :12;  /* [15:4]         ro         */
       uint32_t FLT_DLC_LO              : 4;  /* [19:16]        r/w        */
       uint32_t RSVD_31_20              :12;  /* [31:20]        ro         */
    } CAN_FLT_DLC;

    /* 0xB14*/
    struct {
       uint32_t DATA_BYTE_3             : 8;  /* [7:0]          r/w        */
       uint32_t DATA_BYTE_2             : 8;  /* [15:8]         r/w        */
       uint32_t DATA_BYTE_1             : 8;  /* [23:16]        r/w        */
       uint32_t DATA_BYTE_0             : 8;  /* [31:24]        r/w        */
    } CAN_PL1_LO;

    /* 0xB18*/
    struct {
       uint32_t DATA_BYTE_7             : 8;  /* [7:0]          r/w        */
       uint32_t DATA_BYTE_6             : 8;  /* [15:8]         r/w        */
       uint32_t DATA_BYTE_5             : 8;  /* [23:16]        r/w        */
       uint32_t DATA_BYTE_4             : 8;  /* [31:24]        r/w        */
    } CAN_PL1_HI;

    /* 0xB1C*/
    struct {
       uint32_t FLT_ID2_IDMASK          :29;  /* [28:0]         r/w        */
       uint32_t RTR_MSK                 : 1;  /* [29]           r/w        */
       uint32_t IDE_MSK                 : 1;  /* [30]           r/w        */
       uint32_t RSVD_31                 : 1;  /* [31]           ro         */
    } CAN_FLT_ID2_IDMASK;

    /* 0xB20*/
    struct {
       uint32_t DATA_BYTE_3             : 8;  /* [7:0]          r/w        */
       uint32_t DATA_BYTE_2             : 8;  /* [15:8]         r/w        */
       uint32_t DATA_BYTE_1             : 8;  /* [23:16]        r/w        */
       uint32_t DATA_BYTE_0             : 8;  /* [31:24]        r/w        */
    } CAN_PL2_PLMASK_LO;

    /* 0xB24*/
    struct {
       uint32_t DATA_BYTE_7             : 8;  /* [7:0]          r/w        */
       uint32_t DATA_BYTE_6             : 8;  /* [15:8]         r/w        */
       uint32_t DATA_BYTE_5             : 8;  /* [23:16]        r/w        */
       uint32_t DATA_BYTE_4             : 8;  /* [31:24]        r/w        */
    } CAN_PL2_PLMASK_HI;

    uint8_t zResverd0x0B28[24];   /*pad 0x0B28 - 0B3F*/

    struct {
    /* 0xB40*/
    struct {
       uint32_t RSVD_15_0               :16;  /* [15:0]         ro         */
       uint32_t DLC                     : 4;  /* [19:16]        ro         */
       uint32_t RTR                     : 1;  /* [20]           ro         */
       uint32_t IDE                     : 1;  /* [21]           ro         */
       uint32_t SRR                     : 1;  /* [22]           ro         */
       uint32_t RSVD_31_23              : 9;  /* [31:23]        ro         */
    } CS;

    /* 0xB44*/
    struct {
       uint32_t ID                      :29;  /* [28:0]         ro         */
       uint32_t RSVD_31_29              : 3;  /* [31:29]        ro         */
    } ID;

    /* 0xB48*/
    struct {
       uint32_t DATA_BYTE_3             : 8;  /* [7:0]          ro         */
       uint32_t DATA_BYTE_2             : 8;  /* [15:8]         ro         */
       uint32_t DATA_BYTE_1             : 8;  /* [23:16]        ro         */
       uint32_t DATA_BYTE_0             : 8;  /* [31:24]        ro         */
    } D03;

    /* 0xB4C*/
    struct {
       uint32_t DATA_BYTE_7             : 8;  /* [7:0]          ro         */
       uint32_t DATA_BYTE_6             : 8;  /* [15:8]         ro         */
       uint32_t DATA_BYTE_5             : 8;  /* [23:16]        ro         */
       uint32_t DATA_BYTE_4             : 8;  /* [31:24]        ro         */
    } D47;
    } CAN_WMB[4];
    
    uint8_t zResverd0x0B80[128];   /*pad 0x0B80 - 0BFF*/

    /* 0xC00*/
    struct {
       uint32_t TDCVAL                  : 6;  /* [5:0]          ro         */
       uint32_t RSVD_7_6                : 2;  /* [7:6]          ro         */
       uint32_t TDCOFF                  : 5;  /* [12:8]         r/w        */
       uint32_t RSVD_13                 : 1;  /* [13]           ro         */
       uint32_t TDCFAIL                 : 1;  /* [14]           w1c        */
       uint32_t TDCEN                   : 1;  /* [15]           r/w        */
       uint32_t MBDSR0                  : 2;  /* [17:16]        r/w        */
       uint32_t RSVD_18                 : 1;  /* [18]           ro         */
       uint32_t MBDSR1                  : 2;  /* [20:19]        r/w        */
       uint32_t RSVD_21                 : 1;  /* [21]           ro         */
       uint32_t MBDSR2                  : 2;  /* [23:22]        r/w        */
       uint32_t RSVD_24                 : 1;  /* [24]           ro         */
       uint32_t MBDSR3                  : 2;  /* [26:25]        r/w        */
       uint32_t RSVD_30_27              : 4;  /* [30:27]        ro         */
       uint32_t FD_RATE                 : 1;  /* [31]           r/w        */
    } CAN_FDCTRL;

    /* 0xC04*/
    struct {
       uint32_t FPSEG2                  : 3;  /* [2:0]          r/w        */
       uint32_t RSVD_4_3                : 2;  /* [4:3]          ro         */
       uint32_t FPSEG1                  : 3;  /* [7:5]          r/w        */
       uint32_t RSVD_9_8                : 2;  /* [9:8]          ro         */
       uint32_t FPROPSEG                : 5;  /* [14:10]        r/w        */
       uint32_t RSVD_15                 : 1;  /* [15]           ro         */
       uint32_t FRJW                    : 3;  /* [18:16]        r/w        */
       uint32_t RSVD_19                 : 1;  /* [19]           ro         */
       uint32_t FPRESDIV                :10;  /* [29:20]        r/w        */
       uint32_t RSVD_31_30              : 2;  /* [31:30]        ro         */
    } CAN_FDCBT;

    /* 0xC08*/
    struct {
       uint32_t FD_TXCRC                :21;  /* [20:0]         ro         */
       uint32_t RSVD_23_21              : 3;  /* [23:21]        ro         */
       uint32_t FD_MBCRC                : 7;  /* [30:24]        ro         */
       uint32_t RSVD_31                 : 1;  /* [31]           ro         */
    } CAN_FDCRC;

};    /*can_reg*/

struct can_reg_w {
    /* 0x00*/
    uint32_t CAN_MCR;
    /* 0x04*/
    uint32_t CAN_CTRL1;
    /* 0x08*/
    uint32_t CAN_TIMER;
    uint8_t zResverd0x0C[4];   /*pad 0x0C - 0F*/

    /* 0x10*/
    uint32_t CAN_RXMGMSK;
    /* 0x14*/
    uint32_t CAN_RX14MASK;
    /* 0x18*/
    uint32_t CAN_RX15MASK;
    /* 0x1c*/
    uint32_t CAN_ECR;
    /* 0x20*/
    uint32_t CAN_ESR1;
    /* 0x24*/
    uint32_t CAN_IMASK2;
    /* 0x28*/
    uint32_t CAN_IMASK1;
    /* 0x2c*/
    uint32_t CAN_IFLAG2;
    /* 0x30*/
    uint32_t CAN_IFLAG1;
    /* 0x34*/
    uint32_t CAN_CTRL2;
    /* 0x38*/
    uint32_t CAN_ESR2;
    uint8_t zResverd0x03C[8];   /*pad 0x03C - 043*/

    /* 0x44*/
    uint32_t CAN_CRCR;
    /* 0x48*/
    uint32_t CAN_RXFGMASK;
    /* 0x4c*/
    uint32_t CAN_RXFIR;
    /* 0x50*/
    uint32_t CAN_CBT;
    uint8_t zResverd0x054[20];   /*pad 0x054 - 067*/

    /* 0x68*/
    uint32_t CAN_IMASK4;
    /* 0x6c*/
    uint32_t CAN_IMASK3;
    /* 0x70*/
    uint32_t CAN_IFLAG4;
    /* 0x74*/
    uint32_t CAN_IFLAG3;
    uint8_t zResverd0x078[8];   /*pad 0x078 - 07F*/

    struct {
    /* 0x80 */
    uint32_t CS;
    /* 0x84*/
    uint32_t ID;
    /* 0x88*/
    uint32_t DATA03;
    /* 0x8c*/
    uint32_t DATA47;
    } CAN_MB[128];

    /* 0x880*/
    uint32_t CAN_RXIMR[128];
    uint8_t zResverd0x0A80[96];   /*pad 0x0A80 - 0ADF*/

    /* 0xAE0*/
    uint32_t CAN_MECR;
    /* 0xAE4*/
    uint32_t CAN_ERRIAR;
    /* 0xAE8*/
    uint32_t CAN_ERRIDPR;
    /* 0xAEC*/
    uint32_t CAN_ERRIPPR;
    /* 0xAF0*/
    uint32_t CAN_RERRAR;
    /* 0xAF4*/
    uint32_t CAN_RERRDR;
    /* 0xAF8*/
    uint32_t CAN_RERRSYNR;
    /* 0xAFC*/
    uint32_t CAN_ERRSR;
    /* 0xB00*/
    uint32_t CAN_CTRL1_PN;
    /* 0xB04*/
    uint32_t CAN_CTRL2_PN;
    /* 0xB08*/
    uint32_t CAN_WU_MTC;
    /* 0xB0C*/
    uint32_t CAN_FLT_ID1;
    /* 0xB10*/
    uint32_t CAN_FLT_DLC;
    /* 0xB14*/
    uint32_t CAN_PL1_LO;
    /* 0xB18*/
    uint32_t CAN_PL1_HI;
    /* 0xB1C*/
    uint32_t CAN_FLT_ID2_IDMASK;
    /* 0xB20*/
    uint32_t CAN_PL2_PLMASK_LO;
    /* 0xB24*/
    uint32_t CAN_PL2_PLMASK_HI;
    
    uint8_t zResverd0x0B28[24];   /*pad 0x0B28 - 0B3F*/
    struct {
    /* 0xB40*/
    uint32_t CS;
    /* 0xB44*/
    uint32_t ID;
    /* 0xB48*/
    uint32_t D03;
    /* 0xB4C*/
    uint32_t D47;
    } CAN_WMB[4];
    
    uint8_t zResverd0x0B80[128];   /*pad 0x0B80 - 0BFF*/

    /* 0xC00*/
    uint32_t CAN_FDCTRL;
    /* 0xC04*/
    uint32_t CAN_FDCBT;
    /* 0xC08*/
    uint32_t CAN_FDCRC;
};    /*can_reg*/

typedef volatile struct can_reg can_reg_t;
typedef volatile struct can_reg_w can_reg_w_t;

struct cmp_reg {
    /* 0x0*/
    uint32_t zResverd0x0;
    /* 0x4*/
    struct {
           uint32_t DAC_RES                 : 4;  /* [3:0]          ro         */
           uint32_t RSVD_31_4               :28;  /* [31:4]         ro         */
    } CMP_PARAM;

    /* 0x8*/
    struct {
           uint32_t CMP_SEL                 : 1;  /* [0]            r/w        */
           uint32_t CMP_EN                  : 1;  /* [1]            r/w        */
           uint32_t SOC_TRG_EN              : 1;  /* [2]            r/w        */
           uint32_t STOP_EN                 : 1;  /* [3]            r/w        */
           uint32_t RSVD_31_4               :28;  /* [31:4]         ro         */
    } CMP_CCR0;

    /* 0xC*/
    struct {
           uint32_t WINDOW_EN               : 1;  /* [0]            r/w        */
           uint32_t SAMPLE_EN               : 1;  /* [1]            r/w        */
           uint32_t DMA_EN                  : 1;  /* [2]            r/w        */
           uint32_t COUT_INV                : 1;  /* [3]            r/w        */
           uint32_t COUT_SEL                : 1;  /* [4]            r/w        */
           uint32_t COUT_PEN                : 1;  /* [5]            r/w        */
           uint32_t COUT_OWE                : 1;  /* [6]            r/w        */
           uint32_t COUT_OW                 : 1;  /* [7]            r/w        */
           uint32_t RSVD_15_8               : 8;  /* [15:8]         ro         */
           uint32_t FILT_CNT                : 3;  /* [18:16]        r/w        */
           uint32_t RSVD_23_19              : 5;  /* [23:19]        ro         */
           uint32_t FILT_PER                : 8;  /* [31:24]        r/w        */
    } CMP_CCR1;

    /* 0x10*/
    struct {
           uint32_t HS_HSTCTR               : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t LS_HSTCTR               : 2;  /* [5:4]          r/w        */
           uint32_t RSVD_15_6               :10;  /* [15:6]         ro         */
           uint32_t HS_PSEL                 : 4;  /* [19:16]        r/w        */
           uint32_t HS_MSEL                 : 4;  /* [23:20]        r/w        */
           uint32_t LS_PSEL                 : 4;  /* [27:24]        r/w        */
           uint32_t LS_MSEL                 : 4;  /* [31:28]        r/w        */
    } CMP_CCR2;

    /* 0x14*/
    struct {
           uint32_t DAC_EN                  : 1;  /* [0]            r/w        */
           uint32_t DAC_BUFF_EN             : 1;  /* [1]            r/w        */
           uint32_t RSVD_7_2                : 6;  /* [7:2]          ro         */
           uint32_t VREF_SEL                : 1;  /* [8]            r/w        */
           uint32_t RSVD_15_9               : 7;  /* [15:9]         ro         */
           uint32_t DAC_SEL                 : 8;  /* [23:16]        r/w        */
           uint32_t RSVD_31_24              : 8;  /* [31:24]        ro         */
    } CMP_DCR;

    /* 0x18*/
    struct {
           uint32_t CFR_IE                  : 1;  /* [0]            r/w        */
           uint32_t CFF_IE                  : 1;  /* [1]            r/w        */
           uint32_t RSVD_31_2               :30;  /* [31:2]         ro         */
    } CMP_IER;

    /* 0x1C*/
    struct {
           uint32_t CFR                     : 1;  /* [0]            w1c        */
           uint32_t CFF                     : 1;  /* [1]            w1c        */
           uint32_t RSVD_7_2                : 6;  /* [7:2]          ro         */
           uint32_t COUT                    : 1;  /* [8]            ro         */
           uint32_t RSVD_31_9               :23;  /* [31:9]         ro         */
    } CMP_CSR;

};    /*cmp_reg*/

struct cmp_reg_w {
    /* 0x0*/
    uint32_t zResverd0x0;
    /* 0x4*/
    uint32_t CMP_PARAM;
    /* 0x8*/
    uint32_t CMP_CCR0;
    /* 0xC*/
    uint32_t CMP_CCR1;
    /* 0x10*/
    uint32_t CMP_CCR2;
    /* 0x14*/
    uint32_t CMP_DCR;
    /* 0x18*/
    uint32_t CMP_IER;
    /* 0x1C*/
    uint32_t CMP_CSR;
};    /*cmp_reg*/

typedef volatile struct cmp_reg cmp_reg_t;
typedef volatile struct cmp_reg_w cmp_reg_w_t;

struct cmu_reg {
    /* 0x0*/
    uint32_t zResverd0x0;
    /* 0x4*/
    struct {
           uint32_t RST_IMP                 : 1;  /* [0]            ro         */
           uint32_t RSVD_31_1               :31;  /* [31:1]         ro         */
    } CMU_PARAM;

    /* 0x8*/
    struct {
           uint32_t CME                     : 1;  /* [0]            r/w        */
           uint32_t RSVD_3_1                : 3;  /* [3:1]          ro         */
           uint32_t CMMD                    : 1;  /* [4]            r/w        */
           uint32_t RSVD_7_5                : 3;  /* [7:5]          ro         */
           uint32_t FAHTRSTE                : 1;  /* [8]            r/w        */
           uint32_t FBLTRSTE                : 1;  /* [9]            r/w        */
           uint32_t RSVD_15_10              : 6;  /* [15:10]        ro         */
           uint32_t FAHTIE                  : 1;  /* [16]           r/w        */
           uint32_t FBLTIE                  : 1;  /* [17]           r/w        */
           uint32_t RSVD_30_18              :13;  /* [30:18]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } CMU_CTRL;

    /* 0xC*/
    struct {
           uint32_t MONST                   : 2;  /* [1:0]          ro         */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t STARTMEA                : 1;  /* [4]            r/w        */
           uint32_t RSVD_15_5               :11;  /* [15:5]         ro         */
           uint32_t FAHTIF                  : 1;  /* [16]           w1c        */
           uint32_t FBLTIF                  : 1;  /* [17]           w1c        */
           uint32_t RSVD_31_18              :14;  /* [31:18]        ro         */
    } CMU_STAT;

    /* 0x10*/
    struct {
           uint32_t MONWIN                  :32;  /* [31:0]         r/w        */
    } CMU_MONWIN;

    /* 0x14*/
    struct {
           uint32_t HCT4INT                 :32;  /* [31:0]         r/w        */
    } CMU_CUMHCT4INT;

    /* 0x18*/
    struct {
           uint32_t LCT4INT                 :32;  /* [31:0]         r/w        */
    } CMU_CUMLCT4INT;

    /* 0x1C*/
    struct {
           uint32_t HCT4RST                 :32;  /* [31:0]         r/w        */
    } CMU_CUMHCT4RST;

    /* 0x20*/
    struct {
           uint32_t LCT4RST                 :32;  /* [31:0]         r/w        */
    } CMU_CUMLCT4RST;

    /* 0x24*/
    struct {
           uint32_t MEARSLT                 :32;  /* [31:0]         ro         */
    } CMU_CUMMEARSLT;

};    /*cmu_reg*/

struct cmu_reg_w {
    /* 0x0*/
    uint32_t zResverd0x0;
    /* 0x4*/
    uint32_t CMU_PARAM;
    /* 0x8*/
    uint32_t CMU_CTRL;
    /* 0xC*/
    uint32_t CMU_STAT;
    /* 0x10*/
    uint32_t CMU_MONWIN;
    /* 0x14*/
    uint32_t CMU_CUMHCT4INT;
    /* 0x18*/
    uint32_t CMU_CUMLCT4INT;
    /* 0x1C*/
    uint32_t CMU_CUMHCT4RST;
    /* 0x20*/
    uint32_t CMU_CUMLCT4RST;
    /* 0x24*/
    uint32_t CMU_CUMMEARSLT;
};    /*cmu_reg*/

typedef volatile struct cmu_reg cmu_reg_t;
typedef volatile struct cmu_reg_w cmu_reg_w_t;

struct crc_reg {
    /* 0x0*/
    uint32_t zResverd0x0;
    /* 0x4*/
    struct {
           uint32_t RSVD_31_0               :32;  /* [31:0]         ro         */
    } CRC_PARAM;

    /* 0x8*/
    struct {
           uint32_t BYTE0                   : 8;  /* [7:0]          r/w        */
           uint32_t BYTE1                   : 8;  /* [15:8]         r/w        */
           uint32_t BYTE2                   : 8;  /* [23:16]        r/w        */
           uint32_t BYTE3                   : 8;  /* [31:24]        r/w        */
    } CRC_DATA;

    /* 0xC*/
    struct {
           uint32_t LPHW                    :16;  /* [15:0]         r/w        */
           uint32_t HPHW                    :16;  /* [31:16]        r/w        */
    } CRC_POLY;

    /* 0x10*/
    struct {
           uint32_t MODE                    : 1;  /* [0]            r/w        */
           uint32_t WS                      : 1;  /* [1]            r/w        */
           uint32_t CR                      : 1;  /* [2]            r/w        */
           uint32_t RSVD_3                  : 1;  /* [3]            ro         */
           uint32_t RT                      : 2;  /* [5:4]          r/w        */
           uint32_t WT                      : 2;  /* [7:6]          r/w        */
           uint32_t RSVD_31_8               :24;  /* [31:8]         ro         */
    } CRC_CTRL;

};    /*crc_reg*/

struct crc_reg_w {
    /* 0x0*/
    uint32_t zResverd0x0;
    /* 0x4*/
    uint32_t CRC_PARAM;
    /* 0x8*/
    uint32_t CRC_DATA;
    /* 0xC*/
    uint32_t CRC_POLY;
    /* 0x10*/
    uint32_t CRC_CTRL;
};    /*crc_reg*/

typedef volatile struct crc_reg crc_reg_t;
typedef volatile struct crc_reg_w crc_reg_w_t;

struct dma_chmux_reg {
    /* 0x00*/
    struct {
           uint32_t ENABLE                  : 1;  /* [0]            r/w        */
           uint32_t SRC_MUX                 : 7;  /* [7:1]          r/w        */
           uint32_t RSVD_31_8               :24;  /* [31:8]         ro         */
    } DMA_MUX_CH_CFG[16];

};    /*dma_chmux_reg*/

struct dma_chmux_reg_w {
    /* 0x00*/
    uint32_t DMA_MUX_CH_CFG[16];
};    /*dma_chmux_reg*/

typedef volatile struct dma_chmux_reg dma_chmux_reg_t;
typedef volatile struct dma_chmux_reg_w dma_chmux_reg_w_t;

struct dma_reg {
    /* 0x00*/
    struct {
           uint32_t HALT                    : 1;  /* [0]            r/w        */
           uint32_t HOEE                    : 1;  /* [1]            r/w        */
           uint32_t RRCAE                   : 1;  /* [2]            r/w        */
           uint32_t DBGE                    : 1;  /* [3]            r/w        */
           uint32_t RSVD_5_4                : 2;  /* [5:4]          ro         */
           uint32_t BUSY                    : 1;  /* [6]            ro         */
           uint32_t RSVD_31_7               :25;  /* [31:7]         ro         */
    } DMA_CONF;

    /* 0x04*/
    struct {
           uint32_t DMAE0                   : 1;  /* [0]            r/w        */
           uint32_t DMAE1                   : 1;  /* [1]            r/w        */
           uint32_t DMAE2                   : 1;  /* [2]            r/w        */
           uint32_t DMAE3                   : 1;  /* [3]            r/w        */
           uint32_t DMAE4                   : 1;  /* [4]            r/w        */
           uint32_t DMAE5                   : 1;  /* [5]            r/w        */
           uint32_t DMAE6                   : 1;  /* [6]            r/w        */
           uint32_t DMAE7                   : 1;  /* [7]            r/w        */
           uint32_t DMAE8                   : 1;  /* [8]            r/w        */
           uint32_t DMAE9                   : 1;  /* [9]            r/w        */
           uint32_t DMAE10                  : 1;  /* [10]           r/w        */
           uint32_t DMAE11                  : 1;  /* [11]           r/w        */
           uint32_t DMAE12                  : 1;  /* [12]           r/w        */
           uint32_t DMAE13                  : 1;  /* [13]           r/w        */
           uint32_t DMAE14                  : 1;  /* [14]           r/w        */
           uint32_t DMAE15                  : 1;  /* [15]           r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } DMA_DMAE;

    uint8_t zResverd0x08[4];   /*pad 0x08 - 0B*/

    /* 0x0C*/
    struct {
           uint32_t EIE0                    : 1;  /* [0]            r/w        */
           uint32_t EIE1                    : 1;  /* [1]            r/w        */
           uint32_t EIE2                    : 1;  /* [2]            r/w        */
           uint32_t EIE3                    : 1;  /* [3]            r/w        */
           uint32_t EIE4                    : 1;  /* [4]            r/w        */
           uint32_t EIE5                    : 1;  /* [5]            r/w        */
           uint32_t EIE6                    : 1;  /* [6]            r/w        */
           uint32_t EIE7                    : 1;  /* [7]            r/w        */
           uint32_t EIE8                    : 1;  /* [8]            r/w        */
           uint32_t EIE9                    : 1;  /* [9]            r/w        */
           uint32_t EIE10                   : 1;  /* [10]           r/w        */
           uint32_t EIE11                   : 1;  /* [11]           r/w        */
           uint32_t EIE12                   : 1;  /* [12]           r/w        */
           uint32_t EIE13                   : 1;  /* [13]           r/w        */
           uint32_t EIE14                   : 1;  /* [14]           r/w        */
           uint32_t EIE15                   : 1;  /* [15]           r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } DMA_EIE;

    uint8_t zResverd0x010[4];   /*pad 0x010 - 013*/

    /* 0x14*/
    struct {
           uint32_t CCDONE                  : 4;  /* [3:0]          wo         */
           uint32_t RSVD_5_4                : 2;  /* [5:4]          ro         */
           uint32_t CACDONE                 : 1;  /* [6]            wo         */
           uint32_t WPEN0                   : 1;  /* [7]            wo         */
           uint32_t SCSTART                 : 4;  /* [11:8]         wo         */
           uint32_t RSVD_13_12              : 2;  /* [13:12]        ro         */
           uint32_t SACSTART                : 1;  /* [14]           wo         */
           uint32_t WPEN1                   : 1;  /* [15]           wo         */
           uint32_t CCES                    : 4;  /* [19:16]        wo         */
           uint32_t RSVD_21_20              : 2;  /* [21:20]        ro         */
           uint32_t CACES                   : 1;  /* [22]           wo         */
           uint32_t WPEN2                   : 1;  /* [23]           wo         */
           uint32_t CCIS                    : 4;  /* [27:24]        wo         */
           uint32_t RSVD_29_28              : 2;  /* [29:28]        ro         */
           uint32_t CACIS                   : 1;  /* [30]           wo         */
           uint32_t WPEN3                   : 1;  /* [31]           wo         */
    } DMA_GCC;

    /* 0x18*/
    struct {
           uint32_t DBEF                    : 1;  /* [0]            ro         */
           uint32_t SBEF                    : 1;  /* [1]            ro         */
           uint32_t RSVD_2                  : 1;  /* [2]            ro         */
           uint32_t NUMEF                   : 1;  /* [3]            ro         */
           uint32_t DOEF                    : 1;  /* [4]            ro         */
           uint32_t DAEF                    : 1;  /* [5]            ro         */
           uint32_t SOEF                    : 1;  /* [6]            ro         */
           uint32_t SAEF                    : 1;  /* [7]            ro         */
           uint32_t CHEF                    : 4;  /* [11:8]         ro         */
           uint32_t RSVD_12                 : 1;  /* [12]           ro         */
           uint32_t PRIEF                   : 1;  /* [13]           ro         */
           uint32_t RSVD_14                 : 1;  /* [14]           ro         */
           uint32_t ERRF                    : 1;  /* [15]           ro         */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } DMA_ES;

    /* 0x1C*/
    struct {
           uint32_t ERR0                    : 1;  /* [0]            ro         */
           uint32_t ERR1                    : 1;  /* [1]            ro         */
           uint32_t ERR2                    : 1;  /* [2]            ro         */
           uint32_t ERR3                    : 1;  /* [3]            ro         */
           uint32_t ERR4                    : 1;  /* [4]            ro         */
           uint32_t ERR5                    : 1;  /* [5]            ro         */
           uint32_t ERR6                    : 1;  /* [6]            ro         */
           uint32_t ERR7                    : 1;  /* [7]            ro         */
           uint32_t ERR8                    : 1;  /* [8]            ro         */
           uint32_t ERR9                    : 1;  /* [9]            ro         */
           uint32_t ERR10                   : 1;  /* [10]           ro         */
           uint32_t ERR11                   : 1;  /* [11]           ro         */
           uint32_t ERR12                   : 1;  /* [12]           ro         */
           uint32_t ERR13                   : 1;  /* [13]           ro         */
           uint32_t ERR14                   : 1;  /* [14]           ro         */
           uint32_t ERR15                   : 1;  /* [15]           ro         */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } DMA_CES;

    /* 0x20*/
    struct {
           uint32_t INT0                    : 1;  /* [0]            ro         */
           uint32_t INT1                    : 1;  /* [1]            ro         */
           uint32_t INT2                    : 1;  /* [2]            ro         */
           uint32_t INT3                    : 1;  /* [3]            ro         */
           uint32_t INT4                    : 1;  /* [4]            ro         */
           uint32_t INT5                    : 1;  /* [5]            ro         */
           uint32_t INT6                    : 1;  /* [6]            ro         */
           uint32_t INT7                    : 1;  /* [7]            ro         */
           uint32_t INT8                    : 1;  /* [8]            ro         */
           uint32_t INT9                    : 1;  /* [9]            ro         */
           uint32_t INT10                   : 1;  /* [10]           ro         */
           uint32_t INT11                   : 1;  /* [11]           ro         */
           uint32_t INT12                   : 1;  /* [12]           ro         */
           uint32_t INT13                   : 1;  /* [13]           ro         */
           uint32_t INT14                   : 1;  /* [14]           ro         */
           uint32_t INT15                   : 1;  /* [15]           ro         */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } DMA_CIS;

    /* 0x24*/
    struct {
           uint32_t HRS0                    : 1;  /* [0]            ro         */
           uint32_t HRS1                    : 1;  /* [1]            ro         */
           uint32_t HRS2                    : 1;  /* [2]            ro         */
           uint32_t HRS3                    : 1;  /* [3]            ro         */
           uint32_t HRS4                    : 1;  /* [4]            ro         */
           uint32_t HRS5                    : 1;  /* [5]            ro         */
           uint32_t HRS6                    : 1;  /* [6]            ro         */
           uint32_t HRS7                    : 1;  /* [7]            ro         */
           uint32_t HRS8                    : 1;  /* [8]            ro         */
           uint32_t HRS9                    : 1;  /* [9]            ro         */
           uint32_t HRS10                   : 1;  /* [10]           ro         */
           uint32_t HRS11                   : 1;  /* [11]           ro         */
           uint32_t HRS12                   : 1;  /* [12]           ro         */
           uint32_t HRS13                   : 1;  /* [13]           ro         */
           uint32_t HRS14                   : 1;  /* [14]           ro         */
           uint32_t HRS15                   : 1;  /* [15]           ro         */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } DMA_CHRS;

    /* 0x28*/
    struct {
           uint32_t CPRI3                   : 4;  /* [3:0]          r/w        */
           uint32_t RSVD_5_4                : 2;  /* [5:4]          ro         */
           uint32_t CPDIS3                  : 1;  /* [6]            r/w        */
           uint32_t CSE3                    : 1;  /* [7]            r/w        */
           uint32_t CPRI2                   : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_13_12              : 2;  /* [13:12]        ro         */
           uint32_t CPDIS2                  : 1;  /* [14]           r/w        */
           uint32_t CSE2                    : 1;  /* [15]           r/w        */
           uint32_t CPRI1                   : 4;  /* [19:16]        r/w        */
           uint32_t RSVD_21_20              : 2;  /* [21:20]        ro         */
           uint32_t CPDIS1                  : 1;  /* [22]           r/w        */
           uint32_t CSE1                    : 1;  /* [23]           r/w        */
           uint32_t CPRI0                   : 4;  /* [27:24]        r/w        */
           uint32_t RSVD_29_28              : 2;  /* [29:28]        ro         */
           uint32_t CPDIS0                  : 1;  /* [30]           r/w        */
           uint32_t CSE0                    : 1;  /* [31]           r/w        */
    } DMA_CPRI0;

    /* 0x2C*/
    struct {
           uint32_t CPRI7                   : 4;  /* [3:0]          r/w        */
           uint32_t RSVD_5_4                : 2;  /* [5:4]          ro         */
           uint32_t CPDIS7                  : 1;  /* [6]            r/w        */
           uint32_t CSE7                    : 1;  /* [7]            r/w        */
           uint32_t CPRI6                   : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_13_12              : 2;  /* [13:12]        ro         */
           uint32_t CPDIS6                  : 1;  /* [14]           r/w        */
           uint32_t CSE6                    : 1;  /* [15]           r/w        */
           uint32_t CPRI5                   : 4;  /* [19:16]        r/w        */
           uint32_t RSVD_21_20              : 2;  /* [21:20]        ro         */
           uint32_t CPDIS5                  : 1;  /* [22]           r/w        */
           uint32_t CSE5                    : 1;  /* [23]           r/w        */
           uint32_t CPRI4                   : 4;  /* [27:24]        r/w        */
           uint32_t RSVD_29_28              : 2;  /* [29:28]        ro         */
           uint32_t CPDIS4                  : 1;  /* [30]           r/w        */
           uint32_t CSE4                    : 1;  /* [31]           r/w        */
    } DMA_CPRI1;

    /* 0x30*/
    struct {
           uint32_t CPRI11                  : 4;  /* [3:0]          r/w        */
           uint32_t RSVD_5_4                : 2;  /* [5:4]          ro         */
           uint32_t CPDIS11                 : 1;  /* [6]            r/w        */
           uint32_t CSE11                   : 1;  /* [7]            r/w        */
           uint32_t CPRI10                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_13_12              : 2;  /* [13:12]        ro         */
           uint32_t CPDIS10                 : 1;  /* [14]           r/w        */
           uint32_t CSE10                   : 1;  /* [15]           r/w        */
           uint32_t CPRI9                   : 4;  /* [19:16]        r/w        */
           uint32_t RSVD_21_20              : 2;  /* [21:20]        ro         */
           uint32_t CPDIS9                  : 1;  /* [22]           r/w        */
           uint32_t CSE9                    : 1;  /* [23]           r/w        */
           uint32_t CPRI8                   : 4;  /* [27:24]        r/w        */
           uint32_t RSVD_29_28              : 2;  /* [29:28]        ro         */
           uint32_t CPDIS8                  : 1;  /* [30]           r/w        */
           uint32_t CSE8                    : 1;  /* [31]           r/w        */
    } DMA_CPRI2;

    /* 0x34*/
    struct {
           uint32_t CPRI15                  : 4;  /* [3:0]          r/w        */
           uint32_t RSVD_5_4                : 2;  /* [5:4]          ro         */
           uint32_t CPDIS15                 : 1;  /* [6]            r/w        */
           uint32_t CSE15                   : 1;  /* [7]            r/w        */
           uint32_t CPRI14                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_13_12              : 2;  /* [13:12]        ro         */
           uint32_t CPDIS14                 : 1;  /* [14]           r/w        */
           uint32_t CSE14                   : 1;  /* [15]           r/w        */
           uint32_t CPRI13                  : 4;  /* [19:16]        r/w        */
           uint32_t RSVD_21_20              : 2;  /* [21:20]        ro         */
           uint32_t CPDIS13                 : 1;  /* [22]           r/w        */
           uint32_t CSE13                   : 1;  /* [23]           r/w        */
           uint32_t CPRI12                  : 4;  /* [27:24]        r/w        */
           uint32_t RSVD_29_28              : 2;  /* [29:28]        ro         */
           uint32_t CPDIS12                 : 1;  /* [30]           r/w        */
           uint32_t CSE12                   : 1;  /* [31]           r/w        */
    } DMA_CPRI3;

    uint8_t zResverd0x038[456];   /*pad 0x038 - 01FF*/

    struct {
        /* 0x200*/
        struct {
            uint32_t SADDR                 : 32;  /* [31:0]         r/w        */
        } DMA_SADDR;

        /* 0x204*/
        struct {
            uint32_t DADDR                 : 32;  /* [31:0]         r/w        */
        } DMA_DADDR;

        /* 0x208*/
        struct {
            int32_t SAOFF                  : 16;  /* [15:0]         r/w        */
            int32_t DAOFF                  : 16;  /* [31:16]        r/w        */
        } DMA_AOFF;

        /* 0x20C*/
        struct {
            int32_t MLSAOFF                : 16;  /* [15:0]         r/w        */
            int32_t MLDAOFF                : 16;  /* [31:16]        r/w        */
        } DMA_MLAOFF;

        /* 0x210*/
        struct {
            uint32_t NUM                   : 32;  /* [31:0]         r/w        */
        } DMA_NUM;

        /* 0x214*/
        struct {
            uint32_t MLITER                : 16;  /* [15:0]         r/w        */
            uint32_t MLSTA                 : 16;  /* [31:16]        ro         */
        } DMA_ITER;

        /* 0x218*/
        struct {
            uint32_t START                 : 1;  /* [0]            r/w        */
            uint32_t INTE                  : 1;  /* [1]            r/w        */
            uint32_t RSVD_2                : 1;  /* [2]            ro         */
            uint32_t REQDIS                : 1;  /* [3]            r/w        */
            uint32_t RSVD_5_4              : 2;  /* [5:4]          ro         */
            uint32_t BUSY                  : 1;  /* [6]            ro         */
            uint32_t DONE                  : 1;  /* [7]            r/w        */
            uint32_t RSVD_15_8             : 8;  /* [15:8]         ro         */
            uint32_t DSIZE                 : 2;  /* [17:16]        r/w        */
            uint32_t RSVD_23_18            : 6;  /* [23:18]        ro         */
            uint32_t SSIZE                 : 2;  /* [25:24]        r/w        */
            uint32_t RSVD_31_26            : 6;  /* [31:26]        ro         */
        } DMA_CS;

        uint8_t zResverd[4];   /*pad 4 bytes*/
    }DMA_CH_CONFIG[16];
};    /*dma_reg*/

struct dma_reg_w {
    /* 0x00*/
    uint32_t DMA_CONF;
    /* 0x04*/
    uint32_t DMA_DMAE;
    uint8_t zResverd0x08[4];   /*pad 0x08 - 0B*/

    /* 0x0C*/
    uint32_t DMA_EIE;
    uint8_t zResverd0x010[4];   /*pad 0x010 - 013*/

    /* 0x14*/
    uint32_t DMA_GCC;
    /* 0x18*/
    uint32_t DMA_ES;
    /* 0x1C*/
    uint32_t DMA_CES;
    /* 0x20*/
    uint32_t DMA_CIS;
    /* 0x24*/
    uint32_t DMA_CHRS;
    /* 0x28*/
    uint32_t DMA_CPRI0;
    /* 0x2C*/
    uint32_t DMA_CPRI1;
    /* 0x30*/
    uint32_t DMA_CPRI2;
    /* 0x34*/
    uint32_t DMA_CPRI3;
    uint8_t zResverd0x038[456];   /*pad 0x038 - 01FF*/

    struct {
        /* 0x200*/
        uint32_t DMA_SADDR;
        /* 0x204*/
        uint32_t DMA_DADDR;
        /* 0x208*/
        uint32_t DMA_AOFF;
        /* 0x20C*/
        uint32_t DMA_MLAOFF;
        /* 0x210*/
        uint32_t DMA_NUM;
        /* 0x214*/
        uint32_t DMA_ITER;
        /* 0x218*/
        uint32_t DMA_CS;

        uint8_t zResverd[4];   /*pad 4 bytes*/
    } DMA_CH_CONFIG[16];
};    /*dma_reg*/

typedef volatile struct dma_reg dma_reg_t;
typedef volatile struct dma_reg_w dma_reg_w_t;

struct eiru_reg {
    /* 0x00*/
    struct {
           uint32_t SRAM0_ER_DIS            : 1;  /* [0]            r/w        */
           uint32_t SRAM0_EW_DIS            : 1;  /* [1]            r/w        */
           uint32_t SRAM0_ESB_DIS           : 1;  /* [2]            r/w        */
           uint32_t SRAM0_EMB_DIS           : 1;  /* [3]            r/w        */
           uint32_t SRAM0_EEI_EN            : 1;  /* [4]            r/w        */
           uint32_t RSVD_7_5                : 3;  /* [7:5]          ro         */
           uint32_t SRAM1_ER_DIS            : 1;  /* [8]            r/w        */
           uint32_t SRAM1_EW_DIS            : 1;  /* [9]            r/w        */
           uint32_t SRAM1_ESB_DIS           : 1;  /* [10]           r/w        */
           uint32_t SRAM1_EMB_DIS           : 1;  /* [11]           r/w        */
           uint32_t SRAM1_EEI_EN            : 1;  /* [12]           r/w        */
           uint32_t RSVD_30_13              :18;  /* [30:13]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } EIRU_CR;

    /* 0x04*/
    struct {
           uint32_t RSVD_1_0                : 2;  /* [1:0]          ro         */
           uint32_t EEIADDR                 :30;  /* [31:2]         r/w        */
    } EIRU_EEIADDR;

    uint8_t zResverd0x08[8];   /*pad 0x08 - 0F*/

    struct {
        /* 0x10*/
        struct {
                uint32_t EFPROT                  : 4;  /* [3:0]          ro         */
                uint32_t EFSIZE                  : 3;  /* [6:4]          ro         */
                uint32_t RSVD_7                  : 1;  /* [7]            ro         */
                uint32_t EFMST                   : 8;  /* [15:8]         ro         */
                uint32_t RSVD_28_16              :13;  /* [28:16]        ro         */
                uint32_t SBERR                   : 1;  /* [29]           w1c        */
                uint32_t MBERR                   : 1;  /* [30]           w1c        */
                uint32_t OVERRUN                 : 1;  /* [31]           w1c        */
        } EIRU_SRAMn_EESR;

        /* 0x14*/
        struct {
                uint32_t EFADDR                  :32;  /* [31:0]         ro         */
        } EIRU_SRAMn_FADDR;

        /* 0x18*/
        struct {
                uint32_t EFDATA                  :32;  /* [31:0]         ro         */
        } EIRU_SRAMn_FDATA;

        /* 0x1C*/
        struct {
                uint32_t ECCMASK                 : 7;  /* [6:0]          r/w        */
                uint32_t RSVD_31_7               :25;  /* [31:7]         ro         */
        } EIRU_SRAMn_ECCMASK;

        /* 0x20*/
        struct {
                uint32_t DATAMASK                :32;  /* [31:0]         r/w        */
        } EIRU_SRAMn_DATAMASK;
        
        uint8_t zResverd0x024[12];   /*pad 0x24 - 2F*/
    }EIRU_SRAMn_SC[2];

};    /*eiru_reg*/

struct eiru_reg_w {
    /* 0x00*/
    uint32_t EIRU_CR;
    /* 0x04*/
    uint32_t EIRU_EEIADDR;
    uint8_t zResverd0x08[8];   /*pad 0x08 - 0F*/
    struct {
            /* 0x10*/
            uint32_t EIRU_SRAMn_EESR;
            /* 0x14*/
            uint32_t EIRU_SRAMn_FADDR;
            /* 0x18*/
            uint32_t EIRU_SRAMn_FDATA;
            /* 0x1C*/
            uint32_t EIRU_SRAMn_ECCMASK;
            /* 0x20*/
            uint32_t EIRU_SRAMn_DATAMASK;          
            uint8_t zResverd0x024[12];   /*pad 0x24 - 2F*/
    }EIRU_SRAMn_SC[2];
}; /*eiru_reg*/

typedef volatile struct eiru_reg eiru_reg_t;
typedef volatile struct eiru_reg_w eiru_reg_w_t;


struct ewdt_reg {
    /* 0x0*/
    uint32_t zResverd0x0;
    /* 0x4*/
    struct {
           uint32_t RSVD_31_0               :32;  /* [31:0]         ro         */
    } EWDT_PARAM;

    /* 0x8*/
    struct {
           uint32_t EWDTE                   : 1;  /* [0]            r/w        */
           uint32_t DEBUGE                  : 1;  /* [1]            r/w        */
           uint32_t WAITE                   : 1;  /* [2]            r/w        */
           uint32_t RSVD_3                  : 1;  /* [3]            ro         */
           uint32_t INTE                    : 1;  /* [4]            r/w        */
           uint32_t INPE                    : 1;  /* [5]            r/w        */
           uint32_t INPP                    : 1;  /* [6]            r/w        */
           uint32_t RSVD_23_7               :17;  /* [23:7]         ro         */
           uint32_t INTF                    : 1;  /* [24]           w1c        */
           uint32_t RSVD_31_25              : 7;  /* [31:25]        ro         */
    } EWDT_CS;

    /* 0xC*/
    struct {
           uint32_t COMPH                   :32;  /* [31:0]         r/w        */
    } EWDT_COMPH;

    /* 0x10*/
    struct {
           uint32_t COMPL                   :32;  /* [31:0]         r/w        */
    } EWDT_COMPL;

    /* 0x14*/
    struct {
           uint32_t CNT                     :32;  /* [31:0]         r/w        */
    } EWDT_CNT;

};    /*ewdt_reg*/

struct ewdt_reg_w {
    /* 0x0*/
    uint32_t zResverd0x0;
    /* 0x4*/
    uint32_t EWDT_PARAM;
    /* 0x8*/
    uint32_t EWDT_CS;
    /* 0xC*/
    uint32_t EWDT_COMPH;
    /* 0x10*/
    uint32_t EWDT_COMPL;
    /* 0x14*/
    uint32_t EWDT_CNT;
};    /*ewdt_reg*/

typedef volatile struct ewdt_reg ewdt_reg_t;
typedef volatile struct ewdt_reg_w ewdt_reg_w_t;

struct flash_reg {
    /* 0x0*/
    struct {
           uint32_t FAIL                    : 1;  /* [0]            ro         */
           uint32_t RSVD_1                  : 1;  /* [1]            ro         */
           uint32_t CMDABT                  : 1;  /* [2]            w1c        */
           uint32_t RSVD_4_3                : 2;  /* [4:3]          ro         */
           uint32_t ACCERR                  : 1;  /* [5]            w1c        */
           uint32_t PREABT                  : 1;  /* [6]            w1c        */
           uint32_t CCIF                    : 1;  /* [7]            w1c        */
           uint32_t RSVD_10_8               : 3;  /* [10:8]         ro         */
           uint32_t CMDWRF                  : 1;  /* [11]           ro         */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t DFDIF                   : 1;  /* [16]           w1c        */
           uint32_t SFDIF                   : 1;  /* [17]           w1c        */
           uint32_t RSVD_29_18              :12;  /* [29:18]        ro         */
           uint32_t DBG_ERSALL_DIS          : 1;  /* [30]           ro         */
           uint32_t FSEC                    : 1;  /* [31]           ro         */
    } FLASH_FSTAT;

    /* 0x4*/
    struct {
           uint32_t BK_QUERY                : 1;  /* [0]            r/w        */
           uint32_t RSVD_6_1                : 6;  /* [6:1]          ro         */
           uint32_t CCIE                    : 1;  /* [7]            r/w        */
           uint32_t DBG_ERS_FLG             : 1;  /* [8]            ro         */
           uint32_t RSVD_15_9               : 7;  /* [15:9]         ro         */
           uint32_t DFDIE                   : 1;  /* [16]           r/w        */
           uint32_t SFDIE                   : 1;  /* [17]           r/w        */
           uint32_t RSVD_31_18              :14;  /* [31:18]        ro         */
    } FLASH_FCNFG;

    /* 0x8*/
    struct {
           uint32_t RWSC                    : 4;  /* [3:0]          r/w        */
           uint32_t RSVD_7_4                : 4;  /* [7:4]          ro         */
           uint32_t LSMODE                  : 1;  /* [8]            r/w        */
           uint32_t RSVD_15_9               : 7;  /* [15:9]         ro         */
           uint32_t FECCF                   : 1;  /* [16]           r/w        */
           uint32_t RSVD_23_17              : 7;  /* [23:17]        ro         */
           uint32_t ABTREQ                  : 1;  /* [24]           r/w        */
           uint32_t RSVD_31_25              : 7;  /* [31:25]        ro         */
    } FLASH_FCTRL;

    uint8_t zResverd0x0C[4];   /*pad 0x0C - 0F*/

    /* 0x10*/
    struct {
           uint32_t CMDCODE                 : 8;  /* [7:0]          r/w        */
           uint32_t RSVD_31_8               :24;  /* [31:8]         ro         */
    } FLASH_FCMD;

    /* 0x14*/
    uint8_t zResverd0x14[4];  

    /* 0x18*/
    struct {
           uint32_t CMDADDR                 :32;  /* [31:0]         r/w        */
    } FLASH_FADDR;

    /* 0x1C*/
    struct {
           uint32_t CMDADDRE                :32;  /* [31:0]         r/w        */
    } FLASH_FADDR_END;

    /* 0x20*/
    struct {
           uint32_t CMDDATA0                :32;  /* [31:0]         r/w        */
    } FLASH_FDATA0;

    /* 0x24*/
    struct {
           uint32_t CMDDATA1                :32;  /* [31:0]         r/w        */
    } FLASH_FDATA1;

    /* 0x28*/
    struct {
           uint32_t CMDDATA2                :32;  /* [31:0]         r/w        */
    } FLASH_FDATA2;

    /* 0x2C*/
    struct {
           uint32_t CMDDATA3                :32;  /* [31:0]         r/w        */
    } FLASH_FDATA3;

    /* 0x30*/
    struct {
           uint32_t RSVD_3_0                : 4;  /* [3:0]          ro         */
           uint32_t BED_ADDR_STRT           :28;  /* [31:4]         r/w        */
    } FLASH_BED_ADDR_STRT;

    /* 0x34*/
    struct {
           uint32_t RSVD_3_0                : 4;  /* [3:0]          ro         */
           uint32_t BED_ADDR_END            :28;  /* [31:4]         r/w        */
    } FLASH_BED_ADDR_END;

    /* 0x38*/
    struct {
           uint32_t RSVD_3_0                : 4;  /* [3:0]          ro         */
           uint32_t ECC_IN_ADDR             :28;  /* [31:4]         r/w        */
    } FLASH_ECC_IN_ADDR;

    /* 0x3C*/
    struct {
           uint32_t ECC_9BIT                : 9;  /* [8:0]          r/w        */
           uint32_t ECC_IN_EN               : 1;  /* [9]            r/w        */
           uint32_t RSVD_30_10              :21;  /* [30:10]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } FLASH_ECC_IN_CTRL;

    /* 0x40*/
    struct {
           uint32_t MBE_FLAG                : 1;  /* [0]            w1c        */
           uint32_t MBE_OVERRUN             : 1;  /* [1]            ro         */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t MBE_ADDR                :28;  /* [31:4]         ro         */
    } FLASH_MBE_STATE;

    /* 0x44*/
    struct {
           uint32_t SBE_FLAG                : 1;  /* [0]            w1c        */
           uint32_t SBE_OVERRUN             : 1;  /* [1]            ro         */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t SBE_ADDR                :28;  /* [31:4]         ro         */
    } FLASH_SBE_STATE;

};    /*flash_reg*/

struct flash_reg_w {
    /* 0x0*/
    uint32_t FLASH_FSTAT;
    /* 0x4*/
    uint32_t FLASH_FCNFG;
    /* 0x8*/
    uint32_t FLASH_FCTRL;
    uint8_t zResverd0x0C[4];   /*pad 0x0C - 0F*/

    /* 0x10*/
    uint32_t FLASH_FCMD;
    /* 0x14*/
    uint8_t zResverd0x14[4];
    /* 0x18*/
    uint32_t FLASH_FADDR;
    /* 0x1C*/
    uint32_t FLASH_FADDR_END;
    /* 0x20*/
    uint32_t FLASH_FDATA0;
    /* 0x24*/
    uint32_t FLASH_FDATA1;
    /* 0x28*/
    uint32_t FLASH_FDATA2;
    /* 0x2C*/
    uint32_t FLASH_FDATA3;
    /* 0x30*/
    uint32_t FLASH_BED_ADDR_STRT;
    /* 0x34*/
    uint32_t FLASH_BED_ADDR_END;
    /* 0x38*/
    uint32_t FLASH_ECC_IN_ADDR;
    /* 0x3C*/
    uint32_t FLASH_ECC_IN_CTRL;
    /* 0x40*/
    uint32_t FLASH_MBE_STATE;
    /* 0x44*/
    uint32_t FLASH_SBE_STATE;
};    /*flash_reg*/

typedef volatile struct flash_reg flash_reg_t;
typedef volatile struct flash_reg_w flash_reg_w_t;

struct gpio_reg {
    /* 0x0*/
    struct {
           uint32_t PDO                     :32;  /* [31:0]         r/w        */
    } GPIOx_PDOR;

    /* 0x4*/
    struct {
           uint32_t PSO                     :32;  /* [31:0]         wo         */
    } GPIOx_PSOR;

    /* 0x8*/
    struct {
           uint32_t PCO                     :32;  /* [31:0]         wo         */
    } GPIOx_PCOR;

    /* 0xC*/
    struct {
           uint32_t PTO                     :32;  /* [31:0]         wo         */
    } GPIOx_PTOR;

    /* 0x10*/
    struct {
           uint32_t PDI                     :32;  /* [31:0]         ro         */
    } GPIOx_PDIR;

    /* 0x14*/
    struct {
           uint32_t PDD                     :32;  /* [31:0]         r/w        */
    } GPIOx_PDDR;

};    /*gpio_reg*/

struct gpio_reg_w {
    /* 0x0 */
    uint32_t GPIOx_PDOR;
    /* 0x4 */
    uint32_t GPIOx_PSOR;
    /* 0x8 */
    uint32_t GPIOx_PCOR;
    /* 0xC */
    uint32_t GPIOx_PTOR;
    /* 0x10 */
    uint32_t GPIOx_PDIR;
    /* 0x14 */
    uint32_t GPIOx_PDDR;
};    /* gpio_reg */

typedef volatile struct gpio_reg gpio_reg_t;
typedef volatile struct gpio_reg_w gpio_reg_w_t;

struct i2c_reg {
    /* 0x00*/
    uint32_t zResverd0x00;
    /* 0x04*/
    struct {
           uint32_t I2C_SUPPORT_SPEED       : 2;  /* [1:0]          ro         */
           uint32_t DMA_SUPPORT             : 1;  /* [2]            ro         */
           uint32_t TXFIFO_DEPTH            : 4;  /* [6:3]          ro         */
           uint32_t RXFIFO_DEPTH            : 4;  /* [10:7]         ro         */
           uint32_t RSVD_31_11              :21;  /* [31:11]        ro         */
    } I2C_PARAMETER;

    /* 0x08*/
    struct {
           uint32_t MODULE_EN               : 1;  /* [0]            r/w        */
           uint32_t SLAVE_ACK_GENCALL       : 1;  /* [1]            r/w        */
           uint32_t SLAVE_NACK              : 1;  /* [2]            r/w        */
           uint32_t SDA_RECOVER_EN          : 1;  /* [3]            r/w        */
           uint32_t MASTER_ABORT            : 1;  /* [4]            r/w        */
           uint32_t MASTER_BUS_RECOVER_EN   : 1;  /* [5]            r/w        */
           uint32_t MASTER_BLK_TXFIFO       : 1;  /* [6]            r/w        */
           uint32_t H_MCODE                 : 3;  /* [9:7]          r/w        */
           uint32_t RSVD_31_10              :22;  /* [31:10]        ro         */
    } I2C_CONFIG0;

    /* 0x0c*/
    struct {
           uint32_t SLAVE_MODE_DIS          : 1;  /* [0]            r/w        */
           uint32_t MASTER_MODE_EN          : 1;  /* [1]            r/w        */
           uint32_t MASTER_RESTART_EN       : 1;  /* [2]            r/w        */
           uint32_t SLAVE_STOP_DET_EN       : 1;  /* [3]            r/w        */
           uint32_t MASTER_STOP_DET_EN      : 1;  /* [4]            r/w        */
           uint32_t TXFIFO_EMPTY_EN         : 1;  /* [5]            r/w        */
           uint32_t SPEED_SEL               : 2;  /* [7:6]          r/w        */
           uint32_t HOLD_EN_RXFIFO_FULL     : 1;  /* [8]            r/w        */
           uint32_t SLAVE_10BIT_ADDR_SEL    : 1;  /* [9]            r/w        */
           uint32_t MASTER_10BIT_ADDR_SEL   : 1;  /* [10]           r/w        */
           uint32_t RSVD_31_11              :21;  /* [31:11]        ro         */
    } I2C_CONFIG1;

    /* 0x10*/
    struct {
           uint32_t SDA_SETUP_TIMING        : 8;  /* [7:0]          r/w        */
           uint32_t RSVD_31_8               :24;  /* [31:8]         ro         */
    } I2C_SDA_SETUP_TIMING;

    /* 0x14*/
    struct {
           uint32_t SDA_TX_HOLD_TIMING      :16;  /* [15:0]         r/w        */
           uint32_t SDA_RX_HOLD_TIMING      : 8;  /* [23:16]        r/w        */
           uint32_t RSVD_31_24              : 8;  /* [31:24]        ro         */
    } I2C_SDA_HOLD_TIMING;

    /* 0x18*/
    struct {
           uint32_t RXFIFO_DMA_EN           : 1;  /* [0]            r/w        */
           uint32_t TXFIFO_DMA_EN           : 1;  /* [1]            r/w        */
           uint32_t DMA_TXFIFO_WATERMARK    : 2;  /* [3:2]          r/w        */
           uint32_t DMA_RXFIFO_WATERMARK    : 2;  /* [5:4]          r/w        */
           uint32_t RSVD_31_6               :26;  /* [31:6]         ro         */
    } I2C_DMA_CTRL;

    /* 0x1c*/
    struct {
           uint32_t I2C_CALL_IE             : 1;  /* [0]            r/w        */
           uint32_t I2C_TX_OVF_IE           : 1;  /* [1]            r/w        */
           uint32_t I2C_ERROR_ABORT_IE      : 1;  /* [2]            r/w        */
           uint32_t I2C_ACTIVITY_DET_IE     : 1;  /* [3]            r/w        */
           uint32_t I2C_STOP_DET_IE         : 1;  /* [4]            r/w        */
           uint32_t I2C_START_DET_IE        : 1;  /* [5]            r/w        */
           uint32_t RSVD_21_6               :16;  /* [21:6]         ro         */
           uint32_t SLAVE_RD_REQ_IE         : 1;  /* [22]           r/w        */
           uint32_t RX_DONE_IE              : 1;  /* [23]           r/w        */
           uint32_t RX_UNDER_IE             : 1;  /* [24]           r/w        */
           uint32_t RX_OVF_IE               : 1;  /* [25]           r/w        */
           uint32_t RESTART_DET_IE          : 1;  /* [26]           r/w        */
           uint32_t SCL_STUCK_AT_LOW_IE     : 1;  /* [27]           r/w        */
           uint32_t RSVD_29_28              : 2;  /* [29:28]        ro         */
           uint32_t RX_FULL_IE              : 1;  /* [30]           r/w        */
           uint32_t TX_EMPTY_IE             : 1;  /* [31]           r/w        */
    } I2C_INT_ENABLE;

    /* 0x20*/
    struct {
           uint32_t DATA                    : 8;  /* [7:0]          r/w        */
           uint32_t CMD_MASTER_DIRECTION    : 1;  /* [8]            wo         */
           uint32_t CMD_STOP                : 1;  /* [9]            wo         */
           uint32_t CMD_RESTART             : 1;  /* [10]           wo         */
           uint32_t RSVD_31_11              :21;  /* [31:11]        ro         */
    } I2C_COMMAND_DATA;

    /* 0x24*/
    struct {
           uint32_t DEST_ADDR               :10;  /* [9:0]          r/w        */
           uint32_t MASTER_CMD_SEL          : 2;  /* [11:10]        r/w        */
           uint32_t RSVD_31_12              :20;  /* [31:12]        ro         */
    } I2C_DEST_ADDR;

    /* 0x28*/
    struct {
           uint32_t SLV_ADDR                :10;  /* [9:0]          r/w        */
           uint32_t RSVD_31_10              :22;  /* [31:10]        ro         */
    } I2C_SLAVE_ADDR;

    /* 0x2c*/
    struct {
           uint32_t STD_SCL_HCNT            :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } I2C_STD_SCL_HCNT;

    /* 0x30*/
    struct {
           uint32_t STD_SCL_LCNT            :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } I2C_STD_SCL_LCNT;

    /* 0x34*/
    struct {
           uint32_t FST_SCL_HCNT            :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } I2C_FST_SCL_HCNT;

    /* 0x38*/
    struct {
           uint32_t FST_SCL_LCNT            :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } I2C_FST_SCL_LCNT;

    /* 0x3c*/
    struct {
           uint32_t HS_SCL_HCNT             :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } I2C_HS_SCL_HCNT;

    /* 0x40*/
    struct {
           uint32_t HS_SCL_LCNT             :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } I2C_HS_SCL_LCNT;

    /* 0x44*/
    struct {
           uint32_t RXFIFO_WATER_MARK       : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_31_2               :30;  /* [31:2]         ro         */
    } I2C_RXFIFO_WATER_MARK;

    /* 0x48*/
    struct {
           uint32_t TXFIFO_WATER_MARK       : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_31_2               :30;  /* [31:2]         ro         */
    } I2C_TXFIFO_WATER_MARK;

    /* 0x4c*/
    struct {
           uint32_t TX_FIFO_CNT             : 3;  /* [2:0]          ro         */
           uint32_t RSVD_31_3               :29;  /* [31:3]         ro         */
    } I2C_TX_FIFO_CNT;

    /* 0x50*/
    struct {
           uint32_t RX_FIFO_CNT             : 3;  /* [2:0]          ro         */
           uint32_t RSVD_31_3               :29;  /* [31:3]         ro         */
    } I2C_RX_FIFO_CNT;

    /* 0x54*/
    struct {
           uint32_t FSTD_SPKLEN             : 8;  /* [7:0]          r/w        */
           uint32_t RSVD_31_8               :24;  /* [31:8]         ro         */
    } I2C_FSTD_SPKCNT;

    /* 0x58*/
    struct {
           uint32_t HS_SPKLEN               : 8;  /* [7:0]          r/w        */
           uint32_t RSVD_31_8               :24;  /* [31:8]         ro         */
    } I2C_HS_SPKCNT;

    /* 0x5c*/
    struct {
           uint32_t GENERAL_CALL            : 1;  /* [0]            w1c        */
           uint32_t TXFIFO_OVERUN           : 1;  /* [1]            w1c        */
           uint32_t ERROR_ABORT             : 1;  /* [2]            w1c        */
           uint32_t ACTIVITY                : 1;  /* [3]            w1c        */
           uint32_t STOP_DETECT             : 1;  /* [4]            w1c        */
           uint32_t START_DETECT            : 1;  /* [5]            w1c        */
           uint32_t RSVD_21_6               :16;  /* [21:6]         ro         */
           uint32_t SLAVE_READ_REQ          : 1;  /* [22]           w1c        */
           uint32_t RXFIFO_DONE             : 1;  /* [23]           w1c        */
           uint32_t RXFIFO_UNDERUN          : 1;  /* [24]           w1c        */
           uint32_t RXFIFO_OVERUN           : 1;  /* [25]           w1c        */
           uint32_t RESTART_DET             : 1;  /* [26]           w1c        */
           uint32_t SCL_STUCK_AT_LOW        : 1;  /* [27]           w1c        */
           uint32_t RSVD_29_28              : 2;  /* [29:28]        ro         */
           uint32_t RXFIFO_FULL             : 1;  /* [30]           ro         */
           uint32_t TXFIFO_EMPTY            : 1;  /* [31]           ro         */
    } I2C_STATUS0;

    /* 0x60*/
    struct {
           uint32_t MASTER_IS_ACTIVE        : 1;  /* [0]            ro         */
           uint32_t SLAVE_IS_ACTIVE         : 1;  /* [1]            ro         */
           uint32_t TXFIFO_EMPTY_MASTER_HOLD: 1;  /* [2]            ro         */
           uint32_t TXFIFO_EMPTY_SLAVE_HOLD : 1;  /* [3]            ro         */
           uint32_t RXFIFO_FULL_MASTER_HOLD : 1;  /* [4]            ro         */
           uint32_t RXFIFO_FULL_SLAVE_HOLD  : 1;  /* [5]            ro         */
           uint32_t TXFIFO_IS_NOT_FULL      : 1;  /* [6]            ro         */
           uint32_t TXFIFO_IS_EMPTY         : 1;  /* [7]            ro         */
           uint32_t RXFIFO_IS_NOT_EMPTY     : 1;  /* [8]            ro         */
           uint32_t RXFIFO_IS_FULL          : 1;  /* [9]            ro         */
           uint32_t SDA_ERR_RECOVER_STUCK_LOW: 1;  /* [10]          ro         */
           uint32_t SLAVE_IS_DISABLED_UNDER_ACT: 1;  /* [11]        ro         */
           uint32_t SLAVE_RX_DATA_DISCARD   : 1;  /* [12]           ro         */
           uint32_t I2C_IS_ENABLE           : 1;  /* [13]           ro         */
           uint32_t RSVD_31_14              :18;  /* [31:14]        ro         */
    } I2C_STATUS1;

    /* 0x64*/
    struct {
           uint32_t ERR_GEN_CALL_NO_ACK     : 1;  /* [0]            ro         */
           uint32_t ERR_GEN_CALL_READ       : 1;  /* [1]            ro         */
           uint32_t ERR_START_BYTE_ACK_DET  : 1;  /* [2]            ro         */
           uint32_t ERR_SBYTE_NORSTRT       : 1;  /* [3]            ro         */
           uint32_t ERR_H_NO_RSTRT          : 1;  /* [4]            ro         */
           uint32_t ERR_H_MCODE_ACK_DET     : 1;  /* [5]            ro         */
           uint32_t ERR_7BIT_ADDR_NO_ACK    : 1;  /* [6]            ro         */
           uint32_t ERR_10BIT_ADDR1_NO_ACK  : 1;  /* [7]            ro         */
           uint32_t ERR_10BIT_ADDR2_NO_ACK  : 1;  /* [8]            ro         */
           uint32_t ERR_10BIT_READ_NO_RSTRT : 1;  /* [9]            ro         */
           uint32_t ERR_DATA_NO_ACK         : 1;  /* [10]           ro         */
           uint32_t ERR_MASTER_LOST         : 1;  /* [11]           ro         */
           uint32_t ERR_MASTER_DIS          : 1;  /* [12]           ro         */
           uint32_t ERR_SLAVE_ARBLOST       : 1;  /* [13]           ro         */
           uint32_t ERR_MASTER_ABRT         : 1;  /* [14]           ro         */
           uint32_t ERR_SLAVE_READ_REQ      : 1;  /* [15]           ro         */
           uint32_t ERR_SLAVE_FLUSH_TXFIFO  : 1;  /* [16]           ro         */
           uint32_t ERR_SDA_LOW_TIMEOUT     : 1;  /* [17]           ro         */
           uint32_t ERR_TXFIFO_FLUSH_CNT    : 3;  /* [20:18]        ro         */
           uint32_t RSVD_31_21              :11;  /* [31:21]        ro         */
    } I2C_ERROR_STATUS;

    /* 0x68*/
    struct {
           uint32_t SCL_LOW_TIMEOUT         :32;  /* [31:0]         r/w        */
    } I2C_SCL_LOW_TIMEOUT;

    /* 0x6c*/
    struct {
           uint32_t SDA_LOW_TIMEOUT         :32;  /* [31:0]         r/w        */
    } I2C_SDA_LOW_TIMEOUT;

    /* 0x70*/
    struct {
           uint32_t CLR_ERR                 : 1;  /* [0]            ro         */
           uint32_t RSVD_31_1               :31;  /* [31:1]         ro         */
    } I2C_RD_CLR_ERR_STATUS;

};    /*i2c_reg*/

struct i2c_reg_w {
    /* 0x00*/
    uint32_t zResverd0x00;
    /* 0x04*/
    uint32_t I2C_PARAMETER;
    /* 0x08*/
    uint32_t I2C_CONFIG0;
    /* 0x0c*/
    uint32_t I2C_CONFIG1;
    /* 0x10*/
    uint32_t I2C_SDA_SETUP_TIMING;
    /* 0x14*/
    uint32_t I2C_SDA_HOLD_TIMING;
    /* 0x18*/
    uint32_t I2C_DMA_CTRL;
    /* 0x1c*/
    uint32_t I2C_INT_ENABLE;
    /* 0x20*/
    uint32_t I2C_COMMAND_DATA;
    /* 0x24*/
    uint32_t I2C_DEST_ADDR;
    /* 0x28*/
    uint32_t I2C_SLAVE_ADDR;
    /* 0x2c*/
    uint32_t I2C_STD_SCL_HCNT;
    /* 0x30*/
    uint32_t I2C_STD_SCL_LCNT;
    /* 0x34*/
    uint32_t I2C_FST_SCL_HCNT;
    /* 0x38*/
    uint32_t I2C_FST_SCL_LCNT;
    /* 0x3c*/
    uint32_t I2C_HS_SCL_HCNT;
    /* 0x40*/
    uint32_t I2C_HS_SCL_LCNT;
    /* 0x44*/
    uint32_t I2C_RXFIFO_WATER_MARK;
    /* 0x48*/
    uint32_t I2C_TXFIFO_WATER_MARK;
    /* 0x4c*/
    uint32_t I2C_TX_FIFO_CNT;
    /* 0x50*/
    uint32_t I2C_RX_FIFO_CNT;
    /* 0x54*/
    uint32_t I2C_FSTD_SPKCNT;
    /* 0x58*/
    uint32_t I2C_HS_SPKCNT;
    /* 0x5c*/
    uint32_t I2C_STATUS0;
    /* 0x60*/
    uint32_t I2C_STATUS1;
    /* 0x64*/
    uint32_t I2C_ERROR_STATUS;
    /* 0x68*/
    uint32_t I2C_SCL_LOW_TIMEOUT;
    /* 0x6c*/
    uint32_t I2C_SDA_LOW_TIMEOUT;
    /* 0x70*/
    uint32_t I2C_RD_CLR_ERR_STATUS;
};    /*i2c_reg*/

typedef volatile struct i2c_reg i2c_reg_t;
typedef volatile struct i2c_reg_w i2c_reg_w_t;

struct i2s_reg {
    /* 0x00*/
    struct {
           uint32_t I2S_MODULE_EN           : 1;  /* [0]            r/w        */
           uint32_t I2S_TE                  : 1;  /* [1]            r/w        */
           uint32_t I2S_RE                  : 1;  /* [2]            r/w        */
           uint32_t I2S_TXFIFO_RESET        : 1;  /* [3]            wo         */
           uint32_t I2S_RXFIFO_RESET        : 1;  /* [4]            wo         */
           uint32_t RSVD_31_5               :27;  /* [31:5]         ro         */
    } I2S_CONTROL;

    /* 0x04*/
    struct {
           uint32_t I2S_MASTER_EN           : 1;  /* [0]            r/w        */
           uint32_t I2S_NUM_BCLK            : 2;  /* [2:1]          r/w        */
           uint32_t RSVD_4_3                : 2;  /* [4:3]          ro         */
           uint32_t I2S_NUM_BCLK_GATE       : 3;  /* [7:5]          r/w        */
           uint32_t MCK_DIV                 : 8;  /* [15:8]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]         ro         */
    } I2S_MASTER_CONFIG;

    struct{
        /* 0x08 + 0x14*n*/
        struct {
               uint32_t LEFT_DATA              :32;  /* [31:0]         r/w        */
        } I2S_CHn_LEFT_DATA;

        /* 0x0c + 0x14*n*/
        struct {
               uint32_t RIGHT_DATA             :32;  /* [31:0]         r/w        */
        } I2S_CHn_RIGHT_DATA;

        /* 0x10 + 0x14*n*/
        struct {
               uint32_t TX_EN                   : 1;  /* [0]            r/w        */
               uint32_t RX_EN                   : 1;  /* [1]            r/w        */
               uint32_t TX_AUDIO_RESOLUTION     : 3;  /* [4:2]          r/w        */
               uint32_t RX_AUDIO_RESOLUTION     : 3;  /* [7:5]          r/w        */
               uint32_t RSVD_31_8               :24;  /* [31:8]         ro         */
        } I2S_CHn_CFG;

        /* 0x14 + 0x14*n*/
        struct {
               uint32_t RXFIFO_AVAILABLE_IE     : 1;  /* [0]            r/w        */
               uint32_t RXFIFO_OVERUN_IE        : 1;  /* [1]            r/w        */
               uint32_t TXFIFO_EMPTY_IE         : 1;  /* [2]            r/w        */
               uint32_t TXFIFO_OVERUN_IE        : 1;  /* [3]            r/w        */
               uint32_t RXFIFO_DAF              : 1;  /* [4]            ro         */
               uint32_t RXFIFO_ORF              : 1;  /* [5]            r/w        */
               uint32_t TXFIFO_EMPTYF           : 1;  /* [6]            ro         */
               uint32_t TXFIFO_ORF              : 1;  /* [7]            r/w        */
               uint32_t RSVD_31_8               :24;  /* [31:8]         ro         */
        } I2S_CHn_INT_CFG;

        /* 0x18 + 0x14*n*/
        struct {
               uint32_t RXFIFO_FULL_TRIG_LEV    : 4;  /* [3:0]          r/w        */
               uint32_t TXFIFO_EMPTY_TRIG_LEV   : 4;  /* [7:4]          r/w        */
               uint32_t CH_TXFIFO_RESET         : 1;  /* [8]            wo         */
               uint32_t CH_RXFIFO_RESET         : 1;  /* [9]            wo         */
               uint32_t RSVD_31_10              :22;  /* [31:10]        ro         */
        } I2S_CHn_TRIGGER_LEVEL_CFG;
    }I2S_CHANNEL_REG[4];
    /* 0x58*/
    struct {
           uint32_t CYCLE_TX_DATA           :32;  /* [31:0]         wo         */
    } I2S_CYCLE_TX_DATA;

    /* 0x5c*/
    struct {
           uint32_t CYCLE_TX_RESET          : 1;  /* [0]            wo         */
           uint32_t RSVD_31_1               :31;  /* [31:1]         ro         */
    } I2S_CYCLE_TX_RESET;

    /* 0x60*/
    struct {
           uint32_t CYCLE_RX_DATA           :32;  /* [31:0]         ro         */
    } I2S_CYCLE_RX_DATA;

    /* 0x64*/
    struct {
           uint32_t CYCLE_RX_RESET          : 1;  /* [0]            wo         */
           uint32_t RSVD_31_1               :31;  /* [31:1]         ro         */
    } I2S_CYCLE_RX_RESET;

};    /*i2s_reg*/

struct i2s_reg_w {
    /* 0x00*/
    uint32_t I2S_CONTROL;
    /* 0x04*/
    uint32_t I2S_MASTER_CONFIG;
    struct
    {
       /* 0x08*/
       uint32_t I2S_CHn_LEFT_DATA;
       /* 0x0c*/
       uint32_t I2S_CHn_RIGHT_DATA;
       /* 0x10*/
       uint32_t I2S_CHn_CFG;
       /* 0x14*/
       uint32_t I2S_CHn_INT_CFG;
       /* 0x18*/
       uint32_t I2S_CHn_TRIGGER_LEVEL_CFG;
    }I2S_CHANNEL_REG[4];
    /* 0x58*/
    uint32_t I2S_CYCLE_TX_DATA;
    /* 0x5c*/
    uint32_t I2S_CYCLE_TX_RESET;
    /* 0x60*/
    uint32_t I2S_CYCLE_RX_DATA;
    /* 0x64*/
    uint32_t I2S_CYCLE_RX_RESET;
};    /*i2s_reg*/

typedef volatile struct i2s_reg i2s_reg_t;
typedef volatile struct i2s_reg_w i2s_reg_w_t;

struct mcpwm_reg {
    /* 0x00*/
    struct {
           uint32_t CKSRC                   : 2;  /* [1:0]          r/w        */
           uint32_t PSDIV                   : 3;  /* [4:2]          r/w        */
           uint32_t DBGM                    : 2;  /* [6:5]          r/w        */
           uint32_t RSVD_31_7               :25;  /* [31:7]         ro         */
    } MCPWM_TIMEBASE;

    /* 0x04 - 0x13*/
    struct {
           uint32_t CNT                     :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } MCPWM_CNT[4];

    /* 0x14 - 0x23*/
    struct {
           uint32_t MOD                     :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } MCPWM_MOD[4];

    /* 0x24 - 0x33*/
    struct {
           uint32_t DTVAL                   :12;  /* [11:0]         r/w        */
           uint32_t RSVD_31_12              :20;  /* [31:12]        ro         */
    } MCPWM_DTVAL[4];

    /* 0x34*/
    struct {
           uint32_t CHOE0                   : 1;  /* [0]            r/w        */
           uint32_t CHOE1                   : 1;  /* [1]            r/w        */
           uint32_t CHOE2                   : 1;  /* [2]            r/w        */
           uint32_t CHOE3                   : 1;  /* [3]            r/w        */
           uint32_t CHOE4                   : 1;  /* [4]            r/w        */
           uint32_t CHOE5                   : 1;  /* [5]            r/w        */
           uint32_t CHOE6                   : 1;  /* [6]            r/w        */
           uint32_t CHOE7                   : 1;  /* [7]            r/w        */
           uint32_t CNTM0                   : 1;  /* [8]            r/w        */
           uint32_t CNTM1                   : 1;  /* [9]            r/w        */
           uint32_t CNTM2                   : 1;  /* [10]           r/w        */
           uint32_t CNTM3                   : 1;  /* [11]           r/w        */
           uint32_t CNTEN0                  : 1;  /* [12]                      */
           uint32_t CNTEN1                  : 1;  /* [13]                      */
           uint32_t CNTEN2                  : 1;  /* [14]                      */
           uint32_t CNTEN3                  : 1;  /* [15]                      */
           uint32_t RLDIE0                  : 1;  /* [16]           r/w        */
           uint32_t RLDIE1                  : 1;  /* [17]           r/w        */
           uint32_t RLDIE2                  : 1;  /* [18]           r/w        */
           uint32_t RLDIE3                  : 1;  /* [19]           r/w        */
           uint32_t TOIE0                   : 1;  /* [20]           r/w        */
           uint32_t TOIE1                   : 1;  /* [21]           r/w        */
           uint32_t TOIE2                   : 1;  /* [22]           r/w        */
           uint32_t TOIE3                   : 1;  /* [23]           r/w        */
           uint32_t RSVD_29_24              : 6;  /* [29:24]        ro         */
           uint32_t WPEN                    : 1;  /* [30]                      */
           uint32_t GLBCNTEN                : 1;  /* [31]                      */
    } MCPWM_GLBCR;

    /* 0x38*/
    struct {
           uint32_t CH0F                    : 1;  /* [0]            ro         */
           uint32_t CH1F                    : 1;  /* [1]            ro         */
           uint32_t CH2F                    : 1;  /* [2]            ro         */
           uint32_t CH3F                    : 1;  /* [3]            ro         */
           uint32_t CH4F                    : 1;  /* [4]            ro         */
           uint32_t CH5F                    : 1;  /* [5]            ro         */
           uint32_t CH6F                    : 1;  /* [6]            ro         */
           uint32_t CH7F                    : 1;  /* [7]            ro         */
           uint32_t RLDF0                   : 1;  /* [8]            ro         */
           uint32_t RLDF1                   : 1;  /* [9]            ro         */
           uint32_t RLDF2                   : 1;  /* [10]           ro         */
           uint32_t RLDF3                   : 1;  /* [11]           ro         */
           uint32_t TOF0                    : 1;  /* [12]           ro         */
           uint32_t TOF1                    : 1;  /* [13]           ro         */
           uint32_t TOF2                    : 1;  /* [14]           ro         */
           uint32_t TOF3                    : 1;  /* [15]           ro         */
           uint32_t WPDIS                   : 1;  /* [16]           r/w        */
           uint32_t RSVD_31_17              :15;  /* [31:17]        ro         */
    } MCPWM_GLBSR;

    /* 0x3C - 0x5B*/
    struct {
           uint32_t CPP                     : 1;  /* [0]            r/w        */
           uint32_t RSVD_3_1                : 3;  /* [3:1]          ro         */
           uint32_t CHIE                    : 1;  /* [4]            r/w        */
           uint32_t CHF                     : 1;  /* [5]            ro         */
           uint32_t DMA                     : 1;  /* [6]            r/w        */
           uint32_t RSVD_31_7               :25;  /* [31:7]         ro         */
    } MCPWM_CFG[8];

    /* 0x5C - 0x7B*/
    struct {
           uint32_t CV                      :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } MCPWM_CV[8];

    /* 0x7C*/
    struct {
           uint32_t POL0                    : 1;  /* [0]            r/w        */
           uint32_t POL1                    : 1;  /* [1]            r/w        */
           uint32_t POL2                    : 1;  /* [2]            r/w        */
           uint32_t POL3                    : 1;  /* [3]            r/w        */
           uint32_t POL4                    : 1;  /* [4]            r/w        */
           uint32_t POL5                    : 1;  /* [5]            r/w        */
           uint32_t POL6                    : 1;  /* [6]            r/w        */
           uint32_t POL7                    : 1;  /* [7]            r/w        */
           uint32_t OFFVAL0                 : 1;  /* [8]            r/w        */
           uint32_t OFFVAL1                 : 1;  /* [9]            r/w        */
           uint32_t OFFVAL2                 : 1;  /* [10]           r/w        */
           uint32_t OFFVAL3                 : 1;  /* [11]           r/w        */
           uint32_t OFFVAL4                 : 1;  /* [12]           r/w        */
           uint32_t OFFVAL5                 : 1;  /* [13]           r/w        */
           uint32_t OFFVAL6                 : 1;  /* [14]           r/w        */
           uint32_t OFFVAL7                 : 1;  /* [15]           r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } MCPWM_OUTCR;

    /* 0x80*/
    struct {
           uint32_t TRIGE0                  : 1;  /* [0]            r/w        */
           uint32_t TRIGE1                  : 1;  /* [1]            r/w        */
           uint32_t TRIGE2                  : 1;  /* [2]            r/w        */
           uint32_t TRIGE3                  : 1;  /* [3]            r/w        */
           uint32_t TRIGE4                  : 1;  /* [4]            r/w        */
           uint32_t TRIGE5                  : 1;  /* [5]            r/w        */
           uint32_t TRIGE6                  : 1;  /* [6]            r/w        */
           uint32_t TRIGE7                  : 1;  /* [7]            r/w        */
           uint32_t INITRIGE                : 1;  /* [8]            r/w        */
           uint32_t TRIGF                   : 1;  /* [9]            ro         */
           uint32_t RSVD_31_10              :22;  /* [31:10]        ro         */
    } MCPWM_OUTTRIG;

    /* 0x84*/
    struct {
           uint32_t CH0OC                   : 1;  /* [0]            r/w        */
           uint32_t CH1OC                   : 1;  /* [1]            r/w        */
           uint32_t CH2OC                   : 1;  /* [2]            r/w        */
           uint32_t CH3OC                   : 1;  /* [3]            r/w        */
           uint32_t CH4OC                   : 1;  /* [4]            r/w        */
           uint32_t CH5OC                   : 1;  /* [5]            r/w        */
           uint32_t CH6OC                   : 1;  /* [6]            r/w        */
           uint32_t CH7OC                   : 1;  /* [7]            r/w        */
           uint32_t CH0OCV                  : 1;  /* [8]            r/w        */
           uint32_t CH1OCV                  : 1;  /* [9]            r/w        */
           uint32_t CH2OCV                  : 1;  /* [10]           r/w        */
           uint32_t CH3OCV                  : 1;  /* [11]           r/w        */
           uint32_t CH4OCV                  : 1;  /* [12]           r/w        */
           uint32_t CH5OCV                  : 1;  /* [13]           r/w        */
           uint32_t CH6OCV                  : 1;  /* [14]           r/w        */
           uint32_t CH7OCV                  : 1;  /* [15]           r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } MCPWM_OUTSWCR;

    /* 0x88*/
    struct {
           uint32_t FCTLEN0                 : 1;  /* [0]            r/w        */
           uint32_t DTEN0                   : 1;  /* [1]            r/w        */
           uint32_t SYNCEN0                 : 1;  /* [2]            r/w        */
           uint32_t ASYMEN0                 : 1;  /* [3]                       */
           uint32_t CVSEL0                  : 1;  /* [4]                       */
           uint32_t PEC0                    : 1;  /* [5]                       */
           uint32_t COMB0                   : 1;  /* [6]            r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t FCTLEN1                 : 1;  /* [8]            r/w        */
           uint32_t DTEN1                   : 1;  /* [9]            r/w        */
           uint32_t SYNCEN1                 : 1;  /* [10]           r/w        */
           uint32_t ASYMEN1                 : 1;  /* [11]                      */
           uint32_t CVSEL1                  : 1;  /* [12]                      */
           uint32_t PEC1                    : 1;  /* [13]                      */
           uint32_t COMB1                   : 1;  /* [14]           r/w        */
           uint32_t RSVD_15                 : 1;  /* [15]           ro         */
           uint32_t FCTLEN2                 : 1;  /* [16]           r/w        */
           uint32_t DTEN2                   : 1;  /* [17]           r/w        */
           uint32_t SYNCEN2                 : 1;  /* [18]           r/w        */
           uint32_t ASYMEN2                 : 1;  /* [19]                      */
           uint32_t CVSEL2                  : 1;  /* [20]                      */
           uint32_t PEC2                    : 1;  /* [21]                      */
           uint32_t COMB2                   : 1;  /* [22]           r/w        */
           uint32_t RSVD_23                 : 1;  /* [23]           ro         */
           uint32_t FCTLEN3                 : 1;  /* [24]           r/w        */
           uint32_t DTEN3                   : 1;  /* [25]           r/w        */
           uint32_t SYNCEN3                 : 1;  /* [26]           r/w        */
           uint32_t ASYMEN3                 : 1;  /* [27]                      */
           uint32_t CVSEL3                  : 1;  /* [28]                      */
           uint32_t PEC3                    : 1;  /* [29]                      */
           uint32_t COMB3                   : 1;  /* [30]           r/w        */
           uint32_t RSVD_31                 : 1;  /* [31]           ro         */
    } MCPWM_PCR;

    /* 0x8C*/
    struct {
           uint32_t FIFEN0                  : 1;  /* [0]            r/w        */
           uint32_t FIFEN1                  : 1;  /* [1]            r/w        */
           uint32_t FIFEN2                  : 1;  /* [2]            r/w        */
           uint32_t FIFEN3                  : 1;  /* [3]            r/w        */
           uint32_t FLTEN0                  : 1;  /* [4]            r/w        */
           uint32_t FLTEN1                  : 1;  /* [5]            r/w        */
           uint32_t FLTEN2                  : 1;  /* [6]            r/w        */
           uint32_t FLTEN3                  : 1;  /* [7]            r/w        */
           uint32_t FLTPOL0                 : 1;  /* [8]            r/w        */
           uint32_t FLTPOL1                 : 1;  /* [9]            r/w        */
           uint32_t FLTPOL2                 : 1;  /* [10]           r/w        */
           uint32_t FLTPOL3                 : 1;  /* [11]           r/w        */
           uint32_t FLTIE                   : 1;  /* [12]           r/w        */
           uint32_t FLTCM                   : 1;  /* [13]           r/w        */
           uint32_t RSVD_15_14              : 2;  /* [15:14]        ro         */
           uint32_t FIFVAL                  : 4;  /* [19:16]        r/w        */
           uint32_t FSTATE                  : 1;  /* [20]           r/w        */
           uint32_t RSVD_31_21              :11;  /* [31:21]        ro         */
    } MCPWM_FLTCR;

    /* 0x90*/
    struct {
           uint32_t FAULTF0                 : 1;  /* [0]            r/w        */
           uint32_t FAULTF1                 : 1;  /* [1]            r/w        */
           uint32_t FAULTF2                 : 1;  /* [2]            r/w        */
           uint32_t FAULTF3                 : 1;  /* [3]            r/w        */
           uint32_t FAULTFA                 : 1;  /* [4]            r/w        */
           uint32_t FAULTFB                 : 1;  /* [5]            r/w        */
           uint32_t FAULTINA                : 1;  /* [6]            ro         */
           uint32_t FAULTINB                : 1;  /* [7]            ro         */
           uint32_t RSVD_31_8               :24;  /* [31:8]         ro         */
    } MCPWM_FLTSR;

    /* 0x94*/
    struct {
           uint32_t FLTASS0                 : 1;  /* [0]            r/w        */
           uint32_t FLTASS1                 : 1;  /* [1]            r/w        */
           uint32_t FLTASS2                 : 1;  /* [2]            r/w        */
           uint32_t FLTASS3                 : 1;  /* [3]            r/w        */
           uint32_t FLTASS4                 : 1;  /* [4]            r/w        */
           uint32_t FLTASS5                 : 1;  /* [5]            r/w        */
           uint32_t FLTASS6                 : 1;  /* [6]            r/w        */
           uint32_t FLTASS7                 : 1;  /* [7]            r/w        */
           uint32_t RSVD_31_8               :24;  /* [31:8]         ro         */
    } MCPWM_FLTASS;

    /* 0x98*/
    struct {
           uint32_t FLTBSS0                 : 1;  /* [0]            r/w        */
           uint32_t FLTBSS1                 : 1;  /* [1]            r/w        */
           uint32_t FLTBSS2                 : 1;  /* [2]            r/w        */
           uint32_t FLTBSS3                 : 1;  /* [3]            r/w        */
           uint32_t FLTBSS4                 : 1;  /* [4]            r/w        */
           uint32_t FLTBSS5                 : 1;  /* [5]            r/w        */
           uint32_t FLTBSS6                 : 1;  /* [6]            r/w        */
           uint32_t FLTBSS7                 : 1;  /* [7]            r/w        */
           uint32_t RSVD_31_8               :24;  /* [31:8]         ro         */
    } MCPWM_FLTBSS;

    /* 0x9C*/
    struct {
           uint32_t SWTRIG                  : 1;  /* [0]            r/w        */
           uint32_t SYNCOSWC                : 1;  /* [1]            r/w        */
           uint32_t SWWRBUF                 : 1;  /* [2]            r/w        */
           uint32_t SWRSTCNT                : 1;  /* [3]            r/w        */
           uint32_t RSVD_31_4               :28;  /* [31:4]         ro         */
    } MCPWM_SYNC;

    /* 0xA0*/
    struct {
           uint32_t CPWMFCR0                : 1;  /* [0]            r/w        */
           uint32_t CPWMFCR1                : 1;  /* [1]            r/w        */
           uint32_t CPWMFCR2                : 1;  /* [2]            r/w        */
           uint32_t CPWMFCR3                : 1;  /* [3]            r/w        */
           uint32_t CPWMHCR0                : 1;  /* [4]            r/w        */
           uint32_t CPWMHCR1                : 1;  /* [5]            r/w        */
           uint32_t CPWMHCR2                : 1;  /* [6]            r/w        */
           uint32_t CPWMHCR3                : 1;  /* [7]            r/w        */
           uint32_t LOADEN0                 : 1;  /* [8]            r/w        */
           uint32_t LOADEN1                 : 1;  /* [9]            r/w        */
           uint32_t LOADEN2                 : 1;  /* [10]           r/w        */
           uint32_t LOADEN3                 : 1;  /* [11]           r/w        */
           uint32_t RSVD_31_12              :20;  /* [31:12]        ro         */
    } MCPWM_RELOAD;

    /* 0xA4*/
    struct {
           uint32_t LDFREQ0                 : 5;  /* [4:0]          r/w        */
           uint32_t RSVD_7_5                : 3;  /* [7:5]          ro         */
           uint32_t LDFREQ1                 : 5;  /* [12:8]         r/w        */
           uint32_t RSVD_15_13              : 3;  /* [15:13]        ro         */
           uint32_t LDFREQ2                 : 5;  /* [20:16]        r/w        */
           uint32_t RSVD_23_21              : 3;  /* [23:21]        ro         */
           uint32_t LDFREQ3                 : 5;  /* [28:24]        r/w        */
           uint32_t RSVD_31_29              : 3;  /* [31:29]        ro         */
    } MCPWM_LDFREQ;

    uint8_t zResverd0x0A8[88];   /*pad 0x0A8 - 0FF*/

    /* 0x100 - 0x10F*/
    struct {
           uint32_t MOD_DITHER              : 5;  /* [4:0]          r/w        */
           uint32_t RSVD_31_5               :27;  /* [31:5]         ro         */
    } MCPWM_MOD_DITHER[4];

    /* 0x110 - 0x12F*/
    struct {
           uint32_t CV_DITHER               : 5;  /* [4:0]          r/w        */
           uint32_t RSVD_31_5               :27;  /* [31:5]         ro         */
    } MCPWM_CV_DITHER[8];

};    /*mcpwm_reg*/

struct mcpwm_reg_w {
    /* 0x00*/
    uint32_t MCPWM_TIMEBASE;
    /* 0x04 - 0x13*/
    uint32_t MCPWM_CNT[4];
    /* 0x14 - 0x23*/
    uint32_t MCPWM_MOD[4];
    /* 0x24 - 0x33*/
    uint32_t MCPWM_DTVAL[4];
    /* 0x34*/
    uint32_t MCPWM_GLBCR;
    /* 0x38*/
    uint32_t MCPWM_GLBSR;
    /* 0x3C - 0x5B*/
    uint32_t MCPWM_CFG[8];
    /* 0x5C - 0x7B*/
    uint32_t MCPWM_CV[8];
    /* 0x7C*/
    uint32_t MCPWM_OUTCR;
    /* 0x80*/
    uint32_t MCPWM_OUTTRIG;
    /* 0x84*/
    uint32_t MCPWM_OUTSWCR;
    /* 0x88*/
    uint32_t MCPWM_PCR;
    /* 0x8C*/
    uint32_t MCPWM_FLTCR;
    /* 0x90*/
    uint32_t MCPWM_FLTSR;
    /* 0x94*/
    uint32_t MCPWM_FLTASS;
    /* 0x98*/
    uint32_t MCPWM_FLTBSS;
    /* 0x9C*/
    uint32_t MCPWM_SYNC;
    /* 0xA0*/
    uint32_t MCPWM_RELOAD;
    /* 0xA4*/
    uint32_t MCPWM_LDFREQ;
    /*pad 0x0A8 - 0FF*/
    uint8_t zResverd0x0A8[88];   
    /* 0x100 - 0x10F*/
    uint32_t MCPWM_MOD_DITHER[4];
    /* 0x110 - 0x12F*/
    uint32_t MCPWM_CV_DITHER[8];
};    /*mcpwm_reg*/

typedef volatile struct mcpwm_reg mcpwm_reg_t;
typedef volatile struct mcpwm_reg_w mcpwm_reg_w_t;

struct parcc_reg {
    /* 0x0*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_15_2               :14;  /* [15:2]         ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_WDOG;

    /* 0x4*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_EWDT;

    /* 0x8*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_STIM;

    /* 0xC*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_TIM0;

    /* 0x10*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_TIM1;

    /* 0x14*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_TIM2;

    /* 0x18*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_TIM3;

    /* 0x1C*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_MCPWM0;

    /* 0x20*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_MCPWM1;

    /* 0x24*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_TDG0;

    /* 0x28*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_TDG1;

    /* 0x2C*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_CAN0;

    /* 0x30*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_CAN1;

    /* 0x34*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_CAN2;

    /* 0x38*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_CAN3;

    /* 0x3C*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_CAN4;

    /* 0x40*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_CAN5;

    /* 0x44*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_CAN6;

    /* 0x48*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_CAN7;

    /* 0x4C*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_UART0;

    /* 0x50*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_UART1;

    /* 0x54*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_UART2;

    /* 0x58*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_UART3;

    /* 0x5C*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_UART4;

    /* 0x60*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_UART5;

    /* 0x64*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_SPI0;

    /* 0x68*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_SPI1;

    /* 0x6C*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_SPI2;

    /* 0x70*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_SPI3;

    /* 0x74*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_I2C0;

    /* 0x78*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_I2C1;

    /* 0x7C*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_I2S0;

    /* 0x80*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_I2S1;

    uint8_t zResverd0x084[4];   /*pad 0x084 - 087*/

    /* 0x88*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_ADC0;

    /* 0x8C*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_ADC1;

    /* 0x90*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_15_2               :14;  /* [15:2]         ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_CMP0;

    /* 0x94*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_15_2               :14;  /* [15:2]         ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_CRC;

    /* 0x98*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_15_2               :14;  /* [15:2]         ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_AES;

    /* 0x9C*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_15_2               :14;  /* [15:2]         ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_TRNG;

    /* 0xA0*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t RSVD_16                 : 1;  /* [16]           ro         */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t RSVD_20                 : 1;  /* [20]           ro         */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_FLASH;

    uint8_t zResverd0x0A4[4];   /*pad 0x0A4 - 0A7*/

    /* 0xA8*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_15_2               :14;  /* [15:2]         ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_DMA;

    /* 0xAC*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_15_2               :14;  /* [15:2]         ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_DMAMUX;

    /* 0xB0*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_PORTA;

    /* 0xB4*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_PORTB;

    /* 0xB8*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_PORTC;

    /* 0xBC*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_PORTD;

    /* 0xC0*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_PORTE;

    /* 0xC4*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_15_2               :14;  /* [15:2]         ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_TMU;

    /* 0xC8*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_15_2               :14;  /* [15:2]         ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_REGFILE;

    /* 0xCC*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_15_2               :14;  /* [15:2]         ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_SMPU;

    /* 0xD0*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_15_2               :14;  /* [15:2]         ro         */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t PPR                     : 1;  /* [24]           ro         */
           uint32_t PCLKMUXPR               : 1;  /* [25]           ro         */
           uint32_t PCLKDIVPR               : 1;  /* [26]           ro         */
           uint32_t PSUPVACPR               : 1;  /* [27]           ro         */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_GPIO;

};    /*parcc_reg*/

struct parcc_reg_w {
    /* 0x0*/
    uint32_t PARCC_WDOG;
    /* 0x4*/
    uint32_t PARCC_EWDT;
    /* 0x8*/
    uint32_t PARCC_STIM;
    /* 0xC*/
    uint32_t PARCC_TIM0;
    /* 0x10*/
    uint32_t PARCC_TIM1;
    /* 0x14*/
    uint32_t PARCC_TIM2;
    /* 0x18*/
    uint32_t PARCC_TIM3;
    /* 0x1C*/
    uint32_t PARCC_MCPWM0;
    /* 0x20*/
    uint32_t PARCC_MCPWM1;
    /* 0x24*/
    uint32_t PARCC_TDG0;
    /* 0x28*/
    uint32_t PARCC_TDG1;
    /* 0x2C*/
    uint32_t PARCC_CAN0;
    /* 0x30*/
    uint32_t PARCC_CAN1;
    /* 0x34*/
    uint32_t PARCC_CAN2;
    /* 0x38*/
    uint32_t PARCC_CAN3;
    /* 0x3C*/
    uint32_t PARCC_CAN4;
    /* 0x40*/
    uint32_t PARCC_CAN5;
    /* 0x44*/
    uint32_t PARCC_CAN6;
    /* 0x48*/
    uint32_t PARCC_CAN7;
    /* 0x4C*/
    uint32_t PARCC_UART0;
    /* 0x50*/
    uint32_t PARCC_UART1;
    /* 0x54*/
    uint32_t PARCC_UART2;
    /* 0x58*/
    uint32_t PARCC_UART3;
    /* 0x5C*/
    uint32_t PARCC_UART4;
    /* 0x60*/
    uint32_t PARCC_UART5;
    /* 0x64*/
    uint32_t PARCC_SPI0;
    /* 0x68*/
    uint32_t PARCC_SPI1;
    /* 0x6C*/
    uint32_t PARCC_SPI2;
    /* 0x70*/
    uint32_t PARCC_SPI3;
    /* 0x74*/
    uint32_t PARCC_I2C0;
    /* 0x78*/
    uint32_t PARCC_I2C1;
    /* 0x7C*/
    uint32_t PARCC_I2S0;
    /* 0x80*/
    uint32_t PARCC_I2S1;
    uint8_t zResverd0x084[4];   /*pad 0x084 - 087*/

    /* 0x88*/
    uint32_t PARCC_ADC0;
    /* 0x8C*/
    uint32_t PARCC_ADC1;
    /* 0x90*/
    uint32_t PARCC_CMP0;
    /* 0x94*/
    uint32_t PARCC_CRC;
    /* 0x98*/
    uint32_t PARCC_AES;
    /* 0x9C*/
    uint32_t PARCC_TRNG;
    /* 0xA0*/
    uint32_t PARCC_FLASH;
    uint8_t zResverd0x0A4[4];   /*pad 0x0A4 - 0A7*/

    /* 0xA8*/
    uint32_t PARCC_DMA;
    /* 0xAC*/
    uint32_t PARCC_DMAMUX;
    /* 0xB0*/
    uint32_t PARCC_PORTA;
    /* 0xB4*/
    uint32_t PARCC_PORTB;
    /* 0xB8*/
    uint32_t PARCC_PORTC;
    /* 0xBC*/
    uint32_t PARCC_PORTD;
    /* 0xC0*/
    uint32_t PARCC_PORTE;
    /* 0xC4*/
    uint32_t PARCC_TMU;
    /* 0xC8*/
    uint32_t PARCC_REGFILE;
    /* 0xCC*/
    uint32_t PARCC_SMPU;
    /* 0xD0*/
    uint32_t PARCC_GPIO;
};    /*parcc_reg*/

typedef volatile struct parcc_reg parcc_reg_t;
typedef volatile struct parcc_reg_w parcc_reg_w_t;

struct pmu_reg {
    /* 0x00*/
    struct {
           uint32_t RSVD_30_0               :31;  /* [30:0]         ro         */
           uint32_t LOCK                    : 1;  /* [31]           w/r        */
    } PMU_LOCK;

    /* 0x04*/
    struct {
           uint32_t LPO_CLK_DIS             : 1;  /* [0]            r/w        */
           uint32_t RSVD_1                  : 1;  /* [1]            ro         */
           uint32_t LPO_CLK_READY           : 1;  /* [2]            ro         */
           uint32_t RSVD_31_3               :29;  /* [31:3]         ro         */
    } PMU_LPO_32K_CFG;

    uint8_t zResverd0x08[4];   /*pad 0x08 - 0B*/

    /* 0x0c*/
    struct {
           uint32_t ISO_CLR                 : 1;  /* [0]            w1c        */
           uint32_t RSVD_31_1               :31;  /* [31:1]         ro         */
    } PMU_ISO_CLR;

    /* 0x10*/
    struct {
           uint32_t VDD_LVD_LP_EN           : 1;  /* [0]            r/w        */
           uint32_t VDD_LVD_ACT_EN          : 1;  /* [1]            r/w        */
           uint32_t VDD_LVD_IE              : 1;  /* [2]            r/w        */
           uint32_t VDD_LVD_RE              : 1;  /* [3]            r/w        */
           uint32_t VDD_LVW_EN              : 1;  /* [4]            r/w        */
           uint32_t VDD_LVW_IE              : 1;  /* [5]            r/w        */
           uint32_t LVWF_VDD                : 1;  /* [6]            w1c        */
           uint32_t LVDF_VDD                : 1;  /* [7]            w1c        */
           uint32_t REF_BUF_1V_EN           : 1;  /* [8]            r/w        */
           uint32_t RSVD_31_9               : 23; /* [31:9]         ro         */
    } PMU_CSR;

    /* 0x14*/
    struct {
           uint32_t LDO_CORE_EN             : 1;  /* [0]            r/w        */
           uint32_t LDO_CLOCK_EN            : 1;  /* [1]            r/w        */
           uint32_t LDO_FLASH_EN            : 1;  /* [2]            r/w        */
           uint32_t RSVD_3                  : 1;  /* [3]            ro         */
           uint32_t LDO_CORE_LPEN           : 1;  /* [4]            r/w        */
           uint32_t LDO_CLOCK_LPEN          : 1;  /* [5]            r/w        */
           uint32_t LDO_FLASH_LPEN          : 1;  /* [6]            r/w        */
           uint32_t RSVD_31_7               :25;  /* [31:7]         ro         */
    } PMU_LDO_EN_CFG;

    /* 0x18*/
    struct {
           uint32_t LVD_CORE_FLAG           : 1;  /* [0]            w1c        */
           uint32_t LVD_CLOCK_FLAG          : 1;  /* [1]            w1c        */
           uint32_t LVD_FLASH_FLAG          : 1;  /* [2]            w1c        */
           uint32_t RSVD_3                  : 1;  /* [3]            ro         */
           uint32_t LVD_AOA_FLAG            : 1;  /* [4]            w1c        */
           uint32_t RSVD_31_5               :27;  /* [31:5]         ro         */
    } PMU_LDO_LVD_STATUS;

    /* 0x1c*/
    struct {
           uint32_t LVD_CORE_RE             : 1;  /* [0]            r/w        */
           uint32_t LVD_CLOCK_RE            : 1;  /* [1]            r/w        */
           uint32_t LVD_FLASH_RE            : 1;  /* [2]            r/w        */
           uint32_t RSVD_3                  : 1;  /* [3]            ro         */
           uint32_t LVD_AOA_RE              : 1;  /* [4]            r/w        */
           uint32_t ACT_CORE_LVDE           : 1;  /* [5]            r/w        */
           uint32_t ACT_CLOCK_LVDE          : 1;  /* [6]            r/w        */
           uint32_t RSVD_8_7                : 2;  /* [8:7]          ro         */
           uint32_t ACT_AOA_LVDE            : 1;  /* [9]            r/w        */
           uint32_t LP_CORE_LVDE            : 1;  /* [10]           r/w        */
           uint32_t LP_CLOCK_LVDE           : 1;  /* [11]           r/w        */
           uint32_t RSVD_13_12              : 2;  /* [13:12]        ro         */
           uint32_t LP_AOA_LVDE             : 1;  /* [14]           r/w        */
           uint32_t RSVD_31_15              :17;  /* [31:15]        ro         */
    } PMU_LDO_LVD_CFG;

};    /*pmu_reg*/

struct pmu_reg_w {
    /* 0x00*/
    uint32_t PMU_LOCK;
    /* 0x04*/
    uint32_t PMU_LPO_32K_CFG;
    uint8_t zResverd0x08[4];   /*pad 0x08 - 0B*/

    /* 0x0c*/
    uint32_t PMU_ISO_CLR;
    /* 0x10*/
    uint32_t PMU_CSR;
    /* 0x14*/
    uint32_t PMU_LDO_EN_CFG;
    /* 0x18*/
    uint32_t PMU_LDO_LVD_STATUS;
    /* 0x1c*/
    uint32_t PMU_LDO_LVD_CFG;
};    /*pmu_reg_w*/

typedef volatile struct pmu_reg pmu_reg_t;
typedef volatile struct pmu_reg_w pmu_reg_w_t;

struct port_reg {
    /* 0x0*/
    uint8_t zResverd0x0[8];  


    /* 0x8*/
    struct {
           uint32_t GPWD                    :32;  /* [31:0]         r/w        */
    } PORTx_GLBDAT;

    /* 0xC*/
    struct {
           uint32_t GPWE                    :32;  /* [31:0]         wo         */
    } PORTx_GLBCTL;

    /* 0x10*/
    struct {
           uint32_t PS                      : 1;  /* [0]            r/w        */
           uint32_t PE                      : 1;  /* [1]            r/w        */
           uint32_t RSVD_2                  : 1;  /* [2]            ro         */
           uint32_t SRE                     : 1;  /* [3]            r/w        */
           uint32_t PFE                     : 1;  /* [4]            r/w        */
           uint32_t ODE                     : 1;  /* [5]            r/w        */
           uint32_t RSVD_7_6                : 2;  /* [7:6]          ro         */
           uint32_t MUX                     : 3;  /* [10:8]         r/w        */
           uint32_t RSVD_14_11              : 4;  /* [14:11]        ro         */
           uint32_t LK                      : 1;  /* [15]           r/w        */
           uint32_t IRQC                    : 4;  /* [19:16]        r/w        */
           uint32_t RSVD_22_20              : 3;  /* [22:20]        ro         */
           uint32_t ISF                     : 1;  /* [23]           r/w        */
           uint32_t FLT                     : 5;  /* [28:24]        r/w        */
           uint32_t RSVD_30_29              : 2;  /* [30:29]        ro         */
           uint32_t FLTEN                   : 1;  /* [31]           r/w        */
    } PORTx_PCRn[32];

    /* 0x90*/
    struct {
           uint32_t ISF                     :32;  /* [31:0]         r/w        */
    } PORTx_IRQFLG;
};    /*port_reg*/

struct port_reg_w {
    /* 0x0*/
    uint8_t zResverd0x0[8]; 
    /* 0x8*/
    uint32_t PORTx_GLBDAT;
    /* 0xC*/
    uint32_t PORTx_GLBCTL;
    /* 0x10*/
    uint32_t PORTx_PCRn[32];
    /* 0x90*/
    uint32_t PORTx_IRQFLG;
};    /*port_reg*/

typedef volatile struct port_reg port_reg_t;
typedef volatile struct port_reg_w port_reg_w_t;

struct regfile_reg {
    /* 0x0*/
    struct {
           uint32_t DATA                    :32;  /* [31:0]         r/w        */
    } REGFILE_REGn[32];

};    /*regfile_reg*/

struct regfile_reg_w {
    /* 0x0*/
    uint32_t REGFILE_REGn[32];
};    /*regfile_reg*/

typedef volatile struct regfile_reg regfile_reg_t;
typedef volatile struct regfile_reg_w regfile_reg_w_t;

struct rtc_reg {
    /* 0x00*/
    struct {
           uint32_t CRYSTAL_EN              : 1;  /* [0]            r/w        */
           uint32_t CNT_CLK_SEL             : 1;  /* [1]            r/w        */
           uint32_t CLKOUT_SEL              : 1;  /* [2]            r/w        */
           uint32_t CLKOUT_PIN_EN           : 1;  /* [3]            r/w        */
           uint32_t SUP_EN                  : 1;  /* [4]            r/w        */
           uint32_t SW_RST                  : 1;  /* [5]            r/w        */
           uint32_t COUNT_EN                : 1;  /* [6]            r/w        */
           uint32_t OVF                     : 1;  /* [7]            ro         */
           uint32_t ALARM_MATCHF            : 1;  /* [8]            ro         */
           uint32_t OSC_RDY                 : 1;  /* [9]            ro         */
           uint32_t EXTAL_32K_EN            : 1;  /* [10]           r/w        */
           uint32_t SECONDS_INT_FLAG        : 1;  /* [11]           w1c        */
           uint32_t PERIODIC_CNT_EN         : 1;  /* [12]           r/w        */
           uint32_t PERIODIC_MATCH_FLG      : 1;  /* [13]           w1c        */
           uint32_t RSVD_31_14              :18;  /* [31:14]        ro         */
    } RTC_CSR;

    /* 0x04*/
    struct {
           uint32_t SECOND_INT_MUX_SEL      : 3;  /* [2:0]          r/w        */
           uint32_t OVFLOW_IE               : 1;  /* [3]            r/w        */
           uint32_t ALARM_IE                : 1;  /* [4]            r/w        */
           uint32_t SECONDS_IE              : 1;  /* [5]            r/w        */
           uint32_t PERIODIC_IE             : 1;  /* [6]            r/w        */
           uint32_t RSVD_31_7               :25;  /* [31:7]         ro         */
    } RTC_IER;

    /* 0x08*/
    struct {
           uint32_t ALARM_CNT               :32;  /* [31:0]         r/w        */
    } RTC_ALARM_CNTR;

    /* 0x0c*/
    struct {
           uint32_t ONE_SECOND_CNT          :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } RTC_ONE_SECOND_CNTR;

    /* 0x10*/
    struct {
           uint32_t MATCH_CNT               :32;  /* [31:0]         r/w        */
    } RTC_MATCH_CNTR;

    /* 0x14*/
    struct {
           uint32_t COMP_CNT                : 7;  /* [6:0]          r/w        */
           uint32_t COMP_DIRECTION          : 1;  /* [7]            r/w        */
           uint32_t DLY                     : 8;  /* [15:8]         r/w        */
           uint32_t CCOMP_CNT               : 8;  /* [23:16]        ro         */
           uint32_t CDLY                    : 8;  /* [31:24]        ro         */
    } RTC_COMPENSATIONR;

    /* 0x18*/
    struct {
           uint32_t RSVD_30_0               :31;  /* [30:0]         ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } RTC_LOCKR;

    uint8_t zResverd0x01C[4];   /*pad 0x01C - 01F*/

    /* 0x20*/
    struct {
           uint32_t PERIODIC_TMR_CNT        :32;  /* [31:0]         r/w        */
    } RTC_PERIODIC_TMR_CNT;

    /* 0x24*/
    struct {
           uint32_t PERIODIC_MATCH_CNT      :32;  /* [31:0]         r/w        */
    } RTC_PERIODIC_TMR_MATCH_CNT;

};    /*rtc_reg*/

struct rtc_reg_w {
    /* 0x00*/
    uint32_t RTC_CSR;
    /* 0x04*/
    uint32_t RTC_IER;
    /* 0x08*/
    uint32_t RTC_ALARM_CNTR;
    /* 0x0c*/
    uint32_t RTC_ONE_SECOND_CNTR;
    /* 0x10*/
    uint32_t RTC_MATCH_CNTR;
    /* 0x14*/
    uint32_t RTC_COMPENSATIONR;
    /* 0x18*/
    uint32_t RTC_LOCKR;
    uint8_t zResverd0x01C[4];   /*pad 0x01C - 01F*/

    /* 0x20*/
    uint32_t RTC_PERIODIC_TMR_CNT;
    /* 0x24*/
    uint32_t RTC_PERIODIC_TMR_MATCH_CNT;
};    /*rtc_reg*/

typedef volatile struct rtc_reg rtc_reg_t;
typedef volatile struct rtc_reg_w rtc_reg_w_t;

struct scc_reg {
    /* 0x0*/
    uint32_t zResverd0x0;

    /* 0x4*/
    struct {
           uint32_t CLKSPRES                : 5;  /* [4:0]          ro         */
           uint32_t RSVD_27_5               :23;  /* [27:5]         ro         */
           uint32_t DIVPRES                 : 3;  /* [30:28]        ro         */
           uint32_t RSVD_31                 : 1;  /* [31]           ro         */
    } SCC_PARAM;

    /* 0x8*/
    struct {
           uint32_t DIVSLOW                 : 4;  /* [3:0]          ro         */
           uint32_t DIVBUS                  : 4;  /* [7:4]          ro         */
           uint32_t DIVCORE                 : 4;  /* [11:8]         ro         */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t SCS                     : 3;  /* [18:16]        ro         */
           uint32_t RSVD_31_19              :13;  /* [31:19]        ro         */
    } SCC_CST;

    /* 0xC*/
    struct {
           uint32_t DIVSLOW                 : 4;  /* [3:0]          r/w        */
           uint32_t DIVBUS                  : 4;  /* [7:4]          r/w        */
           uint32_t DIVCORE                 : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t SCS                     : 3;  /* [18:16]        r/w        */
           uint32_t RSVD_30_19              :12;  /* [30:19]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } SCC_CFG;

    /* 0x10*/
    struct {
           uint32_t RSVD_15_0               :16;  /* [15:0]         ro         */
           uint32_t CLKOUTSEL               : 4;  /* [19:16]        r/w        */
           uint32_t RSVD_31_20              :12;  /* [31:20]        ro         */
    } SCC_CLKOUTCFG;

    /* 0x14*/
    struct {
           uint32_t OSCEN                   : 1;  /* [0]            r/w        */
           uint32_t OSCSTOPEN               : 1;  /* [1]            r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t OSCLOCINTEN             : 1;  /* [4]            r/w        */
           uint32_t RSVD_8_5                : 4;  /* [8:5]          ro         */
           uint32_t OSCCME                  : 1;  /* [9]            r/w        */
           uint32_t OSCCMRE                 : 1;  /* [10]           r/w        */
           uint32_t RSVD_15_11              : 5;  /* [15:11]        ro         */
           uint32_t OSCRDY                  : 1;  /* [16]           ro         */
           uint32_t OSCSELD                 : 1;  /* [17]           ro         */
           uint32_t OSCLOC                  : 1;  /* [18]           r/w        */
           uint32_t RSVD_30_19              :12;  /* [30:19]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } SCC_OSCCS;

    /* 0x18*/
    struct {
           uint32_t EXCLKS                  : 1;  /* [0]            r/w        */
           uint32_t OLMEN                   : 1;  /* [1]            r/w        */
           uint32_t HFREQ                   : 1;  /* [2]            r/w        */
           uint32_t RSVD_7_3                : 5;  /* [7:3]          ro         */
           uint32_t ITRIM                   : 2;  /* [9:8]          r/w        */
           uint32_t RSVD_30_10              :21;  /* [30:10]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } SCC_OSCCFG;

    /* 0x1C*/
    struct {
           uint32_t FIRCEN                  : 1;  /* [0]            r/w        */
           uint32_t FIRCSTOPEN              : 1;  /* [1]            r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t FIRCLOCINTEN            : 1;  /* [4]            r/w        */
           uint32_t RSVD_8_5                : 4;  /* [8:5]          ro         */
           uint32_t FIRCCME                 : 1;  /* [9]            r/w        */
           uint32_t FIRCCMRE                : 1;  /* [10]           r/w        */
           uint32_t RSVD_11                 : 1;  /* [11]           ro         */
           uint32_t RSVD_12                 : 1;  /* [12]           ro         */
           uint32_t RSVD_15_13              : 3;  /* [15:13]        ro         */
           uint32_t FIRCRDY                 : 1;  /* [16]           ro         */
           uint32_t FIRCSELD                : 1;  /* [17]           ro         */
           uint32_t FIRCLOC                 : 1;  /* [18]           r/w        */
           uint32_t RSVD_30_19              :12;  /* [30:19]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } SCC_FIRCCS;

    uint8_t zResverd0x020[8];   /*pad 0x020 - 027*/


    /* 0x28*/
    struct {
           uint32_t SPLLEN                  : 1;  /* [0]            r/w        */
           uint32_t SPLLSTOPEN              : 1;  /* [1]            r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t RSVD_4                  : 1;  /* [4]            ro         */
           uint32_t RSVD_8_5                : 4;  /* [8:5]          ro         */
           uint32_t RDYEN                   : 1;  /* [9]            r/w        */
           uint32_t RSVD_10                 : 1;  /* [10]           ro         */
           uint32_t RSVD_11                 : 1;  /* [11]           ro         */
           uint32_t LOCKWIN                 : 2;  /* [13:12]        r/w        */
           uint32_t RSVD_15_14              : 2;  /* [15:14]        ro         */
           uint32_t SPLLRDY                 : 1;  /* [16]           ro         */
           uint32_t SPLLSELD                : 1;  /* [17]           ro         */
           uint32_t RSVD_18                 : 1;  /* [18]           ro         */
           uint32_t RSVD_24_19              : 6;  /* [24:19]        ro         */
           uint32_t OUTEN                   : 1;  /* [25]           r/w        */
           uint32_t RSVD_30_26              : 5;  /* [30:26]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } SCC_SPLLCS;

    /* 0x2C*/
    struct {
           uint32_t PREDIV                  : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t FBPRESEN                : 1;  /* [4]            r/w        */
           uint32_t REFCKS                  : 1;  /* [5]            r/w        */
           uint32_t RSVD_7_6                : 2;  /* [7:6]          ro         */
           uint32_t MULT                    : 8;  /* [15:8]         r/w        */
           uint32_t POSTDIV                 : 3;  /* [18:16]        r/w        */
           uint32_t RSVD_30_19              :12;  /* [30:19]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } SCC_SPLLCFG1;

    /* 0x30*/
    struct {
           uint32_t CPIR                    : 2;  /* [1:0]          r/w        */
           uint32_t CPIC                    : 2;  /* [3:2]          r/w        */
           uint32_t CS                      : 2;  /* [5:4]          r/w        */
           uint32_t CAP                     : 2;  /* [7:6]          r/w        */
           uint32_t RES                     : 3;  /* [10:8]         r/w        */
           uint32_t KVCO                    : 1;  /* [11]           r/w        */
           uint32_t VCODIV                  : 1;  /* [12]           r/w        */
           uint32_t PFDDIEN                 : 1;  /* [13]           r/w        */
           uint32_t CPISEL                  : 1;  /* [14]           r/w        */
           uint32_t RSVD_15                 : 1;  /* [15]           ro         */
           uint32_t RSVD_23_16              : 8;  /* [23:16]        ro         */
           uint32_t LDOODEN                 : 1;  /* [24]           r/w        */
           uint32_t RSVD_30_25              : 6;  /* [30:25]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } SCC_SPLLCFG2;

};    /*scc_reg*/

struct scc_reg_w {
    /* 0x0*/
    uint32_t zResverd0x0;
    /* 0x4*/
    uint32_t SCC_PARAM;
    /* 0x8*/
    uint32_t SCC_CST;
    /* 0xC*/
    uint32_t SCC_CFG;
    /* 0x10*/
    uint32_t SCC_CLKOUTCFG;
    /* 0x14*/
    uint32_t SCC_OSCCS;
    /* 0x18*/
    uint32_t SCC_OSCCFG;
    /* 0x1C*/
    uint32_t SCC_FIRCCS;
    uint8_t zResverd0x020[8];   /*pad 0x020 - 027*/

    /* 0x28*/
    uint32_t SCC_SPLLCS;
    /* 0x2C*/
    uint32_t SCC_SPLLCFG1;
    /* 0x30*/
    uint32_t SCC_SPLLCFG2;

};    /*scc_reg*/

typedef volatile struct scc_reg scc_reg_t;
typedef volatile struct scc_reg_w scc_reg_w_t;

struct scm_reg {
    /* 0x00*/
    struct {
           uint32_t RSVD_3_0                : 4;  /* [3:0]          ro         */
           uint32_t CLKOUTSEL               : 2;  /* [5:4]          r/w        */
           uint32_t RSVD_7_6                : 2;  /* [7:6]          ro         */
           uint32_t CLKOUTDIV               : 3;  /* [10:8]         r/w        */
           uint32_t CLKOUTEN                : 1;  /* [11]           r/w        */
           uint32_t RSVD_31_12              :20;  /* [31:12]        ro         */
    } SCM_CHIPCTL;

    /* 0x04*/
    struct {
           uint32_t SWTRIG0                 : 1;  /* [0]            r/w        */
           uint32_t SWTRIG1                 : 1;  /* [1]            r/w        */
           uint32_t SWTRIG2                 : 1;  /* [2]            r/w        */
           uint32_t SWTRIG3                 : 1;  /* [3]            r/w        */
           uint32_t SRAML_READ_BUFF_EN      : 1;  /* [4]            r/w        */
           uint32_t SRAMU_READ_BUFF_EN      : 1;  /* [5]            r/w        */
           uint32_t XBAR_ROUND_ROBIN        : 1;  /* [6]            r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t RSVD_8                  : 1;  /* [8]            ro         */
           uint32_t RSVD_9                  : 1;  /* [9]            ro         */
           uint32_t RSVD_10                 : 1;  /* [10]           ro         */
           uint32_t CCACHE_CLR              : 1;  /* [11]           r/w        */
           uint32_t CCACHE_PARITY_MISS_EN   : 1;  /* [12]           r/w        */
           uint32_t CCACHE_PARITY_FAULT_EN  : 1;  /* [13]           r/w        */
           uint32_t CACHE_DIS               : 1;  /* [14]           r/w        */
           uint32_t RSVD_15                 : 1;  /* [15]           ro         */
           uint32_t CCACHE_BE_INT_EN        : 1;  /* [16]           r/w        */
           uint32_t RSVD_23_17              : 7;  /* [23:17]        ro         */
           uint32_t FPU_INEXACT_INT_EN      : 1;  /* [24]           r/w        */
           uint32_t FPU_OVERFLOW_INT_EN     : 1;  /* [25]           r/w        */
           uint32_t FPU_UNDERFLOW_INT_EN    : 1;  /* [26]           r/w        */
           uint32_t FPU_INVALIDOP_INT_EN    : 1;  /* [27]           r/w        */
           uint32_t FPU_DIVZERO_INT_EN      : 1;  /* [28]           r/w        */
           uint32_t FPU_DENORMALIN_INT_EN   : 1;  /* [29]           r/w        */
           uint32_t RSVD_31_30              : 2;  /* [31:30]        ro         */
    } SCM_MISCCTL1;

    uint8_t zResverd0x08[32];   /*pad 0x08 - 027*/

    /* 0x28*/
    struct {
           uint32_t RSVD_7_0                : 8;  /* [7:0]          ro         */
           uint32_t MCPWM0_TCLK_SEL         : 2;  /* [9:8]          r/w        */
           uint32_t MCPWM1_TCLK_SEL         : 2;  /* [11:10]        r/w        */
           uint32_t TIM0_TCLK_SEL           : 2;  /* [13:12]        r/w        */
           uint32_t TIM1_TCLK_SEL           : 2;  /* [15:14]        r/w        */
           uint32_t TIM2_TCLK_SEL           : 2;  /* [17:16]        r/w        */
           uint32_t TIM3_TCLK_SEL           : 2;  /* [19:18]        r/w        */
           uint32_t RSVD_23_20              : 4;  /* [23:20]        ro         */
           uint32_t ADC0_CH8_SEL            : 1;  /* [24]           r/w        */
           uint32_t ADC0_CH9_SEL            : 1;  /* [25]           r/w        */
           uint32_t ADC1_CH14_SEL           : 1;  /* [26]           r/w        */
           uint32_t ADC1_CH15_SEL           : 1;  /* [27]           r/w        */
           uint32_t RSVD_31_28              : 4;  /* [31:28]        ro         */
    } SCM_MISCCTL2;

    uint8_t zResverd0x02C[20];   /*pad 0x02C - 03F*/

    /* 0x40*/
    struct {
           uint32_t RSVD_14_0               :15;  /* [14:0]         ro         */
           uint32_t RSVD_15                 : 1;  /* [15]           ro         */
           uint32_t CCACHE_BE_FLAG          : 8;  /* [23:16]        r/w        */
           uint32_t FPU_INEXACT_FLAG        : 1;  /* [24]           r/w        */
           uint32_t FPU_OVERFLOW_FLAG       : 1;  /* [25]           r/w        */
           uint32_t FPU_UNDERFLOW_FLAG      : 1;  /* [26]           r/w        */
           uint32_t FPU_INVALIDOP_FLAG      : 1;  /* [27]           r/w        */
           uint32_t FPU_DIVZERO_FLAG        : 1;  /* [28]           r/w        */
           uint32_t FPU_DENORMALIN_FLAG     : 1;  /* [29]           r/w        */
           uint32_t RSVD_31_30              : 2;  /* [31:30]        ro         */
    } SCM_MISCSTAT1;

    /* 0x44*/
    struct {
           uint32_t CACHE_BE_ADDR           :32;  /* [31:0]         ro         */
    } SCM_MISCDATA1;

    /* 0x48*/
    struct {
           uint32_t CACHE_BE_DATA           :32;  /* [31:0]         ro         */
    } SCM_MISCDATA2;

    uint8_t zResverd0x04C[180];   /*pad 0x04C - 0FF*/

    /* 0x100*/
    struct {
           uint32_t CCACHE_DIS_IFR          : 1;  /* [0]            ro         */
           uint32_t FPU_DIS                 : 1;  /* [1]            r/w        */
           uint32_t RSVD_31_2               :30;  /* [31:2]         ro         */
    } SCM_CHIPOPT;

    /* 0x104*/
    struct {
           uint32_t RSVD_23_0               :24;  /* [23:0]         ro         */
           uint32_t PFSIZE                  : 4;  /* [27:24]        ro         */
           uint32_t DFSIZE                  : 4;  /* [31:28]        ro         */
    } SCM_FLSCFG;

    /* 0x108*/
    struct {
           uint32_t CACHESIZE               : 4;  /* [3:0]          ro         */
           uint32_t RSVD_27_4               :24;  /* [27:4]         ro         */
           uint32_t RAMSIZE                 : 4;  /* [31:28]        ro         */
    } SCM_RAMCFG;

    uint8_t zResverd0x010C[16];   /*pad 0x010C - 011B*/

    /* 0x11C*/
    struct {
           uint32_t MEMSIZE_ID              : 4;  /* [3:0]          ro         */
           uint32_t SERIES_ID               : 3;  /* [6:4]          ro         */
           uint32_t SUBFAMILY_ID            : 5;  /* [11:7]         ro         */
           uint32_t FAMILY_ID               : 4;  /* [15:12]        ro         */
           uint32_t REV_ID                  : 4;  /* [19:16]        ro         */
           uint32_t FEATURE_ID              : 7;  /* [26:20]        ro         */
           uint32_t PACKAGE_ID              : 5;  /* [31:27]        ro         */
    } SCM_DEVID;

    /* 0x120*/
    struct {
           uint32_t UID_31_0                :32;  /* [31:0]         ro         */
    } SCM_UNIQUE0;

    /* 0x124*/
    struct {
           uint32_t UID_63_32               :32;  /* [31:0]         ro         */
    } SCM_UNIQUE1;

    /* 0x128*/
    struct {
           uint32_t UID_95_64               :32;  /* [31:0]         ro         */
    } SCM_UNIQUE2;

    /* 0x12C*/
    struct {
           uint32_t UID_127_96              :32;  /* [31:0]         ro         */
    } SCM_UNIQUE3;

};    /*scm_reg*/

struct scm_reg_w {
    /* 0x00*/
    uint32_t SCM_CHIPCTL;
    /* 0x04*/
    uint32_t SCM_MISCCTL1;
    uint8_t zResverd0x08[32];   /*pad 0x08 - 027*/

    /* 0x28*/
    uint32_t SCM_MISCCTL2;
    uint8_t zResverd0x02C[20];   /*pad 0x02C - 03F*/

    /* 0x40*/
    uint32_t SCM_MISCSTAT1;
    /* 0x44*/
    uint32_t SCM_MISCDATA1;
    /* 0x48*/
    uint32_t SCM_MISCDATA2;
    uint8_t zResverd0x04C[180];   /*pad 0x04C - 0FF*/

    /* 0x100*/
    uint32_t SCM_CHIPOPT;
    /* 0x104*/
    uint32_t SCM_FLSCFG;
    /* 0x108*/
    uint32_t SCM_RAMCFG;
    uint8_t zResverd0x010C[16];   /*pad 0x010C - 011B*/

    /* 0x11C*/
    uint32_t SCM_DEVID;
    /* 0x120*/
    uint32_t SCM_UNIQUE0;
    /* 0x124*/
    uint32_t SCM_UNIQUE1;
    /* 0x128*/
    uint32_t SCM_UNIQUE2;
    /* 0x12C*/
    uint32_t SCM_UNIQUE3;
};    /*scm_reg*/

typedef volatile struct scm_reg scm_reg_t;
typedef volatile struct scm_reg_w scm_reg_w_t;

struct seru_reg {
    /* 0x0*/
    uint32_t zResverd0x0;
    /* 0x4*/
    struct {
           uint32_t PARAM                   :32;  /* [31:0]         ro         */
    } SERU_PARAM;

    /* 0x8*/
    struct {
           uint32_t CRPAR_INT_EN            : 1;  /* [0]            r/w        */
           uint32_t RSVD_3_1                : 3;  /* [3:1]          ro         */
           uint32_t EOUT_PS                 : 1;  /* [4]            r/w        */
           uint32_t EOUT0_IO_EN             : 1;  /* [5]            r/w        */
           uint32_t EOUT1_IO_EN             : 1;  /* [6]            r/w        */
           uint32_t FFI_EN                  : 1;  /* [7]            r/w        */
           uint32_t CFG_MODE                : 1;  /* [8]            ro         */
           uint32_t RSVD_31_9               :23;  /* [31:9]         ro         */
    } SERU_CSR;

    /* 0xC*/
    struct {
           uint32_t S_CRPAR_ERR             : 1;  /* [0]            w1c        */
           uint32_t RSVD_31_1               :31;  /* [31:1]         ro         */
    } SERU_INTF;

    /* 0x10*/
    struct {
           uint32_t KEY                     :32;  /* [31:0]         r/w        */
    } SERU_CFG_KEY;

    /* 0x14*/
    struct {
           uint32_t CH_FFI_6_0              : 7;  /* [6:0]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CH_FFI_14_8             : 7;  /* [14:8]         r/w        */
           uint32_t RSVD_15                 : 1;  /* [15]           ro         */
           uint32_t CH_FFI_16               : 1;  /* [16]           r/w        */
           uint32_t RSVD_31_17              :15;  /* [31:17]        ro         */
    } SERU_CH_FFI;

    /* 0x18*/
    struct {
           uint32_t SWERR_CH0               : 1;  /* [0]            r/w        */
           uint32_t SWERR_CH1               : 1;  /* [1]            r/w        */
           uint32_t SWERR_CH2               : 1;  /* [2]            r/w        */
           uint32_t RSVD_31_3               :29;  /* [31:3]         ro         */
    } SERU_SWERR_GNT;

    /* 0x1C*/
    struct {
           uint32_t CH_FLAG_6_0             : 7;  /* [6:0]          w1c        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CH_FLAG_14_8            : 7;  /* [14:8]         w1c        */
           uint32_t RSVD_15                 : 1;  /* [15]           ro         */
           uint32_t CH_FLAG_16              : 1;  /* [16]           w1c        */
           uint32_t RSVD_31_17              :15;  /* [31:17]        ro         */
    } SERU_CH_FLAG;

    /* 0x20*/
    struct {
           uint32_t CH_EN                   : 1;  /* [0]            r/w        */
           uint32_t CH_INT_CFG              : 1;  /* [1]            r/w        */
           uint32_t CH_INT_TYP              : 1;  /* [2]            r/w        */
           uint32_t CH_EOUT_CFG             : 1;  /* [3]            r/w        */
           uint32_t CH_RESET_CFG            : 1;  /* [4]            r/w        */
           uint32_t CH_RESET_TYP            : 1;  /* [5]            r/w        */
           uint32_t CH_RESET_DLY            : 2;  /* [7:6]          r/w        */
           uint32_t CH_FLAG                 : 1;  /* [8]            w1c        */
           uint32_t RSVD_31_9               :23;  /* [31:9]         ro         */
    } SERU_CFG_CHn[17];

};    /*seru_reg*/

struct seru_reg_w {
    /* 0x0*/
    uint32_t zResverd0x0;
    /* 0x4*/
    uint32_t SERU_PARAM;
    /* 0x8*/
    uint32_t SERU_CSR;
    /* 0xC*/
    uint32_t SERU_INTF;
    /* 0x10*/
    uint32_t SERU_CFG_KEY;
    /* 0x14*/
    uint32_t SERU_CH_FFI;
    /* 0x18*/
    uint32_t SERU_SWERR_GNT;
    /* 0x1C*/
    uint32_t SERU_CH_FLAG;
    /* 0x20*/
    uint32_t SERU_CFG_CHn[17];
};    /*seru_reg*/

typedef volatile struct seru_reg seru_reg_t;
typedef volatile struct seru_reg_w seru_reg_w_t;

struct smpu_reg {
    /* 0x00*/
    uint32_t zResverd0x00;
    /* 0x04*/
    struct {
           uint32_t S0ERR                   : 1;  /* [0]            w1c        */
           uint32_t S1ERR                   : 1;  /* [1]            w1c        */
           uint32_t S2ERR                   : 1;  /* [2]            w1c        */
           uint32_t RSVD_3                  : 1;  /* [3]            ro         */
           uint32_t RSVD_7_4                : 4;  /* [7:4]          ro         */
           uint32_t GLBEN                   : 1;  /* [8]            r/w        */
           uint32_t RSVD_31_9               :23;  /* [31:9]                    */
    } SMPU_CS;

    uint8_t zResverd0x08[8];   /*pad 0x08 - 0F*/

    /* 0x10*/
    struct {
           uint32_t EADDR                   :32;  /* [31:0]         ro         */
    } SMPU_Sn_EA[3];

    uint8_t zResverd0x01C[20];   /*pad 0x01C - 02F*/

    /* 0x30*/
    struct {
           uint32_t EMRC                    :16;  /* [15:0]         ro         */
           uint32_t RSVD_23_16              : 8;  /* [23:16]        ro         */
           uint32_t EMN                     : 4;  /* [27:24]        ro         */
           uint32_t EATTR                   : 1;  /* [28]           ro         */
           uint32_t EUS                     : 1;  /* [29]           ro         */
           uint32_t RSVD_30                 : 1;  /* [30]           ro         */
           uint32_t ERW                     : 1;  /* [31]           ro         */
    } SMPU_Sn_ES[3];

    uint8_t zResverd0x03C[196];   /*pad 0x03C - 0FF*/

    struct{
        /* 0x100*/
        struct {
               uint32_t RSVD_4_0                : 5;  /* [4:0]          ro         */
               uint32_t SADDR                   :27;  /* [31:5]         r/w        */
        } SMPU_MRCn_W0;

        /* 0x104*/
        struct {
               uint32_t RSVD_4_0                : 5;  /* [4:0]          ro         */
               uint32_t EADDR                   :27;  /* [31:5]         r/w        */
        } SMPU_MRCn_W1;

        /* 0x108*/
        struct {
               uint32_t M0UX                    : 1;  /* [0]            r/w        */
               uint32_t M0UW                    : 1;  /* [1]            r/w        */
               uint32_t M0UR                    : 1;  /* [2]            r/w        */
               uint32_t M0SM                    : 2;  /* [4:3]          r/w        */
               uint32_t RSVD_5                  : 1;  /* [5]            ro         */
               uint32_t M1UX                    : 1;  /* [6]            r/w        */
               uint32_t M1UW                    : 1;  /* [7]            r/w        */
               uint32_t M1UR                    : 1;  /* [8]            r/w        */
               uint32_t M1SM                    : 2;  /* [10:9]         r/w        */
               uint32_t RSVD_11                 : 1;  /* [11]           ro         */
               uint32_t M2UX                    : 1;  /* [12]           r/w        */
               uint32_t M2UW                    : 1;  /* [13]           r/w        */
               uint32_t M2UR                    : 1;  /* [14]           r/w        */
               uint32_t M2SM                    : 2;  /* [16:15]        r/w        */
               uint32_t RSVD_31_17              :15;  /* [31:17]        ro         */
        } SMPU_MRCn_W2;

        /* 0x10C*/
        struct {
               uint32_t RSVD_15_0               :16;  /* [15:0]         ro         */
               uint32_t EN                      : 1;  /* [16]           r/w        */
               uint32_t RSVD_31_17              :15;  /* [31:17]        ro         */
        } SMPU_MRCn_W3;
    }SMPU_MRCn_W[16];

};    /*smpu_reg*/

struct smpu_reg_w {
    /* 0x00*/
    uint32_t zResverd0x00;
    /* 0x04*/
    uint32_t SMPU_CS;
    uint8_t zResverd0x08[8];   /*pad 0x08 - 0F*/

    /* 0x10*/
    uint32_t SMPU_Sn_EA[3];
    uint8_t zResverd0x01C[20];   /*pad 0x01C - 02F*/

    /* 0x30*/
    uint32_t SMPU_Sn_ES[3];
    uint8_t zResverd0x03C[196];   /*pad 0x03C - 0FF*/

    /* 0x100*/
    struct {
            uint32_t  SMPU_MRCn_W0;  
            uint32_t  SMPU_MRCn_W1;
            uint32_t  SMPU_MRCn_W2; 
            uint32_t  SMPU_MRCn_W3;
    }SMPU_MRCn_W[16];
};    /*smpu_reg*/

typedef volatile struct smpu_reg smpu_reg_t;
typedef volatile struct smpu_reg_w smpu_reg_w_t;

struct spi_reg {
    /* 0x0*/
    struct {
           uint32_t RSVD_5_0                : 6;  /* [5:0]          ro         */
           uint32_t SCPH                    : 1;  /* [6]            r/w        */
           uint32_t SCPOL                   : 1;  /* [7]            r/w        */
           uint32_t TMOD                    : 2;  /* [9:8]          r/w        */
           uint32_t RSVD_10                 : 1;  /* [10]           ro         */
           uint32_t RSVD_11                 : 1;  /* [11]           ro         */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t DFS_32                  : 5;  /* [20:16]        r/w        */
           uint32_t MST_MODE                : 1;  /* [21]           r/w        */
           uint32_t RSVD_22                 : 1;  /* [22]           ro         */
           uint32_t RSVD_23                 : 1;  /* [23]           ro         */
           uint32_t RSVD_24                 : 1;  /* [24]           ro         */
           uint32_t RSVD_31_25              : 7;  /* [31:25]        ro         */
    } SPI_CTRLR0;

    /* 0x4*/
    struct {
           uint32_t NDF                     :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } SPI_CTRLR1;

    /* 0x8*/
    struct {
           uint32_t SPI_EN                  : 1;  /* [0]            r/w        */
           uint32_t RSVD_15_1               :15;  /* [15:1]         ro         */
           uint32_t SER                     : 2;  /* [17:16]        r/w        */
           uint32_t RSVD_31_18              :14;  /* [31:18]        ro         */
    } SPI_SSENR;

    /* 0xC*/
    struct {
           uint32_t SCKDV                   :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } SPI_BAUDR;

    /* 0x10*/
    struct {
           uint32_t TFT                     : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_15_2               :14;  /* [15:2]         ro         */
           uint32_t RFT                     : 2;  /* [17:16]        r/w        */
           uint32_t RSVD_31_18              :14;  /* [31:18]        ro         */
    } SPI_FTLR;

    /* 0x14*/
    struct {
           uint32_t TXTFL                   : 3;  /* [2:0]          ro         */
           uint32_t RSVD_15_3               :13;  /* [15:3]         ro         */
           uint32_t RXTFL                   : 3;  /* [18:16]        ro         */
           uint32_t RSVD_31_19              :13;  /* [31:19]        ro         */
    } SPI_FLR;

    /* 0x18*/
    struct {
           uint32_t BUSY                    : 1;  /* [0]            ro         */
           uint32_t TFNF                    : 1;  /* [1]            ro         */
           uint32_t TFE                     : 1;  /* [2]            ro         */
           uint32_t RFNE                    : 1;  /* [3]            ro         */
           uint32_t RFF                     : 1;  /* [4]            ro         */
           uint32_t TXE                     : 1;  /* [5]            ro         */
           uint32_t RSVD_31_6               :26;  /* [31:6]         ro         */
    } SPI_SR;

    /* 0x1C*/
    struct {
           uint32_t TXEIE                   : 1;  /* [0]            r/w        */
           uint32_t TXOIE                   : 1;  /* [1]            r/w        */
           uint32_t RXUIE                   : 1;  /* [2]            r/w        */
           uint32_t RXOIE                   : 1;  /* [3]            r/w        */
           uint32_t RXFIE                   : 1;  /* [4]            r/w        */
           uint32_t RSVD_31_5               :27;  /* [31:5]         ro         */
    } SPI_IER;

    /* 0x20*/
    struct {
           uint32_t TXEIS                   : 1;  /* [0]            ro         */
           uint32_t TXOIS                   : 1;  /* [1]            ro         */
           uint32_t RXUIS                   : 1;  /* [2]            ro         */
           uint32_t RXOIS                   : 1;  /* [3]            ro         */
           uint32_t RXFIS                   : 1;  /* [4]            ro         */
           uint32_t RSVD_15_5               :11;  /* [15:5]         ro         */
           uint32_t TXEIR                   : 1;  /* [16]           ro         */
           uint32_t TXOIR                   : 1;  /* [17]           ro         */
           uint32_t RXUIR                   : 1;  /* [18]           ro         */
           uint32_t RXOIR                   : 1;  /* [19]           ro         */
           uint32_t RXFIR                   : 1;  /* [20]           ro         */
           uint32_t RSVD_31_21              :11;  /* [31:21]        ro         */
    } SPI_ISR;

    /* 0x24*/
    struct {
           uint32_t TXOICR                  : 1;  /* [0]            ro         */
           uint32_t RSVD_31_1               :31;  /* [31:1]         ro         */
    } SPI_TXOICR;

    /* 0x28*/
    struct {
           uint32_t RXOICR                  : 1;  /* [0]            ro         */
           uint32_t RSVD_31_1               :31;  /* [31:1]         ro         */
    } SPI_RXOICR;

    /* 0x2c*/
    struct {
           uint32_t RXUICR                  : 1;  /* [0]            ro         */
           uint32_t RSVD_31_1               :31;  /* [31:1]         ro         */
    } SPI_RXUICR;

    uint8_t zResverd0x030[4];   /*pad 0x030 - 033*/

    /* 0x34*/
    struct {
           uint32_t ICR                     : 1;  /* [0]            ro         */
           uint32_t RSVD_31_1               :31;  /* [31:1]         ro         */
    } SPI_ICR;

    /* 0x38*/
    struct {
           uint32_t RDMAE                   : 1;  /* [0]            r/w        */
           uint32_t TDMAE                   : 1;  /* [1]            r/w        */
           uint32_t RSVD_31_2               :30;  /* [31:2]         ro         */
    } SPI_DMACR;

    /* 0x3C*/
    struct {
           uint32_t DMATDL                  : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_31_2               :30;  /* [31:2]         ro         */
    } SPI_DMATDLR;

    /* 0x40*/
    struct {
           uint32_t DMARDL                  : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_31_2               :30;  /* [31:2]         ro         */
    } SPI_DMARDLR;

    uint8_t zResverd0x044[28];   /*pad 0x044 - 05F*/

    /* 0x60*/
    struct {
           uint32_t DR                      :32;  /* [31:0]         r/w        */
    } SPI_DR_LOW;

    uint8_t zResverd0x064[136];   /*pad 0x064 - 0EB*/

    /* 0xEC*/
    struct {
           uint32_t DR                      :32;  /* [31:0]         r/w        */
    } SPI_DR_HIGH;

};    /*spi_reg*/

struct spi_reg_w {
    /* 0x0*/
    uint32_t SPI_CTRLR0;
    /* 0x4*/
    uint32_t SPI_CTRLR1;
    /* 0x8*/
    uint32_t SPI_SSENR;
    /* 0xC*/
    uint32_t SPI_BAUDR;
    /* 0x10*/
    uint32_t SPI_FTLR;
    /* 0x14*/
    uint32_t SPI_FLR;
    /* 0x18*/
    uint32_t SPI_SR;
    /* 0x1C*/
    uint32_t SPI_IER;
    /* 0x20*/
    uint32_t SPI_ISR;
    /* 0x24*/
    uint32_t SPI_TXOICR;
    /* 0x28*/
    uint32_t SPI_RXOICR;
    /* 0x2c*/
    uint32_t SPI_RXUICR;
    uint8_t zResverd0x030[4];   /*pad 0x030 - 033*/

    /* 0x34*/
    uint32_t SPI_ICR;
    /* 0x38*/
    uint32_t SPI_DMACR;
    /* 0x3C*/
    uint32_t SPI_DMATDLR;
    /* 0x40*/
    uint32_t SPI_DMARDLR;
    uint8_t zResverd0x044[28];   /*pad 0x044 - 05F*/

    /* 0x60*/
    uint32_t SPI_DR_LOW;
    uint8_t zResverd0x064[136];   /*pad 0x064 - 0EB*/

    /* 0xEC*/
    uint32_t SPI_DR_HIGH;
};    /*spi_reg*/

typedef volatile struct spi_reg spi_reg_t;
typedef volatile struct spi_reg_w spi_reg_w_t;

struct srmc_reg {
    /* 0x00*/
    uint32_t zResverd0x00;
    /* 0x04*/
    struct {
           uint32_t EWAKEUP                 : 1;  /* [0]            ro         */
           uint32_t ELVD                    : 1;  /* [1]            ro         */
           uint32_t ELOC                    : 1;  /* [2]            ro         */
           uint32_t RSVD_3                  : 1;  /* [3]            ro         */
           uint32_t RSVD_4                  : 1;  /* [4]            ro         */
           uint32_t EWDOG                   : 1;  /* [5]            ro         */
           uint32_t EPIN                    : 1;  /* [6]            ro         */
           uint32_t EPOR                    : 1;  /* [7]            ro         */
           uint32_t RSVD_8                  : 1;  /* [8]            ro         */
           uint32_t ELOCKUP                 : 1;  /* [9]            ro         */
           uint32_t ESW                     : 1;  /* [10]           ro         */
           uint32_t EADM_AP                 : 1;  /* [11]           ro         */
           uint32_t RSVD_12                 : 1;  /* [12]           ro         */
           uint32_t ESACKERR                : 1;  /* [13]           ro         */
           uint32_t RSVD_15_14              : 2;  /* [15:14]        ro         */
           uint32_t ESTB                    : 1;  /* [16]           ro         */
           uint32_t RSVD_31_17              :15;  /* [31:17]        ro         */
    } SRMC_PARAM;

    /* 0x08*/
    struct {
           uint32_t WAKEUP                  : 1;  /* [0]            ro         */
           uint32_t LVD                     : 1;  /* [1]            ro         */
           uint32_t LOC                     : 1;  /* [2]            ro         */
           uint32_t RSVD_4_3                : 2;  /* [4:3]          ro         */
           uint32_t WDOG                    : 1;  /* [5]            ro         */
           uint32_t PIN                     : 1;  /* [6]            ro         */
           uint32_t POR                     : 1;  /* [7]            ro         */
           uint32_t RSVD_8                  : 1;  /* [8]            ro         */
           uint32_t LOCKUP                  : 1;  /* [9]            ro         */
           uint32_t SW                      : 1;  /* [10]           ro         */
           uint32_t ADM_AP                  : 1;  /* [11]           ro         */
           uint32_t SERU_COLD               : 1;  /* [12]           ro         */
           uint32_t SERU_SYS                : 1;  /* [13]           ro         */
           uint32_t RSVD_14                 : 1;  /* [14]           ro         */
           uint32_t SACKERR                 : 1;  /* [15]           ro         */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } SRMC_SRS;

    /* 0x0C*/
    struct {
           uint32_t RSTFLTSRW               : 2;  /* [1:0]          r/w        */
           uint32_t RSTFLTSS                : 1;  /* [2]            r/w        */
           uint32_t RSVD_7_3                : 5;  /* [7:3]          ro         */
           uint32_t RSTFLTSEL               : 5;  /* [12:8]         r/w        */
           uint32_t RSVD_30_13              :18;  /* [30:13]        ro         */
           uint32_t LOCKUP_RST_EN           : 1;  /* [31]           r/w        */
    } SRMC_CTRL;

    uint8_t zResverd0x010[8];   /*pad 0x010 - 017*/

    /* 0x18*/
    struct {
           uint32_t SWAKEUP                 : 1;  /* [0]            w1c        */
           uint32_t SLVD                    : 1;  /* [1]            w1c        */
           uint32_t SLOC                    : 1;  /* [2]            w1c        */
           uint32_t RSVD_4_3                : 2;  /* [4:3]          ro         */
           uint32_t SWDOG                   : 1;  /* [5]            w1c        */
           uint32_t SPIN                    : 1;  /* [6]            w1c        */
           uint32_t SPOR                    : 1;  /* [7]            w1c        */
           uint32_t RSVD_8                  : 1;  /* [8]            ro         */
           uint32_t SLOCKUP                 : 1;  /* [9]            w1c        */
           uint32_t SSW                     : 1;  /* [10]           w1c        */
           uint32_t SADM_AP                 : 1;  /* [11]           w1c        */
           uint32_t SSERU_COLD              : 1;  /* [12]           w1c        */
           uint32_t SSERU_SYS               : 1;  /* [13]           w1c        */
           uint32_t RSVD_14                 : 1;  /* [14]           ro         */
           uint32_t SSACKERR                : 1;  /* [15]           w1c        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } SRMC_SSRS;

    /* 0x1C*/
    struct {
           uint32_t DELAY                   : 2;  /* [1:0]          r/w        */
           uint32_t LOC                     : 1;  /* [2]            r/w        */
           uint32_t RSVD_4_3                : 2;  /* [4:3]          ro         */
           uint32_t WDOG                    : 1;  /* [5]            r/w        */
           uint32_t PIN                     : 1;  /* [6]            r/w        */
           uint32_t GIE                     : 1;  /* [7]            r/w        */
           uint32_t RSVD_8                  : 1;  /* [8]            ro         */
           uint32_t LOCKUP                  : 1;  /* [9]            r/w        */
           uint32_t SW                      : 1;  /* [10]           r/w        */
           uint32_t RSVD_11                 : 1;  /* [11]           ro         */
           uint32_t SERU_COLD               : 1;  /* [12]           w1c        */
           uint32_t SERU_SYS                : 1;  /* [13]           w1c        */
           uint32_t RSVD_14                 : 1;  /* [14]           ro         */
           uint32_t SACKERR                 : 1;  /* [15]           r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } SRMC_SRIE;

    /* 0x20*/
    struct {
           uint32_t APD                     : 1;  /* [0]            r/w        */
           uint32_t RSVD_31_1               :31;  /* [31:1]         ro         */
    } SRMC_PMPORT;

    /* 0x24*/
    struct {
           uint32_t DSMC                    : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_7_2                : 6;  /* [7:2]          ro         */
           uint32_t DSMACKTMO               : 8;  /* [15:8]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } SRMC_PMCTRL;

    /* 0x28*/
    struct {
           uint32_t PMSTAT                  : 4;  /* [3:0]          ro         */
           uint32_t RSVD_7_4                : 4;  /* [7:4]          ro         */
           uint32_t DSMABORT                : 1;  /* [8]            ro         */
           uint32_t RSVD_31_9               :23;  /* [31:9]         ro         */
    } SRMC_PMSTAT;

    /* 0x2C*/
    struct {
           uint32_t WUPSRC_EN2_0            : 3;  /* [2:0]          r/w        */
           uint32_t RSVD_3                  : 1;  /* [3]            ro         */
           uint32_t WUPSRC_EN15_4           :12;  /* [15:4]         r/w        */
           uint32_t WUPSRC_PL2_0            : 3;  /* [18:16]        r/w        */
           uint32_t RSVD_19                 : 1;  /* [19]           ro         */
           uint32_t WUPSRC_PL14_4           :11;  /* [30:20]        r/w        */
           uint32_t RSVD_31                 : 1;  /* [31]           r          */
    } SRMC_DSMWUPC1;

    /* 0x30*/
    struct {
           uint32_t WUPSRC_EN16             : 1;  /* [0]            r/w        */
           uint32_t RSVD_31_1               :31;  /* [31:1]         ro         */
    } SRMC_DSMWUPC2;

    /* 0x34*/
    struct {
           uint32_t WUPS_2_0                : 3;  /* [2:0]          w1c        */
           uint32_t RSVD_3                  : 1;  /* [3]            ro         */
           uint32_t WUPS_16_4               :13;  /* [16:4]         w1c        */
           uint32_t RSVD_31_17              :15;  /* [31:17]        ro         */
    } SRMC_DSMWUPS;

};    /*srmc_reg*/

struct srmc_reg_w {
    /* 0x00*/
    uint32_t zResverd0x00;
    /* 0x04*/
    uint32_t SRMC_PARAM;
    /* 0x08*/
    uint32_t SRMC_SRS;
    /* 0x0C*/
    uint32_t SRMC_CTRL;
    uint8_t zResverd0x010[8];   /*pad 0x010 - 017*/
	
    /* 0x18*/
    uint32_t SRMC_SSRS;
    /* 0x1C*/
    uint32_t SRMC_SRIE;
    /* 0x20*/
    uint32_t SRMC_PMPORT;
    /* 0x24*/
    uint32_t SRMC_PMCTRL;
    /* 0x28*/
    uint32_t SRMC_PMSTAT;
    /* 0x2C*/
    uint32_t SRMC_DSMWUPC1;
    /* 0x30*/
    uint32_t SRMC_DSMWUPC2;
    /* 0x34*/
    uint32_t SRMC_DSMWUPS;
};    /*srmc_reg*/

typedef volatile struct srmc_reg srmc_reg_t;
typedef volatile struct srmc_reg_w srmc_reg_w_t;

struct stim_reg {
    /* 0x00*/
    uint32_t zResverd0x00;
    /* 0x04*/
    struct {
           uint32_t CNT                     :32;  /* [31:0]         ro         */
    } STIM_CNTn[4];

    /* 0x14*/
    struct {
           uint32_t CV                      :32;  /* [31:0]         r/w        */
    } STIM_CVn[4];

    /* 0x24*/
    struct {
           uint32_t CLKS                    : 2;  /* [1:0]          r/w        */
           uint32_t PSDIV                   : 4;  /* [5:2]          r/w        */
           uint32_t PSEN                    : 1;  /* [6]            r/w        */
           uint32_t POL                     : 1;  /* [7]            r/w        */
           uint32_t PSRC                    : 2;  /* [9:8]          r/w        */
           uint32_t MODE                    : 1;  /* [10]           r/w        */
           uint32_t RSTDIS                  : 1;  /* [11]           r/w        */
           uint32_t DMAE                    : 1;  /* [12]           r/w        */
           uint32_t IE                      : 1;  /* [13]           r/w        */
           uint32_t EN                      : 1;  /* [14]           r/w        */
           uint32_t FLAG                    : 1;  /* [15]           w1c        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } STIM_SCn[4];

};    /*stim_reg*/

struct stim_reg_w {
    /* 0x00*/
    uint32_t zResverd0x00;
    /* 0x04*/
    uint32_t STIM_CNTn[4];
    /* 0x14*/
    uint32_t STIM_CVn[4];
    /* 0x24*/
    uint32_t STIM_SCn[4];
};    /*stim_reg*/

typedef volatile struct stim_reg stim_reg_t;
typedef volatile struct stim_reg_w stim_reg_w_t;

struct tdg_reg {
    /* 0x0*/
    uint32_t zResverd0x0;
    /* 0x4*/
    struct {
           uint32_t DOPNUM                  : 4;  /* [3:0]          ro         */
           uint32_t CHNUM                   : 4;  /* [7:4]          ro         */
           uint32_t RSVD_31_8               :24;  /* [31:8]         ro         */
    } TDG_PARAM;

    /* 0x8*/
    struct {
           uint32_t TDGEN                   : 1;  /* [0]            r/w        */
           uint32_t RSVD_3_1                : 3;  /* [3:1]          ro         */
           uint32_t TRIGS                   : 1;  /* [4]            r/w        */
           uint32_t CNTMD                   : 1;  /* [5]            r/w        */
           uint32_t CLRMD                   : 1;  /* [6]            r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t PRES                    : 3;  /* [10:8]         r/w        */
           uint32_t RSVD_15_11              : 5;  /* [15:11]        ro         */
           uint32_t CFGUP                   : 1;  /* [16]           r/w        */
           uint32_t SWTRG                   : 1;  /* [17]           wo         */
           uint32_t RSVD_19_18              : 2;  /* [19:18]        ro         */
           uint32_t UPMD                    : 2;  /* [21:20]        r/w        */
           uint32_t RSVD_31_22              :10;  /* [31:22]        ro         */
    } TDG_CTRL1;

    /* 0xC*/
    struct {
           uint32_t CDO0IE                  : 1;  /* [0]            r/w        */
           uint32_t CDO1IE                  : 1;  /* [1]            r/w        */
           uint32_t CDO2IE                  : 1;  /* [2]            r/w        */
           uint32_t CDO3IE                  : 1;  /* [3]            r/w        */
           uint32_t CDO4IE                  : 1;  /* [4]            r/w        */
           uint32_t CDO5IE                  : 1;  /* [5]            r/w        */
           uint32_t RSVD_7_6                : 2;  /* [7:6]          ro         */
           uint32_t ERRIE                   : 1;  /* [8]            r/w        */
           uint32_t RSVD_15_9               : 7;  /* [15:9]         ro         */
           uint32_t CH0E                    : 1;  /* [16]           r/w        */
           uint32_t CH1E                    : 1;  /* [17]           r/w        */
           uint32_t CH2E                    : 1;  /* [18]           r/w        */
           uint32_t CH3E                    : 1;  /* [19]           r/w        */
           uint32_t CH4E                    : 1;  /* [20]           r/w        */
           uint32_t CH5E                    : 1;  /* [21]           r/w        */
           uint32_t RSVD_31_22              :10;  /* [31:22]        ro         */
    } TDG_CTRL2;

    /* 0x10*/
    struct {
           uint32_t CDO0IF                  : 1;  /* [0]            w1c        */
           uint32_t CDO1IF                  : 1;  /* [1]            w1c        */
           uint32_t CDO2IF                  : 1;  /* [2]            w1c        */
           uint32_t CDO3IF                  : 1;  /* [3]            w1c        */
           uint32_t CDO4IF                  : 1;  /* [4]            w1c        */
           uint32_t CDO5IF                  : 1;  /* [5]            w1c        */
           uint32_t RSVD_7_6                : 2;  /* [7:6]          ro         */
           uint32_t ERRIF                   : 1;  /* [8]            w1c        */
           uint32_t RSVD_31_9               :23;  /* [31:9]         ro         */
    } TDG_STAT;

    /* 0x14*/
    struct {
           uint32_t MOD                     :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } TDG_MOD;

    /* 0x18*/
    struct {
           uint32_t CNT                     :16;  /* [15:0]         ro         */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } TDG_CNT;

    struct {
    /* 0x1C*/
    struct {
           uint32_t RSVD_7_0                : 8;  /* [7:0]                     */
           uint32_t DO0E                    : 1;  /* [8]            r/w        */
           uint32_t DO1E                    : 1;  /* [9]            r/w        */
           uint32_t DO2E                    : 1;  /* [10]           r/w        */
           uint32_t DO3E                    : 1;  /* [11]           r/w        */
           uint32_t DO4E                    : 1;  /* [12]           r/w        */
           uint32_t DO5E                    : 1;  /* [13]           r/w        */
           uint32_t DO6E                    : 1;  /* [14]           r/w        */
           uint32_t DO7E                    : 1;  /* [15]           r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } TDG_CHCTRL;

    /* 0x20 - 0x3F */
    struct {
           uint32_t DO0OFS                  :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } TDG_CHDOOFS[8];

    /* 0x40*/
    struct {
           uint32_t CDOINTDLY               :10;  /* [9:0]          r/w        */
           uint32_t RSVD_15_10              : 6;  /* [15:10]        ro         */
           uint32_t LDCO                    : 1;  /* [16]           ro         */
           uint32_t RSVD_31_17              :15;  /* [31:17]        ro         */
    } TDG_CHCDOINTDLY;
    }TDG_CHCFG[6];
};    /*tdg_reg*/

struct tdg_reg_w {
    /* 0x0*/
    uint32_t zResverd0x0;
    /* 0x4*/
    uint32_t TDG_PARAM;
    /* 0x8*/
    uint32_t TDG_CTRL1;
    /* 0xC*/
    uint32_t TDG_CTRL2;
    /* 0x10*/
    uint32_t TDG_STAT;
    /* 0x14*/
    uint32_t TDG_MOD;
    /* 0x18*/
    uint32_t TDG_CNT;
    
    struct {
    /* 0x1C*/
    uint32_t TDG_CHCTRL;
    /* 0x20 -0x3F */
    uint32_t TDG_CHDOOFS[8];    
    /* 0x40*/
    uint32_t TDG_CHCDOINTDLY;
    }TDG_CHCFG[6];
};    /*tdg_reg*/

typedef volatile struct tdg_reg tdg_reg_t;
typedef volatile struct tdg_reg_w tdg_reg_w_t;

struct tim_reg {
    /* 0x00*/
    struct {
           uint32_t CKSRC                   : 2;  /* [1:0]          r/w        */
           uint32_t PSDIV                   : 3;  /* [4:2]          r/w        */
           uint32_t DBGM                    : 2;  /* [6:5]          r/w        */
           uint32_t RSVD_31_7               :25;  /* [31:7]         ro         */
    } TIM_TIMEBASE;

    /* 0x04*/
    struct {
           uint32_t CNT                     :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } TIM_CNT;

    /* 0x08*/
    struct {
           uint32_t CNTINIT                 :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } TIM_CNTINIT;

    /* 0x0C*/
    struct {
           uint32_t MOD                     :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } TIM_MOD;

    /* 0x10*/
    struct {
           uint32_t CHOE0                   : 1;  /* [0]            r/w        */
           uint32_t CHOE1                   : 1;  /* [1]            r/w        */
           uint32_t CHOE2                   : 1;  /* [2]            r/w        */
           uint32_t CHOE3                   : 1;  /* [3]            r/w        */
           uint32_t CHOE4                   : 1;  /* [4]            r/w        */
           uint32_t CHOE5                   : 1;  /* [5]            r/w        */
           uint32_t CHOE6                   : 1;  /* [6]            r/w        */
           uint32_t CHOE7                   : 1;  /* [7]            r/w        */
           uint32_t RLDIE                   : 1;  /* [8]            r/w        */
           uint32_t TOIE                    : 1;  /* [9]            r/w        */
           uint32_t CNTMODE                 : 1;  /* [10]           r/w        */
           uint32_t INIT                    : 1;  /* [11]           wo         */
           uint32_t RSVD_31_12              :20;  /* [31:12]        ro         */
    } TIM_GLBCR;

    /* 0x14*/
    struct {
           uint32_t CH0F                    : 1;  /* [0]            ro         */
           uint32_t CH1F                    : 1;  /* [1]            ro         */
           uint32_t CH2F                    : 1;  /* [2]            ro         */
           uint32_t CH3F                    : 1;  /* [3]            ro         */
           uint32_t CH4F                    : 1;  /* [4]            ro         */
           uint32_t CH5F                    : 1;  /* [5]            ro         */
           uint32_t CH6F                    : 1;  /* [6]            ro         */
           uint32_t CH7F                    : 1;  /* [7]            ro         */
           uint32_t RLDF                    : 1;  /* [8]            ro         */
           uint32_t TOF                     : 1;  /* [9]            ro         */
           uint32_t WPDIS                   : 1;  /* [10]           r/w        */
           uint32_t RSVD_31_11              :21;  /* [31:11]        ro         */
    } TIM_GLBSR;

    /* 0x18*/
    struct {
           uint32_t ELS                     : 2;  /* [1:0]          r/w        */
           uint32_t CMS                     : 2;  /* [3:2]          r/w        */
           uint32_t CHIE                    : 1;  /* [4]            r/w        */
           uint32_t CHF                     : 1;  /* [5]            ro         */
           uint32_t DMA                     : 1;  /* [6]            r/w        */
           uint32_t ICRST                   : 1;  /* [7]            r/w        */
           uint32_t RSVD_31_8               :24;  /* [31:8]         ro         */
    } TIM_CMCn[8];

    /* 0x38*/
    struct {
           uint32_t CCV                     :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } TIM_CCVn[8];

    /* 0x58*/
    struct {
           uint32_t INIT0                   : 1;  /* [0]            r/w        */
           uint32_t INIT1                   : 1;  /* [1]            r/w        */
           uint32_t INIT2                   : 1;  /* [2]            r/w        */
           uint32_t INIT3                   : 1;  /* [3]            r/w        */
           uint32_t INIT4                   : 1;  /* [4]            r/w        */
           uint32_t INIT5                   : 1;  /* [5]            r/w        */
           uint32_t INIT6                   : 1;  /* [6]            r/w        */
           uint32_t INIT7                   : 1;  /* [7]            r/w        */
           uint32_t POL0                    : 1;  /* [8]            r/w        */
           uint32_t POL1                    : 1;  /* [9]            r/w        */
           uint32_t POL2                    : 1;  /* [10]           r/w        */
           uint32_t POL3                    : 1;  /* [11]           r/w        */
           uint32_t POL4                    : 1;  /* [12]           r/w        */
           uint32_t POL5                    : 1;  /* [13]           r/w        */
           uint32_t POL6                    : 1;  /* [14]           r/w        */
           uint32_t POL7                    : 1;  /* [15]           r/w        */
           uint32_t TRIGE0                  : 1;  /* [16]           r/w        */
           uint32_t TRIGE1                  : 1;  /* [17]           r/w        */
           uint32_t TRIGE2                  : 1;  /* [18]           r/w        */
           uint32_t TRIGE3                  : 1;  /* [19]           r/w        */
           uint32_t TRIGE4                  : 1;  /* [20]           r/w        */
           uint32_t TRIGE5                  : 1;  /* [21]           r/w        */
           uint32_t TRIGE6                  : 1;  /* [22]           r/w        */
           uint32_t TRIGE7                  : 1;  /* [23]           r/w        */
           uint32_t INITRIGE                : 1;  /* [24]           r/w        */
           uint32_t TRIGF                   : 1;  /* [25]           ro         */
           uint32_t RSVD_31_26              : 6;  /* [31:26]        ro         */
    } TIM_OUTCR;

    /* 0x5C*/
    struct {
           uint32_t CH0OC                   : 1;  /* [0]            r/w        */
           uint32_t CH1OC                   : 1;  /* [1]            r/w        */
           uint32_t CH2OC                   : 1;  /* [2]            r/w        */
           uint32_t CH3OC                   : 1;  /* [3]            r/w        */
           uint32_t CH4OC                   : 1;  /* [4]            r/w        */
           uint32_t CH5OC                   : 1;  /* [5]            r/w        */
           uint32_t CH6OC                   : 1;  /* [6]            r/w        */
           uint32_t CH7OC                   : 1;  /* [7]            r/w        */
           uint32_t CH0OCV                  : 1;  /* [8]            r/w        */
           uint32_t CH1OCV                  : 1;  /* [9]            r/w        */
           uint32_t CH2OCV                  : 1;  /* [10]           r/w        */
           uint32_t CH3OCV                  : 1;  /* [11]           r/w        */
           uint32_t CH4OCV                  : 1;  /* [12]           r/w        */
           uint32_t CH5OCV                  : 1;  /* [13]           r/w        */
           uint32_t CH6OCV                  : 1;  /* [14]           r/w        */
           uint32_t CH7OCV                  : 1;  /* [15]           r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } TIM_OUTSWCR;

    /* 0x60*/
    struct {
           uint32_t FCTLEN0                 : 1;  /* [0]            r/w        */
           uint32_t DTEN0                   : 1;  /* [1]            r/w        */
           uint32_t COMB0                   : 1;  /* [2]            r/w        */
           uint32_t SYNCEN0                 : 1;  /* [3]            r/w        */
           uint32_t DECAPEN0                : 1;  /* [4]            r/w        */
           uint32_t DECAP0                  : 1;  /* [5]            r/w        */
           uint32_t RSVD_7_6                : 2;  /* [7:6]          ro         */
           uint32_t FCTLEN1                 : 1;  /* [8]            r/w        */
           uint32_t DTEN1                   : 1;  /* [9]            r/w        */
           uint32_t COMB1                   : 1;  /* [10]           r/w        */
           uint32_t SYNCEN1                 : 1;  /* [11]           r/w        */
           uint32_t DECAPEN1                : 1;  /* [12]           r/w        */
           uint32_t DECAP1                  : 1;  /* [13]           r/w        */
           uint32_t RSVD_15_14              : 2;  /* [15:14]        ro         */
           uint32_t FCTLEN2                 : 1;  /* [16]           r/w        */
           uint32_t DTEN2                   : 1;  /* [17]           r/w        */
           uint32_t COMB2                   : 1;  /* [18]           r/w        */
           uint32_t SYNCEN2                 : 1;  /* [19]           r/w        */
           uint32_t DECAPEN2                : 1;  /* [20]           r/w        */
           uint32_t DECAP2                  : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t FCTLEN3                 : 1;  /* [24]           r/w        */
           uint32_t DTEN3                   : 1;  /* [25]           r/w        */
           uint32_t COMB3                   : 1;  /* [26]           r/w        */
           uint32_t SYNCEN3                 : 1;  /* [27]           r/w        */
           uint32_t DECAPEN3                : 1;  /* [28]           r/w        */
           uint32_t DECAP3                  : 1;  /* [29]           r/w        */
           uint32_t RSVD_31_30              : 2;  /* [31:30]        ro         */
    } TIM_PCR;

    /* 0x64*/
    struct {
           uint32_t FILVAL0                 : 4;  /* [3:0]          r/w        */
           uint32_t FILVAL1                 : 4;  /* [7:4]          r/w        */
           uint32_t FILVAL2                 : 4;  /* [11:8]         r/w        */
           uint32_t FILVAL3                 : 4;  /* [15:12]        r/w        */
           uint32_t DTPS                    : 2;  /* [17:16]        r/w        */
           uint32_t DTVAL                   : 6;  /* [23:18]        r/w        */
           uint32_t RSVD_31_24              : 8;  /* [31:24]        ro         */
    } TIM_FILTER;

    /* 0x68*/
    struct {
           uint32_t FAULTEN0                : 1;  /* [0]            r/w        */
           uint32_t FIFEN0                  : 1;  /* [1]            r/w        */
           uint32_t FLTPOL0                 : 1;  /* [2]            r/w        */
           uint32_t FAULTEN1                : 1;  /* [3]            r/w        */
           uint32_t FIFEN1                  : 1;  /* [4]            r/w        */
           uint32_t FLTPOL1                 : 1;  /* [5]            r/w        */
           uint32_t FLTIE                   : 1;  /* [6]            r/w        */
           uint32_t FLTCEN                  : 1;  /* [7]            r/w        */
           uint32_t FLTCM                   : 1;  /* [8]            r/w        */
           uint32_t RSVD_10_9               : 2;  /* [10:9]         ro         */
           uint32_t FIFVAL                  : 4;  /* [14:11]        r/w        */
           uint32_t FSTATE                  : 1;  /* [15]           r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } TIM_FLTCR;

    /* 0x6C*/
    struct {
           uint32_t FAULTF0                 : 1;  /* [0]            ro         */
           uint32_t FAULTF1                 : 1;  /* [1]            ro         */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t FAULTF                  : 1;  /* [4]            ro         */
           uint32_t FAULTIN                 : 1;  /* [5]            ro         */
           uint32_t WPEN                    : 1;  /* [6]            r/w        */
           uint32_t RSVD_31_7               :25;  /* [31:7]         ro         */
    } TIM_FLTSR;

    /* 0x70*/
    struct {
           uint32_t SWTRIG                  : 1;  /* [0]            r/w        */
           uint32_t RSVD_7_1                : 7;  /* [7:1]          ro         */
           uint32_t SYNCINIT                : 1;  /* [8]            r/w        */
           uint32_t SYNCOSWC                : 1;  /* [9]            r/w        */
           uint32_t RSVD_17_10              : 8;  /* [17:10]        ro         */
           uint32_t SWWRBUF                 : 1;  /* [18]           r/w        */
           uint32_t SWRSTCNT                : 1;  /* [19]           r/w        */
           uint32_t RSVD_31_20              :12;  /* [31:20]        ro         */
    } TIM_SYNC;

    /* 0x74*/
    struct {
           uint32_t CH0SEL                  : 1;  /* [0]            r/w        */
           uint32_t CH1SEL                  : 1;  /* [1]            r/w        */
           uint32_t CH2SEL                  : 1;  /* [2]            r/w        */
           uint32_t CH3SEL                  : 1;  /* [3]            r/w        */
           uint32_t CH4SEL                  : 1;  /* [4]            r/w        */
           uint32_t CH5SEL                  : 1;  /* [5]            r/w        */
           uint32_t CH6SEL                  : 1;  /* [6]            r/w        */
           uint32_t CH7SEL                  : 1;  /* [7]            r/w        */
           uint32_t LOADEN                  : 1;  /* [8]            r/w        */
           uint32_t RSVD_10_9               : 2;  /* [10:9]         ro         */
           uint32_t HCSEL                   : 1;  /* [11]           r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t LDFREQ                  : 5;  /* [20:16]        r/w        */
           uint32_t RSVD_31_21              :11;  /* [31:21]        ro         */
    } TIM_RELOAD;

    /* 0x78*/
    struct {
           uint32_t HCV                     :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } TIM_HCV;

};    /*tim_reg*/

struct tim_reg_w {
    /* 0x00*/
    uint32_t TIM_TIMEBASE;
    /* 0x04*/
    uint32_t TIM_CNT;
    /* 0x08*/
    uint32_t TIM_CNTINIT;
    /* 0x0C*/
    uint32_t TIM_MOD;
    /* 0x10*/
    uint32_t TIM_GLBCR;
    /* 0x14*/
    uint32_t TIM_GLBSR;
    /* 0x18*/
    uint32_t TIM_CMCn[8];
    /* 0x38*/
    uint32_t TIM_CCVn[8];
    /* 0x58*/
    uint32_t TIM_OUTCR;
    /* 0x5C*/
    uint32_t TIM_OUTSWCR;
    /* 0x60*/
    uint32_t TIM_PCR;
    /* 0x64*/
    uint32_t TIM_FILTER;
    /* 0x68*/
    uint32_t TIM_FLTCR;
    /* 0x6C*/
    uint32_t TIM_FLTSR;
    /* 0x70*/
    uint32_t TIM_SYNC;
    /* 0x74*/
    uint32_t TIM_RELOAD;
    /* 0x78*/
    uint32_t TIM_HCV;
};    /*tim_reg*/

typedef volatile struct tim_reg tim_reg_t;
typedef volatile struct tim_reg_w tim_reg_w_t;

struct tmu_reg {
    /* 0x0*/
    struct {
           uint32_t SEL                     :16;  /* [15:0]         r/w        */
           uint32_t EN                      : 1;  /* [16]           r/w        */
           uint32_t RSVD_30_17              :14;  /* [30:17]        ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } TMU_CFGn[40];

};    /*tmu_reg*/

struct tmu_reg_w {
    /* 0x0*/
    uint32_t TMU_CFGn[40];
};    /*tmu_reg*/

typedef volatile struct tmu_reg tmu_reg_t;
typedef volatile struct tmu_reg_w tmu_reg_w_t;

struct trng_reg {
    /* 0x0000*/
    uint32_t zResverd0x0000;
    /* 0x0004*/
    uint32_t zResverd0x0004;
    /* 0x0008*/
    struct {
           uint32_t RD                      : 1;  /* [0]            ro         */
           uint32_t IN                      : 1;  /* [1]            ro         */
           uint32_t TA                      : 1;  /* [2]            ro         */
           uint32_t CA                      : 1;  /* [3]            ro         */
           uint32_t RSVD_31_4               :28;  /* [31:4]         ro         */
    } TRNG_STATUS;

    /* 0x000c*/
    struct {
           uint32_t EN                      : 1;  /* [0]            r/w        */
           uint32_t SM                      : 1;  /* [1]            r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32_t DEC                     :10;  /* [13:4]         r/w        */
           uint32_t LP                      : 5;  /* [18:14]        r/w        */
           uint32_t RSVD_31_19              :13;  /* [31:19]        ro         */
    } TRNG_CONFIG;

    /* 0x0010*/
    struct {
           uint32_t GE                      : 1;  /* [0]            wo         */
           uint32_t IN                      : 1;  /* [1]            wo         */
           uint32_t HT                      : 1;  /* [2]            wo         */
           uint32_t UN                      : 1;  /* [3]            wo         */
           uint32_t RS                      : 1;  /* [4]            wo         */
           uint32_t AK                      : 1;  /* [5]            wo         */
           uint32_t RSVD_31_6               :26;  /* [31:6]         ro         */
    } TRNG_CTR_DRBG_CONTROL;

    /* 0x0014*/
    struct {
           uint32_t RS                      :12;  /* [11:0]         r/w        */
           uint32_t RP                      :20;  /* [31:12]        r/w        */
    } TRNG_CTR_DRBG_REQUEST_SIZE;

    /* 0x0018*/
    struct {
           uint32_t RP                      :32;  /* [31:0]         r/w        */
    } TRNG_CTR_DRBG_CONFIG_1;

    /* 0x001c*/
    struct {
           uint32_t HTP                     :32;  /* [31:0]         r/w        */
    } TRNG_CTR_DRBG_CONFIG_2;

    /* 0x0020*/
    struct {
           uint32_t AL0                     : 1;  /* [0]            ro         */
           uint32_t AL1                     : 1;  /* [1]            ro         */
           uint32_t AL2                     : 1;  /* [2]            ro         */
           uint32_t AL3                     : 1;  /* [3]            ro         */
           uint32_t VA                      : 1;  /* [4]            ro         */
           uint32_t RSVD_31_5               :27;  /* [31:5]         ro         */
    } TRNG_ALARM;

    /* 0x0024*/
    struct {
           uint32_t AL0                     : 1;  /* [0]            ro         */
           uint32_t AL1                     : 1;  /* [1]            ro         */
           uint32_t AL2                     : 1;  /* [2]            ro         */
           uint32_t VA                      : 1;  /* [3]            ro         */
           uint32_t RSVD_31_4               :28;  /* [31:4]         ro         */
    } TRNG_CTR_DRBG_ALARM;

    /* 0x0028*/
    struct {
           uint32_t FL                      : 1;  /* [0]            wo         */
           uint32_t RSVD_31_1               :31;  /* [31:1]         ro         */
    } TRNG_RAW_RANDOM_CONTROL;

    /* 0x002c*/
    struct {
           uint32_t DATA                    :16;  /* [15:0]         ro         */
           uint32_t VA                      : 1;  /* [16]           ro         */
           uint32_t RSVD_31_17              :15;  /* [31:17]        ro         */
    } TRNG_RAW_RANDOM_DATA;

    /* 0x0030*/
    struct {
           uint32_t DATA                    :16;  /* [15:0]         ro         */
           uint32_t VA                      : 1;  /* [16]           ro         */
           uint32_t RSVD_31_17              :15;  /* [31:17]        ro         */
    } TRNG_CTR_DRBG_RANDOM_DATA;

    /* 0x0034*/
    struct {
           uint32_t I0                      : 1;  /* [0]            r/w        */
           uint32_t I1                      : 1;  /* [1]            r/w        */
           uint32_t I2                      : 1;  /* [2]            r/w        */
           uint32_t I3                      : 1;  /* [3]            r/w        */
           uint32_t MC                      : 1;  /* [4]            r/w        */
           uint32_t RE                      : 1;  /* [5]            r/w        */
           uint32_t E0                      : 1;  /* [6]            r/w        */
           uint32_t E1                      : 1;  /* [7]            r/w        */
           uint32_t E2                      : 1;  /* [8]            r/w        */
           uint32_t E3                      : 1;  /* [9]            r/w        */
           uint32_t SE                      : 1;  /* [10]           r/w        */
           uint32_t RSVD_31_11              :21;  /* [31:11]        ro         */
    } TRNG_ADDITIONAL_CONFIG_0;

    /* 0x0038*/
    struct {
           uint32_t AC1                     :11;  /* [10:0]         r/w        */
           uint32_t RSVD_31_11              :21;  /* [31:11]        ro         */
    } TRNG_ADDITIONAL_CONFIG_1;

    /* 0x003c*/
    struct {
           uint32_t AC2                     :32;  /* [31:0]         r/w        */
    } TRNG_ADDITIONAL_CONFIG_2;

    /* 0x0040*/
    struct {
           uint32_t NS                      : 1;  /* [0]            wo         */
           uint32_t RSVD_31_1               :31;  /* [31:1]         ro         */
    } TRNG_ADDITIONAL_MEAS_CONTROL;

    /* 0x0044*/
    struct {
           uint32_t TIME                    :30;  /* [29:0]         r/w        */
           uint32_t SEL                     : 2;  /* [31:30]        r/w        */
    } TRNG_ADDITIONAL_MEAS_CONFIG;

    /* 0x0048*/
    struct {
           uint32_t RD                      : 1;  /* [0]            ro         */
           uint32_t OV                      : 1;  /* [1]            ro         */
           uint32_t RSVD_31_2               :30;  /* [31:2]         ro         */
    } TRNG_ADDITIONAL_MEAS_STATUS;

    /* 0x004c*/
    struct {
           uint32_t D0                      :32;  /* [31:0]         ro         */
    } TRNG_ADDITIONAL_MEAS_DATA_0;

    /* 0x0050*/
    struct {
           uint32_t D1                      :32;  /* [31:0]         ro         */
    } TRNG_ADDITIONAL_MEAS_DATA_1;

    /* 0x0054*/
    struct {
           uint32_t IS0                     : 1;  /* [0]            ro         */
           uint32_t IS1                     : 1;  /* [1]            ro         */
           uint32_t IS2                     : 1;  /* [2]            ro         */
           uint32_t IS3                     : 1;  /* [3]            ro         */
           uint32_t RSVD_31_4               :28;  /* [31:4]         ro         */
    } TRNG_IRQ_STATUS;

    /* 0x0058*/
    struct {
           uint32_t CL0                     : 1;  /* [0]            wo         */
           uint32_t CL1                     : 1;  /* [1]            wo         */
           uint32_t CL2                     : 1;  /* [2]            wo         */
           uint32_t CL3                     : 1;  /* [3]            wo         */
           uint32_t RSVD_31_4               :28;  /* [31:4]         ro         */
    } TRNG_IRQ_CLEAR;

    /* 0x005c*/
    struct {
           uint32_t E0                      : 1;  /* [0]            r/w        */
           uint32_t E1                      : 1;  /* [1]            r/w        */
           uint32_t E2                      : 1;  /* [2]            r/w        */
           uint32_t E3                      : 1;  /* [3]            r/w        */
           uint32_t RSVD_31_4               :28;  /* [31:4]         ro         */
    } TRNG_IRQ_CONFIG;

    /* 0x0060*/
    struct {
           uint32_t TIMEOUT                 :32;  /* [31:0]         r/w        */
    } TRNG_ERROR_CONFIG;

    /* 0x0064*/
    struct {
           uint32_t ST                      : 1;  /* [0]            wo         */
           uint32_t RSVD_31_1               :31;  /* [31:1]         ro         */
    } TRNG_ERROR_CONTROL;

    /* 0x0068*/
    struct {
           uint32_t RD                      : 1;  /* [0]            ro         */
           uint32_t OV                      : 1;  /* [1]            ro         */
           uint32_t TR                      : 1;  /* [2]            ro         */
           uint32_t RSVD_31_3               :29;  /* [31:3]         ro         */
    } TRNG_ERROR_STATUS;

    /* 0x006c*/
    struct {
           uint32_t MO                      : 1;  /* [0]            r/w        */
           uint32_t RSVD_31_1               :31;  /* [31:1]         ro         */
    } TRNG_STATS_CONFIG;

    /* 0x0070*/
    struct {
           uint32_t CL                      : 1;  /* [0]            wo         */
           uint32_t RSVD_31_1               :31;  /* [31:1]         ro         */
    } TRNG_STATS_CONTROL;

    /* 0x0074*/
    struct {
           uint32_t EV                      :16;  /* [15:0]         ro         */
           uint32_t PA                      :16;  /* [31:16]        ro         */
    } TRNG_STATS_DATA;

};    /*trng_reg*/

struct trng_reg_w {
    /* 0x0000*/
    uint32_t zResverd0x0000;
    /* 0x0004*/
    uint32_t zResverd0x0004;
    /* 0x0008*/
    uint32_t TRNG_STATUS;
    /* 0x000c*/
    uint32_t TRNG_CONFIG;
    /* 0x0010*/
    uint32_t TRNG_CTR_DRBG_CONTROL;
    /* 0x0014*/
    uint32_t TRNG_CTR_DRBG_REQUEST_SIZE;
    /* 0x0018*/
    uint32_t TRNG_CTR_DRBG_CONFIG_1;
    /* 0x001c*/
    uint32_t TRNG_CTR_DRBG_CONFIG_2;
    /* 0x0020*/
    uint32_t TRNG_ALARM;
    /* 0x0024*/
    uint32_t TRNG_CTR_DRBG_ALARM;
    /* 0x0028*/
    uint32_t TRNG_RAW_RANDOM_CONTROL;
    /* 0x002c*/
    uint32_t TRNG_RAW_RANDOM_DATA;
    /* 0x0030*/
    uint32_t TRNG_CTR_DRBG_RANDOM_DATA;
    /* 0x0034*/
    uint32_t TRNG_ADDITIONAL_CONFIG_0;
    /* 0x0038*/
    uint32_t TRNG_ADDITIONAL_CONFIG_1;
    /* 0x003c*/
    uint32_t TRNG_ADDITIONAL_CONFIG_2;
    /* 0x0040*/
    uint32_t TRNG_ADDITIONAL_MEAS_CONTROL;
    /* 0x0044*/
    uint32_t TRNG_ADDITIONAL_MEAS_CONFIG;
    /* 0x0048*/
    uint32_t TRNG_ADDITIONAL_MEAS_STATUS;
    /* 0x004c*/
    uint32_t TRNG_ADDITIONAL_MEAS_DATA_0;
    /* 0x0050*/
    uint32_t TRNG_ADDITIONAL_MEAS_DATA_1;
    /* 0x0054*/
    uint32_t TRNG_IRQ_STATUS;
    /* 0x0058*/
    uint32_t TRNG_IRQ_CLEAR;
    /* 0x005c*/
    uint32_t TRNG_IRQ_CONFIG;
    /* 0x0060*/
    uint32_t TRNG_ERROR_CONFIG;
    /* 0x0064*/
    uint32_t TRNG_ERROR_CONTROL;
    /* 0x0068*/
    uint32_t TRNG_ERROR_STATUS;
    /* 0x006c*/
    uint32_t TRNG_STATS_CONFIG;
    /* 0x0070*/
    uint32_t TRNG_STATS_CONTROL;
    /* 0x0074*/
    uint32_t TRNG_STATS_DATA;
};    /*trng_reg*/

typedef volatile struct trng_reg trng_reg_t;
typedef volatile struct trng_reg_w trng_reg_w_t;

struct uart_reg {
    /* 0x0*/
    union {
        struct {
           uint32_t RBR_LSB                 : 8;  /* [7:0]          ro         */
           uint32_t RBR_MSB                 : 1;  /* [8]            ro         */
           uint32_t RSVD_31_9               :23;  /* [31:9]                    */
        } UART_RBR;
        struct {
           uint32_t THR_LSB                 : 8;  /* [7:0]          wo         */
           uint32_t THR_MSB                 : 1;  /* [8]            wo         */
           uint32_t RSVD_31_9               :23;  /* [31:9]                    */
        } UART_THR;
        struct {
           uint32_t DL_L                    : 8;  /* [7:0]          r/w        */
           uint32_t RSVD_31_8               :24;  /* [31:8]         ro         */
        } UART_DLL;
    } UART_RBR_THR_DLL;

    /* 0x4*/
    union {
        struct {
           uint32_t DL_H                    : 8;  /* [7:0]          r/w        */
           uint32_t RSVD_31_8               :24;  /* [31:8]         ro         */
        } UART_DLH;
        struct {
           uint32_t ERBFI                   : 1;  /* [0]            r/w        */
           uint32_t ETBEI                   : 1;  /* [1]            r/w        */
           uint32_t ELSI                    : 1;  /* [2]            r/w        */
           uint32_t EDSSI                   : 1;  /* [3]            r/w        */
           uint32_t RSVD_6_4                : 3;  /* [6:4]          ro         */
           uint32_t PTIME                   : 1;  /* [7]            r/w        */
           uint32_t HEADER_DONE_INT_EN      : 1;  /* [8]            r/w        */
           uint32_t RSP_DONE_INT_EN         : 1;  /* [9]            r/w        */
           uint32_t ASYNC_INT_EN            : 1;  /* [10]           r/w        */
           uint32_t RSVD_31_11              :21;  /* [31:11]        ro         */
        } UART_IER;
    } UART_DLH_IER;

    /* 0x8*/
    union {
        struct {
           uint32_t IID                     : 4;  /* [3:0]          ro         */
           uint32_t RSVD_5_4                : 2;  /* [5:4]          ro         */
           uint32_t FIFOSE                  : 2;  /* [7:6]          ro         */
           uint32_t RSVD_31_8               :24;  /* [31:8]         ro         */
        } UART_IIR;
        struct {
           uint32_t FIFOE                   : 1;  /* [0]            wo         */
           uint32_t RFIFOR                  : 1;  /* [1]            wo         */
           uint32_t XFIFOR                  : 1;  /* [2]            wo         */
           uint32_t RSVD_3                  : 1;  /* [3]            ro         */
           uint32_t TET                     : 2;  /* [5:4]          wo         */
           uint32_t RCVR                    : 2;  /* [7:6]          wo         */
           uint32_t RSVD_31_8               :24;  /* [31:8]         ro         */
        } UART_FCR;
    } UART_IIR_FCR;

    /* 0xC*/
    struct {
           uint32_t DLS                     : 2;  /* [1:0]          r/w        */
           uint32_t STOP                    : 1;  /* [2]            r/w        */
           uint32_t PEN                     : 1;  /* [3 ]           r/w        */
           uint32_t EPS                     : 1;  /* [4]            r/w        */
           uint32_t RSVD_5                  : 1;  /* [5 ]           ro         */
           uint32_t BC                      : 1;  /* [6]            r/w        */
           uint32_t DLAB                    : 1;  /* [7]            r/w        */
           uint32_t LBKEN                   : 1;  /* [8]            r/w        */
           uint32_t LBKM                    : 5;  /* [13:9]         r/w        */
           uint32_t IDLE_DET_LENGTH         : 3;  /* [16:14]        r/w        */
           uint32_t IDLE_DET_EN             : 1;  /* [17]           r/w        */
           uint32_t AUTO_SYNC_EN            : 1;  /* [18]           r/w        */
           uint32_t DEBUG_EN                : 1;  /* [19]           r/w        */
           uint32_t RSVD_31_20              :12;  /* [31:20]        ro         */
    } UART_LCR;

    /* 0x10*/
    struct {
           uint32_t RSVD_0                  : 1;  /* [0]            ro         */
           uint32_t RTS                     : 1;  /* [1]            r/w        */
           uint32_t RSVD_2                  : 1;  /* [2]            ro         */
           uint32_t RSVD_3                  : 1;  /* [3 ]           ro          */
           uint32_t LB                      : 1;  /* [4]            r/w        */
           uint32_t AFCE                    : 1;  /* [5 ]           r/w        */
           uint32_t RSVD_6                  : 1;  /* [6]            ro         */
           uint32_t RSVD_31_7               :25;  /* [31:7]         ro         */
    } UART_AFCR;

    /* 0x14*/
    struct {
           uint32_t DR                      : 1;  /* [0]            ro         */
           uint32_t OE                      : 1;  /* [1]            ro         */
           uint32_t PE                      : 1;  /* [2]            ro         */
           uint32_t FE                      : 1;  /* [3 ]           ro         */
           uint32_t BI                      : 1;  /* [4]            ro         */
           uint32_t THRE                    : 1;  /* [5 ]           ro         */
           uint32_t TEMT                    : 1;  /* [6]            ro         */
           uint32_t RFE                     : 1;  /* [7]            ro         */
           uint32_t ADDR_RCVD               : 1;  /* [8]            ro         */
           uint32_t ASYNC_INT               : 1;  /* [9]            ro         */
           uint32_t SYNC_FIELD_ERROR        : 1;  /* [10]           ro         */
           uint32_t PID_ERR                 : 1;  /* [11]           ro         */
           uint32_t CHECKSUM_ERROR          : 1;  /* [12]           ro         */
           uint32_t TO_ERROR                : 1;  /* [13]           ro         */
           uint32_t HEADER_OP_DONE          : 1;  /* [14]           ro         */
           uint32_t RSP_OP_DONE             : 1;  /* [15]           ro         */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } UART_LSR;

    /* 0x18 */
    struct {
           uint32_t RSVD_3_0                : 4;  /* [3:0]          ro         */
           uint32_t CTS                     : 1;  /* [4]                       */
           uint32_t RSVD_31_5               :27;  /* [31:5]         ro         */
    }UART_MSR;
    
    uint8_t zResverd0x01C[96];   /*pad 0x01c - 07B*/

    /* 0x7C*/
    struct {
           uint32_t BUSY                    : 1;  /* [0]            ro         */
           uint32_t RSVD_31_1               :31;  /* [31:1]         ro         */
    } UART_USR;

    uint8_t zResverd0x080[64];   /*pad 0x080 - 0BF*/

    /* 0xC0*/
    struct {
           uint32_t FD                      : 4;  /* [3:0]          r/w        */
           uint32_t RSVD_31_4               :28;  /* [31:4]         ro         */
    } UART_FD;

    /* 0xC4*/
    struct {
           uint32_t RAR                     : 8;  /* [7:0]          r/w        */
           uint32_t RSVD_31_8               :24;  /* [31:8]         ro         */
    } UART_RAR;

    /* 0xC8*/
    struct {
           uint32_t TAR                     : 8;  /* [7:0]          r/w        */
           uint32_t RSVD_31_8               :24;  /* [31:8]         ro         */
    } UART_TAR;

    /* 0xCC*/
    struct {
           uint32_t DLS_E                   : 1;  /* [0]            r/w        */
           uint32_t ADDR_MATCH              : 1;  /* [1]            r/w        */
           uint32_t SEND_ADDR               : 1;  /* [2]            r/w        */
           uint32_t TRANSMIST_MODE          : 1;  /* [3]            r/w        */
           uint32_t RSVD_31_4               :28;  /* [31:4]         ro         */
    } UART_LCR_EXT;

    uint8_t zResverd0x0D0[48];   /*pad 0x0D0 - 0FF*/

    /* 0x100*/
    struct {
           uint32_t LIN_MODE                : 1;  /* [0]            r/w        */
           uint32_t MASTER_MODE             : 1;  /* [1]            r/w        */
           uint32_t HEADER_OP_START         : 1;  /* [2]            r/w        */
           uint32_t RSP_OP_START            : 1;  /* [3 ]           r/w        */
           uint32_t RSP_DIR                 : 1;  /* [4]            r/w        */
           uint32_t RSVD_31_5               :27;  /* [31:5]         ro         */
    } UART_LIN_CTL;

    /* 0x104*/
    struct {
           uint32_t RSP_LENGTH              : 4;  /* [3:0]          r/w        */
           uint32_t RSVD_31_4               :28;  /* [31:4]         ro         */
    } UART_LIN_RSP_LENGTH;

    /* 0x108*/
    struct {
           uint32_t ID                     : 6;  /* [5:0]          r/w        */
           uint32_t RSVD_31_6               :26;  /* [31:6]         ro         */
    } UART_LIN_ID_VALUE;

    /* 0x10C*/
    struct {
           uint32_t CHECKSUM_TYPE           : 1;  /* [0]            r/w        */
           uint32_t RSVD_7_1                : 7;  /* [7:1]          ro         */
           uint32_t RSVD_31_8               :24;  /* [31:8]         ro         */
    } UART_LIN_CHECKSUM;

    /* 0x110*/
    struct {
           uint32_t LIN_DEL_LENGTH          : 3;  /* [2:0]          r/w        */
           uint32_t RSVD_31_3               :29;  /* [31:3]         ro         */
    } UART_LIN_DEL_LENGTH;

     /* 0x114*/
    struct {
           uint32_t FID0                    : 6;  /* [5:0]          r/w        */
           uint32_t RSVD_7_6                : 2;  /* [7:6]          ro         */
           uint32_t FID1                    : 6;  /* [13:8]         r/w        */
           uint32_t RSVD_15_14              : 2;  /* [15:14]        ro         */
           uint32_t FID2                    : 6;  /* [21:16]        r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t FID3                    : 6;  /* [29:24]        r/w        */
           uint32_t RSVD_31_30              : 2;  /* [31:30]        ro         */
    } UART_LIN_PID_FILTER_0;

    /* 0x118*/
    struct {
           uint32_t FID4                    : 6;  /* [5:0]          r/w        */
           uint32_t RSVD_7_6                : 2;  /* [7:6]          ro         */
           uint32_t FID5                    : 6;  /* [13:8]         r/w        */
           uint32_t RSVD_15_14              : 2;  /* [15:14]        ro         */
           uint32_t FID6                    : 6;  /* [21:16]        r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t FID7                    : 6;  /* [29:24]        r/w        */
           uint32_t RSVD_31_30              : 2;  /* [31:30]        ro         */
    } UART_LIN_PID_FILTER_1;

    /* 0x11c*/
    struct {
           uint32_t FID8                    : 6;  /* [5:0]          r/w        */
           uint32_t RSVD_7_6                : 2;  /* [7:6]          ro         */
           uint32_t FID9                    : 6;  /* [13:8]         r/w        */
           uint32_t RSVD_15_14              : 2;  /* [15:14]        ro         */
           uint32_t FID10                   : 6;  /* [21:16]        r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t FID11                   : 6;  /* [29:24]        r/w        */
           uint32_t RSVD_31_30              : 2;  /* [31:30]        ro         */
    } UART_LIN_PID_FILTER_2;

    /* 0x120*/
    struct {
           uint32_t FID12                   : 6;  /* [5:0]          r/w        */
           uint32_t RSVD_7_6                : 2;  /* [7:6]          ro         */
           uint32_t FID13                   : 6;  /* [13:8]         r/w        */
           uint32_t RSVD_15_14              : 2;  /* [15:14]        ro         */
           uint32_t FID14                   : 6;  /* [21:16]        r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
           uint32_t FID15                   : 6;  /* [29:24]        r/w        */
           uint32_t RSVD_31_30              : 2;  /* [31:30]        ro         */
    } UART_LIN_PID_FILTER_3;

    /* 0x124*/
    struct {
           uint32_t FID_VAGUE               : 6;  /* [5:0]          r/w        */
           uint32_t RSVD_31_6               : 26;  /* [31:6]        ro         */
    } UART_LIN_PID_FILTER_VAGUE;

    /* 0x128*/
    struct {
           uint32_t FID_MASK                :17;  /* [16:0]         r/w        */
           uint32_t FID_VAGUE_MASK          : 6;  /* [22:17]        r/w        */
           uint32_t LIN_FILTER_EN           : 1;  /* [23]           r/w        */
           uint32_t RSVD_31_24              : 8;  /* [31:24]        ro         */
    } UART_LIN_PID_FILTER_CTRL;

};    /*uart_reg*/

struct uart_reg_w {
    /* 0x0*/
    union {
        uint32_t UART_RBR;
        uint32_t UART_THR;
        uint32_t UART_DLL;
    }UART_RBR_THR_DLL;
    /* 0x4*/
    union {
        uint32_t UART_DLH;
        uint32_t UART_IER;
    }UART_DLH_IER;
    /* 0x8*/
    union {
        uint32_t UART_IIR;
        uint32_t UART_FCR;
    }UART_IIR_FCR;
    /* 0xC*/
    uint32_t UART_LCR;
    /* 0x10*/
    uint32_t UART_AFCR;
    /* 0x14*/
    uint32_t UART_LSR;
    /* 0x18*/
    uint32_t UART_MSR;
    
    uint8_t zResverd0x01C[96];   /*pad 0x01C - 07B*/

    /* 0x7C*/
    uint32_t UART_USR;
    uint8_t zResverd0x080[64];   /*pad 0x080 - 0BF*/

    /* 0xC0*/
    uint32_t UART_FD;
    /* 0xC4*/
    uint32_t UART_RAR;
    /* 0xC8*/
    uint32_t UART_TAR;
    /* 0xCC*/
    uint32_t UART_LCR_EXT;
    uint8_t zResverd0x0D0[48];   /*pad 0x0D0 - 0FF*/

    /* 0x100*/
    uint32_t UART_LIN_CTL;
    /* 0x104*/
    uint32_t UART_LIN_RSP_LENGTH;
    /* 0x108*/
    uint32_t UART_LIN_ID_VALUE;
    /* 0x10C*/
    uint32_t UART_LIN_CHECKSUM;
    /* 0x110*/
    uint32_t UART_LIN_DEL_LENGTH;    
    /* 0x114*/
    uint32_t UART_LIN_PID_FILTER_0;
    /* 0x118*/
    uint32_t UART_LIN_PID_FILTER_1;
    /* 0x11c*/
    uint32_t UART_LIN_PID_FILTER_2;
    /* 0x120*/
    uint32_t UART_LIN_PID_FILTER_3;
    /* 0x124*/
    uint32_t UART_LIN_PID_FILTER_VAGUE;
    /* 0x128*/
    uint32_t UART_LIN_PID_FILTER_CTRL;
 
};    /*uart_reg*/

typedef volatile struct uart_reg uart_reg_t;
typedef volatile struct uart_reg_w uart_reg_w_t;

struct wdog_reg {
    /* 0x0*/
    uint32_t zResverd0x0;
    /* 0x4*/
    struct {
           uint32_t INT_PRESENT             : 1;  /* [0]            ro         */
           uint32_t RSVD_31_1               :31;  /* [31:1]         ro         */
    } WDOG_PARAM;

    /* 0x8*/
    struct {
           uint32_t WDOGE                   : 1;  /* [0]            r/w        */
           uint32_t DEBUGE                  : 1;  /* [1]            r/w        */
           uint32_t WAITE                   : 1;  /* [2]            r/w        */
           uint32_t STOPE                   : 1;  /* [3]            r/w        */
           uint32_t INTE                    : 1;  /* [4]            r/w        */
           uint32_t WINE                    : 1;  /* [5]            r/w        */
           uint32_t CFGUA                   : 1;  /* [6]            r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
           uint32_t CLKS                    : 2;  /* [9:8]          r/w        */
           uint32_t RSVD_15_10              : 6;  /* [15:10]        ro         */
           uint32_t TSTM                    : 3;  /* [18:16]        r/w        */
           uint32_t RSVD_23_19              : 5;  /* [23:19]        ro         */
           uint32_t CFGUF                   : 1;  /* [24]           ro         */
           uint32_t UNLKF                   : 1;  /* [25]           ro         */
           uint32_t INTF                    : 1;  /* [26]           w1c        */
           uint32_t RSVD_31_27              : 5;  /* [31:27]        ro         */
    } WDOG_CS;

    /* 0xC*/
    struct {
           uint32_t TMO                     :32;  /* [31:0]         r/w        */
    } WDOG_TMO;

    /* 0x10*/
    struct {
           uint32_t WIN                     :32;  /* [31:0]         r/w        */
    } WDOG_WIN;

    /* 0x14*/
    struct {
           uint32_t CNT                     :32;  /* [31:0]         r/w        */
    } WDOG_CNT;

};    /*wdog_reg*/

struct wdog_reg_w {
    /* 0x0*/
    uint32_t zResverd0x0;
    /* 0x4*/
    uint32_t WDOG_PARAM;
    /* 0x8*/
    uint32_t WDOG_CS;
    /* 0xC*/
    uint32_t WDOG_TMO;
    /* 0x10*/
    uint32_t WDOG_WIN;
    /* 0x14*/
    uint32_t WDOG_CNT;
};    /*wdog_reg*/

typedef volatile struct wdog_reg wdog_reg_t;
typedef volatile struct wdog_reg_w wdog_reg_w_t;

typedef volatile union
{
    struct {
        uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
        uint32_t RSVD_3_2                : 2;  /* [3:2]          ro         */
        uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
        uint32_t RSVD_7                  : 1;  /* [7]            ro         */
        uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
        uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
        uint32_t PWLK                    : 1;  /* [16]           r/w        */
        uint32_t RSVD_19_17              : 3;  /* [19:17]        ro         */
        uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
        uint32_t PRSTB                   : 1;  /* [21]           r/w        */
        uint32_t RSVD_23_22              : 2;  /* [23:22]        ro         */
        uint32_t PPR                     : 1;  /* [24]           r/w        */
        uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
        uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
        uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
        uint32_t RSVD_30_28              : 3;  /* [30:28]        ro         */
        uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } BF;
    uint32_t WORDVAL;
} ModuleClk_t;

#endif /*Z20K146M_H*/
