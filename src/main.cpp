#include "imgui.h"
#include "raylib.h"
#include "rlImGui.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "core/Render.h"
#include "game/Game.h"
#include "game/scenes/TitleScene.h"

#include <format>
#include <iostream>


auto main() -> int {
    render::init_window("keith");
    Game game;

    game.change_scene(std::make_unique<TitleScene>());
    game.Init();

    while (game.IsRunning() && !WindowShouldClose()) {
        game.Update();

        BeginDrawing();
        ClearBackground(BLACK);
        game.Draw();

        rlImGuiBegin();
        ImGui::Begin("Example Window");
        ImGui::Text("%s", std::format("FPS: {}", GetFPS()).c_str());
        ImGui::End();
        rlImGuiEnd();

        EndDrawing();
    }

    game.Shutdown();
    render::shutdown_window();
    return 0;
}
