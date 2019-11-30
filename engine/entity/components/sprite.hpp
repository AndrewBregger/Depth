#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include "common.hpp"
#include "gfx/color.hpp"
#include "assets/asset.hpp"
#include "entity/component.hpp"

namespace entity {
    class Sprite : public entity::Component {
        public:
        
        Sprite(assets::AssetId texture, glm::vec4 coords, gfx::Color hue = gfx::Color::White);

        Sprite(assets::AssetId texture, gfx::Color hue = gfx::Color::White);
        
		assets::AssetId asset();
        
        const glm::vec4& coords();
		const gfx::Color& hue();
        
        private:
		
		/// raw image asset.
		assets::AssetId texture;
		/// (x, y) the the base coordinates, (z, w) the dimensions.
		glm::vec4 coordinates;
		/// a color to be added to the image.
		gfx::Color texture_hue;
    };
}

#endif
