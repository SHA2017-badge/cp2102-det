#include <errno.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "libusb.h"

void die_usb(char *str, int er) {
	printf("%s: %s\n", str, libusb_strerror(er));
	exit(1);
}


int main(int argc, char **argv) {
	struct libusb_device_handle *devh = NULL;
	int r;
	libusb_context *context;

	r = libusb_init(&context);
	if (r != 0) die_usb("libusb_init", r);

	devh = libusb_open_device_with_vid_pid(NULL, 0x10c4, 0xea60);
//	devh = libusb_open_device_with_vid_pid(NULL, 0, 0xea60);
	if (devh == NULL) perror("libusb_open_device");

	libusb_set_auto_detach_kernel_driver(devh, 1);

	r = libusb_claim_interface(devh, 0);
	if (r != 0) die_usb("libusb_claim", r);

	for (int i = 0x9; i < 0xc; i++) {
		uint8_t data[128];
		memset(data, 0xA5, 32);
		int r = libusb_control_transfer(devh, 0xC0, 0xFF, 0x3700+i, 0, data, sizeof(data), 2000);
		if (r > 0) {
			printf("%02X: Got %d bytes:  ", i, r);
			for (int n = 0; n < r; n++) printf("%02X ", data[n]);
			printf("\n");
		} else {
			printf("%02X: Error: %d\n", i, r);
		}
	}

	printf("Done.\n");
}
