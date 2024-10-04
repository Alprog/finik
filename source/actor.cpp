#include "actor.h"

import mesh;

Actor::Actor()
{
    mesh = createCubeMesh();
    transformMatrix = Matrix::Identity;
}