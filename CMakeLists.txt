cmake_minimum_required(VERSION 3.12)

project(vkr LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(SOURCES
    src/tgaimage.cpp
    src/sdl-render.cpp
    src/transform.cpp
    src/model.cpp
    src/line-renderer.cpp
    src/flat-rasterizer.cpp
    src/clip.cpp
    src/camera.cpp
    src/camera-rasterizer.cpp
    src/main.cpp
)

find_package(SDL2 CONFIG REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE mingw32 SDL2::SDL2)
target_include_directories(${PROJECT_NAME} PUBLIC src)

add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:${PROJECT_NAME}>"
            "${CMAKE_SOURCE_DIR}/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
)

file(GENERATE OUTPUT .gitignore CONTENT "*")