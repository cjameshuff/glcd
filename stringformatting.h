
#ifndef STRINGFORMATTING_H
#define STRINGFORMATTING_H

// Define STRF_TEST as 1 and compile as:
// gcc -std=c99 -DSTRF_TEST=1 stringformatting.c -o teststringformatting
// to build tests
#ifndef STRF_TEST
#define STRF_TEST 0
#endif

#define FIXPOINT_FORMATTING 1

#include "common.h"
#if(STRF_TEST)
  typedef char prog_char;
  #define pgm_read_byte(x) (*x)
#else
  #include <avr/pgmspace.h>
#endif // STRF_TEST

// Write null-delimited string, starting at given location. Buffer must
// contain room for string.
void STRF_WriteString(char * bfr, const char * character);
void STRF_WriteString_P(char * bfr, const prog_char * character);

#define STRF_ClearBuffer(bfr, len) memset(lcdBfr, ' ', len)


// Write hex digit (low nybble)
void STRF_WriteHex4(char * bfr, uint8_t val);

// Write pair of hex digits
void STRF_WriteHex8(char * bfr, uint8_t val);

// Write unsigned hex integer of the form 0xFF or 0xFFFF
void STRF_WriteHexUInt8(char * bfr, uint8_t val);
void STRF_WriteHexUInt16(char * bfr, uint16_t val);

// write fixed-width integer value in decimal, right aligned, space padded.
// If number is too large to fit, first digit is replaced with '?' character.
void STRF_WriteUInt16(char * bfr, uint8_t digits, uint16_t val);
void STRF_WriteUInt32(char * bfr, uint8_t digits, uint32_t val);

#if(FIXPOINT_FORMATTING)
void STRF_WriteFix16(char * bfr, uint8_t digits, uint16_t val);
void STRF_WriteFix32(char * bfr, uint8_t digits, uint32_t val);
#endif // FIXPOINT_FORMATTING

#endif // STRINGFORMATTING_H
