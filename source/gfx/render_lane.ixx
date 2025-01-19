export module render_lane;

import core;
import render_surface;
import scene_system_fwd;

export class RenderLane
{
public:
    RenderLane(Scene& scene, Camera& camera, IntSize resolution);
    void resize(IntSize resolution);

    RenderSurface& getSurface();
    void render();

private:
    Scene& scene;
    Camera& camera;
    RenderSurface surface;

    uint64 fenceValue = 0;
};