#include "imgui.h"
#include "raylib.h"
#include "rlImGui.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <iostream>
#include <format>

struct Context {
    int width{1280}, height{720};
    int target_fps{60};
};

auto main() -> int {
    constexpr Context context;
    InitWindow(context.width, context.width, "raylib Keith");
    SetTargetFPS(context.target_fps);
    rlImGuiSetup(true);

    while (!WindowShouldClose()) {
        rlImGuiBegin();

        ImGui::Begin("Example Window");
        ImGui::Text("%s", std::format("FPS: {}", GetFPS()).c_str());
        ImGui::End();


        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawLineEx(Vector2{ 0, 0 }, Vector2{ context.width, context.height}, 2.0f, RED);
        DrawLineEx(Vector2{ 0, context.height}, Vector2{ context.width, 0 }, 2.0f, RED);
        DrawText("example base code template", 260, 400, 20, LIGHTGRAY);
        rlImGuiEnd();
        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();
    return 0;
}
