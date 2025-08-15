#include "PlayScene.h"
#include "OptionsScene.h"
#include "raylib.h"
#include <memory>

void PlayScene::enter() {
    px = 100;
    py = 100;
    pending = Action::None;
}

std::unique_ptr<Scene> PlayScene::update() {
    if (WindowShouldClose()) {
        pending = Action::Quit;
        return {};
    }
    if (IsKeyPressed(KEY_P)) {
        pending = Action::Options;
    }

    auto const dt = GetFrameTime();
    auto const dx = static_cast<float>(IsKeyDown(KEY_D) - IsKeyDown(KEY_A)) * speed * dt;
    auto const dy = static_cast<float>(IsKeyDown(KEY_S) - IsKeyDown(KEY_W)) * speed * dt;
    px += dx;
    py += dy;

    std::unique_ptr<Scene> next;
    switch (pending) {
        case Action::Options:
            next = std::make_unique<OptionsScene>(std::move(next), true);
            pending = Action::None;
            break;
        case Action::Quit:
            pending = Action::None;
            break;
        case Action::None:
            break;
        default:
            break;
    }
    return next;
}

void PlayScene::draw() {
    DrawText("WASD to move, P for Options", 20, 20, 20, RAYWHITE);
    DrawRectangleV({ px, py }, { 32, 32 }, SKYBLUE);
}
