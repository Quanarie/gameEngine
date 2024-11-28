cmake_minimum_required(VERSION 3.10)

project(gameEngine)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Some shit to make it see sdl
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_PREFIX_PATH "/opt/homebrew")
find_package(SDL2 REQUIRED)

add_library(${PROJECT_NAME} STATIC include)

target_sources(${PROJECT_NAME} 
    PRIVATE 
	src/engine.cpp
	src/math/utils.cpp
	src/inputs.cpp
	src/options.cpp
	src/texture_manager.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2::SDL2main)


