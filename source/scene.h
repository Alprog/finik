#pragma once

#include "pipeline_state.h"
#include "render_command.h"

class RenderContext;

class Scene
{
public:
    Scene();

    void render(RenderContext& context);

    RenderCommand renderCommand;
};