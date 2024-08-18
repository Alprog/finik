#pragma once

#include <string>

struct VectorXZ
{
    static const VectorXZ Zero;
    static const VectorXZ One;

    VectorXZ();
    VectorXZ(float x, float z);

    float length();
    float squaredLength();

    friend VectorXZ operator-(const VectorXZ& vector);
    friend VectorXZ operator+(const VectorXZ& lhs, const VectorXZ& rhs);
    friend VectorXZ operator-(const VectorXZ& lhs, const VectorXZ& rhs);

    friend VectorXZ operator*(const VectorXZ& vector, const float& value);

    float x, z;
};
