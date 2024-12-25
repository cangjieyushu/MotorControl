/*********************************************************************************************
Copyright <2024> <Icore Technology (Nanjing)  Co.,Ltd>
All Rights Reserved,
Redistribution and use in source and binary forms, with or without modification, are permitted
provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice, this list of
conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list of
conditions and the following disclaimer in the documentation and/or other materials provided 
with the distribution.
3. Neither the name of the copyright holder nor the names of its contributors may be used to 
endorse or promote products derived from this software without specific prior written
permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS 
OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
OF THE POSSIBILITY OF SUCH DAMAGE.
**********************************************************************************************/

/*
*********************************************************************************************************
*                                              RX32H6xx
*                                           Library Function
*
*                                   Copyright 2024, RX Tech, Corp.
*                                        All Rights Reserved
*
*
* Project      : RX32H6xx
* File         : RX32H6xx.h
* By           : RX_SD_Team
* Version      : V1.0.0
* Description  : 
*********************************************************************************************************
*/
    
#ifndef __RX32H6xx_H
#define __RX32H6xx_H

#ifdef __cplusplus
 extern "C" {
#endif 

typedef enum {DISABLE = 0, ENABLE = !DISABLE}   FunctionalState;        
typedef enum {RESET   = 0, SET    = !RESET  }   FlagStatus, ITStatus;   
typedef enum {FALSE   = 0, TRUE   = !FALSE  }   Bool;

typedef enum
{
  SUCCESS = 0U,
  ERROR = !SUCCESS
} ErrorStatus;

#define SET(n,c)		((n)|=(c))
#define CLR(n,c)		((n)&=~(c))

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL))) 

#define M8(adr)     (*((volatile uint8_t *)  (adr)))
#define M16(adr)    (*((volatile uint16_t *) (adr)))
#define M32(adr)    (*((volatile uint32_t *) (adr)))


#define BIT0			((uint32_t)0x00000001)
#define BIT1			((uint32_t)0x00000002)
#define BIT2			((uint32_t)0x00000004)
#define BIT3			((uint32_t)0x00000008)
#define BIT4			((uint32_t)0x00000010)
#define BIT5			((uint32_t)0x00000020)
#define BIT6			((uint32_t)0x00000040)
#define BIT7			((uint32_t)0x00000080)
#define BIT8			((uint32_t)0x00000100)
#define BIT9			((uint32_t)0x00000200)
#define BIT10			((uint32_t)0x00000400)
#define BIT11			((uint32_t)0x00000800)
#define BIT12			((uint32_t)0x00001000)
#define BIT13			((uint32_t)0x00002000)
#define BIT14			((uint32_t)0x00004000)
#define BIT15			((uint32_t)0x00008000)
#define BIT16			((uint32_t)0x00010000)
#define BIT17			((uint32_t)0x00020000)
#define BIT18			((uint32_t)0x00040000)
#define BIT19			((uint32_t)0x00080000)
#define BIT20			((uint32_t)0x00100000)
#define BIT21			((uint32_t)0x00200000)
#define BIT22			((uint32_t)0x00400000)
#define BIT23			((uint32_t)0x00800000)
#define BIT24			((uint32_t)0x01000000)
#define BIT25			((uint32_t)0x02000000)
#define BIT26			((uint32_t)0x04000000)
#define BIT27			((uint32_t)0x08000000)
#define BIT28			((uint32_t)0x10000000)
#define BIT29			((uint32_t)0x20000000)
#define BIT30			((uint32_t)0x40000000)
#define BIT31			((uint32_t)0x80000000)

/** @addtogroup Configuration_section_for_CMSIS
  * @{
  */

/**
  * @}
  */

/** @addtogroup Peripheral_interrupt_number_definition
  * @{
  */

/**
 * @brief RX32H6xx Interrupt Number Definition, according to the selected device 
 *        in @ref Library_configuration_section 
 */
typedef enum IRQn
{
/*****************************  Cortex-M0 Processor Exceptions Numbers  *********************************/
    NonMaskableInt_IRQn         = -14,      /*!< 2 Non Maskable Interrupt  CMU                    */
    HardFault_IRQn              = -13,      /*!< 3 Cortex-M0 Hard Fault Interrupt                 */
    SVCall_IRQn                 = -5,       /*!< 11 Cortex-M0 SV Call Interrupt                   */
    PendSV_IRQn                 = -2,       /*!< 14 Cortex-M0 Pend SV Interrupt                   */
    SysTick_IRQn                = -1,       /*!< 15 Cortex-M0 System Tick Interrupt               */

/***************************** rx32h6 Specific Interrupt Numbers  **************************************/
    PVD_IRQn                    = 1,	    /*!< PVD Interrupt                                    */
	RTC_IRQn					= 2, 	    /*!< RTC Interrupt                                    */				
    FLASH_IRQn                  = 3,        /*!< FLASH Interrupt                                  */
    RCC_IRQn                    = 4,        /*!< RCC Interrupt                                    */
    EXTI0_3_IRQn                = 5,        /*!< External Interrupt 0-3 Interrupt                 */
    EXTI4_7_IRQn                = 6,        /*!< External Interrupt 4-7 Interrupt                 */
    ADC_IRQn					= 12,       /*!< ADC Interrupt                                    */
    TIM8_BRK_UP_TRG_COM_IRQn    = 13,       /*!< TIM8 break, update, trigger and commutation interrupt*/
    TIM8_CC_IRQn                = 14,       /*!< TIM8 capture compare interrupt                   */
    TIM2_IRQn                   = 15,       /*!< Timer2 Interrupt                                 */
    TIM3_IRQn                   = 16,       /*!< Timer3 Interrupt                                 */
    TIM6_IRQn                   = 17,       /*!< Timer6 Interrupt                                 */
    TIM7_IRQn                   = 18,       /*!< Timer7 Interrupt                                 */
    TIM15_IRQn					= 20,       /*!< Timer15 Interrupt                                */
  	CMP1_IRQn					= 21,       /*!< CMP1 Interrupt                                   */
    CMP2_IRQn                	= 22,       /*!< CMP2 Interrupt                                   */
    I2C1_IRQn                   = 23,       /*!< I2C global interrupt                             */
    SPI1_IRQn                   = 25,       /*!< SPI1 global interrupt                            */
    UART1_IRQn                  = 27,       /*!< UART1 global interrupt                           */
    UART2_IRQn                  = 28,       /*!< UART2 global interrupt                           */
} IRQn_Type;

/**
  * @}
  */

/********************  Configuration of the Cortex-M0 Processor and Core Peripherals  *******************/
#define __MPU_PRESENT             0         /*!< MPU present or not                               */
#define __NVIC_PRIO_BITS          2         /*!< Number of Bits used for Priority Levels          */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used     */
                                            /* end of group rx32h6_CMSIS                         */

#include "core_cm0.h"
#include "system_rx32h6xx.h"
#include <stdint.h>

/** @addtogroup Peripheral_registers_structures
  * @{
  */   

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/** 
  * @brief ADC Registers 
  */
typedef struct
{
  __IO uint32_t SR;   		 //0x0000
  __IO uint32_t CR1; 		//0x0004
  __IO uint32_t CR2;		//0x0008
  __IO uint32_t SMPR1;	//0x000C
  __IO uint32_t SMPR2;	//0x0010
  __IO uint32_t JOFR1;	//0x0014
  __IO uint32_t JOFR2;	//0x0018
  __IO uint32_t JOFR3;	//0x001C
  __IO uint32_t JOFR4;	//0x0020
  __IO uint32_t HTR;		//0x0024
  __IO uint32_t LTR;		//0x0028
  __IO uint32_t SQR1;		//0x002C
  __IO uint32_t SQR2;		//0x0030
  __IO uint32_t SQR3;		//0x0034
  __IO uint32_t JSQR;		//0x0038
  __IO uint32_t JDR1;		//0x003C
  __IO uint32_t JDR2;		//0x0040
  __IO uint32_t JDR3;		//0x0044
  __IO uint32_t JDR4;		//0x0048
  __IO uint32_t DR;		//0x004C
  uint32_t RESERVED3;
  __IO uint32_t CAL;		//0x0054
  uint32_t RESERVED1;
  __IO uint32_t TPS_TEST;		//0x005C
  uint32_t RESERVED2;
  __IO uint32_t TPS;		//0x0064
  __IO uint32_t SMPR;	//0x0068
  __IO uint32_t DATA1;	//0x006C
  __IO uint32_t DATA2;	//0x0070
  __IO uint32_t DATA3;	//0x0074
  __IO uint32_t DATA4;	//0x0078
  __IO uint32_t DATA5;	//0x007C
  __IO uint32_t DATA6;	//0x0080
  __IO uint32_t DATA7;	//0x0084
  __IO uint32_t DATA8;	//0x0088
	uint32_t RESERVED4;
	uint32_t RESERVED5;
	__IO uint32_t CR3;  //0x0094
} ADC_TypeDef;
  
/** 
  * @brief CRC calculation unit 
  */

typedef struct
{
  __IO uint32_t DR;           /*!< CRC Data register,                           Address offset: 0x00 */
  __IO uint8_t  IDR;          /*!< CRC Independent data register,               Address offset: 0x04 */
  uint8_t       RESERVED0;    /*!< Reserved,                                    Address offset: 0x05 */
  uint16_t      RESERVED1;    /*!< Reserved,                                    Address offset: 0x06 */  
  __IO uint32_t CR;           /*!< CRC Control register,                        Address offset: 0x08 */ 
} CRC_TypeDef;


/** 
  * @brief External Interrupt/Event Controller
  */

typedef struct
{
  __IO uint32_t IMR;
  __IO uint32_t EMR;
  __IO uint32_t RTSR;
  __IO uint32_t FTSR;
  __IO uint32_t SWIER;
  __IO uint32_t PR;
} EXTI_TypeDef;

/** 
  * @brief FLASH Registers
  */

typedef struct
{
  __IO uint32_t ACR;              /*!< FLASH access control register,            Address offset: 0x00 */
  __IO uint32_t PDKEYR;           /*!< FLASH power down key register,            Address offset: 0x04 */
  __IO uint32_t KEYR;             /*!< FLASH key register,                       Address offset: 0x08 */
  __IO uint32_t OPTKEYR;          /*!< FLASH option key register,                Address offset: 0x0C */
  __IO uint32_t SR;               /*!< FLASH status register,                    Address offset: 0x10 */
  __IO uint32_t CR;               /*!< FLASH control register,                   Address offset: 0x14 */
       uint32_t RESERVED1[2];        /*!< Reserved,                              Address offset: 0x18 */
  __IO uint32_t OPTR;             /*!< FLASH option register,                    Address offset: 0x20 */
	 uint32_t RESERVED4[2];        /*!< Reserved,                                  Address offset: 0x24 */
  __IO uint32_t WRP1AR;           /*!< FLASH bank1 WRP area A address register,  Address offset: 0x2C */
  __IO uint32_t WRP1BR;           /*!< FLASH bank1 WRP area B address register,  Address offset: 0x30 */
} FLASH_TypeDef;


/** 
  * @brief Debug MCU
  */

typedef struct
{
  __IO uint32_t IDCODE;
  __IO uint32_t CR;
}DBGMCU_TypeDef;

/** 
  * @brief General Purpose I/O
  */
typedef struct
{
  __IO uint32_t MODER;
  __IO uint32_t OTYPER;
  __IO uint32_t OSPEEDR;
  __IO uint32_t PUPDR;
  __IO uint32_t IDR;
  __IO uint32_t ODR;
  #ifdef BSRR_u8
  __IO uint8_t u8_BSR1;    //0x18
  __IO uint8_t u8_BSR2;    //0x19
  __IO uint8_t u8_BRR1;    //0x1A
  __IO uint8_t u8_BRR2;    //0x1B
  #endif
  #ifdef BSRR_u16
  __IO uint16_t u16_BSR;  //0x18 
  __IO uint16_t u16_BRR;  //0x1A
  #endif
  #ifdef BSRR_u32
  __IO uint32_t BSRR;  //0x18 
  #endif
  #if !defined( BSRR_u8 ) && !defined( BSRR_u16 ) && !defined( BSRR_u32 )
  __IO uint32_t BSRR;   //0x18
  #endif
  __IO uint32_t LCKR;
  __IO uint32_t AFRL;
} GPIO_TypeDef;

/** 
  * @brief Alternate Function I/O
  */

typedef struct
{
  uint32_t  RESERVED0[2];//0x00 0x04
  __IO uint32_t EXTICR[4];//0x08 0x0C 0x10 0x14
	__IO uint32_t SCSR;//0x18
	__IO uint32_t CFGR2;//0x1C
  __IO uint32_t RESERVED1;//0x20
  __IO uint32_t SKR;//0x24
  __IO uint32_t RESERVED2;//0x28
  __IO uint32_t CCMINT;//0x2C
} SYSCFG_TypeDef;



typedef struct
{
	__IO uint32_t CSR;
  __IO uint32_t CCR;
} VREFBUF_TypeDef;


/** 
  * @brief Inter Integrated Circuit Interface
  */

typedef struct
{
  __IO uint32_t CR1;
  __IO uint32_t CR2;
  __IO uint32_t OAR1;
  __IO uint32_t OAR2;
  __IO uint32_t DR;
  __IO uint32_t SR1;
  __IO uint32_t SR2;
  __IO uint32_t CCR;
  __IO uint32_t TRISE;
} I2C_TypeDef;

/** 
  * @brief Independent WATCHDOG
  */

typedef struct
{
  __IO uint32_t KR;           /*!< Key register,                                Address offset: 0x00 */
  __IO uint32_t PR;           /*!< Prescaler register,                          Address offset: 0x04 */
  __IO uint32_t RLR;          /*!< Reload register,                             Address offset: 0x08 */
  __IO uint32_t SR;           /*!< Status register,                             Address offset: 0x0C */
} IWDG_TypeDef;

/** 
  * @brief Power Control
  */

typedef struct
{
  __IO uint32_t CR1;
  __IO uint32_t CR2;
	__IO uint32_t CR3;
	__IO uint32_t CR4;
	__IO uint32_t SR;
	__IO uint32_t SR2;
	__IO uint32_t SCR;
} PWR_TypeDef;

/** 
  * @brief Reset and Clock Control
  */

typedef struct
{
  __IO uint32_t CR;
  __IO uint32_t CFGR;
  __IO uint32_t CIR;
  __IO uint32_t APB2RSTR;
  __IO uint32_t APB1RSTR;
  __IO uint32_t AHBENR;
  __IO uint32_t APB2ENR;
  __IO uint32_t APB1ENR;
  __IO uint32_t BDCR;
  __IO uint32_t CSR;
	__IO uint32_t AHBRSTR;
	uint32_t RESERVED1[29];
	uint32_t RESERVED2;
	__IO uint32_t PLLDET;
} RCC_TypeDef;

/** 
  * @brief Real-Time Clock
  */

typedef struct
{
  __IO uint32_t CRH;
  __IO uint32_t CRL;
  __IO uint32_t PRLH;
  __IO uint32_t PRLL;
  __IO uint32_t DIVH;
  __IO uint32_t DIVL;
  __IO uint32_t CNTH;
  __IO uint32_t CNTL;
  __IO uint32_t ALRH;
  __IO uint32_t ALRL;
} RTC_TypeDef;

/** 
  * @brief Backup Registers  
  */

typedef struct
{
  uint32_t  RESERVED[11];
  __IO uint32_t RTCCR;
  __IO uint32_t CR;
  __IO uint32_t CSR;
} BKP_TypeDef;

/** 
  * @brief Serial Peripheral Interface
  */

typedef struct
{
  __IO uint32_t CR1;
  __IO uint32_t CR2;
  __IO uint32_t SR;
  __IO uint32_t DR;
  __IO uint32_t CRCPR;
  __IO uint32_t RXCRCR;
  __IO uint32_t TXCRCR;
  __IO uint32_t I2SCFGR;
  __IO uint32_t I2SPR;
} SPI_TypeDef;


/** 
  * @brief CMP
  */

typedef struct
{
  __IO uint32_t CR;         /*!< COMP control and status register, Address offset: 0x00 */
  uint32_t RESERVED0[15];
  __IO uint32_t CAL;
} COMP_TypeDef;


typedef struct
{
  __IO uint32_t C1CR;             /*!< CMP control register 1,   Address offset: 0x00 */
  __IO uint32_t C2CR;             /*!< CMP control register 2,   Address offset: 0x04 */
 uint32_t RESERVED0[14];    
  __IO uint32_t RG1CAL;             /*!< CMP calculation register, Address offset: 0x40 */  
	__IO uint32_t RG2CAL;             /*!< CMP calculation register, Address offset: 0x44 */  
 uint32_t RESERVED1[14];
	__IO uint32_t CR1;  	         /*!< CMP  register, Address offset: 0x80 */
  __IO uint32_t CR2;          	 /*!< CMP  register, Address offset: 0x84 */
} CMP_TypeDef;


/** 
  * @brief CRV
  */

typedef struct
{
  __IO uint32_t CR1;                 /*!< CRV control register 1,        Address offset: 0x00 */
  __IO uint32_t CH1VSEL;             /*!< CRV Select 1,                  Address offset: 0x04 */
  __IO uint32_t CH2VSEL;             /*!< CRV Select 2,                  Address offset: 0x08 */
  __IO uint32_t CH3VSEL;             /*!< CRV Select 3,                  Address offset: 0x0C */
  uint32_t RESERVED1;
  __IO uint32_t CH5VSEL;             /*!< CRV Select 5,                  Address offset: 0x014 */	
	__IO uint32_t VREAL;               /*!< CRV Real V,                    Address offset: 0x18 */
  __IO uint32_t TC;                  /*!< CRV Real V,                    Address offset: 0x1C */
	__IO uint32_t CR1SRN;                 /*!< CRV control register SRN,        Address offset: 0x20 */
} CRV_TypeDef;

/** 
  * @brief OPAMP
  */

typedef struct
{
  __IO uint32_t O1CSR;           /*!< OPAMP1 control/status register,        Address offset: 0x00 */
	__IO uint32_t O2CSR;           /*!< OPAMP2 control/status register,        Address offset: 0x04 */
	__IO uint32_t O3CSR;           /*!< OPAMP3 control/status register,        Address offset: 0x08 */
  __IO uint32_t O1BIAS;          /*!< OPAMP1 BIAS control register,          Address offset: 0x0C */
	__IO uint32_t O2BIAS;          /*!< OPAMP2 BIAS control register,          Address offset: 0x10 */
	__IO uint32_t O3BIAS;          /*!< OPAMP3 BIAS control register,          Address offset: 0x14 */
} OPA_TypeDef;




typedef struct
{
  __IO uint32_t CSR;           /*!< OPAMP control/status register,                     Address offset: 0x00 */
  __IO uint32_t RESERVED[2];   /*!< OPAMP offset trimming register for normal mode,    Address offset: 0x04 */
  __IO uint32_t BIAS;          /*!< OPAMP timer controlled mux mode register,          Address offset: 0x18 */
} OPAMP_TypeDef;

/**
  * @brief TIM Timers
  */
typedef struct
{
  __IO uint32_t CR1;             /*!< TIM control register 1,                      Address offset: 0x00 */
  __IO uint32_t CR2;             /*!< TIM control register 2,                      Address offset: 0x04 */
  __IO uint32_t SMCR;            /*!< TIM slave Mode Control register,             Address offset: 0x08 */
  __IO uint32_t DIER;            /*!< TIM interrupt enable register,               Address offset: 0x0C */
  __IO uint32_t SR;              /*!< TIM status register,                         Address offset: 0x10 */
  __IO uint32_t EGR;             /*!< TIM event generation register,               Address offset: 0x14 */
  __IO uint32_t CCMR1;           /*!< TIM  capture/compare mode register 1,        Address offset: 0x18 */
  __IO uint32_t CCMR2;           /*!< TIM  capture/compare mode register 2,        Address offset: 0x1C */
  __IO uint32_t CCER;            /*!< TIM capture/compare enable register,         Address offset: 0x20 */
  __IO uint32_t CNT;             /*!< TIM counter register,                        Address offset: 0x24 */
  __IO uint32_t PSC;             /*!< TIM prescaler register,                      Address offset: 0x28 */
  __IO uint32_t ARR;             /*!< TIM auto-reload register,                    Address offset: 0x2C */
  __IO uint32_t RCR;             /*!< TIM  repetition counter register,            Address offset: 0x30 */
  __IO uint32_t CCR1;            /*!< TIM capture/compare register 1,              Address offset: 0x34 */
  __IO uint32_t CCR2;            /*!< TIM capture/compare register 2,              Address offset: 0x38 */
  __IO uint32_t CCR3;            /*!< TIM capture/compare register 3,              Address offset: 0x3C */
  __IO uint32_t CCR4;            /*!< TIM capture/compare register 4,              Address offset: 0x40 */
  __IO uint32_t BDTR;            /*!< TIM break and dead-time register,            Address offset: 0x44 */
  __IO uint32_t CCR5;        /*!< TIM capture/compare register 5,           Address offset: 0x48 */
  __IO uint32_t CCR6;        /*!< TIM capture/compare register 6,           Address offset: 0x4C */
  __IO uint32_t CCMR3;       /*!< TIM capture/compare mode register 3,      Address offset: 0x50 */
  __IO uint32_t DTR2;        /*!< TIM deadtime register 2,                  Address offset: 0x54 */
  __IO uint32_t ECR;         /*!< TIM encoder control register,             Address offset: 0x58 */
  __IO uint32_t TISEL;       /*!< TIM Input Selection register,             Address offset: 0x5C */
  __IO uint32_t AF1;         /*!< TIM alternate function option register 1, Address offset: 0x60 */
  __IO uint32_t AF2;         /*!< TIM alternate function option register 2, Address offset: 0x64 */
  __IO uint32_t CCR1N ;      /*!< TIM capture/compare 1N register 1,        Address offset: 0x68 */
  __IO uint32_t CCR2N ;      /*!< TIM capture/compare 2N register 2,        Address offset: 0x6C */
  __IO uint32_t CCR3N ;      /*!< TIM capture/compare 3N register 3,        Address offset: 0x70 */
  __IO uint32_t CCR4N ;      /*!< TIM capture/compare 4N register 4,        Address offset: 0x74 */
  __IO uint32_t BIC   ;      /*!< TIM Break Input Control,                  Address offset: 0x78 */
  uint32_t RESERVED0[1];     /*!< Reserved,                                 Address offset: 0x7C */
  __IO uint32_t TRGI;        /*!< Slave syn,                                Address offset: 0x80 */
}TIM_TypeDef;


/** 
  * @brief Universal Synchronous Asynchronous Receiver Transmitter
  */
 
typedef struct
{
  __IO uint32_t SR;         /*!< UART Status register,                   Address offset: 0x00 */
  __IO uint32_t DR;         /*!< UART Data register,                     Address offset: 0x04 */
  __IO uint32_t BRR;        /*!< UART Baud rate register,                Address offset: 0x08 */
  __IO uint32_t CR1;        /*!< UART Control register 1,                Address offset: 0x0C */
  __IO uint32_t CR2;        /*!< UART Control register 2,                Address offset: 0x10 */
  __IO uint32_t CR3;        /*!< UART Control register 3,                Address offset: 0x14 */
} UART_TypeDef;

/** 
  * @brief SQRT
  */
 
typedef struct
{
  __IO uint32_t CR;         /*!< Address offset: 0x00 */
	__IO uint32_t ARG1;         /*!< Address offset: 0x04 */
	__IO uint32_t ARG2;         /*!< Address offset: 0x08 */
	__IO uint32_t RSVD[3];
	__IO uint32_t MCYC;        /*!< Address offset: 0x10 */
} ME_TypeDef;

/**
  * @}
  */
  
/** @addtogroup Peripheral_memory_map
  * @{
  */


#define FLASH_BASE            0x08000000U /*!< FLASH base address in the alias region */
#define FLASH_BANK1_END       0x0800FFFFU /*!< FLASH END address of bank1 */
#define SRAM_BASE             0x20000000U /*!< SRAM base address in the alias region */
#define PERIPH_BASE           0x40000000U /*!< Peripheral base address in the alias region */

#define SRAM_BB_BASE          0x22000000U /*!< SRAM base address in the bit-band region */
#define PERIPH_BB_BASE        0x42000000U /*!< Peripheral base address in the bit-band region */


/*!< Peripheral memory map */
#define APB1PERIPH_BASE       PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000U)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x00020000U)

#define TIM2_BASE             (APB1PERIPH_BASE + 0x00000000U)
#define TIM3_BASE             (APB1PERIPH_BASE + 0x00000400U)
#define TIM6_BASE             (APB1PERIPH_BASE + 0x00001000U)
#define TIM7_BASE             (APB1PERIPH_BASE + 0x00001400U)
#define RTC_BASE              (APB1PERIPH_BASE + 0x00002800U)
#define BKP_BASE              (APB1PERIPH_BASE + 0x00006C00U)
#define IWDG_BASE             (APB1PERIPH_BASE + 0x00003000U)
#define UART2_BASE            (APB1PERIPH_BASE + 0x00004400U)
#define I2C1_BASE             (APB1PERIPH_BASE + 0x00005400U)
#define CAN1_BASE             (APB1PERIPH_BASE + 0x00006400U)
#define PWR_BASE              (APB1PERIPH_BASE + 0x00007000U)

#define SYSCFG_BASE           (APB2PERIPH_BASE + 0x00000000U)
#define VREFBUF_BASE          (APB2PERIPH_BASE + 0x00000030U)
#define COMP1_BASE            (APB2PERIPH_BASE + 0x00000200U)
#define COMP2_BASE            (APB2PERIPH_BASE + 0x00000204U)
#define OPAMP_BASE            (APB2PERIPH_BASE + 0x00000300U)
#define OPAMP1_BASE           (APB2PERIPH_BASE + 0x00000300U)
#define OPAMP2_BASE           (APB2PERIPH_BASE + 0x00000304U)
#define OPAMP3_BASE           (APB2PERIPH_BASE + 0x00000308U)
#define EXTI_BASE             (APB2PERIPH_BASE + 0x00000400U)
#define SPI1_BASE             (APB2PERIPH_BASE + 0x00003000U)
#define TIM8_BASE             (APB2PERIPH_BASE + 0x00003400U)
#define UART1_BASE            (APB2PERIPH_BASE + 0x00003800U)
#define TIM15_BASE            (APB2PERIPH_BASE + 0x00004000U)

#define RCC_BASE              (AHBPERIPH_BASE + 0x00001000U)
#define FLASH_R_BASE          (AHBPERIPH_BASE + 0x00002000U) 
#define CRC_BASE              (AHBPERIPH_BASE + 0x00003000U)
#define ME_BASE               (AHBPERIPH_BASE + 0x00005000U)


#define GPIOA_BASE            (PERIPH_BASE + 0x08000000U)
#define GPIOB_BASE            (PERIPH_BASE + 0x08000400U)
#define GPIOC_BASE            (PERIPH_BASE + 0x08000800U)
#define GPIOD_BASE            (PERIPH_BASE + 0x08000C00U)

#define ADC1_BASE             (PERIPH_BASE + 0x09000000U)

#define FLASHSIZE_BASE        0x1FFFF7E0U    /*!< FLASH Size register base address */
#define UID_BASE              0x1FFFF7E8U    /*!< Unique device ID register base address */
#define OB_BASE               0x1FFFF800U    /*!< Flash Option Bytes base address */



#define DBGMCU_BASE          0xE0042000U /*!< Debug MCU registers base address */


/**
  * @}
  */
  
/** @addtogroup Peripheral_declaration
  * @{
  */  

#define TIM2                ((TIM_TypeDef *)TIM2_BASE)
#define TIM3                ((TIM_TypeDef *)TIM3_BASE)
#define TIM6                ((TIM_TypeDef *)TIM6_BASE)
#define TIM7                ((TIM_TypeDef *)TIM7_BASE)
#define RTC                 ((RTC_TypeDef *)RTC_BASE)
#define IWDG                ((IWDG_TypeDef *)IWDG_BASE)
#define UART2               ((UART_TypeDef *)UART2_BASE)
#define I2C1                ((I2C_TypeDef *)I2C1_BASE)
#define CAN1                ((CAN_TypeDef *)CAN1_BASE)
#define BKP                 ((BKP_TypeDef *)BKP_BASE)
#define PWR                 ((PWR_TypeDef *)PWR_BASE)

#define SYSCFG              ((SYSCFG_TypeDef *)SYSCFG_BASE)
#define VREFBUF             ((VREFBUF_TypeDef *)VREFBUF_BASE)
#define COMP1               ((COMP_TypeDef *)COMP1_BASE)
#define COMP2               ((COMP_TypeDef *)COMP2_BASE)
#define COMP                 ((CMP_TypeDef *)COMP1_BASE)
#define OPAMP               ((OPA_TypeDef *) OPAMP_BASE)
#define OPAMP1              ((OPAMP_TypeDef *) OPAMP1_BASE)
#define OPAMP2              ((OPAMP_TypeDef *) OPAMP2_BASE)
#define OPAMP3              ((OPAMP_TypeDef *) OPAMP3_BASE)
#define EXTI                ((EXTI_TypeDef *)EXTI_BASE)
#define SPI1                ((SPI_TypeDef *)SPI1_BASE)
#define TIM8                ((TIM_TypeDef *)TIM8_BASE)
#define UART1               ((UART_TypeDef *)UART1_BASE)
#define TIM15               ((TIM_TypeDef *)TIM15_BASE)

#define RCC                 ((RCC_TypeDef *)RCC_BASE)
#define FLASH               ((FLASH_TypeDef *)FLASH_R_BASE)
#define CRC                 ((CRC_TypeDef *)CRC_BASE)
#define ME                  ((ME_TypeDef *)ME_BASE)
#define GPIOA               ((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *)GPIOD_BASE)

#define ADC1                ((ADC_TypeDef *)ADC1_BASE)

#define OB                  ((OB_TypeDef *)OB_BASE)
#define DBGMCU              ((DBGMCU_TypeDef *)DBGMCU_BASE)

/**
  * @}
*/ 

/** @addtogroup Exported_macro
  * @{
  */

/****************************** ADC Instances *********************************/
#define IS_ADC_MULTIMODE_MASTER_INSTANCE(INSTANCE) ((INSTANCE) == ADC1)

/****************************** CRC Instances *********************************/
#define IS_CRC_ALL_INSTANCE(INSTANCE) ((INSTANCE) == CRC)
  
/******************************* GPIO Instances *******************************/
#define IS_GPIO_ALL_INSTANCE(INSTANCE) (((INSTANCE) == GPIOA) || \
                                        ((INSTANCE) == GPIOB) || \
                                        ((INSTANCE) == GPIOC) || \
                                        ((INSTANCE) == GPIOD) )

/**************************** GPIO Alternate Function Instances ***************/
#define IS_GPIO_AF_INSTANCE(INSTANCE) IS_GPIO_ALL_INSTANCE(INSTANCE)

/**************************** GPIO Lock Instances *****************************/
#define IS_GPIO_LOCK_INSTANCE(INSTANCE) IS_GPIO_ALL_INSTANCE(INSTANCE)

/******************************** I2C Instances *******************************/
#define IS_I2C_ALL_INSTANCE(INSTANCE) ((INSTANCE) == I2C1)

/******************************* SMBUS Instances ******************************/
#define IS_SMBUS_ALL_INSTANCE         IS_I2C_ALL_INSTANCE

/****************************** IWDG Instances ********************************/
#define IS_IWDG_ALL_INSTANCE(INSTANCE)  ((INSTANCE) == IWDG)

/******************************** SPI Instances *******************************/
#define IS_SPI_ALL_INSTANCE(INSTANCE) ((INSTANCE) == SPI1)

/****************************** START TIM Instances ***************************/
/****************** TIM Instances : All supported instances *******************/
#define IS_TIM_INSTANCE(INSTANCE)       (((INSTANCE) == TIM2)   || \
                                         ((INSTANCE) == TIM3)   || \
                                         ((INSTANCE) == TIM6)   || \
                                         ((INSTANCE) == TIM7)   || \
                                         ((INSTANCE) == TIM8)   || \
                                         ((INSTANCE) == TIM15))

/****************** TIM Instances : supporting 32 bits counter ****************/

#define IS_TIM_32B_COUNTER_INSTANCE(INSTANCE) (((INSTANCE) == TIM2))

/****************** TIM Instances : supporting the break function *************/
#define IS_TIM_BREAK_INSTANCE(INSTANCE)    (((INSTANCE) == TIM8)    || \
                                            ((INSTANCE) == TIM15))

/************** TIM Instances : supporting Break source selection *************/
#define IS_TIM_BREAKSOURCE_INSTANCE(INSTANCE) (((INSTANCE) == TIM8)   || \
                                               ((INSTANCE) == TIM15))

/****************** TIM Instances : supporting 2 break inputs *****************/
#define IS_TIM_BKIN2_INSTANCE(INSTANCE)    (((INSTANCE) == TIM8))

/************* TIM Instances : at least 1 capture/compare channel *************/
#define IS_TIM_CC1_INSTANCE(INSTANCE)   (((INSTANCE) == TIM2)   || \
                                         ((INSTANCE) == TIM3)   || \
                                         ((INSTANCE) == TIM8)   || \
                                         ((INSTANCE) == TIM15))

/************ TIM Instances : at least 2 capture/compare channels *************/
#define IS_TIM_CC2_INSTANCE(INSTANCE)   (((INSTANCE) == TIM2)   || \
                                         ((INSTANCE) == TIM3)   || \
                                         ((INSTANCE) == TIM8)   || \
                                         ((INSTANCE) == TIM15))

/************ TIM Instances : at least 3 capture/compare channels *************/
#define IS_TIM_CC3_INSTANCE(INSTANCE)   (((INSTANCE) == TIM2)   || \
                                         ((INSTANCE) == TIM3)   || \
                                         ((INSTANCE) == TIM8))

/************ TIM Instances : at least 4 capture/compare channels *************/
#define IS_TIM_CC4_INSTANCE(INSTANCE)   (((INSTANCE) == TIM2)   || \
                                         ((INSTANCE) == TIM3)   || \
                                         ((INSTANCE) == TIM8))

/****************** TIM Instances : at least 5 capture/compare channels *******/
#define IS_TIM_CC5_INSTANCE(INSTANCE)   (((INSTANCE) == TIM8))

/****************** TIM Instances : at least 6 capture/compare channels *******/
#define IS_TIM_CC6_INSTANCE(INSTANCE)   (((INSTANCE) == TIM8))

/******************* TIM Instances : output(s) available **********************/
#define IS_TIM_CCX_INSTANCE(INSTANCE, CHANNEL) \
     (((INSTANCE) == TIM2) &&                  \
     (((CHANNEL) == TIM_CHANNEL_1) ||          \
      ((CHANNEL) == TIM_CHANNEL_2) ||          \
      ((CHANNEL) == TIM_CHANNEL_3) ||          \
      ((CHANNEL) == TIM_CHANNEL_4)))           \
     ||                                        \
     (((INSTANCE) == TIM3) &&                  \
     (((CHANNEL) == TIM_CHANNEL_1) ||          \
      ((CHANNEL) == TIM_CHANNEL_2) ||          \
      ((CHANNEL) == TIM_CHANNEL_3) ||          \
      ((CHANNEL) == TIM_CHANNEL_4)))           \
     ||                                        \
     (((INSTANCE) == TIM8) &&                  \
     (((CHANNEL) == TIM_CHANNEL_1) ||          \
      ((CHANNEL) == TIM_CHANNEL_2) ||          \
      ((CHANNEL) == TIM_CHANNEL_3) ||          \
      ((CHANNEL) == TIM_CHANNEL_4) ||          \
      ((CHANNEL) == TIM_CHANNEL_5) ||          \
      ((CHANNEL) == TIM_CHANNEL_6)))           \
     ||                                        \
     (((INSTANCE) == TIM15) &&                 \
     (((CHANNEL) == TIM_CHANNEL_1) ||          \
      ((CHANNEL) == TIM_CHANNEL_2))))

/****************** TIM Instances : supporting complementary output(s) ********/
#define IS_TIM_CCXN_INSTANCE(INSTANCE, CHANNEL) \
    (((INSTANCE) == TIM8) &&                    \
     (((CHANNEL) == TIM_CHANNEL_1) ||           \
      ((CHANNEL) == TIM_CHANNEL_2) ||           \
      ((CHANNEL) == TIM_CHANNEL_3) ||           \
      ((CHANNEL) == TIM_CHANNEL_4)))            \
    ||                                          \
    (((INSTANCE) == TIM15) &&                   \
     ((CHANNEL) == TIM_CHANNEL_1)))

/****************** TIM Instances : supporting clock division *****************/
#define IS_TIM_CLOCK_DIVISION_INSTANCE(INSTANCE)   (((INSTANCE) == TIM2)    || \
                                                    ((INSTANCE) == TIM3)    || \
                                                    ((INSTANCE) == TIM8)    || \
                                                    ((INSTANCE) == TIM15))

/****** TIM Instances : supporting external clock mode 1 for ETRF input *******/
#define IS_TIM_CLOCKSOURCE_ETRMODE1_INSTANCE(INSTANCE) (((INSTANCE) == TIM2) || \
                                                        ((INSTANCE) == TIM3) || \
                                                        ((INSTANCE) == TIM8))

/****** TIM Instances : supporting external clock mode 2 for ETRF input *******/
#define IS_TIM_CLOCKSOURCE_ETRMODE2_INSTANCE(INSTANCE) (((INSTANCE) == TIM2) || \
                                                        ((INSTANCE) == TIM3) || \
                                                        ((INSTANCE) == TIM8))

/****************** TIM Instances : supporting external clock mode 1 for TIX inputs*/
#define IS_TIM_CLOCKSOURCE_TIX_INSTANCE(INSTANCE)      (((INSTANCE) == TIM2) || \
                                                        ((INSTANCE) == TIM3) || \
                                                        ((INSTANCE) == TIM8) || \
                                                        ((INSTANCE) == TIM15))

/****************** TIM Instances : supporting internal trigger inputs(ITRX) *******/
#define IS_TIM_CLOCKSOURCE_ITRX_INSTANCE(INSTANCE)     (((INSTANCE) == TIM2) || \
                                                        ((INSTANCE) == TIM3) || \
                                                        ((INSTANCE) == TIM8) || \
                                                        ((INSTANCE) == TIM15))

/****************** TIM Instances : supporting combined 3-phase PWM mode ******/
#define IS_TIM_COMBINED3PHASEPWM_INSTANCE(INSTANCE) (((INSTANCE) == TIM8))

/****************** TIM Instances : supporting commutation event generation ***/
#define IS_TIM_COMMUTATION_EVENT_INSTANCE(INSTANCE) (((INSTANCE) == TIM8)   || \
                                                     ((INSTANCE) == TIM15))

/****************** TIM Instances : supporting counting mode selection ********/
#define IS_TIM_COUNTER_MODE_SELECT_INSTANCE(INSTANCE)  (((INSTANCE) == TIM2) || \
                                                        ((INSTANCE) == TIM3) || \
                                                        ((INSTANCE) == TIM8))

/****************** TIM Instances : supporting encoder interface **************/
#define IS_TIM_ENCODER_INTERFACE_INSTANCE(INSTANCE)  (((INSTANCE) == TIM2)  || \
                                                      ((INSTANCE) == TIM3)  || \
                                                      ((INSTANCE) == TIM8))

/****************** TIM Instances : supporting Hall sensor interface **********/
#define IS_TIM_HALL_SENSOR_INTERFACE_INSTANCE(INSTANCE) (((INSTANCE) == TIM2)   || \
                                                         ((INSTANCE) == TIM3)   || \
                                                         ((INSTANCE) == TIM8)   || \
                                                         ((INSTANCE) == TIM15))

/**************** TIM Instances : external trigger input available ************/
#define IS_TIM_ETR_INSTANCE(INSTANCE)      (((INSTANCE) == TIM2)  || \
                                            ((INSTANCE) == TIM3)  || \
                                            ((INSTANCE) == TIM8))

/************* TIM Instances : supporting ETR source selection ***************/
#define IS_TIM_ETRSEL_INSTANCE(INSTANCE)    (((INSTANCE) == TIM2)  || \
                                             ((INSTANCE) == TIM3)  || \
                                             ((INSTANCE) == TIM8))

/****** TIM Instances : Master mode available (TIMx_CR2.MMS available )********/
#define IS_TIM_MASTER_INSTANCE(INSTANCE)   (((INSTANCE) == TIM2)  || \
                                            ((INSTANCE) == TIM3)  || \
                                            ((INSTANCE) == TIM6)  || \
                                            ((INSTANCE) == TIM7)  || \
                                            ((INSTANCE) == TIM8)  || \
                                            ((INSTANCE) == TIM15))

/*********** TIM Instances : Slave mode available (TIMx_SMCR available )*******/
#define IS_TIM_SLAVE_INSTANCE(INSTANCE)    (((INSTANCE) == TIM2)  || \
                                            ((INSTANCE) == TIM3)  || \
                                            ((INSTANCE) == TIM8)  || \
                                            ((INSTANCE) == TIM15))

/****************** TIM Instances : supporting OCxREF clear *******************/
#define IS_TIM_OCXREF_CLEAR_INSTANCE(INSTANCE)        (((INSTANCE) == TIM2)  || \
                                                       ((INSTANCE) == TIM3)  || \
                                                       ((INSTANCE) == TIM8)  || \
                                                       ((INSTANCE) == TIM15))

/****************** TIM Instances : supporting bitfield OCCS in SMCR register *******************/
#define IS_TIM_OCCS_INSTANCE(INSTANCE)                (((INSTANCE) == TIM2)  || \
                                                       ((INSTANCE) == TIM3)  || \
                                                       ((INSTANCE) == TIM8)  || \
                                                       ((INSTANCE) == TIM15))

/****************** TIM Instances : remapping capability **********************/
#define IS_TIM_REMAP_INSTANCE(INSTANCE)    (((INSTANCE) == TIM2)  || \
                                            ((INSTANCE) == TIM3)  || \
                                            ((INSTANCE) == TIM8))

/****************** TIM Instances : supporting repetition counter *************/
#define IS_TIM_REPETITION_COUNTER_INSTANCE(INSTANCE)  (((INSTANCE) == TIM8)  || \
                                                       ((INSTANCE) == TIM15))

/****************** TIM Instances : supporting ADC triggering through TRGO2 ***/
#define IS_TIM_TRGO2_INSTANCE(INSTANCE)    (((INSTANCE) == TIM8))

/******************* TIM Instances : Timer input XOR function *****************/
#define IS_TIM_XOR_INSTANCE(INSTANCE)      (((INSTANCE) == TIM2)   || \
                                            ((INSTANCE) == TIM3)   || \
                                            ((INSTANCE) == TIM8)   || \
                                            ((INSTANCE) == TIM15))

/******************* TIM Instances : Timer input selection ********************/
#define IS_TIM_TISEL_INSTANCE(INSTANCE) (((INSTANCE) == TIM2)   || \
                                         ((INSTANCE) == TIM3)   || \
                                         ((INSTANCE) == TIM8)   || \
                                         ((INSTANCE) == TIM15))

/****************** TIM Instances : Advanced timer instances *******************/
#define IS_TIM_ADVANCED_INSTANCE(INSTANCE)       (((INSTANCE) == TIM8))



/****************************** END TIM Instances *****************************/


/******************** UART Instances : Asynchronous mode **********************/
#define IS_UART_INSTANCE(INSTANCE) (((INSTANCE) == UART1) || \
                                    ((INSTANCE) == UART2) || \
                                    ((INSTANCE) == UART3))

/******************** UART Instances : Half-Duplex mode **********************/
#define IS_UART_HALFDUPLEX_INSTANCE(INSTANCE) (((INSTANCE) == UART1) || \
                                               ((INSTANCE) == UART2) || \
                                               ((INSTANCE) == UART3))

/******************** UART Instances : LIN mode **********************/
#define IS_UART_LIN_INSTANCE(INSTANCE) (((INSTANCE) == UART1) || \
                                        ((INSTANCE) == UART2) || \
                                        ((INSTANCE) == UART3))

/****************** UART Instances : Hardware Flow control ********************/                                    
#define IS_UART_HWFLOW_INSTANCE(INSTANCE) (((INSTANCE) == UART1) || \
                                           ((INSTANCE) == UART2) || \
                                           ((INSTANCE) == UART3))

/********************* UART Instances : Smard card mode ***********************/
#define IS_SMARTCARD_INSTANCE(INSTANCE) (((INSTANCE) == UART1) || \
                                         ((INSTANCE) == UART2) || \
                                         ((INSTANCE) == UART3))

/*********************** UART Instances : IRDA mode ***************************/
#define IS_IRDA_INSTANCE(INSTANCE) (((INSTANCE) == UART1) || \
                                    ((INSTANCE) == UART2) || \
                                    ((INSTANCE) == UART3))

/***************** UART Instances : Multi-Processor mode **********************/
#define IS_UART_MULTIPROCESSOR_INSTANCE(INSTANCE) (((INSTANCE) == UART1) || \
                                                   ((INSTANCE) == UART2) || \
                                                   ((INSTANCE) == UART3))

/****************************** RTC Instances *********************************/
#define IS_RTC_ALL_INSTANCE(INSTANCE)  ((INSTANCE) == RTC)



#define RCC_HSI_MIN         4000000U
#define RCC_HSI_MAX        16000000U

#define RCC_MAX_FREQUENCY  72000000U

/**
  * @}
  */ 
/******************************************************************************/
/*  For a painless codes migration between the RX32H6xx device product       */
/*  lines, the aliases defined below are put in place to overcome the         */
/*  differences in the interrupt handlers and IRQn definitions.               */
/*  No need to update developed interrupt code when moving across             */ 
/*  product lines within the same RX32H6 Family                              */
/******************************************************************************/


/**
  * @}
  */

/**
  * @}
  */


#ifdef __cplusplus
  }
#endif /* __cplusplus */
  
#endif
  

