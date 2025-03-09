export module render_lane;

import core;
import render_surface;
import scene_system_fwd;
import render_pass;

export class RenderLane
{
public:
    RenderLane(Scene& scene, RenderPass pass, Camera& camera, IntSize resolution);
    void resize(IntSize resolution);

    RenderSurface& getSurface();
    void render();

private:
    Scene& scene;
    Camera& camera;
    RenderSurface surface;
    RenderPass pass;

    uint64 fenceValue = 0;
};