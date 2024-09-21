module;
#include <stdint.h>
export module timebox_tracker;

export namespace finik::profiler
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

export using Profile = finik::profiler::TimeboxTracker;