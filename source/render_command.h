
#pragma once

class Mesh;
class RenderState;

struct RenderCommand
{
    Mesh* mesh;
    RenderState* state;
};
