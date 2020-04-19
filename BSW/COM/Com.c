/**
 * @file Com.c
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief This is the implementation for the COM
 * @version 0.1
 * @date 2020-04-19
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "Std_Types.h"
#include "Com_Cfg.h"
#include "Com.h"
#include "Uart.h"
#include "Sched.h"

#define COM_PDU_TRIGGERED                       0
#define COM_PDU_NOT_TRIGGERED                   1

#define COM_TICK_TIME                           5

#define COM_BYTE_SIZE                           8

typedef struct
{
    const PduInfoType* pduInf;
    uint16_t remainingTicks;
    uint16_t periodicTicks;
    uint8_t data[COM_PDU_SIZE_IN_BYTES];
    uint8_t trig;
}PduType;

static volatile PduType Com_Pdu[COM_NUMBER_OF_PDUS];
static volatile uint32_t Com_Signal[COM_NUMBER_OF_SIGNALS];

const uint8_t Com_ByteMasks[COM_BYTE_SIZE] = {
    0b1,
    0b11,
    0b111,
    0b1111,
    0b11111,
    0b111111,
    0b1111111,
    0b11111111
};

extern const PduInfoType PduInfo[COM_NUMBER_OF_PDUS];

/**
 * @brief Initialises the Com
 * 
 * @return Std_ReturnType 
 *                  E_OK
 *                  E_NOT_OK
 */
Std_ReturnType Com_Init(void)
{
    uint8_t itr;
    for(itr = 0; itr < COM_NUMBER_OF_PDUS; itr++)
    {
        Com_Pdu[itr].pduInf = &PduInfo[itr];
        Com_Pdu[itr].remainingTicks = 0;
        Com_Pdu[itr].periodicTicks = Com_Pdu[itr].pduInf->triggerData / COM_TICK_TIME;
        Com_Pdu[itr].trig = COM_PDU_NOT_TRIGGERED;
    }
    return E_OK;
}

/**
 * @brief Sends a signal
 * 
 * @param signalId The Id of the signal
 * @param data the data to send through the signal
 * 
 * @return Std_ReturnType 
 *                  E_OK
 *                  E_NOT_OK
 */
Std_ReturnType Com_SendSignal(SignalIdType signalId, uint32_t data)
{
    Com_Signal[signalId] = data;
    return E_OK;
}

/**
 * @brief Receives a signal
 * 
 * @param signalId The Id of the signal
 * @param data the data to receive
 * 
 * @return Std_ReturnType 
 *                  E_OK
 *                  E_NOT_OK
 */
Std_ReturnType Com_ReceiveSignal(SignalIdType signalId, uint32_t* data)
{
    *data = Com_Signal[signalId];
    return E_OK;
}

/**
 * @brief Triggers The Transmission
 * 
 * @param pduId The Id of the Pdu
 * 
 * @return Std_ReturnType 
 *                  E_OK
 *                  E_NOT_OK
 */
Std_ReturnType Com_TriggerTransmit(PduIdType pduId)
{
    Com_Pdu[pduId].trig = COM_PDU_TRIGGERED;
    return E_OK;
}

/* WARNING : There is a restriction in the main function Algorithm
        All of the signal bits have to be allocated in the same byte */

/**
 * @brief Transmit Runnable
 * 
 */
static void Com_MainFunctionTx(void)
{
    uint8_t pduItr, signalItr, byteItr;
    for(pduItr = 0; pduItr<COM_NUMBER_OF_PDUS; pduItr++)
    {
        if(Com_Pdu[pduItr].pduInf->direction == PDU_SEND)
        {
            if(Com_Pdu[pduItr].pduInf->trig == PDU_TRIGGER_SIGNAL && Com_Pdu[pduItr].trig == COM_PDU_TRIGGERED)
            {
                for(byteItr=0; byteItr<COM_PDU_SIZE_IN_BYTES; byteItr++)
				{
					Com_Pdu[pduItr].data[byteItr]=0;
				}
                Com_Pdu[pduItr].data[COM_PDU_START/8] |= 
                                Com_Pdu[pduItr].pduInf->id<<(COM_PDU_START & 0x0F);
                for(signalItr = 0; signalItr<Com_Pdu[pduItr].pduInf->nSignals; signalItr++)
                {
                    /* The Byte Number |= signal << signalStart % 8 */
                    Com_Pdu[pduItr].data[Com_Pdu[pduItr].pduInf->signalStart[signalItr]/8] |= 
                                Com_Signal[Com_Pdu[pduItr].pduInf->signal[signalItr]]<<(Com_Pdu[pduItr].pduInf->signalStart[signalItr] & 0x0F);
                }
                Com_Pdu[pduItr].trig = COM_PDU_NOT_TRIGGERED;
                Uart_Send(Com_Pdu[pduItr].data, COM_PDU_SIZE_IN_BYTES);
            }
            if(Com_Pdu[pduItr].pduInf->trig == PDU_TRIGGER_PERIOD && Com_Pdu[pduItr].remainingTicks == 0)
            {
                for(byteItr=0; byteItr<COM_PDU_SIZE_IN_BYTES; byteItr++)
				{
					Com_Pdu[pduItr].data[byteItr]=0;
				}
                Com_Pdu[pduItr].data[COM_PDU_START/8] |=
                                Com_Pdu[pduItr].pduInf->id<<(COM_PDU_START & 0x0F);
                for(signalItr = 0; signalItr<Com_Pdu[pduItr].pduInf->nSignals; signalItr++)
                {
                    /* The Byte Number |= signal << signalStart % 8 */
                    Com_Pdu[pduItr].data[Com_Pdu[pduItr].pduInf->signalStart[signalItr]/8] |= 
                                Com_Signal[Com_Pdu[pduItr].pduInf->signal[signalItr]]<<(Com_Pdu[pduItr].pduInf->signalStart[signalItr] & 0x0F);
                }
                Com_Pdu[pduItr].remainingTicks = Com_Pdu[pduItr].periodicTicks;
                Uart_Send(Com_Pdu[pduItr].data, COM_PDU_SIZE_IN_BYTES);
            }
            if(Com_Pdu[pduItr].pduInf->trig == PDU_TRIGGER_PERIOD)
            {
                Com_Pdu[pduItr].remainingTicks--;
            }
        }
    }
}

/**
 * @brief Receive Runnable
 * 
 */
static void Com_MainFunctionRx(void)
{
    uint8_t pduItr, signalItr;
    for(pduItr = 0; pduItr<COM_NUMBER_OF_PDUS; pduItr++)
    {
        if(Com_Pdu[pduItr].pduInf->direction == PDU_RECEIVE)
        {
            if(Com_Pdu[pduItr].pduInf->trig == PDU_TRIGGER_SIGNAL && Com_Pdu[pduItr].trig == COM_PDU_TRIGGERED)
            {
                Uart_Receive(Com_Pdu[pduItr].data, COM_PDU_SIZE_IN_BYTES);
                for(signalItr = 0; signalItr<Com_Pdu[pduItr].pduInf->nSignals; signalItr++)
                {
                    /* Signal = data[start/8] >> signalStart % 8 */
                    Com_Signal[Com_Pdu[pduItr].pduInf->signal[signalItr]] = 
                                Com_Pdu[pduItr].data[Com_Pdu[pduItr].pduInf->signalStart[signalItr]/8] >> (Com_Pdu[pduItr].pduInf->signalStart[signalItr] & 0x0F);
                    Com_Signal[Com_Pdu[pduItr].pduInf->signal[signalItr]] &= Com_ByteMasks[Com_Pdu[pduItr].pduInf->signalWidth[signalItr]-1];
                }
                Com_Pdu[pduItr].trig = COM_PDU_NOT_TRIGGERED;
            }
            if(Com_Pdu[pduItr].pduInf->trig == PDU_TRIGGER_PERIOD && Com_Pdu[pduItr].remainingTicks == 0)
            {
                Uart_Receive(Com_Pdu[pduItr].data, COM_PDU_SIZE_IN_BYTES);
                for(signalItr = 0; signalItr<Com_Pdu[pduItr].pduInf->nSignals; signalItr++)
                {
                    /* Signal = data[start/8] >> signalStart % 8 */
                    Com_Signal[Com_Pdu[pduItr].pduInf->signal[signalItr]] = 
                                Com_Pdu[pduItr].data[Com_Pdu[pduItr].pduInf->signalStart[signalItr]/8] >> (Com_Pdu[pduItr].pduInf->signalStart[signalItr] & 0x0F);
                    Com_Signal[Com_Pdu[pduItr].pduInf->signal[signalItr]] &= Com_ByteMasks[Com_Pdu[pduItr].pduInf->signalWidth[signalItr]-1];
                }
                Com_Pdu[pduItr].remainingTicks = Com_Pdu[pduItr].periodicTicks;
            }
            if(Com_Pdu[pduItr].pduInf->trig == PDU_TRIGGER_PERIOD)
            {
                Com_Pdu[pduItr].remainingTicks--;
            }
        }
    }
}

/**
 * @brief The Com Runnable
 * 
 */
static void Com_Runnable(void)
{
    Com_MainFunctionTx();
    Com_MainFunctionRx();
}

const task_t Com_task = {&Com_Runnable, COM_TICK_TIME};