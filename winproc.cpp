#include "main.h"


LRESULT CALLBACK WindowProcedure( HWND windowhandle, UINT message, WPARAM wparam, LPARAM lparam )
{
	switch(message)
	{
		case WM_CREATE: {
			break;
		}
		
		case WM_SHOWWINDOW:
		{
			UpdateWindow( windowhandle );
			SetFocus( windowhandle );
			break;
		}

		case WM_ENTERSIZEMOVE: {
			onEnterResize();
			break;
		}

		case WM_EXITSIZEMOVE: {
			onExitResize();
			break;
		}

		case WM_SIZING: {
			onResizing((RECT*)lparam);
			break;
		}

		case WM_SIZE: {
			onWindowState(wparam, lparam);
			break;
		}

		case WM_KEYDOWN:
        {
		    switch (wparam)
            {
	            case VK_ESCAPE: // Escape key has been pressed
					PostMessage( window.handle, WM_CLOSE, NULL, NULL );
            }
            break;
		}

		case WM_LBUTTONDOWN: {
			onButtonPressed(lparam);
			break;
		}

		case WM_MOUSEMOVE: {
			if (mouse.buttonpressed)
				onMouseMove(lparam);
			break;
		}

		case WM_LBUTTONUP: {
			onButtonReleased(lparam);
			break;
		}

		case WM_CLOSE:
		{
			int result = MessageBox(windowhandle, "Are you sure you want to close the application?",
									"Confirmation",
									MB_YESNO | MB_ICONQUESTION);

			// if user wants to close we call the default handler
			if (result == IDYES)
				return DefWindowProc( windowhandle, message, wparam, lparam );
				
			break;
		}

		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}

		default:
			return DefWindowProc( windowhandle, message, wparam, lparam );
    }
	return 0;
} // end -switch-



