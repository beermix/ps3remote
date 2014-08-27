#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include "uinput.h"


int
uinput_open (void) 
{
	int fd;
	struct uinput_user_dev uidev;
	if ((fd = open("/dev/uinput", O_WRONLY)) < 0) {
		perror("uinput_open");
		return -1;
	}
	if (ioctl(fd, UI_SET_EVBIT, EV_SYN) < 0) {
		perror("UI_SET_EVBIT");
		goto uinput_open_error;
	}
	if (ioctl(fd, UI_SET_EVBIT, EV_KEY) < 0) {
		perror("UI_SET_EVBIT");
		goto uinput_open_error;
	}
	if (ioctl(fd, UI_SET_KEYBIT, KEY_1) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_2) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_3) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_4) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_5) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_6) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_7) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_8) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_9) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_0) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_ENTER) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_ESC) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_CLEAR) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_EJECTCD) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_MENU) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_TIME) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_PREVIOUS) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_NEXT) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_PLAY) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_REWIND) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_FORWARD) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_STOP) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_PAUSE) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_CONTEXT_MENU) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_HOME) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_LIST) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_LANGUAGE) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_UP) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_RIGHT) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_DOWN) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_LEFT) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_OPTION) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_BACK) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, BTN_0) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_SCREEN) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_FRAMEBACK) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_FRAMEFORWARD) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_SUBTITLE) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_AUDIO) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_ANGLE) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_INFO) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_BLUE) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_RED) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_GREEN) < 0) goto set_keybit_error;
	if (ioctl(fd, UI_SET_KEYBIT, KEY_YELLOW) < 0) goto set_keybit_error;

	memset(&uidev, 0, sizeof uidev);
	snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "ps3remote");
	uidev.id.bustype = BUS_VIRTUAL;
	uidev.id.vendor  = 0x0609;
	uidev.id.product = 0x0306;
	uidev.id.version = 1;
	if (write(fd, &uidev, sizeof(uidev)) < 0) {
		perror("write");
		goto uinput_open_error;
	}
	if (ioctl(fd, UI_DEV_CREATE) < 0) {
		perror("UI_DEV_CREATE");
		goto uinput_open_error;
	}

	return fd;

set_keybit_error:
	perror("UI_SET_KEYBIT");
uinput_open_error:
	close(fd);
	return -1;
}


int
uinput_close (int fd)
{
	if (ioctl(fd, UI_DEV_DESTROY) < 0) {
		perror("UI_DEV_DESTROY");
	}
	return close(fd);
}


int
uinput_write (int fd, uint16_t key, int32_t value)
{
	struct input_event ev[2];
	int size;

	memset(&ev, 0, sizeof(ev));
	ev[0].type = EV_KEY;
	ev[0].code = key;
	ev[0].value = value;
	ev[1].type = EV_SYN;
	ev[1].code = SYN_REPORT;

	size = sizeof ev;
/*
	int i;
	for (i=size/2 - 1; i>=0; i--) {
		printf("0x%02x ", ((uint8_t*)ev)[i]);
	}
	putchar('\n');
	for (i=size - 1; i>=size/2; i--) {
		printf("0x%02x ", ((uint8_t*)ev)[i]);
	}
	putchar('\n');
*/
	write(fd, &(ev[0]), sizeof(ev[0]));
	write(fd, &(ev[1]), sizeof(ev[1]));
	return 0;

	return write(fd, &ev, sizeof(ev));
}
