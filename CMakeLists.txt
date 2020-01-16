cmake_minimum_required(VERSION 2.8.9)
project (demo)
add_executable(demo demo.cpp)
set (CMAKE_CXX_STANDARD 11)
TARGET_LINK_LIBRARIES(demo rt)

add_executable(demo_runnable demo_runnable.cpp)
TARGET_LINK_LIBRARIES(demo_runnable rt)
