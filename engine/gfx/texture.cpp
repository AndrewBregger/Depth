#include "texture.hpp"

namespace gfx {
    Texture::Texture(const res::Image& image) :
		assets::Asset(assets::AssetType::TextureAsset),
        handle(0),
        w(image.width),
        h(image.height) {
        
        initialize(image.buffer, image.format);
    }
    
    /// Allocates an emtpy texture on the gpu
    Texture::Texture(u32 width, u32 height, PixelFormat format) :
		assets::Asset(assets::AssetType::TextureAsset),
        handle(0),
        w(width),
        h(height) {
        initialize(nullptr, format);
    }
    
    /// binds this texture to texture0
    void Texture::activate() {
        activate_to(handle);
    }
    
    /// binds this texture to GL_TEXTURE0 + offset
    void Texture::activate_to(u32 offset) {
        glCheck(glActiveTexture(GL_TEXTURE0 + offset));
    }
    
    void Texture::initialize(u8* buffer, PixelFormat format) {
        glCheck(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
        
        glCheck(glGenTextures(1, &handle));
        
        bind();
        
        // Set texture options.
        glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
        glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        
        glCheck(glTexImage2D(GL_TEXTURE_2D, 0, gl_pixel_format(format), w, h, 0, 
                             GL_RGBA, GL_UNSIGNED_BYTE, buffer));
        
        unbind();
    }
    
}
