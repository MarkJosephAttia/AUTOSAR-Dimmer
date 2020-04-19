/**
 * @file Dimmer.c
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief This is the implementation for the dimmer application
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
 * @brief This is the runnable for the Dimmer
 * 
 */
static void Dimmer_Runnable(void)
{
    uint8_t data;
    Std_ReturnType error;
    Rte_Call_DimmerReceiveData();
    error = Rte_Read_DoorContact(&data);
    if(data == DOOR_CLOSED && error == E_OK)
    {
        Rte_Write_DimmerStatus(DIMMER_OFF);
    }
    else if(data == DOOR_OPEN && error == E_OK)
    {
        Rte_Write_DimmerStatus(DIMMER_ON);
    }
}

/**
 * @brief Initialise the dimmer application
 * 
 * @return Std_ReturnType 
 *              E_OK If the function executed successfully
 *              E_NOT_OK If the function executed successfully
 */
Std_ReturnType Dimmer_Init(void)
{
    Std_ReturnType error = Rte_SetRunnableEntity(Dimmer_Runnable, RTE_DIMMER_RUNNABLE);
    return error;
}