#define F_CPU 1000000UL

#define BAUDRATE 4800

#define myubrr ((F_CPU/(BAUDRATE*16UL))-1)


#include<avr/io.h>
#include<util/delay.h>

void uart_init()
{
	UBRRL=myubrr;
	UBRRH=(myubrr>>8);
	UCSRB|=(1<<RXEN);
}

unsigned int uart_receive()
{
	while((UCSRA & (1<<RXC))==0);
	return(UDR);
}

void main()
{
	unsigned char value;
	
	DDRB=0b11111111;
	uart_init();
	_delay_ms(50);
	
	while(1)
	{
		value=uart_receive();
		
		if(value=='w')
		PORTB=0b00001010;
		
		else if(value=='s')
		PORTB=0b00000101;
		
		else if(value=='a')
		PORTB=0b00000110;
		
		else if(value=='d')
		PORTB=0b00001001;
		
		else
		PORTB=0b00000000;
	}
}
