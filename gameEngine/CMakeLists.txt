cmake_minimum_required(VERSION 3.10)
project(gameEngine)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Libraries
include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.7.1
)
FetchContent_MakeAvailable(Catch2)

FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.30.9
)
FetchContent_MakeAvailable(SDL2)

# Main project library
add_library(${PROJECT_NAME} STATIC)
target_sources(${PROJECT_NAME} PRIVATE
        src/c++/engine.cpp
        src/c++/inputs.cpp
        src/c++/options.cpp
        src/c++/texture_manager.cpp
        src/c++/component/collider/rectangle_colider_component.cpp
        src/c++/component/collider/collision_resolver.cpp
        src/c++/component/collider/ellipse_collider_component.cpp
        src/c++/component/render/ellipse_render_component.cpp
        src/c++/component/render/rectangle_render_component.cpp
        src/c++/component/render/sprite_render_component.cpp
        src/c++/component/collider/collider.cpp
        src/c++/util/vector.cpp
        src/c++/util/geometry.cpp
)
target_include_directories(${PROJECT_NAME} PUBLIC
        include
        ${SDL2_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)

# Test executable
add_executable(tests src/test/component/collider/collision_resolver.cpp)
target_link_libraries(tests PRIVATE ${PROJECT_NAME} Catch2::Catch2WithMain SDL2::SDL2 SDL2::SDL2main)
target_include_directories(tests PRIVATE include)
