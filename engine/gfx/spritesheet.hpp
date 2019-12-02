#ifndef SPRITE_SHEET_HPP_
#define SPRITE_SHEET_HPP_

#include "texture.hpp"
#include "utils/image.hpp"

#include <glm/glm.hpp>

namespace gfx {
    class SpriteSheet : public Texture {
        public:
            /// Construct spritesheet.
            SpriteSheet(const res::Image& image, const glm::ivec2& dem);

            /// gets the texture info at (x, y)
            glm::vec4 get_at(u32 x, u32 y, bool& valid);

            /// gets the texture info at 2d index.
            glm::vec4 get_at(const glm::ivec2& index, bool& valid);

            inline const glm::ivec2& deminsions() { return dem; }

        private:
            /// deminsions of each sprite in the sheet.
            glm::ivec2 dem;
            /// the number of images in the sheet.
            glm::ivec2 image_deminsions;
            /// cache of all images already calculated.
            std::unordered_map<std::pair<u32, u32>, glm::vec4> cache;
    };
}

#endif
