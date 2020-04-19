/**
 * @file Rte.h
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief This is the user interface for the RTE
 * @version 0.1
 * @date 2020-04-06
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef RTE_H
#define RTE_H

#define DIMMER_ON       0
#define DIMMER_OFF      !DIMMER_ON
#define DOOR_CLOSED     0
#define DOOR_OPEN       !DOOR_CLOSED

#define RTE_CONTACT_ID  0

#define RTE_LEFT_DOOR_RUNNABLE              0
#define RTE_RIGHT_DOOR_RUNNABLE             1
#define RTE_DOOR_CONTACT_RUNNABLE           2
#define RTE_DIMMER_RUNNABLE                 3
#define RTE_LIGHTING_RUNNABLE               4

typedef void (*runnable_t)(void);

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
extern Std_ReturnType Rte_Call_LeftDoorGetStatus(uint8_t* status);

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
extern Std_ReturnType Rte_Write_LeftDoorStatus(uint8_t status);

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
extern Std_ReturnType Rte_Call_RightDoorGetStatus(uint8_t* status);

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
extern Std_ReturnType Rte_Write_RightDoorStatus(uint8_t status);

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
extern Std_ReturnType Rte_Read_LeftDoorStatus(uint8_t* status);

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
extern Std_ReturnType Rte_Read_RightDoorStatus(uint8_t* status);

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
extern Std_ReturnType Rte_Write_DimmerStatus(uint8_t status);

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
extern Std_ReturnType Rte_Read_DimmerStatus(uint8_t* status);

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
extern Std_ReturnType Rte_Call_LightingSetStatus(uint8_t status);

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
extern Std_ReturnType Rte_Write_DoorContactStatus(uint8_t status);

/**
 * @brief Sends Data of the door contact
 * 
 * @return Std_ReturnType 
 *              E_OK If the function executed successfully
 *              E_NOT_OK If the function executed successfully
 */
extern Std_ReturnType Rte_Call_DoorContactSendData(void);

/**
 * @brief Receives Data for the dimmer
 * 
 * @return Std_ReturnType 
 *              E_OK If the function executed successfully
 *              E_NOT_OK If the function executed successfully
 */
extern Std_ReturnType Rte_Call_DimmerReceiveData(void);

/**
 * @brief Receives Data for the dimmer
 * 
 * @return Std_ReturnType 
 *              E_OK If the function executed successfully
 *              E_NOT_OK If the function executed successfully
 */
extern Std_ReturnType Rte_Call_DimmerWriteData(void);

/**
 * @brief Receives Data for the dimmer
 * @param status The status of the door
 *              @arg DOOR_OPEN If the dimmer is on
 *              @arg DOOR_CLOSED If the dimmer is off
 * @return Std_ReturnType 
 *              E_OK If the function executed successfully
 *              E_NOT_OK If the function executed successfully
 */
extern Std_ReturnType Rte_Read_DoorContact(uint8_t* status);

/**
 * @brief Sets the runnable for a certain module
 * 
 * @param runnable the runnable to set
 * @param module the module to set runnable to
 * @return Std_ReturnType 
 *              E_OK If the function executed successfully
 *              E_NOT_OK If the function executed successfully
 */
extern Std_ReturnType Rte_SetRunnableEntity(runnable_t runnable, uint8_t module);

#endif