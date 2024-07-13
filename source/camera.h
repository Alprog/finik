#pragma once

class Scene;
class RenderTarget;

class Camera
{
public:
    Camera(Scene* scene);

    void render(RenderTarget* render_target);

private:
    Scene* scene;
};