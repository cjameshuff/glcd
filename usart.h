
#ifndef USART_H
#define USART_H

#include <avr/io.h>
#include <avr/pgmspace.h>
#include "common.h"

//************************************************************************************************

extern const char hexchars[] PROGMEM;

void USART_Init(void);

static inline void USART_Write(uint8_t byte)
{
	while(!(UCSRA & (1 << UDRE)))
		;
	UDR = byte;
}

static inline void USART_WriteHex8(uint8_t byte)
{
	USART_Write(pgm_read_byte(hexchars + ((byte >> 4) & 0x0F)));
	USART_Write(pgm_read_byte(hexchars + (byte & 0x0F)));
}

static inline void USART_WriteNewline(void)
{
	USART_Write('\n');
	USART_Write('\r');
}

static inline void USART_WriteString_P(const char * str)
{
	while(pgm_read_byte(str) != '\0')
		USART_Write(pgm_read_byte(str++));
}

static inline void USART_WriteString(const char * str)
{
	while(*str != '\0')
		USART_Write(*str++);
}

static inline uint8_t USART_Read(void)
{
	while(!(UCSRA & (1 << RXC)))
		;
	return UDR;
}

static inline void USART_Flush(void)
{
	uint8_t dummy;
	while(!(UCSRA & (1 << RXC)))
		dummy = UDR;
}

//************************************************************************************************

#endif //USART_H
