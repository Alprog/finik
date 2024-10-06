module;
#include "camera.h"
#include "camera_controller.h"
class Scene;
export module scene_view;

import std;
import render_lane;
import view;

export class SceneView : public View
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