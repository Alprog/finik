#pragma once

#include "vector3.h"

struct Ray
{
    Ray() = default;
    Ray(Vector3 origin, Vector3 direction);

    Vector3 Origin;
    Vector3 Direction;
};