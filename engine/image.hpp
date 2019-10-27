#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include "common.hpp"
#include <stbi_image.h>

namespace res {

	/// A raw image.
	struct Image {
		/// width in pixels
		u32 width;
		/// height in pixels
		u32 height;
		/// image buffer
		/// size = width * height * num_channel(format)
		u8* buffer;
		/// the format of the pixels in the buffer.
		PixelFormat format;
		
		/// Constructor
		/// width: the width
		/// height: the height 
		/// buffer: image buffer
		/// format: the pixel format
		Image(u32 width, u32 height, u8* buffer, PixelFormat format);

		Image(const Image& other);

		Image(Image&& other);

		~Image();

		Image operator= (const Image& other);

		Image operator= (Image&& other);
		
		/// build an image from the a file
		/// file_path: the path to the file.
		static Image&& from_file(const std::string& file_path);

		inline u32 get_width();

		inline u32 get_height();

		inline u8* get_buffer();

		inline PixelFormat get_format();
	};

	inline u32 Image::get_width() {
		return width;
	}

	inline u32 Image::get_height() {
		return height;
	}

	inline u8* Image::get_buffer() {
		return buffer;
	}

	inline PixelFormat Image::get_format() {
		return format;
	}
}

#endif
