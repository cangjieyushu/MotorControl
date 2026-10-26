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
* File         : rx32h6xx_me.h
* By           : RX_SD_Team
* Version      : V1.0.0
* Description  : Only rx32h6xx
*********************************************************************************************************
*/
#ifndef _rx32h6xx_ME_H
#define _rx32h6xx_ME_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rx32h6xx.h"

/*******************  Bit definition for ME_CR register  *********************/
#define ME_CR_FUN                 BIT0
#define ME_CR_SN                  BIT4
#define ME_CR_CALF                BIT30
#define ME_CR_BSY                 BIT31


#define ME_FUN_DIV                0
#define ME_FUN_SQRT               BIT0

/*******************  Bit definition for ME_ARG1 register  *********************/
#define ME_ARG1_RES1             0xffffffff

/*******************  Bit definition for ME_ARG2 register  *********************/
#define ME_ARG2_RES2             0xffffffff

/*******************  Bit definition for ME_MCYC register  *********************/
#define ME_MCYC                  0x0000000f


int32_t  ME_SDIV(int32_t ARG1, int32_t ARG2);
uint32_t ME_UDIV(uint32_t ARG1, uint32_t ARG2);
uint32_t ME_SQRT(uint32_t ARG1);

#ifdef __cplusplus
}
#endif

#endif /* __rx32h6xx_ME_H__ */

