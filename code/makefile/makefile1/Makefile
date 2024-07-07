ELF:=main
OBJS:=main.o func.o
$(ELF):$(OBJS)
	gcc $(OBJS) -o $(ELF)
main.o:main.c
	gcc -c main.c
func.o:func.c
	gcc -c func.c
.PHONY:clean
clean:
	rm -rf $(OBJS) $(ELF)
