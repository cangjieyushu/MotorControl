;*********************************************************************************************
;Copyright <2024> <Icore Technology (Nanjing)  Co.,Ltd>
;All Rights Reserved,
;Redistribution and use in source and binary forms, with or without modification, are ;permitted
;provided that the following conditions are met:
;1. Redistributions of source code must retain the above copyright notice, this list of
;conditions and the following disclaimer.
;2. Redistributions in binary form must reproduce the above copyright notice, this list of
;conditions and the following disclaimer in the documentation and/or other materials ;provided 
;with the distribution.
;3. Neither the name of the copyright holder nor the names of its contributors may be ;used to 
;endorse or promote products derived from this software without specific prior written
;permission.
;THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ;"AS IS" AND ANY EXPRESS 
;OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED ;WARRANTIES OF 
;MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN ;NO EVENT SHALL THE 
;COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, ;INCIDENTAL, SPECIAL, 
;EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, ;PROCUREMENT OF SUBSTITUTE 
;GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS ;INTERRUPTION) HOWEVER CAUSED 
;AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR ;TORT (INCLUDING 
;NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS ;SOFTWARE, EVEN IF ADVISED 
;OF THE POSSIBILITY OF SUCH DAMAGE.
;**********************************************************************************************/
;/*
;*********************************************************************************************************
;*                                             rx32h6xx
;*                                         Library Function
;*
;*                                  Copyright 2024, RX Tech, Corp.
;*                                       All Rights Reserved
;*
;*
;* Project      : rx32h6xx
;* File         : startup_rx32h6xx.s
;* By           : SocTeam
;* Version      : 
;* Description  :
;*********************************************************************************************************
;*/

; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB

; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     __initial_sp               ; Top of Stack
                DCD     Reset_Handler              ; Reset Handler
                DCD     NMI_Handler                ; NMI Handler
                DCD     HardFault_Handler          ; Hard Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     SVC_Handler                ; SVCall Handler
                DCD     0                         ; Reserved
                DCD     0                          ; Reserved
                DCD     PendSV_Handler             ; PendSV Handler
                DCD     SysTick_Handler            ; SysTick Handler

                ; External Interrupts
                DCD     0                         ; 16+ 0: Reserved
                DCD     PVD_IRQHandler            ; 16+ 1: PVD
                DCD     RTC_IRQHandler            ; 16+ 2: RTC
                DCD     FLASH_IRQHandler          ; 16+ 3: FLASH
                DCD     RCC_IRQHandler            ; 16+ 4: RCC
                DCD     EXTI0_3_IRQHandler        ; 16+ 5: EXTI0_3
                DCD     EXTI4_7_IRQHandler        ; 16+ 6: EXTI4_7
                DCD     0                         ; 16+ 7: Reserved
                DCD     0                         ; 16+ 8: Reserved
                DCD     0                         ; 16+ 9: Reserved
                DCD     0                         ; 16+10: Reserved
                DCD     0                         ; 16+11: Reserved
                DCD     ADC_IRQHandler            ; 16+12: ADC
                DCD     TIM8_BRK_UP_TRG_COM_IRQHandler ; 16+13: TIM8_BRK_UP_TRG_COM
                DCD     TIM8_CC_IRQHandler        ; 16+14: TIM8_CC
                DCD     TIM2_IRQHandler           ; 16+15: TIM2
                DCD     TIM3_IRQHandler           ; 16+16: TIM3
                DCD     TIM6_IRQHandler           ; 16+17: TIM6
                DCD     TIM7_IRQHandler           ; 16+18: TIM7
                DCD     0                         ; 16+19: Reserved
                DCD     TIM15_IRQHandler          ; 16+20: TIM15
                DCD     CMP1_IRQHandler           ; 16+21: CMP1
                DCD     CMP2_IRQHandler           ; 16+22: CMP2
                DCD     I2C1_IRQHandler           ; 16+23: I2C1
                DCD     0                         ; 16+24: Reserved
                DCD     SPI1_IRQHandler           ; 16+25: SPI1
                DCD     0                         ; 16+26: Reserved
                DCD     UART1_IRQHandler          ; 16+27: UART1
                DCD     UART2_IRQHandler          ; 16+28: UART2
                DCD     0                         ; 16+29: Reserved
                DCD     0                         ; 16+30: CAN
                DCD     0                         ; 16+31: Reserved
                
;                IF      :LNOT::DEF:NO_CRP
;                AREA    |.ARM.__at_0x0FC0|, CODE, READONLY
;; FLASH加密使用此CODE
;; CRP_Key         DCD     0xFAFF00A2
;                
;; FLASH不加密使用此CODE
;CRP_Key         DCD     0xFAF5FFA2
;                ENDIF

                
                AREA    |.text|, CODE, READONLY
                
                
; Reset Handler
_RDefault      EQU     0xFFFFFFFF
Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R1, =_RDefault
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP           
                

; Dummy Exception Handlers (infinite loops which can be modified)

; now, under COMMON NMI.c and NMI.h, a real NMI handler is created if NMI is enabled
; for particular peripheral.
NMI_Handler     PROC
                EXPORT  NMI_Handler                [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler          [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler             [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler            [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  NMI_Handler                     [WEAK]
                EXPORT  PVD_IRQHandler                  [WEAK]
                EXPORT  RTC_IRQHandler                  [WEAK]
                EXPORT  FLASH_IRQHandler                [WEAK]
                EXPORT  RCC_IRQHandler                  [WEAK]
                EXPORT  EXTI0_3_IRQHandler              [WEAK]
                EXPORT  EXTI4_7_IRQHandler              [WEAK]
                EXPORT  ADC_IRQHandler                  [WEAK]
                EXPORT  TIM8_BRK_UP_TRG_COM_IRQHandler  [WEAK]
                EXPORT  TIM8_CC_IRQHandler              [WEAK]
                EXPORT  TIM2_IRQHandler                 [WEAK]
                EXPORT  TIM3_IRQHandler                 [WEAK]
                EXPORT  TIM6_IRQHandler                 [WEAK]
                EXPORT  TIM7_IRQHandler                 [WEAK]
                EXPORT  TIM15_IRQHandler                [WEAK]
                EXPORT  CMP1_IRQHandler                 [WEAK]
                EXPORT  CMP2_IRQHandler                 [WEAK]
                EXPORT  I2C1_IRQHandler                 [WEAK]
                EXPORT  SPI1_IRQHandler                 [WEAK]
                EXPORT  UART1_IRQHandler                [WEAK]
                EXPORT  UART2_IRQHandler                [WEAK]


                 
PVD_IRQHandler                
RTC_IRQHandler                
FLASH_IRQHandler              
RCC_IRQHandler                
EXTI0_3_IRQHandler            
EXTI4_7_IRQHandler                   
ADC_IRQHandler                
TIM8_BRK_UP_TRG_COM_IRQHandler
TIM8_CC_IRQHandler            
TIM2_IRQHandler               
TIM3_IRQHandler               
TIM6_IRQHandler               
TIM7_IRQHandler               
TIM15_IRQHandler              
CMP1_IRQHandler               
CMP2_IRQHandler               
I2C1_IRQHandler               
SPI1_IRQHandler               
UART1_IRQHandler              
UART2_IRQHandler                          



                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB           
                
                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit
                
                ELSE
                
                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END