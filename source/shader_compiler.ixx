export module shader_compiler;

import core;
import singleton;
import asset_path;

export class ShaderCompiler
{
public:
    ShaderCompiler GetInstance()
    {
        static ShaderCompiler instance;
        return instance;
    }

    void AddIncludeDirectory(AssetPath directory)
    {
        InlcudeDirectories.push_back(directory);
    }

    std::vector<AssetPath> InlcudeDirectories;
};