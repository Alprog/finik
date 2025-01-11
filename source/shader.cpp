module shader;

import shader_compiler;
import shader_manager;

Shader::Shader(ShaderKey key)
    : key{key}
{
    hotRecompile();
}

bool Shader::hotRecompile()
{
    auto& output = ShaderCompiler::GetInstance().Compile(key);

    const bool successed = output.errorMessage.empty();

    errorMessage = output.errorMessage;

    if (successed)
    {
        // use new bytecode and source file dependencies (includes)
        bytecode = output.bytecode;
        hotreloadDependencies = output.sourceAssets;
    }
    else
    {
        // if compilation failed, we use fallback shader bytecode
        // and keep old source file dependencies (we will try again once these files change again)
        bytecode = ShaderManager::GetInstance().getFallbackByteCode(key.Type);
        hotreloadDependencies.actualize();
    }

    if (hotreloadDependencies.empty())
    {
        hotreloadDependencies = output.sourceAssets;
    }

    return successed;
}
