#include "camera.h"

Camera::Camera()
{
}

Vector3 Camera::getForward()
{
    return (lookAt - position).getNormalized();
}

void Camera::calcViewMatrix()
{
    Vector3 offset = position * -1.0f;
    Matrix offsetMatrix = Matrix::Translation(offset);

    Vector3 forward = getForward();
    Vector3 right = Vector3::cross(Vector3::Up, forward);
    Vector3 up = Vector3::cross(forward, right);

    Matrix orientationMtrx;
    orientationMtrx.rows[0] = Vector4(right, 0);
    orientationMtrx.rows[1] = Vector4(up, 0);
    orientationMtrx.rows[2] = Vector4(forward, 0);
    orientationMtrx.rows[3] = Vector4::Zero;
    orientationMtrx.transpose();

    viewMatrix = offsetMatrix * orientationMtrx;
}

void Camera::render(RenderContext& context, RenderTarget& renderTarget)
{

}

