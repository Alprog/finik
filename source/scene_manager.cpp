module scene_manager;

import scene;

SceneManager::SceneManager()
{
}

void SceneManager::update(float deltaTime)
{
    for (auto scene : scenes)
    {
        scene->update(deltaTime);
    }
}

Scene& SceneManager::create_scene()
{
    auto scene = new Scene();
    scenes.push_back(scene);
    return *scene;
}