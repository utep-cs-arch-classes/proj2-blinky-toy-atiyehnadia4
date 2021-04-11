# makfile configuration
COMMON_OBJECTS  = 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../demos/h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: toy.elf

#additional rules for files
toy.elf: ${COMMON_OBJECTS} toyMain.o stateMachines.o led.o wdInterruptHandler.o switches.o buzzer.o p2_interrupt_handler.o ../demos/lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: toy.elf
	msp430loader.sh toy.elf

toyMain.o: toyMain.c

clean:
	rm -f *.o *.elf *.c~ *# *.#

led.o: led.c led.h

wdInterruptHandler.o: stateMachines.h

stateMachines.o: led.h stateMachines.h

switches.o: switches.h switches.c

p2_interrupt_handler.o: p2_interrupt_handler.c

buzzer.o: buzzer.h buzzer.c
