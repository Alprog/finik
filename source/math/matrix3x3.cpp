#include "matrix3x3.h"

float Matrix3x3::determinant() const
{
    return a*e*i + b*f*g + c*d*h - c*e*g - b*d*i - a*f*h;
}