/***************************************************************************//**
 * @file     smpu_drv.h
 * @brief    SMPU driver module header file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 ******************************************************************************/

#ifndef SMPU_DRV_H
#define SMPU_DRV_H

#include "common_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SMPU
 *  @{
 */

/** @defgroup SMPU_Public_Types 
 *  @{
 */


/**
 *  @brief SMPU bus master type definition
 */
typedef enum
{
    SMPU_BUS_MASTER_0 = 0U,                   /*!< Bus master 0 */
    SMPU_BUS_MASTER_1,                        /*!< Bus master 1 */
    SMPU_BUS_MASTER_2                         /*!< Bus master 2 */
} SMPU_BusMaster_t; 

/**
 *  @brief SMPU slave port type definition
 */
typedef enum
{
    SMPU_SLV_PORT_0 = 0U,                     /*!< Slave port 0 */
    SMPU_SLV_PORT_1,                          /*!< Slave port 1 */
    SMPU_SLV_PORT_2,                          /*!< Slave port 2 */
} SMPU_SlvPort_t;

/**
 *  @brief SMPU memory region type definition
 */
typedef enum
{
    SMPU_MEMORY_REGION_0 = 0U,                /*!< Memory region 0  */
    SMPU_MEMORY_REGION_1,                     /*!< Memory region 1  */
    SMPU_MEMORY_REGION_2,                     /*!< Memory region 2  */
    SMPU_MEMORY_REGION_3,                     /*!< Memory region 3  */
    SMPU_MEMORY_REGION_4,                     /*!< Memory region 1  */
    SMPU_MEMORY_REGION_5,                     /*!< Memory region 5  */
    SMPU_MEMORY_REGION_6,                     /*!< Memory region 6  */
    SMPU_MEMORY_REGION_7,                     /*!< Memory region 7  */
    SMPU_MEMORY_REGION_8,                     /*!< Memory region 8  */
    SMPU_MEMORY_REGION_9,                     /*!< Memory region 9  */
    SMPU_MEMORY_REGION_10,                    /*!< Memory region 10 */
    SMPU_MEMORY_REGION_11,                    /*!< Memory region 11 */
    SMPU_MEMORY_REGION_12,                    /*!< Memory region 12 */
    SMPU_MEMORY_REGION_13,                    /*!< Memory region 13 */
    SMPU_MEMORY_REGION_14,                    /*!< Memory region 14 */
    SMPU_MEMORY_REGION_15                     /*!< Memory region 15 */ 
} SMPU_MemoryRegion_t;

/**
 *  @brief SMPU slave port n error status type definition
 */
typedef enum
{
    SMPU_SLV_PORT_0_ERROR   = 0U,           /*!< Slave port0 access error */
    SMPU_SLV_PORT_1_ERROR,                  /*!< Slave port1 access error */
    SMPU_SLV_PORT_2_ERROR,                  /*!< Slave port2 access error */
} SMPU_SlvPortErrorStatus_t;

/**
 *  @brief SMPU access control for bus master in supervisor mode type definition
 */
typedef enum
{
    SMPU_ALL_ALLOWED = 0U,            /*!< Read/write/execute are all allowed */
    SMPU_READ_EXE_ALLOWED,            /*!< Read/execute are allowed, write is not allowed */
    SMPU_READ_WRITE_ALLOWED,          /*!< Read/write are allowed, execute is not allowed */
    SMPU_SAME_WITH_USERMODE,          /*!< Access control are same with user mode */
} SMPU_SupvModeAccess_t;

/**
 *  @brief SMPU access type definition
 */
typedef enum
{
    SMPU_ACCESS_TYPE_INS = 0U,         /*!< Access type: instruction access */
    SMPU_ACCESS_TYPE_DATA              /*!< Access type: data access */
} SMPU_AccessErrorType_t;

/**
 *  @brief SMPU access mode definition
 */
typedef enum
{
    SMPU_ACCESS_MODE_USER = 0U,        /*!< Access mode: user mode */
    SMPU_ACCESS_MODE_SVR               /*!< Access mode: supervisor mode */
} SMPU_AccessMode_t;

/**
 *  @brief SMPU init configure struct definition
 */
typedef struct
{
    SMPU_BusMaster_t  busMaster;    /*!< Bus master number.
                                         - SMPU_BUS_MASTER_0
                                         - SMPU_BUS_MASTER_1
                                         - SMPU_BUS_MASTER_2 */
    uint32_t startAddress;          /*!< Start address protected by MRCn(n=0~15). */
    uint32_t endAddress;            /*!< End address protected by MRCn(n=0~15). */
    ControlState_t  exeAllow;       /*!< Enable/Disable execute access. */
    ControlState_t  writeAllow;     /*!< Enable/Disable write access. */
    ControlState_t  readAllow;      /*!< Enable/Disable read access. */
    SMPU_SupvModeAccess_t supervisorModeAccess;  /*!< Access control for bus master in supervisor 
                                                      mode.*/
} SMPU_Config_t;

/**
 *  @brief SMPU slave port error cause struct definition
 */
typedef struct
{
    FlagStatus_t write;                 /*!< whether slave port is caused by writing operation 
                                           - RESET: it is caused by reading
                                           - SET: it is caused by writing  */ 
    SMPU_AccessMode_t accessMode;       /*!< Indicates error caused in which mode. */
    SMPU_AccessErrorType_t accessType;  /*!< Indicates error caused by which type of access. */
} SMPU_ErrorType_t;
 
/** @} end of group SMPU_Public_Types*/

/** @defgroup SMPU_Public_FunctionDeclaration
 *  @brief SMPU functions statement
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
void SMPU_Init(SMPU_MemoryRegion_t region, const SMPU_Config_t* smpuConfigStruct);

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
                                  uint32_t startAddress, uint32_t endAddress);

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
                           SMPU_BusMaster_t busMaster, ControlState_t exeAllow);

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
                        SMPU_BusMaster_t busMaster, ControlState_t writeAllow);

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
                        SMPU_BusMaster_t busMaster, ControlState_t readAllow);

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
                                     SMPU_SupvModeAccess_t controlType);

/**
 * @brief        Global SMPU enable
 *
 * @param[in]    none
 *
 * @return none
 *
 */
void SMPU_Enable(void);

/**
 * @brief        Global SMPU disable
 *
 * @param[in]    none
 *
 * @return none
 *
 */
void SMPU_Disable(void);

/**
 * @brief        Memory region n configuration enable
 *
 * @param[in]   region:Select memory region protect unit.
 *
 * @return none
 *
 */
void SMPU_MemoryRegionConfigEnable(SMPU_MemoryRegion_t region);

/**
 * @brief       Memory region n configuration disable
 *
 * @param[in]   region:Select memory region protect unit.
 *
 * @return none
 *
 */
void SMPU_MemoryRegionConfigDisable(SMPU_MemoryRegion_t region);

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
                                        SMPU_MemoryRegion_t region);

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
uint32_t SMPU_GetErrMrcNum(SMPU_SlvPort_t slavePort);

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
uint32_t SMPU_GetErrAccMstNum(SMPU_SlvPort_t slavePort);

/**
 * @brief       Error type is read or write access
 * @param[in]   slavePort: Select slave PORT Type: SMPU_SLV_PORT_0, 
 *                          SMPU_SLV_PORT_1, SMPU_SLV_PORT_2.
 *
 * @return       none
 *
 */
void SMPU_GetAccErrCause(SMPU_SlvPort_t slavePort, 
                         SMPU_ErrorType_t * errorType);

/**
 * @brief        slave port n error address.
 *
 * @param[in]    slavePort: Select slave PORT Type: SMPU_SLV_PORT_0, 
 *                          SMPU_SLV_PORT_1, SMPU_SLV_PORT_2.
 *
 * @return       slave port n error address
 *
 */
uint32_t SMPU_GetSlvPortErrAddress(SMPU_SlvPort_t slavePort);

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
FlagStatus_t SMPU_GetSlvPortAccErrStatus(SMPU_SlvPortErrorStatus_t portAccessStatus);

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
void SMPU_ClearSlvPortErrStatus(SMPU_SlvPortErrorStatus_t portAccessStatus);

/** @} end of group SMPU_Public_FunctionDeclaration */

/** @} end of group SMPU */

/** @} end of group Z20K14XM_Peripheral_Driver */
#endif /* SMPU_DRV_H */
