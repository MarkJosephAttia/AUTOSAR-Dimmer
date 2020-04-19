/**
 * @file LeftDoor.c
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief This is the implementation for the Left Door
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
static void LeftDoor_Runnable(void)
{
    uint8_t status;
    Rte_Call_LeftDoorGetStatus(&status);
    Rte_Write_LeftDoorStatus(status);
}

/**
 * @brief Initialise the left door application
 * 
 * @return Std_ReturnType 
 *              E_OK If the function executed successfully
 *              E_NOT_OK If the function executed successfully
 */
Std_ReturnType LeftDoor_Init(void)
{
    Std_ReturnType error = Rte_SetRunnableEntity(LeftDoor_Runnable, RTE_LEFT_DOOR_RUNNABLE);
    return error;
}