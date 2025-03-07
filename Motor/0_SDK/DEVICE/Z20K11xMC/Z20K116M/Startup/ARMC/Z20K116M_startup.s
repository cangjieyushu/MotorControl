; ---------------------------------------------------------------------------
;  @file:     : Z20K116M_startup.s
;  @brief:    : Z20K116M startup and Vector Table Source File for ARM Compiler
;  @version   : V1.8.0
;  @date      : May-2020
;  @author    : Zhixin Semiconductor
;
;  @note
;  @copyright : Copyright (c) 2020-2023 Zhixin Semiconductor Ltd. All rights reserved.
; ---------------------------------------------------------------------------


                PRESERVE8
                THUMB


                AREA    |.text|, CODE, READONLY
                EXPORT  __vector_table
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size
                    
                IMPORT  __main

                IMPORT  |Image$$ARM_LIB_STACK$$ZI$$Limit|
                
                    
                IF :LNOT: :DEF:START_FROM_SRAM
                IMPORT  |Image$$RAM_START$$Base|
__RAM_START DCD |Image$$RAM_START$$Base|
__RAM_END   DCD |Image$$ARM_LIB_STACK$$ZI$$Limit|
                ENDIF

                
                AREA    |.intvec|, DATA, READONLY
__vector_table
        DCD   |Image$$ARM_LIB_STACK$$ZI$$Limit| ; Top of Stack
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

__Vectors_Size  EQU     __Vectors_End - __vector_table


                AREA    |.text|, CODE, READONLY

Reset_Handler   PROC
                ALIGN   4
                EXPORT  Reset_Handler             [WEAK]

                CPSID   I               ; Mask interrupts
                
                IF :LNOT: :DEF:START_FROM_SRAM
                ; Init ECC RAM
                LDR     R1, =__RAM_START
                LDR     R1, [R1]
                LDR     R2, =__RAM_END
                LDR     R2, [R2]
                SUBS    R2, R1
                SUBS    R2, #1
                BLE LC2

                MOVS    R0, #0
                MOVS    R3, #4
LC1
                STR R0, [R1]
                ADD R1, R1, R3
                SUBS R2, #4
                BGE LC1
LC2
                NOP
                ENDIF
                    
                LDR     R0, =0xE000ED08
                LDR     R1, =__vector_table
                STR     R1, [R0]
                LDR     R2, [R1]
                MSR     MSP, R2
                CPSIE   i               ; Unmask interrupts
                LDR     R0, =__main
                BLX     R0
                ENDP

NMI_Handler\
                PROC
                EXPORT  NMI_Handler         [WEAK]
                B       .
                ENDP

HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler   [WEAK]
                B       .
                ENDP

SVC_Handler\
                PROC
                EXPORT  SVC_Handler         [WEAK]
                B       .
                ENDP

PendSV_Handler\
                PROC
                EXPORT  PendSV_Handler         [WEAK]
                B       .
                ENDP

SysTick_Handler\
                PROC
                EXPORT  SysTick_Handler         [WEAK]
                B       .
                ENDP

DMA0TO3_IRQHandler\
                PROC
                EXPORT  DMA0TO3_IRQHandler         [WEAK]
                LDR     R0, =DMA0TO3_DriverIRQHandler
                BX      R0
                ENDP

DMA4TO7_IRQHandler\
                PROC
                EXPORT  DMA4TO7_IRQHandler         [WEAK]
                LDR     R0, =DMA4TO7_DriverIRQHandler
                BX      R0
                ENDP

DMA8TO11_IRQHandler\
                PROC
                EXPORT  DMA8TO11_IRQHandler         [WEAK]
                LDR     R0, =DMA8TO11_DriverIRQHandler
                BX      R0
                ENDP

DMA12TO15_IRQHandler\
                PROC
                EXPORT  DMA12TO15_IRQHandler         [WEAK]
                LDR     R0, =DMA12TO15_DriverIRQHandler
                BX      R0
                ENDP

DMAERR_IRQHandler\
                PROC
                EXPORT  DMAERR_IRQHandler         [WEAK]
                LDR     R0, =DMAERR_DriverIRQHandler
                BX      R0
                ENDP

I2C0_IRQHandler\
                PROC
                EXPORT  I2C0_IRQHandler         [WEAK]
                LDR     R0, =I2C0_DriverIRQHandler
                BX      R0
                ENDP

SPI0_IRQHandler\
                PROC
                EXPORT  SPI0_IRQHandler         [WEAK]
                LDR     R0, =SPI0_DriverIRQHandler
                BX      R0
                ENDP

SPI1_IRQHandler\
                PROC
                EXPORT  SPI1_IRQHandler         [WEAK]
                LDR     R0, =SPI1_DriverIRQHandler
                BX      R0
                ENDP

UART0_IRQHandler\
                PROC
                EXPORT  UART0_IRQHandler         [WEAK]
                LDR     R0, =UART0_DriverIRQHandler
                BX      R0
                ENDP

UART1_IRQHandler\
                PROC
                EXPORT  UART1_IRQHandler         [WEAK]
                LDR     R0, =UART1_DriverIRQHandler
                BX      R0
                ENDP

UART2_IRQHandler\
                PROC
                EXPORT  UART2_IRQHandler         [WEAK]
                LDR     R0, =UART2_DriverIRQHandler
                BX      R0
                ENDP

ADC0_IRQHandler\
                PROC
                EXPORT  ADC0_IRQHandler         [WEAK]
                LDR     R0, =ADC0_DriverIRQHandler
                BX      R0
                ENDP

FLASH_IRQHandler\
                PROC
                EXPORT  FLASH_IRQHandler         [WEAK]
                LDR     R0, =FLASH_DriverIRQHandler
                BX      R0
                ENDP

CMP_IRQHandler\
                PROC
                EXPORT  CMP_IRQHandler         [WEAK]
                LDR     R0, =CMP_DriverIRQHandler
                BX      R0
                ENDP

TIM0_IRQHandler\
                PROC
                EXPORT  TIM0_IRQHandler         [WEAK]
                LDR     R0, =TIM0_DriverIRQHandler
                BX      R0
                ENDP

TIM1_IRQHandler\
                PROC
                EXPORT  TIM1_IRQHandler         [WEAK]
                LDR     R0, =TIM1_DriverIRQHandler
                BX      R0
                ENDP

TIM2_IRQHandler\
                PROC
                EXPORT  TIM2_IRQHandler         [WEAK]
                LDR     R0, =TIM2_DriverIRQHandler
                BX      R0
                ENDP

CAN0_IRQHandler\
                PROC
                EXPORT  CAN0_IRQHandler         [WEAK]
                LDR     R0, =CAN0_DriverIRQHandler
                BX      R0
                ENDP

RTC_IRQHandler\
                PROC
                EXPORT  RTC_IRQHandler         [WEAK]
                LDR     R0, =RTC_DriverIRQHandler
                BX      R0
                ENDP

PMU_IRQHandler\
                PROC
                EXPORT  PMU_IRQHandler         [WEAK]
                LDR     R0, =PMU_DriverIRQHandler
                BX      R0
                ENDP

TDG0_IRQHandler\
                PROC
                EXPORT  TDG0_IRQHandler         [WEAK]
                LDR     R0, =TDG0_DriverIRQHandler
                BX      R0
                ENDP

SCC_IRQHandler\
                PROC
                EXPORT  SCC_IRQHandler         [WEAK]
                LDR     R0, =SCC_DriverIRQHandler
                BX      R0
                ENDP

WDOG_IRQHandler\
                PROC
                EXPORT  WDOG_IRQHandler         [WEAK]
                LDR     R0, =WDOG_DriverIRQHandler
                BX      R0
                ENDP

EWDT_IRQHandler\
                PROC
                EXPORT  EWDT_IRQHandler         [WEAK]
                LDR     R0, =EWDT_DriverIRQHandler
                BX      R0
                ENDP

STIM_IRQHandler\
                PROC
                EXPORT  STIM_IRQHandler         [WEAK]
                LDR     R0, =STIM_DriverIRQHandler
                BX      R0
                ENDP

SRMC_IRQHandler\
                PROC
                EXPORT  SRMC_IRQHandler         [WEAK]
                LDR     R0, =SRMC_DriverIRQHandler
                BX      R0
                ENDP

PORTABC_IRQHandler\
                PROC
                EXPORT  PORTABC_IRQHandler         [WEAK]
                LDR     R0, =PORTABC_DriverIRQHandler
                BX      R0
                ENDP

PORTDE_IRQHandler\
                PROC
                EXPORT  PORTDE_IRQHandler         [WEAK]
                LDR     R0, =PORTDE_DriverIRQHandler
                BX      R0
                ENDP

Default_Handler PROC
                EXPORT  DMA0TO3_DriverIRQHandler        [WEAK]
                EXPORT  DMA4TO7_DriverIRQHandler        [WEAK]
                EXPORT  DMA8TO11_DriverIRQHandler       [WEAK]
                EXPORT  DMA12TO15_DriverIRQHandler      [WEAK]
                EXPORT  DMAERR_DriverIRQHandler         [WEAK]
                EXPORT  I2C0_DriverIRQHandler           [WEAK]
                EXPORT  Reserved6_IRQHandler           [WEAK]
                EXPORT  SPI0_DriverIRQHandler           [WEAK]
                EXPORT  SPI1_DriverIRQHandler           [WEAK]
                EXPORT  Reserved9_IRQHandler           [WEAK]
                EXPORT  UART0_DriverIRQHandler          [WEAK]
                EXPORT  UART1_DriverIRQHandler          [WEAK]
                EXPORT  UART2_DriverIRQHandler          [WEAK]
                EXPORT  Reserved13_IRQHandler          [WEAK]
                EXPORT  ADC0_DriverIRQHandler           [WEAK]
                EXPORT  FLASH_DriverIRQHandler          [WEAK]
                EXPORT  CMP_DriverIRQHandler            [WEAK]
                EXPORT  TIM0_DriverIRQHandler           [WEAK]
                EXPORT  TIM1_DriverIRQHandler           [WEAK]
                EXPORT  TIM2_DriverIRQHandler           [WEAK]
                EXPORT  CAN0_DriverIRQHandler           [WEAK]
                EXPORT  Reserved21_IRQHandler           [WEAK]
                EXPORT  RTC_DriverIRQHandler            [WEAK]
                EXPORT  PMU_DriverIRQHandler            [WEAK]
                EXPORT  TDG0_DriverIRQHandler           [WEAK]
                EXPORT  SCC_DriverIRQHandler            [WEAK]
                EXPORT  WDOG_DriverIRQHandler           [WEAK]
                EXPORT  EWDT_DriverIRQHandler           [WEAK]
                EXPORT  STIM_DriverIRQHandler           [WEAK]
                EXPORT  SRMC_DriverIRQHandler           [WEAK]
                EXPORT  PORTABC_DriverIRQHandler        [WEAK]
                EXPORT  PORTDE_DriverIRQHandler         [WEAK]

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

                B       .

                ENDP

                ALIGN
                END