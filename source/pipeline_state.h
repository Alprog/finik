
#pragma once

#include "dx.h"
#include "pipeline_settings.h"

class RenderSystem;

class PipelineState
{
public:
    PipelineState(RenderSystem& renderSystem, const PipelineSettings& pipelineSettings);

    PipelineSettings pipelineSettings;
    ComPtr<ID3D12PipelineState> pipelineState;
    ComPtr<ID3D12RootSignature> rootSignature;
};

