/**
 * @file  Gpio.h 
 * @brief This file is to be used as an interface for the user of GPIO driver.
 *
 * @author Mark Attia
 * @date February 6, 2020
 *
 */

#ifndef GPIO_H
#define GPIO_H

typedef struct 
{
    uint8_t pins;
    uint8_t mode;
    uint8_t port;
} gpio_t;

#define GPIO_PIN_SET                    0
#define GPIO_PIN_RESET                  !GPIO_PIN_SET


#define GPIO_PIN_0                      0x01
#define GPIO_PIN_1                      0x02
#define GPIO_PIN_2                      0x04
#define GPIO_PIN_3                      0x08
#define GPIO_PIN_4                      0x10
#define GPIO_PIN_5                      0x20
#define GPIO_PIN_6                      0x40
#define GPIO_PIN_7                      0x80
#define GPIO_PIN_ALL                    0xFF

#define GPIO_MODE_OUTPUT_PP          0
#define GPIO_MODE_INPUT_PULLUP       1
#define GPIO_MODE_INPUT_FLOAT        2


#define GPIO_PORTA                      0x39
#define GPIO_PORTB                      0x36
#define GPIO_PORTC                      0x33
#define GPIO_PORTD                      0x30

/**
 * Function:  Gpio_InitPins 
 * --------------------
 *  @brief Initializes pins mode and speed for a specific port
 *
 *  @param gpio: An object of type gpio_t to set pins for
 *  
 *  
 *  returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Gpio_InitPins(gpio_t* gpio);

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
 *  returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Gpio_WritePin(uint8_t port, uint8_t pin, uint8_t pinStatus);

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
 *  returns: A status
 *              E_OK : if the function is executed correctly
 *              E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Gpio_ReadPin(uint8_t port, uint8_t pin, uint8_t* state);

#endif