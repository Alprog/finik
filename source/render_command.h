
#pragma once

class Mesh;
class RenderState;

struct RenderCommand
{
    Mesh* mesh = nullptr;
    RenderState* state = nullptr;
};
