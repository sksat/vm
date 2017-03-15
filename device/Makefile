TAR	= Device.a
OBJS	= Device.o Display.o PIC.o

CFLAGS	= -std=c++11 -g

%.o:%.c
	gcc -c $<

%.o:%.cpp
	g++ -c $< $(CFLAGS)

default:
	make $(TAR)

$(TAR):$(OBJS)
	ar rcs $@ $(OBJS)

clean:
	rm $(TAR)
	rm $(OBJS)

