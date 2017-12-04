#pragma once
#include <GL/glew.h>

class CubeRenderer
{
	static GLuint _vao;
	static GLuint _vbo;

public:
	static void Create();
	static void Bind();
	static void Render();
};
