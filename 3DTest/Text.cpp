#include "Text.h"

#include "Vertex.h"

Text::Text() {
}


Text::~Text() {
	glDeleteBuffers(1, &_vbo);
	glDeleteVertexArrays(1, &_vao);

	delete[] _texture_ids;
}

void Text::Create() {
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);

	glBindVertexArray(_vao);
}

inline void BindVAOAttribs() {
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex_P2_UV2), (GLvoid*)offsetof(Vertex_P2_UV2, position));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex_P2_UV2), (GLvoid*)offsetof(Vertex_P2_UV2, uv));
}

void Text::_UpdateVBO() {
	if (!_font || _string.GetSize() <= 1)
		return;

	delete[] _texture_ids;
	_texture_ids = new GLuint[_string.GetLength()];

	Vertex_P2_UV2 verts[6];

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts) * _string.GetLength(), NULL, GL_STATIC_DRAW);

	BindVAOAttribs();

	unsigned int i = 0;
	float x_offset = 0;
	Glyph current;
	for (const char* c = _string.GetData(); *c != '\0'; ++c) {
		current = _font->GetGlyph(*c);
		_texture_ids[i] = current.textureID;

		float x1 = x_offset + current.topleft[0];
		float y1 = current.topleft[1] - (signed int)current.size[1];
		float x2 = x1 + current.size[0];
		float y2 = current.topleft[1];

		verts[0] = Vertex_P2_UV2{ Vector2F(x1,	y1),	Vector2F(0.f, 0.f) };
		verts[1] = Vertex_P2_UV2{ Vector2F(x2,	y1),	Vector2F(1.f, 0.f) };
		verts[2] = Vertex_P2_UV2{ Vector2F(x1,	y2),	Vector2F(0.f, 1.f) };

		verts[3] = Vertex_P2_UV2{ Vector2F(x2,	y2),	Vector2F(1.f, 1.f) };
		verts[4] = Vertex_P2_UV2{ Vector2F(x1,	y2),	Vector2F(0.f, 1.f) };
		verts[5] = Vertex_P2_UV2{ Vector2F(x2,	y1),	Vector2F(1.f, 0.f) };

		glBufferSubData(GL_ARRAY_BUFFER, sizeof(verts) * i, sizeof(verts), verts);

		x_offset += current.advance;
		++i;
	}
}

void Text::Render() {
	glBindVertexArray(_vao);
	glActiveTexture(GL_TEXTURE0);

	for (int i = 0; i < _string.GetLength(); ++i) {
		glBindTexture(GL_TEXTURE_2D, _texture_ids[i]);

		glDrawArrays(GL_TRIANGLES, i * 6, 6);
	}
}
