/**************************************************************************************************/
/**
 * @file     device_regs.h
 * @brief    Z20K14xM device file.
 * @version  V1.1.0
 * @date     December-2022
 * @author   Zhixin Semiconductor
 *
 * @note
 * Copyright (C) 2021-2024 Zhixin Semiconductor Ltd. All rights reserved.
 * 
 **************************************************************************************************/

#ifndef DEVICE_REGS_H
#define DEVICE_REGS_H

#if (defined(DEV_Z20K148M))
    #include "Z20K148M.h"
#elif (defined(DEV_Z20K146M))
    #include "Z20K146M.h"
#elif (defined(DEV_Z20K144M))
    #include "Z20K144M.h"
#else
    #error "No valid device defined!"
#endif

#endif /* DEVICE_REGS_H */
