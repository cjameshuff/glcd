
#include "usart.h"

//************************************************************************************************

const char hexchars[] PROGMEM = "0123456789ABCDEF";


void USART_Init()
{
	const uint16_t ubrr = ((F_CPU/BAUD_RATE)/16) - 1;//1x mode
//	const uint16_t ubrr = ((F_CPU/BAUD_RATE)/8) - 1;//2x mode
	UBRRH = ubrr >> 8;
	UBRRL = ubrr;
	
	
	//UCSRA & (1 << RXC);//RX complete
	//UCSRA & (1 << TXC);//TX complete
	//UCSRA & (1 << UDRE);//Data register empty
	//UCSRA & (1 << FE);//frame error
	//UCSRA & (1 << DOR);//overrun
	//UCSRA & (1 << PE);//parity error
	//UCSRA = (1 << U2X);//2x transmit speed
	
	//UCSRB
	//(1 << MPCM);//Enable multiprocessor mode
	//(1 << RXCIE);//Enable RX complete interrupt
	//(1 << TXCIE);//Enable TX complete interrupt
	//(1 << UDRIE);//Enable data register empty interrupt
	//(1 << UCSZ2);//9 bit mode (with UCSZ1 and UCSZ0 set)
	//(UCSRB & RXB8): 9th bit received in 9-bit mode
	//(1 << TXB8);//9th bit to transmit in 9-bit mode
	UCSRB = (1 << RXCIE) | (1 << RXEN) | (1 << TXEN);
	
	//UCSRC
	//(1 << UMSEL);//Synchronous mode select
	//(1 << UPM1) | (1 << UPM0);//Parity mode (00 disabled, 10 even, 11 odd)
	//(1 << USBS);//stop bit select (1 for 2 stop bits, 0 for 1 stop bit)
	//(1 << UCPOL);//Synchronous mode clock polarity (0 in asynch mode)
	
	//8 data, 1 stop bit, no parity
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
}


//************************************************************************************************

