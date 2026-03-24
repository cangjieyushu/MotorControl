/**************************************************************************************************
*     File Name :                        BSP_GPIO.c
*     Library/Module Name :              BSP
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             GPIO初始化及应用层接口源文件
**************************************************************************************************/
#include "BSP_GPIO.h"

/**********************************************************************************************
Function: BSP_GPIO_Init
Description: GPIO初始化
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void BSP_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    /*TIM8:*/ 
    GPIO_InitStruct.Mode    = GPIO_MODER_MODER_Output;
    GPIO_InitStruct.Pull    = GPIO_PUPDR_Pullup;
    GPIO_InitStruct.Speed   = GPIO_OSPEEDR_High;
    GPIO_InitStruct.Alternate = GPIO_AF0;
    
    GPIO_InitStruct.Pin = LED0_PIN;			
    GPIO_Init(LED0_GPIO_PORT,&GPIO_InitStruct);
    GPIO_InitStruct.Pin = LED1_PIN;			
    GPIO_Init(LED1_GPIO_PORT,&GPIO_InitStruct);
    
    /*TIM8:*/ 
    GPIO_InitStruct.Mode    = GPIO_MODER_MODER_AF;
    GPIO_InitStruct.Pull    = GPIO_PUPDR_Floating;
    GPIO_InitStruct.Speed   = GPIO_OSPEEDR_High;

    GPIO_InitStruct.Alternate = UH_PWM_AF;
    GPIO_InitStruct.Pin = UH_PWM_PIN;			
    GPIO_Init(UH_PWM_GPIO_PORT,&GPIO_InitStruct);
    GPIO_InitStruct.Alternate = VH_PWM_AF;
    GPIO_InitStruct.Pin = VH_PWM_PIN;			
    GPIO_Init(VH_PWM_GPIO_PORT,&GPIO_InitStruct);
    GPIO_InitStruct.Alternate = WH_PWM_AF;
    GPIO_InitStruct.Pin = WH_PWM_PIN;			
    GPIO_Init(WH_PWM_GPIO_PORT,&GPIO_InitStruct);
    
    GPIO_InitStruct.Alternate = UL_PWM_AF;
    GPIO_InitStruct.Pin = UL_PWM_PIN;			
    GPIO_Init(UL_PWM_GPIO_PORT,&GPIO_InitStruct);
    GPIO_InitStruct.Alternate = VL_PWM_AF;
    GPIO_InitStruct.Pin = VL_PWM_PIN;			
    GPIO_Init(VL_PWM_GPIO_PORT,&GPIO_InitStruct);
    GPIO_InitStruct.Alternate = WL_PWM_AF;
    GPIO_InitStruct.Pin = WL_PWM_PIN;			
    GPIO_Init(WL_PWM_GPIO_PORT,&GPIO_InitStruct);
    
    //ADC
    GPIO_InitStruct.Mode 		= GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull 		= GPIO_PUPDR_Floating;
    GPIO_InitStruct.Speed 		= GPIO_OSPEEDR_High;
    GPIO_InitStruct.Alternate 	= GPIO_AF0;

    GPIO_InitStruct.Pin = ADC_U_BEMF_PIN;				
    GPIO_Init(ADC_U_BEMF_GPIO_PORT,&GPIO_InitStruct);

    GPIO_InitStruct.Pin = ADC_V_BEMF_PIN;				
    GPIO_Init(ADC_V_BEMF_GPIO_PORT,&GPIO_InitStruct);	

    GPIO_InitStruct.Pin = ADC_W_BEMF_PIN;				
    GPIO_Init(ADC_W_BEMF_GPIO_PORT,&GPIO_InitStruct);	
    

    GPIO_InitStruct.Pin = ADC_VBUS_PIN;					
    GPIO_Init(ADC_VBUS_GPIO_PORT,&GPIO_InitStruct);		

    GPIO_InitStruct.Pin = ADC_TEMP_PIN;					
    GPIO_Init(ADC_TEMP_GPIO_PORT,&GPIO_InitStruct);	

    GPIO_InitStruct.Pin = ADC_VR_PIN;					
    GPIO_Init(ADC_VR_GPIO_PORT,&GPIO_InitStruct);
    
    /*--------    OPAMP2   ----------*/
    GPIO_InitStruct.Pin  					= CMP_PHASE_P_PIN;
    GPIO_InitStruct.Mode 					= GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull 					= GPIO_PUPDR_Floating;
    GPIO_InitStruct.Alternate			    = GPIO_AF0;
    GPIO_InitStruct.Speed					= GPIO_OSPEEDR_Low;
    GPIO_Init(CMP_PHASE_P_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin  					= CMP_PHASE_N_PIN;
    GPIO_InitStruct.Mode 					= GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull 					= GPIO_PUPDR_Floating;
    GPIO_InitStruct.Alternate			    = GPIO_AF0;
    GPIO_InitStruct.Speed					= GPIO_OSPEEDR_Low;
    GPIO_Init(CMP_PHASE_N_GPIO_PORT, &GPIO_InitStruct);
    
    /*CMP1*/
    GPIO_InitStruct.Pull = GPIO_PUPDR_Floating;
    GPIO_InitStruct.Speed = GPIO_OSPEEDR_High;
    GPIO_InitStruct.Alternate = GPIO_AF0;

    GPIO_InitStruct.Pin = OPA_PHASE_P_PIN;    //2P
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_Init(OPA_PHASE_P_GPIO_PORT,&GPIO_InitStruct);

    GPIO_InitStruct.Pin = OPA_PHASE_N_PIN;    //2N
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_Init(OPA_PHASE_N_GPIO_PORT,&GPIO_InitStruct);
    
    //PB1  -> UART1_TX
    //PB2  -> UART1_RX
    GPIO_InitStruct.Alternate = GPIO_AF4;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PUPDR_Pullup;
    GPIO_InitStruct.Speed     = GPIO_OSPEEDR_High;
    GPIO_InitStruct.Pin       = GPIO_PIN_2;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    GPIO_InitStruct.Pull      = GPIO_PUPDR_Floating;
    GPIO_InitStruct.Pin       = GPIO_PIN_1;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    //PD5  -> UART2_TX
    //PD4  -> UART2_RX
    GPIO_InitStruct.Alternate = GPIO_AF5;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PUPDR_Pullup;
    GPIO_InitStruct.Speed     = GPIO_OSPEEDR_High;
    GPIO_InitStruct.Pin       = GPIO_PIN_4;
    GPIO_Init(GPIOD, &GPIO_InitStruct);
    GPIO_InitStruct.Pull      = GPIO_PUPDR_Floating;
    GPIO_InitStruct.Pin       = GPIO_PIN_5;
    GPIO_Init(GPIOD, &GPIO_InitStruct);
}
