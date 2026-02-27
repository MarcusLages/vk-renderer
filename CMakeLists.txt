cmake_minimum_required(VERSION 3.12)

project(vkr LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
    src/main.cpp
    src/tgaimage.cpp
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