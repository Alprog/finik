
#pragma once

struct Vector3
{
    static const Vector3 Zero;
    static const Vector3 One;
    static const Vector3 Right;
    static const Vector3 Left;
    static const Vector3 Up;
    static const Vector3 Down;
    static const Vector3 Forward;
    static const Vector3 Backward;

    Vector3() = default;
    Vector3(float x, float y, float z);

    float length() const;
    float squaredLength() const;
    void normalize();
    Vector3 getNormalized();

    Vector3& operator+=(const Vector3& vector);
    Vector3& operator-=(const Vector3& vector);

    friend Vector3 operator-(const Vector3& vector);
    friend Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
    friend Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
    friend Vector3 operator*(const Vector3& vector, const float& value);
    friend Vector3 operator/(const Vector3& vector, const float& value);

    static Vector3 cross(const Vector3& a, const Vector3& b);
    static float dot(const Vector3& a, const Vector3 & b);

    float x, y, z;
};
