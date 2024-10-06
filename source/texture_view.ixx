module;
class Scene;
export module texture_view;

import view;

export class TextureView : public View
{
public:
    TextureView(const char* name, Scene& scene);

protected:
    void draw_content() override;

    Scene& scene;
};