export module assets;

import core;
import texture;
import asset_path;
import hot_reloader;
import file_watcher;
import shader_source_file;

export class Assets
{
    friend class AssetsView;

public:
    static Assets& GetInstance()
    {
        static Assets instance;
        return instance;
    }

    Assets()
    {
        AssetDirectory = toStr(std::filesystem::current_path().c_str());
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

    Path AssetDirectory;
    std::unordered_map<Path, std::shared_ptr<Texture>> Textures;
    std::unordered_map<Path, std::shared_ptr<ShaderSourceFile>> ShaderSourceFiles;
};