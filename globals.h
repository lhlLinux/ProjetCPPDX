#ifndef __globals_h__
#define __globals_h__

#include <windows.h> // for ZeroMemory in case it is needed

// Macros
#define CLEAR(block) ZeroMemory( &block, sizeof( block ) )
#define TOGGLE(variable) (variable) ^= 1
#define RELEASE(pointer) { if (pointer) { pointer->Release(); pointer = NULL; } }
#define PROBLEM(message) {  MessageBox( NULL, message, "Error!", MB_ICONEXCLAMATION|MB_OK ); \
							return 0; }


#endif
