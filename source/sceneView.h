#pragma once

#include "view.h"
#include "camera.h"
#include <vector>
#include "render_lane.h"

class Scene;

class SceneView : public View
{
public:
    SceneView(const char* name, Scene& scene);

protected:
    void draw_content() override;

    Scene& scene;
    Camera camera;

    std::shared_ptr<RenderLane> renderLane;
};