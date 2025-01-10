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

    void hot_reload(ByteBlob& blob, int32 version)
    {
        hot_reload(blob);
        this->version = version;
    }

    int32 get_version() const { return version; }

protected:
    virtual void hot_reload(ByteBlob& blob) = 0;

protected:
    int32 version;
    AssetPath assetPath;
};