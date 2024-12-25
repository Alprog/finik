export module shader_manager;

import core;
import shader;
import asset_path;

export class ShaderManager : public Singleton<ShaderManager>
{
public:
    Shader* getVertexShader(AssetPath assetPath, const std::string& entryName)
    {
        return getShader({ assetPath, ShaderType::Vertex, entryName });
    }
    
    Shader* getPixelShader(AssetPath assetPath, const std::string& entryName)
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
        
        auto shader = new Shader(key);
        Shaders[key] = shader;
        return shader;
    }

private:
    std::unordered_map<ShaderKey, Shader*> Shaders;
};