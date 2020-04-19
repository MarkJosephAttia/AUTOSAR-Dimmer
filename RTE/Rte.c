/**
 * @file Rte.c
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-04-06
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "Std_Types.h"
#include "Sched.h"
#include "Switch.h"
#include "Led.h"
#include "Uart.h"
#include "Com_Cfg.h"
#include "Com.h"
#include "Rte.h"

#define RTE_NUMBER_OF_MODULES       5

typedef struct
{
    uint8_t id;
    uint8_t data;
} doorContact_t;

static volatile uint8_t Rte_rightDoorStatus = DOOR_CLOSED;
static volatile uint8_t Rte_leftDoorStatus = DOOR_CLOSED;
static volatile uint32_t Rte_doorContactStatus = DOOR_CLOSED;
static volatile uint8_t Rte_dimmerStatus = DIMMER_OFF;

static volatile runnable_t Rte_runnable[RTE_NUMBER_OF_MODULES];

/**
 * @brief Calls the switch to get the hardware door status
 * 
 * @param status The status of the door
 *              @arg DOOR_CLOSED If the door is closed
 *              @arg DOOR_OPEN If the door is open
 * @return Std_ReturnType 
 *              E_OK If the function executed successfully
 *              E_NOT_OK If the function executed successfully
 */
Std_ReturnType Rte_Call_LeftDoorGetStatus(uint8_t* status)
{
    Std_ReturnType error = E_NOT_OK;
    error = Switch_GetSwitchStatus(LEFT_DOOR, status);
    return error;
}

/**
 * @brief Writes the door status to the RTE
 * 
 * @param status The status of the door
 *              @arg DOOR_CLOSED If the door is closed
 *              @arg DOOR_OPEN If the door is open
 * @return Std_ReturnType 
 *              E_OK If the function executed successfully
 *              E_NOT_OK If the function executed successfully
 */
Std_ReturnType Rte_Write_LeftDoorStatus(uint8_t status)
{
    Rte_leftDoorStatus = status;
    return E_OK;
}

/**
 * @brief Calls the switch to get the hardware door status
 * 
 * @param status The status of the door
 *              @arg DOOR_CLOSED If the door is closed
 *              @arg DOOR_OPEN If the door is open
 * @return Std_ReturnType 
 *              E_OK If the function executed successfully
 *              E_NOT_OK If the function executed successfully
 */
Std_ReturnType Rte_Call_RightDoorGetStatus(uint8_t* status)
{
    Std_ReturnType error = E_NOT_OK;
    error = Switch_GetSwitchStatus(RIGHT_DOOR, status);
    return error;
}

/**
 * @brief Writes the door status to the RTE
 * 
 * @param status The status of the door
 *              @arg DOOR_CLOSED If the door is closed
 *              @arg DOOR_OPEN If the door is open
 * @return Std_ReturnType 
 *              E_OK If the function executed successfully
 *              E_NOT_OK If the function executed successfully
 */
Std_ReturnType Rte_Write_RightDoorStatus(uint8_t status)
{
    Rte_rightDoorStatus = status;
    return E_OK;
}

/**
 * @brief Reads the door status from the RTE
 * 
 * @param status The status of the door
 *              @arg DOOR_CLOSED If the door is closed
 *              @arg DOOR_OPEN If the door is open
 * @return Std_ReturnType 
 *              E_OK If the function executed successfully
 *              E_NOT_OK If the function executed successfully
 */
Std_ReturnType Rte_Read_LeftDoorStatus(uint8_t* status)
{
    *status = Rte_leftDoorStatus;
    return E_OK;
}

/**
 * @brief Reads the door status from the RTE
 * 
 * @param status The status of the door
 *              @arg DOOR_CLOSED If the door is closed
 *              @arg DOOR_OPEN If the door is open
 * @return Std_ReturnType 
 *              E_OK If the function executed successfully
 *              E_NOT_OK If the function executed successfully
 */
Std_ReturnType Rte_Read_RightDoorStatus(uint8_t* status)
{
    *status = Rte_rightDoorStatus;
    return E_OK;    
}

/**
 * @brief Writes the dimmer status to the RTE
 * 
 * @param status The status of the door
 *              @arg DIMMER_ON If the dimmer is on
 *              @arg DIMMER_OF If the dimmer is off
 * @return Std_ReturnType 
 *              E_OK If the function executed successfully
 *              E_NOT_OK If the function executed successfully
 */
Std_ReturnType Rte_Write_DimmerStatus(uint8_t status)
{
    Rte_dimmerStatus = status;
    return E_OK;
}

/**
 * @brief Reads the dimmer status from the RTE
 * 
 * @param status The status of the door
 *              @arg DIMMER_ON If the dimmer is on
 *              @arg DIMMER_OF If the dimmer is off
 * @return Std_ReturnType 
 *              E_OK If the function executed successfully
 *              E_NOT_OK If the function executed successfully
 */
Std_ReturnType Rte_Read_DimmerStatus(uint8_t* status)
{
    *status = Rte_dimmerStatus;
    return E_OK;
}

/**
 * @brief Calls the Led to set the hardware lamp status
 * 
 * @param status The status of the door
 *              @arg DIMMER_ON If the dimmer is on
 *              @arg DIMMER_OF If the dimmer is off
 * @return Std_ReturnType 
 *              E_OK If the function executed successfully
 *              E_NOT_OK If the function executed successfully
 */
Std_ReturnType Rte_Call_LightingSetStatus(uint8_t status)
{
    Std_ReturnType error = E_NOT_OK;
    error = Led_SetLedStatus(DIMMER_LAMP, status);
    return error;
}

/**
 * @brief Writes the door contact status
 * 
 * @param status The status of the door
 *              @arg DOOR_OPEN If the dimmer is on
 *              @arg DOOR_CLOSED If the dimmer is off
 * @return Std_ReturnType 
 *              E_OK If the function executed successfully
 *              E_NOT_OK If the function executed successfully
 */
extern Std_ReturnType Rte_Write_DoorContactStatus(uint8_t status)
{
    Rte_doorContactStatus = status;
    return E_OK;
}

/**
 * @brief Sends Data of the door contact
 * 
 * @return Std_ReturnType 
 *              E_OK If the function executed successfully
 *              E_NOT_OK If the function executed successfully
 */
Std_ReturnType Rte_Call_DoorContactSendData(void)
{
    Std_ReturnType error;
    error = Com_SendSignal(DOOR_STATE_SIGNAL, (const void*)&Rte_doorContactStatus);
    return error;
}

/**
 * @brief Receives Data for the dimmer
 * 
 * @param receiveID The ID of the data
 * @param data The Data to receive
 * @return Std_ReturnType 
 *              E_OK If the function executed successfully
 *              E_NOT_OK If the function executed successfully
 */
Std_ReturnType Rte_Call_DimmerReceiveData(void)
{
    Std_ReturnType error;
    error = Com_ReceiveSignal(DOOR_STATE_SIGNAL, (void*)&Rte_doorContactStatus);;
    return error;
}

/**
 * @brief Receives Data for the dimmer
 * @param status The status of the door
 *              @arg DOOR_OPEN If the dimmer is on
 *              @arg DOOR_CLOSED If the dimmer is off
 * @return Std_ReturnType 
 *              E_OK If the function executed successfully
 *              E_NOT_OK If the function executed successfully
 */
Std_ReturnType Rte_Read_DoorContact(uint8_t* status)
{
    *status = Rte_doorContactStatus;
    return E_OK;
}

/**
 * @brief Sets the runnable for a certain module
 * 
 * @param runnable the runnable to set
 * @param module the module to set runnable to
 * @return Std_ReturnType 
 *              E_OK If the function executed successfully
 *              E_NOT_OK If the function executed successfully
 */
extern Std_ReturnType Rte_SetRunnableEntity(runnable_t runnable, uint8_t module)
{
    Rte_runnable[module] = runnable;
    return E_OK;
}


static void Rte_Runnable(void)
{
    if(Rte_runnable[RTE_LEFT_DOOR_RUNNABLE])
    {
        Rte_runnable[RTE_LEFT_DOOR_RUNNABLE]();
    }
    if(Rte_runnable[RTE_RIGHT_DOOR_RUNNABLE])
    {
        Rte_runnable[RTE_RIGHT_DOOR_RUNNABLE]();
    }
    if(Rte_runnable[RTE_DOOR_CONTACT_RUNNABLE])
    {
        Rte_runnable[RTE_DOOR_CONTACT_RUNNABLE]();
    }
    if(Rte_runnable[RTE_DIMMER_RUNNABLE])
    {
        Rte_runnable[RTE_DIMMER_RUNNABLE]();
    }
    if(Rte_runnable[RTE_LIGHTING_RUNNABLE])
    {
        Rte_runnable[RTE_LIGHTING_RUNNABLE]();
    }
}

const task_t Rte_task = {Rte_Runnable, 40};