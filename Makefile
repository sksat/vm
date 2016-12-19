TAR	= vm
BIN	= test02.bin
OBJS	= main.o Emulator.o Instruction16.o Instruction32.o
OBJS	+= Gui.o
OBJS	+= device/Device.a

CFLAGS	= -std=c++11 -g
LDFLAGS	= -lglut -lGL
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
	make -C device
	make $(TAR)

run:$(TAR) $(BIN)
	./$(TAR) $(RUNFLAGS)

clean:
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
