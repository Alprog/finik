export module shader_compiler;

import core;
import asset_path;
import shader;

export class ShaderCompiler : public Singleton<ShaderCompiler>
{
public:
    void Compile(ShaderKey key, ShaderByteCode& bytecodeBlob);

    void AddIncludeDirectory(AssetPath directory)
    {
        InlcudeDirectories.push_back(directory);
    }

    std::vector<AssetPath> InlcudeDirectories;
};