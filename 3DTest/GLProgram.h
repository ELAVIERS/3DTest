#pragma once
#include "Mat4.h"
#include <GL\glew.h>

class GLProgram
{
	GLuint _id;

	bool _CompileShader(const char* path, int id);
public:
	GLProgram();
	~GLProgram();

	inline void Use() { glUseProgram(_id); };
	inline void Deactivate() {};

	void Load(const char* vertex_path, const char* fragment_path);

	void SetParam(const char* name, GLint param);
	void SetParam(const char* name, GLfloat param);
	void SetParam(const char* name, const Vector3F& param);
	void SetParam(const char* name, const Mat4& param);
};

