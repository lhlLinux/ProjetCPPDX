#ifndef __application_h__
#define __application_h__

#include "objects.h"
#include "window.h"

class Application
{
public:
	LPDIRECT3D9            	pd3d;
	D3DPRESENT_PARAMETERS	deviceparameters;
	D3DDISPLAYMODE 	        displaymode;

	DWORD       fogcolor;
	float       fogstart;
	float       fogend;
	int         fogmode;

	// world objects
	Sun 	   	sun;
	Viewer  	viewer;
	Terrain 	terrain;

	// essential state variable
	bool initialized;
	bool deviceReady;
	bool bufferReady;
	bool paused;

	// Constructor and destructor
	Application() { initialized = false; paused = false; };
	~Application() { Shutdown(); };

	// basic methods
	int Initialize();
	int Shutdown();
	int Render();

	int Resize();
	int Pause() { paused = true; };
	int Resume() { paused = false; };

	int Setup();  // Once-call setup

	// The full setup is segmented into several steps for greater flexibility
	int SetupDevice();
	int SetupGraphics();
	int SetupVertexBuffer(DWORD, WORD);
	int SetupViewer();

	// other
	int updateViewerOrientation(float, float);
};

#endif
