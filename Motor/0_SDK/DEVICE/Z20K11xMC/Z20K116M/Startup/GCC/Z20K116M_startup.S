/****************************************************************************************/
/* @file      : Z20K116M_startup.s                                                      */
/* @brief     : Z20K116M Device Vector Table Source File.                               */
/* @version   : V1.8.0                                                                  */
/* @date      : May-2020                                                                */
/* @author    : Zhixin Semiconductor                                                    */
/*                                                                                      */
/* @note                                                                                */
/* @copyright : Copyright (c) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.  */
/****************************************************************************************/
    .syntax unified
    .arch armv6-m

    .section .isr_vector, "a"
    .align 2
    .globl __isr_vector
__isr_vector:
    .long   __StackTop                     /* Stack */
    .long   Reset_Handler                  /*!< POR Reset Entry */
    .long   NMI_Handler                    /*!< NMI handler */
    .long   HardFault_Handler              /*!< Hard Fault Handler */
    .long   0
    .long   0
    .long   0
    .long   0
    .long   0
    .long   0
    .long   0                              /*!< Reserved 7 Handler */
    .long   SVC_Handler                    /*!< SVC Handler */
    .long   0
    .long   0                              /*!< Reserved 2 Handler */
    .long   PendSV_Handler                 /*!< PendSV Handler */
    .long   SysTick_Handler                /*!< SysTick Handler */

    /* Zhixin specific interrupt */
    .long   DMA0TO3_IRQHandler             /*!< irq 0 : DMA channel 0 - 3 transfer complete ISR */
    .long   DMA4TO7_IRQHandler             /*!< irq 1 : DMA channel 4 - 7 transfer complete ISR */
    .long   DMA8TO11_IRQHandler            /*!< irq 2 : DMA channel 8 - 11 transfer complete ISR */
    .long   DMA12TO15_IRQHandler           /*!< irq 3 : DMA channel 12 - 15 transfer complete ISR */
    .long   DMAERR_IRQHandler              /*!< irq 4 : DMA error interrupt channels 0-7 ISR */
    .long   I2C0_IRQHandler                /*!< irq 5 : I2C 0 ISR */
    .long   Reserved6_IRQHandler           /*!< irq 6 : Reserved Interrupt */
    .long   SPI0_IRQHandler                /*!< irq 7 : SPI 0 ISR */
    .long   SPI1_IRQHandler                /*!< irq 8 : SPI 1 ISR */
    .long   Reserved9_IRQHandler           /*!< irq 9 : Reserved Interrupt */
    .long   UART0_IRQHandler               /*!< irq 10 : UART 0 ISR */
    .long   UART1_IRQHandler               /*!< irq 11 : UART 1 ISR */
    .long   UART2_IRQHandler               /*!< irq 12 : UART2 ISR */
    .long   Reserved13_IRQHandler          /*!< irq 13 : Reserved Interrupt */
    .long   ADC0_IRQHandler                /*!< irq 14 : ADC0 ISR */
    .long   FLASH_IRQHandler               /*!< irq 15 : flash memory ISR */
    .long   CMP_IRQHandler                 /*!< irq 16 : CMP ISR */
    .long   TIM0_IRQHandler                /*!< irq 17 : TIM 0 ISR */
    .long   TIM1_IRQHandler                /*!< irq 18 : TIM 1 ISR */
    .long   TIM2_IRQHandler                /*!< irq 19 : TIM 2 ISR */
    .long   CAN0_IRQHandler                /*!< irq 20 : CAN 0 ISR */
    .long   Reserved21_IRQHandler          /*!< irq 21 : Reserved Interrupt */
    .long   RTC_IRQHandler                 /*!< irq 22 : RTC ISR */
    .long   PMU_IRQHandler                 /*!< irq 23 : PMU ISR */
    .long   TDG0_IRQHandler                /*!< irq 24 : TDG0 ISR */
    .long   SCC_IRQHandler                 /*!< irq 25 : system clock controller ISR */
    .long   WDOG_IRQHandler                /*!< irq 26 : watchdog ISR */
    .long   EWDT_IRQHandler                /*!< irq 27 : external watchdog monitor ISR */
    .long   STIM_IRQHandler                /*!< irq 28 : STIM ISR */
    .long   SRMC_IRQHandler                /*!< irq 29 : system reset and mode control ISR */
    .long   PORTABC_IRQHandler             /*!< irq 30 : port A B C ISR */
    .long   PORTDE_IRQHandler               /*!< irq 31 : port D E ISR */

    .size    __isr_vector, . - __isr_vector

    .text
    .thumb
    
/* Reset_Handler Entry */
    .thumb_func
    .align 2
    .globl   Reset_Handler
    .weak    Reset_Handler
    .type    Reset_Handler, %function
Reset_Handler:
    cpsid   i               /* Mask interrupts */
    .equ    VTOR, 0xE000ED08
    ldr     r0, =VTOR
    ldr     r1, =__isr_vector
    str     r1, [r0]
    ldr     r2, [r1]
    msr     msp, r2
    
#ifndef START_FROM_SRAM
    /* Clean SRAM ECC */
    ldr r1, =__RAM_START
    ldr r2, =__RAM_END

    subs    r2, r1
    subs    r2, #1
    ble .LB2

    movs    r0, 0
    movs    r3, #4
.LB1:
    str r0, [r1]
    add	r1, r1, r3
    subs r2, 4
    bge .LB1
.LB2:
#endif
    

    ldr    r1, =__DATA_ROM
    ldr    r2, =__data_start__
    ldr    r3, =__data_end__

/* Copy data from flash to SRAM.*/
.DATA_LOOP:
    cmp     r2, r3
    bge    .DATA_LOOP_DONE
    ldr     r0, [r1]
    adds    r1, #4
    str     r0, [r2]
    adds    r2, #4
    b      .DATA_LOOP

.DATA_LOOP_DONE:
/* Copy bss from flash to SRAM.*/
    ldr r1, =__bss_start__
    ldr r2, =__bss_end__

    movs    r0, 0
.BSS_LOOP:
    cmp     r1, r2
    bge    .BSS_LOOP_DONE
    str     r0, [r1]
    adds    r1, #4
    b      .BSS_LOOP

.BSS_LOOP_DONE:
    cpsie   i               /* Unmask interrupts */

    ldr   r0,=main
    bx    r0

    .pool
    .size Reset_Handler, . - Reset_Handler
    
    .align  1
    .thumb_func
    .weak JumpToSelf
    .type JumpToSelf, %function
JumpToSelf:
    b JumpToSelf
    .size JumpToSelf, . - JumpToSelf

    .align 1
    .thumb_func
    .weak NMI_Handler
    .type NMI_Handler, %function
NMI_Handler:
    b .
    .size NMI_Handler, . - NMI_Handler

    .align 1
    .thumb_func
    .weak HardFault_Handler
    .type HardFault_Handler, %function
HardFault_Handler:
    b .
    .size HardFault_Handler, . - HardFault_Handler
    
    .align 1
    .thumb_func
    .weak HardFault_Handler
    .type HardFault_Handler, %function
MemManageFault_Handler:
    b .
    .size MemManageFault_Handler, . - MemManageFault_Handler

    .align 1
    .thumb_func
    .weak HardFault_Handler
    .type HardFault_Handler, %function
BusFault_Handler:
    b .
    .size BusFault_Handler, . - BusFault_Handler

    .align 1
    .thumb_func
    .weak HardFault_Handler
    .type HardFault_Handler, %function
UsageFault_Handler:
    b .
    .size UsageFault_Handler, . - UsageFault_Handler

    .align 1
    .thumb_func
    .weak SVC_Handler
    .type SVC_Handler, %function
SVC_Handler:
    b .
    .size SVC_Handler, . - SVC_Handler

    .align 1
    .thumb_func
    .weak SVC_Handler
    .type SVC_Handler, %function
DebugMonitor_Handler:
    b .
    .size DebugMonitor_Handler, . - DebugMonitor_Handler

    .align 1
    .thumb_func
    .weak PendSV_Handler
    .type PendSV_Handler, %function
PendSV_Handler:
    b .
    .size PendSV_Handler, . - PendSV_Handler

    .align 1
    .thumb_func
    .weak SysTick_Handler
    .type SysTick_Handler, %function
SysTick_Handler:
    b .
    .size SysTick_Handler, . - SysTick_Handler

    .align 1
    .thumb_func
    .weak DMA0TO3_IRQHandler
    .type DMA0TO3_IRQHandler, %function
DMA0TO3_IRQHandler:
    ldr   r0,=DMA0TO3_DriverIRQHandler
    bx    r0
    .size DMA0TO3_IRQHandler, . - DMA0TO3_IRQHandler

    .align 1
    .thumb_func
    .weak DMA4TO7_IRQHandler
    .type DMA4TO7_IRQHandler, %function
DMA4TO7_IRQHandler:
    ldr   r0,=DMA4TO7_DriverIRQHandler
    bx    r0
    .size DMA4TO7_IRQHandler, . - DMA4TO7_IRQHandler

    .align 1
    .thumb_func
    .weak DMA8TO11_IRQHandler
    .type DMA8TO11_IRQHandler, %function
DMA8TO11_IRQHandler:
    ldr   r0,=DMA8TO11_DriverIRQHandler
    bx    r0
    .size DMA8TO11_IRQHandler, . - DMA8TO11_IRQHandler

    .align 1
    .thumb_func
    .weak DMA12TO15_IRQHandler
    .type DMA12TO15_IRQHandler, %function
DMA12TO15_IRQHandler:
    ldr   r0,=DMA12TO15_DriverIRQHandler
    bx    r0
    .size DMA12TO15_IRQHandler, . - DMA12TO15_IRQHandler

    .align 1
    .thumb_func
    .weak DMAERR_IRQHandler
    .type DMAERR_IRQHandler, %function
DMAERR_IRQHandler:
    ldr   r0,=DMAERR_DriverIRQHandler
    bx    r0
    .size DMAERR_IRQHandler, . - DMAERR_IRQHandler

    .align 1
    .thumb_func
    .weak I2C0_IRQHandler
    .type I2C0_IRQHandler, %function
I2C0_IRQHandler:
    ldr   r0,=I2C0_DriverIRQHandler
    bx    r0
    .size I2C0_IRQHandler, . - I2C0_IRQHandler

    .align 1
    .thumb_func
    .weak SPI0_IRQHandler
    .type SPI0_IRQHandler, %function
SPI0_IRQHandler:
    ldr   r0,=SPI0_DriverIRQHandler
    bx    r0
    .size SPI0_IRQHandler, . - SPI0_IRQHandler

    .align 1
    .thumb_func
    .weak SPI1_IRQHandler
    .type SPI1_IRQHandler, %function
SPI1_IRQHandler:
    ldr   r0,=SPI1_DriverIRQHandler
    bx    r0
    .size SPI1_IRQHandler, . - SPI1_IRQHandler

    .align 1
    .thumb_func
    .weak UART0_IRQHandler
    .type UART0_IRQHandler, %function
UART0_IRQHandler:
    ldr   r0,=UART0_DriverIRQHandler
    bx    r0
    .size UART0_IRQHandler, . - UART0_IRQHandler

    .align 1
    .thumb_func
    .weak UART1_IRQHandler
    .type UART1_IRQHandler, %function
UART1_IRQHandler:
    ldr   r0,=UART1_DriverIRQHandler
    bx    r0
    .size UART1_IRQHandler, . - UART1_IRQHandler

    .align 1
    .thumb_func
    .weak UART2_IRQHandler
    .type UART2_IRQHandler, %function
UART2_IRQHandler:
    ldr   r0,=UART2_DriverIRQHandler
    bx    r0
    .size UART2_IRQHandler, . - UART2_IRQHandler

    .align 1
    .thumb_func
    .weak ADC0_IRQHandler
    .type ADC0_IRQHandler, %function
ADC0_IRQHandler:
    ldr   r0,=ADC0_DriverIRQHandler
    bx    r0
    .size ADC0_IRQHandler, . - ADC0_IRQHandler

    .align 1
    .thumb_func
    .weak FLASH_IRQHandler
    .type FLASH_IRQHandler, %function
FLASH_IRQHandler:
    ldr   r0,=FLASH_DriverIRQHandler
    bx    r0
    .size FLASH_IRQHandler, . - FLASH_IRQHandler

    .align 1
    .thumb_func
    .weak CMP_IRQHandler
    .type CMP_IRQHandler, %function
CMP_IRQHandler:
    ldr   r0,=CMP_DriverIRQHandler
    bx    r0
    .size CMP_IRQHandler, . - CMP_IRQHandler

    .align 1
    .thumb_func
    .weak TIM0_IRQHandler
    .type TIM0_IRQHandler, %function
TIM0_IRQHandler:
    ldr   r0,=TIM0_DriverIRQHandler
    bx    r0
    .size TIM0_IRQHandler, . - TIM0_IRQHandler

    .align 1
    .thumb_func
    .weak TIM1_IRQHandler
    .type TIM1_IRQHandler, %function
TIM1_IRQHandler:
    ldr   r0,=TIM1_DriverIRQHandler
    bx    r0
    .size TIM1_IRQHandler, . - TIM1_IRQHandler

    .align 1
    .thumb_func
    .weak TIM2_IRQHandler
    .type TIM2_IRQHandler, %function
TIM2_IRQHandler:
    ldr   r0,=TIM2_DriverIRQHandler
    bx    r0
    .size TIM2_IRQHandler, . - TIM2_IRQHandler

    .align 1
    .thumb_func
    .weak CAN0_IRQHandler
    .type CAN0_IRQHandler, %function
CAN0_IRQHandler:
    ldr   r0,=CAN0_DriverIRQHandler
    bx    r0
    .size CAN0_IRQHandler, . - CAN0_IRQHandler

    .align 1
    .thumb_func
    .weak RTC_IRQHandler
    .type RTC_IRQHandler, %function
RTC_IRQHandler:
    ldr   r0,=RTC_DriverIRQHandler
    bx    r0
    .size RTC_IRQHandler, . - RTC_IRQHandler

    .align 1
    .thumb_func
    .weak PMU_IRQHandler
    .type PMU_IRQHandler, %function
PMU_IRQHandler:
    ldr   r0,=PMU_DriverIRQHandler
    bx    r0
    .size PMU_IRQHandler, . - PMU_IRQHandler

    .align 1
    .thumb_func
    .weak TDG0_IRQHandler
    .type TDG0_IRQHandler, %function
TDG0_IRQHandler:
    ldr   r0,=TDG0_DriverIRQHandler
    bx    r0
    .size TDG0_IRQHandler, . - TDG0_IRQHandler

    .align 1
    .thumb_func
    .weak SCC_IRQHandler
    .type SCC_IRQHandler, %function
SCC_IRQHandler:
    ldr   r0,=SCC_DriverIRQHandler
    bx    r0
    .size SCC_IRQHandler, . - SCC_IRQHandler

    .align 1
    .thumb_func
    .weak WDOG_IRQHandler
    .type WDOG_IRQHandler, %function
WDOG_IRQHandler:
    ldr   r0,=WDOG_DriverIRQHandler
    bx    r0
    .size WDOG_IRQHandler, . - WDOG_IRQHandler

    .align 1
    .thumb_func
    .weak EWDT_IRQHandler
    .type EWDT_IRQHandler, %function
EWDT_IRQHandler:
    ldr   r0,=EWDT_DriverIRQHandler
    bx    r0
    .size EWDT_IRQHandler, . - EWDT_IRQHandler

    .align 1
    .thumb_func
    .weak STIM_IRQHandler
    .type STIM_IRQHandler, %function
STIM_IRQHandler:
    ldr   r0,=STIM_DriverIRQHandler
    bx    r0
    .size STIM_IRQHandler, . - STIM_IRQHandler

    .align 1
    .thumb_func
    .weak SRMC_IRQHandler
    .type SRMC_IRQHandler, %function
SRMC_IRQHandler:
    ldr   r0,=SRMC_DriverIRQHandler
    bx    r0
    .size SRMC_IRQHandler, . - SRMC_IRQHandler

    .align 1
    .thumb_func
    .weak PORTABC_IRQHandler
    .type PORTABC_IRQHandler, %function
PORTABC_IRQHandler:
    ldr   r0,=PORTABC_DriverIRQHandler
    bx    r0
    .size PORTABC_IRQHandler, . - PORTABC_IRQHandler

    .align 1
    .thumb_func
    .weak PORTDE_IRQHandler
    .type PORTDE_IRQHandler, %function
PORTDE_IRQHandler:
    ldr   r0,=PORTDE_DriverIRQHandler
    bx    r0
    .size PORTDE_IRQHandler, . - PORTDE_IRQHandler

/* Define default handlers */
    .macro def_irq_handler  handler_name
    .weak \handler_name
    .set  \handler_name, JumpToSelf
    .endm

/* Zhixin specific interrupt */
    def_irq_handler    DMA0TO3_DriverIRQHandler
    def_irq_handler    DMA4TO7_DriverIRQHandler
    def_irq_handler    DMA8TO11_DriverIRQHandler
    def_irq_handler    DMA12TO15_DriverIRQHandler
    def_irq_handler    DMAERR_DriverIRQHandler
    def_irq_handler    I2C0_DriverIRQHandler
    def_irq_handler    Reserved6_IRQHandler
    def_irq_handler    SPI0_DriverIRQHandler
    def_irq_handler    SPI1_DriverIRQHandler
    def_irq_handler    Reserved9_IRQHandler
    def_irq_handler    UART0_DriverIRQHandler
    def_irq_handler    UART1_DriverIRQHandler
    def_irq_handler    UART2_DriverIRQHandler
    def_irq_handler    Reserved13_IRQHandler
    def_irq_handler    ADC0_DriverIRQHandler
    def_irq_handler    FLASH_DriverIRQHandler
    def_irq_handler    CMP_DriverIRQHandler
    def_irq_handler    TIM0_DriverIRQHandler
    def_irq_handler    TIM1_DriverIRQHandler
    def_irq_handler    TIM2_DriverIRQHandler
    def_irq_handler    CAN0_DriverIRQHandler
    def_irq_handler    Reserved21_IRQHandler
    def_irq_handler    RTC_DriverIRQHandler
    def_irq_handler    PMU_DriverIRQHandler
    def_irq_handler    TDG0_DriverIRQHandler
    def_irq_handler    SCC_DriverIRQHandler
    def_irq_handler    WDOG_DriverIRQHandler
    def_irq_handler    EWDT_DriverIRQHandler
    def_irq_handler    STIM_DriverIRQHandler
    def_irq_handler    SRMC_DriverIRQHandler
    def_irq_handler    PORTABC_DriverIRQHandler
    def_irq_handler    PORTDE_DriverIRQHandler


    .end