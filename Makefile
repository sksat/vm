TAR	= vm
BIN	= test02.bin
#BINSRC	= test03.c

OBJS	= main.o Emulator.o Instruction16.o Instruction32.o ModRM.o
OBJS	+= GUI.o
OBJS	+= sksatlib/sksatlib.a
OBJS	+= device/Device.a
#OBJS	+= GL/lib/libglut.a

CFLAGS	= -std=c++11 -g
LDFLAGS	= -lglut -lGLU -lGL
LDFLAGS += -pthread
RUNFLAGS= $(BIN)

NASK	= ~/tolset/z_tools/nask
CC	= gcc
CXX	= g++

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)

%.bin:%.nask
	$(NASK) $< $@ $*.lst

default:
	make $(BIN)
	make -C sksatlib
	make -C device
	make $(TAR)

run:$(TAR) $(BIN)
	make
	./$(TAR) $(RUNFLAGS)

clean:
	make -C sksatlib clean
	make -C device clean
	rm *.o
	rm vm

full:
	make clean
	make

$(TAR):$(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

device/Device.a:
	make -C device

#$(BIN):$(BINSRC) crt0.asm
#	gcc -nostdlib -fno-asynchronous-unwind-tables -g -fno-stack-protector -c $(BINSRC)	
#	ld --entry=start --oformat=binary -Ttext 0x7c00 -o $@ crt0.o $(BINSRC:.c=.o)

crt0.o:crt0.asm
	nasm -f elf crt0.asm

