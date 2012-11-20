//    Copyright (c) 2010, Christopher James Huff
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

#include <stdint.h>
#include <ctype.h>
#include <string.h>

#include <avr/io.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/crc16.h>

#include "common.h"
#include "stringformatting.h"
#include "glcd.h"

//************************************************************************************************

FUSES = {
// external crystal
	(FUSE_SUT0), // .low
	(FUSE_CKOPT & FUSE_BOOTSZ0 & FUSE_BOOTSZ1 & FUSE_SPIEN) // .high
// external clock
//	(FUSE_CKSEL0 & FUSE_CKSEL1 & FUSE_CKSEL2 & FUSE_CKSEL3 & FUSE_SUT0), // .low
//	(FUSE_BOOTSZ0 & FUSE_BOOTSZ1 & FUSE_SPIEN) // .high
};


//************************************************************************************************
// Timer/counter 1 definitions for ATmega16, 32, 644, etc
// Action on compare match
#define TCCR1A_NORMAL (0)
#define TCCR1B_NORMAL (0)

#define TCCR1A_OC1A_NC ((0 << COM1A1) | (0 << COM1A0))
#define TCCR1A_OC1A_TOG ((0 << COM1A1) | (1 << COM1A0))
#define TCCR1A_OC1A_CLR ((1 << COM1A1) | (0 << COM1A0))
#define TCCR1A_OC1A_SET ((1 << COM1A1) | (1 << COM1A0))

#define TCCR1A_OC1B_NC ((0 << COM1B1) | (0 << COM1B0))
#define TCCR1A_OC1B_TOG ((0 << COM1B1) | (1 << COM1B0))
#define TCCR1A_OC1B_CLR ((1 << COM1B1) | (0 << COM1B0))
#define TCCR1A_OC1B_SET ((1 << COM1B1) | (1 << COM1B0))

// WGM modes
#define TCCR1A_WGM_NORMAL ((0 << WGM11) | (0 << WGM10))
#define TCCR1B_WGM_NORMAL ((0 << WGM13) | (0 << WGM12))

#define TCCR1A_WGM_PCPWM8 ((0 << WGM11) | (1 << WGM10))
#define TCCR1B_WGM_PCPWM8 ((0 << WGM13) | (0 << WGM12))

#define TCCR1A_WGM_PCPWM9 ((1 << WGM11) | (0 << WGM10))
#define TCCR1B_WGM_PCPWM9 ((0 << WGM13) | (0 << WGM12))

#define TCCR1A_WGM_PCPWM10 ((1 << WGM11) | (1 << WGM10))
#define TCCR1B_WGM_PCPWM10 ((0 << WGM13) | (0 << WGM12))

// Clear on timer compare, top == OCR1A
#define TCCR1A_WGM_CTC_OCR1A ((0 << WGM11) | (0 << WGM10))
#define TCCR1B_WGM_CTC_OCR1A ((0 << WGM13) | (1 << WGM12))

#define TCCR1A_WGM_FPWM8 ((0 << WGM11) | (1 << WGM10))
#define TCCR1B_WGM_FPWM8 ((0 << WGM13) | (1 << WGM12))

#define TCCR1A_WGM_FPWM9 ((1 << WGM11) | (0 << WGM10))
#define TCCR1B_WGM_FPWM9 ((0 << WGM13) | (1 << WGM12))

#define TCCR1A_WGM_FPWM10 ((1 << WGM11) | (1 << WGM10))
#define TCCR1B_WGM_FPWM10 ((0 << WGM13) | (1 << WGM12))

// Phase and frequency correct PWM, top == ICR1
#define TCCR1A_WGM_PFCPWM_ICR1 ((0 << WGM11) | (0 << WGM10))
#define TCCR1B_WGM_PFCPWM_ICR1 ((1 << WGM13) | (0 << WGM12))
// Phase and frequency correct PWM, top == OCR1A
#define TCCR1A_WGM_PFCPWM_OCR1A ((0 << WGM11) | (1 << WGM10))
#define TCCR1B_WGM_PFCPWM_OCR1A ((1 << WGM13) | (0 << WGM12))

// Phase correct PWM, top == ICR1
#define TCCR1A_WGM_PCPWM_ICR1 ((1 << WGM11) | (0 << WGM10))
#define TCCR1B_WGM_PCPWM_ICR1 ((1 << WGM13) | (0 << WGM12))
// Phase correct PWM, top == OCR1A
#define TCCR1A_WGM_PCPWM_OCR1A ((1 << WGM11) | (1 << WGM10))
#define TCCR1B_WGM_PCPWM_OCR1A ((1 << WGM13) | (0 << WGM12))

// Clear on timer compare, top == ICR1
#define TCCR1A_WGM_CTC_ICR1 ((0 << WGM11) | (0 << WGM10))
#define TCCR1B_WGM_CTC_ICR1 ((1 << WGM13) | (1 << WGM12))

// Fast PWM, top == ICR1
#define TCCR1A_WGM_FPWM_ICR1 ((1 << WGM11) | (0 << WGM10))
#define TCCR1B_WGM_FPWM_ICR1 ((1 << WGM13) | (1 << WGM12))

// Fast PWM, top == OCR1A
#define TCCR1A_WGM_FPWM_OCR1A ((1 << WGM11) | (1 << WGM10))
#define TCCR1B_WGM_FPWM_OCR1A ((1 << WGM13) | (1 << WGM12))


// Clock sources
#define TCCR1B_STOP     ((0 << CS12) | (0 << CS11) | (0 << CS10))
#define TCCR1B_CLK      ((0 << CS12) | (0 << CS11) | (1 << CS10))
#define TCCR1B_CLK_8    ((0 << CS12) | (1 << CS11) | (0 << CS10))
#define TCCR1B_CLK_64   ((0 << CS12) | (1 << CS11) | (1 << CS10))
#define TCCR1B_CLK_256  ((1 << CS12) | (0 << CS11) | (0 << CS10))
#define TCCR1B_CLK_1024 ((1 << CS12) | (0 << CS11) | (1 << CS10))
#define TCCR1B_CLK_EXTFALL ((1 << CS12) | (1 << CS11) | (0 << CS10))
#define TCCR1B_CLK_EXTRISE ((1 << CS12) | (1 << CS11) | (1 << CS10))

//************************************************************************************************

//
///* ADMUX */
//#define REFS1   7
//#define REFS0   6
//#define ADLAR   5
//#define MUX4    4
//#define MUX3    3
//#define MUX2    2
//#define MUX1    1
//#define MUX0    0

#define REFS_AREF   ((0 << REFS1) | (0 << REFS0)) // AREF, internal reference off
#define REFS_AVcc   ((0 << REFS1) | (1 << REFS0)) // AVcc, external capacitor on AREF
#define REFS_2_56V  ((1 << REFS1) | (1 << REFS0)) // internal 2.56V reference with ext capacitor

// Single ended inputs
#define MUX_ADC0  (0x00)
#define MUX_ADC1  (0x01)
#define MUX_ADC2  (0x02)
#define MUX_ADC3  (0x03)
#define MUX_ADC4  (0x04)
#define MUX_ADC5  (0x05)
#define MUX_ADC6  (0x06)
#define MUX_ADC7  (0x07)

// Differential inputs. Positive input first, negative input second, then gain.
// "The differential input channels are not tested for devices in PDIP Package.
// This feature is only guaranteed to work for devices in TQFP and QFN/MLF Packages"
#define MUX_ADC_0_0_10x  (0x08)
#define MUX_ADC_1_0_10x  (0x09)
#define MUX_ADC_0_0_200x  (0x0A)
#define MUX_ADC_1_0_200x  (0x0B)
#define MUX_ADC_2_2_10x  (0x0C)
#define MUX_ADC_3_2_10x  (0x0D)
#define MUX_ADC_2_2_200x  (0x0E)
#define MUX_ADC_3_2_200x  (0x0F)
#define MUX_ADC_0_1_1x  (0x10)
#define MUX_ADC_1_1_1x  (0x11)
#define MUX_ADC_2_1_1x  (0x12)
#define MUX_ADC_3_1_1x  (0x13)
#define MUX_ADC_4_1_1x  (0x14)
#define MUX_ADC_5_1_1x  (0x15)
#define MUX_ADC_6_1_1x  (0x16)
#define MUX_ADC_7_1_1x  (0x17)
#define MUX_ADC_0_2_1x  (0x18)
#define MUX_ADC_1_2_1x  (0x19)
#define MUX_ADC_2_2_1x  (0x1A)
#define MUX_ADC_3_2_1x  (0x1B)
#define MUX_ADC_4_2_1x  (0x1C)
#define MUX_ADC_5_2_1x  (0x1D)

#define MUX_ADC_1_22V  (0x1E)
#define MUX_ADC_0V     (0x1F)


// ADCSRA
//#define ADEN    7 // enable ADC
//#define ADSC    6 // start conversion (cleared on completion)
//#define ADATE   5 // auto-trigger enable, trigger selected by ADTS in SFIOR
//#define ADIF    4 // conversion complete interrupt flag
//#define ADIE    3
//#define ADPS2   2
//#define ADPS1   1
//#define ADPS0   0

#define ADPS_2    (0x01)
#define ADPS_4    (0x02)
#define ADPS_8    (0x03)
#define ADPS_16   (0x04)
#define ADPS_32   (0x05)
#define ADPS_64   (0x06)
#define ADPS_128  (0x07)


//************************************************************************************************

const uint8_t sintbl256[256] PROGMEM = {
    127, 130, 133, 136, 139, 143, 146, 149, 152, 155, 158, 161, 164, 167, 170, 173,
    176, 179, 182, 184, 187, 190, 193, 195, 198, 200, 203, 205, 208, 210, 213, 215,
    217, 219, 221, 224, 226, 228, 229, 231, 233, 235, 236, 238, 239, 241, 242, 244,
    245, 246, 247, 248, 249, 250, 251, 251, 252, 253, 253, 254, 254, 254, 254, 254,
    255, 254, 254, 254, 254, 254, 253, 253, 252, 251, 251, 250, 249, 248, 247, 246,
    245, 244, 242, 241, 239, 238, 236, 235, 233, 231, 229, 228, 226, 224, 221, 219,
    217, 215, 213, 210, 208, 205, 203, 200, 198, 195, 193, 190, 187, 184, 182, 179,
    176, 173, 170, 167, 164, 161, 158, 155, 152, 149, 146, 143, 139, 136, 133, 130,
    127, 124, 121, 118, 115, 111, 108, 105, 102,  99,  96,  93,  90,  87,  84,  81,
     78,  75,  72,  70,  67,  64,  61,  59,  56,  54,  51,  49,  46,  44,  41,  39,
     37,  35,  33,  30,  28,  26,  25,  23,  21,  19,  18,  16,  15,  13,  12,  10,
      9,   8,   7,   6,   5,   4,   3,   3,   2,   1,   1,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   1,   1,   2,   3,   3,   4,   5,   6,   7,   8,
      9,  10,  12,  13,  15,  16,  18,  19,  21,  23,  25,  26,  28,  30,  33,  35,
     37,  39,  41,  44,  46,  49,  51,  54,  56,  59,  61,  64,  67,  70,  72,  75,
     78,  81,  84,  87,  90,  93,  96,  99, 102, 105, 108, 111, 115, 118, 121, 124
};

//************************************************************************************************

// XORshift PRNGs
static uint8_t y8 = 1;

// returns values from 1 to 255 inclusive, period is 255
uint8_t xorshift8(void) {
    y8 ^= (y8 << 7);
    y8 ^= (y8 >> 5);
    return y8 ^= (y8 << 3);
//    y8 ^= (y8 << 2);
//    y8 ^= (y8 >> 1);
//    return y8 ^= (y8 << 1);
}
static uint16_t y16 = 1;
// returns values from 1 to 65535 inclusive, period is 65535
uint16_t xorshift16(void) {
    y16 ^= (y16 << 13);
    y16 ^= (y16 >> 9);
    return y16 ^= (y16 << 7);
}

static uint32_t y32 = 1;
uint32_t xorshift32(void) {
    y32 ^= (y32 << 13);
    y32 ^= (y32 >> 17);
    return y32 ^= (y32 << 5);
}

//************************************************************************************************

//uint8_t eepromOpts[] EEMEM = {
//};

volatile struct {
    bool lcdLine: 1;
//    bool lcdLineDrawn: 1;
    bool newFrame: 1;
    bool dconState: 1;
    bool nocpu: 1;
    bool adc_int: 1;
//    bool usrx_int: 1;
} iflags;

volatile uint32_t drawTime = 0;
static uint32_t drawTimeAccum = 0;
static uint8_t graphstep = 0;


//************************************************************************************************

volatile uint8_t adcbfr[256];
volatile uint8_t adcbfrCrsr;

void StartADC()
{
	PORTA &= ~(1 << PA0);
	DDRA &= ~(1 << PA0);
    ADCSRA = (1 << ADEN) | (1 << ADIF) | (1 << ADIE) | ADPS_128;
//    ADMUX = MUX_ADC_1_22V | REFS_2_56V | (1 << ADLAR);
    ADMUX = MUX_ADC0 | REFS_AVcc | (1 << ADLAR);
    ADCSRA = (1 << ADSC) | (1 << ADEN) | (1 << ADIF) | (1 << ADIE) | ADPS_128;
}

void InitADC()
{
    StartADC();
}

//************************************************************************************************

void RenderGraph(void)
{
    // Each line is cleared as it is drawn. The graph is then drawn by setting the appropriate pixels.
    uint8_t x = 0, px = 0, y;
    uint16_t bmpidx;
    do {
        uint8_t bit = 0x80;
//        for(uint8_t k = 0; k < 4; ++k, x += 8, bit >>= 2) {
        for(uint8_t k = 0; k < 8; ++k, x += 4, bit >>= 1) {
            uint8_t idx = x + adcbfrCrsr + 1;
//            uint8_t idx = x + ((adcbfrCrsr + 1) << 2);
//            uint8_t idx = x + graphstep;
            DO_4_TIMES(
                y = 63 - (adcbfr[idx] >> 2);
//                y = 63 - (adcbfr[idx >> 2] >> 2);
//                y = pgm_read_byte(sintbl256 + idx) >> 2;
                bmpidx = (uint16_t)y*8 + px;
                bmpBfr[bmpidx] |= bit;
                bmpBfr2[bmpidx] |= bit;
                ++idx;
            )
            
//            idx += 64;
//            idx = x - graphstep;
//            DO_4_TIMES(
//                y = pgm_read_byte(sintbl256 + idx) >> 2;
//                bmpidx = (uint16_t)y*8 + px;
//                bmpBfr[bmpidx] |= bit;
//                bmpBfr2[bmpidx] |= bit;
//                ++idx;
//            )
        }
        bmpidx = (uint16_t)32*8 + px;
        bmpBfr[bmpidx] |= 0x55;
        bmpBfr2[bmpidx] |= 0xAA;
        bmpidx += 8;
        bmpBfr[bmpidx] |= 0xAA;
        bmpBfr2[bmpidx] |= 0x55;
        
        ++px;
    } while(x);
    
    y = 32;
    bmpidx = 3;
    do {
        bmpBfr[bmpidx] |= 0x01;
        bmpBfr2[bmpidx+1] |= 0x80;
        bmpidx += 8;
        bmpBfr2[bmpidx] |= 0x01;
        bmpBfr[bmpidx+1] |= 0x80;
        bmpidx += 8;
    } while(--y);
}

//************************************************************************************************

int main(void) __attribute__ ((OS_main));
int main(void)
{
    DDRA = 0x00;
    DDRB = 0x00;
    
    InitGLCD();
    
    _delay_ms(100);// wait for power and peripherals to stabilize/reset
    
    //    ####----####----####----
    // 0: Lorem ipsum dolor sit am
    // 1: et, consectetur adipisic
    // 2: ing elit, sed do eiusmod
    // 3: tempor incididunt ut lab
    // 4: ore et dolore magna aliq
    // 5: ua. Ut enim ad minim ven
    // 6: iam, quis nostrud exerci
    // tation ullamco laboris nisi ut aliquip ex ea commodo consequat. 
    // Duis aute irure dolor in reprehenderit in voluptate velit esse
    // cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat
    // cupidatat non proident, sunt in culpa qui officia deserunt mollit
    // anim id est laborum.
    
    for(uint8_t j = 0; j < (7*24); ++j)
        charBfr[j] = ' ';
    for(uint8_t c = 32, j = 24; c < 127; ++c, ++j)
        charBfr[j] = c;
    
//    memcpy_P(charBfr, PSTR(
//      "Lorem ipsum dolor sit am"
//        "et, consectetur adipisic"
//        "ing elit, sed do eiusmod"
//        "tempor incididunt ut lab"
//        "ore et dolore magna aliq"
//        "ua. Ut enim ad minim ven"
//        "iam, quis nostrud exerci"), 7*24);
    
    // Timer is clocked at main clock, non-prescaled.
    // Refresh rate = (16 MHz/8/64/400)
    // line timer ticks/line = (FCPU/64)/refreshHz
#define GLCD_LINE_TICKS ((F_CPU/GLCD_HEIGHT)/GLCD_REFRESH_FREQ)
    TCCR1A = TCCR1A_WGM_CTC_OCR1A;
    TCCR1B = TCCR1B_WGM_CTC_OCR1A | TCCR1B_CLK;
    OCR1A = GLCD_LINE_TICKS;
    TIMSK |= (1 << OCIE1A);
    
    iflags.nocpu = 0;
    iflags.lcdLine = 0;
//    iflags.lcdLineDrawn = 0;
    iflags.dconState = 1;
    SET_DCON;
    
    
    sei();
    
    InitADC();
    
    STRF_WriteString_P(charBfr, PSTR("CPU: "));
    charBfr[8] = CHAR_PERMIL;
    GLCD_SetCursorPos(10);
    
    while(1)
    {
		if(iflags.newFrame)
		{
			iflags.newFrame = 0;
			if((frameCtr & 0x07) == 0) {
				memset(bmpBfr, 0, 512);
				memset(bmpBfr2, 0, 512);
				RenderGraph();
				graphstep += 1;
			}
			GLCD_BlinkCursor();
//                STRF_WriteUInt16(charBfr + (24*6), 3, graphstep);
			STRF_WriteUInt16(charBfr + (24*6), 3, adcbfr[adcbfrCrsr]);
			STRF_WriteUInt16(charBfr + (24*6) + 10, 3, adcbfrCrsr);
			
			if(iflags.nocpu) {
				STRF_WriteString_P(charBfr + 5, PSTR("999"));
				iflags.nocpu = 0;
			}
			else {
				if((frameCtr & 0x1F) == 0) {
					drawTime *= 1000;
					drawTime /= GLCD_LINE_TICKS;
					drawTime /= GLCD_HEIGHT;
					STRF_WriteUInt16(charBfr + 5, 3, drawTime);
				}
				drawTime = 0;
			}
			
//			if(iflags.adc_int && ((frameCtr & 0x07) == 0))
//			if(iflags.adc_int && ((frameCtr & 0x03) == 0))
//			if(iflags.adc_int && ((frameCtr & 0x01) == 0))
			if(iflags.adc_int)
			{
				++adcbfrCrsr;
				//if(++adcbfrCrsr == 64) adcbfrCrsr = 0;
				adcbfr[adcbfrCrsr] = ADCH;
				iflags.adc_int = 0;
				StartADC();
			}
		}
		
//        if(iflags.lcdLineDrawn)
//        {
//            iflags.lcdLineDrawn = 0;
//            
//        }
    }
}

//************************************************************************************************

ISR(TIMER1_COMPA_vect)
{
    if(iflags.lcdLine == 0)
    {
        // Use nested interrupts to achieve a crude form of tasking.
        // iflags.lcdLineDrawn notifies main loop that a line has been drawn
        // iflags.lcdLine avoids recursion of the interrupt, should drawing take longer
        // than a line draw interval for some reason. If recursion occurs, iflags.nocpu
        // is set to indicate the overloaded CPU condition.
        iflags.lcdLine = 1;
        sei();
//        GLCD_DoLineAllRAM();
        GLCD_DoLine3T1G();
        drawTimeAccum += TCNT1;
        if(lineCtr == 0) {
            iflags.newFrame = 1;
            drawTime = drawTimeAccum;
            drawTimeAccum = 0;
        }
//        iflags.lcdLineDrawn = 1;
        cli();
        iflags.lcdLine = 0;
    }
    else {
        iflags.nocpu = 1;
    }
}

//************************************************************************************************

ISR(ADC_vect) {
	iflags.adc_int = 1;
}

//************************************************************************************************

