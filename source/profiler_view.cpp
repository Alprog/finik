#include "profiler_view.h"

#include "app.h"
#include "imgui.h"

void ProfilerView::draw_content()
{
    auto& profiler = App::get_instance().profiler;
    ImGui::Text("frame: %i", profiler.getFrameIndex());
    ImGui::Text("deltaTime: %f", profiler.getDeltaTime());
    ImGui::Text("FPS: %f", profiler.getFPS());
}
