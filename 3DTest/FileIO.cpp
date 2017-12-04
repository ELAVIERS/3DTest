#include "FileIO.h"

#include "Error.h"
#include "String.h"
#include <fstream>

char* FileIO::ReadToString(const char* path, int& length) {
	std::ifstream file(path, std::ios::binary);

	if (file.fail()) {
		DebugMessage((String("Could not open a file (") + path + ")").GetData());
		ErrorMessage("Unable to read a file", false);
		length = 0;
		return NULL;
	}

	file.seekg(0, file.end);
	length = (int)file.tellg() + 1;
	file.seekg(0, file.beg);

	char* data = new char[length];

	for (int i = 0; i < length; ++i)
		data[i] = file.get();

	file.close();
	data[length - 1] = '\0';

	return data;
}