#pragma once
#include "Font.h"
#include "String.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>

class FontManager
{
	FT_Library _library;

	std::map<String, Font> _fontmap;
public:
	FontManager() {};
	~FontManager() {};

	void Create();

	Font& GetFont(const char* filepath);
};
