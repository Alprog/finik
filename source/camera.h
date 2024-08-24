#pragma once

#include "math/vector2.h"
#include "math/vector3.h"
#include "math/matrix.h"
#include "math/ray.h"

class Scene;
class RenderContext;
class RenderTarget;

class Camera
{
public:
    Camera();

    Vector3 getForward() const;

    void calcViewMatrix();
    void calcProjectionMatrix();

    void render(RenderContext& context, RenderTarget& renderTarget);

    Ray castRay(Vector2 ndcPoint) const;
   
public:
    Vector3 position;
    Vector3 lookAt;
    float FieldOfView;
    float OrthoSize;
    float FarPlane = 800.0f;
    float NearPlane = 0.1f;
    float AspectRatio = 16.0f / 9.0f;

    Matrix viewMatrix;
    Matrix projectionMatrix;

    Scene* scene;
};