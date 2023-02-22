#ifndef __input_h__
#define __input_h__

#include "globals.h"
#include <windowsx.h> // for GET_LPARAM macros

struct Mouse
{
	short cursorx;
	short cursory;
	short originx;
	short originy;
	short dispx;
	short dispy;

	bool buttonpressed;

	Mouse() { CLEAR(*this); }; // constructor

	// --------------- Methods ----------------

	inline void setPosition(const LPARAM coordinates) {
		cursorx = GET_X_LPARAM(coordinates);
		cursory = GET_Y_LPARAM(coordinates);
	};
	
	inline void updateOrigin() {
		originx = cursorx;
		originy = cursory;
	};
	
	inline void computeDisplacement() {
		dispx = originx - cursorx;
		dispy = originy - cursory;
	};
};


#endif // end header
