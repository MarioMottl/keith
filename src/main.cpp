#include "imgui.h"
#include "raylib.h"
#include "rlImGui.h"
#include <iostream>

int main() {
    constexpr auto screenWidth = 800;
    constexpr auto screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "raylib + ImGui example");
    SetTargetFPS(60);

    rlImGuiSetup(true);

    while (!WindowShouldClose()) {
        rlImGuiBegin();

        ImGui::Begin("Example Window");
        ImGui::Text("Hello from Dear ImGui!");
        ImGui::End();

        ImGui::ShowDemoWindow();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawLineEx(Vector2{ 0, 0 }, Vector2{ screenWidth, screenHeight }, 2.0f, RED);
        DrawLineEx(Vector2{ 0, screenHeight }, Vector2{ screenWidth, 0 }, 2.0f, RED);
        DrawText("example base code template", 260, 400, 20, LIGHTGRAY);
        rlImGuiEnd();
        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();
    return 0;
}
