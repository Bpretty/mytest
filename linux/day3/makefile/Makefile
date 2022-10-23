main:main.o print.o
	gcc main.o print.o -o main
main.o:main.c
	gcc -c main.c -o main.o
print.o:print.c
	gcc -c print.c -o print.o
.PYONY:clean
clean:
	rm -rf main main.o print.o
