#include "camera.h"

#include <cmath>

Camera::Camera()
{
    viewMatrix = Matrix::Identity;
    projectionMatrix = Matrix::Identity;
}

Vector3 Camera::getForward() const
{
    return (lookAt - position).getNormalized();
}

void Camera::calcViewMatrix()
{
    Vector3 offset = position * -1.0f;
    Matrix offsetMatrix = Matrix::Translation(offset);

    Vector3 forward = getForward();
    Vector3 backward = -forward; // Y
    Vector3 right = Vector3::cross(backward, Vector3::Up).getNormalized(); // Y ^ Z = X
    Vector3 up = Vector3::cross(right, backward).getNormalized();          // X ^ Y = Z

    Matrix orientationMtrx; // DX12 NDC
    orientationMtrx.rows[0] = Vector4(right, 0);
    orientationMtrx.rows[1] = Vector4(up, 0);
    orientationMtrx.rows[2] = Vector4(forward, 0);
    orientationMtrx.rows[3] = Vector4(0, 0, 0, 1);
    orientationMtrx.transpose();

    viewMatrix = offsetMatrix * orientationMtrx;
}

void Camera::calcProjectionMatrix()
{
    auto scaleY = 1.0f / std::tanf(FieldOfView / 2);
    auto scaleX = scaleY / AspectRatio;

    float m22 = FarPlane / (FarPlane - NearPlane);
    float m32 = -FarPlane * NearPlane / (FarPlane - NearPlane);

    projectionMatrix = Matrix{
      scaleX,   0,     0,  0,
        0,    scaleY,  0,  0,
        0,      0,    m22,  1,
        0,      0,    m32,  0
    };
}

void Camera::render(RenderContext& context, RenderTarget& renderTarget)
{

}

Ray Camera::castRay(Vector2 ndcPoint) const
{
    auto position = this->position;

    auto rh = ndcPoint.x * FieldOfView / 2 * AspectRatio;
    auto rv = ndcPoint.y * FieldOfView / 2;

    auto rotation = Vector2(rh, rv);
    auto rotationAxis = Vector3(rotation.y, -rotation.x, 0); // rotates 90° CW

    auto direction = Vector4(getForward(), 0);
    direction = direction * Matrix::Rotation(Quaternion::FromAxis(rotationAxis, rotation.length()));

    return Ray(position, direction.xyz());
}

