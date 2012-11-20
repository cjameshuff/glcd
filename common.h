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

#ifndef COMMON_H
#define COMMON_H

//************************************************************************************************
#include "stdint.h"

typedef uint8_t bool;
#define true (1==1)
#define false (1!=1)

#define delay_ms(n) _delay_ms(n)
#define delay_us(n) _delay_us(n)

#define ldelay_ms(n) do {uint16_t ctr = n; while(ctr-- > 0) _delay_ms(1);} while(0)
#define ldelay_us(n) do {uint16_t ctr = n; while(ctr-- > 0) _delay_us(1);} while(0)

// Some simple unrolled-loop macros
#define DO_2_TIMES(code) do {code code} while(0);
#define DO_3_TIMES(code) do {DO_2_TIMES(code) code} while(0);
#define DO_4_TIMES(code) do {DO_2_TIMES(code) DO_2_TIMES(code)} while(0);
#define DO_8_TIMES(code) do {DO_4_TIMES(code) DO_4_TIMES(code)} while(0);

//************************************************************************************************
#endif // COMMON_H
