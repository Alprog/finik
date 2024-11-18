export module assets;

import core;
import texture;
import shader;
import asset_path;
import hot_reloader;
import file_watcher;

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

    std::shared_ptr<Texture> GetTexture(AsssetPath assetPath)
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

    Shader* GetShader(AsssetPath path)
    {
        return nullptr;
    }

    Path AssetDirectory;
    std::unordered_map<Path, std::shared_ptr<Texture>> Textures;
};