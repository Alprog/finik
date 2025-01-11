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
    IncludeHandler(AssetDependencies& sourceAssets)
        : sourceAssets{sourceAssets}
    {
    }

    HRESULT __stdcall Open(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID* ppData,
                           UINT* pBytes) override
    {
        std::shared_ptr<ShaderSourceFile> sourceFile = Assets::GetInstance().get<ShaderSourceFile>(pFileName);
        sourceAssets.add(sourceFile);

        const std::string& sourceText = sourceFile->GetSourceText();

        *ppData = &sourceText[0];
        *pBytes = static_cast<UINT>(sourceText.size());
        return S_OK;
    }

    HRESULT __stdcall Close(LPCVOID pData) override
    {
        return S_OK;
    }

private:
    AssetDependencies& sourceAssets;
};

ShaderCompiler::Output ShaderCompiler::Compile(ShaderKey key)
{
    std::shared_ptr<ShaderSourceFile> source_file = Assets::GetInstance().get<ShaderSourceFile>(key.AssetPath);
    const String& sourceText = source_file->GetSourceText();

    auto output = Compile(sourceText, key.Type, key.EntryPoint);
    output.sourceAssets.add(source_file);
    return output;
}

ShaderCompiler::Output ShaderCompiler::Compile(const String& sourceText, ShaderType type, const String& entryPoint)
{
    Output output;

    auto target = type == ShaderType::Vertex ? "vs_5_1" : "ps_5_1";
    uint32 compileFlags = D3DCOMPILE_ENABLE_UNBOUNDED_DESCRIPTOR_TABLES;

    ID3DBlob* errorBlob = nullptr;

    IncludeHandler includeHandler(output.sourceAssets);
    auto result = D3DCompile(&sourceText[0], sourceText.length(), entryPoint.c_str(), nullptr, &includeHandler,
                             entryPoint.c_str(), target, compileFlags, 0, &output.bytecode, &errorBlob);

    if (FAILED(result))
    {
        if (errorBlob)
        {
            output.errorMessage = static_cast<char*>(errorBlob->GetBufferPointer());
            errorBlob->Release();
        }
        else
        {
            output.errorMessage = "unknown error";
        }
    }

    return output;
}