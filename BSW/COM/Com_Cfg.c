/**
 * @file Com_Cfg.c
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief These are the configurations for the COM
 * @version 0.1
 * @date 2020-04-19
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "Std_Types.h"
#include "Com.h"
#include "Com_Cfg.h"

/* WARNING : There is a restriction in the main function Algorithm
        A signal size must not exceed 1 Byte */

const PduInfoType PduInfo[COM_NUMBER_OF_PDUS] = {
        /*      id           direction           nSignal            signal[]              signalStart[]          signalWidth[]                  trig                     triggerData            */
        {    DOOR_PDU,       PDU_SEND,              1,         {DOOR_STATE_SIGNAL},             {0},                  {1},                PDU_TRIGGER_PERIOD,                 5                 }
                            /* This will be changed to PDU_RECEIVE in the second micro controller */

};