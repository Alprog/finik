#include "timebox.h"
#include "../timer.h"

using namespace finik::profiler;

Timebox::Timebox(const char* label, uint8_t level)
    : label{ label}
    , startTimestamp { get_elapsed_time() }
    , endTimestamp { 0 }
    , level { level }
{
}

void Timebox::end()
{
    endTimestamp = get_elapsed_time();
}