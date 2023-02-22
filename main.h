#ifndef __main_h__
#define __main_h__

//#include <stdlib.h>
//#include <string.h>
#include <windows.h>
#include <windowsx.h>
#include "application.h"
#include "input.h"


LRESULT CALLBACK WindowProcedure( HWND, UINT, WPARAM, LPARAM );


// event functions
void onMouseMove(LPARAM);
void onButtonPressed(LPARAM);
void onButtonReleased(LPARAM);
void onWindowState(WPARAM, LPARAM);
void onResizing(RECT*);
void onEnterResize();
void onExitResize();

// globals
extern Mouse mouse;
extern Application app;


#endif // __main_h__
