#ifndef ASSET_MANAGER_HPP_
#define ASSET_MANAGER_HPP_

#include "common.hpp"
#include <memory>
#include <unordered_map>
#include <optional>
#include "asset.hpp"
#include "utils/singleton.hpp"

namespace assets {
    struct ShaderInfo {
        std::string name;
        std::string vs;
        std::optional<std::string> gs;
        std::string fs;
    };

	struct AtlasInfo {
		u32 width;
		u32 height;
		PixelFormat format;
		std::vector<std::string> images;
	};

    struct SpriteSheetInfo {
        // std::string name;
        std::string path;
        glm::ivec2 dem;
    };

    class AssetManager : public utils::Singleton<AssetManager> {
        public:

        AssetManager();

        // loads and creates a texture from a give path.
        AssetId load_texture(const std::string& path);

        // loads and creates a texture atlas from a atlas information
        AssetId load_texture_atlas(const AtlasInfo& atlas_info);

        // loads and creates a sprite sheet.
        AssetId load_spritesheet(const SpriteSheetInfo& sheet_info);

        // loads and creates a font from path
        AssetId load_font(const std::string& path);

        /// loads and creates a shader from shader info
        AssetId load_shader(const ShaderInfo& info);

        /// loads and creates audio samples from...
        AssetId load_audio();

        Asset* get_asset(AssetId id);

        Asset* get_asset(const std::string& name);

        template <typename Type> Type* get_asset_as(AssetId id);

        template <typename Type> Type* get_asset_as(const std::string& name);

        private:
        std::unordered_map<AssetId, std::unique_ptr<Asset>> assets;
    };

    template <typename Type> Type* AssetManager::get_asset_as(AssetId id) {
        auto asset = get_asset(id);

        // use then once asset become polymorphic.
        // return asset ? dynamic_cast<Type*>(asset) : nullptr;
        return asset ? static_cast<Type*>(asset) : nullptr;
    }

	template <typename Type> Type* AssetManager::get_asset_as(const std::string& name) {
		auto asset = get_asset(name);
        return asset ? static_cast<Type*>(asset) : nullptr;
	}
}

#endif
