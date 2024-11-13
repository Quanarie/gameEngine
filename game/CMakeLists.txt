cmake_minimum_required(VERSION 3.10)

project(game)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} src/main.cpp)

set(GAME_ENGINE_PROJECT_NAME "gameEngine")
add_subdirectory(../${GAME_ENGINE_PROJECT_NAME} ${GAME_ENGINE_PROJECT_NAME}Build)
target_link_libraries(${PROJECT_NAME} PRIVATE ${GAME_ENGINE_PROJECT_NAME})

