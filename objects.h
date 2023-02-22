#ifndef __objects_h__
#define __objects_h__

//#include "main.h"
#include "dxglobals.h"
#include "globals.h"
#include <storage.h>

#define VERTEXFORMAT ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE )

// Geometry objects ------------------------------------------------

struct Vertex
{
	D3DXVECTOR3	position;
	D3DXVECTOR3	normal;
	DWORD   	color;
};


struct Triangle
{
	unsigned int v0, v1, v2;
	D3DXVECTOR3  normal;
};

// World objects -----------------------------------------------

struct Sun
{
	D3DLIGHT9	 d3dlight; 	// lighting information (includes light direction)
	D3DXVECTOR3  position; 	// position in Cartesian coordinates

	// direction (position in spherical coordinates)
	float heading;
	float elevation;
	float distance;

	Sun()
	{
		CLEAR( *this );
		d3dlight.Type  = D3DLIGHT_DIRECTIONAL;
		d3dlight.Diffuse = MakeColor(1.0f, 1.0f, 1.0f, 0.0f);
		d3dlight.Direction = D3DXVECTOR3( 0.0f, -8.0f, 10.0f );
		D3DXVec3Normalize( (D3DXVECTOR3*)&d3dlight.Direction, (D3DXVECTOR3*)&d3dlight.Direction );
	 };
};

struct Viewer
{
	// viewing matrices
	D3DXMATRIX  world_matrix;
	D3DXMATRIX	view_matrix;
	D3DXMATRIX  proj_matrix;

	// viewing vectors
	D3DXVECTOR3	position;
	D3DXVECTOR3 upvector;
	D3DXVECTOR3 lookat;

	// rotation angles about all three axes
	float yaw;
	float pitch;
	float roll;

	// Fog settings
	float near_plane;
	float far_plane;

	Viewer()
	{
		CLEAR(*this);

		position = D3DXVECTOR3( 0.0f,  100.0f, -400.0f );
		upvector = D3DXVECTOR3( 0.0f,  1.0f,  0.0f );
		lookat   = D3DXVECTOR3( 0.0f,  0.0f,  0.0f );

		D3DXVec3Normalize( &upvector, &upvector );

		near_plane = 1.0f;
		far_plane = 1000.0f;
	};
};


struct Terrain
{
	Storage::Array<Vertex>   vertices;
	Storage::Array<Triangle> polygons;

	D3DMATERIAL9 d3dmaterial;

	Terrain()
	{
		CLEAR( *this );
		// Setting up the terrain material
		d3dmaterial.Diffuse = MakeColor(0.1f, 0.8f, 0.7f, 0.0f);
		d3dmaterial.Ambient = MakeColor(0.1f, 0.4f, 0.35f, 0.0f);
	};

	int Build( const BYTE rows = 8, const BYTE columns = 8, const float unitsize = 8 );
	int Render() { return pDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, polygons.Count() ); };
	int GetVBSize() { return (3 * polygons.Count() * sizeof(Vertex)); };
	int LoadVertexBuffer();
};


#endif
