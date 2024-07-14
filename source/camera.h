#pragma once

class Scene;
class RenderContext;
class RenderTarget;

class Camera
{
public:
    Camera(Scene* scene);

    void render(RenderContext& context, RenderTarget& renderTarget);

private:
    Scene* scene;
};