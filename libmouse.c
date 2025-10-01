#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "mouse.h"

// Initiailize the mouse
int mouseInit(MouseInfo *m) {
	m->device_fd = -1;
	char *mouse_path[] = {
		"/dev/input/mice",
		"/dev/input/event1",
		"/dev/input/event2",
		NULL,
	};

	int mouse_fd = 0;
	for (int i = 0; mouse_path[i]; i ++) {
		mouse_fd = open(mouse_path[i], O_RDONLY);
		if (mouse_fd > 0)
			break;
	}

	if (mouse_fd < 0) {
		return -1;
	}

	m->device_fd = mouse_fd;
	m->mouse_x = 0;
	m->mouse_y = 0;
	m->max_x = 0;
	m->max_y = 0;
	m->min_x = 0;
	m->min_y = 0;
	m->mleft = 0;
	m->mright = 0;
	m->mmid = 0;
	return 0;
}

// Close the mouse
void mouseClose(MouseInfo *m) {
	close(m->device_fd);
	m->device_fd = -1;
}

// Set the maxium position of the mouse
void mouseSetMax(MouseInfo *m, int max_x, int max_y) {
	m->max_x = max_x;
	m->max_y = max_y;
}

// Set the minium position of the mouse
void mouseSetMin(MouseInfo *m, int min_x, int min_y) {
	m->min_x = min_x;
	m->min_y = min_y;
}

// Set the mouse position
void mouseSetPosition(MouseInfo *m, int x, int y) {
	m->mouse_x = x;
	m->mouse_y = y;
}

// Update the mouse information
int mousePollUpdate(MouseInfo *m) {
	if (m->device_fd < 0)
		return -1;

	char data[3];
	size_t r = read(m->device_fd, data, sizeof(data));
	if (r != sizeof(data))
		return -1;

	int new_x = m->mouse_x + data[1];
	int new_y = m->mouse_y - data[2];

	if (m->max_x > 0 || m->min_x > 0) {
		if (new_x < m->min_x) {
			new_x = m->min_x;
		} else if (new_x > m->max_x) {
			new_x = m->max_x;
		}
	}
	
	if (m->max_y > 0 || m->min_y > 0) {
		if (new_y < m->min_y) {
			new_y = m->min_y;
		} else if (new_y > m->max_y) {
			new_y = m->max_y;
		}
	}

	m->mouse_x = new_x;
	m->mouse_y = new_y;

	m->mleft = data[0] & 0x1;
	m->mright = data[0] & 0x2;
	m->mmid = data[0] & 0x4;
	return 0;
}

// Wait for pressing
int mouseWaitPress(MouseInfo *m, int key) {
	int mkey = key;
	while (mousePollUpdate(m) != -1) {
		if (mkey & M_LEFT) {
			if (m->mleft)
				mkey ^= M_LEFT;
		}
		if (mkey & M_RIGHT) {
			if (m->mright)
				mkey ^= M_RIGHT;
		}
		if (mkey & M_MIDDLE) {
			if (m->mmid)
				mkey ^= M_MIDDLE;
		}

		if (mkey == 0)
			return 0;
		mkey = key;
	}

	return -1;
}
