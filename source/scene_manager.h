#pragma once

#include <vector>

class Scene;

class SceneManager
{
    friend class App;

    SceneManager();

public:
    void update(float deltaTime);
    Scene& create_scene();

private:
    std::vector<Scene*> scenes;
};