export module asset_desc;

import core;
import asset;
import asset_path;
import asset_bundle;

export struct AssetDesc
{
    AssetDesc() = default;

    AssetDesc(AssetPath virtual_path, AssetBundle* bundle)
        : virtual_path { virtual_path }
        , actual_bundle{ bundle }
        , version { 0 }
    {
    }

    std::shared_ptr<Asset> get_asset()
    {
        if (!is_loaded())
        {
            create_asset();
            reload();
        }
        return loaded_asset;
    }

    void create_asset();

    void reload()
    {
        if (actual_bundle)
        {
            loaded_asset->hot_reload(actual_bundle->get(virtual_path), version);
        }
    }
       
    bool is_loaded() const
    {
        return loaded_asset != nullptr;
    }

    bool need_reload() const
    {
        return loaded_asset && loaded_asset->get_version() != version;
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