CC      = gcc
CFLAGS  = -Wall -std=gnu99
CFLAGS += `pkg-config --cflags libusb-1.0`
LDLIBS  = `pkg-config --libs libusb-1.0`

all: main

main: main.o

clean:
	rm -f main main.o
