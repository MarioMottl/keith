#pragma once
#include <memory>

struct Scene {
    virtual ~Scene() = default;
    virtual void enter() { }
    virtual void draw() { }
    virtual std::unique_ptr<Scene> update() {
        return nullptr;
    }
    virtual void exit() { }
    [[nodiscard]] virtual bool wants_quit() const {
        return false;
    }
    [[nodiscard]] virtual bool wants_pop() const {
        return false;
    }
    [[nodiscard]] virtual bool is_overlay() const {
        return false;
    }
};
