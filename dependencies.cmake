include(${PROJECT_SOURCE_DIR}/cmake/CPM.cmake)

CPMAddPackage(
        NAME raylib
        GITHUB_REPOSITORY raysan5/raylib
        GIT_TAG 5.5
)
if (raylib_ADDED)
    message(STATUS "raylib ${raylib_VERSION} added via CPM")
endif ()

CPMAddPackage(
        NAME raygui
        GITHUB_REPOSITORY raysan5/raygui
        GIT_TAG 4.0
        DOWNLOAD_ONLY YES
)
if (raygui_ADDED)
    add_library(raygui INTERFACE)
    target_include_directories(raygui SYSTEM INTERFACE ${raygui_SOURCE_DIR}/src)
    target_link_libraries(raygui INTERFACE raylib)
    message(STATUS "raygui ${raygui_VERSION} added via CPM")
endif ()

CPMAddPackage(
        NAME imgui
        GITHUB_REPOSITORY ocornut/imgui
        GIT_TAG v1.92.2
        DOWNLOAD_ONLY YES
)
if (imgui_ADDED)
    add_library(imgui STATIC
            ${imgui_SOURCE_DIR}/imgui.cpp
            ${imgui_SOURCE_DIR}/imgui_demo.cpp
            ${imgui_SOURCE_DIR}/imgui_draw.cpp
            ${imgui_SOURCE_DIR}/imgui_tables.cpp
            ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    )
    target_include_directories(imgui SYSTEM PUBLIC ${imgui_SOURCE_DIR})
endif ()

CPMAddPackage(
        NAME rlimgui
        GITHUB_REPOSITORY raylib-extras/rlImGui
        GIT_TAG main
        DOWNLOAD_ONLY YES
)
if (rlimgui_ADDED)
    add_library(rlImGui STATIC ${rlimgui_SOURCE_DIR}/rlImGui.cpp)
    target_include_directories(rlImGui SYSTEM PUBLIC
            ${rlimgui_SOURCE_DIR}
            ${imgui_SOURCE_DIR}
    )
    target_link_libraries(rlImGui PUBLIC raylib imgui)
endif ()