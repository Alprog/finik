export module scene;

import render_command;
import pipeline_state;
import render_system_fwd;
import scene_system_fwd;

import core;
import actor;
import grid;
import texture;

export class Scene
{
public:
    Scene();

    void update(float deltaTime);
    void render(RenderContext& context, Camera* camera);
    
    Grid* grid;
    Array<Actor*> actors;

    RenderCommand renderCommand;
    RenderCommand renderCommand2;
   
    Ray hoverRay;
    Vector3 castedPos;
};