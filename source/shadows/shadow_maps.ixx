export module shadow_maps;

import core;
import render_lane;

export class Scene;

export class ShadowMaps
{
public:
    ShadowMaps(Scene& scene)
        : scene{scene}
    {
    }

private:
    Array<std::shared_ptr<RenderLane>> lanes;

    Scene& scene;
};