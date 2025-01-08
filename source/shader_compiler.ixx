export module shader_compiler;

import core;
import asset_path;
import shader;
import asset_dependencies;

export class ShaderCompiler : public Singleton<ShaderCompiler>
{
public:
    struct Output
    {
        ShaderByteCode bytecode;
        AssetDependencies sourceAssets;
        String errorMessage;
    };

    Output Compile(ShaderKey key);
    Output Compile(const String& sourceText, ShaderType type, const String& entryPoint);

    void AddIncludeDirectory(AssetPath directory)
    {
        InlcudeDirectories.append(directory);
    }

    Array<AssetPath> InlcudeDirectories;



    static int32 Counter;
};