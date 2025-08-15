#include "TitleScene.h"
#include "OptionsScene.h"
#include "PlayScene.h"
#include "raygui.h"
#include "raylib.h"

#include <iostream>

void TitleScene::draw() {
    auto const W = static_cast<float>(GetScreenWidth());
    auto const H = static_cast<float>(GetScreenHeight());
    constexpr float button_width = 300.0f, button_height = 50.0f;
    float const X = (W - button_width) * 0.5f;

    if (GuiButton({ X, H * 0.30f, button_width, button_height }, "Singleplayer"))
        m_pending = Action::Single;
    if (GuiButton({ X, H * 0.35f, button_width, button_height }, "Multiplayer"))
        m_pending = Action::Multi;

    constexpr float gap = 10.0f;
    constexpr float half = (button_width - gap) * 0.5f;
    float const Y = H * 0.40f;
    if (GuiButton({ X, Y, half, button_height }, "Options"))
        m_pending = Action::Options;
    if (GuiButton({ X + half + gap, Y, half, button_height }, "Quit"))
        m_pending = Action::Quit;
}

std::unique_ptr<Scene> TitleScene::update() {
    std::unique_ptr<Scene> next;
    switch (m_pending) {
        case Action::Single:
            next = std::make_unique<PlayScene>();
            break;
        case Action::Multi:
            next = std::make_unique<PlayScene>();
            break; // stub
        case Action::Options:
            next = std::make_unique<OptionsScene>(std::make_unique<TitleScene>(), false);
            m_pending = Action::None;
            break;
        case Action::Quit:
            m_quit = true;
            break;
        case Action::None:
            break;
    }
    m_pending = Action::None;
    return next;
}

bool TitleScene::wants_quit() const {
    return m_quit;
}
