#pragma once
#include "Vector.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <GL/glew.h>
#include <map>

struct Glyph {
	GLuint textureID;
	Vector<int, 2> topleft;
	Vector<unsigned int, 2> size;
	FT_Pos advance;
};

class Font
{
	FT_Face _face;
	std::map<char, Glyph> _charmap;

public:
	Font() {};
	~Font() { FT_Done_Face(_face); };

	void Create(FT_Library library, const char* filepath);
	void SetSize(int pixel_size);

	inline const Glyph& GetGlyph(char char_code) const { return _charmap.at(char_code); }
};
