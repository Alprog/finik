#pragma once

import Vector3;

struct Ray
{
    Ray() = default;
    Ray(Vector3 origin, Vector3 direction);

    Vector3 Origin;
    Vector3 Direction;
};