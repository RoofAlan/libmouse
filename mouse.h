#ifndef _MOUSE_H_
#define _MOUSE_H_

#define M_LEFT (1 << 0)		// Left key
#define M_RIGHT (1 << 1)	// Right key
#define M_MIDDLE (1 << 2)	// Middle key

typedef struct {
	int device_fd;	// File descriptor of Mouse

	long mouse_x;	// Mouse X
	long mouse_y;	// Mouse Y

	// Maxium
	long max_x, max_y;
	// Minium
	long min_x, min_y;

	// Key
	int mleft;	// Left
	int mright;	// Right
	int mmid;	// Middle
} MouseInfo;

// Initialize mouse
int mouseInit(MouseInfo *);

// Set the maxium position of the mouse
void mouseSetMax(MouseInfo *, int max_x, int max_y);

// Set the minium position of the mouse
void mouseSetMin(MouseInfo *, int min_x, int min_y);

// Set the mouse position
void mouseSetPosition(MouseInfo *, int x, int y);

// Close mouse
void mouseClose(MouseInfo *);

// Update the mouse information
int mousePollUpdate(MouseInfo *);

// Wait for pressing
int mouseWaitPress(MouseInfo *, int key);

#endif // _MOUSE_H_
