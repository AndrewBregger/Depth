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
	
	Image Image::from_file(const std::string& file_path) {
		auto file = Platform::read_entire_binary_file(file_path);

		i32 x, y, channels;

		u8* buffer = stbi_load_from_memory(file.content, file.length, &x, &y, &channels, STBI_rgb_alpha);

        auto image = allocate<u8>(x * y * 4);

        memcpy(image, buffer, x * y * 4);

        stbi_image_free(buffer);

		// PixelFormat format;
        // switch (channels) {
        //     case 3:
        //         format = PixelFormat::Rgb;
        //         break;
        //     case 4:
		// 	    format = PixelFormat::Rgba;
        //         break;
        //     default:
        //         ///// AHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
        //         break;
        // }

		return Image(x, y, image, PixelFormat::Rgba);
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
    
    /// @TODO: Why is this causing a double free error on the window?
    Image Image::convert_to(PixelFormat format) {
        if (this->format == format) {
            auto size = width * height * (format == PixelFormat::Rgb ? 3: 4);
            u8* buffer = allocate<u8>(size);
            memcpy(buffer, this->buffer, size);
            return Image(width, height, buffer, format);
        }
        else {
            if (this->format == PixelFormat::Red ||
                this->format == PixelFormat::Depth ||
                this->format == PixelFormat::Stencil) {
                LOG_ERR("Unimplemented Image conversion: {} -> {}", this->format, format);
                exit(1);
            }

            switch (format) {
                case PixelFormat::Rgb: {
                   u8* buffer = allocate<u8>(width * height * 3);
                   for (auto i = 0; i < width; ++i) {
                       for (auto j = 0; j < height; ++j) {
                            // only copy the rgb channels
                            buffer[j * width + i + 0] = this->buffer[j * width + i + 0];
                            buffer[j * width + i + 1] = this->buffer[j * width + i + 1];
                            buffer[j * width + i + 2] = this->buffer[j * width + i + 2];
                       }
                   }
                } break;
                case PixelFormat::Rgba: {
                   u8* buffer = allocate<u8>(width * height * 4); 
                   for (auto i = 0; i < width; ++i) {
                       for (auto j = 0; j < height; ++j) {
                            // only copy the rgb channels
                            buffer[j * width + i + 0] = this->buffer[j * width + i + 0];
                            buffer[j * width + i + 1] = this->buffer[j * width + i + 1];
                            buffer[j * width + i + 2] = this->buffer[j * width + i + 2];
                            buffer[j * width + i + 3] = 1.0;
                       }
                   }
                   return Image(width, height, buffer, format);
                } break;
                default:
                    LOG_WARN("Unimplemented image coversion: {}", format);
                    return Image(width, height, nullptr, format);
            }
        }
    }
}
