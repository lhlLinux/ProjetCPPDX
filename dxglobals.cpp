
#include "dxglobals.h"

LPDIRECT3DDEVICE9   pDevice = NULL;
DXVBUFFER           pVertexBuffer = NULL;

D3DCOLORVALUE MakeColor(float r, float g, float b, float a)
{
	D3DCOLORVALUE color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return color;
}
