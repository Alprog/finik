module;
#include "assert.h"
#include "dx.h"
module mipmap_generator;

import app;
import render_system;
import assets;
import shader;
import shader_manager;

MipMapGenerator::MipMapGenerator()
{
    auto& renderSystem = App::GetInstance().render_system;

    auto shader = ShaderManager::GetInstance().getComputeShader("shaders/mipmaps.hlsl", "CSMain");

    D3D12_COMPUTE_PIPELINE_STATE_DESC desc = {};
    desc.CS = CD3DX12_SHADER_BYTECODE(shader->bytecode.Get());
    desc.pRootSignature = renderSystem.getComputeRootSignature().signatureImpl.Get();

    renderSystem.get_device()->CreateComputePipelineState(&desc, IID_PPV_ARGS(&pso));
}