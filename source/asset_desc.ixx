export module asset_desc;

import core;
import asset;
import asset_path;
import asset_bundle;

export struct AssetDesc
{
    AssetDesc() = default;

    AssetDesc(AssetPath virtual_path, AssetBundle* bundle, int32 version = 0)
        : virtual_path { virtual_path }
        , actual_bundle{ bundle }
        , version { version }
    {
    }

    bool is_loaded() const
    {
        return loaded_asset != nullptr;
    }

    std::strong_ordering operator<=>(AssetDesc& another)
    {
        return virtual_path <=> another.virtual_path;
    }

    AssetPath virtual_path;
    
    int32 version;
    AssetBundle* actual_bundle;

    std::shared_ptr<Asset> loaded_asset;
};