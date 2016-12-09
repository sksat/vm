TAR	= Device.a
OBJS	= Device.o Display.o

%.o:%.c
	gcc -c $<

%.o:%.cpp
	g++ -c $<

default:
	make $(TAR)

$(TAR):$(OBJS)
	ar rcs $@ $(OBJS)


