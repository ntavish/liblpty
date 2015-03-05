all: usage

usage: usage.c
	gcc -Os -I../ -L../ usage.c `pkg-config --cflags --libs lua5.1` -llpty -o usage

clean:
	rm usage