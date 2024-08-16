#pragma once

#include "vector3.h"

struct Vector4
{
    static const Vector4 Zero;
    static const Vector4 One;

    Vector4() = default;
    Vector4(Vector3 vector, float w);
    Vector4(float x, float y, float z, float w);

    float length();
    float squaredLength();
    Vector4 getNormalized();

    Vector3 xyz();

    friend Vector4 operator-(const Vector4& vector);
    friend Vector4 operator+(const Vector4& lhs, const Vector4& rhs);
    friend Vector4 operator-(const Vector4& lhs, const Vector4& rhs);
    friend Vector4 operator*(const Vector4& vector, const float& value);

    static Vector4 cross(const Vector4& a, const Vector4& b);
    static float dot(const Vector4& a, const Vector4& b);

    float x, y, z, w;
};
