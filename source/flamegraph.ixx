export module flamegraph;

import core;
import timebox;

export namespace finik
{
    void drawFlamegraph(profiler::Timebox* timeboxes, int count, uint64 startTime, uint64 endTime, Vector2 size);
}