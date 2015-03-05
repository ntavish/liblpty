CC = gcc

CFLAGS = -fPIC -Wall -Wextra -Os $(shell pkg-config --cflags lua5.1)
LDFLAGS = -shared $(shell pkg-config --libs lua5.1)
RM = rm -f
TARGET_LIB = liblpty.so

SRCS = liblpty.c
OBJS = $(SRCS:.c=.o) 

$(TARGET_LIB): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ 

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

examples:
	$(MAKE) -C examples/

include $(SRCS:.c=.d)
 
.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d) 