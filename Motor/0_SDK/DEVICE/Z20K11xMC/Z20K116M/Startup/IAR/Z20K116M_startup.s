; -----------------------------------------------------------------------------
; @file      : Z20K116M_startup.s
; @brief     : Z20K116M startup and Vector Table Source File for IAR.
; @version   : V1.8.0
; @date      : May-2020
; @author    : Zhixin Semiconductor
;
; @note
; @copyright : Copyright (c) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
; -----------------------------------------------------------------------------


        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:ROOT(2)

        EXTERN  __iar_program_start
        PUBLIC  __vector_table
        PUBLIC  __Vectors_End
        PUBLIC  __Vectors_Size

        DATA

__vector_table
        DCD   sfe(CSTACK)
        DCD   Reset_Handler           ; POR Reset Entry
        DCD   NMI_Handler             ; Non Maskable handler
        DCD   HardFault_Handler       ; SV Hard Fault handler
        DCD   0
        DCD   0
        DCD   0
        DCD   0
        DCD   0
        DCD   0
        DCD   0
        DCD   SVC_Handler              ; SV Call handler
        DCD   0
        DCD   0
        DCD   PendSV_Handler           ; Pend SV handler
        DCD   SysTick_Handler          ; System Tick handler


        DCD   DMA0TO3_IRQHandler         ; irq 0 : DMA channel 0 - 3 transfer complete IRQHandler
        DCD   DMA4TO7_IRQHandler         ; irq 1 : DMA channel 4 - 7 transfer complete IRQHandler
        DCD   DMA8TO11_IRQHandler        ; irq 2 : DMA channel 8 - 11 transfer complete IRQHandler
        DCD   DMA12TO15_IRQHandler       ; irq 3 : DMA channel 12 - 15 transfer complete IRQHandler
        DCD   DMAERR_IRQHandler          ; irq 4 : DMA error interrupt channels 0-7 IRQHandler
        DCD   I2C0_IRQHandler            ; irq 5 : I2C 0 IRQHandler
        DCD   Reserved6_IRQHandler       ; irq 6 : Reserved Interrupt
        DCD   SPI0_IRQHandler            ; irq 7 : SPI 0 IRQHandler
        DCD   SPI1_IRQHandler            ; irq 8 : SPI 1 IRQHandler
        DCD   Reserved9_IRQHandler       ; irq 9 : Reserved Interrupt
        DCD   UART0_IRQHandler           ; irq 10 : UART 0 IRQHandler
        DCD   UART1_IRQHandler           ; irq 11 : UART 1 IRQHandler 
        DCD   UART2_IRQHandler           ; irq 12 : UART2 IRQHandler
        DCD   Reserved13_IRQHandler      ; irq 13 : Reserved Interrupt
        DCD   ADC0_IRQHandler            ; irq 14 : ADC0 IRQHandler
        DCD   FLASH_IRQHandler           ; irq 15 : flash memory IRQHandler
        DCD   CMP_IRQHandler             ; irq 16 : CMP IRQHandler
        DCD   TIM0_IRQHandler            ; irq 17 : TIM 0 IRQHandler
        DCD   TIM1_IRQHandler            ; irq 18 : TIM 1 IRQHandler
        DCD   TIM2_IRQHandler            ; irq 19 : TIM 2 IRQHandler
        DCD   CAN0_IRQHandler            ; irq 20 : CAN 0 IRQHandler
        DCD   Reserved21_IRQHandler      ; irq 21 : Reserved Interrupt
        DCD   RTC_IRQHandler             ; irq 22 : RTC IRQHandler
        DCD   PMU_IRQHandler             ; irq 23 : PMU IRQHandler
        DCD   TDG0_IRQHandler            ; irq 24 : TDG0 IRQHandler
        DCD   SCC_IRQHandler             ; irq 25 : system clock controller IRQHandler
        DCD   WDOG_IRQHandler            ; irq 26 : watchdog IRQHandler
        DCD   EWDT_IRQHandler            ; irq 27 : external watchdog monitor IRQHandler
        DCD   STIM_IRQHandler            ; irq 28 : STIM IRQHandler
        DCD   SRMC_IRQHandler            ; irq 29 : system reset and mode control IRQHandler
        DCD   PORTABC_IRQHandler         ; irq 30 : port A B C IRQHandler
        DCD   PORTDE_IRQHandler          ; irq 31 : port D E IRQHandler
__Vectors_End


__Vectors_Size  EQU   __Vectors_End - __vector_table


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
        CPSID   I               ; Mask interrupts
        ;; Init the registers
        LDR     R1,=0
        LDR     R2,=0
        LDR     R3,=0
        LDR     R4,=0
        LDR     R5,=0
        LDR     R6,=0
        LDR     R7,=0
        MOV     R8,R7
        MOV     R9,R7
        MOV     R10,R7
        MOV     R11,R7
        MOV     R12,R7
        
        ; vector table relocation
        LDR     R0, =0xE000ED08
        LDR     R1, =__vector_table
        STR     R1, [R0]

#ifndef START_FROM_SRAM
        IMPORT __RAM_START, __RAM_END
        ;; INIT ECC RAM

        LDR R1, =__RAM_START
        LDR R2, =__RAM_END

        SUBS    R2, R2, R1
        SUBS    R2, #1
        BLE LB2

        MOVS    R0, #0
        MOVS    R3, #4
    LB1:
        STR R0, [R1]
        ADD	R1, R1, R3
        SUBS R2, #4
        BGE LB1
    LB2:
#endif
        ;; Initialize the stack pointer
        LDR     R0, =sfe(CSTACK)
        MOV     R13,R0
        
        CPSIE   I               ; Unmask interrupts

        LDR     R0, =__iar_program_start
        BX      R0

JumpToSelf
        B   JumpToSelf

        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
        B .

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
        B .


        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
        B .

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B .

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B .


        PUBWEAK DMA0TO3_IRQHandler
        PUBWEAK DMA0TO3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA0TO3_IRQHandler
        LDR     R0, =DMA0TO3_DriverIRQHandler
        BX      R0 

        PUBWEAK DMA4TO7_IRQHandler
        PUBWEAK DMA4TO7_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA4TO7_IRQHandler
        LDR     R0, =DMA4TO7_DriverIRQHandler
        BX      R0 

        PUBWEAK DMA8TO11_IRQHandler
        PUBWEAK DMA8TO11_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA8TO11_IRQHandler
        LDR     R0, =DMA8TO11_DriverIRQHandler
        BX      R0 

        PUBWEAK DMA12TO15_IRQHandler
        PUBWEAK DMA12TO15_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA12TO15_IRQHandler
        LDR     R0, =DMA12TO15_DriverIRQHandler
        BX      R0 

        PUBWEAK DMAERR_IRQHandler
        PUBWEAK DMAERR_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMAERR_IRQHandler
        LDR     R0, =DMAERR_DriverIRQHandler
        BX      R0 

        PUBWEAK I2C0_IRQHandler
        PUBWEAK I2C0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
I2C0_IRQHandler
        LDR     R0, =I2C0_DriverIRQHandler
        BX      R0 

        PUBWEAK Reserved6_IRQHandler
        PUBWEAK SPI0_IRQHandler
        PUBWEAK SPI0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI0_IRQHandler
        LDR     R0, =SPI0_DriverIRQHandler
        BX      R0 

        PUBWEAK SPI1_IRQHandler
        PUBWEAK SPI1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI1_IRQHandler
        LDR     R0, =SPI1_DriverIRQHandler
        BX      R0 

        PUBWEAK Reserved9_IRQHandler
        PUBWEAK UART0_IRQHandler
        PUBWEAK UART0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
UART0_IRQHandler
        LDR     R0, =UART0_DriverIRQHandler
        BX      R0 

        PUBWEAK UART1_IRQHandler
        PUBWEAK UART1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
UART1_IRQHandler
        LDR     R0, =UART1_DriverIRQHandler
        BX      R0 

        PUBWEAK UART2_IRQHandler
        PUBWEAK UART2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
UART2_IRQHandler
        LDR     R0, =UART2_DriverIRQHandler
        BX      R0 

        PUBWEAK Reserved13_IRQHandler
        PUBWEAK ADC0_IRQHandler
        PUBWEAK ADC0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ADC0_IRQHandler
        LDR     R0, =ADC0_DriverIRQHandler
        BX      R0 

        PUBWEAK FLASH_IRQHandler
        PUBWEAK FLASH_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLASH_IRQHandler
        LDR     R0, =FLASH_DriverIRQHandler
        BX      R0 

        PUBWEAK CMP_IRQHandler
        PUBWEAK CMP_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CMP_IRQHandler
        LDR     R0, =CMP_DriverIRQHandler
        BX      R0 

        PUBWEAK TIM0_IRQHandler
        PUBWEAK TIM0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TIM0_IRQHandler
        LDR     R0, =TIM0_DriverIRQHandler
        BX      R0 

        PUBWEAK TIM1_IRQHandler
        PUBWEAK TIM1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TIM1_IRQHandler
        LDR     R0, =TIM1_DriverIRQHandler
        BX      R0 

        PUBWEAK TIM2_IRQHandler
        PUBWEAK TIM2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TIM2_IRQHandler
        LDR     R0, =TIM2_DriverIRQHandler
        BX      R0 

        PUBWEAK CAN0_IRQHandler
        PUBWEAK CAN0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN0_IRQHandler
        LDR     R0, =CAN0_DriverIRQHandler
        BX      R0 

        PUBWEAK Reserved21_IRQHandler
        PUBWEAK RTC_IRQHandler
        PUBWEAK RTC_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
RTC_IRQHandler
        LDR     R0, =RTC_DriverIRQHandler
        BX      R0 

        PUBWEAK PMU_IRQHandler
        PUBWEAK PMU_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PMU_IRQHandler
        LDR     R0, =PMU_DriverIRQHandler
        BX      R0 

        PUBWEAK TDG0_IRQHandler
        PUBWEAK TDG0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TDG0_IRQHandler
        LDR     R0, =TDG0_DriverIRQHandler
        BX      R0 

        PUBWEAK SCC_IRQHandler
        PUBWEAK SCC_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SCC_IRQHandler
        LDR     R0, =SCC_DriverIRQHandler
        BX      R0 

        PUBWEAK WDOG_IRQHandler
        PUBWEAK WDOG_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
WDOG_IRQHandler
        LDR     R0, =WDOG_DriverIRQHandler
        BX      R0 

        PUBWEAK EWDT_IRQHandler
        PUBWEAK EWDT_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
EWDT_IRQHandler
        LDR     R0, =EWDT_DriverIRQHandler
        BX      R0 

        PUBWEAK STIM_IRQHandler
        PUBWEAK STIM_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
STIM_IRQHandler
        LDR     R0, =STIM_DriverIRQHandler
        BX      R0 

        PUBWEAK SRMC_IRQHandler
        PUBWEAK SRMC_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SRMC_IRQHandler
        LDR     R0, =SRMC_DriverIRQHandler
        BX      R0 

        PUBWEAK PORTABC_IRQHandler
        PUBWEAK PORTABC_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PORTABC_IRQHandler
        LDR     R0, =PORTABC_DriverIRQHandler
        BX      R0 

        PUBWEAK PORTDE_IRQHandler
        PUBWEAK PORTDE_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PORTDE_IRQHandler
        LDR     R0, =PORTDE_DriverIRQHandler
        BX      R0 

        PUBWEAK DefaultISR
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA0TO3_DriverIRQHandler
DMA4TO7_DriverIRQHandler
DMA8TO11_DriverIRQHandler
DMA12TO15_DriverIRQHandler
DMAERR_DriverIRQHandler
I2C0_DriverIRQHandler
Reserved6_IRQHandler
SPI0_DriverIRQHandler
SPI1_DriverIRQHandler
Reserved9_IRQHandler
UART0_DriverIRQHandler
UART1_DriverIRQHandler
UART2_DriverIRQHandler
Reserved13_IRQHandler
ADC0_DriverIRQHandler
FLASH_DriverIRQHandler
CMP_DriverIRQHandler
TIM0_DriverIRQHandler
TIM1_DriverIRQHandler
TIM2_DriverIRQHandler
CAN0_DriverIRQHandler
Reserved21_IRQHandler
RTC_DriverIRQHandler
PMU_DriverIRQHandler
TDG0_DriverIRQHandler
SCC_DriverIRQHandler
WDOG_DriverIRQHandler
EWDT_DriverIRQHandler
STIM_DriverIRQHandler
SRMC_DriverIRQHandler
PORTABC_DriverIRQHandler
PORTDE_DriverIRQHandler
DefaultISR
        B DefaultISR

        END
