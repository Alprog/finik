export module scene_view;

import std;
import render_lane;
import view;
import camera;
import camera_controller;
import scene;

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