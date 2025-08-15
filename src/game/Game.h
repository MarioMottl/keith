#pragma once

#include <memory>

class Scene;

class Game {
public:
    bool Init();
    void Update();
    void Draw();
    void Shutdown();
    private:
    std::unique_ptr<Scene> m_scene;
};