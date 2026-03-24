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
*                                              rx32h6xx
*                                           Library Function
*
*                                   Copyright 2024, RX Tech, Corp.
*                                        All Rights Reserved
*
*
* Project      : rx32h6xx
* File         : rx32h6xx_adc.h
* By           : RX_SD_Team
* Version      : V1.0.0
* Description  : Only rx32h6xx
*********************************************************************************************************
*/
#ifndef __rx32h6xx_ADC_H__
#define __rx32h6xx_ADC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "rx32h6xx.h"

/******************************************************************************/
/*                                                                            */
/*                      Analog to Digital Converter (ADC)                     */
/*                                                                            */
/******************************************************************************/
 
/********************  Bit definition for ADC_SR register  ********************/
#define ADC_SR_AWD                          ((uint32_t)0x00000001)                     /*!< ADC analog watchdog 1 flag */ 
#define ADC_SR_EOC                          ((uint32_t)0x00000002)                     /*!< ADC group regular end of sequence conversions flag */
#define ADC_SR_JEOC                         ((uint32_t)0x00000004)                     /*!< ADC group injected end of sequence conversions flag */
#define ADC_SR_JSTRT                        ((uint32_t)0x00000008)                     /*!< ADC group injected conversion start flag */
#define ADC_SR_STRT                         ((uint32_t)0x00000010)                     /*!< ADC group regular conversion start flag */

/*******************  Bit definition for ADC_CR1 register  ********************/
#define ADC_CR1_AWDCH                       ((uint32_t)0x0000001F)                     /*!< ADC analog watchdog 1 monitored channel selection */
#define ADC_CR1_AWDCH_0                     ((uint32_t)0x00000001)
#define ADC_CR1_AWDCH_1                     ((uint32_t)0x00000002)
#define ADC_CR1_AWDCH_2                     ((uint32_t)0x00000004)
#define ADC_CR1_AWDCH_3                     ((uint32_t)0x00000008)
#define ADC_CR1_AWDCH_4                     ((uint32_t)0x00000010)

#define ADC_CR1_EOCIE                       ((uint32_t)0x00000020)                     /*!< ADC group regular end of sequence conversions interrupt */
#define ADC_CR1_AWDIE                       ((uint32_t)0x00000040)                     /*!< ADC analog watchdog 1 interrupt */
#define ADC_CR1_JEOCIE                      ((uint32_t)0x00000080)                     /*!< ADC group injected end of sequence conversions interrupt */
#define ADC_CR1_SCAN                        ((uint32_t)0x00000100)                     /*!< ADC scan mode */
#define ADC_CR1_AWDSGL                      ((uint32_t)0x00000200)                     /*!< ADC analog watchdog 1 monitoring a single channel or all channels */
#define ADC_CR1_JAUTO                       ((uint32_t)0x00000400)                     /*!< ADC group injected automatic trigger mode */
#define ADC_CR1_DISCEN                      ((uint32_t)0x00000800)                     /*!< ADC group regular sequencer discontinuous mode */
#define ADC_CR1_JDISCEN                     ((uint32_t)0x00001000)                     /*!< ADC group injected sequencer discontinuous mode */

#define ADC_CR1_DISCNUM                     ((uint32_t)0x0000E000)                     /*!< ADC group regular sequencer discontinuous number of ranks */
#define ADC_CR1_DISCNUM_0                   ((uint32_t)0x00002000)
#define ADC_CR1_DISCNUM_1                   ((uint32_t)0x00004000)
#define ADC_CR1_DISCNUM_2                   ((uint32_t)0x00008000)

#define ADC_CR1_JAWDEN                      ((uint32_t)0x00400000)                     /*!< ADC analog watchdog 1 enable on scope ADC group injected */
#define ADC_CR1_AWDEN                       ((uint32_t)0x00800000)                     /*!< ADC analog watchdog 1 enable on scope ADC group regular */

#define ADC_CR1_AWDFILT											((uint32_t)0x07000000)										 /*!< ADC analog watchdog 1 filter selection */
#define ADC_CR1_AWDFILT_0										((uint32_t)0x01000000)
#define ADC_CR1_AWDFILT_1									  ((uint32_t)0x02000000)
#define ADC_CR1_AWDFILT_2										((uint32_t)0x04000000)
	
/*******************  Bit definition for ADC_CR2 register  ********************/
#define ADC_CR2_ADON                        ((uint32_t)0x00000001)                     /*!< ADC enable */
#define ADC_CR2_CONT                        ((uint32_t)0x00000002)                     /*!< ADC group regular continuous conversion mode */
#define ADC_CR2_CAL                         ((uint32_t)0x00000004)                     /*!< ADC calibration start */
#define ADC_CR2_RSTCAL                      ((uint32_t)0x00000008)                     /*!< ADC calibration reset */
#define ADC_CR2_ALIGN                       ((uint32_t)0x00000400)                     /*!< ADC data alignement */

#define ADC_CR2_JEXTSEL                     ((uint32_t)0x00007800)                     /*!< ADC group injected external trigger source */
#define ADC_CR2_JEXTSEL_0                   ((uint32_t)0x00000800)
#define ADC_CR2_JEXTSEL_1                   ((uint32_t)0x00001000)
#define ADC_CR2_JEXTSEL_2                   ((uint32_t)0x00002000)
#define ADC_CR2_JEXTSEL_3                   ((uint32_t)0x00004000)

#define ADC_CR2_JEXTTRIG                    ((uint32_t)0x00008000)                     /*!< ADC group injected external trigger enable */

#define ADC_CR2_EXTSEL                      ((uint32_t)0x000E0000)                     /*!< ADC group regular external trigger source */
#define ADC_CR2_EXTSEL_0                    ((uint32_t)0x00020000) 
#define ADC_CR2_EXTSEL_1                    ((uint32_t)0x00040000) 
#define ADC_CR2_EXTSEL_2                    ((uint32_t)0x00080000) 

#define ADC_CR2_EXTTRIG                     ((uint32_t)0x00100000)                     /*!< ADC group regular external trigger enable */

#define ADC_CR2_JSWSTART                    ((uint32_t)0x00200000)                     /*!< ADC group injected conversion start */
#define ADC_CR2_SWSTART                     ((uint32_t)0x00400000)                     /*!< ADC group regular conversion start */
#define ADC_CR2_TSVREFE                     ((uint32_t)0x00800000)                     /*!< ADC internal path to VrefInt and temperature sensor enable */
/******************  Bit definition for ADC_SMPR1 register  *******************/
#define ADC_SMPR1_SMP10                     ((uint32_t)0x00000007)                     /*!< ADC channel 10 sampling time selection  */
#define ADC_SMPR1_SMP10_0                   ((uint32_t)0x00000001) 
#define ADC_SMPR1_SMP10_1                   ((uint32_t)0x00000002) 
#define ADC_SMPR1_SMP10_2                   ((uint32_t)0x00000004) 

#define ADC_SMPR1_SMP11                     ((uint32_t)0x00000038)                     /*!< ADC channel 11 sampling time selection  */
#define ADC_SMPR1_SMP11_0                   ((uint32_t)0x00000008) 
#define ADC_SMPR1_SMP11_1                   ((uint32_t)0x00000010) 
#define ADC_SMPR1_SMP11_2                   ((uint32_t)0x00000020) 

#define ADC_SMPR1_SMP12                     ((uint32_t)0x000001C0)                     /*!< ADC channel 12 sampling time selection  */
#define ADC_SMPR1_SMP12_0                   ((uint32_t)0x00000040) 
#define ADC_SMPR1_SMP12_1                   ((uint32_t)0x00000080) 
#define ADC_SMPR1_SMP12_2                   ((uint32_t)0x00000100) 

#define ADC_SMPR1_SMP13                     ((uint32_t)0x00000E00)                     /*!< ADC channel 13 sampling time selection  */
#define ADC_SMPR1_SMP13_0                   ((uint32_t)0x00000200) 
#define ADC_SMPR1_SMP13_1                   ((uint32_t)0x00000400) 
#define ADC_SMPR1_SMP13_2                   ((uint32_t)0x00000800) 

#define ADC_SMPR1_SMP14                     ((uint32_t)0x00007000)                     /*!< ADC channel 14 sampling time selection  */
#define ADC_SMPR1_SMP14_0                   ((uint32_t)0x00001000) 
#define ADC_SMPR1_SMP14_1                   ((uint32_t)0x00002000) 
#define ADC_SMPR1_SMP14_2                   ((uint32_t)0x00004000) 

#define ADC_SMPR1_SMP15                     ((uint32_t)0x00038000)                     /*!< ADC channel 15 sampling time selection  */
#define ADC_SMPR1_SMP15_0                   ((uint32_t)0x00008000) 
#define ADC_SMPR1_SMP15_1                   ((uint32_t)0x00010000) 
#define ADC_SMPR1_SMP15_2                   ((uint32_t)0x00020000) 

#define ADC_SMPR1_SMP16                     ((uint32_t)0x001C0000)                     /*!< ADC channel 16 sampling time selection  */
#define ADC_SMPR1_SMP16_0                   ((uint32_t)0x00040000) 
#define ADC_SMPR1_SMP16_1                   ((uint32_t)0x00080000) 
#define ADC_SMPR1_SMP16_2                   ((uint32_t)0x00100000) 

#define ADC_SMPR1_SMP17                     ((uint32_t)0x00E00000)                     /*!< ADC channel 17 sampling time selection  */
#define ADC_SMPR1_SMP17_0                   ((uint32_t)0x00200000) 
#define ADC_SMPR1_SMP17_1                   ((uint32_t)0x00400000) 
#define ADC_SMPR1_SMP17_2                   ((uint32_t)0x00800000) 

#define ADC_SMPR1_SMP18                     ((uint32_t)0x07000000)                     /*!< ADC channel 18 sampling time selection  */
#define ADC_SMPR1_SMP18_0                   ((uint32_t)0x01000000) 
#define ADC_SMPR1_SMP18_1                   ((uint32_t)0x02000000) 
#define ADC_SMPR1_SMP18_2                   ((uint32_t)0x04000000)

#define ADC_SMPR1_SMP19                     ((uint32_t)0x38000000)                     /*!< ADC channel 19 sampling time selection  */
#define ADC_SMPR1_SMP19_0                   ((uint32_t)0x08000000) 
#define ADC_SMPR1_SMP19_1                   ((uint32_t)0x10000000) 
#define ADC_SMPR1_SMP19_2                   ((uint32_t)0x20000000) 
/******************  Bit definition for ADC_SMPR2 register  *******************/
#define ADC_SMPR2_SMP0                      ((uint32_t)0x00000007)                     /*!< ADC channel 0 sampling time selection  */
#define ADC_SMPR2_SMP0_0                    ((uint32_t)0x00000001) 
#define ADC_SMPR2_SMP0_1                    ((uint32_t)0x00000002) 
#define ADC_SMPR2_SMP0_2                    ((uint32_t)0x00000004) 

#define ADC_SMPR2_SMP1                      ((uint32_t)0x00000038)                     /*!< ADC channel 1 sampling time selection  */
#define ADC_SMPR2_SMP1_0                    ((uint32_t)0x00000008) 
#define ADC_SMPR2_SMP1_1                    ((uint32_t)0x00000010) 
#define ADC_SMPR2_SMP1_2                    ((uint32_t)0x00000020) 

#define ADC_SMPR2_SMP2                      ((uint32_t)0x000001C0)                     /*!< ADC channel 2 sampling time selection  */
#define ADC_SMPR2_SMP2_0                    ((uint32_t)0x00000040) 
#define ADC_SMPR2_SMP2_1                    ((uint32_t)0x00000080) 
#define ADC_SMPR2_SMP2_2                    ((uint32_t)0x00000100) 

#define ADC_SMPR2_SMP3                      ((uint32_t)0x00000E00)                     /*!< ADC channel 3 sampling time selection  */
#define ADC_SMPR2_SMP3_0                    ((uint32_t)0x00000200) 
#define ADC_SMPR2_SMP3_1                    ((uint32_t)0x00000400) 
#define ADC_SMPR2_SMP3_2                    ((uint32_t)0x00000800) 

#define ADC_SMPR2_SMP4                      ((uint32_t)0x00007000)                     /*!< ADC channel 4 sampling time selection  */
#define ADC_SMPR2_SMP4_0                    ((uint32_t)0x00001000) 
#define ADC_SMPR2_SMP4_1                    ((uint32_t)0x00002000) 
#define ADC_SMPR2_SMP4_2                    ((uint32_t)0x00004000) 

#define ADC_SMPR2_SMP5                      ((uint32_t)0x00038000)                     /*!< ADC channel 5 sampling time selection  */
#define ADC_SMPR2_SMP5_0                    ((uint32_t)0x00008000) 
#define ADC_SMPR2_SMP5_1                    ((uint32_t)0x00010000) 
#define ADC_SMPR2_SMP5_2                    ((uint32_t)0x00020000) 

#define ADC_SMPR2_SMP6                      ((uint32_t)0x001C0000)                     /*!< ADC channel 6 sampling time selection  */
#define ADC_SMPR2_SMP6_0                    ((uint32_t)0x00040000) 
#define ADC_SMPR2_SMP6_1                    ((uint32_t)0x00080000) 
#define ADC_SMPR2_SMP6_2                    ((uint32_t)0x00100000) 

#define ADC_SMPR2_SMP7                      ((uint32_t)0x00E00000)                     /*!< ADC channel 7 sampling time selection  */
#define ADC_SMPR2_SMP7_0                    ((uint32_t)0x00200000) 
#define ADC_SMPR2_SMP7_1                    ((uint32_t)0x00400000) 
#define ADC_SMPR2_SMP7_2                    ((uint32_t)0x00800000) 

#define ADC_SMPR2_SMP8                      ((uint32_t)0x07000000)                     /*!< ADC channel 8 sampling time selection  */
#define ADC_SMPR2_SMP8_0                    ((uint32_t)0x01000000) 
#define ADC_SMPR2_SMP8_1                    ((uint32_t)0x02000000) 
#define ADC_SMPR2_SMP8_2                    ((uint32_t)0x04000000) 

#define ADC_SMPR2_SMP9                      ((uint32_t)0x38000000)                     /*!< ADC channel 9 sampling time selection  */
#define ADC_SMPR2_SMP9_0                    ((uint32_t)0x01000000) 
#define ADC_SMPR2_SMP9_1                    ((uint32_t)0x10000000) 
#define ADC_SMPR2_SMP9_2                    ((uint32_t)0x20000000) 
/******************  Bit definition for ADC_JOFR1 register  *******************/
#define ADC_JOFR1_JOFFSET1                  ((uint32_t)0x00000FFF)                     /*!< ADC group injected sequencer rank 1 offset value */
/******************  Bit definition for ADC_JOFR2 register  *******************/
#define ADC_JOFR2_JOFFSET2                  ((uint32_t)0x00000FFF)                     /*!< ADC group injected sequencer rank 2 offset value */
/******************  Bit definition for ADC_JOFR3 register  *******************/
#define ADC_JOFR3_JOFFSET3                  ((uint32_t)0x00000FFF)                     /*!< ADC group injected sequencer rank 3 offset value */
/******************  Bit definition for ADC_JOFR4 register  *******************/
#define ADC_JOFR4_JOFFSET4                  ((uint32_t)0x00000FFF)                     /*!< ADC group injected sequencer rank 4 offset value */
/*******************  Bit definition for ADC_HTR register  ********************/
#define ADC_HTR_HT                          ((uint32_t)0x00000FFF)                     /*!< ADC analog watchdog 1 threshold high */
#define ADC_HTR_CH                          ((uint32_t)0x001F0000)										 /*!< ADC analog watchdog 1 threshold high channel select*/
#define ADC_HTR_EN                          ((uint32_t)0x80000000)										 /*!< ADC analog watchdog 1 threshold high channel select enable*/
/*******************  Bit definition for ADC_LTR register  ********************/
#define ADC_LTR_LT                          ((uint32_t)0x00000FFF)                     /*!< ADC analog watchdog 1 threshold low */
#define ADC_LTR_CH                          ((uint32_t)0x001F0000)										 /*!< ADC analog watchdog 1 threshold low channel select*/
#define ADC_LTR_EN                          ((uint32_t)0x80000000)										 /*!< ADC analog watchdog 1 threshold low channel select enable*/
/*******************  Bit definition for ADC_SQR1 register  *******************/
#define ADC_SQR1_L                          ((uint32_t)0x00700000)                     /*!< ADC group regular sequencer scan length */
#define ADC_SQR1_L_0                        ((uint32_t)0x00100000)            
#define ADC_SQR1_L_1                        ((uint32_t)0x00200000)         
#define ADC_SQR1_L_2                        ((uint32_t)0x00400000)          
/*******************  Bit definition for ADC_SQR2 register  *******************/
#define ADC_SQR2_SQ7                        ((uint32_t)0x0000001F)                     /*!< ADC group regular sequencer rank 7 */
#define ADC_SQR2_SQ7_0                      ((uint32_t)0x00000001) 
#define ADC_SQR2_SQ7_1                      ((uint32_t)0x00000002) 
#define ADC_SQR2_SQ7_2                      ((uint32_t)0x00000004) 
#define ADC_SQR2_SQ7_3                      ((uint32_t)0x00000008) 
#define ADC_SQR2_SQ7_4                      ((uint32_t)0x00000010)

#define ADC_SQR2_SQ8                        ((uint32_t)0x000003E0)                     /*!< ADC group regular sequencer rank 8 */
#define ADC_SQR2_SQ8_0                      ((uint32_t)0x00000020) 
#define ADC_SQR2_SQ8_1                      ((uint32_t)0x00000040) 
#define ADC_SQR2_SQ8_2                      ((uint32_t)0x00000080) 
#define ADC_SQR2_SQ8_3                      ((uint32_t)0x00000100) 
#define ADC_SQR2_SQ8_4                      ((uint32_t)0x00000200) 
/*******************  Bit definition for ADC_SQR3 register  *******************/
#define ADC_SQR3_SQ1                        ((uint32_t)0x0000001F)                     /*!< ADC group regular sequencer rank 1 */
#define ADC_SQR3_SQ1_0                      ((uint32_t)0x00000001)
#define ADC_SQR3_SQ1_1                      ((uint32_t)0x00000002)
#define ADC_SQR3_SQ1_2                      ((uint32_t)0x00000004)
#define ADC_SQR3_SQ1_3                      ((uint32_t)0x00000008)
#define ADC_SQR3_SQ1_4                      ((uint32_t)0x00000010)

#define ADC_SQR3_SQ2                        ((uint32_t)0x000003E0)                     /*!< ADC group regular sequencer rank 2 */
#define ADC_SQR3_SQ2_0                      ((uint32_t)0x00000020)
#define ADC_SQR3_SQ2_1                      ((uint32_t)0x00000040)
#define ADC_SQR3_SQ2_2                      ((uint32_t)0x00000080) 
#define ADC_SQR3_SQ2_3                      ((uint32_t)0x00000100) 
#define ADC_SQR3_SQ2_4                      ((uint32_t)0x00000200) 

#define ADC_SQR3_SQ3                        ((uint32_t)0x00007C00)                     /*!< ADC group regular sequencer rank 3 */
#define ADC_SQR3_SQ3_0                      ((uint32_t)0x00000400) 
#define ADC_SQR3_SQ3_1                      ((uint32_t)0x00000800) 
#define ADC_SQR3_SQ3_2                      ((uint32_t)0x00001000) 
#define ADC_SQR3_SQ3_3                      ((uint32_t)0x00002000) 
#define ADC_SQR3_SQ3_4                      ((uint32_t)0x00004000) 

#define ADC_SQR3_SQ4                        ((uint32_t)0x000F8000)                     /*!< ADC group regular sequencer rank 4 */
#define ADC_SQR3_SQ4_0                      ((uint32_t)0x00008000) 
#define ADC_SQR3_SQ4_1                      ((uint32_t)0x00010000) 
#define ADC_SQR3_SQ4_2                      ((uint32_t)0x00020000) 
#define ADC_SQR3_SQ4_3                      ((uint32_t)0x00040000) 
#define ADC_SQR3_SQ4_4                      ((uint32_t)0x00080000) 

#define ADC_SQR3_SQ5                        ((uint32_t)0x01F00000)                     /*!< ADC group regular sequencer rank 5 */
#define ADC_SQR3_SQ5_0                      ((uint32_t)0x00100000) 
#define ADC_SQR3_SQ5_1                      ((uint32_t)0x00200000) 
#define ADC_SQR3_SQ5_2                      ((uint32_t)0x00400000) 
#define ADC_SQR3_SQ5_3                      ((uint32_t)0x00800000) 
#define ADC_SQR3_SQ5_4                      ((uint32_t)0x01000000) 

#define ADC_SQR3_SQ6                        ((uint32_t)0x3E000000)                     /*!< ADC group regular sequencer rank 6 */
#define ADC_SQR3_SQ6_0                      ((uint32_t)0x02000000)
#define ADC_SQR3_SQ6_1                      ((uint32_t)0x04000000) 
#define ADC_SQR3_SQ6_2                      ((uint32_t)0x08000000) 
#define ADC_SQR3_SQ6_3                      ((uint32_t)0x10000000) 
#define ADC_SQR3_SQ6_4                      ((uint32_t)0x20000000) 

/*******************  Bit definition for ADC_JSQR register  *******************/
#define ADC_JSQR_JSQ1                       ((uint32_t)0x0000001F)                     /*!< ADC group injected sequencer rank 1 */
#define ADC_JSQR_JSQ1_0                     ((uint32_t)0x00000001) 
#define ADC_JSQR_JSQ1_1                     ((uint32_t)0x00000002) 
#define ADC_JSQR_JSQ1_2                     ((uint32_t)0x00000004) 
#define ADC_JSQR_JSQ1_3                     ((uint32_t)0x00000008) 
#define ADC_JSQR_JSQ1_4                     ((uint32_t)0x00000010) 

#define ADC_JSQR_JSQ2                       ((uint32_t)0x000003E0)                     /*!< ADC group injected sequencer rank 2 */
#define ADC_JSQR_JSQ2_0                     ((uint32_t)0x00000020)
#define ADC_JSQR_JSQ2_1                     ((uint32_t)0x00000040) 
#define ADC_JSQR_JSQ2_2                     ((uint32_t)0x00000080)
#define ADC_JSQR_JSQ2_3                     ((uint32_t)0x00000100) 
#define ADC_JSQR_JSQ2_4                     ((uint32_t)0x00000200)

#define ADC_JSQR_JSQ3                       ((uint32_t)0x00007C00)                     /*!< ADC group injected sequencer rank 3 */
#define ADC_JSQR_JSQ3_0                     ((uint32_t)0x00000400) 
#define ADC_JSQR_JSQ3_1                     ((uint32_t)0x00000800) 
#define ADC_JSQR_JSQ3_2                     ((uint32_t)0x00001000) 
#define ADC_JSQR_JSQ3_3                     ((uint32_t)0x00002000) 
#define ADC_JSQR_JSQ3_4                     ((uint32_t)0x00004000) 

#define ADC_JSQR_JSQ4                       ((uint32_t)0x000F8000)                     /*!< ADC group injected sequencer rank 4 */
#define ADC_JSQR_JSQ4_0                     ((uint32_t)0x00008000) 
#define ADC_JSQR_JSQ4_1                     ((uint32_t)0x00010000)
#define ADC_JSQR_JSQ4_2                     ((uint32_t)0x00020000)
#define ADC_JSQR_JSQ4_3                     ((uint32_t)0x00040000)
#define ADC_JSQR_JSQ4_4                     ((uint32_t)0x00080000)

#define ADC_JSQR_JL                         ((uint32_t)0x00300000)                      /*!< ADC group injected sequencer scan length */
#define ADC_JSQR_JL_0                       ((uint32_t)0x00100000)  
#define ADC_JSQR_JL_1                       ((uint32_t)0x00200000)  
/*******************  Bit definition for ADC_JDR1 register  *******************/
#define ADC_JDR1_JDATA                      ((uint32_t)0x0000FFFF)                      /*!< ADC group injected sequencer rank 1 conversion data */
/*******************  Bit definition for ADC_JDR2 register  *******************/
#define ADC_JDR2_JDATA                      ((uint32_t)0x0000FFFF)                      /*!< ADC group injected sequencer rank 2 conversion data */
/*******************  Bit definition for ADC_JDR3 register  *******************/
#define ADC_JDR3_JDATA                      ((uint32_t)0x0000FFFF)                      /*!< ADC group injected sequencer rank 3 conversion data */
/*******************  Bit definition for ADC_JDR4 register  *******************/
#define ADC_JDR4_JDATA                      ((uint32_t)0x0000FFFF)                      /*!< ADC group injected sequencer rank 4 conversion data */
/********************  Bit definition for ADC_DR register  ********************/
#define ADC_DR_DATA                         ((uint32_t)0x0000FFFF)                      /*!< ADC group regular conversion data */                     /*!< ADC group regular conversion data for ADC slave, in multimode */
/********************  Bit definition for ADC_DR(1-8) register  ********************/
#define ADC_DR_DATA1                        ((uint32_t)0x0000FFFF)                      /*!< ADC group regular conversion data */
#define ADC_DR_DATA2                        ((uint32_t)0x0000FFFF)
#define ADC_DR_DATA3                        ((uint32_t)0x0000FFFF)
#define ADC_DR_DATA4                        ((uint32_t)0x0000FFFF)
#define ADC_DR_DATA5                        ((uint32_t)0x0000FFFF)
#define ADC_DR_DATA6                        ((uint32_t)0x0000FFFF)
#define ADC_DR_DATA7                        ((uint32_t)0x0000FFFF)
#define ADC_DR_DATA8                        ((uint32_t)0x0000FFFF)
/*******************  Bit definition for ADC_CAL register  *******************/
#define ADC_CAL_DATA                        ((uint32_t)0x0000007F)                      /*!< ADC calibration data */
/*******************  Bit definition for ADC_SMPR3 register  *******************/
#define ADC_SMPR3_SMP20                     ((uint32_t)0x00000007)    
#define ADC_SMPR3_SMP20_0                   ((uint32_t)0x00000001)
#define ADC_SMPR3_SMP20_1                   ((uint32_t)0x00000002)
#define ADC_SMPR3_SMP20_2                   ((uint32_t)0x00000004)

#define ADC_SMPR3_SMP21                     ((uint32_t)0x00000038)    
#define ADC_SMPR3_SMP21_0                   ((uint32_t)0x00000008)
#define ADC_SMPR3_SMP21_1                   ((uint32_t)0x00000010)
#define ADC_SMPR3_SMP21_2                   ((uint32_t)0x00000020)

#define ADC_SMPR3_SMP22                     ((uint32_t)0x000001C0)    
#define ADC_SMPR3_SMP22_0                   ((uint32_t)0x00000040)
#define ADC_SMPR3_SMP22_1                   ((uint32_t)0x00000080)
#define ADC_SMPR3_SMP22_2                   ((uint32_t)0x00000100)

#define ADC_SMPR3_SMP23                     ((uint32_t)0x00000E00)    
#define ADC_SMPR3_SMP23_0                   ((uint32_t)0x00000200)
#define ADC_SMPR3_SMP23_1                   ((uint32_t)0x00000400)
#define ADC_SMPR3_SMP23_2                   ((uint32_t)0x00000800)

#define ADC_CR1_JAUTO_INDEPENDENT       ((uint32_t)0x00000000) 
#define ADC_CR1_JAUTO_FROM_REG          (ADC_CR1_JAUTO)

#define ADC_EOC_OPT                     ((uint32_t)0x00000020) 
#define ADC_EOC_OPT_DISABLE             ((uint32_t)0x00000000) 
#define ADC_EOC_OPT_ENABLE              (ADC_EOC_OPT)

#define ADC_TPS_OFFSET                  ((uint32_t)0x000000FF)

#define ADC_CR3_PRG_RDY                  ((uint32_t)0x00000001)
#define ADC_CR3_CFG_UPD                  ((uint32_t)0x00000002)

/*
  * @brief  Driver macro reserved for internal use: isolate bits with the
  *         selected mask and shift them to the register LSB
  *         (shift mask on register position bit 0).
  * @param  __BITS__ Bits in register 32 bits
  * @param  __MASK__ Mask in register 32 bits
  * @retval Bits in register 32 bits
 */
#define __ADC_MASK_SHIFT(__BITS__, __MASK__)                                   \
  (((__BITS__) & (__MASK__)) >> POSITION_VAL((__MASK__)))

/*
  * @brief  Driver macro reserved for internal use: set a pointer to
  *         a register from a register basis from which an offset
  *         is applied.
  * @param  __REG__ Register basis from which the offset is applied.
  * @param  __REG_OFFFSET__ Offset to be applied (unit: number of registers).
  * @retval Pointer to register address
  */
#define __ADC_PTR_REG_OFFSET(__REG__, __REG_OFFFSET__)                         \
 ((uint32_t *)((uint32_t) ((uint32_t)(&(__REG__)) + ((__REG_OFFFSET__) << 2U))))
   
/**********************  Bit definition for option ***********************/ 
#define ADC_CHANNEL_0_NUMBER            ((uint32_t)0x00000000)
#define ADC_CHANNEL_1_NUMBER            (                                                                        ADC_CR1_AWDCH_0)
#define ADC_CHANNEL_2_NUMBER            (                                                      ADC_CR1_AWDCH_1                  )
#define ADC_CHANNEL_3_NUMBER            (                                                      ADC_CR1_AWDCH_1 | ADC_CR1_AWDCH_0)
#define ADC_CHANNEL_4_NUMBER            (                                    ADC_CR1_AWDCH_2                                    )
#define ADC_CHANNEL_5_NUMBER            (                                    ADC_CR1_AWDCH_2                   | ADC_CR1_AWDCH_0)
#define ADC_CHANNEL_6_NUMBER            (                                    ADC_CR1_AWDCH_2 | ADC_CR1_AWDCH_1                  )
#define ADC_CHANNEL_7_NUMBER            (                                    ADC_CR1_AWDCH_2 | ADC_CR1_AWDCH_1 | ADC_CR1_AWDCH_0)
#define ADC_CHANNEL_8_NUMBER            (                  ADC_CR1_AWDCH_3                                                      )
#define ADC_CHANNEL_9_NUMBER            (                  ADC_CR1_AWDCH_3                                     | ADC_CR1_AWDCH_0)
#define ADC_CHANNEL_10_NUMBER           (                  ADC_CR1_AWDCH_3 |                   ADC_CR1_AWDCH_1                  )
#define ADC_CHANNEL_11_NUMBER           (                  ADC_CR1_AWDCH_3 |                   ADC_CR1_AWDCH_1 | ADC_CR1_AWDCH_0)
#define ADC_CHANNEL_12_NUMBER           (                  ADC_CR1_AWDCH_3 | ADC_CR1_AWDCH_2                                    )
#define ADC_CHANNEL_13_NUMBER           (                  ADC_CR1_AWDCH_3 | ADC_CR1_AWDCH_2                   | ADC_CR1_AWDCH_0)
#define ADC_CHANNEL_14_NUMBER           (                  ADC_CR1_AWDCH_3 | ADC_CR1_AWDCH_2 | ADC_CR1_AWDCH_1                  )
#define ADC_CHANNEL_15_NUMBER           (                  ADC_CR1_AWDCH_3 | ADC_CR1_AWDCH_2 | ADC_CR1_AWDCH_1 | ADC_CR1_AWDCH_0)
#define ADC_CHANNEL_16_NUMBER           (ADC_CR1_AWDCH_4                                                                        )
#define ADC_CHANNEL_17_NUMBER           (ADC_CR1_AWDCH_4 |                                                       ADC_CR1_AWDCH_0)
#define ADC_CHANNEL_18_NUMBER           (ADC_CR1_AWDCH_4 |                                     ADC_CR1_AWDCH_1                  )
#define ADC_CHANNEL_19_NUMBER           (ADC_CR1_AWDCH_4 |                                     ADC_CR1_AWDCH_1 | ADC_CR1_AWDCH_0)
#define ADC_CHANNEL_20_NUMBER           (ADC_CR1_AWDCH_4 |                   ADC_CR1_AWDCH_2                                    )
#define ADC_CHANNEL_21_NUMBER           (ADC_CR1_AWDCH_4 |                   ADC_CR1_AWDCH_2                   | ADC_CR1_AWDCH_0)
#define ADC_CHANNEL_22_NUMBER           (ADC_CR1_AWDCH_4 |                   ADC_CR1_AWDCH_2 | ADC_CR1_AWDCH_1                  )
#define ADC_CHANNEL_23_NUMBER           (ADC_CR1_AWDCH_4 |                   ADC_CR1_AWDCH_2 | ADC_CR1_AWDCH_1 | ADC_CR1_AWDCH_0)

#define ADC_CR1_SCAN_DISABLE            ((uint32_t)0x00000000) 
#define ADC_CR1_SCAN_ENABLE             (ADC_CR1_SCAN)

#define ADC_CR1_AWD_ENABLE              ((uint32_t)0x00800000)
#define ADC_CR1_AWD_DISABLE             ((uint32_t)0x00000000)

#define ADC_CR1_JAWD_ENABLE              ADC_CR1_AWDEN           
#define ADC_CR1_AWD_DISABLE              ((uint32_t)0x00000000)

#define ADC_AWD_DISABLE                 ((uint32_t)0x00000000)                                                                                 
#define ADC_AWD_ALL_CHANNELS_REG        (                                        ADC_CR1_AWDEN                 ) 
#define ADC_AWD_ALL_CHANNELS_INJ        (                       ADC_CR1_JAWDEN                                 ) 
#define ADC_AWD_ALL_CHANNELS_REG_INJ    (                       ADC_CR1_JAWDEN | ADC_CR1_AWDEN                 ) 
#define ADC_AWD_CHANNEL_0_REG           (ADC_CHANNEL_0_NUMBER                  | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_0_INJ           (ADC_CHANNEL_0_NUMBER | ADC_CR1_JAWDEN                 | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_0_REG_INJ       (ADC_CHANNEL_0_NUMBER | ADC_CR1_JAWDEN | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_1_REG           (ADC_CHANNEL_1_NUMBER | ADC_CR1_AWDEN                  | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_1_INJ           (ADC_CHANNEL_1_NUMBER | ADC_CR1_JAWDEN                 | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_1_REG_INJ       (ADC_CHANNEL_1_NUMBER | ADC_CR1_JAWDEN | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_2_REG           (ADC_CHANNEL_2_NUMBER                  | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_2_INJ           (ADC_CHANNEL_2_NUMBER | ADC_CR1_JAWDEN                 | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_2_REG_INJ       (ADC_CHANNEL_2_NUMBER | ADC_CR1_JAWDEN | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_3_REG           (ADC_CHANNEL_3_NUMBER                  | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_3_INJ           (ADC_CHANNEL_3_NUMBER | ADC_CR1_JAWDEN                 | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_3_REG_INJ       (ADC_CHANNEL_3_NUMBER | ADC_CR1_JAWDEN | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_4_REG           (ADC_CHANNEL_4_NUMBER                  | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_4_INJ           (ADC_CHANNEL_4_NUMBER | ADC_CR1_JAWDEN                 | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_4_REG_INJ       (ADC_CHANNEL_4_NUMBER | ADC_CR1_JAWDEN | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_5_REG           (ADC_CHANNEL_5_NUMBER                  | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_5_INJ           (ADC_CHANNEL_5_NUMBER | ADC_CR1_JAWDEN                 | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_5_REG_INJ       (ADC_CHANNEL_5_NUMBER | ADC_CR1_JAWDEN | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_6_REG           (ADC_CHANNEL_6_NUMBER                  | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_6_INJ           (ADC_CHANNEL_6_NUMBER | ADC_CR1_JAWDEN                 | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_6_REG_INJ       (ADC_CHANNEL_6_NUMBER | ADC_CR1_JAWDEN | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_7_REG           (ADC_CHANNEL_7_NUMBER                  | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_7_INJ           (ADC_CHANNEL_7_NUMBER | ADC_CR1_JAWDEN                 | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_7_REG_INJ       (ADC_CHANNEL_7_NUMBER | ADC_CR1_JAWDEN | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_8_REG           (ADC_CHANNEL_8_NUMBER                  | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_8_INJ           (ADC_CHANNEL_8_NUMBER | ADC_CR1_JAWDEN                 | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_8_REG_INJ       (ADC_CHANNEL_8_NUMBER | ADC_CR1_JAWDEN | ADC_CR1_AWDEN | ADC_CR1_AWDSGL)  
#define ADC_AWD_CHANNEL_9_REG           (ADC_CHANNEL_9_NUMBER                  | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_9_INJ           (ADC_CHANNEL_9_NUMBER | ADC_CR1_JAWDEN                 | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_9_REG_INJ       (ADC_CHANNEL_9_NUMBER | ADC_CR1_JAWDEN | ADC_CR1_AWDEN | ADC_CR1_AWDSGL)  
#define ADC_AWD_CHANNEL_10_REG          (ADC_CHANNEL_10_NUMBER                  | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_10_INJ          (ADC_CHANNEL_10_NUMBER | ADC_CR1_JAWDEN                 | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_10_REG_INJ      (ADC_CHANNEL_10_NUMBER | ADC_CR1_JAWDEN | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_11_REG          (ADC_CHANNEL_11_NUMBER                  | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_11_INJ          (ADC_CHANNEL_11_NUMBER | ADC_CR1_JAWDEN                 | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_11_REG_INJ      (ADC_CHANNEL_11_NUMBER | ADC_CR1_JAWDEN | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_12_REG          (ADC_CHANNEL_12_NUMBER                  | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_12_INJ          (ADC_CHANNEL_12_NUMBER | ADC_CR1_JAWDEN                 | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_12_REG_INJ      (ADC_CHANNEL_12_NUMBER | ADC_CR1_JAWDEN | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_13_REG          (ADC_CHANNEL_13_NUMBER                  | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_13_INJ          (ADC_CHANNEL_13_NUMBER | ADC_CR1_JAWDEN                 | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_13_REG_INJ      (ADC_CHANNEL_13_NUMBER | ADC_CR1_JAWDEN | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_14_REG          (ADC_CHANNEL_14_NUMBER                  | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_14_INJ          (ADC_CHANNEL_14_NUMBER | ADC_CR1_JAWDEN                 | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_14_REG_INJ      (ADC_CHANNEL_14_NUMBER | ADC_CR1_JAWDEN | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_15_REG          (ADC_CHANNEL_15_NUMBER                  | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_15_INJ          (ADC_CHANNEL_15_NUMBER | ADC_CR1_JAWDEN                 | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_15_REG_INJ      (ADC_CHANNEL_15_NUMBER | ADC_CR1_JAWDEN | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_16_REG          (ADC_CHANNEL_16_NUMBER                  | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_16_INJ          (ADC_CHANNEL_16_NUMBER | ADC_CR1_JAWDEN                 | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_16_REG_INJ      (ADC_CHANNEL_16_NUMBER | ADC_CR1_JAWDEN | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_17_REG          (ADC_CHANNEL_17_NUMBER                  | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_17_INJ          (ADC_CHANNEL_17_NUMBER | ADC_CR1_JAWDEN                 | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_17_REG_INJ      (ADC_CHANNEL_17_NUMBER | ADC_CR1_JAWDEN | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_18_REG          (ADC_CHANNEL_18_NUMBER                  | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_18_INJ          (ADC_CHANNEL_18_NUMBER | ADC_CR1_JAWDEN                 | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_18_REG_INJ      (ADC_CHANNEL_18_NUMBER | ADC_CR1_JAWDEN | ADC_CR1_AWDEN | ADC_CR1_AWDSGL)
#define ADC_AWD_CHANNEL_19_REG          (ADC_CHANNEL_19_NUMBER                  | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_19_INJ          (ADC_CHANNEL_19_NUMBER | ADC_CR1_JAWDEN                 | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_19_REG_INJ      (ADC_CHANNEL_19_NUMBER | ADC_CR1_JAWDEN | ADC_CR1_AWDEN | ADC_CR1_AWDSGL)
#define ADC_AWD_CHANNEL_20_REG          (ADC_CHANNEL_20_NUMBER                  | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_20_INJ          (ADC_CHANNEL_20_NUMBER | ADC_CR1_JAWDEN                 | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_20_REG_INJ      (ADC_CHANNEL_20_NUMBER | ADC_CR1_JAWDEN | ADC_CR1_AWDEN | ADC_CR1_AWDSGL)
#define ADC_AWD_CHANNEL_21_REG          (ADC_CHANNEL_21_NUMBER                  | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_21_INJ          (ADC_CHANNEL_21_NUMBER | ADC_CR1_JAWDEN                 | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_21_REG_INJ      (ADC_CHANNEL_21_NUMBER | ADC_CR1_JAWDEN | ADC_CR1_AWDEN | ADC_CR1_AWDSGL)
#define ADC_AWD_CHANNEL_22_REG          (ADC_CHANNEL_22_NUMBER                  | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_22_INJ          (ADC_CHANNEL_22_NUMBER | ADC_CR1_JAWDEN                 | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_22_REG_INJ      (ADC_CHANNEL_22_NUMBER | ADC_CR1_JAWDEN | ADC_CR1_AWDEN | ADC_CR1_AWDSGL)
#define ADC_AWD_CHANNEL_23_REG          (ADC_CHANNEL_23_NUMBER                  | ADC_CR1_AWDEN | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_23_INJ          (ADC_CHANNEL_23_NUMBER | ADC_CR1_JAWDEN                 | ADC_CR1_AWDSGL) 
#define ADC_AWD_CHANNEL_23_REG_INJ      (ADC_CHANNEL_23_NUMBER | ADC_CR1_JAWDEN | ADC_CR1_AWDEN | ADC_CR1_AWDSGL)

#define ADC_CR1_DISCONT_DISABLE         ((uint32_t)0x00000000)      
#define ADC_CR1_DISCONT_1RANK           (                                                        0)
#define ADC_CR1_DISCONT_2RANKS          (                                        ADC_CR1_DISCNUM_0)
#define ADC_CR1_DISCONT_3RANKS          (                    ADC_CR1_DISCNUM_1                    )
#define ADC_CR1_DISCONT_4RANKS          (                    ADC_CR1_DISCNUM_1 | ADC_CR1_DISCNUM_0) 
#define ADC_CR1_DISCONT_5RANKS          (ADC_CR1_DISCNUM_2                                        )
#define ADC_CR1_DISCONT_6RANKS          (ADC_CR1_DISCNUM_2                     | ADC_CR1_DISCNUM_0)
#define ADC_CR1_DISCONT_7RANKS          (ADC_CR1_DISCNUM_2 | ADC_CR1_DISCNUM_1                    )
#define ADC_CR1_DISCONT_8RANKS          (ADC_CR1_DISCNUM_2 | ADC_CR1_DISCNUM_1 | ADC_CR1_DISCNUM_0)

#define ADC_CR1_AWDFILT_DISABLE					((uint32_t)0x00000000)
#define ADC_CR1_AWDFILT_2LEVEL					(																				 ADC_CR1_AWDFILT_0)
#define ADC_CR1_AWDFILT_3LEVEL					(										 ADC_CR1_AWDFILT_1										)
#define ADC_CR1_AWDFILT_4LEVEL					(                    ADC_CR1_AWDFILT_1 | ADC_CR1_AWDFILT_0)
#define ADC_CR1_AWDFILT_5LEVEL					(ADC_CR1_AWDFILT_2                                        )
#define ADC_CR1_AWDFILT_6LEVEL					(ADC_CR1_AWDFILT_2 |                     ADC_CR1_AWDFILT_0)
#define ADC_CR1_AWDFILT_7LEVEL					(ADC_CR1_AWDFILT_2 | ADC_CR1_AWDFILT_1                    )
#define ADC_CR1_AWDFILT_8LEVEL					(ADC_CR1_AWDFILT_2 | ADC_CR1_AWDFILT_1 | ADC_CR1_AWDFILT_0)

#define ADC_CR1_DISCEN_ENABLE            ((uint32_t)0x00000800)
#define ADC_CR1_DISCEN_DISABLE           ((uint32_t)0x00000000)

#define ADC_CR1_JDISCEN_ENABLE           ((uint32_t)0x00001000) 
#define ADC_CR1_JDISCEN_DISABLE          ((uint32_t)0x00000000)

#define ADC_CR2_CONT_SINGLE             ((uint32_t)0x00000000) 
#define ADC_CR2_CONT_CONTINUOUS         (ADC_CR2_CONT)

#define ADC_CR2_ALIGN_RIGHT             ((uint32_t)0x00000000) 
#define ADC_CR2_ALIGN_LEFT              (ADC_CR2_ALIGN)
    
#define ADC_CR2_JEXTSEL_INSOURCE        ((uint32_t)0x00000000)   
#define ADC_CR2_JEXTSEL_TIM8_TRGO1      (                                                                                ADC_CR2_JEXTTRIG)         
#define ADC_CR2_JEXTSEL_TIM8_CC4        (                                                            ADC_CR2_JEXTSEL_0 | ADC_CR2_JEXTTRIG) 
#define ADC_CR2_JEXTSEL_TIM2_TRGO       (                                        ADC_CR2_JEXTSEL_1                     | ADC_CR2_JEXTTRIG) 
#define ADC_CR2_JEXTSEL_TIM2_CC1        (                                        ADC_CR2_JEXTSEL_1 | ADC_CR2_JEXTSEL_0 | ADC_CR2_JEXTTRIG) 
#define ADC_CR2_JEXTSEL_TIM3_CC4        (                    ADC_CR2_JEXTSEL_2                                         | ADC_CR2_JEXTTRIG) 
#define ADC_CR2_JEXTSEL_TIM3_CC3        (                    ADC_CR2_JEXTSEL_2                     | ADC_CR2_JEXTSEL_0 | ADC_CR2_JEXTTRIG) 
#define ADC_CR2_JEXTSEL_EXTI2           (                    ADC_CR2_JEXTSEL_2 | ADC_CR2_JEXTSEL_1                     | ADC_CR2_JEXTTRIG) 
#define ADC_CR2_JEXTSEL_JSWSTART        (                    ADC_CR2_JEXTSEL_2 | ADC_CR2_JEXTSEL_1 | ADC_CR2_JEXTSEL_0 | ADC_CR2_JEXTTRIG) 
#define ADC_CR2_JEXTSEL_TIM8_TRGO2      (ADC_CR2_JEXTSEL_3                                                             | ADC_CR2_JEXTTRIG) 
#define ADC_CR2_JEXTSEL_TIM8_CC2        (ADC_CR2_JEXTSEL_3 |                                          ADC_CR2_JEXTSEL_0| ADC_CR2_JEXTTRIG) 
#define ADC_CR2_JEXTSEL_TIM8_CC5_CC6    (ADC_CR2_JEXTSEL_3 |                      ADC_CR2_JEXTSEL_1                    | ADC_CR2_JEXTTRIG) 
#define ADC_CR2_JEXTSEL_TIM8_CC4_CC6    (ADC_CR2_JEXTSEL_3 |                      ADC_CR2_JEXTSEL_1 | ADC_CR2_JEXTSEL_0| ADC_CR2_JEXTTRIG) 
#define ADC_CR2_JEXTSEL_TIM8_CC4_CC5    (ADC_CR2_JEXTSEL_3 | ADC_CR2_JEXTSEL_2                                         | ADC_CR2_JEXTTRIG) 
#define ADC_CR2_JEXTSEL_TIM8_CC6        (ADC_CR2_JEXTSEL_3 | ADC_CR2_JEXTSEL_2                      | ADC_CR2_JEXTSEL_0| ADC_CR2_JEXTTRIG) 
#define	ADC_CR2_JEXTSEL_TIM15_TRGO			(ADC_CR2_JEXTSEL_3 | ADC_CR2_JEXTSEL_2 |  ADC_CR2_JEXTSEL_1                    | ADC_CR2_JEXTTRIG)
	
#define ADC_CR2_EXTSEL_INSOURCE          ((uint32_t)0x00000000)   
#define ADC_CR2_EXTSEL_TIM8_TRGO2        (                                                         ADC_CR2_EXTTRIG)         
#define ADC_CR2_EXTSEL_TIM8_CC4_CC5      (                                      ADC_CR2_EXTSEL_0 | ADC_CR2_EXTTRIG) 
#define ADC_CR2_EXTSEL_TIM2_CC3_CC4      (                   ADC_CR2_EXTSEL_1                    | ADC_CR2_EXTTRIG) 
#define ADC_CR2_EXTSEL_TIM2_CC4          (                   ADC_CR2_EXTSEL_1 | ADC_CR2_EXTSEL_0 | ADC_CR2_EXTTRIG) 
#define ADC_CR2_EXTSEL_TIM3_CC2          (ADC_CR2_EXTSEL_2                                       | ADC_CR2_EXTTRIG) 
#define ADC_CR2_EXTSEL_TIM3_TRGO         (ADC_CR2_EXTSEL_2                    | ADC_CR2_EXTSEL_0 | ADC_CR2_EXTTRIG) 
#define ADC_CR2_EXTSEL_EXTI3             (ADC_CR2_EXTSEL_2 | ADC_CR2_EXTSEL_1                    | ADC_CR2_EXTTRIG) 
#define ADC_CR2_EXTSEL_SWSTART           (ADC_CR2_EXTSEL_2 | ADC_CR2_EXTSEL_1 | ADC_CR2_EXTSEL_0 | ADC_CR2_EXTTRIG) 

#define ADC_SAMPLINGTIME_2p5CYCLES      ((uint32_t)0x00000000)
#define ADC_SAMPLINGTIME_6p5CYCLES      (                                      ADC_SMPR2_SMP0_0)
#define ADC_SAMPLINGTIME_11p5CYCLES     (                   ADC_SMPR2_SMP0_1                   )
#define ADC_SAMPLINGTIME_17p5CYCLES     (                   ADC_SMPR2_SMP0_1 | ADC_SMPR2_SMP0_0)
#define ADC_SAMPLINGTIME_25p5CYCLES     (ADC_SMPR2_SMP0_2                                      )
#define ADC_SAMPLINGTIME_35p5CYCLES     (ADC_SMPR2_SMP0_2                    | ADC_SMPR2_SMP0_0)
#define ADC_SAMPLINGTIME_48p5CYCLES     (ADC_SMPR2_SMP0_2 | ADC_SMPR2_SMP0_1                   )
#define ADC_SAMPLINGTIME_640p5CYCLES    (ADC_SMPR2_SMP0_2 | ADC_SMPR2_SMP0_1 | ADC_SMPR2_SMP0_0)

#define ADC_SMPR1_REGOFFSET              ((uint32_t)0x00000000)
#define ADC_SMPR2_REGOFFSET              ((uint32_t)0x00000020)
#define ADC_SMPR3_REGOFFSET              ((uint32_t)0x000002E0)
#define ADC_CHANNEL_SMPRX_REGOFFSET_MASK (ADC_SMPR1_REGOFFSET | ADC_SMPR2_REGOFFSET | ADC_SMPR3_REGOFFSET)

#define ADC_SMPR_BITOFFSET_MASK      ((uint32_t)0x01F00000)
#define ADC_SMPR_BITOFFSET_POS       (20U)   

#define ADC_SMP_0_BITOFFSET  ( 0U)
#define ADC_SMP_1_BITOFFSET  ( 3U)
#define ADC_SMP_2_BITOFFSET  ( 6U)
#define ADC_SMP_3_BITOFFSET  ( 9U) 
#define ADC_SMP_4_BITOFFSET  (12U) 
#define ADC_SMP_5_BITOFFSET  (15U) 
#define ADC_SMP_6_BITOFFSET  (18U)
#define ADC_SMP_7_BITOFFSET  (21U) 
#define ADC_SMP_8_BITOFFSET  (24U) 
#define ADC_SMP_9_BITOFFSET  (27U) 
#define ADC_SMP_10_BITOFFSET ( 0U) 
#define ADC_SMP_11_BITOFFSET ( 3U)
#define ADC_SMP_12_BITOFFSET ( 6U)
#define ADC_SMP_13_BITOFFSET ( 9U) 
#define ADC_SMP_14_BITOFFSET (12U) 
#define ADC_SMP_15_BITOFFSET (15U) 
#define ADC_SMP_16_BITOFFSET (18U)
#define ADC_SMP_17_BITOFFSET (21U) 
#define ADC_SMP_18_BITOFFSET (24U) 
#define ADC_SMP_19_BITOFFSET (27U) 
#define ADC_SMP_20_BITOFFSET ( 0U)
#define ADC_SMP_21_BITOFFSET ( 3U)
#define ADC_SMP_22_BITOFFSET ( 6U) 
#define ADC_SMP_23_BITOFFSET ( 9U) 

#define ADC_CHANNEL_0_SMP        (ADC_SMPR2_REGOFFSET | (ADC_SMP_0_BITOFFSET  << ADC_SMPR_BITOFFSET_POS))
#define ADC_CHANNEL_1_SMP        (ADC_SMPR2_REGOFFSET | (ADC_SMP_1_BITOFFSET  << ADC_SMPR_BITOFFSET_POS))
#define ADC_CHANNEL_2_SMP        (ADC_SMPR2_REGOFFSET | (ADC_SMP_2_BITOFFSET  << ADC_SMPR_BITOFFSET_POS))
#define ADC_CHANNEL_3_SMP        (ADC_SMPR2_REGOFFSET | (ADC_SMP_3_BITOFFSET  << ADC_SMPR_BITOFFSET_POS))
#define ADC_CHANNEL_4_SMP        (ADC_SMPR2_REGOFFSET | (ADC_SMP_4_BITOFFSET  << ADC_SMPR_BITOFFSET_POS))
#define ADC_CHANNEL_5_SMP        (ADC_SMPR2_REGOFFSET | (ADC_SMP_5_BITOFFSET  << ADC_SMPR_BITOFFSET_POS))
#define ADC_CHANNEL_6_SMP        (ADC_SMPR2_REGOFFSET | (ADC_SMP_6_BITOFFSET  << ADC_SMPR_BITOFFSET_POS))
#define ADC_CHANNEL_7_SMP        (ADC_SMPR2_REGOFFSET | (ADC_SMP_7_BITOFFSET  << ADC_SMPR_BITOFFSET_POS))
#define ADC_CHANNEL_8_SMP        (ADC_SMPR2_REGOFFSET | (ADC_SMP_8_BITOFFSET  << ADC_SMPR_BITOFFSET_POS))
#define ADC_CHANNEL_9_SMP        (ADC_SMPR2_REGOFFSET | (ADC_SMP_9_BITOFFSET  << ADC_SMPR_BITOFFSET_POS))
#define ADC_CHANNEL_10_SMP       (ADC_SMPR1_REGOFFSET | (ADC_SMP_10_BITOFFSET << ADC_SMPR_BITOFFSET_POS))
#define ADC_CHANNEL_11_SMP       (ADC_SMPR1_REGOFFSET | (ADC_SMP_11_BITOFFSET << ADC_SMPR_BITOFFSET_POS))
#define ADC_CHANNEL_12_SMP       (ADC_SMPR1_REGOFFSET | (ADC_SMP_12_BITOFFSET << ADC_SMPR_BITOFFSET_POS))
#define ADC_CHANNEL_13_SMP       (ADC_SMPR1_REGOFFSET | (ADC_SMP_13_BITOFFSET << ADC_SMPR_BITOFFSET_POS))
#define ADC_CHANNEL_14_SMP       (ADC_SMPR1_REGOFFSET | (ADC_SMP_14_BITOFFSET << ADC_SMPR_BITOFFSET_POS))
#define ADC_CHANNEL_15_SMP       (ADC_SMPR1_REGOFFSET | (ADC_SMP_15_BITOFFSET << ADC_SMPR_BITOFFSET_POS))
#define ADC_CHANNEL_16_SMP       (ADC_SMPR1_REGOFFSET | (ADC_SMP_16_BITOFFSET << ADC_SMPR_BITOFFSET_POS))
#define ADC_CHANNEL_17_SMP       (ADC_SMPR1_REGOFFSET | (ADC_SMP_17_BITOFFSET << ADC_SMPR_BITOFFSET_POS))
#define ADC_CHANNEL_18_SMP       (ADC_SMPR1_REGOFFSET | (ADC_SMP_18_BITOFFSET << ADC_SMPR_BITOFFSET_POS))
#define ADC_CHANNEL_19_SMP       (ADC_SMPR1_REGOFFSET | (ADC_SMP_19_BITOFFSET << ADC_SMPR_BITOFFSET_POS))
#define ADC_CHANNEL_20_SMP       (ADC_SMPR3_REGOFFSET | (ADC_SMP_20_BITOFFSET << ADC_SMPR_BITOFFSET_POS))
#define ADC_CHANNEL_21_SMP       (ADC_SMPR3_REGOFFSET | (ADC_SMP_21_BITOFFSET << ADC_SMPR_BITOFFSET_POS))
#define ADC_CHANNEL_22_SMP       (ADC_SMPR3_REGOFFSET | (ADC_SMP_22_BITOFFSET << ADC_SMPR_BITOFFSET_POS))
#define ADC_CHANNEL_23_SMP       (ADC_SMPR3_REGOFFSET | (ADC_SMP_23_BITOFFSET << ADC_SMPR_BITOFFSET_POS))

#define ADC_CHANNEL_0            (ADC_CHANNEL_0_NUMBER  | ADC_CHANNEL_0_SMP)
#define ADC_CHANNEL_1            (ADC_CHANNEL_1_NUMBER  | ADC_CHANNEL_1_SMP)
#define ADC_CHANNEL_2            (ADC_CHANNEL_2_NUMBER  | ADC_CHANNEL_2_SMP)
#define ADC_CHANNEL_3            (ADC_CHANNEL_3_NUMBER  | ADC_CHANNEL_3_SMP)
#define ADC_CHANNEL_4            (ADC_CHANNEL_4_NUMBER  | ADC_CHANNEL_4_SMP)
#define ADC_CHANNEL_5            (ADC_CHANNEL_5_NUMBER  | ADC_CHANNEL_5_SMP)
#define ADC_CHANNEL_6            (ADC_CHANNEL_6_NUMBER  | ADC_CHANNEL_6_SMP)
#define ADC_CHANNEL_7            (ADC_CHANNEL_7_NUMBER  | ADC_CHANNEL_7_SMP)
#define ADC_CHANNEL_8            (ADC_CHANNEL_8_NUMBER  | ADC_CHANNEL_8_SMP)
#define ADC_CHANNEL_9            (ADC_CHANNEL_9_NUMBER  | ADC_CHANNEL_9_SMP)
#define ADC_CHANNEL_10           (ADC_CHANNEL_10_NUMBER | ADC_CHANNEL_10_SMP)
#define ADC_CHANNEL_11           (ADC_CHANNEL_11_NUMBER | ADC_CHANNEL_11_SMP)
#define ADC_CHANNEL_12           (ADC_CHANNEL_12_NUMBER | ADC_CHANNEL_12_SMP)
#define ADC_CHANNEL_13           (ADC_CHANNEL_13_NUMBER | ADC_CHANNEL_13_SMP)
#define ADC_CHANNEL_14           (ADC_CHANNEL_14_NUMBER | ADC_CHANNEL_14_SMP)
#define ADC_CHANNEL_15           (ADC_CHANNEL_15_NUMBER | ADC_CHANNEL_15_SMP)
#define ADC_CHANNEL_16           (ADC_CHANNEL_16_NUMBER | ADC_CHANNEL_16_SMP)
#define ADC_CHANNEL_17           (ADC_CHANNEL_17_NUMBER | ADC_CHANNEL_17_SMP)
#define ADC_CHANNEL_18           (ADC_CHANNEL_18_NUMBER | ADC_CHANNEL_18_SMP)
#define ADC_CHANNEL_19           (ADC_CHANNEL_19_NUMBER | ADC_CHANNEL_19_SMP)
#define ADC_CHANNEL_20           (ADC_CHANNEL_20_NUMBER | ADC_CHANNEL_20_SMP)
#define ADC_CHANNEL_21           (ADC_CHANNEL_21_NUMBER | ADC_CHANNEL_21_SMP)
#define ADC_CHANNEL_22           (ADC_CHANNEL_22_NUMBER | ADC_CHANNEL_22_SMP)
#define ADC_CHANNEL_23           (ADC_CHANNEL_23_NUMBER | ADC_CHANNEL_23_SMP)
#define ADC_CHANNEL_OPA1         (ADC_CHANNEL_15)
#define ADC_CHANNEL_OPA2         (ADC_CHANNEL_16)
#define ADC_CHANNEL_OPA3         (ADC_CHANNEL_17)
#define ADC_CHANNEL_LDO12        (ADC_CHANNEL_18)
#define ADC_CHANNEL_CMPSRN       (ADC_CHANNEL_19)
#define ADC_CHANNEL_VBGINT       (ADC_CHANNEL_20)
#define ADC_CHANNEL_VREFP        (ADC_CHANNEL_21)
#define ADC_CHANNEL_TPS       	 (ADC_CHANNEL_22)
#define ADC_CHANNEL_LDO17        (ADC_CHANNEL_23)

#define ADC_AWD_THRESHOLD_HIGH   ((uint32_t)0x00000000)
#define ADC_AWD_THRESHOLD_LOW    ((uint32_t)0x00000001) 

#define ADC_SQRL_SCAN_DISABLE    ((uint32_t)0x00000000)
#define ADC_SQRL_SCAN_2RANKS     (                               ADC_SQR1_L_0)
#define ADC_SQRL_SCAN_3RANKS     (                ADC_SQR1_L_1               )
#define ADC_SQRL_SCAN_4RANKS     (                ADC_SQR1_L_1 | ADC_SQR1_L_0)
#define ADC_SQRL_SCAN_5RANKS     ( ADC_SQR1_L_2                              )
#define ADC_SQRL_SCAN_6RANKS     ( ADC_SQR1_L_2                | ADC_SQR1_L_0)
#define ADC_SQRL_SCAN_7RANKS     ( ADC_SQR1_L_2 | ADC_SQR1_L_1               )
#define ADC_SQRL_SCAN_8RANKS     ( ADC_SQR1_L_2 | ADC_SQR1_L_1 | ADC_SQR1_L_0) 

#define ADC_SQR1_REGOFFSET       ((uint32_t)0x00000000)
#define ADC_SQR2_REGOFFSET       ((uint32_t)0x00001000) 
#define ADC_SQR3_REGOFFSET       ((uint32_t)0x00002000)
#define ADC_SQRX_REGOFFSET_MASK  (ADC_SQR1_REGOFFSET | ADC_SQR2_REGOFFSET | ADC_SQR3_REGOFFSET)

#define ADC_REG_RANK_1_BITOFFSET ( 0U)
#define ADC_REG_RANK_2_BITOFFSET ( 5U)
#define ADC_REG_RANK_3_BITOFFSET (10U)
#define ADC_REG_RANK_4_BITOFFSET (15U) 
#define ADC_REG_RANK_5_BITOFFSET (20U) 
#define ADC_REG_RANK_6_BITOFFSET (25U) 
#define ADC_REG_RANK_7_BITOFFSET ( 0U)
#define ADC_REG_RANK_8_BITOFFSET ( 5U) 
#define ADC_REG_RANK_MASK        ((uint32_t)0x0000001F)

#define ADC_REG_RANK_1           (ADC_SQR3_REGOFFSET | ADC_REG_RANK_1_BITOFFSET)
#define ADC_REG_RANK_2           (ADC_SQR3_REGOFFSET | ADC_REG_RANK_2_BITOFFSET)
#define ADC_REG_RANK_3           (ADC_SQR3_REGOFFSET | ADC_REG_RANK_3_BITOFFSET)
#define ADC_REG_RANK_4           (ADC_SQR3_REGOFFSET | ADC_REG_RANK_4_BITOFFSET)
#define ADC_REG_RANK_5           (ADC_SQR3_REGOFFSET | ADC_REG_RANK_5_BITOFFSET)
#define ADC_REG_RANK_6           (ADC_SQR3_REGOFFSET | ADC_REG_RANK_6_BITOFFSET)
#define ADC_REG_RANK_7           (ADC_SQR2_REGOFFSET | ADC_REG_RANK_7_BITOFFSET)
#define ADC_REG_RANK_8           (ADC_SQR2_REGOFFSET | ADC_REG_RANK_8_BITOFFSET)

#define ADC_JDR1_REGOFFSET       ((uint32_t)0x00000000)
#define ADC_JDR2_REGOFFSET       ((uint32_t)0x00000100)
#define ADC_JDR3_REGOFFSET       ((uint32_t)0x00000200)
#define ADC_JDR4_REGOFFSET       ((uint32_t)0x00000300)

#define ADC_JOFR1_REGOFFSET      ((uint32_t)0x00000000)
#define ADC_JOFR2_REGOFFSET      ((uint32_t)0x00001000)
#define ADC_JOFR3_REGOFFSET      ((uint32_t)0x00002000)
#define ADC_JOFR4_REGOFFSET      ((uint32_t)0x00003000)

#define ADC_JDRX_REGOFFSET_MASK  (ADC_JDR1_REGOFFSET | ADC_JDR2_REGOFFSET | ADC_JDR3_REGOFFSET | ADC_JDR4_REGOFFSET)
#define ADC_JOFRX_REGOFFSET_MASK (ADC_JOFR1_REGOFFSET | ADC_JOFR2_REGOFFSET | ADC_JOFR3_REGOFFSET | ADC_JOFR4_REGOFFSET)

#define ADC_INJ_RANK_1           (ADC_JDR1_REGOFFSET | ADC_JOFR1_REGOFFSET | 0x00000001)
#define ADC_INJ_RANK_2           (ADC_JDR2_REGOFFSET | ADC_JOFR2_REGOFFSET | 0x00000002)      
#define ADC_INJ_RANK_3           (ADC_JDR3_REGOFFSET | ADC_JOFR3_REGOFFSET | 0x00000003)       
#define ADC_INJ_RANK_4           (ADC_JDR4_REGOFFSET | ADC_JOFR4_REGOFFSET | 0x00000004)
#define ADC_INJ_RANK_MASK        ((uint32_t)0x0000001F)

#define ADC_JSQRL_SCAN_DISABLE   ((uint32_t)0x00000000)
#define ADC_JSQRL_SCAN_2RANKS    (                ADC_JSQR_JL_0)
#define ADC_JSQRL_SCAN_3RANKS    (ADC_JSQR_JL_1                )
#define ADC_JSQRL_SCAN_4RANKS    (ADC_JSQR_JL_1 | ADC_JSQR_JL_0)

#define ADC_IDX_0                ((uint32_t)0x00000000)
#define ADC_IDX_1                ((uint32_t)0x00000001)
#define ADC_IDX_2                ((uint32_t)0x00000002)
#define ADC_IDX_3                ((uint32_t)0x00000003)

#define ADC_SMPS_IDX_SMPR        ((uint32_t)0x00000000)  
#define ADC_SMPS_IDX_SMPV         ADC_SMPS_IDX0     

#define ADC_DATA1_REGOFFSET       ((uint32_t)0x00000000)  
#define ADC_DATA2_REGOFFSET       ((uint32_t)0x00000001)
#define ADC_DATA3_REGOFFSET       ((uint32_t)0x00000002)
#define ADC_DATA4_REGOFFSET       ((uint32_t)0x00000003)  
#define ADC_DATA5_REGOFFSET       ((uint32_t)0x00000004)
#define ADC_DATA6_REGOFFSET       ((uint32_t)0x00000005)
#define ADC_DATA7_REGOFFSET       ((uint32_t)0x00000006)  
#define ADC_DATA8_REGOFFSET       ((uint32_t)0x00000007)

#define ADC_DR1                 ADC_DATA1_REGOFFSET 
#define ADC_DR2                 ADC_DATA2_REGOFFSET 
#define ADC_DR3                 ADC_DATA3_REGOFFSET 
#define ADC_DR4                 ADC_DATA4_REGOFFSET 
#define ADC_DR5                 ADC_DATA5_REGOFFSET 
#define ADC_DR6                 ADC_DATA6_REGOFFSET
#define ADC_DR7                 ADC_DATA7_REGOFFSET 
#define ADC_DR8                 ADC_DATA8_REGOFFSET 

/*******************  Bit definition for HTR and LTR register  *******************/
#define ADC_HTR_Enable                      ADC_HTR_EN
#define ADC_HTR_Disable                     ((uint32_t)0x00000000)

#define ADC_LTR_Enable                      ADC_LTR_EN
#define ADC_LTR_Disable                     ((uint32_t)0x00000000)


typedef struct
{
	uint32_t TriggerSource;
	uint32_t Continuous;
	uint32_t ScanMode;
	uint32_t DataAlignment;
	uint32_t AnalogWatchDog;
  uint32_t AWDChannelGroup;	
	uint32_t RegularDiscont;
	uint32_t RegularDiscontNumber;
	uint32_t EOCOption;
} ADC_Reg_InitTypeDef;

typedef struct
{
	uint32_t TriggerSource;
	uint32_t ScanMode;
	uint32_t DataAlignment;
  uint32_t SequencerNbRanks;
  uint32_t TrigAuto;
	uint32_t AnalogWatchDog;
	uint32_t AWDChannelGroup;	
	uint32_t InjectDiscont;
	uint32_t EOCOption;
} ADC_Inj_InitTypeDef;

typedef struct
{
	uint32_t REGTriggerSource;
  uint32_t INJTriggerSource;
	uint32_t Continuous;
	uint32_t ScanMode;
	uint32_t DataAlignment;
  uint32_t REGSequencerNbRanks;
  uint32_t INJSequencerNbRanks;
  uint32_t TrigAuto;
  uint32_t AWDChannelGroup;
} ADC_InitTypeDef;

typedef struct
{
	uint32_t Channel;
	uint32_t SamplingTime;
}RankType;

typedef struct
{
  uint32_t Length;
  RankType Rank[8];
} ADC_REG_RankInitTypeDef;

typedef struct
{
  uint32_t Length;
  RankType Rank[4];
} ADC_INJ_RankInitTypeDef;

/**
  * @function  ADC_Get_SR
  * @brief  read complete interrupt Flag status of the selected ADC
  * @param  ADCx :
            @arg ADC Instance
  * @param  IF:
  *         @arg  ADC_SR_AWD  
  *         @arg  ADC_SR_EOC  
  *         @arg  ADC_SR_JEOC 
  *         @arg  ADC_SR_JSTRT 
  *         @arg  ADC_SR_STRT
  * @retval State of bit (1 or 0)
  */
__STATIC_INLINE uint32_t ADC_Get_SR(ADC_TypeDef* ADCx, uint32_t IF)
{
  return (READ_BIT(ADCx->SR, IF) == (IF));
}

/**
  * @function  ADC_Clear_SR
  * @brief  Clear complete interrupt Flag status of the selected ADC
  * @param  ADCx:
            @arg ADC Instance
  * @param  IF:
  *         @arg  ADC_SR_AWD 
  *         @arg  ADC_SR_EOC 
  *         @arg  ADC_SR_JEOC
  *         @arg  ADC_SR_JSTRT 
  *         @arg  ADC_SR_STRT
  */
__STATIC_INLINE void ADC_Clear_SR(ADC_TypeDef *ADCx, uint32_t IF)
{
  CLEAR_BIT(ADCx->SR, IF);
}

/**
  * @function  ADC_Set_AWD
  * @brief  Set AWD ENABLE of the selected ADC
  * @param  ADCx:
            @arg ADC Instance
  * @param  AWDEN:
  *         @arg ADC_CR1_AWD_ENABLE
  *         @arg ADC_CR1_AWD_DISABLE
  * @retval None
  */
__STATIC_INLINE void ADC_Set_AWD(ADC_TypeDef *ADCx, uint32_t AWDEN)
{
  MODIFY_REG(ADCx->CR1, ADC_CR1_AWDEN, AWDEN);
}

/**
  * @function  ADC_Set_JAWD
  * @brief  Set JAWD ENABLE of the selected ADC
  * @param  ADCx:
            @arg ADC Instance
  * @param  JAWDEN:
  *         @arg ADC_CR1_JAWD_ENABLE
  *         @arg ADC_CR1_JAWD_DISABLE
  * @retval None
  */
__STATIC_INLINE void ADC_Set_JAWD(ADC_TypeDef *ADCx, uint32_t JAWDEN)
{
  MODIFY_REG(ADCx->CR1, ADC_CR1_JAWDEN, JAWDEN);
}

/**
  * @function  ADC_Set_AWDChannels
  * @brief  Set AWDChannels of the selected ADC
  * @param  ADCx:
            @arg ADC Instance
  * @param  AWDChannelGroup:
  *         @arg ADC_AWD_DISABLE
  *         @arg ADC_AWD_ALL_CHANNELS_REG
  *         @arg ADC_AWD_ALL_CHANNELS_INJ
  *         @arg ADC_AWD_ALL_CHANNELS_REG_INJ
  *         @arg ADC_AWD_CHANNEL_0_REG 
  *         @arg ADC_AWD_CHANNEL_0_INJ 
  *         @arg ADC_AWD_CHANNEL_0_REG_INJ
  *         @arg ADC_AWD_CHANNEL_1_REG 
  *         @arg ADC_AWD_CHANNEL_1_INJ 
  *         @arg ADC_AWD_CHANNEL_1_REG_INJ
  *         @arg ADC_AWD_CHANNEL_2_REG 
  *         @arg ADC_AWD_CHANNEL_2_INJ 
  *         @arg ADC_AWD_CHANNEL_2_REG_INJ
  *         @arg ADC_AWD_CHANNEL_3_REG 
  *         @arg ADC_AWD_CHANNEL_3_INJ 
  *         @arg ADC_AWD_CHANNEL_3_REG_INJ
  *         @arg ADC_AWD_CHANNEL_4_REG 
  *         @arg ADC_AWD_CHANNEL_4_INJ 
  *         @arg ADC_AWD_CHANNEL_4_REG_INJ
  *         @arg ADC_AWD_CHANNEL_5_REG 
  *         @arg ADC_AWD_CHANNEL_5_INJ 
  *         @arg ADC_AWD_CHANNEL_5_REG_INJ
  *         @arg ADC_AWD_CHANNEL_6_REG 
  *         @arg ADC_AWD_CHANNEL_6_INJ 
  *         @arg ADC_AWD_CHANNEL_6_REG_INJ
  *         @arg ADC_AWD_CHANNEL_7_REG       
  *         @arg ADC_AWD_CHANNEL_7_INJ      
  *         @arg ADC_AWD_CHANNEL_7_REG_INJ  
  *         @arg ADC_AWD_CHANNEL_8_REG       
  *         @arg ADC_AWD_CHANNEL_8_INJ      
  *         @arg ADC_AWD_CHANNEL_8_REG_INJ 
  *         @arg ADC_AWD_CHANNEL_9_REG      
  *         @arg ADC_AWD_CHANNEL_9_INJ       
  *         @arg ADC_AWD_CHANNEL_9_REG_INJ  
  *         @arg ADC_AWD_CHANNEL_10_REG      
  *         @arg ADC_AWD_CHANNEL_10_INJ     
  *         @arg ADC_AWD_CHANNEL_10_REG_INJ       
  *         @arg ADC_AWD_CHANNEL_11_REG      
  *         @arg ADC_AWD_CHANNEL_11_INJ     
  *         @arg ADC_AWD_CHANNEL_11_REG_INJ   
  *         @arg ADC_AWD_CHANNEL_12_REG      
  *         @arg ADC_AWD_CHANNEL_12_INJ     
  *         @arg ADC_AWD_CHANNEL_12_REG_INJ   
  *         @arg ADC_AWD_CHANNEL_13_REG      
  *         @arg ADC_AWD_CHANNEL_13_INJ     
  *         @arg ADC_AWD_CHANNEL_13_REG_INJ   
  *         @arg ADC_AWD_CHANNEL_14_REG      
  *         @arg ADC_AWD_CHANNEL_14_INJ     
  *         @arg ADC_AWD_CHANNEL_14_REG_INJ   
  *         @arg ADC_AWD_CHANNEL_15_REG      
  *         @arg ADC_AWD_CHANNEL_15_INJ     
  *         @arg ADC_AWD_CHANNEL_15_REG_INJ   
  *         @arg ADC_AWD_CHANNEL_16_REG      
  *         @arg ADC_AWD_CHANNEL_16_INJ     
  *         @arg ADC_AWD_CHANNEL_16_REG_INJ   
  *         @arg ADC_AWD_CHANNEL_17_REG      
  *         @arg ADC_AWD_CHANNEL_17_INJ     
  *         @arg ADC_AWD_CHANNEL_17_REG_INJ 
  *         @arg ADC_AWD_CHANNEL_18_REG    
  *         @arg ADC_AWD_CHANNEL_18_INJ    
  *         @arg ADC_AWD_CHANNEL_18_REG_INJ
  *         @arg ADC_AWD_CHANNEL_19_REG    
  *         @arg ADC_AWD_CHANNEL_19_INJ    
  *         @arg ADC_AWD_CHANNEL_19_REG_INJ
  *         @arg ADC_AWD_CHANNEL_20_REG    
  *         @arg ADC_AWD_CHANNEL_20_INJ    
  *         @arg ADC_AWD_CHANNEL_20_REG_INJ
  *         @arg ADC_AWD_CHANNEL_21_REG    
  *         @arg ADC_AWD_CHANNEL_21_INJ    
  *         @arg ADC_AWD_CHANNEL_21_REG_INJ
  *         @arg ADC_AWD_CHANNEL_22_REG    
  *         @arg ADC_AWD_CHANNEL_22_INJ    
  *         @arg ADC_AWD_CHANNEL_22_REG_INJ
  *         @arg ADC_AWD_CHANNEL_23_REG    
  *         @arg ADC_AWD_CHANNEL_23_INJ    
  *         @arg ADC_AWD_CHANNEL_23_REG_INJ
  * @retval None
  */
__STATIC_INLINE void ADC_Set_AWDChannels(ADC_TypeDef *ADCx, uint32_t AWDChannelGroup)
{
  MODIFY_REG(ADCx->CR1,
             (ADC_CR1_AWDEN | ADC_CR1_JAWDEN | ADC_CR1_AWDSGL | ADC_CR1_AWDCH),
             AWDChannelGroup);
}

/**
  * @function  ADC_Enable_IT
  * @brief  Enable ADC interrupt of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @param  IT:
  *         @arg ADC_CR1_EOCIE
  *         @arg ADC_CR1_AWDIE
  *         @arg ADC_CR1_JEOCIE
  * @retval None
  */
__STATIC_INLINE void ADC_Enable_IT(ADC_TypeDef *ADCx,uint16_t IT)
{
	SET_BIT(ADCx->CR1,IT); 
}

/**
  * @function  ADC_Disable_IT
  * @brief  Disable ADC interrupt of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @param  IT:
  *         @arg ADC_CR1_EOCIE
  *         @arg ADC_CR1_AWDIE
  *         @arg ADC_CR1_JEOCIE
  * @retval None
  */
__STATIC_INLINE void ADC_Disable_IT(ADC_TypeDef *ADCx,uint16_t IT)
{
	CLEAR_BIT(ADCx->CR1,IT); 
}

/**
  * @function  ADC_Get_IT
  * @brief  read complete interrupt status of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @param  IT:
  *         @arg ADC_CR1_EOCIE
  *         @arg ADC_CR1_AWDIE
  *         @arg ADC_CR1_JEOCIE
  * @retval 0 is disable, 1 is enable
  */
__STATIC_INLINE uint32_t ADC_Get_IT(ADC_TypeDef *ADCx,uint16_t IT)
{
  return (READ_BIT(ADCx->CR1, IT) == (IT));
}

/**
  * @function  ADC_Set_SCAN
  * @brief  Set SCAN of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @param  ScanMode:
  *         @arg ADC_CR1_SCAN_DISABLE
  *         @arg ADC_CR1_SCAN_ENABLE
  * @retval None
  */
__STATIC_INLINE void ADC_Set_SCAN(ADC_TypeDef *ADCx, uint32_t ScanMode)
{
  MODIFY_REG(ADCx->CR1, ADC_CR1_SCAN, ScanMode);
}

/**
  * @function  ADC_Set_JAUTO
  * @brief  Set JAUTO of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @param  TrigAuto:
  *         @arg ADC_CR1_JAUTO_INDEPENDENT
  *         @arg ADC_CR1_JAUTO_FROM_REG
  * @retval None
  */
__STATIC_INLINE void ADC_Set_JAUTO(ADC_TypeDef *ADCx, uint32_t TrigAuto)
{
  MODIFY_REG(ADCx->CR1, ADC_CR1_JAUTO, TrigAuto);
}

/**
  * @function  ADC_Set_DISCEN
  * @brief  Set regular discont of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @param  TrigAuto:
  *         @arg ADC_CR1_DISCEN_ENABLE
  *         @arg ADC_CR1_DISCEN_DISABLE
  * @retval None
  */
__STATIC_INLINE void ADC_Set_DISCEN(ADC_TypeDef *ADCx, uint32_t discen)
{
	MODIFY_REG(ADCx->CR1, ADC_CR1_DISCEN, discen);
}

/**
  * @function  ADC_Set_JDISCEN
  * @brief  Set inject discont of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @param  TrigAuto:
  *         @arg ADC_CR1_JDISCEN_ENABLE
  *         @arg ADC_CR1_JDISCEN_DISABLE
  * @retval None
  */
__STATIC_INLINE void ADC_Set_JDISCEN(ADC_TypeDef *ADCx, uint32_t jdiscen)
{
	MODIFY_REG(ADCx->CR1, ADC_CR1_JDISCEN, jdiscen);
}

/**
  * @function  ADC_Set_DISCNUM
  * @brief  Set ADC group regular discont ranks. 
  * @param  ADCx:
  *         @arg ADC Instance
  * @param  SeqDiscont:
  *         @arg ADC_CR1_DISCONT_DISABLE
  *         @arg ADC_CR1_DISCONT_1RANK
  *         @arg ADC_CR1_DISCONT_2RANKS
  *         @arg ADC_CR1_DISCONT_3RANKS
  *         @arg ADC_CR1_DISCONT_4RANKS
  *         @arg ADC_CR1_DISCONT_5RANKS
  *         @arg ADC_CR1_DISCONT_6RANKS
  *         @arg ADC_CR1_DISCONT_7RANKS
  *         @arg ADC_CR1_DISCONT_8RANKS
  * @retval None
  */
__STATIC_INLINE void ADC_Set_DISCNUM(ADC_TypeDef *ADCx, uint32_t SeqDiscont)
{
  MODIFY_REG(ADCx->CR1, ADC_CR1_DISCNUM, SeqDiscont);
}

/**
  * @function  ADC_Enable_ADON
  * @brief  Enable ADON of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @retval None
  */
__STATIC_INLINE void ADC_Enable_ADON(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CR2, ADC_CR2_ADON);    
}

/**
  * @function  ADC_Disable_ADON
  * @brief  Disable ADON of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @retval None
  */
__STATIC_INLINE void ADC_Disable_ADON(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->CR2, ADC_CR2_ADON);
}

/**
  * @function  ADC_Get_ADON
  * @brief  Get ADCON state of the selected ADC 
  * @param  ADCx:
  *         @arg ADC Instance
  * @retval 0 is disable, 1 is enable
  */
__STATIC_INLINE uint32_t ADC_Get_ADON(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->CR2, ADC_CR2_ADON) == (ADC_CR2_ADON));
}

/**
  * @function  ADC_Set_CONT
  * @brief  Set ADC group regular continuous mode of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @param  Continuous:
  *         @arg ADC_CR2_CONT_SINGLE
  *         @arg ADC_CR2_CONT_CONTINUOUS
  * @retval None
  */
__STATIC_INLINE void ADC_Set_CONT(ADC_TypeDef *ADCx, uint32_t Continuous)
{
  MODIFY_REG(ADCx->CR2, ADC_CR2_CONT, Continuous);
}

/**
  * @function  ADC_CAL
  * @brief  Trig CAL of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @retval None
  */
__STATIC_INLINE void ADC_CAL(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CR2, ADC_CR2_CAL);
}

/**
  * @function  ADC_Get_CAL
  * @brief  Get CAL state of the selected ADC 
  * @param  ADCx:
  *         @arg ADC Instance
  * @retval 0:CAL is finish, 1:CAL is going
  */
__STATIC_INLINE uint32_t ADC_Get_CAL(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->CR2, ADC_CR2_CAL) == (ADC_CR2_CAL));
}

/**
  * @function  ADC_RSTCAL
  * @brief  Trig RSTCAL of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @retval None
  */
__STATIC_INLINE void ADC_RSTCAL(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CR2, ADC_CR2_RSTCAL);
}

/**
  * @function  ADC_Get_RSTCAL
  * @brief  Get RSTCAL state of the selected ADC 
  * @param  ADCx:
  *         @arg ADC Instance
  * @retval 0:RSTCAL is finish, 1:RSTCAL is going
  */
__STATIC_INLINE uint32_t ADC_Get_RSTCAL(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->CR2, ADC_CR2_RSTCAL) == (ADC_CR2_RSTCAL));
}

/**
  * @function  ADC_Set_ALIGN
  * @brief  Set ADC conversion data alignment of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @param  DataAlignment:
  *         @arg ADC_CR2_ALIGN_RIGHT
  *         @arg ADC_CR2_ALIGN_LEFT
  * @retval None
  */
__STATIC_INLINE void ADC_Set_ALIGN(ADC_TypeDef *ADCx, uint32_t DataAlignment)
{
  MODIFY_REG(ADCx->CR2, ADC_CR2_ALIGN, DataAlignment);
}

/**
  * @function  ADC_Set_JEXTSEL
  * @brief  Set group injected trigger source of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @param  TriggerSource:
  *         @arg ADC_CR2_JEXTSEL_INSOURCE         
  *         @arg ADC_CR2_JEXTSEL_TIM8_TRGO1           
  *         @arg ADC_CR2_JEXTSEL_TIM8_CC4           
  *         @arg ADC_CR2_JEXTSEL_TIM2_TRGO        
  *         @arg ADC_CR2_JEXTSEL_TIM2_CC1       
  *         @arg ADC_CR2_JEXTSEL_TIM3_CC4          
  *         @arg ADC_CR2_JEXTSEL_TIM3_CC3       
  *         @arg ADC_CR2_JEXTSEL_EXTI2       
  *         @arg ADC_CR2_JEXTSEL_JSWSTART      
  *         @arg ADC_CR2_JEXTSEL_TIM8_TRGO2      
  *         @arg ADC_CR2_JEXTSEL_TIM8_CC2         
  *         @arg ADC_CR2_JEXTSEL_TIM8_CC5_CC6   
  *         @arg ADC_CR2_JEXTSEL_TIM8_CC4_CC6  
  *         @arg ADC_CR2_JEXTSEL_TIM8_CC4_CC5
  *         @arg ADC_CR2_JEXTSEL_TIM8_CC6    
  *         @arg ADC_CR2_JEXTSEL_TIM15_TRGO							 
  * @retval None
  */
__STATIC_INLINE void ADC_Set_JEXTSEL(ADC_TypeDef *ADCx, uint32_t TriggerSource)
{
  MODIFY_REG(ADCx->CR2, ADC_CR2_JEXTSEL | ADC_CR2_JEXTTRIG , TriggerSource);
}

/**
  * @function  ADC_Set_EXTSEL
  * @brief  Set group regular trigger source of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @param  TriggerSource:
  *         @arg ADC_CR2_EXTSEL_INSOURCE     
  *         @arg ADC_CR2_EXTSEL_TIM8_TRGO2        
  *         @arg ADC_CR2_EXTSEL_TIM8_CC4_CC5  
  *         @arg ADC_CR2_EXTSEL_TIM2_CC3_CC4
  *         @arg ADC_CR2_EXTSEL_TIM2_CC4       
  *         @arg ADC_CR2_EXTSEL_TIM3_CC2      
  *         @arg ADC_CR2_EXTSEL_TIM3_TRGO      
  *         @arg ADC_CR2_EXTSEL_EXTI3       
  *         @arg ADC_CR2_EXTSEL_SWSTART       
  * @retval None
  */
__STATIC_INLINE void ADC_Set_EXTSEL(ADC_TypeDef *ADCx, uint32_t TriggerSource)
{
  MODIFY_REG(ADCx->CR2, ADC_CR2_EXTSEL | ADC_CR2_EXTTRIG , TriggerSource);
}

/**
  * @function  ADC_Start_SW
  * @brief  Start ADC group regular conversion of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @retval None
  */
__STATIC_INLINE void ADC_Start_SW(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CR2, ADC_CR2_SWSTART);
}

/**
  * @function  ADC_Start_JSW
  * @brief  Start ADC group injected conversion of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @retval None
  */
__STATIC_INLINE void ADC_Start_JSW(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CR2, ADC_CR2_JSWSTART);
}

/**
  * @function  ADC_Enable_TSVREFE
  * @brief  Enable TSVREFE of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @retval None
  */
__STATIC_INLINE void ADC_Enable_TSVREFE(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CR2, ADC_CR2_TSVREFE);     
}

/**
  * @function  ADC_Disable_TSVREFE
  * @brief  Disable TSVREFE of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @retval None
  */
__STATIC_INLINE void ADC_Disable_TSVREFE(ADC_TypeDef *ADCx)
{
  CLEAR_BIT(ADCx->CR2, ADC_CR2_TSVREFE);   
}

/**
  * @function  ADC_Set_SMPR
  * @brief  Set selected channel sampling time of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @param  Channel:
  *         @ref ADC_CHANNEL_0     
  *         @ref ADC_CHANNEL_1     
  *         @ref ADC_CHANNEL_2     
  *         @ref ADC_CHANNEL_3     
  *         @ref ADC_CHANNEL_4     
  *         @ref ADC_CHANNEL_5     
  *         @ref ADC_CHANNEL_6     
  *         @ref ADC_CHANNEL_7     
  *         @ref ADC_CHANNEL_8     
  *         @ref ADC_CHANNEL_9     
  *         @ref ADC_CHANNEL_10    
  *         @ref ADC_CHANNEL_11    
  *         @ref ADC_CHANNEL_12    
  *         @ref ADC_CHANNEL_13    
  *         @ref ADC_CHANNEL_14    
  *         @ref ADC_CHANNEL_15    
  *         @ref ADC_CHANNEL_16    
  *         @ref ADC_CHANNEL_17    
  *         @ref ADC_CHANNEL_18    
  *         @ref ADC_CHANNEL_19    
  *         @ref ADC_CHANNEL_20    
  *         @ref ADC_CHANNEL_21    
  *         @ref ADC_CHANNEL_22    
  *         @ref ADC_CHANNEL_23    
  *         @ref ADC_CHANNEL_OPA1  
  *         @ref ADC_CHANNEL_OPA2  
  *         @ref ADC_CHANNEL_OPA3  
  *         @ref ADC_CHANNEL_LDO12 
  *         @ref ADC_CHANNEL_CMPSRN
  *         @ref ADC_CHANNEL_VBGINT
  *         @ref ADC_CHANNEL_VREFP 
  *         @ref ADC_CHANNEL_TPS   
  *         @ref ADC_CHANNEL_LDO17  
  * @param  SamplingTime:
  *         @ref ADC_SAMPLINGTIME_2p5CYCLES       
  *         @ref ADC_SAMPLINGTIME_6p5CYCLES        
  *         @ref ADC_SAMPLINGTIME_11p5CYCLES         
  *         @ref ADC_SAMPLINGTIME_17p5CYCLES       
  *         @ref ADC_SAMPLINGTIME_25p5CYCLES        
  *         @ref ADC_SAMPLINGTIME_35p5CYCLES       
  *         @ref ADC_SAMPLINGTIME_48p5CYCLES       
  *         @ref ADC_SAMPLINGTIME_640p5CYCLES            
  * @retval None           
  */
__STATIC_INLINE void ADC_Set_SMPR(ADC_TypeDef *ADCx, uint32_t Channel, uint32_t SamplingTime)
{
  register uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->SMPR1, __ADC_MASK_SHIFT(Channel, ADC_CHANNEL_SMPRX_REGOFFSET_MASK));
      MODIFY_REG(*preg, 
             ADC_SMPR2_SMP0 << __ADC_MASK_SHIFT(Channel, ADC_SMPR_BITOFFSET_MASK),
             (SamplingTime & ADC_SMPR2_SMP0)   << __ADC_MASK_SHIFT(Channel, ADC_SMPR_BITOFFSET_MASK));
}

/**
  * @function  ADC_Set_JOFR
  * @brief  Set ADC JOFRx of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @param  Rank:
  *         @ref ADC_INJ_RANK_1       
  *         @ref ADC_INJ_RANK_2        
  *         @ref ADC_INJ_RANK_3       
  *         @ref ADC_INJ_RANK_4 
  * @param  offest:
  *         @ref offest
  * @retval None
  */
__STATIC_INLINE void ADC_Set_JOFR(ADC_TypeDef *ADCx, uint32_t Rank, uint32_t offest)
{
  register uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->JOFR1,  __ADC_MASK_SHIFT(Rank, ADC_JOFRX_REGOFFSET_MASK));
  MODIFY_REG(*preg, ADC_JOFR1_JOFFSET1, offest);
}

/**
  * @function  ADC_Read_JOFR
  * @brief  Get JOFRx offest of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @param  Rank:
  *         @ref ADC_INJ_RANK_1       
  *         @ref ADC_INJ_RANK_2        
  *         @ref ADC_INJ_RANK_3       
  *         @ref ADC_INJ_RANK_4 
  * @retval offest of JOFRx.
  */
__STATIC_INLINE uint32_t ADC_Read_JOFR(ADC_TypeDef *ADCx, uint32_t Rank)
{
  register uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->JOFR1,  __ADC_MASK_SHIFT(Rank, ADC_JOFRX_REGOFFSET_MASK));
  return (uint32_t)(READ_BIT(*preg, ADC_JOFR1_JOFFSET1));
}

/**
  * @function  ADC_Set_AWDThresholds
  * @brief  Set ADC AWDThresholds of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @param  AWDThresholdsHighLow:
  *         @ref ADC_AWD_THRESHOLD_HIGH    
  *         @ref ADC_AWD_THRESHOLD_LOW
  * @param  AWDThresholdValue:
  *         @ref offest
  * @retval None
  */
__STATIC_INLINE void ADC_Set_AWDThresholds(ADC_TypeDef *ADCx, uint32_t AWDThresholdsHighLow, uint32_t AWDThresholdValue)
{
  register uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->HTR, AWDThresholdsHighLow);
  MODIFY_REG(*preg, ADC_HTR_HT, AWDThresholdValue);
}

/**
  * @function  ADC_Read_AWDThresholds
  * @brief  Get AWDThresholds of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @param  AWDThresholdsHighLow:
  *         @ref ADC_AWD_THRESHOLD_HIGH    
  *         @ref ADC_AWD_THRESHOLD_LOW
  * @retval offest of HTR/LTR.
  */
__STATIC_INLINE uint32_t ADC_Read_AWDThresholds(ADC_TypeDef *ADCx, uint32_t AWDThresholdsHighLow)
{
  register uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->HTR, AWDThresholdsHighLow);
  return (uint32_t)(READ_BIT(*preg, ADC_HTR_HT));
}

/**
  * @function  ADC_Set_SQRL
  * @brief  Set ADC group regular sequencer length and scan direction of the selected ADC
  * @param  ADCx:
  *          @arg ADC Instance
  * @param  SEQLENG:
  *         @ref ADC_SQRL_SCAN_DISABLE
  *         @ref ADC_SQRL_SCAN_2RANKS
  *         @ref ADC_SQRL_SCAN_3RANKS
  *         @ref ADC_SQRL_SCAN_4RANKS
  *         @ref ADC_SQRL_SCAN_5RANKS
  *         @ref ADC_SQRL_SCAN_6RANKS
  *         @ref ADC_SQRL_SCAN_7RANKS
  *         @ref ADC_SQRL_SCAN_8RANKS
  * @retval None
  */
__STATIC_INLINE void ADC_Set_SQRL(ADC_TypeDef *ADCx, uint32_t SequencerNbRanks)
{
  MODIFY_REG(ADCx->SQR1, ADC_SQR1_L, SequencerNbRanks);
}

/**
  * @function  ADC_Set_SQ
  * @brief  Set ADC group regular sequence: channel on the selected sequence rank of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @param  Rank:
  *         @ref ADC_REG_RANK_1
  *         @ref ADC_REG_RANK_2
  *         @ref ADC_REG_RANK_3
  *         @ref ADC_REG_RANK_4 
  *         @ref ADC_REG_RANK_5
  *         @ref ADC_REG_RANK_6
  *         @ref ADC_REG_RANK_7
  *         @ref ADC_REG_RANK_8
  * @param  Channel:
  *         @ref ADC_CHANNEL_0     
  *         @ref ADC_CHANNEL_1     
  *         @ref ADC_CHANNEL_2     
  *         @ref ADC_CHANNEL_3     
  *         @ref ADC_CHANNEL_4     
  *         @ref ADC_CHANNEL_5     
  *         @ref ADC_CHANNEL_6     
  *         @ref ADC_CHANNEL_7     
  *         @ref ADC_CHANNEL_8     
  *         @ref ADC_CHANNEL_9     
  *         @ref ADC_CHANNEL_10    
  *         @ref ADC_CHANNEL_11    
  *         @ref ADC_CHANNEL_12    
  *         @ref ADC_CHANNEL_13    
  *         @ref ADC_CHANNEL_14    
  *         @ref ADC_CHANNEL_15    
  *         @ref ADC_CHANNEL_16    
  *         @ref ADC_CHANNEL_17    
  *         @ref ADC_CHANNEL_18    
  *         @ref ADC_CHANNEL_19    
  *         @ref ADC_CHANNEL_20    
  *         @ref ADC_CHANNEL_21    
  *         @ref ADC_CHANNEL_22    
  *         @ref ADC_CHANNEL_23    
  *         @ref ADC_CHANNEL_OPA1  
  *         @ref ADC_CHANNEL_OPA2  
  *         @ref ADC_CHANNEL_OPA3  
  *         @ref ADC_CHANNEL_LDO12 
  *         @ref ADC_CHANNEL_CMPSRN
  *         @ref ADC_CHANNEL_VBGINT
  *         @ref ADC_CHANNEL_VREFP 
  *         @ref ADC_CHANNEL_TPS   
  *         @ref ADC_CHANNEL_LDO17  
  * @retval None
  */
__STATIC_INLINE void ADC_Set_SQ(ADC_TypeDef *ADCx, uint32_t Rank, uint32_t Channel)
{
  register uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->SQR1, __ADC_MASK_SHIFT(Rank, ADC_SQRX_REGOFFSET_MASK));
  MODIFY_REG(*preg,
             ADC_SQR3_SQ1 << (Rank & ADC_REG_RANK_MASK),
             (Channel & ADC_SQR3_SQ1) << (Rank & ADC_REG_RANK_MASK));
}

/**
  * @function  ADC_Set_JSQRL
  * @brief  Set ADC group injected sequencer length and scan direction of the selected ADC
  * @param  ADCx:
  *          @arg ADC Instance
  * @param  SEQLENG:
  *         @ref ADC_JSQRL_SCAN_DISABLE
  *         @ref ADC_JSQRL_SCAN_2RANKS
  *         @ref ADC_JSQRL_SCAN_3RANKS
  *         @ref ADC_JSQRL_SCAN_4RANKS
  * @retval None
  */
__STATIC_INLINE void ADC_Set_JSQRL(ADC_TypeDef *ADCx, uint32_t SequencerNbRanks)
{
  MODIFY_REG(ADCx->JSQR, ADC_JSQR_JL, SequencerNbRanks);
}

/**
  * @function  ADC_Set_JSQ
  * @brief  Set ADC group injected sequence: channel on the selected sequence rank of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @param  Rank:
  *         @ref ADC_INJ_RANK_1
  *         @ref ADC_INJ_RANK_2
  *         @ref ADC_INJ_RANK_3
  *         @ref ADC_INJ_RANK_4 
  * @param  Channel:
  *         @ref ADC_CHANNEL_0     
  *         @ref ADC_CHANNEL_1     
  *         @ref ADC_CHANNEL_2     
  *         @ref ADC_CHANNEL_3     
  *         @ref ADC_CHANNEL_4     
  *         @ref ADC_CHANNEL_5     
  *         @ref ADC_CHANNEL_6     
  *         @ref ADC_CHANNEL_7     
  *         @ref ADC_CHANNEL_8     
  *         @ref ADC_CHANNEL_9     
  *         @ref ADC_CHANNEL_10    
  *         @ref ADC_CHANNEL_11    
  *         @ref ADC_CHANNEL_12    
  *         @ref ADC_CHANNEL_13    
  *         @ref ADC_CHANNEL_14    
  *         @ref ADC_CHANNEL_15    
  *         @ref ADC_CHANNEL_16    
  *         @ref ADC_CHANNEL_17    
  *         @ref ADC_CHANNEL_18    
  *         @ref ADC_CHANNEL_19    
  *         @ref ADC_CHANNEL_20    
  *         @ref ADC_CHANNEL_21    
  *         @ref ADC_CHANNEL_22    
  *         @ref ADC_CHANNEL_23    
  *         @ref ADC_CHANNEL_OPA1  
  *         @ref ADC_CHANNEL_OPA2  
  *         @ref ADC_CHANNEL_OPA3  
  *         @ref ADC_CHANNEL_LDO12 
  *         @ref ADC_CHANNEL_CMPSRN
  *         @ref ADC_CHANNEL_VBGINT
  *         @ref ADC_CHANNEL_VREFP 
  *         @ref ADC_CHANNEL_TPS   
  *         @ref ADC_CHANNEL_LDO17   
  * @retval None
  */
__STATIC_INLINE void ADC_Set_JSQ(ADC_TypeDef *ADCx, uint32_t Rank, uint32_t Channel)
{
  register uint32_t tmpreg1 = (READ_BIT(ADCx->JSQR, ADC_JSQR_JL) >> POSITION_VAL(ADC_JSQR_JL)) + 1U;
  MODIFY_REG(ADCx->JSQR,
             ADC_JSQR_JSQ1 << (5U * (uint8_t)(((Rank & ADC_INJ_RANK_MASK) + 3U) - (tmpreg1))),
             (Channel & ADC_JSQR_JSQ1) << (5U * (uint8_t)(((Rank & ADC_INJ_RANK_MASK) + 3U) - (tmpreg1))));
}

/**
  * @function  ADC_Read_JDR
  * @brief  Get value of JDRx of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @param  Rank:
  *         @ref ADC_INJ_RANK_1
  *         @ref ADC_INJ_RANK_2
  *         @ref ADC_INJ_RANK_3
  *         @ref ADC_INJ_RANK_4 
  * @retval value of JDRx
  */
__STATIC_INLINE uint32_t ADC_Read_JDR(ADC_TypeDef *ADCx, uint32_t Rank)
{
  register uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->JDR1, __ADC_MASK_SHIFT(Rank, ADC_JDRX_REGOFFSET_MASK));
  return (uint32_t)(READ_BIT(*preg, ADC_JDR1_JDATA));
}

/**
  * @function  ADC_Read_DRx
  * @brief  Get value of DRx of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @param  ADC_DATAx:
  *         @ref ADC_DR1
  *         @ref ADC_DR2
  *         @ref ADC_DR3
  *         @ref ADC_DR4
  *         @ref ADC_DR5
  *         @ref ADC_DR6
  *         @ref ADC_DR7
  *         @ref ADC_DR8
  * @retval value of DR_DATA
  */
__STATIC_INLINE uint32_t ADC_Read_DRx(ADC_TypeDef *ADCx, uint32_t ADC_DATAx)
{
	register uint32_t *preg = __ADC_PTR_REG_OFFSET(ADCx->DATA1, ADC_DATAx);
  return (READ_REG(*preg));
}

/**
  * @function  ADC_Read_DR
  * @brief  Get value of DR of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @retval value of DR
  */
__STATIC_INLINE uint32_t ADC_Read_DR(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_REG(ADCx->DR));
}

/**
  * @function  ADC_Set_CAL_DATA
  * @brief  Set  CAL_DATA of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @param  offest:
  *         @ref offest
  * @retval None
  */
__STATIC_INLINE void ADC_Set_CAL_DATA(ADC_TypeDef *ADCx, uint32_t offest)
{
  MODIFY_REG(ADCx->CAL, ADC_CAL_DATA, offest);
}

/**
  * @function  ADC_Read_CAL_DATA
  * @brief  Get value of CAL_DATA of the selected ADC
  * @param  ADCx:
  *         @arg ADC Instance
  * @retval offest of CAL_DATA
  */
__STATIC_INLINE uint32_t ADC_Read_CAL_DATA(ADC_TypeDef *ADCx)
{
  return (uint32_t)(READ_BIT(ADCx->CAL, ADC_CAL_DATA));
}

/**
  * @function  uint32_t ADC_Get_PRGRDY(ADC_TypeDef *ADCx)
  * @brief  check if PRG of ADCx ready
  * @param  ADCx:
  *         @arg ADC Instance
  * @retval 1: register program is finish, 0: register program is ongoing
*/
__STATIC_INLINE uint32_t ADC_Get_PRGRDY(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->CR3, ADC_CR3_PRG_RDY) == (ADC_CR3_PRG_RDY));
}

/**
  * @function  ADC_Set_CFGUPD(ADC_TypeDef *ADCx)
  * @brief  set 1 to start program register ,HW clear to 0 when program finish
  * @param  ADCx:
  *         @arg ADC Instance
  * @retval None
  */
__STATIC_INLINE void ADC_Set_CFGUPD(ADC_TypeDef *ADCx)
{
  SET_BIT(ADCx->CR3,ADC_CR3_CFG_UPD);
}

/**
  * @function  ADC_Get_CFGUPD(ADC_TypeDef *ADCx)
  * @brief  check if configuration update to register is finish
  * @param  ADCx:
  *         @arg ADC Instance
  * @retval 0: finish
  */
__STATIC_INLINE uint32_t ADC_Get_CFGUPD(ADC_TypeDef *ADCx)
{
  return (READ_BIT(ADCx->CR3, ADC_CR3_CFG_UPD) == ADC_CR3_CFG_UPD);
}

/**
  * @function  ADC_Set_AWDFILT(ADC_TypeDef *ADCx, uint32_t FilterLevel)
  * @brief  Set the level of AWD filter of the selected ADC 
  * @param  ADCx:
  *         @arg ADC Instance
  * @param  FilterLevel:
  *         @ref ADC_CR1_AWDFILT_DISABLE
  *         @ref ADC_CR1_AWDFILT_2LEVEL
  *         @ref ADC_CR1_AWDFILT_3LEVEL
  *         @ref ADC_CR1_AWDFILT_4LEVEL
  *         @ref ADC_CR1_AWDFILT_5LEVEL
  *         @ref ADC_CR1_AWDFILT_6LEVEL
  *         @ref ADC_CR1_AWDFILT_7LEVEL
  *         @ref ADC_CR1_AWDFILT_8LEVEL				
  * @retval None
  */
__STATIC_INLINE void ADC_Set_AWDFILT(ADC_TypeDef *ADCx, uint32_t FilterLevel)
{
	MODIFY_REG(ADCx->CR1, ADC_CR1_AWDFILT, FilterLevel);
}

/**
  * @function  ADC_Set_EOCOPT(ADC_TypeDef *ADCx, uint32_t EOCOPT)
  * @brief  End of convertion option
  *         When this bit is set to 1, the EOC and JEOC flag will be raised after the injection channel sequence finish
  *         When this bit is set to 0, only the JEOC flag will be raised after the injection channel sequence finish
  * @param  ADCx:
  *         @arg ADC Instance
  * @param  FilterLevel:
  *         @ref ADC_EOC_OPT_DISABLE
  *         @ref ADC_EOC_OPT_ENABLE			
  * @retval None
  */
__STATIC_INLINE void ADC_Set_EOCOPT(ADC_TypeDef *ADCx, uint32_t EOCOPT)
{
	MODIFY_REG(ADCx->TPS_TEST, ADC_EOC_OPT, EOCOPT);
}

/**
  * @function  ADC_Set_HTREN(ADC_TypeDef *ADCx, uint32_t HTREN)
  * @brief  When HTREN is enabled,the ADC conversion value will be read to the ADC_HTR register after convert the ADC_HTRCH channel 
  * @param  ADCx:
  *         @arg ADC Instance
  * @param  FilterLevel:
  *         @ref ADC_HTR_Enable
  *         @ref ADC_HTR_Disable			
  * @retval None
  */
__STATIC_INLINE void ADC_Set_HTREN(ADC_TypeDef *ADCx, uint32_t HTREN)
{
	SET_BIT(ADCx->HTR,HTREN);
}

/**
  * @function  ADC_Set_HTRChannel
  * @brief  Set the ADC_HTRCH channel
  * @param  ADCx:
  *         @arg ADC Instance
  * @param  FilterLevel:
  *         @ref ADC_CHANNEL_0_NUMBER
  *         @ref ADC_CHANNEL_1_NUMBER  
  *         @ref ADC_CHANNEL_2_NUMBER
  *         @ref ADC_CHANNEL_3_NUMBER
  *         @ref ADC_CHANNEL_4_NUMBER
  *         @ref ADC_CHANNEL_5_NUMBER
  *         @ref ADC_CHANNEL_6_NUMBER
  *         @ref ADC_CHANNEL_7_NUMBER
  *         @ref ADC_CHANNEL_8_NUMBER
  *         @ref ADC_CHANNEL_9_NUMBER
  *         @ref ADC_CHANNEL_10_NUMBER
  *         @ref ADC_CHANNEL_11_NUMBER
  *         @ref ADC_CHANNEL_12_NUMBER
  *         @ref ADC_CHANNEL_13_NUMBER
  *         @ref ADC_CHANNEL_14_NUMBER
  *         @ref ADC_CHANNEL_15_NUMBER
  *         @ref ADC_CHANNEL_16_NUMBER
  *         @ref ADC_CHANNEL_17_NUMBER
  *         @ref ADC_CHANNEL_18_NUMBER  
  *         @ref ADC_CHANNEL_19_NUMBER 
  *         @ref ADC_CHANNEL_20_NUMBER
  *         @ref ADC_CHANNEL_21_NUMBER
  *         @ref ADC_CHANNEL_22_NUMBER
  *         @ref ADC_CHANNEL_23_NUMBER
  * @retval None
  */
__STATIC_INLINE void ADC_Set_HTRChannel(ADC_TypeDef *ADCx, uint32_t HTRChannel)
{
	MODIFY_REG(ADCx->HTR, ADC_HTR_CH, HTRChannel<<16);
}

/**
  * @function  ADC_Set_LTREN(ADC_TypeDef *ADCx, uint32_t LTREN)
  * @brief  When LTREN is enabled,the ADC conversion value will be read to the ADC_LTR register after convert the ADC_LTRCH channel 
  * @param  ADCx:
  *         @arg ADC Instance
  * @param  FilterLevel:
  *         @ref ADC_LTR_Enable
  *         @ref ADC_LTR_Disable			
  * @retval None
  */
__STATIC_INLINE void ADC_Set_LTREN(ADC_TypeDef *ADCx, uint32_t LTREN)
{
	SET_BIT(ADCx->HTR,LTREN);
}

/**
  * @function  ADC_Set_LTRChannel(ADC_TypeDef *ADCx, uint32_t LTRCH)
  * @brief  Set the ADC_LTRCH channel
  * @param  ADCx:
  *         @arg ADC Instance
  * @param  FilterLevel:
  *         @ref ADC_CHANNEL_0_NUMBER
  *         @ref ADC_CHANNEL_1_NUMBER  
  *         @ref ADC_CHANNEL_2_NUMBER
  *         @ref ADC_CHANNEL_3_NUMBER
  *         @ref ADC_CHANNEL_4_NUMBER
  *         @ref ADC_CHANNEL_5_NUMBER
  *         @ref ADC_CHANNEL_6_NUMBER
  *         @ref ADC_CHANNEL_7_NUMBER
  *         @ref ADC_CHANNEL_8_NUMBER
  *         @ref ADC_CHANNEL_9_NUMBER
  *         @ref ADC_CHANNEL_10_NUMBER
  *         @ref ADC_CHANNEL_11_NUMBER
  *         @ref ADC_CHANNEL_12_NUMBER
  *         @ref ADC_CHANNEL_13_NUMBER
  *         @ref ADC_CHANNEL_14_NUMBER
  *         @ref ADC_CHANNEL_15_NUMBER
  *         @ref ADC_CHANNEL_16_NUMBER
  *         @ref ADC_CHANNEL_17_NUMBER
  *         @ref ADC_CHANNEL_18_NUMBER  
  *         @ref ADC_CHANNEL_19_NUMBER 
  *         @ref ADC_CHANNEL_20_NUMBER
  *         @ref ADC_CHANNEL_21_NUMBER
  *         @ref ADC_CHANNEL_22_NUMBER
  *         @ref ADC_CHANNEL_23_NUMBER
  * @retval None
  */
__STATIC_INLINE void ADC_Set_LTRChannel(ADC_TypeDef *ADCx, uint32_t LTRChannel)
{
	MODIFY_REG(ADCx->HTR, ADC_HTR_CH, LTRChannel<<16);
}


void ADC_Reg_StructInit(ADC_Reg_InitTypeDef* ADC_Reg_InitStruct);
void ADC_Reg_Init(ADC_TypeDef *ADCx,ADC_Reg_InitTypeDef* ADC_Reg_InitStruct);
void ADC_Inj_StructInit(ADC_Inj_InitTypeDef* ADC_Inj_InitStruct);
void ADC_Inj_Init(ADC_TypeDef *ADCx,ADC_Inj_InitTypeDef* ADC_Inj_InitStruct);
void ADC_REG_RankInit(ADC_TypeDef* ADCx,ADC_REG_RankInitTypeDef* ADC_REG_RankInitStruct);
void ADC_INJ_RankInit(ADC_TypeDef* ADCx,ADC_INJ_RankInitTypeDef* ADC_INJ_RankInitStruct);
void ADC_Trig_CAL(ADC_TypeDef *ADCx);


#ifdef __cplusplus
}
#endif

#endif /* __rx32h6xx_ADC_H__ */
