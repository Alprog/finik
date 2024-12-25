export module shader_manager;

import core;
import shader;
import asset_path;

export class ShaderManager : public Singleton<ShaderManager>
{
public:
    Shader* getVertexShader(AssetPath assetPath, std::string& entryName)
    {
        return getShader({ assetPath, ShaderType::Pixel, entryName });
    }
    
    Shader* getPixelShader(AssetPath assetPath, std::string& entryName)
    {
        return getShader({ assetPath, ShaderType::Pixel, entryName });
    }

    Shader* getShader(const ShaderKey& key)
    {
        auto it = Shaders.find(key);
        if (it != std::end(Shaders))
        {
            return it->second;
        }
        return nullptr;
    }

private:
    std::unordered_map<ShaderKey, Shader*> Shaders;
};