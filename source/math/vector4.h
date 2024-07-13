
#pragma once

struct [[Meta]] Vector4
{
    static const Vector4 Zero;
    static const Vector4 One;

    Vector4(float x = 0, float y = 0, float z = 0, float w = 0);

    float length();
    float squaredLength();

    friend Vector4 operator-(const Vector4& vector);
    friend Vector4 operator+(const Vector4& lhs, const Vector4& rhs);
    friend Vector4 operator-(const Vector4& lhs, const Vector4& rhs);

    friend Vector4 operator*(const Vector4& vector, const float& value);

    float x, y, z, w;
};
