cmake_minimum_required(VERSION 2.8.11)

project(SteamNations)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -ggdb -W -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3")
set(EXECUTABLE_OUTPUT_PATH "${SteamNations_SOURCE_DIR}/build/bin/")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

#add_subdirectory(lib/gtest-1.7.0)
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

find_package(Qt5Widgets)
find_package(Qt5Gui)
find_package(Qt5Core)
find_package(Qt5Quick)
include_directories(${SteamNations_SOURCE_DIR}/src)
add_subdirectory(src)
