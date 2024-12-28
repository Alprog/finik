export module asset_bundle;

import core;
import asset_path;

export class AssetBundle
{
public:
    AssetBundle(Path folder_path)
        : folder_path{ folder_path }
    {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(folder_path.str()))
        {
            if (entry.is_regular_file())
            {
                const Path file_path = entry.path();
                const AssetPath relative_path = file_path.getRelativeTo(folder_path);
                std::cout << entry.path() << std::endl;
            }
        }
    }

    Path get_folder_path() const
    {
        return folder_path;
    }

    int32 get_asset_count();

private:
    Path folder_path;
};