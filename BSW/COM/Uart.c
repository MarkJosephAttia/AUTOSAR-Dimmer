/**
 * @file Uart.c
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief This is the implementation for the UART driver
 * @version 0.1
 * @date 2020-03-26
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "Std_Types.h"
#include "Uart_Cfg.h"
#include "Uart.h"

typedef struct 
{
  uint8_t *ptr;
  uint32_t pos;
  uint32_t size;
  uint8_t state;
} dataBuffer_t;

typedef void (*appNotify_t)(void);


#define UDR   (*(volatile uint8_t*)(0x2C))
#define UBRRH (*(volatile uint8_t*)(0x40))
#define UCSRC (*(volatile uint8_t*)(0x40))
#define UCSRA (*(volatile uint8_t*)(0x2B))
#define UCSRB (*(volatile uint8_t*)(0x2A))
#define UBRRL (*(volatile uint8_t*)(0x29))

#define SREG                        *((volatile uint8_t*)0x5F)
#define GIE                         0x80

#define UART_INT_NUMBER 37

#define UART_BUFFER_IDLE 0
#define UART_BUFFER_BUSY 1

#define UART_RXCIE_SET     0x80
#define UART_TXCIE_SET     0x40
#define UART_UDRIE_CLR     0xDF
#define UART_RX_EN         0x10
#define UART_TX_EN         0x08
#define UART_CLR_PARITY    0xCF
#define UART_NO_PARITY     0x00
#define UART_BYTE          0x06
#define UART_UCSRC_SELECT  0x80

#define UART_NO_PRESCALER 0x1

static volatile dataBuffer_t txBuffer;
static volatile dataBuffer_t rxBuffer;

static volatile appNotify_t appTxNotify;
static volatile appNotify_t appRxNotify;

void __vector_13 (void) __attribute__ ((signal, used, externally_visible));
void __vector_15 (void) __attribute__ ((signal, used, externally_visible));

/**
 * @brief The interrupt handler for the UART 1 module Receive Interrupt
 * 
 */
void __vector_13 (void)
{
  if (UART_BUFFER_BUSY == rxBuffer.state) 
  {
    rxBuffer.ptr[rxBuffer.pos] = UDR;
    rxBuffer.pos++;

    if (rxBuffer.pos == rxBuffer.size) 
    {
      rxBuffer.ptr = NULL;
      rxBuffer.size = 0;
      rxBuffer.pos = 0;
      rxBuffer.state = UART_BUFFER_IDLE;
      if (appRxNotify) 
      {
        appRxNotify();
      }
    }
  }
}
/**
 * @brief The interrupt handler for the UART 1 module Transmission Complete
 * 
 */
void __vector_15 (void)
{
  if (txBuffer.size != txBuffer.pos) 
  {
    UDR = txBuffer.ptr[txBuffer.pos++];
  } 
  else 
  {
    txBuffer.ptr = NULL;
    txBuffer.size = 0;
    txBuffer.pos = 0;
    txBuffer.state = UART_BUFFER_IDLE;
    if (appTxNotify) 
    {
      appTxNotify();
    }
  }
}

/**
 * @brief Initializes the UART
 *
 * @param baudRate the baud rate of the UART (uint32_t)
 * @param stopBits The number of the stop bits
 *                 UART_ONE_STOP_BIT
 *                 UART_TWO_STOP_BITS
 * @param parity The parity of the transmission
 *                 UART_ODD_PARITY
 *                 UART_EVEN_PARITY
 *                 UART_NO_PARITY
 * @return Std_ReturnType A Status
 *                  E_OK: If the function executed successfully
 *                  E_NOT_OK: If the did not execute successfully
 */
extern Std_ReturnType Uart_Init(uint32_t baudRate, uint32_t stopBits, uint32_t parity) 
{
  uint8_t tmpReg;
  uint32_t baud = ((uint32_t)((f64)UART_SYSTEM_CLK / ((f64)baudRate * 16.0)));
  SREG |= GIE;
  UCSRB |= UART_RX_EN | UART_TX_EN;
  UBRRL = (uint8_t)baud;
  UBRRH = (uint8_t)(baud>>8);
  UCSRC = stopBits | UART_UCSRC_SELECT | UART_BYTE | parity;
  rxBuffer.state = UART_BUFFER_IDLE;
  txBuffer.state = UART_BUFFER_IDLE;
  UCSRB |= UART_RXCIE_SET | UART_TXCIE_SET;;
  return E_OK;
}

/**
 * @brief Sends data through the UART
 *
 * @param data The data to send
 * @param length the length of the data in bytes
 * @return Std_ReturnType A Status
 *                  E_OK: If the driver is ready to send
 *                  E_NOT_OK: If the driver can't send data right now
 */
Std_ReturnType Uart_Send(uint8_t *data, uint16_t length) 
{
  Std_ReturnType error = E_NOT_OK;
  if (data && (length > 0) && txBuffer.state == UART_BUFFER_IDLE) 
  {
    txBuffer.state = UART_BUFFER_BUSY;
    txBuffer.ptr = data;
    txBuffer.pos = 0;
    txBuffer.size = length;

    UDR = txBuffer.ptr[txBuffer.pos++];
    error = E_OK;
  }
  return error;
}
/**
 * @brief Receives data through the UART
 *
 * @param data The buffer to receive data in
 * @param length the length of the data in bytes
 * @return Std_ReturnType A Status
 *                  E_OK: If the driver is ready to receive
 *                  E_NOT_OK: If the driver can't receive data right now
 */
Std_ReturnType Uart_Receive(uint8_t *data, uint16_t length) 
{
  Std_ReturnType error = E_NOT_OK;
  if (rxBuffer.state == UART_BUFFER_IDLE) 
  {
    rxBuffer.ptr = data;
    rxBuffer.size = length;
    rxBuffer.pos = 0;
    rxBuffer.state = UART_BUFFER_BUSY;
    error = E_OK;
  }
  return error;
}
/**
 * @brief Sets the callback function that will be called when transmission is
 * completed
 *
 * @param func the callback function
 * @return Std_ReturnType A Status
 *                  E_OK: If the function executed successfully
 *                  E_NOT_OK: If the did not execute successfully
 */
Std_ReturnType Uart_SetTxCb(txCb_t func) 
{
  appTxNotify = func;
  return E_OK;
}
/**
 * @brief Sets the callback function that will be called when receive is
 * completed
 *
 * @param func the callback function
 * @return Std_ReturnType A Status
 *                  E_OK: If the function executed successfully
 *                  E_NOT_OK: If the did not execute successfully
 */
Std_ReturnType Uart_SetRxCb(rxCb_t func) 
{
  appRxNotify = func;
  return E_OK;
}
