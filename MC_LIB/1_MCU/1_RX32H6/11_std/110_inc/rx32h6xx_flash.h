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
* File         : rx32h6xx_flash.h
* By           : RX_SD_Team
* Description  : Only rx32h6xx
*********************************************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _rx32h6xx_FLASH_H
#define _rx32h6xx_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "rx32h6xx.h"

/** @addtogroup FLASH   */
   
#define assert_param(expr) ((void)0)
/** 
  * @brief  FLASH Status  
  */
typedef enum
{ 
  FLASH_BUSY = 1,
  FLASH_ERROR_PG,
  FLASH_ERROR_WRP,
  FLASH_COMPLETE,
  FLASH_TIMEOUT
}FLASH_Status;

#define FLASH_ACR_LATENCY_Pos               (0U)                               
#define FLASH_ACR_LATENCY_Msk               (0x7U << FLASH_ACR_LATENCY_Pos)    /*!< 0x00000007 */
#define FLASH_ACR_LATENCY                   FLASH_ACR_LATENCY_Msk              /*!< LATENCY[2:0] bits (Latency) */
#define FLASH_ACR_LATENCY_0                 (0x0U << FLASH_ACR_LATENCY_Pos)    /*!< 0x00000000 */
#define FLASH_ACR_LATENCY_1                 (0x1U << FLASH_ACR_LATENCY_Pos)    /*!< 0x00000001 */
#define FLASH_ACR_LATENCY_2                 (0x2U << FLASH_ACR_LATENCY_Pos)    /*!< 0x00000002 */
#define FLASH_ACR_LATENCY_3                 (0x3U << FLASH_ACR_LATENCY_Pos)    /*!< 0x00000003 */
     
#define FLASH_ACR_PRFTEN                     0x100

/******************  Bit definition for FLASH_KEYR register  ******************/
#define  FLASH_CRKEY1                       0x45670123                     /*!< CR Key1 */
#define  FLASH_CRKEY2                       0xCDEF89AB                     /*!< CR Key2 */

/*****************  Bit definition for FLASH_OPTKEYR register  ****************/
#define  FLASH_OPTKEY1                       0x08192A3B                    /*!< Option Byte Key1 */
#define  FLASH_OPTKEY2                       0x4C5D6E7F                    /*!< Option Byte Key2 */

/******************  Bit definition for FLASH_SR register  ********************/
#define FLASH_SR_EOP_Pos                    (0U)                               
#define FLASH_SR_EOP_Msk                    (0x1U << FLASH_SR_EOP_Pos)          /*!< 0x00000001 */
#define FLASH_SR_EOP                       FLASH_SR_EOP_Msk                   
#define FLASH_SR_OPERR_Pos                  (1U)                               
#define FLASH_SR_OPERR_Msk                  (0x1U << FLASH_SR_OPERR_Pos)        /*!< 0x00000002 */
#define FLASH_SR_OPERR                     FLASH_SR_OPERR_Msk                
#define FLASH_SR_PROGERR_Pos                (3U)                               
#define FLASH_SR_PROGERR_Msk               (0x1U << FLASH_SR_PROGERR_Pos)      /*!< 0x00000008 */
#define FLASH_SR_PROGERR                   FLASH_SR_PROGERR_Msk              
#define FLASH_SR_WRPRTERR_Pos               (4U)                               
#define FLASH_SR_WRPRTERR_Msk              (0x1U << FLASH_SR_WRPRTERR_Pos)       /*!< 0x00000010 */
#define FLASH_SR_WRPRTERR                  FLASH_SR_WRPRTERR_Msk                   
#define FLASH_SR_PGAERR_Pos                 (5U)                               
#define FLASH_SR_PGAERR_Msk                (0x1U << FLASH_SR_PGAERR_Pos)       /*!< 0x00000020 */
#define FLASH_SR_PGAERR                    FLASH_SR_PGAERR_Msk 
#define FLASH_SR_SIZERR_Pos               (6U)
#define FLASH_SR_SIZERR_Msk               (0x1UL << FLASH_SR_SIZERR_Pos)       /*!< 0x00000040 */
#define FLASH_SR_SIZERR                   FLASH_SR_SIZERR_Msk
#define FLASH_SR_PGSERR_Pos               (7U)
#define FLASH_SR_PGSERR_Msk               (0x1UL << FLASH_SR_PGSERR_Pos)       /*!< 0x00000080 */
#define FLASH_SR_PGSERR                   FLASH_SR_PGSERR_Msk
#define FLASH_SR_RDERR_Pos                (14U)
#define FLASH_SR_RDERR_Msk                (0x1UL << FLASH_SR_RDERR_Pos)        /*!< 0x00004000 */
#define FLASH_SR_RDERR                    FLASH_SR_RDERR_Msk
#define FLASH_SR_OPTVERR_Pos              (15U)
#define FLASH_SR_OPTVERR_Msk              (0x1UL << FLASH_SR_OPTVERR_Pos)      /*!< 0x00008000 */
#define FLASH_SR_OPTVERR                  FLASH_SR_OPTVERR_Msk
#define FLASH_SR_BSY_Pos                  (16U)
#define FLASH_SR_BSY_Msk                  (0x1UL << FLASH_SR_BSY_Pos)          /*!< 0x00010000 */
#define FLASH_SR_BSY                      FLASH_SR_BSY_Msk

/*******************  Bit definition for FLASH_CR register  *******************/
#define FLASH_CR_PG_Pos                     (0U)                               
#define FLASH_CR_PG_Msk                     (0x1U << FLASH_CR_PG_Pos)          /*!< 0x00000001 */
#define FLASH_CR_PG                         FLASH_CR_PG_Msk                    /*!< Programming */
#define FLASH_CR_PER_Pos                    (1U)                               
#define FLASH_CR_PER_Msk                    (0x1U << FLASH_CR_PER_Pos)         /*!< 0x00000002 */
#define FLASH_CR_PER                        FLASH_CR_PER_Msk                   /*!< Page Erase */
#define FLASH_CR_MER_Pos                    (2U)                               
#define FLASH_CR_MER_Msk                    (0x1U << FLASH_CR_MER_Pos)         /*!< 0x00000004 */
#define FLASH_CR_MER                        FLASH_CR_MER_Msk                   /*!< Mass Erase */
#define FLASH_CR_PNB_Pos                    (3U)
#define FLASH_CR_PNB_Msk                    (0x3FUL << FLASH_CR_PNB_Pos)       /*!< 0x000001F8 */
#define FLASH_CR_PNB                        FLASH_CR_PNB_Msk
#define FLASH_CR_SYSWRE_Pos                 (14U)
#define FLASH_CR_SYSWRE_Msk                 (0x1UL << FLASH_CR_SYSWRE_Pos)       /*!< 0x00002000 */
#define FLASH_CR_SYSWRE                     FLASH_CR_SYSWRE_Msk
#define FLASH_CR_STRT_Pos                   (16U)
#define FLASH_CR_STRT_Msk                   (0x1UL << FLASH_CR_STRT_Pos)         /*!< 0x00010000 */
#define FLASH_CR_STRT                       FLASH_CR_STRT_Msk
#define FLASH_CR_OPTSTRT_Pos                (17U)
#define FLASH_CR_OPTSTRT_Msk                (0x1UL << FLASH_CR_OPTSTRT_Pos)      /*!< 0x00020000 */
#define FLASH_CR_OPTSTRT                    FLASH_CR_OPTSTRT_Msk
#define FLASH_CR_EOPIE_Pos                (24U)
#define FLASH_CR_EOPIE_Msk                (0x1UL << FLASH_CR_EOPIE_Pos)        /*!< 0x01000000 */
#define FLASH_CR_EOPIE                    FLASH_CR_EOPIE_Msk
#define FLASH_CR_ERRIE_Pos                (25U)
#define FLASH_CR_ERRIE_Msk                (0x1UL << FLASH_CR_ERRIE_Pos)        /*!< 0x02000000 */
#define FLASH_CR_ERRIE                    FLASH_CR_ERRIE_Msk
#define FLASH_CR_RDERRIE_Pos              (26U)
#define FLASH_CR_RDERRIE_Msk              (0x1UL << FLASH_CR_RDERRIE_Pos)      /*!< 0x04000000 */
#define FLASH_CR_RDERRIE                  FLASH_CR_RDERRIE_Msk
#define FLASH_CR_OBL_LAUNCH_Pos           (27U)
#define FLASH_CR_OBL_LAUNCH_Msk           (0x1UL << FLASH_CR_OBL_LAUNCH_Pos)   /*!< 0x08000000 */
#define FLASH_CR_OBL_LAUNCH               FLASH_CR_OBL_LAUNCH_Msk
#define FLASH_CR_OPTLOCK_Pos              (30U)
#define FLASH_CR_OPTLOCK_Msk              (0x1UL << FLASH_CR_OPTLOCK_Pos)      /*!< 0x40000000 */
#define FLASH_CR_OPTLOCK                  FLASH_CR_OPTLOCK_Msk
#define FLASH_CR_LOCK_Pos                 (31U)
#define FLASH_CR_LOCK_Msk                 (0x1UL << FLASH_CR_LOCK_Pos)         /*!< 0x80000000 */
#define FLASH_CR_LOCK                     FLASH_CR_LOCK_Msk

/******************  Bit definition for FLASH_OPTR register  *******************/
#define FLASH_OPTR_RDP_Pos                (0U)
#define FLASH_OPTR_RDP_Msk                (0xFFUL << FLASH_OPTR_RDP_Pos)       /*!< 0x000000FF */
#define FLASH_OPTR_RDP                    FLASH_OPTR_RDP_Msk
#define FLASH_OPTR_nRST_STOP_Pos          (12U)
#define FLASH_OPTR_nRST_STOP_Msk          (0x1UL << FLASH_OPTR_nRST_STOP_Pos)  /*!< 0x00001000 */
#define FLASH_OPTR_nRST_STOP              FLASH_OPTR_nRST_STOP_Msk
#define FLASH_OPTR_nRST_STDBY_Pos         (13U)
#define FLASH_OPTR_nRST_STDBY_Msk         (0x1UL << FLASH_OPTR_nRST_STDBY_Pos) /*!< 0x00002000 */
#define FLASH_OPTR_nRST_STDBY             FLASH_OPTR_nRST_STDBY_Msk
#define FLASH_OPTR_IWDG_SW_Pos            (16U)
#define FLASH_OPTR_IWDG_SW_Msk            (0x1UL << FLASH_OPTR_IWDG_SW_Pos)    /*!< 0x00010000 */
#define FLASH_OPTR_IWDG_SW                FLASH_OPTR_IWDG_SW_Msk
#define FLASH_OPTR_IWDG_STOP_Pos          (17U)
#define FLASH_OPTR_IWDG_STOP_Msk          (0x1UL << FLASH_OPTR_IWDG_STOP_Pos)  /*!< 0x00020000 */
#define FLASH_OPTR_IWDG_STOP              FLASH_OPTR_IWDG_STOP_Msk
#define FLASH_OPTR_IWDG_STDBY_Pos         (18U)
#define FLASH_OPTR_IWDG_STDBY_Msk         (0x1UL << FLASH_OPTR_IWDG_STDBY_Pos) /*!< 0x00040000 */
#define FLASH_OPTR_IWDG_STDBY             FLASH_OPTR_IWDG_STDBY_Msk
#define FLASH_OPTR_WWDG_SW_Pos            (19U)
#define FLASH_OPTR_WWDG_SW_Msk            (0x1UL << FLASH_OPTR_WWDG_SW_Pos)    /*!< 0x00080000 */
#define FLASH_OPTR_WWDG_SW                FLASH_OPTR_WWDG_SW_Msk
#define FLASH_OPTR_BFB2_Pos               (20U)
#define FLASH_OPTR_BFB2_Msk               (0x1UL << FLASH_OPTR_BFB2_Pos)      /*!< 0x00100000 */
#define FLASH_OPTR_BFB2                   FLASH_OPTR_BFB2_Msk
#define FLASH_OPTR_ECC_Pos                (21U)
#define FLASH_OPTR_ECC_Msk                (0x1UL << FLASH_OPTR_ECC_Pos)       /*!< 0x00200000 */
#define FLASH_OPTR_ECC                    FLASH_OPTR_ECC_Msk
#define FLASH_OPTR_Nboot1_Pos             (23U)
#define FLASH_OPTR_Nboot1_Msk             (0x1UL << FLASH_OPTR_Nboot1_Pos)      /*!< 0x00800000 */
#define FLASH_OPTR_Nboot1                 FLASH_OPTR_Nboot1_Msk
#define FLASH_OPTR_nSWBOOT0_Pos           (26U)
#define FLASH_OPTR_nSWBOOT0_Msk           (0x1UL << FLASH_OPTR_nSWBOOT0_Pos)     /*!< 0x04000000 */
#define FLASH_OPTR_nSWBOOT0               FLASH_OPTR_nSWBOOT0_Msk
#define FLASH_OPTR_nBOOT0_Pos             (27U)
#define FLASH_OPTR_nBOOT0_Msk             (0x1UL << FLASH_OPTR_nBOOT0_Pos) /*!< 0x08000000 */
#define FLASH_OPTR_nBOOT0                 FLASH_OPTR_nBOOT0_Msk
#define FLASH_OPTR_nRST_MODE_Pos          (28U)
#define FLASH_OPTR_nRST_MODE_Msk          (0x1UL << FLASH_OPTR_nRST_MODE_Pos)  /*!< 0x10000000 */
#define FLASH_OPTR_nRST_MODE               FLASH_OPTR_nRST_MODE_Msk

/******************  Bit definition for FLASH_WRPR register  ******************/
#define FLASH_WRP1AR_WRP1A_STRT_Pos                  (0U)                               
#define FLASH_WRP1AR_WRP1A_STRT_Msk                  (0x1FFU << FLASH_WRP1AR_WRP1A_STRT_Pos)      /*!< 0x0000007F */
#define FLASH_WRP1AR_WRP1A_STRT                      FLASH_WRP1AR_WRP1A_STRT_Msk            
#define FLASH_WRP1AR_WRP1A_END_Pos                   (16U)                               
#define FLASH_WRP1AR_WRP1A_END_Msk                   (0x1FFU << FLASH_WRP1AR_WRP1A_END_Pos)       /*!< 0x007F0000 */
#define FLASH_WRP1AR_WRP1A_END                       FLASH_WRP1AR_WRP1A_END_Msk   
   
/* FLASH Keys */
#define RDP_Key                  ((uint16_t)0xBB)

/* FLASH BANK address */
#define FLASH_BANK1_END_ADDRESS   ((uint32_t)0x800FFFF)

/* Delay definition */   
#define EraseTimeout          ((uint32_t)0x000B0000)
#define ProgramTimeout        ((uint32_t)0x00002000)

#define FLASH_PAGE_SIZE                 0x400U  /* 1 KB */

/** @defgroup Flash_Latency  */
#define FLASH_Latency_0                ((uint32_t)0x00000000)  /*!< FLASH Zero Latency cycle */
#define FLASH_Latency_1                ((uint32_t)0x00000001)  /*!< FLASH One Latency cycle */
#define FLASH_Latency_2                ((uint32_t)0x00000002)  /*!< FLASH Two Latency cycles */
#define FLASH_Latency_3                ((uint32_t)0x00000003)  /*!< FLASH Three Latency cycles */
#define IS_FLASH_LATENCY(LATENCY) (((LATENCY) == FLASH_Latency_0) || \
                                   ((LATENCY) == FLASH_Latency_1) || \
                                   ((LATENCY) == FLASH_Latency_2))

#define IS_FLASH_WRPROT_PAGE(PAGE) (((PAGE) != 0x00000000))

#define IS_FLASH_ADDRESS(ADDRESS) (((ADDRESS) >= 0x08000000) && ((ADDRESS) < 0x080FFFFF))

#define IS_OB_DATA_ADDRESS(ADDRESS) (((ADDRESS) == 0x1FFFF804) || ((ADDRESS) == 0x1FFFF806))

#define IS_FLASH_IT(IT) ((((IT) & (uint32_t)0xFFFFEBFF) == 0x00000000) && (((IT) != 0x00000000)))

#define Read_HalfWord(ADDR) ( *(__IO uint16_t*)ADDR )

/**
  * @brief  Sets the code latency value.
  * @param  FLASH_Latency: specifies the FLASH Latency value.
  *     @arg FLASH_ACR_LATENCY_0
  *     @arg FLASH_ACR_LATENCY_1
  *     @arg FLASH_ACR_LATENCY_2
  *     @arg FLASH_ACR_LATENCY_3
  * @retval None
  */
__STATIC_INLINE void FLASH_Set_Latency(uint32_t FLASH_Latency)
{
  MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_Latency);
}

/**
  * @brief  Sets the code latency value.
  * @param  none
  * @retval FLASH_Latency: specifies the FLASH Latency value.
  *     @arg FLASH_ACR_LATENCY_0
  *     @arg FLASH_ACR_LATENCY_1
  *     @arg FLASH_ACR_LATENCY_2
  *     @arg FLASH_ACR_LATENCY_3
  */
__STATIC_INLINE uint32_t FLASH_Get_Latency( void )
{
  return (uint32_t)(READ_BIT(FLASH->ACR, FLASH_ACR_LATENCY));
}

/**
  * @brief  Enables the Prefetch.
  * @param  FLASH_PrefetchBuffer: specifies the Prefetch buffer status.
  *     @arg FLASH_ACR_PRFTEN_Enable
  * @retval None
  */
__STATIC_INLINE void FLASH_Enable_PRFTEN()
{
  /* Enable or disable the Prefetch Buffer */
  FLASH->ACR |= FLASH_ACR_PRFTEN;
}

/**
  * @brief  Read 4 bytes.
  * @param  None
  * @retval None.
  */
__STATIC_INLINE uint32_t FLASH_Read_Word(uint32_t ADDR)
{
  return *(__IO uint32_t*)ADDR ; 
}

/**
  * @brief  Returns the FLASH Write Protection Option Bytes Register value.
  * @param  None
  * @retval The FLASH Write Protection  Option Bytes Register value
  */
__STATIC_INLINE uint32_t FLASH_Get_WriteProtectionOptionByte(void)
{
  /* Return the Flash write protection Register value */
  return (uint32_t)(FLASH->WRP1AR);
}

/**
  * @brief  Checks whether the FLASH Prefetch Buffer status is set or not.
  * @param  None
  * @retval FLASH Prefetch Buffer Status (1 or 0).
  */
__STATIC_INLINE uint32_t FLASH_Get_PrefetchBufferStatus(void)
{
  return (uint32_t)( (READ_BIT(FLASH->ACR, FLASH_ACR_PRFTEN)) != 0); 
}

/**
  * @brief  Enables the specified FLASH interrupts.
  * @param  FLASH_IT: specifies the FLASH interrupt sources to be enabled or disabled.
  *     @arg FLASH_CR_ERRIE
  *     @arg FLASH_CR_EOPIE
  *     @arg FLASH_CR_RDERRIE
  * @retval None 
  */
__STATIC_INLINE void FLASH_Enable_IT(uint32_t FLASH_IT)
{
  /* Enable the interrupt sources */
  SET_BIT(FLASH->CR, FLASH_IT);
}

/**
  * @brief  Disables the specified FLASH interrupts.
  * @param  FLASH_IT: specifies the FLASH interrupt sources to be enabled or disabled.
  *     @arg FLASH_CR_ERRIE
  *     @arg FLASH_CR_EOPIE   
  *     @arg FLASH_CR_RDERRIE   
  * @retval None 
  */
__STATIC_INLINE void FLASH_Disable_IT(uint32_t FLASH_IT)
{
  /* Disable the interrupt sources */
  CLEAR_BIT(FLASH->CR, FLASH_IT);
}

/**
  * @brief  Get the specified FLASH interrupts.
  * @param  FLASH_IT: specifies the FLASH interrupt sources to be enabled or disabled.
  *     @arg FLASH_CR_ERRIE
  *     @arg FLASH_CR_EOPIE   
  *     @arg FLASH_CR_RDERRIE   
  * @retval (0 or 1) 
  */
__STATIC_INLINE uint32_t FLASH_Get_IT(uint32_t FLASH_IT)
{
   return (uint32_t)(READ_BIT(FLASH->CR, FLASH_IT) == (FLASH_IT));
}

/**
  * @brief  Checks whether the specified FLASH flag is set or not.
  * @param  FLASH_FLAG: specifies the FLASH flag to check.
  *     @arg FLASH_SR_BSY      
  *     @arg FLASH_SR_PGSERR   
  *     @arg FLASH_SR_WRPRTERR    
  *     @arg FLASH_SR_EOP         
  *     @arg FLASH_SR_OPTVERR
  * @retval The new state of FLASH_FLAG (1 or 0).
  */
__STATIC_INLINE uint32_t FLASH_Get_Flag(uint32_t FLASH_FLAG)
{
  return (uint32_t)(READ_BIT(FLASH->SR, FLASH_FLAG) != 0);
}

/**
  * @brief  Clears the FLASH's pending flags.
  * @param  FLASH_FLAG: specifies the FLASH flags to clear.      
  *     @arg FLASH_SR_PGSERR  
  *     @arg FLASH_SR_WRPRTERR 
  *     @arg FLASH_SR_RDERR        
  * @retval None
  */
__STATIC_INLINE void FLASH_Clear_Flag(uint32_t FLASH_FLAG)
{
  /* Clear the flags */
  FLASH->SR = FLASH_FLAG;
}

/** @defgroup FLASH_Exported_Functions   */
void FLASH_Unlock(void);
void FLASH_Lock(void);
void FLASH_Erase_Page(uint32_t Page_Address);
void FLASH_Erase_AllPages(void);
void FLASH_Set_UserOptionByte(uint32_t OB_USER);
void FLASH_Clear_UserOptionByte(uint32_t OB_USER);
void FLASH_Enable_WriteProtection(uint32_t START_Pages,uint32_t END_Pages);
void FLASH_Set_ReadOutProtection(FunctionalState NewState);
void FLASH_OB_Unlock(void);
void FLASH_OB_Lock(void);
void FLASH_Program_DoubleDoubleWord(uint32_t Address,uint32_t* buf);

#ifdef __cplusplus
}
#endif
#endif /* __rx32h6xx_FLASH_H__ */

