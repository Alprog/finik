module;
#include "dx.h"
module root_signature;

import render_system;
import root_signature_params;
import shader;

RootSignature::RootSignature(RenderSystem& renderSystem)
{
    CD3DX12_ROOT_PARAMETER rootParameters[RootSignatureParams::Count];

    rootParameters[RootSignatureParams::UnboundTextureTable].InitAsDescriptorTable(
        1, &CD3DX12_DESCRIPTOR_RANGE(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0), D3D12_SHADER_VISIBILITY_PIXEL); // t0...
    rootParameters[RootSignatureParams::MaterialsConstantBufferView].InitAsConstantBufferView(0); // b0

    rootParameters[RootSignatureParams::FrameConstantBufferView].InitAsConstantBufferView(1); // b1;

    rootParameters[RootSignatureParams::MeshConstantBufferView].InitAsConstantBufferView(2); // b2
    rootParameters[RootSignatureParams::MaterialInlineConstants].InitAsConstants(1, 3); // b3

    D3D12_STATIC_SAMPLER_DESC sampler = {};
    sampler.Filter = D3D12_FILTER_MIN_MAG_MIP_POINT;
    sampler.AddressU = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
    sampler.AddressV = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
    sampler.AddressW = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
    sampler.MipLODBias = 0;
    sampler.MaxAnisotropy = 0;
    sampler.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
    sampler.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
    sampler.MinLOD = 0.0f;
    sampler.MaxLOD = D3D12_FLOAT32_MAX;
    sampler.ShaderRegister = 0;
    sampler.RegisterSpace = 0;
    sampler.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

    CD3DX12_ROOT_SIGNATURE_DESC rootSignatureDesc;
    rootSignatureDesc.Init(_countof(rootParameters), rootParameters, 1, &sampler, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

    MyPtr<ID3DBlob> signature;
    MyPtr<ID3DBlob> error;
    auto result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error);
    if (FAILED(result)) throw;

    auto device = renderSystem.get_device();
    result = device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&signatureImpl));
    if (FAILED(result)) throw;
};