
#include "application.h"


//////////////////////////////////////////////////////////////////////
//  Initialization of DirectX
//////////////////////////////////////////////////////////////////////
int Application::Initialize()
{
	// Creating the D3D interface object
	pd3d = NULL;
 	pd3d = Direct3DCreate9( D3D_SDK_VERSION );
	if (pd3d == NULL)
		PROBLEM("Could not obtain interface to Direct3D");

	// Getting the monitor current display mode
	if (D3D_OK != pd3d->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &displaymode ))
		PROBLEM("Could not get monitor display mode");

	// Preliminary step required to permit the next one
	terrain.Build( 20, 20, 10 );

	// After obtaining and interface to d3d we proceed for a full setup
	Setup();

	return 0;
}

int Application::SetupDevice()
{
	CLEAR(deviceparameters);

	// Setting specific presentation parameters
	deviceparameters.Windowed   			= TRUE;
	deviceparameters.SwapEffect 			= D3DSWAPEFFECT_DISCARD; //D3DSWAPEFFECT_COPY;
    deviceparameters.hDeviceWindow 			= window.handle;
    deviceparameters.BackBufferFormat		= D3DFMT_X8R8G8B8;
    deviceparameters.BackBufferWidth 		= window.width;
    deviceparameters.BackBufferHeight 		= window.height;
	// We also make use of the depth buffer
	deviceparameters.EnableAutoDepthStencil	= true;
    deviceparameters.AutoDepthStencilFormat	= D3DFMT_D16;

	// Creating the d3d device interface
	pDevice = NULL;
	if (D3D_OK != pd3d->CreateDevice(   D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window.handle,
				  						D3DCREATE_SOFTWARE_VERTEXPROCESSING,
										&deviceparameters, &pDevice ))
		PROBLEM("Could not create the device");
		
	deviceReady = true;
	return 0;
}


int Application::SetupViewer()
{
	// Setting up the perspective matrix (needed once per setup)
	D3DXMatrixPerspectiveFovLH( &viewer.proj_matrix,
								D3DXToRadian(40),
								window.aspect,
								viewer.near_plane,
								viewer.far_plane );
	pDevice->SetTransform( D3DTS_PROJECTION, &viewer.proj_matrix );

 	updateViewerOrientation(0,0);

	return 0;
}


int Application::SetupGraphics()
{
	// Setting up lighting and materials
	pDevice->SetLight( 0, &sun.d3dlight );
	pDevice->LightEnable( 0, true );
	pDevice->SetRenderState( D3DRS_LIGHTING, true );
	pDevice->SetRenderState( D3DRS_ZENABLE, true );
	pDevice->SetRenderState( D3DRS_SPECULARENABLE, false );

	pDevice->SetMaterial( &(terrain.d3dmaterial) );
	pDevice->SetRenderState( D3DRS_AMBIENT, D3DCOLOR_RGBA( 128, 128, 128, 0));

	// Other render states
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); // no culling, rendering both sides

	return 0;
}


int Application::SetupVertexBuffer(DWORD buffersize, WORD vertexsize)
{
	// Creating and initializing a -global- vertex buffer
	// Note: its size could be any sufficiently large size
	pVertexBuffer = NULL;
	if (D3D_OK != pDevice->CreateVertexBuffer( 	terrain.GetVBSize(),
					     						0,
					     						VERTEXFORMAT,
					     						D3DPOOL_DEFAULT,
					     						&pVertexBuffer, NULL ))
		PROBLEM("VertexBuffer could not be created");
	pDevice->SetStreamSource( 0, pVertexBuffer, 0, sizeof(Vertex) );
	pDevice->SetFVF( VERTEXFORMAT );

	return 0;
}

	
int Application::updateViewerOrientation(float dispx, float dispy )
{
	static float hilimit = 10.0;
	static float lolimit = -10.0;

	// limiting movement speed
	if (dispx > hilimit) dispx = hilimit;
	if (dispx < lolimit) dispx = lolimit;

	if (dispy > hilimit) dispy = hilimit;
	if (dispy < lolimit) dispy = lolimit;

	// updating the orientation angles
	viewer.yaw += radians( dispx );
	viewer.pitch += radians( dispy );

	// building matrices to rotate the mesh
	static D3DXMATRIX matYaw;
	static D3DXMATRIX matPitch;
	D3DXMatrixRotationY( &matYaw, viewer.yaw );
	D3DXMatrixRotationX( &matPitch, viewer.pitch );

	// updating the world matrix
	viewer.world_matrix = matPitch * matYaw;
    pDevice->SetTransform( D3DTS_WORLD, &viewer.world_matrix );

	// Setting up the view matrix
	D3DXMatrixLookAtLH( &viewer.view_matrix, &viewer.position, &viewer.lookat, &viewer.upvector );
	pDevice->SetTransform( D3DTS_VIEW, &viewer.view_matrix );
	
	return 0;
}


int Application::Render(void)
{
	if (!initialized || paused)
		return 0;

	// Prepare frame for rendering (clearing the canvas and the depth buffer)
	pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 20, 40, 100), 1.0f, 0 );
	pDevice->Clear( 0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0 );
	pDevice->BeginScene(); // All rendering begins here ////////////////////////////

	terrain.Render();

	pDevice->EndScene(); // Finished drawing, so we show the frame//////////////////
	pDevice->Present( NULL, NULL, NULL, NULL );
	Sleep( 60 );
	return 0;
}


int Application::Setup()
{
	SetupDevice();
	SetupViewer();
	SetupGraphics();
	SetupVertexBuffer( terrain.GetVBSize(), sizeof(Vertex) );
	terrain.LoadVertexBuffer();
	initialized = true;
	return 0;
}


int Application::Resize()
{
	// First, releasing interface objects
	initialized = false;
	RELEASE(pVertexBuffer);
	RELEASE(pDevice);
	
	// then reinitializing the application
	Setup();
	return 0;
}


int Application::Shutdown(void)
{
	RELEASE(pVertexBuffer);
	RELEASE(pDevice);
	RELEASE(pd3d);
	initialized = false;
	return 0;
}
