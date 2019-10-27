#include "image.hpp"
#include "utils/platform.hpp"

namespace res {

	Image::Image(u32 width, u32 height, u8* buffer, PixelFormat format) :
		width(width), height(height), buffer(buffer), format(format) {
	}

	Image::Image(const Image& other) = default;

	Image::Image(Image&& other) {
		width = other.width;
		height = other.height;
		buffer = other.buffer;
		format = other.format;

		// buffer doesn't get deallocated now.
		// moved pointers are copied.
		other.buffer = nullptr;
	}

	Image::~Image() {
		delete buffer;
	}
	
	Image&& Image::from_file(const std::string& file_path) {
		auto file = Platform::read_entire_binary_file(file_path);

		i32 x, y, channels;

		u8* buffer = stbi_load_from_memory(file.content, file.length, &x, &y, &channels, STBI_rgb_alpha);

		auto format = PixelFormat::Rgb;
		
		if(channels == 4)
			format = PixelFormat::Rgba;

		// Even though this will have return value optimization, I am being explicit.
		return std::move(Image(x, y, buffer, format));
	}

	Image Image::operator= (const Image& other) {
		width = other.width;
		height = other.height;
		buffer = other.buffer;
		format = other.format;

		return *this;
	}

	Image Image::operator= (Image&& other) {
		width = other.width;
		height = other.height;
		buffer = other.buffer;
		format = other.format;
		
		other.buffer = nullptr;

		return *this;
	}
}
