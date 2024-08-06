/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/
 
#include "BSP_GPIO.h"

void BSP_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_SetBits(SHUTDOWN1_GPIO_Port, SHUTDOWN1_Pin);
    
    GPIO_InitStruct.GPIO_Pin = Start_Stop_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
    GPIO_Init(Start_Stop_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = SHUTDOWN1_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
    GPIO_Init(SHUTDOWN1_GPIO_Port, &GPIO_InitStruct);
    
    GPIO_InitStruct.GPIO_Pin = LED0_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
    GPIO_Init(LED0_GPIO_PORT, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = LED1_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
    GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStruct);
    GPIO_ResetBits(LED0_GPIO_PORT, LED0_Pin);
    GPIO_ResetBits(LED1_GPIO_PORT, LED1_Pin);
    
//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_15;
//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;// 输入  
//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;// 拉GPIO_PuPd_UP
//GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化

//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;;
//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉
//GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化

//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_11;
//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//输入
//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//下拉
//GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化

//GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;/*模拟输入*/
//GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7;/*通道3*/
//GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;/*不带上下拉*/
//GPIO_Init(GPIOA,&GPIO_InitStructure);/*初始化*/

//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;
//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//GPIO_Init(GPIOE,&GPIO_InitStructure);

//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_15;
//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//GPIO_Init(GPIOE,&GPIO_InitStructure);		

//GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_TIM1);
//GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1);
//GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF_TIM1);
//GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_TIM1);
//GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF_TIM1);
//GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_TIM1);
//GPIO_PinAFConfig(GPIOE,GPIO_PinSource15,GPIO_AF_TIM1);
}
