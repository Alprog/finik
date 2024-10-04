#pragma once

#include "dx.h"

import dx;
import render_system_fwd;

#include "render_command.h"

struct Matrix;

class RenderContext
{
public:
    RenderContext(RenderSystem& renderSystem, ID3D12GraphicsCommandList& commandList);

    void draw(RenderCommand renderCommand);

    void drawMesh(Mesh* mesh);
    void setModelMatrix(const Matrix& matrix);

    RenderSystem& renderSystem;
    ID3D12GraphicsCommandList& commandList;
};