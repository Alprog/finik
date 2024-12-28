export module asset_bundle;

import core;
import asset_path;

export class AssetBundle
{
public:
    AssetBundle(Path folder_path)
        : folder_path{ folder_path }
    {
    }

    Path get_folder_path() const
    {
        return folder_path;
    }

    int32 get_asset_count();

private:
    Path folder_path;
};