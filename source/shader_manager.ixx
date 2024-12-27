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
        if (auto it = Shaders.find_value(key))
        {
            return *it;
        }

        auto shader = new Shader(key);
        Shaders[key] = shader;
        return shader;
    }

private:
    HashMap<ShaderKey, Shader*> Shaders;
};