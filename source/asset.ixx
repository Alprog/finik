export module asset;

import core;
import asset_path;
import blob;

export class Asset
{
public:
    Asset(AssetPath assetPath)
        : assetPath{ assetPath }
        , version { 0 }
    {
    }

    virtual void HotReload(Blob& blob) = 0;

    int32 get_version() const { return version; }

protected:
    int32 version;
    AssetPath assetPath;
};