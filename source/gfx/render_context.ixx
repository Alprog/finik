export module render_context;

import core;
import dx;
import render_system_fwd;
import render_command;
import material;

export class RenderContext
{
public:
    RenderContext(RenderSystem& renderSystem, ID3D12GraphicsCommandList& commandList);

    void draw(RenderCommand renderCommand);

    void drawMesh(Mesh* mesh);
    void setModelMatrix(const Matrix& matrix);
    void setMaterial(const Material& material);

    RenderSystem& renderSystem;
    ID3D12GraphicsCommandList& commandList;
};