#pragma once
#include "Debug.h"
#include <Windows.h>

inline void ErrorMessage(const char* message, bool fatal) {
	::MessageBoxA(NULL, message, fatal ? "Fatal Error!" : "Error", MB_OK);

	DEBUG_BREAK;

	if (fatal)
		exit(0);
}
