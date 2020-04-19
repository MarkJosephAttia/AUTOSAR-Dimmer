/**
 * @file main.c
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief This is the main program that will run after the startup code
 * @version 0.1
 * @date 2020-04-07
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "Std_Types.h"
#include "Sched.h"

int main(void)
{
	Sched_Init();
	Sched_Start();
}