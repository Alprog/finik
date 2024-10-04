export module pipeline_state;

import dx;
import pipeline_settings;
import render_system_fwd;

class PipelineState
{
public:
    PipelineState(RenderSystem& renderSystem, const PipelineSettings& pipelineSettings);

    PipelineSettings pipelineSettings;
    ComPtr<ID3D12PipelineState> pipelineState;
    ComPtr<ID3D12RootSignature> rootSignature;
};

