OBJS:=main.o print.o
ELF:=main
$(ELF):$(OBJS)
	gcc $^ -o $@
main.o:main.c
	gcc -c $^
print.o:print.c
	gcc -c $^
.PYONY:clean
clean:
	rm -rf $(OBJS) $(ELF) 
