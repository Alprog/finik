#pragma once

import dx;

#include "render_command.h"

class RenderSystem;
class Mesh;
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