#pragma once

#include "pipeline_state.h"
#include "render_command.h"

class RenderContext;

class Scene
{
public:
    Scene();

    void update(float deltaTime);
    void render(RenderContext& context);
    

    RenderCommand renderCommand;
};