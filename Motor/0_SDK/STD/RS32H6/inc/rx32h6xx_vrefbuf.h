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
* File         : rx32h6xx_vrefbuf.h
* By           : RX_SD_Team
* Description  : Only rx32h6xx
*********************************************************************************************************
*/
#ifndef __rx32h6xx_VREFBUF_H__
#define __rx32h6xx_VREFBUF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "rx32h6xx.h"

/******************************************************************************/
/*                                                                            */
/*                       VREFBUF calculation unit (VREFBUF)                   */
/*                                                                            */
/******************************************************************************/

#if defined(VREFBUF)

/** @defgroup VREFBUF  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/*******************  Bit definition for VREFBUF_CSR register  *********************/
#define VREFBUF_CSR_ENVR_Pos               (0U)
#define VREFBUF_CSR_ENVR_Msk               (0x1U << VREFBUF_CSR_ENVR_Pos)     
#define VREFBUF_CSR_ENVR                   VREFBUF_CSR_ENVR_Msk    

#define VREFBUF_CSR_HIZ_Pos                (1U)
#define VREFBUF_CSR_HIZ_Msk                (0x1U << VREFBUF_CSR_HIZ_Pos)     
#define VREFBUF_CSR_HIZ                    VREFBUF_CSR_HIZ_Msk   

#define VREFBUF_CSR_VRR_Pos                (3U)
#define VREFBUF_CSR_VRR_Msk                (0x1U << VREFBUF_CSR_VRR_Pos)     
#define VREFBUF_CSR_VRR                    VREFBUF_CSR_VRR_Msk  

#define VREFBUF_CSR_VRS_Pos                (4U)
#define VREFBUF_CSR_VRS_Msk                (0x1U << VREFBUF_CSR_VRS_Pos)     
#define VREFBUF_CSR_VRS                    VREFBUF_CSR_VRS_Msk 

#define VREFBUF_CSR_2p5V                   0 
#define VREFBUF_CSR_2p8V                   VREFBUF_CSR_VRS 

/*******************  Bit definition for VREFBUF_CCR register  ********************/
#define VREFBUF_CCR_TRIM_Pos                (0U)
#define VREFBUF_CCR_TRIM_Msk                (0xFU << VREFBUF_CCR_TRIM_Pos)     
#define VREFBUF_CCR_TRIM                    VREFBUF_CCR_TRIM_Msk 


/**
  * @brief  Voltage reference buffer mode enable.
  * @param  None
  * @retval None
  */
__STATIC_INLINE void VREFBUF_Enable_ENVR(void)
{
  SET_BIT(VREFBUF->CSR, VREFBUF_CSR_ENVR);
}


/**
  * @brief  Voltage reference buffer mode Disable.
  * @param  None
  * @retval None
  */
__STATIC_INLINE void VREFBUF_Disable_ENVR(void)
{
  CLEAR_BIT(VREFBUF->CSR, VREFBUF_CSR_ENVR);
}

/**
  * @brief  High impedance mode enable.
  * @param  None
  * @retval None
  */
__STATIC_INLINE void VREFBUF_Enable_HIZ(void)
{
  SET_BIT(VREFBUF->CSR, VREFBUF_CSR_HIZ);
}


/**
  * @brief  High impedance mode Disable.
  * @param  None
  * @retval None
  */
__STATIC_INLINE void VREFBUF_Disable_HIZ(void)
{
  CLEAR_BIT(VREFBUF->CSR, VREFBUF_CSR_HIZ);
}


/**
  * @brief  check if  Voltage reference buffer ready
  * @param  None
  * @retval 1:Voltage reference buffer is ready, 0: Voltage reference buffer not ready
*/
__STATIC_INLINE uint32_t VREFBUF_Get_VRRRDY(void)
{
  return (READ_BIT(VREFBUF->CSR, VREFBUF_CSR_VRR) == (VREFBUF_CSR_VRR));
}


/**
  * @brief  Set Voltage reference scale
  * @param  Source:
            @arg VREFBUF_CSR_2p5V
            @arg VREFBUF_CSR_2p8V
  * @retval None
*/
__STATIC_INLINE void VREFBUF_Set_VRS(uint32_t Source)
{
  MODIFY_REG(VREFBUF->CSR, VREFBUF_CSR_VRS, Source);
}

/**
  * @brief  Specify Trimming code
  * @param  Trimming code between Min_Data=0 and Max_Data=0xF
  * @retval None
  */
__STATIC_INLINE void VREFBUF_Set_CCRTRIM(uint32_t TRIM)
{
  WRITE_REG(VREFBUF->CCR, TRIM);
}


#endif /* defined(VREFBUF) */

#ifdef __cplusplus
}
#endif

#endif /* __rx32h6xx_VREFBUF_H__ */

