/**************************************************************************************************
*     File Name :                        SYS_VOFA.c
*     Library/Module Name :              SYS
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             上位机收发源文件
**************************************************************************************************/

#include "SYS_VOFA.h"


/**********************************************************************************************
Function: SYS_VOFA_RX
Description: 系统通讯控制
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void SYS_VOFA_RX(ST_MOTOR_TASK* pMotor, ST_SYSTEM_TASK* pST, ST_UART_CONTROL* pUC)
{
    Q32U_ rx_tmp = 0;
    UN_Q32U_to_F Q32UF_tmp;
    
    if(UARTH_Rx_DMA_Flag())
    {
        //继电器IO类接口  XX  XX  XX  XX  0X  BB
        if(pUC->rxdata[5] == 0xBBU)
        {
            if(pUC->rxdata[4] == 0x00U)
            {
                rx_tmp = pUC->rxdata[0];
                if(rx_tmp == 1U)
                {
                    BSP_GPIO_RLY0(1);
                }
                else
                {
                    BSP_GPIO_RLY0(0);
                }
            }
            else if(pUC->rxdata[4] == 0x01U)
            {
                rx_tmp = pUC->rxdata[0];
                if(rx_tmp == 1U)
                {
                    BSP_GPIO_RLY1(1);
                }
                else
                {
                    BSP_GPIO_RLY1(0);
                }
            }
            else
            {
                
            }
        }
        
        //电机指令接口    XX  XX  XX  XX  0X  CC
        if(pUC->rxdata[5] == 0xCCU)
        {
            if(pUC->rxdata[4] == 0x00U)
            {
                rx_tmp = pUC->rxdata[0];
                if(rx_tmp == 1U)
                {
                    Motor_Set_Dir(pMotor, -1);
                }
                else
                {
                    Motor_Set_Dir(pMotor, 1);
                }
            }
            else if(pUC->rxdata[4] == 0x01U)
            {
                rx_tmp = pUC->rxdata[0];
                pST->System_State_Flag.BIT.system_runflag = rx_tmp;
            }
            else if(pUC->rxdata[4] == 0x02U)
            {
                Q32UF_tmp.u08p[0] = (Q32U_)pUC->rxdata[0];
                Q32UF_tmp.u08p[1] = (Q32U_)pUC->rxdata[1];
                Q32UF_tmp.u08p[2] = (Q32U_)pUC->rxdata[2];
                Q32UF_tmp.u08p[3] = (Q32U_)pUC->rxdata[3];
                Motor_Set_Target_Speed(pMotor, (Q32U_)(Q32UF_tmp.f32p));
            }
            else
            {
                
            }
        }
        
        //电机参数接口    XX  XX  XX  XX  0X  DD
        if(pUC->rxdata[5] == 0xDDU)
        {
            Q32UF_tmp.u08p[0] = (Q32U_)pUC->rxdata[0];
            Q32UF_tmp.u08p[1] = (Q32U_)pUC->rxdata[1];
            Q32UF_tmp.u08p[2] = (Q32U_)pUC->rxdata[2];
            Q32UF_tmp.u08p[3] = (Q32U_)pUC->rxdata[3];
            Motor_API_Function[pUC->rxdata[4]](pMotor, Q32UF_tmp.f32p);
        }
            
        pUC->rxdata[0] = 0x00U;
        pUC->rxdata[1] = 0x00U;
        pUC->rxdata[2] = 0x00U;
        pUC->rxdata[3] = 0x00U;
        pUC->rxdata[4] = 0x00U;
        pUC->rxdata[5] = 0x00U;
        UARTH_Rx_DMA_Start(pUC->rxdata);
    }
}

/**********************************************************************************************
Function: SYS_VOFA_TX
Description: 系统通讯控制
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void SYS_VOFA_TX(ST_MOTOR_TASK* pMotor, ST_SYSTEM_TASK* pST, ST_UART_CONTROL* pUC)
{
    Q32U_ tx_tmp = 0;
    UN_Q32U_to_F Q32UF_tmp_tx1;
    UN_Q32U_to_F Q32UF_tmp_tx2;
    UN_Q32U_to_F Q32UF_tmp_tx3;
    UN_Q32U_to_F Q32UF_tmp_tx4;
    
    if(UARTH_Tx_DMA_Flag())
    {
        if(Motor_Read_Dir(pMotor) == 1U)
        {
            tx_tmp = 0U;
        }
        else
        {
            tx_tmp = 1U;
        }
        Q32UF_tmp_tx1.f32p = (float)Motor_Read_Speed(pMotor);
        Q32UF_tmp_tx2.f32p = (float)Motor_Read_Current(pMotor);
        Q32UF_tmp_tx3.f32p = (float)Motor_Read_Bus(pMotor);
        Q32UF_tmp_tx4.f32p = (float)(Motor_Read_Error(pMotor) | (tx_tmp<<30U) | (Motor_Read_Run_State(pMotor)<<31U));
        
        pUC->txdata_length_tmp = 0U;
        pUC->txdata[pUC->txdata_length_tmp++] = Q32UF_tmp_tx1.u08p[0];
        pUC->txdata[pUC->txdata_length_tmp++] = Q32UF_tmp_tx1.u08p[1];
        pUC->txdata[pUC->txdata_length_tmp++] = Q32UF_tmp_tx1.u08p[2];
        pUC->txdata[pUC->txdata_length_tmp++] = Q32UF_tmp_tx1.u08p[3];
        pUC->txdata[pUC->txdata_length_tmp++] = Q32UF_tmp_tx2.u08p[0];
        pUC->txdata[pUC->txdata_length_tmp++] = Q32UF_tmp_tx2.u08p[1];
        pUC->txdata[pUC->txdata_length_tmp++] = Q32UF_tmp_tx2.u08p[2];
        pUC->txdata[pUC->txdata_length_tmp++] = Q32UF_tmp_tx2.u08p[3];
        pUC->txdata[pUC->txdata_length_tmp++] = Q32UF_tmp_tx3.u08p[0];
        pUC->txdata[pUC->txdata_length_tmp++] = Q32UF_tmp_tx3.u08p[1];
        pUC->txdata[pUC->txdata_length_tmp++] = Q32UF_tmp_tx3.u08p[2];
        pUC->txdata[pUC->txdata_length_tmp++] = Q32UF_tmp_tx3.u08p[3];
        pUC->txdata[pUC->txdata_length_tmp++] = Q32UF_tmp_tx4.u08p[0];
        pUC->txdata[pUC->txdata_length_tmp++] = Q32UF_tmp_tx4.u08p[1];
        pUC->txdata[pUC->txdata_length_tmp++] = Q32UF_tmp_tx4.u08p[2];
        pUC->txdata[pUC->txdata_length_tmp++] = Q32UF_tmp_tx4.u08p[3];
        pUC->txdata[pUC->txdata_length_tmp++] = 0x00U;
        pUC->txdata[pUC->txdata_length_tmp++] = 0x00U;
        pUC->txdata[pUC->txdata_length_tmp++] = 0x80U;
        pUC->txdata[pUC->txdata_length_tmp++] = 0x7FU;
        
        UARTH_Tx_DMA_Start(pUC->txdata);
    }
}

/**********************************************************************************************
Function: SYS_VOFA_TASK
Description: 系统通讯控制
Input: 无
Output: 无
Input_Output: 无
Return: 无
Author: CJYS
***********************************************************************************************/
void SYS_VOFA_TASK(ST_MOTOR_TASK* pMotor, ST_SYSTEM_TASK* pST, ST_UART_CONTROL* pUC)
{
    SYS_VOFA_RX(pMotor, pST, pUC);
    SYS_VOFA_TX(pMotor, pST, pUC);
}
