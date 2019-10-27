#include "texture.hpp"

#include <glad/glad.h>

namespace gfx {
    Texture::Texture(const res::Image& image) {
        handle = 0;
        width = width;
        height = height;

        initialize(image.buffer, image.format);
    }
    
    /// Allocates an emtpy texture on the gpu
    Texture::Texture(u32 width, u32 height, PixelFormat format) {
        handle = 0;
        width = width;
        height = height;

        initialize(nullptr, format);
    }

    /// binds this texture to texture0
    void Texture::activate() {
        activate_to();
    }

    /// binds this texture to GL_TEXTURE0 + offset
    void Texture::activate_to(u32 offset) {
        glCheck(glActiveTexture(GL_TEXTURE0 + offset));
    }

    inline void Texture::bind() {
        glCheck(glBindTexture(GL_TEXTURE_2D, handle));
    }

    inline void Texture::unbind() {
        glCheck(glBindTexture(GL_TEXTURE_2D, 0));
    }

    void Texture::initialize(u8* buffer, PixelFormat format) {
        glCheck(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
    	glCheck(glPixelStorei(GL_UNPACK_ROW_LENGTH, 0));
	    glCheck(glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0));
	    glCheck(glPixelStorei(GL_UNPACK_SKIP_ROWS, 0));

        glCheck(glGenTextures(1, &handle));

        bind();

        // Set texture options.
        glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
        glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

        // consider making PixelFormat a struct and the value is the enum.
        // glTexImage2D(GL_TEXTURE_2D, 0, format.gl_format());
        
        glCheck(glTexImage2D(GL_TEXTURE_2D, 0, gl_pixel_format(format), width, height, 0, 
            gl_pixel_format(format), GL_UNSIGNED_BYTE, buffer));
        glCheck(glBindTexture(GL_TEXTURE_2D, handle));

        unbind();
    }

}