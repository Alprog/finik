
#include "shader.h"
#include "blob.h"
#include <d3dcompiler.h>

Shader::Shader(Path path, ShaderType type, const std::string& entryPoint)
    : type{ type }
{
    Blob fileBlob(path);

    auto& source = fileBlob.asString();

    auto target = type == ShaderType::Vertex ? "vs_5_0" : "ps_5_0";
    UINT compileFlags = 0;

    auto result = D3DCompile(source.data(), source.size(), entryPoint.c_str(), nullptr, nullptr, entryPoint.c_str(), target, compileFlags, 0, &blob, nullptr);

    if (FAILED(result)) throw;
}
