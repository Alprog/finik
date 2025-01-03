export module assets;

import core;
import texture;
import asset_path;
import hot_reloader;
import file_watcher;
import shader_source_file;
import asset_bundle;
import asset_folder;
import asset_info;
import byte_blob;

export class Assets : public Singleton<Assets>
{
    friend class AssetsView;

public:
    Assets()
    {
        Path working_directory = toStr(std::filesystem::current_path().c_str());
        AssetDirectory = working_directory / "assets";

        mount_folder(working_directory / "assets");
        mount_folder(working_directory / "mods");

        update();
    }

    ~Assets()
    {
        for (auto p_bundle : bundles)
        {
            delete p_bundle;
        }
    }

    void update()
    {
        for (auto p_bundle : bundles)
        {
            p_bundle->update();
        }

        for (auto p_bundle : bundles)
        {
            sync_bundle(*p_bundle);
        }
    }

    void sync_bundle(AssetBundle& bundle)
    {
        if (!bundle.synced)
        {
            for (auto& [path, status] : bundle.entries)
            {
                switch (status)
                {
                case AssetStatus::Added:
                {
                    auto it = asset_infos.find_value(path);
                    if (!it)
                    {
                        // add fully new
                        asset_infos[path] = AssetInfo(path, &bundle);
                    }
                    else
                    {
                        if (bundle.priority > it->actual_bundle->priority)
                        {
                            // override existing
                            it->actual_bundle = &bundle;
                            it->version++;
                        }
                    }
                    status = AssetStatus::Synced;
                    break;
                }
                    
                case AssetStatus::Modified:
                {
                    auto it = asset_infos.find_value(path);
                    if (it && it->actual_bundle == &bundle)
                    {
                        it->version++;
                    }
                    status = AssetStatus::Synced;
                    break;
                }                    

                case AssetStatus::Removing:
                    // not implemented
                    break;
                }
            }

            bundle.synced = true;
        }
    }

    void mount_folder(Path folder_path)
    {
        auto folder = new AssetFolder(folder_path);
        bundles.append(folder);
        refresh_bundle_priorities();
    }

    void unmount_folder(Path folder_path)
    {
        bundles.remove_if([folder_path](auto& p_bundle)
        {
            auto asset_folder = dynamic_cast<AssetFolder*>(p_bundle);
            return asset_folder && asset_folder->get_folder_path() == folder_path;;
        });
        refresh_bundle_priorities();
    }

    bool exists(AssetPath path)
    {
        return asset_infos.contains(path);
    }

    bool is_loaded(AssetPath path)
    {
        // not implemented
        return true;
    }

    std::shared_ptr<Texture> GetTexture(AssetPath assetPath)
    {
        auto it = Textures.find_value(assetPath);
        if (it)
        {
            return *it;
        }

        auto fullFilePath = Path::combine(AssetDirectory, assetPath);
        FileWatcher::GetInstance().WatchFile(fullFilePath);

        ByteBlob blob(fullFilePath);
        auto texture = std::make_shared<Texture>(blob);

        auto texture_ptr = texture.get();
        HotReloader::GetInstance().Add(fullFilePath, [texture_ptr](auto& blob) {
            texture_ptr->HotReload(blob);
        });

        Textures[assetPath] = texture;
        return texture;
    }

    std::shared_ptr<ShaderSourceFile> GetShaderSourceFile(AssetPath assetPath)
    {
        auto it = ShaderSourceFiles.find_value(assetPath);
        if (it)
        {
            return *it;
        }

        auto fullFilePath = Path::combine(AssetDirectory, assetPath);
        FileWatcher::GetInstance().WatchFile(fullFilePath);

        ByteBlob blob(fullFilePath);
        auto sourceFile = std::make_shared<ShaderSourceFile>(assetPath);
        sourceFile->HotReload(blob);

        auto sourceFile_ptr = sourceFile.get();
        HotReloader::GetInstance().Add(fullFilePath, [sourceFile_ptr](auto& blob) {
            sourceFile_ptr->HotReload(blob);
        });

        ShaderSourceFiles[assetPath] = sourceFile;
        return sourceFile;
    }

private:
    void refresh_bundle_priorities()
    {
        int32 index = 0;
        for (auto& bundle : bundles)
        {
            bundle->priority = index++;
        }
    }

private:
    HashMap<AssetPath, AssetInfo> asset_infos;

    Array<AssetBundle*> bundles;

    Path AssetDirectory;
    HashMap<AssetPath, std::shared_ptr<Texture>> Textures;
    HashMap<AssetPath, std::shared_ptr<ShaderSourceFile>> ShaderSourceFiles;
};