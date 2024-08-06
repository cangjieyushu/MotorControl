/**************************************************************************************************/
/**
 * @copyright : 
 **************************************************************************************************/

#include "BSP_DAC.h"

void BSP_DAC_Init(void)
{
    DAC_InitTypeDef   DAC_InitType;
    
    DAC_InitType.DAC_Trigger = DAC_Trigger_Software;	//不使用触发功能 TEN1=0
    DAC_InitType.DAC_WaveGeneration = DAC_WaveGeneration_Noise;//不使用波形发生
    DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;//屏蔽、幅值设置
    DAC_InitType.DAC_OutputBuffer = DAC_OutputBuffer_Disable ;	//DAC1输出缓存关闭 BOFF1=1
    DAC_Init(DAC_Channel_1,&DAC_InitType);	 //初始化DAC通道1
    DAC_Init(DAC_Channel_2,&DAC_InitType);	 //初始化DAC通道2
        
    DAC_Cmd(DAC_Channel_1, ENABLE);  //使能DAC通道1
    DAC_Cmd(DAC_Channel_2, ENABLE);  //使能DAC通道1

    DAC_SetChannel1Data(DAC_Align_12b_R, 0);  //12位右对齐数据格式设置DAC值
    DAC_SetChannel2Data(DAC_Align_12b_R, 0);  //12位右对齐数据格式设置DAC值
}
