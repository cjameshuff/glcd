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

#ifndef CHARFONT_H
#define CHARFONT_H
//************************************************************************************************

#include <avr/pgmspace.h>

#include "stdint.h"
#include "bindefs.h"

// 8x8 pixel character blocks, one row per byte.
// Extended ASCII: ASCII printable characters share codes. If any interaction with serial
// terminals will occur, the first 32 codes should be left as ASCII control codes. The first
// 32 high codes (with bit 0x80 set) can occur as a single-bit error on such a control code,
// and also should be avoided. These codes can be used if needed, though, just be aware of
// their normal meaning.
extern const uint8_t chars8x8[8*256] PROGMEM;

//------------------------------------------------------------------------------------------------

#define BLANKCHAR_ALLSET \
    OOOOOOOO, \
    OOOOOOOO, \
    OOOOOOOO, \
    OOOOOOOO, \
    OOOOOOOO, \
    OOOOOOOO, \
    OOOOOOOO, \
    OOOOOOOO,

//------------------------------------------------------------------------------------------------

#define BLANKCHAR_ALLCLR \
    ________, \
    ________, \
    ________, \
    ________, \
    ________, \
    ________, \
    ________, \
    ________,


//************************************************************************************************
// Custom characters
// TODO: character code assignments are essentially random. Find/design sensible extended codes.
//************************************************************************************************

// Greek letter: Omega
#define CHAR_A0 \
    ________, /*0*/\
    ________, \
    __OOO___, \
    _O___O__, \
    _O___O__, /*4*/\
    __O_O___, \
    _OO_OO__, \
    ________,

#define CHAR_OMEGA (uint8_t)(0xA0)

//------------------------------------------------------------------------------------------------

// Symbol: per-mil
#define CHAR_A1 \
    _O____O_,/* 0*/ \
    O_O__O__, \
    _O__O___, \
    ___O____, \
    __O_____,/* 4*/ \
    _O_O_O__, \
    O_O_O_O_, \
    ___O_O__,

#define CHAR_PERMIL (uint8_t)(0xA1)

//------------------------------------------------------------------------------------------------

// Symbol: infinity
#define CHAR_A2 \
    ________,/*0*/ \
    ________, \
    ________, \
    _OO_OOO_, \
    O__O__O_,/*4*/ \
    OOO_OO__, \
    ________, \
    ________, \

#define CHAR_INF (uint8_t)(0xA2)

//------------------------------------------------------------------------------------------------

// Greek letter: delta
#define CHAR_A3 \
    ________,/*0*/ \
    ________, \
    ___O____, \
    __O_O___, \
    _O___O__,/*4*/ \
    OOOOOOO_, \
    ________, \
    ________,

#define CHAR_DELTA (uint8_t)(0xA3)

//------------------------------------------------------------------------------------------------

    // 4: mu
#define CHAR_A4 \
    ________,/*0*/ \
    ________, \
    ________, \
    _O___O__, \
    _O___O__,/*4*/ \
    _O__OO__, \
    _OOO_O__, \
    _O____O_,
    
    // 5: pi
#define CHAR_A5 \
    ________,/*0*/ \
    ________, \
    ________, \
    _OOOOOO_, \
    __O__O__,/*4*/ \
    __O__O__, \
    __O___O_, \
    ________,
    
    // 6: ^2
#define CHAR_A6 \
    _OO_____,/*0*/ \
    O__O____, \
    __O_____, \
    OOOO____, \
    ________,/*4*/ \
    ________, \
    ________, \
    ________,
    
    // 7: degree
#define CHAR_A7 \
    __OO____,/*0*/ \
    _O__O___, \
    _O__O___, \
    __OO____, \
    ________,/*4*/ \
    ________, \
    ________, \
    ________,
    
    // 8: hollowcircle
#define CHAR_A8 \
    ________,/*0*/ \
    __OOO___, \
    _O___O__, \
    O_____O_, \
    O_____O_,/*4*/ \
    O_____O_, \
    _O___O__, \
    __OOO___,
    
    // 9: filledcircle
#define CHAR_A9 \
    ________,/*0*/ \
    __OOO___, \
    _OOOOO__, \
    OOOOOOO_, \
    OOOOOOO_,/*4*/ \
    OOOOOOO_, \
    _OOOOO__, \
    __OOO___,
    
    // 10: bullseye target
#define CHAR_AA \
    ________,/*0*/ \
    __OOO___, \
    _O___O__, \
    O__O__O_, \
    O_OOO_O_,/*4*/ \
    O__O__O_, \
    _O___O__, \
    __OOO___,
    
    // 11: smallcircle
#define CHAR_AB \
    ________,/*0*/ \
    ________, \
    __OOO___, \
    _O___O__, \
    _O___O__,/*4*/ \
    _O___O__, \
    __OOO___, \
    ________,
    
    // 12: '<<'
#define CHAR_AC \
    ________,/*0*/ \
    ________, \
    ___O__O_, \
    __O__O__, \
    _O__O___,/*4*/ \
    __O__O__, \
    ___O__O_, \
    ________,
    
    // 13: '>>'
#define CHAR_AD \
    ________,/*0*/ \
    ________, \
    _O__O___, \
    __O__O__, \
    ___O__O_,/*4*/ \
    __O__O__, \
    _O__O___, \
    ________,
    
    // 14: bigX
#define CHAR_AE \
    O______O,/*0*/ \
    _O____O_, \
    __O__O__, \
    ___OO___, \
    ___OO___,/*4*/ \
    __O__O__, \
    _O____O_, \
    O______O,
    
    // 15: box
#define CHAR_AF \
    OOOOOOO_,/*0*/ \
    O_____O_, \
    O_____O_, \
    O_____O_, \
    O_____O_,/*4*/ \
    O_____O_, \
    O_____O_, \
    OOOOOOO_,

// Cursor character
#define CHAR_FF \
    OOOOOOOO, \
    OOOOOOOO, \
    OOOOOOOO, \
    OOOOOOOO, \
    OOOOOOOO, \
    OOOOOOOO, \
    OOOOOOOO, \
    OOOOOOOO,

#define CHAR_CURSOR (uint8_t)(0xFF)

//************************************************************************************************
#endif // CHARFONT_H
