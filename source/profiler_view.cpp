#include "profiler_view.h"

#include "app.h"
#include "flamegraph.h"

import imgui;
import Vector2;

void ProfilerView::draw_content()
{
    auto& profiler = App::get_instance().profiler;
    ImGui::Text("frame: %i", profiler.getFrameIndex());
    ImGui::Text("deltaTime: %f", profiler.getDeltaTime());
    ImGui::Text("FPS: %f", profiler.getFPS());
    
    auto& cpuTimeboxes = profiler.GetCpuLane().timeboxes;
    
    int start = 0;
    int end = 0;

    int frameCount = 10;

    for (int i = cpuTimeboxes.size() - 1; i >= 0; i--)
    {
        if (!strcmp(cpuTimeboxes[i].label, "frame"))
        {
            if (end == 0)
            {
                end = i;
            }
            else
            {
                if (!frameCount--)
                {
                    start = i;
                    break;
                }
            }
        }
    }

    if (end == 0)
        return;

    const uint64_t startTime = cpuTimeboxes[start].startTimestamp;
    const uint64_t endTime = cpuTimeboxes[end - 1].endTimestamp;

    finik::drawFlamegraph(&cpuTimeboxes[start], end - start, startTime, endTime, Vector2(900, 30));


    auto& gpuTimeboxes = profiler.GetGpuLane().timeboxes;

    if (gpuTimeboxes.empty())
        return;

    end = gpuTimeboxes.size() - 1;
    
    for (start = end - 1; start > 0; start--)
    {
        if (gpuTimeboxes[start].startTimestamp < startTime)
            break;
    }

    finik::drawFlamegraph(&gpuTimeboxes[start], end - start, startTime, endTime, Vector2(900, 30));
}
