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
* File         : rx32h6xx_flash.c
* By           : RX_SD_Team
* Description  : Only rx32h6xx
*********************************************************************************************************
*/

#include "rx32h6xx_flash.h"

/**
  * @brief  Unlocks the FLASH Program Erase Controller.
  * @note 
  * @param  None
  * @retval None
  */
void FLASH_Unlock(void)
{
  /* Authorize the FPEC of Bank1 Access */
  FLASH->KEYR = FLASH_CRKEY1;
  FLASH->KEYR = FLASH_CRKEY2;
}

/**
  * @brief  Unlocks the FLASH Option Byte Controller.
  * @note 
  * @param  None
  * @retval None
  */
void FLASH_OB_Unlock(void)
{
  /* Authorize the FPEC of Bank1 Access */
  FLASH->OPTKEYR = FLASH_OPTKEY1;
  FLASH->OPTKEYR = FLASH_OPTKEY2;
}

/**
  * @brief  Locks the FLASH Program Erase Controller.
  * @note   
  * @param  None
  * @retval None
  */
void FLASH_Lock(void)
{
  /* Set the Lock Bit to lock the FPEC and the CR of  Bank1 */
  FLASH->CR |= FLASH_CR_LOCK;
}

/**
  * @brief  Locks the FLASH Option Byte Controller.
  * @note   
  * @param  None
  * @retval None
  */
void FLASH_OB_Lock(void)
{
  /* Set the Lock Bit to lock the FPEC and the CR of  Bank1 */
  FLASH->CR |= FLASH_CR_OPTLOCK;
}

/**
  * @brief  Erases a specified FLASH page.
  * @param  Page_Address: The page address to be erased.
  * @retval None.
  */
void FLASH_Erase_Page(uint32_t Page_Num)
{
  /* if the previous operation is completed, proceed to erase the page */
  /* Disable the PER Bit */
  FLASH_Clear_Flag(FLASH_SR_WRPRTERR|FLASH_SR_EOP); 
  CLEAR_BIT(FLASH->CR, FLASH_CR_PG);
  CLEAR_BIT(FLASH->CR, FLASH_CR_PER);


  /* Proceed to erase the page 0-63 */
  MODIFY_REG(FLASH->CR, FLASH_CR_PNB, ((Page_Num & 0xFFU) << 3U));
 

  SET_BIT(FLASH->CR, FLASH_CR_PER);
  SET_BIT(FLASH->CR, FLASH_CR_STRT);
	

  while((FLASH->SR & FLASH_SR_BSY) == FLASH_SR_BSY)
  {
  }; 

  /* Disable the PER Bit */
  CLEAR_BIT(FLASH->CR, (FLASH_CR_PER | FLASH_CR_PNB));
}

/**
  * @brief  Erases all FLASH pages.
  * @param  None
  * @retval None.
  */
void FLASH_Erase_AllPages(void)
{
  FLASH_Clear_Flag(FLASH_SR_WRPRTERR|FLASH_SR_EOP); 
  CLEAR_BIT(FLASH->CR, FLASH_CR_PG);
  CLEAR_BIT(FLASH->CR, FLASH_CR_PER);
	
	SET_BIT(FLASH->CR, FLASH_CR_MER);
  SET_BIT(FLASH->CR, FLASH_CR_STRT);
	
  while((FLASH->SR & FLASH_SR_BSY) == FLASH_SR_BSY)
  {
  }; 

  /* Disable the PER Bit */
  CLEAR_BIT(FLASH->CR, (FLASH_CR_MER | FLASH_CR_PNB));
}

/**
  * @brief  Program 16 bytes.
  * @param  None
  * @retval None.
  */
void FLASH_Program_DoubleDoubleWord(uint32_t Address, uint32_t* buf)
{

  /* Set PG bit */
  CLEAR_BIT(FLASH->CR, FLASH_CR_PER);
  if(FLASH_Get_Flag(FLASH_SR_EOP))
  {
    SET_BIT(FLASH->SR, FLASH_SR_EOP);
  };
  SET_BIT(FLASH->CR, FLASH_CR_PG);
  
  /* clear prften bit */
  uint32_t temp =0x0;
  temp = FLASH->ACR;
  CLEAR_BIT(FLASH->ACR,FLASH_ACR_PRFTEN);
  
  /* Program first word */
  *(uint32_t *)Address = buf[0];
  __ISB();
  /* Program second word */
  *(uint32_t *)(Address + 4U) =  buf[1];
  __ISB();
  /* Program third word */
  *(uint32_t *)(Address + 8U) =  buf[2];
  __ISB();
  /* Program four word */
  *(uint32_t *)(Address + 0xCU) =  buf[3];
	/* Wait for last operation to be completed */
	while((FLASH->SR & FLASH_SR_BSY) == FLASH_SR_BSY)
  {
  }; 
	
  CLEAR_BIT(FLASH->CR, FLASH_CR_PG);
    
  FLASH->ACR = temp;
}

/**
  * @brief  Enables or disables the read out protection.
  * @param  Newstate: new state of the ReadOut Protection.
  *     @arg ENABLE
  *     @arg DISABLE.
  * @retval None.
  */
void FLASH_Set_ReadOutProtection(FunctionalState NewState)
{
  /* unlock CR and OPTR key  */
  FLASH_Unlock();
  FLASH_OB_Unlock();

  if(NewState != DISABLE)
  {
    MODIFY_REG(FLASH->OPTR, FLASH_OPTR_RDP, 0xBB);
  }
  else
  {
    MODIFY_REG(FLASH->OPTR, FLASH_OPTR_RDP, 0xAA);   
  }  
    
	SET_BIT(FLASH->CR,FLASH_CR_OPTSTRT);
  
  while((FLASH->SR & FLASH_SR_BSY) == FLASH_SR_BSY)
  {
  }; 
	FLASH_Lock();
	FLASH_OB_Lock();      
      
}

/**
  * @brief  Write protects the desired pages
  * @param  FLASH_Pages: specifies the address of the pages to be write protected.
  *   This parameter can be:
  *     @arg For @b Medium-density_devices: value between FLASH_WRProt_Pages0to63
  *     @arg FLASH_WRProt_AllPages
  * @retval None.
  */
void FLASH_Enable_WriteProtection(uint32_t START_Pages,uint32_t END_Pages)
{
  FLASH_Unlock();
  FLASH_OB_Unlock();
  
	MODIFY_REG(FLASH->WRP1AR, FLASH_WRP1AR_WRP1A_STRT, START_Pages );  
	MODIFY_REG(FLASH->WRP1AR, FLASH_WRP1AR_WRP1A_END, END_Pages << 16 );        
  
  
	SET_BIT(FLASH->CR,FLASH_CR_OPTSTRT);
  
  while((FLASH->SR & FLASH_SR_BSY) == FLASH_SR_BSY)
  {
  }; 
	FLASH_Lock();
	FLASH_OB_Lock();
}

/**
  * @brief  Programs the FLASH User Option Byte: IWDG_SW / RST_STOP / RST_STDBY / IWDG_STDBY / IWDG_STOP / WWDG_SW / ECC / Nboot1 / nSWBOOT0 / nBOOT0.
  * @param  OB_USER:
  *     @arg FLASH_OPTR_nRST_STOP
  *     @arg FLASH_OPTR_nRST_STDBY
  *     @arg FLASH_OPTR_IWDG_SW
  *     @arg FLASH_OPTR_IWDG_STOP
  *     @arg FLASH_OPTR_IWDG_STDBY
  *     @arg FLASH_OPTR_WWDG_SW
  *     @arg FLASH_OPTR_BFB2
  *     @arg FLASH_OPTR_ECC
  *     @arg FLASH_OPTR_Nboot1
  *     @arg FLASH_OPTR_nSWBOOT0
  *     @arg FLASH_OPTR_nBOOT0
  *     @arg FLASH_OPTR_nRST_MODE
  * @retval None.
  */
void FLASH_Set_UserOptionByte(uint32_t OB_USER)
{
  if(OB_USER != 0)
	{
   FLASH_Unlock();
   FLASH_OB_Unlock();
    
   SET_BIT(FLASH->OPTR,OB_USER);      

	 SET_BIT(FLASH->CR,FLASH_CR_OPTSTRT);
   
   while((FLASH->SR & FLASH_SR_BSY) == FLASH_SR_BSY)
   {
   }; 
	 FLASH_Lock();
	 FLASH_OB_Lock();    
  }
}

/**
  * @brief  Clear the FLASH User Option Byte:IWDG_SW / RST_STOP / RST_STDBY / IWDG_STDBY / IWDG_STOP / WWDG_SW / ECC / Nboot1 / nSWBOOT0 / nBOOT0.
  * @param  OB_USER:
  *     @arg FLASH_OPTR_nRST_STOP
  *     @arg FLASH_OPTR_nRST_STDBY
  *     @arg FLASH_OPTR_IWDG_SW
  *     @arg FLASH_OPTR_IWDG_STOP
  *     @arg FLASH_OPTR_IWDG_STDBY
  *     @arg FLASH_OPTR_WWDG_SW
  *     @arg FLASH_OPTR_BFB2
  *     @arg FLASH_OPTR_ECC
  *     @arg FLASH_OPTR_Nboot1
  *     @arg FLASH_OPTR_nSWBOOT0
  *     @arg FLASH_OPTR_nBOOT0
  *     @arg FLASH_OPTR_nRST_MODE
  * @retval None.
    */
void FLASH_Clear_UserOptionByte(uint32_t OB_USER)
{ 
  if(OB_USER != 0)
	{
    FLASH_Unlock();
    FLASH_OB_Unlock();
    
    CLEAR_BIT(FLASH->OPTR,OB_USER);        
    
    SET_BIT(FLASH->CR,FLASH_CR_OPTSTRT);
  
    while((FLASH->SR & FLASH_SR_BSY) == FLASH_SR_BSY)
    {
    }; 
	  FLASH_Lock();
	  FLASH_OB_Lock(); 
  } 
}

