
#include "Vector3.h"
#include "math.h"

const Vector3 Vector3::Zero {0, 0, 0};
const Vector3 Vector3::One {1, 1, 1};

Vector3::Vector3(float x, float y, float z)
    : x{x}
    , y{y}
    , z{z}
{
}

float Vector3::length()
{
    return sqrt(x * x + y * y + z * z);
}

float Vector3::squaredLength()
{
    return x * x + y * y + z * z;
}

Vector3 operator-(const Vector3& vector)
{
    return
    {
        -vector.x,
        -vector.y,
        -vector.z
    };
}

Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
    return
    {
        lhs.x + rhs.x,
        lhs.y + rhs.y,
        lhs.z + rhs.z
    };
}

Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
    return
    {
        lhs.x - rhs.x,
        lhs.y - rhs.y,
        lhs.z - rhs.z
    };
}

Vector3 operator*(const Vector3& vector, const float& value)
{
    return
    {
        vector.x * value,
        vector.y * value,
        vector.z * value
    };
}


