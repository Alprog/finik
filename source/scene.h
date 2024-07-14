#pragma once

#include "pipeline_state.h"
#include "mesh.h"

class RenderContext;

class Scene
{
public:
    Scene();

    void render(RenderContext& context);

    Mesh* mesh;
};