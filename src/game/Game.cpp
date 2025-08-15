#include "Game.h"

Game::~Game() {
    this->Shutdown();
}

void Game::Init() {
    m_running = true;
    if (!m_scenes.empty()) {
        m_scenes.back()->enter();
    }
}

void Game::Update() {
    if (m_scenes.empty()) {
        m_running = false;
        return;
    }

    auto* top = m_scenes.back().get();

    if (top->wants_quit()) {
        m_running = false;
        return;
    }

    if (auto next = top->update()) {
        if (next->is_overlay()) {
            push_scene(std::move(next));
        } else {
            change_scene(std::move(next));
        }
        if (m_scenes.empty()) {
            m_running = false;
            return;
        }
        top = m_scenes.back().get();
    }

    if (top->wants_pop()) {
        pop_scene();
        if (m_scenes.empty()) {
            m_running = false;
            return;
        }
        top = m_scenes.back().get();
    }

    if (top->wants_quit()) {
        m_running = false;
        return;
    }
}

void Game::Draw() {
    for (auto const& s : m_scenes) {
        s->draw();
    }
}

void Game::Shutdown() {
    while (!m_scenes.empty()) {
        m_scenes.back()->exit();
        m_scenes.pop_back();
    }
    m_running = false;
}

void Game::RequestQuit() {
    m_running = false;
}

bool Game::IsRunning() const {
    return m_running;
}

void Game::change_scene(std::unique_ptr<Scene> scene) {
    while (!m_scenes.empty()) {
        m_scenes.back()->exit();
        m_scenes.pop_back();
    }
    if (scene) {
        m_scenes.push_back(std::move(scene));
        m_scenes.back()->enter();
    }
}

void Game::push_scene(std::unique_ptr<Scene> scene) {
    if (scene) {
        m_scenes.push_back(std::move(scene));
        m_scenes.back()->enter();
    }
}

void Game::pop_scene() {
    if (!m_scenes.empty()) {
        m_scenes.back()->exit();
        m_scenes.pop_back();
    }
}
