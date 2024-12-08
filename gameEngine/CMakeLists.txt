cmake_minimum_required(VERSION 3.10)

project(gameEngine)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(${PROJECT_NAME} STATIC include
        include/component/collider/ellipse/ellipse_axes.h)

target_sources(${PROJECT_NAME}
        PRIVATE
        src/engine.cpp
        src/inputs.cpp
        src/options.cpp
        src/texture_manager.cpp
        src/component/collider/rectangle_colider_component.cpp
        src/component/collider/collision_resolver.cpp
        src/component/collider/ellipse_collider_component.cpp
        src/component/render/ellipse_render_component.cpp
        src/component/render/rectangle_render_component.cpp
        src/component/render/sprite_render_component.cpp
        src/component/collider/collider.cpp
        src/math/point.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC include)


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
find_package(SDL2 REQUIRED)

# Ensure the include directories for SDL2 are added
target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${SDL2_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        SDL2::SDL2 SDL2::SDL2main
        Catch2::Catch2WithMain
)
