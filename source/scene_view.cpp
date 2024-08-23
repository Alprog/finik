#include "scene_view.h"

#include "imgui.h"
#include "app.h"
#include "render_system.h"
#include "render_lane.h"
#include "scene.h"

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

#include "log.h"

void SceneView::draw_content()
{
    D3D12_GPU_DESCRIPTOR_HANDLE handle = renderLane->getSurface().textureHandle.getGPU();

    ImTextureID textureId = (void*)handle.ptr;
    
    auto min = ImGui::GetWindowContentRegionMin();
    auto max = ImGui::GetWindowContentRegionMax();
    auto imSize = ImVec2(max.x - min.x, max.y - min.y);
    
    Size = IntSize(static_cast<int>(imSize.x), static_cast<int>(imSize.y));
    
    auto imageStartPos = ImGui::GetCursorScreenPos();
    ImGui::Image(textureId, imSize);
    if (ImGui::IsItemHovered())
    {
        auto mousePos = ImGui::GetMousePos();
        
        auto dx = (static_cast<float>(mousePos.x) - imageStartPos.x) / imSize.x;
        auto dy = (static_cast<float>(mousePos.y) - imageStartPos.y) / imSize.y;

        auto ndcPos = Vector2(dx, 1 - dy) * 2.0f - Vector2::One;
        
        log("ndc {} {}\n", ndcPos.x, ndcPos.y);
        
        auto ray = cameraContoller.camera.castRay(ndcPos);

        log("ray {} {} {} | {} {} {}\n",
            ray.Origin.x, ray.Origin.y, ray.Origin.z,
            ray.Direction.x, ray.Direction.y, ray.Direction.z);

        if (ray.Direction.z != 0)
        {
            auto distance = ray.Origin.z / -ray.Direction.z;
            auto position = ray.Origin + ray.Direction * distance;
            log("pos {} {}\n", position.x, position.y);
        
            scene.castedPos = position;
        }

        cameraContoller.HandleInput(DeltaTime);
        cameraContoller.RefreshCameraPosition();
    }

    renderLane->resize(Size);
}