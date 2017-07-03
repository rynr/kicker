TARGET = kicker

MCU = attiny20
F_CPU = 16000000UL

OBJS = $(TARGET).o
CC = avr-gcc
CFLAGS = -O -g -Wall -ffreestanding -mmcu=$(MCU)
LDFLAGS = -Wl,-Map,$(TARGET).map
LDLIBS = 

.SUFFIXES: .s .bin .out .hex .srec

#.c.s:
#	$(CC) $(CFLAGS) -S $<
#
#.S.o:
#	$(CC) $(ASFLAGS) -c $<
#
#.o.out:
#	$(CC) $(CFLAGS) -o $@ $<

.out.bin:
	avr-objcopy -O binary $< $@

.out.hex:
	avr-objcopy -O ihex $< $@

.out.srec:
	avr-objcopy -O srec $< $@

all: $(TARGET).bin

$(TARGET).out: $(OBJS)
	$(CC) -o $(TARGET).out $(CFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS)

clean:
	rm -f $(TARGET).o $(TARGET).map $(TARGET).out $(TARGET).bin
