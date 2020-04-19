/**
 * @file Lighting.c
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief This is the implementation for the Lighting
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
 * @brief This is the runnable for the lighting that sets the Lamp
 * 
 */
static void Lighting_Runnable(void)
{
    uint8_t status;
    Rte_Read_DimmerStatus(&status);
    Rte_Call_LightingSetStatus(status);
}

/**
 * @brief Initialise the lighting application
 * 
 * @return Std_ReturnType 
 *              E_OK If the function executed successfully
 *              E_NOT_OK If the function executed successfully
 */
Std_ReturnType Lighting_Init(void)
{
    Std_ReturnType error = Rte_SetRunnableEntity(Lighting_Runnable, RTE_LIGHTING_RUNNABLE);
    return error;
}
