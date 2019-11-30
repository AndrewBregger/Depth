#include "asset.hpp"
#include <atomic>

namespace assets {
    std::atomic<u32> Asset::ID_TOKEN = 0;
    
    Asset::Asset(AssetType type, const std::string& name) : id(next_id(type)), n(name) {
    }
    
    AssetType Asset::get_type() {
        return static_cast<AssetType>((id >> TypeShift) & 0xff);
    }
    
    AssetId Asset::get_id() {
        return id;
    }
    
    AssetUID Asset::uid() {
        return id & 0x00ffffff;
    }

	const std::string& Asset::name() {
		return n;
	}
    
    AssetId Asset::next_id(AssetType type) {
        auto id = ID_TOKEN.fetch_add(1);
        return static_cast<AssetId>((type << TypeShift) | id);
    }
}
