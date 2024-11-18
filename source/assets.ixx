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

        FileWatcher::GetInstance().WatchDirectory("C:/finik/textures");
    }

    std::shared_ptr<Texture> GetTexture(AsssetPath path)
    {
        auto it = Textures.find(path);
        if (it != Textures.end())
        {
            return it->second;
        }

        auto texture = std::make_shared<Texture>(path);

        auto texture_ptr = texture.get();
        HotReloader::GetInstance().Add(path, [texture_ptr](auto& blob) {
            texture_ptr->HotReload(blob);
        });

        Textures[path] = texture;
        return texture;
    }

    Shader* GetShader(AsssetPath path)
    {
        return nullptr;
    }

    Path AssetDirectory;
    std::unordered_map<Path, std::shared_ptr<Texture>> Textures;
};