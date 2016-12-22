TAR	= sksatlib.a
OBJS	= Bitmap.o

CFLAGS	= -g
CXXFLAGS= -std=c++11 -g

%.o:%.c
	gcc -c $< $(CFLAGS)

%.o:%.cpp
	g++ -c $< $(CXXFLAGS)

default:
	make $(TAR)

clean:
	rm $(TAR)
	rm $(OBJS)

$(TAR):$(OBJS)
	ar rcs $@ $(OBJS)

