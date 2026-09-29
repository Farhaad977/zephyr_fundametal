cmake_minimum_required(VERSION 3.20.0)
list(APPEND BOARD_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/..) #Modified to show the Root Directory
list(APPEND ZEPHYR_EXTRA_MODULES ${CMAKE_CURRENT_SOURCE_DIR}/drivers_module)
find_package(Zephyr REQUIRED)
zephyr_include_directories(drivers_module/include/samp_driver)  #Module Include directories added
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(led_blink)

target_sources(app PRIVATE src/main.cpp)