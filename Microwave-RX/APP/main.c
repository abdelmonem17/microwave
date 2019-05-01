

#ifndef F_CPU
# define F_CPU 16000000UL
#endif

#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/io.h>
#include "../HAL/LCD/LCD.h"
#include "../MCAL/UART/uart.h"
#include "../LIB/string/STRING.h"
#include "../MCAL/timer/timer.h"

#define MOTOR_STOP() 			(TCCR0=0)
#define MOTOR_START()			(pwm_timer0(100))



#define DEBUG_STOP(string)   	  LCDClearScreen();\
							  	  LCDPrint(string);\
							  	  while(1)

#define ALARM_PIN		2
#define ALARM_DIR 		DDRB
#define ALARM_PORT		PORTB

#define  ALARM_START()	 (ALARM_PORT|=(1<<ALARM_PIN))
#define  ALARM_STOP()	 (ALARM_PORT&=~(1<<ALARM_PIN))

char read_option();
uint16_t read_entered_time();
void counter_show(uint16_t time );
void operation_show(char option);
char wait_start_or_cancel();
static uint8_t is_stop_forced=0;



//RX
int main()
{

	PORTD=1<<2;
	MCUCR=(1<<ISC01);
	GICR=1<<INT0;
	sei();
uint16_t time_in_second;
char option;
LCDIntiat();
iniatUart(9600);


ALARM_DIR|=1<<ALARM_PIN;


//LCDSendChar( receiveChar() );

while(1)
{


	option=read_option();
	time_in_second=read_entered_time();
	if(wait_start_or_cancel() == '=' )

	{
		LCDClearScreen();
		operation_show(option);
		MOTOR_START();
		counter_show(time_in_second);
		MOTOR_STOP();
		if(is_stop_forced==0)
		{
			ALARM_START();
			_delay_ms(1000);
			ALARM_STOP();
		}

	}
	else
	{
		//cancel
	}
	is_stop_forced=0;


}


return 0;
}


char read_option()
{
	LCDPrint("enter operation:");

	return receiveChar();
}
uint16_t read_entered_time()
{
	uint16_t time=0;
	char ch;
	LCDClearScreen();
	LCDPrint("enter time:");
	do
	{

		ch=receiveChar();
		if(ch >='0' && ch <= '9')
		{
			LCDSendChar(ch);
			time=time*10+ (ch-0x30);
		}
	}
	while(ch != '=' );

	return time;

}
char wait_start_or_cancel()
{
	char ch;
	LCDClearScreen();
	LCDPrint("press START...");
	do{
		ch=receiveChar();
	}
	while( ch != '=' && ch != '<' );
	return ch;
}
void counter_show(uint16_t time )
{
	if(is_stop_forced==0)
	{
		LCDRowColumn(2,1);

		LCDPrint("Time:");
		while(time !=0)
		{
			if(is_stop_forced==1)
				{
					MOTOR_STOP();
					return ;
				}
			LCDRowColumn(2,6);
			LCDPrint( intToString(time) );
			timer1_delay_1s();
			time--;

	   }
	}
	LCDClearScreen();
}

void operation_show(char option)
{
	if(is_stop_forced==0)
	  {
		LCDClearScreen();
		LCDPrint("Running:");
		switch(option)
		{
		case '/':
				LCDPrint("Cooking");
				break;
		case '*':
				LCDPrint("Defrost");
				break;
		case '-':
				LCDPrint("Popcorn");
				break;
		case '+':
				LCDPrint("Bake");
				break;

		}
	  }

}

ISR(INT0_vect)
{


	is_stop_forced=1;

}

