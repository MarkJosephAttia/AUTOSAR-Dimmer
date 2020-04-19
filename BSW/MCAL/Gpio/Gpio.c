/**
 * @file  Gpio.c 
 * @brief This file is to be used as an implementation of the GPIO driver.
 *
 * @author Mark Attia
 * @date February 6, 2020
 *
 */
#include "Std_Types.h"
#include "Gpio.h"

#define     GPIO_PIN                     0
#define     GPIO_DDR                     1
#define     GPIO_PORT                    2

/**
 * Function:  Gpio_InitPins 
 * --------------------
 *  @brief Initializes pins mode and speed for a specific port
 *
 *  @param gpio: An object of type gpio_t to set pins for
 *  
 *  
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Gpio_InitPins(gpio_t* gpio)
{
    Std_ReturnType err = E_NOT_OK;
    switch(gpio->mode)
    {
        case GPIO_MODE_OUTPUT_PP:
            *(uint8_t*)(gpio->port + GPIO_DDR) |= gpio->pins;
            err = E_OK;
            break;
        case GPIO_MODE_INPUT_FLOAT:
            *(uint8_t*)(gpio->port + GPIO_DDR) &= ~(gpio->pins);
            err = E_OK;
            break;
        case GPIO_MODE_INPUT_PULLUP:
            *(uint8_t*)(gpio->port + GPIO_PORT) |= gpio->pins;
            *(uint8_t*)(gpio->port + GPIO_DDR) &= ~(gpio->pins);
            err = E_OK;
            break;
    }
    return err;
}

/**
 * Function:  Gpio_WritePin 
 * --------------------
 *  @brief Write a value to a pin(0/1)
 *
 *  @param port: The port you want to configure
 *                 @arg GPIO_PORTX : The pin number you want to configure  
 * 
 *  @param pin: The pin you want to configure
 *                 @arg GPIO_PIN_X : The pin number you want to configure
 *                 //You can OR more than one pin\\
 *
 *  @param pinStatus: The status of the pins (GPIO_PIN_SET/GPIO_PIN_RESET)
 *                 @arg GPIO_PIN_SET : Sets the pin value to 1
 *                 @arg GPIO_PIN_RESET : Resets the pin value to 0
 *  
 *  @returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Gpio_WritePin(uint8_t port, uint8_t pin, uint8_t pinStatus)
{
    Std_ReturnType errorRet = E_NOT_OK;
    switch(pinStatus)
    {
        case GPIO_PIN_SET:
            *(uint8_t*)(port + GPIO_PORT) |= pin;
            errorRet = E_OK;
            break;
        case GPIO_PIN_RESET:
            *(uint8_t*)(port + GPIO_PORT) &= ~pin;
            errorRet = E_OK;
            break;
    }
    return errorRet;
}

/**
 * Function:  Gpio_ReadPin 
 * --------------------
 *  @brief Reads a value to a pin(0/1)
 *
 *  @param port: The port you want to read from
 *                 @arg GPIO_PORTX : The pin number you want to read from  
 * 
 *  @param pin: The pin you want to read
 *                 @arg GPIO_PIN_X : The pin number you want to read
 *                 //You can OR more than one pin\\
 *
 *  @param state: To return a status in
 *                  @arg GPIO_PIN_SET : The pin is set to 1
 *                  @arg GPIO_PIN_RESET : The pin is set to 0
 *  @returns: A status
 *              E_OK : if the function is executed correctly
 *              E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Gpio_ReadPin(uint8_t port, uint8_t pin, uint8_t* state)
{
    *state = !(*(uint8_t*)(GPIO_PIN + port) & pin);
    return E_OK;
}