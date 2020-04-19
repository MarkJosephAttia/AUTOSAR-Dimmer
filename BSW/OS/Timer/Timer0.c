/**
 * @file  Timer0.h 
 * @brief This file is to be used as an interface for the user of Timer 0 driver.
 *
 * @author Mark Attia
 * @date January 22, 2020
 *
 */
#include "Std_Types.h"
#include "Timer0.h"

#define TCCR0               *(volatile uint8_t*)(0x53)
#define TCNT0               *(volatile uint8_t*)(0x52)
#define TIMSK               *(volatile uint8_t*)(0x59)
#define OCR0                *(volatile uint8_t*)(0x5C)
#define SREG                *(volatile uint8_t*)(0x5F)

#define GLOBAL_INT_EN             0x80
#define TMR0_INT_EN               0x01
#define TMR0_INT_DIS              0xFE
#define TMR0_CMP_INT_EN           0x02
#define TMR0_CMP_INT_DIS          0xFD
#define TMR0_CLR_MODE			  0xB7
#define TMR0_CRC_MODE             0x08
#define TMR0_NORMAL_PORT_OP	      0xCF

void __vector_10 (void) __attribute__ ((signal, used, externally_visible));

callback_t Timer0_func = NULL;
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
Std_ReturnType Timer0_InterruptEnable(void)
{
    SREG |= GLOBAL_INT_EN;
    TIMSK |= TMR0_CMP_INT_EN;
    return E_OK;
}

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
Std_ReturnType Timer0_InterruptDisable(void)
{
    TIMSK &= TMR0_CMP_INT_DIS;
    return E_OK;
}

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
Std_ReturnType Timer0_Start(uint8_t prescaler)
{
	TCCR0 &= TMR0_PRESCALER_CLR & TMR0_NORMAL_PORT_OP;
    TCCR0 |= prescaler;
    TCNT0 = 0;
    TCCR0 &= TMR0_CLR_MODE;
    TCCR0 |= TMR0_CRC_MODE;
    return E_OK;
}

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
Std_ReturnType Timer0_Stop(void)
{
    TCCR0 &= TMR0_PRESCALER_CLR;
    return E_OK;
}

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
Std_ReturnType Timer0_GetValue(uint32_t* val)
{
    *val = (uint32_t)TCNT0;
    return E_OK;
}

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
Std_ReturnType Timer0_SetCallBack(callback_t func)
{
    Timer0_func = func;
    return E_OK;
}

/**
 * Function:  Timer0_ClearValue 
 * --------------------
 *  @brief Clears the value of the counter
 *  
 *  returns: A status
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType Timer0_ClearValue(void)
{
    TCNT0 = 0;
    return E_OK;
}

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
Std_ReturnType Timer0_SetTimeUS(f64 timerClock, uint32_t timeUS)
{
    f64 val;
    val = (f64)timerClock*(f64)timeUS/1000000.0;
    OCR0 = (uint8_t)val;
	return E_OK;
}
/**
 * @brief Timer 0 Interrupt Handler
 * 
 */
void __vector_10(void)
{
	
    if(Timer0_func)
    {
        Timer0_func();
    }
}