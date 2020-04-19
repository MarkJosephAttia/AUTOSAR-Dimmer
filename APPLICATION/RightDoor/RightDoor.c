/**
 * @file RightDoor.c
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief This is the implementation for the Right Door
 * @version 0.1
 * @date 2020-04-06
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "Std_Types.h"
#include "Sched.h"
#include "Rte.h"

/**
 * @brief This is a function that checks the status of the door and sets it in the RTE
 * 
 */
static void RightDoor_Runnable(void)
{
    uint8_t status;
    Rte_Call_RightDoorGetStatus(&status);
    Rte_Write_RightDoorStatus(status);
}

/**
 * @brief Initialise the right door application
 * 
 * @return Std_ReturnType 
 *              E_OK If the function executed successfully
 *              E_NOT_OK If the function executed successfully
 */
Std_ReturnType RightDoor_Init(void)
{
    Std_ReturnType error = Rte_SetRunnableEntity(RightDoor_Runnable, RTE_RIGHT_DOOR_RUNNABLE);
    return error;
}