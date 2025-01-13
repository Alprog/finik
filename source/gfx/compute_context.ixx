export module compute_context;

import core;
import dx;
import render_system_fwd;
import constant_buffer;

export class ComputeContext
{
public:
    ComputeContext(RenderSystem& renderSystem, ID3D12GraphicsCommandList& commandList);

    RenderSystem& renderSystem;
    ID3D12GraphicsCommandList& commandList;
};