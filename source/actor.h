#pragma once

#include "math/matrix.h"

class Mesh;

class Actor
{
public:
    Actor();

    void render();

    Matrix transformMatrix;
    Mesh* mesh;
};