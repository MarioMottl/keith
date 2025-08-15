cmake_minimum_required(VERSION 3.20)
project(keith LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(${PROJECT_SOURCE_DIR}/cmake/CPM.cmake)
include(${PROJECT_SOURCE_DIR}/dependencies.cmake)

if (NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif ()

option(ENABLE_WARNINGS_AS_ERRORS "Treat warnings as errors" ON)
option(ENABLE_SANITIZERS "Enable ASan/UBSan (Debug, GCC/Clang)" OFF)

set(SRCS src/main.cpp)
set(HDRS)

add_executable(keith ${SRCS} ${HDRS})
target_include_directories(keith
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRCS} ${HDRS})

add_library(project_warnings INTERFACE)
target_compile_options(project_warnings INTERFACE
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:
        -Wall -Wextra -Wpedantic
        -Wconversion -Wsign-conversion
        -Wshadow
        -Wold-style-cast
        -Woverloaded-virtual
        -Wnon-virtual-dtor
        -Wdouble-promotion
        -Wformat=2
        -Wnull-dereference
        -Wimplicit-fallthrough
        -Wextra-semi
        >
        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_GREATER_EQUAL:$<CXX_COMPILER_VERSION>,8>>:
        -Wduplicated-cond -Wduplicated-branches -Wuseless-cast
        >
        $<$<CXX_COMPILER_ID:MSVC>:
        /W4 /permissive- /Zc:__cplusplus
        /w14242 /w14254 /w14263 /w14265 /w14287 /we4289
        /w14296 /w14311 /w14545 /w14546 /w14547 /w14549 /w14555
        /w14619 /w14905 /w14906 /w14928
        >
)

target_link_libraries(keith PRIVATE project_warnings raylib raygui imgui rlImGui)

target_compile_options(imgui PRIVATE
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-w>
        $<$<CXX_COMPILER_ID:MSVC>:/w>
)
target_compile_options(rlImGui PRIVATE
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-w>
        $<$<CXX_COMPILER_ID:MSVC>:/w>
)

if (ENABLE_WARNINGS_AS_ERRORS)
    target_compile_options(keith PRIVATE
            $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Werror>
            $<$<CXX_COMPILER_ID:MSVC>:/WX>
    )
endif ()

if (ENABLE_SANITIZERS)
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        target_compile_options(keith PRIVATE
                $<$<CONFIG:Debug>:-fsanitize=address,undefined -fno-omit-frame-pointer>)
        target_link_options(keith PRIVATE
                $<$<CONFIG:Debug>:-fsanitize=address,undefined>)
    endif ()
endif ()

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif ()
