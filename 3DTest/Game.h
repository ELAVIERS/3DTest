#pragma once
#include "Camera.h"
#include "CubeRenderer.h"
#include "GLProgram.h"
#include "Timer.h"
#include "Mat4.h"
#include "Window.h"
#include "WindowClass.h"

class Game {
	//Temporary stuff
	unsigned char	_key_states[256];
	bool			_lock_cursor;
	//Data
	bool			_running;
	WindowClass		_windowclass;
	Window			_window;
	Timer			_timer;

	Camera			_camera;
	GLProgram		_program;
	Mat4			_cube_t;
	Mat4			_cube_t2;
	//Functions
	void _Loop();
	void _Frame();
	void _Update(float FrameTime);
	void _Render();

	void _MouseMove(const Vector<unsigned short, 2>& position);

	static LRESULT CALLBACK _WindowProcedure(HWND, UINT, WPARAM, LPARAM);
public:
	Game() {};

	void Init();
	void Start(int CmdShow);
	void Stop();
};

