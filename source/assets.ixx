export module assets;

import core;
import texture;
import asset_path;
import hot_reloader;
import file_watcher;
import shader_source_file;
import asset_bundle;

export class Assets : public Singleton<Assets>
{
    friend class AssetsView;

public:
    Assets()
    {
        Path working_directory = toStr(std::filesystem::current_path().c_str());
        AssetDirectory = working_directory / "assets";

        mount(working_directory / "assets");
        mount(working_directory / "mods");
    }

    void mount(Path folder_path)
    {
        bundles.append(AssetBundle(folder_path));
    }

    void unmount(Path folder_path)
    {
        bundles.remove_if([folder_path](const AssetBundle& bundle)
        {
            return bundle.get_folder_path() == folder_path;
        });
    }

    bool exists(AssetPath path)
    {
        // not implemented
        return true;
    }

    bool is_loaded(AssetPath path)
    {
        // not implemented
        return true;
    }

    std::shared_ptr<Texture> GetTexture(AssetPath assetPath)
    {
        auto it = Textures.find(assetPath);
        if (it != Textures.end())
        {
            return it->second;
        }

        auto fullFilePath = Path::combine(AssetDirectory, assetPath);
        FileWatcher::GetInstance().WatchFile(fullFilePath);

        Blob blob(fullFilePath);
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
        auto it = ShaderSourceFiles.find(assetPath);
        if (it != ShaderSourceFiles.end())
        {
            return it->second;
        }

        auto fullFilePath = Path::combine(AssetDirectory, assetPath);
        FileWatcher::GetInstance().WatchFile(fullFilePath);

        Blob blob(fullFilePath);
        auto sourceFile = std::make_shared<ShaderSourceFile>(assetPath);
        sourceFile->HotReload(blob);

        auto sourceFile_ptr = sourceFile.get();
        HotReloader::GetInstance().Add(fullFilePath, [sourceFile_ptr](auto& blob) {
            sourceFile_ptr->HotReload(blob);
            });

        ShaderSourceFiles[assetPath] = sourceFile;
        return sourceFile;
    }

    Array<AssetBundle> bundles;

    Path AssetDirectory;
    HashMap<AssetPath, std::shared_ptr<Texture>> Textures;
    HashMap<AssetPath, std::shared_ptr<ShaderSourceFile>> ShaderSourceFiles;
};