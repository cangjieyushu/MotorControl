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
* File         : rx32h6xx_tim.h
* By           : RX_SD_Team
* Version      : V1.0.0
* Description  : Only rx32h6xx
*********************************************************************************************************
*/
#ifndef _rx32h6xx_TIM_H
#define _rx32h6xx_TIM_H

#ifdef __cplusplus
extern "C" {
#endif
	
#include "rx32h6xx.h"

/*******************  Bit definition for TIM_CR1 register  ********************/
#define TIM_CR1_CEN_Pos           (0U)
#define TIM_CR1_CEN_Msk           (0x1UL << TIM_CR1_CEN_Pos)                   /*!< 0x00000001 */
#define TIM_CR1_CEN               TIM_CR1_CEN_Msk                              /*!<Counter enable */
#define TIM_CR1_UDIS_Pos          (1U)
#define TIM_CR1_UDIS_Msk          (0x1UL << TIM_CR1_UDIS_Pos)                  /*!< 0x00000002 */
#define TIM_CR1_UDIS              TIM_CR1_UDIS_Msk                             /*!<Update disable */
#define TIM_CR1_URS_Pos           (2U)
#define TIM_CR1_URS_Msk           (0x1UL << TIM_CR1_URS_Pos)                   /*!< 0x00000004 */
#define TIM_CR1_URS               TIM_CR1_URS_Msk                              /*!<Update request source */
#define TIM_CR1_OPM_Pos           (3U)
#define TIM_CR1_OPM_Msk           (0x1UL << TIM_CR1_OPM_Pos)                   /*!< 0x00000008 */
#define TIM_CR1_OPM               TIM_CR1_OPM_Msk                              /*!<One pulse mode */
#define TIM_CR1_DIR_Pos           (4U)
#define TIM_CR1_DIR_Msk           (0x1UL << TIM_CR1_DIR_Pos)                   /*!< 0x00000010 */
#define TIM_CR1_DIR               TIM_CR1_DIR_Msk                              /*!<Direction */

#define TIM_CR1_CMS_Pos           (5U)
#define TIM_CR1_CMS_Msk           (0x3UL << TIM_CR1_CMS_Pos)                   /*!< 0x00000060 */
#define TIM_CR1_CMS               TIM_CR1_CMS_Msk                              /*!<CMS[1:0] bits (Center-aligned mode selection) */
#define TIM_CR1_CMS_0             (0x1UL << TIM_CR1_CMS_Pos)                   /*!< 0x00000020 */
#define TIM_CR1_CMS_1             (0x2UL << TIM_CR1_CMS_Pos)                   /*!< 0x00000040 */

#define TIM_CR1_ARPE_Pos          (7U)
#define TIM_CR1_ARPE_Msk          (0x1UL << TIM_CR1_ARPE_Pos)                  /*!< 0x00000080 */
#define TIM_CR1_ARPE              TIM_CR1_ARPE_Msk                             /*!<Auto-reload preload enable */

#define TIM_CR1_CKD_Pos           (8U)
#define TIM_CR1_CKD_Msk           (0x3UL << TIM_CR1_CKD_Pos)                   /*!< 0x00000300 */
#define TIM_CR1_CKD               TIM_CR1_CKD_Msk                              /*!<CKD[1:0] bits (clock division) */
#define TIM_CR1_CKD_0             (0x1UL << TIM_CR1_CKD_Pos)                   /*!< 0x00000100 */
#define TIM_CR1_CKD_1             (0x2UL << TIM_CR1_CKD_Pos)                   /*!< 0x00000200 */

#define TIM_CR1_UIFREMAP_Pos      (11U)
#define TIM_CR1_UIFREMAP_Msk      (0x1UL << TIM_CR1_UIFREMAP_Pos)              /*!< 0x00000800 */
#define TIM_CR1_UIFREMAP          TIM_CR1_UIFREMAP_Msk                         /*!<Update interrupt flag remap */

#define TIM_CR1_DITHEN_Pos      (12U)
#define TIM_CR1_DITHEN_Msk      (0x1UL << TIM_CR1_DITHEN_Pos)                  /*!< 0x00001000 */
#define TIM_CR1_DITHEN          TIM_CR1_DITHEN_Msk                             /*!<Dithering enable */

/*******************  Bit definition for TIM_CR2 register  ********************/
#define TIM_CR2_CCPC_Pos          (0U)
#define TIM_CR2_CCPC_Msk          (0x1UL << TIM_CR2_CCPC_Pos)                  /*!< 0x00000001 */
#define TIM_CR2_CCPC              TIM_CR2_CCPC_Msk                             /*!<Capture/Compare Preloaded Control */
#define TIM_CR2_CCUS_Pos          (2U)
#define TIM_CR2_CCUS_Msk          (0x1UL << TIM_CR2_CCUS_Pos)                  /*!< 0x00000004 */
#define TIM_CR2_CCUS              TIM_CR2_CCUS_Msk                             /*!<Capture/Compare Control Update Selection */

#define TIM_CR2_MMS_Pos           (4U)
#define TIM_CR2_MMS_Msk           (0x200007UL << TIM_CR2_MMS_Pos)              /*!< 0x02000070 */
#define TIM_CR2_MMS               TIM_CR2_MMS_Msk                              /*!<MMS[3:0] bits (Master Mode Selection) */
#define TIM_CR2_MMS_0             (0x000001UL << TIM_CR2_MMS_Pos)              /*!< 0x00000010 */
#define TIM_CR2_MMS_1             (0x000002UL << TIM_CR2_MMS_Pos)              /*!< 0x00000020 */
#define TIM_CR2_MMS_2             (0x000004UL << TIM_CR2_MMS_Pos)              /*!< 0x00000040 */
#define TIM_CR2_MMS_3             (0x200000UL << TIM_CR2_MMS_Pos)              /*!< 0x02000000 */

#define TIM_CR2_TI1S_Pos          (7U)
#define TIM_CR2_TI1S_Msk          (0x1UL << TIM_CR2_TI1S_Pos)                  /*!< 0x00000080 */
#define TIM_CR2_TI1S              TIM_CR2_TI1S_Msk                             /*!<TI1 Selection */
#define TIM_CR2_OIS1_Pos          (8U)
#define TIM_CR2_OIS1_Msk          (0x1UL << TIM_CR2_OIS1_Pos)                  /*!< 0x00000100 */
#define TIM_CR2_OIS1              TIM_CR2_OIS1_Msk                             /*!<Output Idle state 1 (OC1 output) */
#define TIM_CR2_OIS1N_Pos         (9U)
#define TIM_CR2_OIS1N_Msk         (0x1UL << TIM_CR2_OIS1N_Pos)                 /*!< 0x00000200 */
#define TIM_CR2_OIS1N             TIM_CR2_OIS1N_Msk                            /*!<Output Idle state 1 (OC1N output) */
#define TIM_CR2_OIS2_Pos          (10U)
#define TIM_CR2_OIS2_Msk          (0x1UL << TIM_CR2_OIS2_Pos)                  /*!< 0x00000400 */
#define TIM_CR2_OIS2              TIM_CR2_OIS2_Msk                             /*!<Output Idle state 2 (OC2 output) */
#define TIM_CR2_OIS2N_Pos         (11U)
#define TIM_CR2_OIS2N_Msk         (0x1UL << TIM_CR2_OIS2N_Pos)                 /*!< 0x00000800 */
#define TIM_CR2_OIS2N             TIM_CR2_OIS2N_Msk                            /*!<Output Idle state 2 (OC2N output) */
#define TIM_CR2_OIS3_Pos          (12U)
#define TIM_CR2_OIS3_Msk          (0x1UL << TIM_CR2_OIS3_Pos)                  /*!< 0x00001000 */
#define TIM_CR2_OIS3              TIM_CR2_OIS3_Msk                             /*!<Output Idle state 3 (OC3 output) */
#define TIM_CR2_OIS3N_Pos         (13U)
#define TIM_CR2_OIS3N_Msk         (0x1UL << TIM_CR2_OIS3N_Pos)                 /*!< 0x00002000 */
#define TIM_CR2_OIS3N             TIM_CR2_OIS3N_Msk                            /*!<Output Idle state 3 (OC3N output) */
#define TIM_CR2_OIS4_Pos          (14U)
#define TIM_CR2_OIS4_Msk          (0x1UL << TIM_CR2_OIS4_Pos)                  /*!< 0x00004000 */
#define TIM_CR2_OIS4              TIM_CR2_OIS4_Msk                             /*!<Output Idle state 4 (OC4 output) */
#define TIM_CR2_OIS5_Pos          (16U)
#define TIM_CR2_OIS5_Msk          (0x1UL << TIM_CR2_OIS5_Pos)                  /*!< 0x00010000 */
#define TIM_CR2_OIS5              TIM_CR2_OIS5_Msk                             /*!<Output Idle state 5 (OC5 output) */
#define TIM_CR2_OIS6_Pos          (18U)
#define TIM_CR2_OIS6_Msk          (0x1UL << TIM_CR2_OIS6_Pos)                  /*!< 0x00040000 */
#define TIM_CR2_OIS6              TIM_CR2_OIS6_Msk                             /*!<Output Idle state 6 (OC6 output) */

#define TIM_CR2_MMS2_Pos          (20U)
#define TIM_CR2_MMS2_Msk          (0xFUL << TIM_CR2_MMS2_Pos)                  /*!< 0x00F00000 */
#define TIM_CR2_MMS2              TIM_CR2_MMS2_Msk                             /*!<MMS[2:0] bits (Master Mode Selection) */
#define TIM_CR2_MMS2_0            (0x1UL << TIM_CR2_MMS2_Pos)                  /*!< 0x00100000 */
#define TIM_CR2_MMS2_1            (0x2UL << TIM_CR2_MMS2_Pos)                  /*!< 0x00200000 */
#define TIM_CR2_MMS2_2            (0x4UL << TIM_CR2_MMS2_Pos)                  /*!< 0x00400000 */
#define TIM_CR2_MMS2_3            (0x8UL << TIM_CR2_MMS2_Pos)                  /*!< 0x00800000 */

/*******************  Bit definition for TIM_SMCR register  *******************/
#define TIM_SMCR_SMS_Pos          (0U)
#define TIM_SMCR_SMS_Msk          (0x10007UL << TIM_SMCR_SMS_Pos)              /*!< 0x00010007 */
#define TIM_SMCR_SMS              TIM_SMCR_SMS_Msk                             /*!<SMS[2:0] bits (Slave mode selection) */
#define TIM_SMCR_SMS_0            (0x00001UL << TIM_SMCR_SMS_Pos)              /*!< 0x00000001 */
#define TIM_SMCR_SMS_1            (0x00002UL << TIM_SMCR_SMS_Pos)              /*!< 0x00000002 */
#define TIM_SMCR_SMS_2            (0x00004UL << TIM_SMCR_SMS_Pos)              /*!< 0x00000004 */
#define TIM_SMCR_SMS_3            (0x10000UL << TIM_SMCR_SMS_Pos)              /*!< 0x00010000 */

#define TIM_SMCR_OCCS_Pos         (3U)
#define TIM_SMCR_OCCS_Msk         (0x1UL << TIM_SMCR_OCCS_Pos)                 /*!< 0x00000008 */
#define TIM_SMCR_OCCS             TIM_SMCR_OCCS_Msk                            /*!< OCREF clear selection */

#define TIM_SMCR_TS_Pos           (4U)
#define TIM_SMCR_TS_Msk           (0x30007UL << TIM_SMCR_TS_Pos)               /*!< 0x00300070 */
#define TIM_SMCR_TS               TIM_SMCR_TS_Msk                              /*!<TS[2:0] bits (Trigger selection) */
#define TIM_SMCR_TS_0             (0x00001UL << TIM_SMCR_TS_Pos)               /*!< 0x00000010 */
#define TIM_SMCR_TS_1             (0x00002UL << TIM_SMCR_TS_Pos)               /*!< 0x00000020 */
#define TIM_SMCR_TS_2             (0x00004UL << TIM_SMCR_TS_Pos)               /*!< 0x00000040 */
#define TIM_SMCR_TS_3             (0x10000UL << TIM_SMCR_TS_Pos)               /*!< 0x00100000 */
#define TIM_SMCR_TS_4             (0x20000UL << TIM_SMCR_TS_Pos)               /*!< 0x00200000 */

#define TIM_SMCR_MSM_Pos          (7U)
#define TIM_SMCR_MSM_Msk          (0x1UL << TIM_SMCR_MSM_Pos)                  /*!< 0x00000080 */
#define TIM_SMCR_MSM              TIM_SMCR_MSM_Msk                             /*!<Master/slave mode */

#define TIM_SMCR_ETF_Pos          (8U)
#define TIM_SMCR_ETF_Msk          (0xFUL << TIM_SMCR_ETF_Pos)                  /*!< 0x00000F00 */
#define TIM_SMCR_ETF              TIM_SMCR_ETF_Msk                             /*!<ETF[3:0] bits (External trigger filter) */
#define TIM_SMCR_ETF_0            (0x1UL << TIM_SMCR_ETF_Pos)                  /*!< 0x00000100 */
#define TIM_SMCR_ETF_1            (0x2UL << TIM_SMCR_ETF_Pos)                  /*!< 0x00000200 */
#define TIM_SMCR_ETF_2            (0x4UL << TIM_SMCR_ETF_Pos)                  /*!< 0x00000400 */
#define TIM_SMCR_ETF_3            (0x8UL << TIM_SMCR_ETF_Pos)                  /*!< 0x00000800 */

#define TIM_SMCR_ETPS_Pos         (12U)
#define TIM_SMCR_ETPS_Msk         (0x3UL << TIM_SMCR_ETPS_Pos)                 /*!< 0x00003000 */
#define TIM_SMCR_ETPS             TIM_SMCR_ETPS_Msk                            /*!<ETPS[1:0] bits (External trigger prescaler) */
#define TIM_SMCR_ETPS_0           (0x1UL << TIM_SMCR_ETPS_Pos)                 /*!< 0x00001000 */
#define TIM_SMCR_ETPS_1           (0x2UL << TIM_SMCR_ETPS_Pos)                 /*!< 0x00002000 */

#define TIM_SMCR_ECE_Pos          (14U)
#define TIM_SMCR_ECE_Msk          (0x1UL << TIM_SMCR_ECE_Pos)                  /*!< 0x00004000 */
#define TIM_SMCR_ECE              TIM_SMCR_ECE_Msk                             /*!<External clock enable */
#define TIM_SMCR_ETP_Pos          (15U)
#define TIM_SMCR_ETP_Msk          (0x1UL << TIM_SMCR_ETP_Pos)                  /*!< 0x00008000 */
#define TIM_SMCR_ETP              TIM_SMCR_ETP_Msk                             /*!<External trigger polarity */

#define TIM_SMCR_SMSPE_Pos        (24U)
#define TIM_SMCR_SMSPE_Msk        (0x1UL << TIM_SMCR_SMSPE_Pos)                /*!< 0x02000000 */
#define TIM_SMCR_SMSPE            TIM_SMCR_SMSPE_Msk                           /*!<SMS preload enable */

#define TIM_SMCR_SMSPS_Pos        (25U)
#define TIM_SMCR_SMSPS_Msk        (0x1UL << TIM_SMCR_SMSPS_Pos)                /*!< 0x04000000 */
#define TIM_SMCR_SMSPS            TIM_SMCR_SMSPS_Msk                           /*!<SMS preload source */

/*******************  Bit definition for TIM_DIER register  *******************/
#define TIM_DIER_UIE_Pos          (0U)
#define TIM_DIER_UIE_Msk          (0x1UL << TIM_DIER_UIE_Pos)                  /*!< 0x00000001 */
#define TIM_DIER_UIE              TIM_DIER_UIE_Msk                             /*!<Update interrupt enable */
#define TIM_DIER_CC1IE_Pos        (1U)
#define TIM_DIER_CC1IE_Msk        (0x1UL << TIM_DIER_CC1IE_Pos)                /*!< 0x00000002 */
#define TIM_DIER_CC1IE            TIM_DIER_CC1IE_Msk                           /*!<Capture/Compare 1 interrupt enable */
#define TIM_DIER_CC2IE_Pos        (2U)
#define TIM_DIER_CC2IE_Msk        (0x1UL << TIM_DIER_CC2IE_Pos)                /*!< 0x00000004 */
#define TIM_DIER_CC2IE            TIM_DIER_CC2IE_Msk                           /*!<Capture/Compare 2 interrupt enable */
#define TIM_DIER_CC3IE_Pos        (3U)
#define TIM_DIER_CC3IE_Msk        (0x1UL << TIM_DIER_CC3IE_Pos)                /*!< 0x00000008 */
#define TIM_DIER_CC3IE            TIM_DIER_CC3IE_Msk                           /*!<Capture/Compare 3 interrupt enable */
#define TIM_DIER_CC4IE_Pos        (4U)
#define TIM_DIER_CC4IE_Msk        (0x1UL << TIM_DIER_CC4IE_Pos)                /*!< 0x00000010 */
#define TIM_DIER_CC4IE            TIM_DIER_CC4IE_Msk                           /*!<Capture/Compare 4 interrupt enable */
#define TIM_DIER_COMIE_Pos        (5U)
#define TIM_DIER_COMIE_Msk        (0x1UL << TIM_DIER_COMIE_Pos)                /*!< 0x00000020 */
#define TIM_DIER_COMIE            TIM_DIER_COMIE_Msk                           /*!<COM interrupt enable */
#define TIM_DIER_TIE_Pos          (6U)
#define TIM_DIER_TIE_Msk          (0x1UL << TIM_DIER_TIE_Pos)                  /*!< 0x00000040 */
#define TIM_DIER_TIE              TIM_DIER_TIE_Msk                             /*!<Trigger interrupt enable */
#define TIM_DIER_BIE_Pos          (7U)
#define TIM_DIER_BIE_Msk          (0x1UL << TIM_DIER_BIE_Pos)                  /*!< 0x00000080 */
#define TIM_DIER_BIE              TIM_DIER_BIE_Msk                             /*!<Break interrupt enable */
#define TIM_DIER_CC5IE_Pos        (15U)
#define TIM_DIER_CC5IE_Msk        (0x1UL << TIM_DIER_CC5IE_Pos)                /*!< 0x00000010 */
#define TIM_DIER_CC5IE            TIM_DIER_CC5IE_Msk
#define TIM_DIER_CC6IE_Pos        (17U)
#define TIM_DIER_CC6IE_Msk        (0x1UL << TIM_DIER_CC6IE_Pos)                /*!< 0x00000010 */
#define TIM_DIER_CC6IE            TIM_DIER_CC6IE_Msk
#define TIM_DIER_IDXIE_Pos        (20U)
#define TIM_DIER_IDXIE_Msk        (0x1UL << TIM_DIER_IDXIE_Pos)                /*!< 0x00100000 */
#define TIM_DIER_IDXIE            TIM_DIER_IDXIE_Msk                           /*!<Encoder index interrupt enable */
#define TIM_DIER_DIRIE_Pos        (21U)
#define TIM_DIER_DIRIE_Msk        (0x1UL << TIM_DIER_DIRIE_Pos)                /*!< 0x00200000 */
#define TIM_DIER_DIRIE            TIM_DIER_DIRIE_Msk                           /*!<Encoder direction change interrupt enable */
#define TIM_DIER_IERRIE_Pos       (22U)
#define TIM_DIER_IERRIE_Msk       (0x1UL << TIM_DIER_IERRIE_Pos)               /*!< 0x00400000 */
#define TIM_DIER_IERRIE           TIM_DIER_IERRIE_Msk                          /*!<Encoder index error enable */
#define TIM_DIER_TERRIE_Pos       (23U)
#define TIM_DIER_TERRIE_Msk       (0x1UL << TIM_DIER_TERRIE_Pos)               /*!< 0x00800000 */
#define TIM_DIER_TERRIE           TIM_DIER_TERRIE_Msk                          /*!<Encoder transition error enable */

/********************  Bit definition for TIM_SR register  ********************/
#define TIM_SR_UIF_Pos            (0U)
#define TIM_SR_UIF_Msk            (0x1UL << TIM_SR_UIF_Pos)                    /*!< 0x00000001 */
#define TIM_SR_UIF                TIM_SR_UIF_Msk                               /*!<Update interrupt Flag */
#define TIM_SR_CC1IF_Pos          (1U)
#define TIM_SR_CC1IF_Msk          (0x1UL << TIM_SR_CC1IF_Pos)                  /*!< 0x00000002 */
#define TIM_SR_CC1IF              TIM_SR_CC1IF_Msk                             /*!<Capture/Compare 1 interrupt Flag */
#define TIM_SR_CC2IF_Pos          (2U)
#define TIM_SR_CC2IF_Msk          (0x1UL << TIM_SR_CC2IF_Pos)                  /*!< 0x00000004 */
#define TIM_SR_CC2IF              TIM_SR_CC2IF_Msk                             /*!<Capture/Compare 2 interrupt Flag */
#define TIM_SR_CC3IF_Pos          (3U)
#define TIM_SR_CC3IF_Msk          (0x1UL << TIM_SR_CC3IF_Pos)                  /*!< 0x00000008 */
#define TIM_SR_CC3IF              TIM_SR_CC3IF_Msk                             /*!<Capture/Compare 3 interrupt Flag */
#define TIM_SR_CC4IF_Pos          (4U)
#define TIM_SR_CC4IF_Msk          (0x1UL << TIM_SR_CC4IF_Pos)                  /*!< 0x00000010 */
#define TIM_SR_CC4IF              TIM_SR_CC4IF_Msk                             /*!<Capture/Compare 4 interrupt Flag */
#define TIM_SR_COMIF_Pos          (5U)
#define TIM_SR_COMIF_Msk          (0x1UL << TIM_SR_COMIF_Pos)                  /*!< 0x00000020 */
#define TIM_SR_COMIF              TIM_SR_COMIF_Msk                             /*!<COM interrupt Flag */
#define TIM_SR_TIF_Pos            (6U)
#define TIM_SR_TIF_Msk            (0x1UL << TIM_SR_TIF_Pos)                    /*!< 0x00000040 */
#define TIM_SR_TIF                TIM_SR_TIF_Msk                               /*!<Trigger interrupt Flag */
#define TIM_SR_BIF_Pos            (7U)
#define TIM_SR_BIF_Msk            (0x1UL << TIM_SR_BIF_Pos)                    /*!< 0x00000080 */
#define TIM_SR_BIF                TIM_SR_BIF_Msk                               /*!<Break interrupt Flag */
#define TIM_SR_B2IF_Pos           (8U)
#define TIM_SR_B2IF_Msk           (0x1UL << TIM_SR_B2IF_Pos)                   /*!< 0x00000100 */
#define TIM_SR_B2IF               TIM_SR_B2IF_Msk                              /*!<Break 2 interrupt Flag */
#define TIM_SR_CC1OF_Pos          (9U)
#define TIM_SR_CC1OF_Msk          (0x1UL << TIM_SR_CC1OF_Pos)                  /*!< 0x00000200 */
#define TIM_SR_CC1OF              TIM_SR_CC1OF_Msk                             /*!<Capture/Compare 1 Overcapture Flag */
#define TIM_SR_CC2OF_Pos          (10U)
#define TIM_SR_CC2OF_Msk          (0x1UL << TIM_SR_CC2OF_Pos)                  /*!< 0x00000400 */
#define TIM_SR_CC2OF              TIM_SR_CC2OF_Msk                             /*!<Capture/Compare 2 Overcapture Flag */
#define TIM_SR_CC3OF_Pos          (11U)
#define TIM_SR_CC3OF_Msk          (0x1UL << TIM_SR_CC3OF_Pos)                  /*!< 0x00000800 */
#define TIM_SR_CC3OF              TIM_SR_CC3OF_Msk                             /*!<Capture/Compare 3 Overcapture Flag */
#define TIM_SR_CC4OF_Pos          (12U)
#define TIM_SR_CC4OF_Msk          (0x1UL << TIM_SR_CC4OF_Pos)                  /*!< 0x00001000 */
#define TIM_SR_CC4OF              TIM_SR_CC4OF_Msk                             /*!<Capture/Compare 4 Overcapture Flag */
#define TIM_SR_SBIF_Pos           (13U)
#define TIM_SR_SBIF_Msk           (0x1UL << TIM_SR_SBIF_Pos)                   /*!< 0x00002000 */
#define TIM_SR_SBIF               TIM_SR_SBIF_Msk                              /*!<System Break interrupt Flag */
#define TIM_SR_CC5IF_Pos          (16U)
#define TIM_SR_CC5IF_Msk          (0x1UL << TIM_SR_CC5IF_Pos)                  /*!< 0x00010000 */
#define TIM_SR_CC5IF              TIM_SR_CC5IF_Msk                             /*!<Capture/Compare 5 interrupt Flag */
#define TIM_SR_CC6IF_Pos          (17U)
#define TIM_SR_CC6IF_Msk          (0x1UL << TIM_SR_CC6IF_Pos)                  /*!< 0x00020000 */
#define TIM_SR_CC6IF              TIM_SR_CC6IF_Msk                             /*!<Capture/Compare 6 interrupt Flag */
#define TIM_SR_IDXF_Pos           (20U)
#define TIM_SR_IDXF_Msk           (0x1UL << TIM_SR_IDXF_Pos)                   /*!< 0x00100000 */
#define TIM_SR_IDXF               TIM_SR_IDXF_Msk                              /*!<Encoder index interrupt flag */
#define TIM_SR_DIRF_Pos           (21U)
#define TIM_SR_DIRF_Msk           (0x1UL << TIM_SR_DIRF_Pos)                   /*!< 0x00200000 */
#define TIM_SR_DIRF               TIM_SR_DIRF_Msk                              /*!<Encoder direction change interrupt flag */
#define TIM_SR_IERRF_Pos          (22U)
#define TIM_SR_IERRF_Msk          (0x1UL << TIM_SR_IERRF_Pos)                  /*!< 0x00400000 */
#define TIM_SR_IERRF              TIM_SR_IERRF_Msk                             /*!<Encoder index error flag */
#define TIM_SR_TERRF_Pos          (23U)
#define TIM_SR_TERRF_Msk          (0x1UL << TIM_SR_TERRF_Pos)                  /*!< 0x00800000 */
#define TIM_SR_TERRF              TIM_SR_TERRF_Msk                             /*!<Encoder transition error flag */

/*******************  Bit definition for TIM_EGR register  ********************/
#define TIM_EGR_UG_Pos            (0U)
#define TIM_EGR_UG_Msk            (0x1UL << TIM_EGR_UG_Pos)                    /*!< 0x00000001 */
#define TIM_EGR_UG                TIM_EGR_UG_Msk                               /*!<Update Generation */
#define TIM_EGR_CC1G_Pos          (1U)
#define TIM_EGR_CC1G_Msk          (0x1UL << TIM_EGR_CC1G_Pos)                  /*!< 0x00000002 */
#define TIM_EGR_CC1G              TIM_EGR_CC1G_Msk                             /*!<Capture/Compare 1 Generation */
#define TIM_EGR_CC2G_Pos          (2U)
#define TIM_EGR_CC2G_Msk          (0x1UL << TIM_EGR_CC2G_Pos)                  /*!< 0x00000004 */
#define TIM_EGR_CC2G              TIM_EGR_CC2G_Msk                             /*!<Capture/Compare 2 Generation */
#define TIM_EGR_CC3G_Pos          (3U)
#define TIM_EGR_CC3G_Msk          (0x1UL << TIM_EGR_CC3G_Pos)                  /*!< 0x00000008 */
#define TIM_EGR_CC3G              TIM_EGR_CC3G_Msk                             /*!<Capture/Compare 3 Generation */
#define TIM_EGR_CC4G_Pos          (4U)
#define TIM_EGR_CC4G_Msk          (0x1UL << TIM_EGR_CC4G_Pos)                  /*!< 0x00000010 */
#define TIM_EGR_CC4G              TIM_EGR_CC4G_Msk                             /*!<Capture/Compare 4 Generation */
#define TIM_EGR_COMG_Pos          (5U)
#define TIM_EGR_COMG_Msk          (0x1UL << TIM_EGR_COMG_Pos)                  /*!< 0x00000020 */
#define TIM_EGR_COMG              TIM_EGR_COMG_Msk                             /*!<Capture/Compare Control Update Generation */
#define TIM_EGR_TG_Pos            (6U)
#define TIM_EGR_TG_Msk            (0x1UL << TIM_EGR_TG_Pos)                    /*!< 0x00000040 */
#define TIM_EGR_TG                TIM_EGR_TG_Msk                               /*!<Trigger Generation */
#define TIM_EGR_BG_Pos            (7U)
#define TIM_EGR_BG_Msk            (0x1UL << TIM_EGR_BG_Pos)                    /*!< 0x00000080 */
#define TIM_EGR_BG                TIM_EGR_BG_Msk                               /*!<Break Generation */
#define TIM_EGR_B2G_Pos           (8U)
#define TIM_EGR_B2G_Msk           (0x1UL << TIM_EGR_B2G_Pos)                   /*!< 0x00000100 */
#define TIM_EGR_B2G               TIM_EGR_B2G_Msk                              /*!<Break 2 Generation */

/******************  Bit definition for TIM_CCMR1 register  *******************/
#define TIM_CCMR1_CC1S_Pos        (0U)
#define TIM_CCMR1_CC1S_Msk        (0x3UL << TIM_CCMR1_CC1S_Pos)                /*!< 0x00000003 */
#define TIM_CCMR1_CC1S            TIM_CCMR1_CC1S_Msk                           /*!<CC1S[1:0] bits (Capture/Compare 1 Selection) */
#define TIM_CCMR1_CC1S_0          (0x1UL << TIM_CCMR1_CC1S_Pos)                /*!< 0x00000001 */
#define TIM_CCMR1_CC1S_1          (0x2UL << TIM_CCMR1_CC1S_Pos)                /*!< 0x00000002 */

#define TIM_CCMR1_OC1FE_Pos       (2U)
#define TIM_CCMR1_OC1FE_Msk       (0x1UL << TIM_CCMR1_OC1FE_Pos)               /*!< 0x00000004 */
#define TIM_CCMR1_OC1FE           TIM_CCMR1_OC1FE_Msk                          /*!<Output Compare 1 Fast enable */
#define TIM_CCMR1_OC1PE_Pos       (3U)
#define TIM_CCMR1_OC1PE_Msk       (0x1UL << TIM_CCMR1_OC1PE_Pos)               /*!< 0x00000008 */
#define TIM_CCMR1_OC1PE           TIM_CCMR1_OC1PE_Msk                          /*!<Output Compare 1 Preload enable */

#define TIM_CCMR1_OC1M_Pos        (4U)
#define TIM_CCMR1_OC1M_Msk        (0x1007UL << TIM_CCMR1_OC1M_Pos)             /*!< 0x00010070 */
#define TIM_CCMR1_OC1M            TIM_CCMR1_OC1M_Msk                           /*!<OC1M[2:0] bits (Output Compare 1 Mode) */
#define TIM_CCMR1_OC1M_0          (0x0001UL << TIM_CCMR1_OC1M_Pos)             /*!< 0x00000010 */
#define TIM_CCMR1_OC1M_1          (0x0002UL << TIM_CCMR1_OC1M_Pos)             /*!< 0x00000020 */
#define TIM_CCMR1_OC1M_2          (0x0004UL << TIM_CCMR1_OC1M_Pos)             /*!< 0x00000040 */
#define TIM_CCMR1_OC1M_3          (0x1000UL << TIM_CCMR1_OC1M_Pos)             /*!< 0x00010000 */

#define TIM_CCMR1_OC1CE_Pos       (7U)
#define TIM_CCMR1_OC1CE_Msk       (0x1UL << TIM_CCMR1_OC1CE_Pos)               /*!< 0x00000080 */
#define TIM_CCMR1_OC1CE           TIM_CCMR1_OC1CE_Msk                          /*!<Output Compare 1 Clear Enable */

#define TIM_CCMR1_CC2S_Pos        (8U)
#define TIM_CCMR1_CC2S_Msk        (0x3UL << TIM_CCMR1_CC2S_Pos)                /*!< 0x00000300 */
#define TIM_CCMR1_CC2S            TIM_CCMR1_CC2S_Msk                           /*!<CC2S[1:0] bits (Capture/Compare 2 Selection) */
#define TIM_CCMR1_CC2S_0          (0x1UL << TIM_CCMR1_CC2S_Pos)                /*!< 0x00000100 */
#define TIM_CCMR1_CC2S_1          (0x2UL << TIM_CCMR1_CC2S_Pos)                /*!< 0x00000200 */

#define TIM_CCMR1_OC2FE_Pos       (10U)
#define TIM_CCMR1_OC2FE_Msk       (0x1UL << TIM_CCMR1_OC2FE_Pos)               /*!< 0x00000400 */
#define TIM_CCMR1_OC2FE           TIM_CCMR1_OC2FE_Msk                          /*!<Output Compare 2 Fast enable */
#define TIM_CCMR1_OC2PE_Pos       (11U)
#define TIM_CCMR1_OC2PE_Msk       (0x1UL << TIM_CCMR1_OC2PE_Pos)               /*!< 0x00000800 */
#define TIM_CCMR1_OC2PE           TIM_CCMR1_OC2PE_Msk                          /*!<Output Compare 2 Preload enable */

#define TIM_CCMR1_OC2M_Pos        (12U)
#define TIM_CCMR1_OC2M_Msk        (0x1007UL << TIM_CCMR1_OC2M_Pos)             /*!< 0x01007000 */
#define TIM_CCMR1_OC2M            TIM_CCMR1_OC2M_Msk                           /*!<OC2M[2:0] bits (Output Compare 2 Mode) */
#define TIM_CCMR1_OC2M_0          (0x0001UL << TIM_CCMR1_OC2M_Pos)             /*!< 0x00001000 */
#define TIM_CCMR1_OC2M_1          (0x0002UL << TIM_CCMR1_OC2M_Pos)             /*!< 0x00002000 */
#define TIM_CCMR1_OC2M_2          (0x0004UL << TIM_CCMR1_OC2M_Pos)             /*!< 0x00004000 */
#define TIM_CCMR1_OC2M_3          (0x1000UL << TIM_CCMR1_OC2M_Pos)             /*!< 0x01000000 */

#define TIM_CCMR1_OC2CE_Pos       (15U)
#define TIM_CCMR1_OC2CE_Msk       (0x1UL << TIM_CCMR1_OC2CE_Pos)               /*!< 0x00008000 */
#define TIM_CCMR1_OC2CE           TIM_CCMR1_OC2CE_Msk                          /*!<Output Compare 2 Clear Enable */

/*----------------------------------------------------------------------------*/
#define TIM_CCMR1_IC1PSC_Pos      (2U)
#define TIM_CCMR1_IC1PSC_Msk      (0x3UL << TIM_CCMR1_IC1PSC_Pos)              /*!< 0x0000000C */
#define TIM_CCMR1_IC1PSC          TIM_CCMR1_IC1PSC_Msk                         /*!<IC1PSC[1:0] bits (Input Capture 1 Prescaler) */
#define TIM_CCMR1_IC1PSC_0        (0x1UL << TIM_CCMR1_IC1PSC_Pos)              /*!< 0x00000004 */
#define TIM_CCMR1_IC1PSC_1        (0x2UL << TIM_CCMR1_IC1PSC_Pos)              /*!< 0x00000008 */

#define TIM_CCMR1_IC1F_Pos        (4U)
#define TIM_CCMR1_IC1F_Msk        (0xFUL << TIM_CCMR1_IC1F_Pos)                /*!< 0x000000F0 */
#define TIM_CCMR1_IC1F            TIM_CCMR1_IC1F_Msk                           /*!<IC1F[3:0] bits (Input Capture 1 Filter) */
#define TIM_CCMR1_IC1F_0          (0x1UL << TIM_CCMR1_IC1F_Pos)                /*!< 0x00000010 */
#define TIM_CCMR1_IC1F_1          (0x2UL << TIM_CCMR1_IC1F_Pos)                /*!< 0x00000020 */
#define TIM_CCMR1_IC1F_2          (0x4UL << TIM_CCMR1_IC1F_Pos)                /*!< 0x00000040 */
#define TIM_CCMR1_IC1F_3          (0x8UL << TIM_CCMR1_IC1F_Pos)                /*!< 0x00000080 */

#define TIM_CCMR1_IC2PSC_Pos      (10U)
#define TIM_CCMR1_IC2PSC_Msk      (0x3UL << TIM_CCMR1_IC2PSC_Pos)              /*!< 0x00000C00 */
#define TIM_CCMR1_IC2PSC          TIM_CCMR1_IC2PSC_Msk                         /*!<IC2PSC[1:0] bits (Input Capture 2 Prescaler) */
#define TIM_CCMR1_IC2PSC_0        (0x1UL << TIM_CCMR1_IC2PSC_Pos)              /*!< 0x00000400 */
#define TIM_CCMR1_IC2PSC_1        (0x2UL << TIM_CCMR1_IC2PSC_Pos)              /*!< 0x00000800 */

#define TIM_CCMR1_IC2F_Pos        (12U)
#define TIM_CCMR1_IC2F_Msk        (0xFUL << TIM_CCMR1_IC2F_Pos)                /*!< 0x0000F000 */
#define TIM_CCMR1_IC2F            TIM_CCMR1_IC2F_Msk                           /*!<IC2F[3:0] bits (Input Capture 2 Filter) */
#define TIM_CCMR1_IC2F_0          (0x1UL << TIM_CCMR1_IC2F_Pos)                /*!< 0x00001000 */
#define TIM_CCMR1_IC2F_1          (0x2UL << TIM_CCMR1_IC2F_Pos)                /*!< 0x00002000 */
#define TIM_CCMR1_IC2F_2          (0x4UL << TIM_CCMR1_IC2F_Pos)                /*!< 0x00004000 */
#define TIM_CCMR1_IC2F_3          (0x8UL << TIM_CCMR1_IC2F_Pos)                /*!< 0x00008000 */

/******************  Bit definition for TIM_CCMR2 register  *******************/
#define TIM_CCMR2_CC3S_Pos        (0U)
#define TIM_CCMR2_CC3S_Msk        (0x3UL << TIM_CCMR2_CC3S_Pos)                /*!< 0x00000003 */
#define TIM_CCMR2_CC3S            TIM_CCMR2_CC3S_Msk                           /*!<CC3S[1:0] bits (Capture/Compare 3 Selection) */
#define TIM_CCMR2_CC3S_0          (0x1UL << TIM_CCMR2_CC3S_Pos)                /*!< 0x00000001 */
#define TIM_CCMR2_CC3S_1          (0x2UL << TIM_CCMR2_CC3S_Pos)                /*!< 0x00000002 */

#define TIM_CCMR2_OC3FE_Pos       (2U)
#define TIM_CCMR2_OC3FE_Msk       (0x1UL << TIM_CCMR2_OC3FE_Pos)               /*!< 0x00000004 */
#define TIM_CCMR2_OC3FE           TIM_CCMR2_OC3FE_Msk                          /*!<Output Compare 3 Fast enable */
#define TIM_CCMR2_OC3PE_Pos       (3U)
#define TIM_CCMR2_OC3PE_Msk       (0x1UL << TIM_CCMR2_OC3PE_Pos)               /*!< 0x00000008 */
#define TIM_CCMR2_OC3PE           TIM_CCMR2_OC3PE_Msk                          /*!<Output Compare 3 Preload enable */

#define TIM_CCMR2_OC3M_Pos        (4U)
#define TIM_CCMR2_OC3M_Msk        (0x1007UL << TIM_CCMR2_OC3M_Pos)             /*!< 0x00010070 */
#define TIM_CCMR2_OC3M            TIM_CCMR2_OC3M_Msk                           /*!<OC3M[2:0] bits (Output Compare 3 Mode) */
#define TIM_CCMR2_OC3M_0          (0x0001UL << TIM_CCMR2_OC3M_Pos)             /*!< 0x00000010 */
#define TIM_CCMR2_OC3M_1          (0x0002UL << TIM_CCMR2_OC3M_Pos)             /*!< 0x00000020 */
#define TIM_CCMR2_OC3M_2          (0x0004UL << TIM_CCMR2_OC3M_Pos)             /*!< 0x00000040 */
#define TIM_CCMR2_OC3M_3          (0x1000UL << TIM_CCMR2_OC3M_Pos)             /*!< 0x00010000 */

#define TIM_CCMR2_OC3CE_Pos       (7U)
#define TIM_CCMR2_OC3CE_Msk       (0x1UL << TIM_CCMR2_OC3CE_Pos)               /*!< 0x00000080 */
#define TIM_CCMR2_OC3CE           TIM_CCMR2_OC3CE_Msk                          /*!<Output Compare 3 Clear Enable */

#define TIM_CCMR2_CC4S_Pos        (8U)
#define TIM_CCMR2_CC4S_Msk        (0x3UL << TIM_CCMR2_CC4S_Pos)                /*!< 0x00000300 */
#define TIM_CCMR2_CC4S            TIM_CCMR2_CC4S_Msk                           /*!<CC4S[1:0] bits (Capture/Compare 4 Selection) */
#define TIM_CCMR2_CC4S_0          (0x1UL << TIM_CCMR2_CC4S_Pos)                /*!< 0x00000100 */
#define TIM_CCMR2_CC4S_1          (0x2UL << TIM_CCMR2_CC4S_Pos)                /*!< 0x00000200 */

#define TIM_CCMR2_OC4FE_Pos       (10U)
#define TIM_CCMR2_OC4FE_Msk       (0x1UL << TIM_CCMR2_OC4FE_Pos)               /*!< 0x00000400 */
#define TIM_CCMR2_OC4FE           TIM_CCMR2_OC4FE_Msk                          /*!<Output Compare 4 Fast enable */
#define TIM_CCMR2_OC4PE_Pos       (11U)
#define TIM_CCMR2_OC4PE_Msk       (0x1UL << TIM_CCMR2_OC4PE_Pos)               /*!< 0x00000800 */
#define TIM_CCMR2_OC4PE           TIM_CCMR2_OC4PE_Msk                          /*!<Output Compare 4 Preload enable */

#define TIM_CCMR2_OC4M_Pos        (12U)
#define TIM_CCMR2_OC4M_Msk        (0x1007UL << TIM_CCMR2_OC4M_Pos)             /*!< 0x01007000 */
#define TIM_CCMR2_OC4M            TIM_CCMR2_OC4M_Msk                           /*!<OC4M[2:0] bits (Output Compare 4 Mode) */
#define TIM_CCMR2_OC4M_0          (0x0001UL << TIM_CCMR2_OC4M_Pos)             /*!< 0x00001000 */
#define TIM_CCMR2_OC4M_1          (0x0002UL << TIM_CCMR2_OC4M_Pos)             /*!< 0x00002000 */
#define TIM_CCMR2_OC4M_2          (0x0004UL << TIM_CCMR2_OC4M_Pos)             /*!< 0x00004000 */
#define TIM_CCMR2_OC4M_3          (0x1000UL << TIM_CCMR2_OC4M_Pos)             /*!< 0x01000000 */

#define TIM_CCMR2_OC4CE_Pos       (15U)
#define TIM_CCMR2_OC4CE_Msk       (0x1UL << TIM_CCMR2_OC4CE_Pos)               /*!< 0x00008000 */
#define TIM_CCMR2_OC4CE           TIM_CCMR2_OC4CE_Msk                          /*!<Output Compare 4 Clear Enable */

/*----------------------------------------------------------------------------*/
#define TIM_CCMR2_IC3PSC_Pos      (2U)
#define TIM_CCMR2_IC3PSC_Msk      (0x3UL << TIM_CCMR2_IC3PSC_Pos)              /*!< 0x0000000C */
#define TIM_CCMR2_IC3PSC          TIM_CCMR2_IC3PSC_Msk                         /*!<IC3PSC[1:0] bits (Input Capture 3 Prescaler) */
#define TIM_CCMR2_IC3PSC_0        (0x1UL << TIM_CCMR2_IC3PSC_Pos)              /*!< 0x00000004 */
#define TIM_CCMR2_IC3PSC_1        (0x2UL << TIM_CCMR2_IC3PSC_Pos)              /*!< 0x00000008 */

#define TIM_CCMR2_IC3F_Pos        (4U)
#define TIM_CCMR2_IC3F_Msk        (0xFUL << TIM_CCMR2_IC3F_Pos)                /*!< 0x000000F0 */
#define TIM_CCMR2_IC3F            TIM_CCMR2_IC3F_Msk                           /*!<IC3F[3:0] bits (Input Capture 3 Filter) */
#define TIM_CCMR2_IC3F_0          (0x1UL << TIM_CCMR2_IC3F_Pos)                /*!< 0x00000010 */
#define TIM_CCMR2_IC3F_1          (0x2UL << TIM_CCMR2_IC3F_Pos)                /*!< 0x00000020 */
#define TIM_CCMR2_IC3F_2          (0x4UL << TIM_CCMR2_IC3F_Pos)                /*!< 0x00000040 */
#define TIM_CCMR2_IC3F_3          (0x8UL << TIM_CCMR2_IC3F_Pos)                /*!< 0x00000080 */

#define TIM_CCMR2_IC4PSC_Pos      (10U)
#define TIM_CCMR2_IC4PSC_Msk      (0x3UL << TIM_CCMR2_IC4PSC_Pos)              /*!< 0x00000C00 */
#define TIM_CCMR2_IC4PSC          TIM_CCMR2_IC4PSC_Msk                         /*!<IC4PSC[1:0] bits (Input Capture 4 Prescaler) */
#define TIM_CCMR2_IC4PSC_0        (0x1UL << TIM_CCMR2_IC4PSC_Pos)              /*!< 0x00000400 */
#define TIM_CCMR2_IC4PSC_1        (0x2UL << TIM_CCMR2_IC4PSC_Pos)              /*!< 0x00000800 */

#define TIM_CCMR2_IC4F_Pos        (12U)
#define TIM_CCMR2_IC4F_Msk        (0xFUL << TIM_CCMR2_IC4F_Pos)                /*!< 0x0000F000 */
#define TIM_CCMR2_IC4F            TIM_CCMR2_IC4F_Msk                           /*!<IC4F[3:0] bits (Input Capture 4 Filter) */
#define TIM_CCMR2_IC4F_0          (0x1UL << TIM_CCMR2_IC4F_Pos)                /*!< 0x00001000 */
#define TIM_CCMR2_IC4F_1          (0x2UL << TIM_CCMR2_IC4F_Pos)                /*!< 0x00002000 */
#define TIM_CCMR2_IC4F_2          (0x4UL << TIM_CCMR2_IC4F_Pos)                /*!< 0x00004000 */
#define TIM_CCMR2_IC4F_3          (0x8UL << TIM_CCMR2_IC4F_Pos)                /*!< 0x00008000 */

/******************  Bit definition for TIM_CCMR3 register  *******************/
#define TIM_CCMR3_OC5FE_Pos       (2U)
#define TIM_CCMR3_OC5FE_Msk       (0x1UL << TIM_CCMR3_OC5FE_Pos)               /*!< 0x00000004 */
#define TIM_CCMR3_OC5FE           TIM_CCMR3_OC5FE_Msk                          /*!<Output Compare 5 Fast enable */
#define TIM_CCMR3_OC5PE_Pos       (3U)
#define TIM_CCMR3_OC5PE_Msk       (0x1UL << TIM_CCMR3_OC5PE_Pos)               /*!< 0x00000008 */
#define TIM_CCMR3_OC5PE           TIM_CCMR3_OC5PE_Msk                          /*!<Output Compare 5 Preload enable */

#define TIM_CCMR3_OC5M_Pos        (4U)
#define TIM_CCMR3_OC5M_Msk        (0x1007UL << TIM_CCMR3_OC5M_Pos)             /*!< 0x00010070 */
#define TIM_CCMR3_OC5M            TIM_CCMR3_OC5M_Msk                           /*!<OC5M[3:0] bits (Output Compare 5 Mode) */
#define TIM_CCMR3_OC5M_0          (0x0001UL << TIM_CCMR3_OC5M_Pos)             /*!< 0x00000010 */
#define TIM_CCMR3_OC5M_1          (0x0002UL << TIM_CCMR3_OC5M_Pos)             /*!< 0x00000020 */
#define TIM_CCMR3_OC5M_2          (0x0004UL << TIM_CCMR3_OC5M_Pos)             /*!< 0x00000040 */
#define TIM_CCMR3_OC5M_3          (0x1000UL << TIM_CCMR3_OC5M_Pos)             /*!< 0x00010000 */

#define TIM_CCMR3_OC5CE_Pos       (7U)
#define TIM_CCMR3_OC5CE_Msk       (0x1UL << TIM_CCMR3_OC5CE_Pos)               /*!< 0x00000080 */
#define TIM_CCMR3_OC5CE           TIM_CCMR3_OC5CE_Msk                          /*!<Output Compare 5 Clear Enable */

#define TIM_CCMR3_OC6FE_Pos       (10U)
#define TIM_CCMR3_OC6FE_Msk       (0x1UL << TIM_CCMR3_OC6FE_Pos)               /*!< 0x00000400 */
#define TIM_CCMR3_OC6FE           TIM_CCMR3_OC6FE_Msk                          /*!<Output Compare 6 Fast enable */
#define TIM_CCMR3_OC6PE_Pos       (11U)
#define TIM_CCMR3_OC6PE_Msk       (0x1UL << TIM_CCMR3_OC6PE_Pos)               /*!< 0x00000800 */
#define TIM_CCMR3_OC6PE           TIM_CCMR3_OC6PE_Msk                          /*!<Output Compare 6 Preload enable */

#define TIM_CCMR3_OC6M_Pos        (12U)
#define TIM_CCMR3_OC6M_Msk        (0x1007UL << TIM_CCMR3_OC6M_Pos)             /*!< 0x01007000 */
#define TIM_CCMR3_OC6M            TIM_CCMR3_OC6M_Msk                           /*!<OC6M[3:0] bits (Output Compare 6 Mode) */
#define TIM_CCMR3_OC6M_0          (0x0001UL << TIM_CCMR3_OC6M_Pos)             /*!< 0x00001000 */
#define TIM_CCMR3_OC6M_1          (0x0002UL << TIM_CCMR3_OC6M_Pos)             /*!< 0x00002000 */
#define TIM_CCMR3_OC6M_2          (0x0004UL << TIM_CCMR3_OC6M_Pos)             /*!< 0x00004000 */
#define TIM_CCMR3_OC6M_3          (0x1000UL << TIM_CCMR3_OC6M_Pos)             /*!< 0x01000000 */

#define TIM_CCMR3_OC6CE_Pos       (15U)
#define TIM_CCMR3_OC6CE_Msk       (0x1UL << TIM_CCMR3_OC6CE_Pos)               /*!< 0x00008000 */
#define TIM_CCMR3_OC6CE           TIM_CCMR3_OC6CE_Msk                          /*!<Output Compare 6 Clear Enable */

/*******************  Bit definition for TIM_CCER register  *******************/
#define TIM_CCER_CC1E_Pos         (0U)
#define TIM_CCER_CC1E_Msk         (0x1UL << TIM_CCER_CC1E_Pos)                 /*!< 0x00000001 */
#define TIM_CCER_CC1E             TIM_CCER_CC1E_Msk                            /*!<Capture/Compare 1 output enable */
#define TIM_CCER_CC1P_Pos         (1U)
#define TIM_CCER_CC1P_Msk         (0x1UL << TIM_CCER_CC1P_Pos)                 /*!< 0x00000002 */
#define TIM_CCER_CC1P             TIM_CCER_CC1P_Msk                            /*!<Capture/Compare 1 output Polarity */
#define TIM_CCER_CC1NE_Pos        (2U)
#define TIM_CCER_CC1NE_Msk        (0x1UL << TIM_CCER_CC1NE_Pos)                /*!< 0x00000004 */
#define TIM_CCER_CC1NE            TIM_CCER_CC1NE_Msk                           /*!<Capture/Compare 1 Complementary output enable */
#define TIM_CCER_CC1NP_Pos        (3U)
#define TIM_CCER_CC1NP_Msk        (0x1UL << TIM_CCER_CC1NP_Pos)                /*!< 0x00000008 */
#define TIM_CCER_CC1NP            TIM_CCER_CC1NP_Msk                           /*!<Capture/Compare 1 Complementary output Polarity */
#define TIM_CCER_CC2E_Pos         (4U)
#define TIM_CCER_CC2E_Msk         (0x1UL << TIM_CCER_CC2E_Pos)                 /*!< 0x00000010 */
#define TIM_CCER_CC2E             TIM_CCER_CC2E_Msk                            /*!<Capture/Compare 2 output enable */
#define TIM_CCER_CC2P_Pos         (5U)
#define TIM_CCER_CC2P_Msk         (0x1UL << TIM_CCER_CC2P_Pos)                 /*!< 0x00000020 */
#define TIM_CCER_CC2P             TIM_CCER_CC2P_Msk                            /*!<Capture/Compare 2 output Polarity */
#define TIM_CCER_CC2NE_Pos        (6U)
#define TIM_CCER_CC2NE_Msk        (0x1UL << TIM_CCER_CC2NE_Pos)                /*!< 0x00000040 */
#define TIM_CCER_CC2NE            TIM_CCER_CC2NE_Msk                           /*!<Capture/Compare 2 Complementary output enable */
#define TIM_CCER_CC2NP_Pos        (7U)
#define TIM_CCER_CC2NP_Msk        (0x1UL << TIM_CCER_CC2NP_Pos)                /*!< 0x00000080 */
#define TIM_CCER_CC2NP            TIM_CCER_CC2NP_Msk                           /*!<Capture/Compare 2 Complementary output Polarity */
#define TIM_CCER_CC3E_Pos         (8U)
#define TIM_CCER_CC3E_Msk         (0x1UL << TIM_CCER_CC3E_Pos)                 /*!< 0x00000100 */
#define TIM_CCER_CC3E             TIM_CCER_CC3E_Msk                            /*!<Capture/Compare 3 output enable */
#define TIM_CCER_CC3P_Pos         (9U)
#define TIM_CCER_CC3P_Msk         (0x1UL << TIM_CCER_CC3P_Pos)                 /*!< 0x00000200 */
#define TIM_CCER_CC3P             TIM_CCER_CC3P_Msk                            /*!<Capture/Compare 3 output Polarity */
#define TIM_CCER_CC3NE_Pos        (10U)
#define TIM_CCER_CC3NE_Msk        (0x1UL << TIM_CCER_CC3NE_Pos)                /*!< 0x00000400 */
#define TIM_CCER_CC3NE            TIM_CCER_CC3NE_Msk                           /*!<Capture/Compare 3 Complementary output enable */
#define TIM_CCER_CC3NP_Pos        (11U)
#define TIM_CCER_CC3NP_Msk        (0x1UL << TIM_CCER_CC3NP_Pos)                /*!< 0x00000800 */
#define TIM_CCER_CC3NP            TIM_CCER_CC3NP_Msk                           /*!<Capture/Compare 3 Complementary output Polarity */
#define TIM_CCER_CC4E_Pos         (12U)
#define TIM_CCER_CC4E_Msk         (0x1UL << TIM_CCER_CC4E_Pos)                 /*!< 0x00001000 */
#define TIM_CCER_CC4E             TIM_CCER_CC4E_Msk                            /*!<Capture/Compare 4 output enable */
#define TIM_CCER_CC4P_Pos         (13U)
#define TIM_CCER_CC4P_Msk         (0x1UL << TIM_CCER_CC4P_Pos)                 /*!< 0x00002000 */
#define TIM_CCER_CC4P             TIM_CCER_CC4P_Msk                            /*!<Capture/Compare 4 output Polarity */
#define TIM_CCER_CC5E_Pos         (16U)
#define TIM_CCER_CC5E_Msk         (0x1UL << TIM_CCER_CC5E_Pos)                 /*!< 0x00010000 */
#define TIM_CCER_CC5E             TIM_CCER_CC5E_Msk                            /*!<Capture/Compare 5 output enable */
#define TIM_CCER_CC5P_Pos         (17U)
#define TIM_CCER_CC5P_Msk         (0x1UL << TIM_CCER_CC5P_Pos)                 /*!< 0x00020000 */
#define TIM_CCER_CC5P             TIM_CCER_CC5P_Msk                            /*!<Capture/Compare 5 output Polarity */
#define TIM_CCER_CC6E_Pos         (20U)
#define TIM_CCER_CC6E_Msk         (0x1UL << TIM_CCER_CC6E_Pos)                 /*!< 0x00100000 */
#define TIM_CCER_CC6E             TIM_CCER_CC6E_Msk                            /*!<Capture/Compare 6 output enable */
#define TIM_CCER_CC6P_Pos         (21U)
#define TIM_CCER_CC6P_Msk         (0x1UL << TIM_CCER_CC6P_Pos)                 /*!< 0x00200000 */
#define TIM_CCER_CC6P             TIM_CCER_CC6P_Msk                            /*!<Capture/Compare 6 output Polarity */

/*******************  Bit definition for TIM_CNT register  ********************/
#define TIM_CNT_CNT_Pos           (0U)
#define TIM_CNT_CNT_Msk           (0xFFFFUL << TIM_CNT_CNT_Pos)            /*!< 0xFFFFFFFF */
#define TIM_CNT_CNT               TIM_CNT_CNT_Msk                              /*!<Counter Value */
#define TIM_CNT_UIFCPY_Pos        (31U)
#define TIM_CNT_UIFCPY_Msk        (0x1UL << TIM_CNT_UIFCPY_Pos)                /*!< 0x80000000 */
#define TIM_CNT_UIFCPY            TIM_CNT_UIFCPY_Msk                           /*!<Update interrupt flag copy (if UIFREMAP=1) */

/*******************  Bit definition for TIM_PSC register  ********************/
#define TIM_PSC_PSC_Pos           (0U)
#define TIM_PSC_PSC_Msk           (0xFFFFUL << TIM_PSC_PSC_Pos)                /*!< 0x0000FFFF */
#define TIM_PSC_PSC               TIM_PSC_PSC_Msk                              /*!<Prescaler Value */

/*******************  Bit definition for TIM_ARR register  ********************/
#define TIM_ARR_ARR_Pos           (0U)
#define TIM_ARR_ARR_Msk           (0xFFFFFUL << TIM_ARR_ARR_Pos)            /*!< 0xFFFFFFFF */
#define TIM_ARR_ARR               TIM_ARR_ARR_Msk                              /*!<Actual auto-reload Value */

/*******************  Bit definition for TIM_RCR register  ********************/
#define TIM_RCR_REP_Pos           (0U)
#define TIM_RCR_REP_Msk           (0xFFFFUL << TIM_RCR_REP_Pos)                /*!< 0x0000FFFF */
#define TIM_RCR_REP               TIM_RCR_REP_Msk                              /*!<Repetition Counter Value */

/*******************  Bit definition for TIM_CCR1 register  *******************/
#define TIM_CCR1_CCR1_Pos         (0U)
#define TIM_CCR1_CCR1_Msk         (0xFFFFFUL << TIM_CCR1_CCR1_Pos)              /*!< 0x0000FFFF */
#define TIM_CCR1_CCR1             TIM_CCR1_CCR1_Msk                            /*!<Capture/Compare 1 Value */

/*******************  Bit definition for TIM_CCR2 register  *******************/
#define TIM_CCR2_CCR2_Pos         (0U)
#define TIM_CCR2_CCR2_Msk         (0xFFFFFUL << TIM_CCR2_CCR2_Pos)              /*!< 0x0000FFFF */
#define TIM_CCR2_CCR2             TIM_CCR2_CCR2_Msk                            /*!<Capture/Compare 2 Value */

/*******************  Bit definition for TIM_CCR3 register  *******************/
#define TIM_CCR3_CCR3_Pos         (0U)
#define TIM_CCR3_CCR3_Msk         (0xFFFFFUL << TIM_CCR3_CCR3_Pos)              /*!< 0x0000FFFF */
#define TIM_CCR3_CCR3             TIM_CCR3_CCR3_Msk                            /*!<Capture/Compare 3 Value */

/*******************  Bit definition for TIM_CCR4 register  *******************/
#define TIM_CCR4_CCR4_Pos         (0U)
#define TIM_CCR4_CCR4_Msk         (0xFFFFFUL << TIM_CCR4_CCR4_Pos)              /*!< 0x0000FFFF */
#define TIM_CCR4_CCR4             TIM_CCR4_CCR4_Msk                            /*!<Capture/Compare 4 Value */

/*******************  Bit definition for TIM_CCR5 register  *******************/
#define TIM_CCR5_CCR5_Pos         (0U)
#define TIM_CCR5_CCR5_Msk         (0xFFFFFUL << TIM_CCR5_CCR5_Pos)          /*!< 0xFFFFFFFF */
#define TIM_CCR5_CCR5             TIM_CCR5_CCR5_Msk                            /*!<Capture/Compare 5 Value */
#define TIM_CCR5_GC5C1_Pos        (29U)
#define TIM_CCR5_GC5C1_Msk        (0x1UL << TIM_CCR5_GC5C1_Pos)                /*!< 0x20000000 */
#define TIM_CCR5_GC5C1            TIM_CCR5_GC5C1_Msk                           /*!<Group Channel 5 and Channel 1 */
#define TIM_CCR5_GC5C2_Pos        (30U)
#define TIM_CCR5_GC5C2_Msk        (0x1UL << TIM_CCR5_GC5C2_Pos)                /*!< 0x40000000 */
#define TIM_CCR5_GC5C2            TIM_CCR5_GC5C2_Msk                           /*!<Group Channel 5 and Channel 2 */
#define TIM_CCR5_GC5C3_Pos        (31U)
#define TIM_CCR5_GC5C3_Msk        (0x1UL << TIM_CCR5_GC5C3_Pos)                /*!< 0x80000000 */
#define TIM_CCR5_GC5C3            TIM_CCR5_GC5C3_Msk                           /*!<Group Channel 5 and Channel 3 */

/*******************  Bit definition for TIM_CCR6 register  *******************/
#define TIM_CCR6_CCR6_Pos         (0U)
#define TIM_CCR6_CCR6_Msk         (0xFFFFFUL << TIM_CCR6_CCR6_Pos)              /*!< 0x0000FFFF */
#define TIM_CCR6_CCR6             TIM_CCR6_CCR6_Msk                            /*!<Capture/Compare 6 Value */

/*******************  Bit definition for TIM_BDTR register  *******************/
#define TIM_BDTR_DTG_Pos          (0U)
#define TIM_BDTR_DTG_Msk          (0xFFUL << TIM_BDTR_DTG_Pos)                 /*!< 0x000000FF */
#define TIM_BDTR_DTG              TIM_BDTR_DTG_Msk                             /*!<DTG[0:7] bits (Dead-Time Generator set-up) */
#define TIM_BDTR_DTG_0            (0x01UL << TIM_BDTR_DTG_Pos)                 /*!< 0x00000001 */
#define TIM_BDTR_DTG_1            (0x02UL << TIM_BDTR_DTG_Pos)                 /*!< 0x00000002 */
#define TIM_BDTR_DTG_2            (0x04UL << TIM_BDTR_DTG_Pos)                 /*!< 0x00000004 */
#define TIM_BDTR_DTG_3            (0x08UL << TIM_BDTR_DTG_Pos)                 /*!< 0x00000008 */
#define TIM_BDTR_DTG_4            (0x10UL << TIM_BDTR_DTG_Pos)                 /*!< 0x00000010 */
#define TIM_BDTR_DTG_5            (0x20UL << TIM_BDTR_DTG_Pos)                 /*!< 0x00000020 */
#define TIM_BDTR_DTG_6            (0x40UL << TIM_BDTR_DTG_Pos)                 /*!< 0x00000040 */
#define TIM_BDTR_DTG_7            (0x80UL << TIM_BDTR_DTG_Pos)                 /*!< 0x00000080 */

#define TIM_BDTR_LOCK_Pos         (8U)
#define TIM_BDTR_LOCK_Msk         (0x3UL << TIM_BDTR_LOCK_Pos)                 /*!< 0x00000300 */
#define TIM_BDTR_LOCK             TIM_BDTR_LOCK_Msk                            /*!<LOCK[1:0] bits (Lock Configuration) */
#define TIM_BDTR_LOCK_0           (0x1UL << TIM_BDTR_LOCK_Pos)                 /*!< 0x00000100 */
#define TIM_BDTR_LOCK_1           (0x2UL << TIM_BDTR_LOCK_Pos)                 /*!< 0x00000200 */

#define TIM_BDTR_OSSI_Pos         (10U)
#define TIM_BDTR_OSSI_Msk         (0x1UL << TIM_BDTR_OSSI_Pos)                 /*!< 0x00000400 */
#define TIM_BDTR_OSSI             TIM_BDTR_OSSI_Msk                            /*!<Off-State Selection for Idle mode */
#define TIM_BDTR_OSSR_Pos         (11U)
#define TIM_BDTR_OSSR_Msk         (0x1UL << TIM_BDTR_OSSR_Pos)                 /*!< 0x00000800 */
#define TIM_BDTR_OSSR             TIM_BDTR_OSSR_Msk                            /*!<Off-State Selection for Run mode */
#define TIM_BDTR_BKE_Pos          (12U)
#define TIM_BDTR_BKE_Msk          (0x1UL << TIM_BDTR_BKE_Pos)                  /*!< 0x00001000 */
#define TIM_BDTR_BKE              TIM_BDTR_BKE_Msk                             /*!<Break enable for Break 1 */
#define TIM_BDTR_BKP_Pos          (13U)
#define TIM_BDTR_BKP_Msk          (0x1UL << TIM_BDTR_BKP_Pos)                  /*!< 0x00002000 */
#define TIM_BDTR_BKP              TIM_BDTR_BKP_Msk                             /*!<Break Polarity for Break 1 */
#define TIM_BDTR_AOE_Pos          (14U)
#define TIM_BDTR_AOE_Msk          (0x1UL << TIM_BDTR_AOE_Pos)                  /*!< 0x00004000 */
#define TIM_BDTR_AOE              TIM_BDTR_AOE_Msk                             /*!<Automatic Output enable */
#define TIM_BDTR_MOE_Pos          (15U)
#define TIM_BDTR_MOE_Msk          (0x1UL << TIM_BDTR_MOE_Pos)                  /*!< 0x00008000 */
#define TIM_BDTR_MOE              TIM_BDTR_MOE_Msk                             /*!<Main Output enable */

#define TIM_BDTR_BKF_Pos          (16U)
#define TIM_BDTR_BKF_Msk          (0xFUL << TIM_BDTR_BKF_Pos)                  /*!< 0x000F0000 */
#define TIM_BDTR_BKF              TIM_BDTR_BKF_Msk                             /*!<Break Filter for Break 1 */
#define TIM_BDTR_BK2F_Pos         (20U)
#define TIM_BDTR_BK2F_Msk         (0xFUL << TIM_BDTR_BK2F_Pos)                 /*!< 0x00F00000 */
#define TIM_BDTR_BK2F             TIM_BDTR_BK2F_Msk                            /*!<Break Filter for Break 2 */

#define TIM_BDTR_BK2E_Pos         (24U)
#define TIM_BDTR_BK2E_Msk         (0x1UL << TIM_BDTR_BK2E_Pos)                 /*!< 0x01000000 */
#define TIM_BDTR_BK2E             TIM_BDTR_BK2E_Msk                            /*!<Break enable for Break 2 */
#define TIM_BDTR_BK2P_Pos         (25U)
#define TIM_BDTR_BK2P_Msk         (0x1UL << TIM_BDTR_BK2P_Pos)                 /*!< 0x02000000 */
#define TIM_BDTR_BK2P             TIM_BDTR_BK2P_Msk                            /*!<Break Polarity for Break 2 */

#define TIM_BDTR_BKDSRM_Pos       (26U)
#define TIM_BDTR_BKDSRM_Msk       (0x1UL << TIM_BDTR_BKDSRM_Pos)               /*!< 0x04000000 */
#define TIM_BDTR_BKDSRM           TIM_BDTR_BKDSRM_Msk                          /*!<Break disarming/re-arming */
#define TIM_BDTR_BK2DSRM_Pos      (27U)
#define TIM_BDTR_BK2DSRM_Msk      (0x1UL << TIM_BDTR_BK2DSRM_Pos)              /*!< 0x08000000 */
#define TIM_BDTR_BK2DSRM          TIM_BDTR_BK2DSRM_Msk                         /*!<Break2 disarming/re-arming */

#define TIM_BDTR_BKBID_Pos        (28U)
#define TIM_BDTR_BKBID_Msk        (0x1UL << TIM_BDTR_BKBID_Pos)                /*!< 0x10000000 */
#define TIM_BDTR_BKBID            TIM_BDTR_BKBID_Msk                           /*!<Break BIDirectional */
#define TIM_BDTR_BK2BID_Pos       (29U)
#define TIM_BDTR_BK2BID_Msk       (0x1UL << TIM_BDTR_BK2BID_Pos)               /*!< 0x20000000 */
#define TIM_BDTR_BK2BID           TIM_BDTR_BK2BID_Msk                          /*!<Break2 BIDirectional */

/*******************  Bit definition for TIM_AF1 register  *******************/
#define TIM_AF1_BKINE_Pos        (0U)
#define TIM_AF1_BKINE_Msk        (0x1UL << TIM_AF1_BKINE_Pos)                /*!< 0x00000001 */
#define TIM_AF1_BKINE            TIM_AF1_BKINE_Msk                           /*!<BRK BKIN input enable */
#define TIM_AF1_BKCMP1E_Pos      (1U)
#define TIM_AF1_BKCMP1E_Msk      (0x1UL << TIM_AF1_BKCMP1E_Pos)              /*!< 0x00000002 */
#define TIM_AF1_BKCMP1E          TIM_AF1_BKCMP1E_Msk                         /*!<BRK COMP1 enable */
#define TIM_AF1_BKCMP2E_Pos      (2U)
#define TIM_AF1_BKCMP2E_Msk      (0x1UL << TIM_AF1_BKCMP2E_Pos)              /*!< 0x00000004 */
#define TIM_AF1_BKCMP2E          TIM_AF1_BKCMP2E_Msk                         /*!<BRK COMP2 enable */
#define TIM_AF1_BKINP_Pos        (9U)
#define TIM_AF1_BKINP_Msk        (0x1UL << TIM_AF1_BKINP_Pos)                /*!< 0x00000200 */
#define TIM_AF1_BKINP            TIM_AF1_BKINP_Msk                           /*!<BRK BKIN input polarity */
#define TIM_AF1_BKCMP1P_Pos      (10U)
#define TIM_AF1_BKCMP1P_Msk      (0x1UL << TIM_AF1_BKCMP1P_Pos)              /*!< 0x00000400 */
#define TIM_AF1_BKCMP1P          TIM_AF1_BKCMP1P_Msk                         /*!<BRK COMP1 input polarity */
#define TIM_AF1_BKCMP2P_Pos      (11U)
#define TIM_AF1_BKCMP2P_Msk      (0x1UL << TIM_AF1_BKCMP2P_Pos)              /*!< 0x00000800 */
#define TIM_AF1_BKCMP2P          TIM_AF1_BKCMP2P_Msk                         /*!<BRK COMP2 input polarity */
#define TIM_AF1_ETRSEL_Pos       (14U)
#define TIM_AF1_ETRSEL_Msk       (0xFUL << TIM_AF1_ETRSEL_Pos)               /*!< 0x0003C000 */
#define TIM_AF1_ETRSEL           TIM_AF1_ETRSEL_Msk                          /*!<ETRSEL[3:0] bits (TIM ETR source selection) */
#define TIM_AF1_ETRSEL_0         (0x1UL << TIM_AF1_ETRSEL_Pos)               /*!< 0x00004000 */
#define TIM_AF1_ETRSEL_1         (0x2UL << TIM_AF1_ETRSEL_Pos)               /*!< 0x00008000 */
#define TIM_AF1_ETRSEL_2         (0x4UL << TIM_AF1_ETRSEL_Pos)               /*!< 0x00010000 */
#define TIM_AF1_ETRSEL_3         (0x8UL << TIM_AF1_ETRSEL_Pos)               /*!< 0x00020000 */

/*******************  Bit definition for TIM_AF2 register  *********************/
#define TIM_AF2_BK2INE_Pos        (0U)
#define TIM_AF2_BK2INE_Msk        (0x1UL << TIM_AF2_BK2INE_Pos)                /*!< 0x00000001 */
#define TIM_AF2_BK2INE            TIM_AF2_BK2INE_Msk                           /*!<BRK2 BKIN input enable */
#define TIM_AF2_BK2CMP1E_Pos      (1U)
#define TIM_AF2_BK2CMP1E_Msk      (0x1UL << TIM_AF2_BK2CMP1E_Pos)              /*!< 0x00000002 */
#define TIM_AF2_BK2CMP1E          TIM_AF2_BK2CMP1E_Msk                         /*!<BRK2 COMP1 enable */
#define TIM_AF2_BK2CMP2E_Pos      (2U)
#define TIM_AF2_BK2CMP2E_Msk      (0x1UL << TIM_AF2_BK2CMP2E_Pos)              /*!< 0x00000004 */
#define TIM_AF2_BK2CMP2E          TIM_AF2_BK2CMP2E_Msk                         /*!<BRK2 COMP2 enable */
#define TIM_AF2_BK2INP_Pos        (9U)
#define TIM_AF2_BK2INP_Msk        (0x1UL << TIM_AF2_BK2INP_Pos)                /*!< 0x00000200 */
#define TIM_AF2_BK2INP            TIM_AF2_BK2INP_Msk                           /*!<BRK2 BKIN input polarity */
#define TIM_AF2_BK2CMP1P_Pos      (10U)
#define TIM_AF2_BK2CMP1P_Msk      (0x1UL << TIM_AF2_BK2CMP1P_Pos)              /*!< 0x00000400 */
#define TIM_AF2_BK2CMP1P          TIM_AF2_BK2CMP1P_Msk                         /*!<BRK2 COMP1 input polarity */
#define TIM_AF2_BK2CMP2P_Pos      (11U)
#define TIM_AF2_BK2CMP2P_Msk      (0x1UL << TIM_AF2_BK2CMP2P_Pos)              /*!< 0x00000800 */
#define TIM_AF2_BK2CMP2P          TIM_AF2_BK2CMP2P_Msk                         /*!<BRK2 COMP2 input polarity */
#define TIM_AF2_OCRSEL_Pos        (16U)
#define TIM_AF2_OCRSEL_Msk        (0x7UL << TIM_AF2_OCRSEL_Pos)                /*!< 0x00070000 */
#define TIM_AF2_OCRSEL            TIM_AF2_OCRSEL_Msk                           /*!<BRK2 COMP2 input polarity */
#define TIM_AF2_OCRSEL_0         (0x1UL << TIM_AF2_OCRSEL_Pos)                 /*!< 0x00010000 */
#define TIM_AF2_OCRSEL_1         (0x2UL << TIM_AF2_OCRSEL_Pos)                 /*!< 0x00020000 */
#define TIM_AF2_OCRSEL_2         (0x4UL << TIM_AF2_OCRSEL_Pos)                 /*!< 0x00040000 */


/*******************  Bit definition for TIM_TISEL register  *********************/
#define TIM_TISEL_TI1SEL_Pos      (0U)
#define TIM_TISEL_TI1SEL_Msk      (0xFUL << TIM_TISEL_TI1SEL_Pos)              /*!< 0x0000000F */
#define TIM_TISEL_TI1SEL          TIM_TISEL_TI1SEL_Msk                         /*!<TI1SEL[3:0] bits (TIM TI1 SEL)*/
#define TIM_TISEL_TI1SEL_0        (0x1UL << TIM_TISEL_TI1SEL_Pos)              /*!< 0x00000001 */
#define TIM_TISEL_TI1SEL_1        (0x2UL << TIM_TISEL_TI1SEL_Pos)              /*!< 0x00000002 */
#define TIM_TISEL_TI1SEL_2        (0x4UL << TIM_TISEL_TI1SEL_Pos)              /*!< 0x00000004 */
#define TIM_TISEL_TI1SEL_3        (0x8UL << TIM_TISEL_TI1SEL_Pos)              /*!< 0x00000008 */

#define TIM_TISEL_TI2SEL_Pos      (8U)
#define TIM_TISEL_TI2SEL_Msk      (0xFUL << TIM_TISEL_TI2SEL_Pos)              /*!< 0x00000F00 */
#define TIM_TISEL_TI2SEL          TIM_TISEL_TI2SEL_Msk                         /*!<TI2SEL[3:0] bits (TIM TI2 SEL)*/
#define TIM_TISEL_TI2SEL_0        (0x1UL << TIM_TISEL_TI2SEL_Pos)              /*!< 0x00000100 */
#define TIM_TISEL_TI2SEL_1        (0x2UL << TIM_TISEL_TI2SEL_Pos)              /*!< 0x00000200 */
#define TIM_TISEL_TI2SEL_2        (0x4UL << TIM_TISEL_TI2SEL_Pos)              /*!< 0x00000400 */
#define TIM_TISEL_TI2SEL_3        (0x8UL << TIM_TISEL_TI2SEL_Pos)              /*!< 0x00000800 */

#define TIM_TISEL_TI3SEL_Pos      (16U)
#define TIM_TISEL_TI3SEL_Msk      (0xFUL << TIM_TISEL_TI3SEL_Pos)              /*!< 0x000F0000 */
#define TIM_TISEL_TI3SEL          TIM_TISEL_TI3SEL_Msk                         /*!<TI3SEL[3:0] bits (TIM TI3 SEL)*/
#define TIM_TISEL_TI3SEL_0        (0x1UL << TIM_TISEL_TI3SEL_Pos)              /*!< 0x00010000 */
#define TIM_TISEL_TI3SEL_1        (0x2UL << TIM_TISEL_TI3SEL_Pos)              /*!< 0x00020000 */
#define TIM_TISEL_TI3SEL_2        (0x4UL << TIM_TISEL_TI3SEL_Pos)              /*!< 0x00040000 */
#define TIM_TISEL_TI3SEL_3        (0x8UL << TIM_TISEL_TI3SEL_Pos)              /*!< 0x00080000 */

#define TIM_TISEL_TI4SEL_Pos      (24U)
#define TIM_TISEL_TI4SEL_Msk      (0xFUL << TIM_TISEL_TI4SEL_Pos)              /*!< 0x0F000000 */
#define TIM_TISEL_TI4SEL          TIM_TISEL_TI4SEL_Msk                         /*!<TI4SEL[3:0] bits (TIM TI4 SEL)*/
#define TIM_TISEL_TI4SEL_0        (0x1UL << TIM_TISEL_TI4SEL_Pos)              /*!< 0x01000000 */
#define TIM_TISEL_TI4SEL_1        (0x2UL << TIM_TISEL_TI4SEL_Pos)              /*!< 0x02000000 */
#define TIM_TISEL_TI4SEL_2        (0x4UL << TIM_TISEL_TI4SEL_Pos)              /*!< 0x04000000 */
#define TIM_TISEL_TI4SEL_3        (0x8UL << TIM_TISEL_TI4SEL_Pos)              /*!< 0x08000000 */

/*******************  Bit definition for TIM_DTR2 register  *********************/
#define TIM_DTR2_DTGF_Pos      (0U)
#define TIM_DTR2_DTGF_Msk      (0xFFUL << TIM_DTR2_DTGF_Pos)                /*!< 0x0000000F */
#define TIM_DTR2_DTGF          TIM_DTR2_DTGF_Msk                            /*!<DTGF[7:0] bits (Deadtime falling edge generator setup)*/
#define TIM_DTR2_DTGF_0        (0x01UL << TIM_DTR2_DTGF_Pos)                /*!< 0x00000001 */
#define TIM_DTR2_DTGF_1        (0x02UL << TIM_DTR2_DTGF_Pos)                /*!< 0x00000002 */
#define TIM_DTR2_DTGF_2        (0x04UL << TIM_DTR2_DTGF_Pos)                /*!< 0x00000004 */
#define TIM_DTR2_DTGF_3        (0x08UL << TIM_DTR2_DTGF_Pos)                /*!< 0x00000008 */
#define TIM_DTR2_DTGF_4        (0x10UL << TIM_DTR2_DTGF_Pos)                /*!< 0x00000010 */
#define TIM_DTR2_DTGF_5        (0x20UL << TIM_DTR2_DTGF_Pos)                /*!< 0x00000020 */
#define TIM_DTR2_DTGF_6        (0x40UL << TIM_DTR2_DTGF_Pos)                /*!< 0x00000040 */
#define TIM_DTR2_DTGF_7        (0x80UL << TIM_DTR2_DTGF_Pos)                /*!< 0x00000080 */

#define TIM_DTR2_DTAE_Pos      (16U)
#define TIM_DTR2_DTAE_Msk      (0x1UL << TIM_DTR2_DTAE_Pos)                 /*!< 0x00004000 */
#define TIM_DTR2_DTAE          TIM_DTR2_DTAE_Msk                            /*!<Deadtime asymmetric enable */
#define TIM_DTR2_DTPE_Pos      (17U)
#define TIM_DTR2_DTPE_Msk      (0x1UL << TIM_DTR2_DTPE_Pos)                 /*!< 0x00008000 */
#define TIM_DTR2_DTPE          TIM_DTR2_DTPE_Msk                            /*!<Deadtime prelaod enable */

/*******************  Bit definition for TIM_ECR register  *********************/
#define TIM_ECR_IE_Pos       (0U)
#define TIM_ECR_IE_Msk       (0x1UL << TIM_ECR_IE_Pos)                   /*!< 0x00000001 */
#define TIM_ECR_IE           TIM_ECR_IE_Msk                              /*!<Index enable */

#define TIM_ECR_IDIR_Pos      (1U)
#define TIM_ECR_IDIR_Msk      (0x3UL << TIM_ECR_IDIR_Pos)                 /*!< 0x00000006 */
#define TIM_ECR_IDIR          TIM_ECR_IDIR_Msk                            /*!<IDIR[1:0] bits (Index direction)*/
#define TIM_ECR_IDIR_0        (0x01UL << TIM_ECR_IDIR_Pos)                /*!< 0x00000001 */
#define TIM_ECR_IDIR_1        (0x02UL << TIM_ECR_IDIR_Pos)                /*!< 0x00000002 */

#define TIM_ECR_FIDX_Pos      (5U)
#define TIM_ECR_FIDX_Msk      (0x1UL << TIM_ECR_FIDX_Pos)                 /*!< 0x00000020 */
#define TIM_ECR_FIDX          TIM_ECR_FIDX_Msk                            /*!<First index enable */

#define TIM_ECR_IPOS_Pos      (6U)
#define TIM_ECR_IPOS_Msk      (0x3UL << TIM_ECR_IPOS_Pos)                 /*!< 0x0000000C0 */
#define TIM_ECR_IPOS          TIM_ECR_IPOS_Msk                            /*!<IPOS[1:0] bits (Index positioning)*/
#define TIM_ECR_IPOS_0        (0x01UL << TIM_ECR_IPOS_Pos)                /*!< 0x00000001 */
#define TIM_ECR_IPOS_1        (0x02UL << TIM_ECR_IPOS_Pos)                /*!< 0x00000002 */

#define TIM_ECR_PW_Pos        (16U)
#define TIM_ECR_PW_Msk        (0xFFUL << TIM_ECR_PW_Pos)                  /*!< 0x00FF0000 */
#define TIM_ECR_PW            TIM_ECR_PW_Msk                              /*!<PW[7:0] bits (Pulse width)*/
#define TIM_ECR_PW_0          (0x01UL << TIM_ECR_PW_Pos)                  /*!< 0x00010000 */
#define TIM_ECR_PW_1          (0x02UL << TIM_ECR_PW_Pos)                  /*!< 0x00020000 */
#define TIM_ECR_PW_2          (0x04UL << TIM_ECR_PW_Pos)                  /*!< 0x00040000 */
#define TIM_ECR_PW_3          (0x08UL << TIM_ECR_PW_Pos)                  /*!< 0x00080000 */
#define TIM_ECR_PW_4          (0x10UL << TIM_ECR_PW_Pos)                  /*!< 0x00100000 */
#define TIM_ECR_PW_5          (0x20UL << TIM_ECR_PW_Pos)                  /*!< 0x00200000 */
#define TIM_ECR_PW_6          (0x40UL << TIM_ECR_PW_Pos)                  /*!< 0x00400000 */
#define TIM_ECR_PW_7          (0x80UL << TIM_ECR_PW_Pos)                  /*!< 0x00800000 */

#define TIM_ECR_PWPRSC_Pos    (24U)
#define TIM_ECR_PWPRSC_Msk    (0x7UL << TIM_ECR_PWPRSC_Pos)               /*!< 0x07000000 */
#define TIM_ECR_PWPRSC        TIM_ECR_PWPRSC_Msk                          /*!<PWPRSC[2:0] bits (Pulse width prescaler)*/
#define TIM_ECR_PWPRSC_0      (0x01UL << TIM_ECR_PWPRSC_Pos)              /*!< 0x01000000 */
#define TIM_ECR_PWPRSC_1      (0x02UL << TIM_ECR_PWPRSC_Pos)              /*!< 0x02000000 */
#define TIM_ECR_PWPRSC_2      (0x04UL << TIM_ECR_PWPRSC_Pos)              /*!< 0x04000000 */



#define IS_TIM_COUNTERMODE(__VALUE__) (((__VALUE__) == TIM_COUNTERMODE_UP) \
                                          || ((__VALUE__) == TIM_COUNTERMODE_DOWN) \
                                          || ((__VALUE__) == TIM_COUNTERMODE_CENTER_UP) \
                                          || ((__VALUE__) == TIM_COUNTERMODE_CENTER_DOWN) \
                                          || ((__VALUE__) == TIM_COUNTERMODE_CENTER_UP_DOWN))

#define IS_TIM_CLOCKDIVISION(__VALUE__) (((__VALUE__) == TIM_CLOCKDIVISION_DIV1) \
                                            || ((__VALUE__) == TIM_CLOCKDIVISION_DIV2) \
                                            || ((__VALUE__) == TIM_CLOCKDIVISION_DIV4))

#define IS_TIM_OCMODE(__VALUE__) (((__VALUE__) == TIM_OCMODE_FROZEN) \
                                     || ((__VALUE__) == TIM_OCMODE_ACTIVE) \
                                     || ((__VALUE__) == TIM_OCMODE_INACTIVE) \
                                     || ((__VALUE__) == TIM_OCMODE_TOGGLE) \
                                     || ((__VALUE__) == TIM_OCMODE_FORCED_INACTIVE) \
                                     || ((__VALUE__) == TIM_OCMODE_FORCED_ACTIVE) \
                                     || ((__VALUE__) == TIM_OCMODE_PWM1) \
                                     || ((__VALUE__) == TIM_OCMODE_PWM2) \
                                     || ((__VALUE__) == TIM_OCMODE_RETRIG_OPM1) \
                                     || ((__VALUE__) == TIM_OCMODE_RETRIG_OPM2) \
                                     || ((__VALUE__) == TIM_OCMODE_COMBINED_PWM1) \
                                     || ((__VALUE__) == TIM_OCMODE_COMBINED_PWM2) \
                                     || ((__VALUE__) == TIM_OCMODE_ASSYMETRIC_PWM1) \
                                     || ((__VALUE__) == TIM_OCMODE_ASSYMETRIC_PWM2) \
                                     || ((__VALUE__) == TIM_OCMODE_PULSE_ON_COMPARE) \
                                     || ((__VALUE__) == TIM_OCMODE_DIRECTION_OUTPUT))

#define IS_TIM_OCSTATE(__VALUE__) (((__VALUE__) == TIM_OCSTATE_DISABLE) \
                                      || ((__VALUE__) == TIM_OCSTATE_ENABLE))

#define IS_TIM_OCPOLARITY(__VALUE__) (((__VALUE__) == TIM_OCPOLARITY_HIGH) \
                                         || ((__VALUE__) == TIM_OCPOLARITY_LOW))

#define IS_TIM_OCIDLESTATE(__VALUE__) (((__VALUE__) == TIM_OCIDLESTATE_SET) \
                                          || ((__VALUE__) == TIM_OCIDLESTATE_RESET))

#define IS_TIM_ACTIVEINPUT(__VALUE__) (((__VALUE__) == TIM_ACTIVEINPUT_DIRECTTI) \
                                          || ((__VALUE__) == TIM_ACTIVEINPUT_INDIRECTTI) \
                                          || ((__VALUE__) == TIM_ACTIVEINPUT_TRC))

#define IS_TIM_ICPSC(__VALUE__) (((__VALUE__) == TIM_ICPSC_DIV1) \
                                    || ((__VALUE__) == TIM_ICPSC_DIV2) \
                                    || ((__VALUE__) == TIM_ICPSC_DIV4) \
                                    || ((__VALUE__) == TIM_ICPSC_DIV8))

#define IS_TIM_IC_FILTER(__VALUE__) (((__VALUE__) == TIM_IC_FILTER_FDIV1) \
                                        || ((__VALUE__) == TIM_IC_FILTER_FDIV1_N2) \
                                        || ((__VALUE__) == TIM_IC_FILTER_FDIV1_N4) \
                                        || ((__VALUE__) == TIM_IC_FILTER_FDIV1_N8) \
                                        || ((__VALUE__) == TIM_IC_FILTER_FDIV2_N6) \
                                        || ((__VALUE__) == TIM_IC_FILTER_FDIV2_N8) \
                                        || ((__VALUE__) == TIM_IC_FILTER_FDIV4_N6) \
                                        || ((__VALUE__) == TIM_IC_FILTER_FDIV4_N8) \
                                        || ((__VALUE__) == TIM_IC_FILTER_FDIV8_N6) \
                                        || ((__VALUE__) == TIM_IC_FILTER_FDIV8_N8) \
                                        || ((__VALUE__) == TIM_IC_FILTER_FDIV16_N5) \
                                        || ((__VALUE__) == TIM_IC_FILTER_FDIV16_N6) \
                                        || ((__VALUE__) == TIM_IC_FILTER_FDIV16_N8) \
                                        || ((__VALUE__) == TIM_IC_FILTER_FDIV32_N5) \
                                        || ((__VALUE__) == TIM_IC_FILTER_FDIV32_N6) \
                                        || ((__VALUE__) == TIM_IC_FILTER_FDIV32_N8))

#define IS_TIM_IC_POLARITY(__VALUE__) (((__VALUE__) == TIM_IC_POLARITY_RISING) \
                                          || ((__VALUE__) == TIM_IC_POLARITY_FALLING) \
                                          || ((__VALUE__) == TIM_IC_POLARITY_BOTHEDGE))

#define IS_TIM_ENCODERMODE(__VALUE__) (((__VALUE__) == TIM_ENCODERMODE_X2_TI1) \
                                          || ((__VALUE__) == TIM_ENCODERMODE_X2_TI2) \
                                          || ((__VALUE__) == TIM_ENCODERMODE_X4_TI12) \
                                          || ((__VALUE__) == TIM_ENCODERMODE_CLOCKPLUSDIRECTION_X2) \
                                          || ((__VALUE__) == TIM_ENCODERMODE_CLOCKPLUSDIRECTION_X1) \
                                          || ((__VALUE__) == TIM_ENCODERMODE_DIRECTIONALCLOCK_X2) \
                                          || ((__VALUE__) == TIM_ENCODERMODE_DIRECTIONALCLOCK_X1_TI12) \
                                          || ((__VALUE__) == TIM_ENCODERMODE_X1_TI1) \
                                          || ((__VALUE__) == TIM_ENCODERMODE_X1_TI2))

#define IS_TIM_IC_POLARITY_ENCODER(__VALUE__) (((__VALUE__) == TIM_IC_POLARITY_RISING) \
                                                  || ((__VALUE__) == TIM_IC_POLARITY_FALLING))

#define IS_TIM_OSSR_STATE(__VALUE__) (((__VALUE__) == TIM_OSSR_DISABLE) \
                                         || ((__VALUE__) == TIM_OSSR_ENABLE))

#define IS_TIM_OSSI_STATE(__VALUE__) (((__VALUE__) == TIM_OSSI_DISABLE) \
                                         || ((__VALUE__) == TIM_OSSI_ENABLE))

#define IS_TIM_LOCK_LEVEL(__VALUE__) (((__VALUE__) == TIM_LOCKLEVEL_OFF) \
                                         || ((__VALUE__) == TIM_LOCKLEVEL_1)   \
                                         || ((__VALUE__) == TIM_LOCKLEVEL_2)   \
                                         || ((__VALUE__) == TIM_LOCKLEVEL_3))

#define IS_TIM_BREAK_STATE(__VALUE__) (((__VALUE__) == TIM_BREAK_DISABLE) \
                                          || ((__VALUE__) == TIM_BREAK_ENABLE))

#define IS_TIM_BREAK_POLARITY(__VALUE__) (((__VALUE__) == TIM_BREAK_POLARITY_LOW) \
                                             || ((__VALUE__) == TIM_BREAK_POLARITY_HIGH))

#define IS_TIM_BREAK_FILTER(__VALUE__) (((__VALUE__) == TIM_BREAK_FILTER_FDIV1)     \
                                           || ((__VALUE__) == TIM_BREAK_FILTER_FDIV1_N2)  \
                                           || ((__VALUE__) == TIM_BREAK_FILTER_FDIV1_N4)  \
                                           || ((__VALUE__) == TIM_BREAK_FILTER_FDIV1_N8)  \
                                           || ((__VALUE__) == TIM_BREAK_FILTER_FDIV2_N6)  \
                                           || ((__VALUE__) == TIM_BREAK_FILTER_FDIV2_N8)  \
                                           || ((__VALUE__) == TIM_BREAK_FILTER_FDIV4_N6)  \
                                           || ((__VALUE__) == TIM_BREAK_FILTER_FDIV4_N8)  \
                                           || ((__VALUE__) == TIM_BREAK_FILTER_FDIV8_N6)  \
                                           || ((__VALUE__) == TIM_BREAK_FILTER_FDIV8_N8)  \
                                           || ((__VALUE__) == TIM_BREAK_FILTER_FDIV16_N5) \
                                           || ((__VALUE__) == TIM_BREAK_FILTER_FDIV16_N6) \
                                           || ((__VALUE__) == TIM_BREAK_FILTER_FDIV16_N8) \
                                           || ((__VALUE__) == TIM_BREAK_FILTER_FDIV32_N5) \
                                           || ((__VALUE__) == TIM_BREAK_FILTER_FDIV32_N6) \
                                           || ((__VALUE__) == TIM_BREAK_FILTER_FDIV32_N8))

#define IS_TIM_BREAK_AFMODE(__VALUE__) (((__VALUE__) == TIM_BREAK_AFMODE_INPUT)          \
                                           || ((__VALUE__) == TIM_BREAK_AFMODE_BIDIRECTIONAL))

#define IS_TIM_BREAK2_STATE(__VALUE__) (((__VALUE__) == TIM_BREAK2_DISABLE) \
                                           || ((__VALUE__) == TIM_BREAK2_ENABLE))

#define IS_TIM_BREAK2_POLARITY(__VALUE__) (((__VALUE__) == TIM_BREAK2_POLARITY_LOW) \
                                              || ((__VALUE__) == TIM_BREAK2_POLARITY_HIGH))

#define IS_TIM_BREAK2_FILTER(__VALUE__) (((__VALUE__) == TIM_BREAK2_FILTER_FDIV1)    \
                                            || ((__VALUE__) == TIM_BREAK2_FILTER_FDIV1_N2)  \
                                            || ((__VALUE__) == TIM_BREAK2_FILTER_FDIV1_N4)  \
                                            || ((__VALUE__) == TIM_BREAK2_FILTER_FDIV1_N8)  \
                                            || ((__VALUE__) == TIM_BREAK2_FILTER_FDIV2_N6)  \
                                            || ((__VALUE__) == TIM_BREAK2_FILTER_FDIV2_N8)  \
                                            || ((__VALUE__) == TIM_BREAK2_FILTER_FDIV4_N6)  \
                                            || ((__VALUE__) == TIM_BREAK2_FILTER_FDIV4_N8)  \
                                            || ((__VALUE__) == TIM_BREAK2_FILTER_FDIV8_N6)  \
                                            || ((__VALUE__) == TIM_BREAK2_FILTER_FDIV8_N8)  \
                                            || ((__VALUE__) == TIM_BREAK2_FILTER_FDIV16_N5) \
                                            || ((__VALUE__) == TIM_BREAK2_FILTER_FDIV16_N6) \
                                            || ((__VALUE__) == TIM_BREAK2_FILTER_FDIV16_N8) \
                                            || ((__VALUE__) == TIM_BREAK2_FILTER_FDIV32_N5) \
                                            || ((__VALUE__) == TIM_BREAK2_FILTER_FDIV32_N6) \
                                            || ((__VALUE__) == TIM_BREAK2_FILTER_FDIV32_N8))

#define IS_TIM_BREAK2_AFMODE(__VALUE__) (((__VALUE__) == TIM_BREAK2_AFMODE_INPUT)       \
                                            || ((__VALUE__) == TIM_BREAK2_AFMODE_BIDIRECTIONAL))

#define IS_TIM_AUTOMATIC_OUTPUT_STATE(__VALUE__) (((__VALUE__) == TIM_AUTOMATICOUTPUT_DISABLE) \
                                                     || ((__VALUE__) == TIM_AUTOMATICOUTPUT_ENABLE))



/** @defgroup TIM_Private_Variables TIM Private Variables
  * @{
  */
static const uint8_t OFFSET_TAB_CCMRx[] =
{
  0x00U,   /* 0: TIMx_CH1  */
  0x00U,   /* 1: TIMx_CH1N */
  0x00U,   /* 2: TIMx_CH2  */
  0x00U,   /* 3: TIMx_CH2N */
  0x04U,   /* 4: TIMx_CH3  */
  0x04U,   /* 5: TIMx_CH3N */
  0x04U,   /* 6: TIMx_CH4  */
  0x04U,   /* 7: TIMx_CH4N */
  0x38U,   /* 8: TIMx_CH5  */
  0x38U    /* 9: TIMx_CH6  */

};

static const uint8_t SHIFT_TAB_OCxx[] =
{
  0U,            /* 0: OC1M, OC1FE, OC1PE */
  0U,            /* 1: - NA */
  8U,            /* 2: OC2M, OC2FE, OC2PE */
  0U,            /* 3: - NA */
  0U,            /* 4: OC3M, OC3FE, OC3PE */
  0U,            /* 5: - NA */
  8U,            /* 6: OC4M, OC4FE, OC4PE */
  0U,            /* 7: - NA */
  0U,            /* 8: OC5M, OC5FE, OC5PE */
  8U             /* 9: OC6M, OC6FE, OC6PE */
};

static const uint8_t SHIFT_TAB_ICxx[] =
{
  0U,            /* 0: CC1S, IC1PSC, IC1F */
  0U,            /* 1: - NA */
  8U,            /* 2: CC2S, IC2PSC, IC2F */
  0U,            /* 3: - NA */
  0U,            /* 4: CC3S, IC3PSC, IC3F */
  0U,            /* 5: - NA */
  8U,            /* 6: CC4S, IC4PSC, IC4F */
  0U,            /* 7: - NA */
  0U,            /* 8: - NA */
  0U             /* 9: - NA */
};

static const uint8_t SHIFT_TAB_CCxP[] =
{
  0U,            /* 0: CC1P */
  2U,            /* 1: CC1NP */
  4U,            /* 2: CC2P */
  6U,            /* 3: CC2NP */
  8U,            /* 4: CC3P */
  10U,           /* 5: CC3NP */
  12U,           /* 6: CC4P */
  14U,           /* 7: CC4NP */
  16U,           /* 8: CC5P */
  20U            /* 9: CC6P */
};

static const uint8_t SHIFT_TAB_OISx[] =
{
  0U,            /* 0: OIS1 */
  1U,            /* 1: OIS1N */
  2U,            /* 2: OIS2 */
  3U,            /* 3: OIS2N */
  4U,            /* 4: OIS3 */
  5U,            /* 5: OIS3N */
  6U,            /* 6: OIS4 */
  7U,            /* 7: OIS4N */
  8U,            /* 8: OIS5 */
  10U            /* 9: OIS6 */
};
/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup TIM_Private_Constants TIM Private Constants
  * @{
  */

/* Defines used for the bit position in the register and perform offsets */
#define TIM_POSITION_BRK_SOURCE            (POSITION_VAL(Source) & 0x1FUL)

/* Generic bit definitions for TIMx_AF1 register */
#define TIMx_AF1_BKINP     TIM_AF1_BKINP     /*!< BRK BKIN input polarity */
#define TIMx_AF1_ETRSEL    TIM_AF1_ETRSEL    /*!< TIMx ETR source selection */


/* Mask used to set the TDG[x:0] of the DTG bits of the TIMx_BDTR register */
#define DT_DELAY_1 ((uint8_t)0x7F)
#define DT_DELAY_2 ((uint8_t)0x3F)
#define DT_DELAY_3 ((uint8_t)0x1F)
#define DT_DELAY_4 ((uint8_t)0x1F)

/* Mask used to set the DTG[7:5] bits of the DTG bits of the TIMx_BDTR register */
#define DT_RANGE_1 ((uint8_t)0x00)
#define DT_RANGE_2 ((uint8_t)0x80)
#define DT_RANGE_3 ((uint8_t)0xC0)
#define DT_RANGE_4 ((uint8_t)0xE0)

/** Legacy definitions for compatibility purpose
@cond 0
  */
/**
@endcond
  */

#define OCREF_CLEAR_SELECT_Pos (28U)
#define OCREF_CLEAR_SELECT_Msk (0x1U << OCREF_CLEAR_SELECT_Pos)                /*!< 0x10000000 */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup TIM_Private_Macros TIM Private Macros
  * @{
  */
/** @brief  Convert channel id into channel index.
  * @param  __CHANNEL__ This parameter can be one of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH1N
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH2N
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH3N
  *         @arg @ref TIM_CHANNEL_CH4
  *         @arg @ref TIM_CHANNEL_CH4N
  *         @arg @ref TIM_CHANNEL_CH5
  *         @arg @ref TIM_CHANNEL_CH6
  * @retval none
  */
#define TIM_GET_CHANNEL_INDEX( __CHANNEL__) \
  (((__CHANNEL__) == TIM_CHANNEL_CH1) ? 0U :\
   ((__CHANNEL__) == TIM_CHANNEL_CH1N) ? 1U :\
   ((__CHANNEL__) == TIM_CHANNEL_CH2) ? 2U :\
   ((__CHANNEL__) == TIM_CHANNEL_CH2N) ? 3U :\
   ((__CHANNEL__) == TIM_CHANNEL_CH3) ? 4U :\
   ((__CHANNEL__) == TIM_CHANNEL_CH3N) ? 5U :\
   ((__CHANNEL__) == TIM_CHANNEL_CH4) ? 6U :\
   ((__CHANNEL__) == TIM_CHANNEL_CH4N) ? 7U :\
   ((__CHANNEL__) == TIM_CHANNEL_CH5) ? 8U : 9U)

/** @brief  Calculate the deadtime sampling period(in ps).
  * @param  __TIMCLK__ timer input clock frequency (in Hz).
  * @param  __CKD__ This parameter can be one of the following values:
  *         @arg @ref TIM_CLOCKDIVISION_DIV1
  *         @arg @ref TIM_CLOCKDIVISION_DIV2
  *         @arg @ref TIM_CLOCKDIVISION_DIV4
  * @retval none
  */
#define TIM_CALC_DTS(__TIMCLK__, __CKD__)                                                        \
  (((__CKD__) == TIM_CLOCKDIVISION_DIV1) ? ((uint64_t)1000000000000U/(__TIMCLK__))         : \
   ((__CKD__) == TIM_CLOCKDIVISION_DIV2) ? ((uint64_t)1000000000000U/((__TIMCLK__) >> 1U)) : \
   ((uint64_t)1000000000000U/((__TIMCLK__) >> 2U)))
   
   
/** 
  * @brief  TIM base Init structure definition  
  */

/** @defgroup TIM_EC_BREAK_ENABLE Break Enable
  * @{
  */
#define TIM_BREAK_DISABLE            0x00000000U             /*!< Break function disabled */
#define TIM_BREAK_ENABLE             TIM_BDTR_BKE            /*!< Break function enabled */
/**
  * @}
  */

/** @defgroup TIM_EC_BREAK2_ENABLE Break2 Enable
  * @{
  */
#define TIM_BREAK2_DISABLE            0x00000000U              /*!< Break2 function disabled */
#define TIM_BREAK2_ENABLE             TIM_BDTR_BK2E            /*!< Break2 function enabled */
/**
  * @}
  */

/** @defgroup TIM_EC_AUTOMATICOUTPUT_ENABLE Automatic output enable
  * @{
  */
#define TIM_AUTOMATICOUTPUT_DISABLE         0x00000000U             /*!< MOE can be set only by software */
#define TIM_AUTOMATICOUTPUT_ENABLE          TIM_BDTR_AOE            /*!< MOE can be set by software or automatically at the next update event */
/**
  * @}
  */



/** @defgroup TIM_EC_UPDATESOURCE Update Source
  * @{
  */
#define TIM_UPDATESOURCE_REGULAR            0x00000000U          /*!< Counter overflow/underflow, Setting the UG bit or Update generation through the slave mode controller generates an update request */
#define TIM_UPDATESOURCE_COUNTER            TIM_CR1_URS          /*!< Only counter overflow/underflow generates an update request */
/**
  * @}
  */

/** @defgroup TIM_EC_ONEPULSEMODE One Pulse Mode
  * @{
  */
#define TIM_ONEPULSEMODE_SINGLE             TIM_CR1_OPM          /*!< Counter stops counting at the next update event */
#define TIM_ONEPULSEMODE_REPETITIVE         0x00000000U          /*!< Counter is not stopped at update event */
/**
  * @}
  */

/** @defgroup TIM_EC_COUNTERMODE Counter Mode
  * @{
  */
#define TIM_COUNTERMODE_UP                  0x00000000U          /*!<Counter used as upcounter */
#define TIM_COUNTERMODE_DOWN                TIM_CR1_DIR          /*!< Counter used as downcounter */
#define TIM_COUNTERMODE_CENTER_DOWN         TIM_CR1_CMS_0        /*!< The counter counts up and down alternatively. Output compare interrupt flags of output channels  are set only when the counter is counting down. */
#define TIM_COUNTERMODE_CENTER_UP           TIM_CR1_CMS_1        /*!<The counter counts up and down alternatively. Output compare interrupt flags of output channels  are set only when the counter is counting up */
#define TIM_COUNTERMODE_CENTER_UP_DOWN      TIM_CR1_CMS          /*!< The counter counts up and down alternatively. Output compare interrupt flags of output channels  are set only when the counter is counting up or down. */
/**
  * @}
  */

/** @defgroup TIM_EC_CLOCKDIVISION Clock Division
  * @{
  */
#define TIM_CLOCKDIVISION_DIV1              0x00000000U          /*!< tDTS=tCK_INT */
#define TIM_CLOCKDIVISION_DIV2              TIM_CR1_CKD_0        /*!< tDTS=2*tCK_INT */
#define TIM_CLOCKDIVISION_DIV4              TIM_CR1_CKD_1        /*!< tDTS=4*tCK_INT */
/**
  * @}
  */

/** @defgroup TIM_EC_COUNTERDIRECTION Counter Direction
  * @{
  */
#define TIM_COUNTERDIRECTION_UP             0x00000000U          /*!< Timer counter counts up */
#define TIM_COUNTERDIRECTION_DOWN           TIM_CR1_DIR          /*!< Timer counter counts down */
/**
  * @}
  */

/** @defgroup TIM_EC_CCUPDATESOURCE Capture Compare  Update Source
  * @{
  */
#define TIM_CCUPDATESOURCE_COMG_ONLY        0x00000000U          /*!< Capture/compare control bits are updated by setting the COMG bit only */
#define TIM_CCUPDATESOURCE_COMG_AND_TRGI    TIM_CR2_CCUS         /*!< Capture/compare control bits are updated by setting the COMG bit or when a rising edge occurs on trigger input (TRGI) */
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup TIM_EC_LOCKLEVEL Lock Level
  * @{
  */
#define TIM_LOCKLEVEL_OFF                   0x00000000U          /*!< LOCK OFF - No bit is write protected */
#define TIM_LOCKLEVEL_1                     TIM_BDTR_LOCK_0      /*!< LOCK Level 1 */
#define TIM_LOCKLEVEL_2                     TIM_BDTR_LOCK_1      /*!< LOCK Level 2 */
#define TIM_LOCKLEVEL_3                     TIM_BDTR_LOCK        /*!< LOCK Level 3 */
/**
  * @}
  */

/** @defgroup TIM_EC_CHANNEL Channel
  * @{
  */

#define TIM_CHANNEL_CH1                     (1<<0) 
#define TIM_CHANNEL_CH1N                    (1<<2) 
#define TIM_CHANNEL_CH2                     (1<<4) 
#define TIM_CHANNEL_CH2N                    (1<<6) 
#define TIM_CHANNEL_CH3                     (1<<8) 
#define TIM_CHANNEL_CH3N                    (1<<10)
#define TIM_CHANNEL_CH4                     (1<<12)
#define TIM_CHANNEL_CH4N                    (1<<14)
#define TIM_CHANNEL_CH5                     (1<<16)
#define TIM_CHANNEL_CH6                     (1<<20)
/**
  * @}
  */

/** @defgroup TIM_EC_OCSTATE Output Configuration State
  * @{
  */
#define TIM_OCSTATE_DISABLE                 0x00000000U             /*!< OCx is not active */
#define TIM_OCSTATE_ENABLE                  TIM_CCER_CC1E           /*!< OCx signal is output on the corresponding output pin */
/**
  * @}
  */

/** @defgroup TIM_EC_OCMODE Output Configuration Mode
  * @{
  */
#define TIM_OCMODE_FROZEN                   0x00000000U                                              /*!<The comparison between the output compare register TIMx_CCRy and the counter TIMx_CNT has no effect on the output channel level */
#define TIM_OCMODE_ACTIVE                   TIM_CCMR1_OC1M_0                                         /*!<OCyREF is forced high on compare match*/
#define TIM_OCMODE_INACTIVE                 TIM_CCMR1_OC1M_1                                         /*!<OCyREF is forced low on compare match*/
#define TIM_OCMODE_TOGGLE                   (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0)                    /*!<OCyREF toggles on compare match*/
#define TIM_OCMODE_FORCED_INACTIVE          TIM_CCMR1_OC1M_2                                         /*!<OCyREF is forced low*/
#define TIM_OCMODE_FORCED_ACTIVE            (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_0)                    /*!<OCyREF is forced high*/
#define TIM_OCMODE_PWM1                     (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1)                    /*!<In upcounting, channel y is active as long as TIMx_CNT<TIMx_CCRy else inactive.  In downcounting, channel y is inactive as long as TIMx_CNT>TIMx_CCRy else active.*/
#define TIM_OCMODE_PWM2                     (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0) /*!<In upcounting, channel y is inactive as long as TIMx_CNT<TIMx_CCRy else active.  In downcounting, channel y is active as long as TIMx_CNT>TIMx_CCRy else inactive*/
#define TIM_OCMODE_RETRIG_OPM1              TIM_CCMR1_OC1M_3                                         /*!<Retrigerrable OPM mode 1*/
#define TIM_OCMODE_RETRIG_OPM2              (TIM_CCMR1_OC1M_3 | TIM_CCMR1_OC1M_0)                    /*!<Retrigerrable OPM mode 2*/
#define TIM_OCMODE_COMBINED_PWM1            (TIM_CCMR1_OC1M_3 | TIM_CCMR1_OC1M_2)                    /*!<Combined PWM mode 1*/
#define TIM_OCMODE_COMBINED_PWM2            (TIM_CCMR1_OC1M_3 | TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_2) /*!<Combined PWM mode 2*/
#define TIM_OCMODE_ASSYMETRIC_PWM1          (TIM_CCMR1_OC1M_3 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2) /*!<Asymmetric PWM mode 1*/
#define TIM_OCMODE_ASSYMETRIC_PWM2          (TIM_CCMR1_OC1M_3 | TIM_CCMR1_OC1M)                      /*!<Asymmetric PWM mode 2*/
#define TIM_OCMODE_PULSE_ON_COMPARE         (TIM_CCMR2_OC3M_3 | TIM_CCMR2_OC3M_1)                    /*!<Pulse on Compare mode */
#define TIM_OCMODE_DIRECTION_OUTPUT         (TIM_CCMR2_OC3M_3 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_0) /*!<Direction output mode */
/**
  * @}
  */

/** @defgroup TIM_EC_OCPOLARITY Output Configuration Polarity
  * @{
  */
#define TIM_OCPOLARITY_HIGH                 0x00000000U                 /*!< OCxactive high*/
#define TIM_OCPOLARITY_LOW                  TIM_CCER_CC1P               /*!< OCxactive low*/


/** @defgroup TIM_EC_OCPOLARITY Output Configuration Polarity
  * @{
  */
#define TIM_OCNPOLARITY_HIGH                0x00000000U                 /*!< OCxactive high*/
#define TIM_OCNPOLARITY_LOW                 TIM_CCER_CC1NP               /*!< OCxactive low*/


/** @defgroup TIM_EC_OCIDLESTATE Output Configuration Idle State
  * @{
  */
#define TIM_OCIDLESTATE_RESET                0x00000000U             /*!<OCx=0 (after a dead-time if OC is implemented) when MOE=0*/
#define TIM_OCIDLESTATE_SET                  TIM_CR2_OIS1            /*!<OCx=1 (after a dead-time if OC is implemented) when MOE=0*/
/**
  * @}
  */
  
/** @defgroup TIM_EC_OCIDLESTATE Output Configuration Idle State
  * @{
  */
#define TIM_OCNIDLESTATE_RESET               0x00000000U             /*!<OCx=0 (after a dead-time if OC is implemented) when MOE=0*/
#define TIM_OCNIDLESTATE_SET                 TIM_CR2_OIS1N            /*!<OCx=1 (after a dead-time if OC is implemented) when MOE=0*/
/**
  * @}
  */  
  
  /** @defgroup TIM_Output_Compare_state 
  * @{
  */
#define TIM_OUTPUTSTATE_DISABLE             0x00000000U  
#define TIM_OUTPUTSTATE_ENABLE              TIM_CCER_CC1E  

/** @defgroup TIM_Output_Compare_state 
  * @{
  */
#define TIM_OUTPUTNSTATE_DISABLE             0x00000000U  
#define TIM_OUTPUTNSTATE_ENABLE              TIM_CCER_CC1NE 


/** @defgroup TIM_EC_GROUPCH5 GROUPCH5
  * @{
  */
#define TIM_GROUPCH5_NONE                   0x00000000U           /*!< No effect of OC5REF on OC1REFC, OC2REFC and OC3REFC */
#define TIM_GROUPCH5_OC1REFC                TIM_CCR5_GC5C1        /*!< OC1REFC is the logical AND of OC1REFC and OC5REF */
#define TIM_GROUPCH5_OC2REFC                TIM_CCR5_GC5C2        /*!< OC2REFC is the logical AND of OC2REFC and OC5REF */
#define TIM_GROUPCH5_OC3REFC                TIM_CCR5_GC5C3        /*!< OC3REFC is the logical AND of OC3REFC and OC5REF */
/**
  * @}
  */

/** @defgroup TIM_EC_ACTIVEINPUT Active Input Selection
  * @{
  */
#define TIM_ACTIVEINPUT_DIRECTTI            (TIM_CCMR1_CC1S_0 << 16U) /*!< ICx is mapped on TIx */
#define TIM_ACTIVEINPUT_INDIRECTTI          (TIM_CCMR1_CC1S_1 << 16U) /*!< ICx is mapped on TIy */
#define TIM_ACTIVEINPUT_TRC                 (TIM_CCMR1_CC1S << 16U)   /*!< ICx is mapped on TRC */
/**
  * @}
  */

/** @defgroup TIM_EC_ICPSC Input Configuration Prescaler
  * @{
  */
#define TIM_ICPSC_DIV1                      0x00000000U                    /*!< No prescaler, capture is done each time an edge is detected on the capture input */
#define TIM_ICPSC_DIV2                      (TIM_CCMR1_IC1PSC_0 << 16U)    /*!< Capture is done once every 2 events */
#define TIM_ICPSC_DIV4                      (TIM_CCMR1_IC1PSC_1 << 16U)    /*!< Capture is done once every 4 events */
#define TIM_ICPSC_DIV8                      (TIM_CCMR1_IC1PSC << 16U)      /*!< Capture is done once every 8 events */
/**
  * @}
  */

/** @defgroup TIM_EC_IC_FILTER Input Configuration Filter
  * @{
  */
#define TIM_IC_FILTER_FDIV1                 0x00000000U                                                        /*!< No filter, sampling is done at fDTS */
#define TIM_IC_FILTER_FDIV1_N2              (TIM_CCMR1_IC1F_0 << 16U)                                          /*!< fSAMPLING=fCK_INT, N=2 */
#define TIM_IC_FILTER_FDIV1_N4              (TIM_CCMR1_IC1F_1 << 16U)                                          /*!< fSAMPLING=fCK_INT, N=4 */
#define TIM_IC_FILTER_FDIV1_N8              ((TIM_CCMR1_IC1F_1 | TIM_CCMR1_IC1F_0) << 16U)                     /*!< fSAMPLING=fCK_INT, N=8 */
#define TIM_IC_FILTER_FDIV2_N6              (TIM_CCMR1_IC1F_2 << 16U)                                          /*!< fSAMPLING=fDTS/2, N=6 */
#define TIM_IC_FILTER_FDIV2_N8              ((TIM_CCMR1_IC1F_2 | TIM_CCMR1_IC1F_0) << 16U)                     /*!< fSAMPLING=fDTS/2, N=8 */
#define TIM_IC_FILTER_FDIV4_N6              ((TIM_CCMR1_IC1F_2 | TIM_CCMR1_IC1F_1) << 16U)                     /*!< fSAMPLING=fDTS/4, N=6 */
#define TIM_IC_FILTER_FDIV4_N8              ((TIM_CCMR1_IC1F_2 | TIM_CCMR1_IC1F_1 | TIM_CCMR1_IC1F_0) << 16U)  /*!< fSAMPLING=fDTS/4, N=8 */
#define TIM_IC_FILTER_FDIV8_N6              (TIM_CCMR1_IC1F_3 << 16U)                                          /*!< fSAMPLING=fDTS/8, N=6 */
#define TIM_IC_FILTER_FDIV8_N8              ((TIM_CCMR1_IC1F_3 | TIM_CCMR1_IC1F_0) << 16U)                     /*!< fSAMPLING=fDTS/8, N=8 */
#define TIM_IC_FILTER_FDIV16_N5             ((TIM_CCMR1_IC1F_3 | TIM_CCMR1_IC1F_1) << 16U)                     /*!< fSAMPLING=fDTS/16, N=5 */
#define TIM_IC_FILTER_FDIV16_N6             ((TIM_CCMR1_IC1F_3 | TIM_CCMR1_IC1F_1 | TIM_CCMR1_IC1F_0) << 16U)  /*!< fSAMPLING=fDTS/16, N=6 */
#define TIM_IC_FILTER_FDIV16_N8             ((TIM_CCMR1_IC1F_3 | TIM_CCMR1_IC1F_2) << 16U)                     /*!< fSAMPLING=fDTS/16, N=8 */
#define TIM_IC_FILTER_FDIV32_N5             ((TIM_CCMR1_IC1F_3 | TIM_CCMR1_IC1F_2 | TIM_CCMR1_IC1F_0) << 16U)  /*!< fSAMPLING=fDTS/32, N=5 */
#define TIM_IC_FILTER_FDIV32_N6             ((TIM_CCMR1_IC1F_3 | TIM_CCMR1_IC1F_2 | TIM_CCMR1_IC1F_1) << 16U)  /*!< fSAMPLING=fDTS/32, N=6 */
#define TIM_IC_FILTER_FDIV32_N8             (TIM_CCMR1_IC1F << 16U)                                            /*!< fSAMPLING=fDTS/32, N=8 */
/**
  * @}
  */

/** @defgroup TIM_EC_IC_POLARITY Input Configuration Polarity
  * @{
  */
#define TIM_IC_POLARITY_RISING              0x00000000U                      /*!< The circuit is sensitive to TIxFP1 rising edge, TIxFP1 is not inverted */
#define TIM_IC_POLARITY_FALLING             TIM_CCER_CC1P                    /*!< The circuit is sensitive to TIxFP1 falling edge, TIxFP1 is inverted */
#define TIM_IC_POLARITY_BOTHEDGE            (TIM_CCER_CC1P | TIM_CCER_CC1NP) /*!< The circuit is sensitive to both TIxFP1 rising and falling edges, TIxFP1 is not inverted */
/**
  * @}
  */

/** @defgroup TIM_EC_CLOCKSOURCE Clock Source
  * @{
  */
#define TIM_CLOCKSOURCE_INTERNAL            0x00000000U                                          /*!< The timer is clocked by the internal clock provided from the RCC */
#define TIM_CLOCKSOURCE_EXT_MODE1           (TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0)   /*!< Counter counts at each rising or falling edge on a selected input*/
#define TIM_CLOCKSOURCE_EXT_MODE2           TIM_SMCR_ECE                                         /*!< Counter counts at each rising or falling edge on the external trigger input ETR */
/**
  * @}
  */

/** @defgroup TIM_EC_ENCODERMODE Encoder Mode
  * @{
  */
#define  TIM_SMCR_SMS_DISABLED                                ((uint32_t)0x0000)          
#define  TIM_SMCR_SMS_ENCODER1                                ((uint32_t)0x0001)          
#define  TIM_SMCR_SMS_ENCODER2                                ((uint32_t)0x0002)          
#define  TIM_SMCR_SMS_ENCODER3                                ((uint32_t)0x0003)          
#define  TIM_SMCR_SMS_RESET                                   ((uint32_t)0x0004)         
#define  TIM_SMCR_SMS_GATEDRESET                              ((uint32_t)0x0005)        
#define  TIM_SMCR_SMS_TRIGGER                                 ((uint32_t)0x0006)         
#define  TIM_SMCR_SMS_EXTCLOCK1                               ((uint32_t)0x0007) 
#define  TIM_SMCR_SMS_COMBINED_RESETTRIGGER                   ((uint32_t)0x010000)
#define  TIM_SMCR_SMS_COMBINED_GATEDRESET                     ((uint32_t)0x010001)  
  
#define TIM_ENCODERMODE_X2_TI1                     TIM_SMCR_SMS_0                                                     /*!< Quadrature encoder mode 1, x2 mode - Counter counts up/down on TI1FP1 edge depending on TI2FP2 level */
#define TIM_ENCODERMODE_X2_TI2                     TIM_SMCR_SMS_1                                                     /*!< Quadrature encoder mode 2, x2 mode - Counter counts up/down on TI2FP2 edge depending on TI1FP1 level */
#define TIM_ENCODERMODE_X4_TI12                   (TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0)                                   /*!< Quadrature encoder mode 3, x4 mode - Counter counts up/down on both TI1FP1 and TI2FP2 edges depending on the level of the other input */
#define TIM_ENCODERMODE_CLOCKPLUSDIRECTION_X2     (TIM_SMCR_SMS_3 | TIM_SMCR_SMS_1)                                   /*!< Encoder mode: Clock plus direction - x2 mode */
#define TIM_ENCODERMODE_CLOCKPLUSDIRECTION_X1     (TIM_SMCR_SMS_3 | TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0)                  /*!< Encoder mode: Clock plus direction, x1 mode, TI2FP2 edge sensitivity is set by CC2P */
#define TIM_ENCODERMODE_DIRECTIONALCLOCK_X2       (TIM_SMCR_SMS_3 | TIM_SMCR_SMS_2)                                   /*!< Encoder mode: Directional Clock, x2 mode */
#define TIM_ENCODERMODE_DIRECTIONALCLOCK_X1_TI12  (TIM_SMCR_SMS_3 | TIM_SMCR_SMS_2 | TIM_SMCR_SMS_0)                  /*!< Encoder mode: Directional Clock, x1 mode, TI1FP1 and TI2FP2 edge sensitivity is set by CC1P and CC2P */
#define TIM_ENCODERMODE_X1_TI1                    (TIM_SMCR_SMS_3 | TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1)                  /*!< Quadrature encoder mode: x1 mode, counting on TI1FP1 edges only, edge sensitivity is set by CC1P */
#define TIM_ENCODERMODE_X1_TI2                    (TIM_SMCR_SMS_3 | TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0) /*!< Quadrature encoder mode: x1 mode, counting on TI2FP2 edges only, edge sensitivity is set by CC1P */
/**
  * @}
  */

/** @defgroup TIM_EC_TRGO Trigger Output
  * @{
  */
#define TIM_TRGO_RESET                      0x00000000U                                     /*!< UG bit from the TIMx_EGR register is used as trigger output */
#define TIM_TRGO_ENABLE                     TIM_CR2_MMS_0                                   /*!< Counter Enable signal (CNT_EN) is used as trigger output */
#define TIM_TRGO_UPDATE                     TIM_CR2_MMS_1                                   /*!< Update event is used as trigger output */
#define TIM_TRGO_CC1IF                      (TIM_CR2_MMS_1 | TIM_CR2_MMS_0)                 /*!< CC1 capture or a compare match is used as trigger output */
#define TIM_TRGO_OC1REF                     TIM_CR2_MMS_2                                   /*!< OC1REF signal is used as trigger output */
#define TIM_TRGO_OC2REF                     (TIM_CR2_MMS_2 | TIM_CR2_MMS_0)                 /*!< OC2REF signal is used as trigger output */
#define TIM_TRGO_OC3REF                     (TIM_CR2_MMS_2 | TIM_CR2_MMS_1)                 /*!< OC3REF signal is used as trigger output */
#define TIM_TRGO_OC4REF                     (TIM_CR2_MMS_2 | TIM_CR2_MMS_1 | TIM_CR2_MMS_0) /*!< OC4REF signal is used as trigger output */
#define TIM_TRGO_ENCODERCLK                 TIM_CR2_MMS_3                                   /*!< Encoder clock signal is used as trigger output */
/**
  * @}
  */

/** @defgroup TIM_EC_TRGO2 Trigger Output 2
  * @{
  */
#define TIM_TRGO2_RESET                     0x00000000U                                                         /*!< UG bit from the TIMx_EGR register is used as trigger output 2 */
#define TIM_TRGO2_ENABLE                    TIM_CR2_MMS2_0                                                      /*!< Counter Enable signal (CNT_EN) is used as trigger output 2 */
#define TIM_TRGO2_UPDATE                    TIM_CR2_MMS2_1                                                      /*!< Update event is used as trigger output 2 */
#define TIM_TRGO2_CC1F                      (TIM_CR2_MMS2_1 | TIM_CR2_MMS2_0)                                   /*!< CC1 capture or a compare match is used as trigger output 2 */
#define TIM_TRGO2_OC1                       TIM_CR2_MMS2_2                                                      /*!< OC1REF signal is used as trigger output 2 */
#define TIM_TRGO2_OC2                       (TIM_CR2_MMS2_2 | TIM_CR2_MMS2_0)                                   /*!< OC2REF signal is used as trigger output 2 */
#define TIM_TRGO2_OC3                       (TIM_CR2_MMS2_2 | TIM_CR2_MMS2_1)                                   /*!< OC3REF signal is used as trigger output 2 */
#define TIM_TRGO2_OC4                       (TIM_CR2_MMS2_2 | TIM_CR2_MMS2_1 | TIM_CR2_MMS2_0)                  /*!< OC4REF signal is used as trigger output 2 */
#define TIM_TRGO2_OC5                       TIM_CR2_MMS2_3                                                      /*!< OC5REF signal is used as trigger output 2 */
#define TIM_TRGO2_OC6                       (TIM_CR2_MMS2_3 | TIM_CR2_MMS2_0)                                   /*!< OC6REF signal is used as trigger output 2 */
#define TIM_TRGO2_OC4_RISINGFALLING         (TIM_CR2_MMS2_3 | TIM_CR2_MMS2_1)                                   /*!< OC4REF rising or falling edges are used as trigger output 2 */
#define TIM_TRGO2_OC6_RISINGFALLING         (TIM_CR2_MMS2_3 | TIM_CR2_MMS2_1 | TIM_CR2_MMS2_0)                  /*!< OC6REF rising or falling edges are used as trigger output 2 */
#define TIM_TRGO2_OC4_RISING_OC6_RISING     (TIM_CR2_MMS2_3 | TIM_CR2_MMS2_2)                                   /*!< OC4REF or OC6REF rising edges are used as trigger output 2 */
#define TIM_TRGO2_OC4_RISING_OC6_FALLING    (TIM_CR2_MMS2_3 | TIM_CR2_MMS2_2 | TIM_CR2_MMS2_0)                  /*!< OC4REF rising or OC6REF falling edges are used as trigger output 2 */
#define TIM_TRGO2_OC5_RISING_OC6_RISING     (TIM_CR2_MMS2_3 | TIM_CR2_MMS2_2 |TIM_CR2_MMS2_1)                   /*!< OC5REF or OC6REF rising edges are used as trigger output 2 */
#define TIM_TRGO2_OC5_RISING_OC6_FALLING    (TIM_CR2_MMS2_3 | TIM_CR2_MMS2_2 | TIM_CR2_MMS2_1 | TIM_CR2_MMS2_0) /*!< OC5REF rising or OC6REF falling edges are used as trigger output 2 */
/**
  * @}
  */

/** @defgroup TIM_EC_SLAVEMODE Slave Mode
  * @{
  */
#define TIM_SLAVEMODE_DISABLED              0x00000000U                         /*!< Slave mode disabled */
#define TIM_SLAVEMODE_RESET                 TIM_SMCR_SMS_2                      /*!< Reset Mode - Rising edge of the selected trigger input (TRGI) reinitializes the counter */
#define TIM_SLAVEMODE_GATED                 (TIM_SMCR_SMS_2 | TIM_SMCR_SMS_0)   /*!< Gated Mode - The counter clock is enabled when the trigger input (TRGI) is high */
#define TIM_SLAVEMODE_TRIGGER               (TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1)   /*!< Trigger Mode - The counter starts at a rising edge of the trigger TRGI */
#define TIM_SLAVEMODE_COMBINED_RESETTRIGGER TIM_SMCR_SMS_3                      /*!< Combined reset + trigger mode - Rising edge of the selected trigger input (TRGI)  reinitializes the counter, generates an update of the registers and starts the counter */
#define TIM_SLAVEMODE_COMBINED_GATEDRESET   (TIM_SMCR_SMS_3 | TIM_SMCR_SMS_0)   /*!< Combined gated + reset mode - The counter clock is enabled when the trigger input (TRGI) is high. The counter stops and is reset) as soon as the trigger becomes low.Both startand stop of
                                                                                        the counter are controlled. */
/**
  * @}
  */

/** @defgroup TIM_EC_SMS_PRELOAD_SOURCE SMS Preload Source
  * @{
  */
#define TIM_SMSPS_TIMUPDATE                 0x00000000U                         /*!< The SMS preload transfer is triggered by the Timer's Update event */
#define TIM_SMSPS_INDEX                     TIM_SMCR_SMSPS                      /*!< The SMS preload transfer is triggered by the Index event */
/**
  * @}
  */

/** @defgroup TIM_EC_TS Trigger Selection
  * @{
  */
#define TIM_TS_ITR0                         0x00000000U                                                     /*!< Internal Trigger 0 (ITR0) is used as trigger input */
#define TIM_TS_ITR1                         TIM_SMCR_TS_0                                                   /*!< Internal Trigger 1 (ITR1) is used as trigger input */
#define TIM_TS_ITR2                         TIM_SMCR_TS_1                                                   /*!< Internal Trigger 2 (ITR2) is used as trigger input */
#define TIM_TS_ITR3                         (TIM_SMCR_TS_0 | TIM_SMCR_TS_1)                                 /*!< Internal Trigger 3 (ITR3) is used as trigger input */
#define TIM_TS_TI1F_ED                      TIM_SMCR_TS_2                                                   /*!< TI1 Edge Detector (TI1F_ED) is used as trigger input */
#define TIM_TS_TI1FP1                       (TIM_SMCR_TS_2 | TIM_SMCR_TS_0)                                 /*!< Filtered Timer Input 1 (TI1FP1) is used as trigger input */
#define TIM_TS_TI2FP2                       (TIM_SMCR_TS_2 | TIM_SMCR_TS_1)                                 /*!< Filtered Timer Input 2 (TI12P2) is used as trigger input */
#define TIM_TS_ETRF                         (TIM_SMCR_TS_2 | TIM_SMCR_TS_1 | TIM_SMCR_TS_0)                 /*!< Filtered external Trigger (ETRF) is used as trigger input */
#define TIM_TS_ITR4                         TIM_SMCR_TS_3                                                   /*!< Internal Trigger 4 (ITR4) is used as trigger input */
#define TIM_TS_ITR5                         (TIM_SMCR_TS_3 | TIM_SMCR_TS_0)                                 /*!< Internal Trigger 5 (ITR5) is used as trigger input */
#define TIM_TS_ITR6                         (TIM_SMCR_TS_3 | TIM_SMCR_TS_1)                                 /*!< Internal Trigger 6 (ITR6) is used as trigger input */
#define TIM_TS_ITR7                         (TIM_SMCR_TS_3 | TIM_SMCR_TS_1 | TIM_SMCR_TS_0)                 /*!< Internal Trigger 7 (ITR7) is used as trigger input */
#define TIM_TS_ITR8                         (TIM_SMCR_TS_3 | TIM_SMCR_TS_2)                                 /*!< Internal Trigger 8 (ITR8) is used as trigger input */
#define TIM_TS_ITR9                         (TIM_SMCR_TS_3 | TIM_SMCR_TS_2 | TIM_SMCR_TS_0)                 /*!< Internal Trigger 9 (ITR9) is used as trigger input */
#define TIM_TS_ITR10                        (TIM_SMCR_TS_3 | TIM_SMCR_TS_2 | TIM_SMCR_TS_1)                 /*!< Internal Trigger 10 (ITR10) is used as trigger input */
#define TIM_TS_ITR11                        (TIM_SMCR_TS_3 | TIM_SMCR_TS_2 | TIM_SMCR_TS_1 | TIM_SMCR_TS_0) /*!< Internal Trigger 11 (ITR11) is used as trigger input */
/**
  * @}
  */

/** @defgroup TIM_EC_ETR_POLARITY External Trigger Polarity
  * @{
  */
#define TIM_ETR_POLARITY_NONINVERTED        0x00000000U             /*!< ETR is non-inverted, active at high level or rising edge */
#define TIM_ETR_POLARITY_INVERTED           TIM_SMCR_ETP            /*!< ETR is inverted, active at low level or falling edge */
/**
  * @}
  */

/** @defgroup TIM_EC_ETR_PRESCALER External Trigger Prescaler
  * @{
  */
#define TIM_ETR_PRESCALER_DIV1              0x00000000U             /*!< ETR prescaler OFF */
#define TIM_ETR_PRESCALER_DIV2              TIM_SMCR_ETPS_0         /*!< ETR frequency is divided by 2 */
#define TIM_ETR_PRESCALER_DIV4              TIM_SMCR_ETPS_1         /*!< ETR frequency is divided by 4 */
#define TIM_ETR_PRESCALER_DIV8              TIM_SMCR_ETPS           /*!< ETR frequency is divided by 8 */
/**
  * @}
  */

/** @defgroup TIM_EC_ETR_FILTER External Trigger Filter
  * @{
  */
#define TIM_ETR_FILTER_FDIV1                0x00000000U                                          /*!< No filter, sampling is done at fDTS */
#define TIM_ETR_FILTER_FDIV1_N2             TIM_SMCR_ETF_0                                       /*!< fSAMPLING=fCK_INT, N=2 */
#define TIM_ETR_FILTER_FDIV1_N4             TIM_SMCR_ETF_1                                       /*!< fSAMPLING=fCK_INT, N=4 */
#define TIM_ETR_FILTER_FDIV1_N8             (TIM_SMCR_ETF_1 | TIM_SMCR_ETF_0)                    /*!< fSAMPLING=fCK_INT, N=8 */
#define TIM_ETR_FILTER_FDIV2_N6             TIM_SMCR_ETF_2                                       /*!< fSAMPLING=fDTS/2, N=6 */
#define TIM_ETR_FILTER_FDIV2_N8             (TIM_SMCR_ETF_2 | TIM_SMCR_ETF_0)                    /*!< fSAMPLING=fDTS/2, N=8 */
#define TIM_ETR_FILTER_FDIV4_N6             (TIM_SMCR_ETF_2 | TIM_SMCR_ETF_1)                    /*!< fSAMPLING=fDTS/4, N=6 */
#define TIM_ETR_FILTER_FDIV4_N8             (TIM_SMCR_ETF_2 | TIM_SMCR_ETF_1 | TIM_SMCR_ETF_0)   /*!< fSAMPLING=fDTS/4, N=8 */
#define TIM_ETR_FILTER_FDIV8_N6             TIM_SMCR_ETF_3                                       /*!< fSAMPLING=fDTS/8, N=8 */
#define TIM_ETR_FILTER_FDIV8_N8             (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_0)                    /*!< fSAMPLING=fDTS/16, N=5 */
#define TIM_ETR_FILTER_FDIV16_N5            (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_1)                    /*!< fSAMPLING=fDTS/16, N=6 */
#define TIM_ETR_FILTER_FDIV16_N6            (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_1 | TIM_SMCR_ETF_0)   /*!< fSAMPLING=fDTS/16, N=8 */
#define TIM_ETR_FILTER_FDIV16_N8            (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_2)                    /*!< fSAMPLING=fDTS/16, N=5 */
#define TIM_ETR_FILTER_FDIV32_N5            (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_2 | TIM_SMCR_ETF_0)   /*!< fSAMPLING=fDTS/32, N=5 */
#define TIM_ETR_FILTER_FDIV32_N6            (TIM_SMCR_ETF_3 | TIM_SMCR_ETF_2 | TIM_SMCR_ETF_1)   /*!< fSAMPLING=fDTS/32, N=6 */
#define TIM_ETR_FILTER_FDIV32_N8            TIM_SMCR_ETF                                         /*!< fSAMPLING=fDTS/32, N=8 */
/**
  * @}
  */

/** @defgroup TIM_EC_TIM2_ETRSOURCE External Trigger Source TIM2
  * @{
  */
#define TIM_TIM2_ETRSOURCE_GPIO         0x00000000U                                                 /*!< ETR input is connected to GPIO */
#define TIM_TIM2_ETRSOURCE_COMP1        TIM_AF1_ETRSEL_0                                            /*!< ETR input is connected to COMP1_OUT */
#define TIM_TIM2_ETRSOURCE_COMP2        TIM_AF1_ETRSEL_1                                            /*!< ETR input is connected to COMP2_OUT */


/**
  * @}
  */

/** @defgroup TIM_EC_TIM3_ETRSOURCE External Trigger Source TIM3
  * @{
  */
#define TIM_TIM3_ETRSOURCE_GPIO         0x00000000U                                                 /*!< ETR input is connected to GPIO */
#define TIM_TIM3_ETRSOURCE_COMP1        TIM_AF1_ETRSEL_0                                            /*!< ETR input is connected to COMP1_OUT */
#define TIM_TIM3_ETRSOURCE_COMP2        TIM_AF1_ETRSEL_1                                            /*!< ETR input is connected to COMP2_OUT */

/**
  * @}
  */

/** @defgroup TIM_EC_TIM8_ETRSOURCE External Trigger Source TIM8
  * @{
  */
#define TIM_TIM8_ETRSOURCE_GPIO        0x00000000U                                                  /*!< ETR input is connected to GPIO */
#define TIM_TIM8_ETRSOURCE_COMP1       TIM_AF1_ETRSEL_0                                             /*!< ETR input is connected to COMP1_OUT */
#define TIM_TIM8_ETRSOURCE_COMP2       TIM_AF1_ETRSEL_1                                             /*!< ETR input is connected to COMP2_OUT */


/**
  * @}
  */

/** @defgroup TIM_EC_BREAK_POLARITY break polarity
  * @{
  */
#define TIM_BREAK_POLARITY_LOW              0x00000000U               /*!< Break input BRK is active low */
#define TIM_BREAK_POLARITY_HIGH             TIM_BDTR_BKP              /*!< Break input BRK is active high */
/**
  * @}
  */

/** @defgroup TIM_EC_BREAK_FILTER break filter
  * @{
  */
#define TIM_BREAK_FILTER_FDIV1              0x00000000U   /*!< No filter, BRK acts asynchronously */
#define TIM_BREAK_FILTER_FDIV1_N2           0x00010000U   /*!< fSAMPLING=fCK_INT, N=2 */
#define TIM_BREAK_FILTER_FDIV1_N4           0x00020000U   /*!< fSAMPLING=fCK_INT, N=4 */
#define TIM_BREAK_FILTER_FDIV1_N8           0x00030000U   /*!< fSAMPLING=fCK_INT, N=8 */
#define TIM_BREAK_FILTER_FDIV2_N6           0x00040000U   /*!< fSAMPLING=fDTS/2, N=6 */
#define TIM_BREAK_FILTER_FDIV2_N8           0x00050000U   /*!< fSAMPLING=fDTS/2, N=8 */
#define TIM_BREAK_FILTER_FDIV4_N6           0x00060000U   /*!< fSAMPLING=fDTS/4, N=6 */
#define TIM_BREAK_FILTER_FDIV4_N8           0x00070000U   /*!< fSAMPLING=fDTS/4, N=8 */
#define TIM_BREAK_FILTER_FDIV8_N6           0x00080000U   /*!< fSAMPLING=fDTS/8, N=6 */
#define TIM_BREAK_FILTER_FDIV8_N8           0x00090000U   /*!< fSAMPLING=fDTS/8, N=8 */
#define TIM_BREAK_FILTER_FDIV16_N5          0x000A0000U   /*!< fSAMPLING=fDTS/16, N=5 */
#define TIM_BREAK_FILTER_FDIV16_N6          0x000B0000U   /*!< fSAMPLING=fDTS/16, N=6 */
#define TIM_BREAK_FILTER_FDIV16_N8          0x000C0000U   /*!< fSAMPLING=fDTS/16, N=8 */
#define TIM_BREAK_FILTER_FDIV32_N5          0x000D0000U   /*!< fSAMPLING=fDTS/32, N=5 */
#define TIM_BREAK_FILTER_FDIV32_N6          0x000E0000U   /*!< fSAMPLING=fDTS/32, N=6 */
#define TIM_BREAK_FILTER_FDIV32_N8          0x000F0000U   /*!< fSAMPLING=fDTS/32, N=8 */
/**
  * @}
  */

/** @defgroup TIM_EC_BREAK2_POLARITY BREAK2 POLARITY
  * @{
  */
#define TIM_BREAK2_POLARITY_LOW             0x00000000U             /*!< Break input BRK2 is active low */
#define TIM_BREAK2_POLARITY_HIGH            TIM_BDTR_BK2P           /*!< Break input BRK2 is active high */
/**
  * @}
  */

/** @defgroup TIM_EC_BREAK2_FILTER BREAK2 FILTER
  * @{
  */
#define TIM_BREAK2_FILTER_FDIV1             0x00000000U   /*!< No filter, BRK acts asynchronously */
#define TIM_BREAK2_FILTER_FDIV1_N2          0x00100000U   /*!< fSAMPLING=fCK_INT, N=2 */
#define TIM_BREAK2_FILTER_FDIV1_N4          0x00200000U   /*!< fSAMPLING=fCK_INT, N=4 */
#define TIM_BREAK2_FILTER_FDIV1_N8          0x00300000U   /*!< fSAMPLING=fCK_INT, N=8 */
#define TIM_BREAK2_FILTER_FDIV2_N6          0x00400000U   /*!< fSAMPLING=fDTS/2, N=6 */
#define TIM_BREAK2_FILTER_FDIV2_N8          0x00500000U   /*!< fSAMPLING=fDTS/2, N=8 */
#define TIM_BREAK2_FILTER_FDIV4_N6          0x00600000U   /*!< fSAMPLING=fDTS/4, N=6 */
#define TIM_BREAK2_FILTER_FDIV4_N8          0x00700000U   /*!< fSAMPLING=fDTS/4, N=8 */
#define TIM_BREAK2_FILTER_FDIV8_N6          0x00800000U   /*!< fSAMPLING=fDTS/8, N=6 */
#define TIM_BREAK2_FILTER_FDIV8_N8          0x00900000U   /*!< fSAMPLING=fDTS/8, N=8 */
#define TIM_BREAK2_FILTER_FDIV16_N5         0x00A00000U   /*!< fSAMPLING=fDTS/16, N=5 */
#define TIM_BREAK2_FILTER_FDIV16_N6         0x00B00000U   /*!< fSAMPLING=fDTS/16, N=6 */
#define TIM_BREAK2_FILTER_FDIV16_N8         0x00C00000U   /*!< fSAMPLING=fDTS/16, N=8 */
#define TIM_BREAK2_FILTER_FDIV32_N5         0x00D00000U   /*!< fSAMPLING=fDTS/32, N=5 */
#define TIM_BREAK2_FILTER_FDIV32_N6         0x00E00000U   /*!< fSAMPLING=fDTS/32, N=6 */
#define TIM_BREAK2_FILTER_FDIV32_N8         0x00F00000U   /*!< fSAMPLING=fDTS/32, N=8 */
/**
  * @}
  */

/** @defgroup TIM_EC_OSSI OSSI
  * @{
  */
#define TIM_OSSI_DISABLE                    0x00000000U             /*!< When inactive, OCx/OCxN outputs are disabled */
#define TIM_OSSI_ENABLE                     TIM_BDTR_OSSI           /*!< When inactive, OxC/OCxN outputs are first forced with their inactive level then forced to their idle level after the deadtime */
/**
  * @}
  */

/** @defgroup TIM_EC_OSSR OSSR
  * @{
  */
#define TIM_OSSR_DISABLE                    0x00000000U             /*!< When inactive, OCx/OCxN outputs are disabled */
#define TIM_OSSR_ENABLE                     TIM_BDTR_OSSR           /*!< When inactive, OC/OCN outputs are enabled with their inactive level as soon as CCxE=1 or CCxNE=1 */
/**
  * @}
  */

/** @defgroup TIM_EC_BREAK_INPUT BREAK INPUT
  * @{
  */
#define TIM_BREAK_INPUT_BKIN                0x00000000U  /*!< TIMx_BKIN input */
#define TIM_BREAK_INPUT_BKIN2               0x00000004U  /*!< TIMx_BKIN2 input */
/**
  * @}
  */

/** @defgroup TIM_EC_BKIN_SOURCE BKIN SOURCE
  * @{
  */
#define TIM_BKIN_SOURCE_BKIN                TIM_AF1_BKINE      /*!< BKIN input from AF controller */
#define TIM_BKIN_SOURCE_BKCOMP1             TIM_AF1_BKCMP1E    /*!< internal signal: COMP1 output */
#define TIM_BKIN_SOURCE_BKCOMP2             TIM_AF1_BKCMP2E    /*!< internal signal: COMP2 output */

/**
  * @}
  */

/** @defgroup TIM_EC_BKIN_POLARITY BKIN POLARITY
  * @{
  */
#define TIM_BKIN_POLARITY_LOW               TIM_AF1_BKINP            /*!< BRK BKIN input is active low */
#define TIM_BKIN_POLARITY_HIGH              0x00000000U              /*!< BRK BKIN input is active high */
/**
  * @}
  */

/** @defgroup TIM_EC_BREAK_AFMODE BREAK AF MODE
  * @{
  */
#define TIM_BREAK_AFMODE_INPUT              0x00000000U              /*!< Break input BRK in input mode */
#define TIM_BREAK_AFMODE_BIDIRECTIONAL      TIM_BDTR_BKBID           /*!< Break input BRK in bidirectional mode */
/**
  * @}
  */

/** @defgroup TIM_EC_BREAK2_AFMODE BREAK2 AF MODE
  * @{
  */
#define TIM_BREAK2_AFMODE_INPUT             0x00000000U             /*!< Break2 input BRK2 in input mode */
#define TIM_BREAK2_AFMODE_BIDIRECTIONAL     TIM_BDTR_BK2BID         /*!< Break2 input BRK2 in bidirectional mode */
/**
  * @}
  */

/** @defgroup TIM_EC_TIM2_TI1_RMP  TIM2 Timer Input Ch1 Remap
  * @{
  */
#define TIM_TIM2_TI1_RMP_GPIO   0x00000000U                                       /*!< TIM2 input 1 is connected to GPIO */
#define TIM_TIM2_TI1_RMP_COMP1  TIM_TISEL_TI1SEL_0                                /*!< TIM2 input 1 is connected to COMP1_OUT */
#define TIM_TIM2_TI1_RMP_COMP2  TIM_TISEL_TI1SEL_1                                /*!< TIM2 input 1 is connected to COMP2_OUT */
/**
  * @}
  */

/** @defgroup TIM_EC_TIM2_TI2_RMP  TIM2 Timer Input Ch2 Remap
  * @{
  */
#define TIM_TIM2_TI2_RMP_GPIO   0x00000000U                                       /*!< TIM2 input 2 is connected to GPIO */
#define TIM_TIM2_TI2_RMP_COMP1  TIM_TISEL_TI2SEL_0                                /*!< TIM2 input 2 is connected to COMP1_OUT */
#define TIM_TIM2_TI2_RMP_COMP2  TIM_TISEL_TI2SEL_1                                /*!< TIM2 input 2 is connected to COMP2_OUT */
/**
  * @}
  */

/** @defgroup TIM_EC_TIM2_TI3_RMP  TIM2 Timer Input Ch3 Remap
  * @{
  */
#define TIM_TIM2_TI3_RMP_GPIO   0x00000000U                                       /*!< TIM2 input 3 is connected to GPIO */
/**
  * @}
  */

/** @defgroup TIM_EC_TIM2_TI4_RMP  TIM2 Timer Input Ch4 Remap
  * @{
  */
#define TIM_TIM2_TI4_RMP_GPIO   0x00000000U                                       /*!< TIM2 input 4 is connected to GPIO */
#define TIM_TIM2_TI4_RMP_COMP1  TIM_TISEL_TI4SEL_0                                /*!< TIM2 input 4 is connected to COMP1_OUT */
#define TIM_TIM2_TI4_RMP_COMP2  TIM_TISEL_TI4SEL_1                                /*!< TIM2 input 4 is connected to COMP2_OUT */
/**
  * @}
  */

/** @defgroup TIM_EC_TIM3_TI1_RMP  TIM3 Timer Input Ch1 Remap
  * @{
  */
#define TIM_TIM3_TI1_RMP_GPIO   0x00000000U                                       /*!< TIM3 input 1 is connected to GPIO */
#define TIM_TIM3_TI1_RMP_COMP1  TIM_TISEL_TI1SEL_0                                /*!< TIM3 input 1 is connected to COMP1_OUT */
#define TIM_TIM3_TI1_RMP_COMP2  TIM_TISEL_TI1SEL_1                                /*!< TIM3 input 1 is connected to COMP2_OUT */
/**
  * @}
  */

/** @defgroup TIM_EC_TIM3_TI2_RMP  TIM3 Timer Input Ch2 Remap
  * @{
  */
#define TIM_TIM3_TI2_RMP_GPIO   0x00000000U                                       /*!< TIM3 input 2 is connected to GPIO */
#define TIM_TIM3_TI2_RMP_COMP1  TIM_TISEL_TI2SEL_0                                /*!< TIM3 input 2 is connected to COMP1_OUT */
#define TIM_TIM3_TI2_RMP_COMP2  TIM_TISEL_TI2SEL_1                                /*!< TIM3 input 2 is connected to COMP2_OUT */
/**
  * @}
  */

/** @defgroup TIM_EC_TIM3_TI3_RMP  TIM3 Timer Input Ch3 Remap
  * @{
  */
#define TIM_TIM3_TI3_RMP_GPIO   0x00000000U                                       /*!< TIM3 input 3 is connected to GPIO */
/**
  * @}
  */
/** @defgroup TIM_EC_TIM8_TI1_RMP  TIM8 Timer Input Ch1 Remap
  * @{
  */
#define TIM_TIM8_TI1_RMP_GPIO   0x00000000U                                       /*!< TIM8 input 1 is connected to GPIO */
#define TIM_TIM8_TI1_RMP_COMP1  TIM_TISEL_TI1SEL_0                                /*!< TIM8 input 1 is connected to COMP1_OUT */
#define TIM_TIM8_TI1_RMP_COMP2  TIM_TISEL_TI1SEL_1                                /*!< TIM8 input 1 is connected to COMP2_OUT */
/**
  * @}
  */

/** @defgroup TIM_EC_TIM15_TI1_RMP  TIM15 Timer Input Ch1 Remap
  * @{
  */
#define TIM_TIM15_TI1_RMP_GPIO  0x00000000U                                       /*!< TIM15 input 1 is connected to GPIO */
#define TIM_TIM15_TI1_RMP_LSI   TIM_TISEL_TI1SEL_0                                /*!< TIM15 input 1 is connected to LSE */
#define TIM_TIM15_TI1_RMP_COMP1 TIM_TISEL_TI1SEL_1                                /*!< TIM15 input 1 is connected to COMP1_OUT */
#define TIM_TIM15_TI1_RMP_COMP2 (TIM_TISEL_TI1SEL_1 | TIM_TISEL_TI1SEL_0)         /*!< TIM15 input 1 is connected to COMP2_OUT */
/**
  * @}
  */

/** @defgroup TIM_EC_TIM15_TI2_RMP  TIM15 Timer Input Ch2 Remap
  * @{
  */
#define TIM_TIM15_TI2_RMP_GPIO  0x00000000U                                       /*!< TIM15 input 2 is connected to GPIO */
#define TIM_TIM15_TI2_RMP_COMP2 TIM_TISEL_TI2SEL_0                                /*!< TIM15 input 2 is connected to COMP2_OUT */
/**
  * @}
  */

/** @defgroup TIM_EC_OCREF_CLR_INT OCREF clear input selection
  * @{
  */
#define TIM_OCREF_CLR_INT_ETR         OCREF_CLEAR_SELECT_Msk                   /*!< OCREF_CLR_INT is connected to ETRF */
#define TIM_OCREF_CLR_INT_COMP1       0x00000000U                              /*!< OCREF clear input is connected to COMP1_OUT */
#define TIM_OCREF_CLR_INT_COMP2       TIM_AF2_OCRSEL_0                         /*!< OCREF clear input is connected to COMP2_OUT */
/**
  * @}
  */

/** @defgroup TIM_EC_INDEX_DIR index direction selection
  * @{
  */
#define TIM_INDEX_UP_DOWN     0x00000000U         /*!< Index resets the counter whatever the direction */
#define TIM_INDEX_UP          TIM_ECR_IDIR_0      /*!< Index resets the counter when up-counting only */
#define TIM_INDEX_DOWN        TIM_ECR_IDIR_1      /*!< Index resets the counter when down-counting only */
/**
  * @}
  */

/** @defgroup TIM_EC_INDEX_POSITION index positioning selection
  * @{
  */
#define TIM_INDEX_POSITION_DOWN_DOWN    0x00000000U                           /*!< Index resets the counter when AB = 00 */
#define TIM_INDEX_POSITION_DOWN_UP      TIM_ECR_IPOS_0                        /*!< Index resets the counter when AB = 01 */
#define TIM_INDEX_POSITION_UP_DOWN      TIM_ECR_IPOS_1                        /*!< Index resets the counter when AB = 10 */
#define TIM_INDEX_POSITION_UP_UP        (TIM_ECR_IPOS_1 | TIM_ECR_IPOS_0)     /*!< Index resets the counter when AB = 11 */
#define TIM_INDEX_POSITION_DOWN         0x00000000U                           /*!< Index resets the counter when clock is 0 */
#define TIM_INDEX_POSITION_UP           TIM_ECR_IPOS_0                        /*!< Index resets the counter when clock is 1 */
/**
  * @}
  */

/** @defgroup TIM_EC_FIRST_INDEX first index selection
  * @{
  */
#define TIM_INDEX_ALL           0x00000000U                           /*!< Index is always active */
#define TIM_INDEX_FIRST_ONLY    TIM_ECR_FIDX                          /*!< The first Index only resets the counter */
/**
  * @}
  */
/** @defgroup TIM_EC_PWPRSC Pulse on compare pulse width prescaler
  * @{
  */
#define TIM_PWPRSC_X1     0x00000000U                                              /*!< Pulse on compare pulse width prescaler 1 */
#define TIM_PWPRSC_X2     TIM_ECR_PWPRSC_0                                         /*!< Pulse on compare pulse width prescaler 2 */
#define TIM_PWPRSC_X4     TIM_ECR_PWPRSC_1                                         /*!< Pulse on compare pulse width prescaler 4 */
#define TIM_PWPRSC_X8     (TIM_ECR_PWPRSC_1 | TIM_ECR_PWPRSC_0)                    /*!< Pulse on compare pulse width prescaler 8 */
#define TIM_PWPRSC_X16    TIM_ECR_PWPRSC_2                                         /*!< Pulse on compare pulse width prescaler 16 */
#define TIM_PWPRSC_X32    (TIM_ECR_PWPRSC_2 | TIM_ECR_PWPRSC_0)                    /*!< Pulse on compare pulse width prescaler 32 */
#define TIM_PWPRSC_X64    (TIM_ECR_PWPRSC_2 | TIM_ECR_PWPRSC_1)                    /*!< Pulse on compare pulse width prescaler 64 */
#define TIM_PWPRSC_X128   (TIM_ECR_PWPRSC_2 | TIM_ECR_PWPRSC_1 | TIM_ECR_PWPRSC_0) /*!< Pulse on compare pulse width prescaler 128 */
/**
  * @}
  */

/**
@endcond
  */
/**
  * @}
  */

#define TIM_AF_BKINE                 BIT0
#define TIM_AF_BKCMP1E               BIT1
#define TIM_AF_BKCMP2E               BIT2

#define TIM_AF_BKINP                 BIT9
#define TIM_AF_BKCMP1P               BIT10
#define TIM_AF_BKCMP2P               BIT11


#define TIM_BKCMP_POLARITY_NoInvert            0           /*!< BRK BKCMP input is no invert */
#define TIM_BKCMP_POLARITY_Invert              1           /*!< BRK BKCMP input is invert */

#define TIM_BKIN_POLARITY_Invert               TIM_AF1_BKINP             /*!< BRK BKIN input is active low */
#define TIM_BKIN_POLARITY_NoInvert              0x00000000U              /*!< BRK BKIN input is active high */


/**********************  Bit definition for BIC register of TIM_TypeDef ***********************/
#define  TIM_BIC                                              ((uint32_t)0x0000003F) 
#define  TIM_BICE_EN                                          ((uint32_t)0x00000001) 
#define  TIM_BICS_CH1_EN                                      ((uint32_t)0x00000002) 
#define  TIM_BICS_CH2_EN                                      ((uint32_t)0x00000004) 
#define  TIM_BICS_CH3_EN                                      ((uint32_t)0x00000008) 
#define  TIM_BICS_CH4_EN                                      ((uint32_t)0x00000010) 
#define  TIM_BICS_CH5_EN                                      ((uint32_t)0x00000020) 
#define  TIM_BICS_CH6_EN                                      ((uint32_t)0x00000040) 

      
#define  TIM_SMCR_TS_ITR0                                     ((uint32_t)0x0000)       
#define  TIM_SMCR_TS_ITR1                                     ((uint32_t)0x0010)         
#define  TIM_SMCR_TS_ITR2                                     ((uint32_t)0x0020)          
#define  TIM_SMCR_TS_ITR3                                     ((uint32_t)0x0030)          
#define  TIM_SMCR_TS_TI1F_ED                                  ((uint32_t)0x0040)          
#define  TIM_SMCR_TS_TI1FP1                                   ((uint32_t)0x0050)         
#define  TIM_SMCR_TS_TI2FP2                                   ((uint32_t)0x0060)          
#define  TIM_SMCR_TS_ETRF                                     ((uint32_t)0x0070)  
#define  TIM_SMCR_TS_ITR4                                     ((uint32_t)0x100000) 
#define  TIM_SMCR_TS_ITR5                                     ((uint32_t)0x100010)
#define  TIM_SMCR_TS_ITR6                                     ((uint32_t)0x100020)
#define  TIM_SMCR_TS_ITR7                                     ((uint32_t)0x100030)
#define  TIM_SMCR_TS_ITR8                                     ((uint32_t)0x100040)
#define  TIM_SMCR_TS_ITR9                                     ((uint32_t)0x100050)
#define  TIM_SMCR_TS_ITR10                                    ((uint32_t)0x100060)


#define  TIM_SMCR_ETF_FDIV1                                   ((uint32_t)0x0000) 
#define  TIM_SMCR_ETF_FDIV1_N2                                ((uint32_t)0x0100) 
#define  TIM_SMCR_ETF_FDIV1_N4                                ((uint32_t)0x0200) 
#define  TIM_SMCR_ETF_FDIV1_N8                                ((uint32_t)0x0300) 
#define  TIM_SMCR_ETF_FDIV2_N6                                ((uint32_t)0x0400) 
#define  TIM_SMCR_ETF_FDIV2_N8                                ((uint32_t)0x0500) 
#define  TIM_SMCR_ETF_FDIV4_N6                                ((uint32_t)0x0600) 
#define  TIM_SMCR_ETF_FDIV4_N8                                ((uint32_t)0x0700) 
#define  TIM_SMCR_ETF_FDIV8_N6                                ((uint32_t)0x0800) 
#define  TIM_SMCR_ETF_FDIV8_N8                                ((uint32_t)0x0900) 
#define  TIM_SMCR_ETF_FDIV16_N5                               ((uint32_t)0x0A00) 
#define  TIM_SMCR_ETF_FDIV16_N6                               ((uint32_t)0x0B00) 
#define  TIM_SMCR_ETF_FDIV16_N8                               ((uint32_t)0x0C00) 
#define  TIM_SMCR_ETF_FDIV32_N5                               ((uint32_t)0x0D00) 
#define  TIM_SMCR_ETF_FDIV32_N6                               ((uint32_t)0x0E00) 
#define  TIM_SMCR_ETF_FDIV32_N8                               ((uint32_t)0x0F00) 

#define  TIM_SMCR_ETPS_DIV1                                   ((uint32_t)0x0000)        
#define  TIM_SMCR_ETPS_DIV2                                   ((uint32_t)0x1000)       
#define  TIM_SMCR_ETPS_DIV4                                   ((uint32_t)0x2000)          
#define  TIM_SMCR_ETPS_DIV8                                   ((uint32_t)0x3000)          

/**********************  Bit definition for CCR1N register of TIM_TypeDef ***********************/
#define  TIM_CCR1N                                            ((uint32_t)0xFFFF) 
#define  TIM_CCR1N_EN                                         ((uint32_t)0x80000000) 

/**********************  Bit definition for CCR2N register of TIM_TypeDef ***********************/
#define  TIM_CCR2N                                            ((uint32_t)0xFFFF) 
#define  TIM_CCR2N_EN                                         ((uint32_t)0x80000000) 

/**********************  Bit definition for CCR3N register of TIM_TypeDef ***********************/
#define  TIM_CCR3N                                            ((uint32_t)0xFFFF) 
#define  TIM_CCR3N_EN                                         ((uint32_t)0x80000000) 

/**********************  Bit definition for CCR4N register of TIM_TypeDef ***********************/
#define  TIM_CCR4N                                            ((uint32_t)0xFFFF) 
#define  TIM_CCR4N_EN                                         ((uint32_t)0x80000000) 

/**********************  Bit definition for CCRxN register of TIM_TypeDef ***********************/
#define  TIM_CCRxN                                            ((uint32_t)0xFFFF) 
#define  TIM_CCRxN_EN                                         ((uint32_t)0x80000000) 

/* Exported macro ------------------------------------------------------------*/
/** @defgroup TIM_Exported_Macros TIM Exported Macros
  * @{
  */

/** @defgroup TIM_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */
/**
  * @brief  Write a value in TIM register.
  * @param  __INSTANCE__ TIM Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define TIM_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG((__INSTANCE__)->__REG__, (__VALUE__))

/**
  * @brief  Read a value in TIM register.
  * @param  __INSTANCE__ TIM Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define TIM_ReadReg(__INSTANCE__, __REG__) READ_REG((__INSTANCE__)->__REG__)
/**
  * @}
  */

/** @defgroup TIM_EM_Exported_Macros Exported_Macros
  * @{
  */

/**
  * @brief  HELPER macro retrieving the UIFCPY flag from the counter value.
  * @note ex: @ref __TIM_GETFLAG_UIFCPY (@ref TIM_GetCounter ());
  * @note  Relevant only if UIF flag remapping has been enabled  (UIF status bit is copied
  *        to TIMx_CNT register bit 31)
  * @param  __CNT__ Counter value
  * @retval UIF status bit
  */
#define __TIM_GETFLAG_UIFCPY(__CNT__)  \
  (READ_BIT((__CNT__), TIM_CNT_UIFCPY) >> TIM_CNT_UIFCPY_Pos)

/**
  * @brief  HELPER macro calculating DTG[0:7] in the TIMx_BDTR register to achieve the requested dead time duration.
  * @note ex: @ref __TIM_CALC_DEADTIME (80000000, @ref TIM_GetClockDivision (), 120);
  * @param  __TIMCLK__ timer input clock frequency (in Hz)
  * @param  __CKD__ This parameter can be one of the following values:
  *         @arg @ref TIM_CLOCKDIVISION_DIV1
  *         @arg @ref TIM_CLOCKDIVISION_DIV2
  *         @arg @ref TIM_CLOCKDIVISION_DIV4
  * @param  __DT__ deadtime duration (in ns)
  * @retval DTG[0:7]
  */
#define __TIM_CALC_DEADTIME(__TIMCLK__, __CKD__, __DT__)  \
  ( (((uint64_t)((__DT__)*1000U)) < ((DT_DELAY_1+1U) * TIM_CALC_DTS((__TIMCLK__), (__CKD__))))    ?  \
    (uint8_t)(((uint64_t)((__DT__)*1000U) / TIM_CALC_DTS((__TIMCLK__), (__CKD__)))  & DT_DELAY_1) :      \
    (((uint64_t)((__DT__)*1000U)) < ((64U + (DT_DELAY_2+1U)) * 2U * TIM_CALC_DTS((__TIMCLK__), (__CKD__))))  ?  \
    (uint8_t)(DT_RANGE_2 | ((uint8_t)((uint8_t)((((uint64_t)((__DT__)*1000U))/ TIM_CALC_DTS((__TIMCLK__),   \
                                                 (__CKD__))) >> 1U) - (uint8_t) 64) & DT_DELAY_2)) :\
    (((uint64_t)((__DT__)*1000U)) < ((32U + (DT_DELAY_3+1U)) * 8U * TIM_CALC_DTS((__TIMCLK__), (__CKD__))))  ?  \
    (uint8_t)(DT_RANGE_3 | ((uint8_t)((uint8_t)(((((uint64_t)(__DT__)*1000U))/ TIM_CALC_DTS((__TIMCLK__),  \
                                                 (__CKD__))) >> 3U) - (uint8_t) 32) & DT_DELAY_3)) :\
    (((uint64_t)((__DT__)*1000U)) < ((32U + (DT_DELAY_4+1U)) * 16U * TIM_CALC_DTS((__TIMCLK__), (__CKD__)))) ?  \
    (uint8_t)(DT_RANGE_4 | ((uint8_t)((uint8_t)(((((uint64_t)(__DT__)*1000U))/ TIM_CALC_DTS((__TIMCLK__),  \
                                                 (__CKD__))) >> 4U) - (uint8_t) 32) & DT_DELAY_4)) :\
    0U)

/**
  * @brief  HELPER macro calculating the prescaler value to achieve the required counter clock frequency.
  * @note ex: @ref __TIM_CALC_PSC (80000000, 1000000);
  * @param  __TIMCLK__ timer input clock frequency (in Hz)
  * @param  __CNTCLK__ counter clock frequency (in Hz)
  * @retval Prescaler value  (between Min_Data=0 and Max_Data=65535)
  */
#define __TIM_CALC_PSC(__TIMCLK__, __CNTCLK__)   \
  (((__TIMCLK__) >= (__CNTCLK__)) ? (uint32_t)(((__TIMCLK__)/(__CNTCLK__)) - 1U) : 0U)

/**
  * @brief  HELPER macro calculating the auto-reload value to achieve the required output signal frequency.
  * @note ex: @ref __TIM_CALC_ARR (1000000, @ref TIM_GetPrescaler (), 10000);
  * @param  __TIMCLK__ timer input clock frequency (in Hz)
  * @param  __PSC__ prescaler
  * @param  __FREQ__ output signal frequency (in Hz)
  * @retval  Auto-reload value  (between Min_Data=0 and Max_Data=65535)
  */
#define __TIM_CALC_ARR(__TIMCLK__, __PSC__, __FREQ__) \
  ((((__TIMCLK__)/((__PSC__) + 1U)) >= (__FREQ__)) ? (((__TIMCLK__)/((__FREQ__) * ((__PSC__) + 1U))) - 1U) : 0U)

/**
  * @brief  HELPER macro calculating the auto-reload value, with dithering feature enabled, to achieve the required
  *         output signal frequency.
  * @note ex: @ref __TIM_CALC_ARR_DITHER (1000000, @ref TIM_GetPrescaler (), 10000);
  * @param  __TIMCLK__ timer input clock frequency (in Hz)
  * @param  __PSC__ prescaler
  * @param  __FREQ__ output signal frequency (in Hz)
  * @retval  Auto-reload value  (between Min_Data=0 and Max_Data=65535)
  */
#define __TIM_CALC_ARR_DITHER(__TIMCLK__, __PSC__, __FREQ__) \
  ((((__TIMCLK__)/((__PSC__) + 1U)) >= (__FREQ__)) ? \
   (uint32_t)((((uint64_t)(__TIMCLK__) * 16U/((__FREQ__) * ((__PSC__) + 1U))) - 16U)) : 0U)

/**
  * @brief  HELPER macro calculating the compare value required to achieve the required timer output compare
  *         active/inactive delay.
  * @note ex: @ref __TIM_CALC_DELAY (1000000, @ref TIM_GetPrescaler (), 10);
  * @param  __TIMCLK__ timer input clock frequency (in Hz)
  * @param  __PSC__ prescaler
  * @param  __DELAY__ timer output compare active/inactive delay (in us)
  * @retval Compare value  (between Min_Data=0 and Max_Data=65535)
  */
#define __TIM_CALC_DELAY(__TIMCLK__, __PSC__, __DELAY__)  \
  ((uint32_t)(((uint64_t)(__TIMCLK__) * (uint64_t)(__DELAY__)) \
              / ((uint64_t)1000000U * (uint64_t)((__PSC__) + 1U))))

/**
  * @brief  HELPER macro calculating the compare value, with dithering feature enabled, to achieve the required timer
  *         output compare active/inactive delay.
  * @note ex: @ref __TIM_CALC_DELAY_DITHER (1000000, @ref TIM_GetPrescaler (), 10);
  * @param  __TIMCLK__ timer input clock frequency (in Hz)
  * @param  __PSC__ prescaler
  * @param  __DELAY__ timer output compare active/inactive delay (in us)
  * @retval Compare value  (between Min_Data=0 and Max_Data=65535)
  */
#define __TIM_CALC_DELAY_DITHER(__TIMCLK__, __PSC__, __DELAY__)  \
  ((uint32_t)(((uint64_t)(__TIMCLK__) * (uint64_t)(__DELAY__) * 16U) \
              / ((uint64_t)1000000U * (uint64_t)((__PSC__) + 1U))))

/**
  * @brief  HELPER macro calculating the auto-reload value to achieve the required pulse duration
  *         (when the timer operates in one pulse mode).
  * @note ex: @ref __TIM_CALC_PULSE (1000000, @ref TIM_GetPrescaler (), 10, 20);
  * @param  __TIMCLK__ timer input clock frequency (in Hz)
  * @param  __PSC__ prescaler
  * @param  __DELAY__ timer output compare active/inactive delay (in us)
  * @param  __PULSE__ pulse duration (in us)
  * @retval Auto-reload value  (between Min_Data=0 and Max_Data=65535)
  */
#define __TIM_CALC_PULSE(__TIMCLK__, __PSC__, __DELAY__, __PULSE__)  \
  ((uint32_t)(__TIM_CALC_DELAY((__TIMCLK__), (__PSC__), (__PULSE__)) \
              + __TIM_CALC_DELAY((__TIMCLK__), (__PSC__), (__DELAY__))))

/**
  * @brief  HELPER macro calculating the auto-reload value, with dithering feature enabled, to achieve the required
  *         pulse duration (when the timer operates in one pulse mode).
  * @note ex: @ref __TIM_CALC_PULSE_DITHER (1000000, @ref TIM_GetPrescaler (), 10, 20);
  * @param  __TIMCLK__ timer input clock frequency (in Hz)
  * @param  __PSC__ prescaler
  * @param  __DELAY__ timer output compare active/inactive delay (in us)
  * @param  __PULSE__ pulse duration (in us)
  * @retval Auto-reload value  (between Min_Data=0 and Max_Data=65535)
  */
#define __TIM_CALC_PULSE_DITHER(__TIMCLK__, __PSC__, __DELAY__, __PULSE__)  \
  ((uint32_t)(__TIM_CALC_DELAY_DITHER((__TIMCLK__), (__PSC__), (__PULSE__)) \
              + __TIM_CALC_DELAY_DITHER((__TIMCLK__), (__PSC__), (__DELAY__))))

/**
  * @brief  HELPER macro retrieving the ratio of the input capture prescaler
  * @note ex: @ref __TIM_GET_ICPSC_RATIO (@ref TIM_IC_GetPrescaler ());
  * @param  __ICPSC__ This parameter can be one of the following values:
  *         @arg @ref TIM_ICPSC_DIV1
  *         @arg @ref TIM_ICPSC_DIV2
  *         @arg @ref TIM_ICPSC_DIV4
  *         @arg @ref TIM_ICPSC_DIV8
  * @retval Input capture prescaler ratio (1, 2, 4 or 8)
  */
#define __TIM_GET_ICPSC_RATIO(__ICPSC__)  \
  ((uint32_t)(0x01U << (((__ICPSC__) >> 16U) >> TIM_CCMR1_IC1PSC_Pos)))  

typedef struct
{
  uint16_t Prescaler;         /*!< Specifies the prescaler value used to divide the TIM clock.
                                   This parameter can be a number between Min_Data=0x0000 and Max_Data=0xFFFF.

                                   This feature can be modified afterwards using unitary function
                                   @ref TIM_SetPrescaler().*/

  uint32_t CounterMode;       /*!< Specifies the counter mode.
                                   This parameter can be a value of @ref TIM_EC_COUNTERMODE.

                                   This feature can be modified afterwards using unitary function
                                   @ref TIM_SetCounterMode().*/
  
  uint32_t Period;            /*!< Specifies the auto reload value to be loaded into the active
                                   Auto-Reload Register at the next update event.
                                   This parameter must be a number between Min_Data=0x0000 and Max_Data=0xFFFF.
                                   Some timer instances may support 32 bits counters. In that case this parameter must
                                   be a number between 0x0000 and 0xFFFFFFFF.

                                   This feature can be modified afterwards using unitary function
                                   @ref TIM_SetAutoReload().*/

  uint32_t ClockDivision;     /*!< Specifies the clock division.
                                   This parameter can be a value of @ref TIM_EC_CLOCKDIVISION.

                                   This feature can be modified afterwards using unitary function
                                   @ref TIM_SetClockDivision().*/

  uint32_t RepetitionCounter;  /*!< Specifies the repetition counter value. Each time the RCR downcounter
                                   reaches zero, an update event is generated and counting restarts
                                   from the RCR value (N).
                                   This means in PWM mode that (N+1) corresponds to:
                                      - the number of PWM periods in edge-aligned mode
                                      - the number of half PWM period in center-aligned mode
                                   GP timers: this parameter must be a number between Min_Data = 0x00 and
                                   Max_Data = 0xFF.
                                   Advanced timers: this parameter must be a number between Min_Data = 0x0000 and
                                   Max_Data = 0xFFFF.

                                   This feature can be modified afterwards using unitary function
                                   @ref TIM_SetRepetitionCounter().*/
} TIM_TimeBaseInitTypeDef;

/**
  * @brief  TIM Output Compare configuration structure definition.
  */
typedef struct
{
  uint32_t OCMode;        /*!< Specifies the output mode.
                               This parameter can be a value of @ref TIM_EC_OCMODE.

                               This feature can be modified afterwards using unitary function
                               @ref TIM_OC_SetMode().*/

  uint32_t OutputState;       /*!< Specifies the TIM Output Compare state.
                               This parameter can be a value of @ref TIM_EC_OCSTATE.

                               This feature can be modified afterwards using unitary functions
                               @ref TIM_CC_EnableChannel() or @ref TIM_CC_DisableChannel().*/

  uint32_t OutputNState;      /*!< Specifies the TIM complementary Output Compare state.
                               This parameter can be a value of @ref TIM_EC_OCSTATE.

                               This feature can be modified afterwards using unitary functions
                               @ref TIM_CC_EnableChannel() or @ref TIM_CC_DisableChannel().*/

  uint32_t Pulse;  /*!< Specifies the Compare value to be loaded into the Capture Compare Register.
                               This parameter can be a number between Min_Data=0x0000 and Max_Data=0xFFFF.

                               This feature can be modified afterwards using unitary function
                               TIM_OC_SetCompareCHx (x=1..6).*/

  uint32_t OCPolarity;    /*!< Specifies the output polarity.
                               This parameter can be a value of @ref TIM_EC_OCPOLARITY.

                               This feature can be modified afterwards using unitary function
                               @ref TIM_OC_SetPolarity().*/

  uint32_t OCNPolarity;   /*!< Specifies the complementary output polarity.
                               This parameter can be a value of @ref TIM_EC_OCPOLARITY.

                               This feature can be modified afterwards using unitary function
                               @ref TIM_OC_SetPolarity().*/


  uint32_t OCIdleState;   /*!< Specifies the TIM Output Compare pin state during Idle state.
                               This parameter can be a value of @ref TIM_EC_OCIDLESTATE.

                               This feature can be modified afterwards using unitary function
                               @ref TIM_OC_SetIdleState().*/

  uint32_t OCNIdleState;  /*!< Specifies the TIM Output Compare pin state during Idle state.
                               This parameter can be a value of @ref TIM_EC_OCIDLESTATE.

                               This feature can be modified afterwards using unitary function
                               @ref TIM_OC_SetIdleState().*/
} TIM_OCInitTypeDef;

/**
  * @brief  TIM Input Capture configuration structure definition.
  */

typedef struct
{
  uint32_t Channel;                  /*!< Specifies the TIM channel
                                      This parameter can be a value of @ref TIM_Channel */

  uint32_t ICPolarity;    /*!< Specifies the active edge of the input signal.
                               This parameter can be a value of @ref TIM_EC_IC_POLARITY.

                               This feature can be modified afterwards using unitary function
                               @ref TIM_IC_SetPolarity().*/

  uint32_t ICSelection; /*!< Specifies the input.
                               This parameter can be a value of @ref TIM_EC_ACTIVEINPUT.

                               This feature can be modified afterwards using unitary function
                               @ref TIM_IC_SetActiveInput().*/

  uint32_t ICPrescaler;   /*!< Specifies the Input Capture Prescaler.
                               This parameter can be a value of @ref TIM_EC_ICPSC.

                               This feature can be modified afterwards using unitary function
                               @ref TIM_IC_SetPrescaler().*/

  uint32_t ICFilter;      /*!< Specifies the input capture filter.
                               This parameter can be a value of @ref TIM_EC_IC_FILTER.

                               This feature can be modified afterwards using unitary function
                               @ref TIM_IC_SetFilter().*/
} TIM_ICInitTypeDef;


/**
  * @brief  TIM Encoder interface configuration structure definition.
  */
typedef struct
{
  uint32_t EncoderMode;     /*!< Specifies the encoder resolution (x2 or x4).
                                 This parameter can be a value of @ref TIM_EC_ENCODERMODE.

                                 This feature can be modified afterwards using unitary function
                                 @ref TIM_SetEncoderMode().*/

  uint32_t IC1Polarity;     /*!< Specifies the active edge of TI1 input.
                                 This parameter can be a value of @ref TIM_EC_IC_POLARITY.

                                 This feature can be modified afterwards using unitary function
                                 @ref TIM_IC_SetPolarity().*/

  uint32_t IC1ActiveInput;  /*!< Specifies the TI1 input source
                                 This parameter can be a value of @ref TIM_EC_ACTIVEINPUT.

                                 This feature can be modified afterwards using unitary function
                                 @ref TIM_IC_SetActiveInput().*/

  uint32_t IC1Prescaler;    /*!< Specifies the TI1 input prescaler value.
                                 This parameter can be a value of @ref TIM_EC_ICPSC.

                                 This feature can be modified afterwards using unitary function
                                 @ref TIM_IC_SetPrescaler().*/

  uint32_t IC1Filter;       /*!< Specifies the TI1 input filter.
                                 This parameter can be a value of @ref TIM_EC_IC_FILTER.

                                 This feature can be modified afterwards using unitary function
                                 @ref TIM_IC_SetFilter().*/

  uint32_t IC2Polarity;      /*!< Specifies the active edge of TI2 input.
                                 This parameter can be a value of @ref TIM_EC_IC_POLARITY.

                                 This feature can be modified afterwards using unitary function
                                 @ref TIM_IC_SetPolarity().*/

  uint32_t IC2ActiveInput;  /*!< Specifies the TI2 input source
                                 This parameter can be a value of @ref TIM_EC_ACTIVEINPUT.

                                 This feature can be modified afterwards using unitary function
                                 @ref TIM_IC_SetActiveInput().*/

  uint32_t IC2Prescaler;    /*!< Specifies the TI2 input prescaler value.
                                 This parameter can be a value of @ref TIM_EC_ICPSC.

                                 This feature can be modified afterwards using unitary function
                                 @ref TIM_IC_SetPrescaler().*/

  uint32_t IC2Filter;       /*!< Specifies the TI2 input filter.
                                 This parameter can be a value of @ref TIM_EC_IC_FILTER.

                                 This feature can be modified afterwards using unitary function
                                 @ref TIM_IC_SetFilter().*/

} TIM_ENCODER_InitTypeDef;

/**
  * @brief  TIM Hall sensor interface configuration structure definition.
  */
typedef struct
{

  uint32_t IC1Polarity;        /*!< Specifies the active edge of TI1 input.
                                    This parameter can be a value of @ref TIM_EC_IC_POLARITY.

                                    This feature can be modified afterwards using unitary function
                                    @ref TIM_IC_SetPolarity().*/

  uint32_t IC1Prescaler;       /*!< Specifies the TI1 input prescaler value.
                                    Prescaler must be set to get a maximum counter period longer than the
                                    time interval between 2 consecutive changes on the Hall inputs.
                                    This parameter can be a value of @ref TIM_EC_ICPSC.

                                    This feature can be modified afterwards using unitary function
                                    @ref TIM_IC_SetPrescaler().*/

  uint32_t IC1Filter;          /*!< Specifies the TI1 input filter.
                                    This parameter can be a value of
                                    @ref TIM_EC_IC_FILTER.

                                    This feature can be modified afterwards using unitary function
                                    @ref TIM_IC_SetFilter().*/

  uint32_t CommutationDelay;   /*!< Specifies the compare value to be loaded into the Capture Compare Register.
                                    A positive pulse (TRGO event) is generated with a programmable delay every time
                                    a change occurs on the Hall inputs.
                                    This parameter can be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF.

                                    This feature can be modified afterwards using unitary function
                                    @ref TIM_OC_SetCompareCH2().*/
} TIM_HALLSENSOR_InitTypeDef;

/**
  * @brief  BDTR (Break and Dead Time) structure definition
  */
typedef struct
{
  uint32_t OSSRState;            /*!< Specifies the Off-State selection used in Run mode.
                                      This parameter can be a value of @ref TIM_EC_OSSR

                                      This feature can be modified afterwards using unitary function
                                      @ref TIM_SetOffStates()

                                      @note This bit-field cannot be modified as long as LOCK level 2 has been
                                       programmed. */

  uint32_t OSSIState;            /*!< Specifies the Off-State used in Idle state.
                                      This parameter can be a value of @ref TIM_EC_OSSI

                                      This feature can be modified afterwards using unitary function
                                      @ref TIM_SetOffStates()

                                      @note This bit-field cannot be modified as long as LOCK level 2 has been
                                      programmed. */

  uint32_t LOCKLevel;            /*!< Specifies the LOCK level parameters.
                                      This parameter can be a value of @ref TIM_EC_LOCKLEVEL

                                      @note The LOCK bits can be written only once after the reset. Once the TIMx_BDTR
                                      register has been written, their content is frozen until the next reset.*/

  uint8_t DeadTime;              /*!< Specifies the delay time between the switching-off and the
                                      switching-on of the outputs.
                                      This parameter can be a number between Min_Data = 0x00 and Max_Data = 0xFF.

                                      This feature can be modified afterwards using unitary function
                                      @ref TIM_OC_SetDeadTime()

                                      @note This bit-field can not be modified as long as LOCK level 1, 2 or 3 has been
                                       programmed. */

  uint16_t BreakState;           /*!< Specifies whether the TIM Break input is enabled or not.
                                      This parameter can be a value of @ref TIM_EC_BREAK_ENABLE

                                      This feature can be modified afterwards using unitary functions
                                      @ref TIM_EnableBRK() or @ref TIM_DisableBRK()

                                      @note This bit-field can not be modified as long as LOCK level 1 has been
                                      programmed. */

  uint32_t BreakPolarity;        /*!< Specifies the TIM Break Input pin polarity.
                                      This parameter can be a value of @ref TIM_EC_BREAK_POLARITY

                                      This feature can be modified afterwards using unitary function
                                      @ref TIM_ConfigBRK()

                                      @note This bit-field can not be modified as long as LOCK level 1 has been
                                      programmed. */

  uint32_t BreakFilter;          /*!< Specifies the TIM Break Filter.
                                      This parameter can be a value of @ref TIM_EC_BREAK_FILTER

                                      This feature can be modified afterwards using unitary function
                                      @ref TIM_ConfigBRK()

                                      @note This bit-field can not be modified as long as LOCK level 1 has been
                                      programmed. */

  uint32_t BreakAFMode;           /*!< Specifies the alternate function mode of the break input.
                                      This parameter can be a value of @ref TIM_EC_BREAK_AFMODE

                                      This feature can be modified afterwards using unitary functions
                                      @ref TIM_ConfigBRK()

                                      @note Bidirectional break input is only supported by advanced timers instances.

                                      @note This bit-field can not be modified as long as LOCK level 1 has been
                                      programmed. */

  uint32_t Break2State;          /*!< Specifies whether the TIM Break2 input is enabled or not.
                                      This parameter can be a value of @ref TIM_EC_BREAK2_ENABLE

                                      This feature can be modified afterwards using unitary functions
                                      @ref TIM_EnableBRK2() or @ref TIM_DisableBRK2()

                                      @note This bit-field can not be modified as long as LOCK level 1 has been
                                      programmed. */

  uint32_t Break2Polarity;        /*!< Specifies the TIM Break2 Input pin polarity.
                                      This parameter can be a value of @ref TIM_EC_BREAK2_POLARITY

                                      This feature can be modified afterwards using unitary function
                                      @ref TIM_ConfigBRK2()

                                      @note This bit-field can not be modified as long as LOCK level 1 has been
                                      programmed. */

  uint32_t Break2Filter;          /*!< Specifies the TIM Break2 Filter.
                                      This parameter can be a value of @ref TIM_EC_BREAK2_FILTER

                                      This feature can be modified afterwards using unitary function
                                      @ref TIM_ConfigBRK2()

                                      @note This bit-field can not be modified as long as LOCK level 1 has been
                                      programmed. */

  uint32_t Break2AFMode;          /*!< Specifies the alternate function mode of the break2 input.
                                      This parameter can be a value of @ref TIM_EC_BREAK2_AFMODE

                                      This feature can be modified afterwards using unitary functions
                                      @ref TIM_ConfigBRK2()

                                      @note Bidirectional break input is only supported by advanced timers instances.

                                      @note This bit-field can not be modified as long as LOCK level 1 has been
                                      programmed. */

  uint32_t AutomaticOutput;      /*!< Specifies whether the TIM Automatic Output feature is enabled or not.
                                      This parameter can be a value of @ref TIM_EC_AUTOMATICOUTPUT_ENABLE

                                      This feature can be modified afterwards using unitary functions
                                      @ref TIM_EnableAutomaticOutput() or @ref TIM_DisableAutomaticOutput()

                                      @note This bit-field can not be modified as long as LOCK level 1 has been
                                      programmed. */
} TIM_BDTRInitTypeDef;


/**
  * @brief  Enable timer counter.
  * @rmtoll CR1          CEN           TIM_EnableCounter
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Enable_CEN(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->CR1, TIM_CR1_CEN);
}

/**
  * @brief  Disable timer counter.
  * @rmtoll CR1          CEN           TIM_DisableCounter
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Disable_CEN(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->CR1, TIM_CR1_CEN);
}

/**
  * @brief  Indicates whether the timer counter is enabled.
  * @rmtoll CR1          CEN           TIM_IsEnabledCounter
  * @param  TIMx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t TIM_Get_CEN(TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->CR1, TIM_CR1_CEN) == (TIM_CR1_CEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable update event generation.
  * @rmtoll CR1          UDIS          TIM_EnableUpdateEvent
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Enable_UpdateEvent(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->CR1, TIM_CR1_UDIS);
}

/**
  * @brief  Disable update event generation.
  * @rmtoll CR1          UDIS          TIM_DisableUpdateEvent
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Disable_UpdateEvent(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->CR1, TIM_CR1_UDIS);
}

/**
  * @brief  Indicates whether update event generation is enabled.
  * @rmtoll CR1          UDIS          TIM_IsEnabledUpdateEvent
  * @param  TIMx Timer instance
  * @retval Inverted state of bit (0 or 1).
  */
__STATIC_INLINE uint32_t TIM_Get_UpdateEvent(TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->CR1, TIM_CR1_UDIS) == (uint32_t)RESET) ? 1UL : 0UL);
}

/**
  * @brief  Set update event source
  * @note Update event source set to TIM_UPDATESOURCE_REGULAR: any of the following events
  *       generate an update interrupt or DMA request if enabled:
  *        - Counter overflow/underflow
  *        - Setting the UG bit
  *        - Update generation through the slave mode controller
  * @note Update event source set to TIM_UPDATESOURCE_COUNTER: only counter
  *       overflow/underflow generates an update interrupt or DMA request if enabled.
  * @rmtoll CR1          URS           TIM_SetUpdateSource
  * @param  TIMx Timer instance
  * @param  UpdateSource This parameter can be one of the following values:
  *         @arg @ref TIM_UPDATESOURCE_REGULAR
  *         @arg @ref TIM_UPDATESOURCE_COUNTER
  * @retval None
  */
__STATIC_INLINE void TIM_Set_UpdateSource(TIM_TypeDef *TIMx, uint32_t UpdateSource)
{
  MODIFY_REG(TIMx->CR1, TIM_CR1_URS, UpdateSource);
}

/**
  * @brief  Get actual event update source
  * @rmtoll CR1          URS           TIM_GetUpdateSource
  * @param  TIMx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref TIM_UPDATESOURCE_REGULAR
  *         @arg @ref TIM_UPDATESOURCE_COUNTER
  */
__STATIC_INLINE uint32_t TIM_Get_UpdateSource(TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_BIT(TIMx->CR1, TIM_CR1_URS));
}

/**
  * @brief  Set one pulse mode (one shot v.s. repetitive).
  * @rmtoll CR1          OPM           TIM_SetOnePulseMode
  * @param  TIMx Timer instance
  * @param  OnePulseMode This parameter can be one of the following values:
  *         @arg @ref TIM_ONEPULSEMODE_SINGLE
  *         @arg @ref TIM_ONEPULSEMODE_REPETITIVE
  * @retval None
  */
__STATIC_INLINE void TIM_Set_OnePulseMode(TIM_TypeDef *TIMx, uint32_t OnePulseMode)
{
  MODIFY_REG(TIMx->CR1, TIM_CR1_OPM, OnePulseMode);
}

/**
  * @brief  Get actual one pulse mode.
  * @rmtoll CR1          OPM           TIM_GetOnePulseMode
  * @param  TIMx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref TIM_ONEPULSEMODE_SINGLE
  *         @arg @ref TIM_ONEPULSEMODE_REPETITIVE
  */
__STATIC_INLINE uint32_t TIM_Get_OnePulseMode(TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_BIT(TIMx->CR1, TIM_CR1_OPM));
}

/**
  * @brief  Set the timer counter counting mode.
  * @note Macro IS_TIM_COUNTER_MODE_SELECT_INSTANCE(TIMx) can be used to
  *       check whether or not the counter mode selection feature is supported
  *       by a timer instance.
  * @note Switching from Center Aligned counter mode to Edge counter mode (or reverse)
  *       requires a timer reset to avoid unexpected direction
  *       due to DIR bit readonly in center aligned mode.
  * @rmtoll CR1          DIR           TIM_SetCounterMode\n
  *         CR1          CMS           TIM_SetCounterMode
  * @param  TIMx Timer instance
  * @param  CounterMode This parameter can be one of the following values:
  *         @arg @ref TIM_COUNTERMODE_UP
  *         @arg @ref TIM_COUNTERMODE_DOWN
  *         @arg @ref TIM_COUNTERMODE_CENTER_UP
  *         @arg @ref TIM_COUNTERMODE_CENTER_DOWN
  *         @arg @ref TIM_COUNTERMODE_CENTER_UP_DOWN
  * @retval None
  */
__STATIC_INLINE void TIM_Set_CounterMode(TIM_TypeDef *TIMx, uint32_t CounterMode)
{
  MODIFY_REG(TIMx->CR1, (TIM_CR1_DIR | TIM_CR1_CMS), CounterMode);
}

/**
  * @brief  Get actual counter mode.
  * @note Macro IS_TIM_COUNTER_MODE_SELECT_INSTANCE(TIMx) can be used to
  *       check whether or not the counter mode selection feature is supported
  *       by a timer instance.
  * @rmtoll CR1          DIR           TIM_GetCounterMode\n
  *         CR1          CMS           TIM_GetCounterMode
  * @param  TIMx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref TIM_COUNTERMODE_UP
  *         @arg @ref TIM_COUNTERMODE_DOWN
  *         @arg @ref TIM_COUNTERMODE_CENTER_UP
  *         @arg @ref TIM_COUNTERMODE_CENTER_DOWN
  *         @arg @ref TIM_COUNTERMODE_CENTER_UP_DOWN
  */
__STATIC_INLINE uint32_t TIM_Get_CounterMode(TIM_TypeDef *TIMx)
{
  uint32_t counter_mode;

  counter_mode = (uint32_t)(READ_BIT(TIMx->CR1, TIM_CR1_CMS));

  if (counter_mode == 0U)
  {
    counter_mode = (uint32_t)(READ_BIT(TIMx->CR1, TIM_CR1_DIR));
  }

  return counter_mode;
}

/**
  * @function  TIM_Get_CounterDirection
  * @brief  Get the current direction of the counter
  * @param  TIMx:
            @arg TIM Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref TIM_COUNTERMODE_UP
  *         @arg @ref TIM_COUNTERMODE_DOWN
  */
__STATIC_INLINE uint32_t TIM_Get_CounterDirection(TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_BIT(TIMx->CR1, TIM_CR1_DIR));
}

/**
  * @brief  Enable auto-reload (ARR) preload.
  * @rmtoll CR1          ARPE          TIM_EnableARRPreload
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Enable_ARRPreload(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->CR1, TIM_CR1_ARPE);
}

/**
  * @brief  Disable auto-reload (ARR) preload.
  * @rmtoll CR1          ARPE          TIM_DisableARRPreload
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Disable_ARRPreload(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->CR1, TIM_CR1_ARPE);
}

/**
  * @brief  Indicates whether auto-reload (ARR) preload is enabled.
  * @rmtoll CR1          ARPE          TIM_IsEnabledARRPreload
  * @param  TIMx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t TIM_Get_ARRPreload(TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->CR1, TIM_CR1_ARPE) == (TIM_CR1_ARPE)) ? 1UL : 0UL);
}

/**
  * @brief  Set the division ratio between the timer clock  and the sampling clock used by the dead-time generators
  *         (when supported) and the digital filters.
  * @note Macro IS_TIM_CLOCK_DIVISION_INSTANCE(TIMx) can be used to check
  *       whether or not the clock division feature is supported by the timer
  *       instance.
  * @rmtoll CR1          CKD           TIM_SetClockDivision
  * @param  TIMx Timer instance
  * @param  ClockDivision This parameter can be one of the following values:
  *         @arg @ref TIM_CLOCKDIVISION_DIV1
  *         @arg @ref TIM_CLOCKDIVISION_DIV2
  *         @arg @ref TIM_CLOCKDIVISION_DIV4
  * @retval None
  */
__STATIC_INLINE void TIM_Set_ClockDivision(TIM_TypeDef *TIMx, uint32_t ClockDivision)
{
  MODIFY_REG(TIMx->CR1, TIM_CR1_CKD, ClockDivision);
}

/**
  * @brief  Get the actual division ratio between the timer clock  and the sampling clock used by the dead-time
  *         generators (when supported) and the digital filters.
  * @note Macro IS_TIM_CLOCK_DIVISION_INSTANCE(TIMx) can be used to check
  *       whether or not the clock division feature is supported by the timer
  *       instance.
  * @rmtoll CR1          CKD           TIM_GetClockDivision
  * @param  TIMx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref TIM_CLOCKDIVISION_DIV1
  *         @arg @ref TIM_CLOCKDIVISION_DIV2
  *         @arg @ref TIM_CLOCKDIVISION_DIV4
  */
__STATIC_INLINE uint32_t TIM_Get_ClockDivision(TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_BIT(TIMx->CR1, TIM_CR1_CKD));
}

/**
  * @brief  Set the counter value.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note If dithering is activated, pay attention to the Counter value interpretation
  * @rmtoll CNT          CNT           TIM_SetCounter
  * @param  TIMx Timer instance
  * @param  Counter Counter value (between Min_Data=0 and Max_Data=0xFFFF or 0xFFFFFFFF)
  * @retval None
  */
__STATIC_INLINE void TIM_Set_Counter(TIM_TypeDef *TIMx, uint32_t Counter)
{
  WRITE_REG(TIMx->CNT, Counter);
}

/**
  * @brief  Get the counter value.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note If dithering is activated, pay attention to the Counter value interpretation
  * @rmtoll CNT          CNT           TIM_GetCounter
  * @param  TIMx Timer instance
  * @retval Counter value (between Min_Data=0 and Max_Data=0xFFFF or 0xFFFFFFFF)
  */
__STATIC_INLINE uint32_t TIM_Get_Counter(TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CNT));
}

/**
  * @brief  Set the prescaler value.
  * @note The counter clock frequency CK_CNT is equal to fCK_PSC / (PSC[15:0] + 1).
  * @note The prescaler can be changed on the fly as this control register is buffered. The new
  *       prescaler ratio is taken into account at the next update event.
  * @note Helper macro @ref __TIM_CALC_PSC can be used to calculate the Prescaler parameter
  * @rmtoll PSC          PSC           TIM_SetPrescaler
  * @param  TIMx Timer instance
  * @param  Prescaler between Min_Data=0 and Max_Data=65535
  * @retval None
  */
__STATIC_INLINE void TIM_Set_Prescaler(TIM_TypeDef *TIMx, uint32_t Prescaler)
{
  WRITE_REG(TIMx->PSC, Prescaler);
}

/**
  * @brief  Get the prescaler value.
  * @rmtoll PSC          PSC           TIM_GetPrescaler
  * @param  TIMx Timer instance
  * @retval  Prescaler value between Min_Data=0 and Max_Data=65535
  */
__STATIC_INLINE uint32_t TIM_Get_Prescaler(TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->PSC));
}

/**
  * @brief  Set the auto-reload value.
  * @note The counter is blocked while the auto-reload value is null.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Helper macro @ref __TIM_CALC_ARR can be used to calculate the AutoReload parameter
  *       In case dithering is activated,macro __TIM_CALC_ARR_DITHER can be used instead, to calculate the AutoReload
  *       parameter.
  * @rmtoll ARR          ARR           TIM_SetAutoReload
  * @param  TIMx Timer instance
  * @param  AutoReload between Min_Data=0 and Max_Data  TIM2/TIM3=0xFFFFFFFF  TIM6/TIM7/TIM15/TIM8=0xFFFF
  * @retval None
  */
__STATIC_INLINE void TIM_Set_AutoReload(TIM_TypeDef *TIMx, uint32_t AutoReload)
{
  WRITE_REG(TIMx->ARR, AutoReload);
}

/**
  * @brief  Get the auto-reload value.
  * @rmtoll ARR          ARR           TIM_GetAutoReload
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note If dithering is activated, pay attention to the returned value interpretation
  * @param  TIMx Timer instance
  * @retval Auto-reload value
  */
__STATIC_INLINE uint32_t TIM_Get_AutoReload(TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->ARR));
}

/**
  * @brief  Set the repetition counter value.
  * @note For advanced timer instances RepetitionCounter can be up to 65535.
  * @note Macro IS_TIM_REPETITION_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a repetition counter.
  * @rmtoll RCR          REP           TIM_SetRepetitionCounter
  * @param  TIMx Timer instance
  * @param  RepetitionCounter between Min_Data=0 and Max_Data=255 or 65535 for advanced timer.
  * @retval None
  */
__STATIC_INLINE void TIM_Set_RepetitionCounter(TIM_TypeDef *TIMx, uint32_t RepetitionCounter)
{
  WRITE_REG(TIMx->RCR, RepetitionCounter);
}

/**
  * @brief  Get the repetition counter value.
  * @note Macro IS_TIM_REPETITION_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a repetition counter.
  * @rmtoll RCR          REP           TIM_GetRepetitionCounter
  * @param  TIMx Timer instance
  * @retval Repetition counter value
  */
__STATIC_INLINE uint32_t TIM_Get_RepetitionCounter(TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->RCR));
}

/**
  * @brief  Force a continuous copy of the update interrupt flag (UIF) into the timer counter register (bit 31).
  * @note This allows both the counter value and a potential roll-over condition signalled by the UIFCPY flag to be read
  *       in an atomic way.
  * @rmtoll CR1          UIFREMAP      TIM_EnableUIFRemap
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Enable_UIFRemap(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->CR1, TIM_CR1_UIFREMAP);
}

/**
  * @brief  Disable update interrupt flag (UIF) remapping.
  * @rmtoll CR1          UIFREMAP      TIM_DisableUIFRemap
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Disable_UIFRemap(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->CR1, TIM_CR1_UIFREMAP);
}

/**
  * @brief  Indicate whether update interrupt flag (UIF) copy is set.
  * @param  Counter Counter value
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t TIM_Get_UIFCPY(TIM_TypeDef *TIMx)
{
  return (((TIMx->CNT & TIM_CNT_UIFCPY) == (TIM_CNT_UIFCPY)) ? 1UL : 0UL);
}

/**
  * @brief  Enable dithering.
  * @note Macro IS_TIM_DITHERING_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides dithering.
  * @rmtoll CR1          DITHEN          TIM_EnableDithering
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Enable_Dithering(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->CR1, TIM_CR1_DITHEN);
}

/**
  * @brief  Disable dithering.
  * @note Macro IS_TIM_DITHERING_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides dithering.
  * @rmtoll CR1          DITHEN          TIM_DisableDithering
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Disable_Dithering(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->CR1, TIM_CR1_DITHEN);
}

/**
  * @brief  Indicates whether dithering is activated.
  * @note Macro IS_TIM_DITHERING_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides dithering.
  * @rmtoll CR1          DITHEN          TIM_IsEnabledDithering
  * @param  TIMx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t TIM_Get_Dithering(TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->CR1, TIM_CR1_DITHEN) == (TIM_CR1_DITHEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable  the capture/compare control bits (CCxE, CCxNE and OCxM) preload.
  * @note CCxE, CCxNE and OCxM bits are preloaded, after having been written,
  *       they are updated only when a commutation event (COM) occurs.
  * @note Only on channels that have a complementary output.
  * @note Macro IS_TIM_COMMUTATION_EVENT_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance is able to generate a commutation event.
  * @rmtoll CR2          CCPC          TIM_CC_EnablePreload
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Enable_CC_Preload(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->CR2, TIM_CR2_CCPC);
}

/**
  * @brief  Disable  the capture/compare control bits (CCxE, CCxNE and OCxM) preload.
  * @note Macro IS_TIM_COMMUTATION_EVENT_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance is able to generate a commutation event.
  * @rmtoll CR2          CCPC          TIM_CC_DisablePreload
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Disable_CC_Preload(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->CR2, TIM_CR2_CCPC);
}

/**
  * @brief  Set the updated source of the capture/compare control bits (CCxE, CCxNE and OCxM).
  * @note Macro IS_TIM_COMMUTATION_EVENT_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance is able to generate a commutation event.
  * @rmtoll CR2          CCUS          TIM_CC_SetUpdate
  * @param  TIMx Timer instance
  * @param  CCUpdateSource This parameter can be one of the following values:
  *         @arg @ref TIM_CCUPDATESOURCE_COMG_ONLY
  *         @arg @ref TIM_CCUPDATESOURCE_COMG_AND_TRGI
  * @retval None
  */
__STATIC_INLINE void TIM_Set_CC_Update(TIM_TypeDef *TIMx, uint32_t CCUpdateSource)
{
  MODIFY_REG(TIMx->CR2, TIM_CR2_CCUS, CCUpdateSource);
}

/**
  * @brief  Set the lock level to freeze the
  *         configuration of several capture/compare parameters.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       the lock mechanism is supported by a timer instance.
  * @rmtoll BDTR         LOCK          TIM_CC_SetLockLevel
  * @param  TIMx Timer instance
  * @param  LockLevel This parameter can be one of the following values:
  *         @arg @ref TIM_LOCKLEVEL_OFF
  *         @arg @ref TIM_LOCKLEVEL_1
  *         @arg @ref TIM_LOCKLEVEL_2
  *         @arg @ref TIM_LOCKLEVEL_3
  * @retval None
  */
__STATIC_INLINE void TIM_Set_CC_LockLevel(TIM_TypeDef *TIMx, uint32_t LockLevel)
{
  MODIFY_REG(TIMx->BDTR, TIM_BDTR_LOCK, LockLevel);
}

/**
  * @brief  Enable capture/compare channels.
  * @rmtoll CCER         CC1E          TIM_CC_EnableChannel\n
  *         CCER         CC1NE         TIM_CC_EnableChannel\n
  *         CCER         CC2E          TIM_CC_EnableChannel\n
  *         CCER         CC2NE         TIM_CC_EnableChannel\n
  *         CCER         CC3E          TIM_CC_EnableChannel\n
  *         CCER         CC3NE         TIM_CC_EnableChannel\n
  *         CCER         CC4E          TIM_CC_EnableChannel\n
  *         CCER         CC5E          TIM_CC_EnableChannel\n
  *         CCER         CC6E          TIM_CC_EnableChannel
  * @param  TIMx Timer instance
  * @param  Channels This parameter can be a combination of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH1N
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH2N
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH3N
  *         @arg @ref TIM_CHANNEL_CH4
  *         @arg @ref TIM_CHANNEL_CH5
  *         @arg @ref TIM_CHANNEL_CH6
  * @retval None
  */
__STATIC_INLINE void TIM_Enable_CC_Channel(TIM_TypeDef *TIMx, uint32_t Channels)
{
  SET_BIT(TIMx->CCER, Channels);
}

/**
  * @brief  Disable capture/compare channels.
  * @rmtoll CCER         CC1E          TIM_CC_DisableChannel\n
  *         CCER         CC1NE         TIM_CC_DisableChannel\n
  *         CCER         CC2E          TIM_CC_DisableChannel\n
  *         CCER         CC2NE         TIM_CC_DisableChannel\n
  *         CCER         CC3E          TIM_CC_DisableChannel\n
  *         CCER         CC3NE         TIM_CC_DisableChannel\n
  *         CCER         CC4E          TIM_CC_DisableChannel\n
  *         CCER         CC5E          TIM_CC_DisableChannel\n
  *         CCER         CC6E          TIM_CC_DisableChannel
  * @param  TIMx Timer instance
  * @param  Channels This parameter can be a combination of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH1N
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH2N
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH3N
  *         @arg @ref TIM_CHANNEL_CH4
  *         @arg @ref TIM_CHANNEL_CH5
  *         @arg @ref TIM_CHANNEL_CH6
  * @retval None
  */
__STATIC_INLINE void TIM_Disable_CC_Channel(TIM_TypeDef *TIMx, uint32_t Channels)
{
  CLEAR_BIT(TIMx->CCER, Channels);
}

/**
  * @brief  Indicate whether channel(s) is(are) enabled.
  * @rmtoll CCER         CC1E          TIM_CC_IsEnabledChannel\n
  *         CCER         CC1NE         TIM_CC_IsEnabledChannel\n
  *         CCER         CC2E          TIM_CC_IsEnabledChannel\n
  *         CCER         CC2NE         TIM_CC_IsEnabledChannel\n
  *         CCER         CC3E          TIM_CC_IsEnabledChannel\n
  *         CCER         CC3NE         TIM_CC_IsEnabledChannel\n
  *         CCER         CC4E          TIM_CC_IsEnabledChannel\n
  *         CCER         CC5E          TIM_CC_IsEnabledChannel\n
  *         CCER         CC6E          TIM_CC_IsEnabledChannel
  * @param  TIMx Timer instance
  * @param  Channels This parameter can be a combination of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH1N
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH2N
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH3N
  *         @arg @ref TIM_CHANNEL_CH4
  *         @arg @ref TIM_CHANNEL_CH5
  *         @arg @ref TIM_CHANNEL_CH6
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t TIM_Get_CC_Channel(TIM_TypeDef *TIMx, uint32_t Channels)
{
  return ((READ_BIT(TIMx->CCER, Channels) == (Channels)) ? 1UL : 0UL);
}

/**
  * @brief  Define the behavior of the output reference signal OCxREF from which
  *         OCx and OCxN (when relevant) are derived.
  * @rmtoll CCMR1        OC1M          TIM_OC_SetMode\n
  *         CCMR1        OC2M          TIM_OC_SetMode\n
  *         CCMR2        OC3M          TIM_OC_SetMode\n
  *         CCMR2        OC4M          TIM_OC_SetMode\n
  *         CCMR3        OC5M          TIM_OC_SetMode\n
  *         CCMR3        OC6M          TIM_OC_SetMode
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH4
  *         @arg @ref TIM_CHANNEL_CH5
  *         @arg @ref TIM_CHANNEL_CH6
  * @param  Mode This parameter can be one of the following values:
  *         @arg @ref TIM_OCMODE_FROZEN
  *         @arg @ref TIM_OCMODE_ACTIVE
  *         @arg @ref TIM_OCMODE_INACTIVE
  *         @arg @ref TIM_OCMODE_TOGGLE
  *         @arg @ref TIM_OCMODE_FORCED_INACTIVE
  *         @arg @ref TIM_OCMODE_FORCED_ACTIVE
  *         @arg @ref TIM_OCMODE_PWM1
  *         @arg @ref TIM_OCMODE_PWM2
  *         @arg @ref TIM_OCMODE_RETRIG_OPM1
  *         @arg @ref TIM_OCMODE_RETRIG_OPM2
  *         @arg @ref TIM_OCMODE_COMBINED_PWM1
  *         @arg @ref TIM_OCMODE_COMBINED_PWM2
  *         @arg @ref TIM_OCMODE_ASSYMETRIC_PWM1
  *         @arg @ref TIM_OCMODE_ASSYMETRIC_PWM2
  *         @arg @ref TIM_OCMODE_PULSE_ON_COMPARE   (for channel 3 or channel 4 only)
  *         @arg @ref TIM_OCMODE_DIRECTION_OUTPUT   (for channel 3 or channel 4 only)
  * @retval None
  */
__STATIC_INLINE void TIM_Set_OC_Mode(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t Mode)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  MODIFY_REG(*pReg, ((TIM_CCMR1_OC1M  | TIM_CCMR1_CC1S) << SHIFT_TAB_OCxx[iChannel]), Mode << SHIFT_TAB_OCxx[iChannel]);
}

/**
  * @brief  Get the output compare mode of an output channel.
  * @rmtoll CCMR1        OC1M          TIM_OC_GetMode\n
  *         CCMR1        OC2M          TIM_OC_GetMode\n
  *         CCMR2        OC3M          TIM_OC_GetMode\n
  *         CCMR2        OC4M          TIM_OC_GetMode\n
  *         CCMR3        OC5M          TIM_OC_GetMode\n
  *         CCMR3        OC6M          TIM_OC_GetMode
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH4
  *         @arg @ref TIM_CHANNEL_CH5
  *         @arg @ref TIM_CHANNEL_CH6
  * @retval Returned value can be one of the following values:
  *         @arg @ref TIM_OCMODE_FROZEN
  *         @arg @ref TIM_OCMODE_ACTIVE
  *         @arg @ref TIM_OCMODE_INACTIVE
  *         @arg @ref TIM_OCMODE_TOGGLE
  *         @arg @ref TIM_OCMODE_FORCED_INACTIVE
  *         @arg @ref TIM_OCMODE_FORCED_ACTIVE
  *         @arg @ref TIM_OCMODE_PWM1
  *         @arg @ref TIM_OCMODE_PWM2
  *         @arg @ref TIM_OCMODE_RETRIG_OPM1
  *         @arg @ref TIM_OCMODE_RETRIG_OPM2
  *         @arg @ref TIM_OCMODE_COMBINED_PWM1
  *         @arg @ref TIM_OCMODE_COMBINED_PWM2
  *         @arg @ref TIM_OCMODE_ASSYMETRIC_PWM1
  *         @arg @ref TIM_OCMODE_ASSYMETRIC_PWM2
  *         @arg @ref TIM_OCMODE_PULSE_ON_COMPARE   (for channel 3 or channel 4 only)
  *         @arg @ref TIM_OCMODE_DIRECTION_OUTPUT   (for channel 3 or channel 4 only)
  */
__STATIC_INLINE uint32_t TIM_Get_OC_Mode(TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  return (READ_BIT(*pReg, ((TIM_CCMR1_OC1M | TIM_CCMR1_CC1S) << SHIFT_TAB_OCxx[iChannel])) >> SHIFT_TAB_OCxx[iChannel]);
}

/**
  * @brief  Set the polarity of an output channel.
  * @rmtoll CCER         CC1P          TIM_OC_SetPolarity\n
  *         CCER         CC1NP         TIM_OC_SetPolarity\n
  *         CCER         CC2P          TIM_OC_SetPolarity\n
  *         CCER         CC2NP         TIM_OC_SetPolarity\n
  *         CCER         CC3P          TIM_OC_SetPolarity\n
  *         CCER         CC3NP         TIM_OC_SetPolarity\n
  *         CCER         CC4P          TIM_OC_SetPolarity\n
  *         CCER         CC5P          TIM_OC_SetPolarity\n
  *         CCER         CC6P          TIM_OC_SetPolarity
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH1N
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH2N
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH3N
  *         @arg @ref TIM_CHANNEL_CH4
  *         @arg @ref TIM_CHANNEL_CH5
  *         @arg @ref TIM_CHANNEL_CH6
  * @param  Polarity This parameter can be one of the following values:
  *         @arg @ref TIM_OCPOLARITY_HIGH
  *         @arg @ref TIM_OCPOLARITY_LOW
  * @retval None
  */
__STATIC_INLINE void TIM_Set_OC_Polarity(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t Polarity)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  MODIFY_REG(TIMx->CCER, (TIM_CCER_CC1P << SHIFT_TAB_CCxP[iChannel]),  Polarity << SHIFT_TAB_CCxP[iChannel]);
}

/**
  * @brief  Get the polarity of an output channel.
  * @rmtoll CCER         CC1P          TIM_OC_GetPolarity\n
  *         CCER         CC1NP         TIM_OC_GetPolarity\n
  *         CCER         CC2P          TIM_OC_GetPolarity\n
  *         CCER         CC2NP         TIM_OC_GetPolarity\n
  *         CCER         CC3P          TIM_OC_GetPolarity\n
  *         CCER         CC3NP         TIM_OC_GetPolarity\n
  *         CCER         CC4P          TIM_OC_GetPolarity\n
  *         CCER         CC5P          TIM_OC_GetPolarity\n
  *         CCER         CC6P          TIM_OC_GetPolarity
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH1N
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH2N
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH3N
  *         @arg @ref TIM_CHANNEL_CH4
  *         @arg @ref TIM_CHANNEL_CH5
  *         @arg @ref TIM_CHANNEL_CH6
  * @retval Returned value can be one of the following values:
  *         @arg @ref TIM_OCPOLARITY_HIGH
  *         @arg @ref TIM_OCPOLARITY_LOW
  */
__STATIC_INLINE uint32_t TIM_Get_OC_Polarity(TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  return (READ_BIT(TIMx->CCER, (TIM_CCER_CC1P << SHIFT_TAB_CCxP[iChannel])) >> SHIFT_TAB_CCxP[iChannel]);
}

/**
  * @brief  Set the IDLE state of an output channel
  * @note This function is significant only for the timer instances
  *       supporting the break feature. Macro IS_TIM_BREAK_INSTANCE(TIMx)
  *       can be used to check whether or not a timer instance provides
  *       a break input.
  * @rmtoll CR2         OIS1          TIM_OC_SetIdleState\n
  *         CR2         OIS2N         TIM_OC_SetIdleState\n
  *         CR2         OIS2          TIM_OC_SetIdleState\n
  *         CR2         OIS2N         TIM_OC_SetIdleState\n
  *         CR2         OIS3          TIM_OC_SetIdleState\n
  *         CR2         OIS3N         TIM_OC_SetIdleState\n
  *         CR2         OIS4          TIM_OC_SetIdleState\n
  *         CR2         OIS5          TIM_OC_SetIdleState\n
  *         CR2         OIS6          TIM_OC_SetIdleState
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH1N
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH2N
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH3N
  *         @arg @ref TIM_CHANNEL_CH4
  *         @arg @ref TIM_CHANNEL_CH5
  *         @arg @ref TIM_CHANNEL_CH6
  * @param  IdleState This parameter can be one of the following values:
  *         @arg @ref TIM_OCIDLESTATE_SET
  *         @arg @ref TIM_OCIDLESTATE_RESET
  * @retval None
  */
__STATIC_INLINE void TIM_Set_OC_IdleState(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t IdleState)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  MODIFY_REG(TIMx->CR2, (TIM_CR2_OIS1 << SHIFT_TAB_OISx[iChannel]),  IdleState << SHIFT_TAB_OISx[iChannel]);
}

/**
  * @brief  Get the IDLE state of an output channel
  * @rmtoll CR2         OIS1          TIM_OC_GetIdleState\n
  *         CR2         OIS2N         TIM_OC_GetIdleState\n
  *         CR2         OIS2          TIM_OC_GetIdleState\n
  *         CR2         OIS2N         TIM_OC_GetIdleState\n
  *         CR2         OIS3          TIM_OC_GetIdleState\n
  *         CR2         OIS3N         TIM_OC_GetIdleState\n
  *         CR2         OIS4          TIM_OC_GetIdleState\n
  *         CR2         OIS5          TIM_OC_GetIdleState\n
  *         CR2         OIS6          TIM_OC_GetIdleState
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH1N
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH2N
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH3N
  *         @arg @ref TIM_CHANNEL_CH4
  *         @arg @ref TIM_CHANNEL_CH5
  *         @arg @ref TIM_CHANNEL_CH6
  * @retval Returned value can be one of the following values:
  *         @arg @ref TIM_OCIDLESTATE_SET
  *         @arg @ref TIM_OCIDLESTATE_RESET
  */
__STATIC_INLINE uint32_t TIM_Get_OC_IdleState(TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  return (READ_BIT(TIMx->CR2, (TIM_CR2_OIS1 << SHIFT_TAB_OISx[iChannel])) >> SHIFT_TAB_OISx[iChannel]);
}

/**
  * @brief  Enable fast mode for the output channel.
  * @note Acts only if the channel is configured in PWM1 or PWM2 mode.
  * @rmtoll CCMR1        OC1FE          TIM_OC_EnableFast\n
  *         CCMR1        OC2FE          TIM_OC_EnableFast\n
  *         CCMR2        OC3FE          TIM_OC_EnableFast\n
  *         CCMR2        OC4FE          TIM_OC_EnableFast\n
  *         CCMR3        OC5FE          TIM_OC_EnableFast\n
  *         CCMR3        OC6FE          TIM_OC_EnableFast
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH4
  *         @arg @ref TIM_CHANNEL_CH5
  *         @arg @ref TIM_CHANNEL_CH6
  * @retval None
  */
__STATIC_INLINE void TIM_Enable_OC_Fast(TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  SET_BIT(*pReg, (TIM_CCMR1_OC1FE << SHIFT_TAB_OCxx[iChannel]));

}

/**
  * @brief  Disable fast mode for the output channel.
  * @rmtoll CCMR1        OC1FE          TIM_OC_DisableFast\n
  *         CCMR1        OC2FE          TIM_OC_DisableFast\n
  *         CCMR2        OC3FE          TIM_OC_DisableFast\n
  *         CCMR2        OC4FE          TIM_OC_DisableFast\n
  *         CCMR3        OC5FE          TIM_OC_DisableFast\n
  *         CCMR3        OC6FE          TIM_OC_DisableFast
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH4
  *         @arg @ref TIM_CHANNEL_CH5
  *         @arg @ref TIM_CHANNEL_CH6
  * @retval None
  */
__STATIC_INLINE void TIM_Disable_OC_Fast(TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  CLEAR_BIT(*pReg, (TIM_CCMR1_OC1FE << SHIFT_TAB_OCxx[iChannel]));

}

/**
  * @brief  Indicates whether fast mode is enabled for the output channel.
  * @rmtoll CCMR1        OC1FE          TIM_OC_IsEnabledFast\n
  *         CCMR1        OC2FE          TIM_OC_IsEnabledFast\n
  *         CCMR2        OC3FE          TIM_OC_IsEnabledFast\n
  *         CCMR2        OC4FE          TIM_OC_IsEnabledFast\n
  *         CCMR3        OC5FE          TIM_OC_IsEnabledFast\n
  *         CCMR3        OC6FE          TIM_OC_IsEnabledFast
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH4
  *         @arg @ref TIM_CHANNEL_CH5
  *         @arg @ref TIM_CHANNEL_CH6
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t TIM_Get_OC_Fast(TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  uint32_t bitfield = TIM_CCMR1_OC1FE << SHIFT_TAB_OCxx[iChannel];
  return ((READ_BIT(*pReg, bitfield) == bitfield) ? 1UL : 0UL);
}

/**
  * @brief  Enable compare register (TIMx_CCRx) preload for the output channel.
  * @rmtoll CCMR1        OC1PE          TIM_OC_EnablePreload\n
  *         CCMR1        OC2PE          TIM_OC_EnablePreload\n
  *         CCMR2        OC3PE          TIM_OC_EnablePreload\n
  *         CCMR2        OC4PE          TIM_OC_EnablePreload\n
  *         CCMR3        OC5PE          TIM_OC_EnablePreload\n
  *         CCMR3        OC6PE          TIM_OC_EnablePreload
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH4
  *         @arg @ref TIM_CHANNEL_CH5
  *         @arg @ref TIM_CHANNEL_CH6
  * @retval None
  */
__STATIC_INLINE void TIM_Enable_OC_Preload(TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  SET_BIT(*pReg, (TIM_CCMR1_OC1PE << SHIFT_TAB_OCxx[iChannel]));
}

/**
  * @brief  Disable compare register (TIMx_CCRx) preload for the output channel.
  * @rmtoll CCMR1        OC1PE          TIM_OC_DisablePreload\n
  *         CCMR1        OC2PE          TIM_OC_DisablePreload\n
  *         CCMR2        OC3PE          TIM_OC_DisablePreload\n
  *         CCMR2        OC4PE          TIM_OC_DisablePreload\n
  *         CCMR3        OC5PE          TIM_OC_DisablePreload\n
  *         CCMR3        OC6PE          TIM_OC_DisablePreload
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH4
  *         @arg @ref TIM_CHANNEL_CH5
  *         @arg @ref TIM_CHANNEL_CH6
  * @retval None
  */
__STATIC_INLINE void TIM_Disable_OC_Preload(TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  CLEAR_BIT(*pReg, (TIM_CCMR1_OC1PE << SHIFT_TAB_OCxx[iChannel]));
}

/**
  * @brief  Indicates whether compare register (TIMx_CCRx) preload is enabled for the output channel.
  * @rmtoll CCMR1        OC1PE          TIM_OC_IsEnabledPreload\n
  *         CCMR1        OC2PE          TIM_OC_IsEnabledPreload\n
  *         CCMR2        OC3PE          TIM_OC_IsEnabledPreload\n
  *         CCMR2        OC4PE          TIM_OC_IsEnabledPreload\n
  *         CCMR3        OC5PE          TIM_OC_IsEnabledPreload\n
  *         CCMR3        OC6PE          TIM_OC_IsEnabledPreload
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH4
  *         @arg @ref TIM_CHANNEL_CH5
  *         @arg @ref TIM_CHANNEL_CH6
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t TIM_Get_OC_Preload(TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  uint32_t bitfield = TIM_CCMR1_OC1PE << SHIFT_TAB_OCxx[iChannel];
  return ((READ_BIT(*pReg, bitfield) == bitfield) ? 1UL : 0UL);
}

/**
  * @brief  Enable clearing the output channel on an external event.
  * @note This function can only be used in Output compare and PWM modes. It does not work in Forced mode.
  * @note Macro IS_TIM_OCXREF_CLEAR_INSTANCE(TIMx) can be used to check whether
  *       or not a timer instance can clear the OCxREF signal on an external event.
  * @rmtoll CCMR1        OC1CE          TIM_OC_EnableClear\n
  *         CCMR1        OC2CE          TIM_OC_EnableClear\n
  *         CCMR2        OC3CE          TIM_OC_EnableClear\n
  *         CCMR2        OC4CE          TIM_OC_EnableClear\n
  *         CCMR3        OC5CE          TIM_OC_EnableClear\n
  *         CCMR3        OC6CE          TIM_OC_EnableClear
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH4
  *         @arg @ref TIM_CHANNEL_CH5
  *         @arg @ref TIM_CHANNEL_CH6
  * @retval None
  */
__STATIC_INLINE void TIM_Enable_OC_Clear(TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  SET_BIT(*pReg, (TIM_CCMR1_OC1CE << SHIFT_TAB_OCxx[iChannel]));
}

/**
  * @brief  Disable clearing the output channel on an external event.
  * @note Macro IS_TIM_OCXREF_CLEAR_INSTANCE(TIMx) can be used to check whether
  *       or not a timer instance can clear the OCxREF signal on an external event.
  * @rmtoll CCMR1        OC1CE          TIM_OC_DisableClear\n
  *         CCMR1        OC2CE          TIM_OC_DisableClear\n
  *         CCMR2        OC3CE          TIM_OC_DisableClear\n
  *         CCMR2        OC4CE          TIM_OC_DisableClear\n
  *         CCMR3        OC5CE          TIM_OC_DisableClear\n
  *         CCMR3        OC6CE          TIM_OC_DisableClear
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH4
  *         @arg @ref TIM_CHANNEL_CH5
  *         @arg @ref TIM_CHANNEL_CH6
  * @retval None
  */
__STATIC_INLINE void TIM_Disable_OC_Clear(TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  CLEAR_BIT(*pReg, (TIM_CCMR1_OC1CE << SHIFT_TAB_OCxx[iChannel]));
}

/**
  * @brief  Indicates clearing the output channel on an external event is enabled for the output channel.
  * @note This function enables clearing the output channel on an external event.
  * @note This function can only be used in Output compare and PWM modes. It does not work in Forced mode.
  * @note Macro IS_TIM_OCXREF_CLEAR_INSTANCE(TIMx) can be used to check whether
  *       or not a timer instance can clear the OCxREF signal on an external event.
  * @rmtoll CCMR1        OC1CE          TIM_OC_IsEnabledClear\n
  *         CCMR1        OC2CE          TIM_OC_IsEnabledClear\n
  *         CCMR2        OC3CE          TIM_OC_IsEnabledClear\n
  *         CCMR2        OC4CE          TIM_OC_IsEnabledClear\n
  *         CCMR3        OC5CE          TIM_OC_IsEnabledClear\n
  *         CCMR3        OC6CE          TIM_OC_IsEnabledClear
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH4
  *         @arg @ref TIM_CHANNEL_CH5
  *         @arg @ref TIM_CHANNEL_CH6
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t TIM_Get_OC_Clear(TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  uint32_t bitfield = TIM_CCMR1_OC1CE << SHIFT_TAB_OCxx[iChannel];
  return ((READ_BIT(*pReg, bitfield) == bitfield) ? 1UL : 0UL);
}

/**
  * @brief  Set the dead-time delay (delay inserted between the rising edge of the OCxREF signal and the rising edge of
  *         the Ocx and OCxN signals).
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       dead-time insertion feature is supported by a timer instance.
  * @note Helper macro @ref __TIM_CALC_DEADTIME can be used to calculate the DeadTime parameter
  * @rmtoll BDTR         DTG           TIM_OC_SetDeadTime
  * @param  TIMx Timer instance
  * @param  DeadTime between Min_Data=0 and Max_Data=255
  * @retval None
  */
__STATIC_INLINE void TIM_Set_OC_DeadTime(TIM_TypeDef *TIMx, uint32_t DeadTime)
{
  MODIFY_REG(TIMx->BDTR, TIM_BDTR_DTG, DeadTime);
}

/**
  * @brief  Set compare value for output channel 1 (TIMx_CCR1).
  * @note In 32-bit timer implementations compare value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC1_INSTANCE(TIMx) can be used to check whether or not
  *       output channel 1 is supported by a timer instance.
  * @note If dithering is activated, CompareValue can be calculated with macro @ref __TIM_CALC_DELAY_DITHER .
  * @rmtoll CCR1         CCR1          TIM_OC_SetCompareCH1
  * @param  TIMx Timer instance
  * @param  CompareValue between Min_Data=0 and Max_Data=65535
  * @retval None
  */
__STATIC_INLINE void TIM_Set_OC_CompareCH1(TIM_TypeDef *TIMx, uint32_t CompareValue)
{
  WRITE_REG(TIMx->CCR1, CompareValue);
}

/**
  * @brief  Set compare value for output channel 2 (TIMx_CCR2).
  * @note In 32-bit timer implementations compare value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC2_INSTANCE(TIMx) can be used to check whether or not
  *       output channel 2 is supported by a timer instance.
  * @note If dithering is activated, CompareValue can be calculated with macro @ref __TIM_CALC_DELAY_DITHER .
  * @rmtoll CCR2         CCR2          TIM_OC_SetCompareCH2
  * @param  TIMx Timer instance
  * @param  CompareValue between Min_Data=0 and Max_Data=65535
  * @retval None
  */
__STATIC_INLINE void TIM_Set_OC_CompareCH2(TIM_TypeDef *TIMx, uint32_t CompareValue)
{
  WRITE_REG(TIMx->CCR2, CompareValue);
}

/**
  * @brief  Set compare value for output channel 3 (TIMx_CCR3).
  * @note In 32-bit timer implementations compare value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC3_INSTANCE(TIMx) can be used to check whether or not
  *       output channel is supported by a timer instance.
  * @note If dithering is activated, CompareValue can be calculated with macro @ref __TIM_CALC_DELAY_DITHER .
  * @rmtoll CCR3         CCR3          TIM_OC_SetCompareCH3
  * @param  TIMx Timer instance
  * @param  CompareValue between Min_Data=0 and Max_Data=65535
  * @retval None
  */
__STATIC_INLINE void TIM_Set_OC_CompareCH3(TIM_TypeDef *TIMx, uint32_t CompareValue)
{
  WRITE_REG(TIMx->CCR3, CompareValue);
}

/**
  * @brief  Set compare value for output channel 4 (TIMx_CCR4).
  * @note In 32-bit timer implementations compare value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC4_INSTANCE(TIMx) can be used to check whether or not
  *       output channel 4 is supported by a timer instance.
  * @note If dithering is activated, CompareValue can be calculated with macro @ref __TIM_CALC_DELAY_DITHER .
  * @rmtoll CCR4         CCR4          TIM_OC_SetCompareCH4
  * @param  TIMx Timer instance
  * @param  CompareValue between Min_Data=0 and Max_Data=65535
  * @retval None
  */
__STATIC_INLINE void TIM_Set_OC_CompareCH4(TIM_TypeDef *TIMx, uint32_t CompareValue)
{
  WRITE_REG(TIMx->CCR4, CompareValue);
}

/**
  * @brief  Set compare value for output channel 5 (TIMx_CCR5).
  * @note Macro IS_TIM_CC5_INSTANCE(TIMx) can be used to check whether or not
  *       output channel 5 is supported by a timer instance.
  * @note If dithering is activated, CompareValue can be calculated with macro @ref __TIM_CALC_DELAY_DITHER .
  * @rmtoll CCR5         CCR5          TIM_OC_SetCompareCH5
  * @param  TIMx Timer instance
  * @param  CompareValue between Min_Data=0 and Max_Data=65535
  * @retval None
  */
__STATIC_INLINE void TIM_Set_OC_CompareCH5(TIM_TypeDef *TIMx, uint32_t CompareValue)
{
  MODIFY_REG(TIMx->CCR5, TIM_CCR5_CCR5, CompareValue);
}

/**
  * @brief  Set compare value for output channel 6 (TIMx_CCR6).
  * @note Macro IS_TIM_CC6_INSTANCE(TIMx) can be used to check whether or not
  *       output channel 6 is supported by a timer instance.
  * @note If dithering is activated, CompareValue can be calculated with macro @ref __TIM_CALC_DELAY_DITHER .
  * @rmtoll CCR6         CCR6          TIM_OC_SetCompareCH6
  * @param  TIMx Timer instance
  * @param  CompareValue between Min_Data=0 and Max_Data=65535
  * @retval None
  */
__STATIC_INLINE void TIM_Set_OC_CompareCH6(TIM_TypeDef *TIMx, uint32_t CompareValue)
{
  WRITE_REG(TIMx->CCR6, CompareValue);
}

/**
  * @brief  Get compare value (TIMx_CCR1) set for  output channel 1.
  * @note In 32-bit timer implementations returned compare value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC1_INSTANCE(TIMx) can be used to check whether or not
  *       output channel 1 is supported by a timer instance.
  * @note If dithering is activated, pay attention to the returned value interpretation.
  * @rmtoll CCR1         CCR1          TIM_OC_GetCompareCH1
  * @param  TIMx Timer instance
  * @retval CompareValue (between Min_Data=0 and Max_Data=65535)
  */
__STATIC_INLINE uint32_t TIM_Get_OC_CompareCH1(TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CCR1));
}

/**
  * @brief  Get compare value (TIMx_CCR2) set for  output channel 2.
  * @note In 32-bit timer implementations returned compare value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC2_INSTANCE(TIMx) can be used to check whether or not
  *       output channel 2 is supported by a timer instance.
  * @note If dithering is activated, pay attention to the returned value interpretation.
  * @rmtoll CCR2         CCR2          TIM_OC_GetCompareCH2
  * @param  TIMx Timer instance
  * @retval CompareValue (between Min_Data=0 and Max_Data=65535)
  */
__STATIC_INLINE uint32_t TIM_Get_OC_CompareCH2(TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CCR2));
}

/**
  * @brief  Get compare value (TIMx_CCR3) set for  output channel 3.
  * @note In 32-bit timer implementations returned compare value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC3_INSTANCE(TIMx) can be used to check whether or not
  *       output channel 3 is supported by a timer instance.
  * @note If dithering is activated, pay attention to the returned value interpretation.
  * @rmtoll CCR3         CCR3          TIM_OC_GetCompareCH3
  * @param  TIMx Timer instance
  * @retval CompareValue (between Min_Data=0 and Max_Data=65535)
  */
__STATIC_INLINE uint32_t TIM_Get_OC_CompareCH3(TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CCR3));
}

/**
  * @brief  Get compare value (TIMx_CCR4) set for  output channel 4.
  * @note In 32-bit timer implementations returned compare value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC4_INSTANCE(TIMx) can be used to check whether or not
  *       output channel 4 is supported by a timer instance.
  * @note If dithering is activated, pay attention to the returned value interpretation.
  * @rmtoll CCR4         CCR4          TIM_OC_GetCompareCH4
  * @param  TIMx Timer instance
  * @retval CompareValue (between Min_Data=0 and Max_Data=65535)
  */
__STATIC_INLINE uint32_t TIM_Get_OC_CompareCH4(TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CCR4));
}

/**
  * @brief  Get compare value (TIMx_CCR5) set for  output channel 5.
  * @note Macro IS_TIM_CC5_INSTANCE(TIMx) can be used to check whether or not
  *       output channel 5 is supported by a timer instance.
  * @note If dithering is activated, pay attention to the returned value interpretation.
  * @rmtoll CCR5         CCR5          TIM_OC_GetCompareCH5
  * @param  TIMx Timer instance
  * @retval CompareValue (between Min_Data=0 and Max_Data=65535)
  */
__STATIC_INLINE uint32_t TIM_Get_OC_CompareCH5(TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_BIT(TIMx->CCR5, TIM_CCR5_CCR5));
}

/**
  * @brief  Get compare value (TIMx_CCR6) set for  output channel 6.
  * @note Macro IS_TIM_CC6_INSTANCE(TIMx) can be used to check whether or not
  *       output channel 6 is supported by a timer instance.
  * @note If dithering is activated, pay attention to the returned value interpretation.
  * @rmtoll CCR6         CCR6          TIM_OC_GetCompareCH6
  * @param  TIMx Timer instance
  * @retval CompareValue (between Min_Data=0 and Max_Data=65535)
  */
__STATIC_INLINE uint32_t TIM_Get_OC_CompareCH6(TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CCR6));
}

/**
  * @brief  Select on which reference signal the OC5REF is combined to.
  * @note Macro IS_TIM_COMBINED3PHASEPWM_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports the combined 3-phase PWM mode.
  * @rmtoll CCR5         GC5C3          TIM_SetCH5CombinedChannels\n
  *         CCR5         GC5C2          TIM_SetCH5CombinedChannels\n
  *         CCR5         GC5C1          TIM_SetCH5CombinedChannels
  * @param  TIMx Timer instance
  * @param  GroupCH5 This parameter can be a combination of the following values:
  *         @arg @ref TIM_GROUPCH5_NONE
  *         @arg @ref TIM_GROUPCH5_OC1REFC
  *         @arg @ref TIM_GROUPCH5_OC2REFC
  *         @arg @ref TIM_GROUPCH5_OC3REFC
  * @retval None
  */
__STATIC_INLINE void TIM_Set_CH5CombinedChannels(TIM_TypeDef *TIMx, uint32_t GroupCH5)
{
  MODIFY_REG(TIMx->CCR5, (TIM_CCR5_GC5C3 | TIM_CCR5_GC5C2 | TIM_CCR5_GC5C1), GroupCH5);
}

/**
  * @brief  Set the pulse on compare pulse width prescaler.
  * @note Macro IS_TIM_PULSEONCOMPARE_INSTANCE(TIMx) can be used to check
  *       whether or not the pulse on compare feature is supported by the timer
  *       instance.
  * @rmtoll ECR          PWPRSC           TIM_OC_SetPulseWidthPrescaler
  * @param  TIMx Timer instance
  * @param  PulseWidthPrescaler This parameter can be one of the following values:
  *         @arg @ref TIM_PWPRSC_X1
  *         @arg @ref TIM_PWPRSC_X2
  *         @arg @ref TIM_PWPRSC_X4
  *         @arg @ref TIM_PWPRSC_X8
  *         @arg @ref TIM_PWPRSC_X16
  *         @arg @ref TIM_PWPRSC_X32
  *         @arg @ref TIM_PWPRSC_X64
  *         @arg @ref TIM_PWPRSC_X128
  * @retval None
  */
__STATIC_INLINE void TIM_OC_Set_PulseWidthPrescaler(TIM_TypeDef *TIMx, uint32_t PulseWidthPrescaler)
{
  MODIFY_REG(TIMx->ECR, TIM_ECR_PWPRSC, PulseWidthPrescaler);
}

/**
  * @brief  Get the pulse on compare pulse width prescaler.
  * @note Macro IS_TIM_PULSEONCOMPARE_INSTANCE(TIMx) can be used to check
  *       whether or not the pulse on compare feature is supported by the timer
  *       instance.
  * @rmtoll ECR          PWPRSC           TIM_OC_GetPulseWidthPrescaler
  * @param  TIMx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref TIM_PWPRSC_X1
  *         @arg @ref TIM_PWPRSC_X2
  *         @arg @ref TIM_PWPRSC_X4
  *         @arg @ref TIM_PWPRSC_X8
  *         @arg @ref TIM_PWPRSC_X16
  *         @arg @ref TIM_PWPRSC_X32
  *         @arg @ref TIM_PWPRSC_X64
  *         @arg @ref TIM_PWPRSC_X128
  */
__STATIC_INLINE uint32_t TIM_OC_Get_PulseWidthPrescaler(TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_BIT(TIMx->ECR, TIM_ECR_PWPRSC));
}

/**
  * @brief  Set the pulse on compare pulse width duration.
  * @note Macro IS_TIM_PULSEONCOMPARE_INSTANCE(TIMx) can be used to check
  *       whether or not the pulse on compare feature is supported by the timer
  *       instance.
  * @rmtoll ECR          PW           TIM_OC_SetPulseWidth
  * @param  TIMx Timer instance
  * @param  PulseWidth This parameter can be between Min_Data=0 and Max_Data=255
  * @retval None
  */
__STATIC_INLINE void TIM_OC_Set_PulseWidth(TIM_TypeDef *TIMx, uint32_t PulseWidth)
{
  MODIFY_REG(TIMx->ECR, TIM_ECR_PW, PulseWidth << TIM_ECR_PW_Pos);
}

/**
  * @brief  Get the pulse on compare pulse width duration.
  * @note Macro IS_TIM_PULSEONCOMPARE_INSTANCE(TIMx) can be used to check
  *       whether or not the pulse on compare feature is supported by the timer
  *       instance.
  * @rmtoll ECR          PW           TIM_OC_GetPulseWidth
  * @param  TIMx Timer instance
  * @retval Returned value can be between Min_Data=0 and Max_Data=255:
  */
__STATIC_INLINE uint32_t TIM_OC_Get_PulseWidth(TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_BIT(TIMx->ECR, TIM_ECR_PW));
}

/**
  * @brief  Set the active input.
  * @rmtoll CCMR1        CC1S          TIM_IC_SetActiveInput\n
  *         CCMR1        CC2S          TIM_IC_SetActiveInput\n
  *         CCMR2        CC3S          TIM_IC_SetActiveInput\n
  *         CCMR2        CC4S          TIM_IC_SetActiveInput
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH4
  * @param  ICActiveInput This parameter can be one of the following values:
  *         @arg @ref TIM_ACTIVEINPUT_DIRECTTI
  *         @arg @ref TIM_ACTIVEINPUT_INDIRECTTI
  *         @arg @ref TIM_ACTIVEINPUT_TRC
  * @retval None
  */
__STATIC_INLINE void TIM_Set_IC_ActiveInput(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t ICActiveInput)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  MODIFY_REG(*pReg, ((TIM_CCMR1_CC1S) << SHIFT_TAB_ICxx[iChannel]), (ICActiveInput >> 16U) << SHIFT_TAB_ICxx[iChannel]);
}

/**
  * @brief  Get the current active input.
  * @rmtoll CCMR1        CC1S          TIM_IC_GetActiveInput\n
  *         CCMR1        CC2S          TIM_IC_GetActiveInput\n
  *         CCMR2        CC3S          TIM_IC_GetActiveInput\n
  *         CCMR2        CC4S          TIM_IC_GetActiveInput
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH4
  * @retval Returned value can be one of the following values:
  *         @arg @ref TIM_ACTIVEINPUT_DIRECTTI
  *         @arg @ref TIM_ACTIVEINPUT_INDIRECTTI
  *         @arg @ref TIM_ACTIVEINPUT_TRC
  */
__STATIC_INLINE uint32_t TIM_Get_IC_ActiveInput(TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  return ((READ_BIT(*pReg, ((TIM_CCMR1_CC1S) << SHIFT_TAB_ICxx[iChannel])) >> SHIFT_TAB_ICxx[iChannel]) << 16U);
}

/**
  * @brief  Set the prescaler of input channel.
  * @rmtoll CCMR1        IC1PSC        TIM_IC_SetPrescaler\n
  *         CCMR1        IC2PSC        TIM_IC_SetPrescaler\n
  *         CCMR2        IC3PSC        TIM_IC_SetPrescaler\n
  *         CCMR2        IC4PSC        TIM_IC_SetPrescaler
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH4
  * @param  ICPrescaler This parameter can be one of the following values:
  *         @arg @ref TIM_ICPSC_DIV1
  *         @arg @ref TIM_ICPSC_DIV2
  *         @arg @ref TIM_ICPSC_DIV4
  *         @arg @ref TIM_ICPSC_DIV8
  * @retval None
  */
__STATIC_INLINE void TIM_Set_IC_Prescaler(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t ICPrescaler)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  MODIFY_REG(*pReg, ((TIM_CCMR1_IC1PSC) << SHIFT_TAB_ICxx[iChannel]), (ICPrescaler >> 16U) << SHIFT_TAB_ICxx[iChannel]);
}

/**
  * @brief  Get the current prescaler value acting on an  input channel.
  * @rmtoll CCMR1        IC1PSC        TIM_IC_GetPrescaler\n
  *         CCMR1        IC2PSC        TIM_IC_GetPrescaler\n
  *         CCMR2        IC3PSC        TIM_IC_GetPrescaler\n
  *         CCMR2        IC4PSC        TIM_IC_GetPrescaler
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH4
  * @retval Returned value can be one of the following values:
  *         @arg @ref TIM_ICPSC_DIV1
  *         @arg @ref TIM_ICPSC_DIV2
  *         @arg @ref TIM_ICPSC_DIV4
  *         @arg @ref TIM_ICPSC_DIV8
  */
__STATIC_INLINE uint32_t TIM_Get_IC_Prescaler(TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  return ((READ_BIT(*pReg, ((TIM_CCMR1_IC1PSC) << SHIFT_TAB_ICxx[iChannel])) >> SHIFT_TAB_ICxx[iChannel]) << 16U);
}

/**
  * @brief  Set the input filter duration.
  * @rmtoll CCMR1        IC1F          TIM_IC_SetFilter\n
  *         CCMR1        IC2F          TIM_IC_SetFilter\n
  *         CCMR2        IC3F          TIM_IC_SetFilter\n
  *         CCMR2        IC4F          TIM_IC_SetFilter
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH4
  * @param  ICFilter This parameter can be one of the following values:
  *         @arg @ref TIM_IC_FILTER_FDIV1
  *         @arg @ref TIM_IC_FILTER_FDIV1_N2
  *         @arg @ref TIM_IC_FILTER_FDIV1_N4
  *         @arg @ref TIM_IC_FILTER_FDIV1_N8
  *         @arg @ref TIM_IC_FILTER_FDIV2_N6
  *         @arg @ref TIM_IC_FILTER_FDIV2_N8
  *         @arg @ref TIM_IC_FILTER_FDIV4_N6
  *         @arg @ref TIM_IC_FILTER_FDIV4_N8
  *         @arg @ref TIM_IC_FILTER_FDIV8_N6
  *         @arg @ref TIM_IC_FILTER_FDIV8_N8
  *         @arg @ref TIM_IC_FILTER_FDIV16_N5
  *         @arg @ref TIM_IC_FILTER_FDIV16_N6
  *         @arg @ref TIM_IC_FILTER_FDIV16_N8
  *         @arg @ref TIM_IC_FILTER_FDIV32_N5
  *         @arg @ref TIM_IC_FILTER_FDIV32_N6
  *         @arg @ref TIM_IC_FILTER_FDIV32_N8
  * @retval None
  */
__STATIC_INLINE void TIM_Set_IC_Filter(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t ICFilter)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  MODIFY_REG(*pReg, ((TIM_CCMR1_IC1F) << SHIFT_TAB_ICxx[iChannel]), (ICFilter >> 16U) << SHIFT_TAB_ICxx[iChannel]);
}

/**
  * @brief  Get the input filter duration.
  * @rmtoll CCMR1        IC1F          TIM_IC_GetFilter\n
  *         CCMR1        IC2F          TIM_IC_GetFilter\n
  *         CCMR2        IC3F          TIM_IC_GetFilter\n
  *         CCMR2        IC4F          TIM_IC_GetFilter
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH4
  * @retval Returned value can be one of the following values:
  *         @arg @ref TIM_IC_FILTER_FDIV1
  *         @arg @ref TIM_IC_FILTER_FDIV1_N2
  *         @arg @ref TIM_IC_FILTER_FDIV1_N4
  *         @arg @ref TIM_IC_FILTER_FDIV1_N8
  *         @arg @ref TIM_IC_FILTER_FDIV2_N6
  *         @arg @ref TIM_IC_FILTER_FDIV2_N8
  *         @arg @ref TIM_IC_FILTER_FDIV4_N6
  *         @arg @ref TIM_IC_FILTER_FDIV4_N8
  *         @arg @ref TIM_IC_FILTER_FDIV8_N6
  *         @arg @ref TIM_IC_FILTER_FDIV8_N8
  *         @arg @ref TIM_IC_FILTER_FDIV16_N5
  *         @arg @ref TIM_IC_FILTER_FDIV16_N6
  *         @arg @ref TIM_IC_FILTER_FDIV16_N8
  *         @arg @ref TIM_IC_FILTER_FDIV32_N5
  *         @arg @ref TIM_IC_FILTER_FDIV32_N6
  *         @arg @ref TIM_IC_FILTER_FDIV32_N8
  */
__STATIC_INLINE uint32_t TIM_Get_IC_Filter(TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  const __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->CCMR1) + OFFSET_TAB_CCMRx[iChannel]));
  return ((READ_BIT(*pReg, ((TIM_CCMR1_IC1F) << SHIFT_TAB_ICxx[iChannel])) >> SHIFT_TAB_ICxx[iChannel]) << 16U);
}

/**
  * @brief  Set the input channel polarity.
  * @rmtoll CCER         CC1P          TIM_IC_SetPolarity\n
  *         CCER         CC1NP         TIM_IC_SetPolarity\n
  *         CCER         CC2P          TIM_IC_SetPolarity\n
  *         CCER         CC2NP         TIM_IC_SetPolarity\n
  *         CCER         CC3P          TIM_IC_SetPolarity\n
  *         CCER         CC3NP         TIM_IC_SetPolarity\n
  *         CCER         CC4P          TIM_IC_SetPolarity\n
  *         CCER         CC4NP         TIM_IC_SetPolarity
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH4
  * @param  ICPolarity This parameter can be one of the following values:
  *         @arg @ref TIM_IC_POLARITY_RISING
  *         @arg @ref TIM_IC_POLARITY_FALLING
  *         @arg @ref TIM_IC_POLARITY_BOTHEDGE
  * @retval None
  */
__STATIC_INLINE void TIM_Set_IC_Polarity(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t ICPolarity)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  MODIFY_REG(TIMx->CCER, ((TIM_CCER_CC1NP | TIM_CCER_CC1P) << SHIFT_TAB_CCxP[iChannel]),
             ICPolarity << SHIFT_TAB_CCxP[iChannel]);
}

/**
  * @brief  Get the current input channel polarity.
  * @rmtoll CCER         CC1P          TIM_IC_GetPolarity\n
  *         CCER         CC1NP         TIM_IC_GetPolarity\n
  *         CCER         CC2P          TIM_IC_GetPolarity\n
  *         CCER         CC2NP         TIM_IC_GetPolarity\n
  *         CCER         CC3P          TIM_IC_GetPolarity\n
  *         CCER         CC3NP         TIM_IC_GetPolarity\n
  *         CCER         CC4P          TIM_IC_GetPolarity\n
  *         CCER         CC4NP         TIM_IC_GetPolarity
  * @param  TIMx Timer instance
  * @param  Channel This parameter can be one of the following values:
  *         @arg @ref TIM_CHANNEL_CH1
  *         @arg @ref TIM_CHANNEL_CH2
  *         @arg @ref TIM_CHANNEL_CH3
  *         @arg @ref TIM_CHANNEL_CH4
  * @retval Returned value can be one of the following values:
  *         @arg @ref TIM_IC_POLARITY_RISING
  *         @arg @ref TIM_IC_POLARITY_FALLING
  *         @arg @ref TIM_IC_POLARITY_BOTHEDGE
  */
__STATIC_INLINE uint32_t TIM_Get_IC_Polarity(TIM_TypeDef *TIMx, uint32_t Channel)
{
  uint8_t iChannel = TIM_GET_CHANNEL_INDEX(Channel);
  return (READ_BIT(TIMx->CCER, ((TIM_CCER_CC1NP | TIM_CCER_CC1P) << SHIFT_TAB_CCxP[iChannel])) >>
          SHIFT_TAB_CCxP[iChannel]);
}

/**
  * @brief  Connect the TIMx_CH1, CH2 and CH3 pins  to the TI1 input (XOR combination).
  * @note Macro IS_TIM_XOR_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides an XOR input.
  * @rmtoll CR2          TI1S          TIM_IC_EnableXORCombination
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Enable_IC_XORCombination(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->CR2, TIM_CR2_TI1S);
}

/**
  * @brief  Disconnect the TIMx_CH1, CH2 and CH3 pins  from the TI1 input.
  * @note Macro IS_TIM_XOR_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides an XOR input.
  * @rmtoll CR2          TI1S          TIM_IC_DisableXORCombination
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Disable_IC_XORCombination(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->CR2, TIM_CR2_TI1S);
}

/**
  * @brief  Indicates whether the TIMx_CH1, CH2 and CH3 pins are connectected to the TI1 input.
  * @note Macro IS_TIM_XOR_INSTANCE(TIMx) can be used to check whether or not
  * a timer instance provides an XOR input.
  * @rmtoll CR2          TI1S          TIM_IC_IsEnabledXORCombination
  * @param  TIMx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t TIM_Get_IC_XORCombination(TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->CR2, TIM_CR2_TI1S) == (TIM_CR2_TI1S)) ? 1UL : 0UL);
}

/**
  * @brief  Get captured value for input channel 1.
  * @note In 32-bit timer implementations returned captured value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC1_INSTANCE(TIMx) can be used to check whether or not
  *       input channel 1 is supported by a timer instance.
  * @note If dithering is activated, pay attention to the returned value interpretation.
  * @rmtoll CCR1         CCR1          TIM_IC_GetCaptureCH1
  * @param  TIMx Timer instance
  * @retval CapturedValue (between Min_Data=0 and Max_Data=65535)
  */
__STATIC_INLINE uint32_t TIM_Get_IC_CaptureCH1(TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CCR1));
}

/**
  * @brief  Get captured value for input channel 2.
  * @note In 32-bit timer implementations returned captured value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC2_INSTANCE(TIMx) can be used to check whether or not
  *       input channel 2 is supported by a timer instance.
  * @note If dithering is activated, pay attention to the returned value interpretation.
  * @rmtoll CCR2         CCR2          TIM_IC_GetCaptureCH2
  * @param  TIMx Timer instance
  * @retval CapturedValue (between Min_Data=0 and Max_Data=65535)
  */
__STATIC_INLINE uint32_t TIM_Get_IC_CaptureCH2(TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CCR2));
}

/**
  * @brief  Get captured value for input channel 3.
  * @note In 32-bit timer implementations returned captured value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC3_INSTANCE(TIMx) can be used to check whether or not
  *       input channel 3 is supported by a timer instance.
  * @note If dithering is activated, pay attention to the returned value interpretation.
  * @rmtoll CCR3         CCR3          TIM_IC_GetCaptureCH3
  * @param  TIMx Timer instance
  * @retval CapturedValue (between Min_Data=0 and Max_Data=65535)
  */
__STATIC_INLINE uint32_t TIM_Get_IC_CaptureCH3(TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CCR3));
}

/**
  * @brief  Get captured value for input channel 4.
  * @note In 32-bit timer implementations returned captured value can be between 0x00000000 and 0xFFFFFFFF.
  * @note Macro IS_TIM_32B_COUNTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports a 32 bits counter.
  * @note Macro IS_TIM_CC4_INSTANCE(TIMx) can be used to check whether or not
  *       input channel 4 is supported by a timer instance.
  * @note If dithering is activated, pay attention to the returned value interpretation.
  * @rmtoll CCR4         CCR4          TIM_IC_GetCaptureCH4
  * @param  TIMx Timer instance
  * @retval CapturedValue (between Min_Data=0 and Max_Data=65535)
  */
__STATIC_INLINE uint32_t TIM_Get_IC_CaptureCH4(TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CCR4));
}

/**
  * @brief  Enable external clock mode 2.
  * @note When external clock mode 2 is enabled the counter is clocked by any active edge on the ETRF signal.
  * @note Macro IS_TIM_CLOCKSOURCE_ETRMODE2_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports external clock mode2.
  * @rmtoll SMCR         ECE           TIM_EnableExternalClock
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Enable_ExternalClock(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->SMCR, TIM_SMCR_ECE);
}

/**
  * @brief  Disable external clock mode 2.
  * @note Macro IS_TIM_CLOCKSOURCE_ETRMODE2_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports external clock mode2.
  * @rmtoll SMCR         ECE           TIM_DisableExternalClock
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Disable_ExternalClock(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->SMCR, TIM_SMCR_ECE);
}

/**
  * @brief  Indicate whether external clock mode 2 is enabled.
  * @note Macro IS_TIM_CLOCKSOURCE_ETRMODE2_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports external clock mode2.
  * @rmtoll SMCR         ECE           TIM_IsEnabledExternalClock
  * @param  TIMx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t TIM_Get_ExternalClock(TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->SMCR, TIM_SMCR_ECE) == (TIM_SMCR_ECE)) ? 1UL : 0UL);
}

/**
  * @brief  Set the clock source of the counter clock.
  * @note when selected clock source is external clock mode 1, the timer input
  *       the external clock is applied is selected by calling the @ref TIM_SetTriggerInput()
  *       function. This timer input must be configured by calling
  *       the @ref TIM_IC_Config() function.
  * @note Macro IS_TIM_CLOCKSOURCE_ETRMODE1_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports external clock mode1.
  * @note Macro IS_TIM_CLOCKSOURCE_ETRMODE2_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports external clock mode2.
  * @rmtoll SMCR         SMS           TIM_SetClockSource\n
  *         SMCR         ECE           TIM_SetClockSource
  * @param  TIMx Timer instance
  * @param  ClockSource This parameter can be one of the following values:
  *         @arg @ref TIM_CLOCKSOURCE_INTERNAL
  *         @arg @ref TIM_CLOCKSOURCE_EXT_MODE1
  *         @arg @ref TIM_CLOCKSOURCE_EXT_MODE2
  * @retval None
  */
__STATIC_INLINE void TIM_Set_ClockSource(TIM_TypeDef *TIMx, uint32_t ClockSource)
{
  MODIFY_REG(TIMx->SMCR, TIM_SMCR_SMS | TIM_SMCR_ECE, ClockSource);
}

/**
  * @brief  Set the encoder interface mode.
  * @note Macro IS_TIM_ENCODER_INTERFACE_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports the encoder mode.
  * @rmtoll SMCR         SMS           TIM_SetEncoderMode
  * @param  TIMx Timer instance
  * @param  EncoderMode This parameter can be one of the following values:
  *         @arg @ref TIM_ENCODERMODE_X2_TI1
  *         @arg @ref TIM_ENCODERMODE_X2_TI2
  *         @arg @ref TIM_ENCODERMODE_X4_TI12
  *         @arg @ref TIM_ENCODERMODE_CLOCKPLUSDIRECTION_X2
  *         @arg @ref TIM_ENCODERMODE_CLOCKPLUSDIRECTION_X1
  *         @arg @ref TIM_ENCODERMODE_DIRECTIONALCLOCK_X2
  *         @arg @ref TIM_ENCODERMODE_DIRECTIONALCLOCK_X1_TI12
  *         @arg @ref TIM_ENCODERMODE_X1_TI1
  *         @arg @ref TIM_ENCODERMODE_X1_TI2
  * @retval None
  */
__STATIC_INLINE void TIM_Set_EncoderMode(TIM_TypeDef *TIMx, uint32_t EncoderMode)
{
  MODIFY_REG(TIMx->SMCR, TIM_SMCR_SMS, EncoderMode);
}

/**
  * @brief  Set the trigger output (TRGO) used for timer synchronization .
  * @note Macro IS_TIM_MASTER_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance can operate as a master timer.
  * @rmtoll CR2          MMS           TIM_SetTriggerOutput
  * @param  TIMx Timer instance
  * @param  TimerSynchronization This parameter can be one of the following values:
  *         @arg @ref TIM_TRGO_RESET
  *         @arg @ref TIM_TRGO_ENABLE
  *         @arg @ref TIM_TRGO_UPDATE
  *         @arg @ref TIM_TRGO_CC1IF
  *         @arg @ref TIM_TRGO_OC1REF
  *         @arg @ref TIM_TRGO_OC2REF
  *         @arg @ref TIM_TRGO_OC3REF
  *         @arg @ref TIM_TRGO_OC4REF
  *         @arg @ref TIM_TRGO_ENCODERCLK
  * @retval None
  */
__STATIC_INLINE void TIM_Set_TriggerOutput(TIM_TypeDef *TIMx, uint32_t TimerSynchronization)
{
  MODIFY_REG(TIMx->CR2, TIM_CR2_MMS, TimerSynchronization);
}

/**
  * @brief  Set the trigger output 2 (TRGO2) used for ADC synchronization .
  * @note Macro IS_TIM_TRGO2_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance can be used for ADC synchronization.
  * @rmtoll CR2          MMS2          TIM_SetTriggerOutput2
  * @param  TIMx Timer Instance
  * @param  ADCSynchronization This parameter can be one of the following values:
  *         @arg @ref TIM_TRGO2_RESET
  *         @arg @ref TIM_TRGO2_ENABLE
  *         @arg @ref TIM_TRGO2_UPDATE
  *         @arg @ref TIM_TRGO2_CC1F
  *         @arg @ref TIM_TRGO2_OC1
  *         @arg @ref TIM_TRGO2_OC2
  *         @arg @ref TIM_TRGO2_OC3
  *         @arg @ref TIM_TRGO2_OC4
  *         @arg @ref TIM_TRGO2_OC5
  *         @arg @ref TIM_TRGO2_OC6
  *         @arg @ref TIM_TRGO2_OC4_RISINGFALLING
  *         @arg @ref TIM_TRGO2_OC6_RISINGFALLING
  *         @arg @ref TIM_TRGO2_OC4_RISING_OC6_RISING
  *         @arg @ref TIM_TRGO2_OC4_RISING_OC6_FALLING
  *         @arg @ref TIM_TRGO2_OC5_RISING_OC6_RISING
  *         @arg @ref TIM_TRGO2_OC5_RISING_OC6_FALLING
  * @retval None
  */
__STATIC_INLINE void TIM_Set_TriggerOutput2(TIM_TypeDef *TIMx, uint32_t ADCSynchronization)
{
  MODIFY_REG(TIMx->CR2, TIM_CR2_MMS2, ADCSynchronization);
}

/**
  * @brief  Set the synchronization mode of a slave timer.
  * @note Macro IS_TIM_SLAVE_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance can operate as a slave timer.
  * @rmtoll SMCR         SMS           TIM_SetSlaveMode
  * @param  TIMx Timer instance
  * @param  SlaveMode This parameter can be one of the following values:
  *         @arg @ref TIM_SLAVEMODE_DISABLED
  *         @arg @ref TIM_SLAVEMODE_RESET
  *         @arg @ref TIM_SLAVEMODE_GATED
  *         @arg @ref TIM_SLAVEMODE_TRIGGER
  *         @arg @ref TIM_SLAVEMODE_COMBINED_RESETTRIGGER
  *         @arg @ref TIM_SLAVEMODE_COMBINED_GATEDRESET
  * @retval None
  */
__STATIC_INLINE void TIM_Set_SlaveMode(TIM_TypeDef *TIMx, uint32_t SlaveMode)
{
  MODIFY_REG(TIMx->SMCR, TIM_SMCR_SMS, SlaveMode);
}

/**
  * @brief  Set the selects the trigger input to be used to synchronize the counter.
  * @note Macro IS_TIM_SLAVE_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance can operate as a slave timer.
  * @rmtoll SMCR         TS            TIM_SetTriggerInput
  * @param  TIMx Timer instance
  * @param  TriggerInput This parameter can be one of the following values:
  *         @arg @ref TIM_TS_ITR0
  *         @arg @ref TIM_TS_ITR1
  *         @arg @ref TIM_TS_ITR2
  *         @arg @ref TIM_TS_ITR3
  *         @arg @ref TIM_TS_TI1F_ED
  *         @arg @ref TIM_TS_TI1FP1
  *         @arg @ref TIM_TS_TI2FP2
  *         @arg @ref TIM_TS_ETRF
  *         @arg @ref TIM_TS_ITR4
  *         @arg @ref TIM_TS_ITR5
  *         @arg @ref TIM_TS_ITR6
  *         @arg @ref TIM_TS_ITR7
  *         @arg @ref TIM_TS_ITR8
  *         @arg @ref TIM_TS_ITR9
  *         @arg @ref TIM_TS_ITR10
  *         @arg @ref TIM_TS_ITR11
  * @retval None
  */
__STATIC_INLINE void TIM_Set_TriggerInput(TIM_TypeDef *TIMx, uint32_t TriggerInput)
{
  MODIFY_REG(TIMx->SMCR, TIM_SMCR_TS, TriggerInput);
}

/**
  * @brief  Enable the Master/Slave mode.
  * @note Macro IS_TIM_SLAVE_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance can operate as a slave timer.
  * @rmtoll SMCR         MSM           TIM_EnableMasterSlaveMode
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Enable_MasterSlaveMode(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->SMCR, TIM_SMCR_MSM);
}

/**
  * @brief  Disable the Master/Slave mode.
  * @note Macro IS_TIM_SLAVE_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance can operate as a slave timer.
  * @rmtoll SMCR         MSM           TIM_DisableMasterSlaveMode
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Disable_MasterSlaveMode(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->SMCR, TIM_SMCR_MSM);
}

/**
  * @brief Indicates whether the Master/Slave mode is enabled.
  * @note Macro IS_TIM_SLAVE_INSTANCE(TIMx) can be used to check whether or not
  * a timer instance can operate as a slave timer.
  * @rmtoll SMCR         MSM           TIM_IsEnabledMasterSlaveMode
  * @param  TIMx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t TIM_Get_MasterSlaveMode(TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->SMCR, TIM_SMCR_MSM) == (TIM_SMCR_MSM)) ? 1UL : 0UL);
}

/**
  * @brief  Configure the external trigger (ETR) input.
  * @note Macro IS_TIM_ETR_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides an external trigger input.
  * @rmtoll SMCR         ETP           TIM_ConfigETR\n
  *         SMCR         ETPS          TIM_ConfigETR\n
  *         SMCR         ETF           TIM_ConfigETR
  * @param  TIMx Timer instance
  * @param  ETRPolarity This parameter can be one of the following values:
  *         @arg @ref TIM_ETR_POLARITY_NONINVERTED
  *         @arg @ref TIM_ETR_POLARITY_INVERTED
  * @param  ETRPrescaler This parameter can be one of the following values:
  *         @arg @ref TIM_ETR_PRESCALER_DIV1
  *         @arg @ref TIM_ETR_PRESCALER_DIV2
  *         @arg @ref TIM_ETR_PRESCALER_DIV4
  *         @arg @ref TIM_ETR_PRESCALER_DIV8
  * @param  ETRFilter This parameter can be one of the following values:
  *         @arg @ref TIM_ETR_FILTER_FDIV1
  *         @arg @ref TIM_ETR_FILTER_FDIV1_N2
  *         @arg @ref TIM_ETR_FILTER_FDIV1_N4
  *         @arg @ref TIM_ETR_FILTER_FDIV1_N8
  *         @arg @ref TIM_ETR_FILTER_FDIV2_N6
  *         @arg @ref TIM_ETR_FILTER_FDIV2_N8
  *         @arg @ref TIM_ETR_FILTER_FDIV4_N6
  *         @arg @ref TIM_ETR_FILTER_FDIV4_N8
  *         @arg @ref TIM_ETR_FILTER_FDIV8_N6
  *         @arg @ref TIM_ETR_FILTER_FDIV8_N8
  *         @arg @ref TIM_ETR_FILTER_FDIV16_N5
  *         @arg @ref TIM_ETR_FILTER_FDIV16_N6
  *         @arg @ref TIM_ETR_FILTER_FDIV16_N8
  *         @arg @ref TIM_ETR_FILTER_FDIV32_N5
  *         @arg @ref TIM_ETR_FILTER_FDIV32_N6
  *         @arg @ref TIM_ETR_FILTER_FDIV32_N8
  * @retval None
  */
__STATIC_INLINE void TIM_Set_ETR(TIM_TypeDef *TIMx, uint32_t ETRPolarity, uint32_t ETRPrescaler,
                                      uint32_t ETRFilter)
{
  MODIFY_REG(TIMx->SMCR, TIM_SMCR_ETP | TIM_SMCR_ETPS | TIM_SMCR_ETF, ETRPolarity | ETRPrescaler | ETRFilter);
}

/**
  * @brief  Select the external trigger (ETR) input source.
  * @note Macro IS_TIM_ETRSEL_INSTANCE(TIMx) can be used to check whether or
  *       not a timer instance supports ETR source selection.
  * @rmtoll AF1          ETRSEL        TIM_SetETRSource
  * @param  TIMx Timer instance
  * @param  ETRSource This parameter can be one of the following values:
  *
  *         TIM2: any combination of ETR_RMP where
  *
  *            @arg @ref TIM_TIM2_ETRSOURCE_GPIO
  *            @arg @ref TIM_TIM2_ETRSOURCE_COMP1
  *            @arg @ref TIM_TIM2_ETRSOURCE_COMP2
  *            @arg @ref TIM_TIM2_ETRSOURCE_TIM3_ETR
  *            @arg @ref TIM_TIM2_ETRSOURCE_TIM4_ETR
  *
  *         TIM3: any combination of ETR_RMP where
  *
  *            @arg @ref TIM_TIM3_ETRSOURCE_GPIO
  *            @arg @ref TIM_TIM3_ETRSOURCE_COMP1
  *            @arg @ref TIM_TIM3_ETRSOURCE_COMP2
  *            @arg @ref TIM_TIM3_ETRSOURCE_TIM2_ETR
  *
  *         TIM8: any combination of ETR_RMP where
  *
  *            . . ETR_RMP can be one of the following values
  *            @arg @ref TIM_TIM8_ETRSOURCE_GPIO
  *            @arg @ref TIM_TIM8_ETRSOURCE_COMP1
  *            @arg @ref TIM_TIM8_ETRSOURCE_COMP2
  *
  *         (*)  Value not defined in all devices. \n
  *         (**) Register not available in all devices.
  * @retval None
  */
__STATIC_INLINE void TIM_Set_ETRSource(TIM_TypeDef *TIMx, uint32_t ETRSource)
{
  MODIFY_REG(TIMx->AF1, TIM_AF1_ETRSEL, ETRSource);
}

/**
  * @brief  Enable SMS preload.
  * @note Macro IS_TIM_SMS_PRELOAD_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports the preload of SMS field in SMCR register.
  * @rmtoll SMCR         SMSPE           TIM_EnableSMSPreload
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Enable_SMSPreload(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->SMCR, TIM_SMCR_SMSPE);
}

/**
  * @brief  Disable SMS preload.
  * @note Macro IS_TIM_SMS_PRELOAD_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports the preload of SMS field in SMCR register.
  * @rmtoll SMCR         SMSPE           TIM_DisableSMSPreload
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Disable_SMSPreload(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->SMCR, TIM_SMCR_SMSPE);
}

/**
  * @brief  Indicate whether  SMS preload is enabled.
  * @note Macro IS_TIM_SMS_PRELOAD_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports the preload of SMS field in SMCR register.
  * @rmtoll SMCR         SMSPE           TIM_IsEnabledSMSPreload
  * @param  TIMx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t TIM_Get_SMSPreload(TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->SMCR, TIM_SMCR_SMSPE) == (TIM_SMCR_SMSPE)) ? 1UL : 0UL);
}

/**
  * @brief  Set the preload source of SMS.
  * @note Macro IS_TIM_SMS_PRELOAD_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports the preload of SMS field in SMCR register.
  * @rmtoll SMCR         SMSPS        TIM_SetSMSPreloadSource\n
  * @param  TIMx Timer instance
  * @param  PreloadSource This parameter can be one of the following values:
  *         @arg @ref TIM_SMSPS_TIMUPDATE
  *         @arg @ref TIM_SMSPS_INDEX
  * @retval None
  */
__STATIC_INLINE void TIM_Set_SMSPreloadSource(TIM_TypeDef *TIMx, uint32_t PreloadSource)
{
  MODIFY_REG(TIMx->SMCR, TIM_SMCR_SMSPS, PreloadSource);
}

/**
  * @brief  Get the preload source of SMS.
  * @note Macro IS_TIM_SMS_PRELOAD_INSTANCE(TIMx) can be used to check
  *       whether or not a timer instance supports the preload of SMS field in SMCR register.
  * @rmtoll SMCR         SMSPS        TIM_GetSMSPreloadSource\n
  * @param  TIMx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref TIM_SMSPS_TIMUPDATE
  *         @arg @ref TIM_SMSPS_INDEX
  */
__STATIC_INLINE uint32_t TIM_Get_SMSPreloadSource(TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_BIT(TIMx->SMCR, TIM_SMCR_SMSPS));
}

/**
  * @brief  Enable the break function.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         BKE           TIM_EnableBRK
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Enable_BRK(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->BDTR, TIM_BDTR_BKE);
}

/**
  * @brief  Disable the break function.
  * @rmtoll BDTR         BKE           TIM_DisableBRK
  * @param  TIMx Timer instance
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @retval None
  */
__STATIC_INLINE void TIM_Disable_BRK(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->BDTR, TIM_BDTR_BKE);
}

/**
  * @brief  Configure the break input.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @note Bidirectional mode is only supported by advanced timer instances.
  *       Macro IS_TIM_ADVANCED_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance is an advanced-control timer.
  * @note In bidirectional mode (BKBID bit set), the Break input is configured both
  *        in input mode and in open drain output mode. Any active Break event will
  *        assert a low logic level on the Break input to indicate an internal break
  *        event to external devices.
  * @note When bidirectional mode isn't supported, BreakAFMode must be set to
  *       TIM_BREAK_AFMODE_INPUT.
  * @rmtoll BDTR         BKP           TIM_ConfigBRK\n
  *         BDTR         BKF           TIM_ConfigBRK\n
  *         BDTR         BKBID         TIM_ConfigBRK
  * @param  TIMx Timer instance
  * @param  BreakPolarity This parameter can be one of the following values:
  *         @arg @ref TIM_BREAK_POLARITY_LOW
  *         @arg @ref TIM_BREAK_POLARITY_HIGH
  * @param  BreakFilter This parameter can be one of the following values:
  *         @arg @ref TIM_BREAK_FILTER_FDIV1
  *         @arg @ref TIM_BREAK_FILTER_FDIV1_N2
  *         @arg @ref TIM_BREAK_FILTER_FDIV1_N4
  *         @arg @ref TIM_BREAK_FILTER_FDIV1_N8
  *         @arg @ref TIM_BREAK_FILTER_FDIV2_N6
  *         @arg @ref TIM_BREAK_FILTER_FDIV2_N8
  *         @arg @ref TIM_BREAK_FILTER_FDIV4_N6
  *         @arg @ref TIM_BREAK_FILTER_FDIV4_N8
  *         @arg @ref TIM_BREAK_FILTER_FDIV8_N6
  *         @arg @ref TIM_BREAK_FILTER_FDIV8_N8
  *         @arg @ref TIM_BREAK_FILTER_FDIV16_N5
  *         @arg @ref TIM_BREAK_FILTER_FDIV16_N6
  *         @arg @ref TIM_BREAK_FILTER_FDIV16_N8
  *         @arg @ref TIM_BREAK_FILTER_FDIV32_N5
  *         @arg @ref TIM_BREAK_FILTER_FDIV32_N6
  *         @arg @ref TIM_BREAK_FILTER_FDIV32_N8
  * @param  BreakAFMode This parameter can be one of the following values:
  *         @arg @ref TIM_BREAK_AFMODE_INPUT
  *         @arg @ref TIM_BREAK_AFMODE_BIDIRECTIONAL
  * @retval None
  */
__STATIC_INLINE void TIM_Config_BRK(TIM_TypeDef *TIMx, uint32_t BreakPolarity, uint32_t BreakFilter,
                                      uint32_t BreakAFMode)
{
  MODIFY_REG(TIMx->BDTR, TIM_BDTR_BKP | TIM_BDTR_BKF | TIM_BDTR_BKBID, BreakPolarity | BreakFilter | BreakAFMode);
}

/**
  * @brief  Disarm the break input (when it operates in bidirectional mode).
  * @note  The break input can be disarmed only when it is configured in
  *        bidirectional mode and when when MOE is reset.
  * @note  Purpose is to be able to have the input voltage back to high-state,
  *        whatever the time constant on the output .
  * @rmtoll BDTR         BKDSRM        TIM_DisarmBRK
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Disarm_BRK(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->BDTR, TIM_BDTR_BKDSRM);
}

/**
  * @brief  Re-arm the break input (when it operates in bidirectional mode).
  * @note  The Break input is automatically armed as soon as MOE bit is set.
  * @rmtoll BDTR         BKDSRM        TIM_ReArmBRK
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_ReArm_BRK(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->BDTR, TIM_BDTR_BKDSRM);
}

/**
  * @brief  Get the Re-arm the break input status.
  * @rmtoll BDTR         BKDSRM        TIM_Read_ReArmBRK\n
  * @param  TIMx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint8_t TIM_Read_ReArmBRK(TIM_TypeDef *TIMx)
{
  return (READ_BIT(TIMx->BDTR, TIM_BDTR_BKDSRM) == (TIM_BDTR_BKDSRM));
}

/**
  * @function  TIM_Set_BreakPolarity
  * @brief  Configure the break input
  * @param  TIMx:
            @arg TIM Instance
  * @param  BreakPolarity This parameter can be one of the following values:
  *         @arg @ref TIM_BREAK_POLARITY_LOW
  *         @arg @ref TIM_BREAK_POLARITY_HIGH
  * @retval None
  */
__STATIC_INLINE void TIM_Set_BreakPolarity(TIM_TypeDef *TIMx,uint32_t BreakPolarity)
{
  MODIFY_REG(TIMx->BDTR, TIM_BDTR_BKP, BreakPolarity);
}

/**
  * @brief  Enable the break 2 function.
  * @note Macro IS_TIM_BKIN2_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a second break input.
  * @rmtoll BDTR         BK2E          TIM_EnableBRK2
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Enable_BRK2(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->BDTR, TIM_BDTR_BK2E);
}

/**
  * @brief  Disable the break  2 function.
  * @note Macro IS_TIM_BKIN2_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a second break input.
  * @rmtoll BDTR         BK2E          TIM_DisableBRK2
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Disable_BRK2(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->BDTR, TIM_BDTR_BK2E);
}

/**
  * @brief  Configure the break 2 input.
  * @note Macro IS_TIM_BKIN2_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a second break input.
  * @note Bidirectional mode is only supported by advanced timer instances.
  *       Macro IS_TIM_ADVANCED_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance is an advanced-control timer.
  * @note In bidirectional mode (BK2BID bit set), the Break 2 input is configured both
  *        in input mode and in open drain output mode. Any active Break event will
  *        assert a low logic level on the Break 2 input to indicate an internal break
  *        event to external devices.
  * @note When bidirectional mode isn't supported, Break2AFMode must be set to
  *       TIM_BREAK2_AFMODE_INPUT.
  * @rmtoll BDTR         BK2P          TIM_ConfigBRK2\n
  *         BDTR         BK2F          TIM_ConfigBRK2\n
  *         BDTR         BK2BID        TIM_ConfigBRK2
  * @param  TIMx Timer instance
  * @param  Break2Polarity This parameter can be one of the following values:
  *         @arg @ref TIM_BREAK2_POLARITY_LOW
  *         @arg @ref TIM_BREAK2_POLARITY_HIGH
  * @param  Break2Filter This parameter can be one of the following values:
  *         @arg @ref TIM_BREAK2_FILTER_FDIV1
  *         @arg @ref TIM_BREAK2_FILTER_FDIV1_N2
  *         @arg @ref TIM_BREAK2_FILTER_FDIV1_N4
  *         @arg @ref TIM_BREAK2_FILTER_FDIV1_N8
  *         @arg @ref TIM_BREAK2_FILTER_FDIV2_N6
  *         @arg @ref TIM_BREAK2_FILTER_FDIV2_N8
  *         @arg @ref TIM_BREAK2_FILTER_FDIV4_N6
  *         @arg @ref TIM_BREAK2_FILTER_FDIV4_N8
  *         @arg @ref TIM_BREAK2_FILTER_FDIV8_N6
  *         @arg @ref TIM_BREAK2_FILTER_FDIV8_N8
  *         @arg @ref TIM_BREAK2_FILTER_FDIV16_N5
  *         @arg @ref TIM_BREAK2_FILTER_FDIV16_N6
  *         @arg @ref TIM_BREAK2_FILTER_FDIV16_N8
  *         @arg @ref TIM_BREAK2_FILTER_FDIV32_N5
  *         @arg @ref TIM_BREAK2_FILTER_FDIV32_N6
  *         @arg @ref TIM_BREAK2_FILTER_FDIV32_N8
  * @param  Break2AFMode This parameter can be one of the following values:
  *         @arg @ref TIM_BREAK2_AFMODE_INPUT
  *         @arg @ref TIM_BREAK2_AFMODE_BIDIRECTIONAL
  * @retval None
  */
__STATIC_INLINE void TIM_Config_BRK2(TIM_TypeDef *TIMx, uint32_t Break2Polarity, uint32_t Break2Filter,
                                       uint32_t Break2AFMode)
{
  MODIFY_REG(TIMx->BDTR, TIM_BDTR_BK2P | TIM_BDTR_BK2F | TIM_BDTR_BK2BID, Break2Polarity | Break2Filter | Break2AFMode);
}

/**
  * @brief  Disarm the break 2 input (when it operates in bidirectional mode).
  * @note  The break 2 input can be disarmed only when it is configured in
  *        bidirectional mode and when when MOE is reset.
  * @note  Purpose is to be able to have the input voltage back to high-state,
  *        whatever the time constant on the output.
  * @rmtoll BDTR         BK2DSRM       TIM_DisarmBRK2
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Disarm_BRK2(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->BDTR, TIM_BDTR_BK2DSRM);
}

/**
  * @brief  Re-arm the break 2 input (when it operates in bidirectional mode).
  * @note  The Break 2 input is automatically armed as soon as MOE bit is set.
  * @rmtoll BDTR         BK2DSRM       TIM_ReArmBRK2
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_ReArm_BRK2(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->BDTR, TIM_BDTR_BK2DSRM);
}


/**
  * @function  TIM_Set_OC_CompareCH1N
  * @brief  Set compare value for output channel 1N (TIM_CCR1N).
  * @param  TIMx:
            @arg TIM Instance
  * @param  CompareValue between Min_Data=0 and Max_Data=65535
  * @retval None
  */
__STATIC_INLINE void TIM_Set_OC_CompareCH1N(TIM_TypeDef *TIMx,uint32_t CompareValue)
{
  WRITE_REG(TIMx->CCR1N, CompareValue);
}

/**
  * @function  TIM_Set_OC_CompareCH2N
  * @brief  Set compare value for output channel 2N (TIM_CCR2N).
  * @param  TIMx:
            @arg TIM Instance
  * @param  CompareValue between Min_Data=0 and Max_Data=65535
  * @retval None
  */
__STATIC_INLINE void TIM_Set_OC_CompareCH2N(TIM_TypeDef *TIMx,uint32_t CompareValue)
{
  WRITE_REG(TIMx->CCR2N, CompareValue);
}

/**
  * @function  TIM_Set_OC_CompareCH3N
  * @brief  Set compare value for output channel 3N (TIM_CCR3N).
  * @param  TIMx:
            @arg TIM Instance
  * @param  CompareValue between Min_Data=0 and Max_Data=65535
  * @retval None
  */
__STATIC_INLINE void TIM_Set_OC_CompareCH3N(TIM_TypeDef *TIMx,uint32_t CompareValue)
{
  WRITE_REG(TIMx->CCR3N, CompareValue);
}

/**
  * @function  TIM_Get_OC_CompareCH1N
  * @brief  Get compare value (TIM_CCR1N) set for  output channel 1N.
  * @param  TIMx:
            @arg TIM Instance
  * @retval CompareValue (between Min_Data=0 and Max_Data=65535)
  */
__STATIC_INLINE uint32_t TIM_Get_OC_CompareCH1N(TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CCR1N));
}

/**
  * @function  TIM_Get_OC_CompareCH2N
  * @brief  Get compare value (TIM_CCR2N) set for  output channel 2N.
  * @param  TIMx:
            @arg TIM Instance
  * @retval CompareValue (between Min_Data=0 and Max_Data=65535)
  */
__STATIC_INLINE uint32_t TIM_Get_OC_CompareCH2N(TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CCR2N));
}

/**
  * @function  TIM_Get_OC_CompareCH3N
  * @brief  Get compare value (TIM_CCR3N) set for  output channel 3N.
  * @param  TIMx:
            @arg TIM Instance
  * @retval CompareValue (between Min_Data=0 and Max_Data=65535)
  */
__STATIC_INLINE uint32_t TIM_Get_OC_CompareCH3N(TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_REG(TIMx->CCR3N));
}

/**
  * @brief  Select the outputs off state (enabled v.s. disabled) in Idle and Run modes.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         OSSI          TIM_SetOffStates\n
  *         BDTR         OSSR          TIM_SetOffStates
  * @param  TIMx Timer instance
  * @param  OffStateIdle This parameter can be one of the following values:
  *         @arg @ref TIM_OSSI_DISABLE
  *         @arg @ref TIM_OSSI_ENABLE
  * @param  OffStateRun This parameter can be one of the following values:
  *         @arg @ref TIM_OSSR_DISABLE
  *         @arg @ref TIM_OSSR_ENABLE
  * @retval None
  */
__STATIC_INLINE void TIM_Set_OffStates(TIM_TypeDef *TIMx, uint32_t OffStateIdle, uint32_t OffStateRun)
{
  MODIFY_REG(TIMx->BDTR, TIM_BDTR_OSSI | TIM_BDTR_OSSR, OffStateIdle | OffStateRun);
}

/**
  * @brief  Enable automatic output (MOE can be set by software or automatically when a break input is active).
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         AOE           TIM_EnableAutomaticOutput
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Enable_AOE(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->BDTR, TIM_BDTR_AOE);
}

/**
  * @brief  Disable automatic output (MOE can be set only by software).
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         AOE           TIM_DisableAutomaticOutput
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Disable_AOE(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->BDTR, TIM_BDTR_AOE);
}

/**
  * @brief  Indicate whether automatic output is enabled.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         AOE           TIM_IsEnabledAutomaticOutput
  * @param  TIMx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t TIM_Get_AOE(TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->BDTR, TIM_BDTR_AOE) == (TIM_BDTR_AOE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable the outputs (set the MOE bit in TIMx_BDTR register).
  * @note The MOE bit in TIMx_BDTR register allows to enable /disable the outputs by
  *       software and is reset in case of break or break2 event
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         MOE           TIM_EnableAllOutputs
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Enable_MOE(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->BDTR, TIM_BDTR_MOE);
}

/**
  * @brief  Disable the outputs (reset the MOE bit in TIMx_BDTR register).
  * @note The MOE bit in TIMx_BDTR register allows to enable /disable the outputs by
  *       software and is reset in case of break or break2 event.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         MOE           TIM_DisableAllOutputs
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Disable_MOE(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->BDTR, TIM_BDTR_MOE);
}

/**
  * @brief  Indicates whether outputs are enabled.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides a break input.
  * @rmtoll BDTR         MOE           TIM_IsEnabledAllOutputs
  * @param  TIMx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t TIM_Get_MOE(TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->BDTR, TIM_BDTR_MOE) == (TIM_BDTR_MOE)) ? 1UL : 0UL);
}


/**
  * @brief  Enable asymmetrical deadtime.
  * @note Macro IS_TIM_DEADTIME_ASYMMETRICAL_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides asymmetrical deadtime.
  * @rmtoll DTR2          DTAE          TIM_EnableAsymmetricalDeadTime
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Enable_AsymmetricalDeadTime(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->DTR2, TIM_DTR2_DTAE);
}

/**
  * @brief  Disable asymmetrical dead-time.
  * @note Macro IS_TIM_DEADTIME_ASYMMETRICAL_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides asymmetrical deadtime.
  * @rmtoll DTR2          DTAE          TIM_DisableAsymmetricalDeadTime
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Disable_AsymmetricalDeadTime(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->DTR2, TIM_DTR2_DTAE);
}

/**
  * @brief  Indicates whether asymmetrical deadtime is activated.
  * @note Macro IS_TIM_DEADTIME_ASYMMETRICAL_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides asymmetrical deadtime.
  * @rmtoll DTR2          DTAE          TIM_IsEnabledAsymmetricalDeadTime
  * @param  TIMx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t TIM_Get_AsymmetricalDeadTime(TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->DTR2, TIM_DTR2_DTAE) == (TIM_DTR2_DTAE)) ? 1UL : 0UL);
}

/**
  * @brief  Set the falling edge dead-time delay (delay inserted between the falling edge of the OCxREF signal and the
  *         rising edge of OCxN signals).
  * @note Macro IS_TIM_DEADTIME_ASYMMETRICAL_INSTANCE(TIMx) can be used to check whether or not
  *       asymmetrical dead-time insertion feature is supported by a timer instance.
  * @note Helper macro @ref __TIM_CALC_DEADTIME can be used to calculate the DeadTime parameter
  * @note This bit-field can not be modified as long as LOCK level 1, 2 or 3 has been programmed
  *       (LOCK bits in TIMx_BDTR register).
  * @rmtoll DTR2         DTGF           TIM_SetFallingDeadTime
  * @param  TIMx Timer instance
  * @param  DeadTime between Min_Data=0 and Max_Data=255
  * @retval None
  */
__STATIC_INLINE void TIM_Set_FallingDeadTime(TIM_TypeDef *TIMx, uint32_t DeadTime)
{
  MODIFY_REG(TIMx->DTR2, TIM_DTR2_DTGF, DeadTime);
}

/**
  * @brief  Get the falling edge dead-time delay (delay inserted between the falling edge of the OCxREF signal and
  *         the rising edge of OCxN signals).
  * @note Macro IS_TIM_DEADTIME_ASYMMETRICAL_INSTANCE(TIMx) can be used to check whether or not
  *       asymmetrical dead-time insertion feature is supported by a timer instance.
  * @note This bit-field can not be modified as long as LOCK level 1, 2 or 3 has been programmed
  *       (LOCK bits in TIMx_BDTR register).
  * @rmtoll DTR2          DTGF           TIM_GetFallingDeadTime
  * @param  TIMx Timer instance
  * @retval Returned value can be between Min_Data=0 and Max_Data=255:
  */
__STATIC_INLINE uint32_t TIM_Get_FallingDeadTime(TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_BIT(TIMx->DTR2, TIM_DTR2_DTGF));
}

/**
  * @brief  Enable deadtime preload.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides deadtime preload.
  * @rmtoll DTR2          DTPE          TIM_EnableDeadTimePreload
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Enable_DeadTimePreload(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->DTR2, TIM_DTR2_DTPE);
}

/**
  * @brief  Disable dead-time preload.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides deadtime preload.
  * @rmtoll DTR2          DTPE          TIM_DisableDeadTimePreload
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Disable_DeadTimePreload(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->DTR2, TIM_DTR2_DTPE);
}

/**
  * @brief  Indicates whether deadtime preload is activated.
  * @note Macro IS_TIM_BREAK_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides deadtime preload.
  * @rmtoll DTR2          DTPE          TIM_IsEnabledDeadTimePreload
  * @param  TIMx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t TIM_Get_DeadTimePreload(TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->DTR2, TIM_DTR2_DTPE) == (TIM_DTR2_DTPE)) ? 1UL : 0UL);
}

/**
  * @brief  Enable encoder index.
  * @note Macro IS_TIM_INDEX_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides an index input.
  * @rmtoll ECR         IE           TIM_EnableEncoderIndex
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Enable_EncoderIndex(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->ECR, TIM_ECR_IE);
}

/**
  * @brief  Disable encoder index.
  * @note Macro IS_TIM_INDEX_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides an index input.
  * @rmtoll ECR         IE           TIM_DisableEncoderIndex
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Disable_EncoderIndex(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->ECR, TIM_ECR_IE);
}

/**
  * @brief  Indicate whether encoder index is enabled.
  * @note Macro IS_TIM_INDEX_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides an index input.
  * @rmtoll ECR         IE           TIM_IsEnabledEncoderIndex
  * @param  TIMx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t TIM_Get_EncoderIndex(TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->ECR, TIM_ECR_IE) == (TIM_ECR_IE)) ? 1U : 0U);
}

/**
  * @brief  Set index direction
  * @note Macro IS_TIM_INDEX_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides an index input.
  * @rmtoll ECR          IDIR           TIM_SetIndexDirection
  * @param  TIMx Timer instance
  * @param  IndexDirection This parameter can be one of the following values:
  *         @arg @ref TIM_INDEX_UP_DOWN
  *         @arg @ref TIM_INDEX_UP
  *         @arg @ref TIM_INDEX_DOWN
  * @retval None
  */
__STATIC_INLINE void TIM_Set_IndexDirection(TIM_TypeDef *TIMx, uint32_t IndexDirection)
{
  MODIFY_REG(TIMx->ECR, TIM_ECR_IDIR, IndexDirection);
}

/**
  * @brief  Get actual index direction
  * @note Macro IS_TIM_INDEX_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides an index input.
  * @rmtoll ECR          IDIR           TIM_GetIndexDirection
  * @param  TIMx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref TIM_INDEX_UP_DOWN
  *         @arg @ref TIM_INDEX_UP
  *         @arg @ref TIM_INDEX_DOWN
  */
__STATIC_INLINE uint32_t TIM_Get_IndexDirection(TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_BIT(TIMx->ECR, TIM_ECR_IDIR));
}

/**
  * @brief  Enable first index.
  * @note Macro IS_TIM_INDEX_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides an index input.
  * @rmtoll ECR          FIDX          TIM_EnableFirstIndex
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Enable_FirstIndex(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->ECR, TIM_ECR_FIDX);
}

/**
  * @brief  Disable first index.
  * @note Macro IS_TIM_INDEX_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides an index input.
  * @rmtoll ECR          FIDX          TIM_DisableFirstIndex
  * @param  TIMx Timer instance
  * @retval None
  */
__STATIC_INLINE void TIM_Disable_FirstIndex(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->ECR, TIM_ECR_FIDX);
}

/**
  * @brief  Indicates whether first index is enabled.
  * @note Macro IS_TIM_INDEX_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides an index input.
  * @rmtoll ECR          FIDX          TIM_IsEnabledFirstIndex
  * @param  TIMx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t TIM_Get_FirstIndex(TIM_TypeDef *TIMx)
{
  return ((READ_BIT(TIMx->ECR, TIM_ECR_FIDX) == (TIM_ECR_FIDX)) ? 1UL : 0UL);
}

/**
  * @brief  Set index positioning
  * @note Macro IS_TIM_INDEX_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides an index input.
  * @rmtoll ECR          IPOS           TIM_SetIndexPositionning
  * @param  TIMx Timer instance
  * @param  IndexPositionning This parameter can be one of the following values:
  *         @arg @ref TIM_INDEX_POSITION_DOWN_DOWN
  *         @arg @ref TIM_INDEX_POSITION_DOWN_UP
  *         @arg @ref TIM_INDEX_POSITION_UP_DOWN
  *         @arg @ref TIM_INDEX_POSITION_UP_UP
  *         @arg @ref TIM_INDEX_POSITION_DOWN
  *         @arg @ref TIM_INDEX_POSITION_UP
  * @retval None
  */
__STATIC_INLINE void TIM_Set_IndexPositionning(TIM_TypeDef *TIMx, uint32_t IndexPositionning)
{
  MODIFY_REG(TIMx->ECR, TIM_ECR_IPOS, IndexPositionning);
}

/**
  * @brief  Get actual index positioning
  * @note Macro IS_TIM_INDEX_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides an index input.
  * @rmtoll ECR          IPOS           TIM_GetIndexPositionning
  * @param  TIMx Timer instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref TIM_INDEX_POSITION_DOWN_DOWN
  *         @arg @ref TIM_INDEX_POSITION_DOWN_UP
  *         @arg @ref TIM_INDEX_POSITION_UP_DOWN
  *         @arg @ref TIM_INDEX_POSITION_UP_UP
  *         @arg @ref TIM_INDEX_POSITION_DOWN
  *         @arg @ref TIM_INDEX_POSITION_UP
  */
__STATIC_INLINE uint32_t TIM_Get_IndexPositionning(TIM_TypeDef *TIMx)
{
  return (uint32_t)(READ_BIT(TIMx->ECR, TIM_ECR_IPOS));
}

/**
  * @brief  Configure encoder index.
  * @note Macro IS_TIM_INDEX_INSTANCE(TIMx) can be used to check whether or not
  *       a timer instance provides an index input.
  * @rmtoll ECR          IDIR          TIM_ConfigIDX\n
  *         ECR          FIDX          TIM_ConfigIDX\n
  *         ECR          IPOS          TIM_ConfigIDX
  * @param  TIMx Timer instance
  * @param  Configuration This parameter must be a combination of all the following values:
  *         @arg @ref TIM_INDEX_UP or @ref TIM_INDEX_DOWN or @ref TIM_INDEX_UP_DOWN
  *         @arg @ref TIM_INDEX_ALL or @ref TIM_INDEX_FIRST_ONLY
  *         @arg @ref TIM_INDEX_POSITION_DOWN_DOWN or ... or @ref TIM_INDEX_POSITION_UP
  * @retval None
  */
__STATIC_INLINE void TIM_Config_IDX(TIM_TypeDef *TIMx, uint32_t Configuration)
{
  MODIFY_REG(TIMx->ECR, TIM_ECR_IDIR | TIM_ECR_FIDX | TIM_ECR_IPOS, Configuration);
}


/**
  * @brief  Remap TIM inputs (input channel, internal/external triggers).
  * @note Macro IS_TIM_REMAP_INSTANCE(TIMx) can be used to check whether or not
  *       a some timer inputs can be remapped.
  * @rmtoll TIM2_TISEL    TI1SEL      TIM_SetRemap\n
  *         TIM2_TISEL    TI2SEL      TIM_SetRemap\n
  *         TIM2_TISEL    TI3SEL      TIM_SetRemap\n
  *         TIM2_TISEL    TI4SEL      TIM_SetRemap\n
  *         TIM3_TISEL    TI1SEL      TIM_SetRemap\n
  *         TIM3_TISEL    TI2SEL      TIM_SetRemap\n
  *         TIM3_TISEL    TI3SEL      TIM_SetRemap\n
  *         TIM8_TISEL    TI1SEL      TIM_SetRemap\n
  *         TIM15_TISEL   TI1SEL      TIM_SetRemap\n
  *         TIM15_TISEL   TI2SEL      TIM_SetRemap
  * @param  TIMx Timer instance
  * @param  Remap Remap param depends on the TIMx. Description available only
  *         in CHM version of the User Manual (not in .pdf).
  *         Otherwise see Reference Manual description of TISEL registers.
  *
  *         Below description summarizes "Timer Instance" and "Remap" param combinations:
  *
  *         TIM2: any combination of TI1_RMP, TI2_RMP, TI3_RMP and TI4_RMP where
  *
  *            . . TI1_RMP can be one of the following values
  *            @arg @ref TIM_TIM2_TI1_RMP_GPIO
  *            @arg @ref TIM_TIM2_TI1_RMP_COMP1
  *            @arg @ref TIM_TIM2_TI1_RMP_COMP2
  *
  *            . . TI2_RMP can be one of the following values
  *            @arg @ref TIM_TIM2_TI2_RMP_GPIO
  *            @arg @ref TIM_TIM2_TI2_RMP_COMP1
  *            @arg @ref TIM_TIM2_TI2_RMP_COMP2
  *
  *            . . TI3_RMP can be one of the following values
  *            @arg @ref TIM_TIM2_TI3_RMP_GPIO
  *
  *            . . TI4_RMP can be one of the following values
  *            @arg @ref TIM_TIM2_TI4_RMP_GPIO
  *            @arg @ref TIM_TIM2_TI4_RMP_COMP1
  *            @arg @ref TIM_TIM2_TI4_RMP_COMP2
  *
  *         TIM3: any combination of TI1_RMP and TI2_RMP where
  *
  *            . . TI1_RMP can be one of the following values
  *            @arg @ref TIM_TIM3_TI1_RMP_GPIO
  *            @arg @ref TIM_TIM3_TI1_RMP_COMP1
  *            @arg @ref TIM_TIM3_TI1_RMP_COMP2
  *
  *            . . TI2_RMP can be one of the following values
  *            @arg @ref TIM_TIM3_TI2_RMP_GPIO
  *            @arg @ref TIM_TIM3_TI2_RMP_COMP1
  *            @arg @ref TIM_TIM3_TI2_RMP_COMP2
  *
  *            . . TI3_RMP can be one of the following values
  *            @arg @ref TIM_TIM3_TI3_RMP_GPIO
  *
  *         TIM8: one of the following values
  *
  *            @arg @ref TIM_TIM8_TI1_RMP_GPIO
  *            @arg @ref TIM_TIM8_TI1_RMP_COMP1
  *            @arg @ref TIM_TIM8_TI1_RMP_COMP2
  *
  *         TIM15: any combination of TI1_RMP and TI2_RMP where
  *
  *            . . TI1_RMP can be one of the following values
  *            @arg @ref TIM_TIM15_TI1_RMP_GPIO
  *            @arg @ref TIM_TIM15_TI1_RMP_LSI
  *            @arg @ref TIM_TIM15_TI1_RMP_COMP1
  *            @arg @ref TIM_TIM15_TI1_RMP_COMP2
  *
  *            . . TI2_RMP can be one of the following values
  *            @arg @ref TIM_TIM15_TI2_RMP_GPIO
  *            @arg @ref TIM_TIM15_TI2_RMP_COMP2
  *
  *         (*)  Value not defined in all devices. \n
  *         (**) Register not available in all devices.
  *
  *
  * @retval None
  */
__STATIC_INLINE void TIM_Set_Remap(TIM_TypeDef *TIMx, uint32_t Remap)
{
  MODIFY_REG(TIMx->TISEL, (TIM_TISEL_TI1SEL | TIM_TISEL_TI2SEL | TIM_TISEL_TI3SEL | TIM_TISEL_TI4SEL), Remap);
}

/**
  * @brief  Set the OCREF clear input source
  * @note The OCxREF signal of a given channel can be cleared when a high level is applied on the OCREF_CLR_INPUT
  * @note This function can only be used in Output compare and PWM modes.
  * @note Macro IS_TIM_OCCS_INSTANCE(TIMx) can be used to check whether
  *       or not a timer instance can configure OCREF clear input source.
  * @rmtoll SMCR          OCCS                TIM_SetOCRefClearInputSource
  * @rmtoll AF2           OCRSEL              TIM_SetOCRefClearInputSource
  * @param  TIMx Timer instance
  * @param  OCRefClearInputSource This parameter can be one of the following values:
  *         @arg @ref TIM_OCREF_CLR_INT_ETR
  *         @arg @ref TIM_OCREF_CLR_INT_COMP1
  *         @arg @ref TIM_OCREF_CLR_INT_COMP2
  *
  *         (*)  Value not defined in all devices. \n
  * @retval None
  */
__STATIC_INLINE void TIM_Set_OCRefClearInputSource(TIM_TypeDef *TIMx, uint32_t OCRefClearInputSource)
{
  MODIFY_REG(TIMx->SMCR, TIM_SMCR_OCCS,
             ((OCRefClearInputSource & OCREF_CLEAR_SELECT_Msk) >> OCREF_CLEAR_SELECT_Pos) << TIM_SMCR_OCCS_Pos);
  MODIFY_REG(TIMx->AF2, TIM_AF2_OCRSEL, OCRefClearInputSource);
}

/**
  * @brief  Clear the update interrupt flag (UIF).
  * @rmtoll SR           UIF           TIM_ClearFlag_UPDATE
  * @param  TIMx Timer instance
  * @param  Flag:
  *         @arg @ref TIM_SR_UIF
  *         @arg @ref TIM_SR_CC1IF
  *         @arg @ref TIM_SR_CC2IF
  *         @arg @ref TIM_SR_CC3IF
  *         @arg @ref TIM_SR_CC4IF
  *         @arg @ref TIM_SR_CC5IF
  *         @arg @ref TIM_SR_CC6IF
  *         @arg @ref TIM_SR_COMIF
  *         @arg @ref TIM_SR_TIF
  *         @arg @ref TIM_SR_BIF
  *         @arg @ref TIM_SR_B2IF
  *         @arg @ref TIM_SR_CC1OF
  *         @arg @ref TIM_SR_CC2OF
  *         @arg @ref TIM_SR_CC3OF
  *         @arg @ref TIM_SR_CC4OF
  *         @arg @ref TIM_SR_SBIF
  *         @arg @ref TIM_SR_TERRF
  *         @arg @ref TIM_SR_IERRF
  *         @arg @ref TIM_SR_DIRF
  *         @arg @ref TIM_SR_IDXF
  * @retval None
  */
__STATIC_INLINE void TIM_Clear_Flag(TIM_TypeDef *TIMx, uint32_t Flag)
{
  WRITE_REG(TIMx->SR, ~(Flag));
}

/**
  * @brief  Indicate whether update interrupt flag (UIF) is set (update interrupt is pending).
  * @rmtoll SR           UIF           TIM_IsActiveFlag_UPDATE
  * @param  TIMx Timer instance
  * @param  Flag:
  *         @arg @ref TIM_SR_UIF
  *         @arg @ref TIM_SR_CC1IF
  *         @arg @ref TIM_SR_CC2IF
  *         @arg @ref TIM_SR_CC3IF
  *         @arg @ref TIM_SR_CC4IF
  *         @arg @ref TIM_SR_CC5IF
  *         @arg @ref TIM_SR_CC6IF
  *         @arg @ref TIM_SR_COMIF
  *         @arg @ref TIM_SR_TIF
  *         @arg @ref TIM_SR_BIF
  *         @arg @ref TIM_SR_B2IF
  *         @arg @ref TIM_SR_CC1OF
  *         @arg @ref TIM_SR_CC2OF
  *         @arg @ref TIM_SR_CC3OF
  *         @arg @ref TIM_SR_CC4OF
  *         @arg @ref TIM_SR_SBIF
  *         @arg @ref TIM_SR_TERRF
  *         @arg @ref TIM_SR_IERRF
  *         @arg @ref TIM_SR_DIRF
  *         @arg @ref TIM_SR_IDXF
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t TIM_Get_Flag(TIM_TypeDef *TIMx, uint32_t Flag)
{
  return ((READ_BIT(TIMx->SR, Flag) == (Flag)) ? 1UL : 0UL);
}


/**
  * @brief  Enable update interrupt (UIE).
  * @rmtoll DIER         UIE           TIM_EnableIT_UPDATE
  * @param  TIMx Timer instance
  * @param  IT:
  *         @arg @ref TIM_DIER_UIE
  *         @arg @ref TIM_DIER_CC1IE
  *         @arg @ref TIM_DIER_CC2IE
  *         @arg @ref TIM_DIER_CC3IE
  *         @arg @ref TIM_DIER_CC4IE
  *         @arg @ref TIM_DIER_COMIE
  *         @arg @ref TIM_DIER_TIE
  *         @arg @ref TIM_DIER_BIE
  *         @arg @ref TIM_DIER_TERRIE
  *         @arg @ref TIM_DIER_IERRIE
  *         @arg @ref TIM_DIER_DIRIE
  *         @arg @ref TIM_DIER_IDXIE
  * @retval None
  */
__STATIC_INLINE void TIM_Enable_IT(TIM_TypeDef *TIMx, uint32_t IT)
{
  SET_BIT(TIMx->DIER, IT);
}

/**
  * @brief  Disable update interrupt (UIE).
  * @rmtoll DIER         UIE           TIM_DisableIT_UPDATE
  * @param  TIMx Timer instance
  * @param  IT:
  *         @arg @ref TIM_DIER_UIE
  *         @arg @ref TIM_DIER_CC1IE
  *         @arg @ref TIM_DIER_CC2IE
  *         @arg @ref TIM_DIER_CC3IE
  *         @arg @ref TIM_DIER_CC4IE
  *         @arg @ref TIM_DIER_COMIE
  *         @arg @ref TIM_DIER_TIE
  *         @arg @ref TIM_DIER_BIE
  *         @arg @ref TIM_DIER_TERRIE
  *         @arg @ref TIM_DIER_IERRIE
  *         @arg @ref TIM_DIER_DIRIE
  *         @arg @ref TIM_DIER_IDXIE
  * @retval None
  */
__STATIC_INLINE void TIM_Disable_IT(TIM_TypeDef *TIMx, uint32_t IT)
{
  CLEAR_BIT(TIMx->DIER, IT);
}

/**
  * @brief  Indicates whether the update interrupt (UIE) is enabled.
  * @rmtoll DIER         UIE           TIM_IsEnabledIT_UPDATE
  * @param  TIMx Timer instance
  * @param  IT:
  *         @arg @ref TIM_DIER_UIE
  *         @arg @ref TIM_DIER_CC1IE
  *         @arg @ref TIM_DIER_CC2IE
  *         @arg @ref TIM_DIER_CC3IE
  *         @arg @ref TIM_DIER_CC4IE
  *         @arg @ref TIM_DIER_COMIE
  *         @arg @ref TIM_DIER_TIE
  *         @arg @ref TIM_DIER_BIE
  *         @arg @ref TIM_DIER_TERRIE
  *         @arg @ref TIM_DIER_IERRIE
  *         @arg @ref TIM_DIER_DIRIE
  *         @arg @ref TIM_DIER_IDXIE
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t TIM_Get_IT(TIM_TypeDef *TIMx, uint32_t IT)
{
  return ((READ_BIT(TIMx->DIER, IT) == (IT)) ? 1UL : 0UL);
}



/**
  * @brief  Generate an update event.
  * @rmtoll EGR          UG            TIM_GenerateEvent_UPDATE
  * @param  TIMx Timer instance
  * @param  IT:
  *         @arg @ref TIM_EGR_UG
  *         @arg @ref TIM_EGR_CC1G
  *         @arg @ref TIM_EGR_CC2G
  *         @arg @ref TIM_EGR_CC3G
  *         @arg @ref TIM_EGR_CC4G
  *         @arg @ref TIM_EGR_COMG
  *         @arg @ref TIM_EGR_TG
  *         @arg @ref TIM_EGR_BG
  *         @arg @ref TIM_EGR_B2G
  * @retval None
  */
__STATIC_INLINE void TIM_Set_GenerateEvent(TIM_TypeDef *TIMx, uint32_t TIMEVENT)
{
  SET_BIT(TIMx->EGR, TIMEVENT);
}


/**
  * @function  TIM_Set_BreakPolarity
  * @brief  Configure the break input
  * @param  TIMx:
            @arg TIM Instance
  * @param  BreakPolarity This parameter can be one of the following values:
  *         @arg @ref TIM_BREAK2_POLARITY_LOW
  *         @arg @ref TIM_BREAK2_POLARITY_HIGH
  * @retval None
  */
__STATIC_INLINE void TIM_Set_Break2Polarity(TIM_TypeDef *TIMx,uint32_t BreakPolarity)
{
  MODIFY_REG(TIMx->BDTR, TIM_BDTR_BK2P, BreakPolarity);
}


/**
  * @brief  Set the polarity of the break signal for the timer break input.
  * @note Macro IS_TIM_BREAKSOURCE_INSTANCE(TIMx) can be used to check whether
  *       or not a timer instance allows for break input selection.
  * @rmtoll AF1          BKINP         TIM_SetBreakInputSourcePolarity\n
  *         AF1          BKCMP1P       TIM_SetBreakInputSourcePolarity\n
  *         AF1          BKCMP2P       TIM_SetBreakInputSourcePolarity\n
  *         AF2          BK2INP        TIM_SetBreakInputSourcePolarity\n
  *         AF2          BK2CMP1P      TIM_SetBreakInputSourcePolarity\n
  *         AF2          BK2CMP2P      TIM_SetBreakInputSourcePolarity\n
  * @param  TIMx Timer instance
  * @param  BreakInput This parameter can be one of the following values:
  *         @arg @ref TIM_BREAK_INPUT_BKIN
  *         @arg @ref TIM_BREAK_INPUT_BKIN2
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref TIM_BKIN_SOURCE_BKIN
  *         @arg @ref TIM_BKIN_SOURCE_BKCOMP1
  *         @arg @ref TIM_BKIN_SOURCE_BKCOMP2
  * @param  Polarity This parameter can be one of the following values:
  *         @arg @ref TIM_BKIN_POLARITY_NoInvert
  *         @arg @ref TIM_BKIN_POLARITY_Invert
  * @retval None
  */
__STATIC_INLINE void TIM_Set_BreakInputSourcePolarity(TIM_TypeDef *TIMx, uint32_t BreakInput, uint32_t Source, uint32_t Polarity)
{
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->AF1) + BreakInput));
  MODIFY_REG(*pReg, (TIM_AF1_BKINP << TIM_POSITION_BRK_SOURCE), (Polarity << TIM_POSITION_BRK_SOURCE));
}


/**
  * @brief  Disable the signals connected to the designated timer break input.
  * @note Macro IS_TIM_BREAKSOURCE_INSTANCE(TIMx) can be used to check whether
  *       or not a timer instance allows for break input selection.
  * @rmtoll AF1          BKINE         TIM_DisableBreakInputSource\n
  *         AF1          BKCMP1E       TIM_DisableBreakInputSource\n
  *         AF1          BKCMP2E       TIM_DisableBreakInputSource\n
  *         AF2          BKINE         TIM_DisableBreakInputSource\n
  *         AF2          BKCMP1E       TIM_DisableBreakInputSource\n
  *         AF2          BKCMP2E       TIM_DisableBreakInputSource\n
  * @param  TIMx Timer instance
  * @param  BreakInput This parameter can be one of the following values:
  *         @arg @ref TIM_BREAK_INPUT_BKIN
  *         @arg @ref TIM_BREAK_INPUT_BKIN2
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref TIM_BKIN_SOURCE_BKIN
  *         @arg @ref TIM_BKIN_SOURCE_BKCOMP1
  *         @arg @ref TIM_BKIN_SOURCE_BKCOMP2
  *
  *         (*)  Value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void TIM_Disable_BreakInputSource(TIM_TypeDef *TIMx, uint32_t BreakInput, uint32_t Source)
{
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->AF1) + BreakInput));
  CLEAR_BIT(*pReg, Source);
}

/**
  * @brief  Enable the signals connected to the designated timer break input.
  * @note Macro IS_TIM_BREAKSOURCE_INSTANCE(TIMx) can be used to check whether
  *       or not a timer instance allows for break input selection.
  * @rmtoll AF1          BKINE         TIM_EnableBreakInputSource\n
  *         AF1          BKCMP1E       TIM_EnableBreakInputSource\n
  *         AF1          BKCMP2E       TIM_EnableBreakInputSource\n
  *         AF2          BK2NE         TIM_EnableBreakInputSource\n
  *         AF2          BK2CMP1E      TIM_EnableBreakInputSource\n
  *         AF2          BK2CMP2E      TIM_EnableBreakInputSource\n
  * @param  TIMx Timer instance
  * @param  BreakInput This parameter can be one of the following values:
  *         @arg @ref TIM_BREAK_INPUT_BKIN
  *         @arg @ref TIM_BREAK_INPUT_BKIN2
  * @param  Source This parameter can be one of the following values:
  *         @arg @ref TIM_BKIN_SOURCE_BKIN
  *         @arg @ref TIM_BKIN_SOURCE_BKCOMP1
  *         @arg @ref TIM_BKIN_SOURCE_BKCOMP2
  *
  *         (*)  Value not defined in all devices.
  * @retval None
  */
__STATIC_INLINE void TIM_Enable_BreakInputSource(TIM_TypeDef *TIMx, uint32_t BreakInput, uint32_t Source)
{
  __IO uint32_t *pReg = (__IO uint32_t *)((uint32_t)((uint32_t)(&TIMx->AF1) + BreakInput));
  SET_BIT(*pReg, Source);
}

/**
  * @function  TIM_Enable_Break_Control
  * @brief  Enable the TIM Break Control.
  * @param  TIMx:
  *         @arg TIM Instance
  * @retval None
  */
__STATIC_INLINE void TIM_Enable_Break_Control(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->BIC, TIM_BICE_EN);
}

/**
  * @function  TIM_Disable_Break_Control
  * @brief  Disable the TIM Break Control.
  * @param  TIMx:
  *         @arg TIM Instance
  * @retval None
  */
__STATIC_INLINE void TIM_Disable_Break_Control(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->BIC, TIM_BICE_EN);
}

/**
  * @function  TIM_Set_CH1Break_Invalid
  * @brief  Configure the CH1Break Invalid
  * @param  TIMx:
  *         @arg TIM Instance
  * @retval None
  */
__STATIC_INLINE void TIM_Set_CH1Break_Invalid(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->BIC, TIM_BICS_CH1_EN);
}

/**
  * @function  TIM_Set_CH2Break_Invalid
  * @brief  Configure the CH2Break Invalid
  * @param  TIMx:
  *         @arg TIM Instance
  * @retval None
  */
__STATIC_INLINE void TIM_Set_CH2Break_Invalid(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->BIC, TIM_BICS_CH2_EN);
}

/**
  * @function  TIM_Set_CH3Break_Invalid
  * @brief  Configure the CH3Break Invalid
  * @param  TIMx:
  *         @arg TIM Instance
  * @retval None
  */
__STATIC_INLINE void TIM_Set_CH3Break_Invalid(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->BIC, TIM_BICS_CH3_EN);
}


/**
  * @function  TIM_Set_CH4Break_Invalid
  * @brief  Configure the CH4Break Invalid
  * @param  TIMx:
  *         @arg TIM Instance
  * @retval None
  */
__STATIC_INLINE void TIM_Set_CH4Break_Invalid(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->BIC, TIM_BICS_CH4_EN);
}

/**
  * @function  TIM_Set_CH5Break_Invalid
  * @brief  Configure the CH5Break Invalid
  * @param  TIMx:
  *         @arg TIM Instance
  * @retval None
  */
__STATIC_INLINE void TIM_Set_CH5Break_Invalid(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->BIC, TIM_BICS_CH5_EN);
}

/**
  * @function  TIM_Set_CH6Break_Invalid
  * @brief  Configure the CH6Break Invalid
  * @param  TIMx:
  *         @arg TIM Instance
  * @retval None
  */
__STATIC_INLINE void TIM_Set_CH6Break_Invalid(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->BIC, TIM_BICS_CH6_EN);
}

/**
  * @function  TIM_Set_CH1Break_valid
  * @brief  Configure the CH1Break valid
  * @param  TIMx:
  *         @arg TIM Instance
  * @retval None
  */
__STATIC_INLINE void TIM_Set_CH1Break_Valid(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->BIC, TIM_BICS_CH1_EN);
}

/**
  * @function  TIM_Set_CH2Break_valid
  * @brief  Configure the CH2Break valid
  * @param  TIMx:
  *         @arg TIM Instance
  * @retval None
  */
__STATIC_INLINE void TIM_Set_CH2Break_Valid(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->BIC, TIM_BICS_CH2_EN);
}

/**
  * @function  TIM_Set_CH3Break_valid
  * @brief  Configure the CH3Break valid
  * @param  TIMx:
  *         @arg TIM Instance
  * @retval None
  */
__STATIC_INLINE void TIM_Set_CH3Break_Valid(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->BIC, TIM_BICS_CH3_EN);
}

/**
  * @function  TIM_Set_CH4Break_valid
  * @brief  Configure the CH4Break valid
  * @param  TIMx:
  *         @arg TIM Instance
  * @retval None
  */
__STATIC_INLINE void TIM_Set_CH4Break_Valid(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->BIC, TIM_BICS_CH4_EN);
}

/**
  * @function  TIM_Set_CH5Break_valid
  * @brief  Configure the CH5Break valid
  * @param  TIMx:
  *         @arg TIM Instance
  * @retval None
  */
__STATIC_INLINE void TIM_Set_CH5Break_Valid(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->BIC, TIM_BICS_CH5_EN);
}

/**
  * @function  TIM_Set_CH6Break_valid
  * @brief  Configure the CH6Break valid
  * @param  TIMx:
  *         @arg TIM Instance
  * @retval None
  */
__STATIC_INLINE void TIM_Set_CH6Break_Valid(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->BIC, TIM_BICS_CH6_EN);
}

/**
  * @function  TIM_Enable_CCR1N
  * @brief  Enable the CCR1N function.
  * @param  TIMx:
            @arg TIM Instance
  * @retval None
  */
__STATIC_INLINE void TIM_Enable_CCR1N(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->CCR1N, TIM_CCR1N_EN);
}

/**
  * @function  TIM_Disable_CCR1N
  * @brief  Disable the CCR1N function.
  * @param  TIMx:
            @arg TIM Instance
  * @retval None
  */
__STATIC_INLINE void TIM_Disable_CCR1N(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->CCR1N, TIM_CCR1N_EN);
}

/**
  * @function  TIM_Enable_CCR2N
  * @brief  Enable the CCR2N function.
  * @param  TIMx:
            @arg TIM Instance
  * @retval None
  */
__STATIC_INLINE void TIM_Enable_CCR2N(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->CCR2N, TIM_CCR2N_EN);
}

/**
  * @function  TIM_Disable_CCR2N
  * @brief  Disable the CCR2N function.
  * @param  TIMx:
            @arg TIM Instance
  * @retval None
  */
__STATIC_INLINE void TIM_Disable_CCR2N(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->CCR2N, TIM_CCR2N_EN);
}

/**
  * @function  TIM_Enable_CCR3N
  * @brief  Enable the CCR3N function.
  * @param  TIMx:
            @arg TIM Instance
  * @retval None
  */
__STATIC_INLINE void TIM_Enable_CCR3N(TIM_TypeDef *TIMx)
{
  SET_BIT(TIMx->CCR3N, TIM_CCR3N_EN);
}

/**
  * @function  TIM_Disable_CCR3N
  * @brief  Disable the CCR3N function.
  * @param  TIMx:
            @arg TIM Instance
  * @retval None
  */
__STATIC_INLINE void TIM_Disable_CCR3N(TIM_TypeDef *TIMx)
{
  CLEAR_BIT(TIMx->CCR3N, TIM_CCR3N_EN);
}


void TIM_DeInit(TIM_TypeDef *TIMx);
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef *TIM_InitStruct);
void TIM_OCStructInit(TIM_OCInitTypeDef *TIM_OC_InitStruct);
void TIM_ICStructInit(TIM_ICInitTypeDef *TIM_ICInitStruct);
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef *TIM_BDTRInitStruct);
void TIM_TimeBaseInit(TIM_TypeDef *TIMx, TIM_TimeBaseInitTypeDef *TIM_InitStruct);
void TIM_OC1Init(TIM_TypeDef *TIMx, TIM_OCInitTypeDef *TIM_OCInitStruct);
void TIM_OC2Init(TIM_TypeDef *TIMx, TIM_OCInitTypeDef *TIM_OCInitStruct);
void TIM_OC3Init(TIM_TypeDef *TIMx, TIM_OCInitTypeDef *TIM_OCInitStruct);
void TIM_OC4Init(TIM_TypeDef *TIMx, TIM_OCInitTypeDef *TIM_OCInitStruct);
void TIM_OC5Init(TIM_TypeDef *TIMx, TIM_OCInitTypeDef *TIM_OCInitStruct);
void TIM_OC6Init(TIM_TypeDef *TIMx, TIM_OCInitTypeDef *TIM_OCInitStruct);
void TIM_ICInit(TIM_TypeDef *TIMx, TIM_ICInitTypeDef *TIM_IC_InitStruct);
void TIM_BDTRInit(TIM_TypeDef *TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct);
void TIM_ENCODERInit(TIM_TypeDef *TIMx, TIM_ENCODER_InitTypeDef *TIM_EncoderInitStruct);
void TIM_HALLSENSOR_StructInit(TIM_HALLSENSOR_InitTypeDef *TIM_HallSensorInitStruct);
void TIM_HALLSENSOR_Init(TIM_TypeDef *TIMx, TIM_HALLSENSOR_InitTypeDef *TIM_HallSensorInitStruct);
void TIM_OC_Init(TIM_TypeDef *TIMx, uint32_t Channel, TIM_OCInitTypeDef *TIM_OC_InitStruct);
void TIM_ENCODER_StructInit(TIM_ENCODER_InitTypeDef *TIM_EncoderInitStruct);
void TIM_Set_OC_Output(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t Configuration);
void TIM_IC_Config(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t Configuration);
void TIM_Set_TI1(TIM_TypeDef *TIMx, TIM_ICInitTypeDef *TIM_ICInitStruct);
void TIM_Set_TI2(TIM_TypeDef *TIMx, TIM_ICInitTypeDef *TIM_ICInitStruct);
void TIM_Set_TI3(TIM_TypeDef *TIMx, TIM_ICInitTypeDef *TIM_ICInitStruct);
void TIM_Set_TI4(TIM_TypeDef *TIMx, TIM_ICInitTypeDef *TIM_ICInitStruct);


#ifdef __cplusplus
}
#endif

#endif /* __rx32h51xx_TIM_H__ */
