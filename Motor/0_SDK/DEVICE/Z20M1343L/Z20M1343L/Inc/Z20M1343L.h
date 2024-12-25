/**************************************************************************************************/
/**
 * @file      : Z20M1343L.h
 * @brief     : Device header file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#ifndef Z20M1343L_H
#define Z20M1343L_H

#include <Platform_Types.h>

/**
 * @brief Peripheral Base Address
 */
#define FLASH_CODE_BASE_ADDR       ((uint32)0x00000000)            /*!< Code flash base address */
#define ROM_BASE_ADDR              ((uint32)0x01000000)            /*!< ROM base address */
#define SRAM_BASE_ADDR             ((uint32)0x20000000)            /*!< SRAM base address */
#define EEPROM_BASE_ADDR           ((uint32)0x20020000)            /*!< EEPROM base address */
#define EEPROM_SIZE                ((uint32)0x00000200)            /*!< EEPROM size */
#define PERIPHERAL_BASE_ADDR       ((uint32)0x40000000)            /*!< Peripheral area base address */
#define AIPS0_BASE_ADDR            ((uint32)0x40000000)            /*!< AIPS0 base address */

#define PRI_PERI_BUS_BASE_ADDR     ((uint32)0xE0000000)            /*!< private Peripheral base address */

#define DMA_BASE_ADDR              (PERIPHERAL_BASE_ADDR + 0x8000UL)        /*!< DMA controller base address */
#define GDU_BASE_ADDR              (PERIPHERAL_BASE_ADDR + 0x9000UL)        /*!< GDU controller base address */
#define FLASHC_BASE_ADDR           (PERIPHERAL_BASE_ADDR + 0x20000UL)       /*!< flash controller base address */
#define ADC_BASE_ADDR              (PERIPHERAL_BASE_ADDR + 0x26000UL)       /*!< ADC base address */
#define SPI_BASE_ADDR              (PERIPHERAL_BASE_ADDR + 0x2C000UL)       /*!< SPI base address */
#define MCPWM_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0x33000UL)       /*!< Motor Control PWM base address */
#define TDG_BASE_ADDR              (PERIPHERAL_BASE_ADDR + 0x35000UL)       /*!< TDG base address */
#define CTIMER_BASE_ADDR           (PERIPHERAL_BASE_ADDR + 0x38000UL)       /*!< TIM base address */
#define STIM_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x40000UL)       /*!< STIM base address */
#define CRC_BASE_ADDR              (PERIPHERAL_BASE_ADDR + 0x43000UL)       /*!< CRC base address */
#define SCM_BASE_ADDR              (PERIPHERAL_BASE_ADDR + 0x48000UL)       /*!< System Control base address */
#define PORTA_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0x4D000UL)       /*!< PORTA multiplexing base address */
#define WDOG_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x52000UL)       /*!< watchdog base address */
#define SCC_BASE_ADDR              (PERIPHERAL_BASE_ADDR + 0x64000UL)       /*!< System Clock Controller base address */
#define UART_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x6A000UL)       /*!< UART base address */
#define LINPHY_BASE_ADDR           (PERIPHERAL_BASE_ADDR + 0x6B000UL)       /*!< LIN PHY base address */
#define CMP_BASE_ADDR              (PERIPHERAL_BASE_ADDR + 0x73000UL)       /*!< Analog comparator base address */
#define CMU_BASE_ADDR              (PERIPHERAL_BASE_ADDR + 0x7C000UL)       /*!< CMU base address */
#define PMU_BASE_ADDR              (PERIPHERAL_BASE_ADDR + 0x7D000UL)       /*!< Power management Unit base address */
#define SRMC_BASE_ADDR             (PERIPHERAL_BASE_ADDR + 0x7E000UL)       /*!< system reset and mode controller base address */
#define GPIOA_BASE_ADDR            (PERIPHERAL_BASE_ADDR + 0xFF000UL)       /*!< GPIOA base address */
#define MATHACCEL_BASE_ADDR        (PERIPHERAL_BASE_ADDR + 0x100000UL)      /*!< MATH ACCEL base address */

/**
 * @brief IRQ Number Definition
 */
typedef enum
{
    /******  Cortex-M0+ Processor IRQ Numbers *******************************/
    NONMASKABLE_IRQn                = -14,  /*!< 2 Non Maskable Interrupt  */
    HARDFAULT_IRQn                  = -13,  /*!< 3 Hardfault Interrupt  */
    SVCALL_IRQn                     = -5,   /*!< 11 Cortex-M0+ SV Call Interrupt */
    PENDSV_IRQn                     = -2,   /*!< 14 Cortex-M0+ Pend SV Interrupt */
    SYSTICK_IRQn                    = -1,   /*!< 15 Cortex-M0+ System Tick Interrupt */

    /******  specific IRQ Numbers *************************************/
    STIM_IRQn                       = 0,    /*!< STIM Interrupt */
    MCPWM_IRQn                      = 1,    /*!< MCPWM Interrupt */
    CTIMER_IRQn                     = 2,    /*!< CTIMER Interrupt */
    ADC_CCOMP01_IRQn                = 3,    /*!< ADC Convert Complete 0-1 Interrupt */
    ADC_CCOMP23_IRQn                = 4,    /*!< ADC Convert Complete 2-3 Interrupt */
    ADC_CCOMP45_IRQn                = 5,    /*!< ADC Convert Complete 4-5 Interrupt */
    ADC_CCOMP67_IRQn                = 6,    /*!< ADC Convert Complete 6-7 Interrupt */
    ADC_MAP_SCOMP_IRQn              = 7,    /*!< ADC mapping Complete Interrupt */
    ADC_LOOP_SCOMP_IRQn             = 8,    /*!< ADC Loop Complete Interrupt */
    ADC_AWDG_OVER_IRQn              = 9,    /*!< ADC Awdg Over Interrupt */
    ADC_AWDG_UNDER_IRQn             = 10,   /*!< ADC Awdg Under Interrupt */
    ADC_ERROR_IRQn                  = 11,   /*!< ADC Error Interrupt */
    ADC_MEASURE_TIMER_IRQn          = 12,   /*!< ADC Measure Timer Interrupt */
    DMA_CH0_IRQn                    = 13,   /*!< DMA Channel 0 Transfer Done Interrupt */
    DMA_CH1_IRQn                    = 14,   /*!< DMA Channel 1 Transfer Done Interrupt */
    DMA_CH2_IRQn                    = 15,   /*!< DMA Channel 2 Transfer Done Interrupt */
    DMA_CH3_IRQn                    = 16,   /*!< DMA Channel 3 Transfer Done Interrupt */
    DMA_ERROR_IRQn                  = 17,   /*!< DMA Error Interrupt */
    MATH_ACCEL_IRQn                 = 18,   /*!< MATH Accelerator Interrupt */
    PORTA_IRQn                      = 21,   /*!< PORTA Interrupt */
    MON_IRQn                        = 22,   /*!< MON Interrupt */
    UART_IRQn                       = 23,   /*!< UART/LIN Interrupt */
    LINPHY_IRQn                     = 24,   /*!< LIN PHY Interrupt */
    SPI_IRQn                        = 25,   /*!< SPI Interrupt */
    SRMC_IRQn                       = 27,   /*!< System Reset And Mode Control Interrupt*/
    PMU_IRQn                        = 28,   /*!< PMU Interrupt */
    FLASH_ERASE_PROGRAM_DONE_IRQn   = 30,   /*!< Flash Erase Or Program Operation Done Interrupt */
} Z20_IrqNumType;

/**
 * @brief  Structure type to access the System Control Block (SCB).
 */
typedef struct
{
    RO uint32 CPUID;                  /*!< Offset: 0x000 (RO)   CPUID Base Register */
    RW uint32 ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
    RW uint32 VTOR;                   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
    RW uint32 AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
    RW uint32 SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
    RW uint32 CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
       uint32 RESERVED1;              /*!< Reserved Register */
    RW uint32 SHPR[2U];               /*!< Offset: 0x01C (R/W)  System Handlers Priority Registers. [0] is RESERVED */
    RW uint32 SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
} Z20_SCBType;

/**
  @brief  Structure type to access the System Timer (SysTick).
 */
typedef struct
{
    RW uint32 CTRL;                   /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
    RW uint32 LOAD;                   /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
    RW uint32 VAL;                    /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
    RO uint32 CALIB;                  /*!< Offset: 0x00C (RO)   SysTick Calibration Register */
} Z20_SysTickType;

/**
 * @brief  Structure type to access the Nested Vectored Interrupt Controller (NVIC).
 */
typedef struct
{
    RW uint32 ISER[1U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
       uint32 RESERVED0[31U];         /*!< Reserved Register */
    RW uint32 ICER[1U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
       uint32 RSERVED1[31U];          /*!< Reserved Register */
    RW uint32 ISPR[1U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
       uint32 RESERVED2[31U];         /*!< Reserved Register */
    RW uint32 ICPR[1U];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
       uint32 RESERVED3[31U];         /*!< Reserved Register */
       uint32 RESERVED4[64U];         /*!< Reserved Register */
    RW uint32 IPR[8U];                /*!< Offset: 0x300 (R/W)  Interrupt Priority Register */
}Z20_NVICType;

/* Memory mapping of Core Hardware */
#define Z20_SCS_BASE            (0xE000E000UL)                            /*!< System Control Space Base Address */
#define Z20_SYSTICK_BASE        (Z20_SCS_BASE +  0x0010UL)                    /*!< SysTick Base Address */
#define Z20_NVIC_BASE           (Z20_SCS_BASE +  0x0100UL)                    /*!< NVIC Base Address */
#define Z20_SCB_BASE            (Z20_SCS_BASE +  0x0D00UL)                    /*!< System Control Block Base Address */

#define Z20_SCB                 ((Z20_SCBType       *)     Z20_SCB_BASE      )   /*!< SCB configuration struct */
#define Z20_SYSTICK             ((Z20_SysTickType   *)     Z20_SYSTICK_BASE  )   /*!< SysTick configuration struct */
#define Z20_NVIC                ((Z20_NVICType      *)     Z20_NVIC_BASE     )   /*!< NVIC configuration struct */

struct Reg_Adc_Bf {
    /* 0x000*/
    uint32 zResverd0x000;
    /* 0x004*/
    uint32 zResverd0x004;
    /* 0x008*/
    struct {
           uint32 ADC_EN                  : 1;  /* [0]            r/w        */
           uint32 RST                     : 1;  /* [1]            r/w        */
           uint32 RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32 GRP0_ABORT              : 1;  /* [4]            r/w        */
           uint32 GRP1_ABORT              : 1;  /* [5]            r/w        */
           uint32 RSVD_31_6               :26;  /* [31:6]         ro         */
    } ADC_CTRL;

    /* 0x00C*/
    struct {
           uint32 DMA_REQ                 : 1;  /* [0]            ro         */
           uint32 AWDG_FAIL_FLAG          : 1;  /* [1]            ro         */
           uint32 AWDG_UNDER              : 1;  /* [2]            r/w1c      */
           uint32 AWDG_OVER               : 1;  /* [3]            r/w1c      */
           uint32 GRP0_LOOP_SCOM          : 1;  /* [4]            r/w1c      */
           uint32 GRP0_MAP_SCOM           : 1;  /* [5]            r/w1c      */
           uint32 CCOM0                   : 1;  /* [6]            r/w1c      */
           uint32 CCOM1                   : 1;  /* [7]            r/w1c      */
           uint32 CCOM2                   : 1;  /* [8]            r/w1c      */
           uint32 CCOM3                   : 1;  /* [9]            r/w1c      */
           uint32 CCOM4                   : 1;  /* [10]           r/w1c      */
           uint32 CCOM5                   : 1;  /* [11]           r/w1c      */
           uint32 CCOM6                   : 1;  /* [12]           r/w1c      */
           uint32 CCOM7                   : 1;  /* [13]           r/w1c      */
           uint32 GRP1_SCOM0              : 1;  /* [14]           r/w1c      */
           uint32 GRP1_SCOM1              : 1;  /* [15]           r/w1c      */
           uint32 GRP1_SCOM2              : 1;  /* [16]           r/w1c      */
           uint32 GRP1_ALL_SCOM           : 1;  /* [17]           r/w1c      */
           uint32 GRP0_LOOP_ABORT         : 1;  /* [18]           r/w1c      */
           uint32 GRP1_LOOP_ABORT         : 1;  /* [19]           r/w1c      */
           uint32 TRIG_CERR               : 1;  /* [20]           r/w1c      */
           uint32 GDU_OT_SD_FLAG          : 1;  /* [21]           r/w1c      */
           uint32 PMU_OT_SD_FLAG          : 1;  /* [22]           r/w1c      */
           uint32 MEAS_TRIG_FLAG          : 1;  /* [23]           r/w1c      */
           uint32 RSVD_26_24              : 3;  /* [26:24]        ro         */
           uint32 PMU_DIS                 : 1;  /* [27]           ro         */
           uint32 GRP0_BUSY               : 1;  /* [28]           ro         */
           uint32 GRP1_BUSY               : 1;  /* [29]           ro         */
           uint32 SAR_BUSY                : 1;  /* [30]           ro         */
           uint32 ADC_PWON                : 1;  /* [31]           ro         */
    } ADC_STAT;

    /* 0x010*/
    struct {
           uint32 ADC_SWTRIG0             : 1;  /* [0]            wo         */
           uint32 ADC_SWTRIG1             : 1;  /* [1]            wo         */
           uint32 ADC_SWTRIG2             : 1;  /* [2]            wo         */
           uint32 ADC_SWTRIG_MEAS         : 1;  /* [3]            wo         */
           uint32 RSVD_31_4               :28;  /* [31:4]         ro         */
    } ADC_SWTRIG;

    /* 0x014*/
    struct {
           uint32 DMA_EN                  : 1;  /* [0]            r/w        */
           uint32 RSVD_1                  : 1;  /* [1]            ro         */
           uint32 AWDG_UNDER_INT_EN       : 1;  /* [2]            r/w        */
           uint32 AWDG_OVER_INT_EN        : 1;  /* [3]            r/w        */
           uint32 GRP0_LOOP_SCOM_EN       : 1;  /* [4]            r/w        */
           uint32 GRP0_MAP_SCOM_EN        : 1;  /* [5]            r/w        */
           uint32 CCOM0_INT_EN            : 1;  /* [6]            r/w        */
           uint32 CCOM1_INT_EN            : 1;  /* [7]            r/w        */
           uint32 CCOM2_INT_EN            : 1;  /* [8]            r/w        */
           uint32 CCOM3_INT_EN            : 1;  /* [9]            r/w        */
           uint32 CCOM4_INT_EN            : 1;  /* [10]           r/w        */
           uint32 CCOM5_INT_EN            : 1;  /* [11]           r/w        */
           uint32 CCOM6_INT_EN            : 1;  /* [12]           r/w        */
           uint32 CCOM7_INT_EN            : 1;  /* [13]           r/w        */
           uint32 GRP1_SCOM0_INT_EN       : 1;  /* [14]           r/w        */
           uint32 GRP1_SCOM1_INT_EN       : 1;  /* [15]           r/w        */
           uint32 GRP1_SCOM2_INT_EN       : 1;  /* [16]           r/w        */
           uint32 GRP1_ALL_COM_INT_EN     : 1;  /* [17]           r/w        */
           uint32 GRP0_LOOP_ABORT_INT_EN  : 1;  /* [18]           r/w        */
           uint32 GRP1_LOOP_ABORT_INT_EN  : 1;  /* [19]           r/w        */
           uint32 TRIG_CERR_INT_EN        : 1;  /* [20]           r/w        */
           uint32 GDU_OT_SD_NMI_EN        : 1;  /* [21]           r/w        */
           uint32 PMU_OT_SD_NMI_EN        : 1;  /* [22]           r/w        */
           uint32 MEAS_TRIG_INT_EN        : 1;  /* [23]           r/w        */
           uint32 RSVD_31_24              : 8;  /* [31:24]        ro         */
    } ADC_IE;

    /* 0x018*/
    struct {
           uint32 BUFFCAL_EN              : 1;  /* [0]            r/w        */
           uint32 CLK_DIV                 : 1;  /* [1]            r/w        */
           uint32 FAST_MODE               : 1;  /* [2]            r/w        */
           uint32 HWT_EN                  : 1;  /* [3]            r/w        */
           uint32 ANA_FAST_EN             : 1;  /* [4]            r/w        */
           uint32 RSVD_15_5               :11;  /* [15:5]         ro         */
           uint32 STABLE_T                :11;  /* [26:16]        r/w        */
           uint32 RSVD_31_27              : 5;  /* [31:27]        ro         */
    } ADC_CFG;

    /* 0x01C*/
    struct {
           uint32 SMP_EXT0                :10;  /* [9:0]          r/w        */
           uint32 SMP_EXT1                :10;  /* [19:10]        r/w        */
           uint32 SMP_EXT2                :10;  /* [29:20]        r/w        */
           uint32 RSVD_31_30              : 2;  /* [31:30]        ro         */
    } ADC_TCFG0;

    /* 0x020*/
    struct {
           uint32 SMP_EXT3                :10;  /* [9:0]          r/w        */
           uint32 SMP_EXT4                :10;  /* [19:10]        r/w        */
           uint32 SMP_EXT5                :10;  /* [29:20]        r/w        */
           uint32 RSVD_31_30              : 2;  /* [31:30]        ro         */
    } ADC_TCFG1;

    /* 0x024*/
    struct {
           uint32 SMP_EXT6                :10;  /* [9:0]          r/w        */
           uint32 SMP_EXT7                :10;  /* [19:10]        r/w        */
           uint32 SMP_EXT8                :10;  /* [29:20]        r/w        */
           uint32 RSVD_31_30              : 2;  /* [31:30]        ro         */
    } ADC_TCFG2;

    /* 0x028*/
    struct {
           uint32 SMP_IN0                 :10;  /* [9:0]          r/w        */
           uint32 SMP_IN1                 :10;  /* [19:10]        r/w        */
           uint32 SMP_IN2                 :10;  /* [29:20]        r/w        */
           uint32 RSVD_31_30              : 2;  /* [31:30]        ro         */
    } ADC_TCFG3;

    /* 0x02C*/
    struct {
           uint32 SMP_IN3                 :10;  /* [9:0]          r/w        */
           uint32 SMP_IN4                 :10;  /* [19:10]        r/w        */
           uint32 RSVD_31_20              :12;  /* [31:20]        ro         */
    } ADC_TCFG4;

    /* 0x030*/
    struct {
           uint32 CH_ID_INTER0            : 1;  /* [0]            r/w        */
           uint32 CH_ID_INTER1            : 1;  /* [1]            r/w        */
           uint32 CH_ID_INTER2            : 1;  /* [2]            r/w        */
           uint32 CH_ID_INTER3            : 1;  /* [3]            r/w        */
           uint32 CH_ID_INTER4            : 1;  /* [4]            r/w        */
           uint32 CH_ID_INTER5            : 1;  /* [5]            r/w        */
           uint32 CH_ID_INTER6            : 1;  /* [6]            r/w        */
           uint32 CH_ID_INTER7            : 1;  /* [7]            r/w        */
           uint32 CH_ID_INTER8            : 1;  /* [8]            r/w        */
           uint32 CH_ID_INTER9            : 1;  /* [9]            r/w        */
           uint32 RSVD_10                 : 1;  /* [10]           ro         */
           uint32 CH_ID_INTER11           : 1;  /* [11]           r/w        */
           uint32 CH_ID_INTER12           : 1;  /* [12]           r/w        */
           uint32 CH_ID_INTER13           : 1;  /* [13]           r/w        */
           uint32 CH_ID_INTER14           : 1;  /* [14]           r/w        */
           uint32 RSVD_15                 : 1;  /* [15]           ro         */
           uint32 CH_ID_INTER16           : 1;  /* [16]           r/w        */
           uint32 CH_ID_INTER17           : 1;  /* [17]           r/w        */
           uint32 CH_ID_INTER18           : 1;  /* [18]           r/w        */
           uint32 RSVD_31_19              :13;  /* [31:19]        ro         */
    } ADC_BUFF_EN;

    /* 0x034*/
    struct {
           uint32 BUFF_OFFSET             :13;  /* [12:0]         r/w        */
           uint32 RSVD_31_13              :19;  /* [31:13]        ro         */
    } ADC_BUFF_OFFSET_VAL;

    /* 0x038*/
    struct {
           uint32 RELOAD_VAL              :16;  /* [15:0]         r/w        */
           uint32 TRIG_EN                 : 1;  /* [16]           r/w        */
           uint32 MOD_EN                  : 1;  /* [17]           r/w        */
           uint32 RSVD_23_18              : 6;  /* [23:18]        ro         */
           uint32 SW_TRIG_INT             : 1;  /* [24]           wo         */
           uint32 RSVD_31_25              : 7;  /* [31:25]        ro         */
    } ADC_MEAS_TRIG;

    uint8 zResverd0x03C[4];   /*pad 0x03C - 03F*/

    /* 0x040*/
    struct {
           uint32 RSVD_0                  : 1;  /* [0]            ro         */
           uint32 DATA_MASK               : 1;  /* [1]            r/w        */
           uint32 RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32 LOOP_SCOM_FLAG_EN       : 1;  /* [4]            r/w        */
           uint32 MAP_SCOM_FLAG_EN        : 1;  /* [5]            r/w        */
           uint32 RSVD_7_6                : 2;  /* [7:6]          ro         */
           uint32 MIX_MODE                : 1;  /* [8]            r/w        */
           uint32 TRIG_MODE               : 1;  /* [9]            r/w        */
           uint32 RSVD_15_10              : 6;  /* [15:10]                   */
           uint32 LMD                     : 3;  /* [18:16]        r/w        */
           uint32 RSVD_23_19              : 5;  /* [23:19]        ro         */
           uint32 AVGS                    : 3;  /* [26:24]        r/w        */
           uint32 RSVD_31_27              : 5;  /* [31:27]        ro         */
    } ADC_GRP0_CFG;

    /* 0x044*/
    struct {
           uint32 CMD0                    : 6;  /* [5:0]          r/w        */
           uint32 CMD0_FLAG_EN            : 1;  /* [6]            r/w        */
           uint32 MAP0_SEQ_AND_EN         : 1;  /* [7]            r/w        */
           uint32 CMD1                    : 6;  /* [13:8]         r/w        */
           uint32 CMD1_FLAG_EN            : 1;  /* [14]           r/w        */
           uint32 MAP1_SEQ_AND_EN         : 1;  /* [15]           r/w        */
           uint32 CMD2                    : 6;  /* [21:16]        r/w        */
           uint32 CMD2_FLAG_EN            : 1;  /* [22]           r/w        */
           uint32 MAP2_SEQ_AND_EN         : 1;  /* [23]           r/w        */
           uint32 CMD3                    : 6;  /* [29:24]        r/w        */
           uint32 CMD3_FLAG_EN            : 1;  /* [30]           r/w        */
           uint32 RSVD_31                 : 1;  /* [31]           ro         */
    } ADC_CMD_BUFF0;

    /* 0x048*/
    struct {
           uint32 CMD4                    : 6;  /* [5:0]          r/w        */
           uint32 CMD4_FLAG_EN            : 1;  /* [6]            r/w        */
           uint32 RSVD_7                  : 1;  /* [7]            ro         */
           uint32 CMD5                    : 6;  /* [13:8]         r/w        */
           uint32 CMD5_FLAG_EN            : 1;  /* [14]           r/w        */
           uint32 RSVD_15                 : 1;  /* [15]           ro         */
           uint32 CMD6                    : 6;  /* [21:16]        r/w        */
           uint32 CMD6_FLAG_EN            : 1;  /* [22]           r/w        */
           uint32 RSVD_23                 : 1;  /* [23]           ro         */
           uint32 CMD7                    : 6;  /* [29:24]        r/w        */
           uint32 CMD7_FLAG_EN            : 1;  /* [30]           r/w        */
           uint32 RSVD_31                 : 1;  /* [31]           ro         */
    } ADC_CMD_BUFF1;

    uint8 zResverd0x04C[4];   /*pad 0x04C - 04F*/

    /* 0x050*/
    struct {
           uint32 ADC_DATA_RD             :12;  /* [11:0]         ro         */
           uint32 RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32 CH_ID                   : 5;  /* [20:16]        ro         */
           uint32 RSVD_23_21              : 3;  /* [23:21]        ro         */
           uint32 VALID                   : 1;  /* [24]           ro         */
           uint32 OVERRUN                 : 1;  /* [25]           ro         */
           uint32 RSVD_31_26              : 6;  /* [31:26]        ro         */
    } ADC_GRP0_DATA_RD[8];

    /* 0x070*/
    struct {
           uint32 RSVD_3_0                : 4;  /* [3:0]          ro         */
           uint32 LOOP0_SCOM_FLAG_EN      : 1;  /* [4]            r/w        */
           uint32 LOOP1_SCOM_FLAG_EN      : 1;  /* [5]            r/w        */
           uint32 LOOP2_SCOM_FLAG_EN      : 1;  /* [6]            r/w        */
           uint32 LOOP_SCOM_FLAG_EN       : 1;  /* [7]            r/w        */
           uint32 RSVD_31_8               :24;  /* [31:8]         ro         */
    } ADC_GRP1_CFG;

    /* 0x074*/
    struct {
           uint32 CH10_EN                 : 1;  /* [0]            r/w        */
           uint32 CH11_EN                 : 1;  /* [1]            r/w        */
           uint32 CH12_EN                 : 1;  /* [2]            r/w        */
           uint32 CH13_EN                 : 1;  /* [3]            r/w        */
           uint32 CH14_EN                 : 1;  /* [4]            r/w        */
           uint32 CH15_EN                 : 1;  /* [5]            r/w        */
           uint32 CH16_EN                 : 1;  /* [6]            r/w        */
           uint32 CH17_EN                 : 1;  /* [7]            r/w        */
           uint32 CH18_EN                 : 1;  /* [8]            r/w        */
           uint32 CH19_EN                 : 1;  /* [9]            r/w        */
           uint32 CH1A_EN                 : 1;  /* [10]           r/w        */
           uint32 CH1B_EN                 : 1;  /* [11]           r/w        */
           uint32 CH1C_EN                 : 1;  /* [12]           r/w        */
           uint32 CH1D_EN                 : 1;  /* [13]           r/w        */
           uint32 CH1E_EN                 : 1;  /* [14]           r/w        */
           uint32 CH1F_EN                 : 1;  /* [15]           r/w        */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } ADC_GRP1_SQ0;

    /* 0x078*/
    struct {
           uint32 CH10_EN                 : 1;  /* [0]            r/w        */
           uint32 CH11_EN                 : 1;  /* [1]            r/w        */
           uint32 CH12_EN                 : 1;  /* [2]            r/w        */
           uint32 CH13_EN                 : 1;  /* [3]            r/w        */
           uint32 CH14_EN                 : 1;  /* [4]            r/w        */
           uint32 CH15_EN                 : 1;  /* [5]            r/w        */
           uint32 CH16_EN                 : 1;  /* [6]            r/w        */
           uint32 CH17_EN                 : 1;  /* [7]            r/w        */
           uint32 CH18_EN                 : 1;  /* [8]            r/w        */
           uint32 CH19_EN                 : 1;  /* [9]            r/w        */
           uint32 CH1A_EN                 : 1;  /* [10]           r/w        */
           uint32 CH1B_EN                 : 1;  /* [11]           r/w        */
           uint32 CH1C_EN                 : 1;  /* [12]           r/w        */
           uint32 CH1D_EN                 : 1;  /* [13]           r/w        */
           uint32 CH1E_EN                 : 1;  /* [14]           r/w        */
           uint32 CH1F_EN                 : 1;  /* [15]           r/w        */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } ADC_GRP1_SQ1;

    /* 0x07C*/
    struct {
           uint32 CH10_EN                 : 1;  /* [0]            r/w        */
           uint32 CH11_EN                 : 1;  /* [1]            r/w        */
           uint32 CH12_EN                 : 1;  /* [2]            r/w        */
           uint32 CH13_EN                 : 1;  /* [3]            r/w        */
           uint32 CH14_EN                 : 1;  /* [4]            r/w        */
           uint32 CH15_EN                 : 1;  /* [5]            r/w        */
           uint32 CH16_EN                 : 1;  /* [6]            r/w        */
           uint32 CH17_EN                 : 1;  /* [7]            r/w        */
           uint32 CH18_EN                 : 1;  /* [8]            r/w        */
           uint32 CH19_EN                 : 1;  /* [9]            r/w        */
           uint32 CH1A_EN                 : 1;  /* [10]           r/w        */
           uint32 CH1B_EN                 : 1;  /* [11]           r/w        */
           uint32 CH1C_EN                 : 1;  /* [12]           r/w        */
           uint32 CH1D_EN                 : 1;  /* [13]           r/w        */
           uint32 CH1E_EN                 : 1;  /* [14]           r/w        */
           uint32 CH1F_EN                 : 1;  /* [15]           r/w        */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } ADC_GRP1_SQ2;

    /* 0x080*/
    struct {
           uint32 ADC_DATA                :10;  /* [9:0]          ro         */
           uint32 RSVD_31_10              :22;  /* [31:10]        ro         */
    } ADC_GRP1_DATA_RD[16];

    uint8 zResverd0x0C0[4];   /*pad 0x0C0 - 0C3*/

    /* 0x0C4*/
    struct {
           uint32 ADC_IIR_DATA            :10;  /* [9:0]          r/w        */
           uint32 RSVD_31_10              :22;  /* [31:10]        ro         */
    } ADC_IIR_DATA_RD[15];

    /* 0x100*/
    struct {
           uint32 CH10_IIR_B              : 2;  /* [1:0]          r/w        */
           uint32 CH11_IIR_B              : 2;  /* [3:2]          r/w        */
           uint32 CH12_IIR_B              : 2;  /* [5:4]          r/w        */
           uint32 CH13_IIR_B              : 2;  /* [7:6]          r/w        */
           uint32 CH14_IIR_B              : 2;  /* [9:8]          r/w        */
           uint32 CH15_IIR_B              : 2;  /* [11:10]        r/w        */
           uint32 CH16_IIR_B              : 2;  /* [13:12]        r/w        */
           uint32 CH17_IIR_B              : 2;  /* [15:14]        r/w        */
           uint32 CH18_IIR_B              : 2;  /* [17:16]        r/w        */
           uint32 CH19_IIR_B              : 2;  /* [19:18]        r/w        */
           uint32 CH1E_IIR_B              : 2;  /* [21:20]        r/w        */
           uint32 CHU1_IIR_B              : 2;  /* [23:22]        r/w        */
           uint32 CHU2_IIR_B              : 2;  /* [25:24]        r/w        */
           uint32 CHU3_IIR_B              : 2;  /* [27:26]        r/w        */
           uint32 CHU4_IIR_B              : 2;  /* [29:28]        r/w        */
           uint32 RSVD_31_30              : 2;  /* [31:30]        ro         */
    } ADC_IIR_COE;

    /* 0x104*/
    struct {
           uint32 RSVD_15_0               :16;  /* [15:0]         ro         */
           uint32 VS_L2_OVER_TH           :10;  /* [25:16]        r/w        */
           uint32 TIME_TH_VS_L2_O         : 3;  /* [28:26]        r/w        */
           uint32 MODE_VS_L2_O            : 1;  /* [29]           ro         */
           uint32 IIR_EN_VS_L2_O          : 1;  /* [30]           r/w        */
           uint32 RSVD_31                 : 1;  /* [31]           ro         */
    } ADC_AWDG_TH10_0;

    /* 0x108*/
    struct {
           uint32 VS_UNDER_TH             :10;  /* [9:0]          r/w        */
           uint32 TIME_TH_VS_U            : 3;  /* [12:10]        r/w        */
           uint32 MODE_VS_U               : 1;  /* [13]           ro         */
           uint32 IIR_EN_VS_U             : 1;  /* [14]           r/w        */
           uint32 RSVD_15                 : 1;  /* [15]           ro         */
           uint32 VS_L1_OVER_TH           :10;  /* [25:16]        r/w        */
           uint32 TIME_TH_VS_L1_O         : 3;  /* [28:26]        r/w        */
           uint32 MODE_VS_L1_O            : 1;  /* [29]           ro         */
           uint32 IIR_EN_VS_L1_O          : 1;  /* [30]           r/w        */
           uint32 RSVD_31                 : 1;  /* [31]           ro         */
    } ADC_AWDG_TH10_1;

    /* 0x10C*/
    struct {
           uint32 VDP_UNDER_TH            :10;  /* [9:0]          r/w        */
           uint32 TIME_TH_VDP_U           : 3;  /* [12:10]        r/w        */
           uint32 MODE_VDP_U              : 1;  /* [13]           ro         */
           uint32 IIR_EN_VDP_U            : 1;  /* [14]           r/w        */
           uint32 RSVD_15                 : 1;  /* [15]           ro         */
           uint32 VDP_OVER_TH             :10;  /* [25:16]        r/w        */
           uint32 TIME_TH_VDP_O           : 3;  /* [28:26]        r/w        */
           uint32 MODE_VDP_O              : 1;  /* [29]           ro         */
           uint32 IIR_EN_VDP_O            : 1;  /* [30]           r/w        */
           uint32 RSVD_31                 : 1;  /* [31]           ro         */
    } ADC_AWDG_TH11;

    /* 0x110*/
    struct {
           uint32 HV_UNDER_TH             :10;  /* [9:0]          r/w        */
           uint32 TIME_TH_HV_U            : 3;  /* [12:10]        r/w        */
           uint32 MODE_HV_U               : 1;  /* [13]           ro         */
           uint32 IIR_EN_HV_U             : 1;  /* [14]           r/w        */
           uint32 RSVD_15                 : 1;  /* [15]           ro         */
           uint32 HV_OVER_TH              :10;  /* [25:16]        r/w        */
           uint32 TIME_TH_HV_O            : 3;  /* [28:26]        r/w        */
           uint32 MODE_HV_O               : 1;  /* [29]           ro         */
           uint32 IIR_EN_HV_O             : 1;  /* [30]           r/w        */
           uint32 RSVD_31                 : 1;  /* [31]           ro         */
    } ADC_AWDG_TH12;

    /* 0x114*/
    struct {
           uint32 VSD_UNDER_TH            :10;  /* [9:0]          r/w        */
           uint32 TIME_TH_VSD_U           : 3;  /* [12:10]        r/w        */
           uint32 MODE_VSD_U              : 1;  /* [13]           ro         */
           uint32 IIR_EN_VSD_U            : 1;  /* [14]           r/w        */
           uint32 RSVD_15                 : 1;  /* [15]           ro         */
           uint32 VSD_OVER_TH             :10;  /* [25:16]        r/w        */
           uint32 TIME_TH_VSD_O           : 3;  /* [28:26]        r/w        */
           uint32 MODE_VSD_O              : 1;  /* [29]           ro         */
           uint32 IIR_EN_VSD_O            : 1;  /* [30]           r/w        */
           uint32 RSVD_31                 : 1;  /* [31]           ro         */
    } ADC_AWDG_TH13;

    /* 0x118*/
    struct {
           uint32 VCP_UNDER_TH            :10;  /* [9:0]          r/w        */
           uint32 TIME_TH_VCP_U           : 3;  /* [12:10]        r/w        */
           uint32 MODE_VCP_U              : 1;  /* [13]           ro         */
           uint32 IIR_EN_VCP_U            : 1;  /* [14]           r/w        */
           uint32 RSVD_15                 : 1;  /* [15]           ro         */
           uint32 VCP_OVER_TH             :10;  /* [25:16]        r/w        */
           uint32 TIME_TH_VCP_O           : 3;  /* [28:26]        r/w        */
           uint32 MODE_VCP_O              : 1;  /* [29]           ro         */
           uint32 IIR_EN_VCP_O            : 1;  /* [30]           r/w        */
           uint32 RSVD_31                 : 1;  /* [31]           ro         */
    } ADC_AWDG_TH14;

    /* 0x11C*/
    struct {
           uint32 VDH_UNDER_TH            :10;  /* [9:0]          r/w        */
           uint32 TIME_TH_VDH_U           : 3;  /* [12:10]        r/w        */
           uint32 MODE_VDH_U              : 1;  /* [13]           ro         */
           uint32 IIR_EN_VDH_U            : 1;  /* [14]           r/w        */
           uint32 RSVD_15                 : 1;  /* [15]           ro         */
           uint32 VDH_OVER_TH             :10;  /* [25:16]        r/w        */
           uint32 TIME_TH_VDH_O           : 3;  /* [28:26]        r/w        */
           uint32 MODE_VDH_O              : 1;  /* [29]           ro         */
           uint32 IIR_EN_VDH_O            : 1;  /* [30]           r/w        */
           uint32 RSVD_31                 : 1;  /* [31]           ro         */
    } ADC_AWDG_TH15;

    /* 0x120*/
    struct {
           uint32 VDC_UNDER_TH            :10;  /* [9:0]          r/w        */
           uint32 TIME_TH_VDC_U           : 3;  /* [12:10]        r/w        */
           uint32 MODE_VDC_U              : 1;  /* [13]           ro         */
           uint32 IIR_EN_VDC_U            : 1;  /* [14]           r/w        */
           uint32 RSVD_15                 : 1;  /* [15]           ro         */
           uint32 VDC_OVER_TH             :10;  /* [25:16]        r/w        */
           uint32 TIME_TH_VDC_O           : 3;  /* [28:26]        r/w        */
           uint32 MODE_VDC_O              : 1;  /* [29]           ro         */
           uint32 IIR_EN_VDC_O            : 1;  /* [30]           r/w        */
           uint32 RSVD_31                 : 1;  /* [31]           ro         */
    } ADC_AWDG_TH16;

    /* 0x124*/
    struct {
           uint32 SOTS_TH                 :10;  /* [9:0]          r/w        */
           uint32 TIME_TH_SOTS            : 3;  /* [12:10]        r/w        */
           uint32 MODE_SOTS               : 1;  /* [13]           ro         */
           uint32 IIR_EN_SOTS             : 1;  /* [14]           r/w        */
           uint32 RSVD_15                 : 1;  /* [15]           ro         */
           uint32 SOTW_TH                 :10;  /* [25:16]        r/w        */
           uint32 TIME_TH_SOTW            : 3;  /* [28:26]        r/w        */
           uint32 MODE_SOTW               : 1;  /* [29]           ro         */
           uint32 IIR_EN_SOTW             : 1;  /* [30]           r/w        */
           uint32 RSVD_31                 : 1;  /* [31]           ro         */
    } ADC_AWDG_TH17;

    /* 0x128*/
    struct {
           uint32 GDU_OTS_TH              :10;  /* [9:0]          r/w        */
           uint32 TIME_TH_GDU_OTS         : 3;  /* [12:10]        r/w        */
           uint32 MODE_GDU_OTS            : 1;  /* [13]           ro         */
           uint32 IIR_EN_GDU_OTS          : 1;  /* [14]           r/w        */
           uint32 RSVD_15                 : 1;  /* [15]           ro         */
           uint32 GDU_OTW_TH              :10;  /* [25:16]        r/w        */
           uint32 TIME_TH_GDU_OTW         : 3;  /* [28:26]        r/w        */
           uint32 MODE_GDU_OTW            : 1;  /* [29]           ro         */
           uint32 IIR_EN_GDU_OTW          : 1;  /* [30]           r/w        */
           uint32 RSVD_31                 : 1;  /* [31]           ro         */
    } ADC_AWDG_TH18;

    /* 0x12C*/
    struct {
           uint32 GDU_LIN_TH              :10;  /* [9:0]          r/w        */
           uint32 TIME_TH_LIN_OTW         : 3;  /* [12:10]        r/w        */
           uint32 MODE_LIN_OTW            : 1;  /* [13]           ro         */
           uint32 IIR_EN_LIN_OTW          : 1;  /* [14]           r/w        */
           uint32 RSVD_15                 : 1;  /* [15]           ro         */
           uint32 AON_O_TH                :10;  /* [25:16]        r/w        */
           uint32 TIME_TH_AON_O           : 3;  /* [28:26]        r/w        */
           uint32 MODE_AON_O              : 1;  /* [29]           ro         */
           uint32 IIR_EN_AON_O            : 1;  /* [30]           r/w        */
           uint32 RSVD_31                 : 1;  /* [31]           ro         */
    } ADC_AWDG_TH19E;

    /* 0x130*/
    struct {
           uint32 TH_U1                   :10;  /* [9:0]          r/w        */
           uint32 TIME_TH_U1              : 3;  /* [12:10]        r/w        */
           uint32 MODE_U1                 : 1;  /* [13]           r/w        */
           uint32 IIR_EN_U1               : 1;  /* [14]           r/w        */
           uint32 RSVD_15                 : 1;  /* [15]           ro         */
           uint32 CH_ID_U1                : 5;  /* [20:16]        r/w        */
           uint32 RSVD_30_21              :10;  /* [30:21]        ro         */
           uint32 U1_EN                   : 1;  /* [31]           r/w        */
    } ADC_AWDG_THU1;

    /* 0x134*/
    struct {
           uint32 TH_U2                   :10;  /* [9:0]          r/w        */
           uint32 TIME_TH_U2              : 3;  /* [12:10]        r/w        */
           uint32 MODE_U2                 : 1;  /* [13]           r/w        */
           uint32 IIR_EN_U2               : 1;  /* [14]           r/w        */
           uint32 RSVD_15                 : 1;  /* [15]           ro         */
           uint32 CH_ID_U2                : 5;  /* [20:16]        r/w        */
           uint32 RSVD_30_21              :10;  /* [30:21]        ro         */
           uint32 U2_EN                   : 1;  /* [31]           r/w        */
    } ADC_AWDG_THU2;

    /* 0x138*/
    struct {
           uint32 TH_U3                   :10;  /* [9:0]          r/w        */
           uint32 TIME_TH_U3              : 3;  /* [12:10]        r/w        */
           uint32 MODE_U3                 : 1;  /* [13]           r/w        */
           uint32 IIR_EN_U3               : 1;  /* [14]           r/w        */
           uint32 RSVD_15                 : 1;  /* [15]           ro         */
           uint32 CH_ID_U3                : 5;  /* [20:16]        r/w        */
           uint32 RSVD_30_21              :10;  /* [30:21]        ro         */
           uint32 U3_EN                   : 1;  /* [31]           r/w        */
    } ADC_AWDG_THU3;

    /* 0x13C*/
    struct {
           uint32 TH_U4                   :10;  /* [9:0]          r/w        */
           uint32 TIME_TH_U4              : 3;  /* [12:10]        r/w        */
           uint32 MODE_U4                 : 1;  /* [13]           r/w        */
           uint32 IIR_EN_U4               : 1;  /* [14]           r/w        */
           uint32 RSVD_15                 : 1;  /* [15]           ro         */
           uint32 CH_ID_U4                : 5;  /* [20:16]        r/w        */
           uint32 RSVD_30_21              :10;  /* [30:21]        ro         */
           uint32 U4_EN                   : 1;  /* [31]           r/w        */
    } ADC_AWDG_THU4;

    /* 0x140*/
    struct {
           uint32 VS_OV_L2_INT            : 1;  /* [0]            ro         */
           uint32 VS_OV_L1_INT            : 1;  /* [1]            ro         */
           uint32 VS_UV_INT               : 1;  /* [2]            ro         */
           uint32 VDDP_OV_INT             : 1;  /* [3]            ro         */
           uint32 VDDP_UV_INT             : 1;  /* [4]            ro         */
           uint32 HV_MON_OV_INT           : 1;  /* [5]            ro         */
           uint32 HV_MON_UV_INT           : 1;  /* [6]            ro         */
           uint32 VSD_OV_INT              : 1;  /* [7]            ro         */
           uint32 VSD_UV_INT              : 1;  /* [8]            ro         */
           uint32 VCP_OV_INT              : 1;  /* [9]            ro         */
           uint32 VCP_UV_INT              : 1;  /* [10]           ro         */
           uint32 VDH_OV_INT              : 1;  /* [11]           ro         */
           uint32 VDH_UV_INT              : 1;  /* [12]           ro         */
           uint32 VDDC_OVER_INT           : 1;  /* [13]           ro         */
           uint32 VDDC_UNDER_INT          : 1;  /* [14]           ro         */
           uint32 SOTW_INT                : 1;  /* [15]           ro         */
           uint32 SOTS_NMI                : 1;  /* [16]           ro         */
           uint32 GDU_OTW_INT             : 1;  /* [17]           ro         */
           uint32 GDU_OTS_NMI             : 1;  /* [18]           ro         */
           uint32 LIN_OTW_INT             : 1;  /* [19]           ro         */
           uint32 VDDC_AON_INT            : 1;  /* [20]           ro         */
           uint32 U1_INT                  : 1;  /* [21]           ro         */
           uint32 U2_INT                  : 1;  /* [22]           ro         */
           uint32 U3_INT                  : 1;  /* [23]           ro         */
           uint32 U4_INT                  : 1;  /* [24]           ro         */
           uint32 RSVD_31_25              : 7;  /* [31:25]        ro         */
    } ADC_AWDOG_STAT;

    uint8 zResverd0x0144[12];   /*pad 0x0144 - 014F*/

    /* 0x150*/
    struct {
           uint32 CUT                     : 5;  /* [4:0]          r/w        */
           uint32 RSVD_7_5                : 3;  /* [7:5]          ro         */
           uint32 TESTPOL                 : 1;  /* [8]            r/w        */
           uint32 TEST                    : 1;  /* [9]            r/w        */
           uint32 RSVD_31_10              :22;  /* [31:10]        ro         */
    } ADC_SELF_TEST_CFG;

    /* 0x154*/
    struct {
           uint32 LIN_TS_CAL_EN           : 1;  /* [0]            r/w        */
           uint32 GDU_TS_CAL_EN           : 1;  /* [1]            r/w        */
           uint32 PMU_TS_CAL_EN           : 1;  /* [2]            r/w        */
           uint32 RSVD_31_3               :29;  /* [31:3]         ro         */
    } ADC_TS_CFG;

    /* 0x158*/
    struct {
           uint32 GDU_TS_OFFSET           :13;  /* [12:0]         r/w        */
           uint32 RSVD_15_13              : 3;  /* [15:13]        ro         */
           uint32 PMU_TS_OFFSET           :13;  /* [28:16]        r/w        */
           uint32 RSVD_31_29              : 3;  /* [31:29]        ro         */
    } ADC_TS_CAL0;

    /* 0x15C*/
    struct {
           uint32 LIN_TS_OFFSET           :13;  /* [12:0]         r/w        */
           uint32 RSVD_31_13              :19;  /* [31:13]        ro         */
    } ADC_TS_CAL1;
};    /*adc_reg*/

struct Reg_Adc_W {
    /* 0x000*/
    uint32 zResverd0x000;
    /* 0x004*/
    uint32 zResverd0x004;
    /* 0x008*/
    uint32 ADC_CTRL;
    /* 0x00C*/
    uint32 ADC_STAT;
    /* 0x010*/
    uint32 ADC_SWTRIG;
    /* 0x014*/
    uint32 ADC_IE;
    /* 0x018*/
    uint32 ADC_CFG;
    /* 0x01C*/
    uint32 ADC_TCFG0;
    /* 0x020*/
    uint32 ADC_TCFG1;
    /* 0x024*/
    uint32 ADC_TCFG2;
    /* 0x028*/
    uint32 ADC_TCFG3;
    /* 0x02C*/
    uint32 ADC_TCFG4;
    /* 0x030*/
    uint32 ADC_BUFF_EN;
    /* 0x034*/
    uint32 ADC_BUFF_OFFSET_VAL;
    /* 0x038*/
    uint32 ADC_MEAS_TRIG;
    uint8 zResverd0x03C[4];   /*pad 0x03C - 03F*/

    /* 0x040*/
    uint32 ADC_GRP0_CFG;
    /* 0x044*/
    uint32 ADC_CMD_BUFF0;
    /* 0x048*/
    uint32 ADC_CMD_BUFF1;
    uint8 zResverd0x04C[4];   /*pad 0x04C - 04F*/

    /* 0x050*/
    uint32 ADC_GRP0_DATA_RD[8];
    /* 0x070*/
    uint32 ADC_GRP1_CFG;
    /* 0x074*/
    uint32 ADC_GRP1_SQ0;
    /* 0x078*/
    uint32 ADC_GRP1_SQ1;
    /* 0x07C*/
    uint32 ADC_GRP1_SQ2;
    /* 0x080*/
    uint32 ADC_GRP1_DATA_RD[16];
    uint8 zResverd0x0C0[4];   /*pad 0x0C0 - 0C3*/

    /* 0x0C4*/
    uint32 ADC_IIR_DATA_RD[15];
    /* 0x100*/
    uint32 ADC_IIR_COE;
    /* 0x104*/
    uint32 ADC_AWDG_TH10_0;
    /* 0x108*/
    uint32 ADC_AWDG_TH10_1;
    /* 0x10C*/
    uint32 ADC_AWDG_TH11;
    /* 0x110*/
    uint32 ADC_AWDG_TH12;
    /* 0x114*/
    uint32 ADC_AWDG_TH13;
    /* 0x118*/
    uint32 ADC_AWDG_TH14;
    /* 0x11C*/
    uint32 ADC_AWDG_TH15;
    /* 0x120*/
    uint32 ADC_AWDG_TH16;
    /* 0x124*/
    uint32 ADC_AWDG_TH17;
    /* 0x128*/
    uint32 ADC_AWDG_TH18;
    /* 0x12C*/
    uint32 ADC_AWDG_TH19E;
    /* 0x130*/
    uint32 ADC_AWDG_THU1;
    /* 0x134*/
    uint32 ADC_AWDG_THU2;
    /* 0x138*/
    uint32 ADC_AWDG_THU3;
    /* 0x13C*/
    uint32 ADC_AWDG_THU4;
    /* 0x140*/
    uint32 ADC_AWDOG_STAT;
    uint8 zResverd0x0144[12];   /*pad 0x0144 - 014F*/

    /* 0x150*/
    uint32 ADC_SELF_TEST_CFG;
    /* 0x154*/
    uint32 ADC_TS_CFG;
    /* 0x158*/
    uint32 ADC_TS_CAL0;
    /* 0x15C*/
    uint32 ADC_TS_CAL1;
};    /*adc_reg*/

typedef volatile struct Reg_Adc_Bf Reg_Adc_BfType;
typedef volatile struct Reg_Adc_W  Reg_Adc_WType;

struct Reg_Cmp_Bf {
    /* 0x0*/
    struct {
           uint32 VERID                   :32;  /* [31:0]         ro         */
    } CMP_VERID;

    /* 0x4*/
    struct {
           uint32 DAC_RES                 : 4;  /* [3:0]          ro         */
           uint32 RSVD_31_4               :28;  /* [31:4]                    */
    } CMP_PARAM;

    /* 0x8*/
    struct {
           uint32 RSVD_0                  : 1;  /* [0]                       */
           uint32 CMP_EN                  : 1;  /* [1]            r/w        */
           uint32 RSVD_31_2               :30;  /* [31:2]                    */
    } CMP_CCR0;

    /* 0xC*/
    struct {
           uint32 RSVD_2_0                : 3;  /* [2:0]                     */
           uint32 COUT_INV                : 1;  /* [3]            r/w        */
           uint32 RSVD_15_4               :12;  /* [15:4]                    */
           uint32 FILT_CNT                : 8;  /* [23:16]        r/w        */
           uint32 RSVD_31_24              : 8;  /* [31:24]                   */
    } CMP_CCR1;

    /* 0x10*/
    struct {
           uint32 HS_HSTCTR               : 2;  /* [1:0]          r/w        */
           uint32 HS_MODE                 : 1;  /* [2]            r/w        */
           uint32 RSVD_15_3               :13;  /* [15:3]                    */
           uint32 HS_PSEL                 : 2;  /* [17:16]        r/w        */
           uint32 RSVD_19_18              : 2;  /* [19:18]                   */
           uint32 HS_MSEL                 : 2;  /* [21:20]        r/w        */
           uint32 RSVD_31_22              :10;  /* [31:22]                   */
    } CMP_CCR2;

    /* 0x14*/
    struct {
           uint32 DAC_EN                  : 1;  /* [0]            r/w        */
           uint32 RSVD_7_1                : 7;  /* [7:1]                     */
           uint32 VREF_SEL                : 1;  /* [8]            r/w        */
           uint32 RSVD_15_9               : 7;  /* [15:9]                    */
           uint32 DAC_SEL                 : 8;  /* [23:16]        r/w        */
           uint32 DAC_OUT_SEL             : 2;  /* [25:24]        r/w        */
           uint32 RSVD_31_26              : 6;  /* [31:26]                   */
    } CMP_DCR;

    /* 0x18*/
    struct {
           uint32 CFR_IE                  : 1;  /* [0]            r/w        */
           uint32 CFF_IE                  : 1;  /* [1]            r/w        */
           uint32 RSVD_31_2               :30;  /* [31:2]                    */
    } CMP_IER;

    /* 0x1C*/
    struct {
           uint32 CFR                     : 1;  /* [0]            r/w1c      */
           uint32 CFF                     : 1;  /* [1]            r/w1c      */
           uint32 RSVD_7_2                : 6;  /* [7:2]                     */
           uint32 COUT                    : 1;  /* [8]            ro         */
           uint32 RSVD_31_9               :23;  /* [31:9]                    */
    } CMP_CSR;

};    /*cmp_reg*/

struct Reg_Cmp_W {
    /* 0x0*/
    uint32 CMP_VERID;
    /* 0x4*/
    uint32 CMP_PARAM;
    /* 0x8*/
    uint32 CMP_CCR0;
    /* 0xC*/
    uint32 CMP_CCR1;
    /* 0x10*/
    uint32 CMP_CCR2;
    /* 0x14*/
    uint32 CMP_DCR;
    /* 0x18*/
    uint32 CMP_IER;
    /* 0x1C*/
    uint32 CMP_CSR;
};    /*cmp_reg*/

typedef volatile struct Reg_Cmp_Bf Reg_Cmp_BfType;
typedef volatile struct Reg_Cmp_W  Reg_Cmp_WType;

struct Reg_Cmu_Bf {
    /* 0x0*/
    uint32 zResverd0x0;
    /* 0x4*/
    uint32 zResverd0x4;
    /* 0x8*/
    struct {
           uint32 CME                     : 1;  /* [0]            r/w        */
           uint32 RSVD_3_1                : 3;  /* [3:1]          ro         */
           uint32 CMMD                    : 1;  /* [4]            r/w        */
           uint32 RSVD_7_5                : 3;  /* [7:5]          ro         */
           uint32 RSVD_8                  : 1;  /* [8]            r/w        */
           uint32 RSVD_9                  : 1;  /* [9]            r/w        */
           uint32 RSVD_15_10              : 6;  /* [15:10]        ro         */
           uint32 FAHTIE                  : 1;  /* [16]           r/w        */
           uint32 FBLTIE                  : 1;  /* [17]           r/w        */
           uint32 RSVD_30_18              :13;  /* [30:18]        ro         */
           uint32 LOCK                    : 1;  /* [31]           r/w        */
    } CMU_CTRL;

    /* 0xC*/
    struct {
           uint32 MONST                   : 2;  /* [1:0]          ro         */
           uint32 RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32 STARTMEA                : 1;  /* [4]            r/w        */
           uint32 RSVD_15_5               :11;  /* [15:5]         ro         */
           uint32 FAHTIF                  : 1;  /* [16]           w1c        */
           uint32 FBLTIF                  : 1;  /* [17]           w1c        */
           uint32 RSVD_31_18              :14;  /* [31:18]        ro         */
    } CMU_STAT;

    /* 0x10*/
    struct {
           uint32 MONWIN                  :32;  /* [31:0]         r/w        */
    } CMU_MONWIN;

    /* 0x14*/
    struct {
           uint32 HCT4INT                 :32;  /* [31:0]         r/w        */
    } CMU_CUMHCT4INT;

    /* 0x18*/
    struct {
           uint32 LCT4INT                 :32;  /* [31:0]         r/w        */
    } CMU_CUMLCT4INT;

    /* 0x1C*/
    uint32 zResverd0x1C;

    /* 0x20*/
    uint32 zResverd0x20;

    /* 0x24*/
    struct {
           uint32 MEARSLT                 :32;  /* [31:0]         ro         */
    } CMU_CUMMEARSLT;

};    /*cmu_reg*/

struct Reg_Cmu_W {
    /* 0x0*/
    uint32 zResverd0x0;
    /* 0x4*/
    uint32 zResverd0x4;
    /* 0x8*/
    uint32 CMU_CTRL;
    /* 0xC*/
    uint32 CMU_STAT;
    /* 0x10*/
    uint32 CMU_MONWIN;
    /* 0x14*/
    uint32 CMU_CUMHCT4INT;
    /* 0x18*/
    uint32 CMU_CUMLCT4INT;
    /* 0x1C*/
    uint32 zResverd0x1C;
    /* 0x20*/
    uint32 zResverd0x20;
    /* 0x24*/
    uint32 CMU_CUMMEARSLT;
};    /*cmu_reg*/

typedef volatile struct Reg_Cmu_Bf Reg_Cmu_BfType;
typedef volatile struct Reg_Cmu_W  Reg_Cmu_WType;

struct Reg_Crc_Bf {
    /* 0x0*/
    uint32 zResverd0x0;
    /* 0x4*/
    uint32 zResverd0x4;
    /* 0x8*/
    struct {
           uint32 BYTE0                   : 8;  /* [7:0]          r/w        */
           uint32 BYTE1                   : 8;  /* [15:8]         r/w        */
           uint32 BYTE2                   : 8;  /* [23:16]        r/w        */
           uint32 BYTE3                   : 8;  /* [31:24]        r/w        */
    } CRC_DATA;

    /* 0xC*/
    struct {
           uint32 LPHW                    :16;  /* [15:0]         r/w        */
           uint32 HPHW                    :16;  /* [31:16]        r/w        */
    } CRC_POLY;

    /* 0x10*/
    struct {
           uint32 MODE                    : 1;  /* [0]            r/w        */
           uint32 WS                      : 1;  /* [1]            r/w        */
           uint32 CR                      : 1;  /* [2]            r/w        */
           uint32 RSVD_3                  : 1;  /* [3]            ro         */
           uint32 RT                      : 2;  /* [5:4]          r/w        */
           uint32 WT                      : 2;  /* [7:6]          r/w        */
           uint32 RSVD_30_8               :23;  /* [30:8]         ro         */
           uint32 LOCK                    : 1;  /* [31]           r/w        */
    } CRC_CTRL;

};    /*crc_reg*/

struct Reg_Crc_W {
    /* 0x0*/
    uint32 zResverd0x0;
    /* 0x4*/
    uint32 zResverd0x4;
    /* 0x8*/
    uint32 CRC_DATA;
    /* 0xC*/
    uint32 CRC_POLY;
    /* 0x10*/
    uint32 CRC_CTRL;
};    /*crc_reg*/

typedef volatile struct Reg_Crc_Bf Reg_Crc_BfType;
typedef volatile struct Reg_Crc_W  Reg_Crc_WType;

struct Reg_Ctimer_Bf {
    /* 0x0*/
    struct {
           uint32 EN                      : 1;  /* [0]            r/w        */
           uint32 FILTER                  : 4;  /* [ 4:1]          r/w        */
           uint32 CH_SEL_TIM1             : 2;  /* [6:5]          r/w        */
           uint32 RSVD_15_7               : 9;  /* [15:7]         ro         */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } CTIMER_CONF0;

    /* 0x4*/
    struct {
           uint32 EDGE_MOD_0              : 2;  /* [1:0]          r/w        */
           uint32 EDGE_MOD_1              : 2;  /* [3:2]          r/w        */
           uint32 EDGE_MOD_2              : 2;  /* [5:4]          r/w        */
           uint32 RSVD_7_6                : 2;  /* [7:6]          ro         */
           uint32 TIM_CLR_SEL_0           : 2;  /* [9:8 ]          r/w        */
           uint32 TIM_CLR_SEL_1           : 2;  /* [11:10]        r/w        */
           uint32 TIM_CLR_SEL_2           : 2;  /* [13:12]        r/w        */
           uint32 RSVD_15_14              : 2;  /* [15:14]        ro         */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } CTIMER_CONF1;

    /* 0x8*/
    struct {
           uint32 INT_EN_REDGE_0          : 1;  /* [0]            r/w        */
           uint32 INT_EN_REDGE_1          : 1;  /* [1]            r/w        */
           uint32 INT_EN_REDGE_2          : 1;  /* [2]            r/w        */
           uint32 RSVD_3                  : 1;  /* [3]            ro         */
           uint32 INT_EN_FEDGE_0          : 1;  /* [4]            r/w        */
           uint32 INT_EN_FEDGE_1          : 1;  /* [5]            r/w        */
           uint32 INT_EN_FEDGE_2          : 1;  /* [6]            r/w        */
           uint32 RSVD_7                  : 1;  /* [7]            ro         */
           uint32 INT_EN_OVF_0            : 1;  /* [8]            r/w        */
           uint32 INT_EN_OVF_1            : 1;  /* [9]            r/w        */
           uint32 INT_EN_OVF_2            : 1;  /* [10]           r/w        */
           uint32 RSVD_15_11              : 5;  /* [15:11]        ro         */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } CTIMER_INT_CTRL;

    /* 0xC*/
    struct {
           uint32 INT_CLR_REDGE_0         : 1;  /* [0]            wo         */
           uint32 INT_CLR_REDGE_1         : 1;  /* [1]            wo         */
           uint32 INT_CLR_REDGE_2         : 1;  /* [2]            wo         */
           uint32 RSVD_3                  : 1;  /* [3]            ro         */
           uint32 INT_CLR_FEDGE_0         : 1;  /* [4]            wo         */
           uint32 INT_CLR_FEDGE_1         : 1;  /* [5]            wo         */
           uint32 INT_CLR_FEDGE_2         : 1;  /* [6]            wo         */
           uint32 RSVD_7                  : 1;  /* [7]            ro         */
           uint32 INT_CLR_OVF_0           : 1;  /* [8]            wo         */
           uint32 INT_CLR_OVF_1           : 1;  /* [9]            wo         */
           uint32 INT_CLR_OVF_2           : 1;  /* [10]           wo         */
           uint32 RSVD_15_11              : 5;  /* [15:11]        ro         */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } CTIMER_INT_CLR;

    /* 0x10*/
    struct {
           uint32 INT_REDGE_0             : 1;  /* [0]            ro         */
           uint32 INT_REDGE_1             : 1;  /* [1]            ro         */
           uint32 INT_REDGE_2             : 1;  /* [2]            ro         */
           uint32 RSVD_3                  : 1;  /* [3]            ro         */
           uint32 INT_FEDGE_0             : 1;  /* [4]            ro         */
           uint32 INT_FEDGE_1             : 1;  /* [5]            ro         */
           uint32 INT_FEDGE_2             : 1;  /* [6]            ro         */
           uint32 RSVD_7                  : 1;  /* [7]            ro         */
           uint32 INT_OVF_0               : 1;  /* [8]            ro         */
           uint32 INT_OVF_1               : 1;  /* [9]            ro         */
           uint32 INT_OVF_2               : 1;  /* [10]           ro         */
           uint32 RSVD_15_11              : 5;  /* [15:11]        ro         */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } CTIMER_INT_STS;

    /* 0x14*/
    struct {
           uint32 OVF_0                   :16;  /* [15:0]         r/w        */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } CTIMER_OVF_0;

    /* 0x18*/
    struct {
           uint32 OVF_1                   :16;  /* [15:0]         r/w        */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } CTIMER_OVF_1;

    /* 0x1C*/
    struct {
           uint32 OVF_2                   :16;  /* [15:0]         r/w        */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } CTIMER_OVF_2;

    /* 0x20*/
    struct {
           uint32 RCAP_0                  :16;  /* [15:0]         ro         */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } CTIMER_RCAP_0;

    /* 0x24*/
    struct {
           uint32 RCAP_1                  :16;  /* [15:0]         ro         */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } CTIMER_RCAP_1;

    /* 0x28*/
    struct {
           uint32 RCAP_2                  :16;  /* [15:0]         ro         */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } CTIMER_RCAP_2;

    /* 0x2C*/
    struct {
           uint32 FCAP_0                  :16;  /* [15:0]         ro         */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } CTIMER_FCAP_0;

    /* 0x30*/
    struct {
           uint32 FCAP_1                  :16;  /* [15:0]         ro         */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } CTIMER_FCAP_1;

    /* 0x34*/
    struct {
           uint32 FCAP_2                  :16;  /* [15:0]         ro         */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } CTIMER_FCAP_2;

};    /*ctimer_reg*/

struct Reg_Ctimer_W {
    /* 0x0*/
    uint32 CTIMER_CONF0;
    /* 0x4*/
    uint32 CTIMER_CONF1;
    /* 0x8*/
    uint32 CTIMER_INT_CTRL;
    /* 0xC*/
    uint32 CTIMER_INT_CLR;
    /* 0x10*/
    uint32 CTIMER_INT_STS;
    /* 0x14*/
    uint32 CTIMER_OVF_0;
    /* 0x18*/
    uint32 CTIMER_OVF_1;
    /* 0x1C*/
    uint32 CTIMER_OVF_2;
    /* 0x20*/
    uint32 CTIMER_RCAP_0;
    /* 0x24*/
    uint32 CTIMER_RCAP_1;
    /* 0x28*/
    uint32 CTIMER_RCAP_2;
    /* 0x2C*/
    uint32 CTIMER_FCAP_0;
    /* 0x30*/
    uint32 CTIMER_FCAP_1;
    /* 0x34*/
    uint32 CTIMER_FCAP_2;
};    /*ctimer_reg*/

typedef volatile struct Reg_Ctimer_Bf Reg_Ctimer_BfType;
typedef volatile struct Reg_Ctimer_W  Reg_Ctimer_WType;

struct Reg_Dma_Bf {
    /* 0x00*/
    struct {
           uint32 HALT                    : 1;  /* [0]            r/w        */
           uint32 HOEE                    : 1;  /* [1]            r/w        */
           uint32 RSVD_2                  : 1;  /* [2]            r/w        */
           uint32 DBGE                    : 1;  /* [3]            r/w        */
           uint32 RSVD_5_4                : 2;  /* [5:4]                     */
           uint32 BUSY                    : 1;  /* [6]            r/o        */
           uint32 RSVD_31_7               :25;  /* [31:7]                    */
    } DMA_CONF;

    /* 0x04*/
    struct {
           uint32 DMAE0                   : 1;  /* [0]            r/w        */
           uint32 DMAE1                   : 1;  /* [1]            r/w        */
           uint32 DMAE2                   : 1;  /* [2]            r/w        */
           uint32 DMAE3                   : 1;  /* [3]            r/w        */
           uint32 RSVD_31_4               :28;  /* [31:4]                    */
    } DMA_DMAE;

    uint8 zResverd0x08[4];   /*pad 0x08 - 0B*/

    /* 0x0C*/
    struct {
           uint32 EIE0                    : 1;  /* [0]            r/w        */
           uint32 EIE1                    : 1;  /* [1]            r/w        */
           uint32 EIE2                    : 1;  /* [2]            r/w        */
           uint32 EIE3                    : 1;  /* [3]            r/w        */
           uint32 RSVD_31_4               :28;  /* [31:4]                    */
    } DMA_EIE;

    uint8 zResverd0x010[4];   /*pad 0x010 - 013*/

    /* 0x14*/
    struct {
           uint32 CCDONE                  : 2;  /* [1:0]          w/o        */
           uint32 RSVD_5_2                : 4;  /* [5:2]                     */
           uint32 CACDONE                 : 1;  /* [6]            w/o        */
           uint32 WPEN0                   : 1;  /* [7]            w/o        */
           uint32 SCSTART                 : 2;  /* [9:8]          w/o        */
           uint32 RSVD_13_10              : 4;  /* [13:10]                   */
           uint32 SACSTART                : 1;  /* [14]           w/o        */
           uint32 WPEN1                   : 1;  /* [15]           w/o        */
           uint32 CCES                    : 2;  /* [17:16]        w/o        */
           uint32 RSVD_21_18              : 4;  /* [21:18]                   */
           uint32 CACES                   : 1;  /* [22]           w/o        */
           uint32 WPEN2                   : 1;  /* [23]           w/o        */
           uint32 CCIS                    : 2;  /* [25:24]        w/o        */
           uint32 RSVD_29_26              : 4;  /* [29:26]                   */
           uint32 CACIS                   : 1;  /* [30]           w/o        */
           uint32 WPEN3                   : 1;  /* [31]           w/o        */
    } DMA_GCC;

    /* 0x18*/
    struct {
           uint32 DBEF                    : 1;  /* [0]            r/o        */
           uint32 SBEF                    : 1;  /* [1]            r/o        */
           uint32 RSVD_2                  : 1;  /* [2]                       */
           uint32 NUMEF                   : 1;  /* [3]            r/o        */
           uint32 DOEF                    : 1;  /* [4]            r/o        */
           uint32 DAEF                    : 1;  /* [5]            r/o        */
           uint32 SOEF                    : 1;  /* [6]            r/o        */
           uint32 SAEF                    : 1;  /* [7]            r/o        */
           uint32 CHEF                    : 2;  /* [9:8]          r/o        */
           uint32 RSVD_12_10              : 3;  /* [12:10]                   */
           uint32 PRIEF                   : 1;  /* [13]           r/o        */
           uint32 RSVD_14                 : 1;  /* [14]                      */
           uint32 ERRF                    : 1;  /* [15]           r/o        */
           uint32 RSVD_31_16              :16;  /* [31:16]                   */
    } DMA_ES;

    /* 0x1C*/
    struct {
           uint32 ERR0                    : 1;  /* [0]            W1C        */
           uint32 ERR1                    : 1;  /* [1]            W1C        */
           uint32 ERR2                    : 1;  /* [2]            W1C        */
           uint32 ERR3                    : 1;  /* [3]            W1C        */
           uint32 RSVD_31_4               :28;  /* [31:4]                    */
    } DMA_CES;

    /* 0x20*/
    struct {
           uint32 INT0                    : 1;  /* [0]            W1C        */
           uint32 INT1                    : 1;  /* [1]            W1C        */
           uint32 INT2                    : 1;  /* [2]            W1C        */
           uint32 INT3                    : 1;  /* [3]            W1C        */
           uint32 RSVD_31_4               :28;  /* [31:4]                    */
    } DMA_CIS;

    /* 0x24*/
    struct {
           uint32 HRS0                    : 1;  /* [0]            r/o        */
           uint32 HRS1                    : 1;  /* [1]            r/o        */
           uint32 HRS2                    : 1;  /* [2]            r/o        */
           uint32 HRS3                    : 1;  /* [3]            r/o        */
           uint32 RSVD_31_4               :28;  /* [31:4]                    */
    } DMA_CHRS;

    /* 0x28*/
    struct {
           uint32 CPRI0                   : 2;  /* [1:0]          r/w        */
           uint32 RSVD_7_2                : 6;  /* [7:2]                     */
           uint32 CPRI1                   : 2;  /* [9:8]          r/w        */
           uint32 RSVD_15_10              : 6;  /* [15:10]                   */
           uint32 CPRI2                   : 2;  /* [17:16]        r/w        */
           uint32 RSVD_23_18              : 6;  /* [23:18]                   */
           uint32 CPRI3                   : 2;  /* [25:24]        r/w        */
           uint32 RSVD_31_26              : 6;  /* [31:26]                   */
    } DMA_CPRI0;

    uint8 zResverd0x02C[468];   /*pad 0x02C - 01FF*/

    /* 0x200*/
    struct {
    struct {
           uint32 SADDR                   :32;  /* [31:0]         r/w        */
    } DMA_SADDR;

    /* 0x204*/
    struct {
           uint32 DADDR                   :32;  /* [31:0]         r/w        */
    } DMA_DADDR;

    /* 0x208*/
    struct {
           uint32 SAOFF                   :16;  /* [15:0]         r/w        */
           uint32 DAOFF                   :16;  /* [31:16]        r/w        */
    } DMA_AOFF;

    /* 0x20C*/
    uint32 zResverd0x20C;
    /* 0x210*/
    struct {
           uint32 NUM                     :32;  /* [31:0]         r/w        */
    } DMA_NUM;

    /* 0x214*/
    uint32 zResverd0x214;
    /* 0x218*/
    struct {
           uint32 START                   : 1;  /* [0]            r/w        */
           uint32 INTE                    : 1;  /* [1]            r/w        */
           uint32 RSVD_2                  : 1;  /* [2]                       */
           uint32 REQDIS                  : 1;  /* [3]            r/w        */
           uint32 RSVD_5_4                : 2;  /* [5:4]                     */
           uint32 BUSY                    : 1;  /* [6]            r/o        */
           uint32 DONE                    : 1;  /* [7]            r/w        */
           uint32 RSVD_23_8               :16;  /* [23:8]         ro         */
           uint32 DSIZE                   : 2;  /* [25:24]        r/w        */
           uint32 RSVD_26                 : 1;  /* [26]                      */
           uint32 SSIZE                   : 2;  /* [28:27]        r/w        */
           uint32 RSVD_31_29              : 3;  /* [31:29]                   */
    } DMA_CS;

    uint8 zResverd[4];
    } DMA_CH_CONFIG[4];

};    /*dma_reg*/

struct Reg_Dma_W {
    /* 0x00*/
    uint32 DMA_CONF;
    /* 0x04*/
    uint32 DMA_DMAE;
    uint8 zResverd0x08[4];   /*pad 0x08 - 0B*/

    /* 0x0C*/
    uint32 DMA_EIE;
    uint8 zResverd0x010[4];   /*pad 0x010 - 013*/

    /* 0x14*/
    uint32 DMA_GCC;
    /* 0x18*/
    uint32 DMA_ES;
    /* 0x1C*/
    uint32 DMA_CES;
    /* 0x20*/
    uint32 DMA_CIS;
    /* 0x24*/
    uint32 DMA_CHRS;
    /* 0x28*/
    uint32 DMA_CPRI0;
    uint8 zResverd0x02C[468];   /*pad 0x02C - 01FF*/

    /* 0x200*/
    struct {
    uint32 DMA_SADDR;
    /* 0x204*/
    uint32 DMA_DADDR;
    /* 0x208*/
    uint32 DMA_AOFF;
    /* 0x20C*/
    uint32 zResverd0x20C;
    /* 0x210*/
    uint32 DMA_NUM;
    /* 0x214*/
    uint32 zResverd0x214;
    /* 0x218*/
    uint32 DMA_CS;
    uint8 zResverd[4];
    } DMA_CH_CONFIG[4];
};    /*dma_reg*/

typedef volatile struct Reg_Dma_Bf Reg_Dma_BfType;
typedef volatile struct Reg_Dma_W  Reg_Dma_WType;

struct Reg_Flash_Bf {
    /* 0x0*/
    struct {
           uint32 RSVD_0                  : 1;  /* [0]            r          */
           uint32 INIT_FAIL               : 1;  /* [1]            r          */
           uint32 CMDABT                  : 1;  /* [2]            r/w1c      */
           uint32 RSVD_4_3                : 2;  /* [4:3]          r          */
           uint32 ACCERR                  : 1;  /* [5]            r/w1c      */
           uint32 PREABT                  : 1;  /* [6]            r/w1c      */
           uint32 CCIF                    : 1;  /* [7]            r/w1c      */
           uint32 RSVD_15_8               : 8;  /* [15:8]         r          */
           uint32 DFDIF                   : 1;  /* [16]           r/w1c      */
           uint32 SFDIF                   : 1;  /* [17]           r/w1c      */
           uint32 RSVD_29_18              :12;  /* [29:18]        r          */
           uint32 DBG_ERSALL_DIS          : 1;  /* [30]           r          */
           uint32 FSEC                    : 1;  /* [31]           r          */
    } FLASH_FSTAT;

    /* 0x4*/
    struct {
           uint32 EE_READ_ECC_EN          : 1;  /* [0]            r/w        */
           uint32 FL_READ_ECC_EN          : 1;  /* [1]            r/w        */
           uint32 RSVD_7_2                : 6;  /* [7:2]          r          */
           uint32 CCIE                    : 1;  /* [8]            r/w        */
           uint32 DFDIE                   : 1;  /* [9]            r/w        */
           uint32 RSVD_10                 : 1;  /* [10]           r/w        */
           uint32 RSVD_14_11              : 4;  /* [14:11]        r          */
           uint32 CLK_DIV                 : 8;  /* [22:15]        r/w        */
           uint32 RSVD_31_23              : 9;  /* [31:23]        r          */
    } FLASH_FCNFG;

    /* 0x8*/
    struct {
           uint32 RSVD_15_0               :16;  /* [15:0]         r          */
           uint32 FECCF                   : 1;  /* [16]           r/w        */
           uint32 BK_QUERY                : 1;  /* [17]           r/w        */
           uint32 RSVD_23_18              : 6;  /* [23:18]        r          */
           uint32 ABTREQ                  : 1;  /* [24]           r/w        */
           uint32 RSVD_31_25              : 7;  /* [31:25]        r          */
    } FLASH_FCTRL;

    /* 0xC*/
    struct {
           uint32 CMDCODE                 : 4;  /* [3:0]          r/w        */
           uint32 RSVD_31_4               :28;  /* [31:4]         r          */
    } FLASH_FCMD;

    /* 0x10*/
    struct {
           uint32 CMDADDR                 :32;  /* [31:0]         r/w        */
    } FLASH_FADDR;

    /* 0x14*/
    struct {
           uint32 CMDDATA0                :32;  /* [31:0]         r/w        */
    } FLASH_FDATA0;

    /* 0x18*/
    struct {
           uint32 CMDDATA1                :32;  /* [31:0]         r/w        */
    } FLASH_FDATA1;

    /* 0x1C*/
    struct {
           uint32 CMDDATA2                :32;  /* [31:0]         r/w        */
    } FLASH_FDATA2;

    /* 0x20*/
    struct {
           uint32 DECRY_KEY0              :32;  /* [31:0]         r/w        */
    } FLASH_DECRY_KEY_R0;

    /* 0x24*/
    struct {
           uint32 DECRY_KEY1              :32;  /* [31:0]         r/w        */
    } FLASH_DECRY_KEY_R1;

    /* 0x28*/
    struct {
           uint32 DECRY_KEY2              :32;  /* [31:0]         r/w        */
    } FLASH_DECRY_KEY_R2;

    /* 0x2c*/
    struct {
           uint32 DECRY_KEY3              :32;  /* [31:0]         r/w        */
    } FLASH_DECRY_KEY_R3;

    /* 0x30*/
    struct {
           uint32 MBE_OVERRUN             : 1;  /* [0]            r          */
           uint32 RSVD_2_1                : 2;  /* [2:1]          r          */
           uint32 MBE_ADDR                :29;  /* [31:3]         r          */
    } FLASH_MBE_STATE;

    /* 0x34*/
    struct {
           uint32 SBE_OVERRUN             : 1;  /* [0]            r          */
           uint32 RSVD_2_1                : 2;  /* [2:1]          r          */
           uint32 SBE_ADDR                :29;  /* [31:3]         r          */
    } FLASH_SBE_STATE;

    /* 0x38*/
    struct {
           uint32 RSVD_2_0                : 3;  /* [2:0]          r          */
           uint32 BED_ADDR_STRT           :29;  /* [31:3]         r/w        */
    } FLASH_BED_ADDR_STRT_RG0;

    /* 0x3c*/
    struct {
           uint32 RSVD_2_0                : 3;  /* [2:0]          r          */
           uint32 BED_ADDR_END            :29;  /* [31:3]         r/w        */
    } FLASH_BED_ADDR_END_RG0;

    /* 0x40*/
    struct {
           uint32 RSVD_2_0                : 3;  /* [2:0]          r          */
           uint32 BED_ADDR_STRT           :29;  /* [31:3]         r/w        */
    } FLASH_BED_ADDR_STRT_RG1;

    /* 0x44*/
    struct {
           uint32 RSVD_2_0                : 3;  /* [2:0]          r          */
           uint32 BED_ADDR_END            :29;  /* [31:3]         r/w        */
    } FLASH_BED_ADDR_END_RG1;

    uint8 zResverd0x048[4];   /*pad 0x048 - 04B*/

    /* 0x4c*/
    struct {
           uint32 RSVD_7_0                : 8;  /* [7:0]          r/w        */
           uint32 NS10_OF_TRCP            :10;  /* [17:8]         r/w        */
           uint32 RSVD_31_18              :14;  /* [31:18]        ro         */
    } FLASH_TIMING_R1;

};    /*flash_reg*/

struct Reg_Flash_W {
    /* 0x0*/
    uint32 FLASH_FSTAT;
    /* 0x4*/
    uint32 FLASH_FCNFG;
    /* 0x8*/
    uint32 FLASH_FCTRL;
    /* 0xC*/
    uint32 FLASH_FCMD;
    /* 0x10*/
    uint32 FLASH_FADDR;
    /* 0x14*/
    uint32 FLASH_FDATA0;
    /* 0x18*/
    uint32 FLASH_FDATA1;
    /* 0x1C*/
    uint32 FLASH_FDATA2;
    /* 0x20*/
    uint32 FLASH_DECRY_KEY_R0;
    /* 0x24*/
    uint32 FLASH_DECRY_KEY_R1;
    /* 0x28*/
    uint32 FLASH_DECRY_KEY_R2;
    /* 0x2c*/
    uint32 FLASH_DECRY_KEY_R3;
    /* 0x30*/
    uint32 FLASH_MBE_STATE;
    /* 0x34*/
    uint32 FLASH_SBE_STATE;
    /* 0x38*/
    uint32 FLASH_BED_ADDR_STRT_RG0;
    /* 0x3c*/
    uint32 FLASH_BED_ADDR_END_RG0;
    /* 0x40*/
    uint32 FLASH_BED_ADDR_STRT_RG1;
    /* 0x44*/
    uint32 FLASH_BED_ADDR_END_RG1;
    uint8 zResverd0x048[4];   /*pad 0x048 - 04B*/

    /* 0x4c*/
    uint32 FLASH_TIMING_R1;
};    /*flash_reg*/

typedef volatile struct Reg_Flash_Bf Reg_Flash_BfType;
typedef volatile struct Reg_Flash_W  Reg_Flash_WType;

struct Reg_Gdu_Bf {
    /* 0x00*/
    struct {
           uint32 VCP_UV_FLT              : 1;  /* [0]            ro         */
           uint32 VSD_OV_FLT              : 1;  /* [1]            ro         */
           uint32 LS1_VDS_FLT             : 1;  /* [2]            ro         */
           uint32 LS2_VDS_FLT             : 1;  /* [3]            ro         */
           uint32 LS3_VDS_FLT             : 1;  /* [4]            ro         */
           uint32 HS1_VDS_FLT             : 1;  /* [5]            ro         */
           uint32 HS2_VDS_FLT             : 1;  /* [6]            ro         */
           uint32 HS3_VDS_FLT             : 1;  /* [7]            ro         */
           uint32 RSVD_31_8               :24;  /* [31:8]                    */
    } GDU_STAT;

    /* 0x04*/
    struct {
           uint32 VCP_UV_IRQ              : 1;  /* [0]            R/W1C      */
           uint32 VCP_UV_IEN              : 1;  /* [1]            r/w        */
           uint32 DRV_VCPUV_DIS           : 1;  /* [2]            r/w        */
           uint32 DRV_VCPUV_RCV           : 1;  /* [3]            r/w        */
           uint32 VSD_OV_IRQ              : 1;  /* [4]            R/W1C      */
           uint32 VSD_OV_IEN              : 1;  /* [5]            r/w        */
           uint32 DRV_VSDOV_DIS           : 1;  /* [6]            r/w        */
           uint32 DRV_VSDOV_RCV           : 1;  /* [7]            r/w        */
           uint32 LS1_VDS_IRQ             : 1;  /* [8]            R/W1C      */
           uint32 LS1_VDS_IEN             : 1;  /* [9]            r/w        */
           uint32 LS1_VDS_RCV             : 1;  /* [10]           r/w        */
           uint32 RSVD_11                 : 1;  /* [11]           ro         */
           uint32 LS2_VDS_IRQ             : 1;  /* [12]           R/W1C      */
           uint32 LS2_VDS_IEN             : 1;  /* [13]           r/w        */
           uint32 LS2_VDS_RCV             : 1;  /* [14]           r/w        */
           uint32 RSVD_15                 : 1;  /* [15]           ro         */
           uint32 LS3_VDS_IRQ             : 1;  /* [16]           R/W1C      */
           uint32 LS3_VDS_IEN             : 1;  /* [17]           r/w        */
           uint32 LS3_VDS_RCV             : 1;  /* [18]           r/w        */
           uint32 RSVD_19                 : 1;  /* [19]           ro         */
           uint32 HS1_VDS_IRQ             : 1;  /* [20]           R/W1C      */
           uint32 HS1_VDS_IEN             : 1;  /* [21]           r/w        */
           uint32 HS1_VDS_RCV             : 1;  /* [22]           r/w        */
           uint32 RSVD_23                 : 1;  /* [23]           ro         */
           uint32 HS2_VDS_IRQ             : 1;  /* [24]           R/W1C      */
           uint32 HS2_VDS_IEN             : 1;  /* [25]           r/w        */
           uint32 HS2_VDS_RCV             : 1;  /* [26]           r/w        */
           uint32 RSVD_27                 : 1;  /* [27]           RO         */
           uint32 HS3_VDS_IRQ             : 1;  /* [28]           R/W1C      */
           uint32 HS3_VDS_IEN             : 1;  /* [29]           r/w        */
           uint32 HS3_VDS_RCV             : 1;  /* [30]           r/w        */
           uint32 RSVD_31                 : 1;  /* [31]                      */
    } GDU_INT;

    /* 0x08*/
    struct {
           uint32 LS1_EN                  : 1;  /* [0]            r/w        */
           uint32 LS1_CMS                 : 1;  /* [1]            r/w        */
           uint32 LS1_ON                  : 1;  /* [2]            r/w        */
           uint32 LS1_DCS_EN              : 1;  /* [3]            r/w        */
           uint32 LS1_VDS_EN              : 1;  /* [4]            r/w        */
           uint32 LS1_DRV_VDS_DIS         : 1;  /* [5]            r/w        */
           uint32 RSVD_7_6                : 2;  /* [7:6]                     */
           uint32 LS2_EN                  : 1;  /* [8]            r/w        */
           uint32 LS2_CMS                 : 1;  /* [9]            r/w        */
           uint32 LS2_ON                  : 1;  /* [10]           r/w        */
           uint32 LS2_DCS_EN              : 1;  /* [11]           r/w        */
           uint32 LS2_VDS_EN              : 1;  /* [12]           r/w        */
           uint32 LS2_DRV_VDS_DIS         : 1;  /* [13]           r/w        */
           uint32 RSVD_15_14              : 2;  /* [15:14]                   */
           uint32 HS1_EN                  : 1;  /* [16]           r/w        */
           uint32 HS1_CMS                 : 1;  /* [17]           r/w        */
           uint32 HS1_ON                  : 1;  /* [18]           r/w        */
           uint32 HS1_DCS_EN              : 1;  /* [19]           r/w        */
           uint32 HS1_VDS_EN              : 1;  /* [20]           r/w        */
           uint32 HS1_DRV_VDS_DIS         : 1;  /* [21]           r/w        */
           uint32 RSVD_23_22              : 2;  /* [23:22]                   */
           uint32 HS2_EN                  : 1;  /* [24]           r/w        */
           uint32 HS2_CMS                 : 1;  /* [25]           r/w        */
           uint32 HS2_ON                  : 1;  /* [26]           r/w        */
           uint32 HS2_DCS_EN              : 1;  /* [27]           r/w        */
           uint32 HS2_VDS_EN              : 1;  /* [28]           r/w        */
           uint32 HS2_DRV_VDS_DIS         : 1;  /* [29]           r/w        */
           uint32 RSVD_31_30              : 2;  /* [31:30]                   */
    } GDU_CTRL1;

    /* 0x0C*/
    struct {
           uint32 LS3_EN                  : 1;  /* [0]            r/w        */
           uint32 LS3_CMS                 : 1;  /* [1]            r/w        */
           uint32 LS3_ON                  : 1;  /* [2]            r/w        */
           uint32 LS3_DCS_EN              : 1;  /* [3]            r/w        */
           uint32 LS3_VDS_EN              : 1;  /* [4]            r/w        */
           uint32 LS3_DRV_VDS_DIS         : 1;  /* [5]            r/w        */
           uint32 RSVD_7_6                : 2;  /* [7:6]                     */
           uint32 HS3_EN                  : 1;  /* [8]            r/w        */
           uint32 HS3_CMS                 : 1;  /* [9]            r/w        */
           uint32 HS3_ON                  : 1;  /* [10]           r/w        */
           uint32 HS3_DCS_EN              : 1;  /* [11]           r/w        */
           uint32 HS3_VDS_EN              : 1;  /* [12]           r/w        */
           uint32 HS3_DRV_VDS_DIS         : 1;  /* [13]           r/w        */
           uint32 RSVD_31_14              :18;  /* [31:14]                   */
    } GDU_CTRL2;

    /* 0x10*/
    struct {
           uint32 VDS_TH                  : 3;  /* [2:0]          r/w        */
           uint32 RSVD_7_3                : 5;  /* [7:3]                     */
           uint32 CCP_TIM                 : 2;  /* [9:8]          r/w        */
           uint32 CCP3_DIS                : 1;  /* [10]           r/w        */
           uint32 CCP2_DIS                : 1;  /* [11]           r/w        */
           uint32 CCP1_DIS                : 1;  /* [12]           r/w        */
           uint32 CCP_MUL                 : 2;  /* [14:13]        r/w        */
           uint32 RSVD_31_15              :17;  /* [31:15]                   */
    } GDU_CTRL3;

    /* 0x14*/
    struct {
           uint32 DLY_MEA_TIM             :12;  /* [11:0]         ro         */
           uint32 DLY_MEA_CLR             : 1;  /* [12]           r/w        */
           uint32 DLY_MEA_CH              : 3;  /* [15:13]        r/w        */
           uint32 DLY_MEA_DIR             : 1;  /* [16]           r/w        */
           uint32 DLY_MEA_RDY             : 1;  /* [17]           ro         */
           uint32 RSVD_31_18              :14;  /* [31:18]                   */
    } GDU_DLY;

    /* 0x18*/
    struct {
           uint32 VDS_BLK                 : 2;  /* [1:0]          r/w        */
           uint32 RSVD_3_2                : 2;  /* [3:2]                     */
           uint32 LS_VDS_FILT             : 2;  /* [5:4]          r/w        */
           uint32 RSVD_7_6                : 2;  /* [7:6]                     */
           uint32 HS_VDS_FILT             : 2;  /* [9:8]          r/w        */
           uint32 RSVD_11_10              : 2;  /* [11:10]                   */
           uint32 VCP_UV_FILT             : 2;  /* [13:12]        r/w        */
           uint32 RSVD_15_14              : 2;  /* [15:14]                   */
           uint32 VSD_OV_FILT             : 2;  /* [17:16]        r/w        */
           uint32 RSVD_31_18              :14;  /* [31:18]                   */
    } GDU_FILT;

    /* 0x1C*/
    struct {
           uint32 DITH_LO                 : 5;  /* [4:0]          r/w        */
           uint32 RSVD_7_5                : 3;  /* [7:5]                     */
           uint32 DITH_UP                 : 5;  /* [12:8]         r/w        */
           uint32 RSVD_15_13              : 3;  /* [15:13]                   */
           uint32 CP_EN                   : 1;  /* [16]           r/w        */
           uint32 RSVD_31_17              :15;  /* [31:17]                   */
    } GDU_CP_CTRL;

};    /*gdu_reg*/

struct Reg_Gdu_W {
    /* 0x00*/
    uint32 GDU_STAT;
    /* 0x04*/
    uint32 GDU_INT;
    /* 0x08*/
    uint32 GDU_CTRL1;
    /* 0x0C*/
    uint32 GDU_CTRL2;
    /* 0x10*/
    uint32 GDU_CTRL3;
    /* 0x14*/
    uint32 GDU_DLY;
    /* 0x18*/
    uint32 GDU_FILT;
    /* 0x1C*/
    uint32 GDU_CP_CTRL;
};    /*gdu_reg*/

typedef volatile struct Reg_Gdu_Bf Reg_Gdu_BfType;
typedef volatile struct Reg_Gdu_W  Reg_Gdu_WType;

struct Reg_Gpio_Bf {
    /* 0x0*/
    struct {
           uint32 PDO                     :32;  /* [31:0]         r/w        */
    } GPIOA_PDOR;

    /* 0x4*/
    struct {
           uint32 PSO                     :32;  /* [31:0]         wo         */
    } GPIOA_PSOR;

    /* 0x8*/
    struct {
           uint32 PCO                     :32;  /* [31:0]         wo         */
    } GPIOA_PCOR;

    /* 0xC*/
    struct {
           uint32 PTO                     :32;  /* [31:0]         wo         */
    } GPIOA_PTOR;

    /* 0x10*/
    struct {
           uint32 PDI                     :32;  /* [31:0]         ro         */
    } GPIOA_PDIR;

    /* 0x14*/
    struct {
           uint32 PDD                     :32;  /* [31:0]         r/w        */
    } GPIOA_PDDR;

    /* 0x18*/
    struct {
           uint32 RSVD_31_0               :32;  /* [31:0]         ro         */
    } GPIOA_PIDR;

};    /*gpio_reg*/

struct Reg_Gpio_W {
    /* 0x0*/
    uint32 GPIOA_PDOR;
    /* 0x4*/
    uint32 GPIOA_PSOR;
    /* 0x8*/
    uint32 GPIOA_PCOR;
    /* 0xC*/
    uint32 GPIOA_PTOR;
    /* 0x10*/
    uint32 GPIOA_PDIR;
    /* 0x14*/
    uint32 GPIOA_PDDR;
    /* 0x18*/
    uint32 GPIOA_PIDR;
};    /*gpio_reg*/

typedef volatile struct Reg_Gpio_Bf Reg_Gpio_BfType;
typedef volatile struct Reg_Gpio_W  Reg_Gpio_WType;

struct Reg_Hwacc_Bf {
    /* 0x0*/
    struct {
           uint32 CLARK_TRANS             : 1;  /* [0]            rw1c       */
           uint32 PARK_TRANS              : 1;  /* [1]            rw1c       */
           uint32 RSVD_2                  : 1;  /* [2]            ro         */
           uint32 PI_IQ                   : 1;  /* [3]            rw1c       */
           uint32 PI_ID                   : 1;  /* [4]            rw1c       */
           uint32 INV_PARK                : 1;  /* [5]            rw1c       */
           uint32 INV_CLARK               : 1;  /* [6]            rw1c       */
           uint32 RSVD_7                  : 1;  /* [7]            ro         */
           uint32 MATH_CMD                : 1;  /* [8]            rw1c       */
           uint32 DIV_NAN                 : 1;  /* [9]            rw1c       */
           uint32 OVERFLOW                : 1;  /* [10]           rw1c       */
           uint32 SQR_ERR                 : 1;  /* [11]           rw1c       */
           uint32 UNDERFLOW               : 1;  /* [12]           rw1c       */
           uint32 RSVD_31_13              :19;  /* [31:13]        ro         */
    } HWACC_INTR_STATE;

    /* 0x4*/
    struct {
           uint32 CLARK_TRANS             : 1;  /* [0]            rw         */
           uint32 PARK_TRANS              : 1;  /* [1]            rw         */
           uint32 RSVD_2                  : 1;  /* [2]            ro         */
           uint32 PI_IQ                   : 1;  /* [3]            rw         */
           uint32 PI_ID                   : 1;  /* [4]            rw         */
           uint32 INV_PARK                : 1;  /* [5]            rw         */
           uint32 INV_CLARK               : 1;  /* [6]            rw         */
           uint32 RSVD_7                  : 1;  /* [7]            ro         */
           uint32 MATH_CMD                : 1;  /* [8]            rw         */
           uint32 DIV_NAN                 : 1;  /* [9]            rw         */
           uint32 OVERFLOW                : 1;  /* [10]           rw         */
           uint32 SQR_ERR                 : 1;  /* [11]           rw         */
           uint32 UNDERFLOW               : 1;  /* [12]           rw         */
           uint32 RSVD_31_13              :19;  /* [31:13]        ro         */
    } HWACC_INTR_ENABLE;

    /* 0x8*/
    struct {
           uint32 DECODE_OPCODE           : 8;  /* [7:0]          rw         */
           uint32 RSVD_22_8               :15;  /* [22:8]         ro         */
           uint32 DECODE_MACHINE          : 1;  /* [23]           rw         */
           uint32 RSVD_31_24              : 8;  /* [31:24]        ro         */
    } HWACC_CTRL_OP;

    /* 0xc*/
    struct {
           uint32 FOC_STATE_RST           : 1;  /* [0]            wo         */
           uint32 RSVD_14_1               :14;  /* [14:1]         ro         */
           uint32 MACHINE_GO              : 1;  /* [15]           wo         */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } HWACC_CTRL_RUN;

    /* 0x10*/
    struct {
           uint32 A_ADDRESS               : 4;  /* [3:0]          rw         */
           uint32 RSVD_7_4                : 4;  /* [7:4]          ro         */
           uint32 B_ADDRESS               : 4;  /* [11:8]         rw         */
           uint32 RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32 C_ADDRESS               : 4;  /* [19:16]        rw         */
           uint32 RSVD_23_20              : 4;  /* [23:20]        ro         */
           uint32 D_ADDRESS               : 4;  /* [27:24]        rw         */
           uint32 RSVD_31_28              : 4;  /* [31:28]        ro         */
    } HWACC_INBASE;

    uint8 zResverd0x014[4];   /*pad 0x014 - 017*/

    /* 0x18*/
    struct {
           uint32 FOC_FSM_STATE           : 4;  /* [3:0]          ro         */
           uint32 ALU_BUSY                : 1;  /* [4]            ro         */
           uint32 RSVD_31_5               :27;  /* [31:5]         ro         */
    } HWACC_STATUS;

    /* 0x1c*/
    struct {
           uint32 SET_VR0                 : 1;  /* [0]            rw         */
           uint32 BYPASS_PU               : 1;  /* [1]            rw         */
           uint32 RSVD_15_2               :14;  /* [15:2]         ro         */
           uint32 THETA                   :16;  /* [31:16]        rw         */
    } HWACC_FOC_CFG;

    /* 0x20*/
    struct {
           uint32 IQ_REF                  :16;  /* [15:0]         rw         */
           uint32 ID_REF                  :16;  /* [31:16]        rw         */
    } HWACC_FOC_IREF;

    /* 0x24*/
    struct {
           uint32 IQ_KP                   :16;  /* [15:0]         rw         */
           uint32 ID_KP                   :16;  /* [31:16]        rw         */
    } HWACC_FOC_IKP;

    /* 0x28*/
    struct {
           uint32 IQ_KI                   :16;  /* [15:0]         rw         */
           uint32 ID_KI                   :16;  /* [31:16]        rw         */
    } HWACC_FOC_IKI;

    /* 0x2c*/
    struct {
           uint32 IQ_I_MAX                :32;  /* [31:0]         ro         */
    } HWACC_FOC_I_IQ_MAX;

    /* 0x30*/
    struct {
           uint32 IQ_I_MIN                :32;  /* [31:0]         ro         */
    } HWACC_FOC_I_IQ_MIN;

    /* 0x34*/
    struct {
           uint32 ID_I_MAX                :32;  /* [31:0]         rw         */
    } HWACC_FOC_I_ID_MAX;

    /* 0x38*/
    struct {
           uint32 ID_I_MIN                :32;  /* [31:0]         rw         */
    } HWACC_FOC_I_ID_MIN;

    /* 0x3c*/
    struct {
           uint32 VS_BASE                 :16;  /* [15:0]         rw         */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } HWACC_FOC_VS_BASE;

    /* 0x40*/
    struct {
           uint32 IQ_PI_MIN               :16;  /* [15:0]         ro         */
           uint32 IQ_PI_MAX               :16;  /* [31:16]        ro         */
    } HWACC_FOC_IQ_LIMIT;

    /* 0x44*/
    struct {
           uint32 ID_PI_MIN               :16;  /* [15:0]         rw         */
           uint32 ID_PI_MAX               :16;  /* [31:16]        rw         */
    } HWACC_FOC_ID_LIMIT;

    /* 0x48*/
    struct {
           uint32 VS_MAX                  :16;  /* [15:0]         rw         */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } HWACC_FOC_VS_MAX;

    /* 0x4c*/
    struct {
           uint32 IA                      :16;  /* [15:0]         rw         */
           uint32 IB                      :16;  /* [31:16]        rw         */
    } HWACC_FOC_CLARKE_RES;

    /* 0x50*/
    struct {
           uint32 IQ                      :16;  /* [15:0]         rw         */
           uint32 ID                      :16;  /* [31:16]        rw         */
    } HWACC_FOC_PARK_RES0;

    /* 0x54*/
    struct {
           uint32 COS                     :16;  /* [15:0]         rw         */
           uint32 SIN                     :16;  /* [31:16]        rw         */
    } HWACC_FOC_PARK_RES1;

    /* 0x58*/
    struct {
           uint32 VQ                      :16;  /* [15:0]         rw         */
           uint32 VD                      :16;  /* [31:16]        rw         */
    } HWACC_FOC_PI_RES;

    /* 0x5c*/
    struct {
           uint32 I_VQ                    :32;  /* [31:0]         rw         */
    } HWACC_FOC_I_VQ;

    /* 0x60*/
    struct {
           uint32 I_VD                    :32;  /* [31:0]         rw         */
    } HWACC_FOC_I_VD;

    /* 0x64*/
    struct {
           uint32 VR1                     :16;  /* [15:0]         rw         */
           uint32 VR2                     :16;  /* [31:16]        rw         */
    } HWACC_FOC_INV_CLARKE_RES;

    /* 0x68*/
    struct {
           uint32 VA                      :16;  /* [15:0]         rw         */
           uint32 VB                      :16;  /* [31:16]        rw         */
    } HWACC_FOC_INV_PARK_RES;

    /* 0x6c*/
    struct {
           uint32 VA_PU                   :16;  /* [15:0]         rw         */
           uint32 VB_PU                   :16;  /* [31:16]        rw         */
    } HWACC_FOC_PU_RES;

    /* 0x70*/
    struct {
           uint32 COMP_REG_L_0            :16;  /* [15:0]         ro         */
           uint32 COMP_REG_H_0            :16;  /* [31:16]        ro         */
    } HWACC_COMPREGS_0;

    /* 0x74*/
    struct {
           uint32 COMP_REG_L_1            :16;  /* [15:0]         ro         */
           uint32 COMP_REG_H_1            :16;  /* [31:16]        ro         */
    } HWACC_COMPREGS_1;

    /* 0x78*/
    struct {
           uint32 GENERAL_REG_L_0         :16;  /* [15:0]         rw         */
           uint32 GENERAL_REG_H_0         :16;  /* [31:16]        rw         */
    } HWACC_GPREGS_0;

    /* 0x7c*/
    struct {
           uint32 GENERAL_REG_L_1         :16;  /* [15:0]         rw         */
           uint32 GENERAL_REG_H_1         :16;  /* [31:16]        rw         */
    } HWACC_GPREGS_1;

};    /*hwacc_reg*/

struct Reg_Hwacc_W {
    /* 0x0*/
    uint32 HWACC_INTR_STATE;
    /* 0x4*/
    uint32 HWACC_INTR_ENABLE;
    /* 0x8*/
    uint32 HWACC_CTRL_OP;
    /* 0xc*/
    uint32 HWACC_CTRL_RUN;
    /* 0x10*/
    uint32 HWACC_INBASE;
    uint8 zResverd0x014[4];   /*pad 0x014 - 017*/

    /* 0x18*/
    uint32 HWACC_STATUS;
    /* 0x1c*/
    uint32 HWACC_FOC_CFG;
    /* 0x20*/
    uint32 HWACC_FOC_IREF;
    /* 0x24*/
    uint32 HWACC_FOC_IKP;
    /* 0x28*/
    uint32 HWACC_FOC_IKI;
    /* 0x2c*/
    uint32 HWACC_FOC_I_IQ_MAX;
    /* 0x30*/
    uint32 HWACC_FOC_I_IQ_MIN;
    /* 0x34*/
    uint32 HWACC_FOC_I_ID_MAX;
    /* 0x38*/
    uint32 HWACC_FOC_I_ID_MIN;
    /* 0x3c*/
    uint32 HWACC_FOC_VS_BASE;
    /* 0x40*/
    uint32 HWACC_FOC_IQ_LIMIT;
    /* 0x44*/
    uint32 HWACC_FOC_ID_LIMIT;
    /* 0x48*/
    uint32 HWACC_FOC_VS_MAX;
    /* 0x4c*/
    uint32 HWACC_FOC_CLARKE_RES;
    /* 0x50*/
    uint32 HWACC_FOC_PARK_RES0;
    /* 0x54*/
    uint32 HWACC_FOC_PARK_RES1;
    /* 0x58*/
    uint32 HWACC_FOC_PI_RES;
    /* 0x5c*/
    uint32 HWACC_FOC_I_VQ;
    /* 0x60*/
    uint32 HWACC_FOC_I_VD;
    /* 0x64*/
    uint32 HWACC_FOC_INV_CLARKE_RES;
    /* 0x68*/
    uint32 HWACC_FOC_INV_PARK_RES;
    /* 0x6c*/
    uint32 HWACC_FOC_PU_RES;
    /* 0x70*/
    uint32 HWACC_COMPREGS_0;
    /* 0x74*/
    uint32 HWACC_COMPREGS_1;
    /* 0x78*/
    uint32 HWACC_GPREGS_0;
    /* 0x7c*/
    uint32 HWACC_GPREGS_1;
};    /*hwacc_reg*/

typedef volatile struct Reg_Hwacc_Bf Reg_Hwacc_BfType;
typedef volatile struct Reg_Hwacc_W  Reg_Hwacc_WType;

struct Reg_Uart_Bf {
    /* 0x0*/
    struct {
           uint32 RBR_LSB                 : 8;  /* [7:0]          ro         */
           uint32 RBR_MSB                 : 1;  /* [8]            ro         */
           uint32 RSVD_31_9               :23;  /* [31:9]                    */
    } UART_RBR;

    /* 0x4*/
    struct {
           uint32 THR_LSB                 : 8;  /* [7:0]          wo         */
           uint32 THR_MSB                 : 1;  /* [8]            wo         */
           uint32 RSVD_31_9               :23;  /* [31:9]                    */
    } UART_THR;

    /* 0x8*/
    struct {
           uint32 DLR                     :16;  /* [15:0]         r/w        */
           uint32 RSVD_31_16              :16;  /* [31:16]                   */
    } UART_DLR;

    /* 0xc*/
    struct {
           uint32 ERBFI                   : 1;  /* [0]            r/w        */
           uint32 ETBEI                   : 1;  /* [1]            r/w        */
           uint32 ELSI                    : 1;  /* [2]            r/w        */
           uint32 EDSSI                   : 1;  /* [3]            r/w        */
           uint32 TOI                     : 1;  /* [4]            r/w        */
           uint32 RSVD_6_5                : 2;  /* [6:5]          ro         */
           uint32 PTIME                   : 1;  /* [7]            r/w        */
           uint32 RSVD_8                  : 1;  /* [8]            ro         */
           uint32 RSVD_9                  : 1;  /* [9]            ro         */
           uint32 RSVD_10                 : 1;  /* [10]           ro         */
           uint32 RSVD_11                 : 1;  /* [11]           ro         */
           uint32 ASYNC_INT_EN            : 1;  /* [12]           r/w        */
           uint32 BYDET_INT_EN            : 1;  /* [13]           r/w        */
           uint32 RSVD_14                 : 1;  /* [14]           ro         */
           uint32 RSVD_31_15              :17;  /* [31:15]        ro         */
    } UART_IER;

    /* 0x10*/
    struct {
           uint32 IID                     : 4;  /* [3:0]          ro         */
           uint32 RSVD_5_4                : 2;  /* [5:4]                     */
           uint32 FIFOSE                  : 2;  /* [7:6]          ro         */
           uint32 RSVD_31_8               :24;  /* [31:8]                    */
    } UART_IIR;

    /* 0x14*/
    struct {
           uint32 FIFOE                   : 1;  /* [0]            rw         */
           uint32 RFIFOR                  : 1;  /* [1]            wo         */
           uint32 XFIFOR                  : 1;  /* [2]            wo         */
           uint32 RSVD_3                  : 1;  /* [3]            rw         */
           uint32 TET                     : 4;  /* [7:4]          rw         */
           uint32 RCVR                    : 4;  /* [11:8]         rw         */
           uint32 RSVD_31_12              :20;  /* [31:12]                   */
    } UART_FCR;

    /* 0x18*/
    struct {
           uint32 DLS                     : 2;  /* [1:0]          r/w        */
           uint32 STOP                    : 1;  /* [2]            r/w        */
           uint32 PEN                     : 1;  /* [3 ]            r/w        */
           uint32 EPS                     : 1;  /* [4]            r/w        */
           uint32 STP                     : 1;  /* [5 ]            r/w        */
           uint32 BC                      : 1;  /* [6]            r/w        */
           uint32 DLAB                    : 1;  /* [7]            r/w        */
           uint32 LBKEN                   : 1;  /* [8]            r/w        */
           uint32 RX_SMP_DLY              : 4;  /* [12:9]         r/w        */
           uint32 LBK_SW                  : 1;  /* [13]           r/w        */
           uint32 IDLE_DET_LENGTH         : 3;  /* [16:14]        r/w        */
           uint32 IDLE_DET_EN             : 1;  /* [17]           r/w        */
           uint32 IDLE_DMA_EN             : 1;  /* [18]           r/w        */
           uint32 DEBUG_EN                : 1;  /* [19]           r/w        */
           uint32 RSVD_20                 : 1;  /* [20]           ro         */
           uint32 UART_LIN_EN             : 1;  /* [21]           r/w        */
           uint32 RSVD_31_22              :10;  /* [31:22]        ro         */
    } UART_LCR;

    /* 0x1c*/
    struct {
           uint32 RSVD_0                  : 1;  /* [0]                       */
           uint32 RTS                     : 1;  /* [1]            r/w        */
           uint32 RSVD_2                  : 1;  /* [2]                       */
           uint32 RSVD_3                  : 1;  /* [3 ]                       */
           uint32 LB                      : 1;  /* [4]            r/w        */
           uint32 AFCE                    : 1;  /* [5 ]            r/w        */
           uint32 RSVD_6                  : 1;  /* [6]            r/w        */
           uint32 RSVD_31_7               :25;  /* [31:7]                    */
    } UART_AFCR;

    /* 0x20*/
    struct {
           uint32 DR                      : 1;  /* [0]            rw1c       */
           uint32 OE                      : 1;  /* [1]            rw1c       */
           uint32 PE                      : 1;  /* [2]            rw1c       */
           uint32 FE                      : 1;  /* [3 ]            rw1c       */
           uint32 BI                      : 1;  /* [4]            rw1c       */
           uint32 THRE                    : 1;  /* [5 ]            r          */
           uint32 TEMT                    : 1;  /* [6]            r          */
           uint32 RFE                     : 1;  /* [7]            rw1c       */
           uint32 ADDR_RCVD               : 1;  /* [8]            rw1c       */
           uint32 ASYNC_INT               : 1;  /* [9]            rw1c       */
           uint32 RSVD_31_10              :22;  /* [31:10]        ro         */
    } UART_LSR;

    /* 0x24*/
    struct {
           uint32 RSVD_3_0                : 4;  /* [3:0]                     */
           uint32 CTS                     : 1;  /* [4]            ro         */
           uint32 RSVD_31_5               :27;  /* [31:5]                    */
    } UART_MSR;

    /* 0x28*/
    struct {
           uint32 LIN_ERR                 : 1;  /* [0]            RO         */
           uint32 WAKEUP_OP_SUCC          : 1;  /* [1]            rw1c       */
           uint32 HEADER_OP_SUCC          : 1;  /* [2]            rw1c       */
           uint32 RSP_OP_SUCC             : 1;  /* [3]            rw1c       */
           uint32 RSVD_31_4               :28;  /* [31:4]                    */
    } UART_LIN_LISR;

    uint8 zResverd0x02C[4];   /*pad 0x02C - 02F*/

    /* 0x30*/
    struct {
           uint32 LIN_ERR_EN              : 1;  /* [0]            r/w        */
           uint32 WAKEUP_OP_SUCC_EN       : 1;  /* [1]            r/w        */
           uint32 HEADER_OP_SUCC_EN       : 1;  /* [2]            r/w        */
           uint32 RSP_OP_SUCC_EN          : 1;  /* [3]            r/w        */
           uint32 RSVD_31_4               :28;  /* [31:4]         ro         */
    } UART_LIN_INT_EN;

    uint8 zResverd0x034[4];   /*pad 0x034 - 037*/

    /* 0x38*/
    struct {
           uint32 SYNC_FIELD_ERROR        : 1;  /* [0]            rw1c       */
           uint32 PID_ERROR               : 1;  /* [1]            rw1c       */
           uint32 CHECKSUM_ERROR          : 1;  /* [2]            rw1c       */
           uint32 TO_ERROR                : 1;  /* [3]            rw1c       */
           uint32 BIT_ERR                 : 1;  /* [4]            rw1c       */
           uint32 WUP_TO                  : 1;  /* [5]            rw1c       */
           uint32 RSVD_31_6               :26;  /* [31:6]                    */
    } UART_LIN_ERR;

    uint8 zResverd0x03C[64];   /*pad 0x03C - 07B*/

    /* 0x7C*/
    struct {
           uint32 BUSY                    : 1;  /* [0]            ro         */
           uint32 TFNF                    : 1;  /* [1]            ro         */
           uint32 TFE                     : 1;  /* [2]            ro         */
           uint32 RFNE                    : 1;  /* [3]            ro         */
           uint32 RFF                     : 1;  /* [4]            ro         */
           uint32 RSVD_7_5                : 3;  /* [7:5]                     */
           uint32 BREAK_LENGTH            : 8;  /* [15:8]         ro         */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } UART_USR;

    /* 0x80*/
    struct {
           uint32 TFL                     : 5;  /* [4:0]                     */
           uint32 RSVD_31_5               :27;  /* [31:5]         ro         */
    } UART_TFL;

    /* 0x84*/
    struct {
           uint32 RFL                     : 5;  /* [4:0]                     */
           uint32 RSVD_31_5               :27;  /* [31:5]         ro         */
    } UART_RFL;

    uint8 zResverd0x088[56];   /*pad 0x088 - 0BF*/

    /* 0xC0*/
    struct {
           uint32 FD                      : 4;  /* [3:0]          r/w        */
           uint32 RSVD_31_4               :28;  /* [31:4]                    */
    } UART_FD;

    /* 0xC4*/
    struct {
           uint32 RAR                     : 8;  /* [7:0]          r/w        */
           uint32 RSVD_31_8               :24;  /* [31:8]                    */
    } UART_RAR;

    /* 0xC8*/
    struct {
           uint32 TAR                     : 8;  /* [7:0]          r/w        */
           uint32 RSVD_31_8               :24;  /* [31:8]                    */
    } UART_TAR;

    /* 0xCC*/
    struct {
           uint32 DLS_E                   : 1;  /* [0]            r/w        */
           uint32 ADDR_MATCH              : 1;  /* [1]            r/w        */
           uint32 SEND_ADDR               : 1;  /* [2]            r/w        */
           uint32 TRANSMIST_MODE          : 1;  /* [3]            r/w        */
           uint32 RSVD_31_4               :28;  /* [31:4]                    */
    } UART_LCR_EXT;

    uint8 zResverd0x0D0[48];   /*pad 0x0D0 - 0FF*/

    /* 0x100*/
    struct {
           uint32 LIN_MODE                : 1;  /* [0]            r/w        */
           uint32 MASTER_MODE             : 1;  /* [1]            r/w        */
           uint32 RSVD_2                  : 1;  /* [2]            ro         */
           uint32 OP_START                : 1;  /* [3 ]            r/w        */
           uint32 RSVD_4                  : 1;  /* [4]            ro         */
           uint32 OP_MODE                 : 2;  /* [6:5]          r/w        */
           uint32 RSVD_11_7               : 5;  /* [11:7]         ro         */
           uint32 AUTO_SYNC_EN            : 1;  /* [12]           r/w        */
           uint32 PID_OVRD_EN             : 1;  /* [13]           r/w        */
           uint32 BIT_ERR_DET_EN          : 1;  /* [14]           r/w        */
           uint32 RSVD_15                 : 1;  /* [15]                      */
           uint32 COLLISION_SAMPLE_DELAY  : 4;  /* [19:16]        r/w        */
           uint32 RSVD_31_20              :12;  /* [31:20]                   */
    } UART_LIN_CTL;

    /* 0x104*/
    struct {
           uint32 RSP_LENGTH              : 4;  /* [3:0]          r/w        */
           uint32 RSP_DIR                 : 1;  /* [4]            r/w        */
           uint32 CHECKSUM_TYPE           : 1;  /* [5]            r/w        */
           uint32 RSVD_7_6                : 2;  /* [7:6]                     */
           uint32 ADD_TO_CNT              : 8;  /* [15:8]                    */
           uint32 RSVD_31_16              :16;  /* [31:16]                   */
    } UART_LIN_RSP_CFG;

    /* 0x108*/
    struct {
           uint32 PID                     : 8;  /* [7:0]          r/w        */
           uint32 RSVD_8                  : 1;  /* [8]                       */
           uint32 LIN_DEL_LENGTH          : 3;  /* [11:9]         r/w        */
           uint32 LBKM                    : 5;  /* [16:12]        r/w        */
           uint32 RSVD_31_17              :15;  /* [31:17]                   */
    } UART_LIN_HEADER_CFG;

    /* 0x10C*/
    struct {
           uint32 WUP_OP_SEL              : 1;  /* [0]            r/w        */
           uint32 WUP_SEND_LEN            : 7;  /* [7: 1]          r/w        */
           uint32 RSVD_15_8               : 8;  /* [15:8]                    */
           uint32 WDR                     :16;  /* [31:16]                   */
    } UART_LIN_WUP_CFG1;

    /* 0x110*/
    struct {
           uint32 WUP_DET_THE_LOW         :12;  /* [11:0]         r/w        */
           uint32 RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32 WUP_DET_THE_HIGH        :12;  /* [27:16]        r/w        */
           uint32 WUP_TO_ACT              : 1;  /* [28]           r/w        */
           uint32 RSVD_31_29              : 3;  /* [31:29]        ro         */
    } UART_LIN_WUP_CFG2;

    /* 0x114*/
    struct {
           uint32 FID0                    : 6;  /* [5:0]          r/w        */
           uint32 RSVD_7_6                : 2;  /* [7:6]                     */
           uint32 FID1                    : 6;  /* [13:8]         r/w        */
           uint32 RSVD_15_14              : 2;  /* [15:14]                   */
           uint32 FID2                    : 6;  /* [21:16]        r/w        */
           uint32 RSVD_23_22              : 2;  /* [23:22]                   */
           uint32 FID3                    : 6;  /* [29:24]        r/w        */
           uint32 RSVD_31_30              : 2;  /* [31:30]                   */
    } UART_LIN_PID_FILTER_0;

    /* 0x118*/
    struct {
           uint32 FID4                    : 6;  /* [5:0]          r/w        */
           uint32 RSVD_7_6                : 2;  /* [7:6]                     */
           uint32 FID5                    : 6;  /* [13:8]         r/w        */
           uint32 RSVD_15_14              : 2;  /* [15:14]                   */
           uint32 FID6                    : 6;  /* [21:16]        r/w        */
           uint32 RSVD_23_22              : 2;  /* [23:22]                   */
           uint32 FID7                    : 6;  /* [29:24]        r/w        */
           uint32 RSVD_31_30              : 2;  /* [31:30]                   */
    } UART_LIN_PID_FILTER_1;

    /* 0x11c*/
    struct {
           uint32 FID8                    : 6;  /* [5:0]          r/w        */
           uint32 RSVD_7_6                : 2;  /* [7:6]                     */
           uint32 FID9                    : 6;  /* [13:8]         r/w        */
           uint32 RSVD_15_14              : 2;  /* [15:14]                   */
           uint32 FID10                   : 6;  /* [21:16]        r/w        */
           uint32 RSVD_23_22              : 2;  /* [23:22]                   */
           uint32 FID11                   : 6;  /* [29:24]        r/w        */
           uint32 RSVD_31_30              : 2;  /* [31:30]                   */
    } UART_LIN_PID_FILTER_2;

    /* 0x120*/
    struct {
           uint32 FID12                   : 6;  /* [5:0]          r/w        */
           uint32 RSVD_7_6                : 2;  /* [7:6]                     */
           uint32 FID13                   : 6;  /* [13:8]         r/w        */
           uint32 RSVD_15_14              : 2;  /* [15:14]                   */
           uint32 FID14                   : 6;  /* [21:16]        r/w        */
           uint32 RSVD_23_22              : 2;  /* [23:22]                   */
           uint32 FID15                   : 6;  /* [29:24]        r/w        */
           uint32 RSVD_31_30              : 2;  /* [31:30]                   */
    } UART_LIN_PID_FILTER_3;

    /* 0x124*/
    struct {
           uint32 FID_VAGUE               : 6;  /* [5:0]          r/w        */
           uint32 RSVD_31_6               :26;  /* [31:6]                    */
    } UART_LIN_PID_FILTER_VAGUE;

    /* 0x128*/
    struct {
           uint32 FID_MASK                :17;  /* [16:0]         r/w        */
           uint32 FID_VAGUE_MASK          : 6;  /* [22:17]        r/w        */
           uint32 LIN_FILTER_EN           : 1;  /* [23]           r/w        */
           uint32 RSVD_31_24              : 8;  /* [31:24]                   */
    } UART_LIN_PID_FILTER_CTRL;

};    /*lin_reg*/

struct Reg_Uart_W {
    /* 0x0*/
    uint32 UART_RBR;
    /* 0x4*/
    uint32 UART_THR;
    /* 0x8*/
    uint32 UART_DLR;
    /* 0xc*/
    uint32 UART_IER;
    /* 0x10*/
    uint32 UART_IIR;
    /* 0x14*/
    uint32 UART_FCR;
    /* 0x18*/
    uint32 UART_LCR;
    /* 0x1c*/
    uint32 UART_AFCR;
    /* 0x20*/
    uint32 UART_LSR;
    /* 0x24*/
    uint32 UART_MSR;
    /* 0x28*/
    uint32 UART_LIN_LISR;
    uint8 zResverd0x02C[4];   /*pad 0x02C - 02F*/

    /* 0x30*/
    uint32 UART_LIN_INT_EN;
    uint8 zResverd0x034[4];   /*pad 0x034 - 037*/

    /* 0x38*/
    uint32 UART_LIN_ERR;
    uint8 zResverd0x03C[64];   /*pad 0x03C - 07B*/

    /* 0x7C*/
    uint32 UART_USR;
    /* 0x80*/
    uint32 UART_TFL;
    /* 0x84*/
    uint32 UART_RFL;

    uint8 zResverd0x088[56];   /*pad 0x088 - 0BF*/

    /* 0xC0*/
    uint32 UART_FD;
    /* 0xC4*/
    uint32 UART_RAR;
    /* 0xC8*/
    uint32 UART_TAR;
    /* 0xCC*/
    uint32 UART_LCR_EXT;
    uint8 zResverd0x0D0[48];   /*pad 0x0D0 - 0FF*/

    /* 0x100*/
    uint32 UART_LIN_CTL;
    /* 0x104*/
    uint32 UART_LIN_RSP_CFG;
    /* 0x108*/
    uint32 UART_LIN_HEADER_CFG;
    /* 0x10C*/
    uint32 UART_LIN_WUP_CFG1;
    /* 0x110*/
    uint32 UART_LIN_WUP_CFG2;
    /* 0x114*/
    uint32 UART_LIN_PID_FILTER_0;
    /* 0x118*/
    uint32 UART_LIN_PID_FILTER_1;
    /* 0x11c*/
    uint32 UART_LIN_PID_FILTER_2;
    /* 0x120*/
    uint32 UART_LIN_PID_FILTER_3;
    /* 0x124*/
    uint32 UART_LIN_PID_FILTER_VAGUE;
    /* 0x128*/
    uint32 UART_LIN_PID_FILTER_CTRL;
};    /*lin_reg*/

typedef volatile struct Reg_Uart_Bf Reg_Uart_BfType;
typedef volatile struct Reg_Uart_W  Reg_Uart_WType;

struct Reg_Linphy_Bf {
    /* 0x0*/
    uint32 zResverd0x0;
    /* 0x4*/
    uint32 zResverd0x4;
    /* 0x8*/
    struct {
           uint32 LINPHYEN                : 1;  /* [0]            r/w        */
           uint32 FAST                    : 1;  /* [1]            r/w        */
           uint32 SRSEL                   : 1;  /* [2]            r/w        */
           uint32 OTACT                   : 2;  /* [4:3]          r/w        */
           uint32 OVACT                   : 2;  /* [6:5]          r/w        */
           uint32 UVACT                   : 2;  /* [8:7]          r/w        */
           uint32 RSVD_10_9               : 2;  /* [10:9]         ro         */
           uint32 RSVD_11                 : 1;  /* [11]           r/w        */
           uint32 RSVD_12                 : 1;  /* [12]           r/w        */
           uint32 PWRON                   : 1;  /* [13]           r/w        */
           uint32 TXCH_CTRL               : 2;  /* [15:14]        r/w        */
           uint32 RXCH_CTRL               : 2;  /* [17:16]        r/w        */
           uint32 RSVD_19_18              : 2;  /* [19:18]        ro         */
           uint32 PHYMODE                 : 1;  /* [20]           r/w        */
           uint32 RSVD_25_21              : 5;  /* [25:21]        ro         */
           uint32 RSVD_27_26              : 2;  /* [27:26]        r/w        */
           uint32 RSVD_31_28              : 4;  /* [31:28]        r/w        */
    } LINPHY_CR;

    /* 0xC*/
    struct {
           uint32 WKUP                    : 1;  /* [0]            r/w1c      */
           uint32 WKUPTO                  : 1;  /* [1]            r/w1c      */
           uint32 DOMDET                  : 1;  /* [2]            r/w1c      */
           uint32 OT                      : 1;  /* [3]            r          */
           uint32 RSVD_4                  : 1;  /* [4]            ro         */
           uint32 OV20                    : 1;  /* [5]            r          */
           uint32 UV                      : 1;  /* [6]            r          */
           uint32 RSVD_31_7               :25;  /* [31:7]         ro         */
    } LINPHY_SR;

    /* 0x10*/
    struct {
           uint32 LWDTH                   :12;  /* [11:0]         r/w        */
           uint32 WKUPIE                  : 1;  /* [12]           r/w        */
           uint32 WKUPTOIE                : 1;  /* [13]           r/w        */
           uint32 TOACT                   : 2;  /* [15:14]        r/w        */
           uint32 HWDTH                   :12;  /* [27:16]        r/w        */
           uint32 RSVD_30_28              : 3;  /* [30:28]        ro         */
           uint32 WUPEN                   : 1;  /* [31]           r/w        */
    } LINPHY_CFGR0;

    /* 0x14*/
    struct {
           uint32 FILTPER                 : 8;  /* [7:0]          r/w        */
           uint32 FILTCNT                 : 3;  /* [10:8]         r/w        */
           uint32 RSVD_31_11              :21;  /* [31:11]        ro         */
    } LINPHY_CFGR1;

    /* 0x18*/
    struct {
           uint32 DOMDETEN                : 1;  /* [0]            r/w        */
           uint32 DOMDETIE                : 1;  /* [1]            r/w        */
           uint32 RSVD_7_2                : 6;  /* [7:2]          ro         */
           uint32 DOMDETTHS               :24;  /* [31:8]         r/w        */
    } LINPHY_CFGR2;

};    /*linphy_reg*/


struct Reg_Linphy_W {
    /* 0x0*/
    uint32 zResverd0x0;
    /* 0x4*/
    uint32 zResverd0x4;
    /* 0x8*/
    uint32 LINPHY_CR;
    /* 0xC*/
    uint32 LINPHY_SR;
    /* 0x10*/
    uint32 LINPHY_CFGR0;
    /* 0x14*/
    uint32 LINPHY_CFGR1;
    /* 0x18*/
    uint32 LINPHY_CFGR2;
};    /*linphy_reg*/

typedef volatile struct Reg_Linphy_Bf Reg_Linphy_BfType;
typedef volatile struct Reg_Linphy_W  Reg_Linphy_WType;

struct Reg_Mcpwm_Bf {
    /* 0x00*/
    struct {
           uint32 CKSRC                   : 2;  /* [1:0]          r/w        */
           uint32 PSDIV                   : 3;  /* [4:2]          r/w        */
           uint32 DBGM                    : 2;  /* [6:5]          r/w        */
           uint32 RSVD_31_7               :25;  /* [31:7]                    */
    } MCPWM_TIMEBASE;

    /* 0x04*/
    struct {
           uint32 CNT                     :16;  /* [15:0]         r/w        */
           uint32 RSVD_31_16              :16;  /* [31:16]                   */
    } MCPWM_CNT[4];

    /* 0x14*/
    struct {
           uint32 MOD                     :16;  /* [15:0]         r/w        */
           uint32 RSVD_31_16              :16;  /* [31:16]                   */
    } MCPWM_MOD[4];

    /* 0x24*/
    struct {
           uint32 DTVAL                   :12;  /* [11:0]         r/w        */
           uint32 RSVD_31_12              :20;  /* [31:12]                   */
    } MCPWM_DTVAL[4];

    /* 0x34*/
    struct {
           uint32 CHOE0                   : 1;  /* [0]            r/w        */
           uint32 CHOE1                   : 1;  /* [1]            r/w        */
           uint32 CHOE2                   : 1;  /* [2]            r/w        */
           uint32 CHOE3                   : 1;  /* [3]            r/w        */
           uint32 CHOE4                   : 1;  /* [4]            r/w        */
           uint32 CHOE5                   : 1;  /* [5]            r/w        */
           uint32 CHOE6                   : 1;  /* [6]            r/w        */
           uint32 CHOE7                   : 1;  /* [7]            r/w        */
           uint32 CNTM0                   : 1;  /* [8]            r/w        */
           uint32 CNTM1                   : 1;  /* [9]            r/w        */
           uint32 CNTM2                   : 1;  /* [10]           r/w        */
           uint32 CNTM3                   : 1;  /* [11]           r/w        */
           uint32 CNTEN0                  : 1;  /* [12]           r/w        */
           uint32 CNTEN1                  : 1;  /* [13]           r/w        */
           uint32 CNTEN2                  : 1;  /* [14]           r/w        */
           uint32 CNTEN3                  : 1;  /* [15]           r/w        */
           uint32 RLDIE0                  : 1;  /* [16]           r/w        */
           uint32 RLDIE1                  : 1;  /* [17]           r/w        */
           uint32 RLDIE2                  : 1;  /* [18]           r/w        */
           uint32 RLDIE3                  : 1;  /* [19]           r/w        */
           uint32 TOIE0                   : 1;  /* [20]           r/w        */
           uint32 TOIE1                   : 1;  /* [21]           r/w        */
           uint32 TOIE2                   : 1;  /* [22]           r/w        */
           uint32 TOIE3                   : 1;  /* [23]           r/w        */
           uint32 RSVD_29_24              : 6;  /* [29:24]                   */
           uint32 WPEN                    : 1;  /* [30]           r/w        */
           uint32 GLBCNTEN                : 1;  /* [31]           r/w        */
    } MCPWM_GLBCR;

    /* 0x38*/
    struct {
           uint32 CH0F                    : 1;  /* [0]            w0c        */
           uint32 CH1F                    : 1;  /* [1]            w0c        */
           uint32 CH2F                    : 1;  /* [2]            w0c        */
           uint32 CH3F                    : 1;  /* [3]            w0c        */
           uint32 CH4F                    : 1;  /* [4]            w0c        */
           uint32 CH5F                    : 1;  /* [5]            w0c        */
           uint32 CH6F                    : 1;  /* [6]            w0c        */
           uint32 CH7F                    : 1;  /* [7]            w0c        */
           uint32 RLDF0                   : 1;  /* [8]            w0c        */
           uint32 RLDF1                   : 1;  /* [9]            w0c        */
           uint32 RLDF2                   : 1;  /* [10]           w0c        */
           uint32 RLDF3                   : 1;  /* [11]           w0c        */
           uint32 TOF0                    : 1;  /* [12]           w0c        */
           uint32 TOF1                    : 1;  /* [13]           w0c        */
           uint32 TOF2                    : 1;  /* [14]           w0c        */
           uint32 TOF3                    : 1;  /* [15]           w0c        */
           uint32 WPDIS                   : 1;  /* [16]           r/w        */
           uint32 RSVD_31_17              :15;  /* [31:17]                   */
    } MCPWM_GLBSR;

    /* 0x3C*/
    struct {
           uint32 CPP                     : 1;  /* [0]            r/w        */
           uint32 RSVD_3_1                : 3;  /* [3:1]                     */
           uint32 CHIE                    : 1;  /* [4]            r/w        */
           uint32 CHF                     : 1;  /* [5]            w0c        */
           uint32 RSVD_6                  : 1;  /* [6]            r/w        */
           uint32 CHOS                    : 1;  /* [7]            r/o        */
           uint32 RSVD_31_8               :24;  /* [31:8]                    */
    } MCPWM_CFG[8];

    /* 0x5C*/
    struct {
           uint32 CV                      :16;  /* [15:0]         r/w        */
           uint32 RSVD_31_16              :16;  /* [31:16]                   */
    } MCPWM_CV[8];

    /* 0x7C*/
    struct {
           uint32 POL0                    : 1;  /* [0]            r/w        */
           uint32 POL1                    : 1;  /* [1]            r/w        */
           uint32 POL2                    : 1;  /* [2]            r/w        */
           uint32 POL3                    : 1;  /* [3]            r/w        */
           uint32 POL4                    : 1;  /* [4]            r/w        */
           uint32 POL5                    : 1;  /* [5]            r/w        */
           uint32 POL6                    : 1;  /* [6]            r/w        */
           uint32 POL7                    : 1;  /* [7]            r/w        */
           uint32 OFFVAL0                 : 1;  /* [8]            r/w        */
           uint32 OFFVAL1                 : 1;  /* [9]            r/w        */
           uint32 OFFVAL2                 : 1;  /* [10]           r/w        */
           uint32 OFFVAL3                 : 1;  /* [11]           r/w        */
           uint32 OFFVAL4                 : 1;  /* [12]           r/w        */
           uint32 OFFVAL5                 : 1;  /* [13]           r/w        */
           uint32 OFFVAL6                 : 1;  /* [14]           r/w        */
           uint32 OFFVAL7                 : 1;  /* [15]           r/w        */
           uint32 RSVD_31_16              :16;  /* [31:16]                   */
    } MCPWM_OUTCR;

    /* 0x80*/
    struct {
           uint32 TRIGE0                  : 2;  /* [1:0]          r/w        */
           uint32 TRIGE1                  : 2;  /* [3:2]          r/w        */
           uint32 TRIGE2                  : 2;  /* [5:4]          r/w        */
           uint32 TRIGE3                  : 2;  /* [7:6]          r/w        */
           uint32 TRIGE4                  : 2;  /* [9:8]          r/w        */
           uint32 TRIGE5                  : 2;  /* [11:10]        r/w        */
           uint32 TRIGE6                  : 2;  /* [13:12]        r/w        */
           uint32 TRIGE7                  : 2;  /* [15:14]        r/w        */
           uint32 INITRIGE                : 1;  /* [16]           r/w        */
           uint32 ENDTRIGE                : 1;  /* [17]           r/w        */
           uint32 TRIGF                   : 1;  /* [18]           w0c        */
           uint32 RSVD_31_19              :13;  /* [31:19]                   */
    } MCPWM_OUTTRIG;

    /* 0x84*/
    struct {
           uint32 CH0OC                   : 1;  /* [0]            r/w        */
           uint32 CH1OC                   : 1;  /* [1]            r/w        */
           uint32 CH2OC                   : 1;  /* [2]            r/w        */
           uint32 CH3OC                   : 1;  /* [3]            r/w        */
           uint32 CH4OC                   : 1;  /* [4]            r/w        */
           uint32 CH5OC                   : 1;  /* [5]            r/w        */
           uint32 CH6OC                   : 1;  /* [6]            r/w        */
           uint32 CH7OC                   : 1;  /* [7]            r/w        */
           uint32 CH0OCV                  : 1;  /* [8]            r/w        */
           uint32 CH1OCV                  : 1;  /* [9]            r/w        */
           uint32 CH2OCV                  : 1;  /* [10]           r/w        */
           uint32 CH3OCV                  : 1;  /* [11]           r/w        */
           uint32 CH4OCV                  : 1;  /* [12]           r/w        */
           uint32 CH5OCV                  : 1;  /* [13]           r/w        */
           uint32 CH6OCV                  : 1;  /* [14]           r/w        */
           uint32 CH7OCV                  : 1;  /* [15]           r/w        */
           uint32 RSVD_31_16              :16;  /* [31:16]                   */
    } MCPWM_OUTSWCR;

    /* 0x88*/
    struct {
           uint32 FCTLEN0                 : 1;  /* [0]            r/w        */
           uint32 DTEN0                   : 1;  /* [1]            r/w        */
           uint32 SYNCEN0                 : 1;  /* [2]            r/w        */
           uint32 ASYMEN0                 : 1;  /* [3]            r/w        */
           uint32 CVSEL0                  : 1;  /* [4]            r/w        */
           uint32 PEC0                    : 1;  /* [5]            r/w        */
           uint32 COMB0                   : 1;  /* [6]            r/w        */
           uint32 RSVD_7                  : 1;  /* [7]                       */
           uint32 FCTLEN1                 : 1;  /* [8]            r/w        */
           uint32 DTEN1                   : 1;  /* [9]            r/w        */
           uint32 SYNCEN1                 : 1;  /* [10]           r/w        */
           uint32 ASYMEN1                 : 1;  /* [11]           r/w        */
           uint32 CVSEL1                  : 1;  /* [12]           r/w        */
           uint32 PEC1                    : 1;  /* [13]           r/w        */
           uint32 COMB1                   : 1;  /* [14]           r/w        */
           uint32 RSVD_15                 : 1;  /* [15]                      */
           uint32 FCTLEN2                 : 1;  /* [16]           r/w        */
           uint32 DTEN2                   : 1;  /* [17]           r/w        */
           uint32 SYNCEN2                 : 1;  /* [18]           r/w        */
           uint32 ASYMEN2                 : 1;  /* [19]           r/w        */
           uint32 CVSEL2                  : 1;  /* [20]           r/w        */
           uint32 PEC2                    : 1;  /* [21]           r/w        */
           uint32 COMB2                   : 1;  /* [22]           r/w        */
           uint32 RSVD_23                 : 1;  /* [23]                      */
           uint32 FCTLEN3                 : 1;  /* [24]           r/w        */
           uint32 DTEN3                   : 1;  /* [25]           r/w        */
           uint32 SYNCEN3                 : 1;  /* [26]           r/w        */
           uint32 ASYMEN3                 : 1;  /* [27]           r/w        */
           uint32 CVSEL3                  : 1;  /* [28]           r/w        */
           uint32 PEC3                    : 1;  /* [29]           r/w        */
           uint32 COMB3                   : 1;  /* [30]           r/w        */
           uint32 RSVD_31                 : 1;  /* [31]                      */
    } MCPWM_PCR;

    /* 0x8C*/
    struct {
           uint32 FIFEN0                  : 1;  /* [0]            r/w        */
           uint32 RSVD_3_1                : 3;  /* [3:1]                     */
           uint32 FLTEN0                  : 1;  /* [4]            r/w        */
           uint32 RSVD_7_5                : 3;  /* [7:5]                     */
           uint32 FLTPOL0                 : 1;  /* [8]            r/w        */
           uint32 RSVD_11_9               : 3;  /* [11:9]                    */
           uint32 FLTIE                   : 1;  /* [12]           r/w        */
           uint32 FLTCM                   : 1;  /* [13]           r/w        */
           uint32 RSVD_15_14              : 2;  /* [15:14]                   */
           uint32 FIFVAL                  : 4;  /* [19:16]        r/w        */
           uint32 FSTATE                  : 1;  /* [20]           r/w        */
           uint32 RSVD_31_21              :11;  /* [31:21]                   */
    } MCPWM_FLTCR;

    /* 0x90*/
    struct {
           uint32 FAULTF0                 : 1;  /* [0]            w0c        */
           uint32 RSVD_3_1                : 1;  /* [3:1]                     */
           uint32 FAULTFA                 : 1;  /* [4]            w0c        */
           uint32 RSVD_5                  : 1;  /* [5]                       */
           uint32 FAULTINA                : 1;  /* [6]            r/o        */
           uint32 RSVD_31_7               :25;  /* [31:7]                    */
    } MCPWM_FLTSR;

    /* 0x94*/
    struct {
           uint32 FLTASS0                 : 1;  /* [0]            r/w        */
           uint32 FLTASS1                 : 1;  /* [1]            r/w        */
           uint32 FLTASS2                 : 1;  /* [2]            r/w        */
           uint32 FLTASS3                 : 1;  /* [3]            r/w        */
           uint32 FLTASS4                 : 1;  /* [4]            r/w        */
           uint32 FLTASS5                 : 1;  /* [5]            r/w        */
           uint32 FLTASS6                 : 1;  /* [6]            r/w        */
           uint32 FLTASS7                 : 1;  /* [7]            r/w        */
           uint32 RSVD_31_8               :24;  /* [31:8]                    */
    } MCPWM_FLTASS;

    /* 0x98*/
    uint32 zResverd0x98;
    /* 0x9C*/
    struct {
           uint32 SWTRIG                  : 1;  /* [0]            r/w        */
           uint32 SYNCOSWC                : 1;  /* [1]            r/w        */
           uint32 SWWRBUF                 : 1;  /* [2]            r/w        */
           uint32 SWRSTCNT                : 1;  /* [3]            r/w        */
           uint32 RSVD_31_4               :28;  /* [31:4]                    */
    } MCPWM_SYNC;

    /* 0xA0*/
    struct {
           uint32 CPWMFCR0                : 1;  /* [0]            r/w        */
           uint32 CPWMFCR1                : 1;  /* [1]            r/w        */
           uint32 CPWMFCR2                : 1;  /* [2]            r/w        */
           uint32 CPWMFCR3                : 1;  /* [3]            r/w        */
           uint32 CPWMHCR0                : 1;  /* [4]            r/w        */
           uint32 CPWMHCR1                : 1;  /* [5]            r/w        */
           uint32 CPWMHCR2                : 1;  /* [6]            r/w        */
           uint32 CPWMHCR3                : 1;  /* [7]            r/w        */
           uint32 LOADEN0                 : 1;  /* [8]            r/w        */
           uint32 LOADEN1                 : 1;  /* [9]            r/w        */
           uint32 LOADEN2                 : 1;  /* [10]           r/w        */
           uint32 LOADEN3                 : 1;  /* [11]           r/w        */
           uint32 LOADMODE                : 1;  /* [12]           r/w        */
           uint32 RSVD_31_13              :19;  /* [31:13]                   */
    } MCPWM_RELOAD;

    /* 0xA4*/
    struct {
           uint32 LDFREQ0                 : 5;  /* [4:0]          r/w        */
           uint32 RSVD_7_5                : 3;  /* [7:5]                     */
           uint32 LDFREQ1                 : 5;  /* [12:8]         r/w        */
           uint32 RSVD_15_13              : 3;  /* [15:13]                   */
           uint32 LDFREQ2                 : 5;  /* [20:16]        r/w        */
           uint32 RSVD_23_21              : 3;  /* [23:21]                   */
           uint32 LDFREQ3                 : 5;  /* [28:24]        r/w        */
           uint32 RSVD_31_29              : 3;  /* [31:29]                   */
    } MCPWM_LDFREQ;

    uint8 zResverd0x0A8[88];   /*pad 0x0A8 - 0FF*/

    /* 0x100*/
    struct {
           uint32 MOD_DITHER              : 5;  /* [4:0]          r/w        */
           uint32 RSVD_31_5               :27;  /* [31:5]                    */
    } MCPWM_MOD_DITHER[4];

    /* 0x110*/
    struct {
           uint32 CV_DITHER               : 5;  /* [4:0]          r/w        */
           uint32 RSVD_31_5               :27;  /* [31:5]                    */
    } MCPWM_CV_DITHER[8];

};    /*mcpwm_reg*/

struct Reg_Mcpwm_W {
    /* 0x00*/
    uint32 MCPWM_TIMEBASE;
    /* 0x04*/
    uint32 MCPWM_CNT[4];
    /* 0x14*/
    uint32 MCPWM_MOD[4];
    /* 0x24*/
    uint32 MCPWM_DTVAL[4];
    /* 0x34*/
    uint32 MCPWM_GLBCR;
    /* 0x38*/
    uint32 MCPWM_GLBSR;
    /* 0x3C*/
    uint32 MCPWM_CFG[8];
    /* 0x5C*/
    uint32 MCPWM_CV[8];
    /* 0x7C*/
    uint32 MCPWM_OUTCR;
    /* 0x80*/
    uint32 MCPWM_OUTTRIG;
    /* 0x84*/
    uint32 MCPWM_OUTSWCR;
    /* 0x88*/
    uint32 MCPWM_PCR;
    /* 0x8C*/
    uint32 MCPWM_FLTCR;
    /* 0x90*/
    uint32 MCPWM_FLTSR;
    /* 0x94*/
    uint32 MCPWM_FLTASS;
    /* 0x98*/
    uint32 zResverd0x98;
    /* 0x9C*/
    uint32 MCPWM_SYNC;
    /* 0xA0*/
    uint32 MCPWM_RELOAD;
    /* 0xA4*/
    uint32 MCPWM_LDFREQ;

    uint8 zResverd0x0A8[88];   /*pad 0x0A8 - 0FF*/

    /* 0x100*/
    uint32 MCPWM_MOD_DITHER[4];
    /* 0x110*/
    uint32 MCPWM_CV_DITHER[8];
};    /*mcpwm_reg*/

typedef volatile struct Reg_Mcpwm_Bf Reg_Mcpwm_BfType;
typedef volatile struct Reg_Mcpwm_W Reg_Mcpwm_WType;

struct Reg_Pmu_Bf {
    /* 0x00*/
    struct {
           uint32 RSVD_30_0               :31;  /* [30:0]         ro         */
           uint32 LOCK                    : 1;  /* [31]           r/w        */
    } PMU_LOCK;

    /* 0x04*/
    struct {
           uint32 LPO_CLK_DIS             : 1;  /* [0]            r/w        */
           uint32 LPO_CLK_READY           : 1;  /* [1]            r          */
           uint32 RSVD_31_2               :30;  /* [31:2]         ro         */
    } PMU_LPO_96K_CFG;

    /* 0x08*/
    uint32 zResverd0x08;
	
    /* 0x0c*/
    struct {
           uint32 ISO_CLR                 : 1;  /* [0]            w1c        */
           uint32 RSVD_31_1               :31;  /* [31:1]         ro         */
    } PMU_ISO_CLR;

    /* 0x10*/
    struct {
           uint32 HVMON_FLT_EN            : 1;  /* [0]            r/w        */
           uint32 HVMON_EN                : 1;  /* [1]            r/w        */
           uint32 RSVD_2                  : 1;  /* [2]            ro         */
           uint32 HVMON_PU_EN             : 1;  /* [3]            r/w        */
           uint32 HVMON_PD_EN             : 1;  /* [4]            r/w        */
           uint32 RSVD_6_5                : 2;  /* [6:5]          ro         */
           uint32 HVMON_FLT_SEL           : 1;  /* [7]            r/w        */
           uint32 HVMON_IE                : 1;  /* [8]            r/w        */
           uint32 HVMON_FLAG              : 1;  /* [9]            w1c        */
           uint32 RSVD_31_10              :22;  /* [31:10]        ro         */
    } PMU_HV_MON_CFG;

    /* 0x14*/
    struct {
           uint32 RSVD_0                  : 1;  /* [0]            ro         */
           uint32 REF1V_BUF_EN            : 1;  /* [1]            r/w        */
           uint32 CYCLIC_CNT_EN           : 1;  /* [2]            r/w        */
           uint32 WKUP_CNT_EN             : 1;  /* [3]            r/w        */
           uint32 CYCLIC_SENSE_SEL        : 1;  /* [4]            r/w        */
           uint32 WKUP_TIMER_IE           : 1;  /* [5]            r/w        */
           uint32 TS_EN                   : 1;  /* [6]            r/w        */
           uint32 OL_ST_FLT_EN            : 1;  /* [7]            r/w        */
           uint32 OV_FLT_EN               : 1;  /* [8]            r/w        */
           uint32 VDDEXT_FAIL_IE          : 1;  /* [9]            r/w        */
           uint32 VAREF_CMP_EN            : 1;  /* [10]           r/w        */
           uint32 VAREF_COMP_FLG          : 1;  /* [11]           w1c        */
           uint32 VAREF_RDY_FLG           : 1;  /* [12]           ro         */
           uint32 VDDP_OK_DET_EN          : 1;  /* [13]           r/w        */
           uint32 VDDP_OK_DET_LPEN        : 1;  /* [14]           r/w        */
           uint32 VDDEXT_OK_DET_EN        : 1;  /* [15]           r/w        */
           uint32 VDDEXT_OK_DET_LPEN      : 1;  /* [16]           r/w        */
           uint32 WKUP_TIMER_INT_FLG      : 1;  /* [17]           w1c        */
           uint32 VDDEXT_RDY_FLG          : 1;  /* [18]           ro         */
           uint32 RSVD_31_19              :13;  /* [31:19]        ro         */
    } PMU_CSR;

    /* 0x18*/
    struct {
           uint32 CYCLIC_DEAD_CNT         : 8;  /* [7:0]          r/w        */
           uint32 RSVD_11_8               : 4;  /* [11:8]         ro         */
           uint32 CYCLIC_SENSE_CNT        : 4;  /* [15:12]        r/w        */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } PMU_CYCLIC_CNT;

    /* 0x1c*/
    struct {
           uint32 AUTO_WKUP_CNT           : 8;  /* [7:0]          r/w        */
           uint32 NORMAL_WKUP_CNT         : 8;  /* [15:8]         r/w        */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } PMU_WKUP_CNT;

    /* 0x20*/
    struct {
           uint32 LDO_VDDC_EN             : 1;  /* [0]            r/w        */
           uint32 LDO_VDDP_EN             : 1;  /* [1]            r/w        */
           uint32 LDO_VDDEXT_EN           : 1;  /* [2]            r/w        */
           uint32 LDO_VDDAVREF_EN         : 1;  /* [3]            r/w        */
           uint32 RSVD_4                  : 1;  /* [4]            ro         */
           uint32 VDDP_STABLE_EN          : 1;  /* [5]            r/w        */
           uint32 VDDEXT_STABLE_EN        : 1;  /* [6]            r/w        */
           uint32 VDDEXT_LPEN             : 1;  /* [7]            r/w        */
           uint32 RSVD_9_8                : 2;  /* [9:8]          ro         */
           uint32 VDDP_IS_STABLE          : 1;  /* [10]           ro         */
           uint32 VDDEXT_IS_STABLE        : 1;  /* [11]           ro         */
           uint32 VDDEXT_IS_OK            : 1;  /* [12]           ro         */
           uint32 VDDP_IS_OK              : 1;  /* [13]           ro         */
           uint32 RSVD_14                 : 1;  /* [14]           ro         */
           uint32 RSVD_15                 : 1;  /* [15]           r/w        */
           uint32 RSVD_16                 : 1;  /* [16]           r/w        */
           uint32 RSVD_17                 : 1;  /* [17]           ro         */
           uint32 VDDP_STABLE_LPEN        : 1;  /* [18]           r/w        */
           uint32 VDDEXT_STABLE_LPEN      : 1;  /* [19]           r/w        */
           uint32 RSVD_30_20              :11;  /* [30:20]        ro         */
           uint32 LOCK                    : 1;  /* [31]           r/w        */
    } PMU_LDO_CFG;

    /* 0x24*/
    struct {
           uint32 VDDC_UV                 : 1;  /* [0]            w1c        */
           uint32 VDDP_UV                 : 1;  /* [1]            w1c        */
           uint32 VDDEXT_UV               : 1;  /* [2]            w1c        */
           uint32 VDDVREF_UV              : 1;  /* [3]            w1c        */
           uint32 RSVD_31_4               :28;  /* [31:4]         ro         */
    } PMU_UV_STATUS;

    /* 0x28*/
    struct {
           uint32 UV_VDDC_EN              : 1;  /* [0]            r/w        */
           uint32 UV_VDDP_EN              : 1;  /* [1]            r/w        */
           uint32 UV_VDDEXT_EN            : 1;  /* [2]            r/w        */
           uint32 UV_VDDVAREF_EN          : 1;  /* [3]            r/w        */
           uint32 RSVD_7_4                : 4;  /* [7:4]          r/w        */
           uint32 UV_VDDC_LPEN            : 1;  /* [8]            r/w        */
           uint32 UV_VDDP_LPEN            : 1;  /* [9]            r/w        */
           uint32 UV_VDDEXT_LPEN          : 1;  /* [10]           r/w        */
           uint32 UV_VDDVREF_LPEN         : 1;  /* [11]           r/w        */
           uint32 UV_VDDC_RE              : 1;  /* [12]           r/w        */
           uint32 UV_VDDP_RE              : 1;  /* [13]           r/w        */
           uint32 RSVD_31_14              :18;  /* [31:14]        ro         */
    } PMU_UV_CFG;

    /* 0x2c*/
    struct {
           uint32 OV_VDDC_EN              : 1;  /* [0]            r/w        */
           uint32 OV_VDDP_EN              : 1;  /* [1]            r/w        */
           uint32 OV_VDDEXT_EN            : 1;  /* [2]            r/w        */
           uint32 OV_VDDVAREF_EN          : 1;  /* [3]            r/w        */
           uint32 OV_VDDC_AON_EN          : 1;  /* [4]            r/w        */
           uint32 RSVD_7_5                : 3;  /* [7:5]          ro         */
           uint32 OV_VDDC_LPEN            : 1;  /* [8]            r/w        */
           uint32 OV_VDDP_LPEN            : 1;  /* [9]            r/w        */
           uint32 OV_VDDEXT_LPEN          : 1;  /* [10]           r/w        */
           uint32 OV_VDDVAREF_LPEN        : 1;  /* [11]           r/w        */
           uint32 OV_VDDC_AON_LPEN        : 1;  /* [12]           r/w        */
           uint32 RSVD_31_13              :19;  /* [31:13]        ro         */
    } PMU_OV_CFG;

    /* 0x30*/
    struct {
           uint32 VDDC_OV                 : 1;  /* [0]            w1c        */
           uint32 VDDP_OV                 : 1;  /* [1]            w1c        */
           uint32 VDDEXT_OV               : 1;  /* [2]            w1c        */
           uint32 VDDVAREF_OV             : 1;  /* [3]            w1c        */
           uint32 VDDCAON_OV              : 1;  /* [4]            w1c        */
           uint32 RSVD_31_5               :27;  /* [31:5]         ro         */
    } PMU_OV_STATUS;

    /* 0x34*/
    struct {
           uint32 OL_VDDC_EN              : 1;  /* [0]            r/w        */
           uint32 OL_VDDP_EN              : 1;  /* [1]            r/w        */
           uint32 OL_VDDEXT_EN            : 1;  /* [2]            r/w        */
           uint32 OL_VDDVAREF_EN          : 1;  /* [3]            r/w        */
           uint32 RSVD_7_4                : 4;  /* [7:4]          ro         */
           uint32 OL_VDDC_LPEN            : 1;  /* [8]            r/w        */
           uint32 OL_VDDP_LPEN            : 1;  /* [9]            r/w        */
           uint32 OL_VDDEXT_LPEN          : 1;  /* [10]           r/w        */
           uint32 OL_VDDVREF_LPEN         : 1;  /* [11]           r/w        */
           uint32 RSVD_31_12              :20;  /* [31:12]        ro         */
    } PMU_OL_CFG;

    /* 0x38*/
    struct {
           uint32 OL_VDDC                 : 1;  /* [0]            w1c        */
           uint32 OL_VDDP                 : 1;  /* [1]            w1c        */
           uint32 OL_VDDEXT               : 1;  /* [2]            w1c        */
           uint32 OL_VDDVREF              : 1;  /* [3]            w1c        */
           uint32 RSVD_31_4               :28;  /* [31:4]         ro         */
    } PMU_OL_STATUS;

    /* 0x3c*/
    uint32 zResverd0x3c;
    /* 0x40*/
    struct {
           uint32 SHORT_VDDC              : 1;  /* [0]            w1c        */
           uint32 SHORT_VDDP              : 1;  /* [1]            w1c        */
           uint32 SHORT_VDDEXT            : 1;  /* [2]            w1c        */
           uint32 RSVD_31_3               :29;  /* [31:3]         ro         */
    } PMU_SHORT_STATUS;

    /* 0x44*/
    struct {
           uint32 OV_FLT_SEL              : 2;  /* [1:0]          r/w        */
           uint32 OL_ST_FLT_SEL           : 2;  /* [3:2]          r/w        */
           uint32 OL_TM_SEL               : 2;  /* [5:4]          r/w        */
           uint32 OL_TM_EXT_SEL           : 2;  /* [7:6]          r/w        */
           uint32 RSVD_31_8               :24;  /* [31:8]         ro         */
    } PMU_MON_FILT_SEL;

    /* 0x48*/
    struct {
           uint32 VDDC_SDBREQ_EN0         : 1;  /* [0]            r/w        */
           uint32 VDDC_SDBREQ_EN1         : 1;  /* [1]            r/w        */
           uint32 VDDP_SDBREQ_EN0         : 1;  /* [2]            r/w        */
           uint32 VDDP_SDBREQ_EN1         : 1;  /* [3]            r/w        */
           uint32 VDDEXT_SDBREQ_EN0       : 1;  /* [4]            r/w        */
           uint32 VDDEXT_SDBREQ_EN1       : 1;  /* [5]            r/w        */
           uint32 VDDEXT_FAIL_STOP_RST_EN : 1;  /* [6]            r/w        */
           uint32 CYCLIC_SENSE_RST_EN     : 1;  /* [7]            r/w        */
           uint32 WKUP_TIMER_TRIG_RST_EN  : 1;  /* [8]            r/w        */
           uint32 CMP_SDBREQ_EN           : 1;  /* [9]            r/w        */
           uint32 GDU_FAIL_SDBREQ_EN      : 1;  /* [10]           r/w        */
           uint32 WDG_SDBREQ_EN           : 1;  /* [11]           r/w        */
           uint32 LOC_SDBREQ_EN           : 1;  /* [12]           r/w        */
           uint32 OT_SDBREQ_EN            : 1;  /* [13]           r/w        */
           uint32 UV_VDDC_SDBREQ_EN       : 1;  /* [14]           r/w        */
           uint32 UV_VDDP_SDBREQ_EN       : 1;  /* [15]           r/w        */
           uint32 LIN_TRIG_RST_EN         : 1;  /* [16]           r/w        */
           uint32 PORTA_RST_EN            : 1;  /* [17]           r/w        */
           uint32 HVMON_RST_EN            : 1;  /* [18]           r/w        */
           uint32 RSVD_31_19              :13;  /* [31:19]        ro         */
    } PMU_STOP_SDBREQ_EN;

    /* 0x4c*/
    struct {
           uint32 BYTE0                   : 8;  /* [7:0]          r/w        */
           uint32 BYTE1                   : 8;  /* [15:8]         r/w        */
           uint32 BYTE2                   : 8;  /* [23:16]        r/w        */
           uint32 BYTE3                   : 8;  /* [31:24]        r/w        */
    } PMU_REGFILE0;

    /* 0x50*/
    struct {
           uint32 BYTE0                   : 8;  /* [7:0]          r/w        */
           uint32 BYTE1                   : 8;  /* [15:8]         r/w        */
           uint32 BYTE2                   : 8;  /* [23:16]        r/w        */
           uint32 RSVD_31_24              : 8;  /* [31:24]        r/w        */
    } PMU_REGFILE1;

    uint8 zResverd0x054[4];   /*pad 0x054 - 057*/

    /* 0x58*/
    struct {
           uint32 CP_REF1V_BUF_EN         : 1;  /* [0]            r/w        */
           uint32 RSVD_13_1               :13;  /* [13:1]         ro         */
           uint32 GDU_TS_EN               : 1;  /* [14]           r/w        */
           uint32 LIN_TS_EN               : 1;  /* [15]           r/w        */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } PMU_MISC_CTRL1;

    /* 0x5c*/
    struct {
           uint32 ATT_VDH_EN              : 1;  /* [0]            r/w        */
           uint32 ATT_VMON_EN             : 1;  /* [1]            r/w        */
           uint32 ATT_VCP_EN              : 1;  /* [2]            r/w        */
           uint32 ATT_VSD_EN              : 1;  /* [3]            r/w        */
           uint32 ATT_VS_EN               : 1;  /* [4]            r/w        */
           uint32 ATT_VDDP_EN             : 1;  /* [5]            r/w        */
           uint32 ATT_EN                  : 1;  /* [6]            r/w        */
           uint32 RSVD_31_7               :25;  /* [31:7]         ro         */
    } PMU_ATTEN_CFG;

    /* 0x60*/
    struct {
           uint32 SYS_FAIL_VDDP_OL        : 1;  /* [0]            w1c        */
           uint32 SYS_FAIL_VDDC_OL        : 1;  /* [1]            w1c        */
           uint32 SYS_FAIL_VDDP_ST        : 1;  /* [2]            w1c        */
           uint32 SYS_FAIL_VDDC_ST        : 1;  /* [3]            w1c        */
           uint32 SYS_FAIL_VDDP_UV        : 1;  /* [4]            w1c        */
           uint32 SYS_FAIL_VDDC_UV        : 1;  /* [5]            w1c        */
           uint32 SYS_FAIL_WDG_5          : 1;  /* [6]            w1c        */
           uint32 SYS_FAIL_ADC_OT         : 1;  /* [7]            w1c        */
           uint32 SYS_FAIL_GDU            : 1;  /* [8]            w1c        */
           uint32 SYS_FAIL_SCC_LOC        : 1;  /* [9]            w1c        */
           uint32 SYS_FAIL_CMP_FAULT      : 1;  /* [10]           w1c        */
           uint32 SUPPLY_FAIL_OVER_5      : 1;  /* [11]           w1c        */
           uint32 RSVD_28_12              :17;  /* [28:12]        ro         */
           uint32 WKUP_TIMER              : 1;  /* [29]           w1c        */
           uint32 WKUP_HVMON              : 1;  /* [30]           w1c        */
           uint32 WKUP_LIN                : 1;  /* [31]           w1c        */
    } PMU_SYS_FAIL_STATUS;
};    /*pmu_reg*/

struct Reg_Pmu_W {
    /* 0x00*/
    uint32 PMU_LOCK;
    /* 0x04*/
    uint32 PMU_LPO_96K_CFG;
    /* 0x08*/
    uint32 zResverd0x08;
    /* 0x0c*/
    uint32 PMU_ISO_CLR;
    /* 0x10*/
    uint32 PMU_HV_MON_CFG;
    /* 0x14*/
    uint32 PMU_CSR;
    /* 0x18*/
    uint32 PMU_CYCLIC_CNT;
    /* 0x1c*/
    uint32 PMU_WKUP_CNT;
    /* 0x20*/
    uint32 PMU_LDO_CFG;
    /* 0x24*/
    uint32 PMU_UV_STATUS;
    /* 0x28*/
    uint32 PMU_UV_CFG;
    /* 0x2c*/
    uint32 PMU_OV_CFG;
    /* 0x30*/
    uint32 PMU_OV_STATUS;
    /* 0x34*/
    uint32 PMU_OL_CFG;
    /* 0x38*/
    uint32 PMU_OL_STATUS;
    /* 0x3c*/
    uint32 zResverd0x3c;
    /* 0x40*/
    uint32 PMU_SHORT_STATUS;
    /* 0x44*/
    uint32 PMU_MON_FILT_SEL;
    /* 0x48*/
    uint32 PMU_STOP_SDBREQ_EN;
    /* 0x4c*/
    uint32 PMU_REGFILE0;
    /* 0x50*/
    uint32 PMU_REGFILE1;
    
    uint8 zResverd0x054[4];   /*pad 0x054 - 057*/
	
    /* 0x58*/
    uint32 PMU_MISC_CTRL1;
    /* 0x5c*/
    uint32 PMU_ATTEN_CFG;
    /* 0x60*/
    uint32 PMU_SYS_FAIL_STATUS;
};    /*pmu_reg*/

typedef volatile struct Reg_Pmu_Bf Reg_Pmu_BfType;
typedef volatile struct Reg_Pmu_W  Reg_Pmu_WType;

struct Reg_Port_Bf {
    /* 0x0*/
    struct {
           uint32 RSVD_15_0               :16;  /* [15:0]         ro         */
           uint32 RSVD_23_16              : 8;  /* [23:16]        ro         */
           uint32 RSVD_31_24              : 8;  /* [31:24]        ro         */
    } PORTA_VERID;

    /* 0x4*/
    struct {
           uint32 RSVD_31_0               :32;  /* [31:0]         ro         */
    } PORTA_PARAM;

    /* 0x8*/
    struct {
           uint32 GPWD                    :32;  /* [31:0]         r/w        */
    } PORTA_GLBDAT;

    /* 0xC*/
    struct {
           uint32 GPWE                    :32;  /* [31:0]         wo         */
    } PORTA_GLBCTL;

    /* 0x10*/
    struct {
           uint32 PS                      : 1;  /* [0]            r/w        */
           uint32 PE                      : 1;  /* [1]            r/w        */
           uint32 RSVD_2                  : 1;  /* [2]            ro         */
           uint32 SRE                     : 1;  /* [3]            r/w        */
           uint32 PFE                     : 1;  /* [4]            r/w        */
           uint32 ODE                     : 1;  /* [5]            r/w        */
           uint32 RSVD_7_6                : 2;  /* [7:6]          ro         */
           uint32 MUX                     : 4;  /* [11:8]         r/w        */
           uint32 RSVD_14_12              : 3;  /* [14:12]        ro         */
           uint32 LK                      : 1;  /* [15]           r/w        */
           uint32 IRQC                    : 4;  /* [19:16]        r/w        */
           uint32 RSVD_22_20              : 3;  /* [22:20]        ro         */
           uint32 ISF                     : 1;  /* [23]           r/w        */
           uint32 FLT                     : 5;  /* [28:24]        r/w        */
           uint32 RSVD_30_29              : 2;  /* [30:29]        ro         */
           uint32 FLTEN                   : 1;  /* [31]           r/w        */
    } PORTA_PCR[16];

    uint8 zResverd0x050[64];   /*pad 0x050 - 08F*/

    /* 0x90*/
    struct {
           uint32 ISF                     :32;  /* [31:0]         r/w        */
    } PORTA_IRQFLG;

};    /*port_reg*/

struct Reg_Port_W {
    /* 0x0*/
    uint32 PORTA_VERID;
    /* 0x4*/
    uint32 PORTA_PARAM;
    /* 0x8*/
    uint32 PORTA_GLBDAT;
    /* 0xC*/
    uint32 PORTA_GLBCTL;
    /* 0x10*/
    uint32 PORTA_PCR[16];
    uint8 zResverd0x050[64];   /*pad 0x050 - 08F*/

    /* 0x90*/
    uint32 PORTA_IRQFLG;
};    /*port_reg*/

typedef volatile struct Reg_Port_Bf Reg_Port_BfType;
typedef volatile struct Reg_Port_W  Reg_Port_WType;

struct Reg_Scc_Bf {
    /* 0x0*/
    uint32 zResverd0x0;
    /* 0x4*/
    uint32 zResverd0x4;
    /* 0x8*/
    struct {
           uint32 RSVD_3_0                : 4;  /* [3:0]          r          */
           uint32 DIVBUS                  : 4;  /* [7:4]          r          */
           uint32 DIVCORE                 : 4;  /* [11:8]         r          */
           uint32 RSVD_15_12              : 4;  /* [15:12]        r          */
           uint32 SCS                     : 3;  /* [18:16]        r          */
           uint32 RSVD_31_19              :13;  /* [31:19]        r          */
    } SCC_CST;

    /* 0xC*/
    struct {
           uint32 RSVD_3_0                : 4;  /* [3:0]          r          */
           uint32 DIVBUS                  : 4;  /* [7:4]          r/w        */
           uint32 DIVCORE                 : 4;  /* [11:8]         r/w        */
           uint32 RSVD_15_12              : 4;  /* [15:12]        r          */
           uint32 SCS                     : 3;  /* [18:16]        r/w        */
           uint32 RSVD_30_19              :12;  /* [30:19]        r          */
           uint32 LOCK                    : 1;  /* [31]           r/w        */
    } SCC_CFG;

    /* 0x10*/
    struct {
           uint32 RSVD_15_0               :16;  /* [15:0]         r          */
           uint32 CLKOUTSEL               : 4;  /* [19:16]        r/w        */
           uint32 RSVD_31_20              :12;  /* [31:20]                   */
    } SCC_CLKOUTCFG;

    uint8 zResverd0x014[44];   /*pad 0x014 - 03F*/

    /* 0x40*/
    struct {
           uint32 EN                      : 1;  /* [0]            r/w        */
           uint32 STOPEN                  : 1;  /* [1]            r/w        */
           uint32 RSVD_8_2                : 7;  /* [8:2]          ro         */
           uint32 CME                     : 1;  /* [9]            r/w        */
           uint32 RSVD_15_10              : 6;  /* [15:10]        ro         */
           uint32 RDY                     : 1;  /* [16]           ro         */
           uint32 SELD                    : 1;  /* [17]           ro         */
           uint32 LOC                     : 1;  /* [18]           w1c        */
           uint32 RSVD_30_19              :12;  /* [30:19]        ro         */
           uint32 LOCK                    : 1;  /* [31]           r/w        */
    } SCC_OSCCS;

    /* 0x44*/
    struct {
           uint32 EXCLKS                  : 1;  /* [0]            r/w        */
           uint32 OLMEN                   : 1;  /* [1]            r/w        */
           uint32 HF_MODE                 : 1;  /* [2]            r/w        */
           uint32 RSVD_7_3                : 5;  /* [7:3]          ro         */
           uint32 ITRIM                   : 2;  /* [9:8]          r/w        */
           uint32 RSVD_11_10              : 2;  /* [11:10]        ro         */
           uint32 NFEN                    : 1;  /* [12]           r/w        */
           uint32 RSVD_30_13              :18;  /* [30:13]        r          */
           uint32 LOCK                    : 1;  /* [31]           r/w        */
    } SCC_OSCCFG;

    uint8 zResverd0x048[56];   /*pad 0x048 - 07F*/

    /* 0x80*/
    struct {
           uint32 EN                      : 1;  /* [0]            r/w        */
           uint32 STOPEN                  : 1;  /* [1]            r/w        */
           uint32 RSVD_8_2                : 7;  /* [8:2]          r          */
           uint32 CME                     : 1;  /* [9]            r/w        */
           uint32 RSVD_15_10              : 6;  /* [15:10]        r          */
           uint32 RDY                     : 1;  /* [16]           r          */
           uint32 SELD                    : 1;  /* [17]           r          */
           uint32 LOC                     : 1;  /* [18]           r/w        */
           uint32 RSVD_30_19              :12;  /* [30:19]        r          */
           uint32 LOCK                    : 1;  /* [31]           r/w        */
    } SCC_FRO48MCS;

    /* 0x84*/
    uint32 zResverd0x84;
    /* 0x88*/
    uint32 zResverd0x88;
    /* 0x8C*/
    uint32 zResverd0x8C;
};    /*scc_reg*/

struct Reg_Scc_W {
    /* 0x0*/
    uint32 zResverd0x0;
    /* 0x4*/
    uint32 zResverd0x4;
    /* 0x8*/
    uint32 SCC_CST;
    /* 0xC*/
    uint32 SCC_CFG;
    /* 0x10*/
    uint32 SCC_CLKOUTCFG;
    uint8 zResverd0x014[44];   /*pad 0x014 - 03F*/

    /* 0x40*/
    uint32 SCC_OSCCS;
    /* 0x44*/
    uint32 SCC_OSCCFG;

    uint8 zResverd0x048[56];   /*pad 0x048 - 07F*/

    /* 0x80*/
    uint32 SCC_FRO48MCS;
    /* 0x84*/
    uint32 zResverd0x84;
    /* 0x88*/
    uint32 zResverd0x88;
    /* 0x8C*/
    uint32 zResverd0x8C;
};    /*scc_reg*/

typedef volatile struct Reg_Scc_Bf Reg_Scc_BfType;
typedef volatile struct Reg_Scc_W  Reg_Scc_WType;

struct Reg_Scm_Bf {
    uint8 zResverd0x00[8];   /*pad 0x00 - 07*/
    /* 0x08*/
    struct {
           uint32 SCM_WRITE_LOCK          :32;  /* [31:0]         r/w        */
    } SCM_WRITE_LOCK;

    uint8 zResverd0x0C[4];   /*pad 0x0C - 0F*/

    /* 0x10*/
    struct {
           uint32 RSVD_3_0                : 4;  /* [3:0]          ro         */
           uint32 CLKOUTSEL               : 3;  /* [6:4]          r/w        */
           uint32 RSVD_7                  : 1;  /* [7]            ro         */
           uint32 CLKOUTDIV               : 3;  /* [10:8]         r/w        */
           uint32 CLKOUTEN                : 1;  /* [11]           r/w        */
           uint32 RSVD_31_12              :20;  /* [31:12]        ro         */
    } SCM_CHIPCTL;

    uint8 zResverd0x014[12];   /*pad 0x014 - 01F*/

    /* 0x20*/
    struct {
           uint32 RSVD_7_0                : 8;  /* [7:0]          ro         */
           uint32 SRAM_INIT_TRIG          : 1;  /* [8]            r/w        */
           uint32 SCM_CMU_CFG             : 1;  /* [9]            r/w        */
           uint32 RSVD_11_10              : 2;  /* [11:10]        ro         */
           uint32 SCM_PWM_CHOUT_SEL       : 1;  /* [12]           r/w        */
           uint32 RSVD_23_13              :11;  /* [23:13]        ro         */
           uint32 SCM_LIN_SEL             : 2;  /* [25:24]        r/w        */
           uint32 SCM_LINPWM_SEL          : 1;  /* [26]           r/w        */
           uint32 RSVD_31_27              : 5;  /* [31:27]        ro         */
    } SCM_MISCCTL1;

    /* 0x24*/
    struct {
           uint32 SRAM_INIT_DONE          : 1;  /* [0]            ro         */
           uint32 RSVD_31_1               :31;  /* [31:1]         ro         */
    } SCM_MISCSTAT1;

    uint8 zResverd0x028[8];   /*pad 0x028 - 02F*/

    /* 0x30*/
    struct {
           uint32 PERI_CLK_EN             :16;  /* [15:0]         r/w        */
           uint32 PERI_WLK                : 1;  /* [16]           r/w        */
           uint32 RSVD_30_17              :14;  /* [30:17]        r          */
           uint32 LOCK                    : 1;  /* [31]           r/w        */
    } SCM_PERI_CTRL;

    /* 0x34*/
    struct {
           uint32 UART_CLK_DIV            : 4;  /* [3:0]          r/w        */
           uint32 UART_CLK_SEL            : 1;  /* [4]            r/w        */
           uint32 RSVD_7_5                : 3;  /* [7:5]          r          */
           uint32 SPI_CLK_DIV             : 4;  /* [11:8]         r/w        */
           uint32 RSVD_31_12              :20;  /* [31:12]        r          */
    } SCM_PERI_CLK;

    uint8 zResverd0x038[24];   /*pad 0x038 - 04F*/

    /* 0x50*/
    struct {
           uint32 RSVD_13_0               : 14;  /* [13:0]         ro        */
           uint32 SCM_PAD_FAULT_INT_EN    : 1;   /* [14]           r/w        */
           uint32 RSVD_22_15              : 8;   /* [22:15]        ro        */
           uint32 SCM_PAD_FLT_POLARITY    : 1;   /* [23]           r/w        */
           uint32 RSVD_31_24              : 8;   /* [31:24]        ro         */
    } SCM_NMI_LVL1_INT_EN;

    /* 0x54*/
    struct {
           uint32 SCM_NMI_LVL2_INT_EN     :16;  /* [15:0]         r/w        */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } SCM_NMI_LVL2_INT_EN;

    /* 0x58*/
    struct {
           uint32 SCM_NMI_LVL1_INT_FLAG   :24;  /* [23:0]         ro        */
           uint32 RSVD_31_24              : 8;  /* [31:24]        ro         */
    } SCM_NMI_LVL1_INT_FLAG;

    /* 0x5C*/
    struct {
           uint32 SCM_NMI_LVL2_INT_FLAG   :16;  /* [15:0]         ro        */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } SCM_NMI_LVL2_INT_FLAG;

    /* 0x60*/
    struct {
           uint32 SRAM_ECCR_DIS           : 1;  /* [0]            r/w        */
           uint32 SRAM_ECCW_DIS           : 1;  /* [1]            r/w        */
           uint32 SRAM_ECCSB_DIS          : 1;  /* [2]            r/w        */
           uint32 SRAM_ECCMB_DIS          : 1;  /* [3]            r/w        */
           uint32 RSVD_31_4               :28;  /* [31:4]         ro         */
    } SCM_ECC_CTRL;

    /* 0x64*/
    struct {
           uint32 SRAM_EFPROT             : 4;  /* [3:0]          ro         */
           uint32 SRAM_EFSIZE             : 3;  /* [6:4]          ro         */
           uint32 SRAM_EFW                : 1;  /* [7]            ro         */
           uint32 SRAM_EFMST              : 4;  /* [11:8]         ro         */
           uint32 RSVD_28_12              :17;  /* [28:12]        ro         */
           uint32 SRAM_SBERR              : 1;  /* [29]           ro         */
           uint32 SRAM_MBERR              : 1;  /* [30]           ro         */
           uint32 SRAM_OVERRUN            : 1;  /* [31]           ro         */
    } SCM_SRAM_ECC_ST;

    /* 0x68*/
    struct {
           uint32 SCM_SRAM_ECC_FADDR      :32;  /* [31:0]         ro         */
    } SCM_SRAM_ECC_FADDR;

    /* 0x6C*/
    struct {
           uint32 SCM_SRAM_ECC_FDATA      :32;  /* [31:0]         ro         */
    } SCM_SRAM_ECC_FDATA;

    uint8 zResverd0x070[32];   /*pad 0x070 - 08F*/

    /* 0x90*/
    struct {
           uint32 SCM_CSA_EN              : 1;  /* [0]            r/w        */
           uint32 RSVD_3_1                : 3;  /* [3:1]          ro         */
           uint32 SCM_CSA_VZERO_CTRL      : 1;  /* [4]            r/w        */
           uint32 RSVD_7_5                : 3;  /* [7:5]          ro         */
           uint32 SCM_CSA_GAIN            : 2;  /* [9:8]          r/w        */
           uint32 RSVD_31_10              : 22;  /* [31:10]        ro         */
    } SCM_CSA_CTRL;

    uint8 zResverd0x094[136];   /*pad 0x094 - 011B*/

    /* 0x11C*/
    struct {
           uint32 CHIP_ID                 : 32;  /* [31:0]          ro         */
    } SCM_DEVID;

    /* 0x120*/
    struct {
           uint32 UID_31_0                :32;  /* [31:0]         ro         */
    } SCM_UNIQUE0;

    /* 0x124*/
    struct {
           uint32 UID_63_32               :32;  /* [31:0]         ro         */
    } SCM_UNIQUE1;

};    /*scm_reg*/

struct Reg_Scm_W {
    uint8 zResverd0x00[8];   /*pad 0x00 - 07*/
    /* 0x08*/
    uint32 SCM_WRITE_LOCK;
    uint8 zResverd0x0C[4];   /*pad 0x0C - 0F*/

    /* 0x10*/
    uint32 SCM_CHIPCTL;
    uint8 zResverd0x014[12];   /*pad 0x014 - 01F*/

    /* 0x20*/
    uint32 SCM_MISCCTL1;
    /* 0x24*/
    uint32 SCM_MISCSTAT1;
    uint8 zResverd0x028[8];   /*pad 0x028 - 02F*/

    /* 0x30*/
    uint32 SCM_PERI_CTRL;
    /* 0x34*/
    uint32 SCM_PERI_CLK;
    uint8 zResverd0x038[24];   /*pad 0x038 - 04F*/
    /* 0x50*/
    uint32 SCM_NMI_LVL1_INT_EN;
    /* 0x54*/
    uint32 SCM_NMI_LVL2_INT_EN;
    /* 0x58*/
    uint32 SCM_NMI_LVL1_INT_FLAG;
    /* 0x5C*/
    uint32 SCM_NMI_LVL2_INT_FLAG;
    /* 0x60*/
    uint32 SCM_ECC_CTRL;
    /* 0x64*/
    uint32 SCM_SRAM_ECC_ST;
    /* 0x68*/
    uint32 SCM_SRAM_ECC_FADDR;
    /* 0x6C*/
    uint32 SCM_SRAM_ECC_FDATA;

    uint8 zResverd0x070[32];   /*pad 0x070 - 08F*/

    /* 0x90*/
    uint32 SCM_CSA_CTRL;
    uint8 zResverd0x094[136];   /*pad 0x094 - 011B*/

    /* 0x11C*/
    uint32 SCM_DEVID;
    /* 0x120*/
    uint32 SCM_UNIQUE0;
    /* 0x124*/
    uint32 SCM_UNIQUE1;
};    /*scm_reg*/

typedef volatile struct Reg_Scm_Bf Reg_Scm_BfType;
typedef volatile struct Reg_Scm_W  Reg_Scm_WType;

struct Reg_Spi_Bf {
    /* 0x0*/
    struct {
           uint32 RSVD_5_0                : 6;  /* [5:0]          ro         */
           uint32 SCPH                    : 1;  /* [6]            r/w        */
           uint32 SCPOL                   : 1;  /* [7]            r/w        */
           uint32 TMOD                    : 2;  /* [9:8]          r/w        */
           uint32 RSVD_10                 : 1;  /* [10]           r/w        */
           uint32 RSVD_11                 : 1;  /* [11]           r/w        */
           uint32 RSVD_15_12              : 4;  /* [15:12]        r/w        */
           uint32 DFS_32                  : 5;  /* [20:16]        r/w        */
           uint32 MST_MODE                : 1;  /* [21]           r/w        */
           uint32 RSVD_22                 : 1;  /* [22]           r/w        */
           uint32 RSVD_23                 : 1;  /* [23]           r/w        */
           uint32 RSVD_24                 : 1;  /* [24]           r/w        */
           uint32 LSB                     : 1;  /* [25]           r/w        */
           uint32 RXFRST                  : 1;  /* [26]           wo         */
           uint32 TXFRST                  : 1;  /* [27]           wo         */
           uint32 RSVD_31_28              : 4;  /* [31:28]        ro         */
    } SPI_CTRLR0;

    /* 0x4*/
    struct {
           uint32 NDF                     :16;  /* [15:0]         r/w        */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } SPI_CTRLR1;

    /* 0x8*/
    struct {
           uint32 SPI_EN                  : 1;  /* [0]            r/w        */
           uint32 RSVD_15_1               :15;  /* [15:1]         ro         */
           uint32 SER                     : 2;  /* [17:16]        r/w        */
           uint32 RSVD_31_18              :14;  /* [31:18]        ro         */
    } SPI_SPIENR;

    /* 0xC*/
    struct {
           uint32 SCKDV                   :16;  /* [15:0]         r/w        */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } SPI_BAUDR;

    /* 0x10*/
    struct {
           uint32 TFT                     : 8;  /* [7:0]          r/w        */
           uint32 RSVD_15_8               : 8;  /* [15:8]         ro         */
           uint32 RFT                     : 8;  /* [23:16]        r/w        */
           uint32 RSVD_31_24              : 8;  /* [31:24]        ro         */
    } SPI_FTLR;

    /* 0x14*/
    struct {
           uint32 TXTFL                   : 3;  /* [2:0]          ro         */
           uint32 RSVD_15_3               :13;  /* [15:3]         ro         */
           uint32 RXTFL                   : 3;  /* [18:16]        ro         */
           uint32 RSVD_31_19              :13;  /* [31:19]        ro         */
    } SPI_FLR;

    /* 0x18*/
    struct {
           uint32 BUSY                    : 1;  /* [0]            ro         */
           uint32 TFNF                    : 1;  /* [1]            ro         */
           uint32 TFE                     : 1;  /* [2]            ro         */
           uint32 RFNE                    : 1;  /* [3]            ro         */
           uint32 RFF                     : 1;  /* [4]            ro         */
           uint32 TXE                     : 1;  /* [5]            ro         */
           uint32 RSVD_6                  : 1;  /* [6]            ro         */
           uint32 RSVD_31_7               :25;  /* [31:7]         ro         */
    } SPI_SR;

    /* 0x1C*/
    struct {
           uint32 TXEIE                   : 1;  /* [0]            r/w        */
           uint32 TXOIE                   : 1;  /* [1]            r/w        */
           uint32 RXUIE                   : 1;  /* [2]            r/w        */
           uint32 RXOIE                   : 1;  /* [3]            r/w        */
           uint32 RXFIE                   : 1;  /* [4]            r/w        */
           uint32 RSVD_5                  : 1;  /* [5]            r/w        */
           uint32 ARXDIE                  : 1;  /* [6]            r/w        */
           uint32 RSVD_31_7               :25;  /* [31:7]         ro         */
    } SPI_IMR;

    /* 0x20*/
    struct {
           uint32 TXEIS                   : 1;  /* [0]            ro         */
           uint32 TXOIS                   : 1;  /* [1]            ro         */
           uint32 RXUIS                   : 1;  /* [2]            ro         */
           uint32 RXOIS                   : 1;  /* [3]            ro         */
           uint32 RXFIS                   : 1;  /* [4]            ro         */
           uint32 RSVD_5                  : 1;  /* [5]            ro         */
           uint32 ARXDIS                  : 1;  /* [6]            ro         */
           uint32 RSVD_15_7               : 9;  /* [15:7]         ro         */
           uint32 TXEIR                   : 1;  /* [16]           ro         */
           uint32 TXOIR                   : 1;  /* [17]           ro         */
           uint32 RXUIR                   : 1;  /* [18]           ro         */
           uint32 RXOIR                   : 1;  /* [19]           ro         */
           uint32 RXFIR                   : 1;  /* [20]           ro         */
           uint32 RSVD_21                 : 1;  /* [21]           ro         */
           uint32 ARXDIR                  : 1;  /* [22]           ro         */
           uint32 RSVD_31_23              : 9;  /* [31:23]        ro         */
    } SPI_ISR;

    /* 0x24*/
    struct {
           uint32 RXUICR                  : 1;  /* [0]            r/w        */
           uint32 RXOICR                  : 1;  /* [1]            r/w        */
           uint32 TXOICR                  : 1;  /* [2]            r/w        */
           uint32 RSVD_3                  : 1;  /* [3]            r/w        */
           uint32 ARXDICR                 : 1;  /* [4]            r/w        */
           uint32 RSVD_31_5               :27;  /* [31:5]         ro         */
    } SPI_ICR;

    uint32 zResverd0x028[4];   /*pad 0x028 - 037*/

    /* 0x38*/
    struct {
           uint32 PCS2SCK                 : 8;  /* [7:0]          r/w        */
           uint32 PCS2SCK_EN              : 1;  /* [8]            r/w        */
           uint32 RSVD_12_9               : 4;  /* [12:9]         ro         */
           uint32 SLV_TXD_ACCELERATE      : 1;  /* [13]           r/w        */
           uint32 CONTINUE_MODE           : 1;  /* [14]           r/w        */
           uint32 RSVD_31_15              :17;  /* [31:15]        ro         */
    } SPI_CTRL2;

    /* 0x3C*/
    struct {
           uint32 DR                      :32;  /* [31:0]         r/w        */
    } SPI_DR_LOW;

    uint8 zResverd0x040[8];   /*pad 0x040 - 047*/

    /* 0x48*/
    struct {
           uint32 DR                      :32;  /* [31:0]         r/w        */
    } SPI_DR_HIGH;

    /* 0x4C*/
    struct {
           uint32 RX_SAMPLE_DLY           : 5;  /* [4:0]          r/w        */
           uint32 RSVD_31_5               :27;  /* [31:5]         r/w        */
    } SPI_RXSDR;

};    /*spi_reg*/

struct Reg_Spi_W {
    /* 0x0*/
    uint32 SPI_CTRLR0;
    /* 0x4*/
    uint32 SPI_CTRLR1;
    /* 0x8*/
    uint32 SPI_SPIENR;
    /* 0xC*/
    uint32 SPI_BAUDR;
    /* 0x10*/
    uint32 SPI_FTLR;
    /* 0x14*/
    uint32 SPI_FLR;
    /* 0x18*/
    uint32 SPI_SR;
    /* 0x1C*/
    uint32 SPI_IMR;
    /* 0x20*/
    uint32 SPI_ISR;
    /* 0x24*/
    uint32 SPI_ICR;
	
    uint32 zResverd0x028[4];   /*pad 0x028 - 037*/

    /* 0x38*/
    uint32 SPI_CTRL2;
    /* 0x3C*/
    uint32 SPI_DR_LOW;
    uint8 zResverd0x040[8];   /*pad 0x040 - 047*/

    /* 0x48*/
    uint32 SPI_DR_HIGH;
    /* 0x4C*/
    uint32 SPI_RXSDR;
};    /*spi_reg*/

typedef volatile struct Reg_Spi_Bf Reg_Spi_BfType;
typedef volatile struct Reg_Spi_W  Reg_Spi_WType;

struct Reg_Srmc_Bf {
    /* 0x00*/
    struct {
           uint32 RSVD_15_0               :16;  /* [15:0]         ro         */
           uint32 RSVD_23_16              : 8;  /* [23:16]        ro         */
           uint32 RSVD_31_24              : 8;  /* [31:24]        ro         */
    } SRMC_VERID;

    /* 0x04*/
    struct {
           uint32 RSVD_0                  : 1;  /* [0]            ro         */
           uint32 RSVD_31_1               :31;  /* [31:1]         ro         */
    } SRMC_PARAM;

    uint8 zResverd0x08[8];   /*pad 0x08 - 0F*/

    /* 0x10*/
    struct {
           uint32 RSTFLTSRW               : 2;  /* [1:0]          r/w        */
           uint32 RSTFLTSS                : 1;  /* [2]            r/w        */
           uint32 RSVD_7_3                : 5;  /* [7:3]          r/w        */
           uint32 RSTFLTSEL               : 5;  /* [12:8]         r/w        */
           uint32 RSVD_30_13              :18;  /* [30:13]        r          */
           uint32 LOCKUP_RST_EN           : 1;  /* [31]           r/w        */
    } SRMC_RST_CTRL;

    /* 0x14*/
    struct {
           uint32 POR                     : 1;  /* [0]            ro         */
           uint32 LVD                     : 1;  /* [1]            ro         */
           uint32 STANDBY_WAKEUP_RST      : 1;  /* [2]            ro         */
           uint32 RSVD_3                  : 1;  /* [3]            r/w        */
           uint32 STOP_WAKEUP_RST         : 1;  /* [4]            ro         */
           uint32 WDOG                    : 1;  /* [5]            ro         */
           uint32 LOCKUP                  : 1;  /* [6]            ro         */
           uint32 SW                      : 1;  /* [7]            ro         */
           uint32 ADM_AP                  : 1;  /* [8]            ro         */
           uint32 RSVD_13_9               : 5;  /* [13:9]         ro         */
           uint32 SACKERR                 : 1;  /* [14]           ro         */
           uint32 PIN                     : 1;  /* [15]           ro         */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } SRMC_RST_SRS;

    /* 0x18*/
    struct {
           uint32 SPOR                    : 1;  /* [0]            w1c        */
           uint32 SLVD                    : 1;  /* [1]            w1c        */
           uint32 SWAKEUP                 : 1;  /* [2]            w1c        */
           uint32 RSVD_3                  : 1;  /* [3]            r/w        */
           uint32 SSTOP_WAKEUP_RST        : 1;  /* [4]            w1c        */
           uint32 SWDOG                   : 1;  /* [5]            w1c        */
           uint32 SLOCKUP                 : 1;  /* [6]            w1c        */
           uint32 SSW                     : 1;  /* [7]            w1c        */
           uint32 SADM_AP                 : 1;  /* [8]            w1c        */
           uint32 RSVD_13_9               : 5;  /* [13:9]         ro         */
           uint32 SSACKERR                : 1;  /* [14]           w1c        */
           uint32 SPIN                    : 1;  /* [15]           w1c        */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } SRMC_RST_SSRS;

    /* 0x1C*/
    struct {
           uint32 DELAY                   : 2;  /* [1:0]          r/w        */
           uint32 RSVD_3_2                : 2;  /* [3:2]          ro         */
           uint32 STOP_WKUP_RST           : 1;  /* [4]            r/w        */
           uint32 WDOG                    : 1;  /* [5]            r/w        */
           uint32 LOCKUP                  : 1;  /* [6]            r/w        */
           uint32 SW                      : 1;  /* [7]            r/w        */
           uint32 ADM_AP                  : 1;  /* [8]            r/w        */
           uint32 RSVD_13_9               : 5;  /* [13:9]         ro         */
           uint32 SACKERR                 : 1;  /* [14]           r/w        */
           uint32 PIN                     : 1;  /* [15]           r/w        */
           uint32 GIE                     : 1;  /* [16]           r/w        */
           uint32 RSVD_31_17              :15;  /* [31:17]        ro         */
    } SRMC_RST_SRIE;

    /* 0x20*/
    struct {
           uint32 SW_RST                  : 5;  /* [4:0]          wo         */
           uint32 RSVD_31_5               :27;  /* [31:5]         ro         */
    } SRMC_SW_RST;

    /* 0x24*/
    struct {
           uint32 SW_RST_FLAG             : 8;  /* [7:0]          w1c        */
           uint32 RSVD_31_8               :24;  /* [31:8]         ro         */
    } SRMC_SW_RST_FLAG;

    uint8 zResverd0x028[8];   /*pad 0x028 - 02F*/

    /* 0x30*/
    struct {
           uint32 APD                     : 1;  /* [0]            r/w        */
           uint32 RSVD_31_1               :31;  /* [31:1]         ro         */
    } SRMC_PM_PROT;

    /* 0x34*/
    struct {
           uint32 DSMC                    : 2;  /* [1:0]          r/w        */
           uint32 RSVD_7_2                : 6;  /* [7:2]          ro         */
           uint32 DSMACKTMO               : 8;  /* [15:8]         r/w        */
           uint32 RSVD_30_16              :15;  /* [30:16]        ro         */
           uint32 STOP_WKUP_RST_EN        : 1;  /* [31]           r/w        */
    } SRMC_PM_CTRL;

    /* 0x38*/
    struct {
           uint32 PMSTAT                  : 3;  /* [2:0]          ro         */
           uint32 RSVD_7_3                : 5;  /* [7:3]          ro         */
           uint32 DSMABORT                : 1;  /* [8]            ro         */
           uint32 RSVD_31_9               :23;  /* [31:9]         ro         */
    } SRMC_PM_STAT;

    uint8 zResverd0x03C[4];   /*pad 0x03C - 03F*/  

    /* 0x40*/
    struct {
           uint32 WUPSRC_EN7_0            : 8;  /* [7:0]          r/w        */
           uint32 RSVD_31_8               :24;  /* [31:8]         ro         */
    } SRMC_PM_WKUP_CTRL1;

    uint8 zResverd0x044[4];   /*pad 0x044 - 047*/

    /* 0x48*/
    struct {
           uint32 WUPS_7_0                : 8;  /* [7:0]          w1c        */
	       uint32 RSVD_31_8               :24;  /* [31:8]         ro         */
    } SRMC_PM_WKUP_STAT;

};    /*srmc_reg*/

struct Reg_Srmc_W {
    /* 0x00*/
    uint32 SRMC_VERID;
    /* 0x04*/
    uint32 SRMC_PARAM;
    uint8 zResverd0x08[8];   /*pad 0x08 - 0F*/

    /* 0x10*/
    uint32 SRMC_RST_CTRL;
    /* 0x14*/
    uint32 SRMC_RST_SRS;
    /* 0x18*/
    uint32 SRMC_RST_SSRS;
    /* 0x1C*/
    uint32 SRMC_RST_SRIE;
    /* 0x20*/
    uint32 SRMC_SW_RST;
    /* 0x24*/
    uint32 SRMC_SW_RST_FLAG;
    uint8 zResverd0x028[8];   /*pad 0x028 - 02F*/

    /* 0x30*/
    uint32 SRMC_PM_PROT;
    /* 0x34*/
    uint32 SRMC_PM_CTRL;
    /* 0x38*/
    uint32 SRMC_PM_STAT;
    
    uint8 zResverd0x03C[4];   /*pad 0x03C - 03F*/
    /* 0x40*/
    uint32 SRMC_PM_WKUP_CTRL1;
    /* 0x44*/
    uint8 zResverd0x044[4];
    /* 0x48*/
    uint32 SRMC_PM_WKUP_STAT;
};    /*srmc_reg*/

typedef volatile struct Reg_Srmc_Bf Reg_Srmc_BfType;
typedef volatile struct Reg_Srmc_W  Reg_Srmc_WType;

struct Reg_Stim_Bf {
    /* 0x0*/
    struct {
           uint32 EN                      : 1;  /* [0]            r/w        */
           uint32 FREERUN                 : 1;  /* [1]            r/w        */
           uint32 RSVD_31_2               :30;  /* [31:2]         ro         */
    } STIM_CONF0;

    /* 0x4*/
    struct {
           uint32 MATCH_VAL               :24;  /* [23:0]         r/w        */
           uint32 RSVD_31_24              : 8;  /* [31:24]        ro         */
    } STIM_MATCH_VAL;

    /* 0x8*/
    struct {
           uint32 TIM_VAL                 :24;  /* [23:0]         ro         */
           uint32 RSVD_31_24              : 8;  /* [31:24]        ro         */
    } STIM_TIM_VAL;

    /* 0xC*/
    struct {
           uint32 INT_EN                  : 1;  /* [0]            r/w        */
           uint32 INT_CLR                 : 1;  /* [1]            wo         */
           uint32 RSVD_31_2               :30;  /* [31:2]         ro         */
    } STIM_INT_CTRL;

    /* 0x10*/
    struct {
           uint32 INT                     : 1;  /* [0]            ro         */
           uint32 RSVD_31_1               :31;  /* [31:1]         ro         */
    } STIM_INT_STS;

};    /*stim_reg*/

struct Reg_Stim_W {
    /* 0x0*/
    uint32 STIM_CONF0;
    /* 0x4*/
    uint32 STIM_MATCH_VAL;
    /* 0x8*/
    uint32 STIM_TIM_VAL;
    /* 0xC*/
    uint32 STIM_INT_CTRL;
    /* 0x10*/
    uint32 STIM_INT_STS;
};    /*stim_reg*/

typedef volatile struct Reg_Stim_Bf Reg_Stim_BfType;
typedef volatile struct Reg_Stim_W  Reg_Stim_WType;

struct Reg_Tdg_Bf {
    /* 0x0*/
    struct {
           uint32 CH_EN                   : 3;  /* [2:0]          r/w        */
           uint32 RSVD_14_3               :12;  /* [14:3]         ro         */
           uint32 EN                      : 1;  /* [15]           r/w        */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } TDG_ABS_CONF0;

    /* 0x4*/
    struct {
           uint32 CH0_TRIG_SEL            : 4;  /* [3:0]          r/w        */
           uint32 CH1_TRIG_SEL            : 4;  /* [7:4]          r/w        */
           uint32 CH2_TRIG_SEL            : 4;  /* [11:8]         r/w        */
           uint32 RSVD_15_12              : 4;  /* [15:12]        ro         */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } TDG_ABS_CH_TRIG_SEL;

    /* 0x8*/
    struct {
           uint32 T0                      :16;  /* [15:0]         r/w        */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } TDG_ABS_T0;

    /* 0xC*/
    struct {
           uint32 T1                      :16;  /* [15:0]         r/w        */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } TDG_ABS_T1;

    /* 0x10*/
    struct {
           uint32 T2                      :16;  /* [15:0]         r/w        */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } TDG_ABS_T2;

    /* 0x14*/
    struct {
           uint32 SKIP_CYC                : 2;  /* [1:0]          r/w        */
           uint32 RSVD_15_2               :14;  /* [15:2]         ro         */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } TDG_ABS_SKIP_CYC;

    /* 0x18*/
    struct {
           uint32 SW_TRIG                 : 3;  /* [2:0]          wo         */
           uint32 RSVD_15_3               :13;  /* [15:3]         ro         */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } TDG_ABS_SW_TRIG;

    /* 0x1C*/
    struct {
           uint32 CNTV                    :16;  /* [15:0]         ro         */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } TDG_ABS_CNT0;

    /* 0x20*/
    struct {
           uint32 CNTV                    :16;  /* [15:0]         ro         */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } TDG_ABS_CNT1;

    /* 0x24*/
    struct {
           uint32 CNTV                    :16;  /* [15:0]         ro         */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } TDG_ABS_CNT2;

    /* 0x28*/
    struct {
           uint32 CH0_TRIG_OVF            : 1;  /* [0]            w1c        */
           uint32 CH1_TRIG_OVF            : 1;  /* [1]            w1c        */
           uint32 CH2_TRIG_OVF            : 1;  /* [2]            w1c        */
           uint32 RSVD_7_3                : 5;  /* [7:3]          ro         */
           uint32 CNT0_RUN                : 1;  /* [8]            ro         */
           uint32 CNT1_RUN                : 1;  /* [9]            ro         */
           uint32 CNT2_RUN                : 1;  /* [10]           ro         */
           uint32 RSVD_31_11              :21;  /* [31:11]        ro         */
    } TDG_ABS_CHX_STS;
};    /*tdg_reg*/

struct Reg_Tdg_W {
    /* 0x0*/
    uint32 TDG_ABS_CONF0;
    /* 0x4*/
    uint32 TDG_ABS_CH_TRIG_SEL;
    /* 0x8*/
    uint32 TDG_ABS_T0;
    /* 0xC*/
    uint32 TDG_ABS_T1;
    /* 0x10*/
    uint32 TDG_ABS_T2;
    /* 0x14*/
    uint32 TDG_ABS_SKIP_CYC;
    /* 0x18*/
    uint32 TDG_ABS_SW_TRIG;
    /* 0x1C*/
    uint32 TDG_ABS_CNT0;
    /* 0x20*/
    uint32 TDG_ABS_CNT1;
    /* 0x24*/
    uint32 TDG_ABS_CNT2;
    /* 0x28*/
    uint32 TDG_ABS_CHX_STS;
};    /*tdg_reg*/

typedef volatile struct Reg_Tdg_Bf Reg_Tdg_BfType;
typedef volatile struct Reg_Tdg_W  Reg_Tdg_WType;

struct Reg_Wdg_Bf {
    /* 0x0*/
    uint32 zResverd0x0;
    /* 0x4*/
    uint32 zResverd0x4;
    /* 0x8*/
    struct {
           uint32 WDOGE                   : 1;  /* [0]            r/w        */
           uint32 DEBUGE                  : 1;  /* [1]            r/w        */
           uint32 RSVD_2                  : 1;  /* [2]            r/w        */
           uint32 STOPE                   : 1;  /* [3]            r/w        */
           uint32 INTE                    : 1;  /* [4]            r/w        */
           uint32 WINE                    : 1;  /* [5]            r/w        */
           uint32 CFGUA                   : 1;  /* [6]            r/w        */
           uint32 RSVD_11_7               : 5;  /* [11:7]         ro         */
           uint32 TICEN                   : 1;  /* [12]           r/w        */
           uint32 RSVD_15_13              : 3;  /* [15:13]        ro         */
           uint32 TSTM                    : 3;  /* [18:16]        r/w        */
           uint32 RSVD_23_19              : 5;  /* [23:19]        ro         */
           uint32 CFGUF                   : 1;  /* [24]           ro         */
           uint32 UNLKF                   : 1;  /* [25]           ro         */
           uint32 INTF                    : 1;  /* [26]           W1C        */
           uint32 RSVD_31_27              : 5;  /* [31:27]        ro         */
    } WDOG_CS;

    /* 0xC*/
    struct {
           uint32 TMO                     :16;  /* [15:0]         r/w        */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } WDOG_TMO;

    /* 0x10*/
    struct {
           uint32 WIN                     :16;  /* [15:0]         r/w        */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } WDOG_WIN;

    /* 0x14*/
    struct {
           uint32 CNT                     :16;  /* [15:0]         r/w        */
           uint32 RSVD_31_16              :16;  /* [31:16]        ro         */
    } WDOG_CNT;

};    /*wdog_reg*/

struct Reg_Wdg_W {
    /* 0x0*/
    uint32 zResverd0x0;
    /* 0x4*/
    uint32 zResverd0x4;
    /* 0x8*/
    uint32 WDOG_CS;
    /* 0xC*/
    uint32 WDOG_TMO;
    /* 0x10*/
    uint32 WDOG_WIN;
    /* 0x14*/
    uint32 WDOG_CNT;
};    /*wdog_reg*/

typedef volatile struct Reg_Wdg_Bf Reg_Wdg_BfType;
typedef volatile struct Reg_Wdg_W  Reg_Wdg_WType;


#endif /*Z20M1343L_H*/
