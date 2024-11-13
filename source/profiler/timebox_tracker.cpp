module timebox_tracker;

import profiler;
import app;
import timer;

using namespace finik::profiler;

TimeboxTracker::TimeboxTracker(const char* label)
    : timebox{ App::get_instance().profiler.GetCpuLane().startTimebox(label) }
{
}

TimeboxTracker::~TimeboxTracker()
{
    App::get_instance().profiler.GetCpuLane().endTimebox(timebox);
}