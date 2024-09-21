module;
#include "../timer.h"
module lane;

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
    timebox.end();
    level--;
}