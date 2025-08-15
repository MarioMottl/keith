#pragma once
#include "game/Scene.h"
#include "raylib.h"
#include <memory>

class PlayScene final : public Scene {
public:
    float px{ 100 }, py{ 100 };
    float speed{ 220 };
    enum class Action { None, Options, Quit } pending{ Action::None };

    void enter() override;
    std::unique_ptr<Scene> update() override;
    void draw() override;
    [[nodiscard]] bool wants_quit() const override {
        return pending == Action::Quit;
    }
};
