#include "Game.h"

#include "Debug.h"
#include "String.h"
#include <GL/glew.h>
#include <GL/wglew.h> //wglSwapIntervalEXT
#include <math.h>

#define GAME ((Game*)::GetWindowLongPtr(hwnd, GWLP_USERDATA))
LRESULT CALLBACK Game::_WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_CREATE:
		::SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)((LPCREATESTRUCT)lparam)->lpCreateParams);
		break;

	case WM_CLOSE:
		::DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		GAME->Stop();
		break;

	case WM_SIZE:
		glViewport(0, 0, LOWORD(lparam), HIWORD(lparam));
		GAME->_camera.SetSize(LOWORD(lparam), HIWORD(lparam));
		GAME->_Render();
		break;

	case WM_KEYDOWN:
		GAME->_key_states[wparam] = 1;
		break;
	case WM_KEYUP:
		GAME->_key_states[wparam] = 0;
		break;

	case WM_LBUTTONDOWN:
		GAME->_lock_cursor = !GAME->_lock_cursor;
		if (GAME->_lock_cursor)
			::ShowCursor(FALSE);
		else
			::ShowCursor(TRUE);
		break;

	case WM_INPUT:
		{
			UINT size;
			::GetRawInputData((HRAWINPUT)lparam, RID_INPUT, NULL, &size, sizeof(RAWINPUTHEADER));
			LPBYTE data = new BYTE[size];

			if (!data || ::GetRawInputData((HRAWINPUT)lparam, RID_INPUT, data, &size, sizeof(RAWINPUTHEADER)) != size) {
				DebugMessage("Warning --\n\tCould not read raw input\n-----");
				return 0;
			}

			GAME->_RawInput((RAWINPUT*)data);

			delete[] data;
		}
		break;

	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return 0;
}

void Game::Init() {
	//Window
	_windowclass.Register("MAINWINDOW", _WindowProcedure);
	_window.Create(_windowclass, this);
	_window.UseGLContext();

	//OpenGL
	glewInit();
	glClearColor(0.f, 0.1f, 0.f, 1.f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	wglSwapIntervalEXT(0);

	_program.Load("Data/Shaders/Shader.vert", "Data/Shaders/Shader.frag");

	//Objects
	CubeRenderer::Create();

	_camera.SetFOV(90.f);
	_camera.position = Vector3F(0.f, 0.f, -5.f);

	_cube_t *= Matrix::Translation(Vector3F(-4.f, 0.f, 0.f));
	_cube_t2 = Matrix::Translation(Vector3F(4.f, 0.f, 0.f));

	//Raw input
	_d_mouse = {
		0x01,	//Usage page
		0x02,	//Usage
		0,		//Flags
		NULL	//Hwnd target
	};

	if (RegisterRawInputDevices(&_d_mouse, 1, sizeof(RAWINPUTDEVICE)) == FALSE)
		DebugMessage("Warning --\n\tCould not register raw input device!\n\n-----");
}

void Game::Start(int cmd_show) {
	_running = true;

	_window.Show(cmd_show);

	_Loop();
}

void Game::Stop() {
	_running = false;
}

void Game::_Loop() {
	MSG msg;

	while (_running) {
		while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		_Frame();
	}

}

float runtime = 0.f;
float frame_time = 0.f;

void Game::_Frame() {
	_timer.Start();
	runtime += frame_time;

	_Update(frame_time);
	_Render();

	frame_time = _timer.Stop();
}

void Game::_Update(float frame_time) {
	::SetWindowTextA(_window.GetHWND(), (String::Convert(1.f / frame_time) + " FPS").GetData());

	if (_lock_cursor) {
		POINT pos = { 0, 0 };
		ClientToScreen(_window.GetHWND(), &pos);
		::SetCursorPos(pos.x + _camera.GetSize()[0] / 2, pos.y + _camera.GetSize()[1] / 2);
	}

	_camera.rotation += Vector2F(
		180.f * frame_time * (_key_states[VK_DOWN] - _key_states[VK_UP]),
		180.f * frame_time * (_key_states[VK_RIGHT] - _key_states[VK_LEFT])
	);

	if (_camera.rotation[0] < -90.f) _camera.rotation[0] = -90.f;
	else if (_camera.rotation[0] > 90.f) _camera.rotation[0] = 90.f;

	const float speed = 10;
	float movement_forward = frame_time * speed * (_key_states[0x57] - _key_states[0x53]);
	float movement_right = frame_time * speed * (_key_states[0x44] - _key_states[0x41]);

	_camera.position += Vector3F(
		cosdeg(_camera.rotation[0])	* sindeg(_camera.rotation[1]) * movement_forward + sindeg(_camera.rotation[1] + 90.f) * movement_right,
		-sindeg(_camera.rotation[0])	* movement_forward,
		cosdeg(_camera.rotation[0])	* cosdeg(_camera.rotation[1]) * movement_forward + cosdeg(_camera.rotation[1] + 90.f) * movement_right
	);

	_cube_t2 *= Matrix::XRotation(30.f * frame_time) * Matrix::YRotation(50.f * frame_time);
}


void Game::_Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_program.Use();
	_program.SetParam("M_Projection", _camera.GetProjectionMatrix());
	_program.SetParam("M_View", _camera.GetViewMatrix());
	_program.SetParam("Time", runtime);

	CubeRenderer::Bind();
	_program.SetParam("M_Model", _cube_t);
	CubeRenderer::Render();
	_program.SetParam("M_Model", _cube_t2);
	CubeRenderer::Render();

	_window.Swap();
}

//Input handling
void Game::_RawInput(RAWINPUT* input) {
	const float sensitivity = .25f;
	if (_lock_cursor && input->header.dwType == RIM_TYPEMOUSE) {
		_camera.rotation[0] += input->data.mouse.lLastY * sensitivity;
		_camera.rotation[1] += input->data.mouse.lLastX * sensitivity;
	}
}
