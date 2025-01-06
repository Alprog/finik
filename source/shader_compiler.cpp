module;
#include "gfx/dx.h"
#include <d3dcompiler.h>
module shader_compiler;

import assets;
import shader_source_file;
import byte_blob;
import asset_dependencies;

class IncludeHandler : public ID3DInclude
{
public:
    IncludeHandler(AssetDependencies& dependencies)
        : dependencies{ dependencies }
    {
    }

    HRESULT __stdcall Open(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID* ppData, UINT* pBytes) override
    {
        std::shared_ptr<ShaderSourceFile> sourceFile = Assets::GetInstance().get<ShaderSourceFile>(pFileName);
        dependencies.add(sourceFile);

        const std::string& sourceText = sourceFile->GetSourceText();

        *ppData = &sourceText[0];
        *pBytes = static_cast<UINT>(sourceText.size());
        return S_OK;
    }

    HRESULT __stdcall Close(LPCVOID pData) override {
        return S_OK;
    }

private:
    AssetDependencies& dependencies;
};

void ShaderCompiler::Compile(ShaderKey key, ShaderByteCode& bytecodeBlob, AssetDependencies& dependencies)
{   
    dependencies = {};

    std::shared_ptr<ShaderSourceFile> source_file = Assets::GetInstance().get<ShaderSourceFile>(key.AssetPath);
    dependencies.add(source_file);

    const std::string& source = source_file->GetSourceText();

    auto target = key.Type == ShaderType::Vertex ? "vs_5_1" : "ps_5_1";
    uint32 compileFlags = D3DCOMPILE_ENABLE_UNBOUNDED_DESCRIPTOR_TABLES;

    ID3DBlob* errorBlob = nullptr;

    IncludeHandler includeHandler(dependencies);
    auto result = D3DCompile(source.data(), source.size(), key.EntryPoint.c_str(), nullptr, &includeHandler, key.EntryPoint.c_str(), target, compileFlags, 0, &bytecodeBlob, &errorBlob);

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
