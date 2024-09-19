module;
#include "math.h"
module math:Vector2;

const Vector2 Vector2::Zero {0, 0};
const Vector2 Vector2::One {1, 1};

Vector2::Vector2()
{

}

Vector2::Vector2(float x, float y)
    : x{x}
    , y{y}
{
}

float Vector2::length()
{
    return sqrt(x * x + y * y);
}

float Vector2::squaredLength()
{
    return x * x + y * y;
}

Vector2 operator-(const Vector2& vector)
{
    return
    {
        -vector.x,
        -vector.y
    };
}

Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
    return
    {
        lhs.x + rhs.x,
        lhs.y + rhs.y
    };
}

Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
    return
    {
        lhs.x - rhs.x,
        lhs.y - rhs.y
    };
}

Vector2 operator*(const Vector2& vector, const float& value)
{
    return
    {
        vector.x * value,
        vector.y * value
    };
}
