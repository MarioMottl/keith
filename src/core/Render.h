#pragma once

#include <string_view>

struct Context {
    int width{ 1280 }, height{ 720 };
    int target_fps{ 60 };
};
constexpr Context context;

namespace render {
    void init_window(std::string_view title);
    void shutdown_window();
}
