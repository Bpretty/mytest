#OBJS = self.o main.o
#main:$(OBJS)
#self.o:self.h
#main.o:main.h self.h
.PHONY:clean all
all:
	#g++ *.c -o main -I include -I include/extern  -L libs -Wl,-rpath=./libs -std=c++11
	g++ *.c -o main -I include  -L libs -Wl,-rpath=./libs -std=c++11
clean:
	rm -rf main *.o
