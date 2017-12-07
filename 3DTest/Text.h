#pragma once
#include "Font.h"
#include "String.h"
#include <GL\glew.h>

class Text
{
	const Font*	_font;
	String		_string;

	GLuint		_vao;
	GLuint		_vbo;
	GLuint*		_texture_ids;

	void _UpdateVBO();
public:
	Text();
	~Text();

	void Create();

	inline void SetFont(const Font& font) { _font = &font; _UpdateVBO(); }
	inline void SetString(const char* string) { _string = string; _UpdateVBO(); }

	void Render();
};

