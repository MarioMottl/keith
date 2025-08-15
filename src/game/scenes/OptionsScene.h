#pragma once
#include "game/Scene.h"
#include <memory>

class OptionsScene final : public Scene {
public:
    explicit OptionsScene(std::unique_ptr<Scene> previous, bool overlay);

    void draw() override;
    std::unique_ptr<Scene> update() override;

    [[nodiscard]] bool wants_pop() const override;
    [[nodiscard]] bool is_overlay() const override {
        return m_overlay;
    }

private:
    std::unique_ptr<Scene> m_previous; // owned only for non-overlay mode
    bool m_overlay{ false };
    bool m_close{ false };
};
