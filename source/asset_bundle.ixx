export module asset_bundle;

import core;
import asset_path;

export class AssetBundle
{
public:
    AssetBundle() = default;
    virtual ~AssetBundle() = default;

    virtual bool has(AssetPath asset_path) = 0;
};

export class AssetFolder : public AssetBundle
{
public:
    AssetFolder(Path folder_path)
        : folder_path{ folder_path }
    {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(folder_path.str()))
        {
            if (entry.is_regular_file())
            {
                const Path file_path = entry.path();
                const AssetPath relative_path = file_path.getRelativeTo(folder_path);
                asset_pathes.insert(relative_path);
            }
        }
    }

    bool has(AssetPath asset_path) override
    {
        // not implemented
        return true;
    }

    Path get_folder_path() const
    {
        return folder_path;
    }

    int32 get_asset_count()
    {
        // not implemented
        return 0;
    }

    SortedArray<AssetPath> asset_pathes;

private:
    Path folder_path;
};