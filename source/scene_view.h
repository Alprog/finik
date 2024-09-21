#pragma once

#include "view.h"
#include "camera.h"
#include "gfx/render_lane.h"
#include "camera_controller.h"

import std.compat;

class Scene;

class SceneView : public View
{
public:
    SceneView(const char* name, Scene& scene);

    const CameraController& getCameraController() const;

    void update(float deltaTime) override;

protected:
    void draw_content() override;

public:
    Scene& scene;

protected:
    Camera camera;
    CameraController cameraContoller;

    std::shared_ptr<RenderLane> renderLane;
};