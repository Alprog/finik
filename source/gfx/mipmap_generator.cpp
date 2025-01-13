module;
#include "assert.h"
#include "dx.h"
module mipmap_generation;

import app;
import render_system;

MipMapGenerator::MipMapGenerator()
{
    auto& renderSystem = App::GetInstance().render_system;
    auto device = renderSystem.get_device();

    D3D12_ROOT_SIGNATURE_FLAGS rootSignatureFlags =
        D3D12_ROOT_SIGNATURE_FLAG_DENY_VERTEX_SHADER_ROOT_ACCESS |
        D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
        D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
        D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
        D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;

    const CD3DX12_STATIC_SAMPLER_DESC sampler(
        0, // register
        D3D12_FILTER_MIN_MAG_LINEAR_MIP_POINT,
        D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
        D3D12_TEXTURE_ADDRESS_MODE_CLAMP,
        D3D12_TEXTURE_ADDRESS_MODE_CLAMP);

    //const CD3DX12_DESCRIPTOR_RANGE sourceDescriptorRange(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);
    //const CD3DX12_DESCRIPTOR_RANGE targetDescriptorRange(D3D12_DESCRIPTOR_RANGE_TYPE_UAV, 1, 0);

    //CD3DX12_ROOT_PARAMETER rootParameters[RootParameterIndex::RootParameterCount] = {};
    //rootParameters[RootParameterIndex::Constants].InitAsConstants(Num32BitConstants, 0);
    //rootParameters[RootParameterIndex::SourceTexture].InitAsDescriptorTable(1, &sourceDescriptorRange);
    //rootParameters[RootParameterIndex::TargetTexture].InitAsDescriptorTable(1, &targetDescriptorRange);

    //CD3DX12_ROOT_SIGNATURE_DESC rsigDesc;
    //rsigDesc.Init(static_cast<UINT>(std::size(rootParameters)), rootParameters, 1, &sampler, rootSignatureFlags);

    //ComPtr<ID3D12RootSignature> rootSignature;
    //ThrowIfFailed(CreateRootSignature(device, &rsigDesc, rootSignature.ReleaseAndGetAddressOf()));

    //SetDebugObjectName(rootSignature.Get(), L"GenerateMips RootSignature");
}