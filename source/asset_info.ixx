export module asset_info;

import core;
import asset;
import asset_path;
import asset_bundle;

export struct AssetInfo
{
    bool is_loaded() const
    {
        return loaded_asset != nullptr;
    }

    std::strong_ordering operator<=>(AssetInfo& another)
    {
        return virtual_path <=> another.virtual_path;
    }

    AssetPath virtual_path;
    
    int32 actual_version;
    AssetBundle* actual_bundle;

    std::shared_ptr<Asset> loaded_asset;
};