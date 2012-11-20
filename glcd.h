//    Copyright (c) 2010, Christopher James Huff <cjameshuff@gmail.com>
//    All rights reserved.
//
//    Redistribution and use in source and binary forms, with or without
//    modification, are permitted provided that the following conditions are met:
//        * Redistributions of source code must retain the above copyright
//          notice, this list of conditions and the following disclaimer.
//        * Redistributions in binary form must reproduce the above copyright
//          notice, this list of conditions and the following disclaimer in the
//          documentation and/or other materials provided with the distribution.
//        * Neither the name of the copyright holder nor the names of contributors
//          may be used to endorse or promote products derived from this software
//          without specific prior written permission.
//
//    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
//    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
//    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
//    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
//************************************************************************************************

#ifndef SHIFTLCD_H
#define SHIFTLCD_H

#include <avr/io.h>
#include <avr/pgmspace.h>
#include "common.h"
#include "charfont.h"


// Epson EG2401 pinout:
// 1: Vdd
// 2: Vss
// 3: Vlcd
// 4: LP Latch pulse signal input (1180 and 1190)
// 5: FR Frame input (1180 and 1190)
// 6: YDIS Display control (1190)
// 7: YSCL Row scan shift clock input (1190)
// 8: DIN Row scan data (1190)
// 9: XSCL Display data shift clock input (1180)
// 10: XECL Enable transition clock input (1180)
// 11: D0 (all 1180)
// 12: D1
// 13: D2
// 14: D3
// 
// SED1180 and SED1190 are essentially shift registers with LCD-drive outputs.
//  FR determines polarity of output
//
// SED1190:
//  LCD LP -> 1190 YSCL (Yes, latch pulse is clock and clock is latch. Don't ask me why.)
//  LCD YSCL -> 1190 LAT
//  LCD YD/DIN -> 1190 DIN
//  LCD YDIS => _INH_
//  1 64-bit shift register drives rows
//	A 1 is latched into the 1190 and shifted along to each row in turn.
//	Data is shifted from latched DIN and along the shift register on the falling edge of LAT
//
// SED1180:
//  4 parallel and interleaved shift registers drive 64 columns
//  4 bits at a time are shifted into a chain of 1180s and shifted along the columns
//  XSCL is shift clock, data is shifted on falling edge
//  ECL "Daisy chain enable clock: the daisy chain enable is propagated on the falling edge of this clock."
//		Enable input is connected to LP. A falling edge on ECL with LP high enables the first controller of
//      the chain, a falling edge on ECL with LP low disables it and enables the next.
//  LP is output latch. Display data is latched on falling edge

// Note: the code makes some assumptions about what ports these are on, particularly
// that XSCL and data are both on the same port, and that YCL, DIN, and XECL share a port.
// Be careful about changing things.

// DCON, FR, LP can go anywhere
// Dot data latch pulse
#define LP_PORT PORTC
#define LP_DDR DDRC
#define LP (1<<PC2)
#define SET_LP LP_PORT |= LP
#define CLR_LP LP_PORT &= ~LP

// Frame signal
// LCD FR, SED1330 WF
// Also used to drive charge pump.
#define FR_PORT PORTC
#define FR_DDR DDRC
#define FR (1<<PC3)
#define SET_FR FR_PORT |= FR
#define CLR_FR FR_PORT &= ~FR

// Display control (YDIS)
#define DCON_PORT PORTC
#define DCON_DDR DDRC
#define DCON (1<<PC4)
#define SET_DCON DCON_PORT |= DCON
#define CLR_DCON DCON_PORT &= ~DCON


// YSCL, DIN, XECL must be on same port
// Y driver shift clock
#define YSCL_DIN_XECL_PORT PORTC
#define YSCL_DIN_XECL_DDR DDRC
#define YSCL (1<<PC5)
#define SET_YSCL YSCL_DIN_XECL_PORT |= YSCL
#define CLR_YSCL YSCL_DIN_XECL_PORT &= ~YSCL

// Scan data
// LCD DIN, SED1330 YD
#define DIN (1<<PC6)
#define SET_DIN YSCL_DIN_XECL_PORT |= DIN
#define CLR_DIN YSCL_DIN_XECL_PORT &= ~DIN

// Chip enable shift clock for Y driver
#define XECL (1<<PC7)
#define SET_XECL YSCL_DIN_XECL_PORT |= XECL
#define CLR_XECL YSCL_DIN_XECL_PORT &= ~XECL
#define STROBE_XECL do {SET_XECL; CLR_XECL;} while(0)


// Data, XSCL must be on same port
// Dot data shift clock for X driver
#define XSCL_DATA_PORT PORTA
#define XSCL_DATA_DDR DDRA
#define XSCL (1<<PA3)
#define GLCD_DATA 0xF0
//#define GLCD_DATA 0x0F

#define SET_XSCL XSCL_DATA_PORT |= XSCL
#define CLR_XSCL XSCL_DATA_PORT &= ~XSCL
#define STROBE_XSCL do {SET_XSCL; CLR_XSCL;} while(0)

// Pins on data/XSCL port not used for LCD should be used for something that
// doesn't mind them being set low.
// Analog inputs are generally in this category, so data is high 4 bits of PORTA,
// XSCL is next highest, and 3 remaining inputs are used for analog inputs.

// If data bits are low bits of port:
//#define SET_DATA_H(data) XSCL_DATA_PORT = (data >> 4);
//#define SET_DATA_H_XSCL(data) XSCL_DATA_PORT = (data >> 4) | XSCL;
//#define SET_DATA_L(data) XSCL_DATA_PORT = (data & 0x0F);
//#define SET_DATA_L_XSCL(data) XSCL_DATA_PORT = (data & 0x0F) | XSCL;
// If high bits of port:
#define SET_DATA_H(data) XSCL_DATA_PORT = (data & 0xF0);
#define SET_DATA_H_XSCL(data) XSCL_DATA_PORT = (data & 0xF0) | XSCL;
#define SET_DATA_L(data) XSCL_DATA_PORT = (data << 4);
#define SET_DATA_L_XSCL(data) XSCL_DATA_PORT = (data << 4) | XSCL;

//************************************************************************************************

#define GLCD_USE_CURSOR


#define GLCD_HEIGHT (64)
#define GLCD_TEXT_HEIGHT (8)
#define GLCD_TEXT_LINE_HEIGHT (GLCD_TEXT_HEIGHT + 1)
#define GLCD_CHAR_LINE_LENGTH (3*8)
#define GLCD_NUMLINES (GLCD_HEIGHT/GLCD_TEXT_LINE_HEIGHT)
#define GLCD_NUMCHARS (GLCD_NUMLINES*GLCD_CHAR_LINE_LENGTH)

#define GLCD_BMPHEIGHT (GLCD_HEIGHT)
#define GLCD_BMPWIDTH (64)
#define GLCD_BMPSIZE (GLCD_BMPHEIGHT*GLCD_BMPWIDTH/8)

//#define GLCD_GRAYSCALE_GFX 0
#define GLCD_GRAYSCALE_GFX 1
//#define GLCD_REFRESH_FREQ (60)
#define GLCD_REFRESH_FREQ (80)

//************************************************************************************************

// These are not fully parameterized based on the above defines, but are set up for a
// 256x64 display with a 64x64 graphics area.
// Customize them to suit your needs instead.
extern char charBfr[GLCD_NUMCHARS];
extern uint8_t bmpBfr[512];
extern uint8_t bmpBfr2[512];

#ifdef GLCD_USE_CURSOR
extern uint8_t cursorIdx;
extern uint8_t cursorChar;
#endif

extern volatile uint8_t frameCtr;
extern uint8_t lineCtr;
extern uint8_t charlineCtr;
extern uint8_t textlineCtr;

//************************************************************************************************

void InitGLCD(void);

// On micros with 2048 B SRAM, each pixel is one bit from SRAM.
static inline void GLCD_DoLineAllRAM(void);

// 7x32 text
static inline void GLCD_DoLine4T(void);

// 7x24 text + 64x64 graphics
static inline void GLCD_DoLine3T1G(void);

#ifdef GLCD_USE_CURSOR
// Cursors are currently implemented by replacing the in-buffer character, saving the character
// that position elsewhere. This avoids additional overhead during rendering, but if the contents
// of the text buffer are to be operated on, make sure the cursor is unset first.
void GLCD_SetCursorPos(uint8_t cIdx);
void GLCD_SetCursorState(bool state);

static inline void GLCD_BlinkCursor(void) {
    if(cursorIdx < GLCD_NUMCHARS)
        charBfr[cursorIdx] = (frameCtr & 0x20)? CHAR_CURSOR : cursorChar;
}
#endif


//************************************************************************************************
// Inlined functions
//************************************************************************************************

// Output a simple bit pattern, low 4 bits repeated over 64 columns.
// Use to efficiently clear large areas.
static inline void DoPatternLineChunk(uint8_t pattern) {
	SET_DATA_L(pattern);
	DO_8_TIMES(STROBE_XSCL; STROBE_XSCL;)
}


static inline void GLCD_StartLine(void)
{
	// It can take varying amounts of time to shift data into the drivers, so
	// latch result of the previous call first thing to avoid timing variations.
	if(lineCtr == 0) {
		// Re-enable first row and latch column outputs.
		SET_LP;
		YSCL_DIN_XECL_PORT |= YSCL | DIN | XECL;
		YSCL_DIN_XECL_PORT &= ~(YSCL | DIN | XECL);
		CLR_LP;
		FR_PORT ^= FR;// toggle FR
	}
	else {
		// Shift to next line, and latch column outputs
		SET_LP;
		YSCL_DIN_XECL_PORT |= YSCL | XECL;
		YSCL_DIN_XECL_PORT &= ~(YSCL | XECL);
		CLR_LP;
	}
    
	if(++lineCtr == GLCD_HEIGHT) {
		lineCtr = 0;
		++frameCtr;
		
        charlineCtr = 0;
        textlineCtr = 0;
    }
	else {
		if(++charlineCtr == GLCD_TEXT_LINE_HEIGHT) {
			charlineCtr = 0;
			++textlineCtr;
		}
	}
}


//   Given the wide variety of ways in which a graphical display can be used, you will
// most likely want to customize GLCD_DoLine() and the associated functions heavily to
// display what you want, where you want it. You may even make multiple customized
// versions of GLCD_DoLine() to achieve multiple display screens without the overhead
// and complexity of a bunch of conditionals.
// 
// Basic display modes:
//   Character: 8x8 characters separated by 1 pixel padding. A trivial modification of
// to use the display line counter instead of the padded character line counter would
// work as an 8x8 sprite mode. Larger characters/sprites are easily possible.
//   It should be entirely possible to do basic antialiasing, using the same trick used
// for grayscale graphics. This will double the flash required for the font, however,
// and increase flicker.
//
//   Graphics: from bitmap in SRAM, as rasterizing even simplistic graphics on the fly
// tends to use too much CPU. Crude grayscale graphics can be achieved by toggling
// between two different bitmaps, at the cost of doubling the already-high SRAM usage.
// If grayscale graphics are enabled, refresh rate also needs to be increased to avoid
// flicker. 80 Hz worked well on my display. Note that the buffers should be switched
// every *two* frames, to avoid effects dependent on drive polarity.
//
//   Data is sent to LCD one 64 column wide segment at a time, one line at a time.
// It's natural to divide the display up by controller, but it would also be fairly
// simple to divide on an 8-column boundary, and only slightly harder to divide on
// a 4-column boundary.
//
// Call GLCD_DoLine() (or a customized version) periodically to draw the display. The
// appropriate call frequency will depend on the size of the display. Ensure that, if
// there are variations in timing of the calls, they at least do not appear consistently
// for certain lines. If some lines are consistently displayed for a shorter or longer
// time than others, contrast will vary between lines. In extreme cases, this can make
// it appear as though lines aren't being drawn at all. It is best to trigger a display
// line refresh from a timer interrupt.

#define DoCharacter8Column()  \
	data = pgm_read_byte(fontdat + (*dataPtr++)*8); \
	SET_DATA_H_XSCL(data); CLR_XSCL; \
	SET_DATA_L_XSCL(data); CLR_XSCL;

#define DoBMP_8Column()  \
    data = *dataPtr++; \
	SET_DATA_H_XSCL(data); CLR_XSCL; \
	SET_DATA_L_XSCL(data); CLR_XSCL;

#define DoCharacterLineChunk()  DO_8_TIMES(DoCharacter8Column())
#define DoCharacterHalfLineChunk()  DO_4_TIMES(DoCharacter8Column())
#define DoBMP_LineChunk()  DO_8_TIMES(DoBMP_8Column())
#define DoBMP_HalfLineChunk()  DO_4_TIMES(DoBMP_8Column())


static inline void GLCD_DoLine3T1G(void)
{
	uint8_t * dataPtr;
	uint8_t data;
    GLCD_StartLine();
    
    // Do text portion: send appropriate line from each character sprite
	if(charlineCtr == GLCD_TEXT_HEIGHT || textlineCtr == GLCD_NUMLINES)
    {
        // for 64 row display, with 8 pixel characters separated by 1 pixel
        // space, last row is blank.
		DoPatternLineChunk(0x00);
		STROBE_XECL;// switch to second controller
		DoPatternLineChunk(0x00);
		STROBE_XECL;// switch to third controller
		DoPatternLineChunk(0x00);
	}
	else
    {
		const prog_uint8_t * fontdat = chars8x8 + charlineCtr;
        dataPtr = (uint8_t*)charBfr + textlineCtr*24;
        DoCharacterLineChunk();
		STROBE_XECL;// switch to second controller
        DoCharacterLineChunk();
        STROBE_XECL;// switch to third controller
        DoCharacterLineChunk();
    }
    
    // Do graphics portion
	STROBE_XECL;// switch to fourth controller
#if(GLCD_GRAYSCALE_GFX)
	// LCD response seems to depend on drive polarity, so only toggle every 2 frames.
	// This increases flicker for gray tones, unfortunately.
	dataPtr = ((frameCtr & 0x02)? bmpBfr : bmpBfr2) + (uint16_t)lineCtr*8;
#else
	dataPtr = ((glcdOpts.currentBuffer)? bmpBfr : bmpBfr2) + (uint16_t)lineCtr*8;
#endif
    DoBMP_LineChunk()
}


static inline void GLCD_DoLine4T(void)
{
	uint8_t * dataPtr;
	uint8_t data;
    GLCD_StartLine();
    
    // Do text portion: send appropriate line from each character sprite
	if(charlineCtr == GLCD_TEXT_HEIGHT || textlineCtr == GLCD_NUMLINES)
    {
        // empty padding line
		DoPatternLineChunk(0x00);
		STROBE_XECL;// switch to second controller
		DoPatternLineChunk(0x00);
		STROBE_XECL;// switch to third controller
		DoPatternLineChunk(0x00);
		STROBE_XECL;// switch to third controller
		DoPatternLineChunk(0x00);
	}
	else
    {
		const prog_uint8_t * fontdat = chars8x8 + charlineCtr;
        dataPtr = (uint8_t*)charBfr + textlineCtr*24;
        DoCharacterLineChunk();
		STROBE_XECL;// switch to second controller
        DoCharacterLineChunk();
        STROBE_XECL;// switch to third controller
        DoCharacterLineChunk();
        STROBE_XECL;// switch to fourth controller
        DoCharacterLineChunk();
    }
}

static inline void GLCD_DoLineAllRAM(void)
{
//	uint8_t * dataPtr = (uint8_t *)((uint16_t)lineCtr*32);// include registers
	uint8_t * dataPtr = (uint8_t *)((uint16_t)lineCtr*32 + 96);// SRAM only
	uint8_t data;
    GLCD_StartLine();
    
    DoBMP_LineChunk()
	STROBE_XECL;// switch to second controller
    DoBMP_LineChunk()
	STROBE_XECL;// switch to third controller
    DoBMP_LineChunk()
	STROBE_XECL;// switch to fourth controller
    DoBMP_LineChunk()
}

//************************************************************************************************
#endif // SHIFTLCD_H
