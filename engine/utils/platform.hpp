#ifndef PLATFORM_HPP_
#define PLATFORM_HPP_

#include "common.hpp"

template <typename Content>
struct File {
	Content* content;
	u32 length;

	File(Content* content, u32 length);

	File(const File& other);

	File(File&& other);

	~File();
};

template <typename Content>
File<Content>::File(Content* content, u32 length) : content(content), 
	length(length) {
}

template <typename Content>
File<Content>::~File() {
	deallocate(content);
}

template <typename Content>
File<Content>::File(const File& other) {
	content = other.content;
	length = other.length;
}

template <typename Content>
File<Content>::File(File&& other) {
	content = other.content;
	length = other.length;

	other.content = nullptr;
}


struct Platform {
	static File<char> read_entire_file(const std::string& file_path);

	static File<u8> read_entire_binary_file(const std::string& file_path);
};

#endif
