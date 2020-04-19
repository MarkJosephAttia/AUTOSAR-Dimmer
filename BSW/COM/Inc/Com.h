/**
 * @file Com.h
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief This is the user inteface for the COM
 * @version 0.1
 * @date 2020-04-19
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef COM_H_
#define COM_H_


#define PDU_MAX_NUMBER_OF_SIGNALS           6

#define PDU_TRIGGER_NONE                    0
#define PDU_TRIGGER_PERIOD                  1
#define PDU_TRIGGER_SIGNAL                  2

#define PDU_SEND                            0
#define PDU_RECEIVE                         1

typedef uint16_t SignalIdType; 
typedef uint16_t PduIdType;
typedef uint8_t PduTriggerType;

/* WARNING : There is a restriction in the main function Algorithm
			A signal size must not exceed 1 Byte */

typedef struct 
{
    PduIdType id;
    uint8_t direction;
    uint16_t nSignals;
    SignalIdType signal[PDU_MAX_NUMBER_OF_SIGNALS];
    uint8_t signalStart[PDU_MAX_NUMBER_OF_SIGNALS];
    uint8_t signalWidth[PDU_MAX_NUMBER_OF_SIGNALS];
    PduTriggerType trig;
    uint16_t triggerData; /* Milleseconds for Period and Signal Id for signal */

}PduInfoType;

/**
 * @brief Initialises the Com
 * 
 * @return Std_ReturnType 
 *                  E_OK
 *                  E_NOT_OK
 */
extern Std_ReturnType Com_Init(void);

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
extern Std_ReturnType Com_SendSignal(SignalIdType signalId, const void* data);

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
extern Std_ReturnType Com_ReceiveSignal(SignalIdType signalId, void* data);

/**
 * @brief Triggers The Transmission
 * 
 * @param pduId The Id of the Pdu
 * 
 * @return Std_ReturnType 
 *                  E_OK
 *                  E_NOT_OK
 */
extern Std_ReturnType Com_TriggerTransmit(PduIdType pduId);

#endif