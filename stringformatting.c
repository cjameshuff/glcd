

#include "stringformatting.h"


//------------------------------------------------------------------------------------------------

void STRF_WriteString(char * bfr, const char * str)
{
	while(*str != '\0')
		*bfr++ = *str++;
}

//------------------------------------------------------------------------------------------------

void STRF_WriteString_P(char * bfr, const prog_char * str)
{
	while(pgm_read_byte(str) != '\0')
		*bfr++ = pgm_read_byte(str++);
}

//------------------------------------------------------------------------------------------------

void STRF_WriteHex4(char * bfr, uint8_t val)
{
	if(val < 10)
		*bfr = '0' + val;
	else
		*bfr = 'A' + val - 10;
}

//------------------------------------------------------------------------------------------------

void STRF_WriteHex8(char * bfr, uint8_t val)
{
    STRF_WriteHex4(bfr, (val >> 4) & 0x0F);
    STRF_WriteHex4(bfr + 1, val & 0x0F);
}

//------------------------------------------------------------------------------------------------

void STRF_WriteHexUInt8(char * bfr, uint8_t val)
{
    bfr[0] = '0';
    bfr[1] = 'x';
	STRF_WriteHex8(bfr + 2, val);
}

//------------------------------------------------------------------------------------------------

void STRF_WriteHexUInt16(char * bfr, uint16_t val)
{
    bfr[0] = '0';
    bfr[1] = 'x';
	STRF_WriteHex8(bfr + 2, (val >> 8) & 0xFF);
	STRF_WriteHex8(bfr + 4, val & 0xFF);
}

//------------------------------------------------------------------------------------------------

void STRF_WriteUInt16(char * bfr, uint8_t digits, uint16_t val)
{
    if(val == 0) {
        --digits;
        bfr[digits] = '0';
		while(digits-- != 0)
			bfr[digits] = ' ';
		return;
	}
	
    while(--digits != 0 && val) {
        bfr[digits] = '0' + val % 10;
        val /= 10;
    }
    
    if(digits) {
        while(--digits != 0)
            bfr[digits] = ' ';
    }
    
    if(val > 9)
        bfr[0] = '?';
    else if(val > 0)
        bfr[0] = '0' + val;
    else
        bfr[0] = ' ';
}

//------------------------------------------------------------------------------------------------

void STRF_WriteUInt32(char * bfr, uint8_t digits, uint32_t val)
{
    if(val == 0) {
        --digits;
        bfr[digits] = '0';
		while(digits-- != 0)
			bfr[digits] = ' ';
		return;
	}
	
    while(--digits != 0 && val) {
        bfr[digits] = '0' + val % 10;
        val /= 10;
    }
    
    if(digits) {
        while(--digits != 0)
            bfr[digits] = ' ';
    }
    
    if(val > 9)
        bfr[0] = '?';
    else if(val > 0)
        bfr[0] = '0' + val;
    else
        bfr[0] = ' ';
}

//------------------------------------------------------------------------------------------------

#if(FIXPOINT_FORMATTING)

void STRF_WriteFix16(char * bfr, uint8_t digits, uint16_t val)
{
}

void STRF_WriteFix32(char * bfr, uint8_t digits, uint32_t val)
{
}

#endif // FIXPOINT_FORMATTING

//------------------------------------------------------------------------------------------------

#if(STRF_TEST)
// TODO: real tests
#include <stdio.h>

#define TEST_BUFFER_LENGTH (32)

void ClearBuffer(char * bfr, int pad) {
    for(int j = 0; j < pad; ++j)
        bfr[j] = '=';
    for(int j = pad; j < TEST_BUFFER_LENGTH; ++j)
        bfr[j] = ' ';
}

void PrintBuffer(const char * bfr)
{
    int j, k;
    for(j = 0; j < TEST_BUFFER_LENGTH; ++j) {
        putchar('0' + j % 10);
//        for(k = 0; k < 3 && j < TEST_BUFFER_LENGTH; ++k, ++j)
//            putchar('-');
//        if(j < TEST_BUFFER_LENGTH)
//            putchar('+');
    }
    putchar('\n');
    for(j = 0; j < TEST_BUFFER_LENGTH;) {
        for(k = 0; k < 4; ++k)
            putchar(bfr[j++]);
    }
    putchar('\n');
    for(j = 0; j < TEST_BUFFER_LENGTH; ++j) {
        for(k = 0; k < 4 && j < TEST_BUFFER_LENGTH; ++k, ++j)
            putchar('-');
        if(j < TEST_BUFFER_LENGTH)
            putchar('+');
    }
    putchar('\n');
}

int main()
{
    char buffer[TEST_BUFFER_LENGTH];
    
    printf("Clear buffer:\n");
    ClearBuffer(buffer, 4);
    PrintBuffer(buffer);
    
    printf("\n0-10, width 5:\n");
    for(int j = 0; j < 11; ++j)
    {
        ClearBuffer(buffer, 4);
        STRF_WriteUInt16(buffer + 4, 5, j);
        PrintBuffer(buffer);
    }
    
    printf("\n12345, width 5:\n");
    ClearBuffer(buffer, 4);
    STRF_WriteUInt16(buffer + 4, 5, 12345);
    PrintBuffer(buffer);
    
    printf("\n12345, width 3:\n");
    ClearBuffer(buffer, 4);
    STRF_WriteUInt16(buffer + 4, 3, 12345);
    PrintBuffer(buffer);
    
    printf("\n345, width 5:\n");
    ClearBuffer(buffer, 4);
    STRF_WriteUInt16(buffer + 4, 5,  345);
    PrintBuffer(buffer);
    
    printf("\n345, width 3:\n");
    ClearBuffer(buffer, 4);
    STRF_WriteUInt16(buffer + 4, 3,  345);
    PrintBuffer(buffer);
}

#endif
