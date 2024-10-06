export module render_command;

import mesh;
import texture;
import render_state;

export struct RenderCommand
{
    Mesh* mesh = nullptr;
    RenderState* state = nullptr;
    Texture* texture = nullptr;
    Texture* texture2 = nullptr;
};