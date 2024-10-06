#pragma once

import render_command;
import pipeline_state;

class RenderContext;
class Camera;
class Texture;
class Grid;
class Actor;

import math;
import std;

class Scene
{
public:
    Scene();

    void update(float deltaTime);
    void render(RenderContext& context, Camera* camera);
    
    Grid* grid;
    std::vector<Actor*> actors;

    RenderCommand renderCommand;
    RenderCommand renderCommand2;
    Texture* texture;
    Texture* cellTexture;
   
    Ray hoverRay;
    Vector3 castedPos;
};