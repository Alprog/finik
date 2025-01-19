export module mipmap_generator;

import core;

import dx;
import command_list;
import gpu_resource;

export class MipMapGenerator : public Singleton<MipMapGenerator>
{
public:
    MipMapGenerator();

    void Generate(GpuResource& resource, CommandList& commandList);

    MyPtr<ID3D12PipelineState> pso;
};
