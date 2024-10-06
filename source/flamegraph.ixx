module;
#include <cstdint>
export module flamegraph;

import std;
import math;
import timebox;

export namespace finik
{
    void drawFlamegraph(profiler::Timebox* timeboxes, int count, uint64_t startTime, uint64_t endTime, Vector2 size);
}