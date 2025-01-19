export module mipmap_generator;

import core;

import dx;
import command_list;
import texture;

export class MipMapGenerator : public Singleton<MipMapGenerator>
{
public:
    MipMapGenerator();

    void Generate(Texture& texture, CommandList& commandList);

    MyPtr<ID3D12PipelineState> pso;
};
