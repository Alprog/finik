module;
#include "gfx/dx.h"
module scene_view;

import imgui;
import render_system;
import descriptor_handle;
import log;
import scene;
import effect_manager;

SceneView::SceneView(const char* name, Scene& scene)
    : View{name}
    , scene{scene}
    , camera{}
    , cameraContoller{camera}
{
    renderLane = std::make_shared<RenderLane>(scene, camera, IntSize{1024, 800});

    auto& lanes = Single::Get<RenderSystem>().lanes;
    lanes.append(renderLane);
}

const CameraController& SceneView::getCameraController() const
{
    return cameraContoller;
}

static float DeltaTime = 0;
static IntSize Size{0, 0};

void SceneView::update(float deltaTime)
{
    DeltaTime = deltaTime;
}

void SceneView::draw_content()
{
    static bool Depth = false;
    ImGui::Checkbox("Depth", &Depth);

    D3D12_GPU_DESCRIPTOR_HANDLE handle = Depth ? renderLane->getSurface().depthTextureHandle.getGPU() : renderLane->getSurface().textureHandle.getGPU();

    ImTextureID textureId = (void*)handle.ptr;

    auto imSize = ImGui::GetContentRegionAvail();

    Size = IntSize(static_cast<int>(imSize.x), static_cast<int>(imSize.y));

    auto imageStartPos = ImGui::GetCursorScreenPos();

    if (Depth)
    {
        auto Callback = [](const ImDrawList* parent_list, const ImDrawCmd* cmd) //
        {
            ID3D12GraphicsCommandList* commandList = Single::Get<RenderSystem>().get_command_list();

            std::shared_ptr effect = EffectManager::GetInstance().get("imgui_custom");
            commandList->SetPipelineState(effect->getPipelineState().Get());
        };
        GImGui->CurrentWindow->DrawList->AddCallback(Callback, nullptr);
    }
    ImGui::Image(textureId, imSize);

    if (Depth)
    {
        GImGui->CurrentWindow->DrawList->AddCallback((ImDrawCallback)(-8), nullptr);
    }


    if (ImGui::IsItemHovered())
    {
        auto mousePos = ImGui::GetMousePos();

        auto dx = (static_cast<float>(mousePos.x) - imageStartPos.x) / imSize.x;
        auto dy = (static_cast<float>(mousePos.y) - imageStartPos.y) / imSize.y;

        auto ndcPos = Vector2(dx, 1 - dy) * 2.0f - Vector2::One;

        log("ndc {} {}\n", ndcPos.x, ndcPos.y);

        cameraContoller.HandleInput(DeltaTime);
        cameraContoller.RefreshCameraPosition();

        auto ray = cameraContoller.Camera.castRay(ndcPos);

        log("ray {} {} {} | {} {} {}\n", ray.Origin.x, ray.Origin.y, ray.Origin.z, ray.Direction.x, ray.Direction.y,
            ray.Direction.z);

        if (ray.Direction.z != 0)
        {
            auto distance = ray.Origin.z / -ray.Direction.z;
            auto position = ray.Origin + ray.Direction * distance;
            log("pos {} {}\n", position.x, position.y);

            scene.castedPos = position;
        }
    }

    renderLane->resize(Size);
}