#ifndef  _UART_H_
#define  _UART_h_

#include <avr/interrupt.h>
#include <stdint.h>


#define  osc   16000000
#define  read  0
#define  write 1
#define  true  1
#define  false 0
#define receiveCharInterrupt()         ( rxReadWriteCharInterrupt(read) )
#define sendCharInterrupt(ch)           ( txReadWriteCharInterrupt(write,ch))
#define loadFromBuffer()               (rxReadWriteCharInterrupt(write))
#define loadTobuffer()                 (txReadWriteCharInterrupt(read,0) )

void (*pSendChar)(char ch);
void iniatUart(uint16_t baudrate );
char receiveChar();
void sendChar(char ch);
void SendString(char str[]);
void SendStringInterrupt(char str[]);
void iniatUartInterrupt(uint16_t baudrate );
char rxReadWriteCharInterrupt(uint8_t readOrWrite);
char txReadWriteCharInterrupt(uint8_t readOrWrite,char sendingCh);


#endif
