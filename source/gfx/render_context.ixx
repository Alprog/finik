module;
#include "dx.h"
export module render_context;

import dx;
import render_system_fwd;
import render_command;
import math;

export class RenderContext
{
public:
    RenderContext(RenderSystem& renderSystem, ID3D12GraphicsCommandList& commandList);

    void draw(RenderCommand renderCommand);

    void drawMesh(Mesh* mesh);
    void setModelMatrix(const Matrix& matrix);

    RenderSystem& renderSystem;
    ID3D12GraphicsCommandList& commandList;
};