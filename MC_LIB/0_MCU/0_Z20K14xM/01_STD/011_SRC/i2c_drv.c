/**************************************************************************************************/
/**
 * @file     i2c_drv.c
 * @brief    I2C module driver file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 *
 **************************************************************************************************/

#include "i2c_drv.h"

/** @addtogroup  Z20K14XM_Peripheral_Driver
 *  @{
 */

/** @defgroup I2C
 *  @brief I2C driver modules
 *  @{
 */

/** @defgroup I2C_Private_Type
 *  @{
 */

/** @} end of group I2C_Private_Type*/

/** @defgroup I2C_Private_Defines
 *  @{
 */
#define I2C_STD_SPEED_SPKLEN       (0x01U)        /*!< I2C standard speed spike suppression limit */
#define I2C_FAST_SPEED_SPKLEN      (0x01U)        /*!< I2C fast speed spike suppression limit */
#define I2C_FAST_PLUS_SPEED_SPKLEN (0x02U)        /*!< I2C fast plus speed spike suppression limit */
#define I2C_HIGH_SPEED_SPKLEN      (0x01U)        /*!< I2C high speed spike suppression limit */
#define I2C_STD_SPEED_SCL_HC       (0x000000C0U)  /*!< Standard speed I2C Clock SCL High Count */
#define I2C_STD_SPEED_SCL_LC       (0x000000C7U)  /*!< Standard speed I2C Clock SCL Low Count */
#define I2C_FAST_SPEED_SCL_HC      (0x00000028U)  /*!< Fast Mode I2C Clock SCL High Count */
#define I2C_FAST_SPEED_SCL_LC      (0x0000002FU)  /*!< Fast Mode I2C Clock SCL Low Count */
#define I2C_FAST_PLUS_SPEED_SCL_HC (0x00000009U)  /*!< Fast Plus Mode I2C Clock SCL High Count */
#define I2C_FAST_PLUS_SPEED_SCL_LC (0x00000011U)  /*!< Fast Plus Mode I2C Clock SCL Low Count */
#define I2C_HIGH_SPEED_SCL_HC      (0x00000004U)  /*!< High speed I2C Clock SCL High Count  */
#define I2C_HIGH_SPEED_SCL_LC      (0x0000000AU)  /*!< High speed I2C Clock SCL Low Count  */
/** @} end of group I2C_Private_Defines */

/** @defgroup I2C_Private_Variables
 *  @{
 */
/**
 *  @brief I2C0 and I2C1 address array
 */
/*PRQA S 0303 ++*/
static i2c_reg_t * const i2cRegPtr[I2C_INSTANCE_NUM] = 
{
    (i2c_reg_t *)I2C0_BASE_ADDR, 
#if (2U == I2C_INSTANCE_NUM) 
    (i2c_reg_t *)I2C1_BASE_ADDR
#endif
};

static i2c_reg_w_t * const i2cRegWPtr[I2C_INSTANCE_NUM] = 
{
    (i2c_reg_w_t *)I2C0_BASE_ADDR, 
#if (2U == I2C_INSTANCE_NUM) 
    (i2c_reg_w_t *)I2C1_BASE_ADDR
#endif
};
/*PRQA S 0303 --*/

/**
 *  @brief I2C ISR callback function pointer array
 */
static isr_cb_t * i2cIsrCb[I2C_INSTANCE_NUM][I2C_INT_ALL]=
{
    {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
#if (I2C_INSTANCE_NUM == 2)
    {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
#endif
};

/**
 *  @brief I2C interrupt enable array
 */
static const uint32_t I2C_IntEnableTable[]=
{
    0x00000001U,               /*!< I2C_INT_GEN_CALL */
    0x00000002U,               /*!< I2C_INT_TX_OVER */
    0x00000004U,               /*!< I2C_INT_ERROR_ABORT */
    0x00000008U,               /*!< I2C_INT_ACTIVITY */
    0x00000010U,               /*!< I2C_INT_STOP_DET */
    0x00000020U,               /*!< I2C_INT_START_DET */
    0x00400000U,               /*!< I2C_INT_RD_REQ */
    0x00800000U,               /*!< I2C_INT_RX_DONE */
    0x01000000U,               /*!< I2C_INT_RX_UNDER */
    0x02000000U,               /*!< I2C_INT_RX_OVER */
    0x04000000U,               /*!< I2C_INT_RESTART_DET */
    0x08000000U,               /*!< I2C_SCL_STUCK_AT_LOW */
    0x40000000U,               /*!< I2C_INT_RX_FULL */
    0x80000000U,               /*!< I2C_INT_TX_EMPTY */
    0xCFC0003FU                /*!< I2C_INT_ALL */
};
/**
 *  @brief I2C interrupt array
 */
static const uint32_t I2C_IntTable[]=
{
    0U,1U,2U,3U,4U,5U,22U,23U,24U,25U,26U,27U,30U,31U
};
/** @} end of group I2C_Private_Variables */

/** @defgroup I2C_Global_Variables
 *  @{
 */

/** @} end of group I2C_Global_Variables */


/** @defgroup I2C_Private_FunctionDeclaration
 *  @{
 */
static void I2C_IntHandler(I2C_Id_t i2cNo);
void I2C0_DriverIRQHandler(void);
#if (I2C_INSTANCE_NUM == 2)
void I2C1_DriverIRQHandler(void);
#endif

/** @} end of group I2C_Private_FunctionDeclaration */

/** @defgroup I2C_Private_Functions
 *  @{
 */
/**
 * @brief      I2C interrupt handle
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 *
 * @return none
 *
 */
static void I2C_IntHandler(I2C_Id_t i2cNo)
{
    uint32_t intStatus;
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);
    i2c_reg_w_t * I2Cxw = (i2c_reg_w_t *)(i2cRegWPtr[i2cNo]);

    /* Read the interrupt status */
    intStatus = I2Cxw->I2C_STATUS0;
    /* get status */  
    intStatus &= I2Cxw->I2C_INT_ENABLE;
    /* Clear the interrupt status */
    I2Cxw->I2C_STATUS0 = intStatus;

    if((intStatus & I2C_IntEnableTable[I2C_INT_GEN_CALL]) != 0U)
    {
        if(i2cIsrCb[i2cNo][I2C_INT_GEN_CALL]!= NULL)
        {
            i2cIsrCb[i2cNo][I2C_INT_GEN_CALL]();
        }
        /* Disable the interrupt */
        else
        {
            I2Cx->I2C_INT_ENABLE.I2C_CALL_IE = 0U;
        }
    }
    if((intStatus & I2C_IntEnableTable[I2C_INT_TX_OVER]) != 0U)
    {
        if(i2cIsrCb[i2cNo][I2C_INT_TX_OVER]!= NULL)
        {
            i2cIsrCb[i2cNo][I2C_INT_TX_OVER]();
        }
        /* Disable the interrupt */
        else
        {
            I2Cx->I2C_INT_ENABLE.I2C_TX_OVF_IE = 0U;
        }
    }
    if((intStatus & I2C_IntEnableTable[I2C_INT_ERROR_ABORT]) != 0U)
    {
        if(i2cIsrCb[i2cNo][I2C_INT_ERROR_ABORT]!= NULL)
        {
            i2cIsrCb[i2cNo][I2C_INT_ERROR_ABORT]();
        }
        /* Disable the interrupt */
        else
        {
            I2Cx->I2C_INT_ENABLE.I2C_ERROR_ABORT_IE = 0U;
        }
    }
    if((intStatus & I2C_IntEnableTable[I2C_INT_ACTIVITY]) != 0U)
    {
        if(i2cIsrCb[i2cNo][I2C_INT_ACTIVITY]!= NULL)
        {
            i2cIsrCb[i2cNo][I2C_INT_ACTIVITY]();
        }
        /* Disable the interrupt */
        else
        {
            I2Cx->I2C_INT_ENABLE.I2C_ACTIVITY_DET_IE = 0U;
        }
    }
    if((intStatus & I2C_IntEnableTable[I2C_INT_STOP_DET]) != 0U)
    {
        if(i2cIsrCb[i2cNo][I2C_INT_STOP_DET]!= NULL)
        {
            i2cIsrCb[i2cNo][I2C_INT_STOP_DET]();
        }
        /* Disable the interrupt */
        else
        {
            I2Cx->I2C_INT_ENABLE.I2C_STOP_DET_IE = 0U;
        }
    }
    if((intStatus & I2C_IntEnableTable[I2C_INT_START_DET]) != 0U)
    {
        if(i2cIsrCb[i2cNo][I2C_INT_START_DET]!= NULL)
        {
            i2cIsrCb[i2cNo][I2C_INT_START_DET]();
        }
        /* Disable the interrupt */
        else
        {
            I2Cx->I2C_INT_ENABLE.I2C_START_DET_IE = 0U;
        }
    }
    if((intStatus & I2C_IntEnableTable[I2C_INT_RD_REQ]) != 0U)
    {
        if(i2cIsrCb[i2cNo][I2C_INT_RD_REQ]!= NULL)
        {
            i2cIsrCb[i2cNo][I2C_INT_RD_REQ]();
        }
        /* Disable the interrupt */
        else
        {
            I2Cx->I2C_INT_ENABLE.SLAVE_RD_REQ_IE = 0U;
        }
    }
    if((intStatus & I2C_IntEnableTable[I2C_INT_RX_DONE]) != 0U)
    {
        if(i2cIsrCb[i2cNo][I2C_INT_RX_DONE]!= NULL)
        {
            i2cIsrCb[i2cNo][I2C_INT_RX_DONE]();
        }
        /* Disable the interrupt */
        else
        {
            I2Cx->I2C_INT_ENABLE.RX_DONE_IE = 0U;
        }
    }
    if((intStatus & I2C_IntEnableTable[I2C_INT_RX_UNDER]) != 0U)
    {
        if(i2cIsrCb[i2cNo][I2C_INT_RX_UNDER]!= NULL)
        {
            i2cIsrCb[i2cNo][I2C_INT_RX_UNDER]();
        }
        /* Disable the interrupt */
        else
        {
            I2Cx->I2C_INT_ENABLE.RX_UNDER_IE = 0U;
        }
    }
    if((intStatus & I2C_IntEnableTable[I2C_INT_RX_OVER]) != 0U)
    {
        if(i2cIsrCb[i2cNo][I2C_INT_RX_OVER]!= NULL)
        {
            i2cIsrCb[i2cNo][I2C_INT_RX_OVER]();
        }
        /* Disable the interrupt */
        else
        {
            I2Cx->I2C_INT_ENABLE.RX_OVF_IE = 0U;
        }
    }
    if((intStatus & I2C_IntEnableTable[I2C_INT_RESTART_DET]) != 0U)
    {
        if(i2cIsrCb[i2cNo][I2C_INT_RESTART_DET]!= NULL)
        {
            i2cIsrCb[i2cNo][I2C_INT_RESTART_DET]();
        }
        /* Disable the interrupt */
        else
        {
            I2Cx->I2C_INT_ENABLE.RESTART_DET_IE = 0U;
        }
    }
    if((intStatus & I2C_IntEnableTable[I2C_INT_SCL_STUCK_AT_LOW]) != 0U)
    {
        if(i2cIsrCb[i2cNo][I2C_INT_SCL_STUCK_AT_LOW]!= NULL)
        {
            i2cIsrCb[i2cNo][I2C_INT_SCL_STUCK_AT_LOW]();
        }
        /* Disable the interrupt */
        else
        {
            I2Cx->I2C_INT_ENABLE.SCL_STUCK_AT_LOW_IE = 0U;
        }
    }
     if((intStatus & I2C_IntEnableTable[I2C_INT_RX_FULL]) != 0U)
    {
        if(i2cIsrCb[i2cNo][I2C_INT_RX_FULL]!= NULL)
        {
            i2cIsrCb[i2cNo][I2C_INT_RX_FULL]();
        }
        /* Disable the interrupt */
        else
        {
            I2Cx->I2C_INT_ENABLE.RX_FULL_IE = 0U;
        }
    }
    if((intStatus & I2C_IntEnableTable[I2C_INT_TX_EMPTY]) != 0U)
    {
        if(i2cIsrCb[i2cNo][I2C_INT_TX_EMPTY]!= NULL)
        {
            i2cIsrCb[i2cNo][I2C_INT_TX_EMPTY]();
        }
        /* Disable the interrupt */
        else
        {
            I2Cx->I2C_INT_ENABLE.TX_EMPTY_IE = 0U;
        }
    }
    
    COMMON_DSB();
}

/**
 * @brief  I2C0 interrupt function
 *
 * @param  none
 *
 * @return none
 *
 */
void I2C0_DriverIRQHandler(void)
{
   I2C_IntHandler(I2C0_ID);
}

#if (I2C_INSTANCE_NUM == 2)
/**
 * @brief  I2C1 interrupt function
 *
 * @param  none
 *
 * @return none
 *
 */
void I2C1_DriverIRQHandler(void)
{
   I2C_IntHandler(I2C1_ID);
}
#endif

/** @} end of group I2C_Private_Functions */

/** @defgroup I2C_Public_Functions
 *  @{
 */
/**
 * @brief      Install call back function
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C0_ID.
 * @param[in]  intId:  Specified interrupt type.
 *             - I2C_INT_GEN_CALL
 *             - I2C_INT_TX_OVER
 *             - I2C_INT_ERROR_ABORT
 *             - I2C_INT_ACTIVITY
 *             - I2C_INT_STOP_DET
 *             - I2C_INT_START_DET
 *             - I2C_INT_RD_REQ
 *             - I2C_INT_RX_DONE
 *             - I2C_INT_RX_UNDER
 *             - I2C_INT_RX_OVER
 *             - I2C_INT_RESTART_DET
 *             - I2C_SCL_STUCK_AT_LOW
 *             - I2C_INT_RX_FULL
 *             - I2C_INT_TX_EMPTY
 *             - I2C_INT_ALL
 *
 * @param[in]  cbFun: Pointer to callback function.
 *
 * @return none
 *
 */
void I2C_InstallCallBackFunc(I2C_Id_t i2cNo, I2C_Int_t intId,
                              isr_cb_t * cbFun)
{
    i2cIsrCb[i2cNo][intId] = cbFun;

}

/**
 * @brief      Initializes the I2C
 *
 * Under the premise that the crystal oscillator is OSC40M, speed mode selects
 * standard speed and the default data transfer rate is 100 Kb/s. Speed mode
 * selects fast speed and the default data transfer rate is 400 Kb/s.Speed mode
 * selects fast plus speed and the default data transfer rate is 1 Mb/s.
 *
 * Under the premise that the crystal oscillator is FIRC64M,speed mode selects
 * high speed and the default data transfer rate is 1.6 Mb/s.
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  i2cConfigStruct: Pointer to a I2C configuration structure.
 *
 * @return none
 *
 */
void I2C_Init(I2C_Id_t i2cNo, const I2C_Config_t* i2cConfigStruct)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);
  /* Set the I2C speed mode */
    I2Cx->I2C_CONFIG1.SPEED_SEL = ((uint32_t)(i2cConfigStruct->speedMode))&0x3U;

    switch(i2cConfigStruct->speedMode)
    {
        case I2C_SPEED_STANDARD:
            I2Cx->I2C_STD_SCL_HCNT.STD_SCL_HCNT = I2C_STD_SPEED_SCL_HC;
            I2Cx->I2C_STD_SCL_LCNT.STD_SCL_LCNT = I2C_STD_SPEED_SCL_LC;
            I2Cx->I2C_FSTD_SPKCNT.FSTD_SPKLEN = I2C_STD_SPEED_SPKLEN;
            break;

        case I2C_SPEED_FAST:
            I2Cx->I2C_FST_SCL_HCNT.FST_SCL_HCNT = I2C_FAST_SPEED_SCL_HC;
            I2Cx->I2C_FST_SCL_LCNT.FST_SCL_LCNT = I2C_FAST_SPEED_SCL_LC;
            I2Cx->I2C_FSTD_SPKCNT.FSTD_SPKLEN = I2C_FAST_SPEED_SPKLEN;
            break;

        case I2C_SPEED_HIGH:
            I2Cx->I2C_HS_SCL_HCNT.HS_SCL_HCNT = I2C_HIGH_SPEED_SCL_HC;
            I2Cx->I2C_HS_SCL_LCNT.HS_SCL_LCNT = I2C_HIGH_SPEED_SCL_LC;
            I2Cx->I2C_HS_SPKCNT.HS_SPKLEN = I2C_HIGH_SPEED_SPKLEN;
            break;

        case I2C_SPEED_FAST_PLUS:
            I2Cx->I2C_FST_SCL_HCNT.FST_SCL_HCNT = I2C_FAST_PLUS_SPEED_SCL_HC;
            I2Cx->I2C_FST_SCL_LCNT.FST_SCL_LCNT = I2C_FAST_PLUS_SPEED_SCL_LC;
            I2Cx->I2C_FSTD_SPKCNT.FSTD_SPKLEN = I2C_FAST_PLUS_SPEED_SPKLEN;
            break;

        default:
            /* Do nothing */
            break;
    }

    /* Set the I2C master or slave mode */
    if(I2C_MASTER == i2cConfigStruct->masterSlaveMode)
    {
        /* Disable slave */
        I2Cx->I2C_CONFIG1.SLAVE_MODE_DIS = 1U;
        /* Enable master */
        I2Cx->I2C_CONFIG1.MASTER_MODE_EN = 1U;
        /* Set I2C start its transfer in 7 or 10 bits address mode */
        I2Cx->I2C_CONFIG1.MASTER_10BIT_ADDR_SEL = 
            (uint32_t)(i2cConfigStruct->addrBitMode);
        /* Set whether RESTART conditions may be sent */
        I2Cx->I2C_CONFIG1.MASTER_RESTART_EN =
              ((ENABLE == i2cConfigStruct->restart)? 1UL : 0UL);
    }
    else
    {
        /* Enable slave */
        I2Cx->I2C_CONFIG1.SLAVE_MODE_DIS = 0U;
        /* Disable master */
        I2Cx->I2C_CONFIG1.MASTER_MODE_EN = 0U;
        /* Set I2C slave address mode */
        I2Cx->I2C_CONFIG1.SLAVE_10BIT_ADDR_SEL = 
            (uint32_t)(i2cConfigStruct->addrBitMode);
        /* Set I2C slave address */
        I2Cx->I2C_SLAVE_ADDR.SLV_ADDR = i2cConfigStruct->ownSlaveAddr;
    }
}

/**
 * @brief      Configure SCL High Count
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  speedMode: Speed mode types.
 *             - I2C_SPEED_STANDARD:I2C standard speed define.(0 to 100 Kb/s)
 *             - I2C_SPEED_FAST:I2C fast speed define.(up to 400 Kb/s)
 *             - I2C_SPEED_HIGH:I2C high speed define.(up to 1.6 Mb/s)
 *             - I2C_SPEED_FAST_PLUS:I2C fast mode plus define.(up to 1000 Kb/s)
 *
 * @return none
 *
 */
void I2C_SclHighCount(I2C_Id_t i2cNo, I2C_Speed_t speedMode)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);
    I2Cx->I2C_CONFIG1.SPEED_SEL = (uint32_t)speedMode&0x3U;
    switch(speedMode)
    {
        case I2C_SPEED_STANDARD:
            I2Cx->I2C_STD_SCL_HCNT.STD_SCL_HCNT = I2C_STD_SPEED_SCL_HC;
            break;

        case I2C_SPEED_FAST:
            I2Cx->I2C_FST_SCL_HCNT.FST_SCL_HCNT = I2C_FAST_SPEED_SCL_HC;
            break;

        case I2C_SPEED_HIGH:
            I2Cx->I2C_HS_SCL_HCNT.HS_SCL_HCNT = I2C_HIGH_SPEED_SCL_HC;
            break;

        case I2C_SPEED_FAST_PLUS:
            I2Cx->I2C_FST_SCL_HCNT.FST_SCL_HCNT = I2C_FAST_PLUS_SPEED_SCL_HC;
            break;

        default:
            /* Do nothing */
            break;
    }
}

/**
 * @brief      Configure SCL Low Count
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  speedMode: Speed mode types.
 *             - I2C_SPEED_STANDARD:I2C standard speed define.(0 to 100 Kb/s)
 *             - I2C_SPEED_FAST:I2C fast speed define.(up to 400 Kb/s)
 *             - I2C_SPEED_HIGH:I2C high speed define.(up to 1.6 Mb/s)
 *             - I2C_SPEED_FAST_PLUS:I2C fast mode plus define.(up to 1000 Kb/s)
 *
 * @return     none
 *
 */
void I2C_SclLowCount(I2C_Id_t i2cNo, I2C_Speed_t speedMode)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);
    I2Cx->I2C_CONFIG1.SPEED_SEL = (uint32_t)speedMode&0x3U;
    switch(speedMode)
    {
        case I2C_SPEED_STANDARD:
            I2Cx->I2C_STD_SCL_LCNT.STD_SCL_LCNT = I2C_STD_SPEED_SCL_LC;
            break;

        case I2C_SPEED_FAST:
            I2Cx->I2C_FST_SCL_LCNT.FST_SCL_LCNT = I2C_FAST_SPEED_SCL_LC;
            break;

        case I2C_SPEED_HIGH:
            I2Cx->I2C_HS_SCL_LCNT.HS_SCL_LCNT = I2C_HIGH_SPEED_SCL_LC;
            break;

        case I2C_SPEED_FAST_PLUS:
            I2Cx->I2C_FST_SCL_LCNT.FST_SCL_LCNT = I2C_FAST_PLUS_SPEED_SCL_LC;
            break;

        default:
            /* Do nothing */
            break;
    }
}

/**
 * @brief      Configure  Spike Suppression Limit
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  speedMode: Speed mode types.
 *             - I2C_SPEED_STANDARD:I2C standard speed define.(0 to 100 Kb/s)
 *             - I2C_SPEED_FAST:I2C fast speed define.(up to 400 Kb/s)
 *             - I2C_SPEED_HIGH:I2C high speed define.(up to 1.6 Mb/s)
 *             - I2C_SPEED_FAST_PLUS:I2C fast mode plus define.(up to 1000 Kb/s)
 *
 * @return     none
 *
 */
void I2C_LimitSpikeSuppression(I2C_Id_t i2cNo, I2C_Speed_t speedMode)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);
    I2Cx->I2C_CONFIG1.SPEED_SEL = (uint32_t)speedMode&0x3U;
    switch(speedMode)
    {
        case I2C_SPEED_STANDARD:
            I2Cx->I2C_FSTD_SPKCNT.FSTD_SPKLEN = I2C_STD_SPEED_SPKLEN;
            break;

        case I2C_SPEED_FAST:
            I2Cx->I2C_FSTD_SPKCNT.FSTD_SPKLEN = I2C_FAST_SPEED_SPKLEN;
            break;

        case I2C_SPEED_HIGH:
            I2Cx->I2C_HS_SPKCNT.HS_SPKLEN = I2C_HIGH_SPEED_SPKLEN;
            break;

        case I2C_SPEED_FAST_PLUS:
            I2Cx->I2C_FSTD_SPKCNT.FSTD_SPKLEN = I2C_FAST_PLUS_SPEED_SPKLEN;
            break;

        default:
            /* Do nothing */
            break;
    }
}
/**
 * @brief      Set the target address .
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  targetAddr: The target address for any master transaction.
 *
 * @return     none
 *
 */
void I2C_SetTargetAddr(I2C_Id_t i2cNo, uint32_t targetAddr)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);

    /* Set the target address */
    I2Cx->I2C_DEST_ADDR.DEST_ADDR = targetAddr;
}

/**
 * @brief      Set the value of the I2C high speed mode master code
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  value: High speed master mode code .
 *
 * @return     none
 *
 */
void I2C_SetMasterModeCodeAddr(I2C_Id_t i2cNo, uint32_t value)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);

    /* Set the value of the I2C high speed mode master code */
    I2Cx->I2C_CONFIG0.H_MCODE = value;
}

/**
 * @brief      Issues the STOP_DETECT interrupt if addressed in slave mode
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  stopDetAddressedType: Specified types.
 *             - I2C_SLV_STOP_DET_WHE_ADDRESSED:I2C issues the STOP_DETECT
 *               irrespective of whether it is addressed or not.
 *             - I2C_SLV_STOP_DEF_ADDRESSED:I2C issues the STOP_DETECT interrupt
 *               only when it is addressed.
 *
 * @return     none
 *
 */
void I2C_StopDetIfAddressed(I2C_Id_t i2cNo,
                            I2C_StopDetAddressed_t stopDetAddressedType)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);

    I2Cx->I2C_CONFIG1.SLAVE_STOP_DET_EN = (uint32_t)stopDetAddressedType;
}

/**
 * @brief      Issues the STOP_DETECT interrupt if master active
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  stopDetMstActiveType: Specified types.
 *             - I2C_MST_STOP_DET_WHE_ACTIVE: I2C issues the STOP_DETECT
 *               irrespective of whether the master is active.
 *             - I2C_MST_STOP_DEF_ACTIVE: I2C issues the STOP_DETECT interrupt
 *               only when the master is active.
 *
 * @return     none
 *
 */
void I2C_StopDetIfMstActive(I2C_Id_t i2cNo,
                            I2C_StopDetActive_t stopDetMstActiveType)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);

    I2Cx->I2C_CONFIG1.MASTER_STOP_DET_EN = (uint32_t)stopDetMstActiveType;
}

/**
 * @brief      Control the generation of the TXFIFO_EMPTY interrupt,
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  txEmptyType: Specified tx empty type.
 *             - I2C_TX_BUFFER: transmit buffer is at or below the threshold 
 *               value set in the TXFIFO_WATER_MARK register.
 *             - I2C_TX_DATA_PATH: transmit buffer is at or below the threshold 
 *               value set in the TXFIFO_WATER_MARK register and the transmission 
 *               of the address/data from the internal shift register for the 
 *               most recently popped command is completed.
 *
 * @return      none
 *
 */
void I2C_TxEmptyCtrl(I2C_Id_t i2cNo, I2C_TxEmptyCtrl_t txEmptyType)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);

    I2Cx->I2C_CONFIG1.TXFIFO_EMPTY_EN = (uint32_t)txEmptyType;
}

/**
 * @brief      Control whether I2C module should hold the bus when the Rx FIFO
 *             is physically full to its RXFIFO_DEPTH
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  newState: Enable/Disable function state.
 *             - ENABLE: Hold the bus when the Rx FIFO is physically full to its
 *               RXFIFO_DEPTH.
 *             - DISABLE: When Rx FIFO's RXFIFO_DEPTH is physically full,
 *               the bus is not hold.
 *
 * @return     none
 *
 */
void I2C_HoldBusCmd(I2C_Id_t i2cNo, ControlState_t newState)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);

    I2Cx->I2C_CONFIG1.HOLD_EN_RXFIFO_FULL = (uint32_t)newState;
}

/**
 * @brief      Initializes the I2C DMA
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  i2cDmaConfig: Pointer to a I2C DMA configuration structure.
 *
 * @return     none
 *
 */
void I2C_DmaConfig(I2C_Id_t i2cNo, const I2C_DmaConfig_t* i2cDmaConfig)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);
    /* Set Transmit data level */
    I2Cx->I2C_DMA_CTRL.DMA_TXFIFO_WATERMARK = 
                                           i2cDmaConfig->i2cDmaTransmitReqLevel;
    /* Set Receive data level */
    I2Cx->I2C_DMA_CTRL.DMA_RXFIFO_WATERMARK = i2cDmaConfig->i2cDmaRecvReqLevel;
}

/**
 * @brief      Enable/disable I2C DMA function.
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  transmitDmaCtrl: Transmit DMA Enable/Disable function state.
 * @param[in]  rcvDmaCtrl: Receive DMA Enable/Disable function state.
 *
 * @return     none
 *
 */
void I2C_DmaCmd(I2C_Id_t i2cNo, ControlState_t transmitDmaCtrl,
                ControlState_t rcvDmaCtrl)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);
    /* Enable/Disable the I2C DMA transmit function */
    I2Cx->I2C_DMA_CTRL.TXFIFO_DMA_EN = (uint32_t)transmitDmaCtrl;
    /* Enable/Disable the I2C DMA receive function */
    I2Cx->I2C_DMA_CTRL.RXFIFO_DMA_EN = (uint32_t)rcvDmaCtrl;
}

/**
 * @brief      Set I2C SDA Transmit hold time
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  i2cSdaTxHoldTime: Pointer to a I2C SDA Tx hold time structure.
 *
 * @return     none
 *
 */
void I2C_SetSdaTxHoldTime(I2C_Id_t i2cNo,
                          const I2C_SdaHoldTime_t* i2cSdaTxHoldTime)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);

    I2Cx->I2C_SDA_HOLD_TIMING.SDA_TX_HOLD_TIMING =
                             i2cSdaTxHoldTime->sdaTransmitHoldTime;
}

/**
 * @brief      Set I2C SDA Receive hold time
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  i2cSdaRxHoldTime: Pointer to a I2C SDA Rx hold time structure.
 *
 * @return     none
 *
 */
void I2C_SetSdaRxHoldTime(I2C_Id_t i2cNo,
                          const I2C_SdaHoldTime_t* i2cSdaRxHoldTime)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);

    I2Cx->I2C_SDA_HOLD_TIMING.SDA_RX_HOLD_TIMING = 
                             i2cSdaRxHoldTime->sdaReceiveHoldTime;
}

/**
 * @brief      SCL stuck at low timeout
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  timeOut: SCL stuck at low time of duration.
 *             I2C module generates the SCL_STUCK_AT_LOW interrupt to indicate
 *             SCL stuck at low if it detects the SCL stuck at low for the
 *             I2C_SCL_LOW_TIMEOUT in units of I2C function clock period.
 *
 * @return none
 *
 */
void I2C_SetSclHoldLowTimeout(I2C_Id_t i2cNo, uint32_t timeOut)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);

    I2Cx->I2C_SCL_LOW_TIMEOUT.SCL_LOW_TIMEOUT = timeOut;
}

/**
 * @brief      SDA stuck at low timeout
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  timeOut: SDA stuck at low time of duration.
 *             I2C module initiates the recovery of SDA line through enabling 
 *             the SDA_RECOVER_EN bit if it detects the SDA stuck at low for the 
 *             I2C_SDA_LOW_TIMEOUT in units of I2C function clock period.
 *
 * @return none
 *
 */
void I2C_SetSdaHoldLowTimeout(I2C_Id_t i2cNo, uint32_t timeOut)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);

    I2Cx->I2C_SDA_LOW_TIMEOUT.SDA_LOW_TIMEOUT = timeOut;
}

/**
 * @brief      Enable I2C .
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 *
 * @return none
 *
 */
void I2C_Enable(I2C_Id_t i2cNo)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);

    /* Enable the I2C */
    I2Cx->I2C_CONFIG0.MODULE_EN = 1U;
}

/**
 * @brief      Disable I2C .
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 *
 * @return none
 *
 */
void I2C_Disable(I2C_Id_t i2cNo)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);

    /* Disable the I2C */
    I2Cx->I2C_CONFIG0.MODULE_EN = 0U;
}

/**
 * @brief      I2C bus recover feature in master mode
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  newState: Enable/Disable function state.
 *            - ENABLE: Means bus recover feature is enable.
 *            - DISABLE: Means bus recover feature is disabled.
 *
 * @return     none
 *
 */
void I2C_MstBusRecover(I2C_Id_t i2cNo, ControlState_t newState)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);

    I2Cx->I2C_CONFIG0.MASTER_BUS_RECOVER_EN = (uint32_t)newState;
}

/**
 * @brief      I2C SDA recover feature
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  newState: Enable/Disable function state.
 *            - ENABLE: Means SDA recover feature is enable.
 *            - DISABLE: Means SDA recover feature is disabled.
 *
 * @return     none
 *
 */
void I2C_SdaRecover(I2C_Id_t i2cNo, ControlState_t newState)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);

    I2Cx->I2C_CONFIG0.SDA_RECOVER_EN = (uint32_t)newState;
}

/**
 * @brief       Block or not block the transmission of data on I2C bus
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  newState: Enable/Disable function state.
 *          - ENABLE: Blocks the transmission of data on I2C bus even if
 *                    Tx FIFO has data to transmit.
 *          - DISABLE: The transmission of data starts on I2C bus automatically,
 *                     as soon as the first data is available in the Tx FIFO.
 *
 * @return     none
 *
 */
void I2C_TxCmdBlock(I2C_Id_t i2cNo, ControlState_t newState)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);

    I2Cx->I2C_CONFIG0.MASTER_BLK_TXFIFO = (uint32_t)newState;
}

/**
 * @brief      Enable/Disable transfer abort.
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  newState: Enable/Disable function state.
 *             - ENABLE: ABORT operation in progress.
 *             - DISABLE: ABORT not initiated or ABORT done.
 *
 * @return     none
 *
 */
void I2C_TxAbortCmd(I2C_Id_t i2cNo, ControlState_t newState)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);

    I2Cx->I2C_CONFIG0.MASTER_ABORT = (uint32_t)newState;
}

/**
 * @brief      Configure the FIFO threshold level.
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  fifoConfig: Pointer to FIFO type structure.
 *
 * @return     none
 *
 */
void I2C_FIFOConfig(I2C_Id_t i2cNo, const I2C_FifoConfig_t* fifoConfig)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);

    /* Set Receive FIFO threshold level */
    I2Cx->I2C_RXFIFO_WATER_MARK.RXFIFO_WATER_MARK = fifoConfig->recvFifoThr;
    /* Set Transmit FIFO threshold level */
    I2Cx->I2C_TXFIFO_WATER_MARK.TXFIFO_WATER_MARK = fifoConfig->transmitFifoThr;
}

/**
 * @brief      Get transmit FIFO level
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 *
 * @return     The number of valid data entries in the transmit FIFO memory.
 *
 */
uint32_t I2C_GetTxFifoLevel(I2C_Id_t i2cNo)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);

    return (I2Cx->I2C_TX_FIFO_CNT.TX_FIFO_CNT);
}

/**
 * @brief      Get receive FIFO level
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 *
 * @return     The number of valid data entries in the receive FIFO memory.
 *
 */
uint32_t I2C_GetRxFifoLevel(I2C_Id_t i2cNo)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);

    return (I2Cx->I2C_RX_FIFO_CNT.RX_FIFO_CNT);
}

/**
 * @brief      I2C master selects transfer address function.
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  transAddrType:transfer address types
 *             - I2C_DEST_ADDR
 *             - I2C_GEN_CALL_ADDR
 *             - I2C_START_BYTE
 *
 * @return     none
 *
 */
void I2C_MstCmdSelect(I2C_Id_t i2cNo, I2C_MstCmdSelect_t transAddrType)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);

    I2Cx->I2C_DEST_ADDR.MASTER_CMD_SEL = (uint32_t)transAddrType;
}

/**
 * @brief      Enable/disable I2C general call ack function.
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  newState: Enable/Disable function state.
 *           - ENABLE: I2C responses with a ACK when it receives a general call.
 *           - DISABLE: No ACK the general call and doesn't generate general
 *                      call interrupt.
 *
 * @return     none
 *
 */
void I2C_GeneralCallAckCmd(I2C_Id_t i2cNo, ControlState_t newState)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);

    /* Set general call ACK function */
    I2Cx->I2C_CONFIG0.SLAVE_ACK_GENCALL = (uint32_t)newState;
}

/**
 * @brief      Generate a NACK for the data part of a transfer when i2c is
 *             acting as a slave receiver
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  genNack: general call ACK/NACK type.
 *         - I2C_GEN_NACK_AFTER_RCV:I2C generates NACK after data byte received.
 *         - I2C_GEN_NACK_OR_ACK_NORMAL:I2C generates NACK/ACK normally.
 *
 * @return     none
 *
 */
void I2C_SlvDataNackGen(I2C_Id_t i2cNo, I2C_GenSlvDataNack_t genNack)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);

    /* Generate a NACK for the data part of a transfer */
    I2Cx->I2C_CONFIG0.SLAVE_NACK = (uint32_t)genNack;
}

/**
 * @brief      Send one byte when i2c as a master.
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  restartStopType: Specified restart,Stop type.
 *             - I2C_RESTART_AND_STOP_DISABLE
 *             - I2C_STOP_EN
 *             - I2C_RESTART_EN
 * @param[in]  data: The data to be send.
 *
 * @return     none
 *
 */
void I2C_MasterSendByte(I2C_Id_t i2cNo, I2C_RestartStop_t restartStopType,
                        uint8_t data)
{
    i2c_reg_w_t * I2Cxw = (i2c_reg_w_t *)(i2cRegWPtr[i2cNo]);

    /* Send one byte */
    I2Cxw->I2C_COMMAND_DATA = ((uint32_t)(restartStopType) << 0x9UL) |
         (((uint32_t)data));
}

/**
 * @brief      Send one byte when i2c as a slave.
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 *
 * @param[in]  data: The data to be send.
 *
 * @return     none
 *
 */
void I2C_SlaveSendByte(I2C_Id_t i2cNo, uint8_t data)
{
    i2c_reg_w_t * I2Cxw = (i2c_reg_w_t *)(i2cRegWPtr[i2cNo]);

    /* Send one byte */
    I2Cxw->I2C_COMMAND_DATA = ((uint32_t)data);
}

/**
 * @brief     Master read/write request.
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  restartStopType: Specified restart,Stop type.
 *             - I2C_RESTART_AND_STOP_DISABLE
 *             - I2C_STOP_EN
 *             - I2C_RESTART_EN
 *
 * @return     none
 *
 */
void I2C_MasterReadCmd(I2C_Id_t i2cNo, I2C_RestartStop_t restartStopType)
{
    i2c_reg_w_t * I2Cxw = (i2c_reg_w_t *)(i2cRegWPtr[i2cNo]);

    /* Set read command */
    I2Cxw->I2C_COMMAND_DATA = 
                            ((uint32_t)(restartStopType) << 0x9UL) | (0x100UL);
}

/**
 * @brief     I2C read one byte .
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 *
 * @return     The received data
 *
 */
uint16_t I2C_ReceiveByte(I2C_Id_t i2cNo)
{
    i2c_reg_w_t * I2Cxw = (i2c_reg_w_t *)(i2cRegWPtr[i2cNo]);

    /* Read one byte */
    return ((uint16_t)(I2Cxw->I2C_COMMAND_DATA & 0xFFUL));
}

/**
 * @brief      Set sda setup time when i2c is acting as a slave transmitter.
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  length: The length of setup time is calculated using
 *                     [(SDA_SETUP_TIMING - 1) * (i2c function clock period)].
 *
 * @return     none
 *
 */
void I2C_SetSdaSetupTime(I2C_Id_t i2cNo, uint8_t length)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);

    /* SDA setup time */
    I2Cx->I2C_SDA_SETUP_TIMING.SDA_SETUP_TIMING = ((uint32_t)length);
}

/**
 * @brief      Enable/Disable specified interrupt type
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  intType:  Specified interrupt type.
 *             - I2C_INT_GEN_CALL
 *             - I2C_INT_TX_OVER
 *             - I2C_INT_ERROR_ABORT
 *             - I2C_INT_ACTIVITY
 *             - I2C_INT_STOP_DET
 *             - I2C_INT_START_DET
 *             - I2C_INT_RD_REQ
 *             - I2C_INT_RX_DONE
 *             - I2C_INT_RX_UNDER
 *             - I2C_INT_RX_OVER
 *             - I2C_INT_RESTART_DET
 *             - I2C_SCL_STUCK_AT_LOW
 *             - I2C_INT_RX_FULL
 *             - I2C_INT_TX_EMPTY
 *             - I2C_INT_ALL
 *
 * @param[in]  newState:  Interrupt enable/disable type.
 *             - ENABLE: enable interrupt
 *             - DISABLE: disable interrupt
 *
 * @return     none
 *
 */
void I2C_IntCmd(I2C_Id_t i2cNo, I2C_Int_t intType, ControlState_t newState)
{
    i2c_reg_w_t * I2Cxw = (i2c_reg_w_t *)(i2cRegWPtr[i2cNo]);

    if(DISABLE == newState )
    {
        I2Cxw->I2C_INT_ENABLE &= (~I2C_IntEnableTable[intType]);
    }
    else
    {
        I2Cxw->I2C_INT_ENABLE |= I2C_IntEnableTable[intType];
    }
}

/**
 * @brief      Check whether interrupt status flag is set or not for given
 *             interrupt type
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  intType:  Specified interrupt type.
 *             - I2C_INT_GEN_CALL
 *             - I2C_INT_TX_OVER
 *             - I2C_INT_ERROR_ABORT
 *             - I2C_INT_ACTIVITY
 *             - I2C_INT_STOP_DET
 *             - I2C_INT_START_DET
 *             - I2C_INT_RD_REQ
 *             - I2C_INT_RX_DONE
 *             - I2C_INT_RX_UNDER
 *             - I2C_INT_RX_OVER
 *             - I2C_INT_RESTART_DET
 *             - I2C_SCL_STUCK_AT_LOW
 *             - I2C_INT_RX_FULL
 *             - I2C_INT_TX_EMPTY
 *
 * @return     The status flag of interrupt status register.
 *             - SET
 *             - RESET
 *
 */
FlagStatus_t I2C_GetIntStatus(I2C_Id_t i2cNo, I2C_Int_t intType)
{
    uint32_t intBitStatus;
    i2c_reg_w_t * I2Cxw = (i2c_reg_w_t *)(i2cRegWPtr[i2cNo]);
    intBitStatus = (((I2Cxw->I2C_STATUS0) &
                    (0x01UL << (uint32_t)I2C_IntTable[intType])) >>
                    (uint32_t)I2C_IntTable[intType]);

    return (FlagStatus_t)intBitStatus;
}

/**
 * @brief      Check whether error status flag is set or not
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  errorType:  Specified abort type.
 *             - I2C_ERR_GEN_CALL_NO_ACK
 *             - I2C_ERR_GEN_CALL_READ
 *             - I2C_ERR_START_BYTE_ACK_DET
 *             - I2C_ERR_SBYTE_NORSTRT
 *             - I2C_ERR_H_NO_RSTRT
 *             - I2C_ERR_H_MCODE_ACK_DET
 *             - I2C_ERR_7BIT_ADDR_NO_ACK
 *             - I2C_ERR_10BIT_ADDR1_NO_ACK
 *             - I2C_ERR_10BIT_ADDR2_NO_ACK
 *             - I2C_ERR_10BIT_READ_NO_RSTRT
 *             - I2C_ERR_DATA_NO_ACK
 *             - I2C_ERR_MASTER_LOST
 *             - I2C_ERR_MASTER_DIS
 *             - I2C_ERR_SLAVE_ARBLOST
 *             - I2C_ERR_MASTER_ABRT         
 *             - I2C_ERR_SLAVE_READ_REQ
 *             - I2C_ERR_SLAVE_FLUSH_TXFIFO
 *             - I2C_ERR_SDA_LOW_TIMEOUT
 *
 * @return     The status flag of error status register.
 *             - SET
 *             - RESET
 *
 */
FlagStatus_t I2C_GetErrorStatus(I2C_Id_t i2cNo, I2C_ErrorStatus_t errorType)
{
    uint32_t bitStatus;
    i2c_reg_w_t * I2Cxw = (i2c_reg_w_t *)(i2cRegWPtr[i2cNo]);
    bitStatus = (((I2Cxw->I2C_ERROR_STATUS) &
                        (0x01UL <<(uint32_t)errorType)) >> (uint32_t)errorType);
    return (FlagStatus_t)bitStatus;
}

/**
 * @brief      Clear specified interrupt type
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  intType:  Specified interrupt type.
 *             - I2C_INT_GEN_CALL
 *             - I2C_INT_TX_OVER
 *             - I2C_INT_ERROR_ABORT
 *             - I2C_INT_ACTIVITY
 *             - I2C_INT_STOP_DET
 *             - I2C_INT_START_DET
 *             - I2C_INT_RD_REQ
 *             - I2C_INT_RX_DONE
 *             - I2C_INT_RX_UNDER
 *             - I2C_INT_RX_OVER
 *             - I2C_INT_RESTART_DET
 *             - I2C_SCL_STUCK_AT_LOW
 *             - I2C_INT_ALL
 *
 * @return     none
 *
 */
void I2C_ClearInt(I2C_Id_t i2cNo, I2C_Int_t intType)
{
    i2c_reg_w_t * I2Cxw = (i2c_reg_w_t *)(i2cRegWPtr[i2cNo]);

    I2Cxw->I2C_STATUS0 = I2C_IntEnableTable[intType];
}

/**
 * @brief     Clear all error status .
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 *
 * @return none
 *
 */
void I2C_ClearErrorStatusAll(I2C_Id_t i2cNo)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);

    volatile uint32_t dummyData;
    /* Dummy read to clear all error status */
    dummyData = I2Cx->I2C_RD_CLR_ERR_STATUS.CLR_ERR;
}

/**
 * @brief     The number of Tx FIFO data Master-Transmitter commands that
 *            are flushed due to ERROR_ABORT or SlaveTransmitter interrupt.
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 *
 * @return     The error flush count.
 *
 */
uint32_t I2C_ErrorFlushCount(I2C_Id_t i2cNo)
{
    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);

    return I2Cx->I2C_ERROR_STATUS.ERR_TXFIFO_FLUSH_CNT;
}

/**
 * @brief      Check whether status flag is set or not for given status type
 *
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  statusType:  Specified status type.
 *             - I2C_MST_ACTIVITY
 *             - I2C_SLV_ACTIVITY
 *             - I2C_TXFIFO_EMPTY_MASTER_HOLD
 *             - I2C_TXFIFO_EMPTY_SLAVE_HOLD
 *             - I2C_RXFIFO_FULL_MASTER_HOLD
 *             - I2C_RXFIFO_FULL_SLAVE_HOLD
 *             - I2C_STATUS_TFNF
 *             - I2C_STATUS_TFE,
 *             - I2C_STATUS_RFNE,
 *             - I2C_STATUS_RFF,
 *             - I2C_SDA_ERR_RECOVER_STUCK_LOW,
 *             - I2C_SLAVE_IS_DISABLED_UNDER_ACT
 *             - I2C_SLAVE_RX_DATA_DISCARD
 *             - I2C_ENABLE
 *
 * @return     The status flag of I2C status register.
 *             - SET
 *             - RESET
 *
 */
FlagStatus_t I2C_GetStatus(I2C_Id_t i2cNo, I2C_Status_t statusType)
{
    uint32_t bitStatus;
    i2c_reg_w_t * I2Cxw = (i2c_reg_w_t *)(i2cRegWPtr[i2cNo]);
    bitStatus = (((I2Cxw->I2C_STATUS1) &
                     (0x01UL << (uint32_t)statusType)) >> (uint32_t)statusType);
    return (FlagStatus_t)bitStatus;
}

/**
 * @brief      Configure speed mode and SCL timing. This function is to configure speed mode and
 *             custom data transfer rate and duty cycle with any clock source supported.
 *             This function need to be called after I2C_Init().
 * 
 * @param[in]  i2cNo: Select the I2C port, should be I2C0_ID, I2C1_ID.
 * @param[in]  sclTimingConfig: Pointer to a SCL timing configuration structure.
 * 
 * @return     SUCC: The SCL timing configuration is successfully configured.
 *             ERR:  The SCL timing configuration is configured while I2C is enabled or speed mode
 *                   is invalid.
 */
ResultStatus_t I2C_ConfigSclTiming(I2C_Id_t i2cNo, I2C_SclTiming_t * sclTimingConfig)
{
    uint32_t i2cEnableBit = 0U;
    ResultStatus_t returnValue = SUCC;

    i2c_reg_t * I2Cx = (i2c_reg_t *)(i2cRegPtr[i2cNo]);
    i2cEnableBit = I2Cx->I2C_CONFIG0.MODULE_EN;
    if (0U == i2cEnableBit)
    {
        /* Set the I2C speed mode */
        I2Cx->I2C_CONFIG1.SPEED_SEL = ((uint32_t)(sclTimingConfig->speedMode))&0x3U;
        switch(sclTimingConfig->speedMode)
        {
            case I2C_SPEED_STANDARD:
                I2Cx->I2C_STD_SCL_HCNT.STD_SCL_HCNT = sclTimingConfig->i2cSclHighCount;
                I2Cx->I2C_STD_SCL_LCNT.STD_SCL_LCNT = sclTimingConfig->i2cSclLowCount;
                I2Cx->I2C_FSTD_SPKCNT.FSTD_SPKLEN = sclTimingConfig->i2cSpikeLengthCount;
                break;

            case I2C_SPEED_FAST:
            case I2C_SPEED_FAST_PLUS:
                I2Cx->I2C_FST_SCL_HCNT.FST_SCL_HCNT = sclTimingConfig->i2cSclHighCount;
                I2Cx->I2C_FST_SCL_LCNT.FST_SCL_LCNT = sclTimingConfig->i2cSclLowCount;
                I2Cx->I2C_FSTD_SPKCNT.FSTD_SPKLEN = sclTimingConfig->i2cSpikeLengthCount;
                break;

            case I2C_SPEED_HIGH:
                I2Cx->I2C_HS_SCL_HCNT.HS_SCL_HCNT = sclTimingConfig->i2cSclHighCount;
                I2Cx->I2C_HS_SCL_LCNT.HS_SCL_LCNT = sclTimingConfig->i2cSclLowCount;
                I2Cx->I2C_HS_SPKCNT.HS_SPKLEN = sclTimingConfig->i2cSpikeLengthCount;
                break;

            default:
                returnValue = ERR;
                break;
        }
    }
    else
    {
        returnValue = ERR;
    }
    return returnValue;
}                                  
/** @} end of group I2C_Public_Functions */

/** @} end of group I2C_definitions */

/** @} end of group Z20K14XM_Peripheral_Driver */
