module;
#include "gfx/dx.h"
#include <d3dcompiler.h>
module shader;

import blob;

class IncludeHandler : public ID3DInclude {
public:
    HRESULT __stdcall Open(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID* ppData, UINT* pBytes) override {
        
        Path path = Path("C:/finik/shaders") / pFileName;
        
        Blob fileBlob(path);

        char* data = new char[fileBlob.size()];
        memcpy(data, fileBlob.data(), fileBlob.size());

        *ppData = data;
        *pBytes = static_cast<UINT>(fileBlob.size());
        return S_OK;
    }

    HRESULT __stdcall Close(LPCVOID pData) override {
        // Free the memory allocated in Open
        delete[] pData;
        return S_OK;
    }
};

Shader::Shader(Path path, ShaderType type, const std::string& entryPoint)
    : type{ type }
{
    Blob fileBlob(path);

    auto& source = fileBlob.asString();

    auto target = type == ShaderType::Vertex ? "vs_5_1" : "ps_5_1";
    uint32 compileFlags = D3DCOMPILE_ENABLE_UNBOUNDED_DESCRIPTOR_TABLES;

    ID3DBlob* errorBlob = nullptr;
    
    static IncludeHandler includeHandler;
    auto result = D3DCompile(source.data(), source.size(), entryPoint.c_str(), nullptr, &includeHandler, entryPoint.c_str(), target, compileFlags, 0, &blob, &errorBlob);

    if (FAILED(result))
    {
        if (errorBlob)
        {
            char* str = static_cast<char*>(errorBlob->GetBufferPointer());
            errorBlob->Release();
            throw;
        }
        throw;
    }
}
