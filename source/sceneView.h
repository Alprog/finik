#pragma once

#include "view.h"
#include "camera.h"
#include <vector>
#include "render_lane.h"
#include "camera_controller.h"

class Scene;

class SceneView : public View
{
public:
    SceneView(const char* name, Scene& scene);

    void update(float deltaTime) override;

protected:
    void draw_content() override;

    Scene& scene;
    Camera camera;
    CameraController cameraContoller;

    std::shared_ptr<RenderLane> renderLane;
};