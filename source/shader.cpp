module;
#include "gfx/dx.h"
#include <d3dcompiler.h>
module shader;

import types;
import blob;
import path;

Shader::Shader(Path path, ShaderType type, const std::string& entryPoint)
    : type{ type }
{
    Blob fileBlob(path);

    auto& source = fileBlob.asString();

    auto target = type == ShaderType::Vertex ? "vs_5_0" : "ps_5_0";
    uint32 compileFlags = 0;

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
