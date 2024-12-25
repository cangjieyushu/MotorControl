; ---------------------------------------------------------------------------
; @file      Z20K146M_startup.s
; @brief     Z20K146M startup and Vector Table Source File for IAR.
; @version   V1.1.0
; @date      December-2022
; @author    Zhixin Semiconductor
;
; @note
; Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
;
; ---------------------------------------------------------------------------


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
        DCD   MemManageFault_Handler  ; MemManage Fault Handler
        DCD   BusFault_Handler        ; Bus Fault Handler
        DCD   UsageFault_Handler      ; Usage Fault Handler
        DCD   0
        DCD   0
        DCD   0
        DCD   0
        DCD   SVC_Handler              ; SV Call handler
        DCD   DebugMonitor_Handler     ; debug monitor Handler
        DCD   0
        DCD   PendSV_Handler           ; Pend SV handler
        DCD   SysTick_Handler          ; System Tick handler


        DCD   DMA_Ch0_IRQHandler             ; irq 0 : DMA channel 0 transfer complete IRQHandler
        DCD   DMA_Ch1_IRQHandler             ; irq 1 : DMA channel 1 transfer complete IRQHandler
        DCD   DMA_Ch2_IRQHandler             ; irq 2 : DMA channel 2 transfer complete IRQHandler
        DCD   DMA_Ch3_IRQHandler             ; irq 3 : DMA channel 3 transfer complete IRQHandler
        DCD   DMA_Ch4_IRQHandler             ; irq 4 : DMA channel 4 transfer complete IRQHandler
        DCD   DMA_Ch5_IRQHandler             ; irq 5 : DMA channel 5 transfer complete IRQHandler
        DCD   DMA_Ch6_IRQHandler             ; irq 6 : DMA channel 6 transfer complete IRQHandler
        DCD   DMA_Ch7_IRQHandler             ; irq 7 : DMA channel 7 transfer complete IRQHandler
        DCD   DMA_Ch8_IRQHandler             ; irq 8 : DMA channel 8 transfer complete IRQHandler
        DCD   DMA_Ch9_IRQHandler             ; irq 9 : DMA channel 9 transfer complete IRQHandler
        DCD   DMA_Ch10_IRQHandler            ; irq 10 : DMA channel 10 transfer complete IRQHandler
        DCD   DMA_Ch11_IRQHandler            ; irq 11 : DMA channel 11 transfer complete IRQHandler 
        DCD   DMA_Ch12_IRQHandler            ; irq 12 : DMA channel 12 transfer complete IRQHandler
        DCD   DMA_Ch13_IRQHandler            ; irq 13 : DMA channel 13 transfer complete IRQHandler
        DCD   DMA_Ch14_IRQHandler            ; irq 14 : DMA channel 14 transfer complete IRQHandler
        DCD   DMA_Ch15_IRQHandler            ; irq 15 : DMA channel 15 transfer complete IRQHandler
        DCD   DMA_Err_IRQHandler             ; irq 16 : DMA channel 0-15 error IRQHandler
        DCD   FLASH_CmdComplete_IRQHandler   ; irq 17 : flash command complete IRQHandler
        DCD   FLASH_Ecc_IRQHandler           ; irq 18 : Multi-bit or single-bit ECC IRQHandler
        DCD   PMU_IRQHandler                 ; irq 19 : PMU IRQHandler
        DCD   WDOG_IRQHandler                ; irq 20 : watchdog IRQHandler
        DCD   EWDT_IRQHandler                ; irq 21 : external watchdog monitor IRQHandler
        DCD   SRMC_IRQHandler                ; irq 22 : system reset and mode control IRQHandler
        DCD   I2C0_IRQHandler                ; irq 23 : I2C 0 IRQHandler
        DCD   I2C1_IRQHandler                ; irq 24 : I2C 1 IRQHandler
        DCD   SPI0_Txe_IRQHandler            ; irq 25 : SPI 0 TXE IRQHandler
        DCD   SPI0_Txo_IRQHandler            ; irq 26 : SPI 0 TXO IRQHandler
        DCD   SPI0_Rxf_IRQHandler            ; irq 27 : SPI 0 RXF IRQHandler
        DCD   SPI0_Rxo_IRQHandler            ; irq 28 : SPI 0 RXO IRQHandler
        DCD   SPI0_Rxu_IRQHandler            ; irq 29 : SPI 0 RXU IRQHandler
        DCD   Reserved30_IRQHandler          ; Reserved interrupt
        DCD   SPI1_Txe_IRQHandler            ; irq 31 : SPI 1 TXE IRQHandler
        DCD   SPI1_Txo_IRQHandler            ; irq 32 : SPI 1 TXO IRQHandler
        DCD   SPI1_Rxf_IRQHandler            ; irq 33 : SPI 1 RXF IRQHandler
        DCD   SPI1_Rxo_IRQHandler            ; irq 34 : SPI 1 RXO IRQHandler
        DCD   SPI1_Rxu_IRQHandler            ; irq 35 : SPI 1 RXU IRQHandler
        DCD   Reserved36_IRQHandler          ; Reserved interrupt
        DCD   SPI2_Txe_IRQHandler            ; irq 37 : SPI 2 TXE IRQHandler
        DCD   SPI2_Txo_IRQHandler            ; irq 38 : SPI 2 TXO IRQHandler
        DCD   SPI2_Rxf_IRQHandler            ; irq 39 : SPI 2 RXF IRQHandler
        DCD   SPI2_Rxo_IRQHandler            ; irq 40 : SPI 2 RXO IRQHandler
        DCD   SPI2_Rxu_IRQHandler            ; irq 41 : SPI 2 RXU IRQHandler
        DCD   Reserved42_IRQHandler          ; Reserved interrupt
        DCD   SPI3_Txe_IRQHandler            ; irq 43 : SPI 3 TXE IRQHandler
        DCD   SPI3_Txo_IRQHandler            ; irq 44 : SPI 3 TXO IRQHandler
        DCD   SPI3_Rxf_IRQHandler            ; irq 45 : SPI 3 RXF IRQHandler
        DCD   SPI3_Rxo_IRQHandler            ; irq 46 : SPI 3 RXO IRQHandler
        DCD   SPI3_Rxu_IRQHandler            ; irq 47 : SPI 3 RXU IRQHandler
        DCD   Reserved48_IRQHandler          ; Reserved interrupt
        DCD   UART0_IRQHandler               ; irq 49 : UART 0 IRQHandler
        DCD   UART1_IRQHandler               ; irq 50 : UART 1 IRQHandler
        DCD   UART2_IRQHandler               ; irq 51 : UART 2 IRQHandler
        DCD   UART3_IRQHandler               ; irq 52 : UART 3 IRQHandler
        DCD   UART4_IRQHandler               ; irq 53 : UART 4 IRQHandler
        DCD   UART5_IRQHandler               ; irq 54 : UART 5 IRQHandler
        DCD   CAN0_BusOff_IRQHandler         ; irq 55 : CAN 0 bus off/ bus off done IRQHandler
        DCD   CAN0_TxWarn_IRQHandler         ; irq 56 : CAN 0 TX warning IRQHandler 
        DCD   CAN0_RxWarn_IRQHandler         ; irq 57 : CAN 0 RX warning IRQHandler
        DCD   CAN0_Err_IRQHandler            ; irq 58 : CAN 0 error IRQHandler
        DCD   CAN0_ErrFd_IRQHandler          ; irq 59 : CAN 0 error FD IRQHandler
        DCD   CAN0_PnWake_IRQHandler         ; irq 60 : CAN 0 wake match IRQHandler
        DCD   CAN0_SelfWakeup_IRQHandler     ; irq 61 : CAN 0 wake to IRQHandler
        DCD   CAN0_Ecc_IRQHandler            ; irq 62 : CAN 0 ECC IRQHandler
        DCD   CAN0_Mb0To15_IRQHandler        ; irq 63 : CAN 0 message buffer 0-15 IRQHandler
        DCD   CAN0_Mb16To31_IRQHandler       ; irq 64 : CAN 0 message buffer 16-31 IRQHandler
        DCD   CAN0_Mb32To47_IRQHandler       ; irq 65 : CAN 0 message buffer 32-47 IRQHandler
        DCD   CAN0_Mb48To63_IRQHandler       ; irq 66 : CAN 0 message buffer 48-63 IRQHandler
        DCD   CAN1_BusOff_IRQHandler         ; irq 67 : CAN 1 bus off/ bus off done IRQHandler
        DCD   CAN1_TxWarn_IRQHandler         ; irq 68 : CAN 1 TX warning IRQHandler
        DCD   CAN1_RxWarn_IRQHandler         ; irq 69 : CAN 1 RX warning IRQHandler
        DCD   CAN1_Err_IRQHandler            ; irq 70 : CAN 1 error IRQHandler
        DCD   CAN1_ErrFd_IRQHandler          ; irq 71 : CAN 1 error FD IRQHandler
        DCD   CAN1_PnWake_IRQHandler         ; irq 72 : CAN 1 wake match IRQHandler
        DCD   CAN1_SelfWakeup_IRQHandler     ; irq 73 : CAN 1 wake to IRQHandler
        DCD   CAN1_Ecc_IRQHandler            ; irq 74 : CAN 1 ECC IRQHandler
        DCD   CAN1_Mb0To15_IRQHandler        ; irq 75 : CAN 1 message buffer 0-15 IRQHandler
        DCD   CAN1_Mb16To31_IRQHandler       ; irq 76 : CAN 1 message buffer 16-31 IRQHandler
        DCD   CAN1_Mb32To47_IRQHandler       ; irq 77 : CAN 1 message buffer 32-47 IRQHandler
        DCD   CAN1_Mb48To63_IRQHandler       ; irq 78 : CAN 1 message buffer 48-63 IRQHandler
        DCD   CAN2_BusOff_IRQHandler         ; irq 79 : CAN 2 bus off/ bus off done IRQHandler
        DCD   CAN2_TxWarn_IRQHandler         ; irq 80 : CAN 2 TX warning IRQHandler
        DCD   CAN2_RxWarn_IRQHandler         ; irq 81 : CAN 2 RX warning IRQHandler
        DCD   CAN2_Err_IRQHandler            ; irq 82 : CAN 2 error IRQHandler
        DCD   CAN2_ErrFd_IRQHandler          ; irq 83 : CAN 2 error FD IRQHandler
        DCD   CAN2_PnWake_IRQHandler         ; irq 84 : CAN 2 wake match IRQHandler
        DCD   CAN2_SelfWakeup_IRQHandler     ; irq 85 : CAN 2 wake to IRQHandler
        DCD   CAN2_Ecc_IRQHandler            ; irq 86 : CAN 2 ECC IRQHandler
        DCD   CAN2_Mb0To15_IRQHandler        ; irq 87 : CAN 2 message buffer 0-15 IRQHandler
        DCD   CAN2_Mb16To31_IRQHandler       ; irq 88 : CAN 2 message buffer 16-31 IRQHandler
        DCD   CAN2_Mb32To47_IRQHandler       ; irq 89 : CAN 2 message buffer 32-47 IRQHandler
        DCD   CAN2_Mb48To63_IRQHandler       ; irq 90 : CAN 2 message buffer 48-63 IRQHandler
        DCD   CAN3_BusOff_IRQHandler         ; irq 91 : CAN 3 bus off/ bus off done IRQHandler
        DCD   CAN3_TxWarn_IRQHandler         ; irq 92 : CAN 3 TX warning IRQHandler
        DCD   CAN3_RxWarn_IRQHandler         ; irq 93 : CAN 3 RX warning IRQHandler
        DCD   CAN3_Err_IRQHandler            ; irq 94 : CAN 3 error IRQHandler
        DCD   CAN3_ErrFd_IRQHandler          ; irq 95 : CAN 3 error FD IRQHandler
        DCD   CAN3_PnWake_IRQHandler         ; irq 96 : CAN 3 wake match IRQHandler
        DCD   CAN3_SelfWakeup_IRQHandler     ; irq 97 : CAN 3 wake to IRQHandler
        DCD   CAN3_Ecc_IRQHandler            ; irq 98 : CAN 3 ECC IRQHandler
        DCD   CAN3_Mb0To15_IRQHandler        ; irq 99 : CAN 3 message buffer 0-15 IRQHandler
        DCD   CAN3_Mb16To31_IRQHandler       ; irq 100 : CAN 3 message buffer 16-31 IRQHandler
        DCD   CAN3_Mb32To47_IRQHandler       ; irq 101 : CAN 3 message buffer 32-47 IRQHandler
        DCD   CAN3_Mb48To63_IRQHandler       ; irq 102 : CAN 3 message buffer 48-63 IRQHandler
        DCD   CAN4_BusOff_IRQHandler         ; irq 103 : CAN 4 bus off/ bus off done IRQHandler
        DCD   CAN4_TxWarn_IRQHandler         ; irq 104 : CAN 4 TX warning IRQHandler
        DCD   CAN4_RxWarn_IRQHandler         ; irq 105 : CAN 4 RX warning IRQHandler
        DCD   CAN4_Err_IRQHandler            ; irq 106 : CAN 4 error IRQHandler
        DCD   CAN4_ErrFd_IRQHandler          ; irq 107 : CAN 4 error FD IRQHandler
        DCD   CAN4_PnWake_IRQHandler         ; irq 108 : CAN 4 wake match IRQHandler
        DCD   CAN4_SelfWakeup_IRQHandler     ; irq 109 : CAN 4 wake to IRQHandler
        DCD   CAN4_Ecc_IRQHandler            ; irq 110 : CAN 4 ECC IRQHandler
        DCD   CAN4_Mb0To15_IRQHandler        ; irq 111 : CAN 4 message buffer 0-15 IRQHandler
        DCD   CAN4_Mb16To31_IRQHandler       ; irq 112 : CAN 4 message buffer 16-31 IRQHandler
        DCD   CAN4_Mb32To47_IRQHandler       ; irq 113 : CAN 4 message buffer 32-47 IRQHandler
        DCD   CAN4_Mb48To63_IRQHandler       ; irq 114 : CAN 4 message buffer 48-63 IRQHandler
        DCD   CAN5_BusOff_IRQHandler         ; irq 115 : CAN 5 bus off/ bus off done IRQHandler
        DCD   CAN5_TxWarn_IRQHandler         ; irq 116 : CAN 5 TX warning IRQHandler
        DCD   CAN5_RxWarn_IRQHandler         ; irq 117 : CAN 5 RX warning IRQHandler
        DCD   CAN5_Err_IRQHandler            ; irq 118 : CAN 5 error IRQHandler
        DCD   CAN5_ErrFd_IRQHandler          ; irq 119 : CAN 5 error FD IRQHandler
        DCD   CAN5_PnWake_IRQHandler         ; irq 120 : CAN 5 wake match IRQHandler
        DCD   CAN5_SelfWakeup_IRQHandler     ; irq 121 : CAN 5 wake to IRQHandler
        DCD   CAN5_Ecc_IRQHandler            ; irq 122 : CAN 5 ECC IRQHandler
        DCD   CAN5_Mb0To15_IRQHandler        ; irq 123 : CAN 5 message buffer 0-15 IRQHandler
        DCD   CAN5_Mb16To31_IRQHandler       ; irq 124 : CAN 5 message buffer 16-31 IRQHandler
        DCD   CAN5_Mb32To47_IRQHandler       ; irq 125 : CAN 5 message buffer 32-47 IRQHandler
        DCD   CAN5_Mb48To63_IRQHandler       ; irq 126 : CAN 5 message buffer 48-63 IRQHandler
        DCD   Reserved127_IRQHandler         ; irq 127 : Reserved127 IRQHandler
        DCD   Reserved128_IRQHandler         ; irq 128 : Reserved128 IRQHandler
        DCD   Reserved129_IRQHandler         ; irq 129 : Reserved129 IRQHandler
        DCD   Reserved130_IRQHandler         ; irq 130 : Reserved130 IRQHandler
        DCD   Reserved131_IRQHandler         ; irq 131 : Reserved131 IRQHandler
        DCD   Reserved132_IRQHandler         ; irq 132 : Reserved132 IRQHandler
        DCD   Reserved133_IRQHandler         ; irq 133 : Reserved133 IRQHandler
        DCD   Reserved134_IRQHandler         ; irq 134 : Reserved134 IRQHandler
        DCD   Reserved135_IRQHandler         ; irq 135 : Reserved135 IRQHandler
        DCD   Reserved136_IRQHandler         ; irq 136 : Reserved136 IRQHandler
        DCD   Reserved137_IRQHandler         ; irq 137 : Reserved137 IRQHandler
        DCD   Reserved138_IRQHandler         ; irq 138 : Reserved138 IRQHandler
        DCD   Reserved139_IRQHandler         ; irq 139 : Reserved139 IRQHandler
        DCD   Reserved140_IRQHandler         ; irq 140 : Reserved140 IRQHandler
        DCD   Reserved141_IRQHandler         ; irq 141 : Reserved141 IRQHandler
        DCD   Reserved142_IRQHandler         ; irq 142 : Reserved142 IRQHandler
        DCD   Reserved143_IRQHandler         ; irq 143 : Reserved143 IRQHandler
        DCD   Reserved144_IRQHandler         ; irq 144 : Reserved144 IRQHandler
        DCD   Reserved145_IRQHandler         ; irq 145 : Reserved145 IRQHandler
        DCD   Reserved146_IRQHandler         ; irq 146 : Reserved146 IRQHandler
        DCD   Reserved147_IRQHandler         ; irq 147 : Reserved147 IRQHandler
        DCD   Reserved148_IRQHandler         ; irq 148 : Reserved148 IRQHandler
        DCD   Reserved149_IRQHandler         ; irq 149 : Reserved149 IRQHandler
        DCD   Reserved150_IRQHandler         ; irq 150 : Reserved150 IRQHandler
        DCD   Reserved151_IRQHandler         ; irq 151 : Reserved151 IRQHandler
        DCD   Reserved152_IRQHandler         ; irq 152 : Reserved152 IRQHandler
        DCD   Reserved153_IRQHandler         ; irq 153 : Reserved153 IRQHandler
        DCD   TIM0_Ch_IRQHandler             ; irq 154 : TIM0 CH IRQHandler
        DCD   TIM0_Fault_IRQHandler          ; irq 155 : TIM0 Fault IRQHandler
        DCD   TIM0_Overflow_IRQHandler        ; irq 156 : TIM0 overflow IRQHandler
        DCD   TIM0_Rlfl_IRQHandler           ; irq 157 : TIM0 Rlfl IRQHandler
        DCD   TIM1_Ch_IRQHandler             ; irq 158 : TIM1 CH IRQHandler
        DCD   TIM1_Fault_IRQHandler          ; irq 159 : TIM1 Fault IRQHandler
        DCD   TIM1_Overflow_IRQHandler        ; irq 160 : TIM1 overflow IRQHandler
        DCD   TIM1_Rlfl_IRQHandler           ; irq 161 : TIM1 Rlfl IRQHandler
        DCD   TIM2_Ch_IRQHandler             ; irq 162 : TIM2 CH IRQHandler
        DCD   TIM2_Fault_IRQHandler          ; irq 163 : TIM2 Fault IRQHandler
        DCD   TIM2_Overflow_IRQHandler        ; irq 164 : TIM2 overflow IRQHandler
        DCD   TIM2_Rlfl_IRQHandler           ; irq 165 : TIM2 Rlfl IRQHandler
        DCD   TIM3_Ch_IRQHandler             ; irq 166 : TIM3 CH IRQHandler
        DCD   TIM3_Fault_IRQHandler          ; irq 167 : TIM3 Fault IRQHandler
        DCD   TIM3_Overflow_IRQHandler        ; irq 168 : TIM3 overflow IRQHandler
        DCD   TIM3_Rlfl_IRQHandler           ; irq 169 : TIM3 Rlfl IRQHandler
        DCD   TDG0_Tco_IRQHandler            ; irq 170 : TDG0 TCO IRQHandler
        DCD   TDG0_Err_IRQHandler            ; irq 171 : TDG0 ERR IRQHandler
        DCD   TDG1_Tco_IRQHandler            ; irq 172 : TDG1 TCO IRQHandler
        DCD   TDG1_Err_IRQHandler            ; irq 173 : TDG1 ERR IRQHandler
        DCD   I2S0_IRQHandler                ; irq 174 : I2S0 IRQHandler
        DCD   Reserved175_IRQHandler         ; irq 175 : Reserved175 IRQHandler
        DCD   PORTA_IRQHandler               ; irq 176 : port A IRQHandler
        DCD   PORTB_IRQHandler               ; irq 177 : port B IRQHandler
        DCD   PORTC_IRQHandler               ; irq 178 : port C IRQHandler
        DCD   PORTD_IRQHandler               ; irq 179 : port D IRQHandler
        DCD   PORTE_IRQHandler               ; irq 180 : port E IRQHandler
        DCD   STIM_IRQHandler                ; irq 181 : STIM IRQHandler
        DCD   RTC_Alarm_IRQHandler           ; irq 182 : RTC alarm IRQHandler
        DCD   RTC_Second_IRQHandler          ; irq 183 : RTC second IRQHandler
        DCD   AES_IRQHandler                 ; irq 184 : AES IRQHandler
        DCD   TRNG_IRQHandler                ; irq 185 : TRNG IRQHandler
        DCD   CMU0_IRQHandler                ; irq 186 : CMU0 IRQHandler
        DCD   CMU1_IRQHandler                ; irq 187 : CMU1 IRQHandler
        DCD   CMU2_IRQHandler                ; irq 188 : CMU2 IRQHandler
        DCD   SERU_ParityErr_IRQHandler      ; irq 189 : SERU parity error IRQHandler
        DCD   SERU_ChErr_IRQHandler          ; irq 190 : SERU channel error IRQHandler
        DCD   SCC_IRQHandler                 ; irq 191 : SCC IRQHandler
        DCD   MCPWM0_Ch_IRQHandler           ; irq 192 : MCPWM0 CH IRQHandler
        DCD   MCPWM0_Fault_IRQHandler        ; irq 193 : MCPWM0 fault IRQHandler
        DCD   MCPWM0_Overflow_IRQHandler     ; irq 194 : MCPWM0 overflow IRQHandler
        DCD   MCPWM0_Rlfl_IRQHandler         ; irq 195 : MCPWM0 Rlfl IRQHandler
        DCD   MCPWM1_Ch_IRQHandler           ; irq 196 : MCPWM1 CH IRQHandler
        DCD   MCPWM1_Fault_IRQHandler        ; irq 197 : MCPWM1 fault IRQHandler
        DCD   MCPWM1_Overflow_IRQHandler     ; irq 198 : MCPWM1 overflow IRQHandler
        DCD   MCPWM1_Rlfl_IRQHandler         ; irq 199 : MCPWM1 Rlfl IRQHandler    
        DCD   ADC0_IRQHandler                ; irq 200 : ADC0 IRQHandler
        DCD   ADC1_IRQHandler                ; irq 201 : ADC1 IRQHandler    
        DCD   CMP_IRQHandler                 ; irq 202 : CMP IRQHandler
        DCD   SCM_FpuErr_IRQHandler             ; irq 203 : FPU error IRQHandler
        DCD   SCM_CacheErr_IRQHandler           ; irq 204 : CACHE error IRQHandler

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

        ; unlock PMU
        LDR     R0, =0x4007D000
        LDR     R1, =0x94730000
        STR     R1, [R0]
        
        ; enable PMU LVD in active/low power mode
        LDR     R0, =0x4007D010
        LDR     R1, =0x00000003
        LDR     R2, [R0]
        BIC     R2, R2, #0x000000C0
        ORR     R1, R1, R2
        STR     R1, [R0]
        
        ; lock pmu
        LDR     R0, =0x4007D000
        LDR     R1, =0x80000000
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

        PUBWEAK MemManageFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
MemManageFault_Handler
        B .

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BusFault_Handler
        B .

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UsageFault_Handler
        B .

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
        B .

        PUBWEAK DebugMonitor_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
DebugMonitor_Handler
        B .

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B .

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B .

        PUBWEAK DMA_Ch0_IRQHandler
        PUBWEAK DMA_Ch0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA_Ch0_IRQHandler
        LDR     R0, =DMA_Ch0_DriverIRQHandler
        BX      R0

        PUBWEAK DMA_Ch1_IRQHandler
        PUBWEAK DMA_Ch1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA_Ch1_IRQHandler
        LDR     R0, =DMA_Ch1_DriverIRQHandler
        BX      R0

        PUBWEAK DMA_Ch2_IRQHandler
        PUBWEAK DMA_Ch2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA_Ch2_IRQHandler
        LDR     R0, =DMA_Ch2_DriverIRQHandler
        BX      R0

        PUBWEAK DMA_Ch3_IRQHandler
        PUBWEAK DMA_Ch3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA_Ch3_IRQHandler
        LDR     R0, =DMA_Ch3_DriverIRQHandler
        BX      R0

        PUBWEAK DMA_Ch4_IRQHandler
        PUBWEAK DMA_Ch4_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA_Ch4_IRQHandler
        LDR     R0, =DMA_Ch4_DriverIRQHandler
        BX      R0

        PUBWEAK DMA_Ch5_IRQHandler
        PUBWEAK DMA_Ch5_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA_Ch5_IRQHandler
        LDR     R0, =DMA_Ch5_DriverIRQHandler
        BX      R0

        PUBWEAK DMA_Ch6_IRQHandler
        PUBWEAK DMA_Ch6_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA_Ch6_IRQHandler
        LDR     R0, =DMA_Ch6_DriverIRQHandler
        BX      R0

        PUBWEAK DMA_Ch7_IRQHandler
        PUBWEAK DMA_Ch7_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA_Ch7_IRQHandler
        LDR     R0, =DMA_Ch7_DriverIRQHandler
        BX      R0

        PUBWEAK DMA_Ch8_IRQHandler
        PUBWEAK DMA_Ch8_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA_Ch8_IRQHandler
        LDR     R0, =DMA_Ch8_DriverIRQHandler
        BX      R0

        PUBWEAK DMA_Ch9_IRQHandler
        PUBWEAK DMA_Ch9_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA_Ch9_IRQHandler
        LDR     R0, =DMA_Ch9_DriverIRQHandler
        BX      R0

        PUBWEAK DMA_Ch10_IRQHandler
        PUBWEAK DMA_Ch10_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA_Ch10_IRQHandler
        LDR     R0, =DMA_Ch10_DriverIRQHandler
        BX      R0

        PUBWEAK DMA_Ch11_IRQHandler
        PUBWEAK DMA_Ch11_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA_Ch11_IRQHandler
        LDR     R0, =DMA_Ch11_DriverIRQHandler
        BX      R0

        PUBWEAK DMA_Ch12_IRQHandler
        PUBWEAK DMA_Ch12_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA_Ch12_IRQHandler
        LDR     R0, =DMA_Ch12_DriverIRQHandler
        BX      R0

        PUBWEAK DMA_Ch13_IRQHandler
        PUBWEAK DMA_Ch13_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA_Ch13_IRQHandler
        LDR     R0, =DMA_Ch13_DriverIRQHandler
        BX      R0

        PUBWEAK DMA_Ch14_IRQHandler
        PUBWEAK DMA_Ch14_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA_Ch14_IRQHandler
        LDR     R0, =DMA_Ch14_DriverIRQHandler
        BX      R0

        PUBWEAK DMA_Ch15_IRQHandler
        PUBWEAK DMA_Ch15_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA_Ch15_IRQHandler
        LDR     R0, =DMA_Ch15_DriverIRQHandler
        BX      R0

        PUBWEAK DMA_Err_IRQHandler
        PUBWEAK DMA_Err_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
DMA_Err_IRQHandler
        LDR     R0, =DMA_Err_DriverIRQHandler
        BX      R0

        PUBWEAK FLASH_CmdComplete_IRQHandler
        PUBWEAK FLASH_CmdComplete_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLASH_CmdComplete_IRQHandler
        LDR     R0, =FLASH_CmdComplete_DriverIRQHandler
        BX      R0

        PUBWEAK FLASH_Ecc_IRQHandler
        PUBWEAK FLASH_Ecc_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
FLASH_Ecc_IRQHandler
        LDR     R0, =FLASH_Ecc_DriverIRQHandler
        BX      R0

        PUBWEAK PMU_IRQHandler
        PUBWEAK PMU_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PMU_IRQHandler
        LDR     R0, =PMU_DriverIRQHandler
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

        PUBWEAK SRMC_IRQHandler
        PUBWEAK SRMC_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SRMC_IRQHandler
        LDR     R0, =SRMC_DriverIRQHandler
        BX      R0

        PUBWEAK I2C0_IRQHandler
        PUBWEAK I2C0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
I2C0_IRQHandler
        LDR     R0, =I2C0_DriverIRQHandler
        BX      R0

        PUBWEAK I2C1_IRQHandler
        PUBWEAK I2C1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
I2C1_IRQHandler
        LDR     R0, =I2C1_DriverIRQHandler
        BX      R0

        PUBWEAK SPI0_Txe_IRQHandler
        PUBWEAK SPI0_Txe_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI0_Txe_IRQHandler
        LDR     R0, =SPI0_Txe_DriverIRQHandler
        BX      R0

        PUBWEAK SPI0_Txo_IRQHandler
        PUBWEAK SPI0_Txo_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI0_Txo_IRQHandler
        LDR     R0, =SPI0_Txo_DriverIRQHandler
        BX      R0

        PUBWEAK SPI0_Rxf_IRQHandler
        PUBWEAK SPI0_Rxf_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI0_Rxf_IRQHandler
        LDR     R0, =SPI0_Rxf_DriverIRQHandler
        BX      R0

        PUBWEAK SPI0_Rxo_IRQHandler
        PUBWEAK SPI0_Rxo_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI0_Rxo_IRQHandler
        LDR     R0, =SPI0_Rxo_DriverIRQHandler
        BX      R0

        PUBWEAK SPI0_Rxu_IRQHandler
        PUBWEAK SPI0_Rxu_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI0_Rxu_IRQHandler
        LDR     R0, =SPI0_Rxu_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved30_IRQHandler
        PUBWEAK SPI1_Txe_IRQHandler
        PUBWEAK SPI1_Txe_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI1_Txe_IRQHandler
        LDR     R0, =SPI1_Txe_DriverIRQHandler
        BX      R0

        PUBWEAK SPI1_Txo_IRQHandler
        PUBWEAK SPI1_Txo_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI1_Txo_IRQHandler
        LDR     R0, =SPI1_Txo_DriverIRQHandler
        BX      R0

        PUBWEAK SPI1_Rxf_IRQHandler
        PUBWEAK SPI1_Rxf_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI1_Rxf_IRQHandler
        LDR     R0, =SPI1_Rxf_DriverIRQHandler
        BX      R0

        PUBWEAK SPI1_Rxo_IRQHandler
        PUBWEAK SPI1_Rxo_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI1_Rxo_IRQHandler
        LDR     R0, =SPI1_Rxo_DriverIRQHandler
        BX      R0

        PUBWEAK SPI1_Rxu_IRQHandler
        PUBWEAK SPI1_Rxu_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI1_Rxu_IRQHandler
        LDR     R0, =SPI1_Rxu_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved36_IRQHandler
        PUBWEAK SPI2_Txe_IRQHandler
        PUBWEAK SPI2_Txe_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI2_Txe_IRQHandler
        LDR     R0, =SPI2_Txe_DriverIRQHandler
        BX      R0

        PUBWEAK SPI2_Txo_IRQHandler
        PUBWEAK SPI2_Txo_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI2_Txo_IRQHandler
        LDR     R0, =SPI2_Txo_DriverIRQHandler
        BX      R0

        PUBWEAK SPI2_Rxf_IRQHandler
        PUBWEAK SPI2_Rxf_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI2_Rxf_IRQHandler
        LDR     R0, =SPI2_Rxf_DriverIRQHandler
        BX      R0

        PUBWEAK SPI2_Rxo_IRQHandler
        PUBWEAK SPI2_Rxo_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI2_Rxo_IRQHandler
        LDR     R0, =SPI2_Rxo_DriverIRQHandler
        BX      R0

        PUBWEAK SPI2_Rxu_IRQHandler
        PUBWEAK SPI2_Rxu_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI2_Rxu_IRQHandler
        LDR     R0, =SPI2_Rxu_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved42_IRQHandler
        PUBWEAK SPI3_Txe_IRQHandler
        PUBWEAK SPI3_Txe_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI3_Txe_IRQHandler
        LDR     R0, =SPI3_Txe_DriverIRQHandler
        BX      R0

        PUBWEAK SPI3_Txo_IRQHandler
        PUBWEAK SPI3_Txo_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI3_Txo_IRQHandler
        LDR     R0, =SPI3_Txo_DriverIRQHandler
        BX      R0

        PUBWEAK SPI3_Rxf_IRQHandler
        PUBWEAK SPI3_Rxf_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI3_Rxf_IRQHandler
        LDR     R0, =SPI3_Rxf_DriverIRQHandler
        BX      R0

        PUBWEAK SPI3_Rxo_IRQHandler
        PUBWEAK SPI3_Rxo_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI3_Rxo_IRQHandler
        LDR     R0, =SPI3_Rxo_DriverIRQHandler
        BX      R0

        PUBWEAK SPI3_Rxu_IRQHandler
        PUBWEAK SPI3_Rxu_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SPI3_Rxu_IRQHandler
        LDR     R0, =SPI3_Rxu_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved48_IRQHandler
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

        PUBWEAK UART3_IRQHandler
        PUBWEAK UART3_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
UART3_IRQHandler
        LDR     R0, =UART3_DriverIRQHandler
        BX      R0

        PUBWEAK UART4_IRQHandler
        PUBWEAK UART4_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
UART4_IRQHandler
        LDR     R0, =UART4_DriverIRQHandler
        BX      R0

        PUBWEAK UART5_IRQHandler
        PUBWEAK UART5_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
UART5_IRQHandler
        LDR     R0, =UART5_DriverIRQHandler
        BX      R0

        PUBWEAK CAN0_BusOff_IRQHandler
        PUBWEAK CAN0_BusOff_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN0_BusOff_IRQHandler
        LDR     R0, =CAN0_BusOff_DriverIRQHandler
        BX      R0

        PUBWEAK CAN0_TxWarn_IRQHandler
        PUBWEAK CAN0_TxWarn_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN0_TxWarn_IRQHandler
        LDR     R0, =CAN0_TxWarn_DriverIRQHandler
        BX      R0

        PUBWEAK CAN0_RxWarn_IRQHandler
        PUBWEAK CAN0_RxWarn_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN0_RxWarn_IRQHandler
        LDR     R0, =CAN0_RxWarn_DriverIRQHandler
        BX      R0

        PUBWEAK CAN0_Err_IRQHandler
        PUBWEAK CAN0_Err_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN0_Err_IRQHandler
        LDR     R0, =CAN0_Err_DriverIRQHandler
        BX      R0

        PUBWEAK CAN0_ErrFd_IRQHandler
        PUBWEAK CAN0_ErrFd_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN0_ErrFd_IRQHandler
        LDR     R0, =CAN0_ErrFd_DriverIRQHandler
        BX      R0

        PUBWEAK CAN0_PnWake_IRQHandler
        PUBWEAK CAN0_PnWake_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN0_PnWake_IRQHandler
        LDR     R0, =CAN0_PnWake_DriverIRQHandler
        BX      R0

        PUBWEAK CAN0_SelfWakeup_IRQHandler
        PUBWEAK CAN0_SelfWakeup_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN0_SelfWakeup_IRQHandler
        LDR     R0, =CAN0_SelfWakeup_DriverIRQHandler
        BX      R0

        PUBWEAK CAN0_Ecc_IRQHandler
        PUBWEAK CAN0_Ecc_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN0_Ecc_IRQHandler
        LDR     R0, =CAN0_Ecc_DriverIRQHandler
        BX      R0

        PUBWEAK CAN0_Mb0To15_IRQHandler
        PUBWEAK CAN0_Mb0To15_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN0_Mb0To15_IRQHandler
        LDR     R0, =CAN0_Mb0To15_DriverIRQHandler
        BX      R0

        PUBWEAK CAN0_Mb16To31_IRQHandler
        PUBWEAK CAN0_Mb16To31_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN0_Mb16To31_IRQHandler
        LDR     R0, =CAN0_Mb16To31_DriverIRQHandler
        BX      R0

        PUBWEAK CAN0_Mb32To47_IRQHandler
        PUBWEAK CAN0_Mb32To47_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN0_Mb32To47_IRQHandler
        LDR     R0, =CAN0_Mb32To47_DriverIRQHandler
        BX      R0

        PUBWEAK CAN0_Mb48To63_IRQHandler
        PUBWEAK CAN0_Mb48To63_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN0_Mb48To63_IRQHandler
        LDR     R0, =CAN0_Mb48To63_DriverIRQHandler
        BX      R0

        PUBWEAK CAN1_BusOff_IRQHandler
        PUBWEAK CAN1_BusOff_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN1_BusOff_IRQHandler
        LDR     R0, =CAN1_BusOff_DriverIRQHandler
        BX      R0

        PUBWEAK CAN1_TxWarn_IRQHandler
        PUBWEAK CAN1_TxWarn_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN1_TxWarn_IRQHandler
        LDR     R0, =CAN1_TxWarn_DriverIRQHandler
        BX      R0

        PUBWEAK CAN1_RxWarn_IRQHandler
        PUBWEAK CAN1_RxWarn_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN1_RxWarn_IRQHandler
        LDR     R0, =CAN1_RxWarn_DriverIRQHandler
        BX      R0

        PUBWEAK CAN1_Err_IRQHandler
        PUBWEAK CAN1_Err_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN1_Err_IRQHandler
        LDR     R0, =CAN1_Err_DriverIRQHandler
        BX      R0

        PUBWEAK CAN1_ErrFd_IRQHandler
        PUBWEAK CAN1_ErrFd_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN1_ErrFd_IRQHandler
        LDR     R0, =CAN1_ErrFd_DriverIRQHandler
        BX      R0

        PUBWEAK CAN1_PnWake_IRQHandler
        PUBWEAK CAN1_PnWake_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN1_PnWake_IRQHandler
        LDR     R0, =CAN1_PnWake_DriverIRQHandler
        BX      R0

        PUBWEAK CAN1_SelfWakeup_IRQHandler
        PUBWEAK CAN1_SelfWakeup_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN1_SelfWakeup_IRQHandler
        LDR     R0, =CAN1_SelfWakeup_DriverIRQHandler
        BX      R0

        PUBWEAK CAN1_Ecc_IRQHandler
        PUBWEAK CAN1_Ecc_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN1_Ecc_IRQHandler
        LDR     R0, =CAN1_Ecc_DriverIRQHandler
        BX      R0

        PUBWEAK CAN1_Mb0To15_IRQHandler
        PUBWEAK CAN1_Mb0To15_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN1_Mb0To15_IRQHandler
        LDR     R0, =CAN1_Mb0To15_DriverIRQHandler
        BX      R0

        PUBWEAK CAN1_Mb16To31_IRQHandler
        PUBWEAK CAN1_Mb16To31_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN1_Mb16To31_IRQHandler
        LDR     R0, =CAN1_Mb16To31_DriverIRQHandler
        BX      R0

        PUBWEAK CAN1_Mb32To47_IRQHandler
        PUBWEAK CAN1_Mb32To47_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN1_Mb32To47_IRQHandler
        LDR     R0, =CAN1_Mb32To47_DriverIRQHandler
        BX      R0

        PUBWEAK CAN1_Mb48To63_IRQHandler
        PUBWEAK CAN1_Mb48To63_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN1_Mb48To63_IRQHandler
        LDR     R0, =CAN1_Mb48To63_DriverIRQHandler
        BX      R0

        PUBWEAK CAN2_BusOff_IRQHandler
        PUBWEAK CAN2_BusOff_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN2_BusOff_IRQHandler
        LDR     R0, =CAN2_BusOff_DriverIRQHandler
        BX      R0

        PUBWEAK CAN2_TxWarn_IRQHandler
        PUBWEAK CAN2_TxWarn_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN2_TxWarn_IRQHandler
        LDR     R0, =CAN2_TxWarn_DriverIRQHandler
        BX      R0

        PUBWEAK CAN2_RxWarn_IRQHandler
        PUBWEAK CAN2_RxWarn_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN2_RxWarn_IRQHandler
        LDR     R0, =CAN2_RxWarn_DriverIRQHandler
        BX      R0

        PUBWEAK CAN2_Err_IRQHandler
        PUBWEAK CAN2_Err_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN2_Err_IRQHandler
        LDR     R0, =CAN2_Err_DriverIRQHandler
        BX      R0

        PUBWEAK CAN2_ErrFd_IRQHandler
        PUBWEAK CAN2_ErrFd_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN2_ErrFd_IRQHandler
        LDR     R0, =CAN2_ErrFd_DriverIRQHandler
        BX      R0

        PUBWEAK CAN2_PnWake_IRQHandler
        PUBWEAK CAN2_PnWake_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN2_PnWake_IRQHandler
        LDR     R0, =CAN2_PnWake_DriverIRQHandler
        BX      R0

        PUBWEAK CAN2_SelfWakeup_IRQHandler
        PUBWEAK CAN2_SelfWakeup_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN2_SelfWakeup_IRQHandler
        LDR     R0, =CAN2_SelfWakeup_DriverIRQHandler
        BX      R0

        PUBWEAK CAN2_Ecc_IRQHandler
        PUBWEAK CAN2_Ecc_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN2_Ecc_IRQHandler
        LDR     R0, =CAN2_Ecc_DriverIRQHandler
        BX      R0

        PUBWEAK CAN2_Mb0To15_IRQHandler
        PUBWEAK CAN2_Mb0To15_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN2_Mb0To15_IRQHandler
        LDR     R0, =CAN2_Mb0To15_DriverIRQHandler
        BX      R0

        PUBWEAK CAN2_Mb16To31_IRQHandler
        PUBWEAK CAN2_Mb16To31_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN2_Mb16To31_IRQHandler
        LDR     R0, =CAN2_Mb16To31_DriverIRQHandler
        BX      R0

        PUBWEAK CAN2_Mb32To47_IRQHandler
        PUBWEAK CAN2_Mb32To47_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN2_Mb32To47_IRQHandler
        LDR     R0, =CAN2_Mb32To47_DriverIRQHandler
        BX      R0

        PUBWEAK CAN2_Mb48To63_IRQHandler
        PUBWEAK CAN2_Mb48To63_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN2_Mb48To63_IRQHandler
        LDR     R0, =CAN2_Mb48To63_DriverIRQHandler
        BX      R0

        PUBWEAK CAN3_BusOff_IRQHandler
        PUBWEAK CAN3_BusOff_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN3_BusOff_IRQHandler
        LDR     R0, =CAN3_BusOff_DriverIRQHandler
        BX      R0

        PUBWEAK CAN3_TxWarn_IRQHandler
        PUBWEAK CAN3_TxWarn_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN3_TxWarn_IRQHandler
        LDR     R0, =CAN3_TxWarn_DriverIRQHandler
        BX      R0

        PUBWEAK CAN3_RxWarn_IRQHandler
        PUBWEAK CAN3_RxWarn_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN3_RxWarn_IRQHandler
        LDR     R0, =CAN3_RxWarn_DriverIRQHandler
        BX      R0

        PUBWEAK CAN3_Err_IRQHandler
        PUBWEAK CAN3_Err_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN3_Err_IRQHandler
        LDR     R0, =CAN3_Err_DriverIRQHandler
        BX      R0

        PUBWEAK CAN3_ErrFd_IRQHandler
        PUBWEAK CAN3_ErrFd_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN3_ErrFd_IRQHandler
        LDR     R0, =CAN3_ErrFd_DriverIRQHandler
        BX      R0

        PUBWEAK CAN3_PnWake_IRQHandler
        PUBWEAK CAN3_PnWake_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN3_PnWake_IRQHandler
        LDR     R0, =CAN3_PnWake_DriverIRQHandler
        BX      R0

        PUBWEAK CAN3_SelfWakeup_IRQHandler
        PUBWEAK CAN3_SelfWakeup_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN3_SelfWakeup_IRQHandler
        LDR     R0, =CAN3_SelfWakeup_DriverIRQHandler
        BX      R0

        PUBWEAK CAN3_Ecc_IRQHandler
        PUBWEAK CAN3_Ecc_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN3_Ecc_IRQHandler
        LDR     R0, =CAN3_Ecc_DriverIRQHandler
        BX      R0

        PUBWEAK CAN3_Mb0To15_IRQHandler
        PUBWEAK CAN3_Mb0To15_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN3_Mb0To15_IRQHandler
        LDR     R0, =CAN3_Mb0To15_DriverIRQHandler
        BX      R0

        PUBWEAK CAN3_Mb16To31_IRQHandler
        PUBWEAK CAN3_Mb16To31_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN3_Mb16To31_IRQHandler
        LDR     R0, =CAN3_Mb16To31_DriverIRQHandler
        BX      R0

        PUBWEAK CAN3_Mb32To47_IRQHandler
        PUBWEAK CAN3_Mb32To47_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN3_Mb32To47_IRQHandler
        LDR     R0, =CAN3_Mb32To47_DriverIRQHandler
        BX      R0

        PUBWEAK CAN3_Mb48To63_IRQHandler
        PUBWEAK CAN3_Mb48To63_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN3_Mb48To63_IRQHandler
        LDR     R0, =CAN3_Mb48To63_DriverIRQHandler
        BX      R0

        PUBWEAK CAN4_BusOff_IRQHandler
        PUBWEAK CAN4_BusOff_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN4_BusOff_IRQHandler
        LDR     R0, =CAN4_BusOff_DriverIRQHandler
        BX      R0

        PUBWEAK CAN4_TxWarn_IRQHandler
        PUBWEAK CAN4_TxWarn_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN4_TxWarn_IRQHandler
        LDR     R0, =CAN4_TxWarn_DriverIRQHandler
        BX      R0

        PUBWEAK CAN4_RxWarn_IRQHandler
        PUBWEAK CAN4_RxWarn_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN4_RxWarn_IRQHandler
        LDR     R0, =CAN4_RxWarn_DriverIRQHandler
        BX      R0

        PUBWEAK CAN4_Err_IRQHandler
        PUBWEAK CAN4_Err_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN4_Err_IRQHandler
        LDR     R0, =CAN4_Err_DriverIRQHandler
        BX      R0

        PUBWEAK CAN4_ErrFd_IRQHandler
        PUBWEAK CAN4_ErrFd_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN4_ErrFd_IRQHandler
        LDR     R0, =CAN4_ErrFd_DriverIRQHandler
        BX      R0

        PUBWEAK CAN4_PnWake_IRQHandler
        PUBWEAK CAN4_PnWake_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN4_PnWake_IRQHandler
        LDR     R0, =CAN4_PnWake_DriverIRQHandler
        BX      R0

        PUBWEAK CAN4_SelfWakeup_IRQHandler
        PUBWEAK CAN4_SelfWakeup_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN4_SelfWakeup_IRQHandler
        LDR     R0, =CAN4_SelfWakeup_DriverIRQHandler
        BX      R0

        PUBWEAK CAN4_Ecc_IRQHandler
        PUBWEAK CAN4_Ecc_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN4_Ecc_IRQHandler
        LDR     R0, =CAN4_Ecc_DriverIRQHandler
        BX      R0

        PUBWEAK CAN4_Mb0To15_IRQHandler
        PUBWEAK CAN4_Mb0To15_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN4_Mb0To15_IRQHandler
        LDR     R0, =CAN4_Mb0To15_DriverIRQHandler
        BX      R0

        PUBWEAK CAN4_Mb16To31_IRQHandler
        PUBWEAK CAN4_Mb16To31_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN4_Mb16To31_IRQHandler
        LDR     R0, =CAN4_Mb16To31_DriverIRQHandler
        BX      R0

        PUBWEAK CAN4_Mb32To47_IRQHandler
        PUBWEAK CAN4_Mb32To47_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN4_Mb32To47_IRQHandler
        LDR     R0, =CAN4_Mb32To47_DriverIRQHandler
        BX      R0

        PUBWEAK CAN4_Mb48To63_IRQHandler
        PUBWEAK CAN4_Mb48To63_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN4_Mb48To63_IRQHandler
        LDR     R0, =CAN4_Mb48To63_DriverIRQHandler
        BX      R0

        PUBWEAK CAN5_BusOff_IRQHandler
        PUBWEAK CAN5_BusOff_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN5_BusOff_IRQHandler
        LDR     R0, =CAN5_BusOff_DriverIRQHandler
        BX      R0

        PUBWEAK CAN5_TxWarn_IRQHandler
        PUBWEAK CAN5_TxWarn_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN5_TxWarn_IRQHandler
        LDR     R0, =CAN5_TxWarn_DriverIRQHandler
        BX      R0

        PUBWEAK CAN5_RxWarn_IRQHandler
        PUBWEAK CAN5_RxWarn_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN5_RxWarn_IRQHandler
        LDR     R0, =CAN5_RxWarn_DriverIRQHandler
        BX      R0

        PUBWEAK CAN5_Err_IRQHandler
        PUBWEAK CAN5_Err_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN5_Err_IRQHandler
        LDR     R0, =CAN5_Err_DriverIRQHandler
        BX      R0

        PUBWEAK CAN5_ErrFd_IRQHandler
        PUBWEAK CAN5_ErrFd_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN5_ErrFd_IRQHandler
        LDR     R0, =CAN5_ErrFd_DriverIRQHandler
        BX      R0

        PUBWEAK CAN5_PnWake_IRQHandler
        PUBWEAK CAN5_PnWake_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN5_PnWake_IRQHandler
        LDR     R0, =CAN5_PnWake_DriverIRQHandler
        BX      R0

        PUBWEAK CAN5_SelfWakeup_IRQHandler
        PUBWEAK CAN5_SelfWakeup_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN5_SelfWakeup_IRQHandler
        LDR     R0, =CAN5_SelfWakeup_DriverIRQHandler
        BX      R0

        PUBWEAK CAN5_Ecc_IRQHandler
        PUBWEAK CAN5_Ecc_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN5_Ecc_IRQHandler
        LDR     R0, =CAN5_Ecc_DriverIRQHandler
        BX      R0

        PUBWEAK CAN5_Mb0To15_IRQHandler
        PUBWEAK CAN5_Mb0To15_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN5_Mb0To15_IRQHandler
        LDR     R0, =CAN5_Mb0To15_DriverIRQHandler
        BX      R0

        PUBWEAK CAN5_Mb16To31_IRQHandler
        PUBWEAK CAN5_Mb16To31_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN5_Mb16To31_IRQHandler
        LDR     R0, =CAN5_Mb16To31_DriverIRQHandler
        BX      R0

        PUBWEAK CAN5_Mb32To47_IRQHandler
        PUBWEAK CAN5_Mb32To47_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN5_Mb32To47_IRQHandler
        LDR     R0, =CAN5_Mb32To47_DriverIRQHandler
        BX      R0

        PUBWEAK CAN5_Mb48To63_IRQHandler
        PUBWEAK CAN5_Mb48To63_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CAN5_Mb48To63_IRQHandler
        LDR     R0, =CAN5_Mb48To63_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved127_IRQHandler
        PUBWEAK Reserved128_IRQHandler
        PUBWEAK Reserved129_IRQHandler
        PUBWEAK Reserved130_IRQHandler
        PUBWEAK Reserved131_IRQHandler
        PUBWEAK Reserved132_IRQHandler
        PUBWEAK Reserved133_IRQHandler
        PUBWEAK Reserved134_IRQHandler
        PUBWEAK Reserved135_IRQHandler
        PUBWEAK Reserved136_IRQHandler
        PUBWEAK Reserved137_IRQHandler
        PUBWEAK Reserved138_IRQHandler
        PUBWEAK Reserved139_IRQHandler
        PUBWEAK Reserved140_IRQHandler
        PUBWEAK Reserved141_IRQHandler
        PUBWEAK Reserved142_IRQHandler
        PUBWEAK Reserved143_IRQHandler
        PUBWEAK Reserved144_IRQHandler
        PUBWEAK Reserved145_IRQHandler
        PUBWEAK Reserved146_IRQHandler
        PUBWEAK Reserved147_IRQHandler
        PUBWEAK Reserved148_IRQHandler
        PUBWEAK Reserved149_IRQHandler
        PUBWEAK Reserved150_IRQHandler
        PUBWEAK Reserved151_IRQHandler
        PUBWEAK Reserved152_IRQHandler
        PUBWEAK Reserved153_IRQHandler
        PUBWEAK TIM0_Ch_IRQHandler
        PUBWEAK TIM0_Ch_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TIM0_Ch_IRQHandler
        LDR     R0, =TIM0_Ch_DriverIRQHandler
        BX      R0

        PUBWEAK TIM0_Fault_IRQHandler
        PUBWEAK TIM0_Fault_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TIM0_Fault_IRQHandler
        LDR     R0, =TIM0_Fault_DriverIRQHandler
        BX      R0

        PUBWEAK TIM0_Overflow_IRQHandler
        PUBWEAK TIM0_Overflow_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TIM0_Overflow_IRQHandler
        LDR     R0, =TIM0_Overflow_DriverIRQHandler
        BX      R0

        PUBWEAK TIM0_Rlfl_IRQHandler
        PUBWEAK TIM0_Rlfl_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TIM0_Rlfl_IRQHandler
        LDR     R0, =TIM0_Rlfl_DriverIRQHandler
        BX      R0

        PUBWEAK TIM1_Ch_IRQHandler
        PUBWEAK TIM1_Ch_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TIM1_Ch_IRQHandler
        LDR     R0, =TIM1_Ch_DriverIRQHandler
        BX      R0

        PUBWEAK TIM1_Fault_IRQHandler
        PUBWEAK TIM1_Fault_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TIM1_Fault_IRQHandler
        LDR     R0, =TIM1_Fault_DriverIRQHandler
        BX      R0

        PUBWEAK TIM1_Overflow_IRQHandler
        PUBWEAK TIM1_Overflow_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TIM1_Overflow_IRQHandler
        LDR     R0, =TIM1_Overflow_DriverIRQHandler
        BX      R0

        PUBWEAK TIM1_Rlfl_IRQHandler
        PUBWEAK TIM1_Rlfl_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TIM1_Rlfl_IRQHandler
        LDR     R0, =TIM1_Rlfl_DriverIRQHandler
        BX      R0

        PUBWEAK TIM2_Ch_IRQHandler
        PUBWEAK TIM2_Ch_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TIM2_Ch_IRQHandler
        LDR     R0, =TIM2_Ch_DriverIRQHandler
        BX      R0

        PUBWEAK TIM2_Fault_IRQHandler
        PUBWEAK TIM2_Fault_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TIM2_Fault_IRQHandler
        LDR     R0, =TIM2_Fault_DriverIRQHandler
        BX      R0

        PUBWEAK TIM2_Overflow_IRQHandler
        PUBWEAK TIM2_Overflow_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TIM2_Overflow_IRQHandler
        LDR     R0, =TIM2_Overflow_DriverIRQHandler
        BX      R0

        PUBWEAK TIM2_Rlfl_IRQHandler
        PUBWEAK TIM2_Rlfl_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TIM2_Rlfl_IRQHandler
        LDR     R0, =TIM2_Rlfl_DriverIRQHandler
        BX      R0

        PUBWEAK TIM3_Ch_IRQHandler
        PUBWEAK TIM3_Ch_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TIM3_Ch_IRQHandler
        LDR     R0, =TIM3_Ch_DriverIRQHandler
        BX      R0

        PUBWEAK TIM3_Fault_IRQHandler
        PUBWEAK TIM3_Fault_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TIM3_Fault_IRQHandler
        LDR     R0, =TIM3_Fault_DriverIRQHandler
        BX      R0

        PUBWEAK TIM3_Overflow_IRQHandler
        PUBWEAK TIM3_Overflow_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TIM3_Overflow_IRQHandler
        LDR     R0, =TIM3_Overflow_DriverIRQHandler
        BX      R0

        PUBWEAK TIM3_Rlfl_IRQHandler
        PUBWEAK TIM3_Rlfl_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TIM3_Rlfl_IRQHandler
        LDR     R0, =TIM3_Rlfl_DriverIRQHandler
        BX      R0

        PUBWEAK TDG0_Tco_IRQHandler
        PUBWEAK TDG0_Tco_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TDG0_Tco_IRQHandler
        LDR     R0, =TDG0_Tco_DriverIRQHandler
        BX      R0

        PUBWEAK TDG0_Err_IRQHandler
        PUBWEAK TDG0_Err_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TDG0_Err_IRQHandler
        LDR     R0, =TDG0_Err_DriverIRQHandler
        BX      R0

        PUBWEAK TDG1_Tco_IRQHandler
        PUBWEAK TDG1_Tco_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TDG1_Tco_IRQHandler
        LDR     R0, =TDG1_Tco_DriverIRQHandler
        BX      R0

        PUBWEAK TDG1_Err_IRQHandler
        PUBWEAK TDG1_Err_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TDG1_Err_IRQHandler
        LDR     R0, =TDG1_Err_DriverIRQHandler
        BX      R0

        PUBWEAK I2S0_IRQHandler
        PUBWEAK I2S0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
I2S0_IRQHandler
        LDR     R0, =I2S0_DriverIRQHandler
        BX      R0

        PUBWEAK Reserved175_IRQHandler
        PUBWEAK PORTA_IRQHandler
        PUBWEAK PORTA_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PORTA_IRQHandler
        LDR     R0, =PORTA_DriverIRQHandler
        BX      R0

        PUBWEAK PORTB_IRQHandler
        PUBWEAK PORTB_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PORTB_IRQHandler
        LDR     R0, =PORTB_DriverIRQHandler
        BX      R0

        PUBWEAK PORTC_IRQHandler
        PUBWEAK PORTC_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PORTC_IRQHandler
        LDR     R0, =PORTC_DriverIRQHandler
        BX      R0

        PUBWEAK PORTD_IRQHandler
        PUBWEAK PORTD_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PORTD_IRQHandler
        LDR     R0, =PORTD_DriverIRQHandler
        BX      R0

        PUBWEAK PORTE_IRQHandler
        PUBWEAK PORTE_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PORTE_IRQHandler
        LDR     R0, =PORTE_DriverIRQHandler
        BX      R0

        PUBWEAK STIM_IRQHandler
        PUBWEAK STIM_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
STIM_IRQHandler
        LDR     R0, =STIM_DriverIRQHandler
        BX      R0

        PUBWEAK RTC_Alarm_IRQHandler
        PUBWEAK RTC_Alarm_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
RTC_Alarm_IRQHandler
        LDR     R0, =RTC_Alarm_DriverIRQHandler
        BX      R0

        PUBWEAK RTC_Second_IRQHandler
        PUBWEAK RTC_Second_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
RTC_Second_IRQHandler
        LDR     R0, =RTC_Second_DriverIRQHandler
        BX      R0

        PUBWEAK AES_IRQHandler
        PUBWEAK AES_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
AES_IRQHandler
        LDR     R0, =AES_DriverIRQHandler
        BX      R0

        PUBWEAK TRNG_IRQHandler
        PUBWEAK TRNG_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
TRNG_IRQHandler
        LDR     R0, =TRNG_DriverIRQHandler
        BX      R0

        PUBWEAK CMU0_IRQHandler
        PUBWEAK CMU0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CMU0_IRQHandler
        LDR     R0, =CMU0_DriverIRQHandler
        BX      R0

        PUBWEAK CMU1_IRQHandler
        PUBWEAK CMU1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CMU1_IRQHandler
        LDR     R0, =CMU1_DriverIRQHandler
        BX      R0

        PUBWEAK CMU2_IRQHandler
        PUBWEAK CMU2_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CMU2_IRQHandler
        LDR     R0, =CMU2_DriverIRQHandler
        BX      R0

        PUBWEAK SERU_ParityErr_IRQHandler
        PUBWEAK SERU_ParityErr_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SERU_ParityErr_IRQHandler
        LDR     R0, =SERU_ParityErr_DriverIRQHandler
        BX      R0

        PUBWEAK SERU_ChErr_IRQHandler
        PUBWEAK SERU_ChErr_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SERU_ChErr_IRQHandler
        LDR     R0, =SERU_ChErr_DriverIRQHandler
        BX      R0

        PUBWEAK SCC_IRQHandler
        PUBWEAK SCC_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SCC_IRQHandler
        LDR     R0, =SCC_DriverIRQHandler
        BX      R0

        PUBWEAK MCPWM0_Ch_IRQHandler
        PUBWEAK MCPWM0_Ch_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
MCPWM0_Ch_IRQHandler
        LDR     R0, =MCPWM0_Ch_DriverIRQHandler
        BX      R0

        PUBWEAK MCPWM0_Fault_IRQHandler
        PUBWEAK MCPWM0_Fault_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
MCPWM0_Fault_IRQHandler
        LDR     R0, =MCPWM0_Fault_DriverIRQHandler
        BX      R0

        PUBWEAK MCPWM0_Overflow_IRQHandler
        PUBWEAK MCPWM0_Overflow_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
MCPWM0_Overflow_IRQHandler
        LDR     R0, =MCPWM0_Overflow_DriverIRQHandler
        BX      R0

        PUBWEAK MCPWM0_Rlfl_IRQHandler
        PUBWEAK MCPWM0_Rlfl_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
MCPWM0_Rlfl_IRQHandler
        LDR     R0, =MCPWM0_Rlfl_DriverIRQHandler
        BX      R0

        PUBWEAK MCPWM1_Ch_IRQHandler
        PUBWEAK MCPWM1_Ch_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
MCPWM1_Ch_IRQHandler
        LDR     R0, =MCPWM1_Ch_DriverIRQHandler
        BX      R0

        PUBWEAK MCPWM1_Fault_IRQHandler
        PUBWEAK MCPWM1_Fault_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
MCPWM1_Fault_IRQHandler
        LDR     R0, =MCPWM1_Fault_DriverIRQHandler
        BX      R0

        PUBWEAK MCPWM1_Overflow_IRQHandler
        PUBWEAK MCPWM1_Overflow_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
MCPWM1_Overflow_IRQHandler
        LDR     R0, =MCPWM1_Overflow_DriverIRQHandler
        BX      R0

        PUBWEAK MCPWM1_Rlfl_IRQHandler
        PUBWEAK MCPWM1_Rlfl_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
MCPWM1_Rlfl_IRQHandler
        LDR     R0, =MCPWM1_Rlfl_DriverIRQHandler
        BX      R0

        PUBWEAK ADC0_IRQHandler
        PUBWEAK ADC0_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ADC0_IRQHandler
        LDR     R0, =ADC0_DriverIRQHandler
        BX      R0

        PUBWEAK ADC1_IRQHandler
        PUBWEAK ADC1_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
ADC1_IRQHandler
        LDR     R0, =ADC1_DriverIRQHandler
        BX      R0

        PUBWEAK CMP_IRQHandler
        PUBWEAK CMP_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
CMP_IRQHandler
        LDR     R0, =CMP_DriverIRQHandler
        BX      R0

        PUBWEAK SCM_FpuErr_IRQHandler
        PUBWEAK SCM_FpuErr_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SCM_FpuErr_IRQHandler
        LDR     R0, =SCM_FpuErr_DriverIRQHandler
        BX      R0

        PUBWEAK SCM_CacheErr_IRQHandler
        PUBWEAK SCM_CacheErr_DriverIRQHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
SCM_CacheErr_IRQHandler
        LDR     R0, =SCM_CacheErr_DriverIRQHandler
        BX      R0

        PUBWEAK DefaultISR
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA_Ch0_DriverIRQHandler
DMA_Ch1_DriverIRQHandler
DMA_Ch2_DriverIRQHandler
DMA_Ch3_DriverIRQHandler
DMA_Ch4_DriverIRQHandler
DMA_Ch5_DriverIRQHandler
DMA_Ch6_DriverIRQHandler
DMA_Ch7_DriverIRQHandler
DMA_Ch8_DriverIRQHandler
DMA_Ch9_DriverIRQHandler
DMA_Ch10_DriverIRQHandler
DMA_Ch11_DriverIRQHandler
DMA_Ch12_DriverIRQHandler
DMA_Ch13_DriverIRQHandler
DMA_Ch14_DriverIRQHandler
DMA_Ch15_DriverIRQHandler
DMA_Err_DriverIRQHandler
FLASH_CmdComplete_DriverIRQHandler
FLASH_Ecc_DriverIRQHandler
PMU_DriverIRQHandler
WDOG_DriverIRQHandler
EWDT_DriverIRQHandler
SRMC_DriverIRQHandler
I2C0_DriverIRQHandler
I2C1_DriverIRQHandler
SPI0_Txe_DriverIRQHandler
SPI0_Txo_DriverIRQHandler
SPI0_Rxf_DriverIRQHandler
SPI0_Rxo_DriverIRQHandler
SPI0_Rxu_DriverIRQHandler
Reserved30_IRQHandler
SPI1_Txe_DriverIRQHandler
SPI1_Txo_DriverIRQHandler
SPI1_Rxf_DriverIRQHandler
SPI1_Rxo_DriverIRQHandler
SPI1_Rxu_DriverIRQHandler
Reserved36_IRQHandler
SPI2_Txe_DriverIRQHandler
SPI2_Txo_DriverIRQHandler
SPI2_Rxf_DriverIRQHandler
SPI2_Rxo_DriverIRQHandler
SPI2_Rxu_DriverIRQHandler
Reserved42_IRQHandler
SPI3_Txe_DriverIRQHandler
SPI3_Txo_DriverIRQHandler
SPI3_Rxf_DriverIRQHandler
SPI3_Rxo_DriverIRQHandler
SPI3_Rxu_DriverIRQHandler
Reserved48_IRQHandler
UART0_DriverIRQHandler
UART1_DriverIRQHandler
UART2_DriverIRQHandler
UART3_DriverIRQHandler
UART4_DriverIRQHandler
UART5_DriverIRQHandler
CAN0_BusOff_DriverIRQHandler
CAN0_TxWarn_DriverIRQHandler
CAN0_RxWarn_DriverIRQHandler
CAN0_Err_DriverIRQHandler
CAN0_ErrFd_DriverIRQHandler
CAN0_PnWake_DriverIRQHandler
CAN0_SelfWakeup_DriverIRQHandler
CAN0_Ecc_DriverIRQHandler
CAN0_Mb0To15_DriverIRQHandler
CAN0_Mb16To31_DriverIRQHandler
CAN0_Mb32To47_DriverIRQHandler
CAN0_Mb48To63_DriverIRQHandler
CAN1_BusOff_DriverIRQHandler
CAN1_TxWarn_DriverIRQHandler
CAN1_RxWarn_DriverIRQHandler
CAN1_Err_DriverIRQHandler
CAN1_ErrFd_DriverIRQHandler
CAN1_PnWake_DriverIRQHandler
CAN1_SelfWakeup_DriverIRQHandler
CAN1_Ecc_DriverIRQHandler
CAN1_Mb0To15_DriverIRQHandler
CAN1_Mb16To31_DriverIRQHandler
CAN1_Mb32To47_DriverIRQHandler
CAN1_Mb48To63_DriverIRQHandler
CAN2_BusOff_DriverIRQHandler
CAN2_TxWarn_DriverIRQHandler
CAN2_RxWarn_DriverIRQHandler
CAN2_Err_DriverIRQHandler
CAN2_ErrFd_DriverIRQHandler
CAN2_PnWake_DriverIRQHandler
CAN2_SelfWakeup_DriverIRQHandler
CAN2_Ecc_DriverIRQHandler
CAN2_Mb0To15_DriverIRQHandler
CAN2_Mb16To31_DriverIRQHandler
CAN2_Mb32To47_DriverIRQHandler
CAN2_Mb48To63_DriverIRQHandler
CAN3_BusOff_DriverIRQHandler
CAN3_TxWarn_DriverIRQHandler
CAN3_RxWarn_DriverIRQHandler
CAN3_Err_DriverIRQHandler
CAN3_ErrFd_DriverIRQHandler
CAN3_PnWake_DriverIRQHandler
CAN3_SelfWakeup_DriverIRQHandler
CAN3_Ecc_DriverIRQHandler
CAN3_Mb0To15_DriverIRQHandler
CAN3_Mb16To31_DriverIRQHandler
CAN3_Mb32To47_DriverIRQHandler
CAN3_Mb48To63_DriverIRQHandler
CAN4_BusOff_DriverIRQHandler
CAN4_TxWarn_DriverIRQHandler
CAN4_RxWarn_DriverIRQHandler
CAN4_Err_DriverIRQHandler
CAN4_ErrFd_DriverIRQHandler
CAN4_PnWake_DriverIRQHandler
CAN4_SelfWakeup_DriverIRQHandler
CAN4_Ecc_DriverIRQHandler
CAN4_Mb0To15_DriverIRQHandler
CAN4_Mb16To31_DriverIRQHandler
CAN4_Mb32To47_DriverIRQHandler
CAN4_Mb48To63_DriverIRQHandler
CAN5_BusOff_DriverIRQHandler
CAN5_TxWarn_DriverIRQHandler
CAN5_RxWarn_DriverIRQHandler
CAN5_Err_DriverIRQHandler
CAN5_ErrFd_DriverIRQHandler
CAN5_PnWake_DriverIRQHandler
CAN5_SelfWakeup_DriverIRQHandler
CAN5_Ecc_DriverIRQHandler
CAN5_Mb0To15_DriverIRQHandler
CAN5_Mb16To31_DriverIRQHandler
CAN5_Mb32To47_DriverIRQHandler
CAN5_Mb48To63_DriverIRQHandler
Reserved127_IRQHandler
Reserved128_IRQHandler
Reserved129_IRQHandler
Reserved130_IRQHandler
Reserved131_IRQHandler
Reserved132_IRQHandler
Reserved133_IRQHandler
Reserved134_IRQHandler
Reserved135_IRQHandler
Reserved136_IRQHandler
Reserved137_IRQHandler
Reserved138_IRQHandler
Reserved139_IRQHandler
Reserved140_IRQHandler
Reserved141_IRQHandler
Reserved142_IRQHandler
Reserved143_IRQHandler
Reserved144_IRQHandler
Reserved145_IRQHandler
Reserved146_IRQHandler
Reserved147_IRQHandler
Reserved148_IRQHandler
Reserved149_IRQHandler
Reserved150_IRQHandler
Reserved151_IRQHandler
Reserved152_IRQHandler
Reserved153_IRQHandler
TIM0_Ch_DriverIRQHandler
TIM0_Fault_DriverIRQHandler
TIM0_Overflow_DriverIRQHandler
TIM0_Rlfl_DriverIRQHandler
TIM1_Ch_DriverIRQHandler
TIM1_Fault_DriverIRQHandler
TIM1_Overflow_DriverIRQHandler
TIM1_Rlfl_DriverIRQHandler
TIM2_Ch_DriverIRQHandler
TIM2_Fault_DriverIRQHandler
TIM2_Overflow_DriverIRQHandler
TIM2_Rlfl_DriverIRQHandler
TIM3_Ch_DriverIRQHandler
TIM3_Fault_DriverIRQHandler
TIM3_Overflow_DriverIRQHandler
TIM3_Rlfl_DriverIRQHandler
TDG0_Tco_DriverIRQHandler
TDG0_Err_DriverIRQHandler
TDG1_Tco_DriverIRQHandler
TDG1_Err_DriverIRQHandler
I2S0_DriverIRQHandler
Reserved175_IRQHandler
PORTA_DriverIRQHandler
PORTB_DriverIRQHandler
PORTC_DriverIRQHandler
PORTD_DriverIRQHandler
PORTE_DriverIRQHandler
STIM_DriverIRQHandler
RTC_Alarm_DriverIRQHandler
RTC_Second_DriverIRQHandler
AES_DriverIRQHandler
TRNG_DriverIRQHandler
CMU0_DriverIRQHandler
CMU1_DriverIRQHandler
CMU2_DriverIRQHandler
SERU_ParityErr_DriverIRQHandler
SERU_ChErr_DriverIRQHandler
SCC_DriverIRQHandler
MCPWM0_Ch_DriverIRQHandler
MCPWM0_Fault_DriverIRQHandler
MCPWM0_Overflow_DriverIRQHandler
MCPWM0_Rlfl_DriverIRQHandler
MCPWM1_Ch_DriverIRQHandler
MCPWM1_Fault_DriverIRQHandler
MCPWM1_Overflow_DriverIRQHandler
MCPWM1_Rlfl_DriverIRQHandler
ADC0_DriverIRQHandler
ADC1_DriverIRQHandler
CMP_DriverIRQHandler
SCM_FpuErr_DriverIRQHandler
SCM_CacheErr_DriverIRQHandler
DefaultISR
        B DefaultISR
        END
