#include "stats_view.h"

#include "imgui.h"
#include "scene_view.h"

StatsView::StatsView(const char* name, SceneView& sceneView)
    : View{ name }
    , sceneView{ sceneView }
{
}

void StatsView::draw_content()
{
    auto& controller = sceneView.getCameraController();

    
    constexpr float radToDegree = 180 / std::numbers::pi;
    
    ImGui::Text("rotation: %f", controller.Rotation * radToDegree);
    ImGui::Text("angle: %f", controller.GetAngle() * radToDegree);
    ImGui::Text("fov: %f", controller.GetFieldOfView() * radToDegree);
    ImGui::Text("vert.area: %f", controller.GetVisibleAreaLength());
}