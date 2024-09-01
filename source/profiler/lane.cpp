#include "lane.h"

#include "../timer.h"

using namespace finik::profiler;

Lane::Lane()
    : level { 0 }
{
    timeboxes.reserve(100'000);
}

Timebox& Lane::startTimebox(const char* label)
{
    return timeboxes.emplace_back(Timebox(label, level++));
}

void Lane::endTimebox(Timebox& timebox)
{
    timebox.endTimestamp = get_elapsed_time();
    level--;
}