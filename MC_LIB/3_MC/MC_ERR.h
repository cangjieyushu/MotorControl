/**************************************************************************************************
*     File Name :                        MC_ERR.h
*     Library/Module Name :              MC
*     Author :                           CJYS
*     Create Date :                      2024/1/1
*     Abstract Description :             电机子任务头文件
**************************************************************************************************/

#ifndef MC_ERR_H
#define MC_ERR_H


#include "PMSM_PARA.h"
#include "MATH_CHECK.h"


//电压保护
#define OVER_VOLTAGE_PROTECT_LEVEL_TL           (Q14I_VOLTAGE_TO_PU(28.0f))         //V，过压保护阈值
#define OVER_VOLTAGE_PROTECT_LEVEL_TIME         (100U)                              //ms，过压保护时间
#define OVER_VOLTAGE_CLEAR_LEVEL_TL             (Q14I_VOLTAGE_TO_PU(26.0f))         //V，过压保护恢复阈值
#define OVER_VOLTAGE_CLEAR_LEVEL_TIME           (100U)                              //ms，过压保护恢复时间

#define LOW_VOLTAGE_PROTECT_LEVEL_TL            (Q14I_VOLTAGE_TO_PU(10.0f))         //V，低压保护阈值
#define LOW_VOLTAGE_PROTECT_LEVEL_TIME          (100U)                              //ms，低压保护时间

#define FAST_OVER_VOLTAGE_PROTECT_LEVEL_TL      (Q14I_VOLTAGE_TO_PU(32.0f))         //V，快速过压保护阈值
#define FAST_OVER_VOLTAGE_PROTECT_LEVEL_TIME    (5U)                                //快速过压保护时间

//电流保护
#define CURRENT_PROTECT_LEVEL                   3                                   //过流保护档位
#define CURRENT_PROTECT_LEVEL_1_TL              (Q14I_CURRENT_TO_PU(40.0f))         //A，过流保护阈值
#define CURRENT_PROTECT_LEVEL_1_TIME            (100U)                              //ms，过流保护时间

#define CURRENT_PROTECT_LEVEL_2_TL              (Q14I_CURRENT_TO_PU(35.0f))         //A，过流保护阈值
#define CURRENT_PROTECT_LEVEL_2_TIME            (1000U)                             //ms，过流保护时间

#define CURRENT_PROTECT_LEVEL_3_TL              (Q14I_CURRENT_TO_PU(30.0f))         //A，过流保护阈值
#define CURRENT_PROTECT_LEVEL_3_TIME            (10000U)                            //ms，过流保护时间

#define FAST_CURRENT_PROTECT_LEVEL_TL           (Q14I_CURRENT_TO_PU(50.0f))         //A，快速过流保护阈值
#define FAST_CURRENT_PROTECT_LEVEL_TIME         (5U)                                //快速过流保护时间

//温度保护
#define OVER_TEMP_PROTECT_LEVEL_TL              ((Q32U_)(1000.0f))                  //lsb，过温保护阈值
#define OVER_TEMP_PROTECT_LEVEL_TIME            (1000U)                             //ms，过温保护时间
#define OVER_TEMP_CLEAR_LEVEL_TL                ((Q32U_)(1200.0f))                  //lsb，过温保护恢复阈值
#define OVER_TEMP_CLEAR_LEVEL_TIME              (1000U)                             //ms，过温保护恢复时间

#define LOW_TEMP_PROTECT_LEVEL_TL               ((Q32U_)(2000.0f))                  //lsb，低温保护阈值
#define LOW_TEMP_PROTECT_LEVEL_TIME             (1000U)                             //ms，低温保护时间
#define LOW_TEMP_CLEAR_LEVEL_TL                 ((Q32U_)(1800.0f))                  //lsb，低温保护恢复阈值
#define LOW_TEMP_CLEAR_LEVEL_TIME               (1000U)                             //ms，低温保护恢复时间

//速度保护
#define OVER_SPEED_PROTECT_LEVEL_TL             (Q14I_FREQ_TO_PU(MOTOR_SPEED_TO_FREQ(25000.0f)))        //rpm，超速保护阈值
#define OVER_SPEED_PROTECT_LEVEL_TIME           (1000U)                                                 //ms，超速保护时间

#define LOW_SPEED_PROTECT_LEVEL_TL              (Q14I_FREQ_TO_PU(MOTOR_SPEED_TO_FREQ(1.0f)))            //rpm，低速保护阈值
#define LOW_SPEED_PROTECT_LEVEL_TIME            (1000U)                                                 //ms，低速保护时间

//功率保护
#define OVER_POWER_PROTECT_LEVEL_TL             (Q14I_VOLTAGE_TO_PU(24.0f)*Q14I_CURRENT_TO_PU(15.0f))   //W，过功率保护阈值
#define OVER_POWER_PROTECT_LEVEL_TIME           (1000U)                                                 //ms，过功率保护时间
#define OVER_IBUS_PROTECT_LEVEL_TL              (Q14I_CURRENT_TO_PU(30.0f))                             //A，过母线保护阈值
#define OVER_IBUS_PROTECT_LEVEL_TIME            (1000U)                                                 //ms，过母线保护时间

//MOS损坏次数
#define MOS_ERROR_COUNT                         (3U)                                                    //MOS损坏次数


//缺相保护
#define PHASE_LACK_IPHASE_PROTECT_LEVEL_TL      (Q14I_CURRENT_TO_PU(5.0f))                              //A，缺相保护阈值
#define PHASE_LACK_ISREF_PROTECT_LEVEL_TL       (Q14I_CURRENT_TO_PU(30.0f))                             //A，缺相保护阈值
#define PHASE_LACK_PROTECT_LEVEL_TIME           (500U)                                                  //ms，缺相保护时间

//堵转保护
#define ROTOR_LOCK_ISREF_PROTECT_LEVEL_TL       (Q14I_CURRENT_TO_PU(30.0f))                             //A，堵转保护阈值
#define ROTOR_LOCK_SPEED_PROTECT_LEVEL_TL       (Q14I_FREQ_TO_PU(MOTOR_SPEED_TO_FREQ(1.0f)))            //rpm，堵转保护阈值
#define ROTOR_LOCK_PROTECT_LEVEL_TIME           (500U)                                                  //ms，堵转保护时间

//失步保护
#define LOSS_STEP_ES_PROTECT_LEVEL_TL           (Q14I_VOLTAGE_TO_PU(25000.0f))                          //V，失步保护阈值
#define LOSS_STEP_SPEED_PROTECT_LEVEL_TL        (Q14I_VOLTAGE_TO_PU(1.0f))                              //V，失步保护阈值
#define LOSS_STEP_PROTECT_LEVEL_TIME            (500U)                                                  //ms，失步保护时间


typedef union{
    ALL all;
    struct{
        BIT current_short       :1;//短路
        BIT mos_fault           :1;//mos损坏（单个上电周期内，发生三次短路保护，锁死故障状态）
        BIT current_offset      :1;//偏置
        BIT position_error      :1;//电机定位失败、缺相SQ
        BIT rotor_stall         :1;//电机堵转
        
        BIT over_voltage        :1;//电机过压
        BIT low_voltage         :1;//电机低压
        BIT over_current1       :1;//电机过流1
        BIT over_current2       :1;//电机过流2
        BIT over_current3       :1;//电机过流3
        BIT over_temp           :1;//电机过温
        BIT low_temp            :1;//电机低温
        BIT over_speed          :1;//电机过速
        BIT low_speed           :1;//电机低速
        BIT over_power          :1;//电机过功率
        BIT over_ibus           :1;//电机过母线
        
        BIT fast_over_voltage   :1;//电机快速过压
        BIT fast_over_current   :1;//电机快速过流
        
        BIT phase_lack_a        :1;//电机A相缺相
        BIT phase_lack_b        :1;//电机B相缺相
        BIT phase_lack_c        :1;//电机C相缺相
        BIT rotor_lock          :1;//电机堵转FOC
        BIT loss_step           :1;//电机失步
    }bit;
}UN_MOTOR_ERROR_FLAG;

typedef struct{
    UN_MOTOR_ERROR_FLAG         Motor_Error_Flag;
    
    Q32I_                       _I_Q14U_Vbus_pu;
    Q32I_                       _I_Q14U_Iphase_Max_pu;
    Q32I_                       _I_Q14U_Temp_ADC;
    Q32I_                       _I_Q14U_Speed_pu;
    Q32I_                       _I_Q14U_Ibus_pu;

    Q32I_                       _I_Q14U_IsRef_pu;
    Q32I_                       _I_Q14U_Iphase_A_Max_pu;
    Q32I_                       _I_Q14U_Iphase_B_Max_pu;
    Q32I_                       _I_Q14U_Iphase_C_Max_pu;
    Q32I_                       _I_Q14U_Es_pu;
    
    ST_CHECK                    Over_Voltage;
    ST_CHECK                    Low_Voltage;
    ST_CHECK                    Over_Current1;
    ST_CHECK                    Over_Current2;
    ST_CHECK                    Over_Current3;
    ST_CHECK                    Over_Temp;
    ST_CHECK                    Low_Temp;
    ST_CHECK                    Over_Speed;
    ST_CHECK                    Low_Speed;
    ST_CHECK                    Over_Power;
    ST_CHECK                    Over_Ibus;
    ST_CHECK                    Phase_Lack_A;
    ST_CHECK                    Phase_Lack_B;
    ST_CHECK                    Phase_Lack_C;
    ST_CHECK                    Rotor_Lock;
    ST_CHECK                    Loss_Step;
    
    ST_CHECK                    Fast_Over_Voltage;
    ST_CHECK                    Fast_Over_Current;
    
    Q32U_                       _V_Q32U_MOS_Error_cnt;
    Q32U_                       _P_Q32U_MOS_Error_Count;
}ST_MOTOR_ERROR;


/**********************************************************************************************
Function: MC_Error_Speed_Flow
Description: 电机故障检测速度环
Input: 无
Output: 无
Input_Output: 电机故障检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MC_Error_Speed_Flow(ST_MOTOR_ERROR* pERR, Q32U_ Q32U_Enable);

/**********************************************************************************************
Function: MC_Error_Speed_Flow_FOC
Description: 电机故障检测速度环FOC
Input: 无
Output: 无
Input_Output: 电机故障检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MC_Error_Speed_Flow_FOC(ST_MOTOR_ERROR* pERR, Q32U_ Q32U_Enable);

/**********************************************************************************************
Function: MC_Error_Current_Flow
Description: 电机故障检测电流环
Input: 无
Output: 无
Input_Output: 电机故障检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MC_Error_Current_Flow(ST_MOTOR_ERROR* pERR);

/**********************************************************************************************
Function: MC_Error_Short_Flow
Description: 电机故障检测短路环
Input: 无
Output: 无
Input_Output: 电机故障检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MC_Error_Short_Flow(ST_MOTOR_ERROR* pERR);

/**********************************************************************************************
Function: MC_Error_Clear_
Description: 清除电机故障
Input: 无
Output: 无
Input_Output: 电机故障检测指针
Return: 无
Author: CJYS
***********************************************************************************************/
void MC_Error_Clear(ST_MOTOR_ERROR* pERR);


#endif /* MC_ERR_H */
