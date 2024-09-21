module timebox;

#include "../timer.h"

using namespace finik::profiler;

Timebox::Timebox(const char* label, uint8_t level)
    : label{ label}
    , startTimestamp { getMicroseconds() }
    , endTimestamp { 0 }
    , level { level }
{
}

void Timebox::end()
{
    endTimestamp = getMicroseconds();
}