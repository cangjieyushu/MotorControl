/**************************************************************************************************/
/**
 * @file      : Z20K114M.h
 * @brief     : Z20K114M device header file.
 * @version   : V1.8.0
 * @date      : May-2020
 * @author    : Zhixin Semiconductor
 *
 * @note
 * @copyright : Copyright (c) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#ifndef Z20K114M_H
#define Z20K114M_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Variant Peripheral Instance Information
 */
#define CAN_INSTANCE_NUM      (1U)
#define SPI_INSTANCE_NUM      (2U)
#define I2C_INSTANCE_NUM      (1U)
#define UART_INSTANCE_NUM     (3U)

/**
 * @brief Peripheral Base Address
 */
#define FLASH_CODE_BASE_ADDR       ((uint32_t)0x00000000)            /*!< Code flash base address */
#define FLASH_DATA_BASE_ADDR       ((uint32_t)0x01000000)            /*!< Data flash base address */
#define FLASH_IFR_BASE_ADDR        ((uint32_t)0x02000000)            /*!< flash IFR base address */
#define SRAMU_BASE_ADDR            ((uint32_t)0x20000000)            /*!< SRAMU base address */
#define PERIPHERAL_BASE_ADDR       ((uint32_t)0x40000000)            /*!< Peripheral area base address */
#define AIPS0_BASE_ADDR            ((uint32_t)0x40000000)            /*!< AIPS0 base address */

#define PRI_PERI_BUS_BASE_ADDR     ((uint32_t)0xE0000000)            /*!< private Peripheral base address */

#define DMA_BASE_ADDR              (PERIPHERAL_BASE_ADDR + 0x8000UL)        /*!< DMA controller base address */
#define FLASHC_BASE_ADDR           (PERIPHERAL_BASE_ADDR + 0x20000UL)       /*!< flash controller base address */
#define DMAMUX_BASE_ADDR           (PERIPHERAL_BASE_ADDR + 0x22000UL)       /*!< DMA channel Multiplexer base address */
#define CAN0_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x24000UL)       /*!< CAN0 base address */
#define ADC0_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x26000UL)       /*!< ADC0 base address */
#define RTC_BASE_ADDR              (PERIPHERAL_BASE_ADDR + 0x28000UL)       /*!< RTC base address */
#define SPI0_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x2C000UL)       /*!< SPI0 base address */
#define SPI1_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x2D000UL)       /*!< SPI1 base address */
#define REGFILE_BASE_ADDR          (PERIPHERAL_BASE_ADDR + 0x34000UL)       /*!< REGFILE base address */
#define TDG0_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x35000UL)       /*!< TDG0 base address */
#define TMU_BASE_ADDR              (PERIPHERAL_BASE_ADDR + 0x36000UL)       /*!< TMU base address */
#define TIM0_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x38000UL)       /*!< TIM0 base address */
#define TIM1_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x39000UL)       /*!< TIM1 base address */
#define TIM2_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x3A000UL)       /*!< TIM2 base address */
#define STIM_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x40000UL)       /*!< STIM base address */
#define CRC_BASE_ADDR              (PERIPHERAL_BASE_ADDR + 0x43000UL)       /*!< CRC base address */
#define SCM_BASE_ADDR              (PERIPHERAL_BASE_ADDR + 0x48000UL)       /*!< System Control base address */
#define PORTA_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0x49000UL)       /*!< PORTA multiplexing base address */
#define PORTB_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0x4A000UL)       /*!< PORTB multiplexing base address */
#define PORTC_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0x4B000UL)       /*!< PORTC multiplexing base address */
#define PORTD_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0x4C000UL)       /*!< PORTD multiplexing base address */
#define PORTE_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0x4D000UL)       /*!< PORTE multiplexing base address */
#define WDOG_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x52000UL)       /*!< watchdog base address */
#define EWDT_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x61000UL)       /*!< External Watchdog Monitor base address */
#define SCC_BASE_ADDR              (PERIPHERAL_BASE_ADDR + 0x64000UL)       /*!< System Clock Controller base address */
#define PARCC_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0x65000UL)       /*!< Peripheral Clock Control base address */
#define I2C0_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x66000UL)       /*!< I2C0 base address */
#define UART0_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0x6A000UL)       /*!< UART0 base address */
#define UART1_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0x6B000UL)       /*!< UART1 base address */
#define UART2_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0x6C000UL)       /*!< UART2 base address */
#define CMP_BASE_ADDR              (PERIPHERAL_BASE_ADDR + 0x73000UL)       /*!< Analog comparator base address */
#define PMU_BASE_ADDR              (PERIPHERAL_BASE_ADDR + 0x7D000UL)       /*!< Power management Unit base address */
#define SRMC_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x7E000UL)       /*!< system reset and mode controller base address */
#define HWDIV_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0xFE000UL)       /*!< HWDIV base address */
#define GPIO_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0xFF000UL)       /*!< GPIO controller base address */
#define GPIOA_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0xFF000UL)       /*!< GPIOA base address */
#define GPIOB_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0xFF040UL)       /*!< GPIOB base address */
#define GPIOC_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0xFF080UL)       /*!< GPIOC base address */
#define GPIOD_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0xFF0C0UL)       /*!< GPIOD base address */
#define GPIOE_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0xFF100UL)       /*!< GPIOE base address */
#define RGPIO_BASE_ADDR            0xF8000000UL                             /*!< Fast GPIO controller base address */
#define RGPIOA_BASE_ADDR           (RGPIO_BASE_ADDR + 0x00000UL)            /*!< Fast GPIOA controller base address */
#define RGPIOB_BASE_ADDR           (RGPIO_BASE_ADDR + 0x00040UL)            /*!< Fast GPIOB controller base address */
#define RGPIOC_BASE_ADDR           (RGPIO_BASE_ADDR + 0x00080UL)            /*!< Fast GPIOC controller base address */
#define RGPIOD_BASE_ADDR           (RGPIO_BASE_ADDR + 0x000C0UL)            /*!< Fast GPIOD controller base address */
#define RGPIOE_BASE_ADDR           (RGPIO_BASE_ADDR + 0x00100UL)            /*!< Fast GPIOE controller base address */

/**
 * @brief IRQ Number Definition
 */
typedef enum IRQn
{
    /******  Cortex-M0+ Processor IRQ Numbers *******************************/
    NonMaskableInt_IRQn  = -14,    /*!< 2 Non Maskable Interrupt  */
    HardFalut_IRQn       = -13,    /*!< 3 Hardfault Interrupt  */
    SVCall_IRQn          = -5,     /*!< 11 Cortex-M0+ SV Call Interrupt */
    PendSV_IRQn          = -2,     /*!< 14 Cortex-M0+ Pend SV Interrupt  */
    SysTick_IRQn         = -1,     /*!< 15 Cortex-M0+ System Tick Interrupt  */

    /******  specific IRQ Numbers *************************************/
    DMA0TO3_IRQn         = 0,      /*!< DMA channel 0-3 transfer complete Interrupt */
    DMA4TO7_IRQn         = 1,      /*!< DMA channel 4-7 transfer complete Interrupt */
    DMA8TO11_IRQn        = 2,      /*!< DMA channel 8-11 transfer complete Interrupt  */
    DMA12TO15_IRQn       = 3,      /*!< DMA channel 12-15 transfer complete Interrupt */
    DMAERR_IRQn          = 4,      /*!< DMA error (channels 0-16) Interrupt   */
    I2C0_IRQn            = 5,      /*!< I2C 0 Interrupt  */
    Reserved6_IRQn       = 6,      /*!< Reserved Interrupt */
    SPI0_IRQn            = 7,      /*!< SPI 0 Interrupt */
    SPI1_IRQn            = 8,      /*!< SPI 1 Interrupt*/
    Reserved9_IRQn       = 9,      /*!< Reserved Interrupt */
    UART0_IRQn           = 10,     /*!< UART 0 Interrupt  */
    UART1_IRQn           = 11,     /*!< UART 1 Interrupt  */
    UART2_IRQn           = 12,     /*!< UART2 Interrupt  */
    Reserved13_IRQn      = 13,     /*!< Reserved Interrupt*/
    ADC0_IRQn             = 14,    /*!< ADC0  Interrupt  */
    FLASH_IRQn           = 15,     /*!< flash ISR */
    CMP_IRQn             = 16,     /*!< CMP Interrupt   */
    TIM0_IRQn            = 17,     /*!< TIM 0 Interrupt  */
    TIM1_IRQn            = 18,     /*!< TIM 1 Interrupt */
    TIM2_IRQn            = 19,     /*!< TIM 2 Interrupt */
    CAN0_IRQn            = 20,     /*!< CAN 0 Interrupt*/
    Reserved21_IRQn      = 21,     /*!< Reserved Interrupt */
    RTC_IRQn             = 22,     /*!< RTC Interrupt    */
    PMU_IRQn             = 23,     /*!< PMU Interrupt    */
    TDG0_IRQn            = 24,     /*!< TDG0 Interrupt   */
    SCC_IRQn             = 25,     /*!< system clock controller Interrupt*/
    WDOG_IRQn            = 26,     /*!< watchdog Interrupt     */
    EWDT_IRQn            = 27,     /*!< external watchdog monitor Interrupt*/
    STIM_IRQn            = 28,     /*!< STIM Interrupt  */
    SRMC_IRQn            = 29,     /*!< system reset and mode control Interrupt*/
    PORTABC_IRQn         = 30,     /*!< port A B C Interrupt  */
    PORTDE_IRQn          = 31      /*!< port D E Interrupt    */
} IRQn_Type;

/**
 * Peripheral Register Defination
 */
struct adc_reg {
    /* 0x000*/
    struct {
           uint32_t DIFFEN                  : 1;  /* [0]            ro         */
           uint32_t CALOFSI                 : 1;  /* [1]            ro         */
           uint32_t RSVD_7_2                : 6;  /* [7:2]          ro         */
           uint32_t FIFO_NUM                : 8;  /* [15:8]         ro         */
           uint32_t MINOR                   : 8;  /* [23:16]        ro         */
           uint32_t MAJOR                   : 8;  /* [31:24]        ro         */
    } ADC_VERID;

    /* 0x004*/
    struct {
           uint32_t RSVD_7_0                : 8;  /* [7:0]          ro         */
           uint32_t FIFO_SIZE               : 8;  /* [15:8]         ro         */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } ADC_PARAM;

    /* 0x008*/
    struct {
           uint32_t ADC_EN                  : 1;  /* [0]            r/w        */
           uint32_t CAL_REQ                 : 1;  /* [1]            r/w        */
           uint32_t RST                     : 1;  /* [2]            r/w        */
           uint32_t DOZEN                   : 1;  /* [3]            r/w        */
           uint32_t TRIG_MODE_ENABLE        : 1;  /* [4]            r/w        */
           uint32_t TRIG_MODE               : 1;  /* [5]            r/w        */
           uint32_t MODE1_RST               : 1;  /* [6]            r/w        */
           uint32_t RSVD_31_7               :25;  /* [31:7]         ro         */
    } ADC_CTRL;

    /* 0x00C*/
    struct {
           uint32_t FWM_INT                 : 1;  /* [0]            r/w1c      */
           uint32_t FOF                     : 1;  /* [1]            r/w1c      */
           uint32_t TCOMP_INT               : 1;  /* [2]            r/w1c      */
           uint32_t CMP_INT                 : 1;  /* [3]            r/w1c      */
           uint32_t DMA_REQ                 : 1;  /* [4]            ro         */
           uint32_t RDY                     : 1;  /* [5]            ro         */
           uint32_t CAL_RDY                 : 1;  /* [6]            ro         */
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
           uint32_t RSVD_15                 : 1;  /* [15]           r/w        */
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

    /* 0x01C*/
    struct {
           uint32_t RSVD_5_0               : 6;  /* [5:0]          ro         */
           uint32_t RSVD_6                 : 1;  /* [6]            ro         */
           uint32_t RSVD_10_7              : 4;  /* [10:7]         ro         */
           uint32_t RSVD_30_11             :20;  /* [30:11]        ro         */
           uint32_t RSVD_31                : 1;  /* [31]           r/w        */
    } ADC_RSVD;

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
           uint32_t ADC_SWTRIG              : 1;  /* [0]            r/w        */
           uint32_t RSVD_31_1               :31;  /* [31:1]         ro         */
    } ADC_SWTRIG;

    /* 0x02C*/
    struct {
           uint32_t ADC_CAL_VAL             :13;  /* [12:0]         ro         */
           uint32_t RSVD_31_13              :19;  /* [31:13]        ro         */
    } ADC_CAL_VAL;

    /* 0x030*/
    struct {
           uint32_t CMD0                    : 5;  /* [4:0]          r/w        */
           uint32_t RSVD_7_5                : 3;  /* [7:5]          ro         */
           uint32_t CMD1                    : 5;  /* [12:8]         r/w        */
           uint32_t RSVD_15_13              : 3;  /* [15:13]        ro         */
           uint32_t CMD2                    : 5;  /* [20:16]        r/w        */
           uint32_t RSVD_23_21              : 3;  /* [23:21]        ro         */
           uint32_t CMD3                    : 5;  /* [28:24]        r/w        */
           uint32_t RSVD_31_29              : 3;  /* [31:29]        ro         */
    } ADC_CMD_BUFF0;

    /* 0x034*/
    struct {
           uint32_t CMD4                    : 5;  /* [4:0]          r/w        */
           uint32_t RSVD_7_5                : 3;  /* [7:5]          ro         */
           uint32_t CMD5                    : 5;  /* [12:8]         r/w        */
           uint32_t RSVD_31_13              :19;  /* [31:13]        ro         */
    } ADC_CMD_BUFF1;

};    /*adc_reg*/

struct adc_reg_w {
    /* 0x000*/
    uint32_t ADC_VERID;
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
    /* 0x01C*/
    uint32_t ADC_RSVD;
    /* 0x020*/
    uint32_t ADC_DATA_RD;
    /* 0x024*/
    uint32_t ADC_FCTRL;
    /* 0x028*/
    uint32_t ADC_SWTRIG;
    /* 0x02C*/
    uint32_t ADC_CAL_VAL;
    /* 0x030*/
    uint32_t ADC_CMD_BUFF0;
    /* 0x034*/
    uint32_t ADC_CMD_BUFF1;
};    /*adc_reg*/

typedef volatile struct adc_reg adc_reg_t;
typedef volatile struct adc_reg_w adc_reg_w_t;

struct can_reg {
    /* 0x00*/
    struct {
       uint32_t MAXMB                   : 7;  /* [6:0]          r/w        */
       uint32_t RSVD_7                  : 1;  /* [7]            reserve    */
       uint32_t IDAM                    : 2;  /* [9:8]          r/w        */
       uint32_t RSVD_10                 : 1;  /* [10]           reserve    */
       uint32_t FDEN                    : 1;  /* [11]           r/w        */
       uint32_t AEN                     : 1;  /* [12]           r/w        */
       uint32_t LPRIOEN                 : 1;  /* [13]           r/w        */
       uint32_t PNET_EN                 : 1;  /* [14]           r/w        */
       uint32_t DMAE                    : 1;  /* [15]           r/w        */
       uint32_t IRMQ                    : 1;  /* [16]           r/w        */
       uint32_t SRXDIS                  : 1;  /* [17]           r/w        */
       uint32_t DOZE                    : 1;  /* [18]           r/w        */
       uint32_t WAKSRC                  : 1;  /* [19]           r/w        */
       uint32_t LPMACK                  : 1;  /* [20]           read only  */
       uint32_t WRNEN                   : 1;  /* [21]           r/w        */
       uint32_t SLFWAK                  : 1;  /* [22]           r/w        */
       uint32_t SUPV                    : 1;  /* [23]           r/w        */
       uint32_t FRZACK                  : 1;  /* [24]           read only  */
       uint32_t SOFTRST                 : 1;  /* [25]           r/w        */
       uint32_t WAKMSK                  : 1;  /* [26]           r/w        */
       uint32_t NOTRDY                  : 1;  /* [27]           read only  */
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
       uint32_t RSVD_9_8                : 2;  /* [9:8]          reserve    */
       uint32_t RWRNMSK                 : 1;  /* [10]           r/w        */
       uint32_t TWRNMSK                 : 1;  /* [11]           r/w        */
       uint32_t LPB                     : 1;  /* [12]           r/w        */
       uint32_t RSVD_13                 : 1;  /* [13]           reserve    */
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
       uint32_t RSVD_31_16              :16;  /* [31:16]        reserve    */
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
       uint32_t WAKINT                  : 1;  /* [0]            r/w1c      */
       uint32_t ERRINT                  : 1;  /* [1]            r/w1c      */
       uint32_t BOFFINT                 : 1;  /* [2]            r/w1c      */
       uint32_t RX                      : 1;  /* [3]            read only  */
       uint32_t FLTCONF                 : 2;  /* [5:4]          read only  */
       uint32_t TX                      : 1;  /* [6]            read only  */
       uint32_t IDLE                    : 1;  /* [7]            read only  */
       uint32_t RXWRN                   : 1;  /* [8]            read only  */
       uint32_t TXWRN                   : 1;  /* [9]            read only  */
       uint32_t STFERR                  : 1;  /* [10]           read only  */
       uint32_t FRAMERR                 : 1;  /* [11]           read only  */
       uint32_t CRCERR                  : 1;  /* [12]           read only  */
       uint32_t ACKERR                  : 1;  /* [13]           read only  */
       uint32_t BIT0ERR                 : 1;  /* [14]           read only  */
       uint32_t BIT1ERR                 : 1;  /* [15]           read only  */
       uint32_t RWRNINT                 : 1;  /* [16]           read only  */
       uint32_t TWRNINT                 : 1;  /* [17]           read only  */
       uint32_t SYNCH                   : 1;  /* [18]           read only  */
       uint32_t BUSOFFDONEINT           : 1;  /* [19]           r/w1c      */
       uint32_t ERRINT_FAST             : 1;  /* [20]           r/w1c      */
       uint32_t ERROVR                  : 1;  /* [21]           r/w1c      */
       uint32_t RSVD_25_22              : 4;  /* [25:22]        reserve    */
       uint32_t STFERR_FAST             : 1;  /* [26]           read only  */
       uint32_t FRAMERR_FAST            : 1;  /* [27]           read only  */
       uint32_t CRCERR_FAST             : 1;  /* [28]           read only  */
       uint32_t RSVD_29                 : 1;  /* [29]           reserve    */
       uint32_t BIT0ERR_FAST            : 1;  /* [30]           read only  */
       uint32_t BIT1ERR_FAST            : 1;  /* [31]           read only  */
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
       uint32_t BUF0I                   : 1;  /* [0]            r/w1c      */
       uint32_t BUF4TO1I                : 4;  /* [4:1]          r/w1c      */
       uint32_t BUF5I                   : 1;  /* [5]            r/w1c      */
       uint32_t BUF6I                   : 1;  /* [6]            r/w1c      */
       uint32_t BUF7I                   : 1;  /* [7]            r/w1c      */
       uint32_t BUF31TO8I               :24;  /* [31:8]         r/w1c      */
    } CAN_IFLAG1;

    /* 0x34*/
    struct {
       uint32_t RSVD_10_0               :11;  /* [10:0]         reserve    */
       uint32_t EDFLTDIS                : 1;  /* [11]           r/w        */
       uint32_t ISOCANFDEN              : 1;  /* [12]           r/w        */
       uint32_t RSVD_13                 : 1;  /* [13]           reserve    */
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
       uint32_t RSVD_12_0               :13;  /* [12:0]         reserve    */
       uint32_t IMB                     : 1;  /* [13]           read only  */
       uint32_t VPS                     : 1;  /* [14]           read only  */
       uint32_t RSVD_15                 : 1;  /* [15]           reserve    */
       uint32_t LPTM                    : 7;  /* [22:16]        read only  */
       uint32_t RSVD_31_23              : 9;  /* [31:23]                   */
    } CAN_ESR2;

    uint8_t zResverd0x03C[8];   /*pad 0x03C - 043*/

    /* 0x44*/
    struct {
       uint32_t TXCRC                   :15;  /* [14:0]         read only  */
       uint32_t RSVD_15                 : 1;  /* [15]           reserve    */
       uint32_t MBCRC                   : 7;  /* [22:16]        read only  */
       uint32_t RSVD_31_23              : 9;  /* [31:23]        reserve    */
    } CAN_CRCR;

    /* 0x48*/
    struct {
       uint32_t FGM                     :32;  /* [31:0]         r/w        */
    } CAN_RXFGMASK;

    /* 0x4c*/
    struct {
       uint32_t IDHIT                   : 9;  /* [8:0]          read only  */
       uint32_t RSVD_31_9               :23;  /* [31:9]         reserve    */
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
       uint32_t BUF127TO96I             :32;  /* [31:0]         r/w1c      */
    } CAN_IFLAG4;

    /* 0x74*/
    struct {
       uint32_t BUF95TO64I              :32;  /* [31:0]         r/w1c      */
    } CAN_IFLAG3;

    uint8_t zResverd0x078[8];   /*pad 0x078 - 07F*/

    /* 0x80 */
    struct {
    struct {
       uint32_t TIME_STAMP              :16;  /* [15:0]                    */
       uint32_t DLC                     : 4;  /* [19:16]                   */
       uint32_t RTR                     : 1;  /* [20]                      */
       uint32_t IDE                     : 1;  /* [21]                      */
       uint32_t SRR                     : 1;  /* [22]                      */
       uint32_t RSVD_23                 : 1;  /* [23]                      */
       uint32_t CODE                    : 4;  /* [27:24]                   */
       uint32_t RSVD_28                 : 1;  /* [28]                      */
       uint32_t ESI                     : 1;  /* [29]                      */
       uint32_t BRS                     : 1;  /* [30]                      */
       uint32_t EDL                     : 1;  /* [31]                      */
    } MB0;

    /* 0x84*/
    struct {
       uint32_t ID_EXTEND               :18;  /* [17:0]                    */
       uint32_t ID_STANDARD             :11;  /* [28:18]                   */
       uint32_t PRIO                    : 3;  /* [31:29]                   */
    } MB1;

    /* 0x88*/
    struct {
       uint32_t DATA_BYTE               :32;  /* [31:0]                    */
    } MB2;

    /* 0x8c*/
    struct {
       uint32_t DATA_BYTE               :32;  /* [31:0]                    */
    } MB3;
    } CAN_MB[64];
    uint8_t zResverd0x0480[0x400];   /*pad 0x0480 - 087F*/

    /* 0x880*/
    struct {
       uint32_t MI                      : 32;  /* [1]                       */
    } CAN_RXIMR[64];

    uint8_t zResverd0x0A80[352];   /*pad 0x0A80 - 0ADF, 64*4 + 96*/

    /* 0xAE0*/
    struct {
       uint32_t RSVD_6_0                : 7;  /* [6:0]          reserve    */
       uint32_t NCEFAFRZ                : 1;  /* [7]            r/w        */
       uint32_t ECCDIS                  : 1;  /* [8]            r/w        */
       uint32_t RERRDIS                 : 1;  /* [9]            r/w        */
       uint32_t RSVD_12_10              : 3;  /* [12:10]        reserve    */
       uint32_t EXTERRIE                : 1;  /* [13]           r/w        */
       uint32_t FAERRIE                 : 1;  /* [14]           r/w        */
       uint32_t HAERRI                  : 1;  /* [15]           r/w        */
       uint32_t CEI_MSK                 : 1;  /* [16]           r/w        */
       uint32_t RSVD_17                 : 1;  /* [17]           reserve    */
       uint32_t FANCEI_MSK              : 1;  /* [18]           r/w        */
       uint32_t HANCEI_MSK              : 1;  /* [19]           r/w        */
       uint32_t RSVD_30_20              :11;  /* [30:20]        reserve    */
       uint32_t ECRWRDIS                : 1;  /* [31]           r/w        */
    } CAN_MECR;

    /* 0xAE4*/
    struct {
       uint32_t INJADDR_L               : 2;  /* [1:0]          r/w        */
       uint32_t INJADDR_H               :12;  /* [13:2]         r/w        */
       uint32_t RSVD_31_14              :18;  /* [31:14]        reserve    */
    } CAN_ERRIAR;

    /* 0xAE8*/
    struct {
       uint32_t DFLIP                   :32;  /* [31:0]         r/w        */
    } CAN_ERRIDPR;

    /* 0xAEC*/
    struct {
       uint32_t PFLIP0                  : 5;  /* [4:0]          r/w        */
       uint32_t RSVD_7_5                : 3;  /* [7:5]          reserve    */
       uint32_t PFLIP1                  : 5;  /* [12:8]         r/w        */
       uint32_t RSVD_15_13              : 3;  /* [15:13]        reserve    */
       uint32_t PFLIP2                  : 5;  /* [20:16]        r/w        */
       uint32_t RSVD_23_21              : 3;  /* [23:21]        reserve    */
       uint32_t PFLIP3                  : 5;  /* [28:24]        r/w        */
       uint32_t RSVD_31_29              : 3;  /* [31:29]        reserve    */
    } CAN_ERRIPPR;

    /* 0xAF0*/
    struct {
       uint32_t ERRADDR                 :14;  /* [13:0]         read only  */
       uint32_t RSVD_15_14              : 2;  /* [15:14]        reserve    */
       uint32_t SAID                    : 3;  /* [18:16]        read only  */
       uint32_t RSVD_23_19              : 5;  /* [23:19]        reserve    */
       uint32_t NCE                     : 1;  /* [24]           read only  */
       uint32_t RSVD_31_25              : 7;  /* [31:25]        reserve    */
    } CAN_RERRAR;

    /* 0xAF4*/
    struct {
       uint32_t RDATA                   :32;  /* [31:0]         read only  */
    } CAN_RERRDR;

    /* 0xAF8*/
    struct {
       uint32_t SYND0                   : 5;  /* [4:0]          read only  */
       uint32_t RSVD_6_5                : 2;  /* [6:5]          reserve    */
       uint32_t BE0                     : 1;  /* [7]            read only  */
       uint32_t SYND1                   : 5;  /* [12:8]         read only  */
       uint32_t RSVD_14_13              : 2;  /* [14:13]        read only  */
       uint32_t BE1                     : 1;  /* [15]           read only  */
       uint32_t SYND2                   : 5;  /* [20:16]        read only  */
       uint32_t RSVD_22_21              : 2;  /* [22:21]        reserve    */
       uint32_t BE2                     : 1;  /* [23]           read only  */
       uint32_t SYND3                   : 5;  /* [28:24]        read only  */
       uint32_t RSVD_30_29              : 2;  /* [30:29]        reserve    */
       uint32_t BE3                     : 1;  /* [31]           read only  */
    } CAN_RERRSYNR;

    /* 0xAFC*/
    struct {
       uint32_t CEIOF                   : 1;  /* [0]            r/w1c      */
       uint32_t RSVD_1                  : 1;  /* [1]            reserve    */
       uint32_t FANCEIOF                : 1;  /* [2]            r/w1c      */
       uint32_t HANCEIOF                : 1;  /* [3]            r/w1c      */
       uint32_t RSVD_15_4               :12;  /* [15:4]         reserve    */
       uint32_t CEIF                    : 1;  /* [16]           r/w1c      */
       uint32_t RSVD_17                 : 1;  /* [17]           reserve    */
       uint32_t FANCEIF                 : 1;  /* [18]           r/w1c      */
       uint32_t HANCEIF                 : 1;  /* [19]           r/w1c      */
       uint32_t RSVD_31_20              :12;  /* [31:20]        reserve    */
    } CAN_ERRSR;

    /* 0xB00*/
    struct {
       uint32_t FCS                     : 2;  /* [1:0]          r/w        */
       uint32_t IDFS                    : 2;  /* [3:2]          r/w        */
       uint32_t PLFS                    : 2;  /* [5:4]          r/w        */
       uint32_t RSVD_7_6                : 2;  /* [7:6]          reserve    */
       uint32_t NMATCH                  : 8;  /* [15:8 ]         r/w        */
       uint32_t WUMF_MSK                : 1;  /* [16]           r/w        */
       uint32_t WTOF_MSK                : 1;  /* [17]           r/w        */
       uint32_t RSVD_31_18              :14;  /* [31:18]                   */
    } CAN_CTRL1_PN;

    /* 0xB04*/
    struct {
       uint32_t MATCHTO                 :16;  /* [15:0]         r/w        */
       uint32_t RSVD_31_16              :16;  /* [31:16]        reserve    */
    } CAN_CTRL2_PN;

    /* 0xB08*/
    struct {
       uint32_t RSVD_7_0                : 8;  /* [7:0]          reserve    */
       uint32_t MCOUNTER                : 8;  /* [15:8]         read only  */
       uint32_t WUMF                    : 1;  /* [16]           r/w1c      */
       uint32_t WTOF                    : 1;  /* [17]           r/w1c      */
       uint32_t RSVD_31_18              :14;  /* [31:18]        reserve    */
    } CAN_WU_MTC;

    /* 0xB0C*/
    struct {
       uint32_t FLT_ID1                 :29;  /* [28:0]         r/w        */
       uint32_t FLT_RTR                 : 1;  /* [29]           r/w        */
       uint32_t FLT_IDE                 : 1;  /* [30]           r/w        */
       uint32_t RSVD_31                 : 1;  /* [31]           reserve    */
    } CAN_FLT_ID1;

    /* 0xB10*/
    struct {
       uint32_t FLT_DLC_HI              : 4;  /* [3:0]                     */
       uint32_t RSVD_15_4               :12;  /* [15:4]         reserve    */
       uint32_t FLT_DLC_LO              : 4;  /* [19:16]        r/w        */
       uint32_t RSVD_31_20              :12;  /* [31:20]        reserve    */
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
       uint32_t RSVD_31                 : 1;  /* [31]           reserve    */
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
       uint32_t RSVD_15_0               :16;  /* [15:0]         reserve    */
       uint32_t DLC                     : 4;  /* [19:16]        read only  */
       uint32_t RTR                     : 1;  /* [20]           read only  */
       uint32_t IDE                     : 1;  /* [21]           read only  */
       uint32_t SRR                     : 1;  /* [22]           read only  */
       uint32_t RSVD_31_23              : 9;  /* [31:23]        reserve    */
    } CS;

    /* 0xB44*/
    struct {
       uint32_t ID                      :29;  /* [28:0]         read only  */
       uint32_t RSVD_31_29              : 3;  /* [31:29]        reserve    */
    } ID;

    /* 0xB48*/
    struct {
       uint32_t DATA_BYTE_3             : 8;  /* [7:0]          read only  */
       uint32_t DATA_BYTE_2             : 8;  /* [15:8]         read only  */
       uint32_t DATA_BYTE_1             : 8;  /* [23:16]        read only  */
       uint32_t DATA_BYTE_0             : 8;  /* [31:24]        read only  */
    } D03;

    /* 0xB4C*/
    struct {
       uint32_t DATA_BYTE_7             : 8;  /* [7:0]          read only  */
       uint32_t DATA_BYTE_6             : 8;  /* [15:8]         read only  */
       uint32_t DATA_BYTE_5             : 8;  /* [23:16]        read only  */
       uint32_t DATA_BYTE_4             : 8;  /* [31:24]        read only  */
    } D47;
    } CAN_WMB[4];
	
    uint8_t zResverd0x0B80[0x80];   /*pad 0x0B80 - 0BFF*/

    /* 0xC00*/
    struct {
       uint32_t TDCVAL                  : 6;  /* [5:0]          read only  */
       uint32_t RSVD_7_6                : 2;  /* [7:6]          reserve    */
       uint32_t TDCOFF                  : 5;  /* [12:8]         r/w        */
       uint32_t RSVD_13                 : 1;  /* [13]           reserve    */
       uint32_t TDCFAIL                 : 1;  /* [14]           r/w1c      */
       uint32_t TDCEN                   : 1;  /* [15]           r/w        */
       uint32_t MBDSR0                  : 2;  /* [17:16]        r/w        */
       uint32_t RSVD_18                 : 1;  /* [18]           reserve    */
       uint32_t MBDSR1                  : 2;  /* [20:19]        r/w        */
       uint32_t RSVD_21                 : 1;  /* [21]           reserve    */
       uint32_t MBDSR2                  : 2;  /* [23:22]        r/w        */
       uint32_t RSVD_24                 : 1;  /* [24]           reserve    */
       uint32_t MBDSR3                  : 2;  /* [26:25]        r/w        */
       uint32_t RSVD_30_27              : 4;  /* [30:27]        reserve    */
       uint32_t FD_RATE                 : 1;  /* [31]           r/w        */
    } CAN_FDCTRL;

    /* 0xC04*/
    struct {
       uint32_t FPSEG2                  : 3;  /* [2:0]          r/w        */
       uint32_t RSVD_4_3                : 2;  /* [4:3]          reserve    */
       uint32_t FPSEG1                  : 3;  /* [7:5]          r/w        */
       uint32_t RSVD_9_8                : 2;  /* [9:8]          reserve    */
       uint32_t FPROPSEG                : 5;  /* [14:10]        r/w        */
       uint32_t RSVD_15                 : 1;  /* [15]           reserve    */
       uint32_t FRJW                    : 3;  /* [18:16]        r/w        */
       uint32_t RSVD_19                 : 1;  /* [19]           reserve    */
       uint32_t FPRESDIV                :10;  /* [29:20]        r/w        */
       uint32_t RSVD_31_30              : 2;  /* [31:30]        reserve    */
    } CAN_FDCBT;

    /* 0xC08*/
    struct {
       uint32_t FD_TXCRC                :21;  /* [20:0]         read only  */
       uint32_t RSVD_23_21              : 3;  /* [23:21]        reserve    */
       uint32_t FD_MBCRC                : 7;  /* [30:24]        read only  */
       uint32_t RSVD_31                 : 1;  /* [31]           reserve    */
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
    uint32_t MB0;
    /* 0x84*/
    uint32_t MB1;
    /* 0x88*/
    uint32_t MB2;
    /* 0x8c*/
    uint32_t MB3;
    } CAN_MB[64];
    uint8_t zResverd0x0480[0x400];   /*pad 0x0480 - 087F*/

    /* 0x880*/
    uint32_t CAN_RXIMR[64];
    uint8_t zResverd0x0A80[352];   /*pad 0x0A80 - 0ADF, 64*4 + 96*/

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
	
    uint8_t zResverd0x0B80[0x80];   /*pad 0x0B80 - 0BFF*/

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
    struct {
           uint32_t VERID                   :32;  /* [31:0]         ro         */
    } CMP_VERID;

    /* 0x4*/
    struct {
           uint32_t DAC_RES                 : 4;  /* [3:0]          ro         */
           uint32_t RSVD_31_4               :28;  /* [31:4]                    */
    } CMP_PARAM;

    /* 0x8*/
    struct {
           uint32_t CMP_SEL                 : 1;  /* [0]            r/w        */
           uint32_t CMP_EN                  : 1;  /* [1]            r/w        */
           uint32_t SOC_TRG_EN              : 1;  /* [2]            r/w        */
           uint32_t STOP_EN                 : 1;  /* [3]            r/w        */
           uint32_t RSVD_31_4               :28;  /* [31:4]                    */
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
           uint32_t RSVD_15_8               : 8;  /* [15:8]                    */
           uint32_t FILT_CNT                : 3;  /* [18:16]        r/w        */
           uint32_t RSVD_23_19              : 5;  /* [23:19]                   */
           uint32_t FILT_PER                : 8;  /* [31:24]        r/w        */
    } CMP_CCR1;

    /* 0x10*/
    struct {
           uint32_t HS_HSTCTR               : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]                     */
           uint32_t LS_HSTCTR               : 2;  /* [5:4]          r/w        */
           uint32_t RSVD_15_6               :10;  /* [15:6]                    */
           uint32_t HS_PSEL                 : 4;  /* [19:16]        r/w        */
           uint32_t HS_MSEL                 : 4;  /* [23:20]        r/w        */
           uint32_t LS_PSEL                 : 4;  /* [27:24]        r/w        */
           uint32_t LS_MSEL                 : 4;  /* [31:28]        r/w        */
    } CMP_CCR2;

    /* 0x14*/
    struct {
           uint32_t DAC_EN                  : 1;  /* [0]            r/w        */
           uint32_t RSVD_1                  : 1;  /* [1]                       */
           uint32_t RSVD_7_2                : 6;  /* [7:2]                     */
           uint32_t VREF_SEL                : 1;  /* [8]            r/w        */
           uint32_t RSVD_15_9               : 7;  /* [15:9]                    */
           uint32_t DAC_SEL                 : 8;  /* [23:16]        r/w        */
           uint32_t RSVD_31_24              : 8;  /* [31:24]                   */
    } CMP_DCR;

    /* 0x18*/
    struct {
           uint32_t CFR_IE                  : 1;  /* [0]            r/w        */
           uint32_t CFF_IE                  : 1;  /* [1]            r/w        */
           uint32_t RSVD_31_2               :30;  /* [31:2]                    */
    } CMP_IER;

    /* 0x1C*/
    struct {
           uint32_t CFR                     : 1;  /* [0]            r/w1c      */
           uint32_t CFF                     : 1;  /* [1]            r/w1c      */
           uint32_t RSVD_7_2                : 6;  /* [7:2]                     */
           uint32_t COUT                    : 1;  /* [8]            ro         */
           uint32_t RSVD_31_9               :23;  /* [31:9]                    */
    } CMP_CSR;

};    /*cmp_reg*/

struct cmp_reg_w {
    /* 0x0*/
    uint32_t CMP_VERID;
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

struct crc_reg {
    /* 0x0*/
    struct {
           uint32_t FEATURE                 :16;  /* [15:0]         r          */
           uint32_t MINOR                   : 8;  /* [23:16]        r          */
           uint32_t MAJOR                   : 8;  /* [31:24]        r          */
    } CRC_VERID;

    /* 0x4*/
    struct {
           uint32_t RSVD_31_0               :32;  /* [31:0]         r          */
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
           uint32_t RSVD_3                  : 1;  /* [3]            r          */
           uint32_t RT                      : 2;  /* [5:4]          r/w        */
           uint32_t WT                      : 2;  /* [7:6]          r/w        */
           uint32_t RSVD_31_8               :24;  /* [31:8]         r          */
    } CRC_CTRL;

};    /*crc_reg*/

struct crc_reg_w {
    /* 0x0*/
    uint32_t CRC_VERID;
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
           uint32_t SRC_MUX                 : 6;  /* [6:1]          r/w        */
           uint32_t RSVD_31_7               :25;  /* [31:7]         reserve    */
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
           uint32_t RSVD_5_4                : 2;  /* [5:4]                     */
           uint32_t BUSY                    : 1;  /* [6]            r/o        */
           uint32_t RSVD_31_7               :25;  /* [31:7]                    */
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
           uint32_t RSVD_31_16              :16;  /* [31:16]                   */
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
           uint32_t RSVD_31_16              :16;  /* [31:16]                   */
    } DMA_EIE;

    uint8_t zResverd0x010[4];   /*pad 0x010 - 013*/

    /* 0x14*/
    struct {
           uint32_t CCDONE                  : 4;  /* [3:0]          w/o        */
           uint32_t RSVD_5_4                : 2;  /* [5:4]                     */
           uint32_t CACDONE                 : 1;  /* [6]            w/o        */
           uint32_t WPEN0                   : 1;  /* [7]            w/o        */
           uint32_t SCSTART                 : 4;  /* [11:8]         w/o        */
           uint32_t RSVD_13_12              : 2;  /* [13:12]                   */
           uint32_t SACSTART                : 1;  /* [14]           w/o        */
           uint32_t WPEN1                   : 1;  /* [15]           w/o        */
           uint32_t CCES                    : 4;  /* [19:16]        w/o        */
           uint32_t RSVD_21_20              : 2;  /* [21:20]                   */
           uint32_t CACES                   : 1;  /* [22]           w/o        */
           uint32_t WPEN2                   : 1;  /* [23]           w/o        */
           uint32_t CCIS                    : 4;  /* [27:24]        w/o        */
           uint32_t RSVD_29_28              : 2;  /* [29:28]                   */
           uint32_t CACIS                   : 1;  /* [30]           w/o        */
           uint32_t WPEN3                   : 1;  /* [31]           w/o        */
    } DMA_GCC;

    /* 0x18*/
    struct {
           uint32_t DBEF                    : 1;  /* [0]            r/o        */
           uint32_t SBEF                    : 1;  /* [1]            r/o        */
           uint32_t RSVD_2                  : 1;  /* [2]                       */
           uint32_t NUMEF                   : 1;  /* [3]            r/o        */
           uint32_t DOEF                    : 1;  /* [4]            r/o        */
           uint32_t DAEF                    : 1;  /* [5]            r/o        */
           uint32_t SOEF                    : 1;  /* [6]            r/o        */
           uint32_t SAEF                    : 1;  /* [7]            r/o        */
           uint32_t CHEF                    : 4;  /* [11:8]         r/o        */
           uint32_t RSVD_12                 : 1;  /* [12]                      */
           uint32_t PRIEF                   : 1;  /* [13]           r/o        */
           uint32_t RSVD_14                 : 1;  /* [14]                      */
           uint32_t ERRF                    : 1;  /* [15]           r/o        */
           uint32_t RSVD_31_16              :16;  /* [31:16]                   */
    } DMA_ES;

    /* 0x1C*/
    struct {
           uint32_t ERR0                    : 1;  /* [0]            r/o        */
           uint32_t ERR1                    : 1;  /* [1]            r/o        */
           uint32_t ERR2                    : 1;  /* [2]            r/o        */
           uint32_t ERR3                    : 1;  /* [3]            r/o        */
           uint32_t ERR4                    : 1;  /* [4]            r/o        */
           uint32_t ERR5                    : 1;  /* [5]            r/o        */
           uint32_t ERR6                    : 1;  /* [6]            r/o        */
           uint32_t ERR7                    : 1;  /* [7]            r/o        */
           uint32_t ERR8                    : 1;  /* [8]            r/o        */
           uint32_t ERR9                    : 1;  /* [9]            r/o        */
           uint32_t ERR10                   : 1;  /* [10]           r/o        */
           uint32_t ERR11                   : 1;  /* [11]           r/o        */
           uint32_t ERR12                   : 1;  /* [12]           r/o        */
           uint32_t ERR13                   : 1;  /* [13]           r/o        */
           uint32_t ERR14                   : 1;  /* [14]           r/o        */
           uint32_t ERR15                   : 1;  /* [15]           r/o        */
           uint32_t RSVD_31_16              :16;  /* [31:16]                   */
    } DMA_CES;

    /* 0x20*/
    struct {
           uint32_t INT0                    : 1;  /* [0]            r/o        */
           uint32_t INT1                    : 1;  /* [1]            r/o        */
           uint32_t INT2                    : 1;  /* [2]            r/o        */
           uint32_t INT3                    : 1;  /* [3]            r/o        */
           uint32_t INT4                    : 1;  /* [4]            r/o        */
           uint32_t INT5                    : 1;  /* [5]            r/o        */
           uint32_t INT6                    : 1;  /* [6]            r/o        */
           uint32_t INT7                    : 1;  /* [7]            r/o        */
           uint32_t INT8                    : 1;  /* [8]            r/o        */
           uint32_t INT9                    : 1;  /* [9]            r/o        */
           uint32_t INT10                   : 1;  /* [10]           r/o        */
           uint32_t INT11                   : 1;  /* [11]           r/o        */
           uint32_t INT12                   : 1;  /* [12]           r/o        */
           uint32_t INT13                   : 1;  /* [13]           r/o        */
           uint32_t INT14                   : 1;  /* [14]           r/o        */
           uint32_t INT15                   : 1;  /* [15]           r/o        */
           uint32_t RSVD_31_16              :16;  /* [31:16]                   */
    } DMA_CIS;

    /* 0x24*/
    struct {
           uint32_t HRS0                    : 1;  /* [0]            r/o        */
           uint32_t HRS1                    : 1;  /* [1]            r/o        */
           uint32_t HRS2                    : 1;  /* [2]            r/o        */
           uint32_t HRS3                    : 1;  /* [3]            r/o        */
           uint32_t HRS4                    : 1;  /* [4]            r/o        */
           uint32_t HRS5                    : 1;  /* [5]            r/o        */
           uint32_t HRS6                    : 1;  /* [6]            r/o        */
           uint32_t HRS7                    : 1;  /* [7]            r/o        */
           uint32_t HRS8                    : 1;  /* [8]            r/o        */
           uint32_t HRS9                    : 1;  /* [9]            r/o        */
           uint32_t HRS10                   : 1;  /* [10]           r/o        */
           uint32_t HRS11                   : 1;  /* [11]           r/o        */
           uint32_t HRS12                   : 1;  /* [12]           r/o        */
           uint32_t HRS13                   : 1;  /* [13]           r/o        */
           uint32_t HRS14                   : 1;  /* [14]           r/o        */
           uint32_t HRS15                   : 1;  /* [15]           r/o        */
           uint32_t RSVD_31_16              :16;  /* [31:16]                   */
    } DMA_CHRS;

    /* 0x28*/
    struct {
           uint32_t CPRI3                   : 4;  /* [3:0]          r/w        */
           uint32_t RSVD_5_4                : 2;  /* [5:4]                     */
           uint32_t CPDIS3                  : 1;  /* [6]            r/w        */
           uint32_t CSE3                    : 1;  /* [7]            r/w        */
           uint32_t CPRI2                   : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_13_12              : 2;  /* [13:12]                   */
           uint32_t CPDIS2                  : 1;  /* [14]           r/w        */
           uint32_t CSE2                    : 1;  /* [15]           r/w        */
           uint32_t CPRI1                   : 4;  /* [19:16]        r/w        */
           uint32_t RSVD_21_20              : 2;  /* [21:20]                   */
           uint32_t CPDIS1                  : 1;  /* [22]           r/w        */
           uint32_t CSE1                    : 1;  /* [23]           r/w        */
           uint32_t CPRI0                   : 4;  /* [27:24]        r/w        */
           uint32_t RSVD_29_28              : 2;  /* [29:28]                   */
           uint32_t CPDIS0                  : 1;  /* [30]           r/w        */
           uint32_t CSE0                    : 1;  /* [31]           r/w        */
    } DMA_CPRI0;

    /* 0x2C*/
    struct {
           uint32_t CPRI7                   : 4;  /* [3:0]          r/w        */
           uint32_t RSVD_5_4                : 2;  /* [5:4]                     */
           uint32_t CPDIS7                  : 1;  /* [6]            r/w        */
           uint32_t CSE7                    : 1;  /* [7]            r/w        */
           uint32_t CPRI6                   : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_13_12              : 2;  /* [13:12]                   */
           uint32_t CPDIS6                  : 1;  /* [14]           r/w        */
           uint32_t CSE6                    : 1;  /* [15]           r/w        */
           uint32_t CPRI5                   : 4;  /* [19:16]        r/w        */
           uint32_t RSVD_21_20              : 2;  /* [21:20]                   */
           uint32_t CPDIS5                  : 1;  /* [22]           r/w        */
           uint32_t CSE5                    : 1;  /* [23]           r/w        */
           uint32_t CPRI4                   : 4;  /* [27:24]        r/w        */
           uint32_t RSVD_29_28              : 2;  /* [29:28]                   */
           uint32_t CPDIS4                  : 1;  /* [30]           r/w        */
           uint32_t CSE4                    : 1;  /* [31]           r/w        */
    } DMA_CPRI1;

    /* 0x30*/
    struct {
           uint32_t CPRI11                  : 4;  /* [3:0]          r/w        */
           uint32_t RSVD_5_4                : 2;  /* [5:4]                     */
           uint32_t CPDIS11                 : 1;  /* [6]            r/w        */
           uint32_t CSE11                   : 1;  /* [7]            r/w        */
           uint32_t CPRI10                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_13_12              : 2;  /* [13:12]                   */
           uint32_t CPDIS10                 : 1;  /* [14]           r/w        */
           uint32_t CSE10                   : 1;  /* [15]           r/w        */
           uint32_t CPRI9                   : 4;  /* [19:16]        r/w        */
           uint32_t RSVD_21_20              : 2;  /* [21:20]                   */
           uint32_t CPDIS9                  : 1;  /* [22]           r/w        */
           uint32_t CSE9                    : 1;  /* [23]           r/w        */
           uint32_t CPRI8                   : 4;  /* [27:24]        r/w        */
           uint32_t RSVD_29_28              : 2;  /* [29:28]                   */
           uint32_t CPDIS8                  : 1;  /* [30]           r/w        */
           uint32_t CSE8                    : 1;  /* [31]           r/w        */
    } DMA_CPRI2;

    /* 0x34*/
    struct {
           uint32_t CPRI15                  : 4;  /* [3:0]          r/w        */
           uint32_t RSVD_5_4                : 2;  /* [5:4]                     */
           uint32_t CPDIS15                 : 1;  /* [6]            r/w        */
           uint32_t CSE15                   : 1;  /* [7]            r/w        */
           uint32_t CPRI14                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_13_12              : 2;  /* [13:12]                   */
           uint32_t CPDIS14                 : 1;  /* [14]           r/w        */
           uint32_t CSE14                   : 1;  /* [15]           r/w        */
           uint32_t CPRI13                  : 4;  /* [19:16]        r/w        */
           uint32_t RSVD_21_20              : 2;  /* [21:20]                   */
           uint32_t CPDIS13                 : 1;  /* [22]           r/w        */
           uint32_t CSE13                   : 1;  /* [23]           r/w        */
           uint32_t CPRI12                  : 4;  /* [27:24]        r/w        */
           uint32_t RSVD_29_28              : 2;  /* [29:28]                   */
           uint32_t CPDIS12                 : 1;  /* [30]           r/w        */
           uint32_t CSE12                   : 1;  /* [31]           r/w        */
    } DMA_CPRI3;

    uint8_t zResverd0x038[456];   /*pad 0x038 - 01FF*/

    struct {
        /* 0x200*/
        struct {
            uint32_t SADDR : 32;  /* [31:0]         r/w        */
        } DMA_SADDR;

        /* 0x204*/
        struct {
            uint32_t DADDR : 32;  /* [31:0]         r/w        */
        } DMA_DADDR;

        /* 0x208*/
        struct {
            int32_t SAOFF : 16;  /* [15:0]         r/w        */
            int32_t DAOFF : 16;  /* [31:16]        r/w        */
        } DMA_AOFF;

        /* 0x20C*/
        struct {
            int32_t MLSAOFF : 16;  /* [15:0]         r/w        */
            int32_t MLDAOFF : 16;  /* [31:16]        r/w        */
        } DMA_MLAOFF;

        /* 0x210*/
        struct {
            uint32_t NUM : 32;  /* [31:0]         r/w        */
        } DMA_NUM;

        /* 0x214*/
        struct {
            uint32_t MLITER : 15;  /* [14:0]         r/w        */
            uint32_t RSVD_15: 1 ;  /* [15]                      */
            uint32_t MLSTA : 15;  /* [30:16]        r/o        */
            uint32_t RSVD_31: 1 ;  /* [31]                      */
        } DMA_ITER;

        /* 0x218*/
        struct {
            uint32_t START : 1;  /* [0]            r/w        */
            uint32_t INTE : 1;  /* [1]            r/w        */
            uint32_t RSVD_2 : 1;  /* [2]                       */
            uint32_t REQDIS : 1;  /* [3]            r/w        */
            uint32_t RSVD_5_4 : 2;  /* [5:4]                     */
            uint32_t BUSY : 1;  /* [6]            r/o        */
            uint32_t DONE : 1;  /* [7]            r/w        */
            uint32_t RSVD_15_8 : 8;  /* [15:8]                    */
            uint32_t DSIZE : 2;  /* [17:16]        r/w        */
            uint32_t RSVD_23_18 : 6;  /* [23:18]                   */
            uint32_t SSIZE : 2;  /* [25:24]        r/w        */
            uint32_t RSVD_31_26 : 6;  /* [31:26]                   */
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

struct ewdt_reg {
    /* 0x0*/
    struct {
           uint32_t MINOR                   : 4;  /* [3:0]          ro         */
           uint32_t MAJOR                   : 4;  /* [7:4]          ro         */
           uint32_t RSVD_31_8               :24;  /* [31:8]         ro         */
    } EWDT_VERID;

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
           uint32_t RSVD_23_7               :17;  /* [23:7]                    */
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
    uint32_t EWDT_VERID;
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
           uint32_t FAIL                    : 1;  /* [0]            r          */
           uint32_t RSVD_1                  : 1;  /* [1]            r          */
           uint32_t CMDABT                  : 1;  /* [2]            r/w1c      */
           uint32_t RSVD_4_3                : 2;  /* [4:3]          r          */
           uint32_t ACCERR                  : 1;  /* [5]            r/w1c      */
           uint32_t PREABT                  : 1;  /* [6]            r/w1c      */
           uint32_t CCIF                    : 1;  /* [7]            r/w1c      */
           uint32_t RSVD_10_8               : 3;  /* [10:8]         r          */
           uint32_t CMDWRF                  : 1;  /* [11]           r          */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        r          */
           uint32_t DFDIF                   : 1;  /* [16]           r/w1c      */
           uint32_t RSVD_29_17              :13;  /* [29:17]        r          */
           uint32_t DBG_ERSALL_DIS          : 1;  /* [30]           r          */
           uint32_t FSEC                    : 1;  /* [31]           r          */
    } FLASH_FSTAT;

    /* 0x4*/
    struct {
           uint32_t RSVD_6_0                : 7;  /* [6:0]          r          */
           uint32_t CCIE                    : 1;  /* [7]            r/w        */
           uint32_t DBG_ERS_FLG             : 1;  /* [8]            r          */
           uint32_t RSVD_15_9               : 7;  /* [15:9]         r          */
           uint32_t DFDIE                   : 1;  /* [16]           r/w        */
           uint32_t RSVD_31_17              :15;  /* [31:17]        r          */
    } FLASH_FCNFG;

    /* 0x8*/
    struct {
           uint32_t RWSC                    : 4;  /* [3:0]          r/w        */
           uint32_t RSVD_7_4                : 4;  /* [7:4]          r          */
           uint32_t LSMODE                  : 1;  /* [8]            r/w        */
           uint32_t RSVD_15_9               : 7;  /* [15:9]         r          */
           uint32_t FECCF                   : 1;  /* [16]           r/w        */
           uint32_t RSVD_23_17              : 7;  /* [23:17]        r          */
           uint32_t ABTREQ                  : 1;  /* [24]           r          */
           uint32_t RSVD_31_25              : 7;  /* [31:25]        r          */
    } FLASH_FCTRL;

    uint8_t zResverd0x0C[4];   /*pad 0x0C - 0F*/

    /* 0x10*/
    struct {
           uint32_t CMDCODE                 : 8;  /* [7:0]          r/w        */
           uint32_t RSVD_31_8               :24;  /* [31:8]         r          */
    } FLASH_FCMD;

    /* 0x14*/
    struct {
           uint32_t CMDOPT                  : 8;  /* [7:0]          r/w        */
           uint32_t RSVD_31_8               :24;  /* [31:8]         r          */
    } FLASH_FCMD_OPT;

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
    uint32_t FLASH_FCMD_OPT;
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

    /* 0x18*/
    struct {
           uint32_t RSVD_31_0               :32;  /* [31:0]         ro         */
    } GPIOx_PIDR;

    uint8_t zResverd[36];   /*pad 0x01C - 03F*/
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
    /* 0x18 */
    uint32_t GPIOx_PIDR;
    /* 0x1C */
    uint8_t zResverd[36];
};    /* gpio_reg */

typedef volatile struct gpio_reg gpio_reg_t;
typedef volatile struct gpio_reg_w gpio_reg_w_t;

struct hwdiv_reg {
    /* 0x0*/
    struct {
           uint32_t VERSION                 :32;  /* [31:0]         ro         */
    } HWDIV_VERSION;

    /* 0x4*/
    struct {
           uint32_t PARAM                   :32;  /* [31:0]         ro         */
    } HWDIV_PARAM;

    /* 0x8*/
    struct {
           uint32_t DIVIDEND                :32;  /* [31:0]         r/w        */
    } HWDIV_DEND;

    /* 0xC*/
    struct {
           uint32_t DIVISOR                 :32;  /* [31:0]         r/w        */
    } HWDIV_DSOR;

    /* 0x10*/
    struct {
           uint32_t DFS                     : 1;  /* [0]            r/w        */
           uint32_t USGN                    : 1;  /* [1]            r/w        */
           uint32_t DZE                     : 1;  /* [2]            r/w        */
           uint32_t DZ                      : 1;  /* [3]            ro         */
           uint32_t SQRT                    : 1;  /* [4]            ro         */
           uint32_t DIV                     : 1;  /* [5]            ro         */
           uint32_t BUSY                    : 1;  /* [6]            ro         */
           uint32_t RSVD_31_7               :25;  /* [31:7]         ro         */
    } HWDIV_CSR;

    /* 0x14*/
    struct {
           uint32_t STRT                    : 1;  /* [0]            w          */
           uint32_t RSVD_31_1               :31;  /* [31:1]         ro         */
    } HWDIV_STRT;

    /* 0x18*/
    struct {
           uint32_t RESULT                  :32;  /* [31:0]         ro         */
    } HWDIV_RES;

    /* 0x1C*/
    struct {
           uint32_t REMAINDER               :32;  /* [31:0]         ro         */
    } HWDIV_REM;

    /* 0x20*/
    struct {
           uint32_t RADICAND                :32;  /* [31:0]         r/w        */
    } HWDIV_RCND;

};    /*hwdiv_reg*/

struct hwdiv_reg_w {
    /* 0x0*/
    uint32_t HWDIV_VERSION;
    /* 0x4*/
    uint32_t HWDIV_PARAM;
    /* 0x8*/
    uint32_t HWDIV_DEND;
    /* 0xC*/
    uint32_t HWDIV_DSOR;
    /* 0x10*/
    uint32_t HWDIV_CSR;
    /* 0x14*/
    uint32_t HWDIV_STRT;
    /* 0x18*/
    uint32_t HWDIV_RES;
    /* 0x1C*/
    uint32_t HWDIV_REM;
    /* 0x20*/
    uint32_t HWDIV_RCND;
};    /*hwdiv_reg*/

typedef volatile struct hwdiv_reg hwdiv_reg_t;
typedef volatile struct hwdiv_reg_w hwdiv_reg_w_t;

struct i2c_reg {
    /* 0x00*/
    struct {
           uint32_t RSVD_31_0               :32;  /* [31:0]         ro         */
    } I2C_VERID;

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
           uint32_t RSVD_31_16              :16;  /* [31:16]        reserve    */
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
           uint32_t TXFIFO_IS_NOT_FULL       : 1;  /* [6]            ro         */
           uint32_t TXFIFO_IS_EMPTY         : 1;  /* [7]            ro         */
           uint32_t RXFIFO_IS_NOT_EMPTY     : 1;  /* [8]            ro         */
           uint32_t RXFIFO_IS_FULL           : 1;  /* [9]            ro         */
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
           uint32_t ERR_MASTER_ABRT         : 1;  /* [11]           ro         */
           uint32_t ERR_MASTER_DIS          : 1;  /* [12]           ro         */
           uint32_t ERR_SLAVE_ARBLOST       : 1;  /* [13]           ro         */
           uint32_t ERR_MASTER_LOST         : 1;  /* [14]           ro         */
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
           uint32_t CLR_ERR                 : 1;  /* [0]            r          */
           uint32_t RSVD_31_1               :31;  /* [31:1]         ro         */
    } I2C_RD_CLR_ERR_STATUS;

};    /*i2c_reg*/

struct i2c_reg_w {
    /* 0x00*/
    uint32_t I2C_VERID;
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
    uint32_t I2C_FST_CLK_LCNT;
    /* 0x3c*/
    uint32_t I2C_HS_CLK_HCNT;
    /* 0x40*/
    uint32_t I2C_HS_CLK_LCNT;
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

struct parcc_reg {
    /* 0x0*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_15_2               :14;  /* [15:2]         r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_WDOG;

    /* 0x4*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          r          */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            r          */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_EWDT;

    /* 0x8*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          r          */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            r          */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_STIM;

    /* 0xC*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          r          */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            r          */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_PWMTIMER0;

    /* 0x10*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          r          */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            r          */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_PWMTIMER1;

    /* 0x14*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          r          */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            r          */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_PWMTIMER2;

    /* 0x18*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          r          */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            r          */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_TDG0;

    /* 0x1C*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          r          */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            r          */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_CAN0;

    /* 0x20*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          r          */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            r          */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_CAN1;

    /* 0x24*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          r          */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            r          */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_UART0;

    /* 0x28*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          r          */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            r          */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_UART1;

    /* 0x2C*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          r          */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            r          */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_UART2;

    /* 0x30*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          r          */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            r          */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_UART3;

    /* 0x34*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          r          */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            r          */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_SPI0;

    /* 0x38*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          r          */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            r          */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_SPI1;

    /* 0x3C*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          r          */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            r          */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_SPI2;

    /* 0x40*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          r          */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            r          */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_I2C0;

    /* 0x44*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          r          */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            r          */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_I2C1;

    /* 0x48*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          r          */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            r          */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_ADC0;

    /* 0x4C*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_15_2               :14;  /* [15:2]         r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_CMP;

    /* 0x50*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_15_2               :14;  /* [15:2]         r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_CRC;

    /* 0x54*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_15_2               :14;  /* [15:2]         r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_FLASH;

    /* 0x58*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_15_2               :14;  /* [15:2]         r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_DMA;

    /* 0x5C*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_15_2               :14;  /* [15:2]         r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_DMAMUX;

    /* 0x60*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          r          */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            r          */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_PORTA;

    /* 0x64*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          r          */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            r          */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_PORTB;

    /* 0x68*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          r          */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            r          */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_PORTC;

    /* 0x6C*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          r          */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            r          */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_PORTD;

    /* 0x70*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          r          */
           uint32_t CLKMUX                  : 3;  /* [6:4]          r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            r          */
           uint32_t CLKDIV                  : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_PORTE;

    /* 0x74*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_15_2               :14;  /* [15:2]         r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_TMU;

    /* 0x78*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_15_2               :14;  /* [15:2]         r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_REGFILE;

    /* 0x7C*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_15_2               :14;  /* [15:2]         r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_GPIO;

    /* 0x80*/
    struct {
           uint32_t PCKMD                   : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_15_2               :14;  /* [15:2]         r          */
           uint32_t PWLK                    : 1;  /* [16]           r/w        */
           uint32_t RSVD_19_17              : 3;  /* [19:17]        r          */
           uint32_t PSUPVACEN               : 1;  /* [20]           r/w        */
           uint32_t PRSTB                   : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]        r          */
           uint32_t PPR                     : 1;  /* [24]           r/w        */
           uint32_t PCLKMUXPR               : 1;  /* [25]           r/w        */
           uint32_t PCLKDIVPR               : 1;  /* [26]           r/w        */
           uint32_t PSUPVACPR               : 1;  /* [27]           r/w        */
           uint32_t RSVD_30_28              : 3;  /* [30:28]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } PARCC_HWDIV;

};    /*parcc_reg*/

struct parcc_reg_w {
    /* 0x0*/
    uint32_t PARCC_WDOG;
    /* 0x4*/
    uint32_t PARCC_EWDT;
    /* 0x8*/
    uint32_t PARCC_STIM;
    /* 0xC*/
    uint32_t PARCC_PWMTIMER0;
    /* 0x10*/
    uint32_t PARCC_PWMTIMER1;
    /* 0x14*/
    uint32_t PARCC_PWMTIMER2;
    /* 0x18*/
    uint32_t PARCC_TDG0;
    /* 0x1C*/
    uint32_t PARCC_CAN0;
    /* 0x20*/
    uint32_t PARCC_CAN1;
    /* 0x24*/
    uint32_t PARCC_UART0;
    /* 0x28*/
    uint32_t PARCC_UART1;
    /* 0x2C*/
    uint32_t PARCC_UART2;
    /* 0x30*/
    uint32_t PARCC_UART3;
    /* 0x34*/
    uint32_t PARCC_SPI0;
    /* 0x38*/
    uint32_t PARCC_SPI1;
    /* 0x3C*/
    uint32_t PARCC_SPI2;
    /* 0x40*/
    uint32_t PARCC_I2C0;
    /* 0x44*/
    uint32_t PARCC_I2C1;
    /* 0x48*/
    uint32_t PARCC_ADC0;
    /* 0x4C*/
    uint32_t PARCC_CMP;
    /* 0x50*/
    uint32_t PARCC_CRC;
    /* 0x54*/
    uint32_t PARCC_FLASH;
    /* 0x58*/
    uint32_t PARCC_DMA;
    /* 0x5C*/
    uint32_t PARCC_DMAMUX;
    /* 0x60*/
    uint32_t PARCC_PORTA;
    /* 0x64*/
    uint32_t PARCC_PORTB;
    /* 0x68*/
    uint32_t PARCC_PORTC;
    /* 0x6C*/
    uint32_t PARCC_PORTD;
    /* 0x70*/
    uint32_t PARCC_PORTE;
    /* 0x74*/
    uint32_t PARCC_TMU;
    /* 0x78*/
    uint32_t PARCC_REGFILE;
    /* 0x7C*/
    uint32_t PARCC_GPIO;
    /* 0x80*/
    uint32_t PARCC_HWDIV;
};    /*parcc_reg*/

typedef volatile struct parcc_reg parcc_reg_t;
typedef volatile struct parcc_reg_w parcc_reg_w_t;

struct pmu_reg {
    /* 0x00*/
    struct {
           uint32_t RSVD_31_0               :32;  /* [31:0]         r          */
    } PMU_VERID;

    /* 0x04*/
    struct {
           uint32_t LPO_CLK_DIS             : 1;  /* [0]            r/w        */
           uint32_t LPO_CLK_SEL             : 1;  /* [1]            r/w        */
           uint32_t LPO_CLK_READY           : 1;  /* [2]            r          */
           uint32_t RSVD_31_3               :29;  /* [31:3]         ro         */
    } PMU_LPO_32K_CFG;

    /* 0x08*/
    struct {
           uint32_t LPO_32K_TRIM            : 7;  /* [6:0]          r/w        */
           uint32_t RSVD_31_7               :25;  /* [31:7]         ro         */
    } PMU_LPO_32K_TRIM;

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
           uint32_t LDO_LVD_ACT_EN          : 1;  /* [9]            r/w        */
           uint32_t LDO_LVD_LP_EN           : 1;  /* [10]           r/w        */
           uint32_t LDO_CLAMP_EN            : 1;  /* [11]           r/w        */
           uint32_t RSVD_31_12              :20;  /* [31:12]        ro         */
    } PMU_VDD5V_CSR;

    /* 0x14*/
    struct {
           uint32_t RSVD_30_0               :31;  /* [30:0]         ro         */
           uint32_t LOCK                    : 1;  /* [31]           w/r        */
    } PMU_LOCK;
    
};    /*pmu_reg*/

struct pmu_reg_w {
    /* 0x00*/
    uint32_t PMU_VERID;
    /* 0x04*/
    uint32_t PMU_LPO_32K_CFG;
    /* 0x08*/
    uint32_t PMU_LPO_32K_TRIM;
    /* 0x0c*/
    uint32_t PMU_ISO_CLR;
    /* 0x10*/
    uint32_t PMU_VDD5V_CSR;
    /* 0x14*/
    uint32_t PMU_LOCK;

};    /*pmu_reg_w*/

typedef volatile struct pmu_reg pmu_reg_t;
typedef volatile struct pmu_reg_w pmu_reg_w_t;

struct port_reg {
    /* 0x0*/
    struct {
           uint32_t FEATURE                 :16;  /* [15:0]         ro         */
           uint32_t MINOR                   : 8;  /* [23:16]        ro         */
           uint32_t MAJOR                   : 8;  /* [31:24]        ro         */
    } PORTx_VERID;

    /* 0x4*/
    struct {
           uint32_t RSVD_31_0               :32;  /* [31:0]         ro         */
    } PORTx_PARAM;

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
           uint32_t DSE                     : 1;  /* [6]            r/w        */
           uint32_t RSVD_7                  : 1;  /* [7]            ro         */
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
    uint32_t PORTx_VERID;
    /* 0x4*/
    uint32_t PORTx_PARAM;
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
           uint32_t DATA                    :32;  /* [31:0]         rw        */
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
           uint32_t RSVD_31_12              :20;  /* [31:12]        ro         */
    } RTC_CSR;

    /* 0x04*/
    struct {
           uint32_t SECOND_INT_MUX_SEL      : 3;  /* [2:0]          r/w        */
           uint32_t OVFLOW_IE               : 1;  /* [3]            r/w        */
           uint32_t ALARM_IE                : 1;  /* [4]            r/w        */
           uint32_t SECONDS_IE              : 1;  /* [5]            r/w        */
           uint32_t RSVD_31_6               :26;  /* [31:6]         ro         */
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

    /* 0x1c*/
    struct {
           uint32_t RSVD_31_0               :32;  /* [31:0]         ro         */
    } RTC_VERID;

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
    /* 0x1c*/
    uint32_t RTC_VERID;
};    /*rtc_reg*/

typedef volatile struct rtc_reg rtc_reg_t;
typedef volatile struct rtc_reg_w rtc_reg_w_t;

struct scc_reg {
    /* 0x0*/
    struct {
           uint32_t RSVD_7_0                : 8;  /* [7:0]          r          */
           uint32_t MINOR                   : 8;  /* [15:8]         r          */
           uint32_t MAJOR                   : 8;  /* [23:16]        r          */
           uint32_t RSVD_31_24              : 8;  /* [31:24]        r          */
    } SCC_VERID;

    /* 0x4*/
    struct {
           uint32_t CLKSPRES                : 5;  /* [4:0]          r          */
           uint32_t RSVD_27_5               :23;  /* [27:5]         r          */
           uint32_t DIVPRES                 : 3;  /* [30:28]        r          */
           uint32_t RSVD_31                 : 1;  /* [31]           r          */
    } SCC_PARAM;

    /* 0x8*/
    struct {
           uint32_t DIVSLOW                 : 4;  /* [3:0]          r          */
           uint32_t DIVBUS                  : 4;  /* [7:4]          r          */
           uint32_t DIVCORE                 : 4;  /* [11:8]         r          */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        r          */
           uint32_t SCS                     : 3;  /* [18:16]        r          */
           uint32_t RSVD_31_19              :13;  /* [31:19]        r          */
    } SCC_CST;

    /* 0xC*/
    struct {
           uint32_t DIVSLOW                 : 4;  /* [3:0]          r/w        */
           uint32_t DIVBUS                  : 4;  /* [7:4]          r/w        */
           uint32_t DIVCORE                 : 4;  /* [11:8]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        r          */
           uint32_t SCS                     : 3;  /* [18:16]        r/w        */
           uint32_t RSVD_30_19              :12;  /* [30:19]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } SCC_CFG;

    /* 0x10*/
    struct {
           uint32_t RSVD_15_0               :16;  /* [15:0]         r          */
           uint32_t CLKOUTSEL               : 4;  /* [19:16]        r/w        */
           uint32_t RSVD_31_20              :12;  /* [31:20]                   */
    } SCC_CLKOUTCFG;

    /* 0x14*/
    struct {
           uint32_t OSCEN                   : 1;  /* [0]            r/w        */
           uint32_t OSCSTOPEN               : 1;  /* [1]            r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          r          */
           uint32_t OSCCMIE                 : 1;  /* [4]            r/w        */
           uint32_t RSVD_8_5                : 4;  /* [8:5]          r          */
           uint32_t OSCCME                  : 1;  /* [9]            r/w        */
           uint32_t OSCCMRE                 : 1;  /* [10]           r/w        */
           uint32_t RSVD_15_11              : 5;  /* [15:11]        r          */
           uint32_t OSCRDY                  : 1;  /* [16]           r          */
           uint32_t OSCSELD                 : 1;  /* [17]           r          */
           uint32_t OSCLOC                  : 1;  /* [18]           r/w        */
           uint32_t RSVD_30_19              :12;  /* [30:19]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } SCC_OSCCS;

    /* 0x18*/
    struct {
           uint32_t EXCLKS                  : 1;  /* [0]            r/w        */
           uint32_t OLMEN                   : 1;  /* [1]            r/w        */
           uint32_t HFREQ                   : 1;  /* [2]            r/w        */
           uint32_t RSVD_7_3                : 5;  /* [7:3]          r          */
           uint32_t RSVD_9_8                : 2;  /* [9:8]          r/w        */
           uint32_t RSVD_31_10              :22;  /* [31:10]        r          */
    } SCC_OSCCFG;

    /* 0x1C*/
    struct {
           uint32_t FIRCEN                  : 1;  /* [0]            r/w        */
           uint32_t FIRCSTOPEN              : 1;  /* [1]            r/w        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]          r          */
           uint32_t FIRCCMIE                : 1;  /* [4]            r/w        */
           uint32_t RSVD_8_5                : 4;  /* [8:5]          r          */
           uint32_t FIRCCME                 : 1;  /* [9]            r/w        */
           uint32_t FIRCCMRE                : 1;  /* [10]           r/w        */
           uint32_t RSVD_11                 : 1;  /* [11]           r          */
           uint32_t RSVD_12                 : 1;  /* [12]           r/w        */
           uint32_t RSVD_15_13              : 3;  /* [15:13]        r          */
           uint32_t FIRCRDY                 : 1;  /* [16]           r          */
           uint32_t FIRCSELD                : 1;  /* [17]           r          */
           uint32_t FIRCLOC                 : 1;  /* [18]           r/w        */
           uint32_t RSVD_30_19              :12;  /* [30:19]        r          */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } SCC_FIRCCS;

    /* 0x20*/
    struct {
           uint32_t RSVD_1_0                : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_31_2               :30;  /* [31:2]         r          */
    } SCC_FIRCCFG;

    /* 0x24*/
    struct {
           uint32_t RSVD_5_0                : 6;  /* [5:0]          r/w        */
           uint32_t RSVD_31_6               :26;  /* [31:6]         r          */
    } SCC_FIRCTRIM;

};    /*scc_reg*/

struct scc_reg_w {
    /* 0x0*/
    uint32_t SCC_VERID;
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
    /* 0x20*/
    uint32_t SCC_FIRCCFG;
    /* 0x24*/
    uint32_t SCC_FIRCTRIM;
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
           uint32_t SWTRIG                  : 4;  /* [3:0]          r/w        */
           uint32_t RSVD_31_4               :28;  /* [31:4]         ro         */
    } SCM_MISCCTL;

    /* 0x08*/
    struct {
           uint32_t TIM0_CLK_SEL            : 2;  /* [1:0]          r/w        */
           uint32_t RSVD_7_2                : 6;  /* [7:2]          ro         */
           uint32_t TIM1_CLK_SEL            : 2;  /* [9:8]          r/w        */
           uint32_t RSVD_15_10              : 6;  /* [15:10]        ro         */
           uint32_t TIM2_CLK_SEL            : 2;  /* [17:16]        r/w        */
           uint32_t RSVD_31_18              :14;  /* [31:18]        ro         */
    } SCM_TIMOPT;

    /* 0x0C*/
    struct {
           uint32_t SRAM0_ECCR_DIS          : 1;  /* [0]            r/w        */
           uint32_t SRAM0_ECCW_DIS          : 1;  /* [1]            r/w        */
           uint32_t SRAM0_ECCSB_DIS         : 1;  /* [2]            r/w        */
           uint32_t SRAM0_ECCMB_DIS         : 1;  /* [3]            r/w        */
           uint32_t RSVD_7_4                : 4;  /* [7:4]          ro         */
           uint32_t SRAM1_ECCR_DIS          : 1;  /* [8]            r/w        */
           uint32_t SRAM1_ECCW_DIS          : 1;  /* [9]            r/w        */
           uint32_t SRAM1_ECCSB_DIS         : 1;  /* [10]           r/w        */
           uint32_t SRAM1_ECCMB_DIS         : 1;  /* [11]           r/w        */
           uint32_t RSVD_31_12              :20;  /* [31:12]        ro         */
    } SCM_ECCOPT;

    /* 0x10*/
    struct {
           uint32_t EFPROT                  : 4;  /* [3:0]          ro         */
           uint32_t EFSIZE                  : 3;  /* [6:4]          ro         */
           uint32_t EFW                     : 1;  /* [7]            ro         */
           uint32_t EFMST                   : 4;  /* [11:8]         ro         */
           uint32_t RSVD_28_12              :17;  /* [28:12]        ro         */
           uint32_t SBERR                   : 1;  /* [29]           w1c        */
           uint32_t MBERR                   : 1;  /* [30]           w1c        */
           uint32_t OVERRUN                 : 1;  /* [31]           w1c        */
    } SCM_ECC0ST;

    /* 0x14*/
    struct {
           uint32_t EFADDR                  :32;  /* [31:0]         ro         */
    } SCM_ECC0FADDR;

    /* 0x18*/
    struct {
           uint32_t EFDATA                  :32;  /* [31:0]         ro         */
    } SCM_ECC0FDATA;

    /* 0x1C*/
    struct {
           uint32_t EFPROT                  : 4;  /* [3:0]          ro         */
           uint32_t EFSIZE                  : 3;  /* [6:4]          ro         */
           uint32_t EFW                     : 1;  /* [7]            ro         */
           uint32_t EFMST                   : 4;  /* [11:8]         ro         */
           uint32_t RSVD_28_12              :17;  /* [28:12]        ro         */
           uint32_t SBERR                   : 1;  /* [29]           w1c        */
           uint32_t MBERR                   : 1;  /* [30]           w1c        */
           uint32_t OVERRUN                 : 1;  /* [31]           w1c        */
    } SCM_ECC1ST;

    /* 0x20*/
    struct {
           uint32_t EFADDR                  :32;  /* [31:0]         ro         */
    } SCM_ECC1FADDR;

    /* 0x24*/
    struct {
           uint32_t EFDATA                  :32;  /* [31:0]         ro         */
    } SCM_ECC1FDATA;

    uint8_t zResverd0x028[216];   /*pad 0x028 - 0FF*/

    /* 0x100*/
    struct {
           uint32_t RSVD_31_0               :32;  /* [31:0]         ro         */
    } SCM_CHIPOPT;

    /* 0x104*/
    struct {
           uint32_t RSVD_23_0               :24;  /* [23:0]         ro         */
           uint32_t PFSIZE                  : 4;  /* [27:24]        ro         */
           uint32_t DFSIZE                  : 4;  /* [31:28]        ro         */
    } SCM_FLSCFG;

    /* 0x108*/
    struct {
           uint32_t RSVD_27_0               :28;  /* [27:0]         ro         */
           uint32_t RAMSIZE                 : 4;  /* [31:28]        ro         */
    } SCM_RAMCFG;

    uint8_t zResverd0x010C[16];   /*pad 0x010C - 011B*/

    /* 0x11C*/
    struct {
           uint32_t MEMSIZE_ID              : 4;  /* [3:0]        ro         */
           uint32_t SERIES_ID               : 3;  /* [6:4]        ro         */
           uint32_t SUBFAMILY_ID            : 5;  /* [11:7]       ro         */
           uint32_t FAMILY_ID               : 4;  /* [15:12]      ro         */
           uint32_t REV_ID                  : 4;  /* [19:16]      ro         */
           uint32_t FEATURE_ID              : 7;  /* [26:20]      ro         */
           uint32_t PACKAGE_ID              : 5;  /* [31:27]      ro         */
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
    uint32_t SCM_MISCCTL;
    /* 0x08*/
    uint32_t SCM_TIMOPT;
    /* 0x0C*/
    uint32_t SCM_ECCOPT;
    /* 0x10*/
    uint32_t SCM_ECC0ST;
    /* 0x14*/
    uint32_t SCM_ECC0FADDR;
    /* 0x18*/
    uint32_t SCM_ECC0FDATA;
    /* 0x1C*/
    uint32_t SCM_ECC1ST;
    /* 0x20*/
    uint32_t SCM_ECC1FADDR;
    /* 0x24*/
    uint32_t SCM_ECC1FDATA;
    uint8_t zResverd0x028[216];   /*pad 0x028 - 0FF*/

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

struct spi_reg {
    /* 0x0*/
    struct {
           uint32_t DFS                     : 4;  /* [3:0]          r/w        */
           uint32_t RSVD_5_4                : 2;  /* [5:4]          ro         */
           uint32_t SCPH                    : 1;  /* [6]            r/w        */
           uint32_t SCPOL                   : 1;  /* [7]            r/w        */
           uint32_t TMOD                    : 2;  /* [9:8]          r/w        */
           uint32_t RSVD_10                 : 1;  /* [10]           r/w        */
           uint32_t RSVD_11                 : 1;  /* [11]           r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        r/w        */
           uint32_t DFS_32                  : 5;  /* [20:16]        r/w        */
           uint32_t MST_MODE                : 1;  /* [21]           r/w        */
           uint32_t RSVD_22                 : 1;  /* [22]           r/w        */
           uint32_t RSVD_23                 : 1;  /* [23]           r/w        */
           uint32_t RSVD_24                 : 1;  /* [24]           r/w        */
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

    /* 0x44*/
    struct {
           uint32_t RSVD_31_0               :32;  /* [31:0]         ro         */
    } SPI_IDR;

    /* 0x48*/
    struct {
           uint32_t RSVD_31_0               :32;  /* [31:0]         ro         */
    } SPI_VIDR;

    uint8_t zResverd0x04C[20];   /*pad 0x04C - 05F*/

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
    /* 0x44*/
    uint32_t SPI_IDR;
    /* 0x48*/
    uint32_t SPI_VIDR;
    uint8_t zResverd0x04C[20];   /*pad 0x04C - 05F*/

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
    struct {
           uint32_t FEATURE                 :16;  /* [15:0]         ro         */
           uint32_t MINOR                   : 8;  /* [23:16]        ro         */
           uint32_t MAJOR                   : 8;  /* [31:24]        ro         */
    } SRMC_VERID;

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
           uint32_t EMDM_AP                 : 1;  /* [11]           ro         */
           uint32_t RSVD_12                 : 1;  /* [12]           ro         */
           uint32_t ESACKERR                : 1;  /* [13]           ro         */
           uint32_t RSVD_15_14              : 2;  /* [15:14]        ro         */
           uint32_t EPDOWN                  : 1;  /* [16]           ro         */
           uint32_t RSVD_31_17              :15;  /* [31:17]        ro         */
    } SRMC_PARAM;

    /* 0x08*/
    struct {
           uint32_t WAKEUP                  : 1;  /* [0]            ro         */
           uint32_t LVD                     : 1;  /* [1]            w1c        */
           uint32_t LOC                     : 1;  /* [2]            w1c        */
           uint32_t RSVD_4_3                : 2;  /* [4:3]          ro         */
           uint32_t WDOG                    : 1;  /* [5]            w1c        */
           uint32_t PIN                     : 1;  /* [6]            w1c        */
           uint32_t POR                     : 1;  /* [7]            w1c        */
           uint32_t RSVD_8                  : 1;  /* [8]            ro         */
           uint32_t LOCKUP                  : 1;  /* [9]            w1c        */
           uint32_t SW                      : 1;  /* [10]           w1c        */
           uint32_t MDM_AP                  : 1;  /* [11]           w1c        */
           uint32_t RSVD_14_12              : 3;  /* [14:12]        ro         */
           uint32_t SACKERR                 : 1;  /* [15]           w1c        */
           uint32_t RSVD_31_16              :16;  /* [31:16]        ro         */
    } SRMC_SRS;

    /* 0x0C*/
    struct {
           uint32_t RSTFLTSRW               : 2;  /* [1:0]          r/w        */
           uint32_t RSTFLTSS                : 1;  /* [2]            r/w        */
           uint32_t RSVD_7_3                : 5;  /* [7:3]          r/w        */
           uint32_t RSTFLTSEL               : 5;  /* [12:8]         r/w        */
           uint32_t RSVD_30_13              :18;  /* [30:13]        r          */
           uint32_t LOCKUP_RST_EN           : 1;  /* [31]           r/w        */
    } SRMC_CTRL;

    /* 0x10*/
    struct {
           uint32_t RSVD_31_0               :32;  /* [31:0]         ro         */
    } SRMC_MR;

    /* 0x14*/
    struct {
           uint32_t RSVD_31_0               :32;  /* [31:0]         ro         */
    } SRMC_FM;

    /* 0x18*/
    struct {
           uint32_t WAKEUP                  : 1;  /* [0]            ro         */
           uint32_t SLVD                    : 1;  /* [1]            ro         */
           uint32_t SLOC                    : 1;  /* [2]            ro         */
           uint32_t RSVD_4_3                : 2;  /* [4:3]          ro         */
           uint32_t SWDOG                   : 1;  /* [5]            ro         */
           uint32_t SPIN                    : 1;  /* [6]            ro         */
           uint32_t SPOR                    : 1;  /* [7]            ro         */
           uint32_t RSVD_8                  : 1;  /* [8]            ro         */
           uint32_t SLOCKUP                 : 1;  /* [9]            ro         */
           uint32_t SSW                     : 1;  /* [10]           ro         */
           uint32_t SMDM_AP                 : 1;  /* [11]           ro         */
           uint32_t RSVD_14_12              : 3;  /* [14:12]        ro         */
           uint32_t SSACKERR                : 1;  /* [15]           ro         */
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
           uint32_t RSVD_14_11              : 4;  /* [14:11]        ro         */
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
           uint32_t WUPSRC_EN0              : 3;  /* [2:0]          r/w        */
           uint32_t RSVD_3                  : 1;  /* [3]            ro         */
           uint32_t WUPSRC_EN1              : 8;  /* [11:4]         r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32_t WUPSRC_PL0              : 3;  /* [18:16]        r/w        */
           uint32_t RSVD_19                 : 1;  /* [19]           ro         */
           uint32_t WUPSRC_PL1              : 8;  /* [27:20]        r/w        */
           uint32_t RSVD_31_28              : 4;  /* [31:28]        ro         */
    } SRMC_DSMWUPC;

    /* 0x30*/
    struct {
           uint32_t WUPS0                   : 3;  /* [2:0]          w1c        */
           uint32_t RSVD_3                  : 1;  /* [3]            ro         */
           uint32_t WUPS1                   : 8;  /* [11:4]         w1c        */
           uint32_t RSVD_31_28              : 4;  /* [31:28]        ro         */
    } SRMC_DSMWUPS;

};    /*srmc_reg*/

struct srmc_reg_w {
    /* 0x00*/
    uint32_t SRMC_VERID;
    /* 0x04*/
    uint32_t SRMC_PARAM;
    /* 0x08*/
    uint32_t SRMC_SRS;
    /* 0x0C*/
    uint32_t SRMC_CTRL;
    /* 0x10*/
    uint32_t SRMC_MR;
    /* 0x14*/
    uint32_t SRMC_FM;
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
    uint32_t SRMC_DSMWUPC;
    /* 0x30*/
    uint32_t SRMC_DSMWUPS;
};    /*srmc_reg*/

typedef volatile struct srmc_reg srmc_reg_t;
typedef volatile struct srmc_reg_w srmc_reg_w_t;

struct stim_reg {
    /* 0x00*/
    struct {
           uint32_t VERID                   :32;  /* [31:0]         ro        */
    } STIM_VERID;

    /* 0x04*/
    struct {
           uint32_t CNT                     :32;  /* [31:0]         ro        */
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
           uint32_t RSVD_31_16              :16;  /* [31:16]                   */
    } STIM_SCn[4];

};    /*stim_reg*/

struct stim_reg_w {
    /* 0x00*/
    uint32_t STIM_VERID;
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
    struct {
       uint32_t MINOR                   : 4;  /* [3:0]          r          */
       uint32_t MAJOR                   : 4;  /* [7:4]          r          */
       uint32_t RSVD_31_8               :24;  /* [31:8]         r          */
    } TDG_VERID;

    /* 0x4*/
    struct {
       uint32_t DOPNUM                  : 4;  /* [3:0]          r          */
       uint32_t CHNUM                   : 4;  /* [7:4]          r          */
       uint32_t RSVD_31_8               :24;  /* [31:8]         r          */
    } TDG_PARAM;

    /* 0x8*/
    struct {
       uint32_t TDGEN                   : 1;  /* [0]            r/w        */
       uint32_t RSVD_3_1                : 3;  /* [3:1]                     */
       uint32_t TRIGS                   : 1;  /* [4]            r/w        */
       uint32_t CNTMD                   : 1;  /* [5]            r/w        */
       uint32_t CLRMD                   : 1;  /* [6]            r/w        */
       uint32_t RSVD_7                  : 1;  /* [7]            r          */
       uint32_t PRES                    : 3;  /* [10:8]         r/w        */
       uint32_t RSVD_15_11              : 5;  /* [15:11]        r          */
       uint32_t CFGUP                   : 1;  /* [16]           r/w        */
       uint32_t SWTRG                   : 1;  /* [17]           r/w        */
       uint32_t RSVD_19_18              : 2;  /* [19:18]                   */
       uint32_t UPMD                    : 2;  /* [21:20]        r          */
       uint32_t RSVD_31_22              :10;  /* [31:22]        r          */
    } TDG_CTRL1;

    /* 0xC*/
    struct {
       uint32_t CDO0IE                  : 1;  /* [0]            r/w        */
       uint32_t CDO1IE                  : 1;  /* [1]            r/w        */
       uint32_t CDO2IE                  : 1;  /* [2]            r/w        */
       uint32_t CDO3IE                  : 1;  /* [3]            r/w        */
       uint32_t CDO4IE                  : 1;  /* [4]            r/w        */
       uint32_t CDO5IE                  : 1;  /* [5]            r/w        */
       uint32_t RSVD_7_6                : 2;  /* [7:6]          r          */
       uint32_t ERRIE                   : 1;  /* [8]            r/w        */
       uint32_t RSVD_15_9               : 7;  /* [15:9]         r          */
       uint32_t CH0E                    : 1;  /* [16]           r/w        */
       uint32_t CH1E                    : 1;  /* [17]           r/w        */
       uint32_t CH2E                    : 1;  /* [18]           r/w        */
       uint32_t CH3E                    : 1;  /* [19]           r/w        */
       uint32_t CH4E                    : 1;  /* [20]           r/w        */
       uint32_t CH5E                    : 1;  /* [21]           r/w        */
       uint32_t RSVD_31_22              :10;  /* [31:22]        r          */
    } TDG_CTRL2;

    /* 0x10*/
    struct {
       uint32_t CDO0IF                  : 1;  /* [0]            r/w        */
       uint32_t CDO1IF                  : 1;  /* [1]            r/w        */
       uint32_t CDO2IF                  : 1;  /* [2]            r/w        */
       uint32_t CDO3IF                  : 1;  /* [3]            r/w        */
       uint32_t CDO4IF                  : 1;  /* [4]            r/w        */
       uint32_t CDO5IF                  : 1;  /* [5]            r/w        */
       uint32_t RSVD_7_6                : 2;  /* [7:6]                     */
       uint32_t ERRIF                   : 1;  /* [8]            r/w        */
       uint32_t RSVD_31_9               :23;  /* [31:9]                    */
    } TDG_STAT;

    /* 0x14*/
    struct {
       uint32_t MOD                     :16;  /* [15:0]         r/w        */
       uint32_t RSVD_31_16              :16;  /* [31:16]        r          */
    } TDG_MOD;

    /* 0x18*/
    struct {
       uint32_t CNT                     :16;  /* [15:0]         r          */
       uint32_t RSVD_31_16              :16;  /* [31:16]        r          */
    } TDG_CNT;

    /* 0x1C*/
    struct {
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
       uint32_t RSVD_31_16              :16;  /* [31:16]                   */
    } TDG_CHCTRL;

    /* 0x20 - 0x3F*/
    struct {
       uint32_t DO0OFS                  :16;  /* [15:0]         r/w        */
       uint32_t RSVD_31_16              :16;  /* [31:16]        r          */
    } TDG_CHDOOFS[8];

    /* 0x40*/
    struct {
       uint32_t CDOINTDLY               :10;  /* [9:0]          r/w        */
       uint32_t RSVD_15_10              : 6;  /* [15:10]        r          */
       uint32_t LDCO                    : 1;  /* [16]           r/w        */
       uint32_t RSVD_31_17              :15;  /* [31:17]        r          */
    } TDG_CHDOCINTDLY;

    } TDG_CHCFG[6];
};    /*tdg_reg*/

struct tdg_reg_w {
    /* 0x0*/
    uint32_t TDG_VERID;
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
    /* 0x1C */
    uint32_t TDG_CHCTRL;
    /* 0x20 - 0x3F*/
    uint32_t TDG_CHDOOFS[8];
    /* 0x40*/
    uint32_t TDG_CHDOCINTDLY;  
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
           uint32_t RSVD_31_7               :25;  /* [31:7]                    */
    } TIM_TIMEBASE;

    /* 0x04*/
    struct {
           uint32_t CNT                     :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]                   */
    } TIM_CNT;

    /* 0x08*/
    struct {
           uint32_t CNTINIT                 :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]                   */
    } TIM_CNTINIT;

    /* 0x0C*/
    struct {
           uint32_t MOD                     :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]                   */
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
           uint32_t INIT                    : 1;  /* [11]           w/o        */
           uint32_t RSVD_31_12              :20;  /* [31:12]                   */
    } TIM_GLBCR;

    /* 0x14*/
    struct {
           uint32_t CH0F                    : 1;  /* [0]            r/o        */
           uint32_t CH1F                    : 1;  /* [1]            r/o        */
           uint32_t CH2F                    : 1;  /* [2]            r/o        */
           uint32_t CH3F                    : 1;  /* [3]            r/o        */
           uint32_t CH4F                    : 1;  /* [4]            r/o        */
           uint32_t CH5F                    : 1;  /* [5]            r/o        */
           uint32_t CH6F                    : 1;  /* [6]            r/o        */
           uint32_t CH7F                    : 1;  /* [7]            r/o        */
           uint32_t RLDF                    : 1;  /* [8]            r/o        */
           uint32_t TOF                     : 1;  /* [9]            r/o        */
           uint32_t WPDIS                   : 1;  /* [10]           r/w        */
           uint32_t RSVD_31_11              :21;  /* [31:11]                   */
    } TIM_GLBSR;

    /* 0x18*/
    struct {
           uint32_t ELS                     : 2;  /* [1:0]          r/w        */
           uint32_t CMS                     : 2;  /* [3:2]          r/w        */
           uint32_t CHIE                    : 1;  /* [4]            r/w        */
           uint32_t CHF                     : 1;  /* [5]            r/o        */
           uint32_t DMAEN                   : 1;  /* [6]            r/w        */
           uint32_t ICRST                   : 1;  /* [7]            r/w        */
           uint32_t RSVD_31_8               :24;  /* [31:8]                    */
    } TIM_CMCn[8];

    /* 0x38*/
    struct {
           uint32_t CCV                     :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]                   */
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
           uint32_t TRIGF                   : 1;  /* [25]           r/o        */
           uint32_t RSVD_31_26              : 6;  /* [31:26]                   */
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
           uint32_t RSVD_31_16              :16;  /* [31:16]                   */
    } TIM_OUTSWCR;

    /* 0x60*/
    struct {
           uint32_t FCTLEN0                 : 1;  /* [0]            r/w        */
           uint32_t DTEN0                   : 1;  /* [1]            r/w        */
           uint32_t COMB0                   : 1;  /* [2]            r/w        */
           uint32_t SYNCEN0                 : 1;  /* [3]            r/w        */
           uint32_t DECAPEN0                : 1;  /* [4]            r/w        */
           uint32_t DECAP0                  : 1;  /* [5]            r/w        */
           uint32_t RSVD_7_6                : 2;  /* [7:6]                     */
           uint32_t FCTLEN1                 : 1;  /* [8]            r/w        */
           uint32_t DTEN1                   : 1;  /* [9]            r/w        */
           uint32_t COMB1                   : 1;  /* [10]           r/w        */
           uint32_t SYNCEN1                 : 1;  /* [11]           r/w        */
           uint32_t DECAPEN1                : 1;  /* [12]           r/w        */
           uint32_t DECAP1                  : 1;  /* [13]           r/w        */
           uint32_t RSVD_15_14              : 2;  /* [15:14]                   */
           uint32_t FCTLEN2                 : 1;  /* [16]           r/w        */
           uint32_t DTEN2                   : 1;  /* [17]           r/w        */
           uint32_t COMB2                   : 1;  /* [18]           r/w        */
           uint32_t SYNCEN2                 : 1;  /* [19]           r/w        */
           uint32_t DECAPEN2                : 1;  /* [20]           r/w        */
           uint32_t DECAP2                  : 1;  /* [21]           r/w        */
           uint32_t RSVD_23_22              : 2;  /* [23:22]                   */
           uint32_t FCTLEN3                 : 1;  /* [24]           r/w        */
           uint32_t DTEN3                   : 1;  /* [25]           r/w        */
           uint32_t COMB3                   : 1;  /* [26]           r/w        */
           uint32_t SYNCEN3                 : 1;  /* [27]           r/w        */
           uint32_t DECAPEN3                : 1;  /* [28]           r/w        */
           uint32_t DECAP3                  : 1;  /* [29]           r/w        */
           uint32_t RSVD_31_30              : 2;  /* [31:30]                   */
    } TIM_PCR;

    /* 0x64*/
    struct {
           uint32_t FILVAL0                 : 4;  /* [3:0]          r/w        */
           uint32_t FILVAL1                 : 4;  /* [7:4]          r/w        */
           uint32_t FILVAL2                 : 4;  /* [11:8]         r/w        */
           uint32_t FILVAL3                 : 4;  /* [15:12]        r/w        */
           uint32_t DTPS                    : 2;  /* [17:16]        r/w        */
           uint32_t DTVAL                   : 6;  /* [23:18]        r/w        */
           uint32_t RSVD_31_24              : 8;  /* [31:24]                   */
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
           uint32_t RSVD_10_9               : 2;  /* [10:9]                    */
           uint32_t FIFVAL                  : 4;  /* [14:11]        r/w        */
           uint32_t FSTATE                  : 1;  /* [15]           r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]                   */
    } TIM_FLTCR;

    /* 0x6C*/
    struct {
           uint32_t FAULTF0                 : 1;  /* [0]            r/o        */
           uint32_t FAULTF1                 : 1;  /* [1]            r/o        */
           uint32_t RSVD_3_2                : 2;  /* [3:2]                     */
           uint32_t FAULTF                  : 1;  /* [4]            r/o        */
           uint32_t FAULTIN                 : 1;  /* [5]            r/o        */
           uint32_t WPEN                    : 1;  /* [6]            r/w        */
           uint32_t RSVD_31_7               :25;  /* [31:7]                    */
    } TIM_FLTSR;

    /* 0x70*/
    struct {
           uint32_t SWTRIG                  : 1;  /* [0]            r/w        */
           uint32_t RSVD_7_1                : 7;  /* [7:1]                     */
           uint32_t SYNCINIT                : 1;  /* [8]            r/w        */
           uint32_t SYNCOSWC                : 1;  /* [9]            r/w        */
           uint32_t RSVD_17_10              : 8;  /* [17:10]                   */
           uint32_t SWWRBUF                 : 1;  /* [18]           r/w        */
           uint32_t SWRSTCNT                : 1;  /* [19]           r/w        */
           uint32_t RSVD_31_20              :12;  /* [31:20]                   */
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
           uint32_t RSVD_10_9               : 2;  /* [10:9]                    */
           uint32_t HCSEL                   : 1;  /* [11]           r/w        */
           uint32_t RSVD_15_12              : 4;  /* [15:12]                   */
           uint32_t LDFREQ                  : 5;  /* [20:16]        r/w        */
           uint32_t RSVD_31_21              :11;  /* [31:21]                   */
    } TIM_RELOAD;

    /* 0x78*/
    struct {
           uint32_t HCV                     :16;  /* [15:0]         r/w        */
           uint32_t RSVD_31_16              :16;  /* [31:16]                   */
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
           uint32_t SEL                     : 6;  /* [5:0]          r/w        */
           uint32_t RSVD_6                  : 1;  /* [6]            ro         */
           uint32_t EN                      : 1;  /* [7]            r/w        */
           uint32_t RSVD_30_8               :23;  /* [30:8]         ro         */
           uint32_t LOCK                    : 1;  /* [31]           r/w        */
    } TMU_CFGn[40];

};    /*tmu_reg*/

struct tmu_reg_w {
    /* 0x0*/
    uint32_t TMU_CFGn[40];
};    /*tmu_reg*/

typedef volatile struct tmu_reg tmu_reg_t;
typedef volatile struct tmu_reg_w tmu_reg_w_t;

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
           uint32_t RSVD_31_8               :24;  /* [31:8]                    */
        } UART_DLL;
    } UART_RBR_THR_DLL;

    /* 0x4*/
    union {
        struct {
           uint32_t DL_H                    : 8;  /* [7:0]          r/w        */
           uint32_t RSVD_31_8               :24;  /* [31:8]                    */
        } UART_DLH;
        struct {
           uint32_t ERBFI                   : 1;  /* [0]            r/w        */
           uint32_t ETBEI                   : 1;  /* [1]            r/w        */
           uint32_t ELSI                    : 1;  /* [2]            r/w        */
           uint32_t RSVD_6_3                : 4;  /* [6:3]          r/w        */
           uint32_t PTIME                   : 1;  /* [7]            r/w        */
           uint32_t HEADER_DONE_INT_EN      : 1;  /* [8]            r/w        */
           uint32_t RSP_DONE_INT_EN         : 1;  /* [9]            r/w        */
           uint32_t ASYNC_INT_EN            : 1;  /* [10]           r/w        */
           uint32_t RSVD_31_11              :21;  /* [31:11]                   */
        } UART_IER;
    } UART_DLH_IER;

    /* 0x8*/
    union {
        struct {
           uint32_t IID                     : 4;  /* [3:0]          ro         */
           uint32_t RSVD_5_4                : 2;  /* [5:4]                     */
           uint32_t FIFOSE                  : 2;  /* [7:6]          ro         */
           uint32_t RSVD_31_8               :24;  /* [31:8]                    */
        } UART_IIR;
        struct {
           uint32_t FIFOE                   : 1;  /* [0]            wo         */
           uint32_t RFIFOR                  : 1;  /* [1]            wo         */
           uint32_t XFIFOR                  : 1;  /* [2]            wo         */
           uint32_t RSVD_3                  : 1;  /* [3]            wo         */
           uint32_t TET                     : 2;  /* [5:4]          wo         */
           uint32_t RCVR                    : 2;  /* [7:6]          wo         */
           uint32_t RSVD_31_8               :24;  /* [31:8]                    */
        } UART_FCR;
    } UART_IIR_FCR;

    /* 0xC*/
    struct {
           uint32_t DLS                     : 2;  /* [1:0]          r/w        */
           uint32_t STOP                    : 1;  /* [2]            r/w        */
           uint32_t PEN                     : 1;  /* [3 ]            r/w        */
           uint32_t EPS                     : 1;  /* [4]            r/w        */
           uint32_t STP                     : 1;  /* [5 ]            r/w        */
           uint32_t BC                      : 1;  /* [6]            r/w        */
           uint32_t DLAB                    : 1;  /* [7]            r/w        */
           uint32_t LBKEN                   : 1;  /* [8]            r/w        */
           uint32_t LBKM                    : 5;  /* [13:9]         r/w        */
           uint32_t IDLE_DET_LENGTH         : 3;  /* [16:14]        r/w        */
           uint32_t IDLE_DET_EN             : 1;  /* [17]           r/w        */
           uint32_t AUTO_SYNC_EN            : 1;  /* [18]           r/w        */
           uint32_t DEBUG_EN                : 1;  /* [19]           r/w        */
           uint32_t RSVD_31_20              :12;  /* [31:20]                   */
    } UART_LCR;

    /* 0x10*/
    struct {
           uint32_t RSVD_0                  : 1;  /* [0]                       */
           uint32_t RTS                     : 1;  /* [1]            r/w        */
           uint32_t RSVD_2                  : 1;  /* [2]                       */
           uint32_t RSVD_3                  : 1;  /* [3 ]                       */
           uint32_t LB                      : 1;  /* [4]            r/w        */
           uint32_t AFCE                    : 1;  /* [5 ]            r/w        */
           uint32_t RSVD_6                  : 1;  /* [6]            r/w        */
           uint32_t RSVD_31_7               :25;  /* [31:7]                    */
    } UART_AFCR;

    /* 0x14*/
    struct {
           uint32_t DR                      : 1;  /* [0]            ro         */
           uint32_t OE                      : 1;  /* [1]            ro         */
           uint32_t PE                      : 1;  /* [2]            ro         */
           uint32_t FE                      : 1;  /* [3 ]            ro         */
           uint32_t BI                      : 1;  /* [4]            ro         */
           uint32_t THRE                    : 1;  /* [5 ]            ro         */
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
           uint32_t RSVD_31_16              :16;  /* [31:16]                   */
    } UART_LSR;

    uint8_t zResverd0x018[100];   /*pad 0x018 - 07B*/

    /* 0x7C*/
    struct {
           uint32_t BUSY                    : 1;  /* [0]            ro         */
           uint32_t RSVD_4_1                : 4;  /* [4:1]                     */
           uint32_t RSVD_31_5               :27;  /* [31:5]                    */
    } UART_USR;

    uint8_t zResverd0x080[40];   /*pad 0x080 - 0A7*/

    /* 0xA8*/
    struct {
           uint32_t RSVD_0                  : 1;  /* [0]            wo         */
           uint32_t RSVD_31_1               :31;  /* [31:1]                    */
    } UART_DMA_SA;

    uint8_t zResverd0x0AC[20];   /*pad 0x0AC - 0BF*/

    /* 0xC0*/
    struct {
           uint32_t FD                      : 4;  /* [3:0]          r/w        */
           uint32_t RSVD_31_4               :28;  /* [31:4]                    */
    } UART_FD;

    /* 0xC4*/
    struct {
           uint32_t RAR                     : 8;  /* [7:0]          r/w        */
           uint32_t RSVD_31_8               :24;  /* [31:8]                    */
    } UART_RAR;

    /* 0xC8*/
    struct {
           uint32_t TAR                     : 8;  /* [7:0]          r/w        */
           uint32_t RSVD_31_8               :24;  /* [31:8]                    */
    } UART_TAR;

    /* 0xCC*/
    struct {
           uint32_t DLS_E                   : 1;  /* [0]            r/w        */
           uint32_t ADDR_MATCH              : 1;  /* [1]            r/w        */
           uint32_t SEND_ADDR               : 1;  /* [2]            r/w        */
           uint32_t TRANSMIST_MODE          : 1;  /* [3]            r/w        */
           uint32_t RSVD_31_4               :28;  /* [31:4]                    */
    } UART_LCR_EXT;

    uint8_t zResverd0x0D0[48];   /*pad 0x0D0 - 0FF*/

    /* 0x100*/
    struct {
           uint32_t LIN_MODE                : 1;  /* [0]            r/w        */
           uint32_t MASTER_MODE             : 1;  /* [1]            r/w        */
           uint32_t HEADER_OP_START         : 1;  /* [2]            r/w        */
           uint32_t RSP_OP_START            : 1;  /* [3 ]            r/w        */
           uint32_t RSP_DIR                 : 1;  /* [4]            r/w        */
           uint32_t RSVD_31_5               :27;  /* [31:5]                    */
    } UART_LIN_CTL;

    /* 0x104*/
    struct {
           uint32_t RSP_LENGTH              : 4;  /* [3:0]          r/w        */
           uint32_t RSVD_31_4               :28;  /* [31:4]                    */
    } UART_LIN_RSP_LENGTH;

    /* 0x108*/
    struct {
           uint32_t PID                     : 6;  /* [5:0]          r/w        */
           uint32_t RSVD_31_6               :26;  /* [31:6]                    */
    } UART_LIN_PID_VALUE;

    /* 0x10C*/
    struct {
           uint32_t CHECKSUM_TYPE           : 1;  /* [0]            r/w        */
           uint32_t RSVD_7_1                : 7;  /* [7:1]                     */
           uint32_t RSVD_31_8               :24;  /* [31:8]                    */
    } UART_LIN_CHECKSUM;

    /* 0x110*/
    struct {
           uint32_t LIN_DEL_LENGTH          : 3;  /* [2:0]          r/w        */
           uint32_t RSVD_31_3               :29;  /* [31:3]                    */
    } UART_LIN_DEL_LENGTH;

    uint8_t zResverd0x114[24];   /* pad 0x114 - 12B */ 

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
    uint8_t zResverd0x080[40];   /*pad 0x080 - 0A7*/

    /* 0xA8*/
    uint32_t UART_DMA_SA;
    uint8_t zResverd0x0AC[20];   /*pad 0x0AC - 0BF*/

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
    uint32_t UART_LIN_PID_VALUE;
    /* 0x10C*/
    uint32_t UART_LIN_CHECKSUM;
    /* 0x110*/
    uint32_t UART_LIN_DEL_LENGTH;
    
    uint8_t zResverd0x114[24];   /* pad 0x114 - 12B */ 
    
};    /*uart_reg*/

typedef volatile struct uart_reg uart_reg_t;
typedef volatile struct uart_reg_w uart_reg_w_t;

struct wdog_reg {
    /* 0x0*/
    struct {
           uint32_t MINOR                   : 4;  /* [3:0]          ro         */
           uint32_t MAJOR                   : 4;  /* [7:4]          ro         */
           uint32_t RSVD_31_8               :24;  /* [31:8]         ro         */
    } WDOG_VERID;

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
           uint32_t INTF                    : 1;  /* [26]           r/w        */
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
    uint32_t WDOG_VERID;
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
#endif /*Z20K114M_H*/
