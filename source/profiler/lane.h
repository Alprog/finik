#pragma once

#include <vector>
#include "timebox.h"

namespace finik::profiler
{
    class Lane
    {
    public:
        Lane();

        std::vector<Timebox> timeboxes;
        int level;

        Timebox& startTimebox(const char* label);
        void endTimebox(Timebox& timebox);
    };
}
