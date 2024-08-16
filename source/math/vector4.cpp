
#include "Vector4.h"
#include "math.h"

const Vector4 Vector4::Zero {0, 0, 0, 0};
const Vector4 Vector4::One {1, 1, 1, 1};

Vector4::Vector4(Vector3 vector, float w)
    : x{ vector.x }
    , y{ vector.y }
    , z{ vector.z }
    , w{ w }
{
}

Vector4::Vector4(float x, float y, float z, float w)
    : x{x}
    , y{y}
    , z{z}
    , w{w}
{
}

float Vector4::length()
{
    return sqrt(x * x + y * y + z * z);
}

float Vector4::squaredLength()
{
    return x * x + y * y + z * z;
}

Vector4 Vector4::getNormalized()
{
    auto length = this->length();
    return { x / length, y / length, z / length, w };
}

Vector3 Vector4::xyz()
{
    return Vector3(x, y, z);
}

Vector4 operator-(const Vector4& vector)
{
    return
    {
        -vector.x,
        -vector.y,
        -vector.z,
        -vector.w
    };
}

Vector4 operator+(const Vector4& lhs, const Vector4& rhs)
{
    return
    {
        lhs.x + rhs.x,
        lhs.y + rhs.y,
        lhs.z + rhs.z,
        lhs.w + rhs.w
    };
}

Vector4 operator-(const Vector4& lhs, const Vector4& rhs)
{
    return
    {
        lhs.x - rhs.x,
        lhs.y - rhs.y,
        lhs.z - rhs.z,
        lhs.w - rhs.w
    };
}

Vector4 operator*(const Vector4& vector, const float& value)
{
    return
    {
        vector.x * value,
        vector.y * value,
        vector.z * value,
        vector.w * value
    };
}

Vector4 Vector4::cross(const Vector4& a, const Vector4& b)
{
    auto z = a.x * b.y - a.y * b.x; // XY
    auto x = a.y * b.z - a.z * b.y; // YZ
    auto y = a.z * b.x - a.x * b.z; // ZX
    return Vector4(x, y, z, 0);
}

float Vector4::dot(const Vector4& lhs, const Vector4& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}