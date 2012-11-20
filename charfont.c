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
#include "charfont.h"
#include "common.h"

//************************************************************************************************
// Defaults for non-printable ASCII characters. Override in charfont.h
//************************************************************************************************
// Control chars
#ifndef CHAR_00
    #define CHAR_00  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_01
    #define CHAR_01  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_02
    #define CHAR_02  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_03
    #define CHAR_03  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_04
    #define CHAR_04  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_05
    #define CHAR_05  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_06
    #define CHAR_06  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_07
    #define CHAR_07  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_08
    #define CHAR_08  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_09
    #define CHAR_09  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_0A
    #define CHAR_0A  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_0B
    #define CHAR_0B  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_0C
    #define CHAR_0C  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_0D
    #define CHAR_0D  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_0E
    #define CHAR_0E  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_0F
    #define CHAR_0F  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_10
    #define CHAR_10  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_11
    #define CHAR_11  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_12
    #define CHAR_12  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_13
    #define CHAR_13  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_14
    #define CHAR_14  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_15
    #define CHAR_15  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_16
    #define CHAR_16  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_17
    #define CHAR_17  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_18
    #define CHAR_18  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_19
    #define CHAR_19  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_1A
    #define CHAR_1A  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_1B
    #define CHAR_1B  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_1C
    #define CHAR_1C  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_1D
    #define CHAR_1D  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_1E
    #define CHAR_1E  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_1F
    #define CHAR_1F  BLANKCHAR_ALLSET
#endif

// High chars
#ifndef CHAR_80
    #define CHAR_80  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_81
    #define CHAR_81  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_82
    #define CHAR_82  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_83
    #define CHAR_83  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_84
    #define CHAR_84  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_85
    #define CHAR_85  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_86
    #define CHAR_86  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_87
    #define CHAR_87  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_88
    #define CHAR_88  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_89
    #define CHAR_89  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_8A
    #define CHAR_8A  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_8B
    #define CHAR_8B  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_8C
    #define CHAR_8C  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_8D
    #define CHAR_8D  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_8E
    #define CHAR_8E  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_8F
    #define CHAR_8F  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_90
    #define CHAR_90  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_91
    #define CHAR_91  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_92
    #define CHAR_92  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_93
    #define CHAR_93  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_94
    #define CHAR_94  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_95
    #define CHAR_95  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_96
    #define CHAR_96  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_97
    #define CHAR_97  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_98
    #define CHAR_98  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_99
    #define CHAR_99  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_9A
    #define CHAR_9A  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_9B
    #define CHAR_9B  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_9C
    #define CHAR_9C  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_9D
    #define CHAR_9D  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_9E
    #define CHAR_9E  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_9F
    #define CHAR_9F  BLANKCHAR_ALLSET
#endif
// End of high control chars

#ifndef CHAR_A0
    #define CHAR_A0  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_A1
    #define CHAR_A1  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_A2
    #define CHAR_A2  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_A3
    #define CHAR_A3  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_A4
    #define CHAR_A4  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_A5
    #define CHAR_A5  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_A6
    #define CHAR_A6  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_A7
    #define CHAR_A7  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_A8
    #define CHAR_A8  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_A9
    #define CHAR_A9  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_AA
    #define CHAR_AA  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_AB
    #define CHAR_AB  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_AC
    #define CHAR_AC  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_AD
    #define CHAR_AD  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_AE
    #define CHAR_AE  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_AF
    #define CHAR_AF  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_B0
    #define CHAR_B0  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_B1
    #define CHAR_B1  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_B2
    #define CHAR_B2  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_B3
    #define CHAR_B3  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_B4
    #define CHAR_B4  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_B5
    #define CHAR_B5  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_B6
    #define CHAR_B6  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_B7
    #define CHAR_B7  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_B8
    #define CHAR_B8  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_B9
    #define CHAR_B9  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_BA
    #define CHAR_BA  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_BB
    #define CHAR_BB  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_BC
    #define CHAR_BC  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_BD
    #define CHAR_BD  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_BE
    #define CHAR_BE  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_BF
    #define CHAR_BF  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_C0
    #define CHAR_C0  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_C1
    #define CHAR_C1  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_C2
    #define CHAR_C2  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_C3
    #define CHAR_C3  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_C4
    #define CHAR_C4  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_C5
    #define CHAR_C5  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_C6
    #define CHAR_C6  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_C7
    #define CHAR_C7  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_C8
    #define CHAR_C8  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_C9
    #define CHAR_C9  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_CA
    #define CHAR_CA  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_CB
    #define CHAR_CB  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_CC
    #define CHAR_CC  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_CD
    #define CHAR_CD  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_CE
    #define CHAR_CE  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_CF
    #define CHAR_CF  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_D0
    #define CHAR_D0  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_D1
    #define CHAR_D1  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_D2
    #define CHAR_D2  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_D3
    #define CHAR_D3  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_D4
    #define CHAR_D4  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_D5
    #define CHAR_D5  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_D6
    #define CHAR_D6  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_D7
    #define CHAR_D7  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_D8
    #define CHAR_D8  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_D9
    #define CHAR_D9  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_DA
    #define CHAR_DA  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_DB
    #define CHAR_DB  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_DC
    #define CHAR_DC  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_DD
    #define CHAR_DD  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_DE
    #define CHAR_DE  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_DF
    #define CHAR_DF  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_E0
    #define CHAR_E0  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_E1
    #define CHAR_E1  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_E2
    #define CHAR_E2  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_E3
    #define CHAR_E3  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_E4
    #define CHAR_E4  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_E5
    #define CHAR_E5  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_E6
    #define CHAR_E6  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_E7
    #define CHAR_E7  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_E8
    #define CHAR_E8  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_E9
    #define CHAR_E9  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_EA
    #define CHAR_EA  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_EB
    #define CHAR_EB  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_EC
    #define CHAR_EC  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_ED
    #define CHAR_ED  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_EE
    #define CHAR_EE  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_EF
    #define CHAR_EF  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_F0
    #define CHAR_F0  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_F1
    #define CHAR_F1  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_F2
    #define CHAR_F2  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_F3
    #define CHAR_F3  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_F4
    #define CHAR_F4  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_F5
    #define CHAR_F5  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_F6
    #define CHAR_F6  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_F7
    #define CHAR_F7  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_F8
    #define CHAR_F8  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_F9
    #define CHAR_F9  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_FA
    #define CHAR_FA  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_FB
    #define CHAR_FB  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_FC
    #define CHAR_FC  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_FD
    #define CHAR_FD  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_FE
    #define CHAR_FE  BLANKCHAR_ALLSET
#endif
#ifndef CHAR_FF
    #define CHAR_FF  BLANKCHAR_ALLSET
#endif

//************************************************************************************************

const uint8_t chars8x8[8*256] PROGMEM =
{
    CHAR_00
    CHAR_01
    CHAR_02
    CHAR_03
    CHAR_04
    CHAR_05
    CHAR_06
    CHAR_07
    CHAR_08
    CHAR_09
    CHAR_0A
    CHAR_0B
    CHAR_0C
    CHAR_0D
    CHAR_0E
    CHAR_0F
    
    CHAR_10
    CHAR_11
    CHAR_12
    CHAR_13
    CHAR_14
    CHAR_15
    CHAR_16
    CHAR_17
    CHAR_18
    CHAR_19
    CHAR_1A
    CHAR_1B
    CHAR_1C
    CHAR_1D
    CHAR_1E
    CHAR_1F
    
	// MARK: start ASCII printables
    // 32: ' '
    BLANKCHAR_ALLCLR
    
    // 33: '!'
    ___O____,// 0
    ___O____,
    ___O____,
    ___O____,
    ___O____,// 4
    ________,
    ___O____,
    ________,
    
    // 34: '"'
    ________,// 0
    ________,
    __O_O___,
    __O_O___,
    ________,// 4
    ________,
    ________,
    ________,
    
    // 35: '#'
    ________,// 0
    __O_O___,
    __O_O___,
    OOOOOOO_,
    __O_O___,// 4
    OOOOOOO_,
    __O_O___,
    __O_O___,
    
    // 36: '$'
    ___O____,// 0
    __OOO___,
    _O_O_O__,
    __OO____,
    ___OO___,// 4
    _O_O_O__,
    __OOO___,
    ___O____,
    
    // 37: '%'
    ________,// 0
    _O____O_,
    O_O__O__,
    _O__O___,
    ___O____,// 4
    __O__O__,
    _O__O_O_,
    O____O__,
    
    // 38: '&'
    ________,// 0
    __O_____,
    _O_O____,
    __O_____,
    _O_O____,// 4
    O___O_O_,
    O____O__,
    _OOOO_O_,
    
    // 39: '''
    ________,// 0
    ________,
    ___O____,
    ___O____,
    ________,// 4
    ________,
    ________,
    ________,
    
    // 40: '('
    ________,// 0
    ___O____,
    __O_____,
    __O_____,
    __O_____,// 4
    __O_____,
    __O_____,
    ___O____,
    
    // 41: ')'
    ________,// 0
    __O_____,
    ___O____,
    ___O____,
    ___O____,// 4
    ___O____,
    ___O____,
    __O_____,
    
    // 42: '*'
    ________,// 0
    ___O____,
    _O_O_O__,
    __OOO___,
    _OOOOO__,// 4
    __OOO___,
    _O_O_O__,
    ___O____,
    
    // 43: '+'
    ________,// 0
    ________,
    ___O____,
    ___O____,
    _OOOOO__,// 4
    ___O____,
    ___O____,
    ________,
    
    // 44: ','
    ________,// 0
    ________,
    ________,
    ________,
    _OO_____,// 4
    _OO_____,
    __O_____,
    _O______,
    
    // 45: '-'
    ________,// 0
    ________,
    ________,
    ________,
    _OOOOO__,// 4
    ________,
    ________,
    ________,
    
    // 46: '.'
    ________,// 0
    ________,
    ________,
    ________,
    ________,// 4
    ________,
    __OO____,
    __OO____,
    
    // 47: '/'
    ________,// 0
    ________,
    _____OO_,
    ____OO__,
    ___OO___,// 4
    __OO____,
    _OO_____,
    ________,
    
	// MARK: start digits
    // 48: '0'
    __OOOO__,// 0
    _O____O_,
    _O___OO_,
    _O__O_O_,
    _O_O__O_,// 4
    _OO___O_,
    _O____O_,
    __OOOO__,
    
    // 49: '1'
    ___O____,// 0
    __OO____,
    ___O____,
    ___O____,
    ___O____,// 4
    ___O____,
    ___O____,
    __OOO___,
    
    // 50: '2'
    __OOOO__,// 0
    _O____O_,
    ______O_,
    _____OO_,
    ____OO__,// 4
    ___OO___,
    __OO____,
    _OOOOOO_,
    
    // 51: '3'
    __OOOO__,// 0
    _O____O_,
    ______O_,
    ___OOO__,
    ______O_,// 4
    ______O_,
    _O____O_,
    __OOOO__,
    
    // 52: '4'
    _O___O__,// 0
    _O___O__,
    _O___O__,
    _OOOOOO_,
    _____O__,// 4
    _____O__,
    _____O__,
    _____O__,
    
    // 53: '5'
    _OOOOO__,// 0
    _O______,
    _O______,
    _OOOOO__,
    ______O_,// 4
    ______O_,
    _O____O_,
    __OOOO__,
    
    // 54: '6'
    ___OOO__,// 0
    __O_____,
    _O______,
    _O_OOO__,
    _OO___O_,// 4
    _O____O_,
    _O____O_,
    __OOOO__,
    
    // 55: '7'
    _OOOOOO_,// 0
    ______O_,
    ______O_,
    _____O__,
    ____O___,// 4
    ___O____,
    ___O____,
    ___O____,
    
    // 56: '8'
    __OOOO__,// 0
    _O____O_,
    _O____O_,
    __OOOO__,
    _O____O_,// 4
    _O____O_,
    _O____O_,
    __OOOO__,
    
    // 57: '9'
//    __OOOO__,// 0
//    _O____O_,
//    _O____O_,
//    __OOOOO_,
//    ______O_,// 4
//    ______O_,
//    _____O__,
//    ___OO___,
    __OOOO__,// 0
    _O____O_,
    _O____O_,
    _O____O_,
    __OOOOO_,// 4
    ______O_,
    _____O__,
    ___OO___,
    
    // 58: ':'
    ________,// 0
    ___OO___,
    ___OO___,
    ________,
    ________,// 4
    ________,
    ___OO___,
    ___OO___,
    
    // 59: ';'
    __OO____,// 0
    __OO____,
    ________,
    ________,
    __OO____,// 4
    __OO____,
    ___O____,
    __O_____,
    
    // 60: '<'
    ________,// 0
    ________,
    ___O____,
    __O_____,
    _O______,// 4
    __O_____,
    ___O____,
    ________,
    
    // 61: '='
    ________,// 0
    ________,
    ________,
    _OOOOO__,
    ________,// 4
    _OOOOO__,
    ________,
    ________,
    
    // 62: '>'
    ________,// 0
    ________,
    __O_____,
    ___O____,
    ____O___,// 4
    ___O____,
    __O_____,
    ________,
    
    // 63: '?'
    __OOOO__,// 0
    _O____O_,
    ______O_,
    ____OO__,
    ___O____,// 4
    ___O____,
    ________,
    ___O____,
    
    // 64: '@'
    __OOO___,// 0
    _O___O__,
    O__O__O_,
    O_O_O_O_,
    O_O_O_O_,// 4
    O__OOOO_,
    _O______,
    __OOOO__,
    
	// MARK: start alphabet, UPPER CASE
    // 65: 'A'
    ___O____,// 0
    __O_O___,
    __O_O___,
    _O___O__,
    _OOOOO__,// 4
    _O___O__,
    O_____O_,
    O_____O_,
    
    // 66: 'B'
    _OOOO___,// 0
    _O___O__,
    _O___O__,
    _OOOO___,
    _O___O__,// 4
    _O____O_,
    _O____O_,
    _OOOOO__,
    
    // 67: 'C'
    __OOO___,// 0
    _O___O__,
    O_____O_,
    O_______,
    O_______,// 4
    O_____O_,
    _O___O__,
    __OOO___,
    
    // 68: 'D'
    OOOOO___,// 0
    O____O__,
    O_____O_,
    O_____O_,
    O_____O_,// 4
    O_____O_,
    O____O__,
    OOOOO___,
    
    // 69: 'E'
    _OOOOOO_,// 0
    _O______,
    _O______,
    _O______,
    _OOOOO__,// 4
    _O______,
    _O______,
    _OOOOOO_,
    
    // 70: 'F'
    _OOOOOO_,// 0
    _O______,
    _O______,
    _OOOOO__,
    _O______,// 4
    _O______,
    _O______,
    _O______,
    
    // 71: 'G'
    __OOO___,// 0
    _O___O__,
    O_____O_,
    O_______,
    O___OOO_,// 4
    O_____O_,
    _O___O__,
    __OOO___,
    
    // 72: 'H'
    _O____O_,// 0
    _O____O_,
    _O____O_,
    _O____O_,
    _OOOOOO_,// 4
    _O____O_,
    _O____O_,
    _O____O_,
    
    // 73: 'I'
    _OOOOO__,// 0
    ___O____,
    ___O____,
    ___O____,
    ___O____,// 4
    ___O____,
    ___O____,
    _OOOOO__,
    
    // 74: 'J'
    _OOOOOO_,// 0
    ____O___,
    ____O___,
    ____O___,
    ____O___,// 4
    ____O___,
    O___O___,
    _OOO____,
    
    // 75: 'K'
    _O____O_,// 0
    _O___O__,
    _O__O___,
    _OOO____,
    _OOO____,// 4
    _O_OO___,
    _O__OO__,
    _O___OO_,
    
    // 76: 'L'
    _O______,// 0
    _O______,
    _O______,
    _O______,
    _O______,// 4
    _O______,
    _O______,
    _OOOOOO_,
    
    // 77: 'M'
    O_____O_,// 0
    OO___OO_,
    O_O_O_O_,
    O_O_O_O_,
    O__O__O_,// 4
    O_____O_,
    O_____O_,
    O_____O_,
    
    // 78: 'N'
    O_____O_,// 0
    OO____O_,
    O_O___O_,
    O__O__O_,
    O___O_O_,// 4
    O____OO_,
    O_____O_,
    O_____O_,
    
    // 79: 'O'
    __OOO___,// 0
    _O___O__,
    O_____O_,
    O_____O_,
    O_____O_,// 4
    O_____O_,
    _O___O__,
    __OOO___,
    
    // 80: 'P'
    _OOOOO__,// 0
    _O____O_,
    _O____O_,
    _OOOOO__,
    _O______,// 4
    _O______,
    _O______,
    _O______,
    
    // 81: 'Q'
    __OOO___,// 0
    _O___O__,
    O_____O_,
    O_____O_,
    O_____O_,// 4
    O___O_O_,
    _O___O__,
    __OOO_O_,
    
    // 82: 'R'
    _OOOOO__,// 0
    _O____O_,
    _O____O_,
    _O____O_,
    _OOOOO__,// 4
    _O__O___,
    _O___O__,
    _O____O_,
    
    // 83: 'S'
    __OOOO__,// 0
    _O____O_,
    _O______,
    __OO____,
    ____OO__,// 4
    ______O_,
    _O____O_,
    __OOOO__,
    
    // 84: 'T'
    OOOOOOO_,// 0
    ___O____,
    ___O____,
    ___O____,
    ___O____,// 4
    ___O____,
    ___O____,
    ___O____,
    
    // 85: 'U'
    O_____O_,// 0
    O_____O_,
    O_____O_,
    O_____O_,
    O_____O_,// 4
    O_____O_,
    _O___O__,
    __OOO___,
    
    // 86: 'V'
    _O____O_,// 0
    _O____O_,
    _O____O_,
    __O__O__,
    __O__O__,// 4
    __O__O__,
    ___OO___,
    ___OO___,
    
    // 87: 'W'
    O_____O_,// 0
    O_____O_,
    O_____O_,
    O__O__O_,
    O_O_O_O_,// 4
    O_O_O_O_,
    _O___O__,
    _O___O__,
    
    // 88: 'X'
    _O____O_,// 0
    _O____O_,
    __O__O__,
    __O__O__,
    ___OO___,// 4
    __O__O__,
    _O____O_,
    _O____O_,
    
    // 89: 'Y'
    O_____O_,// 0
    O_____O_,
    _O___O__,
    __O_O___,
    ___O____,// 4
    ___O____,
    ___O____,
    ___O____,
    
    // 90: 'Z'
    _OOOOOO_,// 0
    ______O_,
    _____O__,
    ____O___,
    ___O____,// 4
    __O_____,
    _O______,
    _OOOOOO_,
	// MARK: end alphabet, UPPER CASE
    
    // 91: '['
    __OOO___,// 0
    __O_____,
    __O_____,
    __O_____,
    __O_____,// 4
    __O_____,
    __O_____,
    __OOO___,
    
    // 92: '\'
    ________,// 0
    ________,
    OO______,
    _OO_____,
    __OO____,// 4
    ___OO___,
    ____OO__,
    _____OO_,
    
    // 93: ']'
    __OOO___,// 0
    ____O___,
    ____O___,
    ____O___,
    ____O___,// 4
    ____O___,
    ____O___,
    __OOO___,
    
    // 94: '^'
    ________,// 0
    ___O____,
    __O_O___,
    _O___O__,
    ________,// 4
    ________,
    ________,
    ________,
    
    // 95: '_'
    ________,// 0
    ________,
    ________,
    ________,
    ________,// 4
    ________,
    ________,
    OOOOOOO_,
    
    // 96: '`'
    ________,// 0
    __O_____,
    ___O____,
    ________,
    ________,// 4
    ________,
    ________,
    ________,
    
	// MARK: start alphabet, lower case
    // 97: 'a'
    ________,// 0
    ________,
    ________,
    ___OOO__,
    __O___O_,// 4
    _O____O_,
    _O___OO_,
    __OOO_O_,
    
    // 98: 'b'
    _O______,// 0
    _O______,
    _O______,
    _O_OO___,
    _OO__O__,// 4
    _OO___O_,
    _OO___O_,
    _O_OOO__,
    
    // 99: 'c'
    ________,// 0
    ________,
    ________,
    __OOOO__,
    _O____O_,// 4
    _O______,
    _O____O_,
    __OOOO__,
    
    // 100: 'd'
    ______O_,// 0
    ______O_,
    ______O_,
    __OOOOO_,
    _O____O_,// 4
    _O____O_,
    _O___OO_,
    __OOO_O_,
    
    // 101: 'e'
    ________,// 0
    ________,
    ________,
    __OOOO__,
    _O____O_,// 4
    _OOOOO__,
    _O______,
    __OOOO__,
    
    // 102: 'f'
    ____OO__,// 0
    ___O__O_,
    ___O____,
    _OOOOO__,
    ___O____,// 4
    ___O____,
    ___O____,
    ___O____,
    
    // 103: 'g'
    ________,// 0
    ________,
    ___OOOO_,
    __O___O_,// 4
    __O___O_,
    ___OOO__,
    ______O_,
    ___OOO__,
    
    // 104: 'h'
    __O_____,// 0
    __O_____,
    __O_____,
    __O_OO__,
    __OO__O_,// 4
    __O___O_,
    __O___O_,
    __O___O_,
    
    // 105: 'i'
    ________,// 0
    ___O____,
    ________,
    __OO____,
    ___O____,// 4
    ___O____,
    ___O____,
    __OOO___,
    
    // 106: 'j'
    ____O___,// 0
    ________,
    ___OO___,
    ____O___,
    ____O___,// 4
    ____O___,
    _O__O___,
    __OO____,
    
    // 107: 'k'
    _O______,// 0
    _O______,
    _O______,
    _O__O___,
    _O_O____,// 4
    _OO_____,
    _O_O____,
    _O__O___,
    
    // 108: 'l'
    __OO____,// 0
    ___O____,
    ___O____,
    ___O____,
    ___O____,// 4
    ___O____,
    ___O____,
    ___OO___,
    
    // 109: 'm'
    ________,// 0
    ________,
    ________,
    OOO_OO__,
    O__O__O_,// 4
    O__O__O_,
    O__O__O_,
    O__O__O_,
    
    // 110: 'n'
    ________,// 0
    ________,
    ________,
    _O_OOO__,
    _OO___O_,// 4
    _O____O_,
    _O____O_,
    _O____O_,
    
    // 111: 'o'
    ________,// 0
    ________,
    ________,
    __OOOO__,
    _O____O_,// 4
    _O____O_,
    _O____O_,
    __OOOO__,
    
    // 112: 'p'
    ________,// 0
    _OOOO___,
    _O___O__,
    _O___O__,
    _O___O__,// 4
    _OOOO___,
    _O______,
    _O______,
    
    // 113: 'q'
    ________,// 0
    __OOOO__,
    _O___O__,
    _O___O__,
    _O___O__,// 4
    __OOOO__,
    _____O__,
    _____OO_,
    
    // 114: 'r'
    ________,// 0
    ________,
    ________,
    _O_OOO__,
    _OO___O_,// 4
    _O______,
    _O______,
    _O______,
    
    // 115: 's'
    ________,// 0
    ________,
    ________,
    __OOOO__,
    _O______,// 4
    __OOOO__,
    ______O_,
    _OOOOO__,
    
    // 116: 't'
    ___O____,// 0
    ___O____,
    _OOOOO__,
    ___O____,
    ___O____,// 4
    ___O____,
    ___O____,
    ___OO___,
    
    // 117: 'u'
    ________,// 0
    ________,
    ________,
    _O___O__,
    _O___O__,// 4
    _O___O__,
    _O__OO__,
    __OO_O__,
    
    // 118: 'v'
    ________,// 0
    ________,
    ________,
    _O___O__,
    _O___O__,// 4
    _O___O__,
    __O_O___,
    ___O____,
    
    // 119: 'w'
    ________,// 0
    ________,
    ________,
    O_____O_,
    O__O__O_,// 4
    O_O_O_O_,
    O_O_O_O_,
    _O___O__,
    
    // 120: 'x'
    ________,// 0
    ________,
    ________,
    _O___O__,
    __O_O___,// 4
    ___O____,
    __O_O___,
    _O___O__,
    
    // 121: 'y'
/*	________,// 0
	________,
	_O___O__,
	_O___O__,
	__O_O___,// 4
	___O____,
	__O_____,
	_O______,*/
	________,// 0
	________,
	________,
	_O___O__,
	_O___O__,// 4
	__OOOO__,
	_____O__,
	_OOOO___,
    
    // 122: 'z'
    ________,// 0
    ________,
    ________,
    _OOOOO__,
    ____O___,// 4
    ___O____,
    __O_____,
    _OOOOO__,
	// MARK: end alphabet, lower case
    
    // 123: '{'
    ____OO__,// 0
    ___O____,
    ____O___,
    ___O____,
    ____O___,
    ___O____,
    ____OO__,
    ________,
    
    // 124: '|'
    ___O____,// 0
    ___O____,
    ___O____,
    ___O____,
    ___O____,// 4
    ___O____,
    ___O____,
    ___O____,
    
    // 125: '}'
    __OO____,// 0
    ____O___,
    ___O____,
    ____O___,
    ___O____,// 4
    ____O___,
    __OO____,
    ________,
    
    // 126: '~'
    ________,// 0
    ________,
    _OO___O_,
    OOOOOOO_,
    O___OO__,// 4
    ________,
    ________,
    ________,
    
    // 127: 'delete'
    ________,// 0
    ________,
    __OOOOO_,
    _O_O_OO_,
    O___O_O_,// 4
    _O_O_OO_,
    __OOOOO_,
    ________,
	
	// MARK: end ASCII printables
	// 128-255
    
    CHAR_80
    CHAR_81
    CHAR_82
    CHAR_83
    CHAR_84
    CHAR_85
    CHAR_86
    CHAR_87
    CHAR_88
    CHAR_89
    CHAR_8A
    CHAR_8B
    CHAR_8C
    CHAR_8D
    CHAR_8E
    CHAR_8F
    
    CHAR_90
    CHAR_91
    CHAR_92
    CHAR_93
    CHAR_94
    CHAR_95
    CHAR_96
    CHAR_97
    CHAR_98
    CHAR_99
    CHAR_9A
    CHAR_9B
    CHAR_9C
    CHAR_9D
    CHAR_9E
    CHAR_9F
    
    CHAR_A0
    CHAR_A1
    CHAR_A2
    CHAR_A3
    CHAR_A4
    CHAR_A5
    CHAR_A6
    CHAR_A7
    CHAR_A8
    CHAR_A9
    CHAR_AA
    CHAR_AB
    CHAR_AC
    CHAR_AD
    CHAR_AE
    CHAR_AF
    
    CHAR_B0
    CHAR_B1
    CHAR_B2
    CHAR_B3
    CHAR_B4
    CHAR_B5
    CHAR_B6
    CHAR_B7
    CHAR_B8
    CHAR_B9
    CHAR_BA
    CHAR_BB
    CHAR_BC
    CHAR_BD
    CHAR_BE
    CHAR_BF
    
    CHAR_C0
    CHAR_C1
    CHAR_C2
    CHAR_C3
    CHAR_C4
    CHAR_C5
    CHAR_C6
    CHAR_C7
    CHAR_C8
    CHAR_C9
    CHAR_CA
    CHAR_CB
    CHAR_CC
    CHAR_CD
    CHAR_CE
    CHAR_CF
    
    CHAR_D0
    CHAR_D1
    CHAR_D2
    CHAR_D3
    CHAR_D4
    CHAR_D5
    CHAR_D6
    CHAR_D7
    CHAR_D8
    CHAR_D9
    CHAR_DA
    CHAR_DB
    CHAR_DC
    CHAR_DD
    CHAR_DE
    CHAR_DF
    
    CHAR_E0
    CHAR_E1
    CHAR_E2
    CHAR_E3
    CHAR_E4
    CHAR_E5
    CHAR_E6
    CHAR_E7
    CHAR_E8
    CHAR_E9
    CHAR_EA
    CHAR_EB
    CHAR_EC
    CHAR_ED
    CHAR_EE
    CHAR_EF
    
    CHAR_F0
    CHAR_F1
    CHAR_F2
    CHAR_F3
    CHAR_F4
    CHAR_F5
    CHAR_F6
    CHAR_F7
    CHAR_F8
    CHAR_F9
    CHAR_FA
    CHAR_FB
    CHAR_FC
    CHAR_FD
    CHAR_FE
    CHAR_FF
};

//************************************************************************************************
