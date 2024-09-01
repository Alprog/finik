#include "profiler_view.h"

#include "app.h"
#include "imgui.h"
#include "flamegraph.h"
#include "math/vector2.h"

void ProfilerView::draw_content()
{
    auto& profiler = App::get_instance().profiler;
    ImGui::Text("frame: %i", profiler.getFrameIndex());
    ImGui::Text("deltaTime: %f", profiler.getDeltaTime());
    ImGui::Text("FPS: %f", profiler.getFPS());
    
    auto& timeboxes = profiler.GetCpuLane().timeboxes;
    
    int start = 0;
    int end = 0;

    for (int i = timeboxes.size() - 1; i >= 0; i--)
    {
        if (!strcmp(timeboxes[i].label, "frame"))
        {
            if (end == 0)
            {
                end = i;
            }
            else
            {
                start = i;
                break;
            }
        }
    }

    finik::drawFlamegraph(&timeboxes[start], end - start, Vector2(500, 30));
}
