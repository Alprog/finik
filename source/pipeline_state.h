
#pragma once

#include "dx.h"

class PipelineState
{
public:
    PipelineState();

    ComPtr<ID3D12PipelineState> pipelineState;
    ComPtr<ID3D12RootSignature> rootSignature;
};

