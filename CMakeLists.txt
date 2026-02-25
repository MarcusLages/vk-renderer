cmake_minimum_required(VERSION 3.12)

project(vk-renderer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
    src/main.cpp
    src/tgaimage.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC src)

file(GENERATE OUTPUT .gitignore CONTENT "*")