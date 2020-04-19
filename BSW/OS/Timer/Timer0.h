/**
 * @file  Timer0.h 
 * @brief This file is to be used as an implementation for the user of Timer 0 driver.
 *
 * @author Mark Attia
 * @date January 22, 2020
 *
 */

#ifndef TIMER0_H
#define TIMER0_H

#define TMR0_PRESCALER_CLR		0xF8

#define TMR0_DIV_1				0x01
#define TMR0_DIV_8				0x02
#define TMR0_DIV_64				0x03
#define TMR0_DIV_256			0x04
#define TMR0_DIV_1024			0x05


/**
 * Function:  Timer0_InterruptEnable 
 * --------------------
 *  @brief Enables the interrupt for the Timer0
 *
 *  
 *  returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Timer0_InterruptEnable(void);

/**
 * Function:  Timer0_InterruptDisable 
 * --------------------
 *  @brief Disables the interrupt for the Timer0
 *
 *  
 *  returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Timer0_InterruptDisable(void);

/**
 * Function:  Timer0_Start 
 * --------------------
 *  @brief Enables the Timer0 timer
 *  
 *  @param prescaler: the division value for system clock
 *					@arg TMR0_DIV_1
 *					@arg TMR0_DIV_8
 *     				@arg TMR0_DIV_64
 *     				@arg TMR0_DIV_256
 *					@arg TMR0_DIV_1024
 *  returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Timer0_Start(uint8_t prescaler);

/**
 * Function:  Timer0_SetTimeUS 
 * --------------------
 *  @brief Sets The reload time for timer 0
 *
 *  @param timerClock: The Timer clock frequency
 *  @param timeUS: The time in Micro seconds
 *  
 *  returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Timer0_SetTimeUS(f64 timerClock, uint32_t timeUS);

/**
 * Function:  Timer0_Stop 
 * --------------------
 *  @brief Disables the Timer0 timer
 *
 *  
 *  returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Timer0_Stop(void);

/**
 * Function:  Timer0_GetValue 
 * --------------------
 *  @brief Reads the current value inside the Timer0 timer
 *
 *  @param val: a pointer to return data in
 *  
 *  returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Timer0_GetValue(uint32_t* val);

/**
 * Function:  Timer0_SetCallBack 
 * --------------------
 *  @brief Sets the callback function for the Timer0
 *
 *  @param func: the callback function
 *  
 *  returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Timer0_SetCallBack(callback_t func);

/**
 * Function:  Timer0_ClearValue 
 * --------------------
 *  @brief Clears the value of the counter
 *  
 *  returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
extern Std_ReturnType Timer0_ClearValue(void);


#endif