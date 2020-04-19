/**
 * @file DoorContact.c
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief This is the implementation for the Door Contact application
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
 * @brief This is the runnable for the Door Contact
 * 
 */
static void DoorContact_Runnable(void)
{
    uint8_t leftStatus, rightStatus;
    Rte_Read_LeftDoorStatus(&leftStatus);
    Rte_Read_RightDoorStatus(&rightStatus);
    if(leftStatus == DOOR_CLOSED && rightStatus == DOOR_CLOSED)
    {
        Rte_Write_DoorContactStatus(DOOR_CLOSED);
        Rte_Call_DoorContactSendData();
    }
    else
    {
        Rte_Write_DoorContactStatus(DOOR_OPEN);
        Rte_Call_DoorContactSendData();
    }
}

/**
 * @brief Initialise the door contact application
 * 
 * @return Std_ReturnType 
 *              E_OK If the function executed successfully
 *              E_NOT_OK If the function executed successfully
 */
Std_ReturnType DoorContact_Init(void)
{
    Std_ReturnType error = Rte_SetRunnableEntity(DoorContact_Runnable, RTE_DOOR_CONTACT_RUNNABLE);
    return error;
}