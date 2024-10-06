export module actor;

import math;
import mesh;

export class Actor
{
public:
    Actor();

    void render();

    Matrix transformMatrix;
    Mesh* mesh;
};