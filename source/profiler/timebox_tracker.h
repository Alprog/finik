#pragma once

#include <stdint.h>

namespace finik::profiler
{
    struct Timebox;

    struct TimeboxTracker
    {
        explicit TimeboxTracker(const char* label);
        ~TimeboxTracker();

        Timebox& timebox;
    };
}

#define PROFILE(x) finik::profiler::TimeboxTracker timebox_tracker(x)