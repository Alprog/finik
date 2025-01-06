export module shader_compiler;

import core;
import asset_path;
import shader;
import asset_dependencies;

export class ShaderCompiler : public Singleton<ShaderCompiler>
{
public:
    void Compile(ShaderKey key, ShaderByteCode& bytecodeBlob, AssetDependencies& dependencies);

    void AddIncludeDirectory(AssetPath directory)
    {
        InlcudeDirectories.append(directory);
    }

    Array<AssetPath> InlcudeDirectories;
};