#pragma once

#include "math/vector3.h"
#include "math/matrix.h"

class Scene;
class RenderContext;
class RenderTarget;

class Camera
{
public:
    Camera();

    Vector3 getForward();

    void calcViewMatrix();

    void render(RenderContext& context, RenderTarget& renderTarget);

private:
    Vector3 position;
    Vector3 lookAt;
    float FieldOfView;
    float AspectRatio;

    //Matrix viewMatrix;
    //Matrix projectionMatrix;

    Scene* scene;
};