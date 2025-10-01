#include <stdio.h>
#include "mouse.h"

int main() {
	MouseInfo m;
	if (mouseInit(&m) < 0) {
		fprintf(stderr, "Cannot init mouse\n");
		return 0;
	}

	/*printf("Wait for clicking MIDDLE and RIGHT...\n"); fflush(stdout);
	mouseWaitPress(&m, M_MIDDLE | M_RIGHT);*/

	mouseSetMax(&m, 500, 500);
	mouseSetMin(&m, -500, -500);
	while(mousePollUpdate(&m) != -1) {
		printf("\rMouse: X: %ld, Y: %ld, Left: %d, Right: %d, Middle: %d                 ", m.mouse_x, m.mouse_y, m.mleft, m.mright, m.mmid); fflush(stdout);
	}

	mouseClose(&m);
	return 0;
}
