#pragma once

#include "profiler/timebox.h"

import Vector2;

namespace finik
{
    void drawFlamegraph(profiler::Timebox* timeboxes, int count, uint64_t startTime, uint64_t endTime, Vector2 size);
}