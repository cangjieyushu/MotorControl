; ---------------------------------------------------------                
; @file     Z20K146M_startup.s                                             
; @brief    Z20K146M Device Vector Table Source File.                      
; @version  V1.1.0                                                         
; @date     December-2022                                                     
; @author   Zhixin Semiconductor                                           
;                                                                          
; @note                                                                    
; Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.   
;                                                                          
;**************************************************************************
    .file "Z20K146M_startup.s"
    .text

    .need DefaultISR
    .globl DefaultISR

    .thumb

    .section .isr_vector, "a"
    .align 2
    .globl __isr_vector
__isr_vector:
    .long   __StackTop              ; Stack 
    .long   Reset_Handler           ; POR Reset Entry
    .long   NMI_Handler             ; Non Maskable handler
    .long   HardFault_Handler       ; SV Hard Fault handler
    .long   MemManageFault_Handler  ; MemManage Fault Handler
    .long   BusFault_Handler        ; Bus Fault Handler
    .long   UsageFault_Handler      ; Usage Fault Handler
    .long   0
    .long   0
    .long   0
    .long   0
    .long   SVC_Handler              ; SV Call handler
    .long   DebugMonitor_Handler     ; debug monitor Handler
    .long   0
    .long   PendSV_Handler           ; Pend SV handler
    .long   SysTick_Handler          ; System Tick handler

    .long   DMA_Ch0_IRQHandler             ; irq 0 : DMA channel 0 transfer complete IRQHandler
    .long   DMA_Ch1_IRQHandler             ; irq 1 : DMA channel 1 transfer complete IRQHandler
    .long   DMA_Ch2_IRQHandler             ; irq 2 : DMA channel 2 transfer complete IRQHandler
    .long   DMA_Ch3_IRQHandler             ; irq 3 : DMA channel 3 transfer complete IRQHandler
    .long   DMA_Ch4_IRQHandler             ; irq 4 : DMA channel 4 transfer complete IRQHandler
    .long   DMA_Ch5_IRQHandler             ; irq 5 : DMA channel 5 transfer complete IRQHandler
    .long   DMA_Ch6_IRQHandler             ; irq 6 : DMA channel 6 transfer complete IRQHandler
    .long   DMA_Ch7_IRQHandler             ; irq 7 : DMA channel 7 transfer complete IRQHandler
    .long   DMA_Ch8_IRQHandler             ; irq 8 : DMA channel 8 transfer complete IRQHandler
    .long   DMA_Ch9_IRQHandler             ; irq 9 : DMA channel 9 transfer complete IRQHandler
    .long   DMA_Ch10_IRQHandler            ; irq 10 : DMA channel 10 transfer complete IRQHandler
    .long   DMA_Ch11_IRQHandler            ; irq 11 : DMA channel 11 transfer complete IRQHandler 
    .long   DMA_Ch12_IRQHandler            ; irq 12 : DMA channel 12 transfer complete IRQHandler
    .long   DMA_Ch13_IRQHandler            ; irq 13 : DMA channel 13 transfer complete IRQHandler
    .long   DMA_Ch14_IRQHandler            ; irq 14 : DMA channel 14 transfer complete IRQHandler
    .long   DMA_Ch15_IRQHandler            ; irq 15 : DMA channel 15 transfer complete IRQHandler
    .long   DMA_Err_IRQHandler             ; irq 16 : DMA channel 0-15 error IRQHandler
    .long   FLASH_CmdComplete_IRQHandler   ; irq 17 : flash command complete IRQHandler
    .long   FLASH_Ecc_IRQHandler           ; irq 18 : Multi-bit or single-bit ECC IRQHandler
    .long   PMU_IRQHandler                 ; irq 19 : PMU IRQHandler
    .long   WDOG_IRQHandler                ; irq 20 : watchdog IRQHandler
    .long   EWDT_IRQHandler                ; irq 21 : external watchdog monitor IRQHandler
    .long   SRMC_IRQHandler                ; irq 22 : system reset and mode control IRQHandler
    .long   I2C0_IRQHandler                ; irq 23 : I2C 0 IRQHandler
    .long   I2C1_IRQHandler                ; irq 24 : I2C 1 IRQHandler
    .long   SPI0_Txe_IRQHandler            ; irq 25 : SPI 0 TXE IRQHandler
    .long   SPI0_Txo_IRQHandler            ; irq 26 : SPI 0 TXO IRQHandler
    .long   SPI0_Rxf_IRQHandler            ; irq 27 : SPI 0 RXF IRQHandler
    .long   SPI0_Rxo_IRQHandler            ; irq 28 : SPI 0 RXO IRQHandler
    .long   SPI0_Rxu_IRQHandler            ; irq 29 : SPI 0 RXU IRQHandler
    .long   Reserved30_IRQHandler          ; Reserved interrupt
    .long   SPI1_Txe_IRQHandler            ; irq 31 : SPI 1 TXE IRQHandler
    .long   SPI1_Txo_IRQHandler            ; irq 32 : SPI 1 TXO IRQHandler
    .long   SPI1_Rxf_IRQHandler            ; irq 33 : SPI 1 RXF IRQHandler
    .long   SPI1_Rxo_IRQHandler            ; irq 34 : SPI 1 RXO IRQHandler
    .long   SPI1_Rxu_IRQHandler            ; irq 35 : SPI 1 RXU IRQHandler
    .long   Reserved36_IRQHandler          ; Reserved interrupt
    .long   SPI2_Txe_IRQHandler            ; irq 37 : SPI 2 TXE IRQHandler
    .long   SPI2_Txo_IRQHandler            ; irq 38 : SPI 2 TXO IRQHandler
    .long   SPI2_Rxf_IRQHandler            ; irq 39 : SPI 2 RXF IRQHandler
    .long   SPI2_Rxo_IRQHandler            ; irq 40 : SPI 2 RXO IRQHandler
    .long   SPI2_Rxu_IRQHandler            ; irq 41 : SPI 2 RXU IRQHandler
    .long   Reserved42_IRQHandler          ; Reserved interrupt
    .long   SPI3_Txe_IRQHandler            ; irq 43 : SPI 3 TXE IRQHandler
    .long   SPI3_Txo_IRQHandler            ; irq 44 : SPI 3 TXO IRQHandler
    .long   SPI3_Rxf_IRQHandler            ; irq 45 : SPI 3 RXF IRQHandler
    .long   SPI3_Rxo_IRQHandler            ; irq 46 : SPI 3 RXO IRQHandler
    .long   SPI3_Rxu_IRQHandler            ; irq 47 : SPI 3 RXU IRQHandler
    .long   Reserved48_IRQHandler          ; Reserved interrupt
    .long   UART0_IRQHandler               ; irq 49 : UART 0 IRQHandler
    .long   UART1_IRQHandler               ; irq 50 : UART 1 IRQHandler
    .long   UART2_IRQHandler               ; irq 51 : UART 2 IRQHandler
    .long   UART3_IRQHandler               ; irq 52 : UART 3 IRQHandler
    .long   UART4_IRQHandler               ; irq 53 : UART 4 IRQHandler
    .long   UART5_IRQHandler               ; irq 54 : UART 5 IRQHandler
    .long   CAN0_BusOff_IRQHandler         ; irq 55 : CAN 0 bus off/ bus off done IRQHandler
    .long   CAN0_TxWarn_IRQHandler         ; irq 56 : CAN 0 TX warning IRQHandler
    .long   CAN0_RxWarn_IRQHandler         ; irq 57 : CAN 0 RX warning IRQHandler
    .long   CAN0_Err_IRQHandler            ; irq 58 : CAN 0 error IRQHandler
    .long   CAN0_ErrFd_IRQHandler          ; irq 59 : CAN 0 error FD IRQHandler
    .long   CAN0_PnWake_IRQHandler         ; irq 60 : CAN 0 pretended network wakeup IRQHandler
    .long   CAN0_SelfWakeup_IRQHandler     ; irq 61 : CAN 0 self-wakeup IRQHandler
    .long   CAN0_Ecc_IRQHandler            ; irq 62 : CAN 0 ECC IRQHandler
    .long   CAN0_Mb0To15_IRQHandler        ; irq 63 : CAN 0 message buffer 0-15 IRQHandler
    .long   CAN0_Mb16To31_IRQHandler       ; irq 64 : CAN 0 message buffer 16-31 IRQHandler
    .long   CAN0_Mb32To47_IRQHandler       ; irq 65 : CAN 0 message buffer 32-47 IRQHandler
    .long   CAN0_Mb48To63_IRQHandler       ; irq 66 : CAN 0 message buffer 48-63 IRQHandler
    .long   CAN1_BusOff_IRQHandler         ; irq 67 : CAN 1 bus off/ bus off done IRQHandler
    .long   CAN1_TxWarn_IRQHandler         ; irq 68 : CAN 1 TX warning IRQHandler
    .long   CAN1_RxWarn_IRQHandler         ; irq 69 : CAN 1 RX warning IRQHandler
    .long   CAN1_Err_IRQHandler            ; irq 70 : CAN 1 error IRQHandler
    .long   CAN1_ErrFd_IRQHandler          ; irq 71 : CAN 1 error FD IRQHandler
    .long   CAN1_PnWake_IRQHandler         ; irq 72 : CAN 1 pretended network wakeup IRQHandler
    .long   CAN1_SelfWakeup_IRQHandler     ; irq 73 : CAN 1 self-wakeup IRQHandler
    .long   CAN1_Ecc_IRQHandler            ; irq 74 : CAN 1 ECC IRQHandler
    .long   CAN1_Mb0To15_IRQHandler        ; irq 75 : CAN 1 message buffer 0-15 IRQHandler
    .long   CAN1_Mb16To31_IRQHandler       ; irq 76 : CAN 1 message buffer 16-31 IRQHandler
    .long   CAN1_Mb32To47_IRQHandler       ; irq 77 : CAN 1 message buffer 32-47 IRQHandler
    .long   CAN1_Mb48To63_IRQHandler       ; irq 78 : CAN 1 message buffer 48-63 IRQHandler
    .long   CAN2_BusOff_IRQHandler         ; irq 79 : CAN 2 bus off/ bus off done IRQHandler
    .long   CAN2_TxWarn_IRQHandler         ; irq 80 : CAN 2 TX warning IRQHandler
    .long   CAN2_RxWarn_IRQHandler         ; irq 81 : CAN 2 RX warning IRQHandler
    .long   CAN2_Err_IRQHandler            ; irq 82 : CAN 2 error IRQHandler
    .long   CAN2_ErrFd_IRQHandler          ; irq 83 : CAN 2 error FD IRQHandler
    .long   CAN2_PnWake_IRQHandler         ; irq 84 : CAN 2 pretended network wakeup IRQHandler
    .long   CAN2_SelfWakeup_IRQHandler     ; irq 85 : CAN 2 self-wakeup IRQHandler
    .long   CAN2_Ecc_IRQHandler            ; irq 86 : CAN 2 ECC IRQHandler
    .long   CAN2_Mb0To15_IRQHandler        ; irq 87 : CAN 2 message buffer 0-15 IRQHandler
    .long   CAN2_Mb16To31_IRQHandler       ; irq 88 : CAN 2 message buffer 16-31 IRQHandler
    .long   CAN2_Mb32To47_IRQHandler       ; irq 89 : CAN 2 message buffer 32-47 IRQHandler
    .long   CAN2_Mb48To63_IRQHandler       ; irq 90 : CAN 2 message buffer 48-63 IRQHandler
    .long   CAN3_BusOff_IRQHandler         ; irq 91 : CAN 3 bus off/ bus off done IRQHandler
    .long   CAN3_TxWarn_IRQHandler         ; irq 92 : CAN 3 TX warning IRQHandler
    .long   CAN3_RxWarn_IRQHandler         ; irq 93 : CAN 3 RX warning IRQHandler
    .long   CAN3_Err_IRQHandler            ; irq 94 : CAN 3 error IRQHandler
    .long   CAN3_ErrFd_IRQHandler          ; irq 95 : CAN 3 error FD IRQHandler
    .long   CAN3_PnWake_IRQHandler         ; irq 96 : CAN 3 pretended network wakeup IRQHandler
    .long   CAN3_SelfWakeup_IRQHandler     ; irq 97 : CAN 3 self-wakeup IRQHandler
    .long   CAN3_Ecc_IRQHandler            ; irq 98 : CAN 3 ECC IRQHandler
    .long   CAN3_Mb0To15_IRQHandler        ; irq 99 : CAN 3 message buffer 0-15 IRQHandler
    .long   CAN3_Mb16To31_IRQHandler       ; irq 100 : CAN 3 message buffer 16-31 IRQHandler
    .long   CAN3_Mb32To47_IRQHandler       ; irq 101 : CAN 3 message buffer 32-47 IRQHandler
    .long   CAN3_Mb48To63_IRQHandler       ; irq 102 : CAN 3 message buffer 48-63 IRQHandler
    .long   CAN4_BusOff_IRQHandler         ; irq 103 : CAN 4 bus off/ bus off done IRQHandler
    .long   CAN4_TxWarn_IRQHandler         ; irq 104 : CAN 4 TX warning IRQHandler
    .long   CAN4_RxWarn_IRQHandler         ; irq 105 : CAN 4 RX warning IRQHandler
    .long   CAN4_Err_IRQHandler            ; irq 106 : CAN 4 error IRQHandler
    .long   CAN4_ErrFd_IRQHandler          ; irq 107 : CAN 4 error FD IRQHandler
    .long   CAN4_PnWake_IRQHandler         ; irq 108 : CAN 4 pretended network wakeup IRQHandler
    .long   CAN4_SelfWakeup_IRQHandler     ; irq 109 : CAN 4 self-wakeup IRQHandler
    .long   CAN4_Ecc_IRQHandler            ; irq 110 : CAN 4 ECC IRQHandler
    .long   CAN4_Mb0To15_IRQHandler        ; irq 111 : CAN 4 message buffer 0-15 IRQHandler
    .long   CAN4_Mb16To31_IRQHandler       ; irq 112 : CAN 4 message buffer 16-31 IRQHandler
    .long   CAN4_Mb32To47_IRQHandler       ; irq 113 : CAN 4 message buffer 32-47 IRQHandler
    .long   CAN4_Mb48To63_IRQHandler       ; irq 114 : CAN 4 message buffer 48-63 IRQHandler
    .long   CAN5_BusOff_IRQHandler         ; irq 115 : CAN 5 bus off/ bus off done IRQHandler
    .long   CAN5_TxWarn_IRQHandler         ; irq 116 : CAN 5 TX warning IRQHandler
    .long   CAN5_RxWarn_IRQHandler         ; irq 117 : CAN 5 RX warning IRQHandler
    .long   CAN5_Err_IRQHandler            ; irq 118 : CAN 5 error IRQHandler
    .long   CAN5_ErrFd_IRQHandler          ; irq 119 : CAN 5 error FD IRQHandler
    .long   CAN5_PnWake_IRQHandler         ; irq 120 : CAN 5 pretended network wakeup IRQHandler
    .long   CAN5_SelfWakeup_IRQHandler     ; irq 121 : CAN 5 self-wakeup IRQHandler
    .long   CAN5_Ecc_IRQHandler            ; irq 122 : CAN 5 ECC IRQHandler
    .long   CAN5_Mb0To15_IRQHandler        ; irq 123 : CAN 5 message buffer 0-15 IRQHandler
    .long   CAN5_Mb16To31_IRQHandler       ; irq 124 : CAN 5 message buffer 16-31 IRQHandler
    .long   CAN5_Mb32To47_IRQHandler       ; irq 125 : CAN 5 message buffer 32-47 IRQHandler
    .long   CAN5_Mb48To63_IRQHandler       ; irq 126 : CAN 5 message buffer 48-63 IRQHandler
    .long   Reserved127_IRQHandler         ; irq 127 : Reserved127 IRQHandler
    .long   Reserved128_IRQHandler         ; irq 128 : Reserved128 IRQHandler
    .long   Reserved129_IRQHandler         ; irq 129 : Reserved129 IRQHandler
    .long   Reserved130_IRQHandler         ; irq 130 : Reserved130 IRQHandler
    .long   Reserved131_IRQHandler         ; irq 131 : Reserved131 IRQHandler
    .long   Reserved132_IRQHandler         ; irq 132 : Reserved132 IRQHandler
    .long   Reserved133_IRQHandler         ; irq 133 : Reserved133 IRQHandler
    .long   Reserved134_IRQHandler         ; irq 134 : Reserved134 IRQHandler
    .long   Reserved135_IRQHandler         ; irq 135 : Reserved135 IRQHandler
    .long   Reserved136_IRQHandler         ; irq 136 : Reserved136 IRQHandler
    .long   Reserved137_IRQHandler         ; irq 137 : Reserved137 IRQHandler
    .long   Reserved138_IRQHandler         ; irq 138 : Reserved138 IRQHandler
    .long   Reserved139_IRQHandler         ; irq 139 : Reserved139 IRQHandler
    .long   Reserved140_IRQHandler         ; irq 140 : Reserved140 IRQHandler
    .long   Reserved141_IRQHandler         ; irq 141 : Reserved141 IRQHandler
    .long   Reserved142_IRQHandler         ; irq 142 : Reserved142 IRQHandler
    .long   Reserved143_IRQHandler         ; irq 143 : Reserved143 IRQHandler
    .long   Reserved144_IRQHandler         ; irq 144 : Reserved144 IRQHandler
    .long   Reserved145_IRQHandler         ; irq 145 : Reserved145 IRQHandler
    .long   Reserved146_IRQHandler         ; irq 146 : Reserved146 IRQHandler
    .long   Reserved147_IRQHandler         ; irq 147 : Reserved147 IRQHandler
    .long   Reserved148_IRQHandler         ; irq 148 : Reserved148 IRQHandler
    .long   Reserved149_IRQHandler         ; irq 149 : Reserved149 IRQHandler
    .long   Reserved150_IRQHandler         ; irq 150 : Reserved150 IRQHandler
    .long   Reserved151_IRQHandler         ; irq 151 : Reserved151 IRQHandler
    .long   Reserved152_IRQHandler         ; irq 152 : Reserved152 IRQHandler
    .long   Reserved153_IRQHandler         ; irq 153 : Reserved153 IRQHandler
    .long   TIM0_Ch_IRQHandler             ; irq 154 : TIM0 CH IRQHandler
    .long   TIM0_Fault_IRQHandler          ; irq 155 : TIM0 Fault IRQHandler
    .long   TIM0_Overflow_IRQHandler       ; irq 156 : TIM0 overflow IRQHandler
    .long   TIM0_Rlfl_IRQHandler           ; irq 157 : TIM0 Rlfl IRQHandler
    .long   TIM1_Ch_IRQHandler             ; irq 158 : TIM1 CH IRQHandler
    .long   TIM1_Fault_IRQHandler          ; irq 159 : TIM1 Fault IRQHandler
    .long   TIM1_Overflow_IRQHandler       ; irq 160 : TIM1 overflow IRQHandler
    .long   TIM1_Rlfl_IRQHandler           ; irq 161 : TIM1 Rlfl IRQHandler
    .long   TIM2_Ch_IRQHandler             ; irq 162 : TIM2 CH IRQHandler
    .long   TIM2_Fault_IRQHandler          ; irq 163 : TIM2 Fault IRQHandler
    .long   TIM2_Overflow_IRQHandler       ; irq 164 : TIM2 overflow IRQHandler
    .long   TIM2_Rlfl_IRQHandler           ; irq 165 : TIM2 Rlfl IRQHandler
    .long   TIM3_Ch_IRQHandler             ; irq 166 : TIM3 CH IRQHandler
    .long   TIM3_Fault_IRQHandler          ; irq 167 : TIM3 Fault IRQHandler
    .long   TIM3_Overflow_IRQHandler       ; irq 168 : TIM3 overflow IRQHandler
    .long   TIM3_Rlfl_IRQHandler           ; irq 169 : TIM3 Rlfl IRQHandler
    .long   TDG0_Tco_IRQHandler            ; irq 170 : TDG0 TCO IRQHandler
    .long   TDG0_Err_IRQHandler            ; irq 171 : TDG0 ERR IRQHandler
    .long   TDG1_Tco_IRQHandler            ; irq 172 : TDG1 TCO IRQHandler
    .long   TDG1_Err_IRQHandler            ; irq 173 : TDG1 ERR IRQHandler
    .long   I2S0_IRQHandler                ; irq 174 : I2S0 IRQHandler
    .long   Reserved175_IRQHandler         ; irq 175 : Reserved175 IRQHandler
    .long   PORTA_IRQHandler               ; irq 176 : port A IRQHandler
    .long   PORTB_IRQHandler               ; irq 177 : port B IRQHandler
    .long   PORTC_IRQHandler               ; irq 178 : port C IRQHandler
    .long   PORTD_IRQHandler               ; irq 179 : port D IRQHandler
    .long   PORTE_IRQHandler               ; irq 180 : port E IRQHandler
    .long   STIM_IRQHandler                ; irq 181 : STIM IRQHandler
    .long   RTC_Alarm_IRQHandler           ; irq 182 : RTC alarm IRQHandler
    .long   RTC_Second_IRQHandler          ; irq 183 : RTC second IRQHandler
    .long   AES_IRQHandler                 ; irq 184 : AES IRQHandler
    .long   TRNG_IRQHandler                ; irq 185 : TRNG IRQHandler
    .long   CMU0_IRQHandler                ; irq 186 : CMU0 IRQHandler
    .long   CMU1_IRQHandler                ; irq 187 : CMU1 IRQHandler
    .long   CMU2_IRQHandler                ; irq 188 : CMU2 IRQHandler
    .long   SERU_ParityErr_IRQHandler      ; irq 189 : SERU parity error IRQHandler
    .long   SERU_ChErr_IRQHandler          ; irq 190 : SERU channel error IRQHandler
    .long   SCC_IRQHandler                 ; irq 191 : SCC IRQHandler
    .long   MCPWM0_Ch_IRQHandler           ; irq 192 : MCPWM0 CH IRQHandler
    .long   MCPWM0_Fault_IRQHandler        ; irq 193 : MCPWM0 fault IRQHandler
    .long   MCPWM0_Overflow_IRQHandler     ; irq 194 : MCPWM0 overflow IRQHandler
    .long   MCPWM0_Rlfl_IRQHandler         ; irq 195 : MCPWM0 Rlfl IRQHandler
    .long   MCPWM1_Ch_IRQHandler           ; irq 196 : MCPWM1 CH IRQHandler
    .long   MCPWM1_Fault_IRQHandler        ; irq 197 : MCPWM1 fault IRQHandler
    .long   MCPWM1_Overflow_IRQHandler     ; irq 198 : MCPWM1 overflow IRQHandler
    .long   MCPWM1_Rlfl_IRQHandler         ; irq 199 : MCPWM1 Rlfl IRQHandler    
    .long   ADC0_IRQHandler                ; irq 200 : ADC0 IRQHandler
    .long   ADC1_IRQHandler                ; irq 201 : ADC1 IRQHandler    
    .long   CMP_IRQHandler                 ; irq 202 : CMP IRQHandler
    .long   SCM_FpuErr_IRQHandler          ; irq 203 : FPU error IRQHandler
    .long   SCM_CacheErr_IRQHandler        ; irq 204 : CACHE error IRQHandler

    .size    __isr_vector, . - __isr_vector

    .text
    .thumb
    
; Reset_Handler Entry 
    .thumb
    .align 4
    .globl   Reset_Handler
    .weak    Reset_Handler
    .type    Reset_Handler, $function
    .set     VTOR, 0xE000ED08
Reset_Handler:
    cpsid   i               ; Mask interrupts 
    ldr     r0, =VTOR
    ldr     r1, =__isr_vector
    str     r1, [r0]
    ldr     r2, [r1]
    msr     msp, r2

; Enable FPU
    ldr     r0, =0xE000ED88
    ldr     r1, [r0]
    ldr     r2, =(0xF << 20)
    orr     r1, r1, r2
    str     r1, [r0]
    dsb
    isb

; unlock PMU
    ldr     r0, =0x4007D000
    ldr     r1, =0x94730000
    str     r1, [r0]
    
; enable PMU LVD in active/low power mode
    ldr     r0, =0x4007D010
    ldr     r1, =0x00000003
    ldr     r2, [r0]
    ldr     r3, =#0x000000C0
    bic     r2, r2, r3
    orr     r1, r1, r2
    str     r1, [r0]
    
; lock pmu
    ldr     r0, =0x4007D000
    ldr     r1, =0x80000000
    str     r1, [r0]

#ifndef START_FROM_SRAM
    ; Clean SRAM ECC 
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

; Copy data from flash to SRAM.
.DATA_LOOP:
    cmp     r2, r3
    beq     COPY_DATA_END
    ldr     r0, [r1]
    str     r0, [r2]
    add     r1, #4
    add     r2, #4
    b      .DATA_LOOP
COPY_DATA_END: 
; Copy bss from flash to SRAM.
    ldr r1, =__bss_start__
    ldr r2, =__bss_end__

    movs    r0, 0
.BSS_LOOP:
    cmp     r1, r2
    beq     COPY_BSS_END
    str     r0, [r1]
    add     r1, #4
    b       .BSS_LOOP
COPY_BSS_END:

    cpsie   i               ; Unmask interrupts 

    ldr   r0,=main
    bx    r0

    .size Reset_Handler, . - Reset_Handler
    
    .align  1
    .weak JumpToSelf
JumpToSelf:
    b JumpToSelf
    .size JumpToSelf, . - JumpToSelf
    .align 1
    .weak DefaultISR
    .type DefaultISR, $function

    .align 1
    .thumb
    .weak NMI_Handler
    .type NMI_Handler, $function
NMI_Handler:
    b .
    .size NMI_Handler, . - NMI_Handler

    .align 1
    .thumb
    .weak HardFault_Handler
    .type HardFault_Handler, $function
HardFault_Handler:
    b .
    .size HardFault_Handler, . - HardFault_Handler

    .align 1
    .thumb
    .weak HardFault_Handler
    .type HardFault_Handler, $function
MemManageFault_Handler:
    b .
    .size MemManageFault_Handler, . - MemManageFault_Handler

    .align 1
    .thumb
    .weak HardFault_Handler
    .type HardFault_Handler, $function
BusFault_Handler:
    b .
    .size BusFault_Handler, . - BusFault_Handler

    .align 1
    .thumb
    .weak HardFault_Handler
    .type HardFault_Handler, $function
UsageFault_Handler:
    b .
    .size UsageFault_Handler, . - UsageFault_Handler

    .align 1
    .thumb
    .weak SVC_Handler
    .type SVC_Handler, $function
SVC_Handler:
    b .
    .size SVC_Handler, . - SVC_Handler

    .align 1
    .thumb
    .weak SVC_Handler
    .type SVC_Handler, $function
DebugMonitor_Handler:
    b .
    .size DebugMonitor_Handler, . - DebugMonitor_Handler

    .align 1
    .thumb
    .weak PendSV_Handler
    .type PendSV_Handler, $function
PendSV_Handler:
    b .
    .size PendSV_Handler, . - PendSV_Handler

    .align 1
    .thumb
    .weak SysTick_Handler
    .type SysTick_Handler, $function
SysTick_Handler:
    b .
    .size SysTick_Handler, . - SysTick_Handler

    .align 1
    .thumb
    .weak DMA_Ch0_IRQHandler
    .type DMA_Ch0_IRQHandler, $function
DMA_Ch0_IRQHandler:
    ldr   r0,=DMA_Ch0_DriverIRQHandler
    bx    r0
    .size DMA_Ch0_IRQHandler, . - DMA_Ch0_IRQHandler

    .align 1
    .thumb
    .weak DMA_Ch1_IRQHandler
    .type DMA_Ch1_IRQHandler, $function
DMA_Ch1_IRQHandler:
    ldr   r0,=DMA_Ch1_DriverIRQHandler
    bx    r0
    .size DMA_Ch1_IRQHandler, . - DMA_Ch1_IRQHandler

    .align 1
    .thumb
    .weak DMA_Ch2_IRQHandler
    .type DMA_Ch2_IRQHandler, $function
DMA_Ch2_IRQHandler:
    ldr   r0,=DMA_Ch2_DriverIRQHandler
    bx    r0
    .size DMA_Ch2_IRQHandler, . - DMA_Ch2_IRQHandler

    .align 1
    .thumb
    .weak DMA_Ch3_IRQHandler
    .type DMA_Ch3_IRQHandler, $function
DMA_Ch3_IRQHandler:
    ldr   r0,=DMA_Ch3_DriverIRQHandler
    bx    r0
    .size DMA_Ch3_IRQHandler, . - DMA_Ch3_IRQHandler

    .align 1
    .thumb
    .weak DMA_Ch4_IRQHandler
    .type DMA_Ch4_IRQHandler, $function
DMA_Ch4_IRQHandler:
    ldr   r0,=DMA_Ch4_DriverIRQHandler
    bx    r0
    .size DMA_Ch4_IRQHandler, . - DMA_Ch4_IRQHandler

    .align 1
    .thumb
    .weak DMA_Ch5_IRQHandler
    .type DMA_Ch5_IRQHandler, $function
DMA_Ch5_IRQHandler:
    ldr   r0,=DMA_Ch5_DriverIRQHandler
    bx    r0
    .size DMA_Ch5_IRQHandler, . - DMA_Ch5_IRQHandler

    .align 1
    .thumb
    .weak DMA_Ch6_IRQHandler
    .type DMA_Ch6_IRQHandler, $function
DMA_Ch6_IRQHandler:
    ldr   r0,=DMA_Ch6_DriverIRQHandler
    bx    r0
    .size DMA_Ch6_IRQHandler, . - DMA_Ch6_IRQHandler

    .align 1
    .thumb
    .weak DMA_Ch7_IRQHandler
    .type DMA_Ch7_IRQHandler, $function
DMA_Ch7_IRQHandler:
    ldr   r0,=DMA_Ch7_DriverIRQHandler
    bx    r0
    .size DMA_Ch7_IRQHandler, . - DMA_Ch7_IRQHandler

    .align 1
    .thumb
    .weak DMA_Ch8_IRQHandler
    .type DMA_Ch8_IRQHandler, $function
DMA_Ch8_IRQHandler:
    ldr   r0,=DMA_Ch8_DriverIRQHandler
    bx    r0
    .size DMA_Ch8_IRQHandler, . - DMA_Ch8_IRQHandler

    .align 1
    .thumb
    .weak DMA_Ch9_IRQHandler
    .type DMA_Ch9_IRQHandler, $function
DMA_Ch9_IRQHandler:
    ldr   r0,=DMA_Ch9_DriverIRQHandler
    bx    r0
    .size DMA_Ch9_IRQHandler, . - DMA_Ch9_IRQHandler

    .align 1
    .thumb
    .weak DMA_Ch10_IRQHandler
    .type DMA_Ch10_IRQHandler, $function
DMA_Ch10_IRQHandler:
    ldr   r0,=DMA_Ch10_DriverIRQHandler
    bx    r0
    .size DMA_Ch10_IRQHandler, . - DMA_Ch10_IRQHandler

    .align 1
    .thumb
    .weak DMA_Ch11_IRQHandler
    .type DMA_Ch11_IRQHandler, $function
DMA_Ch11_IRQHandler:
    ldr   r0,=DMA_Ch11_DriverIRQHandler
    bx    r0
    .size DMA_Ch11_IRQHandler, . - DMA_Ch11_IRQHandler

    .align 1
    .thumb
    .weak DMA_Ch12_IRQHandler
    .type DMA_Ch12_IRQHandler, $function
DMA_Ch12_IRQHandler:
    ldr   r0,=DMA_Ch12_DriverIRQHandler
    bx    r0
    .size DMA_Ch12_IRQHandler, . - DMA_Ch12_IRQHandler

    .align 1
    .thumb
    .weak DMA_Ch13_IRQHandler
    .type DMA_Ch13_IRQHandler, $function
DMA_Ch13_IRQHandler:
    ldr   r0,=DMA_Ch13_DriverIRQHandler
    bx    r0
    .size DMA_Ch13_IRQHandler, . - DMA_Ch13_IRQHandler

    .align 1
    .thumb
    .weak DMA_Ch14_IRQHandler
    .type DMA_Ch14_IRQHandler, $function
DMA_Ch14_IRQHandler:
    ldr   r0,=DMA_Ch14_DriverIRQHandler
    bx    r0
    .size DMA_Ch14_IRQHandler, . - DMA_Ch14_IRQHandler

    .align 1
    .thumb
    .weak DMA_Ch15_IRQHandler
    .type DMA_Ch15_IRQHandler, $function
DMA_Ch15_IRQHandler:
    ldr   r0,=DMA_Ch15_DriverIRQHandler
    bx    r0
    .size DMA_Ch15_IRQHandler, . - DMA_Ch15_IRQHandler

    .align 1
    .thumb
    .weak DMA_Err_IRQHandler
    .type DMA_Err_IRQHandler, $function
DMA_Err_IRQHandler:
    ldr   r0,=DMA_Err_DriverIRQHandler
    bx    r0
    .size DMA_Err_IRQHandler, . - DMA_Err_IRQHandler

    .align 1
    .thumb
    .weak FLASH_CmdComplete_IRQHandler
    .type FLASH_CmdComplete_IRQHandler, $function
FLASH_CmdComplete_IRQHandler:
    ldr   r0,=FLASH_CmdComplete_DriverIRQHandler
    bx    r0
    .size FLASH_CmdComplete_IRQHandler, . - FLASH_CmdComplete_IRQHandler

    .align 1
    .thumb
    .weak FLASH_Ecc_IRQHandler
    .type FLASH_Ecc_IRQHandler, $function
FLASH_Ecc_IRQHandler:
    ldr   r0,=FLASH_Ecc_DriverIRQHandler
    bx    r0
    .size FLASH_Ecc_IRQHandler, . - FLASH_Ecc_IRQHandler

    .align 1
    .thumb
    .weak PMU_IRQHandler
    .type PMU_IRQHandler, $function
PMU_IRQHandler:
    ldr   r0,=PMU_DriverIRQHandler
    bx    r0
    .size PMU_IRQHandler, . - PMU_IRQHandler

    .align 1
    .thumb
    .weak WDOG_IRQHandler
    .type WDOG_IRQHandler, $function
WDOG_IRQHandler:
    ldr   r0,=WDOG_DriverIRQHandler
    bx    r0
    .size WDOG_IRQHandler, . - WDOG_IRQHandler

    .align 1
    .thumb
    .weak EWDT_IRQHandler
    .type EWDT_IRQHandler, $function
EWDT_IRQHandler:
    ldr   r0,=EWDT_DriverIRQHandler
    bx    r0
    .size EWDT_IRQHandler, . - EWDT_IRQHandler

    .align 1
    .thumb
    .weak SRMC_IRQHandler
    .type SRMC_IRQHandler, $function
SRMC_IRQHandler:
    ldr   r0,=SRMC_DriverIRQHandler
    bx    r0
    .size SRMC_IRQHandler, . - SRMC_IRQHandler

    .align 1
    .thumb
    .weak I2C0_IRQHandler
    .type I2C0_IRQHandler, $function
I2C0_IRQHandler:
    ldr   r0,=I2C0_DriverIRQHandler
    bx    r0
    .size I2C0_IRQHandler, . - I2C0_IRQHandler

    .align 1
    .thumb
    .weak I2C1_IRQHandler
    .type I2C1_IRQHandler, $function
I2C1_IRQHandler:
    ldr   r0,=I2C1_DriverIRQHandler
    bx    r0
    .size I2C1_IRQHandler, . - I2C1_IRQHandler

    .align 1
    .thumb
    .weak SPI0_Txe_IRQHandler
    .type SPI0_Txe_IRQHandler, $function
SPI0_Txe_IRQHandler:
    ldr   r0,=SPI0_Txe_DriverIRQHandler
    bx    r0
    .size SPI0_Txe_IRQHandler, . - SPI0_Txe_IRQHandler

    .align 1
    .thumb
    .weak SPI0_Txo_IRQHandler
    .type SPI0_Txo_IRQHandler, $function
SPI0_Txo_IRQHandler:
    ldr   r0,=SPI0_Txo_DriverIRQHandler
    bx    r0
    .size SPI0_Txo_IRQHandler, . - SPI0_Txo_IRQHandler

    .align 1
    .thumb
    .weak SPI0_Rxf_IRQHandler
    .type SPI0_Rxf_IRQHandler, $function
SPI0_Rxf_IRQHandler:
    ldr   r0,=SPI0_Rxf_DriverIRQHandler
    bx    r0
    .size SPI0_Rxf_IRQHandler, . - SPI0_Rxf_IRQHandler

    .align 1
    .thumb
    .weak SPI0_Rxo_IRQHandler
    .type SPI0_Rxo_IRQHandler, $function
SPI0_Rxo_IRQHandler:
    ldr   r0,=SPI0_Rxo_DriverIRQHandler
    bx    r0
    .size SPI0_Rxo_IRQHandler, . - SPI0_Rxo_IRQHandler

    .align 1
    .thumb
    .weak SPI0_Rxu_IRQHandler
    .type SPI0_Rxu_IRQHandler, $function
SPI0_Rxu_IRQHandler:
    ldr   r0,=SPI0_Rxu_DriverIRQHandler
    bx    r0
    .size SPI0_Rxu_IRQHandler, . - SPI0_Rxu_IRQHandler

    .align 1
    .thumb
    .weak SPI1_Txe_IRQHandler
    .type SPI1_Txe_IRQHandler, $function
SPI1_Txe_IRQHandler:
    ldr   r0,=SPI1_Txe_DriverIRQHandler
    bx    r0
    .size SPI1_Txe_IRQHandler, . - SPI1_Txe_IRQHandler

    .align 1
    .thumb
    .weak SPI1_Txo_IRQHandler
    .type SPI1_Txo_IRQHandler, $function
SPI1_Txo_IRQHandler:
    ldr   r0,=SPI1_Txo_DriverIRQHandler
    bx    r0
    .size SPI1_Txo_IRQHandler, . - SPI1_Txo_IRQHandler

    .align 1
    .thumb
    .weak SPI1_Rxf_IRQHandler
    .type SPI1_Rxf_IRQHandler, $function
SPI1_Rxf_IRQHandler:
    ldr   r0,=SPI1_Rxf_DriverIRQHandler
    bx    r0
    .size SPI1_Rxf_IRQHandler, . - SPI1_Rxf_IRQHandler

    .align 1
    .thumb
    .weak SPI1_Rxo_IRQHandler
    .type SPI1_Rxo_IRQHandler, $function
SPI1_Rxo_IRQHandler:
    ldr   r0,=SPI1_Rxo_DriverIRQHandler
    bx    r0
    .size SPI1_Rxo_IRQHandler, . - SPI1_Rxo_IRQHandler

    .align 1
    .thumb
    .weak SPI1_Rxu_IRQHandler
    .type SPI1_Rxu_IRQHandler, $function
SPI1_Rxu_IRQHandler:
    ldr   r0,=SPI1_Rxu_DriverIRQHandler
    bx    r0
    .size SPI1_Rxu_IRQHandler, . - SPI1_Rxu_IRQHandler

    .align 1
    .thumb
    .weak SPI2_Txe_IRQHandler
    .type SPI2_Txe_IRQHandler, $function
SPI2_Txe_IRQHandler:
    ldr   r0,=SPI2_Txe_DriverIRQHandler
    bx    r0
    .size SPI2_Txe_IRQHandler, . - SPI2_Txe_IRQHandler

    .align 1
    .thumb
    .weak SPI2_Txo_IRQHandler
    .type SPI2_Txo_IRQHandler, $function
SPI2_Txo_IRQHandler:
    ldr   r0,=SPI2_Txo_DriverIRQHandler
    bx    r0
    .size SPI2_Txo_IRQHandler, . - SPI2_Txo_IRQHandler

    .align 1
    .thumb
    .weak SPI2_Rxf_IRQHandler
    .type SPI2_Rxf_IRQHandler, $function
SPI2_Rxf_IRQHandler:
    ldr   r0,=SPI2_Rxf_DriverIRQHandler
    bx    r0
    .size SPI2_Rxf_IRQHandler, . - SPI2_Rxf_IRQHandler

    .align 1
    .thumb
    .weak SPI2_Rxo_IRQHandler
    .type SPI2_Rxo_IRQHandler, $function
SPI2_Rxo_IRQHandler:
    ldr   r0,=SPI2_Rxo_DriverIRQHandler
    bx    r0
    .size SPI2_Rxo_IRQHandler, . - SPI2_Rxo_IRQHandler

    .align 1
    .thumb
    .weak SPI2_Rxu_IRQHandler
    .type SPI2_Rxu_IRQHandler, $function
SPI2_Rxu_IRQHandler:
    ldr   r0,=SPI2_Rxu_DriverIRQHandler
    bx    r0
    .size SPI2_Rxu_IRQHandler, . - SPI2_Rxu_IRQHandler

    .align 1
    .thumb
    .weak SPI3_Txe_IRQHandler
    .type SPI3_Txe_IRQHandler, $function
SPI3_Txe_IRQHandler:
    ldr   r0,=SPI3_Txe_DriverIRQHandler
    bx    r0
    .size SPI3_Txe_IRQHandler, . - SPI3_Txe_IRQHandler

    .align 1
    .thumb
    .weak SPI3_Txo_IRQHandler
    .type SPI3_Txo_IRQHandler, $function
SPI3_Txo_IRQHandler:
    ldr   r0,=SPI3_Txo_DriverIRQHandler
    bx    r0
    .size SPI3_Txo_IRQHandler, . - SPI3_Txo_IRQHandler

    .align 1
    .thumb
    .weak SPI3_Rxf_IRQHandler
    .type SPI3_Rxf_IRQHandler, $function
SPI3_Rxf_IRQHandler:
    ldr   r0,=SPI3_Rxf_DriverIRQHandler
    bx    r0
    .size SPI3_Rxf_IRQHandler, . - SPI3_Rxf_IRQHandler

    .align 1
    .thumb
    .weak SPI3_Rxo_IRQHandler
    .type SPI3_Rxo_IRQHandler, $function
SPI3_Rxo_IRQHandler:
    ldr   r0,=SPI3_Rxo_DriverIRQHandler
    bx    r0
    .size SPI3_Rxo_IRQHandler, . - SPI3_Rxo_IRQHandler

    .align 1
    .thumb
    .weak SPI3_Rxu_IRQHandler
    .type SPI3_Rxu_IRQHandler, $function
SPI3_Rxu_IRQHandler:
    ldr   r0,=SPI3_Rxu_DriverIRQHandler
    bx    r0
    .size SPI3_Rxu_IRQHandler, . - SPI3_Rxu_IRQHandler

    .align 1
    .thumb
    .weak UART0_IRQHandler
    .type UART0_IRQHandler, $function
UART0_IRQHandler:
    ldr   r0,=UART0_DriverIRQHandler
    bx    r0
    .size UART0_IRQHandler, . - UART0_IRQHandler

    .align 1
    .thumb
    .weak UART1_IRQHandler
    .type UART1_IRQHandler, $function
UART1_IRQHandler:
    ldr   r0,=UART1_DriverIRQHandler
    bx    r0
    .size UART1_IRQHandler, . - UART1_IRQHandler

    .align 1
    .thumb
    .weak UART2_IRQHandler
    .type UART2_IRQHandler, $function
UART2_IRQHandler:
    ldr   r0,=UART2_DriverIRQHandler
    bx    r0
    .size UART2_IRQHandler, . - UART2_IRQHandler

    .align 1
    .thumb
    .weak UART3_IRQHandler
    .type UART3_IRQHandler, $function
UART3_IRQHandler:
    ldr   r0,=UART3_DriverIRQHandler
    bx    r0
    .size UART3_IRQHandler, . - UART3_IRQHandler

    .align 1
    .thumb
    .weak UART4_IRQHandler
    .type UART4_IRQHandler, $function
UART4_IRQHandler:
    ldr   r0,=UART4_DriverIRQHandler
    bx    r0
    .size UART4_IRQHandler, . - UART4_IRQHandler

    .align 1
    .thumb
    .weak UART5_IRQHandler
    .type UART5_IRQHandler, $function
UART5_IRQHandler:
    ldr   r0,=UART5_DriverIRQHandler
    bx    r0
    .size UART5_IRQHandler, . - UART5_IRQHandler

    .align 1
    .thumb
    .weak CAN0_BusOff_IRQHandler
    .type CAN0_BusOff_IRQHandler, $function
CAN0_BusOff_IRQHandler:
    ldr   r0,=CAN0_BusOff_DriverIRQHandler
    bx    r0
    .size CAN0_BusOff_IRQHandler, . - CAN0_BusOff_IRQHandler

    .align 1
    .thumb
    .weak CAN0_TxWarn_IRQHandler
    .type CAN0_TxWarn_IRQHandler, $function
CAN0_TxWarn_IRQHandler:
    ldr   r0,=CAN0_TxWarn_DriverIRQHandler
    bx    r0
    .size CAN0_TxWarn_IRQHandler, . - CAN0_TxWarn_IRQHandler

    .align 1
    .thumb
    .weak CAN0_RxWarn_IRQHandler
    .type CAN0_RxWarn_IRQHandler, $function
CAN0_RxWarn_IRQHandler:
    ldr   r0,=CAN0_RxWarn_DriverIRQHandler
    bx    r0
    .size CAN0_RxWarn_IRQHandler, . - CAN0_RxWarn_IRQHandler

    .align 1
    .thumb
    .weak CAN0_Err_IRQHandler
    .type CAN0_Err_IRQHandler, $function
CAN0_Err_IRQHandler:
    ldr   r0,=CAN0_Err_DriverIRQHandler
    bx    r0
    .size CAN0_Err_IRQHandler, . - CAN0_Err_IRQHandler

    .align 1
    .thumb
    .weak CAN0_ErrFd_IRQHandler
    .type CAN0_ErrFd_IRQHandler, $function
CAN0_ErrFd_IRQHandler:
    ldr   r0,=CAN0_ErrFd_DriverIRQHandler
    bx    r0
    .size CAN0_ErrFd_IRQHandler, . - CAN0_ErrFd_IRQHandler

    .align 1
    .thumb
    .weak CAN0_PnWake_IRQHandler
    .type CAN0_PnWake_IRQHandler, $function
CAN0_PnWake_IRQHandler:
    ldr   r0,=CAN0_PnWake_DriverIRQHandler
    bx    r0
    .size CAN0_PnWake_IRQHandler, . - CAN0_PnWake_IRQHandler

    .align 1
    .thumb
    .weak CAN0_SelfWakeup_IRQHandler
    .type CAN0_SelfWakeup_IRQHandler, $function
CAN0_SelfWakeup_IRQHandler:
    ldr   r0,=CAN0_SelfWakeup_DriverIRQHandler
    bx    r0
    .size CAN0_SelfWakeup_IRQHandler, . - CAN0_SelfWakeup_IRQHandler

    .align 1
    .thumb
    .weak CAN0_Ecc_IRQHandler
    .type CAN0_Ecc_IRQHandler, $function
CAN0_Ecc_IRQHandler:
    ldr   r0,=CAN0_Ecc_DriverIRQHandler
    bx    r0
    .size CAN0_Ecc_IRQHandler, . - CAN0_Ecc_IRQHandler

    .align 1
    .thumb
    .weak CAN0_Mb0To15_IRQHandler
    .type CAN0_Mb0To15_IRQHandler, $function
CAN0_Mb0To15_IRQHandler:
    ldr   r0,=CAN0_Mb0To15_DriverIRQHandler
    bx    r0
    .size CAN0_Mb0To15_IRQHandler, . - CAN0_Mb0To15_IRQHandler

    .align 1
    .thumb
    .weak CAN0_Mb16To31_IRQHandler
    .type CAN0_Mb16To31_IRQHandler, $function
CAN0_Mb16To31_IRQHandler:
    ldr   r0,=CAN0_Mb16To31_DriverIRQHandler
    bx    r0
    .size CAN0_Mb16To31_IRQHandler, . - CAN0_Mb16To31_IRQHandler

    .align 1
    .thumb
    .weak CAN0_Mb32To47_IRQHandler
    .type CAN0_Mb32To47_IRQHandler, $function
CAN0_Mb32To47_IRQHandler:
    ldr   r0,=CAN0_Mb32To47_DriverIRQHandler
    bx    r0
    .size CAN0_Mb32To47_IRQHandler, . - CAN0_Mb32To47_IRQHandler

    .align 1
    .thumb
    .weak CAN0_Mb48To63_IRQHandler
    .type CAN0_Mb48To63_IRQHandler, $function
CAN0_Mb48To63_IRQHandler:
    ldr   r0,=CAN0_Mb48To63_DriverIRQHandler
    bx    r0
    .size CAN0_Mb48To63_IRQHandler, . - CAN0_Mb48To63_IRQHandler

    .align 1
    .thumb
    .weak CAN1_BusOff_IRQHandler
    .type CAN1_BusOff_IRQHandler, $function
CAN1_BusOff_IRQHandler:
    ldr   r0,=CAN1_BusOff_DriverIRQHandler
    bx    r0
    .size CAN1_BusOff_IRQHandler, . - CAN1_BusOff_IRQHandler

    .align 1
    .thumb
    .weak CAN1_TxWarn_IRQHandler
    .type CAN1_TxWarn_IRQHandler, $function
CAN1_TxWarn_IRQHandler:
    ldr   r0,=CAN1_TxWarn_DriverIRQHandler
    bx    r0
    .size CAN1_TxWarn_IRQHandler, . - CAN1_TxWarn_IRQHandler

    .align 1
    .thumb
    .weak CAN1_RxWarn_IRQHandler
    .type CAN1_RxWarn_IRQHandler, $function
CAN1_RxWarn_IRQHandler:
    ldr   r0,=CAN1_RxWarn_DriverIRQHandler
    bx    r0
    .size CAN1_RxWarn_IRQHandler, . - CAN1_RxWarn_IRQHandler

    .align 1
    .thumb
    .weak CAN1_Err_IRQHandler
    .type CAN1_Err_IRQHandler, $function
CAN1_Err_IRQHandler:
    ldr   r0,=CAN1_Err_DriverIRQHandler
    bx    r0
    .size CAN1_Err_IRQHandler, . - CAN1_Err_IRQHandler

    .align 1
    .thumb
    .weak CAN1_ErrFd_IRQHandler
    .type CAN1_ErrFd_IRQHandler, $function
CAN1_ErrFd_IRQHandler:
    ldr   r0,=CAN1_ErrFd_DriverIRQHandler
    bx    r0
    .size CAN1_ErrFd_IRQHandler, . - CAN1_ErrFd_IRQHandler

    .align 1
    .thumb
    .weak CAN1_PnWake_IRQHandler
    .type CAN1_PnWake_IRQHandler, $function
CAN1_PnWake_IRQHandler:
    ldr   r0,=CAN1_PnWake_DriverIRQHandler
    bx    r0
    .size CAN1_PnWake_IRQHandler, . - CAN1_PnWake_IRQHandler

    .align 1
    .thumb
    .weak CAN1_SelfWakeup_IRQHandler
    .type CAN1_SelfWakeup_IRQHandler, $function
CAN1_SelfWakeup_IRQHandler:
    ldr   r0,=CAN1_SelfWakeup_DriverIRQHandler
    bx    r0
    .size CAN1_SelfWakeup_IRQHandler, . - CAN1_SelfWakeup_IRQHandler

    .align 1
    .thumb
    .weak CAN1_Ecc_IRQHandler
    .type CAN1_Ecc_IRQHandler, $function
CAN1_Ecc_IRQHandler:
    ldr   r0,=CAN1_Ecc_DriverIRQHandler
    bx    r0
    .size CAN1_Ecc_IRQHandler, . - CAN1_Ecc_IRQHandler

    .align 1
    .thumb
    .weak CAN1_Mb0To15_IRQHandler
    .type CAN1_Mb0To15_IRQHandler, $function
CAN1_Mb0To15_IRQHandler:
    ldr   r0,=CAN1_Mb0To15_DriverIRQHandler
    bx    r0
    .size CAN1_Mb0To15_IRQHandler, . - CAN1_Mb0To15_IRQHandler

    .align 1
    .thumb
    .weak CAN1_Mb16To31_IRQHandler
    .type CAN1_Mb16To31_IRQHandler, $function
CAN1_Mb16To31_IRQHandler:
    ldr   r0,=CAN1_Mb16To31_DriverIRQHandler
    bx    r0
    .size CAN1_Mb16To31_IRQHandler, . - CAN1_Mb16To31_IRQHandler

    .align 1
    .thumb
    .weak CAN1_Mb32To47_IRQHandler
    .type CAN1_Mb32To47_IRQHandler, $function
CAN1_Mb32To47_IRQHandler:
    ldr   r0,=CAN1_Mb32To47_DriverIRQHandler
    bx    r0
    .size CAN1_Mb32To47_IRQHandler, . - CAN1_Mb32To47_IRQHandler

    .align 1
    .thumb
    .weak CAN1_Mb48To63_IRQHandler
    .type CAN1_Mb48To63_IRQHandler, $function
CAN1_Mb48To63_IRQHandler:
    ldr   r0,=CAN1_Mb48To63_DriverIRQHandler
    bx    r0
    .size CAN1_Mb48To63_IRQHandler, . - CAN1_Mb48To63_IRQHandler

    .align 1
    .thumb
    .weak CAN2_BusOff_IRQHandler
    .type CAN2_BusOff_IRQHandler, $function
CAN2_BusOff_IRQHandler:
    ldr   r0,=CAN2_BusOff_DriverIRQHandler
    bx    r0
    .size CAN2_BusOff_IRQHandler, . - CAN2_BusOff_IRQHandler

    .align 1
    .thumb
    .weak CAN2_TxWarn_IRQHandler
    .type CAN2_TxWarn_IRQHandler, $function
CAN2_TxWarn_IRQHandler:
    ldr   r0,=CAN2_TxWarn_DriverIRQHandler
    bx    r0
    .size CAN2_TxWarn_IRQHandler, . - CAN2_TxWarn_IRQHandler

    .align 1
    .thumb
    .weak CAN2_RxWarn_IRQHandler
    .type CAN2_RxWarn_IRQHandler, $function
CAN2_RxWarn_IRQHandler:
    ldr   r0,=CAN2_RxWarn_DriverIRQHandler
    bx    r0
    .size CAN2_RxWarn_IRQHandler, . - CAN2_RxWarn_IRQHandler

    .align 1
    .thumb
    .weak CAN2_Err_IRQHandler
    .type CAN2_Err_IRQHandler, $function
CAN2_Err_IRQHandler:
    ldr   r0,=CAN2_Err_DriverIRQHandler
    bx    r0
    .size CAN2_Err_IRQHandler, . - CAN2_Err_IRQHandler

    .align 1
    .thumb
    .weak CAN2_ErrFd_IRQHandler
    .type CAN2_ErrFd_IRQHandler, $function
CAN2_ErrFd_IRQHandler:
    ldr   r0,=CAN2_ErrFd_DriverIRQHandler
    bx    r0
    .size CAN2_ErrFd_IRQHandler, . - CAN2_ErrFd_IRQHandler

    .align 1
    .thumb
    .weak CAN2_PnWake_IRQHandler
    .type CAN2_PnWake_IRQHandler, $function
CAN2_PnWake_IRQHandler:
    ldr   r0,=CAN2_PnWake_DriverIRQHandler
    bx    r0
    .size CAN2_PnWake_IRQHandler, . - CAN2_PnWake_IRQHandler

    .align 1
    .thumb
    .weak CAN2_SelfWakeup_IRQHandler
    .type CAN2_SelfWakeup_IRQHandler, $function
CAN2_SelfWakeup_IRQHandler:
    ldr   r0,=CAN2_SelfWakeup_DriverIRQHandler
    bx    r0
    .size CAN2_SelfWakeup_IRQHandler, . - CAN2_SelfWakeup_IRQHandler

    .align 1
    .thumb
    .weak CAN2_Ecc_IRQHandler
    .type CAN2_Ecc_IRQHandler, $function
CAN2_Ecc_IRQHandler:
    ldr   r0,=CAN2_Ecc_DriverIRQHandler
    bx    r0
    .size CAN2_Ecc_IRQHandler, . - CAN2_Ecc_IRQHandler

    .align 1
    .thumb
    .weak CAN2_Mb0To15_IRQHandler
    .type CAN2_Mb0To15_IRQHandler, $function
CAN2_Mb0To15_IRQHandler:
    ldr   r0,=CAN2_Mb0To15_DriverIRQHandler
    bx    r0
    .size CAN2_Mb0To15_IRQHandler, . - CAN2_Mb0To15_IRQHandler

    .align 1
    .thumb
    .weak CAN2_Mb16To31_IRQHandler
    .type CAN2_Mb16To31_IRQHandler, $function
CAN2_Mb16To31_IRQHandler:
    ldr   r0,=CAN2_Mb16To31_DriverIRQHandler
    bx    r0
    .size CAN2_Mb16To31_IRQHandler, . - CAN2_Mb16To31_IRQHandler

    .align 1
    .thumb
    .weak CAN2_Mb32To47_IRQHandler
    .type CAN2_Mb32To47_IRQHandler, $function
CAN2_Mb32To47_IRQHandler:
    ldr   r0,=CAN2_Mb32To47_DriverIRQHandler
    bx    r0
    .size CAN2_Mb32To47_IRQHandler, . - CAN2_Mb32To47_IRQHandler

    .align 1
    .thumb
    .weak CAN2_Mb48To63_IRQHandler
    .type CAN2_Mb48To63_IRQHandler, $function
CAN2_Mb48To63_IRQHandler:
    ldr   r0,=CAN2_Mb48To63_DriverIRQHandler
    bx    r0
    .size CAN2_Mb48To63_IRQHandler, . - CAN2_Mb48To63_IRQHandler

    .align 1
    .thumb
    .weak CAN3_BusOff_IRQHandler
    .type CAN3_BusOff_IRQHandler, $function
CAN3_BusOff_IRQHandler:
    ldr   r0,=CAN3_BusOff_DriverIRQHandler
    bx    r0
    .size CAN3_BusOff_IRQHandler, . - CAN3_BusOff_IRQHandler

    .align 1
    .thumb
    .weak CAN3_TxWarn_IRQHandler
    .type CAN3_TxWarn_IRQHandler, $function
CAN3_TxWarn_IRQHandler:
    ldr   r0,=CAN3_TxWarn_DriverIRQHandler
    bx    r0
    .size CAN3_TxWarn_IRQHandler, . - CAN3_TxWarn_IRQHandler

    .align 1
    .thumb
    .weak CAN3_RxWarn_IRQHandler
    .type CAN3_RxWarn_IRQHandler, $function
CAN3_RxWarn_IRQHandler:
    ldr   r0,=CAN3_RxWarn_DriverIRQHandler
    bx    r0
    .size CAN3_RxWarn_IRQHandler, . - CAN3_RxWarn_IRQHandler

    .align 1
    .thumb
    .weak CAN3_Err_IRQHandler
    .type CAN3_Err_IRQHandler, $function
CAN3_Err_IRQHandler:
    ldr   r0,=CAN3_Err_DriverIRQHandler
    bx    r0
    .size CAN3_Err_IRQHandler, . - CAN3_Err_IRQHandler

    .align 1
    .thumb
    .weak CAN3_ErrFd_IRQHandler
    .type CAN3_ErrFd_IRQHandler, $function
CAN3_ErrFd_IRQHandler:
    ldr   r0,=CAN3_ErrFd_DriverIRQHandler
    bx    r0
    .size CAN3_ErrFd_IRQHandler, . - CAN3_ErrFd_IRQHandler

    .align 1
    .thumb
    .weak CAN3_PnWake_IRQHandler
    .type CAN3_PnWake_IRQHandler, $function
CAN3_PnWake_IRQHandler:
    ldr   r0,=CAN3_PnWake_DriverIRQHandler
    bx    r0
    .size CAN3_PnWake_IRQHandler, . - CAN3_PnWake_IRQHandler

    .align 1
    .thumb
    .weak CAN3_SelfWakeup_IRQHandler
    .type CAN3_SelfWakeup_IRQHandler, $function
CAN3_SelfWakeup_IRQHandler:
    ldr   r0,=CAN3_SelfWakeup_DriverIRQHandler
    bx    r0
    .size CAN3_SelfWakeup_IRQHandler, . - CAN3_SelfWakeup_IRQHandler

    .align 1
    .thumb
    .weak CAN3_Ecc_IRQHandler
    .type CAN3_Ecc_IRQHandler, $function
CAN3_Ecc_IRQHandler:
    ldr   r0,=CAN3_Ecc_DriverIRQHandler
    bx    r0
    .size CAN3_Ecc_IRQHandler, . - CAN3_Ecc_IRQHandler

    .align 1
    .thumb
    .weak CAN3_Mb0To15_IRQHandler
    .type CAN3_Mb0To15_IRQHandler, $function
CAN3_Mb0To15_IRQHandler:
    ldr   r0,=CAN3_Mb0To15_DriverIRQHandler
    bx    r0
    .size CAN3_Mb0To15_IRQHandler, . - CAN3_Mb0To15_IRQHandler

    .align 1
    .thumb
    .weak CAN3_Mb16To31_IRQHandler
    .type CAN3_Mb16To31_IRQHandler, $function
CAN3_Mb16To31_IRQHandler:
    ldr   r0,=CAN3_Mb16To31_DriverIRQHandler
    bx    r0
    .size CAN3_Mb16To31_IRQHandler, . - CAN3_Mb16To31_IRQHandler

    .align 1
    .thumb
    .weak CAN3_Mb32To47_IRQHandler
    .type CAN3_Mb32To47_IRQHandler, $function
CAN3_Mb32To47_IRQHandler:
    ldr   r0,=CAN3_Mb32To47_DriverIRQHandler
    bx    r0
    .size CAN3_Mb32To47_IRQHandler, . - CAN3_Mb32To47_IRQHandler

    .align 1
    .thumb
    .weak CAN3_Mb48To63_IRQHandler
    .type CAN3_Mb48To63_IRQHandler, $function
CAN3_Mb48To63_IRQHandler:
    ldr   r0,=CAN3_Mb48To63_DriverIRQHandler
    bx    r0
    .size CAN3_Mb48To63_IRQHandler, . - CAN3_Mb48To63_IRQHandler

    .align 1
    .thumb
    .weak CAN4_BusOff_IRQHandler
    .type CAN4_BusOff_IRQHandler, $function
CAN4_BusOff_IRQHandler:
    ldr   r0,=CAN4_BusOff_DriverIRQHandler
    bx    r0
    .size CAN4_BusOff_IRQHandler, . - CAN4_BusOff_IRQHandler

    .align 1
    .thumb
    .weak CAN4_TxWarn_IRQHandler
    .type CAN4_TxWarn_IRQHandler, $function
CAN4_TxWarn_IRQHandler:
    ldr   r0,=CAN4_TxWarn_DriverIRQHandler
    bx    r0
    .size CAN4_TxWarn_IRQHandler, . - CAN4_TxWarn_IRQHandler

    .align 1
    .thumb
    .weak CAN4_RxWarn_IRQHandler
    .type CAN4_RxWarn_IRQHandler, $function
CAN4_RxWarn_IRQHandler:
    ldr   r0,=CAN4_RxWarn_DriverIRQHandler
    bx    r0
    .size CAN4_RxWarn_IRQHandler, . - CAN4_RxWarn_IRQHandler

    .align 1
    .thumb
    .weak CAN4_Err_IRQHandler
    .type CAN4_Err_IRQHandler, $function
CAN4_Err_IRQHandler:
    ldr   r0,=CAN4_Err_DriverIRQHandler
    bx    r0
    .size CAN4_Err_IRQHandler, . - CAN4_Err_IRQHandler

    .align 1
    .thumb
    .weak CAN4_ErrFd_IRQHandler
    .type CAN4_ErrFd_IRQHandler, $function
CAN4_ErrFd_IRQHandler:
    ldr   r0,=CAN4_ErrFd_DriverIRQHandler
    bx    r0
    .size CAN4_ErrFd_IRQHandler, . - CAN4_ErrFd_IRQHandler

    .align 1
    .thumb
    .weak CAN4_PnWake_IRQHandler
    .type CAN4_PnWake_IRQHandler, $function
CAN4_PnWake_IRQHandler:
    ldr   r0,=CAN4_PnWake_DriverIRQHandler
    bx    r0
    .size CAN4_PnWake_IRQHandler, . - CAN4_PnWake_IRQHandler

    .align 1
    .thumb
    .weak CAN4_SelfWakeup_IRQHandler
    .type CAN4_SelfWakeup_IRQHandler, $function
CAN4_SelfWakeup_IRQHandler:
    ldr   r0,=CAN4_SelfWakeup_DriverIRQHandler
    bx    r0
    .size CAN4_SelfWakeup_IRQHandler, . - CAN4_SelfWakeup_IRQHandler

    .align 1
    .thumb
    .weak CAN4_Ecc_IRQHandler
    .type CAN4_Ecc_IRQHandler, $function
CAN4_Ecc_IRQHandler:
    ldr   r0,=CAN4_Ecc_DriverIRQHandler
    bx    r0
    .size CAN4_Ecc_IRQHandler, . - CAN4_Ecc_IRQHandler

    .align 1
    .thumb
    .weak CAN4_Mb0To15_IRQHandler
    .type CAN4_Mb0To15_IRQHandler, $function
CAN4_Mb0To15_IRQHandler:
    ldr   r0,=CAN4_Mb0To15_DriverIRQHandler
    bx    r0
    .size CAN4_Mb0To15_IRQHandler, . - CAN4_Mb0To15_IRQHandler

    .align 1
    .thumb
    .weak CAN4_Mb16To31_IRQHandler
    .type CAN4_Mb16To31_IRQHandler, $function
CAN4_Mb16To31_IRQHandler:
    ldr   r0,=CAN4_Mb16To31_DriverIRQHandler
    bx    r0
    .size CAN4_Mb16To31_IRQHandler, . - CAN4_Mb16To31_IRQHandler

    .align 1
    .thumb
    .weak CAN4_Mb32To47_IRQHandler
    .type CAN4_Mb32To47_IRQHandler, $function
CAN4_Mb32To47_IRQHandler:
    ldr   r0,=CAN4_Mb32To47_DriverIRQHandler
    bx    r0
    .size CAN4_Mb32To47_IRQHandler, . - CAN4_Mb32To47_IRQHandler

    .align 1
    .thumb
    .weak CAN4_Mb48To63_IRQHandler
    .type CAN4_Mb48To63_IRQHandler, $function
CAN4_Mb48To63_IRQHandler:
    ldr   r0,=CAN4_Mb48To63_DriverIRQHandler
    bx    r0
    .size CAN4_Mb48To63_IRQHandler, . - CAN4_Mb48To63_IRQHandler

    .align 1
    .thumb
    .weak CAN5_BusOff_IRQHandler
    .type CAN5_BusOff_IRQHandler, $function
CAN5_BusOff_IRQHandler:
    ldr   r0,=CAN5_BusOff_DriverIRQHandler
    bx    r0
    .size CAN5_BusOff_IRQHandler, . - CAN5_BusOff_IRQHandler

    .align 1
    .thumb
    .weak CAN5_TxWarn_IRQHandler
    .type CAN5_TxWarn_IRQHandler, $function
CAN5_TxWarn_IRQHandler:
    ldr   r0,=CAN5_TxWarn_DriverIRQHandler
    bx    r0
    .size CAN5_TxWarn_IRQHandler, . - CAN5_TxWarn_IRQHandler

    .align 1
    .thumb
    .weak CAN5_RxWarn_IRQHandler
    .type CAN5_RxWarn_IRQHandler, $function
CAN5_RxWarn_IRQHandler:
    ldr   r0,=CAN5_RxWarn_DriverIRQHandler
    bx    r0
    .size CAN5_RxWarn_IRQHandler, . - CAN5_RxWarn_IRQHandler

    .align 1
    .thumb
    .weak CAN5_Err_IRQHandler
    .type CAN5_Err_IRQHandler, $function
CAN5_Err_IRQHandler:
    ldr   r0,=CAN5_Err_DriverIRQHandler
    bx    r0
    .size CAN5_Err_IRQHandler, . - CAN5_Err_IRQHandler

    .align 1
    .thumb
    .weak CAN5_ErrFd_IRQHandler
    .type CAN5_ErrFd_IRQHandler, $function
CAN5_ErrFd_IRQHandler:
    ldr   r0,=CAN5_ErrFd_DriverIRQHandler
    bx    r0
    .size CAN5_ErrFd_IRQHandler, . - CAN5_ErrFd_IRQHandler

    .align 1
    .thumb
    .weak CAN5_PnWake_IRQHandler
    .type CAN5_PnWake_IRQHandler, $function
CAN5_PnWake_IRQHandler:
    ldr   r0,=CAN5_PnWake_DriverIRQHandler
    bx    r0
    .size CAN5_PnWake_IRQHandler, . - CAN5_PnWake_IRQHandler

    .align 1
    .thumb
    .weak CAN5_SelfWakeup_IRQHandler
    .type CAN5_SelfWakeup_IRQHandler, $function
CAN5_SelfWakeup_IRQHandler:
    ldr   r0,=CAN5_SelfWakeup_DriverIRQHandler
    bx    r0
    .size CAN5_SelfWakeup_IRQHandler, . - CAN5_SelfWakeup_IRQHandler

    .align 1
    .thumb
    .weak CAN5_Ecc_IRQHandler
    .type CAN5_Ecc_IRQHandler, $function
CAN5_Ecc_IRQHandler:
    ldr   r0,=CAN5_Ecc_DriverIRQHandler
    bx    r0
    .size CAN5_Ecc_IRQHandler, . - CAN5_Ecc_IRQHandler

    .align 1
    .thumb
    .weak CAN5_Mb0To15_IRQHandler
    .type CAN5_Mb0To15_IRQHandler, $function
CAN5_Mb0To15_IRQHandler:
    ldr   r0,=CAN5_Mb0To15_DriverIRQHandler
    bx    r0
    .size CAN5_Mb0To15_IRQHandler, . - CAN5_Mb0To15_IRQHandler

    .align 1
    .thumb
    .weak CAN5_Mb16To31_IRQHandler
    .type CAN5_Mb16To31_IRQHandler, $function
CAN5_Mb16To31_IRQHandler:
    ldr   r0,=CAN5_Mb16To31_DriverIRQHandler
    bx    r0
    .size CAN5_Mb16To31_IRQHandler, . - CAN5_Mb16To31_IRQHandler

    .align 1
    .thumb
    .weak CAN5_Mb32To47_IRQHandler
    .type CAN5_Mb32To47_IRQHandler, $function
CAN5_Mb32To47_IRQHandler:
    ldr   r0,=CAN5_Mb32To47_DriverIRQHandler
    bx    r0
    .size CAN5_Mb32To47_IRQHandler, . - CAN5_Mb32To47_IRQHandler

    .align 1
    .thumb
    .weak CAN5_Mb48To63_IRQHandler
    .type CAN5_Mb48To63_IRQHandler, $function
CAN5_Mb48To63_IRQHandler:
    ldr   r0,=CAN5_Mb48To63_DriverIRQHandler
    bx    r0
    .size CAN5_Mb48To63_IRQHandler, . - CAN5_Mb48To63_IRQHandler

    .align 1
    .thumb
    .weak CAN6_BusOff_IRQHandler
    .type CAN6_BusOff_IRQHandler, $function
CAN6_BusOff_IRQHandler:
    ldr   r0,=CAN6_BusOff_DriverIRQHandler
    bx    r0
    .size CAN6_BusOff_IRQHandler, . - CAN6_BusOff_IRQHandler

    .align 1
    .thumb
    .weak CAN6_TxWarn_IRQHandler
    .type CAN6_TxWarn_IRQHandler, $function
CAN6_TxWarn_IRQHandler:
    ldr   r0,=CAN6_TxWarn_DriverIRQHandler
    bx    r0
    .size CAN6_TxWarn_IRQHandler, . - CAN6_TxWarn_IRQHandler

    .align 1
    .thumb
    .weak CAN6_RxWarn_IRQHandler
    .type CAN6_RxWarn_IRQHandler, $function
CAN6_RxWarn_IRQHandler:
    ldr   r0,=CAN6_RxWarn_DriverIRQHandler
    bx    r0
    .size CAN6_RxWarn_IRQHandler, . - CAN6_RxWarn_IRQHandler

    .align 1
    .thumb
    .weak CAN6_Err_IRQHandler
    .type CAN6_Err_IRQHandler, $function
CAN6_Err_IRQHandler:
    ldr   r0,=CAN6_Err_DriverIRQHandler
    bx    r0
    .size CAN6_Err_IRQHandler, . - CAN6_Err_IRQHandler

    .align 1
    .thumb
    .weak CAN6_ErrFd_IRQHandler
    .type CAN6_ErrFd_IRQHandler, $function
CAN6_ErrFd_IRQHandler:
    ldr   r0,=CAN6_ErrFd_DriverIRQHandler
    bx    r0
    .size CAN6_ErrFd_IRQHandler, . - CAN6_ErrFd_IRQHandler

    .align 1
    .thumb
    .weak CAN6_PnWake_IRQHandler
    .type CAN6_PnWake_IRQHandler, $function
CAN6_PnWake_IRQHandler:
    ldr   r0,=CAN6_PnWake_DriverIRQHandler
    bx    r0
    .size CAN6_PnWake_IRQHandler, . - CAN6_PnWake_IRQHandler

    .align 1
    .thumb
    .weak CAN6_SelfWakeup_IRQHandler
    .type CAN6_SelfWakeup_IRQHandler, $function
CAN6_SelfWakeup_IRQHandler:
    ldr   r0,=CAN6_SelfWakeup_DriverIRQHandler
    bx    r0
    .size CAN6_SelfWakeup_IRQHandler, . - CAN6_SelfWakeup_IRQHandler

    .align 1
    .thumb
    .weak CAN6_Ecc_IRQHandler
    .type CAN6_Ecc_IRQHandler, $function
CAN6_Ecc_IRQHandler:
    ldr   r0,=CAN6_Ecc_DriverIRQHandler
    bx    r0
    .size CAN6_Ecc_IRQHandler, . - CAN6_Ecc_IRQHandler

    .align 1
    .thumb
    .weak CAN6_Mb0To31_IRQHandler
    .type CAN6_Mb0To31_IRQHandler, $function
CAN6_Mb0To31_IRQHandler:
    ldr   r0,=CAN6_Mb0To31_DriverIRQHandler
    bx    r0
    .size CAN6_Mb0To31_IRQHandler, . - CAN6_Mb0To31_IRQHandler

    .align 1
    .thumb
    .weak CAN6_Mb32To63_IRQHandler
    .type CAN6_Mb32To63_IRQHandler, $function
CAN6_Mb32To63_IRQHandler:
    ldr   r0,=CAN6_Mb32To63_DriverIRQHandler
    bx    r0
    .size CAN6_Mb32To63_IRQHandler, . - CAN6_Mb32To63_IRQHandler

    .align 1
    .thumb
    .weak CAN6_Mb64To95_IRQHandler
    .type CAN6_Mb64To95_IRQHandler, $function
CAN6_Mb64To95_IRQHandler:
    ldr   r0,=CAN6_Mb64To95_DriverIRQHandler
    bx    r0
    .size CAN6_Mb64To95_IRQHandler, . - CAN6_Mb64To95_IRQHandler

    .align 1
    .thumb
    .weak CAN6_Mb96To127_IRQHandler
    .type CAN6_Mb96To127_IRQHandler, $function
CAN6_Mb96To127_IRQHandler:
    ldr   r0,=CAN6_Mb96To127_DriverIRQHandler
    bx    r0
    .size CAN6_Mb96To127_IRQHandler, . - CAN6_Mb96To127_IRQHandler

    .align 1
    .thumb
    .weak CAN7_BusOff_IRQHandler
    .type CAN7_BusOff_IRQHandler, $function
CAN7_BusOff_IRQHandler:
    ldr   r0,=CAN7_BusOff_DriverIRQHandler
    bx    r0
    .size CAN7_BusOff_IRQHandler, . - CAN7_BusOff_IRQHandler

    .align 1
    .thumb
    .weak CAN7_TxWarn_IRQHandler
    .type CAN7_TxWarn_IRQHandler, $function
CAN7_TxWarn_IRQHandler:
    ldr   r0,=CAN7_TxWarn_DriverIRQHandler
    bx    r0
    .size CAN7_TxWarn_IRQHandler, . - CAN7_TxWarn_IRQHandler

    .align 1
    .thumb
    .weak CAN7_RxWarn_IRQHandler
    .type CAN7_RxWarn_IRQHandler, $function
CAN7_RxWarn_IRQHandler:
    ldr   r0,=CAN7_RxWarn_DriverIRQHandler
    bx    r0
    .size CAN7_RxWarn_IRQHandler, . - CAN7_RxWarn_IRQHandler

    .align 1
    .thumb
    .weak CAN7_Err_IRQHandler
    .type CAN7_Err_IRQHandler, $function
CAN7_Err_IRQHandler:
    ldr   r0,=CAN7_Err_DriverIRQHandler
    bx    r0
    .size CAN7_Err_IRQHandler, . - CAN7_Err_IRQHandler

    .align 1
    .thumb
    .weak CAN7_ErrFd_IRQHandler
    .type CAN7_ErrFd_IRQHandler, $function
CAN7_ErrFd_IRQHandler:
    ldr   r0,=CAN7_ErrFd_DriverIRQHandler
    bx    r0
    .size CAN7_ErrFd_IRQHandler, . - CAN7_ErrFd_IRQHandler

    .align 1
    .thumb
    .weak CAN7_PnWake_IRQHandler
    .type CAN7_PnWake_IRQHandler, $function
CAN7_PnWake_IRQHandler:
    ldr   r0,=CAN7_PnWake_DriverIRQHandler
    bx    r0
    .size CAN7_PnWake_IRQHandler, . - CAN7_PnWake_IRQHandler

    .align 1
    .thumb
    .weak CAN7_SelfWakeup_IRQHandler
    .type CAN7_SelfWakeup_IRQHandler, $function
CAN7_SelfWakeup_IRQHandler:
    ldr   r0,=CAN7_SelfWakeup_DriverIRQHandler
    bx    r0
    .size CAN7_SelfWakeup_IRQHandler, . - CAN7_SelfWakeup_IRQHandler

    .align 1
    .thumb
    .weak CAN7_Ecc_IRQHandler
    .type CAN7_Ecc_IRQHandler, $function
CAN7_Ecc_IRQHandler:
    ldr   r0,=CAN7_Ecc_DriverIRQHandler
    bx    r0
    .size CAN7_Ecc_IRQHandler, . - CAN7_Ecc_IRQHandler

    .align 1
    .thumb
    .weak CAN7_Mb0To31_IRQHandler
    .type CAN7_Mb0To31_IRQHandler, $function
CAN7_Mb0To31_IRQHandler:
    ldr   r0,=CAN7_Mb0To31_DriverIRQHandler
    bx    r0
    .size CAN7_Mb0To31_IRQHandler, . - CAN7_Mb0To31_IRQHandler

    .align 1
    .thumb
    .weak CAN7_Mb32To63_IRQHandler
    .type CAN7_Mb32To63_IRQHandler, $function
CAN7_Mb32To63_IRQHandler:
    ldr   r0,=CAN7_Mb32To63_DriverIRQHandler
    bx    r0
    .size CAN7_Mb32To63_IRQHandler, . - CAN7_Mb32To63_IRQHandler

    .align 1
    .thumb
    .weak CAN7_Mb64To95_IRQHandler
    .type CAN7_Mb64To95_IRQHandler, $function
CAN7_Mb64To95_IRQHandler:
    ldr   r0,=CAN7_Mb64To95_DriverIRQHandler
    bx    r0
    .size CAN7_Mb64To95_IRQHandler, . - CAN7_Mb64To95_IRQHandler

    .align 1
    .thumb
    .weak CAN7_Mb96To127_IRQHandler
    .type CAN7_Mb96To127_IRQHandler, $function
CAN7_Mb96To127_IRQHandler:
    ldr   r0,=CAN7_Mb96To127_DriverIRQHandler
    bx    r0
    .size CAN7_Mb96To127_IRQHandler, . - CAN7_Mb96To127_IRQHandler

    .align 1
    .thumb
    .weak TIM0_Ch_IRQHandler
    .type TIM0_Ch_IRQHandler, $function
TIM0_Ch_IRQHandler:
    ldr   r0,=TIM0_Ch_DriverIRQHandler
    bx    r0
    .size TIM0_Ch_IRQHandler, . - TIM0_Ch_IRQHandler

    .align 1
    .thumb
    .weak TIM0_Fault_IRQHandler
    .type TIM0_Fault_IRQHandler, $function
TIM0_Fault_IRQHandler:
    ldr   r0,=TIM0_Fault_DriverIRQHandler
    bx    r0
    .size TIM0_Fault_IRQHandler, . - TIM0_Fault_IRQHandler

    .align 1
    .thumb
    .weak TIM0_Overflow_IRQHandler
    .type TIM0_Overflow_IRQHandler, $function
TIM0_Overflow_IRQHandler:
    ldr   r0,=TIM0_Overflow_DriverIRQHandler
    bx    r0
    .size TIM0_Overflow_IRQHandler, . - TIM0_Overflow_IRQHandler

    .align 1
    .thumb
    .weak TIM0_Rlfl_IRQHandler
    .type TIM0_Rlfl_IRQHandler, $function
TIM0_Rlfl_IRQHandler:
    ldr   r0,=TIM0_Rlfl_DriverIRQHandler
    bx    r0
    .size TIM0_Rlfl_IRQHandler, . - TIM0_Rlfl_IRQHandler

    .align 1
    .thumb
    .weak TIM1_Ch_IRQHandler
    .type TIM1_Ch_IRQHandler, $function
TIM1_Ch_IRQHandler:
    ldr   r0,=TIM1_Ch_DriverIRQHandler
    bx    r0
    .size TIM1_Ch_IRQHandler, . - TIM1_Ch_IRQHandler

    .align 1
    .thumb
    .weak TIM1_Fault_IRQHandler
    .type TIM1_Fault_IRQHandler, $function
TIM1_Fault_IRQHandler:
    ldr   r0,=TIM1_Fault_DriverIRQHandler
    bx    r0
    .size TIM1_Fault_IRQHandler, . - TIM1_Fault_IRQHandler

    .align 1
    .thumb
    .weak TIM1_Overflow_IRQHandler
    .type TIM1_Overflow_IRQHandler, $function
TIM1_Overflow_IRQHandler:
    ldr   r0,=TIM1_Overflow_DriverIRQHandler
    bx    r0
    .size TIM1_Overflow_IRQHandler, . - TIM1_Overflow_IRQHandler

    .align 1
    .thumb
    .weak TIM1_Rlfl_IRQHandler
    .type TIM1_Rlfl_IRQHandler, $function
TIM1_Rlfl_IRQHandler:
    ldr   r0,=TIM1_Rlfl_DriverIRQHandler
    bx    r0
    .size TIM1_Rlfl_IRQHandler, . - TIM1_Rlfl_IRQHandler

    .align 1
    .thumb
    .weak TIM2_Ch_IRQHandler
    .type TIM2_Ch_IRQHandler, $function
TIM2_Ch_IRQHandler:
    ldr   r0,=TIM2_Ch_DriverIRQHandler
    bx    r0
    .size TIM2_Ch_IRQHandler, . - TIM2_Ch_IRQHandler

    .align 1
    .thumb
    .weak TIM2_Fault_IRQHandler
    .type TIM2_Fault_IRQHandler, $function
TIM2_Fault_IRQHandler:
    ldr   r0,=TIM2_Fault_DriverIRQHandler
    bx    r0
    .size TIM2_Fault_IRQHandler, . - TIM2_Fault_IRQHandler

    .align 1
    .thumb
    .weak TIM2_Overflow_IRQHandler
    .type TIM2_Overflow_IRQHandler, $function
TIM2_Overflow_IRQHandler:
    ldr   r0,=TIM2_Overflow_DriverIRQHandler
    bx    r0
    .size TIM2_Overflow_IRQHandler, . - TIM2_Overflow_IRQHandler

    .align 1
    .thumb
    .weak TIM2_Rlfl_IRQHandler
    .type TIM2_Rlfl_IRQHandler, $function
TIM2_Rlfl_IRQHandler:
    ldr   r0,=TIM2_Rlfl_DriverIRQHandler
    bx    r0
    .size TIM2_Rlfl_IRQHandler, . - TIM2_Rlfl_IRQHandler

    .align 1
    .thumb
    .weak TIM3_Ch_IRQHandler
    .type TIM3_Ch_IRQHandler, $function
TIM3_Ch_IRQHandler:
    ldr   r0,=TIM3_Ch_DriverIRQHandler
    bx    r0
    .size TIM3_Ch_IRQHandler, . - TIM3_Ch_IRQHandler

    .align 1
    .thumb
    .weak TIM3_Fault_IRQHandler
    .type TIM3_Fault_IRQHandler, $function
TIM3_Fault_IRQHandler:
    ldr   r0,=TIM3_Fault_DriverIRQHandler
    bx    r0
    .size TIM3_Fault_IRQHandler, . - TIM3_Fault_IRQHandler

    .align 1
    .thumb
    .weak TIM3_Overflow_IRQHandler
    .type TIM3_Overflow_IRQHandler, $function
TIM3_Overflow_IRQHandler:
    ldr   r0,=TIM3_Overflow_DriverIRQHandler
    bx    r0
    .size TIM3_Overflow_IRQHandler, . - TIM3_Overflow_IRQHandler

    .align 1
    .thumb
    .weak TIM3_Rlfl_IRQHandler
    .type TIM3_Rlfl_IRQHandler, $function
TIM3_Rlfl_IRQHandler:
    ldr   r0,=TIM3_Rlfl_DriverIRQHandler
    bx    r0
    .size TIM3_Rlfl_IRQHandler, . - TIM3_Rlfl_IRQHandler

    .align 1
    .thumb
    .weak TDG0_Tco_IRQHandler
    .type TDG0_Tco_IRQHandler, $function
TDG0_Tco_IRQHandler:
    ldr   r0,=TDG0_Tco_DriverIRQHandler
    bx    r0
    .size TDG0_Tco_IRQHandler, . - TDG0_Tco_IRQHandler

    .align 1
    .thumb
    .weak TDG0_Err_IRQHandler
    .type TDG0_Err_IRQHandler, $function
TDG0_Err_IRQHandler:
    ldr   r0,=TDG0_Err_DriverIRQHandler
    bx    r0
    .size TDG0_Err_IRQHandler, . - TDG0_Err_IRQHandler

    .align 1
    .thumb
    .weak TDG1_Tco_IRQHandler
    .type TDG1_Tco_IRQHandler, $function
TDG1_Tco_IRQHandler:
    ldr   r0,=TDG1_Tco_DriverIRQHandler
    bx    r0
    .size TDG1_Tco_IRQHandler, . - TDG1_Tco_IRQHandler

    .align 1
    .thumb
    .weak TDG1_Err_IRQHandler
    .type TDG1_Err_IRQHandler, $function
TDG1_Err_IRQHandler:
    ldr   r0,=TDG1_Err_DriverIRQHandler
    bx    r0
    .size TDG1_Err_IRQHandler, . - TDG1_Err_IRQHandler

    .align 1
    .thumb
    .weak I2S0_IRQHandler
    .type I2S0_IRQHandler, $function
I2S0_IRQHandler:
    ldr   r0,=I2S0_DriverIRQHandler
    bx    r0
    .size I2S0_IRQHandler, . - I2S0_IRQHandler

    .align 1
    .thumb
    .weak PORTA_IRQHandler
    .type PORTA_IRQHandler, $function
PORTA_IRQHandler:
    ldr   r0,=PORTA_DriverIRQHandler
    bx    r0
    .size PORTA_IRQHandler, . - PORTA_IRQHandler

    .align 1
    .thumb
    .weak PORTB_IRQHandler
    .type PORTB_IRQHandler, $function
PORTB_IRQHandler:
    ldr   r0,=PORTB_DriverIRQHandler
    bx    r0
    .size PORTB_IRQHandler, . - PORTB_IRQHandler

    .align 1
    .thumb
    .weak PORTC_IRQHandler
    .type PORTC_IRQHandler, $function
PORTC_IRQHandler:
    ldr   r0,=PORTC_DriverIRQHandler
    bx    r0
    .size PORTC_IRQHandler, . - PORTC_IRQHandler

    .align 1
    .thumb
    .weak PORTD_IRQHandler
    .type PORTD_IRQHandler, $function
PORTD_IRQHandler:
    ldr   r0,=PORTD_DriverIRQHandler
    bx    r0
    .size PORTD_IRQHandler, . - PORTD_IRQHandler

    .align 1
    .thumb
    .weak PORTE_IRQHandler
    .type PORTE_IRQHandler, $function
PORTE_IRQHandler:
    ldr   r0,=PORTE_DriverIRQHandler
    bx    r0
    .size PORTE_IRQHandler, . - PORTE_IRQHandler

    .align 1
    .thumb
    .weak STIM_IRQHandler
    .type STIM_IRQHandler, $function
STIM_IRQHandler:
    ldr   r0,=STIM_DriverIRQHandler
    bx    r0
    .size STIM_IRQHandler, . - STIM_IRQHandler

    .align 1
    .thumb
    .weak RTC_Alarm_IRQHandler
    .type RTC_Alarm_IRQHandler, $function
RTC_Alarm_IRQHandler:
    ldr   r0,=RTC_Alarm_DriverIRQHandler
    bx    r0
    .size RTC_Alarm_IRQHandler, . - RTC_Alarm_IRQHandler

    .align 1
    .thumb
    .weak RTC_Second_IRQHandler
    .type RTC_Second_IRQHandler, $function
RTC_Second_IRQHandler:
    ldr   r0,=RTC_Second_DriverIRQHandler
    bx    r0
    .size RTC_Second_IRQHandler, . - RTC_Second_IRQHandler

    .align 1
    .thumb
    .weak AES_IRQHandler
    .type AES_IRQHandler, $function
AES_IRQHandler:
    ldr   r0,=AES_DriverIRQHandler
    bx    r0
    .size AES_IRQHandler, . - AES_IRQHandler

    .align 1
    .thumb
    .weak TRNG_IRQHandler
    .type TRNG_IRQHandler, $function
TRNG_IRQHandler:
    ldr   r0,=TRNG_DriverIRQHandler
    bx    r0
    .size TRNG_IRQHandler, . - TRNG_IRQHandler

    .align 1
    .thumb
    .weak CMU0_IRQHandler
    .type CMU0_IRQHandler, $function
CMU0_IRQHandler:
    ldr   r0,=CMU0_DriverIRQHandler
    bx    r0
    .size CMU0_IRQHandler, . - CMU0_IRQHandler

    .align 1
    .thumb
    .weak CMU1_IRQHandler
    .type CMU1_IRQHandler, $function
CMU1_IRQHandler:
    ldr   r0,=CMU1_DriverIRQHandler
    bx    r0
    .size CMU1_IRQHandler, . - CMU1_IRQHandler

    .align 1
    .thumb
    .weak CMU2_IRQHandler
    .type CMU2_IRQHandler, $function
CMU2_IRQHandler:
    ldr   r0,=CMU2_DriverIRQHandler
    bx    r0
    .size CMU2_IRQHandler, . - CMU2_IRQHandler

    .align 1
    .thumb
    .weak SERU_ParityErr_IRQHandler
    .type SERU_ParityErr_IRQHandler, $function
SERU_ParityErr_IRQHandler:
    ldr   r0,=SERU_ParityErr_DriverIRQHandler
    bx    r0
    .size SERU_ParityErr_IRQHandler, . - SERU_ParityErr_IRQHandler

    .align 1
    .thumb
    .weak SERU_ChErr_IRQHandler
    .type SERU_ChErr_IRQHandler, $function
SERU_ChErr_IRQHandler:
    ldr   r0,=SERU_ChErr_DriverIRQHandler
    bx    r0
    .size SERU_ChErr_IRQHandler, . - SERU_ChErr_IRQHandler

    .align 1
    .thumb
    .weak SCC_IRQHandler
    .type SCC_IRQHandler, $function
SCC_IRQHandler:
    ldr   r0,=SCC_DriverIRQHandler
    bx    r0
    .size SCC_IRQHandler, . - SCC_IRQHandler

    .align 1
    .thumb
    .weak MCPWM0_Ch_IRQHandler
    .type MCPWM0_Ch_IRQHandler, $function
MCPWM0_Ch_IRQHandler:
    ldr   r0,=MCPWM0_Ch_DriverIRQHandler
    bx    r0
    .size MCPWM0_Ch_IRQHandler, . - MCPWM0_Ch_IRQHandler

    .align 1
    .thumb
    .weak MCPWM0_Fault_IRQHandler
    .type MCPWM0_Fault_IRQHandler, $function
MCPWM0_Fault_IRQHandler:
    ldr   r0,=MCPWM0_Fault_DriverIRQHandler
    bx    r0
    .size MCPWM0_Fault_IRQHandler, . - MCPWM0_Fault_IRQHandler

    .align 1
    .thumb
    .weak MCPWM0_Overflow_IRQHandler
    .type MCPWM0_Overflow_IRQHandler, $function
MCPWM0_Overflow_IRQHandler:
    ldr   r0,=MCPWM0_Overflow_DriverIRQHandler
    bx    r0
    .size MCPWM0_Overflow_IRQHandler, . - MCPWM0_Overflow_IRQHandler

    .align 1
    .thumb
    .weak MCPWM0_Rlfl_IRQHandler
    .type MCPWM0_Rlfl_IRQHandler, $function
MCPWM0_Rlfl_IRQHandler:
    ldr   r0,=MCPWM0_Rlfl_DriverIRQHandler
    bx    r0
    .size MCPWM0_Rlfl_IRQHandler, . - MCPWM0_Rlfl_IRQHandler

    .align 1
    .thumb
    .weak MCPWM1_Ch_IRQHandler
    .type MCPWM1_Ch_IRQHandler, $function
MCPWM1_Ch_IRQHandler:
    ldr   r0,=MCPWM1_Ch_DriverIRQHandler
    bx    r0
    .size MCPWM1_Ch_IRQHandler, . - MCPWM1_Ch_IRQHandler

    .align 1
    .thumb
    .weak MCPWM1_Fault_IRQHandler
    .type MCPWM1_Fault_IRQHandler, $function
MCPWM1_Fault_IRQHandler:
    ldr   r0,=MCPWM1_Fault_DriverIRQHandler
    bx    r0
    .size MCPWM1_Fault_IRQHandler, . - MCPWM1_Fault_IRQHandler

    .align 1
    .thumb
    .weak MCPWM1_Overflow_IRQHandler
    .type MCPWM1_Overflow_IRQHandler, $function
MCPWM1_Overflow_IRQHandler:
    ldr   r0,=MCPWM1_Overflow_DriverIRQHandler
    bx    r0
    .size MCPWM1_Overflow_IRQHandler, . - MCPWM1_Overflow_IRQHandler

    .align 1
    .thumb
    .weak MCPWM1_Rlfl_IRQHandler
    .type MCPWM1_Rlfl_IRQHandler, $function
MCPWM1_Rlfl_IRQHandler:
    ldr   r0,=MCPWM1_Rlfl_DriverIRQHandler
    bx    r0
    .size MCPWM1_Rlfl_IRQHandler, . - MCPWM1_Rlfl_IRQHandler

    .align 1
    .thumb
    .weak ADC0_IRQHandler
    .type ADC0_IRQHandler, $function
ADC0_IRQHandler:
    ldr   r0,=ADC0_DriverIRQHandler
    bx    r0
    .size ADC0_IRQHandler, . - ADC0_IRQHandler

    .align 1
    .thumb
    .weak ADC1_IRQHandler
    .type ADC1_IRQHandler, $function
ADC1_IRQHandler:
    ldr   r0,=ADC1_DriverIRQHandler
    bx    r0
    .size ADC1_IRQHandler, . - ADC1_IRQHandler

    .align 1
    .thumb
    .weak CMP_IRQHandler
    .type CMP_IRQHandler, $function
CMP_IRQHandler:
    ldr   r0,=CMP_DriverIRQHandler
    bx    r0
    .size CMP_IRQHandler, . - CMP_IRQHandler

    .align 1
    .thumb
    .weak SCM_FpuErr_IRQHandler
    .type SCM_FpuErr_IRQHandler, $function
SCM_FpuErr_IRQHandler:
    ldr   r0,=SCM_FpuErr_DriverIRQHandler
    bx    r0
    .size SCM_FpuErr_IRQHandler, . - SCM_FpuErr_IRQHandler

    .align 1
    .thumb
    .weak SCM_CacheErr_IRQHandler
    .type SCM_CacheErr_IRQHandler, $function
SCM_CacheErr_IRQHandler:
    ldr   r0,=SCM_CacheErr_DriverIRQHandler
    bx    r0
    .size SCM_CacheErr_IRQHandler, . - SCM_CacheErr_IRQHandler


/* Define default handlers */
    .macro def_irq_handler  handler_name
    .weak  handler_name
    .set   handler_name, JumpToSelf
    .endm

/* Zhixin specific interrupt */
    def_irq_handler    DMA_Ch0_DriverIRQHandler
    def_irq_handler    DMA_Ch1_DriverIRQHandler
    def_irq_handler    DMA_Ch2_DriverIRQHandler
    def_irq_handler    DMA_Ch3_DriverIRQHandler
    def_irq_handler    DMA_Ch4_DriverIRQHandler
    def_irq_handler    DMA_Ch5_DriverIRQHandler
    def_irq_handler    DMA_Ch6_DriverIRQHandler
    def_irq_handler    DMA_Ch7_DriverIRQHandler
    def_irq_handler    DMA_Ch8_DriverIRQHandler
    def_irq_handler    DMA_Ch9_DriverIRQHandler
    def_irq_handler    DMA_Ch10_DriverIRQHandler
    def_irq_handler    DMA_Ch11_DriverIRQHandler
    def_irq_handler    DMA_Ch12_DriverIRQHandler
    def_irq_handler    DMA_Ch13_DriverIRQHandler
    def_irq_handler    DMA_Ch14_DriverIRQHandler
    def_irq_handler    DMA_Ch15_DriverIRQHandler
    def_irq_handler    DMA_Err_DriverIRQHandler
    def_irq_handler    FLASH_CmdComplete_DriverIRQHandler
    def_irq_handler    FLASH_Ecc_DriverIRQHandler
    def_irq_handler    PMU_DriverIRQHandler
    def_irq_handler    WDOG_DriverIRQHandler
    def_irq_handler    EWDT_DriverIRQHandler
    def_irq_handler    SRMC_DriverIRQHandler
    def_irq_handler    I2C0_DriverIRQHandler
    def_irq_handler    I2C1_DriverIRQHandler
    def_irq_handler    SPI0_Txe_DriverIRQHandler
    def_irq_handler    SPI0_Txo_DriverIRQHandler
    def_irq_handler    SPI0_Rxf_DriverIRQHandler
    def_irq_handler    SPI0_Rxo_DriverIRQHandler
    def_irq_handler    SPI0_Rxu_DriverIRQHandler
    def_irq_handler    Reserved30_IRQHandler
    def_irq_handler    SPI1_Txe_DriverIRQHandler
    def_irq_handler    SPI1_Txo_DriverIRQHandler
    def_irq_handler    SPI1_Rxf_DriverIRQHandler
    def_irq_handler    SPI1_Rxo_DriverIRQHandler
    def_irq_handler    SPI1_Rxu_DriverIRQHandler
    def_irq_handler    Reserved36_IRQHandler
    def_irq_handler    SPI2_Txe_DriverIRQHandler
    def_irq_handler    SPI2_Txo_DriverIRQHandler
    def_irq_handler    SPI2_Rxf_DriverIRQHandler
    def_irq_handler    SPI2_Rxo_DriverIRQHandler
    def_irq_handler    SPI2_Rxu_DriverIRQHandler
    def_irq_handler    Reserved42_IRQHandler
    def_irq_handler    SPI3_Txe_DriverIRQHandler
    def_irq_handler    SPI3_Txo_DriverIRQHandler
    def_irq_handler    SPI3_Rxf_DriverIRQHandler
    def_irq_handler    SPI3_Rxo_DriverIRQHandler
    def_irq_handler    SPI3_Rxu_DriverIRQHandler
    def_irq_handler    Reserved48_IRQHandler
    def_irq_handler    UART0_DriverIRQHandler
    def_irq_handler    UART1_DriverIRQHandler
    def_irq_handler    UART2_DriverIRQHandler
    def_irq_handler    UART3_DriverIRQHandler
    def_irq_handler    UART4_DriverIRQHandler
    def_irq_handler    UART5_DriverIRQHandler
    def_irq_handler    CAN0_BusOff_DriverIRQHandler
    def_irq_handler    CAN0_TxWarn_DriverIRQHandler
    def_irq_handler    CAN0_RxWarn_DriverIRQHandler
    def_irq_handler    CAN0_Err_DriverIRQHandler
    def_irq_handler    CAN0_ErrFd_DriverIRQHandler
    def_irq_handler    CAN0_PnWake_DriverIRQHandler
    def_irq_handler    CAN0_SelfWakeup_DriverIRQHandler
    def_irq_handler    CAN0_Ecc_DriverIRQHandler
    def_irq_handler    CAN0_Mb0To15_DriverIRQHandler
    def_irq_handler    CAN0_Mb16To31_DriverIRQHandler
    def_irq_handler    CAN0_Mb32To47_DriverIRQHandler
    def_irq_handler    CAN0_Mb48To63_DriverIRQHandler
    def_irq_handler    CAN1_BusOff_DriverIRQHandler
    def_irq_handler    CAN1_TxWarn_DriverIRQHandler
    def_irq_handler    CAN1_RxWarn_DriverIRQHandler
    def_irq_handler    CAN1_Err_DriverIRQHandler
    def_irq_handler    CAN1_ErrFd_DriverIRQHandler
    def_irq_handler    CAN1_PnWake_DriverIRQHandler
    def_irq_handler    CAN1_SelfWakeup_DriverIRQHandler
    def_irq_handler    CAN1_Ecc_DriverIRQHandler
    def_irq_handler    CAN1_Mb0To15_DriverIRQHandler
    def_irq_handler    CAN1_Mb16To31_DriverIRQHandler
    def_irq_handler    CAN1_Mb32To47_DriverIRQHandler
    def_irq_handler    CAN1_Mb48To63_DriverIRQHandler
    def_irq_handler    CAN2_BusOff_DriverIRQHandler
    def_irq_handler    CAN2_TxWarn_DriverIRQHandler
    def_irq_handler    CAN2_RxWarn_DriverIRQHandler
    def_irq_handler    CAN2_Err_DriverIRQHandler
    def_irq_handler    CAN2_ErrFd_DriverIRQHandler
    def_irq_handler    CAN2_PnWake_DriverIRQHandler
    def_irq_handler    CAN2_SelfWakeup_DriverIRQHandler
    def_irq_handler    CAN2_Ecc_DriverIRQHandler
    def_irq_handler    CAN2_Mb0To15_DriverIRQHandler
    def_irq_handler    CAN2_Mb16To31_DriverIRQHandler
    def_irq_handler    CAN2_Mb32To47_DriverIRQHandler
    def_irq_handler    CAN2_Mb48To63_DriverIRQHandler
    def_irq_handler    CAN3_BusOff_DriverIRQHandler
    def_irq_handler    CAN3_TxWarn_DriverIRQHandler
    def_irq_handler    CAN3_RxWarn_DriverIRQHandler
    def_irq_handler    CAN3_Err_DriverIRQHandler
    def_irq_handler    CAN3_ErrFd_DriverIRQHandler
    def_irq_handler    CAN3_PnWake_DriverIRQHandler
    def_irq_handler    CAN3_SelfWakeup_DriverIRQHandler
    def_irq_handler    CAN3_Ecc_DriverIRQHandler
    def_irq_handler    CAN3_Mb0To15_DriverIRQHandler
    def_irq_handler    CAN3_Mb16To31_DriverIRQHandler
    def_irq_handler    CAN3_Mb32To47_DriverIRQHandler
    def_irq_handler    CAN3_Mb48To63_DriverIRQHandler
    def_irq_handler    CAN4_BusOff_DriverIRQHandler
    def_irq_handler    CAN4_TxWarn_DriverIRQHandler
    def_irq_handler    CAN4_RxWarn_DriverIRQHandler
    def_irq_handler    CAN4_Err_DriverIRQHandler
    def_irq_handler    CAN4_ErrFd_DriverIRQHandler
    def_irq_handler    CAN4_PnWake_DriverIRQHandler
    def_irq_handler    CAN4_SelfWakeup_DriverIRQHandler
    def_irq_handler    CAN4_Ecc_DriverIRQHandler
    def_irq_handler    CAN4_Mb0To15_DriverIRQHandler
    def_irq_handler    CAN4_Mb16To31_DriverIRQHandler
    def_irq_handler    CAN4_Mb32To47_DriverIRQHandler
    def_irq_handler    CAN4_Mb48To63_DriverIRQHandler
    def_irq_handler    CAN5_BusOff_DriverIRQHandler
    def_irq_handler    CAN5_TxWarn_DriverIRQHandler
    def_irq_handler    CAN5_RxWarn_DriverIRQHandler
    def_irq_handler    CAN5_Err_DriverIRQHandler
    def_irq_handler    CAN5_ErrFd_DriverIRQHandler
    def_irq_handler    CAN5_PnWake_DriverIRQHandler
    def_irq_handler    CAN5_SelfWakeup_DriverIRQHandler
    def_irq_handler    CAN5_Ecc_DriverIRQHandler
    def_irq_handler    CAN5_Mb0To15_DriverIRQHandler
    def_irq_handler    CAN5_Mb16To31_DriverIRQHandler
    def_irq_handler    CAN5_Mb32To47_DriverIRQHandler
    def_irq_handler    CAN5_Mb48To63_DriverIRQHandler
    def_irq_handler    Reserved127_IRQHandler
    def_irq_handler    Reserved128_IRQHandler
    def_irq_handler    Reserved129_IRQHandler
    def_irq_handler    Reserved130_IRQHandler
    def_irq_handler    Reserved131_IRQHandler
    def_irq_handler    Reserved132_IRQHandler
    def_irq_handler    Reserved133_IRQHandler
    def_irq_handler    Reserved134_IRQHandler
    def_irq_handler    Reserved135_IRQHandler
    def_irq_handler    Reserved136_IRQHandler
    def_irq_handler    Reserved137_IRQHandler
    def_irq_handler    Reserved138_IRQHandler
    def_irq_handler    Reserved139_IRQHandler
    def_irq_handler    Reserved140_IRQHandler
    def_irq_handler    Reserved141_IRQHandler
    def_irq_handler    Reserved142_IRQHandler
    def_irq_handler    Reserved143_IRQHandler
    def_irq_handler    Reserved144_IRQHandler
    def_irq_handler    Reserved145_IRQHandler
    def_irq_handler    Reserved146_IRQHandler
    def_irq_handler    Reserved147_IRQHandler
    def_irq_handler    Reserved148_IRQHandler
    def_irq_handler    Reserved149_IRQHandler
    def_irq_handler    Reserved150_IRQHandler
    def_irq_handler    Reserved151_IRQHandler
    def_irq_handler    Reserved152_IRQHandler
    def_irq_handler    Reserved153_IRQHandler
    def_irq_handler    TIM0_Ch_DriverIRQHandler
    def_irq_handler    TIM0_Fault_DriverIRQHandler
    def_irq_handler    TIM0_Overflow_DriverIRQHandler
    def_irq_handler    TIM0_Rlfl_DriverIRQHandler
    def_irq_handler    TIM1_Ch_DriverIRQHandler
    def_irq_handler    TIM1_Fault_DriverIRQHandler
    def_irq_handler    TIM1_Overflow_DriverIRQHandler
    def_irq_handler    TIM1_Rlfl_DriverIRQHandler
    def_irq_handler    TIM2_Ch_DriverIRQHandler
    def_irq_handler    TIM2_Fault_DriverIRQHandler
    def_irq_handler    TIM2_Overflow_DriverIRQHandler
    def_irq_handler    TIM2_Rlfl_DriverIRQHandler
    def_irq_handler    TIM3_Ch_DriverIRQHandler
    def_irq_handler    TIM3_Fault_DriverIRQHandler
    def_irq_handler    TIM3_Overflow_DriverIRQHandler
    def_irq_handler    TIM3_Rlfl_DriverIRQHandler
    def_irq_handler    TDG0_Tco_DriverIRQHandler
    def_irq_handler    TDG0_Err_DriverIRQHandler
    def_irq_handler    TDG1_Tco_DriverIRQHandler
    def_irq_handler    TDG1_Err_DriverIRQHandler
    def_irq_handler    I2S0_DriverIRQHandler
    def_irq_handler    Reserved175_IRQHandler
    def_irq_handler    PORTA_DriverIRQHandler
    def_irq_handler    PORTB_DriverIRQHandler
    def_irq_handler    PORTC_DriverIRQHandler
    def_irq_handler    PORTD_DriverIRQHandler
    def_irq_handler    PORTE_DriverIRQHandler
    def_irq_handler    STIM_DriverIRQHandler
    def_irq_handler    RTC_Alarm_DriverIRQHandler
    def_irq_handler    RTC_Second_DriverIRQHandler
    def_irq_handler    AES_DriverIRQHandler
    def_irq_handler    TRNG_DriverIRQHandler
    def_irq_handler    CMU0_DriverIRQHandler
    def_irq_handler    CMU1_DriverIRQHandler
    def_irq_handler    CMU2_DriverIRQHandler
    def_irq_handler    SERU_ParityErr_DriverIRQHandler
    def_irq_handler    SERU_ChErr_DriverIRQHandler
    def_irq_handler    SCC_DriverIRQHandler
    def_irq_handler    MCPWM0_Ch_DriverIRQHandler
    def_irq_handler    MCPWM0_Fault_DriverIRQHandler
    def_irq_handler    MCPWM0_Overflow_DriverIRQHandler
    def_irq_handler    MCPWM0_Rlfl_DriverIRQHandler
    def_irq_handler    MCPWM1_Ch_DriverIRQHandler
    def_irq_handler    MCPWM1_Fault_DriverIRQHandler
    def_irq_handler    MCPWM1_Overflow_DriverIRQHandler
    def_irq_handler    MCPWM1_Rlfl_DriverIRQHandler
    def_irq_handler    ADC0_DriverIRQHandler
    def_irq_handler    ADC1_DriverIRQHandler
    def_irq_handler    CMP_DriverIRQHandler
    def_irq_handler    SCM_FpuErr_DriverIRQHandler
    def_irq_handler    SCM_CacheErr_DriverIRQHandler

    .end
