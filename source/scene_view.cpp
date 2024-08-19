#include "scene_view.h"

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

const CameraController& SceneView::getCameraController() const
{
    return cameraContoller;
}

static float DeltaTime = 0;
static IntSize Size{ 0, 0 };

void SceneView::update(float deltaTime)
{
    DeltaTime = deltaTime;

}

void SceneView::draw_content()
{
    D3D12_GPU_DESCRIPTOR_HANDLE handle = renderLane->getSurface().textureHandle.getGPU();

    ImTextureID textureId = (void*)handle.ptr;
    
    auto min = ImGui::GetWindowContentRegionMin();
    auto max = ImGui::GetWindowContentRegionMax();
    auto imSize = ImVec2(max.x - min.x, max.y - min.y);
    
    Size = IntSize(static_cast<int>(imSize.x), static_cast<int>(imSize.y));
    
    ImGui::Image(textureId, imSize);
    if (ImGui::IsItemHovered())
    {
        cameraContoller.HandleInput(DeltaTime);
        cameraContoller.RefreshCameraPosition();
    }

    renderLane->resize(Size);
}