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

    std::shared_ptr<Asset> get_asset()
    {
        if (!is_loaded())
        {
            create_asset();
            load();
        }
        return loaded_asset;
    }

    void create_asset();

    void load()
    {
        if (actual_bundle)
        {
            loaded_asset->hot_reload(actual_bundle->get(virtual_path));
        }
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