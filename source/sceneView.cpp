#include "sceneView.h"

#include "imgui.h"
#include "app.h"
#include "render_system.h"
#include "render_lane.h"

SceneView::SceneView(const char* name, Scene& scene)
    : View {name}
    , scene {scene}
{
    renderLane = std::make_shared<RenderLane>(scene, camera, IntSize{ 1024, 800 });

    auto& lanes = App::get_instance().render_system.lanes;
    lanes.push_back(renderLane);
}

void SceneView::draw_content()
{
    ImGui::Button("yo");

    D3D12_GPU_DESCRIPTOR_HANDLE handle = renderLane->getSurface().textureHandle.getGPU();

    ImTextureID textureId = (void*)handle.ptr;
    

    ImGui::Image(textureId, ImVec2(300, 300));
}