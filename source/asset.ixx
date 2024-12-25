export module asset;

import core;
import asset_path;
import blob;

export class Asset
{
public:
    Asset(AssetPath assetPath)
        : assetPath{ assetPath }
    {
    }

    virtual void HotReload(Blob& blob) = 0;

private:
    AssetPath assetPath;
};