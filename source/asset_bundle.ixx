export module asset_bundle;

import core;
import asset_path;

export enum class AssetStatus
{
    Added,
    Synced,
    Modified,
    Removing,
};

export class AssetBundle
{
    friend class Assets;

public:
    AssetBundle() = default;
    virtual ~AssetBundle() = default;

    virtual void update() = 0;

    int32 get_priority() const { return priority; }

    bool has(AssetPath asset_path) const
    {
        return entries.contains(asset_path);
    }

protected:
    SortedMap<AssetPath, AssetStatus> entries;

    bool synced = false;
    int32 priority = 0;
};

