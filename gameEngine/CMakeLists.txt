cmake_minimum_required(VERSION 3.10)

project(gameEngine)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(${PROJECT_NAME} STATIC include
        include/component/collider/ellipse/ellipse_axes.h)

target_sources(${PROJECT_NAME}
        PRIVATE
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
        src/c++/math/point.cpp)
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

add_executable(tests src/test/component/collider/collision_resolver.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)


# Ensure the include directories for SDL2 are added
target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${SDL2_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
        SDL2::SDL2 SDL2::SDL2main
        Catch2::Catch2WithMain
)