#    Copyright (c) 2010, Christopher James Huff
#    All rights reserved.
#
#    Redistribution and use in source and binary forms, with or without
#    modification, are permitted provided that the following conditions are met:
#        * Redistributions of source code must retain the above copyright
#          notice, this list of conditions and the following disclaimer.
#        * Redistributions in binary form must reproduce the above copyright
#          notice, this list of conditions and the following disclaimer in the
#          documentation and/or other materials provided with the distribution.
#        * Neither the name of the copyright holder nor the names of contributors
#          may be used to endorse or promote products derived from this software
#          without specific prior written permission.
#
#    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
#    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
#    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
#    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
#    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
#    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
#    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# 
#************************************************************************************************
# Makefile
# http://www.gnu.org/software/make/manual/make.html
#
# The makefile expects "listings" and "obj" directories to exist. "make dirs" will create them.
#
# Supported targets:
# make depend (run this if dependencies have changed)
# make
# make hex
# make disasm
# make stats
#
# make erase - erases flash and EEPROM, also done when flash is written
#
# make read_flash
# make write_flash
#
# TODO: change this to use avr-libc fuse API:
# http://www.nongnu.org/avr-libc/user-manual/group__avr__fuse.html
# Read fuses and print to standard output.
# make read_fuses
# make write_fuses
#
# Use the EEMEM attribute to create data in the EEPROM section, or simply
# have the program write it.
# make read_eeprom
# make write_eeprom
#
# make clean

#MCU = attiny15
#MCU = attiny85
#MCU = attiny26
#MCU = attiny861
#MCU = atmega16
MCU = atmega32
#MCU = atmega644

# Uncomment the appropriate definitions for the part being used. Not all parts
# have all fuses. Be careful! Bad fuse settings can be difficult to reverse!
#FUSE=0xFF
#LFUSE=0xEF
#HFUSE=0xC9
LFUSE=0xE0
HFUSE=0xD9
#EFUSE=0xFF

#F_CPU = 16000000
F_CPU = 16257000
#F_CPU = 26824000
#F_CPU = 32000000

#BAUD_RATE = 19200
BAUD_RATE = 38400
#BAUD_RATE = 230400
#BAUD_RATE = 250000

# all C, C++, or assembly source files
# whole program optimizations are only possible if 
SOURCE = main.c glcd.c charfont.c stringformatting.c

INCLUDEDIRS = 

LIBS = -lm

DEFINES = -DF_CPU=$(F_CPU)UL -DBAUD_RATE=$(BAUD_RATE)UL

PROJNAME = graphiclcd

# Compile options
# -mcall-prologues can sometimes help reduce program size at the expense of speed
# TODO: implement --combine -fwhole-program
# -mshort-calls ?
CFLAGS = -std=gnu99 -Wall -g -Os

# Only changes low byte of stack pointer. Use if stack size <256 bytes to save
# a little program space and CPU cycles.
CFLAGS := $(CFLAGS) -mtiny-stack

# Small types
CFLAGS := $(CFLAGS) -fpack-struct -fshort-enums -funsigned-bitfields -funsigned-char

# Break things up into sections so --gc-sections in LDFLAGS can omit unused data and code
#  WILL BLOW AWAY EEPROM AND FUSE SECTIONS!
#CFLAGS := $(CFLAGS) -ffunction-sections -fdata-sections

CFLAGS := -mmcu=$(MCU) $(CFLAGS) $(DEFINES) $(INCLUDES) $(INCLUDEDIRS)

CPPFLAGS = $(CFLAGS) -fno-exceptions

ASMFLAGS = -mmcu=$(MCU) $(DEFINES) $(INCLUDES) $(INCLUDEDIRS)

# --relax: Relax function calls, allowing shorter, faster call instructions to be used.
# --gc-sections: together with -ffunction-sections and -fdata-sections, better allow unused code
# to be omitted. WILL BLOW AWAY EEPROM AND FUSE SECTIONS!
# Map...: output map file
# --cref: output cross reference information
LDFLAGS = -mmcu=$(MCU)
LDFLAGS := $(LDFLAGS) -Wl,--relax 
#LDFLAGS := $(LDFLAGS) -Wl,--gc-sections 
LDFLAGS := $(LDFLAGS) -Wl,-Map,listings/$(PROJNAME).map
LDFLAGS := $(LDFLAGS) -Wl,--cref


# AVRDUDE options for writeflash, readfuse, etc targets
AVRDUDE = avrdude -c avrispmkII -P usb
CC = avr-gcc
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump
SIZE=avr-size


CSOURCES = $(filter %.c,$(SOURCE))
CPPSOURCES = $(filter %.cpp,$(SOURCE))
ASMSOURCES = $(filter %.S,$(SOURCE))

OBJECTS = $(addprefix obj/, $(CSOURCES:.c=.c.o)) \
          $(addprefix obj/, $(CPPSOURCES:.cpp=.cpp.o)) \
          $(addprefix obj/, $(ASMSOURCES:.S=.S.o))

# there is certainly a better way to do this...
ifdef FUSE
	WRITEFUSES := $(WRITEFUSES) -U fuse:w:$FUSE:m
	READFUSES := $(READFUSES) -U fuse:r:-:h
endif
ifdef LFUSE
	WRITEFUSES := $(WRITEFUSES) -U lfuse:w:$LFUSE:m
	READFUSES := $(READFUSES) -U lfuse:r:-:h
endif
ifdef HFUSE
	WRITEFUSES := $(WRITEFUSES) -U hfuse:w:$HFUSE:m
	READFUSES := $(READFUSES) -U hfuse:r:-:h
endif
ifdef EFUSE
	WRITEFUSES := $(WRITEFUSES) -U efuse:w:$EFUSE:m
	READFUSES := $(READFUSES) -U efuse:r:-:h
endif

ifdef READFUSES
	WRITEFUSES := $(AVRDUDE) -p $(MCU) $(WRITEFUSES)
	READFUSES := $(AVRDUDE) -p $(MCU) $(READFUSES)
else
	WRITEFUSES = @echo error, no fuses set; false
	READFUSES = @echo error, no fuses set; false
endif

# Produce assembly listings, comment out if these are not desired:
LISTINGS = -Wa,-ahlms=$(addprefix listings/, $<.lst)


.PHONY: clean stats dirs read_flash write_flash read_fuses write_fuses read_eeprom write_eeprom
.SUFFIXES : .c .cpp .s .S .h .o .out .hex .ee.hex .fuse.hex

default: $(PROJNAME) Makefile

dirs:
	mkdir obj
	mkdir listings

$(PROJNAME): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $(PROJNAME)


disasm: listings/$(PROJNAME).s

listings/$(PROJNAME).s: $(PROJNAME).out
	$(OBJDUMP) -S  $< > $@


stats: $(PROJNAME).out
	$(OBJDUMP) -h $(PROJNAME).out
	$(SIZE) $(PROJNAME).out


erase: hex
	$(AVRDUDE) -p $(MCU) -e


read_flash:
	$(AVRDUDE) -p $(MCU) -U flash:r:listings/$(PROJNAME).hex:i

write_flash: hex
	$(AVRDUDE) -p $(MCU) -e -U flash:w:$(PROJNAME).hex


read_eeprom:
	$(AVRDUDE) -p $(MCU) -U eeprom:r:listings/$(PROJNAME).ee.hex:i

write_eeprom: hex
	$(AVRDUDE) -p $(MCU) -U eeprom:w:$(PROJNAME).ee.hex


read_fuses:
	$(READFUSES)

write_fuses: hex
	$(WRITEFUSES)


# Hex file output
hex: $(PROJNAME).hex $(PROJNAME).ee.hex $(PROJNAME).fuse.hex

.out.hex:
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

.out.ee.hex:
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@

.out.fuse.hex:
	$(OBJCOPY) -j .fuse --change-section-lma .fuse=0 -O ihex $< $@


# object files
obj/%.c.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LISTINGS)

obj/%.cpp.o: %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@ $(LISTINGS)

obj/%.S.o: %.S
	$(CC) $(ASMFLAGS) -c $< -o $@ $(LISTINGS)


# assembly listings
listings/%.c.s: %.c
	$(CC) -S $(CFLAGS) $< -o $@

listings/%.cpp.s: %.cpp
	$(CC) -S $(CPPFLAGS) $< -o $@

listings/%.s: %.S
	$(CC) -S $(ASMFLAGS) $< -o $@


clean:
	rm -f obj/*
	rm -f listings/*
	rm -f $(PROJNAME)
	rm -f $(PROJNAME).out
	rm -f $(PROJNAME).hex
	rm -f $(PROJNAME).ee.hex
	rm -f $(PROJNAME).fuse.hex


depend:
	# This gives some warnings, but seems to work properly otherwise.
	# Call makedepend with custom suffixes.
	# First call replaces existing dependencies, later calls append to that.
	makedepend -pobj/ -o .c.o -- $(CFLAGS) -- $(CSOURCES)
	makedepend -pobj/ -a -o .cpp.o -- $(CPPFLAGS) -- $(CPPSOURCES)
	makedepend -pobj/ -a -o .S.o -- $(ASMFLAGS) -- $(ASMSOURCES)


# DO NOT DELETE THIS LINE -- makedepend depends on it.

obj/main.c.o: /Users/cjh/avr/avr/include/stdint.h
obj/main.c.o: /Users/cjh/avr/avr/include/ctype.h
obj/main.c.o: /Users/cjh/avr/avr/include/string.h /usr/include/stddef.h
obj/main.c.o: /usr/include/_types.h /usr/include/sys/_types.h
obj/main.c.o: /usr/include/sys/cdefs.h /usr/include/machine/_types.h
obj/main.c.o: /usr/include/i386/_types.h /Users/cjh/avr/avr/include/avr/io.h
obj/main.c.o: /Users/cjh/avr/avr/include/avr/sfr_defs.h
obj/main.c.o: /Users/cjh/avr/avr/include/inttypes.h
obj/main.c.o: /Users/cjh/avr/avr/include/avr/portpins.h
obj/main.c.o: /Users/cjh/avr/avr/include/avr/common.h
obj/main.c.o: /Users/cjh/avr/avr/include/avr/version.h
obj/main.c.o: /Users/cjh/avr/avr/include/avr/fuse.h
obj/main.c.o: /Users/cjh/avr/avr/include/avr/lock.h
obj/main.c.o: /Users/cjh/avr/avr/include/avr/interrupt.h
obj/main.c.o: /Users/cjh/avr/avr/include/util/delay.h
obj/main.c.o: /Users/cjh/avr/avr/include/util/delay_basic.h
obj/main.c.o: /Users/cjh/avr/avr/include/util/crc16.h
obj/main.c.o: /Users/cjh/avr/avr/include/avr/pgmspace.h common.h
obj/main.c.o: stringformatting.h glcd.h charfont.h
obj/glcd.c.o: glcd.h /Users/cjh/avr/avr/include/avr/io.h
obj/glcd.c.o: /Users/cjh/avr/avr/include/avr/sfr_defs.h
obj/glcd.c.o: /Users/cjh/avr/avr/include/inttypes.h
obj/glcd.c.o: /Users/cjh/avr/avr/include/stdint.h
obj/glcd.c.o: /Users/cjh/avr/avr/include/avr/portpins.h
obj/glcd.c.o: /Users/cjh/avr/avr/include/avr/common.h
obj/glcd.c.o: /Users/cjh/avr/avr/include/avr/version.h
obj/glcd.c.o: /Users/cjh/avr/avr/include/avr/fuse.h
obj/glcd.c.o: /Users/cjh/avr/avr/include/avr/lock.h
obj/glcd.c.o: /Users/cjh/avr/avr/include/avr/pgmspace.h /usr/include/stddef.h
obj/glcd.c.o: /usr/include/_types.h /usr/include/sys/_types.h
obj/glcd.c.o: /usr/include/sys/cdefs.h /usr/include/machine/_types.h
obj/glcd.c.o: /usr/include/i386/_types.h common.h charfont.h
obj/charfont.c.o: charfont.h common.h /Users/cjh/avr/avr/include/stdint.h
obj/charfont.c.o: /Users/cjh/avr/avr/include/avr/pgmspace.h
obj/charfont.c.o: /Users/cjh/avr/avr/include/inttypes.h /usr/include/stddef.h
obj/charfont.c.o: /usr/include/_types.h /usr/include/sys/_types.h
obj/charfont.c.o: /usr/include/sys/cdefs.h /usr/include/machine/_types.h
obj/charfont.c.o: /usr/include/i386/_types.h
obj/charfont.c.o: /Users/cjh/avr/avr/include/avr/io.h
obj/charfont.c.o: /Users/cjh/avr/avr/include/avr/sfr_defs.h
obj/charfont.c.o: /Users/cjh/avr/avr/include/avr/portpins.h
obj/charfont.c.o: /Users/cjh/avr/avr/include/avr/common.h
obj/charfont.c.o: /Users/cjh/avr/avr/include/avr/version.h
obj/charfont.c.o: /Users/cjh/avr/avr/include/avr/fuse.h
obj/charfont.c.o: /Users/cjh/avr/avr/include/avr/lock.h bindefs.h
obj/stringformatting.c.o: stringformatting.h common.h
obj/stringformatting.c.o: /Users/cjh/avr/avr/include/stdint.h
obj/stringformatting.c.o: /Users/cjh/avr/avr/include/avr/pgmspace.h
obj/stringformatting.c.o: /Users/cjh/avr/avr/include/inttypes.h
obj/stringformatting.c.o: /usr/include/stddef.h /usr/include/_types.h
obj/stringformatting.c.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
obj/stringformatting.c.o: /usr/include/machine/_types.h
obj/stringformatting.c.o: /usr/include/i386/_types.h
obj/stringformatting.c.o: /Users/cjh/avr/avr/include/avr/io.h
obj/stringformatting.c.o: /Users/cjh/avr/avr/include/avr/sfr_defs.h
obj/stringformatting.c.o: /Users/cjh/avr/avr/include/avr/portpins.h
obj/stringformatting.c.o: /Users/cjh/avr/avr/include/avr/common.h
obj/stringformatting.c.o: /Users/cjh/avr/avr/include/avr/version.h
obj/stringformatting.c.o: /Users/cjh/avr/avr/include/avr/fuse.h
obj/stringformatting.c.o: /Users/cjh/avr/avr/include/avr/lock.h
