module camera;

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

    // DX12 NDC
    Matrix orientationMtrx;
    orientationMtrx.rows[0] = Vector4(right, 0);
    orientationMtrx.rows[1] = Vector4(up, 0);
    orientationMtrx.rows[2] = Vector4(forward, 0);
    orientationMtrx.rows[3] = Vector4(0, 0, 0, 1);
    orientationMtrx.transpose();

    viewMatrix = offsetMatrix * orientationMtrx;
}

void Camera::calcProjectionMatrix()
{
    if (FieldOfView)
    {
        // perspective
        auto scaleY = 1.0f / std::tanf(FieldOfView / 2);
        auto scaleX = scaleY / AspectRatio;

        float m22 = FarPlane / (FarPlane - NearPlane);
        float m32 = -FarPlane * NearPlane / (FarPlane - NearPlane);

        projectionMatrix = Matrix{
          scaleX,   0,     0,   0,
            0,    scaleY,  0,   0,
            0,      0,    m22,  1,
            0,      0,    m32,  0
        };
    }
    else
    {
        // orthogonal
        auto height = OrthoSize;
        auto width = height * AspectRatio;
        auto depth = 1500.0f;
        projectionMatrix = Matrix::Scaling({ 2.0f / width, 2.0f / height, 1.0f / depth });
    }
}

void Camera::render(RenderContext& context, RenderTarget& renderTarget)
{

}

Ray Camera::castRay(Vector2 ndcPoint) const
{
    auto inverseMtrx = (viewMatrix * projectionMatrix).getInverse();

    Vector4 origin = Vector4(ndcPoint, 0, 1) * inverseMtrx;
    Vector4 target = Vector4(ndcPoint, 1, 1) * inverseMtrx;

    origin.homoNormalize();
    target.homoNormalize();

    return Ray(origin.xyz(), (target - origin).xyz().getNormalized());
}

