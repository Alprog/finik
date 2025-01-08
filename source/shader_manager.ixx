module;
#include "asserts.h"
export module shader_manager;

import core;
import shader;
import asset_path;
import effect_manager;
import shader_compiler;

export class ShaderManager : public Singleton<ShaderManager>
{
public:
    ShaderManager()
    {
        auto& compiler = ShaderCompiler::GetInstance();
        fallbackVertexByteCode = compiler.Compile(getFallbackVertexShaderText(), ShaderType::Vertex, "VSMain").bytecode;
        fallbackPixelByteCode = compiler.Compile(getFallbackPixelShaderText(), ShaderType::Pixel, "PSMain").bytecode;
        ASSERT(fallbackVertexByteCode.blob.Get());
        ASSERT(fallbackPixelByteCode.blob.Get());
    }

    void update()
    {
        if (hotReloadNeeded)
        {
            hotReloadOutdated();
            hotReloadNeeded = false;
        }
    }

    std::shared_ptr<Shader> getVertexShader(AssetPath assetPath, const std::string& entryName)
    {
        return getShader({ assetPath, ShaderType::Vertex, entryName });
    }

    std::shared_ptr<Shader> getPixelShader(AssetPath assetPath, const std::string& entryName)
    {
        return getShader({ assetPath, ShaderType::Pixel, entryName });
    }

    std::shared_ptr<Shader> getShader(const ShaderKey& key)
    {
        auto it = Shaders.find_value(key);
        if (it)
        {
            return *it;
        }

        auto shader = std::make_shared<Shader>(key);
        Shaders[key] = shader;
        return shader;
    }

    void onSourceFileChanged()
    {
        hotReloadNeeded = true;
    }

    ShaderByteCode getFallbackByteCode(ShaderType type)
    {
        return type == ShaderType::Vertex ? fallbackVertexByteCode : fallbackPixelByteCode;
    }

private:
    const char* getFallbackVertexShaderText();
    const char* getFallbackPixelShaderText();

    int32 hotReloadOutdated()
    {
        int32 count = 0;
        for (auto& [_, shader] : Shaders)
        {
            if (shader->hotreloadDependencies.isOutdated())
            {
                shader->hotRecompile();
                EffectManager::GetInstance().onShaderChanged(shader);
                count++;
            }
        }
        return count;
    }

private:
    ShaderByteCode fallbackVertexByteCode;
    ShaderByteCode fallbackPixelByteCode;

    HashMap<ShaderKey, std::shared_ptr<Shader>> Shaders;
    bool hotReloadNeeded = false;
};