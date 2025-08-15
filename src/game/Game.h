#pragma once
#include "Scene.h"
#include <memory>
#include <vector>

class Game {
public:
    ~Game();
    void Init();
    void Update();
    void Draw();
    void Shutdown();
    void RequestQuit();
    [[nodiscard]] bool IsRunning() const;
    void change_scene(std::unique_ptr<Scene> scene);

private:
    void push_scene(std::unique_ptr<Scene> scene);
    void pop_scene();
    bool m_running{ false };
    std::vector<std::unique_ptr<Scene>> m_scenes;
};
