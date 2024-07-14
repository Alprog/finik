#pragma once

#include "dx.h"
#include "render_command.h"

class RenderSystem;

class RenderContext
{
public:
    RenderContext(RenderSystem& renderSystem, ID3D12GraphicsCommandList& commandList);

    void draw(RenderCommand renderCommand);

    RenderSystem& renderSystem;
    ID3D12GraphicsCommandList& commandList;
};