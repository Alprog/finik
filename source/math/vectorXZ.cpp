#include "vectorXZ.h"
#include "math.h"

const VectorXZ VectorXZ::Zero {0, 0};
const VectorXZ VectorXZ::One {1, 1};

VectorXZ::VectorXZ()
{

}

VectorXZ::VectorXZ(float x, float z)
    : x{x}
    , z{z}
{
}

float VectorXZ::length()
{
    return sqrt(x * x + z * z);
}

float VectorXZ::squaredLength()
{
    return x * x + z * z;
}

VectorXZ operator-(const VectorXZ& vector)
{
    return
    {
        -vector.x,
        -vector.z
    };
}

VectorXZ operator+(const VectorXZ& lhs, const VectorXZ& rhs)
{
    return
    {
        lhs.x + rhs.x,
        lhs.z + rhs.z
    };
}

VectorXZ operator-(const VectorXZ& lhs, const VectorXZ& rhs)
{
    return
    {
        lhs.x - rhs.x,
        lhs.z - rhs.z
    };
}

VectorXZ operator*(const VectorXZ& vector, const float& value)
{
    return
    {
        vector.x * value,
        vector.z * value
    };
}
