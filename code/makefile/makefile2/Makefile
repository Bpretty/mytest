ELF:=main
OBJS:=main.o func.o
$(ELF):$(OBJS)
	gcc $^ -o $@
main.o:main.c
	gcc -c $^
func.o:func.c
	gcc -c $^
.PHONY:clean
clean:
	rm -rf $(OBJS) $(ELF)
