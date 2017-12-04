#pragma once
#include <Windows.h>

#ifdef DEBUG
#define DEBUG_BREAK __debugbreak()
#else
#define DEBUG_BREAK
#endif

#ifdef DEBUG
inline void DebugMessage(const char* message) {
	::OutputDebugStringA(message);
}
#else
#define DebugMessage(A)
#endif

#ifdef DEBUG
inline void Assert(bool condition) {
#ifdef DEBUG
	if (!condition) {
		::MessageBox(NULL, "Assertion Failed", "Error", MB_OK);
		DEBUG_BREAK;
	}
#endif
}
#else
#define Assert(A)
#endif
