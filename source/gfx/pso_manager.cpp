module;
#include "backends/imgui_impl_dx12.h"
#include "dx.h"
module pso_manager;

import render_system;
import root_signature;

MyPtr<ID3D12PipelineState> PSOManager::get_pso(const PipelineSettings& settings)
{

    auto it = states.find_value(settings);
    if (it)
    {
        return *it;
    }

    MyPtr<ID3D12PipelineState> result;
    if (settings.type == PipelineType::Standard)
    {
        result = standardCompile(settings);
    }
    else
    {
        result = imguiCompile(settings);
    }
    states[settings] = result;
    return result;
}

MyPtr<ID3D12PipelineState> PSOManager::standardCompile(const PipelineSettings& settings)
{
    auto& renderSystem = Single::Get<RenderSystem>();
    auto device = renderSystem.get_device();

    D3D12_INPUT_ELEMENT_DESC inputElementDescs[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 1, DXGI_FORMAT_R32G32_UINT, 0, 32, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0}};

    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
    psoDesc.InputLayout = {inputElementDescs, _countof(inputElementDescs)};
    psoDesc.pRootSignature = renderSystem.getRootSignature().signatureImpl.Get();

    psoDesc.VS = CD3DX12_SHADER_BYTECODE(settings.vertexByteCode.Get());
    psoDesc.PS = CD3DX12_SHADER_BYTECODE(settings.pixelByteCode.Get());
    psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    psoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;

    // natural for left-handed. front face normals to the viewer (a^b = n)
    psoDesc.RasterizerState.FrontCounterClockwise = false;

    psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);

    CD3DX12_DEPTH_STENCIL_DESC depthStencilDesc(D3D12_DEFAULT);
    depthStencilDesc.DepthEnable = true;
    depthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
    depthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
    depthStencilDesc.StencilEnable = FALSE;
    psoDesc.DepthStencilState = depthStencilDesc;

    psoDesc.SampleMask = UINT_MAX;
    psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    psoDesc.NumRenderTargets = 1;
    psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
    psoDesc.SampleDesc.Count = 1;

    MyPtr<ID3D12PipelineState> pipelineState;
    device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pipelineState)) MUST;
    return pipelineState;
}

MyPtr<ID3D12PipelineState> PSOManager::imguiCompile(const PipelineSettings& settings)
{
    auto& renderSystem = Single::Get<RenderSystem>();
    auto device = renderSystem.get_device();

    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc;
    FillImguiPsoDesc(psoDesc);

    psoDesc.VS = CD3DX12_SHADER_BYTECODE(settings.vertexByteCode.Get());
    psoDesc.PS = CD3DX12_SHADER_BYTECODE(settings.pixelByteCode.Get());

    MyPtr<ID3D12PipelineState> pipelineState;
    device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pipelineState)) MUST;
    return pipelineState;
}