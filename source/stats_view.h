#pragma once

#include "view.h"

class SceneView;

class StatsView : public View
{
public:
    StatsView(const char* name, SceneView& sceneView);

protected:
    void draw_content() override;
    
    SceneView& sceneView;
};