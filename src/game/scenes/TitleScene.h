#pragma once
#include "game/Scene.h"
#include <memory>

class TitleScene final : public Scene {
public:
    enum class Action { None, Single, Multi, Options, Quit };
    void draw() override;
    std::unique_ptr<Scene> update() override;
    [[nodiscard]] bool wants_quit() const override;

private:
    Action m_pending{ Action::None };
    bool m_quit{ false };
};
