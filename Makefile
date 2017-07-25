TARGET=cp2102det
OBJS=main.o
CFLAGS=`pkg-config --cflags libusb-1.0`
LDFLAGS=`pkg-config --libs libusb-1.0`


$(TARGET): $(OBJS)
	$(CC) -o $@ $(LDFLAGS) $^