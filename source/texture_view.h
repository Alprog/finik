#pragma once

#include "view.h"

class Scene;

class TextureView : public View
{
public:
    TextureView(const char* name, Scene& scene);

protected:
    void draw_content() override;

    Scene& scene;
};