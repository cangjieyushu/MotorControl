/**************************************************************************************************/
/**
 * @file      : Z20M1343L_Startup.s
 * @brief     : Z20M1343L startup and Vector Table Source File for IAR.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

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
        DCD   Reset_Handler                     ; POR Reset Entry
        DCD   NMI_Handler                       ; Non Maskable IrqHandler
        DCD   HardFault_Handler                 ; SV Hardfault IrqHandler
        DCD   0
        DCD   0
        DCD   0
        DCD   0
        DCD   0
        DCD   0
        DCD   0
        DCD   SVC_Handler                       ; SV Call IrqHandler
        DCD   0
        DCD   0
        DCD   PendSV_Handler                    ; Pend SV IrqHandler
        DCD   SysTick_Handler                   ; System Tick IrqHandler

        DCD   Stim_IrqHandler                   ; irq 0 : STIM IrqHandler
        DCD   Mcpwm_IrqHandler                  ; irq 1 : MCPWM IrqHandler
        DCD   Ctimer_IrqHandler                 ; irq 2 : CTIMER IrqHandler
        DCD   Adc_Ccomp01_IrqHandler            ; irq 3 : ADC convert complete 0-1 IrqHandler
        DCD   Adc_Ccomp23_IrqHandler            ; irq 4 : ADC convert complete 2-3 IrqHandler
        DCD   Adc_Ccomp45_IrqHandler            ; irq 5 : ADC convert complete 4-5 IrqHandler
        DCD   Adc_Ccomp67_IrqHandler            ; irq 6 : ADC convert complete 6-7 IrqHandler
        DCD   Adc_MapScomp_IrqHandler           ; irq 7 : ADC mapping complete IrqHandler
        DCD   Adc_LoopScomp_IrqHandler          ; irq 8 : ADC loop complete IrqHandler
        DCD   Adc_AwdgOver_IrqHandler           ; irq 9 : ADC awdg over IrqHandler
        DCD   Adc_AwdgUnder_IrqHandler          ; irq 10 : ADC awdg under IrqHandler
        DCD   Adc_Error_IrqHandler              ; irq 11 : ADC error IrqHandler
        DCD   Adc_MeasureTimer_IrqHandler       ; irq 12 : ADC measure timer IrqHandler
        DCD   Dma_Ch0_IrqHandler                ; irq 13 : DMA channel 0 transfer done IrqHandler
        DCD   Dma_Ch1_IrqHandler                ; irq 14 : DMA channel 1 transfer done IrqHandler
        DCD   Dma_Ch2_IrqHandler                ; irq 15 : DMA channel 2 transfer done IrqHandler
        DCD   Dma_Ch3_IrqHandler                ; irq 16 : DMA channel 3 transfer done IrqHandler
        DCD   Dma_Err_IrqHandler                ; irq 17 : DMA error IrqHandler
        DCD   Math_Accel_IrqHandler             ; irq 18 : MATH accelerator IrqHandler
        DCD   Reserved19_IrqHandler             ; irq 19 : Reserved interrupt
        DCD   Reserved20_IrqHandler             ; irq 20 : Reserved interrupt
        DCD   PortA_IrqHandler                  ; irq 21 : PORTA IrqHandler
        DCD   Pmu_Mon_IrqHandler                ; irq 22 : PMU MON IrqHandler
        DCD   Uart_IrqHandler                   ; irq 23 : UART/LIN IrqHandler
        DCD   Linphy_IrqHandler                 ; irq 24 : LIN PHY IrqHandler
        DCD   Spi_IrqHandler                    ; irq 25 : SPI IrqHandler
        DCD   Reserved26_IrqHandler             ; irq 26 : Reserved interrupt
        DCD   Srmc_IrqHandler                   ; irq 27 : System reset and mode control IrqHandler
        DCD   Pmu_IrqHandler                    ; irq 28 : PMU IrqHandler
        DCD   Reserved29_IrqHandler             ; irq 29 : Reserved interrupt
        DCD   Flash_EraseProgram_IrqHandler     ; irq 30 : Flash erase or program operation done IrqHandler
        DCD   Reserved31_IrqHandler             ; irq 31 : Reserved interrupt
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
        ;Unlock SCM_RAM_INIT
        LDR    R1, =0x40048008
        LDR    R2, =0x5A5A5A5A
        STR    R2, [R1]

        ;Trigger SRAM init
        LDR    R1, =0x40048020
        LDR    R2, [R1]
        LDR    R3, =0x100
        ORRS   R2, R2, R3
        STR    R2, [R1]

SRAM_TRIGGER_DONE:
        ;Wait SRAM Trigger done
        LDR    R1, =0x40048024
        LDR    R2, [R1]
        LDR    R3, =0x1
        ANDS   R2, R3
        CMP    R2, R3
        BNE    SRAM_TRIGGER_DONE

        ;Clear SRAML/SRAMU Trigger
        LDR    R1, =0x40048020
        LDR    R2, [R1]
        LDR    R3, =0x100
        BICS   R2, R2, R3
        STR    R2, [R1]

        ;Lock SCM_RAM_INIT
        LDR    R1, =0x40048008
        LDR    R2, =0xA5A5A5A5
        STR    R2, [R1]


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

        PUBWEAK Stim_IrqHandler
        PUBWEAK Stim_DriverIrqHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Stim_IrqHandler
        LDR     R0, =Stim_DriverIrqHandler
        BX      R0 

        PUBWEAK Mcpwm_IrqHandler
        PUBWEAK Mcpwm_DriverIrqHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Mcpwm_IrqHandler
        LDR     R0, =Mcpwm_DriverIrqHandler
        BX      R0 

        PUBWEAK Ctimer_IrqHandler
        PUBWEAK Ctimer_DriverIrqHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Ctimer_IrqHandler
        LDR     R0, =Ctimer_DriverIrqHandler
        BX      R0 

        PUBWEAK Adc_Ccomp01_IrqHandler
        PUBWEAK Adc_Ccomp01_DriverIrqHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Adc_Ccomp01_IrqHandler
        LDR     R0, =Adc_Ccomp01_DriverIrqHandler
        BX      R0 

        PUBWEAK Adc_Ccomp23_IrqHandler
        PUBWEAK Adc_Ccomp23_DriverIrqHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Adc_Ccomp23_IrqHandler
        LDR     R0, =Adc_Ccomp23_DriverIrqHandler
        BX      R0 

        PUBWEAK Adc_Ccomp45_IrqHandler
        PUBWEAK Adc_Ccomp45_DriverIrqHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Adc_Ccomp45_IrqHandler
        LDR     R0, =Adc_Ccomp45_DriverIrqHandler
        BX      R0 

        PUBWEAK Adc_Ccomp67_IrqHandler
        PUBWEAK Adc_Ccomp67_DriverIrqHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Adc_Ccomp67_IrqHandler
        LDR     R0, =Adc_Ccomp67_DriverIrqHandler
        BX      R0 

        PUBWEAK Adc_MapScomp_IrqHandler
        PUBWEAK Adc_MapScomp_DriverIrqHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Adc_MapScomp_IrqHandler
        LDR     R0, =Adc_MapScomp_DriverIrqHandler
        BX      R0 

        PUBWEAK Adc_LoopScomp_IrqHandler
        PUBWEAK Adc_LoopScomp_DriverIrqHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Adc_LoopScomp_IrqHandler
        LDR     R0, =Adc_LoopScomp_DriverIrqHandler
        BX      R0 

        PUBWEAK Adc_AwdgOver_IrqHandler
        PUBWEAK Adc_AwdgOver_DriverIrqHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Adc_AwdgOver_IrqHandler
        LDR     R0, =Adc_AwdgOver_DriverIrqHandler
        BX      R0 

        PUBWEAK Adc_AwdgUnder_IrqHandler
        PUBWEAK Adc_AwdgUnder_DriverIrqHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Adc_AwdgUnder_IrqHandler
        LDR     R0, =Adc_AwdgUnder_DriverIrqHandler
        BX      R0 

        PUBWEAK Adc_Error_IrqHandler
        PUBWEAK Adc_Error_DriverIrqHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Adc_Error_IrqHandler
        LDR     R0, =Adc_Error_DriverIrqHandler
        BX      R0 

        PUBWEAK Adc_MeasureTimer_IrqHandler
        PUBWEAK Adc_MeasureTimer_DriverIrqHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Adc_MeasureTimer_IrqHandler
        LDR     R0, =Adc_MeasureTimer_DriverIrqHandler
        BX      R0 

        PUBWEAK Dma_Ch0_IrqHandler
        PUBWEAK Dma_Ch0_DriverIrqHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Dma_Ch0_IrqHandler
        LDR     R0, =Dma_Ch0_DriverIrqHandler
        BX      R0 

        PUBWEAK Dma_Ch1_IrqHandler
        PUBWEAK Dma_Ch1_DriverIrqHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Dma_Ch1_IrqHandler
        LDR     R0, =Dma_Ch1_DriverIrqHandler
        BX      R0 

        PUBWEAK Dma_Ch2_IrqHandler
        PUBWEAK Dma_Ch2_DriverIrqHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Dma_Ch2_IrqHandler
        LDR     R0, =Dma_Ch2_DriverIrqHandler
        BX      R0 

        PUBWEAK Dma_Ch3_IrqHandler
        PUBWEAK Dma_Ch3_DriverIrqHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Dma_Ch3_IrqHandler
        LDR     R0, =Dma_Ch3_DriverIrqHandler
        BX      R0 

        PUBWEAK Dma_Err_IrqHandler
        PUBWEAK Dma_Err_DriverIrqHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Dma_Err_IrqHandler
        LDR     R0, =Dma_Err_DriverIrqHandler
        BX      R0 

        PUBWEAK Math_Accel_IrqHandler
        PUBWEAK Math_Accel_DriverIrqHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Math_Accel_IrqHandler
        LDR     R0, =Math_Accel_DriverIrqHandler
        BX      R0 

        PUBWEAK Reserved19_IrqHandler

        PUBWEAK Reserved20_IrqHandler

        PUBWEAK PortA_IrqHandler
        PUBWEAK PortA_DriverIrqHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
PortA_IrqHandler
        LDR     R0, =PortA_DriverIrqHandler
        BX      R0 

        PUBWEAK Pmu_Mon_IrqHandler
        PUBWEAK Pmu_Mon_DriverIrqHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Pmu_Mon_IrqHandler
        LDR     R0, =Pmu_Mon_DriverIrqHandler
        BX      R0 

        PUBWEAK Uart_IrqHandler
        PUBWEAK Uart_DriverIrqHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Uart_IrqHandler
        LDR     R0, =Uart_DriverIrqHandler
        BX      R0 

        PUBWEAK Linphy_IrqHandler
        PUBWEAK Linphy_DriverIrqHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Linphy_IrqHandler
        LDR     R0, =Linphy_DriverIrqHandler
        BX      R0 

        PUBWEAK Spi_IrqHandler
        PUBWEAK Spi_DriverIrqHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Spi_IrqHandler
        LDR     R0, =Spi_DriverIrqHandler
        BX      R0 

        PUBWEAK Reserved26_IrqHandler
        PUBWEAK Srmc_IrqHandler
        PUBWEAK Srmc_DriverIrqHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Srmc_IrqHandler
        LDR     R0, =Srmc_DriverIrqHandler
        BX      R0 

        PUBWEAK Reserved29_IrqHandler
        PUBWEAK Pmu_IrqHandler
        PUBWEAK Pmu_DriverIrqHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Pmu_IrqHandler
        LDR     R0, =Pmu_DriverIrqHandler
        BX      R0 

        PUBWEAK Flash_EraseProgram_IrqHandler
        PUBWEAK Flash_EraseProgram_DriverIrqHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Flash_EraseProgram_IrqHandler
        LDR     R0, =Flash_EraseProgram_DriverIrqHandler
        BX      R0 

        PUBWEAK Reserved31_IrqHandler

        PUBWEAK DefaultISR
        SECTION .text:CODE:REORDER:NOROOT(1)
Stim_DriverIrqHandler
Mcpwm_DriverIrqHandler
Ctimer_DriverIrqHandler
Adc_Ccomp01_DriverIrqHandler
Adc_Ccomp23_DriverIrqHandler
Adc_Ccomp45_DriverIrqHandler
Adc_Ccomp67_DriverIrqHandler
Adc_MapScomp_DriverIrqHandler
Adc_LoopScomp_DriverIrqHandler
Adc_AwdgOver_DriverIrqHandler
Adc_AwdgUnder_DriverIrqHandler
Adc_Error_DriverIrqHandler
Adc_MeasureTimer_DriverIrqHandler
Dma_Ch0_DriverIrqHandler
Dma_Ch1_DriverIrqHandler
Dma_Ch2_DriverIrqHandler
Dma_Ch3_DriverIrqHandler
Dma_Err_DriverIrqHandler
Math_Accel_DriverIrqHandler
Reserved19_IrqHandler
Reserved20_IrqHandler
PortA_DriverIrqHandler
Pmu_Mon_DriverIrqHandler
Uart_DriverIrqHandler
Linphy_DriverIrqHandler
Spi_DriverIrqHandler
Reserved26_IrqHandler
Srmc_DriverIrqHandler
Pmu_DriverIrqHandler
Reserved29_IrqHandler
Flash_EraseProgram_DriverIrqHandler
Reserved31_IrqHandler
DefaultISR
        B DefaultISR

        END
