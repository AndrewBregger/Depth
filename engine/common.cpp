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

u32 gl_pixel_format(PixelFormat) {

}

PixelFormat pixel_format(u32 format) {
    
}