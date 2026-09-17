cmake_minimum_required(VERSION 3.20.0)
list(APPEND BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/..) #Modified to show the Root Directory
find_package(Zephyr REQUIRED)
project(led_blink)

target_sources(app PRIVATE src/main.cpp)