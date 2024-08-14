
#pragma once

class Mesh;
class Texture;
class RenderState;

struct RenderCommand
{
    Mesh* mesh = nullptr;
    RenderState* state = nullptr;
    Texture* texture = nullptr;
};
