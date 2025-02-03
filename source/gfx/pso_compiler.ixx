export module pso_compiler;

import core;
import pipeline_settings;
import dx;

// for intellisense

export class PSOCompiler
{
public:
    MyPtr<ID3D12PipelineState> get_pso(const PipelineSettings& settings);
};