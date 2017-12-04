#include "WindowClass.h"

#include "Window.h"

WindowClass::~WindowClass() {
	if (this->_strid)
		delete[] this->_strid;
}

void WindowClass::Register(const char* id, WNDPROC winproc) {
	if (this->_strid)
		delete[] this->_strid;

	size_t length = strlen(id) + 1;
	this->_strid = new char[length];
	strcpy_s(this->_strid, length, id);

	WNDCLASSEXA window_class = {
		sizeof(WNDCLASSEXA),
		0,
		winproc,
		0,
		0,
		::GetModuleHandle(NULL),
		::LoadIcon(NULL, IDI_APPLICATION),
		::LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		_strid,
		::LoadIcon(NULL, IDI_APPLICATION)
	};

	::RegisterClassExA(&window_class);
}

/*
WNDCLASSEX:
UINT        cbSize;
UINT        style;
WNDPROC     lpfnWndProc;
int         cbClsExtra;
int         cbWndExtra;
HINSTANCE   hInstance;
HICON       hIcon;
HCURSOR     hCursor;
HBRUSH      hbrBackground;
LPCSTR      lpszMenuName;
LPCSTR      lpszClassName;
HICON       hIconSm;
*/
