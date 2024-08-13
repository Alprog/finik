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
    void calcProjectionMatrix();

    void render(RenderContext& context, RenderTarget& renderTarget);

public:
    Vector3 position;
    Vector3 lookAt;
    float FieldOfView;
    float FarPlane = 400.0f;
    float NearPlane = 0.1f;
    float AspectRatio = 1;

    Matrix viewMatrix;
    Matrix projectionMatrix;

    Scene* scene;
};