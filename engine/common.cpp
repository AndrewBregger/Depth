#include "common.hpp"

#include <glad/glad.h>

void glCheck_(const char* file, const char* function, u32 line) {

    if (auto error_code = glGetError(); error_code != GL_NO_ERROR) {
        std::string error;

        switch (error_code) {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION";
            break;
        }
        
        LOG_ERR("{}:{}|{} {}", file, line, function, error);
    }
}

u32 gl_pixel_format(PixelFormat format) {
    switch(format) {
        case PixelFormat::Red:      return GL_RED;
        case PixelFormat::Alpha:    return GL_ALPHA;
        case PixelFormat::Depth:    return GL_DEPTH;
        case PixelFormat::Stencil:  return GL_STENCIL;
        case PixelFormat::Rgb:      return GL_RGB;
        case PixelFormat::Rgba:     return GL_RGBA;
        default:                    return GL_RGB;
    }
}

PixelFormat pixel_format(u32 format) {
    switch(format) {
        case GL_RED:        return PixelFormat::Red;
        case GL_ALPHA:      return PixelFormat::Alpha;
        case GL_DEPTH:      return PixelFormat::Depth;
        case GL_STENCIL:    return PixelFormat::Stencil;
        case GL_RGB:        return PixelFormat::Rgb;
        case GL_RGBA:       return PixelFormat::Rgba;
        default:            return PixelFormat::Rgb;
    }
}

std::ostream& operator<< (std::ostream& out, const glm::vec4& v) {
  out << v.x  << " " << v.y << " " << v.z << " " << v.w;
  return out;
}

std::ostream& operator<< (std::ostream& out, const glm::vec3& v) {
  out << v.x  << " " << v.y << " " << v.z;
  return out;
}

std::ostream& operator<< (std::ostream& out, const glm::vec2& v) {
  out << v.x  << " " << v.y;
  return out;
}

std::ostream& operator<< (std::ostream& out, const glm::mat4& v) {
	for (u32 i = 0; i < 4; ++i) {
		for (u32 j = 0; j < 4; ++j) {
			out << v[j][i] << " ";
		}
		out << std::endl;
	}

	return out;
}
