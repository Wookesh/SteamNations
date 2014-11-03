cmake_minimum_required(VERSION 2.8.11)

project(SteamNations)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -ggdb")
set(EXECUTABLE_OUTPUT_PATH "${SteamNations_SOURCE_DIR}/build/bin/")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets)
find_package(Qt5Gui)
find_package(Qt5Core)
add_subdirectory(src)
