#pragma once

#include "pipeline_state.h"
#include "render_command.h"
#include "math/ray.h"

class RenderContext;
class Camera;
class Texture;
class Grid;

class Scene
{
public:
    Scene();

    void update(float deltaTime);
    void render(RenderContext& context, Camera* camera);
    
    RenderCommand renderCommand;
    RenderCommand renderCommand2;
    Texture* texture;
    Texture* cellTexture;
    Grid* grid;
    Ray hoverRay;
    Vector3 castedPos;
};