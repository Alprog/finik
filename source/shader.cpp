module shader;

import shader_compiler;
import shader_manager;

Shader::Shader(ShaderKey key)
    : key{ key }
{
    hotRecompile();
}

bool Shader::hotRecompile()
{
    auto& output = ShaderCompiler::GetInstance().Compile(key);
    errorMessage = output.errorMessage;
    if (errorMessage.empty())
    {
        // if successeded use new bytecode and source file dependencies (includes)
        bytecode = output.bytecode;
        hotreloadDependencies = output.sourceAssets;
    }
    else
    {
        // if compilation failed, we use fallback shader bytecode
        // but keep old source file dependencies (we will try again once these files change again)
        bytecode = ShaderManager::GetInstance().getFallbackByteCode(key.Type);
        hotreloadDependencies.actualize();
    }

    return true;
}
