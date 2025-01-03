export module asset;

import core;
import asset_path;
import byte_blob;

export class Asset
{
public:
    Asset(AssetPath assetPath)
        : assetPath{ assetPath }
        , version { -1 }
    {
    }

    virtual void hot_reload(ByteBlob& blob) = 0;

    int32 get_version() const { return version; }

protected:
    int32 version;
    AssetPath assetPath;
};