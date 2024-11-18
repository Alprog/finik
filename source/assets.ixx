export module assets;

import core;
import texture;
import shader;
import asset_path;
import hot_reloader;

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

    std::shared_ptr<Texture> GetTexture(AsssetPath path)
    {
        auto it = Textures.find(path);
        if (it != Textures.end())
        {
            return it->second;
        }

        auto texture = std::make_shared<Texture>(path);

        HotReloader::GetInstance().Add(path, [](auto& blob) {
            //
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