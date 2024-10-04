
#pragma once

import mesh;
import texture;
import render_state;

struct RenderCommand
{
    Mesh* mesh = nullptr;
    RenderState* state = nullptr;
    Texture* texture = nullptr;
    Texture* texture2 = nullptr;
};
