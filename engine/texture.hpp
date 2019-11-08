#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include "common.hpp"
#include "image.hpp"

#include <glad/glad.h>

namespace gfx {
    class Texture {
        public:
            /// Allocates an gpu texture using image data.
            /// image: image to allocate the texture with.
            Texture(const res::Image& image);
            
            /// Allocates an emtpy texture on the gpu
            Texture(u32 width, u32 height, PixelFormat format);

            /// binds this texture to texture0
            void activate();

            /// binds this texture to GL_TEXTURE0 + offset
            void activate_to(u32 offset = 0);

            inline void bind() { glCheck(glBindTexture(GL_TEXTURE_2D, handle)); }

            inline void unbind()  { Texture::unbind_texture(); }

            inline static void unbind_texture() { glCheck(glBindTexture(GL_TEXTURE_2D, 0)); }

            inline u32 id() { return handle; }
            inline u32 id() const { return handle; }
        private:
            
            void initialize(u8* buffer, PixelFormat format);

        private:
            u32 handle{0};
            u32 width;
            u32 height;
    };
}

#endif