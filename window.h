#ifndef __window_h__
#define __window_h__

#include <windows.h>

struct Window
{
	HWND   handle;
	WORD   width;
	WORD   height;
	float  aspect;
	bool   resizing;

	Window(WORD w, WORD h) {  // constructor
		resizing = false;
		handle = NULL;
		UpdateSize(w, h);
	};

	inline void UpdateSize(WORD w, WORD h) {
		width  = w;
		height = h;
		aspect = (float)width / (float)height;
	};
};

extern Window window;

#endif

