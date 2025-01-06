module shader;

import shader_compiler;

Shader::Shader(ShaderKey key)
    : key { key }
{
    Recompile();
}

void Shader::Recompile()
{
    ShaderCompiler::GetInstance().Compile(key, bytecodeBlob, dependencies);
}
