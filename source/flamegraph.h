#pragma once

#include <stdint.h>

import math;
import timebox;

namespace finik
{
    void drawFlamegraph(profiler::Timebox* timeboxes, int count, uint64_t startTime, uint64_t endTime, Vector2 size);
}