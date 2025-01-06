export module shader_manager;

import core;
import shader;
import asset_path;

export class ShaderManager : public Singleton<ShaderManager>
{
public:
    void update()
    {
        if (sourceFilesChanged)
        {
            hotReloadOutdated();
            sourceFilesChanged = false;
        }
    }

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
        auto it = Shaders.find_value(key);
        if (it)
        {
            return it->get();
        }

        auto shader = std::make_shared<Shader>(key);
        Shaders[key] = shader;
        return shader.get();
    }

    void onSourceFileChanged()
    {
        sourceFilesChanged = true;
    }

private:
    int32 hotReloadOutdated()
    {
        int32 count = 0;
        for (auto& [_, shader] : Shaders)
        {
            if (shader->dependencies.isOutdated())
            {
                shader->Recompile();
                count++;
            }
        }
        return count;
    }

private:
    HashMap<ShaderKey, std::shared_ptr<Shader>> Shaders;
    bool sourceFilesChanged = false;
};