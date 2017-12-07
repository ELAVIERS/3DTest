#pragma once
#include "Camera.h"
#include "CubeRenderer.h"
#include "FontManager.h"
#include "GLProgram.h"
#include "Text.h"
#include "Timer.h"
#include "Mat4.h"
#include "Window.h"
#include "WindowClass.h"

class Game {
	//Managers
	FontManager		_fontmanager;
	//Temporary stuff
	unsigned char	_key_states[256];
	bool			_lock_cursor;
	Text			_text_test;
	//Data
	bool			_running;
	WindowClass		_windowclass;
	Window			_window;
	Timer			_timer;
	Font*			_font;

	Camera			_camera;
	GLProgram		_geometry_program;
	GLProgram		_text_program;
	Mat4			_cube_t;
	Mat4			_cube_t2;

	RAWINPUTDEVICE _d_mouse;

	//Functions
	void _Loop();
	void _Frame();
	void _Update(float FrameTime);
	void _Render();

	//Messages
	void _RawInput(RAWINPUT*);

	static LRESULT CALLBACK _WindowProcedure(HWND, UINT, WPARAM, LPARAM);
public:
	Game() {};

	void Init();
	void Start(int CmdShow);
	void Stop();
};

