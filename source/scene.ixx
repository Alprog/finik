export module scene;

import effect;
import pipeline_state;
import render_system_fwd;
import scene_system_fwd;

import core;
import actor;
import grid;
import texture;
import light;

export class Scene
{
public:
    Scene();

    void update(float deltaTime);
    void render(RenderContext& context, Camera* camera);

    Grid* grid;
    Array<Actor*> actors;

    Effect renderState;
    Effect renderState2;

    Ray hoverRay;
    Vector3 castedPos;

    Light light;
};