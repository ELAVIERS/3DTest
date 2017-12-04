#pragma once
#include <Windows.h>
#include <GL/GL.h>

//Forward declarations
class WindowClass;

/*
Window
******
HWND wrapper

_hwnd	|WINAPI Handle
_hdc	|Device Context
_hglrc	|OpenGL Rendering Context
*/

class Window
{
protected:
	HWND	_hwnd;
	HDC		_hdc;
	HGLRC	_hglrc;
public:
	Window()	{};
	~Window()	{};

	inline const HWND GetHWND() { return _hwnd; };

	void Create(const WindowClass &, void* param);
	void Show(int cmd_show);

	inline void Swap()			{ ::SwapBuffers(_hdc); };
	inline void UseGLContext()	{ wglMakeCurrent(_hdc, _hglrc); };
};
