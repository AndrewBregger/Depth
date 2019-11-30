#ifndef ASSET_HPP_
#define ASSET_HPP_

#include "common.hpp"

namespace assets {
    // The first byte is the type of this assset and the last 24 bits uniquely represents
    // this asset. This number is globally unqiue, so technically just these 24 bits can
    // be used to say which asset this refers to, but we would not be able to know which
    // type of asset this is without doing a lookup on the id.
    //
    // Type of zero and 
    typedef u32 AssetId;
    typedef u32 AssetUID; 
    
    enum AssetType : u8 {
        FontAsset = 1,
        TextureAsset,
        ShaderAsset,
        AudioAsset,
    };
    
    
    class Asset {
        public:
        /// constants used by the class
        static const u32 TypeShift = 24;
        
        // Asset contructor.
        Asset(AssetType type, const std::string& name = "");
        
        // Next id to identify assets.
        static AssetId next_id(AssetType type);
        
        // returns what type of asset this is.
        AssetType get_type();
        
        // returns the raw id.
        AssetId get_id();
        
        // returns the last 24 bits of the id.
        // The actual unique identifier.
        AssetUID uid();

		const std::string& name();
        
        private:
        // Unique identifier for this asset.
        AssetId id;
        
        // name of for this asset. 
        std::string n;
        
        // atomic count storing next asset uid.
        static std::atomic<u32> ID_TOKEN;
    };
}

#endif
