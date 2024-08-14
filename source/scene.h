#pragma once

#include "pipeline_state.h"
#include "render_command.h"

class RenderContext;
class Camera;
class Texture;

class Scene
{
public:
    Scene();

    void update(float deltaTime);
    void render(RenderContext& context, Camera* camera);
    
    RenderCommand renderCommand;
    Texture* texture;
};