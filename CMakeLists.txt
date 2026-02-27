cmake_minimum_required(VERSION 3.12)

project(vkr LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
    src/main.cpp
    src/tgaimage.cpp
)

find_package(SDL2 CONFIG REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)
target_include_directories(${PROJECT_NAME} PUBLIC src)

file(GENERATE OUTPUT .gitignore CONTENT "*")