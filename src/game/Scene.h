#pragma once

struct Scene {
    virtual ~Scene() = default;
    virtual void enter() { }
    virtual void draw() { }
    virtual void update() { }
    virtual void exit() { }
};
