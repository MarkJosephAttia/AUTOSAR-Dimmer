/**
 * @file Sched.c
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief This file is the implementation for the Scheduler
 * @version 0.1
 * @date 2020-03-08
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "Std_Types.h"
#include "Sched_Cfg.h"
#include "Sched.h"
#include "Timer0.h"

#define SCHED_TASK_RUNNING               1
#define SCHED_TASK_SUSPENDED             2

typedef struct
{
    const sysTaskInfo_t* taskInfo;
    uint32_t remainToExec;
    uint32_t periodTicks;
    uint8_t state;
    uint32_t sleepTimes;
} sysTask_t;

extern const sysTaskInfo_t Sched_sysTaskInfo[SCHED_NUMBER_OF_TASKS];

static sysTask_t Sched_task[SCHED_NUMBER_OF_TASKS];

static volatile uint8_t Sched_flag;

static volatile uint8_t Sched_taskItr;

/**
 * @brief Sets the scheduler flag
 * 
 */
static void Sched_SetFlag(void)
{
    Sched_flag = 1;
}

/**
 * @brief The scheduler that will run all the time
 * 
 */
void Sched_Start(void)
{
    while(1)
    {
        if(Sched_flag)
        {
            Sched_flag = 0;
            for(Sched_taskItr=0; Sched_taskItr<SCHED_NUMBER_OF_TASKS; Sched_taskItr++)
            {
                if(SCHED_TASK_RUNNING == Sched_task[Sched_taskItr].state)
                {
                        if(0 == Sched_task[Sched_taskItr].remainToExec)
                        {
                            Sched_task[Sched_taskItr].remainToExec = Sched_task[Sched_taskItr].periodTicks;
                            Sched_task[Sched_taskItr].taskInfo->task->runnable();
                        }
                        Sched_task[Sched_taskItr].remainToExec--;
                }
            }
        }
    }
}

/**
 * @brief The initialization for the Scheduler
 * 
 * @return Std_ReturnType 
 */
Std_ReturnType Sched_Init(void)
{
    uint8_t i;
    for(i=0; i<SCHED_NUMBER_OF_TASKS; i++)
    {
        Sched_task[i].taskInfo = &Sched_sysTaskInfo[i];
        Sched_task[i].remainToExec = Sched_task[i].taskInfo->delayTicks;
        Sched_task[i].periodTicks = Sched_task[i].taskInfo->task->periodicTimeMS / SCHED_TICK_TIME_MS;
        Sched_task[i].state = SCHED_TASK_RUNNING;
    }
    Timer0_SetTimeUS((f64)SCHED_SYS_CLK /256.0, SCHED_TICK_TIME_MS*1000);
    Timer0_SetCallBack(Sched_SetFlag);
    Timer0_ClearValue();
    Timer0_Start(TMR0_DIV_256);
    Timer0_InterruptEnable();
    return E_OK;
}

/**
 * @brief Suspends a running task
 * 
 * @return Std_ReturnType 
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType Sched_SuspendTask(void)
{
    Sched_task[Sched_taskItr].state = SCHED_TASK_SUSPENDED;
    return E_OK;
}

/**
 * @brief Makes a task sleep for a while
 * 
 * @param timeMS The sleep time in milli seconds
 * @return Std_ReturnType 
 *                 E_OK : if the function is executed correctly
 *                 E_NOT_OK : if the function is not executed correctly
 */
Std_ReturnType Sched_Sleep(uint32_t timeMS)
{
    uint32_t times = timeMS / SCHED_TICK_TIME_MS;
    Sched_task[Sched_taskItr].remainToExec += times;
    return E_OK;
}
