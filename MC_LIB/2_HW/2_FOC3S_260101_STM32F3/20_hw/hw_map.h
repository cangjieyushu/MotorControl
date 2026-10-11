/*
*     File Name :                        hw_map
*     Library/Module Name :              hw
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             引脚、外设、中断映射
*/

#ifndef HW_MAP_H
#define HW_MAP_H


/*-------------------------- 1. 头文件包含 -------------------------------*/
#include "stm32f30x.h"
#include "stm32f30x_adc.h"
#include "stm32f30x_comp.h"
#include "stm32f30x_dac.h"
#include "stm32f30x_dma.h"
#include "stm32f30x_exti.h"
#include "stm32f30x_flash.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_opamp.h"
#include "stm32f30x_pwr.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_syscfg.h"
#include "stm32f30x_tim.h"
#include "stm32f30x_usart.h"
#include "stm32f30x_spi.h"
#include "stm32f30x_wwdg.h"


/*-------------------------- 2. 外设重定义 -------------------------------*/
#define HAL_MOTOR_ADC1              ADC1
#define HAL_MOTOR_ADC2              ADC2
#define HAL_MOTOR_ADC3              ADC3
#define HAL_MOTOR_PWM               TIM8
#define HAL_MOTOR_HALL_TIM          TIM2
#define HAL_HMI_UART                USART1
#define HAL_HMI_SPI                 SPI3

/* DMA */
#define HAL_ADC_DMA_CHANNEL         DMA1_Channel1

/* DAC */
#define HAL_DAC                     DAC1
#define HAL_DAC_VH_CHANNEL          DAC_Channel_1
#define HAL_DAC_VL_CHANNEL          DAC_Channel_2

/* OPAMP */
#define HAL_OPAMP1                  OPAMP_Selection_OPAMP1
#define HAL_OPAMP2                  OPAMP_Selection_OPAMP2
#define HAL_OPAMP3                  OPAMP_Selection_OPAMP3

/* ADC 注入 Rank */
#define HAL_ADC_INJ_RANK1           1
#define HAL_ADC_INJ_RANK2           2
#define HAL_ADC_INJ_RANK3           3
#define HAL_ADC_INJ_RANK4           4

/* ADC 规则 Rank */
#define HAL_ADC_REG_RANK1           1
#define HAL_ADC_REG_RANK2           2

/* ================== UART（HAL 层外设实例） ================== */
/* USART1 的 DMA 通道映射（F303 固定）*/
#define HAL_HMI_USART_TX_DMA_CH         DMA1_Channel4
#define HAL_HMI_USART_RX_DMA_CH         DMA1_Channel5

/* USART1 TX 完成标志 / 全部标志 */
#define HAL_HMI_USART_TX_DMA_TC_FLAG    DMA1_FLAG_TC4
#define HAL_HMI_USART_TX_DMA_GL_FLAG    DMA1_FLAG_GL4
#define HAL_HMI_USART_RX_DMA_TC_FLAG    DMA1_FLAG_TC5
#define HAL_HMI_USART_RX_DMA_GL_FLAG    DMA1_FLAG_GL5


/*-------------------------- 3. GPIO 输入 --------------------------------*/
#define START_GPIO_PORT             GPIOC
#define START_Pin                   GPIO_Pin_9
#define START_Pin_Source            GPIO_PinSource9

#define STOP_GPIO_PORT              GPIOA
#define STOP_Pin                    GPIO_Pin_8
#define STOP_Pin_Source             GPIO_PinSource8


/*-------------------------- 4. GPIO 输出 --------------------------------*/
#define RED_GPIO_PORT               GPIOB
#define RED_Pin                     GPIO_Pin_7

#define YEW_GPIO_PORT               GPIOB
#define YEW_Pin                     GPIO_Pin_8

#define GRE_GPIO_PORT               GPIOB
#define GRE_Pin                     GPIO_Pin_9

#define TEST1_GPIO_PORT             GPIOC
#define TEST1_Pin                   GPIO_Pin_0

#define TEST2_GPIO_PORT             GPIOC
#define TEST2_Pin                   GPIO_Pin_1


/*-------------------------- 5. ADC 三相电流 -----------------------------*/
/* U 相电流：PA2 -> ADC1_IN3 */
#define ADC_U_CURRENT_GPIO_Port     GPIOA
#define ADC_U_CURRENT_Pin           GPIO_Pin_2
#define ADC_U_CURRENT_Pin_Source    GPIO_PinSource2
#define ADC_U_CURRENT_Channel       ADC_Channel_3
#define ADC_U_CURRENT_ADC           HAL_MOTOR_ADC1

/* V 相电流：PA6 -> ADC2_IN3 */
#define ADC_V_CURRENT_GPIO_Port     GPIOA
#define ADC_V_CURRENT_Pin           GPIO_Pin_6
#define ADC_V_CURRENT_Pin_Source    GPIO_PinSource6
#define ADC_V_CURRENT_Channel       ADC_Channel_3
#define ADC_V_CURRENT_ADC           HAL_MOTOR_ADC2

/* W 相电流：PB13 -> ADC3_IN5 */
#define ADC_W_CURRENT_GPIO_Port     GPIOB
#define ADC_W_CURRENT_Pin           GPIO_Pin_13
#define ADC_W_CURRENT_Pin_Source    GPIO_PinSource13
#define ADC_W_CURRENT_Channel       ADC_Channel_5
#define ADC_W_CURRENT_ADC           HAL_MOTOR_ADC3


/*-------------------------- 6. ADC 系统（母线电压 + 外部温度） ----------*/
/* 母线电压：PC3 -> ADC1_IN9（也可用 ADC2_IN9） */
#define ADC_VBUS_GPIO_Port          GPIOC
#define ADC_VBUS_Pin                GPIO_Pin_3
#define ADC_VBUS_Pin_Source         GPIO_PinSource3
#define ADC_VBUS_Channel            ADC_Channel_9
#define ADC_VBUS_ADC                HAL_MOTOR_ADC1

/* 外部温度：PC2 -> ADC1_IN8（也可用 ADC2_IN8） */
#define ADC_TEMP_GPIO_Port          GPIOC
#define ADC_TEMP_Pin                GPIO_Pin_2
#define ADC_TEMP_Pin_Source         GPIO_PinSource2
#define ADC_TEMP_Channel            ADC_Channel_8
#define ADC_TEMP_ADC                HAL_MOTOR_ADC1


/*-------------------------- 7. OPA 运算放大器 --------------------------*/
/* OPA 输出引脚（配置为模拟模式，通过 OPAMP_Cmd 使能）
 * 注意：PA2/PC5/PB1 输出后通过外部走线送到主比较器 P 端 */
#define HAL_OPA1_GPIO_Port          GPIOA
#define HAL_OPA1_Pin                GPIO_Pin_2      /* OPA1_VOUT = PA2 */

#define HAL_OPA2_GPIO_Port          GPIOC
#define HAL_OPA2_Pin                GPIO_Pin_5      /* OPA2_VOUT = PC5 */

#define HAL_OPA3_GPIO_Port          GPIOB
#define HAL_OPA3_Pin                GPIO_Pin_1      /* OPA3_VOUT = PB1 */

/* OPA 同相输入引脚 —— 三路独立信号 */
#define HAL_OPA1_VINP_GPIO_Port     GPIOA
#define HAL_OPA1_VINP_Pin           GPIO_Pin_3      /* OPAMP1 IO3 = PA3 */
#define HAL_OPA1_VINP_IO            OPAMP_NonInvertingInput_IO3

#define HAL_OPA2_VINP_GPIO_Port     GPIOB
#define HAL_OPA2_VINP_Pin           GPIO_Pin_0      /* OPAMP2 IO3 = PB0 */
#define HAL_OPA2_VINP_IO            OPAMP_NonInvertingInput_IO3

#define HAL_OPA3_VINP_GPIO_Port     GPIOA
#define HAL_OPA3_VINP_Pin           GPIO_Pin_1      /* OPAMP3 IO3 = PA1 */
#define HAL_OPA3_VINP_IO            OPAMP_NonInvertingInput_IO3


/*-------------------------- 8. CMP 过流保护 ----------------------------*/
/* 三组窗口比较器：CMP1+CMP2、CMP3+CMP4、CMP5+CMP6
 * 负端：DAC1_OUT1(PA4) 作上限、DAC1_OUT2(PA5) 作下限
 * 主比较器（1/3/5）非反相；从比较器（2/4/6）反相
 * 从比较器 P 端由 COMP_WindowCmd() 自动共用主比较器 P 端 */

/* -------- 组 1：主 CMP1，P 端 = PA1 -------- */
#define HAL_OCP_COMP1                   COMP_Selection_COMP1
#define HAL_OCP_COMP1_INVERT            COMP_InvertingInput_DAC1OUT1
#define HAL_OCP_COMP1_NONINVERT         COMP_NonInvertingInput_IO1
#define HAL_OCP_COMP1_OUTPUT            COMP_Output_TIM8BKIN
#define HAL_OCP_COMP1_OUTPUTPOL         COMP_OutputPol_NonInverted
#define HAL_OCP_COMP1_GPIO_Port         GPIOA
#define HAL_OCP_COMP1_Pin               GPIO_Pin_1

/* -------- 组 1：从 CMP2（P 端由窗口模式共用，极性反转） -------- */
#define HAL_OCP_COMP2                   COMP_Selection_COMP2
#define HAL_OCP_COMP2_INVERT            COMP_InvertingInput_DAC1OUT2
#define HAL_OCP_COMP2_OUTPUT            COMP_Output_TIM8BKIN
#define HAL_OCP_COMP2_OUTPUTPOL         COMP_OutputPol_Inverted

/* -------- 组 2：主 CMP3，P 端 = PB14 -------- */
#define HAL_OCP_COMP3                   COMP_Selection_COMP3
#define HAL_OCP_COMP3_INVERT            COMP_InvertingInput_DAC1OUT1
#define HAL_OCP_COMP3_NONINVERT         COMP_NonInvertingInput_IO1
#define HAL_OCP_COMP3_OUTPUT            COMP_Output_TIM8BKIN
#define HAL_OCP_COMP3_OUTPUTPOL         COMP_OutputPol_NonInverted
#define HAL_OCP_COMP3_GPIO_Port         GPIOB
#define HAL_OCP_COMP3_Pin               GPIO_Pin_14

/* -------- 组 2：从 CMP4 -------- */
#define HAL_OCP_COMP4                   COMP_Selection_COMP4
#define HAL_OCP_COMP4_INVERT            COMP_InvertingInput_DAC1OUT2
#define HAL_OCP_COMP4_OUTPUT            COMP_Output_TIM8BKIN
#define HAL_OCP_COMP4_OUTPUTPOL         COMP_OutputPol_Inverted

/* -------- 组 3：主 CMP5，P 端 = PB13（与 W 相电流复用，硬件允许） -------- */
#define HAL_OCP_COMP5                   COMP_Selection_COMP5
#define HAL_OCP_COMP5_INVERT            COMP_InvertingInput_DAC1OUT1
#define HAL_OCP_COMP5_NONINVERT         COMP_NonInvertingInput_IO2
#define HAL_OCP_COMP5_OUTPUT            COMP_Output_TIM8BKIN
#define HAL_OCP_COMP5_OUTPUTPOL         COMP_OutputPol_NonInverted
#define HAL_OCP_COMP5_GPIO_Port         GPIOB
#define HAL_OCP_COMP5_Pin               GPIO_Pin_13

/* -------- 组 3：从 CMP6 -------- */
#define HAL_OCP_COMP6                   COMP_Selection_COMP6
#define HAL_OCP_COMP6_INVERT            COMP_InvertingInput_DAC1OUT2
#define HAL_OCP_COMP6_OUTPUT            COMP_Output_TIM8BKIN
#define HAL_OCP_COMP6_OUTPUTPOL         COMP_OutputPol_Inverted


/*-------------------------- 9. DAC 阈值输出 ----------------------------*/
#define HAL_DAC_VH_GPIO_Port        GPIOA
#define HAL_DAC_VH_Pin              GPIO_Pin_4      /* DAC1_OUT1 = PA4 */
#define HAL_DAC_VH_Pin_Source       GPIO_PinSource4
#define HAL_DAC_VH_Channel          DAC_Channel_1

#define HAL_DAC_VL_GPIO_Port        GPIOA
#define HAL_DAC_VL_Pin              GPIO_Pin_5      /* DAC1_OUT2 = PA5 */
#define HAL_DAC_VL_Pin_Source       GPIO_PinSource5
#define HAL_DAC_VL_Channel          DAC_Channel_2


/*-------------------------- 10. PWM（TIM8 互补输出） -------------------*/
#define UH_PWM_GPIO_Port            GPIOC
#define UH_PWM_Pin                  GPIO_Pin_6
#define UH_PWM_Pin_Source           GPIO_PinSource6

#define VH_PWM_GPIO_Port            GPIOC
#define VH_PWM_Pin                  GPIO_Pin_7
#define VH_PWM_Pin_Source           GPIO_PinSource7

#define WH_PWM_GPIO_Port            GPIOC
#define WH_PWM_Pin                  GPIO_Pin_8
#define WH_PWM_Pin_Source           GPIO_PinSource8

#define UL_PWM_GPIO_Port            GPIOB
#define UL_PWM_Pin                  GPIO_Pin_3
#define UL_PWM_Pin_Source           GPIO_PinSource3

#define VL_PWM_GPIO_Port            GPIOB
#define VL_PWM_Pin                  GPIO_Pin_4
#define VL_PWM_Pin_Source           GPIO_PinSource4

#define WL_PWM_GPIO_Port            GPIOB
#define WL_PWM_Pin                  GPIO_Pin_5
#define WL_PWM_Pin_Source           GPIO_PinSource5

/* TIM8_CH4 用于 ADC 触发（需占用 PC9，或改为内部 Update 事件） */
#define ADC_TRIGGER_CHANNEL         TIM_Channel_4


/*-------------------------- 11. UART（USART1） -------------------------*/
#define UART_TX_PORT                GPIOA
#define UART_TX_Pin                 GPIO_Pin_9
#define UART_TX_Pin_Source          GPIO_PinSource9

#define UART_RX_PORT                GPIOA
#define UART_RX_Pin                 GPIO_Pin_10
#define UART_RX_Pin_Source          GPIO_PinSource10

#define UART_EN_PORT                GPIOA     /* RS485 方向控制（GPIO 输出） */
#define UART_EN_Pin                 GPIO_Pin_11

#define UART_TX_Pin_Source          GPIO_PinSource9
#define UART_RX_Pin_Source          GPIO_PinSource10

/*-------------------------- 12. SPI（SPI3） ----------------------------*/
#define SPI_NSS_PORT                GPIOA     /* 也可用硬件 NSS 之外的 GPIO 控制 */
#define SPI_NSS_Pin                 GPIO_Pin_15
#define SPI_NSS_Pin_Source          GPIO_PinSource15

#define SPI_SCK_PORT                GPIOC
#define SPI_SCK_Pin                 GPIO_Pin_10
#define SPI_SCK_Pin_Source          GPIO_PinSource10

#define SPI_MISO_PORT               GPIOC
#define SPI_MISO_Pin                GPIO_Pin_11
#define SPI_MISO_Pin_Source         GPIO_PinSource11

#define SPI_MOSI_PORT               GPIOC
#define SPI_MOSI_Pin                GPIO_Pin_12
#define SPI_MOSI_Pin_Source         GPIO_PinSource12

#define SPI_OUT_PORT                GPIOD
#define SPI_OUT_Pin                 GPIO_Pin_2

#define SPI_IN_PORT                 GPIOB
#define SPI_IN_Pin                  GPIO_Pin_6


#endif /* HW_MAP_H */
