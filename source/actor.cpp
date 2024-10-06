module actor;

import mesh;

Actor::Actor()
{
    mesh = createCubeMesh();
    transformMatrix = Matrix::Identity;
}