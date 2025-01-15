export module mipmap_generator;

import core;

import dx;
import command_list;

export class MipMapGenerator : public Singleton<MipMapGenerator>
{
public:
    MipMapGenerator();

    void Generate(ID3D12Resource* resource, CommandList& commandList);

    MyPtr<ID3D12PipelineState> pso;
};
