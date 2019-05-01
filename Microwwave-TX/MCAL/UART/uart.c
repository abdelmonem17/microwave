#include "uart.h"


void iniatUart(uint16_t baudrate )
{
	uint16_t ubrr= (osc/16/baudrate) - 1;
	UCSRC= (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);
	UCSRB= (1<<RXEN)| (1<<TXEN);
	UBRRH=ubrr>>8;
	UBRRL=(uint8_t)ubrr;
	
}
void sendChar(char ch)
{
	while( ( UCSRA & (1<<UDRE) ) == 0 );
	UDR=ch;
}
void SendString(char str[])
{
	uint8_t i=0;
	while(str[i]!=0)
	sendChar(str[i++]);

}
char receiveChar()
{
	
	while (  (UCSRA & (1<<RXC)  ) ==0 );
	return UDR;
}

void iniatUartInterrupt(uint16_t baudrate )
{
	uint16_t ubrr= (osc/16/baudrate) - 1;
	UBRRH=ubrr>>8;
	UBRRL=(uint8_t)ubrr;
	UCSRB=(1<<RXEN)| (1<<TXEN)|(1<<RXCIE)|(1<<UDRIE);
	UCSRC=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
	

	
	sei();
}

char txReadWriteCharInterrupt(uint8_t readOrWrite,char sendingCh)
{
	static int8_t ch;
	static int8_t isRead=true;
	if ( readOrWrite == read && isRead == false )
	{
		isRead=true;
		return ch;
	}
	else if(readOrWrite==write)
	{
		ch=sendingCh;
		isRead=false;
		return true;
	}
	else
	return false;
}

char rxReadWriteCharInterrupt(uint8_t readOrWrite)
{
	static char ch;
	static char isRead=true;
	if ( readOrWrite == read && isRead == false )
	{
		isRead=true;
		return ch;
	}
	else if(readOrWrite==write)
	{
		ch=UDR;
		isRead=false;
		return true;
	}
	else
	return false;
}

void SendStringInterrupt(char str[])
{
		uint8_t i=0;
		while(str[i]!=0)
		sendCharInterrupt(str[i++]);
}

ISR(USART_RXC_vect)
{
	 loadFromBuffer();
	
}

ISR(USART_UDRE_vect)
{
	int8_t ch=loadTobuffer();
	if (ch)
	{ 
		UDR=ch;
		
	}
}
