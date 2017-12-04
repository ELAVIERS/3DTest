#include "GLProgram.h"

#include "Error.h"
#include "FileIO.h"
#include "String.h"

GLProgram::GLProgram()
{
}


GLProgram::~GLProgram()
{
}

bool GLProgram::_CompileShader(const char* path, int id) {
	int length;
	char* data;

	if (!(data = FileIO::ReadToString(path, length))) return false;

	glShaderSource(id, 1, &data, nullptr);
	glCompileShader(id);
	delete[] data;

	GLint compile_status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &compile_status);
	if (compile_status == 0) {
		GLint length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		GLchar* error_str = new GLchar[length];
		glGetShaderInfoLog(id, length, &length, error_str);

		glDeleteShader(id);

		DebugMessage((String("\n\n-----COMPILATION ERROR\n") + error_str + "\n-----\n\n").GetData());
		ErrorMessage((String("Could not compile shader \"") + path + '\"').GetData(), false);

		delete[] error_str;
		return false;
	}

	glAttachShader(_id, id);

	return true;
}

void GLProgram::Load(const char* v_path, const char* f_path) {
	_id = 2;
	_id = glCreateProgram();
	GLuint vert_id = glCreateShader(GL_VERTEX_SHADER);
	GLuint frag_id = glCreateShader(GL_FRAGMENT_SHADER);

	_CompileShader(v_path, vert_id);
	_CompileShader(f_path, frag_id);

	glLinkProgram(_id);

	GLint link_status;
	glGetProgramiv(_id, GL_LINK_STATUS, &link_status);
	if (link_status == 0) {
		GLint length;
		glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &length);

		GLchar* error_str = new GLchar[length];
		glGetProgramInfoLog(_id, length, &length, error_str);

		glDeleteProgram(_id);
		glDeleteShader(vert_id);
		glDeleteShader(frag_id);

		DebugMessage(error_str);
		ErrorMessage("Could not link shader", false);

		delete[] error_str;
	}
}

#define IFLOCATION(NAME) GLint location = glGetUniformLocation(_id, NAME); \
							if (location > -1)

void GLProgram::SetParam(const char* name, GLint param) {
	IFLOCATION(name)
		glUniform1i(location, param);
}

void GLProgram::SetParam(const char* name, GLfloat param) {
	IFLOCATION(name)
		glUniform1f(location, param);
}

void GLProgram::SetParam(const char* name, const Vector3F& param) {
	IFLOCATION(name)
		glUniform3f(location, param[0], param[1], param[2]);
}

void GLProgram::SetParam(const char* name, const Mat4& param) {
	IFLOCATION(name)
		glUniformMatrix4fv(location, 1, 0, &param[0][0]);
}
