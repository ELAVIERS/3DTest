#pragma once
#include <Windows.h>

/*
WindowClass
***********
WNDCLASSEXA Wrapper

_strid		|Name of the Window Class
*/

class WindowClass
{
private:
	char* _strid;

public:
	WindowClass() {};
	~WindowClass();

	void Register(const char* ClassName, WNDPROC WindowProcedure);
	inline const char* GetID() const { return _strid; };
};
