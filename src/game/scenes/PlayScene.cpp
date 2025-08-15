#include "PlayScene.h"
#include "OptionsScene.h"
#include "raylib.h"

#include <cmath>
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
    if (auto const length = std::sqrt(dx * dx + dy * dy); length > 0.0f) {
        px += dx / length * speed * dt;
    }
    py += dy;

    px = std::max(0.0f, std::min(px, static_cast<float>(GetScreenWidth() - 32)));
    py = std::max(0.0f, std::min(py, static_cast<float>(GetScreenHeight() - 32)));

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

    for (int x = 0; x < GetScreenWidth(); x += 32) {
        DrawLine(x, 0, x, GetScreenHeight(), { 128, 128, 128, 64 });
    }
    for (int y = 0; y < GetScreenHeight(); y += 32) {
        DrawLine(0, y, GetScreenWidth(), y, { 128, 128, 128, 64 });
    }

    DrawRectangleV({ px, py }, { 32, 32 }, SKYBLUE);
}
