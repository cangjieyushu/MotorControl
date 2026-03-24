/***************************************************************************//**
 * @file     smpu_drv.c
 * @brief    SMPU module driver file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 ******************************************************************************/

#include "smpu_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @defgroup SMPU SMPU
 *  @brief SMPU driver modules
 *  @{
 */

/** @defgroup SMPU_Private_Type
 *  @{
 */

/** @} end of group SMPU_Private_Type*/

/** @defgroup SMPU_Private_Defines
 *  @{
 */

#define SMPU_GE_BIT_POSITION    (8U)    /*SMPU Global Enable Bit Position in SMPU_CS*/

/** @} end of group SMPU_Private_Defines */

/** @defgroup SMPU_Private_Variables
 *  @{
 */

/*PRQA S 0303 ++*/
static smpu_reg_t *const smpuRegPtr = (smpu_reg_t *) SMPU_BASE_ADDR;
static smpu_reg_w_t *const smpuRegWPtr = (smpu_reg_w_t *) SMPU_BASE_ADDR;
/*PRQA S 0303 --*/

static const uint32_t SMPU_ErrStatusTable[] = 
{
    0x00000001U,     /* SMPU_SLV_PORT_0_ERROR status mask */  
    0x00000002U,     /* SMPU_SLV_PORT_1_ERROR status mask */
    0x00000004U      /* SMPU_SLV_PORT_2_ERROR status mask */
};

/** @} end of group SMPU_Private_Variables */

/** @defgroup SMPU_Global_Variables
 *  @{
 */

/** @} end of group SMPU_Global_Variables */


/** @defgroup SMPU_Private_FunctionDeclaration
 *  @{
 */


/** @} end of group SMPU_Private_FunctionDeclaration */

/** @defgroup SMPU_Public_Functions
 *  @{
 */

/**
 * @brief       Initializes the SMPU
 *
 * @param[in]     region: Select memory region protect unit.
 * @param[in]     smpuConfigStruct: Pointer to a SMPU configuration structure.
 *
 * @return none
 *
 */
void SMPU_Init(SMPU_MemoryRegion_t region, const SMPU_Config_t* smpuConfigStruct)
{
   uint32_t retVal;
   
   smpuRegPtr->SMPU_MRCn_W[region].SMPU_MRCn_W0.SADDR = 
                                       smpuConfigStruct->startAddress >> 0x05UL;
   smpuRegPtr->SMPU_MRCn_W[region].SMPU_MRCn_W1.EADDR = 
                                        smpuConfigStruct->endAddress >> 0x05UL;
   
   retVal = ((uint32_t)(smpuConfigStruct->exeAllow) 
                          << ((uint32_t)(smpuConfigStruct->busMaster) * 0x6UL));
   retVal |= ((uint32_t)(smpuConfigStruct->writeAllow)
                  << ((uint32_t)(smpuConfigStruct->busMaster) * 0x6UL + 0x1UL));
   retVal |= ((uint32_t)(smpuConfigStruct->readAllow)
                  << ((uint32_t)(smpuConfigStruct->busMaster) * 0x6UL + 0x2UL));  
   retVal |= ((uint32_t)(smpuConfigStruct->supervisorModeAccess) & 0x03UL)
                     << ((uint32_t)smpuConfigStruct->busMaster * 0x6UL + 0x3UL);
   smpuRegWPtr->SMPU_MRCn_W[region].SMPU_MRCn_W2 &= ~(0x1FUL <<
                                 (uint32_t)smpuConfigStruct->busMaster * 0x6UL);
   smpuRegWPtr->SMPU_MRCn_W[region].SMPU_MRCn_W2 |= retVal;
}

/**
 * @brief       The range of address protected by MRCn.
 *
 *  Memory regions address can overlap.If MRC1 is accessible and MRC2 is not in 
 *  the overlapping part, then the overlapping part is accessible.
 *
 * @param[in]     region: Select memory region protect unit.
 * @param[in]     startAddress: Start address protected by MRCn(n=0~15).
 * @param[in]     endAddress: End address protected by MRCn(n=0~15).
 *
 * @return none
 *
 */
void SMPU_MemoryRegionRange(SMPU_MemoryRegion_t region, 
                                  uint32_t startAddress, uint32_t endAddress)
{  
   smpuRegPtr->SMPU_MRCn_W[region].SMPU_MRCn_W0.SADDR = startAddress >> 0x05UL;
   smpuRegPtr->SMPU_MRCn_W[region].SMPU_MRCn_W1.EADDR = endAddress >> 0x05UL;
}

/**
 * @brief       The execute access control of bus master for each region in user 
 *              mode.
 * @param[in]   region:Select memory region protect unit.
 * @param[in]   busMaster:Select bus master number.
 * @param[in]   exeAllow: Execute access control 
 *                    - Enable: execute is allowed
 *                    - Disable: execute is not allowed
 * @return none
 *
 */
void SMPU_BusMstUserModeExeControl(SMPU_MemoryRegion_t region, 
                            SMPU_BusMaster_t busMaster, ControlState_t exeAllow)
{ 
    uint32_t offset;
    offset = (uint32_t)busMaster * 0x6UL;
    if(DISABLE == exeAllow)
    {
        smpuRegWPtr->SMPU_MRCn_W[region].SMPU_MRCn_W2 &= 
                                                    ~((uint32_t)0x01 << offset);
    }
    else
    {
        smpuRegWPtr->SMPU_MRCn_W[region].SMPU_MRCn_W2 |= 
                                                     ((uint32_t)0x01 << offset);
    }
                          
}

/**
 * @brief       The write access control of bus master for each region in user 
 *              mode.
 * @param[in]   region:Select memory region protect unit.
 * @param[in]   busMaster:Select bus master number.
 * @param[in]   writeAllow: Write access control 
 *                    - Enable: write is allowed
 *                    - Disable: write is not allowed
 * @return none
 *
 */
void SMPU_BusMstUserModeWriteControl(SMPU_MemoryRegion_t region, 
                          SMPU_BusMaster_t busMaster, ControlState_t writeAllow)
{
    uint32_t offset;
    offset = (uint32_t)busMaster * 0x6UL + 0x1UL; 
    if(DISABLE == writeAllow)
    {
        smpuRegWPtr->SMPU_MRCn_W[region].SMPU_MRCn_W2 &= 
                                                    ~((uint32_t)0x01 << offset);
    }
    else
    {
        smpuRegWPtr->SMPU_MRCn_W[region].SMPU_MRCn_W2 |= 
                                                     ((uint32_t)0x01 << offset);
    }
}

/**
 * @brief       The read access control of bus master for each region in user 
 *              mode.
 * @param[in]   region:Select memory region protect unit.
 * @param[in]   busMaster:Select bus master number.
 * @param[in]   readAllow: Read access control 
 *                    - Enable: read is allowed
 *                    - Disable: read is not allowed
 * @return none
 *
 */
void SMPU_BusMstUserModeReadControl(SMPU_MemoryRegion_t region, 
                           SMPU_BusMaster_t busMaster, ControlState_t readAllow)
{   
    uint32_t offset;
    offset = (uint32_t)busMaster * 0x6UL + 0x2UL; 
    if(DISABLE == readAllow)
    {
        smpuRegWPtr->SMPU_MRCn_W[region].SMPU_MRCn_W2 &= 
                                                    ~((uint32_t)0x01 << offset);
    }
    else
    {
        smpuRegWPtr->SMPU_MRCn_W[region].SMPU_MRCn_W2 |= 
                                                     ((uint32_t)0x01 << offset);
    }
}

/**
 * @brief     The write/read/execute access control for bus master in supervisor
 *            mode
 * @param[in]   region:Select memory region protect unit.
 * @param[in]   busMaster:Select bus master number.
 * @param[in]   controlType: Access control types for bus master
 *     - SMPU_ALL_ALLOWED: Read/write/execute are all allowed
 *     - SMPU_READ_EXE_ALLOWED: Read/execute are allowed, write is not allowed
 *     - SMPU_READ_WRITE_ALLOWED: Read/write are allowed, execute is not allowed
 *     - SMPU_SAME_WITH_USERMODE: Access control are same with user mode
 *
 * @return none
 *
 */
void SMPU_BusMstSvrModeAccessControl(SMPU_MemoryRegion_t region, 
                                     SMPU_BusMaster_t busMaster,
                                     SMPU_SupvModeAccess_t controlType)
{   
    uint32_t offset;
    offset = (uint32_t)busMaster * 0x6UL + 0x3UL; 
    
    smpuRegWPtr->SMPU_MRCn_W[region].SMPU_MRCn_W2 &= 
                                    ~((uint32_t)0x3UL << offset);
    smpuRegWPtr->SMPU_MRCn_W[region].SMPU_MRCn_W2 |= 
                                    (((uint32_t)controlType & 0x3UL) << offset);
}

/**
 * @brief        Global SMPU enable
 *
 * @param[in]    none
 *
 * @return none
 *
 */
void SMPU_Enable(void)
{   
    smpuRegWPtr->SMPU_CS = (1UL << SMPU_GE_BIT_POSITION);
}

/**
 * @brief        Global SMPU disable
 *
 * @param[in]    none
 *
 * @return none
 *
 */
void SMPU_Disable(void)
{   
    smpuRegWPtr->SMPU_CS = 0U;
}

/**
 * @brief        Memory region n configuration enable
 *
 * @param[in]   region:Select memory region protect unit.
 *
 * @return none
 *
 */
void SMPU_MemoryRegionConfigEnable(SMPU_MemoryRegion_t region)
{ 
    smpuRegPtr->SMPU_MRCn_W[region].SMPU_MRCn_W3.EN = 1U;
}

/**
 * @brief       Memory region n configuration disable
 *
 * @param[in]   region:Select memory region protect unit.
 *
 * @return none
 *
 */
void SMPU_MemoryRegionConfigDisable(SMPU_MemoryRegion_t region)
{  
    smpuRegPtr->SMPU_MRCn_W[region].SMPU_MRCn_W3.EN = 0U;
}

/**
 * @brief         Record the error is detected by appointed MRC.
 *
 * This function detected a MRC.
 *
 * @param[in]    slavePort: Select slave port type: SMPU_SLV_PORT_0, 
 *                          SMPU_SLV_PORT_1, SMPU_SLV_PORT_2.
 * @param[in]    region:   Select memory region protect unit.
 *
 * @return       - SET: Error detected by memory region configuration
 *               - RESET: No error detected by memory region configuration
 *
 */
FlagStatus_t SMPU_GetSingleMrcErrStatus(SMPU_SlvPort_t slavePort, 
                                        SMPU_MemoryRegion_t region)
{   
    uint32_t mrcStatus = smpuRegPtr->SMPU_Sn_ES[slavePort].EMRC;
    mrcStatus = ((mrcStatus & (0x01UL << (uint32_t)region)) >> 
                                                            (uint32_t)region);
    return (FlagStatus_t)mrcStatus;
}

/**
 * @brief        Record the error is detected by which MRC in slave port
 *
 * @param[in]   slavePort: Select slave PORT Type: SMPU_SLV_PORT_0, 
 *                          SMPU_SLV_PORT_1, SMPU_SLV_PORT_2.
 *              
 * @return      Error detected by MRCn number.(n = 0~15)
 *       (Bit n corresponds to MRCn, and bit n set 1 when error occurs in MRCn.)
 *
 */
uint32_t SMPU_GetErrMrcNum(SMPU_SlvPort_t slavePort)
{   
    return smpuRegPtr->SMPU_Sn_ES[slavePort].EMRC;
}

/**
 * @brief       The bus master that cause the access error.
 * @param[in]   slavePort: Select slave PORT Type: SMPU_SLV_PORT_0, 
 *                          SMPU_SLV_PORT_1, SMPU_SLV_PORT_2.
 * 
 * @return      Error master number:
 *               - 0: bus master0 cause the access error
 *               - 1: bus master1 cause the access error
 *               - 2: bus master2 cause the access error
 */
uint32_t SMPU_GetErrAccMstNum(SMPU_SlvPort_t slavePort)
{ 
    return smpuRegPtr->SMPU_Sn_ES[slavePort].EMN;
}

/**
 * @brief       Error type is read or write access
 * @param[in]   slavePort: Select slave PORT Type: SMPU_SLV_PORT_0, 
 *                          SMPU_SLV_PORT_1, SMPU_SLV_PORT_2.
 *
 * @return       none
 *
 */
void SMPU_GetAccErrCause(SMPU_SlvPort_t slavePort, SMPU_ErrorType_t * errorType)
{  
    errorType->write = (smpuRegPtr->SMPU_Sn_ES[slavePort].ERW != 0U) ? 
                                         SET:RESET;
    errorType->accessMode = (smpuRegPtr->SMPU_Sn_ES[slavePort].EUS == 0U) ?
                                         SMPU_ACCESS_MODE_USER : SMPU_ACCESS_MODE_SVR;
    errorType->accessType = (smpuRegPtr->SMPU_Sn_ES[slavePort].EATTR == 0U) ? 
                                         SMPU_ACCESS_TYPE_INS : SMPU_ACCESS_TYPE_DATA;
}

/**
 * @brief        slave port n error address.
 *
 * @param[in]    slavePort: Select slave PORT Type: SMPU_SLV_PORT_0, 
 *                          SMPU_SLV_PORT_1, SMPU_SLV_PORT_2.
 *
 * @return       slave port n error address
 *
 */
uint32_t SMPU_GetSlvPortErrAddress(SMPU_SlvPort_t slavePort)
{ 
    return smpuRegWPtr->SMPU_Sn_EA[slavePort];
}

/**
 * @brief        slave port n error status .
 *
 * @param[in]    errorPortStatus: slave port n error type
 *               - SMPU_SLV_PORT_0_ERROR
 *               - SMPU_SLV_PORT_1_ERROR
 *               - SMPU_SLV_PORT_2_ERROR
 *
 * @return       - SET: slave port n access error occurred.
 *               - RESET: slave port n access error didn't occur.
 *
 */
FlagStatus_t SMPU_GetSlvPortAccErrStatus(SMPU_SlvPortErrorStatus_t portAccessStatus)
{  
    FlagStatus_t bitStatus;

    if (0UL == ((smpuRegWPtr->SMPU_CS) & SMPU_ErrStatusTable[portAccessStatus])) 
    {
        bitStatus = RESET;
    }
    else
    {
        bitStatus = SET;
    }

    return (FlagStatus_t)bitStatus;
}

/**
 * @brief        clear slave port n error status .
 *
 * @param[in]    errorPortStatus: slave port n error type
 *               - SMPU_SLV_PORT_0_ERROR
 *               - SMPU_SLV_PORT_1_ERROR
 *               - SMPU_SLV_PORT_2_ERROR
 *
 * @return       none
 *
 */
void SMPU_ClearSlvPortErrStatus(SMPU_SlvPortErrorStatus_t portAccessStatus)
{
    uint32_t regVal = smpuRegWPtr->SMPU_CS;
    regVal = regVal & (~7U);
    regVal = regVal | SMPU_ErrStatusTable[portAccessStatus];
    smpuRegWPtr->SMPU_CS = regVal;
}
/** @} end of group SMPU_Public_Functions */

/** @} end of group SMPU_definitions */

/** @} end of group Z20K14XM_Peripheral_Driver */
