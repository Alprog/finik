export module render_context;

import core;
import dx;
import render_system_fwd;
import material;
import effect;

export class RenderContext
{
public:
    RenderContext(RenderSystem& renderSystem, ID3D12GraphicsCommandList& commandList);

    void drawMesh(Mesh* mesh);
    void setModelMatrix(const Matrix& matrix);
    void setMaterial(const Material& material);
    void setEffect(Effect& effect);

    RenderSystem& renderSystem;
    ID3D12GraphicsCommandList& commandList;
};