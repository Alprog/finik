#pragma once

import math;

class Mesh;

class Actor
{
public:
    Actor();

    void render();

    Matrix transformMatrix;
    Mesh* mesh;
};