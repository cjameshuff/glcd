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

#include "glcd.h"


// Character and pixel buffers: read/write from main loop
// 8x9 pixel characters. 7 lines of text, 8 characters per display segment.
// For 3 text + 1 graphics mode, 7x24 = 168 characters and 64x64 = 512 byte image.
char charBfr[GLCD_NUMCHARS];
uint8_t bmpBfr[512];
uint8_t bmpBfr2[512];

// Frame counter is read from main loop, R/W from interrupt/update task
volatile uint8_t frameCtr;

// These are R/W only from interrupt/update task
uint8_t lineCtr;
uint8_t charlineCtr;
uint8_t textlineCtr;

struct {
    bool currentBuffer: 1;
} glcdOpts;

#ifdef GLCD_USE_CURSOR
uint8_t cursorIdx = 0xFF;
uint8_t cursorChar;
#endif

//************************************************************************************************

void InitGLCD(void)
{
    CLR_LP;
    CLR_FR;
	CLR_DCON;
	
	YSCL_DIN_XECL_PORT &= ~(YSCL | DIN | XECL);
	
	XSCL_DATA_PORT &= ~(XSCL | GLCD_DATA);
    
    LP_DDR |= LP;
    FR_DDR |= FR;
    DCON_DDR |= DCON;
	YSCL_DIN_XECL_DDR |= YSCL | DIN | XECL;
    XSCL_DATA_DDR |= XSCL | GLCD_DATA;
}


#ifdef GLCD_USE_CURSOR
void GLCD_SetCursorPos(uint8_t cIdx) {
    if(cursorIdx < GLCD_NUMCHARS)
        charBfr[cursorIdx] = cursorChar;
    
    cursorIdx = cIdx;
    
    if(cursorIdx < GLCD_NUMCHARS)
        cursorChar = charBfr[cursorIdx];
}

void GLCD_SetCursorState(bool state) {
    if(cursorIdx < GLCD_NUMCHARS)
        charBfr[cursorIdx] = (state)? CHAR_CURSOR : cursorChar;
}
#endif

//************************************************************************************************
