
#pragma once

struct Vector4
{
    static const Vector4 Zero;
    static const Vector4 One;

    Vector4(float x = 0, float y = 0, float z = 0, float w = 0);

    float length();
    float squaredLength();
    Vector4 getNormalized();

    friend Vector4 operator-(const Vector4& vector);
    friend Vector4 operator+(const Vector4& lhs, const Vector4& rhs);
    friend Vector4 operator-(const Vector4& lhs, const Vector4& rhs);
    friend Vector4 operator*(const Vector4& vector, const float& value);

    static Vector4 cross(const Vector4& a, const Vector4& b);
    static Vector4 dot(const Vector4& a, const Vector4& b);

    float x, y, z, w;
};
