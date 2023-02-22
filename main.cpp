#include "main.h"
#include "window.h"


Window window(800, 600);
Application app;
Mouse mouse;

// Program entry point
int WINAPI WinMain( HINSTANCE programHandle,
					HINSTANCE unusedHandle,
					LPSTR     cmdString,
					int       cmdShow )
{
	WNDCLASSEX  windowClass;
	CLEAR(windowClass);

	windowClass.style         = CS_HREDRAW | CS_VREDRAW;
	windowClass.cbSize		  = sizeof(WNDCLASSEX);
	windowClass.lpszClassName = "WindowClass";
	windowClass.lpfnWndProc	  = WindowProcedure;
	windowClass.hInstance     = programHandle;
	windowClass.hbrBackground = (HBRUSH)( COLOR_WINDOW + 1 );
	windowClass.hCursor		  = LoadCursor( NULL, IDC_ARROW );
	windowClass.hIcon		  = LoadIcon( NULL, IDI_APPLICATION );
	windowClass.hIconSm		  = LoadIcon( NULL, IDI_APPLICATION );
	windowClass.cbClsExtra    = 0;
    windowClass.cbWndExtra    = 0;

 	// Registering the window class
	if(!RegisterClassEx( &windowClass ))
		PROBLEM("The window class could not be registered");

	window.handle = CreateWindowEx( WS_EX_CLIENTEDGE,
									"WindowClass",
									"Caption",
									WS_VISIBLE|WS_OVERLAPPEDWINDOW,
									CW_USEDEFAULT, 	// window x coordinate
									CW_USEDEFAULT, 	// window y coordinate
									window.width, 	// window width
									window.height, 	// window height
									NULL,
									NULL,
									programHandle,
									NULL);

	if (window.handle == NULL) // make sure the pointer is valid
		PROBLEM("Window creation failed");

	if (app.Initialize())
		PROBLEM("Could not initialize DirectX");

	// Setting up message container for the loop
	MSG	windowMessage;
	CLEAR(windowMessage);
	// Entering program's main loop
    while(windowMessage.message != WM_QUIT)
	{
		// check for messages in the queue and process any
		if (PeekMessage(&windowMessage, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&windowMessage);
			DispatchMessage(&windowMessage);	// send message to winproc
		}
		app.Render();
	} // end loop

	// Freeing up window class memory
	UnregisterClass( windowClass.lpszClassName, windowClass.hInstance );
	return windowMessage.wParam;
} /* END MAIN */

