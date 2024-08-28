#include "actor.h"

#include "mesh.h"

Actor::Actor()
{
    mesh = createCubeMesh();
    transformMatrix = Matrix::Identity;
}