CC         = avr-gcc
OBJCOPY        = avr-objcopy
OBJDUMP        = avr-objdump

CFLAGS        = -g -Wall $(OPTIMIZE) $(DEFS)
LDFLAGS       = -Wl,$(LDSECTION)
# LDSECTION  = --section-start=.text=0x1F000
OPTIMIZE   = -O2
DEFS       = -DBAUD_RATE=57600 -DWATCHDOG_MODS -DLED_DDR=DDRB -DLED_PORT=PORTB -DLED_PIN=PINB -DLED=PINB7 -DMAX_TIME_COUNT='F_CPU>>1' -DADABOOT

# Don't change these default values here. Add new targets below.
MCU_TARGET = atmega1284p
F_CPU = 16000000L
MHZ = 16MHz

ifeq ($(MCU_TARGET), atmega644p)
# (Untested)
LDSECTION  = --section-start=.text=0xF000
endif
ifeq ($(MCU_TARGET), atmega1284p)
LDSECTION  = --section-start=.text=0x1F000
endif
ifeq ($(LDSECTION),)
$(error LDSECTION must be defined)
endif

# .PHONY : all
all : atmega1284p_8MHz atmega1284p_12MHz atmega1284p_16MHz atmega1284p_20MHz \
atmega644p_8MHz atmega644p_12MHz atmega644p_16MHz atmega644p_20MHz 
	$(foreach target, $?, $(MAKE) $(target);)
	$(MAKE) clean

.PHONY : atmega1284p_8MHz
atmega1284p_8MHz : F_CPU = 8000000L
atmega1284p_8MHz : MHZ = 8MHz
atmega1284p_8MHz : common_bootloader

.PHONY : atmega1284p_12MHz
atmega1284p_12MHz : F_CPU = 12000000L
atmega1284p_12MHz : MHZ = 12MHz
atmega1284p_12MHz : common_bootloader

.PHONY : atmega1284p_16MHz
atmega1284p_16MHz : common_bootloader

.PHONY : atmega1284p_20MHz
atmega1284p_20MHz : F_CPU = 20000000L
atmega1284p_20MHz : MHZ = 20MHz
atmega1284p_20MHz : common_bootloader

.PHONY : atmega644p_8MHz
atmega644p_8MHz : MCU_TARGET = atmega644p
atmega644p_8MHz : F_CPU = 8000000L
atmega644p_8MHz : MHZ = 8MHz
atmega644p_8MHz : common_bootloader

.PHONY : atmega644p_12MHz
atmega644p_12MHz : MCU_TARGET = atmega644p
atmega644p_12MHz : F_CPU = 12000000L
atmega644p_12MHz : MHZ = 12MHz
atmega644p_12MHz : common_bootloader

.PHONY : atmega644p_16MHz
atmega644p_16MHz : MCU_TARGET = atmega644p
atmega644p_16MHz : common_bootloader

.PHONY : atmega644p_20MHz
atmega644p_20MHz : MCU_TARGET = atmega644p
atmega644p_20MHz : F_CPU = 20000000L
atmega644p_20MHz : MHZ = 20MHz
atmega644p_20MHz : common_bootloader

.PHONY : common_bootloader
common_bootloader :
	$(MAKE) \
	MCU_TARGET=$(MCU_TARGET) F_CPU=$(F_CPU) MHZ=$(MHZ) \
	$(MCU_TARGET)_$(MHZ).hex

$(MCU_TARGET)_$(MHZ).hex : $(MCU_TARGET)_$(MHZ).elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

$(MCU_TARGET)_$(MHZ).elf : $(MCU_TARGET)_$(MHZ).o
	$(CC) -mmcu=$(MCU_TARGET) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(MCU_TARGET)_$(MHZ).o : ATmegaBOOT.c
	avr-gcc -mmcu=$(MCU_TARGET) -DF_CPU=$(F_CPU) $(CFLAGS) $(LDFLAGS) -c -g -O2 -Wall  ATmegaBOOT.c -o $@

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

%.elf: %.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

%.srec: %.elf
	$(OBJCOPY) -j .text -j .data -O srec $< $@

%.bin: %.elf
	$(OBJCOPY) -j .text -j .data -O binary $< $@

clean:
	$(RM) *.o

realclean: clean
	$(RM) *.elf *.lst *.map *.sym *.lss *.eep *.srec *.bin *.hex

