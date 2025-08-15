#include "OptionsScene.h"
#include "raygui.h"
#include "raylib.h"

OptionsScene::OptionsScene(std::unique_ptr<Scene> previous, bool overlay)
    : m_previous(std::move(previous)),
      m_overlay(overlay) { }

void OptionsScene::draw() {
    DrawText("OPTION SCENE", 40, 40, 30, GREEN);
    if (GuiButton({ 100, 100, 200, 50 }, "Back")) {
        m_close = true;
    }
    // TODO: other options UI
}

std::unique_ptr<Scene> OptionsScene::update() {
    if (!m_close)
        return nullptr;

    if (m_overlay) {
        return nullptr;
    }

    return std::move(m_previous);
}

bool OptionsScene::wants_pop() const {
    return m_overlay && m_close;
}
