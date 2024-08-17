#pragma once

#include <string>

struct Vector2
{
    static const Vector2 Zero;
    static const Vector2 One;

    Vector2();
    Vector2(float x, float y);

    float length();
    float squaredLength();

    friend Vector2 operator-(const Vector2& vector);
    friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
    friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs);

    friend Vector2 operator*(const Vector2& vector, const float& value);

    float x, y;
};
