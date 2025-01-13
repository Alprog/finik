export module compute_context;

import core;
import dx;
import render_system_fwd;
import constant_buffer;

export class ComputeContext
{
public:
    ComputeContext(RenderSystem& renderSystem, ID3D12GraphicsCommandList& commandList);

    void setupRoot();

    void setConstants(D3D12_GPU_VIRTUAL_ADDRESS gpuAddress);

    RenderSystem& renderSystem;
    ID3D12GraphicsCommandList& commandList;
};