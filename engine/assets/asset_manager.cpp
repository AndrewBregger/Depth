#include "asset_manager.hpp"
#include "utils/image.hpp"

#include "gfx/shader.hpp"
#include "gfx/texture.hpp"
#include "gfx/texture_atlas.hpp"
#include "gfx/spritesheet.hpp"

#include <algorithm>

namespace assets {
    AssetManager::AssetManager() = default;

    AssetId AssetManager::load_texture(const std::string& path) {
        LOG_MSG("LOADING texture: {}", path);
        auto image = res::Image::from_file(path);
        auto texture = new gfx::Texture(image);
        assets.emplace(texture->get_id(), texture);

        return texture->get_id();
    }

	AssetId AssetManager::load_texture_atlas(const AtlasInfo& atlas_info) {
		auto texture = new gfx::TextureAtlas(atlas_info.width, atlas_info.height, atlas_info.format);

		for (const auto& path : atlas_info.images) {
			LOG_MSG("LOADING texture atlas {}", path);
			auto image = res::Image::from_file(path);
			if (!texture->add_image(image)) {
				LOG_ERR("Failed to add image {} to atlas", path);
			}
		}

        assets.emplace(texture->get_id(), texture);
		return texture->get_id();
	}

    // loads and creates a sprite sheet.
    AssetId AssetManager::load_spritesheet(const SpriteSheetInfo& sheet_info) {
        LOG_MSG("LOADING SpriteSheet: {}", sheet_info.path);
        auto image = res::Image::from_file(sheet_info.path);

        auto sheet = new gfx::SpriteSheet(image, sheet_info.dem);
        assets.emplace(sheet->get_id(), sheet);
        return sheet->get_id();
    }

    AssetId AssetManager::load_font(const std::string& path) {
        LOG_MSG("LOADING font: {}", path);
        return 0;
    }

    AssetId AssetManager::load_shader(const ShaderInfo& info) {
        LOG_MSG("LOADING shader: {}", info.name);
        auto shader = new gfx::Shader(info.name, info.vs, info.fs, info.gs);
        assets.emplace(shader->get_id(), shader);
        return shader->get_id();
    }

    AssetId AssetManager::load_audio() {
        return 0;
    }

    Asset* AssetManager::get_asset(AssetId id) {
        if (id == 0)
            return nullptr;

        auto asset_iter = assets.find(id);
        if (asset_iter != assets.end()) {
            return asset_iter->second.get();
        }
        else {
            return nullptr;
        }
    }

	Asset* AssetManager::get_asset(const std::string& name) {
		if (name.empty()) {
			return nullptr;
		}

		auto asset_iter = std::find_if(assets.begin(), assets.end(), [&name](const auto& asset) {
					return asset.second->name() == name;
				});

		if (asset_iter != assets.end()) {
			return asset_iter->second.get();
		}

		return nullptr;
	}
}
