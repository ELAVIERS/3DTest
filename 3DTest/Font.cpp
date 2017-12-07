#include "Font.h"

#include "Error.h"
#include "String.h"

inline GLuint CreateGlyphTexture(const FT_GlyphSlot& glyph) {
	if (!glyph->bitmap.buffer)
		return 0;

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_R8, glyph->bitmap.width, glyph->bitmap.rows);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, glyph->bitmap.width, glyph->bitmap.rows,
		GL_RED, GL_UNSIGNED_BYTE, glyph->bitmap.buffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	return texture;
}

void Font::Create(FT_Library library, const char* filepath) {
	FT_Error error = FT_New_Face(library, filepath, 0, &_face);
	if (error) {
		switch (error) {
		case FT_Err_Unknown_File_Format:
		case FT_Err_Cannot_Open_Resource:
			ErrorMessage((String("Could not read font file \"") + filepath + '\"').GetData(), false);
			break;
		default:
			ErrorMessage((String("Error loading font \"") + filepath + "\"\n\t(CODE 0x" + String::ConvertHex(error) + ')').GetData(), false);
		}
		return;
	}
}

void Font::SetSize(int pixel_size) {
	for (auto it = _charmap.begin(); it != _charmap.end(); ++it)
		if (it->second.textureID)
			glDeleteTextures(1, &it->second.textureID);
	_charmap.clear();

	FT_Set_Pixel_Sizes(_face, 0, pixel_size);

	FT_Error	error;
	FT_UInt		glyph_index;
	FT_ULong	char_code;
	
	//Load Characters
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	char_code = FT_Get_First_Char(_face, &glyph_index);
	do {
		//For now, only load charcodes for ASCII
		if (char_code < 256) {
			if (error = FT_Load_Char(_face, char_code, FT_LOAD_RENDER))
				ErrorMessage((String("Character loading error 0x") + String::ConvertHex(error)).GetData(), false);

			_charmap[char_code] = Glyph{
				CreateGlyphTexture(_face->glyph),
				Vector<int, 2>(_face->glyph->bitmap_left, _face->glyph->bitmap_top),
				Vector<unsigned int, 2>(_face->glyph->bitmap.width, _face->glyph->bitmap.rows),
				_face->glyph->advance.x >> 6
			};
		}

		char_code = FT_Get_Next_Char(_face, char_code, &glyph_index);
	} while (glyph_index);
}
