#include "Window.h"

#include "Debug.h"
#include "WindowClass.h"

void Window::Create(const WindowClass& wc, void* param) {
	_hwnd = ::CreateWindowExA(0, wc.GetID(), "Title", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		nullptr, nullptr, ::GetModuleHandle(nullptr), param);
	Assert(_hwnd);

	_hdc = ::GetDC(_hwnd);
	Assert(_hdc);

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,							//cColorBits
		0, 0, 0, 0, 0, 0, 0, 0,		//*
		0, 0, 0, 0, 0,				//*
		32,							//cDepthBits
		0,							//*
		0,							//*
		0,							//Ignored
		0,							//*
		0,							//*	
		0,							//*
		0							//* - Not relevant for finding PFD
	};

	int pfd_id = ::ChoosePixelFormat(_hdc, &pfd);
	Assert(pfd_id);

	::SetPixelFormat(_hdc, pfd_id, &pfd);

	_hglrc = wglCreateContext(_hdc);
	Assert(_hglrc);

	//Note that we are not releasing the device context in this class. This may need to be changed later.
}

void Window::Show(int cmd_show) {
	::ShowWindow(_hwnd, cmd_show);
}

/*
PIXELFORMATDESCRIPTOR:
WORD  nSize;
WORD  nVersion;
DWORD dwFlags;
BYTE  iPixelType;
BYTE  cColorBits;
BYTE  cRedBits;
BYTE  cRedShift;
BYTE  cGreenBits;
BYTE  cGreenShift;
BYTE  cBlueBits;
BYTE  cBlueShift;
BYTE  cAlphaBits;
BYTE  cAlphaShift;
BYTE  cAccumBits;
BYTE  cAccumRedBits;
BYTE  cAccumGreenBits;
BYTE  cAccumBlueBits;
BYTE  cAccumAlphaBits;
BYTE  cDepthBits;
BYTE  cStencilBits;
BYTE  cAuxBuffers;
BYTE  iLayerType;
BYTE  bReserved;
DWORD dwLayerMask;
DWORD dwVisibleMask;
DWORD dwDamageMask;
*/
