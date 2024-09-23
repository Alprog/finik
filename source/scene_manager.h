#pragma once

import std;

class Scene;

class SceneManager
{
    friend class App;

    SceneManager();

public:
    void update(float deltaTime);
    Scene& create_scene();

public:
    std::vector<Scene*> scenes;
};