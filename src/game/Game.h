#pragma once

#include <memory>

#include "Scene.h"

class Game {
public:
    Game() = default;
    ~Game();

    Game(const Game &) = delete; // copy Constructor
    Game& operator=(const Game &) = delete; // copy assignment

    bool Init();
    void Update();
    void Draw();
    void Shutdown();
    private:
    std::unique_ptr<Scene> m_scene;
};