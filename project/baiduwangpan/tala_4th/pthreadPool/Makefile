SRCS:=$(wildcard *.c)
OBJS:=$(SRCS:%.c=%.o)
ELF:=pthreadPoolServer
$(ELF):$(OBJS)
	gcc $^ -o $@  -I /usr/include/mysql/ -lmysqlclient -lpthread -lcrypt
clean:
	rm -rf $(ELF) $(OBJS)
