#include "sceneView.h"

#include "imgui.h"
#include "app.h"
#include "render_system.h"
#include "render_lane.h"

SceneView::SceneView(const char* name, Scene& scene)
    : View {name}
    , scene {scene}
    , camera {}
    , cameraContoller {camera}
{
    renderLane = std::make_shared<RenderLane>(scene, camera, IntSize{ 1024, 800 });

    auto& lanes = App::get_instance().render_system.lanes;
    lanes.push_back(renderLane);
}

void SceneView::draw_content()
{
    D3D12_GPU_DESCRIPTOR_HANDLE handle = renderLane->getSurface().textureHandle.getGPU();

    ImTextureID textureId = (void*)handle.ptr;
    
    auto min = ImGui::GetWindowContentRegionMin();
    auto max = ImGui::GetWindowContentRegionMax();
    auto size = ImVec2(max.x - min.x, max.y - min.y);

    ImGui::Image(textureId, size);
}