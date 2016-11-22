TAR	= vm
OBJS	= main.o Emulator.o Instruction16.o Instruction32.o

CFLAGS	= 
LDFLAGS	= 
RUNFLAGS= test01.bin

%.o:%.cpp
	g++ -o $@ -c $< $(CFLAGS)

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
	g++ -o $@ $^ $(LDFLAGS)


