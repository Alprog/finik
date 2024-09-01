#pragma once

#include "math/vector2.h"
#include "profiler/timebox.h"

namespace finik
{
    void drawFlamegraph(profiler::Timebox* timeboxes, int count, Vector2 size);
}