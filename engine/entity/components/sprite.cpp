#include "sprite.hpp"


namespace entity {
	Sprite::Sprite(assets::AssetId texture, glm::vec4 coords, gfx::Color hue) :
		texture(texture), coordinates(coords), texture_hue(hue) {
		// @todo: make sure the asset type is a texture.
	}

	Sprite::Sprite(assets::AssetId texture, gfx::Color hue) : 
		Sprite(texture, {0, 0, 1, 1}, hue) {
	}

	assets::AssetId Sprite::asset() { return texture; }

	const glm::vec4& Sprite::coords() { return coordinates; }

	const gfx::Color& Sprite::hue() { return texture_hue; }
}

