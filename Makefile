TAR	= vm
OBJS	= main.o Emulator.o Instruction16.o Instruction32.o

CFLAGS	= 
LDFLAGS	= 
RUNFLAGS= test01.bin

CC	= gcc
CXX	= g++

%.o:%.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)

default:
	make $(TAR)

run:$(TAR)
	./$(TAR) $(RUNFLAGS)

clean:
	rm *.o
	rm vm

full:
	make clean
	make

$(TAR):$(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)


