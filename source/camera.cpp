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

    Vector3 right = Vector3::cross(Vector3(0, 1, 0), forward);
    right.normalize();

    //Vector4 up = Vector4::cross(forward, right);
    //Matrix orientationMtrx;
    //orientationMtrx.rows = { right, up, forward, Vector.ZeroPoint() };
    //orientationMtrx.transpose();

    //viewMatrix = offsetMtrx * orientationMtrx;
}

void Camera::render(RenderContext& context, RenderTarget& renderTarget)
{

}

