cmake_minimum_required(VERSION 3.21)

project(MAX_CHEAT_PRO VERSION 1.0.0)

add_library(${PROJECT_NAME} SHARED
    src/main.cpp
    src/features.cpp
    src/menu.cpp
    src/click-sound.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
