export module assets;

import core;
import texture;
import asset_path;
import hot_reloader;
import file_watcher;
import shader_source_file;
import asset_bundle;
import asset_folder;
import asset_desc;
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
                    auto it = asset_descs.find_value(path);
                    if (!it)
                    {
                        // add fully new
                        asset_descs[path] = AssetDesc(path, &bundle);
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
                    auto it = asset_descs.find_value(path);
                    if (it && it->actual_bundle == &bundle)
                    {
                        it->version++;
                    }
                    status = AssetStatus::Synced;
                    break;
                }                    

                case AssetStatus::Removing:
                    auto it = asset_descs.find_value(path);
                    if (it && it->actual_bundle == &bundle)
                    {
                        it->actual_bundle = nullptr;
                        for (int32 index = bundle.priority - 1; index >= 0; index--)
                        {
                            if (bundles[index]->has(path))
                            {
                                it->actual_bundle = bundles[index];
                                it->version++;
                                break;
                            }
                        }
                        if (!it->actual_bundle && !it->is_loaded())
                        {
                            asset_descs.remove(path);
                        }
                    }
                    break;
                }
            }

            bundle.entries.remove_if([](auto& pair) { return pair.second == AssetStatus::Removing; });

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
        return asset_descs.contains(path);
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

        ByteBlob blob(fullFilePath);
        auto texture = std::make_shared<Texture>(blob);

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

        ByteBlob blob(fullFilePath);
        auto sourceFile = std::make_shared<ShaderSourceFile>(assetPath);
        sourceFile->HotReload(blob);

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
    HashMap<AssetPath, AssetDesc> asset_descs;

    Array<AssetBundle*> bundles;

    Path AssetDirectory;
    HashMap<AssetPath, std::shared_ptr<Texture>> Textures;
    HashMap<AssetPath, std::shared_ptr<ShaderSourceFile>> ShaderSourceFiles;
};