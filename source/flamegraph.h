#pragma once

#include "profiler/timebox.h"

import math;

namespace finik
{
    void drawFlamegraph(profiler::Timebox* timeboxes, int count, uint64_t startTime, uint64_t endTime, Vector2 size);
}