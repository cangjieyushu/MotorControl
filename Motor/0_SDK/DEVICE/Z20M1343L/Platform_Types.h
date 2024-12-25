/**************************************************************************************************/
/**
 * @file      : Platform_Types.h
 * @brief     : Platform types definition
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/** @addtogroup Z20M1343L_Peripheral_Driver
 *  @{
 */

/** @defgroup Platform_Types
 *  @brief Platform types definition
 *  @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup Public_MacroDefinition
 *  @{
 */
#ifndef TRUE
    /* Boolean true value */
    #define TRUE 1U
#endif
#ifndef FALSE
    /* Boolean false value */
    #define FALSE 0U
#endif

/**
 * @brief Void pointer to zero definition.
 */
#define NULL_PTR ((void *)0)

/**
 * @brief IO type definition.
 */
#ifndef IO
#define   RO     volatile const       /*!< Read only permission */
#define   WO     volatile             /*!< Write only permission */
#define   RW     volatile             /*!< Read/Write permission */
#endif

/** @} end of Public_MacroDefinition */

/** @defgroup Public_TypeDefinition
 *  @{
 */

/**
 * @brief The standard type boolean shall be implemented as an unsigned integer with a bit
 *        length that is the shortest one natively supported by the platform (8 bits).
 */
typedef unsigned char boolean;

/**
 * @brief Unsigned 8 bit integer with range of 0 ..+255 (0x00..0xFF)
 */
typedef unsigned char uint8;

/**
 * @brief Unsigned 16 bit integer with range of 0 ..+65535 (0x0000..0xFFFF)
 */
typedef unsigned short uint16;

/**
 * @brief Unsigned 32 bit integer with range of 0 ..+4294967295 (0x00000000..0xFFFFFFFF)
 */
typedef unsigned int uint32;

/**
 * @brief Unsigned 64 bit integer with range of 0..18446744073709551615 (0x0000000000000000..
 *        0xFFFFFFFFFFFFFFFF)
 */
typedef unsigned long long uint64;

/**
 * @brief Signed 8 bit integer with range of -128 ..+127 (0x80..0x7F)
 */
typedef signed char sint8;

/**
 * @brief Signed 16 bit integer with range of -32768 ..+32767 (0x8000..0x7FFF)
 */
typedef signed short sint16;

/**
 * @brief Signed 32 bit integer with range of -2147483648.. +2147483647 (0x80000000..0x7FFFFFFF)
 */
typedef signed int sint32;

/**
 * @brief Signed 64 bit integer with range of -9223372036854775808..9223372036854775807
 *        (0x8000000000000000..0x7FFFFFFFFFFFFFFF )
 */
typedef signed long long sint64;

/**
 * @brief 32-bit floating point data type with range of -3.4028235e+38 ..+3.4028235e+38
 */
typedef float float32;

/**
 * @brief 64-bit floating point data type with range -1.7976931348623157e+308 ..
 *        +1.7976931348623157e+308
 */
typedef double float64;

/**
 * @brief a void pointer
 */
typedef void *VoidPtr;

/**
 * @brief a void pointer to const
 */
typedef const void *ConstVoidPtr;

/**
 *  @brief ISR callback function type
 */
typedef void (Isr_CbFuncType)(void);

/** @} end of group Public_TypeDefinition */

/** @defgroup Global_VariableDeclaration
 *  @{
 */

/** @} end of group Global_VariableDeclaration */

/** @defgroup Public_FunctionDeclaration
 *  @{
 */

/** @} end of group Public_FunctionDeclaration */

#ifdef __cplusplus
}
#endif

/** @} end of group Platform_Types */
/** @} end of group Platform_Types_Module */

#endif /* PLATFORM_TYPES_H */
