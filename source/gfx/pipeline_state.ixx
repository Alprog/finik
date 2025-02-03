export module pipeline_state;

import dx;
import pipeline_settings;
import render_system_fwd;
import root_signature;

// for intellisense

export class PipelineState
{
public:
    PipelineState(RenderSystem& renderSystem, const PipelineSettings& pipelineSettings);

    PipelineSettings pipelineSettings;
    MyPtr<ID3D12PipelineState> pipelineState;
};
