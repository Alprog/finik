#include "timebox_tracker.h"

#include "profiler.h"
#include "../app.h"
#include "../timer.h"

using namespace finik::profiler;

TimeboxTracker::TimeboxTracker(const char* label)
    : timebox{ App::get_instance().profiler.GetCpuLane().startTimebox(label) }
{
}

TimeboxTracker::~TimeboxTracker()
{
    App::get_instance().profiler.GetCpuLane().endTimebox(timebox);
}