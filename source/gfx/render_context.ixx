export module render_context;

import core;
import dx;
import render_system_fwd;
import material;
import constant_buffer;

export class RenderContext
{
public:
    RenderContext(RenderSystem& renderSystem, ID3D12GraphicsCommandList& commandList);

    void setFrameConstants(D3D12_GPU_VIRTUAL_ADDRESS gpuAddress);
    void setModelMatrix(const Matrix& matrix);
    void setMaterial(const Material& material);
    void drawMesh(Mesh* mesh);

    RenderSystem& renderSystem;
    ID3D12GraphicsCommandList& commandList;
};