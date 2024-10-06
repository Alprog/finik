
#include "shader.h"
#include <d3dcompiler.h>

import blob;

Shader::Shader(Path path, ShaderType type, const std::string& entryPoint)
    : type{ type }
{
    Blob fileBlob(path);

    auto& source = fileBlob.asString();

    auto target = type == ShaderType::Vertex ? "vs_5_0" : "ps_5_0";
    UINT compileFlags = 0;

    ID3DBlob* errorBlob = nullptr;
    auto result = D3DCompile(source.data(), source.size(), entryPoint.c_str(), nullptr, nullptr, entryPoint.c_str(), target, compileFlags, 0, &blob, &errorBlob);

    if (FAILED(result))
    {
        if (errorBlob)
        {
            char* str = static_cast<char*>(errorBlob->GetBufferPointer());
            errorBlob->Release();
        }
        throw;
    }
}
