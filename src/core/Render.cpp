#include "Render.h"

#include "game/Game.h"
#include "raylib.h"
#include "rlImGui.h"

void render::init_window(std::string_view const title) {
    InitWindow(context.width, context.width, title.data());
    SetTargetFPS(context.target_fps);
    rlImGuiSetup(true);
}

void render::shutdown_window() {
    rlImGuiShutdown();
    CloseWindow();
}
