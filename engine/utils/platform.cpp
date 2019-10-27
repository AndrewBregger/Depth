#include "platform.hpp"
#include <cstdio>
#include <exception>

File<char> Platform::read_entire_file(const std::string& file_path) {
	char* buffer = nullptr;

	FILE* file = fopen(file_path.c_str(), "r");

	if(file) {
		auto len = fseek(file, 0, SEEK_END);	
		buffer = allocate<char>(len + 1);
		rewind(file);

		fread(buffer, sizeof(char), len, file);

		fclose(file);
		
		buffer[len] = 0;

		return File(buffer, len);
	}
	else {
		throw std::runtime_error("Failed to open file: " + file_path);
	}
}

File<u8> Platform::read_entire_binary_file(const std::string& file_path) {
	u8* buffer = nullptr;
	FILE* file = fopen(file_path.c_str(), "rb");

	if(file) {
		auto len = fseek(file, 0, SEEK_END);	
		buffer = allocate<u8>(len);		
		rewind(file);

		fread(buffer, sizeof(u8), len, file);

		fclose(file);

		return File(buffer, len);
	}
	else {
		throw std::runtime_error("Failed to open file: " + file_path);
	}
}
