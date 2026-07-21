/**************************************************************************************************
*     File Name :                        BSP_CLK.c
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             时钟初始化及应用层接口源文件
**************************************************************************************************/
#include "BSP_CLK.h"

/**********************************************************************************************
Function: SysTickConfig
Description: 1ms时钟初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void SysTickConfig(void)
{
    if(SysTick_Config(HAL_SLOW_TIMER_COUNT))
    {
        while(1);
    }
}

/* The following is to prevent Vcore fluctuations caused by frequency switching. 
   It is strongly recommended to include it to avoid issues caused by self-removal. 
*/
#define RCU_MODIFY(__delay)     do{                                     \
                                    volatile uint32_t i,reg;            \
                                    if(0 != __delay){                   \
                                        reg = RCU_CFG0;                 \
                                        reg &= ~(RCU_CFG0_AHBPSC);      \
                                        /* CK_AHB = SYSCLK/2 */         \
                                        reg |= RCU_AHB_CKSYS_DIV2;      \
                                        RCU_CFG0 = reg;                 \
                                        for(i=0; i<__delay; i++){       \
                                        }                               \
                                        reg = RCU_CFG0;                 \
                                        reg &= ~(RCU_CFG0_AHBPSC);      \
                                        reg |= RCU_AHB_CKSYS_DIV4;      \
                                        /* CK_AHB = SYSCLK/4 */         \
                                        RCU_CFG0 = reg;                 \
                                        for(i=0; i<__delay; i++){       \
                                        }                               \
                                    }                                   \
                                }while(0)
#define RCU_MODIFY_UP_2(__delay)     do{                                    \
                                        volatile uint32_t i,reg;            \
                                        if(0 != __delay){                   \
                                            for(i=0; i<__delay; i++){       \
                                            }                               \
                                            reg = RCU_CFG0;                 \
                                            reg &= ~(RCU_CFG0_AHBPSC);      \
                                            reg |= RCU_AHB_CKSYS_DIV2;      \
                                            RCU_CFG0 = reg;                 \
                                            for(i=0; i<__delay; i++){       \
                                            }                               \
                                            reg = RCU_CFG0;                 \
                                            reg &= ~(RCU_CFG0_AHBPSC);      \
                                            reg |= RCU_AHB_CKSYS_DIV1;      \
                                            RCU_CFG0 = reg;                 \
                                    }                                       \
                                }while(0)

static void switch_system_clock_to_72m_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;
    
    RCU_MODIFY(0x80);
    /* select IRC8M as system clock source, deinitialize the RCU */
    rcu_system_clock_source_config(RCU_CKSYSSRC_IRC8M);
    Math_Delay_us(100U);
    rcu_deinit();
    
    /* enable HXTAL */
    RCU_CTL0 |= RCU_CTL0_HXTALEN;

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do{
        timeout++;
        stab_flag = (RCU_CTL0 & RCU_CTL0_HXTALSTB);
    }
    while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));
    /* if fail */
    if(0U == (RCU_CTL0 & RCU_CTL0_HXTALSTB)){
        while(1){
        }
    }

    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT_1;
    
    /* HXTAL is stable */
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;

    /* PLL = HXTAL / 2 * 18 = 72 MHz */
    RCU_CFG0 &= ~(RCU_CFG0_PLLSEL | RCU_CFG0_PLLMF | RCU_CFG0_PLLDV | RCU_CFG0_PLLPREDV);
    RCU_CFG0 |= (RCU_PLLPREDV_DIV2 | RCU_PLLSRC_HXTAL | RCU_PLL_MUL18);

    /* enable PLL */
    RCU_CTL0 |= RCU_CTL0_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL0 & RCU_CTL0_PLLSTB)){
    }

    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLL;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(0U == (RCU_CFG0 & RCU_SCSS_PLL)){
    }
    RCU_MODIFY_UP_2(0x80);
}

static void switch_system_clock_to_72m_irc8m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;
    
    RCU_MODIFY(0x80);
    /* select IRC8M as system clock source, deinitialize the RCU */
    rcu_system_clock_source_config(RCU_CKSYSSRC_IRC8M);
    Math_Delay_us(100U);
    rcu_deinit();
    
    /* enable IRC8M */
    RCU_CTL0 |= RCU_CTL0_IRC8MEN;

    /* wait until IRC8M is stable or the startup time is longer than IRC8M_STARTUP_TIMEOUT */
    do{
        timeout++;
        stab_flag = (RCU_CTL0 & RCU_CTL0_IRC8MSTB);
    }
    while((0U == stab_flag) && (IRC8M_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL0 & RCU_CTL0_IRC8MSTB)){
        while(1){
        }
    }

    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT_2;
    
    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV1;
    /* APB1 = AHB */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV1;
    /* PLL = (IRC8M/2) * 18 = 72 MHz */
    RCU_CFG0 &= ~(RCU_CFG0_PLLSEL | RCU_CFG0_PLLMF);
    RCU_CFG0 |= (RCU_PLLSRC_IRC8M_DIV2 | RCU_PLL_MUL18);

    /* enable PLL */
    RCU_CTL0 |= RCU_CTL0_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL0 & RCU_CTL0_PLLSTB)){
    }

    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLL;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while(0U == (RCU_CFG0 & RCU_SCSS_PLL)){
    }
    RCU_MODIFY_UP_2(0x80);
}

/**********************************************************************************************
Function: BSP_CLK_Init
Description: 时钟初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_CLK_Init(void)
{
//    switch_system_clock_to_72m_irc8m();
    
    systick_clksource_set(SYSTICK_CLKSOURCE_HCLK);
    
    SysTickConfig();
    
    rcu_periph_clock_enable(RCU_CFGCMP);
    
    /* enable GPIOAB clock */
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOB);
    
    /* enable TIMER0 clock */
    rcu_periph_clock_enable(RCU_TIMER0);
    /* enable timer13 clock */
    rcu_periph_clock_enable(RCU_TIMER2);
    rcu_periph_clock_enable(RCU_TIMER13);
    
    /* enable CMP clock */
    rcu_periph_clock_enable(RCU_CFGCMP);
    
    /* config ADC clock */
    rcu_adc_clock_config(RCU_ADCCK_APB2_DIV4);
    /* config USART clock */
    rcu_usart_clock_config(RCU_USART0SRC_CKAPB2);
    
    /* enable USART clock */
    rcu_periph_clock_enable(RCU_USART0);
    rcu_periph_clock_enable(RCU_SPI0);
    
    /* enable ADC clock */
    rcu_periph_clock_enable(RCU_ADC);
    /* enable DMA clock */
    rcu_periph_clock_enable(RCU_DMA);
    
    syscfg_deinit();
    syscfg_dma_remap_enable(SYSCFG_DMA_REMAP_USART0TX);
    syscfg_dma_remap_enable(SYSCFG_DMA_REMAP_USART0RX);
    
    Q32U_ tmp = 0U;
    tmp = rcu_clock_freq_get(CK_SYS);
    tmp = rcu_clock_freq_get(CK_AHB);
    tmp = rcu_clock_freq_get(CK_APB1);
    tmp = rcu_clock_freq_get(CK_APB2);
    tmp = rcu_clock_freq_get(CK_ADC);
    tmp = rcu_clock_freq_get(CK_USART);
}
