CC = gcc
CFLAGS = -O2
RM = rm -f
SRCS = $(wildcard *.c)
PROGS = $(patsubst %.c,%,$(SRCS))

.PHONY: all clean

all: $(PROGS)

%: %.c
	    $(CC) $(CFLAGS) -o ./comp/$@ $<

clean:
	   rm ./comp/*
