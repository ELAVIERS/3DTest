#include "FontManager.h"

#include "Error.h"
#include "String.h"

void FontManager::Create() {
	FT_Error error = FT_Init_FreeType(&_library);
	if (error)
		ErrorMessage(
		(String("Freetype initialisation error\n\t(CODE 0x") + String::ConvertHex(error) + ')').GetData(),
			true
		);
}

Font& FontManager::GetFont(const char* filepath) {
	auto it = _fontmap.find(filepath);

	if (it == _fontmap.end()) {
		_fontmap[filepath].Create(_library, filepath);
		return _fontmap[filepath];
	}

	return it->second;
}
