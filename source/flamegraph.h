#pragma once

#include "math/vector2.h"
#include "profiler/timebox.h"

namespace finik
{
    void drawFlamegraph(profiler::Timebox* timeboxes, int count, uint64_t startTime, uint64_t endTime, Vector2 size);
}