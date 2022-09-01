SRCS:=$(wildcard *.c)
OBJS:=$(SRCS:%.c=%.o)
ELF:=client
$(ELF):$(OBJS)
	gcc $^ -o $@
clean:
	rm -rf $(ELF) $(OBJS)
