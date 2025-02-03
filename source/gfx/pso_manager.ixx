export module pso_manager;

import core;
import pipeline_settings;
import dx;

// for intellisense

export class PSOManager
{
public:
    MyPtr<ID3D12PipelineState> get_pso(const PipelineSettings& settings);

private:
    MyPtr<ID3D12PipelineState> standardCompile(const PipelineSettings& settings);
    MyPtr<ID3D12PipelineState> imguiCompile(const PipelineSettings& settings);

private:
    HashMap<PipelineSettings, ID3D12PipelineState*> states;
};