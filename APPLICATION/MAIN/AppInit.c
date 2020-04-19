/**
 * @file HardwareInit.c
 * @author Mark Attia (you@domain.com)
 * @brief This is the implementation for the hardware initialisation task
 * @version 0.1
 * @date 2020-04-07
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "Std_Types.h"
#include "Led.h"
#include "Switch.h"
#include "Uart.h"
#include "Com.h"
#include "Sched.h"
#include "LeftDoor.h"
#include "RightDoor.h"
#include "DoorContact.h"
#include "Dimmer.h"
#include "Lighting.h"

static void App_Init(void)
{
	Switch_Init();
	Led_Init();
	Uart_Init(9600, UART_ONE_STOP_BIT, UART_EVEN_PARITY);
	Com_Init();
#ifdef FIRST_CONTROLLER_APP
	LeftDoor_Init();
	RightDoor_Init();
	DoorContact_Init();
#else
	Dimmer_Init();
	Lighting_Init();
#endif
	Sched_SuspendTask();
}

const task_t AppInit_task = {App_Init, 5};