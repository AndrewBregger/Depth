#include "spritesheet.hpp"

namespace gfx {
    SpriteSheet::SpriteSheet(const res::Image& image, const glm::ivec2& dem) :
        Texture(image), dem(dem) {
        auto w = width();
        auto h = height();

        // compute the number of elements in this sprite sheet.
        image_deminsions = {w / dem.x, h / dem.y};
    }

    glm::vec4 SpriteSheet::get_at(u32 x, u32 y,  bool& valid) {
        auto iter = cache.find(std::make_pair(x, y ));
        if (iter == cache.end()) {
            if (x < image_deminsions.x && y < image_deminsions.y) {
                valid = true;
                auto loc = glm::vec4((f32) (x * dem.x) / width(), (f32) (y * dem.y) / height(), (f32) dem.x / width(), (f32) dem.y / height());
                cache.emplace(std::make_pair(x, y), loc);
                return loc;
            }
            else {
                valid = false;
                return glm::vec4();
            }
        }
        else {
            valid = true;
            return iter->second;
        }
    }

    glm::vec4 SpriteSheet::get_at(const glm::ivec2& index, bool& valid) {
      return get_at(index.x, index.y, valid);
    }
}
