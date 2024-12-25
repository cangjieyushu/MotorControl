/**************************************************************************************************/
/**
 * @file      : Gpio_Drv.c
 * @brief     : GPIO module driver file.
 *              - Platform: Z20M1343L
 * @version   : 0.1.0
 * @date      : May-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2023-2024 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/

#include "Gpio_Drv.h"

/** @defgroup Private_MacroDefinition
 *  @{
 */
#define PINS_TOTAL_NUM                (16U)
#define PORT_PCR_ALL_MASK             (0x9F8F8F3BU)         /*!< PCR register for all functions */
/** @} end of Private_MacroDefinition */

/** @defgroup Private_TypeDefinition
 *  @{
 */

/** @} end of group Private_TypeDefinition */

/** @defgroup Global_VariableDefinition
 *  @{
 */

 /** @} end of group Global_VariableDefinition */

/** @defgroup Private_VariableDefinition
 *  @{
 */
/**
 *  @brief PORT ISR callback function pointer array
 */
static Port_CallbackType  PortIsrCbFun = NULL_PTR;
 /**
 *  @brief PORTA address pointer
 */
/*PRQA S 0303 ++*/
static Reg_Port_WType   *const Port_RegWPtr = (Reg_Port_WType *) PORTA_BASE_ADDR;
static Reg_Port_BfType  *const Port_RegBfPtr  = (Reg_Port_BfType *) PORTA_BASE_ADDR;
/*PRQA S 0303 --*/

/**
 *  @brief GPIOA address pointer
 */
/*PRQA S 0303 ++*/
static Reg_Gpio_WType   *const Gpio_RegWPtr = (Reg_Gpio_WType *) GPIOA_BASE_ADDR;
static Reg_Gpio_BfType  *const Gpio_RegBfPtr  = (Reg_Gpio_BfType *) GPIOA_BASE_ADDR;
/*PRQA S 0303 --*/

/** @} end of group Private_VariableDefinition */

/** @defgroup Private_FunctionDeclaration
 *  @{
 */
void PortA_DriverIrqHandler(void);
 /** @} end of group Private_FunctionDeclaration */

/** @defgroup Private_FunctionDefinition
 *  @{
 */
/**
 * @brief    PORTA interrupt handle.
 *
 * @param[in]  none.
 * @return     none.
 *
 */
void PortA_DriverIrqHandler(void)
{
    uint32 Status = 0U;
    uint32 GpioNum = 0U;
    Status = Port_RegBfPtr->PORTA_IRQFLG.ISF;
    
    for(GpioNum = (uint32)GPIO_0; GpioNum < (uint32)PINS_TOTAL_NUM; GpioNum++)
    {
        if((Status & (0x01UL<<GpioNum))!= 0U)
        {
            if(PortIsrCbFun!= NULL_PTR)
            {
                PortIsrCbFun((Port_GpioNumType)GpioNum);
            }
            else
            {
                Port_RegWPtr->PORTA_PCR[GpioNum] = 0x5B000000U;
                Port_RegBfPtr->PORTA_PCR[GpioNum].IRQC = 0U;
                Port_RegBfPtr->PORTA_PCR[GpioNum].LK = 1U;
            }   
        } 
        Port_RegBfPtr->PORTA_IRQFLG.ISF = Status & (0x01UL<<GpioNum); 
    }
}

/** @} end of group Private_FunctionDefinition */



/** @defgroup Public_FunctionDefinition
 *  @{
 */

/**
 * @brief        Configure pins with the same global configuration
 * If a pin is locked, global control will not work on it
 *
 * @param[in]    Pins: Select the GPIO pins.
 * @param[in]    Value: Set GPIO pin global value.
 *
 * @return none.
 *
 */
void Port_ConfigGlobalPins(uint32 Pins, uint32 Value)
{
    uint32 Mask = 0U;
    
    Mask = Value & PORT_PCR_ALL_MASK;
    
    Port_RegWPtr->PORTA_GLBDAT = Mask;
    Port_RegWPtr->PORTA_GLBCTL = Pins;
}
/**
 * @brief        Lock or unlock PCR register.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 * @param[in]    LockCtrl: COMMON_DISABLE or COMMON_ENABLE.
 *
 * @return none.
 *
 */
void Port_LockPin(Port_GpioNumType GpioNum, Common_ControlStateType LockCtrl)
{ 
    if(COMMON_DISABLE == LockCtrl)
    {
        Port_RegWPtr->PORTA_PCR[GpioNum] = 0x5B000000U;
    }
    else
    {
        Port_RegBfPtr->PORTA_PCR[GpioNum].LK = 1U;
    }
}

/**
 * @brief        Initialize seleted pin with the given configuration structure.
 *
 * This function configures the pins with the options provided in the
 * provided structure.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 * @param[in]    ConfigPtr: Pin configuration struct.
 *
 * @return none.
 *
 */
void Port_InitPin(Port_GpioNumType GpioNum, const Port_PinConfigType* ConfigPtr)
{ 
    if(1U == Port_RegBfPtr->PORTA_PCR[GpioNum].LK)
    {
        Port_RegWPtr->PORTA_PCR[GpioNum] = 0x5B000000U;
    }
    Port_RegBfPtr->PORTA_PCR[GpioNum].PS = ((uint32)(ConfigPtr->PullConfig))&0x01U;
    Port_RegBfPtr->PORTA_PCR[GpioNum].PE = (((uint32)(ConfigPtr->PullConfig))&0x02U)>>1U;
    Port_RegBfPtr->PORTA_PCR[GpioNum].SRE = (uint32)(ConfigPtr->SlewRateConfig);
    Port_RegBfPtr->PORTA_PCR[GpioNum].ODE = (uint32)(ConfigPtr->OpenDrainConfig);
    Port_RegBfPtr->PORTA_PCR[GpioNum].FLTEN = (uint32)(ConfigPtr->FilterEnable);
    Port_RegBfPtr->PORTA_PCR[GpioNum].FLT = (uint32)(ConfigPtr->FilterConfig);
    Port_RegBfPtr->PORTA_PCR[GpioNum].LK = 1U;
}

/**
 * @brief        Configure the pin mux function
 *
 * This function configures the pin muxing.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 * @param[in]    PinMuxFunc: Pin mux function.
 *
 * @return none.
 *
 */
void Port_ConfigPinmux(Port_GpioNumType GpioNum, Port_PinMuxFuncType PinMuxFunc)
{ 
    if(1U == Port_RegBfPtr->PORTA_PCR[GpioNum].LK)
    {
        Port_RegWPtr->PORTA_PCR[GpioNum] = 0x5B000000U;
    }
    Port_RegBfPtr->PORTA_PCR[GpioNum].MUX = (uint32)PinMuxFunc;
    Port_RegBfPtr->PORTA_PCR[GpioNum].LK = 1U;
}

/**
 * @brief        Configure the pin interrupt configuration
 *
 * This function configures the pin interrupt.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 * @param[in]    IntConfig: Pin interrupt configuration.
 *                         - PORT_ISF_DISABLED(0)
 *                         - PORT_ISF_INT_LOGIC_0(8)
 *                         - PORT_ISF_INT_RISING_EDGE(9)
 *                         - PORT_ISF_INT_FALLING_EDGE(10)
 *                         - PORT_ISF_INT_BOTH_EDGE(11)
 *                         - PORT_ISF_INT_LOGIC_1(12)
 *
 * @return none.
 *
 */
void Port_ConfigPinInt(Port_GpioNumType GpioNum, Port_IntConfigType IntConfig)
{
    if(1U == Port_RegBfPtr->PORTA_PCR[GpioNum].LK)
    {
        Port_RegWPtr->PORTA_PCR[GpioNum] = 0x5B000000U;
    }
    Port_RegBfPtr->PORTA_PCR[GpioNum].IRQC = (uint32)IntConfig;
    Port_RegBfPtr->PORTA_PCR[GpioNum].LK = 1U;
}

/**
 * @brief        Configure the pin pull configuration.
 *
 * This function configures the pin interrupt.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 * @param[in]    PullConfig: Pin pull configuration, should be PORT_PULL_NONE, PORT_PULL_DOWN and
 *                           PORT_PULL_UP.
 *
 * @return none.
 *
 */
void Port_ConfigPull(Port_GpioNumType GpioNum, Port_PullType PullConfig)
{
    if(1U == Port_RegBfPtr->PORTA_PCR[GpioNum].LK)
    {
        Port_RegWPtr->PORTA_PCR[GpioNum] = 0x5B000000U;
    }
    Port_RegBfPtr->PORTA_PCR[GpioNum].PS = (uint32)PullConfig & 0x01U;
    Port_RegBfPtr->PORTA_PCR[GpioNum].PE = ((uint32)PullConfig & 0x02UL)>>1UL;
    Port_RegBfPtr->PORTA_PCR[GpioNum].LK = 1U;
}

/**
 * @brief        Configure the pin slew rate configuration.
 *
 * This function configures the pin slew rate.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 * @param[in]    SlewRateCtrl: Pin slew rate configuration, should be PORT_FAST_RATE and 
 *                             PORT_SLOW_RATE.
 *
 * @return none.
 *
 */
void Port_ConfigSlewRate(Port_GpioNumType GpioNum,
                         Port_SlewRateType SlewRateCtrl)
{
    if(1U == Port_RegBfPtr->PORTA_PCR[GpioNum].LK)
    {
        Port_RegWPtr->PORTA_PCR[GpioNum] = 0x5B000000U;
    }
    Port_RegBfPtr->PORTA_PCR[GpioNum].SRE = (uint32)SlewRateCtrl;
    Port_RegBfPtr->PORTA_PCR[GpioNum].LK = 1U;
}

/**
 * @brief        Enable or disable the pin open drain mode.
 *
 * This function configures the pin open drain.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 * @param[in]    OpenDrainCtrl: Pin open drain configuration, should be COMMON_DISABLE and 
 *                              COMMON_ENABLE 
 *                             
 *
 * @return none.
 *
 */
void Port_EnableOpenDrainMode(Port_GpioNumType GpioNum,
                         Common_ControlStateType OpenDrainCtrl)
{
    if(1U == Port_RegBfPtr->PORTA_PCR[GpioNum].LK)
    {
        Port_RegWPtr->PORTA_PCR[GpioNum] = 0x5B000000U;
    }
    Port_RegBfPtr->PORTA_PCR[GpioNum].ODE = (uint32)OpenDrainCtrl;
    Port_RegBfPtr->PORTA_PCR[GpioNum].LK = 1U;
}

/**
 * @brief        Configure the pin filter configuration.
 *
 * This function configures the pin filter.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 * @param[in]    FilterValue: Pin filter configuration, the value is 0x0 - 0x1F.
 *
 * @return none.
 *
 */
void Port_ConfigFilter(Port_GpioNumType GpioNum, uint8 FilterValue)
{
    if(1U == Port_RegBfPtr->PORTA_PCR[GpioNum].LK)
    {
        Port_RegWPtr->PORTA_PCR[GpioNum] = 0x5B000000U;
    }
    Port_RegBfPtr->PORTA_PCR[GpioNum].FLT = (uint32)FilterValue;
    Port_RegBfPtr->PORTA_PCR[GpioNum].LK = 1U;
}

/**
 * @brief        Enable/Disable the pin filter .
 *
 * This function enables/disables the pin filter.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 * @param[in]    FilterCtrl: Pin filter configuration, 
                             should be COMMON_DISABLE or COMMON_ENABLE.
 *
 * @return none.
 *
 */
void Port_EnableFilter(Port_GpioNumType GpioNum,
                       Common_ControlStateType FilterCtrl)
{
    if(1U == Port_RegBfPtr->PORTA_PCR[GpioNum].LK)
    {
        Port_RegWPtr->PORTA_PCR[GpioNum] = 0x5B000000U;
    }
    Port_RegBfPtr->PORTA_PCR[GpioNum].FLTEN = (uint32)FilterCtrl;
    Port_RegBfPtr->PORTA_PCR[GpioNum].LK = 1U;
}

/**
 * @brief        Get pin interrupt status function
 *
 * This function gets the pin interrupt status.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 * 
 * @return       Interrupt status of a pin.
 *
 */
Common_FlagStatusType Port_GetIntStatus(Port_GpioNumType GpioNum)
{
    return ((Common_FlagStatusType)Port_RegBfPtr->PORTA_PCR[GpioNum].ISF);
}

/**
 * @brief        Get all pins interrupt status of a Port.
 *
 * This function gets all pins interrupt status.
 *
 * @return     All Pins interrupt status of a Port.
 *
 */
uint32 Port_GetAllPinsIntStatus(void)
{
    return ((uint32)Port_RegWPtr->PORTA_IRQFLG);
}

/**
 * @brief        Clear the pin interrupt status function.
 *
 * This function clears interrupt status of a pin.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 *
 * @return       none.
 *
 */
void Port_ClearPinInt(Port_GpioNumType GpioNum)
{
    if(1U == Port_RegBfPtr->PORTA_PCR[GpioNum].LK)
    {
        Port_RegWPtr->PORTA_PCR[GpioNum] = 0x5B000000U;
    }
    Port_RegBfPtr->PORTA_PCR[GpioNum].ISF = 0x01U;
    Port_RegBfPtr->PORTA_PCR[GpioNum].LK = 1U;
}

/**
 * @brief        Clear All Pins Interrupt  Status Function
 *
 * @param[in]    ClrPins: Select pins no, a bit is a pin, bit0-gpio0,...
 *
 * @return       none.
 *
 */
void Port_ClearPinsInt(uint32 ClrPins)
{
    Port_RegWPtr->PORTA_IRQFLG = ClrPins;
}

/**
 * @brief        Port install call back function
 *
 * @param[in]    CbFun: pointer to callback function.
 *
 * @return none
 *
 */
void Port_InstallCallbackFunc(Port_CallbackType CbFun)
{
    PortIsrCbFun = CbFun;
}

/**
 * @brief        Set the pin direction configuration.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 * @param[in]    Direction: Select  I/O direction of a pin.
 *                          - 0: corresponding pin is set to input
 *                          - 1: corresponding pin is set to output
 *
 * @return none.
 *
 */
void Gpio_SetPinDir(Port_GpioNumType GpioNum, Gpio_DirType Direction)
{
    uint32 PinDir = Gpio_RegWPtr->GPIOA_PDDR;
    PinDir &= (~(0x01UL << (uint32)GpioNum));
    PinDir |= ((uint32)Direction << (uint32)GpioNum);
    Gpio_RegWPtr->GPIOA_PDDR = PinDir;
}

/**
 * @brief        Set the direction configuration for all pins.
 *
 * @param[in]    PinsDir: Select I/O directions.
 *                        - 0: corresponding pin is set to input
 *                        - 1: corresponding pin is set to output
 *
 * @return none.
 *
 */
void Gpio_SetPinsDir(uint32 PinsDir)
{
    Gpio_RegWPtr->GPIOA_PDDR = PinsDir;
}

/**
 * @brief        Write a pin with a given value.
 *
 * This function writes a pin with a given value.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 * @param[in]    Level: Pin value.
 *                    - 0: corresponding pin is set to LOW
 *                    - 1: corresponding pin is set to HIGH
 *
 * @return none.
 *
 */
void Gpio_WritePinOutput(Port_GpioNumType GpioNum, Gpio_LevelType Level)
{
    if(GPIO_LOW == Level)
    {
        Gpio_RegWPtr->GPIOA_PCOR = (0x01UL << (uint32)GpioNum);
    }
    else
    {
        Gpio_RegWPtr->GPIOA_PSOR = (0x01UL << (uint32)GpioNum);
    }
}

/**
 * @brief        Write  pins  with the given value.
 *
 * This function writes pins with the given value.
 *
 * @param[in]    Value: Pins value.
 *                    - 0: corresponding pin is set to LOW
 *                    - 1: corresponding pin is set to HIGH
 *
 * @return none.
 *
 */
void Gpio_WritePinsOutput(uint32 Value)
{
    Gpio_RegWPtr->GPIOA_PDOR = Value;
}

/**
 * @brief        Write a pin to 'Clear' value.
 *
 * This function writes a pin to 'Clear' value.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 *
 * @return none.
 *
 */
void Gpio_ClearPinOutput(Port_GpioNumType GpioNum)
{
    Gpio_RegWPtr->GPIOA_PCOR = (0x01UL << (uint32)GpioNum);
}

/**
 * @brief        Write pins to 'Clear' value
 *
 * This function writes pins to 'Clear' value.
 *
 * @param[in]    Pins: Clean the GPIO pins.
 *
 * @return none.
 *
 */
void Gpio_ClearPinsOutput(uint32 Pins)
{
    Gpio_RegBfPtr->GPIOA_PCOR.PCO = Pins;
}

/**
 * @brief        Write a pin with 'Set' value.
 *
 * This function writes a pin with 'Set' value.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 *
 * @return none.
 *
 */
void Gpio_SetPinOutput(Port_GpioNumType GpioNum)
{
    Gpio_RegWPtr->GPIOA_PSOR = (0x01UL << (uint32)GpioNum);
}

/**
 * @brief        Write  pins with 'Set' value.
 *
 * This function writes pins with 'Set' value.
 *
 * @param[in]    Pins: Set the GPIO pins.
 *
 * @return none.
 *
 */
void Gpio_SetPinsOutput(uint32 Pins)
{
    Gpio_RegWPtr->GPIOA_PSOR = Pins;
}

/**
 * @brief        Toggle a pin value.
 *
 * This function toggles a pin with 'Set' value.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 *
 * @return none.
 *
 */
void Gpio_TogglePinOutput(Port_GpioNumType GpioNum)
{
    Gpio_RegWPtr->GPIOA_PTOR = (0x01UL << (uint32)GpioNum);
}

/**
 * @brief        Toggle pins value.
 *
 * This function toggles pins with 'Set' value.
 *
 * @param[in]    Pins: Toggle the GPIO pins.
 *
 * @return none.
 *
 */
void Gpio_TogglePinsOutput(uint32 Pins)
{
    Gpio_RegWPtr->GPIOA_PTOR = Pins;
}

/**
 * @brief        Read a pin value.
 *
 * This function reads a pin value.
 *
 * @param[in]    GpioNum: Select the GPIO pin,such as GPIO_0~GPIO_15.
 *
 * @return       GPIO_HIGH or GPIO_LOW.
 *
 */
Gpio_LevelType Gpio_ReadPinLevel(Port_GpioNumType GpioNum)
{
    uint32 PinLevel = Gpio_RegWPtr->GPIOA_PDIR;
    PinLevel &= (0x01UL << (uint32)GpioNum);
    return ((PinLevel!=0U) ? GPIO_HIGH : GPIO_LOW);
}

/**
 * @brief        Read  pins value.
 *
 * @param[in]    None.
 *
 * @return       Pins value.
 *
 */
uint32 Gpio_ReadPinsLevel(void)
{
    return Gpio_RegBfPtr->GPIOA_PDIR.PDI;
}

/** @} end of group Public_FunctionDefinition */
