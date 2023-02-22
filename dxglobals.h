#ifndef __dxglobals_h__
#define __dxglobals_h__

#include <windows.h>    // required for D3D9Types.h
#include <d3d9types.h>  // essential: for dx types and macros
#include <d3d9.h>
#include <d3dx9.h>      // for dx utility library

typedef LPDIRECT3DVERTEXBUFFER9 DXVBUFFER; // the name is too long, so we use an alias

extern LPDIRECT3DDEVICE9   pDevice;
extern DXVBUFFER           pVertexBuffer;

// Helper functions
D3DCOLORVALUE MakeColor(float, float, float, float);
inline float degrees(float radians) { return radians * 57.296; }
inline float radians(float degrees) { return degrees / 57.296; }


#endif

