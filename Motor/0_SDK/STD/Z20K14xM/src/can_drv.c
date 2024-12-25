/**************************************************************************************************/
/**
 * @file     can_drv.c
 * @brief    CAN module driver file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note     For CAN 0-5, 64 message buffers are available. 
 *           For CAN 6-7, 128 message buffers are available.
 *
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 *
 **************************************************************************************************/

#include "can_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @defgroup CAN
 *  @brief CAN driver modules
 *  @{
 */

/** @defgroup CAN_Private_Type
 *  @{
 */

/**
 *  @brief CAN FD MB region type definition
 */
typedef enum 
{
    CAN_FD_MB_REGION_0 = 0U,  /*!< FD MB region 0*/
    CAN_FD_MB_REGION_1,       /*!< FD MB region 1*/
    CAN_FD_MB_REGION_2,       /*!< FD MB region 2*/
    CAN_FD_MB_REGION_3        /*!< FD MB region 3*/    
} CAN_FdMbRegion_t;

/**
 *  @brief CAN MB type definition
 */
typedef enum 
{
    CAN_MB_RX = 0U,  /*!< TX MB */
    CAN_MB_TX        /*!< RX MB */
} CAN_MbTR_t;



typedef volatile struct
{
    union {
        struct {
            uint32_t TIME_STAMP              :16;  /* [15:0]                  */
            uint32_t DLC                     : 4;  /* [19:16]                 */
            uint32_t RTR                     : 1;  /* [20]                    */
            uint32_t IDE                     : 1;  /* [21]                    */
            uint32_t SRR                     : 1;  /* [22]                    */
            uint32_t RSVD_23                 : 1;  /* [23]                    */
            uint32_t CODE                    : 4;  /* [27:24]                 */
            uint32_t RSVD_28                 : 1;  /* [28]                    */
            uint32_t ESI                     : 1;  /* [29]                    */
            uint32_t BRS                     : 1;  /* [30]                    */
            uint32_t EDL                     : 1;  /* [31]                    */
        } BF;
        uint32_t WORDVAL;
    } config;

    /* 0x84*/
    union {
        struct {
            uint32_t ID_EXTEND               :18;  /* [17:0]                  */
            uint32_t ID_STANDARD             :11;  /* [28:18]                 */
            uint32_t PRIO                    : 3;  /* [31:29]                 */
        } BF;
        uint32_t WORDVAL;
    } id;

    uint32_t data[16];
} CAN_Mb_t;

/**
 *  @brief CAN callback functions struct
 */
typedef struct 
{
   can_mb_cb_t mbCbf[CAN_MB_INT_NUM]; /*!< call back function for MB interrupts */
   isr_cb_t * cbf[(uint32_t)CAN_INT_ALL - 1U];   /*!< other call back functions */ 
} CAN_cbf_t;

/** @} end of group CAN_Private_Type*/

/** @defgroup CAN_Private_Defines
 *  @{
 */
#define  CAN_RX_INACTIVE    (0x0U)  /*!< MB is not active.*/
#define  CAN_RX_FULL        (0x2U)  /*!< MB is full.*/
#define  CAN_RX_EMPTY       (0x4U)  /*!< MB is active and empty.*/
#define  CAN_RX_OVERRUN     (0x6U)  /*!< MB is overwritten into a full buffer.*/
#define  CAN_RX_RANSWER     (0xAU)  /*!< A frame was configured to recognize a Remote 
                                        Request Frame and transmit a Response Frame 
                                        in return.*/

#define  CAN_TX_INACTIVE     (0x08U) /*!< MB is not active.*/
#define  CAN_TX_ABORT        (0x09U) /*!< MB is aborted.*/
#define  CAN_TX_DATA_REMOTE  (0x0CU) /*!< MB is a TX Data Frame(MB RTR must be 0).*/
#define  CAN_TX_TANSWER      (0x0EU) /*!< MB is a TX Response Request Frame from.
                                         an incoming Remote Request Frame.*/
#define  CAN_NOT_USED        (0xFU)  /*!< Not used*/


#define CAN_MCR_LPMACK_MASK    (0x00100000U)
#define CAN_MCR_FRZACK_MASK    (0x01000000U)

#define CAN_WAIT_CNT           (100000)
#define CAN_ID_STD_SHIFT       (18U)
#define CAN_ID_STD_MASK        (0x1FFC0000U)
#define CAN_ID_EXT_MASK        (0x1FFFFFFFU)

/* CAN FD extended data length DLC encoding */
#define CAN_DLC_VALUE_12_BYTES                   (9U)
#define CAN_DLC_VALUE_16_BYTES                   (10U)
#define CAN_DLC_VALUE_20_BYTES                   (11U)
#define CAN_DLC_VALUE_24_BYTES                   (12U)
#define CAN_DLC_VALUE_32_BYTES                   (13U)
#define CAN_DLC_VALUE_48_BYTES                   (14U)
#define CAN_DLC_VALUE_64_BYTES                   (15U)


#define CAN_INT_MSK_BUS_OFF            ((uint32_t)1U << 15U)
#define CAN_INT_MSK_ERR                ((uint32_t)1U << 14U)
#define CAN_INT_MSK_TXW                ((uint32_t)1U << 11U)
#define CAN_INT_MSK_RXW                ((uint32_t)1U << 10U)
#define CAN_INT_MSK_BUS_OFF_DONE       ((uint32_t)1U << 30U)
#define CAN_INT_MSK_ERR_FAST           ((uint32_t)1U << 31U)
#define CAN_INT_MSK_SELF_WAKEUP        ((uint32_t)1U << 26U)
#define CAN_INT_MSK_RXFIFO_FRAME       (1U << 5U)
#define CAN_INT_MSK_RXFIFO_WARNING     (1U << 6U)
#define CAN_INT_MSK_RXFIFO_OVERFLOW    (1U << 7U)
#define CAN_INT_MSK_HOST_MEM_ERR       ((uint32_t)1U << 19U)
#define CAN_INT_MSK_CAN_MEM_ERR        ((uint32_t)1U << 18U) 
#define CAN_INT_MSK_COR_MEM_ERR        ((uint32_t)1U << 16U)
#define CAN_INT_MSK_PN_WAKEUP_MATCH    ((uint32_t)1U << 16U) 
#define CAN_INT_MSK_PN_WAKEUP_TIMEOUT  ((uint32_t)1U << 17U)
#define CAN_INT_MSK_MULTI_1            (CAN_INT_MSK_BUS_OFF | CAN_INT_MSK_ERR |\
                                        CAN_INT_MSK_TXW | CAN_INT_MSK_RXW)
#define CAN_INT_MSK_MULTI_2            (CAN_INT_MSK_BUS_OFF_DONE | CAN_INT_MSK_ERR_FAST)
#define CAN_INT_MSK_MULTI_ECC          (CAN_INT_MSK_HOST_MEM_ERR | \
                                        CAN_INT_MSK_CAN_MEM_ERR | \
                                        CAN_INT_MSK_COR_MEM_ERR)
#define CAN_INT_MSK_MULTI_PN           (CAN_INT_MSK_PN_WAKEUP_MATCH |\
                                        CAN_INT_MSK_PN_WAKEUP_TIMEOUT)


#define CAN_INT_MSK_FLAG_BUS_OFF           (1U << 2U)
#define CAN_INT_MSK_FLAG_ERR               (1U << 1U)
#define CAN_INT_MSK_FLAG_TXW               ((uint32_t)1U << 17U)
#define CAN_INT_MSK_FLAG_RXW               ((uint32_t)1U << 16U)
#define CAN_INT_MSK_FLAG_BUS_OFF_DONE      ((uint32_t)1U << 19U)
#define CAN_INT_MSK_FLAG_ERR_FAST          ((uint32_t)1U << 20U)
#define CAN_INT_MSK_FLAG_SELF_WAKEUP        1U
#define CAN_INT_MSK_FLAG_RXFIFO_FRAME      (1U << 5U)
#define CAN_INT_MSK_FLAG_RXFIFO_WARNING    (1U << 6U)
#define CAN_INT_MSK_FLAG_RXFIFO_OVERFLOW   (1U << 7U)
#define CAN_INT_MSK_FLAG_HOST_MEM_ERR      ((uint32_t)1U << 19U)
#define CAN_INT_MSK_FLAG_CAN_MEM_ERR       ((uint32_t)1U << 18U) 
#define CAN_INT_MSK_FLAG_COR_MEM_ERR       ((uint32_t)1U << 16U)
#define CAN_INT_MSK_FLAG_PN_WAKEUP_MATCH   ((uint32_t)1U << 16U) 
#define CAN_INT_MSK_FLAG_PN_WAKEUP_TIMEOUT ((uint32_t)1U << 17U)
#define CAN_INT_MSK_FLAG_ALL_1         (CAN_INT_MSK_FLAG_BUS_OFF | \
                                        CAN_INT_MSK_FLAG_ERR | \
                                        CAN_INT_MSK_FLAG_TXW | \
                                        CAN_INT_MSK_FLAG_RXW |\
                                        CAN_INT_MSK_FLAG_BUS_OFF_DONE |\
                                        CAN_INT_MSK_FLAG_ERR_FAST |\
                                        CAN_INT_MSK_FLAG_SELF_WAKEUP)
#define CAN_INT_MSK_FLAG_ALL_ECC       (CAN_INT_MSK_FLAG_HOST_MEM_ERR |\
                                        CAN_INT_MSK_FLAG_CAN_MEM_ERR |\
                                        CAN_INT_MSK_FLAG_COR_MEM_ERR)
#define CAN_INT_MSK_FLAG_ALL_PN        (CAN_INT_MSK_FLAG_PN_WAKEUP_MATCH |\
                                        CAN_INT_MSK_FLAG_PN_WAKEUP_TIMEOUT)
#define CAN_INT_MSK_FLAG_ALL_BUSOFF    (CAN_INT_MSK_FLAG_BUS_OFF |\
                                        CAN_INT_MSK_FLAG_BUS_OFF_DONE)

#define CAN_CAL_RX_MB_STD_MASK(mask)    (((mask) << CAN_ID_STD_SHIFT) & CAN_ID_STD_MASK)
#define CAN_CAL_RX_MB_EXT_MASK(mask)    ((mask) & CAN_ID_EXT_MASK)
#define CAN_RX_FIFO_OCUP_LAST_MB_NUM(x) (5U + ((((x) + 1U) * 8U) >> 2U))

#define CAN_SWAP_BYTES_IN_WORD_INDEX(index)    (((index) & ~3U) + (3U - ((index) & 3U)))
#define CAN_SWAP_BYTES_IN_WORD(a, b)            REV_BYTES_32(a, b)

#define CAN_GET_MB_NUM(id)          (((id) < CAN_ID_6) ? CAN05_MB_NUM : CAN67_MB_NUM)

#define CAN_CODE_BUSY_MASK          (0x01U)

#define CAN_RXFIFO_FRAME_AVAILABLE  (5U)
#define CAN_RXFIFO_WARNING          (6U)
#define CAN_RXFIFO_OVERFLOW         (7U)

#define CAN_STATUS_ALL_MASK        (0xDC00FF00U)

#define CAN_RAM_RX_FIFO_ADDR              (0xA80U)
#define CAN_RAM_RX_FIFO_LEN_IN_WORD       (6U)
#define CAN_RAM_MSK_ADDR                  (0xAA0U)
#define CAN_RAM_MSK_LEN_IN_WORD           (4U)
#define CAN_RAM_RX_SMB_ADDR               (0xAB0U)
#define CAN_RAM_RX_SMB_LEN_IN_WORD        (12U)
#define CAN_RAM_FD_SCRATCH_ADDR           (0xF28U)
#define CAN_RAM_FD_SCRATCH_LEN_IN_WORD    (54U)

/** @} end of group CAN_Private_Defines */

/** @defgroup CAN_Private_Variables
 *  @{
 */
/*PRQA S 0303 ++*/
static can_reg_t * const canRegPtr[CAN_INSTANCE_NUM] = 
{
#if (8U == CAN_INSTANCE_NUM ) 
    (can_reg_t *)CAN0_BASE_ADDR, (can_reg_t *)CAN1_BASE_ADDR, 
    (can_reg_t *)CAN2_BASE_ADDR, (can_reg_t *)CAN3_BASE_ADDR,
    (can_reg_t *)CAN4_BASE_ADDR, (can_reg_t *)CAN5_BASE_ADDR, 
    (can_reg_t *)CAN6_BASE_ADDR, (can_reg_t *)CAN7_BASE_ADDR
#elif (6U == CAN_INSTANCE_NUM )
    (can_reg_t *)CAN0_BASE_ADDR, (can_reg_t *)CAN1_BASE_ADDR, 
    (can_reg_t *)CAN2_BASE_ADDR, (can_reg_t *)CAN3_BASE_ADDR,
    (can_reg_t *)CAN4_BASE_ADDR, (can_reg_t *)CAN5_BASE_ADDR
#elif (4U == CAN_INSTANCE_NUM )
    (can_reg_t *)CAN0_BASE_ADDR, (can_reg_t *)CAN1_BASE_ADDR, 
    (can_reg_t *)CAN2_BASE_ADDR, (can_reg_t *)CAN3_BASE_ADDR
#endif
};

static can_reg_w_t * const canRegWPtr[CAN_INSTANCE_NUM] = 
{
#if (8U == CAN_INSTANCE_NUM ) 
    (can_reg_w_t *)CAN0_BASE_ADDR, (can_reg_w_t *)CAN1_BASE_ADDR, 
    (can_reg_w_t *)CAN2_BASE_ADDR, (can_reg_w_t *)CAN3_BASE_ADDR,
    (can_reg_w_t *)CAN4_BASE_ADDR, (can_reg_w_t *)CAN5_BASE_ADDR, 
    (can_reg_w_t *)CAN6_BASE_ADDR, (can_reg_w_t *)CAN7_BASE_ADDR
#elif (6U == CAN_INSTANCE_NUM )
    (can_reg_w_t *)CAN0_BASE_ADDR, (can_reg_w_t *)CAN1_BASE_ADDR, 
    (can_reg_w_t *)CAN2_BASE_ADDR, (can_reg_w_t *)CAN3_BASE_ADDR,
    (can_reg_w_t *)CAN4_BASE_ADDR, (can_reg_w_t *)CAN5_BASE_ADDR
#elif (4U == CAN_INSTANCE_NUM )
    (can_reg_w_t *)CAN0_BASE_ADDR, (can_reg_w_t *)CAN1_BASE_ADDR, 
    (can_reg_w_t *)CAN2_BASE_ADDR, (can_reg_w_t *)CAN3_BASE_ADDR
#endif
};
/*PRQA S 0303 --*/
static const uint32_t canInterruptMaskTable[] =
{    
    CAN_INT_MSK_BUS_OFF,        /* CAN_INT_BUS_OFF */
    CAN_INT_MSK_ERR,            /* CAN_INT_ERR */    
    CAN_INT_MSK_TXW,            /* CAN_INT_TXW */
    CAN_INT_MSK_RXW,            /* CAN_INT_RXW */
    CAN_INT_MSK_BUS_OFF_DONE,   /* CAN_INT_BUS_OFF_DONE */
    CAN_INT_MSK_ERR_FAST,       /* CAN_INT_ERR_FAST */
    CAN_INT_MSK_SELF_WAKEUP,    /* CAN_INT_SELF_WAKEUP */
    CAN_INT_MSK_RXFIFO_FRAME,   /* CAN_INT_RXFIFO_FRAME */  
    CAN_INT_MSK_RXFIFO_WARNING, /* CAN_INT_RXFIFO_WARNING */  
    CAN_INT_MSK_RXFIFO_OVERFLOW,/* CAN_INT_RXFIFO_OVERFLOW */
    CAN_INT_MSK_HOST_MEM_ERR,   /* CAN_INT_HOST_MEM_ERR */
    CAN_INT_MSK_CAN_MEM_ERR,    /* CAN_INT_CAN_MEM_ERR */
    CAN_INT_MSK_COR_MEM_ERR,    /* CAN_INT_COR_MEM_ERR */
    CAN_INT_MSK_PN_WAKEUP_MATCH, /* CAN_INT_PN_WAKEUP_MATCH */
    CAN_INT_MSK_PN_WAKEUP_TIMEOUT,/* CAN_INT_PN_WAKEUP_TIMEOUT */
};

static const uint32_t canInterruptFlagMaskTable[] =
{
    CAN_INT_MSK_FLAG_BUS_OFF,   /* CAN_INT_BUS_OFF */
    CAN_INT_MSK_FLAG_ERR,       /* CAN_INT_ERR */
    CAN_INT_MSK_FLAG_TXW,       /* CAN_INT_TXW */
    CAN_INT_MSK_FLAG_RXW,       /* CAN_INT_RXW */
    CAN_INT_MSK_FLAG_BUS_OFF_DONE,  /* CAN_INT_BUS_OFF_DONE */
    CAN_INT_MSK_FLAG_ERR_FAST,      /* CAN_INT_ERR_FAST */
    CAN_INT_MSK_FLAG_SELF_WAKEUP,   /* CAN_INT_SELF_WAKEUP */
    CAN_INT_MSK_FLAG_RXFIFO_FRAME,  /* CAN_INT_RXFIFO_FRAME */
    CAN_INT_MSK_FLAG_RXFIFO_WARNING,/* CAN_INT_RXFIFO_WARNING */
    CAN_INT_MSK_FLAG_RXFIFO_OVERFLOW, /* CAN_INT_RXFIFO_OVERFLOW */
    CAN_INT_MSK_FLAG_HOST_MEM_ERR,    /* CAN_INT_HOST_MEM_ERR */
    CAN_INT_MSK_FLAG_CAN_MEM_ERR,     /* CAN_INT_CAN_MEM_ERR */
    CAN_INT_MSK_FLAG_COR_MEM_ERR,     /* CAN_INT_COR_MEM_ERR */
    CAN_INT_MSK_FLAG_PN_WAKEUP_MATCH, /* CAN_INT_PN_WAKEUP_MATCH */
    CAN_INT_MSK_FLAG_PN_WAKEUP_TIMEOUT,/* CAN_INT_PN_WAKEUP_TIMEOUT */
    0U,                                /* not used */
};

static CAN_cbf_t canIsrCbFunc[CAN_INSTANCE_NUM] = 
{
#if (8U == CAN_INSTANCE_NUM )
    {{NULL,NULL, NULL, NULL}, {NULL, NULL, NULL,NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
    {{NULL,NULL, NULL, NULL}, {NULL, NULL, NULL,NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
    {{NULL,NULL, NULL, NULL}, {NULL, NULL, NULL,NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
    {{NULL,NULL, NULL, NULL}, {NULL, NULL, NULL,NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
    {{NULL,NULL, NULL, NULL}, {NULL, NULL, NULL,NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
    {{NULL,NULL, NULL, NULL}, {NULL, NULL, NULL,NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
    {{NULL,NULL, NULL, NULL}, {NULL, NULL, NULL,NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
    {{NULL,NULL, NULL, NULL}, {NULL, NULL, NULL,NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
#elif (6U == CAN_INSTANCE_NUM )
    {{NULL,NULL, NULL, NULL}, {NULL, NULL, NULL,NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
    {{NULL,NULL, NULL, NULL}, {NULL, NULL, NULL,NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
    {{NULL,NULL, NULL, NULL}, {NULL, NULL, NULL,NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
    {{NULL,NULL, NULL, NULL}, {NULL, NULL, NULL,NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
    {{NULL,NULL, NULL, NULL}, {NULL, NULL, NULL,NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
    {{NULL,NULL, NULL, NULL}, {NULL, NULL, NULL,NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
#elif (4U == CAN_INSTANCE_NUM )
    {{NULL,NULL, NULL, NULL}, {NULL, NULL, NULL,NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
    {{NULL,NULL, NULL, NULL}, {NULL, NULL, NULL,NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
    {{NULL,NULL, NULL, NULL}, {NULL, NULL, NULL,NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
    {{NULL,NULL, NULL, NULL}, {NULL, NULL, NULL,NULL, NULL, NULL, NULL, NULL, 
    NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
#endif
};

static uint32_t canEsr1Buf[CAN_INSTANCE_NUM] = 
{
#if (8U == CAN_INSTANCE_NUM )
    0U,0U,0U,0U,0U,0U,0U,0U
#elif (6U == CAN_INSTANCE_NUM )
    0U,0U,0U,0U,0U,0U
#elif (4U == CAN_INSTANCE_NUM )
    0U,0U,0U,0U
#endif
};

static uint32_t canIntMaskStatus1[CAN_INSTANCE_NUM] = {
#if (8U == CAN_INSTANCE_NUM )
  0U,0U,0U,0U,0U,0U,0U,0U
#elif (6U == CAN_INSTANCE_NUM )
  0U,0U,0U,0U,0U,0U
#elif (4U == CAN_INSTANCE_NUM )
  0U,0U,0U,0U
#endif
};

/** @} end of group CAN_Private_Variables */

/** @defgroup CAN_Global_Variables
 *  @{
 */

/** @} end of group CAN_Global_Variables */

/** @defgroup CAN_Private_FunctionDeclaration
 *  @{
 */
static ResultStatus_t CAN_ClearMbIntStatus(CAN_Id_t id, uint32_t mbIdx);
void CAN0_BusOff_DriverIRQHandler(void);
void CAN0_TxWarn_DriverIRQHandler(void);
void CAN0_RxWarn_DriverIRQHandler(void);
void CAN0_Err_DriverIRQHandler(void);
void CAN0_ErrFd_DriverIRQHandler(void);
void CAN0_PnWake_DriverIRQHandler(void);
void CAN0_SelfWakeup_DriverIRQHandler(void);
void CAN0_Ecc_DriverIRQHandler(void);
void CAN0_Mb0To15_DriverIRQHandler(void);
void CAN0_Mb16To31_DriverIRQHandler(void);
void CAN0_Mb32To47_DriverIRQHandler(void);
void CAN0_Mb48To63_DriverIRQHandler(void);
void CAN1_BusOff_DriverIRQHandler(void);
void CAN1_TxWarn_DriverIRQHandler(void);
void CAN1_RxWarn_DriverIRQHandler(void);
void CAN1_Err_DriverIRQHandler(void);
void CAN1_ErrFd_DriverIRQHandler(void);
void CAN1_PnWake_DriverIRQHandler(void);
void CAN1_SelfWakeup_DriverIRQHandler(void);
void CAN1_Ecc_DriverIRQHandler(void);
void CAN1_Mb0To15_DriverIRQHandler(void);
void CAN1_Mb16To31_DriverIRQHandler(void);
void CAN1_Mb32To47_DriverIRQHandler(void);
void CAN1_Mb48To63_DriverIRQHandler(void);
void CAN2_BusOff_DriverIRQHandler(void);
void CAN2_TxWarn_DriverIRQHandler(void);
void CAN2_RxWarn_DriverIRQHandler(void);
void CAN2_Err_DriverIRQHandler(void);
void CAN2_ErrFd_DriverIRQHandler(void);
void CAN2_PnWake_DriverIRQHandler(void);
void CAN2_SelfWakeup_DriverIRQHandler(void);
void CAN2_Ecc_DriverIRQHandler(void);
void CAN2_Mb0To15_DriverIRQHandler(void);
void CAN2_Mb16To31_DriverIRQHandler(void);
void CAN2_Mb32To47_DriverIRQHandler(void);
void CAN2_Mb48To63_DriverIRQHandler(void);
void CAN3_BusOff_DriverIRQHandler(void);
void CAN3_TxWarn_DriverIRQHandler(void);
void CAN3_RxWarn_DriverIRQHandler(void);
void CAN3_Err_DriverIRQHandler(void);
void CAN3_ErrFd_DriverIRQHandler(void);
void CAN3_PnWake_DriverIRQHandler(void);
void CAN3_SelfWakeup_DriverIRQHandler(void);
void CAN3_Ecc_DriverIRQHandler(void);
void CAN3_Mb0To15_DriverIRQHandler(void);
void CAN3_Mb16To31_DriverIRQHandler(void);
void CAN3_Mb32To47_DriverIRQHandler(void);
void CAN3_Mb48To63_DriverIRQHandler(void);
#if ((6U == CAN_INSTANCE_NUM) || (8U == CAN_INSTANCE_NUM ))
void CAN4_BusOff_DriverIRQHandler(void);
void CAN4_TxWarn_DriverIRQHandler(void);
void CAN4_RxWarn_DriverIRQHandler(void);
void CAN4_Err_DriverIRQHandler(void);
void CAN4_ErrFd_DriverIRQHandler(void);
void CAN4_PnWake_DriverIRQHandler(void);
void CAN4_SelfWakeup_DriverIRQHandler(void);
void CAN4_Ecc_DriverIRQHandler(void);
void CAN4_Mb0To15_DriverIRQHandler(void);
void CAN4_Mb16To31_DriverIRQHandler(void);
void CAN4_Mb32To47_DriverIRQHandler(void);
void CAN4_Mb48To63_DriverIRQHandler(void);
void CAN5_BusOff_DriverIRQHandler(void);
void CAN5_TxWarn_DriverIRQHandler(void);
void CAN5_RxWarn_DriverIRQHandler(void);
void CAN5_Err_DriverIRQHandler(void);
void CAN5_ErrFd_DriverIRQHandler(void);
void CAN5_PnWake_DriverIRQHandler(void);
void CAN5_SelfWakeup_DriverIRQHandler(void);
void CAN5_Ecc_DriverIRQHandler(void);
void CAN5_Mb0To15_DriverIRQHandler(void);
void CAN5_Mb16To31_DriverIRQHandler(void);
void CAN5_Mb32To47_DriverIRQHandler(void);
void CAN5_Mb48To63_DriverIRQHandler(void);
#endif
#if (8U == CAN_INSTANCE_NUM)
void CAN6_BusOff_DriverIRQHandler(void);
void CAN6_TxWarn_DriverIRQHandler(void);
void CAN6_RxWarn_DriverIRQHandler(void);
void CAN6_Err_DriverIRQHandler(void);
void CAN6_ErrFd_DriverIRQHandler(void);
void CAN6_PnWake_DriverIRQHandler(void);
void CAN6_SelfWakeup_DriverIRQHandler(void);
void CAN6_Ecc_DriverIRQHandler(void);
void CAN6_Mb0To31_DriverIRQHandler(void);
void CAN6_Mb32To63_DriverIRQHandler(void);
void CAN6_Mb64To95_DriverIRQHandler(void);
void CAN6_Mb96To127_DriverIRQHandler(void);
void CAN7_BusOff_DriverIRQHandler(void);
void CAN7_TxWarn_DriverIRQHandler(void);
void CAN7_RxWarn_DriverIRQHandler(void);
void CAN7_Err_DriverIRQHandler(void);
void CAN7_ErrFd_DriverIRQHandler(void);
void CAN7_PnWake_DriverIRQHandler(void);
void CAN7_SelfWakeup_DriverIRQHandler(void);
void CAN7_Ecc_DriverIRQHandler(void);
void CAN7_Mb0To31_DriverIRQHandler(void);
void CAN7_Mb32To63_DriverIRQHandler(void);
void CAN7_Mb64To95_DriverIRQHandler(void);
void CAN7_Mb96To127_DriverIRQHandler(void);
#endif
/** @} end of group CAN_Private_FunctionDeclaration */

/** @defgroup CAN_Private_Functions
 *  @{
 */


/**
 * @brief       get MB status
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: the MB index
 *
 * @return     SET/RESET
 *
 */
static FlagStatus_t CAN_GetMbIntStatus(CAN_Id_t id, uint32_t mbIdx)
{
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    FlagStatus_t ret= RESET;
    if(mbIdx < 32U)
    {
        ret = ((CANxw->CAN_IFLAG1 & (1UL << mbIdx)) != 0U) ? SET : RESET;    
    }
    else if(mbIdx < 64U)
    {
        ret = ((CANxw->CAN_IFLAG2 & (1UL << (mbIdx - 32U))) != 0U) ? SET : RESET;
    }
    else if(mbIdx < 96U)
    {
        if((CAN_ID_6 == id)||(CAN_ID_7 == id))
        {
            ret = ((CANxw->CAN_IFLAG3 & (1UL << (mbIdx - 64U))) != 0U) ? SET : RESET;
        }
        else
        {
            ret = RESET;
        }        
    }
    else if(mbIdx < 128U)
    {
        if((CAN_ID_6 == id)||(CAN_ID_7 == id))
        {
            ret = ((CANxw->CAN_IFLAG4 & (1UL << (mbIdx - 96U))) != 0U) ? SET : RESET;
        }
        else
        {
            ret = RESET;
        }  
    }
    else
    {
        /*nothing to do*/
    }    
    return ret;
}

/**
 * @brief     clear MB interrupt status
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: MB index to be cleared. For CAN0-5, its range is 0-63;
 *                    For CAN6-7, its range is 0-127
 * @return     status
 *
 */
static ResultStatus_t CAN_ClearMbIntStatus(CAN_Id_t id, uint32_t mbIdx)
{
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    uint32_t flag = ((uint32_t)1U << (mbIdx % 32U));
    ResultStatus_t ret = SUCC;
    /* Clear the corresponding message buffer interrupt flag*/
    if (mbIdx < 32U)
    {
        CANxw->CAN_IFLAG1 = flag;
    }
    else if(mbIdx < 64U)
    {
        CANxw->CAN_IFLAG2 = flag;
    }
    else if(mbIdx < 96U)
    {
        if((CAN_ID_6 == id)||(CAN_ID_7 == id))
        {
            CANxw->CAN_IFLAG3 = flag;
        }
        else
        {
            ret = ERR;
        }        
    }
    else if(mbIdx < 128U)
    {
        if((CAN_ID_6 == id)||(CAN_ID_7 == id))
        {
            CANxw->CAN_IFLAG4 = flag;
        }
        else
        {
            ret = ERR;
        }  
    }
    else
    {
        ret = ERR;
    }
    
    return ret;

}

/**
 * @brief  Computes the maximum payload size (in bytes), given a DLC field value
 *
 * @param[in]  dlcValue: the DLC field value
 *
 * @return payload size
 *
 */
static uint8_t CAN_ComputePayloadSize(uint8_t dlcValue)
{
    uint8_t ret = 0U;

    if (dlcValue <= 8U)
    {
        ret = dlcValue;
    }
    else
    {
        switch (dlcValue)
        {
            case CAN_DLC_VALUE_12_BYTES:
                ret = 12U;
                break;
            case CAN_DLC_VALUE_16_BYTES:
                ret = 16U;
                break;
            case CAN_DLC_VALUE_20_BYTES:
                ret = 20U;
                break;
            case CAN_DLC_VALUE_24_BYTES:
                ret = 24U;
                break;
            case CAN_DLC_VALUE_32_BYTES:
                ret = 32U;
                break;
            case CAN_DLC_VALUE_48_BYTES:
                ret = 48U;
                break;
            case CAN_DLC_VALUE_64_BYTES:
                ret = 64U;
                break;
            default:
                /* The argument is not a valid DLC size */
                break;
        }
    }

    return ret;
}

/**
 * @brief  Computes the DLC field value, and the actual data size given a data 
 *         length (in bytes).
 *
 * @param[in]  dataLen:datalength
 * @param[in-out]  dlc: length of data in bytes
 * @param[in-out]  dataSize:payload size
 *
 * @return none
 *
 */
static void CAN_ComputeDlcAndDataSize(uint32_t dataLen, uint32_t *dlc, 
                                      uint32_t *dataSize)
{
    uint32_t dlcVal;
    uint32_t dataSizeVal;
    
    if((NULL == dlc)||(NULL == dataSize))
    {
        /*Nothing to do*/
    }
    else
    {
        if (dataLen <= 8U)
        {
            dlcVal = dataLen;
            dataSizeVal = dataLen;
        }
        else if(dataLen <= 12U)
        {
            dlcVal = CAN_DLC_VALUE_12_BYTES;
            dataSizeVal = 12U;
        }
        else if(dataLen <= 16U)
        {
            dlcVal = CAN_DLC_VALUE_16_BYTES;
            dataSizeVal = 16U;
        }
        else if(dataLen <= 20U)
        {
            dlcVal = CAN_DLC_VALUE_20_BYTES;
            dataSizeVal = 20U;
        }
        else if(dataLen <= 24U)
        {
            dlcVal = CAN_DLC_VALUE_24_BYTES;
            dataSizeVal = 24U;
        }
        else if(dataLen <= 32U)
        {
            dlcVal = CAN_DLC_VALUE_32_BYTES;
            dataSizeVal = 32U;
        }
        else if(dataLen <= 48U)
        {
            dlcVal = CAN_DLC_VALUE_48_BYTES;
            dataSizeVal = 48U;
        }
        else 
        {
            dlcVal = CAN_DLC_VALUE_64_BYTES;
            dataSizeVal = 64U;
        }
        
        *dlc = dlcVal;
        *dataSize = dataSizeVal;
    }
   
}

/**
 * @brief      check if the given MB index is valid
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: MB index to be checked
 * @return     result
 *
 */
static ResultStatus_t CAN_CheckMbId(CAN_Id_t id, uint32_t mbIdx)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    ResultStatus_t ret =  SUCC;
    if ((mbIdx > CANx->CAN_MCR.MAXMB) || (mbIdx >= CAN_GET_MB_NUM(id)))
    {
        ret =  ERR;
    }
    if(SUCC == ret)
    {
        if (CANx->CAN_MCR.RFEN != 0U)
    	{
            if(mbIdx <= CAN_RX_FIFO_OCUP_LAST_MB_NUM((uint32_t)CANx->CAN_CTRL2.RFFN))
            {
                ret =  ERR;
            }
        }
    }
    
    return ret;
}

/**
 * @brief      Get the number of Rx FIFO ID Filter Table Elements 
 *             Affected by Rx Individual Masks.
 *
 * @param[in]  id: select the CAN ID
 *
 * @return     the max no of elements affected by Rx Individual Mask register 
 *             RXMIR in RxFIFO Mode
 *
 */
static inline uint32_t CAN_GetNoOfRxFIFOIndividualMask(CAN_Id_t id)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    
    /* Get the number of RX FIFO Filters*/
    uint32_t ret = CANx->CAN_CTRL2.RFFN;
    
    if(ret < 0x0CU)
    {
        /* Max filters configured by individual mask are (7 + RFFN * 2) depends 
           on the FIFO size */
        ret = (7u + (ret << 1u));
    }
    else
    {
        ret = 31U;
    }

    return ret;
}


/**
 * @brief      Enter freeze mode.
 *
 * @param[in]  id: select the CAN ID
 *
 * @return     result
 *
 */
static ResultStatus_t CAN_EnterFreezeMode(CAN_Id_t id)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    volatile uint32_t count = 0U;
    ResultStatus_t retVal = ERR;
    CANx->CAN_MCR.FRZ = 1U;
    CANx->CAN_MCR.HALT = 1U;
    if (0U != CANx->CAN_MCR.MDIS )
    {
        CANx->CAN_MCR.MDIS = 0U;
    }

    /* Wait for entering the freeze mode */
    while(count < CAN_TIMEOUT_WAIT_CNT_1)
    {
        count++;
        if(1U == CANx->CAN_MCR.NOTRDY )
        {
            break;
        }
    }
    
    if(count >= CAN_TIMEOUT_WAIT_CNT_1)
    {
        retVal = ERR;
    }
    else
    {
        count = 0U;
        while(count < CAN_TIMEOUT_WAIT_CNT_1)
        {
          count++;
          if(1U == CANx->CAN_MCR.FRZACK )
          {
              retVal = SUCC;
              break;
          }
        }
    }
    return retVal;
}

/**
 * @brief      exit freeze mode.
 *
 * @param[in]  id: select the CAN ID
 *
 * @return     result
 *
 */
static ResultStatus_t CAN_ExitFreezeMode(CAN_Id_t id)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    volatile uint32_t count = 0U;
    ResultStatus_t retVal = ERR;
    CANx->CAN_MCR.HALT = 0;
    CANx->CAN_MCR.FRZ = 0;
    
    /* Wait for exit the freeze mode */
    while(count < CAN_TIMEOUT_WAIT_CNT_2)
    {
        count++;
        if(0U == CANx->CAN_MCR.FRZACK )
        {
            retVal = SUCC;
            break;
        }
    }
    
    return retVal;
}

/**
 * @brief      Disable memory error detection
 *
 * @param[in]  id: select the CAN ID
 *
 * @return     none
 *
 */
static inline void CAN_DisableMemErrorDetection(CAN_Id_t id)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    
    /* Enable write of MECR register */
    CANx->CAN_CTRL2.ECRWRE = 1U;
    /* Enable write of MECR */
    CANx->CAN_MECR.ECRWRDIS = 0U;
    /* Disable Error Detection and Correction mechanism,
    that will set CAN in Freeze Mode in case of trigger */
    CANx->CAN_MECR.NCEFAFRZ = 0U;
    /* Disable write of MECR */
    CANx->CAN_CTRL2.ECRWRE = 0U;
}

/**
 * @brief      the payload size of the MBs
 *
 * @param[in]  id: select the CAN ID
 @ @param[in]  region:CAN FD MB region
 *
 * @return      the payload size of the MBs (in bytes).
 *
 */
static uint8_t CAN_GetPayloadSize(CAN_Id_t id,CAN_FdMbRegion_t region)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    uint32_t payloadSize;

    /* The standard payload size is 8 bytes */
    if (CANx->CAN_MCR.FDEN != 0U)
    {
        if(CAN_FD_MB_REGION_0 == region)
        {
            /* the payload size of region 0 */
            payloadSize = 1UL << (CANx->CAN_FDCTRL.MBDSR0 + 3U);
        }
        else if(CAN_FD_MB_REGION_1 == region)
        {
            /* the payload size of region1 */
            payloadSize = 1UL << (CANx->CAN_FDCTRL.MBDSR1 + 3U);
        }
        else if(CAN_FD_MB_REGION_2 == region)
        {
            /* the payload size of region2 */
            payloadSize = 1UL << (CANx->CAN_FDCTRL.MBDSR2 + 3U);
        }
        else
        {
            /* the payload size of region3 */
            payloadSize = 1UL << (CANx->CAN_FDCTRL.MBDSR3 + 3U);
        }
    }
    else
    {
        payloadSize = 8U;        
    }

    return (uint8_t)payloadSize;
}

/**
 * @brief      get the limit of max MB number, the actual MB number can not 
 *             exceed it
 *
 * @param[in]  id: select the CAN ID
 *
 * @return     the limit of max MB number 
 *
 */
static uint8_t CAN_GetMaxMbNumLimit(CAN_Id_t id)
{
    uint32_t payloadSize;
    uint8_t configFieldSize = 8U;
    uint32_t ramBlockSize = 512U;
    uint32_t mbSize;
    uint32_t totalMbNum;

    payloadSize = CAN_GetPayloadSize(id,CAN_FD_MB_REGION_0);
    mbSize= payloadSize + configFieldSize;
    totalMbNum = ramBlockSize / mbSize;
    
    payloadSize = CAN_GetPayloadSize(id,CAN_FD_MB_REGION_1);
    mbSize= payloadSize + configFieldSize;
    totalMbNum += (ramBlockSize / mbSize);
    
    if((CAN_ID_6 == id ) || (CAN_ID_7 == id))
    {
        payloadSize = CAN_GetPayloadSize(id,CAN_FD_MB_REGION_2);
        mbSize= payloadSize + configFieldSize;
        totalMbNum += (ramBlockSize / mbSize);
    
        payloadSize = CAN_GetPayloadSize(id,CAN_FD_MB_REGION_3);
        mbSize= payloadSize + configFieldSize;
        totalMbNum += (ramBlockSize / mbSize);
    }
    
    return (uint8_t)totalMbNum;
}

/**
 * @brief      get the start address of a MB
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: MB index
 * @param[in]  region: point to the address where the region number will 
 *                     be stored 
 * @param[in]  addr: point to the address where the start address of the MB will
 *                   be stored
 *
 * @return     status
 *
 */
static ResultStatus_t CAN_GetMbAddr(CAN_Id_t id,uint8_t mbIdx,
                                      CAN_FdMbRegion_t *region,
                                      CAN_Mb_t **addr)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    uint8_t payloadSize;
    uint8_t configFieldSize = 8U;
    uint32_t ramBlockSize = 512U;
    uint32_t ramBlockOffset = 0U;
    uint32_t mbSize;
    uint32_t regionMaxMbNum = 0U;
    uint32_t mbOffset;
    CAN_FdMbRegion_t maxRegionIndex;
    uint32_t maxRamSize;
    uint32_t index;
    ResultStatus_t res = SUCC;
    
    if(region != NULL)
    {
        *region = CAN_FD_MB_REGION_0;
    }
    
    maxRegionIndex = ((uint32_t)id < (uint32_t)CAN_ID_6) ? CAN_FD_MB_REGION_1 : 
                                         CAN_FD_MB_REGION_3;
    
    for(index = 0U; index <= (uint32_t)maxRegionIndex; index++)
    {
        mbIdx -= (uint8_t)regionMaxMbNum;
        
        payloadSize = CAN_GetPayloadSize(id,(CAN_FdMbRegion_t)index);
        mbSize= (uint32_t)payloadSize + (uint32_t)configFieldSize;
        regionMaxMbNum  = ramBlockSize / mbSize;
        
        if(region != NULL)
        {
            *region = (CAN_FdMbRegion_t)index;
        }
        
        if(mbIdx < regionMaxMbNum)
        {
            /* Multiply the MB index by the MB size (in words) */
            mbOffset = ramBlockOffset + mbIdx * mbSize;
            /*PRQA S 0303 ++*/
            *addr = (CAN_Mb_t *)((uint32_t)&(CANx->CAN_MB[0]) + mbOffset);
            /*PRQA S 0303 --*/
            break;
        }
        else
        {
            ramBlockOffset += 512U;
        }
    }
    maxRamSize = ((uint32_t)id < (uint32_t)CAN_ID_6)? CAN05_RAM_SIZE_IN_BYTE : 
                  CAN67_RAM_SIZE_IN_BYTE;
    if(ramBlockOffset >= maxRamSize)
    {
        res = ERR;
    }
      
    return res;
}

/**
 * @brief Set TX message buffer.It copys user's buffer into the message buffer 
 * data area and configure the message buffer as required for transmission.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: MB index
 * @param[in]  messInfo: message info config
 * @param[in]  msgId: config message id
 * @param[in]  msgData: message data
 * @param[in]  code: code command
 * @param[in]  localPrio: priority
 *
 * @return 
 *        -SUCC: set tx MB successfully
 *        -ERR:  fail to tx MB 
 */
static ResultStatus_t CAN_SetTxMb(CAN_Id_t id, uint8_t mbIdx,
                                      const CAN_MessageInfo_t *messInfo, 
                                      uint32_t msgId, const uint8_t *msgData,
                                      uint32_t code, uint8_t localPrio)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    ResultStatus_t retVal = SUCC;
    uint8_t count;
    uint8_t tmpNum;
    uint8_t tmpIndex;
    uint32_t dlc;
    uint32_t dataSize;
    CAN_FdMbRegion_t region;
    CAN_Mb_t *mbAddr;
    volatile uint8_t  *mbData;
    
    if(ERR == CAN_GetMbAddr(id, mbIdx, &region, &mbAddr))
    {
        retVal = ERR;
    }
    else if(messInfo->dataLen > 64U)
    {
        retVal = ERR;
    }
    else
    {
        mbData = (volatile uint8_t *)(&mbAddr->data[0]);
    
        if(ERR == CAN_CheckMbId(id,mbIdx))
        {
            retVal = ERR;
        }
        else
        {
            if(CANx->CAN_MCR.FDEN != 0U)
            {
                if(messInfo->brsEn == ENABLE)
                {
                    CANx->CAN_FDCTRL.FD_RATE = 1U;
                }
            }
        
            if(messInfo->dataLen > CAN_GetPayloadSize(id,region))
            {
                retVal = ERR;
            }
            else
            {
                CAN_ComputeDlcAndDataSize(messInfo->dataLen,&dlc, &dataSize);   
        
                /* Copy user's buffer into the message buffer data area */
                if(msgData != NULL)
                {
                    tmpNum = (uint8_t)(messInfo->dataLen >> 2U);
                    for (count = 0; count < tmpNum; count += 1U)
                    {
                        mbAddr->data[count] = ((uint32_t)msgData[count*4U] << 24U) |
                                             ((uint32_t)msgData[count*4U + 1U] << 16U)|
                                             ((uint32_t)msgData[count*4U + 2U] << 8U) |
                                             (uint32_t)msgData[count*4U + 3U];   
                    }

                    for ( count = tmpNum*4U; count < messInfo->dataLen; count++)
                    {
                        tmpIndex = CAN_SWAP_BYTES_IN_WORD_INDEX(count) & 0x3FU;
                        mbData[tmpIndex] =  msgData[count];
                    }
                    /* Add padding, if needed */
                    for (count = messInfo->dataLen; count < (uint8_t)dataSize; count++)
                    {
                        tmpIndex = CAN_SWAP_BYTES_IN_WORD_INDEX(count) & 0x3FU;
                        mbData[tmpIndex] = messInfo->fdPadding;
                    }
                }        
            
                mbAddr->config.WORDVAL = 0U;
                mbAddr->id.WORDVAL = 0U;   
                /* set DLC */
                mbAddr->config.BF.DLC = dlc;
            
                /* Set the ID according the format structure */
                if (CAN_MSG_ID_EXT == messInfo->idType)
                {
                    /* ID [28-0] */
                    mbAddr->id.WORDVAL = msgId & CAN_ID_EXT_MASK;
                    mbAddr->id.BF.PRIO = localPrio;
                    /* Set IDE */
                    mbAddr->config.BF.IDE = 1U;
                    /* Set SRR bit */
                    mbAddr->config.BF.SRR = 1U;
                }
                else
                {
                    /* ID[28-18] */
                    mbAddr->id.BF.ID_STANDARD = msgId;
                    mbAddr->id.BF.PRIO = localPrio;

                    /* clear IDE  */
                    mbAddr->config.BF.IDE = 0U;
                    /* Clear SRR bit */
                    mbAddr->config.BF.SRR = 0U;
                }
                
                if(SET == messInfo->remoteFlag )
                {
                    /* Set RTR bit */
                    mbAddr->config.BF.RTR = 1U;
                }
                
                /* Set MB CODE */
                /* Reset the code */
                mbAddr->config.BF.CODE = 0U;
                        
                if (ENABLE == messInfo->fdEn)
                {
                    mbAddr->config.BF.EDL = 1U;
                }
                        
                mbAddr->config.BF.BRS = (uint32_t)(messInfo->brsEn);
                        
                /* Set the code */
                mbAddr->config.BF.CODE = code;           
            }
        }
        
    }
    return retVal;
}

/**
 * @brief Set Rx message buffer. It copys user's buffer into the message buffer 
 * data area and configure the message buffer as required for transmission.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: MB index
 * @param[in]  idType: CAN Message ID type
 * @param[in]  msgId: config message id
 * @param[in]  code: code command
 *
 * @return  ERR/SUCC
 *
 *
 */
static ResultStatus_t CAN_SetRxMb(CAN_Id_t id, uint8_t mbIdx,
                                  CAN_MsgId_t idType, 
                                  uint32_t msgId, uint32_t code)
{
    CAN_FdMbRegion_t region;
    CAN_Mb_t *mbAddr;
    ResultStatus_t retVal = SUCC;
    if(ERR == CAN_GetMbAddr(id, mbIdx, &region, &mbAddr))
    {
        retVal = ERR;
    }  
    else if(ERR == CAN_CheckMbId(id,mbIdx))
    {
        retVal = ERR;
    }
    else
    {
        mbAddr->config.WORDVAL = 0U;
        mbAddr->id.WORDVAL = 0U;   
        
        /* Set the ID according to the format structure */
        if (CAN_MSG_ID_EXT == idType)
        {
            /* ID [28-0] */
            mbAddr->id.WORDVAL = msgId & CAN_ID_EXT_MASK;
            /* Set IDE */
            mbAddr->config.BF.IDE = 1U;
            /* Clear SRR bit */
            mbAddr->config.BF.SRR = 0U;
        }
        else
        {
            /* ID[28-18] */
            mbAddr->id.BF.ID_STANDARD = msgId;

            /* clear IDE  */
            mbAddr->config.BF.IDE = 0U;
            /* Clear SRR bit */
            mbAddr->config.BF.SRR = 0U;
        }
        
        if(code != CAN_NOT_USED)
        {
            mbAddr->config.BF.CODE = code;
        }       
    }
    return retVal;
}


/**
 * @brief Clears CAN memory positions that require initialization.
 *
 * @param[in]  id: select the CAN ID
 * 
 * @return none
 *
 */
static void CAN_ClearRam(CAN_Id_t id)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    uint32_t dataByte;
    uint32_t ramSize;
    uint32_t rxImrSize;
    volatile uint32_t *RAM = &(CANxw->CAN_MB[0].CS);
    
    if((uint32_t)id < (uint32_t)CAN_ID_6)
    {
        ramSize = CAN05_RAM_SIZE_IN_WORD;
        rxImrSize = CAN05_MB_NUM;
    }
    else
    {
        ramSize = CAN67_RAM_SIZE_IN_WORD;
        rxImrSize = CAN67_MB_NUM;
    }

    CANx->CAN_CTRL2.WRMFRZ = 1U;
    /* Clear MB region */
    for (dataByte = 0U; dataByte < ramSize; dataByte++)
    {
        RAM[dataByte] = 0x0U;
    }

    RAM = &(CANxw->CAN_RXIMR[0]);

    /* Clear RXIMR region */
    for (dataByte = 0; dataByte < rxImrSize; dataByte++)
    {
        RAM[dataByte] = 0xFFFFFFFFU;
    }
    
    /* init mask */
    CANxw->CAN_RXMGMSK = 0xFFFFFFFFU;
    CANxw->CAN_RX14MASK = 0xFFFFFFFFU;
    CANxw->CAN_RX15MASK = 0xFFFFFFFFU;
    
    /* RX FIFO global mask */
    CANxw->CAN_RXFGMASK = 0xFFFFFFFFU;
  
    /* RX FIFO */
    /*PRQA S 0303 ++*/
    RAM = (volatile uint32_t*)((uint32_t)canRegPtr[id] + CAN_RAM_RX_FIFO_ADDR);
    /*PRQA S 0303 --*/
    for (dataByte = 0U; dataByte < CAN_RAM_RX_FIFO_LEN_IN_WORD; dataByte++)
    {
        RAM[dataByte] = 0U;
    }
    
    /* RXMGMASK, RXFGMASK, RX14MSK, RX15MASK */
    /*PRQA S 0303 ++*/
    RAM = (volatile uint32_t*)((uint32_t)canRegPtr[id] + CAN_RAM_MSK_ADDR);
    /*PRQA S 0303 --*/
    for (dataByte = 0U; dataByte < CAN_RAM_MSK_LEN_IN_WORD; dataByte++)
    {
        RAM[dataByte] = 0xFFFFFFFFU;
    }
    
    /* Rx_SMB0, Rx_SMB1 */
    /*PRQA S 0303 ++*/
    RAM = (volatile uint32_t*)((uint32_t)canRegPtr[id] + CAN_RAM_RX_SMB_ADDR);
    /*PRQA S 0303 --*/
    for (dataByte = 0U; dataByte < CAN_RAM_RX_SMB_LEN_IN_WORD; dataByte++)
    {
        RAM[dataByte] = 0U;
    }
    
    /* CAN-FD scratch memory */
    /*PRQA S 0303 ++*/
    RAM = (volatile uint32_t*)((uint32_t)canRegPtr[id] + CAN_RAM_FD_SCRATCH_ADDR);    
    /*PRQA S 0303 --*/
    for (dataByte = 0U; dataByte < CAN_RAM_FD_SCRATCH_LEN_IN_WORD; dataByte++)
    {
        RAM[dataByte] = 0U;
    }
    CANx->CAN_CTRL2.WRMFRZ = 0U;
}

/**
 * @brief      CAN handler for bus off/ bus off done interrupts
 *
 * @param[in]  id: select the CAN ID
 *
 * @return    none
 *
 */ 
static void CAN_BusOffHandler(CAN_Id_t id)
{
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    uint32_t status;
    
    status = CANxw->CAN_ESR1; 
    /* only check enabled interrupts */
    status = status & (canIntMaskStatus1[id] & CAN_INT_MSK_FLAG_ALL_BUSOFF);
    /* clear int status */
    CANxw->CAN_ESR1 = status;
    
    /* bus off interrupt */
    if((status & CAN_INT_MSK_FLAG_BUS_OFF) != 0U)
    {
        if(canIsrCbFunc[id].cbf[CAN_INT_BUS_OFF] != NULL)
        {
            canIsrCbFunc[id].cbf[CAN_INT_BUS_OFF]();
        }
        else
        {
            if(SUCC != CAN_IntMask(id, CAN_INT_BUS_OFF, MASK, 0, 0, 0, 0))
            {
                /* user can add code here to handle this error */
            }
        }            
    }
    
    /* bus off done interrupt */
    if((status & CAN_INT_MSK_FLAG_BUS_OFF_DONE) != 0U)
    {
        if(canIsrCbFunc[id].cbf[CAN_INT_BUS_OFF_DONE] != NULL)
        {
            canIsrCbFunc[id].cbf[CAN_INT_BUS_OFF_DONE]();
        }
        else
        {
            if(SUCC != CAN_IntMask(id, CAN_INT_BUS_OFF_DONE, MASK, 0, 0, 0, 0))
            {
                /* user can add code here to handle this error */
            }
        }            
    }
    
}

/**
 * @brief      CAN Handler for TX warning interrupt
 *
 * @param[in]  id: select the CAN ID
 *
 * @return    none
 *
 */ 
static void CAN_TxWarnHandler(CAN_Id_t id)
{
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    
    /* clear TX warning interrupt status */
    CANxw->CAN_ESR1 = CAN_INT_MSK_FLAG_TXW;
    
    if(canIsrCbFunc[id].cbf[CAN_INT_TXW] != NULL)
    {
        canIsrCbFunc[id].cbf[CAN_INT_TXW]();
    }
    else
    {
        if(SUCC != CAN_IntMask(id, CAN_INT_TXW, MASK, 0, 0, 0, 0))
        {
            /* user can add code here to handle this error */
        }
    }  
}

/**
 * @brief      CAN Handler for RX warning interrupt
 *
 * @param[in]  id: select the CAN ID
 *
 * @return    none
 *
 */
static void CAN_RxWarnHandler(CAN_Id_t id)
{
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    
    /* clear interrupt status */
    CANxw->CAN_ESR1 = CAN_INT_MSK_FLAG_RXW;
    
    if(canIsrCbFunc[id].cbf[CAN_INT_RXW] != NULL)
    {
        canIsrCbFunc[id].cbf[CAN_INT_RXW]();
    }
    else
    {
        if(SUCC != CAN_IntMask(id, CAN_INT_RXW, MASK, 0, 0, 0, 0))
        {
            /* user can add code here to handle this error */
        }
    }  
}

/**
 * @brief      CAN Handler for Error interrupt
 *
 * @param[in]  id: select the CAN ID
 *
 * @return    none
 *
 */
static void CAN_ErrHandler(CAN_Id_t id)
{
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    
    canEsr1Buf[id] = CANxw->CAN_ESR1;
    
    /* clear interrupt status */
    CANxw->CAN_ESR1 = CAN_INT_MSK_FLAG_ERR;
        
    if(canIsrCbFunc[id].cbf[CAN_INT_ERR] != NULL)
    {
        canIsrCbFunc[id].cbf[CAN_INT_ERR]();
    }
    else
    {
        if(SUCC != CAN_IntMask(id, CAN_INT_ERR, MASK, 0, 0, 0, 0))
        {
            /* user can add code here to handle this error */
        }
    }  
    
    canEsr1Buf[id] = 0;
}

/**
 * @brief      CAN Handler for Error fast interrupt (CAN_INT_ERR_FAST)
 *
 * @param[in]  id: select the CAN ID
 *
 * @return    none
 *
 */
static void CAN_ErrFdHandler(CAN_Id_t id)
{
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    
    canEsr1Buf[id] = CANxw->CAN_ESR1;
    
    /* clear interrupt status */
    CANxw->CAN_ESR1 = CAN_INT_MSK_FLAG_ERR_FAST;
    
    if(canIsrCbFunc[id].cbf[CAN_INT_ERR_FAST] != NULL)
    {
        canIsrCbFunc[id].cbf[CAN_INT_ERR_FAST]();
    }
    else
    {
        if(SUCC != CAN_IntMask(id, CAN_INT_ERR_FAST, MASK, 0, 0, 0, 0))
        {
            /* user can add code here to handle this error */
        }
    }  
    
    canEsr1Buf[id] = 0;
}

/**
 * @brief      CAN Handler for pretended networking wakeup interrupt including
 *             CAN_INT_PN_WAKE_MATCH and CAN_INT_PN_WAKE_TIMEOUT
 *
 * @param[in]   id: select the CAN ID
 *
 * @return    none
 *
 */
static void CAN_PnWakeHandler(CAN_Id_t id)
{
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    uint32_t status;
    
    status = CANxw->CAN_WU_MTC; 
    /* only check enabled interrupts */
    status = status & (CANxw->CAN_CTRL1_PN & CAN_INT_MSK_FLAG_ALL_PN);
    /* clear int status */
    CANxw->CAN_WU_MTC = status;
    
    /* wakeup match interrupt */
    if((status & CAN_INT_MSK_FLAG_PN_WAKEUP_MATCH) != 0U)
    {
        if(canIsrCbFunc[id].cbf[CAN_INT_PN_WAKEUP_MATCH] != NULL)
        {
            canIsrCbFunc[id].cbf[CAN_INT_PN_WAKEUP_MATCH]();
        }
        else
        {
            if(SUCC != CAN_IntMask(id, CAN_INT_PN_WAKEUP_MATCH, MASK, 0, 0, 0, 0))
            {
                /* user can add code here to handle this error */
            }
        }            
    }
    
    /* wakeup timeout interrupt */
    if((status & CAN_INT_MSK_FLAG_PN_WAKEUP_TIMEOUT) != 0U)
    {
        if(canIsrCbFunc[id].cbf[CAN_INT_PN_WAKEUP_TIMEOUT] != NULL)
        {
            canIsrCbFunc[id].cbf[CAN_INT_PN_WAKEUP_TIMEOUT]();
        }
        else
        {
            if(SUCC != CAN_IntMask(id, CAN_INT_PN_WAKEUP_TIMEOUT, MASK, 0, 0, 0, 0))
            {
                /* user can add code here to handle this error */
            }
        }            
    }
}

/**
 * @brief      CAN Handler for self wakeup interrupt
 *
 * @param[in]  id: select the CAN ID
 *
 * @return    none
 *
 */
static void CAN_SelfWakeupHandler(CAN_Id_t id)
{
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    
    /* clear interrupt status */
    CANxw->CAN_ESR1 = CAN_INT_MSK_FLAG_SELF_WAKEUP;
    
    if(canIsrCbFunc[id].cbf[CAN_INT_SELF_WAKEUP] != NULL)
    {
        canIsrCbFunc[id].cbf[CAN_INT_SELF_WAKEUP]();
    }
    else
    {
        if(SUCC != CAN_IntMask(id, CAN_INT_SELF_WAKEUP, MASK, 0, 0, 0, 0))
        {
            /* user can add code here to handle this error */
        }
    }  
}

/**
 * @brief      CAN Handler for ECC error interrupt(including CAN_INT_HOST_MEM_ERR,
 *             CAN_INT_CAN_MEM_ERR and CAN_INT_COR_MEM_ERR
 *
 * @param[in]  id: select the CAN ID
 *
 * @return    none
 *
 */
static void CAN_EccHandler(CAN_Id_t id)
{
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    uint32_t status;
    
    status = CANxw->CAN_ERRSR; 
    /* only check enabled interrupts */
    status = status & (CANxw->CAN_MECR & CAN_INT_MSK_FLAG_ALL_ECC);
    /* clear int status */
    CANxw->CAN_ERRSR = status;
    
    /* Host Access With Non-Correctable Error Interrupt */
    if((status & CAN_INT_MSK_FLAG_HOST_MEM_ERR) != 0U)
    {
        if(canIsrCbFunc[id].cbf[CAN_INT_HOST_MEM_ERR] != NULL)
        {
            canIsrCbFunc[id].cbf[CAN_INT_HOST_MEM_ERR]();
        }
        else
        {
            if(SUCC != CAN_IntMask(id, CAN_INT_HOST_MEM_ERR, MASK, 0, 0, 0, 0))
            {
                /* user can add code here to handle this error */
            }
        }            
    }
    
    /* CAN Access With Non-Correctable Error Interrupt */
    if((status & CAN_INT_MSK_FLAG_CAN_MEM_ERR) != 0U)
    {
        if(canIsrCbFunc[id].cbf[CAN_INT_CAN_MEM_ERR] != NULL)
        {
            canIsrCbFunc[id].cbf[CAN_INT_CAN_MEM_ERR]();
        }
        else
        {
            if(SUCC != CAN_IntMask(id, CAN_INT_CAN_MEM_ERR, MASK, 0, 0, 0, 0))
            {
                /* user can add code here to handle this error */
            }
        }            
    }
    /* Correctable Error Interrupt */
    if((status & CAN_INT_MSK_FLAG_COR_MEM_ERR) != 0U)
    {
        if(canIsrCbFunc[id].cbf[CAN_INT_COR_MEM_ERR] != NULL)
        {
            canIsrCbFunc[id].cbf[CAN_INT_COR_MEM_ERR]();
        }
        else
        {
            if(SUCC != CAN_IntMask(id, CAN_INT_COR_MEM_ERR, MASK, 0, 0, 0, 0))
            {
                /* user can add code here to handle this error */
            }
        }            
    }
}

/**
 * @brief      CAN Handler for MB0 - MB15 interrupts
 *
 * @param[in]  id: select the CAN ID
 *
 * @return    none
 *
 */
static void CAN05_Mb0To15Handler(CAN_Id_t id)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    uint32_t totalMbNum = (uint32_t)CANx->CAN_MCR.MAXMB + 1U;
    uint32_t maxMb;
    uint32_t status;
    uint32_t mbId;
    
    status = CANxw->CAN_IFLAG1;
    status &= CANxw->CAN_IMASK1;
    status &= 0xFFFFU;
    
    maxMb = (totalMbNum > 16U) ? 16U : totalMbNum;
    for(mbId = 0U; mbId < maxMb; mbId++)
    {
        if((status & (0x00000001UL << mbId)) != 0U)
        {
            if((CANx->CAN_MCR.RFEN != 0U) && (mbId <= CAN_RXFIFO_OVERFLOW))
            {
                /* RX FIFO frame available interrupt */
                if(CAN_RXFIFO_FRAME_AVAILABLE == mbId)
                {
                    if(canIsrCbFunc[id].cbf[CAN_INT_RXFIFO_FRAME] != NULL)
                    {
                        canIsrCbFunc[id].cbf[CAN_INT_RXFIFO_FRAME]();
                    }
                    else
                    {
                        CANxw->CAN_IMASK1 &= ~CAN_INT_MSK_FLAG_RXFIFO_FRAME;
                    }
                }
                /* RX FIFO warning interrupt */
                if(CAN_RXFIFO_WARNING == mbId)
                {
                    if(canIsrCbFunc[id].cbf[CAN_INT_RXFIFO_WARNING] != NULL)
                    {
                        canIsrCbFunc[id].cbf[CAN_INT_RXFIFO_WARNING]();
                    }
                    else
                    {
                        CANxw->CAN_IMASK1 &= ~CAN_INT_MSK_FLAG_RXFIFO_WARNING;
                    }
                }
                /* RX FIFO overflow interrupt */
                if(CAN_RXFIFO_OVERFLOW == mbId)
                {
                    if(canIsrCbFunc[id].cbf[CAN_INT_RXFIFO_OVERFLOW] != NULL)
                    {
                        canIsrCbFunc[id].cbf[CAN_INT_RXFIFO_OVERFLOW]();
                    }
                    else
                    {
                        CANxw->CAN_IMASK1 &= ~CAN_INT_MSK_FLAG_RXFIFO_OVERFLOW;
                    }
                }                    
            }
            else
            {
                if(canIsrCbFunc[id].mbCbf[CAN05_MB_INT_0TO15] != NULL)
                {
                    canIsrCbFunc[id].mbCbf[CAN05_MB_INT_0TO15](mbId);
                }
                else
                {
                    CANxw->CAN_IMASK1 &= ~(0x00000001UL<<mbId);
                }
            }
                
            /* clear MB interrupt */
            CANxw->CAN_IFLAG1 = 0x00000001UL<<mbId;                
        }
    }
}

/**
 * @brief      CAN Handler for MB16 - MB31 interrupts of CAN0-5
 *
 * @param[in]  id: select the CAN ID
 *
 * @return    none
 *
 */
static void CAN05_Mb16To31Handler(CAN_Id_t id)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    uint32_t totalMbNum = (uint32_t)CANx->CAN_MCR.MAXMB + 1U;
    uint32_t maxMb;
    uint32_t status;
    uint32_t mbId;
    
    status = CANxw->CAN_IFLAG1;
    status &= CANxw->CAN_IMASK1;
    status &= 0xFFFF0000U;
    
    maxMb = (totalMbNum > 32U) ? 32U : totalMbNum;
    for(mbId = 16U; mbId < maxMb; mbId++)
    {
        if((status & (0x00000001UL << mbId)) != 0U)
        {
            if(canIsrCbFunc[id].mbCbf[CAN05_MB_INT_16TO31] != NULL)
            {
                canIsrCbFunc[id].mbCbf[CAN05_MB_INT_16TO31](mbId);
            }
            else
            {
                CANxw->CAN_IMASK1 &= ~(0x00000001UL<< mbId);
            }
        }
                
        /* clear MB interrupt */
        CANxw->CAN_IFLAG1 = 0x00000001UL << mbId;                
    }
}

/**
 * @brief      CAN Handler for MB32 - MB47 interrupts
 *
 * @param[in]  id: select the CAN ID
 *
 * @return    none
 *
 */
static void CAN05_Mb32To47Handler(CAN_Id_t id)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    uint32_t totalMbNum = (uint32_t)CANx->CAN_MCR.MAXMB + 1U;
    uint32_t maxMb;
    uint32_t status;
    uint8_t mbId;
    
    status = CANxw->CAN_IFLAG2;
    status &= CANxw->CAN_IMASK2;
    status &= 0xFFFFU;
    
    maxMb = (totalMbNum > 48U) ? 48U : totalMbNum;
    for(mbId = 32U; mbId < maxMb; mbId++)
    {
        if((status & (0x00000001UL << (mbId -32U))) != 0U)
        {
            if(canIsrCbFunc[id].mbCbf[CAN05_MB_INT_32TO47] != NULL)
            {
                canIsrCbFunc[id].mbCbf[CAN05_MB_INT_32TO47](mbId);
            }
            else
            {
                CANxw->CAN_IMASK2 &= ~(0x00000001UL<<(mbId -32U));
            }
        }
                
        /* clear MB interrupt */
        CANxw->CAN_IFLAG2 = 0x00000001UL<<(mbId -32U);
    }
}

/**
 * @brief      CAN Handler for MB48 - MB63 interrupts
 *
 * @param[in]  id: select the CAN ID
 *
 * @return    none
 *
 */
static void CAN05_Mb48To63Handler(CAN_Id_t id)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    uint32_t totalMbNum = (uint32_t)CANx->CAN_MCR.MAXMB + 1U;
    uint32_t maxMb;
    uint32_t status;
    uint32_t mbId;
    
    status = CANxw->CAN_IFLAG2;
    status &= CANxw->CAN_IMASK2;
    status &= 0xFFFF0000U;
    
    maxMb = (totalMbNum > 64U) ? 64U : totalMbNum;
    for(mbId = 48U; mbId < maxMb; mbId++)
    {
        if((status & (0x00000001UL << (mbId - 32U))) != 0U)
        {
            if(canIsrCbFunc[id].mbCbf[CAN05_MB_INT_48TO63] != NULL)
            {
                canIsrCbFunc[id].mbCbf[CAN05_MB_INT_48TO63](mbId);
            }
            else
            {
                CANxw->CAN_IMASK2 &= ~(0x00000001UL << (mbId - 32U));
            }
        }
                
        /* clear MB interrupt */
        CANxw->CAN_IFLAG2 = 0x00000001UL<<(mbId - 32U);
    }
}

#if (8U == CAN_INSTANCE_NUM)
/**
 * @brief      CAN Handler for MB0 - MB31 interrupts
 *
 * @param[in]  id: select the CAN ID
 *
 * @return    none
 *
 */
static void CAN67_Mb0To31Handler(CAN_Id_t id)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    uint32_t totalMbNum = (uint32_t)CANx->CAN_MCR.MAXMB + 1U;
    uint32_t maxMb;
    uint32_t status;
    uint32_t mbId;
    
    status = CANxw->CAN_IFLAG1;
    status &= CANxw->CAN_IMASK1;
    
    maxMb = (totalMbNum > 32U) ? 32U : totalMbNum;
    for(mbId = 0U; mbId < maxMb; mbId++)
    {
        if((status & (0x00000001UL << mbId)) != 0U)
        {
            if((CANx->CAN_MCR.RFEN != 0U) && (mbId <= CAN_RXFIFO_OVERFLOW))
            {
                /* RX FIFO frame available interrupt */
                if(CAN_RXFIFO_FRAME_AVAILABLE == mbId)
                {
                    if(canIsrCbFunc[id].cbf[CAN_INT_RXFIFO_FRAME] != NULL)
                    {
                        canIsrCbFunc[id].cbf[CAN_INT_RXFIFO_FRAME]();
                    }
                    else
                    {
                        CANxw->CAN_IMASK1 &= ~CAN_INT_MSK_FLAG_RXFIFO_FRAME;
                    }
                }
                /* RX FIFO warning interrupt */
                else if (CAN_RXFIFO_WARNING == mbId)
                {
                    if(canIsrCbFunc[id].cbf[CAN_INT_RXFIFO_WARNING] != NULL)
                    {
                        canIsrCbFunc[id].cbf[CAN_INT_RXFIFO_WARNING]();
                    }
                    else
                    {
                        CANxw->CAN_IMASK1 &= ~CAN_INT_MSK_FLAG_RXFIFO_WARNING;
                    }
                }
                /* RX FIFO overflow interrupt */
                else if (CAN_RXFIFO_OVERFLOW == mbId)
                {
                    if(canIsrCbFunc[id].cbf[CAN_INT_RXFIFO_OVERFLOW] != NULL)
                    {
                        canIsrCbFunc[id].cbf[CAN_INT_RXFIFO_OVERFLOW]();
                    }
                    else
                    {
                        CANxw->CAN_IMASK1 &= ~CAN_INT_MSK_FLAG_RXFIFO_OVERFLOW;
                    }
                }
                else
                {
                      /*nothing to do*/
                }
            }
            else
            {
                if(canIsrCbFunc[id].mbCbf[CAN67_MB_INT_0TO31] != NULL)
                {
                    canIsrCbFunc[id].mbCbf[CAN67_MB_INT_0TO31](mbId);
                }
                else
                {
                    CANxw->CAN_IMASK1 &= ~(0x00000001UL << mbId);
                }
            }
                
            /* clear MB interrupt */
            CANxw->CAN_IFLAG1 = 0x00000001UL << mbId;                
        }
    }
}

/**
 * @brief      CAN Handler for MB32 - MB63 interrupts of CAN6-7
 *
 * @param[in]  id: select the CAN ID
 *
 * @return    none
 *
 */
static void CAN67_Mb32To63Handler(CAN_Id_t id)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    uint32_t totalMbNum = (uint32_t)CANx->CAN_MCR.MAXMB + 1U;
    uint32_t maxMb;
    uint32_t status;
    uint32_t mbId;
    
    status = CANxw->CAN_IFLAG2;
    status &= CANxw->CAN_IMASK2;
    
    maxMb = (totalMbNum > 64U) ? 64U : totalMbNum;
    for(mbId = 32U; mbId < maxMb; mbId++)
    {
        if((status & (0x00000001UL << (mbId - 32U))) != 0U)
        {
            if(canIsrCbFunc[id].mbCbf[CAN67_MB_INT_32TO63] != NULL)
            {
                canIsrCbFunc[id].mbCbf[CAN67_MB_INT_32TO63](mbId);
            }
            else
            {
                CANxw->CAN_IMASK2 &= ~(0x00000001UL<<(mbId - 32U));
            }
        }
                
        /* clear MB interrupt */
        CANxw->CAN_IFLAG2 = 0x00000001UL<<(mbId - 32U);                
    }
}

/**
 * @brief      CAN Handler for MB64 - MB95 interrupts for CAN 6-7
 *
 * @param[in]  id: select the CAN ID
 *
 * @return    none
 *
 */
static void CAN67_Mb64To95Handler(CAN_Id_t id)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    uint32_t totalMbNum = (uint32_t)CANx->CAN_MCR.MAXMB + 1U;
    uint32_t maxMb; 
    uint32_t status;
    uint8_t mbId;
    
    status = CANxw->CAN_IFLAG3;
    status &= CANxw->CAN_IMASK3;
    
    maxMb = (totalMbNum > 96U) ? 96U : totalMbNum;
    for(mbId = 64U; mbId < maxMb; mbId++)
    {
        if((status & (0x00000001UL<<(mbId - 64U))) != 0U)
        {
            if(canIsrCbFunc[id].mbCbf[CAN67_MB_INT_64TO95] != NULL)
            {
                canIsrCbFunc[id].mbCbf[CAN67_MB_INT_64TO95](mbId);
            }
            else
            {
                CANxw->CAN_IMASK3 &= ~(0x00000001UL<<(mbId - 64U));
            }
        }
                
        /* clear MB interrupt */
        CANxw->CAN_IFLAG3 = 0x00000001UL<<(mbId - 64U);
    }
}

/**
 * @brief      CAN Handler for MB96 - MB127 interrupts of CAN6-7
 *
 * @param[in]  id: select the CAN ID
 *
 * @return    none
 *
 */
static void CAN67_Mb96To127Handler(CAN_Id_t id)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    uint32_t totalMbNum = (uint32_t)CANx->CAN_MCR.MAXMB + 1U;
    uint32_t maxMb;
    uint32_t status;
    uint32_t mbId;
    
    status = CANxw->CAN_IFLAG4;
    status &= CANxw->CAN_IMASK4;
    
    maxMb = (totalMbNum >= 128U) ? 128U : totalMbNum;
    for(mbId = 96U; mbId < maxMb; mbId++)
    {
        if((status & (0x00000001UL<<(mbId - 96U))) != 0U)
        {
            if(canIsrCbFunc[id].mbCbf[CAN67_MB_INT_96TO127] != NULL)
            {
                canIsrCbFunc[id].mbCbf[CAN67_MB_INT_96TO127](mbId);
            }
            else
            {
                CANxw->CAN_IMASK4 &= ~(0x00000001UL<<(mbId - 96U));
            }
        }
                
        /* clear MB interrupt */
        CANxw->CAN_IFLAG4 = 0x00000001UL<<(mbId - 96U);
    }
}
#endif
/** @} end of group CAN_Private_Functions */

/** @defgroup CAN_Public_Functions
 *  @{
 */

/**
 * @brief      Get ESR1 buffer in interrupt call back functions. The ESR1 
 *        will be stored into ESR1 buffer in CAN_ErrHandler or CAN_ErrFdHandler.
 *       If the call back functions which are installed through 
 *        CAN_InstallCallBackFunc()  needs to get the ESR1 , please use this 
 *         function instead of CAN_GetIntStatus or CAN_GetStatus.
 *
 * @param[in]  id: Select the CAN port,should be CAN0_ID ~ CAN7_ID
 *
 * @return     ESR1 Buff Value
 *
 */
uint32_t CAN_GetESR1BufForCbf(CAN_Id_t id)
{
    return canEsr1Buf[id];
}

/**
 * @brief      Get CAN status from ESR1 Buff
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  status: the status to be get
 *
 * @return   status
 *           - SET
 *           - RESET
 *
 */ 
FlagStatus_t CAN_GetStatusFromESR1Buf(CAN_Id_t id, CAN_Status_t status)
{
    FlagStatus_t res;
    
    res = ((canEsr1Buf[id] & (1UL << (uint32_t)status)) != 0U) ? SET : RESET; 
    
    return res;
}

/**
 * @brief      Initializes the CAN peripheral. This function will do soft reset
 *             for CAN module, and initialize CAN with provided parameters. This
 *             function needs to be called first before other config functions.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  config: points to the configuration struct
 *
 * @note       For CAN 0-5, 64 message buffers are available.
 *             For CAN 6-7, 128 message buffers are available.
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_Init(CAN_Id_t id, const CAN_Config_t *config)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    volatile uint32_t count;
    ResultStatus_t retVal = SUCC;
    if(0U == CANx->CAN_MCR.MDIS)
    {
        if(CAN_EnterFreezeMode(id) != SUCC)
        {
            retVal = ERR;
        }
        else if(CAN_Disable(id) != SUCC)
        {
            retVal = ERR;
        }
        else
        {
            /*nothing to do */
        }
    }
    if(SUCC == retVal)
    {
        if(CAN_Enable(id) != SUCC)
        {
            retVal = ERR;
        }        
        else if(CAN_EnterFreezeMode(id) != SUCC)
        {
            retVal = ERR;
        }
        else
        {
            /* soft reset */
            CANx->CAN_MCR.SOFTRST = 1;
            count = 0U;
            while(count < CAN_TIMEOUT_WAIT_CNT_2)
            {
                count++;
                if(0U == CANx->CAN_MCR.SOFTRST )
                {
                    break;
                }
            }
            
            if(count >= CAN_TIMEOUT_WAIT_CNT_2)
            {
                retVal = ERR;
            }
            
        
        }
    }
    
    if(SUCC == retVal)
    {
        #if (1U == CAN_ABORT_EN) 
            CANx->CAN_MCR.AEN = 1;
        #else
            CANx->CAN_MCR.AEN = 0;
        #endif
            
        /* clear ram */
        CAN_ClearRam(id);
        
        /* Disable all MB interrupts */
        CANxw->CAN_IMASK1 = 0U; 
        CANxw->CAN_IMASK2 = 0U; 
        if((CAN_ID_6 == id ) || (CAN_ID_7 == id ))
        {
            CANxw->CAN_IMASK3 = 0U; 
            CANxw->CAN_IMASK4 = 0U;
        }
        /* Clear all MB interrupt flags */
        CANxw->CAN_IFLAG1 = 0xFFFFFFFFU;
        CANxw->CAN_IFLAG2 = 0xFFFFFFFFU;
        if((CAN_ID_6 == id ) || (CAN_ID_7 == id ))
        {
            CANxw->CAN_IFLAG3 = 0xFFFFFFFFU;
            CANxw->CAN_IFLAG4 = 0xFFFFFFFFU;
        }

        /* Clear all error interrupt flags */
        CANxw->CAN_ESR1 = CAN_INT_MSK_FLAG_ALL_1;
        CANxw->CAN_ERRSR = CAN_INT_MSK_FLAG_ALL_ECC;
        CANxw->CAN_WU_MTC = CAN_INT_MSK_FLAG_ALL_PN;
        
        /* set FD */
        CANx->CAN_MCR.FDEN = (uint32_t)(config->fdEn);    
        
        CANx->CAN_MCR.IRMQ = 1;
        
        /* Enable the use of extended bit time definitions */
        CANx->CAN_CBT.BTF = (uint32_t)(config->fdEn);
        
        /* Disable Transmission Delay Compensation by default */
        CANx->CAN_FDCTRL.TDCEN = 0;
        
        /* enables the CAN FD protocol according to ISO specification (ISO 11898-1)*/
        CANx->CAN_CTRL2.ISOCANFDEN = (uint32_t)(config->fdEn);
        
        if(ENABLE == config->fdEn )
        {
            /* set payload */
            CANx->CAN_FDCTRL.MBDSR0 = (uint32_t)(config->payload0);
            CANx->CAN_FDCTRL.MBDSR1 = (uint32_t)(config->payload1);
            if((CAN_ID_6 == id ) || (CAN_ID_7 == id ))
            {
                CANx->CAN_FDCTRL.MBDSR2 = (uint32_t)(config->payload2);
                CANx->CAN_FDCTRL.MBDSR3 = (uint32_t)(config->payload3);
            }
            
            /* set FD timing */
            if(ERR == CAN_SetFdArbBitTiming(id, &(config->bitTiming)))
            {
                retVal = ERR;
            }            
            else if(ERR == CAN_SetFdDataBitTiming(id, &(config->bitTimingFdData)))
            {
                retVal = ERR;
            }
            else
            {
                /*nothing to do*/
            }
        }
        else
        {
            /* set CAN timing */
            if(ERR == CAN_SetStdBitTiming(id, &(config->bitTiming)))
            {
                retVal = ERR;
            }
        }
        
    }
    
    if(SUCC == retVal)
    {
        if((config->mbMaxNum > CAN_GetMaxMbNumLimit(id)) || 
           (config->mbMaxNum > CAN_GET_MB_NUM(id)))
        {
            retVal = ERR;
        }
        else
        {
            CANx->CAN_MCR.MAXMB = config->mbMaxNum - 1U;
            /* Disable the self reception feature if CAN is not in loopback mode. */
            if (config->mode != CAN_MODE_LOOPBACK)
            {
                CANx->CAN_MCR.SRXDIS = 1;
            }
            /* config RX FIFO */
            if(ENABLE == config->rxFifoEn )
            {
                if(DISABLE == config->fdEn )
                {
                    /* Enable RX FIFO */
                    CANx->CAN_MCR.RFEN = 1;

                    /* Set the number of the RX FIFO filters needed */
                    CANx->CAN_CTRL2.RFFN = (uint32_t)(config->rxFifoIdFilterNum);
                
                    CANx->CAN_MCR.DMAE = (uint32_t)(config->transferType);

                    /* RX FIFO global mask, take in consideration all filter fields*/
                    CANxw->CAN_RXFGMASK = 0xFFFFFFFFU;
                }
                else
                {
                    retVal = ERR;
                }
            }
            else
            {
                /* Disable RX FIFO */
                CANx->CAN_MCR.RFEN = 0;
                
                if( CAN_RXFIFO_DMA == config->transferType)
                {
                    retVal = ERR;
                }
            }
        }
    }
    if(SUCC == retVal)
    {
        /* CAN is able to enter into doze mode when received entering wait-mode 
           request */
        CANx->CAN_MCR.DOZE = 1U;
        
        if(SUCC != CAN_SetOperationMode(id, config->mode))
        {
            retVal = ERR;
        }        
        else if (config->mode != CAN_MODE_FREEZE)
        {
            if(CAN_ExitFreezeMode(id) != SUCC)
            {
                retVal = ERR;
            }
            else
            {
                CAN_DisableMemErrorDetection(id);
            }
        }
        else
        {
            CAN_DisableMemErrorDetection(id);
        }
    }
    return retVal;
}

/**
 * @brief      Deinit the CAN peripheral. This function disables all CAN 
               interrupts, and disable the CAN
 *
 * @param[in]  id: select the CAN ID
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_Deinit(CAN_Id_t id)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    ResultStatus_t retVal = SUCC;
    if(SUCC != CAN_IntMask(id, CAN_INT_ALL,MASK, 0, 0,0,0))
    {
        retVal = ERR;
    }
    else if(0U == CANx->CAN_MCR.MDIS)
    {
        if(CAN_EnterFreezeMode(id) != SUCC)
        {
            retVal = ERR;
        }
        else if(CAN_Disable(id) != SUCC)
        {
            retVal = ERR;
        }
        else
        {
            /*nothing to do*/
        }
    }
    else
    {
        /*nothing to do*/
    }
    
    return retVal;
}

/**
 * @brief      Set operation mode.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mode: select the CAN operation mode
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_SetOperationMode(CAN_Id_t id, CAN_Mode_t mode)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    uint32_t freeze = CANx->CAN_MCR.FRZACK;    
    ResultStatus_t retVal = SUCC;
    if (0U == freeze)
    {
        if(CAN_EnterFreezeMode(id) != SUCC)
        {
            retVal = ERR;
        }
    }
    if(SUCC == retVal)
    {
        switch(mode)
        {
            case CAN_MODE_NORMAL:
                CANx->CAN_CTRL1.LOM = 0;
                CANx->CAN_CTRL1.LPB = 0;            
                CANx->CAN_MCR.SUPV = 0;    
                break;
            case CAN_MODE_LISTEN_ONLY:
                CANx->CAN_CTRL1.LOM = 1;
                CANx->CAN_CTRL1.LPB = 0;
                break;
            case CAN_MODE_LOOPBACK:
                CANx->CAN_CTRL1.LOM = 0;
                CANx->CAN_CTRL1.LPB = 1;
                CANx->CAN_MCR.SRXDIS = 0;
                CANx->CAN_FDCTRL.TDCEN = 0;
                break;
            case CAN_MODE_FREEZE:
                break;
                
            case CAN_MODE_DISABLE:
                CANx->CAN_MCR.MDIS = 1;
                break;
            default:
                /*nothing to do*/
                break;
        }
    }
    
    if(SUCC == retVal)
    {
        if(CAN_MODE_FREEZE != mode)
        {
            if (0U == freeze)
            {
                if(CAN_ExitFreezeMode(id) != SUCC)
                {
                    retVal = ERR;
                }
            }
        }
    }
    
    return retVal;
}

/**
 * @brief      Disable/Enable self reception.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  ctrl: ENABLE/DISABLE
 *
 * @return      status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_SetSelfRec(CAN_Id_t id, ControlState_t ctrl)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    uint32_t freeze = CANx->CAN_MCR.FRZACK;    
    ResultStatus_t retVal = SUCC;
    if (0U == freeze)
    {
    	if(CAN_EnterFreezeMode(id) != SUCC)
        {
            retVal = ERR;
        }
    }
    if(SUCC == retVal)
    {
        CANx->CAN_MCR.SRXDIS = (ENABLE == ctrl )? 0U : 1U;

        if (0U == freeze)
        {
            if(CAN_ExitFreezeMode(id) != SUCC)
            {
                retVal = ERR;
            }
        }
    }
    return retVal;    
}

/**
 * @brief      Select TX Priority mode.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mode: select the CAN TX priority mode
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 */
ResultStatus_t CAN_SelectTxPriorityMode(CAN_Id_t id, CAN_TxPriMode_t mode)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    uint32_t freeze = CANx->CAN_MCR.FRZACK;    
    ResultStatus_t retVal = SUCC;
    if (0U == freeze)
    {
    	if(CAN_EnterFreezeMode(id) != SUCC)
        {
            retVal = ERR;
        }
    }
    if(SUCC == retVal)
    {
        if(CAN_TX_PRI_LOW_NUM_MB_FIRST == mode)
        {
            CANx->CAN_CTRL1.LBUF = 1;
        }
        else if(CAN_TX_PRI_HIGH_PRI_FIRST == mode)
        {
            CANx->CAN_CTRL1.LBUF = 0;
            CANx->CAN_MCR.LPRIOEN = 0;
        }
        else if(CAN_TX_PRI_LOCAL_PRI_EN == mode)
        {
            CANx->CAN_CTRL1.LBUF = 0;
            CANx->CAN_MCR.LPRIOEN = 1;
        }    
        else
        { 
            /*nothing to do*/
        }

        if (0U == freeze)
        {
            if(CAN_ExitFreezeMode(id) != SUCC)
            {
                retVal = ERR;
            }
        }
    }
    return retVal;
}
/**
 * @brief      Enable CAN.
 *
 * @param[in]  id: select the CAN ID
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_Enable(CAN_Id_t id)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    volatile uint32_t count = 0U;
    ResultStatus_t retVal = SUCC;
    if(CANx->CAN_MCR.LPMACK != 0U)
    {
        CANx->CAN_MCR.MDIS = 0U;
        
        while(count < CAN_TIMEOUT_WAIT_CNT_2)
        {
            count++;
            if(0U == CANx->CAN_MCR.LPMACK)
            {   
                break;
            }
        }
        
        if(count >= CAN_TIMEOUT_WAIT_CNT_2)
        {
            retVal = ERR;
        }
    }
    
    return retVal;
}

/**
 * @brief      Disable CAN.
 *
 * @param[in]  id: select the CAN ID
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_Disable(CAN_Id_t id)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    volatile uint32_t count = 0U;
    ResultStatus_t retVal = SUCC;
    if(0U == CANx->CAN_MCR.MDIS)
    {
        /* Clock disable (module) */
        CANx->CAN_MCR.MDIS = 1;
        
        while(count < CAN_TIMEOUT_WAIT_CNT_2)
        {
            count++;
            if(1U == CANx->CAN_MCR.LPMACK)
            {
                break;
            }
        }
        if(count >= CAN_TIMEOUT_WAIT_CNT_2)
        {
            retVal = ERR;
        }
        
    }
    
    return retVal;
}


/**
 * @brief      Sets the CAN bit timing for standard frames or the arbitration 
 *             phase of FD frames.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  timeSeg: A pointer to the CAN bit timing settings
 *
 * @return      status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_SetStdBitTiming(CAN_Id_t id, const CAN_BitTiming_t *timeSeg)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    
    uint32_t freeze =  CANx->CAN_MCR.FRZACK;
    ResultStatus_t retVal = SUCC;
    if (0U == freeze)
    {
        if(CAN_EnterFreezeMode(id) != SUCC)
        {
            retVal = ERR;
        }
    }
    if(SUCC == retVal)
    {
        /* Set time segments*/
        if((0U == timeSeg->propSeg)||(0U == timeSeg->phaseSeg1) || 
            (timeSeg->phaseSeg2 < 1U) || (0U == timeSeg->preDivider)||
              (0U == timeSeg->rJumpwidth))
        {
            retVal = ERR;
        }
        else
        {
            CANx->CAN_CTRL1.PROPSEG = timeSeg->propSeg - 1U;
            CANx->CAN_CTRL1.PSEG2 = timeSeg->phaseSeg2 - 1U;
            CANx->CAN_CTRL1.PSEG1 = timeSeg->phaseSeg1 - 1U;
            CANx->CAN_CTRL1.PRESDIV = timeSeg->preDivider - 1U;
            CANx->CAN_CTRL1.RJW = timeSeg->rJumpwidth - 1U;

            if (0U == freeze)
            {
                if(CAN_ExitFreezeMode(id) != SUCC)
                {
                    retVal = ERR;
                }
            }
        }
        
    }
    return retVal;
}

/**
 * @brief      Sets the CAN bit timing for the arbitration phase of FD frames of
 *             CAN.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  timeSeg: A pointer to the CAN bit timing settings
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_SetFdArbBitTiming(CAN_Id_t id, const CAN_BitTiming_t *timeSeg)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    uint32_t freeze = CANx->CAN_MCR.FRZACK;    
    ResultStatus_t retVal = SUCC;
    if (0U == freeze)
    {
        if(CAN_EnterFreezeMode(id) != SUCC)
        {
            retVal = ERR;
        }
    }
    if(SUCC == retVal)
    {
        /* Set time segments*/
        if((0U == timeSeg->propSeg)||(0U == timeSeg->phaseSeg1) || 
            (timeSeg->phaseSeg2 < 1U) || (0U == timeSeg->preDivider)||
              (0U == timeSeg->rJumpwidth))
        {
            retVal = ERR;
        }
        else
        {
            CANx->CAN_CBT.EPROPSEG = timeSeg->propSeg - 1U;
            CANx->CAN_CBT.EPSEG2 = timeSeg->phaseSeg2 - 1U;
            CANx->CAN_CBT.EPSEG1 = timeSeg->phaseSeg1 - 1U;
            CANx->CAN_CBT.EPRESDIV = timeSeg->preDivider - 1U;
            CANx->CAN_CBT.ERJW = timeSeg->rJumpwidth - 1U;

            if (0U == freeze)
            {
                if(CAN_ExitFreezeMode(id) != SUCC)
                {
                    retVal = ERR;
                }
            }
        }
        
    }
    return retVal;
}

/**
 * @brief      Sets the CAN bit timing for the data phase of FD frames. 
 *             Those time segment values are passed in by the user and are based
 *             on the required baudrate.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  timeSeg: A pointer to the CAN bit timing settings
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_SetFdDataBitTiming(CAN_Id_t id, 
                                      const CAN_BitTiming_t *timeSeg)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    uint32_t freeze = CANx->CAN_MCR.FRZACK;   
    ResultStatus_t retVal = SUCC;
    if (0U == freeze)
    {
        if(CAN_EnterFreezeMode(id) != SUCC)
        {
            retVal = ERR;
        }
    }
    if(SUCC == retVal)
    {
        /* Set time segments*/
        if((0U == timeSeg->propSeg)||(0U == timeSeg->phaseSeg1) || 
            (timeSeg->phaseSeg2 < 1U) || (0U == timeSeg->preDivider)||
              (0U == timeSeg->rJumpwidth))
        {
            retVal = ERR;
        }
        else
        {
            CANx->CAN_FDCBT.FPROPSEG = timeSeg->propSeg;
            CANx->CAN_FDCBT.FPSEG2 = timeSeg->phaseSeg2 - 1U;
            CANx->CAN_FDCBT.FPSEG1 = timeSeg->phaseSeg1 - 1U;
            CANx->CAN_FDCBT.FPRESDIV = timeSeg->preDivider - 1U;
            CANx->CAN_FDCBT.FRJW = timeSeg->rJumpwidth - 1U;
        }
                
        if (0U == freeze)
        {
            if(CAN_ExitFreezeMode(id) != SUCC)
            {
                retVal = ERR;
            }
        }
    }
    return retVal;
}

/**
 * @brief      Sets the Rx masking type.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  type: select RX mask type
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_SetRxMaskType(CAN_Id_t id, CAN_RxMask_t type)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    uint32_t freeze = CANx->CAN_MCR.FRZACK;   
    ResultStatus_t retVal = SUCC;
    if (0U == freeze)
    {
        if(CAN_EnterFreezeMode(id) != SUCC)
        {
            retVal = ERR;
        }
    }
    if(SUCC == retVal)
    {
        CANx->CAN_MCR.IRMQ = (uint32_t)type;
        
        if (0U == freeze)
        {
            if(CAN_ExitFreezeMode(id) != SUCC)
            {
                retVal = ERR;
            }
        }
    }
    return retVal;
}

/**
 * @brief      Sets the CAN Rx MB global mask (standard or extended) 
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  idType: Standard ID or extended ID
 * @param[in]  mask:Mask Value. 11-bit standard mask or 29-bit extended mask
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_SetRxMbGlobalMask(CAN_Id_t id, CAN_MsgId_t idType, 
                                     uint32_t mask)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    uint32_t freeze = CANx->CAN_MCR.FRZACK;  
    ResultStatus_t retVal = SUCC;
    if (0U == freeze)
    {
    	if(CAN_EnterFreezeMode(id) != SUCC)
        {
             retVal = ERR;
        }
    }
    if(SUCC == retVal)
    {
        if (CAN_MSG_ID_STD == idType)
        {
            CANxw->CAN_RXMGMSK = CAN_CAL_RX_MB_STD_MASK(mask);
        }
        else
        {
            CANxw->CAN_RXMGMSK = CAN_CAL_RX_MB_EXT_MASK(mask);
        }
        
        if (0U == freeze)
        {
            if(CAN_ExitFreezeMode(id) != SUCC)
            {
                retVal = ERR;
            }
        }
    }
    return retVal;
}

/**
 * @brief      Set Rx Message Buffer 14 mask (standard or extended) 
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  idType: Standard ID or extended ID
 * @param[in]  mask:Mask Value. 11-bit standard mask or 29-bit extended mask
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_SetRxMb14Mask(CAN_Id_t id, CAN_MsgId_t idType, uint32_t mask)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    uint32_t freeze = CANx->CAN_MCR.FRZACK;  
    ResultStatus_t retVal = SUCC;
    if (0U == freeze)
    {
        if(CAN_EnterFreezeMode(id) != SUCC)
        {
            retVal = ERR;
        }
    }
    if(SUCC == retVal)
    {
        if (CAN_MSG_ID_STD == idType)
        {
            CANxw->CAN_RX14MASK = CAN_CAL_RX_MB_STD_MASK(mask);
        }
        else
        {
            CANxw->CAN_RX14MASK = CAN_CAL_RX_MB_EXT_MASK(mask);
        }
        
        if (0U == freeze)
        {
            if(CAN_ExitFreezeMode(id) != SUCC)
            {
                retVal = ERR;
            }
        }
    }
    return retVal;
}

/**
 * @brief      Set Rx Message Buffer 15 mask (standard or extended) 
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  idType: Standard ID or extended ID
 * @param[in]  mask:Mask Value. 11-bit standard mask or 29-bit extended mask
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_SetRxMb15Mask(CAN_Id_t id, CAN_MsgId_t idType, uint32_t mask)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    uint32_t freeze = CANx->CAN_MCR.FRZACK;  
    ResultStatus_t retVal = SUCC;
    if (0U == freeze)
    {
        if(CAN_EnterFreezeMode(id) != SUCC)
        {
            retVal = ERR;
        }
    }
    if(SUCC == retVal)
    {
        if (CAN_MSG_ID_STD == idType)
        {
            CANxw->CAN_RX15MASK = CAN_CAL_RX_MB_STD_MASK(mask);
        }
        else
        {
            CANxw->CAN_RX15MASK = CAN_CAL_RX_MB_EXT_MASK(mask);
        }
        
        if (0U == freeze)
        {
            if(CAN_ExitFreezeMode(id) != SUCC)
            {
                retVal = ERR;
            }
        }
    }
    return retVal;
}

/**
 * @brief      Sets Rx MB individual mask 
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  idType: Standard ID or extended ID
 * @param[in]  mbIdx: MB index. The MB should not be occupied by RX FIFO if RX
 *                    FIFO is enabled, otherwise, it will return ERR.
 *                    For CAN0-5, the maximum mbIdx is 63 if payload size is
 *                    8-byte. 
 *                    For CAN6-7, the maximum mbIdx is 127 if payload size is
 *                    8-byte.
 *
 * @param[in]  mask: Mask Value. 11-bit standard mask or 29-bit extended mask
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_SetRxMbIndividualMask(CAN_Id_t id, CAN_MsgId_t idType, 
                                         uint32_t mbIdx, uint32_t mask)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    ResultStatus_t retVal = SUCC;
    uint32_t freeze = CANx->CAN_MCR.FRZACK;

    if (CAN_CheckMbId(id,mbIdx) != SUCC)
    {
        retVal = ERR;
    }    
    else if (0U == freeze)
    {
        if(CAN_EnterFreezeMode(id) != SUCC)
        {
            retVal = ERR;
        }
    }
    else
    {
        /*nothing to do*/
    }
    if(SUCC == retVal)
    {
        if (CAN_MSG_ID_STD ==idType)
        {
            CANxw->CAN_RXIMR[mbIdx] = CAN_CAL_RX_MB_STD_MASK(mask);
        }
        else
        {
            CANxw->CAN_RXIMR[mbIdx] = CAN_CAL_RX_MB_EXT_MASK(mask);
        }
        
        if (0U == freeze)
        {
            if(CAN_ExitFreezeMode(id) != SUCC)
            {
                retVal = ERR;
            }
        }
    }
    return retVal;
}

/**
 * @brief      Sets Rx FIFO global mask. It masks the Rx FIFO ID Filter Table
 *             elements that do not have a corresponding individual mask. 
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mask:Mask Value. Its format depends on the RX FIFO id filter 
               format. It should be set as follows:
                        
    Format A ID mask: 
    bit31 | bit30 |      bit29 ... 1             | bit0
    RTR   | IDE(0)| IDmask(std:29-19, ext:29-1)  | reserved

    Format B ID mask: 
    bit31 | bit30 |       bit29 ... 16        | bit 15 | bit 14 | bit13 ... 0
    RTR   | IDE   | ID0(std:29-19, ext:29-16) | RTR    | IDE    | ID1
                                                          (std:13-3, ext:13-0)

    Format C ID mask: 
    bit31...bit 24 | bit23...bit16 |  bit15 ...bit8 | bit7 ... bit0
    IDmask0        | IDmask1       |    IDmask2     |    IDmask3
                        
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_SetRxFifoGlobalMask(CAN_Id_t id, uint32_t mask)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    ResultStatus_t retVal = SUCC;
    uint32_t freeze =  CANx->CAN_MCR.FRZACK;

    if (0U == freeze)
    {
        if(CAN_EnterFreezeMode(id) != SUCC)
        {
            retVal = ERR;
        }
    }
    if(SUCC == retVal)
    {
        if (CANx->CAN_MCR.RFEN != 0U)
        {
            CANxw->CAN_RXFGMASK = mask;
        }
        
        if (0U == freeze)
        {
            if(CAN_ExitFreezeMode(id) != SUCC)
            {
                retVal = ERR;
            }
        }
    }
    return retVal;
}

/**
 * @brief      Sets Rx FIFO individual mask for the specific ID filter table
 *             element
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  elementIdx: ID filter table element index. It indicates which
 *                         filter table element the mask is corresponding to.
 *                         It should not exceeds the MB number that is occupied
 *                         by Rx FIFO.
 * @param[in]  mask:Mask Value. Its format depends on the RX FIFO id filter 
               format. It should be set as follows:
                        
    Format A ID mask: 
    bit31 | bit30 |      bit29 ... 1             | bit0
    RTR   | IDE(0)| IDmask(std:29-19, ext:29-1)  | reserved

   Format B ID mask: 
   bit31 | bit30 |       bit29 ... 16           | bit 15 | bit 14 | bit13 ... 0
   RTR   | IDE   | IDmask0(std:29-19, ext:29-16)| RTR    | IDE    | IDmask1
                                                            (std:13-3, ext:13-0)
   In the extended frame format B, IDmask0/IDmask1 corresponds to the 14 most 
   significant bits of the received ID

   Format C ID mask: 
   bit31...bit 24 | bit23...bit16 |  bit15 ...bit8 | bit7 ... bit0
   IDmask0        | IDmask1       |    IDmask2     |    IDmask3
   For format C IDmask corresponds to the 8 most significant bits of 
   the received ID
                        
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_SetRxFifoIndividualMask(CAN_Id_t id, uint32_t elementIdx, 
                                           uint32_t mask)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    ResultStatus_t retVal = SUCC;
    uint32_t freeze =  CANx->CAN_MCR.FRZACK;

    if (0U == freeze)
    {
        if(CAN_EnterFreezeMode(id) != SUCC)
        {
            retVal = ERR;
        }
    }
    if(SUCC == retVal)
    {
        if (CANx->CAN_MCR.RFEN != 0U )
        {
            if(elementIdx <= CAN_GetNoOfRxFIFOIndividualMask(id))
            {
                CANxw->CAN_RXIMR[elementIdx] = mask;
            }
        }
        
        if (0U == freeze)
        {
            if(CAN_ExitFreezeMode(id) != SUCC)
            {
                retVal = ERR;
            }
        }
    }
    return retVal;
}

/**
 * @brief      Configure transmit message buffer.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: MB index. The MB should not be occupied by RX FIFO if RX
 *                    FIFO is enabled, otherwise, it will return ERR.
 *                    For CAN0-5, the maximum mbIdx is 63 if payload size is
 *                    8-byte. 
 *                    For CAN6-7, the maximum mbIdx is 127 if payload size is
 *                    8-byte.
 * @param[in]  txInfo: TX MB info
 * @param[in]  msgId: message ID. 
 * @param[in]  localPrio: the local priority field, if the TX priority mode is
 *                        CAN_TX_PRI_LOCAL_PRI_EN, this parameter indicates the
 *                        local priority.
 *
 * @return     status
 *
 *
 */
ResultStatus_t CAN_ConfigTxMb(CAN_Id_t id, uint8_t mbIdx,
                              const CAN_MessageInfo_t *txInfo, 
                              uint32_t msgId, uint8_t localPrio)
{
    return CAN_SetTxMb(id, mbIdx, txInfo, msgId, NULL, CAN_TX_INACTIVE, 
                       localPrio);
}

/**
 * @brief      Configures a transmit message buffer for remote frame response
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: MB index. The MB should not be occupied by RX FIFO if RX
 *                    FIFO is enabled, otherwise, it will return ERR.
 *                    For CAN0-5, the maximum mbIdx is 63 if payload size is
 *                    8-byte. 
 *                    For CAN6-7, the maximum mbIdx is 127 if payload size is
 *                    8-byte.
 * @param[in]  txInfo: TX MB info
 * @param[in]  msgId: message ID
 * @param[in]  msgData:  data of the message
 * @param[in]  localPrio: the local priority field, if the TX priority mode is
 *                        CAN_TX_PRI_LOCAL_PRI_EN, this parameter indicates the
 *                        local priority
 *
 * @return     status
 *
 *
 */
ResultStatus_t CAN_ConfigRemoteResponseMb(CAN_Id_t id, uint8_t mbIdx,
                                          const CAN_MessageInfo_t *txInfo, 
                                          uint32_t msgId, const uint8_t *msgData,
                                          uint8_t localPrio)
{
    ResultStatus_t retVal = SUCC;
    if(SUCC != CAN_ClearMbIntStatus(id,mbIdx))
    {
        retVal = ERR;
    }
    if(SUCC == retVal)
    {
        retVal = CAN_SetTxMb(id, mbIdx, txInfo, msgId, msgData, CAN_RX_RANSWER,
                       localPrio);
    }
    return retVal;
}

/**
 * @brief      Configure a Rx message buffer.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: MB index. The MB should not be occupied by RX FIFO if RX
 *                    FIFO is enabled, otherwise, it will return ERR.
 *                    For CAN0-5, the maximum mbIdx is 63 if payload size is
 *                    8-byte. 
 *                    For CAN6-7, the maximum mbIdx is 127 if payload size is
 *                    8-byte.
 * @param[in]  idType: Type of message ID (standard or extended)
 * @param[in]  msgId: message ID
 *
 * @return     status
 *
 *
 */
ResultStatus_t CAN_ConfigRxMb(CAN_Id_t id, uint8_t mbIdx, 
                              CAN_MsgId_t idType, uint32_t msgId)
{
    ResultStatus_t result;

    /* Clear the message buffer flag if previous remained triggered*/
    if(SUCC != CAN_ClearMbIntStatus(id,mbIdx))
    {
        result = ERR;
    }
    else
    {
        /* Initialize rx mb*/
        result = CAN_SetRxMb(id, mbIdx, idType, msgId, CAN_NOT_USED);

        if(SUCC == result)
        {
            /* Initialize receive MB*/
            result = CAN_SetRxMb(id, mbIdx, idType, msgId, CAN_RX_INACTIVE);
        }
        
        if (SUCC == result)
        {
            /* Clear the message buffer flag if previous remained triggered*/
            result = CAN_ClearMbIntStatus(id,mbIdx);
        }

        if (SUCC == result)
        {
            /* Set up MB for receiving data*/
            result = CAN_SetRxMb(id, mbIdx, idType, msgId, CAN_RX_EMPTY);
        }
    }
    return result;
}

/**
 * @brief      sends a CAN frame. This function sends a CAN frame using 
 *             a configured message buffer. Before calling this function,
 *             user needs to make sure that the MB to be configured is inactive,
 *             otherwise, it will return BUSY.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: MB index.The MB should not be occupied by RX FIFO if RX
 *                    FIFO is enabled, otherwise, it will return ERR.
 *                    For CAN0-5, the maximum mbIdx is 63 if payload size is
 *                    8-byte. 
 *                    For CAN6-7, the maximum mbIdx is 127 if payload size is
 *                    8-byte.
 * @param[in]  txInfo: TX MB info
 * @param[in]  msgId: message ID
 * @param[in]  msgData:  data of the message
 *
 * @return     status
 *            - SUCC
 *            - ERR: mbIdx is invalid
 *            - BUSY: the MB to be configured is not in inactive status
 *
 */
ResultStatus_t CAN_Send(CAN_Id_t id, uint8_t mbIdx, 
                        const CAN_MessageInfo_t *txInfo,
                        uint32_t msgId, const uint8_t *msgData)
{
    CAN_FdMbRegion_t region;
    CAN_Mb_t *mbAddr;
    uint32_t code;
    ResultStatus_t retVal = SUCC;
    if(ERR == CAN_GetMbAddr(id, mbIdx, &region, &mbAddr))
    {
        retVal = ERR;
    }    
    /* check if it is a valid MB */
    else if(ERR == CAN_CheckMbId(id, mbIdx))
    {
        retVal = ERR;
    }
    else
    {
        code = mbAddr->config.BF.CODE;
        if((code != (uint32_t)CAN_MB_RX_INACTIVE) && 
           (code != (uint32_t)CAN_MB_TX_INACTIVE) && 
           (code != (uint32_t)CAN_MB_TX_ABORT))  
        {
            retVal = BUSY;
        }
        else
        {
            if(SUCC != CAN_ClearMbIntStatus(id, mbIdx))
            {
                retVal = ERR;
            }
            else
            {
                retVal = CAN_SetTxMb(id, mbIdx, txInfo, msgId, msgData, CAN_TX_DATA_REMOTE, 0);
            }
        }
        
    }
    return retVal;

}

/**
 * @brief      sends a CAN frame when the TX priority mode is CAN_TX_PRI_LOCAL_PRI_EN
 *             This function sends a CAN frame using a configured message buffer.
 *             It also configures the local priority. Before calling this 
 *             function, user needs to make sure that the MB to be configured 
 *             is inactive, otherwise, it will return BUSY.
 *              
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: MB index. The MB should not be occupied by RX FIFO if RX
 *                    FIFO is enabled, otherwise, it will return ERR.
 *                    For CAN0-5, the maximum mbIdx is 63 if payload size is
 *                    8-byte. 
 *                    For CAN6-7, the maximum mbIdx is 127 if payload size is
 *                    8-byte.
 * @param[in]  txInfo: TX MB info
 * @param[in]  msgId: message ID
 * @param[in]  msgData: data of the message
 * @param[in]  localPrio: the local priority field for the MB
 *
 * @return     status
 *            - SUCC
 *            - ERR: mbIdx is invalid
 *            - BUSY: the MB to be configured is not in inactive status
 *
 */
ResultStatus_t CAN_SendwithLocalPrio(CAN_Id_t id, uint8_t mbIdx, 
                                     const CAN_MessageInfo_t *txInfo,
                                     uint32_t msgId, const uint8_t *msgData, 
                                     uint8_t localPrio)
{
    CAN_FdMbRegion_t region;
    CAN_Mb_t *mbAddr;
    uint32_t code;
    ResultStatus_t retVal = SUCC;
    if(ERR == CAN_GetMbAddr(id, mbIdx, &region, &mbAddr))
    {
        retVal = ERR;
    }    
    /* check if it is a valid MB */
    else if(ERR == CAN_CheckMbId(id, mbIdx))
    {
        retVal = ERR;
    }
    else
    {
        code = mbAddr->config.BF.CODE;
        if((code != (uint32_t)CAN_MB_RX_INACTIVE) && 
          (code != (uint32_t)CAN_MB_TX_INACTIVE) && 
          (code != (uint32_t)CAN_MB_TX_ABORT))  
        {
            retVal = BUSY;
        }
        else if(SUCC != CAN_ClearMbIntStatus(id, mbIdx))
        {
            retVal = ERR;
        }
        else
        {
            retVal = CAN_SetTxMb(id, mbIdx, txInfo, msgId, msgData, CAN_TX_DATA_REMOTE, 
                       localPrio);
        }
    }
    return retVal;

}

/**
 * @brief      receive a CAN frame into a configured MB.  
 *             Before calling this function, user needs to make sure that the MB
 *             to be configured is inactive, otherwise, it will return BUSY.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: MB index. The MB should not be occupied by RX FIFO if RX
 *                    FIFO is enabled, otherwise, it will return ERR.
 *                    For CAN0-5, the maximum mbIdx is 63 if payload size is
 *                    8-byte. 
 *                    For CAN6-7, the maximum mbIdx is 127 if payload size is
 *                    8-byte.
 * @param[in]  idType: type of message ID (standard or extended)
 * @param[in]  msgId: message ID
 *
 * @return     status
 *            - SUCC
 *            - ERR: mbIdx is invalid
 *            - BUSY: the MB to be configured is not in inactive status
 *
 */
ResultStatus_t CAN_MbReceive(CAN_Id_t id, uint8_t mbIdx, CAN_MsgId_t idType,
                             uint32_t msgId)
{
    CAN_FdMbRegion_t region;
    CAN_Mb_t *mbAddr;
    uint32_t code;
    ResultStatus_t retVal = SUCC;
    if(ERR == CAN_GetMbAddr(id, mbIdx, &region, &mbAddr))
    {
        retVal = ERR;
    }    
    /* check if it is a valid MB */
    else if(ERR == CAN_CheckMbId(id, mbIdx))
    {
        retVal = ERR;
    }
    else
    {
        code = mbAddr->config.BF.CODE;
        if((code != (uint32_t)CAN_MB_RX_INACTIVE) && 
           (code != (uint32_t)CAN_MB_TX_INACTIVE) && 
           (code != (uint32_t)CAN_MB_TX_ABORT))  
        {
            retVal = BUSY;
        }   
        else
        {
            retVal = CAN_ConfigRxMb(id, mbIdx, idType, msgId);
        }
    }
    
    return retVal;
}

/**
 * @brief      Configure RX FIFO ID filter table elements
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  format: the ID filter format
 * @param[in]  idFilterTable: points to the ID filter table
 *
 * @note 
 *       The number of elements in the ID filter table is defined by the
 *       following formula:
 *       - for format A: the number of Rx FIFO ID filters
 *       - for format B: twice the number of Rx FIFO ID filters
 *       - for format C: four times the number of Rx FIFO ID filters
 *       The user must provide the exact number of elements in order to avoid
 *       any misconfiguration.
 *
 *       Each element in the ID filter table specifies an ID to be used as
 *       acceptance criteria for the FIFO as follows:
 *       - for format A: In the standard frame format, bits 10 to 0 of the ID
 *         are used for frame identification. In the extended frame format, bits
 *         28 to 0 are used.
 *       - for format B: In the standard frame format, bits 10 to 0 of the ID
 *         are used for frame identification. In the extended frame format, only
 *         the 14 most significant bits (28 to 15) of the ID are compared to the
 *         14 most significant bits (28 to 15) of the received ID.
 *       - for format C: In both standard and extended frame formats, only the 8
 *         most significant bits(10 to 3 for standard, 28 to 21 for extended) of
 *         the ID are compared to the 8 most significant bits (10 to 3 for
 *         standard, 28 to 21 for extended) of the received ID.
 *
 * @return  status
 *          - SUCC -- successful
 *          - ERR -- some error
 *
 */
ResultStatus_t CAN_ConfigRxFifo(CAN_Id_t id, CAN_RxFifoIdFormat_t format,
                              const CAN_IdFilter_t *idFilterTable)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    uint32_t freeze =  CANx->CAN_MCR.FRZACK;
    uint32_t i, j;
    uint8_t filterNum;
    uint32_t val1 = 0;
    uint32_t val2;
    uint32_t val;
    ResultStatus_t retVal = SUCC;
    
    volatile uint32_t *filterTable = &(CANxw->CAN_MB[6].CS);
    
    filterNum = (CANx->CAN_CTRL2.RFFN +1U) << 3U;

    if (0U == freeze)
    {
        if(CAN_EnterFreezeMode(id) != SUCC)
        {
            retVal = ERR;
        }
    }
    if(SUCC == retVal)
    {
    
        /* clear RX FIFO */
        CANxw->CAN_IFLAG1 = 1U;

        switch(format)
        {
            case (CAN_RX_FIFO_ID_FORMAT_A):
                /* One full ID (standard and extended) per ID Filter Table element.*/
                CANx->CAN_MCR.IDAM = (uint32_t)format;

                for (i = 0U; i < filterNum; i++)
                {
                    val = 0U;

                    if (SET == idFilterTable[i].isRemoteFrame)
                    {
                        val = 1UL << 31;
                    }
                    if(SET == idFilterTable[i].isExtendedFrame)
                    {
                        val |= 1UL << 30;
                        filterTable[i] = val | ((idFilterTable[i].id << 1U) & 
                                                0x3FFFFFFFU);
                    }
                    else
                    {
                        filterTable[i] = val | ((idFilterTable[i].id << 19U) & 
                                                0x3FFFFFFFU);
                    }
                }
                break;
            case (CAN_RX_FIFO_ID_FORMAT_B):
                /* Two full standard IDs or two partial 14-bit */
                 /*(standard and extended) IDs*/
                /* per ID Filter Table element.*/
               CANx->CAN_MCR.IDAM = (uint32_t)format;
                j = 0U;
                for (i = 0U; i < filterNum; i++)
                {
                    val1 = 0U;
                    val2 = 0U;

                    if (SET == idFilterTable[j].isRemoteFrame)
                    {
                        val1 = 1UL << 31U;
                    }
                    if (SET == idFilterTable[j + 1U].isRemoteFrame)
                    {
                        val2 = 1UL << 15U;
                    }
                    if (SET == idFilterTable[j].isExtendedFrame)
                    {
                        val1 |= 1UL << 30U;

                        filterTable[i] = val1 | (((idFilterTable[j].id & 0x1FFF8000U)
                                                  >> 15) <<16);
                    }
                    else
                    {
                        filterTable[i] = val1 | ((idFilterTable[j].id & 0x7FFU) 
                                                 << 19);
                    }
                    if (SET == idFilterTable[j + 1U].isExtendedFrame)
                    {
                        val2 |= 1UL << 14U;

                        filterTable[i] |= val2 | ((idFilterTable[j + 1U].id & 
                                                   0x1FFF8000U) >>15U);
                    }
                    else
                    {
                        filterTable[i] |= val2 + ((idFilterTable[j + 1U].id &
                                                   0x7FFU) << 3U);
                    }
                    j = j + 2U;
                }
                break;
            case (CAN_RX_FIFO_ID_FORMAT_C):
                /* Four partial 8-bit Standard IDs per ID Filter Table element.*/
                CANx->CAN_MCR.IDAM = (uint32_t)format;
                j = 0U;
                for (i = 0U; i < filterNum; i++)
                {
                    if (SET == idFilterTable[j].isExtendedFrame)
                    {
                        filterTable[i] |= (((idFilterTable[j].id & 
                                                    0x1FE00000U) >> 21U) << 24U);
                    }
                    else
                    {
                        filterTable[i] |= (((idFilterTable[j].id &
                                                    0x7F8U) >> 3U) << 24U);
                    }
                    if (SET == idFilterTable[j + 1U].isExtendedFrame)
                    {
                        filterTable[i] |= (((idFilterTable[j + 1U].id &
                                                    0x1FE00000U) >> 21U) << 16U);
                    }
                    else
                    {
                        filterTable[i] |=  (((idFilterTable[j + 1U].id &
                                                    0x7F8U) >> 3U) << 16U);
                    }
                    if (SET == idFilterTable[j + 2U].isExtendedFrame)
                    {
                        filterTable[i] |= (((idFilterTable[j + 2U].id &
                                                    0x1FE00000U) >> 21U) << 8U);
                    }
                    else
                    {
                        filterTable[i] |= (((idFilterTable[j + 2U].id &
                                                    0x7F8U) >> 3U) << 8U);
                    }
                    if (SET == idFilterTable[j + 3U].isExtendedFrame)
                    {
                        filterTable[i] |= ((idFilterTable[j + 3U].id &
                                                    0x1FE00000U) >> 21U);
                    }
                    else
                    {
                        filterTable[i] |= ((idFilterTable[j + 3U].id &
                                                    0x7F8U) >> 3U);
                    }
                    j = j + 4U;
                }
                break;
            case (CAN_RX_FIFO_ID_FORMAT_D):
                /* All frames rejected.*/
                CANx->CAN_MCR.IDAM = (uint32_t)format;
                break;
            default:
                /* Should not get here */
                break;
        }

        if (0U == freeze)
        {
            if(CAN_ExitFreezeMode(id) != SUCC)
            {
                retVal = ERR;
            }
        }
    }
    return retVal;
}

/**
 * @brief      Get a message buffer field values.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: MB index. The MB should not be occupied by RX FIFO if RX
 *                    FIFO is enabled, otherwise, it will return ERR.
 *                    For CAN0-5, the maximum mbIdx is 63 if payload size is
 *                    8-byte. 
 *                    For CAN6-7, the maximum mbIdx is 127 if payload size is
 *                    8-byte.
 * @param[in]  msgBuff: point to the address where the message buffer will be 
 *            stored 
 *
 * @return     status
 *
 *
 */
ResultStatus_t CAN_GetMsgBuff(CAN_Id_t id, uint32_t mbIdx, CAN_MsgBuf_t *msgBuff)
{
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    uint8_t i;
    uint8_t tmpNum;
    uint8_t tmpIndex;
    uint8_t payloadSize;
    CAN_FdMbRegion_t region;
    CAN_Mb_t *mbAddr;
    volatile uint8_t  *mbData;
    ResultStatus_t retVal = SUCC;
    if(ERR == CAN_GetMbAddr(id, (uint8_t)mbIdx, &region, &mbAddr))
    {
        retVal = ERR;
    }    
    else
    {
        mbData = (volatile uint8_t *)(&mbAddr->data[0]);
    
        if(ERR == CAN_CheckMbId(id,mbIdx))
        {
            retVal = ERR;
        }
    }
    
    if(SUCC == retVal)
    {
        /* Lock the mailbox by reading it */
        (void)(mbAddr->config.WORDVAL);
        
        payloadSize = CAN_ComputePayloadSize((uint8_t)(mbAddr->config.BF.DLC));
        if(payloadSize > CAN_GetPayloadSize(id,region))
        {
            payloadSize = CAN_GetPayloadSize(id,region);
        }
        
        msgBuff->dataLen = payloadSize;
        msgBuff->cs = mbAddr->config.WORDVAL;
        if(mbAddr->config.BF.IDE != 0U)
        {
            msgBuff->msgId = mbAddr->id.WORDVAL & CAN_ID_EXT_MASK;
        }
        else
        {
            msgBuff->msgId = mbAddr->id.BF.ID_STANDARD;
        }
        
        tmpNum = payloadSize >> 2U;
        for (i = 0U ; i < tmpNum; i += 1U)
        {
            msgBuff->data[(i<<2U)] = (uint8_t)((mbAddr->data[i] & 0xFF000000U) >> 24U);
            msgBuff->data[(i<<2U) + 1U] = (uint8_t)((mbAddr->data[i] & 0xFF0000U) >> 
                                                 16U);
            msgBuff->data[(i<<2U) + 2U] = (uint8_t)((mbAddr->data[i] & 0xFF00U) >> 8U);
            msgBuff->data[(i<<2U) + 3U] = (uint8_t)(mbAddr->data[i] & 0xFFU);
        }

        for ( i = (tmpNum << 2U); i < payloadSize ; i++)
        {
            tmpIndex = CAN_SWAP_BYTES_IN_WORD_INDEX(i) & 0x3FU;
            /* Max allowed value for index is 63 */
            msgBuff->data[i] = mbData[tmpIndex];
        }
        
        /* Unlock the mailbox by reading the free running timer */
        (void)CANxw->CAN_TIMER;
    }
    
    
    return retVal;
}

/**
 * @brief      Read a frame in RX FIFO.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  msgBuff: point to the address where the message buffer will be 
 *             stored 
 *
 * @return     none
 *
 *
 */
void CAN_ReadRxFifo(CAN_Id_t id, CAN_MsgBuf_t *msgBuff)
{
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    uint8_t i;
    uint8_t tmpNum;
    uint8_t tmpIndex;
    uint8_t payloadSize;
    /*PRQA S 0303 ++*/
    volatile CAN_Mb_t *mbAddr = (CAN_Mb_t *)(uint32_t)&(CANxw->CAN_MB[0].CS);
    /*PRQA S 0303 --*/
    volatile uint8_t  *mbData;
    
    payloadSize = CAN_ComputePayloadSize((uint8_t)mbAddr->config.BF.DLC);
    if(payloadSize > CAN_GetPayloadSize(id,CAN_FD_MB_REGION_0))
    {
        payloadSize = CAN_GetPayloadSize(id,CAN_FD_MB_REGION_0);
    }
    
    msgBuff->dataLen = payloadSize;
    msgBuff->cs = mbAddr->config.WORDVAL;
    if(mbAddr->config.BF.IDE != 0U)
    {
        msgBuff->msgId = mbAddr->id.WORDVAL & CAN_ID_EXT_MASK;
    }
    else
    {
        msgBuff->msgId = mbAddr->id.BF.ID_STANDARD;
    }
    
    tmpNum = (payloadSize>> 2U);
    for (i = 0U ; i < tmpNum; i += 1U)
    {
        msgBuff->data[(i<<2U)] = (uint8_t)((mbAddr->data[i] & 0xFF000000U) >> 24U);
        msgBuff->data[(i<<2U) + 1U] = (uint8_t)((mbAddr->data[i] & 0xFF0000U) >> 
                                             16U);
        msgBuff->data[(i<<2U) + 2U] = (uint8_t)((mbAddr->data[i] & 0xFF00U) >> 8U);
        msgBuff->data[(i<<2U) + 3U] = (uint8_t)(mbAddr->data[i] & 0xFFU);
    }
    
    mbData = (volatile uint8_t *)(&mbAddr->data[0]);
    for (i = (tmpNum << 2U); i < payloadSize; i++)
    {
        tmpIndex = CAN_SWAP_BYTES_IN_WORD_INDEX(i) & 0x3FU;
        /* Max allowed value for index is 63 */
        msgBuff->data[i] = mbData[tmpIndex];
    }
}
/**
 * @brief     make the MB to inactive status and disable the interrupt of this
 *            MB. The MBs occupied by RX FIFO can not be handle by this function.
 *            If MB is RX MB, it will become CAN_MB_RX_INACTIVE after 
 *            this function; if MB is TX MB, it will become CAN_MB_TX_INACTIVE
 *            or CAN_MB_TX_ABORT after this function.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: MB index
 *
 * @return     status
 *
 *
 */
ResultStatus_t CAN_InactiveMb(CAN_Id_t id, uint8_t mbIdx)
{
    CAN_FdMbRegion_t region;
    CAN_Mb_t *mbAddr;
    uint32_t code;
    volatile uint32_t count;
    ResultStatus_t retVal = SUCC;
    
    if(ERR == CAN_GetMbAddr(id, mbIdx, &region, &mbAddr))
    {
        retVal = ERR;
    }    
    /* check if it is a valid MB */
    else if(ERR == CAN_CheckMbId(id, mbIdx))
    {
        retVal = ERR;
    }
    /* disable interrupt */
    else if(ERR == CAN_MbIntMask(id, mbIdx, MASK))
    {
        retVal = ERR;
    }
    /* clear interrupt status */
    else if(SUCC != CAN_ClearMbIntStatus(id, mbIdx))
    {
        retVal = ERR;
    }
    else
    {
        /* ignore the busy status */
        code = (mbAddr->config.BF.CODE) & (~(uint32_t)CAN_CODE_BUSY_MASK);
        
        /* MB is already inactive */
        if(((uint32_t)CAN_MB_RX_INACTIVE == code) || 
           ((uint32_t)CAN_MB_TX_INACTIVE == code) || 
           ((uint32_t)CAN_MB_TX_ABORT == code))
        {
            retVal = SUCC;
        }
        else if(((uint32_t)CAN_MB_RX_FULL == code) || 
                ((uint32_t)CAN_MB_RX_EMPTY == code)|| 
           ((uint32_t)CAN_MB_RX_OVERRUN == code) ||
             ((uint32_t)CAN_MB_RX_RANSWER == code))
        {
            count = 0U;
            /* wait until it is not busy */
            while(count < CAN_TIMEOUT_WAIT_CNT_3)
            {
                count++;
                if(0U == ((mbAddr->config.BF.CODE) & CAN_CODE_BUSY_MASK))
                {
                    break;
                }
            }
            if(count >= CAN_TIMEOUT_WAIT_CNT_3)
            {
                retVal = ERR;
            }
            if(SUCC == retVal)
            {
                mbAddr->config.BF.CODE = (uint32_t)CAN_MB_RX_INACTIVE;
            
                retVal = CAN_ClearMbIntStatus(id, mbIdx);
            }            
        }    
        else if(((uint32_t)CAN_MB_TX_DATA_REMOTE == code) || 
                ((uint32_t)CAN_MB_TX_TANSWER == code))
        {    
    #if (1U == CAN_ABORT_EN)
            mbAddr->config.BF.CODE = (uint32_t)CAN_MB_TX_ABORT;
            
            count = 0U;
            /* wait until abort is completed */
            while(count < CAN_TIMEOUT_WAIT_CNT_3)
            {
                count++;
                if(SET == CAN_GetMbIntStatus(id, mbIdx))
                {
                    break;
                }
            }
            if(count >= CAN_TIMEOUT_WAIT_CNT_3)
            {
                retVal = ERR;
            }
            if(SUCC == retVal)
            {
                if((uint32_t)CAN_MB_TX_ABORT == mbAddr->config.BF.CODE)
                {
                    mbAddr->config.BF.CODE = (uint32_t)CAN_MB_TX_INACTIVE;
                }
            }
            
    #else
            mbAddr->config.BF.CODE = (uint32_t)CAN_MB_TX_INACTIVE;
    #endif
            if(SUCC == retVal)
            {
                retVal = CAN_ClearMbIntStatus(id, mbIdx);
            }
        }    
        else
        {
            /*nothing to do*/
        }
    }
    
    
    return retVal;    
}

/**
 * @brief     It selects How CAN recovers from bus off state. If 
 *            CAN_BUS_OFF_RECOV_AUTO is selected, automatic recovering from Bus 
 *            Off state occurs according to the CAN Specification. If 
 *            CAN_BUS_OFF_RECOV_MANUAL is selected, user can call 
 *            CAN_RecoverFromBusOffManually() to recover from bus off state.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  recov: It selects how to recover from bus off.

 * @note this function shall be called before entering bus off state. If CAN 
 *       recovers from bus off manually through CAN_RecoverFromBusOffManually(),
 *       and user need to select CAN_BUS_OFF_RECOV_MANUAL for the next time,
 *       this function shall be called again. 
 *
 * @return     none
 *
 *
 */
void CAN_BusOffRecoveryScheme(CAN_Id_t id, CAN_BusOffRecovery_t recov)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    
    CANx->CAN_CTRL1.BOFFREC = (uint32_t)recov;    
}

/**
 * @brief     If CAN_BUS_OFF_RECOV_MANUAL is selected, user can call 
 *            CAN_RecoverFromBusOffManually() to recover from bus off state.
 *
 * @param[in]  id: select the CAN ID
 *
 * @return     none
 *
 *
 */
void CAN_RecoverFromBusOffManually(CAN_Id_t id)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    
    CANx->CAN_CTRL1.BOFFREC = 0;
}

/**
 * @brief      Enables the Transceiver Delay Compensation feature in CAN FD mode
 *             and sets the Transceiver Delay Compensation Offset (offset value
 *             to be added to the measured transceiver's loop delay in order to
 *             define the position of the delayed comparison point when bit rate
 *             switching is active).
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  offset: Transceiver Delay Compensation Offset
 *
 * @return    status
 *            - SUCC -- successful
 *            - ERR -- some error
 *
 */
ResultStatus_t CAN_FdTdcEnable(CAN_Id_t id, uint8_t offset)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    uint32_t freeze =  CANx->CAN_MCR.FRZACK;
    ResultStatus_t retVal = SUCC;
    if (0U == freeze)
    {
        if(CAN_EnterFreezeMode(id) != SUCC)
        {
            retVal = ERR;
        }
    }
    if(SUCC == retVal)
    {
        CANx->CAN_FDCTRL.TDCEN = 1;
        CANx->CAN_FDCTRL.TDCOFF = offset;

        if (0U == freeze)
        {
            if(CAN_ExitFreezeMode(id) != SUCC)
            {
                retVal = ERR;
            }
        }
    }
    return retVal;
}

/**
 * @brief      Disables the Transceiver Delay Compensation feature in CAN FD mode
 *
 * @param[in]  id: select the CAN ID
 *
 * @return    status
 *            - SUCC -- successful
 *            - ERR -- some error
 *
 */
ResultStatus_t CAN_FdTdcDisable(CAN_Id_t id)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    uint32_t freeze =  CANx->CAN_MCR.FRZACK;
    ResultStatus_t retVal = SUCC;
    if (0U == freeze)
    {
        if(CAN_EnterFreezeMode(id) != SUCC)
        {
            retVal = ERR;
        }
    }
    if(SUCC == retVal)
    {
        CANx->CAN_FDCTRL.TDCEN = 0;

        if (0U == freeze)
        {
            if(CAN_ExitFreezeMode(id) != SUCC)
            {
                retVal = ERR;
            }
        }
    }
    return retVal;
}

/**
 * @brief   Gets the value of the Transceiver Delay Compensation.
 *
 * @param[in]  id: select the CAN ID
 *
 * @return  The value of the transceiver loop delay measured from the transmitted
 *          EDL to R0 transition edge to the respective received one added to 
 *          the TDCOFF value.
 */
uint8_t CAN_GetTdcValue(CAN_Id_t id)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    
    return (uint8_t)(CANx->CAN_FDCTRL.TDCVAL);
}

/**
 * @brief Gets the value of the TDC Fail flag.
 *
 * @param[in]  id: select the CAN ID
 *
 * @return  If SET, indicates that the TDC mechanism is out of range, unable to
 *          compensate the transceiver's loop delay and successfully compare the
 *          delayed received bits to the transmitted ones.
 */
FlagStatus_t CAN_GetTdcFail(CAN_Id_t id)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    
    return (CANx->CAN_FDCTRL.TDCFAIL != 0U) ? SET : RESET;
}

/**
 * @brief Clears the TDC Fail flag.
 *
 * @param[in]  id: select the CAN ID
 *
 * @return none
 *
 */
void CAN_ClearTdcFail(CAN_Id_t id)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    
    CANx->CAN_FDCTRL.TDCFAIL = 1;
}

/**
 * @brief  if a message is received by RX FIFO, this function can get the number 
 *         of the ID filter which the received message hit. It is only valid,
 *         when CAN_IFLAG1[BUF5I] is asserted.
 *
 * @param[in]  id: select the CAN ID
 *
 * return  Hit id
 */
uint32_t CAN_GetRxFifoIdHit(CAN_Id_t id)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);;
    
    return CANx->CAN_RXFIR.IDHIT;
}

/**
 * @brief  Set the code of a message buffer
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: Index of the message buffer. 
 *                    The MB should not be occupied by RX FIFO if RX FIFO is 
 *                    enabled, otherwise, it will return ERR.
 *                    For CAN0-5, the maximum mbIdx is 63 if payload size is
 *                    8-byte. 
 *                    For CAN6-7, the maximum mbIdx is 127 if payload size is
 *                    8-byte.
 * @param[in]  code: the code to be set
 *
 * return  status
 *         - ERR  mbIdx is invalid, can not find the MB
 *         - SUCC 
 */
ResultStatus_t CAN_SetMbCode(CAN_Id_t id, uint32_t mbIdx, CAN_MbCode_t code)
{
    CAN_Mb_t *mb;
    ResultStatus_t retVal = SUCC;
    if(ERR == CAN_GetMbAddr(id,(uint8_t)mbIdx,NULL,&mb))
    {
        retVal = ERR;
    }
    else if(ERR == CAN_CheckMbId(id,mbIdx))
    {
        retVal = ERR;
    }
    else
    {
        mb->config.BF.CODE = (uint32_t)code;
    }
    
    return retVal;
}

#if (1U == CAN_ABORT_EN)
/**
 * @brief  Writes the abort code into the CODE field of the requested Tx message
 *         buffer to abort transmission. User needs to check if MB transmission
 *         is aborted or not after this function. It is suggested to use 
 *         CAN_InactiveMb() to abort MB transmission instead of this function.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: Index of the message buffer.
 *                    The MB should not be occupied by RX FIFO if RX FIFO is 
 *                    enabled, otherwise, it will return ERR.
 *                    For CAN0-5, the maximum mbIdx is 63 if payload size is
 *                    8-byte. 
 *                    For CAN6-7, the maximum mbIdx is 127 if payload size is
 *                    8-byte.
 *
 * @note  This function is available only when CAN_ABORT_EN = 1U
 * @return  status
 *         - ERR  mbIdx is invalid
 *         - SUCC 
 */
ResultStatus_t CAN_AbortTxMb(CAN_Id_t id, uint32_t mbIdx)
{
    return CAN_SetMbCode(id, mbIdx, CAN_MB_TX_ABORT);
}
#endif

/**
 * @brief  Enable/Disable global network time mechanism. If enabled, it resets 
 *         the free running timer each time a message is received in message 
 *         buffer 0. This feature provides means to synchronize multiple 
 *         CAN stations with a special "SYNC" message, that is, global 
 *         network time. If Rx FIFO is enabled, the first available mailbox, 
 *         according to CAN_CTRL2[RFFN] setting, is used for timer 
 *         synchronization instead of MB0. 
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  state: timer sync feature enable or not
 *
 * return  status
 *         - SUCC -- successful
 *         - ERR -- some error
 */
ResultStatus_t CAN_ControlGlobalNetworkTime(CAN_Id_t id, ControlState_t state)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    uint32_t freeze =  CANx->CAN_MCR.FRZACK;
    ResultStatus_t retVal = SUCC;
    if (0U == freeze)
    {
        if(CAN_EnterFreezeMode(id) != SUCC)
        {
            retVal = ERR;
        }
    }
    if(SUCC == retVal)
    {
        CANx->CAN_CTRL1.TSYC = (uint32_t)state;
        
        if (0U == freeze)
        {
            if(CAN_ExitFreezeMode(id) != SUCC)
            {
                retVal = ERR;
            }
        }
    }
    return retVal;
}
                                
/**
 * @brief  Get the lowest number inactive MB
 *
 * @param[in]  id: select the CAN ID
 *
 * return  the lowest number inactive MB.
 *         0 - 63: the lowest number inactive MB
 *         0xFF: it means that there is no inactive MB or it can not be read at 
 *               this moment.
 *          
 */
uint8_t CAN_GetInactiveMb(CAN_Id_t id)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    uint8_t retVal = 0xFFU;
    if(CANx->CAN_ESR2.VPS != 0U)
    {
        if(CANx->CAN_ESR2.IMB != 0U)
        {
            retVal = (uint8_t)(CANx->CAN_ESR2.LPTM);
        }
    }

    /* there is no inactive MB or it can not be read at this moment. */
    return retVal;
}

/**
 * @brief      Get the code of a message buffer.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: Index of the message buffer. 
 *                    The MB should not be occupied by RX FIFO if RX FIFO is 
 *                    enabled, otherwise, it will return ERR.
 *                    For CAN0-5, the maximum mbIdx is 63 if payload size is
 *                    8-byte. 
 *                    For CAN6-7, the maximum mbIdx is 127 if payload size is
 *                    8-byte.
 * @param[in]  code: the code will be stored in the memory that pointed by this
 *                   pointer
 *
 * @return     status
 *
 *
 */
ResultStatus_t CAN_GetMbCode(CAN_Id_t id, uint32_t mbIdx, uint32_t *code)
{
    CAN_Mb_t *mbAddr;
    ResultStatus_t retVal = SUCC;
    if(ERR == CAN_GetMbAddr(id, (uint8_t)mbIdx, NULL, &mbAddr))
    {
        retVal = ERR;
    }    
    else if(ERR == CAN_CheckMbId(id,mbIdx))
    {
        retVal = ERR;
    }
    else
    {
        *code = mbAddr->config.BF.CODE;
    }
    return retVal;
}

/**
 * @brief  enable timeout to be a wakeup source for Pretended Networking.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  timeout: timeout value.
 *
 * @return  status
 *          - SUCC -- successful
 *          - ERR -- some error
 *
 */
ResultStatus_t CAN_EnablePnTimeoutWakeup(CAN_Id_t id, uint16_t timeout)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    uint32_t freeze =  CANx->CAN_MCR.FRZACK;
    ResultStatus_t retVal = SUCC;
    if (0U == freeze)
    {
        if(CAN_EnterFreezeMode(id) != SUCC)
        {
            retVal = ERR;
        }
    }
    if(SUCC == retVal)
    {
        /* set timeout value */
        CANx->CAN_CTRL2_PN.MATCHTO = timeout;
        /* enable timeout as a wakeup source */
        if(SUCC != CAN_IntMask(id, CAN_INT_PN_WAKEUP_TIMEOUT, UNMASK,0,0,0,0))
        {
            retVal = ERR;
        }        
        else if (0U == freeze)
        {
            if(CAN_ExitFreezeMode(id) != SUCC)
            {
                retVal = ERR;
            }
        }
        else
        {
            /*nothing to do*/
        }
    }
    return retVal;
}


/**
 * @brief  Disable timeout to be a wakeup source for Pretended Networking.
 *
 * @param[in]  id: select the CAN ID
 *
 * @return  status
 *          - SUCC -- successful
 *          - ERR -- some error
 *
 */
ResultStatus_t CAN_DisablePnTimeoutWakeup(CAN_Id_t id)
{
    return CAN_IntMask(id, CAN_INT_PN_WAKEUP_TIMEOUT, MASK,0,0,0,0);
}

/**
 * @brief  enable and config the wakeup source of receiving matched messages 
 *         for Pretended Networking.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  config: match wakeup config.
 *
 * @return  status
 *          - SUCC -- successful
 *          - ERR -- some error
 *
 */
ResultStatus_t CAN_EnablePnMatchWakeup(CAN_Id_t id, 
                                       const CAN_PnMatchConfig_t *config)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    uint32_t freeze =  CANx->CAN_MCR.FRZACK;
    ResultStatus_t retVal = SUCC;
    if (0U == freeze)
    {
        if(CAN_EnterFreezeMode(id) != SUCC)
        {
            retVal = ERR;
        }
    }
    if(SUCC == retVal)
    {
        CANx->CAN_CTRL1_PN.NMATCH = config->numMatches;
        CANx->CAN_CTRL1_PN.FCS = (uint32_t)(config->matchScheme);
        CANx->CAN_CTRL1_PN.IDFS = (uint32_t)(config->idFilterType);
        CANx->CAN_CTRL1_PN.PLFS = (uint32_t)(config->payloadFilterType);

        /* config ID filter1 */
        CANx->CAN_FLT_ID1.FLT_IDE = (uint32_t)(config->idFilter1.idType);
        CANx->CAN_FLT_ID1.FLT_RTR = (uint32_t)(config->idFilter1.remoteFlag);
        if(CAN_MSG_ID_EXT == config->idFilter1.idType)
        {
            CANx->CAN_FLT_ID1.FLT_ID1 = config->idFilter1.id;
        }
        else
        {
            CANx->CAN_FLT_ID1.FLT_ID1 = config->idFilter1.id << CAN_ID_STD_SHIFT;
        }
        /* set the mask for IDE and RTR */
        CANx->CAN_FLT_ID2_IDMASK.IDE_MSK = (uint32_t)(config->idFilter2.idType);
        CANx->CAN_FLT_ID2_IDMASK.RTR_MSK = (uint32_t)(config->idFilter2.remoteFlag);
            
        /* Configure the ID filter2, if needed */
        /*(as mask for exact matching or higher limit for range matching) */
        if ((CAN_PN_MATCH_EXACT == config->idFilterType) || 
            (CAN_PN_MATCH_RANGE == config->idFilterType))
        {
            /* config ID filter2 */
            if(CAN_MSG_ID_EXT == config->idFilter2.idType)
            {
                CANx->CAN_FLT_ID2_IDMASK.FLT_ID2_IDMASK = config->idFilter2.id;
            }
            else
            {
                CANx->CAN_FLT_ID2_IDMASK.FLT_ID2_IDMASK = config->idFilter2.id << 
                  CAN_ID_STD_SHIFT;
            }        
        }
        
        /* config payload match */
        if((CAN_FILTER_ID_PAYLOAD == config->matchScheme) || 
            (CAN_FILTER_ID_PAYLOAD_NTIMES == config->matchScheme))
        {
            CANx->CAN_FLT_DLC.FLT_DLC_LO = config->payloadFilter.dlcLow;
            CANx->CAN_FLT_DLC.FLT_DLC_HI = config->payloadFilter.dlcHigh;
            CANx->CAN_PL1_LO.DATA_BYTE_0 = config->payloadFilter.payload1[0];
            CANx->CAN_PL1_LO.DATA_BYTE_1 = config->payloadFilter.payload1[1];
            CANx->CAN_PL1_LO.DATA_BYTE_2 = config->payloadFilter.payload1[2];
            CANx->CAN_PL1_LO.DATA_BYTE_3 = config->payloadFilter.payload1[3];
            CANx->CAN_PL1_HI.DATA_BYTE_4 = config->payloadFilter.payload1[4];
            CANx->CAN_PL1_HI.DATA_BYTE_5 = config->payloadFilter.payload1[5];
            CANx->CAN_PL1_HI.DATA_BYTE_6 = config->payloadFilter.payload1[6];
            CANx->CAN_PL1_HI.DATA_BYTE_7 = config->payloadFilter.payload1[7];
            
            /* Configure the second payload, if needed */
            /*(as mask for exact matching or higher limit for range matching) */
            if ((CAN_PN_MATCH_EXACT == config->payloadFilterType) || 
                (CAN_PN_MATCH_RANGE == config->payloadFilterType))
            {
                CANx->CAN_PL2_PLMASK_LO.DATA_BYTE_0 = 
                  config->payloadFilter.payload2[0];
                CANx->CAN_PL2_PLMASK_LO.DATA_BYTE_1 = 
                  config->payloadFilter.payload2[1];
                CANx->CAN_PL2_PLMASK_LO.DATA_BYTE_2 = 
                  config->payloadFilter.payload2[2];
                CANx->CAN_PL2_PLMASK_LO.DATA_BYTE_3 = 
                  config->payloadFilter.payload2[3];
                CANx->CAN_PL2_PLMASK_HI.DATA_BYTE_4 = 
                  config->payloadFilter.payload2[4];
                CANx->CAN_PL2_PLMASK_HI.DATA_BYTE_5 = 
                  config->payloadFilter.payload2[5];
                CANx->CAN_PL2_PLMASK_HI.DATA_BYTE_6 = 
                  config->payloadFilter.payload2[6];
                CANx->CAN_PL2_PLMASK_HI.DATA_BYTE_7 = 
                  config->payloadFilter.payload2[7];
            }
        }
        
        /* enable wakeup match */
        if(SUCC != CAN_IntMask(id, CAN_INT_PN_WAKEUP_MATCH, UNMASK,0,0,0,0))
        {
            retVal = ERR;
        }        
        else if (0U == freeze)
        {
            if(CAN_ExitFreezeMode(id) != SUCC)
            {
                retVal = ERR;
            }
        }
        else
        {
          /*nothing to do*/
        }
    }
    return retVal;
}

/**
 * @brief  Disable the wakeup source of receiving matched messages 
 *         for Pretended Networking.
 *
 * @param[in]  id: select the CAN ID
 *
 * @return  status
 *          - SUCC -- successful
 *          - ERR -- some error
 *
 */
ResultStatus_t CAN_DisablePnMatchWakeup(CAN_Id_t id)
{
    return CAN_IntMask(id, CAN_INT_PN_WAKEUP_MATCH, MASK,0,0,0,0);
}

/**
 * @brief  Configures Pretended Networking settings.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  pnConfig: Points to the Pretended Networking configuration 
 *                       structure.
 *
 * @return  status
 *          - SUCC -- successful
 *          - ERR -- some error
 *
 */
ResultStatus_t CAN_EnablePn(CAN_Id_t id, const CAN_PnConfig_t *pnConfig)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    uint32_t freeze =  CANx->CAN_MCR.FRZACK;
    ResultStatus_t retVal = SUCC;
    if (0U == freeze)
    {
        if(CAN_EnterFreezeMode(id) != SUCC)
        {
            retVal = ERR;
        }
    }
    if(SUCC == retVal)
    {
        /* disable self wakeup */
        CANx->CAN_MCR.SLFWAK = 0;

        if(ENABLE == pnConfig->wakeUpTimeout)
        {
            if(SUCC != CAN_EnablePnTimeoutWakeup(id, pnConfig->timeout))
            {
                retVal = ERR;
            }
        }
    }
    if(SUCC == retVal)
    {
        if(ENABLE == pnConfig->wakeUpMatch)
        {
            if(SUCC != CAN_EnablePnMatchWakeup(id, &(pnConfig->matchConfig)))
            {
                retVal = ERR;
            }
        }
    }
    if(SUCC == retVal)
    {
        CANx->CAN_MCR.PNET_EN = 1;

        if (0U == freeze)
        {
            if(CAN_ExitFreezeMode(id) != SUCC)
            {
                retVal = ERR;
            }
        }
    }
    return retVal;
}

/**
 * @brief  Disable Pretended Networking settings.
 *
 * @param[in]  id: select the CAN ID
 *
 * @return  status
 *          - SUCC -- successful
 *          - ERR -- some error
 *
 */
ResultStatus_t CAN_DisablePn(CAN_Id_t id)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    uint32_t freeze =  CANx->CAN_MCR.FRZACK;
    ResultStatus_t retVal = SUCC;
    if (0U == freeze)
    {
        if(CAN_EnterFreezeMode(id) != SUCC)
        {
            retVal = ERR;
        }
    }
    if(SUCC == retVal)
    {
        CANx->CAN_MCR.PNET_EN = 0;
        
        if (0U == freeze)
        {
            if(CAN_ExitFreezeMode(id) != SUCC)
            {
                retVal = ERR;
            }
        }
    }
    return retVal;
}

/**
 * @brief      Get a wakeup message buffer field values.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  wmbIdx: wakeup MB index. Its range is 0-3.
 * @param[in]  msgBuff: point to the address where the message buffer will be
 *                      stored. The size is 8 at least. 
 *
 * @return     status
 *
 *
 */
ResultStatus_t CAN_GetWakeupMsgBuff(CAN_Id_t id, uint32_t wmbIdx, 
                                    CAN_MsgBuf_t *msgBuff)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    ResultStatus_t retVal = SUCC;
    msgBuff->dataLen = (uint8_t)(CANx->CAN_WMB[wmbIdx].CS.DLC);
    msgBuff->cs = CANxw->CAN_WMB[wmbIdx].CS;
    if(CANx->CAN_WMB[wmbIdx].CS.IDE != 0U)
    {
        msgBuff->msgId = CANx->CAN_WMB[wmbIdx].ID.ID;
    }
    else
    {
        msgBuff->msgId = CANxw->CAN_WMB[wmbIdx].ID >> CAN_ID_STD_SHIFT;
    }
    
    msgBuff->data[0U] = (uint8_t)(CANx->CAN_WMB[wmbIdx].D03.DATA_BYTE_0);
    msgBuff->data[1U] = (uint8_t)(CANx->CAN_WMB[wmbIdx].D03.DATA_BYTE_1);
    msgBuff->data[2U] = (uint8_t)(CANx->CAN_WMB[wmbIdx].D03.DATA_BYTE_2);
    msgBuff->data[3U] = (uint8_t)(CANx->CAN_WMB[wmbIdx].D03.DATA_BYTE_3);
    msgBuff->data[4U] = (uint8_t)(CANx->CAN_WMB[wmbIdx].D47.DATA_BYTE_4);
    msgBuff->data[5U] = (uint8_t)(CANx->CAN_WMB[wmbIdx].D47.DATA_BYTE_5);
    msgBuff->data[6U] = (uint8_t)(CANx->CAN_WMB[wmbIdx].D47.DATA_BYTE_6);
    msgBuff->data[7U] = (uint8_t)(CANx->CAN_WMB[wmbIdx].D47.DATA_BYTE_7);
   
    return retVal;
}
                                  
/**
 * @brief  Enable self wakeup function.
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  intEn: it indicates if the self wakeup interrupt is enabled.
 *                    If it is required to wake up the chip from stop mode 
 *                    through self wakeup. intEn has to be set to ENABLE.
 * @param[in]  filterEn: it indicates if the low-pass filter is enabled to 
 *                        protect the Rx CAN input from spurious wake up
 * 
 * @return  status
 *          - SUCC -- successful
 *          - ERR -- some error
 *
 */
ResultStatus_t CAN_EnableSelfWakeup(CAN_Id_t id, ControlState_t intEn, 
                                    ControlState_t filterEn)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    uint32_t freeze =  CANx->CAN_MCR.FRZACK;
    ResultStatus_t retVal = SUCC;
    
    if (0U == freeze)
    {
        if(CAN_EnterFreezeMode(id) != SUCC)
        {
            retVal = ERR;
        }
    }
    if(SUCC == retVal)
    {
        /* enable self wakeup */
        CANx->CAN_MCR.SLFWAK = 1;
        CANx->CAN_MCR.WAKSRC = (uint32_t)filterEn;
        
        if(ENABLE == intEn)
        {
            /* enable self wakeup interrupt */
            if(SUCC != CAN_IntMask(id, CAN_INT_SELF_WAKEUP, UNMASK,0,0,0,0))
            {
                retVal = ERR;
            }
        }
        else
        {
            /* disable self wakeup interrupt */
            if(SUCC != CAN_IntMask(id, CAN_INT_SELF_WAKEUP, MASK,0,0,0,0))
            {
                retVal = ERR;
            }
        }
    }
    if(SUCC == retVal)
    {
        if (0U == freeze)
        {
            if(CAN_ExitFreezeMode(id) != SUCC)
            {
                retVal = ERR;
            }
        }
    }
    return retVal;
}
                                  
/**
 * @brief  Disable self wakeup function.
 *
 * @param[in]  id: select the CAN ID
 *
 * @return  status
 *          - SUCC -- successful
 *          - ERR -- some error
 *
 */
ResultStatus_t CAN_DisableSelfWakeup(CAN_Id_t id)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    uint32_t freeze =  CANx->CAN_MCR.FRZACK;
    ResultStatus_t retVal = SUCC;
    
    if (0U == freeze)
    {
        if(CAN_EnterFreezeMode(id) != SUCC)
        {
            retVal = ERR;
        }
    }
    if(SUCC == retVal)
    {
        /* disable self wakeup */
        CANx->CAN_MCR.SLFWAK = 0;
        
        /* disable self wakeup interrupt */
        if(SUCC != CAN_IntMask(id, CAN_INT_SELF_WAKEUP, MASK,0,0,0,0))
        {
            retVal = ERR;
        }        
        else if (0U == freeze)
        {
            if(CAN_ExitFreezeMode(id) != SUCC)
            {
                retVal = ERR;
            }
        }
        else
        {
          /*nothing to do*/
        }
    }
    return retVal;
}

/**
 * @brief  Enable enter into doze mode when received entering into wait mode
 *         request.
 *
 * @param[in]  id: select the CAN ID
 *
 * @return none
 *
 */
void CAN_EnableDozeMode(CAN_Id_t id)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    
    CANx->CAN_MCR.DOZE = 1U;
}

/**
 * @brief  Disable enter into doze mode when received entering into wait mode
 *         request.
 *
 * @param[in]  id: select the CAN ID
 *
 * @return none
 *
 */
void CAN_DisableDozeMode(CAN_Id_t id)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    
    CANx->CAN_MCR.DOZE = 0U;
}

/**
 * @brief  config the action when received a remote request frame
 *
 * @param[in]  id: select the CAN ID
 * @param[in] autoResponse: config if remote response frame is transmitted 
 *                          automatically after receiving a remote request frame.
 *                         - ENABLE: The received remote request frame is not
 *                            stored and remote response frame, which is 
 *                            configured through function 
 *                            CAN_ConfigRemoteResponseMb() is transmitted
 *                            automatically
 *                         - DISABLE: remote request frame is stored in the 
 *                           same fashion of a data frame in a RX message buffer,
 *                           configured through function CAN_MbReceive(),
 *                           no automatic remote response is transmitted.
 *                         if RXFIFO is enabled and used to receive remote 
 *                         request, remote request frame is stored and no 
 *                         automatic remote response is transmitted. 
 *
 * @return  status
 *          - SUCC -- successful
 *          - ERR -- some error
 *
 */
ResultStatus_t CAN_RemoteFrameConfig(CAN_Id_t id, ControlState_t autoResponse)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    uint32_t freeze =  CANx->CAN_MCR.FRZACK;
    ResultStatus_t retVal = SUCC;
    if (0U == freeze)
    {
        if(CAN_EnterFreezeMode(id) != SUCC)
        {
            retVal = ERR;
        }
    }
    if(SUCC == retVal)
    {
        if(ENABLE == autoResponse)
        {
            CANx->CAN_CTRL2.RRS = 0U;
        }
        else
        {
            CANx->CAN_CTRL2.RRS = 1U;
        }
        
        if (0U == freeze)
        {
            if(CAN_ExitFreezeMode(id) != SUCC)
            {
                retVal = ERR;
            }
        }
    }
    return retVal;
}

/**
 * @brief      Install callback function for interrupts except message buffer 
 *             interrupts. 
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  intType: select interrupt type
 * @param[in]  cbFun: indicate callback function
 *
 * @return     ResultStatus_t
 *             - SUCC
 *             - ERR: the input parameter is invalid
 *
 */  
ResultStatus_t CAN_InstallCallBackFunc(CAN_Id_t id, CAN_Int_t intType, 
                                       isr_cb_t * cbFun)
{
    ResultStatus_t retVal = SUCC;
    if((uint32_t)intType >= ((uint32_t)CAN_INT_ALL - 1U))
    {
        retVal = ERR;
    }
    else
    {
        canIsrCbFunc[id].cbf[intType] = cbFun;
    }

    return retVal;
}

/**
 * @brief      Install callback function for CAN0-5 message buffer interrupts
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIntType: select the MB interrupt type
 * @param[in]  mbCbf: indicate callback function
 *
 * @return     ResultStatus_t
 *             - SUCC
 *             - ERR: the input parameter is invalid
 *
 */ 
ResultStatus_t CAN05_InstallMbCallBackFunc(CAN_Id_t id, CAN05_MbInt_t mbIntType, 
                                           can_mb_cb_t mbCbf)
{
    ResultStatus_t retVal = SUCC;
    if((uint32_t)id >= (uint32_t)CAN_ID_6)
    {
        retVal = ERR;
    }    
    else if((uint32_t)mbIntType > (uint32_t)CAN05_MB_INT_48TO63)
    {
        retVal = ERR;
    }
    else
    {
        canIsrCbFunc[id].mbCbf[mbIntType] = mbCbf;
    }
        
    return retVal;
}

/**
 * @brief      Install callback function for CAN6-7 message buffer interrupts
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIntType: select the MB interrupt type
 * @param[in]  mbCbf: indicate callback function
 *
 * @return     ResultStatus_t
 *             - SUCC
 *             - ERR: the input parameter is invalid
 *
 */ 
ResultStatus_t CAN67_InstallMbCallBackFunc(CAN_Id_t id, CAN67_MbInt_t mbIntType, 
                                           can_mb_cb_t mbCbf)
{
    ResultStatus_t retVal = SUCC;
    if((id != CAN_ID_6) && (id != CAN_ID_7))
    {
        retVal = ERR;
    }    
    else if((uint32_t)mbIntType > (uint32_t)CAN67_MB_INT_96TO127)
    {
        retVal = ERR;
    }
    else
    {
        canIsrCbFunc[id].mbCbf[mbIntType] = mbCbf;
    }

    return retVal;
}

/**
 * @brief      Interrupt mask/unmask
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  intType: interrupt to be masked/unmasked
 * @param[in]  intMask: MASK/UNMASK
 * @param[in]  mb0t31: if intType is CAN_INT_MB, this parameter selects the MBs
 *                     (MB0-MB31) to be configured. Each bit corresponds a MB
 *                     (bit0 - MB0, bit1 - MB1, ... ,bit31 - MB31). If a bit 
 *                     is 1,it means the corresponding MB to be configured.
 *                     For other interrupt type, this parameter can be ignored.
 * @param[in]  mb32t63: if intType is CAN_INT_MB, this parameter selects the MBs
 *                     (MB32-MB63) to be configured. Each bit corresponds a MB
 *                     (bit0 - MB32, bit1 - MB33, ... ,bit31 - MB63). If a bit 
 *                     is 1,it means the corresponding MB to be configured.
 *                     For other interrupt type, this parameter can be ignored.
 * @param[in]  mb64t95: It is only valid for CAN6 and CAN7.
 *                      if intType is CAN_INT_MB, this parameter selects the MBs
 *                     (MB64-MB95) to be configured. Each bit corresponds a MB
 *                     (bit0 - MB64, bit1 - MB65, ... ,bit31 - MB95). If a bit 
 *                     is 1,it means the corresponding MB to be configured.
 *                     For other interrupt type, this parameter can be ignored.
 * @param[in]  mb96t127: It is only valid for CAN6 and CAN7.
 *                      if intType is CAN_INT_MB, this parameter selects the MBs
 *                     (MB96-MB127) to be configured. Each bit corresponds a MB
 *                     (bit0 - MB96, bit1 - MB97, ... ,bit31 - MB127). If a bit 
 *                     is 1,it means the corresponding MB to be configured.
 *                     For other interrupt type, this parameter can be ignored.
 *
 * @note       For CAN0 - CAN5, only 64 MB is available. parameters mb64t95 and 
 *             mb96t127 will be ignored.
 *
 * @return     status
 *             - SUCC -- successful
 *             - ERR -- some error
 *
 */
ResultStatus_t CAN_IntMask(CAN_Id_t id, CAN_Int_t intType, IntMask_t intMask, 
                           uint32_t mb0t31, uint32_t mb32t63, uint32_t mb64t95, 
                           uint32_t mb96t127)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    uint32_t freeze =  CANx->CAN_MCR.FRZACK;
    ResultStatus_t retVal = SUCC;
    if (0U == freeze)
    {
    	if(CAN_EnterFreezeMode(id) != SUCC)
        {
            retVal = ERR;
        }
    }
    if(SUCC == retVal)
    {
        switch(intType)
        {
            case CAN_INT_MB:
                if(UNMASK == intMask)
                {
                    CANxw->CAN_IMASK1 |= mb0t31;
                    CANxw->CAN_IMASK2 |= mb32t63;
                    if((CAN_ID_6 == id) || (CAN_ID_7 == id))
                    {
                        CANxw->CAN_IMASK3 |= mb64t95;
                        CANxw->CAN_IMASK4 |= mb96t127;
                    }
                }
                else
                {
                    CANxw->CAN_IMASK1 &= ~mb0t31;
                    CANxw->CAN_IMASK2 &= ~mb32t63;
                    if((CAN_ID_6 == id) || (CAN_ID_7 == id))
                    {
                        CANxw->CAN_IMASK3 &= ~mb64t95;
                        CANxw->CAN_IMASK4 &= ~mb96t127;
                    }
                }                
                break;
                
            case CAN_INT_BUS_OFF:
            case CAN_INT_ERR:
                if(UNMASK == intMask)
                {
                    canIntMaskStatus1[id] |= canInterruptFlagMaskTable[intType];
                    CANxw->CAN_CTRL1 |= canInterruptMaskTable[intType];
                }
                else
                {
                    CANxw->CAN_CTRL1 &= ~canInterruptMaskTable[intType];
                    canIntMaskStatus1[id] &= ~canInterruptFlagMaskTable[intType];
                }
                break;
                
            case CAN_INT_TXW:
            case CAN_INT_RXW:
                if(UNMASK == intMask)
                {
                    CANx->CAN_MCR.WRNEN = 1U;
                    canIntMaskStatus1[id] |= canInterruptFlagMaskTable[intType];
                    CANxw->CAN_CTRL1 |= canInterruptMaskTable[intType];
                }
                else
                {
                    CANx->CAN_MCR.WRNEN = 0U;
                    CANxw->CAN_CTRL1 &= ~canInterruptMaskTable[intType];
                    canIntMaskStatus1[id] &= ~canInterruptFlagMaskTable[intType];
                }
                break;
                
            case CAN_INT_BUS_OFF_DONE:
            case CAN_INT_ERR_FAST:
                if(UNMASK == intMask)
                {
                    canIntMaskStatus1[id] |= canInterruptFlagMaskTable[intType];
                    CANxw->CAN_CTRL2 |= canInterruptMaskTable[intType];
                }
                else
                {
                    CANxw->CAN_CTRL2 &= ~canInterruptMaskTable[intType];
                    canIntMaskStatus1[id] &= ~canInterruptFlagMaskTable[intType];
                }
                break;
                
            case CAN_INT_SELF_WAKEUP:
                if(UNMASK == intMask)
                {
                    canIntMaskStatus1[id] |= canInterruptFlagMaskTable[intType];
                    CANxw->CAN_MCR |= canInterruptMaskTable[intType];
                }
                else
                {
                    CANxw->CAN_MCR &= ~canInterruptMaskTable[intType];
                    canIntMaskStatus1[id] &= ~canInterruptFlagMaskTable[intType];
                }
                break;
                
            case CAN_INT_RXFIFO_FRAME:
            case CAN_INT_RXFIFO_WARNING:
            case CAN_INT_RXFIFO_OVERFLOW:
                if(UNMASK == intMask)
                {
                    CANxw->CAN_IMASK1 |= canInterruptMaskTable[intType];
                }
                else
                {
                    CANxw->CAN_IMASK1 &= ~canInterruptMaskTable[intType];
                }
                break;
                
            case CAN_INT_HOST_MEM_ERR:
            case CAN_INT_CAN_MEM_ERR:
            case CAN_INT_COR_MEM_ERR:
                CANx->CAN_CTRL2.ECRWRE = 1;
                CANx->CAN_MECR.ECRWRDIS = 0;
                if(UNMASK == intMask)
                {
                    CANxw->CAN_MECR |= canInterruptMaskTable[intType];
                }
                else
                {
                    CANxw->CAN_MECR &= ~canInterruptMaskTable[intType];
                }
                break;
                
            case CAN_INT_PN_WAKEUP_MATCH:
            case CAN_INT_PN_WAKEUP_TIMEOUT:
                if(UNMASK == intMask)
                {
                    CANxw->CAN_CTRL1_PN |= canInterruptMaskTable[intType];
                }
                else
                {
                    CANxw->CAN_CTRL1_PN &= ~canInterruptMaskTable[intType];
                }
                break;
                
            case CAN_INT_ALL:            
                if(UNMASK == intMask)
                {
                    canIntMaskStatus1[id] = CAN_INT_MSK_FLAG_ALL_1;
                    CANxw->CAN_IMASK1 |= 0xFFFFFFFFU;
                    CANxw->CAN_IMASK2 |= 0xFFFFFFFFU;
                    if((CAN_ID_6 == id) || (CAN_ID_7 == id))
                    {
                        CANxw->CAN_IMASK3 |= 0xFFFFFFFFU;
                        CANxw->CAN_IMASK4 |= 0xFFFFFFFFU;
                    }
                    
                    CANxw->CAN_CTRL1 |= CAN_INT_MSK_MULTI_1;
                    CANxw->CAN_CTRL2 |= CAN_INT_MSK_MULTI_2;
                    CANx->CAN_CTRL2.ECRWRE = 1U;
                    CANx->CAN_MECR.ECRWRDIS = 0U;
                    CANxw->CAN_MECR |= CAN_INT_MSK_MULTI_ECC;
                    CANx->CAN_MCR.WAKMSK = 1;
                    CANx->CAN_MCR.WRNEN = 1U;
                    CANxw->CAN_CTRL1_PN |= CAN_INT_MSK_MULTI_PN;
                }
                else
                {
                    CANxw->CAN_IMASK1 &= 0x00U;
                    CANxw->CAN_IMASK2 &= 0x00U;
                    if((CAN_ID_6 == id) || (CAN_ID_7 == id))
                    {
                        CANxw->CAN_IMASK3 &= 0x00U;
                        CANxw->CAN_IMASK4 &= 0x00U;
                    }
                    CANxw->CAN_CTRL1 &= ~CAN_INT_MSK_MULTI_1;
                    CANxw->CAN_CTRL2 &= ~CAN_INT_MSK_MULTI_2;
                    CANx->CAN_CTRL2.ECRWRE = 1U;
                    CANx->CAN_MECR.ECRWRDIS = 0U;
                    CANxw->CAN_MECR &= ~CAN_INT_MSK_MULTI_ECC;
                    CANx->CAN_MCR.WAKMSK = 0;
                    CANx->CAN_MCR.WRNEN = 0U;
                    CANxw->CAN_CTRL1_PN &= ~CAN_INT_MSK_MULTI_PN;
                    canIntMaskStatus1[id] = 0;
                }
                break;
                
            default:
                /*nothing to do*/
                break;
        }
        
        if (0U == freeze)
        {
            if(CAN_ExitFreezeMode(id) != SUCC)
            {
                retVal = ERR;
            }
        }
    }
    return retVal;
}

/**
 * @brief       MB Interrupt mask/unmask
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  mbIdx: the MB index
 * @param[in]  intMask: MASK/UNMASK
 *
 * @return     ResultStatus_t
 *             - SUCC
 *             - ERR: the input parameter is invalid
 *
 */
ResultStatus_t CAN_MbIntMask(CAN_Id_t id, uint32_t mbIdx, IntMask_t intMask)
{
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);    
    ResultStatus_t retVal = SUCC;
    if(mbIdx < 32U)
    {
        if(UNMASK == intMask)
        {
            CANxw->CAN_IMASK1 |= (1UL << mbIdx); 
        }
        else
        {
            CANxw->CAN_IMASK1 &= ~(1UL << mbIdx);
        }        
    }
    else if(mbIdx < 64U)
    {
        if(UNMASK == intMask)
        {
            CANxw->CAN_IMASK2 |= (1UL << (mbIdx - 32U)); 
        }
        else
        {
            CANxw->CAN_IMASK2 &= ~(1UL << (mbIdx - 32U));
        }        
    }
    else if(mbIdx < 96U)
    {
        if((CAN_ID_6 == id) || (CAN_ID_7 == id))
        {
            if(UNMASK == intMask)
            {
                CANxw->CAN_IMASK3 |= (1UL << (mbIdx - 64U)); 
            }
            else
            {
                CANxw->CAN_IMASK3 &= ~(1UL << (mbIdx - 64U));
            } 
        }
        else
        {
            retVal = ERR;
        }        
    }
    else if(mbIdx < 128U)
    {
        if((CAN_ID_6 == id) || (CAN_ID_7 == id))
        {
            if(UNMASK == intMask)
            {
                CANxw->CAN_IMASK4 |= (1UL << (mbIdx - 96U)); 
            }
            else
            {
                CANxw->CAN_IMASK4 &= ~(1UL << (mbIdx - 96U));
            } 
        }
        else
        {
            retVal = ERR;
        } 
    }
    else
    {
        retVal = ERR;
    }
    
    return retVal;
}

/**
 * @brief      configure all MB Interrupts masked/unmasked status
 *
 * @param[in]  id: select the CAN ID. It selects from CAN0 - CAN5.
 * @param[in]  mb0_31: the configuration for MB0-31. If a bit is 1, this 
 *                     corresponding MB is unmasked(enabled); if a bit is 0, the 
 *                     corresponding MB is masked(disabled).
 * @param[in]  mb32_63: the configuration for MB32-63. If a bit is 1, this 
 *                     corresponding MB is unmasked(enabled); if a bit is 0, the 
 *                     corresponding MB is masked(disabled).
 * @param[in]  mb64_95: It is only valid for CAN6-7
 *                     the configuration for MB64-95. If a bit is 1, this 
 *                     corresponding MB is unmasked(enabled); if a bit is 0, the 
 *                     corresponding MB is masked(disabled).
 * @param[in]  mb96_127: It is only valid for CAN6-7
 *                     the configuration for MB96-127. If a bit is 1, this 
 *                     corresponding MB is unmasked(enabled); if a bit is 0, the 
 *                     corresponding MB is masked(disabled).
 *
 * @note      mb64_95 and mb96_127 are only available for CAN6 and CAN7. For
 *            CAN0-5, their value will be ignored.
 *
 * @return     none
 *
 */
void CAN_MbsIntMask(CAN_Id_t id, uint32_t mb0_31,uint32_t mb32_63,
                    uint32_t mb64_95, uint32_t mb96_127)
{
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);

    CANxw->CAN_IMASK1 = mb0_31; 
    CANxw->CAN_IMASK2 = mb32_63;
        
    if((CAN_ID_6 == id) || (CAN_ID_7 == id))
    {
        CANxw->CAN_IMASK3 = mb64_95; 
        CANxw->CAN_IMASK4 = mb96_127;
    }
}

/**
 * @brief      Clear interrupt
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  intType: select interrupt type
 * @param[in]  mb0t31: if intType is CAN_INT_MB, this parameter selects the MBs
 *                     (MB0-MB31) to be configured. Each bit corresponds a MB
 *                     (bit0 - MB0, bit1 - MB1, ... ,bit31 - MB31). If a bit 
 *                     is 1, it means the corresponding MB interrupt is to be 
 *                     cleared.
 *                     For other interrupt type, this parameter can be ignored.
 * @param[in]  mb32t63: if intType is CAN_INT_MB, this parameter selects the MBs
 *                     (MB32-MB63) to be configured. Each bit corresponds a MB
 *                     (bit0 - MB32, bit1 - MB33, ... ,bit31 - MB63). If a bit 
 *                     is 1, it means the corresponding MB interrupt is to be 
 *                     cleared.
 *                     For other interrupt type, this parameter can be ignored.
 * @param[in]  mb64t95: It is only valid for CAN6 and CAN7.
 *                     if intType is CAN_INT_MB, this parameter selects the MBs
 *                     (MB64-MB95) to be configured. Each bit corresponds a MB
 *                     (bit0 - MB64, bit1 - MB65, ... ,bit31 - MB95). If a bit 
 *                     is 1, it means the corresponding MB interrupt is to be 
 *                     cleared.
 *                     For other interrupt type, this parameter can be ignored.
 * @param[in]  mb96t127: It is only valid for CAN6 and CAN7.
 *                      if intType is CAN_INT_MB, this parameter selects the MBs
 *                     (MB96-MB127) to be configured. Each bit corresponds a MB
 *                     (bit0 - MB96, bit1 - MB97, ... ,bit31 - MB127). If a bit 
 *                     is 1, it means the corresponding MB interrupt is to be 
 *                     cleared.
 *                     For other interrupt type, this parameter can be ignored.
 *
 * @note      For CAN0 - CAN5, only 64 MB is available. parameters mb64t95 and 
 *            mb96t127 will be ignored.
 *
 * @return    none
 *
 */ 
void CAN_IntClear(CAN_Id_t id, CAN_Int_t intType, uint32_t mb0t31,
                  uint32_t mb32t63, uint32_t mb64t95, uint32_t mb96t127)
{
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    
    switch(intType)
    {
        case CAN_INT_MB:
            CANxw->CAN_IFLAG1 = mb0t31;
            CANxw->CAN_IFLAG2 = mb32t63;
            if((CAN_ID_6 == id) || (CAN_ID_7 == id))
            {
                CANxw->CAN_IFLAG3 = mb64t95;
                CANxw->CAN_IFLAG4 = mb96t127;
            }
            break;
        
        case CAN_INT_BUS_OFF:
        case CAN_INT_ERR:    
        case CAN_INT_TXW:
        case CAN_INT_RXW:
        case CAN_INT_BUS_OFF_DONE:
        case CAN_INT_ERR_FAST:
        case CAN_INT_SELF_WAKEUP:
            CANxw->CAN_ESR1 = canInterruptFlagMaskTable[intType];
            break;
            
        case CAN_INT_RXFIFO_FRAME:
        case CAN_INT_RXFIFO_WARNING:
        case CAN_INT_RXFIFO_OVERFLOW:
            CANxw->CAN_IFLAG1 = canInterruptFlagMaskTable[intType];
            break;
            
        case CAN_INT_HOST_MEM_ERR:
        case CAN_INT_CAN_MEM_ERR:
        case CAN_INT_COR_MEM_ERR:
            CANxw->CAN_ERRSR = canInterruptFlagMaskTable[intType];
            break;
            
        case CAN_INT_PN_WAKEUP_MATCH:
        case CAN_INT_PN_WAKEUP_TIMEOUT:
            CANxw->CAN_WU_MTC = canInterruptFlagMaskTable[intType];
            break;
        
        case CAN_INT_ALL:
            CANxw->CAN_ESR1 = CAN_INT_MSK_FLAG_ALL_1;
            CANxw->CAN_ERRSR = CAN_INT_MSK_FLAG_ALL_ECC;
            CANxw->CAN_WU_MTC = CAN_INT_MSK_FLAG_ALL_PN;
            CANxw->CAN_IFLAG1 = 0xFFFFFFFFU;
            CANxw->CAN_IFLAG2 = 0xFFFFFFFFU;
            if((CAN_ID_6 == id) || (CAN_ID_7 == id))
            {
                CANxw->CAN_IFLAG3 = 0xFFFFFFFFU;
                CANxw->CAN_IFLAG4 = 0xFFFFFFFFU;
            }
            break;
        
        default:
            /*nothing to do*/
            break;
    }
}

/**
 * @brief      Get interrupt status
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  intType: select interrupt type
 * @param[in]  mbId: if intType is CAN_INT_MB, this parameter selects the MB 
 *                   status to be get. For CAN 0-5, it selects from MB0-MB63;
 *                   For CAN6-7, it selects from MB0-MB127.
 *                    
 *
 * @return    status
 *            - SET
 *            - RESET
 *
 */ 
IntStatus_t CAN_GetIntStatus(CAN_Id_t id, CAN_Int_t intType, uint32_t mbId)
{
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    IntStatus_t status = RESET;
    bool tmp[7];
        
    switch(intType)
    {
        case CAN_INT_MB:
            if((uint32_t)id < (uint32_t)CAN_ID_6)
            {
                if(mbId < 32U)
                {
                    status = ((CANxw->CAN_IFLAG1 & (1UL << mbId)) != 0U) ?
                    SET : RESET;
                }
                else if(mbId < 64U)
                {
                    status = ((CANxw->CAN_IFLAG2 & (1UL << (mbId - 32U))) != 0U) 
                      ? SET : RESET;
                }
                else
                {
                    /* the input parameter has some error */
                }
            }
            
            if(((uint32_t)CAN_ID_6 == (uint32_t)id) || 
               ((uint32_t)CAN_ID_7 == (uint32_t)id))
            {
                if(mbId < 32U)
                {
                    status = ((CANxw->CAN_IFLAG1 & (1UL << mbId)) != 0U) ? 
                           SET : RESET;
                }
                else if(mbId < 64U)
                {
                    status = ((CANxw->CAN_IFLAG2 & (1UL << (mbId - 32U))) != 0U)
                       ? SET : RESET;
                }
                else if(mbId < 96U)
                {
                    status = ((CANxw->CAN_IFLAG3 & (1UL << (mbId - 64U))) != 0U)
                      ? SET : RESET;
                }
                else if(mbId < 128U)
                {
                    status = ((CANxw->CAN_IFLAG4 & (1UL << (mbId - 96U))) != 0U)
                      ? SET : RESET;
                }
                else
                {
                    /* the input parameter has some error */
                }
            }            
            break;
        
        case CAN_INT_BUS_OFF:
        case CAN_INT_ERR:    
        case CAN_INT_TXW:
        case CAN_INT_RXW:
        case CAN_INT_BUS_OFF_DONE:
        case CAN_INT_ERR_FAST:
        case CAN_INT_SELF_WAKEUP:
            status = ((CANxw->CAN_ESR1 & 
                      canInterruptFlagMaskTable[intType]) != 0U) ? SET : RESET;
            break;
            
        case CAN_INT_RXFIFO_FRAME:
        case CAN_INT_RXFIFO_WARNING:
        case CAN_INT_RXFIFO_OVERFLOW:
            status = ((CANxw->CAN_IFLAG1 &
                      canInterruptFlagMaskTable[intType]) != 0U) ? SET : RESET;
            break;
            
        case CAN_INT_HOST_MEM_ERR:
        case CAN_INT_CAN_MEM_ERR:
        case CAN_INT_COR_MEM_ERR:
            status = ((CANxw->CAN_ERRSR &
                      canInterruptFlagMaskTable[intType]) != 0U) ? SET : RESET;
            break;
            
        case CAN_INT_PN_WAKEUP_MATCH:
        case CAN_INT_PN_WAKEUP_TIMEOUT:
            status = ((CANxw->CAN_WU_MTC &
                       canInterruptFlagMaskTable[intType]) != 0U) ? SET : RESET;
            break;
        
        case CAN_INT_ALL:
            if((uint32_t)id < (uint32_t)CAN_ID_6)
            {
                tmp[0] = (CANxw->CAN_ESR1 & CAN_INT_MSK_FLAG_ALL_1) != 0U;
                tmp[1] = (CANxw->CAN_ERRSR & CAN_INT_MSK_FLAG_ALL_ECC) != 0U;
                tmp[2] = (CANxw->CAN_IFLAG1) != 0U;
                tmp[3] = (CANxw->CAN_IFLAG2) != 0U;
                tmp[4] = (CANxw->CAN_WU_MTC & CAN_INT_MSK_FLAG_ALL_PN) != 0U;
            
                status = (tmp[0] || tmp[1] || tmp[2] || tmp[3] || tmp[4]) ?
                       SET : RESET;
            }
            
            if(((uint32_t)CAN_ID_6 == (uint32_t)id) || 
               ((uint32_t)CAN_ID_7 == (uint32_t)id))
            {
                tmp[0] = (CANxw->CAN_ESR1 & CAN_INT_MSK_FLAG_ALL_1) != 0U;
                tmp[1] = (CANxw->CAN_ERRSR & CAN_INT_MSK_FLAG_ALL_ECC) != 0U;
                tmp[2] = (CANxw->CAN_IFLAG1) != 0U;
                tmp[3] = (CANxw->CAN_IFLAG2) != 0U;
                tmp[4] = (CANxw->CAN_IFLAG3) != 0U;
                tmp[5] = (CANxw->CAN_IFLAG4) != 0U;
                tmp[6] = (CANxw->CAN_WU_MTC & CAN_INT_MSK_FLAG_ALL_PN) != 0U;
            
                status = (tmp[0] || tmp[1] || tmp[2] || tmp[3] || tmp[4] ||
                          tmp[5] || tmp[6]) ? SET : RESET;
            }            
            break;
        
        default:
            /*nothing to do*/
            break;
    }
    return status;
}
                                  
/**
 * @brief      Get CAN state
 *
 * @param[in]  id: select the CAN ID
 *
 * @return   CAN state
 *
 */ 
CAN_State_t CAN_GetState(CAN_Id_t id)
{
    CAN_State_t retVal = CAN_STATE_INVALID;
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    
    if(0U == CANx->CAN_ESR1.SYNCH)
    {
        retVal = CAN_STATE_NOT_SYNC;
    }
    else
    {
        if(CANx->CAN_ESR1.IDLE != 0U)
        {
            retVal = CAN_STATE_IDLE;
        }
        else
        {
            if(CANx->CAN_ESR1.TX != 0U)
            {
                retVal = CAN_STATE_TX;
            }
            if(CANx->CAN_ESR1.RX != 0U)
            {
                retVal = CAN_STATE_RX;
            }
        }       
    }
    
    return retVal;    
}

/**
 * @brief      Get CAN status
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  status: the status to be get
 *
 * @return   status
 *           - SET
 *           - RESET
 *
 */ 
FlagStatus_t CAN_GetStatus(CAN_Id_t id, CAN_Status_t status)
{
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);
    FlagStatus_t res;
    
    if(CAN_STATUS_ALL == status)
    {
        res = ((CANxw->CAN_ESR1 & CAN_STATUS_ALL_MASK) != 0U) ? SET : RESET; 
    }
    else
    {
        res = ((CANxw->CAN_ESR1 & ((uint32_t)1U << (uint32_t)status)) != 0U) ? SET : RESET; 
    }
    
    return res;
}

/**
 * @brief      Clear CAN status, only CAN_STATUS_ERROVR take effect
 *
 * @param[in]  id: select the CAN ID
 * @param[in]  status: the status to clear
 *              - CAN_STATUS_ERROVR: error overrun status
 *              - others: have no effect since other statuses are managed by hardware.
 *
 * @return   none
 *
 */ 
void CAN_ClearStatus(CAN_Id_t id, CAN_Status_t status)
{
    can_reg_w_t * CANxw = (can_reg_w_t *)(canRegWPtr[id]);

    if(CAN_STATUS_ERROVR == status)
    {
        CANxw->CAN_ESR1 = 1UL << (uint32_t)status;
    }
}

/**
 * @brief      Get CAN Fault Confinement State
 *
 * @param[in]  id: select the CAN ID
 *
 * @return   CAN  Fault Confinement State
 *
 */ 
CAN_FaultConfState_t CAN_GetFaultConfinementState(CAN_Id_t id)
{
    can_reg_t * CANx = (can_reg_t *)(canRegPtr[id]);
    CAN_FaultConfState_t retVal = CAN_FAULT_CONF_STATE_ERROR_ACTIVE;
    if((uint32_t)CAN_FAULT_CONF_STATE_ERROR_ACTIVE == CANx->CAN_ESR1.FLTCONF)
    {
        retVal = CAN_FAULT_CONF_STATE_ERROR_ACTIVE;
    }
    else if((uint32_t)CAN_FAULT_CONF_STATE_ERROR_PASSIVE ==
            CANx->CAN_ESR1.FLTCONF)
    {
        retVal = CAN_FAULT_CONF_STATE_ERROR_PASSIVE;
    }
    else
    {
        retVal = CAN_FAULT_CONF_STATE_BUS_OFF;    
    }
    return retVal;
}
/**
 * @brief      CAN0 IRQHandler for bus off/ bus off done interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void CAN0_BusOff_DriverIRQHandler(void)
{
    CAN_BusOffHandler(CAN_ID_0);
    COMMON_DSB();
}

/**
 * @brief      CAN0 IRQHandler for TX warning interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void CAN0_TxWarn_DriverIRQHandler(void)
{
    CAN_TxWarnHandler(CAN_ID_0);
    COMMON_DSB();
}

/**
 * @brief      CAN0 IRQHandler for RX warning interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN0_RxWarn_DriverIRQHandler(void)
{
    CAN_RxWarnHandler(CAN_ID_0);
    COMMON_DSB();
}

/**
 * @brief      CAN0 IRQHandler for Error interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN0_Err_DriverIRQHandler(void)
{
    CAN_ErrHandler(CAN_ID_0);
    COMMON_DSB();
}

/**
 * @brief      CAN0 IRQHandler for Error fast interrupt (CAN_INT_ERR_FAST)
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN0_ErrFd_DriverIRQHandler(void)
{
    CAN_ErrFdHandler(CAN_ID_0);
    COMMON_DSB();
}

/**
 * @brief      CAN0 IRQHandler for pretended networking wakeup interrupt 
 *             including CAN_INT_PN_WAKE_MATCH and CAN_INT_PN_WAKE_TIMEOUT
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN0_PnWake_DriverIRQHandler(void)
{
    CAN_PnWakeHandler(CAN_ID_0);
    COMMON_DSB();
}

/**
 * @brief      CAN0 IRQHandler for self wakeup interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN0_SelfWakeup_DriverIRQHandler(void)
{
    CAN_SelfWakeupHandler(CAN_ID_0);
    COMMON_DSB();
}

/**
 * @brief      CAN0 IRQHandler for ECC error interrupt(including 
 *             CAN_INT_HOST_MEM_ERR, CAN_INT_CAN_MEM_ERR and CAN_INT_COR_MEM_ERR
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN0_Ecc_DriverIRQHandler(void)
{
    CAN_EccHandler(CAN_ID_0);
    COMMON_DSB();
}

/**
 * @brief      CAN0 IRQHandler for MB0 - MB15 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN0_Mb0To15_DriverIRQHandler(void)
{
    CAN05_Mb0To15Handler(CAN_ID_0);
    COMMON_DSB();
}

/**
 * @brief      CAN0 IRQHandler for MB16 - MB31 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN0_Mb16To31_DriverIRQHandler(void)
{
    CAN05_Mb16To31Handler(CAN_ID_0);
    COMMON_DSB();
}

/**
 * @brief      CAN0 IRQHandler for MB32 - MB47 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN0_Mb32To47_DriverIRQHandler(void)
{
    CAN05_Mb32To47Handler(CAN_ID_0);
    COMMON_DSB();
}

/**
 * @brief      CAN0 IRQHandler for MB48 - MB63 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN0_Mb48To63_DriverIRQHandler(void)
{
    CAN05_Mb48To63Handler(CAN_ID_0);
    COMMON_DSB();
}

/**
 * @brief      CAN1 IRQHandler for bus off/ bus off done interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void CAN1_BusOff_DriverIRQHandler(void)
{
    CAN_BusOffHandler(CAN_ID_1);
    COMMON_DSB();
}

/**
 * @brief      CAN1 IRQHandler for TX warning interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void CAN1_TxWarn_DriverIRQHandler(void)
{
    CAN_TxWarnHandler(CAN_ID_1);
    COMMON_DSB();
}

/**
 * @brief      CAN1 IRQHandler for RX warning interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN1_RxWarn_DriverIRQHandler(void)
{
    CAN_RxWarnHandler(CAN_ID_1);
    COMMON_DSB();
}

/**
 * @brief      CAN1 IRQHandler for Error interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN1_Err_DriverIRQHandler(void)
{
    CAN_ErrHandler(CAN_ID_1);
    COMMON_DSB();
}

/**
 * @brief      CAN1 IRQHandler for Error fast interrupt (CAN_INT_ERR_FAST)
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN1_ErrFd_DriverIRQHandler(void)
{
    CAN_ErrFdHandler(CAN_ID_1);
    COMMON_DSB();
}

/**
 * @brief      CAN1 IRQHandler for pretended networking wakeup interrupt 
 *             including CAN_INT_PN_WAKE_MATCH and CAN_INT_PN_WAKE_TIMEOUT
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN1_PnWake_DriverIRQHandler(void)
{
    CAN_PnWakeHandler(CAN_ID_1);
    COMMON_DSB();
}

/**
 * @brief      CAN1 IRQHandler for self wakeup interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN1_SelfWakeup_DriverIRQHandler(void)
{
    CAN_SelfWakeupHandler(CAN_ID_1);
    COMMON_DSB();
}

/**
 * @brief      CAN1 IRQHandler for ECC error interrupt(including 
 *             CAN_INT_HOST_MEM_ERR, CAN_INT_CAN_MEM_ERR and CAN_INT_COR_MEM_ERR
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN1_Ecc_DriverIRQHandler(void)
{
    CAN_EccHandler(CAN_ID_1);
    COMMON_DSB();
}

/**
 * @brief      CAN1 IRQHandler for MB0 - MB15 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN1_Mb0To15_DriverIRQHandler(void)
{
    CAN05_Mb0To15Handler(CAN_ID_1);
    COMMON_DSB();
}

/**
 * @brief      CAN1 IRQHandler for MB16 - MB31 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN1_Mb16To31_DriverIRQHandler(void)
{
    CAN05_Mb16To31Handler(CAN_ID_1);
    COMMON_DSB();
}

/**
 * @brief      CAN1 IRQHandler for MB32 - MB47 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN1_Mb32To47_DriverIRQHandler(void)
{
    CAN05_Mb32To47Handler(CAN_ID_1);
    COMMON_DSB();
}

/**
 * @brief      CAN1 IRQHandler for MB48 - MB63 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN1_Mb48To63_DriverIRQHandler(void)
{
    CAN05_Mb48To63Handler(CAN_ID_1);
    COMMON_DSB();
}
/**
 * @brief      CAN2 IRQHandler for bus off/ bus off done interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void CAN2_BusOff_DriverIRQHandler(void)
{
    CAN_BusOffHandler(CAN_ID_2);
    COMMON_DSB();
}

/**
 * @brief      CAN2 IRQHandler for TX warning interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void CAN2_TxWarn_DriverIRQHandler(void)
{
    CAN_TxWarnHandler(CAN_ID_2);
    COMMON_DSB();
}

/**
 * @brief      CAN2 IRQHandler for RX warning interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN2_RxWarn_DriverIRQHandler(void)
{
    CAN_RxWarnHandler(CAN_ID_2);
    COMMON_DSB();
}

/**
 * @brief      CAN2 IRQHandler for Error interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN2_Err_DriverIRQHandler(void)
{
    CAN_ErrHandler(CAN_ID_2);
    COMMON_DSB();
}

/**
 * @brief      CAN2 IRQHandler for Error fast interrupt (CAN_INT_ERR_FAST)
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN2_ErrFd_DriverIRQHandler(void)
{
    CAN_ErrFdHandler(CAN_ID_2);
    COMMON_DSB();
}

/**
 * @brief      CAN2 IRQHandler for pretended networking wakeup interrupt 
 *             including CAN_INT_PN_WAKE_MATCH and CAN_INT_PN_WAKE_TIMEOUT
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN2_PnWake_DriverIRQHandler(void)
{
    CAN_PnWakeHandler(CAN_ID_2);
    COMMON_DSB();
}

/**
 * @brief      CAN2 IRQHandler for self wakeup interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN2_SelfWakeup_DriverIRQHandler(void)
{
    CAN_SelfWakeupHandler(CAN_ID_2);
    COMMON_DSB();
}

/**
 * @brief      CAN2 IRQHandler for ECC error interrupt(including 
 *             CAN_INT_HOST_MEM_ERR, CAN_INT_CAN_MEM_ERR and CAN_INT_COR_MEM_ERR
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN2_Ecc_DriverIRQHandler(void)
{
    CAN_EccHandler(CAN_ID_2);
    COMMON_DSB();
}

/**
 * @brief      CAN2 IRQHandler for MB0 - MB15 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN2_Mb0To15_DriverIRQHandler(void)
{
    CAN05_Mb0To15Handler(CAN_ID_2);
    COMMON_DSB();
}

/**
 * @brief      CAN2 IRQHandler for MB16 - MB31 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN2_Mb16To31_DriverIRQHandler(void)
{
    CAN05_Mb16To31Handler(CAN_ID_2);
    COMMON_DSB();
}

/**
 * @brief      CAN2 IRQHandler for MB32 - MB47 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN2_Mb32To47_DriverIRQHandler(void)
{
    CAN05_Mb32To47Handler(CAN_ID_2);
    COMMON_DSB();
}

/**
 * @brief      CAN2 IRQHandler for MB48 - MB63 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN2_Mb48To63_DriverIRQHandler(void)
{
    CAN05_Mb48To63Handler(CAN_ID_2);
    COMMON_DSB();
}
/**
 * @brief      CAN3 IRQHandler for bus off/ bus off done interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void CAN3_BusOff_DriverIRQHandler(void)
{
    CAN_BusOffHandler(CAN_ID_3);
    COMMON_DSB();
}

/**
 * @brief      CAN3 IRQHandler for TX warning interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void CAN3_TxWarn_DriverIRQHandler(void)
{
    CAN_TxWarnHandler(CAN_ID_3);
    COMMON_DSB();
}

/**
 * @brief      CAN3 IRQHandler for RX warning interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN3_RxWarn_DriverIRQHandler(void)
{
    CAN_RxWarnHandler(CAN_ID_3);
    COMMON_DSB();
}

/**
 * @brief      CAN3 IRQHandler for Error interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN3_Err_DriverIRQHandler(void)
{
    CAN_ErrHandler(CAN_ID_3);
    COMMON_DSB();
}

/**
 * @brief      CAN3 IRQHandler for Error fast interrupt (CAN_INT_ERR_FAST)
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN3_ErrFd_DriverIRQHandler(void)
{
    CAN_ErrFdHandler(CAN_ID_3);
    COMMON_DSB();
}

/**
 * @brief      CAN3 IRQHandler for pretended networking wakeup interrupt 
 *             including CAN_INT_PN_WAKE_MATCH and CAN_INT_PN_WAKE_TIMEOUT
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN3_PnWake_DriverIRQHandler(void)
{
    CAN_PnWakeHandler(CAN_ID_3);
    COMMON_DSB();
}

/**
 * @brief      CAN3 IRQHandler for self wakeup interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN3_SelfWakeup_DriverIRQHandler(void)
{
    CAN_SelfWakeupHandler(CAN_ID_3);
    COMMON_DSB();
}

/**
 * @brief      CAN3 IRQHandler for ECC error interrupt(including 
 *             CAN_INT_HOST_MEM_ERR, CAN_INT_CAN_MEM_ERR and CAN_INT_COR_MEM_ERR
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN3_Ecc_DriverIRQHandler(void)
{
    CAN_EccHandler(CAN_ID_3);
    COMMON_DSB();
}

/**
 * @brief      CAN3 IRQHandler for MB0 - MB15 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN3_Mb0To15_DriverIRQHandler(void)
{
    CAN05_Mb0To15Handler(CAN_ID_3);
    COMMON_DSB();
}

/**
 * @brief      CAN3 IRQHandler for MB16 - MB31 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN3_Mb16To31_DriverIRQHandler(void)
{
    CAN05_Mb16To31Handler(CAN_ID_3);
    COMMON_DSB();
}

/**
 * @brief      CAN3 IRQHandler for MB32 - MB47 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN3_Mb32To47_DriverIRQHandler(void)
{
    CAN05_Mb32To47Handler(CAN_ID_3);
    COMMON_DSB();
}

/**
 * @brief      CAN3 IRQHandler for MB48 - MB63 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN3_Mb48To63_DriverIRQHandler(void)
{
    CAN05_Mb48To63Handler(CAN_ID_3);
    COMMON_DSB();
}
#if ((6U == CAN_INSTANCE_NUM) || (8U == CAN_INSTANCE_NUM))
/**
 * @brief      CAN4 IRQHandler for bus off/ bus off done interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void CAN4_BusOff_DriverIRQHandler(void)
{
    CAN_BusOffHandler(CAN_ID_4);
    COMMON_DSB();
}

/**
 * @brief      CAN4 IRQHandler for TX warning interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void CAN4_TxWarn_DriverIRQHandler(void)
{
    CAN_TxWarnHandler(CAN_ID_4);
    COMMON_DSB();
}

/**
 * @brief      CAN4 IRQHandler for RX warning interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN4_RxWarn_DriverIRQHandler(void)
{
    CAN_RxWarnHandler(CAN_ID_4);
    COMMON_DSB();
}

/**
 * @brief      CAN4 IRQHandler for Error interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN4_Err_DriverIRQHandler(void)
{
    CAN_ErrHandler(CAN_ID_4);
    COMMON_DSB();
}

/**
 * @brief      CAN4 IRQHandler for Error fast interrupt (CAN_INT_ERR_FAST)
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN4_ErrFd_DriverIRQHandler(void)
{
    CAN_ErrFdHandler(CAN_ID_4);
    COMMON_DSB();
}

/**
 * @brief      CAN4 IRQHandler for pretended networking wakeup interrupt 
 *             including CAN_INT_PN_WAKE_MATCH and CAN_INT_PN_WAKE_TIMEOUT
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN4_PnWake_DriverIRQHandler(void)
{
    CAN_PnWakeHandler(CAN_ID_4);
    COMMON_DSB();
}

/**
 * @brief      CAN4 IRQHandler for self wakeup interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN4_SelfWakeup_DriverIRQHandler(void)
{
    CAN_SelfWakeupHandler(CAN_ID_4);
    COMMON_DSB();
}

/**
 * @brief      CAN4 IRQHandler for ECC error interrupt(including 
 *             CAN_INT_HOST_MEM_ERR, CAN_INT_CAN_MEM_ERR and CAN_INT_COR_MEM_ERR
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN4_Ecc_DriverIRQHandler(void)
{
    CAN_EccHandler(CAN_ID_4);
    COMMON_DSB();
}

/**
 * @brief      CAN4 IRQHandler for MB0 - MB15 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN4_Mb0To15_DriverIRQHandler(void)
{
    CAN05_Mb0To15Handler(CAN_ID_4);
    COMMON_DSB();
}

/**
 * @brief      CAN4 IRQHandler for MB16 - MB31 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN4_Mb16To31_DriverIRQHandler(void)
{
    CAN05_Mb16To31Handler(CAN_ID_4);
    COMMON_DSB();
}

/**
 * @brief      CAN4 IRQHandler for MB32 - MB47 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN4_Mb32To47_DriverIRQHandler(void)
{
    CAN05_Mb32To47Handler(CAN_ID_4);
    COMMON_DSB();
}

/**
 * @brief      CAN4 IRQHandler for MB48 - MB63 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN4_Mb48To63_DriverIRQHandler(void)
{
    CAN05_Mb48To63Handler(CAN_ID_4);
    COMMON_DSB();
}

/**
 * @brief      CAN5 IRQHandler for bus off/ bus off done interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void CAN5_BusOff_DriverIRQHandler(void)
{
    CAN_BusOffHandler(CAN_ID_5);
    COMMON_DSB();
}

/**
 * @brief      CAN5 IRQHandler for TX warning interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void CAN5_TxWarn_DriverIRQHandler(void)
{
    CAN_TxWarnHandler(CAN_ID_5);
    COMMON_DSB();
}

/**
 * @brief      CAN5 IRQHandler for RX warning interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN5_RxWarn_DriverIRQHandler(void)
{
    CAN_RxWarnHandler(CAN_ID_5);
    COMMON_DSB();
}

/**
 * @brief      CAN5 IRQHandler for Error interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN5_Err_DriverIRQHandler(void)
{
    CAN_ErrHandler(CAN_ID_5);
    COMMON_DSB();
}

/**
 * @brief      CAN5 IRQHandler for Error fast interrupt (CAN_INT_ERR_FAST)
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN5_ErrFd_DriverIRQHandler(void)
{
    CAN_ErrFdHandler(CAN_ID_5);
    COMMON_DSB();
}

/**
 * @brief      CAN5 IRQHandler for pretended networking wakeup interrupt 
 *             including CAN_INT_PN_WAKE_MATCH and CAN_INT_PN_WAKE_TIMEOUT
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN5_PnWake_DriverIRQHandler(void)
{
    CAN_PnWakeHandler(CAN_ID_5);
    COMMON_DSB();
}

/**
 * @brief      CAN5 IRQHandler for self wakeup interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN5_SelfWakeup_DriverIRQHandler(void)
{
    CAN_SelfWakeupHandler(CAN_ID_5);
    COMMON_DSB();
}

/**
 * @brief      CAN5 IRQHandler for ECC error interrupt(including 
 *             CAN_INT_HOST_MEM_ERR, CAN_INT_CAN_MEM_ERR and CAN_INT_COR_MEM_ERR
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN5_Ecc_DriverIRQHandler(void)
{
    CAN_EccHandler(CAN_ID_5);
    COMMON_DSB();
}

/**
 * @brief      CAN5 IRQHandler for MB0 - MB15 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN5_Mb0To15_DriverIRQHandler(void)
{
    CAN05_Mb0To15Handler(CAN_ID_5);
    COMMON_DSB();
}

/**
 * @brief      CAN5 IRQHandler for MB16 - MB31 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN5_Mb16To31_DriverIRQHandler(void)
{
    CAN05_Mb16To31Handler(CAN_ID_5);
    COMMON_DSB();
}

/**
 * @brief      CAN5 IRQHandler for MB32 - MB47 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN5_Mb32To47_DriverIRQHandler(void)
{
    CAN05_Mb32To47Handler(CAN_ID_5);
    COMMON_DSB();
}

/**
 * @brief      CAN5 IRQHandler for MB48 - MB63 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN5_Mb48To63_DriverIRQHandler(void)
{
    CAN05_Mb48To63Handler(CAN_ID_5);
    COMMON_DSB();
}
#endif

#if (8U == CAN_INSTANCE_NUM)
/**
 * @brief      CAN6 IRQHandler for bus off/ bus off done interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void CAN6_BusOff_DriverIRQHandler(void)
{
    CAN_BusOffHandler(CAN_ID_6);
    COMMON_DSB();
}

/**
 * @brief      CAN6 IRQHandler for TX warning interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void CAN6_TxWarn_DriverIRQHandler(void)
{
    CAN_TxWarnHandler(CAN_ID_6);
    COMMON_DSB();
}

/**
 * @brief      CAN6 IRQHandler for RX warning interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN6_RxWarn_DriverIRQHandler(void)
{
    CAN_RxWarnHandler(CAN_ID_6);
    COMMON_DSB();
}

/**
 * @brief      CAN6 IRQHandler for Error interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN6_Err_DriverIRQHandler(void)
{
    CAN_ErrHandler(CAN_ID_6);
    COMMON_DSB();
}

/**
 * @brief      CAN6 IRQHandler for Error fast interrupt (CAN_INT_ERR_FAST)
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN6_ErrFd_DriverIRQHandler(void)
{
    CAN_ErrFdHandler(CAN_ID_6);
    COMMON_DSB();
}

/**
 * @brief      CAN6 IRQHandler for pretended networking wakeup interrupt 
 *             including CAN_INT_PN_WAKE_MATCH and CAN_INT_PN_WAKE_TIMEOUT
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN6_PnWake_DriverIRQHandler(void)
{
    CAN_PnWakeHandler(CAN_ID_6);
    COMMON_DSB();
}

/**
 * @brief      CAN6 IRQHandler for self wakeup interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN6_SelfWakeup_DriverIRQHandler(void)
{
    CAN_SelfWakeupHandler(CAN_ID_6);
    COMMON_DSB();
}

/**
 * @brief      CAN6 IRQHandler for ECC error interrupt(including 
 *             CAN_INT_HOST_MEM_ERR, CAN_INT_CAN_MEM_ERR and CAN_INT_COR_MEM_ERR
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN6_Ecc_DriverIRQHandler(void)
{
    CAN_EccHandler(CAN_ID_6);
    COMMON_DSB();
}

/**
 * @brief      CAN6 IRQHandler for MB0 - MB31 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN6_Mb0To31_DriverIRQHandler(void)
{
    CAN67_Mb0To31Handler(CAN_ID_6);
    COMMON_DSB();
}

/**
 * @brief      CAN6 IRQHandler for MB32 - MB63 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN6_Mb32To63_DriverIRQHandler(void)
{
    CAN67_Mb32To63Handler(CAN_ID_6);
    COMMON_DSB();
}

/**
 * @brief      CAN6 IRQHandler for MB64 - MB95 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN6_Mb64To95_DriverIRQHandler(void)
{
    CAN67_Mb64To95Handler(CAN_ID_6);
    COMMON_DSB();
}

/**
 * @brief      CAN6 IRQHandler for MB96 - MB127 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN6_Mb96To127_DriverIRQHandler(void)
{
    CAN67_Mb96To127Handler(CAN_ID_6);
    COMMON_DSB();
}

/**
 * @brief      CAN7 IRQHandler for bus off/ bus off done interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void CAN7_BusOff_DriverIRQHandler(void)
{
    CAN_BusOffHandler(CAN_ID_7);
    COMMON_DSB();
}

/**
 * @brief      CAN7 IRQHandler for TX warning interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */ 
void CAN7_TxWarn_DriverIRQHandler(void)
{
    CAN_TxWarnHandler(CAN_ID_7);
    COMMON_DSB();
}

/**
 * @brief      CAN7 IRQHandler for RX warning interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN7_RxWarn_DriverIRQHandler(void)
{
    CAN_RxWarnHandler(CAN_ID_7);
    COMMON_DSB();
}

/**
 * @brief      CAN7 IRQHandler for Error interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN7_Err_DriverIRQHandler(void)
{
    CAN_ErrHandler(CAN_ID_7);
    COMMON_DSB();
}

/**
 * @brief      CAN7 IRQHandler for Error fast interrupt (CAN_INT_ERR_FAST)
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN7_ErrFd_DriverIRQHandler(void)
{
    CAN_ErrFdHandler(CAN_ID_7);
    COMMON_DSB();
}

/**
 * @brief      CAN7 IRQHandler for pretended networking wakeup interrupt 
 *             including CAN_INT_PN_WAKE_MATCH and CAN_INT_PN_WAKE_TIMEOUT
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN7_PnWake_DriverIRQHandler(void)
{
    CAN_PnWakeHandler(CAN_ID_7);
    COMMON_DSB();
}

/**
 * @brief      CAN7 IRQHandler for self wakeup interrupt
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN7_SelfWakeup_DriverIRQHandler(void)
{
    CAN_SelfWakeupHandler(CAN_ID_7);
    COMMON_DSB();
}

/**
 * @brief      CAN7 IRQHandler for ECC error interrupt(including 
 *             CAN_INT_HOST_MEM_ERR, CAN_INT_CAN_MEM_ERR and CAN_INT_COR_MEM_ERR
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN7_Ecc_DriverIRQHandler(void)
{
    CAN_EccHandler(CAN_ID_7);
    COMMON_DSB();
}

/**
 * @brief      CAN7 IRQHandler for MB0 - MB31 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN7_Mb0To31_DriverIRQHandler(void)
{
    CAN67_Mb0To31Handler(CAN_ID_7);
    COMMON_DSB();
}

/**
 * @brief      CAN7 IRQHandler for MB32 - MB63 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN7_Mb32To63_DriverIRQHandler(void)
{
    CAN67_Mb32To63Handler(CAN_ID_7);
    COMMON_DSB();
}

/**
 * @brief      CAN7 IRQHandler for MB64 - MB95 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN7_Mb64To95_DriverIRQHandler(void)
{
    CAN67_Mb64To95Handler(CAN_ID_7);
    COMMON_DSB();
}

/**
 * @brief      CAN7 IRQHandler for MB96 - MB127 interrupts
 *
 * @param[in]  none
 *
 * @return    none
 *
 */
void CAN7_Mb96To127_DriverIRQHandler(void)
{
    CAN67_Mb96To127Handler(CAN_ID_7);
    COMMON_DSB();
}
#endif

/** @} end of group CAN_Public_Functions */

/** @} end of group CAN */

/** @} end of group Z20K14XM_Peripheral_Driver */
